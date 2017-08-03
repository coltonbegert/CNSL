#include <string.h>
#include <stdlib.h>

typedef struct ll_object{
    void * key;
    void * value;
    struct ll_object * next;
} ll_object_t;

typedef struct{
    ll_object_t *ll_object;
    int items;
} hash_map_bucket_t;

typedef struct{
    int num_objects;
    int num_buckets;
    hash_map_bucket_t * bucket;
} hash_map_t;

#ifndef MIN_hash_map_t_SIZE
#define MIN_HASH_MAP_SIZE 256
#endif


hash_map_t *hash_map_create() {
    hash_map_t * new_hash_map = malloc(sizeof(hash_map_t));
    new_hash_map->num_buckets = MIN_HASH_MAP_SIZE;
    new_hash_map->num_objects = 0;
    hash_map_bucket_t * buckets = malloc(new_hash_map->num_buckets*sizeof(hash_map_bucket_t));
    memset(buckets, new_hash_map->num_buckets * sizeof(hash_map_bucket_t), 0);
    return new_hash_map;
}

void hash_map_delete(hash_map_t * hash_map) {
    for (int i = 0; i < hash_map->num_buckets; i++) {
        for (ll_object_t *next_object, *object = hash_map->bucket[i].ll_object; object != NULL;) {
            next_object = object->next;
            free(object->key);
            free(object->value);
            free(object);
            object = next_object;
        }
    }
    free(hash_map->bucket);
}

int main(int argc, char const *argv[]) {
  /* code */
    return 0;
}
