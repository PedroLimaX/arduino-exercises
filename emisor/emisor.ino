#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

//Declaremos los pines CE y el CSN
#define CE_PIN 9
#define CSN_PIN 10
 
//Variable con la dirección del canal por donde se va a transmitir
byte direccion[5] ={'c','a','n','a','l'};

//creamos el objeto radio (NRF24L01)
RF24 radio(CSN_PIN, CE_PIN);

//vector con los datos a enviar
float datos[3];

void setup()
{
  //inicializamos el NRF24L01 
  radio.begin();
  //inicializamos el puerto serie
  Serial.begin(9600); 
 
//Abrimos un canal de escritura
 radio.openWritingPipe(direccion);
 
}
 
void loop()
{ 
 //cargamos los datos en la variable datos[]
 datos[0]=analogRead(0)* (5.0 / 1023.0);
 datos[1]=millis();
 datos[2]=3.14;
 //enviamos los datos
 bool ok = radio.write(&datos, sizeof(unsigned long));
  //reportamos por el puerto serial los datos enviados 
  if(ok)
  {
     Serial.print("Enviando... "); 
     Serial.println("");
     Serial.print("V: ");
     Serial.print(datos[0]);
     Serial.print(" , Ms: ");
     Serial.print(datos[1]);
     Serial.print(" , Pi: ");
     Serial.println(datos[2]);
  }
  else
  {
     Serial.println("No enviado");
  }
  delay(1000);
}