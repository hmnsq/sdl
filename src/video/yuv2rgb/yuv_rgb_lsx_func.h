// Copyright 2016 Adrien Descamps
// // Distributed under BSD 3-Clause License

#समावेश <lsxintrin.h>

#अगर YUV_FORMAT == YUV_FORMAT_420

#घोषणा READ_Y(y_ptr)                                     \
    y = __lsx_vld(y_ptr, 0);                              \

#घोषणा READ_UV                                           \
    u_अस्थायी = __lsx_vld(u_ptr, 0);                         \
    v_अस्थायी = __lsx_vld(v_ptr, 0);                         \

#अन्यथा
#त्रुटि READ_UV unimplemented
#पूर्ण_अगर

#घोषणा PACK_RGBA_32(R1, R2, G1, G2, B1, B2, A1, A2, RGB1, RGB2,       \
                     RGB3, RGB4, RGB5, RGB6, RGB7, RGB8)               \
{                                       \
    __m128i ab_l, ab_h, gr_l, gr_h;     \
    ab_l = __lsx_vilvl_b(B1, A1);       \
    ab_h = __lsx_vilvh_b(B1, A1);       \
    gr_l = __lsx_vilvl_b(R1, G1);       \
    gr_h = __lsx_vilvh_b(R1, G1);       \
    RGB1 = __lsx_vilvl_h(gr_l, ab_l);   \
    RGB2 = __lsx_vilvh_h(gr_l, ab_l);   \
    RGB3 = __lsx_vilvl_h(gr_h, ab_h);   \
    RGB4 = __lsx_vilvh_h(gr_h, ab_h);   \
    ab_l = __lsx_vilvl_b(B2, A2);       \
    ab_h = __lsx_vilvh_b(B2, A2);       \
    gr_l = __lsx_vilvl_b(R2, G2);       \
    gr_h = __lsx_vilvh_b(R2, G2);       \
    RGB5 = __lsx_vilvl_h(gr_l, ab_l);   \
    RGB6 = __lsx_vilvh_h(gr_l, ab_l);   \
    RGB7 = __lsx_vilvl_h(gr_h, ab_h);   \
    RGB8 = __lsx_vilvh_h(gr_h, ab_h);   \
}

#घोषणा PACK_RGB24_32_STEP(R, G, B, RGB1, RGB2, RGB3)        \
    RGB1 = __lsx_vilvl_b(G, R);                              \
    RGB1 = __lsx_vshuf_b(B, RGB1, mask1);                    \
    RGB2 = __lsx_vshuf_b(B, G, mask2);                       \
    RGB2 = __lsx_vshuf_b(R, RGB2, mask3);                    \
    RGB3 = __lsx_vshuf_b(R, B, mask4);                       \
    RGB3 = __lsx_vshuf_b(G, RGB3, mask5);                    \

#घोषणा PACK_RGB24_32(R1, R2, G1, G2, B1, B2, RGB1, RGB2, RGB3, RGB4, RGB5, RGB6)  \
    PACK_RGB24_32_STEP(R1, G1, B1, RGB1, RGB2, RGB3);                              \
    PACK_RGB24_32_STEP(R2, G2, B2, RGB4, RGB5, RGB6);                              \

#अगर RGB_FORMAT == RGB_FORMAT_RGB24

#घोषणा PACK_PIXEL                                                             \
    __m128i rgb_1, rgb_2, rgb_3, rgb_4, rgb_5, rgb_6;                          \
    __m128i rgb_7, rgb_8, rgb_9, rgb_10, rgb_11, rgb_12;                       \
    PACK_RGB24_32(r_8_11, r_8_12, g_8_11, g_8_12, b_8_11, b_8_12,              \
                  rgb_1, rgb_2, rgb_3, rgb_4, rgb_5, rgb_6)                    \
    PACK_RGB24_32(r_8_21, r_8_22, g_8_21, g_8_22, b_8_21, b_8_22,              \
                  rgb_7, rgb_8, rgb_9, rgb_10, rgb_11, rgb_12)                 \

#या_अगर RGB_FORMAT == RGB_FORMAT_RGBA

