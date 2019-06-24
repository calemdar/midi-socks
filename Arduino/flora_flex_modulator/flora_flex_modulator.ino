//Global Variables
int input_pin = A10;
int value, init_value = 0;
float modulate = 0.1;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Started");
}

void loop() {
  // put your main code here, to run repeatedly:
  value = analogRead(input_pin);
  Serial.println(value);
  
  // change is detected if the recorded value is different than our initial value
  if(value < init_value - 20 || value > init_value + 20){  
    modulus(value - init_value);
    Serial.print("Recorded value: ");
    Serial.println(modulate);
  }
  if(modulate > 100 || modulate < 0){
    modulate = 0.0;
    init_value = value;
  }
  delay(50);
}

void modulus(int value) {
  // computes the moduluate number
  if(modulate < 100){
    modulate += (value * 0.1);
  }
}
