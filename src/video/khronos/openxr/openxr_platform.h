#جے_بنا_تعریف OPENXR_PLATFORM_H_
#تعریف_کرو OPENXR_PLATFORM_H_ 1

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

#جے_تعریف_شدہ __cplusplus
خارجي "C" {
#جے_انت


#جے_تعریف_شدہ XR_USE_PLATFORM_ANDROID

// XR_KHR_android_thread_settings is a preprocessor guard. Do not pass it to API calls.
#تعریف_کرو XR_KHR_android_thread_settings 1
#تعریف_کرو XR_KHR_android_thread_settings_SPEC_نسخہ 6
#تعریف_کرو XR_KHR_ANDROID_THREAD_SETTINGS_EXTENSION_NAME "XR_KHR_android_thread_settings"

تعريفنوع تعداد XrAndroidThreadTypeKHR {
    XR_ANDROID_THREAD_TYPE_APPLICATION_MAIN_KHR = 1,
    XR_ANDROID_THREAD_TYPE_APPLICATION_کامہ_KHR = 2,
    XR_ANDROID_THREAD_TYPE_RENDERER_MAIN_KHR = 3,
    XR_ANDROID_THREAD_TYPE_RENDERER_کامہ_KHR = 4,
    XR_ANDROID_THREAD_TYPE_MAX_ENUM_KHR = 0x7FFFFFFF
} XrAndroidThreadTypeKHR;
تعريفنوع Xr_نتیجہ (XRAPI_PTR *PFN_xr_سیٹ_Android_Application_Thread_KHR)(XrSession session, XrAndroidThreadTypeKHR threadType, uint32_t threadId);

#جے_بنا_تعریف XR_NO_PROTOTYPES
#جے_تعریف_شدہ XR_EXTENSION_PROTOTYPES
XRAPI_ATTR Xr_نتیجہ XRAPI_CALL xr_سیٹ_Android_Application_Thread_KHR(
    XrSession                                   session,
    XrAndroidThreadTypeKHR                      threadType,
    uint32_t                                    threadId);
#جے_انت /* XR_EXTENSION_PROTOTYPES */
#جے_انت /* !XR_NO_PROTOTYPES */
#جے_انت /* XR_USE_PLATFORM_ANDROID */

#جے_تعریف_شدہ XR_USE_PLATFORM_ANDROID

// XR_KHR_android_surface_swapchain is a preprocessor guard. Do not pass it to API calls.
#تعریف_کرو XR_KHR_android_surface_swapchain 1
#تعریف_کرو XR_KHR_android_surface_swapchain_SPEC_نسخہ 4
#تعریف_کرو XR_KHR_ANDROID_SURFACE_SWAPCHAIN_EXTENSION_NAME "XR_KHR_android_surface_swapchain"
تعريفنوع Xr_نتیجہ (XRAPI_PTR *PFN_xrCreateSwapchainAndroidSurfaceKHR)(XrSession session, ثابت XrSwapchainCreateInfo* info, XrSwapchain* swapchain, jobject* surface);

#جے_بنا_تعریف XR_NO_PROTOTYPES
#جے_تعریف_شدہ XR_EXTENSION_PROTOTYPES
XRAPI_ATTR Xr_نتیجہ XRAPI_CALL xrCreateSwapchainAndroidSurfaceKHR(
    XrSession                                   session,
    ثابت XrSwapchainCreateInfo*                info,
    XrSwapchain*                                swapchain,
    jobject*                                    surface);
#جے_انت /* XR_EXTENSION_PROTOTYPES */
#جے_انت /* !XR_NO_PROTOTYPES */
#جے_انت /* XR_USE_PLATFORM_ANDROID */

#جے_تعریف_شدہ XR_USE_PLATFORM_ANDROID

// XR_KHR_android_create_instance is a preprocessor guard. Do not pass it to API calls.
#تعریف_کرو XR_KHR_android_create_instance 1
#تعریف_کرو XR_KHR_android_create_instance_SPEC_نسخہ 3
#تعریف_کرو XR_KHR_ANDROID_CREATE_INSTANCE_EXTENSION_NAME "XR_KHR_android_create_instance"
// XrInstanceCreateInfoAndroidKHR extends XrInstanceCreateInfo
تعريفنوع بنية XrInstanceCreateInfoAndroidKHR {
    XrStructureType             type;
    ثابت فراغ* XR_MAY_ALIAS    اگلا;
    فراغ* XR_MAY_ALIAS          applicationVM;
    فراغ* XR_MAY_ALIAS          applicationActivity;
} XrInstanceCreateInfoAndroidKHR;

#جے_انت /* XR_USE_PLATFORM_ANDROID */

#جے_تعریف_شدہ XR_USE_GRAPHICS_API_VULKAN

// XR_KHR_vulkan_swapchain_format_list is a preprocessor guard. Do not pass it to API calls.
#تعریف_کرو XR_KHR_vulkan_swapchain_format_list 1
#تعریف_کرو XR_KHR_vulkan_swapchain_format_list_SPEC_نسخہ 5
#تعریف_کرو XR_KHR_VULKAN_SWAPCHAIN_FORMAT_LIST_EXTENSION_NAME "XR_KHR_vulkan_swapchain_format_list"
// XrVulkanSwapchainFormatListCreateInfoKHR extends XrSwapchainCreateInfo
تعريفنوع بنية XrVulkanSwapchainFormatListCreateInfoKHR {
    XrStructureType             type;
    ثابت فراغ* XR_MAY_ALIAS    اگلا;
    uint32_t                    view_Format_گنتی;
    ثابت VkFormat*             viewFormats;
} XrVulkanSwapchainFormatListCreateInfoKHR;

#جے_انت /* XR_USE_GRAPHICS_API_VULKAN */

#جے_تعریف_شدہ XR_USE_GRAPHICS_API_OPENGL

// XR_KHR_opengl_enable is a preprocessor guard. Do not pass it to API calls.
#تعریف_کرو XR_KHR_opengl_enable 1
#تعریف_کرو XR_KHR_opengl_enable_SPEC_نسخہ 12
#تعریف_کرو XR_KHR_OPENGL_ENABLE_EXTENSION_NAME "XR_KHR_opengl_enable"
#جے_تعریف_شدہ XR_USE_PLATFORM_WIN32
// XrGraphicsBindingOpenGLWin32KHR extends XrSessionCreateInfo
تعريفنوع بنية XrGraphicsBindingOpenGLWin32KHR {
    XrStructureType             type;
    ثابت فراغ* XR_MAY_ALIAS    اگلا;
    HDC                         hDC;
    HGLRC                       hGLRC;
} XrGraphicsBindingOpenGLWin32KHR;
#جے_انت // XR_USE_PLATFORM_WIN32

#جے_تعریف_شدہ XR_USE_PLATFORM_XLIB
// XrGraphicsBindingOpenGLXlibKHR extends XrSessionCreateInfo
تعريفنوع بنية XrGraphicsBindingOpenGLXlibKHR {
    XrStructureType             type;
    ثابت فراغ* XR_MAY_ALIAS    اگلا;
    Display*                    xDisplay;
    uint32_t                    visualid;
    GLXFBConfig                 glxFBConfig;
    GLXDrawable                 glxDrawable;
    GLXContext                  glxContext;
} XrGraphicsBindingOpenGLXlibKHR;
#جے_انت // XR_USE_PLATFORM_XLIB

#جے_تعریف_شدہ XR_USE_PLATFORM_XCB
// XrGraphicsBindingOpenGLXcbKHR extends XrSessionCreateInfo
تعريفنوع بنية XrGraphicsBindingOpenGLXcbKHR {
    XrStructureType             type;
    ثابت فراغ* XR_MAY_ALIAS    اگلا;
    xcb_connection_t*           connection;
    uint32_t                    screen_نمبر;
    xcb_glx_fbconfig_t          fbconfigid;
    xcb_visualid_t              visualid;
    xcb_glx_drawable_t          glxDrawable;
    xcb_glx_context_t           glxContext;
} XrGraphicsBindingOpenGLXcbKHR;
#جے_انت // XR_USE_PLATFORM_XCB

#جے_تعریف_شدہ XR_USE_PLATFORM_WAYLAND
// XrGraphicsBindingOpenGLWaylandKHR extends XrSessionCreateInfo
تعريفنوع بنية XrGraphicsBindingOpenGLWaylandKHR {
    XrStructureType             type;
    ثابت فراغ* XR_MAY_ALIAS    اگلا;
    بنية wl_display*          display;
} XrGraphicsBindingOpenGLWaylandKHR;
#جے_انت // XR_USE_PLATFORM_WAYLAND

تعريفنوع بنية XrSwapchainImageOpenGLKHR {
    XrStructureType       type;
    فراغ* XR_MAY_ALIAS    اگلا;
    uint32_t              image;
} XrSwapchainImageOpenGLKHR;

تعريفنوع بنية XrGraphicsRequirementsOpenGLKHR {
    XrStructureType       type;
    فراغ* XR_MAY_ALIAS    اگلا;
    Xr_نسخہ             min_Api_نسخہ_Supported;
    Xr_نسخہ             max_Api_نسخہ_Supported;
} XrGraphicsRequirementsOpenGLKHR;

تعريفنوع Xr_نتیجہ (XRAPI_PTR *PFN_xrGetOpenGLGraphicsRequirementsKHR)(XrInstance instance, XrSystemId systemId, XrGraphicsRequirementsOpenGLKHR* graphicsRequirements);

#جے_بنا_تعریف XR_NO_PROTOTYPES
#جے_تعریف_شدہ XR_EXTENSION_PROTOTYPES
XRAPI_ATTR Xr_نتیجہ XRAPI_CALL xrGetOpenGLGraphicsRequirementsKHR(
    XrInstance                                  instance,
    XrSystemId                                  systemId,
    XrGraphicsRequirementsOpenGLKHR*            graphicsRequirements);
#جے_انت /* XR_EXTENSION_PROTOTYPES */
#جے_انت /* !XR_NO_PROTOTYPES */
#جے_انت /* XR_USE_GRAPHICS_API_OPENGL */

#جے_تعریف_شدہ XR_USE_GRAPHICS_API_OPENGL_ES

// XR_KHR_opengl_es_enable is a preprocessor guard. Do not pass it to API calls.
#تعریف_کرو XR_KHR_opengl_es_enable 1
#تعریف_کرو XR_KHR_opengl_es_enable_SPEC_نسخہ 10
#تعریف_کرو XR_KHR_OPENGL_ES_ENABLE_EXTENSION_NAME "XR_KHR_opengl_es_enable"
#جے_تعریف_شدہ XR_USE_PLATFORM_ANDROID
// XrGraphicsBindingOpenGLESAndroidKHR extends XrSessionCreateInfo
تعريفنوع بنية XrGraphicsBindingOpenGLESAndroidKHR {
    XrStructureType             type;
    ثابت فراغ* XR_MAY_ALIAS    اگلا;
    EGLDisplay                  display;
    EGLConfig                   config;
    EGLContext                  context;
} XrGraphicsBindingOpenGLESAndroidKHR;
#جے_انت // XR_USE_PLATFORM_ANDROID

تعريفنوع بنية XrSwapchainImageOpenGLESKHR {
    XrStructureType       type;
    فراغ* XR_MAY_ALIAS    اگلا;
    uint32_t              image;
} XrSwapchainImageOpenGLESKHR;

تعريفنوع بنية XrGraphicsRequirementsOpenGLESKHR {
    XrStructureType       type;
    فراغ* XR_MAY_ALIAS    اگلا;
    Xr_نسخہ             min_Api_نسخہ_Supported;
    Xr_نسخہ             max_Api_نسخہ_Supported;
} XrGraphicsRequirementsOpenGLESKHR;

تعريفنوع Xr_نتیجہ (XRAPI_PTR *PFN_xrGetOpenGLESGraphicsRequirementsKHR)(XrInstance instance, XrSystemId systemId, XrGraphicsRequirementsOpenGLESKHR* graphicsRequirements);

#جے_بنا_تعریف XR_NO_PROTOTYPES
#جے_تعریف_شدہ XR_EXTENSION_PROTOTYPES
XRAPI_ATTR Xr_نتیجہ XRAPI_CALL xrGetOpenGLESGraphicsRequirementsKHR(
    XrInstance                                  instance,
    XrSystemId                                  systemId,
    XrGraphicsRequirementsOpenGLESKHR*          graphicsRequirements);
#جے_انت /* XR_EXTENSION_PROTOTYPES */
#جے_انت /* !XR_NO_PROTOTYPES */
#جے_انت /* XR_USE_GRAPHICS_API_OPENGL_ES */

#جے_تعریف_شدہ XR_USE_GRAPHICS_API_VULKAN

// XR_KHR_vulkan_enable is a preprocessor guard. Do not pass it to API calls.
#تعریف_کرو XR_KHR_vulkan_enable 1
#تعریف_کرو XR_KHR_vulkan_enable_SPEC_نسخہ 10
#تعریف_کرو XR_KHR_VULKAN_ENABLE_EXTENSION_NAME "XR_KHR_vulkan_enable"
// XrGraphicsBindingVulkanKHR extends XrSessionCreateInfo
تعريفنوع بنية XrGraphicsBindingVulkanKHR {
    XrStructureType             type;
    ثابت فراغ* XR_MAY_ALIAS    اگلا;
    VkInstance                  instance;
    VkPhysicalDevice            physicalDevice;
    VkDevice                    device;
    uint32_t                    قطار_Family_اشاریہ;
    uint32_t                    قطار_اشاریہ;
} XrGraphicsBindingVulkanKHR;

تعريفنوع بنية XrSwapchainImageVulkanKHR {
    XrStructureType       type;
    فراغ* XR_MAY_ALIAS    اگلا;
    VkImage               image;
} XrSwapchainImageVulkanKHR;

تعريفنوع بنية XrGraphicsRequirementsVulkanKHR {
    XrStructureType       type;
    فراغ* XR_MAY_ALIAS    اگلا;
    Xr_نسخہ             min_Api_نسخہ_Supported;
    Xr_نسخہ             max_Api_نسخہ_Supported;
} XrGraphicsRequirementsVulkanKHR;

تعريفنوع Xr_نتیجہ (XRAPI_PTR *PFN_xrGetVulkanInstanceExtensionsKHR)(XrInstance instance, XrSystemId systemId, uint32_t بفر_سمرتھا_داخلہ, uint32_t* بفر_گنتی_Output, حرف* بفر_2);
تعريفنوع Xr_نتیجہ (XRAPI_PTR *PFN_xrGetVulkanDeviceExtensionsKHR)(XrInstance instance, XrSystemId systemId, uint32_t بفر_سمرتھا_داخلہ, uint32_t* بفر_گنتی_Output, حرف* بفر_2);
تعريفنوع Xr_نتیجہ (XRAPI_PTR *PFN_xrGetVulkanGraphicsDeviceKHR)(XrInstance instance, XrSystemId systemId, VkInstance vkInstance, VkPhysicalDevice* vkPhysicalDevice);
تعريفنوع Xr_نتیجہ (XRAPI_PTR *PFN_xrGetVulkanGraphicsRequirementsKHR)(XrInstance instance, XrSystemId systemId, XrGraphicsRequirementsVulkanKHR* graphicsRequirements);

#جے_بنا_تعریف XR_NO_PROTOTYPES
#جے_تعریف_شدہ XR_EXTENSION_PROTOTYPES
XRAPI_ATTR Xr_نتیجہ XRAPI_CALL xrGetVulkanInstanceExtensionsKHR(
    XrInstance                                  instance,
    XrSystemId                                  systemId,
    uint32_t                                    بفر_سمرتھا_داخلہ,
    uint32_t*                                   بفر_گنتی_Output,
    حرف*                                       بفر_2);

XRAPI_ATTR Xr_نتیجہ XRAPI_CALL xrGetVulkanDeviceExtensionsKHR(
    XrInstance                                  instance,
    XrSystemId                                  systemId,
    uint32_t                                    بفر_سمرتھا_داخلہ,
    uint32_t*                                   بفر_گنتی_Output,
    حرف*                                       بفر_2);

XRAPI_ATTR Xr_نتیجہ XRAPI_CALL xrGetVulkanGraphicsDeviceKHR(
    XrInstance                                  instance,
    XrSystemId                                  systemId,
    VkInstance                                  vkInstance,
    VkPhysicalDevice*                           vkPhysicalDevice);

XRAPI_ATTR Xr_نتیجہ XRAPI_CALL xrGetVulkanGraphicsRequirementsKHR(
    XrInstance                                  instance,
    XrSystemId                                  systemId,
    XrGraphicsRequirementsVulkanKHR*            graphicsRequirements);
#جے_انت /* XR_EXTENSION_PROTOTYPES */
#جے_انت /* !XR_NO_PROTOTYPES */
#جے_انت /* XR_USE_GRAPHICS_API_VULKAN */

#جے_تعریف_شدہ XR_USE_GRAPHICS_API_D3D11

// XR_KHR_D3D11_enable is a preprocessor guard. Do not pass it to API calls.
#تعریف_کرو XR_KHR_D3D11_enable 1
#تعریف_کرو XR_KHR_D3_D11_enable_SPEC_نسخہ  11
#تعریف_کرو XR_KHR_D3D11_ENABLE_EXTENSION_NAME "XR_KHR_D3D11_enable"
// XrGraphicsBindingD3D11KHR extends XrSessionCreateInfo
تعريفنوع بنية XrGraphicsBindingD3D11KHR {
    XrStructureType             type;
    ثابت فراغ* XR_MAY_ALIAS    اگلا;
    ID3D11Device*               device;
} XrGraphicsBindingD3D11KHR;

تعريفنوع بنية XrSwapchainImageD3D11KHR {
     XrStructureType      type;
    فراغ* XR_MAY_ALIAS    اگلا;
    ID3D11Texture2D*      texture;
} XrSwapchainImageD3D11KHR;

تعريفنوع بنية XrGraphicsRequirementsD3D11KHR {
    XrStructureType       type;
    فراغ* XR_MAY_ALIAS    اگلا;
    LUID                  adapterLuid;
    D3D_FEATURE_LEVEL     minFeatureLevel;
} XrGraphicsRequirementsD3D11KHR;

تعريفنوع Xr_نتیجہ (XRAPI_PTR *PFN_xrGetD3D11GraphicsRequirementsKHR)(XrInstance instance, XrSystemId systemId, XrGraphicsRequirementsD3D11KHR* graphicsRequirements);

#جے_بنا_تعریف XR_NO_PROTOTYPES
#جے_تعریف_شدہ XR_EXTENSION_PROTOTYPES
XRAPI_ATTR Xr_نتیجہ XRAPI_CALL xrGetD3D11GraphicsRequirementsKHR(
    XrInstance                                  instance,
    XrSystemId                                  systemId,
    XrGraphicsRequirementsD3D11KHR*             graphicsRequirements);
#جے_انت /* XR_EXTENSION_PROTOTYPES */
#جے_انت /* !XR_NO_PROTOTYPES */
#جے_انت /* XR_USE_GRAPHICS_API_D3D11 */

#جے_تعریف_شدہ XR_USE_GRAPHICS_API_D3D12

// XR_KHR_D3D12_enable is a preprocessor guard. Do not pass it to API calls.
#تعریف_کرو XR_KHR_D3D12_enable 1
#تعریف_کرو XR_KHR_D3_D12_enable_SPEC_نسخہ  11
#تعریف_کرو XR_KHR_D3D12_ENABLE_EXTENSION_NAME "XR_KHR_D3D12_enable"
// XrGraphicsBindingD3D12KHR extends XrSessionCreateInfo
تعريفنوع بنية XrGraphicsBindingD3D12KHR {
    XrStructureType             type;
    ثابت فراغ* XR_MAY_ALIAS    اگلا;
    ID3D12Device*               device;
    ID3_D12_Command_قطار*         قطار;
} XrGraphicsBindingD3D12KHR;

تعريفنوع بنية XrSwapchainImageD3D12KHR {
     XrStructureType      type;
    فراغ* XR_MAY_ALIAS    اگلا;
    ID3D12Resource*       texture;
} XrSwapchainImageD3D12KHR;

تعريفنوع بنية XrGraphicsRequirementsD3D12KHR {
    XrStructureType       type;
    فراغ* XR_MAY_ALIAS    اگلا;
    LUID                  adapterLuid;
    D3D_FEATURE_LEVEL     minFeatureLevel;
} XrGraphicsRequirementsD3D12KHR;

تعريفنوع Xr_نتیجہ (XRAPI_PTR *PFN_xrGetD3D12GraphicsRequirementsKHR)(XrInstance instance, XrSystemId systemId, XrGraphicsRequirementsD3D12KHR* graphicsRequirements);

#جے_بنا_تعریف XR_NO_PROTOTYPES
#جے_تعریف_شدہ XR_EXTENSION_PROTOTYPES
XRAPI_ATTR Xr_نتیجہ XRAPI_CALL xrGetD3D12GraphicsRequirementsKHR(
    XrInstance                                  instance,
    XrSystemId                                  systemId,
    XrGraphicsRequirementsD3D12KHR*             graphicsRequirements);
#جے_انت /* XR_EXTENSION_PROTOTYPES */
#جے_انت /* !XR_NO_PROTOTYPES */
#جے_انت /* XR_USE_GRAPHICS_API_D3D12 */

#جے_تعریف_شدہ XR_USE_GRAPHICS_API_METAL

// XR_KHR_metal_enable is a preprocessor guard. Do not pass it to API calls.
#تعریف_کرو XR_KHR_metal_enable 1
#تعریف_کرو XR_KHR_metal_enable_SPEC_نسخہ  3
#تعریف_کرو XR_KHR_METAL_ENABLE_EXTENSION_NAME "XR_KHR_metal_enable"
// XrGraphicsBindingMetalKHR extends XrSessionCreateInfo
تعريفنوع بنية XrGraphicsBindingMetalKHR {
    XrStructureType             type;
    ثابت فراغ* XR_MAY_ALIAS    اگلا;
    فراغ* XR_MAY_ALIAS          command_قطار;
} XrGraphicsBindingMetalKHR;

تعريفنوع بنية XrSwapchainImageMetalKHR {
    XrStructureType       type;
    فراغ* XR_MAY_ALIAS    اگلا;
    فراغ* XR_MAY_ALIAS    texture;
} XrSwapchainImageMetalKHR;

تعريفنوع بنية XrGraphicsRequirementsMetalKHR {
    XrStructureType       type;
    فراغ* XR_MAY_ALIAS    اگلا;
    فراغ* XR_MAY_ALIAS    metalDevice;
} XrGraphicsRequirementsMetalKHR;

تعريفنوع Xr_نتیجہ (XRAPI_PTR *PFN_xrGetMetalGraphicsRequirementsKHR)(XrInstance instance, XrSystemId systemId, XrGraphicsRequirementsMetalKHR* graphicsRequirements);

#جے_بنا_تعریف XR_NO_PROTOTYPES
#جے_تعریف_شدہ XR_EXTENSION_PROTOTYPES
XRAPI_ATTR Xr_نتیجہ XRAPI_CALL xrGetMetalGraphicsRequirementsKHR(
    XrInstance                                  instance,
    XrSystemId                                  systemId,
    XrGraphicsRequirementsMetalKHR*             graphicsRequirements);
#جے_انت /* XR_EXTENSION_PROTOTYPES */
#جے_انت /* !XR_NO_PROTOTYPES */
#جے_انت /* XR_USE_GRAPHICS_API_METAL */

#جے_تعریف_شدہ XR_USE_PLATFORM_WIN32

// XR_KHR_win32_convert_performance_counter_time is a preprocessor guard. Do not pass it to API calls.
#تعریف_کرو XR_KHR_win32_convert_performance_counter_ویلا 1
#تعریف_کرو XR_KHR_win32_convert_performance_counter_ویلا_SPEC_نسخہ 1
#تعریف_کرو XR_KHR_WIN32_CONVERT_PERFORMANCE_COUNTER_ویلا_EXTENSION_NAME "XR_KHR_win32_convert_performance_counter_time"
تعريفنوع Xr_نتیجہ (XRAPI_PTR *PFN_xr_Convert_Win32_Performance_Counter_منزل_ویلا_KHR)(XrInstance instance, ثابت LARGE_INTEGER* performanceCounter, Xr_ویلا* ویلا);
تعريفنوع Xr_نتیجہ (XRAPI_PTR *PFN_xr_Convert_ویلا_منزل_Win32_Performance_Counter_KHR)(XrInstance instance, Xr_ویلا ویلا, LARGE_INTEGER* performanceCounter);

#جے_بنا_تعریف XR_NO_PROTOTYPES
#جے_تعریف_شدہ XR_EXTENSION_PROTOTYPES
XRAPI_ATTR Xr_نتیجہ XRAPI_CALL xr_Convert_Win32_Performance_Counter_منزل_ویلا_KHR(
    XrInstance                                  instance,
    ثابت LARGE_INTEGER*                        performanceCounter,
    Xr_ویلا*                                     ویلا);

XRAPI_ATTR Xr_نتیجہ XRAPI_CALL xr_Convert_ویلا_منزل_Win32_Performance_Counter_KHR(
    XrInstance                                  instance,
    Xr_ویلا                                      ویلا,
    LARGE_INTEGER*                              performanceCounter);
#جے_انت /* XR_EXTENSION_PROTOTYPES */
#جے_انت /* !XR_NO_PROTOTYPES */
#جے_انت /* XR_USE_PLATFORM_WIN32 */

#جے_تعریف_شدہ XR_USE_TIMESPEC

// XR_KHR_convert_timespec_time is a preprocessor guard. Do not pass it to API calls.
#تعریف_کرو XR_KHR_convert_timespec_ویلا 1
#تعریف_کرو XR_KHR_convert_timespec_ویلا_SPEC_نسخہ 1
#تعریف_کرو XR_KHR_CONVERT_TIMESPEC_ویلا_EXTENSION_NAME "XR_KHR_convert_timespec_time"
تعريفنوع Xr_نتیجہ (XRAPI_PTR *PFN_xr_Convert_Timespec_ویلا_منزل_ویلا_KHR)(XrInstance instance, ثابت بنية timespec* timespec_ویلا, Xr_ویلا* ویلا);
تعريفنوع Xr_نتیجہ (XRAPI_PTR *PFN_xr_Convert_ویلا_منزل_Timespec_ویلا_KHR)(XrInstance instance, Xr_ویلا ویلا, بنية timespec* timespec_ویلا);

#جے_بنا_تعریف XR_NO_PROTOTYPES
#جے_تعریف_شدہ XR_EXTENSION_PROTOTYPES
XRAPI_ATTR Xr_نتیجہ XRAPI_CALL xr_Convert_Timespec_ویلا_منزل_ویلا_KHR(
    XrInstance                                  instance,
    ثابت بنية timespec*                      timespec_ویلا,
    Xr_ویلا*                                     ویلا);

XRAPI_ATTR Xr_نتیجہ XRAPI_CALL xr_Convert_ویلا_منزل_Timespec_ویلا_KHR(
    XrInstance                                  instance,
    Xr_ویلا                                      ویلا,
    بنية timespec*                            timespec_ویلا);
#جے_انت /* XR_EXTENSION_PROTOTYPES */
#جے_انت /* !XR_NO_PROTOTYPES */
#جے_انت /* XR_USE_TIMESPEC */

#جے_تعریف_شدہ XR_USE_PLATFORM_ANDROID

// XR_KHR_loader_init_android is a preprocessor guard. Do not pass it to API calls.
#تعریف_کرو XR_KHR_loader_init_android 1
#تعریف_کرو XR_KHR_loader_init_android_SPEC_نسخہ 1
#تعریف_کرو XR_KHR_LOADER_INIT_ANDROID_EXTENSION_NAME "XR_KHR_loader_init_android"
تعريفنوع بنية XrLoaderInitInfoAndroidKHR {
    XrStructureType             type;
    ثابت فراغ* XR_MAY_ALIAS    اگلا;
    فراغ* XR_MAY_ALIAS          applicationVM;
    فراغ* XR_MAY_ALIAS          applicationContext;
} XrLoaderInitInfoAndroidKHR;

#جے_انت /* XR_USE_PLATFORM_ANDROID */

#جے_تعریف_شدہ XR_USE_GRAPHICS_API_VULKAN

// XR_KHR_vulkan_enable2 is a preprocessor guard. Do not pass it to API calls.
#تعریف_کرو XR_KHR_vulkan_enable2 1
#تعریف_کرو XR_KHR_vulkan_enable2_SPEC_نسخہ 4
#تعریف_کرو XR_KHR_VULKAN_ENABLE2_EXTENSION_NAME "XR_KHR_vulkan_enable2"
تعريفنوع XrFlags64 XrVulkanInstanceCreateFlagsKHR;

// Flag bits for XrVulkanInstanceCreateFlagsKHR

تعريفنوع XrFlags64 XrVulkanDeviceCreateFlagsKHR;

// Flag bits for XrVulkanDeviceCreateFlagsKHR

تعريفنوع بنية XrVulkanInstanceCreateInfoKHR {
    XrStructureType                   type;
    ثابت فراغ* XR_MAY_ALIAS          اگلا;
    XrSystemId                        systemId;
    XrVulkanInstanceCreateFlagsKHR    createFlags;
    PFN_vkGetInstanceProcAddr         pfnGetInstanceProcAddr;
    ثابت VkInstanceCreateInfo*       vulkanCreateInfo;
    ثابت Vk_ونڈ_Callbacks*      vulkanAllocator;
} XrVulkanInstanceCreateInfoKHR;

تعريفنوع بنية XrVulkanDeviceCreateInfoKHR {
    XrStructureType                 type;
    ثابت فراغ* XR_MAY_ALIAS        اگلا;
    XrSystemId                      systemId;
    XrVulkanDeviceCreateFlagsKHR    createFlags;
    PFN_vkGetInstanceProcAddr       pfnGetInstanceProcAddr;
    VkPhysicalDevice                vulkanPhysicalDevice;
    ثابت VkDeviceCreateInfo*       vulkanCreateInfo;
    ثابت Vk_ونڈ_Callbacks*    vulkanAllocator;
} XrVulkanDeviceCreateInfoKHR;

تعريفنوع XrGraphicsBindingVulkanKHR XrGraphicsBindingVulkan2KHR;

تعريفنوع بنية XrVulkanGraphicsDeviceGetInfoKHR {
    XrStructureType             type;
    ثابت فراغ* XR_MAY_ALIAS    اگلا;
    XrSystemId                  systemId;
    VkInstance                  vulkanInstance;
} XrVulkanGraphicsDeviceGetInfoKHR;

تعريفنوع XrSwapchainImageVulkanKHR XrSwapchainImageVulkan2KHR;

تعريفنوع XrGraphicsRequirementsVulkanKHR XrGraphicsRequirementsVulkan2KHR;

تعريفنوع Xr_نتیجہ (XRAPI_PTR *PFN_xrCreateVulkanInstanceKHR)(XrInstance instance, ثابت XrVulkanInstanceCreateInfoKHR* createInfo, VkInstance* vulkanInstance, Vk_نتیجہ* vulkan_نتیجہ);
تعريفنوع Xr_نتیجہ (XRAPI_PTR *PFN_xrCreateVulkanDeviceKHR)(XrInstance instance, ثابت XrVulkanDeviceCreateInfoKHR* createInfo, VkDevice* vulkanDevice, Vk_نتیجہ* vulkan_نتیجہ);
تعريفنوع Xr_نتیجہ (XRAPI_PTR *PFN_xrGetVulkanGraphicsDevice2KHR)(XrInstance instance, ثابت XrVulkanGraphicsDeviceGetInfoKHR* getInfo, VkPhysicalDevice* vulkanPhysicalDevice);
تعريفنوع Xr_نتیجہ (XRAPI_PTR *PFN_xrGetVulkanGraphicsRequirements2KHR)(XrInstance instance, XrSystemId systemId, XrGraphicsRequirementsVulkanKHR* graphicsRequirements);

#جے_بنا_تعریف XR_NO_PROTOTYPES
#جے_تعریف_شدہ XR_EXTENSION_PROTOTYPES
XRAPI_ATTR Xr_نتیجہ XRAPI_CALL xrCreateVulkanInstanceKHR(
    XrInstance                                  instance,
    ثابت XrVulkanInstanceCreateInfoKHR*        createInfo,
    VkInstance*                                 vulkanInstance,
    Vk_نتیجہ*                                   vulkan_نتیجہ);

XRAPI_ATTR Xr_نتیجہ XRAPI_CALL xrCreateVulkanDeviceKHR(
    XrInstance                                  instance,
    ثابت XrVulkanDeviceCreateInfoKHR*          createInfo,
    VkDevice*                                   vulkanDevice,
    Vk_نتیجہ*                                   vulkan_نتیجہ);

XRAPI_ATTR Xr_نتیجہ XRAPI_CALL xrGetVulkanGraphicsDevice2KHR(
    XrInstance                                  instance,
    ثابت XrVulkanGraphicsDeviceGetInfoKHR*     getInfo,
    VkPhysicalDevice*                           vulkanPhysicalDevice);

XRAPI_ATTR Xr_نتیجہ XRAPI_CALL xrGetVulkanGraphicsRequirements2KHR(
    XrInstance                                  instance,
    XrSystemId                                  systemId,
    XrGraphicsRequirementsVulkanKHR*            graphicsRequirements);
#جے_انت /* XR_EXTENSION_PROTOTYPES */
#جے_انت /* !XR_NO_PROTOTYPES */
#جے_انت /* XR_USE_GRAPHICS_API_VULKAN */

#جے_تعریف_شدہ XR_USE_PLATFORM_EGL

// XR_MNDX_egl_enable is a preprocessor guard. Do not pass it to API calls.
#تعریف_کرو XR_MNDX_egl_enable 1
#تعریف_کرو XR_MNDX_egl_enable_SPEC_نسخہ   2
#تعریف_کرو XR_MNDX_EGL_ENABLE_EXTENSION_NAME "XR_MNDX_egl_enable"
تعريفنوع PFN_xrVoidFunction (*PFN_xr_Egl_Get_Proc_پتہ_MNDX)(ثابت حرف *name);
// XrGraphicsBindingEGLMNDX extends XrSessionCreateInfo
تعريفنوع بنية XrGraphicsBindingEGLMNDX {
    XrStructureType                type;
    ثابت فراغ* XR_MAY_ALIAS       اگلا;
    PFN_xr_Egl_Get_Proc_پتہ_MNDX    get_Proc_پتہ;
    EGLDisplay                     display;
    EGLConfig                      config;
    EGLContext                     context;
} XrGraphicsBindingEGLMNDX;

#جے_انت /* XR_USE_PLATFORM_EGL */

#جے_تعریف_شدہ XR_USE_PLATFORM_WIN32

// XR_MSFT_perception_anchor_interop is a preprocessor guard. Do not pass it to API calls.
#تعریف_کرو XR_MSFT_perception_anchor_interop 1
#تعریف_کرو XR_MSFT_perception_anchor_interop_SPEC_نسخہ 1
#تعریف_کرو XR_MSFT_PERCEPTION_ANCHOR_INTEROP_EXTENSION_NAME "XR_MSFT_perception_anchor_interop"
تعريفنوع Xr_نتیجہ (XRAPI_PTR *PFN_xrCreateSpatialAnchorFromPerceptionAnchorMSFT)(XrSession session, IUnknown* perceptionAnchor, XrSpatialAnchorMSFT* anchor);
تعريفنوع Xr_نتیجہ (XRAPI_PTR *PFN_xrTryGetPerceptionAnchorFromSpatialAnchorMSFT)(XrSession session, XrSpatialAnchorMSFT anchor, IUnknown** perceptionAnchor);

#جے_بنا_تعریف XR_NO_PROTOTYPES
#جے_تعریف_شدہ XR_EXTENSION_PROTOTYPES
XRAPI_ATTR Xr_نتیجہ XRAPI_CALL xrCreateSpatialAnchorFromPerceptionAnchorMSFT(
    XrSession                                   session,
    IUnknown*                                   perceptionAnchor,
    XrSpatialAnchorMSFT*                        anchor);

XRAPI_ATTR Xr_نتیجہ XRAPI_CALL xrTryGetPerceptionAnchorFromSpatialAnchorMSFT(
    XrSession                                   session,
    XrSpatialAnchorMSFT                         anchor,
    IUnknown**                                  perceptionAnchor);
#جے_انت /* XR_EXTENSION_PROTOTYPES */
#جے_انت /* !XR_NO_PROTOTYPES */
#جے_انت /* XR_USE_PLATFORM_WIN32 */

#جے_تعریف_شدہ XR_USE_PLATFORM_WIN32

// XR_MSFT_holographic_window_attachment is a preprocessor guard. Do not pass it to API calls.
#تعریف_کرو XR_MSFT_holographic_کھڑکی_attachment 1
#تعریف_کرو XR_MSFT_holographic_کھڑکی_attachment_SPEC_نسخہ 1
#تعریف_کرو XR_MSFT_HOLOGRAPHIC_کھڑکی_ATTACHMENT_EXTENSION_NAME "XR_MSFT_holographic_window_attachment"
#جے_تعریف_شدہ XR_USE_PLATFORM_WIN32
// XrHolographicWindowAttachmentMSFT extends XrSessionCreateInfo
تعريفنوع بنية Xr_Holographic_کھڑکی_Attachment_MSFT {
    XrStructureType             type;
    ثابت فراغ* XR_MAY_ALIAS    اگلا;
    IUnknown*                   holographicSpace;
    IUnknown*                   core_کھڑکی;
} Xr_Holographic_کھڑکی_Attachment_MSFT;
#جے_انت // XR_USE_PLATFORM_WIN32

#جے_انت /* XR_USE_PLATFORM_WIN32 */

#جے_تعریف_شدہ XR_USE_PLATFORM_ANDROID

// XR_FB_android_surface_swapchain_create is a preprocessor guard. Do not pass it to API calls.
#تعریف_کرو XR_FB_android_surface_swapchain_create 1
#تعریف_کرو XR_FB_android_surface_swapchain_create_SPEC_نسخہ 1
#تعریف_کرو XR_FB_ANDROID_SURFACE_SWAPCHAIN_CREATE_EXTENSION_NAME "XR_FB_android_surface_swapchain_create"
تعريفنوع XrFlags64 XrAndroidSurfaceSwapchainFlagsFB;

// Flag bits for XrAndroidSurfaceSwapchainFlagsFB
ساكن ثابت XrAndroidSurfaceSwapchainFlagsFB XR_ANDROID_SURFACE_SWAPCHAIN_SYNCHRONOUS_ثنائی_ہندسہ_FB = 0x00000001;
ساكن ثابت XrAndroidSurfaceSwapchainFlagsFB XR_ANDROID_SURFACE_SWAPCHAIN_USE_TIMESTAMPS_ثنائی_ہندسہ_FB = 0x00000002;

#جے_تعریف_شدہ XR_USE_PLATFORM_ANDROID
// XrAndroidSurfaceSwapchainCreateInfoFB extends XrSwapchainCreateInfo
تعريفنوع بنية XrAndroidSurfaceSwapchainCreateInfoFB {
    XrStructureType                     type;
    ثابت فراغ* XR_MAY_ALIAS            اگلا;
    XrAndroidSurfaceSwapchainFlagsFB    createFlags;
} XrAndroidSurfaceSwapchainCreateInfoFB;
#جے_انت // XR_USE_PLATFORM_ANDROID

#جے_انت /* XR_USE_PLATFORM_ANDROID */

#جے_تعریف_شدہ XR_USE_PLATFORM_ML

// XR_ML_compat is a preprocessor guard. Do not pass it to API calls.
#تعریف_کرو XR_ML_compat 1
#تعریف_کرو XR_ML_compat_SPEC_نسخہ         1
#تعریف_کرو XR_ML_COMPAT_EXTENSION_NAME       "XR_ML_compat"
تعريفنوع بنية XrCoordinateSpaceCreateInfoML {
    XrStructureType             type;
    ثابت فراغ* XR_MAY_ALIAS    اگلا;
    MLCoordinate_چوکھٹا_UID        cfuid;
    XrPosef                     pose_وچ_Coordinate_Space;
} XrCoordinateSpaceCreateInfoML;

تعريفنوع Xr_نتیجہ (XRAPI_PTR *PFN_xr_Create_Space_From_Coordinate_چوکھٹا_UIDML)(XrSession session, ثابت XrCoordinateSpaceCreateInfoML *createInfo, XrSpace* space);

#جے_بنا_تعریف XR_NO_PROTOTYPES
#جے_تعریف_شدہ XR_EXTENSION_PROTOTYPES
XRAPI_ATTR Xr_نتیجہ XRAPI_CALL xr_Create_Space_From_Coordinate_چوکھٹا_UIDML(
    XrSession                                   session,
    ثابت XrCoordinateSpaceCreateInfoML *       createInfo,
    XrSpace*                                    space);
#جے_انت /* XR_EXTENSION_PROTOTYPES */
#جے_انت /* !XR_NO_PROTOTYPES */
#جے_انت /* XR_USE_PLATFORM_ML */

#جے_تعریف_شدہ XR_USE_PLATFORM_WIN32

// XR_OCULUS_audio_device_guid is a preprocessor guard. Do not pass it to API calls.
#تعریف_کرو XR_OCULUS_audio_device_guid 1
#تعریف_کرو XR_OCULUS_audio_device_guid_SPEC_نسخہ 1
#تعریف_کرو XR_OCULUS_AUDIO_DEVICE_GUID_EXTENSION_NAME "XR_OCULUS_audio_device_guid"
#تعریف_کرو XR_MAX_AUDIO_DEVICE_STR_ناپ_OCULUS 128
تعريفنوع Xr_نتیجہ (XRAPI_PTR *PFN_xrGetAudioOutputDeviceGuidOculus)(XrInstance instance, wchar_t بفر_2[XR_MAX_AUDIO_DEVICE_STR_ناپ_OCULUS]);
تعريفنوع Xr_نتیجہ (XRAPI_PTR *PFN_xr_Get_Audio_داخلہ_Device_Guid_Oculus)(XrInstance instance, wchar_t بفر_2[XR_MAX_AUDIO_DEVICE_STR_ناپ_OCULUS]);

#جے_بنا_تعریف XR_NO_PROTOTYPES
#جے_تعریف_شدہ XR_EXTENSION_PROTOTYPES
XRAPI_ATTR Xr_نتیجہ XRAPI_CALL xrGetAudioOutputDeviceGuidOculus(
    XrInstance                                  instance,
    wchar_t                                     بفر_2[XR_MAX_AUDIO_DEVICE_STR_ناپ_OCULUS]);

XRAPI_ATTR Xr_نتیجہ XRAPI_CALL xr_Get_Audio_داخلہ_Device_Guid_Oculus(
    XrInstance                                  instance,
    wchar_t                                     بفر_2[XR_MAX_AUDIO_DEVICE_STR_ناپ_OCULUS]);
#جے_انت /* XR_EXTENSION_PROTOTYPES */
#جے_انت /* !XR_NO_PROTOTYPES */
#جے_انت /* XR_USE_PLATFORM_WIN32 */

#جے_تعریف_شدہ XR_USE_GRAPHICS_API_VULKAN

// XR_FB_foveation_vulkan is a preprocessor guard. Do not pass it to API calls.
#تعریف_کرو XR_FB_foveation_vulkan 1
#تعریف_کرو XR_FB_foveation_vulkan_SPEC_نسخہ 1
#تعریف_کرو XR_FB_FOVEATION_VULKAN_EXTENSION_NAME "XR_FB_foveation_vulkan"
// XrSwapchainImageFoveationVulkanFB extends XrSwapchainImageVulkanKHR
تعريفنوع بنية XrSwapchainImageFoveationVulkanFB {
    XrStructureType       type;
    فراغ* XR_MAY_ALIAS    اگلا;
    VkImage               image;
    uint32_t              چوڑائی;
    uint32_t              اچائی;
} XrSwapchainImageFoveationVulkanFB;

#جے_انت /* XR_USE_GRAPHICS_API_VULKAN */

#جے_تعریف_شدہ XR_USE_PLATFORM_ANDROID

// XR_FB_swapchain_update_state_android_surface is a preprocessor guard. Do not pass it to API calls.
#تعریف_کرو XR_FB_swapchain_update_state_android_surface 1
#تعریف_کرو XR_FB_swapchain_update_state_android_surface_SPEC_نسخہ 1
#تعریف_کرو XR_FB_SWAPCHAIN_UPDATE_STATE_ANDROID_SURFACE_EXTENSION_NAME "XR_FB_swapchain_update_state_android_surface"
#جے_تعریف_شدہ XR_USE_PLATFORM_ANDROID
تعريفنوع بنية XrSwapchainStateAndroidSurfaceDimensionsFB {
    XrStructureType       type;
    فراغ* XR_MAY_ALIAS    اگلا;
    uint32_t              چوڑائی;
    uint32_t              اچائی;
} XrSwapchainStateAndroidSurfaceDimensionsFB;
#جے_انت // XR_USE_PLATFORM_ANDROID

#جے_انت /* XR_USE_PLATFORM_ANDROID */

#جے_تعریف_شدہ XR_USE_GRAPHICS_API_OPENGL_ES

// XR_FB_swapchain_update_state_opengl_es is a preprocessor guard. Do not pass it to API calls.
#تعریف_کرو XR_FB_swapchain_update_state_opengl_es 1
#تعریف_کرو XR_FB_swapchain_update_state_opengl_es_SPEC_نسخہ 1
#تعریف_کرو XR_FB_SWAPCHAIN_UPDATE_STATE_OPENGL_ES_EXTENSION_NAME "XR_FB_swapchain_update_state_opengl_es"
#جے_تعریف_شدہ XR_USE_GRAPHICS_API_OPENGL_ES
تعريفنوع بنية XrSwapchainStateSamplerOpenGLESFB {
    XrStructureType       type;
    فراغ* XR_MAY_ALIAS    اگلا;
    EGLenum               minFilter;
    EGLenum               magFilter;
    EGLenum               wrap_منوال_S;
    EGLenum               wrap_منوال_T;
    EGLenum               swizzleRed;
    EGLenum               swizzleGreen;
    EGLenum               swizzleBlue;
    EGLenum               swizzleAlpha;
    عائم                 maxAnisotropy;
    XrColor4f             borderColor;
} XrSwapchainStateSamplerOpenGLESFB;
#جے_انت // XR_USE_GRAPHICS_API_OPENGL_ES

#جے_انت /* XR_USE_GRAPHICS_API_OPENGL_ES */

#جے_تعریف_شدہ XR_USE_GRAPHICS_API_VULKAN

// XR_FB_swapchain_update_state_vulkan is a preprocessor guard. Do not pass it to API calls.
#تعریف_کرو XR_FB_swapchain_update_state_vulkan 1
#تعریف_کرو XR_FB_swapchain_update_state_vulkan_SPEC_نسخہ 1
#تعریف_کرو XR_FB_SWAPCHAIN_UPDATE_STATE_VULKAN_EXTENSION_NAME "XR_FB_swapchain_update_state_vulkan"
#جے_تعریف_شدہ XR_USE_GRAPHICS_API_VULKAN
تعريفنوع بنية XrSwapchainStateSamplerVulkanFB {
    XrStructureType         type;
    فراغ* XR_MAY_ALIAS      اگلا;
    VkFilter                minFilter;
    VkFilter                magFilter;
    Vk_Sampler_Mipmap_منوال     mipmap_منوال;
    Vk_Sampler_پتہ_منوال    wrap_منوال_S;
    Vk_Sampler_پتہ_منوال    wrap_منوال_T;
    VkComponentSwizzle      swizzleRed;
    VkComponentSwizzle      swizzleGreen;
    VkComponentSwizzle      swizzleBlue;
    VkComponentSwizzle      swizzleAlpha;
    عائم                   maxAnisotropy;
    XrColor4f               borderColor;
} XrSwapchainStateSamplerVulkanFB;
#جے_انت // XR_USE_GRAPHICS_API_VULKAN

#جے_انت /* XR_USE_GRAPHICS_API_VULKAN */

#جے_تعریف_شدہ XR_USE_GRAPHICS_API_VULKAN

// XR_META_vulkan_swapchain_create_info is a preprocessor guard. Do not pass it to API calls.
#تعریف_کرو XR_META_vulkan_swapchain_create_info 1
#تعریف_کرو XR_META_vulkan_swapchain_create_info_SPEC_نسخہ 1
#تعریف_کرو XR_META_VULKAN_SWAPCHAIN_CREATE_INFO_EXTENSION_NAME "XR_META_vulkan_swapchain_create_info"
// XrVulkanSwapchainCreateInfoMETA extends XrSwapchainCreateInfo
تعريفنوع بنية XrVulkanSwapchainCreateInfoMETA {
    XrStructureType             type;
    ثابت فراغ* XR_MAY_ALIAS    اگلا;
    VkImageCreateFlags          additionalCreateFlags;
    VkImageUsageFlags           additionalUsageFlags;
} XrVulkanSwapchainCreateInfoMETA;

#جے_انت /* XR_USE_GRAPHICS_API_VULKAN */

#جے_تعریف_شدہ XR_USE_PLATFORM_ANDROID

// XR_ANDROID_anchor_sharing_export is a preprocessor guard. Do not pass it to API calls.
#تعریف_کرو XR_ANDROID_anchor_sharing_export 1
#تعریف_کرو XR_ANDROID_anchor_sharing_export_SPEC_نسخہ 1
#تعریف_کرو XR_ANDROID_ANCHOR_SHARING_EXPORT_EXTENSION_NAME "XR_ANDROID_anchor_sharing_export"
تعريفنوع بنية XrAnchorSharingInfoANDROID {
    XrStructureType             type;
    ثابت فراغ* XR_MAY_ALIAS    اگلا;
    XrSpace                     anchor;
} XrAnchorSharingInfoANDROID;

تعريفنوع بنية XrAnchorSharingTokenANDROID {
    XrStructureType       type;
    فراغ* XR_MAY_ALIAS    اگلا;
    بنية AIBinder*      token;
} XrAnchorSharingTokenANDROID;

// XrSystemAnchorSharingExportPropertiesANDROID extends XrSystemProperties
تعريفنوع بنية XrSystemAnchorSharingExportPropertiesANDROID {
    XrStructureType       type;
    فراغ* XR_MAY_ALIAS    اگلا;
    XrBool32              supportsAnchorSharingExport;
} XrSystemAnchorSharingExportPropertiesANDROID;

تعريفنوع Xr_نتیجہ (XRAPI_PTR *PFN_xrShareAnchorANDROID)(XrSession session, ثابت XrAnchorSharingInfoANDROID* sharingInfo, XrAnchorSharingTokenANDROID* anchorToken);
تعريفنوع Xr_نتیجہ (XRAPI_PTR *PFN_xrUnshareAnchorANDROID)(XrSession session, XrSpace anchor);

#جے_بنا_تعریف XR_NO_PROTOTYPES
#جے_تعریف_شدہ XR_EXTENSION_PROTOTYPES
XRAPI_ATTR Xr_نتیجہ XRAPI_CALL xrShareAnchorANDROID(
    XrSession                                   session,
    ثابت XrAnchorSharingInfoANDROID*           sharingInfo,
    XrAnchorSharingTokenANDROID*                anchorToken);

XRAPI_ATTR Xr_نتیجہ XRAPI_CALL xrUnshareAnchorANDROID(
    XrSession                                   session,
    XrSpace                                     anchor);
#جے_انت /* XR_EXTENSION_PROTOTYPES */
#جے_انت /* !XR_NO_PROTOTYPES */
#جے_انت /* XR_USE_PLATFORM_ANDROID */

#جے_تعریف_شدہ __cplusplus
}
#جے_انت

#جے_انت
