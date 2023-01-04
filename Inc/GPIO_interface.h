/***************************************************************************************/
/***************************************************************************************/
/********************			Author	:	Nada Alaa			************************/
/********************			Layer	:	MCAL				************************/
/********************			SWC		:	GPIO			    ************************/
/********************			Version	:	1.00				************************/
/***************************************************************************************/
/***************************************************************************************/

#ifndef GPIO_INTERFACE_H_
#define GPIO_INTERFACE_H_

#include "STD_TYPES.h"

/* GPIO PORTS */
#define GPIO_PORTA					0
#define GPIO_PORTB					1
#define GPIO_PORTC					2
#define GPIO_PORTD					3
#define GPIO_PORTH					4

/* GPIO PINS */
#define GPIO_PIN0					0
#define GPIO_PIN1					1
#define GPIO_PIN2					2
#define GPIO_PIN3					3
#define GPIO_PIN4					4
#define GPIO_PIN5					5
#define GPIO_PIN6					6
#define GPIO_PIN7					7
#define GPIO_PIN8					8
#define GPIO_PIN9					9
#define GPIO_PIN10					10
#define GPIO_PIN11					11
#define GPIO_PIN12					12
#define GPIO_PIN13					13
#define GPIO_PIN14					14
#define GPIO_PIN15					15

/* Alternate Functions */
#define AF0						 0
#define AF1						 1
#define AF2						 2
#define AF3						 3
#define AF4						 4
#define AF5						 5
#define AF6						 6
#define AF7				         7
#define AF8					     8
#define AF9					     9
#define AF10					10
#define AF11					11
#define AF12					12
#define AF13					13
#define AF14					14
#define AF15					15

#define NUM_OF_PORTS               	5
#define NUM_OF_PINS_PER_PORT_ABC    16
#define NUM_OF_PINS_PER_PORTD       1
#define NUM_OF_PINS_PER_PORTH  		2

/********************************************************************************************/
/*									SELECT PIN MODE :										*/
/*																							*/
/*		Options:					0-INPUT_MODE			=>(Initial State)				*/
/*									1-OUTPUT_MODE											*/
/*									2-AF_MODE												*/
/*									3-ANALOG_MODE											*/
/*																							*/
/********************************************************************************************/
typedef enum {
	INPUT_MODE, OUTPUT_MODE, AF_MODE, ANALOG_MODE
} Pin_Mode;

/********************************************************************************************/
/*								SELECT PIN OUTPUT TYPE :									*/
/*																							*/
/*		Options	:					0-OUTPUT_PUSH_PULL			=>(Initial State)			*/
/*									1-OUTPUT_OPEN_DRAIN										*/
/*																							*/
/*		Caution	:	The Output Type is Selected Only For Output Pins						*/
/*																							*/
/********************************************************************************************/

typedef enum {
	OUTPUT_PUSH_PULL = 0, OUTPUT_OPEN_DRAIN = 1, OUTPUT_DEFAULT = 0
} Pin_Output_Type;

/********************************************************************************************/
/*								SELECT PIN OUTPUT SPEED :									*/
/*																							*/
/*		Options:					0-OUTPUT_LOW_SPEED										*/
/*									1-OUTPUT_MEDIUM_SPEED									*/
/*									2-OUTPUT_FAST_SPEED										*/
/*									3-OUTPUT_HIGH_SPEED										*/
/*																							*/
/*		Caution	:	The Output Speed is Selected Only For Output Pins						*/
/*																							*/
/********************************************************************************************/
typedef enum {
	LOW_SPEED = 0,
	MEDIUM_SPEED = 1,
	FAST_SPEED = 2,
	HIGH_SPEED = 3,
	DEFAULT_SPEED = 0
} Output_Speed;

/********************************************************************************************/
/*						SELECT PIN PULL UP/ PULL DOWN CONFIGURATION :						*/
/*																							*/
/*		Options:					0-NO_PULL_UP_PULL_DOWN			=>(Output Pins)			*/
/*									1-PULL_UP						=>(Input Pins)			*/
/*									2-PULL_DOWN						=>(Input Pins)			*/
/*																							*/
/********************************************************************************************/
typedef enum {
	NO_PULL_UP_DOWN = 0, PULL_UP = 1, PULL_DOWN = 2, DEFAULT_PULL = 0
} Pull_Up_Down;

/********************************************************************************************/
/*								SELECT PIN OUTPUT VALUE :									*/
/*																							*/
/*		Options	:					0-OUTPUT_LOW				=>(Initial State)			*/
/*									1-OUTPUT_HIGH											*/
/*																							*/
/*		Caution	:	The Initial Value is Selected Only For Output Pins						*/
/*																							*/
/********************************************************************************************/
typedef enum {
	OUTPUT_LOW, OUTPUT_HIGH
} Pin_Output_Value;

/********************************************************************************************/
/*								SELECT Pin Value Status :									*/
/*																							*/
/*		Options	:					0-PIN_LOW				=>(Initial State)				*/
/*									1-PIN_HIGH												*/
/*																							*/
/*																							*/
/********************************************************************************************/
typedef enum {
	PIN_LOW, PIN_HIGH
} GPIO_PinValueStatus;

/********************************************************************************************/
/*								SELECT Port Value Status :									*/
/*																							*/
/*		Options	:					0-PORT_LOW				=>(Initial State)				*/
/*									1-PORT_HIGH												*/
/*																							*/
/*																							*/
/********************************************************************************************/
typedef enum {
	PORT_LOW, PORT_HIGH = 0xFFFF
} GPIO_PortValueStatus;

