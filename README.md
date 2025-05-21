# 🚕 Rush Hour – C++ OpenGL Game (GLUT + Binary File I/O)

Welcome to **Rush Hour**, a C++ game developed using **OpenGL (GLUT)** as Object-Oriented Programming (OOP) project on Ubuntu. This fun and interactive game blends real-world logic with game development fundamentals like file handling, graphics, and object-oriented design.

---

## 🎮 Game Overview

You're a city driver in a rush! Switch between:

- **🚖 Taxi Mode** – Pick up passengers and drop them at their destination
- **📦 Delivery Mode** – Pick up packages (boxes) and deliver them

### Game Features:

- 🧭 **Mode Changer** at the corner to switch between Taxi and Delivery
- ⛽ **Fuel Stations** to refill your vehicle
- 🧱 **Obstacles** to avoid
- 🏁 **Leaderboard** at the end using **binary file handling**
- 🔊 Integrated sound effects (`collision.wav`, `dropped.wav`, `gameover.wav`)

---

## 🛠️ Tech Used

- **C++**
- **OpenGL (GLUT)** for graphics
- **WAV files** for sound effects
- **Binary File I/O** for storing leaderboard data
- **Ubuntu Linux**

---

## 🚀 How to Run the Game

### 1. Install Required Packages (Ubuntu)

```bash
sudo apt-get update
sudo apt-get install freeglut3-dev build-essential libglu1-mesa-dev
```

2. Build the Game

Make sure you are in the project root folder, then:

```bash
make
```

3. Play the Game

```bash
./game
```
