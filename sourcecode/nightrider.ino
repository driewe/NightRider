/*
Using three 74HC595s to control 24 leds (outputs) on the arduino uno. 

This is an improved version by John Rogers

*/

int latchPin = 5;   // to pin 12
int clockPin = 6;	// to pin 11
int dataPin = 4;	// to pin 14

int numLights=24;
unsigned long light = 0;  // Bit pattern for entire display
byte b1 = 0;				// byte place holders for each shift register
byte b2 = 0;				// extracted from "light"
byte b3 = 0;

	

void setup() 
{
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);  
  pinMode(clockPin, OUTPUT);
 // Serial.begin(9600);
}

void loop() 
{
	for (int i = 0; i < numLights*2; i++)
	{
		int shift = i;
		if( i >= numLights )	//if i is above numlights then wee need to start
		{						// moving back to the left.
			shift = numLights*2 - i - 1;
		}
		// Extract the bytes of the light patter to be sent out
		light = (long)(1)<<shift;
		b1 = (byte)((light>>16)&0xFF);
		b2 = (byte)((light>>8)&0xFF);
		b3 = (byte)((light)&0xFF);
		updateShiftRegister();	// shift out b1, b2 and b3
		delay(30);
	}
}

void updateShiftRegister()
{
   	digitalWrite(latchPin, LOW);
   	shiftOut(dataPin, clockPin, MSBFIRST, b1);
   	shiftOut(dataPin, clockPin, MSBFIRST, b2);
   	shiftOut(dataPin, clockPin, MSBFIRST, b3);
   	digitalWrite(latchPin, HIGH);
   	
   	// For debugging
   		/*Serial.print(i);
			Serial.print(" ");
			Serial.print(light);
			Serial.print(" ");
			Serial.print(b1);
			Serial.print(" ");
			Serial.print(b2);
			Serial.print(" ");
			Serial.println(b3);*/
}