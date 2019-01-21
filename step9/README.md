# Step 9: Multiple Cities

Wouldn't it be nice if we could decide what cities we looked at the weather for? 

In this step, we're going to use the potentiometer as a way to scrub through cities and get information for lots of different places. 

We can do this simply by just changing the information we pass in the `Particle.publish` for the webhook. Until now we've used `Particle.publish("forecast", "40.4406,-79.9959", PRIVATE);` but we can use any lat and lon values in there to retrieve the weather for any number of cities. 

Let's add in Phoenix, San Fran, Syndey, Dublin and more!

## More cities

First things first let's add two new global variables at the top. These will store the name of the city we're looking at and the number (relating to how far the potentiometer is turned.) Pop these two lines in at the top of your code:

````
String currentCity = "none";
int cityIndex = 0;
````

It'd also be nice if we had a variable, so we can easily look up city is being presented. Pop this line into the end of your `setup()`

````
  Particle.variable("city", &currentCity, STRING );
````

We don't need to change the loop at all but we do need to make two big changes to:

- `checkForRefresh()` - we'll need to see if the potentiometer has changed position 
- `getData()` - we'll need to make the cities it requests dependent on the potentiometer's position


In `checkForRefresh` add the following lines. This reads in from the potentometer and maps the range to the number of cities we want to include and then sees if the dial has changed from this loop to the last. Perfect

````
  // has the dial changed

  int newcityIndex = map(  analogRead( potPin ), 0, 4095, 0, 6 );
  if( newcityIndex != cityIndex ){
    getData();
  }
````

In `getData` we're going to need to do a lot of new stuff! 
First we'll need to read from the potentometer. 
Then we'll need to map that into the number of cities we want to look up weather for - and then publish a lat and lon depending on the city that's been selected using the potentiometer. 

Our new getData looks like this: 

````
void getData()
{
  Serial.println( "requesting Data" );

  potReading = analogRead( potPin ) ;
  cityIndex = map( potReading, 0, 4095, 0, 6 );

  if( cityIndex == 0 ){
    // Pittsburgh
    currentCity = "Pittsburgh";
    Particle.publish("forecast", "40.4406,-79.9959", PRIVATE);
  }else if( cityIndex == 1 ){
    currentCity = "Phoenix";
    Particle.publish("forecast", "33.448376,-112.074036", PRIVATE);
  }else if( cityIndex == 2 ){
    currentCity = "San Francisco";
    Particle.publish("forecast", "37.7749,-122.4194", PRIVATE);
  }else if( cityIndex == 3 ){
    currentCity = "Sydney";
    Particle.publish("forecast", "-33.8688,151.2093", PRIVATE);
  }else if( cityIndex == 4 ){
    currentCity = "Dublin";
    Particle.publish("forecast", "53.3498,-6.2603", PRIVATE);
  }else if( cityIndex == 5 ){
    currentCity = "Antarctica";
    Particle.publish("forecast", "-82.8628,-135.0000", PRIVATE);
  }

  Serial.println( currentCity );


  isLoading = true;
}

````

Add it to your code, save and compile!

## Give it a whirl

Once the code has flashed, dial the knob and see it cycle through cities! 