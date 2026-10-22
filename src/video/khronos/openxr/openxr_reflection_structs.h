#که_نه_تعریف_شوی OPENXR_REFLECTION_STRUCTS_H_
#تعریف_کړه OPENXR_REFLECTION_STRUCTS_H_ 1

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
This file contains expansion macros (X Macros) for OpenXR structures.
*/



/// Calls one of your macros with the structure type name and the XrStructureType constant for
/// each known structure type. The first macro (_avail) is called for those that are available,
/// while the second macro (_unavail) is called for those unavailable due to preprocessor definitions.
#تعریف_کړه XR_LIST_ALL_STRUCTURE_TYPES(_avail, _unavail) \
    _impl_XR_LIST_ALL_STRUCTURE_TYPES_CORE(_avail, _unavail) \
    _impl_XR_LIST_ALL_STRUCTURE_TYPES_XR_USE_GRAPHICS_API_D3D11(_avail, _unavail) \
    _impl_XR_LIST_ALL_STRUCTURE_TYPES_XR_USE_GRAPHICS_API_D3D12(_avail, _unavail) \
    _impl_XR_LIST_ALL_STRUCTURE_TYPES_XR_USE_GRAPHICS_API_METAL(_avail, _unavail) \
    _impl_XR_LIST_ALL_STRUCTURE_TYPES_XR_USE_GRAPHICS_API_OPENGL(_avail, _unavail) \
    _impl_XR_LIST_ALL_STRUCTURE_TYPES_XR_USE_GRAPHICS_API_OPENGL_XR_USE_PLATFORM_WAYLAND(_avail, _unavail) \
    _impl_XR_LIST_ALL_STRUCTURE_TYPES_XR_USE_GRAPHICS_API_OPENGL_XR_USE_PLATFORM_WIN32(_avail, _unavail) \
    _impl_XR_LIST_ALL_STRUCTURE_TYPES_XR_USE_GRAPHICS_API_OPENGL_XR_USE_PLATFORM_XCB(_avail, _unavail) \
    _impl_XR_LIST_ALL_STRUCTURE_TYPES_XR_USE_GRAPHICS_API_OPENGL_XR_USE_PLATFORM_XLIB(_avail, _unavail) \
    _impl_XR_LIST_ALL_STRUCTURE_TYPES_XR_USE_GRAPHICS_API_OPENGL_ES(_avail, _unavail) \
    _impl_XR_LIST_ALL_STRUCTURE_TYPES_XR_USE_GRAPHICS_API_OPENGL_ES_XR_USE_PLATFORM_ANDROID(_avail, _unavail) \
    _impl_XR_LIST_ALL_STRUCTURE_TYPES_XR_USE_GRAPHICS_API_VULKAN(_avail, _unavail) \
    _impl_XR_LIST_ALL_STRUCTURE_TYPES_XR_USE_PLATFORM_ANDROID(_avail, _unavail) \
    _impl_XR_LIST_ALL_STRUCTURE_TYPES_XR_USE_PLATFORM_EGL(_avail, _unavail) \
    _impl_XR_LIST_ALL_STRUCTURE_TYPES_XR_USE_PLATFORM_ML(_avail, _unavail) \
    _impl_XR_LIST_ALL_STRUCTURE_TYPES_XR_USE_PLATFORM_WIN32(_avail, _unavail) \


