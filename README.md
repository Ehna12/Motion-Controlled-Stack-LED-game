# 🎮 Motion-Controlled Stack LED Game

An interactive **motion-controlled LED stacking game** built using an **Arduino** and an **8×8 LED dot matrix**. The player controls the movement of the falling blocks using a motion sensor, making the game more engaging than a traditional button-controlled version.

## 📌 Overview

The **Motion-Controlled Stack LED Game** is a compact embedded-systems project that combines:

* 🎮 Game logic
* 💡 LED matrix display
* 🧭 Motion-based user interaction
* ⚡ Arduino microcontroller programming

The objective is to **stack falling blocks as accurately as possible**. The player uses physical motion to control the horizontal position of the falling block and attempts to align it with the blocks already placed below.

The game demonstrates how sensors, microcontrollers, and visual output devices can be integrated to create an interactive embedded system.

## ✨ Features

* 🕹️ Motion-based game control
* 🔲 8×8 LED dot matrix display
* 📦 Falling-block gameplay
* 🎯 Alignment-based scoring
* ⚡ Arduino-based control
* 🔄 Real-time game updates
* 💾 Lightweight embedded implementation
* 👾 Simple and interactive gameplay

## 💻 Software Requirements

* Arduino IDE
* Arduino-compatible board
* Required sensor/display libraries
* USB drivers for the Arduino board

## 🔌 System Architecture

```text
        ┌──────────────────┐
        │   Motion Sensor  │
        │  / Accelerometer │
        └────────┬─────────┘
                 │
                 ▼
        ┌──────────────────┐
        │     Arduino      │
        │   Game Logic     │
        └────────┬─────────┘
                 │
                 ▼
        ┌──────────────────┐
        │   8×8 LED Matrix │
        │      Display     │
        └──────────────────┘
```

### Working Principle

1. The motion sensor detects the player's movement.
2. The Arduino reads and processes the sensor values.
3. The detected motion is converted into horizontal movement of the falling block.
4. The falling block is displayed on the 8×8 LED matrix.
5. When the block reaches the bottom, its position is compared with the existing stack.
6. Successfully aligned blocks increase the player's score.
7. Poor alignment reduces the playable area for subsequent blocks.
8. The game continues until the stack reaches the top of the display.

## 🎮 Gameplay

### Objective

Stack as many blocks as possible while maintaining maximum alignment between consecutive blocks.

### Controls

| Motion            | Action            |
| ----------------- | ----------------- |
| Tilt / Move Left  | Move block left   |
| Tilt / Move Right | Move block right  |
| Neutral Position  | Maintain position |

The exact control mapping depends on the orientation and calibration of the motion sensor.

## 🧠 Game Logic

The game can be represented using the following sequence:

```text
START
  │
  ▼
Initialize Arduino
  │
  ▼
Initialize Motion Sensor
  │
  ▼
Initialize LED Matrix
  │
  ▼
Generate Falling Block
  │
  ▼
Read Motion Sensor
  │
  ▼
Move Block Horizontally
  │
  ▼
Block Reaches Stack
  │
  ▼
Check Alignment
  │
  ├──── Good Alignment ────► Update Stack + Score
  │
  └──── Poor Alignment ────► Reduce Stack Width
                              │
                              ▼
                       Generate Next Block
                              │
                              ▼
                         Game Over?
                           │
                     ┌─────┴─────┐
                    NO           YES
                     │             │
                     └──────┐      ▼
                            │   Display Score
                            │
                            └──► Continue
```

## 📂 Repository Structure

```text
Motion-Controlled-Stack-LED-Game/
│
├── src/
│   └── motion_stack_game.ino
│
├── README.md
│
└── images/
    └── project_setup.jpg
```

> Update the filenames and folder structure according to the actual contents of your repository.

## 🚀 Getting Started

### 1. Clone the Repository

```bash
git clone <repository-url>
```

### 2. Open the Project

Open the `.ino` file in the **Arduino IDE**.

### 3. Connect the Hardware

Connect the Arduino, motion sensor, and 8×8 LED matrix according to the circuit design.

### 4. Select the Board

In Arduino IDE:

```text
Tools → Board → Arduino Uno
```

Select the appropriate COM port under:

```text
Tools → Port
```

### 5. Upload the Code

Compile and upload the program to the Arduino.

### 6. Play

Once the system starts, use the motion sensor to control the falling blocks and try to build the tallest possible stack.

## 🔧 Calibration

For reliable motion control, the sensor should be calibrated before gameplay.

A typical calibration process is:

```text
Read sensor values
       ↓
Determine neutral position
       ↓
Define left/right thresholds
       ↓
Apply threshold filtering
       ↓
Map sensor movement → block movement
```

Calibration helps prevent unwanted movement caused by sensor noise or small hand movements.

## 📊 Concepts Demonstrated

This project demonstrates several fundamental concepts in electronics and embedded systems:

* Microcontroller programming
* Digital output control
* LED matrix multiplexing
* Sensor interfacing
* Motion detection
* Analog-to-digital conversion
* Real-time processing
* Game-state management
* Conditional logic
* Embedded hardware-software integration

## 🔮 Future Improvements

Possible extensions include:

* 🔊 Add a buzzer for sound effects
* 🏆 Implement a high-score system
* 💾 Store high scores using EEPROM
* 🎨 Use RGB LED matrices
* 📱 Add Bluetooth-based score monitoring
* ⚙️ Add adjustable game difficulty
* 🔋 Make the system battery powered
* 👥 Add multiplayer functionality
* 🎵 Add background music and game sounds
* 📈 Add different levels and increasing block speeds

## 🎯 Learning Outcomes

Through this project, we learned how to:

* Interface sensors with an Arduino.
* Control an LED matrix using a microcontroller.
* Process real-time sensor data.
* Convert physical movement into digital control.
* Implement game logic on resource-constrained hardware.
* Integrate hardware and software into an interactive system.

## 👩‍💻 Project

**Project:** Motion-Controlled Stack LED Game
**Platform:** Arduino
**Display:** 8×8 LED Dot Matrix
**Input:** Motion Sensor / Accelerometer
**Domain:** Embedded Systems & Interactive Electronics
