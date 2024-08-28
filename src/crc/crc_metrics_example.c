#include "crc_metrics_example.h"
#include "crc.h"
#include "metrics.h"

void crc_metrics_example(void){

    uint8_t poly = 0b10100000;
    uint8_t buffor[] = { 0b11010110 };

    crc_metrics_inst_global_inc(CRC_METR_GLOB_CTR_NUM);
    uint8_t crc_value = crc(buffor, sizeof(buffor),poly);

    uint8_t buffor2[sizeof(buffor) + 1];
    memcpy(buffor2, buffor, sizeof(buffor));
    buffor2[sizeof(buffor)] = crc_value;

    crc_metrics_inst_global_inc(CRC_METR_GLOB_CTR_NUM);
    crc_value = crc(buffor2, sizeof(buffor2),poly);
    if(crc_value == 0){
        crc_metrics_inst_global_inc(CRC_METR_GLOB_CTR_FAIL);
    }
}