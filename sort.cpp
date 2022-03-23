#include <emmintrin.h>
#include <immintrin.h>
#include <iostream>

using namespace std;

void out(__m256i in) {
  int b[8];
  _mm256_storeu_si256((__m256i_u*)b, in);
  for (int i =0; i < 4; ++i)cout << b[i]  << " ";
  cout << endl;
}

void mergesort(int* l, int* r, int* s) {
  //level1
  __m256i l1 = _mm256_set_epi32(0, 0, 0, 0, l[3], l[2], l[1], l[0]);
  __m256i r1 = _mm256_set_epi32(0, 0, 0, 0, r[0], r[1], r[2], r[3]);

  __m256i min1 = _mm256_min_epi32(l1, r1);
  __m256i max1 = _mm256_max_epi32(l1, r1);

  __m256i l2 = _mm256_blend_epi32(min1, max1, (int)0b00001100);
  __m256i r2 = _mm256_blend_epi32(min1, max1, (int)0b00000011);
  r2 = _mm256_shuffle_epi32(r2, (int)0b01001110);

  //level2
  __m256i max2 = _mm256_max_epi32(l2, r2);
  __m256i min2 = _mm256_min_epi32(l2, r2);

  __m256i l3 = _mm256_blend_epi32(min2, max2, (int)0b00001010);
  __m256i r3 = _mm256_blend_epi32(min2, max2, (int)0b00000101);
  r3 = _mm256_shuffle_epi32(r3, (int)0b10110001);

  //level3
  __m256i max3 = _mm256_max_epi32(l3, r3);
  __m256i min3 = _mm256_min_epi32(l3, r3);

  __m256i s1 = _mm256_shuffle_epi32(min3, (int)0b11011000);
  __m256i s2 = _mm256_shuffle_epi32(max3, (int)0b01110010);

  __m256i first4 = _mm256_blend_epi32(s1, s2, (int)0b00001010);
  __m256i second4 = _mm256_blend_epi32(s1, s2, (int)0b00000101);
  second4 = _mm256_shuffle_epi32(second4, (int)0b10110001);

  _mm256_storeu_si256((__m256i_u*)s, first4);
  _mm256_storeu_si256((__m256i_u*)(s+4), second4);
}

int main() {
  int l[] = {1, 9, 10, 18};
  int r[] = {2, 5, 7, 20};
  int s[8] = {0, 0, 0, 0, 0, 0, 0, 0};
  mergesort(l, r, s);
  for(int i = 0; i < 8; ++i)cout << s[i] << endl;

  return 0;
}