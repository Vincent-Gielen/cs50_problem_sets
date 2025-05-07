-- Keep a log of any SQL queries you execute as you solve the mystery.


-- See how the months and days are stored in the crime_scene_reports table
SELECT month, day
FROM crime_scene_reports;

-- Get the data from the crime matching the date and street
SELECT *
FROM crime_scene_reports
WHERE year = 2023
AND month = 7
AND day = 28
AND street LIKE 'Humphrey Street';

-- View the transcripts of the 3 interviews conducted that day mentioning the bakery
-- Info: cars leaving, atm on Legget Street, phone call < 1min and flight out tomorrow paid by reciever
SELECT transcript
FROM interviews
WHERE transcript LIKE '%bakery%'
AND year = 2023
AND month = 7
AND day = 28;

-- View the activity and license plates of cars that left within 10min of the theft
SELECT activity, license_plate
FROM bakery_security_logs
WHERE year = 2023
AND month = 7
AND day = 28
AND hour = 10
AND minute BETWEEN 15 AND 25;

-- See what transcation types there are at the ATM
SELECT DISTINCT transaction_type
FROM atm_transactions;

-- See what bakery results there are for atm_location -> none
SELECT DISTINCT atm_location
FROM atm_transactions
WHERE atm_location LIKE '%bakery%';

-- View the withdraw transactions made the day of the theft at Leggett Street
SELECT account_number, atm_location, amount
FROM atm_transactions
WHERE year = 2023
AND month = 7
AND day = 28
AND atm_location LIKE 'Leggett Street';

-- View the person_id of the people that made these withdraw transactions
SELECT DISTINCT ba.person_id
FROM bank_accounts AS ba
JOIN atm_transactions AS atm ON ba.account_number = atm.account_number
WHERE ba.account_number IN (
    SELECT account_number
    FROM atm_transactions
    WHERE year = 2023
    AND month = 7
    AND day = 28
    AND atm_location LIKE 'Leggett Street'
);

-- View all callers and recievers that made phone calls that lasted less than a minute
SELECT caller, receiver
FROM phone_calls
WHERE year = 2023
AND month = 7
AND day = 28
AND duration < 60;

-- VIEW all people that match the found license plates, phone numbers and person_ids(from the atm)-> Diana(514354) and Bruce(686048)
SELECT name, id
FROM people
WHERE phone_number IN (
    SELECT caller
    FROM phone_calls
    WHERE year = 2023
    AND month = 7
    AND day = 28
    AND duration < 60
)
AND license_plate IN (
    SELECT license_plate
    FROM bakery_security_logs
    WHERE year = 2023
    AND month = 7
    AND day = 28
    AND hour = 10
    AND activity = 'exit'
    AND minute BETWEEN 15 AND 25
)
AND id IN (
    SELECT DISTINCT ba.person_id
    FROM bank_accounts AS ba
    JOIN atm_transactions AS atm ON ba.account_number = atm.account_number
    WHERE ba.account_number IN (
        SELECT account_number
        FROM atm_transactions
        WHERE year = 2023
        AND month = 7
        AND day = 28
        AND atm_location LIKE 'Leggett Street'
    )
);

-- Find the recievers of the phone calls from Diana -> Philip(847116) and Bruce -> Robin(864400)
SELECT name, id
FROM people
WHERE phone_number IN (
    SELECT receiver
    FROM phone_calls
    WHERE year = 2023
    AND month = 7
    AND day = 28
    AND duration < 60
    AND caller IN (
        SELECT phone_number
        FROM people
        WHERE name IN ('Diana', 'Bruce')
    )
);

-- Get all their passport numbers
SELECT name, passport_number
FROM people
WHERE name IN ('Bruce', 'Robin', 'Diana', 'Philip');

-- View the earliest flight from Fiftyville tomorrow
SELECT *
FROM airports
JOIN flights ON flights.origin_airport_id = airports.id
WHERE year = 2023
AND month = 7
AND day = 29
ORDER BY hour
LIMIT 1;

-- View the flight and their destination and see if one of the suspects has a seat booked
SELECT passengers.passport_number, airports.city
FROM passengers
JOIN flights ON passengers.flight_id = flights.id
JOIN airports ON flights.destination_airport_id = airports.id
WHERE flights.id = (
    SELECT flights.id
    FROM flights
    JOIN airports ON flights.origin_airport_id = airports.id
    WHERE year = 2023
    AND month = 7
    AND day = 29
    ORDER BY hour
    LIMIT 1
)
AND passengers.passport_number IN (
    SELECT passport_number
    FROM people
    WHERE name IN ('Bruce', 'Robin', 'Diana', 'Philip')
);


-- Select the people that match the travelers
SELECT name
FROM people
WHERE passport_number IN (
    SELECT passengers.passport_number
    FROM passengers
    JOIN flights ON passengers.flight_id = flights.id
    JOIN airports ON flights.destination_airport_id = airports.id
    WHERE year = 2023
    AND month = 7
    AND day = 29
    AND flights.id = (
        SELECT flights.id
        FROM flights
        JOIN airports ON flights.origin_airport_id = airports.id
        WHERE year = 2023
        AND month = 7
        AND day = 29
        ORDER BY hour
        LIMIT 1
    )
    AND passengers.passport_number IN (
        SELECT passport_number
        FROM people
        WHERE name IN ('Bruce', 'Robin', 'Diana', 'Philip')
    )
);

