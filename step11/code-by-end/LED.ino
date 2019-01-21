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

int targetRed = 0;
int targetGreen = 0;
int targetBlue = 0;

// ----- BITCOIN 

// Store the last time
// the webhook was called
long lastData = 0;

bool isLoading = false;
bool displayImmediately = false;

String currentCurrency = "none";
int currencyIndex = 0;

// Store the bitcoin readings
double currencyChange = 0;

// ----- APP STATE

// Track if it's on or off
bool appState = true;

// store the last value the button registered
bool previousButtonState = LOW;

void setup()
{
  Serial.begin(9600);
    
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

  Particle.variable("dial", potReading);

  Particle.subscribe("hook-response/bitcoin", handleBitcoinPriceReceived, MY_DEVICES);

  // make the currency values visible online
  Particle.variable("change", currencyChange );
  Particle.variable("currency", currentCurrency );


  Particle.variable("r", redValue );
  Particle.variable("g", greenValue );
  Particle.variable("b", blueValue );


  // refresh the bitcoin pricing information
  displayImmediately = true;
  getData();

}

void loop()
{
  int buttonState = digitalRead( buttonPin );

  if( buttonState != previousButtonState && buttonState == LOW )
  {

    appState = !appState;

    if( appState == HIGH ){
      Particle.publish( "iot-workshop-2018/ambient/status", "toggledOn" );
    }else{
      Particle.publish( "iot-workshop-2018/ambient/status", "toggledOff" );
    }

  }
  
  previousButtonState = buttonState;

  if( !appState ){
    setRGBColor( 0,0,0 );

  }else{

    checkForRefresh();

    if( isLoading ) {
      digitalWrite( ledPin, HIGH );
      delay( 100 );
      digitalWrite( ledPin, LOW );
    }

    // finally display the change 
    // in currency
    displayChange();
    fadeToTargetColors();
  }
  
  
  delay( 200 );

}


void fadeToTargetColors( ){
    
    int nextRed = redValue;
    int nextGreen = greenValue;
    int nextBlue = blueValue;
    
    if( redValue < targetRed  ){
        nextRed = redValue + 1;
    }else if( redValue > targetRed ){
        nextRed = redValue - 1;
    }
    
    if( greenValue < targetGreen  ){
        nextGreen = greenValue + 1;
    }else if( greenValue > targetGreen ){
        nextGreen = greenValue - 1;
    }

    if( blueValue < targetBlue  ){
        nextBlue = blueValue + 1;
    }else if( blueValue > targetBlue ){
        nextBlue = blueValue - 1;
    }

    setRGBColor( nextRed, nextGreen, nextBlue );

}


// Note that
// Full brightness for an ANODE RGB LED is 0, and off 255
// So we set our RGB values to be 255 - value (invert them)

void setRGBColor( int r, int g, int b ){

  redValue = constrain( r, 0, 255 );
  greenValue = constrain( g, 0, 255 );
  blueValue = constrain( b, 0, 255 );

  strip.setPixelColor(0, redValue, greenValue, blueValue);
  strip.show();

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


void getData()
{
  Serial.println( "requesting Data" );

  potReading = analogRead( potPin ) ;
  currencyIndex = map( potReading, 0, 4095, 0, 5 );

  if( currencyIndex == 0 ){
    currentCurrency = "Bitcoin";
    Particle.publish("bitcoin", "BTC-USD", PRIVATE);
  }else if( currencyIndex == 1 ){
    currentCurrency = "Ethereum";
    Particle.publish("bitcoin", "ETH-USD", PRIVATE);
  }else if( currencyIndex == 2 ){
    currentCurrency = "Litecoin";
    Particle.publish("bitcoin", "LTC-USD", PRIVATE);
  }else if( currencyIndex == 3 ){
    currentCurrency = "XRP";
    Particle.publish("bitcoin", "XRP-USD", PRIVATE);
  }else if( currencyIndex == 4 ){
    currentCurrency = "Bitcoin Cash";
    Particle.publish("bitcoin", "BCH-USD", PRIVATE);
  }

  Serial.println( currencyIndex );
  displayImmediately = true;
  isLoading = true;
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


void handleBitcoinPriceReceived(const char *event, const char *data) {
  // Handle the integration response

  String receivedStr =  String( data );
  // take the received string
  // convert it to a floating point number
  // then to a double
  currencyChange = (double) receivedStr.toFloat();

  isLoading = false;


}