// Implementation detail of XR_LIST_ALL_STRUCTURE_TYPES()
#تعریف_کړه _impl_XR_LIST_ALL_STRUCTURE_TYPES_CORE(_avail, _unavail) \
    _avail(XrApiLayerProperties, XR_TYPE_API_LAYER_PROPERTIES) \
    _avail(XrExtensionProperties, XR_TYPE_EXTENSION_PROPERTIES) \
    _avail(XrInstanceCreateInfo, XR_TYPE_INSTANCE_CREATE_INFO) \
    _avail(XrInstanceProperties, XR_TYPE_INSTANCE_PROPERTIES) \
    _avail(Xr_Event_معلومات_بفر, XR_TYPE_EVENT_معلومات_بفر) \
    _avail(XrSystemGetInfo, XR_TYPE_SYSTEM_GET_INFO) \
    _avail(XrSystemProperties, XR_TYPE_SYSTEM_PROPERTIES) \
    _avail(XrSessionCreateInfo, XR_TYPE_SESSION_CREATE_INFO) \
    _avail(XrReferenceSpaceCreateInfo, XR_TYPE_REFERENCE_SPACE_CREATE_INFO) \
    _avail(XrActionSpaceCreateInfo, XR_TYPE_ACTION_SPACE_CREATE_INFO) \
    _avail(XrSpaceLocation, XR_TYPE_SPACE_LOCATION) \
    _avail(XrSpaceVelocity, XR_TYPE_SPACE_VELOCITY) \
    _avail(XrViewConfigurationProperties, XR_TYPE_VIEW_CONFIGURATION_PROPERTIES) \
    _avail(XrViewConfigurationView, XR_TYPE_VIEW_CONFIGURATION_VIEW) \
    _avail(XrSwapchainCreateInfo, XR_TYPE_SWAPCHAIN_CREATE_INFO) \
    _avail(XrSwapchainImageAcquireInfo, XR_TYPE_SWAPCHAIN_IMAGE_ACQUIRE_INFO) \
    _avail(XrSwapchainImageWaitInfo, XR_TYPE_SWAPCHAIN_IMAGE_WAIT_INFO) \
    _avail(XrSwapchainImageReleaseInfo, XR_TYPE_SWAPCHAIN_IMAGE_RELEASE_INFO) \
    _avail(XrSessionBeginInfo, XR_TYPE_SESSION_BEGIN_INFO) \
    _avail(Xr_چوکاټ_State, XR_TYPE_چوکاټ_STATE) \
    _avail(Xr_چوکاټ_Wait_Info, XR_TYPE_چوکاټ_WAIT_INFO) \
    _avail(Xr_چوکاټ_Begin_Info, XR_TYPE_چوکاټ_BEGIN_INFO) \
    _avail(Xr_چوکاټ_پای_ټکی_Info, XR_TYPE_چوکاټ_پای_ټکی_INFO) \
    _avail(XrViewState, XR_TYPE_VIEW_STATE) \
    _avail(XrViewLocateInfo, XR_TYPE_VIEW_LOCATE_INFO) \
    _avail(XrView, XR_TYPE_VIEW) \
    _avail(Xr_Action_سېټ_Create_Info, XR_TYPE_ACTION_سېټ_CREATE_INFO) \
    _avail(XrActionCreateInfo, XR_TYPE_ACTION_CREATE_INFO) \
    _avail(XrInteractionProfileSuggestedBinding, XR_TYPE_INTERACTION_PROFILE_SUGGESTED_BINDING) \
    _avail(XrSessionActionSetsAttachInfo, XR_TYPE_SESSION_ACTION_SETS_ATTACH_INFO) \
    _avail(XrInteractionProfileState, XR_TYPE_INTERACTION_PROFILE_STATE) \
    _avail(XrActionStateGetInfo, XR_TYPE_ACTION_STATE_GET_INFO) \
    _avail(XrActionStateBoolean, XR_TYPE_ACTION_STATE_BOOLEAN) \
    _avail(XrActionStateFloat, XR_TYPE_ACTION_STATE_FLOAT) \
    _avail(XrActionStateVector2f, XR_TYPE_ACTION_STATE_VECTOR2F) \
    _avail(XrActionStatePose, XR_TYPE_ACTION_STATE_POSE) \
    _avail(XrActionsSyncInfo, XR_TYPE_ACTIONS_SYNC_INFO) \
    _avail(XrBoundSourcesForActionEnumerateInfo, XR_TYPE_BOUND_SOURCES_FOR_ACTION_ENUMERATE_INFO) \
    _avail(Xr_ننوت_سرچینه_Localized_Name_Get_Info, XR_TYPE_ننوت_سرچینه_LOCALIZED_NAME_GET_INFO) \
    _avail(XrHapticActionInfo, XR_TYPE_HAPTIC_ACTION_INFO) \
    _avail(XrCompositionLayerProjectionView, XR_TYPE_COMPOSITION_LAYER_PROJECTION_VIEW) \
    _avail(XrCompositionLayerProjection, XR_TYPE_COMPOSITION_LAYER_PROJECTION) \
    _avail(XrCompositionLayerQuad, XR_TYPE_COMPOSITION_LAYER_QUAD) \
    _avail(Xr_Event_معلومات_Events_ورک, XR_TYPE_EVENT_معلومات_EVENTS_ورک) \
    _avail(Xr_Event_معلومات_Instance_Loss_Pending, XR_TYPE_EVENT_معلومات_INSTANCE_LOSS_PENDING) \
    _avail(Xr_Event_معلومات_Session_State_بدل_شوی, XR_TYPE_EVENT_معلومات_SESSION_STATE_بدل_شوی) \
    _avail(Xr_Event_معلومات_Reference_Space_Change_Pending, XR_TYPE_EVENT_معلومات_REFERENCE_SPACE_CHANGE_PENDING) \
    _avail(Xr_Event_معلومات_Interaction_Profile_بدل_شوی, XR_TYPE_EVENT_معلومات_INTERACTION_PROFILE_بدل_شوی) \
    _avail(XrHapticVibration, XR_TYPE_HAPTIC_VIBRATION) \
    _avail(XrSpacesLocateInfo, XR_TYPE_SPACES_LOCATE_INFO) \
    _avail(XrSpaceLocations, XR_TYPE_SPACE_LOCATIONS) \
    _avail(XrSpaceVelocities, XR_TYPE_SPACE_VELOCITIES) \
    _avail(XrCompositionLayerCubeKHR, XR_TYPE_COMPOSITION_LAYER_CUBE_KHR) \
    _avail(Xr_Composition_Layer_ژوروالی_Info_KHR, XR_TYPE_COMPOSITION_LAYER_ژوروالی_INFO_KHR) \
    _avail(XrCompositionLayerCylinderKHR, XR_TYPE_COMPOSITION_LAYER_CYLINDER_KHR) \
    _avail(XrCompositionLayerEquirectKHR, XR_TYPE_COMPOSITION_LAYER_EQUIRECT_KHR) \
    _avail(Xr_Visibility_ماسک_KHR, XR_TYPE_VISIBILITY_ماسک_KHR) \
    _avail(Xr_Event_معلومات_Visibility_ماسک_بدل_شوی_KHR, XR_TYPE_EVENT_معلومات_VISIBILITY_ماسک_بدل_شوی_KHR) \
    _avail(XrCompositionLayerColorScaleBiasKHR, XR_TYPE_COMPOSITION_LAYER_COLOR_SCALE_BIAS_KHR) \
    _avail(XrCompositionLayerEquirect2KHR, XR_TYPE_COMPOSITION_LAYER_EQUIRECT2_KHR) \
    _avail(XrBindingModificationsKHR, XR_TYPE_BINDING_MODIFICATIONS_KHR) \
    _avail(Xr_Event_معلومات_Perf_Settings_EXT, XR_TYPE_EVENT_معلومات_PERF_SETTINGS_EXT) \
    _avail(XrDebugUtilsObjectNameInfoEXT, XR_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT) \
    _avail(XrDebugUtilsLabelEXT, XR_TYPE_DEBUG_UTILS_LABEL_EXT) \
    _avail(Xr_Debug_Utils_Messenger_Callback_معلومات_EXT, XR_TYPE_DEBUG_UTILS_MESSENGER_CALLBACK_معلومات_EXT) \
    _avail(XrDebugUtilsMessengerCreateInfoEXT, XR_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT) \
    _avail(XrSystemEyeGazeInteractionPropertiesEXT, XR_TYPE_SYSTEM_EYE_GAZE_INTERACTION_PROPERTIES_EXT) \
    _avail(Xr_Eye_Gaze_Sample_وخت_EXT, XR_TYPE_EYE_GAZE_SAMPLE_وخت_EXT) \
    _avail(XrSessionCreateInfoOverlayEXTX, XR_TYPE_SESSION_CREATE_INFO_OVERLAY_EXTX) \
    _avail(Xr_Event_معلومات_Main_Session_Visibility_بدل_شوی_EXTX, XR_TYPE_EVENT_معلومات_MAIN_SESSION_VISIBILITY_بدل_شوی_EXTX) \
    _avail(XrSpatialAnchorCreateInfoMSFT, XR_TYPE_SPATIAL_ANCHOR_CREATE_INFO_MSFT) \
    _avail(XrSpatialAnchorSpaceCreateInfoMSFT, XR_TYPE_SPATIAL_ANCHOR_SPACE_CREATE_INFO_MSFT) \
    _avail(XrCompositionLayerImageLayoutFB, XR_TYPE_COMPOSITION_LAYER_IMAGE_LAYOUT_FB) \
    _avail(XrCompositionLayerAlphaBlendFB, XR_TYPE_COMPOSITION_LAYER_ALPHA_BLEND_FB) \
    _avail(Xr_View_Configuration_ژوروالی_Range_EXT, XR_TYPE_VIEW_CONFIGURATION_ژوروالی_RANGE_EXT) \
    _avail(Xr_Spatial_ګراف_غوټه_Space_Create_Info_MSFT, XR_TYPE_SPATIAL_ګراف_غوټه_SPACE_CREATE_INFO_MSFT) \
    _avail(Xr_Spatial_ګراف_Static_غوټه_Binding_Create_Info_MSFT, XR_TYPE_SPATIAL_ګراف_STATIC_غوټه_BINDING_CREATE_INFO_MSFT) \
    _avail(Xr_Spatial_ګراف_غوټه_Binding_Properties_Get_Info_MSFT, XR_TYPE_SPATIAL_ګراف_غوټه_BINDING_PROPERTIES_GET_INFO_MSFT) \
    _avail(Xr_Spatial_ګراف_غوټه_Binding_Properties_MSFT, XR_TYPE_SPATIAL_ګراف_غوټه_BINDING_PROPERTIES_MSFT) \
    _avail(XrSystemHandTrackingPropertiesEXT, XR_TYPE_SYSTEM_HAND_TRACKING_PROPERTIES_EXT) \
    _avail(XrHandTrackerCreateInfoEXT, XR_TYPE_HAND_TRACKER_CREATE_INFO_EXT) \
    _avail(XrHandJointsLocateInfoEXT, XR_TYPE_HAND_JOINTS_LOCATE_INFO_EXT) \
    _avail(XrHandJointLocationsEXT, XR_TYPE_HAND_JOINT_LOCATIONS_EXT) \
    _avail(XrHandJointVelocitiesEXT, XR_TYPE_HAND_JOINT_VELOCITIES_EXT) \
    _avail(XrSystemHandTrackingMeshPropertiesMSFT, XR_TYPE_SYSTEM_HAND_TRACKING_MESH_PROPERTIES_MSFT) \
    _avail(XrHandMeshSpaceCreateInfoMSFT, XR_TYPE_HAND_MESH_SPACE_CREATE_INFO_MSFT) \
    _avail(XrHandMeshUpdateInfoMSFT, XR_TYPE_HAND_MESH_UPDATE_INFO_MSFT) \
    _avail(XrHandMeshMSFT, XR_TYPE_HAND_MESH_MSFT) \
    _avail(XrHandPoseTypeInfoMSFT, XR_TYPE_HAND_POSE_TYPE_INFO_MSFT) \
    _avail(XrSecondaryViewConfigurationSessionBeginInfoMSFT, XR_TYPE_SECONDARY_VIEW_CONFIGURATION_SESSION_BEGIN_INFO_MSFT) \
    _avail(XrSecondaryViewConfigurationStateMSFT, XR_TYPE_SECONDARY_VIEW_CONFIGURATION_STATE_MSFT) \
    _avail(Xr_Secondary_View_Configuration_چوکاټ_State_MSFT, XR_TYPE_SECONDARY_VIEW_CONFIGURATION_چوکاټ_STATE_MSFT) \
    _avail(XrSecondaryViewConfigurationLayerInfoMSFT, XR_TYPE_SECONDARY_VIEW_CONFIGURATION_LAYER_INFO_MSFT) \
    _avail(Xr_Secondary_View_Configuration_چوکاټ_پای_ټکی_Info_MSFT, XR_TYPE_SECONDARY_VIEW_CONFIGURATION_چوکاټ_پای_ټکی_INFO_MSFT) \
    _avail(XrSecondaryViewConfigurationSwapchainCreateInfoMSFT, XR_TYPE_SECONDARY_VIEW_CONFIGURATION_SWAPCHAIN_CREATE_INFO_MSFT) \
    _avail(Xr_Controller_Model_کلی_State_MSFT, XR_TYPE_CONTROLLER_MODEL_کلی_STATE_MSFT) \
    _avail(Xr_Controller_Model_غوټه_Properties_MSFT, XR_TYPE_CONTROLLER_MODEL_غوټه_PROPERTIES_MSFT) \
    _avail(XrControllerModelPropertiesMSFT, XR_TYPE_CONTROLLER_MODEL_PROPERTIES_MSFT) \
    _avail(Xr_Controller_Model_غوټه_State_MSFT, XR_TYPE_CONTROLLER_MODEL_غوټه_STATE_MSFT) \
    _avail(XrControllerModelStateMSFT, XR_TYPE_CONTROLLER_MODEL_STATE_MSFT) \
    _avail(XrViewConfigurationViewFovEPIC, XR_TYPE_VIEW_CONFIGURATION_VIEW_FOV_EPIC) \
    _avail(XrCompositionLayerReprojectionInfoMSFT, XR_TYPE_COMPOSITION_LAYER_REPROJECTION_INFO_MSFT) \
    _avail(XrCompositionLayerReprojectionPlaneOverrideMSFT, XR_TYPE_COMPOSITION_LAYER_REPROJECTION_PLANE_OVERRIDE_MSFT) \
    _avail(XrCompositionLayerSecureContentFB, XR_TYPE_COMPOSITION_LAYER_SECURE_CONTENT_FB) \
    _avail(XrSystemBodyTrackingPropertiesFB, XR_TYPE_SYSTEM_BODY_TRACKING_PROPERTIES_FB) \
    _avail(XrBodyTrackerCreateInfoFB, XR_TYPE_BODY_TRACKER_CREATE_INFO_FB) \
    _avail(XrBodySkeletonFB, XR_TYPE_BODY_SKELETON_FB) \
    _avail(XrBodyJointsLocateInfoFB, XR_TYPE_BODY_JOINTS_LOCATE_INFO_FB) \
    _avail(XrBodyJointLocationsFB, XR_TYPE_BODY_JOINT_LOCATIONS_FB) \
    _avail(XrInteractionProfileDpadBindingEXT, XR_TYPE_INTERACTION_PROFILE_DPAD_BINDING_EXT) \
    _avail(Xr_Interaction_Profile_Analog_پوله_VALVE, XR_TYPE_INTERACTION_PROFILE_ANALOG_پوله_VALVE) \
    _avail(XrHandJointsMotionRangeInfoEXT, XR_TYPE_HAND_JOINTS_MOTION_RANGE_INFO_EXT) \
    _avail(XrSceneObserverCreateInfoMSFT, XR_TYPE_SCENE_OBSERVER_CREATE_INFO_MSFT) \
    _avail(XrSceneCreateInfoMSFT, XR_TYPE_SCENE_CREATE_INFO_MSFT) \
    _avail(XrNewSceneComputeInfoMSFT, XR_TYPE_NEW_SCENE_COMPUTE_INFO_MSFT) \
    _avail(XrVisualMeshComputeLodInfoMSFT, XR_TYPE_VISUAL_MESH_COMPUTE_LOD_INFO_MSFT) \
    _avail(XrSceneComponentsMSFT, XR_TYPE_SCENE_COMPONENTS_MSFT) \
    _avail(XrSceneComponentsGetInfoMSFT, XR_TYPE_SCENE_COMPONENTS_GET_INFO_MSFT) \
    _avail(XrSceneComponentLocationsMSFT, XR_TYPE_SCENE_COMPONENT_LOCATIONS_MSFT) \
    _avail(XrSceneComponentsLocateInfoMSFT, XR_TYPE_SCENE_COMPONENTS_LOCATE_INFO_MSFT) \
    _avail(XrSceneObjectsMSFT, XR_TYPE_SCENE_OBJECTS_MSFT) \
    _avail(Xr_Scene_Component_پلار_Filter_Info_MSFT, XR_TYPE_SCENE_COMPONENT_پلار_FILTER_INFO_MSFT) \
    _avail(XrSceneObjectTypesFilterInfoMSFT, XR_TYPE_SCENE_OBJECT_TYPES_FILTER_INFO_MSFT) \
    _avail(XrScenePlanesMSFT, XR_TYPE_SCENE_PLANES_MSFT) \
    _avail(XrScenePlaneAlignmentFilterInfoMSFT, XR_TYPE_SCENE_PLANE_ALIGNMENT_FILTER_INFO_MSFT) \
    _avail(XrSceneMeshesMSFT, XR_TYPE_SCENE_MESHES_MSFT) \
    _avail(XrSceneMeshBuffersGetInfoMSFT, XR_TYPE_SCENE_MESH_BUFFERS_GET_INFO_MSFT) \
    _avail(XrSceneMeshBuffersMSFT, XR_TYPE_SCENE_MESH_BUFFERS_MSFT) \
    _avail(Xr_Scene_Mesh_راس_بفر_MSFT, XR_TYPE_SCENE_MESH_راس_بفر_MSFT) \
    _avail(XrSceneMeshIndicesUint32MSFT, XR_TYPE_SCENE_MESH_INDICES_UINT32_MSFT) \
    _avail(XrSceneMeshIndicesUint16MSFT, XR_TYPE_SCENE_MESH_INDICES_UINT16_MSFT) \
    _avail(Xr_Serialized_Scene_Fragment_معلومات_Get_Info_MSFT, XR_TYPE_SERIALIZED_SCENE_FRAGMENT_معلومات_GET_INFO_MSFT) \
    _avail(XrSceneDeserializeInfoMSFT, XR_TYPE_SCENE_DESERIALIZE_INFO_MSFT) \
    _avail(Xr_Event_معلومات_Display_Refresh_شرح_بدل_شوی_FB, XR_TYPE_EVENT_معلومات_DISPLAY_REFRESH_شرح_بدل_شوی_FB) \
    _avail(XrViveTrackerPathsHTCX, XR_TYPE_VIVE_TRACKER_PATHS_HTCX) \
    _avail(Xr_Event_معلومات_Vive_Tracker_Connected_HTCX, XR_TYPE_EVENT_معلومات_VIVE_TRACKER_CONNECTED_HTCX) \
    _avail(XrSystemFacialTrackingPropertiesHTC, XR_TYPE_SYSTEM_FACIAL_TRACKING_PROPERTIES_HTC) \
    _avail(XrFacialExpressionsHTC, XR_TYPE_FACIAL_EXPRESSIONS_HTC) \
    _avail(XrFacialTrackerCreateInfoHTC, XR_TYPE_FACIAL_TRACKER_CREATE_INFO_HTC) \
    _avail(XrSystemColorSpacePropertiesFB, XR_TYPE_SYSTEM_COLOR_SPACE_PROPERTIES_FB) \
    _avail(XrHandTrackingMeshFB, XR_TYPE_HAND_TRACKING_MESH_FB) \
    _avail(XrHandTrackingScaleFB, XR_TYPE_HAND_TRACKING_SCALE_FB) \
    _avail(XrHandTrackingAimStateFB, XR_TYPE_HAND_TRACKING_AIM_STATE_FB) \
    _avail(XrHandTrackingCapsulesStateFB, XR_TYPE_HAND_TRACKING_CAPSULES_STATE_FB) \
    _avail(XrSystemSpatialEntityPropertiesFB, XR_TYPE_SYSTEM_SPATIAL_ENTITY_PROPERTIES_FB) \
    _avail(XrSpatialAnchorCreateInfoFB, XR_TYPE_SPATIAL_ANCHOR_CREATE_INFO_FB) \
    _avail(Xr_Space_Component_حالت_سېټ_Info_FB, XR_TYPE_SPACE_COMPONENT_حالت_سېټ_INFO_FB) \
    _avail(Xr_Space_Component_حالت_FB, XR_TYPE_SPACE_COMPONENT_حالت_FB) \
    _avail(Xr_Event_معلومات_Spatial_Anchor_Create_Complete_FB, XR_TYPE_EVENT_معلومات_SPATIAL_ANCHOR_CREATE_COMPLETE_FB) \
    _avail(Xr_Event_معلومات_Space_سېټ_حالت_Complete_FB, XR_TYPE_EVENT_معلومات_SPACE_سېټ_حالت_COMPLETE_FB) \
    _avail(XrFoveationProfileCreateInfoFB, XR_TYPE_FOVEATION_PROFILE_CREATE_INFO_FB) \
    _avail(XrSwapchainCreateInfoFoveationFB, XR_TYPE_SWAPCHAIN_CREATE_INFO_FOVEATION_FB) \
    _avail(XrSwapchainStateFoveationFB, XR_TYPE_SWAPCHAIN_STATE_FOVEATION_FB) \
    _avail(XrFoveationLevelProfileCreateInfoFB, XR_TYPE_FOVEATION_LEVEL_PROFILE_CREATE_INFO_FB) \
    _avail(XrSystemKeyboardTrackingPropertiesFB, XR_TYPE_SYSTEM_KEYBOARD_TRACKING_PROPERTIES_FB) \
    _avail(XrKeyboardSpaceCreateInfoFB, XR_TYPE_KEYBOARD_SPACE_CREATE_INFO_FB) \
    _avail(XrKeyboardTrackingQueryFB, XR_TYPE_KEYBOARD_TRACKING_QUERY_FB) \
    _avail(XrTriangleMeshCreateInfoFB, XR_TYPE_TRIANGLE_MESH_CREATE_INFO_FB) \
    _avail(XrSystemPassthroughPropertiesFB, XR_TYPE_SYSTEM_PASSTHROUGH_PROPERTIES_FB) \
    _avail(XrSystemPassthroughProperties2FB, XR_TYPE_SYSTEM_PASSTHROUGH_PROPERTIES2_FB) \
    _avail(XrPassthroughCreateInfoFB, XR_TYPE_PASSTHROUGH_CREATE_INFO_FB) \
    _avail(XrPassthroughLayerCreateInfoFB, XR_TYPE_PASSTHROUGH_LAYER_CREATE_INFO_FB) \
    _avail(XrCompositionLayerPassthroughFB, XR_TYPE_COMPOSITION_LAYER_PASSTHROUGH_FB) \
    _avail(XrGeometryInstanceCreateInfoFB, XR_TYPE_GEOMETRY_INSTANCE_CREATE_INFO_FB) \
    _avail(XrGeometryInstanceTransformFB, XR_TYPE_GEOMETRY_INSTANCE_TRANSFORM_FB) \
    _avail(XrPassthroughStyleFB, XR_TYPE_PASSTHROUGH_STYLE_FB) \
    _avail(Xr_Passthrough_Color_Map_Mono_منزل_Rgba_FB, XR_TYPE_PASSTHROUGH_COLOR_MAP_MONO_منزل_RGBA_FB) \
    _avail(Xr_Passthrough_Color_Map_Mono_منزل_Mono_FB, XR_TYPE_PASSTHROUGH_COLOR_MAP_MONO_منزل_MONO_FB) \
    _avail(XrPassthroughBrightnessContrastSaturationFB, XR_TYPE_PASSTHROUGH_BRIGHTNESS_CONTRAST_SATURATION_FB) \
    _avail(Xr_Event_معلومات_Passthrough_State_بدل_شوی_FB, XR_TYPE_EVENT_معلومات_PASSTHROUGH_STATE_بدل_شوی_FB) \
    _avail(Xr_Render_Model_لار_Info_FB, XR_TYPE_RENDER_MODEL_لار_INFO_FB) \
    _avail(XrRenderModelPropertiesFB, XR_TYPE_RENDER_MODEL_PROPERTIES_FB) \
    _avail(Xr_Render_Model_بفر_FB, XR_TYPE_RENDER_MODEL_بفر_FB) \
    _avail(Xr_Render_Model_بارول_Info_FB, XR_TYPE_RENDER_MODEL_بارول_INFO_FB) \
    _avail(XrSystemRenderModelPropertiesFB, XR_TYPE_SYSTEM_RENDER_MODEL_PROPERTIES_FB) \
    _avail(XrRenderModelCapabilitiesRequestFB, XR_TYPE_RENDER_MODEL_CAPABILITIES_REQUEST_FB) \
    _avail(XrViewLocateFoveatedRenderingVARJO, XR_TYPE_VIEW_LOCATE_FOVEATED_RENDERING_VARJO) \
    _avail(XrFoveatedViewConfigurationViewVARJO, XR_TYPE_FOVEATED_VIEW_CONFIGURATION_VIEW_VARJO) \
    _avail(XrSystemFoveatedRenderingPropertiesVARJO, XR_TYPE_SYSTEM_FOVEATED_RENDERING_PROPERTIES_VARJO) \
    _avail(Xr_Composition_Layer_ژوروالی_Test_VARJO, XR_TYPE_COMPOSITION_LAYER_ژوروالی_TEST_VARJO) \
    _avail(XrSystemMarkerTrackingPropertiesVARJO, XR_TYPE_SYSTEM_MARKER_TRACKING_PROPERTIES_VARJO) \
    _avail(Xr_Event_معلومات_Marker_Tracking_Update_VARJO, XR_TYPE_EVENT_معلومات_MARKER_TRACKING_UPDATE_VARJO) \
    _avail(XrMarkerSpaceCreateInfoVARJO, XR_TYPE_MARKER_SPACE_CREATE_INFO_VARJO) \
    _avail(Xr_چوکاټ_پای_ټکی_Info_ML, XR_TYPE_چوکاټ_پای_ټکی_INFO_ML) \
    _avail(Xr_Global_Dimmer_چوکاټ_پای_ټکی_Info_ML, XR_TYPE_GLOBAL_DIMMER_چوکاټ_پای_ټکی_INFO_ML) \
    _avail(XrSystemMarkerUnderstandingPropertiesML, XR_TYPE_SYSTEM_MARKER_UNDERSTANDING_PROPERTIES_ML) \
    _avail(XrMarkerDetectorCreateInfoML, XR_TYPE_MARKER_DETECTOR_CREATE_INFO_ML) \
    _avail(XrMarkerDetectorArucoInfoML, XR_TYPE_MARKER_DETECTOR_ARUCO_INFO_ML) \
    _avail(Xr_Marker_Detector_اندازه_Info_ML, XR_TYPE_MARKER_DETECTOR_اندازه_INFO_ML) \
    _avail(Xr_Marker_Detector_April_نښان_Info_ML, XR_TYPE_MARKER_DETECTOR_APRIL_نښان_INFO_ML) \
    _avail(XrMarkerDetectorCustomProfileInfoML, XR_TYPE_MARKER_DETECTOR_CUSTOM_PROFILE_INFO_ML) \
    _avail(XrMarkerDetectorSnapshotInfoML, XR_TYPE_MARKER_DETECTOR_SNAPSHOT_INFO_ML) \
    _avail(XrMarkerDetectorStateML, XR_TYPE_MARKER_DETECTOR_STATE_ML) \
    _avail(XrMarkerSpaceCreateInfoML, XR_TYPE_MARKER_SPACE_CREATE_INFO_ML) \
    _avail(XrLocalizationMapML, XR_TYPE_LOCALIZATION_MAP_ML) \
    _avail(Xr_Event_معلومات_Localization_بدل_شوی_ML, XR_TYPE_EVENT_معلومات_LOCALIZATION_بدل_شوی_ML) \
    _avail(XrMapLocalizationRequestInfoML, XR_TYPE_MAP_LOCALIZATION_REQUEST_INFO_ML) \
    _avail(XrLocalizationMapImportInfoML, XR_TYPE_LOCALIZATION_MAP_IMPORT_INFO_ML) \
    _avail(XrLocalizationEnableEventsInfoML, XR_TYPE_LOCALIZATION_ENABLE_EVENTS_INFO_ML) \
    _avail(XrSpatialAnchorsCreateInfoFromPoseML, XR_TYPE_SPATIAL_ANCHORS_CREATE_INFO_FROM_POSE_ML) \
    _avail(XrCreateSpatialAnchorsCompletionML, XR_TYPE_CREATE_SPATIAL_ANCHORS_COMPLETION_ML) \
    _avail(XrSpatialAnchorStateML, XR_TYPE_SPATIAL_ANCHOR_STATE_ML) \
    _avail(XrSpatialAnchorsCreateStorageInfoML, XR_TYPE_SPATIAL_ANCHORS_CREATE_STORAGE_INFO_ML) \
    _avail(XrSpatialAnchorsQueryInfoRadiusML, XR_TYPE_SPATIAL_ANCHORS_QUERY_INFO_RADIUS_ML) \
    _avail(XrSpatialAnchorsQueryCompletionML, XR_TYPE_SPATIAL_ANCHORS_QUERY_COMPLETION_ML) \
    _avail(XrSpatialAnchorsCreateInfoFromUuidsML, XR_TYPE_SPATIAL_ANCHORS_CREATE_INFO_FROM_UUIDS_ML) \
    _avail(XrSpatialAnchorsPublishInfoML, XR_TYPE_SPATIAL_ANCHORS_PUBLISH_INFO_ML) \
    _avail(XrSpatialAnchorsPublishCompletionML, XR_TYPE_SPATIAL_ANCHORS_PUBLISH_COMPLETION_ML) \
    _avail(XrSpatialAnchorsDeleteInfoML, XR_TYPE_SPATIAL_ANCHORS_DELETE_INFO_ML) \
    _avail(XrSpatialAnchorsDeleteCompletionML, XR_TYPE_SPATIAL_ANCHORS_DELETE_COMPLETION_ML) \
    _avail(XrSpatialAnchorsUpdateExpirationInfoML, XR_TYPE_SPATIAL_ANCHORS_UPDATE_EXPIRATION_INFO_ML) \
    _avail(XrSpatialAnchorsUpdateExpirationCompletionML, XR_TYPE_SPATIAL_ANCHORS_UPDATE_EXPIRATION_COMPLETION_ML) \
    _avail(XrSpatialAnchorsPublishCompletionDetailsML, XR_TYPE_SPATIAL_ANCHORS_PUBLISH_COMPLETION_DETAILS_ML) \
    _avail(XrSpatialAnchorsDeleteCompletionDetailsML, XR_TYPE_SPATIAL_ANCHORS_DELETE_COMPLETION_DETAILS_ML) \
    _avail(XrSpatialAnchorsUpdateExpirationCompletionDetailsML, XR_TYPE_SPATIAL_ANCHORS_UPDATE_EXPIRATION_COMPLETION_DETAILS_ML) \
    _avail(XrSpatialAnchorPersistenceInfoMSFT, XR_TYPE_SPATIAL_ANCHOR_PERSISTENCE_INFO_MSFT) \
    _avail(XrSpatialAnchorFromPersistedAnchorCreateInfoMSFT, XR_TYPE_SPATIAL_ANCHOR_FROM_PERSISTED_ANCHOR_CREATE_INFO_MSFT) \
    _avail(XrSceneMarkersMSFT, XR_TYPE_SCENE_MARKERS_MSFT) \
    _avail(XrSceneMarkerTypeFilterMSFT, XR_TYPE_SCENE_MARKER_TYPE_FILTER_MSFT) \
    _avail(XrSceneMarkerQRCodesMSFT, XR_TYPE_SCENE_MARKER_QR_CODES_MSFT) \
    _avail(XrSpaceQueryInfoFB, XR_TYPE_SPACE_QUERY_INFO_FB) \
    _avail(XrSpaceStorageLocationFilterInfoFB, XR_TYPE_SPACE_STORAGE_LOCATION_FILTER_INFO_FB) \
    _avail(XrSpaceUuidFilterInfoFB, XR_TYPE_SPACE_UUID_FILTER_INFO_FB) \
    _avail(XrSpaceComponentFilterInfoFB, XR_TYPE_SPACE_COMPONENT_FILTER_INFO_FB) \
    _avail(XrSpaceQueryResultsFB, XR_TYPE_SPACE_QUERY_RESULTS_FB) \
    _avail(Xr_Event_معلومات_Space_Query_Results_شته_FB, XR_TYPE_EVENT_معلومات_SPACE_QUERY_RESULTS_شته_FB) \
    _avail(Xr_Event_معلومات_Space_Query_Complete_FB, XR_TYPE_EVENT_معلومات_SPACE_QUERY_COMPLETE_FB) \
    _avail(XrSpaceSaveInfoFB, XR_TYPE_SPACE_SAVE_INFO_FB) \
    _avail(XrSpaceEraseInfoFB, XR_TYPE_SPACE_ERASE_INFO_FB) \
    _avail(Xr_Event_معلومات_Space_Save_Complete_FB, XR_TYPE_EVENT_معلومات_SPACE_SAVE_COMPLETE_FB) \
    _avail(Xr_Event_معلومات_Space_Erase_Complete_FB, XR_TYPE_EVENT_معلومات_SPACE_ERASE_COMPLETE_FB) \
    _avail(XrSpaceShareInfoFB, XR_TYPE_SPACE_SHARE_INFO_FB) \
    _avail(Xr_Event_معلومات_Space_Share_Complete_FB, XR_TYPE_EVENT_معلومات_SPACE_SHARE_COMPLETE_FB) \
    _avail(XrCompositionLayerSpaceWarpInfoFB, XR_TYPE_COMPOSITION_LAYER_SPACE_WARP_INFO_FB) \
    _avail(XrSystemSpaceWarpPropertiesFB, XR_TYPE_SYSTEM_SPACE_WARP_PROPERTIES_FB) \
    _avail(XrHapticAmplitudeEnvelopeVibrationFB, XR_TYPE_HAPTIC_AMPLITUDE_ENVELOPE_VIBRATION_FB) \
    _avail(XrSemanticLabelsFB, XR_TYPE_SEMANTIC_LABELS_FB) \
    _avail(Xr_ځای_Layout_FB, XR_TYPE_ځای_LAYOUT_FB) \
    _avail(XrBoundary2DFB, XR_TYPE_BOUNDARY_2D_FB) \
    _avail(XrSemanticLabelsSupportInfoFB, XR_TYPE_SEMANTIC_LABELS_SUPPORT_INFO_FB) \
    _avail(XrDigitalLensControlALMALENCE, XR_TYPE_DIGITAL_LENS_CONTROL_ALMALENCE) \
    _avail(Xr_Event_معلومات_Scene_Capture_Complete_FB, XR_TYPE_EVENT_معلومات_SCENE_CAPTURE_COMPLETE_FB) \
    _avail(XrSceneCaptureRequestInfoFB, XR_TYPE_SCENE_CAPTURE_REQUEST_INFO_FB) \
    _avail(XrSpaceContainerFB, XR_TYPE_SPACE_CONTAINER_FB) \
    _avail(XrFoveationEyeTrackedProfileCreateInfoMETA, XR_TYPE_FOVEATION_EYE_TRACKED_PROFILE_CREATE_INFO_META) \
    _avail(XrFoveationEyeTrackedStateMETA, XR_TYPE_FOVEATION_EYE_TRACKED_STATE_META) \
    _avail(XrSystemFoveationEyeTrackedPropertiesMETA, XR_TYPE_SYSTEM_FOVEATION_EYE_TRACKED_PROPERTIES_META) \
    _avail(XrSystemFaceTrackingPropertiesFB, XR_TYPE_SYSTEM_FACE_TRACKING_PROPERTIES_FB) \
    _avail(XrFaceTrackerCreateInfoFB, XR_TYPE_FACE_TRACKER_CREATE_INFO_FB) \
    _avail(Xr_Face_افاده_Info_FB, XR_TYPE_FACE_افاده_INFO_FB) \
    _avail(Xr_Face_افاده_Weights_FB, XR_TYPE_FACE_افاده_WEIGHTS_FB) \
    _avail(XrEyeTrackerCreateInfoFB, XR_TYPE_EYE_TRACKER_CREATE_INFO_FB) \
    _avail(XrEyeGazesInfoFB, XR_TYPE_EYE_GAZES_INFO_FB) \
    _avail(XrSystemEyeTrackingPropertiesFB, XR_TYPE_SYSTEM_EYE_TRACKING_PROPERTIES_FB) \
    _avail(XrEyeGazesFB, XR_TYPE_EYE_GAZES_FB) \
    _avail(XrPassthroughKeyboardHandsIntensityFB, XR_TYPE_PASSTHROUGH_KEYBOARD_HANDS_INTENSITY_FB) \
    _avail(XrCompositionLayerSettingsFB, XR_TYPE_COMPOSITION_LAYER_SETTINGS_FB) \
    _avail(XrHapticPcmVibrationFB, XR_TYPE_HAPTIC_PCM_VIBRATION_FB) \
    _avail(Xr_Device_Pcm_Sample_شرح_State_FB, XR_TYPE_DEVICE_PCM_SAMPLE_شرح_STATE_FB) \
    _avail(Xr_چوکاټ_Synthesis_Info_EXT, XR_TYPE_چوکاټ_SYNTHESIS_INFO_EXT) \
    _avail(Xr_چوکاټ_Synthesis_Config_View_EXT, XR_TYPE_چوکاټ_SYNTHESIS_CONFIG_VIEW_EXT) \
    _avail(Xr_Composition_Layer_ژوروالی_Test_FB, XR_TYPE_COMPOSITION_LAYER_ژوروالی_TEST_FB) \
    _avail(Xr_Local_Dimming_چوکاټ_پای_ټکی_Info_META, XR_TYPE_LOCAL_DIMMING_چوکاټ_پای_ټکی_INFO_META) \
    _avail(XrPassthroughPreferencesMETA, XR_TYPE_PASSTHROUGH_PREFERENCES_META) \
    _avail(XrSystemVirtualKeyboardPropertiesMETA, XR_TYPE_SYSTEM_VIRTUAL_KEYBOARD_PROPERTIES_META) \
    _avail(XrVirtualKeyboardCreateInfoMETA, XR_TYPE_VIRTUAL_KEYBOARD_CREATE_INFO_META) \
    _avail(XrVirtualKeyboardSpaceCreateInfoMETA, XR_TYPE_VIRTUAL_KEYBOARD_SPACE_CREATE_INFO_META) \
    _avail(XrVirtualKeyboardLocationInfoMETA, XR_TYPE_VIRTUAL_KEYBOARD_LOCATION_INFO_META) \
    _avail(Xr_Virtual_Keyboard_Model_Visibility_سېټ_Info_META, XR_TYPE_VIRTUAL_KEYBOARD_MODEL_VISIBILITY_سېټ_INFO_META) \
    _avail(XrVirtualKeyboardAnimationStateMETA, XR_TYPE_VIRTUAL_KEYBOARD_ANIMATION_STATE_META) \
    _avail(Xr_Virtual_Keyboard_Model_Animation_حالتونه_META, XR_TYPE_VIRTUAL_KEYBOARD_MODEL_ANIMATION_حالتونه_META) \
    _avail(Xr_Virtual_Keyboard_Texture_معلومات_META, XR_TYPE_VIRTUAL_KEYBOARD_TEXTURE_معلومات_META) \
    _avail(Xr_Virtual_Keyboard_ننوت_Info_META, XR_TYPE_VIRTUAL_KEYBOARD_ننوت_INFO_META) \
    _avail(Xr_Virtual_Keyboard_متن_Context_Change_Info_META, XR_TYPE_VIRTUAL_KEYBOARD_متن_CONTEXT_CHANGE_INFO_META) \
    _avail(Xr_Event_معلومات_Virtual_Keyboard_Commit_متن_META, XR_TYPE_EVENT_معلومات_VIRTUAL_KEYBOARD_COMMIT_متن_META) \
    _avail(Xr_Event_معلومات_Virtual_Keyboard_Backspace_META, XR_TYPE_EVENT_معلومات_VIRTUAL_KEYBOARD_BACKSPACE_META) \
    _avail(Xr_Event_معلومات_Virtual_Keyboard_Enter_META, XR_TYPE_EVENT_معلومات_VIRTUAL_KEYBOARD_ENTER_META) \
    _avail(Xr_Event_معلومات_Virtual_Keyboard_Shown_META, XR_TYPE_EVENT_معلومات_VIRTUAL_KEYBOARD_SHOWN_META) \
    _avail(Xr_Event_معلومات_Virtual_Keyboard_Hidden_META, XR_TYPE_EVENT_معلومات_VIRTUAL_KEYBOARD_HIDDEN_META) \
    _avail(XrExternalCameraOCULUS, XR_TYPE_EXTERNAL_CAMERA_OCULUS) \
    _avail(XrPerformanceMetricsStateMETA, XR_TYPE_PERFORMANCE_METRICS_STATE_META) \
    _avail(XrPerformanceMetricsCounterMETA, XR_TYPE_PERFORMANCE_METRICS_COUNTER_META) \
    _avail(XrSpaceListSaveInfoFB, XR_TYPE_SPACE_LIST_SAVE_INFO_FB) \
    _avail(Xr_Event_معلومات_Space_List_Save_Complete_FB, XR_TYPE_EVENT_معلومات_SPACE_LIST_SAVE_COMPLETE_FB) \
    _avail(XrSpaceUserCreateInfoFB, XR_TYPE_SPACE_USER_CREATE_INFO_FB) \
    _avail(XrSystemHeadsetIdPropertiesMETA, XR_TYPE_SYSTEM_HEADSET_ID_PROPERTIES_META) \
    _avail(XrSystemSpaceDiscoveryPropertiesMETA, XR_TYPE_SYSTEM_SPACE_DISCOVERY_PROPERTIES_META) \
    _avail(XrSpaceDiscoveryInfoMETA, XR_TYPE_SPACE_DISCOVERY_INFO_META) \
    _avail(XrSpaceFilterUuidMETA, XR_TYPE_SPACE_FILTER_UUID_META) \
    _avail(XrSpaceFilterComponentMETA, XR_TYPE_SPACE_FILTER_COMPONENT_META) \
    _avail(XrSpaceDiscoveryResultsMETA, XR_TYPE_SPACE_DISCOVERY_RESULTS_META) \
    _avail(Xr_Event_معلومات_Space_Discovery_Results_شته_META, XR_TYPE_EVENT_معلومات_SPACE_DISCOVERY_RESULTS_شته_META) \
    _avail(Xr_Event_معلومات_Space_Discovery_Complete_META, XR_TYPE_EVENT_معلومات_SPACE_DISCOVERY_COMPLETE_META) \
    _avail(XrRecommendedLayerResolutionMETA, XR_TYPE_RECOMMENDED_LAYER_RESOLUTION_META) \
    _avail(XrRecommendedLayerResolutionGetInfoMETA, XR_TYPE_RECOMMENDED_LAYER_RESOLUTION_GET_INFO_META) \
    _avail(XrSystemSpacePersistencePropertiesMETA, XR_TYPE_SYSTEM_SPACE_PERSISTENCE_PROPERTIES_META) \
    _avail(XrSpacesSaveInfoMETA, XR_TYPE_SPACES_SAVE_INFO_META) \
    _avail(Xr_Event_معلومات_Spaces_Save_پایله_META, XR_TYPE_EVENT_معلومات_SPACES_SAVE_پایله_META) \
    _avail(XrSpacesEraseInfoMETA, XR_TYPE_SPACES_ERASE_INFO_META) \
    _avail(Xr_Event_معلومات_Spaces_Erase_پایله_META, XR_TYPE_EVENT_معلومات_SPACES_ERASE_پایله_META) \
    _avail(XrPassthroughColorLutCreateInfoMETA, XR_TYPE_PASSTHROUGH_COLOR_LUT_CREATE_INFO_META) \
    _avail(XrPassthroughColorLutUpdateInfoMETA, XR_TYPE_PASSTHROUGH_COLOR_LUT_UPDATE_INFO_META) \
    _avail(XrPassthroughColorMapLutMETA, XR_TYPE_PASSTHROUGH_COLOR_MAP_LUT_META) \
    _avail(XrPassthroughColorMapInterpolatedLutMETA, XR_TYPE_PASSTHROUGH_COLOR_MAP_INTERPOLATED_LUT_META) \
    _avail(XrSystemPassthroughColorLutPropertiesMETA, XR_TYPE_SYSTEM_PASSTHROUGH_COLOR_LUT_PROPERTIES_META) \
    _avail(XrSpaceTriangleMeshGetInfoMETA, XR_TYPE_SPACE_TRIANGLE_MESH_GET_INFO_META) \
    _avail(XrSpaceTriangleMeshMETA, XR_TYPE_SPACE_TRIANGLE_MESH_META) \
    _avail(Xr_System_Properties_Body_Tracking_ډک_Body_META, XR_TYPE_SYSTEM_PROPERTIES_BODY_TRACKING_ډک_BODY_META) \
    _avail(Xr_Event_معلومات_Passthrough_Layer_Resumed_META, XR_TYPE_EVENT_معلومات_PASSTHROUGH_LAYER_RESUMED_META) \
    _avail(Xr_Body_Tracking_Calibration_حالت_META, XR_TYPE_BODY_TRACKING_CALIBRATION_حالت_META) \
    _avail(XrBodyTrackingCalibrationInfoMETA, XR_TYPE_BODY_TRACKING_CALIBRATION_INFO_META) \
    _avail(XrSystemPropertiesBodyTrackingCalibrationMETA, XR_TYPE_SYSTEM_PROPERTIES_BODY_TRACKING_CALIBRATION_META) \
    _avail(XrSystemPropertiesBodyTrackingFidelityMETA, XR_TYPE_SYSTEM_PROPERTIES_BODY_TRACKING_FIDELITY_META) \
    _avail(Xr_Body_Tracking_Fidelity_حالت_META, XR_TYPE_BODY_TRACKING_FIDELITY_حالت_META) \
    _avail(XrSystemFaceTrackingProperties2FB, XR_TYPE_SYSTEM_FACE_TRACKING_PROPERTIES2_FB) \
    _avail(XrFaceTrackerCreateInfo2FB, XR_TYPE_FACE_TRACKER_CREATE_INFO2_FB) \
    _avail(Xr_Face_افاده_Info2_FB, XR_TYPE_FACE_افاده_INFO2_FB) \
    _avail(Xr_Face_افاده_Weights2_FB, XR_TYPE_FACE_افاده_WEIGHTS2_FB) \
    _avail(XrSystemSpatialEntitySharingPropertiesMETA, XR_TYPE_SYSTEM_SPATIAL_ENTITY_SHARING_PROPERTIES_META) \
    _avail(XrShareSpacesInfoMETA, XR_TYPE_SHARE_SPACES_INFO_META) \
    _avail(Xr_Event_معلومات_Share_Spaces_Complete_META, XR_TYPE_EVENT_معلومات_SHARE_SPACES_COMPLETE_META) \
    _avail(Xr_Environment_ژوروالی_Provider_Create_Info_META, XR_TYPE_ENVIRONMENT_ژوروالی_PROVIDER_CREATE_INFO_META) \
    _avail(Xr_Environment_ژوروالی_Swapchain_Create_Info_META, XR_TYPE_ENVIRONMENT_ژوروالی_SWAPCHAIN_CREATE_INFO_META) \
    _avail(Xr_Environment_ژوروالی_Swapchain_State_META, XR_TYPE_ENVIRONMENT_ژوروالی_SWAPCHAIN_STATE_META) \
    _avail(Xr_Environment_ژوروالی_Image_Acquire_Info_META, XR_TYPE_ENVIRONMENT_ژوروالی_IMAGE_ACQUIRE_INFO_META) \
    _avail(Xr_Environment_ژوروالی_Image_View_META, XR_TYPE_ENVIRONMENT_ژوروالی_IMAGE_VIEW_META) \
    _avail(Xr_Environment_ژوروالی_Image_META, XR_TYPE_ENVIRONMENT_ژوروالی_IMAGE_META) \
    _avail(Xr_Environment_ژوروالی_Image_Timestamp_META, XR_TYPE_ENVIRONMENT_ژوروالی_IMAGE_TIMESTAMP_META) \
    _avail(Xr_Environment_ژوروالی_Hand_Removal_سېټ_Info_META, XR_TYPE_ENVIRONMENT_ژوروالی_HAND_REMOVAL_سېټ_INFO_META) \
    _avail(Xr_System_Environment_ژوروالی_Properties_META, XR_TYPE_SYSTEM_ENVIRONMENT_ژوروالی_PROPERTIES_META) \
    _avail(XrRenderModelCreateInfoEXT, XR_TYPE_RENDER_MODEL_CREATE_INFO_EXT) \
    _avail(XrRenderModelPropertiesGetInfoEXT, XR_TYPE_RENDER_MODEL_PROPERTIES_GET_INFO_EXT) \
    _avail(XrRenderModelPropertiesEXT, XR_TYPE_RENDER_MODEL_PROPERTIES_EXT) \
    _avail(XrRenderModelSpaceCreateInfoEXT, XR_TYPE_RENDER_MODEL_SPACE_CREATE_INFO_EXT) \
    _avail(XrRenderModelStateGetInfoEXT, XR_TYPE_RENDER_MODEL_STATE_GET_INFO_EXT) \
    _avail(XrRenderModelStateEXT, XR_TYPE_RENDER_MODEL_STATE_EXT) \
    _avail(XrRenderModelAssetCreateInfoEXT, XR_TYPE_RENDER_MODEL_ASSET_CREATE_INFO_EXT) \
    _avail(Xr_Render_Model_Asset_معلومات_Get_Info_EXT, XR_TYPE_RENDER_MODEL_ASSET_معلومات_GET_INFO_EXT) \
    _avail(Xr_Render_Model_Asset_معلومات_EXT, XR_TYPE_RENDER_MODEL_ASSET_معلومات_EXT) \
    _avail(XrRenderModelAssetPropertiesGetInfoEXT, XR_TYPE_RENDER_MODEL_ASSET_PROPERTIES_GET_INFO_EXT) \
    _avail(XrRenderModelAssetPropertiesEXT, XR_TYPE_RENDER_MODEL_ASSET_PROPERTIES_EXT) \
    _avail(XrInteractionRenderModelIdsEnumerateInfoEXT, XR_TYPE_INTERACTION_RENDER_MODEL_IDS_ENUMERATE_INFO_EXT) \
    _avail(Xr_Interaction_Render_Model_Subaction_لار_Info_EXT, XR_TYPE_INTERACTION_RENDER_MODEL_SUBACTION_لار_INFO_EXT) \
    _avail(Xr_Interaction_Render_Model_سر_Level_User_لار_Get_Info_EXT, XR_TYPE_INTERACTION_RENDER_MODEL_سر_LEVEL_USER_لار_GET_INFO_EXT) \
    _avail(Xr_Event_معلومات_Interaction_Render_Models_بدل_شوی_EXT, XR_TYPE_EVENT_معلومات_INTERACTION_RENDER_MODELS_بدل_شوی_EXT) \
    _avail(XrPassthroughCreateInfoHTC, XR_TYPE_PASSTHROUGH_CREATE_INFO_HTC) \
    _avail(XrPassthroughColorHTC, XR_TYPE_PASSTHROUGH_COLOR_HTC) \
    _avail(XrPassthroughMeshTransformInfoHTC, XR_TYPE_PASSTHROUGH_MESH_TRANSFORM_INFO_HTC) \
    _avail(XrCompositionLayerPassthroughHTC, XR_TYPE_COMPOSITION_LAYER_PASSTHROUGH_HTC) \
    _avail(XrFoveationApplyInfoHTC, XR_TYPE_FOVEATION_APPLY_INFO_HTC) \
    _avail(Xr_Foveation_Dynamic_ډېرپېښ_Info_HTC, XR_TYPE_FOVEATION_DYNAMIC_ډېرپېښ_INFO_HTC) \
    _avail(Xr_Foveation_Custom_ډېرپېښ_Info_HTC, XR_TYPE_FOVEATION_CUSTOM_ډېرپېښ_INFO_HTC) \
    _avail(XrSystemAnchorPropertiesHTC, XR_TYPE_SYSTEM_ANCHOR_PROPERTIES_HTC) \
    _avail(XrSpatialAnchorCreateInfoHTC, XR_TYPE_SPATIAL_ANCHOR_CREATE_INFO_HTC) \
    _avail(XrSystemBodyTrackingPropertiesHTC, XR_TYPE_SYSTEM_BODY_TRACKING_PROPERTIES_HTC) \
    _avail(XrBodyTrackerCreateInfoHTC, XR_TYPE_BODY_TRACKER_CREATE_INFO_HTC) \
    _avail(XrBodyJointsLocateInfoHTC, XR_TYPE_BODY_JOINTS_LOCATE_INFO_HTC) \
    _avail(XrBodyJointLocationsHTC, XR_TYPE_BODY_JOINT_LOCATIONS_HTC) \
    _avail(XrBodySkeletonHTC, XR_TYPE_BODY_SKELETON_HTC) \
    _avail(Xr_فعال_Action_سېټ_Priorities_EXT, XR_TYPE_فعال_ACTION_سېټ_PRIORITIES_EXT) \
    _avail(XrSystemForceFeedbackCurlPropertiesMNDX, XR_TYPE_SYSTEM_FORCE_FEEDBACK_CURL_PROPERTIES_MNDX) \
    _avail(XrForceFeedbackCurlApplyLocationsMNDX, XR_TYPE_FORCE_FEEDBACK_CURL_APPLY_LOCATIONS_MNDX) \
    _avail(XrSystemBodyTrackingPropertiesBD, XR_TYPE_SYSTEM_BODY_TRACKING_PROPERTIES_BD) \
    _avail(XrBodyTrackerCreateInfoBD, XR_TYPE_BODY_TRACKER_CREATE_INFO_BD) \
    _avail(XrBodyJointsLocateInfoBD, XR_TYPE_BODY_JOINTS_LOCATE_INFO_BD) \
    _avail(XrBodyJointLocationsBD, XR_TYPE_BODY_JOINT_LOCATIONS_BD) \
    _avail(XrSystemFacialSimulationPropertiesBD, XR_TYPE_SYSTEM_FACIAL_SIMULATION_PROPERTIES_BD) \
    _avail(XrFaceTrackerCreateInfoBD, XR_TYPE_FACE_TRACKER_CREATE_INFO_BD) \
    _avail(Xr_Facial_Simulation_معلومات_Get_Info_BD, XR_TYPE_FACIAL_SIMULATION_معلومات_GET_INFO_BD) \
    _avail(Xr_Facial_Simulation_معلومات_BD, XR_TYPE_FACIAL_SIMULATION_معلومات_BD) \
    _avail(Xr_Lip_افاده_معلومات_BD, XR_TYPE_LIP_افاده_معلومات_BD) \
    _avail(XrSystemSpatialSensingPropertiesBD, XR_TYPE_SYSTEM_SPATIAL_SENSING_PROPERTIES_BD) \
    _avail(XrSpatialEntityComponentGetInfoBD, XR_TYPE_SPATIAL_ENTITY_COMPONENT_GET_INFO_BD) \
    _avail(XrSpatialEntityLocationGetInfoBD, XR_TYPE_SPATIAL_ENTITY_LOCATION_GET_INFO_BD) \
    _avail(Xr_Spatial_Entity_Component_معلومات_Location_BD, XR_TYPE_SPATIAL_ENTITY_COMPONENT_معلومات_LOCATION_BD) \
    _avail(Xr_Spatial_Entity_Component_معلومات_Semantic_BD, XR_TYPE_SPATIAL_ENTITY_COMPONENT_معلومات_SEMANTIC_BD) \
    _avail(Xr_Spatial_Entity_Component_معلومات_Bounding_Box2_DBD, XR_TYPE_SPATIAL_ENTITY_COMPONENT_معلومات_BOUNDING_BOX_2_D_BD) \
    _avail(Xr_Spatial_Entity_Component_معلومات_Polygon_BD, XR_TYPE_SPATIAL_ENTITY_COMPONENT_معلومات_POLYGON_BD) \
    _avail(Xr_Spatial_Entity_Component_معلومات_Bounding_Box3_DBD, XR_TYPE_SPATIAL_ENTITY_COMPONENT_معلومات_BOUNDING_BOX_3_D_BD) \
    _avail(Xr_Spatial_Entity_Component_معلومات_Triangle_Mesh_BD, XR_TYPE_SPATIAL_ENTITY_COMPONENT_معلومات_TRIANGLE_MESH_BD) \
    _avail(Xr_Spatial_Entity_Component_معلومات_Sphere_BD, XR_TYPE_SPATIAL_ENTITY_COMPONENT_معلومات_SPHERE_BD) \
    _avail(Xr_Sense_معلومات_Provider_Create_Info_BD, XR_TYPE_SENSE_معلومات_PROVIDER_CREATE_INFO_BD) \
    _avail(Xr_Sense_معلومات_Provider_پیل_Info_BD, XR_TYPE_SENSE_معلومات_PROVIDER_پیل_INFO_BD) \
    _avail(Xr_Event_معلومات_Sense_معلومات_Provider_State_بدل_شوی_BD, XR_TYPE_EVENT_معلومات_SENSE_معلومات_PROVIDER_STATE_بدل_شوی_BD) \
    _avail(Xr_Event_معلومات_Sense_معلومات_Updated_BD, XR_TYPE_EVENT_معلومات_SENSE_معلومات_UPDATED_BD) \
    _avail(Xr_Sense_معلومات_Query_Info_BD, XR_TYPE_SENSE_معلومات_QUERY_INFO_BD) \
    _avail(Xr_Sense_معلومات_Query_Completion_BD, XR_TYPE_SENSE_معلومات_QUERY_COMPLETION_BD) \
    _avail(Xr_Queried_Sense_معلومات_Get_Info_BD, XR_TYPE_QUERIED_SENSE_معلومات_GET_INFO_BD) \
    _avail(XrSpatialEntityStateBD, XR_TYPE_SPATIAL_ENTITY_STATE_BD) \
    _avail(Xr_Queried_Sense_معلومات_BD, XR_TYPE_QUERIED_SENSE_معلومات_BD) \
    _avail(Xr_Sense_معلومات_Filter_Uuid_BD, XR_TYPE_SENSE_معلومات_FILTER_UUID_BD) \
    _avail(Xr_Sense_معلومات_Filter_Semantic_BD, XR_TYPE_SENSE_معلومات_FILTER_SEMANTIC_BD) \
    _avail(XrSpatialEntityAnchorCreateInfoBD, XR_TYPE_SPATIAL_ENTITY_ANCHOR_CREATE_INFO_BD) \
    _avail(XrAnchorSpaceCreateInfoBD, XR_TYPE_ANCHOR_SPACE_CREATE_INFO_BD) \
    _avail(XrFutureCompletionEXT, XR_TYPE_FUTURE_COMPLETION_EXT) \
    _avail(XrSystemSpatialAnchorPropertiesBD, XR_TYPE_SYSTEM_SPATIAL_ANCHOR_PROPERTIES_BD) \
    _avail(XrSpatialAnchorCreateInfoBD, XR_TYPE_SPATIAL_ANCHOR_CREATE_INFO_BD) \
    _avail(XrSpatialAnchorCreateCompletionBD, XR_TYPE_SPATIAL_ANCHOR_CREATE_COMPLETION_BD) \
    _avail(XrSpatialAnchorPersistInfoBD, XR_TYPE_SPATIAL_ANCHOR_PERSIST_INFO_BD) \
    _avail(XrSpatialAnchorUnpersistInfoBD, XR_TYPE_SPATIAL_ANCHOR_UNPERSIST_INFO_BD) \
    _avail(XrSystemSpatialAnchorSharingPropertiesBD, XR_TYPE_SYSTEM_SPATIAL_ANCHOR_SHARING_PROPERTIES_BD) \
    _avail(XrSpatialAnchorShareInfoBD, XR_TYPE_SPATIAL_ANCHOR_SHARE_INFO_BD) \
    _avail(XrSharedSpatialAnchorDownloadInfoBD, XR_TYPE_SHARED_SPATIAL_ANCHOR_DOWNLOAD_INFO_BD) \
    _avail(XrSystemSpatialScenePropertiesBD, XR_TYPE_SYSTEM_SPATIAL_SCENE_PROPERTIES_BD) \
    _avail(XrSceneCaptureInfoBD, XR_TYPE_SCENE_CAPTURE_INFO_BD) \
    _avail(XrSystemSpatialMeshPropertiesBD, XR_TYPE_SYSTEM_SPATIAL_MESH_PROPERTIES_BD) \
    _avail(Xr_Sense_معلومات_Provider_Create_Info_Spatial_Mesh_BD, XR_TYPE_SENSE_معلومات_PROVIDER_CREATE_INFO_SPATIAL_MESH_BD) \
    _avail(Xr_Future_Poll_پایله_پرمختګ_BD, XR_TYPE_FUTURE_POLL_پایله_پرمختګ_BD) \
    _avail(Xr_Body_Tracking_Posture_معلومات_BD, XR_TYPE_BODY_TRACKING_POSTURE_معلومات_BD) \
    _avail(XrBodyJointVelocitiesBD, XR_TYPE_BODY_JOINT_VELOCITIES_BD) \
    _avail(XrBodyJointAccelerationsBD, XR_TYPE_BODY_JOINT_ACCELERATIONS_BD) \
    _avail(XrBodyTrackingStateBD, XR_TYPE_BODY_TRACKING_STATE_BD) \
    _avail(XrSystemSpatialPlanePropertiesBD, XR_TYPE_SYSTEM_SPATIAL_PLANE_PROPERTIES_BD) \
    _avail(Xr_Spatial_Entity_Component_معلومات_Plane_Orientation_BD, XR_TYPE_SPATIAL_ENTITY_COMPONENT_معلومات_PLANE_ORIENTATION_BD) \
    _avail(Xr_Sense_معلومات_Filter_Plane_Orientation_BD, XR_TYPE_SENSE_معلومات_FILTER_PLANE_ORIENTATION_BD) \
    _avail(XrSystemLightEstimationPropertiesBD, XR_TYPE_SYSTEM_LIGHT_ESTIMATION_PROPERTIES_BD) \
    _avail(Xr_Sense_معلومات_Provider_Create_Info_Light_Estimation_BD, XR_TYPE_SENSE_معلومات_PROVIDER_CREATE_INFO_LIGHT_ESTIMATION_BD) \
    _avail(XrEnvironmentTextureCreateConfigInfoBD, XR_TYPE_ENVIRONMENT_TEXTURE_CREATE_CONFIG_INFO_BD) \
    _avail(Xr_Light_Estimation_معلومات_Environment_Texture_Raw_BD, XR_TYPE_LIGHT_ESTIMATION_معلومات_ENVIRONMENT_TEXTURE_RAW_BD) \
    _avail(Xr_Light_Estimation_معلومات_Spherical_Harmonics_BD, XR_TYPE_LIGHT_ESTIMATION_معلومات_SPHERICAL_HARMONICS_BD) \
    _avail(Xr_Spatial_Entity_Component_معلومات_Light_Estimation_BD, XR_TYPE_SPATIAL_ENTITY_COMPONENT_معلومات_LIGHT_ESTIMATION_BD) \
    _avail(XrSpatialAudioRendererCreateInfoBD, XR_TYPE_SPATIAL_AUDIO_RENDERER_CREATE_INFO_BD) \
    _avail(Xr_Audio_بفر_BD, XR_TYPE_AUDIO_بفر_BD) \
    _avail(XrSoundObjectDirectivityCardioidBD, XR_TYPE_SOUND_OBJECT_DIRECTIVITY_CARDIOID_BD) \
    _avail(XrSoundObjectShapeSphereBD, XR_TYPE_SOUND_OBJECT_SHAPE_SPHERE_BD) \
    _avail(Xr_Sound_Object_واټن_Attenuation_منحني_BD, XR_TYPE_SOUND_OBJECT_واټن_ATTENUATION_منحني_BD) \
    _avail(Xr_Sound_Object_واټن_Attenuation_BD, XR_TYPE_SOUND_OBJECT_واټن_ATTENUATION_BD) \
    _avail(XrSoundObjectConfigBD, XR_TYPE_SOUND_OBJECT_CONFIG_BD) \
    _avail(Xr_Sound_ډګر_Config_BD, XR_TYPE_SOUND_ډګر_CONFIG_BD) \
    _avail(Xr_Sound_ډګر_Channel_Definition_Surround_BD, XR_TYPE_SOUND_ډګر_CHANNEL_DEFINITION_SURROUND_BD) \
    _avail(Xr_Sound_ډګر_Channel_Definition_Ambix_BD, XR_TYPE_SOUND_ډګر_CHANNEL_DEFINITION_AMBIX_BD) \
    _avail(Xr_Sound_ډګر_Channel_Definition_Fuma_BD, XR_TYPE_SOUND_ډګر_CHANNEL_DEFINITION_FUMA_BD) \
    _avail(XrSoundTriangleMeshBD, XR_TYPE_SOUND_TRIANGLE_MESH_BD) \
    _avail(XrSoundObstacleConfigBD, XR_TYPE_SOUND_OBSTACLE_CONFIG_BD) \
    _avail(XrSoundObstacleMaterialConfigBD, XR_TYPE_SOUND_OBSTACLE_MATERIAL_CONFIG_BD) \
    _avail(Xr_Hand_Tracking_معلومات_سرچینه_Info_EXT, XR_TYPE_HAND_TRACKING_معلومات_سرچینه_INFO_EXT) \
    _avail(Xr_Hand_Tracking_معلومات_سرچینه_State_EXT, XR_TYPE_HAND_TRACKING_معلومات_سرچینه_STATE_EXT) \
    _avail(XrSystemPlaneDetectionPropertiesEXT, XR_TYPE_SYSTEM_PLANE_DETECTION_PROPERTIES_EXT) \
    _avail(XrPlaneDetectorCreateInfoEXT, XR_TYPE_PLANE_DETECTOR_CREATE_INFO_EXT) \
    _avail(XrPlaneDetectorBeginInfoEXT, XR_TYPE_PLANE_DETECTOR_BEGIN_INFO_EXT) \
    _avail(XrPlaneDetectorGetInfoEXT, XR_TYPE_PLANE_DETECTOR_GET_INFO_EXT) \
    _avail(XrPlaneDetectorLocationEXT, XR_TYPE_PLANE_DETECTOR_LOCATION_EXT) \
    _avail(XrPlaneDetectorLocationsEXT, XR_TYPE_PLANE_DETECTOR_LOCATIONS_EXT) \
    _avail(Xr_Plane_Detector_Polygon_بفر_EXT, XR_TYPE_PLANE_DETECTOR_POLYGON_بفر_EXT) \
    _avail(XrTrackableTrackerCreateInfoANDROID, XR_TYPE_TRACKABLE_TRACKER_CREATE_INFO_ANDROID) \
    _avail(XrTrackableGetInfoANDROID, XR_TYPE_TRACKABLE_GET_INFO_ANDROID) \
    _avail(XrTrackablePlaneANDROID, XR_TYPE_TRACKABLE_PLANE_ANDROID) \
    _avail(XrAnchorSpaceCreateInfoANDROID, XR_TYPE_ANCHOR_SPACE_CREATE_INFO_ANDROID) \
    _avail(XrSystemTrackablesPropertiesANDROID, XR_TYPE_SYSTEM_TRACKABLES_PROPERTIES_ANDROID) \
    _avail(XrSystemEyeTrackingPropertiesANDROID, XR_TYPE_SYSTEM_EYE_TRACKING_PROPERTIES_ANDROID) \
    _avail(XrEyesANDROID, XR_TYPE_EYES_ANDROID) \
    _avail(XrEyesGetInfoANDROID, XR_TYPE_EYES_GET_INFO_ANDROID) \
    _avail(XrEyeTrackerCreateInfoANDROID, XR_TYPE_EYE_TRACKER_CREATE_INFO_ANDROID) \
    _avail(XrDeviceAnchorPersistenceCreateInfoANDROID, XR_TYPE_DEVICE_ANCHOR_PERSISTENCE_CREATE_INFO_ANDROID) \
    _avail(XrPersistedAnchorSpaceCreateInfoANDROID, XR_TYPE_PERSISTED_ANCHOR_SPACE_CREATE_INFO_ANDROID) \
    _avail(XrPersistedAnchorSpaceInfoANDROID, XR_TYPE_PERSISTED_ANCHOR_SPACE_INFO_ANDROID) \
    _avail(XrSystemDeviceAnchorPersistencePropertiesANDROID, XR_TYPE_SYSTEM_DEVICE_ANCHOR_PERSISTENCE_PROPERTIES_ANDROID) \
    _avail(XrFaceTrackerCreateInfoANDROID, XR_TYPE_FACE_TRACKER_CREATE_INFO_ANDROID) \
    _avail(XrFaceStateGetInfoANDROID, XR_TYPE_FACE_STATE_GET_INFO_ANDROID) \
    _avail(XrFaceStateANDROID, XR_TYPE_FACE_STATE_ANDROID) \
    _avail(XrSystemFaceTrackingPropertiesANDROID, XR_TYPE_SYSTEM_FACE_TRACKING_PROPERTIES_ANDROID) \
    _avail(XrSystemPassthroughCameraStatePropertiesANDROID, XR_TYPE_SYSTEM_PASSTHROUGH_CAMERA_STATE_PROPERTIES_ANDROID) \
    _avail(XrPassthroughCameraStateGetInfoANDROID, XR_TYPE_PASSTHROUGH_CAMERA_STATE_GET_INFO_ANDROID) \
    _avail(Xr_Event_معلومات_Recommended_Resolution_بدل_شوی_ANDROID, XR_TYPE_EVENT_معلومات_RECOMMENDED_RESOLUTION_بدل_شوی_ANDROID) \
    _avail(XrPassthroughLayerCreateInfoANDROID, XR_TYPE_PASSTHROUGH_LAYER_CREATE_INFO_ANDROID) \
    _avail(XrPassthroughLayerMeshANDROID, XR_TYPE_PASSTHROUGH_LAYER_MESH_ANDROID) \
    _avail(XrCompositionLayerPassthroughANDROID, XR_TYPE_COMPOSITION_LAYER_PASSTHROUGH_ANDROID) \
    _avail(XrSystemPassthroughLayerPropertiesANDROID, XR_TYPE_SYSTEM_PASSTHROUGH_LAYER_PROPERTIES_ANDROID) \
    _avail(XrRaycastInfoANDROID, XR_TYPE_RAYCAST_INFO_ANDROID) \
    _avail(Xr_Raycast_موندنه_Results_ANDROID, XR_TYPE_RAYCAST_موندنه_RESULTS_ANDROID) \
    _avail(XrPerformanceMetricsStateANDROID, XR_TYPE_PERFORMANCE_METRICS_STATE_ANDROID) \
    _avail(XrPerformanceMetricsCounterANDROID, XR_TYPE_PERFORMANCE_METRICS_COUNTER_ANDROID) \
    _avail(XrTrackableObjectANDROID, XR_TYPE_TRACKABLE_OBJECT_ANDROID) \
    _avail(XrTrackableObjectConfigurationANDROID, XR_TYPE_TRACKABLE_OBJECT_CONFIGURATION_ANDROID) \
    _avail(XrFutureCancelInfoEXT, XR_TYPE_FUTURE_CANCEL_INFO_EXT) \
    _avail(XrFuturePollInfoEXT, XR_TYPE_FUTURE_POLL_INFO_EXT) \
    _avail(Xr_Future_Poll_پایله_EXT, XR_TYPE_FUTURE_POLL_پایله_EXT) \
    _avail(Xr_Event_معلومات_User_Presence_بدل_شوی_EXT, XR_TYPE_EVENT_معلومات_USER_PRESENCE_بدل_شوی_EXT) \
    _avail(XrSystemUserPresencePropertiesEXT, XR_TYPE_SYSTEM_USER_PRESENCE_PROPERTIES_EXT) \
    _avail(Xr_Event_معلومات_Headset_Fit_بدل_شوی_ML, XR_TYPE_EVENT_معلومات_HEADSET_FIT_بدل_شوی_ML) \
    _avail(Xr_Event_معلومات_Eye_Calibration_بدل_شوی_ML, XR_TYPE_EVENT_معلومات_EYE_CALIBRATION_بدل_شوی_ML) \
    _avail(XrUserCalibrationEnableEventsInfoML, XR_TYPE_USER_CALIBRATION_ENABLE_EVENTS_INFO_ML) \
    _avail(Xr_System_Notifications_سېټ_Info_ML, XR_TYPE_SYSTEM_NOTIFICATIONS_سېټ_INFO_ML) \
    _avail(XrWorldMeshDetectorCreateInfoML, XR_TYPE_WORLD_MESH_DETECTOR_CREATE_INFO_ML) \
    _avail(Xr_World_Mesh_بلاک_State_ML, XR_TYPE_WORLD_MESH_بلاک_STATE_ML) \
    _avail(XrWorldMeshStateRequestInfoML, XR_TYPE_WORLD_MESH_STATE_REQUEST_INFO_ML) \
    _avail(XrWorldMeshStateRequestCompletionML, XR_TYPE_WORLD_MESH_STATE_REQUEST_COMPLETION_ML) \
    _avail(Xr_World_Mesh_بفر_Recommended_اندازه_Info_ML, XR_TYPE_WORLD_MESH_بفر_RECOMMENDED_اندازه_INFO_ML) \
    _avail(Xr_World_Mesh_بفر_اندازه_ML, XR_TYPE_WORLD_MESH_بفر_اندازه_ML) \
    _avail(Xr_World_Mesh_بفر_ML, XR_TYPE_WORLD_MESH_بفر_ML) \
    _avail(Xr_World_Mesh_بلاک_Request_ML, XR_TYPE_WORLD_MESH_بلاک_REQUEST_ML) \
    _avail(XrWorldMeshGetInfoML, XR_TYPE_WORLD_MESH_GET_INFO_ML) \
    _avail(Xr_World_Mesh_بلاک_ML, XR_TYPE_WORLD_MESH_بلاک_ML) \
    _avail(XrWorldMeshRequestCompletionInfoML, XR_TYPE_WORLD_MESH_REQUEST_COMPLETION_INFO_ML) \
    _avail(XrWorldMeshRequestCompletionML, XR_TYPE_WORLD_MESH_REQUEST_COMPLETION_ML) \
    _avail(Xr_System_Facial_افاده_Properties_ML, XR_TYPE_SYSTEM_FACIAL_افاده_PROPERTIES_ML) \
    _avail(Xr_Facial_افاده_Client_Create_Info_ML, XR_TYPE_FACIAL_افاده_CLIENT_CREATE_INFO_ML) \
    _avail(Xr_Facial_افاده_Blend_Shape_Get_Info_ML, XR_TYPE_FACIAL_افاده_BLEND_SHAPE_GET_INFO_ML) \
    _avail(Xr_Facial_افاده_Blend_Shape_Properties_ML, XR_TYPE_FACIAL_افاده_BLEND_SHAPE_PROPERTIES_ML) \
    _avail(XrSystemBoundaryVisibilityPropertiesMETA, XR_TYPE_SYSTEM_BOUNDARY_VISIBILITY_PROPERTIES_META) \
    _avail(Xr_Event_معلومات_Boundary_Visibility_بدل_شوی_META, XR_TYPE_EVENT_معلومات_BOUNDARY_VISIBILITY_بدل_شوی_META) \
    _avail(Xr_System_همزمانه_Hands_And_Controllers_Properties_META, XR_TYPE_SYSTEM_همزمانه_HANDS_AND_CONTROLLERS_PROPERTIES_META) \
    _avail(Xr_همزمانه_Hands_And_Controllers_Tracking_Resume_Info_META, XR_TYPE_همزمانه_HANDS_AND_CONTROLLERS_TRACKING_RESUME_INFO_META) \
    _avail(Xr_همزمانه_Hands_And_Controllers_Tracking_Pause_Info_META, XR_TYPE_همزمانه_HANDS_AND_CONTROLLERS_TRACKING_PAUSE_INFO_META) \
    _avail(XrFaceTrackingVisemesMETA, XR_TYPE_FACE_TRACKING_VISEMES_META) \
    _avail(XrSystemFaceTrackingVisemesPropertiesMETA, XR_TYPE_SYSTEM_FACE_TRACKING_VISEMES_PROPERTIES_META) \
    _avail(Xr_ځای_Mesh_Face_Indices_META, XR_TYPE_ځای_MESH_FACE_INDICES_META) \
    _avail(Xr_Space_ځای_Mesh_Get_Info_META, XR_TYPE_SPACE_ځای_MESH_GET_INFO_META) \
    _avail(Xr_ځای_Mesh_META, XR_TYPE_ځای_MESH_META) \
    _avail(Xr_Colocation_Discovery_پیل_Info_META, XR_TYPE_COLOCATION_DISCOVERY_پیل_INFO_META) \
    _avail(XrColocationDiscoveryStopInfoMETA, XR_TYPE_COLOCATION_DISCOVERY_STOP_INFO_META) \
    _avail(Xr_Colocation_Advertisement_پیل_Info_META, XR_TYPE_COLOCATION_ADVERTISEMENT_پیل_INFO_META) \
    _avail(XrColocationAdvertisementStopInfoMETA, XR_TYPE_COLOCATION_ADVERTISEMENT_STOP_INFO_META) \
    _avail(Xr_Event_معلومات_پیل_Colocation_Advertisement_Complete_META, XR_TYPE_EVENT_معلومات_پیل_COLOCATION_ADVERTISEMENT_COMPLETE_META) \
    _avail(Xr_Event_معلومات_Stop_Colocation_Advertisement_Complete_META, XR_TYPE_EVENT_معلومات_STOP_COLOCATION_ADVERTISEMENT_COMPLETE_META) \
    _avail(Xr_Event_معلومات_Colocation_Advertisement_Complete_META, XR_TYPE_EVENT_معلومات_COLOCATION_ADVERTISEMENT_COMPLETE_META) \
    _avail(Xr_Event_معلومات_پیل_Colocation_Discovery_Complete_META, XR_TYPE_EVENT_معلومات_پیل_COLOCATION_DISCOVERY_COMPLETE_META) \
    _avail(Xr_Event_معلومات_Colocation_Discovery_پایله_META, XR_TYPE_EVENT_معلومات_COLOCATION_DISCOVERY_پایله_META) \
    _avail(Xr_Event_معلومات_Colocation_Discovery_Complete_META, XR_TYPE_EVENT_معلومات_COLOCATION_DISCOVERY_COMPLETE_META) \
    _avail(Xr_Event_معلومات_Stop_Colocation_Discovery_Complete_META, XR_TYPE_EVENT_معلومات_STOP_COLOCATION_DISCOVERY_COMPLETE_META) \
    _avail(XrSystemColocationDiscoveryPropertiesMETA, XR_TYPE_SYSTEM_COLOCATION_DISCOVERY_PROPERTIES_META) \
    _avail(Xr_System_Spatial_Entity_ډله_Sharing_Properties_META, XR_TYPE_SYSTEM_SPATIAL_ENTITY_ډله_SHARING_PROPERTIES_META) \
    _avail(XrShareSpacesRecipientGroupsMETA, XR_TYPE_SHARE_SPACES_RECIPIENT_GROUPS_META) \
    _avail(Xr_Space_ډله_Uuid_Filter_Info_META, XR_TYPE_SPACE_ډله_UUID_FILTER_INFO_META) \
    _avail(XrSystemEnvironmentRaycastPropertiesMETA, XR_TYPE_SYSTEM_ENVIRONMENT_RAYCAST_PROPERTIES_META) \
    _avail(XrEnvironmentRaycasterCreateInfoMETA, XR_TYPE_ENVIRONMENT_RAYCASTER_CREATE_INFO_META) \
    _avail(XrEnvironmentRaycasterCreateCompletionMETA, XR_TYPE_ENVIRONMENT_RAYCASTER_CREATE_COMPLETION_META) \
    _avail(Xr_Environment_Raycast_موندنه_Get_Info_META, XR_TYPE_ENVIRONMENT_RAYCAST_موندنه_GET_INFO_META) \
    _avail(Xr_Environment_Raycast_موندنه_META, XR_TYPE_ENVIRONMENT_RAYCAST_موندنه_META) \
    _avail(Xr_Environment_Raycast_Filter_واټن_META, XR_TYPE_ENVIRONMENT_RAYCAST_FILTER_واټن_META) \
    _avail(XrTilePropertiesMETA, XR_TYPE_TILE_PROPERTIES_META) \
    _avail(XrTilePropertiesHintMETA, XR_TYPE_TILE_PROPERTIES_HINT_META) \
    _avail(XrHandTrackingUnextrapolatedPosesRequestMETA, XR_TYPE_HAND_TRACKING_UNEXTRAPOLATED_POSES_REQUEST_META) \
    _avail(XrHandTrackingUnextrapolatedPosesMETA, XR_TYPE_HAND_TRACKING_UNEXTRAPOLATED_POSES_META) \
    _avail(XrSystemLightEstimationPropertiesANDROID, XR_TYPE_SYSTEM_LIGHT_ESTIMATION_PROPERTIES_ANDROID) \
    _avail(XrLightEstimatorCreateInfoANDROID, XR_TYPE_LIGHT_ESTIMATOR_CREATE_INFO_ANDROID) \
    _avail(XrLightEstimateGetInfoANDROID, XR_TYPE_LIGHT_ESTIMATE_GET_INFO_ANDROID) \
    _avail(XrLightEstimateANDROID, XR_TYPE_LIGHT_ESTIMATE_ANDROID) \
    _avail(XrDirectionalLightANDROID, XR_TYPE_DIRECTIONAL_LIGHT_ANDROID) \
    _avail(XrAmbientLightANDROID, XR_TYPE_AMBIENT_LIGHT_ANDROID) \
    _avail(XrSphericalHarmonicsANDROID, XR_TYPE_SPHERICAL_HARMONICS_ANDROID) \
    _avail(XrSystemMarkerTrackingPropertiesANDROID, XR_TYPE_SYSTEM_MARKER_TRACKING_PROPERTIES_ANDROID) \
    _avail(XrTrackableMarkerConfigurationANDROID, XR_TYPE_TRACKABLE_MARKER_CONFIGURATION_ANDROID) \
    _avail(XrTrackableMarkerANDROID, XR_TYPE_TRACKABLE_MARKER_ANDROID) \
    _avail(Xr_System_Qr_کوډ_Tracking_Properties_ANDROID, XR_TYPE_SYSTEM_QR_کوډ_TRACKING_PROPERTIES_ANDROID) \
    _avail(Xr_Trackable_Qr_کوډ_Configuration_ANDROID, XR_TYPE_TRACKABLE_QR_کوډ_CONFIGURATION_ANDROID) \
    _avail(Xr_Trackable_Qr_کوډ_ANDROID, XR_TYPE_TRACKABLE_QR_کوډ_ANDROID) \
    _avail(XrSystemImageTrackingPropertiesANDROID, XR_TYPE_SYSTEM_IMAGE_TRACKING_PROPERTIES_ANDROID) \
    _avail(Xr_Trackable_Image_Database_ثبت_ANDROID, XR_TYPE_TRACKABLE_IMAGE_DATABASE_ثبت_ANDROID) \
    _avail(XrTrackableImageDatabaseCreateInfoANDROID, XR_TYPE_TRACKABLE_IMAGE_DATABASE_CREATE_INFO_ANDROID) \
    _avail(XrCreateTrackableImageDatabaseCompletionANDROID, XR_TYPE_CREATE_TRACKABLE_IMAGE_DATABASE_COMPLETION_ANDROID) \
    _avail(XrTrackableImageConfigurationANDROID, XR_TYPE_TRACKABLE_IMAGE_CONFIGURATION_ANDROID) \
    _avail(XrTrackableImageANDROID, XR_TYPE_TRACKABLE_IMAGE_ANDROID) \
    _avail(Xr_Event_معلومات_Image_Tracking_ورک_ANDROID, XR_TYPE_EVENT_معلومات_IMAGE_TRACKING_ورک_ANDROID) \
    _avail(XrSystemSceneMeshingPropertiesANDROID, XR_TYPE_SYSTEM_SCENE_MESHING_PROPERTIES_ANDROID) \
    _avail(XrSceneMeshingTrackerCreateInfoANDROID, XR_TYPE_SCENE_MESHING_TRACKER_CREATE_INFO_ANDROID) \
    _avail(XrSceneMeshSnapshotCreateInfoANDROID, XR_TYPE_SCENE_MESH_SNAPSHOT_CREATE_INFO_ANDROID) \
    _avail(Xr_Scene_Mesh_Snapshot_Creation_پایله_ANDROID, XR_TYPE_SCENE_MESH_SNAPSHOT_CREATION_پایله_ANDROID) \
    _avail(XrSceneSubmeshStateANDROID, XR_TYPE_SCENE_SUBMESH_STATE_ANDROID) \
    _avail(Xr_Scene_Submesh_معلومات_ANDROID, XR_TYPE_SCENE_SUBMESH_معلومات_ANDROID) \
    _avail(XrSpatialCapabilityComponentTypesEXT, XR_TYPE_SPATIAL_CAPABILITY_COMPONENT_TYPES_EXT) \
    _avail(XrSpatialContextCreateInfoEXT, XR_TYPE_SPATIAL_CONTEXT_CREATE_INFO_EXT) \
    _avail(XrCreateSpatialContextCompletionEXT, XR_TYPE_CREATE_SPATIAL_CONTEXT_COMPLETION_EXT) \
    _avail(XrSpatialDiscoverySnapshotCreateInfoEXT, XR_TYPE_SPATIAL_DISCOVERY_SNAPSHOT_CREATE_INFO_EXT) \
    _avail(XrCreateSpatialDiscoverySnapshotCompletionInfoEXT, XR_TYPE_CREATE_SPATIAL_DISCOVERY_SNAPSHOT_COMPLETION_INFO_EXT) \
    _avail(XrCreateSpatialDiscoverySnapshotCompletionEXT, XR_TYPE_CREATE_SPATIAL_DISCOVERY_SNAPSHOT_COMPLETION_EXT) \
    _avail(Xr_Spatial_Component_معلومات_Query_Condition_EXT, XR_TYPE_SPATIAL_COMPONENT_معلومات_QUERY_CONDITION_EXT) \
    _avail(Xr_Spatial_Component_معلومات_Query_پایله_EXT, XR_TYPE_SPATIAL_COMPONENT_معلومات_QUERY_پایله_EXT) \
    _avail(Xr_Spatial_بفر_Get_Info_EXT, XR_TYPE_SPATIAL_بفر_GET_INFO_EXT) \
    _avail(XrSpatialComponentBounded2DListEXT, XR_TYPE_SPATIAL_COMPONENT_BOUNDED_2D_LIST_EXT) \
    _avail(XrSpatialComponentBounded3DListEXT, XR_TYPE_SPATIAL_COMPONENT_BOUNDED_3D_LIST_EXT) \
    _avail(Xr_Spatial_Component_پلار_List_EXT, XR_TYPE_SPATIAL_COMPONENT_پلار_LIST_EXT) \
    _avail(XrSpatialComponentMesh3DListEXT, XR_TYPE_SPATIAL_COMPONENT_MESH_3D_LIST_EXT) \
    _avail(XrSpatialEntityFromIdCreateInfoEXT, XR_TYPE_SPATIAL_ENTITY_FROM_ID_CREATE_INFO_EXT) \
    _avail(XrSpatialUpdateSnapshotCreateInfoEXT, XR_TYPE_SPATIAL_UPDATE_SNAPSHOT_CREATE_INFO_EXT) \
    _avail(Xr_Event_معلومات_Spatial_Discovery_Recommended_EXT, XR_TYPE_EVENT_معلومات_SPATIAL_DISCOVERY_RECOMMENDED_EXT) \
    _avail(XrSpatialFilterTrackingStateEXT, XR_TYPE_SPATIAL_FILTER_TRACKING_STATE_EXT) \
    _avail(XrSpatialCapabilityConfigurationPlaneTrackingEXT, XR_TYPE_SPATIAL_CAPABILITY_CONFIGURATION_PLANE_TRACKING_EXT) \
    _avail(XrSpatialComponentPlaneAlignmentListEXT, XR_TYPE_SPATIAL_COMPONENT_PLANE_ALIGNMENT_LIST_EXT) \
    _avail(XrSpatialComponentMesh2DListEXT, XR_TYPE_SPATIAL_COMPONENT_MESH_2D_LIST_EXT) \
    _avail(XrSpatialComponentPolygon2DListEXT, XR_TYPE_SPATIAL_COMPONENT_POLYGON_2D_LIST_EXT) \
    _avail(XrSpatialComponentPlaneSemanticLabelListEXT, XR_TYPE_SPATIAL_COMPONENT_PLANE_SEMANTIC_LABEL_LIST_EXT) \
    _avail(XrStationaryReferenceSpaceGenerationIdGetInfoEXT, XR_TYPE_STATIONARY_REFERENCE_SPACE_GENERATION_ID_GET_INFO_EXT) \
    _avail(Xr_Stationary_Reference_Space_Generation_Id_پایله_EXT, XR_TYPE_STATIONARY_REFERENCE_SPACE_GENERATION_ID_پایله_EXT) \
    _avail(Xr_Spatial_Capability_Configuration_Qr_کوډ_EXT, XR_TYPE_SPATIAL_CAPABILITY_CONFIGURATION_QR_کوډ_EXT) \
    _avail(Xr_Spatial_Capability_Configuration_Micro_Qr_کوډ_EXT, XR_TYPE_SPATIAL_CAPABILITY_CONFIGURATION_MICRO_QR_کوډ_EXT) \
    _avail(XrSpatialCapabilityConfigurationArucoMarkerEXT, XR_TYPE_SPATIAL_CAPABILITY_CONFIGURATION_ARUCO_MARKER_EXT) \
    _avail(Xr_Spatial_Capability_Configuration_April_نښان_EXT, XR_TYPE_SPATIAL_CAPABILITY_CONFIGURATION_APRIL_نښان_EXT) \
    _avail(Xr_Spatial_Marker_اندازه_EXT, XR_TYPE_SPATIAL_MARKER_اندازه_EXT) \
    _avail(XrSpatialMarkerStaticOptimizationEXT, XR_TYPE_SPATIAL_MARKER_STATIC_OPTIMIZATION_EXT) \
    _avail(XrSpatialComponentMarkerListEXT, XR_TYPE_SPATIAL_COMPONENT_MARKER_LIST_EXT) \
    _avail(XrSpatialCapabilityConfigurationObjectTrackingEXT, XR_TYPE_SPATIAL_CAPABILITY_CONFIGURATION_OBJECT_TRACKING_EXT) \
    _avail(XrSpatialComponentObjectSemanticLabelListEXT, XR_TYPE_SPATIAL_COMPONENT_OBJECT_SEMANTIC_LABEL_LIST_EXT) \
    _avail(XrSpatialFeatureObjectSemanticLabelSubsetEXT, XR_TYPE_SPATIAL_FEATURE_OBJECT_SEMANTIC_LABEL_SUBSET_EXT) \
    _avail(XrSpatialComponentKeyboardSemanticLabelListEXT, XR_TYPE_SPATIAL_COMPONENT_KEYBOARD_SEMANTIC_LABEL_LIST_EXT) \
    _avail(XrSpatialComponentMouseSemanticLabelListEXT, XR_TYPE_SPATIAL_COMPONENT_MOUSE_SEMANTIC_LABEL_LIST_EXT) \
    _avail(XrSystemDynamicObjectTrackingPropertiesBD, XR_TYPE_SYSTEM_DYNAMIC_OBJECT_TRACKING_PROPERTIES_BD) \
    _avail(Xr_Sense_معلومات_Provider_Create_Info_Dynamic_Object_BD, XR_TYPE_SENSE_معلومات_PROVIDER_CREATE_INFO_DYNAMIC_OBJECT_BD) \
    _avail(Xr_Dynamic_Object_معلومات_BD, XR_TYPE_DYNAMIC_OBJECT_معلومات_BD) \
    _avail(Xr_Spatial_Entity_Component_معلومات_Dynamic_Object_BD, XR_TYPE_SPATIAL_ENTITY_COMPONENT_معلومات_DYNAMIC_OBJECT_BD) \
    _avail(Xr_Sense_معلومات_Filter_Dynamic_Object_Type_BD, XR_TYPE_SENSE_معلومات_FILTER_DYNAMIC_OBJECT_TYPE_BD) \
    _avail(XrSystemDynamicObjectKeyboardPropertiesBD, XR_TYPE_SYSTEM_DYNAMIC_OBJECT_KEYBOARD_PROPERTIES_BD) \
    _avail(XrSystemDynamicObjectMousePropertiesBD, XR_TYPE_SYSTEM_DYNAMIC_OBJECT_MOUSE_PROPERTIES_BD) \
    _avail(XrCameraPropertiesBD, XR_TYPE_CAMERA_PROPERTIES_BD) \
    _avail(XrCameraCapabilitiesBD, XR_TYPE_CAMERA_CAPABILITIES_BD) \
    _avail(Xr_شته_Cameras_Enumerate_Info_BD, XR_TYPE_شته_CAMERAS_ENUMERATE_INFO_BD) \
    _avail(Xr_شته_Camera_BD, XR_TYPE_شته_CAMERA_BD) \
    _avail(XrCameraPropertyTypesEnumerateInfoBD, XR_TYPE_CAMERA_PROPERTY_TYPES_ENUMERATE_INFO_BD) \
    _avail(XrCameraPropertyTypesBD, XR_TYPE_CAMERA_PROPERTY_TYPES_BD) \
    _avail(XrCameraPropertiesGetInfoBD, XR_TYPE_CAMERA_PROPERTIES_GET_INFO_BD) \
    _avail(XrCameraPropertyFacingBD, XR_TYPE_CAMERA_PROPERTY_FACING_BD) \
    _avail(XrCameraPropertyPositionBD, XR_TYPE_CAMERA_PROPERTY_POSITION_BD) \
    _avail(XrCameraPropertyCameraTypeBD, XR_TYPE_CAMERA_PROPERTY_CAMERA_TYPE_BD) \
    _avail(XrCameraCapabilityTypesEnumerateInfoBD, XR_TYPE_CAMERA_CAPABILITY_TYPES_ENUMERATE_INFO_BD) \
    _avail(XrCameraCapabilityTypesBD, XR_TYPE_CAMERA_CAPABILITY_TYPES_BD) \
    _avail(XrCameraSupportedCapabilitiesGetInfoBD, XR_TYPE_CAMERA_SUPPORTED_CAPABILITIES_GET_INFO_BD) \
    _avail(XrCameraSupportedCapabilitiesBD, XR_TYPE_CAMERA_SUPPORTED_CAPABILITIES_BD) \
    _avail(Xr_Camera_Supported_Capability_Image_Resolution_And_چوکاټ_شرح_BD, XR_TYPE_CAMERA_SUPPORTED_CAPABILITY_IMAGE_RESOLUTION_AND_چوکاټ_شرح_BD) \
    _avail(Xr_Camera_Capability_Image_Resolution_And_چوکاټ_شرح_BD, XR_TYPE_CAMERA_CAPABILITY_IMAGE_RESOLUTION_AND_چوکاټ_شرح_BD) \
    _avail(Xr_Camera_Supported_Capability_معلومات_Transfer_Type_BD, XR_TYPE_CAMERA_SUPPORTED_CAPABILITY_معلومات_TRANSFER_TYPE_BD) \
    _avail(Xr_Camera_Capability_معلومات_Transfer_Type_BD, XR_TYPE_CAMERA_CAPABILITY_معلومات_TRANSFER_TYPE_BD) \
    _avail(XrCameraSupportedCapabilityImageFormatBD, XR_TYPE_CAMERA_SUPPORTED_CAPABILITY_IMAGE_FORMAT_BD) \
    _avail(XrCameraCapabilityImageFormatBD, XR_TYPE_CAMERA_CAPABILITY_IMAGE_FORMAT_BD) \
    _avail(XrCameraSupportedCapabilityCameraModelBD, XR_TYPE_CAMERA_SUPPORTED_CAPABILITY_CAMERA_MODEL_BD) \
    _avail(XrCameraCapabilityCameraModelBD, XR_TYPE_CAMERA_CAPABILITY_CAMERA_MODEL_BD) \
    _avail(XrCameraDeviceCreateInfoBD, XR_TYPE_CAMERA_DEVICE_CREATE_INFO_BD) \
    _avail(XrCreateCameraDeviceCompletionBD, XR_TYPE_CREATE_CAMERA_DEVICE_COMPLETION_BD) \
    _avail(XrCameraCaptureSessionCreateInfoBD, XR_TYPE_CAMERA_CAPTURE_SESSION_CREATE_INFO_BD) \
    _avail(XrCreateCameraCaptureSessionCompletionBD, XR_TYPE_CREATE_CAMERA_CAPTURE_SESSION_COMPLETION_BD) \
    _avail(XrCameraIntrinsicsBD, XR_TYPE_CAMERA_INTRINSICS_BD) \
    _avail(XrCameraExtrinsicsBD, XR_TYPE_CAMERA_EXTRINSICS_BD) \
    _avail(XrCameraCaptureBeginInfoBD, XR_TYPE_CAMERA_CAPTURE_BEGIN_INFO_BD) \
    _avail(XrCameraImageAcquireInfoBD, XR_TYPE_CAMERA_IMAGE_ACQUIRE_INFO_BD) \
    _avail(XrCameraImageBD, XR_TYPE_CAMERA_IMAGE_BD) \
    _avail(Xr_Camera_Image_معلومات_Raw_بفر_BD, XR_TYPE_CAMERA_IMAGE_معلومات_RAW_بفر_BD) \
    _avail(XrSpatialBoundsSpherefANDROID, XR_TYPE_SPATIAL_BOUNDS_SPHEREF_ANDROID) \
    _avail(XrSpatialBoundsBoxfANDROID, XR_TYPE_SPATIAL_BOUNDS_BOXF_ANDROID) \
    _avail(XrSpatialBoundsFrustumfANDROID, XR_TYPE_SPATIAL_BOUNDS_FRUSTUMF_ANDROID) \
    _avail(XrSpatialCapabilityConfigurationAnchorEXT, XR_TYPE_SPATIAL_CAPABILITY_CONFIGURATION_ANCHOR_EXT) \
    _avail(XrSpatialComponentAnchorListEXT, XR_TYPE_SPATIAL_COMPONENT_ANCHOR_LIST_EXT) \
    _avail(XrSpatialAnchorCreateInfoEXT, XR_TYPE_SPATIAL_ANCHOR_CREATE_INFO_EXT) \
    _avail(XrSpatialPersistenceContextCreateInfoEXT, XR_TYPE_SPATIAL_PERSISTENCE_CONTEXT_CREATE_INFO_EXT) \
    _avail(XrCreateSpatialPersistenceContextCompletionEXT, XR_TYPE_CREATE_SPATIAL_PERSISTENCE_CONTEXT_COMPLETION_EXT) \
    _avail(XrSpatialContextPersistenceConfigEXT, XR_TYPE_SPATIAL_CONTEXT_PERSISTENCE_CONFIG_EXT) \
    _avail(XrSpatialDiscoveryPersistenceUuidFilterEXT, XR_TYPE_SPATIAL_DISCOVERY_PERSISTENCE_UUID_FILTER_EXT) \
    _avail(XrSpatialComponentPersistenceListEXT, XR_TYPE_SPATIAL_COMPONENT_PERSISTENCE_LIST_EXT) \
    _avail(XrHapticParametricPropertiesEXT, XR_TYPE_HAPTIC_PARAMETRIC_PROPERTIES_EXT) \
    _avail(XrHapticParametricVibrationEXT, XR_TYPE_HAPTIC_PARAMETRIC_VIBRATION_EXT) \
    _avail(XrSystemHapticParametricPropertiesEXT, XR_TYPE_SYSTEM_HAPTIC_PARAMETRIC_PROPERTIES_EXT) \
    _avail(XrColorSpacesEnumerateInfoSONY, XR_TYPE_COLOR_SPACES_ENUMERATE_INFO_SONY) \
    _avail(XrSwapchainCreateInfoColorSpaceSONY, XR_TYPE_SWAPCHAIN_CREATE_INFO_COLOR_SPACE_SONY) \
    _avail(XrHdrMetadataSONY, XR_TYPE_HDR_METADATA_SONY) \
    _avail(XrSpatialEntityPersistInfoEXT, XR_TYPE_SPATIAL_ENTITY_PERSIST_INFO_EXT) \
    _avail(XrPersistSpatialEntityCompletionEXT, XR_TYPE_PERSIST_SPATIAL_ENTITY_COMPLETION_EXT) \
    _avail(XrSpatialEntityUnpersistInfoEXT, XR_TYPE_SPATIAL_ENTITY_UNPERSIST_INFO_EXT) \
    _avail(XrUnpersistSpatialEntityCompletionEXT, XR_TYPE_UNPERSIST_SPATIAL_ENTITY_COMPLETION_EXT) \
    _avail(XrSpatialReferenceImageEXT, XR_TYPE_SPATIAL_REFERENCE_IMAGE_EXT) \
    _avail(XrSpatialImageStaticOptimizationEXT, XR_TYPE_SPATIAL_IMAGE_STATIC_OPTIMIZATION_EXT) \
    _avail(Xr_Spatial_Image_اندازه_EXT, XR_TYPE_SPATIAL_IMAGE_اندازه_EXT) \
    _avail(XrSpatialCapabilityConfigurationImageTrackingEXT, XR_TYPE_SPATIAL_CAPABILITY_CONFIGURATION_IMAGE_TRACKING_EXT) \
    _avail(XrSpatialImageTrackingDatabaseCreateInfoEXT, XR_TYPE_SPATIAL_IMAGE_TRACKING_DATABASE_CREATE_INFO_EXT) \
    _avail(XrSpatialComponentImage2DListEXT, XR_TYPE_SPATIAL_COMPONENT_IMAGE_2D_LIST_EXT) \
    _avail(XrCreateSpatialImageTrackingDatabaseCompletionEXT, XR_TYPE_CREATE_SPATIAL_IMAGE_TRACKING_DATABASE_COMPLETION_EXT) \
    _avail(XrSpatialCapabilityConfigurationMeshTrackingEXT, XR_TYPE_SPATIAL_CAPABILITY_CONFIGURATION_MESH_TRACKING_EXT) \
    _avail(XrSpatialFeatureTrackWatertightMeshEXT, XR_TYPE_SPATIAL_FEATURE_TRACK_WATERTIGHT_MESH_EXT) \
    _avail(XrSpatialComponentMesh3DNormalsListEXT, XR_TYPE_SPATIAL_COMPONENT_MESH_3D_NORMALS_LIST_EXT) \
    _avail(XrSpatialComponentMesh3DVertexSemanticLabelsListEXT, XR_TYPE_SPATIAL_COMPONENT_MESH_3_D_راس_SEMANTIC_LABELS_LIST_EXT) \
    _avail(XrSpatialComponentMesh3DTriangleSemanticLabelsListEXT, XR_TYPE_SPATIAL_COMPONENT_MESH_3D_TRIANGLE_SEMANTIC_LABELS_LIST_EXT) \
    _avail(XrSpatialCapabilityConfigurationObjectTrackingANDROID, XR_TYPE_SPATIAL_CAPABILITY_CONFIGURATION_OBJECT_TRACKING_ANDROID) \
    _avail(XrSpatialComponentObjectSemanticLabelListANDROID, XR_TYPE_SPATIAL_COMPONENT_OBJECT_SEMANTIC_LABEL_LIST_ANDROID) \
    _avail(Xr_Spatial_Capability_Configuration_ژوروالی_Raycast_ANDROID, XR_TYPE_SPATIAL_CAPABILITY_CONFIGURATION_ژوروالی_RAYCAST_ANDROID) \
    _avail(XrSpatialRaycastInfoANDROID, XR_TYPE_SPATIAL_RAYCAST_INFO_ANDROID) \
    _avail(Xr_Spatial_Component_Raycast_پایله_List_ANDROID, XR_TYPE_SPATIAL_COMPONENT_RAYCAST_پایله_LIST_ANDROID) \
    _avail(XrSpatialRaycastSnapshotCreateInfoANDROID, XR_TYPE_SPATIAL_RAYCAST_SNAPSHOT_CREATE_INFO_ANDROID) \
    _avail(Xr_Google_Cloud_Auth_Info_Api_کلی_ANDROID, XR_TYPE_GOOGLE_CLOUD_AUTH_INFO_API_کلی_ANDROID) \
    _avail(XrGoogleCloudAuthInfoTokenANDROID, XR_TYPE_GOOGLE_CLOUD_AUTH_INFO_TOKEN_ANDROID) \
    _avail(XrGoogleCloudAuthInfoKeylessANDROID, XR_TYPE_GOOGLE_CLOUD_AUTH_INFO_KEYLESS_ANDROID) \
    _avail(Xr_Google_Cloud_Auth_Error_پایله_ANDROID, XR_TYPE_GOOGLE_CLOUD_AUTH_ERROR_پایله_ANDROID) \
    _avail(XrSystemGeospatialPropertiesANDROID, XR_TYPE_SYSTEM_GEOSPATIAL_PROPERTIES_ANDROID) \
    _avail(XrGeospatialTrackerCreateInfoANDROID, XR_TYPE_GEOSPATIAL_TRACKER_CREATE_INFO_ANDROID) \
    _avail(Xr_Event_معلومات_Geospatial_Tracker_State_بدل_شوی_ANDROID, XR_TYPE_EVENT_معلومات_GEOSPATIAL_TRACKER_STATE_بدل_شوی_ANDROID) \
    _avail(XrGeospatialPoseFromPoseLocateInfoANDROID, XR_TYPE_GEOSPATIAL_POSE_FROM_POSE_LOCATE_INFO_ANDROID) \
    _avail(Xr_Geospatial_Pose_پایله_ANDROID, XR_TYPE_GEOSPATIAL_POSE_پایله_ANDROID) \
    _avail(XrGeospatialPoseLocateInfoANDROID, XR_TYPE_GEOSPATIAL_POSE_LOCATE_INFO_ANDROID) \
    _avail(XrVPSAvailabilityCheckCompletionANDROID, XR_TYPE_VPS_AVAILABILITY_CHECK_COMPLETION_ANDROID) \
    _avail(Xr_Spatial_Anchor_پلار_ANDROID, XR_TYPE_SPATIAL_ANCHOR_پلار_ANDROID) \
    _avail(XrSpatialDiscoveryUniqueEntitiesFilterANDROID, XR_TYPE_SPATIAL_DISCOVERY_UNIQUE_ENTITIES_FILTER_ANDROID) \
    _avail(XrSpatialComponentSubsumedByListANDROID, XR_TYPE_SPATIAL_COMPONENT_SUBSUMED_BY_LIST_ANDROID) \
    _avail(XrSpatialAnchorSpaceFromIdCreateInfoANDROID, XR_TYPE_SPATIAL_ANCHOR_SPACE_FROM_ID_CREATE_INFO_ANDROID) \
    _avail(XrSystemGeospatialAnchorPropertiesANDROID, XR_TYPE_SYSTEM_GEOSPATIAL_ANCHOR_PROPERTIES_ANDROID) \
    _avail(XrGeospatialTrackerAnchorTrackingInfoANDROID, XR_TYPE_GEOSPATIAL_TRACKER_ANCHOR_TRACKING_INFO_ANDROID) \
    _avail(XrGeospatialAnchorCreateInfoANDROID, XR_TYPE_GEOSPATIAL_ANCHOR_CREATE_INFO_ANDROID) \
    _avail(XrSurfaceAnchorCreateInfoANDROID, XR_TYPE_SURFACE_ANCHOR_CREATE_INFO_ANDROID) \
    _avail(XrSurfaceAnchorCreateCompletionANDROID, XR_TYPE_SURFACE_ANCHOR_CREATE_COMPLETION_ANDROID) \
    _avail(XrSessionCreateInfoSpatialContainersEXT, XR_TYPE_SESSION_CREATE_INFO_SPATIAL_CONTAINERS_EXT) \
    _avail(XrSpatialContainerCreateInfoEXT, XR_TYPE_SPATIAL_CONTAINER_CREATE_INFO_EXT) \
    _avail(XrSpatialContainerSpaceCreateInfoEXT, XR_TYPE_SPATIAL_CONTAINER_SPACE_CREATE_INFO_EXT) \
    _avail(Xr_Event_معلومات_Spatial_Container_Closed_EXT, XR_TYPE_EVENT_معلومات_SPATIAL_CONTAINER_CLOSED_EXT) \
    _avail(XrSystemSpatialContainerPropertiesEXT, XR_TYPE_SYSTEM_SPATIAL_CONTAINER_PROPERTIES_EXT) \
    _avail(XrSpatialContainerBoundsEXT, XR_TYPE_SPATIAL_CONTAINER_BOUNDS_EXT) \
    _avail(Xr_Event_معلومات_Spatial_Container_Bounds_بدل_شوی_EXT, XR_TYPE_EVENT_معلومات_SPATIAL_CONTAINER_BOUNDS_بدل_شوی_EXT) \
    _avail(XrSpatialContainerBoundsGetInfoEXT, XR_TYPE_SPATIAL_CONTAINER_BOUNDS_GET_INFO_EXT) \
    _avail(XrSpatialContainerStateGetInfoEXT, XR_TYPE_SPATIAL_CONTAINER_STATE_GET_INFO_EXT) \
    _avail(XrSpatialContainerVisibleRequestInfoEXT, XR_TYPE_SPATIAL_CONTAINER_VISIBLE_REQUEST_INFO_EXT) \
    _avail(Xr_Event_معلومات_Spatial_Container_Visible_بدل_شوی_EXT, XR_TYPE_EVENT_معلومات_SPATIAL_CONTAINER_VISIBLE_بدل_شوی_EXT) \
    _avail(Xr_Event_معلومات_Spatial_Container_Visible_Request_Denied_EXT, XR_TYPE_EVENT_معلومات_SPATIAL_CONTAINER_VISIBLE_REQUEST_DENIED_EXT) \
    _avail(Xr_Event_معلومات_Spatial_Container_Interactable_بدل_شوی_EXT, XR_TYPE_EVENT_معلومات_SPATIAL_CONTAINER_INTERACTABLE_بدل_شوی_EXT) \
    _avail(Xr_Spatial_Container_Bounds_ډېرپېښ_Request_Info_EXT, XR_TYPE_SPATIAL_CONTAINER_BOUNDS_ډېرپېښ_REQUEST_INFO_EXT) \
    _avail(Xr_Event_معلومات_Spatial_Container_Bounds_ډېرپېښ_Request_Denied_EXT, XR_TYPE_EVENT_معلومات_SPATIAL_CONTAINER_BOUNDS_ډېرپېښ_REQUEST_DENIED_EXT) \
    _avail(XrSpatialContainerStateEXT, XR_TYPE_SPATIAL_CONTAINER_STATE_EXT) \
    _avail(XrSpatialContainerViewLocateInfoEXT, XR_TYPE_SPATIAL_CONTAINER_VIEW_LOCATE_INFO_EXT) \
    _avail(XrSpatialContainerViewsLocateInfoEXT, XR_TYPE_SPATIAL_CONTAINER_VIEWS_LOCATE_INFO_EXT) \
    _avail(XrSpatialContainerViewStateEXT, XR_TYPE_SPATIAL_CONTAINER_VIEW_STATE_EXT) \
    _avail(XrSpatialContainerLayerEXT, XR_TYPE_SPATIAL_CONTAINER_LAYER_EXT) \
    _avail(Xr_Spatial_Container_Layer_چوکاټ_پای_ټکی_Info_EXT, XR_TYPE_SPATIAL_CONTAINER_LAYER_چوکاټ_پای_ټکی_INFO_EXT) \
    _avail(XrSpatialContainerBeginInfoEXT, XR_TYPE_SPATIAL_CONTAINER_BEGIN_INFO_EXT) \
    _avail(Xr_Spatial_Container_پای_ټکی_Info_EXT, XR_TYPE_SPATIAL_CONTAINER_پای_ټکی_INFO_EXT) \
    _avail(XrSpatialContainerCompositionLayerViewConfigurationEXT, XR_TYPE_SPATIAL_CONTAINER_COMPOSITION_LAYER_VIEW_CONFIGURATION_EXT) \
    _avail(XrSpatialContainerLayerVolumeClippingEXT, XR_TYPE_SPATIAL_CONTAINER_LAYER_VOLUME_CLIPPING_EXT) \
    _avail(XrBatteryStateDisplayEXT, XR_TYPE_BATTERY_STATE_DISPLAY_EXT) \
    _avail(XrLoaderInitInfoPropertiesEXT, XR_TYPE_LOADER_INIT_INFO_PROPERTIES_EXT) \
    _avail(Xr_Event_معلومات_View_Configuration_Views_بدل_شوی_EXT, XR_TYPE_EVENT_معلومات_VIEW_CONFIGURATION_VIEWS_بدل_شوی_EXT) \
    _avail(XrSpatialFilterArchetypeEXT, XR_TYPE_SPATIAL_FILTER_ARCHETYPE_EXT) \
    _avail(XrSpatialComponentPlaneSemanticLabel2ListEXT, XR_TYPE_SPATIAL_COMPONENT_PLANE_SEMANTIC_LABEL2_LIST_EXT) \
    _avail(XrSpatialFeaturePlaneSemanticLabel2SubsetEXT, XR_TYPE_SPATIAL_FEATURE_PLANE_SEMANTIC_LABEL2_SUBSET_EXT) \
    _avail(XrSwapchainFormatsEnumerateInfoEXT, XR_TYPE_SWAPCHAIN_FORMATS_ENUMERATE_INFO_EXT) \
    _avail(XrAppConsumedSwapchainCreateInfoEXT, XR_TYPE_APP_CONSUMED_SWAPCHAIN_CREATE_INFO_EXT) \
    _avail(XrAppConsumedSwapchainPropertiesEXT, XR_TYPE_APP_CONSUMED_SWAPCHAIN_PROPERTIES_EXT) \
    _avail(XrAppConsumedSwapchainImageAcquireInfoEXT, XR_TYPE_APP_CONSUMED_SWAPCHAIN_IMAGE_ACQUIRE_INFO_EXT) \
    _avail(XrAppConsumedSwapchainImageStateEXT, XR_TYPE_APP_CONSUMED_SWAPCHAIN_IMAGE_STATE_EXT) \
    _avail(XrAppConsumedSwapchainImageReleaseInfoEXT, XR_TYPE_APP_CONSUMED_SWAPCHAIN_IMAGE_RELEASE_INFO_EXT) \


