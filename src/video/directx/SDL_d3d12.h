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
#अन्तर्भाव "SDL_internal.h"

#यदि_अपरिभाषितम् SDL_D3D12_H
#परिभाषय SDL_D3D12_H

#यदि !(defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES))

/* From the DirectX-Headers build system:
 * "MinGW has RPC headers which define old versions, and complain if D3D
 * headers are included before the RPC headers, since D3D headers were
 * generated with new MIDL and "require" new RPC headers."
 */
#परिभाषय __REQUIRED_RPCNDR_H_VERSION__ 475

// May not be defined in winapifamily.h, can safely be ignored
#यदि_अपरिभाषितम् WINAPI_PARTITION_GAMES
#परिभाषय WINAPI_PARTITION_GAMES 0
#यदि_अन्तः // WINAPI_PARTITION_GAMES

#यदि_परिभाषितम् __CYGWIN__
  // generated header d3d12.h wants to see _WIN32 defined in order to believe it's targeting windows
  #परिभाषय _WIN32 1
#यदि_अन्तः
#परिभाषय COBJMACROS
#अन्तर्भाव "d3d12.h"
#यदि_परिभाषितम् __CYGWIN__
  #अपरिभाषय _WIN32
#यदि_अन्तः
#अन्तर्भाव <dxgi1_6.h>
#अन्तर्भाव <dxgidebug.h>

#परिभाषय D3D_GUID(X) &(X)

#परिभाषय D3D_SAFE_RELEASE(X)      \
    यदि (X) {                     \
        (X)->lpVtbl->Release(X); \
        X = रिक्त;                \
    }

/* Some D3D12 calls are mismatched between Windows/Xbox, so we need to wrap the
 * C function ourselves :(
 */
#परिभाषय D3D_CALL_RET(THIS, FUNC, ...) (THIS)->lpVtbl->FUNC((THIS), ##__VA_ARGS__)

#अन्यथा // !(defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES))

#यदि defined(SDL_PLATFORM_XBOXONE)
#अन्तर्भाव <d3d12_x.h>
#अन्यथा // SDL_PLATFORM_XBOXSERIES
#अन्तर्भाव <d3d12_xs.h>
#यदि_अन्तः

#परिभाषय D3D_GUID(X) (X)

#परिभाषय D3D_SAFE_RELEASE(X) \
    यदि (X) {                \
        (X)->Release();     \
        X = रिक्त;           \
    }

// Older versions of the Xbox GDK may not have this defined
#यदि_अपरिभाषितम् D3_D12_TEXTURE_दत्त_PITCH_ALIGNMENT
#परिभाषय D3_D12_TEXTURE_दत्त_PITCH_ALIGNMENT 256
#यदि_अन्तः
#यदि_अपरिभाषितम् D3D12_RESOURCE_STATE_ALL_SHADER_RESOURCE
#परिभाषय D3D12_RESOURCE_STATE_ALL_SHADER_RESOURCE ((D3_D12_RESOURCE_अवस्थाः) (0x40 | 0x80))
#यदि_अन्तः
#यदि_अपरिभाषितम् D3D12_HEAP_TYPE_GPU_UPLOAD
#परिभाषय D3D12_HEAP_TYPE_GPU_UPLOAD ((D3D12_HEAP_TYPE) 5)
#यदि_अन्तः

// DXGI_PRESENT flags are removed on Xbox
#परिभाषय DXGI_PRESENT_ALLOW_TEARING 0

// Xbox D3D12 does not define the COBJMACROS, so we need to define them ourselves
#अन्तर्भाव "SDL_d3d12_xbox_cmacros.h"

// They don't even define the CMACROS for ID3DBlob, come on man
#परिभाषय ID3_D10_Blob_Get_बफर_Pointer(blob) blob->Get_बफर_Pointer()
#परिभाषय ID3_D10_Blob_Get_बफर_आकार(blob) blob->Get_बफर_आकार()
#परिभाषय ID3D10Blob_Release(blob) blob->Release()

/* Xbox's D3D12 ABI actually varies from Windows, if a function does not exist
 * in the above header then you need to use this instead :(
 */
#परिभाषय D3D_CALL_RET(THIS, FUNC, RETVAL, ...) *(RETVAL) = (THIS)->FUNC(__VA_ARGS__)

#यदि_अन्तः // !(defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES))

#यदि_अन्तः // SDL_D3D12_H
