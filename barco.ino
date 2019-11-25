#define BRAKEVCC 		0
#define CW				1
#define CCW				2
#define BRAKEGND		3
#define CS_THRESHOLD	100

int entApin[2] 	= {7, 4};
int entBpin[2] 	= {8, 9};
int pwmPin[2]	= {5, 6};
int csPin[2]	= {2, 3};
int enPin[2] 	= {0, 1};

int estatusPin = 13;

void setup(){
	Serial.begin(9600);

	pinMode(estatusPin, OUTPUT);

	for(int i=0; i<2; i++){
		pinMode(entApin[i], OUTPUT);
		pinMode(entBpin[i], OUTPUT);
		pinMode(pwmPin[i], OUTPUT);	    
	}

	motorOff(0);
	motorOff(1);
}

void loop(){
	motorGo(0, CW, 50);
	motorGo(1, CCW, 50);
	delay(500);

	motorGo(0, CCW, 50);
	motorGo(1, CW, 50);
	delay(500);

	if((analogRead(csPin[0]) < CS_THRESHOLD) && (analogRead(csPin[1]) < CS_THRESHOLD)){
		digitalWrite(estatusPin, HIGH);
	}
}

void motorOff(int motor){
	for(int i=0; i<2; i++){
		digitalWrite(entApin[i], LOW);
		digitalWrite(entBpin[i], LOW);
	}

	analogWrite(pwmPin[motor], 0);
}

void motorGo(uint8_t motor, uint8_t direccion, uint8_t pwm){
	if(motor <= 1){
		if(direccion < 4){
			if(direccion <= 1)
				digitalWrite(entApin[motor], HIGH);
			else
				digitalWrite(entApin[motor], LOW);

			if((direccion == 0) || (direccion == 2))
				digitalWrite(entBpin[motor], HIGH);
			else	
				digitalWrite(entBpin[motor], LOW);
			
			analogWrite(pwmPin[motor], pwm);
		}
	}
}