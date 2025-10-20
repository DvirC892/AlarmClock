#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {A0, A1, A2, A3};
byte colPins[COLS] = {6, 7, 8, 9};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

int buzzerPin = 10;

unsigned long prevMillis = 0;
unsigned long buzzerTimer = 0;

int seconds = 0, minutes = 0, hours = 0;
bool editMode = false;
bool alarmMode = false;
bool alarmOn = false;
bool alarmRinging = false;
bool buzzerState = false;

int setHour, setMinute, setSecond;
int alarmHour = -1, alarmMinute = -1, alarmSecond = -1;

void setup() {
  lcd.init();
  lcd.backlight();
  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  unsigned long currentMillis = millis();
  char key = keypad.getKey();

  if (!editMode && currentMillis - prevMillis >= 1000) {
    prevMillis = currentMillis;
    seconds++;
    if (seconds >= 60) {
      seconds = 0;
      minutes++;
      if (minutes >= 60) {
        minutes = 0;
        hours = (hours + 1) % 24;
      }
    }
    displayTime(hours, minutes, seconds);
    checkAlarm();
  }

  if (key) {
    if (alarmRinging) {
      if (key == 'A') {
        alarmRinging = false;
        alarmOn = false;
        noTone(buzzerPin);
        clearAlarmLine();
      }
    } else {
      switch (key) {
        case '1':
          editMode = !editMode;
          if (editMode) {
            setHour = hours;
            setMinute = minutes;
            setSecond = seconds;
          } else {
            hours = setHour;
            minutes = setMinute;
            seconds = setSecond;
            displayTime(hours, minutes, seconds);
          }
          break;
        case '3':
          alarmMode = !alarmMode;
          if (alarmMode) {
            alarmHour = 0;
            alarmMinute = 0;
            alarmSecond = 0;
          } else {
            alarmOn = true;
            displayTime(hours, minutes, seconds);
          }
          break;
        case '4':
          if (editMode) {
            setHour = (setHour + 1) % 24;
          } else if (alarmMode) {
            alarmHour = (alarmHour + 1) % 24;
          }
          break;
        case '5':
          if (editMode) {
            setMinute = (setMinute + 1) % 60;
          } else if (alarmMode) {
            alarmMinute = (alarmMinute + 1) % 60;
          }
          break;
        case '6':
          if (editMode) {
            setSecond = (setSecond + 1) % 60;
          } else if (alarmMode) {
            alarmSecond = (alarmSecond + 1) % 60;
          }
          break;
        case '7':
           if (editMode) {
          setHour = (setHour + 23) % 24; 
          } else if (alarmMode) {
            alarmHour = (alarmHour + 23) % 24;
         }
          break;
        case '8':
          if (editMode) {
        setMinute = (setMinute + 59) % 60;
        } else if (alarmMode) {
          alarmMinute = (alarmMinute + 59) % 60;
        }
         break;
        case '9':
         if (editMode) {
        setSecond = (setSecond + 59) % 60;
        } else if (alarmMode) {
          alarmSecond = (alarmSecond + 59) % 60;
        }
         break;
      }
    }
  }

  if (editMode) {
    displayTime(setHour, setMinute, setSecond);
  }

  if (alarmMode) {
    lcd.setCursor(0, 0);
    lcd.print("Alarm:");
    printDigits(alarmHour); lcd.print(":");
    printDigits(alarmMinute); lcd.print(":");
    printDigits(alarmSecond);
  }

  if (alarmRinging) {
    if (currentMillis - buzzerTimer >= 500) {
      buzzerTimer = currentMillis;
      if (buzzerState) {
        noTone(buzzerPin);
        buzzerState = false;
      } else {
        tone(buzzerPin, 1000);
        buzzerState = true;
      }
    }
    lcd.setCursor(0, 1);
    lcd.print("** ALARM RING! **");
  }

  delay(50);
}

void displayTime(int h, int m, int s) {
  lcd.setCursor(0, 0);
  lcd.print("Time: ");
  printDigits(h); lcd.print(":");
  printDigits(m); lcd.print(":");
  printDigits(s);
}

void printDigits(int val) {
  if (val < 10) lcd.print("0");
  lcd.print(val);
}

void checkAlarm() {
  if (alarmOn && hours == alarmHour && minutes == alarmMinute && seconds == alarmSecond) {
    alarmRinging = true;
    buzzerTimer = millis();
    buzzerState = false;
  }
}

void clearAlarmLine() {
  lcd.setCursor(0, 1);
  lcd.print("                ");
}









