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

  Particle.subscribe("hook-response/bitcoin", handleBitcoinPriceReceived, MY_DEVICES);

	getData();

}

void loop()
{


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
