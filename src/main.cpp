#include <Arduino.h>
#include <DabbleESP32.h>
#include <Ps3Controller.h>

#include "My_Defines.h"
#include "My_Debug.h"

/******** TASK *****************/
TaskHandle_t hTaskBL;

uint16_t player = 0;
uint16_t battery = 0;

//?#############################################*/
//!------------------- FUNCIONS --------------------------*/
//?#############################################*/
void notify()
{
	//--- Digital cross/square/triangle/circle button events ---
	if (Ps3.event.button_down.cross)
	{
		/*[JSA]*/
		Serial2.println("~ST");
		Serial.println("Started pressing the cross button");
	}
	if (Ps3.event.button_up.cross)
		Serial.println("Released the cross button");

	if (Ps3.event.button_down.square)
		Serial.println("Started pressing the square button");
	if (Ps3.event.button_up.square)
		Serial.println("Released the square button");

	if (Ps3.event.button_down.triangle)
	{
		/*[JSA]*/
		Serial2.println("G0F1");
		Serial.println("Started pressing the triangle button");
	}
	if (Ps3.event.button_up.triangle)
		Serial.println("Released the triangle button");

	if (Ps3.event.button_down.circle)
		Serial.println("Started pressing the circle button");
	if (Ps3.event.button_up.circle)
		Serial.println("Released the circle button");

	//--------------- Digital D-pad button events --------------
	if (Ps3.event.button_down.up)
		Serial.println("Started pressing the up button");
	if (Ps3.event.button_up.up)
		Serial.println("Released the up button");

	if (Ps3.event.button_down.right)
		Serial.println("Started pressing the right button");
	if (Ps3.event.button_up.right)
		Serial.println("Released the right button");

	if (Ps3.event.button_down.down)
		Serial.println("Started pressing the down button");
	if (Ps3.event.button_up.down)
		Serial.println("Released the down button");

	if (Ps3.event.button_down.left)
		Serial.println("Started pressing the left button");
	if (Ps3.event.button_up.left)
		Serial.println("Released the left button");

	//------------- Digital shoulder button events -------------
	if (Ps3.event.button_down.l1)
		Serial.println("Started pressing the left shoulder button");
	if (Ps3.event.button_up.l1)
		Serial.println("Released the left shoulder button");

	if (Ps3.event.button_down.r1)
		Serial.println("Started pressing the right shoulder button");
	if (Ps3.event.button_up.r1)
		Serial.println("Released the right shoulder button");

	//-------------- Digital trigger button events -------------
	if (Ps3.event.button_down.l2)
		Serial.println("Started pressing the left trigger button");
	if (Ps3.event.button_up.l2)
		Serial.println("Released the left trigger button");

	if (Ps3.event.button_down.r2)
		Serial.println("Started pressing the right trigger button");
	if (Ps3.event.button_up.r2)
		Serial.println("Released the right trigger button");

	//--------------- Digital stick button events --------------
	if (Ps3.event.button_down.l3)
		Serial.println("Started pressing the left stick button");
	if (Ps3.event.button_up.l3)
		Serial.println("Released the left stick button");

	if (Ps3.event.button_down.r3)
		Serial.println("Started pressing the right stick button");
	if (Ps3.event.button_up.r3)
		Serial.println("Released the right stick button");

	//---------- Digital select/start/ps button events ---------
	if (Ps3.event.button_down.select)
		Serial.println("Started pressing the select button");
	if (Ps3.event.button_up.select)
		Serial.println("Released the select button");

	if (Ps3.event.button_down.start)
		Serial.println("Started pressing the start button");
	if (Ps3.event.button_up.start)
		Serial.println("Released the start button");

	if (Ps3.event.button_down.ps)
		Serial.println("Started pressing the Playstation button");
	if (Ps3.event.button_up.ps)
		Serial.println("Released the Playstation button");

	//---------------- Analog stick value events ---------------
	if (abs(Ps3.event.analog_changed.stick.lx) + abs(Ps3.event.analog_changed.stick.ly) > 2)
	{

		/*[JSA]*/
		/*Conversion*/
		/*int ConvDataP32 = ((Ps3.data.analog.stick.lx)+128)*7.84+500;

		int ConvDataP31 = ((Ps3.data.analog.stick.ly)-127)*(-5.38)+1126;*/

		int Resultant = sqrt(sq(Ps3.data.analog.stick.lx) + sq(Ps3.data.analog.stick.ly));
		double Rad31 = (atan2(Ps3.data.analog.stick.ly, Ps3.data.analog.stick.lx));

		int Degrees = int(Rad31 * 180 / PI);

		if ((Degrees >= 0 && Degrees < 180) && (Resultant < 177))
		{

			int ConvDataP32 = -Degrees * 11.11 + 2500;

			int ConvDataP31 = -Resultant * 7.19 + 2400;

			Serial2.print("#32P");
			Serial2.print(ConvDataP32, DEC);
			Serial2.print("#31P");
			Serial2.print(ConvDataP31, DEC);
			Serial2.print("T100D100");
			Serial2.println();

			/*Serial.print("Moved the left stick:");
			Serial.print(" x="); Serial.print(Ps3.data.analog.stick.lx, DEC);
			Serial.print(" y="); Serial.print(Ps3.data.analog.stick.ly, DEC);*/
			Serial.print(" ROBOT=");
			Serial.print(ConvDataP32, DEC);
			Serial.print(" ROBOT=");
			Serial.print(ConvDataP31, DEC);
			Serial.println();
		}
	}

	if (abs(Ps3.event.analog_changed.stick.rx) + abs(Ps3.event.analog_changed.stick.ry) > 2)
	{

		int ResultantR = sqrt(sq(Ps3.data.analog.stick.rx) + sq(Ps3.data.analog.stick.ry));
		double Rad1 = (atan2(Ps3.data.analog.stick.ry, Ps3.data.analog.stick.rx));

		int DegreesR = int(Rad1 * 180 / PI);

		if ((DegreesR >= 0 && DegreesR < 180) && (ResultantR < 177))
		{

			int ConvDataP1 = DegreesR * 11.11 + 500;

			int ConvDataP2 = ResultantR * 9.5 + 600;

			Serial2.print("#1P");
			Serial2.print(ConvDataP1, DEC);
			Serial2.print("#2P");
			Serial2.print(ConvDataP2, DEC);
			Serial2.print("T100D100");
			Serial2.println();

			Serial.print("Moved the right stick:");
			Serial.print(" x=");
			Serial.print(Ps3.data.analog.stick.rx, DEC);
			Serial.print(" y=");
			Serial.print(Ps3.data.analog.stick.ry, DEC);
			Serial.println();
		}
	}

	//--------------- Analog D-pad button events ----------------
	if (abs(Ps3.event.analog_changed.button.up))
	{
		Serial.print("Pressing the up button: ");
		Serial.println(Ps3.data.analog.button.up, DEC);
	}

	if (abs(Ps3.event.analog_changed.button.right))
	{
		Serial.print("Pressing the right button: ");
		Serial.println(Ps3.data.analog.button.right, DEC);
	}

	if (abs(Ps3.event.analog_changed.button.down))
	{
		Serial.print("Pressing the down button: ");
		Serial.println(Ps3.data.analog.button.down, DEC);
	}

	if (abs(Ps3.event.analog_changed.button.left))
	{
		Serial.print("Pressing the left button: ");
		Serial.println(Ps3.data.analog.button.left, DEC);
	}

	//---------- Analog shoulder/trigger button events ----------
	if (abs(Ps3.event.analog_changed.button.l1))
	{
		Serial.print("Pressing the left shoulder button: ");
		Serial.println(Ps3.data.analog.button.l1, DEC);
	}

	if (abs(Ps3.event.analog_changed.button.r1))
	{
		Serial.print("Pressing the right shoulder button: ");
		Serial.println(Ps3.data.analog.button.r1, DEC);
	}

	if (abs(Ps3.event.analog_changed.button.l2))
	{
		Serial.print("Pressing the left trigger button: ");
		Serial.println(Ps3.data.analog.button.l2, DEC);
	}

	if (abs(Ps3.event.analog_changed.button.r2))
	{
		Serial.print("Pressing the right trigger button: ");
		Serial.println(Ps3.data.analog.button.r2, DEC);
	}

	//---- Analog cross/square/triangle/circle button events ----
	if (abs(Ps3.event.analog_changed.button.triangle))
	{
		Serial.print("Pressing the triangle button: ");
		Serial.println(Ps3.data.analog.button.triangle, DEC);
	}

	if (abs(Ps3.event.analog_changed.button.circle))
	{
		Serial.print("Pressing the circle button: ");
		Serial.println(Ps3.data.analog.button.circle, DEC);
	}

	if (abs(Ps3.event.analog_changed.button.cross))
	{
		Serial.print("Pressing the cross button: ");
		Serial.println(Ps3.data.analog.button.cross, DEC);
	}

	if (abs(Ps3.event.analog_changed.button.square))
	{
		Serial.print("Pressing the square button: ");
		Serial.println(Ps3.data.analog.button.square, DEC);
	}

	//---------------------- Battery events ---------------------
	if (battery != Ps3.data.status.battery)
	{
		battery = Ps3.data.status.battery;
		Serial.print("The controller battery is ");
		if (battery == ps3_status_battery_charging)
			Serial.println("charging");
		else if (battery == ps3_status_battery_full)
			Serial.println("FULL");
		else if (battery == ps3_status_battery_high)
			Serial.println("HIGH");
		else if (battery == ps3_status_battery_low)
			Serial.println("LOW");
		else if (battery == ps3_status_battery_dying)
			Serial.println("DYING");
		else if (battery == ps3_status_battery_shutdown)
			Serial.println("SHUTDOWN");
		else
			Serial.println("UNDEFINED");
	}
}
//?#############################################*/
//!-------------------------------------------------------*/
//?#############################################*/
void onConnect()
{
	Serial.println("Connected.");
}
//?#############################################*/
//!-------------------------------------------------------*/
//?#############################################*/
void ps3()
{
	if (!Ps3.isConnected())
	{
		Serial.print("\nConnect the controller!");
		vTaskDelay(100);
		return;
	}

	//-------------------- Player LEDs -------------------
	Serial.print("Setting LEDs to player ");
	Serial.println(player, DEC);
	Ps3.setPlayer(player);

	player += 1;
	if (player > 10)
		player = 0;

	//------ Digital cross/square/triangle/circle buttons ------
	if (Ps3.data.button.cross && Ps3.data.button.down)
		Serial.println("Pressing both the down and cross buttons");
	if (Ps3.data.button.square && Ps3.data.button.left)
		Serial.println("Pressing both the square and left buttons");
	if (Ps3.data.button.triangle && Ps3.data.button.up)
		Serial.println("Pressing both the triangle and up buttons");
	if (Ps3.data.button.circle && Ps3.data.button.right)
		Serial.println("Pressing both the circle and right buttons");

	if (Ps3.data.button.l1 && Ps3.data.button.r1)
		Serial.println("Pressing both the left and right bumper buttons");
	if (Ps3.data.button.l2 && Ps3.data.button.r2)
		Serial.println("Pressing both the left and right trigger buttons");
	if (Ps3.data.button.l3 && Ps3.data.button.r3)
		Serial.println("Pressing both the left and right stick buttons");
	if (Ps3.data.button.select && Ps3.data.button.start)
		Serial.println("Pressing both the select and start buttons");

	delay(2000);
}
//?#############################################*/
//!-------------------------------------------------------*/
//?#############################################*/
void app()
{
	Dabble.processInput(); // this function is used to refresh data obtained from smartphone.Hence calling this function is mandatory in order to get data properly from your mobile.
	Serial.print("KeyPressed: ");
	if (GamePad.isUpPressed())
	{
		Serial.print("Up");
		// moveFrente(150);
	}
	else if (GamePad.isDownPressed())
	{
		Serial.print("Down");
		// moveTras(150);
	}

	else if (GamePad.isLeftPressed())
	{
		Serial.print("Left");
	}

	else if (GamePad.isRightPressed())
	{
		Serial.print("Right");
	}

	else if (GamePad.isSquarePressed())
	{
		Serial.print("Square");
	}

	else if (GamePad.isCirclePressed())
	{
		Serial.print("Circle");
	}

	else if (GamePad.isCrossPressed())
	{
		Serial.print("Cross");
	}

	else if (GamePad.isTrianglePressed())
	{
		Serial.print("Triangle");
	}

	else if (GamePad.isStartPressed())
	{
		Serial.print("Start");
	}

	else if (GamePad.isSelectPressed())
	{
		Serial.print("Select");
	}
	Serial.print('\t');

	int a = GamePad.getAngle();
	Serial.print("Angle: ");
	Serial.print(a);
	Serial.print('\t');
	int b = GamePad.getRadius();
	Serial.print("Radius: ");
	Serial.print(b);
	Serial.print('\t');
	float c = GamePad.getXaxisData();
	Serial.print("x_axis: ");
	Serial.print(c);
	Serial.print('\t');
	float d = GamePad.getYaxisData();
	Serial.print("y_axis: ");
	Serial.println(d);
	Serial.println();
}
//?#############################################*/
//!-------------------------------------------------------*/
//?#############################################*/
void TaskBL(void *pvParameters)
{
	for (;;)
	{
		//ps3();
		app();
	}
}
//?#############################################*/
//!-------------------------------------------------------*/
//?#############################################*/
void StartCommunication()
{
	Serial.begin(115200);
	Serial2.begin(9600);
}
//?#############################################*/
//!-------------------------------------------------------*/
//?#############################################*/
void StartPins()
{
}
//?#############################################*/
//!-------------------------------------------------------*/
//?#############################################*/
void StartSystem()
{
	Dabble.begin(DEVICE_NAME); // set bluetooth name of your device

    //Ps3.attach(notify);
    //Ps3.attachOnConnect(onConnect);
    //Ps3.begin("5c:6d:20:07:55:21");
	//Ps3.begin("78:18:81:0d:17:dd");

}
//?#############################################*/
//!-------------------------------------------------------*/
//?#############################################*/
void StartTasks()
{
	//--- Creating task for WIFI ---
	xTaskCreatePinnedToCore(
		TaskBL,					  // Task function.
		"TaskBL",				  // name of task.
		10000,					  // Stack size of task
		NULL,					  // parameter of the task
		1,						  // priority of the task
		&hTaskBL,				  // Task handle to keep track of created task
		PROCESSOR_COMMUNICATION); // pin task to core communication
	Serial.print("\n>>> Task Bluetooth...\tDONE");
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