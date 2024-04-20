// include the library code:
#include <LiquidCrystal.h>

#define C4 261
#define D4 293
#define E4 329
#define F4 349
#define G4 392
#define A4 440
#define B4 493
#define C5 523
#define E5 659

#define quarter 400
#define half 800
#define eighth 200

const unsigned long interval = 10000; // 86400000 Interval in milliseconds (e.g., 60000 ms = 1 minute)
const unsigned long notificationTime = 5000;
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int buttonStateOne = 0;
int buttonStateTwo = 0;
int buttonStateThree = 0;
int buttonStateFour = 0;
int buttonStateFive = 0;

int currentIndex = 0;

const int maxLength = 10;           // Maximum length of the arrays
String taskArray[maxLength];        // Array to hold tasks
int streakArray[maxLength];         // Array to hold streaks
long startedStreakTimes[maxLength]; // The times when the task has last been done
int currentLength = 0;              // Variable to keep track of current length

void setup() {
    Serial.begin(9600);

    lcd.begin(16, 2);

    pinMode(6, INPUT);
    pinMode(7, INPUT);
    pinMode(8, INPUT);
    pinMode(9, INPUT);
    pinMode(10, INPUT);
    pinMode(13, OUTPUT);
    pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {

    buttonStateFour = digitalRead(7);
    buttonStateFive = digitalRead(6);
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

    checkTaskTimers();

    // Button 1 (Previous Task Button)
    if (buttonStateOne == HIGH) { // Button = Pressed

        currentIndex--;

        if (currentIndex == -1) {
            currentIndex = currentLength - 1;
        }

        currentTask = taskArray[currentIndex];

        currentStreak = streakArray[currentIndex];
    }

    // Button 2 (Next Task Button)
    if (buttonStateTwo == HIGH) { // Button = Pressed

        currentIndex++;

        if (currentIndex == currentLength) {
            currentIndex = 0;
        }

        currentTask = taskArray[currentIndex];

        currentStreak = streakArray[currentIndex];
    }

    // Button 3 (Increase Streak Counter Button)
    if (buttonStateThree == HIGH) { // Button = Pressed
        streakArray[currentIndex]++;
        startedStreakTimes[currentIndex] = millis();
    }

    // Button 4 (Add Task Button)
    if (buttonStateFour == HIGH) {
        addTask();
    }

    // Button 5 (Remove Task Button)
    if (buttonStateFive == HIGH) { // Button = Pressed
        removeTask();
    }

    delay(120); // Delay a little bit to improve simulation performance
}

int getLength() {
    return sizeof(streakArray) / sizeof(streakArray[0]);
}

void addTask() {

    Serial.println("Enter new task:");
    while (Serial.available() == 0) {
    }

    // Get task name from user
    String newTask = Serial.readString();
    newTask.trim();
    Serial.println(newTask);

    // Check if there's space to add a new task
    if (currentLength >= maxLength) {
        Serial.println("Cannot add more tasks, array is full!");
        return;
    }

    // Add the new task to the next empty slot in the arrays
    taskArray[currentLength] = newTask;
    streakArray[currentLength] = 0;
    startedStreakTimes[currentLength] = millis();
    // Increment the current length
    currentLength++;
}

void removeTask() {
    // Display available tasks to remove
    for (int i = 0; i < currentLength; i++) {
        Serial.println(i + 1 + taskArray[i]);
    }
    Serial.println("Enter id to remove task:");
    int id = Serial.parseInt();

    // Check if there are tasks to remove
    if (currentLength == 0) {
        Serial.println("No tasks to remove!");
        return;
    }

    // Remove the last task added
    taskArray[id - 1] = "";
    streakArray[id - 1] = 0;

    // Shift all elements after the removed element one index left
    for (int i = id; i < currentLength - 1; i++) {
        taskArray[i] = taskArray[i + 1];
        streakArray[i] = streakArray[i + 1];
    }

    // Decrement the current length
    currentLength--;
}

// Function to play a note with a specific duration
void playTone(int frequency, int duration) {
    tone(13, frequency, duration); // Play tone on pin 8
    delay(duration);               // Add a small delay for spacing between notes
}

void TetrisTheme() {
    // Play Tetris theme melody
    playTone(E4, quarter);
    playTone(B4, quarter);
    playTone(C5, half);
    playTone(A4, eighth);
    playTone(G4, eighth);
    playTone(F4, half);

    playTone(E4, quarter);
    playTone(B4, quarter);
    playTone(C5, half);
    playTone(A4, eighth);
    playTone(G4, eighth);
    playTone(F4, half);

    playTone(E4, quarter);
    playTone(B4, quarter);
    playTone(C5, half);
    playTone(E5, eighth); // E5 (high E note)
    playTone(C5, eighth);
    playTone(B4, half);

    playTone(A4, quarter);
    playTone(F4, quarter);
    playTone(G4, half);
    playTone(E4, eighth);
    playTone(G4, eighth);
    playTone(A4, half);

    delay(1000);
}

void checkTaskTimers() {
    // Get the current time
    unsigned long currentMillis = millis();
    // Serial.println(currentMillis);
    for (int i = 0; i < currentLength; i++) {
        // Serial.println(startedStreakTimes[i]);
        if (currentMillis - startedStreakTimes[i] >= interval && streakArray[i] != 0) { // Check if timer has ran out
            streakArray[i] = 0;                                                         // Decrease the streak
            // Streak not increased in time, trigger EyeOfTheTiger()
            Serial.println("Timer ran out!!!" + taskArray[i]);
        } else if (currentMillis - startedStreakTimes[i] >= interval - notificationTime && streakArray[i] != 0) {
            TetrisTheme();
        }
    }
}
