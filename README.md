
# Teleron - ESP32 RF Geliştirme Kartı 

Teleron, EBYTE E01 modülü kullanarak kolayca RF haberleşmesi yapabilen bir geliştirme kartıdır.




## Kütüphane Kullanımı

### E01RF 
EC25'e istediğim AT komutlarını gönderebilmek ve aldığımız cevabı yorumlamak için gerekli fonksiyonlar bu sınıf içinde tanımlanmıştır.

#### E01RF(uint16_t CE, uint16_t CS, uint8_t* _addr, uint8_t* _connectAddr,bool lowPower);
E01RF'i initialize etmek için kullanılır.

| Parametre | Tip     | Açıklama                |
| :-------- | :------- | :------------------------- |
| `CE` | `uint16_t` | E01 CE pini |
| `CS` | `uint16_t` | E01 CS pini |
| `_addr` | `uint8_t` | Bağlı modüle atanacak adres |
| `_connectAddr` | `uint8_t` | Uzak modülün adresi |
| `lowPower` | `bool` | Güç modunu belirler. Eğer 1 ise düşük güç modu aktif edilir. |

#### bool sendData(void* data,int size);
E01RF ile gönderilmek istenen verinin yollanmasını sağlar.
| Parametre | Tip     | Açıklama                |
| :-------- | :------- | :------------------------- |
| `data` | `pointer` | Gönderilecek veri |
| `size` | `int` | Gönderilecek verinin boyutu |
| `return` | `bool` | Gönderim başarısı |

#### bool receiveData(void* data);
E01RF ile veri alınmasını sağlar.
| Parametre | Tip     | Açıklama                |
| :-------- | :------- | :------------------------- |
| `data` | `pointer` | Gelen veri |
| `return` | `bool` | Gelen veri var mı  |

#### void listenPost();
EC25'den dönen cevaplar bitiş verisi gelene kadar dinlenir.

## Örnek Kod

### Gönderici

```cpp

#include <Arduino.h>
#include "E01RF.h"


uint8_t myAddress[6] = "Node2"; // Benim adresim
uint8_t otherAddress[6] = "Node1"; // Bağlandığım adres

float* data;

E01RF radio(5,4,myAddress,otherAddress,1); // CE, CS, adresim, bağlanılacak adres, güç modu
// Güç modu 1 ise low power modu açılır 


void setup() {
  Serial.begin(9600);
  data = new float; 
} 

void loop() {
  radio.sendData(data, sizeof(*data));
  delay(1000); 

}
```

### Alıcı

```cpp

#include <Arduino.h>
#include "E01RF.h"


uint8_t myAddress[6] = "Node1"; // Benim adresim
uint8_t otherAddress[6] = "Node2"; // Bağlandığım adres

float* data;

E01RF radio(5,4,myAddress,otherAddress,1); // CE, CS, adresim, bağlanılacak adres, güç modu
// Güç modu 1 ise low power modu açılır 


void setup() {
  Serial.begin(9600);
  data = new float; 
} 

void loop() {

  if (radio.receiveData(data))
  {
    Serial.print(F("Received ")); // gelen veriyi ekrana yazdırır
    Serial.println(*data);
    *data = *data + 0.1; //veriyi 0.1 arttırır.
  } 
}
```