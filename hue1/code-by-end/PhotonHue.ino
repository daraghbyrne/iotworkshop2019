int redPin = D0;    // RED pin of the LED to PWM pin **A0**
int greenPin = D1;  // GREEN pin of the LED to PWM pin **D0**
int bluePin = D2;   // BLUE pin of the LED to PWM pin **D1**
int redValue = 255; // Full brightness for an ANODE RGB LED is 0, and off 255
int greenValue = 255; // Full brightness for an ANODE RGB LED is 0, and off 255
int blueValue = 255; // Full brightness for an ANODE RGB LED is 0, and off 255</td>

// Our button wired to D0
int buttonPin = D4;

// store the last value the button registered
bool previousButtonState = LOW;

// Define a pin that we'll place the pot on
int potPin = A0;
// Create a variable to hold the pot reading
int potReading = 0;

// status ledPin
int ledPin = D3;
int ledValue = 255;


// store the current application
// is it progrmatically on or off
bool currentHueState = LOW;


void setup()
{
  // Set up our pins for output
  pinMode( redPin, OUTPUT);
  pinMode( greenPin, OUTPUT);
  pinMode( bluePin, OUTPUT);

  pinMode( ledPin, OUTPUT);

  // For input, we define the
  // pushbutton as an input-pullup
  // this uses an internal pullup resistor
  // to manage consistent reads from the device

  pinMode( buttonPin , INPUT_PULLUP); // sets pin as input

  // Create a cloud variable of type integer
  // called 'light' mapped to photoCellReading
  Particle.variable("pot", potReading );
  Particle.variable("r", redValue );
  Particle.variable("g", greenValue );
  Particle.variable("b", blueValue);

  Particle.variable("isOn", currentHueState );

  //Register our Particle function here
  Particle.function("ledR", changeR);
  Particle.function("ledG", changeG);
  Particle.function("ledB", changeB );

  Particle.function("state", changeState );

  Particle.subscribe( "iot-workshop/hue/setcolor", handleSetColor );

  // turn them all off...
  analogWrite( redPin, redValue);
  analogWrite( greenPin, greenValue);
  analogWrite( bluePin, blueValue);

}

void loop()
{

    int buttonState = digitalRead( buttonPin );

    if( buttonState != previousButtonState )
    {
      currentHueState = !currentHueState;

      if( currentHueState == HIGH ){
        Particle.publish( "iot-workshop-2018/hue/status", "ON" );
        updateColorLED();

      }else{
        Particle.publish( "iot-workshop-2018/hue/status", "OFF" );
      }

    }
    previousButtonState = buttonState;


    if( currentHueState == LOW ){
        offColorLED( );
    }else{
      int currentVal = analogRead( potPin );
      if( abs( currentVal - potReading ) > 10 ) {
        int val = map(potReading , 0, 4095, 0, 255 );
        wheel( val );
        updateColorLED();
        potReading = currentVal;
      }
    }



    // wait 1 second
    delay( 1000 );
}

void handleSetColor(const char *event, const char *data)
{
    blinkStatusLED();

    currentHueState = HIGH;

    String colors[3];
    colors[0]="";
    colors[1]="";
    colors[2]="";

    String colorString = String( data );

    int index = 0;
    for( int i = 0; i < colorString.length(); i++ )
    {
      if( index < 3 ){
        char c = colorString.charAt(i);
        colors[index] += c;

        if( c == ',') index++;
      }
    }

    // get the red component...
    redValue = colors[0].toInt();
    // now green
    greenValue = colors[1].toInt();
    // now blue
    blueValue = colors[2].toInt();

    updateColorLED();


}

void blinkStatusLED(){

  for( int i = 0 ; i < 3; i++){
    digitalWrite(ledPin, HIGH);
    delay( 100 );
    digitalWrite(ledPin, LOW);
    delay( 100 );
  }

}

void updateColorLED( ){
  //RGB.color( redValue,greenValue,blueValue);
  analogWrite(redPin, 255 - redValue);
  analogWrite(greenPin, 255 - greenValue);
  analogWrite(bluePin, 255 - blueValue);

}
void offColorLED( ){

  analogWrite(redPin, 255);
  analogWrite(greenPin, 255);
  analogWrite(bluePin, 255);
}



int changeState( String command )
{
  command = command.toUpperCase();
  blinkStatusLED();

  if( command.equals( "ON" ) || command.equals( "HIGH" ) ){
    currentHueState = HIGH;
    Particle.publish( "iot-workshop-2018/hue/status", "ON" );
    updateColorLED();
    return 1;
  }

  if( command.equals( "OFF" ) || command.equals( "LOW" ) ){
    currentHueState = LOW;
    Particle.publish( "iot-workshop-2018/hue/status", "OFF" );

  }

  return -1;
}

int changeR( String command )
{
    // get the red component...
    int colorValue = command.toInt();

   // write the mixed color
   redValue = colorValue;
   blinkStatusLED();
   updateColorLED();
   return 1;
}

int changeB( String command )
{
    // get the red component...
    int colorValue = command.toInt();
    blinkStatusLED();

   // write the mixed color
   blueValue = colorValue;
   updateColorLED();

   return 1;
}

int changeG( String command )
{
    // get the red component...
    int colorValue = command.toInt();
    blinkStatusLED();

   // write the mixed color
   greenValue = colorValue;
   updateColorLED();

   return 1;
}


// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t wheel(byte WheelPos) {
  if(WheelPos < 85) {
    redValue = WheelPos * 3;
    greenValue = 255 - WheelPos * 3;
    blueValue = 0;
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   redValue = 255 - WheelPos * 3;
   greenValue = 0;
   blueValue = WheelPos * 3;
  } else {
   WheelPos -= 170;
   redValue = 0;
   greenValue = WheelPos * 3;
   blueValue = 255 - WheelPos * 3;
  }
}
