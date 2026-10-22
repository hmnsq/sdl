// Copyright 2016 Adrien Descamps
// Distributed under BSD 3-Clause License
#समावेश "SDL_internal.h"

#अगर_घोषित SDL_HAVE_YUV
#समावेश "yuv_rgb_lsx.h"
#समावेश "yuv_rgb_internal.h"

#अगर_घोषित SDL_LSX_INTRINSICS

#घोषणा LSX_FUNCTION_NAME	yuv420_rgb24_lsx
#घोषणा STD_FUNCTION_NAME	yuv420_rgb24_std
#घोषणा YUV_FORMAT			YUV_FORMAT_420
#घोषणा RGB_FORMAT			RGB_FORMAT_RGB24
#समावेश "yuv_rgb_lsx_func.h"

#घोषणा LSX_FUNCTION_NAME	yuv420_rgba_lsx
#घोषणा STD_FUNCTION_NAME	yuv420_rgba_std
#घोषणा YUV_FORMAT			YUV_FORMAT_420
#घोषणा RGB_FORMAT			RGB_FORMAT_RGBA
#समावेश "yuv_rgb_lsx_func.h"

#घोषणा LSX_FUNCTION_NAME	yuv420_bgra_lsx
#घोषणा STD_FUNCTION_NAME	yuv420_bgra_std
#घोषणा YUV_FORMAT			YUV_FORMAT_420
#घोषणा RGB_FORMAT			RGB_FORMAT_BGRA
#समावेश "yuv_rgb_lsx_func.h"

#घोषणा LSX_FUNCTION_NAME	yuv420_argb_lsx
#घोषणा STD_FUNCTION_NAME	yuv420_argb_std
#घोषणा YUV_FORMAT			YUV_FORMAT_420
#घोषणा RGB_FORMAT			RGB_FORMAT_ARGB
#समावेश "yuv_rgb_lsx_func.h"

#घोषणा LSX_FUNCTION_NAME	yuv420_abgr_lsx
#घोषणा STD_FUNCTION_NAME	yuv420_abgr_std
#घोषणा YUV_FORMAT			YUV_FORMAT_420
#घोषणा RGB_FORMAT			RGB_FORMAT_ABGR
#समावेश "yuv_rgb_lsx_func.h"

#पूर्ण_अगर  // SDL_LSX_INTRINSICS

#पूर्ण_अगर // SDL_HAVE_YUV
