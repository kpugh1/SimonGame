
//Indicates where each of the components are connected 
//	to which arduino pin
const int piezoPin = 9;
const int redLed = 2;
const int redButton = 4;
const int blueButton = 8;
const int blueLed = 7;
const int yellowLed = 11;
const int yellowButton = 12;
const int redTone = 150;
const int blueTone = 200;
const int yellowTone = 350;
const int startGameTone = 600;
const int failGameTone = 500;

// Boolean to indicate when the game is over
bool playing = true;

//Sets up each pin to be either a output or an input
void setup() {
    pinMode(redLed, OUTPUT);
    pinMode(blueLed, OUTPUT);
    pinMode(yellowLed, OUTPUT);
  
  	pinMode(redButton, INPUT);
    pinMode(blueButton, INPUT);
    pinMode(yellowButton, INPUT);
    
    pinMode(piezoPin, OUTPUT);

}


void loop() {


 
  //Array for the users input
  int userInput[20];
  
  //The position of the game
  int gamePosition;
 
  // If any of the buttons are pressed
  if (buttonPressed(redButton) || buttonPressed(blueButton) || buttonPressed(yellowButton)) {
    
    //Start the game introduction
    startGame();
    
    //Set playing to true
    playing = true;
    
    //Set game position to 0
    gamePosition = 0;
      	
    //While the game is less than 20 sequences and the user is still playing
    while ( (gamePosition < 20) && (playing)) {
        
      	// holds the random led
    	int randomLed;
		
      	//Set the random led from 1 to 3
        randomLed = random(1, 4);
        
      	//The userinput at the game level is the button for the led
        userInput[gamePosition] = chooseLed(randomLed);
        
      	//play the sequence up to where the game level
        for (int i = 0; i < gamePosition; i++) {
        	playSequence(userInput[i]);
          }
    	
      	// the sequence if the game and while still playing 
        for (int j = 0; (j < gamePosition) && playing; j++) {
          
          	//Wait for the user to press a button
        	while (!buttonPressed(redButton) && !buttonPressed(blueButton) && !buttonPressed(yellowButton)) {}
            
          	// If the button pressed is incorrect
            if (!buttonPressed(userInput[j])) {
            	
              	//Indicate the game is over and set playing to false
            	gameOver();
              	playing = false;
              
            } 
          	else {
            	
              	//Play the of the user input
           		 playSequence(userInput[j]);
              
           	} 
          }
      		
      	// Move the game position 1 more level
          gamePosition++;
        }
         
   
    }
}




//To indicate the game is over all the leds flash at once
// and then the buzzer sounds for 2 seconds
void gameOver() {
  	//Turn all the leds on 
    digitalWrite(redLed, HIGH);
    digitalWrite(blueLed, HIGH);
    digitalWrite(yellowLed, HIGH);
    delay(500); // Wait for .5 seconds
  
  	//Turn all the leds off
    digitalWrite(redLed, LOW);
    digitalWrite(blueLed, LOW);
    digitalWrite(yellowLed, LOW);
    delay(500);
    tone(piezoPin, failGameTone, 2000); // buzz the buzzer for 2 seconds
    delay(500); //wait for .5 seconds
    noTone(piezoPin); //Turn buzzer off
    delay(500); 
}
//To indicate the game started the buzzzer goes off and then
//each led lights with its corresponding tone
void startGame() {
    //Buzz the buzzer 
  	tone(piezoPin, startGameTone);
    delay(500); // Wait for .5 seconds
    noTone(piezoPin); //Turn buzzer off
    delay(500); 
    delay(500);
  	//Light each led on and sound their tone
  	lightLed(redLed, redTone);
   	lightLed(blueLed, blueTone);
    lightLed(yellowLed, yellowTone);
  
}

//Returns True/False if the specific button is pressed
bool buttonPressed(int buttonPin) {
  
  	bool read = false;
  //If the button reads LOW then it is pressed  
  if (digitalRead(buttonPin) == LOW) {
        read = true;
    }
	
    return read;
}

//Returns the button that corresponds with the led
int chooseLed(int led) {

    switch (led) {
        case 1:
            return redButton;
            break;
        case 2:
            return blueButton;
            break;
        case 3:
            return yellowButton;
            break;
    }

}

//Based on the button play the led that corresponds with it 
void playSequence(int sequence)
{
   switch (sequence) {
        case redButton:
            lightLed(redLed, redTone);
            break;
        case blueButton:
            lightLed(blueLed, blueTone);
            break;
        case yellowButton:
           lightLed(yellowLed, yellowTone);
            break;
    }
}

//Lights the led and play the tone 
void lightLed(int led, int playTone)
{
  
   digitalWrite(led, HIGH);
     delay(500);
    digitalWrite(led, LOW);
     delay(500);
  tone(piezoPin, playTone);
     delay(500); 
    noTone(piezoPin);
     delay(500);
}

