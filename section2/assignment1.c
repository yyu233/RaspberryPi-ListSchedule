#include "assignment1.h"
#include <stdio.h>
#include <wiringPi.h>
#include <softPwm.h>
#include <stdint.h>

void init_shared_variable(SharedVariable* sv) {
	// You can initialize the shared variable if needed.
	sv->bProgramExit = 0;
	sv->state = 1;
	sv->obs = 1;
	sv->aud = 0;
	sv->rot = 0;
}

void init_sensors(SharedVariable* sv) {
	//button
	pinMode(PIN_BUTTON, INPUT);
	
	//big sound
	pinMode(PIN_BIG, INPUT);

	//rot
	pinMode(PIN_ROTARY_CLK, INPUT);
	pinMode(PIN_ROTARY_DT, INPUT);
	
	//obs
	pinMode(PIN_OBS, INPUT);
	
	//2-color led 
	pinMode(PIN_DIP_RED, OUTPUT);
	pinMode(PIN_DIP_GRN, OUTPUT);
	
	//rgb
	if (softPwmCreate(PIN_SMD_RED, 0, 255) != 0) {
		printf("setup software pwm handler failed!");
		sv->bProgramExit = 1;
	}
	if (softPwmCreate(PIN_SMD_GRN, 0, 255) != 0) {
		printf("setup software pwm handler failed!");
		sv->bProgramExit = 1;

	}
	if (softPwmCreate(PIN_SMD_BLU, 0, 255) != 0) {
		printf("setup software pwm handler failed!");
		sv->bProgramExit = 1;
	}
	
	//aled
	pinMode(PIN_ALED, OUTPUT);
	
	//buzzer
	if (softPwmCreate(PIN_BUZZER, 0, 100) != 0) {
		printf("setup software pwm handler failed!");
		sv->bProgramExit = 1;
	}
}

// 1. Button
void body_button(SharedVariable* sv) {
	int read;
	
	while(1) {
		read = digitalRead(PIN_BUTTON);
		if (read == 0) {
			if (sv->state == 1) {
				sv->state = 0;
			} else {
				sv->state = 1;
			}
		}
	}
}

// 2. Big audio sensor
void body_big(SharedVariable* sv) {
	int read;
	
	while(1) {
		read = digitalRead(PIN_BIG);
		sv->aud = read;
	}
}

// 3. Rotary encoder
void body_encoder(SharedVariable* sv) {
	int lastCLKState = digitalRead(PIN_ROTARY_CLK);;
	
	while(1){
		int currCLKState = digitalRead(PIN_ROTARY_CLK);
		int currDTState = digitalRead(PIN_ROTARY_DT);
		if (currCLKState != lastCLKState) {
			//CW
			if (currCLKState == currDTState) {
				sv->rot = 1;
			} else { //CCW
				sv->rot = 2;
			}
		}
		lastCLKState = currCLKState;
	}
}

// 4. Obstacle avoidance sensor
void body_obstacle(SharedVariable* sv) {
	int read;
	
	while(1) {
		read = digitalRead(PIN_OBS);
		if (read == 1) { //Not detected
			sv->obs = 1;
		}
		if (read == 0) {//detected
			sv->obs = 0;
		}
	}
}

// 5. DIP two-color LED (Dual In-line Package)
void body_twocolor(SharedVariable* sv) {
	while(1) {
		if (sv->state == 1) {
			//RED
			if (sv->obs == 1) {
				digitalWrite(PIN_DIP_GRN, LOW);
				digitalWrite(PIN_DIP_RED, HIGH);
			} else { //GREEN
				digitalWrite(PIN_DIP_GRN, HIGH);
				digitalWrite(PIN_DIP_RED, LOW);
			}
		} else {
			digitalWrite(PIN_DIP_RED, LOW);
			digitalWrite(PIN_DIP_GRN, LOW);
		}
	}
}

// 6. SMD RGB LED (Surface Mount Device)
void body_rgbcolor(SharedVariable* sv) {
	while(1) {
		if (sv->state == 1) {
			//rgb
			if (sv->rot == 1 && sv->obs == 0) {
				//RED
				softPwmWrite(PIN_SMD_RED, 0x00);
				softPwmWrite(PIN_SMD_GRN, 0xff);
				softPwmWrite(PIN_SMD_BLU, 0x00);
			}
			if (sv->rot == 2 && sv->obs == 0) {
				//PURPLE
				softPwmWrite(PIN_SMD_RED, 0x00);
				softPwmWrite(PIN_SMD_GRN, 0xff);
				softPwmWrite(PIN_SMD_BLU, 0xff);
			}
			if (sv->rot == 1 && sv->obs == 1) {
				//GREEN
				softPwmWrite(PIN_SMD_RED, 0xff);
				softPwmWrite(PIN_SMD_GRN, 0x00);
				softPwmWrite(PIN_SMD_BLU, 0x00);
			}
			if (sv->rot == 2 && sv->obs == 1) {
				//CYAN
				softPwmWrite(PIN_SMD_RED, 0xee);
				softPwmWrite(PIN_SMD_GRN, 0x00);
				softPwmWrite(PIN_SMD_BLU, 0xc8);
			}
		} else {
			softPwmWrite(PIN_SMD_RED, 0x00);
			softPwmWrite(PIN_SMD_GRN, 0x00);
			softPwmWrite(PIN_SMD_BLU, 0x00);
		}
	}
}

// 7. Auto-flash LED
void body_aled(SharedVariable* sv) {
	while(1) {
		if (sv->state == 1) {
			digitalWrite(PIN_ALED, HIGH);
		} else {
			digitalWrite(PIN_ALED, LOW);
		}
	}
}

// 8. Buzzer
void body_buzzer(SharedVariable* sv) {
	while(1) {
		if (sv->aud == 1) {
			for (int i = 1; i <= 500; i++) {
				softPwmWrite(PIN_BUZZER, 99);
				delay(1);
			}
		} else {
			softPwmWrite(PIN_BUZZER, 0);	
		}
	}
}

void writeDIP_RG(int red, int green) {
}

void writeSMD_RGB(int red, int green, int blue) {
}
