#define SIZE 4
#define STATE_START 0
#define STATE_SHOW_SEQ 1
#define STATE_PLAYER_READ 2
#define STATE_GAME_OVER 3
int fsm;

const int ledPins[SIZE] = {4,5,6,7};
const int buttonPins[SIZE] = {8,9,10,11}; 
int *gameSequence = NULL;
int playerStep = 0;
int currentLevel = 0;

unsigned long lastDebounce = 0;
unsigned long debounceDelay = 200;

void setup() {
  for(int i = 0 ; i < SIZE ; i++){
    pinMode(ledPins[i] , OUTPUT);
  }

  for(int j=0 ; j < SIZE ; j++){
    pinMode(buttonPins[j] , INPUT_PULLUP);
  }
  randomSeed(analogRead(0));
  Serial.begin(9600);
  fsm = STATE_START;


}

void loop() {
  switch(fsm){
    case STATE_START:
      if(gameSequence != NULL){
        free(gameSequence);
        gameSequence = NULL;
      }
      currentLevel = 1;
      playerStep = 0;

      gameSequence = (int*)malloc(1 * sizeof(int));
      gameSequence[0] = random(0 , 4);
      fsm = STATE_SHOW_SEQ;
      break;
    case STATE_SHOW_SEQ:
    delay(500);
      for(int i = 0 ; i < currentLevel ; i++){

        int index = gameSequence[i];

        digitalWrite(ledPins[index] , HIGH);
        delay(600);
        digitalWrite(ledPins[index] , LOW);
        delay(200);
        
      }
      playerStep = 0;
      fsm = STATE_PLAYER_READ;
      break;
    case STATE_PLAYER_READ:
    
      for(int i = 0 ; i < SIZE ; i++){
        if(digitalRead(buttonPins[i]) == LOW){
          unsigned long currentTime = millis();
          if(currentTime - lastDebounce > debounceDelay){
            lastDebounce = currentTime;

            
          digitalWrite(ledPins[i], HIGH);
            delay(200);
            digitalWrite(ledPins[i], LOW);

            if(i == gameSequence[playerStep]){
              playerStep++;

              if(playerStep == currentLevel){
                  Serial.println("You Guess!!");
                  currentLevel++;

                  gameSequence = (int*)realloc(gameSequence, currentLevel * sizeof(int));
                  gameSequence[currentLevel - 1] = random(0 , 4);
                  fsm = STATE_SHOW_SEQ;
              }

            }
            else{
              Serial.println("You lost!");
              fsm = STATE_GAME_OVER;
            }
            break;
          }
        }
      }
      break;

    case STATE_GAME_OVER:
      if(gameSequence != NULL){
        free(gameSequence);
        gameSequence = NULL;
      }

      delay(2000);
      fsm = STATE_START;
      break;
  }

}
