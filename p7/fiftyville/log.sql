-- Keep a log of any SQL queries you execute as you solve the mystery.
--Crime scene report
SELECT
  description
FROM
  crime_scene_reports
WHERE
  DAY = 28
  AND MONTH = 7
  AND street = 'Humphrey Street'
  AND YEAR = 2021;

-- Crime scene witness report
SELECT
  name,
  transcript
FROM
  interviews
WHERE
  YEAR = 2021
  AND DAY = 28
  AND MONTH = 7;

--Those who withdrew money on that date
SELECT
  people.name,
  people.passport_number
FROM
  people
  JOIN bank_accounts ON person_id = people.id
  JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number
WHERE
  atm_location = 'Leggett Street'
  AND DAY = 28
  AND MONTH = 7
  AND YEAR = 2021
  AND transaction_type = 'withdraw';

--People who called
SELECT
  people.name,
  people.phone_number,
  phone_calls.duration,
  people.passport_number,
  phone_calls.receiver
FROM
  phone_calls
  JOIN people ON people.phone_number = phone_calls.caller
WHERE
  phone_calls.day = 28
  AND phone_calls.month = 7
  AND phone_calls.year = 2021
  AND phone_calls.duration < 60;

--The first plane that leaves the next day
SELECT
  flights.hour,
  airports.city,
  flights.id
FROM
  airports
  JOIN flights ON airports.id = flights.destination_airport_id
WHERE
  DAY = 29
  AND MONTH = 7
  AND YEAR = 2021
  AND flights.origin_airport_id IN (
    SELECT
      id
    FROM
      airports
    WHERE
      city = 'Fiftyville'
  )
ORDER BY
  flights.hour;

--The cars that came out of the parking lot
SELECT
  name,
  bakery_security_logs.minute
FROM
  people
  JOIN bakery_security_logs ON people.license_plate = bakery_security_logs.license_plate
WHERE
  DAY = 28
  AND MONTH = 7
  AND YEAR = 2021
  AND activity = 'exit'
  AND HOUR = 10
  AND MINUTE >= 15
  AND MINUTE <= 20
ORDER BY
  bakery_security_logs.minute;

--WHO ??
SELECT
  name,
  passengers.passport_number,
  people.phone_number,
FROM
  people
  JOIN passengers ON passengers.passport_number = people.passport_number
  JOIN flights ON flights.id = passengers.flight_id
WHERE
  flights.id = 36
  AND passengers.passport_number IN (
    SELECT
      people.passport_number
    FROM
      phone_calls
      JOIN people ON people.phone_number = phone_calls.caller
    WHERE
      phone_calls.day = 28
      AND phone_calls.month = 7
      AND phone_calls.year = 2021
      AND phone_calls.duration < 60
  )
  AND people.passport_number IN (
    SELECT
      people.passport_number
    FROM
      people
      JOIN bank_accounts ON person_id = people.id
      JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number
    WHERE
      atm_location = 'Leggett Street'
      AND DAY = 28
      AND MONTH = 7
      AND YEAR = 2021
      AND transaction_type = 'withdraw'
  )
  AND passengers.passport_number IN (
    SELECT
      people.passport_number
    FROM
      people
      JOIN bakery_security_logs ON people.license_plate = bakery_security_logs.license_plate
    WHERE
      DAY = 28
      AND MONTH = 7
      AND YEAR = 2021
      AND activity = 'exit'
      AND HOUR = 10
      AND MINUTE >= 15
      AND MINUTE <= 20
    ORDER BY
      bakery_security_logs.minute
  );

--Who was the accomplice of the robbery ??
SELECT
  people.name,
  phone_calls.duration,
  people.phone_number
FROM
  phone_calls
  JOIN people ON people.phone_number = phone_calls.receiver
WHERE
  phone_calls.day = 28
  AND phone_calls.month = 7
  AND phone_calls.year = 2021
  AND phone_calls.duration < 60
  AND phone_calls.caller = '(367) 555-5533';