#घोषणा PACK_PIXEL                                                              \
    __m128i rgb_1, rgb_2, rgb_3, rgb_4, rgb_5, rgb_6, rgb_7, rgb_8;             \
    __m128i rgb_9, rgb_10, rgb_11, rgb_12, rgb_13, rgb_14, rgb_15, rgb_16;      \
    __m128i a = __lsx_vldi(0xFF);                                               \
    PACK_RGBA_32(r_8_11, r_8_12, g_8_11, g_8_12, b_8_11, b_8_12, a, a,          \
                 rgb_1, rgb_2, rgb_3, rgb_4, rgb_5, rgb_6, rgb_7, rgb_8)        \
    PACK_RGBA_32(r_8_21, r_8_22, g_8_21, g_8_22, b_8_21, b_8_22, a, a,          \
                 rgb_9, rgb_10, rgb_11, rgb_12, rgb_13, rgb_14, rgb_15, rgb_16) \

#या_अगर RGB_FORMAT == RGB_FORMAT_BGRA

#घोषणा PACK_PIXEL                                                              \
    __m128i rgb_1, rgb_2, rgb_3, rgb_4, rgb_5, rgb_6, rgb_7, rgb_8;             \
    __m128i rgb_9, rgb_10, rgb_11, rgb_12, rgb_13, rgb_14, rgb_15, rgb_16;      \
    __m128i a = __lsx_vldi(0xFF);                                               \
    PACK_RGBA_32(b_8_11, b_8_12, g_8_11, g_8_12, r_8_11, r_8_12, a, a,          \
                 rgb_1, rgb_2, rgb_3, rgb_4, rgb_5, rgb_6, rgb_7, rgb_8)        \
    PACK_RGBA_32(b_8_21, b_8_22, g_8_21, g_8_22, r_8_21, r_8_22, a, a,          \
                 rgb_9, rgb_10, rgb_11, rgb_12, rgb_13, rgb_14, rgb_15, rgb_16) \

#या_अगर RGB_FORMAT == RGB_FORMAT_ARGB

#घोषणा PACK_PIXEL                                                              \
    __m128i rgb_1, rgb_2, rgb_3, rgb_4, rgb_5, rgb_6, rgb_7, rgb_8;             \
    __m128i rgb_9, rgb_10, rgb_11, rgb_12, rgb_13, rgb_14, rgb_15, rgb_16;      \
    __m128i a = __lsx_vldi(0xFF);                                               \
    PACK_RGBA_32(a, a, r_8_11, r_8_12, g_8_11, g_8_12, b_8_11, b_8_12,          \
                 rgb_1, rgb_2, rgb_3, rgb_4, rgb_5, rgb_6, rgb_7, rgb_8)        \
    PACK_RGBA_32(a, a, r_8_21, r_8_22, g_8_21, g_8_22, b_8_21, b_8_22,          \
                 rgb_9, rgb_10, rgb_11, rgb_12, rgb_13, rgb_14, rgb_15, rgb_16) \

#या_अगर RGB_FORMAT == RGB_FORMAT_ABGR

#घोषणा PACK_PIXEL                                                              \
    __m128i rgb_1, rgb_2, rgb_3, rgb_4, rgb_5, rgb_6, rgb_7, rgb_8;             \
    __m128i rgb_9, rgb_10, rgb_11, rgb_12, rgb_13, rgb_14, rgb_15, rgb_16;      \
    __m128i a = __lsx_vldi(0xFF);                                               \
    PACK_RGBA_32(a, a, b_8_11, b_8_12, g_8_11, g_8_12, r_8_11, r_8_12,          \
                 rgb_1, rgb_2, rgb_3, rgb_4, rgb_5, rgb_6, rgb_7, rgb_8)        \
    PACK_RGBA_32(a, a, b_8_21, b_8_22, g_8_21, g_8_22, r_8_21, r_8_22,          \
                 rgb_9, rgb_10, rgb_11, rgb_12, rgb_13, rgb_14, rgb_15, rgb_16) \

#अन्यथा
#त्रुटि PACK_PIXEL unimplemented
#पूर्ण_अगर

#घोषणा LSX_ST_UB2(in0, in1, pdst, stride)                      \
{                                                               \
    __lsx_vst(in0, pdst, 0);                                    \
    __lsx_vst(in1, pdst + stride, 0);                           \
}

