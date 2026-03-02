#include <Wire.h>
//#include <Adafruit_Sensor.h>
#include <Adafruit_TSL2561_U.h>

//#define DEBUG

#define ATTENTE            500  // en ms
#define PERIODE            5000 // en ms
#define VITESSE_PORT_SERIE 9600

// Pour le scan I2C
#define ADRESSE_I2C_DEBUT 0x01
#define ADRESSE_I2C_FIN   0x7F

/*
I2C address TSL2561
TSL2561_ADDR_LOW   = 0x29   ///< Default address (pin pulled low)
TSL2561_ADDR_FLOAT = 0x39   ///< Default address (pin left floating)
TSL2561_ADDR_HIGH  = 0x49   ///< Default address (pin pulled high)
*/

Adafruit_TSL2561_Unified capteurLuminosite = Adafruit_TSL2561_Unified(TSL2561_ADDR_FLOAT, 12345);
/*
Default configuration
AutoGain        = false;
IntegrationTime = TSL2561_INTEGRATIONTIME_13MS;
Gain            = TSL2561_GAIN_1X;
*/

uint16_t luminosite = 0;
uint16_t infraRouge = 0;
uint32_t lux        = 0;

void scanI2C()
{
}

void afficherInformations()
{
    sensor_t sensor;
    capteurLuminosite.getSensor(&sensor);
    Serial.println("------------------------------------");
    Serial.print("Sensor:       ");
    Serial.println(sensor.name);
    Serial.print("Driver Ver:   ");
    Serial.println(sensor.version);
    Serial.print("Unique ID:    ");
    Serial.println(sensor.sensor_id);
    Serial.print("Max Value:    ");
    Serial.print(sensor.max_value);
    Serial.println(" lux");
    Serial.print("Min Value:    ");
    Serial.print(sensor.min_value);
    Serial.println(" lux");
    Serial.print("Resolution:   ");
    Serial.print(sensor.resolution);
    Serial.println(" lux");
    Serial.println("------------------------------------");
    Serial.println("");
    delay(ATTENTE);
}

void configurerCapteur(bool                     autoRange = true,
                       tsl2561Gain_t            gain      = TSL2561_GAIN_16X,
                       tsl2561IntegrationTime_t time      = TSL2561_INTEGRATIONTIME_402MS)
{
    Serial.println("------------------------------------");
    /* Auto-gain ... switches automatically between 1x and 16x */
    capteurLuminosite.enableAutoRange(autoRange);
    Serial.print("Gain:         ");
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
    Serial.print("Timing:       ");
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
    Serial.println("------------------------------------");
    Serial.println("");
}

void afficherLuminosite(uint32_t lux)
{
    Serial.print("Luminosité : ");
    Serial.print(lux);
    Serial.println(" lx");
}

void afficherValeurs(float lux, uint32_t channel_0, uint32_t channel_1)
{
    if(lux)
    {
        // Format CSV
        String message =
          String(lux, 0) + ";0x" + String(channel_0, HEX) + ";0x" + String(channel_1, HEX);
        Serial.println(message);
    }
    else
    {
#ifdef DEBUG
        Serial.println("Hors limites !");
#endif
    }
}

void setup()
{
    Serial.begin(VITESSE_PORT_SERIE);

    // Wire.begin();

    if(!capteurLuminosite.begin())
    {
        Serial.println("TSL2561 non détecté ... verifie le cablage ou l'adresse I2C !");
        scanI2C();
        while(true)
            ;
    }

    afficherInformations();
    configurerCapteur();

    // Format CSV
    Serial.println("lx;CH0;CH1");
}

void loop()
{
    // TODO : mesurer périodiquement la luminosité en lux et l'afficher
}
