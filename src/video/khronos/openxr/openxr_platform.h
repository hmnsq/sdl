#ifndef OPENXR_PLATFORM_H_
#define OPENXR_PLATFORM_H_ 1

/*
** Copyright 2017-2026 The Khronos Group Inc.
**
** SPDX-License-Identifier: Apache-2.0 OR MIT
*/

/*
** This header is generated from the Khronos OpenXR XML API Registry.
**
*/

#અન્તર્ભાવ "openxr.h"

#ifdef __cplusplus
બાહ્ય "C" {
#endif


#ifdef XR_USE_PLATFORM_ANDROID

// XR_KHR_android_thread_settings is a preprocessor guard. Do not pass it to API calls.
#define XR_KHR_android_thread_settings 1
#define XR_KHR_android_thread_settings_SPEC_VERSION 6
#define XR_KHR_ANDROID_THREAD_SETTINGS_EXTENSION_NAME "XR_KHR_android_thread_settings"

પ્રકારવ્યાખ્યા ગણના XrAndroidThreadTypeKHR {
    XR_ANDROID_THREAD_TYPE_APPLICATION_MAIN_KHR = 1,
    XR_ANDROID_THREAD_TYPE_APPLICATION_WORKER_KHR = 2,
    XR_ANDROID_THREAD_TYPE_RENDERER_MAIN_KHR = 3,
    XR_ANDROID_THREAD_TYPE_RENDERER_WORKER_KHR = 4,
    XR_ANDROID_THREAD_TYPE_MAX_ENUM_KHR = 0x7FFFFFFF
} XrAndroidThreadTypeKHR;
પ્રકારવ્યાખ્યા XrResult (XRAPI_PTR *PFN_xrSetAndroidApplicationThreadKHR)(XrSession session, XrAndroidThreadTypeKHR threadType, uint32_t threadId);

#ifndef XR_NO_PROTOTYPES
#ifdef XR_EXTENSION_PROTOTYPES
XRAPI_ATTR XrResult XRAPI_CALL xrSetAndroidApplicationThreadKHR(
    XrSession                                   session,
    XrAndroidThreadTypeKHR                      threadType,
    uint32_t                                    threadId);
#endif /* XR_EXTENSION_PROTOTYPES */
#endif /* !XR_NO_PROTOTYPES */
#endif /* XR_USE_PLATFORM_ANDROID */

#ifdef XR_USE_PLATFORM_ANDROID

// XR_KHR_android_surface_swapchain is a preprocessor guard. Do not pass it to API calls.
#define XR_KHR_android_surface_swapchain 1
#define XR_KHR_android_surface_swapchain_SPEC_VERSION 4
#define XR_KHR_ANDROID_SURFACE_SWAPCHAIN_EXTENSION_NAME "XR_KHR_android_surface_swapchain"
પ્રકારવ્યાખ્યા XrResult (XRAPI_PTR *PFN_xrCreateSwapchainAndroidSurfaceKHR)(XrSession session, અચલ XrSwapchainCreateInfo* info, XrSwapchain* swapchain, jobject* surface);

#ifndef XR_NO_PROTOTYPES
#ifdef XR_EXTENSION_PROTOTYPES
XRAPI_ATTR XrResult XRAPI_CALL xrCreateSwapchainAndroidSurfaceKHR(
    XrSession                                   session,
    અચલ XrSwapchainCreateInfo*                info,
    XrSwapchain*                                swapchain,
    jobject*                                    surface);
#endif /* XR_EXTENSION_PROTOTYPES */
#endif /* !XR_NO_PROTOTYPES */
#endif /* XR_USE_PLATFORM_ANDROID */

#ifdef XR_USE_PLATFORM_ANDROID

// XR_KHR_android_create_instance is a preprocessor guard. Do not pass it to API calls.
#define XR_KHR_android_create_instance 1
#define XR_KHR_android_create_instance_SPEC_VERSION 3
#define XR_KHR_ANDROID_CREATE_INSTANCE_EXTENSION_NAME "XR_KHR_android_create_instance"
// XrInstanceCreateInfoAndroidKHR extends XrInstanceCreateInfo
પ્રકારવ્યાખ્યા સંરચના XrInstanceCreateInfoAndroidKHR {
    XrStructureType             type;
    અચલ શૂન્ય* XR_MAY_ALIAS    next;
    શૂન્ય* XR_MAY_ALIAS          applicationVM;
    શૂન્ય* XR_MAY_ALIAS          applicationActivity;
} XrInstanceCreateInfoAndroidKHR;

#endif /* XR_USE_PLATFORM_ANDROID */

#ifdef XR_USE_GRAPHICS_API_VULKAN

// XR_KHR_vulkan_swapchain_format_list is a preprocessor guard. Do not pass it to API calls.
#define XR_KHR_vulkan_swapchain_format_list 1
#define XR_KHR_vulkan_swapchain_format_list_SPEC_VERSION 5
#define XR_KHR_VULKAN_SWAPCHAIN_FORMAT_LIST_EXTENSION_NAME "XR_KHR_vulkan_swapchain_format_list"
// XrVulkanSwapchainFormatListCreateInfoKHR extends XrSwapchainCreateInfo
પ્રકારવ્યાખ્યા સંરચના XrVulkanSwapchainFormatListCreateInfoKHR {
    XrStructureType             type;
    અચલ શૂન્ય* XR_MAY_ALIAS    next;
    uint32_t                    view_Format_ગણતરી;
    અચલ VkFormat*             viewFormats;
} XrVulkanSwapchainFormatListCreateInfoKHR;

#endif /* XR_USE_GRAPHICS_API_VULKAN */

#ifdef XR_USE_GRAPHICS_API_OPENGL

// XR_KHR_opengl_enable is a preprocessor guard. Do not pass it to API calls.
#define XR_KHR_opengl_enable 1
#define XR_KHR_opengl_enable_SPEC_VERSION 12
#define XR_KHR_OPENGL_ENABLE_EXTENSION_NAME "XR_KHR_opengl_enable"
#ifdef XR_USE_PLATFORM_WIN32
// XrGraphicsBindingOpenGLWin32KHR extends XrSessionCreateInfo
પ્રકારવ્યાખ્યા સંરચના XrGraphicsBindingOpenGLWin32KHR {
    XrStructureType             type;
    અચલ શૂન્ય* XR_MAY_ALIAS    next;
    HDC                         hDC;
    HGLRC                       hGLRC;
} XrGraphicsBindingOpenGLWin32KHR;
#endif // XR_USE_PLATFORM_WIN32

#ifdef XR_USE_PLATFORM_XLIB
// XrGraphicsBindingOpenGLXlibKHR extends XrSessionCreateInfo
પ્રકારવ્યાખ્યા સંરચના XrGraphicsBindingOpenGLXlibKHR {
    XrStructureType             type;
    અચલ શૂન્ય* XR_MAY_ALIAS    next;
    Display*                    xDisplay;
    uint32_t                    visualid;
    GLXFBConfig                 glxFBConfig;
    GLXDrawable                 glxDrawable;
    GLXContext                  glxContext;
} XrGraphicsBindingOpenGLXlibKHR;
#endif // XR_USE_PLATFORM_XLIB

#ifdef XR_USE_PLATFORM_XCB
// XrGraphicsBindingOpenGLXcbKHR extends XrSessionCreateInfo
પ્રકારવ્યાખ્યા સંરચના XrGraphicsBindingOpenGLXcbKHR {
    XrStructureType             type;
    અચલ શૂન્ય* XR_MAY_ALIAS    next;
    xcb_connection_t*           connection;
    uint32_t                    screen_સંખ્યા;
    xcb_glx_fbconfig_t          fbconfigid;
    xcb_visualid_t              visualid;
    xcb_glx_drawable_t          glxDrawable;
    xcb_glx_context_t           glxContext;
} XrGraphicsBindingOpenGLXcbKHR;
#endif // XR_USE_PLATFORM_XCB

#ifdef XR_USE_PLATFORM_WAYLAND
// XrGraphicsBindingOpenGLWaylandKHR extends XrSessionCreateInfo
પ્રકારવ્યાખ્યા સંરચના XrGraphicsBindingOpenGLWaylandKHR {
    XrStructureType             type;
    અચલ શૂન્ય* XR_MAY_ALIAS    next;
    સંરચના wl_display*          display;
} XrGraphicsBindingOpenGLWaylandKHR;
#endif // XR_USE_PLATFORM_WAYLAND

પ્રકારવ્યાખ્યા સંરચના XrSwapchainImageOpenGLKHR {
    XrStructureType       type;
    શૂન્ય* XR_MAY_ALIAS    next;
    uint32_t              image;
} XrSwapchainImageOpenGLKHR;

પ્રકારવ્યાખ્યા સંરચના XrGraphicsRequirementsOpenGLKHR {
    XrStructureType       type;
    શૂન્ય* XR_MAY_ALIAS    next;
    XrVersion             minApiVersionSupported;
    XrVersion             maxApiVersionSupported;
} XrGraphicsRequirementsOpenGLKHR;

પ્રકારવ્યાખ્યા XrResult (XRAPI_PTR *PFN_xrGetOpenGLGraphicsRequirementsKHR)(XrInstance instance, XrSystemId systemId, XrGraphicsRequirementsOpenGLKHR* graphicsRequirements);

#ifndef XR_NO_PROTOTYPES
#ifdef XR_EXTENSION_PROTOTYPES
XRAPI_ATTR XrResult XRAPI_CALL xrGetOpenGLGraphicsRequirementsKHR(
    XrInstance                                  instance,
    XrSystemId                                  systemId,
    XrGraphicsRequirementsOpenGLKHR*            graphicsRequirements);
#endif /* XR_EXTENSION_PROTOTYPES */
#endif /* !XR_NO_PROTOTYPES */
#endif /* XR_USE_GRAPHICS_API_OPENGL */

#ifdef XR_USE_GRAPHICS_API_OPENGL_ES

// XR_KHR_opengl_es_enable is a preprocessor guard. Do not pass it to API calls.
#define XR_KHR_opengl_es_enable 1
#define XR_KHR_opengl_es_enable_SPEC_VERSION 10
#define XR_KHR_OPENGL_ES_ENABLE_EXTENSION_NAME "XR_KHR_opengl_es_enable"
#ifdef XR_USE_PLATFORM_ANDROID
// XrGraphicsBindingOpenGLESAndroidKHR extends XrSessionCreateInfo
પ્રકારવ્યાખ્યા સંરચના XrGraphicsBindingOpenGLESAndroidKHR {
    XrStructureType             type;
    અચલ શૂન્ય* XR_MAY_ALIAS    next;
    EGLDisplay                  display;
    EGLConfig                   config;
    EGLContext                  context;
} XrGraphicsBindingOpenGLESAndroidKHR;
#endif // XR_USE_PLATFORM_ANDROID

પ્રકારવ્યાખ્યા સંરચના XrSwapchainImageOpenGLESKHR {
    XrStructureType       type;
    શૂન્ય* XR_MAY_ALIAS    next;
    uint32_t              image;
} XrSwapchainImageOpenGLESKHR;

પ્રકારવ્યાખ્યા સંરચના XrGraphicsRequirementsOpenGLESKHR {
    XrStructureType       type;
    શૂન્ય* XR_MAY_ALIAS    next;
    XrVersion             minApiVersionSupported;
    XrVersion             maxApiVersionSupported;
} XrGraphicsRequirementsOpenGLESKHR;

પ્રકારવ્યાખ્યા XrResult (XRAPI_PTR *PFN_xrGetOpenGLESGraphicsRequirementsKHR)(XrInstance instance, XrSystemId systemId, XrGraphicsRequirementsOpenGLESKHR* graphicsRequirements);

#ifndef XR_NO_PROTOTYPES
#ifdef XR_EXTENSION_PROTOTYPES
XRAPI_ATTR XrResult XRAPI_CALL xrGetOpenGLESGraphicsRequirementsKHR(
    XrInstance                                  instance,
    XrSystemId                                  systemId,
    XrGraphicsRequirementsOpenGLESKHR*          graphicsRequirements);
#endif /* XR_EXTENSION_PROTOTYPES */
#endif /* !XR_NO_PROTOTYPES */
#endif /* XR_USE_GRAPHICS_API_OPENGL_ES */

#ifdef XR_USE_GRAPHICS_API_VULKAN

// XR_KHR_vulkan_enable is a preprocessor guard. Do not pass it to API calls.
#define XR_KHR_vulkan_enable 1
#define XR_KHR_vulkan_enable_SPEC_VERSION 10
#define XR_KHR_VULKAN_ENABLE_EXTENSION_NAME "XR_KHR_vulkan_enable"
// XrGraphicsBindingVulkanKHR extends XrSessionCreateInfo
પ્રકારવ્યાખ્યા સંરચના XrGraphicsBindingVulkanKHR {
    XrStructureType             type;
    અચલ શૂન્ય* XR_MAY_ALIAS    next;
    VkInstance                  instance;
    VkPhysicalDevice            physicalDevice;
    VkDevice                    device;
    uint32_t                    queueFamilyIndex;
    uint32_t                    queueIndex;
} XrGraphicsBindingVulkanKHR;

પ્રકારવ્યાખ્યા સંરચના XrSwapchainImageVulkanKHR {
    XrStructureType       type;
    શૂન્ય* XR_MAY_ALIAS    next;
    VkImage               image;
} XrSwapchainImageVulkanKHR;

પ્રકારવ્યાખ્યા સંરચના XrGraphicsRequirementsVulkanKHR {
    XrStructureType       type;
    શૂન્ય* XR_MAY_ALIAS    next;
    XrVersion             minApiVersionSupported;
    XrVersion             maxApiVersionSupported;
} XrGraphicsRequirementsVulkanKHR;

પ્રકારવ્યાખ્યા XrResult (XRAPI_PTR *PFN_xrGetVulkanInstanceExtensionsKHR)(XrInstance instance, XrSystemId systemId, uint32_t buffer_Capacity_આગત, uint32_t* buffer_ગણતરી_Output, અક્ષર* buffer);
પ્રકારવ્યાખ્યા XrResult (XRAPI_PTR *PFN_xrGetVulkanDeviceExtensionsKHR)(XrInstance instance, XrSystemId systemId, uint32_t buffer_Capacity_આગત, uint32_t* buffer_ગણતરી_Output, અક્ષર* buffer);
પ્રકારવ્યાખ્યા XrResult (XRAPI_PTR *PFN_xrGetVulkanGraphicsDeviceKHR)(XrInstance instance, XrSystemId systemId, VkInstance vkInstance, VkPhysicalDevice* vkPhysicalDevice);
પ્રકારવ્યાખ્યા XrResult (XRAPI_PTR *PFN_xrGetVulkanGraphicsRequirementsKHR)(XrInstance instance, XrSystemId systemId, XrGraphicsRequirementsVulkanKHR* graphicsRequirements);

#ifndef XR_NO_PROTOTYPES
#ifdef XR_EXTENSION_PROTOTYPES
XRAPI_ATTR XrResult XRAPI_CALL xrGetVulkanInstanceExtensionsKHR(
    XrInstance                                  instance,
    XrSystemId                                  systemId,
    uint32_t                                    buffer_Capacity_આગત,
    uint32_t*                                   buffer_ગણતરી_Output,
    અક્ષર*                                       buffer);

XRAPI_ATTR XrResult XRAPI_CALL xrGetVulkanDeviceExtensionsKHR(
    XrInstance                                  instance,
    XrSystemId                                  systemId,
    uint32_t                                    buffer_Capacity_આગત,
    uint32_t*                                   buffer_ગણતરી_Output,
    અક્ષર*                                       buffer);

XRAPI_ATTR XrResult XRAPI_CALL xrGetVulkanGraphicsDeviceKHR(
    XrInstance                                  instance,
    XrSystemId                                  systemId,
    VkInstance                                  vkInstance,
    VkPhysicalDevice*                           vkPhysicalDevice);

XRAPI_ATTR XrResult XRAPI_CALL xrGetVulkanGraphicsRequirementsKHR(
    XrInstance                                  instance,
    XrSystemId                                  systemId,
    XrGraphicsRequirementsVulkanKHR*            graphicsRequirements);
#endif /* XR_EXTENSION_PROTOTYPES */
#endif /* !XR_NO_PROTOTYPES */
#endif /* XR_USE_GRAPHICS_API_VULKAN */

#ifdef XR_USE_GRAPHICS_API_D3D11

// XR_KHR_D3D11_enable is a preprocessor guard. Do not pass it to API calls.
#define XR_KHR_D3D11_enable 1
#define XR_KHR_D3D11_enable_SPEC_VERSION  11
#define XR_KHR_D3D11_ENABLE_EXTENSION_NAME "XR_KHR_D3D11_enable"
// XrGraphicsBindingD3D11KHR extends XrSessionCreateInfo
પ્રકારવ્યાખ્યા સંરચના XrGraphicsBindingD3D11KHR {
    XrStructureType             type;
    અચલ શૂન્ય* XR_MAY_ALIAS    next;
    ID3D11Device*               device;
} XrGraphicsBindingD3D11KHR;

પ્રકારવ્યાખ્યા સંરચના XrSwapchainImageD3D11KHR {
     XrStructureType      type;
    શૂન્ય* XR_MAY_ALIAS    next;
    ID3D11Texture2D*      texture;
} XrSwapchainImageD3D11KHR;

પ્રકારવ્યાખ્યા સંરચના XrGraphicsRequirementsD3D11KHR {
    XrStructureType       type;
    શૂન્ય* XR_MAY_ALIAS    next;
    LUID                  adapterLuid;
    D3D_FEATURE_LEVEL     minFeatureLevel;
} XrGraphicsRequirementsD3D11KHR;

પ્રકારવ્યાખ્યા XrResult (XRAPI_PTR *PFN_xrGetD3D11GraphicsRequirementsKHR)(XrInstance instance, XrSystemId systemId, XrGraphicsRequirementsD3D11KHR* graphicsRequirements);

#ifndef XR_NO_PROTOTYPES
#ifdef XR_EXTENSION_PROTOTYPES
XRAPI_ATTR XrResult XRAPI_CALL xrGetD3D11GraphicsRequirementsKHR(
    XrInstance                                  instance,
    XrSystemId                                  systemId,
    XrGraphicsRequirementsD3D11KHR*             graphicsRequirements);
#endif /* XR_EXTENSION_PROTOTYPES */
#endif /* !XR_NO_PROTOTYPES */
#endif /* XR_USE_GRAPHICS_API_D3D11 */

#ifdef XR_USE_GRAPHICS_API_D3D12

// XR_KHR_D3D12_enable is a preprocessor guard. Do not pass it to API calls.
#define XR_KHR_D3D12_enable 1
#define XR_KHR_D3D12_enable_SPEC_VERSION  11
#define XR_KHR_D3D12_ENABLE_EXTENSION_NAME "XR_KHR_D3D12_enable"
// XrGraphicsBindingD3D12KHR extends XrSessionCreateInfo
પ્રકારવ્યાખ્યા સંરચના XrGraphicsBindingD3D12KHR {
    XrStructureType             type;
    અચલ શૂન્ય* XR_MAY_ALIAS    next;
    ID3D12Device*               device;
    ID3D12CommandQueue*         queue;
} XrGraphicsBindingD3D12KHR;

પ્રકારવ્યાખ્યા સંરચના XrSwapchainImageD3D12KHR {
     XrStructureType      type;
    શૂન્ય* XR_MAY_ALIAS    next;
    ID3D12Resource*       texture;
} XrSwapchainImageD3D12KHR;

પ્રકારવ્યાખ્યા સંરચના XrGraphicsRequirementsD3D12KHR {
    XrStructureType       type;
    શૂન્ય* XR_MAY_ALIAS    next;
    LUID                  adapterLuid;
    D3D_FEATURE_LEVEL     minFeatureLevel;
} XrGraphicsRequirementsD3D12KHR;

પ્રકારવ્યાખ્યા XrResult (XRAPI_PTR *PFN_xrGetD3D12GraphicsRequirementsKHR)(XrInstance instance, XrSystemId systemId, XrGraphicsRequirementsD3D12KHR* graphicsRequirements);

#ifndef XR_NO_PROTOTYPES
#ifdef XR_EXTENSION_PROTOTYPES
XRAPI_ATTR XrResult XRAPI_CALL xrGetD3D12GraphicsRequirementsKHR(
    XrInstance                                  instance,
    XrSystemId                                  systemId,
    XrGraphicsRequirementsD3D12KHR*             graphicsRequirements);
#endif /* XR_EXTENSION_PROTOTYPES */
#endif /* !XR_NO_PROTOTYPES */
#endif /* XR_USE_GRAPHICS_API_D3D12 */

#ifdef XR_USE_GRAPHICS_API_METAL

// XR_KHR_metal_enable is a preprocessor guard. Do not pass it to API calls.
#define XR_KHR_metal_enable 1
#define XR_KHR_metal_enable_SPEC_VERSION  3
#define XR_KHR_METAL_ENABLE_EXTENSION_NAME "XR_KHR_metal_enable"
// XrGraphicsBindingMetalKHR extends XrSessionCreateInfo
પ્રકારવ્યાખ્યા સંરચના XrGraphicsBindingMetalKHR {
    XrStructureType             type;
    અચલ શૂન્ય* XR_MAY_ALIAS    next;
    શૂન્ય* XR_MAY_ALIAS          commandQueue;
} XrGraphicsBindingMetalKHR;

પ્રકારવ્યાખ્યા સંરચના XrSwapchainImageMetalKHR {
    XrStructureType       type;
    શૂન્ય* XR_MAY_ALIAS    next;
    શૂન્ય* XR_MAY_ALIAS    texture;
} XrSwapchainImageMetalKHR;

પ્રકારવ્યાખ્યા સંરચના XrGraphicsRequirementsMetalKHR {
    XrStructureType       type;
    શૂન્ય* XR_MAY_ALIAS    next;
    શૂન્ય* XR_MAY_ALIAS    metalDevice;
} XrGraphicsRequirementsMetalKHR;

પ્રકારવ્યાખ્યા XrResult (XRAPI_PTR *PFN_xrGetMetalGraphicsRequirementsKHR)(XrInstance instance, XrSystemId systemId, XrGraphicsRequirementsMetalKHR* graphicsRequirements);

#ifndef XR_NO_PROTOTYPES
#ifdef XR_EXTENSION_PROTOTYPES
XRAPI_ATTR XrResult XRAPI_CALL xrGetMetalGraphicsRequirementsKHR(
    XrInstance                                  instance,
    XrSystemId                                  systemId,
    XrGraphicsRequirementsMetalKHR*             graphicsRequirements);
#endif /* XR_EXTENSION_PROTOTYPES */
#endif /* !XR_NO_PROTOTYPES */
#endif /* XR_USE_GRAPHICS_API_METAL */

#ifdef XR_USE_PLATFORM_WIN32

// XR_KHR_win32_convert_performance_counter_time is a preprocessor guard. Do not pass it to API calls.
#define XR_KHR_win32_convert_performance_counter_time 1
#define XR_KHR_win32_convert_performance_counter_time_SPEC_VERSION 1
#define XR_KHR_WIN32_CONVERT_PERFORMANCE_COUNTER_TIME_EXTENSION_NAME "XR_KHR_win32_convert_performance_counter_time"
પ્રકારવ્યાખ્યા XrResult (XRAPI_PTR *PFN_xrConvertWin32PerformanceCounterToTimeKHR)(XrInstance instance, અચલ LARGE_INTEGER* performanceCounter, XrTime* time);
પ્રકારવ્યાખ્યા XrResult (XRAPI_PTR *PFN_xrConvertTimeToWin32PerformanceCounterKHR)(XrInstance instance, XrTime time, LARGE_INTEGER* performanceCounter);

#ifndef XR_NO_PROTOTYPES
#ifdef XR_EXTENSION_PROTOTYPES
XRAPI_ATTR XrResult XRAPI_CALL xrConvertWin32PerformanceCounterToTimeKHR(
    XrInstance                                  instance,
    અચલ LARGE_INTEGER*                        performanceCounter,
    XrTime*                                     time);

XRAPI_ATTR XrResult XRAPI_CALL xrConvertTimeToWin32PerformanceCounterKHR(
    XrInstance                                  instance,
    XrTime                                      time,
    LARGE_INTEGER*                              performanceCounter);
#endif /* XR_EXTENSION_PROTOTYPES */
#endif /* !XR_NO_PROTOTYPES */
#endif /* XR_USE_PLATFORM_WIN32 */

#ifdef XR_USE_TIMESPEC

// XR_KHR_convert_timespec_time is a preprocessor guard. Do not pass it to API calls.
#define XR_KHR_convert_timespec_time 1
#define XR_KHR_convert_timespec_time_SPEC_VERSION 1
#define XR_KHR_CONVERT_TIMESPEC_TIME_EXTENSION_NAME "XR_KHR_convert_timespec_time"
પ્રકારવ્યાખ્યા XrResult (XRAPI_PTR *PFN_xrConvertTimespecTimeToTimeKHR)(XrInstance instance, અચલ સંરચના timespec* timespecTime, XrTime* time);
પ્રકારવ્યાખ્યા XrResult (XRAPI_PTR *PFN_xrConvertTimeToTimespecTimeKHR)(XrInstance instance, XrTime time, સંરચના timespec* timespecTime);

#ifndef XR_NO_PROTOTYPES
#ifdef XR_EXTENSION_PROTOTYPES
XRAPI_ATTR XrResult XRAPI_CALL xrConvertTimespecTimeToTimeKHR(
    XrInstance                                  instance,
    અચલ સંરચના timespec*                      timespecTime,
    XrTime*                                     time);

XRAPI_ATTR XrResult XRAPI_CALL xrConvertTimeToTimespecTimeKHR(
    XrInstance                                  instance,
    XrTime                                      time,
    સંરચના timespec*                            timespecTime);
#endif /* XR_EXTENSION_PROTOTYPES */
#endif /* !XR_NO_PROTOTYPES */
#endif /* XR_USE_TIMESPEC */

#ifdef XR_USE_PLATFORM_ANDROID

// XR_KHR_loader_init_android is a preprocessor guard. Do not pass it to API calls.
#define XR_KHR_loader_init_android 1
#define XR_KHR_loader_init_android_SPEC_VERSION 1
#define XR_KHR_LOADER_INIT_ANDROID_EXTENSION_NAME "XR_KHR_loader_init_android"
પ્રકારવ્યાખ્યા સંરચના XrLoaderInitInfoAndroidKHR {
    XrStructureType             type;
    અચલ શૂન્ય* XR_MAY_ALIAS    next;
    શૂન્ય* XR_MAY_ALIAS          applicationVM;
    શૂન્ય* XR_MAY_ALIAS          applicationContext;
} XrLoaderInitInfoAndroidKHR;

#endif /* XR_USE_PLATFORM_ANDROID */

#ifdef XR_USE_GRAPHICS_API_VULKAN

// XR_KHR_vulkan_enable2 is a preprocessor guard. Do not pass it to API calls.
#define XR_KHR_vulkan_enable2 1
#define XR_KHR_vulkan_enable2_SPEC_VERSION 4
#define XR_KHR_VULKAN_ENABLE2_EXTENSION_NAME "XR_KHR_vulkan_enable2"
પ્રકારવ્યાખ્યા XrFlags64 XrVulkanInstanceCreateFlagsKHR;

// Flag bits for XrVulkanInstanceCreateFlagsKHR

પ્રકારવ્યાખ્યા XrFlags64 XrVulkanDeviceCreateFlagsKHR;

// Flag bits for XrVulkanDeviceCreateFlagsKHR

પ્રકારવ્યાખ્યા સંરચના XrVulkanInstanceCreateInfoKHR {
    XrStructureType                   type;
    અચલ શૂન્ય* XR_MAY_ALIAS          next;
    XrSystemId                        systemId;
    XrVulkanInstanceCreateFlagsKHR    createFlags;
    PFN_vkGetInstanceProcAddr         pfnGetInstanceProcAddr;
    અચલ VkInstanceCreateInfo*       vulkanCreateInfo;
    અચલ VkAllocationCallbacks*      vulkanAllocator;
} XrVulkanInstanceCreateInfoKHR;

પ્રકારવ્યાખ્યા સંરચના XrVulkanDeviceCreateInfoKHR {
    XrStructureType                 type;
    અચલ શૂન્ય* XR_MAY_ALIAS        next;
    XrSystemId                      systemId;
    XrVulkanDeviceCreateFlagsKHR    createFlags;
    PFN_vkGetInstanceProcAddr       pfnGetInstanceProcAddr;
    VkPhysicalDevice                vulkanPhysicalDevice;
    અચલ VkDeviceCreateInfo*       vulkanCreateInfo;
    અચલ VkAllocationCallbacks*    vulkanAllocator;
} XrVulkanDeviceCreateInfoKHR;

પ્રકારવ્યાખ્યા XrGraphicsBindingVulkanKHR XrGraphicsBindingVulkan2KHR;

પ્રકારવ્યાખ્યા સંરચના XrVulkanGraphicsDeviceGetInfoKHR {
    XrStructureType             type;
    અચલ શૂન્ય* XR_MAY_ALIAS    next;
    XrSystemId                  systemId;
    VkInstance                  vulkanInstance;
} XrVulkanGraphicsDeviceGetInfoKHR;

પ્રકારવ્યાખ્યા XrSwapchainImageVulkanKHR XrSwapchainImageVulkan2KHR;

પ્રકારવ્યાખ્યા XrGraphicsRequirementsVulkanKHR XrGraphicsRequirementsVulkan2KHR;

પ્રકારવ્યાખ્યા XrResult (XRAPI_PTR *PFN_xrCreateVulkanInstanceKHR)(XrInstance instance, અચલ XrVulkanInstanceCreateInfoKHR* createInfo, VkInstance* vulkanInstance, VkResult* vulkanResult);
પ્રકારવ્યાખ્યા XrResult (XRAPI_PTR *PFN_xrCreateVulkanDeviceKHR)(XrInstance instance, અચલ XrVulkanDeviceCreateInfoKHR* createInfo, VkDevice* vulkanDevice, VkResult* vulkanResult);
પ્રકારવ્યાખ્યા XrResult (XRAPI_PTR *PFN_xrGetVulkanGraphicsDevice2KHR)(XrInstance instance, અચલ XrVulkanGraphicsDeviceGetInfoKHR* getInfo, VkPhysicalDevice* vulkanPhysicalDevice);
પ્રકારવ્યાખ્યા XrResult (XRAPI_PTR *PFN_xrGetVulkanGraphicsRequirements2KHR)(XrInstance instance, XrSystemId systemId, XrGraphicsRequirementsVulkanKHR* graphicsRequirements);

#ifndef XR_NO_PROTOTYPES
#ifdef XR_EXTENSION_PROTOTYPES
XRAPI_ATTR XrResult XRAPI_CALL xrCreateVulkanInstanceKHR(
    XrInstance                                  instance,
    અચલ XrVulkanInstanceCreateInfoKHR*        createInfo,
    VkInstance*                                 vulkanInstance,
    VkResult*                                   vulkanResult);

XRAPI_ATTR XrResult XRAPI_CALL xrCreateVulkanDeviceKHR(
    XrInstance                                  instance,
    અચલ XrVulkanDeviceCreateInfoKHR*          createInfo,
    VkDevice*                                   vulkanDevice,
    VkResult*                                   vulkanResult);

XRAPI_ATTR XrResult XRAPI_CALL xrGetVulkanGraphicsDevice2KHR(
    XrInstance                                  instance,
    અચલ XrVulkanGraphicsDeviceGetInfoKHR*     getInfo,
    VkPhysicalDevice*                           vulkanPhysicalDevice);

XRAPI_ATTR XrResult XRAPI_CALL xrGetVulkanGraphicsRequirements2KHR(
    XrInstance                                  instance,
    XrSystemId                                  systemId,
    XrGraphicsRequirementsVulkanKHR*            graphicsRequirements);
#endif /* XR_EXTENSION_PROTOTYPES */
#endif /* !XR_NO_PROTOTYPES */
#endif /* XR_USE_GRAPHICS_API_VULKAN */

#ifdef XR_USE_PLATFORM_EGL

// XR_MNDX_egl_enable is a preprocessor guard. Do not pass it to API calls.
#define XR_MNDX_egl_enable 1
#define XR_MNDX_egl_enable_SPEC_VERSION   2
#define XR_MNDX_EGL_ENABLE_EXTENSION_NAME "XR_MNDX_egl_enable"
પ્રકારવ્યાખ્યા PFN_xrVoidFunction (*PFN_xrEglGetProcAddressMNDX)(અચલ અક્ષર *name);
// XrGraphicsBindingEGLMNDX extends XrSessionCreateInfo
પ્રકારવ્યાખ્યા સંરચના XrGraphicsBindingEGLMNDX {
    XrStructureType                type;
    અચલ શૂન્ય* XR_MAY_ALIAS       next;
    PFN_xrEglGetProcAddressMNDX    getProcAddress;
    EGLDisplay                     display;
    EGLConfig                      config;
    EGLContext                     context;
} XrGraphicsBindingEGLMNDX;

#endif /* XR_USE_PLATFORM_EGL */

#ifdef XR_USE_PLATFORM_WIN32

// XR_MSFT_perception_anchor_interop is a preprocessor guard. Do not pass it to API calls.
#define XR_MSFT_perception_anchor_interop 1
#define XR_MSFT_perception_anchor_interop_SPEC_VERSION 1
#define XR_MSFT_PERCEPTION_ANCHOR_INTEROP_EXTENSION_NAME "XR_MSFT_perception_anchor_interop"
પ્રકારવ્યાખ્યા XrResult (XRAPI_PTR *PFN_xrCreateSpatialAnchorFromPerceptionAnchorMSFT)(XrSession session, IUnknown* perceptionAnchor, XrSpatialAnchorMSFT* anchor);
પ્રકારવ્યાખ્યા XrResult (XRAPI_PTR *PFN_xrTryGetPerceptionAnchorFromSpatialAnchorMSFT)(XrSession session, XrSpatialAnchorMSFT anchor, IUnknown** perceptionAnchor);

#ifndef XR_NO_PROTOTYPES
#ifdef XR_EXTENSION_PROTOTYPES
XRAPI_ATTR XrResult XRAPI_CALL xrCreateSpatialAnchorFromPerceptionAnchorMSFT(
    XrSession                                   session,
    IUnknown*                                   perceptionAnchor,
    XrSpatialAnchorMSFT*                        anchor);

XRAPI_ATTR XrResult XRAPI_CALL xrTryGetPerceptionAnchorFromSpatialAnchorMSFT(
    XrSession                                   session,
    XrSpatialAnchorMSFT                         anchor,
    IUnknown**                                  perceptionAnchor);
#endif /* XR_EXTENSION_PROTOTYPES */
#endif /* !XR_NO_PROTOTYPES */
#endif /* XR_USE_PLATFORM_WIN32 */

#ifdef XR_USE_PLATFORM_WIN32

// XR_MSFT_holographic_window_attachment is a preprocessor guard. Do not pass it to API calls.
#define XR_MSFT_holographic_window_attachment 1
#define XR_MSFT_holographic_window_attachment_SPEC_VERSION 1
#define XR_MSFT_HOLOGRAPHIC_WINDOW_ATTACHMENT_EXTENSION_NAME "XR_MSFT_holographic_window_attachment"
#ifdef XR_USE_PLATFORM_WIN32
// XrHolographicWindowAttachmentMSFT extends XrSessionCreateInfo
પ્રકારવ્યાખ્યા સંરચના XrHolographicWindowAttachmentMSFT {
    XrStructureType             type;
    અચલ શૂન્ય* XR_MAY_ALIAS    next;
    IUnknown*                   holographicSpace;
    IUnknown*                   coreWindow;
} XrHolographicWindowAttachmentMSFT;
#endif // XR_USE_PLATFORM_WIN32

#endif /* XR_USE_PLATFORM_WIN32 */

#ifdef XR_USE_PLATFORM_ANDROID

// XR_FB_android_surface_swapchain_create is a preprocessor guard. Do not pass it to API calls.
#define XR_FB_android_surface_swapchain_create 1
#define XR_FB_android_surface_swapchain_create_SPEC_VERSION 1
#define XR_FB_ANDROID_SURFACE_SWAPCHAIN_CREATE_EXTENSION_NAME "XR_FB_android_surface_swapchain_create"
પ્રકારવ્યાખ્યા XrFlags64 XrAndroidSurfaceSwapchainFlagsFB;

// Flag bits for XrAndroidSurfaceSwapchainFlagsFB
સ્થિર અચલ XrAndroidSurfaceSwapchainFlagsFB XR_ANDROID_SURFACE_SWAPCHAIN_SYNCHRONOUS_BIT_FB = 0x00000001;
સ્થિર અચલ XrAndroidSurfaceSwapchainFlagsFB XR_ANDROID_SURFACE_SWAPCHAIN_USE_TIMESTAMPS_BIT_FB = 0x00000002;

#ifdef XR_USE_PLATFORM_ANDROID
// XrAndroidSurfaceSwapchainCreateInfoFB extends XrSwapchainCreateInfo
પ્રકારવ્યાખ્યા સંરચના XrAndroidSurfaceSwapchainCreateInfoFB {
    XrStructureType                     type;
    અચલ શૂન્ય* XR_MAY_ALIAS            next;
    XrAndroidSurfaceSwapchainFlagsFB    createFlags;
} XrAndroidSurfaceSwapchainCreateInfoFB;
#endif // XR_USE_PLATFORM_ANDROID

#endif /* XR_USE_PLATFORM_ANDROID */

#ifdef XR_USE_PLATFORM_ML

// XR_ML_compat is a preprocessor guard. Do not pass it to API calls.
#define XR_ML_compat 1
#define XR_ML_compat_SPEC_VERSION         1
#define XR_ML_COMPAT_EXTENSION_NAME       "XR_ML_compat"
પ્રકારવ્યાખ્યા સંરચના XrCoordinateSpaceCreateInfoML {
    XrStructureType             type;
    અચલ શૂન્ય* XR_MAY_ALIAS    next;
    MLCoordinateFrameUID        cfuid;
    XrPosef                     poseInCoordinateSpace;
} XrCoordinateSpaceCreateInfoML;

પ્રકારવ્યાખ્યા XrResult (XRAPI_PTR *PFN_xrCreateSpaceFromCoordinateFrameUIDML)(XrSession session, અચલ XrCoordinateSpaceCreateInfoML *createInfo, XrSpace* space);

#ifndef XR_NO_PROTOTYPES
#ifdef XR_EXTENSION_PROTOTYPES
XRAPI_ATTR XrResult XRAPI_CALL xrCreateSpaceFromCoordinateFrameUIDML(
    XrSession                                   session,
    અચલ XrCoordinateSpaceCreateInfoML *       createInfo,
    XrSpace*                                    space);
#endif /* XR_EXTENSION_PROTOTYPES */
#endif /* !XR_NO_PROTOTYPES */
#endif /* XR_USE_PLATFORM_ML */

#ifdef XR_USE_PLATFORM_WIN32

// XR_OCULUS_audio_device_guid is a preprocessor guard. Do not pass it to API calls.
#define XR_OCULUS_audio_device_guid 1
#define XR_OCULUS_audio_device_guid_SPEC_VERSION 1
#define XR_OCULUS_AUDIO_DEVICE_GUID_EXTENSION_NAME "XR_OCULUS_audio_device_guid"
#define XR_MAX_AUDIO_DEVICE_STR_SIZE_OCULUS 128
પ્રકારવ્યાખ્યા XrResult (XRAPI_PTR *PFN_xrGetAudioOutputDeviceGuidOculus)(XrInstance instance, wchar_t buffer[XR_MAX_AUDIO_DEVICE_STR_SIZE_OCULUS]);
પ્રકારવ્યાખ્યા XrResult (XRAPI_PTR *PFN_xr_Get_Audio_આગત_Device_Guid_Oculus)(XrInstance instance, wchar_t buffer[XR_MAX_AUDIO_DEVICE_STR_SIZE_OCULUS]);

#ifndef XR_NO_PROTOTYPES
#ifdef XR_EXTENSION_PROTOTYPES
XRAPI_ATTR XrResult XRAPI_CALL xrGetAudioOutputDeviceGuidOculus(
    XrInstance                                  instance,
    wchar_t                                     buffer[XR_MAX_AUDIO_DEVICE_STR_SIZE_OCULUS]);

XRAPI_ATTR XrResult XRAPI_CALL xr_Get_Audio_આગત_Device_Guid_Oculus(
    XrInstance                                  instance,
    wchar_t                                     buffer[XR_MAX_AUDIO_DEVICE_STR_SIZE_OCULUS]);
#endif /* XR_EXTENSION_PROTOTYPES */
#endif /* !XR_NO_PROTOTYPES */
#endif /* XR_USE_PLATFORM_WIN32 */

#ifdef XR_USE_GRAPHICS_API_VULKAN

// XR_FB_foveation_vulkan is a preprocessor guard. Do not pass it to API calls.
#define XR_FB_foveation_vulkan 1
#define XR_FB_foveation_vulkan_SPEC_VERSION 1
#define XR_FB_FOVEATION_VULKAN_EXTENSION_NAME "XR_FB_foveation_vulkan"
// XrSwapchainImageFoveationVulkanFB extends XrSwapchainImageVulkanKHR
પ્રકારવ્યાખ્યા સંરચના XrSwapchainImageFoveationVulkanFB {
    XrStructureType       type;
    શૂન્ય* XR_MAY_ALIAS    next;
    VkImage               image;
    uint32_t              width;
    uint32_t              height;
} XrSwapchainImageFoveationVulkanFB;

#endif /* XR_USE_GRAPHICS_API_VULKAN */

#ifdef XR_USE_PLATFORM_ANDROID

// XR_FB_swapchain_update_state_android_surface is a preprocessor guard. Do not pass it to API calls.
#define XR_FB_swapchain_update_state_android_surface 1
#define XR_FB_swapchain_update_state_android_surface_SPEC_VERSION 1
#define XR_FB_SWAPCHAIN_UPDATE_STATE_ANDROID_SURFACE_EXTENSION_NAME "XR_FB_swapchain_update_state_android_surface"
#ifdef XR_USE_PLATFORM_ANDROID
પ્રકારવ્યાખ્યા સંરચના XrSwapchainStateAndroidSurfaceDimensionsFB {
    XrStructureType       type;
    શૂન્ય* XR_MAY_ALIAS    next;
    uint32_t              width;
    uint32_t              height;
} XrSwapchainStateAndroidSurfaceDimensionsFB;
#endif // XR_USE_PLATFORM_ANDROID

#endif /* XR_USE_PLATFORM_ANDROID */

#ifdef XR_USE_GRAPHICS_API_OPENGL_ES

// XR_FB_swapchain_update_state_opengl_es is a preprocessor guard. Do not pass it to API calls.
#define XR_FB_swapchain_update_state_opengl_es 1
#define XR_FB_swapchain_update_state_opengl_es_SPEC_VERSION 1
#define XR_FB_SWAPCHAIN_UPDATE_STATE_OPENGL_ES_EXTENSION_NAME "XR_FB_swapchain_update_state_opengl_es"
#ifdef XR_USE_GRAPHICS_API_OPENGL_ES
પ્રકારવ્યાખ્યા સંરચના XrSwapchainStateSamplerOpenGLESFB {
    XrStructureType       type;
    શૂન્ય* XR_MAY_ALIAS    next;
    EGLenum               minFilter;
    EGLenum               magFilter;
    EGLenum               wrapModeS;
    EGLenum               wrapModeT;
    EGLenum               swizzleRed;
    EGLenum               swizzleGreen;
    EGLenum               swizzleBlue;
    EGLenum               swizzleAlpha;
    દશાંશ                 maxAnisotropy;
    XrColor4f             borderColor;
} XrSwapchainStateSamplerOpenGLESFB;
#endif // XR_USE_GRAPHICS_API_OPENGL_ES

#endif /* XR_USE_GRAPHICS_API_OPENGL_ES */

#ifdef XR_USE_GRAPHICS_API_VULKAN

// XR_FB_swapchain_update_state_vulkan is a preprocessor guard. Do not pass it to API calls.
#define XR_FB_swapchain_update_state_vulkan 1
#define XR_FB_swapchain_update_state_vulkan_SPEC_VERSION 1
#define XR_FB_SWAPCHAIN_UPDATE_STATE_VULKAN_EXTENSION_NAME "XR_FB_swapchain_update_state_vulkan"
#ifdef XR_USE_GRAPHICS_API_VULKAN
પ્રકારવ્યાખ્યા સંરચના XrSwapchainStateSamplerVulkanFB {
    XrStructureType         type;
    શૂન્ય* XR_MAY_ALIAS      next;
    VkFilter                minFilter;
    VkFilter                magFilter;
    VkSamplerMipmapMode     mipmapMode;
    VkSamplerAddressMode    wrapModeS;
    VkSamplerAddressMode    wrapModeT;
    VkComponentSwizzle      swizzleRed;
    VkComponentSwizzle      swizzleGreen;
    VkComponentSwizzle      swizzleBlue;
    VkComponentSwizzle      swizzleAlpha;
    દશાંશ                   maxAnisotropy;
    XrColor4f               borderColor;
} XrSwapchainStateSamplerVulkanFB;
#endif // XR_USE_GRAPHICS_API_VULKAN

#endif /* XR_USE_GRAPHICS_API_VULKAN */

#ifdef XR_USE_GRAPHICS_API_VULKAN

// XR_META_vulkan_swapchain_create_info is a preprocessor guard. Do not pass it to API calls.
#define XR_META_vulkan_swapchain_create_info 1
#define XR_META_vulkan_swapchain_create_info_SPEC_VERSION 1
#define XR_META_VULKAN_SWAPCHAIN_CREATE_INFO_EXTENSION_NAME "XR_META_vulkan_swapchain_create_info"
// XrVulkanSwapchainCreateInfoMETA extends XrSwapchainCreateInfo
પ્રકારવ્યાખ્યા સંરચના XrVulkanSwapchainCreateInfoMETA {
    XrStructureType             type;
    અચલ શૂન્ય* XR_MAY_ALIAS    next;
    VkImageCreateFlags          additionalCreateFlags;
    VkImageUsageFlags           additionalUsageFlags;
} XrVulkanSwapchainCreateInfoMETA;

#endif /* XR_USE_GRAPHICS_API_VULKAN */

#ifdef XR_USE_PLATFORM_ANDROID

// XR_ANDROID_anchor_sharing_export is a preprocessor guard. Do not pass it to API calls.
#define XR_ANDROID_anchor_sharing_export 1
#define XR_ANDROID_anchor_sharing_export_SPEC_VERSION 1
#define XR_ANDROID_ANCHOR_SHARING_EXPORT_EXTENSION_NAME "XR_ANDROID_anchor_sharing_export"
પ્રકારવ્યાખ્યા સંરચના XrAnchorSharingInfoANDROID {
    XrStructureType             type;
    અચલ શૂન્ય* XR_MAY_ALIAS    next;
    XrSpace                     anchor;
} XrAnchorSharingInfoANDROID;

પ્રકારવ્યાખ્યા સંરચના XrAnchorSharingTokenANDROID {
    XrStructureType       type;
    શૂન્ય* XR_MAY_ALIAS    next;
    સંરચના AIBinder*      token;
} XrAnchorSharingTokenANDROID;

// XrSystemAnchorSharingExportPropertiesANDROID extends XrSystemProperties
પ્રકારવ્યાખ્યા સંરચના XrSystemAnchorSharingExportPropertiesANDROID {
    XrStructureType       type;
    શૂન્ય* XR_MAY_ALIAS    next;
    XrBool32              supportsAnchorSharingExport;
} XrSystemAnchorSharingExportPropertiesANDROID;

પ્રકારવ્યાખ્યા XrResult (XRAPI_PTR *PFN_xrShareAnchorANDROID)(XrSession session, અચલ XrAnchorSharingInfoANDROID* sharingInfo, XrAnchorSharingTokenANDROID* anchorToken);
પ્રકારવ્યાખ્યા XrResult (XRAPI_PTR *PFN_xrUnshareAnchorANDROID)(XrSession session, XrSpace anchor);

#ifndef XR_NO_PROTOTYPES
#ifdef XR_EXTENSION_PROTOTYPES
XRAPI_ATTR XrResult XRAPI_CALL xrShareAnchorANDROID(
    XrSession                                   session,
    અચલ XrAnchorSharingInfoANDROID*           sharingInfo,
    XrAnchorSharingTokenANDROID*                anchorToken);

XRAPI_ATTR XrResult XRAPI_CALL xrUnshareAnchorANDROID(
    XrSession                                   session,
    XrSpace                                     anchor);
#endif /* XR_EXTENSION_PROTOTYPES */
#endif /* !XR_NO_PROTOTYPES */
#endif /* XR_USE_PLATFORM_ANDROID */

#ifdef __cplusplus
}
#endif

#endif
