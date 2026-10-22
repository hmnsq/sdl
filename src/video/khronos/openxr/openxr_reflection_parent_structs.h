#अगर_अघोषित OPENXR_REFLECTION_PARENT_STRUCTS_H_
#घोषणा OPENXR_REFLECTION_PARENT_STRUCTS_H_ 1

/*
** Copyright (c) 2017-2026 The Khronos Group Inc.
**
** SPDX-License-Identifier: Apache-2.0 OR MIT
*/

/*
** This header is generated from the Khronos OpenXR XML API Registry.
**
*/

#समावेश "openxr.h"

/*
This file contains expansion macros (X Macros) for OpenXR structures that have a parent type.
*/


/// Like XR_LIST_ALL_STRUCTURE_TYPES, but only includes types whose parent struct type is XrCompositionLayerBaseHeader
#घोषणा XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrCompositionLayerBaseHeader(_avail, _unavail) \
    _impl_XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrCompositionLayerBaseHeader_CORE(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrCompositionLayerBaseHeader()
#घोषणा _impl_XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrCompositionLayerBaseHeader_CORE(_avail, _unavail) \
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
#घोषणा XR_LIST_ALL_CHILD_STRUCTURE_TYPES_Xr_Event_तथ्य_Base_Header(_avail, _unavail) \
    impl_XR_LIST_ALL_CHILD_STRUCTURE_TYPES_Xr_Event_तथ्य_Base_Header_CORE(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrEventDataBaseHeader()
#घोषणा impl_XR_LIST_ALL_CHILD_STRUCTURE_TYPES_Xr_Event_तथ्य_Base_Header_CORE(_avail, _unavail) \
    _avail(Xr_Event_तथ्य_Events_Lost, XR_TYPE_EVENT_तथ्य_EVENTS_LOST) \
    _avail(Xr_Event_तथ्य_Instance_Loss_Pending, XR_TYPE_EVENT_तथ्य_INSTANCE_LOSS_PENDING) \
    _avail(Xr_Event_तथ्य_Session_State_Changed, XR_TYPE_EVENT_तथ्य_SESSION_STATE_CHANGED) \
    _avail(Xr_Event_तथ्य_Reference_Space_Change_Pending, XR_TYPE_EVENT_तथ्य_REFERENCE_SPACE_CHANGE_PENDING) \
    _avail(Xr_Event_तथ्य_Interaction_Profile_Changed, XR_TYPE_EVENT_तथ्य_INTERACTION_PROFILE_CHANGED) \
    _avail(Xr_Event_तथ्य_Visibility_Mask_Changed_KHR, XR_TYPE_EVENT_तथ्य_VISIBILITY_MASK_CHANGED_KHR) \
    _avail(Xr_Event_तथ्य_Perf_Settings_EXT, XR_TYPE_EVENT_तथ्य_PERF_SETTINGS_EXT) \
    _avail(Xr_Event_तथ्य_Main_Session_Visibility_Changed_EXTX, XR_TYPE_EVENT_तथ्य_MAIN_SESSION_VISIBILITY_CHANGED_EXTX) \
    _avail(Xr_Event_तथ्य_Display_Refresh_Rate_Changed_FB, XR_TYPE_EVENT_तथ्य_DISPLAY_REFRESH_RATE_CHANGED_FB) \
    _avail(Xr_Event_तथ्य_Vive_Tracker_Connected_HTCX, XR_TYPE_EVENT_तथ्य_VIVE_TRACKER_CONNECTED_HTCX) \
    _avail(Xr_Event_तथ्य_Spatial_Anchor_Create_Complete_FB, XR_TYPE_EVENT_तथ्य_SPATIAL_ANCHOR_CREATE_COMPLETE_FB) \
    _avail(Xr_Event_तथ्य_Space_Set_Status_Complete_FB, XR_TYPE_EVENT_तथ्य_SPACE_SET_STATUS_COMPLETE_FB) \
    _avail(Xr_Event_तथ्य_Passthrough_State_Changed_FB, XR_TYPE_EVENT_तथ्य_PASSTHROUGH_STATE_CHANGED_FB) \
    _avail(Xr_Event_तथ्य_Marker_Tracking_Update_VARJO, XR_TYPE_EVENT_तथ्य_MARKER_TRACKING_UPDATE_VARJO) \
    _avail(Xr_Event_तथ्य_Localization_Changed_ML, XR_TYPE_EVENT_तथ्य_LOCALIZATION_CHANGED_ML) \
    _avail(Xr_Event_तथ्य_Space_Query_Results_Available_FB, XR_TYPE_EVENT_तथ्य_SPACE_QUERY_RESULTS_AVAILABLE_FB) \
    _avail(Xr_Event_तथ्य_Space_Query_Complete_FB, XR_TYPE_EVENT_तथ्य_SPACE_QUERY_COMPLETE_FB) \
    _avail(Xr_Event_तथ्य_Space_Save_Complete_FB, XR_TYPE_EVENT_तथ्य_SPACE_SAVE_COMPLETE_FB) \
    _avail(Xr_Event_तथ्य_Space_Erase_Complete_FB, XR_TYPE_EVENT_तथ्य_SPACE_ERASE_COMPLETE_FB) \
    _avail(Xr_Event_तथ्य_Space_Share_Complete_FB, XR_TYPE_EVENT_तथ्य_SPACE_SHARE_COMPLETE_FB) \
    _avail(Xr_Event_तथ्य_Scene_Capture_Complete_FB, XR_TYPE_EVENT_तथ्य_SCENE_CAPTURE_COMPLETE_FB) \
    _avail(Xr_Event_तथ्य_Virtual_Keyboard_Commit_Text_META, XR_TYPE_EVENT_तथ्य_VIRTUAL_KEYBOARD_COMMIT_TEXT_META) \
    _avail(Xr_Event_तथ्य_Virtual_Keyboard_Backspace_META, XR_TYPE_EVENT_तथ्य_VIRTUAL_KEYBOARD_BACKSPACE_META) \
    _avail(Xr_Event_तथ्य_Virtual_Keyboard_Enter_META, XR_TYPE_EVENT_तथ्य_VIRTUAL_KEYBOARD_ENTER_META) \
    _avail(Xr_Event_तथ्य_Virtual_Keyboard_Shown_META, XR_TYPE_EVENT_तथ्य_VIRTUAL_KEYBOARD_SHOWN_META) \
    _avail(Xr_Event_तथ्य_Virtual_Keyboard_Hidden_META, XR_TYPE_EVENT_तथ्य_VIRTUAL_KEYBOARD_HIDDEN_META) \
    _avail(Xr_Event_तथ्य_Space_List_Save_Complete_FB, XR_TYPE_EVENT_तथ्य_SPACE_LIST_SAVE_COMPLETE_FB) \
    _avail(Xr_Event_तथ्य_Space_Discovery_Results_Available_META, XR_TYPE_EVENT_तथ्य_SPACE_DISCOVERY_RESULTS_AVAILABLE_META) \
    _avail(Xr_Event_तथ्य_Space_Discovery_Complete_META, XR_TYPE_EVENT_तथ्य_SPACE_DISCOVERY_COMPLETE_META) \
    _avail(Xr_Event_तथ्य_Spaces_Save_परिणाम_META, XR_TYPE_EVENT_तथ्य_SPACES_SAVE_परिणाम_META) \
    _avail(Xr_Event_तथ्य_Spaces_Erase_परिणाम_META, XR_TYPE_EVENT_तथ्य_SPACES_ERASE_परिणाम_META) \
    _avail(Xr_Event_तथ्य_Passthrough_Layer_Resumed_META, XR_TYPE_EVENT_तथ्य_PASSTHROUGH_LAYER_RESUMED_META) \
    _avail(Xr_Event_तथ्य_Share_Spaces_Complete_META, XR_TYPE_EVENT_तथ्य_SHARE_SPACES_COMPLETE_META) \
    _avail(Xr_Event_तथ्य_Interaction_Render_Models_Changed_EXT, XR_TYPE_EVENT_तथ्य_INTERACTION_RENDER_MODELS_CHANGED_EXT) \
    _avail(Xr_Event_तथ्य_Sense_तथ्य_Provider_State_Changed_BD, XR_TYPE_EVENT_तथ्य_SENSE_तथ्य_PROVIDER_STATE_CHANGED_BD) \
    _avail(Xr_Event_तथ्य_Sense_तथ्य_Updated_BD, XR_TYPE_EVENT_तथ्य_SENSE_तथ्य_UPDATED_BD) \
    _avail(Xr_Event_तथ्य_Recommended_Resolution_Changed_ANDROID, XR_TYPE_EVENT_तथ्य_RECOMMENDED_RESOLUTION_CHANGED_ANDROID) \
    _avail(Xr_Event_तथ्य_User_Presence_Changed_EXT, XR_TYPE_EVENT_तथ्य_USER_PRESENCE_CHANGED_EXT) \
    _avail(Xr_Event_तथ्य_Headset_Fit_Changed_ML, XR_TYPE_EVENT_तथ्य_HEADSET_FIT_CHANGED_ML) \
    _avail(Xr_Event_तथ्य_Eye_Calibration_Changed_ML, XR_TYPE_EVENT_तथ्य_EYE_CALIBRATION_CHANGED_ML) \
    _avail(Xr_Event_तथ्य_Boundary_Visibility_Changed_META, XR_TYPE_EVENT_तथ्य_BOUNDARY_VISIBILITY_CHANGED_META) \
    _avail(Xr_Event_तथ्य_Start_Colocation_Advertisement_Complete_META, XR_TYPE_EVENT_तथ्य_START_COLOCATION_ADVERTISEMENT_COMPLETE_META) \
    _avail(Xr_Event_तथ्य_Stop_Colocation_Advertisement_Complete_META, XR_TYPE_EVENT_तथ्य_STOP_COLOCATION_ADVERTISEMENT_COMPLETE_META) \
    _avail(Xr_Event_तथ्य_Colocation_Advertisement_Complete_META, XR_TYPE_EVENT_तथ्य_COLOCATION_ADVERTISEMENT_COMPLETE_META) \
    _avail(Xr_Event_तथ्य_Start_Colocation_Discovery_Complete_META, XR_TYPE_EVENT_तथ्य_START_COLOCATION_DISCOVERY_COMPLETE_META) \
    _avail(Xr_Event_तथ्य_Colocation_Discovery_परिणाम_META, XR_TYPE_EVENT_तथ्य_COLOCATION_DISCOVERY_परिणाम_META) \
    _avail(Xr_Event_तथ्य_Colocation_Discovery_Complete_META, XR_TYPE_EVENT_तथ्य_COLOCATION_DISCOVERY_COMPLETE_META) \
    _avail(Xr_Event_तथ्य_Stop_Colocation_Discovery_Complete_META, XR_TYPE_EVENT_तथ्य_STOP_COLOCATION_DISCOVERY_COMPLETE_META) \
    _avail(Xr_Event_तथ्य_Image_Tracking_Lost_ANDROID, XR_TYPE_EVENT_तथ्य_IMAGE_TRACKING_LOST_ANDROID) \
    _avail(Xr_Event_तथ्य_Spatial_Discovery_Recommended_EXT, XR_TYPE_EVENT_तथ्य_SPATIAL_DISCOVERY_RECOMMENDED_EXT) \
    _avail(Xr_Event_तथ्य_Geospatial_Tracker_State_Changed_ANDROID, XR_TYPE_EVENT_तथ्य_GEOSPATIAL_TRACKER_STATE_CHANGED_ANDROID) \
    _avail(Xr_Event_तथ्य_Spatial_Container_Closed_EXT, XR_TYPE_EVENT_तथ्य_SPATIAL_CONTAINER_CLOSED_EXT) \
    _avail(Xr_Event_तथ्य_Spatial_Container_Bounds_Changed_EXT, XR_TYPE_EVENT_तथ्य_SPATIAL_CONTAINER_BOUNDS_CHANGED_EXT) \
    _avail(Xr_Event_तथ्य_Spatial_Container_Visible_Changed_EXT, XR_TYPE_EVENT_तथ्य_SPATIAL_CONTAINER_VISIBLE_CHANGED_EXT) \
    _avail(Xr_Event_तथ्य_Spatial_Container_Visible_Request_Denied_EXT, XR_TYPE_EVENT_तथ्य_SPATIAL_CONTAINER_VISIBLE_REQUEST_DENIED_EXT) \
    _avail(Xr_Event_तथ्य_Spatial_Container_Interactable_Changed_EXT, XR_TYPE_EVENT_तथ्य_SPATIAL_CONTAINER_INTERACTABLE_CHANGED_EXT) \
    _avail(Xr_Event_तथ्य_Spatial_Container_Bounds_Mode_Request_Denied_EXT, XR_TYPE_EVENT_तथ्य_SPATIAL_CONTAINER_BOUNDS_MODE_REQUEST_DENIED_EXT) \
    _avail(Xr_Event_तथ्य_View_Configuration_Views_Changed_EXT, XR_TYPE_EVENT_तथ्य_VIEW_CONFIGURATION_VIEWS_CHANGED_EXT) \





/// Like XR_LIST_ALL_STRUCTURE_TYPES, but only includes types whose parent struct type is XrHapticBaseHeader
#घोषणा XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrHapticBaseHeader(_avail, _unavail) \
    _impl_XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrHapticBaseHeader_CORE(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrHapticBaseHeader()
#घोषणा _impl_XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrHapticBaseHeader_CORE(_avail, _unavail) \
    _avail(XrHapticVibration, XR_TYPE_HAPTIC_VIBRATION) \
    _avail(XrHapticAmplitudeEnvelopeVibrationFB, XR_TYPE_HAPTIC_AMPLITUDE_ENVELOPE_VIBRATION_FB) \
    _avail(XrHapticPcmVibrationFB, XR_TYPE_HAPTIC_PCM_VIBRATION_FB) \
    _avail(XrHapticParametricVibrationEXT, XR_TYPE_HAPTIC_PARAMETRIC_VIBRATION_EXT) \





/// Like XR_LIST_ALL_STRUCTURE_TYPES, but only includes types whose parent struct type is XrSwapchainImageBaseHeader
#घोषणा XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrSwapchainImageBaseHeader(_avail, _unavail) \
    _impl_XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrSwapchainImageBaseHeader_CORE(_avail, _unavail) \
    _impl_XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrSwapchainImageBaseHeader_XR_USE_GRAPHICS_API_D3D11(_avail, _unavail) \
    _impl_XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrSwapchainImageBaseHeader_XR_USE_GRAPHICS_API_D3D12(_avail, _unavail) \
    _impl_XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrSwapchainImageBaseHeader_XR_USE_GRAPHICS_API_METAL(_avail, _unavail) \
    _impl_XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrSwapchainImageBaseHeader_XR_USE_GRAPHICS_API_OPENGL(_avail, _unavail) \
    _impl_XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrSwapchainImageBaseHeader_XR_USE_GRAPHICS_API_OPENGL_ES(_avail, _unavail) \
    _impl_XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrSwapchainImageBaseHeader_XR_USE_GRAPHICS_API_VULKAN(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrSwapchainImageBaseHeader()
#घोषणा _impl_XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrSwapchainImageBaseHeader_CORE(_avail, _unavail) \


#अगर defined(XR_USE_GRAPHICS_API_D3D11)
#घोषणा _impl_XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrSwapchainImageBaseHeader_XR_USE_GRAPHICS_API_D3D11(_avail, _unavail) \
    _avail(XrSwapchainImageD3D11KHR, XR_TYPE_SWAPCHAIN_IMAGE_D3D11_KHR) \

#अन्यथा
#घोषणा _impl_XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrSwapchainImageBaseHeader_XR_USE_GRAPHICS_API_D3D11(_avail, _unavail) \
    _unavail(XrSwapchainImageD3D11KHR, XR_TYPE_SWAPCHAIN_IMAGE_D3D11_KHR) \

#पूर्ण_अगर

#अगर defined(XR_USE_GRAPHICS_API_D3D12)
#घोषणा _impl_XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrSwapchainImageBaseHeader_XR_USE_GRAPHICS_API_D3D12(_avail, _unavail) \
    _avail(XrSwapchainImageD3D12KHR, XR_TYPE_SWAPCHAIN_IMAGE_D3D12_KHR) \

#अन्यथा
#घोषणा _impl_XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrSwapchainImageBaseHeader_XR_USE_GRAPHICS_API_D3D12(_avail, _unavail) \
    _unavail(XrSwapchainImageD3D12KHR, XR_TYPE_SWAPCHAIN_IMAGE_D3D12_KHR) \

#पूर्ण_अगर

#अगर defined(XR_USE_GRAPHICS_API_METAL)
#घोषणा _impl_XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrSwapchainImageBaseHeader_XR_USE_GRAPHICS_API_METAL(_avail, _unavail) \
    _avail(XrSwapchainImageMetalKHR, XR_TYPE_SWAPCHAIN_IMAGE_METAL_KHR) \

#अन्यथा
#घोषणा _impl_XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrSwapchainImageBaseHeader_XR_USE_GRAPHICS_API_METAL(_avail, _unavail) \
    _unavail(XrSwapchainImageMetalKHR, XR_TYPE_SWAPCHAIN_IMAGE_METAL_KHR) \

#पूर्ण_अगर

#अगर defined(XR_USE_GRAPHICS_API_OPENGL)
#घोषणा _impl_XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrSwapchainImageBaseHeader_XR_USE_GRAPHICS_API_OPENGL(_avail, _unavail) \
    _avail(XrSwapchainImageOpenGLKHR, XR_TYPE_SWAPCHAIN_IMAGE_OPENGL_KHR) \

#अन्यथा
#घोषणा _impl_XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrSwapchainImageBaseHeader_XR_USE_GRAPHICS_API_OPENGL(_avail, _unavail) \
    _unavail(XrSwapchainImageOpenGLKHR, XR_TYPE_SWAPCHAIN_IMAGE_OPENGL_KHR) \

#पूर्ण_अगर

#अगर defined(XR_USE_GRAPHICS_API_OPENGL_ES)
#घोषणा _impl_XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrSwapchainImageBaseHeader_XR_USE_GRAPHICS_API_OPENGL_ES(_avail, _unavail) \
    _avail(XrSwapchainImageOpenGLESKHR, XR_TYPE_SWAPCHAIN_IMAGE_OPENGL_ES_KHR) \

#अन्यथा
#घोषणा _impl_XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrSwapchainImageBaseHeader_XR_USE_GRAPHICS_API_OPENGL_ES(_avail, _unavail) \
    _unavail(XrSwapchainImageOpenGLESKHR, XR_TYPE_SWAPCHAIN_IMAGE_OPENGL_ES_KHR) \

#पूर्ण_अगर

#अगर defined(XR_USE_GRAPHICS_API_VULKAN)
#घोषणा _impl_XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrSwapchainImageBaseHeader_XR_USE_GRAPHICS_API_VULKAN(_avail, _unavail) \
    _avail(XrSwapchainImageVulkanKHR, XR_TYPE_SWAPCHAIN_IMAGE_VULKAN_KHR) \

#अन्यथा
#घोषणा _impl_XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrSwapchainImageBaseHeader_XR_USE_GRAPHICS_API_VULKAN(_avail, _unavail) \
    _unavail(XrSwapchainImageVulkanKHR, XR_TYPE_SWAPCHAIN_IMAGE_VULKAN_KHR) \

#पूर्ण_अगर




/// Like XR_LIST_ALL_STRUCTURE_TYPES, but only includes types whose parent struct type is XrLoaderInitInfoBaseHeaderKHR
#घोषणा XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrLoaderInitInfoBaseHeaderKHR(_avail, _unavail) \
    _impl_XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrLoaderInitInfoBaseHeaderKHR_CORE(_avail, _unavail) \
    _impl_XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrLoaderInitInfoBaseHeaderKHR_XR_USE_PLATFORM_ANDROID(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrLoaderInitInfoBaseHeaderKHR()
#घोषणा _impl_XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrLoaderInitInfoBaseHeaderKHR_CORE(_avail, _unavail) \
    _avail(XrLoaderInitInfoPropertiesEXT, XR_TYPE_LOADER_INIT_INFO_PROPERTIES_EXT) \


#अगर defined(XR_USE_PLATFORM_ANDROID)
#घोषणा _impl_XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrLoaderInitInfoBaseHeaderKHR_XR_USE_PLATFORM_ANDROID(_avail, _unavail) \
    _avail(XrLoaderInitInfoAndroidKHR, XR_TYPE_LOADER_INIT_INFO_ANDROID_KHR) \

#अन्यथा
#घोषणा _impl_XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrLoaderInitInfoBaseHeaderKHR_XR_USE_PLATFORM_ANDROID(_avail, _unavail) \
    _unavail(XrLoaderInitInfoAndroidKHR, XR_TYPE_LOADER_INIT_INFO_ANDROID_KHR) \

#पूर्ण_अगर




/// Like XR_LIST_ALL_STRUCTURE_TYPES, but only includes types whose parent struct type is XrBindingModificationBaseHeaderKHR
#घोषणा XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrBindingModificationBaseHeaderKHR(_avail, _unavail) \
    _impl_XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrBindingModificationBaseHeaderKHR_CORE(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrBindingModificationBaseHeaderKHR()
#घोषणा _impl_XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrBindingModificationBaseHeaderKHR_CORE(_avail, _unavail) \
    _avail(XrInteractionProfileDpadBindingEXT, XR_TYPE_INTERACTION_PROFILE_DPAD_BINDING_EXT) \
    _avail(XrInteractionProfileAnalogThresholdVALVE, XR_TYPE_INTERACTION_PROFILE_ANALOG_THRESHOLD_VALVE) \





/// Like XR_LIST_ALL_STRUCTURE_TYPES, but only includes types whose parent struct type is XrSwapchainStateBaseHeaderFB
#घोषणा XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrSwapchainStateBaseHeaderFB(_avail, _unavail) \
    _impl_XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrSwapchainStateBaseHeaderFB_CORE(_avail, _unavail) \
    _impl_XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrSwapchainStateBaseHeaderFB_XR_USE_GRAPHICS_API_OPENGL_ES(_avail, _unavail) \
    _impl_XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrSwapchainStateBaseHeaderFB_XR_USE_GRAPHICS_API_VULKAN(_avail, _unavail) \
    _impl_XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrSwapchainStateBaseHeaderFB_XR_USE_PLATFORM_ANDROID(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrSwapchainStateBaseHeaderFB()
#घोषणा _impl_XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrSwapchainStateBaseHeaderFB_CORE(_avail, _unavail) \
    _avail(XrSwapchainStateFoveationFB, XR_TYPE_SWAPCHAIN_STATE_FOVEATION_FB) \


#अगर defined(XR_USE_GRAPHICS_API_OPENGL_ES)
#घोषणा _impl_XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrSwapchainStateBaseHeaderFB_XR_USE_GRAPHICS_API_OPENGL_ES(_avail, _unavail) \
    _avail(XrSwapchainStateSamplerOpenGLESFB, XR_TYPE_SWAPCHAIN_STATE_SAMPLER_OPENGL_ES_FB) \

#अन्यथा
#घोषणा _impl_XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrSwapchainStateBaseHeaderFB_XR_USE_GRAPHICS_API_OPENGL_ES(_avail, _unavail) \
    _unavail(XrSwapchainStateSamplerOpenGLESFB, XR_TYPE_SWAPCHAIN_STATE_SAMPLER_OPENGL_ES_FB) \

#पूर्ण_अगर

#अगर defined(XR_USE_GRAPHICS_API_VULKAN)
#घोषणा _impl_XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrSwapchainStateBaseHeaderFB_XR_USE_GRAPHICS_API_VULKAN(_avail, _unavail) \
    _avail(XrSwapchainStateSamplerVulkanFB, XR_TYPE_SWAPCHAIN_STATE_SAMPLER_VULKAN_FB) \

#अन्यथा
#घोषणा _impl_XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrSwapchainStateBaseHeaderFB_XR_USE_GRAPHICS_API_VULKAN(_avail, _unavail) \
    _unavail(XrSwapchainStateSamplerVulkanFB, XR_TYPE_SWAPCHAIN_STATE_SAMPLER_VULKAN_FB) \

#पूर्ण_अगर

#अगर defined(XR_USE_PLATFORM_ANDROID)
#घोषणा _impl_XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrSwapchainStateBaseHeaderFB_XR_USE_PLATFORM_ANDROID(_avail, _unavail) \
    _avail(XrSwapchainStateAndroidSurfaceDimensionsFB, XR_TYPE_SWAPCHAIN_STATE_ANDROID_SURFACE_DIMENSIONS_FB) \

#अन्यथा
#घोषणा _impl_XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrSwapchainStateBaseHeaderFB_XR_USE_PLATFORM_ANDROID(_avail, _unavail) \
    _unavail(XrSwapchainStateAndroidSurfaceDimensionsFB, XR_TYPE_SWAPCHAIN_STATE_ANDROID_SURFACE_DIMENSIONS_FB) \

#पूर्ण_अगर




/// Like XR_LIST_ALL_STRUCTURE_TYPES, but only includes types whose parent struct type is XrSpatialAnchorsCreateInfoBaseHeaderML
#घोषणा XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrSpatialAnchorsCreateInfoBaseHeaderML(_avail, _unavail) \
    _impl_XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrSpatialAnchorsCreateInfoBaseHeaderML_CORE(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrSpatialAnchorsCreateInfoBaseHeaderML()
#घोषणा _impl_XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrSpatialAnchorsCreateInfoBaseHeaderML_CORE(_avail, _unavail) \
    _avail(XrSpatialAnchorsCreateInfoFromPoseML, XR_TYPE_SPATIAL_ANCHORS_CREATE_INFO_FROM_POSE_ML) \
    _avail(XrSpatialAnchorsCreateInfoFromUuidsML, XR_TYPE_SPATIAL_ANCHORS_CREATE_INFO_FROM_UUIDS_ML) \





/// Like XR_LIST_ALL_STRUCTURE_TYPES, but only includes types whose parent struct type is XrFutureCompletionBaseHeaderEXT
#घोषणा XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrFutureCompletionBaseHeaderEXT(_avail, _unavail) \
    _impl_XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrFutureCompletionBaseHeaderEXT_CORE(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrFutureCompletionBaseHeaderEXT()
#घोषणा _impl_XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrFutureCompletionBaseHeaderEXT_CORE(_avail, _unavail) \
    _avail(XrCreateSpatialAnchorsCompletionML, XR_TYPE_CREATE_SPATIAL_ANCHORS_COMPLETION_ML) \
    _avail(XrSpatialAnchorsQueryCompletionML, XR_TYPE_SPATIAL_ANCHORS_QUERY_COMPLETION_ML) \
    _avail(XrSpatialAnchorsPublishCompletionML, XR_TYPE_SPATIAL_ANCHORS_PUBLISH_COMPLETION_ML) \
    _avail(XrSpatialAnchorsDeleteCompletionML, XR_TYPE_SPATIAL_ANCHORS_DELETE_COMPLETION_ML) \
    _avail(XrSpatialAnchorsUpdateExpirationCompletionML, XR_TYPE_SPATIAL_ANCHORS_UPDATE_EXPIRATION_COMPLETION_ML) \
    _avail(Xr_Sense_तथ्य_Query_Completion_BD, XR_TYPE_SENSE_तथ्य_QUERY_COMPLETION_BD) \
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
#घोषणा XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrSpatialAnchorsQueryInfoBaseHeaderML(_avail, _unavail) \
    _impl_XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrSpatialAnchorsQueryInfoBaseHeaderML_CORE(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrSpatialAnchorsQueryInfoBaseHeaderML()
#घोषणा _impl_XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrSpatialAnchorsQueryInfoBaseHeaderML_CORE(_avail, _unavail) \
    _avail(XrSpatialAnchorsQueryInfoRadiusML, XR_TYPE_SPATIAL_ANCHORS_QUERY_INFO_RADIUS_ML) \





/// Like XR_LIST_ALL_STRUCTURE_TYPES, but only includes types whose parent struct type is XrSpaceQueryInfoBaseHeaderFB
#घोषणा XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrSpaceQueryInfoBaseHeaderFB(_avail, _unavail) \
    _impl_XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrSpaceQueryInfoBaseHeaderFB_CORE(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrSpaceQueryInfoBaseHeaderFB()
#घोषणा _impl_XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrSpaceQueryInfoBaseHeaderFB_CORE(_avail, _unavail) \
    _avail(XrSpaceQueryInfoFB, XR_TYPE_SPACE_QUERY_INFO_FB) \





/// Like XR_LIST_ALL_STRUCTURE_TYPES, but only includes types whose parent struct type is XrSpaceFilterInfoBaseHeaderFB
#घोषणा XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrSpaceFilterInfoBaseHeaderFB(_avail, _unavail) \
    _impl_XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrSpaceFilterInfoBaseHeaderFB_CORE(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrSpaceFilterInfoBaseHeaderFB()
#घोषणा _impl_XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrSpaceFilterInfoBaseHeaderFB_CORE(_avail, _unavail) \
    _avail(XrSpaceUuidFilterInfoFB, XR_TYPE_SPACE_UUID_FILTER_INFO_FB) \
    _avail(XrSpaceComponentFilterInfoFB, XR_TYPE_SPACE_COMPONENT_FILTER_INFO_FB) \





/// Like XR_LIST_ALL_STRUCTURE_TYPES, but only includes types whose parent struct type is XrSpaceFilterBaseHeaderMETA
#घोषणा XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrSpaceFilterBaseHeaderMETA(_avail, _unavail) \
    _impl_XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrSpaceFilterBaseHeaderMETA_CORE(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrSpaceFilterBaseHeaderMETA()
#घोषणा _impl_XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrSpaceFilterBaseHeaderMETA_CORE(_avail, _unavail) \
    _avail(XrSpaceFilterUuidMETA, XR_TYPE_SPACE_FILTER_UUID_META) \
    _avail(XrSpaceFilterComponentMETA, XR_TYPE_SPACE_FILTER_COMPONENT_META) \





/// Like XR_LIST_ALL_STRUCTURE_TYPES, but only includes types whose parent struct type is XrShareSpacesRecipientBaseHeaderMETA
#घोषणा XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrShareSpacesRecipientBaseHeaderMETA(_avail, _unavail) \
    _impl_XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrShareSpacesRecipientBaseHeaderMETA_CORE(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrShareSpacesRecipientBaseHeaderMETA()
#घोषणा _impl_XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrShareSpacesRecipientBaseHeaderMETA_CORE(_avail, _unavail) \
    _avail(XrShareSpacesRecipientGroupsMETA, XR_TYPE_SHARE_SPACES_RECIPIENT_GROUPS_META) \





/// Like XR_LIST_ALL_STRUCTURE_TYPES, but only includes types whose parent struct type is XrEnvironmentRaycastFilterBaseHeaderMETA
#घोषणा XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrEnvironmentRaycastFilterBaseHeaderMETA(_avail, _unavail) \
    _impl_XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrEnvironmentRaycastFilterBaseHeaderMETA_CORE(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrEnvironmentRaycastFilterBaseHeaderMETA()
#घोषणा _impl_XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrEnvironmentRaycastFilterBaseHeaderMETA_CORE(_avail, _unavail) \
    _avail(XrEnvironmentRaycastFilterDistanceMETA, XR_TYPE_ENVIRONMENT_RAYCAST_FILTER_DISTANCE_META) \





/// Like XR_LIST_ALL_STRUCTURE_TYPES, but only includes types whose parent struct type is XrSpatialCapabilityConfigurationBaseHeaderEXT
#घोषणा XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrSpatialCapabilityConfigurationBaseHeaderEXT(_avail, _unavail) \
    _impl_XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrSpatialCapabilityConfigurationBaseHeaderEXT_CORE(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrSpatialCapabilityConfigurationBaseHeaderEXT()
#घोषणा _impl_XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrSpatialCapabilityConfigurationBaseHeaderEXT_CORE(_avail, _unavail) \
    _avail(XrSpatialCapabilityConfigurationPlaneTrackingEXT, XR_TYPE_SPATIAL_CAPABILITY_CONFIGURATION_PLANE_TRACKING_EXT) \
    _avail(XrSpatialCapabilityConfigurationQrCodeEXT, XR_TYPE_SPATIAL_CAPABILITY_CONFIGURATION_QR_CODE_EXT) \
    _avail(XrSpatialCapabilityConfigurationMicroQrCodeEXT, XR_TYPE_SPATIAL_CAPABILITY_CONFIGURATION_MICRO_QR_CODE_EXT) \
    _avail(XrSpatialCapabilityConfigurationArucoMarkerEXT, XR_TYPE_SPATIAL_CAPABILITY_CONFIGURATION_ARUCO_MARKER_EXT) \
    _avail(XrSpatialCapabilityConfigurationAprilTagEXT, XR_TYPE_SPATIAL_CAPABILITY_CONFIGURATION_APRIL_TAG_EXT) \
    _avail(XrSpatialCapabilityConfigurationObjectTrackingEXT, XR_TYPE_SPATIAL_CAPABILITY_CONFIGURATION_OBJECT_TRACKING_EXT) \
    _avail(XrSpatialCapabilityConfigurationAnchorEXT, XR_TYPE_SPATIAL_CAPABILITY_CONFIGURATION_ANCHOR_EXT) \
    _avail(XrSpatialCapabilityConfigurationImageTrackingEXT, XR_TYPE_SPATIAL_CAPABILITY_CONFIGURATION_IMAGE_TRACKING_EXT) \
    _avail(XrSpatialCapabilityConfigurationMeshTrackingEXT, XR_TYPE_SPATIAL_CAPABILITY_CONFIGURATION_MESH_TRACKING_EXT) \
    _avail(XrSpatialCapabilityConfigurationObjectTrackingANDROID, XR_TYPE_SPATIAL_CAPABILITY_CONFIGURATION_OBJECT_TRACKING_ANDROID) \
    _avail(XrSpatialCapabilityConfigurationDepthRaycastANDROID, XR_TYPE_SPATIAL_CAPABILITY_CONFIGURATION_DEPTH_RAYCAST_ANDROID) \





/// Like XR_LIST_ALL_STRUCTURE_TYPES, but only includes types whose parent struct type is XrCameraPropertyBaseHeaderBD
#घोषणा XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrCameraPropertyBaseHeaderBD(_avail, _unavail) \
    _impl_XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrCameraPropertyBaseHeaderBD_CORE(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrCameraPropertyBaseHeaderBD()
#घोषणा _impl_XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrCameraPropertyBaseHeaderBD_CORE(_avail, _unavail) \
    _avail(XrCameraPropertyFacingBD, XR_TYPE_CAMERA_PROPERTY_FACING_BD) \
    _avail(XrCameraPropertyPositionBD, XR_TYPE_CAMERA_PROPERTY_POSITION_BD) \
    _avail(XrCameraPropertyCameraTypeBD, XR_TYPE_CAMERA_PROPERTY_CAMERA_TYPE_BD) \





/// Like XR_LIST_ALL_STRUCTURE_TYPES, but only includes types whose parent struct type is XrCameraSupportedCapabilityBaseHeaderBD
#घोषणा XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrCameraSupportedCapabilityBaseHeaderBD(_avail, _unavail) \
    _impl_XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrCameraSupportedCapabilityBaseHeaderBD_CORE(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrCameraSupportedCapabilityBaseHeaderBD()
#घोषणा _impl_XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrCameraSupportedCapabilityBaseHeaderBD_CORE(_avail, _unavail) \
    _avail(XrCameraSupportedCapabilityImageResolutionAndFrameRateBD, XR_TYPE_CAMERA_SUPPORTED_CAPABILITY_IMAGE_RESOLUTION_AND_FRAME_RATE_BD) \
    _avail(Xr_Camera_Supported_Capability_तथ्य_Transfer_Type_BD, XR_TYPE_CAMERA_SUPPORTED_CAPABILITY_तथ्य_TRANSFER_TYPE_BD) \
    _avail(XrCameraSupportedCapabilityImageFormatBD, XR_TYPE_CAMERA_SUPPORTED_CAPABILITY_IMAGE_FORMAT_BD) \
    _avail(XrCameraSupportedCapabilityCameraModelBD, XR_TYPE_CAMERA_SUPPORTED_CAPABILITY_CAMERA_MODEL_BD) \





/// Like XR_LIST_ALL_STRUCTURE_TYPES, but only includes types whose parent struct type is XrCameraCapabilityBaseHeaderBD
#घोषणा XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrCameraCapabilityBaseHeaderBD(_avail, _unavail) \
    _impl_XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrCameraCapabilityBaseHeaderBD_CORE(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrCameraCapabilityBaseHeaderBD()
#घोषणा _impl_XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrCameraCapabilityBaseHeaderBD_CORE(_avail, _unavail) \
    _avail(XrCameraCapabilityImageResolutionAndFrameRateBD, XR_TYPE_CAMERA_CAPABILITY_IMAGE_RESOLUTION_AND_FRAME_RATE_BD) \
    _avail(Xr_Camera_Capability_तथ्य_Transfer_Type_BD, XR_TYPE_CAMERA_CAPABILITY_तथ्य_TRANSFER_TYPE_BD) \
    _avail(XrCameraCapabilityImageFormatBD, XR_TYPE_CAMERA_CAPABILITY_IMAGE_FORMAT_BD) \
    _avail(XrCameraCapabilityCameraModelBD, XR_TYPE_CAMERA_CAPABILITY_CAMERA_MODEL_BD) \





/// Like XR_LIST_ALL_STRUCTURE_TYPES, but only includes types whose parent struct type is XrCameraImageDataBaseHeaderBD
#घोषणा XR_LIST_ALL_CHILD_STRUCTURE_TYPES_Xr_Camera_Image_तथ्य_Base_Header_BD(_avail, _unavail) \
    impl_XR_LIST_ALL_CHILD_STRUCTURE_TYPES_Xr_Camera_Image_तथ्य_Base_Header_BD_CORE(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrCameraImageDataBaseHeaderBD()
#घोषणा impl_XR_LIST_ALL_CHILD_STRUCTURE_TYPES_Xr_Camera_Image_तथ्य_Base_Header_BD_CORE(_avail, _unavail) \
    _avail(Xr_Camera_Image_तथ्य_Raw_बफर_BD, XR_TYPE_CAMERA_IMAGE_तथ्य_RAW_बफर_BD) \





/// Like XR_LIST_ALL_STRUCTURE_TYPES, but only includes types whose parent struct type is XrGoogleCloudAuthInfoBaseHeaderANDROID
#घोषणा XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrGoogleCloudAuthInfoBaseHeaderANDROID(_avail, _unavail) \
    _impl_XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrGoogleCloudAuthInfoBaseHeaderANDROID_CORE(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrGoogleCloudAuthInfoBaseHeaderANDROID()
#घोषणा _impl_XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrGoogleCloudAuthInfoBaseHeaderANDROID_CORE(_avail, _unavail) \
    _avail(Xr_Google_Cloud_Auth_Info_Api_कुंजी_ANDROID, XR_TYPE_GOOGLE_CLOUD_AUTH_INFO_API_कुंजी_ANDROID) \
    _avail(XrGoogleCloudAuthInfoTokenANDROID, XR_TYPE_GOOGLE_CLOUD_AUTH_INFO_TOKEN_ANDROID) \
    _avail(XrGoogleCloudAuthInfoKeylessANDROID, XR_TYPE_GOOGLE_CLOUD_AUTH_INFO_KEYLESS_ANDROID) \





#पूर्ण_अगर

