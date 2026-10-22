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
#ضمن "SDL_internal.h"

#اگر_تعریف_نشده SDL_D3D12_H
#تعریف_کن SDL_D3D12_H

#إذا !(defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES))

/* From the DirectX-Headers build system:
 * "MinGW has RPC headers which define old versions, and complain if D3D
 * headers are included before the RPC headers, since D3D headers were
 * generated with new MIDL and "require" new RPC headers."
 */
#تعریف_کن __REQUIRED_RPCNDR_H_VERSION__ 475

// May not be defined in winapifamily.h, can safely be ignored
#اگر_تعریف_نشده WINAPI_افراز_GAMES
#تعریف_کن WINAPI_افراز_GAMES 0
#پایان_اگر // WINAPI_PARTITION_GAMES

#اگر_تعریف_شده __CYGWIN__
  // generated header d3d12.h wants to see _WIN32 defined in order to believe it's targeting windows
  #تعریف_کن _WIN32 1
#پایان_اگر
#تعریف_کن COBJMACROS
#ضمن "d3d12.h"
#اگر_تعریف_شده __CYGWIN__
  #لغو_تعریف _WIN32
#پایان_اگر
#ضمن <dxgi1_6.h>
#ضمن <dxgidebug.h>

#تعریف_کن D3D_GUID(X) &(X)

#تعریف_کن D3_D_امن_RELEASE(X)      \
    إذا (X) {                     \
        (X)->lpVtbl->Release(X); \
        X = عدم;                \
    }

/* Some D3D12 calls are mismatched between Windows/Xbox, so we need to wrap the
 * C function ourselves :(
 */
#تعریف_کن D3D_CALL_RET(THIS, FUNC, ...) (THIS)->lpVtbl->FUNC((THIS), ##__VA_ARGS__)

#وإلا // !(defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES))

#إذا defined(SDL_PLATFORM_XBOXONE)
#ضمن <d3d12_x.h>
#وإلا // SDL_PLATFORM_XBOXSERIES
#ضمن <d3d12_xs.h>
#پایان_اگر

#تعریف_کن D3D_GUID(X) (X)

#تعریف_کن D3_D_امن_RELEASE(X) \
    إذا (X) {                \
        (X)->Release();     \
        X = عدم;           \
    }

// Older versions of the Xbox GDK may not have this defined
#اگر_تعریف_نشده D3_D12_TEXTURE_داده_PITCH_ALIGNMENT
#تعریف_کن D3_D12_TEXTURE_داده_PITCH_ALIGNMENT 256
#پایان_اگر
#اگر_تعریف_نشده D3D12_RESOURCE_STATE_ALL_SHADER_RESOURCE
#تعریف_کن D3D12_RESOURCE_STATE_ALL_SHADER_RESOURCE ((D3_D12_RESOURCE_حالتها) (0x40 | 0x80))
#پایان_اگر
#اگر_تعریف_نشده D3_D12_انباشته_TYPE_GPU_UPLOAD
#تعریف_کن D3_D12_انباشته_TYPE_GPU_UPLOAD ((D3_D12_انباشته_TYPE) 5)
#پایان_اگر

// DXGI_PRESENT flags are removed on Xbox
#تعریف_کن DXGI_PRESENT_ALLOW_TEARING 0

// Xbox D3D12 does not define the COBJMACROS, so we need to define them ourselves
#ضمن "SDL_d3d12_xbox_cmacros.h"

// They don't even define the CMACROS for ID3DBlob, come on man
#تعریف_کن ID3_D10_Blob_Get_میانگیر_اشاره_گر(blob) blob->Get_میانگیر_اشاره_گر()
#تعریف_کن ID3_D10_Blob_Get_میانگیر_اندازه(blob) blob->Get_میانگیر_اندازه()
#تعریف_کن ID3D10Blob_Release(blob) blob->Release()

/* Xbox's D3D12 ABI actually varies from Windows, if a function does not exist
 * in the above header then you need to use this instead :(
 */
#تعریف_کن D3D_CALL_RET(THIS, FUNC, RETVAL, ...) *(RETVAL) = (THIS)->FUNC(__VA_ARGS__)

#پایان_اگر // !(defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES))

#پایان_اگر // SDL_D3D12_H
