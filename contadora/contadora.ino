#include <SoftwareSerial.h> 
SoftwareSerial BT(10,11); 

int entrada=2, 
    cont=0, 
    estado=0, 
    maxCoin = 0,
    pinSSR = 7;

char motorStart = 'B';
    
void setup() {   
  BT.begin(9600);
  Serial.begin(9600);
  pinMode(entrada,INPUT);
  pinMode(pinSSR , OUTPUT);
}

void loop() {       
  if (maxCoin < 1 || (motorStart != 'A')) {
     
    if (BT.available()) {
        if (maxCoin < 1) {
          char data = BT.parseInt();
          if (data != 0) {
            maxCoin = (int)data;
            Serial.println(maxCoin);
          } else {
            //ingresa una cantidad antes de iniciar a contar
            Serial.println("ingresa una cantidad antes de iniciar a contar");
          }
        } else {
          motorStart = BT.read();
          Serial.println(motorStart);
        }
    }
   
    if(Serial.available()) {
         if (maxCoin < 1) {
          char data = Serial.parseInt();
          if (data != 0) {
            maxCoin = (int)data;
            Serial.println(maxCoin);
          } else {
            //ingresa una cantidad antes de iniciar a contar
            Serial.println("ingresa una cantidad antes de iniciar a contar");
          }
         } else {
          motorStart = Serial.read();
          Serial.println(motorStart);
        }
    }
  } else {
    if(maxCoin > cont) {
      estado = digitalRead(entrada);
      digitalWrite(pinSSR , HIGH);
      if(estado == LOW){
        cont++;
        while(estado == LOW){                 //antirebote
          estado = digitalRead(entrada);
        }
      }
      Serial.println(cont);
    }
    if(cont >= maxCoin){
      cont=0;
      maxCoin = 0;
      motorStart = 'B';
      digitalWrite(pinSSR , LOW);
    }
  }
  
  
 
} 
