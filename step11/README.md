# Step 10: Fine Tuning 

One minor problem, now our Ambient Orb will immediately jump to the color instead of slowly fading to the color. We want it to be ambient. 

In our ideal solution, it should gradually from the current color to the color of the new data point. This is what we'll do in our final step.


First create some new variables, so that we can separate the currently displayed color from the ideal target color

````
int targetRed = 0;
int targetGreen = 0;
int targetBlue = 0;

````

In some cases, like changing the currency or when the microcontroller first loads, we'll want to display the color immediately instead of just fading to it. We should handle this. So, we'll also create a variable to know when this is the case. Add the following to the top of your code:

````
bool displayImmediately = true;
````

By setting it to true, this meand that when our microcontroller boots up, our first data is immediatey displayed and not faded.


Modify `getData` to also set `displayImmediately` to `true`. Add this line before the end

````
void getData()
{
  ...
  displayImmediately = true;
  isLoading = true;
}
````


Now we'll need to handle the fading in. Add this function to our code:

````
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

````

We'll also need to modify our loop to add this in, and control the feedback. Modify the `loop()` to add a call to it

````
void loop()
{
...
    // finally display the change 
    // in currency
    displayChange();
    fadeToTargetColors();
  }
  
  delay( 100 );

}

````

And last but not least, let's modify `displayChange()` to handle the new approach:

````
void displayChange()
{

	...
 
  targetRed = color ;
  targetGreen = 0;
  targetBlue =  255 - color;
  
  if( !isLoading && displayImmediately ){
      
    setRGBColor( targetRed , 0, targetBlue );
    displayImmediately = false;
      
  }



}
````

And that's it. Flash your code and you're done!