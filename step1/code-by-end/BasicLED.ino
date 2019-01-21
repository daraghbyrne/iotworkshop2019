// Define a pin we'll place an LED on
int ledPin = D3;

void setup()
{
  // Set up the LED for output
  pinMode(ledPin, OUTPUT);

}

void loop()
{

  // turn the power on to the LED
  digitalWrite(ledPin, HIGH);
  delay( 1000 ); // wait 1s

  // turn the power off to the LED
  digitalWrite(ledPin, LOW);
  delay( 1000 ); // wait 1s

}
