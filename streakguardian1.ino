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

String taskArray[] = {"Duolingo","Workout","Walk the dogs"};
int streakArray[] = {0,0,0};
int current = 0;

void setup() {
  
  
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
  
  
  String currentTask = taskArray[current];
  int currentStreak = streakArray[current];
  
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
    
    current--;
    
     if(current == -1){
      current =  3 - 1; 
    }
   
    currentTask = taskArray[current];
    
    currentStreak = streakArray[current];
  } 
  
  // Button 2
  if (buttonStateTwo == HIGH) {
    // turn LED on
    digitalWrite(LED_BUILTIN, HIGH);
    
    current++;
    
    if(current == 3){
      current = 0; 
    }
    
    currentTask = taskArray[current];
    
    currentStreak = streakArray[current];
  } else {
    // turn LED off
    digitalWrite(LED_BUILTIN, LOW);
  }
  
  
  // Button 3
  if (buttonStateThree == HIGH) {
    // turn LED on
    digitalWrite(LED_BUILTIN, HIGH);
    
    streakArray[current]++;
    
  } else {
    // turn LED off
    digitalWrite(LED_BUILTIN, LOW);
  }
  
  delay(200); // Delay a little bit to improve simulation performance

}



