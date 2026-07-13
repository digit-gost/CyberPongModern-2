# 🏓 Cyber Pong Modern

Réinterprétation cyberpunk du jeu Pong, développée en C++17 avec SFML.
Projet réalisé dans le cadre du module *C++ et Bibliothèques Graphiques*.

## Fonctionnalités

✅ Boucle de jeu avec delta time (stable à 30 comme à 144 FPS)
✅ Architecture MVC + Pattern State (Menu / Jeu / Pause / Game Over)
✅ Physique de balle : rebond sur bords et raquettes, angle selon point d'impact, accélération progressive
✅ Mode 2 joueurs (même clavier) et mode Joueur vs IA
✅ IA à 3 niveaux sélectionnables dans le menu (Rookie, Cyborg, NEXUS-9)
✅ 6 power-ups (Speed Boost, Slow Mo, Big Paddle, Tiny Paddle, Invisible Ball, Twin Ball)
✅ Score en temps réel + sets, avec couleurs distinctes par joueur
✅ Trainée lumineuse de la balle (8 frames)
✅ Flash à l'impact sur les raquettes
✅ Fond animé en grille cyberpunk
✅ Écran de pause (reprise ou retour au menu)
✅ Écran de victoire avec récapitulatif des sets
✅ Sauvegarde du top 5 des scores (`scores.txt`) + affichage dans le menu
✅ Effets sonores (impact raquette, victoire, défaite, set gagné) + musique d'ambiance

🎁 Bonus réalisés : Son & Musique (+1 pt)
🚧 Bonus non réalisés : particules, shader CRT, IA adaptative, mode tournoi

## Prérequis

- CMake ≥ 3.16
- SFML 3.x
- Compilateur compatible C++17 (Clang, GCC, MSVC)

> **Note technique :** le sujet demande SFML 2.5, mais seule SFML 3.x était
> disponible facilement via Homebrew sur macOS (Apple Silicon) au moment du
> développement. L'API a été adaptée en conséquence (voir la section
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
(gratuite sur [Google Fonts](https://fonts.google.com/specimen/Orbitron)),
sinon le texte (menu, score) ne s'affichera pas correctement.

⚠️ Des fichiers audio doivent être présents dans `assets/sounds/` :
`paddle_hit.wav`, `victory.wav`, `defeat.wav`, `set_win.wav`, `ambiance.ogg`
(sources libres recommandées : freesound.org, Pixabay Music, incompetech.com).

## Contrôles

| Action                             | Touche(s)              |
|-------------------------------------|--------------------------|
| Naviguer dans le menu                | Flèches Haut / Bas       |
| Changer le niveau d'IA (option "Jouer") | Flèches Gauche / Droite |
| Valider une option du menu           | Entrée                   |
| Raquette gauche (Joueur 1)           | Z / W (haut) — S (bas)  |
| Raquette droite (Joueur 2, mode 2P)  | Flèches Haut / Bas       |
| Pause / Reprendre                    | P ou Échap               |
| Depuis la pause, retour au menu      | M ou Entrée              |
| Depuis l'écran de victoire, retour au menu | Entrée              |
| Quitter (depuis le menu)             | Échap                    |

## Vérification mémoire

```bash
cd build
make CyberPongModern_asan
./CyberPongModern_asan
```

> Sur macOS (notamment Apple Silicon), valgrind n'est pas officiellement
> supporté. AddressSanitizer (intégré à Clang) est utilisé comme équivalent
> pendant le développement. Une vérification avec `valgrind --leak-check=full`
> est également prévue sur la machine Linux Ubuntu 22.04 utilisée pour le
> rendu final.

## Architecture du projet

```
CyberPongModern/
├── CMakeLists.txt
├── main.cpp
├── src/
│   ├── core/
│   │   ├── Game.h / .cpp         ← boucle principale, pile d'états
│   │   ├── AssetManager.h / .cpp ← cache de polices
│   │   ├── AudioManager.h / .cpp ← effets sonores et musique
│   │   └── Paths.h               ← chemins des assets
│   ├── states/                   ← Pattern State
│   │   ├── State.h               ← interface abstraite
│   │   ├── GameMode.h
│   │   ├── StateMenu.h / .cpp
│   │   ├── StateGame.h / .cpp
│   │   ├── StatePause.h / .cpp
│   │   └── StateGameOver.h / .cpp
│   ├── entities/                 ← Héritage & Polymorphisme
│   │   ├── Entity.h              ← classe de base abstraite
│   │   ├── Ball.h / .cpp
│   │   ├── Paddle.h / .cpp
│   │   └── PowerUp.h / .cpp
│   ├── systems/
│   │   ├── PhysicsSystem.h / .cpp    ← collisions & physique
│   │   ├── AIController.h / .cpp     ← IA des 3 niveaux
│   │   ├── ScoreSystem.h / .cpp      ← score, sets
│   │   ├── PowerUpSystem.h / .cpp    ← spawn & effets des power-ups
│   │   └── HighScoreTable.h / .cpp   ← sauvegarde des scores
│   └── ui/
│       └── HUD.h / .cpp          ← affichage du score
└── assets/
    ├── fonts/Orbitron-Regular.ttf
    └── sounds/ (paddle_hit.wav, victory.wav, defeat.wav, set_win.wav, ambiance.ogg)
```

## Développé par Serigne Abdou Khadre Mbacke SANKHARE