#अगर RGB_FORMAT == RGB_FORMAT_RGB24                              \

#घोषणा SAVE_LINE1                                              \
    LSX_ST_UB2(rgb_1, rgb_2, rgb_ptr1, 16);                     \
    LSX_ST_UB2(rgb_3, rgb_4, rgb_ptr1 + 32, 16);                \
    LSX_ST_UB2(rgb_5, rgb_6, rgb_ptr1 + 64, 16);                \

#घोषणा SAVE_LINE2                                              \
    LSX_ST_UB2(rgb_7, rgb_8, rgb_ptr2, 16);                     \
    LSX_ST_UB2(rgb_9, rgb_10, rgb_ptr2 + 32, 16);               \
    LSX_ST_UB2(rgb_11, rgb_12, rgb_ptr2 + 64, 16);              \

#या_अगर RGB_FORMAT == RGB_FORMAT_RGBA || RGB_FORMAT == RGB_FORMAT_BGRA ||  \
    RGB_FORMAT == RGB_FORMAT_ARGB || RGB_FORMAT == RGB_FORMAT_ABGR       \

#घोषणा SAVE_LINE1                                              \
    LSX_ST_UB2(rgb_1, rgb_2, rgb_ptr1, 16);                     \
    LSX_ST_UB2(rgb_3, rgb_4, rgb_ptr1 + 32, 16);                \
    LSX_ST_UB2(rgb_5, rgb_6, rgb_ptr1 + 64, 16);                \
    LSX_ST_UB2(rgb_7, rgb_8, rgb_ptr1 + 96, 16);                \

#घोषणा SAVE_LINE2                                              \
    LSX_ST_UB2(rgb_9,  rgb_10, rgb_ptr2, 16);                   \
    LSX_ST_UB2(rgb_11, rgb_12, rgb_ptr2 + 32, 16);              \
    LSX_ST_UB2(rgb_13, rgb_14, rgb_ptr2 + 64, 16);              \
    LSX_ST_UB2(rgb_15, rgb_16, rgb_ptr2 + 96, 16);              \

#अन्यथा
#त्रुटि SAVE_पंक्ति unimplemented
#पूर्ण_अगर

// = u*vr g=u*ug+v*vg b=u*ub
#घोषणा UV2RGB_16(U, V, R1, G1, B1, R2, G2, B2)     \
    r_अस्थायी = __lsx_vmul_h(V, v2r);                  \
    g_अस्थायी = __lsx_vmul_h(U, u2g);                  \
    g_अस्थायी = __lsx_vmadd_h(g_अस्थायी, V, v2g);         \
    b_अस्थायी = __lsx_vmul_h(U, u2b);                  \
    R1     = __lsx_vilvl_h(r_अस्थायी, r_अस्थायी);         \
    G1     = __lsx_vilvl_h(g_अस्थायी, g_अस्थायी);         \
    B1     = __lsx_vilvl_h(b_अस्थायी, b_अस्थायी);         \
    R2     = __lsx_vilvh_h(r_अस्थायी, r_अस्थायी);         \
    G2     = __lsx_vilvh_h(g_अस्थायी, g_अस्थायी);         \
    B2     = __lsx_vilvh_h(b_अस्थायी, b_अस्थायी);         \

// Y=(Y-shift)*shift R=(Y+R)>>6,G=(Y+G)>>6,B=(B+Y)>>6
#घोषणा ADD_Y2RGB_16(Y1, Y2, R1, G1, B1, R2, G2, B2)        \
    Y1 = __lsx_vsub_h(Y1, shift);                           \
    Y2 = __lsx_vsub_h(Y2, shift);                           \
    Y1 = __lsx_vmul_h(Y1, yf);                              \
    Y2 = __lsx_vmul_h(Y2, yf);                              \
    R1 = __lsx_vadd_h(R1, Y1);                              \
    G1 = __lsx_vadd_h(G1, Y1);                              \
    B1 = __lsx_vadd_h(B1, Y1);                              \
    R2 = __lsx_vadd_h(R2, Y2);                              \
    G2 = __lsx_vadd_h(G2, Y2);                              \
    B2 = __lsx_vadd_h(B2, Y2);                              \
    R1 = __lsx_vsrai_h(R1, PRECISION);                      \
    G1 = __lsx_vsrai_h(G1, PRECISION);                      \
    B1 = __lsx_vsrai_h(B1, PRECISION);                      \
    R2 = __lsx_vsrai_h(R2, PRECISION);                      \
    G2 = __lsx_vsrai_h(G2, PRECISION);                      \
    B2 = __lsx_vsrai_h(B2, PRECISION);                      \

