#include <Arduino.h>
#include <Wire.h>

//#define DEBUG

#define VITESSE_PORT_SERIE 9600
#define ADRESSE_I2C_DEBUT  0x01
#define ADRESSE_I2C_FIN    0x7F

void scanI2C()
{
    Serial.println("Scan du bus I2C en cours");

    for(int adresse = ADRESSE_I2C_DEBUT; adresse <= ADRESSE_I2C_FIN; adresse++)
    {
        Wire.beginTransmission(adresse);
        uint8_t erreur = Wire.endTransmission();

        if(erreur == 0)
        {
            Serial.printf("0x%02X ok\n", adresse);
        }
    }
}

void setup()
{
    Serial.begin(VITESSE_PORT_SERIE);

    Wire.begin();
}

void loop()
{
    scanI2C();
    delay(1000);
}
