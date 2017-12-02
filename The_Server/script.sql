CREATE TABLE FLIGHTS
(
  flight_code TEXT PRIMARY KEY NOT NULL,
  origin TEXT NOT NULL,
  destination TEXT NOT NULL,
  departure_time TEXT NOT NULL,
  departure_date TEXT NOT NULL,
  arrival_time TEXT NOT NULL,
  arrival_date TEXT NOT NULL,
  model TEXT NOT NULL,
  FOREIGN KEY(model) REFERENCES PLANES
);

CREATE TABLE PLANES
(
  model TEXT PRIMARY KEY NOT NULL,
  rows INT NOT NULL,
  left INT NOT NULL,
  middle INT NOT NULL,
  right INT NOT NULL

);

CREATE TABLE RESERVATIONS
(
  flight_code TEXT NOT NULL,
  seat TEXT NOT NULL,
  name TEXT NOT NULL,
  PRIMARY KEY(flight_code, seat),
  FOREIGN KEY (flight_code) REFERENCES FLIGHTS

);

CREATE TABLE CANCELATIONS
(
  flight_code TEXT NOT NULL,
  seat TEXT NOT NULL,
  name TEXT NOT NULL,
  PRIMARY KEY(flight_code, seat),
  FOREIGN KEY (flight_code) REFERENCES FLIGHTS
);
