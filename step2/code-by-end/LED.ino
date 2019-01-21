// Define a pin we'll place an LED on
int ledPin = D3;

// Our button wired to D0
int buttonPin = D4;

void setup()
{
  // Set up the LED for output
  pinMode(ledPin, OUTPUT);

  // For input, we define the
  // pushbutton as an input-pullup
  // this uses an internal pullup resistor
  // to manage consistent reads from the device

  pinMode( buttonPin , INPUT_PULLUP); // sets pin as input

}

void loop()
{
    // find out if the button is pushed
    // or not by reading from it.
    int buttonState = digitalRead( buttonPin );

    // remember that we have wired the pushbutton to
    // ground and are using a pulldown resistor
    // that means, when the button is pushed,
    // we will get a LOW signal
    // when the button is not pushed we'll get a HIGH

    // let's use that to set our LED on or off

    if( buttonState == LOW )
    {
     // turn the LED On
     digitalWrite( ledPin, HIGH);
    }else{
     // otherwise
     // turn the LED Off
     digitalWrite( ledPin, LOW);

    }

}
