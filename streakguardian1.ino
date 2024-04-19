// include the library code:
#include <LiquidCrystal.h>
// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int i = 7;

int buttonStateOne = 0;
int buttonStateTwo = 0;
int buttonStateThree = 0;

int currentIndex = 0;

const int maxLength = 10;    // Maximum length of the arrays
String taskArray[maxLength]; // Array to hold tasks
int streakArray[maxLength];  // Array to hold streaks
int currentLength = 0;       // Variable to keep track of current length

void setup() {
    addTask("Cook");
    Serial.begin(9600);
    // set up the LCD's number of columns and rows:
    lcd.begin(16, 2);

    pinMode(8, INPUT);
    pinMode(9, INPUT);
    pinMode(10, INPUT);
    pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {

    buttonStateThree = digitalRead(8);
    buttonStateTwo = digitalRead(9);
    buttonStateOne = digitalRead(10);

    String currentTask = taskArray[currentIndex];
    int currentStreak = streakArray[currentIndex];

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(currentTask);
    lcd.setCursor(0, 1);
    lcd.print(currentStreak);

    /*
      lcd.setCursor(0, 0);


      lcd.print(taskOne);




      lcd.scrollDisplayLeft();

      i++;
      lcd.setCursor(i-2, 1);
      lcd.print("  ");
      lcd.setCursor(i, 1);
      lcd.print(10);

      if (i == 40) {
        i = 0;
      }
      //lcd.print("    ");
      delay(100);

    */

    // Button 1
    if (buttonStateOne == HIGH) {
        // turn LED on
        digitalWrite(LED_BUILTIN, HIGH);

        currentIndex--;

        if (currentIndex == -1) {
            currentIndex = 3 - 1;
        }

        currentTask = taskArray[currentIndex];

        currentStreak = streakArray[currentIndex];
    }

    // Button 2
    if (buttonStateTwo == HIGH) {
        // turn LED on
        digitalWrite(LED_BUILTIN, HIGH);

        currentIndex++;

        if (currentIndex == 3) {
            currentIndex = 0;
        }

        currentTask = taskArray[currentIndex];

        currentStreak = streakArray[currentIndex];
    } else {
        // turn LED off
        digitalWrite(LED_BUILTIN, LOW);
    }

    // Button 3
    if (buttonStateThree == HIGH) {
        // turn LED on
        digitalWrite(LED_BUILTIN, HIGH);

        streakArray[currentIndex]++;
    } else {
        // turn LED off
        digitalWrite(LED_BUILTIN, LOW);
    }

    delay(120); // Delay a little bit to improve simulation performance
}

int getLength() {
    return sizeof(streakArray) / sizeof(streakArray[0]);
}

void addTask(String newTask) {
    // Check if there's space to add a new task
    if (currentLength >= maxLength) {
        Serial.println("Cannot add more tasks, array is full!");
        return;
    }

    // Add the new task to the next empty slot in the arrays
    taskArray[currentLength] = newTask;
    streakArray[currentLength] = 0;

    // Increment the current length
    currentLength++;
}

void remove() {
    // Check if there are tasks to remove
    if (currentLength == 0) {
        Serial.println("No tasks to remove!");
        return;
    }

    // Remove the last task added
    taskArray[currentLength - 1] = "";
    streakArray[currentLength - 1] = 0;

    // Decrement the current length
    currentLength--;
}
