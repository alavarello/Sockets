CREATE TABLE FLIGHTS
(
  flight_code TEXT PRIMARY KEY,
  origin TEXT,
  destination TEXT,
  departure_time TEXT,
  arrival_time TEXT
);

CREATE TABLE PLANES
(
  model TEXT PRIMARY KEY,
  rows INT,
  left INT,
  middle INT,
  right INT

);

CREATE TABLE RESERVATIONS
(
  flight_code TEXT,
  seat TEXT,
  passport TEXT,
  name TEXT,
  reservation_code TEXT,
  FOREIGN KEY flight_code REFERENCES FLIGHTS

);

CREATE TABLE CANCELATIONS
(
  flight_code TEXT,
  seat TEXT,
  passport TEXT,
  name TEXT,
  reservation_code TEXT,
  FOREIGN KEY flight_code REFERENCES FLIGHTS
);
