#include <Adafruit_GPS.h>
#include <SoftwareSerial.h>
Adafruit_GPS GPS(&Serial1);
#define GPSECHO  true
boolean usingInterrupt = false;

void setup()  
{ 
  while (!Serial);
  Serial.begin(115200);
  Serial.println("Adafruit GPS logging dump test!");
  GPS.begin(9600);
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_OFF);

  while (Serial1.available())
     Serial1.read();

  delay(1000);
  GPS.sendCommand("$PMTK622,1*29");
  Serial.println("----------------------------------------------------");
}


void loop()
{  
  if (Serial1.available()) {
    char c = Serial1.read();
      if (c) Serial.print(c);
  }
}

