# Enter your project write-up here!

The Arduino connects to wifi and to Adafruit.io in the setup.

In the loop, the Arduino reconnects to Adafruit.io and reads the button state. If the button is pushed down, the built in LED turns on and a message is sent to Adafruit.io.

Every time a message is sent to the Andium feed in Adafruit.io, IFTTT is triggered and a notification appears on my phone.