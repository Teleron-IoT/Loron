#pragma once
#include <Arduino.h>
#include "RF24.h"
#include <SPI.h>
#include "RF24.h"
class E01RF:RF24{

    uint8_t *addr;
    uint8_t *connectAddr;


    public:
    E01RF(uint16_t CE, uint16_t CS, uint8_t* _addr, uint8_t* _connectAddr,bool lowPower);// CE, CS, adresim, bağlanılacak adres, güç modu
    // Güç modu 1 ise low power modu açılır 
    bool sendData(void* data,int size); // data'da aldığı veriyi yollar

    bool receiveData(void* data); // aldığı veriyi data'ya yazar



};

