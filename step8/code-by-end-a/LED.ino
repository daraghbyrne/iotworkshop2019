
int redPin = D0;    // RED pin of the LED to PWM pin **A0**
int greenPin = D1;  // GREEN pin of the LED to PWM pin **D0**
int bluePin = D2;   // BLUE pin of the LED to PWM pin **D1**
int redValue = 255; // Full brightness for an ANODE RGB LED is 0, and off 255
int greenValue = 255; // Full brightness for an ANODE RGB LED is 0, and off 255
int blueValue = 255; // Full brightness for an ANODE RGB LED is 0, and off 255</td>



// Define a pin we'll place an LED on
int ledPin = D3;

// Our button wired to D0
int buttonPin = D4;

// Define a pin that we'll place the pot on
int potPin = A0;

// Create a variable to hold the pot reading
int potReading = 0;

String weatherIcon = "";
double temperature = 0;
double precipProbability = 0;
double precipIntensity = 0;

// Store the last time 
// the webhook was called 
long lastData = 0;


void setup()
{
  // Set up the LED for output
  pinMode(ledPin, OUTPUT);


  // Set up our RGB LED pins for output
  pinMode( redPin, OUTPUT);
  pinMode( greenPin, OUTPUT);
  pinMode( bluePin, OUTPUT);


  // For input, we define the
  // pushbutton as an input-pullup
  // this uses an internal pullup resistor
  // to manage consistent reads from the device

  pinMode( buttonPin , INPUT_PULLUP); // sets pin as input

  // Create a cloud variable of type integer
  // called 'dial' mapped to potReading

  Particle.variable("dial", &potReading, INT);

  Particle.subscribe("hook-response/forecast", handleForecastReceived, MY_DEVICES);
	
	// make the temperature values visible online
  Particle.variable("temp", &temperature, DOUBLE );
	
	getData();
	
}

void loop()
{
	checkForRefresh();

	displayTemperature();
	
  delay( 100 );
	

}

// Note that
// Full brightness for an ANODE RGB LED is 0, and off 255
// So we set our RGB values to be 255 - value (invert them)

void setRGBColor( int r, int g, int b ){

  redValue = r;
  greenValue = g;
  blueValue = b;

  analogWrite(redPin, 255 - redValue);
  analogWrite(greenPin, 255 - greenValue);
  analogWrite(bluePin, 255 - blueValue);
}

void checkForRefresh(){

  // has it been 10 minutes since we last updated
  if( lastData == 0 or lastData + 600000 < millis() )
  {
		// get data from the webhook
    getData();
		// if we're refreshing, set the time we last called the webhook to now
    lastData = millis();
  }
}


void getData()
{
	// Publish an event to trigger the webhook
	  Particle.publish("forecast", "40.4406,-79.9959", PRIVATE);
}



void displayTemperature()
{
	// the temperature from 40-80F into the color range of 0-255
  int tCol = map( (int)(temperature), 40, 80 , 0 , 255 );
	// make sure its in that range
	// not bigger or smaller!
  tCol = constrain( tCol, 0, 255 );

	// map the color in.
	// if t is high so is Red
	// if t is low, blue is high

  setRGBColor( tCol , 0, 255 - tCol );
}


void handleForecastReceived(const char *event, const char *data) {
  // Handle the integration response

  String receivedStr =  String( data );
  int loc1 = 0;
  int loc2 = 0;
  int loc3 = 0;
  int loc4 = 0;

  loc1 = receivedStr.indexOf("~");

  weatherIcon = receivedStr.substring(0,loc1);

  loc2 = receivedStr.indexOf("~",loc1+1);
  temperature = (double) String(receivedStr.substring(loc1+1,loc2)).toFloat();

  loc3 = receivedStr.indexOf("~",loc2+1);
  precipProbability = (double) String(receivedStr.substring(loc2+1,loc3)).toFloat();

  loc4 = receivedStr.indexOf("~",loc3+1);
  precipIntensity = (double) String(receivedStr.indexOf(loc3+1)).toFloat();


}