// Copyright 2016 Adrien Descamps
// Distributed under BSD 3-Clause License

/* You need to define the following macros before including this file:
	SSE_FUNCTION_NAME
	STD_FUNCTION_NAME
	YUV_FORMAT
	RGB_FORMAT
*/
/* You may define the following macro, which affects generated code:
	SSE_ALIGNED
*/

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SSE_ALIGNED
/* Unaligned instructions seem faster, even on aligned data? */
/*
#define LOAD_SI128 _mm_load_si128
#define SAVE_SI128 _mm_stream_si128
*/
#ವ್ಯಾಖ್ಯಾನಿಸು ತುಂಬು_SI128 _mm_loadu_si128
#ವ್ಯಾಖ್ಯಾನಿಸು SAVE_SI128 _mm_storeu_si128
#ಇಲ್ಲದಿದ್ದರೆ
#ವ್ಯಾಖ್ಯಾನಿಸು ತುಂಬು_SI128 _mm_loadu_si128
#ವ್ಯಾಖ್ಯಾನಿಸು SAVE_SI128 _mm_storeu_si128
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿಸು UV2RGB_16(U,V,R1,G1,B1,R2,G2,B2) \
	r_tmp = _mm_mullo_epi16(V, _mm_set1_epi16(param->v_r_ಗುಣಕ)); \
	g_tmp = mm_ಕೂಡಿಸು_epi16( \
		_mm_mullo_epi16(U, _mm_set1_epi16(param->u_g_ಗುಣಕ)), \
		_mm_mullo_epi16(V, _mm_set1_epi16(param->v_g_ಗುಣಕ))); \
	b_tmp = _mm_mullo_epi16(U, _mm_set1_epi16(param->u_b_ಗುಣಕ)); \
	R1 = _mm_unpacklo_epi16(r_tmp, r_tmp); \
	G1 = _mm_unpacklo_epi16(g_tmp, g_tmp); \
	B1 = _mm_unpacklo_epi16(b_tmp, b_tmp); \
	R2 = _mm_unpackhi_epi16(r_tmp, r_tmp); \
	G2 = _mm_unpackhi_epi16(g_tmp, g_tmp); \
	B2 = _mm_unpackhi_epi16(b_tmp, b_tmp); \

#ವ್ಯಾಖ್ಯಾನಿಸು ಕೂಡಿಸು_Y2_RGB_16(Y1,Y2,R1,G1,B1,R2,G2,B2) \
	Y1 = _mm_mullo_epi16(_mm_sub_epi16(Y1, _mm_set1_epi16(param->y_ಸರಿಸು)), _mm_set1_epi16(param->y_ಗುಣಕ)); \
	Y2 = _mm_mullo_epi16(_mm_sub_epi16(Y2, _mm_set1_epi16(param->y_ಸರಿಸು)), _mm_set1_epi16(param->y_ಗುಣಕ)); \
	\
	R1 = _mm_srai_epi16(mm_ಕೂಡಿಸು_epi16(R1, Y1), PRECISION); \
	G1 = _mm_srai_epi16(mm_ಕೂಡಿಸು_epi16(G1, Y1), PRECISION); \
	B1 = _mm_srai_epi16(mm_ಕೂಡಿಸು_epi16(B1, Y1), PRECISION); \
	R2 = _mm_srai_epi16(mm_ಕೂಡಿಸು_epi16(R2, Y2), PRECISION); \
	G2 = _mm_srai_epi16(mm_ಕೂಡಿಸು_epi16(G2, Y2), PRECISION); \
	B2 = _mm_srai_epi16(mm_ಕೂಡಿಸು_epi16(B2, Y2), PRECISION); \

