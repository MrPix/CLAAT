#include <Servo.h>
// create servo object to control a servo
Servo esc;

int maxThrottle = 120;

int curThrottle = 0;

// will store last time
unsigned long previousMillis = 0;

unsigned long currentInterval = 0;

// time to prepare (milliseconds)
const long prepareTime = 30000;
// time to fly (milliseconds)
const long flyingTime = 90000;

/*
	Current state
	0 - prepare to fly
	1 - fly
	2 - landing
*/
int currentState = 0;

void setup() {
	// attaches the servo on pin 9 to the servo object
	esc.attach(9, 1000, 2000);
	esc.write(curThrottle);
	currentInterval = prepareTime;
}

void loop() {
	unsigned long currentMillis = millis();
	if (currentMillis - previousMillis >= currentInterval) {
		if (currentState == 0) {
			// we are ready to fly, throttle max!
			for (curThrottle = 0; curThrottle <= maxThrottle; curThrottle += 1) {
				esc.write(curThrottle);
				delay(20); // Throlle up delay
			}
			if (curThrottle < maxThrottle) {
				curThrottle = maxThrottle;
			}
			esc.write(curThrottle);
			currentInterval = flyingTime;
			previousMillis = millis();
			currentState = 1;
		} else if (currentState == 1) {
			// flying time is gone, time to landing
			for (curThrottle = maxThrottle; curThrottle > 0; curThrottle -= 1) {
				esc.write(curThrottle);
				delay(100);// Throlle down delay
			}
			if (curThrottle < 0) {
				curThrottle = 0;
			}
			esc.write(curThrottle);
			currentState = 2;
		} else {
			// done
		}
	}
}