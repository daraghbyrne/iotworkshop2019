# Step 10: On/Off


I'm sure we won't always want our weather viz on! Let's use the push button to turn off the visualization for a bit.

Let's make a quick change to toggle on and off the visualisation.  All of these changes will go into our `loop()`

First we'll need to read in our button. Add this line to the top of the loop. It'll see if the button is pushed by checking for power on the button pin

````
// Track if it's on or off
bool appState = true;

// store the last value the button registered
bool previousButtonState = LOW;

````

Next, if the button is pushed (reading `LOW`) then we want to toggle it on or off like so

````
  if( buttonState != previousButtonState && buttonState == LOW )
  {

    appState = !appState;
		
    if( appState == HIGH ){
      Particle.publish( "iot-workshop-2018/ambient/status", "toggledOn" );
    }else{
      Particle.publish( "iot-workshop-2018/ambient/status", "toggledOff" );
    }

  }		

````

As a bonus you can also publish the toggle to see it unfold!

Then finally we just decide if we should display the change or nothing at all based on the variable `ledState`. Modify the loop to wrap `displayChange()`  in an `if` statement like so

````

  if( !appState ){
    setRGBColor( 0,0,0 );

  }else{

    checkForRefresh();

    if( isLoading ) {
      digitalWrite( ledPin, HIGH );
      delay( 100 );
      digitalWrite( ledPin, LOW );
    }

    displayChange();
  }

````

And you're done!

Compile, flash and try it out! Push the button, dial the knob and find out what the markets are like for bitcoin!

Nice work. 