#ವ್ಯಾಖ್ಯಾನಿಸು PACK_RGB565_32(R1, R2, G1, G2, B1, B2, RGB1, RGB2, RGB3, RGB4) \
{ \
	__m128i red_ಮುಖವಾಡ, tmp1, tmp2, tmp3, tmp4; \
\
	red_ಮುಖವಾಡ = _mm_set1_epi16((ಚಿಹ್ನೆರಹಿತ ಗಿಡ್ಡ)0xF800); \
	RGB1 = _mm_and_si128(_mm_unpacklo_epi8(_mm_setzero_si128(), R1), red_ಮುಖವಾಡ); \
	RGB2 = _mm_and_si128(_mm_unpackhi_epi8(_mm_setzero_si128(), R1), red_ಮುಖವಾಡ); \
	RGB3 = _mm_and_si128(_mm_unpacklo_epi8(_mm_setzero_si128(), R2), red_ಮುಖವಾಡ); \
	RGB4 = _mm_and_si128(_mm_unpackhi_epi8(_mm_setzero_si128(), R2), red_ಮುಖವಾಡ); \
	tmp1 = _mm_slli_epi16(_mm_srli_epi16(_mm_unpacklo_epi8(G1, _mm_setzero_si128()), 2), 5); \
	tmp2 = _mm_slli_epi16(_mm_srli_epi16(_mm_unpackhi_epi8(G1, _mm_setzero_si128()), 2), 5); \
	tmp3 = _mm_slli_epi16(_mm_srli_epi16(_mm_unpacklo_epi8(G2, _mm_setzero_si128()), 2), 5); \
	tmp4 = _mm_slli_epi16(_mm_srli_epi16(_mm_unpackhi_epi8(G2, _mm_setzero_si128()), 2), 5); \
	RGB1 = _mm_or_si128(RGB1, tmp1); \
	RGB2 = _mm_or_si128(RGB2, tmp2); \
	RGB3 = _mm_or_si128(RGB3, tmp3); \
	RGB4 = _mm_or_si128(RGB4, tmp4); \
	tmp1 = _mm_srli_epi16(_mm_unpacklo_epi8(B1, _mm_setzero_si128()), 3); \
	tmp2 = _mm_srli_epi16(_mm_unpackhi_epi8(B1, _mm_setzero_si128()), 3); \
	tmp3 = _mm_srli_epi16(_mm_unpacklo_epi8(B2, _mm_setzero_si128()), 3); \
	tmp4 = _mm_srli_epi16(_mm_unpackhi_epi8(B2, _mm_setzero_si128()), 3); \
	RGB1 = _mm_or_si128(RGB1, tmp1); \
	RGB2 = _mm_or_si128(RGB2, tmp2); \
	RGB3 = _mm_or_si128(RGB3, tmp3); \
	RGB4 = _mm_or_si128(RGB4, tmp4); \
}

#ವ್ಯಾಖ್ಯಾನಿಸು PACK_RGB24_32_STEP1(R1, R2, G1, G2, B1, B2, RGB1, RGB2, RGB3, RGB4, RGB5, RGB6) \
RGB1 = _mm_packus_epi16(_mm_and_si128(R1,_mm_set1_epi16(0xFF)), _mm_and_si128(R2,_mm_set1_epi16(0xFF))); \
RGB2 = _mm_packus_epi16(_mm_and_si128(G1,_mm_set1_epi16(0xFF)), _mm_and_si128(G2,_mm_set1_epi16(0xFF))); \
RGB3 = _mm_packus_epi16(_mm_and_si128(B1,_mm_set1_epi16(0xFF)), _mm_and_si128(B2,_mm_set1_epi16(0xFF))); \
RGB4 = _mm_packus_epi16(_mm_srli_epi16(R1,8), _mm_srli_epi16(R2,8)); \
RGB5 = _mm_packus_epi16(_mm_srli_epi16(G1,8), _mm_srli_epi16(G2,8)); \
RGB6 = _mm_packus_epi16(_mm_srli_epi16(B1,8), _mm_srli_epi16(B2,8)); \

#ವ್ಯಾಖ್ಯಾನಿಸು PACK_RGB24_32_STEP2(R1, R2, G1, G2, B1, B2, RGB1, RGB2, RGB3, RGB4, RGB5, RGB6) \
R1 = _mm_packus_epi16(_mm_and_si128(RGB1,_mm_set1_epi16(0xFF)), _mm_and_si128(RGB2,_mm_set1_epi16(0xFF))); \
R2 = _mm_packus_epi16(_mm_and_si128(RGB3,_mm_set1_epi16(0xFF)), _mm_and_si128(RGB4,_mm_set1_epi16(0xFF))); \
G1 = _mm_packus_epi16(_mm_and_si128(RGB5,_mm_set1_epi16(0xFF)), _mm_and_si128(RGB6,_mm_set1_epi16(0xFF))); \
G2 = _mm_packus_epi16(_mm_srli_epi16(RGB1,8), _mm_srli_epi16(RGB2,8)); \
B1 = _mm_packus_epi16(_mm_srli_epi16(RGB3,8), _mm_srli_epi16(RGB4,8)); \
B2 = _mm_packus_epi16(_mm_srli_epi16(RGB5,8), _mm_srli_epi16(RGB6,8)); \

#ವ್ಯಾಖ್ಯಾನಿಸು PACK_RGB24_32(R1, R2, G1, G2, B1, B2, RGB1, RGB2, RGB3, RGB4, RGB5, RGB6) \
PACK_RGB24_32_STEP1(R1, R2, G1, G2, B1, B2, RGB1, RGB2, RGB3, RGB4, RGB5, RGB6) \
PACK_RGB24_32_STEP2(R1, R2, G1, G2, B1, B2, RGB1, RGB2, RGB3, RGB4, RGB5, RGB6) \
PACK_RGB24_32_STEP1(R1, R2, G1, G2, B1, B2, RGB1, RGB2, RGB3, RGB4, RGB5, RGB6) \
PACK_RGB24_32_STEP2(R1, R2, G1, G2, B1, B2, RGB1, RGB2, RGB3, RGB4, RGB5, RGB6) \
PACK_RGB24_32_STEP1(R1, R2, G1, G2, B1, B2, RGB1, RGB2, RGB3, RGB4, RGB5, RGB6) \

