#include "hash-table.h"
#include "my-pjlib-utils.h"
#include "ansi-utils.h"

#define HASH_COUNT 10

int main() {
    pj_status_t status;
    hash_table_t app_data;
    
    pj_caching_pool cp;
    pj_hash_iterator_t it_buf,*it;

    int key = 9, key2 = 6, f_key = 9 , f_key2 = 10;
    int value = 11, value2 = 22;
    unsigned *entry;

    char *dummy, option[10];
    int f_quit;

    CHECK(__FILE__, pj_init());
    SET_LOG_LEVEL(4);
    pj_log_set_level(3);    

    pj_caching_pool_init(&cp, NULL, 1024);
    app_data.pool = pj_pool_create(&cp.factory, "pool", 1024, 1024, NULL);

    //CREATE HASH TABLE
    ht_create(&app_data, HASH_COUNT);

    //ADD ITEM
    pj_hash_set(app_data.pool, app_data.hash_table, &key2, sizeof(key2), 0, &value2);
    pj_hash_set(app_data.pool, app_data.hash_table, &key, sizeof(key), 0, &value);

    //GET ITEM
    int ret;

    ret = ht_get_item(&app_data, f_key);
    SHOW_LOG(4, "Search for key: %d - Result: entry = %d\n", f_key, ret);

    ret = ht_get_item(&app_data, f_key2);
    SHOW_LOG(4, "Search for key: %d - Result: entry = %d\n", f_key2, ret);

    //LIST ITEM
    ht_list_item(&app_data);

    //REMOVE ITEM
    pj_hash_set(app_data.pool, app_data.hash_table, &key, sizeof(key), 0, NULL);

    SHOW_LOG(3, "-----------------\n");
    //LIST ITEM AGAIN
    ht_list_item(&app_data);
    return 0;
}
