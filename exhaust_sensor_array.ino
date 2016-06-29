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
#define print   Serial.print
#define println Serial.println
#else
#define print   log_file.print
#define println log_file.println
#endif

int sensor_array[6];

void print_log() {

  File log_file = SD.open("log.csv", FILE_WRITE);

  print(gps.location.lat(), 6);
  print(',');
  print(gps.location.lng(), 6);
  print(',');
  print(gps.time.hour());
  print(',');
  print(gps.time.minute());
  print(',');
  print(gps.time.second());
  print(',');
  print(gps.date.day());
  print(',');
  print(gps.date.month());
  print(',');
  print(gps.date.year());
  print(',');
  print(gps.speed.mph());
  print(',');
  print(map(CO,  0, 1023, 20,  2000)); //ppm
  print(',');
  print(map(CO2, 0, 1023,  0, 10000)); //ppm
  print(',');
  print(map(O3,  0, 1023, 10,  2000)); //ppb
  print(',');
  print(map(NO,  0, 1023, 50, 10000)); //ppb
  print(',');
  print(map(TEMP, 0, 1023 , -40, 125)); // celsius
  print(',');
  print(map(WIND, 0, 1023 , 0, 100)); // meter per second
  println();

  log_file.close();
}

void setup() {

  Serial.begin(9600);
  gps_port.begin(GPS_BAUD_RATE); //GPS Setup

  //SD card start
  pinMode(SD_PIN, OUTPUT);
  digitalWrite(SD_PIN, HIGH);
  SD.begin(SD_PIN);
//  if( !SD.begin(SD_PIN) ) Serial.println("ERROR: SD failure");
  
  //print header
  if(!SD.exsists("log.csv")) {
    File log_file = SD.open("log.csv", FILE_WRITE);
    log_file.println("latitude,longitude,hour,minute,second,day,month,year,speed (in mph),CO (in ppm),CO2 (in ppm),O3 (in ppb),NO (in ppb),tempurature (in celsius),wind speed (in meters per second)");
    log_file.close();
  }
}

void loop() {

  delay(500);

  // update GPS
  while(gps_port.available()) gps.encode(gps_port.read());

  //read from sensors
  for(unsigned int i=0; i < 6; ++i) sensor_array[i] = analogRead(i);

  print_log();
}
