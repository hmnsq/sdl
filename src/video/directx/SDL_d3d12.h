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
#समावेश "SDL_internal.h"

#अगर_अघोषित SDL_D3D12_H
#घोषणा SDL_D3D12_H

#अगर !(defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES))

/* From the DirectX-Headers build system:
 * "MinGW has RPC headers which define old versions, and complain if D3D
 * headers are included before the RPC headers, since D3D headers were
 * generated with new MIDL and "require" new RPC headers."
 */
#घोषणा __REQUIRED_RPCNDR_H_VERSION__ 475

// May not be defined in winapifamily.h, can safely be ignored
#अगर_अघोषित WINAPI_PARTITION_GAMES
#घोषणा WINAPI_PARTITION_GAMES 0
#पूर्ण_अगर // WINAPI_PARTITION_GAMES

#अगर_घोषित __CYGWIN__
  // generated header d3d12.h wants to see _WIN32 defined in order to believe it's targeting windows
  #घोषणा _WIN32 1
#पूर्ण_अगर
#घोषणा COBJMACROS
#समावेश "d3d12.h"
#अगर_घोषित __CYGWIN__
  #अघोषित _WIN32
#पूर्ण_अगर
#समावेश <dxgi1_6.h>
#समावेश <dxgidebug.h>

#घोषणा D3D_GUID(X) &(X)

#घोषणा D3D_SAFE_RELEASE(X)      \
    अगर (X) {                     \
        (X)->lpVtbl->Release(X); \
        X = शून्य;                \
    }

/* Some D3D12 calls are mismatched between Windows/Xbox, so we need to wrap the
 * C function ourselves :(
 */
#घोषणा D3D_CALL_RET(THIS, FUNC, ...) (THIS)->lpVtbl->FUNC((THIS), ##__VA_ARGS__)

#अन्यथा // !(defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES))

#अगर defined(SDL_PLATFORM_XBOXONE)
#समावेश <d3d12_x.h>
#अन्यथा // SDL_PLATFORM_XBOXSERIES
#समावेश <d3d12_xs.h>
#पूर्ण_अगर

#घोषणा D3D_GUID(X) (X)

#घोषणा D3D_SAFE_RELEASE(X) \
    अगर (X) {                \
        (X)->Release();     \
        X = शून्य;           \
    }

// Older versions of the Xbox GDK may not have this defined
#अगर_अघोषित D3_D12_TEXTURE_तथ्य_PITCH_ALIGNMENT
#घोषणा D3_D12_TEXTURE_तथ्य_PITCH_ALIGNMENT 256
#पूर्ण_अगर
#अगर_अघोषित D3D12_RESOURCE_STATE_ALL_SHADER_RESOURCE
#घोषणा D3D12_RESOURCE_STATE_ALL_SHADER_RESOURCE ((D3D12_RESOURCE_STATES) (0x40 | 0x80))
#पूर्ण_अगर
#अगर_अघोषित D3D12_HEAP_TYPE_GPU_UPLOAD
#घोषणा D3D12_HEAP_TYPE_GPU_UPLOAD ((D3D12_HEAP_TYPE) 5)
#पूर्ण_अगर

// DXGI_PRESENT flags are removed on Xbox
#घोषणा DXGI_PRESENT_ALLOW_TEARING 0

// Xbox D3D12 does not define the COBJMACROS, so we need to define them ourselves
#समावेश "SDL_d3d12_xbox_cmacros.h"

// They don't even define the CMACROS for ID3DBlob, come on man
#घोषणा ID3_D10_Blob_Get_बफर_Pointer(blob) blob->Get_बफर_Pointer()
#घोषणा ID3_D10_Blob_Get_बफर_आकार(blob) blob->Get_बफर_आकार()
#घोषणा ID3D10Blob_Release(blob) blob->Release()

/* Xbox's D3D12 ABI actually varies from Windows, if a function does not exist
 * in the above header then you need to use this instead :(
 */
#घोषणा D3D_CALL_RET(THIS, FUNC, RETVAL, ...) *(RETVAL) = (THIS)->FUNC(__VA_ARGS__)

#पूर्ण_अगर // !(defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES))

#पूर्ण_अगर // SDL_D3D12_H
