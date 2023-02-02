# STM32_Serial_Terminal_Game

The famous snake game implemented using STM32F446RE , UART Communication, and FreeRTOS.

This is a very basic implementation of the game, it starts with a welcome message, to start the game press 's' and to end press 'e'.

The game operates at 4 FPS, maximum number of levels is 5, to go up one level you must reach a certain score, the game speed increases with each level.

The Xor-Shift algorithm was used to generate symbols at random locations, the 'E' letter resembles enemies which you should avoid, letter 'A' increases the score by 1, letter 'D' doubles the score for a certain amount of time, letter 'S' lowers the speed for a certain amount of time.

You also lose if the snake touchs itself or it hits the wall '#'.

# Implemented UART, GPIO, RCC, NVIC, and FreeRTOS

# Screenshots:

<img style="display:block; width: 60%; margin-bottom: 10%;" src="https://user-images.githubusercontent.com/85132955/216424584-bba9aedf-a07e-45ad-95f3-025ec6ee38a3.png" />

<img style="display:block; width: 60%;  margin-bottom: 10%;" src="https://user-images.githubusercontent.com/85132955/216424728-0e49ccdd-67a4-4db6-9e09-8397a844478e.png" />

<img style="display:block; width: 60%;  margin-bottom: 1%;" src="https://user-images.githubusercontent.com/85132955/216424800-f104825f-c64a-479b-8170-87921580f58e.png" />
