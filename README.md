# III IoT Workshop 2018

An introduction to the internet of things and making a [Particle](http://particle.io) powered Ambient Orb

As part of this workshop you'll have a kit with

- A breadboard
- A Particle Photon
- A Micro USB Cable (use this to power the photon)
- A 10K Potentiometer a.k.a. a dial
- 10K, 1K, 220Ohm Ohm Resistors
- A single 5mm LED (components that make light)
- An RGB LED (common anode) 
- A momentary push button
- A Photocell / photoresistor

By the end of this workshop you'll have built a simple ambient weather visualization using this components. It'll work like this:
- the pushbutton will let you turn the visualization on (displaying) and off (no lights).
- the potentiometer will work like a dial allowing you to select multiple cities 
- in the background, the microcontroller will look up weather data online 
- while it's retrieving data, the LED will blink to let you know
- it'll display temperature information on the device using the inbuilt RGB (full color) LED.
- hot places will be displayed with with a red color (>95F or more) and cool blue will indicate temperatures of 50F or less.
- it'll automatically update every 10 minutes. 


### Step by Step

- Step 1: [Basic LED Circuit](/step1)
- Step 2: [Turn and LED on and Off with a pushbutton](/step2)
- Step 3: [Adding a Potentiometer and Fading the LED](/step3)
- Step 4: [Adding Internet - Seeing Values](/step4)
- Step 5: [Controling Color](/step5)
- Step 6: [Weather Data](/step6)
- Step 7: [Displaying Temperature](/step7)
- Step 8: [Better Loading](/step8)
- Step 9: [Adding Multiple Cities](/step9)
- Step 10: [Fine Tuning - On/Off](/step10)

By the end of this you should have a working Weather Lamp. This is only a starting point. With a little effort, you can easily modify this example to be an ambient orb that visualizes a tonne of different content. It could be adapted to display stock prices, arriving buses, bitcoin trading, slack notifications, inbox zero, and lots more. 

### One Circuit Many Possibilities

- [A Connected Lamp](/hue1)