/********************************************************************************************/
/*								SELECT Pin Lock Status :									*/
/*																							*/
/*		Options	:					0-PIN_LOCK					=>(Initial State)			*/
/*									1-PIN_UNLOCK											*/
/*																							*/
/*																							*/
/********************************************************************************************/
typedef enum {
	PIN_UNLOCK, PIN_LOCK
} GPIO_PinLockStatus;

/********************************************************************************************/
/*								SELECT Port Lock Status :									*/
/*																							*/
/*		Options	:					0-PORT_LOCK					=>(Initial State)			*/
/*									1-PORT_UNLOCK											*/
/*																							*/
/*																							*/
/********************************************************************************************/
typedef enum {
	PORT_UNLOCK, PORT_LOCK = 0xFFFF
} GPIO_PortLockStatus;



/* GPIO configuration structure */
typedef struct {
	u8 portID;
	u8 pinID;
	Pin_Mode PinMode;
	Pin_Output_Type outputType;
	Output_Speed speed;
	Pull_Up_Down PullUpDown;
} GPIO_ConfigType;



/********************************************************************************************/
/*					Fun Def	:	Initialize All Ports Value & Mode Configuration 			*/
/*																							*/
/*					Inputs	:	Void														*/
/*																							*/
/*					Outputs	:	Void														*/
/*																							*/
/********************************************************************************************/
void MCAL_GPIO_voidInit(GPIO_ConfigType *configPtr);

/********************************************************************************************/
/*				Fun Def	:	Set Pin Value of a Port To Be High or Low						*/
/*																							*/
/*				Inputs	:	Copy_u8Port	: GPIO_PORTA | GPIO_PORTB | GPIO_PORTC				*/
/*							Copy_u8Pin	: GPIO_PIN0 -> GPIO_PIN15							*/
/*							Copy_u8Value: GPIO_PIN_HIGH | GPIO_PIN_LOW						*/
/*																							*/
/*				Outputs	:	void									                        */
/*																							*/
/********************************************************************************************/
void MCAL_GPIO_voidSetPinValue(u8 Copy_u8Port, u8 Copy_u8Pin, u8 Copy_u8Value);

/********************************************************************************************/
/*				Fun Def	:	Set Pin alternate function of the pin     						*/
/*																							*/
/*				Inputs	:	Copy_u8Port	: GPIO_PORTA | GPIO_PORTB | GPIO_PORTC				*/
/*							Copy_u8Pin	: GPIO_PIN0 -> GPIO_PIN15							*/
/*							u8 AF_NUM   : AF0 to AF15                    						*/
/*																							*/
/*				Outputs	:	void									                        */
/*																							*/
/********************************************************************************************/
void MCAL_GPIO_voidSetPinAlternateFunction(u8 Copy_u8Port, u8 Copy_u8Pin,
		u8 AF_NUM);

/********************************************************************************************/
/*			Fun Def	:	Set Port Value To Be High or Low									*/
/*																							*/
/*			Inputs	:	Copy_u8Port		: GPIO_PORTA | GPIO_PORTB | GPIO_PORTC				*/
/*						Copy_u16Value	: GPIO_PORT_HIGH | GPIO_PORT_LOW | Any 16 Bit Value	*/
/*																							*/
/*			Outputs	:	void									                            */
/*																							*/
/********************************************************************************************/
void MCAL_GPIO_voidSetPortValue(u8 Copy_u8Port, u16 Copy_u16Value);

/********************************************************************************************/
/*				Fun Def	:	Get The Value of a Pin of specific Port							*/
/*																							*/
/*				Inputs	:	Copy_u8Port		: GPIO_PORTA | GPIO_PORTB | GPIO_PORTC			*/
/*							Copy_u8Pin		: GPIO_PIN0 -> GPIO_PIN15						*/
/*							Copy_pu8Value	: Pass A Variable of Type u8					*/
/*																							*/
/*				Outputs	:	pin value             									*/
/*																							*/
/********************************************************************************************/
u8 MCAL_GPIO_u8GetPinValue(u8 Copy_u8Port, u8 Copy_u8Pin);

/********************************************************************************************/
/*			Fun Def	:	Lock Pin of a Port To Prevent Changing Configuration Until Reset	*/
/*																							*/
/*			Inputs	:	Copy_u8Port		: GPIO_PORTA | GPIO_PORTB | GPIO_PORTC				*/
/*						Copy_u8Pin		: GPIO_PIN0 -> GPIO_PIN15							*/
/*						Copy_u8Value	: GPIO_PIN_LOCK | GPIO_PIN_UNLOCK					*/
/*																							*/
/*			Outputs	:	void                         										*/
/*																							*/
/********************************************************************************************/
void MCAL_GPIO_voidSetPinLock(u8 Copy_u8Port, u8 Copy_u8Pin, u8 Copy_u8Value);

/********************************************************************************************/
/*		Fun Def	:	Lock Port To Prevent Changing Configuration	Until Reset					*/
/*																							*/
/*		Inputs	:	Copy_u8Port		: GPIO_PORTA | GPIO_PORTB | GPIO_PORTC					*/
/*					Copy_u16Value	: GPIO_PORT_LOCK | GPIO_PORT_UNLOCK | Any 16 Bit Value	*/
/*																							*/
/*		Outputs	:	void                        											*/
/*																							*/
/********************************************************************************************/
void MCAL_GPIO_voidSetPortLock(u8 Copy_u8Port, u16 Copy_u16Value);

#endif /* GPIO_INTERFACE_H_ */
