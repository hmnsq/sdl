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
#అన్తర్భావ "SDL_internal.h"

#నిర్వచితం_కాకపోతే SDL_D3D12_H
#నిర్వచించు SDL_D3D12_H

#ఒకవేళ !(defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES))

/* From the DirectX-Headers build system:
 * "MinGW has RPC headers which define old versions, and complain if D3D
 * headers are included before the RPC headers, since D3D headers were
 * generated with new MIDL and "require" new RPC headers."
 */
#నిర్వచించు __REQUIRED_RPCNDR_H_VERSION__ 475

// May not be defined in winapifamily.h, can safely be ignored
#నిర్వచితం_కాకపోతే WINAPI_విభజన_GAMES
#నిర్వచించు WINAPI_విభజన_GAMES 0
#అయితే_ముగింపు // WINAPI_PARTITION_GAMES

#నిర్వచితమైతే __CYGWIN__
  // generated header d3d12.h wants to see _WIN32 defined in order to believe it's targeting windows
  #నిర్వచించు _WIN32 1
#అయితే_ముగింపు
#నిర్వచించు COBJMACROS
#అన్తర్భావ "d3d12.h"
#నిర్వచితమైతే __CYGWIN__
  #నిర్వచనం_రద్దు _WIN32
#అయితే_ముగింపు
#అన్తర్భావ <dxgi1_6.h>
#అన్తర్భావ <dxgidebug.h>

#నిర్వచించు D3D_GUID(X) &(X)

#నిర్వచించు D3_D_సురక్షిత_RELEASE(X)      \
    ఒకవేళ (X) {                     \
        (X)->lpVtbl->Release(X); \
        X = ఖాళీ;                \
    }

/* Some D3D12 calls are mismatched between Windows/Xbox, so we need to wrap the
 * C function ourselves :(
 */
#నిర్వచించు D3D_CALL_RET(THIS, FUNC, ...) (THIS)->lpVtbl->FUNC((THIS), ##__VA_ARGS__)

#లేకపోతే // !(defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES))

#ఒకవేళ defined(SDL_PLATFORM_XBOXONE)
#అన్తర్భావ <d3d12_x.h>
#లేకపోతే // SDL_PLATFORM_XBOXSERIES
#అన్తర్భావ <d3d12_xs.h>
#అయితే_ముగింపు

#నిర్వచించు D3D_GUID(X) (X)

#నిర్వచించు D3_D_సురక్షిత_RELEASE(X) \
    ఒకవేళ (X) {                \
        (X)->Release();     \
        X = ఖాళీ;           \
    }

// Older versions of the Xbox GDK may not have this defined
#నిర్వచితం_కాకపోతే D3_D12_TEXTURE_దత్తాంశం_PITCH_ALIGNMENT
#నిర్వచించు D3_D12_TEXTURE_దత్తాంశం_PITCH_ALIGNMENT 256
#అయితే_ముగింపు
#నిర్వచితం_కాకపోతే D3D12_RESOURCE_STATE_ALL_SHADER_RESOURCE
#నిర్వచించు D3D12_RESOURCE_STATE_ALL_SHADER_RESOURCE ((D3_D12_RESOURCE_స్థితులు) (0x40 | 0x80))
#అయితే_ముగింపు
#నిర్వచితం_కాకపోతే D3_D12_కుప్ప_TYPE_GPU_UPLOAD
#నిర్వచించు D3_D12_కుప్ప_TYPE_GPU_UPLOAD ((D3_D12_కుప్ప_TYPE) 5)
#అయితే_ముగింపు

// DXGI_PRESENT flags are removed on Xbox
#నిర్వచించు DXGI_PRESENT_ALLOW_TEARING 0

// Xbox D3D12 does not define the COBJMACROS, so we need to define them ourselves
#అన్తర్భావ "SDL_d3d12_xbox_cmacros.h"

// They don't even define the CMACROS for ID3DBlob, come on man
#నిర్వచించు ID3_D10_Blob_Get_బఫరు_సూచిక(blob) blob->Get_బఫరు_సూచిక()
#నిర్వచించు ID3_D10_Blob_Get_బఫరు_కొలత(blob) blob->Get_బఫరు_కొలత()
#నిర్వచించు ID3D10Blob_Release(blob) blob->Release()

/* Xbox's D3D12 ABI actually varies from Windows, if a function does not exist
 * in the above header then you need to use this instead :(
 */
#నిర్వచించు D3D_CALL_RET(THIS, FUNC, RETVAL, ...) *(RETVAL) = (THIS)->FUNC(__VA_ARGS__)

#అయితే_ముగింపు // !(defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES))

#అయితే_ముగింపు // SDL_D3D12_H
