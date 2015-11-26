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
    pj_hash_set(table_data->pool, table_data->hash_table, (void *)key, sizeof(key), 0, (void *)value);
    SHOW_LOG(4, "Added key %s - value %d\n", key, *value);
}

int ht_get_item(hash_table_t* table_data, char *key) {
    int *ret;
    ret = (int *)pj_hash_get(table_data->hash_table, (void *)key, sizeof(key), NULL);
    if (ret == NULL)
        return -1;
    else
        return *ret;
}

void ht_remove_item(hash_table_t* table_data, char* key) {
    pj_hash_set(table_data->pool, table_data->hash_table, (void *)key, sizeof(key), 0, NULL);
    SHOW_LOG(4, "Removed key %s\n", key);
}

void ht_list_item(hash_table_t* table_data) {
    pj_hash_iterator_t it_buf,*it;
    unsigned count;
    int *ret;

    count = pj_hash_count(table_data->hash_table);
    SHOW_LOG(4, "Total: %d %s\n", count, (count < 2)?"entry":"entries" );

    it = pj_hash_first(table_data->hash_table, &it_buf);
    while (it) {
        ret = (int *)pj_hash_this(table_data->hash_table, it);
        SHOW_LOG(4, "Entry: %d\n", *ret);
        it = pj_hash_next(table_data->hash_table, it);
    }   
}

