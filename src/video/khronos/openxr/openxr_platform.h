#جيڪڏهن_وصف_نه_ٿيل OPENXR_PLATFORM_H_
#وصف_ڪريو OPENXR_PLATFORM_H_ 1

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

#جيڪڏهن_وصف_ٿيل __cplusplus
خارجي "C" {
#جيڪڏهن_پورو


#جيڪڏهن_وصف_ٿيل XR_USE_PLATFORM_ANDROID

// XR_KHR_android_thread_settings is a preprocessor guard. Do not pass it to API calls.
#وصف_ڪريو XR_KHR_android_thread_settings 1
#وصف_ڪريو XR_KHR_android_thread_settings_SPEC_نسخو 6
#وصف_ڪريو XR_KHR_ANDROID_THREAD_SETTINGS_EXTENSION_NAME "XR_KHR_android_thread_settings"

تعريفنوع تعداد XrAndroidThreadTypeKHR {
    XR_ANDROID_THREAD_TYPE_APPLICATION_MAIN_KHR = 1,
    XR_ANDROID_THREAD_TYPE_APPLICATION_ڪم_ڪندڙ_KHR = 2,
    XR_ANDROID_THREAD_TYPE_RENDERER_MAIN_KHR = 3,
    XR_ANDROID_THREAD_TYPE_RENDERER_ڪم_ڪندڙ_KHR = 4,
    XR_ANDROID_THREAD_TYPE_MAX_ENUM_KHR = 0x7FFFFFFF
} XrAndroidThreadTypeKHR;
تعريفنوع Xr_نتيجو (XRAPI_PTR *PFN_xr_سيٽ_Android_Application_Thread_KHR)(XrSession session, XrAndroidThreadTypeKHR threadType, uint32_t threadId);

#جيڪڏهن_وصف_نه_ٿيل XR_NO_PROTOTYPES
#جيڪڏهن_وصف_ٿيل XR_EXTENSION_PROTOTYPES
XRAPI_ATTR Xr_نتيجو XRAPI_CALL xr_سيٽ_Android_Application_Thread_KHR(
    XrSession                                   session,
    XrAndroidThreadTypeKHR                      threadType,
    uint32_t                                    threadId);
#جيڪڏهن_پورو /* XR_EXTENSION_PROTOTYPES */
#جيڪڏهن_پورو /* !XR_NO_PROTOTYPES */
#جيڪڏهن_پورو /* XR_USE_PLATFORM_ANDROID */

#جيڪڏهن_وصف_ٿيل XR_USE_PLATFORM_ANDROID

// XR_KHR_android_surface_swapchain is a preprocessor guard. Do not pass it to API calls.
#وصف_ڪريو XR_KHR_android_surface_swapchain 1
#وصف_ڪريو XR_KHR_android_surface_swapchain_SPEC_نسخو 4
#وصف_ڪريو XR_KHR_ANDROID_SURFACE_SWAPCHAIN_EXTENSION_NAME "XR_KHR_android_surface_swapchain"
تعريفنوع Xr_نتيجو (XRAPI_PTR *PFN_xrCreateSwapchainAndroidSurfaceKHR)(XrSession session, ثابت XrSwapchainCreateInfo* info, XrSwapchain* swapchain, jobject* surface);

#جيڪڏهن_وصف_نه_ٿيل XR_NO_PROTOTYPES
#جيڪڏهن_وصف_ٿيل XR_EXTENSION_PROTOTYPES
XRAPI_ATTR Xr_نتيجو XRAPI_CALL xrCreateSwapchainAndroidSurfaceKHR(
    XrSession                                   session,
    ثابت XrSwapchainCreateInfo*                info,
    XrSwapchain*                                swapchain,
    jobject*                                    surface);
#جيڪڏهن_پورو /* XR_EXTENSION_PROTOTYPES */
#جيڪڏهن_پورو /* !XR_NO_PROTOTYPES */
#جيڪڏهن_پورو /* XR_USE_PLATFORM_ANDROID */

#جيڪڏهن_وصف_ٿيل XR_USE_PLATFORM_ANDROID

// XR_KHR_android_create_instance is a preprocessor guard. Do not pass it to API calls.
#وصف_ڪريو XR_KHR_android_create_instance 1
#وصف_ڪريو XR_KHR_android_create_instance_SPEC_نسخو 3
#وصف_ڪريو XR_KHR_ANDROID_CREATE_INSTANCE_EXTENSION_NAME "XR_KHR_android_create_instance"
// XrInstanceCreateInfoAndroidKHR extends XrInstanceCreateInfo
تعريفنوع بنية XrInstanceCreateInfoAndroidKHR {
    XrStructureType             type;
    ثابت فراغ* XR_MAY_ALIAS    ايندڙ;
    فراغ* XR_MAY_ALIAS          applicationVM;
    فراغ* XR_MAY_ALIAS          applicationActivity;
} XrInstanceCreateInfoAndroidKHR;

#جيڪڏهن_پورو /* XR_USE_PLATFORM_ANDROID */

#جيڪڏهن_وصف_ٿيل XR_USE_GRAPHICS_API_VULKAN

// XR_KHR_vulkan_swapchain_format_list is a preprocessor guard. Do not pass it to API calls.
#وصف_ڪريو XR_KHR_vulkan_swapchain_format_list 1
#وصف_ڪريو XR_KHR_vulkan_swapchain_format_list_SPEC_نسخو 5
#وصف_ڪريو XR_KHR_VULKAN_SWAPCHAIN_FORMAT_LIST_EXTENSION_NAME "XR_KHR_vulkan_swapchain_format_list"
// XrVulkanSwapchainFormatListCreateInfoKHR extends XrSwapchainCreateInfo
تعريفنوع بنية XrVulkanSwapchainFormatListCreateInfoKHR {
    XrStructureType             type;
    ثابت فراغ* XR_MAY_ALIAS    ايندڙ;
    uint32_t                    view_Format_ڳڻپ;
    ثابت VkFormat*             viewFormats;
} XrVulkanSwapchainFormatListCreateInfoKHR;

#جيڪڏهن_پورو /* XR_USE_GRAPHICS_API_VULKAN */

#جيڪڏهن_وصف_ٿيل XR_USE_GRAPHICS_API_OPENGL

// XR_KHR_opengl_enable is a preprocessor guard. Do not pass it to API calls.
#وصف_ڪريو XR_KHR_opengl_enable 1
#وصف_ڪريو XR_KHR_opengl_enable_SPEC_نسخو 12
#وصف_ڪريو XR_KHR_OPENGL_ENABLE_EXTENSION_NAME "XR_KHR_opengl_enable"
#جيڪڏهن_وصف_ٿيل XR_USE_PLATFORM_WIN32
// XrGraphicsBindingOpenGLWin32KHR extends XrSessionCreateInfo
تعريفنوع بنية XrGraphicsBindingOpenGLWin32KHR {
    XrStructureType             type;
    ثابت فراغ* XR_MAY_ALIAS    ايندڙ;
    HDC                         hDC;
    HGLRC                       hGLRC;
} XrGraphicsBindingOpenGLWin32KHR;
#جيڪڏهن_پورو // XR_USE_PLATFORM_WIN32

#جيڪڏهن_وصف_ٿيل XR_USE_PLATFORM_XLIB
// XrGraphicsBindingOpenGLXlibKHR extends XrSessionCreateInfo
تعريفنوع بنية XrGraphicsBindingOpenGLXlibKHR {
    XrStructureType             type;
    ثابت فراغ* XR_MAY_ALIAS    ايندڙ;
    Display*                    xDisplay;
    uint32_t                    visualid;
    GLXFBConfig                 glxFBConfig;
    GLXDrawable                 glxDrawable;
    GLXContext                  glxContext;
} XrGraphicsBindingOpenGLXlibKHR;
#جيڪڏهن_پورو // XR_USE_PLATFORM_XLIB

#جيڪڏهن_وصف_ٿيل XR_USE_PLATFORM_XCB
// XrGraphicsBindingOpenGLXcbKHR extends XrSessionCreateInfo
تعريفنوع بنية XrGraphicsBindingOpenGLXcbKHR {
    XrStructureType             type;
    ثابت فراغ* XR_MAY_ALIAS    ايندڙ;
    xcb_connection_t*           connection;
    uint32_t                    screen_عدد;
    xcb_glx_fbconfig_t          fbconfigid;
    xcb_visualid_t              visualid;
    xcb_glx_drawable_t          glxDrawable;
    xcb_glx_context_t           glxContext;
} XrGraphicsBindingOpenGLXcbKHR;
#جيڪڏهن_پورو // XR_USE_PLATFORM_XCB

#جيڪڏهن_وصف_ٿيل XR_USE_PLATFORM_WAYLAND
// XrGraphicsBindingOpenGLWaylandKHR extends XrSessionCreateInfo
تعريفنوع بنية XrGraphicsBindingOpenGLWaylandKHR {
    XrStructureType             type;
    ثابت فراغ* XR_MAY_ALIAS    ايندڙ;
    بنية wl_display*          display;
} XrGraphicsBindingOpenGLWaylandKHR;
#جيڪڏهن_پورو // XR_USE_PLATFORM_WAYLAND

تعريفنوع بنية XrSwapchainImageOpenGLKHR {
    XrStructureType       type;
    فراغ* XR_MAY_ALIAS    ايندڙ;
    uint32_t              image;
} XrSwapchainImageOpenGLKHR;

تعريفنوع بنية XrGraphicsRequirementsOpenGLKHR {
    XrStructureType       type;
    فراغ* XR_MAY_ALIAS    ايندڙ;
    Xr_نسخو             min_Api_نسخو_Supported;
    Xr_نسخو             max_Api_نسخو_Supported;
} XrGraphicsRequirementsOpenGLKHR;

تعريفنوع Xr_نتيجو (XRAPI_PTR *PFN_xrGetOpenGLGraphicsRequirementsKHR)(XrInstance instance, XrSystemId systemId, XrGraphicsRequirementsOpenGLKHR* graphicsRequirements);

#جيڪڏهن_وصف_نه_ٿيل XR_NO_PROTOTYPES
#جيڪڏهن_وصف_ٿيل XR_EXTENSION_PROTOTYPES
XRAPI_ATTR Xr_نتيجو XRAPI_CALL xrGetOpenGLGraphicsRequirementsKHR(
    XrInstance                                  instance,
    XrSystemId                                  systemId,
    XrGraphicsRequirementsOpenGLKHR*            graphicsRequirements);
#جيڪڏهن_پورو /* XR_EXTENSION_PROTOTYPES */
#جيڪڏهن_پورو /* !XR_NO_PROTOTYPES */
#جيڪڏهن_پورو /* XR_USE_GRAPHICS_API_OPENGL */

#جيڪڏهن_وصف_ٿيل XR_USE_GRAPHICS_API_OPENGL_ES

// XR_KHR_opengl_es_enable is a preprocessor guard. Do not pass it to API calls.
#وصف_ڪريو XR_KHR_opengl_es_enable 1
#وصف_ڪريو XR_KHR_opengl_es_enable_SPEC_نسخو 10
#وصف_ڪريو XR_KHR_OPENGL_ES_ENABLE_EXTENSION_NAME "XR_KHR_opengl_es_enable"
#جيڪڏهن_وصف_ٿيل XR_USE_PLATFORM_ANDROID
// XrGraphicsBindingOpenGLESAndroidKHR extends XrSessionCreateInfo
تعريفنوع بنية XrGraphicsBindingOpenGLESAndroidKHR {
    XrStructureType             type;
    ثابت فراغ* XR_MAY_ALIAS    ايندڙ;
    EGLDisplay                  display;
    EGLConfig                   config;
    EGLContext                  context;
} XrGraphicsBindingOpenGLESAndroidKHR;
#جيڪڏهن_پورو // XR_USE_PLATFORM_ANDROID

تعريفنوع بنية XrSwapchainImageOpenGLESKHR {
    XrStructureType       type;
    فراغ* XR_MAY_ALIAS    ايندڙ;
    uint32_t              image;
} XrSwapchainImageOpenGLESKHR;

تعريفنوع بنية XrGraphicsRequirementsOpenGLESKHR {
    XrStructureType       type;
    فراغ* XR_MAY_ALIAS    ايندڙ;
    Xr_نسخو             min_Api_نسخو_Supported;
    Xr_نسخو             max_Api_نسخو_Supported;
} XrGraphicsRequirementsOpenGLESKHR;

تعريفنوع Xr_نتيجو (XRAPI_PTR *PFN_xrGetOpenGLESGraphicsRequirementsKHR)(XrInstance instance, XrSystemId systemId, XrGraphicsRequirementsOpenGLESKHR* graphicsRequirements);

#جيڪڏهن_وصف_نه_ٿيل XR_NO_PROTOTYPES
#جيڪڏهن_وصف_ٿيل XR_EXTENSION_PROTOTYPES
XRAPI_ATTR Xr_نتيجو XRAPI_CALL xrGetOpenGLESGraphicsRequirementsKHR(
    XrInstance                                  instance,
    XrSystemId                                  systemId,
    XrGraphicsRequirementsOpenGLESKHR*          graphicsRequirements);
#جيڪڏهن_پورو /* XR_EXTENSION_PROTOTYPES */
#جيڪڏهن_پورو /* !XR_NO_PROTOTYPES */
#جيڪڏهن_پورو /* XR_USE_GRAPHICS_API_OPENGL_ES */

#جيڪڏهن_وصف_ٿيل XR_USE_GRAPHICS_API_VULKAN

// XR_KHR_vulkan_enable is a preprocessor guard. Do not pass it to API calls.
#وصف_ڪريو XR_KHR_vulkan_enable 1
#وصف_ڪريو XR_KHR_vulkan_enable_SPEC_نسخو 10
#وصف_ڪريو XR_KHR_VULKAN_ENABLE_EXTENSION_NAME "XR_KHR_vulkan_enable"
// XrGraphicsBindingVulkanKHR extends XrSessionCreateInfo
تعريفنوع بنية XrGraphicsBindingVulkanKHR {
    XrStructureType             type;
    ثابت فراغ* XR_MAY_ALIAS    ايندڙ;
    VkInstance                  instance;
    VkPhysicalDevice            physicalDevice;
    VkDevice                    device;
    uint32_t                    قطار_Family_اشاريو;
    uint32_t                    قطار_اشاريو;
} XrGraphicsBindingVulkanKHR;

تعريفنوع بنية XrSwapchainImageVulkanKHR {
    XrStructureType       type;
    فراغ* XR_MAY_ALIAS    ايندڙ;
    VkImage               image;
} XrSwapchainImageVulkanKHR;

تعريفنوع بنية XrGraphicsRequirementsVulkanKHR {
    XrStructureType       type;
    فراغ* XR_MAY_ALIAS    ايندڙ;
    Xr_نسخو             min_Api_نسخو_Supported;
    Xr_نسخو             max_Api_نسخو_Supported;
} XrGraphicsRequirementsVulkanKHR;

تعريفنوع Xr_نتيجو (XRAPI_PTR *PFN_xrGetVulkanInstanceExtensionsKHR)(XrInstance instance, XrSystemId systemId, uint32_t بفر_صلاحيت_داخلا, uint32_t* بفر_ڳڻپ_Output, حرف* بفر_2);
تعريفنوع Xr_نتيجو (XRAPI_PTR *PFN_xrGetVulkanDeviceExtensionsKHR)(XrInstance instance, XrSystemId systemId, uint32_t بفر_صلاحيت_داخلا, uint32_t* بفر_ڳڻپ_Output, حرف* بفر_2);
تعريفنوع Xr_نتيجو (XRAPI_PTR *PFN_xrGetVulkanGraphicsDeviceKHR)(XrInstance instance, XrSystemId systemId, VkInstance vkInstance, VkPhysicalDevice* vkPhysicalDevice);
تعريفنوع Xr_نتيجو (XRAPI_PTR *PFN_xrGetVulkanGraphicsRequirementsKHR)(XrInstance instance, XrSystemId systemId, XrGraphicsRequirementsVulkanKHR* graphicsRequirements);

#جيڪڏهن_وصف_نه_ٿيل XR_NO_PROTOTYPES
#جيڪڏهن_وصف_ٿيل XR_EXTENSION_PROTOTYPES
XRAPI_ATTR Xr_نتيجو XRAPI_CALL xrGetVulkanInstanceExtensionsKHR(
    XrInstance                                  instance,
    XrSystemId                                  systemId,
    uint32_t                                    بفر_صلاحيت_داخلا,
    uint32_t*                                   بفر_ڳڻپ_Output,
    حرف*                                       بفر_2);

XRAPI_ATTR Xr_نتيجو XRAPI_CALL xrGetVulkanDeviceExtensionsKHR(
    XrInstance                                  instance,
    XrSystemId                                  systemId,
    uint32_t                                    بفر_صلاحيت_داخلا,
    uint32_t*                                   بفر_ڳڻپ_Output,
    حرف*                                       بفر_2);

XRAPI_ATTR Xr_نتيجو XRAPI_CALL xrGetVulkanGraphicsDeviceKHR(
    XrInstance                                  instance,
    XrSystemId                                  systemId,
    VkInstance                                  vkInstance,
    VkPhysicalDevice*                           vkPhysicalDevice);

XRAPI_ATTR Xr_نتيجو XRAPI_CALL xrGetVulkanGraphicsRequirementsKHR(
    XrInstance                                  instance,
    XrSystemId                                  systemId,
    XrGraphicsRequirementsVulkanKHR*            graphicsRequirements);
#جيڪڏهن_پورو /* XR_EXTENSION_PROTOTYPES */
#جيڪڏهن_پورو /* !XR_NO_PROTOTYPES */
#جيڪڏهن_پورو /* XR_USE_GRAPHICS_API_VULKAN */

#جيڪڏهن_وصف_ٿيل XR_USE_GRAPHICS_API_D3D11

// XR_KHR_D3D11_enable is a preprocessor guard. Do not pass it to API calls.
#وصف_ڪريو XR_KHR_D3D11_enable 1
#وصف_ڪريو XR_KHR_D3_D11_enable_SPEC_نسخو  11
#وصف_ڪريو XR_KHR_D3D11_ENABLE_EXTENSION_NAME "XR_KHR_D3D11_enable"
// XrGraphicsBindingD3D11KHR extends XrSessionCreateInfo
تعريفنوع بنية XrGraphicsBindingD3D11KHR {
    XrStructureType             type;
    ثابت فراغ* XR_MAY_ALIAS    ايندڙ;
    ID3D11Device*               device;
} XrGraphicsBindingD3D11KHR;

تعريفنوع بنية XrSwapchainImageD3D11KHR {
     XrStructureType      type;
    فراغ* XR_MAY_ALIAS    ايندڙ;
    ID3D11Texture2D*      texture;
} XrSwapchainImageD3D11KHR;

تعريفنوع بنية XrGraphicsRequirementsD3D11KHR {
    XrStructureType       type;
    فراغ* XR_MAY_ALIAS    ايندڙ;
    LUID                  adapterLuid;
    D3D_FEATURE_LEVEL     minFeatureLevel;
} XrGraphicsRequirementsD3D11KHR;

تعريفنوع Xr_نتيجو (XRAPI_PTR *PFN_xrGetD3D11GraphicsRequirementsKHR)(XrInstance instance, XrSystemId systemId, XrGraphicsRequirementsD3D11KHR* graphicsRequirements);

#جيڪڏهن_وصف_نه_ٿيل XR_NO_PROTOTYPES
#جيڪڏهن_وصف_ٿيل XR_EXTENSION_PROTOTYPES
XRAPI_ATTR Xr_نتيجو XRAPI_CALL xrGetD3D11GraphicsRequirementsKHR(
    XrInstance                                  instance,
    XrSystemId                                  systemId,
    XrGraphicsRequirementsD3D11KHR*             graphicsRequirements);
#جيڪڏهن_پورو /* XR_EXTENSION_PROTOTYPES */
#جيڪڏهن_پورو /* !XR_NO_PROTOTYPES */
#جيڪڏهن_پورو /* XR_USE_GRAPHICS_API_D3D11 */

#جيڪڏهن_وصف_ٿيل XR_USE_GRAPHICS_API_D3D12

// XR_KHR_D3D12_enable is a preprocessor guard. Do not pass it to API calls.
#وصف_ڪريو XR_KHR_D3D12_enable 1
#وصف_ڪريو XR_KHR_D3_D12_enable_SPEC_نسخو  11
#وصف_ڪريو XR_KHR_D3D12_ENABLE_EXTENSION_NAME "XR_KHR_D3D12_enable"
// XrGraphicsBindingD3D12KHR extends XrSessionCreateInfo
تعريفنوع بنية XrGraphicsBindingD3D12KHR {
    XrStructureType             type;
    ثابت فراغ* XR_MAY_ALIAS    ايندڙ;
    ID3D12Device*               device;
    ID3_D12_Command_قطار*         قطار;
} XrGraphicsBindingD3D12KHR;

تعريفنوع بنية XrSwapchainImageD3D12KHR {
     XrStructureType      type;
    فراغ* XR_MAY_ALIAS    ايندڙ;
    ID3D12Resource*       texture;
} XrSwapchainImageD3D12KHR;

تعريفنوع بنية XrGraphicsRequirementsD3D12KHR {
    XrStructureType       type;
    فراغ* XR_MAY_ALIAS    ايندڙ;
    LUID                  adapterLuid;
    D3D_FEATURE_LEVEL     minFeatureLevel;
} XrGraphicsRequirementsD3D12KHR;

تعريفنوع Xr_نتيجو (XRAPI_PTR *PFN_xrGetD3D12GraphicsRequirementsKHR)(XrInstance instance, XrSystemId systemId, XrGraphicsRequirementsD3D12KHR* graphicsRequirements);

#جيڪڏهن_وصف_نه_ٿيل XR_NO_PROTOTYPES
#جيڪڏهن_وصف_ٿيل XR_EXTENSION_PROTOTYPES
XRAPI_ATTR Xr_نتيجو XRAPI_CALL xrGetD3D12GraphicsRequirementsKHR(
    XrInstance                                  instance,
    XrSystemId                                  systemId,
    XrGraphicsRequirementsD3D12KHR*             graphicsRequirements);
#جيڪڏهن_پورو /* XR_EXTENSION_PROTOTYPES */
#جيڪڏهن_پورو /* !XR_NO_PROTOTYPES */
#جيڪڏهن_پورو /* XR_USE_GRAPHICS_API_D3D12 */

#جيڪڏهن_وصف_ٿيل XR_USE_GRAPHICS_API_METAL

// XR_KHR_metal_enable is a preprocessor guard. Do not pass it to API calls.
#وصف_ڪريو XR_KHR_metal_enable 1
#وصف_ڪريو XR_KHR_metal_enable_SPEC_نسخو  3
#وصف_ڪريو XR_KHR_METAL_ENABLE_EXTENSION_NAME "XR_KHR_metal_enable"
// XrGraphicsBindingMetalKHR extends XrSessionCreateInfo
تعريفنوع بنية XrGraphicsBindingMetalKHR {
    XrStructureType             type;
    ثابت فراغ* XR_MAY_ALIAS    ايندڙ;
    فراغ* XR_MAY_ALIAS          command_قطار;
} XrGraphicsBindingMetalKHR;

تعريفنوع بنية XrSwapchainImageMetalKHR {
    XrStructureType       type;
    فراغ* XR_MAY_ALIAS    ايندڙ;
    فراغ* XR_MAY_ALIAS    texture;
} XrSwapchainImageMetalKHR;

تعريفنوع بنية XrGraphicsRequirementsMetalKHR {
    XrStructureType       type;
    فراغ* XR_MAY_ALIAS    ايندڙ;
    فراغ* XR_MAY_ALIAS    metalDevice;
} XrGraphicsRequirementsMetalKHR;

تعريفنوع Xr_نتيجو (XRAPI_PTR *PFN_xrGetMetalGraphicsRequirementsKHR)(XrInstance instance, XrSystemId systemId, XrGraphicsRequirementsMetalKHR* graphicsRequirements);

#جيڪڏهن_وصف_نه_ٿيل XR_NO_PROTOTYPES
#جيڪڏهن_وصف_ٿيل XR_EXTENSION_PROTOTYPES
XRAPI_ATTR Xr_نتيجو XRAPI_CALL xrGetMetalGraphicsRequirementsKHR(
    XrInstance                                  instance,
    XrSystemId                                  systemId,
    XrGraphicsRequirementsMetalKHR*             graphicsRequirements);
#جيڪڏهن_پورو /* XR_EXTENSION_PROTOTYPES */
#جيڪڏهن_پورو /* !XR_NO_PROTOTYPES */
#جيڪڏهن_پورو /* XR_USE_GRAPHICS_API_METAL */

#جيڪڏهن_وصف_ٿيل XR_USE_PLATFORM_WIN32

// XR_KHR_win32_convert_performance_counter_time is a preprocessor guard. Do not pass it to API calls.
#وصف_ڪريو XR_KHR_win32_convert_performance_counter_وقت 1
#وصف_ڪريو XR_KHR_win32_convert_performance_counter_وقت_SPEC_نسخو 1
#وصف_ڪريو XR_KHR_WIN32_CONVERT_PERFORMANCE_COUNTER_وقت_EXTENSION_NAME "XR_KHR_win32_convert_performance_counter_time"
تعريفنوع Xr_نتيجو (XRAPI_PTR *PFN_xr_Convert_Win32_Performance_Counter_منزل_وقت_KHR)(XrInstance instance, ثابت LARGE_INTEGER* performanceCounter, Xr_وقت* وقت);
تعريفنوع Xr_نتيجو (XRAPI_PTR *PFN_xr_Convert_وقت_منزل_Win32_Performance_Counter_KHR)(XrInstance instance, Xr_وقت وقت, LARGE_INTEGER* performanceCounter);

#جيڪڏهن_وصف_نه_ٿيل XR_NO_PROTOTYPES
#جيڪڏهن_وصف_ٿيل XR_EXTENSION_PROTOTYPES
XRAPI_ATTR Xr_نتيجو XRAPI_CALL xr_Convert_Win32_Performance_Counter_منزل_وقت_KHR(
    XrInstance                                  instance,
    ثابت LARGE_INTEGER*                        performanceCounter,
    Xr_وقت*                                     وقت);

XRAPI_ATTR Xr_نتيجو XRAPI_CALL xr_Convert_وقت_منزل_Win32_Performance_Counter_KHR(
    XrInstance                                  instance,
    Xr_وقت                                      وقت,
    LARGE_INTEGER*                              performanceCounter);
#جيڪڏهن_پورو /* XR_EXTENSION_PROTOTYPES */
#جيڪڏهن_پورو /* !XR_NO_PROTOTYPES */
#جيڪڏهن_پورو /* XR_USE_PLATFORM_WIN32 */

#جيڪڏهن_وصف_ٿيل XR_USE_TIMESPEC

// XR_KHR_convert_timespec_time is a preprocessor guard. Do not pass it to API calls.
#وصف_ڪريو XR_KHR_convert_timespec_وقت 1
#وصف_ڪريو XR_KHR_convert_timespec_وقت_SPEC_نسخو 1
#وصف_ڪريو XR_KHR_CONVERT_TIMESPEC_وقت_EXTENSION_NAME "XR_KHR_convert_timespec_time"
تعريفنوع Xr_نتيجو (XRAPI_PTR *PFN_xr_Convert_Timespec_وقت_منزل_وقت_KHR)(XrInstance instance, ثابت بنية timespec* timespec_وقت, Xr_وقت* وقت);
تعريفنوع Xr_نتيجو (XRAPI_PTR *PFN_xr_Convert_وقت_منزل_Timespec_وقت_KHR)(XrInstance instance, Xr_وقت وقت, بنية timespec* timespec_وقت);

#جيڪڏهن_وصف_نه_ٿيل XR_NO_PROTOTYPES
#جيڪڏهن_وصف_ٿيل XR_EXTENSION_PROTOTYPES
XRAPI_ATTR Xr_نتيجو XRAPI_CALL xr_Convert_Timespec_وقت_منزل_وقت_KHR(
    XrInstance                                  instance,
    ثابت بنية timespec*                      timespec_وقت,
    Xr_وقت*                                     وقت);

XRAPI_ATTR Xr_نتيجو XRAPI_CALL xr_Convert_وقت_منزل_Timespec_وقت_KHR(
    XrInstance                                  instance,
    Xr_وقت                                      وقت,
    بنية timespec*                            timespec_وقت);
#جيڪڏهن_پورو /* XR_EXTENSION_PROTOTYPES */
#جيڪڏهن_پورو /* !XR_NO_PROTOTYPES */
#جيڪڏهن_پورو /* XR_USE_TIMESPEC */

#جيڪڏهن_وصف_ٿيل XR_USE_PLATFORM_ANDROID

// XR_KHR_loader_init_android is a preprocessor guard. Do not pass it to API calls.
#وصف_ڪريو XR_KHR_loader_init_android 1
#وصف_ڪريو XR_KHR_loader_init_android_SPEC_نسخو 1
#وصف_ڪريو XR_KHR_LOADER_INIT_ANDROID_EXTENSION_NAME "XR_KHR_loader_init_android"
تعريفنوع بنية XrLoaderInitInfoAndroidKHR {
    XrStructureType             type;
    ثابت فراغ* XR_MAY_ALIAS    ايندڙ;
    فراغ* XR_MAY_ALIAS          applicationVM;
    فراغ* XR_MAY_ALIAS          applicationContext;
} XrLoaderInitInfoAndroidKHR;

#جيڪڏهن_پورو /* XR_USE_PLATFORM_ANDROID */

#جيڪڏهن_وصف_ٿيل XR_USE_GRAPHICS_API_VULKAN

// XR_KHR_vulkan_enable2 is a preprocessor guard. Do not pass it to API calls.
#وصف_ڪريو XR_KHR_vulkan_enable2 1
#وصف_ڪريو XR_KHR_vulkan_enable2_SPEC_نسخو 4
#وصف_ڪريو XR_KHR_VULKAN_ENABLE2_EXTENSION_NAME "XR_KHR_vulkan_enable2"
تعريفنوع XrFlags64 XrVulkanInstanceCreateFlagsKHR;

// Flag bits for XrVulkanInstanceCreateFlagsKHR

تعريفنوع XrFlags64 XrVulkanDeviceCreateFlagsKHR;

// Flag bits for XrVulkanDeviceCreateFlagsKHR

تعريفنوع بنية XrVulkanInstanceCreateInfoKHR {
    XrStructureType                   type;
    ثابت فراغ* XR_MAY_ALIAS          ايندڙ;
    XrSystemId                        systemId;
    XrVulkanInstanceCreateFlagsKHR    createFlags;
    PFN_vkGetInstanceProcAddr         pfnGetInstanceProcAddr;
    ثابت VkInstanceCreateInfo*       vulkanCreateInfo;
    ثابت Vk_ورهاست_Callbacks*      vulkanAllocator;
} XrVulkanInstanceCreateInfoKHR;

تعريفنوع بنية XrVulkanDeviceCreateInfoKHR {
    XrStructureType                 type;
    ثابت فراغ* XR_MAY_ALIAS        ايندڙ;
    XrSystemId                      systemId;
    XrVulkanDeviceCreateFlagsKHR    createFlags;
    PFN_vkGetInstanceProcAddr       pfnGetInstanceProcAddr;
    VkPhysicalDevice                vulkanPhysicalDevice;
    ثابت VkDeviceCreateInfo*       vulkanCreateInfo;
    ثابت Vk_ورهاست_Callbacks*    vulkanAllocator;
} XrVulkanDeviceCreateInfoKHR;

تعريفنوع XrGraphicsBindingVulkanKHR XrGraphicsBindingVulkan2KHR;

تعريفنوع بنية XrVulkanGraphicsDeviceGetInfoKHR {
    XrStructureType             type;
    ثابت فراغ* XR_MAY_ALIAS    ايندڙ;
    XrSystemId                  systemId;
    VkInstance                  vulkanInstance;
} XrVulkanGraphicsDeviceGetInfoKHR;

تعريفنوع XrSwapchainImageVulkanKHR XrSwapchainImageVulkan2KHR;

تعريفنوع XrGraphicsRequirementsVulkanKHR XrGraphicsRequirementsVulkan2KHR;

تعريفنوع Xr_نتيجو (XRAPI_PTR *PFN_xrCreateVulkanInstanceKHR)(XrInstance instance, ثابت XrVulkanInstanceCreateInfoKHR* createInfo, VkInstance* vulkanInstance, Vk_نتيجو* vulkan_نتيجو);
تعريفنوع Xr_نتيجو (XRAPI_PTR *PFN_xrCreateVulkanDeviceKHR)(XrInstance instance, ثابت XrVulkanDeviceCreateInfoKHR* createInfo, VkDevice* vulkanDevice, Vk_نتيجو* vulkan_نتيجو);
تعريفنوع Xr_نتيجو (XRAPI_PTR *PFN_xrGetVulkanGraphicsDevice2KHR)(XrInstance instance, ثابت XrVulkanGraphicsDeviceGetInfoKHR* getInfo, VkPhysicalDevice* vulkanPhysicalDevice);
تعريفنوع Xr_نتيجو (XRAPI_PTR *PFN_xrGetVulkanGraphicsRequirements2KHR)(XrInstance instance, XrSystemId systemId, XrGraphicsRequirementsVulkanKHR* graphicsRequirements);

#جيڪڏهن_وصف_نه_ٿيل XR_NO_PROTOTYPES
#جيڪڏهن_وصف_ٿيل XR_EXTENSION_PROTOTYPES
XRAPI_ATTR Xr_نتيجو XRAPI_CALL xrCreateVulkanInstanceKHR(
    XrInstance                                  instance,
    ثابت XrVulkanInstanceCreateInfoKHR*        createInfo,
    VkInstance*                                 vulkanInstance,
    Vk_نتيجو*                                   vulkan_نتيجو);

XRAPI_ATTR Xr_نتيجو XRAPI_CALL xrCreateVulkanDeviceKHR(
    XrInstance                                  instance,
    ثابت XrVulkanDeviceCreateInfoKHR*          createInfo,
    VkDevice*                                   vulkanDevice,
    Vk_نتيجو*                                   vulkan_نتيجو);

XRAPI_ATTR Xr_نتيجو XRAPI_CALL xrGetVulkanGraphicsDevice2KHR(
    XrInstance                                  instance,
    ثابت XrVulkanGraphicsDeviceGetInfoKHR*     getInfo,
    VkPhysicalDevice*                           vulkanPhysicalDevice);

XRAPI_ATTR Xr_نتيجو XRAPI_CALL xrGetVulkanGraphicsRequirements2KHR(
    XrInstance                                  instance,
    XrSystemId                                  systemId,
    XrGraphicsRequirementsVulkanKHR*            graphicsRequirements);
#جيڪڏهن_پورو /* XR_EXTENSION_PROTOTYPES */
#جيڪڏهن_پورو /* !XR_NO_PROTOTYPES */
#جيڪڏهن_پورو /* XR_USE_GRAPHICS_API_VULKAN */

#جيڪڏهن_وصف_ٿيل XR_USE_PLATFORM_EGL

// XR_MNDX_egl_enable is a preprocessor guard. Do not pass it to API calls.
#وصف_ڪريو XR_MNDX_egl_enable 1
#وصف_ڪريو XR_MNDX_egl_enable_SPEC_نسخو   2
#وصف_ڪريو XR_MNDX_EGL_ENABLE_EXTENSION_NAME "XR_MNDX_egl_enable"
تعريفنوع PFN_xrVoidFunction (*PFN_xr_Egl_Get_Proc_پتو_MNDX)(ثابت حرف *name);
// XrGraphicsBindingEGLMNDX extends XrSessionCreateInfo
تعريفنوع بنية XrGraphicsBindingEGLMNDX {
    XrStructureType                type;
    ثابت فراغ* XR_MAY_ALIAS       ايندڙ;
    PFN_xr_Egl_Get_Proc_پتو_MNDX    get_Proc_پتو;
    EGLDisplay                     display;
    EGLConfig                      config;
    EGLContext                     context;
} XrGraphicsBindingEGLMNDX;

#جيڪڏهن_پورو /* XR_USE_PLATFORM_EGL */

#جيڪڏهن_وصف_ٿيل XR_USE_PLATFORM_WIN32

// XR_MSFT_perception_anchor_interop is a preprocessor guard. Do not pass it to API calls.
#وصف_ڪريو XR_MSFT_perception_anchor_interop 1
#وصف_ڪريو XR_MSFT_perception_anchor_interop_SPEC_نسخو 1
#وصف_ڪريو XR_MSFT_PERCEPTION_ANCHOR_INTEROP_EXTENSION_NAME "XR_MSFT_perception_anchor_interop"
تعريفنوع Xr_نتيجو (XRAPI_PTR *PFN_xrCreateSpatialAnchorFromPerceptionAnchorMSFT)(XrSession session, IUnknown* perceptionAnchor, XrSpatialAnchorMSFT* anchor);
تعريفنوع Xr_نتيجو (XRAPI_PTR *PFN_xrTryGetPerceptionAnchorFromSpatialAnchorMSFT)(XrSession session, XrSpatialAnchorMSFT anchor, IUnknown** perceptionAnchor);

#جيڪڏهن_وصف_نه_ٿيل XR_NO_PROTOTYPES
#جيڪڏهن_وصف_ٿيل XR_EXTENSION_PROTOTYPES
XRAPI_ATTR Xr_نتيجو XRAPI_CALL xrCreateSpatialAnchorFromPerceptionAnchorMSFT(
    XrSession                                   session,
    IUnknown*                                   perceptionAnchor,
    XrSpatialAnchorMSFT*                        anchor);

XRAPI_ATTR Xr_نتيجو XRAPI_CALL xrTryGetPerceptionAnchorFromSpatialAnchorMSFT(
    XrSession                                   session,
    XrSpatialAnchorMSFT                         anchor,
    IUnknown**                                  perceptionAnchor);
#جيڪڏهن_پورو /* XR_EXTENSION_PROTOTYPES */
#جيڪڏهن_پورو /* !XR_NO_PROTOTYPES */
#جيڪڏهن_پورو /* XR_USE_PLATFORM_WIN32 */

#جيڪڏهن_وصف_ٿيل XR_USE_PLATFORM_WIN32

// XR_MSFT_holographic_window_attachment is a preprocessor guard. Do not pass it to API calls.
#وصف_ڪريو XR_MSFT_holographic_دري_attachment 1
#وصف_ڪريو XR_MSFT_holographic_دري_attachment_SPEC_نسخو 1
#وصف_ڪريو XR_MSFT_HOLOGRAPHIC_دري_ATTACHMENT_EXTENSION_NAME "XR_MSFT_holographic_window_attachment"
#جيڪڏهن_وصف_ٿيل XR_USE_PLATFORM_WIN32
// XrHolographicWindowAttachmentMSFT extends XrSessionCreateInfo
تعريفنوع بنية Xr_Holographic_دري_Attachment_MSFT {
    XrStructureType             type;
    ثابت فراغ* XR_MAY_ALIAS    ايندڙ;
    IUnknown*                   holographicSpace;
    IUnknown*                   core_دري;
} Xr_Holographic_دري_Attachment_MSFT;
#جيڪڏهن_پورو // XR_USE_PLATFORM_WIN32

#جيڪڏهن_پورو /* XR_USE_PLATFORM_WIN32 */

#جيڪڏهن_وصف_ٿيل XR_USE_PLATFORM_ANDROID

// XR_FB_android_surface_swapchain_create is a preprocessor guard. Do not pass it to API calls.
#وصف_ڪريو XR_FB_android_surface_swapchain_create 1
#وصف_ڪريو XR_FB_android_surface_swapchain_create_SPEC_نسخو 1
#وصف_ڪريو XR_FB_ANDROID_SURFACE_SWAPCHAIN_CREATE_EXTENSION_NAME "XR_FB_android_surface_swapchain_create"
تعريفنوع XrFlags64 XrAndroidSurfaceSwapchainFlagsFB;

// Flag bits for XrAndroidSurfaceSwapchainFlagsFB
ساكن ثابت XrAndroidSurfaceSwapchainFlagsFB XR_ANDROID_SURFACE_SWAPCHAIN_SYNCHRONOUS_ٻٽو_انگ_FB = 0x00000001;
ساكن ثابت XrAndroidSurfaceSwapchainFlagsFB XR_ANDROID_SURFACE_SWAPCHAIN_USE_TIMESTAMPS_ٻٽو_انگ_FB = 0x00000002;

#جيڪڏهن_وصف_ٿيل XR_USE_PLATFORM_ANDROID
// XrAndroidSurfaceSwapchainCreateInfoFB extends XrSwapchainCreateInfo
تعريفنوع بنية XrAndroidSurfaceSwapchainCreateInfoFB {
    XrStructureType                     type;
    ثابت فراغ* XR_MAY_ALIAS            ايندڙ;
    XrAndroidSurfaceSwapchainFlagsFB    createFlags;
} XrAndroidSurfaceSwapchainCreateInfoFB;
#جيڪڏهن_پورو // XR_USE_PLATFORM_ANDROID

#جيڪڏهن_پورو /* XR_USE_PLATFORM_ANDROID */

#جيڪڏهن_وصف_ٿيل XR_USE_PLATFORM_ML

// XR_ML_compat is a preprocessor guard. Do not pass it to API calls.
#وصف_ڪريو XR_ML_compat 1
#وصف_ڪريو XR_ML_compat_SPEC_نسخو         1
#وصف_ڪريو XR_ML_COMPAT_EXTENSION_NAME       "XR_ML_compat"
تعريفنوع بنية XrCoordinateSpaceCreateInfoML {
    XrStructureType             type;
    ثابت فراغ* XR_MAY_ALIAS    ايندڙ;
    MLCoordinate_چوکٺو_UID        cfuid;
    XrPosef                     pose_اندريون_Coordinate_Space;
} XrCoordinateSpaceCreateInfoML;

تعريفنوع Xr_نتيجو (XRAPI_PTR *PFN_xr_Create_Space_From_Coordinate_چوکٺو_UIDML)(XrSession session, ثابت XrCoordinateSpaceCreateInfoML *createInfo, XrSpace* space);

#جيڪڏهن_وصف_نه_ٿيل XR_NO_PROTOTYPES
#جيڪڏهن_وصف_ٿيل XR_EXTENSION_PROTOTYPES
XRAPI_ATTR Xr_نتيجو XRAPI_CALL xr_Create_Space_From_Coordinate_چوکٺو_UIDML(
    XrSession                                   session,
    ثابت XrCoordinateSpaceCreateInfoML *       createInfo,
    XrSpace*                                    space);
#جيڪڏهن_پورو /* XR_EXTENSION_PROTOTYPES */
#جيڪڏهن_پورو /* !XR_NO_PROTOTYPES */
#جيڪڏهن_پورو /* XR_USE_PLATFORM_ML */

#جيڪڏهن_وصف_ٿيل XR_USE_PLATFORM_WIN32

// XR_OCULUS_audio_device_guid is a preprocessor guard. Do not pass it to API calls.
#وصف_ڪريو XR_OCULUS_audio_device_guid 1
#وصف_ڪريو XR_OCULUS_audio_device_guid_SPEC_نسخو 1
#وصف_ڪريو XR_OCULUS_AUDIO_DEVICE_GUID_EXTENSION_NAME "XR_OCULUS_audio_device_guid"
#وصف_ڪريو XR_MAX_AUDIO_DEVICE_STR_سائيز_OCULUS 128
تعريفنوع Xr_نتيجو (XRAPI_PTR *PFN_xrGetAudioOutputDeviceGuidOculus)(XrInstance instance, wchar_t بفر_2[XR_MAX_AUDIO_DEVICE_STR_سائيز_OCULUS]);
تعريفنوع Xr_نتيجو (XRAPI_PTR *PFN_xr_Get_Audio_داخلا_Device_Guid_Oculus)(XrInstance instance, wchar_t بفر_2[XR_MAX_AUDIO_DEVICE_STR_سائيز_OCULUS]);

#جيڪڏهن_وصف_نه_ٿيل XR_NO_PROTOTYPES
#جيڪڏهن_وصف_ٿيل XR_EXTENSION_PROTOTYPES
XRAPI_ATTR Xr_نتيجو XRAPI_CALL xrGetAudioOutputDeviceGuidOculus(
    XrInstance                                  instance,
    wchar_t                                     بفر_2[XR_MAX_AUDIO_DEVICE_STR_سائيز_OCULUS]);

XRAPI_ATTR Xr_نتيجو XRAPI_CALL xr_Get_Audio_داخلا_Device_Guid_Oculus(
    XrInstance                                  instance,
    wchar_t                                     بفر_2[XR_MAX_AUDIO_DEVICE_STR_سائيز_OCULUS]);
#جيڪڏهن_پورو /* XR_EXTENSION_PROTOTYPES */
#جيڪڏهن_پورو /* !XR_NO_PROTOTYPES */
#جيڪڏهن_پورو /* XR_USE_PLATFORM_WIN32 */

#جيڪڏهن_وصف_ٿيل XR_USE_GRAPHICS_API_VULKAN

// XR_FB_foveation_vulkan is a preprocessor guard. Do not pass it to API calls.
#وصف_ڪريو XR_FB_foveation_vulkan 1
#وصف_ڪريو XR_FB_foveation_vulkan_SPEC_نسخو 1
#وصف_ڪريو XR_FB_FOVEATION_VULKAN_EXTENSION_NAME "XR_FB_foveation_vulkan"
// XrSwapchainImageFoveationVulkanFB extends XrSwapchainImageVulkanKHR
تعريفنوع بنية XrSwapchainImageFoveationVulkanFB {
    XrStructureType       type;
    فراغ* XR_MAY_ALIAS    ايندڙ;
    VkImage               image;
    uint32_t              ويڪر;
    uint32_t              اوچائي;
} XrSwapchainImageFoveationVulkanFB;

#جيڪڏهن_پورو /* XR_USE_GRAPHICS_API_VULKAN */

#جيڪڏهن_وصف_ٿيل XR_USE_PLATFORM_ANDROID

// XR_FB_swapchain_update_state_android_surface is a preprocessor guard. Do not pass it to API calls.
#وصف_ڪريو XR_FB_swapchain_update_state_android_surface 1
#وصف_ڪريو XR_FB_swapchain_update_state_android_surface_SPEC_نسخو 1
#وصف_ڪريو XR_FB_SWAPCHAIN_UPDATE_STATE_ANDROID_SURFACE_EXTENSION_NAME "XR_FB_swapchain_update_state_android_surface"
#جيڪڏهن_وصف_ٿيل XR_USE_PLATFORM_ANDROID
تعريفنوع بنية XrSwapchainStateAndroidSurfaceDimensionsFB {
    XrStructureType       type;
    فراغ* XR_MAY_ALIAS    ايندڙ;
    uint32_t              ويڪر;
    uint32_t              اوچائي;
} XrSwapchainStateAndroidSurfaceDimensionsFB;
#جيڪڏهن_پورو // XR_USE_PLATFORM_ANDROID

#جيڪڏهن_پورو /* XR_USE_PLATFORM_ANDROID */

#جيڪڏهن_وصف_ٿيل XR_USE_GRAPHICS_API_OPENGL_ES

// XR_FB_swapchain_update_state_opengl_es is a preprocessor guard. Do not pass it to API calls.
#وصف_ڪريو XR_FB_swapchain_update_state_opengl_es 1
#وصف_ڪريو XR_FB_swapchain_update_state_opengl_es_SPEC_نسخو 1
#وصف_ڪريو XR_FB_SWAPCHAIN_UPDATE_STATE_OPENGL_ES_EXTENSION_NAME "XR_FB_swapchain_update_state_opengl_es"
#جيڪڏهن_وصف_ٿيل XR_USE_GRAPHICS_API_OPENGL_ES
تعريفنوع بنية XrSwapchainStateSamplerOpenGLESFB {
    XrStructureType       type;
    فراغ* XR_MAY_ALIAS    ايندڙ;
    EGLenum               minFilter;
    EGLenum               magFilter;
    EGLenum               wrap_گهڻائي_S;
    EGLenum               wrap_گهڻائي_T;
    EGLenum               swizzleRed;
    EGLenum               swizzleGreen;
    EGLenum               swizzleBlue;
    EGLenum               swizzleAlpha;
    عائم                 maxAnisotropy;
    XrColor4f             borderColor;
} XrSwapchainStateSamplerOpenGLESFB;
#جيڪڏهن_پورو // XR_USE_GRAPHICS_API_OPENGL_ES

#جيڪڏهن_پورو /* XR_USE_GRAPHICS_API_OPENGL_ES */

#جيڪڏهن_وصف_ٿيل XR_USE_GRAPHICS_API_VULKAN

// XR_FB_swapchain_update_state_vulkan is a preprocessor guard. Do not pass it to API calls.
#وصف_ڪريو XR_FB_swapchain_update_state_vulkan 1
#وصف_ڪريو XR_FB_swapchain_update_state_vulkan_SPEC_نسخو 1
#وصف_ڪريو XR_FB_SWAPCHAIN_UPDATE_STATE_VULKAN_EXTENSION_NAME "XR_FB_swapchain_update_state_vulkan"
#جيڪڏهن_وصف_ٿيل XR_USE_GRAPHICS_API_VULKAN
تعريفنوع بنية XrSwapchainStateSamplerVulkanFB {
    XrStructureType         type;
    فراغ* XR_MAY_ALIAS      ايندڙ;
    VkFilter                minFilter;
    VkFilter                magFilter;
    Vk_Sampler_Mipmap_گهڻائي     mipmap_گهڻائي;
    Vk_Sampler_پتو_گهڻائي    wrap_گهڻائي_S;
    Vk_Sampler_پتو_گهڻائي    wrap_گهڻائي_T;
    VkComponentSwizzle      swizzleRed;
    VkComponentSwizzle      swizzleGreen;
    VkComponentSwizzle      swizzleBlue;
    VkComponentSwizzle      swizzleAlpha;
    عائم                   maxAnisotropy;
    XrColor4f               borderColor;
} XrSwapchainStateSamplerVulkanFB;
#جيڪڏهن_پورو // XR_USE_GRAPHICS_API_VULKAN

#جيڪڏهن_پورو /* XR_USE_GRAPHICS_API_VULKAN */

#جيڪڏهن_وصف_ٿيل XR_USE_GRAPHICS_API_VULKAN

// XR_META_vulkan_swapchain_create_info is a preprocessor guard. Do not pass it to API calls.
#وصف_ڪريو XR_META_vulkan_swapchain_create_info 1
#وصف_ڪريو XR_META_vulkan_swapchain_create_info_SPEC_نسخو 1
#وصف_ڪريو XR_META_VULKAN_SWAPCHAIN_CREATE_INFO_EXTENSION_NAME "XR_META_vulkan_swapchain_create_info"
// XrVulkanSwapchainCreateInfoMETA extends XrSwapchainCreateInfo
تعريفنوع بنية XrVulkanSwapchainCreateInfoMETA {
    XrStructureType             type;
    ثابت فراغ* XR_MAY_ALIAS    ايندڙ;
    VkImageCreateFlags          additionalCreateFlags;
    VkImageUsageFlags           additionalUsageFlags;
} XrVulkanSwapchainCreateInfoMETA;

#جيڪڏهن_پورو /* XR_USE_GRAPHICS_API_VULKAN */

#جيڪڏهن_وصف_ٿيل XR_USE_PLATFORM_ANDROID

// XR_ANDROID_anchor_sharing_export is a preprocessor guard. Do not pass it to API calls.
#وصف_ڪريو XR_ANDROID_anchor_sharing_export 1
#وصف_ڪريو XR_ANDROID_anchor_sharing_export_SPEC_نسخو 1
#وصف_ڪريو XR_ANDROID_ANCHOR_SHARING_EXPORT_EXTENSION_NAME "XR_ANDROID_anchor_sharing_export"
تعريفنوع بنية XrAnchorSharingInfoANDROID {
    XrStructureType             type;
    ثابت فراغ* XR_MAY_ALIAS    ايندڙ;
    XrSpace                     anchor;
} XrAnchorSharingInfoANDROID;

تعريفنوع بنية XrAnchorSharingTokenANDROID {
    XrStructureType       type;
    فراغ* XR_MAY_ALIAS    ايندڙ;
    بنية AIBinder*      token;
} XrAnchorSharingTokenANDROID;

// XrSystemAnchorSharingExportPropertiesANDROID extends XrSystemProperties
تعريفنوع بنية XrSystemAnchorSharingExportPropertiesANDROID {
    XrStructureType       type;
    فراغ* XR_MAY_ALIAS    ايندڙ;
    XrBool32              supportsAnchorSharingExport;
} XrSystemAnchorSharingExportPropertiesANDROID;

تعريفنوع Xr_نتيجو (XRAPI_PTR *PFN_xrShareAnchorANDROID)(XrSession session, ثابت XrAnchorSharingInfoANDROID* sharingInfo, XrAnchorSharingTokenANDROID* anchorToken);
تعريفنوع Xr_نتيجو (XRAPI_PTR *PFN_xrUnshareAnchorANDROID)(XrSession session, XrSpace anchor);

#جيڪڏهن_وصف_نه_ٿيل XR_NO_PROTOTYPES
#جيڪڏهن_وصف_ٿيل XR_EXTENSION_PROTOTYPES
XRAPI_ATTR Xr_نتيجو XRAPI_CALL xrShareAnchorANDROID(
    XrSession                                   session,
    ثابت XrAnchorSharingInfoANDROID*           sharingInfo,
    XrAnchorSharingTokenANDROID*                anchorToken);

XRAPI_ATTR Xr_نتيجو XRAPI_CALL xrUnshareAnchorANDROID(
    XrSession                                   session,
    XrSpace                                     anchor);
#جيڪڏهن_پورو /* XR_EXTENSION_PROTOTYPES */
#جيڪڏهن_پورو /* !XR_NO_PROTOTYPES */
#جيڪڏهن_پورو /* XR_USE_PLATFORM_ANDROID */

#جيڪڏهن_وصف_ٿيل __cplusplus
}
#جيڪڏهن_پورو

#جيڪڏهن_پورو
