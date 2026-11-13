# Mohamed Mohamed – Software Engineering Portfolio

![C++17](https://img.shields.io/badge/C%2B%2B17-00599C?style=flat-square&logo=cplusplus&logoColor=white)
![Qt](https://img.shields.io/badge/Qt-41CD52?style=flat-square&logo=qt&logoColor=white)
![Flutter](https://img.shields.io/badge/Flutter-02569B?style=flat-square&logo=flutter&logoColor=white)
![Python](https://img.shields.io/badge/Python-3776AB?style=flat-square&logo=python&logoColor=white)
![GitLab CI](https://img.shields.io/badge/GitLab%20CI-FC6D26?style=flat-square&logo=gitlab&logoColor=white)

A curated portfolio of university and personal software engineering projects built during my **B.Sc. Information Technology** studies at **Hochschule Darmstadt**, covering **C++17 / Qt**, **Flutter / Dart**, **Python**, object-oriented design, and automated testing.

- **GitHub:** [@mohaziko](https://github.com/mohaziko)
- **Contact:** mohamedarbeit99@gmail.com
- **Location:** Darmstadt, Germany

---

## Repository Overview

| Folder | Stack | Focus |
|---|---|---|
| [`./Fit4Life_Flutter`](./Fit4Life_Flutter) | Flutter, Dart, Provider, Hive | Full cross-platform fitness, nutrition & social app |
| [`./Drachen`](./Drachen) | C++17, Qt Widgets, `QGraphicsScene`, `nlohmann/json` | Interactive map & dragon-flight travel planner with SVG layers and Haversine POI distances |
| [`./Navigation von Deutschland`](./Navigation%20von%20Deutschland) | C++17, Qt Widgets, QTest | German city-graph route planner implementing Dijkstra's shortest-path algorithm + unit tests |
| [`./Calculator`](./Calculator) | C++17, Qt Widgets, QTest | Desktop calculator with custom `anglefunctor` math evaluation and automated unit tests |
| [`./Bibliothek`](./Bibliothek) | C++17 (OOP / Console) | Polymorphic library management system (`Medien`, `Buch`, `CD`, `Hoerbuch`, `Kunde`) |

---

## Project Highlights

### 1. Fit4Life – Cross-Platform Fitness App ([`./Fit4Life_Flutter`](./Fit4Life_Flutter))
Modular Flutter application structured into `pages/`, `handler/`, `crud/`, `models/`, and `data/`:
- **State & Local Persistence:** `provider` for reactive UI state and `hive_ce` / `hive_ce_flutter` for offline data storage (`foodcrud`, `trainingcrud`, `profilcrud`, `statisticscrud`).
- **Features:** Workout & meal tracking, progress semicircle & analytics views, local notifications (`flutter_local_notifications`), QR contact/profile sharing (`qr_flutter`), social/chat pages, and image picking/sharing.
- **Run locally:**
  ```bash
  cd Fit4Life_Flutter/src
  flutter pub get
  flutter test
  flutter run
  ```

### 2. Drachen – Qt Map & Travel Planner ([`./Drachen`](./Drachen))
Desktop Qt application (`Filmstudio_Aufgabe8_Ausgangsbasis.pro`) inspired by *How to Train Your Dragon*:
- **Graphics & UI:** Custom `QGraphicsScene` canvas (`Kartenszene`), SVG POI map layers (`DragonMap`, `DragonPOILayer`, `icons.qrc`), and custom dialogs (`DrachenflugDialog`, `NachtlagerDialog`, `SuchergebnisDialog`).
- **Architecture & Data:** Polymorphic `Drache` class hierarchy, Haversine distance calculations across POIs, `Reiseplan` management, and JSON persistence via `nlohmann/json` (`filmstudio.json`, `poi.json`).

### 3. Navigation von Deutschland ([`./Navigation von Deutschland`](./Navigation%20von%20Deutschland))
Graph routing and map visualization application (`Navi_P4.pro`) across German cities (`Ort.txt`):
- **Routing:** Shortest-path calculation using **Dijkstra's algorithm** over modeled city, address, and POI nodes (`Ort`, `MyOrt`, `Adresse`, `POI`).
- **Testing:** Built-in **Qt TestLib (`QTest`)** suite in `test.cpp`.

### 4. Calculator ([`./Calculator`](./Calculator))
Qt Widgets desktop calculator (`Calculatorrr.pro`) pairing UI forms (`mainwindow.ui`) with a custom angle functor (`anglefunctor`) and unit tests (`test.cpp` with `QTest`).

### 5. Bibliothek ([`./Bibliothek`](./Bibliothek))
C++17 OOP console system (`lj.pro`) demonstrating inheritance and polymorphism across `Medien` subclasses (`Buch`, `CD`, `Hoerbuch`), customer management (`Kunde`), and file persistence (`medien.txt`).

---

## Tech Stack
- **Languages:** C++ (C++17), Dart, Python
- **Frameworks & Libraries:** Qt (`Core`, `GUI`, `Widgets`, `Network`, `TestLib`), Flutter (`provider`, `hive_ce`, `qr_flutter`, `flutter_local_notifications`), `nlohmann/json`
- **Engineering & CI:** Git, GitLab CI (`.gitlab-ci.yml`), Linux, QTest, `flutter_test`
