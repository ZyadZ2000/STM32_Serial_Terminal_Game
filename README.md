# Introduction

A simple variation of the famous snake game implemented in the serial terminal using stm32f446re, and FreeRTOS.

The game is very simple, the snake is represented as '&**\***' where the head is '&', and the body is '\*'. The snake moves in the direction of the head, and the user can change the direction of the snake using the following keys:
1: left
2: down
3: right
5: up

The snake dies if it hits the wall, eats and enemy 'E', or if it hits itself. The user is first presented with a welcome message, and can start the game by pressing 's'. The user can reset the game by pressing 'r'.

Each level is 30 seconds, and the snake gets faster as the level increases.

max level: 5

# Implementation details

The game is implemented using the Active Object design pattern on top of FreeRTOS. This pattern is used to eliminate the most of the blocking typically found in traditional RTOS tasks. Credit to <a href="https://www.youtube.com/@StateMachineCOM">Dr. Miro Samek</a> for the idea and explanation.

## There are two main Active Objects:

### 1. Game:

This active object encapsulates the attributes and logic of the game. This is a state diagram for the Game implemented in <a href="https://www.state-machine.com/products/qm">QM modeling tool</a>.

<img style="display:block; width: 60%; margin-bottom: 10%;" src="https://github.com/ZyadZ2000/STM32_Serial_Terminal_Game/assets/85132955/8af5d41c-7187-4881-8cb3-7887963e6047" />

### 1. ScreenFrame:

This active object is responsible for sending the displayed frame to the serial terminal through UART communication. The frame is sent as a string of characters, and the screen is updated every 33ms (30fps). This is the state diagram for the ScreenFrame implemented in <a href="https://www.state-machine.com/products/qm">QM modeling tool</a>.

<img style="display:block; width: 60%; margin-bottom: 10%;" src="https://github.com/ZyadZ2000/STM32_Serial_Terminal_Game/assets/85132955/775d8e2e-c6cd-4b1f-b7be-9230d5a71e20" />

# Screenshots:

## Note:

These screenshots are based on the previous implementation of the game (which didn't use the Active Objects Pattern), I didn't get the chance to test the new implementation on actual hardware yet due to the current inavailability of the hardware.

<img style="display:block; width: 60%; margin-bottom: 10%;" src="https://user-images.githubusercontent.com/85132955/216424584-bba9aedf-a07e-45ad-95f3-025ec6ee38a3.png" />

<img style="display:block; width: 60%;  margin-bottom: 10%;" src="https://user-images.githubusercontent.com/85132955/216424728-0e49ccdd-67a4-4db6-9e09-8397a844478e.png" />

<img style="display:block; width: 60%;  margin-bottom: 1%;" src="https://user-images.githubusercontent.com/85132955/216424800-f104825f-c64a-479b-8170-87921580f58e.png" />
