# 🌿 MINI PROJET 2026 : SERRE AUTONOME & ADAPTATIVE (AGRITECH)

## Activité n°1 (Sciences Physiques) : Étude du système

### Mise en situation

Rappel : Le système devra remplir la mission suivante "maintenir un environnement idéal pour la croissance des plantes".

La culture sous serre s'appelle la **serriculture**.

Une serre est une structure qui peut être parfaitement close destinée en général à la production agricole. Elle vise à soustraire aux éléments climatiques les cultures vivrières ou de loisir pour **une meilleure gestion des besoins des plantes et pour en accélérer la croissance ou les produire indépendamment des saisons**.

La maîtrise du climat est la raison d'être des serres : **on cherche à créer un environnement idéal pour la croissance des plantes**.

> Sa gestion est souvent confiée à un ordinateur surtout si les unités de production sont grandes.

### Travail demandé

:warning: Le document à rédiger est dans _Google Classroom_.

> Annexe : [CAPTEUR.md](./annexes/CAPTEUR.md)

On a récupéré les besoins vitaux pour la culture de tomates (_lycopersicon esculentum_).

![](https://opb-img.plantbook.io/lycopersicon%20esculentum.jpg)

```sh
$ curl --silent --location 'https://open.plantbook.io/api/v1/plant/detail/lycopersicon%20esculentum/' --header 'Authorization: Token XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX' | jq
{
  "pid": "lycopersicon esculentum",
  "display_pid": "Lycopersicon esculentum",
  "alias": "solanum lycopersicum",
  "category": "Solanaceae, Solanum",
  "max_light_mmol": 22000,
  "min_light_mmol": 5200,
  "max_light_lux": 130000,
  "min_light_lux": 4000,
  "max_temp": 35,
  "min_temp": 10,
  "max_env_humid": 70,
  "min_env_humid": 30,
  "max_soil_moist": 70,
  "min_soil_moist": 22,
  "max_soil_ec": 2500,
  "min_soil_ec": 350,
  "image_url": "https://opb-img.plantbook.io/lycopersicon%20esculentum.jpg",
  "common_names": []
}
```

1. À partir des résultats fournis par la commande précédente, identifier les mesures à effectuer pour contrôler les seuils des paramètres :

| Paramètre    | Mesure | Unité |
| ------------ | ------ | :---: |
| "light_mmol" |        |       |
| "light_lux"  |        |       |
| "temp"       |        |       |
| "env_humid"  |        |       |
| "soil_moist" |        |       |
| "soil_ec"    |        |       |

2. En quoi la mesure du rayonnement photosynthétiquement actif (PAR) est-elle  essentielle en serriculture ?

3. Rechercher des capteurs à intégrer à la serre pour assurer les mesures ci-dessus.

4. Rechercher des actionneurs à intégrer à la serre en précisant leur but pour maintenir un environnement idéal pour la croissance des plantes.

5. Compléter maintenant le synoptique ci-dessous de la serre en précisant les capteurs et les actionneurs.

```mermaid
flowchart TD
    %% Styles
    classDef hardware fill:#ccf,stroke:#333,stroke-width:2px;

    subgraph GREENHOUSE ["🌿 SERRE PHYSIQUE"]
        ESP32{{"Microcontrôleur<br>(ESP32)"}}:::hardware

        subgraph SENSORS ["Capteurs (Entrées)"]
            Sol[/"___________"/]
            Air[/"___________"/]
            Lum[/"___________"/]
        end

        subgraph ACTUATORS ["Actionneurs (Sorties)"]
            Pompe(("___________"))
            Verrin(("___________"))
            Ventilateur(("___________"))
            Chauffage(("___________"))
        end
    end

    %% Relations
    SENSORS -- "Lecture" --> ESP32
    ESP32 -- "Commande" --> ACTUATORS
```

---
BTS LaSalle Avignon 2026
