/*

  Traffic light
  by Jerome Maurey-Delaunay
  @jeromemaurey
  
  This script is part of a project to create a small traffic light using 2 LEDs.
  The mount for it can be downloaded from thingiverse and 3D printed: http://www.thingiverse.com/thing:93925
  
  There are 2 push buttons and 2 LEDs on the breadboard. Manual mode toggles lights by pressing one push button.
  Automatic mode uses a random delay to switch between lights. It uses millis() to ensure handling of push buttons.
  
  Enjoy!
  
  Jerome.
  
*/



// buttons
int buttonAutoPin = 9;
int buttonManualPin = 8;

// used to make push buttons act as toggles that execute only once upon being pressed
boolean ignoreButtonAuto = false;
boolean ignoreButtonManual = false;

// leds and current
int redLed = 5;
int greenLed = 6;
int currentLed = 0;

// delay handling
long previousMillis = 0; 
unsigned long currentMillis = 0;
int delayTime = 1000;

// mode handling
int automatic = 0;
int manual = 1;
int mode = 0;

void setup() 
{
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(buttonAutoPin, INPUT_PULLUP);  
  pinMode(buttonManualPin, INPUT_PULLUP);
}
 
void loop() 
{
  
  // automatic button
  if (digitalRead(buttonAutoPin) == LOW && !ignoreButtonAuto)
  {
    mode = automatic;
    previousMillis = currentMillis = millis();
    ignoreButtonAuto = true;
  }
  // manual button
  else if (digitalRead(buttonManualPin) == LOW && !ignoreButtonManual)
  {
    
     mode = manual;
     digitalWrite(currentLed, LOW);
     if( currentLed == redLed ) currentLed = greenLed;
     else currentLed = redLed;
     ignoreButtonManual = true;
   
  }
  
  // we ignore the buttons until they are released and pressed again
  if (digitalRead(buttonManualPin) == HIGH && ignoreButtonManual) ignoreButtonManual = false;
  if (digitalRead(buttonAutoPin) == HIGH && ignoreButtonAuto) ignoreButtonAuto = false;
  
  // handle current mode
  switch( mode )
  {
    
    // automatic mode
    case 0:
        
        // update time
        currentMillis = millis();
        
        // if time passed is superior to set delay switch lights!
        if(currentMillis - previousMillis > delayTime)
        {
          // turn off current light
          digitalWrite(currentLed, LOW);
          // switch
          if( currentLed == redLed ) currentLed = greenLed;
          else currentLed = redLed;
          // turn on current light
          digitalWrite(currentLed, HIGH);
          
          // random delay
          delayTime = random( 1000, 4000 );
          // reset time tracking
          previousMillis = currentMillis;
        }
        
        break;
     
     // manual mode 
     case 1:
       
       // turn on current light
       digitalWrite(currentLed, HIGH);
       // small delay for avoiding "button bounce" (found on the interwebs at http://forum.arduino.cc/index.php?topic=58284.0) 
       delay(100);
       
       break;
  }

  
}
