
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "lmf_info.h"

OpenAPI_lmf_info_t *OpenAPI_lmf_info_create(
    OpenAPI_list_t *serving_client_types,
    char *lmf_id,
    OpenAPI_list_t *serving_access_types,
    OpenAPI_list_t *serving_an_node_types,
    OpenAPI_list_t *serving_rat_types
)
{
    OpenAPI_lmf_info_t *lmf_info_local_var = ogs_malloc(sizeof(OpenAPI_lmf_info_t));
    ogs_assert(lmf_info_local_var);

    lmf_info_local_var->serving_client_types = serving_client_types;
    lmf_info_local_var->lmf_id = lmf_id;
    lmf_info_local_var->serving_access_types = serving_access_types;
    lmf_info_local_var->serving_an_node_types = serving_an_node_types;
    lmf_info_local_var->serving_rat_types = serving_rat_types;

    return lmf_info_local_var;
}

void OpenAPI_lmf_info_free(OpenAPI_lmf_info_t *lmf_info)
{
    OpenAPI_lnode_t *node = NULL;

    if (NULL == lmf_info) {
        return;
    }
    if (lmf_info->serving_client_types) {
        OpenAPI_list_for_each(lmf_info->serving_client_types, node) {
            OpenAPI_external_client_type_free(node->data);
        }
        OpenAPI_list_free(lmf_info->serving_client_types);
        lmf_info->serving_client_types = NULL;
    }
    if (lmf_info->lmf_id) {
        ogs_free(lmf_info->lmf_id);
        lmf_info->lmf_id = NULL;
    }
    if (lmf_info->serving_access_types) {
        OpenAPI_list_free(lmf_info->serving_access_types);
        lmf_info->serving_access_types = NULL;
    }
    if (lmf_info->serving_an_node_types) {
        OpenAPI_list_free(lmf_info->serving_an_node_types);
        lmf_info->serving_an_node_types = NULL;
    }
    if (lmf_info->serving_rat_types) {
        OpenAPI_list_free(lmf_info->serving_rat_types);
        lmf_info->serving_rat_types = NULL;
    }
    ogs_free(lmf_info);
}

cJSON *OpenAPI_lmf_info_convertToJSON(OpenAPI_lmf_info_t *lmf_info)
{
    cJSON *item = NULL;
    OpenAPI_lnode_t *node = NULL;

    if (lmf_info == NULL) {
        ogs_error("OpenAPI_lmf_info_convertToJSON() failed [LmfInfo]");
        return NULL;
    }

    item = cJSON_CreateObject();
    if (lmf_info->serving_client_types) {
    cJSON *serving_client_typesList = cJSON_AddArrayToObject(item, "servingClientTypes");
    if (serving_client_typesList == NULL) {
        ogs_error("OpenAPI_lmf_info_convertToJSON() failed [serving_client_types]");
        goto end;
    }
    OpenAPI_list_for_each(lmf_info->serving_client_types, node) {
        cJSON *itemLocal = OpenAPI_external_client_type_convertToJSON(node->data);
        if (itemLocal == NULL) {
            ogs_error("OpenAPI_lmf_info_convertToJSON() failed [serving_client_types]");
            goto end;
        }
        cJSON_AddItemToArray(serving_client_typesList, itemLocal);
    }
    }

    if (lmf_info->lmf_id) {
    if (cJSON_AddStringToObject(item, "lmfId", lmf_info->lmf_id) == NULL) {
        ogs_error("OpenAPI_lmf_info_convertToJSON() failed [lmf_id]");
        goto end;
    }
    }

    if (lmf_info->serving_access_types != OpenAPI_access_type_NULL) {
    cJSON *serving_access_typesList = cJSON_AddArrayToObject(item, "servingAccessTypes");
    if (serving_access_typesList == NULL) {
        ogs_error("OpenAPI_lmf_info_convertToJSON() failed [serving_access_types]");
        goto end;
    }
    OpenAPI_list_for_each(lmf_info->serving_access_types, node) {
        if (cJSON_AddStringToObject(serving_access_typesList, "", OpenAPI_access_type_ToString((intptr_t)node->data)) == NULL) {
            ogs_error("OpenAPI_lmf_info_convertToJSON() failed [serving_access_types]");
            goto end;
        }
    }
    }

    if (lmf_info->serving_an_node_types != OpenAPI_an_node_type_NULL) {
    cJSON *serving_an_node_typesList = cJSON_AddArrayToObject(item, "servingAnNodeTypes");
    if (serving_an_node_typesList == NULL) {
        ogs_error("OpenAPI_lmf_info_convertToJSON() failed [serving_an_node_types]");
        goto end;
    }
    OpenAPI_list_for_each(lmf_info->serving_an_node_types, node) {
        if (cJSON_AddStringToObject(serving_an_node_typesList, "", OpenAPI_an_node_type_ToString((intptr_t)node->data)) == NULL) {
            ogs_error("OpenAPI_lmf_info_convertToJSON() failed [serving_an_node_types]");
            goto end;
        }
    }
    }

    if (lmf_info->serving_rat_types != OpenAPI_rat_type_NULL) {
    cJSON *serving_rat_typesList = cJSON_AddArrayToObject(item, "servingRatTypes");
    if (serving_rat_typesList == NULL) {
        ogs_error("OpenAPI_lmf_info_convertToJSON() failed [serving_rat_types]");
        goto end;
    }
    OpenAPI_list_for_each(lmf_info->serving_rat_types, node) {
        if (cJSON_AddStringToObject(serving_rat_typesList, "", OpenAPI_rat_type_ToString((intptr_t)node->data)) == NULL) {
            ogs_error("OpenAPI_lmf_info_convertToJSON() failed [serving_rat_types]");
            goto end;
        }
    }
    }

end:
    return item;
}