#إذا defined(XR_USE_GRAPHICS_API_D3D11)
#تعریف_کړه _impl_XR_LIST_ALL_STRUCTURE_TYPES_XR_USE_GRAPHICS_API_D3D11(_avail, _unavail) \
    _avail(XrGraphicsBindingD3D11KHR, XR_TYPE_GRAPHICS_BINDING_D3D11_KHR) \
    _avail(XrSwapchainImageD3D11KHR, XR_TYPE_SWAPCHAIN_IMAGE_D3D11_KHR) \
    _avail(XrGraphicsRequirementsD3D11KHR, XR_TYPE_GRAPHICS_REQUIREMENTS_D3D11_KHR) \

#وإلا
#تعریف_کړه _impl_XR_LIST_ALL_STRUCTURE_TYPES_XR_USE_GRAPHICS_API_D3D11(_avail, _unavail) \
    _unavail(XrGraphicsBindingD3D11KHR, XR_TYPE_GRAPHICS_BINDING_D3D11_KHR) \
    _unavail(XrSwapchainImageD3D11KHR, XR_TYPE_SWAPCHAIN_IMAGE_D3D11_KHR) \
    _unavail(XrGraphicsRequirementsD3D11KHR, XR_TYPE_GRAPHICS_REQUIREMENTS_D3D11_KHR) \

