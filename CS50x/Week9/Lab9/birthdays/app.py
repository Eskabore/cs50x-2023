import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session, url_for
from flask_session import Session

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True
# Configure session
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///birthdays.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/", methods=["GET", "POST"])
def index():

    if not session.get("name"):
        return redirect("/login")
        
    if request.method == "POST":

        # Add the user's entry into the database
        # Get the user's input
        name = request.form.get("name")
        month = request.form.get("month")
        day = request.form.get("day")

        # Insert the user's input into the birthdays table
        db.execute("INSERT INTO birthdays (name, month, day) VALUES (?, ?, ?)", name, month, day)

        # Redirect to home page
        return redirect("/")

    else:

        # Display the entries in the database on index.html
        # Fetch data from the birthdays table
        birthdays = db.execute("SELECT * FROM birthdays")

        # Pass the data to the index.html template
        return render_template("index.html", birthdays=birthdays)


@app.route("/delete/<int:id>", methods=["POST"])
def delete(id):
    # Delete the entry from the birthdays table
    db.execute("DELETE FROM birthdays WHERE id = :id", id=id)
    return redirect("/")

@app.route("/login", methods=["GET", "POST"])
def login():
    if request.method == "POST":
        session["name"] = request.form.get("name")
        return redirect("/")
    return render_template("login.html")


@app.route("/logout")
def logout():
    session["name"] = None
    return redirect("/")