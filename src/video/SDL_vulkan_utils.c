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
#شامل "SDL_internal.h"

#شامل "SDL_vulkan_internal.h"

#اگر_تعریف_شدہ SDL_VIDEO_VULKAN

ثابت حرف *SDL_Vulkan_Get_نتیجہ_String(Vk_نتیجہ نتیجہ)
{
    انتخاب ((صحیح)نتیجہ) {
    حالت VK_SUCCESS:
        واپس "VK_SUCCESS";
    حالت VK_NOT_READY:
        واپس "VK_NOT_READY";
    حالت VK_TIMEOUT:
        واپس "VK_TIMEOUT";
    حالت VK_EVENT_سیٹ:
        واپس "VK_EVENT_SET";
    حالت VK_EVENT_RESET:
        واپس "VK_EVENT_RESET";
    حالت VK_INCOMPLETE:
        واپس "VK_INCOMPLETE";
    حالت VK_ERROR_برآمد_کا_HOST_حافظہ:
        واپس "VK_ERROR_OUT_OF_HOST_MEMORY";
    حالت VK_ERROR_برآمد_کا_DEVICE_حافظہ:
        واپس "VK_ERROR_OUT_OF_DEVICE_MEMORY";
    حالت VK_ERROR_INITIALIZATION_FAILED:
        واپس "VK_ERROR_INITIALIZATION_FAILED";
    حالت VK_ERROR_DEVICE_گمشدہ:
        واپس "VK_ERROR_DEVICE_LOST";
    حالت VK_ERROR_حافظہ_MAP_FAILED:
        واپس "VK_ERROR_MEMORY_MAP_FAILED";
    حالت VK_ERROR_LAYER_NOT_PRESENT:
        واپس "VK_ERROR_LAYER_NOT_PRESENT";
    حالت VK_ERROR_EXTENSION_NOT_PRESENT:
        واپس "VK_ERROR_EXTENSION_NOT_PRESENT";
    حالت VK_ERROR_FEATURE_NOT_PRESENT:
        واپس "VK_ERROR_FEATURE_NOT_PRESENT";
    حالت VK_ERROR_INCOMPATIBLE_DRIVER:
        واپس "VK_ERROR_INCOMPATIBLE_DRIVER";
    حالت VK_ERROR_TOO_MANY_OBJECTS:
        واپس "VK_ERROR_TOO_MANY_OBJECTS";
    حالت VK_ERROR_FORMAT_NOT_SUPPORTED:
        واپس "VK_ERROR_FORMAT_NOT_SUPPORTED";
    حالت VK_ERROR_FRAGMENTED_POOL:
        واپس "VK_ERROR_FRAGMENTED_POOL";
    حالت VK_ERROR_UNKNOWN:
        واپس "VK_ERROR_UNKNOWN";
    حالت VK_ERROR_برآمد_کا_POOL_حافظہ:
        واپس "VK_ERROR_OUT_OF_POOL_MEMORY";
    حالت VK_ERROR_INVALID_EXTERNAL_HANDLE:
        واپس "VK_ERROR_INVALID_EXTERNAL_HANDLE";
    حالت VK_ERROR_FRAGMENTATION:
        واپس "VK_ERROR_FRAGMENTATION";
    حالت VK_ERROR_INVALID_OPAQUE_CAPTURE_پتہ:
        واپس "VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS";
    حالت VK_ERROR_SURFACE_گمشدہ_KHR:
        واپس "VK_ERROR_SURFACE_LOST_KHR";
    حالت VK_ERROR_NATIVE_کھڑکی_اندر_USE_KHR:
        واپس "VK_ERROR_NATIVE_WINDOW_IN_USE_KHR";
    حالت VK_SUBOPTIMAL_KHR:
        واپس "VK_SUBOPTIMAL_KHR";
    حالت VK_ERROR_برآمد_کا_DATE_KHR:
        واپس "VK_ERROR_OUT_OF_DATE_KHR";
    حالت VK_ERROR_INCOMPATIBLE_DISPLAY_KHR:
        واپس "VK_ERROR_INCOMPATIBLE_DISPLAY_KHR";
    حالت VK_ERROR_VALIDATION_FAILED_EXT:
        واپس "VK_ERROR_VALIDATION_FAILED_EXT";
    حالت VK_ERROR_INVALID_SHADER_NV:
        واپس "VK_ERROR_INVALID_SHADER_NV";
#اگر VK_سرخی_نسخہ >= 135 && VK_سرخی_نسخہ < 162
    حالت VK_ERROR_INCOMPATIBLE_نسخہ_KHR:
        واپس "VK_ERROR_INCOMPATIBLE_VERSION_KHR";
#اگر_ختم
    حالت VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT:
        واپس "VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT";
    حالت VK_ERROR_NOT_PERMITTED_EXT:
        واپس "VK_ERROR_NOT_PERMITTED_EXT";
    حالت VK_ERROR_بھرا_SCREEN_EXCLUSIVE_منوال_گمشدہ_EXT:
        واپس "VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT";
    حالت VK_THREAD_IDLE_KHR:
        واپس "VK_THREAD_IDLE_KHR";
    حالت VK_THREAD_مکمل_KHR:
        واپس "VK_THREAD_DONE_KHR";
    حالت VK_OPERATION_DEFERRED_KHR:
        واپس "VK_OPERATION_DEFERRED_KHR";
    حالت VK_OPERATION_NOT_DEFERRED_KHR:
        واپس "VK_OPERATION_NOT_DEFERRED_KHR";
    حالت VK_PIPELINE_COMPILE_REQUIRED_EXT:
        واپس "VK_PIPELINE_COMPILE_REQUIRED_EXT";
    طےشدہ:
        توڑو;
    }
    اگر (نتیجہ < 0) {
        واپس "VK_ERROR_<Unknown>";
    }
    واپس "VK_<Unknown>";
}

