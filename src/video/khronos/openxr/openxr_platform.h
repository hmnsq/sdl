#अगर_अघोषित OPENXR_PLATFORM_H_
#घोषणा OPENXR_PLATFORM_H_ 1

/*
** Copyright 2017-2026 The Khronos Group Inc.
**
** SPDX-License-Identifier: Apache-2.0 OR MIT
*/

/*
** This header is generated from the Khronos OpenXR XML API Registry.
**
*/

#समावेश "openxr.h"

#अगर_घोषित __cplusplus
बाह्य "C" {
#पूर्ण_अगर


#अगर_घोषित XR_USE_PLATFORM_ANDROID

// XR_KHR_android_thread_settings is a preprocessor guard. Do not pass it to API calls.
#घोषणा XR_KHR_android_thread_settings 1
#घोषणा XR_KHR_android_thread_settings_SPEC_VERSION 6
#घोषणा XR_KHR_ANDROID_THREAD_SETTINGS_EXTENSION_NAME "XR_KHR_android_thread_settings"

प्रकार क्रमागत XrAndroidThreadTypeKHR {
    XR_ANDROID_THREAD_TYPE_APPLICATION_MAIN_KHR = 1,
    XR_ANDROID_THREAD_TYPE_APPLICATION_WORKER_KHR = 2,
    XR_ANDROID_THREAD_TYPE_RENDERER_MAIN_KHR = 3,
    XR_ANDROID_THREAD_TYPE_RENDERER_WORKER_KHR = 4,
    XR_ANDROID_THREAD_TYPE_MAX_ENUM_KHR = 0x7FFFFFFF
} XrAndroidThreadTypeKHR;
प्रकार Xr_परिणाम (XRAPI_PTR *PFN_xrSetAndroidApplicationThreadKHR)(XrSession session, XrAndroidThreadTypeKHR threadType, uint32_t threadId);

#अगर_अघोषित XR_NO_PROTOTYPES
#अगर_घोषित XR_EXTENSION_PROTOTYPES
XRAPI_ATTR Xr_परिणाम XRAPI_CALL xrSetAndroidApplicationThreadKHR(
    XrSession                                   session,
    XrAndroidThreadTypeKHR                      threadType,
    uint32_t                                    threadId);
#पूर्ण_अगर /* XR_EXTENSION_PROTOTYPES */
#पूर्ण_अगर /* !XR_NO_PROTOTYPES */
#पूर्ण_अगर /* XR_USE_PLATFORM_ANDROID */

#अगर_घोषित XR_USE_PLATFORM_ANDROID

// XR_KHR_android_surface_swapchain is a preprocessor guard. Do not pass it to API calls.
#घोषणा XR_KHR_android_surface_swapchain 1
#घोषणा XR_KHR_android_surface_swapchain_SPEC_VERSION 4
#घोषणा XR_KHR_ANDROID_SURFACE_SWAPCHAIN_EXTENSION_NAME "XR_KHR_android_surface_swapchain"
प्रकार Xr_परिणाम (XRAPI_PTR *PFN_xrCreateSwapchainAndroidSurfaceKHR)(XrSession session, स्थिर XrSwapchainCreateInfo* info, XrSwapchain* swapchain, jobject* surface);

#अगर_अघोषित XR_NO_PROTOTYPES
#अगर_घोषित XR_EXTENSION_PROTOTYPES
XRAPI_ATTR Xr_परिणाम XRAPI_CALL xrCreateSwapchainAndroidSurfaceKHR(
    XrSession                                   session,
    स्थिर XrSwapchainCreateInfo*                info,
    XrSwapchain*                                swapchain,
    jobject*                                    surface);
#पूर्ण_अगर /* XR_EXTENSION_PROTOTYPES */
#पूर्ण_अगर /* !XR_NO_PROTOTYPES */
#पूर्ण_अगर /* XR_USE_PLATFORM_ANDROID */

#अगर_घोषित XR_USE_PLATFORM_ANDROID

// XR_KHR_android_create_instance is a preprocessor guard. Do not pass it to API calls.
#घोषणा XR_KHR_android_create_instance 1
#घोषणा XR_KHR_android_create_instance_SPEC_VERSION 3
#घोषणा XR_KHR_ANDROID_CREATE_INSTANCE_EXTENSION_NAME "XR_KHR_android_create_instance"
// XrInstanceCreateInfoAndroidKHR extends XrInstanceCreateInfo
प्रकार काष्ठा XrInstanceCreateInfoAndroidKHR {
    XrStructureType             type;
    स्थिर व्योम* XR_MAY_ALIAS    अग्र;
    व्योम* XR_MAY_ALIAS          applicationVM;
    व्योम* XR_MAY_ALIAS          applicationActivity;
} XrInstanceCreateInfoAndroidKHR;

#पूर्ण_अगर /* XR_USE_PLATFORM_ANDROID */

#अगर_घोषित XR_USE_GRAPHICS_API_VULKAN

// XR_KHR_vulkan_swapchain_format_list is a preprocessor guard. Do not pass it to API calls.
#घोषणा XR_KHR_vulkan_swapchain_format_list 1
#घोषणा XR_KHR_vulkan_swapchain_format_list_SPEC_VERSION 5
#घोषणा XR_KHR_VULKAN_SWAPCHAIN_FORMAT_LIST_EXTENSION_NAME "XR_KHR_vulkan_swapchain_format_list"
// XrVulkanSwapchainFormatListCreateInfoKHR extends XrSwapchainCreateInfo
प्रकार काष्ठा XrVulkanSwapchainFormatListCreateInfoKHR {
    XrStructureType             type;
    स्थिर व्योम* XR_MAY_ALIAS    अग्र;
    uint32_t                    view_Format_गिनती;
    स्थिर VkFormat*             viewFormats;
} XrVulkanSwapchainFormatListCreateInfoKHR;

#पूर्ण_अगर /* XR_USE_GRAPHICS_API_VULKAN */

#अगर_घोषित XR_USE_GRAPHICS_API_OPENGL

// XR_KHR_opengl_enable is a preprocessor guard. Do not pass it to API calls.
#घोषणा XR_KHR_opengl_enable 1
#घोषणा XR_KHR_opengl_enable_SPEC_VERSION 12
#घोषणा XR_KHR_OPENGL_ENABLE_EXTENSION_NAME "XR_KHR_opengl_enable"
#अगर_घोषित XR_USE_PLATFORM_WIN32
// XrGraphicsBindingOpenGLWin32KHR extends XrSessionCreateInfo
प्रकार काष्ठा XrGraphicsBindingOpenGLWin32KHR {
    XrStructureType             type;
    स्थिर व्योम* XR_MAY_ALIAS    अग्र;
    HDC                         hDC;
    HGLRC                       hGLRC;
} XrGraphicsBindingOpenGLWin32KHR;
#पूर्ण_अगर // XR_USE_PLATFORM_WIN32

#अगर_घोषित XR_USE_PLATFORM_XLIB
// XrGraphicsBindingOpenGLXlibKHR extends XrSessionCreateInfo
प्रकार काष्ठा XrGraphicsBindingOpenGLXlibKHR {
    XrStructureType             type;
    स्थिर व्योम* XR_MAY_ALIAS    अग्र;
    Display*                    xDisplay;
    uint32_t                    visualid;
    GLXFBConfig                 glxFBConfig;
    GLXDrawable                 glxDrawable;
    GLXContext                  glxContext;
} XrGraphicsBindingOpenGLXlibKHR;
#पूर्ण_अगर // XR_USE_PLATFORM_XLIB

#अगर_घोषित XR_USE_PLATFORM_XCB
// XrGraphicsBindingOpenGLXcbKHR extends XrSessionCreateInfo
प्रकार काष्ठा XrGraphicsBindingOpenGLXcbKHR {
    XrStructureType             type;
    स्थिर व्योम* XR_MAY_ALIAS    अग्र;
    xcb_connection_t*           connection;
    uint32_t                    screen_संख्या;
    xcb_glx_fbconfig_t          fbconfigid;
    xcb_visualid_t              visualid;
    xcb_glx_drawable_t          glxDrawable;
    xcb_glx_context_t           glxContext;
} XrGraphicsBindingOpenGLXcbKHR;
#पूर्ण_अगर // XR_USE_PLATFORM_XCB

#अगर_घोषित XR_USE_PLATFORM_WAYLAND
// XrGraphicsBindingOpenGLWaylandKHR extends XrSessionCreateInfo
प्रकार काष्ठा XrGraphicsBindingOpenGLWaylandKHR {
    XrStructureType             type;
    स्थिर व्योम* XR_MAY_ALIAS    अग्र;
    काष्ठा wl_display*          display;
} XrGraphicsBindingOpenGLWaylandKHR;
#पूर्ण_अगर // XR_USE_PLATFORM_WAYLAND

प्रकार काष्ठा XrSwapchainImageOpenGLKHR {
    XrStructureType       type;
    व्योम* XR_MAY_ALIAS    अग्र;
    uint32_t              image;
} XrSwapchainImageOpenGLKHR;

प्रकार काष्ठा XrGraphicsRequirementsOpenGLKHR {
    XrStructureType       type;
    व्योम* XR_MAY_ALIAS    अग्र;
    XrVersion             minApiVersionSupported;
    XrVersion             maxApiVersionSupported;
} XrGraphicsRequirementsOpenGLKHR;

प्रकार Xr_परिणाम (XRAPI_PTR *PFN_xrGetOpenGLGraphicsRequirementsKHR)(XrInstance instance, XrSystemId systemId, XrGraphicsRequirementsOpenGLKHR* graphicsRequirements);

#अगर_अघोषित XR_NO_PROTOTYPES
#अगर_घोषित XR_EXTENSION_PROTOTYPES
XRAPI_ATTR Xr_परिणाम XRAPI_CALL xrGetOpenGLGraphicsRequirementsKHR(
    XrInstance                                  instance,
    XrSystemId                                  systemId,
    XrGraphicsRequirementsOpenGLKHR*            graphicsRequirements);
#पूर्ण_अगर /* XR_EXTENSION_PROTOTYPES */
#पूर्ण_अगर /* !XR_NO_PROTOTYPES */
#पूर्ण_अगर /* XR_USE_GRAPHICS_API_OPENGL */

#अगर_घोषित XR_USE_GRAPHICS_API_OPENGL_ES

// XR_KHR_opengl_es_enable is a preprocessor guard. Do not pass it to API calls.
#घोषणा XR_KHR_opengl_es_enable 1
#घोषणा XR_KHR_opengl_es_enable_SPEC_VERSION 10
#घोषणा XR_KHR_OPENGL_ES_ENABLE_EXTENSION_NAME "XR_KHR_opengl_es_enable"
#अगर_घोषित XR_USE_PLATFORM_ANDROID
// XrGraphicsBindingOpenGLESAndroidKHR extends XrSessionCreateInfo
प्रकार काष्ठा XrGraphicsBindingOpenGLESAndroidKHR {
    XrStructureType             type;
    स्थिर व्योम* XR_MAY_ALIAS    अग्र;
    EGLDisplay                  display;
    EGLConfig                   config;
    EGLContext                  context;
} XrGraphicsBindingOpenGLESAndroidKHR;
#पूर्ण_अगर // XR_USE_PLATFORM_ANDROID

प्रकार काष्ठा XrSwapchainImageOpenGLESKHR {
    XrStructureType       type;
    व्योम* XR_MAY_ALIAS    अग्र;
    uint32_t              image;
} XrSwapchainImageOpenGLESKHR;

प्रकार काष्ठा XrGraphicsRequirementsOpenGLESKHR {
    XrStructureType       type;
    व्योम* XR_MAY_ALIAS    अग्र;
    XrVersion             minApiVersionSupported;
    XrVersion             maxApiVersionSupported;
} XrGraphicsRequirementsOpenGLESKHR;

प्रकार Xr_परिणाम (XRAPI_PTR *PFN_xrGetOpenGLESGraphicsRequirementsKHR)(XrInstance instance, XrSystemId systemId, XrGraphicsRequirementsOpenGLESKHR* graphicsRequirements);

#अगर_अघोषित XR_NO_PROTOTYPES
#अगर_घोषित XR_EXTENSION_PROTOTYPES
XRAPI_ATTR Xr_परिणाम XRAPI_CALL xrGetOpenGLESGraphicsRequirementsKHR(
    XrInstance                                  instance,
    XrSystemId                                  systemId,
    XrGraphicsRequirementsOpenGLESKHR*          graphicsRequirements);
#पूर्ण_अगर /* XR_EXTENSION_PROTOTYPES */
#पूर्ण_अगर /* !XR_NO_PROTOTYPES */
#पूर्ण_अगर /* XR_USE_GRAPHICS_API_OPENGL_ES */

#अगर_घोषित XR_USE_GRAPHICS_API_VULKAN

// XR_KHR_vulkan_enable is a preprocessor guard. Do not pass it to API calls.
#घोषणा XR_KHR_vulkan_enable 1
#घोषणा XR_KHR_vulkan_enable_SPEC_VERSION 10
#घोषणा XR_KHR_VULKAN_ENABLE_EXTENSION_NAME "XR_KHR_vulkan_enable"
// XrGraphicsBindingVulkanKHR extends XrSessionCreateInfo
प्रकार काष्ठा XrGraphicsBindingVulkanKHR {
    XrStructureType             type;
    स्थिर व्योम* XR_MAY_ALIAS    अग्र;
    VkInstance                  instance;
    VkPhysicalDevice            physicalDevice;
    VkDevice                    device;
    uint32_t                    queue_Family_सूचकांक;
    uint32_t                    queue_सूचकांक;
} XrGraphicsBindingVulkanKHR;

प्रकार काष्ठा XrSwapchainImageVulkanKHR {
    XrStructureType       type;
    व्योम* XR_MAY_ALIAS    अग्र;
    VkImage               image;
} XrSwapchainImageVulkanKHR;

प्रकार काष्ठा XrGraphicsRequirementsVulkanKHR {
    XrStructureType       type;
    व्योम* XR_MAY_ALIAS    अग्र;
    XrVersion             minApiVersionSupported;
    XrVersion             maxApiVersionSupported;
} XrGraphicsRequirementsVulkanKHR;

प्रकार Xr_परिणाम (XRAPI_PTR *PFN_xrGetVulkanInstanceExtensionsKHR)(XrInstance instance, XrSystemId systemId, uint32_t बफर_Capacity_निवेश, uint32_t* बफर_गिनती_Output, अक्षर* बफर_2);
प्रकार Xr_परिणाम (XRAPI_PTR *PFN_xrGetVulkanDeviceExtensionsKHR)(XrInstance instance, XrSystemId systemId, uint32_t बफर_Capacity_निवेश, uint32_t* बफर_गिनती_Output, अक्षर* बफर_2);
प्रकार Xr_परिणाम (XRAPI_PTR *PFN_xrGetVulkanGraphicsDeviceKHR)(XrInstance instance, XrSystemId systemId, VkInstance vkInstance, VkPhysicalDevice* vkPhysicalDevice);
प्रकार Xr_परिणाम (XRAPI_PTR *PFN_xrGetVulkanGraphicsRequirementsKHR)(XrInstance instance, XrSystemId systemId, XrGraphicsRequirementsVulkanKHR* graphicsRequirements);

#अगर_अघोषित XR_NO_PROTOTYPES
#अगर_घोषित XR_EXTENSION_PROTOTYPES
XRAPI_ATTR Xr_परिणाम XRAPI_CALL xrGetVulkanInstanceExtensionsKHR(
    XrInstance                                  instance,
    XrSystemId                                  systemId,
    uint32_t                                    बफर_Capacity_निवेश,
    uint32_t*                                   बफर_गिनती_Output,
    अक्षर*                                       बफर_2);

XRAPI_ATTR Xr_परिणाम XRAPI_CALL xrGetVulkanDeviceExtensionsKHR(
    XrInstance                                  instance,
    XrSystemId                                  systemId,
    uint32_t                                    बफर_Capacity_निवेश,
    uint32_t*                                   बफर_गिनती_Output,
    अक्षर*                                       बफर_2);

XRAPI_ATTR Xr_परिणाम XRAPI_CALL xrGetVulkanGraphicsDeviceKHR(
    XrInstance                                  instance,
    XrSystemId                                  systemId,
    VkInstance                                  vkInstance,
    VkPhysicalDevice*                           vkPhysicalDevice);

XRAPI_ATTR Xr_परिणाम XRAPI_CALL xrGetVulkanGraphicsRequirementsKHR(
    XrInstance                                  instance,
    XrSystemId                                  systemId,
    XrGraphicsRequirementsVulkanKHR*            graphicsRequirements);
#पूर्ण_अगर /* XR_EXTENSION_PROTOTYPES */
#पूर्ण_अगर /* !XR_NO_PROTOTYPES */
#पूर्ण_अगर /* XR_USE_GRAPHICS_API_VULKAN */

#अगर_घोषित XR_USE_GRAPHICS_API_D3D11

// XR_KHR_D3D11_enable is a preprocessor guard. Do not pass it to API calls.
#घोषणा XR_KHR_D3D11_enable 1
#घोषणा XR_KHR_D3D11_enable_SPEC_VERSION  11
#घोषणा XR_KHR_D3D11_ENABLE_EXTENSION_NAME "XR_KHR_D3D11_enable"
// XrGraphicsBindingD3D11KHR extends XrSessionCreateInfo
प्रकार काष्ठा XrGraphicsBindingD3D11KHR {
    XrStructureType             type;
    स्थिर व्योम* XR_MAY_ALIAS    अग्र;
    ID3D11Device*               device;
} XrGraphicsBindingD3D11KHR;

प्रकार काष्ठा XrSwapchainImageD3D11KHR {
     XrStructureType      type;
    व्योम* XR_MAY_ALIAS    अग्र;
    ID3D11Texture2D*      texture;
} XrSwapchainImageD3D11KHR;

प्रकार काष्ठा XrGraphicsRequirementsD3D11KHR {
    XrStructureType       type;
    व्योम* XR_MAY_ALIAS    अग्र;
    LUID                  adapterLuid;
    D3D_FEATURE_LEVEL     minFeatureLevel;
} XrGraphicsRequirementsD3D11KHR;

प्रकार Xr_परिणाम (XRAPI_PTR *PFN_xrGetD3D11GraphicsRequirementsKHR)(XrInstance instance, XrSystemId systemId, XrGraphicsRequirementsD3D11KHR* graphicsRequirements);

#अगर_अघोषित XR_NO_PROTOTYPES
#अगर_घोषित XR_EXTENSION_PROTOTYPES
XRAPI_ATTR Xr_परिणाम XRAPI_CALL xrGetD3D11GraphicsRequirementsKHR(
    XrInstance                                  instance,
    XrSystemId                                  systemId,
    XrGraphicsRequirementsD3D11KHR*             graphicsRequirements);
#पूर्ण_अगर /* XR_EXTENSION_PROTOTYPES */
#पूर्ण_अगर /* !XR_NO_PROTOTYPES */
#पूर्ण_अगर /* XR_USE_GRAPHICS_API_D3D11 */

#अगर_घोषित XR_USE_GRAPHICS_API_D3D12

// XR_KHR_D3D12_enable is a preprocessor guard. Do not pass it to API calls.
#घोषणा XR_KHR_D3D12_enable 1
#घोषणा XR_KHR_D3D12_enable_SPEC_VERSION  11
#घोषणा XR_KHR_D3D12_ENABLE_EXTENSION_NAME "XR_KHR_D3D12_enable"
// XrGraphicsBindingD3D12KHR extends XrSessionCreateInfo
प्रकार काष्ठा XrGraphicsBindingD3D12KHR {
    XrStructureType             type;
    स्थिर व्योम* XR_MAY_ALIAS    अग्र;
    ID3D12Device*               device;
    ID3D12CommandQueue*         queue;
} XrGraphicsBindingD3D12KHR;

प्रकार काष्ठा XrSwapchainImageD3D12KHR {
     XrStructureType      type;
    व्योम* XR_MAY_ALIAS    अग्र;
    ID3D12Resource*       texture;
} XrSwapchainImageD3D12KHR;

प्रकार काष्ठा XrGraphicsRequirementsD3D12KHR {
    XrStructureType       type;
    व्योम* XR_MAY_ALIAS    अग्र;
    LUID                  adapterLuid;
    D3D_FEATURE_LEVEL     minFeatureLevel;
} XrGraphicsRequirementsD3D12KHR;

प्रकार Xr_परिणाम (XRAPI_PTR *PFN_xrGetD3D12GraphicsRequirementsKHR)(XrInstance instance, XrSystemId systemId, XrGraphicsRequirementsD3D12KHR* graphicsRequirements);

#अगर_अघोषित XR_NO_PROTOTYPES
#अगर_घोषित XR_EXTENSION_PROTOTYPES
XRAPI_ATTR Xr_परिणाम XRAPI_CALL xrGetD3D12GraphicsRequirementsKHR(
    XrInstance                                  instance,
    XrSystemId                                  systemId,
    XrGraphicsRequirementsD3D12KHR*             graphicsRequirements);
#पूर्ण_अगर /* XR_EXTENSION_PROTOTYPES */
#पूर्ण_अगर /* !XR_NO_PROTOTYPES */
#पूर्ण_अगर /* XR_USE_GRAPHICS_API_D3D12 */

#अगर_घोषित XR_USE_GRAPHICS_API_METAL

// XR_KHR_metal_enable is a preprocessor guard. Do not pass it to API calls.
#घोषणा XR_KHR_metal_enable 1
#घोषणा XR_KHR_metal_enable_SPEC_VERSION  3
#घोषणा XR_KHR_METAL_ENABLE_EXTENSION_NAME "XR_KHR_metal_enable"
// XrGraphicsBindingMetalKHR extends XrSessionCreateInfo
प्रकार काष्ठा XrGraphicsBindingMetalKHR {
    XrStructureType             type;
    स्थिर व्योम* XR_MAY_ALIAS    अग्र;
    व्योम* XR_MAY_ALIAS          commandQueue;
} XrGraphicsBindingMetalKHR;

प्रकार काष्ठा XrSwapchainImageMetalKHR {
    XrStructureType       type;
    व्योम* XR_MAY_ALIAS    अग्र;
    व्योम* XR_MAY_ALIAS    texture;
} XrSwapchainImageMetalKHR;

प्रकार काष्ठा XrGraphicsRequirementsMetalKHR {
    XrStructureType       type;
    व्योम* XR_MAY_ALIAS    अग्र;
    व्योम* XR_MAY_ALIAS    metalDevice;
} XrGraphicsRequirementsMetalKHR;

प्रकार Xr_परिणाम (XRAPI_PTR *PFN_xrGetMetalGraphicsRequirementsKHR)(XrInstance instance, XrSystemId systemId, XrGraphicsRequirementsMetalKHR* graphicsRequirements);

#अगर_अघोषित XR_NO_PROTOTYPES
#अगर_घोषित XR_EXTENSION_PROTOTYPES
XRAPI_ATTR Xr_परिणाम XRAPI_CALL xrGetMetalGraphicsRequirementsKHR(
    XrInstance                                  instance,
    XrSystemId                                  systemId,
    XrGraphicsRequirementsMetalKHR*             graphicsRequirements);
#पूर्ण_अगर /* XR_EXTENSION_PROTOTYPES */
#पूर्ण_अगर /* !XR_NO_PROTOTYPES */
#पूर्ण_अगर /* XR_USE_GRAPHICS_API_METAL */

#अगर_घोषित XR_USE_PLATFORM_WIN32

// XR_KHR_win32_convert_performance_counter_time is a preprocessor guard. Do not pass it to API calls.
#घोषणा XR_KHR_win32_convert_performance_गणक_time 1
#घोषणा XR_KHR_win32_convert_performance_गणक_time_SPEC_VERSION 1
#घोषणा XR_KHR_WIN32_CONVERT_PERFORMANCE_गणक_TIME_EXTENSION_NAME "XR_KHR_win32_convert_performance_counter_time"
प्रकार Xr_परिणाम (XRAPI_PTR *PFN_xr_Convert_Win32_Performance_गणक_To_Time_KHR)(XrInstance instance, स्थिर LARGE_INTEGER* performance_गणक, XrTime* समय);
प्रकार Xr_परिणाम (XRAPI_PTR *PFN_xr_Convert_Time_To_Win32_Performance_गणक_KHR)(XrInstance instance, XrTime समय, LARGE_INTEGER* performance_गणक);

#अगर_अघोषित XR_NO_PROTOTYPES
#अगर_घोषित XR_EXTENSION_PROTOTYPES
XRAPI_ATTR Xr_परिणाम XRAPI_CALL xr_Convert_Win32_Performance_गणक_To_Time_KHR(
    XrInstance                                  instance,
    स्थिर LARGE_INTEGER*                        performance_गणक,
    XrTime*                                     समय);

XRAPI_ATTR Xr_परिणाम XRAPI_CALL xr_Convert_Time_To_Win32_Performance_गणक_KHR(
    XrInstance                                  instance,
    XrTime                                      समय,
    LARGE_INTEGER*                              performance_गणक);
#पूर्ण_अगर /* XR_EXTENSION_PROTOTYPES */
#पूर्ण_अगर /* !XR_NO_PROTOTYPES */
#पूर्ण_अगर /* XR_USE_PLATFORM_WIN32 */

#अगर_घोषित XR_USE_TIMESPEC

// XR_KHR_convert_timespec_time is a preprocessor guard. Do not pass it to API calls.
#घोषणा XR_KHR_convert_timespec_time 1
#घोषणा XR_KHR_convert_timespec_time_SPEC_VERSION 1
#घोषणा XR_KHR_CONVERT_TIMESPEC_TIME_EXTENSION_NAME "XR_KHR_convert_timespec_time"
प्रकार Xr_परिणाम (XRAPI_PTR *PFN_xrConvertTimespecTimeToTimeKHR)(XrInstance instance, स्थिर काष्ठा timespec* timespecTime, XrTime* समय);
प्रकार Xr_परिणाम (XRAPI_PTR *PFN_xrConvertTimeToTimespecTimeKHR)(XrInstance instance, XrTime समय, काष्ठा timespec* timespecTime);

#अगर_अघोषित XR_NO_PROTOTYPES
#अगर_घोषित XR_EXTENSION_PROTOTYPES
XRAPI_ATTR Xr_परिणाम XRAPI_CALL xrConvertTimespecTimeToTimeKHR(
    XrInstance                                  instance,
    स्थिर काष्ठा timespec*                      timespecTime,
    XrTime*                                     समय);

XRAPI_ATTR Xr_परिणाम XRAPI_CALL xrConvertTimeToTimespecTimeKHR(
    XrInstance                                  instance,
    XrTime                                      समय,
    काष्ठा timespec*                            timespecTime);
#पूर्ण_अगर /* XR_EXTENSION_PROTOTYPES */
#पूर्ण_अगर /* !XR_NO_PROTOTYPES */
#पूर्ण_अगर /* XR_USE_TIMESPEC */

#अगर_घोषित XR_USE_PLATFORM_ANDROID

// XR_KHR_loader_init_android is a preprocessor guard. Do not pass it to API calls.
#घोषणा XR_KHR_loader_init_android 1
#घोषणा XR_KHR_loader_init_android_SPEC_VERSION 1
#घोषणा XR_KHR_LOADER_INIT_ANDROID_EXTENSION_NAME "XR_KHR_loader_init_android"
प्रकार काष्ठा XrLoaderInitInfoAndroidKHR {
    XrStructureType             type;
    स्थिर व्योम* XR_MAY_ALIAS    अग्र;
    व्योम* XR_MAY_ALIAS          applicationVM;
    व्योम* XR_MAY_ALIAS          applicationContext;
} XrLoaderInitInfoAndroidKHR;

#पूर्ण_अगर /* XR_USE_PLATFORM_ANDROID */

#अगर_घोषित XR_USE_GRAPHICS_API_VULKAN

// XR_KHR_vulkan_enable2 is a preprocessor guard. Do not pass it to API calls.
#घोषणा XR_KHR_vulkan_enable2 1
#घोषणा XR_KHR_vulkan_enable2_SPEC_VERSION 4
#घोषणा XR_KHR_VULKAN_ENABLE2_EXTENSION_NAME "XR_KHR_vulkan_enable2"
प्रकार XrFlags64 XrVulkanInstanceCreateFlagsKHR;

// Flag bits for XrVulkanInstanceCreateFlagsKHR

प्रकार XrFlags64 XrVulkanDeviceCreateFlagsKHR;

// Flag bits for XrVulkanDeviceCreateFlagsKHR

प्रकार काष्ठा XrVulkanInstanceCreateInfoKHR {
    XrStructureType                   type;
    स्थिर व्योम* XR_MAY_ALIAS          अग्र;
    XrSystemId                        systemId;
    XrVulkanInstanceCreateFlagsKHR    createFlags;
    PFN_vkGetInstanceProcAddr         pfnGetInstanceProcAddr;
    स्थिर VkInstanceCreateInfo*       vulkanCreateInfo;
    स्थिर VkAllocationCallbacks*      vulkanAllocator;
} XrVulkanInstanceCreateInfoKHR;

प्रकार काष्ठा XrVulkanDeviceCreateInfoKHR {
    XrStructureType                 type;
    स्थिर व्योम* XR_MAY_ALIAS        अग्र;
    XrSystemId                      systemId;
    XrVulkanDeviceCreateFlagsKHR    createFlags;
    PFN_vkGetInstanceProcAddr       pfnGetInstanceProcAddr;
    VkPhysicalDevice                vulkanPhysicalDevice;
    स्थिर VkDeviceCreateInfo*       vulkanCreateInfo;
    स्थिर VkAllocationCallbacks*    vulkanAllocator;
} XrVulkanDeviceCreateInfoKHR;

प्रकार XrGraphicsBindingVulkanKHR XrGraphicsBindingVulkan2KHR;

प्रकार काष्ठा XrVulkanGraphicsDeviceGetInfoKHR {
    XrStructureType             type;
    स्थिर व्योम* XR_MAY_ALIAS    अग्र;
    XrSystemId                  systemId;
    VkInstance                  vulkanInstance;
} XrVulkanGraphicsDeviceGetInfoKHR;

प्रकार XrSwapchainImageVulkanKHR XrSwapchainImageVulkan2KHR;

प्रकार XrGraphicsRequirementsVulkanKHR XrGraphicsRequirementsVulkan2KHR;

प्रकार Xr_परिणाम (XRAPI_PTR *PFN_xrCreateVulkanInstanceKHR)(XrInstance instance, स्थिर XrVulkanInstanceCreateInfoKHR* createInfo, VkInstance* vulkanInstance, Vk_परिणाम* vulkan_परिणाम);
प्रकार Xr_परिणाम (XRAPI_PTR *PFN_xrCreateVulkanDeviceKHR)(XrInstance instance, स्थिर XrVulkanDeviceCreateInfoKHR* createInfo, VkDevice* vulkanDevice, Vk_परिणाम* vulkan_परिणाम);
प्रकार Xr_परिणाम (XRAPI_PTR *PFN_xrGetVulkanGraphicsDevice2KHR)(XrInstance instance, स्थिर XrVulkanGraphicsDeviceGetInfoKHR* getInfo, VkPhysicalDevice* vulkanPhysicalDevice);
प्रकार Xr_परिणाम (XRAPI_PTR *PFN_xrGetVulkanGraphicsRequirements2KHR)(XrInstance instance, XrSystemId systemId, XrGraphicsRequirementsVulkanKHR* graphicsRequirements);

#अगर_अघोषित XR_NO_PROTOTYPES
#अगर_घोषित XR_EXTENSION_PROTOTYPES
XRAPI_ATTR Xr_परिणाम XRAPI_CALL xrCreateVulkanInstanceKHR(
    XrInstance                                  instance,
    स्थिर XrVulkanInstanceCreateInfoKHR*        createInfo,
    VkInstance*                                 vulkanInstance,
    Vk_परिणाम*                                   vulkan_परिणाम);

XRAPI_ATTR Xr_परिणाम XRAPI_CALL xrCreateVulkanDeviceKHR(
    XrInstance                                  instance,
    स्थिर XrVulkanDeviceCreateInfoKHR*          createInfo,
    VkDevice*                                   vulkanDevice,
    Vk_परिणाम*                                   vulkan_परिणाम);

XRAPI_ATTR Xr_परिणाम XRAPI_CALL xrGetVulkanGraphicsDevice2KHR(
    XrInstance                                  instance,
    स्थिर XrVulkanGraphicsDeviceGetInfoKHR*     getInfo,
    VkPhysicalDevice*                           vulkanPhysicalDevice);

XRAPI_ATTR Xr_परिणाम XRAPI_CALL xrGetVulkanGraphicsRequirements2KHR(
    XrInstance                                  instance,
    XrSystemId                                  systemId,
    XrGraphicsRequirementsVulkanKHR*            graphicsRequirements);
#पूर्ण_अगर /* XR_EXTENSION_PROTOTYPES */
#पूर्ण_अगर /* !XR_NO_PROTOTYPES */
#पूर्ण_अगर /* XR_USE_GRAPHICS_API_VULKAN */

#अगर_घोषित XR_USE_PLATFORM_EGL

// XR_MNDX_egl_enable is a preprocessor guard. Do not pass it to API calls.
#घोषणा XR_MNDX_egl_enable 1
#घोषणा XR_MNDX_egl_enable_SPEC_VERSION   2
#घोषणा XR_MNDX_EGL_ENABLE_EXTENSION_NAME "XR_MNDX_egl_enable"
प्रकार PFN_xrVoidFunction (*PFN_xrEglGetProcAddressMNDX)(स्थिर अक्षर *name);
// XrGraphicsBindingEGLMNDX extends XrSessionCreateInfo
प्रकार काष्ठा XrGraphicsBindingEGLMNDX {
    XrStructureType                type;
    स्थिर व्योम* XR_MAY_ALIAS       अग्र;
    PFN_xrEglGetProcAddressMNDX    getProcAddress;
    EGLDisplay                     display;
    EGLConfig                      config;
    EGLContext                     context;
} XrGraphicsBindingEGLMNDX;

#पूर्ण_अगर /* XR_USE_PLATFORM_EGL */

#अगर_घोषित XR_USE_PLATFORM_WIN32

// XR_MSFT_perception_anchor_interop is a preprocessor guard. Do not pass it to API calls.
#घोषणा XR_MSFT_perception_anchor_interop 1
#घोषणा XR_MSFT_perception_anchor_interop_SPEC_VERSION 1
#घोषणा XR_MSFT_PERCEPTION_ANCHOR_INTEROP_EXTENSION_NAME "XR_MSFT_perception_anchor_interop"
प्रकार Xr_परिणाम (XRAPI_PTR *PFN_xrCreateSpatialAnchorFromPerceptionAnchorMSFT)(XrSession session, IUnknown* perceptionAnchor, XrSpatialAnchorMSFT* anchor);
प्रकार Xr_परिणाम (XRAPI_PTR *PFN_xrTryGetPerceptionAnchorFromSpatialAnchorMSFT)(XrSession session, XrSpatialAnchorMSFT anchor, IUnknown** perceptionAnchor);

#अगर_अघोषित XR_NO_PROTOTYPES
#अगर_घोषित XR_EXTENSION_PROTOTYPES
XRAPI_ATTR Xr_परिणाम XRAPI_CALL xrCreateSpatialAnchorFromPerceptionAnchorMSFT(
    XrSession                                   session,
    IUnknown*                                   perceptionAnchor,
    XrSpatialAnchorMSFT*                        anchor);

XRAPI_ATTR Xr_परिणाम XRAPI_CALL xrTryGetPerceptionAnchorFromSpatialAnchorMSFT(
    XrSession                                   session,
    XrSpatialAnchorMSFT                         anchor,
    IUnknown**                                  perceptionAnchor);
#पूर्ण_अगर /* XR_EXTENSION_PROTOTYPES */
#पूर्ण_अगर /* !XR_NO_PROTOTYPES */
#पूर्ण_अगर /* XR_USE_PLATFORM_WIN32 */

#अगर_घोषित XR_USE_PLATFORM_WIN32

// XR_MSFT_holographic_window_attachment is a preprocessor guard. Do not pass it to API calls.
#घोषणा XR_MSFT_holographic_window_attachment 1
#घोषणा XR_MSFT_holographic_window_attachment_SPEC_VERSION 1
#घोषणा XR_MSFT_HOLOGRAPHIC_WINDOW_ATTACHMENT_EXTENSION_NAME "XR_MSFT_holographic_window_attachment"
#अगर_घोषित XR_USE_PLATFORM_WIN32
// XrHolographicWindowAttachmentMSFT extends XrSessionCreateInfo
प्रकार काष्ठा XrHolographicWindowAttachmentMSFT {
    XrStructureType             type;
    स्थिर व्योम* XR_MAY_ALIAS    अग्र;
    IUnknown*                   holographicSpace;
    IUnknown*                   coreWindow;
} XrHolographicWindowAttachmentMSFT;
#पूर्ण_अगर // XR_USE_PLATFORM_WIN32

#पूर्ण_अगर /* XR_USE_PLATFORM_WIN32 */

#अगर_घोषित XR_USE_PLATFORM_ANDROID

// XR_FB_android_surface_swapchain_create is a preprocessor guard. Do not pass it to API calls.
#घोषणा XR_FB_android_surface_swapchain_create 1
#घोषणा XR_FB_android_surface_swapchain_create_SPEC_VERSION 1
#घोषणा XR_FB_ANDROID_SURFACE_SWAPCHAIN_CREATE_EXTENSION_NAME "XR_FB_android_surface_swapchain_create"
प्रकार XrFlags64 XrAndroidSurfaceSwapchainFlagsFB;

// Flag bits for XrAndroidSurfaceSwapchainFlagsFB
अटल स्थिर XrAndroidSurfaceSwapchainFlagsFB XR_ANDROID_SURFACE_SWAPCHAIN_SYNCHRONOUS_BIT_FB = 0x00000001;
अटल स्थिर XrAndroidSurfaceSwapchainFlagsFB XR_ANDROID_SURFACE_SWAPCHAIN_USE_TIMESTAMPS_BIT_FB = 0x00000002;

#अगर_घोषित XR_USE_PLATFORM_ANDROID
// XrAndroidSurfaceSwapchainCreateInfoFB extends XrSwapchainCreateInfo
प्रकार काष्ठा XrAndroidSurfaceSwapchainCreateInfoFB {
    XrStructureType                     type;
    स्थिर व्योम* XR_MAY_ALIAS            अग्र;
    XrAndroidSurfaceSwapchainFlagsFB    createFlags;
} XrAndroidSurfaceSwapchainCreateInfoFB;
#पूर्ण_अगर // XR_USE_PLATFORM_ANDROID

#पूर्ण_अगर /* XR_USE_PLATFORM_ANDROID */

#अगर_घोषित XR_USE_PLATFORM_ML

// XR_ML_compat is a preprocessor guard. Do not pass it to API calls.
#घोषणा XR_ML_compat 1
#घोषणा XR_ML_compat_SPEC_VERSION         1
#घोषणा XR_ML_COMPAT_EXTENSION_NAME       "XR_ML_compat"
प्रकार काष्ठा XrCoordinateSpaceCreateInfoML {
    XrStructureType             type;
    स्थिर व्योम* XR_MAY_ALIAS    अग्र;
    MLCoordinateFrameUID        cfuid;
    XrPosef                     poseInCoordinateSpace;
} XrCoordinateSpaceCreateInfoML;

प्रकार Xr_परिणाम (XRAPI_PTR *PFN_xrCreateSpaceFromCoordinateFrameUIDML)(XrSession session, स्थिर XrCoordinateSpaceCreateInfoML *createInfo, XrSpace* space);

#अगर_अघोषित XR_NO_PROTOTYPES
#अगर_घोषित XR_EXTENSION_PROTOTYPES
XRAPI_ATTR Xr_परिणाम XRAPI_CALL xrCreateSpaceFromCoordinateFrameUIDML(
    XrSession                                   session,
    स्थिर XrCoordinateSpaceCreateInfoML *       createInfo,
    XrSpace*                                    space);
#पूर्ण_अगर /* XR_EXTENSION_PROTOTYPES */
#पूर्ण_अगर /* !XR_NO_PROTOTYPES */
#पूर्ण_अगर /* XR_USE_PLATFORM_ML */

#अगर_घोषित XR_USE_PLATFORM_WIN32

// XR_OCULUS_audio_device_guid is a preprocessor guard. Do not pass it to API calls.
#घोषणा XR_OCULUS_audio_device_guid 1
#घोषणा XR_OCULUS_audio_device_guid_SPEC_VERSION 1
#घोषणा XR_OCULUS_AUDIO_DEVICE_GUID_EXTENSION_NAME "XR_OCULUS_audio_device_guid"
#घोषणा XR_MAX_AUDIO_DEVICE_STR_आकार_OCULUS 128
प्रकार Xr_परिणाम (XRAPI_PTR *PFN_xrGetAudioOutputDeviceGuidOculus)(XrInstance instance, ब_अक्षर_प्रकार बफर_2[XR_MAX_AUDIO_DEVICE_STR_आकार_OCULUS]);
प्रकार Xr_परिणाम (XRAPI_PTR *PFN_xr_Get_Audio_निवेश_Device_Guid_Oculus)(XrInstance instance, ब_अक्षर_प्रकार बफर_2[XR_MAX_AUDIO_DEVICE_STR_आकार_OCULUS]);

#अगर_अघोषित XR_NO_PROTOTYPES
#अगर_घोषित XR_EXTENSION_PROTOTYPES
XRAPI_ATTR Xr_परिणाम XRAPI_CALL xrGetAudioOutputDeviceGuidOculus(
    XrInstance                                  instance,
    ब_अक्षर_प्रकार                                     बफर_2[XR_MAX_AUDIO_DEVICE_STR_आकार_OCULUS]);

XRAPI_ATTR Xr_परिणाम XRAPI_CALL xr_Get_Audio_निवेश_Device_Guid_Oculus(
    XrInstance                                  instance,
    ब_अक्षर_प्रकार                                     बफर_2[XR_MAX_AUDIO_DEVICE_STR_आकार_OCULUS]);
#पूर्ण_अगर /* XR_EXTENSION_PROTOTYPES */
#पूर्ण_अगर /* !XR_NO_PROTOTYPES */
#पूर्ण_अगर /* XR_USE_PLATFORM_WIN32 */

#अगर_घोषित XR_USE_GRAPHICS_API_VULKAN

// XR_FB_foveation_vulkan is a preprocessor guard. Do not pass it to API calls.
#घोषणा XR_FB_foveation_vulkan 1
#घोषणा XR_FB_foveation_vulkan_SPEC_VERSION 1
#घोषणा XR_FB_FOVEATION_VULKAN_EXTENSION_NAME "XR_FB_foveation_vulkan"
// XrSwapchainImageFoveationVulkanFB extends XrSwapchainImageVulkanKHR
प्रकार काष्ठा XrSwapchainImageFoveationVulkanFB {
    XrStructureType       type;
    व्योम* XR_MAY_ALIAS    अग्र;
    VkImage               image;
    uint32_t              width;
    uint32_t              height;
} XrSwapchainImageFoveationVulkanFB;

#पूर्ण_अगर /* XR_USE_GRAPHICS_API_VULKAN */

#अगर_घोषित XR_USE_PLATFORM_ANDROID

// XR_FB_swapchain_update_state_android_surface is a preprocessor guard. Do not pass it to API calls.
#घोषणा XR_FB_swapchain_update_state_android_surface 1
#घोषणा XR_FB_swapchain_update_state_android_surface_SPEC_VERSION 1
#घोषणा XR_FB_SWAPCHAIN_UPDATE_STATE_ANDROID_SURFACE_EXTENSION_NAME "XR_FB_swapchain_update_state_android_surface"
#अगर_घोषित XR_USE_PLATFORM_ANDROID
प्रकार काष्ठा XrSwapchainStateAndroidSurfaceDimensionsFB {
    XrStructureType       type;
    व्योम* XR_MAY_ALIAS    अग्र;
    uint32_t              width;
    uint32_t              height;
} XrSwapchainStateAndroidSurfaceDimensionsFB;
#पूर्ण_अगर // XR_USE_PLATFORM_ANDROID

#पूर्ण_अगर /* XR_USE_PLATFORM_ANDROID */

#अगर_घोषित XR_USE_GRAPHICS_API_OPENGL_ES

// XR_FB_swapchain_update_state_opengl_es is a preprocessor guard. Do not pass it to API calls.
#घोषणा XR_FB_swapchain_update_state_opengl_es 1
#घोषणा XR_FB_swapchain_update_state_opengl_es_SPEC_VERSION 1
#घोषणा XR_FB_SWAPCHAIN_UPDATE_STATE_OPENGL_ES_EXTENSION_NAME "XR_FB_swapchain_update_state_opengl_es"
#अगर_घोषित XR_USE_GRAPHICS_API_OPENGL_ES
प्रकार काष्ठा XrSwapchainStateSamplerOpenGLESFB {
    XrStructureType       type;
    व्योम* XR_MAY_ALIAS    अग्र;
    EGLenum               minFilter;
    EGLenum               magFilter;
    EGLenum               wrapModeS;
    EGLenum               wrapModeT;
    EGLenum               swizzleRed;
    EGLenum               swizzleGreen;
    EGLenum               swizzleBlue;
    EGLenum               swizzleAlpha;
    भग्न                 maxAnisotropy;
    XrColor4f             borderColor;
} XrSwapchainStateSamplerOpenGLESFB;
#पूर्ण_अगर // XR_USE_GRAPHICS_API_OPENGL_ES

#पूर्ण_अगर /* XR_USE_GRAPHICS_API_OPENGL_ES */

#अगर_घोषित XR_USE_GRAPHICS_API_VULKAN

// XR_FB_swapchain_update_state_vulkan is a preprocessor guard. Do not pass it to API calls.
#घोषणा XR_FB_swapchain_update_state_vulkan 1
#घोषणा XR_FB_swapchain_update_state_vulkan_SPEC_VERSION 1
#घोषणा XR_FB_SWAPCHAIN_UPDATE_STATE_VULKAN_EXTENSION_NAME "XR_FB_swapchain_update_state_vulkan"
#अगर_घोषित XR_USE_GRAPHICS_API_VULKAN
प्रकार काष्ठा XrSwapchainStateSamplerVulkanFB {
    XrStructureType         type;
    व्योम* XR_MAY_ALIAS      अग्र;
    VkFilter                minFilter;
    VkFilter                magFilter;
    VkSamplerMipmapMode     mipmapMode;
    VkSamplerAddressMode    wrapModeS;
    VkSamplerAddressMode    wrapModeT;
    VkComponentSwizzle      swizzleRed;
    VkComponentSwizzle      swizzleGreen;
    VkComponentSwizzle      swizzleBlue;
    VkComponentSwizzle      swizzleAlpha;
    भग्न                   maxAnisotropy;
    XrColor4f               borderColor;
} XrSwapchainStateSamplerVulkanFB;
#पूर्ण_अगर // XR_USE_GRAPHICS_API_VULKAN

#पूर्ण_अगर /* XR_USE_GRAPHICS_API_VULKAN */

#अगर_घोषित XR_USE_GRAPHICS_API_VULKAN

// XR_META_vulkan_swapchain_create_info is a preprocessor guard. Do not pass it to API calls.
#घोषणा XR_META_vulkan_swapchain_create_info 1
#घोषणा XR_META_vulkan_swapchain_create_info_SPEC_VERSION 1
#घोषणा XR_META_VULKAN_SWAPCHAIN_CREATE_INFO_EXTENSION_NAME "XR_META_vulkan_swapchain_create_info"
// XrVulkanSwapchainCreateInfoMETA extends XrSwapchainCreateInfo
प्रकार काष्ठा XrVulkanSwapchainCreateInfoMETA {
    XrStructureType             type;
    स्थिर व्योम* XR_MAY_ALIAS    अग्र;
    VkImageCreateFlags          additionalCreateFlags;
    VkImageUsageFlags           additionalUsageFlags;
} XrVulkanSwapchainCreateInfoMETA;

#पूर्ण_अगर /* XR_USE_GRAPHICS_API_VULKAN */

#अगर_घोषित XR_USE_PLATFORM_ANDROID

// XR_ANDROID_anchor_sharing_export is a preprocessor guard. Do not pass it to API calls.
#घोषणा XR_ANDROID_anchor_sharing_export 1
#घोषणा XR_ANDROID_anchor_sharing_export_SPEC_VERSION 1
#घोषणा XR_ANDROID_ANCHOR_SHARING_EXPORT_EXTENSION_NAME "XR_ANDROID_anchor_sharing_export"
प्रकार काष्ठा XrAnchorSharingInfoANDROID {
    XrStructureType             type;
    स्थिर व्योम* XR_MAY_ALIAS    अग्र;
    XrSpace                     anchor;
} XrAnchorSharingInfoANDROID;

प्रकार काष्ठा XrAnchorSharingTokenANDROID {
    XrStructureType       type;
    व्योम* XR_MAY_ALIAS    अग्र;
    काष्ठा AIBinder*      token;
} XrAnchorSharingTokenANDROID;

// XrSystemAnchorSharingExportPropertiesANDROID extends XrSystemProperties
प्रकार काष्ठा XrSystemAnchorSharingExportPropertiesANDROID {
    XrStructureType       type;
    व्योम* XR_MAY_ALIAS    अग्र;
    XrBool32              supportsAnchorSharingExport;
} XrSystemAnchorSharingExportPropertiesANDROID;

प्रकार Xr_परिणाम (XRAPI_PTR *PFN_xrShareAnchorANDROID)(XrSession session, स्थिर XrAnchorSharingInfoANDROID* sharingInfo, XrAnchorSharingTokenANDROID* anchorToken);
प्रकार Xr_परिणाम (XRAPI_PTR *PFN_xrUnshareAnchorANDROID)(XrSession session, XrSpace anchor);

#अगर_अघोषित XR_NO_PROTOTYPES
#अगर_घोषित XR_EXTENSION_PROTOTYPES
XRAPI_ATTR Xr_परिणाम XRAPI_CALL xrShareAnchorANDROID(
    XrSession                                   session,
    स्थिर XrAnchorSharingInfoANDROID*           sharingInfo,
    XrAnchorSharingTokenANDROID*                anchorToken);

XRAPI_ATTR Xr_परिणाम XRAPI_CALL xrUnshareAnchorANDROID(
    XrSession                                   session,
    XrSpace                                     anchor);
#पूर्ण_अगर /* XR_EXTENSION_PROTOTYPES */
#पूर्ण_अगर /* !XR_NO_PROTOTYPES */
#पूर्ण_अगर /* XR_USE_PLATFORM_ANDROID */

#अगर_घोषित __cplusplus
}
#पूर्ण_अगर

#पूर्ण_अगर
