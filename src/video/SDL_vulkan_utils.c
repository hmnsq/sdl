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

#समावेश "SDL_vulkan_internal.h"

#अगर_घोषित SDL_VIDEO_VULKAN

स्थिर अक्षर *SDL_Vulkan_Get_परिणाम_String(Vk_परिणाम परिणाम)
{
    चयन ((पूर्णांक)परिणाम) {
    हाल VK_SUCCESS:
        वापस "VK_SUCCESS";
    हाल VK_NOT_READY:
        वापस "VK_NOT_READY";
    हाल VK_TIMEOUT:
        वापस "VK_TIMEOUT";
    हाल VK_EVENT_SET:
        वापस "VK_EVENT_SET";
    हाल VK_EVENT_RESET:
        वापस "VK_EVENT_RESET";
    हाल VK_INCOMPLETE:
        वापस "VK_INCOMPLETE";
    हाल VK_ERROR_OUT_OF_HOST_MEMORY:
        वापस "VK_ERROR_OUT_OF_HOST_MEMORY";
    हाल VK_ERROR_OUT_OF_DEVICE_MEMORY:
        वापस "VK_ERROR_OUT_OF_DEVICE_MEMORY";
    हाल VK_ERROR_INITIALIZATION_FAILED:
        वापस "VK_ERROR_INITIALIZATION_FAILED";
    हाल VK_ERROR_DEVICE_LOST:
        वापस "VK_ERROR_DEVICE_LOST";
    हाल VK_ERROR_MEMORY_MAP_FAILED:
        वापस "VK_ERROR_MEMORY_MAP_FAILED";
    हाल VK_ERROR_LAYER_NOT_PRESENT:
        वापस "VK_ERROR_LAYER_NOT_PRESENT";
    हाल VK_ERROR_EXTENSION_NOT_PRESENT:
        वापस "VK_ERROR_EXTENSION_NOT_PRESENT";
    हाल VK_ERROR_FEATURE_NOT_PRESENT:
        वापस "VK_ERROR_FEATURE_NOT_PRESENT";
    हाल VK_ERROR_INCOMPATIBLE_DRIVER:
        वापस "VK_ERROR_INCOMPATIBLE_DRIVER";
    हाल VK_ERROR_TOO_MANY_OBJECTS:
        वापस "VK_ERROR_TOO_MANY_OBJECTS";
    हाल VK_ERROR_FORMAT_NOT_SUPPORTED:
        वापस "VK_ERROR_FORMAT_NOT_SUPPORTED";
    हाल VK_ERROR_FRAGMENTED_POOL:
        वापस "VK_ERROR_FRAGMENTED_POOL";
    हाल VK_ERROR_UNKNOWN:
        वापस "VK_ERROR_UNKNOWN";
    हाल VK_ERROR_OUT_OF_POOL_MEMORY:
        वापस "VK_ERROR_OUT_OF_POOL_MEMORY";
    हाल VK_ERROR_INVALID_EXTERNAL_HANDLE:
        वापस "VK_ERROR_INVALID_EXTERNAL_HANDLE";
    हाल VK_ERROR_FRAGMENTATION:
        वापस "VK_ERROR_FRAGMENTATION";
    हाल VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS:
        वापस "VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS";
    हाल VK_ERROR_SURFACE_LOST_KHR:
        वापस "VK_ERROR_SURFACE_LOST_KHR";
    हाल VK_ERROR_NATIVE_WINDOW_IN_USE_KHR:
        वापस "VK_ERROR_NATIVE_WINDOW_IN_USE_KHR";
    हाल VK_SUBOPTIMAL_KHR:
        वापस "VK_SUBOPTIMAL_KHR";
    हाल VK_ERROR_OUT_OF_DATE_KHR:
        वापस "VK_ERROR_OUT_OF_DATE_KHR";
    हाल VK_ERROR_INCOMPATIBLE_DISPLAY_KHR:
        वापस "VK_ERROR_INCOMPATIBLE_DISPLAY_KHR";
    हाल VK_ERROR_VALIDATION_FAILED_EXT:
        वापस "VK_ERROR_VALIDATION_FAILED_EXT";
    हाल VK_ERROR_INVALID_SHADER_NV:
        वापस "VK_ERROR_INVALID_SHADER_NV";
#अगर VK_HEADER_VERSION >= 135 && VK_HEADER_VERSION < 162
    हाल VK_ERROR_INCOMPATIBLE_VERSION_KHR:
        वापस "VK_ERROR_INCOMPATIBLE_VERSION_KHR";
#पूर्ण_अगर
    हाल VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT:
        वापस "VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT";
    हाल VK_ERROR_NOT_PERMITTED_EXT:
        वापस "VK_ERROR_NOT_PERMITTED_EXT";
    हाल VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT:
        वापस "VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT";
    हाल VK_THREAD_IDLE_KHR:
        वापस "VK_THREAD_IDLE_KHR";
    हाल VK_THREAD_DONE_KHR:
        वापस "VK_THREAD_DONE_KHR";
    हाल VK_OPERATION_DEFERRED_KHR:
        वापस "VK_OPERATION_DEFERRED_KHR";
    हाल VK_OPERATION_NOT_DEFERRED_KHR:
        वापस "VK_OPERATION_NOT_DEFERRED_KHR";
    हाल VK_PIPELINE_COMPILE_REQUIRED_EXT:
        वापस "VK_PIPELINE_COMPILE_REQUIRED_EXT";
    शेष:
        अवरोध;
    }
    अगर (परिणाम < 0) {
        वापस "VK_ERROR_<Unknown>";
    }
    वापस "VK_<Unknown>";
}

