#include "assignment1.h"
#include <stdio.h>
#include <wiringPi.h>
#include <softPwm.h>
#include <stdint.h>

void init_shared_variable(SharedVariable* sv) {
	// You can initialize the shared variable if needed.
	sv->bProgramExit = 0;
}

void init_sensors(SharedVariable* sv) {
}

// 1. Button
void body_button(SharedVariable* sv) {
}

// 2. Big audio sensor
void body_big(SharedVariable* sv) {
}

// 3. Rotary encoder
void body_encoder(SharedVariable* sv) {
}

// 4. Obstacle avoidance sensor
void body_obstacle(SharedVariable* sv) {
}

// 5. DIP two-color LED (Dual In-line Package)
void body_twocolor(SharedVariable* sv) {
}

// 6. SMD RGB LED (Surface Mount Device)
void body_rgbcolor(SharedVariable* sv) {
}

// 7. Auto-flash LED
void body_aled(SharedVariable* sv) {
}

// 8. Buzzer
void body_buzzer(SharedVariable* sv) {
}

void writeDIP_RG(int red, int green) {
}

void writeSMD_RGB(int red, int green, int blue) {
}