VkExtensionProperties *SDL_Vulkan_CreateInstanceExtensionsList(
    PFN_vkEnumerateInstanceExtensionProperties vkEnumerateInstanceExtensionProperties,
    Uint32 *extension_گنتی)
{
    Uint32 گنتی = 0;
    Vk_نتیجہ rc = vkEnumerateInstanceExtensionProperties(تہی, &گنتی, تہی);
    VkExtensionProperties *نتیجہ;

    اگر (rc == VK_ERROR_INCOMPATIBLE_DRIVER) {
        // Avoid the ERR_MAX_STRLEN limit by passing part of the message as a string argument.
        SDL_سیٹ_Error(
            "You probably don't have a working Vulkan driver installed. %s %s %s(%d)",
            "Getting Vulkan extensions failed:",
            "vkEnumerateInstanceExtensionProperties returned",
            SDL_Vulkan_Get_نتیجہ_String(rc),
            (صحیح)rc);
        واپس تہی;
    } ورنہ اگر (rc != VK_SUCCESS) {
        SDL_سیٹ_Error(
            "Getting Vulkan extensions failed: vkEnumerateInstanceExtensionProperties returned "
            "%s(%d)",
            SDL_Vulkan_Get_نتیجہ_String(rc),
            (صحیح)rc);
        واپس تہی;
    }

    اگر (گنتی == 0) {
        نتیجہ = (VkExtensionProperties *)SDL_calloc(1, حجم(VkExtensionProperties)); // so we can return non-null
    } ورنہ {
        نتیجہ = (VkExtensionProperties *)SDL_calloc(گنتی, حجم(VkExtensionProperties));
    }

    اگر (!نتیجہ) {
        واپس تہی;
    }

    rc = vkEnumerateInstanceExtensionProperties(تہی, &گنتی, نتیجہ);
    اگر (rc != VK_SUCCESS) {
        SDL_سیٹ_Error(
            "Getting Vulkan extensions failed: vkEnumerateInstanceExtensionProperties returned "
            "%s(%d)",
            SDL_Vulkan_Get_نتیجہ_String(rc),
            (صحیح)rc);
        SDL_free(نتیجہ);
        واپس تہی;
    }
    *extension_گنتی = گنتی;
    واپس نتیجہ;
}

