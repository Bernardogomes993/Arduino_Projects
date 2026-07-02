# Simon Says Game with Arduino Uno
This project is about the classic game of Simon Says. The system generates a random sequence of lights for each round.

## Functionalities
* **Dinamic  Random Generation**: In the setup of arduino, the use of `randomSeed(analogRead(0))` guarantee that there
  is always a random sequence.
* **Visual Feedback**: In each round there is a sequence of colors that are generated via the leds.
* **Progressive Dificulties**: If the player guesses the sequence there is a random value generated between 0 and 4 and
  this value is added to the new sequence.

## Connections
The schematic is available at the folder of the project

## How to play
1. Copy the code `.ino` or clone the repository.
2. Do the `Upload` of the sketch into the IDE of Arduino.
3. The first play the computer will choose a random led, you need to press the correspondent button.
4. If you guess the Arduino will repeat the same sequence and adds another random light.
   If you miss the game will go back to the beginning (one led).
   