#د_که_پای

#إذا defined(XR_USE_GRAPHICS_API_D3D12)
#تعریف_کړه _impl_XR_LIST_ALL_STRUCTURE_TYPES_XR_USE_GRAPHICS_API_D3D12(_avail, _unavail) \
    _avail(XrGraphicsBindingD3D12KHR, XR_TYPE_GRAPHICS_BINDING_D3D12_KHR) \
    _avail(XrSwapchainImageD3D12KHR, XR_TYPE_SWAPCHAIN_IMAGE_D3D12_KHR) \
    _avail(XrGraphicsRequirementsD3D12KHR, XR_TYPE_GRAPHICS_REQUIREMENTS_D3D12_KHR) \

#وإلا
#تعریف_کړه _impl_XR_LIST_ALL_STRUCTURE_TYPES_XR_USE_GRAPHICS_API_D3D12(_avail, _unavail) \
    _unavail(XrGraphicsBindingD3D12KHR, XR_TYPE_GRAPHICS_BINDING_D3D12_KHR) \
    _unavail(XrSwapchainImageD3D12KHR, XR_TYPE_SWAPCHAIN_IMAGE_D3D12_KHR) \
    _unavail(XrGraphicsRequirementsD3D12KHR, XR_TYPE_GRAPHICS_REQUIREMENTS_D3D12_KHR) \

