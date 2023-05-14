SELECT people.name, people.license_plate, bakery_security_logs.activity, bakery_security_logs.hour, bakery_security_logs.minute
FROM bakery_security_logs
JOIN people ON bakery_security_logs.license_plate = people.license_plate
WHERE bakery_security_logs.year = 2021 AND bakery_security_logs.month = 7 AND bakery_security_logs.day = 28 AND bakery_security_logs.activity = 'exit' AND bakery_security_logs.hour = 10 AND bakery_security_logs.minute BETWEEN 15 AND 30;