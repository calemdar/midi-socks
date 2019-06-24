int input_pin = A9;
int value, prev_value, pressure = 0;
bool pressed = false;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Started");
}

void loop() {
  // put your main code here, to run repeatedly:
  value = analogRead(input_pin);
  Serial.println(value);

  if(value > prev_value + 10){
    
    prev_value = value;
    pressed = true;
    pressure += 10;
    Serial.print("Recorded value: ");
    Serial.println(prev_value);
    Serial.print("Pressure value: ");
    Serial.println(pressure);
    Serial.print("Pressed? ");
    Serial.println(pressed);

  } else {
    if(pressure > 0){
      pressure -= 10;
    }
    
    prev_value = value;
    pressed = false;
  }
  delay(100);
}
