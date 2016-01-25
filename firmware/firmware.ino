#include <Servo.h>
// create servo object to control a servo
Servo esc;

int maxThrottle = 180;

int curThrottle = 0;

// will store last time
unsigned long previousMillis = 0;

unsigned long currentInterval = 0;

// time to prepare (milliseconds)
const long prepareTime = 120000; // 1000ms * 60sec * 2min
// time to fly (milliseconds)
const long flyingTime = 240000;	// 1000ms * 60sec * 4min

/*
	Current state
	0 - prepare to fly
	1 - fly
	2 - landing
*/
int currentState = 0;

void setup() {
	// attaches the servo on pin 9 to the servo object
	esc.attach(9);
	esc.write(curThrottle);
	currentInterval = prepareTime;
}

void loop() {
	unsigned long currentMillis = millis();
	if (currentMillis - previousMillis >= currentInterval) {
		if (currentState == 0) {
			// we are ready to fly, throttle max!
			for (curThrottle = 0; curThrottle <= maxThrottle; curThrottle += 10) {
				esc.write(curThrottle);
				delay(10);
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
			for (curThrottle = maxThrottle; curThrottle > 0; curThrottle -= 10) {
				esc.write(curThrottle);
				delay(10);
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
