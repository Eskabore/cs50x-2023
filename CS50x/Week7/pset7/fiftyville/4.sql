SELECT license_plate, hour, minute
FROM bakery_security_logs
WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND minute BETWEEN 15 AND 30 AND activity = 'exit';