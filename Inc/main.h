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

typedef struct {
	u8 row;
	u8 col;
} Point;

void initialize_starting_frame(void);
u32 XORShift(void);
void update_with_input(void);
void Game_Update_Handler(void *parameters);
void Frame_Handler(void *parameters);
void UART_Input_Handler(void *parameters);
void Random_Symbols_Handler(void *parameters);
void delayMs(unsigned long long n);
void clear_random_symbols(void);
