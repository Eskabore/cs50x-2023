SELECT destination_airport_id FROM flights
JOIN passengers ON flights.id = passengers.flight_id
WHERE passengers.flight_id = 36
AND passengers.passport_number = 5773159633
AND flights.year = 2021
AND flights.month = 7
AND flights.day = 29;