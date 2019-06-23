#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Display Adress: 3F
LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

int Htime;              //integer for storing high time
int Ltime;              //integer for storing low time
float Ttime;            // integer for storing total time of a cycle
float frequency;        //storing frequency

float triggerfrequency = 100; //storing the frequency

int LED =   13;


void setup()
{
	// initialize the LCD
	lcd.begin(16, 2);

	pinMode(8,INPUT);
	pinMode(LED, OUTPUT);

	// Turn on the blacklight and print a message.
	lcd.backlight();
	lcd.print("Frequency Counter");
}

void loop() {
	freqCounter();
	freqTrigger();
}

void freqCounter() {
	// Counting Frequency and display them on the LCD Display
	lcd.clear();
	lcd.setCursor(0,0);
	lcd.print("Frequency of signal");

	Htime=pulseIn(8,HIGH);      //read high time
	Ltime=pulseIn(8,LOW);        //read low time

	Ttime = Htime+Ltime;

	frequency=1000000/Ttime;    //getting frequency with Ttime is in Micro seconds
	lcd.setCursor(0,1);
	lcd.print(frequency);
	lcd.print(" Hz");
	delay(500);
	}

void freqTrigger() {
  // keep watching the frequency and trigger output when reached the limit
	if(frequency >= triggerfrequency) {
		digitalWrite(LED, HIGH);
	}
	else {
			digitalWrite(LED, LOW);
	}
}
