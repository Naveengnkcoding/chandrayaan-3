int sensorPin = 5;
int signals = 0;

void setup() {
  Serial.begin(250000);
  pinMode(sensorPin, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(sensorPin, LOW);
}

void loop() {
  unsigned long currentTime = millis();
  int sensorValue = digitalRead(sensorPin);  // Read the sensor value
  if (sensorValue == HIGH) {
    // Get current milliseconds
    digitalWrite(LED_BUILTIN, HIGH);
    // Serial.print(currentTime);
    // Serial.print("Pulse is HIGH and id: ");
    signals++;
    // Serial.println(signals); // Print the current time in milliseconds
  } else {
    Serial.println(sensorValue);
  }
  if (currentTime % 1000 == 0) {
    Serial.print(currentTime);
    Serial.print("count");
    Serial.println(signals);
  }
}