#घोषणा CLIP(in0, in1, in2, in3, in4, in5)       \
{                                                \
    in0 = __lsx_vmaxi_h(in0, 0);                 \
    in1 = __lsx_vmaxi_h(in1, 0);                 \
    in2 = __lsx_vmaxi_h(in2, 0);                 \
    in3 = __lsx_vmaxi_h(in3, 0);                 \
    in4 = __lsx_vmaxi_h(in4, 0);                 \
    in5 = __lsx_vmaxi_h(in5, 0);                 \
    in0 = __lsx_vsat_hu(in0, 7);                 \
    in1 = __lsx_vsat_hu(in1, 7);                 \
    in2 = __lsx_vsat_hu(in2, 7);                 \
    in3 = __lsx_vsat_hu(in3, 7);                 \
    in4 = __lsx_vsat_hu(in4, 7);                 \
    in5 = __lsx_vsat_hu(in5, 7);                 \
}

#घोषणा YUV2RGB_32                                            \
    __m128i y, u_अस्थायी, v_अस्थायी;                                \
    __m128i r_8_11, g_8_11, b_8_11, r_8_21, g_8_21, b_8_21;   \
    __m128i r_8_12, g_8_12, b_8_12, r_8_22, g_8_22, b_8_22;   \
    __m128i u, v, r_अस्थायी, g_अस्थायी, b_अस्थायी;                     \
    __m128i r_1, g_1, b_1, r_2, g_2, b_2;                     \
    __m128i y_1, y_2;                                         \
    __m128i r_uv_1, g_uv_1, b_uv_1, r_uv_2, g_uv_2, b_uv_2;   \
                                                              \
    READ_UV                                                   \
                                                              \
    /* process first 16 pixels of first line */               \
    u = __lsx_vilvl_b(zero, u_अस्थायी);                          \
    v = __lsx_vilvl_b(zero, v_अस्थायी);                          \
    u = __lsx_vsub_h(u, bias);                                \
    v = __lsx_vsub_h(v, bias);                                \
    UV2RGB_16(u, v, r_1, g_1, b_1, r_2, g_2, b_2);            \
    r_uv_1 = r_1; g_uv_1 = g_1; b_uv_1 = b_1;                 \
    r_uv_2 = r_2; g_uv_2 = g_2; b_uv_2 = b_2;                 \
    READ_Y(y_ptr1)                                            \
    y_1 = __lsx_vilvl_b(zero, y);                             \
    y_2 = __lsx_vilvh_b(zero, y);                             \
    ADD_Y2RGB_16(y_1, y_2, r_1, g_1, b_1, r_2, g_2, b_2)      \
    CLIP(r_1, g_1, b_1, r_2, g_2, b_2);                       \
    r_8_11 = __lsx_vpickev_b(r_2, r_1);                       \
    g_8_11 = __lsx_vpickev_b(g_2, g_1);                       \
    b_8_11 = __lsx_vpickev_b(b_2, b_1);                       \
                                                              \
    /* process first 16 pixels of second line */              \
    r_1 = r_uv_1; g_1 = g_uv_1; b_1 = b_uv_1;                 \
    r_2 = r_uv_2; g_2 = g_uv_2; b_2 = b_uv_2;                 \
                                                              \
    READ_Y(y_ptr2)                                            \
    y_1 = __lsx_vilvl_b(zero, y);                             \
    y_2 = __lsx_vilvh_b(zero, y);                             \
    ADD_Y2RGB_16(y_1, y_2, r_1, g_1, b_1, r_2, g_2, b_2)      \
    CLIP(r_1, g_1, b_1, r_2, g_2, b_2);                       \
    r_8_21 = __lsx_vpickev_b(r_2, r_1);                       \
    g_8_21 = __lsx_vpickev_b(g_2, g_1);                       \
    b_8_21 = __lsx_vpickev_b(b_2, b_1);                       \
                                                              \
    /* process last 16 pixels of first line */                \
    u = __lsx_vilvh_b(zero, u_अस्थायी);                          \
    v = __lsx_vilvh_b(zero, v_अस्थायी);                          \
    u = __lsx_vsub_h(u, bias);                                \
    v = __lsx_vsub_h(v, bias);                                \
    UV2RGB_16(u, v, r_1, g_1, b_1, r_2, g_2, b_2);            \
    r_uv_1 = r_1; g_uv_1 = g_1; b_uv_1 = b_1;                 \
    r_uv_2 = r_2; g_uv_2 = g_2; b_uv_2 = b_2;                 \
    READ_Y(y_ptr1 + 16 * y_pixel_stride)                      \
    y_1 = __lsx_vilvl_b(zero, y);                             \
    y_2 = __lsx_vilvh_b(zero, y);                             \
    ADD_Y2RGB_16(y_1, y_2, r_1, g_1, b_1, r_2, g_2, b_2)      \
    CLIP(r_1, g_1, b_1, r_2, g_2, b_2);                       \
    r_8_12 = __lsx_vpickev_b(r_2, r_1);                       \
    g_8_12 = __lsx_vpickev_b(g_2, g_1);                       \
    b_8_12 = __lsx_vpickev_b(b_2, b_1);                       \
                                                              \
   /* process last 16 pixels of second line */                \
    r_1 = r_uv_1; g_1 = g_uv_1; b_1 = b_uv_1;                 \
    r_2 = r_uv_2; g_2 = g_uv_2; b_2 = b_uv_2;                 \
                                                              \
    READ_Y(y_ptr2 + 16 * y_pixel_stride)                      \
    y_1 = __lsx_vilvl_b(zero, y);                             \
    y_2 = __lsx_vilvh_b(zero, y);                             \
    ADD_Y2RGB_16(y_1, y_2, r_1, g_1, b_1, r_2, g_2, b_2)      \
    CLIP(r_1, g_1, b_1, r_2, g_2, b_2);                       \
    r_8_22 = __lsx_vpickev_b(r_2, r_1);                       \
    g_8_22 = __lsx_vpickev_b(g_2, g_1);                       \
    b_8_22 = __lsx_vpickev_b(b_2, b_1);                       \
                                                              \

