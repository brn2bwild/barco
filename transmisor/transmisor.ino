#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>

#define pinDireccion     A0
#define pinVelocidad     A1

RF24 radio(9, 10);
Servo direccion;

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
    datos[0] = map(analogRead(pinDireccion), 0, 1023, 1000, 2000);
    //datos[0] = map(datos[0], 0, 180, 55, 115);
    datos[1] = map(analogRead(pinVelocidad), 0, 1023, 255, -255);
    //int valorADC = map(analogRead(pinVelocidad), 0, 1023, -1, 1);
    //int velocidad = pow(10, log10(map(analogRead(pinVelocidad), 0, 1023, 255, -255)));
    //float log10valor = log10(valorADC);
    //float velocidad = pow(10, log10valor);
    if(datos[0] > 1600) datos[0] = 1680;
    
    //if(datos[1] < 0) datos[1] = 0;
    //datos[0] = analogRead(pinDireccion);
    Serial.print(datos[0]);
    Serial.print(", ");
    Serial.println(datos[1]);
    //Serial.println(datos[1]);

    radio.write(&datos, sizeof(datos));

    delay(5);
}
