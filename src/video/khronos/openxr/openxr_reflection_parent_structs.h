#که_نه_تعریف_شوی OPENXR_REFLECTION_پلار_STRUCTS_H
#تعریف_کړه OPENXR_REFLECTION_پلار_STRUCTS_H 1

/*
** Copyright (c) 2017-2026 The Khronos Group Inc.
**
** SPDX-License-Identifier: Apache-2.0 OR MIT
*/

/*
** This header is generated from the Khronos OpenXR XML API Registry.
**
*/

#ضمن "openxr.h"

/*
This file contains expansion macros (X Macros) for OpenXR structures that have a parent type.
*/


/// Like XR_LIST_ALL_STRUCTURE_TYPES, but only includes types whose parent struct type is XrCompositionLayerBaseHeader
#تعریف_کړه XR_LIST_ALL_ماشوم_STRUCTURE_TYPES_Xr_Composition_Layer_بنسټ_سرلیک(_avail, _unavail) \
    impl_XR_LIST_ALL_ماشوم_STRUCTURE_TYPES_Xr_Composition_Layer_بنسټ_سرلیک_CORE(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrCompositionLayerBaseHeader()
#تعریف_کړه impl_XR_LIST_ALL_ماشوم_STRUCTURE_TYPES_Xr_Composition_Layer_بنسټ_سرلیک_CORE(_avail, _unavail) \
    _avail(XrCompositionLayerProjection, XR_TYPE_COMPOSITION_LAYER_PROJECTION) \
    _avail(XrCompositionLayerQuad, XR_TYPE_COMPOSITION_LAYER_QUAD) \
    _avail(XrCompositionLayerCubeKHR, XR_TYPE_COMPOSITION_LAYER_CUBE_KHR) \
    _avail(XrCompositionLayerCylinderKHR, XR_TYPE_COMPOSITION_LAYER_CYLINDER_KHR) \
    _avail(XrCompositionLayerEquirectKHR, XR_TYPE_COMPOSITION_LAYER_EQUIRECT_KHR) \
    _avail(XrCompositionLayerEquirect2KHR, XR_TYPE_COMPOSITION_LAYER_EQUIRECT2_KHR) \
    _avail(XrCompositionLayerPassthroughFB, XR_TYPE_COMPOSITION_LAYER_PASSTHROUGH_FB) \
    _avail(XrCompositionLayerPassthroughHTC, XR_TYPE_COMPOSITION_LAYER_PASSTHROUGH_HTC) \
    _avail(XrCompositionLayerPassthroughANDROID, XR_TYPE_COMPOSITION_LAYER_PASSTHROUGH_ANDROID) \





/// Like XR_LIST_ALL_STRUCTURE_TYPES, but only includes types whose parent struct type is XrEventDataBaseHeader
#تعریف_کړه XR_LIST_ALL_ماشوم_STRUCTURE_TYPES_Xr_Event_معلومات_بنسټ_سرلیک(_avail, _unavail) \
    impl_XR_LIST_ALL_ماشوم_STRUCTURE_TYPES_Xr_Event_معلومات_بنسټ_سرلیک_CORE(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrEventDataBaseHeader()
#تعریف_کړه impl_XR_LIST_ALL_ماشوم_STRUCTURE_TYPES_Xr_Event_معلومات_بنسټ_سرلیک_CORE(_avail, _unavail) \
    _avail(Xr_Event_معلومات_Events_ورک, XR_TYPE_EVENT_معلومات_EVENTS_ورک) \
    _avail(Xr_Event_معلومات_Instance_Loss_Pending, XR_TYPE_EVENT_معلومات_INSTANCE_LOSS_PENDING) \
    _avail(Xr_Event_معلومات_Session_State_بدل_شوی, XR_TYPE_EVENT_معلومات_SESSION_STATE_بدل_شوی) \
    _avail(Xr_Event_معلومات_Reference_Space_Change_Pending, XR_TYPE_EVENT_معلومات_REFERENCE_SPACE_CHANGE_PENDING) \
    _avail(Xr_Event_معلومات_Interaction_Profile_بدل_شوی, XR_TYPE_EVENT_معلومات_INTERACTION_PROFILE_بدل_شوی) \
    _avail(Xr_Event_معلومات_Visibility_ماسک_بدل_شوی_KHR, XR_TYPE_EVENT_معلومات_VISIBILITY_ماسک_بدل_شوی_KHR) \
    _avail(Xr_Event_معلومات_Perf_Settings_EXT, XR_TYPE_EVENT_معلومات_PERF_SETTINGS_EXT) \
    _avail(Xr_Event_معلومات_Main_Session_Visibility_بدل_شوی_EXTX, XR_TYPE_EVENT_معلومات_MAIN_SESSION_VISIBILITY_بدل_شوی_EXTX) \
    _avail(Xr_Event_معلومات_Display_Refresh_شرح_بدل_شوی_FB, XR_TYPE_EVENT_معلومات_DISPLAY_REFRESH_شرح_بدل_شوی_FB) \
    _avail(Xr_Event_معلومات_Vive_Tracker_Connected_HTCX, XR_TYPE_EVENT_معلومات_VIVE_TRACKER_CONNECTED_HTCX) \
    _avail(Xr_Event_معلومات_Spatial_Anchor_Create_Complete_FB, XR_TYPE_EVENT_معلومات_SPATIAL_ANCHOR_CREATE_COMPLETE_FB) \
    _avail(Xr_Event_معلومات_Space_سېټ_حالت_Complete_FB, XR_TYPE_EVENT_معلومات_SPACE_سېټ_حالت_COMPLETE_FB) \
    _avail(Xr_Event_معلومات_Passthrough_State_بدل_شوی_FB, XR_TYPE_EVENT_معلومات_PASSTHROUGH_STATE_بدل_شوی_FB) \
    _avail(Xr_Event_معلومات_Marker_Tracking_Update_VARJO, XR_TYPE_EVENT_معلومات_MARKER_TRACKING_UPDATE_VARJO) \
    _avail(Xr_Event_معلومات_Localization_بدل_شوی_ML, XR_TYPE_EVENT_معلومات_LOCALIZATION_بدل_شوی_ML) \
    _avail(Xr_Event_معلومات_Space_Query_Results_شته_FB, XR_TYPE_EVENT_معلومات_SPACE_QUERY_RESULTS_شته_FB) \
    _avail(Xr_Event_معلومات_Space_Query_Complete_FB, XR_TYPE_EVENT_معلومات_SPACE_QUERY_COMPLETE_FB) \
    _avail(Xr_Event_معلومات_Space_Save_Complete_FB, XR_TYPE_EVENT_معلومات_SPACE_SAVE_COMPLETE_FB) \
    _avail(Xr_Event_معلومات_Space_Erase_Complete_FB, XR_TYPE_EVENT_معلومات_SPACE_ERASE_COMPLETE_FB) \
    _avail(Xr_Event_معلومات_Space_Share_Complete_FB, XR_TYPE_EVENT_معلومات_SPACE_SHARE_COMPLETE_FB) \
    _avail(Xr_Event_معلومات_Scene_Capture_Complete_FB, XR_TYPE_EVENT_معلومات_SCENE_CAPTURE_COMPLETE_FB) \
    _avail(Xr_Event_معلومات_Virtual_Keyboard_Commit_متن_META, XR_TYPE_EVENT_معلومات_VIRTUAL_KEYBOARD_COMMIT_متن_META) \
    _avail(Xr_Event_معلومات_Virtual_Keyboard_Backspace_META, XR_TYPE_EVENT_معلومات_VIRTUAL_KEYBOARD_BACKSPACE_META) \
    _avail(Xr_Event_معلومات_Virtual_Keyboard_Enter_META, XR_TYPE_EVENT_معلومات_VIRTUAL_KEYBOARD_ENTER_META) \
    _avail(Xr_Event_معلومات_Virtual_Keyboard_Shown_META, XR_TYPE_EVENT_معلومات_VIRTUAL_KEYBOARD_SHOWN_META) \
    _avail(Xr_Event_معلومات_Virtual_Keyboard_Hidden_META, XR_TYPE_EVENT_معلومات_VIRTUAL_KEYBOARD_HIDDEN_META) \
    _avail(Xr_Event_معلومات_Space_List_Save_Complete_FB, XR_TYPE_EVENT_معلومات_SPACE_LIST_SAVE_COMPLETE_FB) \
    _avail(Xr_Event_معلومات_Space_Discovery_Results_شته_META, XR_TYPE_EVENT_معلومات_SPACE_DISCOVERY_RESULTS_شته_META) \
    _avail(Xr_Event_معلومات_Space_Discovery_Complete_META, XR_TYPE_EVENT_معلومات_SPACE_DISCOVERY_COMPLETE_META) \
    _avail(Xr_Event_معلومات_Spaces_Save_پایله_META, XR_TYPE_EVENT_معلومات_SPACES_SAVE_پایله_META) \
    _avail(Xr_Event_معلومات_Spaces_Erase_پایله_META, XR_TYPE_EVENT_معلومات_SPACES_ERASE_پایله_META) \
    _avail(Xr_Event_معلومات_Passthrough_Layer_Resumed_META, XR_TYPE_EVENT_معلومات_PASSTHROUGH_LAYER_RESUMED_META) \
    _avail(Xr_Event_معلومات_Share_Spaces_Complete_META, XR_TYPE_EVENT_معلومات_SHARE_SPACES_COMPLETE_META) \
    _avail(Xr_Event_معلومات_Interaction_Render_Models_بدل_شوی_EXT, XR_TYPE_EVENT_معلومات_INTERACTION_RENDER_MODELS_بدل_شوی_EXT) \
    _avail(Xr_Event_معلومات_Sense_معلومات_Provider_State_بدل_شوی_BD, XR_TYPE_EVENT_معلومات_SENSE_معلومات_PROVIDER_STATE_بدل_شوی_BD) \
    _avail(Xr_Event_معلومات_Sense_معلومات_Updated_BD, XR_TYPE_EVENT_معلومات_SENSE_معلومات_UPDATED_BD) \
    _avail(Xr_Event_معلومات_Recommended_Resolution_بدل_شوی_ANDROID, XR_TYPE_EVENT_معلومات_RECOMMENDED_RESOLUTION_بدل_شوی_ANDROID) \
    _avail(Xr_Event_معلومات_User_Presence_بدل_شوی_EXT, XR_TYPE_EVENT_معلومات_USER_PRESENCE_بدل_شوی_EXT) \
    _avail(Xr_Event_معلومات_Headset_Fit_بدل_شوی_ML, XR_TYPE_EVENT_معلومات_HEADSET_FIT_بدل_شوی_ML) \
    _avail(Xr_Event_معلومات_Eye_Calibration_بدل_شوی_ML, XR_TYPE_EVENT_معلومات_EYE_CALIBRATION_بدل_شوی_ML) \
    _avail(Xr_Event_معلومات_Boundary_Visibility_بدل_شوی_META, XR_TYPE_EVENT_معلومات_BOUNDARY_VISIBILITY_بدل_شوی_META) \
    _avail(Xr_Event_معلومات_پیل_Colocation_Advertisement_Complete_META, XR_TYPE_EVENT_معلومات_پیل_COLOCATION_ADVERTISEMENT_COMPLETE_META) \
    _avail(Xr_Event_معلومات_Stop_Colocation_Advertisement_Complete_META, XR_TYPE_EVENT_معلومات_STOP_COLOCATION_ADVERTISEMENT_COMPLETE_META) \
    _avail(Xr_Event_معلومات_Colocation_Advertisement_Complete_META, XR_TYPE_EVENT_معلومات_COLOCATION_ADVERTISEMENT_COMPLETE_META) \
    _avail(Xr_Event_معلومات_پیل_Colocation_Discovery_Complete_META, XR_TYPE_EVENT_معلومات_پیل_COLOCATION_DISCOVERY_COMPLETE_META) \
    _avail(Xr_Event_معلومات_Colocation_Discovery_پایله_META, XR_TYPE_EVENT_معلومات_COLOCATION_DISCOVERY_پایله_META) \
    _avail(Xr_Event_معلومات_Colocation_Discovery_Complete_META, XR_TYPE_EVENT_معلومات_COLOCATION_DISCOVERY_COMPLETE_META) \
    _avail(Xr_Event_معلومات_Stop_Colocation_Discovery_Complete_META, XR_TYPE_EVENT_معلومات_STOP_COLOCATION_DISCOVERY_COMPLETE_META) \
    _avail(Xr_Event_معلومات_Image_Tracking_ورک_ANDROID, XR_TYPE_EVENT_معلومات_IMAGE_TRACKING_ورک_ANDROID) \
    _avail(Xr_Event_معلومات_Spatial_Discovery_Recommended_EXT, XR_TYPE_EVENT_معلومات_SPATIAL_DISCOVERY_RECOMMENDED_EXT) \
    _avail(Xr_Event_معلومات_Geospatial_Tracker_State_بدل_شوی_ANDROID, XR_TYPE_EVENT_معلومات_GEOSPATIAL_TRACKER_STATE_بدل_شوی_ANDROID) \
    _avail(Xr_Event_معلومات_Spatial_Container_Closed_EXT, XR_TYPE_EVENT_معلومات_SPATIAL_CONTAINER_CLOSED_EXT) \
    _avail(Xr_Event_معلومات_Spatial_Container_Bounds_بدل_شوی_EXT, XR_TYPE_EVENT_معلومات_SPATIAL_CONTAINER_BOUNDS_بدل_شوی_EXT) \
    _avail(Xr_Event_معلومات_Spatial_Container_Visible_بدل_شوی_EXT, XR_TYPE_EVENT_معلومات_SPATIAL_CONTAINER_VISIBLE_بدل_شوی_EXT) \
    _avail(Xr_Event_معلومات_Spatial_Container_Visible_Request_Denied_EXT, XR_TYPE_EVENT_معلومات_SPATIAL_CONTAINER_VISIBLE_REQUEST_DENIED_EXT) \
    _avail(Xr_Event_معلومات_Spatial_Container_Interactable_بدل_شوی_EXT, XR_TYPE_EVENT_معلومات_SPATIAL_CONTAINER_INTERACTABLE_بدل_شوی_EXT) \
    _avail(Xr_Event_معلومات_Spatial_Container_Bounds_ډېرپېښ_Request_Denied_EXT, XR_TYPE_EVENT_معلومات_SPATIAL_CONTAINER_BOUNDS_ډېرپېښ_REQUEST_DENIED_EXT) \
    _avail(Xr_Event_معلومات_View_Configuration_Views_بدل_شوی_EXT, XR_TYPE_EVENT_معلومات_VIEW_CONFIGURATION_VIEWS_بدل_شوی_EXT) \





/// Like XR_LIST_ALL_STRUCTURE_TYPES, but only includes types whose parent struct type is XrHapticBaseHeader
#تعریف_کړه XR_LIST_ALL_ماشوم_STRUCTURE_TYPES_Xr_Haptic_بنسټ_سرلیک(_avail, _unavail) \
    impl_XR_LIST_ALL_ماشوم_STRUCTURE_TYPES_Xr_Haptic_بنسټ_سرلیک_CORE(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrHapticBaseHeader()
#تعریف_کړه impl_XR_LIST_ALL_ماشوم_STRUCTURE_TYPES_Xr_Haptic_بنسټ_سرلیک_CORE(_avail, _unavail) \
    _avail(XrHapticVibration, XR_TYPE_HAPTIC_VIBRATION) \
    _avail(XrHapticAmplitudeEnvelopeVibrationFB, XR_TYPE_HAPTIC_AMPLITUDE_ENVELOPE_VIBRATION_FB) \
    _avail(XrHapticPcmVibrationFB, XR_TYPE_HAPTIC_PCM_VIBRATION_FB) \
    _avail(XrHapticParametricVibrationEXT, XR_TYPE_HAPTIC_PARAMETRIC_VIBRATION_EXT) \





/// Like XR_LIST_ALL_STRUCTURE_TYPES, but only includes types whose parent struct type is XrSwapchainImageBaseHeader
#تعریف_کړه XR_LIST_ALL_ماشوم_STRUCTURE_TYPES_Xr_Swapchain_Image_بنسټ_سرلیک(_avail, _unavail) \
    impl_XR_LIST_ALL_ماشوم_STRUCTURE_TYPES_Xr_Swapchain_Image_بنسټ_سرلیک_CORE(_avail, _unavail) \
    impl_XR_LIST_ALL_ماشوم_STRUCTURE_TYPES_Xr_Swapchain_Image_بنسټ_سرلیک_XR_USE_GRAPHICS_API_D3_D11(_avail, _unavail) \
    impl_XR_LIST_ALL_ماشوم_STRUCTURE_TYPES_Xr_Swapchain_Image_بنسټ_سرلیک_XR_USE_GRAPHICS_API_D3_D12(_avail, _unavail) \
    impl_XR_LIST_ALL_ماشوم_STRUCTURE_TYPES_Xr_Swapchain_Image_بنسټ_سرلیک_XR_USE_GRAPHICS_API_METAL(_avail, _unavail) \
    impl_XR_LIST_ALL_ماشوم_STRUCTURE_TYPES_Xr_Swapchain_Image_بنسټ_سرلیک_XR_USE_GRAPHICS_API_OPENGL(_avail, _unavail) \
    impl_XR_LIST_ALL_ماشوم_STRUCTURE_TYPES_Xr_Swapchain_Image_بنسټ_سرلیک_XR_USE_GRAPHICS_API_OPENGL_ES(_avail, _unavail) \
    impl_XR_LIST_ALL_ماشوم_STRUCTURE_TYPES_Xr_Swapchain_Image_بنسټ_سرلیک_XR_USE_GRAPHICS_API_VULKAN(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrSwapchainImageBaseHeader()
#تعریف_کړه impl_XR_LIST_ALL_ماشوم_STRUCTURE_TYPES_Xr_Swapchain_Image_بنسټ_سرلیک_CORE(_avail, _unavail) \


#إذا defined(XR_USE_GRAPHICS_API_D3D11)
#تعریف_کړه impl_XR_LIST_ALL_ماشوم_STRUCTURE_TYPES_Xr_Swapchain_Image_بنسټ_سرلیک_XR_USE_GRAPHICS_API_D3_D11(_avail, _unavail) \
    _avail(XrSwapchainImageD3D11KHR, XR_TYPE_SWAPCHAIN_IMAGE_D3D11_KHR) \

#وإلا
#تعریف_کړه impl_XR_LIST_ALL_ماشوم_STRUCTURE_TYPES_Xr_Swapchain_Image_بنسټ_سرلیک_XR_USE_GRAPHICS_API_D3_D11(_avail, _unavail) \
    _unavail(XrSwapchainImageD3D11KHR, XR_TYPE_SWAPCHAIN_IMAGE_D3D11_KHR) \

#د_که_پای

#إذا defined(XR_USE_GRAPHICS_API_D3D12)
#تعریف_کړه impl_XR_LIST_ALL_ماشوم_STRUCTURE_TYPES_Xr_Swapchain_Image_بنسټ_سرلیک_XR_USE_GRAPHICS_API_D3_D12(_avail, _unavail) \
    _avail(XrSwapchainImageD3D12KHR, XR_TYPE_SWAPCHAIN_IMAGE_D3D12_KHR) \

#وإلا
#تعریف_کړه impl_XR_LIST_ALL_ماشوم_STRUCTURE_TYPES_Xr_Swapchain_Image_بنسټ_سرلیک_XR_USE_GRAPHICS_API_D3_D12(_avail, _unavail) \
    _unavail(XrSwapchainImageD3D12KHR, XR_TYPE_SWAPCHAIN_IMAGE_D3D12_KHR) \

#د_که_پای

#إذا defined(XR_USE_GRAPHICS_API_METAL)
#تعریف_کړه impl_XR_LIST_ALL_ماشوم_STRUCTURE_TYPES_Xr_Swapchain_Image_بنسټ_سرلیک_XR_USE_GRAPHICS_API_METAL(_avail, _unavail) \
    _avail(XrSwapchainImageMetalKHR, XR_TYPE_SWAPCHAIN_IMAGE_METAL_KHR) \

#وإلا
#تعریف_کړه impl_XR_LIST_ALL_ماشوم_STRUCTURE_TYPES_Xr_Swapchain_Image_بنسټ_سرلیک_XR_USE_GRAPHICS_API_METAL(_avail, _unavail) \
    _unavail(XrSwapchainImageMetalKHR, XR_TYPE_SWAPCHAIN_IMAGE_METAL_KHR) \

#د_که_پای

#إذا defined(XR_USE_GRAPHICS_API_OPENGL)
#تعریف_کړه impl_XR_LIST_ALL_ماشوم_STRUCTURE_TYPES_Xr_Swapchain_Image_بنسټ_سرلیک_XR_USE_GRAPHICS_API_OPENGL(_avail, _unavail) \
    _avail(XrSwapchainImageOpenGLKHR, XR_TYPE_SWAPCHAIN_IMAGE_OPENGL_KHR) \

#وإلا
#تعریف_کړه impl_XR_LIST_ALL_ماشوم_STRUCTURE_TYPES_Xr_Swapchain_Image_بنسټ_سرلیک_XR_USE_GRAPHICS_API_OPENGL(_avail, _unavail) \
    _unavail(XrSwapchainImageOpenGLKHR, XR_TYPE_SWAPCHAIN_IMAGE_OPENGL_KHR) \

#د_که_پای

#إذا defined(XR_USE_GRAPHICS_API_OPENGL_ES)
#تعریف_کړه impl_XR_LIST_ALL_ماشوم_STRUCTURE_TYPES_Xr_Swapchain_Image_بنسټ_سرلیک_XR_USE_GRAPHICS_API_OPENGL_ES(_avail, _unavail) \
    _avail(XrSwapchainImageOpenGLESKHR, XR_TYPE_SWAPCHAIN_IMAGE_OPENGL_ES_KHR) \

#وإلا
#تعریف_کړه impl_XR_LIST_ALL_ماشوم_STRUCTURE_TYPES_Xr_Swapchain_Image_بنسټ_سرلیک_XR_USE_GRAPHICS_API_OPENGL_ES(_avail, _unavail) \
    _unavail(XrSwapchainImageOpenGLESKHR, XR_TYPE_SWAPCHAIN_IMAGE_OPENGL_ES_KHR) \

#د_که_پای

#إذا defined(XR_USE_GRAPHICS_API_VULKAN)
#تعریف_کړه impl_XR_LIST_ALL_ماشوم_STRUCTURE_TYPES_Xr_Swapchain_Image_بنسټ_سرلیک_XR_USE_GRAPHICS_API_VULKAN(_avail, _unavail) \
    _avail(XrSwapchainImageVulkanKHR, XR_TYPE_SWAPCHAIN_IMAGE_VULKAN_KHR) \

#وإلا
#تعریف_کړه impl_XR_LIST_ALL_ماشوم_STRUCTURE_TYPES_Xr_Swapchain_Image_بنسټ_سرلیک_XR_USE_GRAPHICS_API_VULKAN(_avail, _unavail) \
    _unavail(XrSwapchainImageVulkanKHR, XR_TYPE_SWAPCHAIN_IMAGE_VULKAN_KHR) \

#د_که_پای




/// Like XR_LIST_ALL_STRUCTURE_TYPES, but only includes types whose parent struct type is XrLoaderInitInfoBaseHeaderKHR
#تعریف_کړه XR_LIST_ALL_ماشوم_STRUCTURE_TYPES_Xr_Loader_Init_Info_بنسټ_سرلیک_KHR(_avail, _unavail) \
    impl_XR_LIST_ALL_ماشوم_STRUCTURE_TYPES_Xr_Loader_Init_Info_بنسټ_سرلیک_KHR_CORE(_avail, _unavail) \
    impl_XR_LIST_ALL_ماشوم_STRUCTURE_TYPES_Xr_Loader_Init_Info_بنسټ_سرلیک_KHR_XR_USE_PLATFORM_ANDROID(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrLoaderInitInfoBaseHeaderKHR()
#تعریف_کړه impl_XR_LIST_ALL_ماشوم_STRUCTURE_TYPES_Xr_Loader_Init_Info_بنسټ_سرلیک_KHR_CORE(_avail, _unavail) \
    _avail(XrLoaderInitInfoPropertiesEXT, XR_TYPE_LOADER_INIT_INFO_PROPERTIES_EXT) \


#إذا defined(XR_USE_PLATFORM_ANDROID)
#تعریف_کړه impl_XR_LIST_ALL_ماشوم_STRUCTURE_TYPES_Xr_Loader_Init_Info_بنسټ_سرلیک_KHR_XR_USE_PLATFORM_ANDROID(_avail, _unavail) \
    _avail(XrLoaderInitInfoAndroidKHR, XR_TYPE_LOADER_INIT_INFO_ANDROID_KHR) \

#وإلا
#تعریف_کړه impl_XR_LIST_ALL_ماشوم_STRUCTURE_TYPES_Xr_Loader_Init_Info_بنسټ_سرلیک_KHR_XR_USE_PLATFORM_ANDROID(_avail, _unavail) \
    _unavail(XrLoaderInitInfoAndroidKHR, XR_TYPE_LOADER_INIT_INFO_ANDROID_KHR) \

#د_که_پای




/// Like XR_LIST_ALL_STRUCTURE_TYPES, but only includes types whose parent struct type is XrBindingModificationBaseHeaderKHR
#تعریف_کړه XR_LIST_ALL_ماشوم_STRUCTURE_TYPES_Xr_Binding_Modification_بنسټ_سرلیک_KHR(_avail, _unavail) \
    impl_XR_LIST_ALL_ماشوم_STRUCTURE_TYPES_Xr_Binding_Modification_بنسټ_سرلیک_KHR_CORE(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrBindingModificationBaseHeaderKHR()
#تعریف_کړه impl_XR_LIST_ALL_ماشوم_STRUCTURE_TYPES_Xr_Binding_Modification_بنسټ_سرلیک_KHR_CORE(_avail, _unavail) \
    _avail(XrInteractionProfileDpadBindingEXT, XR_TYPE_INTERACTION_PROFILE_DPAD_BINDING_EXT) \
    _avail(Xr_Interaction_Profile_Analog_پوله_VALVE, XR_TYPE_INTERACTION_PROFILE_ANALOG_پوله_VALVE) \





/// Like XR_LIST_ALL_STRUCTURE_TYPES, but only includes types whose parent struct type is XrSwapchainStateBaseHeaderFB
#تعریف_کړه XR_LIST_ALL_ماشوم_STRUCTURE_TYPES_Xr_Swapchain_State_بنسټ_سرلیک_FB(_avail, _unavail) \
    impl_XR_LIST_ALL_ماشوم_STRUCTURE_TYPES_Xr_Swapchain_State_بنسټ_سرلیک_FB_CORE(_avail, _unavail) \
    impl_XR_LIST_ALL_ماشوم_STRUCTURE_TYPES_Xr_Swapchain_State_بنسټ_سرلیک_FB_XR_USE_GRAPHICS_API_OPENGL_ES(_avail, _unavail) \
    impl_XR_LIST_ALL_ماشوم_STRUCTURE_TYPES_Xr_Swapchain_State_بنسټ_سرلیک_FB_XR_USE_GRAPHICS_API_VULKAN(_avail, _unavail) \
    impl_XR_LIST_ALL_ماشوم_STRUCTURE_TYPES_Xr_Swapchain_State_بنسټ_سرلیک_FB_XR_USE_PLATFORM_ANDROID(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrSwapchainStateBaseHeaderFB()
#تعریف_کړه impl_XR_LIST_ALL_ماشوم_STRUCTURE_TYPES_Xr_Swapchain_State_بنسټ_سرلیک_FB_CORE(_avail, _unavail) \
    _avail(XrSwapchainStateFoveationFB, XR_TYPE_SWAPCHAIN_STATE_FOVEATION_FB) \


#إذا defined(XR_USE_GRAPHICS_API_OPENGL_ES)
#تعریف_کړه impl_XR_LIST_ALL_ماشوم_STRUCTURE_TYPES_Xr_Swapchain_State_بنسټ_سرلیک_FB_XR_USE_GRAPHICS_API_OPENGL_ES(_avail, _unavail) \
    _avail(XrSwapchainStateSamplerOpenGLESFB, XR_TYPE_SWAPCHAIN_STATE_SAMPLER_OPENGL_ES_FB) \

#وإلا
#تعریف_کړه impl_XR_LIST_ALL_ماشوم_STRUCTURE_TYPES_Xr_Swapchain_State_بنسټ_سرلیک_FB_XR_USE_GRAPHICS_API_OPENGL_ES(_avail, _unavail) \
    _unavail(XrSwapchainStateSamplerOpenGLESFB, XR_TYPE_SWAPCHAIN_STATE_SAMPLER_OPENGL_ES_FB) \

#د_که_پای

#إذا defined(XR_USE_GRAPHICS_API_VULKAN)
#تعریف_کړه impl_XR_LIST_ALL_ماشوم_STRUCTURE_TYPES_Xr_Swapchain_State_بنسټ_سرلیک_FB_XR_USE_GRAPHICS_API_VULKAN(_avail, _unavail) \
    _avail(XrSwapchainStateSamplerVulkanFB, XR_TYPE_SWAPCHAIN_STATE_SAMPLER_VULKAN_FB) \

#وإلا
#تعریف_کړه impl_XR_LIST_ALL_ماشوم_STRUCTURE_TYPES_Xr_Swapchain_State_بنسټ_سرلیک_FB_XR_USE_GRAPHICS_API_VULKAN(_avail, _unavail) \
    _unavail(XrSwapchainStateSamplerVulkanFB, XR_TYPE_SWAPCHAIN_STATE_SAMPLER_VULKAN_FB) \

#د_که_پای

#إذا defined(XR_USE_PLATFORM_ANDROID)
#تعریف_کړه impl_XR_LIST_ALL_ماشوم_STRUCTURE_TYPES_Xr_Swapchain_State_بنسټ_سرلیک_FB_XR_USE_PLATFORM_ANDROID(_avail, _unavail) \
    _avail(XrSwapchainStateAndroidSurfaceDimensionsFB, XR_TYPE_SWAPCHAIN_STATE_ANDROID_SURFACE_DIMENSIONS_FB) \

#وإلا
#تعریف_کړه impl_XR_LIST_ALL_ماشوم_STRUCTURE_TYPES_Xr_Swapchain_State_بنسټ_سرلیک_FB_XR_USE_PLATFORM_ANDROID(_avail, _unavail) \
    _unavail(XrSwapchainStateAndroidSurfaceDimensionsFB, XR_TYPE_SWAPCHAIN_STATE_ANDROID_SURFACE_DIMENSIONS_FB) \

#د_که_پای




/// Like XR_LIST_ALL_STRUCTURE_TYPES, but only includes types whose parent struct type is XrSpatialAnchorsCreateInfoBaseHeaderML
#تعریف_کړه XR_LIST_ALL_ماشوم_STRUCTURE_TYPES_Xr_Spatial_Anchors_Create_Info_بنسټ_سرلیک_ML(_avail, _unavail) \
    impl_XR_LIST_ALL_ماشوم_STRUCTURE_TYPES_Xr_Spatial_Anchors_Create_Info_بنسټ_سرلیک_ML_CORE(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrSpatialAnchorsCreateInfoBaseHeaderML()
#تعریف_کړه impl_XR_LIST_ALL_ماشوم_STRUCTURE_TYPES_Xr_Spatial_Anchors_Create_Info_بنسټ_سرلیک_ML_CORE(_avail, _unavail) \
    _avail(XrSpatialAnchorsCreateInfoFromPoseML, XR_TYPE_SPATIAL_ANCHORS_CREATE_INFO_FROM_POSE_ML) \
    _avail(XrSpatialAnchorsCreateInfoFromUuidsML, XR_TYPE_SPATIAL_ANCHORS_CREATE_INFO_FROM_UUIDS_ML) \





/// Like XR_LIST_ALL_STRUCTURE_TYPES, but only includes types whose parent struct type is XrFutureCompletionBaseHeaderEXT
#تعریف_کړه XR_LIST_ALL_ماشوم_STRUCTURE_TYPES_Xr_Future_Completion_بنسټ_سرلیک_EXT(_avail, _unavail) \
    impl_XR_LIST_ALL_ماشوم_STRUCTURE_TYPES_Xr_Future_Completion_بنسټ_سرلیک_EXT_CORE(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrFutureCompletionBaseHeaderEXT()
#تعریف_کړه impl_XR_LIST_ALL_ماشوم_STRUCTURE_TYPES_Xr_Future_Completion_بنسټ_سرلیک_EXT_CORE(_avail, _unavail) \
    _avail(XrCreateSpatialAnchorsCompletionML, XR_TYPE_CREATE_SPATIAL_ANCHORS_COMPLETION_ML) \
    _avail(XrSpatialAnchorsQueryCompletionML, XR_TYPE_SPATIAL_ANCHORS_QUERY_COMPLETION_ML) \
    _avail(XrSpatialAnchorsPublishCompletionML, XR_TYPE_SPATIAL_ANCHORS_PUBLISH_COMPLETION_ML) \
    _avail(XrSpatialAnchorsDeleteCompletionML, XR_TYPE_SPATIAL_ANCHORS_DELETE_COMPLETION_ML) \
    _avail(XrSpatialAnchorsUpdateExpirationCompletionML, XR_TYPE_SPATIAL_ANCHORS_UPDATE_EXPIRATION_COMPLETION_ML) \
    _avail(Xr_Sense_معلومات_Query_Completion_BD, XR_TYPE_SENSE_معلومات_QUERY_COMPLETION_BD) \
    _avail(XrFutureCompletionEXT, XR_TYPE_FUTURE_COMPLETION_EXT) \
    _avail(XrSpatialAnchorCreateCompletionBD, XR_TYPE_SPATIAL_ANCHOR_CREATE_COMPLETION_BD) \
    _avail(XrWorldMeshStateRequestCompletionML, XR_TYPE_WORLD_MESH_STATE_REQUEST_COMPLETION_ML) \
    _avail(XrWorldMeshRequestCompletionML, XR_TYPE_WORLD_MESH_REQUEST_COMPLETION_ML) \
    _avail(XrEnvironmentRaycasterCreateCompletionMETA, XR_TYPE_ENVIRONMENT_RAYCASTER_CREATE_COMPLETION_META) \
    _avail(XrCreateTrackableImageDatabaseCompletionANDROID, XR_TYPE_CREATE_TRACKABLE_IMAGE_DATABASE_COMPLETION_ANDROID) \
    _avail(XrCreateSpatialContextCompletionEXT, XR_TYPE_CREATE_SPATIAL_CONTEXT_COMPLETION_EXT) \
    _avail(XrCreateSpatialDiscoverySnapshotCompletionEXT, XR_TYPE_CREATE_SPATIAL_DISCOVERY_SNAPSHOT_COMPLETION_EXT) \
    _avail(XrCreateCameraDeviceCompletionBD, XR_TYPE_CREATE_CAMERA_DEVICE_COMPLETION_BD) \
    _avail(XrCreateCameraCaptureSessionCompletionBD, XR_TYPE_CREATE_CAMERA_CAPTURE_SESSION_COMPLETION_BD) \
    _avail(XrCreateSpatialPersistenceContextCompletionEXT, XR_TYPE_CREATE_SPATIAL_PERSISTENCE_CONTEXT_COMPLETION_EXT) \
    _avail(XrPersistSpatialEntityCompletionEXT, XR_TYPE_PERSIST_SPATIAL_ENTITY_COMPLETION_EXT) \
    _avail(XrUnpersistSpatialEntityCompletionEXT, XR_TYPE_UNPERSIST_SPATIAL_ENTITY_COMPLETION_EXT) \
    _avail(XrCreateSpatialImageTrackingDatabaseCompletionEXT, XR_TYPE_CREATE_SPATIAL_IMAGE_TRACKING_DATABASE_COMPLETION_EXT) \
    _avail(XrVPSAvailabilityCheckCompletionANDROID, XR_TYPE_VPS_AVAILABILITY_CHECK_COMPLETION_ANDROID) \
    _avail(XrSurfaceAnchorCreateCompletionANDROID, XR_TYPE_SURFACE_ANCHOR_CREATE_COMPLETION_ANDROID) \





/// Like XR_LIST_ALL_STRUCTURE_TYPES, but only includes types whose parent struct type is XrSpatialAnchorsQueryInfoBaseHeaderML
#تعریف_کړه XR_LIST_ALL_ماشوم_STRUCTURE_TYPES_Xr_Spatial_Anchors_Query_Info_بنسټ_سرلیک_ML(_avail, _unavail) \
    impl_XR_LIST_ALL_ماشوم_STRUCTURE_TYPES_Xr_Spatial_Anchors_Query_Info_بنسټ_سرلیک_ML_CORE(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrSpatialAnchorsQueryInfoBaseHeaderML()
#تعریف_کړه impl_XR_LIST_ALL_ماشوم_STRUCTURE_TYPES_Xr_Spatial_Anchors_Query_Info_بنسټ_سرلیک_ML_CORE(_avail, _unavail) \
    _avail(XrSpatialAnchorsQueryInfoRadiusML, XR_TYPE_SPATIAL_ANCHORS_QUERY_INFO_RADIUS_ML) \





/// Like XR_LIST_ALL_STRUCTURE_TYPES, but only includes types whose parent struct type is XrSpaceQueryInfoBaseHeaderFB
#تعریف_کړه XR_LIST_ALL_ماشوم_STRUCTURE_TYPES_Xr_Space_Query_Info_بنسټ_سرلیک_FB(_avail, _unavail) \
    impl_XR_LIST_ALL_ماشوم_STRUCTURE_TYPES_Xr_Space_Query_Info_بنسټ_سرلیک_FB_CORE(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrSpaceQueryInfoBaseHeaderFB()
#تعریف_کړه impl_XR_LIST_ALL_ماشوم_STRUCTURE_TYPES_Xr_Space_Query_Info_بنسټ_سرلیک_FB_CORE(_avail, _unavail) \
    _avail(XrSpaceQueryInfoFB, XR_TYPE_SPACE_QUERY_INFO_FB) \





/// Like XR_LIST_ALL_STRUCTURE_TYPES, but only includes types whose parent struct type is XrSpaceFilterInfoBaseHeaderFB
#تعریف_کړه XR_LIST_ALL_ماشوم_STRUCTURE_TYPES_Xr_Space_Filter_Info_بنسټ_سرلیک_FB(_avail, _unavail) \
    impl_XR_LIST_ALL_ماشوم_STRUCTURE_TYPES_Xr_Space_Filter_Info_بنسټ_سرلیک_FB_CORE(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrSpaceFilterInfoBaseHeaderFB()
#تعریف_کړه impl_XR_LIST_ALL_ماشوم_STRUCTURE_TYPES_Xr_Space_Filter_Info_بنسټ_سرلیک_FB_CORE(_avail, _unavail) \
    _avail(XrSpaceUuidFilterInfoFB, XR_TYPE_SPACE_UUID_FILTER_INFO_FB) \
    _avail(XrSpaceComponentFilterInfoFB, XR_TYPE_SPACE_COMPONENT_FILTER_INFO_FB) \





/// Like XR_LIST_ALL_STRUCTURE_TYPES, but only includes types whose parent struct type is XrSpaceFilterBaseHeaderMETA
#تعریف_کړه XR_LIST_ALL_ماشوم_STRUCTURE_TYPES_Xr_Space_Filter_بنسټ_سرلیک_META(_avail, _unavail) \
    impl_XR_LIST_ALL_ماشوم_STRUCTURE_TYPES_Xr_Space_Filter_بنسټ_سرلیک_META_CORE(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrSpaceFilterBaseHeaderMETA()
#تعریف_کړه impl_XR_LIST_ALL_ماشوم_STRUCTURE_TYPES_Xr_Space_Filter_بنسټ_سرلیک_META_CORE(_avail, _unavail) \
    _avail(XrSpaceFilterUuidMETA, XR_TYPE_SPACE_FILTER_UUID_META) \
    _avail(XrSpaceFilterComponentMETA, XR_TYPE_SPACE_FILTER_COMPONENT_META) \





/// Like XR_LIST_ALL_STRUCTURE_TYPES, but only includes types whose parent struct type is XrShareSpacesRecipientBaseHeaderMETA
#تعریف_کړه XR_LIST_ALL_ماشوم_STRUCTURE_TYPES_Xr_Share_Spaces_Recipient_بنسټ_سرلیک_META(_avail, _unavail) \
    impl_XR_LIST_ALL_ماشوم_STRUCTURE_TYPES_Xr_Share_Spaces_Recipient_بنسټ_سرلیک_META_CORE(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrShareSpacesRecipientBaseHeaderMETA()
#تعریف_کړه impl_XR_LIST_ALL_ماشوم_STRUCTURE_TYPES_Xr_Share_Spaces_Recipient_بنسټ_سرلیک_META_CORE(_avail, _unavail) \
    _avail(XrShareSpacesRecipientGroupsMETA, XR_TYPE_SHARE_SPACES_RECIPIENT_GROUPS_META) \





/// Like XR_LIST_ALL_STRUCTURE_TYPES, but only includes types whose parent struct type is XrEnvironmentRaycastFilterBaseHeaderMETA
#تعریف_کړه XR_LIST_ALL_ماشوم_STRUCTURE_TYPES_Xr_Environment_Raycast_Filter_بنسټ_سرلیک_META(_avail, _unavail) \
    impl_XR_LIST_ALL_ماشوم_STRUCTURE_TYPES_Xr_Environment_Raycast_Filter_بنسټ_سرلیک_META_CORE(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrEnvironmentRaycastFilterBaseHeaderMETA()
#تعریف_کړه impl_XR_LIST_ALL_ماشوم_STRUCTURE_TYPES_Xr_Environment_Raycast_Filter_بنسټ_سرلیک_META_CORE(_avail, _unavail) \
    _avail(Xr_Environment_Raycast_Filter_واټن_META, XR_TYPE_ENVIRONMENT_RAYCAST_FILTER_واټن_META) \





/// Like XR_LIST_ALL_STRUCTURE_TYPES, but only includes types whose parent struct type is XrSpatialCapabilityConfigurationBaseHeaderEXT
#تعریف_کړه XR_LIST_ALL_ماشوم_STRUCTURE_TYPES_Xr_Spatial_Capability_Configuration_بنسټ_سرلیک_EXT(_avail, _unavail) \
    impl_XR_LIST_ALL_ماشوم_STRUCTURE_TYPES_Xr_Spatial_Capability_Configuration_بنسټ_سرلیک_EXT_CORE(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrSpatialCapabilityConfigurationBaseHeaderEXT()
#تعریف_کړه impl_XR_LIST_ALL_ماشوم_STRUCTURE_TYPES_Xr_Spatial_Capability_Configuration_بنسټ_سرلیک_EXT_CORE(_avail, _unavail) \
    _avail(XrSpatialCapabilityConfigurationPlaneTrackingEXT, XR_TYPE_SPATIAL_CAPABILITY_CONFIGURATION_PLANE_TRACKING_EXT) \
    _avail(Xr_Spatial_Capability_Configuration_Qr_کوډ_EXT, XR_TYPE_SPATIAL_CAPABILITY_CONFIGURATION_QR_کوډ_EXT) \
    _avail(Xr_Spatial_Capability_Configuration_Micro_Qr_کوډ_EXT, XR_TYPE_SPATIAL_CAPABILITY_CONFIGURATION_MICRO_QR_کوډ_EXT) \
    _avail(XrSpatialCapabilityConfigurationArucoMarkerEXT, XR_TYPE_SPATIAL_CAPABILITY_CONFIGURATION_ARUCO_MARKER_EXT) \
    _avail(Xr_Spatial_Capability_Configuration_April_نښان_EXT, XR_TYPE_SPATIAL_CAPABILITY_CONFIGURATION_APRIL_نښان_EXT) \
    _avail(XrSpatialCapabilityConfigurationObjectTrackingEXT, XR_TYPE_SPATIAL_CAPABILITY_CONFIGURATION_OBJECT_TRACKING_EXT) \
    _avail(XrSpatialCapabilityConfigurationAnchorEXT, XR_TYPE_SPATIAL_CAPABILITY_CONFIGURATION_ANCHOR_EXT) \
    _avail(XrSpatialCapabilityConfigurationImageTrackingEXT, XR_TYPE_SPATIAL_CAPABILITY_CONFIGURATION_IMAGE_TRACKING_EXT) \
    _avail(XrSpatialCapabilityConfigurationMeshTrackingEXT, XR_TYPE_SPATIAL_CAPABILITY_CONFIGURATION_MESH_TRACKING_EXT) \
    _avail(XrSpatialCapabilityConfigurationObjectTrackingANDROID, XR_TYPE_SPATIAL_CAPABILITY_CONFIGURATION_OBJECT_TRACKING_ANDROID) \
    _avail(Xr_Spatial_Capability_Configuration_ژوروالی_Raycast_ANDROID, XR_TYPE_SPATIAL_CAPABILITY_CONFIGURATION_ژوروالی_RAYCAST_ANDROID) \





/// Like XR_LIST_ALL_STRUCTURE_TYPES, but only includes types whose parent struct type is XrCameraPropertyBaseHeaderBD
#تعریف_کړه XR_LIST_ALL_ماشوم_STRUCTURE_TYPES_Xr_Camera_Property_بنسټ_سرلیک_BD(_avail, _unavail) \
    impl_XR_LIST_ALL_ماشوم_STRUCTURE_TYPES_Xr_Camera_Property_بنسټ_سرلیک_BD_CORE(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrCameraPropertyBaseHeaderBD()
#تعریف_کړه impl_XR_LIST_ALL_ماشوم_STRUCTURE_TYPES_Xr_Camera_Property_بنسټ_سرلیک_BD_CORE(_avail, _unavail) \
    _avail(XrCameraPropertyFacingBD, XR_TYPE_CAMERA_PROPERTY_FACING_BD) \
    _avail(XrCameraPropertyPositionBD, XR_TYPE_CAMERA_PROPERTY_POSITION_BD) \
    _avail(XrCameraPropertyCameraTypeBD, XR_TYPE_CAMERA_PROPERTY_CAMERA_TYPE_BD) \





/// Like XR_LIST_ALL_STRUCTURE_TYPES, but only includes types whose parent struct type is XrCameraSupportedCapabilityBaseHeaderBD
#تعریف_کړه XR_LIST_ALL_ماشوم_STRUCTURE_TYPES_Xr_Camera_Supported_Capability_بنسټ_سرلیک_BD(_avail, _unavail) \
    impl_XR_LIST_ALL_ماشوم_STRUCTURE_TYPES_Xr_Camera_Supported_Capability_بنسټ_سرلیک_BD_CORE(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrCameraSupportedCapabilityBaseHeaderBD()
#تعریف_کړه impl_XR_LIST_ALL_ماشوم_STRUCTURE_TYPES_Xr_Camera_Supported_Capability_بنسټ_سرلیک_BD_CORE(_avail, _unavail) \
    _avail(Xr_Camera_Supported_Capability_Image_Resolution_And_چوکاټ_شرح_BD, XR_TYPE_CAMERA_SUPPORTED_CAPABILITY_IMAGE_RESOLUTION_AND_چوکاټ_شرح_BD) \
    _avail(Xr_Camera_Supported_Capability_معلومات_Transfer_Type_BD, XR_TYPE_CAMERA_SUPPORTED_CAPABILITY_معلومات_TRANSFER_TYPE_BD) \
    _avail(XrCameraSupportedCapabilityImageFormatBD, XR_TYPE_CAMERA_SUPPORTED_CAPABILITY_IMAGE_FORMAT_BD) \
    _avail(XrCameraSupportedCapabilityCameraModelBD, XR_TYPE_CAMERA_SUPPORTED_CAPABILITY_CAMERA_MODEL_BD) \





/// Like XR_LIST_ALL_STRUCTURE_TYPES, but only includes types whose parent struct type is XrCameraCapabilityBaseHeaderBD
#تعریف_کړه XR_LIST_ALL_ماشوم_STRUCTURE_TYPES_Xr_Camera_Capability_بنسټ_سرلیک_BD(_avail, _unavail) \
    impl_XR_LIST_ALL_ماشوم_STRUCTURE_TYPES_Xr_Camera_Capability_بنسټ_سرلیک_BD_CORE(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrCameraCapabilityBaseHeaderBD()
#تعریف_کړه impl_XR_LIST_ALL_ماشوم_STRUCTURE_TYPES_Xr_Camera_Capability_بنسټ_سرلیک_BD_CORE(_avail, _unavail) \
    _avail(Xr_Camera_Capability_Image_Resolution_And_چوکاټ_شرح_BD, XR_TYPE_CAMERA_CAPABILITY_IMAGE_RESOLUTION_AND_چوکاټ_شرح_BD) \
    _avail(Xr_Camera_Capability_معلومات_Transfer_Type_BD, XR_TYPE_CAMERA_CAPABILITY_معلومات_TRANSFER_TYPE_BD) \
    _avail(XrCameraCapabilityImageFormatBD, XR_TYPE_CAMERA_CAPABILITY_IMAGE_FORMAT_BD) \
    _avail(XrCameraCapabilityCameraModelBD, XR_TYPE_CAMERA_CAPABILITY_CAMERA_MODEL_BD) \





/// Like XR_LIST_ALL_STRUCTURE_TYPES, but only includes types whose parent struct type is XrCameraImageDataBaseHeaderBD
#تعریف_کړه XR_LIST_ALL_ماشوم_STRUCTURE_TYPES_Xr_Camera_Image_معلومات_بنسټ_سرلیک_BD(_avail, _unavail) \
    impl_XR_LIST_ALL_ماشوم_STRUCTURE_TYPES_Xr_Camera_Image_معلومات_بنسټ_سرلیک_BD_CORE(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrCameraImageDataBaseHeaderBD()
#تعریف_کړه impl_XR_LIST_ALL_ماشوم_STRUCTURE_TYPES_Xr_Camera_Image_معلومات_بنسټ_سرلیک_BD_CORE(_avail, _unavail) \
    _avail(Xr_Camera_Image_معلومات_Raw_بفر_BD, XR_TYPE_CAMERA_IMAGE_معلومات_RAW_بفر_BD) \





/// Like XR_LIST_ALL_STRUCTURE_TYPES, but only includes types whose parent struct type is XrGoogleCloudAuthInfoBaseHeaderANDROID
#تعریف_کړه XR_LIST_ALL_ماشوم_STRUCTURE_TYPES_Xr_Google_Cloud_Auth_Info_بنسټ_سرلیک_ANDROID(_avail, _unavail) \
    impl_XR_LIST_ALL_ماشوم_STRUCTURE_TYPES_Xr_Google_Cloud_Auth_Info_بنسټ_سرلیک_ANDROID_CORE(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrGoogleCloudAuthInfoBaseHeaderANDROID()
#تعریف_کړه impl_XR_LIST_ALL_ماشوم_STRUCTURE_TYPES_Xr_Google_Cloud_Auth_Info_بنسټ_سرلیک_ANDROID_CORE(_avail, _unavail) \
    _avail(Xr_Google_Cloud_Auth_Info_Api_کلی_ANDROID, XR_TYPE_GOOGLE_CLOUD_AUTH_INFO_API_کلی_ANDROID) \
    _avail(XrGoogleCloudAuthInfoTokenANDROID, XR_TYPE_GOOGLE_CLOUD_AUTH_INFO_TOKEN_ANDROID) \
    _avail(XrGoogleCloudAuthInfoKeylessANDROID, XR_TYPE_GOOGLE_CLOUD_AUTH_INFO_KEYLESS_ANDROID) \





#د_که_پای

