# 🌿 MINI PROJET 2026 : SERRE AUTONOME & ADAPTATIVE (AGRITECH)

## Activité n°1 (IR) : Mettre en oeuvre l'API Open Plantbook

### Mise en situation

Rappel : Le système devra remplir la mission suivante "sélection de la culture" afin d'adapter sa gestion.

1.  **Sélection :** L'utilisateur indique sa culture (par exemple : "Basilic", "Orchidée", ...) via une interface web.
2.  **Traitement :** Le système interroge une **API externe** (_Open Plantbook_) pour récupérer les besoins vitaux de la plante pour les transmettre ensuite au module de gestion de la serre.

Exemple : scénario d'usage

```mermaid

sequenceDiagram
    participant U as Utilisateur
    participant RPI as Raspberry Pi (Serre)
    participant ESP as ESP32 (Serre)
    participant API as API OpenPlantbook
    participant ACT as Pompe/Moteur

    Note over U, ACT: SCÉNARIO "CHANGEMENT DE CULTURE"
    U->>RPI: Sélectionne "Tomate (Solanum lycopersicum)"
    activate RPI
    RPI->>API: GET /api/v1/plant/details?alias=tomato
    activate API
    API-->>RPI: JSON {min_moisture: 60%, max_temp: 28°C}
    deactivate API
    RPI->>ESP: trame "min_moisture:60,max_temp:28"
    activate ESP
    Note over ESP: Mise à jour des variables de seuil<br>Seuil_Arrosage = 60%

    deactivate ESP
```

### API Open Plantbook

