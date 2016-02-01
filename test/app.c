#include "hash-table.h"
#include "my-pjlib-utils.h"
#include "ansi-utils.h"

#define HASH_COUNT 10

int main() {
    pj_status_t status;
    hash_table_t app_data;
    
    pj_caching_pool cp;
    pj_pool_t *pool;
    pj_hash_iterator_t it_buf,*it;

    //int key = 999, key2 = 666, f_key = 999 , f_key2 = 10;
    char key[10] = "OIUC1", key2[10] = "OIUC2", f_key[10] = "aaaa", f_key2[10] = "OIUC9";
    int value = 11, value2 = 22, value3 = 33;
    unsigned *entry;

    char *dummy, option[10];
    int f_quit;
    int ret;

    CHECK(__FILE__, pj_init());
    SET_LOG_LEVEL(4);
    pj_log_set_level(3);    

    pj_caching_pool_init(&cp, NULL, 1024);

    pool = pj_pool_create(&cp.factory, "pool", 1024, 1024, NULL);

    //INIT HASH TABLE
    ht_init(&app_data, pool);

    //CREATE HASH TABLE
    ht_create(&app_data, HASH_COUNT);

    //ADD ITEM
    ht_add_item(&app_data, key, &value);
    //ht_add_item(&app_data, key2, &value2);
    //GET ITEM
    ret = ht_get_item(&app_data, f_key);
    SHOW_LOG(4, "Search for key: %s - Result: entry = %d\n", f_key, ret);
    ret = ht_get_item(&app_data, f_key2);
    SHOW_LOG(4, "Search for key: %s - Result: entry = %d\n", f_key2, ret);
    //LIST ITEM
    ht_list_item(&app_data);

    ht_add_item(&app_data, key, &value3);
    //LIST ITEM
    SHOW_LOG(3, "Try to update key1");
    ht_list_item(&app_data);

    //REMOVE ITEM
    ht_remove_item(&app_data, key);
    ht_remove_item(&app_data, f_key2);

    SHOW_LOG(3, "-----------------\n");
    //LIST ITEM AGAIN
    ht_list_item(&app_data);

    return 0;
}
