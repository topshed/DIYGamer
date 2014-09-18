/*
 * SIMON SAYS! (images)
 * A TWSU Gamer game by RDH
 * the finished Game + enhancements
*/

#include <Gamer.h>  // Include the Gamer library

/*
Create an "object" - a copy of the DIY Gamer library,
which contains commands for controlling the display,
buttons, and everything else on your console.
*/
Gamer gamer;
#define NUMFRAMES 4

byte sequence[50];
int sequenceLength = 0;
int delayTime = 300;
boolean waiting = true;

/* You should create your own arrays with your own
   images! */
byte frames[NUMFRAMES][8] = {
		{B00000000,
		B00000000,
		B00000000,
		B00011000,
		B00011000,
		B00000000,
		B00000000,
		B00000000},

		{B00000000,
		B00000000,
		B00111100,
		B00100100,
		B00100100,
		B00111100,
		B00000000,
		B00000000},

		{B00000000,
		B01111110,
		B01000010,
		B01000010,
		B01000010,
		B01000010,
		B01111110,
		B00000000},

		{B11111111,
		B10000001,
		B10000001,
		B10000001,
		B10000001,
		B10000001,
		B10000001,
		B11111111}};
// These are our arrow images
byte framesSimon[4][8] = {
  { // up
    B00000000,
    B00011000,
    B00111100,
    B01111110,
    B00011000,
    B00011000,
    B00011000,
    B00000000
  },
  { // down
    B00000000,
    B00011000,
    B00011000,
    B00011000,
    B01111110,
    B00111100,
    B00011000,
    B00000000
  },
  { // left
    B00000000,
    B00010000,
    B00110000,
    B01111110,
    B01111110,
    B00110000,
    B00010000,
    B00000000
  },
  { // right
    B00000000,
    B00001000,
    B00001100,
    B01111110,
    B01111110,
    B00001100,
    B00001000,
    B00000000
  }
};

// This is our "GO!" image
byte go[8] = {
  B00000000,
  B01101110,
  B10001010,
  B10001010,
  B10001010,
  B10101010,
  B01101110,
  B00100000
};

// This is our tick image
byte right[8] = {
  B00000001,
  B00000011,
  B00000111,
  B00001110,
  B11011100,
  B11111000,
  B01110000,
  B00100000
};

// This is our cross image
byte wrong[8] = {
  B11000011,
  B01100110,
  B00111100,
  B00011000,
  B00011000,
  B00111100,
  B01100110,
  B11000011
};

void setup() {
  gamer.begin(); // Fire up the Gamer!
  setupScore();
 // resetSimon();
}

void loop() {
//tone(2,200,2);
delay(200);
if (gamer.isPressed(START)){
  waiting = false;
 
  resetSimon();
 }
 
if (waiting){
  for(int i = 0; i < NUMFRAMES; i++){
	gamer.printImage(frames[i]);
	delay(200);
	}
 } else {
   
addToSequence();
gamer.clear();
delay(delayTime);
boolean success = true;
for(int i=0;i<sequenceLength;i++){
  
  int key = waitForButtonPress();
  gamer.clear();
  delay(100);
  gamer.printImage(framesSimon[key]);
  if(key != sequence[i]){
    success = false;
    break;
  }
}

delay(delayTime);
delayTime-=(delayTime/40);

if(success) {
  gamer.printImage(right);
  sequenceLength++;
} else{
  gamer.printImage(wrong);
  delay(1000);
  showScore(sequenceLength);
  delay(1000);
  resetSimon();
}
delay(500);
}
}
int waitForButtonPress(){
  int key = 4;
  while(key==4){
    if(gamer.isPressed(UP)) key=0;
    if(gamer.isPressed(DOWN)) key=1;
    if(gamer.isPressed(LEFT)) key=2;
    if(gamer.isPressed(RIGHT)) key=3;
  }
  return key;
}
 
void addToSequence(){
  sequence[sequenceLength] = random(0,4);
  for(int i=0;i<sequenceLength;i++){
    gamer.clear();
    delay(delayTime);
    gamer.printImage(framesSimon[sequence[i]]);
    buzz();
    delay(delayTime);
   
    }
 }
 void resetSimon(){
   gamer.clear();
   randomSeed(analogRead(5));
   delay(100);
   for(byte b=0;b<sequenceLength;b++) sequence[b]=0;{
   }
   sequenceLength=0;
   delayTime=300;
   sequence[0] = random(0,4);
   sequenceLength++;
   
   delay(1000);
   gamer.printImage(go);
   delay(250);
 }
 void buzz(){
    digitalWrite(BUZZER,HIGH);
  delay(50);
  digitalWrite(BUZZER,LOW);
 }
