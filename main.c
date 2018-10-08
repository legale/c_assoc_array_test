#include "time.h" //clock()
#include "assoc_array.h" //array_set() array_get() array_init()


void test(htable *array, unsigned char mode_flag, bool hash_flag) {
    for (int i = 0, j = 45, k = 45, n = 45, m = 45; i < array->size / 2 ; ++i) { //a ascii code is 97
        if (j > 122) { //z ascii code is 122
            exit(2);
            j = 45;
            m++;
        }
        if (k > 122) {
            k = 45;
            j++;
        }
        if (n > 122) {
            n = 45;
            k++;
        }
        if (m > 122) {
            m = 45;
            n++;
        }
        unsigned char string[5] = {j, k, n, m, 0};

        if (!hash_flag) {
            switch(mode_flag) {
                case 1:
                    array_set(array, string, sizeof(string), n + m);
                    break;
                case 2:
                    array_get(array, string, sizeof(string)) != n + m ? printf("ops! key not found: %s\n", string) : 0;
                    break;
                case 3:
                    array_remove(array, string, sizeof(string));
                    break;
                default:
                    return;
            }
        } else {
            switch(mode_flag) {
                case 1:
                    array_set_(array, string, sizeof(string), n + m);
                    break;
                case 2:
                    array_get_(array, string, sizeof(string)) != n + m ? printf("ops! key not found: %s\n", string) : 0;
                    break;
                case 3:
                    array_remove_(array, string, sizeof(string));
                    break;
                default:
                    return;
            }
        }
        m++;
    }
}

#define CYCLES 10

int main(){

    htable *array;
    array = init_array(20);

    clock_t begin, end;
    begin = clock();
    for(int i = 0; i < CYCLES; ++i) {

       test(array, 1, false); //write
       test(array, 2, false);//read
       test(array, 3, false);//remove
    }
    end = clock();

    printf("array DJBX33A hash:   %u s\n", (unsigned int) (end - begin) / 1000000); //s
    printf("array size:              %i\n", (unsigned int)array->size );
    printf("array load factor:       %f\n", (float)array->elements /  array->size);
    printf("collision factor:        %f\n", (float) array->collisions / array->halfsize);
    printf("array collisions:        %i\n", (unsigned int)array->collisions );


    printf("\n\n");

    htable *array2;
    array2 = init_array_(20);

    begin = clock();
    for(int i = 0; i < CYCLES ; ++i) {

        test(array2, 1, true); //write
        test(array2, 2, true);//read
        test(array2, 3, true);//remove
    }
    end = clock();
    printf("array crc32 + DJBX33A hash:     %u s\n", (unsigned int) (end - begin) / 1000000); //s
    printf("array size:              %i\n", (unsigned int)array2->size );
    printf("array load factor:       %f\n", (float)array2->elements /  array2->size);
    printf("collision factor:        %f\n", (float) array2->collisions / array2->halfsize);
    printf("collision:               %i\n", (int) array2->collisions);

}