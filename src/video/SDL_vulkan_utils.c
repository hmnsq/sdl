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

#अन्तर्भाव "SDL_vulkan_internal.h"

#यदि_परिभाषितम् SDL_VIDEO_VULKAN

ध्रुव वर्ण *SDL_Vulkan_Get_परिणाम_String(Vk_परिणाम परिणाम)
{
    विकल्प ((पूर्णाङ्क)परिणाम) {
    पक्ष VK_SUCCESS:
        प्रत्यागम "VK_SUCCESS";
    पक्ष VK_NOT_READY:
        प्रत्यागम "VK_NOT_READY";
    पक्ष VK_TIMEOUT:
        प्रत्यागम "VK_TIMEOUT";
    पक्ष VK_EVENT_समुच्चयः:
        प्रत्यागम "VK_EVENT_SET";
    पक्ष VK_EVENT_RESET:
        प्रत्यागम "VK_EVENT_RESET";
    पक्ष VK_INCOMPLETE:
        प्रत्यागम "VK_INCOMPLETE";
    पक्ष VK_ERROR_बहिर्गमनम्_सम्बन्धि_HOST_स्मृतिः:
        प्रत्यागम "VK_ERROR_OUT_OF_HOST_MEMORY";
    पक्ष VK_ERROR_बहिर्गमनम्_सम्बन्धि_DEVICE_स्मृतिः:
        प्रत्यागम "VK_ERROR_OUT_OF_DEVICE_MEMORY";
    पक्ष VK_ERROR_INITIALIZATION_FAILED:
        प्रत्यागम "VK_ERROR_INITIALIZATION_FAILED";
    पक्ष VK_ERROR_DEVICE_नष्टम्:
        प्रत्यागम "VK_ERROR_DEVICE_LOST";
    पक्ष VK_ERROR_स्मृतिः_MAP_FAILED:
        प्रत्यागम "VK_ERROR_MEMORY_MAP_FAILED";
    पक्ष VK_ERROR_LAYER_NOT_PRESENT:
        प्रत्यागम "VK_ERROR_LAYER_NOT_PRESENT";
    पक्ष VK_ERROR_EXTENSION_NOT_PRESENT:
        प्रत्यागम "VK_ERROR_EXTENSION_NOT_PRESENT";
    पक्ष VK_ERROR_FEATURE_NOT_PRESENT:
        प्रत्यागम "VK_ERROR_FEATURE_NOT_PRESENT";
    पक्ष VK_ERROR_INCOMPATIBLE_DRIVER:
        प्रत्यागम "VK_ERROR_INCOMPATIBLE_DRIVER";
    पक्ष VK_ERROR_TOO_MANY_OBJECTS:
        प्रत्यागम "VK_ERROR_TOO_MANY_OBJECTS";
    पक्ष VK_ERROR_FORMAT_NOT_SUPPORTED:
        प्रत्यागम "VK_ERROR_FORMAT_NOT_SUPPORTED";
    पक्ष VK_ERROR_FRAGMENTED_POOL:
        प्रत्यागम "VK_ERROR_FRAGMENTED_POOL";
    पक्ष VK_ERROR_UNKNOWN:
        प्रत्यागम "VK_ERROR_UNKNOWN";
    पक्ष VK_ERROR_बहिर्गमनम्_सम्बन्धि_POOL_स्मृतिः:
        प्रत्यागम "VK_ERROR_OUT_OF_POOL_MEMORY";
    पक्ष VK_ERROR_INVALID_EXTERNAL_HANDLE:
        प्रत्यागम "VK_ERROR_INVALID_EXTERNAL_HANDLE";
    पक्ष VK_ERROR_FRAGMENTATION:
        प्रत्यागम "VK_ERROR_FRAGMENTATION";
    पक्ष VK_ERROR_INVALID_OPAQUE_CAPTURE_स्थानाङ्कः:
        प्रत्यागम "VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS";
    पक्ष VK_ERROR_SURFACE_नष्टम्_KHR:
        प्रत्यागम "VK_ERROR_SURFACE_LOST_KHR";
    पक्ष VK_ERROR_NATIVE_गवाक्षः_अन्तर्_USE_KHR:
        प्रत्यागम "VK_ERROR_NATIVE_WINDOW_IN_USE_KHR";
    पक्ष VK_SUBOPTIMAL_KHR:
        प्रत्यागम "VK_SUBOPTIMAL_KHR";
    पक्ष VK_ERROR_बहिर्गमनम्_सम्बन्धि_DATE_KHR:
        प्रत्यागम "VK_ERROR_OUT_OF_DATE_KHR";
    पक्ष VK_ERROR_INCOMPATIBLE_DISPLAY_KHR:
        प्रत्यागम "VK_ERROR_INCOMPATIBLE_DISPLAY_KHR";
    पक्ष VK_ERROR_VALIDATION_FAILED_EXT:
        प्रत्यागम "VK_ERROR_VALIDATION_FAILED_EXT";
    पक्ष VK_ERROR_INVALID_SHADER_NV:
        प्रत्यागम "VK_ERROR_INVALID_SHADER_NV";
#यदि VK_शीर्षकम्_संस्करणम् >= 135 && VK_शीर्षकम्_संस्करणम् < 162
    पक्ष VK_ERROR_INCOMPATIBLE_संस्करणम्_KHR:
        प्रत्यागम "VK_ERROR_INCOMPATIBLE_VERSION_KHR";
#यदि_अन्तः
    पक्ष VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT:
        प्रत्यागम "VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT";
    पक्ष VK_ERROR_NOT_PERMITTED_EXT:
        प्रत्यागम "VK_ERROR_NOT_PERMITTED_EXT";
    पक्ष VK_ERROR_पूर्णम्_SCREEN_EXCLUSIVE_बहुलकम्_नष्टम्_EXT:
        प्रत्यागम "VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT";
    पक्ष VK_THREAD_IDLE_KHR:
        प्रत्यागम "VK_THREAD_IDLE_KHR";
    पक्ष VK_THREAD_समाप्तम्_KHR:
        प्रत्यागम "VK_THREAD_DONE_KHR";
    पक्ष VK_OPERATION_DEFERRED_KHR:
        प्रत्यागम "VK_OPERATION_DEFERRED_KHR";
    पक्ष VK_OPERATION_NOT_DEFERRED_KHR:
        प्रत्यागम "VK_OPERATION_NOT_DEFERRED_KHR";
    पक्ष VK_PIPELINE_COMPILE_REQUIRED_EXT:
        प्रत्यागम "VK_PIPELINE_COMPILE_REQUIRED_EXT";
    स्वभाव:
        भङ्ग;
    }
    यदि (परिणाम < 0) {
        प्रत्यागम "VK_ERROR_<Unknown>";
    }
    प्रत्यागम "VK_<Unknown>";
}

