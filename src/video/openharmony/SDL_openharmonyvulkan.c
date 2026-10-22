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

/*
 * Copied from the Android implementation, which was done by Mark Callow,
 * www.edgewise-consulting.com, and originally based on Jacob Lifshay's SDL_x11vulkan.h.
 */

#అన్తర్భావ "SDL_internal.h"

#ఒకవేళ defined(SDL_VIDEO_VULKAN) && defined(SDL_VIDEO_DRIVER_OPENHARMONY)

#అన్తర్భావ "../SDL_vulkan_internal.h"

#అన్తర్భావ "SDL_openharmonyvideo.h"
#అన్తర్భావ "SDL_openharmonywindow.h"

#అన్తర్భావ "SDL_openharmonyvulkan.h"


bool OPENHARMONY_Vulkan_ఎక్కించు_Library(SDL_VideoDevice *_this, స్థిరరాశి అక్షరం *మార్గం)
{
    VkExtensionProperties *extensions = ఖాళీ;
    Uint32 extension_లెక్క = 0;
    bool hasSurfaceExtension = false;
    bool hasOHOSSurfaceExtension = false;
    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr = ఖాళీ;

    ఒకవేళ (_this->vulkan_config.loader_handle) {
        తిరిగి SDL_సమితి_Error("Vulkan already loaded");
    }

    // Load the Vulkan loader library
    ఒకవేళ (!మార్గం) {
        మార్గం = SDL_GetHint(SDL_HINT_VULKAN_LIBRARY);
        ఒకవేళ (!మార్గం) {
            మార్గం = "libvulkan.so";
        }
    }

    SDL_SharedObject *lib = SDL_ఎక్కించు_Object(మార్గం);
    _this->vulkan_config.loader_handle = lib;
    ఒకవేళ (!lib) {
        తిరిగి false;
    }

    SDL_strlcpy(_this->vulkan_config.loader_మార్గం, మార్గం, పరిమాణం (_this->vulkan_config.loader_మార్గం));
    vkGetInstanceProcAddr = (PFN_vkGetInstanceProcAddr) SDL_ఎక్కించు_Function(lib, "vkGetInstanceProcAddr");
    ఒకవేళ (!vkGetInstanceProcAddr) {
        వెళ్ళు fail;
    }

    _this->vulkan_config.vkGetInstanceProcAddr = (శూన్య *)vkGetInstanceProcAddr;
    _this->vulkan_config.vkEnumerateInstanceExtensionProperties = (శూన్య *)((PFN_vkGetInstanceProcAddr)_this->vulkan_config.vkGetInstanceProcAddr)(VK_NULL_HANDLE, "vkEnumerateInstanceExtensionProperties");
    ఒకవేళ (!_this->vulkan_config.vkEnumerateInstanceExtensionProperties) {
        వెళ్ళు fail;
    }

    extensions = SDL_Vulkan_CreateInstanceExtensionsList((PFN_vkEnumerateInstanceExtensionProperties) _this->vulkan_config.vkEnumerateInstanceExtensionProperties, &extension_లెక్క);
    ఒకవేళ (!extensions) {
        వెళ్ళు fail;
    }

    కొరకు (Uint32 i = 0; i < extension_లెక్క; i++) {
        ఒకవేళ (SDL_strcmp(VK_KHR_SURFACE_EXTENSION_NAME, extensions[i].extensionName) == 0) {
            hasSurfaceExtension = true;
        } లేకపోతే ఒకవేళ (SDL_strcmp(VK_OHOS_SURFACE_EXTENSION_NAME, extensions[i].extensionName) == 0) {
            hasOHOSSurfaceExtension = true;
        }
    }

    SDL_free(extensions);

    ఒకవేళ (!hasSurfaceExtension) {
        SDL_సమితి_Error("Installed Vulkan doesn't implement the " VK_KHR_SURFACE_EXTENSION_NAME " extension");
        వెళ్ళు fail;
    } లేకపోతే ఒకవేళ (!hasOHOSSurfaceExtension) {
        SDL_సమితి_Error("Installed Vulkan doesn't implement the " VK_OHOS_SURFACE_EXTENSION_NAME " extension");
        వెళ్ళు fail;
    }

    తిరిగి true;

fail:
    SDL_UnloadObject(_this->vulkan_config.loader_handle);
    _this->vulkan_config.loader_handle = ఖాళీ;
    తిరిగి false;
}

