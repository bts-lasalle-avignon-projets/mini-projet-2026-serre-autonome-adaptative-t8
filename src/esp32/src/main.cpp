#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_TSL2561_U.h>

//#define MODE_SIMULATION

// Le port série 0 : moniteur
#define DEBIT_PORT_SERIE_0 115200
// Le port série 1 : communication avec le Raspberry Pi
#define DEBIT_PORT_SERIE_1 9600

// Le port série 1 : communication avec le Raspberry Pi
#define FORMAT_PORT_SERIE_1    SERIAL_8N1 // 8 bits, pas de parité et 1 bit de stop
#define BROCHE_PORT_SERIE_1_RX 4          // réaffectation de la broche RX du port série 1
#define BROCHE_PORT_SERIE_1_TX 5          // réaffectation de la broche TX du port série 1

#ifdef MODE_SIMULATION
#define PERIODE_MESURE 30000 // 30 secondes exprimées en ms
#else
#define PERIODE_MESURE 30000 // 30 secondes exprimées en ms
// À définir en mode réel
//#define PERIODE_MESURE 600000 // 10 minutes exprimées en ms
#endif

// Protocole de communication série
#define DELIMITER_DEBUT_TRAME      '$'
#define DELIMITER_FIN_TRAME        "\r\n"
#define DELIMITER_FIN_TRAME_1      '\r'
#define DELIMITER_FIN_TRAME_2      '\n'
#define DELIMITER_FIN_CHAMP        ';'
#define NB_CHAMPS_TRAME_PARAMETRES 12

#define ON  HIGH
#define OFF LOW

// Pour le scan I2C
#define ADRESSE_I2C_DEBUT 0x01
#define ADRESSE_I2C_FIN   0x7F

/*
Documentation I2C address TSL2561
TSL2561_ADDR_LOW   = 0x29   ///< Default address (pin pulled low)
TSL2561_ADDR_FLOAT = 0x39   ///< Default address (pin left floating)
TSL2561_ADDR_HIGH  = 0x49   ///< Default address (pin pulled high)
*/

// Capteurs
Adafruit_TSL2561_Unified capteurLuminosite = Adafruit_TSL2561_Unified(TSL2561_ADDR_FLOAT, 12345);

// Actionneurs (au moins les Leds)

struct ParametresPlante
{
    int max_light_mmol;
    int min_light_mmol;
    int max_light_lux;
    int min_light_lux;
    int max_temp;
    int min_temp;
    int max_env_humid;
    int min_env_humid;
    int max_soil_moist;
    int min_soil_moist;
    int max_soil_ec;
    int min_soil_ec;
};

struct MesuresCapteurs
{
    int      light_mmol;
    uint32_t light_lux;
    int      temp;
    int      env_humid;
    int      soil_moist;
    int      soil_ec;
};

// Variables globales
ParametresPlante parametresPlante = {
    6000, 3600, 150, 100, 32, 8, 80, 30, 60, 15, 2000, 350
}; // par défaut
MesuresCapteurs mesuresCapteurs = { 0, 0, 0, 0, 0, 0 };

// Fonctions
void receptionnerParametresPlante()
{
    // TODO
#ifdef DEBUG
    // Afficher les paramètres de la structure parametresPlante
    Serial.println("Paramètres de la plante reçus :");
    Serial.println("  max_light_mmol : " + String(parametresPlante.max_light_mmol) + " µmol/m²/s");
    Serial.println("  min_light_mmol : " + String(parametresPlante.min_light_mmol) + " µmol/m²/s");
    Serial.println("  max_light_lux : " + String(parametresPlante.max_light_lux) + " lx");
    Serial.println("  min_light_lux : " + String(parametresPlante.min_light_lux) + " lx");
    Serial.println("  max_temp : " + String(parametresPlante.max_temp) + " °C");
    Serial.println("  min_temp : " + String(parametresPlante.min_temp) + " °C");
    Serial.println("  max_env_humid : " + String(parametresPlante.max_env_humid) + " %");
    Serial.println("  min_env_humid : " + String(parametresPlante.min_env_humid) + " %");
    Serial.println("  max_soil_moist : " + String(parametresPlante.max_soil_moist) + " %");
    Serial.println("  min_soil_moist : " + String(parametresPlante.min_soil_moist) + " %");
    Serial.println("  max_soil_ec : " + String(parametresPlante.max_soil_ec) + " µS/cm");
    Serial.println("  min_soil_ec : " + String(parametresPlante.min_soil_ec) + " µS/cm");
#endif
}

