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
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_internal.h"

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ SDL_D3D12_H
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_D3D12_H

#ਜੇ !(defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES))

/* From the DirectX-Headers build system:
 * "MinGW has RPC headers which define old versions, and complain if D3D
 * headers are included before the RPC headers, since D3D headers were
 * generated with new MIDL and "require" new RPC headers."
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ __REQUIRED_RPCNDR_H_VERSION__ 475

// May not be defined in winapifamily.h, can safely be ignored
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ WINAPI_ਹਿੱਸੇ_ਕਰੋ_GAMES
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ WINAPI_ਹਿੱਸੇ_ਕਰੋ_GAMES 0
#ਜੇ_ਅੰਤ // WINAPI_PARTITION_GAMES

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __CYGWIN__
  // generated header d3d12.h wants to see _WIN32 defined in order to believe it's targeting windows
  #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ _WIN32 1
#ਜੇ_ਅੰਤ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ COBJMACROS
#ਅਨ੍ਤਰ੍ਭਾਵ "d3d12.h"
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __CYGWIN__
  #ਪਰਿਭਾਸ਼ਾ_ਰੱਦ _WIN32
#ਜੇ_ਅੰਤ
#ਅਨ੍ਤਰ੍ਭਾਵ <dxgi1_6.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <dxgidebug.h>

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ D3D_GUID(X) &(X)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ D3_D_ਸੁਰੱਖਿਅਤ_RELEASE(X)      \
    ਜੇ (X) {                     \
        (X)->lpVtbl->Release(X); \
        X = ਨਿਰਾ;                \
    }

/* Some D3D12 calls are mismatched between Windows/Xbox, so we need to wrap the
 * C function ourselves :(
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ D3D_CALL_RET(THIS, FUNC, ...) (THIS)->lpVtbl->FUNC((THIS), ##__VA_ARGS__)

#ਨਹੀਂਤਾਂ // !(defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES))

#ਜੇ defined(SDL_PLATFORM_XBOXONE)
#ਅਨ੍ਤਰ੍ਭਾਵ <d3d12_x.h>
#ਨਹੀਂਤਾਂ // SDL_PLATFORM_XBOXSERIES
#ਅਨ੍ਤਰ੍ਭਾਵ <d3d12_xs.h>
#ਜੇ_ਅੰਤ

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ D3D_GUID(X) (X)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ D3_D_ਸੁਰੱਖਿਅਤ_RELEASE(X) \
    ਜੇ (X) {                \
        (X)->Release();     \
        X = ਨਿਰਾ;           \
    }

// Older versions of the Xbox GDK may not have this defined
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ D3_D12_TEXTURE_ਅੰਕੜੇ_PITCH_ALIGNMENT
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ D3_D12_TEXTURE_ਅੰਕੜੇ_PITCH_ALIGNMENT 256
#ਜੇ_ਅੰਤ
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ D3D12_RESOURCE_STATE_ALL_SHADER_RESOURCE
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ D3D12_RESOURCE_STATE_ALL_SHADER_RESOURCE ((D3_D12_RESOURCE_ਹਾਲਤਾਂ) (0x40 | 0x80))
#ਜੇ_ਅੰਤ
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ D3_D12_ਢੇਰ_TYPE_GPU_UPLOAD
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ D3_D12_ਢੇਰ_TYPE_GPU_UPLOAD ((D3_D12_ਢੇਰ_TYPE) 5)
#ਜੇ_ਅੰਤ

// DXGI_PRESENT flags are removed on Xbox
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DXGI_PRESENT_ALLOW_TEARING 0

// Xbox D3D12 does not define the COBJMACROS, so we need to define them ourselves
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_d3d12_xbox_cmacros.h"

// They don't even define the CMACROS for ID3DBlob, come on man
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ID3_D10_Blob_Get_ਬਫਰ_ਸੂਚਕ(blob) blob->Get_ਬਫਰ_ਸੂਚਕ()
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ID3_D10_Blob_Get_ਬਫਰ_ਮਾਪ(blob) blob->Get_ਬਫਰ_ਮਾਪ()
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ID3D10Blob_Release(blob) blob->Release()

/* Xbox's D3D12 ABI actually varies from Windows, if a function does not exist
 * in the above header then you need to use this instead :(
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ D3D_CALL_RET(THIS, FUNC, RETVAL, ...) *(RETVAL) = (THIS)->FUNC(__VA_ARGS__)

#ਜੇ_ਅੰਤ // !(defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES))

#ਜੇ_ਅੰਤ // SDL_D3D12_H
