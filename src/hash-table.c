#include "hash-table.h"
#include "my-pjlib-utils.h"
#include "ansi-utils.h"

void ht_init(hash_table_t *table_data, pj_pool_t *pool) {
    EXIT_IF_TRUE(pool == NULL, "Error: NULL pool\n");
    table_data->pool = pool;
}

void ht_create(hash_table_t *table_data, unsigned size) {
    table_data->hash_table = pj_hash_create(table_data->pool, size);
    EXIT_IF_TRUE(table_data->hash_table == NULL, "Error: pj_hash_create()\n");
}

void ht_add_item(hash_table_t* table_data, char *key, int *value) {
    pj_hash_set(table_data->pool, table_data->hash_table, key, strlen(key), 0, (void *) value);
    //SHOW_LOG(4, "******************** Added key %s - value %s\n", (char *)key, (char *)value);
}
void ht_remove_item(hash_table_t* table_data, char* key) {
    pj_hash_set(table_data->pool, table_data->hash_table, key, strlen(key), 0, NULL);
    SHOW_LOG(4, "Removed item %s\n", key);
}

unsigned ht_get_size(hash_table_t *table_data) {
    return pj_hash_count(table_data->hash_table);
}

void ht_list_item(hash_table_t *table_data) {
    pj_hash_iterator_t it_buf,*it;
    unsigned count;
    void *ret;

    count = pj_hash_count(table_data->hash_table);
    SHOW_LOG(1, "Total: %d %s\n", count, (count < 2)?"entry":"entries" );

    it = pj_hash_first(table_data->hash_table, &it_buf);
    while (it) {
        ret = (int *)pj_hash_this(table_data->hash_table, it);
        SHOW_LOG(1, "---Entry: %s\n", (char *)ret);
        it = pj_hash_next(table_data->hash_table, it);
    }   
}

int *ht_get_item(hash_table_t* table_data, char *key) {
    int *p; 
    p = (int *) pj_hash_get(table_data->hash_table, (void *)key, strlen(key), NULL);
    return p;
}