// Alpha modes, in order of preference
ساکن ثابت Vk_Display_Plane_Alpha_Flag_بٹ_KHR alphaModes[4] = {
    VK_DISPLAY_PLANE_ALPHA_OPAQUE_ثنائی_ہندسہ_KHR,
    VK_DISPLAY_PLANE_ALPHA_GLOBAL_ثنائی_ہندسہ_KHR,
    VK_DISPLAY_PLANE_ALPHA_فی_PIXEL_ثنائی_ہندسہ_KHR,
    VK_DISPLAY_PLANE_ALPHA_فی_PIXEL_PREMULTIPLIED_ثنائی_ہندسہ_KHR,
};

bool SDL_Vulkan_Display_CreateSurface(خالی *vkGetInstanceProcAddr_,
                                      VkInstance instance,
                                      ثابت ساخت Vk_تخصیص_Callbacks *allocator,
                                      VkSurfaceKHR *surface)
{
    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr =
        (PFN_vkGetInstanceProcAddr)vkGetInstanceProcAddr_;
#تعریف_کرو VULKAN_INSTANCE_FUNCTION(name) \
    PFN_##name name = (PFN_##name)vkGetInstanceProcAddr((VkInstance)instance, #name)
    VULKAN_INSTANCE_FUNCTION(vkEnumeratePhysicalDevices);
    VULKAN_INSTANCE_FUNCTION(vkGetPhysicalDeviceDisplayPropertiesKHR);
    VULKAN_INSTANCE_FUNCTION(vk_Get_Display_منوال_Properties_KHR);
    VULKAN_INSTANCE_FUNCTION(vkGetPhysicalDeviceDisplayPlanePropertiesKHR);
    VULKAN_INSTANCE_FUNCTION(vkGetDisplayPlaneCapabilitiesKHR);
    VULKAN_INSTANCE_FUNCTION(vkGetDisplayPlaneSupportedDisplaysKHR);
    VULKAN_INSTANCE_FUNCTION(vkCreateDisplayPlaneSurfaceKHR);
#تعریف_منسوخ VULKAN_INSTANCE_FUNCTION
    VkDisplaySurfaceCreateInfoKHR createInfo;
    Vk_نتیجہ rc;
    uint32_t physical_Device_گنتی = 0;
    VkPhysicalDevice *physicalDevices = تہی;
    uint32_t physical_Device_اشاریہ;
    ثابت حرف *chosenDisplayId;
    صحیح displayId = 0; // Counting from physical device 0, display 0

    اگر (!vkEnumeratePhysicalDevices ||
        !vkGetPhysicalDeviceDisplayPropertiesKHR ||
        !vk_Get_Display_منوال_Properties_KHR ||
        !vkGetPhysicalDeviceDisplayPlanePropertiesKHR ||
        !vkGetDisplayPlaneCapabilitiesKHR ||
        !vkGetDisplayPlaneSupportedDisplaysKHR ||
        !vkCreateDisplayPlaneSurfaceKHR) {
        SDL_سیٹ_Error(VK_KHR_DISPLAY_EXTENSION_NAME " extension is not enabled in the Vulkan instance.");
        جاؤ error;
    }
    chosenDisplayId = SDL_GetHint(SDL_HINT_VULKAN_DISPLAY);
    اگر (chosenDisplayId) {
        displayId = SDL_atoi(chosenDisplayId);
    }

    // Enumerate physical devices
    rc = vkEnumeratePhysicalDevices(instance, &physical_Device_گنتی, تہی);
    اگر (rc != VK_SUCCESS) {
        SDL_سیٹ_Error("Could not enumerate Vulkan physical devices");
        جاؤ error;
    }

    اگر (physical_Device_گنتی == 0) {
        SDL_سیٹ_Error("No Vulkan physical devices");
        جاؤ error;
    }

    physicalDevices = (VkPhysicalDevice *)SDL_malloc(حجم(VkPhysicalDevice) * physical_Device_گنتی);
    اگر (!physicalDevices) {
        جاؤ error;
    }

    rc = vkEnumeratePhysicalDevices(instance, &physical_Device_گنتی, physicalDevices);
    اگر (rc != VK_SUCCESS) {
        SDL_سیٹ_Error("Error enumerating physical devices");
        جاؤ error;
    }

    برائے (physical_Device_اشاریہ = 0; physical_Device_اشاریہ < physical_Device_گنتی; physical_Device_اشاریہ++) {
        VkPhysicalDevice physicalDevice = physicalDevices[physical_Device_اشاریہ];
        uint32_t display_Properties_گنتی = 0;
        VkDisplayPropertiesKHR *displayProperties = تہی;
        uint32_t display_منوال_Properties_گنتی = 0;
        Vk_Display_منوال_Properties_KHR *display_منوال_Properties = تہی;
        صحیح بہترین_مطابقت_اشاریہ = -1;
        uint32_t refresh_شرح_2 = 0;
        uint32_t i;
        uint32_t display_Plane_Properties_گنتی = 0;
        صحیح plane_اشاریہ = -1;
        VkDisplayKHR display;
        VkDisplayPlanePropertiesKHR *displayPlaneProperties = تہی;
        VkExtent2D extent;
        VkDisplayPlaneCapabilitiesKHR planeCaps = { 0 };

        // Get information about the physical displays
        rc = vkGetPhysicalDeviceDisplayPropertiesKHR(physicalDevice, &display_Properties_گنتی, تہی);
        اگر (rc != VK_SUCCESS || display_Properties_گنتی == 0) {
            // This device has no physical device display properties, move on to next.
            جاری;
        }
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Number of display properties for device %u: %u",
                     physical_Device_اشاریہ, display_Properties_گنتی);

        اگر (displayId < 0 || (uint32_t)displayId >= display_Properties_گنتی) {
            // Display id specified was higher than number of available displays, move to next physical device.
            displayId -= display_Properties_گنتی;
            جاری;
        }

        displayProperties = (VkDisplayPropertiesKHR *)SDL_malloc(حجم(VkDisplayPropertiesKHR) * display_Properties_گنتی);
        اگر (!displayProperties) {
            جاؤ error;
        }

        rc = vkGetPhysicalDeviceDisplayPropertiesKHR(physicalDevice, &display_Properties_گنتی, displayProperties);
        اگر (rc != VK_SUCCESS || display_Properties_گنتی == 0) {
            SDL_free(displayProperties);
            SDL_سیٹ_Error("Error enumerating physical device displays");
            جاؤ error;
        }

        display = displayProperties[displayId].display;
        extent = displayProperties[displayId].physicalResolution;
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Display: %s Native resolution: %ux%u",
                     displayProperties[displayId].displayName, extent.چوڑائی, extent.اونچائی);

        SDL_free(displayProperties);
        displayProperties = تہی;

        // Get display mode properties for the chosen display
        rc = vk_Get_Display_منوال_Properties_KHR(physicalDevice, display, &display_منوال_Properties_گنتی, تہی);
        اگر (rc != VK_SUCCESS || display_منوال_Properties_گنتی == 0) {
            SDL_سیٹ_Error("Error enumerating display modes");
            جاؤ error;
        }
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Number of display modes: %u", display_منوال_Properties_گنتی);

        display_منوال_Properties = (Vk_Display_منوال_Properties_KHR *)SDL_malloc(حجم(Vk_Display_منوال_Properties_KHR) * display_منوال_Properties_گنتی);
        اگر (!display_منوال_Properties) {
            جاؤ error;
        }

        rc = vk_Get_Display_منوال_Properties_KHR(physicalDevice, display, &display_منوال_Properties_گنتی, display_منوال_Properties);
        اگر (rc != VK_SUCCESS || display_منوال_Properties_گنتی == 0) {
            SDL_سیٹ_Error("Error enumerating display modes");
            SDL_free(display_منوال_Properties);
            جاؤ error;
        }

        // Try to find a display mode that matches the native resolution
        برائے (i = 0; i < display_منوال_Properties_گنتی; ++i) {
            اگر (display_منوال_Properties[i].parameters.visibleRegion.چوڑائی == extent.چوڑائی &&
                display_منوال_Properties[i].parameters.visibleRegion.اونچائی == extent.اونچائی &&
                display_منوال_Properties[i].parameters.refresh_شرح_2 > refresh_شرح_2) {
                بہترین_مطابقت_اشاریہ = i;
                refresh_شرح_2 = display_منوال_Properties[i].parameters.refresh_شرح_2;
            }
        }

        اگر (بہترین_مطابقت_اشاریہ < 0) {
            SDL_سیٹ_Error("Found no matching display mode");
            SDL_free(display_منوال_Properties);
            جاؤ error;
        }

        SDL_zero(createInfo);
        createInfo.display_منوال = display_منوال_Properties[بہترین_مطابقت_اشاریہ].display_منوال;
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Matching mode %ux%u with refresh rate %u",
                     display_منوال_Properties[بہترین_مطابقت_اشاریہ].parameters.visibleRegion.چوڑائی,
                     display_منوال_Properties[بہترین_مطابقت_اشاریہ].parameters.visibleRegion.اونچائی,
                     refresh_شرح_2);

        SDL_free(display_منوال_Properties);
        display_منوال_Properties = تہی;

        // Try to find a plane index that supports our display
        rc = vkGetPhysicalDeviceDisplayPlanePropertiesKHR(physicalDevice, &display_Plane_Properties_گنتی, تہی);
        اگر (rc != VK_SUCCESS || display_Plane_Properties_گنتی == 0) {
            SDL_سیٹ_Error("Error enumerating display planes");
            جاؤ error;
        }
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Number of display planes: %u", display_Plane_Properties_گنتی);

        displayPlaneProperties = (VkDisplayPlanePropertiesKHR *)SDL_malloc(حجم(VkDisplayPlanePropertiesKHR) * display_Plane_Properties_گنتی);
        اگر (!displayPlaneProperties) {
            جاؤ error;
        }

        rc = vkGetPhysicalDeviceDisplayPlanePropertiesKHR(physicalDevice, &display_Plane_Properties_گنتی, displayPlaneProperties);
        اگر (rc != VK_SUCCESS || display_Plane_Properties_گنتی == 0) {
            SDL_سیٹ_Error("Error enumerating display plane properties");
            SDL_free(displayPlaneProperties);
            جاؤ error;
        }

        برائے (i = 0; i < display_Plane_Properties_گنتی; ++i) {
            uint32_t plane_Supported_Displays_گنتی = 0;
            VkDisplayKHR *planeSupportedDisplays = تہی;
            uint32_t j;

            // Check if plane is attached to a display, if not, continue.
            اگر (displayPlaneProperties[i].currentDisplay == VK_NULL_HANDLE) {
                جاری;
            }

            // Check supported displays for this plane.
            rc = vkGetDisplayPlaneSupportedDisplaysKHR(physicalDevice, i, &plane_Supported_Displays_گنتی, تہی);
            اگر (rc != VK_SUCCESS || plane_Supported_Displays_گنتی == 0) {
                جاری; // No supported displays, on to next plane.
            }

            SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Number of supported displays for plane %u: %u", i, plane_Supported_Displays_گنتی);

            planeSupportedDisplays = (VkDisplayKHR *)SDL_malloc(حجم(VkDisplayKHR) * plane_Supported_Displays_گنتی);
            اگر (!planeSupportedDisplays) {
                SDL_free(displayPlaneProperties);
                جاؤ error;
            }

            rc = vkGetDisplayPlaneSupportedDisplaysKHR(physicalDevice, i, &plane_Supported_Displays_گنتی, planeSupportedDisplays);
            اگر (rc != VK_SUCCESS || plane_Supported_Displays_گنتی == 0) {
                SDL_سیٹ_Error("Error enumerating supported displays, or no supported displays");
                SDL_free(planeSupportedDisplays);
                SDL_free(displayPlaneProperties);
                جاؤ error;
            }

            برائے (j = 0; j < plane_Supported_Displays_گنتی && planeSupportedDisplays[j] != display; ++j) {
            }

            SDL_free(planeSupportedDisplays);
            planeSupportedDisplays = تہی;

            اگر (j == plane_Supported_Displays_گنتی) {
                // This display is not supported for this plane, move on.
                جاری;
            }

            rc = vkGetDisplayPlaneCapabilitiesKHR(physicalDevice, createInfo.display_منوال, i, &planeCaps);
            اگر (rc != VK_SUCCESS) {
                SDL_سیٹ_Error("Error getting display plane capabilities");
                SDL_free(displayPlaneProperties);
                جاؤ error;
            }

            // Check if plane fulfills extent requirements.
            اگر (extent.چوڑائی >= planeCaps.minDstExtent.چوڑائی && extent.اونچائی >= planeCaps.minDstExtent.اونچائی &&
                extent.چوڑائی <= planeCaps.maxDstExtent.چوڑائی && extent.اونچائی <= planeCaps.maxDstExtent.اونچائی) {
                // If it does, choose this plane.
                SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Choosing plane %u, minimum extent %ux%u maximum extent %ux%u", i,
                             planeCaps.minDstExtent.چوڑائی, planeCaps.minDstExtent.اونچائی,
                             planeCaps.maxDstExtent.چوڑائی, planeCaps.maxDstExtent.اونچائی);
                plane_اشاریہ = i;
                توڑو;
            }
        }

        اگر (plane_اشاریہ < 0) {
            SDL_سیٹ_Error("No plane supports the selected resolution");
            SDL_free(displayPlaneProperties);
            جاؤ error;
        }

        createInfo.plane_اشاریہ = plane_اشاریہ;
        createInfo.plane_ڈھیر_اشاریہ = displayPlaneProperties[plane_اشاریہ].current_ڈھیر_اشاریہ;
        SDL_free(displayPlaneProperties);
        displayPlaneProperties = تہی;

        // Find a supported alpha mode. Not all planes support OPAQUE
        createInfo.alpha_منوال = VK_DISPLAY_PLANE_ALPHA_OPAQUE_ثنائی_ہندسہ_KHR;
        برائے (i = 0; i < SDL_arraysize(alphaModes); i++) {
            اگر (planeCaps.supportedAlpha & alphaModes[i]) {
                createInfo.alpha_منوال = alphaModes[i];
                توڑو;
            }
        }
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Chose alpha mode 0x%x", createInfo.alpha_منوال);

        // Found a match, finally! Fill in extent, and break from loop
        createInfo.imageExtent = extent;
        توڑو;
    }

    SDL_free(physicalDevices);
    physicalDevices = تہی;

    اگر (physical_Device_اشاریہ == physical_Device_گنتی) {
        SDL_سیٹ_Error("No usable displays found or requested display out of range");
        جاؤ error;
    }

    createInfo.sType = VK_STRUCTURE_TYPE_DISPLAY_SURFACE_CREATE_INFO_KHR;
    createInfo.transform = VK_SURFACE_TRANSFORM_شناختی_عنصر_ثنائی_ہندسہ_KHR;
    createInfo.globalAlpha = 1.0f;

    rc = vkCreateDisplayPlaneSurfaceKHR(instance, &createInfo, allocator, surface);
    اگر (rc != VK_SUCCESS) {
        SDL_سیٹ_Error("vkCreateDisplayPlaneSurfaceKHR failed: %s", SDL_Vulkan_Get_نتیجہ_String(rc));
        جاؤ error;
    }
    SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Created surface");
    واپس true;

error:
    SDL_free(physicalDevices);
    واپس false;
}

خالی SDL_Vulkan_Destroy_Surface_اندرونی(خالی *vkGetInstanceProcAddr_,
                                        VkInstance instance,
                                        VkSurfaceKHR surface,
                                        ثابت ساخت Vk_تخصیص_Callbacks *allocator)
{
    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr =
        (PFN_vkGetInstanceProcAddr)vkGetInstanceProcAddr_;
    PFN_vkDestroySurfaceKHR vkDestroySurfaceKHR =
        (PFN_vkDestroySurfaceKHR)vkGetInstanceProcAddr(
            instance,
            "vkDestroySurfaceKHR");

    اگر (vkDestroySurfaceKHR) {
        vkDestroySurfaceKHR(instance, surface, allocator);
    }
}

#اگر_ختم
