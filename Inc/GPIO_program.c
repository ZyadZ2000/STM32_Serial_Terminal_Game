/***************************************************************************************/
/***************************************************************************************/
/********************			Author	:	Nada Alaa			************************/
/********************			Layer	:	MCAL				************************/
/********************			SWC		:	GPIO			    ************************/
/********************			Version	:	1.00				************************/
/***************************************************************************************/
/***************************************************************************************/

#include "BIT_MATH.h"
#include "GPIO_register.h"
#include "GPIO_interface.h"
#include <assert.h>


static void LCKR_voidWriteSeq(volatile u32 *Copy_pu32LCKRegister);

/* Initialize All Ports Value & Mode Configuration */

void MCAL_GPIO_voidInit(GPIO_ConfigType *configPtr) {
	assert(
			configPtr->portID < NUM_OF_PORTS && "Exceeded available number of ports");
	switch (configPtr->portID) {
	case GPIO_PORTA:
		GPIOA->MODER = ((GPIOA->MODER) & ~(2 << (2 * configPtr->pinID)))
				| ((configPtr->PinMode & 0XFFFF)
						<< (2 * (configPtr->pinID & 0XFFFF)));
		GPIOA->OTYPER = ((GPIOA->OTYPER) & ~(1 << (configPtr->pinID)))
				| ((configPtr->outputType & 0XFFFF)
						<< (configPtr->pinID & 0XFFFF));
		GPIOA->OSPEEDR = ((GPIOA->OSPEEDR) & ~(2 << (2 * configPtr->pinID)))
				| ((configPtr->speed & 0XFFFF)
						<< (2 * (configPtr->pinID & 0XFFFF)));
		GPIOA->PUPDR = ((GPIOA->PUPDR) & ~(2 << (2 * configPtr->pinID)))
				| ((configPtr->PullUpDown & 0XFFFF)
						<< (2 * (configPtr->pinID & 0XFFFF)));
		break;

	case GPIO_PORTB:
		GPIOB->MODER = ((GPIOB->MODER) & ~(2 << (2 * configPtr->pinID)))
				| ((configPtr->PinMode & 0XFFFF)
						<< (2 * (configPtr->pinID & 0XFFFF)));
		GPIOB->OTYPER = ((GPIOB->OTYPER) & ~(1 << (configPtr->pinID)))
				| ((configPtr->outputType & 0XFFFF)
						<< (configPtr->pinID & 0XFFFF));
		GPIOB->OSPEEDR = ((GPIOB->OSPEEDR) & ~(2 << (2 * configPtr->pinID)))
				| ((configPtr->speed & 0XFFFF)
						<< (2 * (configPtr->pinID & 0XFFFF)));
		GPIOB->PUPDR = ((GPIOB->PUPDR) & ~(2 << (2 * configPtr->pinID)))
				| ((configPtr->PullUpDown & 0XFFFF)
						<< (2 * (configPtr->pinID & 0XFFFF)));
		break;
	case GPIO_PORTC:
		GPIOC->MODER = ((GPIOC->MODER) & ~(2 << (2 * configPtr->pinID)))
				| ((configPtr->PinMode & 0XFFFF)
						<< (2 * (configPtr->pinID & 0XFFFF)));
		GPIOC->OTYPER = ((GPIOC->OTYPER) & ~(1 << (configPtr->pinID)))
				| ((configPtr->outputType & 0XFFFF)
						<< (configPtr->pinID & 0XFFFF));
		GPIOC->OSPEEDR = ((GPIOC->OSPEEDR) & ~(2 << (2 * configPtr->pinID)))
				| ((configPtr->speed & 0XFFFF)
						<< (2 * (configPtr->pinID & 0XFFFF)));
		GPIOC->PUPDR = ((GPIOC->PUPDR) & ~(2 << (2 * configPtr->pinID)))
				| ((configPtr->PullUpDown & 0XFFFF)
						<< (2 * (configPtr->pinID & 0XFFFF)));
		break;
	case GPIO_PORTD:
		GPIOD->MODER = ((GPIOD->MODER) & ~(2 << (2 * configPtr->pinID)))
				| ((configPtr->PinMode & 0XFFFF)
						<< (2 * (configPtr->pinID & 0XFFFF)));
		GPIOD->OTYPER = ((GPIOD->OTYPER) & ~(1 << (configPtr->pinID)))
				| ((configPtr->outputType & 0XFFFF)
						<< (configPtr->pinID & 0XFFFF));
		GPIOD->OSPEEDR = ((GPIOD->OSPEEDR) & ~(2 << (2 * configPtr->pinID)))
				| ((configPtr->speed & 0XFFFF)
						<< (2 * (configPtr->pinID & 0XFFFF)));
		GPIOD->PUPDR = ((GPIOD->PUPDR) & ~(2 << (2 * configPtr->pinID)))
				| ((configPtr->PullUpDown & 0XFFFF)
						<< (2 * (configPtr->pinID & 0XFFFF)));
		break;
	case GPIO_PORTH:
		GPIOH->MODER = ((GPIOH->MODER) & ~(2 << (2 * configPtr->pinID)))
				| ((configPtr->PinMode & 0XFFFF)
						<< (2 * (configPtr->pinID & 0XFFFF)));
		GPIOH->OTYPER = ((GPIOH->OTYPER) & ~(1 << (configPtr->pinID)))
				| ((configPtr->outputType & 0XFFFF)
						<< (configPtr->pinID & 0XFFFF));
		GPIOH->OSPEEDR = ((GPIOH->OSPEEDR) & ~(2 << (2 * configPtr->pinID)))
				| ((configPtr->speed & 0XFFFF)
						<< (2 * (configPtr->pinID & 0XFFFF)));
		GPIOH->PUPDR = ((GPIOH->PUPDR) & ~(2 << (2 * configPtr->pinID)))
				| ((configPtr->PullUpDown & 0XFFFF)
						<< (2 * (configPtr->pinID & 0XFFFF)));
		break;
	}
}

