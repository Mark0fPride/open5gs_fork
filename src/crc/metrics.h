#ifndef CRC_METRICS_H
#define CRC_METRICS_H

#include "ogs-metrics.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum crc_metric_type_global_s {
   CRC_METR_GLOB_CTR_NUM,
   CRC_METR_GLOB_CTR_FAIL,
   _CRC_METR_GLOB_MAX 
} crc_metric_type_global_t;
extern ogs_metrics_inst_t *crc_metrics_inst_global[_CRC_METR_GLOB_MAX];

int crc_metrics_init_inst_global(void);
int crc_metrics_free_inst_global(void);

static inline void crc_metrics_inst_global_set(crc_metric_type_global_t t, int val)
{ ogs_metrics_inst_set(crc_metrics_inst_global[t], val); }
static inline void crc_metrics_inst_global_add(crc_metric_type_global_t t, int val)
{ ogs_metrics_inst_add(crc_metrics_inst_global[t], val); }
static inline void crc_metrics_inst_global_inc(crc_metric_type_global_t t)
{ ogs_metrics_inst_inc(crc_metrics_inst_global[t]); }
static inline void crc_metrics_inst_global_dec(crc_metric_type_global_t t)
{ ogs_metrics_inst_dec(crc_metrics_inst_global[t]); }

void crc_metrics_init(void);
void crc_metrics_final(void);

#ifdef __cplusplus
}
#endif

#endif /* CRC_METRICS_H */
