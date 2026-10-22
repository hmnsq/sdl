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

#అన్తర్భావ "SDL_vulkan_internal.h"

#నిర్వచితమైతే SDL_VIDEO_VULKAN

స్థిరరాశి అక్షరం *SDL_Vulkan_Get_ఫలితం_String(Vk_ఫలితం ఫలితం)
{
    ఎంపిక ((పూర్ణాంకం)ఫలితం) {
    స్థితి VK_SUCCESS:
        తిరిగి "VK_SUCCESS";
    స్థితి VK_NOT_READY:
        తిరిగి "VK_NOT_READY";
    స్థితి VK_TIMEOUT:
        తిరిగి "VK_TIMEOUT";
    స్థితి VK_EVENT_సమితి:
        తిరిగి "VK_EVENT_SET";
    స్థితి VK_EVENT_RESET:
        తిరిగి "VK_EVENT_RESET";
    స్థితి VK_INCOMPLETE:
        తిరిగి "VK_INCOMPLETE";
    స్థితి VK_ERROR_బహిర్గతం_యొక్క_HOST_జ్ఞాపకం:
        తిరిగి "VK_ERROR_OUT_OF_HOST_MEMORY";
    స్థితి VK_ERROR_బహిర్గతం_యొక్క_DEVICE_జ్ఞాపకం:
        తిరిగి "VK_ERROR_OUT_OF_DEVICE_MEMORY";
    స్థితి VK_ERROR_INITIALIZATION_FAILED:
        తిరిగి "VK_ERROR_INITIALIZATION_FAILED";
    స్థితి VK_ERROR_DEVICE_కోల్పోయిన:
        తిరిగి "VK_ERROR_DEVICE_LOST";
    స్థితి VK_ERROR_జ్ఞాపకం_MAP_FAILED:
        తిరిగి "VK_ERROR_MEMORY_MAP_FAILED";
    స్థితి VK_ERROR_LAYER_NOT_PRESENT:
        తిరిగి "VK_ERROR_LAYER_NOT_PRESENT";
    స్థితి VK_ERROR_EXTENSION_NOT_PRESENT:
        తిరిగి "VK_ERROR_EXTENSION_NOT_PRESENT";
    స్థితి VK_ERROR_FEATURE_NOT_PRESENT:
        తిరిగి "VK_ERROR_FEATURE_NOT_PRESENT";
    స్థితి VK_ERROR_INCOMPATIBLE_DRIVER:
        తిరిగి "VK_ERROR_INCOMPATIBLE_DRIVER";
    స్థితి VK_ERROR_TOO_MANY_OBJECTS:
        తిరిగి "VK_ERROR_TOO_MANY_OBJECTS";
    స్థితి VK_ERROR_FORMAT_NOT_SUPPORTED:
        తిరిగి "VK_ERROR_FORMAT_NOT_SUPPORTED";
    స్థితి VK_ERROR_FRAGMENTED_POOL:
        తిరిగి "VK_ERROR_FRAGMENTED_POOL";
    స్థితి VK_ERROR_UNKNOWN:
        తిరిగి "VK_ERROR_UNKNOWN";
    స్థితి VK_ERROR_బహిర్గతం_యొక్క_POOL_జ్ఞాపకం:
        తిరిగి "VK_ERROR_OUT_OF_POOL_MEMORY";
    స్థితి VK_ERROR_INVALID_EXTERNAL_HANDLE:
        తిరిగి "VK_ERROR_INVALID_EXTERNAL_HANDLE";
    స్థితి VK_ERROR_FRAGMENTATION:
        తిరిగి "VK_ERROR_FRAGMENTATION";
    స్థితి VK_ERROR_INVALID_OPAQUE_CAPTURE_చిరునామా:
        తిరిగి "VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS";
    స్థితి VK_ERROR_SURFACE_కోల్పోయిన_KHR:
        తిరిగి "VK_ERROR_SURFACE_LOST_KHR";
    స్థితి VK_ERROR_NATIVE_కిటికీ_లోపల_USE_KHR:
        తిరిగి "VK_ERROR_NATIVE_WINDOW_IN_USE_KHR";
    స్థితి VK_SUBOPTIMAL_KHR:
        తిరిగి "VK_SUBOPTIMAL_KHR";
    స్థితి VK_ERROR_బహిర్గతం_యొక్క_DATE_KHR:
        తిరిగి "VK_ERROR_OUT_OF_DATE_KHR";
    స్థితి VK_ERROR_INCOMPATIBLE_DISPLAY_KHR:
        తిరిగి "VK_ERROR_INCOMPATIBLE_DISPLAY_KHR";
    స్థితి VK_ERROR_VALIDATION_FAILED_EXT:
        తిరిగి "VK_ERROR_VALIDATION_FAILED_EXT";
    స్థితి VK_ERROR_INVALID_SHADER_NV:
        తిరిగి "VK_ERROR_INVALID_SHADER_NV";
#ఒకవేళ VK_శీర్షిక_సంస్కరణ >= 135 && VK_శీర్షిక_సంస్కరణ < 162
    స్థితి VK_ERROR_INCOMPATIBLE_సంస్కరణ_KHR:
        తిరిగి "VK_ERROR_INCOMPATIBLE_VERSION_KHR";
#అయితే_ముగింపు
    స్థితి VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT:
        తిరిగి "VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT";
    స్థితి VK_ERROR_NOT_PERMITTED_EXT:
        తిరిగి "VK_ERROR_NOT_PERMITTED_EXT";
    స్థితి VK_ERROR_నిండిన_SCREEN_EXCLUSIVE_బహుళకం_కోల్పోయిన_EXT:
        తిరిగి "VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT";
    స్థితి VK_THREAD_IDLE_KHR:
        తిరిగి "VK_THREAD_IDLE_KHR";
    స్థితి VK_THREAD_పూర్తి_KHR:
        తిరిగి "VK_THREAD_DONE_KHR";
    స్థితి VK_OPERATION_DEFERRED_KHR:
        తిరిగి "VK_OPERATION_DEFERRED_KHR";
    స్థితి VK_OPERATION_NOT_DEFERRED_KHR:
        తిరిగి "VK_OPERATION_NOT_DEFERRED_KHR";
    స్థితి VK_PIPELINE_COMPILE_REQUIRED_EXT:
        తిరిగి "VK_PIPELINE_COMPILE_REQUIRED_EXT";
    అప్రమేయ:
        ఆపు;
    }
    ఒకవేళ (ఫలితం < 0) {
        తిరిగి "VK_ERROR_<Unknown>";
    }
    తిరిగి "VK_<Unknown>";
}

