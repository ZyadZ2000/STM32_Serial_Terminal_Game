/***************************************************************************************/
/***************************************************************************************/
/********************			Author	:	GP TEAM       		************************/
/********************			Layer	:	MCAL				************************/
/********************			SWC		:	UART			    ************************/
/********************			Version	:	1.00				************************/
/***************************************************************************************/
/***************************************************************************************/

#include "BIT_MATH.h"
#include "UART_register.h"
#include "UART_interface.h"
#include <assert.h>

/* *
 * ISRs names are in the startup code
 * */

void MCAL_UART_init(UART_ConfigType *config_ptr) {
	assert(
			(config_ptr->UART_num >= USE_USART1 && config_ptr->UART_num <= USE_USART6) && "invalid UART number");
	switch (config_ptr->UART_num) {
	case USE_USART1:
		USART1->CR1 = (USART1->CR1 & ~(1 << 15))
				| ((config_ptr->oversampling_mode & 1) << 15);
		USART1->CR1 = (USART1->CR1 & ~(1 << 12))
				| ((config_ptr->data_bits & 1) << 12);
		SET_BIT(USART1->CR1, 13);          //UART enable
		USART1->CR1 = (USART1->CR1 & ~(1 << 10))
				| ((config_ptr->parity_mode & 1) << 10);
		USART1->CR1 = (USART1->CR1 & ~(1 << 9))
				| ((config_ptr->parity_bits & 1) << 9);

		USART1->CR2 = (USART1->CR2 & ~(3 << 12))
				| ((config_ptr->stop_bits & 3) << 12);
		assert(
				config_ptr->baud_rate == 2400 || config_ptr->baud_rate == 9600
						|| config_ptr->baud_rate == 19200
						|| config_ptr->baud_rate == 115200
						|| config_ptr->baud_rate == 921600
						|| config_ptr->baud_rate == 460800);
		if (config_ptr->oversampling_mode == OVER16) {
			switch (config_ptr->baud_rate) {
			case 2400:
				USART1->BRR = (USART1->BRR & (0xFFFF0000)) | OVER16_2400;
				break;
			case 9600:

				USART1->BRR = (USART1->BRR & (0xFFFF0000)) | OVER16_9600;
				break;

			case 19200:
				USART1->BRR = (USART1->BRR & (0xFFFF0000)) | OVER16_19200;
				break;
			case 115200:
				USART1->BRR = (USART1->BRR & (0xFFFF0000)) | OVER16_115200;
				break;
			case 460800:
				USART1->BRR = (USART1->BRR & (0xFFFF0000)) | OVER16_460800;
				break;
			case 921600:
				USART1->BRR = (USART1->BRR & (0xFFFF0000)) | OVER16_921600;
				break;
			}
		} else if (config_ptr->oversampling_mode == OVER8) {
			switch (config_ptr->baud_rate) {
			case 2400:
				USART1->BRR = (USART1->BRR & (0xFFFF0000)) | OVER8_2400;
				break;
			case 9600:

				USART1->BRR = (USART1->BRR & (0xFFFF0000)) | OVER8_9600;
				break;

			case 19200:
				USART1->BRR = (USART1->BRR & (0xFFFF0000)) | OVER8_19200;
				break;
			case 115200:
				USART1->BRR = (USART1->BRR & (0xFFFF0000)) | OVER8_115200;
				break;
			case 460800:
				USART1->BRR = (USART1->BRR & (0xFFFF0000)) | OVER8_460800;
				break;
			case 921600:
				USART1->BRR = (USART1->BRR & (0xFFFF0000)) | OVER8_921600;
				break;
			case 2000000:
				USART1->BRR = (USART1->BRR & (0xFFFF0000)) | OVER8_2000000;
				break;
			}
		}

		SET_BIT(USART1->CR1, 3); 		//UART Transmitter enable
		SET_BIT(USART1->CR1, 2); 			//UART Receiver enable
		break;
	case USE_USART2:
		USART2->CR1 = (USART2->CR1 & ~(1 << 15))
				| ((config_ptr->oversampling_mode & 1) << 15);
		USART2->CR1 = (USART2->CR1 & ~(1 << 12))
				| ((config_ptr->data_bits & 1) << 12);
		SET_BIT(USART2->CR1, 13);          //UART enable
		USART2->CR1 = (USART2->CR1 & ~(1 << 10))
				| ((config_ptr->parity_mode & 1) << 10);
		USART2->CR1 = (USART2->CR1 & ~(1 << 9))
				| ((config_ptr->parity_bits & 1) << 9);

		USART2->CR2 = (USART2->CR2 & ~(3 << 12))
				| ((config_ptr->stop_bits & 3) << 12);
		assert(
				config_ptr->baud_rate == 2400 || config_ptr->baud_rate == 9600
						|| config_ptr->baud_rate == 19200
						|| config_ptr->baud_rate == 115200
						|| config_ptr->baud_rate == 921600
						|| config_ptr->baud_rate == 460800);
		if (config_ptr->oversampling_mode == OVER16) {
			switch (config_ptr->baud_rate) {
			case 2400:
				USART2->BRR = (USART2->BRR & (0xFFFF0000)) | OVER16_2400;
				break;
			case 9600:

				USART2->BRR = (USART2->BRR & (0xFFFF0000)) | OVER16_9600;
				break;

			case 19200:
				USART2->BRR = (USART2->BRR & (0xFFFF0000)) | OVER16_19200;
				break;
			case 115200:
				USART2->BRR = (USART2->BRR & (0xFFFF0000)) | OVER16_115200;
				break;
			case 460800:
				USART2->BRR = (USART2->BRR & (0xFFFF0000)) | OVER16_460800;
				break;
			case 921600:
				USART2->BRR = (USART2->BRR & (0xFFFF0000)) | OVER16_921600;
				break;
			}
		} else if (config_ptr->oversampling_mode == OVER8) {
			switch (config_ptr->baud_rate) {
			case 2400:
				USART2->BRR = (USART2->BRR & (0xFFFF0000)) | OVER8_2400;
				break;
			case 9600:

				USART2->BRR = (USART2->BRR & (0xFFFF0000)) | OVER8_9600;
				break;

			case 19200:
				USART2->BRR = (USART2->BRR & (0xFFFF0000)) | OVER8_19200;
				break;
			case 115200:
				USART2->BRR = (USART2->BRR & (0xFFFF0000)) | OVER8_115200;
				break;
			case 460800:
				USART2->BRR = (USART2->BRR & (0xFFFF0000)) | OVER8_460800;
				break;
			case 921600:
				USART2->BRR = (USART2->BRR & (0xFFFF0000)) | OVER8_921600;
				break;
			case 2000000:
				USART2->BRR = (USART2->BRR & (0xFFFF0000)) | OVER8_2000000;
				break;
			}
		}

		SET_BIT(USART2->CR1, 3); 		//UART Transmitter enable
		SET_BIT(USART2->CR1, 2); 			//UART Receiver enable
		break;
	case USE_USART3:
		USART3->CR1 = (USART3->CR1 & ~(1 << 15))
				| ((config_ptr->oversampling_mode & 1) << 15);
		USART3->CR1 = (USART3->CR1 & ~(1 << 12))
				| ((config_ptr->data_bits & 1) << 12);
		SET_BIT(USART3->CR1, 13);          //UART enable
		USART3->CR1 = (USART3->CR1 & ~(1 << 10))
				| ((config_ptr->parity_mode & 1) << 10);
		USART3->CR1 = (USART3->CR1 & ~(1 << 9))
				| ((config_ptr->parity_bits & 1) << 9);

		USART3->CR2 = (USART3->CR2 & ~(3 << 12))
				| ((config_ptr->stop_bits & 3) << 12);
		assert(
				config_ptr->baud_rate == 2400 || config_ptr->baud_rate == 9600
						|| config_ptr->baud_rate == 19200
						|| config_ptr->baud_rate == 115200
						|| config_ptr->baud_rate == 921600
						|| config_ptr->baud_rate == 460800);
		if (config_ptr->oversampling_mode == OVER16) {
			switch (config_ptr->baud_rate) {
			case 2400:
				USART3->BRR = (USART3->BRR & (0xFFFF0000)) | OVER16_2400;
				break;
			case 9600:

				USART3->BRR = (USART3->BRR & (0xFFFF0000)) | OVER16_9600;
				break;

			case 19200:
				USART3->BRR = (USART3->BRR & (0xFFFF0000)) | OVER16_19200;
				break;
			case 115200:
				USART3->BRR = (USART3->BRR & (0xFFFF0000)) | OVER16_115200;
				break;
			case 460800:
				USART3->BRR = (USART3->BRR & (0xFFFF0000)) | OVER16_460800;
				break;
			case 921600:
				USART3->BRR = (USART3->BRR & (0xFFFF0000)) | OVER16_921600;
				break;
			}
		} else if (config_ptr->oversampling_mode == OVER8) {
			switch (config_ptr->baud_rate) {
			case 2400:
				USART3->BRR = (USART3->BRR & (0xFFFF0000)) | OVER8_2400;
				break;
			case 9600:

				USART3->BRR = (USART3->BRR & (0xFFFF0000)) | OVER8_9600;
				break;

			case 19200:
				USART3->BRR = (USART3->BRR & (0xFFFF0000)) | OVER8_19200;
				break;
			case 115200:
				USART3->BRR = (USART3->BRR & (0xFFFF0000)) | OVER8_115200;
				break;
			case 460800:
				USART3->BRR = (USART3->BRR & (0xFFFF0000)) | OVER8_460800;
				break;
			case 921600:
				USART3->BRR = (USART3->BRR & (0xFFFF0000)) | OVER8_921600;
				break;
			case 2000000:
				USART3->BRR = (USART3->BRR & (0xFFFF0000)) | OVER8_2000000;
				break;
			}
		}

		SET_BIT(USART3->CR1, 3); 		//UART Transmitter enable
		SET_BIT(USART3->CR1, 2); 			//UART Receiver enable
		break;
	case USE_UART4:
		UART4->CR1 = (UART4->CR1 & ~(1 << 15))
				| ((config_ptr->oversampling_mode & 1) << 15);
		UART4->CR1 = (UART4->CR1 & ~(1 << 12))
				| ((config_ptr->data_bits & 1) << 12);
		SET_BIT(UART4->CR1, 13);          //UART enable
		UART4->CR1 = (UART4->CR1 & ~(1 << 10))
				| ((config_ptr->parity_mode & 1) << 10);
		UART4->CR1 = (UART4->CR1 & ~(1 << 9))
				| ((config_ptr->parity_bits & 1) << 9);

		UART4->CR2 = (UART4->CR2 & ~(3 << 12))
				| ((config_ptr->stop_bits & 3) << 12);
		assert(
				config_ptr->baud_rate == 2400 || config_ptr->baud_rate == 9600
						|| config_ptr->baud_rate == 19200
						|| config_ptr->baud_rate == 115200
						|| config_ptr->baud_rate == 921600
						|| config_ptr->baud_rate == 460800);
		if (config_ptr->oversampling_mode == OVER16) {
			switch (config_ptr->baud_rate) {
			case 2400:
				UART4->BRR = (UART4->BRR & (0xFFFF0000)) | OVER16_2400;
				break;
			case 9600:

				UART4->BRR = (UART4->BRR & (0xFFFF0000)) | OVER16_9600;
				break;

			case 19200:
				UART4->BRR = (UART4->BRR & (0xFFFF0000)) | OVER16_19200;
				break;
			case 115200:
				UART4->BRR = (UART4->BRR & (0xFFFF0000)) | OVER16_115200;
				break;
			case 460800:
				UART4->BRR = (UART4->BRR & (0xFFFF0000)) | OVER16_460800;
				break;
			case 921600:
				UART4->BRR = (UART4->BRR & (0xFFFF0000)) | OVER16_921600;
				break;
			}
		} else if (config_ptr->oversampling_mode == OVER8) {
			switch (config_ptr->baud_rate) {
			case 2400:
				UART4->BRR = (UART4->BRR & (0xFFFF0000)) | OVER8_2400;
				break;
			case 9600:

				UART4->BRR = (UART4->BRR & (0xFFFF0000)) | OVER8_9600;
				break;

			case 19200:
				UART4->BRR = (UART4->BRR & (0xFFFF0000)) | OVER8_19200;
				break;
			case 115200:
				UART4->BRR = (UART4->BRR & (0xFFFF0000)) | OVER8_115200;
				break;
			case 460800:
				UART4->BRR = (UART4->BRR & (0xFFFF0000)) | OVER8_460800;
				break;
			case 921600:
				UART4->BRR = (UART4->BRR & (0xFFFF0000)) | OVER8_921600;
				break;
			case 2000000:
				UART4->BRR = (UART4->BRR & (0xFFFF0000)) | OVER8_2000000;
				break;
			}
		}

		SET_BIT(UART4->CR1, 3); 		//UART Transmitter enable
		SET_BIT(UART4->CR1, 2); 			//UART Receiver enable
		break;
	case USE_UART5:
		UART5->CR1 = (UART5->CR1 & ~(1 << 15))
				| ((config_ptr->oversampling_mode & 1) << 15);
		UART5->CR1 = (UART5->CR1 & ~(1 << 12))
				| ((config_ptr->data_bits & 1) << 12);
		SET_BIT(UART5->CR1, 13);          //UART enable
		UART5->CR1 = (UART5->CR1 & ~(1 << 10))
				| ((config_ptr->parity_mode & 1) << 10);
		UART5->CR1 = (UART5->CR1 & ~(1 << 9))
				| ((config_ptr->parity_bits & 1) << 9);

		UART5->CR2 = (UART5->CR2 & ~(3 << 12))
				| ((config_ptr->stop_bits & 3) << 12);
		assert(
				config_ptr->baud_rate == 2400 || config_ptr->baud_rate == 9600
						|| config_ptr->baud_rate == 19200
						|| config_ptr->baud_rate == 115200
						|| config_ptr->baud_rate == 921600
						|| config_ptr->baud_rate == 460800);
		if (config_ptr->oversampling_mode == OVER16) {
			switch (config_ptr->baud_rate) {
			case 2400:
				UART5->BRR = (UART5->BRR & (0xFFFF0000)) | OVER16_2400;
				break;
			case 9600:

				UART5->BRR = (UART5->BRR & (0xFFFF0000)) | OVER16_9600;
				break;

			case 19200:
				UART5->BRR = (UART5->BRR & (0xFFFF0000)) | OVER16_19200;
				break;
			case 115200:
				UART5->BRR = (UART5->BRR & (0xFFFF0000)) | OVER16_115200;
				break;
			case 460800:
				UART5->BRR = (UART5->BRR & (0xFFFF0000)) | OVER16_460800;
				break;
			case 921600:
				UART5->BRR = (UART5->BRR & (0xFFFF0000)) | OVER16_921600;
				break;
			}
		} else if (config_ptr->oversampling_mode == OVER8) {
			switch (config_ptr->baud_rate) {
			case 2400:
				UART5->BRR = (UART5->BRR & (0xFFFF0000)) | OVER8_2400;
				break;
			case 9600:

				UART5->BRR = (UART5->BRR & (0xFFFF0000)) | OVER8_9600;
				break;

			case 19200:
				UART5->BRR = (UART5->BRR & (0xFFFF0000)) | OVER8_19200;
				break;
			case 115200:
				UART5->BRR = (UART5->BRR & (0xFFFF0000)) | OVER8_115200;
				break;
			case 460800:
				UART5->BRR = (UART5->BRR & (0xFFFF0000)) | OVER8_460800;
				break;
			case 921600:
				UART5->BRR = (UART5->BRR & (0xFFFF0000)) | OVER8_921600;
				break;
			case 2000000:
				UART5->BRR = (UART5->BRR & (0xFFFF0000)) | OVER8_2000000;
				break;
			}
		}

		SET_BIT(UART5->CR1, 3); 		//UART Transmitter enable
		SET_BIT(UART5->CR1, 2); 			//UART Receiver enable
		break;
	case USE_USART6:
		USART6->CR1 = (USART6->CR1 & ~(1 << 15))
				| ((config_ptr->oversampling_mode & 1) << 15);
		USART6->CR1 = (USART6->CR1 & ~(1 << 12))
				| ((config_ptr->data_bits & 1) << 12);
		SET_BIT(USART6->CR1, 13);          //UART enable
		USART6->CR1 = (USART6->CR1 & ~(1 << 10))
				| ((config_ptr->parity_mode & 1) << 10);
		USART6->CR1 = (USART6->CR1 & ~(1 << 9))
				| ((config_ptr->parity_bits & 1) << 9);

		USART6->CR2 = (USART6->CR2 & ~(3 << 12))
				| ((config_ptr->stop_bits & 3) << 12);
		assert(
				config_ptr->baud_rate == 2400 || config_ptr->baud_rate == 9600
						|| config_ptr->baud_rate == 19200
						|| config_ptr->baud_rate == 115200
						|| config_ptr->baud_rate == 921600
						|| config_ptr->baud_rate == 460800);
		if (config_ptr->oversampling_mode == OVER16) {
			switch (config_ptr->baud_rate) {
			case 2400:
				USART6->BRR = (USART6->BRR & (0xFFFF0000)) | OVER16_2400;
				break;
			case 9600:

				USART6->BRR = (USART6->BRR & (0xFFFF0000)) | OVER16_9600;
				break;

			case 19200:
				USART6->BRR = (USART6->BRR & (0xFFFF0000)) | OVER16_19200;
				break;
			case 115200:
				USART6->BRR = (USART6->BRR & (0xFFFF0000)) | OVER16_115200;
				break;
			case 460800:
				USART6->BRR = (USART6->BRR & (0xFFFF0000)) | OVER16_460800;
				break;
			case 921600:
				USART6->BRR = (USART6->BRR & (0xFFFF0000)) | OVER16_921600;
				break;
			}
		} else if (config_ptr->oversampling_mode == OVER8) {
			switch (config_ptr->baud_rate) {
			case 2400:
				USART6->BRR = (USART6->BRR & (0xFFFF0000)) | OVER8_2400;
				break;
			case 9600:

				USART6->BRR = (USART6->BRR & (0xFFFF0000)) | OVER8_9600;
				break;

			case 19200:
				USART6->BRR = (USART6->BRR & (0xFFFF0000)) | OVER8_19200;
				break;
			case 115200:
				USART6->BRR = (USART6->BRR & (0xFFFF0000)) | OVER8_115200;
				break;
			case 460800:
				USART6->BRR = (USART6->BRR & (0xFFFF0000)) | OVER8_460800;
				break;
			case 921600:
				USART6->BRR = (USART6->BRR & (0xFFFF0000)) | OVER8_921600;
				break;
			case 2000000:
				USART6->BRR = (USART6->BRR & (0xFFFF0000)) | OVER8_2000000;
				break;
			}
		}

		SET_BIT(USART6->CR1, 3); 		//UART Transmitter enable
		SET_BIT(USART6->CR1, 2); 			//UART Receiver enable
	}
}