void envoyerTrameMesures()
{
#ifdef DEBUG
    // Afficher les mesures des capteurs
    Serial.println("Mesures :");
    Serial.println("  light_mmol : " + String(mesuresCapteurs.light_mmol) + " µmol/m²/s");
    Serial.println("  light_lux : " + String(mesuresCapteurs.light_lux) + " lx");
    Serial.println("  temp : " + String(mesuresCapteurs.temp) + " °C");
    Serial.println("  env_humid : " + String(mesuresCapteurs.env_humid) + " %");
    Serial.println("  soil_moist : " + String(mesuresCapteurs.soil_moist) + " %");
    Serial.println("  soil_ec : " + String(mesuresCapteurs.soil_ec) + " µS/cm");
#endif
    // TODO
}

void commanderActionneurs()
{
}

void scanI2C()
{
}

void configurerTSL2561(bool                     autoRange = true,
                       tsl2561Gain_t            gain      = TSL2561_GAIN_16X,
                       tsl2561IntegrationTime_t time      = TSL2561_INTEGRATIONTIME_402MS)
{
    /* Auto-gain ... switches automatically between 1x and 16x */
    capteurLuminosite.enableAutoRange(autoRange);
    Serial.print("  Gain :         ");
    if(autoRange)
    {
        Serial.println("Auto");
    }
    else
    {
        capteurLuminosite.setGain(gain);
        /** TSL2561 offers 2 gain settings */
        switch(gain)
        {
            case TSL2561_GAIN_1X:
                Serial.println("No");
                break;
            case TSL2561_GAIN_16X:
                Serial.println("16x");
                break;
            default:
                break;
        }

        Serial.println("16x");
    }

    capteurLuminosite.setIntegrationTime(time);
    Serial.print("  Timing :       ");
    /** Three options for how long to integrate readings for */
    switch(time)
    {
        case TSL2561_INTEGRATIONTIME_13MS:
            /* fast but low resolution */
            Serial.println("13,7 ms");
            break;
        case TSL2561_INTEGRATIONTIME_101MS:
            /* medium resolution and speed   */
            Serial.println("101 ms");
            break;
        case TSL2561_INTEGRATIONTIME_402MS:
            /* 16-bit data but slowest conversions */
            Serial.println("402 ms");
        default:
            break;
    }
    Serial.println("");
}

void setup()
{
    // Initialise le port série 0
    Serial.begin(DEBIT_PORT_SERIE_0);

    Serial.println("Gestion de la serre autonome adaptative - ESP32 - 2026");

    // Initialise le port série 1 en précisant le débit, le format et les broches
    Serial1.begin(DEBIT_PORT_SERIE_1,
                  FORMAT_PORT_SERIE_1,
                  BROCHE_PORT_SERIE_1_RX,
                  BROCHE_PORT_SERIE_1_TX);

    // Définit la fonction de rappel appelée lors de la réception de données sur le port série 1

#ifdef DEBUG
    Serial.println("Initialisation des ports series terminee !");
#endif

#ifdef DEBUG
    Serial.println("Scan I2C en cours ...");
#endif
    // Initialise le bus I2C
    Wire.begin();
    // Scanne le bus I2C pour détecter les circuits présents
    scanI2C();

#ifdef MODE_SIMULATION
    Serial.println("Mode simulation active : mesures et envoi toutes les " +
                   String(PERIODE_MESURE / 1000) + " secondes");
    // Initialise le générateur pseudo-aléatoire
    randomSeed(analogRead(0));
#else

#ifdef DEBUG
    Serial.println("Initialisation des capteurs terminee !");
#endif

    // Initialise les broches des actionneurs

#ifdef DEBUG
    Serial.println("Initialisation des actionneurs terminee !");
#endif

#endif
}

void loop()
{
}
