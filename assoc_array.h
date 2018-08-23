#ifndef _ASSOC_ARRAY
#define _ASSOC_ARRAY

#include <stdlib.h>     //malloc() calloc() free()
#include <stdbool.h>    //bool true false constant
#include <string.h>     //memcpy() memcmp()
#include "inline.h"    //INLINE constant
#include "hash.h"        //hash functions
#include "single_list.h" //linked list library


//structures
//hash table
typedef struct htable {
    unsigned long size;
    unsigned long halfsize;
    unsigned long quartersize;
    unsigned long collisions;
    unsigned long elements;
    list **table;
} htable;


//functions declaration
INLINE htable *init_array(unsigned int power_of_two_size);

INLINE unsigned long array_get(htable *htable, unsigned char *key, unsigned int len);

INLINE list *array_set(htable *htable, unsigned char *key, unsigned int len, unsigned long value);

INLINE bool array_remove(htable *htable, unsigned char *key, unsigned int len);

INLINE unsigned long array_get_(htable *htable, unsigned char *key, unsigned int len);

INLINE list *array_set_(htable *htable, unsigned char *key, unsigned int len, unsigned long value);

INLINE bool array_remove_(htable *htable, unsigned char *key, unsigned int len);



//functions initialization
inline unsigned long array_get(htable *htable, unsigned char *key, unsigned int len) {
    unsigned int key_idx = (crc32(key) & (htable->halfsize - 1)) + (hashphp(key, len) & (htable->halfsize - 1));

    if (htable->table[key_idx] != NULL) {
        list_node *node = list_get(htable->table[key_idx], key, len);
        return node->value;
    }

}


inline list *array_set(htable *htable, unsigned char *key, unsigned int len, unsigned long value) {
    unsigned int key_idx = (crc32(key) & (htable->halfsize - 1)) + (hashphp(key, len) & (htable->halfsize - 1));


    if (htable->table[key_idx] == NULL) {
        htable->table[key_idx] = list_push(NULL, key, len, value);
    } else {
        ++htable->collisions;
        //printf("collision!!! key:%s, key_idx: %i\n", key, key_idx);
        htable->table[key_idx] = list_push(htable->table[key_idx], key, len, value);
    }
    ++htable->elements;
    return htable->table[key_idx];
}


inline bool array_remove(htable *htable, unsigned char *key, unsigned int len) {
    unsigned int key_idx = (crc32(key) & (htable->halfsize - 1)) + (hashphp(key, len) & (htable->halfsize - 1));

    if (htable->table[key_idx] != NULL) {
        switch(list_remove(htable->table[key_idx], key, len)) {
            case 0: //0 means there is no linked list elements left
                htable->table[key_idx] = NULL; /* fallthrough... */
            default:
                --htable->elements;
                return true;
        }
    } else {
        return false;
    }
}


inline unsigned long array_get_(htable *htable, unsigned char *key, unsigned int len) {
    unsigned int key_idx = (hashphp(key, len) & (htable->size - 1));

    if (htable->table[key_idx] != NULL) {
        list_node *node = list_get(htable->table[key_idx], key, len);
        return node->value;
    }

}


inline list *array_set_(htable *htable, unsigned char *key, unsigned int len, unsigned long value) {
    unsigned int key_idx = (hashphp(key, len) & (htable->size - 1));

    if (htable->table[key_idx] == NULL) {
        htable->table[key_idx] = list_push(NULL, key, len, value);
    } else {
        ++htable->collisions;
        //printf("collision!!! key:%s, key_idx: %i\n", key, key_idx);
        htable->table[key_idx] = list_push(htable->table[key_idx], key, len, value);
    }
    ++htable->elements;
    return htable->table[key_idx];
}


inline bool array_remove_(htable *htable, unsigned char *key, unsigned int len) {
    unsigned int key_idx = (hashphp(key, len) & (htable->size - 1));

    if (htable->table[key_idx] != NULL) {
        switch(list_remove(htable->table[key_idx], key, len)) {
            case 0: //0 means there is no linked list elements left
                htable->table[key_idx] = NULL; /* fallthrough... */
            default:
                --htable->elements;
                return true;
        }
    } else {
        return false;
    }
}

inline htable *init_array(unsigned int power_of_two_size) {
    htable *htbl = (htable *) malloc(sizeof(htable));
    list **table = (list **) malloc(sizeof(size_t) * (2 << power_of_two_size));

    htbl->size = 2 << power_of_two_size - 1;
    htbl->halfsize = 2 << (power_of_two_size - 2);
    htbl->quartersize = 2 << (power_of_two_size - 3);
    htbl->collisions = 0;
    htbl->elements = 0;
    htbl->table = table;
    return htbl;
}

#endif /* assoc_array.h  */