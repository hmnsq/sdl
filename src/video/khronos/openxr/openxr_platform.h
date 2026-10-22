#که_نه_تعریف_شوی OPENXR_PLATFORM_H_
#تعریف_کړه OPENXR_PLATFORM_H_ 1

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

#که_تعریف_شوی __cplusplus
خارجي "C" {
#د_که_پای


#که_تعریف_شوی XR_USE_PLATFORM_ANDROID

// XR_KHR_android_thread_settings is a preprocessor guard. Do not pass it to API calls.
#تعریف_کړه XR_KHR_android_thread_settings 1
#تعریف_کړه XR_KHR_android_thread_settings_SPEC_نسخه 6
#تعریف_کړه XR_KHR_ANDROID_THREAD_SETTINGS_EXTENSION_NAME "XR_KHR_android_thread_settings"

تعريفنوع تعداد XrAndroidThreadTypeKHR {
    XR_ANDROID_THREAD_TYPE_APPLICATION_MAIN_KHR = 1,
    XR_ANDROID_THREAD_TYPE_APPLICATION_کارګر_KHR = 2,
    XR_ANDROID_THREAD_TYPE_RENDERER_MAIN_KHR = 3,
    XR_ANDROID_THREAD_TYPE_RENDERER_کارګر_KHR = 4,
    XR_ANDROID_THREAD_TYPE_MAX_ENUM_KHR = 0x7FFFFFFF
} XrAndroidThreadTypeKHR;
تعريفنوع Xr_پایله (XRAPI_PTR *PFN_xr_سېټ_Android_Application_Thread_KHR)(XrSession session, XrAndroidThreadTypeKHR threadType, uint32_t threadId);

#که_نه_تعریف_شوی XR_NO_PROTOTYPES
#که_تعریف_شوی XR_EXTENSION_PROTOTYPES
XRAPI_ATTR Xr_پایله XRAPI_CALL xr_سېټ_Android_Application_Thread_KHR(
    XrSession                                   session,
    XrAndroidThreadTypeKHR                      threadType,
    uint32_t                                    threadId);
#د_که_پای /* XR_EXTENSION_PROTOTYPES */
#د_که_پای /* !XR_NO_PROTOTYPES */
#د_که_پای /* XR_USE_PLATFORM_ANDROID */

#که_تعریف_شوی XR_USE_PLATFORM_ANDROID

// XR_KHR_android_surface_swapchain is a preprocessor guard. Do not pass it to API calls.
#تعریف_کړه XR_KHR_android_surface_swapchain 1
#تعریف_کړه XR_KHR_android_surface_swapchain_SPEC_نسخه 4
#تعریف_کړه XR_KHR_ANDROID_SURFACE_SWAPCHAIN_EXTENSION_NAME "XR_KHR_android_surface_swapchain"
تعريفنوع Xr_پایله (XRAPI_PTR *PFN_xrCreateSwapchainAndroidSurfaceKHR)(XrSession session, ثابت XrSwapchainCreateInfo* info, XrSwapchain* swapchain, jobject* surface);

#که_نه_تعریف_شوی XR_NO_PROTOTYPES
#که_تعریف_شوی XR_EXTENSION_PROTOTYPES
XRAPI_ATTR Xr_پایله XRAPI_CALL xrCreateSwapchainAndroidSurfaceKHR(
    XrSession                                   session,
    ثابت XrSwapchainCreateInfo*                info,
    XrSwapchain*                                swapchain,
    jobject*                                    surface);
#د_که_پای /* XR_EXTENSION_PROTOTYPES */
#د_که_پای /* !XR_NO_PROTOTYPES */
#د_که_پای /* XR_USE_PLATFORM_ANDROID */

#که_تعریف_شوی XR_USE_PLATFORM_ANDROID

// XR_KHR_android_create_instance is a preprocessor guard. Do not pass it to API calls.
#تعریف_کړه XR_KHR_android_create_instance 1
#تعریف_کړه XR_KHR_android_create_instance_SPEC_نسخه 3
#تعریف_کړه XR_KHR_ANDROID_CREATE_INSTANCE_EXTENSION_NAME "XR_KHR_android_create_instance"
// XrInstanceCreateInfoAndroidKHR extends XrInstanceCreateInfo
تعريفنوع بنية XrInstanceCreateInfoAndroidKHR {
    XrStructureType             type;
    ثابت فراغ* XR_MAY_ALIAS    بل;
    فراغ* XR_MAY_ALIAS          applicationVM;
    فراغ* XR_MAY_ALIAS          applicationActivity;
} XrInstanceCreateInfoAndroidKHR;

#د_که_پای /* XR_USE_PLATFORM_ANDROID */

#که_تعریف_شوی XR_USE_GRAPHICS_API_VULKAN

// XR_KHR_vulkan_swapchain_format_list is a preprocessor guard. Do not pass it to API calls.
#تعریف_کړه XR_KHR_vulkan_swapchain_format_list 1
#تعریف_کړه XR_KHR_vulkan_swapchain_format_list_SPEC_نسخه 5
#تعریف_کړه XR_KHR_VULKAN_SWAPCHAIN_FORMAT_LIST_EXTENSION_NAME "XR_KHR_vulkan_swapchain_format_list"
// XrVulkanSwapchainFormatListCreateInfoKHR extends XrSwapchainCreateInfo
تعريفنوع بنية XrVulkanSwapchainFormatListCreateInfoKHR {
    XrStructureType             type;
    ثابت فراغ* XR_MAY_ALIAS    بل;
    uint32_t                    view_Format_شمېر;
    ثابت VkFormat*             viewFormats;
} XrVulkanSwapchainFormatListCreateInfoKHR;

#د_که_پای /* XR_USE_GRAPHICS_API_VULKAN */

#که_تعریف_شوی XR_USE_GRAPHICS_API_OPENGL

// XR_KHR_opengl_enable is a preprocessor guard. Do not pass it to API calls.
#تعریف_کړه XR_KHR_opengl_enable 1
#تعریف_کړه XR_KHR_opengl_enable_SPEC_نسخه 12
#تعریف_کړه XR_KHR_OPENGL_ENABLE_EXTENSION_NAME "XR_KHR_opengl_enable"
#که_تعریف_شوی XR_USE_PLATFORM_WIN32
// XrGraphicsBindingOpenGLWin32KHR extends XrSessionCreateInfo
تعريفنوع بنية XrGraphicsBindingOpenGLWin32KHR {
    XrStructureType             type;
    ثابت فراغ* XR_MAY_ALIAS    بل;
    HDC                         hDC;
    HGLRC                       hGLRC;
} XrGraphicsBindingOpenGLWin32KHR;
#د_که_پای // XR_USE_PLATFORM_WIN32

#که_تعریف_شوی XR_USE_PLATFORM_XLIB
// XrGraphicsBindingOpenGLXlibKHR extends XrSessionCreateInfo
تعريفنوع بنية XrGraphicsBindingOpenGLXlibKHR {
    XrStructureType             type;
    ثابت فراغ* XR_MAY_ALIAS    بل;
    Display*                    xDisplay;
    uint32_t                    visualid;
    GLXFBConfig                 glxFBConfig;
    GLXDrawable                 glxDrawable;
    GLXContext                  glxContext;
} XrGraphicsBindingOpenGLXlibKHR;
#د_که_پای // XR_USE_PLATFORM_XLIB

#که_تعریف_شوی XR_USE_PLATFORM_XCB
// XrGraphicsBindingOpenGLXcbKHR extends XrSessionCreateInfo
تعريفنوع بنية XrGraphicsBindingOpenGLXcbKHR {
    XrStructureType             type;
    ثابت فراغ* XR_MAY_ALIAS    بل;
    xcb_connection_t*           connection;
    uint32_t                    screen_شمېره;
    xcb_glx_fbconfig_t          fbconfigid;
    xcb_visualid_t              visualid;
    xcb_glx_drawable_t          glxDrawable;
    xcb_glx_context_t           glxContext;
} XrGraphicsBindingOpenGLXcbKHR;
#د_که_پای // XR_USE_PLATFORM_XCB

#که_تعریف_شوی XR_USE_PLATFORM_WAYLAND
// XrGraphicsBindingOpenGLWaylandKHR extends XrSessionCreateInfo
تعريفنوع بنية XrGraphicsBindingOpenGLWaylandKHR {
    XrStructureType             type;
    ثابت فراغ* XR_MAY_ALIAS    بل;
    بنية wl_display*          display;
} XrGraphicsBindingOpenGLWaylandKHR;
#د_که_پای // XR_USE_PLATFORM_WAYLAND

تعريفنوع بنية XrSwapchainImageOpenGLKHR {
    XrStructureType       type;
    فراغ* XR_MAY_ALIAS    بل;
    uint32_t              image;
} XrSwapchainImageOpenGLKHR;

تعريفنوع بنية XrGraphicsRequirementsOpenGLKHR {
    XrStructureType       type;
    فراغ* XR_MAY_ALIAS    بل;
    Xr_نسخه             min_Api_نسخه_Supported;
    Xr_نسخه             max_Api_نسخه_Supported;
} XrGraphicsRequirementsOpenGLKHR;

تعريفنوع Xr_پایله (XRAPI_PTR *PFN_xrGetOpenGLGraphicsRequirementsKHR)(XrInstance instance, XrSystemId systemId, XrGraphicsRequirementsOpenGLKHR* graphicsRequirements);

#که_نه_تعریف_شوی XR_NO_PROTOTYPES
#که_تعریف_شوی XR_EXTENSION_PROTOTYPES
XRAPI_ATTR Xr_پایله XRAPI_CALL xrGetOpenGLGraphicsRequirementsKHR(
    XrInstance                                  instance,
    XrSystemId                                  systemId,
    XrGraphicsRequirementsOpenGLKHR*            graphicsRequirements);
#د_که_پای /* XR_EXTENSION_PROTOTYPES */
#د_که_پای /* !XR_NO_PROTOTYPES */
#د_که_پای /* XR_USE_GRAPHICS_API_OPENGL */

#که_تعریف_شوی XR_USE_GRAPHICS_API_OPENGL_ES

// XR_KHR_opengl_es_enable is a preprocessor guard. Do not pass it to API calls.
#تعریف_کړه XR_KHR_opengl_es_enable 1
#تعریف_کړه XR_KHR_opengl_es_enable_SPEC_نسخه 10
#تعریف_کړه XR_KHR_OPENGL_ES_ENABLE_EXTENSION_NAME "XR_KHR_opengl_es_enable"
#که_تعریف_شوی XR_USE_PLATFORM_ANDROID
// XrGraphicsBindingOpenGLESAndroidKHR extends XrSessionCreateInfo
تعريفنوع بنية XrGraphicsBindingOpenGLESAndroidKHR {
    XrStructureType             type;
    ثابت فراغ* XR_MAY_ALIAS    بل;
    EGLDisplay                  display;
    EGLConfig                   config;
    EGLContext                  context;
} XrGraphicsBindingOpenGLESAndroidKHR;
#د_که_پای // XR_USE_PLATFORM_ANDROID

تعريفنوع بنية XrSwapchainImageOpenGLESKHR {
    XrStructureType       type;
    فراغ* XR_MAY_ALIAS    بل;
    uint32_t              image;
} XrSwapchainImageOpenGLESKHR;

تعريفنوع بنية XrGraphicsRequirementsOpenGLESKHR {
    XrStructureType       type;
    فراغ* XR_MAY_ALIAS    بل;
    Xr_نسخه             min_Api_نسخه_Supported;
    Xr_نسخه             max_Api_نسخه_Supported;
} XrGraphicsRequirementsOpenGLESKHR;

تعريفنوع Xr_پایله (XRAPI_PTR *PFN_xrGetOpenGLESGraphicsRequirementsKHR)(XrInstance instance, XrSystemId systemId, XrGraphicsRequirementsOpenGLESKHR* graphicsRequirements);

#که_نه_تعریف_شوی XR_NO_PROTOTYPES
#که_تعریف_شوی XR_EXTENSION_PROTOTYPES
XRAPI_ATTR Xr_پایله XRAPI_CALL xrGetOpenGLESGraphicsRequirementsKHR(
    XrInstance                                  instance,
    XrSystemId                                  systemId,
    XrGraphicsRequirementsOpenGLESKHR*          graphicsRequirements);
#د_که_پای /* XR_EXTENSION_PROTOTYPES */
#د_که_پای /* !XR_NO_PROTOTYPES */
#د_که_پای /* XR_USE_GRAPHICS_API_OPENGL_ES */

#که_تعریف_شوی XR_USE_GRAPHICS_API_VULKAN

// XR_KHR_vulkan_enable is a preprocessor guard. Do not pass it to API calls.
#تعریف_کړه XR_KHR_vulkan_enable 1
#تعریف_کړه XR_KHR_vulkan_enable_SPEC_نسخه 10
#تعریف_کړه XR_KHR_VULKAN_ENABLE_EXTENSION_NAME "XR_KHR_vulkan_enable"
// XrGraphicsBindingVulkanKHR extends XrSessionCreateInfo
تعريفنوع بنية XrGraphicsBindingVulkanKHR {
    XrStructureType             type;
    ثابت فراغ* XR_MAY_ALIAS    بل;
    VkInstance                  instance;
    VkPhysicalDevice            physicalDevice;
    VkDevice                    device;
    uint32_t                    کتار_Family_شاخص;
    uint32_t                    کتار_شاخص;
} XrGraphicsBindingVulkanKHR;

تعريفنوع بنية XrSwapchainImageVulkanKHR {
    XrStructureType       type;
    فراغ* XR_MAY_ALIAS    بل;
    VkImage               image;
} XrSwapchainImageVulkanKHR;

تعريفنوع بنية XrGraphicsRequirementsVulkanKHR {
    XrStructureType       type;
    فراغ* XR_MAY_ALIAS    بل;
    Xr_نسخه             min_Api_نسخه_Supported;
    Xr_نسخه             max_Api_نسخه_Supported;
} XrGraphicsRequirementsVulkanKHR;

تعريفنوع Xr_پایله (XRAPI_PTR *PFN_xrGetVulkanInstanceExtensionsKHR)(XrInstance instance, XrSystemId systemId, uint32_t بفر_ظرفیت_ننوت, uint32_t* بفر_شمېر_Output, حرف* بفر_2);
تعريفنوع Xr_پایله (XRAPI_PTR *PFN_xrGetVulkanDeviceExtensionsKHR)(XrInstance instance, XrSystemId systemId, uint32_t بفر_ظرفیت_ننوت, uint32_t* بفر_شمېر_Output, حرف* بفر_2);
تعريفنوع Xr_پایله (XRAPI_PTR *PFN_xrGetVulkanGraphicsDeviceKHR)(XrInstance instance, XrSystemId systemId, VkInstance vkInstance, VkPhysicalDevice* vkPhysicalDevice);
تعريفنوع Xr_پایله (XRAPI_PTR *PFN_xrGetVulkanGraphicsRequirementsKHR)(XrInstance instance, XrSystemId systemId, XrGraphicsRequirementsVulkanKHR* graphicsRequirements);

#که_نه_تعریف_شوی XR_NO_PROTOTYPES
#که_تعریف_شوی XR_EXTENSION_PROTOTYPES
XRAPI_ATTR Xr_پایله XRAPI_CALL xrGetVulkanInstanceExtensionsKHR(
    XrInstance                                  instance,
    XrSystemId                                  systemId,
    uint32_t                                    بفر_ظرفیت_ننوت,
    uint32_t*                                   بفر_شمېر_Output,
    حرف*                                       بفر_2);

XRAPI_ATTR Xr_پایله XRAPI_CALL xrGetVulkanDeviceExtensionsKHR(
    XrInstance                                  instance,
    XrSystemId                                  systemId,
    uint32_t                                    بفر_ظرفیت_ننوت,
    uint32_t*                                   بفر_شمېر_Output,
    حرف*                                       بفر_2);

XRAPI_ATTR Xr_پایله XRAPI_CALL xrGetVulkanGraphicsDeviceKHR(
    XrInstance                                  instance,
    XrSystemId                                  systemId,
    VkInstance                                  vkInstance,
    VkPhysicalDevice*                           vkPhysicalDevice);

XRAPI_ATTR Xr_پایله XRAPI_CALL xrGetVulkanGraphicsRequirementsKHR(
    XrInstance                                  instance,
    XrSystemId                                  systemId,
    XrGraphicsRequirementsVulkanKHR*            graphicsRequirements);
#د_که_پای /* XR_EXTENSION_PROTOTYPES */
#د_که_پای /* !XR_NO_PROTOTYPES */
#د_که_پای /* XR_USE_GRAPHICS_API_VULKAN */

#که_تعریف_شوی XR_USE_GRAPHICS_API_D3D11

// XR_KHR_D3D11_enable is a preprocessor guard. Do not pass it to API calls.
#تعریف_کړه XR_KHR_D3D11_enable 1
#تعریف_کړه XR_KHR_D3_D11_enable_SPEC_نسخه  11
#تعریف_کړه XR_KHR_D3D11_ENABLE_EXTENSION_NAME "XR_KHR_D3D11_enable"
// XrGraphicsBindingD3D11KHR extends XrSessionCreateInfo
تعريفنوع بنية XrGraphicsBindingD3D11KHR {
    XrStructureType             type;
    ثابت فراغ* XR_MAY_ALIAS    بل;
    ID3D11Device*               device;
} XrGraphicsBindingD3D11KHR;

تعريفنوع بنية XrSwapchainImageD3D11KHR {
     XrStructureType      type;
    فراغ* XR_MAY_ALIAS    بل;
    ID3D11Texture2D*      texture;
} XrSwapchainImageD3D11KHR;

تعريفنوع بنية XrGraphicsRequirementsD3D11KHR {
    XrStructureType       type;
    فراغ* XR_MAY_ALIAS    بل;
    LUID                  adapterLuid;
    D3D_FEATURE_LEVEL     minFeatureLevel;
} XrGraphicsRequirementsD3D11KHR;

تعريفنوع Xr_پایله (XRAPI_PTR *PFN_xrGetD3D11GraphicsRequirementsKHR)(XrInstance instance, XrSystemId systemId, XrGraphicsRequirementsD3D11KHR* graphicsRequirements);

#که_نه_تعریف_شوی XR_NO_PROTOTYPES
#که_تعریف_شوی XR_EXTENSION_PROTOTYPES
XRAPI_ATTR Xr_پایله XRAPI_CALL xrGetD3D11GraphicsRequirementsKHR(
    XrInstance                                  instance,
    XrSystemId                                  systemId,
    XrGraphicsRequirementsD3D11KHR*             graphicsRequirements);
#د_که_پای /* XR_EXTENSION_PROTOTYPES */
#د_که_پای /* !XR_NO_PROTOTYPES */
#د_که_پای /* XR_USE_GRAPHICS_API_D3D11 */

#که_تعریف_شوی XR_USE_GRAPHICS_API_D3D12

// XR_KHR_D3D12_enable is a preprocessor guard. Do not pass it to API calls.
#تعریف_کړه XR_KHR_D3D12_enable 1
#تعریف_کړه XR_KHR_D3_D12_enable_SPEC_نسخه  11
#تعریف_کړه XR_KHR_D3D12_ENABLE_EXTENSION_NAME "XR_KHR_D3D12_enable"
// XrGraphicsBindingD3D12KHR extends XrSessionCreateInfo
تعريفنوع بنية XrGraphicsBindingD3D12KHR {
    XrStructureType             type;
    ثابت فراغ* XR_MAY_ALIAS    بل;
    ID3D12Device*               device;
    ID3_D12_Command_کتار*         کتار;
} XrGraphicsBindingD3D12KHR;

تعريفنوع بنية XrSwapchainImageD3D12KHR {
     XrStructureType      type;
    فراغ* XR_MAY_ALIAS    بل;
    ID3D12Resource*       texture;
} XrSwapchainImageD3D12KHR;

تعريفنوع بنية XrGraphicsRequirementsD3D12KHR {
    XrStructureType       type;
    فراغ* XR_MAY_ALIAS    بل;
    LUID                  adapterLuid;
    D3D_FEATURE_LEVEL     minFeatureLevel;
} XrGraphicsRequirementsD3D12KHR;

تعريفنوع Xr_پایله (XRAPI_PTR *PFN_xrGetD3D12GraphicsRequirementsKHR)(XrInstance instance, XrSystemId systemId, XrGraphicsRequirementsD3D12KHR* graphicsRequirements);

#که_نه_تعریف_شوی XR_NO_PROTOTYPES
#که_تعریف_شوی XR_EXTENSION_PROTOTYPES
XRAPI_ATTR Xr_پایله XRAPI_CALL xrGetD3D12GraphicsRequirementsKHR(
    XrInstance                                  instance,
    XrSystemId                                  systemId,
    XrGraphicsRequirementsD3D12KHR*             graphicsRequirements);
#د_که_پای /* XR_EXTENSION_PROTOTYPES */
#د_که_پای /* !XR_NO_PROTOTYPES */
#د_که_پای /* XR_USE_GRAPHICS_API_D3D12 */

#که_تعریف_شوی XR_USE_GRAPHICS_API_METAL

// XR_KHR_metal_enable is a preprocessor guard. Do not pass it to API calls.
#تعریف_کړه XR_KHR_metal_enable 1
#تعریف_کړه XR_KHR_metal_enable_SPEC_نسخه  3
#تعریف_کړه XR_KHR_METAL_ENABLE_EXTENSION_NAME "XR_KHR_metal_enable"
// XrGraphicsBindingMetalKHR extends XrSessionCreateInfo
تعريفنوع بنية XrGraphicsBindingMetalKHR {
    XrStructureType             type;
    ثابت فراغ* XR_MAY_ALIAS    بل;
    فراغ* XR_MAY_ALIAS          command_کتار;
} XrGraphicsBindingMetalKHR;

تعريفنوع بنية XrSwapchainImageMetalKHR {
    XrStructureType       type;
    فراغ* XR_MAY_ALIAS    بل;
    فراغ* XR_MAY_ALIAS    texture;
} XrSwapchainImageMetalKHR;

تعريفنوع بنية XrGraphicsRequirementsMetalKHR {
    XrStructureType       type;
    فراغ* XR_MAY_ALIAS    بل;
    فراغ* XR_MAY_ALIAS    metalDevice;
} XrGraphicsRequirementsMetalKHR;

تعريفنوع Xr_پایله (XRAPI_PTR *PFN_xrGetMetalGraphicsRequirementsKHR)(XrInstance instance, XrSystemId systemId, XrGraphicsRequirementsMetalKHR* graphicsRequirements);

#که_نه_تعریف_شوی XR_NO_PROTOTYPES
#که_تعریف_شوی XR_EXTENSION_PROTOTYPES
XRAPI_ATTR Xr_پایله XRAPI_CALL xrGetMetalGraphicsRequirementsKHR(
    XrInstance                                  instance,
    XrSystemId                                  systemId,
    XrGraphicsRequirementsMetalKHR*             graphicsRequirements);
#د_که_پای /* XR_EXTENSION_PROTOTYPES */
#د_که_پای /* !XR_NO_PROTOTYPES */
#د_که_پای /* XR_USE_GRAPHICS_API_METAL */

#که_تعریف_شوی XR_USE_PLATFORM_WIN32

// XR_KHR_win32_convert_performance_counter_time is a preprocessor guard. Do not pass it to API calls.
#تعریف_کړه XR_KHR_win32_convert_performance_counter_وخت 1
#تعریف_کړه XR_KHR_win32_convert_performance_counter_وخت_SPEC_نسخه 1
#تعریف_کړه XR_KHR_WIN32_CONVERT_PERFORMANCE_COUNTER_وخت_EXTENSION_NAME "XR_KHR_win32_convert_performance_counter_time"
تعريفنوع Xr_پایله (XRAPI_PTR *PFN_xr_Convert_Win32_Performance_Counter_منزل_وخت_KHR)(XrInstance instance, ثابت LARGE_INTEGER* performanceCounter, Xr_وخت* وخت);
تعريفنوع Xr_پایله (XRAPI_PTR *PFN_xr_Convert_وخت_منزل_Win32_Performance_Counter_KHR)(XrInstance instance, Xr_وخت وخت, LARGE_INTEGER* performanceCounter);

#که_نه_تعریف_شوی XR_NO_PROTOTYPES
#که_تعریف_شوی XR_EXTENSION_PROTOTYPES
XRAPI_ATTR Xr_پایله XRAPI_CALL xr_Convert_Win32_Performance_Counter_منزل_وخت_KHR(
    XrInstance                                  instance,
    ثابت LARGE_INTEGER*                        performanceCounter,
    Xr_وخت*                                     وخت);

XRAPI_ATTR Xr_پایله XRAPI_CALL xr_Convert_وخت_منزل_Win32_Performance_Counter_KHR(
    XrInstance                                  instance,
    Xr_وخت                                      وخت,
    LARGE_INTEGER*                              performanceCounter);
#د_که_پای /* XR_EXTENSION_PROTOTYPES */
#د_که_پای /* !XR_NO_PROTOTYPES */
#د_که_پای /* XR_USE_PLATFORM_WIN32 */

#که_تعریف_شوی XR_USE_TIMESPEC

// XR_KHR_convert_timespec_time is a preprocessor guard. Do not pass it to API calls.
#تعریف_کړه XR_KHR_convert_timespec_وخت 1
#تعریف_کړه XR_KHR_convert_timespec_وخت_SPEC_نسخه 1
#تعریف_کړه XR_KHR_CONVERT_TIMESPEC_وخت_EXTENSION_NAME "XR_KHR_convert_timespec_time"
تعريفنوع Xr_پایله (XRAPI_PTR *PFN_xr_Convert_Timespec_وخت_منزل_وخت_KHR)(XrInstance instance, ثابت بنية timespec* timespec_وخت, Xr_وخت* وخت);
تعريفنوع Xr_پایله (XRAPI_PTR *PFN_xr_Convert_وخت_منزل_Timespec_وخت_KHR)(XrInstance instance, Xr_وخت وخت, بنية timespec* timespec_وخت);

#که_نه_تعریف_شوی XR_NO_PROTOTYPES
#که_تعریف_شوی XR_EXTENSION_PROTOTYPES
XRAPI_ATTR Xr_پایله XRAPI_CALL xr_Convert_Timespec_وخت_منزل_وخت_KHR(
    XrInstance                                  instance,
    ثابت بنية timespec*                      timespec_وخت,
    Xr_وخت*                                     وخت);

XRAPI_ATTR Xr_پایله XRAPI_CALL xr_Convert_وخت_منزل_Timespec_وخت_KHR(
    XrInstance                                  instance,
    Xr_وخت                                      وخت,
    بنية timespec*                            timespec_وخت);
#د_که_پای /* XR_EXTENSION_PROTOTYPES */
#د_که_پای /* !XR_NO_PROTOTYPES */
#د_که_پای /* XR_USE_TIMESPEC */

#که_تعریف_شوی XR_USE_PLATFORM_ANDROID

// XR_KHR_loader_init_android is a preprocessor guard. Do not pass it to API calls.
#تعریف_کړه XR_KHR_loader_init_android 1
#تعریف_کړه XR_KHR_loader_init_android_SPEC_نسخه 1
#تعریف_کړه XR_KHR_LOADER_INIT_ANDROID_EXTENSION_NAME "XR_KHR_loader_init_android"
تعريفنوع بنية XrLoaderInitInfoAndroidKHR {
    XrStructureType             type;
    ثابت فراغ* XR_MAY_ALIAS    بل;
    فراغ* XR_MAY_ALIAS          applicationVM;
    فراغ* XR_MAY_ALIAS          applicationContext;
} XrLoaderInitInfoAndroidKHR;

#د_که_پای /* XR_USE_PLATFORM_ANDROID */

#که_تعریف_شوی XR_USE_GRAPHICS_API_VULKAN

// XR_KHR_vulkan_enable2 is a preprocessor guard. Do not pass it to API calls.
#تعریف_کړه XR_KHR_vulkan_enable2 1
#تعریف_کړه XR_KHR_vulkan_enable2_SPEC_نسخه 4
#تعریف_کړه XR_KHR_VULKAN_ENABLE2_EXTENSION_NAME "XR_KHR_vulkan_enable2"
تعريفنوع XrFlags64 XrVulkanInstanceCreateFlagsKHR;

// Flag bits for XrVulkanInstanceCreateFlagsKHR

تعريفنوع XrFlags64 XrVulkanDeviceCreateFlagsKHR;

// Flag bits for XrVulkanDeviceCreateFlagsKHR

تعريفنوع بنية XrVulkanInstanceCreateInfoKHR {
    XrStructureType                   type;
    ثابت فراغ* XR_MAY_ALIAS          بل;
    XrSystemId                        systemId;
    XrVulkanInstanceCreateFlagsKHR    createFlags;
    PFN_vkGetInstanceProcAddr         pfnGetInstanceProcAddr;
    ثابت VkInstanceCreateInfo*       vulkanCreateInfo;
    ثابت Vk_ویش_Callbacks*      vulkanAllocator;
} XrVulkanInstanceCreateInfoKHR;

تعريفنوع بنية XrVulkanDeviceCreateInfoKHR {
    XrStructureType                 type;
    ثابت فراغ* XR_MAY_ALIAS        بل;
    XrSystemId                      systemId;
    XrVulkanDeviceCreateFlagsKHR    createFlags;
    PFN_vkGetInstanceProcAddr       pfnGetInstanceProcAddr;
    VkPhysicalDevice                vulkanPhysicalDevice;
    ثابت VkDeviceCreateInfo*       vulkanCreateInfo;
    ثابت Vk_ویش_Callbacks*    vulkanAllocator;
} XrVulkanDeviceCreateInfoKHR;

تعريفنوع XrGraphicsBindingVulkanKHR XrGraphicsBindingVulkan2KHR;

تعريفنوع بنية XrVulkanGraphicsDeviceGetInfoKHR {
    XrStructureType             type;
    ثابت فراغ* XR_MAY_ALIAS    بل;
    XrSystemId                  systemId;
    VkInstance                  vulkanInstance;
} XrVulkanGraphicsDeviceGetInfoKHR;

تعريفنوع XrSwapchainImageVulkanKHR XrSwapchainImageVulkan2KHR;

تعريفنوع XrGraphicsRequirementsVulkanKHR XrGraphicsRequirementsVulkan2KHR;

تعريفنوع Xr_پایله (XRAPI_PTR *PFN_xrCreateVulkanInstanceKHR)(XrInstance instance, ثابت XrVulkanInstanceCreateInfoKHR* createInfo, VkInstance* vulkanInstance, Vk_پایله* vulkan_پایله);
تعريفنوع Xr_پایله (XRAPI_PTR *PFN_xrCreateVulkanDeviceKHR)(XrInstance instance, ثابت XrVulkanDeviceCreateInfoKHR* createInfo, VkDevice* vulkanDevice, Vk_پایله* vulkan_پایله);
تعريفنوع Xr_پایله (XRAPI_PTR *PFN_xrGetVulkanGraphicsDevice2KHR)(XrInstance instance, ثابت XrVulkanGraphicsDeviceGetInfoKHR* getInfo, VkPhysicalDevice* vulkanPhysicalDevice);
تعريفنوع Xr_پایله (XRAPI_PTR *PFN_xrGetVulkanGraphicsRequirements2KHR)(XrInstance instance, XrSystemId systemId, XrGraphicsRequirementsVulkanKHR* graphicsRequirements);

#که_نه_تعریف_شوی XR_NO_PROTOTYPES
#که_تعریف_شوی XR_EXTENSION_PROTOTYPES
XRAPI_ATTR Xr_پایله XRAPI_CALL xrCreateVulkanInstanceKHR(
    XrInstance                                  instance,
    ثابت XrVulkanInstanceCreateInfoKHR*        createInfo,
    VkInstance*                                 vulkanInstance,
    Vk_پایله*                                   vulkan_پایله);

XRAPI_ATTR Xr_پایله XRAPI_CALL xrCreateVulkanDeviceKHR(
    XrInstance                                  instance,
    ثابت XrVulkanDeviceCreateInfoKHR*          createInfo,
    VkDevice*                                   vulkanDevice,
    Vk_پایله*                                   vulkan_پایله);

XRAPI_ATTR Xr_پایله XRAPI_CALL xrGetVulkanGraphicsDevice2KHR(
    XrInstance                                  instance,
    ثابت XrVulkanGraphicsDeviceGetInfoKHR*     getInfo,
    VkPhysicalDevice*                           vulkanPhysicalDevice);

XRAPI_ATTR Xr_پایله XRAPI_CALL xrGetVulkanGraphicsRequirements2KHR(
    XrInstance                                  instance,
    XrSystemId                                  systemId,
    XrGraphicsRequirementsVulkanKHR*            graphicsRequirements);
#د_که_پای /* XR_EXTENSION_PROTOTYPES */
#د_که_پای /* !XR_NO_PROTOTYPES */
#د_که_پای /* XR_USE_GRAPHICS_API_VULKAN */

#که_تعریف_شوی XR_USE_PLATFORM_EGL

// XR_MNDX_egl_enable is a preprocessor guard. Do not pass it to API calls.
#تعریف_کړه XR_MNDX_egl_enable 1
#تعریف_کړه XR_MNDX_egl_enable_SPEC_نسخه   2
#تعریف_کړه XR_MNDX_EGL_ENABLE_EXTENSION_NAME "XR_MNDX_egl_enable"
تعريفنوع PFN_xrVoidFunction (*PFN_xr_Egl_Get_Proc_پته_MNDX)(ثابت حرف *name);
// XrGraphicsBindingEGLMNDX extends XrSessionCreateInfo
تعريفنوع بنية XrGraphicsBindingEGLMNDX {
    XrStructureType                type;
    ثابت فراغ* XR_MAY_ALIAS       بل;
    PFN_xr_Egl_Get_Proc_پته_MNDX    get_Proc_پته;
    EGLDisplay                     display;
    EGLConfig                      config;
    EGLContext                     context;
} XrGraphicsBindingEGLMNDX;

#د_که_پای /* XR_USE_PLATFORM_EGL */

#که_تعریف_شوی XR_USE_PLATFORM_WIN32

// XR_MSFT_perception_anchor_interop is a preprocessor guard. Do not pass it to API calls.
#تعریف_کړه XR_MSFT_perception_anchor_interop 1
#تعریف_کړه XR_MSFT_perception_anchor_interop_SPEC_نسخه 1
#تعریف_کړه XR_MSFT_PERCEPTION_ANCHOR_INTEROP_EXTENSION_NAME "XR_MSFT_perception_anchor_interop"
تعريفنوع Xr_پایله (XRAPI_PTR *PFN_xrCreateSpatialAnchorFromPerceptionAnchorMSFT)(XrSession session, IUnknown* perceptionAnchor, XrSpatialAnchorMSFT* anchor);
تعريفنوع Xr_پایله (XRAPI_PTR *PFN_xrTryGetPerceptionAnchorFromSpatialAnchorMSFT)(XrSession session, XrSpatialAnchorMSFT anchor, IUnknown** perceptionAnchor);

#که_نه_تعریف_شوی XR_NO_PROTOTYPES
#که_تعریف_شوی XR_EXTENSION_PROTOTYPES
XRAPI_ATTR Xr_پایله XRAPI_CALL xrCreateSpatialAnchorFromPerceptionAnchorMSFT(
    XrSession                                   session,
    IUnknown*                                   perceptionAnchor,
    XrSpatialAnchorMSFT*                        anchor);

XRAPI_ATTR Xr_پایله XRAPI_CALL xrTryGetPerceptionAnchorFromSpatialAnchorMSFT(
    XrSession                                   session,
    XrSpatialAnchorMSFT                         anchor,
    IUnknown**                                  perceptionAnchor);
#د_که_پای /* XR_EXTENSION_PROTOTYPES */
#د_که_پای /* !XR_NO_PROTOTYPES */
#د_که_پای /* XR_USE_PLATFORM_WIN32 */

#که_تعریف_شوی XR_USE_PLATFORM_WIN32

// XR_MSFT_holographic_window_attachment is a preprocessor guard. Do not pass it to API calls.
#تعریف_کړه XR_MSFT_holographic_کړکۍ_attachment 1
#تعریف_کړه XR_MSFT_holographic_کړکۍ_attachment_SPEC_نسخه 1
#تعریف_کړه XR_MSFT_HOLOGRAPHIC_کړکۍ_ATTACHMENT_EXTENSION_NAME "XR_MSFT_holographic_window_attachment"
#که_تعریف_شوی XR_USE_PLATFORM_WIN32
// XrHolographicWindowAttachmentMSFT extends XrSessionCreateInfo
تعريفنوع بنية Xr_Holographic_کړکۍ_Attachment_MSFT {
    XrStructureType             type;
    ثابت فراغ* XR_MAY_ALIAS    بل;
    IUnknown*                   holographicSpace;
    IUnknown*                   core_کړکۍ;
} Xr_Holographic_کړکۍ_Attachment_MSFT;
#د_که_پای // XR_USE_PLATFORM_WIN32

#د_که_پای /* XR_USE_PLATFORM_WIN32 */

#که_تعریف_شوی XR_USE_PLATFORM_ANDROID

// XR_FB_android_surface_swapchain_create is a preprocessor guard. Do not pass it to API calls.
#تعریف_کړه XR_FB_android_surface_swapchain_create 1
#تعریف_کړه XR_FB_android_surface_swapchain_create_SPEC_نسخه 1
#تعریف_کړه XR_FB_ANDROID_SURFACE_SWAPCHAIN_CREATE_EXTENSION_NAME "XR_FB_android_surface_swapchain_create"
تعريفنوع XrFlags64 XrAndroidSurfaceSwapchainFlagsFB;

// Flag bits for XrAndroidSurfaceSwapchainFlagsFB
ساكن ثابت XrAndroidSurfaceSwapchainFlagsFB XR_ANDROID_SURFACE_SWAPCHAIN_SYNCHRONOUS_بټ_FB = 0x00000001;
ساكن ثابت XrAndroidSurfaceSwapchainFlagsFB XR_ANDROID_SURFACE_SWAPCHAIN_USE_TIMESTAMPS_بټ_FB = 0x00000002;

#که_تعریف_شوی XR_USE_PLATFORM_ANDROID
// XrAndroidSurfaceSwapchainCreateInfoFB extends XrSwapchainCreateInfo
تعريفنوع بنية XrAndroidSurfaceSwapchainCreateInfoFB {
    XrStructureType                     type;
    ثابت فراغ* XR_MAY_ALIAS            بل;
    XrAndroidSurfaceSwapchainFlagsFB    createFlags;
} XrAndroidSurfaceSwapchainCreateInfoFB;
#د_که_پای // XR_USE_PLATFORM_ANDROID

#د_که_پای /* XR_USE_PLATFORM_ANDROID */

#که_تعریف_شوی XR_USE_PLATFORM_ML

// XR_ML_compat is a preprocessor guard. Do not pass it to API calls.
#تعریف_کړه XR_ML_compat 1
#تعریف_کړه XR_ML_compat_SPEC_نسخه         1
#تعریف_کړه XR_ML_COMPAT_EXTENSION_NAME       "XR_ML_compat"
تعريفنوع بنية XrCoordinateSpaceCreateInfoML {
    XrStructureType             type;
    ثابت فراغ* XR_MAY_ALIAS    بل;
    MLCoordinate_چوکاټ_UID        cfuid;
    XrPosef                     pose_دننه_Coordinate_Space;
} XrCoordinateSpaceCreateInfoML;

تعريفنوع Xr_پایله (XRAPI_PTR *PFN_xr_Create_Space_From_Coordinate_چوکاټ_UIDML)(XrSession session, ثابت XrCoordinateSpaceCreateInfoML *createInfo, XrSpace* space);

#که_نه_تعریف_شوی XR_NO_PROTOTYPES
#که_تعریف_شوی XR_EXTENSION_PROTOTYPES
XRAPI_ATTR Xr_پایله XRAPI_CALL xr_Create_Space_From_Coordinate_چوکاټ_UIDML(
    XrSession                                   session,
    ثابت XrCoordinateSpaceCreateInfoML *       createInfo,
    XrSpace*                                    space);
#د_که_پای /* XR_EXTENSION_PROTOTYPES */
#د_که_پای /* !XR_NO_PROTOTYPES */
#د_که_پای /* XR_USE_PLATFORM_ML */

#که_تعریف_شوی XR_USE_PLATFORM_WIN32

// XR_OCULUS_audio_device_guid is a preprocessor guard. Do not pass it to API calls.
#تعریف_کړه XR_OCULUS_audio_device_guid 1
#تعریف_کړه XR_OCULUS_audio_device_guid_SPEC_نسخه 1
#تعریف_کړه XR_OCULUS_AUDIO_DEVICE_GUID_EXTENSION_NAME "XR_OCULUS_audio_device_guid"
#تعریف_کړه XR_MAX_AUDIO_DEVICE_STR_اندازه_OCULUS 128
تعريفنوع Xr_پایله (XRAPI_PTR *PFN_xrGetAudioOutputDeviceGuidOculus)(XrInstance instance, wchar_t بفر_2[XR_MAX_AUDIO_DEVICE_STR_اندازه_OCULUS]);
تعريفنوع Xr_پایله (XRAPI_PTR *PFN_xr_Get_Audio_ننوت_Device_Guid_Oculus)(XrInstance instance, wchar_t بفر_2[XR_MAX_AUDIO_DEVICE_STR_اندازه_OCULUS]);

#که_نه_تعریف_شوی XR_NO_PROTOTYPES
#که_تعریف_شوی XR_EXTENSION_PROTOTYPES
XRAPI_ATTR Xr_پایله XRAPI_CALL xrGetAudioOutputDeviceGuidOculus(
    XrInstance                                  instance,
    wchar_t                                     بفر_2[XR_MAX_AUDIO_DEVICE_STR_اندازه_OCULUS]);

XRAPI_ATTR Xr_پایله XRAPI_CALL xr_Get_Audio_ننوت_Device_Guid_Oculus(
    XrInstance                                  instance,
    wchar_t                                     بفر_2[XR_MAX_AUDIO_DEVICE_STR_اندازه_OCULUS]);
#د_که_پای /* XR_EXTENSION_PROTOTYPES */
#د_که_پای /* !XR_NO_PROTOTYPES */
#د_که_پای /* XR_USE_PLATFORM_WIN32 */

#که_تعریف_شوی XR_USE_GRAPHICS_API_VULKAN

// XR_FB_foveation_vulkan is a preprocessor guard. Do not pass it to API calls.
#تعریف_کړه XR_FB_foveation_vulkan 1
#تعریف_کړه XR_FB_foveation_vulkan_SPEC_نسخه 1
#تعریف_کړه XR_FB_FOVEATION_VULKAN_EXTENSION_NAME "XR_FB_foveation_vulkan"
// XrSwapchainImageFoveationVulkanFB extends XrSwapchainImageVulkanKHR
تعريفنوع بنية XrSwapchainImageFoveationVulkanFB {
    XrStructureType       type;
    فراغ* XR_MAY_ALIAS    بل;
    VkImage               image;
    uint32_t              پلنوالی;
    uint32_t              لوړوالی;
} XrSwapchainImageFoveationVulkanFB;

#د_که_پای /* XR_USE_GRAPHICS_API_VULKAN */

#که_تعریف_شوی XR_USE_PLATFORM_ANDROID

// XR_FB_swapchain_update_state_android_surface is a preprocessor guard. Do not pass it to API calls.
#تعریف_کړه XR_FB_swapchain_update_state_android_surface 1
#تعریف_کړه XR_FB_swapchain_update_state_android_surface_SPEC_نسخه 1
#تعریف_کړه XR_FB_SWAPCHAIN_UPDATE_STATE_ANDROID_SURFACE_EXTENSION_NAME "XR_FB_swapchain_update_state_android_surface"
#که_تعریف_شوی XR_USE_PLATFORM_ANDROID
تعريفنوع بنية XrSwapchainStateAndroidSurfaceDimensionsFB {
    XrStructureType       type;
    فراغ* XR_MAY_ALIAS    بل;
    uint32_t              پلنوالی;
    uint32_t              لوړوالی;
} XrSwapchainStateAndroidSurfaceDimensionsFB;
#د_که_پای // XR_USE_PLATFORM_ANDROID

#د_که_پای /* XR_USE_PLATFORM_ANDROID */

#که_تعریف_شوی XR_USE_GRAPHICS_API_OPENGL_ES

// XR_FB_swapchain_update_state_opengl_es is a preprocessor guard. Do not pass it to API calls.
#تعریف_کړه XR_FB_swapchain_update_state_opengl_es 1
#تعریف_کړه XR_FB_swapchain_update_state_opengl_es_SPEC_نسخه 1
#تعریف_کړه XR_FB_SWAPCHAIN_UPDATE_STATE_OPENGL_ES_EXTENSION_NAME "XR_FB_swapchain_update_state_opengl_es"
#که_تعریف_شوی XR_USE_GRAPHICS_API_OPENGL_ES
تعريفنوع بنية XrSwapchainStateSamplerOpenGLESFB {
    XrStructureType       type;
    فراغ* XR_MAY_ALIAS    بل;
    EGLenum               minFilter;
    EGLenum               magFilter;
    EGLenum               wrap_ډېرپېښ_S;
    EGLenum               wrap_ډېرپېښ_T;
    EGLenum               swizzleRed;
    EGLenum               swizzleGreen;
    EGLenum               swizzleBlue;
    EGLenum               swizzleAlpha;
    عائم                 maxAnisotropy;
    XrColor4f             borderColor;
} XrSwapchainStateSamplerOpenGLESFB;
#د_که_پای // XR_USE_GRAPHICS_API_OPENGL_ES

#د_که_پای /* XR_USE_GRAPHICS_API_OPENGL_ES */

#که_تعریف_شوی XR_USE_GRAPHICS_API_VULKAN

// XR_FB_swapchain_update_state_vulkan is a preprocessor guard. Do not pass it to API calls.
#تعریف_کړه XR_FB_swapchain_update_state_vulkan 1
#تعریف_کړه XR_FB_swapchain_update_state_vulkan_SPEC_نسخه 1
#تعریف_کړه XR_FB_SWAPCHAIN_UPDATE_STATE_VULKAN_EXTENSION_NAME "XR_FB_swapchain_update_state_vulkan"
#که_تعریف_شوی XR_USE_GRAPHICS_API_VULKAN
تعريفنوع بنية XrSwapchainStateSamplerVulkanFB {
    XrStructureType         type;
    فراغ* XR_MAY_ALIAS      بل;
    VkFilter                minFilter;
    VkFilter                magFilter;
    Vk_Sampler_Mipmap_ډېرپېښ     mipmap_ډېرپېښ;
    Vk_Sampler_پته_ډېرپېښ    wrap_ډېرپېښ_S;
    Vk_Sampler_پته_ډېرپېښ    wrap_ډېرپېښ_T;
    VkComponentSwizzle      swizzleRed;
    VkComponentSwizzle      swizzleGreen;
    VkComponentSwizzle      swizzleBlue;
    VkComponentSwizzle      swizzleAlpha;
    عائم                   maxAnisotropy;
    XrColor4f               borderColor;
} XrSwapchainStateSamplerVulkanFB;
#د_که_پای // XR_USE_GRAPHICS_API_VULKAN

#د_که_پای /* XR_USE_GRAPHICS_API_VULKAN */

#که_تعریف_شوی XR_USE_GRAPHICS_API_VULKAN

// XR_META_vulkan_swapchain_create_info is a preprocessor guard. Do not pass it to API calls.
#تعریف_کړه XR_META_vulkan_swapchain_create_info 1
#تعریف_کړه XR_META_vulkan_swapchain_create_info_SPEC_نسخه 1
#تعریف_کړه XR_META_VULKAN_SWAPCHAIN_CREATE_INFO_EXTENSION_NAME "XR_META_vulkan_swapchain_create_info"
// XrVulkanSwapchainCreateInfoMETA extends XrSwapchainCreateInfo
تعريفنوع بنية XrVulkanSwapchainCreateInfoMETA {
    XrStructureType             type;
    ثابت فراغ* XR_MAY_ALIAS    بل;
    VkImageCreateFlags          additionalCreateFlags;
    VkImageUsageFlags           additionalUsageFlags;
} XrVulkanSwapchainCreateInfoMETA;

#د_که_پای /* XR_USE_GRAPHICS_API_VULKAN */

#که_تعریف_شوی XR_USE_PLATFORM_ANDROID

// XR_ANDROID_anchor_sharing_export is a preprocessor guard. Do not pass it to API calls.
#تعریف_کړه XR_ANDROID_anchor_sharing_export 1
#تعریف_کړه XR_ANDROID_anchor_sharing_export_SPEC_نسخه 1
#تعریف_کړه XR_ANDROID_ANCHOR_SHARING_EXPORT_EXTENSION_NAME "XR_ANDROID_anchor_sharing_export"
تعريفنوع بنية XrAnchorSharingInfoANDROID {
    XrStructureType             type;
    ثابت فراغ* XR_MAY_ALIAS    بل;
    XrSpace                     anchor;
} XrAnchorSharingInfoANDROID;

تعريفنوع بنية XrAnchorSharingTokenANDROID {
    XrStructureType       type;
    فراغ* XR_MAY_ALIAS    بل;
    بنية AIBinder*      token;
} XrAnchorSharingTokenANDROID;

// XrSystemAnchorSharingExportPropertiesANDROID extends XrSystemProperties
تعريفنوع بنية XrSystemAnchorSharingExportPropertiesANDROID {
    XrStructureType       type;
    فراغ* XR_MAY_ALIAS    بل;
    XrBool32              supportsAnchorSharingExport;
} XrSystemAnchorSharingExportPropertiesANDROID;

تعريفنوع Xr_پایله (XRAPI_PTR *PFN_xrShareAnchorANDROID)(XrSession session, ثابت XrAnchorSharingInfoANDROID* sharingInfo, XrAnchorSharingTokenANDROID* anchorToken);
تعريفنوع Xr_پایله (XRAPI_PTR *PFN_xrUnshareAnchorANDROID)(XrSession session, XrSpace anchor);

#که_نه_تعریف_شوی XR_NO_PROTOTYPES
#که_تعریف_شوی XR_EXTENSION_PROTOTYPES
XRAPI_ATTR Xr_پایله XRAPI_CALL xrShareAnchorANDROID(
    XrSession                                   session,
    ثابت XrAnchorSharingInfoANDROID*           sharingInfo,
    XrAnchorSharingTokenANDROID*                anchorToken);

XRAPI_ATTR Xr_پایله XRAPI_CALL xrUnshareAnchorANDROID(
    XrSession                                   session,
    XrSpace                                     anchor);
#د_که_پای /* XR_EXTENSION_PROTOTYPES */
#د_که_پای /* !XR_NO_PROTOTYPES */
#د_که_پای /* XR_USE_PLATFORM_ANDROID */

#که_تعریف_شوی __cplusplus
}
#د_که_پای

#د_که_پای
