# Digital Electronic Lock with EEPROM
This project implements a security system that implements  a FSM (Finite State Machine) in Arduino Uno.
This system uses a keypad for the user passwords, a servo motor and two leds(green , red) to indicate diferent states.
Using the EEPROM from Arduino the password is never lost so the user needs to put the correct password to access the different
states.

## System Architecture
  The system operates within three different states:
1. **STATE_BLOCKED**: The servo goes to the 0 degrees position, the red led lights up and the green led is down.
  The system waits for the user to introduce the correct password and the validation process occurs when the user presses
  on the keypad the button `#`.
  If the user wants to clear the keypad i can do so when pressing the `*` button.
2. **STATE_OPEN**: If the passsword was right the servo motor rotates to the 90 degrees position and the green led lights up.
  The user can go to the **STATE_BLOCKED** if he presses `*` or can go to the next state(**STATE_NEW_PASSWORD**) by pressing `A`.
3.**STATE_NEW_PASSWORD**: This state allows the user to enter a new 4 digits password and then by pressing `#` the data is
   stored in the EEPROM.
   And then the program enters  the **STATE_BLOCKED**.
   If the user wants to clear the digits or if he dont want the sequence i can always press `*` to redo the password.

## Memory maintainability(EEPROM)
* **Address 0 (Control BYTE)**: This address contains the number 42 in order to check if is the first boot of the arduino.
  If it is the first boot the arduino puts in the next addresses(1,2,3,4) the numbers 49 50 51 and 52 which corresponds to the string
  (`1234`).
  If the password was changed the EEPROM preserves that password.
* **Addresses 1 to 4**: Has mentioned above this addresses in the first boot contain de string (`1234`).

## Connections Schematic
The connections schematic are available in the folder of the project.

## How to use the program
1. **Initialize the program**
2. **Initial Access**: The user must enter the initial password `1234` and then presses `#`, the green led will light up
   and the servo motor will rotate 90 degrees.
3. **Open State**: Then the user decides if he wants to go back to the blocked state by pressing `*` or go to the new password
   state by pressing `A`.
4. **New Password State**: The leds will be both blinking and the user can change the password to a new one with 4 digits.
   
   
