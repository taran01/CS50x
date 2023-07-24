-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Find crime scene discription
SELECT description
FROM crime_scene_reports
WHERE day = 28
AND month = 7
AND street = 'Humphrey Street';

-- Find the persons who got interviewed
SELECT * FROM interviews
WHERE day = 28 AND month = 7
AND transcript LIKE '%bakery%';

-- Bakery log within 10 minutes of theft as mentioned by witness 1
SELECT * FROM bakery_security_logs
WHERE day = 28 AND month = 7
AND hour = 10 AND minute BETWEEN 15 AND 25;

-- ATM transactions at leggett street as mentioned by witness 2
SELECT * FROM atm_transactions
WHERE day = 28 AND month = 7
AND atm_location = 'Leggett Street';

--  Flight data of next day's first flight out of Fiftyville (Witeness 3)
SELECT * FROM flights
        JOIN airports ON flights.origin_airport_id = airports.id
WHERE day = 29 AND month = 7
AND city = 'Fiftyville'
ORDER BY hour, minute LIMIT 1;

-- THE THIEF
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


--The Accomliace is
SELECT name FROM people
WHERE phone_number IN
    (SELECT receiver FROM phone_calls
    WHERE day = 28 AND month = 7
    AND duration < 60
    AND caller =
            (SELECT phone_number FROM people WHERE name = 'Bruce')
    );