#ವ್ಯಾಖ್ಯಾನಿಸು PACK_RGBA_32(R1, R2, G1, G2, B1, B2, A1, A2, RGB1, RGB2, RGB3, RGB4, RGB5, RGB6, RGB7, RGB8) \
{ \
	__m128i lo_ab, hi_ab, lo_gr, hi_gr; \
\
	lo_ab = _mm_unpacklo_epi8( A1, B1 ); \
	hi_ab = _mm_unpackhi_epi8( A1, B1 ); \
	lo_gr = _mm_unpacklo_epi8( G1, R1 ); \
	hi_gr = _mm_unpackhi_epi8( G1, R1 ); \
	RGB1 = _mm_unpacklo_epi16( lo_ab, lo_gr ); \
	RGB2 = _mm_unpackhi_epi16( lo_ab, lo_gr ); \
	RGB3 = _mm_unpacklo_epi16( hi_ab, hi_gr ); \
	RGB4 = _mm_unpackhi_epi16( hi_ab, hi_gr ); \
\
	lo_ab = _mm_unpacklo_epi8( A2, B2 ); \
	hi_ab = _mm_unpackhi_epi8( A2, B2 ); \
	lo_gr = _mm_unpacklo_epi8( G2, R2 ); \
	hi_gr = _mm_unpackhi_epi8( G2, R2 ); \
	RGB5 = _mm_unpacklo_epi16( lo_ab, lo_gr ); \
	RGB6 = _mm_unpackhi_epi16( lo_ab, lo_gr ); \
	RGB7 = _mm_unpacklo_epi16( hi_ab, hi_gr ); \
	RGB8 = _mm_unpackhi_epi16( hi_ab, hi_gr ); \
}

#ಆದರೆ RGB_FORMAT == RGB_FORMAT_RGB565

#ವ್ಯಾಖ್ಯಾನಿಸು PACK_PIXEL \
	__m128i rgb_1, rgb_2, rgb_3, rgb_4, rgb_5, rgb_6, rgb_7, rgb_8; \
	\
	PACK_RGB565_32(r_8_11, r_8_12, g_8_11, g_8_12, b_8_11, b_8_12, rgb_1, rgb_2, rgb_3, rgb_4) \
	\
	PACK_RGB565_32(r_8_21, r_8_22, g_8_21, g_8_22, b_8_21, b_8_22, rgb_5, rgb_6, rgb_7, rgb_8) \

#ಅಥವಾಆದರೆ RGB_FORMAT == RGB_FORMAT_RGB24

#ವ್ಯಾಖ್ಯಾನಿಸು PACK_PIXEL \
	__m128i rgb_1, rgb_2, rgb_3, rgb_4, rgb_5, rgb_6; \
	__m128i rgb_7, rgb_8, rgb_9, rgb_10, rgb_11, rgb_12; \
	\
	PACK_RGB24_32(r_8_11, r_8_12, g_8_11, g_8_12, b_8_11, b_8_12, rgb_1, rgb_2, rgb_3, rgb_4, rgb_5, rgb_6) \
	\
	PACK_RGB24_32(r_8_21, r_8_22, g_8_21, g_8_22, b_8_21, b_8_22, rgb_7, rgb_8, rgb_9, rgb_10, rgb_11, rgb_12) \

#ಅಥವಾಆದರೆ RGB_FORMAT == RGB_FORMAT_RGBA

#ವ್ಯಾಖ್ಯಾನಿಸು PACK_PIXEL \
	__m128i rgb_1, rgb_2, rgb_3, rgb_4, rgb_5, rgb_6, rgb_7, rgb_8; \
	__m128i rgb_9, rgb_10, rgb_11, rgb_12, rgb_13, rgb_14, rgb_15, rgb_16; \
	__m128i a = _mm_set1_epi8((ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ)0xFF); \
	\
	PACK_RGBA_32(r_8_11, r_8_12, g_8_11, g_8_12, b_8_11, b_8_12, a, a, rgb_1, rgb_2, rgb_3, rgb_4, rgb_5, rgb_6, rgb_7, rgb_8) \
	\
	PACK_RGBA_32(r_8_21, r_8_22, g_8_21, g_8_22, b_8_21, b_8_22, a, a, rgb_9, rgb_10, rgb_11, rgb_12, rgb_13, rgb_14, rgb_15, rgb_16) \

#ಅಥವಾಆದರೆ RGB_FORMAT == RGB_FORMAT_BGRA

#ವ್ಯಾಖ್ಯಾನಿಸು PACK_PIXEL \
	__m128i rgb_1, rgb_2, rgb_3, rgb_4, rgb_5, rgb_6, rgb_7, rgb_8; \
	__m128i rgb_9, rgb_10, rgb_11, rgb_12, rgb_13, rgb_14, rgb_15, rgb_16; \
	__m128i a = _mm_set1_epi8((ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ)0xFF); \
	\
	PACK_RGBA_32(b_8_11, b_8_12, g_8_11, g_8_12, r_8_11, r_8_12, a, a, rgb_1, rgb_2, rgb_3, rgb_4, rgb_5, rgb_6, rgb_7, rgb_8) \
	\
	PACK_RGBA_32(b_8_21, b_8_22, g_8_21, g_8_22, r_8_21, r_8_22, a, a, rgb_9, rgb_10, rgb_11, rgb_12, rgb_13, rgb_14, rgb_15, rgb_16) \

