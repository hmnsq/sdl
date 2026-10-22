#यदि_अपरिभाषितम् OPENXR_REFLECTION_PARENT_STRUCTS_H_
#परिभाषय OPENXR_REFLECTION_PARENT_STRUCTS_H_ 1

/*
** Copyright (c) 2017-2026 The Khronos Group Inc.
**
** SPDX-License-Identifier: Apache-2.0 OR MIT
*/

/*
** This header is generated from the Khronos OpenXR XML API Registry.
**
*/

#अन्तर्भाव "openxr.h"

/*
This file contains expansion macros (X Macros) for OpenXR structures that have a parent type.
*/


/// Like XR_LIST_ALL_STRUCTURE_TYPES, but only includes types whose parent struct type is XrCompositionLayerBaseHeader
#परिभाषय XR_LIST_ALL_CHILD_STRUCTURE_TYPES_Xr_Composition_Layer_आधारः_शीर्षकम्(_avail, _unavail) \
    impl_XR_LIST_ALL_CHILD_STRUCTURE_TYPES_Xr_Composition_Layer_आधारः_शीर्षकम्_CORE(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrCompositionLayerBaseHeader()
#परिभाषय impl_XR_LIST_ALL_CHILD_STRUCTURE_TYPES_Xr_Composition_Layer_आधारः_शीर्षकम्_CORE(_avail, _unavail) \
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
#परिभाषय XR_LIST_ALL_CHILD_STRUCTURE_TYPES_Xr_Event_दत्त_आधारः_शीर्षकम्(_avail, _unavail) \
    impl_XR_LIST_ALL_CHILD_STRUCTURE_TYPES_Xr_Event_दत्त_आधारः_शीर्षकम्_CORE(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrEventDataBaseHeader()
#परिभाषय impl_XR_LIST_ALL_CHILD_STRUCTURE_TYPES_Xr_Event_दत्त_आधारः_शीर्षकम्_CORE(_avail, _unavail) \
    _avail(Xr_Event_दत्त_Events_नष्टम्, XR_TYPE_EVENT_दत्त_EVENTS_नष्टम्) \
    _avail(Xr_Event_दत्त_Instance_Loss_Pending, XR_TYPE_EVENT_दत्त_INSTANCE_LOSS_PENDING) \
    _avail(Xr_Event_दत्त_Session_State_परिवर्तितम्, XR_TYPE_EVENT_दत्त_SESSION_STATE_परिवर्तितम्) \
    _avail(Xr_Event_दत्त_Reference_Space_Change_Pending, XR_TYPE_EVENT_दत्त_REFERENCE_SPACE_CHANGE_PENDING) \
    _avail(Xr_Event_दत्त_Interaction_Profile_परिवर्तितम्, XR_TYPE_EVENT_दत्त_INTERACTION_PROFILE_परिवर्तितम्) \
    _avail(Xr_Event_दत्त_Visibility_आवरणम्_परिवर्तितम्_KHR, XR_TYPE_EVENT_दत्त_VISIBILITY_आवरणम्_परिवर्तितम्_KHR) \
    _avail(Xr_Event_दत्त_Perf_Settings_EXT, XR_TYPE_EVENT_दत्त_PERF_SETTINGS_EXT) \
    _avail(Xr_Event_दत्त_Main_Session_Visibility_परिवर्तितम्_EXTX, XR_TYPE_EVENT_दत्त_MAIN_SESSION_VISIBILITY_परिवर्तितम्_EXTX) \
    _avail(Xr_Event_दत्त_Display_Refresh_दरः_परिवर्तितम्_FB, XR_TYPE_EVENT_दत्त_DISPLAY_REFRESH_दरः_परिवर्तितम्_FB) \
    _avail(Xr_Event_दत्त_Vive_Tracker_Connected_HTCX, XR_TYPE_EVENT_दत्त_VIVE_TRACKER_CONNECTED_HTCX) \
    _avail(Xr_Event_दत्त_Spatial_Anchor_Create_Complete_FB, XR_TYPE_EVENT_दत्त_SPATIAL_ANCHOR_CREATE_COMPLETE_FB) \
    _avail(Xr_Event_दत्त_Space_समुच्चयः_स्थितिः_Complete_FB, XR_TYPE_EVENT_दत्त_SPACE_समुच्चयः_स्थितिः_COMPLETE_FB) \
    _avail(Xr_Event_दत्त_Passthrough_State_परिवर्तितम्_FB, XR_TYPE_EVENT_दत्त_PASSTHROUGH_STATE_परिवर्तितम्_FB) \
    _avail(Xr_Event_दत्त_Marker_Tracking_Update_VARJO, XR_TYPE_EVENT_दत्त_MARKER_TRACKING_UPDATE_VARJO) \
    _avail(Xr_Event_दत्त_Localization_परिवर्तितम्_ML, XR_TYPE_EVENT_दत्त_LOCALIZATION_परिवर्तितम्_ML) \
    _avail(Xr_Event_दत्त_Space_Query_Results_उपलब्धम्_FB, XR_TYPE_EVENT_दत्त_SPACE_QUERY_RESULTS_उपलब्धम्_FB) \
    _avail(Xr_Event_दत्त_Space_Query_Complete_FB, XR_TYPE_EVENT_दत्त_SPACE_QUERY_COMPLETE_FB) \
    _avail(Xr_Event_दत्त_Space_Save_Complete_FB, XR_TYPE_EVENT_दत्त_SPACE_SAVE_COMPLETE_FB) \
    _avail(Xr_Event_दत्त_Space_Erase_Complete_FB, XR_TYPE_EVENT_दत्त_SPACE_ERASE_COMPLETE_FB) \
    _avail(Xr_Event_दत्त_Space_Share_Complete_FB, XR_TYPE_EVENT_दत्त_SPACE_SHARE_COMPLETE_FB) \
    _avail(Xr_Event_दत्त_Scene_Capture_Complete_FB, XR_TYPE_EVENT_दत्त_SCENE_CAPTURE_COMPLETE_FB) \
    _avail(Xr_Event_दत्त_Virtual_Keyboard_Commit_Text_META, XR_TYPE_EVENT_दत्त_VIRTUAL_KEYBOARD_COMMIT_TEXT_META) \
    _avail(Xr_Event_दत्त_Virtual_Keyboard_Backspace_META, XR_TYPE_EVENT_दत्त_VIRTUAL_KEYBOARD_BACKSPACE_META) \
    _avail(Xr_Event_दत्त_Virtual_Keyboard_Enter_META, XR_TYPE_EVENT_दत्त_VIRTUAL_KEYBOARD_ENTER_META) \
    _avail(Xr_Event_दत्त_Virtual_Keyboard_Shown_META, XR_TYPE_EVENT_दत्त_VIRTUAL_KEYBOARD_SHOWN_META) \
    _avail(Xr_Event_दत्त_Virtual_Keyboard_Hidden_META, XR_TYPE_EVENT_दत्त_VIRTUAL_KEYBOARD_HIDDEN_META) \
    _avail(Xr_Event_दत्त_Space_List_Save_Complete_FB, XR_TYPE_EVENT_दत्त_SPACE_LIST_SAVE_COMPLETE_FB) \
    _avail(Xr_Event_दत्त_Space_Discovery_Results_उपलब्धम्_META, XR_TYPE_EVENT_दत्त_SPACE_DISCOVERY_RESULTS_उपलब्धम्_META) \
    _avail(Xr_Event_दत्त_Space_Discovery_Complete_META, XR_TYPE_EVENT_दत्त_SPACE_DISCOVERY_COMPLETE_META) \
    _avail(Xr_Event_दत्त_Spaces_Save_परिणाम_META, XR_TYPE_EVENT_दत्त_SPACES_SAVE_परिणाम_META) \
    _avail(Xr_Event_दत्त_Spaces_Erase_परिणाम_META, XR_TYPE_EVENT_दत्त_SPACES_ERASE_परिणाम_META) \
    _avail(Xr_Event_दत्त_Passthrough_Layer_Resumed_META, XR_TYPE_EVENT_दत्त_PASSTHROUGH_LAYER_RESUMED_META) \
    _avail(Xr_Event_दत्त_Share_Spaces_Complete_META, XR_TYPE_EVENT_दत्त_SHARE_SPACES_COMPLETE_META) \
    _avail(Xr_Event_दत्त_Interaction_Render_Models_परिवर्तितम्_EXT, XR_TYPE_EVENT_दत्त_INTERACTION_RENDER_MODELS_परिवर्तितम्_EXT) \
    _avail(Xr_Event_दत्त_Sense_दत्त_Provider_State_परिवर्तितम्_BD, XR_TYPE_EVENT_दत्त_SENSE_दत्त_PROVIDER_STATE_परिवर्तितम्_BD) \
    _avail(Xr_Event_दत्त_Sense_दत्त_Updated_BD, XR_TYPE_EVENT_दत्त_SENSE_दत्त_UPDATED_BD) \
    _avail(Xr_Event_दत्त_Recommended_Resolution_परिवर्तितम्_ANDROID, XR_TYPE_EVENT_दत्त_RECOMMENDED_RESOLUTION_परिवर्तितम्_ANDROID) \
    _avail(Xr_Event_दत्त_User_Presence_परिवर्तितम्_EXT, XR_TYPE_EVENT_दत्त_USER_PRESENCE_परिवर्तितम्_EXT) \
    _avail(Xr_Event_दत्त_Headset_Fit_परिवर्तितम्_ML, XR_TYPE_EVENT_दत्त_HEADSET_FIT_परिवर्तितम्_ML) \
    _avail(Xr_Event_दत्त_Eye_Calibration_परिवर्तितम्_ML, XR_TYPE_EVENT_दत्त_EYE_CALIBRATION_परिवर्तितम्_ML) \
    _avail(Xr_Event_दत्त_Boundary_Visibility_परिवर्तितम्_META, XR_TYPE_EVENT_दत्त_BOUNDARY_VISIBILITY_परिवर्तितम्_META) \
    _avail(Xr_Event_दत्त_Start_Colocation_Advertisement_Complete_META, XR_TYPE_EVENT_दत्त_START_COLOCATION_ADVERTISEMENT_COMPLETE_META) \
    _avail(Xr_Event_दत्त_Stop_Colocation_Advertisement_Complete_META, XR_TYPE_EVENT_दत्त_STOP_COLOCATION_ADVERTISEMENT_COMPLETE_META) \
    _avail(Xr_Event_दत्त_Colocation_Advertisement_Complete_META, XR_TYPE_EVENT_दत्त_COLOCATION_ADVERTISEMENT_COMPLETE_META) \
    _avail(Xr_Event_दत्त_Start_Colocation_Discovery_Complete_META, XR_TYPE_EVENT_दत्त_START_COLOCATION_DISCOVERY_COMPLETE_META) \
    _avail(Xr_Event_दत्त_Colocation_Discovery_परिणाम_META, XR_TYPE_EVENT_दत्त_COLOCATION_DISCOVERY_परिणाम_META) \
    _avail(Xr_Event_दत्त_Colocation_Discovery_Complete_META, XR_TYPE_EVENT_दत्त_COLOCATION_DISCOVERY_COMPLETE_META) \
    _avail(Xr_Event_दत्त_Stop_Colocation_Discovery_Complete_META, XR_TYPE_EVENT_दत्त_STOP_COLOCATION_DISCOVERY_COMPLETE_META) \
    _avail(Xr_Event_दत्त_Image_Tracking_नष्टम्_ANDROID, XR_TYPE_EVENT_दत्त_IMAGE_TRACKING_नष्टम्_ANDROID) \
    _avail(Xr_Event_दत्त_Spatial_Discovery_Recommended_EXT, XR_TYPE_EVENT_दत्त_SPATIAL_DISCOVERY_RECOMMENDED_EXT) \
    _avail(Xr_Event_दत्त_Geospatial_Tracker_State_परिवर्तितम्_ANDROID, XR_TYPE_EVENT_दत्त_GEOSPATIAL_TRACKER_STATE_परिवर्तितम्_ANDROID) \
    _avail(Xr_Event_दत्त_Spatial_Container_Closed_EXT, XR_TYPE_EVENT_दत्त_SPATIAL_CONTAINER_CLOSED_EXT) \
    _avail(Xr_Event_दत्त_Spatial_Container_Bounds_परिवर्तितम्_EXT, XR_TYPE_EVENT_दत्त_SPATIAL_CONTAINER_BOUNDS_परिवर्तितम्_EXT) \
    _avail(Xr_Event_दत्त_Spatial_Container_Visible_परिवर्तितम्_EXT, XR_TYPE_EVENT_दत्त_SPATIAL_CONTAINER_VISIBLE_परिवर्तितम्_EXT) \
    _avail(Xr_Event_दत्त_Spatial_Container_Visible_Request_Denied_EXT, XR_TYPE_EVENT_दत्त_SPATIAL_CONTAINER_VISIBLE_REQUEST_DENIED_EXT) \
    _avail(Xr_Event_दत्त_Spatial_Container_Interactable_परिवर्तितम्_EXT, XR_TYPE_EVENT_दत्त_SPATIAL_CONTAINER_INTERACTABLE_परिवर्तितम्_EXT) \
    _avail(Xr_Event_दत्त_Spatial_Container_Bounds_बहुलकम्_Request_Denied_EXT, XR_TYPE_EVENT_दत्त_SPATIAL_CONTAINER_BOUNDS_बहुलकम्_REQUEST_DENIED_EXT) \
    _avail(Xr_Event_दत्त_View_Configuration_Views_परिवर्तितम्_EXT, XR_TYPE_EVENT_दत्त_VIEW_CONFIGURATION_VIEWS_परिवर्तितम्_EXT) \





/// Like XR_LIST_ALL_STRUCTURE_TYPES, but only includes types whose parent struct type is XrHapticBaseHeader
#परिभाषय XR_LIST_ALL_CHILD_STRUCTURE_TYPES_Xr_Haptic_आधारः_शीर्षकम्(_avail, _unavail) \
    impl_XR_LIST_ALL_CHILD_STRUCTURE_TYPES_Xr_Haptic_आधारः_शीर्षकम्_CORE(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrHapticBaseHeader()
#परिभाषय impl_XR_LIST_ALL_CHILD_STRUCTURE_TYPES_Xr_Haptic_आधारः_शीर्षकम्_CORE(_avail, _unavail) \
    _avail(XrHapticVibration, XR_TYPE_HAPTIC_VIBRATION) \
    _avail(XrHapticAmplitudeEnvelopeVibrationFB, XR_TYPE_HAPTIC_AMPLITUDE_ENVELOPE_VIBRATION_FB) \
    _avail(XrHapticPcmVibrationFB, XR_TYPE_HAPTIC_PCM_VIBRATION_FB) \
    _avail(XrHapticParametricVibrationEXT, XR_TYPE_HAPTIC_PARAMETRIC_VIBRATION_EXT) \





/// Like XR_LIST_ALL_STRUCTURE_TYPES, but only includes types whose parent struct type is XrSwapchainImageBaseHeader
#परिभाषय XR_LIST_ALL_CHILD_STRUCTURE_TYPES_Xr_Swapchain_Image_आधारः_शीर्षकम्(_avail, _unavail) \
    impl_XR_LIST_ALL_CHILD_STRUCTURE_TYPES_Xr_Swapchain_Image_आधारः_शीर्षकम्_CORE(_avail, _unavail) \
    impl_XR_LIST_ALL_CHILD_STRUCTURE_TYPES_Xr_Swapchain_Image_आधारः_शीर्षकम्_XR_USE_GRAPHICS_API_D3_D11(_avail, _unavail) \
    impl_XR_LIST_ALL_CHILD_STRUCTURE_TYPES_Xr_Swapchain_Image_आधारः_शीर्षकम्_XR_USE_GRAPHICS_API_D3_D12(_avail, _unavail) \
    impl_XR_LIST_ALL_CHILD_STRUCTURE_TYPES_Xr_Swapchain_Image_आधारः_शीर्षकम्_XR_USE_GRAPHICS_API_METAL(_avail, _unavail) \
    impl_XR_LIST_ALL_CHILD_STRUCTURE_TYPES_Xr_Swapchain_Image_आधारः_शीर्षकम्_XR_USE_GRAPHICS_API_OPENGL(_avail, _unavail) \
    impl_XR_LIST_ALL_CHILD_STRUCTURE_TYPES_Xr_Swapchain_Image_आधारः_शीर्षकम्_XR_USE_GRAPHICS_API_OPENGL_ES(_avail, _unavail) \
    impl_XR_LIST_ALL_CHILD_STRUCTURE_TYPES_Xr_Swapchain_Image_आधारः_शीर्षकम्_XR_USE_GRAPHICS_API_VULKAN(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrSwapchainImageBaseHeader()
#परिभाषय impl_XR_LIST_ALL_CHILD_STRUCTURE_TYPES_Xr_Swapchain_Image_आधारः_शीर्षकम्_CORE(_avail, _unavail) \


#यदि defined(XR_USE_GRAPHICS_API_D3D11)
#परिभाषय impl_XR_LIST_ALL_CHILD_STRUCTURE_TYPES_Xr_Swapchain_Image_आधारः_शीर्षकम्_XR_USE_GRAPHICS_API_D3_D11(_avail, _unavail) \
    _avail(XrSwapchainImageD3D11KHR, XR_TYPE_SWAPCHAIN_IMAGE_D3D11_KHR) \

#अन्यथा
#परिभाषय impl_XR_LIST_ALL_CHILD_STRUCTURE_TYPES_Xr_Swapchain_Image_आधारः_शीर्षकम्_XR_USE_GRAPHICS_API_D3_D11(_avail, _unavail) \
    _unavail(XrSwapchainImageD3D11KHR, XR_TYPE_SWAPCHAIN_IMAGE_D3D11_KHR) \

#यदि_अन्तः

#यदि defined(XR_USE_GRAPHICS_API_D3D12)
#परिभाषय impl_XR_LIST_ALL_CHILD_STRUCTURE_TYPES_Xr_Swapchain_Image_आधारः_शीर्षकम्_XR_USE_GRAPHICS_API_D3_D12(_avail, _unavail) \
    _avail(XrSwapchainImageD3D12KHR, XR_TYPE_SWAPCHAIN_IMAGE_D3D12_KHR) \

#अन्यथा
#परिभाषय impl_XR_LIST_ALL_CHILD_STRUCTURE_TYPES_Xr_Swapchain_Image_आधारः_शीर्षकम्_XR_USE_GRAPHICS_API_D3_D12(_avail, _unavail) \
    _unavail(XrSwapchainImageD3D12KHR, XR_TYPE_SWAPCHAIN_IMAGE_D3D12_KHR) \

#यदि_अन्तः

#यदि defined(XR_USE_GRAPHICS_API_METAL)
#परिभाषय impl_XR_LIST_ALL_CHILD_STRUCTURE_TYPES_Xr_Swapchain_Image_आधारः_शीर्षकम्_XR_USE_GRAPHICS_API_METAL(_avail, _unavail) \
    _avail(XrSwapchainImageMetalKHR, XR_TYPE_SWAPCHAIN_IMAGE_METAL_KHR) \

#अन्यथा
#परिभाषय impl_XR_LIST_ALL_CHILD_STRUCTURE_TYPES_Xr_Swapchain_Image_आधारः_शीर्षकम्_XR_USE_GRAPHICS_API_METAL(_avail, _unavail) \
    _unavail(XrSwapchainImageMetalKHR, XR_TYPE_SWAPCHAIN_IMAGE_METAL_KHR) \

#यदि_अन्तः

#यदि defined(XR_USE_GRAPHICS_API_OPENGL)
#परिभाषय impl_XR_LIST_ALL_CHILD_STRUCTURE_TYPES_Xr_Swapchain_Image_आधारः_शीर्षकम्_XR_USE_GRAPHICS_API_OPENGL(_avail, _unavail) \
    _avail(XrSwapchainImageOpenGLKHR, XR_TYPE_SWAPCHAIN_IMAGE_OPENGL_KHR) \

#अन्यथा
#परिभाषय impl_XR_LIST_ALL_CHILD_STRUCTURE_TYPES_Xr_Swapchain_Image_आधारः_शीर्षकम्_XR_USE_GRAPHICS_API_OPENGL(_avail, _unavail) \
    _unavail(XrSwapchainImageOpenGLKHR, XR_TYPE_SWAPCHAIN_IMAGE_OPENGL_KHR) \

#यदि_अन्तः

#यदि defined(XR_USE_GRAPHICS_API_OPENGL_ES)
#परिभाषय impl_XR_LIST_ALL_CHILD_STRUCTURE_TYPES_Xr_Swapchain_Image_आधारः_शीर्षकम्_XR_USE_GRAPHICS_API_OPENGL_ES(_avail, _unavail) \
    _avail(XrSwapchainImageOpenGLESKHR, XR_TYPE_SWAPCHAIN_IMAGE_OPENGL_ES_KHR) \

#अन्यथा
#परिभाषय impl_XR_LIST_ALL_CHILD_STRUCTURE_TYPES_Xr_Swapchain_Image_आधारः_शीर्षकम्_XR_USE_GRAPHICS_API_OPENGL_ES(_avail, _unavail) \
    _unavail(XrSwapchainImageOpenGLESKHR, XR_TYPE_SWAPCHAIN_IMAGE_OPENGL_ES_KHR) \

#यदि_अन्तः

#यदि defined(XR_USE_GRAPHICS_API_VULKAN)
#परिभाषय impl_XR_LIST_ALL_CHILD_STRUCTURE_TYPES_Xr_Swapchain_Image_आधारः_शीर्षकम्_XR_USE_GRAPHICS_API_VULKAN(_avail, _unavail) \
    _avail(XrSwapchainImageVulkanKHR, XR_TYPE_SWAPCHAIN_IMAGE_VULKAN_KHR) \

#अन्यथा
#परिभाषय impl_XR_LIST_ALL_CHILD_STRUCTURE_TYPES_Xr_Swapchain_Image_आधारः_शीर्षकम्_XR_USE_GRAPHICS_API_VULKAN(_avail, _unavail) \
    _unavail(XrSwapchainImageVulkanKHR, XR_TYPE_SWAPCHAIN_IMAGE_VULKAN_KHR) \

#यदि_अन्तः




/// Like XR_LIST_ALL_STRUCTURE_TYPES, but only includes types whose parent struct type is XrLoaderInitInfoBaseHeaderKHR
#परिभाषय XR_LIST_ALL_CHILD_STRUCTURE_TYPES_Xr_Loader_Init_Info_आधारः_शीर्षकम्_KHR(_avail, _unavail) \
    impl_XR_LIST_ALL_CHILD_STRUCTURE_TYPES_Xr_Loader_Init_Info_आधारः_शीर्षकम्_KHR_CORE(_avail, _unavail) \
    impl_XR_LIST_ALL_CHILD_STRUCTURE_TYPES_Xr_Loader_Init_Info_आधारः_शीर्षकम्_KHR_XR_USE_PLATFORM_ANDROID(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrLoaderInitInfoBaseHeaderKHR()
#परिभाषय impl_XR_LIST_ALL_CHILD_STRUCTURE_TYPES_Xr_Loader_Init_Info_आधारः_शीर्षकम्_KHR_CORE(_avail, _unavail) \
    _avail(XrLoaderInitInfoPropertiesEXT, XR_TYPE_LOADER_INIT_INFO_PROPERTIES_EXT) \


#यदि defined(XR_USE_PLATFORM_ANDROID)
#परिभाषय impl_XR_LIST_ALL_CHILD_STRUCTURE_TYPES_Xr_Loader_Init_Info_आधारः_शीर्षकम्_KHR_XR_USE_PLATFORM_ANDROID(_avail, _unavail) \
    _avail(XrLoaderInitInfoAndroidKHR, XR_TYPE_LOADER_INIT_INFO_ANDROID_KHR) \

#अन्यथा
#परिभाषय impl_XR_LIST_ALL_CHILD_STRUCTURE_TYPES_Xr_Loader_Init_Info_आधारः_शीर्षकम्_KHR_XR_USE_PLATFORM_ANDROID(_avail, _unavail) \
    _unavail(XrLoaderInitInfoAndroidKHR, XR_TYPE_LOADER_INIT_INFO_ANDROID_KHR) \

#यदि_अन्तः




/// Like XR_LIST_ALL_STRUCTURE_TYPES, but only includes types whose parent struct type is XrBindingModificationBaseHeaderKHR
#परिभाषय XR_LIST_ALL_CHILD_STRUCTURE_TYPES_Xr_Binding_Modification_आधारः_शीर्षकम्_KHR(_avail, _unavail) \
    impl_XR_LIST_ALL_CHILD_STRUCTURE_TYPES_Xr_Binding_Modification_आधारः_शीर्षकम्_KHR_CORE(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrBindingModificationBaseHeaderKHR()
#परिभाषय impl_XR_LIST_ALL_CHILD_STRUCTURE_TYPES_Xr_Binding_Modification_आधारः_शीर्षकम्_KHR_CORE(_avail, _unavail) \
    _avail(XrInteractionProfileDpadBindingEXT, XR_TYPE_INTERACTION_PROFILE_DPAD_BINDING_EXT) \
    _avail(Xr_Interaction_Profile_Analog_देहली_VALVE, XR_TYPE_INTERACTION_PROFILE_ANALOG_देहली_VALVE) \





/// Like XR_LIST_ALL_STRUCTURE_TYPES, but only includes types whose parent struct type is XrSwapchainStateBaseHeaderFB
#परिभाषय XR_LIST_ALL_CHILD_STRUCTURE_TYPES_Xr_Swapchain_State_आधारः_शीर्षकम्_FB(_avail, _unavail) \
    impl_XR_LIST_ALL_CHILD_STRUCTURE_TYPES_Xr_Swapchain_State_आधारः_शीर्षकम्_FB_CORE(_avail, _unavail) \
    impl_XR_LIST_ALL_CHILD_STRUCTURE_TYPES_Xr_Swapchain_State_आधारः_शीर्षकम्_FB_XR_USE_GRAPHICS_API_OPENGL_ES(_avail, _unavail) \
    impl_XR_LIST_ALL_CHILD_STRUCTURE_TYPES_Xr_Swapchain_State_आधारः_शीर्षकम्_FB_XR_USE_GRAPHICS_API_VULKAN(_avail, _unavail) \
    impl_XR_LIST_ALL_CHILD_STRUCTURE_TYPES_Xr_Swapchain_State_आधारः_शीर्षकम्_FB_XR_USE_PLATFORM_ANDROID(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrSwapchainStateBaseHeaderFB()
#परिभाषय impl_XR_LIST_ALL_CHILD_STRUCTURE_TYPES_Xr_Swapchain_State_आधारः_शीर्षकम्_FB_CORE(_avail, _unavail) \
    _avail(XrSwapchainStateFoveationFB, XR_TYPE_SWAPCHAIN_STATE_FOVEATION_FB) \


#यदि defined(XR_USE_GRAPHICS_API_OPENGL_ES)
#परिभाषय impl_XR_LIST_ALL_CHILD_STRUCTURE_TYPES_Xr_Swapchain_State_आधारः_शीर्षकम्_FB_XR_USE_GRAPHICS_API_OPENGL_ES(_avail, _unavail) \
    _avail(XrSwapchainStateSamplerOpenGLESFB, XR_TYPE_SWAPCHAIN_STATE_SAMPLER_OPENGL_ES_FB) \

#अन्यथा
#परिभाषय impl_XR_LIST_ALL_CHILD_STRUCTURE_TYPES_Xr_Swapchain_State_आधारः_शीर्षकम्_FB_XR_USE_GRAPHICS_API_OPENGL_ES(_avail, _unavail) \
    _unavail(XrSwapchainStateSamplerOpenGLESFB, XR_TYPE_SWAPCHAIN_STATE_SAMPLER_OPENGL_ES_FB) \

#यदि_अन्तः

#यदि defined(XR_USE_GRAPHICS_API_VULKAN)
#परिभाषय impl_XR_LIST_ALL_CHILD_STRUCTURE_TYPES_Xr_Swapchain_State_आधारः_शीर्षकम्_FB_XR_USE_GRAPHICS_API_VULKAN(_avail, _unavail) \
    _avail(XrSwapchainStateSamplerVulkanFB, XR_TYPE_SWAPCHAIN_STATE_SAMPLER_VULKAN_FB) \

#अन्यथा
#परिभाषय impl_XR_LIST_ALL_CHILD_STRUCTURE_TYPES_Xr_Swapchain_State_आधारः_शीर्षकम्_FB_XR_USE_GRAPHICS_API_VULKAN(_avail, _unavail) \
    _unavail(XrSwapchainStateSamplerVulkanFB, XR_TYPE_SWAPCHAIN_STATE_SAMPLER_VULKAN_FB) \

#यदि_अन्तः

#यदि defined(XR_USE_PLATFORM_ANDROID)
#परिभाषय impl_XR_LIST_ALL_CHILD_STRUCTURE_TYPES_Xr_Swapchain_State_आधारः_शीर्षकम्_FB_XR_USE_PLATFORM_ANDROID(_avail, _unavail) \
    _avail(XrSwapchainStateAndroidSurfaceDimensionsFB, XR_TYPE_SWAPCHAIN_STATE_ANDROID_SURFACE_DIMENSIONS_FB) \

#अन्यथा
#परिभाषय impl_XR_LIST_ALL_CHILD_STRUCTURE_TYPES_Xr_Swapchain_State_आधारः_शीर्षकम्_FB_XR_USE_PLATFORM_ANDROID(_avail, _unavail) \
    _unavail(XrSwapchainStateAndroidSurfaceDimensionsFB, XR_TYPE_SWAPCHAIN_STATE_ANDROID_SURFACE_DIMENSIONS_FB) \

#यदि_अन्तः




/// Like XR_LIST_ALL_STRUCTURE_TYPES, but only includes types whose parent struct type is XrSpatialAnchorsCreateInfoBaseHeaderML
#परिभाषय XR_LIST_ALL_CHILD_STRUCTURE_TYPES_Xr_Spatial_Anchors_Create_Info_आधारः_शीर्षकम्_ML(_avail, _unavail) \
    impl_XR_LIST_ALL_CHILD_STRUCTURE_TYPES_Xr_Spatial_Anchors_Create_Info_आधारः_शीर्षकम्_ML_CORE(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrSpatialAnchorsCreateInfoBaseHeaderML()
#परिभाषय impl_XR_LIST_ALL_CHILD_STRUCTURE_TYPES_Xr_Spatial_Anchors_Create_Info_आधारः_शीर्षकम्_ML_CORE(_avail, _unavail) \
    _avail(XrSpatialAnchorsCreateInfoFromPoseML, XR_TYPE_SPATIAL_ANCHORS_CREATE_INFO_FROM_POSE_ML) \
    _avail(XrSpatialAnchorsCreateInfoFromUuidsML, XR_TYPE_SPATIAL_ANCHORS_CREATE_INFO_FROM_UUIDS_ML) \





/// Like XR_LIST_ALL_STRUCTURE_TYPES, but only includes types whose parent struct type is XrFutureCompletionBaseHeaderEXT
#परिभाषय XR_LIST_ALL_CHILD_STRUCTURE_TYPES_Xr_Future_Completion_आधारः_शीर्षकम्_EXT(_avail, _unavail) \
    impl_XR_LIST_ALL_CHILD_STRUCTURE_TYPES_Xr_Future_Completion_आधारः_शीर्षकम्_EXT_CORE(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrFutureCompletionBaseHeaderEXT()
#परिभाषय impl_XR_LIST_ALL_CHILD_STRUCTURE_TYPES_Xr_Future_Completion_आधारः_शीर्षकम्_EXT_CORE(_avail, _unavail) \
    _avail(XrCreateSpatialAnchorsCompletionML, XR_TYPE_CREATE_SPATIAL_ANCHORS_COMPLETION_ML) \
    _avail(XrSpatialAnchorsQueryCompletionML, XR_TYPE_SPATIAL_ANCHORS_QUERY_COMPLETION_ML) \
    _avail(XrSpatialAnchorsPublishCompletionML, XR_TYPE_SPATIAL_ANCHORS_PUBLISH_COMPLETION_ML) \
    _avail(XrSpatialAnchorsDeleteCompletionML, XR_TYPE_SPATIAL_ANCHORS_DELETE_COMPLETION_ML) \
    _avail(XrSpatialAnchorsUpdateExpirationCompletionML, XR_TYPE_SPATIAL_ANCHORS_UPDATE_EXPIRATION_COMPLETION_ML) \
    _avail(Xr_Sense_दत्त_Query_Completion_BD, XR_TYPE_SENSE_दत्त_QUERY_COMPLETION_BD) \
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
#परिभाषय XR_LIST_ALL_CHILD_STRUCTURE_TYPES_Xr_Spatial_Anchors_Query_Info_आधारः_शीर्षकम्_ML(_avail, _unavail) \
    impl_XR_LIST_ALL_CHILD_STRUCTURE_TYPES_Xr_Spatial_Anchors_Query_Info_आधारः_शीर्षकम्_ML_CORE(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrSpatialAnchorsQueryInfoBaseHeaderML()
#परिभाषय impl_XR_LIST_ALL_CHILD_STRUCTURE_TYPES_Xr_Spatial_Anchors_Query_Info_आधारः_शीर्षकम्_ML_CORE(_avail, _unavail) \
    _avail(XrSpatialAnchorsQueryInfoRadiusML, XR_TYPE_SPATIAL_ANCHORS_QUERY_INFO_RADIUS_ML) \





/// Like XR_LIST_ALL_STRUCTURE_TYPES, but only includes types whose parent struct type is XrSpaceQueryInfoBaseHeaderFB
#परिभाषय XR_LIST_ALL_CHILD_STRUCTURE_TYPES_Xr_Space_Query_Info_आधारः_शीर्षकम्_FB(_avail, _unavail) \
    impl_XR_LIST_ALL_CHILD_STRUCTURE_TYPES_Xr_Space_Query_Info_आधारः_शीर्षकम्_FB_CORE(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrSpaceQueryInfoBaseHeaderFB()
#परिभाषय impl_XR_LIST_ALL_CHILD_STRUCTURE_TYPES_Xr_Space_Query_Info_आधारः_शीर्षकम्_FB_CORE(_avail, _unavail) \
    _avail(XrSpaceQueryInfoFB, XR_TYPE_SPACE_QUERY_INFO_FB) \





/// Like XR_LIST_ALL_STRUCTURE_TYPES, but only includes types whose parent struct type is XrSpaceFilterInfoBaseHeaderFB
#परिभाषय XR_LIST_ALL_CHILD_STRUCTURE_TYPES_Xr_Space_Filter_Info_आधारः_शीर्षकम्_FB(_avail, _unavail) \
    impl_XR_LIST_ALL_CHILD_STRUCTURE_TYPES_Xr_Space_Filter_Info_आधारः_शीर्षकम्_FB_CORE(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrSpaceFilterInfoBaseHeaderFB()
#परिभाषय impl_XR_LIST_ALL_CHILD_STRUCTURE_TYPES_Xr_Space_Filter_Info_आधारः_शीर्षकम्_FB_CORE(_avail, _unavail) \
    _avail(XrSpaceUuidFilterInfoFB, XR_TYPE_SPACE_UUID_FILTER_INFO_FB) \
    _avail(XrSpaceComponentFilterInfoFB, XR_TYPE_SPACE_COMPONENT_FILTER_INFO_FB) \





/// Like XR_LIST_ALL_STRUCTURE_TYPES, but only includes types whose parent struct type is XrSpaceFilterBaseHeaderMETA
#परिभाषय XR_LIST_ALL_CHILD_STRUCTURE_TYPES_Xr_Space_Filter_आधारः_शीर्षकम्_META(_avail, _unavail) \
    impl_XR_LIST_ALL_CHILD_STRUCTURE_TYPES_Xr_Space_Filter_आधारः_शीर्षकम्_META_CORE(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrSpaceFilterBaseHeaderMETA()
#परिभाषय impl_XR_LIST_ALL_CHILD_STRUCTURE_TYPES_Xr_Space_Filter_आधारः_शीर्षकम्_META_CORE(_avail, _unavail) \
    _avail(XrSpaceFilterUuidMETA, XR_TYPE_SPACE_FILTER_UUID_META) \
    _avail(XrSpaceFilterComponentMETA, XR_TYPE_SPACE_FILTER_COMPONENT_META) \





/// Like XR_LIST_ALL_STRUCTURE_TYPES, but only includes types whose parent struct type is XrShareSpacesRecipientBaseHeaderMETA
#परिभाषय XR_LIST_ALL_CHILD_STRUCTURE_TYPES_Xr_Share_Spaces_Recipient_आधारः_शीर्षकम्_META(_avail, _unavail) \
    impl_XR_LIST_ALL_CHILD_STRUCTURE_TYPES_Xr_Share_Spaces_Recipient_आधारः_शीर्षकम्_META_CORE(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrShareSpacesRecipientBaseHeaderMETA()
#परिभाषय impl_XR_LIST_ALL_CHILD_STRUCTURE_TYPES_Xr_Share_Spaces_Recipient_आधारः_शीर्षकम्_META_CORE(_avail, _unavail) \
    _avail(XrShareSpacesRecipientGroupsMETA, XR_TYPE_SHARE_SPACES_RECIPIENT_GROUPS_META) \





/// Like XR_LIST_ALL_STRUCTURE_TYPES, but only includes types whose parent struct type is XrEnvironmentRaycastFilterBaseHeaderMETA
#परिभाषय XR_LIST_ALL_CHILD_STRUCTURE_TYPES_Xr_Environment_Raycast_Filter_आधारः_शीर्षकम्_META(_avail, _unavail) \
    impl_XR_LIST_ALL_CHILD_STRUCTURE_TYPES_Xr_Environment_Raycast_Filter_आधारः_शीर्षकम्_META_CORE(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrEnvironmentRaycastFilterBaseHeaderMETA()
#परिभाषय impl_XR_LIST_ALL_CHILD_STRUCTURE_TYPES_Xr_Environment_Raycast_Filter_आधारः_शीर्षकम्_META_CORE(_avail, _unavail) \
    _avail(XrEnvironmentRaycastFilterDistanceMETA, XR_TYPE_ENVIRONMENT_RAYCAST_FILTER_DISTANCE_META) \





/// Like XR_LIST_ALL_STRUCTURE_TYPES, but only includes types whose parent struct type is XrSpatialCapabilityConfigurationBaseHeaderEXT
#परिभाषय XR_LIST_ALL_CHILD_STRUCTURE_TYPES_Xr_Spatial_Capability_Configuration_आधारः_शीर्षकम्_EXT(_avail, _unavail) \
    impl_XR_LIST_ALL_CHILD_STRUCTURE_TYPES_Xr_Spatial_Capability_Configuration_आधारः_शीर्षकम्_EXT_CORE(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrSpatialCapabilityConfigurationBaseHeaderEXT()
#परिभाषय impl_XR_LIST_ALL_CHILD_STRUCTURE_TYPES_Xr_Spatial_Capability_Configuration_आधारः_शीर्षकम्_EXT_CORE(_avail, _unavail) \
    _avail(XrSpatialCapabilityConfigurationPlaneTrackingEXT, XR_TYPE_SPATIAL_CAPABILITY_CONFIGURATION_PLANE_TRACKING_EXT) \
    _avail(Xr_Spatial_Capability_Configuration_Qr_संहिता_EXT, XR_TYPE_SPATIAL_CAPABILITY_CONFIGURATION_QR_संहिता_EXT) \
    _avail(Xr_Spatial_Capability_Configuration_Micro_Qr_संहिता_EXT, XR_TYPE_SPATIAL_CAPABILITY_CONFIGURATION_MICRO_QR_संहिता_EXT) \
    _avail(XrSpatialCapabilityConfigurationArucoMarkerEXT, XR_TYPE_SPATIAL_CAPABILITY_CONFIGURATION_ARUCO_MARKER_EXT) \
    _avail(Xr_Spatial_Capability_Configuration_April_चिह्नकम्_EXT, XR_TYPE_SPATIAL_CAPABILITY_CONFIGURATION_APRIL_चिह्नकम्_EXT) \
    _avail(XrSpatialCapabilityConfigurationObjectTrackingEXT, XR_TYPE_SPATIAL_CAPABILITY_CONFIGURATION_OBJECT_TRACKING_EXT) \
    _avail(XrSpatialCapabilityConfigurationAnchorEXT, XR_TYPE_SPATIAL_CAPABILITY_CONFIGURATION_ANCHOR_EXT) \
    _avail(XrSpatialCapabilityConfigurationImageTrackingEXT, XR_TYPE_SPATIAL_CAPABILITY_CONFIGURATION_IMAGE_TRACKING_EXT) \
    _avail(XrSpatialCapabilityConfigurationMeshTrackingEXT, XR_TYPE_SPATIAL_CAPABILITY_CONFIGURATION_MESH_TRACKING_EXT) \
    _avail(XrSpatialCapabilityConfigurationObjectTrackingANDROID, XR_TYPE_SPATIAL_CAPABILITY_CONFIGURATION_OBJECT_TRACKING_ANDROID) \
    _avail(Xr_Spatial_Capability_Configuration_गभीरता_Raycast_ANDROID, XR_TYPE_SPATIAL_CAPABILITY_CONFIGURATION_गभीरता_RAYCAST_ANDROID) \





/// Like XR_LIST_ALL_STRUCTURE_TYPES, but only includes types whose parent struct type is XrCameraPropertyBaseHeaderBD
#परिभाषय XR_LIST_ALL_CHILD_STRUCTURE_TYPES_Xr_Camera_Property_आधारः_शीर्षकम्_BD(_avail, _unavail) \
    impl_XR_LIST_ALL_CHILD_STRUCTURE_TYPES_Xr_Camera_Property_आधारः_शीर्षकम्_BD_CORE(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrCameraPropertyBaseHeaderBD()
#परिभाषय impl_XR_LIST_ALL_CHILD_STRUCTURE_TYPES_Xr_Camera_Property_आधारः_शीर्षकम्_BD_CORE(_avail, _unavail) \
    _avail(XrCameraPropertyFacingBD, XR_TYPE_CAMERA_PROPERTY_FACING_BD) \
    _avail(XrCameraPropertyPositionBD, XR_TYPE_CAMERA_PROPERTY_POSITION_BD) \
    _avail(XrCameraPropertyCameraTypeBD, XR_TYPE_CAMERA_PROPERTY_CAMERA_TYPE_BD) \





/// Like XR_LIST_ALL_STRUCTURE_TYPES, but only includes types whose parent struct type is XrCameraSupportedCapabilityBaseHeaderBD
#परिभाषय XR_LIST_ALL_CHILD_STRUCTURE_TYPES_Xr_Camera_Supported_Capability_आधारः_शीर्षकम्_BD(_avail, _unavail) \
    impl_XR_LIST_ALL_CHILD_STRUCTURE_TYPES_Xr_Camera_Supported_Capability_आधारः_शीर्षकम्_BD_CORE(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrCameraSupportedCapabilityBaseHeaderBD()
#परिभाषय impl_XR_LIST_ALL_CHILD_STRUCTURE_TYPES_Xr_Camera_Supported_Capability_आधारः_शीर्षकम्_BD_CORE(_avail, _unavail) \
    _avail(Xr_Camera_Supported_Capability_Image_Resolution_And_Frame_दरः_BD, XR_TYPE_CAMERA_SUPPORTED_CAPABILITY_IMAGE_RESOLUTION_AND_FRAME_दरः_BD) \
    _avail(Xr_Camera_Supported_Capability_दत्त_Transfer_Type_BD, XR_TYPE_CAMERA_SUPPORTED_CAPABILITY_दत्त_TRANSFER_TYPE_BD) \
    _avail(XrCameraSupportedCapabilityImageFormatBD, XR_TYPE_CAMERA_SUPPORTED_CAPABILITY_IMAGE_FORMAT_BD) \
    _avail(XrCameraSupportedCapabilityCameraModelBD, XR_TYPE_CAMERA_SUPPORTED_CAPABILITY_CAMERA_MODEL_BD) \





/// Like XR_LIST_ALL_STRUCTURE_TYPES, but only includes types whose parent struct type is XrCameraCapabilityBaseHeaderBD
#परिभाषय XR_LIST_ALL_CHILD_STRUCTURE_TYPES_Xr_Camera_Capability_आधारः_शीर्षकम्_BD(_avail, _unavail) \
    impl_XR_LIST_ALL_CHILD_STRUCTURE_TYPES_Xr_Camera_Capability_आधारः_शीर्षकम्_BD_CORE(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrCameraCapabilityBaseHeaderBD()
#परिभाषय impl_XR_LIST_ALL_CHILD_STRUCTURE_TYPES_Xr_Camera_Capability_आधारः_शीर्षकम्_BD_CORE(_avail, _unavail) \
    _avail(Xr_Camera_Capability_Image_Resolution_And_Frame_दरः_BD, XR_TYPE_CAMERA_CAPABILITY_IMAGE_RESOLUTION_AND_FRAME_दरः_BD) \
    _avail(Xr_Camera_Capability_दत्त_Transfer_Type_BD, XR_TYPE_CAMERA_CAPABILITY_दत्त_TRANSFER_TYPE_BD) \
    _avail(XrCameraCapabilityImageFormatBD, XR_TYPE_CAMERA_CAPABILITY_IMAGE_FORMAT_BD) \
    _avail(XrCameraCapabilityCameraModelBD, XR_TYPE_CAMERA_CAPABILITY_CAMERA_MODEL_BD) \





/// Like XR_LIST_ALL_STRUCTURE_TYPES, but only includes types whose parent struct type is XrCameraImageDataBaseHeaderBD
#परिभाषय XR_LIST_ALL_CHILD_STRUCTURE_TYPES_Xr_Camera_Image_दत्त_आधारः_शीर्षकम्_BD(_avail, _unavail) \
    impl_XR_LIST_ALL_CHILD_STRUCTURE_TYPES_Xr_Camera_Image_दत्त_आधारः_शीर्षकम्_BD_CORE(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrCameraImageDataBaseHeaderBD()
#परिभाषय impl_XR_LIST_ALL_CHILD_STRUCTURE_TYPES_Xr_Camera_Image_दत्त_आधारः_शीर्षकम्_BD_CORE(_avail, _unavail) \
    _avail(Xr_Camera_Image_दत्त_Raw_बफर_BD, XR_TYPE_CAMERA_IMAGE_दत्त_RAW_बफर_BD) \





/// Like XR_LIST_ALL_STRUCTURE_TYPES, but only includes types whose parent struct type is XrGoogleCloudAuthInfoBaseHeaderANDROID
#परिभाषय XR_LIST_ALL_CHILD_STRUCTURE_TYPES_Xr_Google_Cloud_Auth_Info_आधारः_शीर्षकम्_ANDROID(_avail, _unavail) \
    impl_XR_LIST_ALL_CHILD_STRUCTURE_TYPES_Xr_Google_Cloud_Auth_Info_आधारः_शीर्षकम्_ANDROID_CORE(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrGoogleCloudAuthInfoBaseHeaderANDROID()
#परिभाषय impl_XR_LIST_ALL_CHILD_STRUCTURE_TYPES_Xr_Google_Cloud_Auth_Info_आधारः_शीर्षकम्_ANDROID_CORE(_avail, _unavail) \
    _avail(Xr_Google_Cloud_Auth_Info_Api_कुञ्चिका_ANDROID, XR_TYPE_GOOGLE_CLOUD_AUTH_INFO_API_कुञ्चिका_ANDROID) \
    _avail(XrGoogleCloudAuthInfoTokenANDROID, XR_TYPE_GOOGLE_CLOUD_AUTH_INFO_TOKEN_ANDROID) \
    _avail(XrGoogleCloudAuthInfoKeylessANDROID, XR_TYPE_GOOGLE_CLOUD_AUTH_INFO_KEYLESS_ANDROID) \





#यदि_अन्तः

