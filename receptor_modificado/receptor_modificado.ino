#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>

#define pinDireccion    5
#define pinVelocidad    6

RF24 radio(7, 8);
Servo direccion, motor;

const byte address[6] = "10002";
int datos[2];

void resetDatos(){
    datos[0] = 90;  //ésta controla la dirección
    datos[1] = 0;     //ésta controla la velocidad
}

void calibrarSistema(){
  direccion.write(90);
  motor.write(0);
  delay(5000);
}

void setup(){
  direccion.attach(pinDireccion, 1000, 2000);
  motor.attach(pinVelocidad, 1000, 2000);
  calibrarSistema();
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
      direccion.write(datos[0]);
      motor.write(datos[1]);
    }
  }
}

void loop(){
    delay(5);
    recibirDatos();
    Serial.print(datos[0]);
    Serial.print(",");
    Serial.println(datos[1]);
}
