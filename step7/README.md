# Step 7: Displaying Data

We're going to visualize the data from blue to red (improving - decline). To do this we're going to take the % change value we receive from the webhook and map it into the Neopixel LED.

We really only need the Red and Blue components, so the green will always be off.

The mapping will look like this:
- When it's declining (more than -5% change) the R component will be high (close to 255), and the B component will be low (close to zero)
- When it's increasing (more than 5% change) the R component will be low (close to 0), and the B component will be high (close to 255)

### Let's hook this up. 

In your code add the following method

````
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
  
  setRGBColor( color , 0, 255 - color );
      
}

````

Now to display the temperature, you just need to call this method in your loop

Add this one line:

````
      displayChange();
````

Save your code. Flash your code and you should see the color change. 


### Seeing it online too

While we're at it, it's really easy to add a `Particle.variable` to see the actual value of the temperature quickly from the console. 

In setup() add the following to make the temperature value visible online. 

````
  Particle.variable("change", currencyChange );
````

Save your code. Flash your code and you should see the color change. To view these variables in real time, you can do that from [Particle Console. ](http://console.particle.io)
