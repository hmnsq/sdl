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

#ضمن "openxr.h"

#ifdef __cplusplus
خارجي "C" {
#endif


#ifdef XR_USE_PLATFORM_ANDROID

// XR_KHR_android_thread_settings is a preprocessor guard. Do not pass it to API calls.
#define XR_KHR_android_thread_settings 1
#define XR_KHR_android_thread_settings_SPEC_VERSION 6
#define XR_KHR_ANDROID_THREAD_SETTINGS_EXTENSION_NAME "XR_KHR_android_thread_settings"

تعريفنوع تعداد XrAndroidThreadTypeKHR {
    XR_ANDROID_THREAD_TYPE_APPLICATION_MAIN_KHR = 1,
    XR_ANDROID_THREAD_TYPE_APPLICATION_WORKER_KHR = 2,
    XR_ANDROID_THREAD_TYPE_RENDERER_MAIN_KHR = 3,
    XR_ANDROID_THREAD_TYPE_RENDERER_WORKER_KHR = 4,
    XR_ANDROID_THREAD_TYPE_MAX_ENUM_KHR = 0x7FFFFFFF
} XrAndroidThreadTypeKHR;
تعريفنوع XrResult (XRAPI_PTR *PFN_xrSetAndroidApplicationThreadKHR)(XrSession session, XrAndroidThreadTypeKHR threadType, uint32_t threadId);

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
تعريفنوع XrResult (XRAPI_PTR *PFN_xrCreateSwapchainAndroidSurfaceKHR)(XrSession session, ثابت XrSwapchainCreateInfo* info, XrSwapchain* swapchain, jobject* surface);

#ifndef XR_NO_PROTOTYPES
#ifdef XR_EXTENSION_PROTOTYPES
XRAPI_ATTR XrResult XRAPI_CALL xrCreateSwapchainAndroidSurfaceKHR(
    XrSession                                   session,
    ثابت XrSwapchainCreateInfo*                info,
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
تعريفنوع بنية XrInstanceCreateInfoAndroidKHR {
    XrStructureType             type;
    ثابت فراغ* XR_MAY_ALIAS    next;
    فراغ* XR_MAY_ALIAS          applicationVM;
    فراغ* XR_MAY_ALIAS          applicationActivity;
} XrInstanceCreateInfoAndroidKHR;

#endif /* XR_USE_PLATFORM_ANDROID */

#ifdef XR_USE_GRAPHICS_API_VULKAN

// XR_KHR_vulkan_swapchain_format_list is a preprocessor guard. Do not pass it to API calls.
#define XR_KHR_vulkan_swapchain_format_list 1
#define XR_KHR_vulkan_swapchain_format_list_SPEC_VERSION 5
#define XR_KHR_VULKAN_SWAPCHAIN_FORMAT_LIST_EXTENSION_NAME "XR_KHR_vulkan_swapchain_format_list"
// XrVulkanSwapchainFormatListCreateInfoKHR extends XrSwapchainCreateInfo
تعريفنوع بنية XrVulkanSwapchainFormatListCreateInfoKHR {
    XrStructureType             type;
    ثابت فراغ* XR_MAY_ALIAS    next;
    uint32_t                    view_Format_کيراءن;
    ثابت VkFormat*             viewFormats;
} XrVulkanSwapchainFormatListCreateInfoKHR;

#endif /* XR_USE_GRAPHICS_API_VULKAN */

#ifdef XR_USE_GRAPHICS_API_OPENGL

// XR_KHR_opengl_enable is a preprocessor guard. Do not pass it to API calls.
#define XR_KHR_opengl_enable 1
#define XR_KHR_opengl_enable_SPEC_VERSION 12
#define XR_KHR_OPENGL_ENABLE_EXTENSION_NAME "XR_KHR_opengl_enable"
#ifdef XR_USE_PLATFORM_WIN32
// XrGraphicsBindingOpenGLWin32KHR extends XrSessionCreateInfo
تعريفنوع بنية XrGraphicsBindingOpenGLWin32KHR {
    XrStructureType             type;
    ثابت فراغ* XR_MAY_ALIAS    next;
    HDC                         hDC;
    HGLRC                       hGLRC;
} XrGraphicsBindingOpenGLWin32KHR;
#endif // XR_USE_PLATFORM_WIN32

#ifdef XR_USE_PLATFORM_XLIB
// XrGraphicsBindingOpenGLXlibKHR extends XrSessionCreateInfo
تعريفنوع بنية XrGraphicsBindingOpenGLXlibKHR {
    XrStructureType             type;
    ثابت فراغ* XR_MAY_ALIAS    next;
    Display*                    xDisplay;
    uint32_t                    visualid;
    GLXFBConfig                 glxFBConfig;
    GLXDrawable                 glxDrawable;
    GLXContext                  glxContext;
} XrGraphicsBindingOpenGLXlibKHR;
#endif // XR_USE_PLATFORM_XLIB

#ifdef XR_USE_PLATFORM_XCB
// XrGraphicsBindingOpenGLXcbKHR extends XrSessionCreateInfo
تعريفنوع بنية XrGraphicsBindingOpenGLXcbKHR {
    XrStructureType             type;
    ثابت فراغ* XR_MAY_ALIAS    next;
    xcb_connection_t*           connection;
    uint32_t                    screen_نومبور;
    xcb_glx_fbconfig_t          fbconfigid;
    xcb_visualid_t              visualid;
    xcb_glx_drawable_t          glxDrawable;
    xcb_glx_context_t           glxContext;
} XrGraphicsBindingOpenGLXcbKHR;
#endif // XR_USE_PLATFORM_XCB

#ifdef XR_USE_PLATFORM_WAYLAND
// XrGraphicsBindingOpenGLWaylandKHR extends XrSessionCreateInfo
تعريفنوع بنية XrGraphicsBindingOpenGLWaylandKHR {
    XrStructureType             type;
    ثابت فراغ* XR_MAY_ALIAS    next;
    بنية wl_display*          display;
} XrGraphicsBindingOpenGLWaylandKHR;
#endif // XR_USE_PLATFORM_WAYLAND

تعريفنوع بنية XrSwapchainImageOpenGLKHR {
    XrStructureType       type;
    فراغ* XR_MAY_ALIAS    next;
    uint32_t              image;
} XrSwapchainImageOpenGLKHR;

تعريفنوع بنية XrGraphicsRequirementsOpenGLKHR {
    XrStructureType       type;
    فراغ* XR_MAY_ALIAS    next;
    XrVersion             minApiVersionSupported;
    XrVersion             maxApiVersionSupported;
} XrGraphicsRequirementsOpenGLKHR;

تعريفنوع XrResult (XRAPI_PTR *PFN_xrGetOpenGLGraphicsRequirementsKHR)(XrInstance instance, XrSystemId systemId, XrGraphicsRequirementsOpenGLKHR* graphicsRequirements);

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
تعريفنوع بنية XrGraphicsBindingOpenGLESAndroidKHR {
    XrStructureType             type;
    ثابت فراغ* XR_MAY_ALIAS    next;
    EGLDisplay                  display;
    EGLConfig                   config;
    EGLContext                  context;
} XrGraphicsBindingOpenGLESAndroidKHR;
#endif // XR_USE_PLATFORM_ANDROID

تعريفنوع بنية XrSwapchainImageOpenGLESKHR {
    XrStructureType       type;
    فراغ* XR_MAY_ALIAS    next;
    uint32_t              image;
} XrSwapchainImageOpenGLESKHR;

تعريفنوع بنية XrGraphicsRequirementsOpenGLESKHR {
    XrStructureType       type;
    فراغ* XR_MAY_ALIAS    next;
    XrVersion             minApiVersionSupported;
    XrVersion             maxApiVersionSupported;
} XrGraphicsRequirementsOpenGLESKHR;

تعريفنوع XrResult (XRAPI_PTR *PFN_xrGetOpenGLESGraphicsRequirementsKHR)(XrInstance instance, XrSystemId systemId, XrGraphicsRequirementsOpenGLESKHR* graphicsRequirements);

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
تعريفنوع بنية XrGraphicsBindingVulkanKHR {
    XrStructureType             type;
    ثابت فراغ* XR_MAY_ALIAS    next;
    VkInstance                  instance;
    VkPhysicalDevice            physicalDevice;
    VkDevice                    device;
    uint32_t                    queueFamilyIndex;
    uint32_t                    queueIndex;
} XrGraphicsBindingVulkanKHR;

تعريفنوع بنية XrSwapchainImageVulkanKHR {
    XrStructureType       type;
    فراغ* XR_MAY_ALIAS    next;
    VkImage               image;
} XrSwapchainImageVulkanKHR;

تعريفنوع بنية XrGraphicsRequirementsVulkanKHR {
    XrStructureType       type;
    فراغ* XR_MAY_ALIAS    next;
    XrVersion             minApiVersionSupported;
    XrVersion             maxApiVersionSupported;
} XrGraphicsRequirementsVulkanKHR;

تعريفنوع XrResult (XRAPI_PTR *PFN_xrGetVulkanInstanceExtensionsKHR)(XrInstance instance, XrSystemId systemId, uint32_t buffer_Capacity_ماسوقن, uint32_t* buffer_کيراءن_Output, حرف* buffer);
تعريفنوع XrResult (XRAPI_PTR *PFN_xrGetVulkanDeviceExtensionsKHR)(XrInstance instance, XrSystemId systemId, uint32_t buffer_Capacity_ماسوقن, uint32_t* buffer_کيراءن_Output, حرف* buffer);
تعريفنوع XrResult (XRAPI_PTR *PFN_xrGetVulkanGraphicsDeviceKHR)(XrInstance instance, XrSystemId systemId, VkInstance vkInstance, VkPhysicalDevice* vkPhysicalDevice);
تعريفنوع XrResult (XRAPI_PTR *PFN_xrGetVulkanGraphicsRequirementsKHR)(XrInstance instance, XrSystemId systemId, XrGraphicsRequirementsVulkanKHR* graphicsRequirements);

#ifndef XR_NO_PROTOTYPES
#ifdef XR_EXTENSION_PROTOTYPES
XRAPI_ATTR XrResult XRAPI_CALL xrGetVulkanInstanceExtensionsKHR(
    XrInstance                                  instance,
    XrSystemId                                  systemId,
    uint32_t                                    buffer_Capacity_ماسوقن,
    uint32_t*                                   buffer_کيراءن_Output,
    حرف*                                       buffer);

XRAPI_ATTR XrResult XRAPI_CALL xrGetVulkanDeviceExtensionsKHR(
    XrInstance                                  instance,
    XrSystemId                                  systemId,
    uint32_t                                    buffer_Capacity_ماسوقن,
    uint32_t*                                   buffer_کيراءن_Output,
    حرف*                                       buffer);

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
تعريفنوع بنية XrGraphicsBindingD3D11KHR {
    XrStructureType             type;
    ثابت فراغ* XR_MAY_ALIAS    next;
    ID3D11Device*               device;
} XrGraphicsBindingD3D11KHR;

تعريفنوع بنية XrSwapchainImageD3D11KHR {
     XrStructureType      type;
    فراغ* XR_MAY_ALIAS    next;
    ID3D11Texture2D*      texture;
} XrSwapchainImageD3D11KHR;

تعريفنوع بنية XrGraphicsRequirementsD3D11KHR {
    XrStructureType       type;
    فراغ* XR_MAY_ALIAS    next;
    LUID                  adapterLuid;
    D3D_FEATURE_LEVEL     minFeatureLevel;
} XrGraphicsRequirementsD3D11KHR;

تعريفنوع XrResult (XRAPI_PTR *PFN_xrGetD3D11GraphicsRequirementsKHR)(XrInstance instance, XrSystemId systemId, XrGraphicsRequirementsD3D11KHR* graphicsRequirements);

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
تعريفنوع بنية XrGraphicsBindingD3D12KHR {
    XrStructureType             type;
    ثابت فراغ* XR_MAY_ALIAS    next;
    ID3D12Device*               device;
    ID3D12CommandQueue*         queue;
} XrGraphicsBindingD3D12KHR;

تعريفنوع بنية XrSwapchainImageD3D12KHR {
     XrStructureType      type;
    فراغ* XR_MAY_ALIAS    next;
    ID3D12Resource*       texture;
} XrSwapchainImageD3D12KHR;

تعريفنوع بنية XrGraphicsRequirementsD3D12KHR {
    XrStructureType       type;
    فراغ* XR_MAY_ALIAS    next;
    LUID                  adapterLuid;
    D3D_FEATURE_LEVEL     minFeatureLevel;
} XrGraphicsRequirementsD3D12KHR;

تعريفنوع XrResult (XRAPI_PTR *PFN_xrGetD3D12GraphicsRequirementsKHR)(XrInstance instance, XrSystemId systemId, XrGraphicsRequirementsD3D12KHR* graphicsRequirements);

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
تعريفنوع بنية XrGraphicsBindingMetalKHR {
    XrStructureType             type;
    ثابت فراغ* XR_MAY_ALIAS    next;
    فراغ* XR_MAY_ALIAS          commandQueue;
} XrGraphicsBindingMetalKHR;

تعريفنوع بنية XrSwapchainImageMetalKHR {
    XrStructureType       type;
    فراغ* XR_MAY_ALIAS    next;
    فراغ* XR_MAY_ALIAS    texture;
} XrSwapchainImageMetalKHR;

تعريفنوع بنية XrGraphicsRequirementsMetalKHR {
    XrStructureType       type;
    فراغ* XR_MAY_ALIAS    next;
    فراغ* XR_MAY_ALIAS    metalDevice;
} XrGraphicsRequirementsMetalKHR;

تعريفنوع XrResult (XRAPI_PTR *PFN_xrGetMetalGraphicsRequirementsKHR)(XrInstance instance, XrSystemId systemId, XrGraphicsRequirementsMetalKHR* graphicsRequirements);

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
تعريفنوع XrResult (XRAPI_PTR *PFN_xrConvertWin32PerformanceCounterToTimeKHR)(XrInstance instance, ثابت LARGE_INTEGER* performanceCounter, XrTime* time);
تعريفنوع XrResult (XRAPI_PTR *PFN_xrConvertTimeToWin32PerformanceCounterKHR)(XrInstance instance, XrTime time, LARGE_INTEGER* performanceCounter);

#ifndef XR_NO_PROTOTYPES
#ifdef XR_EXTENSION_PROTOTYPES
XRAPI_ATTR XrResult XRAPI_CALL xrConvertWin32PerformanceCounterToTimeKHR(
    XrInstance                                  instance,
    ثابت LARGE_INTEGER*                        performanceCounter,
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
تعريفنوع XrResult (XRAPI_PTR *PFN_xrConvertTimespecTimeToTimeKHR)(XrInstance instance, ثابت بنية timespec* timespecTime, XrTime* time);
تعريفنوع XrResult (XRAPI_PTR *PFN_xrConvertTimeToTimespecTimeKHR)(XrInstance instance, XrTime time, بنية timespec* timespecTime);

#ifndef XR_NO_PROTOTYPES
#ifdef XR_EXTENSION_PROTOTYPES
XRAPI_ATTR XrResult XRAPI_CALL xrConvertTimespecTimeToTimeKHR(
    XrInstance                                  instance,
    ثابت بنية timespec*                      timespecTime,
    XrTime*                                     time);

XRAPI_ATTR XrResult XRAPI_CALL xrConvertTimeToTimespecTimeKHR(
    XrInstance                                  instance,
    XrTime                                      time,
    بنية timespec*                            timespecTime);
#endif /* XR_EXTENSION_PROTOTYPES */
#endif /* !XR_NO_PROTOTYPES */
#endif /* XR_USE_TIMESPEC */

#ifdef XR_USE_PLATFORM_ANDROID

// XR_KHR_loader_init_android is a preprocessor guard. Do not pass it to API calls.
#define XR_KHR_loader_init_android 1
#define XR_KHR_loader_init_android_SPEC_VERSION 1
#define XR_KHR_LOADER_INIT_ANDROID_EXTENSION_NAME "XR_KHR_loader_init_android"
تعريفنوع بنية XrLoaderInitInfoAndroidKHR {
    XrStructureType             type;
    ثابت فراغ* XR_MAY_ALIAS    next;
    فراغ* XR_MAY_ALIAS          applicationVM;
    فراغ* XR_MAY_ALIAS          applicationContext;
} XrLoaderInitInfoAndroidKHR;

#endif /* XR_USE_PLATFORM_ANDROID */

#ifdef XR_USE_GRAPHICS_API_VULKAN

// XR_KHR_vulkan_enable2 is a preprocessor guard. Do not pass it to API calls.
#define XR_KHR_vulkan_enable2 1
#define XR_KHR_vulkan_enable2_SPEC_VERSION 4
#define XR_KHR_VULKAN_ENABLE2_EXTENSION_NAME "XR_KHR_vulkan_enable2"
تعريفنوع XrFlags64 XrVulkanInstanceCreateFlagsKHR;

// Flag bits for XrVulkanInstanceCreateFlagsKHR

تعريفنوع XrFlags64 XrVulkanDeviceCreateFlagsKHR;

// Flag bits for XrVulkanDeviceCreateFlagsKHR

تعريفنوع بنية XrVulkanInstanceCreateInfoKHR {
    XrStructureType                   type;
    ثابت فراغ* XR_MAY_ALIAS          next;
    XrSystemId                        systemId;
    XrVulkanInstanceCreateFlagsKHR    createFlags;
    PFN_vkGetInstanceProcAddr         pfnGetInstanceProcAddr;
    ثابت VkInstanceCreateInfo*       vulkanCreateInfo;
    ثابت VkAllocationCallbacks*      vulkanAllocator;
} XrVulkanInstanceCreateInfoKHR;

تعريفنوع بنية XrVulkanDeviceCreateInfoKHR {
    XrStructureType                 type;
    ثابت فراغ* XR_MAY_ALIAS        next;
    XrSystemId                      systemId;
    XrVulkanDeviceCreateFlagsKHR    createFlags;
    PFN_vkGetInstanceProcAddr       pfnGetInstanceProcAddr;
    VkPhysicalDevice                vulkanPhysicalDevice;
    ثابت VkDeviceCreateInfo*       vulkanCreateInfo;
    ثابت VkAllocationCallbacks*    vulkanAllocator;
} XrVulkanDeviceCreateInfoKHR;

تعريفنوع XrGraphicsBindingVulkanKHR XrGraphicsBindingVulkan2KHR;

تعريفنوع بنية XrVulkanGraphicsDeviceGetInfoKHR {
    XrStructureType             type;
    ثابت فراغ* XR_MAY_ALIAS    next;
    XrSystemId                  systemId;
    VkInstance                  vulkanInstance;
} XrVulkanGraphicsDeviceGetInfoKHR;

تعريفنوع XrSwapchainImageVulkanKHR XrSwapchainImageVulkan2KHR;

تعريفنوع XrGraphicsRequirementsVulkanKHR XrGraphicsRequirementsVulkan2KHR;

تعريفنوع XrResult (XRAPI_PTR *PFN_xrCreateVulkanInstanceKHR)(XrInstance instance, ثابت XrVulkanInstanceCreateInfoKHR* createInfo, VkInstance* vulkanInstance, VkResult* vulkanResult);
تعريفنوع XrResult (XRAPI_PTR *PFN_xrCreateVulkanDeviceKHR)(XrInstance instance, ثابت XrVulkanDeviceCreateInfoKHR* createInfo, VkDevice* vulkanDevice, VkResult* vulkanResult);
تعريفنوع XrResult (XRAPI_PTR *PFN_xrGetVulkanGraphicsDevice2KHR)(XrInstance instance, ثابت XrVulkanGraphicsDeviceGetInfoKHR* getInfo, VkPhysicalDevice* vulkanPhysicalDevice);
تعريفنوع XrResult (XRAPI_PTR *PFN_xrGetVulkanGraphicsRequirements2KHR)(XrInstance instance, XrSystemId systemId, XrGraphicsRequirementsVulkanKHR* graphicsRequirements);

#ifndef XR_NO_PROTOTYPES
#ifdef XR_EXTENSION_PROTOTYPES
XRAPI_ATTR XrResult XRAPI_CALL xrCreateVulkanInstanceKHR(
    XrInstance                                  instance,
    ثابت XrVulkanInstanceCreateInfoKHR*        createInfo,
    VkInstance*                                 vulkanInstance,
    VkResult*                                   vulkanResult);

XRAPI_ATTR XrResult XRAPI_CALL xrCreateVulkanDeviceKHR(
    XrInstance                                  instance,
    ثابت XrVulkanDeviceCreateInfoKHR*          createInfo,
    VkDevice*                                   vulkanDevice,
    VkResult*                                   vulkanResult);

XRAPI_ATTR XrResult XRAPI_CALL xrGetVulkanGraphicsDevice2KHR(
    XrInstance                                  instance,
    ثابت XrVulkanGraphicsDeviceGetInfoKHR*     getInfo,
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
تعريفنوع PFN_xrVoidFunction (*PFN_xrEglGetProcAddressMNDX)(ثابت حرف *name);
// XrGraphicsBindingEGLMNDX extends XrSessionCreateInfo
تعريفنوع بنية XrGraphicsBindingEGLMNDX {
    XrStructureType                type;
    ثابت فراغ* XR_MAY_ALIAS       next;
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
تعريفنوع XrResult (XRAPI_PTR *PFN_xrCreateSpatialAnchorFromPerceptionAnchorMSFT)(XrSession session, IUnknown* perceptionAnchor, XrSpatialAnchorMSFT* anchor);
تعريفنوع XrResult (XRAPI_PTR *PFN_xrTryGetPerceptionAnchorFromSpatialAnchorMSFT)(XrSession session, XrSpatialAnchorMSFT anchor, IUnknown** perceptionAnchor);

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
تعريفنوع بنية XrHolographicWindowAttachmentMSFT {
    XrStructureType             type;
    ثابت فراغ* XR_MAY_ALIAS    next;
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
تعريفنوع XrFlags64 XrAndroidSurfaceSwapchainFlagsFB;

// Flag bits for XrAndroidSurfaceSwapchainFlagsFB
ساكن ثابت XrAndroidSurfaceSwapchainFlagsFB XR_ANDROID_SURFACE_SWAPCHAIN_SYNCHRONOUS_BIT_FB = 0x00000001;
ساكن ثابت XrAndroidSurfaceSwapchainFlagsFB XR_ANDROID_SURFACE_SWAPCHAIN_USE_TIMESTAMPS_BIT_FB = 0x00000002;

#ifdef XR_USE_PLATFORM_ANDROID
// XrAndroidSurfaceSwapchainCreateInfoFB extends XrSwapchainCreateInfo
تعريفنوع بنية XrAndroidSurfaceSwapchainCreateInfoFB {
    XrStructureType                     type;
    ثابت فراغ* XR_MAY_ALIAS            next;
    XrAndroidSurfaceSwapchainFlagsFB    createFlags;
} XrAndroidSurfaceSwapchainCreateInfoFB;
#endif // XR_USE_PLATFORM_ANDROID

#endif /* XR_USE_PLATFORM_ANDROID */

#ifdef XR_USE_PLATFORM_ML

// XR_ML_compat is a preprocessor guard. Do not pass it to API calls.
#define XR_ML_compat 1
#define XR_ML_compat_SPEC_VERSION         1
#define XR_ML_COMPAT_EXTENSION_NAME       "XR_ML_compat"
تعريفنوع بنية XrCoordinateSpaceCreateInfoML {
    XrStructureType             type;
    ثابت فراغ* XR_MAY_ALIAS    next;
    MLCoordinateFrameUID        cfuid;
    XrPosef                     poseInCoordinateSpace;
} XrCoordinateSpaceCreateInfoML;

تعريفنوع XrResult (XRAPI_PTR *PFN_xrCreateSpaceFromCoordinateFrameUIDML)(XrSession session, ثابت XrCoordinateSpaceCreateInfoML *createInfo, XrSpace* space);

#ifndef XR_NO_PROTOTYPES
#ifdef XR_EXTENSION_PROTOTYPES
XRAPI_ATTR XrResult XRAPI_CALL xrCreateSpaceFromCoordinateFrameUIDML(
    XrSession                                   session,
    ثابت XrCoordinateSpaceCreateInfoML *       createInfo,
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
تعريفنوع XrResult (XRAPI_PTR *PFN_xrGetAudioOutputDeviceGuidOculus)(XrInstance instance, wchar_t buffer[XR_MAX_AUDIO_DEVICE_STR_SIZE_OCULUS]);
تعريفنوع XrResult (XRAPI_PTR *PFN_xr_Get_Audio_ماسوقن_Device_Guid_Oculus)(XrInstance instance, wchar_t buffer[XR_MAX_AUDIO_DEVICE_STR_SIZE_OCULUS]);

#ifndef XR_NO_PROTOTYPES
#ifdef XR_EXTENSION_PROTOTYPES
XRAPI_ATTR XrResult XRAPI_CALL xrGetAudioOutputDeviceGuidOculus(
    XrInstance                                  instance,
    wchar_t                                     buffer[XR_MAX_AUDIO_DEVICE_STR_SIZE_OCULUS]);

XRAPI_ATTR XrResult XRAPI_CALL xr_Get_Audio_ماسوقن_Device_Guid_Oculus(
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
تعريفنوع بنية XrSwapchainImageFoveationVulkanFB {
    XrStructureType       type;
    فراغ* XR_MAY_ALIAS    next;
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
تعريفنوع بنية XrSwapchainStateAndroidSurfaceDimensionsFB {
    XrStructureType       type;
    فراغ* XR_MAY_ALIAS    next;
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
تعريفنوع بنية XrSwapchainStateSamplerOpenGLESFB {
    XrStructureType       type;
    فراغ* XR_MAY_ALIAS    next;
    EGLenum               minFilter;
    EGLenum               magFilter;
    EGLenum               wrapModeS;
    EGLenum               wrapModeT;
    EGLenum               swizzleRed;
    EGLenum               swizzleGreen;
    EGLenum               swizzleBlue;
    EGLenum               swizzleAlpha;
    عائم                 maxAnisotropy;
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
تعريفنوع بنية XrSwapchainStateSamplerVulkanFB {
    XrStructureType         type;
    فراغ* XR_MAY_ALIAS      next;
    VkFilter                minFilter;
    VkFilter                magFilter;
    VkSamplerMipmapMode     mipmapMode;
    VkSamplerAddressMode    wrapModeS;
    VkSamplerAddressMode    wrapModeT;
    VkComponentSwizzle      swizzleRed;
    VkComponentSwizzle      swizzleGreen;
    VkComponentSwizzle      swizzleBlue;
    VkComponentSwizzle      swizzleAlpha;
    عائم                   maxAnisotropy;
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
تعريفنوع بنية XrVulkanSwapchainCreateInfoMETA {
    XrStructureType             type;
    ثابت فراغ* XR_MAY_ALIAS    next;
    VkImageCreateFlags          additionalCreateFlags;
    VkImageUsageFlags           additionalUsageFlags;
} XrVulkanSwapchainCreateInfoMETA;

#endif /* XR_USE_GRAPHICS_API_VULKAN */

#ifdef XR_USE_PLATFORM_ANDROID

// XR_ANDROID_anchor_sharing_export is a preprocessor guard. Do not pass it to API calls.
#define XR_ANDROID_anchor_sharing_export 1
#define XR_ANDROID_anchor_sharing_export_SPEC_VERSION 1
#define XR_ANDROID_ANCHOR_SHARING_EXPORT_EXTENSION_NAME "XR_ANDROID_anchor_sharing_export"
تعريفنوع بنية XrAnchorSharingInfoANDROID {
    XrStructureType             type;
    ثابت فراغ* XR_MAY_ALIAS    next;
    XrSpace                     anchor;
} XrAnchorSharingInfoANDROID;

تعريفنوع بنية XrAnchorSharingTokenANDROID {
    XrStructureType       type;
    فراغ* XR_MAY_ALIAS    next;
    بنية AIBinder*      token;
} XrAnchorSharingTokenANDROID;

// XrSystemAnchorSharingExportPropertiesANDROID extends XrSystemProperties
تعريفنوع بنية XrSystemAnchorSharingExportPropertiesANDROID {
    XrStructureType       type;
    فراغ* XR_MAY_ALIAS    next;
    XrBool32              supportsAnchorSharingExport;
} XrSystemAnchorSharingExportPropertiesANDROID;

تعريفنوع XrResult (XRAPI_PTR *PFN_xrShareAnchorANDROID)(XrSession session, ثابت XrAnchorSharingInfoANDROID* sharingInfo, XrAnchorSharingTokenANDROID* anchorToken);
تعريفنوع XrResult (XRAPI_PTR *PFN_xrUnshareAnchorANDROID)(XrSession session, XrSpace anchor);

#ifndef XR_NO_PROTOTYPES
#ifdef XR_EXTENSION_PROTOTYPES
XRAPI_ATTR XrResult XRAPI_CALL xrShareAnchorANDROID(
    XrSession                                   session,
    ثابت XrAnchorSharingInfoANDROID*           sharingInfo,
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
