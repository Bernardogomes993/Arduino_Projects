# Parking Lot with Arduino Uno
This project implements some concepts like interrupts, millis and finite state machine.
The objective of this project is to recreate a parking lot.

# Functionalities
* **General Function**: The project has two buttons and one seven display segment(common anode) and a
  relay module.
  The green button has the purpose of simulating the entry of a car when the display has the number 9
  it means that the parking lot is full.
  When is full the user needs to press the red button which simulates a car leaving and then the display
  is going to have the number 8.

* **States of Finite State Machine**: The states are as follows:
    * **STATE_EMPTY**: In this state the led attached to the relay will blink every two seconds to
      sinalize the user that he is in the empty state.
      The user in this state can put the cars by pressing the green button or remove cars by pressing
      the red button.
      Once the number is `9` the program transits to the `STATE_FULL`.
    * **STATE_FULL**: In this state the led is off and the user cannot add more cars only remove, the
      display will show the number 9 once the user presses the red button the display will be 8 and
      the program transits to the `STATE_EMPTY`.

  # Connections
  All the connections are provide in the folder of this project `Schematic`.

  # How to use
  1. Download or clone the repository of this project.
  2. `Upload` the `sketch.ino` to your IDE or use the wokwi project.
  3. Finally play with the buttons.

  # Link to the project
  If you want to play with this project access here:
  [click here](https://wokwi.com/projects/468239331812603905)
  
