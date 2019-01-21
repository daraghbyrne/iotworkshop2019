# Step 8: Better Loading

There's still two shortcomings to our little device

1. It's only getting data when it starts up. That means it's not changing over time as the weather does! 

2. We don't know when it's getting data and refreshing.

Let's solve both of these problems now!

- Ideally we want it to refresh at least every 10 minutes and

- Visually indicate when it has refreshed / is refreshing. 


## a. Refresh every 10 minutes

To make it refresh every 10 minutes, we need to know when it last refreshed. So first, let's add a variable to the top of our code 

````
long lastData = 0;
````

We'll use this variable to store the time when the webhook was last called. 

Next we'll need to write some code to check if we should refresh: Drop this awesome function in your code

````
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

````

Finally, we need to add a call to this function into our loop. Add this line at the top of the loop:

````
	checkForRefresh();

````

Save and flash your code

## b. Indicate Refresh is happening

Now we need to visually indicate it's refreshing. And it just so happens we've an unused LED that's perfect for blinking. And that's just wnat we'll do. 

First we'll need to have a variable that we can use to indicate if the program is waiting on data to be loaded from the webhook. Add this at the top of the code

````
bool isLoading = false;

````

Then if it's loading we'll want to blink the LED. This means we'll use a conditional `if` statement that will use the value of the variable `isLoading` to decide if we blink. In our loop we'll add a conditional blink statement


````
    if( isLoading ) {
      digitalWrite( ledPin, HIGH );
      delay( 100 );
      digitalWrite( ledPin, LOW );
    }
````

Then finally in the `getData()` method, we need to set the isLoading variable to true to indicate it is loading data 

Update this method to add this at the end

````
void getData()
{
	//.... [add below the particle.publish ]
	
  isLoading = true;
}
````


And in the handler for webhook responses i.e. when we've got the information back we'll want to set the variable to not-loading or false> Like so:

````
void handleForecastReceived(const char *event, const char *data) {

  isLoading = false; 
	
	[rest of the content below]
	...
````

Save and flash your code


Now not only should your LED blink when it's updating but the colors should continue to change over time. 
