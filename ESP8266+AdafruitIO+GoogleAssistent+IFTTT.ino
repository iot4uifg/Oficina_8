/**********
  Projeto IOT4U
  IFG Campus Goiânia
  Oficina 8
  Autor:    Matheus Yosimura / Adafruit IO Subscription Example
  Objetivo: Conectar o ESP8266 com a plataforma Adafruit para atualização do estado dos LEDs de acordo com os valores recebidos

// Adafruit IO Subscription Example
// Adafruit invests time and resources providing this open source code.
// Please support Adafruit and open source hardware by purchasing
// products from Adafruit!
//
// Written by Todd Treece for Adafruit Industries
// Copyright (c) 2016 Adafruit Industries
// Licensed under the MIT license.
//
// All text above must be included in any redistribution.

/************************** Configuration ***********************************/

// edit the config.h tab and enter your Adafruit IO credentials
// and any additional configuration needed for WiFi, cellular,
// or ethernet clients.

#include "config.h"  //adiciona biblioteca config.h

/************************ Example Starts Here *******************************/

AdafruitIO_Feed *Verde = io.feed("Verde");  //Inscreve no Feed Verde
AdafruitIO_Feed *Vermelho = io.feed("Vermelho");  //Inscreve no Feed Vermelho

#define R 4  //GPIO 4 para o LED Vermelho
#define G 5  //GPIO 5 para o LED Verde
void setup() {
  pinMode(R,OUTPUT);  
  pinMode(G,OUTPUT);
  Serial.begin(115200);
  while(! Serial);
  Serial.print("Connecting to Adafruit IO");
  io.connect();  //Conecta com a plataforma Adafruit
  Vermelho->onMessage(RedMessage);  //Chama a função RedMessage
  Verde->onMessage(GreenMessage);  //Chama a função GreenMessage
  while(io.mqttStatus() < AIO_CONNECTED) {  //Imrpime pontos (.............) até conseguir se comunicar com a plataforma Adafruit
    Serial.print(".");
    delay(500);
  }
  Vermelho->get();  //Ponteiro Vermelho recebe atualização do Feed Vermelho
  Verde->get();  //Ponteiro Verde recebe atualização do Feed Verde
  Serial.println();
  Serial.println(io.statusText());
}

void loop() {
  io.run();  //Função para comunicação com o Adafruit
}


//Função para ligar ou desligar o LED vermelho de acordo com a atualização recebida do Feed Vermelho
void RedMessage(AdafruitIO_Data *data) {
  Serial.print("received <- Vermelho :  ");
  Serial.println(data->value());
  if(data->isTrue()){
    digitalWrite(R,HIGH);  
  }else{
    digitalWrite(R,LOW);  
  }
}

//Função para ligar ou desligar o LED verde de acordo com a atualização recebida do Feed Verde
void GreenMessage(AdafruitIO_Data *data) {
  Serial.print("received <- Verde : ");
  Serial.println(data->value());
  if(data->isTrue()){
    digitalWrite(G,HIGH);  
  }else{
    digitalWrite(G,LOW);  
  }
}
