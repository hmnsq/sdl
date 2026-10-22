#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ OPENXR_REFLECTION_ਮਾਪਾ_STRUCTS_H
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ OPENXR_REFLECTION_ਮਾਪਾ_STRUCTS_H 1

/*
** Copyright (c) 2017-2026 The Khronos Group Inc.
**
** SPDX-License-Identifier: Apache-2.0 OR MIT
*/

/*
** This header is generated from the Khronos OpenXR XML API Registry.
**
*/

#ਅਨ੍ਤਰ੍ਭਾਵ "openxr.h"

/*
This file contains expansion macros (X Macros) for OpenXR structures that have a parent type.
*/


/// Like XR_LIST_ALL_STRUCTURE_TYPES, but only includes types whose parent struct type is XrCompositionLayerBaseHeader
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XR_LIST_ALL_ਬੱਚਾ_STRUCTURE_TYPES_Xr_Composition_Layer_ਅਧਾਰ_ਸਿਰਲੇਖ(_avail, _unavail) \
    impl_XR_LIST_ALL_ਬੱਚਾ_STRUCTURE_TYPES_Xr_Composition_Layer_ਅਧਾਰ_ਸਿਰਲੇਖ_CORE(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrCompositionLayerBaseHeader()
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ impl_XR_LIST_ALL_ਬੱਚਾ_STRUCTURE_TYPES_Xr_Composition_Layer_ਅਧਾਰ_ਸਿਰਲੇਖ_CORE(_avail, _unavail) \
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
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XR_LIST_ALL_ਬੱਚਾ_STRUCTURE_TYPES_Xr_Event_ਅੰਕੜੇ_ਅਧਾਰ_ਸਿਰਲੇਖ(_avail, _unavail) \
    impl_XR_LIST_ALL_ਬੱਚਾ_STRUCTURE_TYPES_Xr_Event_ਅੰਕੜੇ_ਅਧਾਰ_ਸਿਰਲੇਖ_CORE(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrEventDataBaseHeader()
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ impl_XR_LIST_ALL_ਬੱਚਾ_STRUCTURE_TYPES_Xr_Event_ਅੰਕੜੇ_ਅਧਾਰ_ਸਿਰਲੇਖ_CORE(_avail, _unavail) \
    _avail(Xr_Event_ਅੰਕੜੇ_Events_ਗੁਆਚਾ, XR_TYPE_EVENT_ਅੰਕੜੇ_EVENTS_ਗੁਆਚਾ) \
    _avail(Xr_Event_ਅੰਕੜੇ_Instance_Loss_Pending, XR_TYPE_EVENT_ਅੰਕੜੇ_INSTANCE_LOSS_PENDING) \
    _avail(Xr_Event_ਅੰਕੜੇ_Session_State_ਬਦਲਿਆ, XR_TYPE_EVENT_ਅੰਕੜੇ_SESSION_STATE_ਬਦਲਿਆ) \
    _avail(Xr_Event_ਅੰਕੜੇ_Reference_Space_Change_Pending, XR_TYPE_EVENT_ਅੰਕੜੇ_REFERENCE_SPACE_CHANGE_PENDING) \
    _avail(Xr_Event_ਅੰਕੜੇ_Interaction_Profile_ਬਦਲਿਆ, XR_TYPE_EVENT_ਅੰਕੜੇ_INTERACTION_PROFILE_ਬਦਲਿਆ) \
    _avail(Xr_Event_ਅੰਕੜੇ_Visibility_ਨਕਾਬ_ਬਦਲਿਆ_KHR, XR_TYPE_EVENT_ਅੰਕੜੇ_VISIBILITY_ਨਕਾਬ_ਬਦਲਿਆ_KHR) \
    _avail(Xr_Event_ਅੰਕੜੇ_Perf_Settings_EXT, XR_TYPE_EVENT_ਅੰਕੜੇ_PERF_SETTINGS_EXT) \
    _avail(Xr_Event_ਅੰਕੜੇ_Main_Session_Visibility_ਬਦਲਿਆ_EXTX, XR_TYPE_EVENT_ਅੰਕੜੇ_MAIN_SESSION_VISIBILITY_ਬਦਲਿਆ_EXTX) \
    _avail(Xr_Event_ਅੰਕੜੇ_Display_Refresh_ਦਰ_ਬਦਲਿਆ_FB, XR_TYPE_EVENT_ਅੰਕੜੇ_DISPLAY_REFRESH_ਦਰ_ਬਦਲਿਆ_FB) \
    _avail(Xr_Event_ਅੰਕੜੇ_Vive_Tracker_Connected_HTCX, XR_TYPE_EVENT_ਅੰਕੜੇ_VIVE_TRACKER_CONNECTED_HTCX) \
    _avail(Xr_Event_ਅੰਕੜੇ_Spatial_Anchor_Create_Complete_FB, XR_TYPE_EVENT_ਅੰਕੜੇ_SPATIAL_ANCHOR_CREATE_COMPLETE_FB) \
    _avail(Xr_Event_ਅੰਕੜੇ_Space_ਸੈੱਟ_ਸਥਿਤੀ_Complete_FB, XR_TYPE_EVENT_ਅੰਕੜੇ_SPACE_ਸੈੱਟ_ਸਥਿਤੀ_COMPLETE_FB) \
    _avail(Xr_Event_ਅੰਕੜੇ_Passthrough_State_ਬਦਲਿਆ_FB, XR_TYPE_EVENT_ਅੰਕੜੇ_PASSTHROUGH_STATE_ਬਦਲਿਆ_FB) \
    _avail(Xr_Event_ਅੰਕੜੇ_Marker_Tracking_Update_VARJO, XR_TYPE_EVENT_ਅੰਕੜੇ_MARKER_TRACKING_UPDATE_VARJO) \
    _avail(Xr_Event_ਅੰਕੜੇ_Localization_ਬਦਲਿਆ_ML, XR_TYPE_EVENT_ਅੰਕੜੇ_LOCALIZATION_ਬਦਲਿਆ_ML) \
    _avail(Xr_Event_ਅੰਕੜੇ_Space_Query_Results_ਉਪਲਬਧ_FB, XR_TYPE_EVENT_ਅੰਕੜੇ_SPACE_QUERY_RESULTS_ਉਪਲਬਧ_FB) \
    _avail(Xr_Event_ਅੰਕੜੇ_Space_Query_Complete_FB, XR_TYPE_EVENT_ਅੰਕੜੇ_SPACE_QUERY_COMPLETE_FB) \
    _avail(Xr_Event_ਅੰਕੜੇ_Space_Save_Complete_FB, XR_TYPE_EVENT_ਅੰਕੜੇ_SPACE_SAVE_COMPLETE_FB) \
    _avail(Xr_Event_ਅੰਕੜੇ_Space_Erase_Complete_FB, XR_TYPE_EVENT_ਅੰਕੜੇ_SPACE_ERASE_COMPLETE_FB) \
    _avail(Xr_Event_ਅੰਕੜੇ_Space_Share_Complete_FB, XR_TYPE_EVENT_ਅੰਕੜੇ_SPACE_SHARE_COMPLETE_FB) \
    _avail(Xr_Event_ਅੰਕੜੇ_Scene_Capture_Complete_FB, XR_TYPE_EVENT_ਅੰਕੜੇ_SCENE_CAPTURE_COMPLETE_FB) \
    _avail(Xr_Event_ਅੰਕੜੇ_Virtual_Keyboard_Commit_ਪਾਠ_META, XR_TYPE_EVENT_ਅੰਕੜੇ_VIRTUAL_KEYBOARD_COMMIT_ਪਾਠ_META) \
    _avail(Xr_Event_ਅੰਕੜੇ_Virtual_Keyboard_Backspace_META, XR_TYPE_EVENT_ਅੰਕੜੇ_VIRTUAL_KEYBOARD_BACKSPACE_META) \
    _avail(Xr_Event_ਅੰਕੜੇ_Virtual_Keyboard_Enter_META, XR_TYPE_EVENT_ਅੰਕੜੇ_VIRTUAL_KEYBOARD_ENTER_META) \
    _avail(Xr_Event_ਅੰਕੜੇ_Virtual_Keyboard_Shown_META, XR_TYPE_EVENT_ਅੰਕੜੇ_VIRTUAL_KEYBOARD_SHOWN_META) \
    _avail(Xr_Event_ਅੰਕੜੇ_Virtual_Keyboard_Hidden_META, XR_TYPE_EVENT_ਅੰਕੜੇ_VIRTUAL_KEYBOARD_HIDDEN_META) \
    _avail(Xr_Event_ਅੰਕੜੇ_Space_List_Save_Complete_FB, XR_TYPE_EVENT_ਅੰਕੜੇ_SPACE_LIST_SAVE_COMPLETE_FB) \
    _avail(Xr_Event_ਅੰਕੜੇ_Space_Discovery_Results_ਉਪਲਬਧ_META, XR_TYPE_EVENT_ਅੰਕੜੇ_SPACE_DISCOVERY_RESULTS_ਉਪਲਬਧ_META) \
    _avail(Xr_Event_ਅੰਕੜੇ_Space_Discovery_Complete_META, XR_TYPE_EVENT_ਅੰਕੜੇ_SPACE_DISCOVERY_COMPLETE_META) \
    _avail(Xr_Event_ਅੰਕੜੇ_Spaces_Save_ਨਤੀਜਾ_META, XR_TYPE_EVENT_ਅੰਕੜੇ_SPACES_SAVE_ਨਤੀਜਾ_META) \
    _avail(Xr_Event_ਅੰਕੜੇ_Spaces_Erase_ਨਤੀਜਾ_META, XR_TYPE_EVENT_ਅੰਕੜੇ_SPACES_ERASE_ਨਤੀਜਾ_META) \
    _avail(Xr_Event_ਅੰਕੜੇ_Passthrough_Layer_Resumed_META, XR_TYPE_EVENT_ਅੰਕੜੇ_PASSTHROUGH_LAYER_RESUMED_META) \
    _avail(Xr_Event_ਅੰਕੜੇ_Share_Spaces_Complete_META, XR_TYPE_EVENT_ਅੰਕੜੇ_SHARE_SPACES_COMPLETE_META) \
    _avail(Xr_Event_ਅੰਕੜੇ_Interaction_Render_Models_ਬਦਲਿਆ_EXT, XR_TYPE_EVENT_ਅੰਕੜੇ_INTERACTION_RENDER_MODELS_ਬਦਲਿਆ_EXT) \
    _avail(Xr_Event_ਅੰਕੜੇ_Sense_ਅੰਕੜੇ_Provider_State_ਬਦਲਿਆ_BD, XR_TYPE_EVENT_ਅੰਕੜੇ_SENSE_ਅੰਕੜੇ_PROVIDER_STATE_ਬਦਲਿਆ_BD) \
    _avail(Xr_Event_ਅੰਕੜੇ_Sense_ਅੰਕੜੇ_Updated_BD, XR_TYPE_EVENT_ਅੰਕੜੇ_SENSE_ਅੰਕੜੇ_UPDATED_BD) \
    _avail(Xr_Event_ਅੰਕੜੇ_Recommended_Resolution_ਬਦਲਿਆ_ANDROID, XR_TYPE_EVENT_ਅੰਕੜੇ_RECOMMENDED_RESOLUTION_ਬਦਲਿਆ_ANDROID) \
    _avail(Xr_Event_ਅੰਕੜੇ_User_Presence_ਬਦਲਿਆ_EXT, XR_TYPE_EVENT_ਅੰਕੜੇ_USER_PRESENCE_ਬਦਲਿਆ_EXT) \
    _avail(Xr_Event_ਅੰਕੜੇ_Headset_Fit_ਬਦਲਿਆ_ML, XR_TYPE_EVENT_ਅੰਕੜੇ_HEADSET_FIT_ਬਦਲਿਆ_ML) \
    _avail(Xr_Event_ਅੰਕੜੇ_Eye_Calibration_ਬਦਲਿਆ_ML, XR_TYPE_EVENT_ਅੰਕੜੇ_EYE_CALIBRATION_ਬਦਲਿਆ_ML) \
    _avail(Xr_Event_ਅੰਕੜੇ_Boundary_Visibility_ਬਦਲਿਆ_META, XR_TYPE_EVENT_ਅੰਕੜੇ_BOUNDARY_VISIBILITY_ਬਦਲਿਆ_META) \
    _avail(Xr_Event_ਅੰਕੜੇ_ਸ਼ੁਰੂ_Colocation_Advertisement_Complete_META, XR_TYPE_EVENT_ਅੰਕੜੇ_ਸ਼ੁਰੂ_COLOCATION_ADVERTISEMENT_COMPLETE_META) \
    _avail(Xr_Event_ਅੰਕੜੇ_Stop_Colocation_Advertisement_Complete_META, XR_TYPE_EVENT_ਅੰਕੜੇ_STOP_COLOCATION_ADVERTISEMENT_COMPLETE_META) \
    _avail(Xr_Event_ਅੰਕੜੇ_Colocation_Advertisement_Complete_META, XR_TYPE_EVENT_ਅੰਕੜੇ_COLOCATION_ADVERTISEMENT_COMPLETE_META) \
    _avail(Xr_Event_ਅੰਕੜੇ_ਸ਼ੁਰੂ_Colocation_Discovery_Complete_META, XR_TYPE_EVENT_ਅੰਕੜੇ_ਸ਼ੁਰੂ_COLOCATION_DISCOVERY_COMPLETE_META) \
    _avail(Xr_Event_ਅੰਕੜੇ_Colocation_Discovery_ਨਤੀਜਾ_META, XR_TYPE_EVENT_ਅੰਕੜੇ_COLOCATION_DISCOVERY_ਨਤੀਜਾ_META) \
    _avail(Xr_Event_ਅੰਕੜੇ_Colocation_Discovery_Complete_META, XR_TYPE_EVENT_ਅੰਕੜੇ_COLOCATION_DISCOVERY_COMPLETE_META) \
    _avail(Xr_Event_ਅੰਕੜੇ_Stop_Colocation_Discovery_Complete_META, XR_TYPE_EVENT_ਅੰਕੜੇ_STOP_COLOCATION_DISCOVERY_COMPLETE_META) \
    _avail(Xr_Event_ਅੰਕੜੇ_Image_Tracking_ਗੁਆਚਾ_ANDROID, XR_TYPE_EVENT_ਅੰਕੜੇ_IMAGE_TRACKING_ਗੁਆਚਾ_ANDROID) \
    _avail(Xr_Event_ਅੰਕੜੇ_Spatial_Discovery_Recommended_EXT, XR_TYPE_EVENT_ਅੰਕੜੇ_SPATIAL_DISCOVERY_RECOMMENDED_EXT) \
    _avail(Xr_Event_ਅੰਕੜੇ_Geospatial_Tracker_State_ਬਦਲਿਆ_ANDROID, XR_TYPE_EVENT_ਅੰਕੜੇ_GEOSPATIAL_TRACKER_STATE_ਬਦਲਿਆ_ANDROID) \
    _avail(Xr_Event_ਅੰਕੜੇ_Spatial_Container_Closed_EXT, XR_TYPE_EVENT_ਅੰਕੜੇ_SPATIAL_CONTAINER_CLOSED_EXT) \
    _avail(Xr_Event_ਅੰਕੜੇ_Spatial_Container_Bounds_ਬਦਲਿਆ_EXT, XR_TYPE_EVENT_ਅੰਕੜੇ_SPATIAL_CONTAINER_BOUNDS_ਬਦਲਿਆ_EXT) \
    _avail(Xr_Event_ਅੰਕੜੇ_Spatial_Container_Visible_ਬਦਲਿਆ_EXT, XR_TYPE_EVENT_ਅੰਕੜੇ_SPATIAL_CONTAINER_VISIBLE_ਬਦਲਿਆ_EXT) \
    _avail(Xr_Event_ਅੰਕੜੇ_Spatial_Container_Visible_Request_Denied_EXT, XR_TYPE_EVENT_ਅੰਕੜੇ_SPATIAL_CONTAINER_VISIBLE_REQUEST_DENIED_EXT) \
    _avail(Xr_Event_ਅੰਕੜੇ_Spatial_Container_Interactable_ਬਦਲਿਆ_EXT, XR_TYPE_EVENT_ਅੰਕੜੇ_SPATIAL_CONTAINER_INTERACTABLE_ਬਦਲਿਆ_EXT) \
    _avail(Xr_Event_ਅੰਕੜੇ_Spatial_Container_Bounds_ਬਹੁਲਕ_Request_Denied_EXT, XR_TYPE_EVENT_ਅੰਕੜੇ_SPATIAL_CONTAINER_BOUNDS_ਬਹੁਲਕ_REQUEST_DENIED_EXT) \
    _avail(Xr_Event_ਅੰਕੜੇ_View_Configuration_Views_ਬਦਲਿਆ_EXT, XR_TYPE_EVENT_ਅੰਕੜੇ_VIEW_CONFIGURATION_VIEWS_ਬਦਲਿਆ_EXT) \





/// Like XR_LIST_ALL_STRUCTURE_TYPES, but only includes types whose parent struct type is XrHapticBaseHeader
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XR_LIST_ALL_ਬੱਚਾ_STRUCTURE_TYPES_Xr_Haptic_ਅਧਾਰ_ਸਿਰਲੇਖ(_avail, _unavail) \
    impl_XR_LIST_ALL_ਬੱਚਾ_STRUCTURE_TYPES_Xr_Haptic_ਅਧਾਰ_ਸਿਰਲੇਖ_CORE(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrHapticBaseHeader()
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ impl_XR_LIST_ALL_ਬੱਚਾ_STRUCTURE_TYPES_Xr_Haptic_ਅਧਾਰ_ਸਿਰਲੇਖ_CORE(_avail, _unavail) \
    _avail(XrHapticVibration, XR_TYPE_HAPTIC_VIBRATION) \
    _avail(XrHapticAmplitudeEnvelopeVibrationFB, XR_TYPE_HAPTIC_AMPLITUDE_ENVELOPE_VIBRATION_FB) \
    _avail(XrHapticPcmVibrationFB, XR_TYPE_HAPTIC_PCM_VIBRATION_FB) \
    _avail(XrHapticParametricVibrationEXT, XR_TYPE_HAPTIC_PARAMETRIC_VIBRATION_EXT) \





/// Like XR_LIST_ALL_STRUCTURE_TYPES, but only includes types whose parent struct type is XrSwapchainImageBaseHeader
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XR_LIST_ALL_ਬੱਚਾ_STRUCTURE_TYPES_Xr_Swapchain_Image_ਅਧਾਰ_ਸਿਰਲੇਖ(_avail, _unavail) \
    impl_XR_LIST_ALL_ਬੱਚਾ_STRUCTURE_TYPES_Xr_Swapchain_Image_ਅਧਾਰ_ਸਿਰਲੇਖ_CORE(_avail, _unavail) \
    impl_XR_LIST_ALL_ਬੱਚਾ_STRUCTURE_TYPES_Xr_Swapchain_Image_ਅਧਾਰ_ਸਿਰਲੇਖ_XR_USE_GRAPHICS_API_D3_D11(_avail, _unavail) \
    impl_XR_LIST_ALL_ਬੱਚਾ_STRUCTURE_TYPES_Xr_Swapchain_Image_ਅਧਾਰ_ਸਿਰਲੇਖ_XR_USE_GRAPHICS_API_D3_D12(_avail, _unavail) \
    impl_XR_LIST_ALL_ਬੱਚਾ_STRUCTURE_TYPES_Xr_Swapchain_Image_ਅਧਾਰ_ਸਿਰਲੇਖ_XR_USE_GRAPHICS_API_METAL(_avail, _unavail) \
    impl_XR_LIST_ALL_ਬੱਚਾ_STRUCTURE_TYPES_Xr_Swapchain_Image_ਅਧਾਰ_ਸਿਰਲੇਖ_XR_USE_GRAPHICS_API_OPENGL(_avail, _unavail) \
    impl_XR_LIST_ALL_ਬੱਚਾ_STRUCTURE_TYPES_Xr_Swapchain_Image_ਅਧਾਰ_ਸਿਰਲੇਖ_XR_USE_GRAPHICS_API_OPENGL_ES(_avail, _unavail) \
    impl_XR_LIST_ALL_ਬੱਚਾ_STRUCTURE_TYPES_Xr_Swapchain_Image_ਅਧਾਰ_ਸਿਰਲੇਖ_XR_USE_GRAPHICS_API_VULKAN(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrSwapchainImageBaseHeader()
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ impl_XR_LIST_ALL_ਬੱਚਾ_STRUCTURE_TYPES_Xr_Swapchain_Image_ਅਧਾਰ_ਸਿਰਲੇਖ_CORE(_avail, _unavail) \


#ਜੇ defined(XR_USE_GRAPHICS_API_D3D11)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ impl_XR_LIST_ALL_ਬੱਚਾ_STRUCTURE_TYPES_Xr_Swapchain_Image_ਅਧਾਰ_ਸਿਰਲੇਖ_XR_USE_GRAPHICS_API_D3_D11(_avail, _unavail) \
    _avail(XrSwapchainImageD3D11KHR, XR_TYPE_SWAPCHAIN_IMAGE_D3D11_KHR) \

#ਨਹੀਂਤਾਂ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ impl_XR_LIST_ALL_ਬੱਚਾ_STRUCTURE_TYPES_Xr_Swapchain_Image_ਅਧਾਰ_ਸਿਰਲੇਖ_XR_USE_GRAPHICS_API_D3_D11(_avail, _unavail) \
    _unavail(XrSwapchainImageD3D11KHR, XR_TYPE_SWAPCHAIN_IMAGE_D3D11_KHR) \

#ਜੇ_ਅੰਤ

#ਜੇ defined(XR_USE_GRAPHICS_API_D3D12)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ impl_XR_LIST_ALL_ਬੱਚਾ_STRUCTURE_TYPES_Xr_Swapchain_Image_ਅਧਾਰ_ਸਿਰਲੇਖ_XR_USE_GRAPHICS_API_D3_D12(_avail, _unavail) \
    _avail(XrSwapchainImageD3D12KHR, XR_TYPE_SWAPCHAIN_IMAGE_D3D12_KHR) \

#ਨਹੀਂਤਾਂ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ impl_XR_LIST_ALL_ਬੱਚਾ_STRUCTURE_TYPES_Xr_Swapchain_Image_ਅਧਾਰ_ਸਿਰਲੇਖ_XR_USE_GRAPHICS_API_D3_D12(_avail, _unavail) \
    _unavail(XrSwapchainImageD3D12KHR, XR_TYPE_SWAPCHAIN_IMAGE_D3D12_KHR) \

#ਜੇ_ਅੰਤ

#ਜੇ defined(XR_USE_GRAPHICS_API_METAL)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ impl_XR_LIST_ALL_ਬੱਚਾ_STRUCTURE_TYPES_Xr_Swapchain_Image_ਅਧਾਰ_ਸਿਰਲੇਖ_XR_USE_GRAPHICS_API_METAL(_avail, _unavail) \
    _avail(XrSwapchainImageMetalKHR, XR_TYPE_SWAPCHAIN_IMAGE_METAL_KHR) \

#ਨਹੀਂਤਾਂ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ impl_XR_LIST_ALL_ਬੱਚਾ_STRUCTURE_TYPES_Xr_Swapchain_Image_ਅਧਾਰ_ਸਿਰਲੇਖ_XR_USE_GRAPHICS_API_METAL(_avail, _unavail) \
    _unavail(XrSwapchainImageMetalKHR, XR_TYPE_SWAPCHAIN_IMAGE_METAL_KHR) \

#ਜੇ_ਅੰਤ

#ਜੇ defined(XR_USE_GRAPHICS_API_OPENGL)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ impl_XR_LIST_ALL_ਬੱਚਾ_STRUCTURE_TYPES_Xr_Swapchain_Image_ਅਧਾਰ_ਸਿਰਲੇਖ_XR_USE_GRAPHICS_API_OPENGL(_avail, _unavail) \
    _avail(XrSwapchainImageOpenGLKHR, XR_TYPE_SWAPCHAIN_IMAGE_OPENGL_KHR) \

#ਨਹੀਂਤਾਂ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ impl_XR_LIST_ALL_ਬੱਚਾ_STRUCTURE_TYPES_Xr_Swapchain_Image_ਅਧਾਰ_ਸਿਰਲੇਖ_XR_USE_GRAPHICS_API_OPENGL(_avail, _unavail) \
    _unavail(XrSwapchainImageOpenGLKHR, XR_TYPE_SWAPCHAIN_IMAGE_OPENGL_KHR) \

#ਜੇ_ਅੰਤ

#ਜੇ defined(XR_USE_GRAPHICS_API_OPENGL_ES)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ impl_XR_LIST_ALL_ਬੱਚਾ_STRUCTURE_TYPES_Xr_Swapchain_Image_ਅਧਾਰ_ਸਿਰਲੇਖ_XR_USE_GRAPHICS_API_OPENGL_ES(_avail, _unavail) \
    _avail(XrSwapchainImageOpenGLESKHR, XR_TYPE_SWAPCHAIN_IMAGE_OPENGL_ES_KHR) \

#ਨਹੀਂਤਾਂ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ impl_XR_LIST_ALL_ਬੱਚਾ_STRUCTURE_TYPES_Xr_Swapchain_Image_ਅਧਾਰ_ਸਿਰਲੇਖ_XR_USE_GRAPHICS_API_OPENGL_ES(_avail, _unavail) \
    _unavail(XrSwapchainImageOpenGLESKHR, XR_TYPE_SWAPCHAIN_IMAGE_OPENGL_ES_KHR) \

#ਜੇ_ਅੰਤ

#ਜੇ defined(XR_USE_GRAPHICS_API_VULKAN)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ impl_XR_LIST_ALL_ਬੱਚਾ_STRUCTURE_TYPES_Xr_Swapchain_Image_ਅਧਾਰ_ਸਿਰਲੇਖ_XR_USE_GRAPHICS_API_VULKAN(_avail, _unavail) \
    _avail(XrSwapchainImageVulkanKHR, XR_TYPE_SWAPCHAIN_IMAGE_VULKAN_KHR) \

#ਨਹੀਂਤਾਂ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ impl_XR_LIST_ALL_ਬੱਚਾ_STRUCTURE_TYPES_Xr_Swapchain_Image_ਅਧਾਰ_ਸਿਰਲੇਖ_XR_USE_GRAPHICS_API_VULKAN(_avail, _unavail) \
    _unavail(XrSwapchainImageVulkanKHR, XR_TYPE_SWAPCHAIN_IMAGE_VULKAN_KHR) \

#ਜੇ_ਅੰਤ




/// Like XR_LIST_ALL_STRUCTURE_TYPES, but only includes types whose parent struct type is XrLoaderInitInfoBaseHeaderKHR
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XR_LIST_ALL_ਬੱਚਾ_STRUCTURE_TYPES_Xr_Loader_Init_Info_ਅਧਾਰ_ਸਿਰਲੇਖ_KHR(_avail, _unavail) \
    impl_XR_LIST_ALL_ਬੱਚਾ_STRUCTURE_TYPES_Xr_Loader_Init_Info_ਅਧਾਰ_ਸਿਰਲੇਖ_KHR_CORE(_avail, _unavail) \
    impl_XR_LIST_ALL_ਬੱਚਾ_STRUCTURE_TYPES_Xr_Loader_Init_Info_ਅਧਾਰ_ਸਿਰਲੇਖ_KHR_XR_USE_PLATFORM_ANDROID(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrLoaderInitInfoBaseHeaderKHR()
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ impl_XR_LIST_ALL_ਬੱਚਾ_STRUCTURE_TYPES_Xr_Loader_Init_Info_ਅਧਾਰ_ਸਿਰਲੇਖ_KHR_CORE(_avail, _unavail) \
    _avail(XrLoaderInitInfoPropertiesEXT, XR_TYPE_LOADER_INIT_INFO_PROPERTIES_EXT) \


#ਜੇ defined(XR_USE_PLATFORM_ANDROID)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ impl_XR_LIST_ALL_ਬੱਚਾ_STRUCTURE_TYPES_Xr_Loader_Init_Info_ਅਧਾਰ_ਸਿਰਲੇਖ_KHR_XR_USE_PLATFORM_ANDROID(_avail, _unavail) \
    _avail(XrLoaderInitInfoAndroidKHR, XR_TYPE_LOADER_INIT_INFO_ANDROID_KHR) \

#ਨਹੀਂਤਾਂ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ impl_XR_LIST_ALL_ਬੱਚਾ_STRUCTURE_TYPES_Xr_Loader_Init_Info_ਅਧਾਰ_ਸਿਰਲੇਖ_KHR_XR_USE_PLATFORM_ANDROID(_avail, _unavail) \
    _unavail(XrLoaderInitInfoAndroidKHR, XR_TYPE_LOADER_INIT_INFO_ANDROID_KHR) \

#ਜੇ_ਅੰਤ




/// Like XR_LIST_ALL_STRUCTURE_TYPES, but only includes types whose parent struct type is XrBindingModificationBaseHeaderKHR
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XR_LIST_ALL_ਬੱਚਾ_STRUCTURE_TYPES_Xr_Binding_Modification_ਅਧਾਰ_ਸਿਰਲੇਖ_KHR(_avail, _unavail) \
    impl_XR_LIST_ALL_ਬੱਚਾ_STRUCTURE_TYPES_Xr_Binding_Modification_ਅਧਾਰ_ਸਿਰਲੇਖ_KHR_CORE(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrBindingModificationBaseHeaderKHR()
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ impl_XR_LIST_ALL_ਬੱਚਾ_STRUCTURE_TYPES_Xr_Binding_Modification_ਅਧਾਰ_ਸਿਰਲੇਖ_KHR_CORE(_avail, _unavail) \
    _avail(XrInteractionProfileDpadBindingEXT, XR_TYPE_INTERACTION_PROFILE_DPAD_BINDING_EXT) \
    _avail(Xr_Interaction_Profile_Analog_ਹੱਦ_VALVE, XR_TYPE_INTERACTION_PROFILE_ANALOG_ਹੱਦ_VALVE) \





/// Like XR_LIST_ALL_STRUCTURE_TYPES, but only includes types whose parent struct type is XrSwapchainStateBaseHeaderFB
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XR_LIST_ALL_ਬੱਚਾ_STRUCTURE_TYPES_Xr_Swapchain_State_ਅਧਾਰ_ਸਿਰਲੇਖ_FB(_avail, _unavail) \
    impl_XR_LIST_ALL_ਬੱਚਾ_STRUCTURE_TYPES_Xr_Swapchain_State_ਅਧਾਰ_ਸਿਰਲੇਖ_FB_CORE(_avail, _unavail) \
    impl_XR_LIST_ALL_ਬੱਚਾ_STRUCTURE_TYPES_Xr_Swapchain_State_ਅਧਾਰ_ਸਿਰਲੇਖ_FB_XR_USE_GRAPHICS_API_OPENGL_ES(_avail, _unavail) \
    impl_XR_LIST_ALL_ਬੱਚਾ_STRUCTURE_TYPES_Xr_Swapchain_State_ਅਧਾਰ_ਸਿਰਲੇਖ_FB_XR_USE_GRAPHICS_API_VULKAN(_avail, _unavail) \
    impl_XR_LIST_ALL_ਬੱਚਾ_STRUCTURE_TYPES_Xr_Swapchain_State_ਅਧਾਰ_ਸਿਰਲੇਖ_FB_XR_USE_PLATFORM_ANDROID(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrSwapchainStateBaseHeaderFB()
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ impl_XR_LIST_ALL_ਬੱਚਾ_STRUCTURE_TYPES_Xr_Swapchain_State_ਅਧਾਰ_ਸਿਰਲੇਖ_FB_CORE(_avail, _unavail) \
    _avail(XrSwapchainStateFoveationFB, XR_TYPE_SWAPCHAIN_STATE_FOVEATION_FB) \


#ਜੇ defined(XR_USE_GRAPHICS_API_OPENGL_ES)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ impl_XR_LIST_ALL_ਬੱਚਾ_STRUCTURE_TYPES_Xr_Swapchain_State_ਅਧਾਰ_ਸਿਰਲੇਖ_FB_XR_USE_GRAPHICS_API_OPENGL_ES(_avail, _unavail) \
    _avail(XrSwapchainStateSamplerOpenGLESFB, XR_TYPE_SWAPCHAIN_STATE_SAMPLER_OPENGL_ES_FB) \

#ਨਹੀਂਤਾਂ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ impl_XR_LIST_ALL_ਬੱਚਾ_STRUCTURE_TYPES_Xr_Swapchain_State_ਅਧਾਰ_ਸਿਰਲੇਖ_FB_XR_USE_GRAPHICS_API_OPENGL_ES(_avail, _unavail) \
    _unavail(XrSwapchainStateSamplerOpenGLESFB, XR_TYPE_SWAPCHAIN_STATE_SAMPLER_OPENGL_ES_FB) \

#ਜੇ_ਅੰਤ

#ਜੇ defined(XR_USE_GRAPHICS_API_VULKAN)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ impl_XR_LIST_ALL_ਬੱਚਾ_STRUCTURE_TYPES_Xr_Swapchain_State_ਅਧਾਰ_ਸਿਰਲੇਖ_FB_XR_USE_GRAPHICS_API_VULKAN(_avail, _unavail) \
    _avail(XrSwapchainStateSamplerVulkanFB, XR_TYPE_SWAPCHAIN_STATE_SAMPLER_VULKAN_FB) \

#ਨਹੀਂਤਾਂ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ impl_XR_LIST_ALL_ਬੱਚਾ_STRUCTURE_TYPES_Xr_Swapchain_State_ਅਧਾਰ_ਸਿਰਲੇਖ_FB_XR_USE_GRAPHICS_API_VULKAN(_avail, _unavail) \
    _unavail(XrSwapchainStateSamplerVulkanFB, XR_TYPE_SWAPCHAIN_STATE_SAMPLER_VULKAN_FB) \

#ਜੇ_ਅੰਤ

#ਜੇ defined(XR_USE_PLATFORM_ANDROID)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ impl_XR_LIST_ALL_ਬੱਚਾ_STRUCTURE_TYPES_Xr_Swapchain_State_ਅਧਾਰ_ਸਿਰਲੇਖ_FB_XR_USE_PLATFORM_ANDROID(_avail, _unavail) \
    _avail(XrSwapchainStateAndroidSurfaceDimensionsFB, XR_TYPE_SWAPCHAIN_STATE_ANDROID_SURFACE_DIMENSIONS_FB) \

#ਨਹੀਂਤਾਂ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ impl_XR_LIST_ALL_ਬੱਚਾ_STRUCTURE_TYPES_Xr_Swapchain_State_ਅਧਾਰ_ਸਿਰਲੇਖ_FB_XR_USE_PLATFORM_ANDROID(_avail, _unavail) \
    _unavail(XrSwapchainStateAndroidSurfaceDimensionsFB, XR_TYPE_SWAPCHAIN_STATE_ANDROID_SURFACE_DIMENSIONS_FB) \

#ਜੇ_ਅੰਤ




/// Like XR_LIST_ALL_STRUCTURE_TYPES, but only includes types whose parent struct type is XrSpatialAnchorsCreateInfoBaseHeaderML
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XR_LIST_ALL_ਬੱਚਾ_STRUCTURE_TYPES_Xr_Spatial_Anchors_Create_Info_ਅਧਾਰ_ਸਿਰਲੇਖ_ML(_avail, _unavail) \
    impl_XR_LIST_ALL_ਬੱਚਾ_STRUCTURE_TYPES_Xr_Spatial_Anchors_Create_Info_ਅਧਾਰ_ਸਿਰਲੇਖ_ML_CORE(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrSpatialAnchorsCreateInfoBaseHeaderML()
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ impl_XR_LIST_ALL_ਬੱਚਾ_STRUCTURE_TYPES_Xr_Spatial_Anchors_Create_Info_ਅਧਾਰ_ਸਿਰਲੇਖ_ML_CORE(_avail, _unavail) \
    _avail(XrSpatialAnchorsCreateInfoFromPoseML, XR_TYPE_SPATIAL_ANCHORS_CREATE_INFO_FROM_POSE_ML) \
    _avail(XrSpatialAnchorsCreateInfoFromUuidsML, XR_TYPE_SPATIAL_ANCHORS_CREATE_INFO_FROM_UUIDS_ML) \





/// Like XR_LIST_ALL_STRUCTURE_TYPES, but only includes types whose parent struct type is XrFutureCompletionBaseHeaderEXT
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XR_LIST_ALL_ਬੱਚਾ_STRUCTURE_TYPES_Xr_Future_Completion_ਅਧਾਰ_ਸਿਰਲੇਖ_EXT(_avail, _unavail) \
    impl_XR_LIST_ALL_ਬੱਚਾ_STRUCTURE_TYPES_Xr_Future_Completion_ਅਧਾਰ_ਸਿਰਲੇਖ_EXT_CORE(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrFutureCompletionBaseHeaderEXT()
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ impl_XR_LIST_ALL_ਬੱਚਾ_STRUCTURE_TYPES_Xr_Future_Completion_ਅਧਾਰ_ਸਿਰਲੇਖ_EXT_CORE(_avail, _unavail) \
    _avail(XrCreateSpatialAnchorsCompletionML, XR_TYPE_CREATE_SPATIAL_ANCHORS_COMPLETION_ML) \
    _avail(XrSpatialAnchorsQueryCompletionML, XR_TYPE_SPATIAL_ANCHORS_QUERY_COMPLETION_ML) \
    _avail(XrSpatialAnchorsPublishCompletionML, XR_TYPE_SPATIAL_ANCHORS_PUBLISH_COMPLETION_ML) \
    _avail(XrSpatialAnchorsDeleteCompletionML, XR_TYPE_SPATIAL_ANCHORS_DELETE_COMPLETION_ML) \
    _avail(XrSpatialAnchorsUpdateExpirationCompletionML, XR_TYPE_SPATIAL_ANCHORS_UPDATE_EXPIRATION_COMPLETION_ML) \
    _avail(Xr_Sense_ਅੰਕੜੇ_Query_Completion_BD, XR_TYPE_SENSE_ਅੰਕੜੇ_QUERY_COMPLETION_BD) \
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
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XR_LIST_ALL_ਬੱਚਾ_STRUCTURE_TYPES_Xr_Spatial_Anchors_Query_Info_ਅਧਾਰ_ਸਿਰਲੇਖ_ML(_avail, _unavail) \
    impl_XR_LIST_ALL_ਬੱਚਾ_STRUCTURE_TYPES_Xr_Spatial_Anchors_Query_Info_ਅਧਾਰ_ਸਿਰਲੇਖ_ML_CORE(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrSpatialAnchorsQueryInfoBaseHeaderML()
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ impl_XR_LIST_ALL_ਬੱਚਾ_STRUCTURE_TYPES_Xr_Spatial_Anchors_Query_Info_ਅਧਾਰ_ਸਿਰਲੇਖ_ML_CORE(_avail, _unavail) \
    _avail(XrSpatialAnchorsQueryInfoRadiusML, XR_TYPE_SPATIAL_ANCHORS_QUERY_INFO_RADIUS_ML) \





/// Like XR_LIST_ALL_STRUCTURE_TYPES, but only includes types whose parent struct type is XrSpaceQueryInfoBaseHeaderFB
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XR_LIST_ALL_ਬੱਚਾ_STRUCTURE_TYPES_Xr_Space_Query_Info_ਅਧਾਰ_ਸਿਰਲੇਖ_FB(_avail, _unavail) \
    impl_XR_LIST_ALL_ਬੱਚਾ_STRUCTURE_TYPES_Xr_Space_Query_Info_ਅਧਾਰ_ਸਿਰਲੇਖ_FB_CORE(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrSpaceQueryInfoBaseHeaderFB()
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ impl_XR_LIST_ALL_ਬੱਚਾ_STRUCTURE_TYPES_Xr_Space_Query_Info_ਅਧਾਰ_ਸਿਰਲੇਖ_FB_CORE(_avail, _unavail) \
    _avail(XrSpaceQueryInfoFB, XR_TYPE_SPACE_QUERY_INFO_FB) \





/// Like XR_LIST_ALL_STRUCTURE_TYPES, but only includes types whose parent struct type is XrSpaceFilterInfoBaseHeaderFB
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XR_LIST_ALL_ਬੱਚਾ_STRUCTURE_TYPES_Xr_Space_Filter_Info_ਅਧਾਰ_ਸਿਰਲੇਖ_FB(_avail, _unavail) \
    impl_XR_LIST_ALL_ਬੱਚਾ_STRUCTURE_TYPES_Xr_Space_Filter_Info_ਅਧਾਰ_ਸਿਰਲੇਖ_FB_CORE(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrSpaceFilterInfoBaseHeaderFB()
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ impl_XR_LIST_ALL_ਬੱਚਾ_STRUCTURE_TYPES_Xr_Space_Filter_Info_ਅਧਾਰ_ਸਿਰਲੇਖ_FB_CORE(_avail, _unavail) \
    _avail(XrSpaceUuidFilterInfoFB, XR_TYPE_SPACE_UUID_FILTER_INFO_FB) \
    _avail(XrSpaceComponentFilterInfoFB, XR_TYPE_SPACE_COMPONENT_FILTER_INFO_FB) \





/// Like XR_LIST_ALL_STRUCTURE_TYPES, but only includes types whose parent struct type is XrSpaceFilterBaseHeaderMETA
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XR_LIST_ALL_ਬੱਚਾ_STRUCTURE_TYPES_Xr_Space_Filter_ਅਧਾਰ_ਸਿਰਲੇਖ_META(_avail, _unavail) \
    impl_XR_LIST_ALL_ਬੱਚਾ_STRUCTURE_TYPES_Xr_Space_Filter_ਅਧਾਰ_ਸਿਰਲੇਖ_META_CORE(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrSpaceFilterBaseHeaderMETA()
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ impl_XR_LIST_ALL_ਬੱਚਾ_STRUCTURE_TYPES_Xr_Space_Filter_ਅਧਾਰ_ਸਿਰਲੇਖ_META_CORE(_avail, _unavail) \
    _avail(XrSpaceFilterUuidMETA, XR_TYPE_SPACE_FILTER_UUID_META) \
    _avail(XrSpaceFilterComponentMETA, XR_TYPE_SPACE_FILTER_COMPONENT_META) \





/// Like XR_LIST_ALL_STRUCTURE_TYPES, but only includes types whose parent struct type is XrShareSpacesRecipientBaseHeaderMETA
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XR_LIST_ALL_ਬੱਚਾ_STRUCTURE_TYPES_Xr_Share_Spaces_Recipient_ਅਧਾਰ_ਸਿਰਲੇਖ_META(_avail, _unavail) \
    impl_XR_LIST_ALL_ਬੱਚਾ_STRUCTURE_TYPES_Xr_Share_Spaces_Recipient_ਅਧਾਰ_ਸਿਰਲੇਖ_META_CORE(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrShareSpacesRecipientBaseHeaderMETA()
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ impl_XR_LIST_ALL_ਬੱਚਾ_STRUCTURE_TYPES_Xr_Share_Spaces_Recipient_ਅਧਾਰ_ਸਿਰਲੇਖ_META_CORE(_avail, _unavail) \
    _avail(XrShareSpacesRecipientGroupsMETA, XR_TYPE_SHARE_SPACES_RECIPIENT_GROUPS_META) \





/// Like XR_LIST_ALL_STRUCTURE_TYPES, but only includes types whose parent struct type is XrEnvironmentRaycastFilterBaseHeaderMETA
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XR_LIST_ALL_ਬੱਚਾ_STRUCTURE_TYPES_Xr_Environment_Raycast_Filter_ਅਧਾਰ_ਸਿਰਲੇਖ_META(_avail, _unavail) \
    impl_XR_LIST_ALL_ਬੱਚਾ_STRUCTURE_TYPES_Xr_Environment_Raycast_Filter_ਅਧਾਰ_ਸਿਰਲੇਖ_META_CORE(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrEnvironmentRaycastFilterBaseHeaderMETA()
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ impl_XR_LIST_ALL_ਬੱਚਾ_STRUCTURE_TYPES_Xr_Environment_Raycast_Filter_ਅਧਾਰ_ਸਿਰਲੇਖ_META_CORE(_avail, _unavail) \
    _avail(Xr_Environment_Raycast_Filter_ਦੂਰੀ_META, XR_TYPE_ENVIRONMENT_RAYCAST_FILTER_ਦੂਰੀ_META) \





/// Like XR_LIST_ALL_STRUCTURE_TYPES, but only includes types whose parent struct type is XrSpatialCapabilityConfigurationBaseHeaderEXT
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XR_LIST_ALL_ਬੱਚਾ_STRUCTURE_TYPES_Xr_Spatial_Capability_Configuration_ਅਧਾਰ_ਸਿਰਲੇਖ_EXT(_avail, _unavail) \
    impl_XR_LIST_ALL_ਬੱਚਾ_STRUCTURE_TYPES_Xr_Spatial_Capability_Configuration_ਅਧਾਰ_ਸਿਰਲੇਖ_EXT_CORE(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrSpatialCapabilityConfigurationBaseHeaderEXT()
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ impl_XR_LIST_ALL_ਬੱਚਾ_STRUCTURE_TYPES_Xr_Spatial_Capability_Configuration_ਅਧਾਰ_ਸਿਰਲੇਖ_EXT_CORE(_avail, _unavail) \
    _avail(XrSpatialCapabilityConfigurationPlaneTrackingEXT, XR_TYPE_SPATIAL_CAPABILITY_CONFIGURATION_PLANE_TRACKING_EXT) \
    _avail(Xr_Spatial_Capability_Configuration_Qr_ਕੋਡ_EXT, XR_TYPE_SPATIAL_CAPABILITY_CONFIGURATION_QR_ਕੋਡ_EXT) \
    _avail(Xr_Spatial_Capability_Configuration_Micro_Qr_ਕੋਡ_EXT, XR_TYPE_SPATIAL_CAPABILITY_CONFIGURATION_MICRO_QR_ਕੋਡ_EXT) \
    _avail(XrSpatialCapabilityConfigurationArucoMarkerEXT, XR_TYPE_SPATIAL_CAPABILITY_CONFIGURATION_ARUCO_MARKER_EXT) \
    _avail(Xr_Spatial_Capability_Configuration_April_ਟੈਗ_EXT, XR_TYPE_SPATIAL_CAPABILITY_CONFIGURATION_APRIL_ਟੈਗ_EXT) \
    _avail(XrSpatialCapabilityConfigurationObjectTrackingEXT, XR_TYPE_SPATIAL_CAPABILITY_CONFIGURATION_OBJECT_TRACKING_EXT) \
    _avail(XrSpatialCapabilityConfigurationAnchorEXT, XR_TYPE_SPATIAL_CAPABILITY_CONFIGURATION_ANCHOR_EXT) \
    _avail(XrSpatialCapabilityConfigurationImageTrackingEXT, XR_TYPE_SPATIAL_CAPABILITY_CONFIGURATION_IMAGE_TRACKING_EXT) \
    _avail(XrSpatialCapabilityConfigurationMeshTrackingEXT, XR_TYPE_SPATIAL_CAPABILITY_CONFIGURATION_MESH_TRACKING_EXT) \
    _avail(XrSpatialCapabilityConfigurationObjectTrackingANDROID, XR_TYPE_SPATIAL_CAPABILITY_CONFIGURATION_OBJECT_TRACKING_ANDROID) \
    _avail(Xr_Spatial_Capability_Configuration_ਡੂੰਘਾਈ_Raycast_ANDROID, XR_TYPE_SPATIAL_CAPABILITY_CONFIGURATION_ਡੂੰਘਾਈ_RAYCAST_ANDROID) \





/// Like XR_LIST_ALL_STRUCTURE_TYPES, but only includes types whose parent struct type is XrCameraPropertyBaseHeaderBD
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XR_LIST_ALL_ਬੱਚਾ_STRUCTURE_TYPES_Xr_Camera_Property_ਅਧਾਰ_ਸਿਰਲੇਖ_BD(_avail, _unavail) \
    impl_XR_LIST_ALL_ਬੱਚਾ_STRUCTURE_TYPES_Xr_Camera_Property_ਅਧਾਰ_ਸਿਰਲੇਖ_BD_CORE(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrCameraPropertyBaseHeaderBD()
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ impl_XR_LIST_ALL_ਬੱਚਾ_STRUCTURE_TYPES_Xr_Camera_Property_ਅਧਾਰ_ਸਿਰਲੇਖ_BD_CORE(_avail, _unavail) \
    _avail(XrCameraPropertyFacingBD, XR_TYPE_CAMERA_PROPERTY_FACING_BD) \
    _avail(XrCameraPropertyPositionBD, XR_TYPE_CAMERA_PROPERTY_POSITION_BD) \
    _avail(XrCameraPropertyCameraTypeBD, XR_TYPE_CAMERA_PROPERTY_CAMERA_TYPE_BD) \





/// Like XR_LIST_ALL_STRUCTURE_TYPES, but only includes types whose parent struct type is XrCameraSupportedCapabilityBaseHeaderBD
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XR_LIST_ALL_ਬੱਚਾ_STRUCTURE_TYPES_Xr_Camera_Supported_Capability_ਅਧਾਰ_ਸਿਰਲੇਖ_BD(_avail, _unavail) \
    impl_XR_LIST_ALL_ਬੱਚਾ_STRUCTURE_TYPES_Xr_Camera_Supported_Capability_ਅਧਾਰ_ਸਿਰਲੇਖ_BD_CORE(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrCameraSupportedCapabilityBaseHeaderBD()
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ impl_XR_LIST_ALL_ਬੱਚਾ_STRUCTURE_TYPES_Xr_Camera_Supported_Capability_ਅਧਾਰ_ਸਿਰਲੇਖ_BD_CORE(_avail, _unavail) \
    _avail(Xr_Camera_Supported_Capability_Image_Resolution_And_ਚੌਖਟਾ_ਦਰ_BD, XR_TYPE_CAMERA_SUPPORTED_CAPABILITY_IMAGE_RESOLUTION_AND_ਚੌਖਟਾ_ਦਰ_BD) \
    _avail(Xr_Camera_Supported_Capability_ਅੰਕੜੇ_Transfer_Type_BD, XR_TYPE_CAMERA_SUPPORTED_CAPABILITY_ਅੰਕੜੇ_TRANSFER_TYPE_BD) \
    _avail(XrCameraSupportedCapabilityImageFormatBD, XR_TYPE_CAMERA_SUPPORTED_CAPABILITY_IMAGE_FORMAT_BD) \
    _avail(XrCameraSupportedCapabilityCameraModelBD, XR_TYPE_CAMERA_SUPPORTED_CAPABILITY_CAMERA_MODEL_BD) \





/// Like XR_LIST_ALL_STRUCTURE_TYPES, but only includes types whose parent struct type is XrCameraCapabilityBaseHeaderBD
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XR_LIST_ALL_ਬੱਚਾ_STRUCTURE_TYPES_Xr_Camera_Capability_ਅਧਾਰ_ਸਿਰਲੇਖ_BD(_avail, _unavail) \
    impl_XR_LIST_ALL_ਬੱਚਾ_STRUCTURE_TYPES_Xr_Camera_Capability_ਅਧਾਰ_ਸਿਰਲੇਖ_BD_CORE(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrCameraCapabilityBaseHeaderBD()
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ impl_XR_LIST_ALL_ਬੱਚਾ_STRUCTURE_TYPES_Xr_Camera_Capability_ਅਧਾਰ_ਸਿਰਲੇਖ_BD_CORE(_avail, _unavail) \
    _avail(Xr_Camera_Capability_Image_Resolution_And_ਚੌਖਟਾ_ਦਰ_BD, XR_TYPE_CAMERA_CAPABILITY_IMAGE_RESOLUTION_AND_ਚੌਖਟਾ_ਦਰ_BD) \
    _avail(Xr_Camera_Capability_ਅੰਕੜੇ_Transfer_Type_BD, XR_TYPE_CAMERA_CAPABILITY_ਅੰਕੜੇ_TRANSFER_TYPE_BD) \
    _avail(XrCameraCapabilityImageFormatBD, XR_TYPE_CAMERA_CAPABILITY_IMAGE_FORMAT_BD) \
    _avail(XrCameraCapabilityCameraModelBD, XR_TYPE_CAMERA_CAPABILITY_CAMERA_MODEL_BD) \





/// Like XR_LIST_ALL_STRUCTURE_TYPES, but only includes types whose parent struct type is XrCameraImageDataBaseHeaderBD
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XR_LIST_ALL_ਬੱਚਾ_STRUCTURE_TYPES_Xr_Camera_Image_ਅੰਕੜੇ_ਅਧਾਰ_ਸਿਰਲੇਖ_BD(_avail, _unavail) \
    impl_XR_LIST_ALL_ਬੱਚਾ_STRUCTURE_TYPES_Xr_Camera_Image_ਅੰਕੜੇ_ਅਧਾਰ_ਸਿਰਲੇਖ_BD_CORE(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrCameraImageDataBaseHeaderBD()
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ impl_XR_LIST_ALL_ਬੱਚਾ_STRUCTURE_TYPES_Xr_Camera_Image_ਅੰਕੜੇ_ਅਧਾਰ_ਸਿਰਲੇਖ_BD_CORE(_avail, _unavail) \
    _avail(Xr_Camera_Image_ਅੰਕੜੇ_Raw_ਬਫਰ_BD, XR_TYPE_CAMERA_IMAGE_ਅੰਕੜੇ_RAW_ਬਫਰ_BD) \





/// Like XR_LIST_ALL_STRUCTURE_TYPES, but only includes types whose parent struct type is XrGoogleCloudAuthInfoBaseHeaderANDROID
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XR_LIST_ALL_ਬੱਚਾ_STRUCTURE_TYPES_Xr_Google_Cloud_Auth_Info_ਅਧਾਰ_ਸਿਰਲੇਖ_ANDROID(_avail, _unavail) \
    impl_XR_LIST_ALL_ਬੱਚਾ_STRUCTURE_TYPES_Xr_Google_Cloud_Auth_Info_ਅਧਾਰ_ਸਿਰਲੇਖ_ANDROID_CORE(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrGoogleCloudAuthInfoBaseHeaderANDROID()
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ impl_XR_LIST_ALL_ਬੱਚਾ_STRUCTURE_TYPES_Xr_Google_Cloud_Auth_Info_ਅਧਾਰ_ਸਿਰਲੇਖ_ANDROID_CORE(_avail, _unavail) \
    _avail(Xr_Google_Cloud_Auth_Info_Api_ਕੁੰਜੀ_ANDROID, XR_TYPE_GOOGLE_CLOUD_AUTH_INFO_API_ਕੁੰਜੀ_ANDROID) \
    _avail(XrGoogleCloudAuthInfoTokenANDROID, XR_TYPE_GOOGLE_CLOUD_AUTH_INFO_TOKEN_ANDROID) \
    _avail(XrGoogleCloudAuthInfoKeylessANDROID, XR_TYPE_GOOGLE_CLOUD_AUTH_INFO_KEYLESS_ANDROID) \





#ਜੇ_ਅੰਤ

