#include <Adafruit_GPS.h>
#include <SoftwareSerial.h>
Adafruit_GPS GPS(&Serial1);
#define GPSECHO  true
boolean usingInterrupt = false;

void setup()  
{    
  Serial.begin(115200);
  Serial.println("Adafruit Flora GPS logging");
  GPS.begin(9600);
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);
  useInterrupt(true);
  delay(500);
  while (true) {
    Serial.print("Starting logging....");
    if (GPS.LOCUS_StartLogger()) {
      Serial.println(" STARTED!");
      break;
    } else {
      Serial.println(" no response :(");
    }
  }
}

void loop()
{
  pinMode(7, OUTPUT);
  digitalWrite(7, HIGH);
  delay(200);
  digitalWrite(7, LOW);
  delay(200);
}

SIGNAL(TIMER0_COMPA_vect) {
  char c = GPS.read();
  if (GPSECHO)
    if (c) Serial.print(c);  
}

void useInterrupt(boolean v) {
  if (v) {
    OCR0A = 0xAF;
    TIMSK0 |= _BV(OCIE0A);
    usingInterrupt = true;
  } else {
    TIMSK0 &= ~_BV(OCIE0A);
    usingInterrupt = false;
  }
}
