-- Determine the calls lof of Bruce, Luca, and Iman on the day of theft

SELECT people.name, people.phone_number, phone_calls.caller, phone_calls.receiver, phone_calls.duration
FROM people
JOIN phone_calls ON people.phone_number = phone_calls.caller
                 OR people.phone_number = phone_calls.receiver
WHERE people.name IN ('Bruce', 'Luca', 'Iman')
AND phone_calls.year = 2021
AND phone_calls.month = 7
AND phone_calls.day = 28
;