#د_که_پای

#إذا defined(XR_USE_GRAPHICS_API_METAL)
#تعریف_کړه _impl_XR_LIST_ALL_STRUCTURE_TYPES_XR_USE_GRAPHICS_API_METAL(_avail, _unavail) \
    _avail(XrGraphicsBindingMetalKHR, XR_TYPE_GRAPHICS_BINDING_METAL_KHR) \
    _avail(XrSwapchainImageMetalKHR, XR_TYPE_SWAPCHAIN_IMAGE_METAL_KHR) \
    _avail(XrGraphicsRequirementsMetalKHR, XR_TYPE_GRAPHICS_REQUIREMENTS_METAL_KHR) \

#وإلا
#تعریف_کړه _impl_XR_LIST_ALL_STRUCTURE_TYPES_XR_USE_GRAPHICS_API_METAL(_avail, _unavail) \
    _unavail(XrGraphicsBindingMetalKHR, XR_TYPE_GRAPHICS_BINDING_METAL_KHR) \
    _unavail(XrSwapchainImageMetalKHR, XR_TYPE_SWAPCHAIN_IMAGE_METAL_KHR) \
    _unavail(XrGraphicsRequirementsMetalKHR, XR_TYPE_GRAPHICS_REQUIREMENTS_METAL_KHR) \

