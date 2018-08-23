#ifndef _HASH
#define _HASH

#include <stdio.h> //size_t constant
#include "inline.h"    //INLINE constant


//functions declaration
INLINE unsigned int crc32(unsigned char *msg);

INLINE unsigned int crc32_slow(unsigned char *message);

INLINE unsigned long hashphp(const char *str, size_t len);

INLINE unsigned long murmur3_64(const unsigned char *data, const int len);

INLINE unsigned int murmur3_32(const unsigned char *data, const int len);

INLINE unsigned long time33(char const *str, int len);


/*
  Name:      CRC-32/zlib
  Poly:      0x4C11DB7 (reversed 0xEDB88320) (X^32+X^26+X^23+X^22+X^16+X^12+X^11+X^10+X^8+X^7+X^5+X^4+X^2+X^1+X^0)
  reversed:  true
  init:      0xFFFFFFFF
  xorout:    0xFFFFFFFF
  check:     0xCBF43926

*/

const unsigned int crc32_tab[256] = {
        0x00000000, 0x77073096, 0xee0e612c, 0x990951ba, 0x076dc419, 0x706af48f,
        0xe963a535, 0x9e6495a3, 0x0edb8832, 0x79dcb8a4, 0xe0d5e91e, 0x97d2d988,
        0x09b64c2b, 0x7eb17cbd, 0xe7b82d07, 0x90bf1d91, 0x1db71064, 0x6ab020f2,
        0xf3b97148, 0x84be41de, 0x1adad47d, 0x6ddde4eb, 0xf4d4b551, 0x83d385c7,
        0x136c9856, 0x646ba8c0, 0xfd62f97a, 0x8a65c9ec, 0x14015c4f, 0x63066cd9,
        0xfa0f3d63, 0x8d080df5, 0x3b6e20c8, 0x4c69105e, 0xd56041e4, 0xa2677172,
        0x3c03e4d1, 0x4b04d447, 0xd20d85fd, 0xa50ab56b, 0x35b5a8fa, 0x42b2986c,
        0xdbbbc9d6, 0xacbcf940, 0x32d86ce3, 0x45df5c75, 0xdcd60dcf, 0xabd13d59,
        0x26d930ac, 0x51de003a, 0xc8d75180, 0xbfd06116, 0x21b4f4b5, 0x56b3c423,
        0xcfba9599, 0xb8bda50f, 0x2802b89e, 0x5f058808, 0xc60cd9b2, 0xb10be924,
        0x2f6f7c87, 0x58684c11, 0xc1611dab, 0xb6662d3d, 0x76dc4190, 0x01db7106,
        0x98d220bc, 0xefd5102a, 0x71b18589, 0x06b6b51f, 0x9fbfe4a5, 0xe8b8d433,
        0x7807c9a2, 0x0f00f934, 0x9609a88e, 0xe10e9818, 0x7f6a0dbb, 0x086d3d2d,
        0x91646c97, 0xe6635c01, 0x6b6b51f4, 0x1c6c6162, 0x856530d8, 0xf262004e,
        0x6c0695ed, 0x1b01a57b, 0x8208f4c1, 0xf50fc457, 0x65b0d9c6, 0x12b7e950,
        0x8bbeb8ea, 0xfcb9887c, 0x62dd1ddf, 0x15da2d49, 0x8cd37cf3, 0xfbd44c65,
        0x4db26158, 0x3ab551ce, 0xa3bc0074, 0xd4bb30e2, 0x4adfa541, 0x3dd895d7,
        0xa4d1c46d, 0xd3d6f4fb, 0x4369e96a, 0x346ed9fc, 0xad678846, 0xda60b8d0,
        0x44042d73, 0x33031de5, 0xaa0a4c5f, 0xdd0d7cc9, 0x5005713c, 0x270241aa,
        0xbe0b1010, 0xc90c2086, 0x5768b525, 0x206f85b3, 0xb966d409, 0xce61e49f,
        0x5edef90e, 0x29d9c998, 0xb0d09822, 0xc7d7a8b4, 0x59b33d17, 0x2eb40d81,
        0xb7bd5c3b, 0xc0ba6cad, 0xedb88320, 0x9abfb3b6, 0x03b6e20c, 0x74b1d29a,
        0xead54739, 0x9dd277af, 0x04db2615, 0x73dc1683, 0xe3630b12, 0x94643b84,
        0x0d6d6a3e, 0x7a6a5aa8, 0xe40ecf0b, 0x9309ff9d, 0x0a00ae27, 0x7d079eb1,
        0xf00f9344, 0x8708a3d2, 0x1e01f268, 0x6906c2fe, 0xf762575d, 0x806567cb,
        0x196c3671, 0x6e6b06e7, 0xfed41b76, 0x89d32be0, 0x10da7a5a, 0x67dd4acc,
        0xf9b9df6f, 0x8ebeeff9, 0x17b7be43, 0x60b08ed5, 0xd6d6a3e8, 0xa1d1937e,
        0x38d8c2c4, 0x4fdff252, 0xd1bb67f1, 0xa6bc5767, 0x3fb506dd, 0x48b2364b,
        0xd80d2bda, 0xaf0a1b4c, 0x36034af6, 0x41047a60, 0xdf60efc3, 0xa867df55,
        0x316e8eef, 0x4669be79, 0xcb61b38c, 0xbc66831a, 0x256fd2a0, 0x5268e236,
        0xcc0c7795, 0xbb0b4703, 0x220216b9, 0x5505262f, 0xc5ba3bbe, 0xb2bd0b28,
        0x2bb45a92, 0x5cb36a04, 0xc2d7ffa7, 0xb5d0cf31, 0x2cd99e8b, 0x5bdeae1d,
        0x9b64c2b0, 0xec63f226, 0x756aa39c, 0x026d930a, 0x9c0906a9, 0xeb0e363f,
        0x72076785, 0x05005713, 0x95bf4a82, 0xe2b87a14, 0x7bb12bae, 0x0cb61b38,
        0x92d28e9b, 0xe5d5be0d, 0x7cdcefb7, 0x0bdbdf21, 0x86d3d2d4, 0xf1d4e242,
        0x68ddb3f8, 0x1fda836e, 0x81be16cd, 0xf6b9265b, 0x6fb077e1, 0x18b74777,
        0x88085ae6, 0xff0f6a70, 0x66063bca, 0x11010b5c, 0x8f659eff, 0xf862ae69,
        0x616bffd3, 0x166ccf45, 0xa00ae278, 0xd70dd2ee, 0x4e048354, 0x3903b3c2,
        0xa7672661, 0xd06016f7, 0x4969474d, 0x3e6e77db, 0xaed16a4a, 0xd9d65adc,
        0x40df0b66, 0x37d83bf0, 0xa9bcae53, 0xdebb9ec5, 0x47b2cf7f, 0x30b5ffe9,
        0xbdbdf21c, 0xcabac28a, 0x53b39330, 0x24b4a3a6, 0xbad03605, 0xcdd70693,
        0x54de5729, 0x23d967bf, 0xb3667a2e, 0xc4614ab8, 0x5d681b02, 0x2a6f2b94,
        0xb40bbe37, 0xc30c8ea1, 0x5a05df1b, 0x2d02ef8d
};


