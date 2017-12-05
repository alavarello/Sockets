CREATE TABLE FLIGHTS
(
  flight_code TEXT PRIMARY KEY NOT NULL CHECK(length("flight_code") = 5),
  origin TEXT NOT NULL CHECK(length("origin") = 3),
  destination TEXT NOT NULL CHECK(length("destination") = 3),
  departure_time TEXT NOT NULL CHECK(length("departure_time") = 5),
  departure_date TEXT NOT NULL CHECK(length("departure_date") = 10),
  arrival_time TEXT NOT NULL CHECK(length("arrival_time") = 5),
  arrival_date TEXT NOT NULL CHECK(length("arrival_date") = 10),
  model TEXT NOT NULL CHECK(length("model") <= 14),
  FOREIGN KEY(model) REFERENCES PLANES
);

CREATE TABLE PLANES
(
  model TEXT PRIMARY KEY NOT NULL CHECK(length("model") <= 14),
  rows INT NOT NULL CHECK(rows > 0),
  left INT NOT NULL CHECK(left >= 0),
  middle INT NOT NULL CHECK(middle >= 0),
  right INT NOT NULL CHECK(right >= 0)

);

CREATE TABLE RESERVATIONS
(
  flight_code TEXT NOT NULL CHECK(length("flight_code") = 5),
  seat TEXT NOT NULL CHECK(length("seat") = 3),
  name TEXT NOT NULL CHECK(length("name") <= 24),
  PRIMARY KEY(flight_code, seat),
  FOREIGN KEY (flight_code) REFERENCES FLIGHTS
);

CREATE TABLE CANCELATIONS
(
  flight_code TEXT NOT NULL CHECK(length("flight_code") = 5),
  seat TEXT NOT NULL CHECK(length("seat") = 3),
  name TEXT NOT NULL CHECK(length("name") <= 24),
  Id INTEGER PRIMARY KEY AUTOINCREMENT,
  FOREIGN KEY (flight_code) REFERENCES FLIGHTS
);
