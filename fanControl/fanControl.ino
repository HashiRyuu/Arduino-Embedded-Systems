const int tachPin = 2;
const int blue = 3;

volatile unsigned long pulseCount = 0;

void countPulse() {
  pulseCount++;
}

void setup() {
  Serial.begin(9600);

  pinMode(tachPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(tachPin), countPulse, FALLING);
}

void loop() {
  noInterrupts();
  pulseCount = 0;
  interrupts();

  delay(2000);

  noInterrupts();
  unsigned long pulses = pulseCount;
  interrupts();

  float seconds = 2.0;
  float rpm = (pulses / 2.0) * (60.0 / seconds);

  Serial.print("Pulses: ");
  Serial.print(pulses);
  Serial.print("   RPM: ");
  Serial.println(rpm);
}