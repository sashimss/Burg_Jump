# 🐰 Burg Jump

**Burg Jump** is a side-scrolling mini-game for the **Arduino Uno** with a **16x2 I2C LCD display**.  
Guide a pixelated rabbit to jump over obstacles using a single button!

The game uses **custom LCD bitmaps** to represent the rabbit and obstacles, making full use of the limited display for a fun visual experience.

## 🎮 Gameplay

- A rabbit (drawn using a custom bitmap) stays on the left side of the screen.
- Obstacles (also bitmap characters) scroll from right to left.
- Press the button (connected to **digital pin 8**) to make the rabbit jump.
- The rabbit stays in the air for a moment before automatically landing.
- Survive as long as you can — the game speed increases over time!

## 🧰 Hardware Requirements

- Arduino Uno
- 16x2 LCD Display with I2C interface
- Push Button
- 10kΩ Resistor (pull-down)
- Jumper Wires
- Breadboard

## 🔌 Circuit Diagram

| Component     | Connection                |
|---------------|----------------------------|
| LCD SDA       | A4 (Arduino Uno)           |
| LCD SCL       | A5 (Arduino Uno)           |
| Button        | One side to Digital Pin 8  |
|               | Other side to GND via 10kΩ |
|               | Also to 5V directly        |

> Tip: If the LCD doesn’t show anything, run an I2C address scanner to check the display’s address.

## 💾 Libraries Used

- `LiquidCrystal_I2C.h`
- `Wire.h`

## 🚀 Getting Started

1. Clone or download this repository.
2. Open the `.ino` sketch in the Arduino IDE.
3. Connect your components as per the circuit diagram.
4. Upload the sketch to your Arduino Uno.
5. Press the button to jump and dodge the obstacles!

## 🧠 Features

- Custom character bitmaps for rabbit and obstacle
- Side-scrolling obstacle logic
- Jump-and-land mechanic with button press
- Simple game loop and increasing difficulty
- Designed entirely within the limitations of a 16x2 LCD

---