#د_که_پای

#إذا defined(XR_USE_GRAPHICS_API_OPENGL)
#تعریف_کړه _impl_XR_LIST_ALL_STRUCTURE_TYPES_XR_USE_GRAPHICS_API_OPENGL(_avail, _unavail) \
    _avail(XrSwapchainImageOpenGLKHR, XR_TYPE_SWAPCHAIN_IMAGE_OPENGL_KHR) \
    _avail(XrGraphicsRequirementsOpenGLKHR, XR_TYPE_GRAPHICS_REQUIREMENTS_OPENGL_KHR) \

#وإلا
#تعریف_کړه _impl_XR_LIST_ALL_STRUCTURE_TYPES_XR_USE_GRAPHICS_API_OPENGL(_avail, _unavail) \
    _unavail(XrSwapchainImageOpenGLKHR, XR_TYPE_SWAPCHAIN_IMAGE_OPENGL_KHR) \
    _unavail(XrGraphicsRequirementsOpenGLKHR, XR_TYPE_GRAPHICS_REQUIREMENTS_OPENGL_KHR) \

#د_که_پای

#إذا defined(XR_USE_GRAPHICS_API_OPENGL) && defined(XR_USE_PLATFORM_WAYLAND)
#تعریف_کړه _impl_XR_LIST_ALL_STRUCTURE_TYPES_XR_USE_GRAPHICS_API_OPENGL_XR_USE_PLATFORM_WAYLAND(_avail, _unavail) \
    _avail(XrGraphicsBindingOpenGLWaylandKHR, XR_TYPE_GRAPHICS_BINDING_OPENGL_WAYLAND_KHR) \

