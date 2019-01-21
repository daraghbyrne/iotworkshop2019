
# Hue Part 1

With the same components and circuity, we can create lots of different outcomes.

To showcase this, let's adapt the circuit to become a quick open source implementation of Philips Hue

We'll reuse the same components but instead, we'll:

- Use the Potentiometer to select a color 
- The Button will toggle the LED on and off.
- The LED will indicate when remote (from online) changes are being made to the color
- The RGB LED will display the color which can be set by the dial or remotely through the Particle cloud. 

We'll use Particle Cloud in a few ways to enable remote access and customisation of the light : 
- A series of `Particle.variables` to expose the Red, green and Blue values; if the light is on or off, and what the dial is set to.
- `Particle.publish` (events) to announce a change in the state
- `Particle.function` s to allow us to remotely set the red, green and blue components and to turn the lamp on and off.

## Circuit

Zero changes. Literally none.

## Code

The [completed code](code-by-end/PhotonHue.ino) is available in the folder above.

Copy and Paste this into Particle Dev, compile and flash to your photon.

## Try it out

Turn the dial, push the button, open [Particle console](http://console.particle.io) and experiment with setting color!