VkExtensionProperties *SDL_Vulkan_CreateInstanceExtensionsList(
    PFN_vkEnumerateInstanceExtensionProperties vkEnumerateInstanceExtensionProperties,
    Uint32 *extension_गिनती)
{
    Uint32 गिनती = 0;
    Vk_परिणाम rc = vkEnumerateInstanceExtensionProperties(शून्य, &गिनती, शून्य);
    VkExtensionProperties *परिणाम;

    अगर (rc == VK_ERROR_INCOMPATIBLE_DRIVER) {
        // Avoid the ERR_MAX_STRLEN limit by passing part of the message as a string argument.
        SDL_SetError(
            "You probably don't have a working Vulkan driver installed. %s %s %s(%d)",
            "Getting Vulkan extensions failed:",
            "vkEnumerateInstanceExtensionProperties returned",
            SDL_Vulkan_Get_परिणाम_String(rc),
            (पूर्णांक)rc);
        वापस शून्य;
    } अन्यथा अगर (rc != VK_SUCCESS) {
        SDL_SetError(
            "Getting Vulkan extensions failed: vkEnumerateInstanceExtensionProperties returned "
            "%s(%d)",
            SDL_Vulkan_Get_परिणाम_String(rc),
            (पूर्णांक)rc);
        वापस शून्य;
    }

    अगर (गिनती == 0) {
        परिणाम = (VkExtensionProperties *)SDL_calloc(1, माप(VkExtensionProperties)); // so we can return non-null
    } अन्यथा {
        परिणाम = (VkExtensionProperties *)SDL_calloc(गिनती, माप(VkExtensionProperties));
    }

    अगर (!परिणाम) {
        वापस शून्य;
    }

    rc = vkEnumerateInstanceExtensionProperties(शून्य, &गिनती, परिणाम);
    अगर (rc != VK_SUCCESS) {
        SDL_SetError(
            "Getting Vulkan extensions failed: vkEnumerateInstanceExtensionProperties returned "
            "%s(%d)",
            SDL_Vulkan_Get_परिणाम_String(rc),
            (पूर्णांक)rc);
        SDL_free(परिणाम);
        वापस शून्य;
    }
    *extension_गिनती = गिनती;
    वापस परिणाम;
}

