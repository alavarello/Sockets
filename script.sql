CREATE TABLE FLIGHTS
(
  flight_code TEXT PRIMARY KEY,
  origin TEXT,
  destination TEXT,
  departure_time TEXT,
  departure_date TEXT,
  arrival_time TEXT,
  arrival_date TEXT,
  model TEXT,
  FOREIGN KEY(model) REFERENCES PLANES
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
  reservation_code TEXT PRIMARY KEY,
  FOREIGN KEY (flight_code) REFERENCES FLIGHTS

);

CREATE TABLE CANCELATIONS
(
  flight_code TEXT,
  seat TEXT,
  passport TEXT,
  name TEXT,
  reservation_code TEXT,
  FOREIGN KEY (flight_code) REFERENCES FLIGHTS
);