व्योम LSX_FUNCTION_NAME(uint32_t width, uint32_t height, स्थिर uint8_t *Y,
                       स्थिर uint8_t *U, स्थिर uint8_t *V, uint32_t Y_stride,
                       uint32_t UV_stride, uint8_t *RGB, uint32_t RGB_stride,
                       YCbCrType yuv_type)
{
    स्थिर YUV2RGBParam *स्थिर param = &(YUV2RGB[yuv_type]);
#अगर YUV_FORMAT == YUV_FORMAT_420
    स्थिर पूर्णांक y_pixel_stride = 1;
    स्थिर पूर्णांक uv_pixel_stride = 1;
    स्थिर पूर्णांक uv_x_sample_interval = 2;
    स्थिर पूर्णांक uv_y_sample_interval = 2;
#पूर्ण_अगर

#अगर RGB_FORMAT == RGB_FORMAT_RGB565
    स्थिर पूर्णांक rgb_pixel_stride = 2;
#या_अगर RGB_FORMAT == RGB_FORMAT_RGB24
    स्थिर पूर्णांक rgb_pixel_stride = 3;
    __m128i mask1 = {0x0504110302100100, 0x0A14090813070612};
    __m128i mask2 = {0x1808170716061505, 0x00000000000A1909};
    __m128i mask3 = {0x0504170302160100, 0x0A1A090819070618};
    __m128i mask4 = {0x1E0D1D0C1C0B1B0A, 0x00000000000F1F0E};
    __m128i mask5 = {0x05041C03021B0100, 0x0A1F09081E07061D};
#या_अगर RGB_FORMAT == RGB_FORMAT_RGBA || RGB_FORMAT_BGRA || \
    RGB_FORMAT == RGB_FORMAT_ARGB || RGB_FORMAT_ABGR
    स्थिर पूर्णांक rgb_pixel_stride = 4;
#अन्यथा
#त्रुटि Unknown RGB pixel आकार
#पूर्ण_अगर

    uint32_t xpos, ypos;
    __m128i v2r   = __lsx_vreplgr2vr_h(param->v_r_factor);
    __m128i v2g   = __lsx_vreplgr2vr_h(param->v_g_factor);
    __m128i u2g   = __lsx_vreplgr2vr_h(param->u_g_factor);
    __m128i u2b   = __lsx_vreplgr2vr_h(param->u_b_factor);
    __m128i bias  = __lsx_vreplgr2vr_h(128);
    __m128i shift = __lsx_vreplgr2vr_h(param->y_shift);
    __m128i yf    = __lsx_vreplgr2vr_h(param->y_factor);
    __m128i zero  = __lsx_vldi(0);

    अगर (width >= 32) {
        क्रम (ypos = 0; ypos < (height - (uv_y_sample_interval - 1)); ypos += uv_y_sample_interval) {
            स्थिर uint8_t *y_ptr1 = Y + ypos * Y_stride,
                          *y_ptr2 = Y + (ypos + 1) * Y_stride,
                          *u_ptr  = U + (ypos/uv_y_sample_interval) * UV_stride,
                          *v_ptr  = V + (ypos/uv_y_sample_interval) * UV_stride;
            uint8_t *rgb_ptr1 = RGB + ypos * RGB_stride,
                    *rgb_ptr2 = RGB + (ypos + 1) * RGB_stride;

            क्रम (xpos = 0; xpos < (width - 31); xpos += 32){
                YUV2RGB_32
                {
                    PACK_PIXEL
                    SAVE_LINE1
                    अगर (uv_y_sample_interval > 1)
                    {
                        SAVE_LINE2
                    }
                }
                y_ptr1   += 32 * y_pixel_stride;
                y_ptr2   += 32 * y_pixel_stride;
                u_ptr    += 32 * uv_pixel_stride/uv_x_sample_interval;
                v_ptr    += 32 * uv_pixel_stride/uv_x_sample_interval;
                rgb_ptr1 += 32 * rgb_pixel_stride;
                rgb_ptr2 += 32 * rgb_pixel_stride;
            }
        }
        अगर (uv_y_sample_interval == 2 && ypos == (height - 1)) {
            स्थिर uint8_t *y_ptr = Y + ypos * Y_stride,
                          *u_ptr = U + (ypos/uv_y_sample_interval) * UV_stride,
                          *v_ptr = V + (ypos/uv_y_sample_interval) * UV_stride;
            uint8_t *rgb_ptr = RGB + ypos * RGB_stride;
            STD_FUNCTION_NAME(width, 1, y_ptr, u_ptr, v_ptr, Y_stride, UV_stride, rgb_ptr, RGB_stride, yuv_type);
        }
    }
    {
        पूर्णांक converted = (width & ~31);
        अगर (converted != width)
        {
            स्थिर uint8_t *y_ptr = Y + converted * y_pixel_stride,
                          *u_ptr = U + converted * uv_pixel_stride / uv_x_sample_interval,
                          *v_ptr = V + converted * uv_pixel_stride / uv_x_sample_interval;
            uint8_t *rgb_ptr = RGB + converted * rgb_pixel_stride;

            STD_FUNCTION_NAME(width-converted, height, y_ptr, u_ptr, v_ptr, Y_stride, UV_stride, rgb_ptr, RGB_stride, yuv_type);
        }
    }
}

#अघोषित LSX_FUNCTION_NAME
#अघोषित STD_FUNCTION_NAME
#अघोषित YUV_FORMAT
#अघोषित RGB_FORMAT
#अघोषित LSX_ALIGNED
#अघोषित LSX_ST_UB2
#अघोषित UV2RGB_16
#अघोषित ADD_Y2RGB_16
#अघोषित PACK_RGB24_32_STEP
#अघोषित PACK_RGB24_32
#अघोषित PACK_PIXEL
#अघोषित PACK_RGBA_32
#अघोषित SAVE_LINE1
#अघोषित SAVE_LINE2
#अघोषित READ_Y
#अघोषित READ_UV
#अघोषित YUV2RGB_32
