# Circuit Playground Express Cyclone Game

#### Description

This is a game that can be played on the Circuit Playground Express. Is inspired by the cyclone arcade game. In the game there is a stationary red light and a circling blue light, to score a point the player must click either button while the blue light covers the red light. If the player scores a point the speed of the circling blue light will increase making it more difficult for the following rounds. The difficulty will continue increasing until the player presses a button at the wrong time which will end the game. However as the game becomes more difficult the player has three life lines that they can use. By switching the switch the the speed at which the light circles is decreased for that round.

#### Rules

Click the buttons at the right time to score a point. Utelize the switch to make a round easier. Continue increasing difficulty until the player fails to press the button at the right time.

#### Inputs

1) Buttons: Pressing the either of the buttons will check the position of the blue light relative to the current red light.
2) Switch: Switching the position of the switch will slow down the circling light for one round, the player may use this three times per game.

#### Outputs

1) LEDs: The LEDs are the main output of the game showing the red and blue lights.
2) Sound: When the player scores a point the board will play a sound the frequency will increase as the player scores more points. When the player fails the speakers say "Fail" ending the game.
3) Serial Monitor: The serial monitor will print out the players score as they score more and more points. When the player fails a level "GAME OVER" and the players final score will be printed to the serial monitor, followed by prompting the player to play again.
