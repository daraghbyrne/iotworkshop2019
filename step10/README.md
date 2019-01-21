# Step 10: Fine Tuning - On/Off


I'm sure we won't always want our weather viz on! Let's use the push button to turn off the visualization for a bit.

Let's make a quick change to toggle on and off the visualisation.  All of these changes will go into our `loop()`

First we'll need to read in our button. Add this line to the top of the loop. It'll see if the button is pushed by checking for power on the button pin

````
  int buttonState = digitalRead( buttonPin );
````

Next, if the button is pushed (reading `LOW`) then we want to toggle it on or off like so

````
	// Set the button value to 
	// tell us if the app should be on or off
    appState = buttonState;

````

Then finally we just decide if we should display the temperature or nothing at all based on the variable `ledState`. Modify the loop to wrap `displayTemperature()`  in an `if` statement like so

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

    displayTemperature();
  }

````

And you're done!

Compile, flash and try it out! Push the button, dial the knob and find out what the weather's like around the world. 

Nice work. 