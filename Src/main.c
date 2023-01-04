#include <stdio.h>
#include "STD_TYPES.h"
#include "RCC_interface.h"
#include "GPIO_interface.h"
#include "UART_interface.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

#include "stm32f446xx.h"
#include "core_cm4.h"

xSemaphoreHandle xBinarySemaphore;
u8 data = 'e';
u8 *currentString = NULL;
u8 frame[50][70];
u8 *welcomeString =
		(u8*) "Welcome to Snake game\r\ns:to start game\r\ne:to end game\r\nUse arrow keys to move the snake.\r\n";

typedef struct {
	u8 row;
	u8 col;
} Point;

u8 snakeLength = 5;
Point snakeHead = { 2, 6 };
Point snakeTail = { 2, 2 };

void fill_String(void) {
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
	snakeLength = 5;
	snakeHead.row = 2;
	snakeHead.col = 6;
	snakeTail.row = 2;
	snakeTail.col = 2;
	for (i = 0; i < snakeLength - 1; i++) {
		frame[2][i + 2] = '*';
	}
	frame[2][snakeLength + 1] = '&';
}

void USART1_IRQHandler(void) {
	portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;
	xSemaphoreGiveFromISR(xBinarySemaphore, &xHigherPriorityTaskWoken);
	data = USART1->DR;
	portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}

void USART1_Logic_Handler(u8 data) {
	switch (data) {
	case 's':
		fill_String();
		currentString = (u8*) frame;
		break;
	case 'e':
		currentString = welcomeString;
		break;
	case '1': //move to left
		if (frame[snakeHead.row][snakeHead.col - 1] == '#') {
			currentString = (u8*) "GAME OVER!,Press 's' to try again";
		} else {
			if (frame[snakeHead.row][snakeHead.col - 1] == '*') {

			} else {
				frame[snakeHead.row][snakeHead.col] = '*';
				frame[snakeHead.row][snakeHead.col - 1] = '&';
				frame[snakeTail.row][snakeTail.col] = ' ';
				snakeHead.col--;
				/*	if ((frame[snakeTail.row][snakeTail.col + 1] == '*'))
				 snakeTail.col++;
				 //here
				 else if (frame[snakeTail.row - 1][snakeTail.col] == '*') {
				 snakeTail.row--;
				 } else if (frame[snakeTail.row][snakeTail.col - 1] == '*')
				 snakeTail.col--;
				 else {
				 snakeTail.row++;
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
		}
		break;
	case '3':
		//move to right
		if (frame[snakeHead.row][snakeHead.col + 1] == '#') {
			currentString = (u8*) "GAME OVER!,Press 's' to try again";
		} else {
			if (frame[snakeHead.row][snakeHead.col + 1] == '*') {

			} else {
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
		}

		break;
	case '5':
		//move up
		if (frame[snakeHead.row - 1][snakeHead.col] == '#') {
			currentString = (u8*) "GAME OVER!,Press 's' to try again";
		} else if (frame[snakeHead.row - 1][snakeHead.col] == '*') {

		} else {
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
		if (frame[snakeHead.row + 1][snakeHead.col] == '#') {
			currentString = (u8*) "GAME OVER!,Press 's' to try again";
		} else if (frame[snakeHead.row + 1][snakeHead.col] == '*') {

		} else {
			frame[snakeHead.row][snakeHead.col] = '*';
			frame[snakeHead.row + 1][snakeHead.col] = '&';
			frame[snakeTail.row][snakeTail.col] = ' ';
			snakeHead.row++;
			/*	if ((frame[snakeTail.row][snakeTail.col + 1] == '*'))
			 snakeTail.col++;
			 else if (frame[snakeTail.row][snakeTail.col - 1] == '*') {
			 snakeTail.col--;
			 } else {
			 snakeTail.row++;
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
	}
}

void Frame_Handler(void *parameters) {
	for (;;) {
		MCAL_UART_sendString(USE_USART1, (u8*) "\x1b[2J\x1b[H");
		taskENTER_CRITICAL();
		USART1_Logic_Handler(data);
		taskEXIT_CRITICAL();
		MCAL_UART_sendString(USE_USART1, currentString);
		vTaskDelay(500);
	}
}

void UART_Input_Handler(void *parameters) {
	xSemaphoreTake(xBinarySemaphore, 0);
	NVIC_EnableIRQ(USART1_IRQn);
	for (;;) {
		xSemaphoreTake(xBinarySemaphore, portMAX_DELAY);
		taskENTER_CRITICAL();
		USART1_Logic_Handler(data);
		taskEXIT_CRITICAL();
	}
}

int main(void) {
	MCAL_RCC_voidIntiSysClock();
	GPIO_ConfigType GPIO_configPtr1 = { GPIO_PORTA, GPIO_PIN9, AF_MODE,
			OUTPUT_DEFAULT, DEFAULT_SPEED, DEFAULT_PULL };
	GPIO_ConfigType GPIO_configPtr2 = { GPIO_PORTA, GPIO_PIN10, AF_MODE,
			OUTPUT_DEFAULT, DEFAULT_SPEED, DEFAULT_PULL };
	UART_ConfigType UART_configPtr = { USE_USART1, STOP_1, PARITY_DISABLED,
			EVEN_PARITY, OVER16, EIGHT_BITS, 460800 };
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
	fill_String();
	currentString = welcomeString;
	vSemaphoreCreateBinary(xBinarySemaphore);
	xBinarySemaphore = xSemaphoreCreateBinary();
	xTaskCreate(&Frame_Handler, "Frame Handler", 240, NULL, 2, NULL);
	xTaskCreate(&UART_Input_Handler, "UART Handler", 240, NULL, 3, NULL);

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
