# Step 9: Multiple Currencies

Wouldn't it be nice if we could decide what cities we looked at the weather for? 

In this step, we're going to use the potentiometer as a way to scrub through different curriencies and get information for lots of different situations. 

We can do this simply by just changing the information we pass in the `Particle.publish` for the webhook. Until now we've used `   Particle.publish("bitcoin", "BTC-USD", PRIVATE);;` but we can use any lat and lon values in there to retrieve the weather for any number of cities. 

Let's add in Etherium, Bitcoin cash  and more!

## More currencies

First things first let's add two new global variables at the top. These will store the name of the city we're looking at and the number (relating to how far the potentiometer is turned.) Pop these two lines in at the top of your code:

````

String currentCurrency = "none";
int currencyIndex = 0;

````

It'd also be nice if we had a variable, so we can easily look up city is being presented. Pop this line into the end of your `setup()`

````
  Particle.variable("currency", currentCurrency );
````

We don't need to change the loop at all but we do need to make two big changes to:

- `checkForRefresh()` - we'll need to see if the potentiometer has changed position 
- `getData()` - we'll need to make the cities it requests dependent on the potentiometer's position


In `checkForRefresh` add the following lines. This reads in from the potentometer and maps the range to the number of cities we want to include and then sees if the dial has changed from this loop to the last. Perfect

````
  // has the dial changed

  if( abs( analogRead( potPin ) - potReading ) > 10 ){
    int newCurrencyIndex = map(  analogRead( potPin ), 0, 4095, 0, 5 );
    if( newCurrencyIndex != currencyIndex ){
        getData();
    }
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


	// Publish an event to trigger the webhook
   Particle.publish("bitcoin", "BTC-USD", PRIVATE);
	

  isLoading = true;
}

````

Add it to your code, save and compile!

## Give it a whirl

Once the code has flashed, dial the knob and see it cycle through cities! 