# Exhaust Sensor Array
Arduino project for logging exhaust produced by cars.

This project is a Capstone Project for the University of Massachussetts Lowell.

## Useage

The arduino takes readings from gas, tempurature, wind, and GPS sensors.
The the results are logged in an SD card in a CSV file with the following schema.

### Log file schema

- latitude
- longitude
- hour
- minute
- second
- day
- month
- year
- speed (in mph)
- CO (in ppm)
- CO2 (in ppm)
- O3 (in ppb)
- NO (in ppb)
- tempurature (in celsius)
- wind speed (in meters per second)

## Dependancies

This project imports [TinyGPSPlus](https://github.com/mikalhart/TinyGPSPlus) as a subtree for easier communication with the GPS module.

## License

This repository is protected under the MIT license.
