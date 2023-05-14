import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    # Get the current user's id
    user_id = session["user_id"]

    # Get thee current cash balance for the user
    cash_balance = db.execute("SELECT cash FROM users WHERE id = :user_id", user_id=user_id)[0]["cash"]

    # Get the user's porfolio (symbol, shares, ans the current price)
    portfolio = db.execute(
        "SELECT symbol, SUM(shares) as shares, price FROM history WHERE user_id = :user_id GROUP BY symbol HAVING SUM(shares) > 0", user_id=user_id)

    # Update the price for each stock in the portfolio
    for stock in portfolio:
        updated_stock = lookup(stock["symbol"])
        stock["price"] = updated_stock["price"]

    # Calculate the total value of each holding (shares * price) and the grand total (cash + stock value)
    total_value = 0
    for stock in portfolio:
        stock["total"] = stock["shares"] * stock["price"]
        total_value += stock["total"]
    total_value += cash_balance

    return render_template("index.html", portfolio=portfolio, cash_balance=cash_balance, total_value=total_value)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    # # Check if user submitted form
    if request.method == "POST":

        # Ensure symbol was submitted
        if not request.form.get("symbol"):
            return apology("Must provide symbol", 400)

        # Ensure shares was submitted
        elif not request.form.get("shares"):
            return apology("Must provide shares", 400)

        # Ensure shares is a positive integer
        try:
            shares = float(request.form.get("shares"))
            if not shares or shares <= 0:
                return apology("Shares must be a positive integer", 400)

        except:
            return apology("Shares must be a positive integer", 400)

        # Lookup Stock information
        quote = lookup(request.form.get("symbol"))
        if not quote:
            return apology("Invalid Symbol", 400)

        # Check if user has enough cash
        cash = db.execute("SELECT cash FROM users WHERE id = :user_id", user_id=session["user_id"])[0]["cash"]
        if cash < quote["price"] * shares:
            return apology("not enough cash", 400)

        # Udpate user's cash and insert transaction into history
        db.execute("UPDATE users SET cash = cash - :purchase WHERE id = :user_id",
                   purchase=quote["price"] * shares, user_id=session["user_id"])
        db.execute("INSERT INTO history (user_id, symbol, shares, price, transacted, date) VALUES (:user_id, :symbol, :shares, :price, 'BUY', datetime('now'))",
                   user_id=session["user_id"], symbol=quote["symbol"], shares=shares, price=quote["price"])

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET method
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    # Query the database for all tranactions of the current user
    transactions = db.execute("SELECT * FROM history WHERE user_id = :user_id ORDER BY date DESC", user_id=session["user_id"])
    return render_template("history.html", transactions=transactions)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # Check if user submitted form
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("Must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("Must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    # Check if user submitted form
    if request.method == "POST":
        # Get the symbol from the form
        symbol = request.form.get("symbol")

        # Lookup the stock's price
        quote = lookup(symbol)

        if quote == None:
            return apology("Invalid symbol")

        # Render quoted.html template with the quote information
        return render_template("quoted.html", quote=quote)
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    # Check if user submitted form
    if request.method == "POST":

        # Get form inputs
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        # Check if inputs are valid
        if not username:
            return apology("Must provide a username", 400)
        elif not password:
            return apology("Must provide a password", 400)
        elif not confirmation:
            return apology("Must confirm password", 400)
        elif password != confirmation:
            return apology("Passwords do not match", 400)

        # Check if username already exists
        rows = db.execute("SELECT * FROM users WHERE username = :username", username=username)
        if len(rows) != 0:
            return apology("Username already exists", 400)

        # Hash password
        hashed_password = generate_password_hash(password)

        # Insert user into users table
        db.execute("INSERT INTO users (username, hash) VALUES (:username, :hash)", username=username, hash=hashed_password)

        # Redirect user to login page
        return redirect("/login")

    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    # Check if user submitted form
    if request.method == "POST":

        symbol = request.form.get("symbol")
        shares = request.form.get("shares")

        # Ensure symbol was selected
        if not symbol:
            return apology("Must select a Symbol", 400)

        # Ensure shares is not blank
        elif not shares:
            return apology("Must provide Shares", 400)

        # Check if shares is a positive integer
        try:
            shares = float(shares)
            if shares <= 0:
                return apology("Shares must be a positive integer", 400)

        except:
            return apology("Shares must be a positive integer", 400)

        # Check if user owns shares of that stock
        stocks = db.execute("SELECT * FROM history WHERE user_id = :user_id AND symbol = :symbol",
                            user_id=session["user_id"], symbol=symbol)
        if not stocks:
            return apology("You do not own any shares of that stock")
        else:
            total_shares = sum(stock["shares"] for stock in stocks)
            if shares > total_shares:
                return apology("You do not own that many shares of that stock")
            else:
                stock_info = lookup(symbol)

                # Calculate total cost of sale
                total_cost = shares * stock_info["price"]
                # Update user's cash
                db.execute("UPDATE users SET cash = cash + :total_cost WHERE id = :user_id",
                           total_cost=total_cost, user_id=session["user_id"])
                # Update user's history
                db.execute("INSERT INTO history (user_id, symbol, shares, price, transacted, date) VALUES (:user_id, :symbol, :shares, :price, 'SELL', datetime('now'))",
                           user_id=session["user_id"], symbol=symbol, shares=shares, price=stock_info["price"])

        # Redirect to home page
        return redirect("/")

    else:
        stocks = db.execute("SELECT DISTINCT symbol FROM history WHERE user_id = :user_id", user_id=session["user_id"])
        return render_template("sell.html", stocks=stocks)


@app.route("/change_password", methods=["GET", "POST"])
@login_required
def change_password():
    """Change user's password"""

    if request.method == "POST":
        current_password = request.form.get("current_password")
        new_password = request.form.get("new_password")
        confirm_password = request.form.get("confirm_password")

        # Ensure current password was submitted
        if not current_password:
            return apology("Current password is required", 403)

        # Ensure new password was submitted
        if not new_password:
            return apology("New password is required", 403)

        # Ensure password confirmation was submitted
        elif not confirm_password:
            return apology("Please confirm your new password", 403)

        # Ensure new password and confirmation match
        elif new_password != confirm_password:
            return apology("Passwords don't match", 403)

        # Ensure current password is correct
        rows = db.execute("SELECT * FROM users WHERE id = :user_id", user_id=session["user_id"])
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], current_password):
            return apology("Incorrect current password", 403)

        # Update password
        db.execute("UPDATE users SET hash = :hash WHERE id = :user_id",
                   hash=generate_password_hash(new_password), user_id=session["user_id"])
        return redirect("/")
    else:
        return render_template("change_password.html")