-- Keep a log of any SQL queries you execute as you solve the mystery.


-- Initial setup
-- List all tables in the database
.tables


-- Print the schema of specific tables
.schema crime_scene_reports


-- Find crime scene reports on July 28, 2021 on Humphrey Street matching the theft of CS%) duck
-- Looking for crime scene report's description for the theft that took place on July 28, 2021 on Humphrey Street
SELECT description
  FROM crime_scene_reports
 WHERE year = 2021
   AND month = 07
   AND day = 28
   AND street = 'Humphrey Street';

/*
+--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
|                                                                                                       description                                                                                                        |
+--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
| Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery. Interviews were conducted today with three witnesses who were present at the time – each of their interview transcripts mentions the bakery. |
| Littering took place at 16:36. No known witnesses.                                                                                                                                                                       |
+--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
*/


-- Find interviews transcripts for witnesses at the bakery during theft
SELECT transcript, name
  FROM interviews
 WHERE year = 2021
   AND month = 07
   AND day = 28;

/* 3 interviews seem promising
-- "I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at Emma's bakery, I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money." (Eugene)
-- "Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away. If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame." (Ruth)
-- "As the thief was leaving the bakery, they called someone who talked to them for less than a minute. In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket." (Raymond)
*/


-- Find list of people who made a transaction on Leggett Street on July 28, 2021, the amount they withdrew, their phone number, passport number, and their license plate
SELECT people.name, atm_transactions.amount, people.phone_number, people.passport_number, people.license_plate
FROM atm_transactions
JOIN bank_accounts ON atm_transactions.account_number = bank_accounts.account_number
JOIN people ON bank_accounts.person_id = people.id
WHERE atm_transactions.transaction_type = 'withdraw' AND atm_transactions.year = 2021 AND atm_transactions.month = 7 AND atm_transactions.day = 28 AND atm_transactions.atm_location = 'Leggett Street';

/*
+---------+--------+----------------+-----------------+---------------+
|  name   | amount |  phone_number  | passport_number | license_plate |
+---------+--------+----------------+-----------------+---------------+
| Bruce   | 50     | (367) 555-5533 | 5773159633      | 94KL13X       |
| Diana   | 35     | (770) 555-1861 | 3592750733      | 322W7JE       |
| Brooke  | 80     | (122) 555-4581 | 4408372428      | QX4YZN3       |
| Kenny   | 20     | (826) 555-1652 | 9878712108      | 30G67EN       |
| Iman    | 20     | (829) 555-5269 | 7049073643      | L93JTIZ       |
| Luca    | 48     | (389) 555-5198 | 8496433585      | 4328GD8       |
| Taylor  | 60     | (286) 555-6063 | 1988161715      | 1106N58       |
| Benista | 30     | (338) 555-6650 | 9586786673      | 8X428L0       |
+---------+--------+----------------+-----------------+---------------+
*/


-- Find cars that left the bakery parking lot between 10:15 and 10:30 am on July 28, 2021 using the bakery security logs
-- First, determine the different types of activities that are logged
SELECT DISTINCT activity
  FROM bakery_security_logs;
/*
+----------+
| activity |
+----------+
| entrance |
| exit     |
+----------+
*/

-- Second, find cars that left the bakery parking lot between 10:15 and 10:30 am on July 28, 2021
SELECT license_plate, hour, minute
  FROM bakery_security_logs
 WHERE year = 2021
   AND month = 7
   AND day = 28
   AND hour = 10
   AND minute BETWEEN 15 AND 30
   AND activity = 'exit';

/*
+---------------+------+--------+
| license_plate | hour | minute |
+---------------+------+--------+
| 5P2BI95       | 10   | 16     |
| 94KL13X       | 10   | 18     |
| 6P58WS2       | 10   | 18     |
| 4328GD8       | 10   | 19     |
| G412CB7       | 10   | 20     |
| L93JTIZ       | 10   | 21     |
| 322W7JE       | 10   | 23     |
| 0NTHK55       | 10   | 23     |
+---------------+------+--------+
*/


-- Correlating the names and license plate numbers of people who were on Leggett Street on July 28, and left the bakery parking lot between 10:15 and 10:30
SELECT people.name, people.license_plate, bakery_security_logs.activity, bakery_security_logs.hour, bakery_security_logs.minute
  FROM bakery_security_logs
       JOIN people
         ON bakery_security_logs.license_plate = people.license_plate
      WHERE bakery_security_logs.year = 2021
        AND bakery_security_logs.month = 7
        AND bakery_security_logs.day = 28
        AND bakery_security_logs.activity = 'exit'
        AND bakery_security_logs.hour = 10
        AND bakery_security_logs.minute BETWEEN 15 AND 30;