[Open Plantbook](https://open.plantbook.io/) permet de recueillir et stocker des informations structurées sur les besoins vitaux des plantes.

> C'est un service gratuit. Tout le monde peut utiliser les informations de la base de données pour n'importe quel but sans limites.

[Open Plantbook](https://open.plantbook.io/) fournit une API pour récupérer les données biologiques des plantes (un _token_ est requis).

L'URL de base de l'API : `https://open.plantbook.io/api/v1/`

Pour utiliser cette API, il faut se connecter à l'interface utilisateur Web d'Open Plantbook et générer des informations d'identification API.

![](./images/plantbook-home.png)

On clique sur _Sign In_ :

![](./images/plantbook-signin.png)

On peut utiliser son compte _Google_ ou _GitHub_ :

![](./images/plantbook-github-access.png)

#### Authentification

Documentation : [Open Plantbook API Public](https://documenter.getpostman.com/view/12627470/TVsxBRjD#56623c2d-7182-4b70-b31c-5cb8ed7b38c2)

L'API [Open Plantbook](https://open.plantbook.io/) prend en charge deux types d'authentification :

- _OAuth2 Client Credentials_ : le jeton généré est valable pour un temps limité et permet d'utiliser toutes les fonctionnalités (_endpoins_) en lecture/écriture.
- _API-key_ (pour la phase de développement uniquement) : le jeton généré n'expirera jamais mais ne permet que  l'utilisation de "`plant/search`" et "`plant/detail`" en lecture.

a. _OAuth2 Client Credentials_

Les informations d'identification sont `client_id` et `client_secret`.

Principe :

- Il faut générer `client_id` et `client_secret` dans l'interface web :

![](./images/plantbook-oauth2.png)

- En utilisant les informations d'identification ci-dessus, il faut obtenir le jeton _OAuth2 Bearer_ :

```sh
$ curl --location 'https://open.plantbook.io/api/v1/token/' --form 'grant_type="client_credentials"' --form 'client_id="xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"' --form 'client_secret="YYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYyyyyy"'
{"access_token": "vQ2McKKk4vvOzjPz2ZtAgxEXM8fsE7", "expires_in": 86400, "token_type": "Bearer", "scope": "read write"}
```

- On peut ensuite utiliser l'API avec le jeton _Bearer_ émis :

```sh
$ curl --silent --location 'https://open.plantbook.io/api/v1/plant/search?alias=acer&limit=10&offset=20' --header 'Authorization: Bearer vQ2McKKk4vvOzjPz2ZtAgxEXM8fsE7'
...
```

b. _API-key_

Principe :

- Il faut activer l'authentification _Token_ dans l'interface web et conserver une copie du jeton de clé API permanent :

![](./images/plantbook-token.png)

- On peut ensuite utiliser l'API avec le jeton _Token_ émis :

```sh
$ curl --silent --location 'https://open.plantbook.io/api/v1/plant/search?alias=acer&limit=10&offset=20' --header 'Authorization: Token XXXXXXXXXXXXXXXXXXXXXXXXXXXX'
...
```

#### Rechercher des plantes

Documentation : [Open lantbook API Public](https://documenter.getpostman.com/view/12627470/TVsxBRjD#d8ed1e76-6866-493b-8ccf-dd8ee8688aa6)

Il est possible de rechercher toute occurrence de texte dans les champs `display_pid` et `alias`, ainsi que les noms communs des plantes.

```sh
curl --silent --location 'https://open.plantbook.io/api/v1/plant/search?alias=acer&limit=10&offset=20' --header 'Authorization: Token XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX'
{"count":38,"next":"https://open.plantbook.io:443/api/v1/plant/search?alias=acer&limit=10&offset=30","previous":"https://open.plantbook.io:443/api/v1/plant/search?alias=acer&limit=10&offset=10","results":[{"pid":"platanus orientalis","display_pid":"Platanus orientalis","alias":"platanus acerifolia","category":"Platanaceae, Platanus"},{"pid":"acer capillipes","display_pid":"Acer capillipes","alias":"acer capillipes","category":"Aceraceae, Acer"},{"pid":"acer carpinifolium","display_pid":"Acer carpinifolium","alias":"acer carpinifolium","category":"Aceraceae, Acer"},{"pid":"acer circinatum","display_pid":"Acer circinatum","alias":"acer circinatum","category":"Sapindaceae, Acer"},{"pid":"acer davidii","display_pid":"Acer davidii","alias":"acer davidii","category":"Aceraceae, Acer"},{"pid":"acer ginnala","display_pid":"Acer ginnala","alias":"acer ginnala","category":"Aceraceae, Acer"},{"pid":"acer glabrum","display_pid":"Acer glabrum","alias":"acer glabrum","category":"Aceraceae, Acer"},{"pid":"acer macrophyllum","display_pid":"Acer macrophyllum","alias":"acer macrophyllum","category":"Aceraceae, Acer"},{"pid":"acer maximowiczianum","display_pid":"Acer maximowiczianum","alias":"acer maximowiczianum","category":"Aceraceae, Acer"},{"pid":"acer miyabei","display_pid":"Acer miyabei","alias":"acer miyabei","category":"Aceraceae, Acer"}]}
```

L'API retourne une réponse au format [JSON](https://fr.wikipedia.org/wiki/JavaScript_Object_Notation). Il est possible d'afficher un affichage formaté avec la commande `jq` :

```sh
$ curl --silent --location 'https://open.plantbook.io/api/v1/plant/search?alias=acer&limit=10&offset=20' --header 'Authorization: Token XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX' | jq
{
  "count": 38,
  "next": "https://open.plantbook.io:443/api/v1/plant/search?alias=acer&limit=10&offset=30",
  "previous": "https://open.plantbook.io:443/api/v1/plant/search?alias=acer&limit=10&offset=10",
  "results": [
    {
      "pid": "platanus orientalis",
      "display_pid": "Platanus orientalis",
      "alias": "platanus acerifolia",
      "category": "Platanaceae, Platanus"
    },
    {
      "pid": "acer capillipes",
      "display_pid": "Acer capillipes",
      "alias": "acer capillipes",
      "category": "Aceraceae, Acer"
    },
    {
      "pid": "acer carpinifolium",
      "display_pid": "Acer carpinifolium",
      "alias": "acer carpinifolium",
      "category": "Aceraceae, Acer"
    },
    {
      "pid": "acer circinatum",
      "display_pid": "Acer circinatum",
      "alias": "acer circinatum",
      "category": "Sapindaceae, Acer"
    },
    {
      "pid": "acer davidii",
      "display_pid": "Acer davidii",
      "alias": "acer davidii",
      "category": "Aceraceae, Acer"
    },
    {
      "pid": "acer ginnala",
      "display_pid": "Acer ginnala",
      "alias": "acer ginnala",
      "category": "Aceraceae, Acer"
    },
    {
      "pid": "acer glabrum",
      "display_pid": "Acer glabrum",
      "alias": "acer glabrum",
      "category": "Aceraceae, Acer"
    },
    {
      "pid": "acer macrophyllum",
      "display_pid": "Acer macrophyllum",
      "alias": "acer macrophyllum",
      "category": "Aceraceae, Acer"
    },
    {
      "pid": "acer maximowiczianum",
      "display_pid": "Acer maximowiczianum",
      "alias": "acer maximowiczianum",
      "category": "Aceraceae, Acer"
    },
    {
      "pid": "acer miyabei",
      "display_pid": "Acer miyabei",
      "alias": "acer miyabei",
      "category": "Aceraceae, Acer"
    }
  ]
}
```

#### Obtenir les détails de la plante par son Plant-ID

Documentation : [Open Plantbook API Public](https://documenter.getpostman.com/view/12627470/TVsxBRjD#c6cb33f4-e2c3-47d9-b086-786664db24d0)

Il est possible d'obtenir les détails d'une plante à partir de son _pid_ (ID de la plante).

```sh
$ curl --silent --location 'https://open.plantbook.io/api/v1/plant/detail/acer%20pseudoplatanus/' --header 'Authorization: Token XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX'
{"pid":"acer pseudoplatanus","display_pid":"Acer pseudoplatanus","alias":"acer pseudoplatanus","category":"Aceraceae, Acer","max_light_mmol":7200,"min_light_mmol":3000,"max_light_lux":75000,"min_light_lux":2800,"max_temp":35,"min_temp":5,"max_env_humid":80,"min_env_humid":30,"max_soil_moist":60,"min_soil_moist":15,"max_soil_ec":2000,"min_soil_ec":350,"image_url":"https://opb-img.plantbook.io/acer%20pseudoplatanus.jpg","common_names":[]}
```

> _Remarque :_ l'encodage de l'espace '` `' dans une URL est `%20` (La valeur hexdécimale `20` est le code ASCII du caractère espace '` `')

L'API retourne une réponse au format [JSON](https://fr.wikipedia.org/wiki/JavaScript_Object_Notation). Il est possible d'afficher un affichage formaté avec la commande `jq` :

```sh
$ curl --silent --location 'https://open.plantbook.io/api/v1/plant/detail/acer%20pseudoplatanus/' --header 'Authorization: Token XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX' | jq
{
  "pid": "acer pseudoplatanus",
  "display_pid": "Acer pseudoplatanus",
  "alias": "acer pseudoplatanus",
  "category": "Aceraceae, Acer",
  "max_light_mmol": 7200,
  "min_light_mmol": 3000,
  "max_light_lux": 75000,
  "min_light_lux": 2800,
  "max_temp": 35,
  "min_temp": 5,
  "max_env_humid": 80,
  "min_env_humid": 30,
  "max_soil_moist": 60,
  "min_soil_moist": 15,
  "max_soil_ec": 2000,
  "min_soil_ec": 350,
  "image_url": "https://opb-img.plantbook.io/acer%20pseudoplatanus.jpg",
  "common_names": []
}
```

L'image de cette plante :

![](https://opb-img.plantbook.io/acer%20pseudoplatanus.jpg)

### Travail demandé

:warning: Vous devez répondre dans le document au format Markdown.

1. Donner la commande `curl` et le résultat obtenu pour récupérer le _pid_ de la plante dont le nom commun est "Basilic".

![](https://opb-img.plantbook.io/ocimum%20basilicum.jpg)

```sh
curl --silent --location 'https://open.plantbook.io/api/v1/plant/search?alias=basilic' --header 'Authorization: Token 141c16127c00b409ba21fea487a26e509c337a9b' | jq

```

Résultat:

```sh

{
  "count": 1,
  "next": null,
  "previous": null,
  "results": [
    {
      "pid": "ocimum basilicum",
      "display_pid": "Ocimum basilicum",
      "alias": "ocimum basilicum",
      "category": "Labiatae, Ocimum"
    }
  ]
}

```

Le _pid_ du "Basilic" est ocimum basilicum 

2. Donner la commande `curl` et le résultat obtenu pour récupérer les besoins vitaux de la plante dont le _pid_ est "lycopersicon esculentum".

![](https://opb-img.plantbook.io/lycopersicon%20esculentum.jpg)

```sh

curl --silent --location 'https://open.plantbook.io/api/v1/plant/detail/lycopersicon%20esculentum/' --header 'Authorization: Token 141c16127c00b409ba21fea487a26e509c337a9b' | jq

```

Résultat



3. Identifier la description et les unités des paramètres fournis par la commande précédente.

| Paramètre    | Description                           | Unité       |
| ------------ | ------------------------------------- | :---------: |
| "light_mmol" | Rayonnement photosynthétiquement actif| μmol.m .s   |
| "light_lux"  | Éclairement lumineux                  | lux         |
| "temp"       | temperature de l'air                  |  °C         |
| "env_humid"  | Humidité de l'air                     |   %         |
| "soil_moist" | Humidité du sol                       |   %         |
| "soil_ec"    | Conductivité du sol                   |   μS/cm     |

On vous fournit le script Python [src/1-plantbook/plantbook.py](./src/1-plantbook/plantbook.py) qui permet d'effectuer des requêtes vers l'API d'_Open Plantbook_.

```sh
$ python3 plantbook.py
Usage: plantbook.py <nom_plante>
```

4. Exécuter le script pour effectuer une recherche pour les plantes suivantes :

- l'alias "Basilic"
- le _pid_ "ocimum basilicum"
- l'alias "tomato"
- l'alias "fraise"

5. Compléter le script pour obtenir les détails d'une plante à partir de son _pid_.

```sh
$ python3 plantbook.py "ocimum basilicum"
Recherche de la plante 'ocimum basilicum' dans Open Plantbook ...
1 plante(s) trouvée(s)
{
    "count": 1,
    "next": null,
    "previous": null,
    "results": [
        {
            "pid": "ocimum basilicum",
            "display_pid": "Ocimum basilicum",
            "alias": "ocimum basilicum",
            "category": "Labiatae, Ocimum"
        }
    ]
}
Détails de la plante (ocimum basilicum):
{
    "pid": "ocimum basilicum",
    "display_pid": "Ocimum basilicum",
    "alias": "ocimum basilicum",
    "category": "Labiatae, Ocimum",
    "max_light_mmol": 6000,
    "min_light_mmol": 3600,
    "max_light_lux": 60000,
    "min_light_lux": 2500,
    "max_temp": 32,
    "min_temp": 8,
    "max_env_humid": 80,
    "min_env_humid": 30,
    "max_soil_moist": 60,
    "min_soil_moist": 15,
    "max_soil_ec": 2000,
    "min_soil_ec": 350,
    "image_url": "https://opb-img.plantbook.io/ocimum%20basilicum.jpg",
    "common_names": [
        {
            "name": "Basilikum",
            "language_code": "de"
        },
        {
            "name": "Basil",
            "language_code": "en"
        },
        {
            "name": "Basilico",
            "language_code": "it"
        },
        {
            "name": "Basilicum",
            "language_code": "nl"
        }
    ]
}
```

---
BTS LaSalle Avignon 2026
