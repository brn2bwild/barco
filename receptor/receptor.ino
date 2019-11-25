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

//struct Transmisor{
//    int direccion;
//    int velocidad;
//};
//
//Transmisor datos;

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

unsigned long tiempo_ultima_recepcion = 0;

void recibirDatos(){
  if(radio.available()){
    while(radio.available()){
      radio.read(&datos, sizeof(datos));
      //servo.write(datos[0]);
      servo.writeMicroseconds(datos[0]);
      motorPrincipal(datos[1]);
    }
        //tiempo_ultima_recepcion = millis();
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

//  if(millis() - tiempo_ultima_recepcion > 1000) resetDatos();

//    int angulo = map(datos.direccion, 0, 255, 0, 180);
//    int velocidad = map(datos.velocidad, 127, 255, 0, 255);
//    servo.write(90);
//    delay(1000);
//    servo.write(180);
//    delay(1000);
//    servo.write(0);
//    delay(1000);
    Serial.print(datos[0]);
    Serial.print(", ");
    Serial.println(datos[1]);
}
