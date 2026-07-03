#define SIZE 7
#define EMPTY 0
#define FULL 1
const int buttonEntry = 3;
const int buttonOut = 2;
int fsm;

const int ledPins[SIZE] = {4 , 5 , 6 , 7 , 8 , 9 , 10};
const byte ledMatrix[][SIZE] = {
  {0,0,0,0,0,0,1},
  {1,0,0,1,1,1,1},
  {0,0,1,0,0,1,0},
  {0,0,0,0,1,1,0},
  {1,0,0,1,1,0,0},
  {0,1,0,0,1,0,0},
  {0,1,0,0,0,0,0},
  {0,0,0,1,1,1,1},
  {0,0,0,0,0,0,0},
  {0,0,0,1,1,0,0}
};

const int contactRelay = 11;
unsigned long ledLastDebounce = 0;
int ledState = LOW;
int counter;

volatile unsigned long lastOutDebounce = 0;
volatile unsigned long debounceDelay = 200;
volatile bool isOut = false;

volatile unsigned long lastEntryDebounce = 0;
volatile bool isEntry = false;

void setup() {
  pinMode(buttonEntry , INPUT_PULLUP);
  attachInterrupt(1 , entryInterrupt , FALLING);
  pinMode(buttonOut , INPUT_PULLUP);
  attachInterrupt(0, outInterrupt , FALLING);

  for(int i = 0 ; i < SIZE ; i++){
    pinMode(ledPins[i], OUTPUT);
  }

  pinMode(contactRelay , OUTPUT);
  fsm = EMPTY;
}

void loop() {
  switch(fsm){
    case EMPTY:
      blinkingLed();
      display(counter);
      if(isEntry){
        if(counter < 9){
          counter++;
        }
        isEntry = false;
      }

      if(isOut){
        if(counter > 0){
          counter--;
        }
        isOut = false;
      }

      if(counter == 9){
        digitalWrite(contactRelay , LOW);
        fsm = FULL;
      }
      break;
    case FULL:
      display(counter);
      if(isOut){
        counter--;
        fsm = EMPTY;
        isOut = false;
      }
      if(isEntry){
        isEntry = false;
      }
      break;
  }

}


void entryInterrupt(){
  unsigned long currentTime = millis();
  if(currentTime - lastEntryDebounce > debounceDelay){
    isEntry = true;
    lastEntryDebounce = currentTime;
  }
}

void outInterrupt(){
  unsigned long currentTime = millis();
  if(currentTime - lastOutDebounce > debounceDelay){
    isOut = true;
    lastOutDebounce = currentTime;
  }
}

void blinkingLed(){
  unsigned long currentTime = millis();
  if(currentTime - ledLastDebounce > 2000){
    if(ledState == LOW){
      ledState = HIGH;
    }
    else{
      ledState = LOW;
    }
    ledLastDebounce = currentTime;
    digitalWrite(contactRelay , ledState);
  }
}

void display(int adder){
  for(int i = 0 ; i < SIZE ; i++){
    digitalWrite(ledPins[i] , ledMatrix[adder][i]);
  }
}
