
#ifndef CRC_HEADER
#define CRC_HEADER

#include <stdint.h>

#define CRC_FAILURE 1
#define CRC_SUCCESS 0

uint8_t crc(uint8_t* buffor, uint8_t bufforSize, uint8_t poly);

#endif