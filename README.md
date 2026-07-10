# 🏓 Cyber Pong Modern

Réinterprétation cyberpunk du jeu Pong, développée en C++17 avec SFML.
Projet réalisé dans le cadre du module *C++ et Bibliothèques Graphiques*.

## État d'avancement

✅ Boucle de jeu avec delta time (stable à 30 comme à 144 FPS)
✅ Architecture MVC + Pattern State (Menu / Jeu / Pause / Game Over)
✅ Physique de balle : rebond sur bords et raquettes, angle selon point d'impact, accélération progressive
✅ Mode 2 joueurs (même clavier) et mode Joueur vs IA
✅ IA à 3 niveaux (Rookie, Cyborg, NEXUS-9)
✅ Score en temps réel (points colorés par joueur) + sets
✅ Fond animé en grille cyberpunk
✅ Écran de pause avec retour au menu
✅ Écran de victoire avec retour au menu

🚧 À venir : power-ups, trainée lumineuse de la balle, sauvegarde des scores (`scores.txt`)

## Prérequis

- CMake ≥ 3.16
- SFML 3.x
- Compilateur compatible C++17 (Clang, GCC, MSVC)

> **Note technique :** le sujet demande SFML 2.5, mais seule SFML 3.x était
> disponible facilement via Homebrew sur macOS (Apple Silicon) au moment du
> développement. L'API a été adaptée en conséquence (voir section
> "Choix techniques" du rapport). Le comportement et les fonctionnalités
> demandées restent identiques.

## Installation des dépendances (macOS)

```bash
brew install cmake sfml
```

## Compilation

```bash
mkdir build
cd build
cmake ..
make
```

## Lancement

Depuis le dossier `build` :

```bash
./CyberPongModern
```

⚠️ Une police doit être présente dans `assets/fonts/Orbitron-Regular.ttf`
(téléchargeable gratuitement sur [Google Fonts](https://fonts.google.com/specimen/Orbitron)),
sinon le texte (menu, score) ne s'affichera pas correctement.

## Contrôles

| Action                          | Touche(s)            |
|----------------------------------|-----------------------|
| Naviguer dans le menu             | Flèches Haut / Bas    |
| Valider une option du menu        | Entrée                |
| Raquette gauche (Joueur 1)        | Z / W (haut) — S (bas)|
| Raquette droite (Joueur 2, mode 2P) | Flèches Haut / Bas  |
| Pause / Reprendre                 | P ou Échap            |
| Depuis la pause, retour au menu   | M ou Entrée           |
| Depuis l'écran de victoire, retour au menu | Entrée        |
| Quitter (depuis le menu)          | Échap                 |

## Vérification mémoire (valgrind)

```bash
cd build
make memcheck
```

> Sur macOS, valgrind n'est pas officiellement supporté (surtout sur Apple
> Silicon). Cette vérification sera faite sur la machine Linux Ubuntu 22.04
> utilisée pour le rendu final du projet.

## Architecture du projet
CyberPongModern/
├── CMakeLists.txt
├── main.cpp
├── src/
│   ├── core/
│   │   ├── Game.h / .cpp        ← boucle principale, gestion de la pile d'états
│   │   ├── AssetManager.h / .cpp← cache de polices
│   │   └── Paths.h              ← chemins des assets
│   ├── states/                  ← Pattern State
│   │   ├── State.h              ← interface abstraite
│   │   ├── GameMode.h
│   │   ├── StateMenu.h / .cpp
│   │   ├── StateGame.h / .cpp
│   │   ├── StatePause.h / .cpp
│   │   └── StateGameOver.h / .cpp
│   ├── entities/                ← Héritage & Polymorphisme
│   │   ├── Entity.h             ← classe de base abstraite
│   │   ├── Ball.h / .cpp
│   │   └── Paddle.h / .cpp
│   ├── systems/
│   │   ├── PhysicsSystem.h / .cpp   ← collisions & physique
│   │   ├── AIController.h / .cpp    ← IA des 3 niveaux
│   │   └── ScoreSystem.h / .cpp     ← score, sets
│   └── ui/
│       └── HUD.h / .cpp         ← affichage du score
└── assets/
└── fonts/Orbitron-Regular.ttf