/* Set Pin Value of a Port To Be High or Low */

void MCAL_GPIO_voidSetPinValue(u8 Copy_u8Port, u8 Copy_u8Pin, u8 Copy_u8Value) {
	assert(Copy_u8Port < NUM_OF_PORTS && "Exceeded available number of ports");
	/* Check if the Pin is Low:reset*/
	if (Copy_u8Value == PIN_LOW) {
		switch (Copy_u8Port) {
		case GPIO_PORTA:
			assert(
					Copy_u8Pin < NUM_OF_PINS_PER_PORT_ABC && "Exceeded available number of pins");
			GPIOA->BSRR = (1 << (Copy_u8Pin + 16));
			break;		//PORT A
		case GPIO_PORTB:
			assert(
					Copy_u8Pin < NUM_OF_PINS_PER_PORT_ABC && "Exceeded available number of pins");
			GPIOB->BSRR = (1 << (Copy_u8Pin + 16));
			break;		//PORT B
		case GPIO_PORTC:
			assert(
					Copy_u8Pin < NUM_OF_PINS_PER_PORT_ABC && "Exceeded available number of pins");
			GPIOC->BSRR = (1 << (Copy_u8Pin + 16));
			break;		//PORT C
		case GPIO_PORTD:
			assert(
					Copy_u8Pin < NUM_OF_PINS_PER_PORTD && "Exceeded available number of pins");
			GPIOD->BSRR = (1 << (Copy_u8Pin + 16));
			break;		//PORT D
		case GPIO_PORTH:
			assert(
					Copy_u8Pin < NUM_OF_PINS_PER_PORTH && "Exceeded available number of pins");
			GPIOH->BSRR = (1 << (Copy_u8Pin + 16));
			break;		//PORT H
		}
	}
	/* Check if the Pin is High:set */
	else if (Copy_u8Value == PIN_HIGH) {
		switch (Copy_u8Port) {
		case GPIO_PORTA:
			assert(
					Copy_u8Pin < NUM_OF_PINS_PER_PORT_ABC && "Exceeded available number of pins");
			GPIOA->BSRR = (1 << Copy_u8Pin);
			break;		//PORT A
		case GPIO_PORTB:
			assert(
					Copy_u8Pin < NUM_OF_PINS_PER_PORT_ABC && "Exceeded available number of pins");
			GPIOB->BSRR = (1 << Copy_u8Pin);
			break;		//PORT B
		case GPIO_PORTC:
			assert(
					Copy_u8Pin < NUM_OF_PINS_PER_PORT_ABC && "Exceeded available number of pins");
			GPIOC->BSRR = (1 << Copy_u8Pin);
			break;		//PORT C
		case GPIO_PORTD:
			assert(
					Copy_u8Pin < NUM_OF_PINS_PER_PORTD && "Exceeded available number of pins");
			GPIOD->BSRR = (1 << Copy_u8Pin);
			break;		//PORT D
		case GPIO_PORTH:
			assert(
					Copy_u8Pin < NUM_OF_PINS_PER_PORTH && "Exceeded available number of pins");
			GPIOH->BSRR = (1 << Copy_u8Pin);
			break;		//PORT H
		}
	}
}

