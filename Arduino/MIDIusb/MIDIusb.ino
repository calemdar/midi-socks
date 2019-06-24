#include "MIDIUSB.h"

// Global Variables
int square_sensor_pin = A9;
int flex_sensor_pin = A10;
bool pressed_square, pressed_circle = false;
int max_flex_value = 1;
int note1 = 48; // key values between 0-127
int note2 = 50;
int velocity = 64; //veocity range 0-127

// First parameter is the event type (0x09 = note on, 0x08 = note off).
// Second parameter is note-on/note-off, combined with the channel.
// Channel can be anything between 0-15. Typically reported to the user as 1-16.
// Third parameter is the note number (48 = middle C).
// Fourth parameter is the velocity (64 = normal, 127 = fastest).

void noteOn(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOn = {0x09, 0x90 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOn);
}

void noteOff(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOff = {0x08, 0x80 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOff);
}

void setup() {
  Serial.begin(9600);
  Serial.println("Started");

}

bool readSquareSensor() {
  int value, prev_value = 0;
  value = analogRead(square_sensor_pin);
  if(value > prev_value + 10){
    pressed_square = true;
    prev_value = value;
    max_flex_value = 1;
  } else {
      prev_value = value;
      readFlexSensor();
      pressed_square = false;
  }
  return pressed_square;
}

// reads analog input and returns true if the sensor is being pressed
bool readCircleSensor() {
  int value, prev_value = 0;
  value = analogRead(circle_sensor_pin);
  if(value > prev_value + 10){
    pressed_circle = true;
    prev_value = value;
    max_flex_value = 1;
  } else {
      prev_value = value;
      readFlexSensor();
      pressed_circle = false;
  }
  return pressed_circle;
}

bool readFlexSensor() {
  for(int i = 0; i < 100; i++){
    flex_value = analogRead(flex_sensor_pin);
    if(flex_value > max_flex_value){
      max_flex_value = value;
    }
  }
  Serial.println("Flex value: ");
  Serial.println(max_flex_value);
  velocity = 64 + (max_flex_value / 50);
}

// First parameter is the event type (0x0B = control change).
// Second parameter is the event type, combined with the channel.
// Third parameter is the control number number (0-119).
// Fourth parameter is the control value (0-127).

void controlChange(byte channel, byte control, byte value) {
  midiEventPacket_t event = {0x0B, 0xB0 | channel, control, value};
  MidiUSB.sendMIDI(event);
}

void loop() {
  
  Serial.println("Velocity: ");
  Serial.println(velocity);
  if(readSquareSensor()){
    Serial.println("Sending note: ");
    Serial.println(note1);
    noteOn(0, note1, velocity);   // Channel 0, middle C, normal velocity
    MidiUSB.flush();
  }
  else{
    Serial.println("Stop sending note");
    Serial.println(note1);
    noteOff(0, note1, velocity);  // Channel 0, middle C, normal velocity
    MidiUSB.flush();
  }
  
  delay(300);
  // controlChange(0, 10, 65); // Set the value of controller 10 on channel 0 to 65
}
