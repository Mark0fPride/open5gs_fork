#include "ogs-app.h"
#include "metrics.h"

typedef struct crc_metrics_spec_def_s {
    unsigned int type;
    const char *name;
    const char *description;
    int initial_val;
    unsigned int num_labels;
    const char **labels;
    ogs_metrics_histogram_params_t histogram_params;
} crc_metrics_spec_def_t;

/* Helper generic functions: */
static int crc_metrics_init_inst(ogs_metrics_inst_t **inst, ogs_metrics_spec_t **specs,
        unsigned int len, unsigned int num_labels, const char **labels)
{
    unsigned int i;
    for (i = 0; i < len; i++)
        inst[i] = ogs_metrics_inst_new(specs[i], num_labels, labels);
    return OGS_OK;
}

static int crc_metrics_free_inst(ogs_metrics_inst_t **inst,
        unsigned int len)
{
    unsigned int i;
    for (i = 0; i < len; i++)
        ogs_metrics_inst_free(inst[i]);
    memset(inst, 0, sizeof(inst[0]) * len);
    return OGS_OK;
}

static int crc_metrics_init_spec(ogs_metrics_context_t *ctx,
        ogs_metrics_spec_t **dst, crc_metrics_spec_def_t *src, unsigned int len)
{
    unsigned int i;
    for (i = 0; i < len; i++) {
        dst[i] = ogs_metrics_spec_new(ctx, src[i].type,
                src[i].name, src[i].description,
                src[i].initial_val, src[i].num_labels, src[i].labels,
                &src[i].histogram_params);
    }

    return OGS_OK;
}

/* GLOBAL */
ogs_metrics_spec_t *crc_metrics_spec_global[_CRC_METR_GLOB_MAX];
ogs_metrics_inst_t *crc_metrics_inst_global[_CRC_METR_GLOB_MAX];
crc_metrics_spec_def_t crc_metrics_spec_def_global[_CRC_METR_GLOB_MAX] = {
[CRC_METR_GLOB_CTR_NUM] = {
    .type = OGS_METRICS_METRIC_TYPE_COUNTER,
    .name = "fivegs_crc",
    .description = "Number of crc calculations",
},
[CRC_METR_GLOB_CTR_FAIL] = {
    .type = OGS_METRICS_METRIC_TYPE_COUNTER,
    .name = "fivegs_crc",
    .description = "Number of successful error detections by crc",
},
};

int crc_metrics_init_inst_global(void)
{
    return crc_metrics_init_inst(crc_metrics_inst_global, crc_metrics_spec_global,
                _CRC_METR_GLOB_MAX, 0, NULL);
}
int crc_metrics_free_inst_global(void)
{
    return crc_metrics_free_inst(crc_metrics_inst_global, _CRC_METR_GLOB_MAX);
}


void crc_metrics_init(void)
{
    ogs_metrics_context_t *ctx = ogs_metrics_self();
    ogs_metrics_context_init();

    crc_metrics_init_spec(ctx, crc_metrics_spec_global, crc_metrics_spec_def_global,
            _CRC_METR_GLOB_MAX);

    crc_metrics_init_inst_global();

}

void crc_metrics_final(void)
{
    ogs_metrics_context_final();
}