void MCAL_GPIO_voidSetPinAlternateFunction(u8 Copy_u8Port, u8 Copy_u8Pin,
		u8 AF_NUM) {
	assert(Copy_u8Port < NUM_OF_PORTS && "Exceeded available number of ports");
	assert(AF_NUM < 15 && "Exceeded available number of alternate functions");
	if (Copy_u8Pin <= 7) {
		switch (Copy_u8Port) {
		case GPIO_PORTA:
			assert(
					Copy_u8Pin < NUM_OF_PINS_PER_PORT_ABC && "Exceeded available number of pins");
			GPIOA->AFRL = (GPIOA->AFRL & ~(15 << (4 * Copy_u8Pin)))
					| (AF_NUM << (4 * Copy_u8Pin));
			break;		//PORT A
		case GPIO_PORTB:
			assert(
					Copy_u8Pin < NUM_OF_PINS_PER_PORT_ABC && "Exceeded available number of pins");
			GPIOB->AFRL = (GPIOB->AFRL & ~(15 << (4 * Copy_u8Pin)))
					| (AF_NUM << (4 * Copy_u8Pin));
			break;		//PORT B
		case GPIO_PORTC:
			assert(
					Copy_u8Pin < NUM_OF_PINS_PER_PORT_ABC && "Exceeded available number of pins");
			GPIOC->AFRL = (GPIOC->AFRL & ~(15 << (4 * Copy_u8Pin)))
					| (AF_NUM << (4 * Copy_u8Pin));
			break;		//PORT C
		case GPIO_PORTD:
			assert(
					Copy_u8Pin < NUM_OF_PINS_PER_PORTD && "Exceeded available number of pins");
			GPIOD->AFRL = (GPIOD->AFRL & ~(15 << (4 * Copy_u8Pin)))
					| (AF_NUM << (4 * Copy_u8Pin));
			break;		//PORT D
		case GPIO_PORTH:
			assert(
					Copy_u8Pin < NUM_OF_PINS_PER_PORTH && "Exceeded available number of pins");
			GPIOH->AFRL = (GPIOH->AFRL & ~(15 << (4 * Copy_u8Pin)))
					| (AF_NUM << (4 * Copy_u8Pin));
			break;		//PORT H
		}
	} else {
		switch (Copy_u8Port) {
		case GPIO_PORTA:
			assert(
					Copy_u8Pin < NUM_OF_PINS_PER_PORT_ABC && "Exceeded available number of pins");
			GPIOA->AFRH =
					(GPIOA->AFRH & ~(0x0000000F << (4 * (Copy_u8Pin - 8))))
							| (AF_NUM << (4 * (Copy_u8Pin - 8)));
			break;		//PORT A
		case GPIO_PORTB:
			assert(
					Copy_u8Pin < NUM_OF_PINS_PER_PORT_ABC && "Exceeded available number of pins");
			GPIOB->AFRH = (GPIOB->AFRH & ~(15 << (4 * (Copy_u8Pin - 8))))
					| (AF_NUM << (4 * (Copy_u8Pin - 8)));
			break;		//PORT B
		case GPIO_PORTC:
			assert(
					Copy_u8Pin < NUM_OF_PINS_PER_PORT_ABC && "Exceeded available number of pins");
			GPIOC->AFRH = (GPIOC->AFRH & ~(15 << (4 * (Copy_u8Pin - 8))))
					| (AF_NUM << (4 * (Copy_u8Pin - 8)));
			break;		//PORT C
		case GPIO_PORTD:
			assert(
					Copy_u8Pin < NUM_OF_PINS_PER_PORTD && "Exceeded available number of pins");
			GPIOD->AFRH = (GPIOD->AFRH & ~(15 << (4 * (Copy_u8Pin - 8))))
					| (AF_NUM << (4 * (Copy_u8Pin - 8)));
			break;		//PORT D
		case GPIO_PORTH:
			assert(
					Copy_u8Pin < NUM_OF_PINS_PER_PORTH && "Exceeded available number of pins");
			GPIOH->AFRH = (GPIOH->AFRH & ~(15 << (4 * (Copy_u8Pin - 8))))
					| (AF_NUM << (4 * (Copy_u8Pin - 8)));
			break;		//PORT H
		}
	}
}