#ಅಥವಾಆದರೆ RGB_FORMAT == RGB_FORMAT_ARGB

#ವ್ಯಾಖ್ಯಾನಿಸು PACK_PIXEL \
	__m128i rgb_1, rgb_2, rgb_3, rgb_4, rgb_5, rgb_6, rgb_7, rgb_8; \
	__m128i rgb_9, rgb_10, rgb_11, rgb_12, rgb_13, rgb_14, rgb_15, rgb_16; \
	__m128i a = _mm_set1_epi8((ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ)0xFF); \
	\
	PACK_RGBA_32(a, a, r_8_11, r_8_12, g_8_11, g_8_12, b_8_11, b_8_12, rgb_1, rgb_2, rgb_3, rgb_4, rgb_5, rgb_6, rgb_7, rgb_8) \
	\
	PACK_RGBA_32(a, a, r_8_21, r_8_22, g_8_21, g_8_22, b_8_21, b_8_22, rgb_9, rgb_10, rgb_11, rgb_12, rgb_13, rgb_14, rgb_15, rgb_16) \

#ಅಥವಾಆದರೆ RGB_FORMAT == RGB_FORMAT_ABGR

#ವ್ಯಾಖ್ಯಾನಿಸು PACK_PIXEL \
	__m128i rgb_1, rgb_2, rgb_3, rgb_4, rgb_5, rgb_6, rgb_7, rgb_8; \
	__m128i rgb_9, rgb_10, rgb_11, rgb_12, rgb_13, rgb_14, rgb_15, rgb_16; \
	__m128i a = _mm_set1_epi8((ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ)0xFF); \
	\
	PACK_RGBA_32(a, a, b_8_11, b_8_12, g_8_11, g_8_12, r_8_11, r_8_12, rgb_1, rgb_2, rgb_3, rgb_4, rgb_5, rgb_6, rgb_7, rgb_8) \
	\
	PACK_RGBA_32(a, a, b_8_21, b_8_22, g_8_21, g_8_22, r_8_21, r_8_22, rgb_9, rgb_10, rgb_11, rgb_12, rgb_13, rgb_14, rgb_15, rgb_16) \

#ಇಲ್ಲದಿದ್ದರೆ
#ದೋಷ PACK_PIXEL unimplemented
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ RGB_FORMAT == RGB_FORMAT_RGB565

#ವ್ಯಾಖ್ಯಾನಿಸು SAVE_LINE1 \
	SAVE_SI128((__m128i*)(rgb_ptr1), rgb_1); \
	SAVE_SI128((__m128i*)(rgb_ptr1+16), rgb_2); \
	SAVE_SI128((__m128i*)(rgb_ptr1+32), rgb_3); \
	SAVE_SI128((__m128i*)(rgb_ptr1+48), rgb_4); \

#ವ್ಯಾಖ್ಯಾನಿಸು SAVE_LINE2 \
	SAVE_SI128((__m128i*)(rgb_ptr2), rgb_5); \
	SAVE_SI128((__m128i*)(rgb_ptr2+16), rgb_6); \
	SAVE_SI128((__m128i*)(rgb_ptr2+32), rgb_7); \
	SAVE_SI128((__m128i*)(rgb_ptr2+48), rgb_8); \

#ಅಥವಾಆದರೆ RGB_FORMAT == RGB_FORMAT_RGB24

#ವ್ಯಾಖ್ಯಾನಿಸು SAVE_LINE1 \
	SAVE_SI128((__m128i*)(rgb_ptr1), rgb_1); \
	SAVE_SI128((__m128i*)(rgb_ptr1+16), rgb_2); \
	SAVE_SI128((__m128i*)(rgb_ptr1+32), rgb_3); \
	SAVE_SI128((__m128i*)(rgb_ptr1+48), rgb_4); \
	SAVE_SI128((__m128i*)(rgb_ptr1+64), rgb_5); \
	SAVE_SI128((__m128i*)(rgb_ptr1+80), rgb_6); \

#ವ್ಯಾಖ್ಯಾನಿಸು SAVE_LINE2 \
	SAVE_SI128((__m128i*)(rgb_ptr2), rgb_7); \
	SAVE_SI128((__m128i*)(rgb_ptr2+16), rgb_8); \
	SAVE_SI128((__m128i*)(rgb_ptr2+32), rgb_9); \
	SAVE_SI128((__m128i*)(rgb_ptr2+48), rgb_10); \
	SAVE_SI128((__m128i*)(rgb_ptr2+64), rgb_11); \
	SAVE_SI128((__m128i*)(rgb_ptr2+80), rgb_12); \

#ಅಥವಾಆದರೆ RGB_FORMAT == RGB_FORMAT_RGBA || RGB_FORMAT == RGB_FORMAT_BGRA || \
      RGB_FORMAT == RGB_FORMAT_ARGB || RGB_FORMAT == RGB_FORMAT_ABGR

