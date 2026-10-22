#اگر_غیر_تعریف_شدہ OPENXR_REFLECTION_والد_STRUCTS_H
#تعریف_کرو OPENXR_REFLECTION_والد_STRUCTS_H 1

/*
** Copyright (c) 2017-2026 The Khronos Group Inc.
**
** SPDX-License-Identifier: Apache-2.0 OR MIT
*/

/*
** This header is generated from the Khronos OpenXR XML API Registry.
**
*/

#شامل "openxr.h"

/*
This file contains expansion macros (X Macros) for OpenXR structures that have a parent type.
*/


/// Like XR_LIST_ALL_STRUCTURE_TYPES, but only includes types whose parent struct type is XrCompositionLayerBaseHeader
#تعریف_کرو XR_LIST_ALL_بچہ_STRUCTURE_TYPES_Xr_Composition_Layer_بنیاد_سرخی(_avail, _unavail) \
    impl_XR_LIST_ALL_بچہ_STRUCTURE_TYPES_Xr_Composition_Layer_بنیاد_سرخی_CORE(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrCompositionLayerBaseHeader()
#تعریف_کرو impl_XR_LIST_ALL_بچہ_STRUCTURE_TYPES_Xr_Composition_Layer_بنیاد_سرخی_CORE(_avail, _unavail) \
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
#تعریف_کرو XR_LIST_ALL_بچہ_STRUCTURE_TYPES_Xr_Event_ڈیٹا_بنیاد_سرخی(_avail, _unavail) \
    impl_XR_LIST_ALL_بچہ_STRUCTURE_TYPES_Xr_Event_ڈیٹا_بنیاد_سرخی_CORE(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrEventDataBaseHeader()
#تعریف_کرو impl_XR_LIST_ALL_بچہ_STRUCTURE_TYPES_Xr_Event_ڈیٹا_بنیاد_سرخی_CORE(_avail, _unavail) \
    _avail(Xr_Event_ڈیٹا_Events_گمشدہ, XR_TYPE_EVENT_ڈیٹا_EVENTS_گمشدہ) \
    _avail(Xr_Event_ڈیٹا_Instance_Loss_Pending, XR_TYPE_EVENT_ڈیٹا_INSTANCE_LOSS_PENDING) \
    _avail(Xr_Event_ڈیٹا_Session_State_بدلا, XR_TYPE_EVENT_ڈیٹا_SESSION_STATE_بدلا) \
    _avail(Xr_Event_ڈیٹا_Reference_Space_Change_Pending, XR_TYPE_EVENT_ڈیٹا_REFERENCE_SPACE_CHANGE_PENDING) \
    _avail(Xr_Event_ڈیٹا_Interaction_Profile_بدلا, XR_TYPE_EVENT_ڈیٹا_INTERACTION_PROFILE_بدلا) \
    _avail(Xr_Event_ڈیٹا_Visibility_نقاب_بدلا_KHR, XR_TYPE_EVENT_ڈیٹا_VISIBILITY_نقاب_بدلا_KHR) \
    _avail(Xr_Event_ڈیٹا_Perf_Settings_EXT, XR_TYPE_EVENT_ڈیٹا_PERF_SETTINGS_EXT) \
    _avail(Xr_Event_ڈیٹا_Main_Session_Visibility_بدلا_EXTX, XR_TYPE_EVENT_ڈیٹا_MAIN_SESSION_VISIBILITY_بدلا_EXTX) \
    _avail(Xr_Event_ڈیٹا_Display_Refresh_شرح_بدلا_FB, XR_TYPE_EVENT_ڈیٹا_DISPLAY_REFRESH_شرح_بدلا_FB) \
    _avail(Xr_Event_ڈیٹا_Vive_Tracker_Connected_HTCX, XR_TYPE_EVENT_ڈیٹا_VIVE_TRACKER_CONNECTED_HTCX) \
    _avail(Xr_Event_ڈیٹا_Spatial_Anchor_Create_Complete_FB, XR_TYPE_EVENT_ڈیٹا_SPATIAL_ANCHOR_CREATE_COMPLETE_FB) \
    _avail(Xr_Event_ڈیٹا_Space_سیٹ_حالت_Complete_FB, XR_TYPE_EVENT_ڈیٹا_SPACE_سیٹ_حالت_COMPLETE_FB) \
    _avail(Xr_Event_ڈیٹا_Passthrough_State_بدلا_FB, XR_TYPE_EVENT_ڈیٹا_PASSTHROUGH_STATE_بدلا_FB) \
    _avail(Xr_Event_ڈیٹا_Marker_Tracking_Update_VARJO, XR_TYPE_EVENT_ڈیٹا_MARKER_TRACKING_UPDATE_VARJO) \
    _avail(Xr_Event_ڈیٹا_Localization_بدلا_ML, XR_TYPE_EVENT_ڈیٹا_LOCALIZATION_بدلا_ML) \
    _avail(Xr_Event_ڈیٹا_Space_Query_Results_دستیاب_FB, XR_TYPE_EVENT_ڈیٹا_SPACE_QUERY_RESULTS_دستیاب_FB) \
    _avail(Xr_Event_ڈیٹا_Space_Query_Complete_FB, XR_TYPE_EVENT_ڈیٹا_SPACE_QUERY_COMPLETE_FB) \
    _avail(Xr_Event_ڈیٹا_Space_Save_Complete_FB, XR_TYPE_EVENT_ڈیٹا_SPACE_SAVE_COMPLETE_FB) \
    _avail(Xr_Event_ڈیٹا_Space_Erase_Complete_FB, XR_TYPE_EVENT_ڈیٹا_SPACE_ERASE_COMPLETE_FB) \
    _avail(Xr_Event_ڈیٹا_Space_Share_Complete_FB, XR_TYPE_EVENT_ڈیٹا_SPACE_SHARE_COMPLETE_FB) \
    _avail(Xr_Event_ڈیٹا_Scene_Capture_Complete_FB, XR_TYPE_EVENT_ڈیٹا_SCENE_CAPTURE_COMPLETE_FB) \
    _avail(Xr_Event_ڈیٹا_Virtual_Keyboard_Commit_متن_META, XR_TYPE_EVENT_ڈیٹا_VIRTUAL_KEYBOARD_COMMIT_متن_META) \
    _avail(Xr_Event_ڈیٹا_Virtual_Keyboard_Backspace_META, XR_TYPE_EVENT_ڈیٹا_VIRTUAL_KEYBOARD_BACKSPACE_META) \
    _avail(Xr_Event_ڈیٹا_Virtual_Keyboard_Enter_META, XR_TYPE_EVENT_ڈیٹا_VIRTUAL_KEYBOARD_ENTER_META) \
    _avail(Xr_Event_ڈیٹا_Virtual_Keyboard_Shown_META, XR_TYPE_EVENT_ڈیٹا_VIRTUAL_KEYBOARD_SHOWN_META) \
    _avail(Xr_Event_ڈیٹا_Virtual_Keyboard_Hidden_META, XR_TYPE_EVENT_ڈیٹا_VIRTUAL_KEYBOARD_HIDDEN_META) \
    _avail(Xr_Event_ڈیٹا_Space_List_Save_Complete_FB, XR_TYPE_EVENT_ڈیٹا_SPACE_LIST_SAVE_COMPLETE_FB) \
    _avail(Xr_Event_ڈیٹا_Space_Discovery_Results_دستیاب_META, XR_TYPE_EVENT_ڈیٹا_SPACE_DISCOVERY_RESULTS_دستیاب_META) \
    _avail(Xr_Event_ڈیٹا_Space_Discovery_Complete_META, XR_TYPE_EVENT_ڈیٹا_SPACE_DISCOVERY_COMPLETE_META) \
    _avail(Xr_Event_ڈیٹا_Spaces_Save_نتیجہ_META, XR_TYPE_EVENT_ڈیٹا_SPACES_SAVE_نتیجہ_META) \
    _avail(Xr_Event_ڈیٹا_Spaces_Erase_نتیجہ_META, XR_TYPE_EVENT_ڈیٹا_SPACES_ERASE_نتیجہ_META) \
    _avail(Xr_Event_ڈیٹا_Passthrough_Layer_Resumed_META, XR_TYPE_EVENT_ڈیٹا_PASSTHROUGH_LAYER_RESUMED_META) \
    _avail(Xr_Event_ڈیٹا_Share_Spaces_Complete_META, XR_TYPE_EVENT_ڈیٹا_SHARE_SPACES_COMPLETE_META) \
    _avail(Xr_Event_ڈیٹا_Interaction_Render_Models_بدلا_EXT, XR_TYPE_EVENT_ڈیٹا_INTERACTION_RENDER_MODELS_بدلا_EXT) \
    _avail(Xr_Event_ڈیٹا_Sense_ڈیٹا_Provider_State_بدلا_BD, XR_TYPE_EVENT_ڈیٹا_SENSE_ڈیٹا_PROVIDER_STATE_بدلا_BD) \
    _avail(Xr_Event_ڈیٹا_Sense_ڈیٹا_Updated_BD, XR_TYPE_EVENT_ڈیٹا_SENSE_ڈیٹا_UPDATED_BD) \
    _avail(Xr_Event_ڈیٹا_Recommended_Resolution_بدلا_ANDROID, XR_TYPE_EVENT_ڈیٹا_RECOMMENDED_RESOLUTION_بدلا_ANDROID) \
    _avail(Xr_Event_ڈیٹا_User_Presence_بدلا_EXT, XR_TYPE_EVENT_ڈیٹا_USER_PRESENCE_بدلا_EXT) \
    _avail(Xr_Event_ڈیٹا_Headset_Fit_بدلا_ML, XR_TYPE_EVENT_ڈیٹا_HEADSET_FIT_بدلا_ML) \
    _avail(Xr_Event_ڈیٹا_Eye_Calibration_بدلا_ML, XR_TYPE_EVENT_ڈیٹا_EYE_CALIBRATION_بدلا_ML) \
    _avail(Xr_Event_ڈیٹا_Boundary_Visibility_بدلا_META, XR_TYPE_EVENT_ڈیٹا_BOUNDARY_VISIBILITY_بدلا_META) \
    _avail(Xr_Event_ڈیٹا_آغاز_Colocation_Advertisement_Complete_META, XR_TYPE_EVENT_ڈیٹا_آغاز_COLOCATION_ADVERTISEMENT_COMPLETE_META) \
    _avail(Xr_Event_ڈیٹا_Stop_Colocation_Advertisement_Complete_META, XR_TYPE_EVENT_ڈیٹا_STOP_COLOCATION_ADVERTISEMENT_COMPLETE_META) \
    _avail(Xr_Event_ڈیٹا_Colocation_Advertisement_Complete_META, XR_TYPE_EVENT_ڈیٹا_COLOCATION_ADVERTISEMENT_COMPLETE_META) \
    _avail(Xr_Event_ڈیٹا_آغاز_Colocation_Discovery_Complete_META, XR_TYPE_EVENT_ڈیٹا_آغاز_COLOCATION_DISCOVERY_COMPLETE_META) \
    _avail(Xr_Event_ڈیٹا_Colocation_Discovery_نتیجہ_META, XR_TYPE_EVENT_ڈیٹا_COLOCATION_DISCOVERY_نتیجہ_META) \
    _avail(Xr_Event_ڈیٹا_Colocation_Discovery_Complete_META, XR_TYPE_EVENT_ڈیٹا_COLOCATION_DISCOVERY_COMPLETE_META) \
    _avail(Xr_Event_ڈیٹا_Stop_Colocation_Discovery_Complete_META, XR_TYPE_EVENT_ڈیٹا_STOP_COLOCATION_DISCOVERY_COMPLETE_META) \
    _avail(Xr_Event_ڈیٹا_Image_Tracking_گمشدہ_ANDROID, XR_TYPE_EVENT_ڈیٹا_IMAGE_TRACKING_گمشدہ_ANDROID) \
    _avail(Xr_Event_ڈیٹا_Spatial_Discovery_Recommended_EXT, XR_TYPE_EVENT_ڈیٹا_SPATIAL_DISCOVERY_RECOMMENDED_EXT) \
    _avail(Xr_Event_ڈیٹا_Geospatial_Tracker_State_بدلا_ANDROID, XR_TYPE_EVENT_ڈیٹا_GEOSPATIAL_TRACKER_STATE_بدلا_ANDROID) \
    _avail(Xr_Event_ڈیٹا_Spatial_Container_Closed_EXT, XR_TYPE_EVENT_ڈیٹا_SPATIAL_CONTAINER_CLOSED_EXT) \
    _avail(Xr_Event_ڈیٹا_Spatial_Container_Bounds_بدلا_EXT, XR_TYPE_EVENT_ڈیٹا_SPATIAL_CONTAINER_BOUNDS_بدلا_EXT) \
    _avail(Xr_Event_ڈیٹا_Spatial_Container_Visible_بدلا_EXT, XR_TYPE_EVENT_ڈیٹا_SPATIAL_CONTAINER_VISIBLE_بدلا_EXT) \
    _avail(Xr_Event_ڈیٹا_Spatial_Container_Visible_Request_Denied_EXT, XR_TYPE_EVENT_ڈیٹا_SPATIAL_CONTAINER_VISIBLE_REQUEST_DENIED_EXT) \
    _avail(Xr_Event_ڈیٹا_Spatial_Container_Interactable_بدلا_EXT, XR_TYPE_EVENT_ڈیٹا_SPATIAL_CONTAINER_INTERACTABLE_بدلا_EXT) \
    _avail(Xr_Event_ڈیٹا_Spatial_Container_Bounds_منوال_Request_Denied_EXT, XR_TYPE_EVENT_ڈیٹا_SPATIAL_CONTAINER_BOUNDS_منوال_REQUEST_DENIED_EXT) \
    _avail(Xr_Event_ڈیٹا_View_Configuration_Views_بدلا_EXT, XR_TYPE_EVENT_ڈیٹا_VIEW_CONFIGURATION_VIEWS_بدلا_EXT) \





/// Like XR_LIST_ALL_STRUCTURE_TYPES, but only includes types whose parent struct type is XrHapticBaseHeader
#تعریف_کرو XR_LIST_ALL_بچہ_STRUCTURE_TYPES_Xr_Haptic_بنیاد_سرخی(_avail, _unavail) \
    impl_XR_LIST_ALL_بچہ_STRUCTURE_TYPES_Xr_Haptic_بنیاد_سرخی_CORE(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrHapticBaseHeader()
#تعریف_کرو impl_XR_LIST_ALL_بچہ_STRUCTURE_TYPES_Xr_Haptic_بنیاد_سرخی_CORE(_avail, _unavail) \
    _avail(XrHapticVibration, XR_TYPE_HAPTIC_VIBRATION) \
    _avail(XrHapticAmplitudeEnvelopeVibrationFB, XR_TYPE_HAPTIC_AMPLITUDE_ENVELOPE_VIBRATION_FB) \
    _avail(XrHapticPcmVibrationFB, XR_TYPE_HAPTIC_PCM_VIBRATION_FB) \
    _avail(XrHapticParametricVibrationEXT, XR_TYPE_HAPTIC_PARAMETRIC_VIBRATION_EXT) \





/// Like XR_LIST_ALL_STRUCTURE_TYPES, but only includes types whose parent struct type is XrSwapchainImageBaseHeader
#تعریف_کرو XR_LIST_ALL_بچہ_STRUCTURE_TYPES_Xr_Swapchain_Image_بنیاد_سرخی(_avail, _unavail) \
    impl_XR_LIST_ALL_بچہ_STRUCTURE_TYPES_Xr_Swapchain_Image_بنیاد_سرخی_CORE(_avail, _unavail) \
    impl_XR_LIST_ALL_بچہ_STRUCTURE_TYPES_Xr_Swapchain_Image_بنیاد_سرخی_XR_USE_GRAPHICS_API_D3_D11(_avail, _unavail) \
    impl_XR_LIST_ALL_بچہ_STRUCTURE_TYPES_Xr_Swapchain_Image_بنیاد_سرخی_XR_USE_GRAPHICS_API_D3_D12(_avail, _unavail) \
    impl_XR_LIST_ALL_بچہ_STRUCTURE_TYPES_Xr_Swapchain_Image_بنیاد_سرخی_XR_USE_GRAPHICS_API_METAL(_avail, _unavail) \
    impl_XR_LIST_ALL_بچہ_STRUCTURE_TYPES_Xr_Swapchain_Image_بنیاد_سرخی_XR_USE_GRAPHICS_API_OPENGL(_avail, _unavail) \
    impl_XR_LIST_ALL_بچہ_STRUCTURE_TYPES_Xr_Swapchain_Image_بنیاد_سرخی_XR_USE_GRAPHICS_API_OPENGL_ES(_avail, _unavail) \
    impl_XR_LIST_ALL_بچہ_STRUCTURE_TYPES_Xr_Swapchain_Image_بنیاد_سرخی_XR_USE_GRAPHICS_API_VULKAN(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrSwapchainImageBaseHeader()
#تعریف_کرو impl_XR_LIST_ALL_بچہ_STRUCTURE_TYPES_Xr_Swapchain_Image_بنیاد_سرخی_CORE(_avail, _unavail) \


#اگر defined(XR_USE_GRAPHICS_API_D3D11)
#تعریف_کرو impl_XR_LIST_ALL_بچہ_STRUCTURE_TYPES_Xr_Swapchain_Image_بنیاد_سرخی_XR_USE_GRAPHICS_API_D3_D11(_avail, _unavail) \
    _avail(XrSwapchainImageD3D11KHR, XR_TYPE_SWAPCHAIN_IMAGE_D3D11_KHR) \

#ورنہ
#تعریف_کرو impl_XR_LIST_ALL_بچہ_STRUCTURE_TYPES_Xr_Swapchain_Image_بنیاد_سرخی_XR_USE_GRAPHICS_API_D3_D11(_avail, _unavail) \
    _unavail(XrSwapchainImageD3D11KHR, XR_TYPE_SWAPCHAIN_IMAGE_D3D11_KHR) \

#اگر_ختم

#اگر defined(XR_USE_GRAPHICS_API_D3D12)
#تعریف_کرو impl_XR_LIST_ALL_بچہ_STRUCTURE_TYPES_Xr_Swapchain_Image_بنیاد_سرخی_XR_USE_GRAPHICS_API_D3_D12(_avail, _unavail) \
    _avail(XrSwapchainImageD3D12KHR, XR_TYPE_SWAPCHAIN_IMAGE_D3D12_KHR) \

#ورنہ
#تعریف_کرو impl_XR_LIST_ALL_بچہ_STRUCTURE_TYPES_Xr_Swapchain_Image_بنیاد_سرخی_XR_USE_GRAPHICS_API_D3_D12(_avail, _unavail) \
    _unavail(XrSwapchainImageD3D12KHR, XR_TYPE_SWAPCHAIN_IMAGE_D3D12_KHR) \

#اگر_ختم

#اگر defined(XR_USE_GRAPHICS_API_METAL)
#تعریف_کرو impl_XR_LIST_ALL_بچہ_STRUCTURE_TYPES_Xr_Swapchain_Image_بنیاد_سرخی_XR_USE_GRAPHICS_API_METAL(_avail, _unavail) \
    _avail(XrSwapchainImageMetalKHR, XR_TYPE_SWAPCHAIN_IMAGE_METAL_KHR) \

#ورنہ
#تعریف_کرو impl_XR_LIST_ALL_بچہ_STRUCTURE_TYPES_Xr_Swapchain_Image_بنیاد_سرخی_XR_USE_GRAPHICS_API_METAL(_avail, _unavail) \
    _unavail(XrSwapchainImageMetalKHR, XR_TYPE_SWAPCHAIN_IMAGE_METAL_KHR) \

#اگر_ختم

#اگر defined(XR_USE_GRAPHICS_API_OPENGL)
#تعریف_کرو impl_XR_LIST_ALL_بچہ_STRUCTURE_TYPES_Xr_Swapchain_Image_بنیاد_سرخی_XR_USE_GRAPHICS_API_OPENGL(_avail, _unavail) \
    _avail(XrSwapchainImageOpenGLKHR, XR_TYPE_SWAPCHAIN_IMAGE_OPENGL_KHR) \

#ورنہ
#تعریف_کرو impl_XR_LIST_ALL_بچہ_STRUCTURE_TYPES_Xr_Swapchain_Image_بنیاد_سرخی_XR_USE_GRAPHICS_API_OPENGL(_avail, _unavail) \
    _unavail(XrSwapchainImageOpenGLKHR, XR_TYPE_SWAPCHAIN_IMAGE_OPENGL_KHR) \

#اگر_ختم

#اگر defined(XR_USE_GRAPHICS_API_OPENGL_ES)
#تعریف_کرو impl_XR_LIST_ALL_بچہ_STRUCTURE_TYPES_Xr_Swapchain_Image_بنیاد_سرخی_XR_USE_GRAPHICS_API_OPENGL_ES(_avail, _unavail) \
    _avail(XrSwapchainImageOpenGLESKHR, XR_TYPE_SWAPCHAIN_IMAGE_OPENGL_ES_KHR) \

#ورنہ
#تعریف_کرو impl_XR_LIST_ALL_بچہ_STRUCTURE_TYPES_Xr_Swapchain_Image_بنیاد_سرخی_XR_USE_GRAPHICS_API_OPENGL_ES(_avail, _unavail) \
    _unavail(XrSwapchainImageOpenGLESKHR, XR_TYPE_SWAPCHAIN_IMAGE_OPENGL_ES_KHR) \

#اگر_ختم

#اگر defined(XR_USE_GRAPHICS_API_VULKAN)
#تعریف_کرو impl_XR_LIST_ALL_بچہ_STRUCTURE_TYPES_Xr_Swapchain_Image_بنیاد_سرخی_XR_USE_GRAPHICS_API_VULKAN(_avail, _unavail) \
    _avail(XrSwapchainImageVulkanKHR, XR_TYPE_SWAPCHAIN_IMAGE_VULKAN_KHR) \

#ورنہ
#تعریف_کرو impl_XR_LIST_ALL_بچہ_STRUCTURE_TYPES_Xr_Swapchain_Image_بنیاد_سرخی_XR_USE_GRAPHICS_API_VULKAN(_avail, _unavail) \
    _unavail(XrSwapchainImageVulkanKHR, XR_TYPE_SWAPCHAIN_IMAGE_VULKAN_KHR) \

#اگر_ختم




/// Like XR_LIST_ALL_STRUCTURE_TYPES, but only includes types whose parent struct type is XrLoaderInitInfoBaseHeaderKHR
#تعریف_کرو XR_LIST_ALL_بچہ_STRUCTURE_TYPES_Xr_Loader_Init_Info_بنیاد_سرخی_KHR(_avail, _unavail) \
    impl_XR_LIST_ALL_بچہ_STRUCTURE_TYPES_Xr_Loader_Init_Info_بنیاد_سرخی_KHR_CORE(_avail, _unavail) \
    impl_XR_LIST_ALL_بچہ_STRUCTURE_TYPES_Xr_Loader_Init_Info_بنیاد_سرخی_KHR_XR_USE_PLATFORM_ANDROID(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrLoaderInitInfoBaseHeaderKHR()
#تعریف_کرو impl_XR_LIST_ALL_بچہ_STRUCTURE_TYPES_Xr_Loader_Init_Info_بنیاد_سرخی_KHR_CORE(_avail, _unavail) \
    _avail(XrLoaderInitInfoPropertiesEXT, XR_TYPE_LOADER_INIT_INFO_PROPERTIES_EXT) \


#اگر defined(XR_USE_PLATFORM_ANDROID)
#تعریف_کرو impl_XR_LIST_ALL_بچہ_STRUCTURE_TYPES_Xr_Loader_Init_Info_بنیاد_سرخی_KHR_XR_USE_PLATFORM_ANDROID(_avail, _unavail) \
    _avail(XrLoaderInitInfoAndroidKHR, XR_TYPE_LOADER_INIT_INFO_ANDROID_KHR) \

#ورنہ
#تعریف_کرو impl_XR_LIST_ALL_بچہ_STRUCTURE_TYPES_Xr_Loader_Init_Info_بنیاد_سرخی_KHR_XR_USE_PLATFORM_ANDROID(_avail, _unavail) \
    _unavail(XrLoaderInitInfoAndroidKHR, XR_TYPE_LOADER_INIT_INFO_ANDROID_KHR) \

#اگر_ختم




/// Like XR_LIST_ALL_STRUCTURE_TYPES, but only includes types whose parent struct type is XrBindingModificationBaseHeaderKHR
#تعریف_کرو XR_LIST_ALL_بچہ_STRUCTURE_TYPES_Xr_Binding_Modification_بنیاد_سرخی_KHR(_avail, _unavail) \
    impl_XR_LIST_ALL_بچہ_STRUCTURE_TYPES_Xr_Binding_Modification_بنیاد_سرخی_KHR_CORE(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrBindingModificationBaseHeaderKHR()
#تعریف_کرو impl_XR_LIST_ALL_بچہ_STRUCTURE_TYPES_Xr_Binding_Modification_بنیاد_سرخی_KHR_CORE(_avail, _unavail) \
    _avail(XrInteractionProfileDpadBindingEXT, XR_TYPE_INTERACTION_PROFILE_DPAD_BINDING_EXT) \
    _avail(Xr_Interaction_Profile_Analog_حد_VALVE, XR_TYPE_INTERACTION_PROFILE_ANALOG_حد_VALVE) \





/// Like XR_LIST_ALL_STRUCTURE_TYPES, but only includes types whose parent struct type is XrSwapchainStateBaseHeaderFB
#تعریف_کرو XR_LIST_ALL_بچہ_STRUCTURE_TYPES_Xr_Swapchain_State_بنیاد_سرخی_FB(_avail, _unavail) \
    impl_XR_LIST_ALL_بچہ_STRUCTURE_TYPES_Xr_Swapchain_State_بنیاد_سرخی_FB_CORE(_avail, _unavail) \
    impl_XR_LIST_ALL_بچہ_STRUCTURE_TYPES_Xr_Swapchain_State_بنیاد_سرخی_FB_XR_USE_GRAPHICS_API_OPENGL_ES(_avail, _unavail) \
    impl_XR_LIST_ALL_بچہ_STRUCTURE_TYPES_Xr_Swapchain_State_بنیاد_سرخی_FB_XR_USE_GRAPHICS_API_VULKAN(_avail, _unavail) \
    impl_XR_LIST_ALL_بچہ_STRUCTURE_TYPES_Xr_Swapchain_State_بنیاد_سرخی_FB_XR_USE_PLATFORM_ANDROID(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrSwapchainStateBaseHeaderFB()
#تعریف_کرو impl_XR_LIST_ALL_بچہ_STRUCTURE_TYPES_Xr_Swapchain_State_بنیاد_سرخی_FB_CORE(_avail, _unavail) \
    _avail(XrSwapchainStateFoveationFB, XR_TYPE_SWAPCHAIN_STATE_FOVEATION_FB) \


#اگر defined(XR_USE_GRAPHICS_API_OPENGL_ES)
#تعریف_کرو impl_XR_LIST_ALL_بچہ_STRUCTURE_TYPES_Xr_Swapchain_State_بنیاد_سرخی_FB_XR_USE_GRAPHICS_API_OPENGL_ES(_avail, _unavail) \
    _avail(XrSwapchainStateSamplerOpenGLESFB, XR_TYPE_SWAPCHAIN_STATE_SAMPLER_OPENGL_ES_FB) \

#ورنہ
#تعریف_کرو impl_XR_LIST_ALL_بچہ_STRUCTURE_TYPES_Xr_Swapchain_State_بنیاد_سرخی_FB_XR_USE_GRAPHICS_API_OPENGL_ES(_avail, _unavail) \
    _unavail(XrSwapchainStateSamplerOpenGLESFB, XR_TYPE_SWAPCHAIN_STATE_SAMPLER_OPENGL_ES_FB) \

#اگر_ختم

#اگر defined(XR_USE_GRAPHICS_API_VULKAN)
#تعریف_کرو impl_XR_LIST_ALL_بچہ_STRUCTURE_TYPES_Xr_Swapchain_State_بنیاد_سرخی_FB_XR_USE_GRAPHICS_API_VULKAN(_avail, _unavail) \
    _avail(XrSwapchainStateSamplerVulkanFB, XR_TYPE_SWAPCHAIN_STATE_SAMPLER_VULKAN_FB) \

#ورنہ
#تعریف_کرو impl_XR_LIST_ALL_بچہ_STRUCTURE_TYPES_Xr_Swapchain_State_بنیاد_سرخی_FB_XR_USE_GRAPHICS_API_VULKAN(_avail, _unavail) \
    _unavail(XrSwapchainStateSamplerVulkanFB, XR_TYPE_SWAPCHAIN_STATE_SAMPLER_VULKAN_FB) \

#اگر_ختم

#اگر defined(XR_USE_PLATFORM_ANDROID)
#تعریف_کرو impl_XR_LIST_ALL_بچہ_STRUCTURE_TYPES_Xr_Swapchain_State_بنیاد_سرخی_FB_XR_USE_PLATFORM_ANDROID(_avail, _unavail) \
    _avail(XrSwapchainStateAndroidSurfaceDimensionsFB, XR_TYPE_SWAPCHAIN_STATE_ANDROID_SURFACE_DIMENSIONS_FB) \

#ورنہ
#تعریف_کرو impl_XR_LIST_ALL_بچہ_STRUCTURE_TYPES_Xr_Swapchain_State_بنیاد_سرخی_FB_XR_USE_PLATFORM_ANDROID(_avail, _unavail) \
    _unavail(XrSwapchainStateAndroidSurfaceDimensionsFB, XR_TYPE_SWAPCHAIN_STATE_ANDROID_SURFACE_DIMENSIONS_FB) \

#اگر_ختم




/// Like XR_LIST_ALL_STRUCTURE_TYPES, but only includes types whose parent struct type is XrSpatialAnchorsCreateInfoBaseHeaderML
#تعریف_کرو XR_LIST_ALL_بچہ_STRUCTURE_TYPES_Xr_Spatial_Anchors_Create_Info_بنیاد_سرخی_ML(_avail, _unavail) \
    impl_XR_LIST_ALL_بچہ_STRUCTURE_TYPES_Xr_Spatial_Anchors_Create_Info_بنیاد_سرخی_ML_CORE(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrSpatialAnchorsCreateInfoBaseHeaderML()
#تعریف_کرو impl_XR_LIST_ALL_بچہ_STRUCTURE_TYPES_Xr_Spatial_Anchors_Create_Info_بنیاد_سرخی_ML_CORE(_avail, _unavail) \
    _avail(XrSpatialAnchorsCreateInfoFromPoseML, XR_TYPE_SPATIAL_ANCHORS_CREATE_INFO_FROM_POSE_ML) \
    _avail(XrSpatialAnchorsCreateInfoFromUuidsML, XR_TYPE_SPATIAL_ANCHORS_CREATE_INFO_FROM_UUIDS_ML) \





/// Like XR_LIST_ALL_STRUCTURE_TYPES, but only includes types whose parent struct type is XrFutureCompletionBaseHeaderEXT
#تعریف_کرو XR_LIST_ALL_بچہ_STRUCTURE_TYPES_Xr_Future_Completion_بنیاد_سرخی_EXT(_avail, _unavail) \
    impl_XR_LIST_ALL_بچہ_STRUCTURE_TYPES_Xr_Future_Completion_بنیاد_سرخی_EXT_CORE(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrFutureCompletionBaseHeaderEXT()
#تعریف_کرو impl_XR_LIST_ALL_بچہ_STRUCTURE_TYPES_Xr_Future_Completion_بنیاد_سرخی_EXT_CORE(_avail, _unavail) \
    _avail(XrCreateSpatialAnchorsCompletionML, XR_TYPE_CREATE_SPATIAL_ANCHORS_COMPLETION_ML) \
    _avail(XrSpatialAnchorsQueryCompletionML, XR_TYPE_SPATIAL_ANCHORS_QUERY_COMPLETION_ML) \
    _avail(XrSpatialAnchorsPublishCompletionML, XR_TYPE_SPATIAL_ANCHORS_PUBLISH_COMPLETION_ML) \
    _avail(XrSpatialAnchorsDeleteCompletionML, XR_TYPE_SPATIAL_ANCHORS_DELETE_COMPLETION_ML) \
    _avail(XrSpatialAnchorsUpdateExpirationCompletionML, XR_TYPE_SPATIAL_ANCHORS_UPDATE_EXPIRATION_COMPLETION_ML) \
    _avail(Xr_Sense_ڈیٹا_Query_Completion_BD, XR_TYPE_SENSE_ڈیٹا_QUERY_COMPLETION_BD) \
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
#تعریف_کرو XR_LIST_ALL_بچہ_STRUCTURE_TYPES_Xr_Spatial_Anchors_Query_Info_بنیاد_سرخی_ML(_avail, _unavail) \
    impl_XR_LIST_ALL_بچہ_STRUCTURE_TYPES_Xr_Spatial_Anchors_Query_Info_بنیاد_سرخی_ML_CORE(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrSpatialAnchorsQueryInfoBaseHeaderML()
#تعریف_کرو impl_XR_LIST_ALL_بچہ_STRUCTURE_TYPES_Xr_Spatial_Anchors_Query_Info_بنیاد_سرخی_ML_CORE(_avail, _unavail) \
    _avail(XrSpatialAnchorsQueryInfoRadiusML, XR_TYPE_SPATIAL_ANCHORS_QUERY_INFO_RADIUS_ML) \





/// Like XR_LIST_ALL_STRUCTURE_TYPES, but only includes types whose parent struct type is XrSpaceQueryInfoBaseHeaderFB
#تعریف_کرو XR_LIST_ALL_بچہ_STRUCTURE_TYPES_Xr_Space_Query_Info_بنیاد_سرخی_FB(_avail, _unavail) \
    impl_XR_LIST_ALL_بچہ_STRUCTURE_TYPES_Xr_Space_Query_Info_بنیاد_سرخی_FB_CORE(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrSpaceQueryInfoBaseHeaderFB()
#تعریف_کرو impl_XR_LIST_ALL_بچہ_STRUCTURE_TYPES_Xr_Space_Query_Info_بنیاد_سرخی_FB_CORE(_avail, _unavail) \
    _avail(XrSpaceQueryInfoFB, XR_TYPE_SPACE_QUERY_INFO_FB) \





/// Like XR_LIST_ALL_STRUCTURE_TYPES, but only includes types whose parent struct type is XrSpaceFilterInfoBaseHeaderFB
#تعریف_کرو XR_LIST_ALL_بچہ_STRUCTURE_TYPES_Xr_Space_Filter_Info_بنیاد_سرخی_FB(_avail, _unavail) \
    impl_XR_LIST_ALL_بچہ_STRUCTURE_TYPES_Xr_Space_Filter_Info_بنیاد_سرخی_FB_CORE(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrSpaceFilterInfoBaseHeaderFB()
#تعریف_کرو impl_XR_LIST_ALL_بچہ_STRUCTURE_TYPES_Xr_Space_Filter_Info_بنیاد_سرخی_FB_CORE(_avail, _unavail) \
    _avail(XrSpaceUuidFilterInfoFB, XR_TYPE_SPACE_UUID_FILTER_INFO_FB) \
    _avail(XrSpaceComponentFilterInfoFB, XR_TYPE_SPACE_COMPONENT_FILTER_INFO_FB) \





/// Like XR_LIST_ALL_STRUCTURE_TYPES, but only includes types whose parent struct type is XrSpaceFilterBaseHeaderMETA
#تعریف_کرو XR_LIST_ALL_بچہ_STRUCTURE_TYPES_Xr_Space_Filter_بنیاد_سرخی_META(_avail, _unavail) \
    impl_XR_LIST_ALL_بچہ_STRUCTURE_TYPES_Xr_Space_Filter_بنیاد_سرخی_META_CORE(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrSpaceFilterBaseHeaderMETA()
#تعریف_کرو impl_XR_LIST_ALL_بچہ_STRUCTURE_TYPES_Xr_Space_Filter_بنیاد_سرخی_META_CORE(_avail, _unavail) \
    _avail(XrSpaceFilterUuidMETA, XR_TYPE_SPACE_FILTER_UUID_META) \
    _avail(XrSpaceFilterComponentMETA, XR_TYPE_SPACE_FILTER_COMPONENT_META) \





/// Like XR_LIST_ALL_STRUCTURE_TYPES, but only includes types whose parent struct type is XrShareSpacesRecipientBaseHeaderMETA
#تعریف_کرو XR_LIST_ALL_بچہ_STRUCTURE_TYPES_Xr_Share_Spaces_Recipient_بنیاد_سرخی_META(_avail, _unavail) \
    impl_XR_LIST_ALL_بچہ_STRUCTURE_TYPES_Xr_Share_Spaces_Recipient_بنیاد_سرخی_META_CORE(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrShareSpacesRecipientBaseHeaderMETA()
#تعریف_کرو impl_XR_LIST_ALL_بچہ_STRUCTURE_TYPES_Xr_Share_Spaces_Recipient_بنیاد_سرخی_META_CORE(_avail, _unavail) \
    _avail(XrShareSpacesRecipientGroupsMETA, XR_TYPE_SHARE_SPACES_RECIPIENT_GROUPS_META) \





/// Like XR_LIST_ALL_STRUCTURE_TYPES, but only includes types whose parent struct type is XrEnvironmentRaycastFilterBaseHeaderMETA
#تعریف_کرو XR_LIST_ALL_بچہ_STRUCTURE_TYPES_Xr_Environment_Raycast_Filter_بنیاد_سرخی_META(_avail, _unavail) \
    impl_XR_LIST_ALL_بچہ_STRUCTURE_TYPES_Xr_Environment_Raycast_Filter_بنیاد_سرخی_META_CORE(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrEnvironmentRaycastFilterBaseHeaderMETA()
#تعریف_کرو impl_XR_LIST_ALL_بچہ_STRUCTURE_TYPES_Xr_Environment_Raycast_Filter_بنیاد_سرخی_META_CORE(_avail, _unavail) \
    _avail(Xr_Environment_Raycast_Filter_فاصلہ_META, XR_TYPE_ENVIRONMENT_RAYCAST_FILTER_فاصلہ_META) \





/// Like XR_LIST_ALL_STRUCTURE_TYPES, but only includes types whose parent struct type is XrSpatialCapabilityConfigurationBaseHeaderEXT
#تعریف_کرو XR_LIST_ALL_بچہ_STRUCTURE_TYPES_Xr_Spatial_Capability_Configuration_بنیاد_سرخی_EXT(_avail, _unavail) \
    impl_XR_LIST_ALL_بچہ_STRUCTURE_TYPES_Xr_Spatial_Capability_Configuration_بنیاد_سرخی_EXT_CORE(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrSpatialCapabilityConfigurationBaseHeaderEXT()
#تعریف_کرو impl_XR_LIST_ALL_بچہ_STRUCTURE_TYPES_Xr_Spatial_Capability_Configuration_بنیاد_سرخی_EXT_CORE(_avail, _unavail) \
    _avail(XrSpatialCapabilityConfigurationPlaneTrackingEXT, XR_TYPE_SPATIAL_CAPABILITY_CONFIGURATION_PLANE_TRACKING_EXT) \
    _avail(Xr_Spatial_Capability_Configuration_Qr_رمز_EXT, XR_TYPE_SPATIAL_CAPABILITY_CONFIGURATION_QR_رمز_EXT) \
    _avail(Xr_Spatial_Capability_Configuration_Micro_Qr_رمز_EXT, XR_TYPE_SPATIAL_CAPABILITY_CONFIGURATION_MICRO_QR_رمز_EXT) \
    _avail(XrSpatialCapabilityConfigurationArucoMarkerEXT, XR_TYPE_SPATIAL_CAPABILITY_CONFIGURATION_ARUCO_MARKER_EXT) \
    _avail(Xr_Spatial_Capability_Configuration_April_لیبل_EXT, XR_TYPE_SPATIAL_CAPABILITY_CONFIGURATION_APRIL_لیبل_EXT) \
    _avail(XrSpatialCapabilityConfigurationObjectTrackingEXT, XR_TYPE_SPATIAL_CAPABILITY_CONFIGURATION_OBJECT_TRACKING_EXT) \
    _avail(XrSpatialCapabilityConfigurationAnchorEXT, XR_TYPE_SPATIAL_CAPABILITY_CONFIGURATION_ANCHOR_EXT) \
    _avail(XrSpatialCapabilityConfigurationImageTrackingEXT, XR_TYPE_SPATIAL_CAPABILITY_CONFIGURATION_IMAGE_TRACKING_EXT) \
    _avail(XrSpatialCapabilityConfigurationMeshTrackingEXT, XR_TYPE_SPATIAL_CAPABILITY_CONFIGURATION_MESH_TRACKING_EXT) \
    _avail(XrSpatialCapabilityConfigurationObjectTrackingANDROID, XR_TYPE_SPATIAL_CAPABILITY_CONFIGURATION_OBJECT_TRACKING_ANDROID) \
    _avail(Xr_Spatial_Capability_Configuration_گہرائی_Raycast_ANDROID, XR_TYPE_SPATIAL_CAPABILITY_CONFIGURATION_گہرائی_RAYCAST_ANDROID) \





/// Like XR_LIST_ALL_STRUCTURE_TYPES, but only includes types whose parent struct type is XrCameraPropertyBaseHeaderBD
#تعریف_کرو XR_LIST_ALL_بچہ_STRUCTURE_TYPES_Xr_Camera_Property_بنیاد_سرخی_BD(_avail, _unavail) \
    impl_XR_LIST_ALL_بچہ_STRUCTURE_TYPES_Xr_Camera_Property_بنیاد_سرخی_BD_CORE(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrCameraPropertyBaseHeaderBD()
#تعریف_کرو impl_XR_LIST_ALL_بچہ_STRUCTURE_TYPES_Xr_Camera_Property_بنیاد_سرخی_BD_CORE(_avail, _unavail) \
    _avail(XrCameraPropertyFacingBD, XR_TYPE_CAMERA_PROPERTY_FACING_BD) \
    _avail(XrCameraPropertyPositionBD, XR_TYPE_CAMERA_PROPERTY_POSITION_BD) \
    _avail(XrCameraPropertyCameraTypeBD, XR_TYPE_CAMERA_PROPERTY_CAMERA_TYPE_BD) \





/// Like XR_LIST_ALL_STRUCTURE_TYPES, but only includes types whose parent struct type is XrCameraSupportedCapabilityBaseHeaderBD
#تعریف_کرو XR_LIST_ALL_بچہ_STRUCTURE_TYPES_Xr_Camera_Supported_Capability_بنیاد_سرخی_BD(_avail, _unavail) \
    impl_XR_LIST_ALL_بچہ_STRUCTURE_TYPES_Xr_Camera_Supported_Capability_بنیاد_سرخی_BD_CORE(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrCameraSupportedCapabilityBaseHeaderBD()
#تعریف_کرو impl_XR_LIST_ALL_بچہ_STRUCTURE_TYPES_Xr_Camera_Supported_Capability_بنیاد_سرخی_BD_CORE(_avail, _unavail) \
    _avail(Xr_Camera_Supported_Capability_Image_Resolution_And_چوکھٹا_شرح_BD, XR_TYPE_CAMERA_SUPPORTED_CAPABILITY_IMAGE_RESOLUTION_AND_چوکھٹا_شرح_BD) \
    _avail(Xr_Camera_Supported_Capability_ڈیٹا_Transfer_Type_BD, XR_TYPE_CAMERA_SUPPORTED_CAPABILITY_ڈیٹا_TRANSFER_TYPE_BD) \
    _avail(XrCameraSupportedCapabilityImageFormatBD, XR_TYPE_CAMERA_SUPPORTED_CAPABILITY_IMAGE_FORMAT_BD) \
    _avail(XrCameraSupportedCapabilityCameraModelBD, XR_TYPE_CAMERA_SUPPORTED_CAPABILITY_CAMERA_MODEL_BD) \





/// Like XR_LIST_ALL_STRUCTURE_TYPES, but only includes types whose parent struct type is XrCameraCapabilityBaseHeaderBD
#تعریف_کرو XR_LIST_ALL_بچہ_STRUCTURE_TYPES_Xr_Camera_Capability_بنیاد_سرخی_BD(_avail, _unavail) \
    impl_XR_LIST_ALL_بچہ_STRUCTURE_TYPES_Xr_Camera_Capability_بنیاد_سرخی_BD_CORE(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrCameraCapabilityBaseHeaderBD()
#تعریف_کرو impl_XR_LIST_ALL_بچہ_STRUCTURE_TYPES_Xr_Camera_Capability_بنیاد_سرخی_BD_CORE(_avail, _unavail) \
    _avail(Xr_Camera_Capability_Image_Resolution_And_چوکھٹا_شرح_BD, XR_TYPE_CAMERA_CAPABILITY_IMAGE_RESOLUTION_AND_چوکھٹا_شرح_BD) \
    _avail(Xr_Camera_Capability_ڈیٹا_Transfer_Type_BD, XR_TYPE_CAMERA_CAPABILITY_ڈیٹا_TRANSFER_TYPE_BD) \
    _avail(XrCameraCapabilityImageFormatBD, XR_TYPE_CAMERA_CAPABILITY_IMAGE_FORMAT_BD) \
    _avail(XrCameraCapabilityCameraModelBD, XR_TYPE_CAMERA_CAPABILITY_CAMERA_MODEL_BD) \





/// Like XR_LIST_ALL_STRUCTURE_TYPES, but only includes types whose parent struct type is XrCameraImageDataBaseHeaderBD
#تعریف_کرو XR_LIST_ALL_بچہ_STRUCTURE_TYPES_Xr_Camera_Image_ڈیٹا_بنیاد_سرخی_BD(_avail, _unavail) \
    impl_XR_LIST_ALL_بچہ_STRUCTURE_TYPES_Xr_Camera_Image_ڈیٹا_بنیاد_سرخی_BD_CORE(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrCameraImageDataBaseHeaderBD()
#تعریف_کرو impl_XR_LIST_ALL_بچہ_STRUCTURE_TYPES_Xr_Camera_Image_ڈیٹا_بنیاد_سرخی_BD_CORE(_avail, _unavail) \
    _avail(Xr_Camera_Image_ڈیٹا_Raw_بفر_BD, XR_TYPE_CAMERA_IMAGE_ڈیٹا_RAW_بفر_BD) \





/// Like XR_LIST_ALL_STRUCTURE_TYPES, but only includes types whose parent struct type is XrGoogleCloudAuthInfoBaseHeaderANDROID
#تعریف_کرو XR_LIST_ALL_بچہ_STRUCTURE_TYPES_Xr_Google_Cloud_Auth_Info_بنیاد_سرخی_ANDROID(_avail, _unavail) \
    impl_XR_LIST_ALL_بچہ_STRUCTURE_TYPES_Xr_Google_Cloud_Auth_Info_بنیاد_سرخی_ANDROID_CORE(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrGoogleCloudAuthInfoBaseHeaderANDROID()
#تعریف_کرو impl_XR_LIST_ALL_بچہ_STRUCTURE_TYPES_Xr_Google_Cloud_Auth_Info_بنیاد_سرخی_ANDROID_CORE(_avail, _unavail) \
    _avail(Xr_Google_Cloud_Auth_Info_Api_کلید_ANDROID, XR_TYPE_GOOGLE_CLOUD_AUTH_INFO_API_کلید_ANDROID) \
    _avail(XrGoogleCloudAuthInfoTokenANDROID, XR_TYPE_GOOGLE_CLOUD_AUTH_INFO_TOKEN_ANDROID) \
    _avail(XrGoogleCloudAuthInfoKeylessANDROID, XR_TYPE_GOOGLE_CLOUD_AUTH_INFO_KEYLESS_ANDROID) \





#اگر_ختم

