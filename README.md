# Cyber Pong Modern — État Jour 1

## État actuel
- Boucle de jeu avec delta time (Game.h/.cpp)
- Entity abstraite (Entity.h)
- Ball et Paddle fonctionnels (déplacement, rebond bords haut/bas)
- PhysicsSystem : collision balle/raquette avec angle de rebond et accélération progressive
- Pas encore : menu, score affiché, IA, power-ups, sauvegarde (arrivent Jour 2 et 3)

## Compilation
Prérequis : CMake >= 3.16, SFML 3.x (adapté depuis SFML 2.5 — voir note
dans CMakeLists.txt et section rapport "choix techniques"), un compilateur
C++17.

Installation sur macOS :
```bash
brew install cmake sfml
```

```bash
mkdir build && cd build
cmake ..
make
./CyberPongModern
```

## Contrôles (Jour 1)
- Joueur gauche : Z/W (haut) et S (bas)
- Joueur droit : flèches Haut / Bas
- Échap : quitter

## Vérification mémoire
```bash
cd build
make memcheck
```