VkExtensionProperties *SDL_Vulkan_CreateInstanceExtensionsList(
    PFN_vkEnumerateInstanceExtensionProperties vkEnumerateInstanceExtensionProperties,
    Uint32 *extension_లెక్క)
{
    Uint32 లెక్క = 0;
    Vk_ఫలితం rc = vkEnumerateInstanceExtensionProperties(ఖాళీ, &లెక్క, ఖాళీ);
    VkExtensionProperties *ఫలితం;

    ఒకవేళ (rc == VK_ERROR_INCOMPATIBLE_DRIVER) {
        // Avoid the ERR_MAX_STRLEN limit by passing part of the message as a string argument.
        SDL_సమితి_Error(
            "You probably don't have a working Vulkan driver installed. %s %s %s(%d)",
            "Getting Vulkan extensions failed:",
            "vkEnumerateInstanceExtensionProperties returned",
            SDL_Vulkan_Get_ఫలితం_String(rc),
            (పూర్ణాంకం)rc);
        తిరిగి ఖాళీ;
    } లేకపోతే ఒకవేళ (rc != VK_SUCCESS) {
        SDL_సమితి_Error(
            "Getting Vulkan extensions failed: vkEnumerateInstanceExtensionProperties returned "
            "%s(%d)",
            SDL_Vulkan_Get_ఫలితం_String(rc),
            (పూర్ణాంకం)rc);
        తిరిగి ఖాళీ;
    }

    ఒకవేళ (లెక్క == 0) {
        ఫలితం = (VkExtensionProperties *)SDL_calloc(1, పరిమాణం(VkExtensionProperties)); // so we can return non-null
    } లేకపోతే {
        ఫలితం = (VkExtensionProperties *)SDL_calloc(లెక్క, పరిమాణం(VkExtensionProperties));
    }

    ఒకవేళ (!ఫలితం) {
        తిరిగి ఖాళీ;
    }

    rc = vkEnumerateInstanceExtensionProperties(ఖాళీ, &లెక్క, ఫలితం);
    ఒకవేళ (rc != VK_SUCCESS) {
        SDL_సమితి_Error(
            "Getting Vulkan extensions failed: vkEnumerateInstanceExtensionProperties returned "
            "%s(%d)",
            SDL_Vulkan_Get_ఫలితం_String(rc),
            (పూర్ణాంకం)rc);
        SDL_free(ఫలితం);
        తిరిగి ఖాళీ;
    }
    *extension_లెక్క = లెక్క;
    తిరిగి ఫలితం;
}

