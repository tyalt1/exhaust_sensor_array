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
#define GPS_RX           9 // Arduino RX pin connected to GPS RX
#define GPS_TX           8 // Arduino TX pin connected to GPS TX
#define GPS_BAUD_RATE 9600 // The GPS Shield module defaults to 9600 baud
SoftwareSerial gps_port(GPS_TX, GPS_RX);
TinyGPSPlus gps;

// SD card
#include <SD.h>
#define SD_PIN 10

// code!
//#define DEBUG
#ifdef DEBUG
#define fprint   Serial.print
#define fprintln Serial.println
#else
#define fprint   log_file.print
#define fprintln log_file.println
#endif

const int analog[] = {A0, A1, A2, A3, A4, A5};
int sensor_array[6];

void print_log() {

  File log_file = SD.open("log.csv", FILE_WRITE);

  fprint(gps.location.lat(), 6);
  fprint(',');
  fprint(gps.location.lng(), 6);
  fprint(',');
  fprint(gps.time.hour());
  fprint(',');
  fprint(gps.time.minute());
  fprint(',');
  fprint(gps.time.second());
  fprint(',');
  fprint(gps.date.day());
  fprint(',');
  fprint(gps.date.month());
  fprint(',');
  fprint(gps.date.year());
  fprint(',');
  fprint(gps.speed.mph());
  fprint(',');
  fprint(map(CO,  0, 1023, 20,  2000)); //ppm
  fprint(',');
  fprint(map(CO2, 0, 1023,  0, 10000)); //ppm
  fprint(',');
  fprint(map(O3,  0, 1023, 10,  2000)); //ppb
  fprint(',');
  fprint(map(NO,  0, 1023, 50, 10000)); //ppb
  fprint(',');
  fprint(map(TEMP, 0, 1023 , -40, 125)); // celsius
  fprint(',');
  fprint(map(WIND, 0, 1023 , 0, 100)); // meter per second
  fprintln();

  log_file.close();
}

void setup() {

  Serial.begin(9600);
  gps_port.begin(GPS_BAUD_RATE); //GPS Setup

  #ifndef DEBUG
  //SD card start
  pinMode(SD_PIN, OUTPUT);
  digitalWrite(SD_PIN, HIGH);
  SD.begin(SD_PIN);

  //print header
  if(!SD.exists("log.csv")) {
    File log_file = SD.open("log.csv", FILE_WRITE);
    log_file.println("latitude,longitude,hour,minute,second,day,month,year,speed (in mph),CO (in ppm),CO2 (in ppm),O3 (in ppb),NO (in ppb),tempurature (in celsius),wind speed (in meters per second)");
    log_file.close();
  }
  #endif
}

void loop() {

  delay(500);

  // update GPS
  while(gps_port.available()) gps.encode(gps_port.read());

  //read from sensors
  for(unsigned int i=0; i < 6; ++i) sensor_array[i] = analogRead(analog[i]);

  print_log();
}