#ವ್ಯಾಖ್ಯಾನಿಸು SAVE_LINE1 \
	SAVE_SI128((__m128i*)(rgb_ptr1), rgb_1); \
	SAVE_SI128((__m128i*)(rgb_ptr1+16), rgb_2); \
	SAVE_SI128((__m128i*)(rgb_ptr1+32), rgb_3); \
	SAVE_SI128((__m128i*)(rgb_ptr1+48), rgb_4); \
	SAVE_SI128((__m128i*)(rgb_ptr1+64), rgb_5); \
	SAVE_SI128((__m128i*)(rgb_ptr1+80), rgb_6); \
	SAVE_SI128((__m128i*)(rgb_ptr1+96), rgb_7); \
	SAVE_SI128((__m128i*)(rgb_ptr1+112), rgb_8); \

#ವ್ಯಾಖ್ಯಾನಿಸು SAVE_LINE2 \
	SAVE_SI128((__m128i*)(rgb_ptr2), rgb_9); \
	SAVE_SI128((__m128i*)(rgb_ptr2+16), rgb_10); \
	SAVE_SI128((__m128i*)(rgb_ptr2+32), rgb_11); \
	SAVE_SI128((__m128i*)(rgb_ptr2+48), rgb_12); \
	SAVE_SI128((__m128i*)(rgb_ptr2+64), rgb_13); \
	SAVE_SI128((__m128i*)(rgb_ptr2+80), rgb_14); \
	SAVE_SI128((__m128i*)(rgb_ptr2+96), rgb_15); \
	SAVE_SI128((__m128i*)(rgb_ptr2+112), rgb_16); \

#ಇಲ್ಲದಿದ್ದರೆ
#ದೋಷ SAVE_ಸಾಲು unimplemented
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ YUV_FORMAT == YUV_FORMAT_420

#ವ್ಯಾಖ್ಯಾನಿಸು READ_Y(y_ptr) \
	y = ತುಂಬು_SI128((ಸ್ಥಿರಾಂಕ __m128i*)(y_ptr)); \

#ವ್ಯಾಖ್ಯಾನಿಸು READ_UV	\
	u = ತುಂಬು_SI128((ಸ್ಥಿರಾಂಕ __m128i*)(u_ptr)); \
	v = ತುಂಬು_SI128((ಸ್ಥಿರಾಂಕ __m128i*)(v_ptr)); \

#ಅಥವಾಆದರೆ YUV_FORMAT == YUV_FORMAT_422

#ವ್ಯಾಖ್ಯಾನಿಸು READ_Y(y_ptr) \
{ \
	__m128i y1, y2; \
	y1 = _mm_srli_epi16(_mm_slli_epi16(ತುಂಬು_SI128((ಸ್ಥಿರಾಂಕ __m128i*)(y_ptr)), 8), 8); \
	y2 = _mm_srli_epi16(_mm_slli_epi16(ತುಂಬು_SI128((ಸ್ಥಿರಾಂಕ __m128i*)(y_ptr+16)), 8), 8); \
	y = _mm_packus_epi16(y1, y2); \
}

#ವ್ಯಾಖ್ಯಾನಿಸು READ_UV	\
{ \
	__m128i u1, u2, u3, u4, v1, v2, v3, v4; \
	u1 = _mm_srli_epi32(_mm_slli_epi32(ತುಂಬು_SI128((ಸ್ಥಿರಾಂಕ __m128i*)(u_ptr)), 24), 24); \
	u2 = _mm_srli_epi32(_mm_slli_epi32(ತುಂಬು_SI128((ಸ್ಥಿರಾಂಕ __m128i*)(u_ptr+16)), 24), 24); \
	u3 = _mm_srli_epi32(_mm_slli_epi32(ತುಂಬು_SI128((ಸ್ಥಿರಾಂಕ __m128i*)(u_ptr+32)), 24), 24); \
	u4 = _mm_srli_epi32(_mm_slli_epi32(ತುಂಬು_SI128((ಸ್ಥಿರಾಂಕ __m128i*)(u_ptr+48)), 24), 24); \
	u = _mm_packus_epi16(_mm_packs_epi32(u1, u2), _mm_packs_epi32(u3, u4)); \
	v1 = _mm_srli_epi32(_mm_slli_epi32(ತುಂಬು_SI128((ಸ್ಥಿರಾಂಕ __m128i*)(v_ptr)), 24), 24); \
	v2 = _mm_srli_epi32(_mm_slli_epi32(ತುಂಬು_SI128((ಸ್ಥಿರಾಂಕ __m128i*)(v_ptr+16)), 24), 24); \
	v3 = _mm_srli_epi32(_mm_slli_epi32(ತುಂಬು_SI128((ಸ್ಥಿರಾಂಕ __m128i*)(v_ptr+32)), 24), 24); \
	v4 = _mm_srli_epi32(_mm_slli_epi32(ತುಂಬು_SI128((ಸ್ಥಿರಾಂಕ __m128i*)(v_ptr+48)), 24), 24); \
	v = _mm_packus_epi16(_mm_packs_epi32(v1, v2), _mm_packs_epi32(v3, v4)); \
}

