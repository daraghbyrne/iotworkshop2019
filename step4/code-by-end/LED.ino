// Define a pin we'll place an LED on
int ledPin = D3;

// Our button wired to D0
int buttonPin = D4;

// Define a pin that we'll place the pot on
int potPin = A0;

// Create a variable to hold the pot reading
int potReading = 0;

// Create a variable to store the LED brightness.
int ledBrightness = 0;

void setup()
{
  // Set up the LED for output
  pinMode(ledPin, OUTPUT);

  // For input, we define the
  // pushbutton as an input-pullup
  // this uses an internal pullup resistor
  // to manage consistent reads from the device

  pinMode( buttonPin , INPUT_PULLUP); // sets pin as input

  // Create a cloud variable of type integer
  // called 'dial' mapped to potReading

  Particle.variable("dial", potReading );

  Particle.variable("brightness", ledBrightness );

	
}

void loop()
{
  // Use analogRead to read the potentiometer reading
  // This gives us a value from 0 to 4095
  potReading = analogRead(potPin);

  // Map this value into the PWM range (0-255)
  // and store as the led brightness
  ledBrightness = map(potReading, 0, 4095, 0, 255);

  // fade the LED to the desired brightness
  analogWrite(ledPin, ledBrightness);

  int buttonState = digitalRead( buttonPin );

	 if( buttonState == LOW )
	 {
	  // turn the LED On
	  Particle.publish( "iveBeenPushed" );
	 }

  // wait 1/10th of a second and then loop
  delay(1000);

}
