#నిర్వచితం_కాకపోతే OPENXR_REFLECTION_మాతృ_STRUCTS_H
#నిర్వచించు OPENXR_REFLECTION_మాతృ_STRUCTS_H 1

/*
** Copyright (c) 2017-2026 The Khronos Group Inc.
**
** SPDX-License-Identifier: Apache-2.0 OR MIT
*/

/*
** This header is generated from the Khronos OpenXR XML API Registry.
**
*/

#అన్తర్భావ "openxr.h"

/*
This file contains expansion macros (X Macros) for OpenXR structures that have a parent type.
*/


/// Like XR_LIST_ALL_STRUCTURE_TYPES, but only includes types whose parent struct type is XrCompositionLayerBaseHeader
#నిర్వచించు XR_LIST_ALL_బిడ్డ_STRUCTURE_TYPES_Xr_Composition_Layer_పునాది_శీర్షిక(_avail, _unavail) \
    impl_XR_LIST_ALL_బిడ్డ_STRUCTURE_TYPES_Xr_Composition_Layer_పునాది_శీర్షిక_CORE(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrCompositionLayerBaseHeader()
#నిర్వచించు impl_XR_LIST_ALL_బిడ్డ_STRUCTURE_TYPES_Xr_Composition_Layer_పునాది_శీర్షిక_CORE(_avail, _unavail) \
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
#నిర్వచించు XR_LIST_ALL_బిడ్డ_STRUCTURE_TYPES_Xr_Event_దత్తాంశం_పునాది_శీర్షిక(_avail, _unavail) \
    impl_XR_LIST_ALL_బిడ్డ_STRUCTURE_TYPES_Xr_Event_దత్తాంశం_పునాది_శీర్షిక_CORE(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrEventDataBaseHeader()
#నిర్వచించు impl_XR_LIST_ALL_బిడ్డ_STRUCTURE_TYPES_Xr_Event_దత్తాంశం_పునాది_శీర్షిక_CORE(_avail, _unavail) \
    _avail(Xr_Event_దత్తాంశం_Events_కోల్పోయిన, XR_TYPE_EVENT_దత్తాంశం_EVENTS_కోల్పోయిన) \
    _avail(Xr_Event_దత్తాంశం_Instance_Loss_Pending, XR_TYPE_EVENT_దత్తాంశం_INSTANCE_LOSS_PENDING) \
    _avail(Xr_Event_దత్తాంశం_Session_State_మారింది, XR_TYPE_EVENT_దత్తాంశం_SESSION_STATE_మారింది) \
    _avail(Xr_Event_దత్తాంశం_Reference_Space_Change_Pending, XR_TYPE_EVENT_దత్తాంశం_REFERENCE_SPACE_CHANGE_PENDING) \
    _avail(Xr_Event_దత్తాంశం_Interaction_Profile_మారింది, XR_TYPE_EVENT_దత్తాంశం_INTERACTION_PROFILE_మారింది) \
    _avail(Xr_Event_దత్తాంశం_Visibility_ముసుగు_మారింది_KHR, XR_TYPE_EVENT_దత్తాంశం_VISIBILITY_ముసుగు_మారింది_KHR) \
    _avail(Xr_Event_దత్తాంశం_Perf_Settings_EXT, XR_TYPE_EVENT_దత్తాంశం_PERF_SETTINGS_EXT) \
    _avail(Xr_Event_దత్తాంశం_Main_Session_Visibility_మారింది_EXTX, XR_TYPE_EVENT_దత్తాంశం_MAIN_SESSION_VISIBILITY_మారింది_EXTX) \
    _avail(Xr_Event_దత్తాంశం_Display_Refresh_రేటు_మారింది_FB, XR_TYPE_EVENT_దత్తాంశం_DISPLAY_REFRESH_రేటు_మారింది_FB) \
    _avail(Xr_Event_దత్తాంశం_Vive_Tracker_Connected_HTCX, XR_TYPE_EVENT_దత్తాంశం_VIVE_TRACKER_CONNECTED_HTCX) \
    _avail(Xr_Event_దత్తాంశం_Spatial_Anchor_Create_Complete_FB, XR_TYPE_EVENT_దత్తాంశం_SPATIAL_ANCHOR_CREATE_COMPLETE_FB) \
    _avail(Xr_Event_దత్తాంశం_Space_సమితి_స్థితి_Complete_FB, XR_TYPE_EVENT_దత్తాంశం_SPACE_సమితి_స్థితి_COMPLETE_FB) \
    _avail(Xr_Event_దత్తాంశం_Passthrough_State_మారింది_FB, XR_TYPE_EVENT_దత్తాంశం_PASSTHROUGH_STATE_మారింది_FB) \
    _avail(Xr_Event_దత్తాంశం_Marker_Tracking_Update_VARJO, XR_TYPE_EVENT_దత్తాంశం_MARKER_TRACKING_UPDATE_VARJO) \
    _avail(Xr_Event_దత్తాంశం_Localization_మారింది_ML, XR_TYPE_EVENT_దత్తాంశం_LOCALIZATION_మారింది_ML) \
    _avail(Xr_Event_దత్తాంశం_Space_Query_Results_అందుబాటు_FB, XR_TYPE_EVENT_దత్తాంశం_SPACE_QUERY_RESULTS_అందుబాటు_FB) \
    _avail(Xr_Event_దత్తాంశం_Space_Query_Complete_FB, XR_TYPE_EVENT_దత్తాంశం_SPACE_QUERY_COMPLETE_FB) \
    _avail(Xr_Event_దత్తాంశం_Space_Save_Complete_FB, XR_TYPE_EVENT_దత్తాంశం_SPACE_SAVE_COMPLETE_FB) \
    _avail(Xr_Event_దత్తాంశం_Space_Erase_Complete_FB, XR_TYPE_EVENT_దత్తాంశం_SPACE_ERASE_COMPLETE_FB) \
    _avail(Xr_Event_దత్తాంశం_Space_Share_Complete_FB, XR_TYPE_EVENT_దత్తాంశం_SPACE_SHARE_COMPLETE_FB) \
    _avail(Xr_Event_దత్తాంశం_Scene_Capture_Complete_FB, XR_TYPE_EVENT_దత్తాంశం_SCENE_CAPTURE_COMPLETE_FB) \
    _avail(Xr_Event_దత్తాంశం_Virtual_Keyboard_Commit_పాఠ్యం_META, XR_TYPE_EVENT_దత్తాంశం_VIRTUAL_KEYBOARD_COMMIT_పాఠ్యం_META) \
    _avail(Xr_Event_దత్తాంశం_Virtual_Keyboard_Backspace_META, XR_TYPE_EVENT_దత్తాంశం_VIRTUAL_KEYBOARD_BACKSPACE_META) \
    _avail(Xr_Event_దత్తాంశం_Virtual_Keyboard_Enter_META, XR_TYPE_EVENT_దత్తాంశం_VIRTUAL_KEYBOARD_ENTER_META) \
    _avail(Xr_Event_దత్తాంశం_Virtual_Keyboard_Shown_META, XR_TYPE_EVENT_దత్తాంశం_VIRTUAL_KEYBOARD_SHOWN_META) \
    _avail(Xr_Event_దత్తాంశం_Virtual_Keyboard_Hidden_META, XR_TYPE_EVENT_దత్తాంశం_VIRTUAL_KEYBOARD_HIDDEN_META) \
    _avail(Xr_Event_దత్తాంశం_Space_List_Save_Complete_FB, XR_TYPE_EVENT_దత్తాంశం_SPACE_LIST_SAVE_COMPLETE_FB) \
    _avail(Xr_Event_దత్తాంశం_Space_Discovery_Results_అందుబాటు_META, XR_TYPE_EVENT_దత్తాంశం_SPACE_DISCOVERY_RESULTS_అందుబాటు_META) \
    _avail(Xr_Event_దత్తాంశం_Space_Discovery_Complete_META, XR_TYPE_EVENT_దత్తాంశం_SPACE_DISCOVERY_COMPLETE_META) \
    _avail(Xr_Event_దత్తాంశం_Spaces_Save_ఫలితం_META, XR_TYPE_EVENT_దత్తాంశం_SPACES_SAVE_ఫలితం_META) \
    _avail(Xr_Event_దత్తాంశం_Spaces_Erase_ఫలితం_META, XR_TYPE_EVENT_దత్తాంశం_SPACES_ERASE_ఫలితం_META) \
    _avail(Xr_Event_దత్తాంశం_Passthrough_Layer_Resumed_META, XR_TYPE_EVENT_దత్తాంశం_PASSTHROUGH_LAYER_RESUMED_META) \
    _avail(Xr_Event_దత్తాంశం_Share_Spaces_Complete_META, XR_TYPE_EVENT_దత్తాంశం_SHARE_SPACES_COMPLETE_META) \
    _avail(Xr_Event_దత్తాంశం_Interaction_Render_Models_మారింది_EXT, XR_TYPE_EVENT_దత్తాంశం_INTERACTION_RENDER_MODELS_మారింది_EXT) \
    _avail(Xr_Event_దత్తాంశం_Sense_దత్తాంశం_Provider_State_మారింది_BD, XR_TYPE_EVENT_దత్తాంశం_SENSE_దత్తాంశం_PROVIDER_STATE_మారింది_BD) \
    _avail(Xr_Event_దత్తాంశం_Sense_దత్తాంశం_Updated_BD, XR_TYPE_EVENT_దత్తాంశం_SENSE_దత్తాంశం_UPDATED_BD) \
    _avail(Xr_Event_దత్తాంశం_Recommended_Resolution_మారింది_ANDROID, XR_TYPE_EVENT_దత్తాంశం_RECOMMENDED_RESOLUTION_మారింది_ANDROID) \
    _avail(Xr_Event_దత్తాంశం_User_Presence_మారింది_EXT, XR_TYPE_EVENT_దత్తాంశం_USER_PRESENCE_మారింది_EXT) \
    _avail(Xr_Event_దత్తాంశం_Headset_Fit_మారింది_ML, XR_TYPE_EVENT_దత్తాంశం_HEADSET_FIT_మారింది_ML) \
    _avail(Xr_Event_దత్తాంశం_Eye_Calibration_మారింది_ML, XR_TYPE_EVENT_దత్తాంశం_EYE_CALIBRATION_మారింది_ML) \
    _avail(Xr_Event_దత్తాంశం_Boundary_Visibility_మారింది_META, XR_TYPE_EVENT_దత్తాంశం_BOUNDARY_VISIBILITY_మారింది_META) \
    _avail(Xr_Event_దత్తాంశం_ప్రారంభం_Colocation_Advertisement_Complete_META, XR_TYPE_EVENT_దత్తాంశం_ప్రారంభం_COLOCATION_ADVERTISEMENT_COMPLETE_META) \
    _avail(Xr_Event_దత్తాంశం_Stop_Colocation_Advertisement_Complete_META, XR_TYPE_EVENT_దత్తాంశం_STOP_COLOCATION_ADVERTISEMENT_COMPLETE_META) \
    _avail(Xr_Event_దత్తాంశం_Colocation_Advertisement_Complete_META, XR_TYPE_EVENT_దత్తాంశం_COLOCATION_ADVERTISEMENT_COMPLETE_META) \
    _avail(Xr_Event_దత్తాంశం_ప్రారంభం_Colocation_Discovery_Complete_META, XR_TYPE_EVENT_దత్తాంశం_ప్రారంభం_COLOCATION_DISCOVERY_COMPLETE_META) \
    _avail(Xr_Event_దత్తాంశం_Colocation_Discovery_ఫలితం_META, XR_TYPE_EVENT_దత్తాంశం_COLOCATION_DISCOVERY_ఫలితం_META) \
    _avail(Xr_Event_దత్తాంశం_Colocation_Discovery_Complete_META, XR_TYPE_EVENT_దత్తాంశం_COLOCATION_DISCOVERY_COMPLETE_META) \
    _avail(Xr_Event_దత్తాంశం_Stop_Colocation_Discovery_Complete_META, XR_TYPE_EVENT_దత్తాంశం_STOP_COLOCATION_DISCOVERY_COMPLETE_META) \
    _avail(Xr_Event_దత్తాంశం_Image_Tracking_కోల్పోయిన_ANDROID, XR_TYPE_EVENT_దత్తాంశం_IMAGE_TRACKING_కోల్పోయిన_ANDROID) \
    _avail(Xr_Event_దత్తాంశం_Spatial_Discovery_Recommended_EXT, XR_TYPE_EVENT_దత్తాంశం_SPATIAL_DISCOVERY_RECOMMENDED_EXT) \
    _avail(Xr_Event_దత్తాంశం_Geospatial_Tracker_State_మారింది_ANDROID, XR_TYPE_EVENT_దత్తాంశం_GEOSPATIAL_TRACKER_STATE_మారింది_ANDROID) \
    _avail(Xr_Event_దత్తాంశం_Spatial_Container_Closed_EXT, XR_TYPE_EVENT_దత్తాంశం_SPATIAL_CONTAINER_CLOSED_EXT) \
    _avail(Xr_Event_దత్తాంశం_Spatial_Container_Bounds_మారింది_EXT, XR_TYPE_EVENT_దత్తాంశం_SPATIAL_CONTAINER_BOUNDS_మారింది_EXT) \
    _avail(Xr_Event_దత్తాంశం_Spatial_Container_Visible_మారింది_EXT, XR_TYPE_EVENT_దత్తాంశం_SPATIAL_CONTAINER_VISIBLE_మారింది_EXT) \
    _avail(Xr_Event_దత్తాంశం_Spatial_Container_Visible_Request_Denied_EXT, XR_TYPE_EVENT_దత్తాంశం_SPATIAL_CONTAINER_VISIBLE_REQUEST_DENIED_EXT) \
    _avail(Xr_Event_దత్తాంశం_Spatial_Container_Interactable_మారింది_EXT, XR_TYPE_EVENT_దత్తాంశం_SPATIAL_CONTAINER_INTERACTABLE_మారింది_EXT) \
    _avail(Xr_Event_దత్తాంశం_Spatial_Container_Bounds_బహుళకం_Request_Denied_EXT, XR_TYPE_EVENT_దత్తాంశం_SPATIAL_CONTAINER_BOUNDS_బహుళకం_REQUEST_DENIED_EXT) \
    _avail(Xr_Event_దత్తాంశం_View_Configuration_Views_మారింది_EXT, XR_TYPE_EVENT_దత్తాంశం_VIEW_CONFIGURATION_VIEWS_మారింది_EXT) \





/// Like XR_LIST_ALL_STRUCTURE_TYPES, but only includes types whose parent struct type is XrHapticBaseHeader
#నిర్వచించు XR_LIST_ALL_బిడ్డ_STRUCTURE_TYPES_Xr_Haptic_పునాది_శీర్షిక(_avail, _unavail) \
    impl_XR_LIST_ALL_బిడ్డ_STRUCTURE_TYPES_Xr_Haptic_పునాది_శీర్షిక_CORE(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrHapticBaseHeader()
#నిర్వచించు impl_XR_LIST_ALL_బిడ్డ_STRUCTURE_TYPES_Xr_Haptic_పునాది_శీర్షిక_CORE(_avail, _unavail) \
    _avail(XrHapticVibration, XR_TYPE_HAPTIC_VIBRATION) \
    _avail(XrHapticAmplitudeEnvelopeVibrationFB, XR_TYPE_HAPTIC_AMPLITUDE_ENVELOPE_VIBRATION_FB) \
    _avail(XrHapticPcmVibrationFB, XR_TYPE_HAPTIC_PCM_VIBRATION_FB) \
    _avail(XrHapticParametricVibrationEXT, XR_TYPE_HAPTIC_PARAMETRIC_VIBRATION_EXT) \





/// Like XR_LIST_ALL_STRUCTURE_TYPES, but only includes types whose parent struct type is XrSwapchainImageBaseHeader
#నిర్వచించు XR_LIST_ALL_బిడ్డ_STRUCTURE_TYPES_Xr_Swapchain_Image_పునాది_శీర్షిక(_avail, _unavail) \
    impl_XR_LIST_ALL_బిడ్డ_STRUCTURE_TYPES_Xr_Swapchain_Image_పునాది_శీర్షిక_CORE(_avail, _unavail) \
    impl_XR_LIST_ALL_బిడ్డ_STRUCTURE_TYPES_Xr_Swapchain_Image_పునాది_శీర్షిక_XR_USE_GRAPHICS_API_D3_D11(_avail, _unavail) \
    impl_XR_LIST_ALL_బిడ్డ_STRUCTURE_TYPES_Xr_Swapchain_Image_పునాది_శీర్షిక_XR_USE_GRAPHICS_API_D3_D12(_avail, _unavail) \
    impl_XR_LIST_ALL_బిడ్డ_STRUCTURE_TYPES_Xr_Swapchain_Image_పునాది_శీర్షిక_XR_USE_GRAPHICS_API_METAL(_avail, _unavail) \
    impl_XR_LIST_ALL_బిడ్డ_STRUCTURE_TYPES_Xr_Swapchain_Image_పునాది_శీర్షిక_XR_USE_GRAPHICS_API_OPENGL(_avail, _unavail) \
    impl_XR_LIST_ALL_బిడ్డ_STRUCTURE_TYPES_Xr_Swapchain_Image_పునాది_శీర్షిక_XR_USE_GRAPHICS_API_OPENGL_ES(_avail, _unavail) \
    impl_XR_LIST_ALL_బిడ్డ_STRUCTURE_TYPES_Xr_Swapchain_Image_పునాది_శీర్షిక_XR_USE_GRAPHICS_API_VULKAN(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrSwapchainImageBaseHeader()
#నిర్వచించు impl_XR_LIST_ALL_బిడ్డ_STRUCTURE_TYPES_Xr_Swapchain_Image_పునాది_శీర్షిక_CORE(_avail, _unavail) \


#ఒకవేళ defined(XR_USE_GRAPHICS_API_D3D11)
#నిర్వచించు impl_XR_LIST_ALL_బిడ్డ_STRUCTURE_TYPES_Xr_Swapchain_Image_పునాది_శీర్షిక_XR_USE_GRAPHICS_API_D3_D11(_avail, _unavail) \
    _avail(XrSwapchainImageD3D11KHR, XR_TYPE_SWAPCHAIN_IMAGE_D3D11_KHR) \

#లేకపోతే
#నిర్వచించు impl_XR_LIST_ALL_బిడ్డ_STRUCTURE_TYPES_Xr_Swapchain_Image_పునాది_శీర్షిక_XR_USE_GRAPHICS_API_D3_D11(_avail, _unavail) \
    _unavail(XrSwapchainImageD3D11KHR, XR_TYPE_SWAPCHAIN_IMAGE_D3D11_KHR) \

#అయితే_ముగింపు

#ఒకవేళ defined(XR_USE_GRAPHICS_API_D3D12)
#నిర్వచించు impl_XR_LIST_ALL_బిడ్డ_STRUCTURE_TYPES_Xr_Swapchain_Image_పునాది_శీర్షిక_XR_USE_GRAPHICS_API_D3_D12(_avail, _unavail) \
    _avail(XrSwapchainImageD3D12KHR, XR_TYPE_SWAPCHAIN_IMAGE_D3D12_KHR) \

#లేకపోతే
#నిర్వచించు impl_XR_LIST_ALL_బిడ్డ_STRUCTURE_TYPES_Xr_Swapchain_Image_పునాది_శీర్షిక_XR_USE_GRAPHICS_API_D3_D12(_avail, _unavail) \
    _unavail(XrSwapchainImageD3D12KHR, XR_TYPE_SWAPCHAIN_IMAGE_D3D12_KHR) \

#అయితే_ముగింపు

#ఒకవేళ defined(XR_USE_GRAPHICS_API_METAL)
#నిర్వచించు impl_XR_LIST_ALL_బిడ్డ_STRUCTURE_TYPES_Xr_Swapchain_Image_పునాది_శీర్షిక_XR_USE_GRAPHICS_API_METAL(_avail, _unavail) \
    _avail(XrSwapchainImageMetalKHR, XR_TYPE_SWAPCHAIN_IMAGE_METAL_KHR) \

#లేకపోతే
#నిర్వచించు impl_XR_LIST_ALL_బిడ్డ_STRUCTURE_TYPES_Xr_Swapchain_Image_పునాది_శీర్షిక_XR_USE_GRAPHICS_API_METAL(_avail, _unavail) \
    _unavail(XrSwapchainImageMetalKHR, XR_TYPE_SWAPCHAIN_IMAGE_METAL_KHR) \

#అయితే_ముగింపు

#ఒకవేళ defined(XR_USE_GRAPHICS_API_OPENGL)
#నిర్వచించు impl_XR_LIST_ALL_బిడ్డ_STRUCTURE_TYPES_Xr_Swapchain_Image_పునాది_శీర్షిక_XR_USE_GRAPHICS_API_OPENGL(_avail, _unavail) \
    _avail(XrSwapchainImageOpenGLKHR, XR_TYPE_SWAPCHAIN_IMAGE_OPENGL_KHR) \

#లేకపోతే
#నిర్వచించు impl_XR_LIST_ALL_బిడ్డ_STRUCTURE_TYPES_Xr_Swapchain_Image_పునాది_శీర్షిక_XR_USE_GRAPHICS_API_OPENGL(_avail, _unavail) \
    _unavail(XrSwapchainImageOpenGLKHR, XR_TYPE_SWAPCHAIN_IMAGE_OPENGL_KHR) \

#అయితే_ముగింపు

#ఒకవేళ defined(XR_USE_GRAPHICS_API_OPENGL_ES)
#నిర్వచించు impl_XR_LIST_ALL_బిడ్డ_STRUCTURE_TYPES_Xr_Swapchain_Image_పునాది_శీర్షిక_XR_USE_GRAPHICS_API_OPENGL_ES(_avail, _unavail) \
    _avail(XrSwapchainImageOpenGLESKHR, XR_TYPE_SWAPCHAIN_IMAGE_OPENGL_ES_KHR) \

#లేకపోతే
#నిర్వచించు impl_XR_LIST_ALL_బిడ్డ_STRUCTURE_TYPES_Xr_Swapchain_Image_పునాది_శీర్షిక_XR_USE_GRAPHICS_API_OPENGL_ES(_avail, _unavail) \
    _unavail(XrSwapchainImageOpenGLESKHR, XR_TYPE_SWAPCHAIN_IMAGE_OPENGL_ES_KHR) \

#అయితే_ముగింపు

#ఒకవేళ defined(XR_USE_GRAPHICS_API_VULKAN)
#నిర్వచించు impl_XR_LIST_ALL_బిడ్డ_STRUCTURE_TYPES_Xr_Swapchain_Image_పునాది_శీర్షిక_XR_USE_GRAPHICS_API_VULKAN(_avail, _unavail) \
    _avail(XrSwapchainImageVulkanKHR, XR_TYPE_SWAPCHAIN_IMAGE_VULKAN_KHR) \

#లేకపోతే
#నిర్వచించు impl_XR_LIST_ALL_బిడ్డ_STRUCTURE_TYPES_Xr_Swapchain_Image_పునాది_శీర్షిక_XR_USE_GRAPHICS_API_VULKAN(_avail, _unavail) \
    _unavail(XrSwapchainImageVulkanKHR, XR_TYPE_SWAPCHAIN_IMAGE_VULKAN_KHR) \

#అయితే_ముగింపు




/// Like XR_LIST_ALL_STRUCTURE_TYPES, but only includes types whose parent struct type is XrLoaderInitInfoBaseHeaderKHR
#నిర్వచించు XR_LIST_ALL_బిడ్డ_STRUCTURE_TYPES_Xr_Loader_Init_Info_పునాది_శీర్షిక_KHR(_avail, _unavail) \
    impl_XR_LIST_ALL_బిడ్డ_STRUCTURE_TYPES_Xr_Loader_Init_Info_పునాది_శీర్షిక_KHR_CORE(_avail, _unavail) \
    impl_XR_LIST_ALL_బిడ్డ_STRUCTURE_TYPES_Xr_Loader_Init_Info_పునాది_శీర్షిక_KHR_XR_USE_PLATFORM_ANDROID(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrLoaderInitInfoBaseHeaderKHR()
#నిర్వచించు impl_XR_LIST_ALL_బిడ్డ_STRUCTURE_TYPES_Xr_Loader_Init_Info_పునాది_శీర్షిక_KHR_CORE(_avail, _unavail) \
    _avail(XrLoaderInitInfoPropertiesEXT, XR_TYPE_LOADER_INIT_INFO_PROPERTIES_EXT) \


#ఒకవేళ defined(XR_USE_PLATFORM_ANDROID)
#నిర్వచించు impl_XR_LIST_ALL_బిడ్డ_STRUCTURE_TYPES_Xr_Loader_Init_Info_పునాది_శీర్షిక_KHR_XR_USE_PLATFORM_ANDROID(_avail, _unavail) \
    _avail(XrLoaderInitInfoAndroidKHR, XR_TYPE_LOADER_INIT_INFO_ANDROID_KHR) \

#లేకపోతే
#నిర్వచించు impl_XR_LIST_ALL_బిడ్డ_STRUCTURE_TYPES_Xr_Loader_Init_Info_పునాది_శీర్షిక_KHR_XR_USE_PLATFORM_ANDROID(_avail, _unavail) \
    _unavail(XrLoaderInitInfoAndroidKHR, XR_TYPE_LOADER_INIT_INFO_ANDROID_KHR) \

#అయితే_ముగింపు




/// Like XR_LIST_ALL_STRUCTURE_TYPES, but only includes types whose parent struct type is XrBindingModificationBaseHeaderKHR
#నిర్వచించు XR_LIST_ALL_బిడ్డ_STRUCTURE_TYPES_Xr_Binding_Modification_పునాది_శీర్షిక_KHR(_avail, _unavail) \
    impl_XR_LIST_ALL_బిడ్డ_STRUCTURE_TYPES_Xr_Binding_Modification_పునాది_శీర్షిక_KHR_CORE(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrBindingModificationBaseHeaderKHR()
#నిర్వచించు impl_XR_LIST_ALL_బిడ్డ_STRUCTURE_TYPES_Xr_Binding_Modification_పునాది_శీర్షిక_KHR_CORE(_avail, _unavail) \
    _avail(XrInteractionProfileDpadBindingEXT, XR_TYPE_INTERACTION_PROFILE_DPAD_BINDING_EXT) \
    _avail(Xr_Interaction_Profile_Analog_పరిమితి_VALVE, XR_TYPE_INTERACTION_PROFILE_ANALOG_పరిమితి_VALVE) \





/// Like XR_LIST_ALL_STRUCTURE_TYPES, but only includes types whose parent struct type is XrSwapchainStateBaseHeaderFB
#నిర్వచించు XR_LIST_ALL_బిడ్డ_STRUCTURE_TYPES_Xr_Swapchain_State_పునాది_శీర్షిక_FB(_avail, _unavail) \
    impl_XR_LIST_ALL_బిడ్డ_STRUCTURE_TYPES_Xr_Swapchain_State_పునాది_శీర్షిక_FB_CORE(_avail, _unavail) \
    impl_XR_LIST_ALL_బిడ్డ_STRUCTURE_TYPES_Xr_Swapchain_State_పునాది_శీర్షిక_FB_XR_USE_GRAPHICS_API_OPENGL_ES(_avail, _unavail) \
    impl_XR_LIST_ALL_బిడ్డ_STRUCTURE_TYPES_Xr_Swapchain_State_పునాది_శీర్షిక_FB_XR_USE_GRAPHICS_API_VULKAN(_avail, _unavail) \
    impl_XR_LIST_ALL_బిడ్డ_STRUCTURE_TYPES_Xr_Swapchain_State_పునాది_శీర్షిక_FB_XR_USE_PLATFORM_ANDROID(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrSwapchainStateBaseHeaderFB()
#నిర్వచించు impl_XR_LIST_ALL_బిడ్డ_STRUCTURE_TYPES_Xr_Swapchain_State_పునాది_శీర్షిక_FB_CORE(_avail, _unavail) \
    _avail(XrSwapchainStateFoveationFB, XR_TYPE_SWAPCHAIN_STATE_FOVEATION_FB) \


#ఒకవేళ defined(XR_USE_GRAPHICS_API_OPENGL_ES)
#నిర్వచించు impl_XR_LIST_ALL_బిడ్డ_STRUCTURE_TYPES_Xr_Swapchain_State_పునాది_శీర్షిక_FB_XR_USE_GRAPHICS_API_OPENGL_ES(_avail, _unavail) \
    _avail(XrSwapchainStateSamplerOpenGLESFB, XR_TYPE_SWAPCHAIN_STATE_SAMPLER_OPENGL_ES_FB) \

#లేకపోతే
#నిర్వచించు impl_XR_LIST_ALL_బిడ్డ_STRUCTURE_TYPES_Xr_Swapchain_State_పునాది_శీర్షిక_FB_XR_USE_GRAPHICS_API_OPENGL_ES(_avail, _unavail) \
    _unavail(XrSwapchainStateSamplerOpenGLESFB, XR_TYPE_SWAPCHAIN_STATE_SAMPLER_OPENGL_ES_FB) \

#అయితే_ముగింపు

#ఒకవేళ defined(XR_USE_GRAPHICS_API_VULKAN)
#నిర్వచించు impl_XR_LIST_ALL_బిడ్డ_STRUCTURE_TYPES_Xr_Swapchain_State_పునాది_శీర్షిక_FB_XR_USE_GRAPHICS_API_VULKAN(_avail, _unavail) \
    _avail(XrSwapchainStateSamplerVulkanFB, XR_TYPE_SWAPCHAIN_STATE_SAMPLER_VULKAN_FB) \

#లేకపోతే
#నిర్వచించు impl_XR_LIST_ALL_బిడ్డ_STRUCTURE_TYPES_Xr_Swapchain_State_పునాది_శీర్షిక_FB_XR_USE_GRAPHICS_API_VULKAN(_avail, _unavail) \
    _unavail(XrSwapchainStateSamplerVulkanFB, XR_TYPE_SWAPCHAIN_STATE_SAMPLER_VULKAN_FB) \

#అయితే_ముగింపు

#ఒకవేళ defined(XR_USE_PLATFORM_ANDROID)
#నిర్వచించు impl_XR_LIST_ALL_బిడ్డ_STRUCTURE_TYPES_Xr_Swapchain_State_పునాది_శీర్షిక_FB_XR_USE_PLATFORM_ANDROID(_avail, _unavail) \
    _avail(XrSwapchainStateAndroidSurfaceDimensionsFB, XR_TYPE_SWAPCHAIN_STATE_ANDROID_SURFACE_DIMENSIONS_FB) \

#లేకపోతే
#నిర్వచించు impl_XR_LIST_ALL_బిడ్డ_STRUCTURE_TYPES_Xr_Swapchain_State_పునాది_శీర్షిక_FB_XR_USE_PLATFORM_ANDROID(_avail, _unavail) \
    _unavail(XrSwapchainStateAndroidSurfaceDimensionsFB, XR_TYPE_SWAPCHAIN_STATE_ANDROID_SURFACE_DIMENSIONS_FB) \

#అయితే_ముగింపు




/// Like XR_LIST_ALL_STRUCTURE_TYPES, but only includes types whose parent struct type is XrSpatialAnchorsCreateInfoBaseHeaderML
#నిర్వచించు XR_LIST_ALL_బిడ్డ_STRUCTURE_TYPES_Xr_Spatial_Anchors_Create_Info_పునాది_శీర్షిక_ML(_avail, _unavail) \
    impl_XR_LIST_ALL_బిడ్డ_STRUCTURE_TYPES_Xr_Spatial_Anchors_Create_Info_పునాది_శీర్షిక_ML_CORE(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrSpatialAnchorsCreateInfoBaseHeaderML()
#నిర్వచించు impl_XR_LIST_ALL_బిడ్డ_STRUCTURE_TYPES_Xr_Spatial_Anchors_Create_Info_పునాది_శీర్షిక_ML_CORE(_avail, _unavail) \
    _avail(XrSpatialAnchorsCreateInfoFromPoseML, XR_TYPE_SPATIAL_ANCHORS_CREATE_INFO_FROM_POSE_ML) \
    _avail(XrSpatialAnchorsCreateInfoFromUuidsML, XR_TYPE_SPATIAL_ANCHORS_CREATE_INFO_FROM_UUIDS_ML) \





/// Like XR_LIST_ALL_STRUCTURE_TYPES, but only includes types whose parent struct type is XrFutureCompletionBaseHeaderEXT
#నిర్వచించు XR_LIST_ALL_బిడ్డ_STRUCTURE_TYPES_Xr_Future_Completion_పునాది_శీర్షిక_EXT(_avail, _unavail) \
    impl_XR_LIST_ALL_బిడ్డ_STRUCTURE_TYPES_Xr_Future_Completion_పునాది_శీర్షిక_EXT_CORE(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrFutureCompletionBaseHeaderEXT()
#నిర్వచించు impl_XR_LIST_ALL_బిడ్డ_STRUCTURE_TYPES_Xr_Future_Completion_పునాది_శీర్షిక_EXT_CORE(_avail, _unavail) \
    _avail(XrCreateSpatialAnchorsCompletionML, XR_TYPE_CREATE_SPATIAL_ANCHORS_COMPLETION_ML) \
    _avail(XrSpatialAnchorsQueryCompletionML, XR_TYPE_SPATIAL_ANCHORS_QUERY_COMPLETION_ML) \
    _avail(XrSpatialAnchorsPublishCompletionML, XR_TYPE_SPATIAL_ANCHORS_PUBLISH_COMPLETION_ML) \
    _avail(XrSpatialAnchorsDeleteCompletionML, XR_TYPE_SPATIAL_ANCHORS_DELETE_COMPLETION_ML) \
    _avail(XrSpatialAnchorsUpdateExpirationCompletionML, XR_TYPE_SPATIAL_ANCHORS_UPDATE_EXPIRATION_COMPLETION_ML) \
    _avail(Xr_Sense_దత్తాంశం_Query_Completion_BD, XR_TYPE_SENSE_దత్తాంశం_QUERY_COMPLETION_BD) \
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
#నిర్వచించు XR_LIST_ALL_బిడ్డ_STRUCTURE_TYPES_Xr_Spatial_Anchors_Query_Info_పునాది_శీర్షిక_ML(_avail, _unavail) \
    impl_XR_LIST_ALL_బిడ్డ_STRUCTURE_TYPES_Xr_Spatial_Anchors_Query_Info_పునాది_శీర్షిక_ML_CORE(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrSpatialAnchorsQueryInfoBaseHeaderML()
#నిర్వచించు impl_XR_LIST_ALL_బిడ్డ_STRUCTURE_TYPES_Xr_Spatial_Anchors_Query_Info_పునాది_శీర్షిక_ML_CORE(_avail, _unavail) \
    _avail(XrSpatialAnchorsQueryInfoRadiusML, XR_TYPE_SPATIAL_ANCHORS_QUERY_INFO_RADIUS_ML) \





/// Like XR_LIST_ALL_STRUCTURE_TYPES, but only includes types whose parent struct type is XrSpaceQueryInfoBaseHeaderFB
#నిర్వచించు XR_LIST_ALL_బిడ్డ_STRUCTURE_TYPES_Xr_Space_Query_Info_పునాది_శీర్షిక_FB(_avail, _unavail) \
    impl_XR_LIST_ALL_బిడ్డ_STRUCTURE_TYPES_Xr_Space_Query_Info_పునాది_శీర్షిక_FB_CORE(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrSpaceQueryInfoBaseHeaderFB()
#నిర్వచించు impl_XR_LIST_ALL_బిడ్డ_STRUCTURE_TYPES_Xr_Space_Query_Info_పునాది_శీర్షిక_FB_CORE(_avail, _unavail) \
    _avail(XrSpaceQueryInfoFB, XR_TYPE_SPACE_QUERY_INFO_FB) \





/// Like XR_LIST_ALL_STRUCTURE_TYPES, but only includes types whose parent struct type is XrSpaceFilterInfoBaseHeaderFB
#నిర్వచించు XR_LIST_ALL_బిడ్డ_STRUCTURE_TYPES_Xr_Space_Filter_Info_పునాది_శీర్షిక_FB(_avail, _unavail) \
    impl_XR_LIST_ALL_బిడ్డ_STRUCTURE_TYPES_Xr_Space_Filter_Info_పునాది_శీర్షిక_FB_CORE(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrSpaceFilterInfoBaseHeaderFB()
#నిర్వచించు impl_XR_LIST_ALL_బిడ్డ_STRUCTURE_TYPES_Xr_Space_Filter_Info_పునాది_శీర్షిక_FB_CORE(_avail, _unavail) \
    _avail(XrSpaceUuidFilterInfoFB, XR_TYPE_SPACE_UUID_FILTER_INFO_FB) \
    _avail(XrSpaceComponentFilterInfoFB, XR_TYPE_SPACE_COMPONENT_FILTER_INFO_FB) \





/// Like XR_LIST_ALL_STRUCTURE_TYPES, but only includes types whose parent struct type is XrSpaceFilterBaseHeaderMETA
#నిర్వచించు XR_LIST_ALL_బిడ్డ_STRUCTURE_TYPES_Xr_Space_Filter_పునాది_శీర్షిక_META(_avail, _unavail) \
    impl_XR_LIST_ALL_బిడ్డ_STRUCTURE_TYPES_Xr_Space_Filter_పునాది_శీర్షిక_META_CORE(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrSpaceFilterBaseHeaderMETA()
#నిర్వచించు impl_XR_LIST_ALL_బిడ్డ_STRUCTURE_TYPES_Xr_Space_Filter_పునాది_శీర్షిక_META_CORE(_avail, _unavail) \
    _avail(XrSpaceFilterUuidMETA, XR_TYPE_SPACE_FILTER_UUID_META) \
    _avail(XrSpaceFilterComponentMETA, XR_TYPE_SPACE_FILTER_COMPONENT_META) \





/// Like XR_LIST_ALL_STRUCTURE_TYPES, but only includes types whose parent struct type is XrShareSpacesRecipientBaseHeaderMETA
#నిర్వచించు XR_LIST_ALL_బిడ్డ_STRUCTURE_TYPES_Xr_Share_Spaces_Recipient_పునాది_శీర్షిక_META(_avail, _unavail) \
    impl_XR_LIST_ALL_బిడ్డ_STRUCTURE_TYPES_Xr_Share_Spaces_Recipient_పునాది_శీర్షిక_META_CORE(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrShareSpacesRecipientBaseHeaderMETA()
#నిర్వచించు impl_XR_LIST_ALL_బిడ్డ_STRUCTURE_TYPES_Xr_Share_Spaces_Recipient_పునాది_శీర్షిక_META_CORE(_avail, _unavail) \
    _avail(XrShareSpacesRecipientGroupsMETA, XR_TYPE_SHARE_SPACES_RECIPIENT_GROUPS_META) \





/// Like XR_LIST_ALL_STRUCTURE_TYPES, but only includes types whose parent struct type is XrEnvironmentRaycastFilterBaseHeaderMETA
#నిర్వచించు XR_LIST_ALL_బిడ్డ_STRUCTURE_TYPES_Xr_Environment_Raycast_Filter_పునాది_శీర్షిక_META(_avail, _unavail) \
    impl_XR_LIST_ALL_బిడ్డ_STRUCTURE_TYPES_Xr_Environment_Raycast_Filter_పునాది_శీర్షిక_META_CORE(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrEnvironmentRaycastFilterBaseHeaderMETA()
#నిర్వచించు impl_XR_LIST_ALL_బిడ్డ_STRUCTURE_TYPES_Xr_Environment_Raycast_Filter_పునాది_శీర్షిక_META_CORE(_avail, _unavail) \
    _avail(Xr_Environment_Raycast_Filter_దూరం_META, XR_TYPE_ENVIRONMENT_RAYCAST_FILTER_దూరం_META) \





/// Like XR_LIST_ALL_STRUCTURE_TYPES, but only includes types whose parent struct type is XrSpatialCapabilityConfigurationBaseHeaderEXT
#నిర్వచించు XR_LIST_ALL_బిడ్డ_STRUCTURE_TYPES_Xr_Spatial_Capability_Configuration_పునాది_శీర్షిక_EXT(_avail, _unavail) \
    impl_XR_LIST_ALL_బిడ్డ_STRUCTURE_TYPES_Xr_Spatial_Capability_Configuration_పునాది_శీర్షిక_EXT_CORE(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrSpatialCapabilityConfigurationBaseHeaderEXT()
#నిర్వచించు impl_XR_LIST_ALL_బిడ్డ_STRUCTURE_TYPES_Xr_Spatial_Capability_Configuration_పునాది_శీర్షిక_EXT_CORE(_avail, _unavail) \
    _avail(XrSpatialCapabilityConfigurationPlaneTrackingEXT, XR_TYPE_SPATIAL_CAPABILITY_CONFIGURATION_PLANE_TRACKING_EXT) \
    _avail(Xr_Spatial_Capability_Configuration_Qr_సంకేతం_EXT, XR_TYPE_SPATIAL_CAPABILITY_CONFIGURATION_QR_సంకేతం_EXT) \
    _avail(Xr_Spatial_Capability_Configuration_Micro_Qr_సంకేతం_EXT, XR_TYPE_SPATIAL_CAPABILITY_CONFIGURATION_MICRO_QR_సంకేతం_EXT) \
    _avail(XrSpatialCapabilityConfigurationArucoMarkerEXT, XR_TYPE_SPATIAL_CAPABILITY_CONFIGURATION_ARUCO_MARKER_EXT) \
    _avail(Xr_Spatial_Capability_Configuration_April_ట్యాగ్_EXT, XR_TYPE_SPATIAL_CAPABILITY_CONFIGURATION_APRIL_ట్యాగ్_EXT) \
    _avail(XrSpatialCapabilityConfigurationObjectTrackingEXT, XR_TYPE_SPATIAL_CAPABILITY_CONFIGURATION_OBJECT_TRACKING_EXT) \
    _avail(XrSpatialCapabilityConfigurationAnchorEXT, XR_TYPE_SPATIAL_CAPABILITY_CONFIGURATION_ANCHOR_EXT) \
    _avail(XrSpatialCapabilityConfigurationImageTrackingEXT, XR_TYPE_SPATIAL_CAPABILITY_CONFIGURATION_IMAGE_TRACKING_EXT) \
    _avail(XrSpatialCapabilityConfigurationMeshTrackingEXT, XR_TYPE_SPATIAL_CAPABILITY_CONFIGURATION_MESH_TRACKING_EXT) \
    _avail(XrSpatialCapabilityConfigurationObjectTrackingANDROID, XR_TYPE_SPATIAL_CAPABILITY_CONFIGURATION_OBJECT_TRACKING_ANDROID) \
    _avail(Xr_Spatial_Capability_Configuration_లోతు_Raycast_ANDROID, XR_TYPE_SPATIAL_CAPABILITY_CONFIGURATION_లోతు_RAYCAST_ANDROID) \





/// Like XR_LIST_ALL_STRUCTURE_TYPES, but only includes types whose parent struct type is XrCameraPropertyBaseHeaderBD
#నిర్వచించు XR_LIST_ALL_బిడ్డ_STRUCTURE_TYPES_Xr_Camera_Property_పునాది_శీర్షిక_BD(_avail, _unavail) \
    impl_XR_LIST_ALL_బిడ్డ_STRUCTURE_TYPES_Xr_Camera_Property_పునాది_శీర్షిక_BD_CORE(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrCameraPropertyBaseHeaderBD()
#నిర్వచించు impl_XR_LIST_ALL_బిడ్డ_STRUCTURE_TYPES_Xr_Camera_Property_పునాది_శీర్షిక_BD_CORE(_avail, _unavail) \
    _avail(XrCameraPropertyFacingBD, XR_TYPE_CAMERA_PROPERTY_FACING_BD) \
    _avail(XrCameraPropertyPositionBD, XR_TYPE_CAMERA_PROPERTY_POSITION_BD) \
    _avail(XrCameraPropertyCameraTypeBD, XR_TYPE_CAMERA_PROPERTY_CAMERA_TYPE_BD) \





/// Like XR_LIST_ALL_STRUCTURE_TYPES, but only includes types whose parent struct type is XrCameraSupportedCapabilityBaseHeaderBD
#నిర్వచించు XR_LIST_ALL_బిడ్డ_STRUCTURE_TYPES_Xr_Camera_Supported_Capability_పునాది_శీర్షిక_BD(_avail, _unavail) \
    impl_XR_LIST_ALL_బిడ్డ_STRUCTURE_TYPES_Xr_Camera_Supported_Capability_పునాది_శీర్షిక_BD_CORE(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrCameraSupportedCapabilityBaseHeaderBD()
#నిర్వచించు impl_XR_LIST_ALL_బిడ్డ_STRUCTURE_TYPES_Xr_Camera_Supported_Capability_పునాది_శీర్షిక_BD_CORE(_avail, _unavail) \
    _avail(Xr_Camera_Supported_Capability_Image_Resolution_And_చట్రం_రేటు_BD, XR_TYPE_CAMERA_SUPPORTED_CAPABILITY_IMAGE_RESOLUTION_AND_చట్రం_రేటు_BD) \
    _avail(Xr_Camera_Supported_Capability_దత్తాంశం_Transfer_Type_BD, XR_TYPE_CAMERA_SUPPORTED_CAPABILITY_దత్తాంశం_TRANSFER_TYPE_BD) \
    _avail(XrCameraSupportedCapabilityImageFormatBD, XR_TYPE_CAMERA_SUPPORTED_CAPABILITY_IMAGE_FORMAT_BD) \
    _avail(XrCameraSupportedCapabilityCameraModelBD, XR_TYPE_CAMERA_SUPPORTED_CAPABILITY_CAMERA_MODEL_BD) \





/// Like XR_LIST_ALL_STRUCTURE_TYPES, but only includes types whose parent struct type is XrCameraCapabilityBaseHeaderBD
#నిర్వచించు XR_LIST_ALL_బిడ్డ_STRUCTURE_TYPES_Xr_Camera_Capability_పునాది_శీర్షిక_BD(_avail, _unavail) \
    impl_XR_LIST_ALL_బిడ్డ_STRUCTURE_TYPES_Xr_Camera_Capability_పునాది_శీర్షిక_BD_CORE(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrCameraCapabilityBaseHeaderBD()
#నిర్వచించు impl_XR_LIST_ALL_బిడ్డ_STRUCTURE_TYPES_Xr_Camera_Capability_పునాది_శీర్షిక_BD_CORE(_avail, _unavail) \
    _avail(Xr_Camera_Capability_Image_Resolution_And_చట్రం_రేటు_BD, XR_TYPE_CAMERA_CAPABILITY_IMAGE_RESOLUTION_AND_చట్రం_రేటు_BD) \
    _avail(Xr_Camera_Capability_దత్తాంశం_Transfer_Type_BD, XR_TYPE_CAMERA_CAPABILITY_దత్తాంశం_TRANSFER_TYPE_BD) \
    _avail(XrCameraCapabilityImageFormatBD, XR_TYPE_CAMERA_CAPABILITY_IMAGE_FORMAT_BD) \
    _avail(XrCameraCapabilityCameraModelBD, XR_TYPE_CAMERA_CAPABILITY_CAMERA_MODEL_BD) \





/// Like XR_LIST_ALL_STRUCTURE_TYPES, but only includes types whose parent struct type is XrCameraImageDataBaseHeaderBD
#నిర్వచించు XR_LIST_ALL_బిడ్డ_STRUCTURE_TYPES_Xr_Camera_Image_దత్తాంశం_పునాది_శీర్షిక_BD(_avail, _unavail) \
    impl_XR_LIST_ALL_బిడ్డ_STRUCTURE_TYPES_Xr_Camera_Image_దత్తాంశం_పునాది_శీర్షిక_BD_CORE(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrCameraImageDataBaseHeaderBD()
#నిర్వచించు impl_XR_LIST_ALL_బిడ్డ_STRUCTURE_TYPES_Xr_Camera_Image_దత్తాంశం_పునాది_శీర్షిక_BD_CORE(_avail, _unavail) \
    _avail(Xr_Camera_Image_దత్తాంశం_Raw_బఫరు_BD, XR_TYPE_CAMERA_IMAGE_దత్తాంశం_RAW_బఫరు_BD) \





/// Like XR_LIST_ALL_STRUCTURE_TYPES, but only includes types whose parent struct type is XrGoogleCloudAuthInfoBaseHeaderANDROID
#నిర్వచించు XR_LIST_ALL_బిడ్డ_STRUCTURE_TYPES_Xr_Google_Cloud_Auth_Info_పునాది_శీర్షిక_ANDROID(_avail, _unavail) \
    impl_XR_LIST_ALL_బిడ్డ_STRUCTURE_TYPES_Xr_Google_Cloud_Auth_Info_పునాది_శీర్షిక_ANDROID_CORE(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrGoogleCloudAuthInfoBaseHeaderANDROID()
#నిర్వచించు impl_XR_LIST_ALL_బిడ్డ_STRUCTURE_TYPES_Xr_Google_Cloud_Auth_Info_పునాది_శీర్షిక_ANDROID_CORE(_avail, _unavail) \
    _avail(Xr_Google_Cloud_Auth_Info_Api_కీలకం_ANDROID, XR_TYPE_GOOGLE_CLOUD_AUTH_INFO_API_కీలకం_ANDROID) \
    _avail(XrGoogleCloudAuthInfoTokenANDROID, XR_TYPE_GOOGLE_CLOUD_AUTH_INFO_TOKEN_ANDROID) \
    _avail(XrGoogleCloudAuthInfoKeylessANDROID, XR_TYPE_GOOGLE_CLOUD_AUTH_INFO_KEYLESS_ANDROID) \





#అయితే_ముగింపు

