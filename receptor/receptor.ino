#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>

#define pinDireccion    6
#define pinMotorIzq     3
#define pinMotorDer     4
#define pinVelocidad    5

RF24 radio(7, 8);
Servo servo;

const byte address[6] = "10002";
int datos[2];

void resetDatos(){
    datos[0] = 1500;
    datos[1] = 0;
}

void setup(){
  pinMode(pinMotorIzq, OUTPUT);
  pinMode(pinMotorDer, OUTPUT);
  pinMode(pinVelocidad, OUTPUT);
  servo.attach(9);
  servo.writeMicroseconds(1500);
  Serial.begin(9600);
  resetDatos();
  radio.begin();
  radio.setAutoAck(false);
  radio.setDataRate(RF24_250KBPS);
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
}

void recibirDatos(){
  if(radio.available()){
    while(radio.available()){
      radio.read(&datos, sizeof(datos));
      servo.writeMicroseconds(datos[0]);
      motorPrincipal(datos[1]);
    }
  }
}

void motorPrincipal(int _velocidad){
  if(_velocidad >= 0){
    digitalWrite(pinMotorDer, HIGH);
    digitalWrite(pinMotorIzq, LOW);
  }else if(_velocidad < 0){
    _velocidad = _velocidad * -1;
    digitalWrite(pinMotorDer, LOW);
    digitalWrite(pinMotorIzq, HIGH);
  }
  if(_velocidad > 255) _velocidad = 255;
  else if(_velocidad < -255) _velocidad = -255;
  
  analogWrite(pinVelocidad, _velocidad);
}

void loop(){
    delay(5);
    recibirDatos();
    Serial.print(datos[0]);
    Serial.print(', ');
    Serial.println(datos[1]);
}