// Alpha modes, in order of preference
अटल स्थिर VkDisplayPlaneAlphaFlagBitsKHR alphaModes[4] = {
    VK_DISPLAY_PLANE_ALPHA_OPAQUE_BIT_KHR,
    VK_DISPLAY_PLANE_ALPHA_GLOBAL_BIT_KHR,
    VK_DISPLAY_PLANE_ALPHA_PER_PIXEL_BIT_KHR,
    VK_DISPLAY_PLANE_ALPHA_PER_PIXEL_PREMULTIPLIED_BIT_KHR,
};

bool SDL_Vulkan_Display_CreateSurface(व्योम *vkGetInstanceProcAddr_,
                                      VkInstance instance,
                                      स्थिर काष्ठा VkAllocationCallbacks *allocator,
                                      VkSurfaceKHR *surface)
{
    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr =
        (PFN_vkGetInstanceProcAddr)vkGetInstanceProcAddr_;
#घोषणा VULKAN_INSTANCE_FUNCTION(name) \
    PFN_##name name = (PFN_##name)vkGetInstanceProcAddr((VkInstance)instance, #name)
    VULKAN_INSTANCE_FUNCTION(vkEnumeratePhysicalDevices);
    VULKAN_INSTANCE_FUNCTION(vkGetPhysicalDeviceDisplayPropertiesKHR);
    VULKAN_INSTANCE_FUNCTION(vkGetDisplayModePropertiesKHR);
    VULKAN_INSTANCE_FUNCTION(vkGetPhysicalDeviceDisplayPlanePropertiesKHR);
    VULKAN_INSTANCE_FUNCTION(vkGetDisplayPlaneCapabilitiesKHR);
    VULKAN_INSTANCE_FUNCTION(vkGetDisplayPlaneSupportedDisplaysKHR);
    VULKAN_INSTANCE_FUNCTION(vkCreateDisplayPlaneSurfaceKHR);
#अघोषित VULKAN_INSTANCE_FUNCTION
    VkDisplaySurfaceCreateInfoKHR createInfo;
    Vk_परिणाम rc;
    uint32_t physical_Device_गिनती = 0;
    VkPhysicalDevice *physicalDevices = शून्य;
    uint32_t physical_Device_सूचकांक;
    स्थिर अक्षर *chosenDisplayId;
    पूर्णांक displayId = 0; // Counting from physical device 0, display 0

    अगर (!vkEnumeratePhysicalDevices ||
        !vkGetPhysicalDeviceDisplayPropertiesKHR ||
        !vkGetDisplayModePropertiesKHR ||
        !vkGetPhysicalDeviceDisplayPlanePropertiesKHR ||
        !vkGetDisplayPlaneCapabilitiesKHR ||
        !vkGetDisplayPlaneSupportedDisplaysKHR ||
        !vkCreateDisplayPlaneSurfaceKHR) {
        SDL_SetError(VK_KHR_DISPLAY_EXTENSION_NAME " extension is not enabled in the Vulkan instance.");
        जाओ error;
    }
    chosenDisplayId = SDL_GetHint(SDL_HINT_VULKAN_DISPLAY);
    अगर (chosenDisplayId) {
        displayId = SDL_atoi(chosenDisplayId);
    }

    // Enumerate physical devices
    rc = vkEnumeratePhysicalDevices(instance, &physical_Device_गिनती, शून्य);
    अगर (rc != VK_SUCCESS) {
        SDL_SetError("Could not enumerate Vulkan physical devices");
        जाओ error;
    }

    अगर (physical_Device_गिनती == 0) {
        SDL_SetError("No Vulkan physical devices");
        जाओ error;
    }

    physicalDevices = (VkPhysicalDevice *)SDL_malloc(माप(VkPhysicalDevice) * physical_Device_गिनती);
    अगर (!physicalDevices) {
        जाओ error;
    }

    rc = vkEnumeratePhysicalDevices(instance, &physical_Device_गिनती, physicalDevices);
    अगर (rc != VK_SUCCESS) {
        SDL_SetError("Error enumerating physical devices");
        जाओ error;
    }

    क्रम (physical_Device_सूचकांक = 0; physical_Device_सूचकांक < physical_Device_गिनती; physical_Device_सूचकांक++) {
        VkPhysicalDevice physicalDevice = physicalDevices[physical_Device_सूचकांक];
        uint32_t display_Properties_गिनती = 0;
        VkDisplayPropertiesKHR *displayProperties = शून्य;
        uint32_t display_Mode_Properties_गिनती = 0;
        VkDisplayModePropertiesKHR *displayModeProperties = शून्य;
        पूर्णांक best_Match_सूचकांक = -1;
        uint32_t refreshRate = 0;
        uint32_t i;
        uint32_t display_Plane_Properties_गिनती = 0;
        पूर्णांक plane_सूचकांक = -1;
        VkDisplayKHR display;
        VkDisplayPlanePropertiesKHR *displayPlaneProperties = शून्य;
        VkExtent2D extent;
        VkDisplayPlaneCapabilitiesKHR planeCaps = { 0 };

        // Get information about the physical displays
        rc = vkGetPhysicalDeviceDisplayPropertiesKHR(physicalDevice, &display_Properties_गिनती, शून्य);
        अगर (rc != VK_SUCCESS || display_Properties_गिनती == 0) {
            // This device has no physical device display properties, move on to next.
            जारी;
        }
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Number of display properties for device %u: %u",
                     physical_Device_सूचकांक, display_Properties_गिनती);

        अगर (displayId < 0 || (uint32_t)displayId >= display_Properties_गिनती) {
            // Display id specified was higher than number of available displays, move to next physical device.
            displayId -= display_Properties_गिनती;
            जारी;
        }

        displayProperties = (VkDisplayPropertiesKHR *)SDL_malloc(माप(VkDisplayPropertiesKHR) * display_Properties_गिनती);
        अगर (!displayProperties) {
            जाओ error;
        }

        rc = vkGetPhysicalDeviceDisplayPropertiesKHR(physicalDevice, &display_Properties_गिनती, displayProperties);
        अगर (rc != VK_SUCCESS || display_Properties_गिनती == 0) {
            SDL_free(displayProperties);
            SDL_SetError("Error enumerating physical device displays");
            जाओ error;
        }

        display = displayProperties[displayId].display;
        extent = displayProperties[displayId].physicalResolution;
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Display: %s Native resolution: %ux%u",
                     displayProperties[displayId].displayName, extent.width, extent.height);

        SDL_free(displayProperties);
        displayProperties = शून्य;

        // Get display mode properties for the chosen display
        rc = vkGetDisplayModePropertiesKHR(physicalDevice, display, &display_Mode_Properties_गिनती, शून्य);
        अगर (rc != VK_SUCCESS || display_Mode_Properties_गिनती == 0) {
            SDL_SetError("Error enumerating display modes");
            जाओ error;
        }
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Number of display modes: %u", display_Mode_Properties_गिनती);

        displayModeProperties = (VkDisplayModePropertiesKHR *)SDL_malloc(माप(VkDisplayModePropertiesKHR) * display_Mode_Properties_गिनती);
        अगर (!displayModeProperties) {
            जाओ error;
        }

        rc = vkGetDisplayModePropertiesKHR(physicalDevice, display, &display_Mode_Properties_गिनती, displayModeProperties);
        अगर (rc != VK_SUCCESS || display_Mode_Properties_गिनती == 0) {
            SDL_SetError("Error enumerating display modes");
            SDL_free(displayModeProperties);
            जाओ error;
        }

        // Try to find a display mode that matches the native resolution
        क्रम (i = 0; i < display_Mode_Properties_गिनती; ++i) {
            अगर (displayModeProperties[i].parameters.visibleRegion.width == extent.width &&
                displayModeProperties[i].parameters.visibleRegion.height == extent.height &&
                displayModeProperties[i].parameters.refreshRate > refreshRate) {
                best_Match_सूचकांक = i;
                refreshRate = displayModeProperties[i].parameters.refreshRate;
            }
        }

        अगर (best_Match_सूचकांक < 0) {
            SDL_SetError("Found no matching display mode");
            SDL_free(displayModeProperties);
            जाओ error;
        }

        SDL_zero(createInfo);
        createInfo.displayMode = displayModeProperties[best_Match_सूचकांक].displayMode;
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Matching mode %ux%u with refresh rate %u",
                     displayModeProperties[best_Match_सूचकांक].parameters.visibleRegion.width,
                     displayModeProperties[best_Match_सूचकांक].parameters.visibleRegion.height,
                     refreshRate);

        SDL_free(displayModeProperties);
        displayModeProperties = शून्य;

        // Try to find a plane index that supports our display
        rc = vkGetPhysicalDeviceDisplayPlanePropertiesKHR(physicalDevice, &display_Plane_Properties_गिनती, शून्य);
        अगर (rc != VK_SUCCESS || display_Plane_Properties_गिनती == 0) {
            SDL_SetError("Error enumerating display planes");
            जाओ error;
        }
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Number of display planes: %u", display_Plane_Properties_गिनती);

        displayPlaneProperties = (VkDisplayPlanePropertiesKHR *)SDL_malloc(माप(VkDisplayPlanePropertiesKHR) * display_Plane_Properties_गिनती);
        अगर (!displayPlaneProperties) {
            जाओ error;
        }

        rc = vkGetPhysicalDeviceDisplayPlanePropertiesKHR(physicalDevice, &display_Plane_Properties_गिनती, displayPlaneProperties);
        अगर (rc != VK_SUCCESS || display_Plane_Properties_गिनती == 0) {
            SDL_SetError("Error enumerating display plane properties");
            SDL_free(displayPlaneProperties);
            जाओ error;
        }

        क्रम (i = 0; i < display_Plane_Properties_गिनती; ++i) {
            uint32_t plane_Supported_Displays_गिनती = 0;
            VkDisplayKHR *planeSupportedDisplays = शून्य;
            uint32_t j;

            // Check if plane is attached to a display, if not, continue.
            अगर (displayPlaneProperties[i].currentDisplay == VK_NULL_HANDLE) {
                जारी;
            }

            // Check supported displays for this plane.
            rc = vkGetDisplayPlaneSupportedDisplaysKHR(physicalDevice, i, &plane_Supported_Displays_गिनती, शून्य);
            अगर (rc != VK_SUCCESS || plane_Supported_Displays_गिनती == 0) {
                जारी; // No supported displays, on to next plane.
            }

            SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Number of supported displays for plane %u: %u", i, plane_Supported_Displays_गिनती);

            planeSupportedDisplays = (VkDisplayKHR *)SDL_malloc(माप(VkDisplayKHR) * plane_Supported_Displays_गिनती);
            अगर (!planeSupportedDisplays) {
                SDL_free(displayPlaneProperties);
                जाओ error;
            }

            rc = vkGetDisplayPlaneSupportedDisplaysKHR(physicalDevice, i, &plane_Supported_Displays_गिनती, planeSupportedDisplays);
            अगर (rc != VK_SUCCESS || plane_Supported_Displays_गिनती == 0) {
                SDL_SetError("Error enumerating supported displays, or no supported displays");
                SDL_free(planeSupportedDisplays);
                SDL_free(displayPlaneProperties);
                जाओ error;
            }

            क्रम (j = 0; j < plane_Supported_Displays_गिनती && planeSupportedDisplays[j] != display; ++j) {
            }

            SDL_free(planeSupportedDisplays);
            planeSupportedDisplays = शून्य;

            अगर (j == plane_Supported_Displays_गिनती) {
                // This display is not supported for this plane, move on.
                जारी;
            }

            rc = vkGetDisplayPlaneCapabilitiesKHR(physicalDevice, createInfo.displayMode, i, &planeCaps);
            अगर (rc != VK_SUCCESS) {
                SDL_SetError("Error getting display plane capabilities");
                SDL_free(displayPlaneProperties);
                जाओ error;
            }

            // Check if plane fulfills extent requirements.
            अगर (extent.width >= planeCaps.minDstExtent.width && extent.height >= planeCaps.minDstExtent.height &&
                extent.width <= planeCaps.maxDstExtent.width && extent.height <= planeCaps.maxDstExtent.height) {
                // If it does, choose this plane.
                SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Choosing plane %u, minimum extent %ux%u maximum extent %ux%u", i,
                             planeCaps.minDstExtent.width, planeCaps.minDstExtent.height,
                             planeCaps.maxDstExtent.width, planeCaps.maxDstExtent.height);
                plane_सूचकांक = i;
                अवरोध;
            }
        }

        अगर (plane_सूचकांक < 0) {
            SDL_SetError("No plane supports the selected resolution");
            SDL_free(displayPlaneProperties);
            जाओ error;
        }

        createInfo.plane_सूचकांक = plane_सूचकांक;
        createInfo.plane_ढेर_सूचकांक = displayPlaneProperties[plane_सूचकांक].current_ढेर_सूचकांक;
        SDL_free(displayPlaneProperties);
        displayPlaneProperties = शून्य;

        // Find a supported alpha mode. Not all planes support OPAQUE
        createInfo.alphaMode = VK_DISPLAY_PLANE_ALPHA_OPAQUE_BIT_KHR;
        क्रम (i = 0; i < SDL_arraysize(alphaModes); i++) {
            अगर (planeCaps.supportedAlpha & alphaModes[i]) {
                createInfo.alphaMode = alphaModes[i];
                अवरोध;
            }
        }
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Chose alpha mode 0x%x", createInfo.alphaMode);

        // Found a match, finally! Fill in extent, and break from loop
        createInfo.imageExtent = extent;
        अवरोध;
    }

    SDL_free(physicalDevices);
    physicalDevices = शून्य;

    अगर (physical_Device_सूचकांक == physical_Device_गिनती) {
        SDL_SetError("No usable displays found or requested display out of range");
        जाओ error;
    }

    createInfo.sType = VK_STRUCTURE_TYPE_DISPLAY_SURFACE_CREATE_INFO_KHR;
    createInfo.transform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;
    createInfo.globalAlpha = 1.0f;

    rc = vkCreateDisplayPlaneSurfaceKHR(instance, &createInfo, allocator, surface);
    अगर (rc != VK_SUCCESS) {
        SDL_SetError("vkCreateDisplayPlaneSurfaceKHR failed: %s", SDL_Vulkan_Get_परिणाम_String(rc));
        जाओ error;
    }
    SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Created surface");
    वापस true;

error:
    SDL_free(physicalDevices);
    वापस false;
}

व्योम SDL_Vulkan_DestroySurface_Internal(व्योम *vkGetInstanceProcAddr_,
                                        VkInstance instance,
                                        VkSurfaceKHR surface,
                                        स्थिर काष्ठा VkAllocationCallbacks *allocator)
{
    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr =
        (PFN_vkGetInstanceProcAddr)vkGetInstanceProcAddr_;
    PFN_vkDestroySurfaceKHR vkDestroySurfaceKHR =
        (PFN_vkDestroySurfaceKHR)vkGetInstanceProcAddr(
            instance,
            "vkDestroySurfaceKHR");

    अगर (vkDestroySurfaceKHR) {
        vkDestroySurfaceKHR(instance, surface, allocator);
    }
}

#पूर्ण_अगर
