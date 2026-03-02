#include <Arduino.h>
#include <Wire.h>

//#define DEBUG

#define VITESSE_PORT_SERIE 9600
#define ADRESSE_I2C_DEBUT  0x01
#define ADRESSE_I2C_FIN    0x7F

void scanI2C()
{
}

void setup()
{
    Serial.begin(VITESSE_PORT_SERIE);

    Wire.begin();
}

void loop()
{
    while(true)
    {
        scanI2C();
        delay(1000);
    }
}
