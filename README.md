# KiQted

> A fast, interactive football fixture viewer


## Table of Contents

- [Requirement](#requirement)
- [Dependency](#dependency)
- [Features](#features)
- [Planned Updates](#updates)
- [License](#license)


---

## Requirement

- Qt 5.14.0
- MSVC 19.24.28316


---

## Dependency

- libcurl 7.51.0-DEV
- OpenSSL 1.1.0c
- libssh2 1.8.0
- zlib 1.2.8


---

## Features

KiQted is a fast, online football fixture calender. It uses libcurl in the backend to retrieve the fixture information from football-data.org in JSON format. For the rest of the GUI and data manipulation operations, it uses Qt. The main interface of the application is heavily influenced by Qt's pre-existing [Calender example](https://doc.qt.io/qt-5/qtwidgets-richtext-calendar-example.html). Currently it supports only the English Premier League.

I've used this python notebook for preparing the spritesheet. Prior to using the notebook, I resized each of the team logos to make the longer side to be 200 pixels wide while preserving the aspect ratio.


---

## Planned Updates

- Reduce the overall latency by dividing the operations over multiple threads.
- Support multiple leagues.
- Make the interface more user-friendly and less of an eyesore. ;)


---

## License

MIT
