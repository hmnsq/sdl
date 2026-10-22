#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ OPENXR_PLATFORM_H_
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ OPENXR_PLATFORM_H_ 1

/*
** Copyright 2017-2026 The Khronos Group Inc.
**
** SPDX-License-Identifier: Apache-2.0 OR MIT
*/

/*
** This header is generated from the Khronos OpenXR XML API Registry.
**
*/

#ਅਨ੍ਤਰ੍ਭਾਵ "openxr.h"

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __cplusplus
ਬਾਹਰੀ "C" {
#ਜੇ_ਅੰਤ


#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ XR_USE_PLATFORM_ANDROID

// XR_KHR_android_thread_settings is a preprocessor guard. Do not pass it to API calls.
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XR_KHR_android_thread_settings 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XR_KHR_android_thread_settings_SPEC_ਸੰਸਕਰਣ 6
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XR_KHR_ANDROID_THREAD_SETTINGS_EXTENSION_NAME "XR_KHR_android_thread_settings"

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ XrAndroidThreadTypeKHR {
    XR_ANDROID_THREAD_TYPE_APPLICATION_MAIN_KHR = 1,
    XR_ANDROID_THREAD_TYPE_APPLICATION_ਕਾਮਾ_KHR = 2,
    XR_ANDROID_THREAD_TYPE_RENDERER_MAIN_KHR = 3,
    XR_ANDROID_THREAD_TYPE_RENDERER_ਕਾਮਾ_KHR = 4,
    XR_ANDROID_THREAD_TYPE_MAX_ENUM_KHR = 0x7FFFFFFF
} XrAndroidThreadTypeKHR;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ Xr_ਨਤੀਜਾ (XRAPI_PTR *PFN_xr_ਸੈੱਟ_Android_Application_Thread_KHR)(XrSession session, XrAndroidThreadTypeKHR threadType, uint32_t threadId);

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ XR_NO_PROTOTYPES
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ XR_EXTENSION_PROTOTYPES
XRAPI_ATTR Xr_ਨਤੀਜਾ XRAPI_CALL xr_ਸੈੱਟ_Android_Application_Thread_KHR(
    XrSession                                   session,
    XrAndroidThreadTypeKHR                      threadType,
    uint32_t                                    threadId);
#ਜੇ_ਅੰਤ /* XR_EXTENSION_PROTOTYPES */
#ਜੇ_ਅੰਤ /* !XR_NO_PROTOTYPES */
#ਜੇ_ਅੰਤ /* XR_USE_PLATFORM_ANDROID */

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ XR_USE_PLATFORM_ANDROID

// XR_KHR_android_surface_swapchain is a preprocessor guard. Do not pass it to API calls.
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XR_KHR_android_surface_swapchain 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XR_KHR_android_surface_swapchain_SPEC_ਸੰਸਕਰਣ 4
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XR_KHR_ANDROID_SURFACE_SWAPCHAIN_EXTENSION_NAME "XR_KHR_android_surface_swapchain"
ਕਿਸਮਪਰਿਭਾਸ਼ਾ Xr_ਨਤੀਜਾ (XRAPI_PTR *PFN_xrCreateSwapchainAndroidSurfaceKHR)(XrSession session, ਅਚਲ XrSwapchainCreateInfo* info, XrSwapchain* swapchain, jobject* surface);

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ XR_NO_PROTOTYPES
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ XR_EXTENSION_PROTOTYPES
XRAPI_ATTR Xr_ਨਤੀਜਾ XRAPI_CALL xrCreateSwapchainAndroidSurfaceKHR(
    XrSession                                   session,
    ਅਚਲ XrSwapchainCreateInfo*                info,
    XrSwapchain*                                swapchain,
    jobject*                                    surface);
#ਜੇ_ਅੰਤ /* XR_EXTENSION_PROTOTYPES */
#ਜੇ_ਅੰਤ /* !XR_NO_PROTOTYPES */
#ਜੇ_ਅੰਤ /* XR_USE_PLATFORM_ANDROID */

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ XR_USE_PLATFORM_ANDROID

// XR_KHR_android_create_instance is a preprocessor guard. Do not pass it to API calls.
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XR_KHR_android_create_instance 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XR_KHR_android_create_instance_SPEC_ਸੰਸਕਰਣ 3
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XR_KHR_ANDROID_CREATE_INSTANCE_EXTENSION_NAME "XR_KHR_android_create_instance"
// XrInstanceCreateInfoAndroidKHR extends XrInstanceCreateInfo
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ XrInstanceCreateInfoAndroidKHR {
    XrStructureType             type;
    ਅਚਲ ਖਾਲੀ* XR_MAY_ALIAS    ਅਗਲਾ;
    ਖਾਲੀ* XR_MAY_ALIAS          applicationVM;
    ਖਾਲੀ* XR_MAY_ALIAS          applicationActivity;
} XrInstanceCreateInfoAndroidKHR;

#ਜੇ_ਅੰਤ /* XR_USE_PLATFORM_ANDROID */

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ XR_USE_GRAPHICS_API_VULKAN

// XR_KHR_vulkan_swapchain_format_list is a preprocessor guard. Do not pass it to API calls.
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XR_KHR_vulkan_swapchain_format_list 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XR_KHR_vulkan_swapchain_format_list_SPEC_ਸੰਸਕਰਣ 5
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XR_KHR_VULKAN_SWAPCHAIN_FORMAT_LIST_EXTENSION_NAME "XR_KHR_vulkan_swapchain_format_list"
// XrVulkanSwapchainFormatListCreateInfoKHR extends XrSwapchainCreateInfo
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ XrVulkanSwapchainFormatListCreateInfoKHR {
    XrStructureType             type;
    ਅਚਲ ਖਾਲੀ* XR_MAY_ALIAS    ਅਗਲਾ;
    uint32_t                    view_Format_ਗਿਣਤੀ;
    ਅਚਲ VkFormat*             viewFormats;
} XrVulkanSwapchainFormatListCreateInfoKHR;

#ਜੇ_ਅੰਤ /* XR_USE_GRAPHICS_API_VULKAN */

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ XR_USE_GRAPHICS_API_OPENGL

// XR_KHR_opengl_enable is a preprocessor guard. Do not pass it to API calls.
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XR_KHR_opengl_enable 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XR_KHR_opengl_enable_SPEC_ਸੰਸਕਰਣ 12
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XR_KHR_OPENGL_ENABLE_EXTENSION_NAME "XR_KHR_opengl_enable"
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ XR_USE_PLATFORM_WIN32
// XrGraphicsBindingOpenGLWin32KHR extends XrSessionCreateInfo
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ XrGraphicsBindingOpenGLWin32KHR {
    XrStructureType             type;
    ਅਚਲ ਖਾਲੀ* XR_MAY_ALIAS    ਅਗਲਾ;
    HDC                         hDC;
    HGLRC                       hGLRC;
} XrGraphicsBindingOpenGLWin32KHR;
#ਜੇ_ਅੰਤ // XR_USE_PLATFORM_WIN32

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ XR_USE_PLATFORM_XLIB
// XrGraphicsBindingOpenGLXlibKHR extends XrSessionCreateInfo
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ XrGraphicsBindingOpenGLXlibKHR {
    XrStructureType             type;
    ਅਚਲ ਖਾਲੀ* XR_MAY_ALIAS    ਅਗਲਾ;
    Display*                    xDisplay;
    uint32_t                    visualid;
    GLXFBConfig                 glxFBConfig;
    GLXDrawable                 glxDrawable;
    GLXContext                  glxContext;
} XrGraphicsBindingOpenGLXlibKHR;
#ਜੇ_ਅੰਤ // XR_USE_PLATFORM_XLIB

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ XR_USE_PLATFORM_XCB
// XrGraphicsBindingOpenGLXcbKHR extends XrSessionCreateInfo
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ XrGraphicsBindingOpenGLXcbKHR {
    XrStructureType             type;
    ਅਚਲ ਖਾਲੀ* XR_MAY_ALIAS    ਅਗਲਾ;
    xcb_connection_t*           connection;
    uint32_t                    screen_ਸੰਖਿਆ;
    xcb_glx_fbconfig_t          fbconfigid;
    xcb_visualid_t              visualid;
    xcb_glx_drawable_t          glxDrawable;
    xcb_glx_context_t           glxContext;
} XrGraphicsBindingOpenGLXcbKHR;
#ਜੇ_ਅੰਤ // XR_USE_PLATFORM_XCB

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ XR_USE_PLATFORM_WAYLAND
// XrGraphicsBindingOpenGLWaylandKHR extends XrSessionCreateInfo
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ XrGraphicsBindingOpenGLWaylandKHR {
    XrStructureType             type;
    ਅਚਲ ਖਾਲੀ* XR_MAY_ALIAS    ਅਗਲਾ;
    ਬਣਤਰ wl_display*          display;
} XrGraphicsBindingOpenGLWaylandKHR;
#ਜੇ_ਅੰਤ // XR_USE_PLATFORM_WAYLAND

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ XrSwapchainImageOpenGLKHR {
    XrStructureType       type;
    ਖਾਲੀ* XR_MAY_ALIAS    ਅਗਲਾ;
    uint32_t              image;
} XrSwapchainImageOpenGLKHR;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ XrGraphicsRequirementsOpenGLKHR {
    XrStructureType       type;
    ਖਾਲੀ* XR_MAY_ALIAS    ਅਗਲਾ;
    Xr_ਸੰਸਕਰਣ             min_Api_ਸੰਸਕਰਣ_Supported;
    Xr_ਸੰਸਕਰਣ             max_Api_ਸੰਸਕਰਣ_Supported;
} XrGraphicsRequirementsOpenGLKHR;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ Xr_ਨਤੀਜਾ (XRAPI_PTR *PFN_xrGetOpenGLGraphicsRequirementsKHR)(XrInstance instance, XrSystemId systemId, XrGraphicsRequirementsOpenGLKHR* graphicsRequirements);

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ XR_NO_PROTOTYPES
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ XR_EXTENSION_PROTOTYPES
XRAPI_ATTR Xr_ਨਤੀਜਾ XRAPI_CALL xrGetOpenGLGraphicsRequirementsKHR(
    XrInstance                                  instance,
    XrSystemId                                  systemId,
    XrGraphicsRequirementsOpenGLKHR*            graphicsRequirements);
#ਜੇ_ਅੰਤ /* XR_EXTENSION_PROTOTYPES */
#ਜੇ_ਅੰਤ /* !XR_NO_PROTOTYPES */
#ਜੇ_ਅੰਤ /* XR_USE_GRAPHICS_API_OPENGL */

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ XR_USE_GRAPHICS_API_OPENGL_ES

// XR_KHR_opengl_es_enable is a preprocessor guard. Do not pass it to API calls.
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XR_KHR_opengl_es_enable 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XR_KHR_opengl_es_enable_SPEC_ਸੰਸਕਰਣ 10
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XR_KHR_OPENGL_ES_ENABLE_EXTENSION_NAME "XR_KHR_opengl_es_enable"
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ XR_USE_PLATFORM_ANDROID
// XrGraphicsBindingOpenGLESAndroidKHR extends XrSessionCreateInfo
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ XrGraphicsBindingOpenGLESAndroidKHR {
    XrStructureType             type;
    ਅਚਲ ਖਾਲੀ* XR_MAY_ALIAS    ਅਗਲਾ;
    EGLDisplay                  display;
    EGLConfig                   config;
    EGLContext                  context;
} XrGraphicsBindingOpenGLESAndroidKHR;
#ਜੇ_ਅੰਤ // XR_USE_PLATFORM_ANDROID

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ XrSwapchainImageOpenGLESKHR {
    XrStructureType       type;
    ਖਾਲੀ* XR_MAY_ALIAS    ਅਗਲਾ;
    uint32_t              image;
} XrSwapchainImageOpenGLESKHR;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ XrGraphicsRequirementsOpenGLESKHR {
    XrStructureType       type;
    ਖਾਲੀ* XR_MAY_ALIAS    ਅਗਲਾ;
    Xr_ਸੰਸਕਰਣ             min_Api_ਸੰਸਕਰਣ_Supported;
    Xr_ਸੰਸਕਰਣ             max_Api_ਸੰਸਕਰਣ_Supported;
} XrGraphicsRequirementsOpenGLESKHR;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ Xr_ਨਤੀਜਾ (XRAPI_PTR *PFN_xrGetOpenGLESGraphicsRequirementsKHR)(XrInstance instance, XrSystemId systemId, XrGraphicsRequirementsOpenGLESKHR* graphicsRequirements);

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ XR_NO_PROTOTYPES
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ XR_EXTENSION_PROTOTYPES
XRAPI_ATTR Xr_ਨਤੀਜਾ XRAPI_CALL xrGetOpenGLESGraphicsRequirementsKHR(
    XrInstance                                  instance,
    XrSystemId                                  systemId,
    XrGraphicsRequirementsOpenGLESKHR*          graphicsRequirements);
#ਜੇ_ਅੰਤ /* XR_EXTENSION_PROTOTYPES */
#ਜੇ_ਅੰਤ /* !XR_NO_PROTOTYPES */
#ਜੇ_ਅੰਤ /* XR_USE_GRAPHICS_API_OPENGL_ES */

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ XR_USE_GRAPHICS_API_VULKAN

// XR_KHR_vulkan_enable is a preprocessor guard. Do not pass it to API calls.
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XR_KHR_vulkan_enable 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XR_KHR_vulkan_enable_SPEC_ਸੰਸਕਰਣ 10
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XR_KHR_VULKAN_ENABLE_EXTENSION_NAME "XR_KHR_vulkan_enable"
// XrGraphicsBindingVulkanKHR extends XrSessionCreateInfo
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ XrGraphicsBindingVulkanKHR {
    XrStructureType             type;
    ਅਚਲ ਖਾਲੀ* XR_MAY_ALIAS    ਅਗਲਾ;
    VkInstance                  instance;
    VkPhysicalDevice            physicalDevice;
    VkDevice                    device;
    uint32_t                    ਕਤਾਰ_Family_ਸੂਚਕਾਂਕ;
    uint32_t                    ਕਤਾਰ_ਸੂਚਕਾਂਕ;
} XrGraphicsBindingVulkanKHR;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ XrSwapchainImageVulkanKHR {
    XrStructureType       type;
    ਖਾਲੀ* XR_MAY_ALIAS    ਅਗਲਾ;
    VkImage               image;
} XrSwapchainImageVulkanKHR;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ XrGraphicsRequirementsVulkanKHR {
    XrStructureType       type;
    ਖਾਲੀ* XR_MAY_ALIAS    ਅਗਲਾ;
    Xr_ਸੰਸਕਰਣ             min_Api_ਸੰਸਕਰਣ_Supported;
    Xr_ਸੰਸਕਰਣ             max_Api_ਸੰਸਕਰਣ_Supported;
} XrGraphicsRequirementsVulkanKHR;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ Xr_ਨਤੀਜਾ (XRAPI_PTR *PFN_xrGetVulkanInstanceExtensionsKHR)(XrInstance instance, XrSystemId systemId, uint32_t ਬਫਰ_ਸਮਰੱਥਾ_ਨਿਵੇਸ਼, uint32_t* ਬਫਰ_ਗਿਣਤੀ_Output, ਅੱਖਰ* ਬਫਰ_2);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ Xr_ਨਤੀਜਾ (XRAPI_PTR *PFN_xrGetVulkanDeviceExtensionsKHR)(XrInstance instance, XrSystemId systemId, uint32_t ਬਫਰ_ਸਮਰੱਥਾ_ਨਿਵੇਸ਼, uint32_t* ਬਫਰ_ਗਿਣਤੀ_Output, ਅੱਖਰ* ਬਫਰ_2);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ Xr_ਨਤੀਜਾ (XRAPI_PTR *PFN_xrGetVulkanGraphicsDeviceKHR)(XrInstance instance, XrSystemId systemId, VkInstance vkInstance, VkPhysicalDevice* vkPhysicalDevice);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ Xr_ਨਤੀਜਾ (XRAPI_PTR *PFN_xrGetVulkanGraphicsRequirementsKHR)(XrInstance instance, XrSystemId systemId, XrGraphicsRequirementsVulkanKHR* graphicsRequirements);

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ XR_NO_PROTOTYPES
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ XR_EXTENSION_PROTOTYPES
XRAPI_ATTR Xr_ਨਤੀਜਾ XRAPI_CALL xrGetVulkanInstanceExtensionsKHR(
    XrInstance                                  instance,
    XrSystemId                                  systemId,
    uint32_t                                    ਬਫਰ_ਸਮਰੱਥਾ_ਨਿਵੇਸ਼,
    uint32_t*                                   ਬਫਰ_ਗਿਣਤੀ_Output,
    ਅੱਖਰ*                                       ਬਫਰ_2);

XRAPI_ATTR Xr_ਨਤੀਜਾ XRAPI_CALL xrGetVulkanDeviceExtensionsKHR(
    XrInstance                                  instance,
    XrSystemId                                  systemId,
    uint32_t                                    ਬਫਰ_ਸਮਰੱਥਾ_ਨਿਵੇਸ਼,
    uint32_t*                                   ਬਫਰ_ਗਿਣਤੀ_Output,
    ਅੱਖਰ*                                       ਬਫਰ_2);

XRAPI_ATTR Xr_ਨਤੀਜਾ XRAPI_CALL xrGetVulkanGraphicsDeviceKHR(
    XrInstance                                  instance,
    XrSystemId                                  systemId,
    VkInstance                                  vkInstance,
    VkPhysicalDevice*                           vkPhysicalDevice);

XRAPI_ATTR Xr_ਨਤੀਜਾ XRAPI_CALL xrGetVulkanGraphicsRequirementsKHR(
    XrInstance                                  instance,
    XrSystemId                                  systemId,
    XrGraphicsRequirementsVulkanKHR*            graphicsRequirements);
#ਜੇ_ਅੰਤ /* XR_EXTENSION_PROTOTYPES */
#ਜੇ_ਅੰਤ /* !XR_NO_PROTOTYPES */
#ਜੇ_ਅੰਤ /* XR_USE_GRAPHICS_API_VULKAN */

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ XR_USE_GRAPHICS_API_D3D11

// XR_KHR_D3D11_enable is a preprocessor guard. Do not pass it to API calls.
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XR_KHR_D3D11_enable 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XR_KHR_D3_D11_enable_SPEC_ਸੰਸਕਰਣ  11
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XR_KHR_D3D11_ENABLE_EXTENSION_NAME "XR_KHR_D3D11_enable"
// XrGraphicsBindingD3D11KHR extends XrSessionCreateInfo
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ XrGraphicsBindingD3D11KHR {
    XrStructureType             type;
    ਅਚਲ ਖਾਲੀ* XR_MAY_ALIAS    ਅਗਲਾ;
    ID3D11Device*               device;
} XrGraphicsBindingD3D11KHR;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ XrSwapchainImageD3D11KHR {
     XrStructureType      type;
    ਖਾਲੀ* XR_MAY_ALIAS    ਅਗਲਾ;
    ID3D11Texture2D*      texture;
} XrSwapchainImageD3D11KHR;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ XrGraphicsRequirementsD3D11KHR {
    XrStructureType       type;
    ਖਾਲੀ* XR_MAY_ALIAS    ਅਗਲਾ;
    LUID                  adapterLuid;
    D3D_FEATURE_LEVEL     minFeatureLevel;
} XrGraphicsRequirementsD3D11KHR;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ Xr_ਨਤੀਜਾ (XRAPI_PTR *PFN_xrGetD3D11GraphicsRequirementsKHR)(XrInstance instance, XrSystemId systemId, XrGraphicsRequirementsD3D11KHR* graphicsRequirements);

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ XR_NO_PROTOTYPES
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ XR_EXTENSION_PROTOTYPES
XRAPI_ATTR Xr_ਨਤੀਜਾ XRAPI_CALL xrGetD3D11GraphicsRequirementsKHR(
    XrInstance                                  instance,
    XrSystemId                                  systemId,
    XrGraphicsRequirementsD3D11KHR*             graphicsRequirements);
#ਜੇ_ਅੰਤ /* XR_EXTENSION_PROTOTYPES */
#ਜੇ_ਅੰਤ /* !XR_NO_PROTOTYPES */
#ਜੇ_ਅੰਤ /* XR_USE_GRAPHICS_API_D3D11 */

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ XR_USE_GRAPHICS_API_D3D12

// XR_KHR_D3D12_enable is a preprocessor guard. Do not pass it to API calls.
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XR_KHR_D3D12_enable 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XR_KHR_D3_D12_enable_SPEC_ਸੰਸਕਰਣ  11
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XR_KHR_D3D12_ENABLE_EXTENSION_NAME "XR_KHR_D3D12_enable"
// XrGraphicsBindingD3D12KHR extends XrSessionCreateInfo
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ XrGraphicsBindingD3D12KHR {
    XrStructureType             type;
    ਅਚਲ ਖਾਲੀ* XR_MAY_ALIAS    ਅਗਲਾ;
    ID3D12Device*               device;
    ID3_D12_Command_ਕਤਾਰ*         ਕਤਾਰ;
} XrGraphicsBindingD3D12KHR;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ XrSwapchainImageD3D12KHR {
     XrStructureType      type;
    ਖਾਲੀ* XR_MAY_ALIAS    ਅਗਲਾ;
    ID3D12Resource*       texture;
} XrSwapchainImageD3D12KHR;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ XrGraphicsRequirementsD3D12KHR {
    XrStructureType       type;
    ਖਾਲੀ* XR_MAY_ALIAS    ਅਗਲਾ;
    LUID                  adapterLuid;
    D3D_FEATURE_LEVEL     minFeatureLevel;
} XrGraphicsRequirementsD3D12KHR;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ Xr_ਨਤੀਜਾ (XRAPI_PTR *PFN_xrGetD3D12GraphicsRequirementsKHR)(XrInstance instance, XrSystemId systemId, XrGraphicsRequirementsD3D12KHR* graphicsRequirements);

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ XR_NO_PROTOTYPES
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ XR_EXTENSION_PROTOTYPES
XRAPI_ATTR Xr_ਨਤੀਜਾ XRAPI_CALL xrGetD3D12GraphicsRequirementsKHR(
    XrInstance                                  instance,
    XrSystemId                                  systemId,
    XrGraphicsRequirementsD3D12KHR*             graphicsRequirements);
#ਜੇ_ਅੰਤ /* XR_EXTENSION_PROTOTYPES */
#ਜੇ_ਅੰਤ /* !XR_NO_PROTOTYPES */
#ਜੇ_ਅੰਤ /* XR_USE_GRAPHICS_API_D3D12 */

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ XR_USE_GRAPHICS_API_METAL

// XR_KHR_metal_enable is a preprocessor guard. Do not pass it to API calls.
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XR_KHR_metal_enable 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XR_KHR_metal_enable_SPEC_ਸੰਸਕਰਣ  3
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XR_KHR_METAL_ENABLE_EXTENSION_NAME "XR_KHR_metal_enable"
// XrGraphicsBindingMetalKHR extends XrSessionCreateInfo
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ XrGraphicsBindingMetalKHR {
    XrStructureType             type;
    ਅਚਲ ਖਾਲੀ* XR_MAY_ALIAS    ਅਗਲਾ;
    ਖਾਲੀ* XR_MAY_ALIAS          command_ਕਤਾਰ;
} XrGraphicsBindingMetalKHR;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ XrSwapchainImageMetalKHR {
    XrStructureType       type;
    ਖਾਲੀ* XR_MAY_ALIAS    ਅਗਲਾ;
    ਖਾਲੀ* XR_MAY_ALIAS    texture;
} XrSwapchainImageMetalKHR;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ XrGraphicsRequirementsMetalKHR {
    XrStructureType       type;
    ਖਾਲੀ* XR_MAY_ALIAS    ਅਗਲਾ;
    ਖਾਲੀ* XR_MAY_ALIAS    metalDevice;
} XrGraphicsRequirementsMetalKHR;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ Xr_ਨਤੀਜਾ (XRAPI_PTR *PFN_xrGetMetalGraphicsRequirementsKHR)(XrInstance instance, XrSystemId systemId, XrGraphicsRequirementsMetalKHR* graphicsRequirements);

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ XR_NO_PROTOTYPES
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ XR_EXTENSION_PROTOTYPES
XRAPI_ATTR Xr_ਨਤੀਜਾ XRAPI_CALL xrGetMetalGraphicsRequirementsKHR(
    XrInstance                                  instance,
    XrSystemId                                  systemId,
    XrGraphicsRequirementsMetalKHR*             graphicsRequirements);
#ਜੇ_ਅੰਤ /* XR_EXTENSION_PROTOTYPES */
#ਜੇ_ਅੰਤ /* !XR_NO_PROTOTYPES */
#ਜੇ_ਅੰਤ /* XR_USE_GRAPHICS_API_METAL */

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ XR_USE_PLATFORM_WIN32

// XR_KHR_win32_convert_performance_counter_time is a preprocessor guard. Do not pass it to API calls.
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XR_KHR_win32_convert_performance_counter_ਸਮਾਂ 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XR_KHR_win32_convert_performance_counter_ਸਮਾਂ_SPEC_ਸੰਸਕਰਣ 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XR_KHR_WIN32_CONVERT_PERFORMANCE_COUNTER_ਸਮਾਂ_EXTENSION_NAME "XR_KHR_win32_convert_performance_counter_time"
ਕਿਸਮਪਰਿਭਾਸ਼ਾ Xr_ਨਤੀਜਾ (XRAPI_PTR *PFN_xr_Convert_Win32_Performance_Counter_ਮੰਜ਼ਿਲ_ਸਮਾਂ_KHR)(XrInstance instance, ਅਚਲ LARGE_INTEGER* performanceCounter, Xr_ਸਮਾਂ* ਸਮਾਂ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ Xr_ਨਤੀਜਾ (XRAPI_PTR *PFN_xr_Convert_ਸਮਾਂ_ਮੰਜ਼ਿਲ_Win32_Performance_Counter_KHR)(XrInstance instance, Xr_ਸਮਾਂ ਸਮਾਂ, LARGE_INTEGER* performanceCounter);

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ XR_NO_PROTOTYPES
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ XR_EXTENSION_PROTOTYPES
XRAPI_ATTR Xr_ਨਤੀਜਾ XRAPI_CALL xr_Convert_Win32_Performance_Counter_ਮੰਜ਼ਿਲ_ਸਮਾਂ_KHR(
    XrInstance                                  instance,
    ਅਚਲ LARGE_INTEGER*                        performanceCounter,
    Xr_ਸਮਾਂ*                                     ਸਮਾਂ);

XRAPI_ATTR Xr_ਨਤੀਜਾ XRAPI_CALL xr_Convert_ਸਮਾਂ_ਮੰਜ਼ਿਲ_Win32_Performance_Counter_KHR(
    XrInstance                                  instance,
    Xr_ਸਮਾਂ                                      ਸਮਾਂ,
    LARGE_INTEGER*                              performanceCounter);
#ਜੇ_ਅੰਤ /* XR_EXTENSION_PROTOTYPES */
#ਜੇ_ਅੰਤ /* !XR_NO_PROTOTYPES */
#ਜੇ_ਅੰਤ /* XR_USE_PLATFORM_WIN32 */

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ XR_USE_TIMESPEC

// XR_KHR_convert_timespec_time is a preprocessor guard. Do not pass it to API calls.
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XR_KHR_convert_timespec_ਸਮਾਂ 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XR_KHR_convert_timespec_ਸਮਾਂ_SPEC_ਸੰਸਕਰਣ 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XR_KHR_CONVERT_TIMESPEC_ਸਮਾਂ_EXTENSION_NAME "XR_KHR_convert_timespec_time"
ਕਿਸਮਪਰਿਭਾਸ਼ਾ Xr_ਨਤੀਜਾ (XRAPI_PTR *PFN_xr_Convert_Timespec_ਸਮਾਂ_ਮੰਜ਼ਿਲ_ਸਮਾਂ_KHR)(XrInstance instance, ਅਚਲ ਬਣਤਰ timespec* timespec_ਸਮਾਂ, Xr_ਸਮਾਂ* ਸਮਾਂ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ Xr_ਨਤੀਜਾ (XRAPI_PTR *PFN_xr_Convert_ਸਮਾਂ_ਮੰਜ਼ਿਲ_Timespec_ਸਮਾਂ_KHR)(XrInstance instance, Xr_ਸਮਾਂ ਸਮਾਂ, ਬਣਤਰ timespec* timespec_ਸਮਾਂ);

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ XR_NO_PROTOTYPES
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ XR_EXTENSION_PROTOTYPES
XRAPI_ATTR Xr_ਨਤੀਜਾ XRAPI_CALL xr_Convert_Timespec_ਸਮਾਂ_ਮੰਜ਼ਿਲ_ਸਮਾਂ_KHR(
    XrInstance                                  instance,
    ਅਚਲ ਬਣਤਰ timespec*                      timespec_ਸਮਾਂ,
    Xr_ਸਮਾਂ*                                     ਸਮਾਂ);

XRAPI_ATTR Xr_ਨਤੀਜਾ XRAPI_CALL xr_Convert_ਸਮਾਂ_ਮੰਜ਼ਿਲ_Timespec_ਸਮਾਂ_KHR(
    XrInstance                                  instance,
    Xr_ਸਮਾਂ                                      ਸਮਾਂ,
    ਬਣਤਰ timespec*                            timespec_ਸਮਾਂ);
#ਜੇ_ਅੰਤ /* XR_EXTENSION_PROTOTYPES */
#ਜੇ_ਅੰਤ /* !XR_NO_PROTOTYPES */
#ਜੇ_ਅੰਤ /* XR_USE_TIMESPEC */

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ XR_USE_PLATFORM_ANDROID

// XR_KHR_loader_init_android is a preprocessor guard. Do not pass it to API calls.
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XR_KHR_loader_init_android 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XR_KHR_loader_init_android_SPEC_ਸੰਸਕਰਣ 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XR_KHR_LOADER_INIT_ANDROID_EXTENSION_NAME "XR_KHR_loader_init_android"
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ XrLoaderInitInfoAndroidKHR {
    XrStructureType             type;
    ਅਚਲ ਖਾਲੀ* XR_MAY_ALIAS    ਅਗਲਾ;
    ਖਾਲੀ* XR_MAY_ALIAS          applicationVM;
    ਖਾਲੀ* XR_MAY_ALIAS          applicationContext;
} XrLoaderInitInfoAndroidKHR;

#ਜੇ_ਅੰਤ /* XR_USE_PLATFORM_ANDROID */

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ XR_USE_GRAPHICS_API_VULKAN

// XR_KHR_vulkan_enable2 is a preprocessor guard. Do not pass it to API calls.
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XR_KHR_vulkan_enable2 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XR_KHR_vulkan_enable2_SPEC_ਸੰਸਕਰਣ 4
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XR_KHR_VULKAN_ENABLE2_EXTENSION_NAME "XR_KHR_vulkan_enable2"
ਕਿਸਮਪਰਿਭਾਸ਼ਾ XrFlags64 XrVulkanInstanceCreateFlagsKHR;

// Flag bits for XrVulkanInstanceCreateFlagsKHR

ਕਿਸਮਪਰਿਭਾਸ਼ਾ XrFlags64 XrVulkanDeviceCreateFlagsKHR;

// Flag bits for XrVulkanDeviceCreateFlagsKHR

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ XrVulkanInstanceCreateInfoKHR {
    XrStructureType                   type;
    ਅਚਲ ਖਾਲੀ* XR_MAY_ALIAS          ਅਗਲਾ;
    XrSystemId                        systemId;
    XrVulkanInstanceCreateFlagsKHR    createFlags;
    PFN_vkGetInstanceProcAddr         pfnGetInstanceProcAddr;
    ਅਚਲ VkInstanceCreateInfo*       vulkanCreateInfo;
    ਅਚਲ Vk_ਵੰਡ_Callbacks*      vulkanAllocator;
} XrVulkanInstanceCreateInfoKHR;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ XrVulkanDeviceCreateInfoKHR {
    XrStructureType                 type;
    ਅਚਲ ਖਾਲੀ* XR_MAY_ALIAS        ਅਗਲਾ;
    XrSystemId                      systemId;
    XrVulkanDeviceCreateFlagsKHR    createFlags;
    PFN_vkGetInstanceProcAddr       pfnGetInstanceProcAddr;
    VkPhysicalDevice                vulkanPhysicalDevice;
    ਅਚਲ VkDeviceCreateInfo*       vulkanCreateInfo;
    ਅਚਲ Vk_ਵੰਡ_Callbacks*    vulkanAllocator;
} XrVulkanDeviceCreateInfoKHR;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ XrGraphicsBindingVulkanKHR XrGraphicsBindingVulkan2KHR;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ XrVulkanGraphicsDeviceGetInfoKHR {
    XrStructureType             type;
    ਅਚਲ ਖਾਲੀ* XR_MAY_ALIAS    ਅਗਲਾ;
    XrSystemId                  systemId;
    VkInstance                  vulkanInstance;
} XrVulkanGraphicsDeviceGetInfoKHR;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ XrSwapchainImageVulkanKHR XrSwapchainImageVulkan2KHR;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ XrGraphicsRequirementsVulkanKHR XrGraphicsRequirementsVulkan2KHR;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ Xr_ਨਤੀਜਾ (XRAPI_PTR *PFN_xrCreateVulkanInstanceKHR)(XrInstance instance, ਅਚਲ XrVulkanInstanceCreateInfoKHR* createInfo, VkInstance* vulkanInstance, Vk_ਨਤੀਜਾ* vulkan_ਨਤੀਜਾ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ Xr_ਨਤੀਜਾ (XRAPI_PTR *PFN_xrCreateVulkanDeviceKHR)(XrInstance instance, ਅਚਲ XrVulkanDeviceCreateInfoKHR* createInfo, VkDevice* vulkanDevice, Vk_ਨਤੀਜਾ* vulkan_ਨਤੀਜਾ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ Xr_ਨਤੀਜਾ (XRAPI_PTR *PFN_xrGetVulkanGraphicsDevice2KHR)(XrInstance instance, ਅਚਲ XrVulkanGraphicsDeviceGetInfoKHR* getInfo, VkPhysicalDevice* vulkanPhysicalDevice);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ Xr_ਨਤੀਜਾ (XRAPI_PTR *PFN_xrGetVulkanGraphicsRequirements2KHR)(XrInstance instance, XrSystemId systemId, XrGraphicsRequirementsVulkanKHR* graphicsRequirements);

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ XR_NO_PROTOTYPES
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ XR_EXTENSION_PROTOTYPES
XRAPI_ATTR Xr_ਨਤੀਜਾ XRAPI_CALL xrCreateVulkanInstanceKHR(
    XrInstance                                  instance,
    ਅਚਲ XrVulkanInstanceCreateInfoKHR*        createInfo,
    VkInstance*                                 vulkanInstance,
    Vk_ਨਤੀਜਾ*                                   vulkan_ਨਤੀਜਾ);

XRAPI_ATTR Xr_ਨਤੀਜਾ XRAPI_CALL xrCreateVulkanDeviceKHR(
    XrInstance                                  instance,
    ਅਚਲ XrVulkanDeviceCreateInfoKHR*          createInfo,
    VkDevice*                                   vulkanDevice,
    Vk_ਨਤੀਜਾ*                                   vulkan_ਨਤੀਜਾ);

XRAPI_ATTR Xr_ਨਤੀਜਾ XRAPI_CALL xrGetVulkanGraphicsDevice2KHR(
    XrInstance                                  instance,
    ਅਚਲ XrVulkanGraphicsDeviceGetInfoKHR*     getInfo,
    VkPhysicalDevice*                           vulkanPhysicalDevice);

XRAPI_ATTR Xr_ਨਤੀਜਾ XRAPI_CALL xrGetVulkanGraphicsRequirements2KHR(
    XrInstance                                  instance,
    XrSystemId                                  systemId,
    XrGraphicsRequirementsVulkanKHR*            graphicsRequirements);
#ਜੇ_ਅੰਤ /* XR_EXTENSION_PROTOTYPES */
#ਜੇ_ਅੰਤ /* !XR_NO_PROTOTYPES */
#ਜੇ_ਅੰਤ /* XR_USE_GRAPHICS_API_VULKAN */

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ XR_USE_PLATFORM_EGL

// XR_MNDX_egl_enable is a preprocessor guard. Do not pass it to API calls.
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XR_MNDX_egl_enable 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XR_MNDX_egl_enable_SPEC_ਸੰਸਕਰਣ   2
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XR_MNDX_EGL_ENABLE_EXTENSION_NAME "XR_MNDX_egl_enable"
ਕਿਸਮਪਰਿਭਾਸ਼ਾ PFN_xrVoidFunction (*PFN_xr_Egl_Get_Proc_ਪਤਾ_MNDX)(ਅਚਲ ਅੱਖਰ *name);
// XrGraphicsBindingEGLMNDX extends XrSessionCreateInfo
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ XrGraphicsBindingEGLMNDX {
    XrStructureType                type;
    ਅਚਲ ਖਾਲੀ* XR_MAY_ALIAS       ਅਗਲਾ;
    PFN_xr_Egl_Get_Proc_ਪਤਾ_MNDX    get_Proc_ਪਤਾ;
    EGLDisplay                     display;
    EGLConfig                      config;
    EGLContext                     context;
} XrGraphicsBindingEGLMNDX;

#ਜੇ_ਅੰਤ /* XR_USE_PLATFORM_EGL */

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ XR_USE_PLATFORM_WIN32

// XR_MSFT_perception_anchor_interop is a preprocessor guard. Do not pass it to API calls.
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XR_MSFT_perception_anchor_interop 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XR_MSFT_perception_anchor_interop_SPEC_ਸੰਸਕਰਣ 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XR_MSFT_PERCEPTION_ANCHOR_INTEROP_EXTENSION_NAME "XR_MSFT_perception_anchor_interop"
ਕਿਸਮਪਰਿਭਾਸ਼ਾ Xr_ਨਤੀਜਾ (XRAPI_PTR *PFN_xrCreateSpatialAnchorFromPerceptionAnchorMSFT)(XrSession session, IUnknown* perceptionAnchor, XrSpatialAnchorMSFT* anchor);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ Xr_ਨਤੀਜਾ (XRAPI_PTR *PFN_xrTryGetPerceptionAnchorFromSpatialAnchorMSFT)(XrSession session, XrSpatialAnchorMSFT anchor, IUnknown** perceptionAnchor);

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ XR_NO_PROTOTYPES
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ XR_EXTENSION_PROTOTYPES
XRAPI_ATTR Xr_ਨਤੀਜਾ XRAPI_CALL xrCreateSpatialAnchorFromPerceptionAnchorMSFT(
    XrSession                                   session,
    IUnknown*                                   perceptionAnchor,
    XrSpatialAnchorMSFT*                        anchor);

XRAPI_ATTR Xr_ਨਤੀਜਾ XRAPI_CALL xrTryGetPerceptionAnchorFromSpatialAnchorMSFT(
    XrSession                                   session,
    XrSpatialAnchorMSFT                         anchor,
    IUnknown**                                  perceptionAnchor);
#ਜੇ_ਅੰਤ /* XR_EXTENSION_PROTOTYPES */
#ਜੇ_ਅੰਤ /* !XR_NO_PROTOTYPES */
#ਜੇ_ਅੰਤ /* XR_USE_PLATFORM_WIN32 */

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ XR_USE_PLATFORM_WIN32

// XR_MSFT_holographic_window_attachment is a preprocessor guard. Do not pass it to API calls.
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XR_MSFT_holographic_ਖਿੜਕੀ_attachment 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XR_MSFT_holographic_ਖਿੜਕੀ_attachment_SPEC_ਸੰਸਕਰਣ 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XR_MSFT_HOLOGRAPHIC_ਖਿੜਕੀ_ATTACHMENT_EXTENSION_NAME "XR_MSFT_holographic_window_attachment"
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ XR_USE_PLATFORM_WIN32
// XrHolographicWindowAttachmentMSFT extends XrSessionCreateInfo
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ Xr_Holographic_ਖਿੜਕੀ_Attachment_MSFT {
    XrStructureType             type;
    ਅਚਲ ਖਾਲੀ* XR_MAY_ALIAS    ਅਗਲਾ;
    IUnknown*                   holographicSpace;
    IUnknown*                   core_ਖਿੜਕੀ;
} Xr_Holographic_ਖਿੜਕੀ_Attachment_MSFT;
#ਜੇ_ਅੰਤ // XR_USE_PLATFORM_WIN32

#ਜੇ_ਅੰਤ /* XR_USE_PLATFORM_WIN32 */

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ XR_USE_PLATFORM_ANDROID

// XR_FB_android_surface_swapchain_create is a preprocessor guard. Do not pass it to API calls.
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XR_FB_android_surface_swapchain_create 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XR_FB_android_surface_swapchain_create_SPEC_ਸੰਸਕਰਣ 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XR_FB_ANDROID_SURFACE_SWAPCHAIN_CREATE_EXTENSION_NAME "XR_FB_android_surface_swapchain_create"
ਕਿਸਮਪਰਿਭਾਸ਼ਾ XrFlags64 XrAndroidSurfaceSwapchainFlagsFB;

// Flag bits for XrAndroidSurfaceSwapchainFlagsFB
ਸਥਿਰ ਅਚਲ XrAndroidSurfaceSwapchainFlagsFB XR_ANDROID_SURFACE_SWAPCHAIN_SYNCHRONOUS_ਦੋਆਧਾਰੀ_ਅੰਕ_FB = 0x00000001;
ਸਥਿਰ ਅਚਲ XrAndroidSurfaceSwapchainFlagsFB XR_ANDROID_SURFACE_SWAPCHAIN_USE_TIMESTAMPS_ਦੋਆਧਾਰੀ_ਅੰਕ_FB = 0x00000002;

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ XR_USE_PLATFORM_ANDROID
// XrAndroidSurfaceSwapchainCreateInfoFB extends XrSwapchainCreateInfo
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ XrAndroidSurfaceSwapchainCreateInfoFB {
    XrStructureType                     type;
    ਅਚਲ ਖਾਲੀ* XR_MAY_ALIAS            ਅਗਲਾ;
    XrAndroidSurfaceSwapchainFlagsFB    createFlags;
} XrAndroidSurfaceSwapchainCreateInfoFB;
#ਜੇ_ਅੰਤ // XR_USE_PLATFORM_ANDROID

#ਜੇ_ਅੰਤ /* XR_USE_PLATFORM_ANDROID */

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ XR_USE_PLATFORM_ML

// XR_ML_compat is a preprocessor guard. Do not pass it to API calls.
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XR_ML_compat 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XR_ML_compat_SPEC_ਸੰਸਕਰਣ         1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XR_ML_COMPAT_EXTENSION_NAME       "XR_ML_compat"
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ XrCoordinateSpaceCreateInfoML {
    XrStructureType             type;
    ਅਚਲ ਖਾਲੀ* XR_MAY_ALIAS    ਅਗਲਾ;
    MLCoordinate_ਚੌਖਟਾ_UID        cfuid;
    XrPosef                     pose_ਵਿੱਚ_Coordinate_Space;
} XrCoordinateSpaceCreateInfoML;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ Xr_ਨਤੀਜਾ (XRAPI_PTR *PFN_xr_Create_Space_From_Coordinate_ਚੌਖਟਾ_UIDML)(XrSession session, ਅਚਲ XrCoordinateSpaceCreateInfoML *createInfo, XrSpace* space);

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ XR_NO_PROTOTYPES
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ XR_EXTENSION_PROTOTYPES
XRAPI_ATTR Xr_ਨਤੀਜਾ XRAPI_CALL xr_Create_Space_From_Coordinate_ਚੌਖਟਾ_UIDML(
    XrSession                                   session,
    ਅਚਲ XrCoordinateSpaceCreateInfoML *       createInfo,
    XrSpace*                                    space);
#ਜੇ_ਅੰਤ /* XR_EXTENSION_PROTOTYPES */
#ਜੇ_ਅੰਤ /* !XR_NO_PROTOTYPES */
#ਜੇ_ਅੰਤ /* XR_USE_PLATFORM_ML */

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ XR_USE_PLATFORM_WIN32

// XR_OCULUS_audio_device_guid is a preprocessor guard. Do not pass it to API calls.
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XR_OCULUS_audio_device_guid 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XR_OCULUS_audio_device_guid_SPEC_ਸੰਸਕਰਣ 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XR_OCULUS_AUDIO_DEVICE_GUID_EXTENSION_NAME "XR_OCULUS_audio_device_guid"
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XR_MAX_AUDIO_DEVICE_STR_ਮਾਪ_OCULUS 128
ਕਿਸਮਪਰਿਭਾਸ਼ਾ Xr_ਨਤੀਜਾ (XRAPI_PTR *PFN_xrGetAudioOutputDeviceGuidOculus)(XrInstance instance, wchar_t ਬਫਰ_2[XR_MAX_AUDIO_DEVICE_STR_ਮਾਪ_OCULUS]);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ Xr_ਨਤੀਜਾ (XRAPI_PTR *PFN_xr_Get_Audio_ਨਿਵੇਸ਼_Device_Guid_Oculus)(XrInstance instance, wchar_t ਬਫਰ_2[XR_MAX_AUDIO_DEVICE_STR_ਮਾਪ_OCULUS]);

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ XR_NO_PROTOTYPES
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ XR_EXTENSION_PROTOTYPES
XRAPI_ATTR Xr_ਨਤੀਜਾ XRAPI_CALL xrGetAudioOutputDeviceGuidOculus(
    XrInstance                                  instance,
    wchar_t                                     ਬਫਰ_2[XR_MAX_AUDIO_DEVICE_STR_ਮਾਪ_OCULUS]);

XRAPI_ATTR Xr_ਨਤੀਜਾ XRAPI_CALL xr_Get_Audio_ਨਿਵੇਸ਼_Device_Guid_Oculus(
    XrInstance                                  instance,
    wchar_t                                     ਬਫਰ_2[XR_MAX_AUDIO_DEVICE_STR_ਮਾਪ_OCULUS]);
#ਜੇ_ਅੰਤ /* XR_EXTENSION_PROTOTYPES */
#ਜੇ_ਅੰਤ /* !XR_NO_PROTOTYPES */
#ਜੇ_ਅੰਤ /* XR_USE_PLATFORM_WIN32 */

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ XR_USE_GRAPHICS_API_VULKAN

// XR_FB_foveation_vulkan is a preprocessor guard. Do not pass it to API calls.
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XR_FB_foveation_vulkan 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XR_FB_foveation_vulkan_SPEC_ਸੰਸਕਰਣ 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XR_FB_FOVEATION_VULKAN_EXTENSION_NAME "XR_FB_foveation_vulkan"
// XrSwapchainImageFoveationVulkanFB extends XrSwapchainImageVulkanKHR
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ XrSwapchainImageFoveationVulkanFB {
    XrStructureType       type;
    ਖਾਲੀ* XR_MAY_ALIAS    ਅਗਲਾ;
    VkImage               image;
    uint32_t              ਚੌੜਾਈ;
    uint32_t              ਉਚਾਈ;
} XrSwapchainImageFoveationVulkanFB;

#ਜੇ_ਅੰਤ /* XR_USE_GRAPHICS_API_VULKAN */

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ XR_USE_PLATFORM_ANDROID

// XR_FB_swapchain_update_state_android_surface is a preprocessor guard. Do not pass it to API calls.
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XR_FB_swapchain_update_state_android_surface 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XR_FB_swapchain_update_state_android_surface_SPEC_ਸੰਸਕਰਣ 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XR_FB_SWAPCHAIN_UPDATE_STATE_ANDROID_SURFACE_EXTENSION_NAME "XR_FB_swapchain_update_state_android_surface"
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ XR_USE_PLATFORM_ANDROID
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ XrSwapchainStateAndroidSurfaceDimensionsFB {
    XrStructureType       type;
    ਖਾਲੀ* XR_MAY_ALIAS    ਅਗਲਾ;
    uint32_t              ਚੌੜਾਈ;
    uint32_t              ਉਚਾਈ;
} XrSwapchainStateAndroidSurfaceDimensionsFB;
#ਜੇ_ਅੰਤ // XR_USE_PLATFORM_ANDROID

#ਜੇ_ਅੰਤ /* XR_USE_PLATFORM_ANDROID */

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ XR_USE_GRAPHICS_API_OPENGL_ES

// XR_FB_swapchain_update_state_opengl_es is a preprocessor guard. Do not pass it to API calls.
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XR_FB_swapchain_update_state_opengl_es 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XR_FB_swapchain_update_state_opengl_es_SPEC_ਸੰਸਕਰਣ 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XR_FB_SWAPCHAIN_UPDATE_STATE_OPENGL_ES_EXTENSION_NAME "XR_FB_swapchain_update_state_opengl_es"
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ XR_USE_GRAPHICS_API_OPENGL_ES
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ XrSwapchainStateSamplerOpenGLESFB {
    XrStructureType       type;
    ਖਾਲੀ* XR_MAY_ALIAS    ਅਗਲਾ;
    EGLenum               minFilter;
    EGLenum               magFilter;
    EGLenum               wrap_ਬਹੁਲਕ_S;
    EGLenum               wrap_ਬਹੁਲਕ_T;
    EGLenum               swizzleRed;
    EGLenum               swizzleGreen;
    EGLenum               swizzleBlue;
    EGLenum               swizzleAlpha;
    ਦਸ਼ਮਲਵ                 maxAnisotropy;
    XrColor4f             borderColor;
} XrSwapchainStateSamplerOpenGLESFB;
#ਜੇ_ਅੰਤ // XR_USE_GRAPHICS_API_OPENGL_ES

#ਜੇ_ਅੰਤ /* XR_USE_GRAPHICS_API_OPENGL_ES */

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ XR_USE_GRAPHICS_API_VULKAN

// XR_FB_swapchain_update_state_vulkan is a preprocessor guard. Do not pass it to API calls.
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XR_FB_swapchain_update_state_vulkan 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XR_FB_swapchain_update_state_vulkan_SPEC_ਸੰਸਕਰਣ 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XR_FB_SWAPCHAIN_UPDATE_STATE_VULKAN_EXTENSION_NAME "XR_FB_swapchain_update_state_vulkan"
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ XR_USE_GRAPHICS_API_VULKAN
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ XrSwapchainStateSamplerVulkanFB {
    XrStructureType         type;
    ਖਾਲੀ* XR_MAY_ALIAS      ਅਗਲਾ;
    VkFilter                minFilter;
    VkFilter                magFilter;
    Vk_Sampler_Mipmap_ਬਹੁਲਕ     mipmap_ਬਹੁਲਕ;
    Vk_Sampler_ਪਤਾ_ਬਹੁਲਕ    wrap_ਬਹੁਲਕ_S;
    Vk_Sampler_ਪਤਾ_ਬਹੁਲਕ    wrap_ਬਹੁਲਕ_T;
    VkComponentSwizzle      swizzleRed;
    VkComponentSwizzle      swizzleGreen;
    VkComponentSwizzle      swizzleBlue;
    VkComponentSwizzle      swizzleAlpha;
    ਦਸ਼ਮਲਵ                   maxAnisotropy;
    XrColor4f               borderColor;
} XrSwapchainStateSamplerVulkanFB;
#ਜੇ_ਅੰਤ // XR_USE_GRAPHICS_API_VULKAN

#ਜੇ_ਅੰਤ /* XR_USE_GRAPHICS_API_VULKAN */

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ XR_USE_GRAPHICS_API_VULKAN

// XR_META_vulkan_swapchain_create_info is a preprocessor guard. Do not pass it to API calls.
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XR_META_vulkan_swapchain_create_info 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XR_META_vulkan_swapchain_create_info_SPEC_ਸੰਸਕਰਣ 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XR_META_VULKAN_SWAPCHAIN_CREATE_INFO_EXTENSION_NAME "XR_META_vulkan_swapchain_create_info"
// XrVulkanSwapchainCreateInfoMETA extends XrSwapchainCreateInfo
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ XrVulkanSwapchainCreateInfoMETA {
    XrStructureType             type;
    ਅਚਲ ਖਾਲੀ* XR_MAY_ALIAS    ਅਗਲਾ;
    VkImageCreateFlags          additionalCreateFlags;
    VkImageUsageFlags           additionalUsageFlags;
} XrVulkanSwapchainCreateInfoMETA;

#ਜੇ_ਅੰਤ /* XR_USE_GRAPHICS_API_VULKAN */

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ XR_USE_PLATFORM_ANDROID

// XR_ANDROID_anchor_sharing_export is a preprocessor guard. Do not pass it to API calls.
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XR_ANDROID_anchor_sharing_export 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XR_ANDROID_anchor_sharing_export_SPEC_ਸੰਸਕਰਣ 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XR_ANDROID_ANCHOR_SHARING_EXPORT_EXTENSION_NAME "XR_ANDROID_anchor_sharing_export"
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ XrAnchorSharingInfoANDROID {
    XrStructureType             type;
    ਅਚਲ ਖਾਲੀ* XR_MAY_ALIAS    ਅਗਲਾ;
    XrSpace                     anchor;
} XrAnchorSharingInfoANDROID;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ XrAnchorSharingTokenANDROID {
    XrStructureType       type;
    ਖਾਲੀ* XR_MAY_ALIAS    ਅਗਲਾ;
    ਬਣਤਰ AIBinder*      token;
} XrAnchorSharingTokenANDROID;

// XrSystemAnchorSharingExportPropertiesANDROID extends XrSystemProperties
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ XrSystemAnchorSharingExportPropertiesANDROID {
    XrStructureType       type;
    ਖਾਲੀ* XR_MAY_ALIAS    ਅਗਲਾ;
    XrBool32              supportsAnchorSharingExport;
} XrSystemAnchorSharingExportPropertiesANDROID;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ Xr_ਨਤੀਜਾ (XRAPI_PTR *PFN_xrShareAnchorANDROID)(XrSession session, ਅਚਲ XrAnchorSharingInfoANDROID* sharingInfo, XrAnchorSharingTokenANDROID* anchorToken);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ Xr_ਨਤੀਜਾ (XRAPI_PTR *PFN_xrUnshareAnchorANDROID)(XrSession session, XrSpace anchor);

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ XR_NO_PROTOTYPES
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ XR_EXTENSION_PROTOTYPES
XRAPI_ATTR Xr_ਨਤੀਜਾ XRAPI_CALL xrShareAnchorANDROID(
    XrSession                                   session,
    ਅਚਲ XrAnchorSharingInfoANDROID*           sharingInfo,
    XrAnchorSharingTokenANDROID*                anchorToken);

XRAPI_ATTR Xr_ਨਤੀਜਾ XRAPI_CALL xrUnshareAnchorANDROID(
    XrSession                                   session,
    XrSpace                                     anchor);
#ਜੇ_ਅੰਤ /* XR_EXTENSION_PROTOTYPES */
#ਜੇ_ਅੰਤ /* !XR_NO_PROTOTYPES */
#ਜੇ_ਅੰਤ /* XR_USE_PLATFORM_ANDROID */

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __cplusplus
}
#ਜੇ_ਅੰਤ

#ਜੇ_ਅੰਤ