/*
+---------+---------------+----------+------+--------+
|  name   | license_plate | activity | hour | minute |
+---------+---------------+----------+------+--------+
| Vanessa | 5P2BI95       | exit     | 10   | 16     |
| Bruce   | 94KL13X       | exit     | 10   | 18     |
| Barry   | 6P58WS2       | exit     | 10   | 18     |
| Luca    | 4328GD8       | exit     | 10   | 19     |
| Sofia   | G412CB7       | exit     | 10   | 20     |
| Iman    | L93JTIZ       | exit     | 10   | 21     |
| Diana   | 322W7JE       | exit     | 10   | 23     |
| Kelsey  | 0NTHK55       | exit     | 10   | 23     |
+---------+---------------+----------+------+--------+
*/
/* We note that Bruce, Luca, and Iman were at the ATM the day of theft, and left the parking lot of the bakery within 10 minutes of theft */


-- Finding the names, phone numbers, and license of people who were at the ATM on Leggett Street on July 28 and left the bakery within 10 minutes of the theft
SELECT people.name, people.phone_number, phone_calls.caller, phone_calls.receiver, phone_calls.duration
  FROM people
       JOIN phone_calls
         ON people.phone_number = phone_calls.caller
         OR people.phone_number = phone_calls.receiver
      WHERE people.name IN ('Bruce', 'Luca', 'Iman')
        AND phone_calls.year = 2021
        AND phone_calls.month = 7
        AND phone_calls.day = 28;

/*
+-------+----------------+----------------+----------------+----------+
| name  |  phone_number  |     caller     |    receiver    | duration |
+-------+----------------+----------------+----------------+----------+
| Luca  | (389) 555-5198 | (544) 555-8087 | (389) 555-5198 | 595      |
| Luca  | (389) 555-5198 | (609) 555-5876 | (389) 555-5198 | 60       |
| Bruce | (367) 555-5533 | (367) 555-5533 | (022) 555-4052 | 241      |
| Bruce | (367) 555-5533 | (367) 555-5533 | (344) 555-9601 | 120      |
| Bruce | (367) 555-5533 | (367) 555-5533 | (375) 555-8161 | 45       |
| Bruce | (367) 555-5533 | (367) 555-5533 | (704) 555-5790 | 75       |
+-------+----------------+----------------+----------------+----------+
*/
/* Based on interviews and the table above, we note that:
   - Iman has not made any call that day
   - Luca only received calls
   - Bruce called 4 different people but only
   one call lasted less than a minute
*/


-- Find the name and the passport number of the call receiver
SELECT name, passport_number
  FROM people
 WHERE phone_number = '(375) 555-8161';

/*
+-------+-----------------+
| name  | passport_number |
+-------+-----------------+
| Robin |                 |
+-------+-----------------+
*/
/* The suspect named Robin, has no passport number registered. We can conlude that she won't travel. Nevertheless, more information is required, the query will be repated including license_plate column */

-- Find the name, passport number, and license plate of the suspect
SELECT name, passport_number, license_plate
  FROM people
 WHERE phone_number = '(375) 555-8161';

/*
+-------+-----------------+---------------+
| name  | passport_number | license_plate |
+-------+-----------------+---------------+
| Robin |                 | 4V16VO0       |
+-------+-----------------+---------------+
*/


-- Find the bakery security log of this license plate
SELECT *
  FROM bakery_security_logs
 WHERE license_plate = '4V16VO0';

/*
+-----+------+-------+-----+------+--------+----------+---------------+
| id  | year | month | day | hour | minute | activity | license_plate |
+-----+------+-------+-----+------+--------+----------+---------------+
| 248 | 2021 | 7     | 28  | 8    | 50     | entrance | 4V16VO0       |
| 249 | 2021 | 7     | 28  | 8    | 50     | exit     | 4V16VO0       |
+-----+------+-------+-----+------+--------+----------+---------------+
*/
/* We note that Robin, went to the bakery parking lot shortly before the theft.
   She is now confirmed suspect of the crime along with Bruce */


-- Find the flight that registered Bruce as passenger
SELECT flight_id
  FROM passengers
 WHERE passport_number = 5773159633;

/*
+-----------+
| flight_id |
+-----------+
| 36        |
+-----------+
*/


-- Find Bruce destination airport of the flight 36 on July 29
SELECT destination_airport_id
  FROM flights
  JOIN passengers ON flights.id = passengers.flight_id
 WHERE passengers.flight_id = 36
   AND passengers.passport_number = 5773159633
   AND flights.year = 2021
   AND flights.month = 7
   AND flights.day = 29;

/*
+------------------------+
| destination_airport_id |
+------------------------+
| 4                      |
+------------------------+
*/

-- Find full_name and city of airport 4
SELECT full_name, city
  FROM airports
 WHERE id = 4;

/*
+-------------------+---------------+
|     full_name     |     city      |
+-------------------+---------------+
| LaGuardia Airport | New York City |
+-------------------+---------------+
*/
/* Bruce escaped to LaGuardia Airport in New York City */