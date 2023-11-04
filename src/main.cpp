#include <Arduino.h>
#include <ps5Controller.h>

#include "My_Defines.h"
#include "My_Debug.h"

//******* VARIABLES *************

//?CONTROLLER
uint16_t player = 0;
uint8_t battery_controller = 0;

//******* TASK *****************
TaskHandle_t hTaskBL;
TaskHandle_t hTaskLEDStatus;

class DCMotor
{
	int spd = 255, pin1, pin2;

public:
	void Pinout(int in1, int in2)
	{ // Pinout é o método para a declaração dos pinos que vão controlar o objeto motor
		pin1 = in1;
		pin2 = in2;
		pinMode(pin1, OUTPUT);
		pinMode(pin2, OUTPUT);
	}
	void Speed(int in1)
	{ // Speed é o método que irá ser responsável por salvar a velocidade de atuação do motor
		spd = in1;
	}
	void Forward()
	{ // Forward é o método para fazer o motor girar para frente
		analogWrite(pin1, spd);
		digitalWrite(pin2, LOW);
	}
	void Backward()
	{ // Backward é o método para fazer o motor girar para trás
		digitalWrite(pin1, LOW);
		analogWrite(pin2, spd);
	}
	void Stop()
	{ // Stop é o metodo para fazer o motor ficar parado.
		digitalWrite(pin1, LOW);
		digitalWrite(pin2, LOW);
	}
};
DCMotor Motor1, Motor2; // Criação de dois objetos motores, já que usaremos dois motores, e eles já estão prontos para receber os comandos já configurados acima.

//?#############################################*/
//!------------------- FUNCIONS --------------------------*/
//?#############################################*/
void PS5_Controller()
{
	if (ps5.isConnected() == true)
	{
		if (ps5.Down())
		{
			Serial.println("Down Button");

			digitalWrite(MOTOR1_PIN1, LOW);
			digitalWrite(MOTOR1_PIN2, HIGH);

			digitalWrite(MOTOR1_PIN3, LOW);
			digitalWrite(MOTOR1_PIN4, HIGH);

			digitalWrite(MOTOR2_PIN1, LOW);
			digitalWrite(MOTOR2_PIN2, HIGH);

			digitalWrite(MOTOR2_PIN3, LOW);
			digitalWrite(MOTOR2_PIN4, HIGH);
		}

		if (ps5.Up())
		{
			Serial.println("Up Button");

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

		if (ps5.Left())
		{
			Serial.println("Left Button");

			digitalWrite(MOTOR1_PIN1, LOW);
			digitalWrite(MOTOR1_PIN2, HIGH);

			digitalWrite(MOTOR2_PIN1, LOW);
			digitalWrite(MOTOR2_PIN2, HIGH);

			digitalWrite(MOTOR1_PIN3, HIGH);
			digitalWrite(MOTOR1_PIN4, LOW);

			digitalWrite(MOTOR2_PIN3, HIGH);
			digitalWrite(MOTOR2_PIN4, LOW);
		}

		if (ps5.Right())
		{
			Serial.println("Right Button");

			digitalWrite(MOTOR1_PIN1, HIGH);
			digitalWrite(MOTOR1_PIN2, LOW);

			digitalWrite(MOTOR2_PIN1, HIGH);
			digitalWrite(MOTOR2_PIN2, LOW);

			digitalWrite(MOTOR1_PIN3, LOW);
			digitalWrite(MOTOR1_PIN4, HIGH);

			digitalWrite(MOTOR2_PIN3, LOW);
			digitalWrite(MOTOR2_PIN4, HIGH);
		}

		if (ps5.Square())
		{
			Serial.println("Square Button");

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

		if (ps5.Circle())
		{
			Serial.println("Circle Button");
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

		/*
		if (ps5.Cross())
					Serial.println("Cross Button");
		if (ps5.Triangle())
					Serial.println("Triangle Button");
				if (ps5.UpRight())
					Serial.println("Up Right");
				if (ps5.DownRight())
					Serial.println("Down Right");
				if (ps5.UpLeft())
					Serial.println("Up Left");
				if (ps5.DownLeft())
					Serial.println("Down Left");

				if (ps5.L1())
					Serial.println("L1 Button");
				if (ps5.R1())
					Serial.println("R1 Button");

				if (ps5.Share())
					Serial.println("Share Button");
				if (ps5.Options())
					Serial.println("Options Button");
				if (ps5.L3())
					Serial.println("L3 Button");
				if (ps5.R3())
					Serial.println("R3 Button");

				if (ps5.PSButton())
					Serial.println("PS Button");
				if (ps5.Touchpad())
					Serial.println("Touch Pad Button");

				if (ps5.L2())
				{
					Serial.printf("L2 button at %d\n", ps5.L2Value());
				}
				if (ps5.R2())
				{
					Serial.printf("R2 button at %d\n", ps5.R2Value());
				}

				if (ps5.LStickX())
				{
					// Serial.printf("Left Stick x at %d\n", ps5.LStickX());
				}
				if (ps5.LStickY())
				{
					// Serial.printf("Left Stick y at %d\n", ps5.LStickY());
				}
				if (ps5.RStickX())
				{
					// Serial.printf("Right Stick x at %d\n", ps5.RStickX());
				}
				if (ps5.RStickY())
				{
					// Serial.printf("Right Stick y at %d\n", ps5.RStickY());
				}*/

		if (!ps5.Up() && !ps5.Down() && !ps5.Right() && !ps5.Left() && !ps5.Square() && !ps5.Circle())
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
		vTaskDelay(1);
	}

	else
	{
		Serial.println("The controller is not conected!");
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
void LEDStatus(void *pvParameters)
{
	for (;;)
	{
		Serial.print("\nController Battery: ");
		Serial.println(battery_controller);

		if (battery_controller >= 60)
		{
			ps5.setLed(0, 255, 0);
		}

		else if (battery_controller > 25 && battery_controller < 60)
		{
			ps5.setLed(255, 165, 0);
		}

		else if (battery_controller <= 25)
		{
			ps5.setLed(255, 0, 0);
		}

		vTaskDelay(1000);
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

	pinMode(MOTOR1_PIN3, OUTPUT);
	pinMode(MOTOR1_PIN4, OUTPUT);

	pinMode(MOTOR2_PIN1, OUTPUT);
	pinMode(MOTOR2_PIN2, OUTPUT);

	pinMode(MOTOR2_PIN3, OUTPUT);
	pinMode(MOTOR2_PIN4, OUTPUT);

	digitalWrite(MOTOR1_PIN1, LOW);
	digitalWrite(MOTOR1_PIN2, LOW);

	digitalWrite(MOTOR1_PIN3, LOW);
	digitalWrite(MOTOR1_PIN4, LOW);

	digitalWrite(MOTOR2_PIN1, LOW);
	digitalWrite(MOTOR2_PIN2, LOW);

	digitalWrite(MOTOR2_PIN3, LOW);
	digitalWrite(MOTOR2_PIN4, LOW);
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
	xTaskCreatePinnedToCore(
		LEDStatus,		 // Task function.
		"TaskLED",		 // name of task.
		5000,			 // Stack size of task
		NULL,			 // parameter of the task
		2,				 // priority of the task
		&hTaskLEDStatus, // Task handle to keep track of created task
		PROCESSOR_MAIN); // pin task to core communication
	Serial.print("\n>>> Task LEDStatus...\tDONE");
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