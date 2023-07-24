-- SELECT * FROM bakery_security_logs
-- WHERE day = 28 AND month = 7
-- AND hour = 10 AND minute BETWEEN 15 AND 25;

-- SELECT * FROM interviews
-- WHERE day = 28 AND month = 7
-- AND transcript LIKE '%bakery%';

-- SELECT * FROM atm_transactions
-- WHERE day = 28 AND month = 7
-- AND atm_location = 'Leggett Street';

-- SELECT * FROM flights
--         JOIN airports ON flights.origin_airport_id = airports.id
-- WHERE day = 29 AND month = 7
-- AND city = 'Fiftyville'
-- ORDER BY hour, minute LIMIT 1;

-- SELECT city FROM airports
-- WHERE id = 4;

-- SELECT * FROM phone_calls
-- WHERE day = 28 AND month = 7
-- AND duration < 60;

-- SELECT * FROM passengers
-- WHERE flight_id = 36;

SELECT name FROM people
    JOIN bank_accounts ON people.id = bank_accounts.person_id
WHERE phone_number IN
    (SELECT caller FROM phone_calls
    WHERE day = 28 AND month = 7
    AND duration < 60)
AND passport_number IN
    (SELECT passport_number FROM passengers
    WHERE flight_id =
        (SELECT flights.id FROM flights
            JOIN airports ON flights.origin_airport_id = airports.id
        WHERE day = 29 AND month = 7
        AND city = 'Fiftyville'
        ORDER BY hour, minute LIMIT 1)
    )
AND license_plate IN
    (SELECT license_plate FROM bakery_security_logs
    WHERE day = 28 AND month = 7
    AND hour = 10 AND minute BETWEEN 15 AND 25
    )
AND account_number IN
    (SELECT account_number FROM atm_transactions
    WHERE day = 28 AND month = 7
    AND atm_location = 'Leggett Street');


SELECT name FROM people
WHERE phone_number IN
    (SELECT receiver FROM phone_calls
    WHERE day = 28 AND month = 7
    AND duration < 60
    AND caller =
            (SELECT phone_number FROM people WHERE name = 'Bruce')
    );