శూన్య OPENHARMONY_Vulkan_UnloadLibrary(SDL_VideoDevice *_this)
{
    ఒకవేళ (_this->vulkan_config.loader_handle) {
        SDL_UnloadObject(_this->vulkan_config.loader_handle);
        _this->vulkan_config.loader_handle = ఖాళీ;
    }
}

అక్షరం స్థిరరాశి * స్థిరరాశి *OPENHARMONY_Vulkan_GetInstanceExtensions(SDL_VideoDevice *_this, Uint32 *లెక్క)
{
    స్థిర స్థిరరాశి అక్షరం *స్థిరరాశి extensionsForOpenHarmony[] = {
        VK_KHR_SURFACE_EXTENSION_NAME, VK_OHOS_SURFACE_EXTENSION_NAME
    };
    ఒకవేళ (లెక్క) {
        *లెక్క = SDL_arraysize(extensionsForOpenHarmony);
    }
    తిరిగి extensionsForOpenHarmony;
}

bool OPENHARMONY_Vulkan_CreateSurface(SDL_VideoDevice *_this,
                                 SDL_కిటికీ *కిటికీ,
                                 VkInstance instance,
                                 స్థిరరాశి నిర్మాణం Vk_కేటాయింపు_Callbacks *allocator,
                                 VkSurfaceKHR *surface)
{
    SDL_కిటికీ_దత్తాంశం *కిటికీ_దత్తాంశం = కిటికీ->అంతర్గత;
    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr = (PFN_vkGetInstanceProcAddr)_this->vulkan_config.vkGetInstanceProcAddr;
    PFN_vkCreateSurfaceOHOS vkCreateSurfaceOHOS = (PFN_vkCreateSurfaceOHOS ) vkGetInstanceProcAddr(instance, "vkCreateSurfaceOHOS");
    VkSurfaceCreateInfoOHOS createInfo;
    Vk_ఫలితం ఫలితం;

    ఒకవేళ (!_this->vulkan_config.loader_handle) {
        తిరిగి SDL_సమితి_Error("Vulkan is not loaded");
    }

    ఒకవేళ (!vkCreateSurfaceOHOS) {
        తిరిగి SDL_సమితి_Error(VK_OHOS_SURFACE_EXTENSION_NAME " extension is not enabled in the Vulkan instance.");
    }

    SDL_zero(createInfo);
    createInfo.sType = VK_STRUCTURE_TYPE_SURFACE_CREATE_INFO_OHOS;
    createInfo.p_తదుపరి = ఖాళీ;
    createInfo.flags = 0;
    createInfo.కిటికీ = (OHNative_కిటికీ *) కిటికీ_దత్తాంశం->native_కిటికీ;
    ఫలితం = vkCreateSurfaceOHOS(instance, &createInfo, allocator, surface);
    ఒకవేళ (ఫలితం != VK_SUCCESS) {
        ఒకవేళ (ఫలితం == VK_ERROR_NATIVE_కిటికీ_లోపల_USE_KHR) {
            తిరిగి SDL_సమితి_Error("vkCreateSurfaceOHOS failed: %s, was the window created with SDL_WINDOW_VULKAN?", SDL_Vulkan_Get_ఫలితం_String(ఫలితం));
        } లేకపోతే {
            తిరిగి SDL_సమితి_Error("vkCreateSurfaceOHOS failed: %s", SDL_Vulkan_Get_ఫలితం_String(ఫలితం));
        }
    }
    తిరిగి true;
}

శూన్య OPENHARMONY_Vulkan_DestroySurface(SDL_VideoDevice *_this,
                                   VkInstance instance,
                                   VkSurfaceKHR surface,
                                   స్థిరరాశి నిర్మాణం Vk_కేటాయింపు_Callbacks *allocator)
{
    ఒకవేళ (_this->vulkan_config.loader_handle) {
        SDL_Vulkan_Destroy_Surface_అంతర్గత(_this->vulkan_config.vkGetInstanceProcAddr, instance, surface, allocator);
    }
}

#అయితే_ముగింపు