#ಅಥವಾಆದರೆ YUV_FORMAT == YUV_FORMAT_NV12

#ವ್ಯಾಖ್ಯಾನಿಸು READ_Y(y_ptr) \
	y = ತುಂಬು_SI128((ಸ್ಥಿರಾಂಕ __m128i*)(y_ptr)); \

#ವ್ಯಾಖ್ಯಾನಿಸು READ_UV	\
{ \
	__m128i u1, u2, v1, v2; \
	u1 = _mm_srli_epi16(_mm_slli_epi16(ತುಂಬು_SI128((ಸ್ಥಿರಾಂಕ __m128i*)(u_ptr)), 8), 8); \
	u2 = _mm_srli_epi16(_mm_slli_epi16(ತುಂಬು_SI128((ಸ್ಥಿರಾಂಕ __m128i*)(u_ptr+16)), 8), 8); \
	u = _mm_packus_epi16(u1, u2); \
	v1 = _mm_srli_epi16(_mm_slli_epi16(ತುಂಬು_SI128((ಸ್ಥಿರಾಂಕ __m128i*)(v_ptr)), 8), 8); \
	v2 = _mm_srli_epi16(_mm_slli_epi16(ತುಂಬು_SI128((ಸ್ಥಿರಾಂಕ __m128i*)(v_ptr+16)), 8), 8); \
	v = _mm_packus_epi16(v1, v2); \
}

#ಇಲ್ಲದಿದ್ದರೆ
#ದೋಷ READ_UV unimplemented
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿಸು YUV2RGB_32 \
	__m128i r_tmp, g_tmp, b_tmp; \
	__m128i r_16_1, g_16_1, b_16_1, r_16_2, g_16_2, b_16_2; \
	__m128i r_uv_16_1, g_uv_16_1, b_uv_16_1, r_uv_16_2, g_uv_16_2, b_uv_16_2; \
	__m128i y_16_1, y_16_2; \
	__m128i y, u, v, u_16, v_16; \
    __m128i r_8_11, g_8_11, b_8_11, r_8_21, g_8_21, b_8_21; \
    __m128i r_8_12, g_8_12, b_8_12, r_8_22, g_8_22, b_8_22; \
	\
	READ_UV \
	\
	/* process first 16 pixels of first line */\
	u_16 = _mm_unpacklo_epi8(u, _mm_setzero_si128()); \
	v_16 = _mm_unpacklo_epi8(v, _mm_setzero_si128()); \
	u_16 = mm_ಕೂಡಿಸು_epi16(u_16, _mm_set1_epi16(-128)); \
	v_16 = mm_ಕೂಡಿಸು_epi16(v_16, _mm_set1_epi16(-128)); \
	\
	UV2RGB_16(u_16, v_16, r_16_1, g_16_1, b_16_1, r_16_2, g_16_2, b_16_2) \
	r_uv_16_1=r_16_1; g_uv_16_1=g_16_1; b_uv_16_1=b_16_1; \
	r_uv_16_2=r_16_2; g_uv_16_2=g_16_2; b_uv_16_2=b_16_2; \
	\
	READ_Y(y_ptr1) \
	y_16_1 = _mm_unpacklo_epi8(y, _mm_setzero_si128()); \
	y_16_2 = _mm_unpackhi_epi8(y, _mm_setzero_si128()); \
	\
	ಕೂಡಿಸು_Y2_RGB_16(y_16_1, y_16_2, r_16_1, g_16_1, b_16_1, r_16_2, g_16_2, b_16_2) \
	\
	r_8_11 = _mm_packus_epi16(r_16_1, r_16_2); \
	g_8_11 = _mm_packus_epi16(g_16_1, g_16_2); \
	b_8_11 = _mm_packus_epi16(b_16_1, b_16_2); \
	\
	/* process first 16 pixels of second line */\
	r_16_1=r_uv_16_1; g_16_1=g_uv_16_1; b_16_1=b_uv_16_1; \
	r_16_2=r_uv_16_2; g_16_2=g_uv_16_2; b_16_2=b_uv_16_2; \
	\
	READ_Y(y_ptr2) \
	y_16_1 = _mm_unpacklo_epi8(y, _mm_setzero_si128()); \
	y_16_2 = _mm_unpackhi_epi8(y, _mm_setzero_si128()); \
	\
	ಕೂಡಿಸು_Y2_RGB_16(y_16_1, y_16_2, r_16_1, g_16_1, b_16_1, r_16_2, g_16_2, b_16_2) \
	\
	r_8_21 = _mm_packus_epi16(r_16_1, r_16_2); \
	g_8_21 = _mm_packus_epi16(g_16_1, g_16_2); \
	b_8_21 = _mm_packus_epi16(b_16_1, b_16_2); \
	\
	/* process last 16 pixels of first line */\
	u_16 = _mm_unpackhi_epi8(u, _mm_setzero_si128()); \
	v_16 = _mm_unpackhi_epi8(v, _mm_setzero_si128()); \
	u_16 = mm_ಕೂಡಿಸು_epi16(u_16, _mm_set1_epi16(-128)); \
	v_16 = mm_ಕೂಡಿಸು_epi16(v_16, _mm_set1_epi16(-128)); \
	\
	UV2RGB_16(u_16, v_16, r_16_1, g_16_1, b_16_1, r_16_2, g_16_2, b_16_2) \
	r_uv_16_1=r_16_1; g_uv_16_1=g_16_1; b_uv_16_1=b_16_1; \
	r_uv_16_2=r_16_2; g_uv_16_2=g_16_2; b_uv_16_2=b_16_2; \
	\
	READ_Y(y_ptr1+16*y_pixel_stride) \
	y_16_1 = _mm_unpacklo_epi8(y, _mm_setzero_si128()); \
	y_16_2 = _mm_unpackhi_epi8(y, _mm_setzero_si128()); \
	\
	ಕೂಡಿಸು_Y2_RGB_16(y_16_1, y_16_2, r_16_1, g_16_1, b_16_1, r_16_2, g_16_2, b_16_2) \
	\
	r_8_12 = _mm_packus_epi16(r_16_1, r_16_2); \
	g_8_12 = _mm_packus_epi16(g_16_1, g_16_2); \
	b_8_12 = _mm_packus_epi16(b_16_1, b_16_2); \
	\
	/* process last 16 pixels of second line */\
	r_16_1=r_uv_16_1; g_16_1=g_uv_16_1; b_16_1=b_uv_16_1; \
	r_16_2=r_uv_16_2; g_16_2=g_uv_16_2; b_16_2=b_uv_16_2; \
	\
	READ_Y(y_ptr2+16*y_pixel_stride) \
	y_16_1 = _mm_unpacklo_epi8(y, _mm_setzero_si128()); \
	y_16_2 = _mm_unpackhi_epi8(y, _mm_setzero_si128()); \
	\
	ಕೂಡಿಸು_Y2_RGB_16(y_16_1, y_16_2, r_16_1, g_16_1, b_16_1, r_16_2, g_16_2, b_16_2) \
	\
	r_8_22 = _mm_packus_epi16(r_16_1, r_16_2); \
	g_8_22 = _mm_packus_epi16(g_16_1, g_16_2); \
	b_8_22 = _mm_packus_epi16(b_16_1, b_16_2); \
	\


