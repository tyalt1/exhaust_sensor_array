// Sensors
#define CO   sensor_array[0]
#define O3   sensor_array[1]
#define CO2  sensor_array[2]
#define NO   sensor_array[3]
#define TEMP sensor_array[4]
#define WIND sensor_array[5]

// GPS
#include <SoftwareSerial.h>
#include "TinyGPSPlus/TinyGPS++.h"
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

void print() {

  log_file.print(gps.location.lat(), 6);
  log_file.print(',');
  log_file.print(gps.location.lng(), 6);
  log_file.print(',');
  log_file.print(gps.time.hour());
  log_file.print(',');
  log_file.print(gps.time.minute());
  log_file.print(',');
  log_file.print(gps.time.second());
  log_file.print(',');
  log_file.print(gps.date.day());
  log_file.print(',');
  log_file.print(gps.date.month());
  log_file.print(',');
  log_file.print(gps.date.year());
  log_file.print(',');
  log_file.print(gps.speed.mph());
  log_file.print(',');
  log_file.print(map(CO,  0, 1023, 20,  2000)); //ppm
  log_file.print(',');
  log_file.print(map(CO2, 0, 1023,  0, 10000)); //ppm
  log_file.print(',');
  log_file.print(map(O3,  0, 1023, 10,  2000)); //ppb
  log_file.print(',');
  log_file.print(map(NO,  0, 1023, 50, 10000)); //ppb
  log_file.print(',');
  log_file.print(map(TEMP, 0, 1023 , 0, 0)); // TODO find temp range
  log_file.print(',');
  log_file.print(map(WIND, 0, 1023 , 0, 0)); // TODO find wind range
  log_file.println();
}

void setup() {

  gps.begin(GPS_BAUD_RATE); //GPS Setup
  SD.begin(SD_PIN);         //SD card start
}

void loop() {

  delay(5000);

  log_file = SD.open("log.csv", FILE_WRITE);

  // update GPS
  while(gps_port.available()) gps.encode(gps_port.read());

  //read from sensors
  for(unsigned int i=0; i < 6; ++i) sensor_array[i] = analogRead(i);

  print();
}
