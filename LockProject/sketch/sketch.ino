#include <EEPROM.h>
#include <Keypad.h>
#include <Servo.h>

//Finite State Machine
#define STATE_BLOCKED 0
#define STATE_OPEN 1
#define STATE_NEW_PASSWORD 3
int fsm;
//EEPROM Variables
#define CONTROL_BYTE 42
int address = 0;
byte value;
byte initialValue = 49;

//Led Variables
const int redPin = 2;
const int greenPin = 12;
int ledStateGreen = LOW;
int ledStateRed = LOW;
unsigned long delayTime = 200;
unsigned long lastDebounceRed = 0;
unsigned long lastDebounceGreen = 0;

//Servo variables
Servo myServo;
int servoPin = 3;

//Keypad variables
#define PASSWORD_LENGTH 4
char userData[PASSWORD_LENGTH];
byte data_count = 0;
char costumKey;
const byte ROWS = 4;
const byte COLS = 4;
bool rightPassword ;

char hexaKeys[ROWS][COLS] = {
  {'1' , '2' , '3' , 'A'},
  {'4' , '5' , '6' , 'B'},
  {'7' , '8' , '9' , 'C'},
  {'*' , '0' , '#' , 'D'}
};

byte rowPins[ROWS] = {11,10,9,8};
byte colPins[COLS] = {7,6,5,4};

Keypad customKeypad = Keypad(makeKeymap(hexaKeys) , rowPins , colPins , ROWS , COLS);

void setup() {
  Serial.begin(9600);
  value = EEPROM.read(address);
  if(value != CONTROL_BYTE){
    EEPROM.write(address, CONTROL_BYTE);
    for(int i = 1 ; i <= 4 ; i++){
      address++;
      EEPROM.write(address, initialValue);
      initialValue++;
    }
    Serial.println("Primeiro Arranque detetado! Password padrao configurada");

  }

  address = 0;
  value = EEPROM.read(address);
  if(value == CONTROL_BYTE){
    Serial.println("Sistema inicializado com sucesso! Password Carregada");
  }

  //Setup Led
  pinMode(redPin , OUTPUT);
  pinMode(greenPin , OUTPUT);

  //Setup Servo
  myServo.attach(servoPin);

  fsm = STATE_BLOCKED;
  

}

void loop() {
  switch(fsm){
    case STATE_BLOCKED:
   
      address = 1;
      myServo.write(0);
      digitalWrite(redPin , HIGH);
      digitalWrite(greenPin , LOW);
      rightPassword = false;
      costumKey = customKeypad.getKey();
      if(costumKey){
          if(costumKey == '#'){
            if(data_count == PASSWORD_LENGTH){
              for(int i = 0 ; i< 4 ; i++){
                  value = EEPROM.read(address);
                  if(userData[i] == value){
                    rightPassword = true;
                  }
                  else{
                    rightPassword = false;
                    break;
                  }
                  address++;
              }

            }
            if(rightPassword){
              fsm = STATE_OPEN;
            }
            else{
              Serial.println("Wrong!");
              data_count = 0;
              userData[0] = '\0';
              fsm = STATE_BLOCKED;
            }
          }

          else{
                
              if(costumKey == '*'){
                data_count = 0;
                userData[0] = '\0';
              }

              else{
                userData[data_count] = costumKey;
                Serial.print("Keys: ");
                Serial.print( userData[data_count] );
                data_count++;
                Serial.print("  Counts: ");
                Serial.println( data_count );
              }
          }
       
      }
   
      break;
    case STATE_OPEN:
      digitalWrite(greenPin , HIGH);
      digitalWrite(redPin , LOW);
      myServo.write(90);
      costumKey = customKeypad.getKey();
      if(costumKey){
        if(costumKey == '*'){
            data_count = 0;
            userData[0] = '\0';
          fsm = STATE_BLOCKED;
        }
        else{
          if(costumKey == 'A'){
            data_count = 0;
            fsm = STATE_NEW_PASSWORD;
          }
        }
      }
      break;
    case STATE_NEW_PASSWORD:
      address = 1;
      blinkingRed();
      blinkingGreen();
      costumKey = customKeypad.getKey();
      if(costumKey){
          if(costumKey == '#'){
            if(data_count == PASSWORD_LENGTH){
              for(int i = 0 ; i < PASSWORD_LENGTH ; i++){
                value = userData[i];
                EEPROM.write(address , value);
                address++;
              }
              data_count = 0;
              userData[0] = '\0';
              fsm = STATE_BLOCKED;
            }
          }
          else{
            if(costumKey == '*'){
              data_count = 0;
              userData[0] = '\0';
            }
            else{

              userData[data_count] = costumKey;
              Serial.print("Keys: ");
              Serial.print( userData[data_count] );
              data_count++;
                Serial.print("  Counts: ");
                Serial.println( data_count );
            }
          }
      }
      break;
  }
  

}

void blinkingRed(){
  unsigned long currentTime = millis();
  if(currentTime - lastDebounceRed > delayTime){
    lastDebounceRed = currentTime;
    if(ledStateRed == LOW){
      ledStateRed = HIGH;
    }
    else{
      ledStateRed = LOW;
    }
    digitalWrite(redPin , ledStateRed);
  }
}

void blinkingGreen(){
  unsigned long currentTime = millis();
  if(currentTime - lastDebounceGreen > delayTime){
    lastDebounceGreen = currentTime;
    if(ledStateGreen == LOW){
      ledStateGreen = HIGH;
    }
    else{
      ledStateGreen = LOW;
    }
    digitalWrite(greenPin , ledStateGreen);
  }
}
