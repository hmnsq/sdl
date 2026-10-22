#నిర్వచితం_కాకపోతే OPENXR_PLATFORM_H_
#నిర్వచించు OPENXR_PLATFORM_H_ 1

/*
** Copyright 2017-2026 The Khronos Group Inc.
**
** SPDX-License-Identifier: Apache-2.0 OR MIT
*/

/*
** This header is generated from the Khronos OpenXR XML API Registry.
**
*/

#అన్తర్భావ "openxr.h"

#నిర్వచితమైతే __cplusplus
బాహ్య "C" {
#అయితే_ముగింపు


#నిర్వచితమైతే XR_USE_PLATFORM_ANDROID

// XR_KHR_android_thread_settings is a preprocessor guard. Do not pass it to API calls.
#నిర్వచించు XR_KHR_android_thread_settings 1
#నిర్వచించు XR_KHR_android_thread_settings_SPEC_సంస్కరణ 6
#నిర్వచించు XR_KHR_ANDROID_THREAD_SETTINGS_EXTENSION_NAME "XR_KHR_android_thread_settings"

రకనిర్వచనం గణన XrAndroidThreadTypeKHR {
    XR_ANDROID_THREAD_TYPE_APPLICATION_MAIN_KHR = 1,
    XR_ANDROID_THREAD_TYPE_APPLICATION_కార్మికుడు_KHR = 2,
    XR_ANDROID_THREAD_TYPE_RENDERER_MAIN_KHR = 3,
    XR_ANDROID_THREAD_TYPE_RENDERER_కార్మికుడు_KHR = 4,
    XR_ANDROID_THREAD_TYPE_MAX_ENUM_KHR = 0x7FFFFFFF
} XrAndroidThreadTypeKHR;
రకనిర్వచనం Xr_ఫలితం (XRAPI_PTR *PFN_xr_సమితి_Android_Application_Thread_KHR)(XrSession session, XrAndroidThreadTypeKHR threadType, uint32_t threadId);

#నిర్వచితం_కాకపోతే XR_NO_PROTOTYPES
#నిర్వచితమైతే XR_EXTENSION_PROTOTYPES
XRAPI_ATTR Xr_ఫలితం XRAPI_CALL xr_సమితి_Android_Application_Thread_KHR(
    XrSession                                   session,
    XrAndroidThreadTypeKHR                      threadType,
    uint32_t                                    threadId);
#అయితే_ముగింపు /* XR_EXTENSION_PROTOTYPES */
#అయితే_ముగింపు /* !XR_NO_PROTOTYPES */
#అయితే_ముగింపు /* XR_USE_PLATFORM_ANDROID */

#నిర్వచితమైతే XR_USE_PLATFORM_ANDROID

// XR_KHR_android_surface_swapchain is a preprocessor guard. Do not pass it to API calls.
#నిర్వచించు XR_KHR_android_surface_swapchain 1
#నిర్వచించు XR_KHR_android_surface_swapchain_SPEC_సంస్కరణ 4
#నిర్వచించు XR_KHR_ANDROID_SURFACE_SWAPCHAIN_EXTENSION_NAME "XR_KHR_android_surface_swapchain"
రకనిర్వచనం Xr_ఫలితం (XRAPI_PTR *PFN_xrCreateSwapchainAndroidSurfaceKHR)(XrSession session, స్థిరరాశి XrSwapchainCreateInfo* info, XrSwapchain* swapchain, jobject* surface);

#నిర్వచితం_కాకపోతే XR_NO_PROTOTYPES
#నిర్వచితమైతే XR_EXTENSION_PROTOTYPES
XRAPI_ATTR Xr_ఫలితం XRAPI_CALL xrCreateSwapchainAndroidSurfaceKHR(
    XrSession                                   session,
    స్థిరరాశి XrSwapchainCreateInfo*                info,
    XrSwapchain*                                swapchain,
    jobject*                                    surface);
#అయితే_ముగింపు /* XR_EXTENSION_PROTOTYPES */
#అయితే_ముగింపు /* !XR_NO_PROTOTYPES */
#అయితే_ముగింపు /* XR_USE_PLATFORM_ANDROID */

#నిర్వచితమైతే XR_USE_PLATFORM_ANDROID

// XR_KHR_android_create_instance is a preprocessor guard. Do not pass it to API calls.
#నిర్వచించు XR_KHR_android_create_instance 1
#నిర్వచించు XR_KHR_android_create_instance_SPEC_సంస్కరణ 3
#నిర్వచించు XR_KHR_ANDROID_CREATE_INSTANCE_EXTENSION_NAME "XR_KHR_android_create_instance"
// XrInstanceCreateInfoAndroidKHR extends XrInstanceCreateInfo
రకనిర్వచనం నిర్మాణం XrInstanceCreateInfoAndroidKHR {
    XrStructureType             type;
    స్థిరరాశి శూన్య* XR_MAY_ALIAS    తదుపరి;
    శూన్య* XR_MAY_ALIAS          applicationVM;
    శూన్య* XR_MAY_ALIAS          applicationActivity;
} XrInstanceCreateInfoAndroidKHR;

#అయితే_ముగింపు /* XR_USE_PLATFORM_ANDROID */

#నిర్వచితమైతే XR_USE_GRAPHICS_API_VULKAN

// XR_KHR_vulkan_swapchain_format_list is a preprocessor guard. Do not pass it to API calls.
#నిర్వచించు XR_KHR_vulkan_swapchain_format_list 1
#నిర్వచించు XR_KHR_vulkan_swapchain_format_list_SPEC_సంస్కరణ 5
#నిర్వచించు XR_KHR_VULKAN_SWAPCHAIN_FORMAT_LIST_EXTENSION_NAME "XR_KHR_vulkan_swapchain_format_list"
// XrVulkanSwapchainFormatListCreateInfoKHR extends XrSwapchainCreateInfo
రకనిర్వచనం నిర్మాణం XrVulkanSwapchainFormatListCreateInfoKHR {
    XrStructureType             type;
    స్థిరరాశి శూన్య* XR_MAY_ALIAS    తదుపరి;
    uint32_t                    view_Format_లెక్క;
    స్థిరరాశి VkFormat*             viewFormats;
} XrVulkanSwapchainFormatListCreateInfoKHR;

#అయితే_ముగింపు /* XR_USE_GRAPHICS_API_VULKAN */

#నిర్వచితమైతే XR_USE_GRAPHICS_API_OPENGL

// XR_KHR_opengl_enable is a preprocessor guard. Do not pass it to API calls.
#నిర్వచించు XR_KHR_opengl_enable 1
#నిర్వచించు XR_KHR_opengl_enable_SPEC_సంస్కరణ 12
#నిర్వచించు XR_KHR_OPENGL_ENABLE_EXTENSION_NAME "XR_KHR_opengl_enable"
#నిర్వచితమైతే XR_USE_PLATFORM_WIN32
// XrGraphicsBindingOpenGLWin32KHR extends XrSessionCreateInfo
రకనిర్వచనం నిర్మాణం XrGraphicsBindingOpenGLWin32KHR {
    XrStructureType             type;
    స్థిరరాశి శూన్య* XR_MAY_ALIAS    తదుపరి;
    HDC                         hDC;
    HGLRC                       hGLRC;
} XrGraphicsBindingOpenGLWin32KHR;
#అయితే_ముగింపు // XR_USE_PLATFORM_WIN32

#నిర్వచితమైతే XR_USE_PLATFORM_XLIB
// XrGraphicsBindingOpenGLXlibKHR extends XrSessionCreateInfo
రకనిర్వచనం నిర్మాణం XrGraphicsBindingOpenGLXlibKHR {
    XrStructureType             type;
    స్థిరరాశి శూన్య* XR_MAY_ALIAS    తదుపరి;
    Display*                    xDisplay;
    uint32_t                    visualid;
    GLXFBConfig                 glxFBConfig;
    GLXDrawable                 glxDrawable;
    GLXContext                  glxContext;
} XrGraphicsBindingOpenGLXlibKHR;
#అయితే_ముగింపు // XR_USE_PLATFORM_XLIB

#నిర్వచితమైతే XR_USE_PLATFORM_XCB
// XrGraphicsBindingOpenGLXcbKHR extends XrSessionCreateInfo
రకనిర్వచనం నిర్మాణం XrGraphicsBindingOpenGLXcbKHR {
    XrStructureType             type;
    స్థిరరాశి శూన్య* XR_MAY_ALIAS    తదుపరి;
    xcb_connection_t*           connection;
    uint32_t                    screen_సంఖ్య;
    xcb_glx_fbconfig_t          fbconfigid;
    xcb_visualid_t              visualid;
    xcb_glx_drawable_t          glxDrawable;
    xcb_glx_context_t           glxContext;
} XrGraphicsBindingOpenGLXcbKHR;
#అయితే_ముగింపు // XR_USE_PLATFORM_XCB

#నిర్వచితమైతే XR_USE_PLATFORM_WAYLAND
// XrGraphicsBindingOpenGLWaylandKHR extends XrSessionCreateInfo
రకనిర్వచనం నిర్మాణం XrGraphicsBindingOpenGLWaylandKHR {
    XrStructureType             type;
    స్థిరరాశి శూన్య* XR_MAY_ALIAS    తదుపరి;
    నిర్మాణం wl_display*          display;
} XrGraphicsBindingOpenGLWaylandKHR;
#అయితే_ముగింపు // XR_USE_PLATFORM_WAYLAND

రకనిర్వచనం నిర్మాణం XrSwapchainImageOpenGLKHR {
    XrStructureType       type;
    శూన్య* XR_MAY_ALIAS    తదుపరి;
    uint32_t              image;
} XrSwapchainImageOpenGLKHR;

రకనిర్వచనం నిర్మాణం XrGraphicsRequirementsOpenGLKHR {
    XrStructureType       type;
    శూన్య* XR_MAY_ALIAS    తదుపరి;
    Xr_సంస్కరణ             min_Api_సంస్కరణ_Supported;
    Xr_సంస్కరణ             max_Api_సంస్కరణ_Supported;
} XrGraphicsRequirementsOpenGLKHR;

రకనిర్వచనం Xr_ఫలితం (XRAPI_PTR *PFN_xrGetOpenGLGraphicsRequirementsKHR)(XrInstance instance, XrSystemId systemId, XrGraphicsRequirementsOpenGLKHR* graphicsRequirements);

#నిర్వచితం_కాకపోతే XR_NO_PROTOTYPES
#నిర్వచితమైతే XR_EXTENSION_PROTOTYPES
XRAPI_ATTR Xr_ఫలితం XRAPI_CALL xrGetOpenGLGraphicsRequirementsKHR(
    XrInstance                                  instance,
    XrSystemId                                  systemId,
    XrGraphicsRequirementsOpenGLKHR*            graphicsRequirements);
#అయితే_ముగింపు /* XR_EXTENSION_PROTOTYPES */
#అయితే_ముగింపు /* !XR_NO_PROTOTYPES */
#అయితే_ముగింపు /* XR_USE_GRAPHICS_API_OPENGL */

#నిర్వచితమైతే XR_USE_GRAPHICS_API_OPENGL_ES

// XR_KHR_opengl_es_enable is a preprocessor guard. Do not pass it to API calls.
#నిర్వచించు XR_KHR_opengl_es_enable 1
#నిర్వచించు XR_KHR_opengl_es_enable_SPEC_సంస్కరణ 10
#నిర్వచించు XR_KHR_OPENGL_ES_ENABLE_EXTENSION_NAME "XR_KHR_opengl_es_enable"
#నిర్వచితమైతే XR_USE_PLATFORM_ANDROID
// XrGraphicsBindingOpenGLESAndroidKHR extends XrSessionCreateInfo
రకనిర్వచనం నిర్మాణం XrGraphicsBindingOpenGLESAndroidKHR {
    XrStructureType             type;
    స్థిరరాశి శూన్య* XR_MAY_ALIAS    తదుపరి;
    EGLDisplay                  display;
    EGLConfig                   config;
    EGLContext                  context;
} XrGraphicsBindingOpenGLESAndroidKHR;
#అయితే_ముగింపు // XR_USE_PLATFORM_ANDROID

రకనిర్వచనం నిర్మాణం XrSwapchainImageOpenGLESKHR {
    XrStructureType       type;
    శూన్య* XR_MAY_ALIAS    తదుపరి;
    uint32_t              image;
} XrSwapchainImageOpenGLESKHR;

రకనిర్వచనం నిర్మాణం XrGraphicsRequirementsOpenGLESKHR {
    XrStructureType       type;
    శూన్య* XR_MAY_ALIAS    తదుపరి;
    Xr_సంస్కరణ             min_Api_సంస్కరణ_Supported;
    Xr_సంస్కరణ             max_Api_సంస్కరణ_Supported;
} XrGraphicsRequirementsOpenGLESKHR;

రకనిర్వచనం Xr_ఫలితం (XRAPI_PTR *PFN_xrGetOpenGLESGraphicsRequirementsKHR)(XrInstance instance, XrSystemId systemId, XrGraphicsRequirementsOpenGLESKHR* graphicsRequirements);

#నిర్వచితం_కాకపోతే XR_NO_PROTOTYPES
#నిర్వచితమైతే XR_EXTENSION_PROTOTYPES
XRAPI_ATTR Xr_ఫలితం XRAPI_CALL xrGetOpenGLESGraphicsRequirementsKHR(
    XrInstance                                  instance,
    XrSystemId                                  systemId,
    XrGraphicsRequirementsOpenGLESKHR*          graphicsRequirements);
#అయితే_ముగింపు /* XR_EXTENSION_PROTOTYPES */
#అయితే_ముగింపు /* !XR_NO_PROTOTYPES */
#అయితే_ముగింపు /* XR_USE_GRAPHICS_API_OPENGL_ES */

#నిర్వచితమైతే XR_USE_GRAPHICS_API_VULKAN

// XR_KHR_vulkan_enable is a preprocessor guard. Do not pass it to API calls.
#నిర్వచించు XR_KHR_vulkan_enable 1
#నిర్వచించు XR_KHR_vulkan_enable_SPEC_సంస్కరణ 10
#నిర్వచించు XR_KHR_VULKAN_ENABLE_EXTENSION_NAME "XR_KHR_vulkan_enable"
// XrGraphicsBindingVulkanKHR extends XrSessionCreateInfo
రకనిర్వచనం నిర్మాణం XrGraphicsBindingVulkanKHR {
    XrStructureType             type;
    స్థిరరాశి శూన్య* XR_MAY_ALIAS    తదుపరి;
    VkInstance                  instance;
    VkPhysicalDevice            physicalDevice;
    VkDevice                    device;
    uint32_t                    వరుస_Family_సూచీ;
    uint32_t                    వరుస_సూచీ;
} XrGraphicsBindingVulkanKHR;

రకనిర్వచనం నిర్మాణం XrSwapchainImageVulkanKHR {
    XrStructureType       type;
    శూన్య* XR_MAY_ALIAS    తదుపరి;
    VkImage               image;
} XrSwapchainImageVulkanKHR;

రకనిర్వచనం నిర్మాణం XrGraphicsRequirementsVulkanKHR {
    XrStructureType       type;
    శూన్య* XR_MAY_ALIAS    తదుపరి;
    Xr_సంస్కరణ             min_Api_సంస్కరణ_Supported;
    Xr_సంస్కరణ             max_Api_సంస్కరణ_Supported;
} XrGraphicsRequirementsVulkanKHR;

రకనిర్వచనం Xr_ఫలితం (XRAPI_PTR *PFN_xrGetVulkanInstanceExtensionsKHR)(XrInstance instance, XrSystemId systemId, uint32_t బఫరు_సామర్థ్యం_ఆదానం, uint32_t* బఫరు_లెక్క_Output, అక్షరం* బఫరు_2);
రకనిర్వచనం Xr_ఫలితం (XRAPI_PTR *PFN_xrGetVulkanDeviceExtensionsKHR)(XrInstance instance, XrSystemId systemId, uint32_t బఫరు_సామర్థ్యం_ఆదానం, uint32_t* బఫరు_లెక్క_Output, అక్షరం* బఫరు_2);
రకనిర్వచనం Xr_ఫలితం (XRAPI_PTR *PFN_xrGetVulkanGraphicsDeviceKHR)(XrInstance instance, XrSystemId systemId, VkInstance vkInstance, VkPhysicalDevice* vkPhysicalDevice);
రకనిర్వచనం Xr_ఫలితం (XRAPI_PTR *PFN_xrGetVulkanGraphicsRequirementsKHR)(XrInstance instance, XrSystemId systemId, XrGraphicsRequirementsVulkanKHR* graphicsRequirements);

#నిర్వచితం_కాకపోతే XR_NO_PROTOTYPES
#నిర్వచితమైతే XR_EXTENSION_PROTOTYPES
XRAPI_ATTR Xr_ఫలితం XRAPI_CALL xrGetVulkanInstanceExtensionsKHR(
    XrInstance                                  instance,
    XrSystemId                                  systemId,
    uint32_t                                    బఫరు_సామర్థ్యం_ఆదానం,
    uint32_t*                                   బఫరు_లెక్క_Output,
    అక్షరం*                                       బఫరు_2);

XRAPI_ATTR Xr_ఫలితం XRAPI_CALL xrGetVulkanDeviceExtensionsKHR(
    XrInstance                                  instance,
    XrSystemId                                  systemId,
    uint32_t                                    బఫరు_సామర్థ్యం_ఆదానం,
    uint32_t*                                   బఫరు_లెక్క_Output,
    అక్షరం*                                       బఫరు_2);

XRAPI_ATTR Xr_ఫలితం XRAPI_CALL xrGetVulkanGraphicsDeviceKHR(
    XrInstance                                  instance,
    XrSystemId                                  systemId,
    VkInstance                                  vkInstance,
    VkPhysicalDevice*                           vkPhysicalDevice);

XRAPI_ATTR Xr_ఫలితం XRAPI_CALL xrGetVulkanGraphicsRequirementsKHR(
    XrInstance                                  instance,
    XrSystemId                                  systemId,
    XrGraphicsRequirementsVulkanKHR*            graphicsRequirements);
#అయితే_ముగింపు /* XR_EXTENSION_PROTOTYPES */
#అయితే_ముగింపు /* !XR_NO_PROTOTYPES */
#అయితే_ముగింపు /* XR_USE_GRAPHICS_API_VULKAN */

#నిర్వచితమైతే XR_USE_GRAPHICS_API_D3D11

// XR_KHR_D3D11_enable is a preprocessor guard. Do not pass it to API calls.
#నిర్వచించు XR_KHR_D3D11_enable 1
#నిర్వచించు XR_KHR_D3_D11_enable_SPEC_సంస్కరణ  11
#నిర్వచించు XR_KHR_D3D11_ENABLE_EXTENSION_NAME "XR_KHR_D3D11_enable"
// XrGraphicsBindingD3D11KHR extends XrSessionCreateInfo
రకనిర్వచనం నిర్మాణం XrGraphicsBindingD3D11KHR {
    XrStructureType             type;
    స్థిరరాశి శూన్య* XR_MAY_ALIAS    తదుపరి;
    ID3D11Device*               device;
} XrGraphicsBindingD3D11KHR;

రకనిర్వచనం నిర్మాణం XrSwapchainImageD3D11KHR {
     XrStructureType      type;
    శూన్య* XR_MAY_ALIAS    తదుపరి;
    ID3D11Texture2D*      texture;
} XrSwapchainImageD3D11KHR;

రకనిర్వచనం నిర్మాణం XrGraphicsRequirementsD3D11KHR {
    XrStructureType       type;
    శూన్య* XR_MAY_ALIAS    తదుపరి;
    LUID                  adapterLuid;
    D3D_FEATURE_LEVEL     minFeatureLevel;
} XrGraphicsRequirementsD3D11KHR;

రకనిర్వచనం Xr_ఫలితం (XRAPI_PTR *PFN_xrGetD3D11GraphicsRequirementsKHR)(XrInstance instance, XrSystemId systemId, XrGraphicsRequirementsD3D11KHR* graphicsRequirements);

#నిర్వచితం_కాకపోతే XR_NO_PROTOTYPES
#నిర్వచితమైతే XR_EXTENSION_PROTOTYPES
XRAPI_ATTR Xr_ఫలితం XRAPI_CALL xrGetD3D11GraphicsRequirementsKHR(
    XrInstance                                  instance,
    XrSystemId                                  systemId,
    XrGraphicsRequirementsD3D11KHR*             graphicsRequirements);
#అయితే_ముగింపు /* XR_EXTENSION_PROTOTYPES */
#అయితే_ముగింపు /* !XR_NO_PROTOTYPES */
#అయితే_ముగింపు /* XR_USE_GRAPHICS_API_D3D11 */

#నిర్వచితమైతే XR_USE_GRAPHICS_API_D3D12

// XR_KHR_D3D12_enable is a preprocessor guard. Do not pass it to API calls.
#నిర్వచించు XR_KHR_D3D12_enable 1
#నిర్వచించు XR_KHR_D3_D12_enable_SPEC_సంస్కరణ  11
#నిర్వచించు XR_KHR_D3D12_ENABLE_EXTENSION_NAME "XR_KHR_D3D12_enable"
// XrGraphicsBindingD3D12KHR extends XrSessionCreateInfo
రకనిర్వచనం నిర్మాణం XrGraphicsBindingD3D12KHR {
    XrStructureType             type;
    స్థిరరాశి శూన్య* XR_MAY_ALIAS    తదుపరి;
    ID3D12Device*               device;
    ID3_D12_Command_వరుస*         వరుస;
} XrGraphicsBindingD3D12KHR;

రకనిర్వచనం నిర్మాణం XrSwapchainImageD3D12KHR {
     XrStructureType      type;
    శూన్య* XR_MAY_ALIAS    తదుపరి;
    ID3D12Resource*       texture;
} XrSwapchainImageD3D12KHR;

రకనిర్వచనం నిర్మాణం XrGraphicsRequirementsD3D12KHR {
    XrStructureType       type;
    శూన్య* XR_MAY_ALIAS    తదుపరి;
    LUID                  adapterLuid;
    D3D_FEATURE_LEVEL     minFeatureLevel;
} XrGraphicsRequirementsD3D12KHR;

రకనిర్వచనం Xr_ఫలితం (XRAPI_PTR *PFN_xrGetD3D12GraphicsRequirementsKHR)(XrInstance instance, XrSystemId systemId, XrGraphicsRequirementsD3D12KHR* graphicsRequirements);

#నిర్వచితం_కాకపోతే XR_NO_PROTOTYPES
#నిర్వచితమైతే XR_EXTENSION_PROTOTYPES
XRAPI_ATTR Xr_ఫలితం XRAPI_CALL xrGetD3D12GraphicsRequirementsKHR(
    XrInstance                                  instance,
    XrSystemId                                  systemId,
    XrGraphicsRequirementsD3D12KHR*             graphicsRequirements);
#అయితే_ముగింపు /* XR_EXTENSION_PROTOTYPES */
#అయితే_ముగింపు /* !XR_NO_PROTOTYPES */
#అయితే_ముగింపు /* XR_USE_GRAPHICS_API_D3D12 */

#నిర్వచితమైతే XR_USE_GRAPHICS_API_METAL

// XR_KHR_metal_enable is a preprocessor guard. Do not pass it to API calls.
#నిర్వచించు XR_KHR_metal_enable 1
#నిర్వచించు XR_KHR_metal_enable_SPEC_సంస్కరణ  3
#నిర్వచించు XR_KHR_METAL_ENABLE_EXTENSION_NAME "XR_KHR_metal_enable"
// XrGraphicsBindingMetalKHR extends XrSessionCreateInfo
రకనిర్వచనం నిర్మాణం XrGraphicsBindingMetalKHR {
    XrStructureType             type;
    స్థిరరాశి శూన్య* XR_MAY_ALIAS    తదుపరి;
    శూన్య* XR_MAY_ALIAS          command_వరుస;
} XrGraphicsBindingMetalKHR;

రకనిర్వచనం నిర్మాణం XrSwapchainImageMetalKHR {
    XrStructureType       type;
    శూన్య* XR_MAY_ALIAS    తదుపరి;
    శూన్య* XR_MAY_ALIAS    texture;
} XrSwapchainImageMetalKHR;

రకనిర్వచనం నిర్మాణం XrGraphicsRequirementsMetalKHR {
    XrStructureType       type;
    శూన్య* XR_MAY_ALIAS    తదుపరి;
    శూన్య* XR_MAY_ALIAS    metalDevice;
} XrGraphicsRequirementsMetalKHR;

రకనిర్వచనం Xr_ఫలితం (XRAPI_PTR *PFN_xrGetMetalGraphicsRequirementsKHR)(XrInstance instance, XrSystemId systemId, XrGraphicsRequirementsMetalKHR* graphicsRequirements);

#నిర్వచితం_కాకపోతే XR_NO_PROTOTYPES
#నిర్వచితమైతే XR_EXTENSION_PROTOTYPES
XRAPI_ATTR Xr_ఫలితం XRAPI_CALL xrGetMetalGraphicsRequirementsKHR(
    XrInstance                                  instance,
    XrSystemId                                  systemId,
    XrGraphicsRequirementsMetalKHR*             graphicsRequirements);
#అయితే_ముగింపు /* XR_EXTENSION_PROTOTYPES */
#అయితే_ముగింపు /* !XR_NO_PROTOTYPES */
#అయితే_ముగింపు /* XR_USE_GRAPHICS_API_METAL */

#నిర్వచితమైతే XR_USE_PLATFORM_WIN32

// XR_KHR_win32_convert_performance_counter_time is a preprocessor guard. Do not pass it to API calls.
#నిర్వచించు XR_KHR_win32_convert_performance_counter_సమయం 1
#నిర్వచించు XR_KHR_win32_convert_performance_counter_సమయం_SPEC_సంస్కరణ 1
#నిర్వచించు XR_KHR_WIN32_CONVERT_PERFORMANCE_COUNTER_సమయం_EXTENSION_NAME "XR_KHR_win32_convert_performance_counter_time"
రకనిర్వచనం Xr_ఫలితం (XRAPI_PTR *PFN_xr_Convert_Win32_Performance_Counter_గమ్యం_సమయం_KHR)(XrInstance instance, స్థిరరాశి LARGE_INTEGER* performanceCounter, Xr_సమయం* సమయం);
రకనిర్వచనం Xr_ఫలితం (XRAPI_PTR *PFN_xr_Convert_సమయం_గమ్యం_Win32_Performance_Counter_KHR)(XrInstance instance, Xr_సమయం సమయం, LARGE_INTEGER* performanceCounter);

#నిర్వచితం_కాకపోతే XR_NO_PROTOTYPES
#నిర్వచితమైతే XR_EXTENSION_PROTOTYPES
XRAPI_ATTR Xr_ఫలితం XRAPI_CALL xr_Convert_Win32_Performance_Counter_గమ్యం_సమయం_KHR(
    XrInstance                                  instance,
    స్థిరరాశి LARGE_INTEGER*                        performanceCounter,
    Xr_సమయం*                                     సమయం);

XRAPI_ATTR Xr_ఫలితం XRAPI_CALL xr_Convert_సమయం_గమ్యం_Win32_Performance_Counter_KHR(
    XrInstance                                  instance,
    Xr_సమయం                                      సమయం,
    LARGE_INTEGER*                              performanceCounter);
#అయితే_ముగింపు /* XR_EXTENSION_PROTOTYPES */
#అయితే_ముగింపు /* !XR_NO_PROTOTYPES */
#అయితే_ముగింపు /* XR_USE_PLATFORM_WIN32 */

#నిర్వచితమైతే XR_USE_TIMESPEC

// XR_KHR_convert_timespec_time is a preprocessor guard. Do not pass it to API calls.
#నిర్వచించు XR_KHR_convert_timespec_సమయం 1
#నిర్వచించు XR_KHR_convert_timespec_సమయం_SPEC_సంస్కరణ 1
#నిర్వచించు XR_KHR_CONVERT_TIMESPEC_సమయం_EXTENSION_NAME "XR_KHR_convert_timespec_time"
రకనిర్వచనం Xr_ఫలితం (XRAPI_PTR *PFN_xr_Convert_Timespec_సమయం_గమ్యం_సమయం_KHR)(XrInstance instance, స్థిరరాశి నిర్మాణం timespec* timespec_సమయం, Xr_సమయం* సమయం);
రకనిర్వచనం Xr_ఫలితం (XRAPI_PTR *PFN_xr_Convert_సమయం_గమ్యం_Timespec_సమయం_KHR)(XrInstance instance, Xr_సమయం సమయం, నిర్మాణం timespec* timespec_సమయం);

#నిర్వచితం_కాకపోతే XR_NO_PROTOTYPES
#నిర్వచితమైతే XR_EXTENSION_PROTOTYPES
XRAPI_ATTR Xr_ఫలితం XRAPI_CALL xr_Convert_Timespec_సమయం_గమ్యం_సమయం_KHR(
    XrInstance                                  instance,
    స్థిరరాశి నిర్మాణం timespec*                      timespec_సమయం,
    Xr_సమయం*                                     సమయం);

XRAPI_ATTR Xr_ఫలితం XRAPI_CALL xr_Convert_సమయం_గమ్యం_Timespec_సమయం_KHR(
    XrInstance                                  instance,
    Xr_సమయం                                      సమయం,
    నిర్మాణం timespec*                            timespec_సమయం);
#అయితే_ముగింపు /* XR_EXTENSION_PROTOTYPES */
#అయితే_ముగింపు /* !XR_NO_PROTOTYPES */
#అయితే_ముగింపు /* XR_USE_TIMESPEC */

#నిర్వచితమైతే XR_USE_PLATFORM_ANDROID

// XR_KHR_loader_init_android is a preprocessor guard. Do not pass it to API calls.
#నిర్వచించు XR_KHR_loader_init_android 1
#నిర్వచించు XR_KHR_loader_init_android_SPEC_సంస్కరణ 1
#నిర్వచించు XR_KHR_LOADER_INIT_ANDROID_EXTENSION_NAME "XR_KHR_loader_init_android"
రకనిర్వచనం నిర్మాణం XrLoaderInitInfoAndroidKHR {
    XrStructureType             type;
    స్థిరరాశి శూన్య* XR_MAY_ALIAS    తదుపరి;
    శూన్య* XR_MAY_ALIAS          applicationVM;
    శూన్య* XR_MAY_ALIAS          applicationContext;
} XrLoaderInitInfoAndroidKHR;

#అయితే_ముగింపు /* XR_USE_PLATFORM_ANDROID */

#నిర్వచితమైతే XR_USE_GRAPHICS_API_VULKAN

// XR_KHR_vulkan_enable2 is a preprocessor guard. Do not pass it to API calls.
#నిర్వచించు XR_KHR_vulkan_enable2 1
#నిర్వచించు XR_KHR_vulkan_enable2_SPEC_సంస్కరణ 4
#నిర్వచించు XR_KHR_VULKAN_ENABLE2_EXTENSION_NAME "XR_KHR_vulkan_enable2"
రకనిర్వచనం XrFlags64 XrVulkanInstanceCreateFlagsKHR;

// Flag bits for XrVulkanInstanceCreateFlagsKHR

రకనిర్వచనం XrFlags64 XrVulkanDeviceCreateFlagsKHR;

// Flag bits for XrVulkanDeviceCreateFlagsKHR

రకనిర్వచనం నిర్మాణం XrVulkanInstanceCreateInfoKHR {
    XrStructureType                   type;
    స్థిరరాశి శూన్య* XR_MAY_ALIAS          తదుపరి;
    XrSystemId                        systemId;
    XrVulkanInstanceCreateFlagsKHR    createFlags;
    PFN_vkGetInstanceProcAddr         pfnGetInstanceProcAddr;
    స్థిరరాశి VkInstanceCreateInfo*       vulkanCreateInfo;
    స్థిరరాశి Vk_కేటాయింపు_Callbacks*      vulkanAllocator;
} XrVulkanInstanceCreateInfoKHR;

రకనిర్వచనం నిర్మాణం XrVulkanDeviceCreateInfoKHR {
    XrStructureType                 type;
    స్థిరరాశి శూన్య* XR_MAY_ALIAS        తదుపరి;
    XrSystemId                      systemId;
    XrVulkanDeviceCreateFlagsKHR    createFlags;
    PFN_vkGetInstanceProcAddr       pfnGetInstanceProcAddr;
    VkPhysicalDevice                vulkanPhysicalDevice;
    స్థిరరాశి VkDeviceCreateInfo*       vulkanCreateInfo;
    స్థిరరాశి Vk_కేటాయింపు_Callbacks*    vulkanAllocator;
} XrVulkanDeviceCreateInfoKHR;

రకనిర్వచనం XrGraphicsBindingVulkanKHR XrGraphicsBindingVulkan2KHR;

రకనిర్వచనం నిర్మాణం XrVulkanGraphicsDeviceGetInfoKHR {
    XrStructureType             type;
    స్థిరరాశి శూన్య* XR_MAY_ALIAS    తదుపరి;
    XrSystemId                  systemId;
    VkInstance                  vulkanInstance;
} XrVulkanGraphicsDeviceGetInfoKHR;

రకనిర్వచనం XrSwapchainImageVulkanKHR XrSwapchainImageVulkan2KHR;

రకనిర్వచనం XrGraphicsRequirementsVulkanKHR XrGraphicsRequirementsVulkan2KHR;

రకనిర్వచనం Xr_ఫలితం (XRAPI_PTR *PFN_xrCreateVulkanInstanceKHR)(XrInstance instance, స్థిరరాశి XrVulkanInstanceCreateInfoKHR* createInfo, VkInstance* vulkanInstance, Vk_ఫలితం* vulkan_ఫలితం);
రకనిర్వచనం Xr_ఫలితం (XRAPI_PTR *PFN_xrCreateVulkanDeviceKHR)(XrInstance instance, స్థిరరాశి XrVulkanDeviceCreateInfoKHR* createInfo, VkDevice* vulkanDevice, Vk_ఫలితం* vulkan_ఫలితం);
రకనిర్వచనం Xr_ఫలితం (XRAPI_PTR *PFN_xrGetVulkanGraphicsDevice2KHR)(XrInstance instance, స్థిరరాశి XrVulkanGraphicsDeviceGetInfoKHR* getInfo, VkPhysicalDevice* vulkanPhysicalDevice);
రకనిర్వచనం Xr_ఫలితం (XRAPI_PTR *PFN_xrGetVulkanGraphicsRequirements2KHR)(XrInstance instance, XrSystemId systemId, XrGraphicsRequirementsVulkanKHR* graphicsRequirements);

#నిర్వచితం_కాకపోతే XR_NO_PROTOTYPES
#నిర్వచితమైతే XR_EXTENSION_PROTOTYPES
XRAPI_ATTR Xr_ఫలితం XRAPI_CALL xrCreateVulkanInstanceKHR(
    XrInstance                                  instance,
    స్థిరరాశి XrVulkanInstanceCreateInfoKHR*        createInfo,
    VkInstance*                                 vulkanInstance,
    Vk_ఫలితం*                                   vulkan_ఫలితం);

XRAPI_ATTR Xr_ఫలితం XRAPI_CALL xrCreateVulkanDeviceKHR(
    XrInstance                                  instance,
    స్థిరరాశి XrVulkanDeviceCreateInfoKHR*          createInfo,
    VkDevice*                                   vulkanDevice,
    Vk_ఫలితం*                                   vulkan_ఫలితం);

XRAPI_ATTR Xr_ఫలితం XRAPI_CALL xrGetVulkanGraphicsDevice2KHR(
    XrInstance                                  instance,
    స్థిరరాశి XrVulkanGraphicsDeviceGetInfoKHR*     getInfo,
    VkPhysicalDevice*                           vulkanPhysicalDevice);

XRAPI_ATTR Xr_ఫలితం XRAPI_CALL xrGetVulkanGraphicsRequirements2KHR(
    XrInstance                                  instance,
    XrSystemId                                  systemId,
    XrGraphicsRequirementsVulkanKHR*            graphicsRequirements);
#అయితే_ముగింపు /* XR_EXTENSION_PROTOTYPES */
#అయితే_ముగింపు /* !XR_NO_PROTOTYPES */
#అయితే_ముగింపు /* XR_USE_GRAPHICS_API_VULKAN */

#నిర్వచితమైతే XR_USE_PLATFORM_EGL

// XR_MNDX_egl_enable is a preprocessor guard. Do not pass it to API calls.
#నిర్వచించు XR_MNDX_egl_enable 1
#నిర్వచించు XR_MNDX_egl_enable_SPEC_సంస్కరణ   2
#నిర్వచించు XR_MNDX_EGL_ENABLE_EXTENSION_NAME "XR_MNDX_egl_enable"
రకనిర్వచనం PFN_xrVoidFunction (*PFN_xr_Egl_Get_Proc_చిరునామా_MNDX)(స్థిరరాశి అక్షరం *name);
// XrGraphicsBindingEGLMNDX extends XrSessionCreateInfo
రకనిర్వచనం నిర్మాణం XrGraphicsBindingEGLMNDX {
    XrStructureType                type;
    స్థిరరాశి శూన్య* XR_MAY_ALIAS       తదుపరి;
    PFN_xr_Egl_Get_Proc_చిరునామా_MNDX    get_Proc_చిరునామా;
    EGLDisplay                     display;
    EGLConfig                      config;
    EGLContext                     context;
} XrGraphicsBindingEGLMNDX;

#అయితే_ముగింపు /* XR_USE_PLATFORM_EGL */

#నిర్వచితమైతే XR_USE_PLATFORM_WIN32

// XR_MSFT_perception_anchor_interop is a preprocessor guard. Do not pass it to API calls.
#నిర్వచించు XR_MSFT_perception_anchor_interop 1
#నిర్వచించు XR_MSFT_perception_anchor_interop_SPEC_సంస్కరణ 1
#నిర్వచించు XR_MSFT_PERCEPTION_ANCHOR_INTEROP_EXTENSION_NAME "XR_MSFT_perception_anchor_interop"
రకనిర్వచనం Xr_ఫలితం (XRAPI_PTR *PFN_xrCreateSpatialAnchorFromPerceptionAnchorMSFT)(XrSession session, IUnknown* perceptionAnchor, XrSpatialAnchorMSFT* anchor);
రకనిర్వచనం Xr_ఫలితం (XRAPI_PTR *PFN_xrTryGetPerceptionAnchorFromSpatialAnchorMSFT)(XrSession session, XrSpatialAnchorMSFT anchor, IUnknown** perceptionAnchor);

#నిర్వచితం_కాకపోతే XR_NO_PROTOTYPES
#నిర్వచితమైతే XR_EXTENSION_PROTOTYPES
XRAPI_ATTR Xr_ఫలితం XRAPI_CALL xrCreateSpatialAnchorFromPerceptionAnchorMSFT(
    XrSession                                   session,
    IUnknown*                                   perceptionAnchor,
    XrSpatialAnchorMSFT*                        anchor);

XRAPI_ATTR Xr_ఫలితం XRAPI_CALL xrTryGetPerceptionAnchorFromSpatialAnchorMSFT(
    XrSession                                   session,
    XrSpatialAnchorMSFT                         anchor,
    IUnknown**                                  perceptionAnchor);
#అయితే_ముగింపు /* XR_EXTENSION_PROTOTYPES */
#అయితే_ముగింపు /* !XR_NO_PROTOTYPES */
#అయితే_ముగింపు /* XR_USE_PLATFORM_WIN32 */

#నిర్వచితమైతే XR_USE_PLATFORM_WIN32

// XR_MSFT_holographic_window_attachment is a preprocessor guard. Do not pass it to API calls.
#నిర్వచించు XR_MSFT_holographic_కిటికీ_attachment 1
#నిర్వచించు XR_MSFT_holographic_కిటికీ_attachment_SPEC_సంస్కరణ 1
#నిర్వచించు XR_MSFT_HOLOGRAPHIC_కిటికీ_ATTACHMENT_EXTENSION_NAME "XR_MSFT_holographic_window_attachment"
#నిర్వచితమైతే XR_USE_PLATFORM_WIN32
// XrHolographicWindowAttachmentMSFT extends XrSessionCreateInfo
రకనిర్వచనం నిర్మాణం Xr_Holographic_కిటికీ_Attachment_MSFT {
    XrStructureType             type;
    స్థిరరాశి శూన్య* XR_MAY_ALIAS    తదుపరి;
    IUnknown*                   holographicSpace;
    IUnknown*                   core_కిటికీ;
} Xr_Holographic_కిటికీ_Attachment_MSFT;
#అయితే_ముగింపు // XR_USE_PLATFORM_WIN32

#అయితే_ముగింపు /* XR_USE_PLATFORM_WIN32 */

#నిర్వచితమైతే XR_USE_PLATFORM_ANDROID

// XR_FB_android_surface_swapchain_create is a preprocessor guard. Do not pass it to API calls.
#నిర్వచించు XR_FB_android_surface_swapchain_create 1
#నిర్వచించు XR_FB_android_surface_swapchain_create_SPEC_సంస్కరణ 1
#నిర్వచించు XR_FB_ANDROID_SURFACE_SWAPCHAIN_CREATE_EXTENSION_NAME "XR_FB_android_surface_swapchain_create"
రకనిర్వచనం XrFlags64 XrAndroidSurfaceSwapchainFlagsFB;

// Flag bits for XrAndroidSurfaceSwapchainFlagsFB
స్థిర స్థిరరాశి XrAndroidSurfaceSwapchainFlagsFB XR_ANDROID_SURFACE_SWAPCHAIN_SYNCHRONOUS_బిట్టు_FB = 0x00000001;
స్థిర స్థిరరాశి XrAndroidSurfaceSwapchainFlagsFB XR_ANDROID_SURFACE_SWAPCHAIN_USE_TIMESTAMPS_బిట్టు_FB = 0x00000002;

#నిర్వచితమైతే XR_USE_PLATFORM_ANDROID
// XrAndroidSurfaceSwapchainCreateInfoFB extends XrSwapchainCreateInfo
రకనిర్వచనం నిర్మాణం XrAndroidSurfaceSwapchainCreateInfoFB {
    XrStructureType                     type;
    స్థిరరాశి శూన్య* XR_MAY_ALIAS            తదుపరి;
    XrAndroidSurfaceSwapchainFlagsFB    createFlags;
} XrAndroidSurfaceSwapchainCreateInfoFB;
#అయితే_ముగింపు // XR_USE_PLATFORM_ANDROID

#అయితే_ముగింపు /* XR_USE_PLATFORM_ANDROID */

#నిర్వచితమైతే XR_USE_PLATFORM_ML

// XR_ML_compat is a preprocessor guard. Do not pass it to API calls.
#నిర్వచించు XR_ML_compat 1
#నిర్వచించు XR_ML_compat_SPEC_సంస్కరణ         1
#నిర్వచించు XR_ML_COMPAT_EXTENSION_NAME       "XR_ML_compat"
రకనిర్వచనం నిర్మాణం XrCoordinateSpaceCreateInfoML {
    XrStructureType             type;
    స్థిరరాశి శూన్య* XR_MAY_ALIAS    తదుపరి;
    MLCoordinate_చట్రం_UID        cfuid;
    XrPosef                     pose_లోపల_Coordinate_Space;
} XrCoordinateSpaceCreateInfoML;

రకనిర్వచనం Xr_ఫలితం (XRAPI_PTR *PFN_xr_Create_Space_From_Coordinate_చట్రం_UIDML)(XrSession session, స్థిరరాశి XrCoordinateSpaceCreateInfoML *createInfo, XrSpace* space);

#నిర్వచితం_కాకపోతే XR_NO_PROTOTYPES
#నిర్వచితమైతే XR_EXTENSION_PROTOTYPES
XRAPI_ATTR Xr_ఫలితం XRAPI_CALL xr_Create_Space_From_Coordinate_చట్రం_UIDML(
    XrSession                                   session,
    స్థిరరాశి XrCoordinateSpaceCreateInfoML *       createInfo,
    XrSpace*                                    space);
#అయితే_ముగింపు /* XR_EXTENSION_PROTOTYPES */
#అయితే_ముగింపు /* !XR_NO_PROTOTYPES */
#అయితే_ముగింపు /* XR_USE_PLATFORM_ML */

#నిర్వచితమైతే XR_USE_PLATFORM_WIN32

// XR_OCULUS_audio_device_guid is a preprocessor guard. Do not pass it to API calls.
#నిర్వచించు XR_OCULUS_audio_device_guid 1
#నిర్వచించు XR_OCULUS_audio_device_guid_SPEC_సంస్కరణ 1
#నిర్వచించు XR_OCULUS_AUDIO_DEVICE_GUID_EXTENSION_NAME "XR_OCULUS_audio_device_guid"
#నిర్వచించు XR_MAX_AUDIO_DEVICE_STR_కొలత_OCULUS 128
రకనిర్వచనం Xr_ఫలితం (XRAPI_PTR *PFN_xrGetAudioOutputDeviceGuidOculus)(XrInstance instance, wchar_t బఫరు_2[XR_MAX_AUDIO_DEVICE_STR_కొలత_OCULUS]);
రకనిర్వచనం Xr_ఫలితం (XRAPI_PTR *PFN_xr_Get_Audio_ఆదానం_Device_Guid_Oculus)(XrInstance instance, wchar_t బఫరు_2[XR_MAX_AUDIO_DEVICE_STR_కొలత_OCULUS]);

#నిర్వచితం_కాకపోతే XR_NO_PROTOTYPES
#నిర్వచితమైతే XR_EXTENSION_PROTOTYPES
XRAPI_ATTR Xr_ఫలితం XRAPI_CALL xrGetAudioOutputDeviceGuidOculus(
    XrInstance                                  instance,
    wchar_t                                     బఫరు_2[XR_MAX_AUDIO_DEVICE_STR_కొలత_OCULUS]);

XRAPI_ATTR Xr_ఫలితం XRAPI_CALL xr_Get_Audio_ఆదానం_Device_Guid_Oculus(
    XrInstance                                  instance,
    wchar_t                                     బఫరు_2[XR_MAX_AUDIO_DEVICE_STR_కొలత_OCULUS]);
#అయితే_ముగింపు /* XR_EXTENSION_PROTOTYPES */
#అయితే_ముగింపు /* !XR_NO_PROTOTYPES */
#అయితే_ముగింపు /* XR_USE_PLATFORM_WIN32 */

#నిర్వచితమైతే XR_USE_GRAPHICS_API_VULKAN

// XR_FB_foveation_vulkan is a preprocessor guard. Do not pass it to API calls.
#నిర్వచించు XR_FB_foveation_vulkan 1
#నిర్వచించు XR_FB_foveation_vulkan_SPEC_సంస్కరణ 1
#నిర్వచించు XR_FB_FOVEATION_VULKAN_EXTENSION_NAME "XR_FB_foveation_vulkan"
// XrSwapchainImageFoveationVulkanFB extends XrSwapchainImageVulkanKHR
రకనిర్వచనం నిర్మాణం XrSwapchainImageFoveationVulkanFB {
    XrStructureType       type;
    శూన్య* XR_MAY_ALIAS    తదుపరి;
    VkImage               image;
    uint32_t              వెడల్పు;
    uint32_t              ఎత్తు;
} XrSwapchainImageFoveationVulkanFB;

#అయితే_ముగింపు /* XR_USE_GRAPHICS_API_VULKAN */

#నిర్వచితమైతే XR_USE_PLATFORM_ANDROID

// XR_FB_swapchain_update_state_android_surface is a preprocessor guard. Do not pass it to API calls.
#నిర్వచించు XR_FB_swapchain_update_state_android_surface 1
#నిర్వచించు XR_FB_swapchain_update_state_android_surface_SPEC_సంస్కరణ 1
#నిర్వచించు XR_FB_SWAPCHAIN_UPDATE_STATE_ANDROID_SURFACE_EXTENSION_NAME "XR_FB_swapchain_update_state_android_surface"
#నిర్వచితమైతే XR_USE_PLATFORM_ANDROID
రకనిర్వచనం నిర్మాణం XrSwapchainStateAndroidSurfaceDimensionsFB {
    XrStructureType       type;
    శూన్య* XR_MAY_ALIAS    తదుపరి;
    uint32_t              వెడల్పు;
    uint32_t              ఎత్తు;
} XrSwapchainStateAndroidSurfaceDimensionsFB;
#అయితే_ముగింపు // XR_USE_PLATFORM_ANDROID

#అయితే_ముగింపు /* XR_USE_PLATFORM_ANDROID */

#నిర్వచితమైతే XR_USE_GRAPHICS_API_OPENGL_ES

// XR_FB_swapchain_update_state_opengl_es is a preprocessor guard. Do not pass it to API calls.
#నిర్వచించు XR_FB_swapchain_update_state_opengl_es 1
#నిర్వచించు XR_FB_swapchain_update_state_opengl_es_SPEC_సంస్కరణ 1
#నిర్వచించు XR_FB_SWAPCHAIN_UPDATE_STATE_OPENGL_ES_EXTENSION_NAME "XR_FB_swapchain_update_state_opengl_es"
#నిర్వచితమైతే XR_USE_GRAPHICS_API_OPENGL_ES
రకనిర్వచనం నిర్మాణం XrSwapchainStateSamplerOpenGLESFB {
    XrStructureType       type;
    శూన్య* XR_MAY_ALIAS    తదుపరి;
    EGLenum               minFilter;
    EGLenum               magFilter;
    EGLenum               wrap_బహుళకం_S;
    EGLenum               wrap_బహుళకం_T;
    EGLenum               swizzleRed;
    EGLenum               swizzleGreen;
    EGLenum               swizzleBlue;
    EGLenum               swizzleAlpha;
    దశాంశం                 maxAnisotropy;
    XrColor4f             borderColor;
} XrSwapchainStateSamplerOpenGLESFB;
#అయితే_ముగింపు // XR_USE_GRAPHICS_API_OPENGL_ES

#అయితే_ముగింపు /* XR_USE_GRAPHICS_API_OPENGL_ES */

#నిర్వచితమైతే XR_USE_GRAPHICS_API_VULKAN

// XR_FB_swapchain_update_state_vulkan is a preprocessor guard. Do not pass it to API calls.
#నిర్వచించు XR_FB_swapchain_update_state_vulkan 1
#నిర్వచించు XR_FB_swapchain_update_state_vulkan_SPEC_సంస్కరణ 1
#నిర్వచించు XR_FB_SWAPCHAIN_UPDATE_STATE_VULKAN_EXTENSION_NAME "XR_FB_swapchain_update_state_vulkan"
#నిర్వచితమైతే XR_USE_GRAPHICS_API_VULKAN
రకనిర్వచనం నిర్మాణం XrSwapchainStateSamplerVulkanFB {
    XrStructureType         type;
    శూన్య* XR_MAY_ALIAS      తదుపరి;
    VkFilter                minFilter;
    VkFilter                magFilter;
    Vk_Sampler_Mipmap_బహుళకం     mipmap_బహుళకం;
    Vk_Sampler_చిరునామా_బహుళకం    wrap_బహుళకం_S;
    Vk_Sampler_చిరునామా_బహుళకం    wrap_బహుళకం_T;
    VkComponentSwizzle      swizzleRed;
    VkComponentSwizzle      swizzleGreen;
    VkComponentSwizzle      swizzleBlue;
    VkComponentSwizzle      swizzleAlpha;
    దశాంశం                   maxAnisotropy;
    XrColor4f               borderColor;
} XrSwapchainStateSamplerVulkanFB;
#అయితే_ముగింపు // XR_USE_GRAPHICS_API_VULKAN

#అయితే_ముగింపు /* XR_USE_GRAPHICS_API_VULKAN */

#నిర్వచితమైతే XR_USE_GRAPHICS_API_VULKAN

// XR_META_vulkan_swapchain_create_info is a preprocessor guard. Do not pass it to API calls.
#నిర్వచించు XR_META_vulkan_swapchain_create_info 1
#నిర్వచించు XR_META_vulkan_swapchain_create_info_SPEC_సంస్కరణ 1
#నిర్వచించు XR_META_VULKAN_SWAPCHAIN_CREATE_INFO_EXTENSION_NAME "XR_META_vulkan_swapchain_create_info"
// XrVulkanSwapchainCreateInfoMETA extends XrSwapchainCreateInfo
రకనిర్వచనం నిర్మాణం XrVulkanSwapchainCreateInfoMETA {
    XrStructureType             type;
    స్థిరరాశి శూన్య* XR_MAY_ALIAS    తదుపరి;
    VkImageCreateFlags          additionalCreateFlags;
    VkImageUsageFlags           additionalUsageFlags;
} XrVulkanSwapchainCreateInfoMETA;

#అయితే_ముగింపు /* XR_USE_GRAPHICS_API_VULKAN */

#నిర్వచితమైతే XR_USE_PLATFORM_ANDROID

// XR_ANDROID_anchor_sharing_export is a preprocessor guard. Do not pass it to API calls.
#నిర్వచించు XR_ANDROID_anchor_sharing_export 1
#నిర్వచించు XR_ANDROID_anchor_sharing_export_SPEC_సంస్కరణ 1
#నిర్వచించు XR_ANDROID_ANCHOR_SHARING_EXPORT_EXTENSION_NAME "XR_ANDROID_anchor_sharing_export"
రకనిర్వచనం నిర్మాణం XrAnchorSharingInfoANDROID {
    XrStructureType             type;
    స్థిరరాశి శూన్య* XR_MAY_ALIAS    తదుపరి;
    XrSpace                     anchor;
} XrAnchorSharingInfoANDROID;

రకనిర్వచనం నిర్మాణం XrAnchorSharingTokenANDROID {
    XrStructureType       type;
    శూన్య* XR_MAY_ALIAS    తదుపరి;
    నిర్మాణం AIBinder*      token;
} XrAnchorSharingTokenANDROID;

// XrSystemAnchorSharingExportPropertiesANDROID extends XrSystemProperties
రకనిర్వచనం నిర్మాణం XrSystemAnchorSharingExportPropertiesANDROID {
    XrStructureType       type;
    శూన్య* XR_MAY_ALIAS    తదుపరి;
    XrBool32              supportsAnchorSharingExport;
} XrSystemAnchorSharingExportPropertiesANDROID;

రకనిర్వచనం Xr_ఫలితం (XRAPI_PTR *PFN_xrShareAnchorANDROID)(XrSession session, స్థిరరాశి XrAnchorSharingInfoANDROID* sharingInfo, XrAnchorSharingTokenANDROID* anchorToken);
రకనిర్వచనం Xr_ఫలితం (XRAPI_PTR *PFN_xrUnshareAnchorANDROID)(XrSession session, XrSpace anchor);

#నిర్వచితం_కాకపోతే XR_NO_PROTOTYPES
#నిర్వచితమైతే XR_EXTENSION_PROTOTYPES
XRAPI_ATTR Xr_ఫలితం XRAPI_CALL xrShareAnchorANDROID(
    XrSession                                   session,
    స్థిరరాశి XrAnchorSharingInfoANDROID*           sharingInfo,
    XrAnchorSharingTokenANDROID*                anchorToken);

XRAPI_ATTR Xr_ఫలితం XRAPI_CALL xrUnshareAnchorANDROID(
    XrSession                                   session,
    XrSpace                                     anchor);
#అయితే_ముగింపు /* XR_EXTENSION_PROTOTYPES */
#అయితే_ముగింపు /* !XR_NO_PROTOTYPES */
#అయితే_ముగింపు /* XR_USE_PLATFORM_ANDROID */

#నిర్వచితమైతే __cplusplus
}
#అయితే_ముగింపు

#అయితే_ముగింపు
