import sys
import os
import json
import requests
from dotenv import load_dotenv

# TODO: ajouter un fichier .env avec les variables d'environnement suivantes API_URL, CLIENT_ID, SECRET, TOKEN.

load_dotenv()
API_URL = os.getenv("API_URL", "https://open.plantbook.io/api/v1")
client_id = os.getenv("CLIENT_ID")
secret = os.getenv("SECRET")
token = os.getenv("TOKEN")
HEADERS = {"Authorization": f"token {token}"}

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
        return reponses['results'][0]['pid']
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

if __name__ == "__main__":
    if len(sys.argv) < 2:
        # nom_plante = pid ou alias
        print("Usage: {} <nom_plante>".format(sys.argv[0]))
        sys.exit(1)
    nom_plante = sys.argv[1]
    print("Recherche de la plante '{}' dans Open Plantbook ...".format(nom_plante))
    # OAuth2 Client Credentials (token temporaire)
    #token_type,token_oauth2 = get_plantbook_token(client_id, secret)
    #pid = rechercher_plante(nom_plante, token_type, token_oauth2)
    #obtenir_details_plante(pid, token_type, token_oauth2)
    # API-key (token permanent)
    pid = rechercher_plante(nom_plante, "Token", token)
    if pid != None:
        obtenir_details_plante(pid, "Token", token)
