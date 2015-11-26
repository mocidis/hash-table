#ifndef __HASH_TABLE__
#define __HASH_TABLE__

#include "stdio.h"
#include "stdlib.h"
#include "pjlib.h"

typedef struct data_s data_t;

struct data_s {
    char value[20];
};

typedef struct hash_table_s {
    pj_pool_t *pool;

    pj_hash_table_t* hash_table;
}hash_table_t;

void ht_init(hash_table_t * table_data, pj_pool_t *pool);
void ht_create(hash_table_t* table_data, unsigned size );
void ht_add_item(hash_table_t* table_data, char *key, int *value);
int ht_get_item(hash_table_t* table_data, char *key);
void ht_remove_item(hash_table_t* table_data, char *key);
#endif
