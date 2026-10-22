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

#ضمن "SDL_vulkan_internal.h"

#اگر_تعریف_شده SDL_VIDEO_VULKAN

ثابت حرف *SDL_Vulkan_Get_نتیجه_String(Vk_نتیجه نتیجه)
{
    بدل ((صحيح)نتیجه) {
    حالة VK_SUCCESS:
        أرجع "VK_SUCCESS";
    حالة VK_NOT_READY:
        أرجع "VK_NOT_READY";
    حالة VK_TIMEOUT:
        أرجع "VK_TIMEOUT";
    حالة VK_EVENT_مجموعه:
        أرجع "VK_EVENT_SET";
    حالة VK_EVENT_RESET:
        أرجع "VK_EVENT_RESET";
    حالة VK_INCOMPLETE:
        أرجع "VK_INCOMPLETE";
    حالة VK_ERROR_بیرون_از_HOST_حافظه:
        أرجع "VK_ERROR_OUT_OF_HOST_MEMORY";
    حالة VK_ERROR_بیرون_از_DEVICE_حافظه:
        أرجع "VK_ERROR_OUT_OF_DEVICE_MEMORY";
    حالة VK_ERROR_INITIALIZATION_FAILED:
        أرجع "VK_ERROR_INITIALIZATION_FAILED";
    حالة VK_ERROR_DEVICE_گمشده:
        أرجع "VK_ERROR_DEVICE_LOST";
    حالة VK_ERROR_حافظه_MAP_FAILED:
        أرجع "VK_ERROR_MEMORY_MAP_FAILED";
    حالة VK_ERROR_LAYER_NOT_PRESENT:
        أرجع "VK_ERROR_LAYER_NOT_PRESENT";
    حالة VK_ERROR_EXTENSION_NOT_PRESENT:
        أرجع "VK_ERROR_EXTENSION_NOT_PRESENT";
    حالة VK_ERROR_FEATURE_NOT_PRESENT:
        أرجع "VK_ERROR_FEATURE_NOT_PRESENT";
    حالة VK_ERROR_INCOMPATIBLE_DRIVER:
        أرجع "VK_ERROR_INCOMPATIBLE_DRIVER";
    حالة VK_ERROR_TOO_MANY_OBJECTS:
        أرجع "VK_ERROR_TOO_MANY_OBJECTS";
    حالة VK_ERROR_FORMAT_NOT_SUPPORTED:
        أرجع "VK_ERROR_FORMAT_NOT_SUPPORTED";
    حالة VK_ERROR_FRAGMENTED_POOL:
        أرجع "VK_ERROR_FRAGMENTED_POOL";
    حالة VK_ERROR_UNKNOWN:
        أرجع "VK_ERROR_UNKNOWN";
    حالة VK_ERROR_بیرون_از_POOL_حافظه:
        أرجع "VK_ERROR_OUT_OF_POOL_MEMORY";
    حالة VK_ERROR_INVALID_EXTERNAL_HANDLE:
        أرجع "VK_ERROR_INVALID_EXTERNAL_HANDLE";
    حالة VK_ERROR_FRAGMENTATION:
        أرجع "VK_ERROR_FRAGMENTATION";
    حالة VK_ERROR_INVALID_OPAQUE_CAPTURE_آدرس:
        أرجع "VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS";
    حالة VK_ERROR_SURFACE_گمشده_KHR:
        أرجع "VK_ERROR_SURFACE_LOST_KHR";
    حالة VK_ERROR_NATIVE_پنجره_درون_USE_KHR:
        أرجع "VK_ERROR_NATIVE_WINDOW_IN_USE_KHR";
    حالة VK_SUBOPTIMAL_KHR:
        أرجع "VK_SUBOPTIMAL_KHR";
    حالة VK_ERROR_بیرون_از_DATE_KHR:
        أرجع "VK_ERROR_OUT_OF_DATE_KHR";
    حالة VK_ERROR_INCOMPATIBLE_DISPLAY_KHR:
        أرجع "VK_ERROR_INCOMPATIBLE_DISPLAY_KHR";
    حالة VK_ERROR_VALIDATION_FAILED_EXT:
        أرجع "VK_ERROR_VALIDATION_FAILED_EXT";
    حالة VK_ERROR_INVALID_SHADER_NV:
        أرجع "VK_ERROR_INVALID_SHADER_NV";
#إذا VK_سرآیند_نسخه >= 135 && VK_سرآیند_نسخه < 162
    حالة VK_ERROR_INCOMPATIBLE_نسخه_KHR:
        أرجع "VK_ERROR_INCOMPATIBLE_VERSION_KHR";
#پایان_اگر
    حالة VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT:
        أرجع "VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT";
    حالة VK_ERROR_NOT_PERMITTED_EXT:
        أرجع "VK_ERROR_NOT_PERMITTED_EXT";
    حالة VK_ERROR_پر_SCREEN_EXCLUSIVE_نما_گمشده_EXT:
        أرجع "VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT";
    حالة VK_THREAD_IDLE_KHR:
        أرجع "VK_THREAD_IDLE_KHR";
    حالة VK_THREAD_انجامشده_KHR:
        أرجع "VK_THREAD_DONE_KHR";
    حالة VK_OPERATION_DEFERRED_KHR:
        أرجع "VK_OPERATION_DEFERRED_KHR";
    حالة VK_OPERATION_NOT_DEFERRED_KHR:
        أرجع "VK_OPERATION_NOT_DEFERRED_KHR";
    حالة VK_PIPELINE_COMPILE_REQUIRED_EXT:
        أرجع "VK_PIPELINE_COMPILE_REQUIRED_EXT";
    افتراضي:
        اكسر;
    }
    إذا (نتیجه < 0) {
        أرجع "VK_ERROR_<Unknown>";
    }
    أرجع "VK_<Unknown>";
}

