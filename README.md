# Arduino Alarm Clock

This is a simple *Arduino-based alarm clock* using a *16x2 LCD* and a *4x4 keypad*. It allows you to set the current time, configure an alarm, and provides a buzzer notification when the alarm goes off.

[Watch a demo video](https://www.youtube.com/shorts/GKTbKIOK1yM)

---

## Features

- Display current time on a 16x2 LCD
- Set hours, minutes, and seconds
- Set an alarm time
- Alarm notification with buzzer
- Increment/decrement time using a 4x4 keypad
- Start/stop alarm using keypad buttons

---

## Hardware Requirements

- Arduino board (Uno, Mega, etc.)
- 16x2 I2C LCD
- 4x4 Keypad
- Buzzer
- Jumper wires
- Breadboard

---

## Connections

| Component       | Pin on Arduino |
|-----------------|----------------|
| LCD SDA         | A4             |
| LCD SCL         | A5             |
| Keypad Rows     | A0, A1, A2, A3 |
| Keypad Columns  | 6, 7, 8, 9     |
| Buzzer          | 10             |

---

## Keypad Controls

| Key | Function                                      |
|-----|-----------------------------------------------|
| 1   | Toggle edit mode for current time            |
| 3   | Toggle alarm mode                             |
| 4   | Increase hours (edit/alarm)                  |
| 5   | Increase minutes (edit/alarm)                |
| 6   | Increase seconds (edit/alarm)                |
| 7   | Decrease hours (edit/alarm)                  |
| 8   | Decrease minutes (edit/alarm)                |
| 9   | Decrease seconds (edit/alarm)                |
| A   | Stop ringing alarm                            |

---

## Code

The main code file is AlarmClock.ino.  
It uses the following libraries:

- [Wire.h](https://www.arduino.cc/en/reference/wire)  
- [LiquidCrystal_I2C.h](https://github.com/johnrickman/LiquidCrystal_I2C)  
- [Keypad.h](https://playground.arduino.cc/Code/Keypad/)

---

## How It Works

1. The clock keeps track of hours, minutes, and seconds.
2. The user can edit the current time using the keypad.
3. The user can set an alarm time.
4. When the current time matches the alarm, the buzzer rings and the LCD displays "*ALARM RING!*".
5. Pressing 'A' on the keypad stops the alarm.

---

## Video Demo

Watch the working demo here: [YouTube Short](https://www.youtube.com/shorts/GKTbKIOK1yM)

---

## License

This project is licensed under the MIT License.  
Feel free to use, modify, and share it!