void MCAL_UART_enableRecieveInterrupt(u8 UART_num) {
	assert(
			(UART_num >= USE_USART1 && UART_num <= USE_USART6) && "invalid UART number");
	switch (UART_num) {
	case USE_USART1:
		SET_BIT(USART1->CR1, 5);		//RXNEIE: RXNE interrupt enable
		break;
	case USE_USART2:
		SET_BIT(USART2->CR1, 5);		//RXNEIE: RXNE interrupt enable
		break;
	case USE_USART3:
		SET_BIT(USART3->CR1, 5);		//RXNEIE: RXNE interrupt enable
		break;
	case USE_UART4:
		SET_BIT(UART4->CR1, 5);		//RXNEIE: RXNE interrupt enable
		break;
	case USE_UART5:
		SET_BIT(UART5->CR1, 5);		//RXNEIE: RXNE interrupt enable
		break;
	case USE_USART6:
		SET_BIT(USART6->CR1, 5);		//RXNEIE: RXNE interrupt enable
	}

}
void MCAL_UART_disableRecieveInterrupt(u8 UART_num) {
	assert(
			(UART_num >= USE_USART1 && UART_num <= USE_USART6) && "invalid UART number");
	switch (UART_num) {
	case USE_USART1:
		CLR_BIT(USART1->CR1, 5);		//RXNEIE: RXNE interrupt disable
		break;
	case USE_USART2:
		CLR_BIT(USART2->CR1, 5);		//RXNEIE: RXNE interrupt disable
		break;
	case USE_USART3:
		CLR_BIT(USART3->CR1, 5);		//RXNEIE: RXNE interrupt disable
		break;
	case USE_UART4:
		CLR_BIT(UART4->CR1, 5);		//RXNEIE: RXNE interrupt disable
		break;
	case USE_UART5:
		CLR_BIT(UART5->CR1, 5);		//RXNEIE: RXNE interrupt disable
		break;
	case USE_USART6:
		CLR_BIT(USART6->CR1, 5);		//RXNEIE: RXNE interrupt disable
	}
}
void MCAL_UART_enableTransmitInterrupt(u8 UART_num) {
	assert(
			(UART_num >= USE_USART1 && UART_num <= USE_USART6) && "invalid UART number");
	switch (UART_num) {
	case USE_USART1:
		SET_BIT(USART1->CR1, 7);		//TXE interrupt enable
		break;
	case USE_USART2:
		SET_BIT(USART2->CR1, 7);		//TXE interrupt enable
		break;
	case USE_USART3:
		SET_BIT(USART3->CR1, 7);		//TXE interrupt enable
		break;
	case USE_UART4:
		SET_BIT(UART4->CR1, 7);		//TXE interrupt enable
		break;
	case USE_UART5:
		SET_BIT(UART5->CR1, 7);		//TXE interrupt enable
		break;
	case USE_USART6:
		SET_BIT(USART6->CR1, 7);		//TXE interrupt enable
	}
}
void MCAL_UART_disableTransmitInterrupt(u8 UART_num) {
	assert(
			(UART_num >= USE_USART1 && UART_num <= USE_USART6) && "invalid UART number");

	switch (UART_num) {
	case USE_USART1:
		CLR_BIT(USART1->CR1, 7);		//TXE interrupt disable
		break;
	case USE_USART2:
		CLR_BIT(USART2->CR1, 7);		//TXE interrupt disable
		break;
	case USE_USART3:
		CLR_BIT(USART3->CR1, 7);		//TXE interrupt disable
		break;
	case USE_UART4:
		CLR_BIT(UART4->CR1, 7);		//TXE interrupt disable
		break;
	case USE_UART5:
		CLR_BIT(UART5->CR1, 7);		//TXE interrupt disable
		break;
	case USE_USART6:
		CLR_BIT(USART6->CR1, 7);		//TXE interrupt disable
	}
}
void MCAL_UART_sendCharacter(u8 UART_num, u8 data) {
	assert(
			(UART_num >= USE_USART1 && UART_num <= USE_USART6) && "invalid UART number");
	switch (UART_num) {
	case USE_USART1:
		while (GET_BIT(USART1->SR, 7) == 0) {//TXE: Transmit data register empty

		}
		;
		USART1->DR = (USART1->DR & ~(0x000000FF)) | (data);
		CLR_BIT(USART1->SR, 7);
		break;
	case USE_USART2:
		while (GET_BIT(USART2->SR, 7) == 0) {//TXE: Transmit data register empty

		}
		;
		USART2->DR = (USART2->DR & ~(0x000000FF)) | (data);
		CLR_BIT(USART2->SR, 7);
		break;
	case USE_USART3:
		while (GET_BIT(USART3->SR, 7) == 0) {//TXE: Transmit data register empty

		}
		;
		USART3->DR = (USART3->DR & ~(0x000000FF)) | (data);
		CLR_BIT(USART3->SR, 7);
		break;
	case USE_UART4:
		while (GET_BIT(UART4->SR, 7) == 0) {//TXE: Transmit data register empty

		}
		;
		UART4->DR = (UART4->DR & ~(0x000000FF)) | (data);
		CLR_BIT(UART4->SR, 7);
		break;
	case USE_UART5:
		while (GET_BIT(UART5->SR, 7) == 0) {//TXE: Transmit data register empty

		}
		;
		UART5->DR = (UART5->DR & ~(0x000000FF)) | (data);
		CLR_BIT(UART5->SR, 7);
		break;
	case USE_USART6:
		while (GET_BIT(USART6->SR, 7) == 0) {//TXE: Transmit data register empty

		}
		;
		USART6->DR = (USART6->DR & ~(0x000000FF)) | (data);
		CLR_BIT(USART6->SR, 7);
	}

}