VkExtensionProperties *SDL_Vulkan_CreateInstanceExtensionsList(
    PFN_vkEnumerateInstanceExtensionProperties vkEnumerateInstanceExtensionProperties,
    Uint32 *extension_شمار)
{
    Uint32 شمار = 0;
    Vk_نتیجه rc = vkEnumerateInstanceExtensionProperties(عدم, &شمار, عدم);
    VkExtensionProperties *نتیجه;

    إذا (rc == VK_ERROR_INCOMPATIBLE_DRIVER) {
        // Avoid the ERR_MAX_STRLEN limit by passing part of the message as a string argument.
        SDL_مجموعه_Error(
            "You probably don't have a working Vulkan driver installed. %s %s %s(%d)",
            "Getting Vulkan extensions failed:",
            "vkEnumerateInstanceExtensionProperties returned",
            SDL_Vulkan_Get_نتیجه_String(rc),
            (صحيح)rc);
        أرجع عدم;
    } وإلا إذا (rc != VK_SUCCESS) {
        SDL_مجموعه_Error(
            "Getting Vulkan extensions failed: vkEnumerateInstanceExtensionProperties returned "
            "%s(%d)",
            SDL_Vulkan_Get_نتیجه_String(rc),
            (صحيح)rc);
        أرجع عدم;
    }

    إذا (شمار == 0) {
        نتیجه = (VkExtensionProperties *)SDL_calloc(1, حجم(VkExtensionProperties)); // so we can return non-null
    } وإلا {
        نتیجه = (VkExtensionProperties *)SDL_calloc(شمار, حجم(VkExtensionProperties));
    }

    إذا (!نتیجه) {
        أرجع عدم;
    }

    rc = vkEnumerateInstanceExtensionProperties(عدم, &شمار, نتیجه);
    إذا (rc != VK_SUCCESS) {
        SDL_مجموعه_Error(
            "Getting Vulkan extensions failed: vkEnumerateInstanceExtensionProperties returned "
            "%s(%d)",
            SDL_Vulkan_Get_نتیجه_String(rc),
            (صحيح)rc);
        SDL_free(نتیجه);
        أرجع عدم;
    }
    *extension_شمار = شمار;
    أرجع نتیجه;
}

