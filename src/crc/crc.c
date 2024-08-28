#include "crc.h"

uint8_t crc(uint8_t* buffer, uint8_t bufferSize, uint8_t poly) {
    
    uint8_t word = buffer[0];
    int i;;
    for (i = 0; i < bufferSize; i++) {
        int j;
        for (j = 0; j < 8; j++) {

            if (word & 0x80) {
                word ^= poly;
            }

            word <<= 1;  

            if (i + 1 < bufferSize) {
                word |= (buffer[i + 1] & (0x80 >> j)) >> (7 - j);
            }         
        }
    }
    return word; //reszta
}


