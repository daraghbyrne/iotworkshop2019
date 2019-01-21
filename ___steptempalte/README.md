

To make this circuit you need a Particle microcontroller, an LED, a 1KΩ resistor (brown, black, red)
Along your Particle device you will see a series of PINs or legs labeled D0 to D7. These are the digitalPins which can be used for input or output. In this case we’ll be using them for output or to turn power on and off to make the LED blink.
First connect your resistor to D0 and the other lead to a row on the resistor.
Next add an LED with the anode (longer leg) to the row where the resistor connects. The pin at D0 will provide power when it is turned on.
Next we need to connect the cathode to ground. Use your jumper wires to make a connection to the negative column of the power rail (marked in with the blue line)
Finally, near the GND pin use another jumper cable to connect it to the power rail as shown. Now we have a complete circuit where power from Pin D0 will always flow to ground.
