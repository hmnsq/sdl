#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ OPENXR_REFLECTION_ಪೋಷಕ_STRUCTS_H
#ವ್ಯಾಖ್ಯಾನಿಸು OPENXR_REFLECTION_ಪೋಷಕ_STRUCTS_H 1

/*
** Copyright (c) 2017-2026 The Khronos Group Inc.
**
** SPDX-License-Identifier: Apache-2.0 OR MIT
*/

/*
** This header is generated from the Khronos OpenXR XML API Registry.
**
*/

#ಅನ್ತರ್ಭಾವ "openxr.h"

/*
This file contains expansion macros (X Macros) for OpenXR structures that have a parent type.
*/


/// Like XR_LIST_ALL_STRUCTURE_TYPES, but only includes types whose parent struct type is XrCompositionLayerBaseHeader
#ವ್ಯಾಖ್ಯಾನಿಸು XR_LIST_ALL_ಮಗು_STRUCTURE_TYPES_Xr_Composition_Layer_ತಳ_ಶೀರ್ಷಿಕೆ(_avail, _unavail) \
    impl_XR_LIST_ALL_ಮಗು_STRUCTURE_TYPES_Xr_Composition_Layer_ತಳ_ಶೀರ್ಷಿಕೆ_CORE(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrCompositionLayerBaseHeader()
#ವ್ಯಾಖ್ಯಾನಿಸು impl_XR_LIST_ALL_ಮಗು_STRUCTURE_TYPES_Xr_Composition_Layer_ತಳ_ಶೀರ್ಷಿಕೆ_CORE(_avail, _unavail) \
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
#ವ್ಯಾಖ್ಯಾನಿಸು XR_LIST_ALL_ಮಗು_STRUCTURE_TYPES_Xr_Event_ದತ್ತಾಂಶ_ತಳ_ಶೀರ್ಷಿಕೆ(_avail, _unavail) \
    impl_XR_LIST_ALL_ಮಗು_STRUCTURE_TYPES_Xr_Event_ದತ್ತಾಂಶ_ತಳ_ಶೀರ್ಷಿಕೆ_CORE(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrEventDataBaseHeader()
#ವ್ಯಾಖ್ಯಾನಿಸು impl_XR_LIST_ALL_ಮಗು_STRUCTURE_TYPES_Xr_Event_ದತ್ತಾಂಶ_ತಳ_ಶೀರ್ಷಿಕೆ_CORE(_avail, _unavail) \
    _avail(Xr_Event_ದತ್ತಾಂಶ_Events_ಕಳೆದುಹೋದ, XR_TYPE_EVENT_ದತ್ತಾಂಶ_EVENTS_ಕಳೆದುಹೋದ) \
    _avail(Xr_Event_ದತ್ತಾಂಶ_Instance_Loss_Pending, XR_TYPE_EVENT_ದತ್ತಾಂಶ_INSTANCE_LOSS_PENDING) \
    _avail(Xr_Event_ದತ್ತಾಂಶ_Session_State_ಬದಲಾಯಿತು, XR_TYPE_EVENT_ದತ್ತಾಂಶ_SESSION_STATE_ಬದಲಾಯಿತು) \
    _avail(Xr_Event_ದತ್ತಾಂಶ_Reference_Space_Change_Pending, XR_TYPE_EVENT_ದತ್ತಾಂಶ_REFERENCE_SPACE_CHANGE_PENDING) \
    _avail(Xr_Event_ದತ್ತಾಂಶ_Interaction_Profile_ಬದಲಾಯಿತು, XR_TYPE_EVENT_ದತ್ತಾಂಶ_INTERACTION_PROFILE_ಬದಲಾಯಿತು) \
    _avail(Xr_Event_ದತ್ತಾಂಶ_Visibility_ಮುಖವಾಡ_ಬದಲಾಯಿತು_KHR, XR_TYPE_EVENT_ದತ್ತಾಂಶ_VISIBILITY_ಮುಖವಾಡ_ಬದಲಾಯಿತು_KHR) \
    _avail(Xr_Event_ದತ್ತಾಂಶ_Perf_Settings_EXT, XR_TYPE_EVENT_ದತ್ತಾಂಶ_PERF_SETTINGS_EXT) \
    _avail(Xr_Event_ದತ್ತಾಂಶ_Main_Session_Visibility_ಬದಲಾಯಿತು_EXTX, XR_TYPE_EVENT_ದತ್ತಾಂಶ_MAIN_SESSION_VISIBILITY_ಬದಲಾಯಿತು_EXTX) \
    _avail(Xr_Event_ದತ್ತಾಂಶ_Display_Refresh_ದರ_ಬದಲಾಯಿತು_FB, XR_TYPE_EVENT_ದತ್ತಾಂಶ_DISPLAY_REFRESH_ದರ_ಬದಲಾಯಿತು_FB) \
    _avail(Xr_Event_ದತ್ತಾಂಶ_Vive_Tracker_Connected_HTCX, XR_TYPE_EVENT_ದತ್ತಾಂಶ_VIVE_TRACKER_CONNECTED_HTCX) \
    _avail(Xr_Event_ದತ್ತಾಂಶ_Spatial_Anchor_Create_Complete_FB, XR_TYPE_EVENT_ದತ್ತಾಂಶ_SPATIAL_ANCHOR_CREATE_COMPLETE_FB) \
    _avail(Xr_Event_ದತ್ತಾಂಶ_Space_ಗಣ_ಸ್ಥಿತಿ_Complete_FB, XR_TYPE_EVENT_ದತ್ತಾಂಶ_SPACE_ಗಣ_ಸ್ಥಿತಿ_COMPLETE_FB) \
    _avail(Xr_Event_ದತ್ತಾಂಶ_Passthrough_State_ಬದಲಾಯಿತು_FB, XR_TYPE_EVENT_ದತ್ತಾಂಶ_PASSTHROUGH_STATE_ಬದಲಾಯಿತು_FB) \
    _avail(Xr_Event_ದತ್ತಾಂಶ_Marker_Tracking_Update_VARJO, XR_TYPE_EVENT_ದತ್ತಾಂಶ_MARKER_TRACKING_UPDATE_VARJO) \
    _avail(Xr_Event_ದತ್ತಾಂಶ_Localization_ಬದಲಾಯಿತು_ML, XR_TYPE_EVENT_ದತ್ತಾಂಶ_LOCALIZATION_ಬದಲಾಯಿತು_ML) \
    _avail(Xr_Event_ದತ್ತಾಂಶ_Space_Query_Results_ಲಭ್ಯ_FB, XR_TYPE_EVENT_ದತ್ತಾಂಶ_SPACE_QUERY_RESULTS_ಲಭ್ಯ_FB) \
    _avail(Xr_Event_ದತ್ತಾಂಶ_Space_Query_Complete_FB, XR_TYPE_EVENT_ದತ್ತಾಂಶ_SPACE_QUERY_COMPLETE_FB) \
    _avail(Xr_Event_ದತ್ತಾಂಶ_Space_Save_Complete_FB, XR_TYPE_EVENT_ದತ್ತಾಂಶ_SPACE_SAVE_COMPLETE_FB) \
    _avail(Xr_Event_ದತ್ತಾಂಶ_Space_Erase_Complete_FB, XR_TYPE_EVENT_ದತ್ತಾಂಶ_SPACE_ERASE_COMPLETE_FB) \
    _avail(Xr_Event_ದತ್ತಾಂಶ_Space_Share_Complete_FB, XR_TYPE_EVENT_ದತ್ತಾಂಶ_SPACE_SHARE_COMPLETE_FB) \
    _avail(Xr_Event_ದತ್ತಾಂಶ_Scene_Capture_Complete_FB, XR_TYPE_EVENT_ದತ್ತಾಂಶ_SCENE_CAPTURE_COMPLETE_FB) \
    _avail(Xr_Event_ದತ್ತಾಂಶ_Virtual_Keyboard_Commit_ಪಠ್ಯ_META, XR_TYPE_EVENT_ದತ್ತಾಂಶ_VIRTUAL_KEYBOARD_COMMIT_ಪಠ್ಯ_META) \
    _avail(Xr_Event_ದತ್ತಾಂಶ_Virtual_Keyboard_Backspace_META, XR_TYPE_EVENT_ದತ್ತಾಂಶ_VIRTUAL_KEYBOARD_BACKSPACE_META) \
    _avail(Xr_Event_ದತ್ತಾಂಶ_Virtual_Keyboard_Enter_META, XR_TYPE_EVENT_ದತ್ತಾಂಶ_VIRTUAL_KEYBOARD_ENTER_META) \
    _avail(Xr_Event_ದತ್ತಾಂಶ_Virtual_Keyboard_Shown_META, XR_TYPE_EVENT_ದತ್ತಾಂಶ_VIRTUAL_KEYBOARD_SHOWN_META) \
    _avail(Xr_Event_ದತ್ತಾಂಶ_Virtual_Keyboard_Hidden_META, XR_TYPE_EVENT_ದತ್ತಾಂಶ_VIRTUAL_KEYBOARD_HIDDEN_META) \
    _avail(Xr_Event_ದತ್ತಾಂಶ_Space_List_Save_Complete_FB, XR_TYPE_EVENT_ದತ್ತಾಂಶ_SPACE_LIST_SAVE_COMPLETE_FB) \
    _avail(Xr_Event_ದತ್ತಾಂಶ_Space_Discovery_Results_ಲಭ್ಯ_META, XR_TYPE_EVENT_ದತ್ತಾಂಶ_SPACE_DISCOVERY_RESULTS_ಲಭ್ಯ_META) \
    _avail(Xr_Event_ದತ್ತಾಂಶ_Space_Discovery_Complete_META, XR_TYPE_EVENT_ದತ್ತಾಂಶ_SPACE_DISCOVERY_COMPLETE_META) \
    _avail(Xr_Event_ದತ್ತಾಂಶ_Spaces_Save_ಫಲಿತಾಂಶ_META, XR_TYPE_EVENT_ದತ್ತಾಂಶ_SPACES_SAVE_ಫಲಿತಾಂಶ_META) \
    _avail(Xr_Event_ದತ್ತಾಂಶ_Spaces_Erase_ಫಲಿತಾಂಶ_META, XR_TYPE_EVENT_ದತ್ತಾಂಶ_SPACES_ERASE_ಫಲಿತಾಂಶ_META) \
    _avail(Xr_Event_ದತ್ತಾಂಶ_Passthrough_Layer_Resumed_META, XR_TYPE_EVENT_ದತ್ತಾಂಶ_PASSTHROUGH_LAYER_RESUMED_META) \
    _avail(Xr_Event_ದತ್ತಾಂಶ_Share_Spaces_Complete_META, XR_TYPE_EVENT_ದತ್ತಾಂಶ_SHARE_SPACES_COMPLETE_META) \
    _avail(Xr_Event_ದತ್ತಾಂಶ_Interaction_Render_Models_ಬದಲಾಯಿತು_EXT, XR_TYPE_EVENT_ದತ್ತಾಂಶ_INTERACTION_RENDER_MODELS_ಬದಲಾಯಿತು_EXT) \
    _avail(Xr_Event_ದತ್ತಾಂಶ_Sense_ದತ್ತಾಂಶ_Provider_State_ಬದಲಾಯಿತು_BD, XR_TYPE_EVENT_ದತ್ತಾಂಶ_SENSE_ದತ್ತಾಂಶ_PROVIDER_STATE_ಬದಲಾಯಿತು_BD) \
    _avail(Xr_Event_ದತ್ತಾಂಶ_Sense_ದತ್ತಾಂಶ_Updated_BD, XR_TYPE_EVENT_ದತ್ತಾಂಶ_SENSE_ದತ್ತಾಂಶ_UPDATED_BD) \
    _avail(Xr_Event_ದತ್ತಾಂಶ_Recommended_Resolution_ಬದಲಾಯಿತು_ANDROID, XR_TYPE_EVENT_ದತ್ತಾಂಶ_RECOMMENDED_RESOLUTION_ಬದಲಾಯಿತು_ANDROID) \
    _avail(Xr_Event_ದತ್ತಾಂಶ_User_Presence_ಬದಲಾಯಿತು_EXT, XR_TYPE_EVENT_ದತ್ತಾಂಶ_USER_PRESENCE_ಬದಲಾಯಿತು_EXT) \
    _avail(Xr_Event_ದತ್ತಾಂಶ_Headset_Fit_ಬದಲಾಯಿತು_ML, XR_TYPE_EVENT_ದತ್ತಾಂಶ_HEADSET_FIT_ಬದಲಾಯಿತು_ML) \
    _avail(Xr_Event_ದತ್ತಾಂಶ_Eye_Calibration_ಬದಲಾಯಿತು_ML, XR_TYPE_EVENT_ದತ್ತಾಂಶ_EYE_CALIBRATION_ಬದಲಾಯಿತು_ML) \
    _avail(Xr_Event_ದತ್ತಾಂಶ_Boundary_Visibility_ಬದಲಾಯಿತು_META, XR_TYPE_EVENT_ದತ್ತಾಂಶ_BOUNDARY_VISIBILITY_ಬದಲಾಯಿತು_META) \
    _avail(Xr_Event_ದತ್ತಾಂಶ_ಆರಂಭ_Colocation_Advertisement_Complete_META, XR_TYPE_EVENT_ದತ್ತಾಂಶ_ಆರಂಭ_COLOCATION_ADVERTISEMENT_COMPLETE_META) \
    _avail(Xr_Event_ದತ್ತಾಂಶ_Stop_Colocation_Advertisement_Complete_META, XR_TYPE_EVENT_ದತ್ತಾಂಶ_STOP_COLOCATION_ADVERTISEMENT_COMPLETE_META) \
    _avail(Xr_Event_ದತ್ತಾಂಶ_Colocation_Advertisement_Complete_META, XR_TYPE_EVENT_ದತ್ತಾಂಶ_COLOCATION_ADVERTISEMENT_COMPLETE_META) \
    _avail(Xr_Event_ದತ್ತಾಂಶ_ಆರಂಭ_Colocation_Discovery_Complete_META, XR_TYPE_EVENT_ದತ್ತಾಂಶ_ಆರಂಭ_COLOCATION_DISCOVERY_COMPLETE_META) \
    _avail(Xr_Event_ದತ್ತಾಂಶ_Colocation_Discovery_ಫಲಿತಾಂಶ_META, XR_TYPE_EVENT_ದತ್ತಾಂಶ_COLOCATION_DISCOVERY_ಫಲಿತಾಂಶ_META) \
    _avail(Xr_Event_ದತ್ತಾಂಶ_Colocation_Discovery_Complete_META, XR_TYPE_EVENT_ದತ್ತಾಂಶ_COLOCATION_DISCOVERY_COMPLETE_META) \
    _avail(Xr_Event_ದತ್ತಾಂಶ_Stop_Colocation_Discovery_Complete_META, XR_TYPE_EVENT_ದತ್ತಾಂಶ_STOP_COLOCATION_DISCOVERY_COMPLETE_META) \
    _avail(Xr_Event_ದತ್ತಾಂಶ_Image_Tracking_ಕಳೆದುಹೋದ_ANDROID, XR_TYPE_EVENT_ದತ್ತಾಂಶ_IMAGE_TRACKING_ಕಳೆದುಹೋದ_ANDROID) \
    _avail(Xr_Event_ದತ್ತಾಂಶ_Spatial_Discovery_Recommended_EXT, XR_TYPE_EVENT_ದತ್ತಾಂಶ_SPATIAL_DISCOVERY_RECOMMENDED_EXT) \
    _avail(Xr_Event_ದತ್ತಾಂಶ_Geospatial_Tracker_State_ಬದಲಾಯಿತು_ANDROID, XR_TYPE_EVENT_ದತ್ತಾಂಶ_GEOSPATIAL_TRACKER_STATE_ಬದಲಾಯಿತು_ANDROID) \
    _avail(Xr_Event_ದತ್ತಾಂಶ_Spatial_Container_Closed_EXT, XR_TYPE_EVENT_ದತ್ತಾಂಶ_SPATIAL_CONTAINER_CLOSED_EXT) \
    _avail(Xr_Event_ದತ್ತಾಂಶ_Spatial_Container_Bounds_ಬದಲಾಯಿತು_EXT, XR_TYPE_EVENT_ದತ್ತಾಂಶ_SPATIAL_CONTAINER_BOUNDS_ಬದಲಾಯಿತು_EXT) \
    _avail(Xr_Event_ದತ್ತಾಂಶ_Spatial_Container_Visible_ಬದಲಾಯಿತು_EXT, XR_TYPE_EVENT_ದತ್ತಾಂಶ_SPATIAL_CONTAINER_VISIBLE_ಬದಲಾಯಿತು_EXT) \
    _avail(Xr_Event_ದತ್ತಾಂಶ_Spatial_Container_Visible_Request_Denied_EXT, XR_TYPE_EVENT_ದತ್ತಾಂಶ_SPATIAL_CONTAINER_VISIBLE_REQUEST_DENIED_EXT) \
    _avail(Xr_Event_ದತ್ತಾಂಶ_Spatial_Container_Interactable_ಬದಲಾಯಿತು_EXT, XR_TYPE_EVENT_ದತ್ತಾಂಶ_SPATIAL_CONTAINER_INTERACTABLE_ಬದಲಾಯಿತು_EXT) \
    _avail(Xr_Event_ದತ್ತಾಂಶ_Spatial_Container_Bounds_ಬಹುಲಕ_Request_Denied_EXT, XR_TYPE_EVENT_ದತ್ತಾಂಶ_SPATIAL_CONTAINER_BOUNDS_ಬಹುಲಕ_REQUEST_DENIED_EXT) \
    _avail(Xr_Event_ದತ್ತಾಂಶ_View_Configuration_Views_ಬದಲಾಯಿತು_EXT, XR_TYPE_EVENT_ದತ್ತಾಂಶ_VIEW_CONFIGURATION_VIEWS_ಬದಲಾಯಿತು_EXT) \





/// Like XR_LIST_ALL_STRUCTURE_TYPES, but only includes types whose parent struct type is XrHapticBaseHeader
#ವ್ಯಾಖ್ಯಾನಿಸು XR_LIST_ALL_ಮಗು_STRUCTURE_TYPES_Xr_Haptic_ತಳ_ಶೀರ್ಷಿಕೆ(_avail, _unavail) \
    impl_XR_LIST_ALL_ಮಗು_STRUCTURE_TYPES_Xr_Haptic_ತಳ_ಶೀರ್ಷಿಕೆ_CORE(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrHapticBaseHeader()
#ವ್ಯಾಖ್ಯಾನಿಸು impl_XR_LIST_ALL_ಮಗು_STRUCTURE_TYPES_Xr_Haptic_ತಳ_ಶೀರ್ಷಿಕೆ_CORE(_avail, _unavail) \
    _avail(XrHapticVibration, XR_TYPE_HAPTIC_VIBRATION) \
    _avail(XrHapticAmplitudeEnvelopeVibrationFB, XR_TYPE_HAPTIC_AMPLITUDE_ENVELOPE_VIBRATION_FB) \
    _avail(XrHapticPcmVibrationFB, XR_TYPE_HAPTIC_PCM_VIBRATION_FB) \
    _avail(XrHapticParametricVibrationEXT, XR_TYPE_HAPTIC_PARAMETRIC_VIBRATION_EXT) \





/// Like XR_LIST_ALL_STRUCTURE_TYPES, but only includes types whose parent struct type is XrSwapchainImageBaseHeader
#ವ್ಯಾಖ್ಯಾನಿಸು XR_LIST_ALL_ಮಗು_STRUCTURE_TYPES_Xr_Swapchain_Image_ತಳ_ಶೀರ್ಷಿಕೆ(_avail, _unavail) \
    impl_XR_LIST_ALL_ಮಗು_STRUCTURE_TYPES_Xr_Swapchain_Image_ತಳ_ಶೀರ್ಷಿಕೆ_CORE(_avail, _unavail) \
    impl_XR_LIST_ALL_ಮಗು_STRUCTURE_TYPES_Xr_Swapchain_Image_ತಳ_ಶೀರ್ಷಿಕೆ_XR_USE_GRAPHICS_API_D3_D11(_avail, _unavail) \
    impl_XR_LIST_ALL_ಮಗು_STRUCTURE_TYPES_Xr_Swapchain_Image_ತಳ_ಶೀರ್ಷಿಕೆ_XR_USE_GRAPHICS_API_D3_D12(_avail, _unavail) \
    impl_XR_LIST_ALL_ಮಗು_STRUCTURE_TYPES_Xr_Swapchain_Image_ತಳ_ಶೀರ್ಷಿಕೆ_XR_USE_GRAPHICS_API_METAL(_avail, _unavail) \
    impl_XR_LIST_ALL_ಮಗು_STRUCTURE_TYPES_Xr_Swapchain_Image_ತಳ_ಶೀರ್ಷಿಕೆ_XR_USE_GRAPHICS_API_OPENGL(_avail, _unavail) \
    impl_XR_LIST_ALL_ಮಗು_STRUCTURE_TYPES_Xr_Swapchain_Image_ತಳ_ಶೀರ್ಷಿಕೆ_XR_USE_GRAPHICS_API_OPENGL_ES(_avail, _unavail) \
    impl_XR_LIST_ALL_ಮಗು_STRUCTURE_TYPES_Xr_Swapchain_Image_ತಳ_ಶೀರ್ಷಿಕೆ_XR_USE_GRAPHICS_API_VULKAN(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrSwapchainImageBaseHeader()
#ವ್ಯಾಖ್ಯಾನಿಸು impl_XR_LIST_ALL_ಮಗು_STRUCTURE_TYPES_Xr_Swapchain_Image_ತಳ_ಶೀರ್ಷಿಕೆ_CORE(_avail, _unavail) \


#ಆದರೆ defined(XR_USE_GRAPHICS_API_D3D11)
#ವ್ಯಾಖ್ಯಾನಿಸು impl_XR_LIST_ALL_ಮಗು_STRUCTURE_TYPES_Xr_Swapchain_Image_ತಳ_ಶೀರ್ಷಿಕೆ_XR_USE_GRAPHICS_API_D3_D11(_avail, _unavail) \
    _avail(XrSwapchainImageD3D11KHR, XR_TYPE_SWAPCHAIN_IMAGE_D3D11_KHR) \

#ಇಲ್ಲದಿದ್ದರೆ
#ವ್ಯಾಖ್ಯಾನಿಸು impl_XR_LIST_ALL_ಮಗು_STRUCTURE_TYPES_Xr_Swapchain_Image_ತಳ_ಶೀರ್ಷಿಕೆ_XR_USE_GRAPHICS_API_D3_D11(_avail, _unavail) \
    _unavail(XrSwapchainImageD3D11KHR, XR_TYPE_SWAPCHAIN_IMAGE_D3D11_KHR) \

#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ defined(XR_USE_GRAPHICS_API_D3D12)
#ವ್ಯಾಖ್ಯಾನಿಸು impl_XR_LIST_ALL_ಮಗು_STRUCTURE_TYPES_Xr_Swapchain_Image_ತಳ_ಶೀರ್ಷಿಕೆ_XR_USE_GRAPHICS_API_D3_D12(_avail, _unavail) \
    _avail(XrSwapchainImageD3D12KHR, XR_TYPE_SWAPCHAIN_IMAGE_D3D12_KHR) \

#ಇಲ್ಲದಿದ್ದರೆ
#ವ್ಯಾಖ್ಯಾನಿಸು impl_XR_LIST_ALL_ಮಗು_STRUCTURE_TYPES_Xr_Swapchain_Image_ತಳ_ಶೀರ್ಷಿಕೆ_XR_USE_GRAPHICS_API_D3_D12(_avail, _unavail) \
    _unavail(XrSwapchainImageD3D12KHR, XR_TYPE_SWAPCHAIN_IMAGE_D3D12_KHR) \

#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ defined(XR_USE_GRAPHICS_API_METAL)
#ವ್ಯಾಖ್ಯಾನಿಸು impl_XR_LIST_ALL_ಮಗು_STRUCTURE_TYPES_Xr_Swapchain_Image_ತಳ_ಶೀರ್ಷಿಕೆ_XR_USE_GRAPHICS_API_METAL(_avail, _unavail) \
    _avail(XrSwapchainImageMetalKHR, XR_TYPE_SWAPCHAIN_IMAGE_METAL_KHR) \

#ಇಲ್ಲದಿದ್ದರೆ
#ವ್ಯಾಖ್ಯಾನಿಸು impl_XR_LIST_ALL_ಮಗು_STRUCTURE_TYPES_Xr_Swapchain_Image_ತಳ_ಶೀರ್ಷಿಕೆ_XR_USE_GRAPHICS_API_METAL(_avail, _unavail) \
    _unavail(XrSwapchainImageMetalKHR, XR_TYPE_SWAPCHAIN_IMAGE_METAL_KHR) \

#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ defined(XR_USE_GRAPHICS_API_OPENGL)
#ವ್ಯಾಖ್ಯಾನಿಸು impl_XR_LIST_ALL_ಮಗು_STRUCTURE_TYPES_Xr_Swapchain_Image_ತಳ_ಶೀರ್ಷಿಕೆ_XR_USE_GRAPHICS_API_OPENGL(_avail, _unavail) \
    _avail(XrSwapchainImageOpenGLKHR, XR_TYPE_SWAPCHAIN_IMAGE_OPENGL_KHR) \

#ಇಲ್ಲದಿದ್ದರೆ
#ವ್ಯಾಖ್ಯಾನಿಸು impl_XR_LIST_ALL_ಮಗು_STRUCTURE_TYPES_Xr_Swapchain_Image_ತಳ_ಶೀರ್ಷಿಕೆ_XR_USE_GRAPHICS_API_OPENGL(_avail, _unavail) \
    _unavail(XrSwapchainImageOpenGLKHR, XR_TYPE_SWAPCHAIN_IMAGE_OPENGL_KHR) \

#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ defined(XR_USE_GRAPHICS_API_OPENGL_ES)
#ವ್ಯಾಖ್ಯಾನಿಸು impl_XR_LIST_ALL_ಮಗು_STRUCTURE_TYPES_Xr_Swapchain_Image_ತಳ_ಶೀರ್ಷಿಕೆ_XR_USE_GRAPHICS_API_OPENGL_ES(_avail, _unavail) \
    _avail(XrSwapchainImageOpenGLESKHR, XR_TYPE_SWAPCHAIN_IMAGE_OPENGL_ES_KHR) \

#ಇಲ್ಲದಿದ್ದರೆ
#ವ್ಯಾಖ್ಯಾನಿಸು impl_XR_LIST_ALL_ಮಗು_STRUCTURE_TYPES_Xr_Swapchain_Image_ತಳ_ಶೀರ್ಷಿಕೆ_XR_USE_GRAPHICS_API_OPENGL_ES(_avail, _unavail) \
    _unavail(XrSwapchainImageOpenGLESKHR, XR_TYPE_SWAPCHAIN_IMAGE_OPENGL_ES_KHR) \

#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ defined(XR_USE_GRAPHICS_API_VULKAN)
#ವ್ಯಾಖ್ಯಾನಿಸು impl_XR_LIST_ALL_ಮಗು_STRUCTURE_TYPES_Xr_Swapchain_Image_ತಳ_ಶೀರ್ಷಿಕೆ_XR_USE_GRAPHICS_API_VULKAN(_avail, _unavail) \
    _avail(XrSwapchainImageVulkanKHR, XR_TYPE_SWAPCHAIN_IMAGE_VULKAN_KHR) \

#ಇಲ್ಲದಿದ್ದರೆ
#ವ್ಯಾಖ್ಯಾನಿಸು impl_XR_LIST_ALL_ಮಗು_STRUCTURE_TYPES_Xr_Swapchain_Image_ತಳ_ಶೀರ್ಷಿಕೆ_XR_USE_GRAPHICS_API_VULKAN(_avail, _unavail) \
    _unavail(XrSwapchainImageVulkanKHR, XR_TYPE_SWAPCHAIN_IMAGE_VULKAN_KHR) \

#ಆದರೆ_ಅಂತ್ಯ




/// Like XR_LIST_ALL_STRUCTURE_TYPES, but only includes types whose parent struct type is XrLoaderInitInfoBaseHeaderKHR
#ವ್ಯಾಖ್ಯಾನಿಸು XR_LIST_ALL_ಮಗು_STRUCTURE_TYPES_Xr_Loader_Init_Info_ತಳ_ಶೀರ್ಷಿಕೆ_KHR(_avail, _unavail) \
    impl_XR_LIST_ALL_ಮಗು_STRUCTURE_TYPES_Xr_Loader_Init_Info_ತಳ_ಶೀರ್ಷಿಕೆ_KHR_CORE(_avail, _unavail) \
    impl_XR_LIST_ALL_ಮಗು_STRUCTURE_TYPES_Xr_Loader_Init_Info_ತಳ_ಶೀರ್ಷಿಕೆ_KHR_XR_USE_PLATFORM_ANDROID(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrLoaderInitInfoBaseHeaderKHR()
#ವ್ಯಾಖ್ಯಾನಿಸು impl_XR_LIST_ALL_ಮಗು_STRUCTURE_TYPES_Xr_Loader_Init_Info_ತಳ_ಶೀರ್ಷಿಕೆ_KHR_CORE(_avail, _unavail) \
    _avail(XrLoaderInitInfoPropertiesEXT, XR_TYPE_LOADER_INIT_INFO_PROPERTIES_EXT) \


#ಆದರೆ defined(XR_USE_PLATFORM_ANDROID)
#ವ್ಯಾಖ್ಯಾನಿಸು impl_XR_LIST_ALL_ಮಗು_STRUCTURE_TYPES_Xr_Loader_Init_Info_ತಳ_ಶೀರ್ಷಿಕೆ_KHR_XR_USE_PLATFORM_ANDROID(_avail, _unavail) \
    _avail(XrLoaderInitInfoAndroidKHR, XR_TYPE_LOADER_INIT_INFO_ANDROID_KHR) \

#ಇಲ್ಲದಿದ್ದರೆ
#ವ್ಯಾಖ್ಯಾನಿಸು impl_XR_LIST_ALL_ಮಗು_STRUCTURE_TYPES_Xr_Loader_Init_Info_ತಳ_ಶೀರ್ಷಿಕೆ_KHR_XR_USE_PLATFORM_ANDROID(_avail, _unavail) \
    _unavail(XrLoaderInitInfoAndroidKHR, XR_TYPE_LOADER_INIT_INFO_ANDROID_KHR) \

#ಆದರೆ_ಅಂತ್ಯ




/// Like XR_LIST_ALL_STRUCTURE_TYPES, but only includes types whose parent struct type is XrBindingModificationBaseHeaderKHR
#ವ್ಯಾಖ್ಯಾನಿಸು XR_LIST_ALL_ಮಗು_STRUCTURE_TYPES_Xr_Binding_Modification_ತಳ_ಶೀರ್ಷಿಕೆ_KHR(_avail, _unavail) \
    impl_XR_LIST_ALL_ಮಗು_STRUCTURE_TYPES_Xr_Binding_Modification_ತಳ_ಶೀರ್ಷಿಕೆ_KHR_CORE(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrBindingModificationBaseHeaderKHR()
#ವ್ಯಾಖ್ಯಾನಿಸು impl_XR_LIST_ALL_ಮಗು_STRUCTURE_TYPES_Xr_Binding_Modification_ತಳ_ಶೀರ್ಷಿಕೆ_KHR_CORE(_avail, _unavail) \
    _avail(XrInteractionProfileDpadBindingEXT, XR_TYPE_INTERACTION_PROFILE_DPAD_BINDING_EXT) \
    _avail(Xr_Interaction_Profile_Analog_ಮಿತಿ_VALVE, XR_TYPE_INTERACTION_PROFILE_ANALOG_ಮಿತಿ_VALVE) \





/// Like XR_LIST_ALL_STRUCTURE_TYPES, but only includes types whose parent struct type is XrSwapchainStateBaseHeaderFB
#ವ್ಯಾಖ್ಯಾನಿಸು XR_LIST_ALL_ಮಗು_STRUCTURE_TYPES_Xr_Swapchain_State_ತಳ_ಶೀರ್ಷಿಕೆ_FB(_avail, _unavail) \
    impl_XR_LIST_ALL_ಮಗು_STRUCTURE_TYPES_Xr_Swapchain_State_ತಳ_ಶೀರ್ಷಿಕೆ_FB_CORE(_avail, _unavail) \
    impl_XR_LIST_ALL_ಮಗು_STRUCTURE_TYPES_Xr_Swapchain_State_ತಳ_ಶೀರ್ಷಿಕೆ_FB_XR_USE_GRAPHICS_API_OPENGL_ES(_avail, _unavail) \
    impl_XR_LIST_ALL_ಮಗು_STRUCTURE_TYPES_Xr_Swapchain_State_ತಳ_ಶೀರ್ಷಿಕೆ_FB_XR_USE_GRAPHICS_API_VULKAN(_avail, _unavail) \
    impl_XR_LIST_ALL_ಮಗು_STRUCTURE_TYPES_Xr_Swapchain_State_ತಳ_ಶೀರ್ಷಿಕೆ_FB_XR_USE_PLATFORM_ANDROID(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrSwapchainStateBaseHeaderFB()
#ವ್ಯಾಖ್ಯಾನಿಸು impl_XR_LIST_ALL_ಮಗು_STRUCTURE_TYPES_Xr_Swapchain_State_ತಳ_ಶೀರ್ಷಿಕೆ_FB_CORE(_avail, _unavail) \
    _avail(XrSwapchainStateFoveationFB, XR_TYPE_SWAPCHAIN_STATE_FOVEATION_FB) \


#ಆದರೆ defined(XR_USE_GRAPHICS_API_OPENGL_ES)
#ವ್ಯಾಖ್ಯಾನಿಸು impl_XR_LIST_ALL_ಮಗು_STRUCTURE_TYPES_Xr_Swapchain_State_ತಳ_ಶೀರ್ಷಿಕೆ_FB_XR_USE_GRAPHICS_API_OPENGL_ES(_avail, _unavail) \
    _avail(XrSwapchainStateSamplerOpenGLESFB, XR_TYPE_SWAPCHAIN_STATE_SAMPLER_OPENGL_ES_FB) \

#ಇಲ್ಲದಿದ್ದರೆ
#ವ್ಯಾಖ್ಯಾನಿಸು impl_XR_LIST_ALL_ಮಗು_STRUCTURE_TYPES_Xr_Swapchain_State_ತಳ_ಶೀರ್ಷಿಕೆ_FB_XR_USE_GRAPHICS_API_OPENGL_ES(_avail, _unavail) \
    _unavail(XrSwapchainStateSamplerOpenGLESFB, XR_TYPE_SWAPCHAIN_STATE_SAMPLER_OPENGL_ES_FB) \

#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ defined(XR_USE_GRAPHICS_API_VULKAN)
#ವ್ಯಾಖ್ಯಾನಿಸು impl_XR_LIST_ALL_ಮಗು_STRUCTURE_TYPES_Xr_Swapchain_State_ತಳ_ಶೀರ್ಷಿಕೆ_FB_XR_USE_GRAPHICS_API_VULKAN(_avail, _unavail) \
    _avail(XrSwapchainStateSamplerVulkanFB, XR_TYPE_SWAPCHAIN_STATE_SAMPLER_VULKAN_FB) \

#ಇಲ್ಲದಿದ್ದರೆ
#ವ್ಯಾಖ್ಯಾನಿಸು impl_XR_LIST_ALL_ಮಗು_STRUCTURE_TYPES_Xr_Swapchain_State_ತಳ_ಶೀರ್ಷಿಕೆ_FB_XR_USE_GRAPHICS_API_VULKAN(_avail, _unavail) \
    _unavail(XrSwapchainStateSamplerVulkanFB, XR_TYPE_SWAPCHAIN_STATE_SAMPLER_VULKAN_FB) \

#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ defined(XR_USE_PLATFORM_ANDROID)
#ವ್ಯಾಖ್ಯಾನಿಸು impl_XR_LIST_ALL_ಮಗು_STRUCTURE_TYPES_Xr_Swapchain_State_ತಳ_ಶೀರ್ಷಿಕೆ_FB_XR_USE_PLATFORM_ANDROID(_avail, _unavail) \
    _avail(XrSwapchainStateAndroidSurfaceDimensionsFB, XR_TYPE_SWAPCHAIN_STATE_ANDROID_SURFACE_DIMENSIONS_FB) \

#ಇಲ್ಲದಿದ್ದರೆ
#ವ್ಯಾಖ್ಯಾನಿಸು impl_XR_LIST_ALL_ಮಗು_STRUCTURE_TYPES_Xr_Swapchain_State_ತಳ_ಶೀರ್ಷಿಕೆ_FB_XR_USE_PLATFORM_ANDROID(_avail, _unavail) \
    _unavail(XrSwapchainStateAndroidSurfaceDimensionsFB, XR_TYPE_SWAPCHAIN_STATE_ANDROID_SURFACE_DIMENSIONS_FB) \

#ಆದರೆ_ಅಂತ್ಯ




/// Like XR_LIST_ALL_STRUCTURE_TYPES, but only includes types whose parent struct type is XrSpatialAnchorsCreateInfoBaseHeaderML
#ವ್ಯಾಖ್ಯಾನಿಸು XR_LIST_ALL_ಮಗು_STRUCTURE_TYPES_Xr_Spatial_Anchors_Create_Info_ತಳ_ಶೀರ್ಷಿಕೆ_ML(_avail, _unavail) \
    impl_XR_LIST_ALL_ಮಗು_STRUCTURE_TYPES_Xr_Spatial_Anchors_Create_Info_ತಳ_ಶೀರ್ಷಿಕೆ_ML_CORE(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrSpatialAnchorsCreateInfoBaseHeaderML()
#ವ್ಯಾಖ್ಯಾನಿಸು impl_XR_LIST_ALL_ಮಗು_STRUCTURE_TYPES_Xr_Spatial_Anchors_Create_Info_ತಳ_ಶೀರ್ಷಿಕೆ_ML_CORE(_avail, _unavail) \
    _avail(XrSpatialAnchorsCreateInfoFromPoseML, XR_TYPE_SPATIAL_ANCHORS_CREATE_INFO_FROM_POSE_ML) \
    _avail(XrSpatialAnchorsCreateInfoFromUuidsML, XR_TYPE_SPATIAL_ANCHORS_CREATE_INFO_FROM_UUIDS_ML) \





/// Like XR_LIST_ALL_STRUCTURE_TYPES, but only includes types whose parent struct type is XrFutureCompletionBaseHeaderEXT
#ವ್ಯಾಖ್ಯಾನಿಸು XR_LIST_ALL_ಮಗು_STRUCTURE_TYPES_Xr_Future_Completion_ತಳ_ಶೀರ್ಷಿಕೆ_EXT(_avail, _unavail) \
    impl_XR_LIST_ALL_ಮಗು_STRUCTURE_TYPES_Xr_Future_Completion_ತಳ_ಶೀರ್ಷಿಕೆ_EXT_CORE(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrFutureCompletionBaseHeaderEXT()
#ವ್ಯಾಖ್ಯಾನಿಸು impl_XR_LIST_ALL_ಮಗು_STRUCTURE_TYPES_Xr_Future_Completion_ತಳ_ಶೀರ್ಷಿಕೆ_EXT_CORE(_avail, _unavail) \
    _avail(XrCreateSpatialAnchorsCompletionML, XR_TYPE_CREATE_SPATIAL_ANCHORS_COMPLETION_ML) \
    _avail(XrSpatialAnchorsQueryCompletionML, XR_TYPE_SPATIAL_ANCHORS_QUERY_COMPLETION_ML) \
    _avail(XrSpatialAnchorsPublishCompletionML, XR_TYPE_SPATIAL_ANCHORS_PUBLISH_COMPLETION_ML) \
    _avail(XrSpatialAnchorsDeleteCompletionML, XR_TYPE_SPATIAL_ANCHORS_DELETE_COMPLETION_ML) \
    _avail(XrSpatialAnchorsUpdateExpirationCompletionML, XR_TYPE_SPATIAL_ANCHORS_UPDATE_EXPIRATION_COMPLETION_ML) \
    _avail(Xr_Sense_ದತ್ತಾಂಶ_Query_Completion_BD, XR_TYPE_SENSE_ದತ್ತಾಂಶ_QUERY_COMPLETION_BD) \
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
#ವ್ಯಾಖ್ಯಾನಿಸು XR_LIST_ALL_ಮಗು_STRUCTURE_TYPES_Xr_Spatial_Anchors_Query_Info_ತಳ_ಶೀರ್ಷಿಕೆ_ML(_avail, _unavail) \
    impl_XR_LIST_ALL_ಮಗು_STRUCTURE_TYPES_Xr_Spatial_Anchors_Query_Info_ತಳ_ಶೀರ್ಷಿಕೆ_ML_CORE(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrSpatialAnchorsQueryInfoBaseHeaderML()
#ವ್ಯಾಖ್ಯಾನಿಸು impl_XR_LIST_ALL_ಮಗು_STRUCTURE_TYPES_Xr_Spatial_Anchors_Query_Info_ತಳ_ಶೀರ್ಷಿಕೆ_ML_CORE(_avail, _unavail) \
    _avail(XrSpatialAnchorsQueryInfoRadiusML, XR_TYPE_SPATIAL_ANCHORS_QUERY_INFO_RADIUS_ML) \





/// Like XR_LIST_ALL_STRUCTURE_TYPES, but only includes types whose parent struct type is XrSpaceQueryInfoBaseHeaderFB
#ವ್ಯಾಖ್ಯಾನಿಸು XR_LIST_ALL_ಮಗು_STRUCTURE_TYPES_Xr_Space_Query_Info_ತಳ_ಶೀರ್ಷಿಕೆ_FB(_avail, _unavail) \
    impl_XR_LIST_ALL_ಮಗು_STRUCTURE_TYPES_Xr_Space_Query_Info_ತಳ_ಶೀರ್ಷಿಕೆ_FB_CORE(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrSpaceQueryInfoBaseHeaderFB()
#ವ್ಯಾಖ್ಯಾನಿಸು impl_XR_LIST_ALL_ಮಗು_STRUCTURE_TYPES_Xr_Space_Query_Info_ತಳ_ಶೀರ್ಷಿಕೆ_FB_CORE(_avail, _unavail) \
    _avail(XrSpaceQueryInfoFB, XR_TYPE_SPACE_QUERY_INFO_FB) \





/// Like XR_LIST_ALL_STRUCTURE_TYPES, but only includes types whose parent struct type is XrSpaceFilterInfoBaseHeaderFB
#ವ್ಯಾಖ್ಯಾನಿಸು XR_LIST_ALL_ಮಗು_STRUCTURE_TYPES_Xr_Space_Filter_Info_ತಳ_ಶೀರ್ಷಿಕೆ_FB(_avail, _unavail) \
    impl_XR_LIST_ALL_ಮಗು_STRUCTURE_TYPES_Xr_Space_Filter_Info_ತಳ_ಶೀರ್ಷಿಕೆ_FB_CORE(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrSpaceFilterInfoBaseHeaderFB()
#ವ್ಯಾಖ್ಯಾನಿಸು impl_XR_LIST_ALL_ಮಗು_STRUCTURE_TYPES_Xr_Space_Filter_Info_ತಳ_ಶೀರ್ಷಿಕೆ_FB_CORE(_avail, _unavail) \
    _avail(XrSpaceUuidFilterInfoFB, XR_TYPE_SPACE_UUID_FILTER_INFO_FB) \
    _avail(XrSpaceComponentFilterInfoFB, XR_TYPE_SPACE_COMPONENT_FILTER_INFO_FB) \





/// Like XR_LIST_ALL_STRUCTURE_TYPES, but only includes types whose parent struct type is XrSpaceFilterBaseHeaderMETA
#ವ್ಯಾಖ್ಯಾನಿಸು XR_LIST_ALL_ಮಗು_STRUCTURE_TYPES_Xr_Space_Filter_ತಳ_ಶೀರ್ಷಿಕೆ_META(_avail, _unavail) \
    impl_XR_LIST_ALL_ಮಗು_STRUCTURE_TYPES_Xr_Space_Filter_ತಳ_ಶೀರ್ಷಿಕೆ_META_CORE(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrSpaceFilterBaseHeaderMETA()
#ವ್ಯಾಖ್ಯಾನಿಸು impl_XR_LIST_ALL_ಮಗು_STRUCTURE_TYPES_Xr_Space_Filter_ತಳ_ಶೀರ್ಷಿಕೆ_META_CORE(_avail, _unavail) \
    _avail(XrSpaceFilterUuidMETA, XR_TYPE_SPACE_FILTER_UUID_META) \
    _avail(XrSpaceFilterComponentMETA, XR_TYPE_SPACE_FILTER_COMPONENT_META) \





/// Like XR_LIST_ALL_STRUCTURE_TYPES, but only includes types whose parent struct type is XrShareSpacesRecipientBaseHeaderMETA
#ವ್ಯಾಖ್ಯಾನಿಸು XR_LIST_ALL_ಮಗು_STRUCTURE_TYPES_Xr_Share_Spaces_Recipient_ತಳ_ಶೀರ್ಷಿಕೆ_META(_avail, _unavail) \
    impl_XR_LIST_ALL_ಮಗು_STRUCTURE_TYPES_Xr_Share_Spaces_Recipient_ತಳ_ಶೀರ್ಷಿಕೆ_META_CORE(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrShareSpacesRecipientBaseHeaderMETA()
#ವ್ಯಾಖ್ಯಾನಿಸು impl_XR_LIST_ALL_ಮಗು_STRUCTURE_TYPES_Xr_Share_Spaces_Recipient_ತಳ_ಶೀರ್ಷಿಕೆ_META_CORE(_avail, _unavail) \
    _avail(XrShareSpacesRecipientGroupsMETA, XR_TYPE_SHARE_SPACES_RECIPIENT_GROUPS_META) \





/// Like XR_LIST_ALL_STRUCTURE_TYPES, but only includes types whose parent struct type is XrEnvironmentRaycastFilterBaseHeaderMETA
#ವ್ಯಾಖ್ಯಾನಿಸು XR_LIST_ALL_ಮಗು_STRUCTURE_TYPES_Xr_Environment_Raycast_Filter_ತಳ_ಶೀರ್ಷಿಕೆ_META(_avail, _unavail) \
    impl_XR_LIST_ALL_ಮಗು_STRUCTURE_TYPES_Xr_Environment_Raycast_Filter_ತಳ_ಶೀರ್ಷಿಕೆ_META_CORE(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrEnvironmentRaycastFilterBaseHeaderMETA()
#ವ್ಯಾಖ್ಯಾನಿಸು impl_XR_LIST_ALL_ಮಗು_STRUCTURE_TYPES_Xr_Environment_Raycast_Filter_ತಳ_ಶೀರ್ಷಿಕೆ_META_CORE(_avail, _unavail) \
    _avail(Xr_Environment_Raycast_Filter_ದೂರ_META, XR_TYPE_ENVIRONMENT_RAYCAST_FILTER_ದೂರ_META) \





/// Like XR_LIST_ALL_STRUCTURE_TYPES, but only includes types whose parent struct type is XrSpatialCapabilityConfigurationBaseHeaderEXT
#ವ್ಯಾಖ್ಯಾನಿಸು XR_LIST_ALL_ಮಗು_STRUCTURE_TYPES_Xr_Spatial_Capability_Configuration_ತಳ_ಶೀರ್ಷಿಕೆ_EXT(_avail, _unavail) \
    impl_XR_LIST_ALL_ಮಗು_STRUCTURE_TYPES_Xr_Spatial_Capability_Configuration_ತಳ_ಶೀರ್ಷಿಕೆ_EXT_CORE(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrSpatialCapabilityConfigurationBaseHeaderEXT()
#ವ್ಯಾಖ್ಯಾನಿಸು impl_XR_LIST_ALL_ಮಗು_STRUCTURE_TYPES_Xr_Spatial_Capability_Configuration_ತಳ_ಶೀರ್ಷಿಕೆ_EXT_CORE(_avail, _unavail) \
    _avail(XrSpatialCapabilityConfigurationPlaneTrackingEXT, XR_TYPE_SPATIAL_CAPABILITY_CONFIGURATION_PLANE_TRACKING_EXT) \
    _avail(Xr_Spatial_Capability_Configuration_Qr_ಸಂಕೇತ_EXT, XR_TYPE_SPATIAL_CAPABILITY_CONFIGURATION_QR_ಸಂಕೇತ_EXT) \
    _avail(Xr_Spatial_Capability_Configuration_Micro_Qr_ಸಂಕೇತ_EXT, XR_TYPE_SPATIAL_CAPABILITY_CONFIGURATION_MICRO_QR_ಸಂಕೇತ_EXT) \
    _avail(XrSpatialCapabilityConfigurationArucoMarkerEXT, XR_TYPE_SPATIAL_CAPABILITY_CONFIGURATION_ARUCO_MARKER_EXT) \
    _avail(Xr_Spatial_Capability_Configuration_April_ಟ್ಯಾಗ್_EXT, XR_TYPE_SPATIAL_CAPABILITY_CONFIGURATION_APRIL_ಟ್ಯಾಗ್_EXT) \
    _avail(XrSpatialCapabilityConfigurationObjectTrackingEXT, XR_TYPE_SPATIAL_CAPABILITY_CONFIGURATION_OBJECT_TRACKING_EXT) \
    _avail(XrSpatialCapabilityConfigurationAnchorEXT, XR_TYPE_SPATIAL_CAPABILITY_CONFIGURATION_ANCHOR_EXT) \
    _avail(XrSpatialCapabilityConfigurationImageTrackingEXT, XR_TYPE_SPATIAL_CAPABILITY_CONFIGURATION_IMAGE_TRACKING_EXT) \
    _avail(XrSpatialCapabilityConfigurationMeshTrackingEXT, XR_TYPE_SPATIAL_CAPABILITY_CONFIGURATION_MESH_TRACKING_EXT) \
    _avail(XrSpatialCapabilityConfigurationObjectTrackingANDROID, XR_TYPE_SPATIAL_CAPABILITY_CONFIGURATION_OBJECT_TRACKING_ANDROID) \
    _avail(Xr_Spatial_Capability_Configuration_ಆಳ_Raycast_ANDROID, XR_TYPE_SPATIAL_CAPABILITY_CONFIGURATION_ಆಳ_RAYCAST_ANDROID) \





/// Like XR_LIST_ALL_STRUCTURE_TYPES, but only includes types whose parent struct type is XrCameraPropertyBaseHeaderBD
#ವ್ಯಾಖ್ಯಾನಿಸು XR_LIST_ALL_ಮಗು_STRUCTURE_TYPES_Xr_Camera_Property_ತಳ_ಶೀರ್ಷಿಕೆ_BD(_avail, _unavail) \
    impl_XR_LIST_ALL_ಮಗು_STRUCTURE_TYPES_Xr_Camera_Property_ತಳ_ಶೀರ್ಷಿಕೆ_BD_CORE(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrCameraPropertyBaseHeaderBD()
#ವ್ಯಾಖ್ಯಾನಿಸು impl_XR_LIST_ALL_ಮಗು_STRUCTURE_TYPES_Xr_Camera_Property_ತಳ_ಶೀರ್ಷಿಕೆ_BD_CORE(_avail, _unavail) \
    _avail(XrCameraPropertyFacingBD, XR_TYPE_CAMERA_PROPERTY_FACING_BD) \
    _avail(XrCameraPropertyPositionBD, XR_TYPE_CAMERA_PROPERTY_POSITION_BD) \
    _avail(XrCameraPropertyCameraTypeBD, XR_TYPE_CAMERA_PROPERTY_CAMERA_TYPE_BD) \





/// Like XR_LIST_ALL_STRUCTURE_TYPES, but only includes types whose parent struct type is XrCameraSupportedCapabilityBaseHeaderBD
#ವ್ಯಾಖ್ಯಾನಿಸು XR_LIST_ALL_ಮಗು_STRUCTURE_TYPES_Xr_Camera_Supported_Capability_ತಳ_ಶೀರ್ಷಿಕೆ_BD(_avail, _unavail) \
    impl_XR_LIST_ALL_ಮಗು_STRUCTURE_TYPES_Xr_Camera_Supported_Capability_ತಳ_ಶೀರ್ಷಿಕೆ_BD_CORE(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrCameraSupportedCapabilityBaseHeaderBD()
#ವ್ಯಾಖ್ಯಾನಿಸು impl_XR_LIST_ALL_ಮಗು_STRUCTURE_TYPES_Xr_Camera_Supported_Capability_ತಳ_ಶೀರ್ಷಿಕೆ_BD_CORE(_avail, _unavail) \
    _avail(Xr_Camera_Supported_Capability_Image_Resolution_And_ಚೌಕಟ್ಟು_ದರ_BD, XR_TYPE_CAMERA_SUPPORTED_CAPABILITY_IMAGE_RESOLUTION_AND_ಚೌಕಟ್ಟು_ದರ_BD) \
    _avail(Xr_Camera_Supported_Capability_ದತ್ತಾಂಶ_Transfer_Type_BD, XR_TYPE_CAMERA_SUPPORTED_CAPABILITY_ದತ್ತಾಂಶ_TRANSFER_TYPE_BD) \
    _avail(XrCameraSupportedCapabilityImageFormatBD, XR_TYPE_CAMERA_SUPPORTED_CAPABILITY_IMAGE_FORMAT_BD) \
    _avail(XrCameraSupportedCapabilityCameraModelBD, XR_TYPE_CAMERA_SUPPORTED_CAPABILITY_CAMERA_MODEL_BD) \





/// Like XR_LIST_ALL_STRUCTURE_TYPES, but only includes types whose parent struct type is XrCameraCapabilityBaseHeaderBD
#ವ್ಯಾಖ್ಯಾನಿಸು XR_LIST_ALL_ಮಗು_STRUCTURE_TYPES_Xr_Camera_Capability_ತಳ_ಶೀರ್ಷಿಕೆ_BD(_avail, _unavail) \
    impl_XR_LIST_ALL_ಮಗು_STRUCTURE_TYPES_Xr_Camera_Capability_ತಳ_ಶೀರ್ಷಿಕೆ_BD_CORE(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrCameraCapabilityBaseHeaderBD()
#ವ್ಯಾಖ್ಯಾನಿಸು impl_XR_LIST_ALL_ಮಗು_STRUCTURE_TYPES_Xr_Camera_Capability_ತಳ_ಶೀರ್ಷಿಕೆ_BD_CORE(_avail, _unavail) \
    _avail(Xr_Camera_Capability_Image_Resolution_And_ಚೌಕಟ್ಟು_ದರ_BD, XR_TYPE_CAMERA_CAPABILITY_IMAGE_RESOLUTION_AND_ಚೌಕಟ್ಟು_ದರ_BD) \
    _avail(Xr_Camera_Capability_ದತ್ತಾಂಶ_Transfer_Type_BD, XR_TYPE_CAMERA_CAPABILITY_ದತ್ತಾಂಶ_TRANSFER_TYPE_BD) \
    _avail(XrCameraCapabilityImageFormatBD, XR_TYPE_CAMERA_CAPABILITY_IMAGE_FORMAT_BD) \
    _avail(XrCameraCapabilityCameraModelBD, XR_TYPE_CAMERA_CAPABILITY_CAMERA_MODEL_BD) \





/// Like XR_LIST_ALL_STRUCTURE_TYPES, but only includes types whose parent struct type is XrCameraImageDataBaseHeaderBD
#ವ್ಯಾಖ್ಯಾನಿಸು XR_LIST_ALL_ಮಗು_STRUCTURE_TYPES_Xr_Camera_Image_ದತ್ತಾಂಶ_ತಳ_ಶೀರ್ಷಿಕೆ_BD(_avail, _unavail) \
    impl_XR_LIST_ALL_ಮಗು_STRUCTURE_TYPES_Xr_Camera_Image_ದತ್ತಾಂಶ_ತಳ_ಶೀರ್ಷಿಕೆ_BD_CORE(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrCameraImageDataBaseHeaderBD()
#ವ್ಯಾಖ್ಯಾನಿಸು impl_XR_LIST_ALL_ಮಗು_STRUCTURE_TYPES_Xr_Camera_Image_ದತ್ತಾಂಶ_ತಳ_ಶೀರ್ಷಿಕೆ_BD_CORE(_avail, _unavail) \
    _avail(Xr_Camera_Image_ದತ್ತಾಂಶ_Raw_ಬಫರ್_BD, XR_TYPE_CAMERA_IMAGE_ದತ್ತಾಂಶ_RAW_ಬಫರ್_BD) \





/// Like XR_LIST_ALL_STRUCTURE_TYPES, but only includes types whose parent struct type is XrGoogleCloudAuthInfoBaseHeaderANDROID
#ವ್ಯಾಖ್ಯಾನಿಸು XR_LIST_ALL_ಮಗು_STRUCTURE_TYPES_Xr_Google_Cloud_Auth_Info_ತಳ_ಶೀರ್ಷಿಕೆ_ANDROID(_avail, _unavail) \
    impl_XR_LIST_ALL_ಮಗು_STRUCTURE_TYPES_Xr_Google_Cloud_Auth_Info_ತಳ_ಶೀರ್ಷಿಕೆ_ANDROID_CORE(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_CHILD_STRUCTURE_TYPES_XrGoogleCloudAuthInfoBaseHeaderANDROID()
#ವ್ಯಾಖ್ಯಾನಿಸು impl_XR_LIST_ALL_ಮಗು_STRUCTURE_TYPES_Xr_Google_Cloud_Auth_Info_ತಳ_ಶೀರ್ಷಿಕೆ_ANDROID_CORE(_avail, _unavail) \
    _avail(Xr_Google_Cloud_Auth_Info_Api_ಕೀಲಿ_ANDROID, XR_TYPE_GOOGLE_CLOUD_AUTH_INFO_API_ಕೀಲಿ_ANDROID) \
    _avail(XrGoogleCloudAuthInfoTokenANDROID, XR_TYPE_GOOGLE_CLOUD_AUTH_INFO_TOKEN_ANDROID) \
    _avail(XrGoogleCloudAuthInfoKeylessANDROID, XR_TYPE_GOOGLE_CLOUD_AUTH_INFO_KEYLESS_ANDROID) \





#ಆದರೆ_ಅಂತ್ಯ