void MCAL_UART_sendString(u8 UART_num, u8 *data) {
	while (*data != '\0') {
		MCAL_UART_sendCharacter(UART_num, *data);
		data++;
	}
}

u8 MCAL_UART_recieveCharacter(u8 UART_num) {
	u8 data;
	assert(
			(UART_num >= USE_USART1 && UART_num <= USE_USART6) && "invalid UART number");
	switch (UART_num) {
	case USE_USART1:
		while (GET_BIT(USART1->SR, 5) == 0)
			//RXNE: Read data register not empty
			;
		data = (USART1->DR & 0x000000FF);
		CLR_BIT(USART1->SR, 5);
		break;
	case USE_USART2:
		while (GET_BIT(USART2->SR, 5) == 0)
			//RXNE: Read data register not empty
			;
		data = (USART2->DR & 0x000000FF);
		CLR_BIT(USART2->SR, 5);
		break;
	case USE_USART3:
		while (GET_BIT(USART3->SR, 5) == 0)
			//RXNE: Read data register not empty
			;
		data = (USART3->DR & 0x000000FF);
		CLR_BIT(USART3->SR, 5);
		break;
	case USE_UART4:
		while (GET_BIT(UART4->SR, 5) == 0)
			//RXNE: Read data register not empty
			;
		data = (UART4->DR & 0x000000FF);
		CLR_BIT(UART4->SR, 5);
		break;
	case USE_UART5:
		while (GET_BIT(UART5->SR, 5) == 0)
			//RXNE: Read data register not empty
			;
		data = (UART5->DR & 0x000000FF);
		CLR_BIT(UART5->SR, 5);
		break;
	case USE_USART6:
		while (GET_BIT(USART6->SR, 5) == 0)
			//RXNE: Read data register not empty
			;
		data = (USART6->DR & 0x000000FF);
		CLR_BIT(USART6->SR, 5);
	}
	return data;

}

void MCAL_UART_recieveString(u8 UART_num, u8 *data) {
	u8 recieved = MCAL_UART_recieveCharacter(UART_num);
	while (recieved != '#') {
		*data = recieved;
		data++;
		recieved = MCAL_UART_recieveCharacter(UART_num);
	}
	*data = '\0';
}
