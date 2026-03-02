# --- Réception des mesures par le port série - Serre autonome adaptative - Raspberry Pi - 2026 ---
import sys
import os
import serial
import threading
from dotenv import load_dotenv

print(f"Réception des mesures par le port série - Raspberry Pi - 2026")

# --- Chargement des variables du fichier .env ---
load_dotenv()

# --- Configuration du port série ---
nom_port_serie = os.getenv("NOM_PORT", "/dev/ttyUSB0")
debit = int(os.getenv("DEBIT", "9600"))
print(f"Port '{nom_port_serie}' ({debit} bps)")
try:
    # Ouvrir le port série
    port_serie = serial.Serial(nom_port_serie, debit, timeout=1)
    print(f"Port '{nom_port_serie}' ouvert")
except serial.SerialException as e:
    print(f"Erreur : {e}")
except PermissionError:
    print("Accès refusé !")
except FileNotFoundError:
    print("Port non trouvé !")

# --- Protocoles de communication ---
DELIMITER_DEBUT_TRAME =     '$'
DELIMITER_FIN_TRAME   =     "\r\n"
DELIMITER_FIN_TRAME_1 =     '\r'
DELIMITER_FIN_TRAME_2 =     '\n'
DELIMITER_FIN_CHAMP   =     ';'
DELIMITER_NB_CHAMPS_TRAME_MESURES = 6

# --- Fonction de réception des mesures depuis le port série ---
def receptionner_mesures():
    while True:
        try:
            donnees_recues = port_serie.readline()
            if donnees_recues:
                trame = donnees_recues.decode('ascii', errors='ignore').strip()
                # Vérifie que la trame commence par le bon délimiteur
                if trame and trame[0] != DELIMITER_DEBUT_TRAME:
                    print("Erreur : trame reçue invalide (délimiteur de début incorrect ou manquant) !")
                    continue
                # Vérifie que le nombre de champs est correct
                nbChamps = trame.count(DELIMITER_FIN_CHAMP)
                if nbChamps != DELIMITER_NB_CHAMPS_TRAME_MESURES:
                    print("Erreur : trame reçue invalide (nombre de champs incorrect) !")
                    continue
                if trame:
                    #print(f"Trame reçue : '{trame}'")
                    yield trame
        except KeyboardInterrupt:
            port_serie.close()
            print(f"Port '{nom_port_serie}' fermé")
            break
        except Exception as e:
            print(f"Erreur réception : {e}")
            break

def fermer_port_serie():
    if port_serie.is_open:
        port_serie.close()
        print(f"Port '{nom_port_serie}' fermé")

# --- Fonction d'affichage des mesures d'une trame ---
def afficher_mesures(trame):
    # Exemple de trame : $;15000;28;56;60;;\r\n
    print(f"Trame reçue : '{trame}\\r\\n'")
    champs = trame.strip(DELIMITER_DEBUT_TRAME).split(DELIMITER_FIN_CHAMP)
    nbChamps = trame.count(DELIMITER_FIN_CHAMP)
    # Vérifie que le nombre de champs est correct
    nbChamps = trame.count(DELIMITER_FIN_CHAMP)
    if nbChamps != DELIMITER_NB_CHAMPS_TRAME_MESURES:
        print("Erreur : trame reçue invalide (nombre de champs incorrect) !")
        return
    try:
        champs_protocole = {"Rayonnement PAR": 0, "Éclairement lumineux": 1, "Température de l'air": 2, "Humidité de l'air": 3, "Humidité du sol": 4, "Conductivité du sol": 5}
        unites_champs = {0: "μmol.m^-2.s^-1", 1: "lux", 2: "°C", 3: "%", 4: "%", 5: "μS/cm"}
        print("Mesures reçues :")
        for key, index in champs_protocole.items():
            if champs[index] != '':
                print(f"  {key} : {int(champs[index])} {unites_champs[index]}")
    except ValueError:
        print("Erreur : valeur numérique invalide dans la trame !")

# --- Lancement de la réception des mesures par le port série ---
if __name__ == '__main__':
    print("CTRL+C pour quitter")

    # Affiche les trames reçues
    for trame in receptionner_mesures():
        if trame:
            afficher_mesures(trame)

    # Fermer le port série
    fermer_port_serie()
    print("Arrêt de l'application")
