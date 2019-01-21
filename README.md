# III IoT Workshop 2019

An introduction to the internet of things and making a [Particle](http://particle.io) powered Ambient Orb

As part of this workshop you'll have a kit with

- A breadboard
- A Particle Argon
- A Micro USB Cable (use this to power the Argon)
- A 10K Potentiometer a.k.a. a dial
- 10K, 1K, 220Ohm Ohm Resistors
- A single 5mm LED (components that make light)
- An RGB LED (common anode) 
- A momentary push button
- A Photocell / photoresistor

By the end of this workshop you'll have built a simple ambient bitcoin price visualization using this components. It'll work like this:

- the pushbutton will let you turn the visualization on (displaying) and off (no lights).
- the potentiometer will work like a dial allowing you to select different currencies
- in the background, the microcontroller will look up pricing data online 
- while it's retrieving data, the LED will blink to let you know
- it'll display rate of change information on the device using a Neopixel RGB (full color) LED.
- a 24 hour changes of 5% will be displayed by a cool blue; and if it changes by -5% or more you'll see an angry red.
- it'll automatically update every 1 minutes. 
- it'll fade slowly to the new color 

### Step by Step

- Step 1: [Basic LED Circuit](/step1)
- TODO - Step 2: [Turn and LED on and Off with a pushbutton](/step2)
- TODO - Step 3: [Adding a Potentiometer and Fading the LED](/step3)
- TODO - Step 4: [Adding Internet - Seeing Values](/step4)
- TODO - Step 5: [Controling Color](/step5)
- TODO - Step 6: [Weather Data](/step6)
- TODO - Step 7: [Displaying Temperature](/step7)
- TODO - Step 8: [Better Loading](/step8)
- TODO - Step 9: [Adding Multiple Currencies](/step9)
- TODO - Step 10: [Fine Tuning - On/Off](/step10)

By the end of this you should have a working Ambient Orb . This is only a starting point. With a little effort, you can easily modify this example to be an ambient orb that visualizes a tonne of different content. It could be adapted to display weather, stock prices, arriving buses, slack notifications, inbox count, and lots more. 

### One Circuit Many Possibilities

- [A Connected Lamp](/hue1)
