# --- Gestion de la serre autonome adaptative - Raspberry Pi - 2026 ---
# -- Application Web avec Flask pour interagir avec l'API Open Plantbook --
import sys
import os
import json
import requests
import serial
from dotenv import load_dotenv
from flask import Flask, jsonify, request, abort, render_template

print(f"Gestion de la serre autonome adaptative - Raspberry Pi - 2026")

# --- Chargement des variables du fichier .env ---
load_dotenv()

# --- Configuration de l'API Open Plantbook ---
API_URL = os.getenv("API_URL", "https://open.plantbook.io/api/v1")
client_id = os.getenv("CLIENT_ID")
secret = os.getenv("SECRET")
token = os.getenv("TOKEN")

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

# --- Fonctions de gestion de l'API Open Plantbook ---
def get_plantbook_token(client_id, secret):
    url =  f"{API_URL}/token/"
    data = {
        'grant_type': 'client_credentials',
        'client_id': client_id,
        'client_secret': secret
    }
    try:
        resultats = requests.post(url, data = data)
        resultats.raise_for_status()
    except requests.exceptions.HTTPError as erreur:
        print("Erreur lors de l'obtention du jeton depuis {}: {}".format(url, erreur))
        return None
    token_oauth2 = resultats.json().get('access_token')
    token_type = resultats.json().get('token_type')
    return token_type,token_oauth2

def rechercher_plante(nom_plante, token_type, token):
    url = "{}/plant/search?limit=10&alias={}".format(API_URL, nom_plante)
    headers = {"Authorization": "{} {}".format(token_type, token)}
    try:
        resultats = requests.get(url, headers=headers)
        resultats.raise_for_status()
    except requests.exceptions.HTTPError as erreur:
        print("Erreur lors de la recherche depuis {}: {}".format(url, erreur))
        return None
    reponses = resultats.json()
    print("{} plante(s) trouvée(s)".format(len(reponses['results'])))
    # retourner le pid de la première plante trouvée
    if len(reponses['results']) > 0:
        print(json.dumps(reponses, indent=4))
        return reponses['results']
    return None

def obtenir_details_plante(pid, token_type, token):
    # TODO
    url = "{}/plant/detail/{}/".format(API_URL, pid.replace(' ', '%20'))
    headers = {"Authorization": "{} {}".format(token_type, token)}

    try:
        resultats = requests.get(url, headers=headers)
        resultats.raise_for_status()
        details = resultats.json()

        print("\nDétails de la plante({}):".format(pid))
        print(json.dumps(details, indent=4))
        return details

    except requests.exceptions.HTTPError as erreur:
        print("Erreur lors de la récupération des détails :{}".format(erreur))
        return None

# --- Configuration de Flask ---
def create_app():
    app = Flask(__name__)

    return app

app = create_app()

# --- Création des routes Flask ---
# Page d'accueil pour rechercher une plante
@app.route('/')
def index():
    # Affiche la page d'accueil
    return render_template('index.html')

# Page pour sélectionner une plante recherchée
@app.route('/search', methods=['POST'])
def rechercher_nom_plante():
    nom_plante = request.form['nom_plante']
    token_type, token = get_plantbook_token(client_id, secret)
    plantes = rechercher_plante(nom_plante, token_type, token)
    if plantes:
        # Affiche les résultats de la recherche
        return render_template('plantes.html', plantes=plantes)
    else:
        abort(404, description="Plante non trouvée !")

# Page pour afficher les détails de la plante sélectionnée
@app.route('/select', methods=['POST'])
def selectionner_plante():
    pid = request.form['plante']
    token_type, token = get_plantbook_token(client_id, secret)
    details = obtenir_details_plante(pid, token_type, token)
    if details:
        # Affiche les détails de la plante
        return render_template('details.html', details=details)
    else:
        abort(404, description="Plante non trouvée !")

# Pour transférer les paramètres sur le port série
@app.route('/upload', methods=['POST'])
def transferer_parametres_plante():
    pid = request.form['pid']
    token_type, token = get_plantbook_token(client_id, secret)
    details = obtenir_details_plante(pid, token_type, token)
    if details:
        # Transférer les paramètres sur le port série dans une trame au format $${valeur_parametre};\r\n
        trame_parametres = "$"
        for key, value in details.items():
            if key not in ["pid","display_pid","alias","category","image_url","common_names"]:
                trame_parametres += f"{value};"
        trame_parametres += "\r\n"
        if port_serie.is_open:
            print(f"Envoi trame : '{trame_parametres.strip()}'")
            print(f"Nb d'octets à envoyer : {len(trame_parametres.encode('ascii'))}")
            # TODO : envoyer la trame sur le port série et afficher le nombre d'octets envoyés
            nb_octets = port_serie.write(trame_parametres.encode('ascii'))
            print(f"Nb octets envoyés : {nb_octets}")
            # Affiche la trame envoyée
            return render_template('transfert.html', transfert={"trame": trame_parametres.strip(), "display_pid": details.get("display_pid", pid)})
        else:
            abort(404, description="Port non disponible !")
    else:
        abort(404, description="Plante non trouvée !")

# --- Lancement de l'application Flask ---
if __name__ == '__main__':
    # Lance l'application en mode debug (rechargement automatique)
    app.run(debug=True)

    # Fermer le port série
    port_serie.close()
    print(f"Port '{nom_port_serie}' fermé")
    print("Arrêt de l'application")