// Alpha modes, in order of preference
ساكن ثابت Vk_Display_Plane_Alpha_Flag_بیتها_KHR alphaModes[4] = {
    VK_DISPLAY_PLANE_ALPHA_OPAQUE_بیت_KHR,
    VK_DISPLAY_PLANE_ALPHA_GLOBAL_بیت_KHR,
    VK_DISPLAY_PLANE_ALPHA_در_هر_PIXEL_بیت_KHR,
    VK_DISPLAY_PLANE_ALPHA_در_هر_PIXEL_PREMULTIPLIED_بیت_KHR,
};

bool SDL_Vulkan_Display_CreateSurface(فراغ *vkGetInstanceProcAddr_,
                                      VkInstance instance,
                                      ثابت بنية Vk_تخصیص_Callbacks *allocator,
                                      VkSurfaceKHR *surface)
{
    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr =
        (PFN_vkGetInstanceProcAddr)vkGetInstanceProcAddr_;
#تعریف_کن VULKAN_INSTANCE_FUNCTION(name) \
    PFN_##name name = (PFN_##name)vkGetInstanceProcAddr((VkInstance)instance, #name)
    VULKAN_INSTANCE_FUNCTION(vkEnumeratePhysicalDevices);
    VULKAN_INSTANCE_FUNCTION(vkGetPhysicalDeviceDisplayPropertiesKHR);
    VULKAN_INSTANCE_FUNCTION(vk_Get_Display_نما_Properties_KHR);
    VULKAN_INSTANCE_FUNCTION(vkGetPhysicalDeviceDisplayPlanePropertiesKHR);
    VULKAN_INSTANCE_FUNCTION(vkGetDisplayPlaneCapabilitiesKHR);
    VULKAN_INSTANCE_FUNCTION(vkGetDisplayPlaneSupportedDisplaysKHR);
    VULKAN_INSTANCE_FUNCTION(vkCreateDisplayPlaneSurfaceKHR);
#لغو_تعریف VULKAN_INSTANCE_FUNCTION
    VkDisplaySurfaceCreateInfoKHR createInfo;
    Vk_نتیجه rc;
    uint32_t physical_Device_شمار = 0;
    VkPhysicalDevice *physicalDevices = عدم;
    uint32_t physical_Device_شاخص;
    ثابت حرف *chosenDisplayId;
    صحيح displayId = 0; // Counting from physical device 0, display 0

    إذا (!vkEnumeratePhysicalDevices ||
        !vkGetPhysicalDeviceDisplayPropertiesKHR ||
        !vk_Get_Display_نما_Properties_KHR ||
        !vkGetPhysicalDeviceDisplayPlanePropertiesKHR ||
        !vkGetDisplayPlaneCapabilitiesKHR ||
        !vkGetDisplayPlaneSupportedDisplaysKHR ||
        !vkCreateDisplayPlaneSurfaceKHR) {
        SDL_مجموعه_Error(VK_KHR_DISPLAY_EXTENSION_NAME " extension is not enabled in the Vulkan instance.");
        اذهب error;
    }
    chosenDisplayId = SDL_GetHint(SDL_HINT_VULKAN_DISPLAY);
    إذا (chosenDisplayId) {
        displayId = SDL_atoi(chosenDisplayId);
    }

    // Enumerate physical devices
    rc = vkEnumeratePhysicalDevices(instance, &physical_Device_شمار, عدم);
    إذا (rc != VK_SUCCESS) {
        SDL_مجموعه_Error("Could not enumerate Vulkan physical devices");
        اذهب error;
    }

    إذا (physical_Device_شمار == 0) {
        SDL_مجموعه_Error("No Vulkan physical devices");
        اذهب error;
    }

    physicalDevices = (VkPhysicalDevice *)SDL_malloc(حجم(VkPhysicalDevice) * physical_Device_شمار);
    إذا (!physicalDevices) {
        اذهب error;
    }

    rc = vkEnumeratePhysicalDevices(instance, &physical_Device_شمار, physicalDevices);
    إذا (rc != VK_SUCCESS) {
        SDL_مجموعه_Error("Error enumerating physical devices");
        اذهب error;
    }

    لكل (physical_Device_شاخص = 0; physical_Device_شاخص < physical_Device_شمار; physical_Device_شاخص++) {
        VkPhysicalDevice physicalDevice = physicalDevices[physical_Device_شاخص];
        uint32_t display_Properties_شمار = 0;
        VkDisplayPropertiesKHR *displayProperties = عدم;
        uint32_t display_نما_Properties_شمار = 0;
        Vk_Display_نما_Properties_KHR *display_نما_Properties = عدم;
        صحيح بهترین_تطابق_شاخص = -1;
        uint32_t refresh_نرخ_2 = 0;
        uint32_t i;
        uint32_t display_Plane_Properties_شمار = 0;
        صحيح plane_شاخص = -1;
        VkDisplayKHR display;
        VkDisplayPlanePropertiesKHR *displayPlaneProperties = عدم;
        VkExtent2D extent;
        VkDisplayPlaneCapabilitiesKHR planeCaps = { 0 };

        // Get information about the physical displays
        rc = vkGetPhysicalDeviceDisplayPropertiesKHR(physicalDevice, &display_Properties_شمار, عدم);
        إذا (rc != VK_SUCCESS || display_Properties_شمار == 0) {
            // This device has no physical device display properties, move on to next.
            استمر;
        }
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Number of display properties for device %u: %u",
                     physical_Device_شاخص, display_Properties_شمار);

        إذا (displayId < 0 || (uint32_t)displayId >= display_Properties_شمار) {
            // Display id specified was higher than number of available displays, move to next physical device.
            displayId -= display_Properties_شمار;
            استمر;
        }

        displayProperties = (VkDisplayPropertiesKHR *)SDL_malloc(حجم(VkDisplayPropertiesKHR) * display_Properties_شمار);
        إذا (!displayProperties) {
            اذهب error;
        }

        rc = vkGetPhysicalDeviceDisplayPropertiesKHR(physicalDevice, &display_Properties_شمار, displayProperties);
        إذا (rc != VK_SUCCESS || display_Properties_شمار == 0) {
            SDL_free(displayProperties);
            SDL_مجموعه_Error("Error enumerating physical device displays");
            اذهب error;
        }

        display = displayProperties[displayId].display;
        extent = displayProperties[displayId].physicalResolution;
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Display: %s Native resolution: %ux%u",
                     displayProperties[displayId].displayName, extent.عرض, extent.ارتفاع);

        SDL_free(displayProperties);
        displayProperties = عدم;

        // Get display mode properties for the chosen display
        rc = vk_Get_Display_نما_Properties_KHR(physicalDevice, display, &display_نما_Properties_شمار, عدم);
        إذا (rc != VK_SUCCESS || display_نما_Properties_شمار == 0) {
            SDL_مجموعه_Error("Error enumerating display modes");
            اذهب error;
        }
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Number of display modes: %u", display_نما_Properties_شمار);

        display_نما_Properties = (Vk_Display_نما_Properties_KHR *)SDL_malloc(حجم(Vk_Display_نما_Properties_KHR) * display_نما_Properties_شمار);
        إذا (!display_نما_Properties) {
            اذهب error;
        }

        rc = vk_Get_Display_نما_Properties_KHR(physicalDevice, display, &display_نما_Properties_شمار, display_نما_Properties);
        إذا (rc != VK_SUCCESS || display_نما_Properties_شمار == 0) {
            SDL_مجموعه_Error("Error enumerating display modes");
            SDL_free(display_نما_Properties);
            اذهب error;
        }

        // Try to find a display mode that matches the native resolution
        لكل (i = 0; i < display_نما_Properties_شمار; ++i) {
            إذا (display_نما_Properties[i].parameters.visibleRegion.عرض == extent.عرض &&
                display_نما_Properties[i].parameters.visibleRegion.ارتفاع == extent.ارتفاع &&
                display_نما_Properties[i].parameters.refresh_نرخ_2 > refresh_نرخ_2) {
                بهترین_تطابق_شاخص = i;
                refresh_نرخ_2 = display_نما_Properties[i].parameters.refresh_نرخ_2;
            }
        }

        إذا (بهترین_تطابق_شاخص < 0) {
            SDL_مجموعه_Error("Found no matching display mode");
            SDL_free(display_نما_Properties);
            اذهب error;
        }

        SDL_zero(createInfo);
        createInfo.display_نما = display_نما_Properties[بهترین_تطابق_شاخص].display_نما;
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Matching mode %ux%u with refresh rate %u",
                     display_نما_Properties[بهترین_تطابق_شاخص].parameters.visibleRegion.عرض,
                     display_نما_Properties[بهترین_تطابق_شاخص].parameters.visibleRegion.ارتفاع,
                     refresh_نرخ_2);

        SDL_free(display_نما_Properties);
        display_نما_Properties = عدم;

        // Try to find a plane index that supports our display
        rc = vkGetPhysicalDeviceDisplayPlanePropertiesKHR(physicalDevice, &display_Plane_Properties_شمار, عدم);
        إذا (rc != VK_SUCCESS || display_Plane_Properties_شمار == 0) {
            SDL_مجموعه_Error("Error enumerating display planes");
            اذهب error;
        }
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Number of display planes: %u", display_Plane_Properties_شمار);

        displayPlaneProperties = (VkDisplayPlanePropertiesKHR *)SDL_malloc(حجم(VkDisplayPlanePropertiesKHR) * display_Plane_Properties_شمار);
        إذا (!displayPlaneProperties) {
            اذهب error;
        }

        rc = vkGetPhysicalDeviceDisplayPlanePropertiesKHR(physicalDevice, &display_Plane_Properties_شمار, displayPlaneProperties);
        إذا (rc != VK_SUCCESS || display_Plane_Properties_شمار == 0) {
            SDL_مجموعه_Error("Error enumerating display plane properties");
            SDL_free(displayPlaneProperties);
            اذهب error;
        }

        لكل (i = 0; i < display_Plane_Properties_شمار; ++i) {
            uint32_t plane_Supported_Displays_شمار = 0;
            VkDisplayKHR *planeSupportedDisplays = عدم;
            uint32_t j;

            // Check if plane is attached to a display, if not, continue.
            إذا (displayPlaneProperties[i].currentDisplay == VK_NULL_HANDLE) {
                استمر;
            }

            // Check supported displays for this plane.
            rc = vkGetDisplayPlaneSupportedDisplaysKHR(physicalDevice, i, &plane_Supported_Displays_شمار, عدم);
            إذا (rc != VK_SUCCESS || plane_Supported_Displays_شمار == 0) {
                استمر; // No supported displays, on to next plane.
            }

            SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Number of supported displays for plane %u: %u", i, plane_Supported_Displays_شمار);

            planeSupportedDisplays = (VkDisplayKHR *)SDL_malloc(حجم(VkDisplayKHR) * plane_Supported_Displays_شمار);
            إذا (!planeSupportedDisplays) {
                SDL_free(displayPlaneProperties);
                اذهب error;
            }

            rc = vkGetDisplayPlaneSupportedDisplaysKHR(physicalDevice, i, &plane_Supported_Displays_شمار, planeSupportedDisplays);
            إذا (rc != VK_SUCCESS || plane_Supported_Displays_شمار == 0) {
                SDL_مجموعه_Error("Error enumerating supported displays, or no supported displays");
                SDL_free(planeSupportedDisplays);
                SDL_free(displayPlaneProperties);
                اذهب error;
            }

            لكل (j = 0; j < plane_Supported_Displays_شمار && planeSupportedDisplays[j] != display; ++j) {
            }

            SDL_free(planeSupportedDisplays);
            planeSupportedDisplays = عدم;

            إذا (j == plane_Supported_Displays_شمار) {
                // This display is not supported for this plane, move on.
                استمر;
            }

            rc = vkGetDisplayPlaneCapabilitiesKHR(physicalDevice, createInfo.display_نما, i, &planeCaps);
            إذا (rc != VK_SUCCESS) {
                SDL_مجموعه_Error("Error getting display plane capabilities");
                SDL_free(displayPlaneProperties);
                اذهب error;
            }

            // Check if plane fulfills extent requirements.
            إذا (extent.عرض >= planeCaps.minDstExtent.عرض && extent.ارتفاع >= planeCaps.minDstExtent.ارتفاع &&
                extent.عرض <= planeCaps.maxDstExtent.عرض && extent.ارتفاع <= planeCaps.maxDstExtent.ارتفاع) {
                // If it does, choose this plane.
                SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Choosing plane %u, minimum extent %ux%u maximum extent %ux%u", i,
                             planeCaps.minDstExtent.عرض, planeCaps.minDstExtent.ارتفاع,
                             planeCaps.maxDstExtent.عرض, planeCaps.maxDstExtent.ارتفاع);
                plane_شاخص = i;
                اكسر;
            }
        }

        إذا (plane_شاخص < 0) {
            SDL_مجموعه_Error("No plane supports the selected resolution");
            SDL_free(displayPlaneProperties);
            اذهب error;
        }

        createInfo.plane_شاخص = plane_شاخص;
        createInfo.plane_پشته_شاخص = displayPlaneProperties[plane_شاخص].current_پشته_شاخص;
        SDL_free(displayPlaneProperties);
        displayPlaneProperties = عدم;

        // Find a supported alpha mode. Not all planes support OPAQUE
        createInfo.alpha_نما = VK_DISPLAY_PLANE_ALPHA_OPAQUE_بیت_KHR;
        لكل (i = 0; i < SDL_arraysize(alphaModes); i++) {
            إذا (planeCaps.supportedAlpha & alphaModes[i]) {
                createInfo.alpha_نما = alphaModes[i];
                اكسر;
            }
        }
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Chose alpha mode 0x%x", createInfo.alpha_نما);

        // Found a match, finally! Fill in extent, and break from loop
        createInfo.imageExtent = extent;
        اكسر;
    }

    SDL_free(physicalDevices);
    physicalDevices = عدم;

    إذا (physical_Device_شاخص == physical_Device_شمار) {
        SDL_مجموعه_Error("No usable displays found or requested display out of range");
        اذهب error;
    }

    createInfo.sType = VK_STRUCTURE_TYPE_DISPLAY_SURFACE_CREATE_INFO_KHR;
    createInfo.transform = VK_SURFACE_TRANSFORM_عنصر_خنثی_بیت_KHR;
    createInfo.globalAlpha = 1.0f;

    rc = vkCreateDisplayPlaneSurfaceKHR(instance, &createInfo, allocator, surface);
    إذا (rc != VK_SUCCESS) {
        SDL_مجموعه_Error("vkCreateDisplayPlaneSurfaceKHR failed: %s", SDL_Vulkan_Get_نتیجه_String(rc));
        اذهب error;
    }
    SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Created surface");
    أرجع true;

error:
    SDL_free(physicalDevices);
    أرجع false;
}

فراغ SDL_Vulkan_Destroy_Surface_داخلی(فراغ *vkGetInstanceProcAddr_,
                                        VkInstance instance,
                                        VkSurfaceKHR surface,
                                        ثابت بنية Vk_تخصیص_Callbacks *allocator)
{
    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr =
        (PFN_vkGetInstanceProcAddr)vkGetInstanceProcAddr_;
    PFN_vkDestroySurfaceKHR vkDestroySurfaceKHR =
        (PFN_vkDestroySurfaceKHR)vkGetInstanceProcAddr(
            instance,
            "vkDestroySurfaceKHR");

    إذا (vkDestroySurfaceKHR) {
        vkDestroySurfaceKHR(instance, surface, allocator);
    }
}

#پایان_اگر
