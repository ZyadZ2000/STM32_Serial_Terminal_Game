#include <stdlib.h>
#include "main.h"

void UART_intgerToString(int data) {
	char buff[16]; /* String to hold the ascii result */
	itoa(data, buff, 10); /* Use itoa C function to convert the data to its corresponding ASCII value, 10 for decimal */
	MCAL_UART_sendString(USE_USART1, buff);
	/* Display the string */
}

xSemaphoreHandle xBinarySemaphore;
u8 frame[50][70];
u8 specialSymbols[2] = { 'S', 'D' };
u8 symbols[2] = { 'E', 'A' };
u8 *welcomeString =
		(u8*) "Welcome to Snake game\r\ns:to start game\r\ne:to end game\r\nUse arrow keys to move the snake.\r\n";

Point snakeHead;
Point snakeTail;

/* Game State */
u8 data = 'e';
u8 *currentString = NULL;
u8 currentLevel;
u8 currentSpeed;
u8 numOfGeneratedSymbols;
u8 numOfSpecialSymbols;
u8 currentPower;
u32 currentPowerTime;
u8 score;
u32 elapsedTime;
u8 g_tick;

void USART1_IRQHandler(void) {
	//portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;
	//xSemaphoreGiveFromISR(xBinarySemaphore, &xHigherPriorityTaskWoken);
	data = USART1->DR;
	//portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}

u32 XORShift(void) {
	static u32 x = 10, y = 630, z = 100, w = 263;
	u32 t = x ^ (x << 11);
	x = y;
	y = z;
	z = w;
	return w = w ^ (w >> 19) ^ t ^ (t >> 8);
}

void clear_random_symbols(void) {
	int i, j;
	numOfGeneratedSymbols = 0;
	for (i = 0; i < 50; i++) {
		for (j = 0; j < 70; j++) {
			if (frame[i][j] == 'E' || frame[i][j] == 'A') {
				frame[i][j] = ' ';
			}
		}
	}
}

void clear_special_symbols(void) {
	int i, j;
	numOfSpecialSymbols = 0;
	for (i = 0; i < 50; i++) {
		for (j = 0; j < 70; j++) {
			if (frame[i][j] == 'D' || frame[i][j] == 'S') {
				frame[i][j] = ' ';
			}
		}
	}
}

void initialize_starting_frame(void) {
	currentLevel = 1;
	currentSpeed = 1;
	numOfGeneratedSymbols = 0;
	numOfSpecialSymbols = 0;
	currentPower = 0;
	currentPowerTime = 0;
	score = 0;
	elapsedTime = 0;
	g_tick = 0;
	u8 i, j;
	for (i = 0; i < 50; i++) {
		for (j = 0; j < 70; j++) {
			if (i == 0 || i == 49) {
				if (j == 68) {
					frame[i][j] = '\r';
				} else if (j == 69) {
					if (i == 49) {
						frame[i][j] = '\0';
					} else {
						frame[i][j] = '\n';
					}
				} else {
					frame[i][j] = '#';
				}
			} else {
				if (j == 68) {
					frame[i][j] = '\r';
				} else if (j == 69) {
					frame[i][j] = '\n';
				} else {
					if (j == 0 || j == 67) {
						frame[i][j] = '#';
						frame[i][j] = '#';
					} else {
						frame[i][j] = ' ';
					}
				}
			}
		}
	}
	snakeHead.row = 2;
	snakeHead.col = 6;
	snakeTail.row = 2;
	snakeTail.col = 2;
	for (i = 0; i < 5 - 1; i++) {
		frame[2][i + 2] = '*';
	}
	frame[2][5 + 1] = '&';
}

void update_with_input(void) {
	if (currentPowerTime == 20) {
		currentPower = 0;
		currentPowerTime = 0;
	}
	switch (data) {
	case 's':
		initialize_starting_frame();
		currentString = (u8*) frame;
		break;
	case 'e':
		currentString = welcomeString;
		break;
	case '1':
		//move to left
		if (frame[snakeHead.row][snakeHead.col - 1] == '#'
				|| frame[snakeHead.row][snakeHead.col - 1] == '*'
				|| frame[snakeHead.row][snakeHead.col - 1] == 'E') {
			currentString = (u8*) "GAME OVER!,Press 's' to try again";
		} else if (frame[snakeHead.row][snakeHead.col - 1] == 'A') {
			if (frame[snakeHead.row][snakeHead.col - 2] == '#'
					|| frame[snakeHead.row][snakeHead.col - 2] == '*'
					|| frame[snakeHead.row][snakeHead.col - 2] == 'E') {
				currentString = (u8*) "GAME OVER!,Press 's' to try again";
				return;
			}
			if (currentPower == 'D') {
				score += 2;
			} else {
				score++;
			}
			frame[snakeHead.row][snakeHead.col] = '*';
			frame[snakeHead.row][snakeHead.col - 1] = '*';
			frame[snakeHead.row][snakeHead.col - 2] = '&';
			snakeHead.col -= 2;
			numOfGeneratedSymbols--;
		} else {
			if (frame[snakeHead.row][snakeHead.col - 1] == 'S') {
				currentPower = 'S';
				currentPowerTime = 0;
				if (currentSpeed != 0)
					currentSpeed--;
			} else if (frame[snakeHead.row][snakeHead.col - 1] == 'D') {
				currentPower = 'D';
				currentPowerTime = 0;
				if (currentSpeed != 5)
					currentSpeed++;
			}
			frame[snakeHead.row][snakeHead.col] = '*';
			frame[snakeHead.row][snakeHead.col - 1] = '&';
			frame[snakeTail.row][snakeTail.col] = ' ';
			snakeHead.col--;
			if (frame[snakeTail.row][snakeTail.col + 1] == '*')
				snakeTail.col++;
			else if (frame[snakeTail.row][snakeTail.col - 1] == '*') {
				snakeTail.col--;
			} else if (frame[snakeTail.row + 1][snakeTail.col] == '*') {
				snakeTail.row++;
			} else {
				snakeTail.row--;
			}
		}
		break;
	case '3':
		//move to right
		if (frame[snakeHead.row][snakeHead.col + 1] == '#'
				|| frame[snakeHead.row][snakeHead.col + 1] == '*'
				|| frame[snakeHead.row][snakeHead.col + 1] == 'E') {
			currentString = (u8*) "GAME OVER!,Press 's' to try again";
		} else if (frame[snakeHead.row][snakeHead.col + 1] == 'A') {
			if (frame[snakeHead.row][snakeHead.col + 2] == '#'
					|| frame[snakeHead.row][snakeHead.col + 2] == '*'
					|| frame[snakeHead.row][snakeHead.col + 2] == 'E') {
				currentString = (u8*) "GAME OVER!,Press 's' to try again";
				return;
			}
			if (currentPower == 'D') {
				score += 2;
			} else {
				score++;
			}
			frame[snakeHead.row][snakeHead.col] = '*';
			frame[snakeHead.row][snakeHead.col + 1] = '*';
			frame[snakeHead.row][snakeHead.col + 2] = '&';
			snakeHead.col += 2;
			numOfGeneratedSymbols--;
		} else {
			if (frame[snakeHead.row][snakeHead.col + 1] == 'S') {
				currentPower = 'S';
				currentPowerTime = 0;
				if (currentSpeed != 0)
					currentSpeed--;
			} else if (frame[snakeHead.row][snakeHead.col + 1] == 'D') {
				currentPower = 'D';
				currentPowerTime = 0;
				if (currentSpeed != 5)
					currentSpeed++;
			}
			frame[snakeHead.row][snakeHead.col] = '*';
			frame[snakeHead.row][snakeHead.col + 1] = '&';
			frame[snakeTail.row][snakeTail.col] = ' ';
			snakeHead.col++;
			/*if (frame[snakeTail.row + 1][snakeTail.col] == '*') {
			 snakeTail.row++;
			 }
			 //this
			 else if (frame[snakeTail.row - 1][snakeTail.col] == '*') {
			 snakeTail.row--;
			 } else {
			 snakeTail.col++;
			 }*/
			if (frame[snakeTail.row][snakeTail.col + 1] == '*')
				snakeTail.col++;
			else if (frame[snakeTail.row][snakeTail.col - 1] == '*') {
				snakeTail.col--;
			} else if (frame[snakeTail.row + 1][snakeTail.col] == '*') {
				snakeTail.row++;
			} else {
				snakeTail.row--;
			}
		}

		break;
	case '5':
		//move up
		if (frame[snakeHead.row - 1][snakeHead.col] == '#'
				|| frame[snakeHead.row - 1][snakeHead.col] == '*'
				|| frame[snakeHead.row - 1][snakeHead.col] == 'E') {
			currentString = (u8*) "GAME OVER!,Press 's' to try again";
		} else if (frame[snakeHead.row - 1][snakeHead.col] == 'A') {
			if (frame[snakeHead.row - 2][snakeHead.col] == '#'
					|| frame[snakeHead.row - 2][snakeHead.col] == '*'
					|| frame[snakeHead.row - 2][snakeHead.col] == 'E') {
				currentString = (u8*) "GAME OVER!,Press 's' to try again";
				return;
			}
			if (currentPower == 'D') {
				score += 2;
			} else {
				score++;
			}
			frame[snakeHead.row][snakeHead.col] = '*';
			frame[snakeHead.row - 1][snakeHead.col] = '*';
			frame[snakeHead.row - 2][snakeHead.col] = '&';
			snakeHead.row -= 2;
			numOfGeneratedSymbols--;
		} else {
			if (frame[snakeHead.row - 1][snakeHead.col] == 'S') {
				currentPower = 'S';
				currentPowerTime = 0;
				if (currentSpeed != 0)
					currentSpeed--;
			} else if (frame[snakeHead.row - 1][snakeHead.col] == 'D') {
				currentPower = 'D';
				currentPowerTime = 0;
				if (currentSpeed != 5)
					currentSpeed++;
			}
			frame[snakeHead.row][snakeHead.col] = '*';
			frame[snakeHead.row - 1][snakeHead.col] = '&';
			frame[snakeTail.row][snakeTail.col] = ' ';
			snakeHead.row--;
			if (frame[snakeTail.row][snakeTail.col + 1] == '*')
				snakeTail.col++;
			else if (frame[snakeTail.row][snakeTail.col - 1] == '*') {
				snakeTail.col--;
			} else if (frame[snakeTail.row + 1][snakeTail.col] == '*') {
				snakeTail.row++;
			} else {
				snakeTail.row--;
			}
		}
		break;
	case '2':
//move down
		if (frame[snakeHead.row + 1][snakeHead.col] == '#'
				|| frame[snakeHead.row + 1][snakeHead.col] == '*'
				|| frame[snakeHead.row + 1][snakeHead.col] == 'E') {
			currentString = (u8*) "GAME OVER!,Press 's' to try again";
		} else if (frame[snakeHead.row + 1][snakeHead.col] == 'A') {
			if (frame[snakeHead.row + 2][snakeHead.col] == '#'
					|| frame[snakeHead.row + 2][snakeHead.col] == '*'
					|| frame[snakeHead.row + 2][snakeHead.col] == 'E') {
				currentString = (u8*) "GAME OVER!,Press 's' to try again";
				return;
			}
			if (currentPower == 'D') {
				score += 2;
			} else {
				score++;
			}
			frame[snakeHead.row][snakeHead.col] = '*';
			frame[snakeHead.row + 1][snakeHead.col] = '*';
			frame[snakeHead.row + 2][snakeHead.col] = '&';
			snakeHead.row += 2;
			numOfGeneratedSymbols--;
		} else {
			if (frame[snakeHead.row + 1][snakeHead.col] == 'S') {
				currentPower = 'S';
				currentPowerTime = 0;
				if (currentSpeed != 0)
					currentSpeed--;
			} else if (frame[snakeHead.row + 1][snakeHead.col] == 'D') {
				currentPower = 'D';
				currentPowerTime = 0;
				if (currentSpeed != 5)
					currentSpeed++;
			}
			frame[snakeHead.row][snakeHead.col] = '*';
			frame[snakeHead.row + 1][snakeHead.col] = '&';
			frame[snakeTail.row][snakeTail.col] = ' ';
			snakeHead.row++;
			if (frame[snakeTail.row][snakeTail.col + 1] == '*')
				snakeTail.col++;
			else if (frame[snakeTail.row][snakeTail.col - 1] == '*') {
				snakeTail.col--;
			} else if (frame[snakeTail.row + 1][snakeTail.col] == '*') {
				snakeTail.row++;
			} else {
				snakeTail.row--;
			}
		}
		break;
	}
	if (score >= (currentLevel * 8)) {
		currentLevel++;
		currentSpeed++;
		clear_random_symbols();
		clear_special_symbols();
	}
	if (currentLevel == 6) {
		currentString = (u8*) "YOU WON!!!";
	}
}

void Game_Update_Handler(void *parameters) {
	while (1) {
		taskENTER_CRITICAL();
		update_with_input();
		taskEXIT_CRITICAL();
		vTaskDelay((6 - currentSpeed) * 50);
	}
}

void Frame_Handler(void *parameters) {
	for (;;) {
		taskENTER_CRITICAL();
		g_tick++;
		if (g_tick == 4) {
			g_tick = 0;
			elapsedTime++;
			currentPowerTime++;
		}
		MCAL_UART_sendString(USE_USART1, (u8*) "\x1b[2J\x1b[H");
		update_with_input();
		MCAL_UART_sendString(USE_USART1, currentString);
		MCAL_UART_sendString(USE_USART1, "\r\n\0");
		MCAL_UART_sendString(USE_USART1, "Score: ");
		UART_intgerToString(score);
		MCAL_UART_sendString(USE_USART1, "\r\n\0");
		MCAL_UART_sendString(USE_USART1, "Current Level: ");
		UART_intgerToString(currentLevel);
		MCAL_UART_sendString(USE_USART1, "\r\n\0");
		MCAL_UART_sendString(USE_USART1, "Elapsed Seconds: ");
		UART_intgerToString(elapsedTime);
		MCAL_UART_sendString(USE_USART1, "\r\n\0");
		taskEXIT_CRITICAL();
		vTaskDelay(250);
	}
}

void Random_Symbols_Handler(void *parameters) {
	u8 xorRandom;
	u8 randomRow, randomCol;
	u8 randomSymbol;
	for (;;) {
		if (numOfGeneratedSymbols == (12 + currentSpeed * 3)) {
			clear_random_symbols();
			clear_special_symbols();
		} else {
			do {
				xorRandom = (u8) XORShift();
				randomRow = xorRandom % 50;
				randomCol = xorRandom % 70;
			} while (frame[randomRow][randomCol] != ' ');
			randomSymbol = xorRandom % 2;
			frame[randomRow][randomCol] = symbols[randomSymbol];
			numOfGeneratedSymbols++;
		}
		vTaskDelay((6 - currentSpeed) * 350);
	}
}

void Special_Symbols_Handler(void *parameters) {
	u8 xorRandom;
	u8 randomRow, randomCol;
	u8 randomSymbol;
	for (;;) {
		if (numOfSpecialSymbols == (9 - currentSpeed)) {
			clear_special_symbols();
		} else {
			do {
				xorRandom = (u8) XORShift();
				randomRow = xorRandom % 50;
				randomCol = xorRandom % 70;
			} while (frame[randomRow][randomCol] != ' ');
			randomSymbol = xorRandom % 2;
			frame[randomRow][randomCol] = specialSymbols[randomSymbol];
			numOfSpecialSymbols++;
		}
		vTaskDelay((6 - currentSpeed) * 500);
	}
}
/*
 void UART_Input_Handler(void *parameters) {
 xSemaphoreTake(xBinarySemaphore, 0);
 NVIC_EnableIRQ(USART1_IRQn);
 for (;;) {
 xSemaphoreTake(xBinarySemaphore, portMAX_DELAY);
 taskENTER_CRITICAL();
 MCAL_UART_sendString(USE_USART1, (u8*) "\x1b[2J\x1b[H");
 update_with_input();
 MCAL_UART_sendString(USE_USART1, currentString);
 MCAL_UART_sendCharacter(USE_USART1, "\r\n\0");
 MCAL_UART_sendString(USE_USART1, "Score: ");
 UART_intgerToString(score);
 MCAL_UART_sendString(USE_USART1, "\r\n\0");
 MCAL_UART_sendString(USE_USART1, "Current Level: ");
 UART_intgerToString(currentLevel);
 MCAL_UART_sendString(USE_USART1, "\r\n\0");
 taskEXIT_CRITICAL();
 vTaskDelay(300);
 }
 }
 */

int main(void) {
	MCAL_RCC_voidIntiSysClock();
	GPIO_ConfigType GPIO_configPtr1 = { GPIO_PORTA, GPIO_PIN9, AF_MODE,
			OUTPUT_DEFAULT, DEFAULT_SPEED, DEFAULT_PULL };
	GPIO_ConfigType GPIO_configPtr2 = { GPIO_PORTA, GPIO_PIN10, AF_MODE,
			OUTPUT_DEFAULT, DEFAULT_SPEED, DEFAULT_PULL };
	UART_ConfigType UART_configPtr = { USE_USART1, STOP_1, PARITY_DISABLED,
			EVEN_PARITY, OVER16, EIGHT_BITS, 921600 };
	MCAL_RCC_voidIntiSysClock();
	MCAL_RCC_voidEnablePeripheralClock(RCC_AHB1, AHB1_GPIOA);
	MCAL_RCC_voidEnablePeripheralClock(RCC_APB2, APB2_USART1);
	MCAL_GPIO_voidInit(&GPIO_configPtr1);
	MCAL_GPIO_voidInit(&GPIO_configPtr2);
	MCAL_GPIO_voidSetPinAlternateFunction(GPIO_PORTA, GPIO_PIN9, AF7);
	MCAL_GPIO_voidSetPinAlternateFunction(GPIO_PORTA, GPIO_PIN10, AF7);
	MCAL_UART_init(&UART_configPtr);
	MCAL_UART_enableRecieveInterrupt(USE_USART1);
	NVIC_SetPriority(USART1_IRQn, 6);
	*((u32*) 0xe000ed0c) = 0x05FA0000;
	initialize_starting_frame();
	currentString = welcomeString;
// vSemaphoreCreateBinary(xBinarySemaphore);
	xBinarySemaphore = xSemaphoreCreateBinary();
	xTaskCreate(&Frame_Handler, "Frame Handler", 240, NULL, 3, NULL);
	//xTaskCreate(&UART_Input_Handler, "UART Handler", 240, NULL, 4, NULL);
	xTaskCreate(&Game_Update_Handler, "Game Update Handler", 240, NULL, 2,
	NULL);
	xTaskCreate(&Random_Symbols_Handler, "Random Symbols Handler", 240, NULL, 2,
	NULL);
	xTaskCreate(&Special_Symbols_Handler, "Special Symbols Handler", 240, NULL,
			2,
			NULL);
	NVIC_EnableIRQ(USART1_IRQn);

	if (xBinarySemaphore != NULL) {
		vTaskStartScheduler();
	}

	for (;;) {

	}
}

//task with delay 500ms
//task handle UART input
//helper function to update the array
/*
 static inline void __spin_delay_m4(uint32_t cycles) {
 u32 iterations = (cycles + 2) / 3;
 asm volatile(
 ".balign 4;"
 "1:"
 "    subs %0, 1;"
 "    bne 1b;"

 :"+r"(iterations)
 :
 :"memory", "cc");
 }
 */
#if 0
void SysTick_Handler(void)
{
  /* USER CODE BEGIN SysTick_IRQn 0 */

  /* USER CODE END SysTick_IRQn 0 */
  HAL_IncTick();
#if (INCLUDE_xTaskGetSchedulerState == 1 )
  if (xTaskGetSchedulerState() != taskSCHEDULER_NOT_STARTED)
  {
#endif /* INCLUDE_xTaskGetSchedulerState */
  xPortSysTickHandler();
#if (INCLUDE_xTaskGetSchedulerState == 1 )
  }
#endif /* INCLUDE_xTaskGetSchedulerState */
  /* USER CODE BEGIN SysTick_IRQn 1 */

  /* USER CODE END SysTick_IRQn 1 */
}
#endif
