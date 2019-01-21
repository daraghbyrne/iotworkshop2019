// This #include statement was automatically added by the Particle IDE.
#include <neopixel.h>

// IMPORTANT: Set pixel COUNT, PIN and TYPE
#define PIXEL_COUNT 1
#define PIXEL_PIN D7
#define PIXEL_TYPE WS2812B
Adafruit_NeoPixel strip(PIXEL_COUNT, PIXEL_PIN, PIXEL_TYPE);

int redValue = 0; // Full brightness for an ANODE RGB LED is 0, and off 255
int greenValue = 0; // Full brightness for an ANODE RGB LED is 0, and off 255
int blueValue = 0; // Full brightness for an ANODE RGB LED is 0, and off 255</td>

// Our button wired to D0
int buttonPin = D3;

// store the last value the button registered
bool previousButtonState = LOW;

// Define a pin that we'll place the pot on
int potPin = A5;
// Create a variable to hold the pot reading
int potReading = 0;

// status ledPin
int ledPin = D2;
int ledValue = 255;


// store the current application
// is it progrmatically on or off
bool currentHueState = HIGH;


void setup()
{
  // Set up our NEOPIXEL RGB Pin pins for output
  strip.begin();

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




}

void loop()
{

    int buttonState = digitalRead( buttonPin );

    if( buttonState != previousButtonState && buttonState == LOW )
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


    if( !currentHueState ){
        offColorLED( );
    }else{
      int currentVal = analogRead( potPin );
      if( abs( currentVal - potReading ) > 15 ) {
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

  strip.setPixelColor(0, redValue, greenValue, blueValue);
  strip.show();

}
void offColorLED( ){

  strip.setPixelColor(0, 0, 0, 0);
  strip.show();
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
