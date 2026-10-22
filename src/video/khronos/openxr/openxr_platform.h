#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ OPENXR_PLATFORM_H_
#ವ್ಯಾಖ್ಯಾನಿಸು OPENXR_PLATFORM_H_ 1

/*
** Copyright 2017-2026 The Khronos Group Inc.
**
** SPDX-License-Identifier: Apache-2.0 OR MIT
*/

/*
** This header is generated from the Khronos OpenXR XML API Registry.
**
*/

#ಅನ್ತರ್ಭಾವ "openxr.h"

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __cplusplus
ಬಾಹ್ಯ "C" {
#ಆದರೆ_ಅಂತ್ಯ


#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ XR_USE_PLATFORM_ANDROID

// XR_KHR_android_thread_settings is a preprocessor guard. Do not pass it to API calls.
#ವ್ಯಾಖ್ಯಾನಿಸು XR_KHR_android_thread_settings 1
#ವ್ಯಾಖ್ಯಾನಿಸು XR_KHR_android_thread_settings_SPEC_ಆವೃತ್ತಿ 6
#ವ್ಯಾಖ್ಯಾನಿಸು XR_KHR_ANDROID_THREAD_SETTINGS_EXTENSION_NAME "XR_KHR_android_thread_settings"

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ XrAndroidThreadTypeKHR {
    XR_ANDROID_THREAD_TYPE_APPLICATION_MAIN_KHR = 1,
    XR_ANDROID_THREAD_TYPE_APPLICATION_ಕೆಲಸಗಾರ_KHR = 2,
    XR_ANDROID_THREAD_TYPE_RENDERER_MAIN_KHR = 3,
    XR_ANDROID_THREAD_TYPE_RENDERER_ಕೆಲಸಗಾರ_KHR = 4,
    XR_ANDROID_THREAD_TYPE_MAX_ENUM_KHR = 0x7FFFFFFF
} XrAndroidThreadTypeKHR;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ Xr_ಫಲಿತಾಂಶ (XRAPI_PTR *PFN_xr_ಗಣ_Android_Application_Thread_KHR)(XrSession session, XrAndroidThreadTypeKHR threadType, uint32_t threadId);

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ XR_NO_PROTOTYPES
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ XR_EXTENSION_PROTOTYPES
XRAPI_ATTR Xr_ಫಲಿತಾಂಶ XRAPI_CALL xr_ಗಣ_Android_Application_Thread_KHR(
    XrSession                                   session,
    XrAndroidThreadTypeKHR                      threadType,
    uint32_t                                    threadId);
#ಆದರೆ_ಅಂತ್ಯ /* XR_EXTENSION_PROTOTYPES */
#ಆದರೆ_ಅಂತ್ಯ /* !XR_NO_PROTOTYPES */
#ಆದರೆ_ಅಂತ್ಯ /* XR_USE_PLATFORM_ANDROID */

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ XR_USE_PLATFORM_ANDROID

// XR_KHR_android_surface_swapchain is a preprocessor guard. Do not pass it to API calls.
#ವ್ಯಾಖ್ಯಾನಿಸು XR_KHR_android_surface_swapchain 1
#ವ್ಯಾಖ್ಯಾನಿಸು XR_KHR_android_surface_swapchain_SPEC_ಆವೃತ್ತಿ 4
#ವ್ಯಾಖ್ಯಾನಿಸು XR_KHR_ANDROID_SURFACE_SWAPCHAIN_EXTENSION_NAME "XR_KHR_android_surface_swapchain"
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ Xr_ಫಲಿತಾಂಶ (XRAPI_PTR *PFN_xrCreateSwapchainAndroidSurfaceKHR)(XrSession session, ಸ್ಥಿರಾಂಕ XrSwapchainCreateInfo* info, XrSwapchain* swapchain, jobject* surface);

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ XR_NO_PROTOTYPES
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ XR_EXTENSION_PROTOTYPES
XRAPI_ATTR Xr_ಫಲಿತಾಂಶ XRAPI_CALL xrCreateSwapchainAndroidSurfaceKHR(
    XrSession                                   session,
    ಸ್ಥಿರಾಂಕ XrSwapchainCreateInfo*                info,
    XrSwapchain*                                swapchain,
    jobject*                                    surface);
#ಆದರೆ_ಅಂತ್ಯ /* XR_EXTENSION_PROTOTYPES */
#ಆದರೆ_ಅಂತ್ಯ /* !XR_NO_PROTOTYPES */
#ಆದರೆ_ಅಂತ್ಯ /* XR_USE_PLATFORM_ANDROID */

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ XR_USE_PLATFORM_ANDROID

// XR_KHR_android_create_instance is a preprocessor guard. Do not pass it to API calls.
#ವ್ಯಾಖ್ಯಾನಿಸು XR_KHR_android_create_instance 1
#ವ್ಯಾಖ್ಯಾನಿಸು XR_KHR_android_create_instance_SPEC_ಆವೃತ್ತಿ 3
#ವ್ಯಾಖ್ಯಾನಿಸು XR_KHR_ANDROID_CREATE_INSTANCE_EXTENSION_NAME "XR_KHR_android_create_instance"
// XrInstanceCreateInfoAndroidKHR extends XrInstanceCreateInfo
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ XrInstanceCreateInfoAndroidKHR {
    XrStructureType             type;
    ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ* XR_MAY_ALIAS    ಮುಂದಿನ;
    ಶೂನ್ಯ* XR_MAY_ALIAS          applicationVM;
    ಶೂನ್ಯ* XR_MAY_ALIAS          applicationActivity;
} XrInstanceCreateInfoAndroidKHR;

#ಆದರೆ_ಅಂತ್ಯ /* XR_USE_PLATFORM_ANDROID */

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ XR_USE_GRAPHICS_API_VULKAN

// XR_KHR_vulkan_swapchain_format_list is a preprocessor guard. Do not pass it to API calls.
#ವ್ಯಾಖ್ಯಾನಿಸು XR_KHR_vulkan_swapchain_format_list 1
#ವ್ಯಾಖ್ಯಾನಿಸು XR_KHR_vulkan_swapchain_format_list_SPEC_ಆವೃತ್ತಿ 5
#ವ್ಯಾಖ್ಯಾನಿಸು XR_KHR_VULKAN_SWAPCHAIN_FORMAT_LIST_EXTENSION_NAME "XR_KHR_vulkan_swapchain_format_list"
// XrVulkanSwapchainFormatListCreateInfoKHR extends XrSwapchainCreateInfo
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ XrVulkanSwapchainFormatListCreateInfoKHR {
    XrStructureType             type;
    ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ* XR_MAY_ALIAS    ಮುಂದಿನ;
    uint32_t                    view_Format_ಎಣಿಕೆ;
    ಸ್ಥಿರಾಂಕ VkFormat*             viewFormats;
} XrVulkanSwapchainFormatListCreateInfoKHR;

#ಆದರೆ_ಅಂತ್ಯ /* XR_USE_GRAPHICS_API_VULKAN */

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ XR_USE_GRAPHICS_API_OPENGL

// XR_KHR_opengl_enable is a preprocessor guard. Do not pass it to API calls.
#ವ್ಯಾಖ್ಯಾನಿಸು XR_KHR_opengl_enable 1
#ವ್ಯಾಖ್ಯಾನಿಸು XR_KHR_opengl_enable_SPEC_ಆವೃತ್ತಿ 12
#ವ್ಯಾಖ್ಯಾನಿಸು XR_KHR_OPENGL_ENABLE_EXTENSION_NAME "XR_KHR_opengl_enable"
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ XR_USE_PLATFORM_WIN32
// XrGraphicsBindingOpenGLWin32KHR extends XrSessionCreateInfo
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ XrGraphicsBindingOpenGLWin32KHR {
    XrStructureType             type;
    ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ* XR_MAY_ALIAS    ಮುಂದಿನ;
    HDC                         hDC;
    HGLRC                       hGLRC;
} XrGraphicsBindingOpenGLWin32KHR;
#ಆದರೆ_ಅಂತ್ಯ // XR_USE_PLATFORM_WIN32

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ XR_USE_PLATFORM_XLIB
// XrGraphicsBindingOpenGLXlibKHR extends XrSessionCreateInfo
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ XrGraphicsBindingOpenGLXlibKHR {
    XrStructureType             type;
    ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ* XR_MAY_ALIAS    ಮುಂದಿನ;
    Display*                    xDisplay;
    uint32_t                    visualid;
    GLXFBConfig                 glxFBConfig;
    GLXDrawable                 glxDrawable;
    GLXContext                  glxContext;
} XrGraphicsBindingOpenGLXlibKHR;
#ಆದರೆ_ಅಂತ್ಯ // XR_USE_PLATFORM_XLIB

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ XR_USE_PLATFORM_XCB
// XrGraphicsBindingOpenGLXcbKHR extends XrSessionCreateInfo
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ XrGraphicsBindingOpenGLXcbKHR {
    XrStructureType             type;
    ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ* XR_MAY_ALIAS    ಮುಂದಿನ;
    xcb_connection_t*           connection;
    uint32_t                    screen_ಸಂಖ್ಯೆ;
    xcb_glx_fbconfig_t          fbconfigid;
    xcb_visualid_t              visualid;
    xcb_glx_drawable_t          glxDrawable;
    xcb_glx_context_t           glxContext;
} XrGraphicsBindingOpenGLXcbKHR;
#ಆದರೆ_ಅಂತ್ಯ // XR_USE_PLATFORM_XCB

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ XR_USE_PLATFORM_WAYLAND
// XrGraphicsBindingOpenGLWaylandKHR extends XrSessionCreateInfo
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ XrGraphicsBindingOpenGLWaylandKHR {
    XrStructureType             type;
    ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ* XR_MAY_ALIAS    ಮುಂದಿನ;
    ರಚನೆ wl_display*          display;
} XrGraphicsBindingOpenGLWaylandKHR;
#ಆದರೆ_ಅಂತ್ಯ // XR_USE_PLATFORM_WAYLAND

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ XrSwapchainImageOpenGLKHR {
    XrStructureType       type;
    ಶೂನ್ಯ* XR_MAY_ALIAS    ಮುಂದಿನ;
    uint32_t              image;
} XrSwapchainImageOpenGLKHR;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ XrGraphicsRequirementsOpenGLKHR {
    XrStructureType       type;
    ಶೂನ್ಯ* XR_MAY_ALIAS    ಮುಂದಿನ;
    Xr_ಆವೃತ್ತಿ             min_Api_ಆವೃತ್ತಿ_Supported;
    Xr_ಆವೃತ್ತಿ             max_Api_ಆವೃತ್ತಿ_Supported;
} XrGraphicsRequirementsOpenGLKHR;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ Xr_ಫಲಿತಾಂಶ (XRAPI_PTR *PFN_xrGetOpenGLGraphicsRequirementsKHR)(XrInstance instance, XrSystemId systemId, XrGraphicsRequirementsOpenGLKHR* graphicsRequirements);

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ XR_NO_PROTOTYPES
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ XR_EXTENSION_PROTOTYPES
XRAPI_ATTR Xr_ಫಲಿತಾಂಶ XRAPI_CALL xrGetOpenGLGraphicsRequirementsKHR(
    XrInstance                                  instance,
    XrSystemId                                  systemId,
    XrGraphicsRequirementsOpenGLKHR*            graphicsRequirements);
#ಆದರೆ_ಅಂತ್ಯ /* XR_EXTENSION_PROTOTYPES */
#ಆದರೆ_ಅಂತ್ಯ /* !XR_NO_PROTOTYPES */
#ಆದರೆ_ಅಂತ್ಯ /* XR_USE_GRAPHICS_API_OPENGL */

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ XR_USE_GRAPHICS_API_OPENGL_ES

// XR_KHR_opengl_es_enable is a preprocessor guard. Do not pass it to API calls.
#ವ್ಯಾಖ್ಯಾನಿಸು XR_KHR_opengl_es_enable 1
#ವ್ಯಾಖ್ಯಾನಿಸು XR_KHR_opengl_es_enable_SPEC_ಆವೃತ್ತಿ 10
#ವ್ಯಾಖ್ಯಾನಿಸು XR_KHR_OPENGL_ES_ENABLE_EXTENSION_NAME "XR_KHR_opengl_es_enable"
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ XR_USE_PLATFORM_ANDROID
// XrGraphicsBindingOpenGLESAndroidKHR extends XrSessionCreateInfo
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ XrGraphicsBindingOpenGLESAndroidKHR {
    XrStructureType             type;
    ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ* XR_MAY_ALIAS    ಮುಂದಿನ;
    EGLDisplay                  display;
    EGLConfig                   config;
    EGLContext                  context;
} XrGraphicsBindingOpenGLESAndroidKHR;
#ಆದರೆ_ಅಂತ್ಯ // XR_USE_PLATFORM_ANDROID

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ XrSwapchainImageOpenGLESKHR {
    XrStructureType       type;
    ಶೂನ್ಯ* XR_MAY_ALIAS    ಮುಂದಿನ;
    uint32_t              image;
} XrSwapchainImageOpenGLESKHR;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ XrGraphicsRequirementsOpenGLESKHR {
    XrStructureType       type;
    ಶೂನ್ಯ* XR_MAY_ALIAS    ಮುಂದಿನ;
    Xr_ಆವೃತ್ತಿ             min_Api_ಆವೃತ್ತಿ_Supported;
    Xr_ಆವೃತ್ತಿ             max_Api_ಆವೃತ್ತಿ_Supported;
} XrGraphicsRequirementsOpenGLESKHR;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ Xr_ಫಲಿತಾಂಶ (XRAPI_PTR *PFN_xrGetOpenGLESGraphicsRequirementsKHR)(XrInstance instance, XrSystemId systemId, XrGraphicsRequirementsOpenGLESKHR* graphicsRequirements);

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ XR_NO_PROTOTYPES
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ XR_EXTENSION_PROTOTYPES
XRAPI_ATTR Xr_ಫಲಿತಾಂಶ XRAPI_CALL xrGetOpenGLESGraphicsRequirementsKHR(
    XrInstance                                  instance,
    XrSystemId                                  systemId,
    XrGraphicsRequirementsOpenGLESKHR*          graphicsRequirements);
#ಆದರೆ_ಅಂತ್ಯ /* XR_EXTENSION_PROTOTYPES */
#ಆದರೆ_ಅಂತ್ಯ /* !XR_NO_PROTOTYPES */
#ಆದರೆ_ಅಂತ್ಯ /* XR_USE_GRAPHICS_API_OPENGL_ES */

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ XR_USE_GRAPHICS_API_VULKAN

// XR_KHR_vulkan_enable is a preprocessor guard. Do not pass it to API calls.
#ವ್ಯಾಖ್ಯಾನಿಸು XR_KHR_vulkan_enable 1
#ವ್ಯಾಖ್ಯಾನಿಸು XR_KHR_vulkan_enable_SPEC_ಆವೃತ್ತಿ 10
#ವ್ಯಾಖ್ಯಾನಿಸು XR_KHR_VULKAN_ENABLE_EXTENSION_NAME "XR_KHR_vulkan_enable"
// XrGraphicsBindingVulkanKHR extends XrSessionCreateInfo
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ XrGraphicsBindingVulkanKHR {
    XrStructureType             type;
    ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ* XR_MAY_ALIAS    ಮುಂದಿನ;
    VkInstance                  instance;
    VkPhysicalDevice            physicalDevice;
    VkDevice                    device;
    uint32_t                    ಸರತಿ_Family_ಸೂಚ್ಯಂಕ;
    uint32_t                    ಸರತಿ_ಸೂಚ್ಯಂಕ;
} XrGraphicsBindingVulkanKHR;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ XrSwapchainImageVulkanKHR {
    XrStructureType       type;
    ಶೂನ್ಯ* XR_MAY_ALIAS    ಮುಂದಿನ;
    VkImage               image;
} XrSwapchainImageVulkanKHR;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ XrGraphicsRequirementsVulkanKHR {
    XrStructureType       type;
    ಶೂನ್ಯ* XR_MAY_ALIAS    ಮುಂದಿನ;
    Xr_ಆವೃತ್ತಿ             min_Api_ಆವೃತ್ತಿ_Supported;
    Xr_ಆವೃತ್ತಿ             max_Api_ಆವೃತ್ತಿ_Supported;
} XrGraphicsRequirementsVulkanKHR;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ Xr_ಫಲಿತಾಂಶ (XRAPI_PTR *PFN_xrGetVulkanInstanceExtensionsKHR)(XrInstance instance, XrSystemId systemId, uint32_t ಬಫರ್_ಸಾಮರ್ಥ್ಯ_ಒಳಹರಿವು, uint32_t* ಬಫರ್_ಎಣಿಕೆ_Output, ಅಕ್ಷರ* ಬಫರ್_2);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ Xr_ಫಲಿತಾಂಶ (XRAPI_PTR *PFN_xrGetVulkanDeviceExtensionsKHR)(XrInstance instance, XrSystemId systemId, uint32_t ಬಫರ್_ಸಾಮರ್ಥ್ಯ_ಒಳಹರಿವು, uint32_t* ಬಫರ್_ಎಣಿಕೆ_Output, ಅಕ್ಷರ* ಬಫರ್_2);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ Xr_ಫಲಿತಾಂಶ (XRAPI_PTR *PFN_xrGetVulkanGraphicsDeviceKHR)(XrInstance instance, XrSystemId systemId, VkInstance vkInstance, VkPhysicalDevice* vkPhysicalDevice);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ Xr_ಫಲಿತಾಂಶ (XRAPI_PTR *PFN_xrGetVulkanGraphicsRequirementsKHR)(XrInstance instance, XrSystemId systemId, XrGraphicsRequirementsVulkanKHR* graphicsRequirements);

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ XR_NO_PROTOTYPES
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ XR_EXTENSION_PROTOTYPES
XRAPI_ATTR Xr_ಫಲಿತಾಂಶ XRAPI_CALL xrGetVulkanInstanceExtensionsKHR(
    XrInstance                                  instance,
    XrSystemId                                  systemId,
    uint32_t                                    ಬಫರ್_ಸಾಮರ್ಥ್ಯ_ಒಳಹರಿವು,
    uint32_t*                                   ಬಫರ್_ಎಣಿಕೆ_Output,
    ಅಕ್ಷರ*                                       ಬಫರ್_2);

XRAPI_ATTR Xr_ಫಲಿತಾಂಶ XRAPI_CALL xrGetVulkanDeviceExtensionsKHR(
    XrInstance                                  instance,
    XrSystemId                                  systemId,
    uint32_t                                    ಬಫರ್_ಸಾಮರ್ಥ್ಯ_ಒಳಹರಿವು,
    uint32_t*                                   ಬಫರ್_ಎಣಿಕೆ_Output,
    ಅಕ್ಷರ*                                       ಬಫರ್_2);

XRAPI_ATTR Xr_ಫಲಿತಾಂಶ XRAPI_CALL xrGetVulkanGraphicsDeviceKHR(
    XrInstance                                  instance,
    XrSystemId                                  systemId,
    VkInstance                                  vkInstance,
    VkPhysicalDevice*                           vkPhysicalDevice);

XRAPI_ATTR Xr_ಫಲಿತಾಂಶ XRAPI_CALL xrGetVulkanGraphicsRequirementsKHR(
    XrInstance                                  instance,
    XrSystemId                                  systemId,
    XrGraphicsRequirementsVulkanKHR*            graphicsRequirements);
#ಆದರೆ_ಅಂತ್ಯ /* XR_EXTENSION_PROTOTYPES */
#ಆದರೆ_ಅಂತ್ಯ /* !XR_NO_PROTOTYPES */
#ಆದರೆ_ಅಂತ್ಯ /* XR_USE_GRAPHICS_API_VULKAN */

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ XR_USE_GRAPHICS_API_D3D11

// XR_KHR_D3D11_enable is a preprocessor guard. Do not pass it to API calls.
#ವ್ಯಾಖ್ಯಾನಿಸು XR_KHR_D3D11_enable 1
#ವ್ಯಾಖ್ಯಾನಿಸು XR_KHR_D3_D11_enable_SPEC_ಆವೃತ್ತಿ  11
#ವ್ಯಾಖ್ಯಾನಿಸು XR_KHR_D3D11_ENABLE_EXTENSION_NAME "XR_KHR_D3D11_enable"
// XrGraphicsBindingD3D11KHR extends XrSessionCreateInfo
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ XrGraphicsBindingD3D11KHR {
    XrStructureType             type;
    ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ* XR_MAY_ALIAS    ಮುಂದಿನ;
    ID3D11Device*               device;
} XrGraphicsBindingD3D11KHR;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ XrSwapchainImageD3D11KHR {
     XrStructureType      type;
    ಶೂನ್ಯ* XR_MAY_ALIAS    ಮುಂದಿನ;
    ID3D11Texture2D*      texture;
} XrSwapchainImageD3D11KHR;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ XrGraphicsRequirementsD3D11KHR {
    XrStructureType       type;
    ಶೂನ್ಯ* XR_MAY_ALIAS    ಮುಂದಿನ;
    LUID                  adapterLuid;
    D3D_FEATURE_LEVEL     minFeatureLevel;
} XrGraphicsRequirementsD3D11KHR;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ Xr_ಫಲಿತಾಂಶ (XRAPI_PTR *PFN_xrGetD3D11GraphicsRequirementsKHR)(XrInstance instance, XrSystemId systemId, XrGraphicsRequirementsD3D11KHR* graphicsRequirements);

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ XR_NO_PROTOTYPES
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ XR_EXTENSION_PROTOTYPES
XRAPI_ATTR Xr_ಫಲಿತಾಂಶ XRAPI_CALL xrGetD3D11GraphicsRequirementsKHR(
    XrInstance                                  instance,
    XrSystemId                                  systemId,
    XrGraphicsRequirementsD3D11KHR*             graphicsRequirements);
#ಆದರೆ_ಅಂತ್ಯ /* XR_EXTENSION_PROTOTYPES */
#ಆದರೆ_ಅಂತ್ಯ /* !XR_NO_PROTOTYPES */
#ಆದರೆ_ಅಂತ್ಯ /* XR_USE_GRAPHICS_API_D3D11 */

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ XR_USE_GRAPHICS_API_D3D12

// XR_KHR_D3D12_enable is a preprocessor guard. Do not pass it to API calls.
#ವ್ಯಾಖ್ಯಾನಿಸು XR_KHR_D3D12_enable 1
#ವ್ಯಾಖ್ಯಾನಿಸು XR_KHR_D3_D12_enable_SPEC_ಆವೃತ್ತಿ  11
#ವ್ಯಾಖ್ಯಾನಿಸು XR_KHR_D3D12_ENABLE_EXTENSION_NAME "XR_KHR_D3D12_enable"
// XrGraphicsBindingD3D12KHR extends XrSessionCreateInfo
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ XrGraphicsBindingD3D12KHR {
    XrStructureType             type;
    ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ* XR_MAY_ALIAS    ಮುಂದಿನ;
    ID3D12Device*               device;
    ID3_D12_Command_ಸರತಿ*         ಸರತಿ;
} XrGraphicsBindingD3D12KHR;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ XrSwapchainImageD3D12KHR {
     XrStructureType      type;
    ಶೂನ್ಯ* XR_MAY_ALIAS    ಮುಂದಿನ;
    ID3D12Resource*       texture;
} XrSwapchainImageD3D12KHR;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ XrGraphicsRequirementsD3D12KHR {
    XrStructureType       type;
    ಶೂನ್ಯ* XR_MAY_ALIAS    ಮುಂದಿನ;
    LUID                  adapterLuid;
    D3D_FEATURE_LEVEL     minFeatureLevel;
} XrGraphicsRequirementsD3D12KHR;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ Xr_ಫಲಿತಾಂಶ (XRAPI_PTR *PFN_xrGetD3D12GraphicsRequirementsKHR)(XrInstance instance, XrSystemId systemId, XrGraphicsRequirementsD3D12KHR* graphicsRequirements);

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ XR_NO_PROTOTYPES
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ XR_EXTENSION_PROTOTYPES
XRAPI_ATTR Xr_ಫಲಿತಾಂಶ XRAPI_CALL xrGetD3D12GraphicsRequirementsKHR(
    XrInstance                                  instance,
    XrSystemId                                  systemId,
    XrGraphicsRequirementsD3D12KHR*             graphicsRequirements);
#ಆದರೆ_ಅಂತ್ಯ /* XR_EXTENSION_PROTOTYPES */
#ಆದರೆ_ಅಂತ್ಯ /* !XR_NO_PROTOTYPES */
#ಆದರೆ_ಅಂತ್ಯ /* XR_USE_GRAPHICS_API_D3D12 */

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ XR_USE_GRAPHICS_API_METAL

// XR_KHR_metal_enable is a preprocessor guard. Do not pass it to API calls.
#ವ್ಯಾಖ್ಯಾನಿಸು XR_KHR_metal_enable 1
#ವ್ಯಾಖ್ಯಾನಿಸು XR_KHR_metal_enable_SPEC_ಆವೃತ್ತಿ  3
#ವ್ಯಾಖ್ಯಾನಿಸು XR_KHR_METAL_ENABLE_EXTENSION_NAME "XR_KHR_metal_enable"
// XrGraphicsBindingMetalKHR extends XrSessionCreateInfo
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ XrGraphicsBindingMetalKHR {
    XrStructureType             type;
    ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ* XR_MAY_ALIAS    ಮುಂದಿನ;
    ಶೂನ್ಯ* XR_MAY_ALIAS          command_ಸರತಿ;
} XrGraphicsBindingMetalKHR;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ XrSwapchainImageMetalKHR {
    XrStructureType       type;
    ಶೂನ್ಯ* XR_MAY_ALIAS    ಮುಂದಿನ;
    ಶೂನ್ಯ* XR_MAY_ALIAS    texture;
} XrSwapchainImageMetalKHR;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ XrGraphicsRequirementsMetalKHR {
    XrStructureType       type;
    ಶೂನ್ಯ* XR_MAY_ALIAS    ಮುಂದಿನ;
    ಶೂನ್ಯ* XR_MAY_ALIAS    metalDevice;
} XrGraphicsRequirementsMetalKHR;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ Xr_ಫಲಿತಾಂಶ (XRAPI_PTR *PFN_xrGetMetalGraphicsRequirementsKHR)(XrInstance instance, XrSystemId systemId, XrGraphicsRequirementsMetalKHR* graphicsRequirements);

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ XR_NO_PROTOTYPES
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ XR_EXTENSION_PROTOTYPES
XRAPI_ATTR Xr_ಫಲಿತಾಂಶ XRAPI_CALL xrGetMetalGraphicsRequirementsKHR(
    XrInstance                                  instance,
    XrSystemId                                  systemId,
    XrGraphicsRequirementsMetalKHR*             graphicsRequirements);
#ಆದರೆ_ಅಂತ್ಯ /* XR_EXTENSION_PROTOTYPES */
#ಆದರೆ_ಅಂತ್ಯ /* !XR_NO_PROTOTYPES */
#ಆದರೆ_ಅಂತ್ಯ /* XR_USE_GRAPHICS_API_METAL */

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ XR_USE_PLATFORM_WIN32

// XR_KHR_win32_convert_performance_counter_time is a preprocessor guard. Do not pass it to API calls.
#ವ್ಯಾಖ್ಯಾನಿಸು XR_KHR_win32_convert_performance_counter_ಸಮಯ 1
#ವ್ಯಾಖ್ಯಾನಿಸು XR_KHR_win32_convert_performance_counter_ಸಮಯ_SPEC_ಆವೃತ್ತಿ 1
#ವ್ಯಾಖ್ಯಾನಿಸು XR_KHR_WIN32_CONVERT_PERFORMANCE_COUNTER_ಸಮಯ_EXTENSION_NAME "XR_KHR_win32_convert_performance_counter_time"
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ Xr_ಫಲಿತಾಂಶ (XRAPI_PTR *PFN_xr_Convert_Win32_Performance_Counter_ಗಮ್ಯ_ಸಮಯ_KHR)(XrInstance instance, ಸ್ಥಿರಾಂಕ LARGE_INTEGER* performanceCounter, Xr_ಸಮಯ* ಸಮಯ);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ Xr_ಫಲಿತಾಂಶ (XRAPI_PTR *PFN_xr_Convert_ಸಮಯ_ಗಮ್ಯ_Win32_Performance_Counter_KHR)(XrInstance instance, Xr_ಸಮಯ ಸಮಯ, LARGE_INTEGER* performanceCounter);

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ XR_NO_PROTOTYPES
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ XR_EXTENSION_PROTOTYPES
XRAPI_ATTR Xr_ಫಲಿತಾಂಶ XRAPI_CALL xr_Convert_Win32_Performance_Counter_ಗಮ್ಯ_ಸಮಯ_KHR(
    XrInstance                                  instance,
    ಸ್ಥಿರಾಂಕ LARGE_INTEGER*                        performanceCounter,
    Xr_ಸಮಯ*                                     ಸಮಯ);

XRAPI_ATTR Xr_ಫಲಿತಾಂಶ XRAPI_CALL xr_Convert_ಸಮಯ_ಗಮ್ಯ_Win32_Performance_Counter_KHR(
    XrInstance                                  instance,
    Xr_ಸಮಯ                                      ಸಮಯ,
    LARGE_INTEGER*                              performanceCounter);
#ಆದರೆ_ಅಂತ್ಯ /* XR_EXTENSION_PROTOTYPES */
#ಆದರೆ_ಅಂತ್ಯ /* !XR_NO_PROTOTYPES */
#ಆದರೆ_ಅಂತ್ಯ /* XR_USE_PLATFORM_WIN32 */

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ XR_USE_TIMESPEC

// XR_KHR_convert_timespec_time is a preprocessor guard. Do not pass it to API calls.
#ವ್ಯಾಖ್ಯಾನಿಸು XR_KHR_convert_timespec_ಸಮಯ 1
#ವ್ಯಾಖ್ಯಾನಿಸು XR_KHR_convert_timespec_ಸಮಯ_SPEC_ಆವೃತ್ತಿ 1
#ವ್ಯಾಖ್ಯಾನಿಸು XR_KHR_CONVERT_TIMESPEC_ಸಮಯ_EXTENSION_NAME "XR_KHR_convert_timespec_time"
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ Xr_ಫಲಿತಾಂಶ (XRAPI_PTR *PFN_xr_Convert_Timespec_ಸಮಯ_ಗಮ್ಯ_ಸಮಯ_KHR)(XrInstance instance, ಸ್ಥಿರಾಂಕ ರಚನೆ timespec* timespec_ಸಮಯ, Xr_ಸಮಯ* ಸಮಯ);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ Xr_ಫಲಿತಾಂಶ (XRAPI_PTR *PFN_xr_Convert_ಸಮಯ_ಗಮ್ಯ_Timespec_ಸಮಯ_KHR)(XrInstance instance, Xr_ಸಮಯ ಸಮಯ, ರಚನೆ timespec* timespec_ಸಮಯ);

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ XR_NO_PROTOTYPES
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ XR_EXTENSION_PROTOTYPES
XRAPI_ATTR Xr_ಫಲಿತಾಂಶ XRAPI_CALL xr_Convert_Timespec_ಸಮಯ_ಗಮ್ಯ_ಸಮಯ_KHR(
    XrInstance                                  instance,
    ಸ್ಥಿರಾಂಕ ರಚನೆ timespec*                      timespec_ಸಮಯ,
    Xr_ಸಮಯ*                                     ಸಮಯ);

XRAPI_ATTR Xr_ಫಲಿತಾಂಶ XRAPI_CALL xr_Convert_ಸಮಯ_ಗಮ್ಯ_Timespec_ಸಮಯ_KHR(
    XrInstance                                  instance,
    Xr_ಸಮಯ                                      ಸಮಯ,
    ರಚನೆ timespec*                            timespec_ಸಮಯ);
#ಆದರೆ_ಅಂತ್ಯ /* XR_EXTENSION_PROTOTYPES */
#ಆದರೆ_ಅಂತ್ಯ /* !XR_NO_PROTOTYPES */
#ಆದರೆ_ಅಂತ್ಯ /* XR_USE_TIMESPEC */

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ XR_USE_PLATFORM_ANDROID

// XR_KHR_loader_init_android is a preprocessor guard. Do not pass it to API calls.
#ವ್ಯಾಖ್ಯಾನಿಸು XR_KHR_loader_init_android 1
#ವ್ಯಾಖ್ಯಾನಿಸು XR_KHR_loader_init_android_SPEC_ಆವೃತ್ತಿ 1
#ವ್ಯಾಖ್ಯಾನಿಸು XR_KHR_LOADER_INIT_ANDROID_EXTENSION_NAME "XR_KHR_loader_init_android"
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ XrLoaderInitInfoAndroidKHR {
    XrStructureType             type;
    ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ* XR_MAY_ALIAS    ಮುಂದಿನ;
    ಶೂನ್ಯ* XR_MAY_ALIAS          applicationVM;
    ಶೂನ್ಯ* XR_MAY_ALIAS          applicationContext;
} XrLoaderInitInfoAndroidKHR;

#ಆದರೆ_ಅಂತ್ಯ /* XR_USE_PLATFORM_ANDROID */

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ XR_USE_GRAPHICS_API_VULKAN

// XR_KHR_vulkan_enable2 is a preprocessor guard. Do not pass it to API calls.
#ವ್ಯಾಖ್ಯಾನಿಸು XR_KHR_vulkan_enable2 1
#ವ್ಯಾಖ್ಯಾನಿಸು XR_KHR_vulkan_enable2_SPEC_ಆವೃತ್ತಿ 4
#ವ್ಯಾಖ್ಯಾನಿಸು XR_KHR_VULKAN_ENABLE2_EXTENSION_NAME "XR_KHR_vulkan_enable2"
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ XrFlags64 XrVulkanInstanceCreateFlagsKHR;

// Flag bits for XrVulkanInstanceCreateFlagsKHR

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ XrFlags64 XrVulkanDeviceCreateFlagsKHR;

// Flag bits for XrVulkanDeviceCreateFlagsKHR

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ XrVulkanInstanceCreateInfoKHR {
    XrStructureType                   type;
    ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ* XR_MAY_ALIAS          ಮುಂದಿನ;
    XrSystemId                        systemId;
    XrVulkanInstanceCreateFlagsKHR    createFlags;
    PFN_vkGetInstanceProcAddr         pfnGetInstanceProcAddr;
    ಸ್ಥಿರಾಂಕ VkInstanceCreateInfo*       vulkanCreateInfo;
    ಸ್ಥಿರಾಂಕ Vk_ಹಂಚಿಕೆ_Callbacks*      vulkanAllocator;
} XrVulkanInstanceCreateInfoKHR;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ XrVulkanDeviceCreateInfoKHR {
    XrStructureType                 type;
    ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ* XR_MAY_ALIAS        ಮುಂದಿನ;
    XrSystemId                      systemId;
    XrVulkanDeviceCreateFlagsKHR    createFlags;
    PFN_vkGetInstanceProcAddr       pfnGetInstanceProcAddr;
    VkPhysicalDevice                vulkanPhysicalDevice;
    ಸ್ಥಿರಾಂಕ VkDeviceCreateInfo*       vulkanCreateInfo;
    ಸ್ಥಿರಾಂಕ Vk_ಹಂಚಿಕೆ_Callbacks*    vulkanAllocator;
} XrVulkanDeviceCreateInfoKHR;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ XrGraphicsBindingVulkanKHR XrGraphicsBindingVulkan2KHR;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ XrVulkanGraphicsDeviceGetInfoKHR {
    XrStructureType             type;
    ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ* XR_MAY_ALIAS    ಮುಂದಿನ;
    XrSystemId                  systemId;
    VkInstance                  vulkanInstance;
} XrVulkanGraphicsDeviceGetInfoKHR;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ XrSwapchainImageVulkanKHR XrSwapchainImageVulkan2KHR;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ XrGraphicsRequirementsVulkanKHR XrGraphicsRequirementsVulkan2KHR;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ Xr_ಫಲಿತಾಂಶ (XRAPI_PTR *PFN_xrCreateVulkanInstanceKHR)(XrInstance instance, ಸ್ಥಿರಾಂಕ XrVulkanInstanceCreateInfoKHR* createInfo, VkInstance* vulkanInstance, Vk_ಫಲಿತಾಂಶ* vulkan_ಫಲಿತಾಂಶ);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ Xr_ಫಲಿತಾಂಶ (XRAPI_PTR *PFN_xrCreateVulkanDeviceKHR)(XrInstance instance, ಸ್ಥಿರಾಂಕ XrVulkanDeviceCreateInfoKHR* createInfo, VkDevice* vulkanDevice, Vk_ಫಲಿತಾಂಶ* vulkan_ಫಲಿತಾಂಶ);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ Xr_ಫಲಿತಾಂಶ (XRAPI_PTR *PFN_xrGetVulkanGraphicsDevice2KHR)(XrInstance instance, ಸ್ಥಿರಾಂಕ XrVulkanGraphicsDeviceGetInfoKHR* getInfo, VkPhysicalDevice* vulkanPhysicalDevice);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ Xr_ಫಲಿತಾಂಶ (XRAPI_PTR *PFN_xrGetVulkanGraphicsRequirements2KHR)(XrInstance instance, XrSystemId systemId, XrGraphicsRequirementsVulkanKHR* graphicsRequirements);

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ XR_NO_PROTOTYPES
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ XR_EXTENSION_PROTOTYPES
XRAPI_ATTR Xr_ಫಲಿತಾಂಶ XRAPI_CALL xrCreateVulkanInstanceKHR(
    XrInstance                                  instance,
    ಸ್ಥಿರಾಂಕ XrVulkanInstanceCreateInfoKHR*        createInfo,
    VkInstance*                                 vulkanInstance,
    Vk_ಫಲಿತಾಂಶ*                                   vulkan_ಫಲಿತಾಂಶ);

XRAPI_ATTR Xr_ಫಲಿತಾಂಶ XRAPI_CALL xrCreateVulkanDeviceKHR(
    XrInstance                                  instance,
    ಸ್ಥಿರಾಂಕ XrVulkanDeviceCreateInfoKHR*          createInfo,
    VkDevice*                                   vulkanDevice,
    Vk_ಫಲಿತಾಂಶ*                                   vulkan_ಫಲಿತಾಂಶ);

XRAPI_ATTR Xr_ಫಲಿತಾಂಶ XRAPI_CALL xrGetVulkanGraphicsDevice2KHR(
    XrInstance                                  instance,
    ಸ್ಥಿರಾಂಕ XrVulkanGraphicsDeviceGetInfoKHR*     getInfo,
    VkPhysicalDevice*                           vulkanPhysicalDevice);

XRAPI_ATTR Xr_ಫಲಿತಾಂಶ XRAPI_CALL xrGetVulkanGraphicsRequirements2KHR(
    XrInstance                                  instance,
    XrSystemId                                  systemId,
    XrGraphicsRequirementsVulkanKHR*            graphicsRequirements);
#ಆದರೆ_ಅಂತ್ಯ /* XR_EXTENSION_PROTOTYPES */
#ಆದರೆ_ಅಂತ್ಯ /* !XR_NO_PROTOTYPES */
#ಆದರೆ_ಅಂತ್ಯ /* XR_USE_GRAPHICS_API_VULKAN */

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ XR_USE_PLATFORM_EGL

// XR_MNDX_egl_enable is a preprocessor guard. Do not pass it to API calls.
#ವ್ಯಾಖ್ಯಾನಿಸು XR_MNDX_egl_enable 1
#ವ್ಯಾಖ್ಯಾನಿಸು XR_MNDX_egl_enable_SPEC_ಆವೃತ್ತಿ   2
#ವ್ಯಾಖ್ಯಾನಿಸು XR_MNDX_EGL_ENABLE_EXTENSION_NAME "XR_MNDX_egl_enable"
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ PFN_xrVoidFunction (*PFN_xr_Egl_Get_Proc_ವಿಳಾಸ_MNDX)(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *name);
// XrGraphicsBindingEGLMNDX extends XrSessionCreateInfo
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ XrGraphicsBindingEGLMNDX {
    XrStructureType                type;
    ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ* XR_MAY_ALIAS       ಮುಂದಿನ;
    PFN_xr_Egl_Get_Proc_ವಿಳಾಸ_MNDX    get_Proc_ವಿಳಾಸ;
    EGLDisplay                     display;
    EGLConfig                      config;
    EGLContext                     context;
} XrGraphicsBindingEGLMNDX;

#ಆದರೆ_ಅಂತ್ಯ /* XR_USE_PLATFORM_EGL */

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ XR_USE_PLATFORM_WIN32

// XR_MSFT_perception_anchor_interop is a preprocessor guard. Do not pass it to API calls.
#ವ್ಯಾಖ್ಯಾನಿಸು XR_MSFT_perception_anchor_interop 1
#ವ್ಯಾಖ್ಯಾನಿಸು XR_MSFT_perception_anchor_interop_SPEC_ಆವೃತ್ತಿ 1
#ವ್ಯಾಖ್ಯಾನಿಸು XR_MSFT_PERCEPTION_ANCHOR_INTEROP_EXTENSION_NAME "XR_MSFT_perception_anchor_interop"
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ Xr_ಫಲಿತಾಂಶ (XRAPI_PTR *PFN_xrCreateSpatialAnchorFromPerceptionAnchorMSFT)(XrSession session, IUnknown* perceptionAnchor, XrSpatialAnchorMSFT* anchor);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ Xr_ಫಲಿತಾಂಶ (XRAPI_PTR *PFN_xrTryGetPerceptionAnchorFromSpatialAnchorMSFT)(XrSession session, XrSpatialAnchorMSFT anchor, IUnknown** perceptionAnchor);

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ XR_NO_PROTOTYPES
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ XR_EXTENSION_PROTOTYPES
XRAPI_ATTR Xr_ಫಲಿತಾಂಶ XRAPI_CALL xrCreateSpatialAnchorFromPerceptionAnchorMSFT(
    XrSession                                   session,
    IUnknown*                                   perceptionAnchor,
    XrSpatialAnchorMSFT*                        anchor);

XRAPI_ATTR Xr_ಫಲಿತಾಂಶ XRAPI_CALL xrTryGetPerceptionAnchorFromSpatialAnchorMSFT(
    XrSession                                   session,
    XrSpatialAnchorMSFT                         anchor,
    IUnknown**                                  perceptionAnchor);
#ಆದರೆ_ಅಂತ್ಯ /* XR_EXTENSION_PROTOTYPES */
#ಆದರೆ_ಅಂತ್ಯ /* !XR_NO_PROTOTYPES */
#ಆದರೆ_ಅಂತ್ಯ /* XR_USE_PLATFORM_WIN32 */

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ XR_USE_PLATFORM_WIN32

// XR_MSFT_holographic_window_attachment is a preprocessor guard. Do not pass it to API calls.
#ವ್ಯಾಖ್ಯಾನಿಸು XR_MSFT_holographic_ಕಿಟಕಿ_attachment 1
#ವ್ಯಾಖ್ಯಾನಿಸು XR_MSFT_holographic_ಕಿಟಕಿ_attachment_SPEC_ಆವೃತ್ತಿ 1
#ವ್ಯಾಖ್ಯಾನಿಸು XR_MSFT_HOLOGRAPHIC_ಕಿಟಕಿ_ATTACHMENT_EXTENSION_NAME "XR_MSFT_holographic_window_attachment"
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ XR_USE_PLATFORM_WIN32
// XrHolographicWindowAttachmentMSFT extends XrSessionCreateInfo
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ Xr_Holographic_ಕಿಟಕಿ_Attachment_MSFT {
    XrStructureType             type;
    ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ* XR_MAY_ALIAS    ಮುಂದಿನ;
    IUnknown*                   holographicSpace;
    IUnknown*                   core_ಕಿಟಕಿ;
} Xr_Holographic_ಕಿಟಕಿ_Attachment_MSFT;
#ಆದರೆ_ಅಂತ್ಯ // XR_USE_PLATFORM_WIN32

#ಆದರೆ_ಅಂತ್ಯ /* XR_USE_PLATFORM_WIN32 */

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ XR_USE_PLATFORM_ANDROID

// XR_FB_android_surface_swapchain_create is a preprocessor guard. Do not pass it to API calls.
#ವ್ಯಾಖ್ಯಾನಿಸು XR_FB_android_surface_swapchain_create 1
#ವ್ಯಾಖ್ಯಾನಿಸು XR_FB_android_surface_swapchain_create_SPEC_ಆವೃತ್ತಿ 1
#ವ್ಯಾಖ್ಯಾನಿಸು XR_FB_ANDROID_SURFACE_SWAPCHAIN_CREATE_EXTENSION_NAME "XR_FB_android_surface_swapchain_create"
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ XrFlags64 XrAndroidSurfaceSwapchainFlagsFB;

// Flag bits for XrAndroidSurfaceSwapchainFlagsFB
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ XrAndroidSurfaceSwapchainFlagsFB XR_ANDROID_SURFACE_SWAPCHAIN_SYNCHRONOUS_ಬಿಟ್_FB = 0x00000001;
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ XrAndroidSurfaceSwapchainFlagsFB XR_ANDROID_SURFACE_SWAPCHAIN_USE_TIMESTAMPS_ಬಿಟ್_FB = 0x00000002;

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ XR_USE_PLATFORM_ANDROID
// XrAndroidSurfaceSwapchainCreateInfoFB extends XrSwapchainCreateInfo
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ XrAndroidSurfaceSwapchainCreateInfoFB {
    XrStructureType                     type;
    ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ* XR_MAY_ALIAS            ಮುಂದಿನ;
    XrAndroidSurfaceSwapchainFlagsFB    createFlags;
} XrAndroidSurfaceSwapchainCreateInfoFB;
#ಆದರೆ_ಅಂತ್ಯ // XR_USE_PLATFORM_ANDROID

#ಆದರೆ_ಅಂತ್ಯ /* XR_USE_PLATFORM_ANDROID */

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ XR_USE_PLATFORM_ML

// XR_ML_compat is a preprocessor guard. Do not pass it to API calls.
#ವ್ಯಾಖ್ಯಾನಿಸು XR_ML_compat 1
#ವ್ಯಾಖ್ಯಾನಿಸು XR_ML_compat_SPEC_ಆವೃತ್ತಿ         1
#ವ್ಯಾಖ್ಯಾನಿಸು XR_ML_COMPAT_EXTENSION_NAME       "XR_ML_compat"
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ XrCoordinateSpaceCreateInfoML {
    XrStructureType             type;
    ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ* XR_MAY_ALIAS    ಮುಂದಿನ;
    MLCoordinate_ಚೌಕಟ್ಟು_UID        cfuid;
    XrPosef                     pose_ಒಳ_Coordinate_Space;
} XrCoordinateSpaceCreateInfoML;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ Xr_ಫಲಿತಾಂಶ (XRAPI_PTR *PFN_xr_Create_Space_From_Coordinate_ಚೌಕಟ್ಟು_UIDML)(XrSession session, ಸ್ಥಿರಾಂಕ XrCoordinateSpaceCreateInfoML *createInfo, XrSpace* space);

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ XR_NO_PROTOTYPES
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ XR_EXTENSION_PROTOTYPES
XRAPI_ATTR Xr_ಫಲಿತಾಂಶ XRAPI_CALL xr_Create_Space_From_Coordinate_ಚೌಕಟ್ಟು_UIDML(
    XrSession                                   session,
    ಸ್ಥಿರಾಂಕ XrCoordinateSpaceCreateInfoML *       createInfo,
    XrSpace*                                    space);
#ಆದರೆ_ಅಂತ್ಯ /* XR_EXTENSION_PROTOTYPES */
#ಆದರೆ_ಅಂತ್ಯ /* !XR_NO_PROTOTYPES */
#ಆದರೆ_ಅಂತ್ಯ /* XR_USE_PLATFORM_ML */

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ XR_USE_PLATFORM_WIN32

// XR_OCULUS_audio_device_guid is a preprocessor guard. Do not pass it to API calls.
#ವ್ಯಾಖ್ಯಾನಿಸು XR_OCULUS_audio_device_guid 1
#ವ್ಯಾಖ್ಯಾನಿಸು XR_OCULUS_audio_device_guid_SPEC_ಆವೃತ್ತಿ 1
#ವ್ಯಾಖ್ಯಾನಿಸು XR_OCULUS_AUDIO_DEVICE_GUID_EXTENSION_NAME "XR_OCULUS_audio_device_guid"
#ವ್ಯಾಖ್ಯಾನಿಸು XR_MAX_AUDIO_DEVICE_STR_ಗಾತ್ರ_OCULUS 128
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ Xr_ಫಲಿತಾಂಶ (XRAPI_PTR *PFN_xrGetAudioOutputDeviceGuidOculus)(XrInstance instance, wchar_t ಬಫರ್_2[XR_MAX_AUDIO_DEVICE_STR_ಗಾತ್ರ_OCULUS]);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ Xr_ಫಲಿತಾಂಶ (XRAPI_PTR *PFN_xr_Get_Audio_ಒಳಹರಿವು_Device_Guid_Oculus)(XrInstance instance, wchar_t ಬಫರ್_2[XR_MAX_AUDIO_DEVICE_STR_ಗಾತ್ರ_OCULUS]);

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ XR_NO_PROTOTYPES
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ XR_EXTENSION_PROTOTYPES
XRAPI_ATTR Xr_ಫಲಿತಾಂಶ XRAPI_CALL xrGetAudioOutputDeviceGuidOculus(
    XrInstance                                  instance,
    wchar_t                                     ಬಫರ್_2[XR_MAX_AUDIO_DEVICE_STR_ಗಾತ್ರ_OCULUS]);

XRAPI_ATTR Xr_ಫಲಿತಾಂಶ XRAPI_CALL xr_Get_Audio_ಒಳಹರಿವು_Device_Guid_Oculus(
    XrInstance                                  instance,
    wchar_t                                     ಬಫರ್_2[XR_MAX_AUDIO_DEVICE_STR_ಗಾತ್ರ_OCULUS]);
#ಆದರೆ_ಅಂತ್ಯ /* XR_EXTENSION_PROTOTYPES */
#ಆದರೆ_ಅಂತ್ಯ /* !XR_NO_PROTOTYPES */
#ಆದರೆ_ಅಂತ್ಯ /* XR_USE_PLATFORM_WIN32 */

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ XR_USE_GRAPHICS_API_VULKAN

// XR_FB_foveation_vulkan is a preprocessor guard. Do not pass it to API calls.
#ವ್ಯಾಖ್ಯಾನಿಸು XR_FB_foveation_vulkan 1
#ವ್ಯಾಖ್ಯಾನಿಸು XR_FB_foveation_vulkan_SPEC_ಆವೃತ್ತಿ 1
#ವ್ಯಾಖ್ಯಾನಿಸು XR_FB_FOVEATION_VULKAN_EXTENSION_NAME "XR_FB_foveation_vulkan"
// XrSwapchainImageFoveationVulkanFB extends XrSwapchainImageVulkanKHR
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ XrSwapchainImageFoveationVulkanFB {
    XrStructureType       type;
    ಶೂನ್ಯ* XR_MAY_ALIAS    ಮುಂದಿನ;
    VkImage               image;
    uint32_t              ಅಗಲ;
    uint32_t              ಎತ್ತರ;
} XrSwapchainImageFoveationVulkanFB;

#ಆದರೆ_ಅಂತ್ಯ /* XR_USE_GRAPHICS_API_VULKAN */

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ XR_USE_PLATFORM_ANDROID

// XR_FB_swapchain_update_state_android_surface is a preprocessor guard. Do not pass it to API calls.
#ವ್ಯಾಖ್ಯಾನಿಸು XR_FB_swapchain_update_state_android_surface 1
#ವ್ಯಾಖ್ಯಾನಿಸು XR_FB_swapchain_update_state_android_surface_SPEC_ಆವೃತ್ತಿ 1
#ವ್ಯಾಖ್ಯಾನಿಸು XR_FB_SWAPCHAIN_UPDATE_STATE_ANDROID_SURFACE_EXTENSION_NAME "XR_FB_swapchain_update_state_android_surface"
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ XR_USE_PLATFORM_ANDROID
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ XrSwapchainStateAndroidSurfaceDimensionsFB {
    XrStructureType       type;
    ಶೂನ್ಯ* XR_MAY_ALIAS    ಮುಂದಿನ;
    uint32_t              ಅಗಲ;
    uint32_t              ಎತ್ತರ;
} XrSwapchainStateAndroidSurfaceDimensionsFB;
#ಆದರೆ_ಅಂತ್ಯ // XR_USE_PLATFORM_ANDROID

#ಆದರೆ_ಅಂತ್ಯ /* XR_USE_PLATFORM_ANDROID */

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ XR_USE_GRAPHICS_API_OPENGL_ES

// XR_FB_swapchain_update_state_opengl_es is a preprocessor guard. Do not pass it to API calls.
#ವ್ಯಾಖ್ಯಾನಿಸು XR_FB_swapchain_update_state_opengl_es 1
#ವ್ಯಾಖ್ಯಾನಿಸು XR_FB_swapchain_update_state_opengl_es_SPEC_ಆವೃತ್ತಿ 1
#ವ್ಯಾಖ್ಯಾನಿಸು XR_FB_SWAPCHAIN_UPDATE_STATE_OPENGL_ES_EXTENSION_NAME "XR_FB_swapchain_update_state_opengl_es"
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ XR_USE_GRAPHICS_API_OPENGL_ES
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ XrSwapchainStateSamplerOpenGLESFB {
    XrStructureType       type;
    ಶೂನ್ಯ* XR_MAY_ALIAS    ಮುಂದಿನ;
    EGLenum               minFilter;
    EGLenum               magFilter;
    EGLenum               wrap_ಬಹುಲಕ_S;
    EGLenum               wrap_ಬಹುಲಕ_T;
    EGLenum               swizzleRed;
    EGLenum               swizzleGreen;
    EGLenum               swizzleBlue;
    EGLenum               swizzleAlpha;
    ದಶಮಾಂಶ                 maxAnisotropy;
    XrColor4f             borderColor;
} XrSwapchainStateSamplerOpenGLESFB;
#ಆದರೆ_ಅಂತ್ಯ // XR_USE_GRAPHICS_API_OPENGL_ES

#ಆದರೆ_ಅಂತ್ಯ /* XR_USE_GRAPHICS_API_OPENGL_ES */

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ XR_USE_GRAPHICS_API_VULKAN

// XR_FB_swapchain_update_state_vulkan is a preprocessor guard. Do not pass it to API calls.
#ವ್ಯಾಖ್ಯಾನಿಸು XR_FB_swapchain_update_state_vulkan 1
#ವ್ಯಾಖ್ಯಾನಿಸು XR_FB_swapchain_update_state_vulkan_SPEC_ಆವೃತ್ತಿ 1
#ವ್ಯಾಖ್ಯಾನಿಸು XR_FB_SWAPCHAIN_UPDATE_STATE_VULKAN_EXTENSION_NAME "XR_FB_swapchain_update_state_vulkan"
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ XR_USE_GRAPHICS_API_VULKAN
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ XrSwapchainStateSamplerVulkanFB {
    XrStructureType         type;
    ಶೂನ್ಯ* XR_MAY_ALIAS      ಮುಂದಿನ;
    VkFilter                minFilter;
    VkFilter                magFilter;
    Vk_Sampler_Mipmap_ಬಹುಲಕ     mipmap_ಬಹುಲಕ;
    Vk_Sampler_ವಿಳಾಸ_ಬಹುಲಕ    wrap_ಬಹುಲಕ_S;
    Vk_Sampler_ವಿಳಾಸ_ಬಹುಲಕ    wrap_ಬಹುಲಕ_T;
    VkComponentSwizzle      swizzleRed;
    VkComponentSwizzle      swizzleGreen;
    VkComponentSwizzle      swizzleBlue;
    VkComponentSwizzle      swizzleAlpha;
    ದಶಮಾಂಶ                   maxAnisotropy;
    XrColor4f               borderColor;
} XrSwapchainStateSamplerVulkanFB;
#ಆದರೆ_ಅಂತ್ಯ // XR_USE_GRAPHICS_API_VULKAN

#ಆದರೆ_ಅಂತ್ಯ /* XR_USE_GRAPHICS_API_VULKAN */

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ XR_USE_GRAPHICS_API_VULKAN

// XR_META_vulkan_swapchain_create_info is a preprocessor guard. Do not pass it to API calls.
#ವ್ಯಾಖ್ಯಾನಿಸು XR_META_vulkan_swapchain_create_info 1
#ವ್ಯಾಖ್ಯಾನಿಸು XR_META_vulkan_swapchain_create_info_SPEC_ಆವೃತ್ತಿ 1
#ವ್ಯಾಖ್ಯಾನಿಸು XR_META_VULKAN_SWAPCHAIN_CREATE_INFO_EXTENSION_NAME "XR_META_vulkan_swapchain_create_info"
// XrVulkanSwapchainCreateInfoMETA extends XrSwapchainCreateInfo
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ XrVulkanSwapchainCreateInfoMETA {
    XrStructureType             type;
    ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ* XR_MAY_ALIAS    ಮುಂದಿನ;
    VkImageCreateFlags          additionalCreateFlags;
    VkImageUsageFlags           additionalUsageFlags;
} XrVulkanSwapchainCreateInfoMETA;

#ಆದರೆ_ಅಂತ್ಯ /* XR_USE_GRAPHICS_API_VULKAN */

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ XR_USE_PLATFORM_ANDROID

// XR_ANDROID_anchor_sharing_export is a preprocessor guard. Do not pass it to API calls.
#ವ್ಯಾಖ್ಯಾನಿಸು XR_ANDROID_anchor_sharing_export 1
#ವ್ಯಾಖ್ಯಾನಿಸು XR_ANDROID_anchor_sharing_export_SPEC_ಆವೃತ್ತಿ 1
#ವ್ಯಾಖ್ಯಾನಿಸು XR_ANDROID_ANCHOR_SHARING_EXPORT_EXTENSION_NAME "XR_ANDROID_anchor_sharing_export"
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ XrAnchorSharingInfoANDROID {
    XrStructureType             type;
    ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ* XR_MAY_ALIAS    ಮುಂದಿನ;
    XrSpace                     anchor;
} XrAnchorSharingInfoANDROID;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ XrAnchorSharingTokenANDROID {
    XrStructureType       type;
    ಶೂನ್ಯ* XR_MAY_ALIAS    ಮುಂದಿನ;
    ರಚನೆ AIBinder*      token;
} XrAnchorSharingTokenANDROID;

// XrSystemAnchorSharingExportPropertiesANDROID extends XrSystemProperties
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ XrSystemAnchorSharingExportPropertiesANDROID {
    XrStructureType       type;
    ಶೂನ್ಯ* XR_MAY_ALIAS    ಮುಂದಿನ;
    XrBool32              supportsAnchorSharingExport;
} XrSystemAnchorSharingExportPropertiesANDROID;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ Xr_ಫಲಿತಾಂಶ (XRAPI_PTR *PFN_xrShareAnchorANDROID)(XrSession session, ಸ್ಥಿರಾಂಕ XrAnchorSharingInfoANDROID* sharingInfo, XrAnchorSharingTokenANDROID* anchorToken);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ Xr_ಫಲಿತಾಂಶ (XRAPI_PTR *PFN_xrUnshareAnchorANDROID)(XrSession session, XrSpace anchor);

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ XR_NO_PROTOTYPES
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ XR_EXTENSION_PROTOTYPES
XRAPI_ATTR Xr_ಫಲಿತಾಂಶ XRAPI_CALL xrShareAnchorANDROID(
    XrSession                                   session,
    ಸ್ಥಿರಾಂಕ XrAnchorSharingInfoANDROID*           sharingInfo,
    XrAnchorSharingTokenANDROID*                anchorToken);

XRAPI_ATTR Xr_ಫಲಿತಾಂಶ XRAPI_CALL xrUnshareAnchorANDROID(
    XrSession                                   session,
    XrSpace                                     anchor);
#ಆದರೆ_ಅಂತ್ಯ /* XR_EXTENSION_PROTOTYPES */
#ಆದರೆ_ಅಂತ್ಯ /* !XR_NO_PROTOTYPES */
#ಆದರೆ_ಅಂತ್ಯ /* XR_USE_PLATFORM_ANDROID */

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __cplusplus
}
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ_ಅಂತ್ಯ
