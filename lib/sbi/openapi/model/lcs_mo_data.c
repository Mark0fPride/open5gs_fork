
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "lcs_mo_data.h"

OpenAPI_lcs_mo_data_t *OpenAPI_lcs_mo_data_create(
    OpenAPI_list_t *allowed_service_classes
)
{
    OpenAPI_lcs_mo_data_t *lcs_mo_data_local_var = ogs_malloc(sizeof(OpenAPI_lcs_mo_data_t));
    ogs_assert(lcs_mo_data_local_var);

    lcs_mo_data_local_var->allowed_service_classes = allowed_service_classes;

    return lcs_mo_data_local_var;
}

void OpenAPI_lcs_mo_data_free(OpenAPI_lcs_mo_data_t *lcs_mo_data)
{
    OpenAPI_lnode_t *node = NULL;

    if (NULL == lcs_mo_data) {
        return;
    }
    if (lcs_mo_data->allowed_service_classes) {
        OpenAPI_list_free(lcs_mo_data->allowed_service_classes);
        lcs_mo_data->allowed_service_classes = NULL;
    }
    ogs_free(lcs_mo_data);
}

cJSON *OpenAPI_lcs_mo_data_convertToJSON(OpenAPI_lcs_mo_data_t *lcs_mo_data)
{
    cJSON *item = NULL;
    OpenAPI_lnode_t *node = NULL;

    if (lcs_mo_data == NULL) {
        ogs_error("OpenAPI_lcs_mo_data_convertToJSON() failed [LcsMoData]");
        return NULL;
    }

    item = cJSON_CreateObject();
    if (lcs_mo_data->allowed_service_classes == OpenAPI_lcs_mo_service_class_NULL) {
        ogs_error("OpenAPI_lcs_mo_data_convertToJSON() failed [allowed_service_classes]");
        return NULL;
    }
    cJSON *allowed_service_classesList = cJSON_AddArrayToObject(item, "allowedServiceClasses");
    if (allowed_service_classesList == NULL) {
        ogs_error("OpenAPI_lcs_mo_data_convertToJSON() failed [allowed_service_classes]");
        goto end;
    }
    OpenAPI_list_for_each(lcs_mo_data->allowed_service_classes, node) {
        if (cJSON_AddStringToObject(allowed_service_classesList, "", OpenAPI_lcs_mo_service_class_ToString((intptr_t)node->data)) == NULL) {
            ogs_error("OpenAPI_lcs_mo_data_convertToJSON() failed [allowed_service_classes]");
            goto end;
        }
    }

end:
    return item;
}

OpenAPI_lcs_mo_data_t *OpenAPI_lcs_mo_data_parseFromJSON(cJSON *lcs_mo_dataJSON)
{
    OpenAPI_lcs_mo_data_t *lcs_mo_data_local_var = NULL;
    OpenAPI_lnode_t *node = NULL;
    cJSON *allowed_service_classes = NULL;
    OpenAPI_list_t *allowed_service_classesList = NULL;
    allowed_service_classes = cJSON_GetObjectItemCaseSensitive(lcs_mo_dataJSON, "allowedServiceClasses");
    if (!allowed_service_classes) {
        ogs_error("OpenAPI_lcs_mo_data_parseFromJSON() failed [allowed_service_classes]");
        goto end;
    }
        cJSON *allowed_service_classes_local = NULL;
        if (!cJSON_IsArray(allowed_service_classes)) {
            ogs_error("OpenAPI_lcs_mo_data_parseFromJSON() failed [allowed_service_classes]");
            goto end;
        }

        allowed_service_classesList = OpenAPI_list_create();

        cJSON_ArrayForEach(allowed_service_classes_local, allowed_service_classes) {
            if (!cJSON_IsString(allowed_service_classes_local)) {
                ogs_error("OpenAPI_lcs_mo_data_parseFromJSON() failed [allowed_service_classes]");
                goto end;
            }
            OpenAPI_list_add(allowed_service_classesList, (void *)OpenAPI_lcs_mo_service_class_FromString(allowed_service_classes_local->valuestring));
        }

    lcs_mo_data_local_var = OpenAPI_lcs_mo_data_create (
        allowed_service_classesList
    );

    return lcs_mo_data_local_var;
end:
    if (allowed_service_classesList) {
        OpenAPI_list_free(allowed_service_classesList);
        allowed_service_classesList = NULL;
    }
    return NULL;
}

OpenAPI_lcs_mo_data_t *OpenAPI_lcs_mo_data_copy(OpenAPI_lcs_mo_data_t *dst, OpenAPI_lcs_mo_data_t *src)
{
    cJSON *item = NULL;
    char *content = NULL;

    ogs_assert(src);
    item = OpenAPI_lcs_mo_data_convertToJSON(src);
    if (!item) {
        ogs_error("OpenAPI_lcs_mo_data_convertToJSON() failed");
        return NULL;
    }

    content = cJSON_Print(item);
    cJSON_Delete(item);

    if (!content) {
        ogs_error("cJSON_Print() failed");
        return NULL;
    }

    item = cJSON_Parse(content);
    ogs_free(content);
    if (!item) {
        ogs_error("cJSON_Parse() failed");
        return NULL;
    }

    OpenAPI_lcs_mo_data_free(dst);
    dst = OpenAPI_lcs_mo_data_parseFromJSON(item);
    cJSON_Delete(item);

    return dst;
}

