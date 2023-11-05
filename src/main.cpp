#include <Arduino.h>
#include <ps5Controller.h>

#include "My_Defines.h"
#include "My_Debug.h"

//******* VARIABLES *************

//?CONTROLLER
uint16_t player = 0;
uint8_t battery_controller = 0;
uint8_t status_analog = 0;
uint8_t status_analogR = 0;
uint8_t status_carangueijo = 0;
uint8_t status_seta = 0;

//?TIMERs
unsigned long time_bl = 0;

//******* TASK *****************
TaskHandle_t hTaskBL;

//?#############################################*/
//!------------------- FUNCIONS --------------------------*/
//?#############################################*/
void LedRed()
{
	digitalWrite(LED_RED, HIGH);
	digitalWrite(LED_GREEN, LOW);
	digitalWrite(LED_BLUE, LOW);
}
//?#############################################*/
//!-------------------------------------------------------*/
//?#############################################*/
void LedGreen()
{
	digitalWrite(LED_RED, LOW);
	digitalWrite(LED_GREEN, HIGH);
	digitalWrite(LED_BLUE, LOW);
}
//?#############################################*/
//!-------------------------------------------------------*/
//?#############################################*/
void LedBlue()
{
	digitalWrite(LED_RED, LOW);
	digitalWrite(LED_GREEN, LOW);
	digitalWrite(LED_BLUE, HIGH);
}
//?#############################################*/
//!-------------------------------------------------------*/
//?#############################################*/
void LedWhite()
{
	digitalWrite(LED_RED, HIGH);
	digitalWrite(LED_GREEN, HIGH);
	digitalWrite(LED_BLUE, HIGH);
}
//?#############################################*/
//!-------------------------------------------------------*/
//?#############################################*/
void LedOff()
{
	digitalWrite(LED_RED, LOW);
	digitalWrite(LED_GREEN, LOW);
	digitalWrite(LED_BLUE, LOW);
}
//?#############################################*/
//!-------------------------------------------------------*/
//?#############################################*/
void PS5_Controller()
{
	if (ps5.isConnected() == true)
	{
		LedBlue();

		if (ps5.Down() && !status_analog && !status_carangueijo && !status_analogR)
		{
			status_seta = 1;
			// Serial.println("Down Button");

			digitalWrite(MOTOR1_PIN1, LOW);
			digitalWrite(MOTOR1_PIN2, HIGH);

			digitalWrite(MOTOR1_PIN3, LOW);
			digitalWrite(MOTOR1_PIN4, HIGH);

			digitalWrite(MOTOR2_PIN1, LOW);
			digitalWrite(MOTOR2_PIN2, HIGH);

			digitalWrite(MOTOR2_PIN3, LOW);
			digitalWrite(MOTOR2_PIN4, HIGH);
		}

		else if (ps5.Up() && !status_analog && !status_carangueijo && !status_analogR)
		{
			status_seta = 1;
			// Serial.println("Up Button");

			digitalWrite(MOTOR1_PIN1, HIGH);
			digitalWrite(MOTOR1_PIN2, LOW);

			digitalWrite(MOTOR2_PIN1, HIGH);
			digitalWrite(MOTOR2_PIN2, LOW);

			//***************************************
			digitalWrite(MOTOR1_PIN3, HIGH);
			digitalWrite(MOTOR1_PIN4, LOW);

			digitalWrite(MOTOR2_PIN3, HIGH);
			digitalWrite(MOTOR2_PIN4, LOW);
		}

		else if (ps5.Left() && !status_analog && !status_carangueijo && !status_analogR)
		{
			status_seta = 1;
			// Serial.println("Left Button");

			digitalWrite(MOTOR1_PIN1, LOW);
			digitalWrite(MOTOR1_PIN2, HIGH);

			digitalWrite(MOTOR2_PIN1, HIGH);
			digitalWrite(MOTOR2_PIN2, LOW);

			//***************************************

			digitalWrite(MOTOR1_PIN3, HIGH);
			digitalWrite(MOTOR1_PIN4, LOW);

			digitalWrite(MOTOR2_PIN3, LOW);
			digitalWrite(MOTOR2_PIN4, HIGH);
		}

		else if (ps5.Right() && !status_analog && !status_carangueijo && !status_analogR)
		{
			status_seta = 1;
			// Serial.println("Right Button");

			digitalWrite(MOTOR1_PIN1, HIGH);
			digitalWrite(MOTOR1_PIN2, LOW);

			digitalWrite(MOTOR2_PIN1, LOW);
			digitalWrite(MOTOR2_PIN2, HIGH);

			//***************************************
			digitalWrite(MOTOR1_PIN3, LOW);
			digitalWrite(MOTOR1_PIN4, HIGH);

			digitalWrite(MOTOR2_PIN3, HIGH);
			digitalWrite(MOTOR2_PIN4, LOW);
		}

		else
		{
			status_seta = 0;
		}

		if (ps5.Square() && !status_analog && !status_seta && !status_analogR)
		{
			status_carangueijo = 1;
			// Serial.println("Square Button");

			digitalWrite(MOTOR1_PIN1, LOW);
			digitalWrite(MOTOR1_PIN2, HIGH);

			digitalWrite(MOTOR2_PIN1, LOW);
			digitalWrite(MOTOR2_PIN2, HIGH);

			digitalWrite(MOTOR1_PIN3, HIGH);
			digitalWrite(MOTOR1_PIN4, LOW);

			digitalWrite(MOTOR2_PIN3, HIGH);
			digitalWrite(MOTOR2_PIN4, LOW);
		}

		else if (ps5.Circle() && !status_analog && !status_seta && !status_analogR)
		{
			status_carangueijo = 1;
			// Serial.println("Circle Button");
			digitalWrite(MOTOR1_PIN1, HIGH);
			digitalWrite(MOTOR1_PIN2, LOW);

			digitalWrite(MOTOR2_PIN1, HIGH);
			digitalWrite(MOTOR2_PIN2, LOW);

			digitalWrite(MOTOR1_PIN3, LOW);
			digitalWrite(MOTOR1_PIN4, HIGH);

			digitalWrite(MOTOR2_PIN3, LOW);
			digitalWrite(MOTOR2_PIN4, HIGH);
		}

		else
		{
			status_carangueijo = 0;
		}

		if (ps5.LStickX() >= -120 && ps5.LStickY() >= 100 && !status_carangueijo && !status_seta && !status_analogR)
		{
			status_analog = 1;
			//Serial.println("Up Analog");
			digitalWrite(MOTOR1_PIN1, HIGH);
			digitalWrite(MOTOR1_PIN2, LOW);

			digitalWrite(MOTOR2_PIN1, HIGH);
			digitalWrite(MOTOR2_PIN2, LOW);

			//***************************************
			digitalWrite(MOTOR1_PIN3, HIGH);
			digitalWrite(MOTOR1_PIN4, LOW);

			digitalWrite(MOTOR2_PIN3, HIGH);
			digitalWrite(MOTOR2_PIN4, LOW);
		}

		else if (ps5.LStickX() >= -100 && ps5.LStickY() <= -110 && !status_carangueijo && !status_seta && !status_analogR)
		{
			status_analog = 1;
			//Serial.println("Down Analog");

			digitalWrite(MOTOR1_PIN1, LOW);
			digitalWrite(MOTOR1_PIN2, HIGH);

			digitalWrite(MOTOR1_PIN3, LOW);
			digitalWrite(MOTOR1_PIN4, HIGH);
			//***************************************
			digitalWrite(MOTOR2_PIN1, LOW);
			digitalWrite(MOTOR2_PIN2, HIGH);

			digitalWrite(MOTOR2_PIN3, LOW);
			digitalWrite(MOTOR2_PIN4, HIGH);
		}

		else if (ps5.LStickX() <= -120 && ps5.LStickY() <= 100 && !status_carangueijo && !status_seta && !status_analogR)
		{
			status_analog = 1;
			//Serial.println("Left Analog");

			digitalWrite(MOTOR1_PIN1, LOW);
			digitalWrite(MOTOR1_PIN2, HIGH);

			digitalWrite(MOTOR2_PIN1, HIGH);
			digitalWrite(MOTOR2_PIN2, LOW);

			//***************************************

			digitalWrite(MOTOR1_PIN3, HIGH);
			digitalWrite(MOTOR1_PIN4, LOW);

			digitalWrite(MOTOR2_PIN3, LOW);
			digitalWrite(MOTOR2_PIN4, HIGH);
		}

		else if (ps5.LStickX() >= 112 && ps5.LStickY() >= -122 && !status_carangueijo && !status_seta && !status_analogR)
		{
			status_analog = 1;
			//Serial.println("Right Analog");

			digitalWrite(MOTOR1_PIN1, HIGH);
			digitalWrite(MOTOR1_PIN2, LOW);

			digitalWrite(MOTOR2_PIN1, LOW);
			digitalWrite(MOTOR2_PIN2, HIGH);

			//***************************************
			digitalWrite(MOTOR1_PIN3, LOW);
			digitalWrite(MOTOR1_PIN4, HIGH);

			digitalWrite(MOTOR2_PIN3, HIGH);
			digitalWrite(MOTOR2_PIN4, LOW);
		}

		else
		{
			status_analog = 0;
		}

		if (ps5.RStickX() <= -120 && ps5.RStickY() <= 100 && !status_carangueijo && !status_seta && !status_analog)
		{
			status_analogR= 1;
			//Serial.println("Left Analog");

			digitalWrite(MOTOR1_PIN1, LOW);
			digitalWrite(MOTOR1_PIN2, HIGH);

			digitalWrite(MOTOR2_PIN1, HIGH);
			digitalWrite(MOTOR2_PIN2, LOW);

			//***************************************

			digitalWrite(MOTOR1_PIN3, HIGH);
			digitalWrite(MOTOR1_PIN4, LOW);

			digitalWrite(MOTOR2_PIN3, LOW);
			digitalWrite(MOTOR2_PIN4, HIGH);
		}

		else if (ps5.RStickX() >= 112 && ps5.RStickY() >= -122 && !status_carangueijo && !status_seta && !status_analog)
		{
			status_analogR = 1;
			//Serial.println("Right Analog");

			digitalWrite(MOTOR1_PIN1, HIGH);
			digitalWrite(MOTOR1_PIN2, LOW);

			digitalWrite(MOTOR2_PIN1, LOW);
			digitalWrite(MOTOR2_PIN2, HIGH);

			//***************************************
			digitalWrite(MOTOR1_PIN3, LOW);
			digitalWrite(MOTOR1_PIN4, HIGH);

			digitalWrite(MOTOR2_PIN3, HIGH);
			digitalWrite(MOTOR2_PIN4, LOW);
		}

		else
		{
			status_analogR = 0;
		}

		/*if (ps5.LStickX())
		{
			//Serial.printf("Left Stick x at %d\n", ps5.LStickX());

		}
		if (ps5.LStickY())
		{
			//Serial.printf("Left Stick y at %d\n", ps5.LStickY());
		}
		if (ps5.RStickX())
		{
			//Serial.printf("Right Stick x at %d\n", ps5.RStickX());
		}
		if (ps5.RStickY())
		{
			//Serial.printf("Right Stick y at %d\n", ps5.RStickY());
		}*/

		if (!ps5.Up() && !ps5.Down() && !ps5.Right() && !ps5.Left() && !ps5.Square() && !ps5.Circle() && !status_analog && !status_analogR)
		{
			digitalWrite(MOTOR1_PIN1, LOW);
			digitalWrite(MOTOR1_PIN2, LOW);

			digitalWrite(MOTOR1_PIN3, LOW);
			digitalWrite(MOTOR1_PIN4, LOW);

			digitalWrite(MOTOR2_PIN1, LOW);
			digitalWrite(MOTOR2_PIN2, LOW);

			digitalWrite(MOTOR2_PIN3, LOW);
			digitalWrite(MOTOR2_PIN4, LOW);
		}

		battery_controller = ps5.Battery();
		//vTaskDelay(1);
	}

	else
	{
		if ((millis() - time_bl) > TIMER_BL)
		{
			time_bl = millis();
			Serial.println("The controller is not conected!");
		}

		LedRed();
		digitalWrite(MOTOR1_PIN1, LOW);
		digitalWrite(MOTOR1_PIN2, LOW);

		digitalWrite(MOTOR1_PIN3, LOW);
		digitalWrite(MOTOR1_PIN4, LOW);

		digitalWrite(MOTOR2_PIN1, LOW);
		digitalWrite(MOTOR2_PIN2, LOW);

		digitalWrite(MOTOR2_PIN3, LOW);
		digitalWrite(MOTOR2_PIN4, LOW);

		// vTaskDelay(5000);
	}
}
//?#############################################*/
//!-------------------------------------------------------*/
//?#############################################*/
void PS5_Controller(void *pvParameters)
{
	for (;;)
	{
		PS5_Controller();
	}
}
//?#############################################*/
//!-------------------------------------------------------*/
//?#############################################*/
void StartCommunication()
{
	Serial.begin(115200);

	ps5.begin("4c:b9:9b:60:58:9d"); // replace with MAC address of your controller
}
//?#############################################*/
//!-------------------------------------------------------*/
//?#############################################*/
void StartPins()
{
	pinMode(MOTOR1_PIN1, OUTPUT);
	pinMode(MOTOR1_PIN2, OUTPUT);
	digitalWrite(MOTOR1_PIN1, LOW);
	digitalWrite(MOTOR1_PIN2, LOW);

	pinMode(MOTOR1_PIN3, OUTPUT);
	pinMode(MOTOR1_PIN4, OUTPUT);
	digitalWrite(MOTOR1_PIN3, LOW);
	digitalWrite(MOTOR1_PIN4, LOW);

	pinMode(MOTOR2_PIN1, OUTPUT);
	pinMode(MOTOR2_PIN2, OUTPUT);
	digitalWrite(MOTOR2_PIN1, LOW);
	digitalWrite(MOTOR2_PIN2, LOW);

	pinMode(MOTOR2_PIN3, OUTPUT);
	pinMode(MOTOR2_PIN4, OUTPUT);
	digitalWrite(MOTOR2_PIN3, LOW);
	digitalWrite(MOTOR2_PIN4, LOW);

	pinMode(LED_RED, OUTPUT);
	pinMode(LED_GREEN, OUTPUT);
	pinMode(LED_BLUE, OUTPUT);

	digitalWrite(LED_RED, LOW);
	digitalWrite(LED_GREEN, LOW);
	digitalWrite(LED_BLUE, LOW);
}
//?#############################################*/
//!-------------------------------------------------------*/
//?#############################################*/
void StartSystem()
{
	delay(1000);
}
//?#############################################*/
//!-------------------------------------------------------*/
//?#############################################*/
void StartTasks()
{
	//--- Creating task for WIFI ---
	xTaskCreatePinnedToCore(
		PS5_Controller,			  // Task function.
		"TaskBL",				  // name of task.
		10000,					  // Stack size of task
		NULL,					  // parameter of the task
		1,						  // priority of the task
		&hTaskBL,				  // Task handle to keep track of created task
		PROCESSOR_COMMUNICATION); // pin task to core communication
	Serial.print("\n>>> Task PS5_Controller...\tDONE");

	//--- Creating task for WIFI ---
	/*xTaskCreatePinnedToCore(
		LEDStatus,		 // Task function.
		"TaskLED",		 // name of task.
		5000,			 // Stack size of task
		NULL,			 // parameter of the task
		2,				 // priority of the task
		&hTaskLEDStatus, // Task handle to keep track of created task
		PROCESSOR_MAIN); // pin task to core communication
	Serial.print("\n>>> Task LEDStatus...\tDONE");*/
}
//?#############################################*/
//!-------------------------------------------------------*/
//?#############################################*/
void setup()
{
	StartCommunication();
	StartPins();
	StartSystem();
	StartTasks();

	Serial.print("\n\nSystem Started! : \nDEVICE: ");
	Serial.print(DEVICE_NAME);
	Serial.print("_");
	Serial.print(DEVICE_ID);
}
//!-------------------------------------------------------*/
void loop()
{
	// vTaskDelay(1);
}