/* Get The Value of a Pin of specific Port */

u8 MCAL_GPIO_u8GetPinValue(u8 Copy_u8Port, u8 Copy_u8Pin) {
	assert(Copy_u8Port < NUM_OF_PORTS && "Exceeded available number of ports");
	u8 Pin_Value;

	switch (Copy_u8Port) {
	case GPIO_PORTA:
		assert(
				Copy_u8Pin < NUM_OF_PINS_PER_PORT_ABC && "Exceeded available number of pins");
		Pin_Value = GET_BIT(GPIOA->IDR, Copy_u8Pin);
	case GPIO_PORTB:
		assert(
				Copy_u8Pin < NUM_OF_PINS_PER_PORT_ABC && "Exceeded available number of pins");
		Pin_Value = GET_BIT(GPIOB->IDR, Copy_u8Pin);
		break;		//PORT B
	case GPIO_PORTC:
		assert(
				Copy_u8Pin < NUM_OF_PINS_PER_PORT_ABC && "Exceeded available number of pins");
		Pin_Value = GET_BIT(GPIOC->IDR, Copy_u8Pin);
		break;		//PORT C
	case GPIO_PORTD:
		assert(
				Copy_u8Pin < NUM_OF_PINS_PER_PORTD && "Exceeded available number of pins");
		Pin_Value = GET_BIT(GPIOD->IDR, Copy_u8Pin);
		break;		//PORT D
	case GPIO_PORTH:
		assert(
				Copy_u8Pin < NUM_OF_PINS_PER_PORTH && "Exceeded available number of pins");
		Pin_Value = GET_BIT(GPIOH->IDR, Copy_u8Pin);
		break;		//PORT H
	default:
		Pin_Value = NOK;
		break;		//Error State NOT OK
	}
	return Pin_Value;
}

/* Set Port Value To Be High or Low */

void MCAL_GPIO_voidSetPortValue(u8 Copy_u8Port, u16 Copy_u16Value) {
	u8 Local_u8ErrorState = OK;

	/* Check the Pin is less than or equal 15 */
	if (Copy_u8Port >= NUM_OF_PORTS) {
		Local_u8ErrorState = NOK;
	} else {
		switch (Copy_u8Port) {
		case GPIO_PORTA:
			GPIOA->ODR = Copy_u16Value;
			break;
		case GPIO_PORTB:
			GPIOB->ODR = Copy_u16Value;
			break;

		case GPIO_PORTC:
			GPIOC->ODR = Copy_u16Value;
			break;

		case GPIO_PORTD:
			GPIOD->ODR = Copy_u16Value;
			break;

		case GPIO_PORTH:
			GPIOH->ODR = Copy_u16Value;
			break;
		default:
			Local_u8ErrorState = NOK;
			break;
		}
	}
	assert(Local_u8ErrorState != NOK);
}

/* Lock Pin of a Port To Prevent Changing Configuration Until Reset */

