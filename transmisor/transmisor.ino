#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>

#define pinDireccion     A0
#define pinVelocidad     A1

RF24 radio(9, 10);

const byte address[6] = "10002";

int datos[2];

void setup(){
  Serial.begin(9600);
  radio.begin();
  radio.setAutoAck(false);
  radio.setDataRate(RF24_250KBPS);
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
}

void loop(){
    datos[0] = map(analogRead(pinDireccion), 0, 1000, 0, 180);
    datos[1] = map(analogRead(pinVelocidad), 480, 1000, 0, 180);

//    datos[0] = analogRead(pinDireccion);
//    datos[1] = analogRead(pinVelocidad);
    
    if(datos[0] > 180) datos[0] = 180;
    if(datos[0] < 0) datos[0] = 0;
    if(datos[1] > 180) datos[1] = 180;
    if(datos[1] < 0) datos[1] = 0;
    
     Serial.print(datos[0]);
     Serial.print(", ");
     Serial.println(datos[1]);

    radio.write(&datos, sizeof(datos));
    delay(5);
}
