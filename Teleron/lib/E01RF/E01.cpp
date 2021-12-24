#include "E01RF.h"

    E01RF::E01RF(uint16_t CE, uint16_t CS, uint8_t* _addr, uint8_t* _connectAddr, bool lowPower):RF24(CE, CS){
        addr = _addr; 
        connectAddr = _connectAddr;

        // SPI'ı açarak bağlantıyı kontrol eder
        if (!RF24::begin()) {
            Serial.println(F("radio hardware is not responding!!"));
            while (1) {} //Bağlanamazsa sonsuz döngüye gir
        }

        if(lowPower){
            RF24::setPALevel(RF24_PA_LOW);
        }

        RF24::openWritingPipe(*addr);

        RF24::openReadingPipe(1, *connectAddr);
    };

    bool E01RF::sendData(void* data, int size){
        RF24::stopListening();
        RF24::setPayloadSize(size); 
        bool report = RF24::write(data, size); 

        if (report) {
        Serial.print(F("Transmission successful! "));
        
        } else {
        Serial.println(F("Transmission failed or timed out"));
        }
        return report;
    }

    bool E01RF::receiveData(void* data){
        RF24::startListening();
        uint8_t pipe;
        if (RF24::available(&pipe)) {             
            uint8_t bytes = RF24::getPayloadSize();
            RF24::read(data, bytes);
            return true;
        }else{
            return false;
        }
    }