void MCAL_GPIO_voidSetPinLock(u8 Copy_u8Port, u8 Copy_u8Pin,
		u8 Copy_u8LockStatus) {
	/* Error state OK */
	u8 Local_u8ErrorState = OK;

	/* Check the Pin is less than or equal 15 */
	if (Copy_u8Pin >= NUM_OF_PINS_PER_PORT_ABC || Copy_u8Port >= NUM_OF_PORTS) {
		Local_u8ErrorState = NOK;
	} else {
		/* Check if the Pin Status is Lock */
		if (Copy_u8LockStatus == PIN_LOCK) {
			switch (Copy_u8Port) {
			case GPIO_PORTA:
				SET_BIT(GPIOA->LCKR, Copy_u8Pin);
				LCKR_voidWriteSeq(&(GPIOA->LCKR));
				break;	//PORT A
			case GPIO_PORTB:
				SET_BIT(GPIOB->LCKR, Copy_u8Pin);
				LCKR_voidWriteSeq(&(GPIOB->LCKR));
				break;	//PORT B
			case GPIO_PORTC:
				SET_BIT(GPIOC->LCKR, Copy_u8Pin);
				LCKR_voidWriteSeq(&(GPIOC->LCKR));
				break;	//PORT C
			case GPIO_PORTD:
				SET_BIT(GPIOD->LCKR, Copy_u8Pin);
				LCKR_voidWriteSeq(&(GPIOD->LCKR));
				break;	//PORT D
			case GPIO_PORTH:
				SET_BIT(GPIOH->LCKR, Copy_u8Pin);
				LCKR_voidWriteSeq(&(GPIOH->LCKR));
				break;	//PORT H
			default:
				Local_u8ErrorState = NOK;
				break;	//Error State NOT OK
			}
		}
		/* Check if the Pin is Locked */
		else if (Copy_u8LockStatus == PIN_UNLOCK) {
			/* THE BOARD NEEDS TO BE RESET TO UNLOCK PIN MODE */
//#warning " The Board Need To Be Reset To Unlock Pin Mode "
		} else {
			/* Error State NOT OK */
			Local_u8ErrorState = NOK;
		}
	}

	assert(Local_u8ErrorState != NOK);
}

/* Lock Port To Prevent Changing Configuration	Until Reset */

void MCAL_GPIO_voidSetPortLock(u8 Copy_u8Port, u16 Copy_u16LockStatus) {
	/* Error state OK */
	u8 Local_u8ErrorState = OK;

	switch (Copy_u8Port) {
	case GPIO_PORTA:
		GPIOA->LCKR = Copy_u16LockStatus;
		LCKR_voidWriteSeq(&(GPIOA->LCKR));
		break;	//PORT A
	case GPIO_PORTB:
		GPIOB->LCKR = Copy_u16LockStatus;
		LCKR_voidWriteSeq(&(GPIOB->LCKR));
		break;	//PORT B
	case GPIO_PORTC:
		GPIOC->LCKR = Copy_u16LockStatus;
		LCKR_voidWriteSeq(&(GPIOC->LCKR));
		break;	//PORT C
	case GPIO_PORTD:
		GPIOD->LCKR = Copy_u16LockStatus;
		LCKR_voidWriteSeq(&(GPIOD->LCKR));
		break;	//PORT D
	case GPIO_PORTH:
		GPIOH->LCKR = Copy_u16LockStatus;
		LCKR_voidWriteSeq(&(GPIOH->LCKR));
		break;	//PORT H
	default:
		Local_u8ErrorState = NOK;
		break;	//Error State NOT OK
	}
	/* Return Error State */
	assert(Local_u8ErrorState != NOK);
}

/* Set Writing Sequence to Lock Configurations of Pin */

static void LCKR_voidWriteSeq(volatile u32 *Copy_pu32LCKRegister) {
	/* Writing Sequence On Specific Port */
	SET_BIT(*Copy_pu32LCKRegister, 16);
	CLR_BIT(*Copy_pu32LCKRegister, 16);
	SET_BIT(*Copy_pu32LCKRegister, 16);

	/* Polling (BUSY WAITING) Until Bit 16 is High */
	while (!GET_BIT(*Copy_pu32LCKRegister, 16))
		;
}