#وإلا
#تعریف_کړه _impl_XR_LIST_ALL_STRUCTURE_TYPES_XR_USE_GRAPHICS_API_OPENGL_XR_USE_PLATFORM_WAYLAND(_avail, _unavail) \
    _unavail(XrGraphicsBindingOpenGLWaylandKHR, XR_TYPE_GRAPHICS_BINDING_OPENGL_WAYLAND_KHR) \

#د_که_پای

#إذا defined(XR_USE_GRAPHICS_API_OPENGL) && defined(XR_USE_PLATFORM_WIN32)
#تعریف_کړه _impl_XR_LIST_ALL_STRUCTURE_TYPES_XR_USE_GRAPHICS_API_OPENGL_XR_USE_PLATFORM_WIN32(_avail, _unavail) \
    _avail(XrGraphicsBindingOpenGLWin32KHR, XR_TYPE_GRAPHICS_BINDING_OPENGL_WIN32_KHR) \

#وإلا
#تعریف_کړه _impl_XR_LIST_ALL_STRUCTURE_TYPES_XR_USE_GRAPHICS_API_OPENGL_XR_USE_PLATFORM_WIN32(_avail, _unavail) \
    _unavail(XrGraphicsBindingOpenGLWin32KHR, XR_TYPE_GRAPHICS_BINDING_OPENGL_WIN32_KHR) \

