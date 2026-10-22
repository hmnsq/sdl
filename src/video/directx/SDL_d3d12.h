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

#جيڪڏهن_وصف_نه_ٿيل SDL_D3D12_H
#وصف_ڪريو SDL_D3D12_H

#إذا !(defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES))

/* From the DirectX-Headers build system:
 * "MinGW has RPC headers which define old versions, and complain if D3D
 * headers are included before the RPC headers, since D3D headers were
 * generated with new MIDL and "require" new RPC headers."
 */
#وصف_ڪريو __REQUIRED_RPCNDR_H_VERSION__ 475

// May not be defined in winapifamily.h, can safely be ignored
#جيڪڏهن_وصف_نه_ٿيل WINAPI_حصا_ڪريو_GAMES
#وصف_ڪريو WINAPI_حصا_ڪريو_GAMES 0
#جيڪڏهن_پورو // WINAPI_PARTITION_GAMES

#جيڪڏهن_وصف_ٿيل __CYGWIN__
  // generated header d3d12.h wants to see _WIN32 defined in order to believe it's targeting windows
  #وصف_ڪريو _WIN32 1
#جيڪڏهن_پورو
#وصف_ڪريو COBJMACROS
#ضمن "d3d12.h"
#جيڪڏهن_وصف_ٿيل __CYGWIN__
  #وصف_رد _WIN32
#جيڪڏهن_پورو
#ضمن <dxgi1_6.h>
#ضمن <dxgidebug.h>

#وصف_ڪريو D3D_GUID(X) &(X)

#وصف_ڪريو D3_D_محفوظ_RELEASE(X)      \
    إذا (X) {                     \
        (X)->lpVtbl->Release(X); \
        X = عدم;                \
    }

/* Some D3D12 calls are mismatched between Windows/Xbox, so we need to wrap the
 * C function ourselves :(
 */
#وصف_ڪريو D3D_CALL_RET(THIS, FUNC, ...) (THIS)->lpVtbl->FUNC((THIS), ##__VA_ARGS__)

#وإلا // !(defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES))

#إذا defined(SDL_PLATFORM_XBOXONE)
#ضمن <d3d12_x.h>
#وإلا // SDL_PLATFORM_XBOXSERIES
#ضمن <d3d12_xs.h>
#جيڪڏهن_پورو

#وصف_ڪريو D3D_GUID(X) (X)

#وصف_ڪريو D3_D_محفوظ_RELEASE(X) \
    إذا (X) {                \
        (X)->Release();     \
        X = عدم;           \
    }

// Older versions of the Xbox GDK may not have this defined
#جيڪڏهن_وصف_نه_ٿيل D3_D12_TEXTURE_معلومات_PITCH_ALIGNMENT
#وصف_ڪريو D3_D12_TEXTURE_معلومات_PITCH_ALIGNMENT 256
#جيڪڏهن_پورو
#جيڪڏهن_وصف_نه_ٿيل D3D12_RESOURCE_STATE_ALL_SHADER_RESOURCE
#وصف_ڪريو D3D12_RESOURCE_STATE_ALL_SHADER_RESOURCE ((D3_D12_RESOURCE_حالتون) (0x40 | 0x80))
#جيڪڏهن_پورو
#جيڪڏهن_وصف_نه_ٿيل D3_D12_ڍير_TYPE_GPU_UPLOAD
#وصف_ڪريو D3_D12_ڍير_TYPE_GPU_UPLOAD ((D3_D12_ڍير_TYPE) 5)
#جيڪڏهن_پورو

// DXGI_PRESENT flags are removed on Xbox
#وصف_ڪريو DXGI_PRESENT_ALLOW_TEARING 0

// Xbox D3D12 does not define the COBJMACROS, so we need to define them ourselves
#ضمن "SDL_d3d12_xbox_cmacros.h"

// They don't even define the CMACROS for ID3DBlob, come on man
#وصف_ڪريو ID3_D10_Blob_Get_بفر_اشارو(blob) blob->Get_بفر_اشارو()
#وصف_ڪريو ID3_D10_Blob_Get_بفر_سائيز(blob) blob->Get_بفر_سائيز()
#وصف_ڪريو ID3D10Blob_Release(blob) blob->Release()

/* Xbox's D3D12 ABI actually varies from Windows, if a function does not exist
 * in the above header then you need to use this instead :(
 */
#وصف_ڪريو D3D_CALL_RET(THIS, FUNC, RETVAL, ...) *(RETVAL) = (THIS)->FUNC(__VA_ARGS__)

#جيڪڏهن_پورو // !(defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES))

#جيڪڏهن_پورو // SDL_D3D12_H