inline unsigned int crc32(unsigned char *msg) {
    unsigned char swapped = 1;
    unsigned int crc = 0xffffffff; //init value
    if (swapped) {
        while (*msg) {
            crc = ((crc >> 8) & 0xffffff) ^ crc32_tab[(crc & 0xff) ^ *msg++];
        }
    } else {
        while (*msg) {
            crc = ((crc << 8) & 0xffffff00) ^ crc32_tab[((crc >> 24) & 0xff) ^ *msg++];
        }
    }
    return crc ^ 0xffffffff; //xorout 0xffffffff
}


//without lookup table (slow)
inline unsigned int crc32_slow(unsigned char *message) {
    int i, j;
    unsigned int byte, crc, mask;

    i = 0;
    crc = 0xFFFFFFFF; //init register
    while (message[i] != 0) {
        byte = message[i];            // Get next byte.
        crc = crc ^ byte;
        for (j = 8; j > 0; --j) {    // Do eight times.
            mask = -(crc & 1);
            crc = (crc >> 1) ^ (0xEDB88320 & mask);
        }
        i = i + 1;
    }
    return crc ^ 0xFFFFFFFF; //xorout 0xFFFFFFFF
}


/*
* DJBX33A (Daniel J. Bernstein, Times 33 with Addition)
*/

inline unsigned long hashphp(const char *str, size_t len) {
    unsigned long hash = 5381;

    /* variant with the hash unrolled eight times */
    for (; len >= 8; len -= 8) {
        hash = ((hash << 5) + hash) + *str++;
        hash = ((hash << 5) + hash) + *str++;
        hash = ((hash << 5) + hash) + *str++;
        hash = ((hash << 5) + hash) + *str++;
        hash = ((hash << 5) + hash) + *str++;
        hash = ((hash << 5) + hash) + *str++;
        hash = ((hash << 5) + hash) + *str++;
        hash = ((hash << 5) + hash) + *str++;
    }
    switch (len) {
        case 7:
            hash = ((hash << 5) + hash) + *str++; /* fallthrough... */
        case 6:
            hash = ((hash << 5) + hash) + *str++; /* fallthrough... */
        case 5:
            hash = ((hash << 5) + hash) + *str++; /* fallthrough... */
        case 4:
            hash = ((hash << 5) + hash) + *str++; /* fallthrough... */
        case 3:
            hash = ((hash << 5) + hash) + *str++; /* fallthrough... */
        case 2:
            hash = ((hash << 5) + hash) + *str++; /* fallthrough... */
        case 1:
            hash = ((hash << 5) + hash) + *str++;
            break;
        case 0:
            break;
        default:;
            break;
    }

    return hash;
}


//-----------------------------------------------------------------------------
// Block read - if your platform needs to do endian-swapping or can only
// handle aligned reads, do the conversion here

#define getblock(p, i) (p[i])

static inline unsigned int rotl32 ( unsigned int x, char r )
{
return (x << r) | (x >> (32 - r));
}

