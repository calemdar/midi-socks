# Midi Socks
This project is a MIDI instrument that transmits MIDI notes using two pressure sensors

# Hardware
1 Flora Microcontroller
2 Sparkfun FSR pressure sensor
Stainless thin conductive thread
Resistors
USB cable

# How it works:

The Flora microcontroller detects if the sensors are being pressed. This is done through Arduino code running in the microcontroller. The Arduino code converts sensory input into a MIDI note and sends it through USB using a library called MIDIUSB. So essentially the Arduino device can be detected as a MIDI instrument. 

# Arduino code:
The code uploaded into the microcontroller is called "two-pressure-sensors". In it you can find more information about how we gather data from the sensors and use it to create MIDI notes.

Current code in Flora: two-pressure-sensor.ino

# How to get input into Ableton:

Since we are transferring MIDI using the USB, we have to use a "Virtual MIDI Bus" to detect the MIDI notes coming from the instrument, and get it as an input to Ableton. Here is a link with all of the information on how to set it up:
https://help.ableton.com/hc/en-us/articles/209774225-Using-virtual-MIDI-buses

# It is in Ableton, now what?

This instrument is essentially a percussion instrument. That's why it would make sense to use it with a drum rack, or a sampler. One of the sensors send a middle C note while the other sends a D note. 

Made by: Cem Alemdar, Alp Piskin, Diana Kumykova
Advised by: VJ Manzo
