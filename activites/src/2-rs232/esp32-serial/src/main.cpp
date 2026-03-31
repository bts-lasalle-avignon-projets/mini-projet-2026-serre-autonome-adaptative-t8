#include <Arduino.h>

// Le port série 0 : moniteur
#define DEBIT_PORT_SERIE_0 115200
#define DEBIT_PORT_SERIE_1 9600
#define DEBIT_PORT_SERIE_2 9600

// Le port série 1
#define FORMAT_PORT_SERIE_1    SERIAL_8N1 // 8 bits, pas de parité et 1 bit de stop
#define BROCHE_PORT_SERIE_1_RX 4          // réaffectation de la broche RX du port série 1
#define BROCHE_PORT_SERIE_1_TX 5          // réaffectation de la broche TX du port série 1

// Le port série 2
#define FORMAT_PORT_SERIE_2    SERIAL_8N1 // 8 bits, pas de parité et 1 bit de stop
#define BROCHE_PORT_SERIE_2_RX 16
#define BROCHE_PORT_SERIE_2_TX 17

void setup()
{
    // Initialise le port série 0
    Serial.begin(DEBIT_PORT_SERIE_0);

    // Initialise le port série 1 en précisant le débit, le format et les broches
    Serial1.begin(DEBIT_PORT_SERIE_1,
                  FORMAT_PORT_SERIE_1,
                  BROCHE_PORT_SERIE_1_RX,
                  BROCHE_PORT_SERIE_1_TX);

    // Initialise le port série 2 en précisant le débit, le format et les broches
    Serial2.begin(DEBIT_PORT_SERIE_2,
                  FORMAT_PORT_SERIE_2,
                  BROCHE_PORT_SERIE_2_RX,
                  BROCHE_PORT_SERIE_2_TX);
#ifdef DEBUG
    Serial.println("Initialisation des ports series terminee !");
#endif
}

// Mode echo
void loop()
{
    while(Serial1.available() > 0)
    {
        uint8_t octetLu = Serial1.read();
        Serial1.write(octetLu);
#ifdef DEBUG
        Serial.print("[port 1] Octet lu : ");
        Serial.print(char(octetLu));
        Serial.print(" ");
        Serial.print(octetLu);
        Serial.print(" 0x");
        Serial.println(octetLu, HEX);
#endif
    }
}