ಶೂನ್ಯ SDL_TARGETING("sse2") SSE_FUNCTION_NAME(uint32_t ಅಗಲ, uint32_t ಎತ್ತರ, 
	ಸ್ಥಿರಾಂಕ uint8_t *Y, ಸ್ಥಿರಾಂಕ uint8_t *U, ಸ್ಥಿರಾಂಕ uint8_t *V, uint32_t Y_stride, uint32_t UV_stride, 
	uint8_t *RGB, uint32_t RGB_stride, 
	YCbCrType yuv_type)
{
	ಸ್ಥಿರಾಂಕ YUV2RGBParam *ಸ್ಥಿರಾಂಕ param = &(YUV2RGB[yuv_type]);
#ಆದರೆ YUV_FORMAT == YUV_FORMAT_420
	ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ y_pixel_stride = 1;
	ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ uv_pixel_stride = 1;
	ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ uv_x_sample_interval = 2;
	ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ uv_y_sample_interval = 2;
#ಅಥವಾಆದರೆ YUV_FORMAT == YUV_FORMAT_422
	ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ y_pixel_stride = 2;
	ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ uv_pixel_stride = 4;
	ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ uv_x_sample_interval = 2;
	ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ uv_y_sample_interval = 1;
#ಅಥವಾಆದರೆ YUV_FORMAT == YUV_FORMAT_NV12
	ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ y_pixel_stride = 1;
	ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ uv_pixel_stride = 2;
	ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ uv_x_sample_interval = 2;
	ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ uv_y_sample_interval = 2;
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ RGB_FORMAT == RGB_FORMAT_RGB565
	ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ rgb_pixel_stride = 2;
#ಅಥವಾಆದರೆ RGB_FORMAT == RGB_FORMAT_RGB24
	ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ rgb_pixel_stride = 3;
#ಅಥವಾಆದರೆ RGB_FORMAT == RGB_FORMAT_RGBA || RGB_FORMAT == RGB_FORMAT_BGRA || \
      RGB_FORMAT == RGB_FORMAT_ARGB || RGB_FORMAT == RGB_FORMAT_ABGR
	ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ rgb_pixel_stride = 4;
#ಇಲ್ಲದಿದ್ದರೆ
#ದೋಷ Unknown RGB pixel ಗಾತ್ರ_2
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ YUV_FORMAT == YUV_FORMAT_NV12
	/* For NV12 formats (where U/V are interleaved)
	 * SSE READ_UV does an invalid read access at the very last pixel.
	 * As a workaround. Make sure not to decode the last column using assembly but with STD fallback path.
	 * see https://github.com/libsdl-org/SDL/issues/4841
	 */
	ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ fix_read_nv12 = ((ಅಗಲ & 31) == 0);
#ಇಲ್ಲದಿದ್ದರೆ
	ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ fix_read_nv12 = 0;
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ YUV_FORMAT == YUV_FORMAT_422
	/* Avoid invalid read on last line */
	ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ fix_read_422 = 1;
#ಇಲ್ಲದಿದ್ದರೆ
	ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ fix_read_422 = 0;
#ಆದರೆ_ಅಂತ್ಯ


	ಆದರೆ (ಅಗಲ >= 32) {
		uint32_t xpos, ypos;
		ಗಾಗಿ(ypos=0; ypos<(ಎತ್ತರ-(uv_y_sample_interval-1)) - fix_read_422; ypos+=uv_y_sample_interval)
		{
			ಸ್ಥಿರಾಂಕ uint8_t *y_ptr1=Y+ypos*Y_stride,
				*y_ptr2=Y+(ypos+1)*Y_stride,
				*u_ptr=U+(ypos/uv_y_sample_interval)*UV_stride,
				*v_ptr=V+(ypos/uv_y_sample_interval)*UV_stride;
			
			uint8_t *rgb_ptr1=RGB+ypos*RGB_stride,
				*rgb_ptr2=RGB+(ypos+1)*RGB_stride;
			
			ಗಾಗಿ(xpos=0; xpos<(ಅಗಲ-31) - fix_read_nv12; xpos+=32)
			{
				YUV2RGB_32
				{
					PACK_PIXEL
					SAVE_LINE1
					ಆದರೆ (uv_y_sample_interval > 1)
					{
						SAVE_LINE2
					}
				}

				y_ptr1+=32*y_pixel_stride;
				y_ptr2+=32*y_pixel_stride;
				u_ptr+=32*uv_pixel_stride/uv_x_sample_interval;
				v_ptr+=32*uv_pixel_stride/uv_x_sample_interval;
				rgb_ptr1+=32*rgb_pixel_stride;
				rgb_ptr2+=32*rgb_pixel_stride;
			}
		}

		ಆದರೆ (fix_read_422) {
			ಸ್ಥಿರಾಂಕ uint8_t *y_ptr=Y+ypos*Y_stride,
				*u_ptr=U+(ypos/uv_y_sample_interval)*UV_stride,
				*v_ptr=V+(ypos/uv_y_sample_interval)*UV_stride;
			uint8_t *rgb_ptr=RGB+ypos*RGB_stride;
			STD_FUNCTION_NAME(ಅಗಲ, 1, y_ptr, u_ptr, v_ptr, Y_stride, UV_stride, rgb_ptr, RGB_stride, yuv_type);
			ypos += uv_y_sample_interval;
		}

		/* Catch the last line, if needed */
		ಆದರೆ (uv_y_sample_interval == 2 && ypos == (ಎತ್ತರ-1))
		{
			ಸ್ಥಿರಾಂಕ uint8_t *y_ptr=Y+ypos*Y_stride,
				*u_ptr=U+(ypos/uv_y_sample_interval)*UV_stride,
				*v_ptr=V+(ypos/uv_y_sample_interval)*UV_stride;
			
			uint8_t *rgb_ptr=RGB+ypos*RGB_stride;

			STD_FUNCTION_NAME(ಅಗಲ, 1, y_ptr, u_ptr, v_ptr, Y_stride, UV_stride, rgb_ptr, RGB_stride, yuv_type);
		}
	}

	/* Catch the right column, if needed */
	{
		uint32_t converted = (ಅಗಲ & ~31);
		ಆದರೆ (fix_read_nv12) {
			converted -= 32;
		}
		ಆದರೆ (converted != ಅಗಲ)
		{
			ಸ್ಥಿರಾಂಕ uint8_t *y_ptr=Y+converted*y_pixel_stride,
				*u_ptr=U+converted*uv_pixel_stride/uv_x_sample_interval,
				*v_ptr=V+converted*uv_pixel_stride/uv_x_sample_interval;
			
			uint8_t *rgb_ptr=RGB+converted*rgb_pixel_stride;

			STD_FUNCTION_NAME(ಅಗಲ-converted, ಎತ್ತರ, y_ptr, u_ptr, v_ptr, Y_stride, UV_stride, rgb_ptr, RGB_stride, yuv_type);
		}
	}
}

#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು SSE_FUNCTION_NAME
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು STD_FUNCTION_NAME
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು YUV_FORMAT
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು RGB_FORMAT
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು SSE_ALIGNED
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು ತುಂಬು_SI128
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು SAVE_SI128
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು UV2RGB_16
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು ಕೂಡಿಸು_Y2_RGB_16
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು PACK_RGB24_32_STEP1
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು PACK_RGB24_32_STEP2
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು PACK_RGB24_32
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು PACK_RGBA_32
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು PACK_PIXEL
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು SAVE_LINE1
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು SAVE_LINE2
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು READ_Y
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು READ_UV
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು YUV2RGB_32
