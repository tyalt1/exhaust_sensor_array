// Sensors
#define CO   sensor_array[0]
#define O3   sensor_array[1]
#define CO2  sensor_array[2]
#define NO   sensor_array[3]
#define TEMP sensor_array[4]
#define WIND sensor_array[5]

// GPS
#include <SoftwareSerial.h>
#include "TinyGPS.h"
#define GPS_RX           9 // Arduino RX pin connected to GPS TX
#define GPS_TX           8 // Arduino TX pin connected to GPS RX
#define GPS_BAUD_RATE 9600 // The GPS Shield module defaults to 9600 baud
SoftwareSerial gps_port(GPS_TX, GPS_RX);
TinyGPSPlus gps;

// SD card
#include <SD.h>
#include <SPI.h>
#define SD_pin 10

// code!
int sensor_array[6];
File log_file;

void read_sensors() {

  for(unsigned int i=0; i < 6; ++i) array[i] = analogRead(i);
}

void print() {


}

void setup() {

  gps.begin(GPS_BAUD_RATE); //GPS Setup
  SD.begin(SD_PIN)          //SD card start
}

void loop() {
  delay(5000);

  log_file = SD.open("log.csv", FILE_WRITE);

  //read from sensors
  read_sensors();

  // update GPS
  while(gps_port.available()) gps.encode(gps_port.read());

  // TODO read from GPS
  // gps.date.month()
  // gps.date.day()
  // gps.date.year()
  // gps.time.hour()
  // gps.time.minute()
  // gps.time.second()
  // gps.location.lat() in base6
  // gps.location.lng() in base6
  // gps.altitude.feet()
  // gps.course.degree()
  // gps.speed.mph()
  // gps.satellites.value()

  // TODO write to uSD card
  print();
}
