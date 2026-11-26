// Define Pins
#define BLUE 3
#define GREEN 5
#define RED 6
#define buttonA 9

void setup() {
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  pinMode(buttonA, INPUT_PULLUP);
  Serial.begin(9600);
}

// Define variables
int redValue;
int greenValue;
int blueValue;
int count = 0;
bool check = false;
bool buttonPressed = false;
unsigned long lastDebounceTime = 0; // For debouncing
const unsigned long debounceDelay = 100; // Adjust debounce delay if needed

// Main loop
void loop() {
  #define delayTime 20 // Fading time between colors
  redValue = 0;
  greenValue = 0;
  blueValue = 0;
  
  int pressA = digitalRead(buttonA);
  //Serial.println(pressA);

  // Debounce logic
  if (pressA == LOW && !buttonPressed && (millis() - lastDebounceTime > debounceDelay)) {
    count++;
    buttonPressed = true;
    lastDebounceTime = millis(); // Reset debounce timer
    
    // Toggle `check` every time button is pressed
    if (count % 2 != 0) {
      check = true;
    } else {
      check = false;
    }
  } else if (pressA == HIGH) {
    buttonPressed = false;
  }

  // Set LED color based on `check`
  
  if (check) {
    for(int i = 0; i <= 255; i++)
    {
    int pressZ = digitalRead(buttonA); // Continuously read the button state
    if (pressZ == LOW) break; // Exit the loop if the button is pressed
    analogWrite(RED, i);
    analogWrite(GREEN, 255 - i);
    analogWrite(BLUE, i);
    delay(10);
    }
    for(int i = 255; i >= 0; i--)
    {
    int pressZ = digitalRead(buttonA); // Continuously read the button state
    if (pressZ == LOW) break; // Exit the loop if the button is pressed
    analogWrite(RED, i);
    analogWrite(GREEN, 255 - i);
    analogWrite(BLUE, i);
    delay(10);
    }
  } else {
    analogWrite(RED, 0);
    analogWrite(GREEN, 155);
    analogWrite(BLUE, 0);
  }

  delay(delayTime);
}