OpenAPI_lmf_info_t *OpenAPI_lmf_info_parseFromJSON(cJSON *lmf_infoJSON)
{
    OpenAPI_lmf_info_t *lmf_info_local_var = NULL;
    OpenAPI_lnode_t *node = NULL;
    cJSON *serving_client_types = NULL;
    OpenAPI_list_t *serving_client_typesList = NULL;
    cJSON *lmf_id = NULL;
    cJSON *serving_access_types = NULL;
    OpenAPI_list_t *serving_access_typesList = NULL;
    cJSON *serving_an_node_types = NULL;
    OpenAPI_list_t *serving_an_node_typesList = NULL;
    cJSON *serving_rat_types = NULL;
    OpenAPI_list_t *serving_rat_typesList = NULL;
    serving_client_types = cJSON_GetObjectItemCaseSensitive(lmf_infoJSON, "servingClientTypes");
    if (serving_client_types) {
        cJSON *serving_client_types_local = NULL;
        if (!cJSON_IsArray(serving_client_types)) {
            ogs_error("OpenAPI_lmf_info_parseFromJSON() failed [serving_client_types]");
            goto end;
        }

        serving_client_typesList = OpenAPI_list_create();

        cJSON_ArrayForEach(serving_client_types_local, serving_client_types) {
            if (!cJSON_IsObject(serving_client_types_local)) {
                ogs_error("OpenAPI_lmf_info_parseFromJSON() failed [serving_client_types]");
                goto end;
            }
            OpenAPI_external_client_type_t *serving_client_typesItem = OpenAPI_external_client_type_parseFromJSON(serving_client_types_local);
            if (!serving_client_typesItem) {
                ogs_error("No serving_client_typesItem");
                OpenAPI_list_free(serving_client_typesList);
                goto end;
            }
            OpenAPI_list_add(serving_client_typesList, serving_client_typesItem);
        }
    }

    lmf_id = cJSON_GetObjectItemCaseSensitive(lmf_infoJSON, "lmfId");
    if (lmf_id) {
    if (!cJSON_IsString(lmf_id) && !cJSON_IsNull(lmf_id)) {
        ogs_error("OpenAPI_lmf_info_parseFromJSON() failed [lmf_id]");
        goto end;
    }
    }

    serving_access_types = cJSON_GetObjectItemCaseSensitive(lmf_infoJSON, "servingAccessTypes");
    if (serving_access_types) {
        cJSON *serving_access_types_local = NULL;
        if (!cJSON_IsArray(serving_access_types)) {
            ogs_error("OpenAPI_lmf_info_parseFromJSON() failed [serving_access_types]");
            goto end;
        }

        serving_access_typesList = OpenAPI_list_create();

        cJSON_ArrayForEach(serving_access_types_local, serving_access_types) {
            if (!cJSON_IsString(serving_access_types_local)) {
                ogs_error("OpenAPI_lmf_info_parseFromJSON() failed [serving_access_types]");
                goto end;
            }
            OpenAPI_list_add(serving_access_typesList, (void *)OpenAPI_access_type_FromString(serving_access_types_local->valuestring));
        }
    }

    serving_an_node_types = cJSON_GetObjectItemCaseSensitive(lmf_infoJSON, "servingAnNodeTypes");
    if (serving_an_node_types) {
        cJSON *serving_an_node_types_local = NULL;
        if (!cJSON_IsArray(serving_an_node_types)) {
            ogs_error("OpenAPI_lmf_info_parseFromJSON() failed [serving_an_node_types]");
            goto end;
        }

        serving_an_node_typesList = OpenAPI_list_create();

        cJSON_ArrayForEach(serving_an_node_types_local, serving_an_node_types) {
            if (!cJSON_IsString(serving_an_node_types_local)) {
                ogs_error("OpenAPI_lmf_info_parseFromJSON() failed [serving_an_node_types]");
                goto end;
            }
            OpenAPI_list_add(serving_an_node_typesList, (void *)OpenAPI_an_node_type_FromString(serving_an_node_types_local->valuestring));
        }
    }

    serving_rat_types = cJSON_GetObjectItemCaseSensitive(lmf_infoJSON, "servingRatTypes");
    if (serving_rat_types) {
        cJSON *serving_rat_types_local = NULL;
        if (!cJSON_IsArray(serving_rat_types)) {
            ogs_error("OpenAPI_lmf_info_parseFromJSON() failed [serving_rat_types]");
            goto end;
        }

        serving_rat_typesList = OpenAPI_list_create();

        cJSON_ArrayForEach(serving_rat_types_local, serving_rat_types) {
            if (!cJSON_IsString(serving_rat_types_local)) {
                ogs_error("OpenAPI_lmf_info_parseFromJSON() failed [serving_rat_types]");
                goto end;
            }
            OpenAPI_list_add(serving_rat_typesList, (void *)OpenAPI_rat_type_FromString(serving_rat_types_local->valuestring));
        }
    }

    lmf_info_local_var = OpenAPI_lmf_info_create (
        serving_client_types ? serving_client_typesList : NULL,
        lmf_id && !cJSON_IsNull(lmf_id) ? ogs_strdup(lmf_id->valuestring) : NULL,
        serving_access_types ? serving_access_typesList : NULL,
        serving_an_node_types ? serving_an_node_typesList : NULL,
        serving_rat_types ? serving_rat_typesList : NULL
    );

    return lmf_info_local_var;
end:
    if (serving_client_typesList) {
        OpenAPI_list_for_each(serving_client_typesList, node) {
            OpenAPI_external_client_type_free(node->data);
        }
        OpenAPI_list_free(serving_client_typesList);
        serving_client_typesList = NULL;
    }
    if (serving_access_typesList) {
        OpenAPI_list_free(serving_access_typesList);
        serving_access_typesList = NULL;
    }
    if (serving_an_node_typesList) {
        OpenAPI_list_free(serving_an_node_typesList);
        serving_an_node_typesList = NULL;
    }
    if (serving_rat_typesList) {
        OpenAPI_list_free(serving_rat_typesList);
        serving_rat_typesList = NULL;
    }
    return NULL;
}

OpenAPI_lmf_info_t *OpenAPI_lmf_info_copy(OpenAPI_lmf_info_t *dst, OpenAPI_lmf_info_t *src)
{
    cJSON *item = NULL;
    char *content = NULL;

    ogs_assert(src);
    item = OpenAPI_lmf_info_convertToJSON(src);
    if (!item) {
        ogs_error("OpenAPI_lmf_info_convertToJSON() failed");
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

    OpenAPI_lmf_info_free(dst);
    dst = OpenAPI_lmf_info_parseFromJSON(item);
    cJSON_Delete(item);

    return dst;
}

