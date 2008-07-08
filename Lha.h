/*
  headers for Archive::Lha

  Copyright (C) 2007 by Kenichi Ishigaki.

  This program is free software; you can redistribute it and/or
  modify it under the same terms as Perl itself.
*/

#define hash_store(hash, key, value) \
  hv_store(hash, key, strlen(key), value, 0)
#define hash_fetch(hash, key) \
  hv_fetch(hash, key, strlen(key), 0)
#define hash_exists(hash, key) \
  hv_exists(hash, key, strlen(key))
#define self_int(key) \
  SvIV(*hash_fetch(self, key))
#define self_uint(key) \
  (unsigned int)SvIV(*hash_fetch(self, key))
#define self_ushort(key) \
  (unsigned short)SvIV(*hash_fetch(self, key))
#define self_uchar(key) \
  (unsigned char)SvIV(*hash_fetch(self, key))
#define self_ushort_pt(key) \
  (unsigned short *)SvIV(*hash_fetch(self, key))
#define self_uchar_pt(key) \
  (unsigned char *)SvIV(*hash_fetch(self, key))
#define self_sv(key) \
  *hash_fetch(self, key)
#define self_store_n(key, n) \
  hash_store(self, key, newSViv(n))
#define self_store_p(key, n) \
  hash_store(self, key, newSVpv(n, 0))

#define char_bit       8
#define uchar_bit      8
#define ushort_bit    16

#define uchar_max (1 << uchar_bit) - 1
#define ushort_max (1 << ushort_bit) - 1

#define uchar_center  (1 << (uchar_bit - 1))
#define ushort_center (1 << (ushort_bit - 1))

#ifndef min
#define min(a,b) ((a) <= (b) ? (a) : (b))
#endif

#define create_mask(n) \
  (1 << (ushort_bit - 1 - n))

#define readbuf_size 4096

typedef struct LhaTree {
  unsigned short * left;
  unsigned short * right;
} LhaTree;

typedef struct LhaTable {
  unsigned short * table;
  unsigned char  * length;
  unsigned short   size;
  unsigned short   length_size;
  unsigned char    bit;
} LhaTable;

typedef struct LhaBitstream {
  unsigned short value;
  unsigned char  buf;
  unsigned char  pos;
  unsigned short blocksize;
  unsigned char  readbuf[readbuf_size];
  unsigned short readpos;
} LhaBitstream;

typedef struct LhaStash {
  LhaTree       * tree;
  LhaTable      * pt;
  LhaTable      * c;
  LhaBitstream  * bit;
  unsigned char * queue;
  SV            * read;
  SV            * write;
  unsigned short  NPT;
  unsigned short  NP;
  unsigned short  NT;
  unsigned short  NC;
  unsigned char   PBIT;
  unsigned char   TBIT;
  unsigned char   CBIT;
  unsigned int    original_size;
  unsigned int    encoded_size;
} LhaStash;

unsigned short crctable[] = {
      0, 49345, 49537,   320, 49921,   960,   640, 49729,
  50689,  1728,  1920, 51009,  1280, 50625, 50305,  1088,
  52225,  3264,  3456, 52545,  3840, 53185, 52865,  3648,
   2560, 51905, 52097,  2880, 51457,  2496,  2176, 51265,
  55297,  6336,  6528, 55617,  6912, 56257, 55937,  6720,
   7680, 57025, 57217,  8000, 56577,  7616,  7296, 56385,
   5120, 54465, 54657,  5440, 55041,  6080,  5760, 54849,
  53761,  4800,  4992, 54081,  4352, 53697, 53377,  4160,
  61441, 12480, 12672, 61761, 13056, 62401, 62081, 12864,
  13824, 63169, 63361, 14144, 62721, 13760, 13440, 62529,
  15360, 64705, 64897, 15680, 65281, 16320, 16000, 65089,
  64001, 15040, 15232, 64321, 14592, 63937, 63617, 14400,
  10240, 59585, 59777, 10560, 60161, 11200, 10880, 59969,
  60929, 11968, 12160, 61249, 11520, 60865, 60545, 11328,
  58369,  9408,  9600, 58689,  9984, 59329, 59009,  9792,
   8704, 58049, 58241,  9024, 57601,  8640,  8320, 57409,
  40961, 24768, 24960, 41281, 25344, 41921, 41601, 25152,
  26112, 42689, 42881, 26432, 42241, 26048, 25728, 42049,
  27648, 44225, 44417, 27968, 44801, 28608, 28288, 44609,
  43521, 27328, 27520, 43841, 26880, 43457, 43137, 26688,
  30720, 47297, 47489, 31040, 47873, 31680, 31360, 47681,
  48641, 32448, 32640, 48961, 32000, 48577, 48257, 31808,
  46081, 29888, 30080, 46401, 30464, 47041, 46721, 30272,
  29184, 45761, 45953, 29504, 45313, 29120, 28800, 45121,
  20480, 37057, 37249, 20800, 37633, 21440, 21120, 37441,
  38401, 22208, 22400, 38721, 21760, 38337, 38017, 21568,
  39937, 23744, 23936, 40257, 24320, 40897, 40577, 24128,
  23040, 39617, 39809, 23360, 39169, 22976, 22656, 38977,
  34817, 18624, 18816, 35137, 19200, 35777, 35457, 19008,
  19968, 36545, 36737, 20288, 36097, 19904, 19584, 35905,
  17408, 33985, 34177, 17728, 34561, 18368, 18048, 34369,
  33281, 17088, 17280, 33601, 16640, 33217, 32897, 16448,
};
