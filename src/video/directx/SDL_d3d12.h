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
#ಅನ್ತರ್ಭಾವ "SDL_internal.h"

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ SDL_D3D12_H
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_D3D12_H

#ಆದರೆ !(defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES))

/* From the DirectX-Headers build system:
 * "MinGW has RPC headers which define old versions, and complain if D3D
 * headers are included before the RPC headers, since D3D headers were
 * generated with new MIDL and "require" new RPC headers."
 */
#ವ್ಯಾಖ್ಯಾನಿಸು __REQUIRED_RPCNDR_H_VERSION__ 475

// May not be defined in winapifamily.h, can safely be ignored
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ WINAPI_ವಿಭಜನೆ_GAMES
#ವ್ಯಾಖ್ಯಾನಿಸು WINAPI_ವಿಭಜನೆ_GAMES 0
#ಆದರೆ_ಅಂತ್ಯ // WINAPI_PARTITION_GAMES

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __CYGWIN__
  // generated header d3d12.h wants to see _WIN32 defined in order to believe it's targeting windows
  #ವ್ಯಾಖ್ಯಾನಿಸು _WIN32 1
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿಸು COBJMACROS
#ಅನ್ತರ್ಭಾವ "d3d12.h"
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __CYGWIN__
  #ವ್ಯಾಖ್ಯಾನ_ರದ್ದು _WIN32
#ಆದರೆ_ಅಂತ್ಯ
#ಅನ್ತರ್ಭಾವ <dxgi1_6.h>
#ಅನ್ತರ್ಭಾವ <dxgidebug.h>

#ವ್ಯಾಖ್ಯಾನಿಸು D3D_GUID(X) &(X)

#ವ್ಯಾಖ್ಯಾನಿಸು D3_D_ಸುರಕ್ಷಿತ_RELEASE(X)      \
    ಆದರೆ (X) {                     \
        (X)->lpVtbl->Release(X); \
        X = ಖಾಲಿ;                \
    }

/* Some D3D12 calls are mismatched between Windows/Xbox, so we need to wrap the
 * C function ourselves :(
 */
#ವ್ಯಾಖ್ಯಾನಿಸು D3D_CALL_RET(THIS, FUNC, ...) (THIS)->lpVtbl->FUNC((THIS), ##__VA_ARGS__)

#ಇಲ್ಲದಿದ್ದರೆ // !(defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES))

#ಆದರೆ defined(SDL_PLATFORM_XBOXONE)
#ಅನ್ತರ್ಭಾವ <d3d12_x.h>
#ಇಲ್ಲದಿದ್ದರೆ // SDL_PLATFORM_XBOXSERIES
#ಅನ್ತರ್ಭಾವ <d3d12_xs.h>
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿಸು D3D_GUID(X) (X)

#ವ್ಯಾಖ್ಯಾನಿಸು D3_D_ಸುರಕ್ಷಿತ_RELEASE(X) \
    ಆದರೆ (X) {                \
        (X)->Release();     \
        X = ಖಾಲಿ;           \
    }

// Older versions of the Xbox GDK may not have this defined
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ D3_D12_TEXTURE_ದತ್ತಾಂಶ_PITCH_ALIGNMENT
#ವ್ಯಾಖ್ಯಾನಿಸು D3_D12_TEXTURE_ದತ್ತಾಂಶ_PITCH_ALIGNMENT 256
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ D3D12_RESOURCE_STATE_ALL_SHADER_RESOURCE
#ವ್ಯಾಖ್ಯಾನಿಸು D3D12_RESOURCE_STATE_ALL_SHADER_RESOURCE ((D3_D12_RESOURCE_ಸ್ಥಿತಿಗಳು) (0x40 | 0x80))
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ D3_D12_ರಾಶಿ_TYPE_GPU_UPLOAD
#ವ್ಯಾಖ್ಯಾನಿಸು D3_D12_ರಾಶಿ_TYPE_GPU_UPLOAD ((D3_D12_ರಾಶಿ_TYPE) 5)
#ಆದರೆ_ಅಂತ್ಯ

// DXGI_PRESENT flags are removed on Xbox
#ವ್ಯಾಖ್ಯಾನಿಸು DXGI_PRESENT_ALLOW_TEARING 0

// Xbox D3D12 does not define the COBJMACROS, so we need to define them ourselves
#ಅನ್ತರ್ಭಾವ "SDL_d3d12_xbox_cmacros.h"

// They don't even define the CMACROS for ID3DBlob, come on man
#ವ್ಯಾಖ್ಯಾನಿಸು ID3_D10_Blob_Get_ಬಫರ್_ಸೂಚಕ(blob) blob->Get_ಬಫರ್_ಸೂಚಕ()
#ವ್ಯಾಖ್ಯಾನಿಸು ID3_D10_Blob_Get_ಬಫರ್_ಗಾತ್ರ(blob) blob->Get_ಬಫರ್_ಗಾತ್ರ()
#ವ್ಯಾಖ್ಯಾನಿಸು ID3D10Blob_Release(blob) blob->Release()

/* Xbox's D3D12 ABI actually varies from Windows, if a function does not exist
 * in the above header then you need to use this instead :(
 */
#ವ್ಯಾಖ್ಯಾನಿಸು D3D_CALL_RET(THIS, FUNC, RETVAL, ...) *(RETVAL) = (THIS)->FUNC(__VA_ARGS__)

#ಆದರೆ_ಅಂತ್ಯ // !(defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES))

#ಆದರೆ_ಅಂತ್ಯ // SDL_D3D12_H
