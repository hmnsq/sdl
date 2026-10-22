/*
  Simple DirectMedia Layer
  Copyright (C) 1997-2026 Sam Lantinga <slouken@libsdl.org>

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/
#شامل "SDL_internal.h"

#اگر_غیر_تعریف_شدہ SDL_D3D12_H
#تعریف_کرو SDL_D3D12_H

#اگر !(defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES))

/* From the DirectX-Headers build system:
 * "MinGW has RPC headers which define old versions, and complain if D3D
 * headers are included before the RPC headers, since D3D headers were
 * generated with new MIDL and "require" new RPC headers."
 */
#تعریف_کرو __REQUIRED_RPCNDR_H_VERSION__ 475

// May not be defined in winapifamily.h, can safely be ignored
#اگر_غیر_تعریف_شدہ WINAPI_تقسیم_GAMES
#تعریف_کرو WINAPI_تقسیم_GAMES 0
#اگر_ختم // WINAPI_PARTITION_GAMES

#اگر_تعریف_شدہ __CYGWIN__
  // generated header d3d12.h wants to see _WIN32 defined in order to believe it's targeting windows
  #تعریف_کرو _WIN32 1
#اگر_ختم
#تعریف_کرو COBJMACROS
#شامل "d3d12.h"
#اگر_تعریف_شدہ __CYGWIN__
  #تعریف_منسوخ _WIN32
#اگر_ختم
#شامل <dxgi1_6.h>
#شامل <dxgidebug.h>

#تعریف_کرو D3D_GUID(X) &(X)

#تعریف_کرو D3_D_محفوظ_RELEASE(X)      \
    اگر (X) {                     \
        (X)->lpVtbl->Release(X); \
        X = تہی;                \
    }

/* Some D3D12 calls are mismatched between Windows/Xbox, so we need to wrap the
 * C function ourselves :(
 */
#تعریف_کرو D3D_CALL_RET(THIS, FUNC, ...) (THIS)->lpVtbl->FUNC((THIS), ##__VA_ARGS__)

#ورنہ // !(defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES))

#اگر defined(SDL_PLATFORM_XBOXONE)
#شامل <d3d12_x.h>
#ورنہ // SDL_PLATFORM_XBOXSERIES
#شامل <d3d12_xs.h>
#اگر_ختم

#تعریف_کرو D3D_GUID(X) (X)

#تعریف_کرو D3_D_محفوظ_RELEASE(X) \
    اگر (X) {                \
        (X)->Release();     \
        X = تہی;           \
    }

// Older versions of the Xbox GDK may not have this defined
#اگر_غیر_تعریف_شدہ D3_D12_TEXTURE_ڈیٹا_PITCH_ALIGNMENT
#تعریف_کرو D3_D12_TEXTURE_ڈیٹا_PITCH_ALIGNMENT 256
#اگر_ختم
#اگر_غیر_تعریف_شدہ D3D12_RESOURCE_STATE_ALL_SHADER_RESOURCE
#تعریف_کرو D3D12_RESOURCE_STATE_ALL_SHADER_RESOURCE ((D3_D12_RESOURCE_حالتیں) (0x40 | 0x80))
#اگر_ختم
#اگر_غیر_تعریف_شدہ D3_D12_ڈھیر_TYPE_GPU_UPLOAD
#تعریف_کرو D3_D12_ڈھیر_TYPE_GPU_UPLOAD ((D3_D12_ڈھیر_TYPE) 5)
#اگر_ختم

// DXGI_PRESENT flags are removed on Xbox
#تعریف_کرو DXGI_PRESENT_ALLOW_TEARING 0

// Xbox D3D12 does not define the COBJMACROS, so we need to define them ourselves
#شامل "SDL_d3d12_xbox_cmacros.h"

// They don't even define the CMACROS for ID3DBlob, come on man
#تعریف_کرو ID3_D10_Blob_Get_بفر_اشارہ_گر(blob) blob->Get_بفر_اشارہ_گر()
#تعریف_کرو ID3_D10_Blob_Get_بفر_سائز(blob) blob->Get_بفر_سائز()
#تعریف_کرو ID3D10Blob_Release(blob) blob->Release()

/* Xbox's D3D12 ABI actually varies from Windows, if a function does not exist
 * in the above header then you need to use this instead :(
 */
#تعریف_کرو D3D_CALL_RET(THIS, FUNC, RETVAL, ...) *(RETVAL) = (THIS)->FUNC(__VA_ARGS__)

#اگر_ختم // !(defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES))

#اگر_ختم // SDL_D3D12_H
