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


// Définir la broche de la LED (GPIO 2 )
#define BROCHE_LED 2


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
MesuresCapteurs mesuresCapteurs      = { 0, 0, 0, 0, 0, 0 };
unsigned long   tempsPrecedentMesure = 0;


// Fonctions
void receptionnerParametresPlante()
{
   if(Serial1.available())
   {
       String trame = Serial1.readStringUntil('\n');


       Serial.print("Trame brute reçue : ");
       Serial.println(trame);


       if(!trame.startsWith("$"))
       {
           Serial.println("Erreur : pas de $ au début");
           return;
       }


       trame.remove(0, 1);


       int champs[12] = { 0 };
       int indexChamp = 0;
       int pos        = 0;


       while((pos = trame.indexOf(';')) != -1 && indexChamp < 12)
       {
           String valeurStr   = trame.substring(0, pos);
           champs[indexChamp] = (valeurStr == "") ? 0 : valeurStr.toInt();
           trame.remove(0, pos + 1);
           indexChamp++;
       }


       if(indexChamp == 12)
       {
           parametresPlante.max_light_mmol = champs[0];
           parametresPlante.min_light_mmol = champs[1];
           parametresPlante.max_light_lux  = champs[2];
           parametresPlante.min_light_lux  = champs[3];
           parametresPlante.max_temp       = champs[4];
           parametresPlante.min_temp       = champs[5];
           parametresPlante.max_env_humid  = champs[6];
           parametresPlante.min_env_humid  = champs[7];
           parametresPlante.max_soil_moist = champs[8];
           parametresPlante.min_soil_moist = champs[9];
           parametresPlante.max_soil_ec    = champs[10];
           parametresPlante.min_soil_ec    = champs[11];


           Serial.print("min_light_lux mis à jour : ");
           Serial.println(parametresPlante.min_light_lux);
       }
       else
       {
           Serial.print("Erreur : nombre de champs incorrect (");
           Serial.print(indexChamp);
           Serial.println(")");
       }
   }


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
   // Format : $;light_mmol;light_lux;temp;env_humid;soil_moist;soil_ec;;\r\n
   String trame = String(DELIMITER_DEBUT_TRAME) + String(DELIMITER_FIN_CHAMP);
   trame += String(mesuresCapteurs.light_mmol) + String(DELIMITER_FIN_CHAMP);
   trame += String(mesuresCapteurs.light_lux) + String(DELIMITER_FIN_CHAMP);
   trame += String(mesuresCapteurs.temp) + String(DELIMITER_FIN_CHAMP);
   trame += String(mesuresCapteurs.env_humid) + String(DELIMITER_FIN_CHAMP);
   trame += String(mesuresCapteurs.soil_moist) + String(DELIMITER_FIN_CHAMP);
   trame += String(mesuresCapteurs.soil_ec) + String(DELIMITER_FIN_CHAMP);
   trame += String(DELIMITER_FIN_CHAMP); // Champ vide final
   trame += String(DELIMITER_FIN_TRAME);


   Serial1.print(trame);


#ifdef DEBUG
   Serial.print("Trame envoyée au RPi : ");
   Serial.print(trame);
#endif
}


void commanderActionneurs()
{
   // Si la luminosité actuelle est inférieure au seuil minimum de la plante
   if(mesuresCapteurs.light_lux < parametresPlante.min_light_lux)
   {
       digitalWrite(BROCHE_LED, ON); // Allumer l'éclairage
   }
   else
   {
       digitalWrite(BROCHE_LED, OFF); // Éteindre
   }
}


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


void lireLuminosite()
{
   sensors_event_t event;
   capteurLuminosite.getEvent(&event);  
   mesuresCapteurs.light_lux  = (event.light) ? event.light : 0;

   if (event.light)
    {
        mesuresCapteurs.light_lux = (uint32_t)event.light;
        Serial.println(mesuresCapteurs.light_lux);
    }
    else
    {
        Serial.println("Erreur capteur TSL2561");
    }
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
   Serial1.onReceive(receptionnerParametresPlante);


   pinMode(BROCHE_LED, OUTPUT);


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


   // Initialisation réelle du capteur de luminosité
   if(!capteurLuminosite.begin())
   {
       Serial.println("Erreur : Capteur TSL2561 non détecté !");
   }
   else
   {
       configurerTSL2561(); // Appel de la fonction simple de config
       Serial.println("Capteur TSL2561 prêt.");
   }


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
   unsigned long tempsActuel = millis();

   // Envoi périodique des mesures
   if(tempsActuel - tempsPrecedentMesure >= PERIODE_MESURE)
   {
       tempsPrecedentMesure = tempsActuel;
       envoyerTrameMesures();
       commanderActionneurs();
       lireLuminosite();

   }
}