static inline unsigned long rotl64 ( unsigned long x, char r )
{
return (x << r) | (x >> (64 - r));
}

//-----------------------------------------------------------------------------
// Finalization mix - force all bits of a hash block to avalanche

static inline unsigned int fmix32 ( unsigned int h )
{
h ^= h >> 16;
h *= 0x85ebca6b;
h ^= h >> 13;
h *= 0xc2b2ae35;
h ^= h >> 16;

return h;
}

//----------

static inline unsigned long fmix64 ( unsigned long k )
{
k ^= k >> 33;
k *= 0xff51afd7ed558ccd;
k ^= k >> 33;
k *= 0xc4ceb9fe1a85ec53;
k ^= k >> 33;

return k;
}

inline unsigned long murmur3_64(const unsigned char *data, const int len) {

    const int nblocks = len / 16;
    int i;
    unsigned long seed = 0; //in the original murmur3 this value is passed as argument

    unsigned long h1 = seed;
    unsigned long h2 = seed;

    unsigned long c1 = 0x87c37b91114253d5;
    unsigned long c2 = 0x4cf5ad432745937f;

    //----------
    // body

    const unsigned long * blocks = (const unsigned long *)(data);

    for(i = 0; i < nblocks; i++)
    {
        unsigned long k1 = getblock(blocks,i*2+0);
        unsigned long k2 = getblock(blocks,i*2+1);

        k1 *= c1; k1  = rotl64(k1,31); k1 *= c2; h1 ^= k1;

        h1 = rotl64(h1,27); h1 += h2; h1 = h1*5+0x52dce729;

        k2 *= c2; k2  = rotl64(k2,33); k2 *= c1; h2 ^= k2;

        h2 = rotl64(h2,31); h2 += h1; h2 = h2*5+0x38495ab5;
    }

    //----------
    // tail

    const unsigned char * tail = (const unsigned char*)(data + nblocks*16);

    unsigned long k1 = 0;
    unsigned long k2 = 0;

    switch(len & 15)
    {
        case 15: k2 ^= (unsigned long)(tail[14]) << 48;
        case 14: k2 ^= (unsigned long)(tail[13]) << 40;
        case 13: k2 ^= (unsigned long)(tail[12]) << 32;
        case 12: k2 ^= (unsigned long)(tail[11]) << 24;
        case 11: k2 ^= (unsigned long)(tail[10]) << 16;
        case 10: k2 ^= (unsigned long)(tail[ 9]) << 8;
        case  9: k2 ^= (unsigned long)(tail[ 8]) << 0;
            k2 *= c2; k2  = rotl64(k2,33); k2 *= c1; h2 ^= k2;

        case  8: k1 ^= (unsigned long)(tail[ 7]) << 56;
        case  7: k1 ^= (unsigned long)(tail[ 6]) << 48;
        case  6: k1 ^= (unsigned long)(tail[ 5]) << 40;
        case  5: k1 ^= (unsigned long)(tail[ 4]) << 32;
        case  4: k1 ^= (unsigned long)(tail[ 3]) << 24;
        case  3: k1 ^= (unsigned long)(tail[ 2]) << 16;
        case  2: k1 ^= (unsigned long)(tail[ 1]) << 8;
        case  1: k1 ^= (unsigned long)(tail[ 0]) << 0;
            k1 *= c1; k1  = rotl64(k1,31); k1 *= c2; h1 ^= k1;
    };

    //----------
    // finalization

    h1 ^= len; h2 ^= len;

    h1 += h2;
    h2 += h1;

    h1 = fmix64(h1);
    h2 = fmix64(h2);

    h1 += h2;
    h2 += h1;

    return h1;

}

inline unsigned int murmur3_32 (const unsigned char *data, const int len) {
    const int nblocks = len / 4;
    int i;
    unsigned int seed = 0;

    unsigned int h1 = seed;

    unsigned int c1 = 0xcc9e2d51;
    unsigned int c2 = 0x1b873593;

    //----------
    // body

    const unsigned int * blocks = (const unsigned int *)(data + nblocks*4);

    for(i = -nblocks; i; i++)
    {
        unsigned int k1 = getblock(blocks,i);

        k1 *= c1;
        k1 = rotl32(k1,15);
        k1 *= c2;

        h1 ^= k1;
        h1 = rotl32(h1,13);
        h1 = h1*5+0xe6546b64;
    }

    //----------
    // tail

    const unsigned char * tail = (const unsigned char*)(data + nblocks*4);

    unsigned int k1 = 0;

    switch(len & 3)
    {
        case 3: k1 ^= tail[2] << 16;
        case 2: k1 ^= tail[1] << 8;
        case 1: k1 ^= tail[0];
            k1 *= c1; k1 = rotl32(k1,15); k1 *= c2; h1 ^= k1;
    };

    //----------
    // finalization

    h1 ^= len;

    h1 = fmix32(h1);

    return h1;
}


inline unsigned long time33(char const *str, int len)
{
    unsigned long  hash = 0;
    for (int i = 0; i < len; i++) {
        hash = ((hash <<5) + hash) + (unsigned long) str[i];
    }
    return hash;
}


#endif /* hash.h */