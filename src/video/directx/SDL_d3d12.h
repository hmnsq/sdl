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

#جے_بنا_تعریف SDL_D3D12_H
#تعریف_کرو SDL_D3D12_H

#إذا !(defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES))

/* From the DirectX-Headers build system:
 * "MinGW has RPC headers which define old versions, and complain if D3D
 * headers are included before the RPC headers, since D3D headers were
 * generated with new MIDL and "require" new RPC headers."
 */
#تعریف_کرو __REQUIRED_RPCNDR_H_VERSION__ 475

// May not be defined in winapifamily.h, can safely be ignored
#جے_بنا_تعریف WINAPI_حصے_کرو_GAMES
#تعریف_کرو WINAPI_حصے_کرو_GAMES 0
#جے_انت // WINAPI_PARTITION_GAMES

#جے_تعریف_شدہ __CYGWIN__
  // generated header d3d12.h wants to see _WIN32 defined in order to believe it's targeting windows
  #تعریف_کرو _WIN32 1
#جے_انت
#تعریف_کرو COBJMACROS
#ضمن "d3d12.h"
#جے_تعریف_شدہ __CYGWIN__
  #تعریف_رد _WIN32
#جے_انت
#ضمن <dxgi1_6.h>
#ضمن <dxgidebug.h>

#تعریف_کرو D3D_GUID(X) &(X)

#تعریف_کرو D3_D_محفوظ_RELEASE(X)      \
    إذا (X) {                     \
        (X)->lpVtbl->Release(X); \
        X = عدم;                \
    }

/* Some D3D12 calls are mismatched between Windows/Xbox, so we need to wrap the
 * C function ourselves :(
 */
#تعریف_کرو D3D_CALL_RET(THIS, FUNC, ...) (THIS)->lpVtbl->FUNC((THIS), ##__VA_ARGS__)

#وإلا // !(defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES))

#إذا defined(SDL_PLATFORM_XBOXONE)
#ضمن <d3d12_x.h>
#وإلا // SDL_PLATFORM_XBOXSERIES
#ضمن <d3d12_xs.h>
#جے_انت

#تعریف_کرو D3D_GUID(X) (X)

#تعریف_کرو D3_D_محفوظ_RELEASE(X) \
    إذا (X) {                \
        (X)->Release();     \
        X = عدم;           \
    }

// Older versions of the Xbox GDK may not have this defined
#جے_بنا_تعریف D3_D12_TEXTURE_انکڑے_PITCH_ALIGNMENT
#تعریف_کرو D3_D12_TEXTURE_انکڑے_PITCH_ALIGNMENT 256
#جے_انت
#جے_بنا_تعریف D3D12_RESOURCE_STATE_ALL_SHADER_RESOURCE
#تعریف_کرو D3D12_RESOURCE_STATE_ALL_SHADER_RESOURCE ((D3_D12_RESOURCE_حالتاں) (0x40 | 0x80))
#جے_انت
#جے_بنا_تعریف D3_D12_ڈھیر_TYPE_GPU_UPLOAD
#تعریف_کرو D3_D12_ڈھیر_TYPE_GPU_UPLOAD ((D3_D12_ڈھیر_TYPE) 5)
#جے_انت

// DXGI_PRESENT flags are removed on Xbox
#تعریف_کرو DXGI_PRESENT_ALLOW_TEARING 0

// Xbox D3D12 does not define the COBJMACROS, so we need to define them ourselves
#ضمن "SDL_d3d12_xbox_cmacros.h"

// They don't even define the CMACROS for ID3DBlob, come on man
#تعریف_کرو ID3_D10_Blob_Get_بفر_اشارہ_گر(blob) blob->Get_بفر_اشارہ_گر()
#تعریف_کرو ID3_D10_Blob_Get_بفر_ناپ(blob) blob->Get_بفر_ناپ()
#تعریف_کرو ID3D10Blob_Release(blob) blob->Release()

/* Xbox's D3D12 ABI actually varies from Windows, if a function does not exist
 * in the above header then you need to use this instead :(
 */
#تعریف_کرو D3D_CALL_RET(THIS, FUNC, RETVAL, ...) *(RETVAL) = (THIS)->FUNC(__VA_ARGS__)

#جے_انت // !(defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES))

#جے_انت // SDL_D3D12_H