// Alpha modes, in order of preference
స్థిర స్థిరరాశి Vk_Display_Plane_Alpha_Flag_బిట్లు_KHR alphaModes[4] = {
    VK_DISPLAY_PLANE_ALPHA_OPAQUE_బిట్టు_KHR,
    VK_DISPLAY_PLANE_ALPHA_GLOBAL_బిట్టు_KHR,
    VK_DISPLAY_PLANE_ALPHA_చొప్పున_PIXEL_బిట్టు_KHR,
    VK_DISPLAY_PLANE_ALPHA_చొప్పున_PIXEL_PREMULTIPLIED_బిట్టు_KHR,
};

bool SDL_Vulkan_Display_CreateSurface(శూన్య *vkGetInstanceProcAddr_,
                                      VkInstance instance,
                                      స్థిరరాశి నిర్మాణం Vk_కేటాయింపు_Callbacks *allocator,
                                      VkSurfaceKHR *surface)
{
    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr =
        (PFN_vkGetInstanceProcAddr)vkGetInstanceProcAddr_;
#నిర్వచించు VULKAN_INSTANCE_FUNCTION(name) \
    PFN_##name name = (PFN_##name)vkGetInstanceProcAddr((VkInstance)instance, #name)
    VULKAN_INSTANCE_FUNCTION(vkEnumeratePhysicalDevices);
    VULKAN_INSTANCE_FUNCTION(vkGetPhysicalDeviceDisplayPropertiesKHR);
    VULKAN_INSTANCE_FUNCTION(vk_Get_Display_బహుళకం_Properties_KHR);
    VULKAN_INSTANCE_FUNCTION(vkGetPhysicalDeviceDisplayPlanePropertiesKHR);
    VULKAN_INSTANCE_FUNCTION(vkGetDisplayPlaneCapabilitiesKHR);
    VULKAN_INSTANCE_FUNCTION(vkGetDisplayPlaneSupportedDisplaysKHR);
    VULKAN_INSTANCE_FUNCTION(vkCreateDisplayPlaneSurfaceKHR);
#నిర్వచనం_రద్దు VULKAN_INSTANCE_FUNCTION
    VkDisplaySurfaceCreateInfoKHR createInfo;
    Vk_ఫలితం rc;
    uint32_t physical_Device_లెక్క = 0;
    VkPhysicalDevice *physicalDevices = ఖాళీ;
    uint32_t physical_Device_సూచీ;
    స్థిరరాశి అక్షరం *chosenDisplayId;
    పూర్ణాంకం displayId = 0; // Counting from physical device 0, display 0

    ఒకవేళ (!vkEnumeratePhysicalDevices ||
        !vkGetPhysicalDeviceDisplayPropertiesKHR ||
        !vk_Get_Display_బహుళకం_Properties_KHR ||
        !vkGetPhysicalDeviceDisplayPlanePropertiesKHR ||
        !vkGetDisplayPlaneCapabilitiesKHR ||
        !vkGetDisplayPlaneSupportedDisplaysKHR ||
        !vkCreateDisplayPlaneSurfaceKHR) {
        SDL_సమితి_Error(VK_KHR_DISPLAY_EXTENSION_NAME " extension is not enabled in the Vulkan instance.");
        వెళ్ళు error;
    }
    chosenDisplayId = SDL_GetHint(SDL_HINT_VULKAN_DISPLAY);
    ఒకవేళ (chosenDisplayId) {
        displayId = SDL_atoi(chosenDisplayId);
    }

    // Enumerate physical devices
    rc = vkEnumeratePhysicalDevices(instance, &physical_Device_లెక్క, ఖాళీ);
    ఒకవేళ (rc != VK_SUCCESS) {
        SDL_సమితి_Error("Could not enumerate Vulkan physical devices");
        వెళ్ళు error;
    }

    ఒకవేళ (physical_Device_లెక్క == 0) {
        SDL_సమితి_Error("No Vulkan physical devices");
        వెళ్ళు error;
    }

    physicalDevices = (VkPhysicalDevice *)SDL_malloc(పరిమాణం(VkPhysicalDevice) * physical_Device_లెక్క);
    ఒకవేళ (!physicalDevices) {
        వెళ్ళు error;
    }

    rc = vkEnumeratePhysicalDevices(instance, &physical_Device_లెక్క, physicalDevices);
    ఒకవేళ (rc != VK_SUCCESS) {
        SDL_సమితి_Error("Error enumerating physical devices");
        వెళ్ళు error;
    }

    కొరకు (physical_Device_సూచీ = 0; physical_Device_సూచీ < physical_Device_లెక్క; physical_Device_సూచీ++) {
        VkPhysicalDevice physicalDevice = physicalDevices[physical_Device_సూచీ];
        uint32_t display_Properties_లెక్క = 0;
        VkDisplayPropertiesKHR *displayProperties = ఖాళీ;
        uint32_t display_బహుళకం_Properties_లెక్క = 0;
        Vk_Display_బహుళకం_Properties_KHR *display_బహుళకం_Properties = ఖాళీ;
        పూర్ణాంకం ఉత్తమ_సరిపోలిక_సూచీ = -1;
        uint32_t refresh_రేటు_2 = 0;
        uint32_t i;
        uint32_t display_Plane_Properties_లెక్క = 0;
        పూర్ణాంకం plane_సూచీ = -1;
        VkDisplayKHR display;
        VkDisplayPlanePropertiesKHR *displayPlaneProperties = ఖాళీ;
        VkExtent2D extent;
        VkDisplayPlaneCapabilitiesKHR planeCaps = { 0 };

        // Get information about the physical displays
        rc = vkGetPhysicalDeviceDisplayPropertiesKHR(physicalDevice, &display_Properties_లెక్క, ఖాళీ);
        ఒకవేళ (rc != VK_SUCCESS || display_Properties_లెక్క == 0) {
            // This device has no physical device display properties, move on to next.
            కొనసాగు;
        }
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Number of display properties for device %u: %u",
                     physical_Device_సూచీ, display_Properties_లెక్క);

        ఒకవేళ (displayId < 0 || (uint32_t)displayId >= display_Properties_లెక్క) {
            // Display id specified was higher than number of available displays, move to next physical device.
            displayId -= display_Properties_లెక్క;
            కొనసాగు;
        }

        displayProperties = (VkDisplayPropertiesKHR *)SDL_malloc(పరిమాణం(VkDisplayPropertiesKHR) * display_Properties_లెక్క);
        ఒకవేళ (!displayProperties) {
            వెళ్ళు error;
        }

        rc = vkGetPhysicalDeviceDisplayPropertiesKHR(physicalDevice, &display_Properties_లెక్క, displayProperties);
        ఒకవేళ (rc != VK_SUCCESS || display_Properties_లెక్క == 0) {
            SDL_free(displayProperties);
            SDL_సమితి_Error("Error enumerating physical device displays");
            వెళ్ళు error;
        }

        display = displayProperties[displayId].display;
        extent = displayProperties[displayId].physicalResolution;
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Display: %s Native resolution: %ux%u",
                     displayProperties[displayId].displayName, extent.వెడల్పు, extent.ఎత్తు);

        SDL_free(displayProperties);
        displayProperties = ఖాళీ;

        // Get display mode properties for the chosen display
        rc = vk_Get_Display_బహుళకం_Properties_KHR(physicalDevice, display, &display_బహుళకం_Properties_లెక్క, ఖాళీ);
        ఒకవేళ (rc != VK_SUCCESS || display_బహుళకం_Properties_లెక్క == 0) {
            SDL_సమితి_Error("Error enumerating display modes");
            వెళ్ళు error;
        }
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Number of display modes: %u", display_బహుళకం_Properties_లెక్క);

        display_బహుళకం_Properties = (Vk_Display_బహుళకం_Properties_KHR *)SDL_malloc(పరిమాణం(Vk_Display_బహుళకం_Properties_KHR) * display_బహుళకం_Properties_లెక్క);
        ఒకవేళ (!display_బహుళకం_Properties) {
            వెళ్ళు error;
        }

        rc = vk_Get_Display_బహుళకం_Properties_KHR(physicalDevice, display, &display_బహుళకం_Properties_లెక్క, display_బహుళకం_Properties);
        ఒకవేళ (rc != VK_SUCCESS || display_బహుళకం_Properties_లెక్క == 0) {
            SDL_సమితి_Error("Error enumerating display modes");
            SDL_free(display_బహుళకం_Properties);
            వెళ్ళు error;
        }

        // Try to find a display mode that matches the native resolution
        కొరకు (i = 0; i < display_బహుళకం_Properties_లెక్క; ++i) {
            ఒకవేళ (display_బహుళకం_Properties[i].parameters.visibleRegion.వెడల్పు == extent.వెడల్పు &&
                display_బహుళకం_Properties[i].parameters.visibleRegion.ఎత్తు == extent.ఎత్తు &&
                display_బహుళకం_Properties[i].parameters.refresh_రేటు_2 > refresh_రేటు_2) {
                ఉత్తమ_సరిపోలిక_సూచీ = i;
                refresh_రేటు_2 = display_బహుళకం_Properties[i].parameters.refresh_రేటు_2;
            }
        }

        ఒకవేళ (ఉత్తమ_సరిపోలిక_సూచీ < 0) {
            SDL_సమితి_Error("Found no matching display mode");
            SDL_free(display_బహుళకం_Properties);
            వెళ్ళు error;
        }

        SDL_zero(createInfo);
        createInfo.display_బహుళకం = display_బహుళకం_Properties[ఉత్తమ_సరిపోలిక_సూచీ].display_బహుళకం;
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Matching mode %ux%u with refresh rate %u",
                     display_బహుళకం_Properties[ఉత్తమ_సరిపోలిక_సూచీ].parameters.visibleRegion.వెడల్పు,
                     display_బహుళకం_Properties[ఉత్తమ_సరిపోలిక_సూచీ].parameters.visibleRegion.ఎత్తు,
                     refresh_రేటు_2);

        SDL_free(display_బహుళకం_Properties);
        display_బహుళకం_Properties = ఖాళీ;

        // Try to find a plane index that supports our display
        rc = vkGetPhysicalDeviceDisplayPlanePropertiesKHR(physicalDevice, &display_Plane_Properties_లెక్క, ఖాళీ);
        ఒకవేళ (rc != VK_SUCCESS || display_Plane_Properties_లెక్క == 0) {
            SDL_సమితి_Error("Error enumerating display planes");
            వెళ్ళు error;
        }
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Number of display planes: %u", display_Plane_Properties_లెక్క);

        displayPlaneProperties = (VkDisplayPlanePropertiesKHR *)SDL_malloc(పరిమాణం(VkDisplayPlanePropertiesKHR) * display_Plane_Properties_లెక్క);
        ఒకవేళ (!displayPlaneProperties) {
            వెళ్ళు error;
        }

        rc = vkGetPhysicalDeviceDisplayPlanePropertiesKHR(physicalDevice, &display_Plane_Properties_లెక్క, displayPlaneProperties);
        ఒకవేళ (rc != VK_SUCCESS || display_Plane_Properties_లెక్క == 0) {
            SDL_సమితి_Error("Error enumerating display plane properties");
            SDL_free(displayPlaneProperties);
            వెళ్ళు error;
        }

        కొరకు (i = 0; i < display_Plane_Properties_లెక్క; ++i) {
            uint32_t plane_Supported_Displays_లెక్క = 0;
            VkDisplayKHR *planeSupportedDisplays = ఖాళీ;
            uint32_t j;

            // Check if plane is attached to a display, if not, continue.
            ఒకవేళ (displayPlaneProperties[i].currentDisplay == VK_NULL_HANDLE) {
                కొనసాగు;
            }

            // Check supported displays for this plane.
            rc = vkGetDisplayPlaneSupportedDisplaysKHR(physicalDevice, i, &plane_Supported_Displays_లెక్క, ఖాళీ);
            ఒకవేళ (rc != VK_SUCCESS || plane_Supported_Displays_లెక్క == 0) {
                కొనసాగు; // No supported displays, on to next plane.
            }

            SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Number of supported displays for plane %u: %u", i, plane_Supported_Displays_లెక్క);

            planeSupportedDisplays = (VkDisplayKHR *)SDL_malloc(పరిమాణం(VkDisplayKHR) * plane_Supported_Displays_లెక్క);
            ఒకవేళ (!planeSupportedDisplays) {
                SDL_free(displayPlaneProperties);
                వెళ్ళు error;
            }

            rc = vkGetDisplayPlaneSupportedDisplaysKHR(physicalDevice, i, &plane_Supported_Displays_లెక్క, planeSupportedDisplays);
            ఒకవేళ (rc != VK_SUCCESS || plane_Supported_Displays_లెక్క == 0) {
                SDL_సమితి_Error("Error enumerating supported displays, or no supported displays");
                SDL_free(planeSupportedDisplays);
                SDL_free(displayPlaneProperties);
                వెళ్ళు error;
            }

            కొరకు (j = 0; j < plane_Supported_Displays_లెక్క && planeSupportedDisplays[j] != display; ++j) {
            }

            SDL_free(planeSupportedDisplays);
            planeSupportedDisplays = ఖాళీ;

            ఒకవేళ (j == plane_Supported_Displays_లెక్క) {
                // This display is not supported for this plane, move on.
                కొనసాగు;
            }

            rc = vkGetDisplayPlaneCapabilitiesKHR(physicalDevice, createInfo.display_బహుళకం, i, &planeCaps);
            ఒకవేళ (rc != VK_SUCCESS) {
                SDL_సమితి_Error("Error getting display plane capabilities");
                SDL_free(displayPlaneProperties);
                వెళ్ళు error;
            }

            // Check if plane fulfills extent requirements.
            ఒకవేళ (extent.వెడల్పు >= planeCaps.minDstExtent.వెడల్పు && extent.ఎత్తు >= planeCaps.minDstExtent.ఎత్తు &&
                extent.వెడల్పు <= planeCaps.maxDstExtent.వెడల్పు && extent.ఎత్తు <= planeCaps.maxDstExtent.ఎత్తు) {
                // If it does, choose this plane.
                SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Choosing plane %u, minimum extent %ux%u maximum extent %ux%u", i,
                             planeCaps.minDstExtent.వెడల్పు, planeCaps.minDstExtent.ఎత్తు,
                             planeCaps.maxDstExtent.వెడల్పు, planeCaps.maxDstExtent.ఎత్తు);
                plane_సూచీ = i;
                ఆపు;
            }
        }

        ఒకవేళ (plane_సూచీ < 0) {
            SDL_సమితి_Error("No plane supports the selected resolution");
            SDL_free(displayPlaneProperties);
            వెళ్ళు error;
        }

        createInfo.plane_సూచీ = plane_సూచీ;
        createInfo.plane_దొంతర_సూచీ = displayPlaneProperties[plane_సూచీ].current_దొంతర_సూచీ;
        SDL_free(displayPlaneProperties);
        displayPlaneProperties = ఖాళీ;

        // Find a supported alpha mode. Not all planes support OPAQUE
        createInfo.alpha_బహుళకం = VK_DISPLAY_PLANE_ALPHA_OPAQUE_బిట్టు_KHR;
        కొరకు (i = 0; i < SDL_arraysize(alphaModes); i++) {
            ఒకవేళ (planeCaps.supportedAlpha & alphaModes[i]) {
                createInfo.alpha_బహుళకం = alphaModes[i];
                ఆపు;
            }
        }
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Chose alpha mode 0x%x", createInfo.alpha_బహుళకం);

        // Found a match, finally! Fill in extent, and break from loop
        createInfo.imageExtent = extent;
        ఆపు;
    }

    SDL_free(physicalDevices);
    physicalDevices = ఖాళీ;

    ఒకవేళ (physical_Device_సూచీ == physical_Device_లెక్క) {
        SDL_సమితి_Error("No usable displays found or requested display out of range");
        వెళ్ళు error;
    }

    createInfo.sType = VK_STRUCTURE_TYPE_DISPLAY_SURFACE_CREATE_INFO_KHR;
    createInfo.transform = VK_SURFACE_TRANSFORM_తటస్థం_బిట్టు_KHR;
    createInfo.globalAlpha = 1.0f;

    rc = vkCreateDisplayPlaneSurfaceKHR(instance, &createInfo, allocator, surface);
    ఒకవేళ (rc != VK_SUCCESS) {
        SDL_సమితి_Error("vkCreateDisplayPlaneSurfaceKHR failed: %s", SDL_Vulkan_Get_ఫలితం_String(rc));
        వెళ్ళు error;
    }
    SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Created surface");
    తిరిగి true;

error:
    SDL_free(physicalDevices);
    తిరిగి false;
}

శూన్య SDL_Vulkan_Destroy_Surface_అంతర్గత(శూన్య *vkGetInstanceProcAddr_,
                                        VkInstance instance,
                                        VkSurfaceKHR surface,
                                        స్థిరరాశి నిర్మాణం Vk_కేటాయింపు_Callbacks *allocator)
{
    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr =
        (PFN_vkGetInstanceProcAddr)vkGetInstanceProcAddr_;
    PFN_vkDestroySurfaceKHR vkDestroySurfaceKHR =
        (PFN_vkDestroySurfaceKHR)vkGetInstanceProcAddr(
            instance,
            "vkDestroySurfaceKHR");

    ఒకవేళ (vkDestroySurfaceKHR) {
        vkDestroySurfaceKHR(instance, surface, allocator);
    }
}

#అయితే_ముగింపు
