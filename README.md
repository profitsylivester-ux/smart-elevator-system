 Accessible Elevator Control System 🛗

An Arduino-based elevator simulation designed with **accessibility in mind**. The system gives three independent channels of feedback — visual (LCD text), audible (chime), and physical (servo position) — every time a floor is requested, so users don't have to rely on a single sense to know the elevator has responded.

Built as a prototype for a 4-floor building: **Basement, Ground Floor, Floor 1, Floor 2.**

---

## ✨ Features

- 4 push-button floor selection (Basement, Ground, Floor 1, Floor 2)
- 16x2 LCD display showing current floor and "Floors Changing" transition status
- Realistic floor-passing simulation (shows intermediate floors when skipping levels)
- Servo motor that rotates to a position representing the current floor
- Soft, modern-elevator-style arrival chime (non-intrusive tone via piezo buzzer)
- Pull-down resistors on all button inputs for stable, noise-free readings

---

## 🧰 Hardware Required

| Component | Qty | Notes |
|---|---|---|
| Arduino Uno R3 | 1 | Main controller |
| 16x2 LCD (HD44780, parallel) | 1 | 4-bit mode |
| 10 kΩ Potentiometer | 1 | LCD contrast control |
| Push buttons | 4 | Floor selection |
| 10 kΩ resistors | 4 | Pull-down for buttons |
| 220 Ω resistor | 1 | LCD backlight current limiting |
| Piezo buzzer | 1 | Arrival chime |
| Servo motor (SG90 or similar) | 1 | Floor position indicator |
| External 6V supply (4×AA battery pack) | 1 | Dedicated servo power — do **not** power the servo from the Arduino's 5V pin |
| Breadboard + jumper wires | — | |

---

## 🔌 Pin Connections

### LCD (HD44780, 4-bit mode)
| LCD Pin | Arduino Pin |
|---|---|
| RS | 12 |
| E | 11 |
| DB4 | 5 |
| DB5 | 4 |
| DB6 | 3 |
| DB7 | 2 |
| VSS | GND |
| VDD | 5V |
| V0 (contrast) | Potentiometer wiper |
| RW | GND |
| LED+ (backlight) | 5V (via 220 Ω resistor) |
| LED− (backlight) | GND |

### Buttons (each with a 10 kΩ pull-down resistor to GND)
| Floor | Arduino Pin |
|---|---|
| Basement | 7 |
| Ground Floor | 8 |
| Floor 1 | 9 |
| Floor 2 | 13 |

### Other
| Component | Arduino Pin |
|---|---|
| Buzzer | 10 |
| Servo signal | 6 |
| Servo VCC | External 6V supply (**not** Arduino 5V) |
| Servo GND | Shared with Arduino GND |

> ⚠️ **Important:** The servo must be powered from a separate 6V source (e.g. 4×AA battery pack), not directly from the Arduino. Servos draw current spikes (up to ~650 mA under load) that can brown out the Arduino's shared 5V rail, causing the LCD to glitch or the servo to stop responding. The servo's ground must still be tied to the Arduino's ground.

---

## ⚙️ How It Works

1. A button press is read on the corresponding pin (pulled LOW by default, HIGH when pressed).
2. If the requested floor differs from the current floor, the LCD displays **"Floors Changing"**.
3. If moving past intermediate floors (e.g. Ground → Floor 2), those floors are briefly displayed in sequence — just like a real elevator's floor indicator.
4. The servo rotates to the angle assigned to the destination floor.
5. On arrival, a short two-tone chime plays (2000 Hz, 80 ms) and the LCD updates to show the final floor.

---

## 🚀 Getting Started

1. Wire the circuit according to the pin tables above.
2. Install the required library in Arduino IDE:
   - `LiquidCrystal` (built-in)
   - `Servo` (built-in)
3. Open `elevator_control.ino` in the Arduino IDE.
4. Select **Tools → Board → Arduino Uno** and the correct COM port.
5. Upload the sketch.
6. Power the servo from the external 6V supply, with grounds connected together.

---

## 🐞 Troubleshooting

| Symptom | Likely Cause |
|---|---|
| LCD shows nothing | Check contrast potentiometer, and confirm RW is wired to GND |
| A button doesn't respond | Missing/miswired pull-down resistor, or button on wrong pin — verify with a simple `digitalRead()` test sketch |
| Servo doesn't move | Confirm servo angle is between 0–180°, and that it's powered from the external 6V supply with a shared ground |
| Servo moves but LCD/buzzer glitch when it does | Servo is likely still powered from the Arduino 5V pin — move it to the external supply |

---

## 📄 License

This project is open for educational and non-commercial use. Feel free to fork and adapt for your own accessibility-focused builds.

---

## 🙋 Author
Faida sylivester mosses
Built as part of an Electrical Engineering coursework project exploring embedded systems for accessible building infrastructure.