VkExtensionProperties *SDL_Vulkan_CreateInstanceExtensionsList(
    PFN_vkEnumerateInstanceExtensionProperties vkEnumerateInstanceExtensionProperties,
    Uint32 *extension_गणनम्)
{
    Uint32 गणनम् = 0;
    Vk_परिणाम rc = vkEnumerateInstanceExtensionProperties(रिक्त, &गणनम्, रिक्त);
    VkExtensionProperties *परिणाम;

    यदि (rc == VK_ERROR_INCOMPATIBLE_DRIVER) {
        // Avoid the ERR_MAX_STRLEN limit by passing part of the message as a string argument.
        SDL_समुच्चयः_Error(
            "You probably don't have a working Vulkan driver installed. %s %s %s(%d)",
            "Getting Vulkan extensions failed:",
            "vkEnumerateInstanceExtensionProperties returned",
            SDL_Vulkan_Get_परिणाम_String(rc),
            (पूर्णाङ्क)rc);
        प्रत्यागम रिक्त;
    } अन्यथा यदि (rc != VK_SUCCESS) {
        SDL_समुच्चयः_Error(
            "Getting Vulkan extensions failed: vkEnumerateInstanceExtensionProperties returned "
            "%s(%d)",
            SDL_Vulkan_Get_परिणाम_String(rc),
            (पूर्णाङ्क)rc);
        प्रत्यागम रिक्त;
    }

    यदि (गणनम् == 0) {
        परिणाम = (VkExtensionProperties *)SDL_calloc(1, परिमाण(VkExtensionProperties)); // so we can return non-null
    } अन्यथा {
        परिणाम = (VkExtensionProperties *)SDL_calloc(गणनम्, परिमाण(VkExtensionProperties));
    }

    यदि (!परिणाम) {
        प्रत्यागम रिक्त;
    }

    rc = vkEnumerateInstanceExtensionProperties(रिक्त, &गणनम्, परिणाम);
    यदि (rc != VK_SUCCESS) {
        SDL_समुच्चयः_Error(
            "Getting Vulkan extensions failed: vkEnumerateInstanceExtensionProperties returned "
            "%s(%d)",
            SDL_Vulkan_Get_परिणाम_String(rc),
            (पूर्णाङ्क)rc);
        SDL_free(परिणाम);
        प्रत्यागम रिक्त;
    }
    *extension_गणनम् = गणनम्;
    प्रत्यागम परिणाम;
}

