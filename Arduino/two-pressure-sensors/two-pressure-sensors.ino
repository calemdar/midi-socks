#include "MIDIUSB.h"

// Global Variables
int square_sensor_pin = A9;
int circle_sensor_pin = A10;
int square_value, square_prev_value = 0;
int circle_value, circle_prev_value = 0;
bool pressed_square, pressed_circle = false;
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

//compares current value to previous value recorded. Returns true 
//if the change in value is greater than a certain value
bool readSquareSensor() {
  square_value = analogRead(square_sensor_pin);
  Serial.println("Square Value: ");
  Serial.println(square_value);
  Serial.println("##########################");
  if(square_value > square_prev_value + 200){
    square_prev_value = square_value;
    return true;
  } else {
      square_prev_value = square_value;
      pressed_square = false;
      return false;
  }
}

//compares current value to previous value recorded. Returns true 
//if the change in value is greater than a certain value
bool readCircleSensor() {
  circle_value = analogRead(circle_sensor_pin);
  Serial.println("Circle Value: ");
  Serial.println(circle_value);
  Serial.println("000000000000000000000");
  if(circle_value > circle_prev_value + 100){
    circle_prev_value = circle_value;
    return true;
  } else {
      circle_prev_value = circle_value;
      pressed_circle = false;
      return false;
  }
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
 
  /*
   * Check square sensor
   */
  if(readSquareSensor() && pressed_square == false){
    Serial.println("Sending square note: ");
    Serial.println(note1);
    noteOn(1, note1, velocity);   // Channel 1, middle C, normal velocity
    pressed_square = true;
  }
  else if(pressed_square == false){
    //Serial.println("Stop sending notes");
    noteOff(1, note1, 0);  // Channel 1, middle C, normal velocity
  }
  /*
   * Check circle sensor
   */
  if(readCircleSensor() && pressed_circle == false){
    Serial.println("Sending circle note: ");
    Serial.println(note2);
    noteOn(2, note2, velocity);   // Channel 0, middle C, normal velocity
    pressed_circle = true;
  }
  else if(pressed_circle == false){
    //Serial.println("Stop sending notes");
    noteOff(2, note2, 0);
  }
  
  MidiUSB.flush();
  delay(300);
  // controlChange(0, 10, 65); // Set the value of controller 10 on channel 0 to 65
}
