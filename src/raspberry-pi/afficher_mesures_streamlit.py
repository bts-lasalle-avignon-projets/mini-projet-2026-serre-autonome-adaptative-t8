# --- Gestion de la serre autonome adaptative - Raspberry Pi - 2026 ---
# -- Affichage des mesures reçues depuis le port série avec Streamlit --
import sys
import os
import serial
import threading
from dotenv import load_dotenv
import streamlit as st
import numpy as np
import pandas as pd

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
# Index des champs dans la trame de mesures
CHAMP_MESURE_PAR = 0
CHAMP_MESURE_LUMINOSITE = 1
CHAMP_MESURE_TEMPERATURE_AIR = 2
CHAMP_MESURE_HUMIDITE_AIR = 3
CHAMP_MESURE_HUMIDITE_SOL = 4
CHAMP_MESURE_CONDUCTIVITE_SOL = 5

# --- Fonction de réception des mesures depuis le port série ---
def receptionner_mesures():
    while True:
        try:
            donnees_recues = port_serie.readline()
            if donnees_recues:
                trame = donnees_recues.decode('ascii', errors='ignore').strip()
                #print(f"Trame reçue : '{trame}\\r\\n'")
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
                    # On a reçu une trame valide
                    yield trame
        except KeyboardInterrupt:
            port_serie.close()
            print(f"Port '{nom_port_serie}' fermé")
            break
        except Exception as e:
            print(f"Erreur réception : {e}")
            break

# --- Fonction d'extraction des mesures depuis une trame ---
@st.cache_data
def extraire_mesures(trame):
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
        # Affichage des mesures reçues dans la console
        champs_protocole = {"Rayonnement PAR": 0, "Éclairement lumineux": 1, "Température de l'air": 2, "Humidité de l'air": 3, "Humidité du sol": 4, "Conductivité du sol": 5}
        unites_champs = {0: "μmol.m^-2.s^-1", 1: "lux", 2: "°C", 3: "%", 4: "%", 5: "μS/cm"}
        print("Mesures reçues :")
        for key, index in champs_protocole.items():
            if champs[index] != '':
                print(f"  {key} : {int(champs[index])} {unites_champs[index]}")
        # Extraction des mesures
        if champs[CHAMP_MESURE_PAR] == '':
            mesure_par = None
        else:
            mesure_par = int(champs[CHAMP_MESURE_PAR])
        if champs[CHAMP_MESURE_LUMINOSITE] == '':
            mesure_luminosite = None
        else:
            mesure_luminosite = int(champs[CHAMP_MESURE_LUMINOSITE])
        if champs[CHAMP_MESURE_TEMPERATURE_AIR] == '':
            mesure_remperature_air = None
        else:
            mesure_remperature_air = int(champs[CHAMP_MESURE_TEMPERATURE_AIR])
        if champs[CHAMP_MESURE_HUMIDITE_AIR] == '':
            mesure_humidite_air = None
        else:
            mesure_humidite_air = int(champs[CHAMP_MESURE_HUMIDITE_AIR])
        if champs[CHAMP_MESURE_HUMIDITE_SOL] == '':
            mesure_humidite_sol = None
        else:
            mesure_humidite_sol = int(champs[CHAMP_MESURE_HUMIDITE_SOL])
        if champs[CHAMP_MESURE_CONDUCTIVITE_SOL] == '':
            mesure_conductivite_sol = None
        else:
            mesure_conductivite_sol = int(champs[CHAMP_MESURE_CONDUCTIVITE_SOL])
        return mesure_par, mesure_luminosite, mesure_remperature_air, mesure_humidite_air, mesure_humidite_sol, mesure_conductivite_sol
    except ValueError:
        print("Erreur : valeur numérique invalide dans la trame !")

def fermer_port_serie():
    if port_serie.is_open:
        port_serie.close()
        print(f"Port '{nom_port_serie}' fermé")

# -- Affichage des mesures reçues depuis le port série avec Streamlit --
st.set_page_config(layout="wide")
st.title('Mesures d\'une serre')
etat_reception_mesures = st.empty()
etat_reception_mesures.text('Réception des mesures en cours...')

colonnes = {"Rayonnement PAR": 0, "Éclairement lumineux": 1, "Température de l'air": 2, "Humidité de l'air": 3, "Humidité du sol": 4, "Conductivité du sol": 5}

# Initialisation des graphiques et tableaux Streamlit
# cf. https://docs.streamlit.io/develop/quick-reference/cheat-sheet
st.write("### Graphique des mesures reçues")
graphique = st.line_chart(None)
st.write("### Tableau des mesures reçues")
tableau = st.dataframe(None)

# Affiche les mesures des trames reçues
for trame in receptionner_mesures():
    if trame:
        st.toast(f"Trame reçue : '{trame}\\r\\n' ! Mise à jour des graphiques ...")
        mesure_par, mesure_luminosite, mesure_remperature_air, mesure_humidite_air, mesure_humidite_sol, mesure_conductivite_sol = extraire_mesures(trame)
        mesures = np.array([[mesure_par,mesure_luminosite,mesure_remperature_air,mesure_humidite_air,mesure_humidite_sol,mesure_conductivite_sol]])
        donnees = pd.DataFrame(mesures,
                    columns=['%s' % key for key, index in colonnes.items()])
        graphique.add_rows(donnees)
        tableau.add_rows(donnees)

# Fermer le port série
fermer_port_serie()
etat_reception_mesures.text('Arrêt de la réception des mesures.')