// Alpha modes, in order of preference
स्थिर ध्रुव Vk_Display_Plane_Alpha_Flag_द्वयङ्काः_KHR alphaModes[4] = {
    VK_DISPLAY_PLANE_ALPHA_OPAQUE_BIT_KHR,
    VK_DISPLAY_PLANE_ALPHA_GLOBAL_BIT_KHR,
    VK_DISPLAY_PLANE_ALPHA_प्रत्येकम्_PIXEL_BIT_KHR,
    VK_DISPLAY_PLANE_ALPHA_प्रत्येकम्_PIXEL_PREMULTIPLIED_BIT_KHR,
};

bool SDL_Vulkan_Display_CreateSurface(शून्य *vkGetInstanceProcAddr_,
                                      VkInstance instance,
                                      ध्रुव संरचना Vk_आवण्टनम्_Callbacks *allocator,
                                      VkSurfaceKHR *surface)
{
    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr =
        (PFN_vkGetInstanceProcAddr)vkGetInstanceProcAddr_;
#परिभाषय VULKAN_INSTANCE_FUNCTION(name) \
    PFN_##name name = (PFN_##name)vkGetInstanceProcAddr((VkInstance)instance, #name)
    VULKAN_INSTANCE_FUNCTION(vkEnumeratePhysicalDevices);
    VULKAN_INSTANCE_FUNCTION(vkGetPhysicalDeviceDisplayPropertiesKHR);
    VULKAN_INSTANCE_FUNCTION(vk_Get_Display_बहुलकम्_Properties_KHR);
    VULKAN_INSTANCE_FUNCTION(vkGetPhysicalDeviceDisplayPlanePropertiesKHR);
    VULKAN_INSTANCE_FUNCTION(vkGetDisplayPlaneCapabilitiesKHR);
    VULKAN_INSTANCE_FUNCTION(vkGetDisplayPlaneSupportedDisplaysKHR);
    VULKAN_INSTANCE_FUNCTION(vkCreateDisplayPlaneSurfaceKHR);
#अपरिभाषय VULKAN_INSTANCE_FUNCTION
    VkDisplaySurfaceCreateInfoKHR createInfo;
    Vk_परिणाम rc;
    uint32_t physical_Device_गणनम् = 0;
    VkPhysicalDevice *physicalDevices = रिक्त;
    uint32_t physical_Device_सूचकांक;
    ध्रुव वर्ण *chosenDisplayId;
    पूर्णाङ्क displayId = 0; // Counting from physical device 0, display 0

    यदि (!vkEnumeratePhysicalDevices ||
        !vkGetPhysicalDeviceDisplayPropertiesKHR ||
        !vk_Get_Display_बहुलकम्_Properties_KHR ||
        !vkGetPhysicalDeviceDisplayPlanePropertiesKHR ||
        !vkGetDisplayPlaneCapabilitiesKHR ||
        !vkGetDisplayPlaneSupportedDisplaysKHR ||
        !vkCreateDisplayPlaneSurfaceKHR) {
        SDL_समुच्चयः_Error(VK_KHR_DISPLAY_EXTENSION_NAME " extension is not enabled in the Vulkan instance.");
        गच्छ error;
    }
    chosenDisplayId = SDL_GetHint(SDL_HINT_VULKAN_DISPLAY);
    यदि (chosenDisplayId) {
        displayId = SDL_atoi(chosenDisplayId);
    }

    // Enumerate physical devices
    rc = vkEnumeratePhysicalDevices(instance, &physical_Device_गणनम्, रिक्त);
    यदि (rc != VK_SUCCESS) {
        SDL_समुच्चयः_Error("Could not enumerate Vulkan physical devices");
        गच्छ error;
    }

    यदि (physical_Device_गणनम् == 0) {
        SDL_समुच्चयः_Error("No Vulkan physical devices");
        गच्छ error;
    }

    physicalDevices = (VkPhysicalDevice *)SDL_malloc(परिमाण(VkPhysicalDevice) * physical_Device_गणनम्);
    यदि (!physicalDevices) {
        गच्छ error;
    }

    rc = vkEnumeratePhysicalDevices(instance, &physical_Device_गणनम्, physicalDevices);
    यदि (rc != VK_SUCCESS) {
        SDL_समुच्चयः_Error("Error enumerating physical devices");
        गच्छ error;
    }

    प्रति (physical_Device_सूचकांक = 0; physical_Device_सूचकांक < physical_Device_गणनम्; physical_Device_सूचकांक++) {
        VkPhysicalDevice physicalDevice = physicalDevices[physical_Device_सूचकांक];
        uint32_t display_Properties_गणनम् = 0;
        VkDisplayPropertiesKHR *displayProperties = रिक्त;
        uint32_t display_बहुलकम्_Properties_गणनम् = 0;
        Vk_Display_बहुलकम्_Properties_KHR *display_बहुलकम्_Properties = रिक्त;
        पूर्णाङ्क best_मेलनम्_सूचकांक = -1;
        uint32_t refresh_दरः_2 = 0;
        uint32_t i;
        uint32_t display_Plane_Properties_गणनम् = 0;
        पूर्णाङ्क plane_सूचकांक = -1;
        VkDisplayKHR display;
        VkDisplayPlanePropertiesKHR *displayPlaneProperties = रिक्त;
        VkExtent2D extent;
        VkDisplayPlaneCapabilitiesKHR planeCaps = { 0 };

        // Get information about the physical displays
        rc = vkGetPhysicalDeviceDisplayPropertiesKHR(physicalDevice, &display_Properties_गणनम्, रिक्त);
        यदि (rc != VK_SUCCESS || display_Properties_गणनम् == 0) {
            // This device has no physical device display properties, move on to next.
            अनुवर्त;
        }
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Number of display properties for device %u: %u",
                     physical_Device_सूचकांक, display_Properties_गणनम्);

        यदि (displayId < 0 || (uint32_t)displayId >= display_Properties_गणनम्) {
            // Display id specified was higher than number of available displays, move to next physical device.
            displayId -= display_Properties_गणनम्;
            अनुवर्त;
        }

        displayProperties = (VkDisplayPropertiesKHR *)SDL_malloc(परिमाण(VkDisplayPropertiesKHR) * display_Properties_गणनम्);
        यदि (!displayProperties) {
            गच्छ error;
        }

        rc = vkGetPhysicalDeviceDisplayPropertiesKHR(physicalDevice, &display_Properties_गणनम्, displayProperties);
        यदि (rc != VK_SUCCESS || display_Properties_गणनम् == 0) {
            SDL_free(displayProperties);
            SDL_समुच्चयः_Error("Error enumerating physical device displays");
            गच्छ error;
        }

        display = displayProperties[displayId].display;
        extent = displayProperties[displayId].physicalResolution;
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Display: %s Native resolution: %ux%u",
                     displayProperties[displayId].displayName, extent.विस्तारः, extent.height);

        SDL_free(displayProperties);
        displayProperties = रिक्त;

        // Get display mode properties for the chosen display
        rc = vk_Get_Display_बहुलकम्_Properties_KHR(physicalDevice, display, &display_बहुलकम्_Properties_गणनम्, रिक्त);
        यदि (rc != VK_SUCCESS || display_बहुलकम्_Properties_गणनम् == 0) {
            SDL_समुच्चयः_Error("Error enumerating display modes");
            गच्छ error;
        }
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Number of display modes: %u", display_बहुलकम्_Properties_गणनम्);

        display_बहुलकम्_Properties = (Vk_Display_बहुलकम्_Properties_KHR *)SDL_malloc(परिमाण(Vk_Display_बहुलकम्_Properties_KHR) * display_बहुलकम्_Properties_गणनम्);
        यदि (!display_बहुलकम्_Properties) {
            गच्छ error;
        }

        rc = vk_Get_Display_बहुलकम्_Properties_KHR(physicalDevice, display, &display_बहुलकम्_Properties_गणनम्, display_बहुलकम्_Properties);
        यदि (rc != VK_SUCCESS || display_बहुलकम्_Properties_गणनम् == 0) {
            SDL_समुच्चयः_Error("Error enumerating display modes");
            SDL_free(display_बहुलकम्_Properties);
            गच्छ error;
        }

        // Try to find a display mode that matches the native resolution
        प्रति (i = 0; i < display_बहुलकम्_Properties_गणनम्; ++i) {
            यदि (display_बहुलकम्_Properties[i].parameters.visibleRegion.विस्तारः == extent.विस्तारः &&
                display_बहुलकम्_Properties[i].parameters.visibleRegion.height == extent.height &&
                display_बहुलकम्_Properties[i].parameters.refresh_दरः_2 > refresh_दरः_2) {
                best_मेलनम्_सूचकांक = i;
                refresh_दरः_2 = display_बहुलकम्_Properties[i].parameters.refresh_दरः_2;
            }
        }

        यदि (best_मेलनम्_सूचकांक < 0) {
            SDL_समुच्चयः_Error("Found no matching display mode");
            SDL_free(display_बहुलकम्_Properties);
            गच्छ error;
        }

        SDL_zero(createInfo);
        createInfo.display_बहुलकम् = display_बहुलकम्_Properties[best_मेलनम्_सूचकांक].display_बहुलकम्;
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Matching mode %ux%u with refresh rate %u",
                     display_बहुलकम्_Properties[best_मेलनम्_सूचकांक].parameters.visibleRegion.विस्तारः,
                     display_बहुलकम्_Properties[best_मेलनम्_सूचकांक].parameters.visibleRegion.height,
                     refresh_दरः_2);

        SDL_free(display_बहुलकम्_Properties);
        display_बहुलकम्_Properties = रिक्त;

        // Try to find a plane index that supports our display
        rc = vkGetPhysicalDeviceDisplayPlanePropertiesKHR(physicalDevice, &display_Plane_Properties_गणनम्, रिक्त);
        यदि (rc != VK_SUCCESS || display_Plane_Properties_गणनम् == 0) {
            SDL_समुच्चयः_Error("Error enumerating display planes");
            गच्छ error;
        }
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Number of display planes: %u", display_Plane_Properties_गणनम्);

        displayPlaneProperties = (VkDisplayPlanePropertiesKHR *)SDL_malloc(परिमाण(VkDisplayPlanePropertiesKHR) * display_Plane_Properties_गणनम्);
        यदि (!displayPlaneProperties) {
            गच्छ error;
        }

        rc = vkGetPhysicalDeviceDisplayPlanePropertiesKHR(physicalDevice, &display_Plane_Properties_गणनम्, displayPlaneProperties);
        यदि (rc != VK_SUCCESS || display_Plane_Properties_गणनम् == 0) {
            SDL_समुच्चयः_Error("Error enumerating display plane properties");
            SDL_free(displayPlaneProperties);
            गच्छ error;
        }

        प्रति (i = 0; i < display_Plane_Properties_गणनम्; ++i) {
            uint32_t plane_Supported_Displays_गणनम् = 0;
            VkDisplayKHR *planeSupportedDisplays = रिक्त;
            uint32_t j;

            // Check if plane is attached to a display, if not, continue.
            यदि (displayPlaneProperties[i].currentDisplay == VK_NULL_HANDLE) {
                अनुवर्त;
            }

            // Check supported displays for this plane.
            rc = vkGetDisplayPlaneSupportedDisplaysKHR(physicalDevice, i, &plane_Supported_Displays_गणनम्, रिक्त);
            यदि (rc != VK_SUCCESS || plane_Supported_Displays_गणनम् == 0) {
                अनुवर्त; // No supported displays, on to next plane.
            }

            SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Number of supported displays for plane %u: %u", i, plane_Supported_Displays_गणनम्);

            planeSupportedDisplays = (VkDisplayKHR *)SDL_malloc(परिमाण(VkDisplayKHR) * plane_Supported_Displays_गणनम्);
            यदि (!planeSupportedDisplays) {
                SDL_free(displayPlaneProperties);
                गच्छ error;
            }

            rc = vkGetDisplayPlaneSupportedDisplaysKHR(physicalDevice, i, &plane_Supported_Displays_गणनम्, planeSupportedDisplays);
            यदि (rc != VK_SUCCESS || plane_Supported_Displays_गणनम् == 0) {
                SDL_समुच्चयः_Error("Error enumerating supported displays, or no supported displays");
                SDL_free(planeSupportedDisplays);
                SDL_free(displayPlaneProperties);
                गच्छ error;
            }

            प्रति (j = 0; j < plane_Supported_Displays_गणनम् && planeSupportedDisplays[j] != display; ++j) {
            }

            SDL_free(planeSupportedDisplays);
            planeSupportedDisplays = रिक्त;

            यदि (j == plane_Supported_Displays_गणनम्) {
                // This display is not supported for this plane, move on.
                अनुवर्त;
            }

            rc = vkGetDisplayPlaneCapabilitiesKHR(physicalDevice, createInfo.display_बहुलकम्, i, &planeCaps);
            यदि (rc != VK_SUCCESS) {
                SDL_समुच्चयः_Error("Error getting display plane capabilities");
                SDL_free(displayPlaneProperties);
                गच्छ error;
            }

            // Check if plane fulfills extent requirements.
            यदि (extent.विस्तारः >= planeCaps.minDstExtent.विस्तारः && extent.height >= planeCaps.minDstExtent.height &&
                extent.विस्तारः <= planeCaps.maxDstExtent.विस्तारः && extent.height <= planeCaps.maxDstExtent.height) {
                // If it does, choose this plane.
                SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Choosing plane %u, minimum extent %ux%u maximum extent %ux%u", i,
                             planeCaps.minDstExtent.विस्तारः, planeCaps.minDstExtent.height,
                             planeCaps.maxDstExtent.विस्तारः, planeCaps.maxDstExtent.height);
                plane_सूचकांक = i;
                भङ्ग;
            }
        }

        यदि (plane_सूचकांक < 0) {
            SDL_समुच्चयः_Error("No plane supports the selected resolution");
            SDL_free(displayPlaneProperties);
            गच्छ error;
        }

        createInfo.plane_सूचकांक = plane_सूचकांक;
        createInfo.plane_राशिः_सूचकांक = displayPlaneProperties[plane_सूचकांक].current_राशिः_सूचकांक;
        SDL_free(displayPlaneProperties);
        displayPlaneProperties = रिक्त;

        // Find a supported alpha mode. Not all planes support OPAQUE
        createInfo.alpha_बहुलकम् = VK_DISPLAY_PLANE_ALPHA_OPAQUE_BIT_KHR;
        प्रति (i = 0; i < SDL_arraysize(alphaModes); i++) {
            यदि (planeCaps.supportedAlpha & alphaModes[i]) {
                createInfo.alpha_बहुलकम् = alphaModes[i];
                भङ्ग;
            }
        }
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Chose alpha mode 0x%x", createInfo.alpha_बहुलकम्);

        // Found a match, finally! Fill in extent, and break from loop
        createInfo.imageExtent = extent;
        भङ्ग;
    }

    SDL_free(physicalDevices);
    physicalDevices = रिक्त;

    यदि (physical_Device_सूचकांक == physical_Device_गणनम्) {
        SDL_समुच्चयः_Error("No usable displays found or requested display out of range");
        गच्छ error;
    }

    createInfo.sType = VK_STRUCTURE_TYPE_DISPLAY_SURFACE_CREATE_INFO_KHR;
    createInfo.transform = VK_SURFACE_TRANSFORM_तटस्थः_BIT_KHR;
    createInfo.globalAlpha = 1.0f;

    rc = vkCreateDisplayPlaneSurfaceKHR(instance, &createInfo, allocator, surface);
    यदि (rc != VK_SUCCESS) {
        SDL_समुच्चयः_Error("vkCreateDisplayPlaneSurfaceKHR failed: %s", SDL_Vulkan_Get_परिणाम_String(rc));
        गच्छ error;
    }
    SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Created surface");
    प्रत्यागम true;

error:
    SDL_free(physicalDevices);
    प्रत्यागम false;
}

शून्य SDL_Vulkan_Destroy_Surface_आन्तरिकम्(शून्य *vkGetInstanceProcAddr_,
                                        VkInstance instance,
                                        VkSurfaceKHR surface,
                                        ध्रुव संरचना Vk_आवण्टनम्_Callbacks *allocator)
{
    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr =
        (PFN_vkGetInstanceProcAddr)vkGetInstanceProcAddr_;
    PFN_vkDestroySurfaceKHR vkDestroySurfaceKHR =
        (PFN_vkDestroySurfaceKHR)vkGetInstanceProcAddr(
            instance,
            "vkDestroySurfaceKHR");

    यदि (vkDestroySurfaceKHR) {
        vkDestroySurfaceKHR(instance, surface, allocator);
    }
}

#यदि_अन्तः
