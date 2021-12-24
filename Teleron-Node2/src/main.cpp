
#include <Arduino.h>
#include "E01RF.h"


uint8_t myAddress[6] = "Node2"; // Benim adresim
uint8_t otherAddress[6] = "Node1"; // Bağlandığım adres

// Modu gönderme veya alma olarak ayarlar
bool role = true;  // true = TX role, false = RX role


float* data;

E01RF radio(5,4,myAddress,otherAddress,1); // CE, CS, adresim, bağlanılacak adres, güç modu
// Güç modu 1 ise low power modu açılır 


void setup() {
  Serial.begin(9600);
  data = new float; 
} 

void loop() {

  if (role) { //Eğer yollama modunda ise veriyi yollar
      if (radio.sendData(data, sizeof(*data)))
      {
        role = !role; //Yollandıysa mod değiştirir
      }
    delay(1000); 

  } else { //Eğer alma modunda ise veriyi alır 
    if (radio.receiveData(data))
      {
        Serial.print(F("Received ")); // gelen veriyi ekrana yazdırır
        Serial.println(*data);
        role = !role; // alındıysa mod değiştir
        *data = *data + 0.1; //veriyi 0.1 arttırır.
      } 
  }
}