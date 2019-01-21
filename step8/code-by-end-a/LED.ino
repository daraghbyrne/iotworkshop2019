// This #include statement was automatically added by the Particle IDE.
#include <neopixel.h>

// MAIN COMPONENTS

// Define a pin we'll place an LED on
int ledPin = D2;

// Our button wired to D0
int buttonPin = D3;

// Define a pin that we'll place the pot on
int potPin = A5;

// Create a variable to hold the pot reading
int potReading = 0;

// -------- NEOPIXEL


// IMPORTANT: Set pixel COUNT, PIN and TYPE
#define PIXEL_COUNT 1
#define PIXEL_PIN D7
#define PIXEL_TYPE WS2812B
Adafruit_NeoPixel strip(PIXEL_COUNT, PIXEL_PIN, PIXEL_TYPE);

int redValue = 0; // Full brightness for an ANODE RGB LED is 0, and off 255
int greenValue = 0; // Full brightness for an ANODE RGB LED is 0, and off 255
int blueValue = 0; // Full brightness for an ANODE RGB LED is 0, and off 255</td>


// Store the bitcoin readings
double currencyChange = 0;

// Store the last time
// the webhook was called
long lastData = 0;
bool isLoading = false;


void setup()
{
  // Set up the LED for output
  pinMode(ledPin, OUTPUT);


  // Set up our NEOPIXEL RGB Pin pins for output
  strip.begin();

  // For input, we define the
  // pushbutton as an input-pullup
  // this uses an internal pullup resistor
  // to manage consistent reads from the device

  pinMode( buttonPin , INPUT_PULLUP); // sets pin as input

  // Create a cloud variable of type integer
  // called 'dial' mapped to potReading

  Particle.variable("dial", &potReading, INT);
  Particle.variable("change", currencyChange );

  Particle.subscribe("hook-response/bitcoin", handleBitcoinPriceReceived, MY_DEVICES);

	getData();

}

void loop()
{
   checkForRefresh();

   displayChange();

}


// Note that
// Full brightness for an ANODE RGB LED is 0, and off 255
// So we set our RGB values to be 255 - value (invert them)

void setRGBColor( int r, int g, int b ){
  redValue = r;
  greenValue = g;
  blueValue = b;

  strip.setPixelColor(0, redValue, greenValue, blueValue);
  strip.show();
  
}

void getData()
{
	// Publish an event to trigger the webhook
   Particle.publish("bitcoin", "BTC-USD", PRIVATE);
}


void handleBitcoinPriceReceived(const char *event, const char *data) {
  // Handle the integration response

  String receivedStr =  String( data );
  // take the received string
  // convert it to a floating point number
  // then to a double
  currencyChange = (double) receivedStr.toFloat();

  isLoading = false;


}

void checkForRefresh(){

  // has it been 10 minutes since we last updated
  if( lastData == 0 or lastData + 60000 < millis() )
  {
		// get data from the webhook
    getData();
		// if we're refreshing, set the time we last called the webhook to now
    lastData = millis();
  }

  // has the dial changed

  if( abs( analogRead( potPin ) - potReading ) > 10 ){
    int newCurrencyIndex = map(  analogRead( potPin ), 0, 4095, 0, 5 );
    if( newCurrencyIndex != currencyIndex ){
        getData();
    }
  }
  

}



void displayChange()
{
    // the change is in %
    // map takes an integer.
    // lets magnify the change by multipling by 100
    // i.e 1.106% becomes 110.6 
    // and -5.678 becomes -567.8
    // then convert to an integer

   int chnge = (int)(currencyChange * 100 ) ;

   // using map we can convert this into a color range
   // we'll go from 5% to -5%
   int color = map( chnge, -500, 500 , 0 , 255 );
   // make sure its in that range
   // not bigger or smaller!
  
   // switch the axes so a low number = closer to red
   color = 255 - constrain( color, 0, 255 );

   // map the color in.
   // if t is high so is Red
   // if t is low, blue is high
 
   targetRed = color ;
   targetGreen = 0;
   targetBlue =  255 - color;
  
   if( !isLoading && displayImmediately ){
      
     setRGBColor( targetRed , 0, targetBlue );
     displayImmediately = false;
      
   }

}
