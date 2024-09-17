-- Keep a log of any SQL queries you execute as you solve the mystery.

SELECT * FROM interviews WHERE(
day = (SELECT day FROM crime_scene_reports WHERE description LIKE '%duck%')
AND year = (SELECT year FROM crime_scene_reports WHERE description LIKE '%duck%')
AND month = (SELECT month FROM crime_scene_reports WHERE description LIKE '%duck%')) AND transcript LIKE '%bakery%';

SELECT * FROM bakery_security_logs WHERE day = 28 AND month = 07 AND year = 2023 AND hour = 10 AND minute >= 15;

SELECT * FROM atm_transactions WHERE day = 28 AND month = 07 AND year = 2023 AND atm_location = 'Leggett Street';

SELECT * FROM phone_calls WHERE day = 28 AND month = 07 AND year = 2023 AND duration < 60;

SELECT * FROM people WHERE license_plate = '322W7JE';
SELECT * FROM people WHERE license_plate = '0NTHK55';

SELECT caller FROM phone_calls WHERE caller IN
(SELECT phone_number FROM people WHERE license_plate = '0NTHK55') AND day = 28 AND month = 07 AND year = 2023 AND duration < 60;

SELECT * FROM flights WHERE origin_airport_id = 8 AND day = 29 AND destination_airport_id = 4;


SELECT * FROM people WHERE id IN
(SELECT person_id FROM bank_accounts WHERE account_number IN
(SELECT account_number FROM atm_transactions WHERE day = 28 AND month = 07 AND year = 2023 AND atm_location = 'Leggett Street' AND transaction_type = 'withdraw') AND person_id IN
(SELECT id FROM people WHERE passport_number IN
(SELECT passport_number FROM passengers WHERE flight_id = 36) AND phone_number IN
(SELECT phone_number FROM phone_calls WHERE day = 28 AND month = 07 AND year = 2023 AND duration < 60) AND license_plate IN
(SELECT license_plate FROM bakery_security_logs WHERE day = 28 AND month = 07 AND year = 2023 AND hour = 10 AND minute >= 15 AND minute <= 18 AND activity = 'exit')));


SELECT name FROM people WHERE phone_number IN
(SELECT receiver FROM phone_calls WHERE caller = '(367) 555-5533' AND day = 28 AND month = 07 AND year = 2023 AND duration < 60);
