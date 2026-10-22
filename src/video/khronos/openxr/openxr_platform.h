#यदि_अपरिभाषितम् OPENXR_PLATFORM_H_
#परिभाषय OPENXR_PLATFORM_H_ 1

/*
** Copyright 2017-2026 The Khronos Group Inc.
**
** SPDX-License-Identifier: Apache-2.0 OR MIT
*/

/*
** This header is generated from the Khronos OpenXR XML API Registry.
**
*/

#अन्तर्भाव "openxr.h"

#यदि_परिभाषितम् __cplusplus
बाह्य "C" {
#यदि_अन्तः


#यदि_परिभाषितम् XR_USE_PLATFORM_ANDROID

// XR_KHR_android_thread_settings is a preprocessor guard. Do not pass it to API calls.
#परिभाषय XR_KHR_android_thread_settings 1
#परिभाषय XR_KHR_android_thread_settings_SPEC_संस्करणम् 6
#परिभाषय XR_KHR_ANDROID_THREAD_SETTINGS_EXTENSION_NAME "XR_KHR_android_thread_settings"

प्रकारनिर्देश गणना XrAndroidThreadTypeKHR {
    XR_ANDROID_THREAD_TYPE_APPLICATION_MAIN_KHR = 1,
    XR_ANDROID_THREAD_TYPE_APPLICATION_कार्यकर्ता_KHR = 2,
    XR_ANDROID_THREAD_TYPE_RENDERER_MAIN_KHR = 3,
    XR_ANDROID_THREAD_TYPE_RENDERER_कार्यकर्ता_KHR = 4,
    XR_ANDROID_THREAD_TYPE_MAX_ENUM_KHR = 0x7FFFFFFF
} XrAndroidThreadTypeKHR;
प्रकारनिर्देश Xr_परिणाम (XRAPI_PTR *PFN_xr_समुच्चयः_Android_Application_Thread_KHR)(XrSession session, XrAndroidThreadTypeKHR threadType, uint32_t threadId);

#यदि_अपरिभाषितम् XR_NO_PROTOTYPES
#यदि_परिभाषितम् XR_EXTENSION_PROTOTYPES
XRAPI_ATTR Xr_परिणाम XRAPI_CALL xr_समुच्चयः_Android_Application_Thread_KHR(
    XrSession                                   session,
    XrAndroidThreadTypeKHR                      threadType,
    uint32_t                                    threadId);
#यदि_अन्तः /* XR_EXTENSION_PROTOTYPES */
#यदि_अन्तः /* !XR_NO_PROTOTYPES */
#यदि_अन्तः /* XR_USE_PLATFORM_ANDROID */

#यदि_परिभाषितम् XR_USE_PLATFORM_ANDROID

// XR_KHR_android_surface_swapchain is a preprocessor guard. Do not pass it to API calls.
#परिभाषय XR_KHR_android_surface_swapchain 1
#परिभाषय XR_KHR_android_surface_swapchain_SPEC_संस्करणम् 4
#परिभाषय XR_KHR_ANDROID_SURFACE_SWAPCHAIN_EXTENSION_NAME "XR_KHR_android_surface_swapchain"
प्रकारनिर्देश Xr_परिणाम (XRAPI_PTR *PFN_xrCreateSwapchainAndroidSurfaceKHR)(XrSession session, ध्रुव XrSwapchainCreateInfo* info, XrSwapchain* swapchain, jobject* surface);

#यदि_अपरिभाषितम् XR_NO_PROTOTYPES
#यदि_परिभाषितम् XR_EXTENSION_PROTOTYPES
XRAPI_ATTR Xr_परिणाम XRAPI_CALL xrCreateSwapchainAndroidSurfaceKHR(
    XrSession                                   session,
    ध्रुव XrSwapchainCreateInfo*                info,
    XrSwapchain*                                swapchain,
    jobject*                                    surface);
#यदि_अन्तः /* XR_EXTENSION_PROTOTYPES */
#यदि_अन्तः /* !XR_NO_PROTOTYPES */
#यदि_अन्तः /* XR_USE_PLATFORM_ANDROID */

#यदि_परिभाषितम् XR_USE_PLATFORM_ANDROID

// XR_KHR_android_create_instance is a preprocessor guard. Do not pass it to API calls.
#परिभाषय XR_KHR_android_create_instance 1
#परिभाषय XR_KHR_android_create_instance_SPEC_संस्करणम् 3
#परिभाषय XR_KHR_ANDROID_CREATE_INSTANCE_EXTENSION_NAME "XR_KHR_android_create_instance"
// XrInstanceCreateInfoAndroidKHR extends XrInstanceCreateInfo
प्रकारनिर्देश संरचना XrInstanceCreateInfoAndroidKHR {
    XrStructureType             type;
    ध्रुव शून्य* XR_MAY_ALIAS    अग्र;
    शून्य* XR_MAY_ALIAS          applicationVM;
    शून्य* XR_MAY_ALIAS          applicationActivity;
} XrInstanceCreateInfoAndroidKHR;

#यदि_अन्तः /* XR_USE_PLATFORM_ANDROID */

#यदि_परिभाषितम् XR_USE_GRAPHICS_API_VULKAN

// XR_KHR_vulkan_swapchain_format_list is a preprocessor guard. Do not pass it to API calls.
#परिभाषय XR_KHR_vulkan_swapchain_format_list 1
#परिभाषय XR_KHR_vulkan_swapchain_format_list_SPEC_संस्करणम् 5
#परिभाषय XR_KHR_VULKAN_SWAPCHAIN_FORMAT_LIST_EXTENSION_NAME "XR_KHR_vulkan_swapchain_format_list"
// XrVulkanSwapchainFormatListCreateInfoKHR extends XrSwapchainCreateInfo
प्रकारनिर्देश संरचना XrVulkanSwapchainFormatListCreateInfoKHR {
    XrStructureType             type;
    ध्रुव शून्य* XR_MAY_ALIAS    अग्र;
    uint32_t                    view_Format_गणनम्;
    ध्रुव VkFormat*             viewFormats;
} XrVulkanSwapchainFormatListCreateInfoKHR;

#यदि_अन्तः /* XR_USE_GRAPHICS_API_VULKAN */

#यदि_परिभाषितम् XR_USE_GRAPHICS_API_OPENGL

// XR_KHR_opengl_enable is a preprocessor guard. Do not pass it to API calls.
#परिभाषय XR_KHR_opengl_enable 1
#परिभाषय XR_KHR_opengl_enable_SPEC_संस्करणम् 12
#परिभाषय XR_KHR_OPENGL_ENABLE_EXTENSION_NAME "XR_KHR_opengl_enable"
#यदि_परिभाषितम् XR_USE_PLATFORM_WIN32
// XrGraphicsBindingOpenGLWin32KHR extends XrSessionCreateInfo
प्रकारनिर्देश संरचना XrGraphicsBindingOpenGLWin32KHR {
    XrStructureType             type;
    ध्रुव शून्य* XR_MAY_ALIAS    अग्र;
    HDC                         hDC;
    HGLRC                       hGLRC;
} XrGraphicsBindingOpenGLWin32KHR;
#यदि_अन्तः // XR_USE_PLATFORM_WIN32

#यदि_परिभाषितम् XR_USE_PLATFORM_XLIB
// XrGraphicsBindingOpenGLXlibKHR extends XrSessionCreateInfo
प्रकारनिर्देश संरचना XrGraphicsBindingOpenGLXlibKHR {
    XrStructureType             type;
    ध्रुव शून्य* XR_MAY_ALIAS    अग्र;
    Display*                    xDisplay;
    uint32_t                    visualid;
    GLXFBConfig                 glxFBConfig;
    GLXDrawable                 glxDrawable;
    GLXContext                  glxContext;
} XrGraphicsBindingOpenGLXlibKHR;
#यदि_अन्तः // XR_USE_PLATFORM_XLIB

#यदि_परिभाषितम् XR_USE_PLATFORM_XCB
// XrGraphicsBindingOpenGLXcbKHR extends XrSessionCreateInfo
प्रकारनिर्देश संरचना XrGraphicsBindingOpenGLXcbKHR {
    XrStructureType             type;
    ध्रुव शून्य* XR_MAY_ALIAS    अग्र;
    xcb_connection_t*           connection;
    uint32_t                    screen_सङ्ख्या;
    xcb_glx_fbconfig_t          fbconfigid;
    xcb_visualid_t              visualid;
    xcb_glx_drawable_t          glxDrawable;
    xcb_glx_context_t           glxContext;
} XrGraphicsBindingOpenGLXcbKHR;
#यदि_अन्तः // XR_USE_PLATFORM_XCB

#यदि_परिभाषितम् XR_USE_PLATFORM_WAYLAND
// XrGraphicsBindingOpenGLWaylandKHR extends XrSessionCreateInfo
प्रकारनिर्देश संरचना XrGraphicsBindingOpenGLWaylandKHR {
    XrStructureType             type;
    ध्रुव शून्य* XR_MAY_ALIAS    अग्र;
    संरचना wl_display*          display;
} XrGraphicsBindingOpenGLWaylandKHR;
#यदि_अन्तः // XR_USE_PLATFORM_WAYLAND

प्रकारनिर्देश संरचना XrSwapchainImageOpenGLKHR {
    XrStructureType       type;
    शून्य* XR_MAY_ALIAS    अग्र;
    uint32_t              image;
} XrSwapchainImageOpenGLKHR;

प्रकारनिर्देश संरचना XrGraphicsRequirementsOpenGLKHR {
    XrStructureType       type;
    शून्य* XR_MAY_ALIAS    अग्र;
    Xr_संस्करणम्             min_Api_संस्करणम्_Supported;
    Xr_संस्करणम्             max_Api_संस्करणम्_Supported;
} XrGraphicsRequirementsOpenGLKHR;

प्रकारनिर्देश Xr_परिणाम (XRAPI_PTR *PFN_xrGetOpenGLGraphicsRequirementsKHR)(XrInstance instance, XrSystemId systemId, XrGraphicsRequirementsOpenGLKHR* graphicsRequirements);

#यदि_अपरिभाषितम् XR_NO_PROTOTYPES
#यदि_परिभाषितम् XR_EXTENSION_PROTOTYPES
XRAPI_ATTR Xr_परिणाम XRAPI_CALL xrGetOpenGLGraphicsRequirementsKHR(
    XrInstance                                  instance,
    XrSystemId                                  systemId,
    XrGraphicsRequirementsOpenGLKHR*            graphicsRequirements);
#यदि_अन्तः /* XR_EXTENSION_PROTOTYPES */
#यदि_अन्तः /* !XR_NO_PROTOTYPES */
#यदि_अन्तः /* XR_USE_GRAPHICS_API_OPENGL */

#यदि_परिभाषितम् XR_USE_GRAPHICS_API_OPENGL_ES

// XR_KHR_opengl_es_enable is a preprocessor guard. Do not pass it to API calls.
#परिभाषय XR_KHR_opengl_es_enable 1
#परिभाषय XR_KHR_opengl_es_enable_SPEC_संस्करणम् 10
#परिभाषय XR_KHR_OPENGL_ES_ENABLE_EXTENSION_NAME "XR_KHR_opengl_es_enable"
#यदि_परिभाषितम् XR_USE_PLATFORM_ANDROID
// XrGraphicsBindingOpenGLESAndroidKHR extends XrSessionCreateInfo
प्रकारनिर्देश संरचना XrGraphicsBindingOpenGLESAndroidKHR {
    XrStructureType             type;
    ध्रुव शून्य* XR_MAY_ALIAS    अग्र;
    EGLDisplay                  display;
    EGLConfig                   config;
    EGLContext                  context;
} XrGraphicsBindingOpenGLESAndroidKHR;
#यदि_अन्तः // XR_USE_PLATFORM_ANDROID

प्रकारनिर्देश संरचना XrSwapchainImageOpenGLESKHR {
    XrStructureType       type;
    शून्य* XR_MAY_ALIAS    अग्र;
    uint32_t              image;
} XrSwapchainImageOpenGLESKHR;

प्रकारनिर्देश संरचना XrGraphicsRequirementsOpenGLESKHR {
    XrStructureType       type;
    शून्य* XR_MAY_ALIAS    अग्र;
    Xr_संस्करणम्             min_Api_संस्करणम्_Supported;
    Xr_संस्करणम्             max_Api_संस्करणम्_Supported;
} XrGraphicsRequirementsOpenGLESKHR;

प्रकारनिर्देश Xr_परिणाम (XRAPI_PTR *PFN_xrGetOpenGLESGraphicsRequirementsKHR)(XrInstance instance, XrSystemId systemId, XrGraphicsRequirementsOpenGLESKHR* graphicsRequirements);

#यदि_अपरिभाषितम् XR_NO_PROTOTYPES
#यदि_परिभाषितम् XR_EXTENSION_PROTOTYPES
XRAPI_ATTR Xr_परिणाम XRAPI_CALL xrGetOpenGLESGraphicsRequirementsKHR(
    XrInstance                                  instance,
    XrSystemId                                  systemId,
    XrGraphicsRequirementsOpenGLESKHR*          graphicsRequirements);
#यदि_अन्तः /* XR_EXTENSION_PROTOTYPES */
#यदि_अन्तः /* !XR_NO_PROTOTYPES */
#यदि_अन्तः /* XR_USE_GRAPHICS_API_OPENGL_ES */

#यदि_परिभाषितम् XR_USE_GRAPHICS_API_VULKAN

// XR_KHR_vulkan_enable is a preprocessor guard. Do not pass it to API calls.
#परिभाषय XR_KHR_vulkan_enable 1
#परिभाषय XR_KHR_vulkan_enable_SPEC_संस्करणम् 10
#परिभाषय XR_KHR_VULKAN_ENABLE_EXTENSION_NAME "XR_KHR_vulkan_enable"
// XrGraphicsBindingVulkanKHR extends XrSessionCreateInfo
प्रकारनिर्देश संरचना XrGraphicsBindingVulkanKHR {
    XrStructureType             type;
    ध्रुव शून्य* XR_MAY_ALIAS    अग्र;
    VkInstance                  instance;
    VkPhysicalDevice            physicalDevice;
    VkDevice                    device;
    uint32_t                    queue_Family_सूचकांक;
    uint32_t                    queue_सूचकांक;
} XrGraphicsBindingVulkanKHR;

प्रकारनिर्देश संरचना XrSwapchainImageVulkanKHR {
    XrStructureType       type;
    शून्य* XR_MAY_ALIAS    अग्र;
    VkImage               image;
} XrSwapchainImageVulkanKHR;

प्रकारनिर्देश संरचना XrGraphicsRequirementsVulkanKHR {
    XrStructureType       type;
    शून्य* XR_MAY_ALIAS    अग्र;
    Xr_संस्करणम्             min_Api_संस्करणम्_Supported;
    Xr_संस्करणम्             max_Api_संस्करणम्_Supported;
} XrGraphicsRequirementsVulkanKHR;

प्रकारनिर्देश Xr_परिणाम (XRAPI_PTR *PFN_xrGetVulkanInstanceExtensionsKHR)(XrInstance instance, XrSystemId systemId, uint32_t बफर_क्षमता_निवेशः, uint32_t* बफर_गणनम्_Output, वर्ण* बफर_2);
प्रकारनिर्देश Xr_परिणाम (XRAPI_PTR *PFN_xrGetVulkanDeviceExtensionsKHR)(XrInstance instance, XrSystemId systemId, uint32_t बफर_क्षमता_निवेशः, uint32_t* बफर_गणनम्_Output, वर्ण* बफर_2);
प्रकारनिर्देश Xr_परिणाम (XRAPI_PTR *PFN_xrGetVulkanGraphicsDeviceKHR)(XrInstance instance, XrSystemId systemId, VkInstance vkInstance, VkPhysicalDevice* vkPhysicalDevice);
प्रकारनिर्देश Xr_परिणाम (XRAPI_PTR *PFN_xrGetVulkanGraphicsRequirementsKHR)(XrInstance instance, XrSystemId systemId, XrGraphicsRequirementsVulkanKHR* graphicsRequirements);

#यदि_अपरिभाषितम् XR_NO_PROTOTYPES
#यदि_परिभाषितम् XR_EXTENSION_PROTOTYPES
XRAPI_ATTR Xr_परिणाम XRAPI_CALL xrGetVulkanInstanceExtensionsKHR(
    XrInstance                                  instance,
    XrSystemId                                  systemId,
    uint32_t                                    बफर_क्षमता_निवेशः,
    uint32_t*                                   बफर_गणनम्_Output,
    वर्ण*                                       बफर_2);

XRAPI_ATTR Xr_परिणाम XRAPI_CALL xrGetVulkanDeviceExtensionsKHR(
    XrInstance                                  instance,
    XrSystemId                                  systemId,
    uint32_t                                    बफर_क्षमता_निवेशः,
    uint32_t*                                   बफर_गणनम्_Output,
    वर्ण*                                       बफर_2);

XRAPI_ATTR Xr_परिणाम XRAPI_CALL xrGetVulkanGraphicsDeviceKHR(
    XrInstance                                  instance,
    XrSystemId                                  systemId,
    VkInstance                                  vkInstance,
    VkPhysicalDevice*                           vkPhysicalDevice);

XRAPI_ATTR Xr_परिणाम XRAPI_CALL xrGetVulkanGraphicsRequirementsKHR(
    XrInstance                                  instance,
    XrSystemId                                  systemId,
    XrGraphicsRequirementsVulkanKHR*            graphicsRequirements);
#यदि_अन्तः /* XR_EXTENSION_PROTOTYPES */
#यदि_अन्तः /* !XR_NO_PROTOTYPES */
#यदि_अन्तः /* XR_USE_GRAPHICS_API_VULKAN */

#यदि_परिभाषितम् XR_USE_GRAPHICS_API_D3D11

// XR_KHR_D3D11_enable is a preprocessor guard. Do not pass it to API calls.
#परिभाषय XR_KHR_D3D11_enable 1
#परिभाषय XR_KHR_D3_D11_enable_SPEC_संस्करणम्  11
#परिभाषय XR_KHR_D3D11_ENABLE_EXTENSION_NAME "XR_KHR_D3D11_enable"
// XrGraphicsBindingD3D11KHR extends XrSessionCreateInfo
प्रकारनिर्देश संरचना XrGraphicsBindingD3D11KHR {
    XrStructureType             type;
    ध्रुव शून्य* XR_MAY_ALIAS    अग्र;
    ID3D11Device*               device;
} XrGraphicsBindingD3D11KHR;

प्रकारनिर्देश संरचना XrSwapchainImageD3D11KHR {
     XrStructureType      type;
    शून्य* XR_MAY_ALIAS    अग्र;
    ID3D11Texture2D*      texture;
} XrSwapchainImageD3D11KHR;

प्रकारनिर्देश संरचना XrGraphicsRequirementsD3D11KHR {
    XrStructureType       type;
    शून्य* XR_MAY_ALIAS    अग्र;
    LUID                  adapterLuid;
    D3D_FEATURE_LEVEL     minFeatureLevel;
} XrGraphicsRequirementsD3D11KHR;

प्रकारनिर्देश Xr_परिणाम (XRAPI_PTR *PFN_xrGetD3D11GraphicsRequirementsKHR)(XrInstance instance, XrSystemId systemId, XrGraphicsRequirementsD3D11KHR* graphicsRequirements);

#यदि_अपरिभाषितम् XR_NO_PROTOTYPES
#यदि_परिभाषितम् XR_EXTENSION_PROTOTYPES
XRAPI_ATTR Xr_परिणाम XRAPI_CALL xrGetD3D11GraphicsRequirementsKHR(
    XrInstance                                  instance,
    XrSystemId                                  systemId,
    XrGraphicsRequirementsD3D11KHR*             graphicsRequirements);
#यदि_अन्तः /* XR_EXTENSION_PROTOTYPES */
#यदि_अन्तः /* !XR_NO_PROTOTYPES */
#यदि_अन्तः /* XR_USE_GRAPHICS_API_D3D11 */

#यदि_परिभाषितम् XR_USE_GRAPHICS_API_D3D12

// XR_KHR_D3D12_enable is a preprocessor guard. Do not pass it to API calls.
#परिभाषय XR_KHR_D3D12_enable 1
#परिभाषय XR_KHR_D3_D12_enable_SPEC_संस्करणम्  11
#परिभाषय XR_KHR_D3D12_ENABLE_EXTENSION_NAME "XR_KHR_D3D12_enable"
// XrGraphicsBindingD3D12KHR extends XrSessionCreateInfo
प्रकारनिर्देश संरचना XrGraphicsBindingD3D12KHR {
    XrStructureType             type;
    ध्रुव शून्य* XR_MAY_ALIAS    अग्र;
    ID3D12Device*               device;
    ID3D12CommandQueue*         queue;
} XrGraphicsBindingD3D12KHR;

प्रकारनिर्देश संरचना XrSwapchainImageD3D12KHR {
     XrStructureType      type;
    शून्य* XR_MAY_ALIAS    अग्र;
    ID3D12Resource*       texture;
} XrSwapchainImageD3D12KHR;

प्रकारनिर्देश संरचना XrGraphicsRequirementsD3D12KHR {
    XrStructureType       type;
    शून्य* XR_MAY_ALIAS    अग्र;
    LUID                  adapterLuid;
    D3D_FEATURE_LEVEL     minFeatureLevel;
} XrGraphicsRequirementsD3D12KHR;

प्रकारनिर्देश Xr_परिणाम (XRAPI_PTR *PFN_xrGetD3D12GraphicsRequirementsKHR)(XrInstance instance, XrSystemId systemId, XrGraphicsRequirementsD3D12KHR* graphicsRequirements);

#यदि_अपरिभाषितम् XR_NO_PROTOTYPES
#यदि_परिभाषितम् XR_EXTENSION_PROTOTYPES
XRAPI_ATTR Xr_परिणाम XRAPI_CALL xrGetD3D12GraphicsRequirementsKHR(
    XrInstance                                  instance,
    XrSystemId                                  systemId,
    XrGraphicsRequirementsD3D12KHR*             graphicsRequirements);
#यदि_अन्तः /* XR_EXTENSION_PROTOTYPES */
#यदि_अन्तः /* !XR_NO_PROTOTYPES */
#यदि_अन्तः /* XR_USE_GRAPHICS_API_D3D12 */

#यदि_परिभाषितम् XR_USE_GRAPHICS_API_METAL

// XR_KHR_metal_enable is a preprocessor guard. Do not pass it to API calls.
#परिभाषय XR_KHR_metal_enable 1
#परिभाषय XR_KHR_metal_enable_SPEC_संस्करणम्  3
#परिभाषय XR_KHR_METAL_ENABLE_EXTENSION_NAME "XR_KHR_metal_enable"
// XrGraphicsBindingMetalKHR extends XrSessionCreateInfo
प्रकारनिर्देश संरचना XrGraphicsBindingMetalKHR {
    XrStructureType             type;
    ध्रुव शून्य* XR_MAY_ALIAS    अग्र;
    शून्य* XR_MAY_ALIAS          commandQueue;
} XrGraphicsBindingMetalKHR;

प्रकारनिर्देश संरचना XrSwapchainImageMetalKHR {
    XrStructureType       type;
    शून्य* XR_MAY_ALIAS    अग्र;
    शून्य* XR_MAY_ALIAS    texture;
} XrSwapchainImageMetalKHR;

प्रकारनिर्देश संरचना XrGraphicsRequirementsMetalKHR {
    XrStructureType       type;
    शून्य* XR_MAY_ALIAS    अग्र;
    शून्य* XR_MAY_ALIAS    metalDevice;
} XrGraphicsRequirementsMetalKHR;

प्रकारनिर्देश Xr_परिणाम (XRAPI_PTR *PFN_xrGetMetalGraphicsRequirementsKHR)(XrInstance instance, XrSystemId systemId, XrGraphicsRequirementsMetalKHR* graphicsRequirements);

#यदि_अपरिभाषितम् XR_NO_PROTOTYPES
#यदि_परिभाषितम् XR_EXTENSION_PROTOTYPES
XRAPI_ATTR Xr_परिणाम XRAPI_CALL xrGetMetalGraphicsRequirementsKHR(
    XrInstance                                  instance,
    XrSystemId                                  systemId,
    XrGraphicsRequirementsMetalKHR*             graphicsRequirements);
#यदि_अन्तः /* XR_EXTENSION_PROTOTYPES */
#यदि_अन्तः /* !XR_NO_PROTOTYPES */
#यदि_अन्तः /* XR_USE_GRAPHICS_API_METAL */

#यदि_परिभाषितम् XR_USE_PLATFORM_WIN32

// XR_KHR_win32_convert_performance_counter_time is a preprocessor guard. Do not pass it to API calls.
#परिभाषय XR_KHR_win32_convert_performance_गणक_time 1
#परिभाषय XR_KHR_win32_convert_performance_गणक_time_SPEC_संस्करणम् 1
#परिभाषय XR_KHR_WIN32_CONVERT_PERFORMANCE_गणक_TIME_EXTENSION_NAME "XR_KHR_win32_convert_performance_counter_time"
प्रकारनिर्देश Xr_परिणाम (XRAPI_PTR *PFN_xr_Convert_Win32_Performance_गणक_गन्तव्यम्_Time_KHR)(XrInstance instance, ध्रुव LARGE_INTEGER* performance_गणक, XrTime* time);
प्रकारनिर्देश Xr_परिणाम (XRAPI_PTR *PFN_xr_Convert_Time_गन्तव्यम्_Win32_Performance_गणक_KHR)(XrInstance instance, XrTime time, LARGE_INTEGER* performance_गणक);

#यदि_अपरिभाषितम् XR_NO_PROTOTYPES
#यदि_परिभाषितम् XR_EXTENSION_PROTOTYPES
XRAPI_ATTR Xr_परिणाम XRAPI_CALL xr_Convert_Win32_Performance_गणक_गन्तव्यम्_Time_KHR(
    XrInstance                                  instance,
    ध्रुव LARGE_INTEGER*                        performance_गणक,
    XrTime*                                     time);

XRAPI_ATTR Xr_परिणाम XRAPI_CALL xr_Convert_Time_गन्तव्यम्_Win32_Performance_गणक_KHR(
    XrInstance                                  instance,
    XrTime                                      time,
    LARGE_INTEGER*                              performance_गणक);
#यदि_अन्तः /* XR_EXTENSION_PROTOTYPES */
#यदि_अन्तः /* !XR_NO_PROTOTYPES */
#यदि_अन्तः /* XR_USE_PLATFORM_WIN32 */

#यदि_परिभाषितम् XR_USE_TIMESPEC

// XR_KHR_convert_timespec_time is a preprocessor guard. Do not pass it to API calls.
#परिभाषय XR_KHR_convert_timespec_time 1
#परिभाषय XR_KHR_convert_timespec_time_SPEC_संस्करणम् 1
#परिभाषय XR_KHR_CONVERT_TIMESPEC_TIME_EXTENSION_NAME "XR_KHR_convert_timespec_time"
प्रकारनिर्देश Xr_परिणाम (XRAPI_PTR *PFN_xr_Convert_Timespec_Time_गन्तव्यम्_Time_KHR)(XrInstance instance, ध्रुव संरचना timespec* timespecTime, XrTime* time);
प्रकारनिर्देश Xr_परिणाम (XRAPI_PTR *PFN_xr_Convert_Time_गन्तव्यम्_Timespec_Time_KHR)(XrInstance instance, XrTime time, संरचना timespec* timespecTime);

#यदि_अपरिभाषितम् XR_NO_PROTOTYPES
#यदि_परिभाषितम् XR_EXTENSION_PROTOTYPES
XRAPI_ATTR Xr_परिणाम XRAPI_CALL xr_Convert_Timespec_Time_गन्तव्यम्_Time_KHR(
    XrInstance                                  instance,
    ध्रुव संरचना timespec*                      timespecTime,
    XrTime*                                     time);

XRAPI_ATTR Xr_परिणाम XRAPI_CALL xr_Convert_Time_गन्तव्यम्_Timespec_Time_KHR(
    XrInstance                                  instance,
    XrTime                                      time,
    संरचना timespec*                            timespecTime);
#यदि_अन्तः /* XR_EXTENSION_PROTOTYPES */
#यदि_अन्तः /* !XR_NO_PROTOTYPES */
#यदि_अन्तः /* XR_USE_TIMESPEC */

#यदि_परिभाषितम् XR_USE_PLATFORM_ANDROID

// XR_KHR_loader_init_android is a preprocessor guard. Do not pass it to API calls.
#परिभाषय XR_KHR_loader_init_android 1
#परिभाषय XR_KHR_loader_init_android_SPEC_संस्करणम् 1
#परिभाषय XR_KHR_LOADER_INIT_ANDROID_EXTENSION_NAME "XR_KHR_loader_init_android"
प्रकारनिर्देश संरचना XrLoaderInitInfoAndroidKHR {
    XrStructureType             type;
    ध्रुव शून्य* XR_MAY_ALIAS    अग्र;
    शून्य* XR_MAY_ALIAS          applicationVM;
    शून्य* XR_MAY_ALIAS          applicationContext;
} XrLoaderInitInfoAndroidKHR;

#यदि_अन्तः /* XR_USE_PLATFORM_ANDROID */

#यदि_परिभाषितम् XR_USE_GRAPHICS_API_VULKAN

// XR_KHR_vulkan_enable2 is a preprocessor guard. Do not pass it to API calls.
#परिभाषय XR_KHR_vulkan_enable2 1
#परिभाषय XR_KHR_vulkan_enable2_SPEC_संस्करणम् 4
#परिभाषय XR_KHR_VULKAN_ENABLE2_EXTENSION_NAME "XR_KHR_vulkan_enable2"
प्रकारनिर्देश XrFlags64 XrVulkanInstanceCreateFlagsKHR;

// Flag bits for XrVulkanInstanceCreateFlagsKHR

प्रकारनिर्देश XrFlags64 XrVulkanDeviceCreateFlagsKHR;

// Flag bits for XrVulkanDeviceCreateFlagsKHR

प्रकारनिर्देश संरचना XrVulkanInstanceCreateInfoKHR {
    XrStructureType                   type;
    ध्रुव शून्य* XR_MAY_ALIAS          अग्र;
    XrSystemId                        systemId;
    XrVulkanInstanceCreateFlagsKHR    createFlags;
    PFN_vkGetInstanceProcAddr         pfnGetInstanceProcAddr;
    ध्रुव VkInstanceCreateInfo*       vulkanCreateInfo;
    ध्रुव Vk_आवण्टनम्_Callbacks*      vulkanAllocator;
} XrVulkanInstanceCreateInfoKHR;

प्रकारनिर्देश संरचना XrVulkanDeviceCreateInfoKHR {
    XrStructureType                 type;
    ध्रुव शून्य* XR_MAY_ALIAS        अग्र;
    XrSystemId                      systemId;
    XrVulkanDeviceCreateFlagsKHR    createFlags;
    PFN_vkGetInstanceProcAddr       pfnGetInstanceProcAddr;
    VkPhysicalDevice                vulkanPhysicalDevice;
    ध्रुव VkDeviceCreateInfo*       vulkanCreateInfo;
    ध्रुव Vk_आवण्टनम्_Callbacks*    vulkanAllocator;
} XrVulkanDeviceCreateInfoKHR;

प्रकारनिर्देश XrGraphicsBindingVulkanKHR XrGraphicsBindingVulkan2KHR;

प्रकारनिर्देश संरचना XrVulkanGraphicsDeviceGetInfoKHR {
    XrStructureType             type;
    ध्रुव शून्य* XR_MAY_ALIAS    अग्र;
    XrSystemId                  systemId;
    VkInstance                  vulkanInstance;
} XrVulkanGraphicsDeviceGetInfoKHR;

प्रकारनिर्देश XrSwapchainImageVulkanKHR XrSwapchainImageVulkan2KHR;

प्रकारनिर्देश XrGraphicsRequirementsVulkanKHR XrGraphicsRequirementsVulkan2KHR;

प्रकारनिर्देश Xr_परिणाम (XRAPI_PTR *PFN_xrCreateVulkanInstanceKHR)(XrInstance instance, ध्रुव XrVulkanInstanceCreateInfoKHR* createInfo, VkInstance* vulkanInstance, Vk_परिणाम* vulkan_परिणाम);
प्रकारनिर्देश Xr_परिणाम (XRAPI_PTR *PFN_xrCreateVulkanDeviceKHR)(XrInstance instance, ध्रुव XrVulkanDeviceCreateInfoKHR* createInfo, VkDevice* vulkanDevice, Vk_परिणाम* vulkan_परिणाम);
प्रकारनिर्देश Xr_परिणाम (XRAPI_PTR *PFN_xrGetVulkanGraphicsDevice2KHR)(XrInstance instance, ध्रुव XrVulkanGraphicsDeviceGetInfoKHR* getInfo, VkPhysicalDevice* vulkanPhysicalDevice);
प्रकारनिर्देश Xr_परिणाम (XRAPI_PTR *PFN_xrGetVulkanGraphicsRequirements2KHR)(XrInstance instance, XrSystemId systemId, XrGraphicsRequirementsVulkanKHR* graphicsRequirements);

#यदि_अपरिभाषितम् XR_NO_PROTOTYPES
#यदि_परिभाषितम् XR_EXTENSION_PROTOTYPES
XRAPI_ATTR Xr_परिणाम XRAPI_CALL xrCreateVulkanInstanceKHR(
    XrInstance                                  instance,
    ध्रुव XrVulkanInstanceCreateInfoKHR*        createInfo,
    VkInstance*                                 vulkanInstance,
    Vk_परिणाम*                                   vulkan_परिणाम);

XRAPI_ATTR Xr_परिणाम XRAPI_CALL xrCreateVulkanDeviceKHR(
    XrInstance                                  instance,
    ध्रुव XrVulkanDeviceCreateInfoKHR*          createInfo,
    VkDevice*                                   vulkanDevice,
    Vk_परिणाम*                                   vulkan_परिणाम);

XRAPI_ATTR Xr_परिणाम XRAPI_CALL xrGetVulkanGraphicsDevice2KHR(
    XrInstance                                  instance,
    ध्रुव XrVulkanGraphicsDeviceGetInfoKHR*     getInfo,
    VkPhysicalDevice*                           vulkanPhysicalDevice);

XRAPI_ATTR Xr_परिणाम XRAPI_CALL xrGetVulkanGraphicsRequirements2KHR(
    XrInstance                                  instance,
    XrSystemId                                  systemId,
    XrGraphicsRequirementsVulkanKHR*            graphicsRequirements);
#यदि_अन्तः /* XR_EXTENSION_PROTOTYPES */
#यदि_अन्तः /* !XR_NO_PROTOTYPES */
#यदि_अन्तः /* XR_USE_GRAPHICS_API_VULKAN */

#यदि_परिभाषितम् XR_USE_PLATFORM_EGL

// XR_MNDX_egl_enable is a preprocessor guard. Do not pass it to API calls.
#परिभाषय XR_MNDX_egl_enable 1
#परिभाषय XR_MNDX_egl_enable_SPEC_संस्करणम्   2
#परिभाषय XR_MNDX_EGL_ENABLE_EXTENSION_NAME "XR_MNDX_egl_enable"
प्रकारनिर्देश PFN_xrVoidFunction (*PFN_xr_Egl_Get_Proc_स्थानाङ्कः_MNDX)(ध्रुव वर्ण *name);
// XrGraphicsBindingEGLMNDX extends XrSessionCreateInfo
प्रकारनिर्देश संरचना XrGraphicsBindingEGLMNDX {
    XrStructureType                type;
    ध्रुव शून्य* XR_MAY_ALIAS       अग्र;
    PFN_xr_Egl_Get_Proc_स्थानाङ्कः_MNDX    get_Proc_स्थानाङ्कः;
    EGLDisplay                     display;
    EGLConfig                      config;
    EGLContext                     context;
} XrGraphicsBindingEGLMNDX;

#यदि_अन्तः /* XR_USE_PLATFORM_EGL */

#यदि_परिभाषितम् XR_USE_PLATFORM_WIN32

// XR_MSFT_perception_anchor_interop is a preprocessor guard. Do not pass it to API calls.
#परिभाषय XR_MSFT_perception_anchor_interop 1
#परिभाषय XR_MSFT_perception_anchor_interop_SPEC_संस्करणम् 1
#परिभाषय XR_MSFT_PERCEPTION_ANCHOR_INTEROP_EXTENSION_NAME "XR_MSFT_perception_anchor_interop"
प्रकारनिर्देश Xr_परिणाम (XRAPI_PTR *PFN_xrCreateSpatialAnchorFromPerceptionAnchorMSFT)(XrSession session, IUnknown* perceptionAnchor, XrSpatialAnchorMSFT* anchor);
प्रकारनिर्देश Xr_परिणाम (XRAPI_PTR *PFN_xrTryGetPerceptionAnchorFromSpatialAnchorMSFT)(XrSession session, XrSpatialAnchorMSFT anchor, IUnknown** perceptionAnchor);

#यदि_अपरिभाषितम् XR_NO_PROTOTYPES
#यदि_परिभाषितम् XR_EXTENSION_PROTOTYPES
XRAPI_ATTR Xr_परिणाम XRAPI_CALL xrCreateSpatialAnchorFromPerceptionAnchorMSFT(
    XrSession                                   session,
    IUnknown*                                   perceptionAnchor,
    XrSpatialAnchorMSFT*                        anchor);

XRAPI_ATTR Xr_परिणाम XRAPI_CALL xrTryGetPerceptionAnchorFromSpatialAnchorMSFT(
    XrSession                                   session,
    XrSpatialAnchorMSFT                         anchor,
    IUnknown**                                  perceptionAnchor);
#यदि_अन्तः /* XR_EXTENSION_PROTOTYPES */
#यदि_अन्तः /* !XR_NO_PROTOTYPES */
#यदि_अन्तः /* XR_USE_PLATFORM_WIN32 */

#यदि_परिभाषितम् XR_USE_PLATFORM_WIN32

// XR_MSFT_holographic_window_attachment is a preprocessor guard. Do not pass it to API calls.
#परिभाषय XR_MSFT_holographic_गवाक्षः_attachment 1
#परिभाषय XR_MSFT_holographic_गवाक्षः_attachment_SPEC_संस्करणम् 1
#परिभाषय XR_MSFT_HOLOGRAPHIC_गवाक्षः_ATTACHMENT_EXTENSION_NAME "XR_MSFT_holographic_window_attachment"
#यदि_परिभाषितम् XR_USE_PLATFORM_WIN32
// XrHolographicWindowAttachmentMSFT extends XrSessionCreateInfo
प्रकारनिर्देश संरचना Xr_Holographic_गवाक्षः_Attachment_MSFT {
    XrStructureType             type;
    ध्रुव शून्य* XR_MAY_ALIAS    अग्र;
    IUnknown*                   holographicSpace;
    IUnknown*                   core_गवाक्षः;
} Xr_Holographic_गवाक्षः_Attachment_MSFT;
#यदि_अन्तः // XR_USE_PLATFORM_WIN32

#यदि_अन्तः /* XR_USE_PLATFORM_WIN32 */

#यदि_परिभाषितम् XR_USE_PLATFORM_ANDROID

// XR_FB_android_surface_swapchain_create is a preprocessor guard. Do not pass it to API calls.
#परिभाषय XR_FB_android_surface_swapchain_create 1
#परिभाषय XR_FB_android_surface_swapchain_create_SPEC_संस्करणम् 1
#परिभाषय XR_FB_ANDROID_SURFACE_SWAPCHAIN_CREATE_EXTENSION_NAME "XR_FB_android_surface_swapchain_create"
प्रकारनिर्देश XrFlags64 XrAndroidSurfaceSwapchainFlagsFB;

// Flag bits for XrAndroidSurfaceSwapchainFlagsFB
स्थिर ध्रुव XrAndroidSurfaceSwapchainFlagsFB XR_ANDROID_SURFACE_SWAPCHAIN_SYNCHRONOUS_BIT_FB = 0x00000001;
स्थिर ध्रुव XrAndroidSurfaceSwapchainFlagsFB XR_ANDROID_SURFACE_SWAPCHAIN_USE_TIMESTAMPS_BIT_FB = 0x00000002;

#यदि_परिभाषितम् XR_USE_PLATFORM_ANDROID
// XrAndroidSurfaceSwapchainCreateInfoFB extends XrSwapchainCreateInfo
प्रकारनिर्देश संरचना XrAndroidSurfaceSwapchainCreateInfoFB {
    XrStructureType                     type;
    ध्रुव शून्य* XR_MAY_ALIAS            अग्र;
    XrAndroidSurfaceSwapchainFlagsFB    createFlags;
} XrAndroidSurfaceSwapchainCreateInfoFB;
#यदि_अन्तः // XR_USE_PLATFORM_ANDROID

#यदि_अन्तः /* XR_USE_PLATFORM_ANDROID */

#यदि_परिभाषितम् XR_USE_PLATFORM_ML

// XR_ML_compat is a preprocessor guard. Do not pass it to API calls.
#परिभाषय XR_ML_compat 1
#परिभाषय XR_ML_compat_SPEC_संस्करणम्         1
#परिभाषय XR_ML_COMPAT_EXTENSION_NAME       "XR_ML_compat"
प्रकारनिर्देश संरचना XrCoordinateSpaceCreateInfoML {
    XrStructureType             type;
    ध्रुव शून्य* XR_MAY_ALIAS    अग्र;
    MLCoordinateFrameUID        cfuid;
    XrPosef                     pose_अन्तर्_Coordinate_Space;
} XrCoordinateSpaceCreateInfoML;

प्रकारनिर्देश Xr_परिणाम (XRAPI_PTR *PFN_xrCreateSpaceFromCoordinateFrameUIDML)(XrSession session, ध्रुव XrCoordinateSpaceCreateInfoML *createInfo, XrSpace* space);

#यदि_अपरिभाषितम् XR_NO_PROTOTYPES
#यदि_परिभाषितम् XR_EXTENSION_PROTOTYPES
XRAPI_ATTR Xr_परिणाम XRAPI_CALL xrCreateSpaceFromCoordinateFrameUIDML(
    XrSession                                   session,
    ध्रुव XrCoordinateSpaceCreateInfoML *       createInfo,
    XrSpace*                                    space);
#यदि_अन्तः /* XR_EXTENSION_PROTOTYPES */
#यदि_अन्तः /* !XR_NO_PROTOTYPES */
#यदि_अन्तः /* XR_USE_PLATFORM_ML */

#यदि_परिभाषितम् XR_USE_PLATFORM_WIN32

// XR_OCULUS_audio_device_guid is a preprocessor guard. Do not pass it to API calls.
#परिभाषय XR_OCULUS_audio_device_guid 1
#परिभाषय XR_OCULUS_audio_device_guid_SPEC_संस्करणम् 1
#परिभाषय XR_OCULUS_AUDIO_DEVICE_GUID_EXTENSION_NAME "XR_OCULUS_audio_device_guid"
#परिभाषय XR_MAX_AUDIO_DEVICE_STR_आकार_OCULUS 128
प्रकारनिर्देश Xr_परिणाम (XRAPI_PTR *PFN_xrGetAudioOutputDeviceGuidOculus)(XrInstance instance, wchar_t बफर_2[XR_MAX_AUDIO_DEVICE_STR_आकार_OCULUS]);
प्रकारनिर्देश Xr_परिणाम (XRAPI_PTR *PFN_xr_Get_Audio_निवेशः_Device_Guid_Oculus)(XrInstance instance, wchar_t बफर_2[XR_MAX_AUDIO_DEVICE_STR_आकार_OCULUS]);

#यदि_अपरिभाषितम् XR_NO_PROTOTYPES
#यदि_परिभाषितम् XR_EXTENSION_PROTOTYPES
XRAPI_ATTR Xr_परिणाम XRAPI_CALL xrGetAudioOutputDeviceGuidOculus(
    XrInstance                                  instance,
    wchar_t                                     बफर_2[XR_MAX_AUDIO_DEVICE_STR_आकार_OCULUS]);

XRAPI_ATTR Xr_परिणाम XRAPI_CALL xr_Get_Audio_निवेशः_Device_Guid_Oculus(
    XrInstance                                  instance,
    wchar_t                                     बफर_2[XR_MAX_AUDIO_DEVICE_STR_आकार_OCULUS]);
#यदि_अन्तः /* XR_EXTENSION_PROTOTYPES */
#यदि_अन्तः /* !XR_NO_PROTOTYPES */
#यदि_अन्तः /* XR_USE_PLATFORM_WIN32 */

#यदि_परिभाषितम् XR_USE_GRAPHICS_API_VULKAN

// XR_FB_foveation_vulkan is a preprocessor guard. Do not pass it to API calls.
#परिभाषय XR_FB_foveation_vulkan 1
#परिभाषय XR_FB_foveation_vulkan_SPEC_संस्करणम् 1
#परिभाषय XR_FB_FOVEATION_VULKAN_EXTENSION_NAME "XR_FB_foveation_vulkan"
// XrSwapchainImageFoveationVulkanFB extends XrSwapchainImageVulkanKHR
प्रकारनिर्देश संरचना XrSwapchainImageFoveationVulkanFB {
    XrStructureType       type;
    शून्य* XR_MAY_ALIAS    अग्र;
    VkImage               image;
    uint32_t              विस्तारः;
    uint32_t              height;
} XrSwapchainImageFoveationVulkanFB;

#यदि_अन्तः /* XR_USE_GRAPHICS_API_VULKAN */

#यदि_परिभाषितम् XR_USE_PLATFORM_ANDROID

// XR_FB_swapchain_update_state_android_surface is a preprocessor guard. Do not pass it to API calls.
#परिभाषय XR_FB_swapchain_update_state_android_surface 1
#परिभाषय XR_FB_swapchain_update_state_android_surface_SPEC_संस्करणम् 1
#परिभाषय XR_FB_SWAPCHAIN_UPDATE_STATE_ANDROID_SURFACE_EXTENSION_NAME "XR_FB_swapchain_update_state_android_surface"
#यदि_परिभाषितम् XR_USE_PLATFORM_ANDROID
प्रकारनिर्देश संरचना XrSwapchainStateAndroidSurfaceDimensionsFB {
    XrStructureType       type;
    शून्य* XR_MAY_ALIAS    अग्र;
    uint32_t              विस्तारः;
    uint32_t              height;
} XrSwapchainStateAndroidSurfaceDimensionsFB;
#यदि_अन्तः // XR_USE_PLATFORM_ANDROID

#यदि_अन्तः /* XR_USE_PLATFORM_ANDROID */

#यदि_परिभाषितम् XR_USE_GRAPHICS_API_OPENGL_ES

// XR_FB_swapchain_update_state_opengl_es is a preprocessor guard. Do not pass it to API calls.
#परिभाषय XR_FB_swapchain_update_state_opengl_es 1
#परिभाषय XR_FB_swapchain_update_state_opengl_es_SPEC_संस्करणम् 1
#परिभाषय XR_FB_SWAPCHAIN_UPDATE_STATE_OPENGL_ES_EXTENSION_NAME "XR_FB_swapchain_update_state_opengl_es"
#यदि_परिभाषितम् XR_USE_GRAPHICS_API_OPENGL_ES
प्रकारनिर्देश संरचना XrSwapchainStateSamplerOpenGLESFB {
    XrStructureType       type;
    शून्य* XR_MAY_ALIAS    अग्र;
    EGLenum               minFilter;
    EGLenum               magFilter;
    EGLenum               wrap_बहुलकम्_S;
    EGLenum               wrap_बहुलकम्_T;
    EGLenum               swizzleRed;
    EGLenum               swizzleGreen;
    EGLenum               swizzleBlue;
    EGLenum               swizzleAlpha;
    भिन्न                 maxAnisotropy;
    XrColor4f             borderColor;
} XrSwapchainStateSamplerOpenGLESFB;
#यदि_अन्तः // XR_USE_GRAPHICS_API_OPENGL_ES

#यदि_अन्तः /* XR_USE_GRAPHICS_API_OPENGL_ES */

#यदि_परिभाषितम् XR_USE_GRAPHICS_API_VULKAN

// XR_FB_swapchain_update_state_vulkan is a preprocessor guard. Do not pass it to API calls.
#परिभाषय XR_FB_swapchain_update_state_vulkan 1
#परिभाषय XR_FB_swapchain_update_state_vulkan_SPEC_संस्करणम् 1
#परिभाषय XR_FB_SWAPCHAIN_UPDATE_STATE_VULKAN_EXTENSION_NAME "XR_FB_swapchain_update_state_vulkan"
#यदि_परिभाषितम् XR_USE_GRAPHICS_API_VULKAN
प्रकारनिर्देश संरचना XrSwapchainStateSamplerVulkanFB {
    XrStructureType         type;
    शून्य* XR_MAY_ALIAS      अग्र;
    VkFilter                minFilter;
    VkFilter                magFilter;
    Vk_Sampler_Mipmap_बहुलकम्     mipmap_बहुलकम्;
    Vk_Sampler_स्थानाङ्कः_बहुलकम्    wrap_बहुलकम्_S;
    Vk_Sampler_स्थानाङ्कः_बहुलकम्    wrap_बहुलकम्_T;
    VkComponentSwizzle      swizzleRed;
    VkComponentSwizzle      swizzleGreen;
    VkComponentSwizzle      swizzleBlue;
    VkComponentSwizzle      swizzleAlpha;
    भिन्न                   maxAnisotropy;
    XrColor4f               borderColor;
} XrSwapchainStateSamplerVulkanFB;
#यदि_अन्तः // XR_USE_GRAPHICS_API_VULKAN

#यदि_अन्तः /* XR_USE_GRAPHICS_API_VULKAN */

#यदि_परिभाषितम् XR_USE_GRAPHICS_API_VULKAN

// XR_META_vulkan_swapchain_create_info is a preprocessor guard. Do not pass it to API calls.
#परिभाषय XR_META_vulkan_swapchain_create_info 1
#परिभाषय XR_META_vulkan_swapchain_create_info_SPEC_संस्करणम् 1
#परिभाषय XR_META_VULKAN_SWAPCHAIN_CREATE_INFO_EXTENSION_NAME "XR_META_vulkan_swapchain_create_info"
// XrVulkanSwapchainCreateInfoMETA extends XrSwapchainCreateInfo
प्रकारनिर्देश संरचना XrVulkanSwapchainCreateInfoMETA {
    XrStructureType             type;
    ध्रुव शून्य* XR_MAY_ALIAS    अग्र;
    VkImageCreateFlags          additionalCreateFlags;
    VkImageUsageFlags           additionalUsageFlags;
} XrVulkanSwapchainCreateInfoMETA;

#यदि_अन्तः /* XR_USE_GRAPHICS_API_VULKAN */

#यदि_परिभाषितम् XR_USE_PLATFORM_ANDROID

// XR_ANDROID_anchor_sharing_export is a preprocessor guard. Do not pass it to API calls.
#परिभाषय XR_ANDROID_anchor_sharing_export 1
#परिभाषय XR_ANDROID_anchor_sharing_export_SPEC_संस्करणम् 1
#परिभाषय XR_ANDROID_ANCHOR_SHARING_EXPORT_EXTENSION_NAME "XR_ANDROID_anchor_sharing_export"
प्रकारनिर्देश संरचना XrAnchorSharingInfoANDROID {
    XrStructureType             type;
    ध्रुव शून्य* XR_MAY_ALIAS    अग्र;
    XrSpace                     anchor;
} XrAnchorSharingInfoANDROID;

प्रकारनिर्देश संरचना XrAnchorSharingTokenANDROID {
    XrStructureType       type;
    शून्य* XR_MAY_ALIAS    अग्र;
    संरचना AIBinder*      token;
} XrAnchorSharingTokenANDROID;

// XrSystemAnchorSharingExportPropertiesANDROID extends XrSystemProperties
प्रकारनिर्देश संरचना XrSystemAnchorSharingExportPropertiesANDROID {
    XrStructureType       type;
    शून्य* XR_MAY_ALIAS    अग्र;
    XrBool32              supportsAnchorSharingExport;
} XrSystemAnchorSharingExportPropertiesANDROID;

प्रकारनिर्देश Xr_परिणाम (XRAPI_PTR *PFN_xrShareAnchorANDROID)(XrSession session, ध्रुव XrAnchorSharingInfoANDROID* sharingInfo, XrAnchorSharingTokenANDROID* anchorToken);
प्रकारनिर्देश Xr_परिणाम (XRAPI_PTR *PFN_xrUnshareAnchorANDROID)(XrSession session, XrSpace anchor);

#यदि_अपरिभाषितम् XR_NO_PROTOTYPES
#यदि_परिभाषितम् XR_EXTENSION_PROTOTYPES
XRAPI_ATTR Xr_परिणाम XRAPI_CALL xrShareAnchorANDROID(
    XrSession                                   session,
    ध्रुव XrAnchorSharingInfoANDROID*           sharingInfo,
    XrAnchorSharingTokenANDROID*                anchorToken);

XRAPI_ATTR Xr_परिणाम XRAPI_CALL xrUnshareAnchorANDROID(
    XrSession                                   session,
    XrSpace                                     anchor);
#यदि_अन्तः /* XR_EXTENSION_PROTOTYPES */
#यदि_अन्तः /* !XR_NO_PROTOTYPES */
#यदि_अन्तः /* XR_USE_PLATFORM_ANDROID */

#यदि_परिभाषितम् __cplusplus
}
#यदि_अन्तः

#यदि_अन्तः
