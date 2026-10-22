#جيڪڏهن_وصف_نه_ٿيل OPENXR_REFLECTION_والد_STRUCTS_H
#وصف_ڪريو OPENXR_REFLECTION_والد_STRUCTS_H 1

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
#وصف_ڪريو XR_LIST_ALL_ٻار_STRUCTURE_TYPES_Xr_Composition_Layer_بنياد_سرو(_avail, _unavail) \
    impl_XR_LIST_ALL_ٻار_STRUCTURE_TYPES_Xr_Composition_Layer_بنياد_سرو_CORE(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrCompositionLayerBaseHeader()
#وصف_ڪريو impl_XR_LIST_ALL_ٻار_STRUCTURE_TYPES_Xr_Composition_Layer_بنياد_سرو_CORE(_avail, _unavail) \
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
#وصف_ڪريو XR_LIST_ALL_ٻار_STRUCTURE_TYPES_Xr_Event_معلومات_بنياد_سرو(_avail, _unavail) \
    impl_XR_LIST_ALL_ٻار_STRUCTURE_TYPES_Xr_Event_معلومات_بنياد_سرو_CORE(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrEventDataBaseHeader()
#وصف_ڪريو impl_XR_LIST_ALL_ٻار_STRUCTURE_TYPES_Xr_Event_معلومات_بنياد_سرو_CORE(_avail, _unavail) \
    _avail(Xr_Event_معلومات_Events_گم, XR_TYPE_EVENT_معلومات_EVENTS_گم) \
    _avail(Xr_Event_معلومات_Instance_Loss_Pending, XR_TYPE_EVENT_معلومات_INSTANCE_LOSS_PENDING) \
    _avail(Xr_Event_معلومات_Session_State_بدليو, XR_TYPE_EVENT_معلومات_SESSION_STATE_بدليو) \
    _avail(Xr_Event_معلومات_Reference_Space_Change_Pending, XR_TYPE_EVENT_معلومات_REFERENCE_SPACE_CHANGE_PENDING) \
    _avail(Xr_Event_معلومات_Interaction_Profile_بدليو, XR_TYPE_EVENT_معلومات_INTERACTION_PROFILE_بدليو) \
    _avail(Xr_Event_معلومات_Visibility_نقاب_بدليو_KHR, XR_TYPE_EVENT_معلومات_VISIBILITY_نقاب_بدليو_KHR) \
    _avail(Xr_Event_معلومات_Perf_Settings_EXT, XR_TYPE_EVENT_معلومات_PERF_SETTINGS_EXT) \
    _avail(Xr_Event_معلومات_Main_Session_Visibility_بدليو_EXTX, XR_TYPE_EVENT_معلومات_MAIN_SESSION_VISIBILITY_بدليو_EXTX) \
    _avail(Xr_Event_معلومات_Display_Refresh_شرح_بدليو_FB, XR_TYPE_EVENT_معلومات_DISPLAY_REFRESH_شرح_بدليو_FB) \
    _avail(Xr_Event_معلومات_Vive_Tracker_Connected_HTCX, XR_TYPE_EVENT_معلومات_VIVE_TRACKER_CONNECTED_HTCX) \
    _avail(Xr_Event_معلومات_Spatial_Anchor_Create_Complete_FB, XR_TYPE_EVENT_معلومات_SPATIAL_ANCHOR_CREATE_COMPLETE_FB) \
    _avail(Xr_Event_معلومات_Space_سيٽ_حالت_Complete_FB, XR_TYPE_EVENT_معلومات_SPACE_سيٽ_حالت_COMPLETE_FB) \
    _avail(Xr_Event_معلومات_Passthrough_State_بدليو_FB, XR_TYPE_EVENT_معلومات_PASSTHROUGH_STATE_بدليو_FB) \
    _avail(Xr_Event_معلومات_Marker_Tracking_Update_VARJO, XR_TYPE_EVENT_معلومات_MARKER_TRACKING_UPDATE_VARJO) \
    _avail(Xr_Event_معلومات_Localization_بدليو_ML, XR_TYPE_EVENT_معلومات_LOCALIZATION_بدليو_ML) \
    _avail(Xr_Event_معلومات_Space_Query_Results_موجود_FB, XR_TYPE_EVENT_معلومات_SPACE_QUERY_RESULTS_موجود_FB) \
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
    _avail(Xr_Event_معلومات_Space_Discovery_Results_موجود_META, XR_TYPE_EVENT_معلومات_SPACE_DISCOVERY_RESULTS_موجود_META) \
    _avail(Xr_Event_معلومات_Space_Discovery_Complete_META, XR_TYPE_EVENT_معلومات_SPACE_DISCOVERY_COMPLETE_META) \
    _avail(Xr_Event_معلومات_Spaces_Save_نتيجو_META, XR_TYPE_EVENT_معلومات_SPACES_SAVE_نتيجو_META) \
    _avail(Xr_Event_معلومات_Spaces_Erase_نتيجو_META, XR_TYPE_EVENT_معلومات_SPACES_ERASE_نتيجو_META) \
    _avail(Xr_Event_معلومات_Passthrough_Layer_Resumed_META, XR_TYPE_EVENT_معلومات_PASSTHROUGH_LAYER_RESUMED_META) \
    _avail(Xr_Event_معلومات_Share_Spaces_Complete_META, XR_TYPE_EVENT_معلومات_SHARE_SPACES_COMPLETE_META) \
    _avail(Xr_Event_معلومات_Interaction_Render_Models_بدليو_EXT, XR_TYPE_EVENT_معلومات_INTERACTION_RENDER_MODELS_بدليو_EXT) \
    _avail(Xr_Event_معلومات_Sense_معلومات_Provider_State_بدليو_BD, XR_TYPE_EVENT_معلومات_SENSE_معلومات_PROVIDER_STATE_بدليو_BD) \
    _avail(Xr_Event_معلومات_Sense_معلومات_Updated_BD, XR_TYPE_EVENT_معلومات_SENSE_معلومات_UPDATED_BD) \
    _avail(Xr_Event_معلومات_Recommended_Resolution_بدليو_ANDROID, XR_TYPE_EVENT_معلومات_RECOMMENDED_RESOLUTION_بدليو_ANDROID) \
    _avail(Xr_Event_معلومات_User_Presence_بدليو_EXT, XR_TYPE_EVENT_معلومات_USER_PRESENCE_بدليو_EXT) \
    _avail(Xr_Event_معلومات_Headset_Fit_بدليو_ML, XR_TYPE_EVENT_معلومات_HEADSET_FIT_بدليو_ML) \
    _avail(Xr_Event_معلومات_Eye_Calibration_بدليو_ML, XR_TYPE_EVENT_معلومات_EYE_CALIBRATION_بدليو_ML) \
    _avail(Xr_Event_معلومات_Boundary_Visibility_بدليو_META, XR_TYPE_EVENT_معلومات_BOUNDARY_VISIBILITY_بدليو_META) \
    _avail(Xr_Event_معلومات_شروعات_Colocation_Advertisement_Complete_META, XR_TYPE_EVENT_معلومات_شروعات_COLOCATION_ADVERTISEMENT_COMPLETE_META) \
    _avail(Xr_Event_معلومات_Stop_Colocation_Advertisement_Complete_META, XR_TYPE_EVENT_معلومات_STOP_COLOCATION_ADVERTISEMENT_COMPLETE_META) \
    _avail(Xr_Event_معلومات_Colocation_Advertisement_Complete_META, XR_TYPE_EVENT_معلومات_COLOCATION_ADVERTISEMENT_COMPLETE_META) \
    _avail(Xr_Event_معلومات_شروعات_Colocation_Discovery_Complete_META, XR_TYPE_EVENT_معلومات_شروعات_COLOCATION_DISCOVERY_COMPLETE_META) \
    _avail(Xr_Event_معلومات_Colocation_Discovery_نتيجو_META, XR_TYPE_EVENT_معلومات_COLOCATION_DISCOVERY_نتيجو_META) \
    _avail(Xr_Event_معلومات_Colocation_Discovery_Complete_META, XR_TYPE_EVENT_معلومات_COLOCATION_DISCOVERY_COMPLETE_META) \
    _avail(Xr_Event_معلومات_Stop_Colocation_Discovery_Complete_META, XR_TYPE_EVENT_معلومات_STOP_COLOCATION_DISCOVERY_COMPLETE_META) \
    _avail(Xr_Event_معلومات_Image_Tracking_گم_ANDROID, XR_TYPE_EVENT_معلومات_IMAGE_TRACKING_گم_ANDROID) \
    _avail(Xr_Event_معلومات_Spatial_Discovery_Recommended_EXT, XR_TYPE_EVENT_معلومات_SPATIAL_DISCOVERY_RECOMMENDED_EXT) \
    _avail(Xr_Event_معلومات_Geospatial_Tracker_State_بدليو_ANDROID, XR_TYPE_EVENT_معلومات_GEOSPATIAL_TRACKER_STATE_بدليو_ANDROID) \
    _avail(Xr_Event_معلومات_Spatial_Container_Closed_EXT, XR_TYPE_EVENT_معلومات_SPATIAL_CONTAINER_CLOSED_EXT) \
    _avail(Xr_Event_معلومات_Spatial_Container_Bounds_بدليو_EXT, XR_TYPE_EVENT_معلومات_SPATIAL_CONTAINER_BOUNDS_بدليو_EXT) \
    _avail(Xr_Event_معلومات_Spatial_Container_Visible_بدليو_EXT, XR_TYPE_EVENT_معلومات_SPATIAL_CONTAINER_VISIBLE_بدليو_EXT) \
    _avail(Xr_Event_معلومات_Spatial_Container_Visible_Request_Denied_EXT, XR_TYPE_EVENT_معلومات_SPATIAL_CONTAINER_VISIBLE_REQUEST_DENIED_EXT) \
    _avail(Xr_Event_معلومات_Spatial_Container_Interactable_بدليو_EXT, XR_TYPE_EVENT_معلومات_SPATIAL_CONTAINER_INTERACTABLE_بدليو_EXT) \
    _avail(Xr_Event_معلومات_Spatial_Container_Bounds_گهڻائي_Request_Denied_EXT, XR_TYPE_EVENT_معلومات_SPATIAL_CONTAINER_BOUNDS_گهڻائي_REQUEST_DENIED_EXT) \
    _avail(Xr_Event_معلومات_View_Configuration_Views_بدليو_EXT, XR_TYPE_EVENT_معلومات_VIEW_CONFIGURATION_VIEWS_بدليو_EXT) \





/// Like XR_LIST_ALL_STRUCTURE_TYPES, but only includes types whose parent struct type is XrHapticBaseHeader
#وصف_ڪريو XR_LIST_ALL_ٻار_STRUCTURE_TYPES_Xr_Haptic_بنياد_سرو(_avail, _unavail) \
    impl_XR_LIST_ALL_ٻار_STRUCTURE_TYPES_Xr_Haptic_بنياد_سرو_CORE(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrHapticBaseHeader()
#وصف_ڪريو impl_XR_LIST_ALL_ٻار_STRUCTURE_TYPES_Xr_Haptic_بنياد_سرو_CORE(_avail, _unavail) \
    _avail(XrHapticVibration, XR_TYPE_HAPTIC_VIBRATION) \
    _avail(XrHapticAmplitudeEnvelopeVibrationFB, XR_TYPE_HAPTIC_AMPLITUDE_ENVELOPE_VIBRATION_FB) \
    _avail(XrHapticPcmVibrationFB, XR_TYPE_HAPTIC_PCM_VIBRATION_FB) \
    _avail(XrHapticParametricVibrationEXT, XR_TYPE_HAPTIC_PARAMETRIC_VIBRATION_EXT) \





/// Like XR_LIST_ALL_STRUCTURE_TYPES, but only includes types whose parent struct type is XrSwapchainImageBaseHeader
#وصف_ڪريو XR_LIST_ALL_ٻار_STRUCTURE_TYPES_Xr_Swapchain_Image_بنياد_سرو(_avail, _unavail) \
    impl_XR_LIST_ALL_ٻار_STRUCTURE_TYPES_Xr_Swapchain_Image_بنياد_سرو_CORE(_avail, _unavail) \
    impl_XR_LIST_ALL_ٻار_STRUCTURE_TYPES_Xr_Swapchain_Image_بنياد_سرو_XR_USE_GRAPHICS_API_D3_D11(_avail, _unavail) \
    impl_XR_LIST_ALL_ٻار_STRUCTURE_TYPES_Xr_Swapchain_Image_بنياد_سرو_XR_USE_GRAPHICS_API_D3_D12(_avail, _unavail) \
    impl_XR_LIST_ALL_ٻار_STRUCTURE_TYPES_Xr_Swapchain_Image_بنياد_سرو_XR_USE_GRAPHICS_API_METAL(_avail, _unavail) \
    impl_XR_LIST_ALL_ٻار_STRUCTURE_TYPES_Xr_Swapchain_Image_بنياد_سرو_XR_USE_GRAPHICS_API_OPENGL(_avail, _unavail) \
    impl_XR_LIST_ALL_ٻار_STRUCTURE_TYPES_Xr_Swapchain_Image_بنياد_سرو_XR_USE_GRAPHICS_API_OPENGL_ES(_avail, _unavail) \
    impl_XR_LIST_ALL_ٻار_STRUCTURE_TYPES_Xr_Swapchain_Image_بنياد_سرو_XR_USE_GRAPHICS_API_VULKAN(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrSwapchainImageBaseHeader()
#وصف_ڪريو impl_XR_LIST_ALL_ٻار_STRUCTURE_TYPES_Xr_Swapchain_Image_بنياد_سرو_CORE(_avail, _unavail) \


#إذا defined(XR_USE_GRAPHICS_API_D3D11)
#وصف_ڪريو impl_XR_LIST_ALL_ٻار_STRUCTURE_TYPES_Xr_Swapchain_Image_بنياد_سرو_XR_USE_GRAPHICS_API_D3_D11(_avail, _unavail) \
    _avail(XrSwapchainImageD3D11KHR, XR_TYPE_SWAPCHAIN_IMAGE_D3D11_KHR) \

#وإلا
#وصف_ڪريو impl_XR_LIST_ALL_ٻار_STRUCTURE_TYPES_Xr_Swapchain_Image_بنياد_سرو_XR_USE_GRAPHICS_API_D3_D11(_avail, _unavail) \
    _unavail(XrSwapchainImageD3D11KHR, XR_TYPE_SWAPCHAIN_IMAGE_D3D11_KHR) \

#جيڪڏهن_پورو

#إذا defined(XR_USE_GRAPHICS_API_D3D12)
#وصف_ڪريو impl_XR_LIST_ALL_ٻار_STRUCTURE_TYPES_Xr_Swapchain_Image_بنياد_سرو_XR_USE_GRAPHICS_API_D3_D12(_avail, _unavail) \
    _avail(XrSwapchainImageD3D12KHR, XR_TYPE_SWAPCHAIN_IMAGE_D3D12_KHR) \

#وإلا
#وصف_ڪريو impl_XR_LIST_ALL_ٻار_STRUCTURE_TYPES_Xr_Swapchain_Image_بنياد_سرو_XR_USE_GRAPHICS_API_D3_D12(_avail, _unavail) \
    _unavail(XrSwapchainImageD3D12KHR, XR_TYPE_SWAPCHAIN_IMAGE_D3D12_KHR) \

#جيڪڏهن_پورو

#إذا defined(XR_USE_GRAPHICS_API_METAL)
#وصف_ڪريو impl_XR_LIST_ALL_ٻار_STRUCTURE_TYPES_Xr_Swapchain_Image_بنياد_سرو_XR_USE_GRAPHICS_API_METAL(_avail, _unavail) \
    _avail(XrSwapchainImageMetalKHR, XR_TYPE_SWAPCHAIN_IMAGE_METAL_KHR) \

#وإلا
#وصف_ڪريو impl_XR_LIST_ALL_ٻار_STRUCTURE_TYPES_Xr_Swapchain_Image_بنياد_سرو_XR_USE_GRAPHICS_API_METAL(_avail, _unavail) \
    _unavail(XrSwapchainImageMetalKHR, XR_TYPE_SWAPCHAIN_IMAGE_METAL_KHR) \

#جيڪڏهن_پورو

#إذا defined(XR_USE_GRAPHICS_API_OPENGL)
#وصف_ڪريو impl_XR_LIST_ALL_ٻار_STRUCTURE_TYPES_Xr_Swapchain_Image_بنياد_سرو_XR_USE_GRAPHICS_API_OPENGL(_avail, _unavail) \
    _avail(XrSwapchainImageOpenGLKHR, XR_TYPE_SWAPCHAIN_IMAGE_OPENGL_KHR) \

#وإلا
#وصف_ڪريو impl_XR_LIST_ALL_ٻار_STRUCTURE_TYPES_Xr_Swapchain_Image_بنياد_سرو_XR_USE_GRAPHICS_API_OPENGL(_avail, _unavail) \
    _unavail(XrSwapchainImageOpenGLKHR, XR_TYPE_SWAPCHAIN_IMAGE_OPENGL_KHR) \

#جيڪڏهن_پورو

#إذا defined(XR_USE_GRAPHICS_API_OPENGL_ES)
#وصف_ڪريو impl_XR_LIST_ALL_ٻار_STRUCTURE_TYPES_Xr_Swapchain_Image_بنياد_سرو_XR_USE_GRAPHICS_API_OPENGL_ES(_avail, _unavail) \
    _avail(XrSwapchainImageOpenGLESKHR, XR_TYPE_SWAPCHAIN_IMAGE_OPENGL_ES_KHR) \

#وإلا
#وصف_ڪريو impl_XR_LIST_ALL_ٻار_STRUCTURE_TYPES_Xr_Swapchain_Image_بنياد_سرو_XR_USE_GRAPHICS_API_OPENGL_ES(_avail, _unavail) \
    _unavail(XrSwapchainImageOpenGLESKHR, XR_TYPE_SWAPCHAIN_IMAGE_OPENGL_ES_KHR) \

#جيڪڏهن_پورو

#إذا defined(XR_USE_GRAPHICS_API_VULKAN)
#وصف_ڪريو impl_XR_LIST_ALL_ٻار_STRUCTURE_TYPES_Xr_Swapchain_Image_بنياد_سرو_XR_USE_GRAPHICS_API_VULKAN(_avail, _unavail) \
    _avail(XrSwapchainImageVulkanKHR, XR_TYPE_SWAPCHAIN_IMAGE_VULKAN_KHR) \

#وإلا
#وصف_ڪريو impl_XR_LIST_ALL_ٻار_STRUCTURE_TYPES_Xr_Swapchain_Image_بنياد_سرو_XR_USE_GRAPHICS_API_VULKAN(_avail, _unavail) \
    _unavail(XrSwapchainImageVulkanKHR, XR_TYPE_SWAPCHAIN_IMAGE_VULKAN_KHR) \

#جيڪڏهن_پورو




/// Like XR_LIST_ALL_STRUCTURE_TYPES, but only includes types whose parent struct type is XrLoaderInitInfoBaseHeaderKHR
#وصف_ڪريو XR_LIST_ALL_ٻار_STRUCTURE_TYPES_Xr_Loader_Init_Info_بنياد_سرو_KHR(_avail, _unavail) \
    impl_XR_LIST_ALL_ٻار_STRUCTURE_TYPES_Xr_Loader_Init_Info_بنياد_سرو_KHR_CORE(_avail, _unavail) \
    impl_XR_LIST_ALL_ٻار_STRUCTURE_TYPES_Xr_Loader_Init_Info_بنياد_سرو_KHR_XR_USE_PLATFORM_ANDROID(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrLoaderInitInfoBaseHeaderKHR()
#وصف_ڪريو impl_XR_LIST_ALL_ٻار_STRUCTURE_TYPES_Xr_Loader_Init_Info_بنياد_سرو_KHR_CORE(_avail, _unavail) \
    _avail(XrLoaderInitInfoPropertiesEXT, XR_TYPE_LOADER_INIT_INFO_PROPERTIES_EXT) \


#إذا defined(XR_USE_PLATFORM_ANDROID)
#وصف_ڪريو impl_XR_LIST_ALL_ٻار_STRUCTURE_TYPES_Xr_Loader_Init_Info_بنياد_سرو_KHR_XR_USE_PLATFORM_ANDROID(_avail, _unavail) \
    _avail(XrLoaderInitInfoAndroidKHR, XR_TYPE_LOADER_INIT_INFO_ANDROID_KHR) \

#وإلا
#وصف_ڪريو impl_XR_LIST_ALL_ٻار_STRUCTURE_TYPES_Xr_Loader_Init_Info_بنياد_سرو_KHR_XR_USE_PLATFORM_ANDROID(_avail, _unavail) \
    _unavail(XrLoaderInitInfoAndroidKHR, XR_TYPE_LOADER_INIT_INFO_ANDROID_KHR) \

#جيڪڏهن_پورو




/// Like XR_LIST_ALL_STRUCTURE_TYPES, but only includes types whose parent struct type is XrBindingModificationBaseHeaderKHR
#وصف_ڪريو XR_LIST_ALL_ٻار_STRUCTURE_TYPES_Xr_Binding_Modification_بنياد_سرو_KHR(_avail, _unavail) \
    impl_XR_LIST_ALL_ٻار_STRUCTURE_TYPES_Xr_Binding_Modification_بنياد_سرو_KHR_CORE(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrBindingModificationBaseHeaderKHR()
#وصف_ڪريو impl_XR_LIST_ALL_ٻار_STRUCTURE_TYPES_Xr_Binding_Modification_بنياد_سرو_KHR_CORE(_avail, _unavail) \
    _avail(XrInteractionProfileDpadBindingEXT, XR_TYPE_INTERACTION_PROFILE_DPAD_BINDING_EXT) \
    _avail(Xr_Interaction_Profile_Analog_حد_VALVE, XR_TYPE_INTERACTION_PROFILE_ANALOG_حد_VALVE) \





/// Like XR_LIST_ALL_STRUCTURE_TYPES, but only includes types whose parent struct type is XrSwapchainStateBaseHeaderFB
#وصف_ڪريو XR_LIST_ALL_ٻار_STRUCTURE_TYPES_Xr_Swapchain_State_بنياد_سرو_FB(_avail, _unavail) \
    impl_XR_LIST_ALL_ٻار_STRUCTURE_TYPES_Xr_Swapchain_State_بنياد_سرو_FB_CORE(_avail, _unavail) \
    impl_XR_LIST_ALL_ٻار_STRUCTURE_TYPES_Xr_Swapchain_State_بنياد_سرو_FB_XR_USE_GRAPHICS_API_OPENGL_ES(_avail, _unavail) \
    impl_XR_LIST_ALL_ٻار_STRUCTURE_TYPES_Xr_Swapchain_State_بنياد_سرو_FB_XR_USE_GRAPHICS_API_VULKAN(_avail, _unavail) \
    impl_XR_LIST_ALL_ٻار_STRUCTURE_TYPES_Xr_Swapchain_State_بنياد_سرو_FB_XR_USE_PLATFORM_ANDROID(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrSwapchainStateBaseHeaderFB()
#وصف_ڪريو impl_XR_LIST_ALL_ٻار_STRUCTURE_TYPES_Xr_Swapchain_State_بنياد_سرو_FB_CORE(_avail, _unavail) \
    _avail(XrSwapchainStateFoveationFB, XR_TYPE_SWAPCHAIN_STATE_FOVEATION_FB) \


#إذا defined(XR_USE_GRAPHICS_API_OPENGL_ES)
#وصف_ڪريو impl_XR_LIST_ALL_ٻار_STRUCTURE_TYPES_Xr_Swapchain_State_بنياد_سرو_FB_XR_USE_GRAPHICS_API_OPENGL_ES(_avail, _unavail) \
    _avail(XrSwapchainStateSamplerOpenGLESFB, XR_TYPE_SWAPCHAIN_STATE_SAMPLER_OPENGL_ES_FB) \

#وإلا
#وصف_ڪريو impl_XR_LIST_ALL_ٻار_STRUCTURE_TYPES_Xr_Swapchain_State_بنياد_سرو_FB_XR_USE_GRAPHICS_API_OPENGL_ES(_avail, _unavail) \
    _unavail(XrSwapchainStateSamplerOpenGLESFB, XR_TYPE_SWAPCHAIN_STATE_SAMPLER_OPENGL_ES_FB) \

#جيڪڏهن_پورو

#إذا defined(XR_USE_GRAPHICS_API_VULKAN)
#وصف_ڪريو impl_XR_LIST_ALL_ٻار_STRUCTURE_TYPES_Xr_Swapchain_State_بنياد_سرو_FB_XR_USE_GRAPHICS_API_VULKAN(_avail, _unavail) \
    _avail(XrSwapchainStateSamplerVulkanFB, XR_TYPE_SWAPCHAIN_STATE_SAMPLER_VULKAN_FB) \

#وإلا
#وصف_ڪريو impl_XR_LIST_ALL_ٻار_STRUCTURE_TYPES_Xr_Swapchain_State_بنياد_سرو_FB_XR_USE_GRAPHICS_API_VULKAN(_avail, _unavail) \
    _unavail(XrSwapchainStateSamplerVulkanFB, XR_TYPE_SWAPCHAIN_STATE_SAMPLER_VULKAN_FB) \

#جيڪڏهن_پورو

#إذا defined(XR_USE_PLATFORM_ANDROID)
#وصف_ڪريو impl_XR_LIST_ALL_ٻار_STRUCTURE_TYPES_Xr_Swapchain_State_بنياد_سرو_FB_XR_USE_PLATFORM_ANDROID(_avail, _unavail) \
    _avail(XrSwapchainStateAndroidSurfaceDimensionsFB, XR_TYPE_SWAPCHAIN_STATE_ANDROID_SURFACE_DIMENSIONS_FB) \

#وإلا
#وصف_ڪريو impl_XR_LIST_ALL_ٻار_STRUCTURE_TYPES_Xr_Swapchain_State_بنياد_سرو_FB_XR_USE_PLATFORM_ANDROID(_avail, _unavail) \
    _unavail(XrSwapchainStateAndroidSurfaceDimensionsFB, XR_TYPE_SWAPCHAIN_STATE_ANDROID_SURFACE_DIMENSIONS_FB) \

#جيڪڏهن_پورو




/// Like XR_LIST_ALL_STRUCTURE_TYPES, but only includes types whose parent struct type is XrSpatialAnchorsCreateInfoBaseHeaderML
#وصف_ڪريو XR_LIST_ALL_ٻار_STRUCTURE_TYPES_Xr_Spatial_Anchors_Create_Info_بنياد_سرو_ML(_avail, _unavail) \
    impl_XR_LIST_ALL_ٻار_STRUCTURE_TYPES_Xr_Spatial_Anchors_Create_Info_بنياد_سرو_ML_CORE(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrSpatialAnchorsCreateInfoBaseHeaderML()
#وصف_ڪريو impl_XR_LIST_ALL_ٻار_STRUCTURE_TYPES_Xr_Spatial_Anchors_Create_Info_بنياد_سرو_ML_CORE(_avail, _unavail) \
    _avail(XrSpatialAnchorsCreateInfoFromPoseML, XR_TYPE_SPATIAL_ANCHORS_CREATE_INFO_FROM_POSE_ML) \
    _avail(XrSpatialAnchorsCreateInfoFromUuidsML, XR_TYPE_SPATIAL_ANCHORS_CREATE_INFO_FROM_UUIDS_ML) \





/// Like XR_LIST_ALL_STRUCTURE_TYPES, but only includes types whose parent struct type is XrFutureCompletionBaseHeaderEXT
#وصف_ڪريو XR_LIST_ALL_ٻار_STRUCTURE_TYPES_Xr_Future_Completion_بنياد_سرو_EXT(_avail, _unavail) \
    impl_XR_LIST_ALL_ٻار_STRUCTURE_TYPES_Xr_Future_Completion_بنياد_سرو_EXT_CORE(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrFutureCompletionBaseHeaderEXT()
#وصف_ڪريو impl_XR_LIST_ALL_ٻار_STRUCTURE_TYPES_Xr_Future_Completion_بنياد_سرو_EXT_CORE(_avail, _unavail) \
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
#وصف_ڪريو XR_LIST_ALL_ٻار_STRUCTURE_TYPES_Xr_Spatial_Anchors_Query_Info_بنياد_سرو_ML(_avail, _unavail) \
    impl_XR_LIST_ALL_ٻار_STRUCTURE_TYPES_Xr_Spatial_Anchors_Query_Info_بنياد_سرو_ML_CORE(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrSpatialAnchorsQueryInfoBaseHeaderML()
#وصف_ڪريو impl_XR_LIST_ALL_ٻار_STRUCTURE_TYPES_Xr_Spatial_Anchors_Query_Info_بنياد_سرو_ML_CORE(_avail, _unavail) \
    _avail(XrSpatialAnchorsQueryInfoRadiusML, XR_TYPE_SPATIAL_ANCHORS_QUERY_INFO_RADIUS_ML) \





/// Like XR_LIST_ALL_STRUCTURE_TYPES, but only includes types whose parent struct type is XrSpaceQueryInfoBaseHeaderFB
#وصف_ڪريو XR_LIST_ALL_ٻار_STRUCTURE_TYPES_Xr_Space_Query_Info_بنياد_سرو_FB(_avail, _unavail) \
    impl_XR_LIST_ALL_ٻار_STRUCTURE_TYPES_Xr_Space_Query_Info_بنياد_سرو_FB_CORE(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrSpaceQueryInfoBaseHeaderFB()
#وصف_ڪريو impl_XR_LIST_ALL_ٻار_STRUCTURE_TYPES_Xr_Space_Query_Info_بنياد_سرو_FB_CORE(_avail, _unavail) \
    _avail(XrSpaceQueryInfoFB, XR_TYPE_SPACE_QUERY_INFO_FB) \





/// Like XR_LIST_ALL_STRUCTURE_TYPES, but only includes types whose parent struct type is XrSpaceFilterInfoBaseHeaderFB
#وصف_ڪريو XR_LIST_ALL_ٻار_STRUCTURE_TYPES_Xr_Space_Filter_Info_بنياد_سرو_FB(_avail, _unavail) \
    impl_XR_LIST_ALL_ٻار_STRUCTURE_TYPES_Xr_Space_Filter_Info_بنياد_سرو_FB_CORE(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrSpaceFilterInfoBaseHeaderFB()
#وصف_ڪريو impl_XR_LIST_ALL_ٻار_STRUCTURE_TYPES_Xr_Space_Filter_Info_بنياد_سرو_FB_CORE(_avail, _unavail) \
    _avail(XrSpaceUuidFilterInfoFB, XR_TYPE_SPACE_UUID_FILTER_INFO_FB) \
    _avail(XrSpaceComponentFilterInfoFB, XR_TYPE_SPACE_COMPONENT_FILTER_INFO_FB) \





/// Like XR_LIST_ALL_STRUCTURE_TYPES, but only includes types whose parent struct type is XrSpaceFilterBaseHeaderMETA
#وصف_ڪريو XR_LIST_ALL_ٻار_STRUCTURE_TYPES_Xr_Space_Filter_بنياد_سرو_META(_avail, _unavail) \
    impl_XR_LIST_ALL_ٻار_STRUCTURE_TYPES_Xr_Space_Filter_بنياد_سرو_META_CORE(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrSpaceFilterBaseHeaderMETA()
#وصف_ڪريو impl_XR_LIST_ALL_ٻار_STRUCTURE_TYPES_Xr_Space_Filter_بنياد_سرو_META_CORE(_avail, _unavail) \
    _avail(XrSpaceFilterUuidMETA, XR_TYPE_SPACE_FILTER_UUID_META) \
    _avail(XrSpaceFilterComponentMETA, XR_TYPE_SPACE_FILTER_COMPONENT_META) \





/// Like XR_LIST_ALL_STRUCTURE_TYPES, but only includes types whose parent struct type is XrShareSpacesRecipientBaseHeaderMETA
#وصف_ڪريو XR_LIST_ALL_ٻار_STRUCTURE_TYPES_Xr_Share_Spaces_Recipient_بنياد_سرو_META(_avail, _unavail) \
    impl_XR_LIST_ALL_ٻار_STRUCTURE_TYPES_Xr_Share_Spaces_Recipient_بنياد_سرو_META_CORE(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrShareSpacesRecipientBaseHeaderMETA()
#وصف_ڪريو impl_XR_LIST_ALL_ٻار_STRUCTURE_TYPES_Xr_Share_Spaces_Recipient_بنياد_سرو_META_CORE(_avail, _unavail) \
    _avail(XrShareSpacesRecipientGroupsMETA, XR_TYPE_SHARE_SPACES_RECIPIENT_GROUPS_META) \





/// Like XR_LIST_ALL_STRUCTURE_TYPES, but only includes types whose parent struct type is XrEnvironmentRaycastFilterBaseHeaderMETA
#وصف_ڪريو XR_LIST_ALL_ٻار_STRUCTURE_TYPES_Xr_Environment_Raycast_Filter_بنياد_سرو_META(_avail, _unavail) \
    impl_XR_LIST_ALL_ٻار_STRUCTURE_TYPES_Xr_Environment_Raycast_Filter_بنياد_سرو_META_CORE(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrEnvironmentRaycastFilterBaseHeaderMETA()
#وصف_ڪريو impl_XR_LIST_ALL_ٻار_STRUCTURE_TYPES_Xr_Environment_Raycast_Filter_بنياد_سرو_META_CORE(_avail, _unavail) \
    _avail(Xr_Environment_Raycast_Filter_مفاصلو_META, XR_TYPE_ENVIRONMENT_RAYCAST_FILTER_مفاصلو_META) \





/// Like XR_LIST_ALL_STRUCTURE_TYPES, but only includes types whose parent struct type is XrSpatialCapabilityConfigurationBaseHeaderEXT
#وصف_ڪريو XR_LIST_ALL_ٻار_STRUCTURE_TYPES_Xr_Spatial_Capability_Configuration_بنياد_سرو_EXT(_avail, _unavail) \
    impl_XR_LIST_ALL_ٻار_STRUCTURE_TYPES_Xr_Spatial_Capability_Configuration_بنياد_سرو_EXT_CORE(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrSpatialCapabilityConfigurationBaseHeaderEXT()
#وصف_ڪريو impl_XR_LIST_ALL_ٻار_STRUCTURE_TYPES_Xr_Spatial_Capability_Configuration_بنياد_سرو_EXT_CORE(_avail, _unavail) \
    _avail(XrSpatialCapabilityConfigurationPlaneTrackingEXT, XR_TYPE_SPATIAL_CAPABILITY_CONFIGURATION_PLANE_TRACKING_EXT) \
    _avail(Xr_Spatial_Capability_Configuration_Qr_ڪوڊ_EXT, XR_TYPE_SPATIAL_CAPABILITY_CONFIGURATION_QR_ڪوڊ_EXT) \
    _avail(Xr_Spatial_Capability_Configuration_Micro_Qr_ڪوڊ_EXT, XR_TYPE_SPATIAL_CAPABILITY_CONFIGURATION_MICRO_QR_ڪوڊ_EXT) \
    _avail(XrSpatialCapabilityConfigurationArucoMarkerEXT, XR_TYPE_SPATIAL_CAPABILITY_CONFIGURATION_ARUCO_MARKER_EXT) \
    _avail(Xr_Spatial_Capability_Configuration_April_ٽيگ_EXT, XR_TYPE_SPATIAL_CAPABILITY_CONFIGURATION_APRIL_ٽيگ_EXT) \
    _avail(XrSpatialCapabilityConfigurationObjectTrackingEXT, XR_TYPE_SPATIAL_CAPABILITY_CONFIGURATION_OBJECT_TRACKING_EXT) \
    _avail(XrSpatialCapabilityConfigurationAnchorEXT, XR_TYPE_SPATIAL_CAPABILITY_CONFIGURATION_ANCHOR_EXT) \
    _avail(XrSpatialCapabilityConfigurationImageTrackingEXT, XR_TYPE_SPATIAL_CAPABILITY_CONFIGURATION_IMAGE_TRACKING_EXT) \
    _avail(XrSpatialCapabilityConfigurationMeshTrackingEXT, XR_TYPE_SPATIAL_CAPABILITY_CONFIGURATION_MESH_TRACKING_EXT) \
    _avail(XrSpatialCapabilityConfigurationObjectTrackingANDROID, XR_TYPE_SPATIAL_CAPABILITY_CONFIGURATION_OBJECT_TRACKING_ANDROID) \
    _avail(Xr_Spatial_Capability_Configuration_اونهائي_Raycast_ANDROID, XR_TYPE_SPATIAL_CAPABILITY_CONFIGURATION_اونهائي_RAYCAST_ANDROID) \





/// Like XR_LIST_ALL_STRUCTURE_TYPES, but only includes types whose parent struct type is XrCameraPropertyBaseHeaderBD
#وصف_ڪريو XR_LIST_ALL_ٻار_STRUCTURE_TYPES_Xr_Camera_Property_بنياد_سرو_BD(_avail, _unavail) \
    impl_XR_LIST_ALL_ٻار_STRUCTURE_TYPES_Xr_Camera_Property_بنياد_سرو_BD_CORE(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrCameraPropertyBaseHeaderBD()
#وصف_ڪريو impl_XR_LIST_ALL_ٻار_STRUCTURE_TYPES_Xr_Camera_Property_بنياد_سرو_BD_CORE(_avail, _unavail) \
    _avail(XrCameraPropertyFacingBD, XR_TYPE_CAMERA_PROPERTY_FACING_BD) \
    _avail(XrCameraPropertyPositionBD, XR_TYPE_CAMERA_PROPERTY_POSITION_BD) \
    _avail(XrCameraPropertyCameraTypeBD, XR_TYPE_CAMERA_PROPERTY_CAMERA_TYPE_BD) \





/// Like XR_LIST_ALL_STRUCTURE_TYPES, but only includes types whose parent struct type is XrCameraSupportedCapabilityBaseHeaderBD
#وصف_ڪريو XR_LIST_ALL_ٻار_STRUCTURE_TYPES_Xr_Camera_Supported_Capability_بنياد_سرو_BD(_avail, _unavail) \
    impl_XR_LIST_ALL_ٻار_STRUCTURE_TYPES_Xr_Camera_Supported_Capability_بنياد_سرو_BD_CORE(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrCameraSupportedCapabilityBaseHeaderBD()
#وصف_ڪريو impl_XR_LIST_ALL_ٻار_STRUCTURE_TYPES_Xr_Camera_Supported_Capability_بنياد_سرو_BD_CORE(_avail, _unavail) \
    _avail(Xr_Camera_Supported_Capability_Image_Resolution_And_چوکٺو_شرح_BD, XR_TYPE_CAMERA_SUPPORTED_CAPABILITY_IMAGE_RESOLUTION_AND_چوکٺو_شرح_BD) \
    _avail(Xr_Camera_Supported_Capability_معلومات_Transfer_Type_BD, XR_TYPE_CAMERA_SUPPORTED_CAPABILITY_معلومات_TRANSFER_TYPE_BD) \
    _avail(XrCameraSupportedCapabilityImageFormatBD, XR_TYPE_CAMERA_SUPPORTED_CAPABILITY_IMAGE_FORMAT_BD) \
    _avail(XrCameraSupportedCapabilityCameraModelBD, XR_TYPE_CAMERA_SUPPORTED_CAPABILITY_CAMERA_MODEL_BD) \





/// Like XR_LIST_ALL_STRUCTURE_TYPES, but only includes types whose parent struct type is XrCameraCapabilityBaseHeaderBD
#وصف_ڪريو XR_LIST_ALL_ٻار_STRUCTURE_TYPES_Xr_Camera_Capability_بنياد_سرو_BD(_avail, _unavail) \
    impl_XR_LIST_ALL_ٻار_STRUCTURE_TYPES_Xr_Camera_Capability_بنياد_سرو_BD_CORE(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrCameraCapabilityBaseHeaderBD()
#وصف_ڪريو impl_XR_LIST_ALL_ٻار_STRUCTURE_TYPES_Xr_Camera_Capability_بنياد_سرو_BD_CORE(_avail, _unavail) \
    _avail(Xr_Camera_Capability_Image_Resolution_And_چوکٺو_شرح_BD, XR_TYPE_CAMERA_CAPABILITY_IMAGE_RESOLUTION_AND_چوکٺو_شرح_BD) \
    _avail(Xr_Camera_Capability_معلومات_Transfer_Type_BD, XR_TYPE_CAMERA_CAPABILITY_معلومات_TRANSFER_TYPE_BD) \
    _avail(XrCameraCapabilityImageFormatBD, XR_TYPE_CAMERA_CAPABILITY_IMAGE_FORMAT_BD) \
    _avail(XrCameraCapabilityCameraModelBD, XR_TYPE_CAMERA_CAPABILITY_CAMERA_MODEL_BD) \





/// Like XR_LIST_ALL_STRUCTURE_TYPES, but only includes types whose parent struct type is XrCameraImageDataBaseHeaderBD
#وصف_ڪريو XR_LIST_ALL_ٻار_STRUCTURE_TYPES_Xr_Camera_Image_معلومات_بنياد_سرو_BD(_avail, _unavail) \
    impl_XR_LIST_ALL_ٻار_STRUCTURE_TYPES_Xr_Camera_Image_معلومات_بنياد_سرو_BD_CORE(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrCameraImageDataBaseHeaderBD()
#وصف_ڪريو impl_XR_LIST_ALL_ٻار_STRUCTURE_TYPES_Xr_Camera_Image_معلومات_بنياد_سرو_BD_CORE(_avail, _unavail) \
    _avail(Xr_Camera_Image_معلومات_Raw_بفر_BD, XR_TYPE_CAMERA_IMAGE_معلومات_RAW_بفر_BD) \





/// Like XR_LIST_ALL_STRUCTURE_TYPES, but only includes types whose parent struct type is XrGoogleCloudAuthInfoBaseHeaderANDROID
#وصف_ڪريو XR_LIST_ALL_ٻار_STRUCTURE_TYPES_Xr_Google_Cloud_Auth_Info_بنياد_سرو_ANDROID(_avail, _unavail) \
    impl_XR_LIST_ALL_ٻار_STRUCTURE_TYPES_Xr_Google_Cloud_Auth_Info_بنياد_سرو_ANDROID_CORE(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrGoogleCloudAuthInfoBaseHeaderANDROID()
#وصف_ڪريو impl_XR_LIST_ALL_ٻار_STRUCTURE_TYPES_Xr_Google_Cloud_Auth_Info_بنياد_سرو_ANDROID_CORE(_avail, _unavail) \
    _avail(Xr_Google_Cloud_Auth_Info_Api_ڪنجي_ANDROID, XR_TYPE_GOOGLE_CLOUD_AUTH_INFO_API_ڪنجي_ANDROID) \
    _avail(XrGoogleCloudAuthInfoTokenANDROID, XR_TYPE_GOOGLE_CLOUD_AUTH_INFO_TOKEN_ANDROID) \
    _avail(XrGoogleCloudAuthInfoKeylessANDROID, XR_TYPE_GOOGLE_CLOUD_AUTH_INFO_KEYLESS_ANDROID) \





#جيڪڏهن_پورو