#د_که_پای

#إذا defined(XR_USE_GRAPHICS_API_OPENGL) && defined(XR_USE_PLATFORM_XCB)
#تعریف_کړه _impl_XR_LIST_ALL_STRUCTURE_TYPES_XR_USE_GRAPHICS_API_OPENGL_XR_USE_PLATFORM_XCB(_avail, _unavail) \
    _avail(XrGraphicsBindingOpenGLXcbKHR, XR_TYPE_GRAPHICS_BINDING_OPENGL_XCB_KHR) \

#وإلا
#تعریف_کړه _impl_XR_LIST_ALL_STRUCTURE_TYPES_XR_USE_GRAPHICS_API_OPENGL_XR_USE_PLATFORM_XCB(_avail, _unavail) \
    _unavail(XrGraphicsBindingOpenGLXcbKHR, XR_TYPE_GRAPHICS_BINDING_OPENGL_XCB_KHR) \

#د_که_پای

#إذا defined(XR_USE_GRAPHICS_API_OPENGL) && defined(XR_USE_PLATFORM_XLIB)
#تعریف_کړه _impl_XR_LIST_ALL_STRUCTURE_TYPES_XR_USE_GRAPHICS_API_OPENGL_XR_USE_PLATFORM_XLIB(_avail, _unavail) \
    _avail(XrGraphicsBindingOpenGLXlibKHR, XR_TYPE_GRAPHICS_BINDING_OPENGL_XLIB_KHR) \

#وإلا
#تعریف_کړه _impl_XR_LIST_ALL_STRUCTURE_TYPES_XR_USE_GRAPHICS_API_OPENGL_XR_USE_PLATFORM_XLIB(_avail, _unavail) \
    _unavail(XrGraphicsBindingOpenGLXlibKHR, XR_TYPE_GRAPHICS_BINDING_OPENGL_XLIB_KHR) \

#د_که_پای

#إذا defined(XR_USE_GRAPHICS_API_OPENGL_ES)
#تعریف_کړه _impl_XR_LIST_ALL_STRUCTURE_TYPES_XR_USE_GRAPHICS_API_OPENGL_ES(_avail, _unavail) \
    _avail(XrSwapchainImageOpenGLESKHR, XR_TYPE_SWAPCHAIN_IMAGE_OPENGL_ES_KHR) \
    _avail(XrGraphicsRequirementsOpenGLESKHR, XR_TYPE_GRAPHICS_REQUIREMENTS_OPENGL_ES_KHR) \
    _avail(XrSwapchainStateSamplerOpenGLESFB, XR_TYPE_SWAPCHAIN_STATE_SAMPLER_OPENGL_ES_FB) \

#وإلا
#تعریف_کړه _impl_XR_LIST_ALL_STRUCTURE_TYPES_XR_USE_GRAPHICS_API_OPENGL_ES(_avail, _unavail) \
    _unavail(XrSwapchainImageOpenGLESKHR, XR_TYPE_SWAPCHAIN_IMAGE_OPENGL_ES_KHR) \
    _unavail(XrGraphicsRequirementsOpenGLESKHR, XR_TYPE_GRAPHICS_REQUIREMENTS_OPENGL_ES_KHR) \
    _unavail(XrSwapchainStateSamplerOpenGLESFB, XR_TYPE_SWAPCHAIN_STATE_SAMPLER_OPENGL_ES_FB) \

#د_که_پای

#إذا defined(XR_USE_GRAPHICS_API_OPENGL_ES) && defined(XR_USE_PLATFORM_ANDROID)
#تعریف_کړه _impl_XR_LIST_ALL_STRUCTURE_TYPES_XR_USE_GRAPHICS_API_OPENGL_ES_XR_USE_PLATFORM_ANDROID(_avail, _unavail) \
    _avail(XrGraphicsBindingOpenGLESAndroidKHR, XR_TYPE_GRAPHICS_BINDING_OPENGL_ES_ANDROID_KHR) \

#وإلا
#تعریف_کړه _impl_XR_LIST_ALL_STRUCTURE_TYPES_XR_USE_GRAPHICS_API_OPENGL_ES_XR_USE_PLATFORM_ANDROID(_avail, _unavail) \
    _unavail(XrGraphicsBindingOpenGLESAndroidKHR, XR_TYPE_GRAPHICS_BINDING_OPENGL_ES_ANDROID_KHR) \

#د_که_پای

#إذا defined(XR_USE_GRAPHICS_API_VULKAN)
#تعریف_کړه _impl_XR_LIST_ALL_STRUCTURE_TYPES_XR_USE_GRAPHICS_API_VULKAN(_avail, _unavail) \
    _avail(XrVulkanSwapchainFormatListCreateInfoKHR, XR_TYPE_VULKAN_SWAPCHAIN_FORMAT_LIST_CREATE_INFO_KHR) \
    _avail(XrGraphicsBindingVulkanKHR, XR_TYPE_GRAPHICS_BINDING_VULKAN_KHR) \
    _avail(XrSwapchainImageVulkanKHR, XR_TYPE_SWAPCHAIN_IMAGE_VULKAN_KHR) \
    _avail(XrGraphicsRequirementsVulkanKHR, XR_TYPE_GRAPHICS_REQUIREMENTS_VULKAN_KHR) \
    _avail(XrVulkanInstanceCreateInfoKHR, XR_TYPE_VULKAN_INSTANCE_CREATE_INFO_KHR) \
    _avail(XrVulkanDeviceCreateInfoKHR, XR_TYPE_VULKAN_DEVICE_CREATE_INFO_KHR) \
    _avail(XrVulkanGraphicsDeviceGetInfoKHR, XR_TYPE_VULKAN_GRAPHICS_DEVICE_GET_INFO_KHR) \
    _avail(XrSwapchainImageFoveationVulkanFB, XR_TYPE_SWAPCHAIN_IMAGE_FOVEATION_VULKAN_FB) \
    _avail(XrSwapchainStateSamplerVulkanFB, XR_TYPE_SWAPCHAIN_STATE_SAMPLER_VULKAN_FB) \
    _avail(XrVulkanSwapchainCreateInfoMETA, XR_TYPE_VULKAN_SWAPCHAIN_CREATE_INFO_META) \

#وإلا
#تعریف_کړه _impl_XR_LIST_ALL_STRUCTURE_TYPES_XR_USE_GRAPHICS_API_VULKAN(_avail, _unavail) \
    _unavail(XrVulkanSwapchainFormatListCreateInfoKHR, XR_TYPE_VULKAN_SWAPCHAIN_FORMAT_LIST_CREATE_INFO_KHR) \
    _unavail(XrGraphicsBindingVulkanKHR, XR_TYPE_GRAPHICS_BINDING_VULKAN_KHR) \
    _unavail(XrSwapchainImageVulkanKHR, XR_TYPE_SWAPCHAIN_IMAGE_VULKAN_KHR) \
    _unavail(XrGraphicsRequirementsVulkanKHR, XR_TYPE_GRAPHICS_REQUIREMENTS_VULKAN_KHR) \
    _unavail(XrVulkanInstanceCreateInfoKHR, XR_TYPE_VULKAN_INSTANCE_CREATE_INFO_KHR) \
    _unavail(XrVulkanDeviceCreateInfoKHR, XR_TYPE_VULKAN_DEVICE_CREATE_INFO_KHR) \
    _unavail(XrVulkanGraphicsDeviceGetInfoKHR, XR_TYPE_VULKAN_GRAPHICS_DEVICE_GET_INFO_KHR) \
    _unavail(XrSwapchainImageFoveationVulkanFB, XR_TYPE_SWAPCHAIN_IMAGE_FOVEATION_VULKAN_FB) \
    _unavail(XrSwapchainStateSamplerVulkanFB, XR_TYPE_SWAPCHAIN_STATE_SAMPLER_VULKAN_FB) \
    _unavail(XrVulkanSwapchainCreateInfoMETA, XR_TYPE_VULKAN_SWAPCHAIN_CREATE_INFO_META) \

#د_که_پای

#إذا defined(XR_USE_PLATFORM_ANDROID)
#تعریف_کړه _impl_XR_LIST_ALL_STRUCTURE_TYPES_XR_USE_PLATFORM_ANDROID(_avail, _unavail) \
    _avail(XrInstanceCreateInfoAndroidKHR, XR_TYPE_INSTANCE_CREATE_INFO_ANDROID_KHR) \
    _avail(XrLoaderInitInfoAndroidKHR, XR_TYPE_LOADER_INIT_INFO_ANDROID_KHR) \
    _avail(XrAndroidSurfaceSwapchainCreateInfoFB, XR_TYPE_ANDROID_SURFACE_SWAPCHAIN_CREATE_INFO_FB) \
    _avail(XrSwapchainStateAndroidSurfaceDimensionsFB, XR_TYPE_SWAPCHAIN_STATE_ANDROID_SURFACE_DIMENSIONS_FB) \
    _avail(XrAnchorSharingInfoANDROID, XR_TYPE_ANCHOR_SHARING_INFO_ANDROID) \
    _avail(XrAnchorSharingTokenANDROID, XR_TYPE_ANCHOR_SHARING_TOKEN_ANDROID) \
    _avail(XrSystemAnchorSharingExportPropertiesANDROID, XR_TYPE_SYSTEM_ANCHOR_SHARING_EXPORT_PROPERTIES_ANDROID) \

#وإلا
#تعریف_کړه _impl_XR_LIST_ALL_STRUCTURE_TYPES_XR_USE_PLATFORM_ANDROID(_avail, _unavail) \
    _unavail(XrInstanceCreateInfoAndroidKHR, XR_TYPE_INSTANCE_CREATE_INFO_ANDROID_KHR) \
    _unavail(XrLoaderInitInfoAndroidKHR, XR_TYPE_LOADER_INIT_INFO_ANDROID_KHR) \
    _unavail(XrAndroidSurfaceSwapchainCreateInfoFB, XR_TYPE_ANDROID_SURFACE_SWAPCHAIN_CREATE_INFO_FB) \
    _unavail(XrSwapchainStateAndroidSurfaceDimensionsFB, XR_TYPE_SWAPCHAIN_STATE_ANDROID_SURFACE_DIMENSIONS_FB) \
    _unavail(XrAnchorSharingInfoANDROID, XR_TYPE_ANCHOR_SHARING_INFO_ANDROID) \
    _unavail(XrAnchorSharingTokenANDROID, XR_TYPE_ANCHOR_SHARING_TOKEN_ANDROID) \
    _unavail(XrSystemAnchorSharingExportPropertiesANDROID, XR_TYPE_SYSTEM_ANCHOR_SHARING_EXPORT_PROPERTIES_ANDROID) \

#د_که_پای

#إذا defined(XR_USE_PLATFORM_EGL)
#تعریف_کړه _impl_XR_LIST_ALL_STRUCTURE_TYPES_XR_USE_PLATFORM_EGL(_avail, _unavail) \
    _avail(XrGraphicsBindingEGLMNDX, XR_TYPE_GRAPHICS_BINDING_EGL_MNDX) \

#وإلا
#تعریف_کړه _impl_XR_LIST_ALL_STRUCTURE_TYPES_XR_USE_PLATFORM_EGL(_avail, _unavail) \
    _unavail(XrGraphicsBindingEGLMNDX, XR_TYPE_GRAPHICS_BINDING_EGL_MNDX) \

#د_که_پای

#إذا defined(XR_USE_PLATFORM_ML)
#تعریف_کړه _impl_XR_LIST_ALL_STRUCTURE_TYPES_XR_USE_PLATFORM_ML(_avail, _unavail) \
    _avail(XrCoordinateSpaceCreateInfoML, XR_TYPE_COORDINATE_SPACE_CREATE_INFO_ML) \

#وإلا
#تعریف_کړه _impl_XR_LIST_ALL_STRUCTURE_TYPES_XR_USE_PLATFORM_ML(_avail, _unavail) \
    _unavail(XrCoordinateSpaceCreateInfoML, XR_TYPE_COORDINATE_SPACE_CREATE_INFO_ML) \

#د_که_پای

#إذا defined(XR_USE_PLATFORM_WIN32)
#تعریف_کړه _impl_XR_LIST_ALL_STRUCTURE_TYPES_XR_USE_PLATFORM_WIN32(_avail, _unavail) \
    _avail(Xr_Holographic_کړکۍ_Attachment_MSFT, XR_TYPE_HOLOGRAPHIC_کړکۍ_ATTACHMENT_MSFT) \

#وإلا
#تعریف_کړه _impl_XR_LIST_ALL_STRUCTURE_TYPES_XR_USE_PLATFORM_WIN32(_avail, _unavail) \
    _unavail(Xr_Holographic_کړکۍ_Attachment_MSFT, XR_TYPE_HOLOGRAPHIC_کړکۍ_ATTACHMENT_MSFT) \

#د_که_پای




#د_که_پای

