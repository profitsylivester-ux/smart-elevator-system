// Add the LiquidCrystal library and set up LCD screen on Pins 11-12 and 2-5
// Buttons for floor selection:
// - Basement button on Pin 7
// - Ground Floor button on Pin 8
// - Floor 1 button on Pin 9
// - Floor 2 button on Pin 13
// Buzzer on Pin 10 (plays soft modern elevator tone when reaching floor)
// Servo motor on Pin 6 (shows floor position by rotation angle)
// Current floor starts at Ground Floor (0)

#include <LiquidCrystal.h>
#include <Servo.h>

// Initialize LCD with pins (RS, E, DB4, DB5, DB6, DB7)
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// Initialize servo motor on pin 6
Servo elevatorServo;
int servoPin = 6;

// Define button pins for each floor
int basementButton = 7;    // Basement button
int groundButton = 8;      // Ground Floor button
int floor1Button = 9;      // Floor 1 button
int floor2Button = 13;     // Floor 2 button

// Buzzer pin for arrival tone
int buzzerPin = 10;

// Track current floor and destination
// 0 = Ground, -1 = Basement, 1 = Floor 1, 2 = Floor 2
int currentFloor = 0;      // Start at Ground Floor
int floorDestination = 0;

// Servo angles for each floor (adjust these to match your setup)
int basementAngle = 0;    // Basement: 0 degrees
int groundAngle = 60;      // Ground Floor: 60 degrees (middle)
int floor1Angle = 90;     // Floor 1: 90 degrees
int floor2Angle = 180;     // Floor 2: 180 degrees

void setup() {
  // Set up all floor buttons as inputs
  pinMode(basementButton, INPUT);
  pinMode(groundButton, INPUT);
  pinMode(floor1Button, INPUT);
  pinMode(floor2Button, INPUT);
  
  // Set up buzzer as output
  pinMode(buzzerPin, OUTPUT);
  
  // Attach servo motor to pin 6
  elevatorServo.attach(servoPin);
  
  // Move servo to starting position (Ground Floor)
  elevatorServo.write(groundAngle);
  
  // Set up LCD dimensions (16 columns, 2 rows)
  lcd.begin(16, 2);
  
  // Display starting floor when LCD turns on
  lcd.print("Ground Floor");
}

void loop() {
  lcd.setCursor(0, 0);
  
  // Check if Basement button is pressed
  if (digitalRead(basementButton) == HIGH) {
    if (currentFloor != -1) {  // Only move if not already in basement
      moveToFloor(-1, "Basement", basementAngle);
    }
  }
  
  // Check if Ground Floor button is pressed
  else if (digitalRead(groundButton) == HIGH) {
    if (currentFloor != 0) {  // Only move if not already on ground
      moveToFloor(0, "Ground Floor", groundAngle);
    }
  }
  
  // Check if Floor 1 button is pressed
  else if (digitalRead(floor1Button) == HIGH) {
    if (currentFloor != 1) {  // Only move if not already on floor 1
      moveToFloor(1, "Floor 1", floor1Angle);
    }
  }
  
  // Check if Floor 2 button is pressed
  else if (digitalRead(floor2Button) == HIGH) {
    if (currentFloor != 2) {  // Only move if not already on floor 2
      moveToFloor(2, "Floor 2", floor2Angle);
    }
  }
}

// Helper function to play soft modern elevator "ding" tone
void playArrivalTone() {
  tone(buzzerPin, 2000, 80);   // High clear tone: 2000Hz for 80ms
  delay(400);                   // Wait for tone to finish
}

// Helper function to move elevator to target floor
// Shows "Floors Changing", intermediate floors, and rotates servo smoothly
void moveToFloor(int target, String floorName, int targetAngle) {
  lcd.setCursor(0, 1);
  lcd.print("Floors Changing");
  
  // Show intermediate floors when moving multiple floors
  // From Floor 2 down to Ground: show Floor 1
  if (currentFloor == 2 && target == 0) {
    delay(1000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Floor 1");
    delay(1000);
  }
  
  // From Floor 2 down to Basement: show Floor 1 and Ground
  if (currentFloor == 2 && target == -1) {
    delay(1000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Floor 1");
    delay(1000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Ground Floor");
    delay(1000);
  }
  
  // From Floor 1 down to Basement: show Ground
  if (currentFloor == 1 && target == -1) {
    delay(1000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Ground Floor");
    delay(1000);
  }
  
  // From Ground up to Floor 2: show Floor 1
  if (currentFloor == 0 && target == 2) {
    delay(1000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Floor 1");
    delay(1000);
  }
  
  // From Basement up to Floor 1: show Ground
  if (currentFloor == -1 && target == 1) {
    delay(1000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Ground Floor");
    delay(1000);
  }
  
  // From Basement up to Floor 2: show Ground and Floor 1
  if (currentFloor == -1 && target == 2) {
    delay(1000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Ground Floor");
    delay(1000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Floor 1");
    delay(1000);
  }
  
  // Final delay and display target floor
  delay(1000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(floorName);
  
  // Rotate servo smoothly to target floor angle
  elevatorServo.write(targetAngle);
  
  // Update current floor
  currentFloor = target;
  
  // Play soft modern elevator tone when reaching the floor
  playArrivalTone();
}