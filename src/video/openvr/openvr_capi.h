/*
  Copyright (c) 2015, Valve Corporation
  All rights reserved.

  Redistribution and use in source and binary forms, with or without modification,
  are permitted provided that the following conditions are met:

  1. Redistributions of source code must retain the above copyright notice, this
     list of conditions and the following disclaimer.

  2. Redistributions in binary form must reproduce the above copyright notice,
     this list of conditions and the following disclaimer in the documentation and/or
     other materials provided with the distribution.

  3. Neither the name of the copyright holder nor the names of its contributors
     may be used to endorse or promote products derived from this software without
     specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
  ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
  ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
//=============================================================================
//
// Purpose: Header for flatted SteamAPI. Use this for binding to other languages.
// This file is auto-generated, do not edit it.
//
//=============================================================================

#यदि_अपरिभाषितम् __OPENVR_API_FLAT_H__
#परिभाषय __OPENVR_API_FLAT_H__
#यदि defined( _WIN32 ) || defined( __clang__ )
#निर्देशः once
#यदि_अन्तः

#यदि_परिभाषितम् __cplusplus
#परिभाषय EXTERN_C बाह्य "C"
#अन्यथा
#परिभाषय EXTERN_C
#यदि_अन्तः

#यदि defined( _WIN32 )
#परिभाषय OPENVR_FNTABLE_CALLTYPE __stdcall
#अन्यथा
#परिभाषय OPENVR_FNTABLE_CALLTYPE 
#यदि_अन्तः

// OPENVR API export macro
#यदि defined( _WIN32 ) && !defined( _X360 )
	#यदि defined( OPENVR_API_EXPORTS )
	#परिभाषय S_API EXTERN_C __declspec( dllexport )
	#नोचेद्यदि defined( OPENVR_API_NODLL )
	#परिभाषय S_API EXTERN_C
	#अन्यथा
	#परिभाषय S_API बाह्य "C" __declspec( dllimport ) 
	#यदि_अन्तः // OPENVR_API_EXPORTS
#नोचेद्यदि defined( __GNUC__ )
	#यदि defined( OPENVR_API_EXPORTS )
	#परिभाषय S_API EXTERN_C __attribute__ ((visibility("default")))
	#अन्यथा
	#परिभाषय S_API EXTERN_C
	#यदि_अन्तः // OPENVR_API_EXPORTS
#अन्यथा // !WIN32
	#यदि defined( OPENVR_API_EXPORTS )
	#परिभाषय S_API EXTERN_C
	#अन्यथा
	#परिभाषय S_API EXTERN_C
	#यदि_अन्तः // OPENVR_API_EXPORTS
#यदि_अन्तः

#यदि_अपरिभाषितम् USE_SDL
#अन्तर्भाव <stdint.h>

#यदि defined( __WIN32 )
प्रकारनिर्देश वर्ण bool;
#अन्यथा
#अन्तर्भाव <stdbool.h>
#यदि_अन्तः
#यदि_अन्तः // USE_SDL

// OpenVR Constants

स्थिर ध्रुव अचिह्नित दीर्घ k_nDriverNone = 4294967295;
स्थिर ध्रुव अचिह्नित दीर्घ k_un_Max_Driver_Debug_Response_आकार = 32768;
स्थिर ध्रुव अचिह्नित दीर्घ k_un_Tracked_Device_सूचकांक_Hmd = 0;
स्थिर ध्रुव अचिह्नित दीर्घ k_un_Max_Tracked_Device_गणनम् = 64;
स्थिर ध्रुव अचिह्नित दीर्घ k_un_Tracked_Device_सूचकांक_Other = 4294967294;
स्थिर ध्रुव अचिह्नित दीर्घ k_un_Tracked_Device_सूचकांक_Invalid = 4294967295;
स्थिर ध्रुव अचिह्नित दीर्घ दीर्घ k_ulInvalidPropertyContainer = 0;
स्थिर ध्रुव अचिह्नित दीर्घ k_un_Invalid_Property_चिह्नकम् = 0;
स्थिर ध्रुव अचिह्नित दीर्घ दीर्घ k_ulInvalidDriverHandle = 0;
स्थिर ध्रुव अचिह्नित दीर्घ k_un_Float_Property_चिह्नकम् = 1;
स्थिर ध्रुव अचिह्नित दीर्घ k_un_Int32_Property_चिह्नकम् = 2;
स्थिर ध्रुव अचिह्नित दीर्घ k_un_Uint64_Property_चिह्नकम् = 3;
स्थिर ध्रुव अचिह्नित दीर्घ k_un_Bool_Property_चिह्नकम् = 4;
स्थिर ध्रुव अचिह्नित दीर्घ k_un_String_Property_चिह्नकम् = 5;
स्थिर ध्रुव अचिह्नित दीर्घ k_un_Error_Property_चिह्नकम् = 6;
स्थिर ध्रुव अचिह्नित दीर्घ k_un_Double_Property_चिह्नकम् = 7;
स्थिर ध्रुव अचिह्नित दीर्घ k_un_Hmd_Matrix34_Property_चिह्नकम् = 20;
स्थिर ध्रुव अचिह्नित दीर्घ k_un_Hmd_Matrix44_Property_चिह्नकम् = 21;
स्थिर ध्रुव अचिह्नित दीर्घ k_un_Hmd_Vector3_Property_चिह्नकम् = 22;
स्थिर ध्रुव अचिह्नित दीर्घ k_un_Hmd_Vector4_Property_चिह्नकम् = 23;
स्थिर ध्रुव अचिह्नित दीर्घ k_un_Hmd_Vector2_Property_चिह्नकम् = 24;
स्थिर ध्रुव अचिह्नित दीर्घ k_un_Hmd_Quad_Property_चिह्नकम् = 25;
स्थिर ध्रुव अचिह्नित दीर्घ k_un_Hidden_Area_Property_चिह्नकम् = 30;
स्थिर ध्रुव अचिह्नित दीर्घ k_un_मार्गः_Handle_Info_चिह्नकम् = 31;
स्थिर ध्रुव अचिह्नित दीर्घ k_un_Action_Property_चिह्नकम् = 32;
स्थिर ध्रुव अचिह्नित दीर्घ k_un_निवेशः_मानम्_Property_चिह्नकम् = 33;
स्थिर ध्रुव अचिह्नित दीर्घ k_un_Wildcard_Property_चिह्नकम् = 34;
स्थिर ध्रुव अचिह्नित दीर्घ k_un_Haptic_Vibration_Property_चिह्नकम् = 35;
स्थिर ध्रुव अचिह्नित दीर्घ k_un_Skeleton_Property_चिह्नकम् = 36;
स्थिर ध्रुव अचिह्नित दीर्घ k_un_Spatial_Anchor_Pose_Property_चिह्नकम् = 40;
स्थिर ध्रुव अचिह्नित दीर्घ k_un_Json_Property_चिह्नकम् = 41;
स्थिर ध्रुव अचिह्नित दीर्घ k_un_सक्रिय_Action_समुच्चयः_Property_चिह्नकम् = 42;
स्थिर ध्रुव अचिह्नित दीर्घ k_unOpenVRInternalReserved_Start = 1000;
स्थिर ध्रुव अचिह्नित दीर्घ k_un_Open_VRInternal_Reserved_अन्तः = 10000;
स्थिर ध्रुव अचिह्नित दीर्घ k_un_Max_Property_String_आकार = 32768;
स्थिर ध्रुव अचिह्नित दीर्घ दीर्घ k_ulInvalidActionHandle = 0;
स्थिर ध्रुव अचिह्नित दीर्घ दीर्घ k_ul_Invalid_Action_समुच्चयः_Handle = 0;
स्थिर ध्रुव अचिह्नित दीर्घ दीर्घ k_ul_Invalid_निवेशः_मानम्_Handle = 0;
स्थिर ध्रुव अचिह्नित दीर्घ k_un_Controller_State_Axis_गणनम् = 5;
स्थिर ध्रुव अचिह्नित दीर्घ दीर्घ k_ulOverlayHandleInvalid = 0;
स्थिर ध्रुव अचिह्नित दीर्घ k_unMaxDistortionFunctionParameters = 8;
स्थिर ध्रुव अचिह्नित दीर्घ k_unScreenshotHandleInvalid = 0;
स्थिर ध्रुव वर्ण * IVRSystem_संस्करणम् = "IVRSystem_022";
स्थिर ध्रुव वर्ण * IVRExtended_Display_संस्करणम् = "IVRExtendedDisplay_001";
स्थिर ध्रुव वर्ण * IVRTracked_Camera_संस्करणम् = "IVRTrackedCamera_006";
स्थिर ध्रुव अचिह्नित दीर्घ k_un_Max_Application_कुञ्चिका_दीर्घता = 128;
स्थिर ध्रुव वर्ण * k_pch_MimeType_HomeApp = "vr/home";
स्थिर ध्रुव वर्ण * k_pch_MimeType_GameTheater = "vr/game_theater";
स्थिर ध्रुव वर्ण * IVRApplications_संस्करणम् = "IVRApplications_007";
स्थिर ध्रुव वर्ण * IVRChaperone_संस्करणम् = "IVRChaperone_004";
स्थिर ध्रुव वर्ण * IVRChaperone_सज्जता_संस्करणम् = "IVRChaperoneSetup_006";
स्थिर ध्रुव वर्ण * IVRCompositor_संस्करणम् = "IVRCompositor_027";
स्थिर ध्रुव अचिह्नित दीर्घ k_un_VROverlay_Max_कुञ्चिका_दीर्घता = 128;
स्थिर ध्रुव अचिह्नित दीर्घ k_un_VROverlay_Max_Name_दीर्घता = 128;
स्थिर ध्रुव अचिह्नित दीर्घ k_un_Max_Overlay_गणनम् = 128;
स्थिर ध्रुव अचिह्नित दीर्घ k_un_Max_Overlay_Intersection_आवरणम्_Primitives_गणनम् = 32;
स्थिर ध्रुव वर्ण * IVROverlay_संस्करणम् = "IVROverlay_026";
स्थिर ध्रुव वर्ण * IVROverlay_View_संस्करणम् = "IVROverlayView_003";
स्थिर ध्रुव अचिह्नित दीर्घ k_un_Headset_View_Max_विस्तारः = 3840;
स्थिर ध्रुव अचिह्नित दीर्घ k_unHeadsetViewMaxHeight = 2160;
स्थिर ध्रुव वर्ण * k_pch_Headset_View_Overlay_कुञ्चिका = "system.HeadsetView";
स्थिर ध्रुव वर्ण * IVRHeadset_View_संस्करणम् = "IVRHeadsetView_001";
स्थिर ध्रुव वर्ण * k_pch_Controller_Component_GDC2015 = "gdc2015";
स्थिर ध्रुव वर्ण * k_pch_Controller_Component_आधारः = "base";
स्थिर ध्रुव वर्ण * k_pch_Controller_Component_Tip = "tip";
स्थिर ध्रुव वर्ण * k_pch_Controller_Component_OpenXR_Aim = "openxr_aim";
स्थिर ध्रुव वर्ण * k_pch_Controller_Component_HandGrip = "handgrip";
स्थिर ध्रुव वर्ण * k_pch_Controller_Component_OpenXR_Grip = "openxr_grip";
स्थिर ध्रुव वर्ण * k_pch_Controller_Component_OpenXR_HandModel = "openxr_handmodel";
स्थिर ध्रुव वर्ण * k_pch_Controller_Component_स्थितिः = "status";
स्थिर ध्रुव वर्ण * IVRRender_Models_संस्करणम् = "IVRRenderModels_006";
स्थिर ध्रुव अचिह्नित दीर्घ k_un_Notification_Text_Max_आकार = 256;
स्थिर ध्रुव वर्ण * IVRNotifications_संस्करणम् = "IVRNotifications_002";
स्थिर ध्रुव अचिह्नित दीर्घ k_un_Max_Settings_कुञ्चिका_दीर्घता = 128;
स्थिर ध्रुव वर्ण * IVRSettings_संस्करणम् = "IVRSettings_003";
स्थिर ध्रुव वर्ण * k_pch_SteamVR_Section = "steamvr";
स्थिर ध्रुव वर्ण * k_pch_SteamVR_RequireHmd_String = "requireHmd";
स्थिर ध्रुव वर्ण * k_pch_Steam_VR_Forced_Driver_कुञ्चिका_String = "forcedDriver";
स्थिर ध्रुव वर्ण * k_pch_Steam_VR_Forced_Hmd_कुञ्चिका_String = "forcedHmd";
स्थिर ध्रुव वर्ण * k_pch_SteamVR_DisplayDebug_Bool = "displayDebug";
स्थिर ध्रुव वर्ण * k_pch_SteamVR_DebugProcessPipe_String = "debugProcessPipe";
स्थिर ध्रुव वर्ण * k_pch_SteamVR_DisplayDebugX_Int32 = "displayDebugX";
स्थिर ध्रुव वर्ण * k_pch_SteamVR_DisplayDebugY_Int32 = "displayDebugY";
स्थिर ध्रुव वर्ण * k_pch_Steam_VR_Send_System_Button_गन्तव्यम्_All_Apps_Bool = "sendSystemButtonToAllApps";
स्थिर ध्रुव वर्ण * k_pch_SteamVR_LogLevel_Int32 = "loglevel";
स्थिर ध्रुव वर्ण * k_pch_SteamVR_IPD_Float = "ipd";
स्थिर ध्रुव वर्ण * k_pch_SteamVR_Background_String = "background";
स्थिर ध्रुव वर्ण * k_pch_SteamVR_BackgroundUseDomeProjection_Bool = "backgroundUseDomeProjection";
स्थिर ध्रुव वर्ण * k_pch_SteamVR_BackgroundCameraHeight_Float = "backgroundCameraHeight";
स्थिर ध्रुव वर्ण * k_pch_SteamVR_BackgroundDomeRadius_Float = "backgroundDomeRadius";
स्थिर ध्रुव वर्ण * k_pch_SteamVR_GridColor_String = "gridColor";
स्थिर ध्रुव वर्ण * k_pch_SteamVR_PlayAreaColor_String = "playAreaColor";
स्थिर ध्रुव वर्ण * k_pch_SteamVR_TrackingLossColor_String = "trackingLossColor";
स्थिर ध्रुव वर्ण * k_pch_SteamVR_ShowStage_Bool = "showStage";
स्थिर ध्रुव वर्ण * k_pch_SteamVR_DrawTrackingReferences_Bool = "drawTrackingReferences";
स्थिर ध्रुव वर्ण * k_pch_Steam_VR_Activate_गुणजः_Drivers_Bool = "activateMultipleDrivers";
स्थिर ध्रुव वर्ण * k_pch_SteamVR_UsingSpeakers_Bool = "usingSpeakers";
स्थिर ध्रुव वर्ण * k_pch_Steam_VR_Speakers_Forward_Yaw_विस्थापनम्_Degrees_Float = "speakersForwardYawOffsetDegrees";
स्थिर ध्रुव वर्ण * k_pch_Steam_VR_आधारः_Station_Power_Management_Int32 = "basestationPowerManagement";
स्थिर ध्रुव वर्ण * k_pch_Steam_VR_Show_आधारः_Station_Power_Management_Tip_Int32 = "ShowBaseStationPowerManagementTip";
स्थिर ध्रुव वर्ण * k_pch_SteamVR_NeverKillProcesses_Bool = "neverKillProcesses";
स्थिर ध्रुव वर्ण * k_pch_SteamVR_SupersampleScale_Float = "supersampleScale";
स्थिर ध्रुव वर्ण * k_pch_SteamVR_MaxRecommendedResolution_Int32 = "maxRecommendedResolution";
स्थिर ध्रुव वर्ण * k_pch_SteamVR_MotionSmoothing_Bool = "motionSmoothing";
स्थिर ध्रुव वर्ण * k_pch_SteamVR_MotionSmoothingOverride_Int32 = "motionSmoothingOverride";
स्थिर ध्रुव वर्ण * k_pch_Steam_VR_चौकटाः_गन्तव्यम्_Throttle_Int32 = "framesToThrottle";
स्थिर ध्रुव वर्ण * k_pch_Steam_VR_Additional_चौकटाः_गन्तव्यम्_Predict_Int32 = "additionalFramesToPredict";
स्थिर ध्रुव वर्ण * k_pch_SteamVR_WorldScale_Float = "worldScale";
स्थिर ध्रुव वर्ण * k_pch_SteamVR_FovScale_Int32 = "fovScale";
स्थिर ध्रुव वर्ण * k_pch_SteamVR_DisableAsyncReprojection_Bool = "disableAsync";
स्थिर ध्रुव वर्ण * k_pch_SteamVR_ForceFadeOnBadTracking_Bool = "forceFadeOnBadTracking";
स्थिर ध्रुव वर्ण * k_pch_SteamVR_DefaultMirrorView_Int32 = "mirrorView";
स्थिर ध्रुव वर्ण * k_pch_SteamVR_ShowLegacyMirrorView_Bool = "showLegacyMirrorView";
स्थिर ध्रुव वर्ण * k_pch_SteamVR_MirrorViewVisibility_Bool = "showMirrorView";
स्थिर ध्रुव वर्ण * k_pch_Steam_VR_Mirror_View_Display_बहुलकम्_Int32 = "mirrorViewDisplayMode";
स्थिर ध्रुव वर्ण * k_pch_SteamVR_MirrorViewEye_Int32 = "mirrorViewEye";
स्थिर ध्रुव वर्ण * k_pch_SteamVR_MirrorViewGeometry_String = "mirrorViewGeometry";
स्थिर ध्रुव वर्ण * k_pch_SteamVR_MirrorViewGeometryMaximized_String = "mirrorViewGeometryMaximized";
स्थिर ध्रुव वर्ण * k_pch_SteamVR_PerfGraphVisibility_Bool = "showPerfGraph";
स्थिर ध्रुव वर्ण * k_pch_SteamVR_StartMonitorFromAppLaunch = "startMonitorFromAppLaunch";
स्थिर ध्रुव वर्ण * k_pch_SteamVR_StartCompositorFromAppLaunch_Bool = "startCompositorFromAppLaunch";
स्थिर ध्रुव वर्ण * k_pch_SteamVR_StartDashboardFromAppLaunch_Bool = "startDashboardFromAppLaunch";
स्थिर ध्रुव वर्ण * k_pch_SteamVR_StartOverlayAppsFromDashboard_Bool = "startOverlayAppsFromDashboard";
स्थिर ध्रुव वर्ण * k_pch_SteamVR_EnableHomeApp = "enableHomeApp";
स्थिर ध्रुव वर्ण * k_pch_Steam_VR_आवृत्तिः_Background_Image_Time_Sec_Int32 = "CycleBackgroundImageTimeSec";
स्थिर ध्रुव वर्ण * k_pch_SteamVR_RetailDemo_Bool = "retailDemo";
स्थिर ध्रुव वर्ण * k_pch_Steam_VR_Ipd_विस्थापनम्_Float = "ipdOffset";
स्थिर ध्रुव वर्ण * k_pch_SteamVR_AllowSupersampleFiltering_Bool = "allowSupersampleFiltering";
स्थिर ध्रुव वर्ण * k_pch_SteamVR_SupersampleManualOverride_Bool = "supersampleManualOverride";
स्थिर ध्रुव वर्ण * k_pch_SteamVR_EnableLinuxVulkanAsync_Bool = "enableLinuxVulkanAsync";
स्थिर ध्रुव वर्ण * k_pch_Steam_VR_Allow_Display_Locked_बहुलकम्_Bool = "allowDisplayLockedMode";
स्थिर ध्रुव वर्ण * k_pch_SteamVR_HaveStartedTutorialForNativeChaperoneDriver_Bool = "haveStartedTutorialForNativeChaperoneDriver";
स्थिर ध्रुव वर्ण * k_pch_SteamVR_ForceWindows32bitVRMonitor = "forceWindows32BitVRMonitor";
स्थिर ध्रुव वर्ण * k_pch_Steam_VR_Debug_निवेशः_Binding = "debugInputBinding";
स्थिर ध्रुव वर्ण * k_pch_Steam_VR_Do_Not_Fade_गन्तव्यम्_Grid = "doNotFadeToGrid";
स्थिर ध्रुव वर्ण * k_pch_Steam_VR_Render_Camera_बहुलकम् = "renderCameraMode";
स्थिर ध्रुव वर्ण * k_pch_SteamVR_EnableSharedResourceJournaling = "enableSharedResourceJournaling";
स्थिर ध्रुव वर्ण * k_pch_Steam_VR_Enable_Safe_बहुलकम् = "enableSafeMode";
स्थिर ध्रुव वर्ण * k_pch_Steam_VR_Preferred_Refresh_दरः = "preferredRefreshRate";
स्थिर ध्रुव वर्ण * k_pch_Steam_VR_चरमः_संस्करणम्_Notice = "lastVersionNotice";
स्थिर ध्रुव वर्ण * k_pch_Steam_VR_चरमः_संस्करणम्_Notice_Date = "lastVersionNoticeDate";
स्थिर ध्रुव वर्ण * k_pch_SteamVR_HmdDisplayColorGainR_Float = "hmdDisplayColorGainR";
स्थिर ध्रुव वर्ण * k_pch_SteamVR_HmdDisplayColorGainG_Float = "hmdDisplayColorGainG";
स्थिर ध्रुव वर्ण * k_pch_SteamVR_HmdDisplayColorGainB_Float = "hmdDisplayColorGainB";
स्थिर ध्रुव वर्ण * k_pch_SteamVR_CustomIconStyle_String = "customIconStyle";
स्थिर ध्रुव वर्ण * k_pch_SteamVR_CustomOffIconStyle_String = "customOffIconStyle";
स्थिर ध्रुव वर्ण * k_pch_SteamVR_CustomIconForceUpdate_String = "customIconForceUpdate";
स्थिर ध्रुव वर्ण * k_pch_Steam_VR_Allow_Global_Action_समुच्चयः_प्राथमिकता = "globalActionSetPriority";
स्थिर ध्रुव वर्ण * k_pch_SteamVR_OverlayRenderQuality = "overlayRenderQuality_2";
स्थिर ध्रुव वर्ण * k_pch_Steam_VR_खण्डम्_Oculus_SDKOn_Open_VRLaunch_Option_Bool = "blockOculusSDKOnOpenVRLaunchOption";
स्थिर ध्रुव वर्ण * k_pch_Steam_VR_खण्डम्_Oculus_SDKOn_All_Launches_Bool = "blockOculusSDKOnAllLaunches";
स्थिर ध्रुव वर्ण * k_pch_SteamVR_HDCPLegacyCompatibility_Bool = "hdcp14legacyCompatibility";
स्थिर ध्रुव वर्ण * k_pch_Steam_VR_Display_पत्तनम्_Training_बहुलकम्_Int = "displayPortTrainingMode";
स्थिर ध्रुव वर्ण * k_pch_SteamVR_UsePrism_Bool = "usePrism";
स्थिर ध्रुव वर्ण * k_pch_प्रत्यक्षम्_बहुलकम्_Section = "direct_mode";
स्थिर ध्रुव वर्ण * k_pch_प्रत्यक्षम्_बहुलकम्_Enable_Bool = "enable";
स्थिर ध्रुव वर्ण * k_pch_प्रत्यक्षम्_बहुलकम्_गणनम्_Int32 = "count";
स्थिर ध्रुव वर्ण * k_pch_प्रत्यक्षम्_बहुलकम्_Edid_Vid_Int32 = "edidVid";
स्थिर ध्रुव वर्ण * k_pch_प्रत्यक्षम्_बहुलकम्_Edid_Pid_Int32 = "edidPid";
स्थिर ध्रुव वर्ण * k_pch_Lighthouse_Section = "driver_lighthouse";
स्थिर ध्रुव वर्ण * k_pch_Lighthouse_DisableIMU_Bool = "disableimu";
स्थिर ध्रुव वर्ण * k_pch_Lighthouse_DisableIMUExceptHMD_Bool = "disableimuexcepthmd";
स्थिर ध्रुव वर्ण * k_pch_Lighthouse_UseDisambiguation_String = "usedisambiguation";
स्थिर ध्रुव वर्ण * k_pch_Lighthouse_DisambiguationDebug_Int32 = "disambiguationdebug";
स्थिर ध्रुव वर्ण * k_pch_Lighthouse_PrimaryBasestation_Int32 = "primarybasestation";
स्थिर ध्रुव वर्ण * k_pch_Lighthouse_DBHistory_Bool = "dbhistory";
स्थिर ध्रुव वर्ण * k_pch_Lighthouse_EnableBluetooth_Bool = "enableBluetooth";
स्थिर ध्रुव वर्ण * k_pch_Lighthouse_Power_Managed_आधारः_Stations_String = "PowerManagedBaseStations";
स्थिर ध्रुव वर्ण * k_pch_Lighthouse_Power_Managed_आधारः_Stations2_String = "PowerManagedBaseStations2";
स्थिर ध्रुव वर्ण * k_pch_Lighthouse_Inactivity_Timeout_For_आधारः_Stations_Int32 = "InactivityTimeoutForBaseStations";
स्थिर ध्रुव वर्ण * k_pch_Lighthouse_EnableImuFallback_Bool = "enableImuFallback";
स्थिर ध्रुव वर्ण * k_pch_Null_Section = "driver_null";
स्थिर ध्रुव वर्ण * k_pch_Null_Serial_सङ्ख्या_String = "serialNumber";
स्थिर ध्रुव वर्ण * k_pch_Null_Model_सङ्ख्या_String = "modelNumber";
स्थिर ध्रुव वर्ण * k_pch_Null_गवाक्षः_X_Int32 = "windowX";
स्थिर ध्रुव वर्ण * k_pch_Null_गवाक्षः_Y_Int32 = "windowY";
स्थिर ध्रुव वर्ण * k_pch_Null_गवाक्षः_विस्तारः_Int32 = "windowWidth";
स्थिर ध्रुव वर्ण * k_pch_Null_गवाक्षः_Height_Int32 = "windowHeight";
स्थिर ध्रुव वर्ण * k_pch_Null_Render_विस्तारः_Int32 = "renderWidth";
स्थिर ध्रुव वर्ण * k_pch_Null_RenderHeight_Int32 = "renderHeight";
स्थिर ध्रुव वर्ण * k_pch_Null_Seconds_From_Vsync_गन्तव्यम्_Photons_Float = "secondsFromVsyncToPhotons";
स्थिर ध्रुव वर्ण * k_pch_Null_DisplayFrequency_Float = "displayFrequency";
स्थिर ध्रुव वर्ण * k_pch_WindowsMR_Section = "driver_holographic";
स्थिर ध्रुव वर्ण * k_pch_UserInterface_Section = "userinterface";
स्थिर ध्रुव वर्ण * k_pch_User_Interface_स्थितिः_Always_On_शिखरम्_Bool = "StatusAlwaysOnTop";
स्थिर ध्रुव वर्ण * k_pch_User_Interface_Minimize_गन्तव्यम्_Tray_Bool = "MinimizeToTray";
स्थिर ध्रुव वर्ण * k_pch_User_Interface_Hide_Popups_When_स्थितिः_Minimized_Bool = "HidePopupsWhenStatusMinimized";
स्थिर ध्रुव वर्ण * k_pch_UserInterface_Screenshots_Bool = "screenshots";
स्थिर ध्रुव वर्ण * k_pch_UserInterface_ScreenshotType_Int = "screenshotType";
स्थिर ध्रुव वर्ण * k_pch_Notifications_Section = "notifications";
स्थिर ध्रुव वर्ण * k_pch_Notifications_DoNotDisturb_Bool = "DoNotDisturb";
स्थिर ध्रुव वर्ण * k_pch_Keyboard_Section = "keyboard";
स्थिर ध्रुव वर्ण * k_pch_Keyboard_TutorialCompletions = "TutorialCompletions";
स्थिर ध्रुव वर्ण * k_pch_Keyboard_ScaleX = "ScaleX";
स्थिर ध्रुव वर्ण * k_pch_Keyboard_ScaleY = "ScaleY";
स्थिर ध्रुव वर्ण * k_pch_Keyboard_विस्थापनम्_वामः_X = "OffsetLeftX";
स्थिर ध्रुव वर्ण * k_pch_Keyboard_विस्थापनम्_दक्षिणः_X = "OffsetRightX";
स्थिर ध्रुव वर्ण * k_pch_Keyboard_विस्थापनम्_Y = "OffsetY";
स्थिर ध्रुव वर्ण * k_pch_Keyboard_Smoothing = "Smoothing";
स्थिर ध्रुव वर्ण * k_pch_Perf_Section = "perfcheck";
स्थिर ध्रुव वर्ण * k_pch_Perf_Perf_Graph_अन्तर्_HMD_Bool = "perfGraphInHMD";
स्थिर ध्रुव वर्ण * k_pch_Perf_AllowTimingStore_Bool = "allowTimingStore";
स्थिर ध्रुव वर्ण * k_pch_Perf_SaveTimingsOnExit_Bool = "saveTimingsOnExit";
स्थिर ध्रुव वर्ण * k_pch_Perf_Test_दत्त_Float = "perfTestData";
स्थिर ध्रुव वर्ण * k_pch_Perf_GPUProfiling_Bool = "GPUProfiling";
स्थिर ध्रुव वर्ण * k_pch_CollisionBounds_Section = "collisionBounds";
स्थिर ध्रुव वर्ण * k_pch_CollisionBounds_Style_Int32 = "CollisionBoundsStyle";
स्थिर ध्रुव वर्ण * k_pch_CollisionBounds_GroundPerimeterOn_Bool = "CollisionBoundsGroundPerimeterOn";
स्थिर ध्रुव वर्ण * k_pch_CollisionBounds_CenterMarkerOn_Bool = "CollisionBoundsCenterMarkerOn";
स्थिर ध्रुव वर्ण * k_pch_CollisionBounds_PlaySpaceOn_Bool = "CollisionBoundsPlaySpaceOn";
स्थिर ध्रुव वर्ण * k_pch_CollisionBounds_FadeDistance_Float = "CollisionBoundsFadeDistance";
स्थिर ध्रुव वर्ण * k_pch_CollisionBounds_WallHeight_Float = "CollisionBoundsWallHeight";
स्थिर ध्रुव वर्ण * k_pch_CollisionBounds_ColorGammaR_Int32 = "CollisionBoundsColorGammaR";
स्थिर ध्रुव वर्ण * k_pch_CollisionBounds_ColorGammaG_Int32 = "CollisionBoundsColorGammaG";
स्थिर ध्रुव वर्ण * k_pch_CollisionBounds_ColorGammaB_Int32 = "CollisionBoundsColorGammaB";
स्थिर ध्रुव वर्ण * k_pch_CollisionBounds_ColorGammaA_Int32 = "CollisionBoundsColorGammaA";
स्थिर ध्रुव वर्ण * k_pch_CollisionBounds_EnableDriverImport = "enableDriverBoundsImport";
स्थिर ध्रुव वर्ण * k_pch_Camera_Section = "camera";
स्थिर ध्रुव वर्ण * k_pch_Camera_EnableCamera_Bool = "enableCamera";
स्थिर ध्रुव वर्ण * k_pch_Camera_ShowOnController_Bool = "showOnController";
स्थिर ध्रुव वर्ण * k_pch_Camera_EnableCameraForCollisionBounds_Bool = "enableCameraForCollisionBounds";
स्थिर ध्रुव वर्ण * k_pch_Camera_अवकाशः_View_Int32 = "roomView";
स्थिर ध्रुव वर्ण * k_pch_Camera_BoundsColorGammaR_Int32 = "cameraBoundsColorGammaR";
स्थिर ध्रुव वर्ण * k_pch_Camera_BoundsColorGammaG_Int32 = "cameraBoundsColorGammaG";
स्थिर ध्रुव वर्ण * k_pch_Camera_BoundsColorGammaB_Int32 = "cameraBoundsColorGammaB";
स्थिर ध्रुव वर्ण * k_pch_Camera_BoundsColorGammaA_Int32 = "cameraBoundsColorGammaA";
स्थिर ध्रुव वर्ण * k_pch_Camera_BoundsStrength_Int32 = "cameraBoundsStrength";
स्थिर ध्रुव वर्ण * k_pch_Camera_अवकाशः_View_Style_Int32 = "roomViewStyle";
स्थिर ध्रुव वर्ण * k_pch_audio_Section = "audio";
स्थिर ध्रुव वर्ण * k_pch_audio_समुच्चयः_Os_Default_Playback_Device_Bool = "setOsDefaultPlaybackDevice";
स्थिर ध्रुव वर्ण * k_pch_audio_EnablePlaybackDeviceOverride_Bool = "enablePlaybackDeviceOverride";
स्थिर ध्रुव वर्ण * k_pch_audio_PlaybackDeviceOverride_String = "playbackDeviceOverride";
स्थिर ध्रुव वर्ण * k_pch_audio_PlaybackDeviceOverrideName_String = "playbackDeviceOverrideName";
स्थिर ध्रुव वर्ण * k_pch_audio_समुच्चयः_Os_Default_Recording_Device_Bool = "setOsDefaultRecordingDevice";
स्थिर ध्रुव वर्ण * k_pch_audio_EnableRecordingDeviceOverride_Bool = "enableRecordingDeviceOverride";
स्थिर ध्रुव वर्ण * k_pch_audio_RecordingDeviceOverride_String = "recordingDeviceOverride";
स्थिर ध्रुव वर्ण * k_pch_audio_RecordingDeviceOverrideName_String = "recordingDeviceOverrideName";
स्थिर ध्रुव वर्ण * k_pch_audio_EnablePlaybackMirror_Bool = "enablePlaybackMirror";
स्थिर ध्रुव वर्ण * k_pch_audio_PlaybackMirrorDevice_String = "playbackMirrorDevice";
स्थिर ध्रुव वर्ण * k_pch_audio_PlaybackMirrorDeviceName_String = "playbackMirrorDeviceName";
स्थिर ध्रुव वर्ण * k_pch_audio_OldPlaybackMirrorDevice_String = "onPlaybackMirrorDevice";
स्थिर ध्रुव वर्ण * k_pch_audio_सक्रिय_Mirror_Device_String = "activePlaybackMirrorDevice";
स्थिर ध्रुव वर्ण * k_pch_audio_EnablePlaybackMirrorIndependentVolume_Bool = "enablePlaybackMirrorIndependentVolume";
स्थिर ध्रुव वर्ण * k_pch_audio_चरमः_Hmd_Playback_Device_Id_String = "lastHmdPlaybackDeviceId";
स्थिर ध्रुव वर्ण * k_pch_audio_VIVEHDMIGain = "viveHDMIGain";
स्थिर ध्रुव वर्ण * k_pch_audio_DualSpeakerAndJackOutput_Bool = "dualSpeakerAndJackOutput";
स्थिर ध्रुव वर्ण * k_pch_audio_MuteMicMonitor_Bool = "muteMicMonitor";
स्थिर ध्रुव वर्ण * k_pch_Power_Section = "power";
स्थिर ध्रुव वर्ण * k_pch_Power_PowerOffOnExit_Bool = "powerOffOnExit";
स्थिर ध्रुव वर्ण * k_pch_Power_TurnOffScreensTimeout_Float = "turnOffScreensTimeout";
स्थिर ध्रुव वर्ण * k_pch_Power_TurnOffControllersTimeout_Float = "turnOffControllersTimeout";
स्थिर ध्रुव वर्ण * k_pch_Power_Return_गन्तव्यम्_Watchdog_Timeout_Float = "returnToWatchdogTimeout";
स्थिर ध्रुव वर्ण * k_pch_Power_AutoLaunchSteamVROnButtonPress = "autoLaunchSteamVROnButtonPress";
स्थिर ध्रुव वर्ण * k_pch_Power_PauseCompositorOnStandby_Bool = "pauseCompositorOnStandby";
स्थिर ध्रुव वर्ण * k_pch_Dashboard_Section = "dashboard";
स्थिर ध्रुव वर्ण * k_pch_Dashboard_EnableDashboard_Bool = "enableDashboard";
स्थिर ध्रुव वर्ण * k_pch_Dashboard_Arcade_बहुलकम्_Bool = "arcadeMode";
स्थिर ध्रुव वर्ण * k_pch_Dashboard_Position = "position";
स्थिर ध्रुव वर्ण * k_pch_Dashboard_DesktopScale = "desktopScale";
स्थिर ध्रुव वर्ण * k_pch_Dashboard_DashboardScale = "dashboardScale";
स्थिर ध्रुव वर्ण * k_pch_Dashboard_UseStandaloneSystemLayer = "standaloneSystemLayer";
स्थिर ध्रुव वर्ण * k_pch_Dashboard_StickyDashboard = "stickyDashboard";
स्थिर ध्रुव वर्ण * k_pch_modelskin_Section = "modelskins";
स्थिर ध्रुव वर्ण * k_pch_Driver_Enable_Bool = "enable";
स्थिर ध्रुव वर्ण * k_pch_Driver_BlockedBySafemode_Bool = "blocked_by_safe_mode";
स्थिर ध्रुव वर्ण * k_pch_Driver_आरोपय_प्राथमिकता_Int32 = "loadPriority";
स्थिर ध्रुव वर्ण * k_pch_WebInterface_Section = "WebInterface";
स्थिर ध्रुव वर्ण * k_pch_VRWebHelper_Section = "VRWebHelper";
स्थिर ध्रुव वर्ण * k_pch_VRWebHelper_DebuggerEnabled_Bool = "DebuggerEnabled";
स्थिर ध्रुव वर्ण * k_pch_VRWeb_Helper_Debugger_पत्तनम्_Int32 = "DebuggerPort";
स्थिर ध्रुव वर्ण * k_pch_TrackingOverride_Section = "TrackingOverrides";
स्थिर ध्रुव वर्ण * k_pch_App_BindingAutosaveURLSuffix_String = "AutosaveURL";
स्थिर ध्रुव वर्ण * k_pch_App_BindingLegacyAPISuffix_String = "_legacy";
स्थिर ध्रुव वर्ण * k_pch_App_BindingSteamVRInputAPISuffix_String = "_steamvrinput";
स्थिर ध्रुव वर्ण * k_pch_App_BindingOpenXRAPISuffix_String = "_openxr";
स्थिर ध्रुव वर्ण * k_pch_App_BindingCurrentURLSuffix_String = "CurrentURL";
स्थिर ध्रुव वर्ण * k_pch_App_BindingPreviousURLSuffix_String = "PreviousURL";
स्थिर ध्रुव वर्ण * k_pch_App_Need_गन्तव्यम्_Update_Autosave_Suffix_Bool = "NeedToUpdateAutosave";
स्थिर ध्रुव वर्ण * k_pch_App_DominantHand_Int32 = "DominantHand";
स्थिर ध्रुव वर्ण * k_pch_App_खण्डम्_Oculus_SDK_Bool = "blockOculusSDK";
स्थिर ध्रुव वर्ण * k_pch_Trackers_Section = "trackers";
स्थिर ध्रुव वर्ण * k_pch_DesktopUI_Section = "DesktopUI";
स्थिर ध्रुव वर्ण * k_pch_चरमः_ज्ञातम्_Section = "LastKnown";
स्थिर ध्रुव वर्ण * k_pch_चरमः_ज्ञातम्_HMDManufacturer_String = "HMDManufacturer";
स्थिर ध्रुव वर्ण * k_pch_चरमः_ज्ञातम्_HMDModel_String = "HMDModel";
स्थिर ध्रुव वर्ण * k_pch_DismissedWarnings_Section = "DismissedWarnings";
स्थिर ध्रुव वर्ण * k_pch_निवेशः_Section = "input";
स्थिर ध्रुव वर्ण * k_pch_निवेशः_वामः_Thumbstick_Rotation_Float = "leftThumbstickRotation";
स्थिर ध्रुव वर्ण * k_pch_निवेशः_दक्षिणः_Thumbstick_Rotation_Float = "rightThumbstickRotation";
स्थिर ध्रुव वर्ण * k_pch_निवेशः_Thumbstick_Deadzone_Float = "thumbstickDeadzone";
स्थिर ध्रुव वर्ण * k_pch_Gpu_जवः_Section = "GpuSpeed";
स्थिर ध्रुव वर्ण * IVRScreenshots_संस्करणम् = "IVRScreenshots_001";
स्थिर ध्रुव वर्ण * IVRResources_संस्करणम् = "IVRResources_001";
स्थिर ध्रुव वर्ण * IVRDriver_Manager_संस्करणम् = "IVRDriverManager_001";
स्थिर ध्रुव अचिह्नित दीर्घ k_un_Max_Action_Name_दीर्घता = 64;
स्थिर ध्रुव अचिह्नित दीर्घ k_un_Max_Action_समुच्चयः_Name_दीर्घता = 64;
स्थिर ध्रुव अचिह्नित दीर्घ k_un_Max_Action_Origin_गणनम् = 16;
स्थिर ध्रुव अचिह्नित दीर्घ k_un_Max_Bone_Name_दीर्घता = 32;
स्थिर ध्रुव पूर्णाङ्क k_n_Action_समुच्चयः_Overlay_Global_प्राथमिकता_Min = 16777216;
स्थिर ध्रुव पूर्णाङ्क k_n_Action_समुच्चयः_Overlay_Global_प्राथमिकता_Max = 33554431;
स्थिर ध्रुव पूर्णाङ्क k_n_Action_समुच्चयः_प्राथमिकता_Reserved_Min = 33554432;
स्थिर ध्रुव वर्ण * IVRInput_संस्करणम् = "IVRInput_010";
स्थिर ध्रुव अचिह्नित दीर्घ दीर्घ k_ulInvalidIOBufferHandle = 0;
स्थिर ध्रुव वर्ण * IVRIOBuffer_संस्करणम् = "IVRIOBuffer_002";
स्थिर ध्रुव अचिह्नित दीर्घ k_ulInvalidSpatialAnchorHandle = 0;
स्थिर ध्रुव वर्ण * IVRSpatial_Anchors_संस्करणम् = "IVRSpatialAnchors_001";
स्थिर ध्रुव वर्ण * IVRDebug_संस्करणम् = "IVRDebug_001";
स्थिर ध्रुव अचिह्नित दीर्घ दीर्घ k_ulDisplayRedirectContainer = 25769803779;
स्थिर ध्रुव वर्ण * IVRProperties_संस्करणम् = "IVRProperties_001";
स्थिर ध्रुव वर्ण * k_pch_मार्गः_User_Hand_दक्षिणः = "/user/hand/right";
स्थिर ध्रुव वर्ण * k_pch_मार्गः_User_Hand_वामः = "/user/hand/left";
स्थिर ध्रुव वर्ण * k_pch_मार्गः_User_Hand_Primary = "/user/hand/primary";
स्थिर ध्रुव वर्ण * k_pch_मार्गः_User_Hand_Secondary = "/user/hand/secondary";
स्थिर ध्रुव वर्ण * k_pch_मार्गः_User_शीर्ष = "/user/head";
स्थिर ध्रुव वर्ण * k_pch_मार्गः_User_Gamepad = "/user/gamepad";
स्थिर ध्रुव वर्ण * k_pch_मार्गः_User_Treadmill = "/user/treadmill";
स्थिर ध्रुव वर्ण * k_pch_मार्गः_User_Stylus = "/user/stylus";
स्थिर ध्रुव वर्ण * k_pch_मार्गः_Devices = "/devices";
स्थिर ध्रुव वर्ण * k_pch_मार्गः_Device_मार्गः = "/device_path";
स्थिर ध्रुव वर्ण * k_pch_मार्गः_Best_Alias_मार्गः = "/best_alias_path";
स्थिर ध्रुव वर्ण * k_pch_मार्गः_Bound_Tracker_Alias_मार्गः = "/bound_tracker_path";
स्थिर ध्रुव वर्ण * k_pch_मार्गः_Bound_Tracker_Role = "/bound_tracker_role";
स्थिर ध्रुव वर्ण * k_pch_मार्गः_Pose_Raw = "/pose/raw";
स्थिर ध्रुव वर्ण * k_pch_मार्गः_Pose_Tip = "/pose/tip";
स्थिर ध्रुव वर्ण * k_pch_मार्गः_Pose_Grip = "/pose/grip";
स्थिर ध्रुव वर्ण * k_pch_मार्गः_System_Button_Click = "/input/system/click";
स्थिर ध्रुव वर्ण * k_pch_मार्गः_Proximity = "/proximity";
स्थिर ध्रुव वर्ण * k_pch_मार्गः_Controller_Type_उपसर्गः = "/controller_type/";
स्थिर ध्रुव वर्ण * k_pch_मार्गः_निवेशः_Profile_Suffix = "/input_profile";
स्थिर ध्रुव वर्ण * k_pch_मार्गः_Binding_Name_Suffix = "/binding_name";
स्थिर ध्रुव वर्ण * k_pch_मार्गः_Binding_Url_Suffix = "/binding_url";
स्थिर ध्रुव वर्ण * k_pch_मार्गः_Binding_Error_Suffix = "/binding_error";
स्थिर ध्रुव वर्ण * k_pch_मार्गः_सक्रिय_Action_Sets = "/active_action_sets";
स्थिर ध्रुव वर्ण * k_pch_मार्गः_Component_Updates = "/total_component_updates";
स्थिर ध्रुव वर्ण * k_pch_मार्गः_User_Foot_वामः = "/user/foot/left";
स्थिर ध्रुव वर्ण * k_pch_मार्गः_User_Foot_दक्षिणः = "/user/foot/right";
स्थिर ध्रुव वर्ण * k_pch_मार्गः_User_Shoulder_वामः = "/user/shoulder/left";
स्थिर ध्रुव वर्ण * k_pch_मार्गः_User_Shoulder_दक्षिणः = "/user/shoulder/right";
स्थिर ध्रुव वर्ण * k_pch_मार्गः_User_Elbow_वामः = "/user/elbow/left";
स्थिर ध्रुव वर्ण * k_pch_मार्गः_User_Elbow_दक्षिणः = "/user/elbow/right";
स्थिर ध्रुव वर्ण * k_pch_मार्गः_User_Knee_वामः = "/user/knee/left";
स्थिर ध्रुव वर्ण * k_pch_मार्गः_User_Knee_दक्षिणः = "/user/knee/right";
स्थिर ध्रुव वर्ण * k_pch_मार्गः_User_Waist = "/user/waist";
स्थिर ध्रुव वर्ण * k_pch_मार्गः_User_Chest = "/user/chest";
स्थिर ध्रुव वर्ण * k_pch_मार्गः_User_Camera = "/user/camera";
स्थिर ध्रुव वर्ण * k_pch_मार्गः_User_Keyboard = "/user/keyboard";
स्थिर ध्रुव वर्ण * k_pch_मार्गः_Client_App_कुञ्चिका = "/client_info/app_key";
स्थिर ध्रुव अचिह्नित दीर्घ दीर्घ k_ul_Invalid_मार्गः_Handle = 0;
स्थिर ध्रुव वर्ण * IVRPaths_संस्करणम् = "IVRPaths_001";
स्थिर ध्रुव वर्ण * IVRBlock_Queue_संस्करणम् = "IVRBlockQueue_005";

// OpenVR Enums

प्रकारनिर्देश गणना EVREye
{
	EVREye_Eye_वामः = 0,
	EVREye_Eye_दक्षिणः = 1,
} EVREye;

प्रकारनिर्देश गणना ETextureType
{
	ETextureType_TextureType_Invalid = -1,
	ETexture_Type_Texture_Type_प्रत्यक्षम्_X = 0,
	ETextureType_TextureType_OpenGL = 1,
	ETextureType_TextureType_Vulkan = 2,
	ETextureType_TextureType_IOSurface = 3,
	ETexture_Type_Texture_Type_प्रत्यक्षम्_X12 = 4,
	ETextureType_TextureType_DXGISharedHandle = 5,
	ETextureType_TextureType_Metal = 6,
} ETextureType;

प्रकारनिर्देश गणना EColorSpace
{
	EColorSpace_ColorSpace_Auto = 0,
	EColorSpace_ColorSpace_Gamma = 1,
	EColor_Space_Color_Space_रैखिकम् = 2,
} EColorSpace;

प्रकारनिर्देश गणना ETracking_परिणाम
{
	ETracking_परिणाम_Tracking_परिणाम_Uninitialized = 1,
	ETracking_परिणाम_Tracking_परिणाम_Calibrating_अन्तर्_प्रगतिः = 100,
	ETracking_परिणाम_Tracking_परिणाम_Calibrating_बहिर्गमनम्_सम्बन्धि_Range = 101,
	ETracking_परिणाम_Tracking_परिणाम_Running_OK = 200,
	ETracking_परिणाम_Tracking_परिणाम_Running_बहिर्गमनम्_सम्बन्धि_Range = 201,
	ETracking_परिणाम_Tracking_परिणाम_Fallback_Rotation_Only = 300,
} ETracking_परिणाम;

प्रकारनिर्देश गणना ETrackedDeviceClass
{
	ETrackedDeviceClass_TrackedDeviceClass_Invalid = 0,
	ETrackedDeviceClass_TrackedDeviceClass_HMD = 1,
	ETrackedDeviceClass_TrackedDeviceClass_Controller = 2,
	ETrackedDeviceClass_TrackedDeviceClass_GenericTracker = 3,
	ETrackedDeviceClass_TrackedDeviceClass_TrackingReference = 4,
	ETrackedDeviceClass_TrackedDeviceClass_DisplayRedirect = 5,
	ETrackedDeviceClass_TrackedDeviceClass_Max = 6,
} ETrackedDeviceClass;

प्रकारनिर्देश गणना ETrackedControllerRole
{
	ETrackedControllerRole_TrackedControllerRole_Invalid = 0,
	ETracked_Controller_Role_Tracked_Controller_Role_वामः_Hand = 1,
	ETracked_Controller_Role_Tracked_Controller_Role_दक्षिणः_Hand = 2,
	ETracked_Controller_Role_Tracked_Controller_Role_Opt_बहिर्गमनम् = 3,
	ETrackedControllerRole_TrackedControllerRole_Treadmill = 4,
	ETrackedControllerRole_TrackedControllerRole_Stylus = 5,
	ETrackedControllerRole_TrackedControllerRole_Max = 5,
} ETrackedControllerRole;

प्रकारनिर्देश गणना ETrackingUniverseOrigin
{
	ETrackingUniverseOrigin_TrackingUniverseSeated = 0,
	ETrackingUniverseOrigin_TrackingUniverseStanding = 1,
	ETrackingUniverseOrigin_TrackingUniverseRawAndUncalibrated = 2,
} ETrackingUniverseOrigin;

प्रकारनिर्देश गणना EAdditionalRadioFeatures
{
	EAdditionalRadioFeatures_AdditionalRadioFeatures_None = 0,
	EAdditionalRadioFeatures_AdditionalRadioFeatures_HTCLinkBox = 1,
	EAdditional_Radio_Features_Additional_Radio_Features_आन्तरिकम्_Dongle = 2,
	EAdditionalRadioFeatures_AdditionalRadioFeatures_ExternalDongle = 4,
} EAdditionalRadioFeatures;

प्रकारनिर्देश गणना ETrackedDeviceProperty
{
	ETrackedDeviceProperty_Prop_Invalid = 0,
	ETrackedDeviceProperty_Prop_TrackingSystemName_String = 1000,
	ETracked_Device_Property_Prop_Model_सङ्ख्या_String = 1001,
	ETracked_Device_Property_Prop_Serial_सङ्ख्या_String = 1002,
	ETrackedDeviceProperty_Prop_RenderModelName_String = 1003,
	ETracked_Device_Property_Prop_Will_Drift_अन्तर्_Yaw_Bool = 1004,
	ETrackedDeviceProperty_Prop_ManufacturerName_String = 1005,
	ETracked_Device_Property_Prop_Tracking_Firmware_संस्करणम्_String = 1006,
	ETrackedDeviceProperty_Prop_HardwareRevision_String = 1007,
	ETrackedDeviceProperty_Prop_AllWirelessDongleDescriptions_String = 1008,
	ETrackedDeviceProperty_Prop_ConnectedWirelessDongle_String = 1009,
	ETrackedDeviceProperty_Prop_DeviceIsWireless_Bool = 1010,
	ETrackedDeviceProperty_Prop_DeviceIsCharging_Bool = 1011,
	ETrackedDeviceProperty_Prop_DeviceBatteryPercentage_Float = 1012,
	ETracked_Device_Property_Prop_स्थितिः_Display_Transform_Matrix34 = 1013,
	ETracked_Device_Property_Prop_Firmware_Update_उपलब्धम्_Bool = 1014,
	ETrackedDeviceProperty_Prop_Firmware_ManualUpdate_Bool = 1015,
	ETrackedDeviceProperty_Prop_Firmware_ManualUpdateURL_String = 1016,
	ETrackedDeviceProperty_Prop_HardwareRevision_Uint64 = 1017,
	ETracked_Device_Property_Prop_Firmware_संस्करणम्_Uint64 = 1018,
	ETrackedDeviceProperty_Prop_FPGAVersion_Uint64 = 1019,
	ETrackedDeviceProperty_Prop_VRCVersion_Uint64 = 1020,
	ETracked_Device_Property_Prop_Radio_संस्करणम्_Uint64 = 1021,
	ETracked_Device_Property_Prop_Dongle_संस्करणम्_Uint64 = 1022,
	ETracked_Device_Property_Prop_खण्डम्_Server_Shutdown_Bool = 1023,
	ETrackedDeviceProperty_Prop_CanUnifyCoordinateSystemWithHmd_Bool = 1024,
	ETracked_Device_Property_Prop_अन्तर्भवति_Proximity_Sensor_Bool = 1025,
	ETracked_Device_Property_Prop_Device_Provides_Battery_स्थितिः_Bool = 1026,
	ETrackedDeviceProperty_Prop_DeviceCanPowerOff_Bool = 1027,
	ETrackedDeviceProperty_Prop_Firmware_ProgrammingTarget_String = 1028,
	ETrackedDeviceProperty_Prop_DeviceClass_Int32 = 1029,
	ETrackedDeviceProperty_Prop_HasCamera_Bool = 1030,
	ETracked_Device_Property_Prop_Driver_संस्करणम्_String = 1031,
	ETrackedDeviceProperty_Prop_Firmware_ForceUpdateRequired_Bool = 1032,
	ETrackedDeviceProperty_Prop_ViveSystemButtonFixRequired_Bool = 1033,
	ETrackedDeviceProperty_Prop_ParentDriver_Uint64 = 1034,
	ETracked_Device_Property_Prop_Resource_मूलम्_String = 1035,
	ETrackedDeviceProperty_Prop_RegisteredDeviceType_String = 1036,
	ETracked_Device_Property_Prop_निवेशः_Profile_मार्गः_String = 1037,
	ETrackedDeviceProperty_Prop_NeverTracked_Bool = 1038,
	ETracked_Device_Property_Prop_अङ्कः_Cameras_Int32 = 1039,
	ETrackedDeviceProperty_Prop_CameraFrameLayout_Int32 = 1040,
	ETracked_Device_Property_Prop_Camera_प्रवाहः_Format_Int32 = 1041,
	ETracked_Device_Property_Prop_Additional_Device_Settings_मार्गः_String = 1042,
	ETrackedDeviceProperty_Prop_Identifiable_Bool = 1043,
	ETracked_Device_Property_Prop_Bootloader_संस्करणम्_Uint64 = 1044,
	ETracked_Device_Property_Prop_Additional_System_Report_दत्त_String = 1045,
	ETracked_Device_Property_Prop_संयुक्त_Firmware_संस्करणम्_String = 1046,
	ETrackedDeviceProperty_Prop_Firmware_RemindUpdate_Bool = 1047,
	ETracked_Device_Property_Prop_Peripheral_Application_संस्करणम्_Uint64 = 1048,
	ETracked_Device_Property_Prop_Manufacturer_Serial_सङ्ख्या_String = 1049,
	ETracked_Device_Property_Prop_Computed_Serial_सङ्ख्या_String = 1050,
	ETrackedDeviceProperty_Prop_EstimatedDeviceFirstUseTime_Int32 = 1051,
	ETrackedDeviceProperty_Prop_DevicePowerUsage_Float = 1052,
	ETrackedDeviceProperty_Prop_IgnoreMotionForStandby_Bool = 1053,
	ETrackedDeviceProperty_Prop_ReportsTimeSinceVSync_Bool = 2000,
	ETracked_Device_Property_Prop_Seconds_From_Vsync_गन्तव्यम्_Photons_Float = 2001,
	ETrackedDeviceProperty_Prop_DisplayFrequency_Float = 2002,
	ETrackedDeviceProperty_Prop_UserIpdMeters_Float = 2003,
	ETrackedDeviceProperty_Prop_CurrentUniverseId_Uint64 = 2004,
	ETrackedDeviceProperty_Prop_PreviousUniverseId_Uint64 = 2005,
	ETracked_Device_Property_Prop_Display_Firmware_संस्करणम्_Uint64 = 2006,
	ETrackedDeviceProperty_Prop_IsOnDesktop_Bool = 2007,
	ETrackedDeviceProperty_Prop_DisplayMCType_Int32 = 2008,
	ETrackedDeviceProperty_Prop_DisplayMCOffset_Float = 2009,
	ETrackedDeviceProperty_Prop_DisplayMCScale_Float = 2010,
	ETrackedDeviceProperty_Prop_EdidVendorID_Int32 = 2011,
	ETracked_Device_Property_Prop_Display_MCImage_वामः_String = 2012,
	ETracked_Device_Property_Prop_Display_MCImage_दक्षिणः_String = 2013,
	ETrackedDeviceProperty_Prop_DisplayGCBlackClamp_Float = 2014,
	ETracked_Device_Property_Prop_Edid_गुणनफलम्_ID_Int32 = 2015,
	ETracked_Device_Property_Prop_Camera_गन्तव्यम्_शीर्ष_Transform_Matrix34 = 2016,
	ETrackedDeviceProperty_Prop_DisplayGCType_Int32 = 2017,
	ETrackedDeviceProperty_Prop_DisplayGCOffset_Float = 2018,
	ETrackedDeviceProperty_Prop_DisplayGCScale_Float = 2019,
	ETrackedDeviceProperty_Prop_DisplayGCPrescale_Float = 2020,
	ETrackedDeviceProperty_Prop_DisplayGCImage_String = 2021,
	ETracked_Device_Property_Prop_Lens_Center_वामः_U_Float = 2022,
	ETracked_Device_Property_Prop_Lens_Center_वामः_V_Float = 2023,
	ETracked_Device_Property_Prop_Lens_Center_दक्षिणः_U_Float = 2024,
	ETracked_Device_Property_Prop_Lens_Center_दक्षिणः_V_Float = 2025,
	ETracked_Device_Property_Prop_User_शीर्ष_गन्तव्यम्_Eye_गभीरता_Meters_Float = 2026,
	ETracked_Device_Property_Prop_Camera_Firmware_संस्करणम्_Uint64 = 2027,
	ETrackedDeviceProperty_Prop_CameraFirmwareDescription_String = 2028,
	ETrackedDeviceProperty_Prop_DisplayFPGAVersion_Uint64 = 2029,
	ETracked_Device_Property_Prop_Display_Bootloader_संस्करणम्_Uint64 = 2030,
	ETracked_Device_Property_Prop_Display_Hardware_संस्करणम्_Uint64 = 2031,
	ETracked_Device_Property_Prop_Audio_Firmware_संस्करणम्_Uint64 = 2032,
	ETracked_Device_Property_Prop_Camera_Compatibility_बहुलकम्_Int32 = 2033,
	ETracked_Device_Property_Prop_Screenshot_Horizontal_क्षेत्रम्_सम्बन्धि_View_Degrees_Float = 2034,
	ETracked_Device_Property_Prop_Screenshot_Vertical_क्षेत्रम्_सम्बन्धि_View_Degrees_Float = 2035,
	ETrackedDeviceProperty_Prop_DisplaySuppressed_Bool = 2036,
	ETracked_Device_Property_Prop_Display_Allow_Night_बहुलकम्_Bool = 2037,
	ETracked_Device_Property_Prop_Display_MCImage_विस्तारः_Int32 = 2038,
	ETrackedDeviceProperty_Prop_DisplayMCImageHeight_Int32 = 2039,
	ETracked_Device_Property_Prop_Display_MCImage_अङ्कः_Channels_Int32 = 2040,
	ETracked_Device_Property_Prop_Display_MCImage_दत्त_द्विमान = 2041,
	ETracked_Device_Property_Prop_Seconds_From_Photons_गन्तव्यम्_Vblank_Float = 2042,
	ETracked_Device_Property_Prop_Driver_प्रत्यक्षम्_बहुलकम्_Sends_Vsync_Events_Bool = 2043,
	ETracked_Device_Property_Prop_Display_Debug_बहुलकम्_Bool = 2044,
	ETrackedDeviceProperty_Prop_GraphicsAdapterLuid_Uint64 = 2045,
	ETracked_Device_Property_Prop_Driver_Provided_Chaperone_मार्गः_String = 2048,
	ETracked_Device_Property_Prop_Expected_Tracking_Reference_गणनम्_Int32 = 2049,
	ETracked_Device_Property_Prop_Expected_Controller_गणनम्_Int32 = 2050,
	ETracked_Device_Property_Prop_Named_Icon_मार्गः_Controller_वामः_Device_Off_String = 2051,
	ETracked_Device_Property_Prop_Named_Icon_मार्गः_Controller_दक्षिणः_Device_Off_String = 2052,
	ETracked_Device_Property_Prop_Named_Icon_मार्गः_Tracking_Reference_Device_Off_String = 2053,
	ETrackedDeviceProperty_Prop_DoNotApplyPrediction_Bool = 2054,
	ETracked_Device_Property_Prop_Camera_गन्तव्यम्_शीर्ष_Transforms_Matrix34_Array = 2055,
	ETrackedDeviceProperty_Prop_DistortionMeshResolution_Int32 = 2056,
	ETrackedDeviceProperty_Prop_DriverIsDrawingControllers_Bool = 2057,
	ETracked_Device_Property_Prop_Driver_अनुरोधाः_Application_Pause_Bool = 2058,
	ETracked_Device_Property_Prop_Driver_अनुरोधाः_Reduced_Rendering_Bool = 2059,
	ETracked_Device_Property_Prop_Minimum_Ipd_चरणः_Meters_Float = 2060,
	ETracked_Device_Property_Prop_Audio_Bridge_Firmware_संस्करणम्_Uint64 = 2061,
	ETracked_Device_Property_Prop_Image_Bridge_Firmware_संस्करणम्_Uint64 = 2062,
	ETracked_Device_Property_Prop_Imu_गन्तव्यम्_शीर्ष_Transform_Matrix34 = 2063,
	ETrackedDeviceProperty_Prop_ImuFactoryGyroBias_Vector3 = 2064,
	ETrackedDeviceProperty_Prop_ImuFactoryGyroScale_Vector3 = 2065,
	ETrackedDeviceProperty_Prop_ImuFactoryAccelerometerBias_Vector3 = 2066,
	ETrackedDeviceProperty_Prop_ImuFactoryAccelerometerScale_Vector3 = 2067,
	ETrackedDeviceProperty_Prop_ConfigurationIncludesLighthouse20Features_Bool = 2069,
	ETrackedDeviceProperty_Prop_AdditionalRadioFeatures_Uint64 = 2070,
	ETrackedDeviceProperty_Prop_CameraWhiteBalance_Vector4_Array = 2071,
	ETrackedDeviceProperty_Prop_CameraDistortionFunction_Int32_Array = 2072,
	ETrackedDeviceProperty_Prop_CameraDistortionCoefficients_Float_Array = 2073,
	ETrackedDeviceProperty_Prop_ExpectedControllerType_String = 2074,
	ETrackedDeviceProperty_Prop_HmdTrackingStyle_Int32 = 2075,
	ETrackedDeviceProperty_Prop_DriverProvidedChaperoneVisibility_Bool = 2076,
	ETracked_Device_Property_Prop_Hmd_Column_Correction_Setting_उपसर्गः_String = 2077,
	ETrackedDeviceProperty_Prop_CameraSupportsCompatibilityModes_Bool = 2078,
	ETracked_Device_Property_Prop_Supports_अवकाशः_View_गभीरता_Projection_Bool = 2079,
	ETracked_Device_Property_Prop_Display_उपलब्धम्_Frame_Rates_Float_Array = 2080,
	ETracked_Device_Property_Prop_Display_Supports_गुणजः_Framerates_Bool = 2081,
	ETracked_Device_Property_Prop_Display_Color_Mult_वामः_Vector3 = 2082,
	ETracked_Device_Property_Prop_Display_Color_Mult_दक्षिणः_Vector3 = 2083,
	ETrackedDeviceProperty_Prop_DisplaySupportsRuntimeFramerateChange_Bool = 2084,
	ETrackedDeviceProperty_Prop_DisplaySupportsAnalogGain_Bool = 2085,
	ETrackedDeviceProperty_Prop_DisplayMinAnalogGain_Float = 2086,
	ETrackedDeviceProperty_Prop_DisplayMaxAnalogGain_Float = 2087,
	ETrackedDeviceProperty_Prop_CameraExposureTime_Float = 2088,
	ETrackedDeviceProperty_Prop_CameraGlobalGain_Float = 2089,
	ETrackedDeviceProperty_Prop_DashboardScale_Float = 2091,
	ETrackedDeviceProperty_Prop_PeerButtonInfo_String = 2092,
	ETrackedDeviceProperty_Prop_Hmd_SupportsHDR10_Bool = 2093,
	ETrackedDeviceProperty_Prop_IpdUIRangeMinMeters_Float = 2100,
	ETrackedDeviceProperty_Prop_IpdUIRangeMaxMeters_Float = 2101,
	ETrackedDeviceProperty_Prop_Hmd_SupportsHDCP14LegacyCompat_Bool = 2102,
	ETrackedDeviceProperty_Prop_Hmd_SupportsMicMonitoring_Bool = 2103,
	ETracked_Device_Property_Prop_Hmd_Supports_Display_पत्तनम्_Training_बहुलकम्_Bool = 2104,
	ETracked_Device_Property_Prop_Supports_अवकाशः_View_प्रत्यक्षम्_Bool = 2105,
	ETrackedDeviceProperty_Prop_SupportsAppThrottling_Bool = 2106,
	ETrackedDeviceProperty_Prop_DSCVersion_Int32 = 2110,
	ETracked_Device_Property_Prop_DSCSlice_गणनम्_Int32 = 2111,
	ETrackedDeviceProperty_Prop_DSCBPPx16_Int32 = 2112,
	ETracked_Device_Property_Prop_Driver_Requested_Mura_Correction_बहुलकम्_Int32 = 2200,
	ETracked_Device_Property_Prop_Driver_Requested_Mura_Feather_Inner_वामः_Int32 = 2201,
	ETracked_Device_Property_Prop_Driver_Requested_Mura_Feather_Inner_दक्षिणः_Int32 = 2202,
	ETracked_Device_Property_Prop_Driver_Requested_Mura_Feather_Inner_शिखरम्_Int32 = 2203,
	ETrackedDeviceProperty_Prop_DriverRequestedMuraFeather_InnerBottom_Int32 = 2204,
	ETracked_Device_Property_Prop_Driver_Requested_Mura_Feather_Outer_वामः_Int32 = 2205,
	ETracked_Device_Property_Prop_Driver_Requested_Mura_Feather_Outer_दक्षिणः_Int32 = 2206,
	ETracked_Device_Property_Prop_Driver_Requested_Mura_Feather_Outer_शिखरम्_Int32 = 2207,
	ETrackedDeviceProperty_Prop_DriverRequestedMuraFeather_OuterBottom_Int32 = 2208,
	ETrackedDeviceProperty_Prop_Audio_DefaultPlaybackDeviceId_String = 2300,
	ETrackedDeviceProperty_Prop_Audio_DefaultRecordingDeviceId_String = 2301,
	ETrackedDeviceProperty_Prop_Audio_DefaultPlaybackDeviceVolume_Float = 2302,
	ETrackedDeviceProperty_Prop_Audio_SupportsDualSpeakerAndJackOutput_Bool = 2303,
	ETrackedDeviceProperty_Prop_AttachedDeviceId_String = 3000,
	ETrackedDeviceProperty_Prop_SupportedButtons_Uint64 = 3001,
	ETrackedDeviceProperty_Prop_Axis0Type_Int32 = 3002,
	ETrackedDeviceProperty_Prop_Axis1Type_Int32 = 3003,
	ETrackedDeviceProperty_Prop_Axis2Type_Int32 = 3004,
	ETrackedDeviceProperty_Prop_Axis3Type_Int32 = 3005,
	ETrackedDeviceProperty_Prop_Axis4Type_Int32 = 3006,
	ETrackedDeviceProperty_Prop_ControllerRoleHint_Int32 = 3007,
	ETracked_Device_Property_Prop_क्षेत्रम्_सम्बन्धि_View_वामः_Degrees_Float = 4000,
	ETracked_Device_Property_Prop_क्षेत्रम्_सम्बन्धि_View_दक्षिणः_Degrees_Float = 4001,
	ETracked_Device_Property_Prop_क्षेत्रम्_सम्बन्धि_View_शिखरम्_Degrees_Float = 4002,
	ETracked_Device_Property_Prop_क्षेत्रम्_सम्बन्धि_View_Bottom_Degrees_Float = 4003,
	ETrackedDeviceProperty_Prop_TrackingRangeMinimumMeters_Float = 4004,
	ETracked_Device_Property_Prop_Tracking_Range_अधिकतमम्_Meters_Float = 4005,
	ETracked_Device_Property_Prop_बहुलकम्_Label_String = 4006,
	ETrackedDeviceProperty_Prop_CanWirelessIdentify_Bool = 4007,
	ETrackedDeviceProperty_Prop_Nonce_Int32 = 4008,
	ETracked_Device_Property_Prop_Icon_मार्गः_Name_String = 5000,
	ETracked_Device_Property_Prop_Named_Icon_मार्गः_Device_Off_String = 5001,
	ETracked_Device_Property_Prop_Named_Icon_मार्गः_Device_Searching_String = 5002,
	ETracked_Device_Property_Prop_Named_Icon_मार्गः_Device_Searching_Alert_String = 5003,
	ETracked_Device_Property_Prop_Named_Icon_मार्गः_Device_Ready_String = 5004,
	ETracked_Device_Property_Prop_Named_Icon_मार्गः_Device_Ready_Alert_String = 5005,
	ETracked_Device_Property_Prop_Named_Icon_मार्गः_Device_Not_Ready_String = 5006,
	ETracked_Device_Property_Prop_Named_Icon_मार्गः_Device_Standby_String = 5007,
	ETracked_Device_Property_Prop_Named_Icon_मार्गः_Device_Alert_नीचः_String = 5008,
	ETracked_Device_Property_Prop_Named_Icon_मार्गः_Device_Standby_Alert_String = 5009,
	ETracked_Device_Property_Prop_Display_Hidden_Area_द्विमान_Start = 5100,
	ETracked_Device_Property_Prop_Display_Hidden_Area_द्विमान_अन्तः = 5150,
	ETrackedDeviceProperty_Prop_ParentContainer = 5151,
	ETrackedDeviceProperty_Prop_OverrideContainer_Uint64 = 5152,
	ETracked_Device_Property_Prop_User_Config_मार्गः_String = 6000,
	ETracked_Device_Property_Prop_Install_मार्गः_String = 6001,
	ETrackedDeviceProperty_Prop_HasDisplayComponent_Bool = 6002,
	ETrackedDeviceProperty_Prop_HasControllerComponent_Bool = 6003,
	ETrackedDeviceProperty_Prop_HasCameraComponent_Bool = 6004,
	ETracked_Device_Property_Prop_Has_Driver_प्रत्यक्षम्_बहुलकम्_Component_Bool = 6005,
	ETrackedDeviceProperty_Prop_HasVirtualDisplayComponent_Bool = 6006,
	ETrackedDeviceProperty_Prop_HasSpatialAnchorsSupport_Bool = 6007,
	ETrackedDeviceProperty_Prop_ControllerType_String = 7000,
	ETracked_Device_Property_Prop_Controller_Hand_Selection_प्राथमिकता_Int32 = 7002,
	ETrackedDeviceProperty_Prop_VendorSpecific_Reserved_Start = 10000,
	ETracked_Device_Property_Prop_Vendor_Specific_Reserved_अन्तः = 10999,
	ETrackedDeviceProperty_Prop_TrackedDeviceProperty_Max = 1000000,
} ETrackedDeviceProperty;

प्रकारनिर्देश गणना ETrackedPropertyError
{
	ETrackedPropertyError_TrackedProp_Success = 0,
	ETracked_Property_Error_Tracked_Prop_Wrong_दत्त_Type = 1,
	ETrackedPropertyError_TrackedProp_WrongDeviceClass = 2,
	ETracked_Property_Error_Tracked_Prop_बफर_Too_Small = 3,
	ETrackedPropertyError_TrackedProp_UnknownProperty = 4,
	ETrackedPropertyError_TrackedProp_InvalidDevice = 5,
	ETrackedPropertyError_TrackedProp_CouldNotContactServer = 6,
	ETracked_Property_Error_Tracked_Prop_मानम्_Not_Provided_By_Device = 7,
	ETracked_Property_Error_Tracked_Prop_String_Exceeds_अधिकतमम्_दीर्घता = 8,
	ETracked_Property_Error_Tracked_Prop_Not_Yet_उपलब्धम् = 9,
	ETrackedPropertyError_TrackedProp_PermissionDenied = 10,
	ETrackedPropertyError_TrackedProp_InvalidOperation = 11,
	ETracked_Property_Error_Tracked_Prop_Cannot_Write_गन्तव्यम्_Wildcards = 12,
	ETrackedPropertyError_TrackedProp_IPCReadFailure = 13,
	ETracked_Property_Error_Tracked_Prop_बहिर्गमनम्_सम्बन्धि_स्मृतिः = 14,
	ETrackedPropertyError_TrackedProp_InvalidContainer = 15,
} ETrackedPropertyError;

प्रकारनिर्देश गणना EHmdTrackingStyle
{
	EHmdTrackingStyle_HmdTrackingStyle_Unknown = 0,
	EHmdTrackingStyle_HmdTrackingStyle_Lighthouse = 1,
	EHmd_Tracking_Style_Hmd_Tracking_Style_Outside_अन्तर्_Cameras = 2,
	EHmd_Tracking_Style_Hmd_Tracking_Style_Inside_बहिर्गमनम्_Cameras = 3,
} EHmdTrackingStyle;

प्रकारनिर्देश गणना EVRSubmitFlags
{
	EVRSubmitFlags_Submit_Default = 0,
	EVRSubmitFlags_Submit_LensDistortionAlreadyApplied = 1,
	EVRSubmit_Flags_Submit_Gl_Render_बफर = 2,
	EVRSubmitFlags_Submit_Reserved = 4,
	EVRSubmitFlags_Submit_TextureWithPose = 8,
	EVRSubmit_Flags_Submit_Texture_With_गभीरता = 16,
	EVRSubmitFlags_Submit_FrameDiscontinuty = 32,
	EVRSubmit_Flags_Submit_Vulkan_Texture_With_Array_दत्त = 64,
	EVRSubmitFlags_Submit_GlArrayTexture = 128,
	EVRSubmitFlags_Submit_Reserved2 = 32768,
	EVRSubmitFlags_Submit_Reserved3 = 65536,
} EVRSubmitFlags;

प्रकारनिर्देश गणना EVRState
{
	EVRState_VRState_Undefined = -1,
	EVRState_VRState_Off = 0,
	EVRState_VRState_Searching = 1,
	EVRState_VRState_Searching_Alert = 2,
	EVRState_VRState_Ready = 3,
	EVRState_VRState_Ready_Alert = 4,
	EVRState_VRState_NotReady = 5,
	EVRState_VRState_Standby = 6,
	EVRState_VRState_Ready_Alert_नीचः = 7,
} EVRState;

प्रकारनिर्देश गणना EVREventType
{
	EVREventType_VREvent_None = 0,
	EVREventType_VREvent_TrackedDeviceActivated = 100,
	EVREventType_VREvent_TrackedDeviceDeactivated = 101,
	EVREventType_VREvent_TrackedDeviceUpdated = 102,
	EVREventType_VREvent_TrackedDeviceUserInteractionStarted = 103,
	EVREventType_VREvent_TrackedDeviceUserInteractionEnded = 104,
	EVREvent_Type_VREvent_Ipd_परिवर्तितम् = 105,
	EVREvent_Type_VREvent_Enter_Standby_बहुलकम् = 106,
	EVREvent_Type_VREvent_Leave_Standby_बहुलकम् = 107,
	EVREvent_Type_VREvent_Tracked_Device_Role_परिवर्तितम् = 108,
	EVREvent_Type_VREvent_Watchdog_Wake_ऊर्ध्वम्_Requested = 109,
	EVREvent_Type_VREvent_Lens_Distortion_परिवर्तितम् = 110,
	EVREvent_Type_VREvent_Property_परिवर्तितम् = 111,
	EVREventType_VREvent_WirelessDisconnect = 112,
	EVREventType_VREvent_WirelessReconnect = 113,
	EVREventType_VREvent_ButtonPress = 200,
	EVREventType_VREvent_ButtonUnpress = 201,
	EVREventType_VREvent_ButtonTouch = 202,
	EVREventType_VREvent_ButtonUntouch = 203,
	EVREventType_VREvent_Modal_Cancel = 257,
	EVREventType_VREvent_MouseMove = 300,
	EVREvent_Type_VREvent_Mouse_Button_अधस्तात् = 301,
	EVREvent_Type_VREvent_Mouse_Button_ऊर्ध्वम् = 302,
	EVREventType_VREvent_FocusEnter = 303,
	EVREventType_VREvent_FocusLeave = 304,
	EVREventType_VREvent_ScrollDiscrete = 305,
	EVREventType_VREvent_TouchPadMove = 306,
	EVREvent_Type_VREvent_Overlay_Focus_परिवर्तितम् = 307,
	EVREventType_VREvent_ReloadOverlays = 308,
	EVREventType_VREvent_ScrollSmooth = 309,
	EVREvent_Type_VREvent_तालकम्_Mouse_Position = 310,
	EVREventType_VREvent_UnlockMousePosition = 311,
	EVREvent_Type_VREvent_निवेशः_Focus_Captured = 400,
	EVREvent_Type_VREvent_निवेशः_Focus_Released = 401,
	EVREvent_Type_VREvent_Scene_Application_परिवर्तितम् = 404,
	EVREvent_Type_VREvent_निवेशः_Focus_परिवर्तितम् = 406,
	EVREventType_VREvent_SceneApplicationUsingWrongGraphicsAdapter = 408,
	EVREventType_VREvent_ActionBindingReloaded = 409,
	EVREventType_VREvent_HideRenderModels = 410,
	EVREventType_VREvent_ShowRenderModels = 411,
	EVREvent_Type_VREvent_Scene_Application_State_परिवर्तितम् = 412,
	EVREventType_VREvent_SceneAppPipeDisconnected = 413,
	EVREventType_VREvent_ConsoleOpened = 420,
	EVREventType_VREvent_ConsoleClosed = 421,
	EVREventType_VREvent_OverlayShown = 500,
	EVREventType_VREvent_OverlayHidden = 501,
	EVREventType_VREvent_DashboardActivated = 502,
	EVREventType_VREvent_DashboardDeactivated = 503,
	EVREventType_VREvent_DashboardRequested = 505,
	EVREventType_VREvent_ResetDashboard = 506,
	EVREventType_VREvent_ImageLoaded = 508,
	EVREventType_VREvent_ShowKeyboard = 509,
	EVREventType_VREvent_HideKeyboard = 510,
	EVREventType_VREvent_OverlayGamepadFocusGained = 511,
	EVREvent_Type_VREvent_Overlay_Gamepad_Focus_नष्टम् = 512,
	EVREvent_Type_VREvent_Overlay_Shared_Texture_परिवर्तितम् = 513,
	EVREventType_VREvent_ScreenshotTriggered = 516,
	EVREventType_VREvent_ImageFailed = 517,
	EVREventType_VREvent_DashboardOverlayCreated = 518,
	EVREventType_VREvent_SwitchGamepadFocus = 519,
	EVREventType_VREvent_RequestScreenshot = 520,
	EVREvent_Type_VREvent_Screenshot_गृहीतम् = 521,
	EVREventType_VREvent_ScreenshotFailed = 522,
	EVREvent_Type_VREvent_Submit_Screenshot_गन्तव्यम्_Dashboard = 523,
	EVREvent_Type_VREvent_Screenshot_प्रगतिः_गन्तव्यम्_Dashboard = 524,
	EVREvent_Type_VREvent_Primary_Dashboard_Device_परिवर्तितम् = 525,
	EVREvent_Type_VREvent_अवकाशः_View_Shown = 526,
	EVREvent_Type_VREvent_अवकाशः_View_Hidden = 527,
	EVREventType_VREvent_ShowUI = 528,
	EVREventType_VREvent_ShowDevTools = 529,
	EVREventType_VREvent_DesktopViewUpdating = 530,
	EVREventType_VREvent_DesktopViewReady = 531,
	EVREventType_VREvent_StartDashboard = 532,
	EVREventType_VREvent_ElevatePrism = 533,
	EVREventType_VREvent_OverlayClosed = 534,
	EVREventType_VREvent_Notification_Shown = 600,
	EVREventType_VREvent_Notification_Hidden = 601,
	EVREventType_VREvent_Notification_BeginInteraction = 602,
	EVREventType_VREvent_Notification_Destroyed = 603,
	EVREventType_VREvent_Quit = 700,
	EVREventType_VREvent_ProcessQuit = 701,
	EVREventType_VREvent_QuitAcknowledged = 703,
	EVREventType_VREvent_DriverRequestedQuit = 704,
	EVREventType_VREvent_RestartRequested = 705,
	EVREventType_VREvent_InvalidateSwapTextureSets = 706,
	EVREvent_Type_VREvent_Chaperone_दत्त_Has_परिवर्तितम् = 800,
	EVREvent_Type_VREvent_Chaperone_Universe_Has_परिवर्तितम् = 801,
	EVREvent_Type_VREvent_Chaperone_अस्थायी_दत्त_Has_परिवर्तितम् = 802,
	EVREvent_Type_VREvent_Chaperone_Settings_Have_परिवर्तितम् = 803,
	EVREventType_VREvent_SeatedZeroPoseReset = 804,
	EVREventType_VREvent_ChaperoneFlushCache = 805,
	EVREvent_Type_VREvent_Chaperone_अवकाशः_सज्जता_Starting = 806,
	EVREvent_Type_VREvent_Chaperone_अवकाशः_सज्जता_परिसमाप्तम् = 807,
	EVREventType_VREvent_StandingZeroPoseReset = 808,
	EVREvent_Type_VREvent_Audio_Settings_Have_परिवर्तितम् = 820,
	EVREvent_Type_VREvent_Background_Setting_Has_परिवर्तितम् = 850,
	EVREvent_Type_VREvent_Camera_Settings_Have_परिवर्तितम् = 851,
	EVREvent_Type_VREvent_Reprojection_Setting_Has_परिवर्तितम् = 852,
	EVREvent_Type_VREvent_Model_Skin_Settings_Have_परिवर्तितम् = 853,
	EVREvent_Type_VREvent_Environment_Settings_Have_परिवर्तितम् = 854,
	EVREvent_Type_VREvent_Power_Settings_Have_परिवर्तितम् = 855,
	EVREvent_Type_VREvent_Enable_Home_App_Settings_Have_परिवर्तितम् = 856,
	EVREvent_Type_VREvent_Steam_VRSection_Setting_परिवर्तितम् = 857,
	EVREvent_Type_VREvent_Lighthouse_Section_Setting_परिवर्तितम् = 858,
	EVREvent_Type_VREvent_Null_Section_Setting_परिवर्तितम् = 859,
	EVREvent_Type_VREvent_User_Interface_Section_Setting_परिवर्तितम् = 860,
	EVREvent_Type_VREvent_Notifications_Section_Setting_परिवर्तितम् = 861,
	EVREvent_Type_VREvent_Keyboard_Section_Setting_परिवर्तितम् = 862,
	EVREvent_Type_VREvent_Perf_Section_Setting_परिवर्तितम् = 863,
	EVREvent_Type_VREvent_Dashboard_Section_Setting_परिवर्तितम् = 864,
	EVREvent_Type_VREvent_Web_Interface_Section_Setting_परिवर्तितम् = 865,
	EVREvent_Type_VREvent_Trackers_Section_Setting_परिवर्तितम् = 866,
	EVREvent_Type_VREvent_चरमः_ज्ञातम्_Section_Setting_परिवर्तितम् = 867,
	EVREvent_Type_VREvent_Dismissed_Warnings_Section_Setting_परिवर्तितम् = 868,
	EVREvent_Type_VREvent_Gpu_जवः_Section_Setting_परिवर्तितम् = 869,
	EVREvent_Type_VREvent_Windows_MRSection_Setting_परिवर्तितम् = 870,
	EVREvent_Type_VREvent_Other_Section_Setting_परिवर्तितम् = 871,
	EVREvent_Type_VREvent_स्थितिः_Update = 900,
	EVREventType_VREvent_WebInterface_InstallDriverCompleted = 950,
	EVREventType_VREvent_MCImageUpdated = 1000,
	EVREventType_VREvent_FirmwareUpdateStarted = 1100,
	EVREvent_Type_VREvent_Firmware_Update_परिसमाप्तम् = 1101,
	EVREventType_VREvent_KeyboardClosed = 1200,
	EVREvent_Type_VREvent_Keyboard_Char_निवेशः = 1201,
	EVREvent_Type_VREvent_Keyboard_समाप्तम् = 1202,
	EVREventType_VREvent_ApplicationListUpdated = 1303,
	EVREvent_Type_VREvent_Application_Mime_Type_आरोपय = 1304,
	EVREventType_VREvent_ProcessConnected = 1306,
	EVREventType_VREvent_ProcessDisconnected = 1307,
	EVREventType_VREvent_Compositor_ChaperoneBoundsShown = 1410,
	EVREventType_VREvent_Compositor_ChaperoneBoundsHidden = 1411,
	EVREventType_VREvent_Compositor_DisplayDisconnected = 1412,
	EVREventType_VREvent_Compositor_DisplayReconnected = 1413,
	EVREventType_VREvent_Compositor_HDCPError = 1414,
	EVREventType_VREvent_Compositor_ApplicationNotResponding = 1415,
	EVREventType_VREvent_Compositor_ApplicationResumed = 1416,
	EVREvent_Type_VREvent_Compositor_बहिर्गमनम्_सम्बन्धि_Video_स्मृतिः = 1417,
	EVREvent_Type_VREvent_Compositor_Display_बहुलकम्_Not_Supported = 1418,
	EVREventType_VREvent_Compositor_StageOverrideReady = 1419,
	EVREventType_VREvent_Compositor_RequestDisconnectReconnect = 1420,
	EVREvent_Type_VREvent_Tracked_Camera_Start_Video_प्रवाहः = 1500,
	EVREvent_Type_VREvent_Tracked_Camera_Stop_Video_प्रवाहः = 1501,
	EVREvent_Type_VREvent_Tracked_Camera_Pause_Video_प्रवाहः = 1502,
	EVREvent_Type_VREvent_Tracked_Camera_Resume_Video_प्रवाहः = 1503,
	EVREventType_VREvent_TrackedCamera_EditingSurface = 1550,
	EVREventType_VREvent_PerformanceTest_EnableCapture = 1600,
	EVREventType_VREvent_PerformanceTest_DisableCapture = 1601,
	EVREventType_VREvent_PerformanceTest_FidelityLevel = 1602,
	EVREvent_Type_VREvent_सन्देशः_Overlay_Closed = 1650,
	EVREvent_Type_VREvent_सन्देशः_Overlay_Close_Requested = 1651,
	EVREvent_Type_VREvent_निवेशः_Haptic_Vibration = 1700,
	EVREvent_Type_VREvent_निवेशः_Binding_आरोपय_Failed = 1701,
	EVREvent_Type_VREvent_निवेशः_Binding_आरोपय_Successful = 1702,
	EVREvent_Type_VREvent_निवेशः_Action_Manifest_Reloaded = 1703,
	EVREvent_Type_VREvent_निवेशः_Action_Manifest_आरोपय_Failed = 1704,
	EVREvent_Type_VREvent_निवेशः_प्रगतिः_Update = 1705,
	EVREvent_Type_VREvent_निवेशः_Tracker_Activated = 1706,
	EVREvent_Type_VREvent_निवेशः_Bindings_Updated = 1707,
	EVREvent_Type_VREvent_निवेशः_Binding_Subscription_परिवर्तितम् = 1708,
	EVREventType_VREvent_SpatialAnchors_PoseUpdated = 1800,
	EVREventType_VREvent_SpatialAnchors_DescriptorUpdated = 1801,
	EVREventType_VREvent_SpatialAnchors_RequestPoseUpdate = 1802,
	EVREventType_VREvent_SpatialAnchors_RequestDescriptorUpdate = 1803,
	EVREventType_VREvent_SystemReport_Started = 1900,
	EVREventType_VREvent_Monitor_ShowHeadsetView = 2000,
	EVREventType_VREvent_Monitor_HideHeadsetView = 2001,
	EVREventType_VREvent_VendorSpecific_Reserved_Start = 10000,
	EVREvent_Type_VREvent_Vendor_Specific_Reserved_अन्तः = 19999,
} EVREventType;

प्रकारनिर्देश गणना EDeviceActivityLevel
{
	EDeviceActivityLevel_k_EDeviceActivityLevel_Unknown = -1,
	EDeviceActivityLevel_k_EDeviceActivityLevel_Idle = 0,
	EDeviceActivityLevel_k_EDeviceActivityLevel_UserInteraction = 1,
	EDeviceActivityLevel_k_EDeviceActivityLevel_UserInteraction_Timeout = 2,
	EDeviceActivityLevel_k_EDeviceActivityLevel_Standby = 3,
	EDeviceActivityLevel_k_EDeviceActivityLevel_Idle_Timeout = 4,
} EDeviceActivityLevel;

प्रकारनिर्देश गणना EVRButtonId
{
	EVRButtonId_k_EButton_System = 0,
	EVRButtonId_k_EButton_ApplicationMenu = 1,
	EVRButtonId_k_EButton_Grip = 2,
	EVRButton_Id_k_EButton_DPad_वामः = 3,
	EVRButton_Id_k_EButton_DPad_ऊर्ध्वम् = 4,
	EVRButton_Id_k_EButton_DPad_दक्षिणः = 5,
	EVRButton_Id_k_EButton_DPad_अधस्तात् = 6,
	EVRButtonId_k_EButton_A = 7,
	EVRButtonId_k_EButton_ProximitySensor = 31,
	EVRButtonId_k_EButton_Axis0 = 32,
	EVRButtonId_k_EButton_Axis1 = 33,
	EVRButtonId_k_EButton_Axis2 = 34,
	EVRButtonId_k_EButton_Axis3 = 35,
	EVRButtonId_k_EButton_Axis4 = 36,
	EVRButtonId_k_EButton_SteamVR_Touchpad = 32,
	EVRButtonId_k_EButton_SteamVR_Trigger = 33,
	EVRButton_Id_k_EButton_Dashboard_पृष्ठभागः = 2,
	EVRButton_Id_k_EButton_सूचकांक_Controller_A = 2,
	EVRButton_Id_k_EButton_सूचकांक_Controller_B = 1,
	EVRButton_Id_k_EButton_सूचकांक_Controller_Joy_Stick = 35,
	EVRButtonId_k_EButton_Max = 64,
} EVRButtonId;

प्रकारनिर्देश गणना EVRMouseButton
{
	EVRMouse_Button_VRMouse_Button_वामः = 1,
	EVRMouse_Button_VRMouse_Button_दक्षिणः = 2,
	EVRMouse_Button_VRMouse_Button_मध्यः = 4,
} EVRMouseButton;

प्रकारनिर्देश गणना EShowUIType
{
	EShowUIType_ShowUI_ControllerBinding = 0,
	EShowUIType_ShowUI_ManageTrackers = 1,
	EShowUIType_ShowUI_Pairing = 3,
	EShowUIType_ShowUI_Settings = 4,
	EShowUIType_ShowUI_DebugCommands = 5,
	EShow_UIType_Show_UI_पूर्णम्_Controller_Binding = 6,
	EShowUIType_ShowUI_ManageDrivers = 7,
} EShowUIType;

प्रकारनिर्देश गणना EHDCPError
{
	EHDCPError_HDCPError_None = 0,
	EHDCPError_HDCPError_Link_नष्टम् = 1,
	EHDCPError_HDCPError_Tampered = 2,
	EHDCPError_HDCPError_DeviceRevoked = 3,
	EHDCPError_HDCPError_Unknown = 4,
} EHDCPError;

प्रकारनिर्देश गणना EVRComponentProperty
{
	EVRComponentProperty_VRComponentProperty_IsStatic = 1,
	EVRComponentProperty_VRComponentProperty_IsVisible = 2,
	EVRComponentProperty_VRComponentProperty_IsTouched = 4,
	EVRComponentProperty_VRComponentProperty_IsPressed = 8,
	EVRComponentProperty_VRComponentProperty_IsScrolled = 16,
	EVRComponentProperty_VRComponentProperty_IsHighlighted = 32,
} EVRComponentProperty;

प्रकारनिर्देश गणना EVRInputError
{
	EVRInputError_VRInputError_None = 0,
	EVRInput_Error_VRInput_Error_Name_Not_प्राप्तम् = 1,
	EVRInputError_VRInputError_WrongType = 2,
	EVRInputError_VRInputError_InvalidHandle = 3,
	EVRInputError_VRInputError_InvalidParam = 4,
	EVRInputError_VRInputError_NoSteam = 5,
	EVRInput_Error_VRInput_Error_Max_क्षमता_Reached = 6,
	EVRInputError_VRInputError_IPCError = 7,
	EVRInput_Error_VRInput_Error_No_सक्रिय_Action_समुच्चयः = 8,
	EVRInputError_VRInputError_InvalidDevice = 9,
	EVRInputError_VRInputError_InvalidSkeleton = 10,
	EVRInput_Error_VRInput_Error_Invalid_Bone_गणनम् = 11,
	EVRInput_Error_VRInput_Error_Invalid_Compressed_दत्त = 12,
	EVRInput_Error_VRInput_Error_No_दत्त = 13,
	EVRInput_Error_VRInput_Error_बफर_Too_Small = 14,
	EVRInputError_VRInputError_MismatchedActionManifest = 15,
	EVRInput_Error_VRInput_Error_Missing_Skeleton_दत्त = 16,
	EVRInput_Error_VRInput_Error_Invalid_Bone_सूचकांक = 17,
	EVRInput_Error_VRInput_Error_Invalid_प्राथमिकता = 18,
	EVRInputError_VRInputError_PermissionDenied = 19,
	EVRInputError_VRInputError_InvalidRenderModel = 20,
} EVRInputError;

प्रकारनिर्देश गणना EVRSpatialAnchorError
{
	EVRSpatialAnchorError_VRSpatialAnchorError_Success = 0,
	EVRSpatial_Anchor_Error_VRSpatial_Anchor_Error_आन्तरिकम् = 1,
	EVRSpatialAnchorError_VRSpatialAnchorError_UnknownHandle = 2,
	EVRSpatialAnchorError_VRSpatialAnchorError_ArrayTooSmall = 3,
	EVRSpatialAnchorError_VRSpatialAnchorError_InvalidDescriptorChar = 4,
	EVRSpatial_Anchor_Error_VRSpatial_Anchor_Error_Not_Yet_उपलब्धम् = 5,
	EVRSpatial_Anchor_Error_VRSpatial_Anchor_Error_Not_उपलब्धम्_अन्तर्_This_Universe = 6,
	EVRSpatialAnchorError_VRSpatialAnchorError_PermanentlyUnavailable = 7,
	EVRSpatialAnchorError_VRSpatialAnchorError_WrongDriver = 8,
	EVRSpatialAnchorError_VRSpatialAnchorError_DescriptorTooLong = 9,
	EVRSpatialAnchorError_VRSpatialAnchorError_Unknown = 10,
	EVRSpatial_Anchor_Error_VRSpatial_Anchor_Error_No_अवकाशः_Calibration = 11,
	EVRSpatial_Anchor_Error_VRSpatial_Anchor_Error_Invalid_तर्कः = 12,
	EVRSpatialAnchorError_VRSpatialAnchorError_UnknownDriver = 13,
} EVRSpatialAnchorError;

प्रकारनिर्देश गणना EHiddenAreaMeshType
{
	EHiddenAreaMeshType_k_eHiddenAreaMesh_Standard = 0,
	EHiddenAreaMeshType_k_eHiddenAreaMesh_Inverse = 1,
	EHidden_Area_Mesh_Type_k_e_Hidden_Area_Mesh_पङ्क्तिः_Loop = 2,
	EHiddenAreaMeshType_k_eHiddenAreaMesh_Max = 3,
} EHiddenAreaMeshType;

प्रकारनिर्देश गणना EVRControllerAxisType
{
	EVRControllerAxisType_k_eControllerAxis_None = 0,
	EVRControllerAxisType_k_eControllerAxis_TrackPad = 1,
	EVRControllerAxisType_k_eControllerAxis_Joystick = 2,
	EVRControllerAxisType_k_eControllerAxis_Trigger = 3,
} EVRControllerAxisType;

प्रकारनिर्देश गणना EVRControllerEventOutputType
{
	EVRControllerEventOutputType_ControllerEventOutput_OSEvents = 0,
	EVRControllerEventOutputType_ControllerEventOutput_VREvents = 1,
} EVRControllerEventOutputType;

प्रकारनिर्देश गणना ECollisionBoundsStyle
{
	ECollisionBoundsStyle_COLLISION_BOUNDS_STYLE_BEGINNER = 0,
	ECollisionBoundsStyle_COLLISION_BOUNDS_STYLE_INTERMEDIATE = 1,
	ECollisionBoundsStyle_COLLISION_BOUNDS_STYLE_SQUARES = 2,
	ECollisionBoundsStyle_COLLISION_BOUNDS_STYLE_ADVANCED = 3,
	ECollisionBoundsStyle_COLLISION_BOUNDS_STYLE_NONE = 4,
	ECollision_Bounds_Style_COLLISION_BOUNDS_STYLE_गणनम् = 5,
} ECollisionBoundsStyle;

प्रकारनिर्देश गणना EVROverlayError
{
	EVROverlayError_VROverlayError_None = 0,
	EVROverlayError_VROverlayError_UnknownOverlay = 10,
	EVROverlayError_VROverlayError_InvalidHandle = 11,
	EVROverlayError_VROverlayError_PermissionDenied = 12,
	EVROverlay_Error_VROverlay_Error_Overlay_सीमा_Exceeded = 13,
	EVROverlayError_VROverlayError_WrongVisibilityType = 14,
	EVROverlay_Error_VROverlay_Error_कुञ्चिका_Too_Long = 15,
	EVROverlayError_VROverlayError_NameTooLong = 16,
	EVROverlay_Error_VROverlay_Error_कुञ्चिका_अन्तर्_Use = 17,
	EVROverlayError_VROverlayError_WrongTransformType = 18,
	EVROverlayError_VROverlayError_InvalidTrackedDevice = 19,
	EVROverlayError_VROverlayError_InvalidParameter = 20,
	EVROverlayError_VROverlayError_ThumbnailCantBeDestroyed = 21,
	EVROverlayError_VROverlayError_ArrayTooSmall = 22,
	EVROverlayError_VROverlayError_RequestFailed = 23,
	EVROverlayError_VROverlayError_InvalidTexture = 24,
	EVROverlay_Error_VROverlay_Error_Unable_गन्तव्यम्_आरोपय_File = 25,
	EVROverlay_Error_VROverlay_Error_Keyboard_Already_अन्तर्_Use = 26,
	EVROverlayError_VROverlayError_NoNeighbor = 27,
	EVROverlay_Error_VROverlay_Error_Too_Many_आवरणम्_Primitives = 29,
	EVROverlay_Error_VROverlay_Error_Bad_आवरणम्_Primitive = 30,
	EVROverlayError_VROverlayError_TextureAlreadyLocked = 31,
	EVROverlay_Error_VROverlay_Error_Texture_तालकम्_क्षमता_Reached = 32,
	EVROverlayError_VROverlayError_TextureNotLocked = 33,
	EVROverlay_Error_VROverlay_Error_Timed_बहिर्गमनम् = 34,
} EVROverlayError;

प्रकारनिर्देश गणना EVRApplicationType
{
	EVRApplicationType_VRApplication_Other = 0,
	EVRApplicationType_VRApplication_Scene = 1,
	EVRApplicationType_VRApplication_Overlay = 2,
	EVRApplicationType_VRApplication_Background = 3,
	EVRApplicationType_VRApplication_Utility = 4,
	EVRApplicationType_VRApplication_VRMonitor = 5,
	EVRApplicationType_VRApplication_SteamWatchdog = 6,
	EVRApplicationType_VRApplication_Bootstrapper = 7,
	EVRApplicationType_VRApplication_WebHelper = 8,
	EVRApplicationType_VRApplication_OpenXRInstance = 9,
	EVRApplicationType_VRApplication_OpenXRScene = 10,
	EVRApplicationType_VRApplication_OpenXROverlay = 11,
	EVRApplicationType_VRApplication_Prism = 12,
	EVRApplication_Type_VRApplication_अवकाशः_View = 13,
	EVRApplicationType_VRApplication_Max = 14,
} EVRApplicationType;

प्रकारनिर्देश गणना EVRFirmwareError
{
	EVRFirmwareError_VRFirmwareError_None = 0,
	EVRFirmwareError_VRFirmwareError_Success = 1,
	EVRFirmwareError_VRFirmwareError_Fail = 2,
} EVRFirmwareError;

प्रकारनिर्देश गणना EVRNotificationError
{
	EVRNotificationError_VRNotificationError_OK = 0,
	EVRNotificationError_VRNotificationError_InvalidNotificationId = 100,
	EVRNotification_Error_VRNotification_Error_Notification_Queue_पूर्णम् = 101,
	EVRNotificationError_VRNotificationError_InvalidOverlayHandle = 102,
	EVRNotification_Error_VRNotification_Error_System_With_User_मानम्_Already_Exists = 103,
} EVRNotificationError;

प्रकारनिर्देश गणना EVRSkeletalMotionRange
{
	EVRSkeletalMotionRange_VRSkeletalMotionRange_WithController = 0,
	EVRSkeletalMotionRange_VRSkeletalMotionRange_WithoutController = 1,
} EVRSkeletalMotionRange;

प्रकारनिर्देश गणना EVRSkeletalTrackingLevel
{
	EVRSkeletalTrackingLevel_VRSkeletalTracking_Estimated = 0,
	EVRSkeletalTrackingLevel_VRSkeletalTracking_Partial = 1,
	EVRSkeletal_Tracking_Level_VRSkeletal_Tracking_पूर्णम् = 2,
	EVRSkeletal_Tracking_Level_VRSkeletal_Tracking_Level_गणनम् = 3,
	EVRSkeletalTrackingLevel_VRSkeletalTrackingLevel_Max = 2,
} EVRSkeletalTrackingLevel;

प्रकारनिर्देश गणना EVRInitError
{
	EVRInitError_VRInitError_None = 0,
	EVRInitError_VRInitError_Unknown = 1,
	EVRInit_Error_VRInit_Error_Init_Installation_Not_प्राप्तम् = 100,
	EVRInitError_VRInitError_Init_InstallationCorrupt = 101,
	EVRInit_Error_VRInit_Error_Init_VRClient_DLLNot_प्राप्तम् = 102,
	EVRInit_Error_VRInit_Error_Init_File_Not_प्राप्तम् = 103,
	EVRInit_Error_VRInit_Error_Init_Factory_Not_प्राप्तम् = 104,
	EVRInit_Error_VRInit_Error_Init_Interface_Not_प्राप्तम् = 105,
	EVRInitError_VRInitError_Init_InvalidInterface = 106,
	EVRInitError_VRInitError_Init_UserConfigDirectoryInvalid = 107,
	EVRInit_Error_VRInit_Error_Init_Hmd_Not_प्राप्तम् = 108,
	EVRInitError_VRInitError_Init_NotInitialized = 109,
	EVRInit_Error_VRInit_Error_Init_मार्गः_Registry_Not_प्राप्तम् = 110,
	EVRInit_Error_VRInit_Error_Init_No_Config_मार्गः = 111,
	EVRInit_Error_VRInit_Error_Init_No_Log_मार्गः = 112,
	EVRInit_Error_VRInit_Error_Init_मार्गः_Registry_Not_Writable = 113,
	EVRInitError_VRInitError_Init_AppInfoInitFailed = 114,
	EVRInitError_VRInitError_Init_Retry = 115,
	EVRInitError_VRInitError_Init_InitCanceledByUser = 116,
	EVRInitError_VRInitError_Init_AnotherAppLaunching = 117,
	EVRInitError_VRInitError_Init_SettingsInitFailed = 118,
	EVRInit_Error_VRInit_Error_Init_Shutting_अधस्तात् = 119,
	EVRInitError_VRInitError_Init_TooManyObjects = 120,
	EVRInitError_VRInitError_Init_NoServerForBackgroundApp = 121,
	EVRInitError_VRInitError_Init_NotSupportedWithCompositor = 122,
	EVRInit_Error_VRInit_Error_Init_Not_उपलब्धम्_गन्तव्यम्_Utility_Apps = 123,
	EVRInit_Error_VRInit_Error_Init_आन्तरिकम् = 124,
	EVRInitError_VRInitError_Init_HmdDriverIdIsNone = 125,
	EVRInit_Error_VRInit_Error_Init_Hmd_Not_प्राप्तम्_Presence_Failed = 126,
	EVRInit_Error_VRInit_Error_Init_VRMonitor_Not_प्राप्तम् = 127,
	EVRInitError_VRInitError_Init_VRMonitorStartupFailed = 128,
	EVRInit_Error_VRInit_Error_Init_नीचः_Power_Watchdog_Not_Supported = 129,
	EVRInitError_VRInitError_Init_InvalidApplicationType = 130,
	EVRInit_Error_VRInit_Error_Init_Not_उपलब्धम्_गन्तव्यम्_Watchdog_Apps = 131,
	EVRInit_Error_VRInit_Error_Init_Watchdog_Disabled_अन्तर्_Settings = 132,
	EVRInit_Error_VRInit_Error_Init_VRDashboard_Not_प्राप्तम् = 133,
	EVRInitError_VRInitError_Init_VRDashboardStartupFailed = 134,
	EVRInit_Error_VRInit_Error_Init_VRHome_Not_प्राप्तम् = 135,
	EVRInitError_VRInitError_Init_VRHomeStartupFailed = 136,
	EVRInitError_VRInitError_Init_RebootingBusy = 137,
	EVRInitError_VRInitError_Init_FirmwareUpdateBusy = 138,
	EVRInitError_VRInitError_Init_FirmwareRecoveryBusy = 139,
	EVRInitError_VRInitError_Init_USBServiceBusy = 140,
	EVRInitError_VRInitError_Init_VRWebHelperStartupFailed = 141,
	EVRInitError_VRInitError_Init_TrackerManagerInitFailed = 142,
	EVRInitError_VRInitError_Init_AlreadyRunning = 143,
	EVRInitError_VRInitError_Init_FailedForVrMonitor = 144,
	EVRInitError_VRInitError_Init_PropertyManagerInitFailed = 145,
	EVRInitError_VRInitError_Init_WebServerFailed = 146,
	EVRInitError_VRInitError_Init_IllegalTypeTransition = 147,
	EVRInitError_VRInitError_Init_MismatchedRuntimes = 148,
	EVRInitError_VRInitError_Init_InvalidProcessId = 149,
	EVRInitError_VRInitError_Init_VRServiceStartupFailed = 150,
	EVRInitError_VRInitError_Init_PrismNeedsNewDrivers = 151,
	EVRInit_Error_VRInit_Error_Init_Prism_Startup_Timed_बहिर्गमनम् = 152,
	EVRInitError_VRInitError_Init_CouldNotStartPrism = 153,
	EVRInitError_VRInitError_Init_PrismClientInitFailed = 154,
	EVRInitError_VRInitError_Init_PrismClientStartFailed = 155,
	EVRInitError_VRInitError_Init_PrismExitedUnexpectedly = 156,
	EVRInitError_VRInitError_Init_BadLuid = 157,
	EVRInitError_VRInitError_Init_NoServerForAppContainer = 158,
	EVRInitError_VRInitError_Init_DuplicateBootstrapper = 159,
	EVRInitError_VRInitError_Init_VRDashboardServicePending = 160,
	EVRInitError_VRInitError_Init_VRDashboardServiceTimeout = 161,
	EVRInitError_VRInitError_Init_VRDashboardServiceStopped = 162,
	EVRInitError_VRInitError_Init_VRDashboardAlreadyStarted = 163,
	EVRInitError_VRInitError_Init_VRDashboardCopyFailed = 164,
	EVRInitError_VRInitError_Init_VRDashboardTokenFailure = 165,
	EVRInitError_VRInitError_Init_VRDashboardEnvironmentFailure = 166,
	EVRInit_Error_VRInit_Error_Init_VRDashboard_मार्गः_Failure = 167,
	EVRInitError_VRInitError_Driver_Failed = 200,
	EVRInitError_VRInitError_Driver_Unknown = 201,
	EVRInitError_VRInitError_Driver_HmdUnknown = 202,
	EVRInitError_VRInitError_Driver_NotLoaded = 203,
	EVRInit_Error_VRInit_Error_Driver_Runtime_बहिर्गमनम्_सम्बन्धि_Date = 204,
	EVRInit_Error_VRInit_Error_Driver_Hmd_अन्तर्_Use = 205,
	EVRInitError_VRInitError_Driver_NotCalibrated = 206,
	EVRInitError_VRInitError_Driver_CalibrationInvalid = 207,
	EVRInit_Error_VRInit_Error_Driver_Hmd_Display_Not_प्राप्तम् = 208,
	EVRInitError_VRInitError_Driver_TrackedDeviceInterfaceUnknown = 209,
	EVRInit_Error_VRInit_Error_Driver_Hmd_Driver_Id_बहिर्गमनम्_सम्बन्धि_Bounds = 211,
	EVRInitError_VRInitError_Driver_HmdDisplayMirrored = 212,
	EVRInit_Error_VRInit_Error_Driver_Hmd_Display_Not_प्राप्तम्_Laptop = 213,
	EVRInitError_VRInitError_Driver_PeerDriverNotInstalled = 214,
	EVRInitError_VRInitError_Driver_WirelessHmdNotConnected = 215,
	EVRInitError_VRInitError_IPC_ServerInitFailed = 300,
	EVRInitError_VRInitError_IPC_ConnectFailed = 301,
	EVRInitError_VRInitError_IPC_SharedStateInitFailed = 302,
	EVRInitError_VRInitError_IPC_CompositorInitFailed = 303,
	EVRInitError_VRInitError_IPC_MutexInitFailed = 304,
	EVRInitError_VRInitError_IPC_Failed = 305,
	EVRInitError_VRInitError_IPC_CompositorConnectFailed = 306,
	EVRInitError_VRInitError_IPC_CompositorInvalidConnectResponse = 307,
	EVRInit_Error_VRInit_Error_IPC_Connect_Failed_After_गुणजः_Attempts = 308,
	EVRInitError_VRInitError_IPC_ConnectFailedAfterTargetExited = 309,
	EVRInitError_VRInitError_IPC_NamespaceUnavailable = 310,
	EVRInitError_VRInitError_Compositor_Failed = 400,
	EVRInitError_VRInitError_Compositor_D3D11HardwareRequired = 401,
	EVRInitError_VRInitError_Compositor_FirmwareRequiresUpdate = 402,
	EVRInitError_VRInitError_Compositor_OverlayInitFailed = 403,
	EVRInitError_VRInitError_Compositor_ScreenshotsInitFailed = 404,
	EVRInit_Error_VRInit_Error_Compositor_Unable_गन्तव्यम्_Create_Device = 405,
	EVRInitError_VRInitError_Compositor_SharedStateIsNull = 406,
	EVRInitError_VRInitError_Compositor_NotificationManagerIsNull = 407,
	EVRInitError_VRInitError_Compositor_ResourceManagerClientIsNull = 408,
	EVRInit_Error_VRInit_Error_Compositor_सन्देशः_Overlay_Shared_State_Init_Failure = 409,
	EVRInitError_VRInitError_Compositor_PropertiesInterfaceIsNull = 410,
	EVRInit_Error_VRInit_Error_Compositor_Create_Fullscreen_गवाक्षः_Failed = 411,
	EVRInitError_VRInitError_Compositor_SettingsInterfaceIsNull = 412,
	EVRInit_Error_VRInit_Error_Compositor_Failed_गन्तव्यम्_Show_गवाक्षः = 413,
	EVRInitError_VRInitError_Compositor_DistortInterfaceIsNull = 414,
	EVRInitError_VRInitError_Compositor_DisplayFrequencyFailure = 415,
	EVRInitError_VRInitError_Compositor_RendererInitializationFailed = 416,
	EVRInitError_VRInitError_Compositor_DXGIFactoryInterfaceIsNull = 417,
	EVRInitError_VRInitError_Compositor_DXGIFactoryCreateFailed = 418,
	EVRInitError_VRInitError_Compositor_DXGIFactoryQueryFailed = 419,
	EVRInitError_VRInitError_Compositor_InvalidAdapterDesktop = 420,
	EVRInitError_VRInitError_Compositor_InvalidHmdAttachment = 421,
	EVRInitError_VRInitError_Compositor_InvalidOutputDesktop = 422,
	EVRInitError_VRInitError_Compositor_InvalidDeviceProvided = 423,
	EVRInitError_VRInitError_Compositor_D3D11RendererInitializationFailed = 424,
	EVRInit_Error_VRInit_Error_Compositor_Failed_गन्तव्यम्_Find_Display_बहुलकम् = 425,
	EVRInit_Error_VRInit_Error_Compositor_Failed_गन्तव्यम्_Create_Swap_Chain = 426,
	EVRInit_Error_VRInit_Error_Compositor_Failed_गन्तव्यम्_Get_पृष्ठभागः_बफर = 427,
	EVRInit_Error_VRInit_Error_Compositor_Failed_गन्तव्यम्_Create_Render_Target = 428,
	EVRInit_Error_VRInit_Error_Compositor_Failed_गन्तव्यम्_Create_DXGI2_Swap_Chain = 429,
	EVRInit_Error_VRInit_Error_Compositor_Failedto_Get_DXGI2_पृष्ठभागः_बफर = 430,
	EVRInit_Error_VRInit_Error_Compositor_Failed_गन्तव्यम्_Create_DXGI2_Render_Target = 431,
	EVRInit_Error_VRInit_Error_Compositor_Failed_गन्तव्यम्_Get_DXGIDevice_Interface = 432,
	EVRInit_Error_VRInit_Error_Compositor_Select_Display_बहुलकम् = 433,
	EVRInit_Error_VRInit_Error_Compositor_Failed_गन्तव्यम्_Create_Nv_APIRender_Targets = 434,
	EVRInit_Error_VRInit_Error_Compositor_Nv_APISet_Display_बहुलकम् = 435,
	EVRInit_Error_VRInit_Error_Compositor_Failed_गन्तव्यम्_Create_प्रत्यक्षम्_बहुलकम्_Display = 436,
	EVRInitError_VRInitError_Compositor_InvalidHmdPropertyContainer = 437,
	EVRInitError_VRInitError_Compositor_UpdateDisplayFrequency = 438,
	EVRInitError_VRInitError_Compositor_CreateRasterizerState = 439,
	EVRInitError_VRInitError_Compositor_CreateWireframeRasterizerState = 440,
	EVRInitError_VRInitError_Compositor_CreateSamplerState = 441,
	EVRInit_Error_VRInit_Error_Compositor_Create_Clamp_गन्तव्यम्_Border_Sampler_State = 442,
	EVRInitError_VRInitError_Compositor_CreateAnisoSamplerState = 443,
	EVRInitError_VRInitError_Compositor_CreateOverlaySamplerState = 444,
	EVRInitError_VRInitError_Compositor_CreatePanoramaSamplerState = 445,
	EVRInitError_VRInitError_Compositor_CreateFontSamplerState = 446,
	EVRInitError_VRInitError_Compositor_CreateNoBlendState = 447,
	EVRInitError_VRInitError_Compositor_CreateBlendState = 448,
	EVRInitError_VRInitError_Compositor_CreateAlphaBlendState = 449,
	EVRInit_Error_VRInit_Error_Compositor_Create_Blend_State_आवरणम्_R = 450,
	EVRInit_Error_VRInit_Error_Compositor_Create_Blend_State_आवरणम्_G = 451,
	EVRInit_Error_VRInit_Error_Compositor_Create_Blend_State_आवरणम्_B = 452,
	EVRInit_Error_VRInit_Error_Compositor_Create_गभीरता_Stencil_State = 453,
	EVRInit_Error_VRInit_Error_Compositor_Create_गभीरता_Stencil_State_No_Write = 454,
	EVRInit_Error_VRInit_Error_Compositor_Create_गभीरता_Stencil_State_No_गभीरता = 455,
	EVRInitError_VRInitError_Compositor_CreateFlushTexture = 456,
	EVRInitError_VRInitError_Compositor_CreateDistortionSurfaces = 457,
	EVRInit_Error_VRInit_Error_Compositor_Create_Constant_बफर = 458,
	EVRInit_Error_VRInit_Error_Compositor_Create_Hmd_Pose_Constant_बफर = 459,
	EVRInit_Error_VRInit_Error_Compositor_Create_Hmd_Pose_Staging_Constant_बफर = 460,
	EVRInit_Error_VRInit_Error_Compositor_Create_Shared_Frame_Info_Constant_बफर = 461,
	EVRInit_Error_VRInit_Error_Compositor_Create_Overlay_Constant_बफर = 462,
	EVRInit_Error_VRInit_Error_Compositor_Create_Scene_Texture_सूचकांक_Constant_बफर = 463,
	EVRInit_Error_VRInit_Error_Compositor_Create_Readable_Scene_Texture_सूचकांक_Constant_बफर = 464,
	EVRInit_Error_VRInit_Error_Compositor_Create_Layer_Graphics_Texture_सूचकांक_Constant_बफर = 465,
	EVRInit_Error_VRInit_Error_Compositor_Create_Layer_Compute_Texture_सूचकांक_Constant_बफर = 466,
	EVRInit_Error_VRInit_Error_Compositor_Create_Layer_Compute_Scene_Texture_सूचकांक_Constant_बफर = 467,
	EVRInit_Error_VRInit_Error_Compositor_Create_Compute_Hmd_Pose_Constant_बफर = 468,
	EVRInit_Error_VRInit_Error_Compositor_Create_Geom_Constant_बफर = 469,
	EVRInit_Error_VRInit_Error_Compositor_Create_Panel_आवरणम्_Constant_बफर = 470,
	EVRInitError_VRInitError_Compositor_CreatePixelSimUBO = 471,
	EVRInitError_VRInitError_Compositor_CreateMSAARenderTextures = 472,
	EVRInitError_VRInitError_Compositor_CreateResolveRenderTextures = 473,
	EVRInitError_VRInitError_Compositor_CreateComputeResolveRenderTextures = 474,
	EVRInit_Error_VRInit_Error_Compositor_Create_Driver_प्रत्यक्षम्_बहुलकम्_Resolve_Textures = 475,
	EVRInit_Error_VRInit_Error_Compositor_Open_Driver_प्रत्यक्षम्_बहुलकम्_Resolve_Textures = 476,
	EVRInitError_VRInitError_Compositor_CreateFallbackSyncTexture = 477,
	EVRInitError_VRInitError_Compositor_ShareFallbackSyncTexture = 478,
	EVRInit_Error_VRInit_Error_Compositor_Create_Overlay_सूचकांक_बफर = 479,
	EVRInit_Error_VRInit_Error_Compositor_Create_Overlay_Vertex_बफर = 480,
	EVRInit_Error_VRInit_Error_Compositor_Create_Text_Vertex_बफर = 481,
	EVRInit_Error_VRInit_Error_Compositor_Create_Text_सूचकांक_बफर = 482,
	EVRInitError_VRInitError_Compositor_CreateMirrorTextures = 483,
	EVRInit_Error_VRInit_Error_Compositor_Create_चरमः_Frame_Render_Texture = 484,
	EVRInitError_VRInitError_Compositor_CreateMirrorOverlay = 485,
	EVRInit_Error_VRInit_Error_Compositor_Failed_गन्तव्यम्_Create_Virtual_Display_Backbuffer = 486,
	EVRInit_Error_VRInit_Error_Compositor_Display_बहुलकम्_Not_Supported = 487,
	EVRInitError_VRInitError_Compositor_CreateOverlayInvalidCall = 488,
	EVRInitError_VRInitError_Compositor_CreateOverlayAlreadyInitialized = 489,
	EVRInit_Error_VRInit_Error_Compositor_Failed_गन्तव्यम्_Create_Mailbox = 490,
	EVRInit_Error_VRInit_Error_Compositor_गवाक्षः_Interface_Is_Null = 491,
	EVRInitError_VRInitError_Compositor_SystemLayerCreateInstance = 492,
	EVRInitError_VRInitError_Compositor_SystemLayerCreateSession = 493,
	EVRInitError_VRInitError_Compoistor_CreateInverseDistortUVs = 494,
	EVRInit_Error_VRInit_Error_Compoistor_Create_Backbuffer_गभीरता = 495,
	EVRInit_Error_VRInit_Error_Vendor_Specific_Unable_गन्तव्यम्_Connect_गन्तव्यम्_Oculus_Runtime = 1000,
	EVRInit_Error_VRInit_Error_Vendor_Specific_Windows_Not_अन्तर्_Dev_बहुलकम् = 1001,
	EVRInitError_VRInitError_VendorSpecific_OculusLinkNotEnabled = 1002,
	EVRInit_Error_VRInit_Error_Vendor_Specific_Hmd_प्राप्तम्_Cant_Open_Device = 1101,
	EVRInit_Error_VRInit_Error_Vendor_Specific_Hmd_प्राप्तम्_Unable_गन्तव्यम्_Request_Config_Start = 1102,
	EVRInit_Error_VRInit_Error_Vendor_Specific_Hmd_प्राप्तम्_No_Stored_Config = 1103,
	EVRInit_Error_VRInit_Error_Vendor_Specific_Hmd_प्राप्तम्_Config_Too_Big = 1104,
	EVRInit_Error_VRInit_Error_Vendor_Specific_Hmd_प्राप्तम्_Config_Too_Small = 1105,
	EVRInit_Error_VRInit_Error_Vendor_Specific_Hmd_प्राप्तम्_Unable_गन्तव्यम्_Init_ZLib = 1106,
	EVRInit_Error_VRInit_Error_Vendor_Specific_Hmd_प्राप्तम्_Cant_Read_Firmware_संस्करणम् = 1107,
	EVRInit_Error_VRInit_Error_Vendor_Specific_Hmd_प्राप्तम्_Unable_गन्तव्यम्_Send_User_दत्त_Start = 1108,
	EVRInit_Error_VRInit_Error_Vendor_Specific_Hmd_प्राप्तम्_Unable_गन्तव्यम्_Get_User_दत्त_Start = 1109,
	EVRInit_Error_VRInit_Error_Vendor_Specific_Hmd_प्राप्तम्_Unable_गन्तव्यम्_Get_User_दत्त_अग्र = 1110,
	EVRInit_Error_VRInit_Error_Vendor_Specific_Hmd_प्राप्तम्_User_दत्त_स्थानाङ्कः_Range = 1111,
	EVRInit_Error_VRInit_Error_Vendor_Specific_Hmd_प्राप्तम्_User_दत्त_Error = 1112,
	EVRInit_Error_VRInit_Error_Vendor_Specific_Hmd_प्राप्तम्_Config_Failed_Sanity_Check = 1113,
	EVRInitError_VRInitError_VendorSpecific_OculusRuntimeBadInstall = 1114,
	EVRInit_Error_VRInit_Error_Vendor_Specific_Hmd_प्राप्तम्_Unexpected_Configuration_1 = 1115,
	EVRInit_Error_VRInit_Error_Steam_Steam_Installation_Not_प्राप्तम् = 2000,
	EVRInit_Error_VRInit_Error_चरमः_Error = 2001,
} EVRInitError;

प्रकारनिर्देश गणना EVRScreenshotType
{
	EVRScreenshotType_VRScreenshotType_None = 0,
	EVRScreenshotType_VRScreenshotType_Mono = 1,
	EVRScreenshotType_VRScreenshotType_Stereo = 2,
	EVRScreenshotType_VRScreenshotType_Cubemap = 3,
	EVRScreenshotType_VRScreenshotType_MonoPanorama = 4,
	EVRScreenshotType_VRScreenshotType_StereoPanorama = 5,
} EVRScreenshotType;

प्रकारनिर्देश गणना EVRScreenshotPropertyFilenames
{
	EVRScreenshotPropertyFilenames_VRScreenshotPropertyFilenames_Preview = 0,
	EVRScreenshotPropertyFilenames_VRScreenshotPropertyFilenames_VR = 1,
} EVRScreenshotPropertyFilenames;

प्रकारनिर्देश गणना EVRTrackedCameraError
{
	EVRTrackedCameraError_VRTrackedCameraError_None = 0,
	EVRTrackedCameraError_VRTrackedCameraError_OperationFailed = 100,
	EVRTrackedCameraError_VRTrackedCameraError_InvalidHandle = 101,
	EVRTracked_Camera_Error_VRTracked_Camera_Error_Invalid_Frame_शीर्षकम्_संस्करणम् = 102,
	EVRTracked_Camera_Error_VRTracked_Camera_Error_बहिर्गमनम्_सम्बन्धि_Handles = 103,
	EVRTrackedCameraError_VRTrackedCameraError_IPCFailure = 104,
	EVRTrackedCameraError_VRTrackedCameraError_NotSupportedForThisDevice = 105,
	EVRTracked_Camera_Error_VRTracked_Camera_Error_Shared_स्मृतिः_Failure = 106,
	EVRTrackedCameraError_VRTrackedCameraError_FrameBufferingFailure = 107,
	EVRTracked_Camera_Error_VRTracked_Camera_Error_प्रवाहः_सज्जता_Failure = 108,
	EVRTrackedCameraError_VRTrackedCameraError_InvalidGLTextureId = 109,
	EVRTrackedCameraError_VRTrackedCameraError_InvalidSharedTextureHandle = 110,
	EVRTracked_Camera_Error_VRTracked_Camera_Error_Failed_गन्तव्यम्_Get_GLTexture_Id = 111,
	EVRTrackedCameraError_VRTrackedCameraError_SharedTextureFailure = 112,
	EVRTracked_Camera_Error_VRTracked_Camera_Error_No_Frame_उपलब्धम् = 113,
	EVRTracked_Camera_Error_VRTracked_Camera_Error_Invalid_तर्कः = 114,
	EVRTracked_Camera_Error_VRTracked_Camera_Error_Invalid_Frame_बफर_आकार = 115,
} EVRTrackedCameraError;

प्रकारनिर्देश गणना EVRTrackedCameraFrameLayout
{
	EVRTrackedCameraFrameLayout_Mono = 1,
	EVRTrackedCameraFrameLayout_Stereo = 2,
	EVRTrackedCameraFrameLayout_VerticalLayout = 16,
	EVRTrackedCameraFrameLayout_HorizontalLayout = 32,
} EVRTrackedCameraFrameLayout;

प्रकारनिर्देश गणना EVRTrackedCameraFrameType
{
	EVRTrackedCameraFrameType_VRTrackedCameraFrameType_Distorted = 0,
	EVRTrackedCameraFrameType_VRTrackedCameraFrameType_Undistorted = 1,
	EVRTracked_Camera_Frame_Type_VRTracked_Camera_Frame_Type_अधिकतमम्_Undistorted = 2,
	EVRTrackedCameraFrameType_MAX_CAMERA_FRAME_TYPES = 3,
} EVRTrackedCameraFrameType;

प्रकारनिर्देश गणना EVRDistortionFunctionType
{
	EVRDistortionFunctionType_VRDistortionFunctionType_None = 0,
	EVRDistortionFunctionType_VRDistortionFunctionType_FTheta = 1,
	EVRDistortionFunctionType_VRDistortionFunctionType_Extended_FTheta = 2,
	EVRDistortionFunctionType_MAX_DISTORTION_FUNCTION_TYPES = 3,
} EVRDistortionFunctionType;

प्रकारनिर्देश गणना EVSync
{
	EVSync_VSync_None = 0,
	EVSync_VSync_WaitRender = 1,
	EVSync_VSync_NoWaitRender = 2,
} EVSync;

प्रकारनिर्देश गणना EVRMura_Correction_बहुलकम्
{
	EVRMura_Correction_बहुलकम्_Default = 0,
	EVRMura_Correction_बहुलकम्_No_Correction = 1,
} EVRMura_Correction_बहुलकम्;

प्रकारनिर्देश गणना Imu_OffScaleFlags
{
	Imu_OffScaleFlags_OffScale_AccelX = 1,
	Imu_OffScaleFlags_OffScale_AccelY = 2,
	Imu_OffScaleFlags_OffScale_AccelZ = 4,
	Imu_OffScaleFlags_OffScale_GyroX = 8,
	Imu_OffScaleFlags_OffScale_GyroY = 16,
	Imu_OffScaleFlags_OffScale_GyroZ = 32,
} Imu_OffScaleFlags;

प्रकारनिर्देश गणना EVRApplicationError
{
	EVRApplicationError_VRApplicationError_None = 0,
	EVRApplication_Error_VRApplication_Error_App_कुञ्चिका_Already_Exists = 100,
	EVRApplicationError_VRApplicationError_NoManifest = 101,
	EVRApplicationError_VRApplicationError_NoApplication = 102,
	EVRApplication_Error_VRApplication_Error_Invalid_सूचकांक = 103,
	EVRApplicationError_VRApplicationError_UnknownApplication = 104,
	EVRApplicationError_VRApplicationError_IPCFailed = 105,
	EVRApplicationError_VRApplicationError_ApplicationAlreadyRunning = 106,
	EVRApplicationError_VRApplicationError_InvalidManifest = 107,
	EVRApplicationError_VRApplicationError_InvalidApplication = 108,
	EVRApplicationError_VRApplicationError_LaunchFailed = 109,
	EVRApplicationError_VRApplicationError_ApplicationAlreadyStarting = 110,
	EVRApplication_Error_VRApplication_Error_Launch_अन्तर्_प्रगतिः = 111,
	EVRApplicationError_VRApplicationError_OldApplicationQuitting = 112,
	EVRApplicationError_VRApplicationError_TransitionAborted = 113,
	EVRApplicationError_VRApplicationError_IsTemplate = 114,
	EVRApplicationError_VRApplicationError_SteamVRIsExiting = 115,
	EVRApplication_Error_VRApplication_Error_बफर_Too_Small = 200,
	EVRApplication_Error_VRApplication_Error_Property_Not_समुच्चयः = 201,
	EVRApplicationError_VRApplicationError_UnknownProperty = 202,
	EVRApplicationError_VRApplicationError_InvalidParameter = 203,
	EVRApplicationError_VRApplicationError_NotImplemented = 300,
} EVRApplicationError;

प्रकारनिर्देश गणना EVRApplicationProperty
{
	EVRApplicationProperty_VRApplicationProperty_Name_String = 0,
	EVRApplicationProperty_VRApplicationProperty_LaunchType_String = 11,
	EVRApplicationProperty_VRApplicationProperty_WorkingDirectory_String = 12,
	EVRApplication_Property_VRApplication_Property_द्विमान_मार्गः_String = 13,
	EVRApplicationProperty_VRApplicationProperty_Arguments_String = 14,
	EVRApplicationProperty_VRApplicationProperty_URL_String = 15,
	EVRApplicationProperty_VRApplicationProperty_Description_String = 50,
	EVRApplicationProperty_VRApplicationProperty_NewsURL_String = 51,
	EVRApplication_Property_VRApplication_Property_Image_मार्गः_String = 52,
	EVRApplicationProperty_VRApplicationProperty_Source_String = 53,
	EVRApplicationProperty_VRApplicationProperty_ActionManifestURL_String = 54,
	EVRApplicationProperty_VRApplicationProperty_IsDashboardOverlay_Bool = 60,
	EVRApplicationProperty_VRApplicationProperty_IsTemplate_Bool = 61,
	EVRApplicationProperty_VRApplicationProperty_IsInstanced_Bool = 62,
	EVRApplication_Property_VRApplication_Property_Is_आन्तरिकम्_Bool = 63,
	EVRApplication_Property_VRApplication_Property_इच्छति_Compositor_Pause_अन्तर्_Standby_Bool = 64,
	EVRApplicationProperty_VRApplicationProperty_IsHidden_Bool = 65,
	EVRApplication_Property_VRApplication_Property_चरमः_Launch_Time_Uint64 = 70,
} EVRApplicationProperty;

प्रकारनिर्देश गणना EVRSceneApplicationState
{
	EVRSceneApplicationState_None = 0,
	EVRSceneApplicationState_Starting = 1,
	EVRSceneApplicationState_Quitting = 2,
	EVRSceneApplicationState_Running = 3,
	EVRScene_Application_State_प्रतीक्षा = 4,
} EVRSceneApplicationState;

प्रकारनिर्देश गणना ChaperoneCalibrationState
{
	ChaperoneCalibrationState_OK = 1,
	ChaperoneCalibrationState_Warning = 100,
	Chaperone_Calibration_State_Warning_आधारः_Station_May_Have_Moved = 101,
	Chaperone_Calibration_State_Warning_आधारः_Station_Removed = 102,
	ChaperoneCalibrationState_Warning_SeatedBoundsInvalid = 103,
	ChaperoneCalibrationState_Error = 200,
	Chaperone_Calibration_State_Error_आधारः_Station_Uninitialized = 201,
	Chaperone_Calibration_State_Error_आधारः_Station_Conflict = 202,
	ChaperoneCalibrationState_Error_PlayAreaInvalid = 203,
	ChaperoneCalibrationState_Error_CollisionBoundsInvalid = 204,
} ChaperoneCalibrationState;

प्रकारनिर्देश गणना EChaperoneConfigFile
{
	EChaperone_Config_File_जीवितम् = 1,
	EChaperone_Config_File_अस्थायी = 2,
} EChaperoneConfigFile;

प्रकारनिर्देश गणना EChaperoneImportFlags
{
	EChaperoneImportFlags_EChaperoneImport_BoundsOnly = 1,
} EChaperoneImportFlags;

प्रकारनिर्देश गणना EVRCompositorError
{
	EVRCompositorError_VRCompositorError_None = 0,
	EVRCompositorError_VRCompositorError_RequestFailed = 1,
	EVRCompositor_Error_VRCompositor_Error_Incompatible_संस्करणम् = 100,
	EVRCompositorError_VRCompositorError_DoNotHaveFocus = 101,
	EVRCompositorError_VRCompositorError_InvalidTexture = 102,
	EVRCompositorError_VRCompositorError_IsNotSceneApplication = 103,
	EVRCompositorError_VRCompositorError_TextureIsOnWrongDevice = 104,
	EVRCompositor_Error_VRCompositor_Error_Texture_उपयुङ्क्ते_Unsupported_Format = 105,
	EVRCompositorError_VRCompositorError_SharedTexturesNotSupported = 106,
	EVRCompositor_Error_VRCompositor_Error_सूचकांक_बहिर्गमनम्_सम्बन्धि_Range = 107,
	EVRCompositorError_VRCompositorError_AlreadySubmitted = 108,
	EVRCompositorError_VRCompositorError_InvalidBounds = 109,
	EVRCompositor_Error_VRCompositor_Error_Already_समुच्चयः = 110,
} EVRCompositorError;

प्रकारनिर्देश गणना EVRCompositor_Timing_बहुलकम्
{
	EVRCompositor_Timing_बहुलकम्_VRCompositor_Timing_बहुलकम्_Implicit = 0,
	EVRCompositor_Timing_बहुलकम्_VRCompositor_Timing_बहुलकम्_Explicit_Runtime_Performs_Post_Present_Handoff = 1,
	EVRCompositor_Timing_बहुलकम्_VRCompositor_Timing_बहुलकम्_Explicit_Application_Performs_Post_Present_Handoff = 2,
} EVRCompositor_Timing_बहुलकम्;

प्रकारनिर्देश गणना VROverlay_निवेशः_विधानम्
{
	VROverlay_निवेशः_विधानम्_None = 0,
	VROverlay_निवेशः_विधानम्_Mouse = 1,
} VROverlay_निवेशः_विधानम्;

प्रकारनिर्देश गणना VROverlayTransformType
{
	VROverlayTransformType_VROverlayTransform_Invalid = -1,
	VROverlayTransformType_VROverlayTransform_Absolute = 0,
	VROverlayTransformType_VROverlayTransform_TrackedDeviceRelative = 1,
	VROverlayTransformType_VROverlayTransform_SystemOverlay = 2,
	VROverlayTransformType_VROverlayTransform_TrackedComponent = 3,
	VROverlayTransformType_VROverlayTransform_Cursor = 4,
	VROverlayTransformType_VROverlayTransform_DashboardTab = 5,
	VROverlayTransformType_VROverlayTransform_DashboardThumb = 6,
	VROverlayTransformType_VROverlayTransform_Mountable = 7,
	VROverlayTransformType_VROverlayTransform_Projection = 8,
} VROverlayTransformType;

प्रकारनिर्देश गणना VROverlayFlags
{
	VROverlayFlags_NoDashboardTab = 8,
	VROverlayFlags_SendVRDiscreteScrollEvents = 64,
	VROverlayFlags_SendVRTouchpadEvents = 128,
	VROverlayFlags_ShowTouchPadScrollWheel = 256,
	VROverlay_Flags_Transfer_Ownership_गन्तव्यम्_आन्तरिकम्_Process = 512,
	VROverlayFlags_SideBySide_Parallel = 1024,
	VROverlayFlags_SideBySide_Crossed = 2048,
	VROverlayFlags_Panorama = 4096,
	VROverlayFlags_StereoPanorama = 8192,
	VROverlay_Flags_क्रमय_With_Non_Scene_Overlays = 16384,
	VROverlay_Flags_Visible_अन्तर्_Dashboard = 32768,
	VROverlayFlags_MakeOverlaysInteractiveIfVisible = 65536,
	VROverlayFlags_SendVRSmoothScrollEvents = 131072,
	VROverlayFlags_ProtectedContent = 262144,
	VROverlayFlags_HideLaserIntersection = 524288,
	VROverlay_Flags_इच्छति_Modal_Behavior = 1048576,
	VROverlayFlags_IsPremultiplied = 2097152,
	VROverlayFlags_IgnoreTextureAlpha = 4194304,
	VROverlayFlags_EnableControlBar = 8388608,
	VROverlayFlags_EnableControlBarKeyboard = 16777216,
	VROverlayFlags_EnableControlBarClose = 33554432,
} VROverlayFlags;

प्रकारनिर्देश गणना VRMessageOverlayResponse
{
	VRMessageOverlayResponse_ButtonPress_0 = 0,
	VRMessageOverlayResponse_ButtonPress_1 = 1,
	VRMessageOverlayResponse_ButtonPress_2 = 2,
	VRMessageOverlayResponse_ButtonPress_3 = 3,
	VRMessageOverlayResponse_CouldntFindSystemOverlay = 4,
	VRMessageOverlayResponse_CouldntFindOrCreateClientOverlay = 5,
	VRMessageOverlayResponse_ApplicationQuit = 6,
} VRMessageOverlayResponse;

प्रकारनिर्देश गणना EGamepad_Text_निवेशः_बहुलकम्
{
	EGamepad_Text_निवेशः_बहुलकम्_k_EGamepad_Text_निवेशः_बहुलकम्_प्रसामान्यम् = 0,
	EGamepad_Text_निवेशः_बहुलकम्_k_EGamepad_Text_निवेशः_बहुलकम्_Password = 1,
	EGamepad_Text_निवेशः_बहुलकम्_k_EGamepad_Text_निवेशः_बहुलकम्_Submit = 2,
} EGamepad_Text_निवेशः_बहुलकम्;

प्रकारनिर्देश गणना EGamepad_Text_निवेशः_पङ्क्तिः_बहुलकम्
{
	EGamepad_Text_निवेशः_पङ्क्तिः_बहुलकम्_k_EGamepad_Text_निवेशः_पङ्क्तिः_बहुलकम्_Single_पङ्क्तिः = 0,
	EGamepad_Text_निवेशः_पङ्क्तिः_बहुलकम्_k_EGamepad_Text_निवेशः_पङ्क्तिः_बहुलकम्_गुणजः_पङ्क्तयः = 1,
} EGamepad_Text_निवेशः_पङ्क्तिः_बहुलकम्;

प्रकारनिर्देश गणना EVROverlay_Intersection_आवरणम्_Primitive_Type
{
	EVROverlay_Intersection_आवरणम्_Primitive_Type_Overlay_Intersection_Primitive_Type_Rectangle = 0,
	EVROverlay_Intersection_आवरणम्_Primitive_Type_Overlay_Intersection_Primitive_Type_Circle = 1,
} EVROverlay_Intersection_आवरणम्_Primitive_Type;

प्रकारनिर्देश गणना EKeyboardFlags
{
	EKeyboard_Flags_Keyboard_Flag_अल्पिष्ठम् = 1,
	EKeyboardFlags_KeyboardFlag_Modal = 2,
} EKeyboardFlags;

प्रकारनिर्देश गणना EDeviceType
{
	EDeviceType_DeviceType_Invalid = -1,
	EDevice_Type_Device_Type_प्रत्यक्षम्_X11 = 0,
	EDeviceType_DeviceType_Vulkan = 1,
} EDeviceType;

प्रकारनिर्देश गणना Headset_View_बहुलकम्_t
{
	Headset_View_बहुलकम्_t_Headset_View_बहुलकम्_वामः = 0,
	Headset_View_बहुलकम्_t_Headset_View_बहुलकम्_दक्षिणः = 1,
	Headset_View_बहुलकम्_t_Headset_View_बहुलकम्_Both = 2,
} Headset_View_बहुलकम्_t;

प्रकारनिर्देश गणना EVRRenderModelError
{
	EVRRenderModelError_VRRenderModelError_None = 0,
	EVRRenderModelError_VRRenderModelError_Loading = 100,
	EVRRenderModelError_VRRenderModelError_NotSupported = 200,
	EVRRenderModelError_VRRenderModelError_InvalidArg = 300,
	EVRRenderModelError_VRRenderModelError_InvalidModel = 301,
	EVRRenderModelError_VRRenderModelError_NoShapes = 302,
	EVRRender_Model_Error_VRRender_Model_Error_गुणजः_Shapes = 303,
	EVRRenderModelError_VRRenderModelError_TooManyVertices = 304,
	EVRRender_Model_Error_VRRender_Model_Error_गुणजः_Textures = 305,
	EVRRender_Model_Error_VRRender_Model_Error_बफर_Too_Small = 306,
	EVRRenderModelError_VRRenderModelError_NotEnoughNormals = 307,
	EVRRenderModelError_VRRenderModelError_NotEnoughTexCoords = 308,
	EVRRenderModelError_VRRenderModelError_InvalidTexture = 400,
} EVRRenderModelError;

प्रकारनिर्देश गणना EVRRenderModelTextureFormat
{
	EVRRenderModelTextureFormat_VRRenderModelTextureFormat_RGBA8_SRGB = 0,
	EVRRenderModelTextureFormat_VRRenderModelTextureFormat_BC2 = 1,
	EVRRenderModelTextureFormat_VRRenderModelTextureFormat_BC4 = 2,
	EVRRenderModelTextureFormat_VRRenderModelTextureFormat_BC7 = 3,
	EVRRenderModelTextureFormat_VRRenderModelTextureFormat_BC7_SRGB = 4,
	EVRRenderModelTextureFormat_VRRenderModelTextureFormat_RGBA16_FLOAT = 5,
} EVRRenderModelTextureFormat;

प्रकारनिर्देश गणना EVRNotificationType
{
	EVRNotificationType_Transient = 0,
	EVRNotificationType_Persistent = 1,
	EVRNotification_Type_Transient_System_With_User_मानम् = 2,
} EVRNotificationType;

प्रकारनिर्देश गणना EVRNotificationStyle
{
	EVRNotificationStyle_None = 0,
	EVRNotificationStyle_Application = 100,
	EVRNotificationStyle_Contact_Disabled = 200,
	EVRNotificationStyle_Contact_Enabled = 201,
	EVRNotification_Style_Contact_सक्रिय = 202,
} EVRNotificationStyle;

प्रकारनिर्देश गणना EVRSettingsError
{
	EVRSettingsError_VRSettingsError_None = 0,
	EVRSettingsError_VRSettingsError_IPCFailed = 1,
	EVRSettingsError_VRSettingsError_WriteFailed = 2,
	EVRSettingsError_VRSettingsError_ReadFailed = 3,
	EVRSettingsError_VRSettingsError_JsonParseFailed = 4,
	EVRSettingsError_VRSettingsError_UnsetSettingHasNoDefault = 5,
} EVRSettingsError;

प्रकारनिर्देश गणना EVRScreenshotError
{
	EVRScreenshotError_VRScreenshotError_None = 0,
	EVRScreenshotError_VRScreenshotError_RequestFailed = 1,
	EVRScreenshot_Error_VRScreenshot_Error_Incompatible_संस्करणम् = 100,
	EVRScreenshot_Error_VRScreenshot_Error_Not_प्राप्तम् = 101,
	EVRScreenshot_Error_VRScreenshot_Error_बफर_Too_Small = 102,
	EVRScreenshot_Error_VRScreenshot_Error_Screenshot_Already_अन्तर्_प्रगतिः = 108,
} EVRScreenshotError;

प्रकारनिर्देश गणना EVRSkeletalTransformSpace
{
	EVRSkeletalTransformSpace_VRSkeletalTransformSpace_Model = 0,
	EVRSkeletalTransformSpace_VRSkeletalTransformSpace_Parent = 1,
} EVRSkeletalTransformSpace;

प्रकारनिर्देश गणना EVRSkeletalReferencePose
{
	EVRSkeletalReferencePose_VRSkeletalReferencePose_BindPose = 0,
	EVRSkeletalReferencePose_VRSkeletalReferencePose_OpenHand = 1,
	EVRSkeletalReferencePose_VRSkeletalReferencePose_Fist = 2,
	EVRSkeletal_Reference_Pose_VRSkeletal_Reference_Pose_Grip_सीमा = 3,
} EVRSkeletalReferencePose;

प्रकारनिर्देश गणना EVRFinger
{
	EVRFinger_VRFinger_Thumb = 0,
	EVRFinger_VRFinger_सूचकांक = 1,
	EVRFinger_VRFinger_मध्यः = 2,
	EVRFinger_VRFinger_Ring = 3,
	EVRFinger_VRFinger_Pinky = 4,
	EVRFinger_VRFinger_गणनम् = 5,
} EVRFinger;

प्रकारनिर्देश गणना EVRFingerSplay
{
	EVRFinger_Splay_VRFinger_Splay_Thumb_सूचकांक = 0,
	EVRFinger_Splay_VRFinger_Splay_सूचकांक_मध्यः = 1,
	EVRFinger_Splay_VRFinger_Splay_मध्यः_Ring = 2,
	EVRFingerSplay_VRFingerSplay_Ring_Pinky = 3,
	EVRFinger_Splay_VRFinger_Splay_गणनम् = 4,
} EVRFingerSplay;

प्रकारनिर्देश गणना EVRSummaryType
{
	EVRSummaryType_VRSummaryType_FromAnimation = 0,
	EVRSummaryType_VRSummaryType_FromDevice = 1,
} EVRSummaryType;

प्रकारनिर्देश गणना EVRInputFilterCancelType
{
	EVRInputFilterCancelType_VRInputFilterCancel_Timers = 0,
	EVRInputFilterCancelType_VRInputFilterCancel_Momentum = 1,
} EVRInputFilterCancelType;

प्रकारनिर्देश गणना EVRInput_String_द्वयङ्काः
{
	EVRInput_String_द्वयङ्काः_VRInput_String_Hand = 1,
	EVRInput_String_द्वयङ्काः_VRInput_String_Controller_Type = 2,
	EVRInput_String_द्वयङ्काः_VRInput_String_निवेशः_Source = 4,
	EVRInput_String_द्वयङ्काः_VRInput_String_All = -1,
} EVRInput_String_द्वयङ्काः;

प्रकारनिर्देश गणना EIOBufferError
{
	EIOBufferError_IOBuffer_Success = 0,
	EIOBufferError_IOBuffer_OperationFailed = 100,
	EIOBufferError_IOBuffer_InvalidHandle = 101,
	EIOBuffer_Error_IOBuffer_Invalid_तर्कः = 102,
	EIOBuffer_Error_IOBuffer_मार्गः_Exists = 103,
	EIOBuffer_Error_IOBuffer_मार्गः_Does_Not_Exist = 104,
	EIOBufferError_IOBuffer_Permission = 105,
} EIOBufferError;

प्रकारनिर्देश गणना EIOBuffer_बहुलकम्
{
	EIOBuffer_बहुलकम्_IOBuffer_बहुलकम्_Read = 1,
	EIOBuffer_बहुलकम्_IOBuffer_बहुलकम्_Write = 2,
	EIOBuffer_बहुलकम्_IOBuffer_बहुलकम्_Create = 512,
} EIOBuffer_बहुलकम्;

प्रकारनिर्देश गणना EVRDebugError
{
	EVRDebugError_VRDebugError_Success = 0,
	EVRDebugError_VRDebugError_BadParameter = 1,
} EVRDebugError;

प्रकारनिर्देश गणना EPropertyWriteType
{
	EProperty_Write_Type_Property_Write_समुच्चयः = 0,
	EPropertyWriteType_PropertyWrite_Erase = 1,
	EProperty_Write_Type_Property_Write_समुच्चयः_Error = 2,
} EPropertyWriteType;

प्रकारनिर्देश गणना EBlockQueueError
{
	EBlock_Queue_Error_खण्डम्_Queue_Error_None = 0,
	EBlock_Queue_Error_खण्डम्_Queue_Error_Queue_Already_Exists = 1,
	EBlock_Queue_Error_खण्डम्_Queue_Error_Queue_Not_प्राप्तम् = 2,
	EBlock_Queue_Error_खण्डम्_Queue_Error_खण्डम्_Not_उपलब्धम् = 3,
	EBlock_Queue_Error_खण्डम्_Queue_Error_Invalid_Handle = 4,
	EBlock_Queue_Error_खण्डम्_Queue_Error_Invalid_Param = 5,
	EBlock_Queue_Error_खण्डम्_Queue_Error_Param_Mismatch = 6,
	EBlock_Queue_Error_खण्डम्_Queue_Error_आन्तरिकम्_Error = 7,
	EBlock_Queue_Error_खण्डम्_Queue_Error_Already_Initialized = 8,
	EBlock_Queue_Error_खण्डम्_Queue_Error_Operation_Is_Server_Only = 9,
	EBlock_Queue_Error_खण्डम्_Queue_Error_Too_Many_Connections = 10,
} EBlockQueueError;

प्रकारनिर्देश गणना EBlockQueueReadType
{
	EBlock_Queue_Read_Type_खण्डम्_Queue_Read_Latest = 0,
	EBlock_Queue_Read_Type_खण्डम्_Queue_Read_New = 1,
	EBlock_Queue_Read_Type_खण्डम्_Queue_Read_अग्र = 2,
} EBlockQueueReadType;

प्रकारनिर्देश गणना EBlockQueueCreationFlag
{
	EBlock_Queue_Creation_Flag_खण्डम्_Queue_Flag_Owner_Is_Reader = 1,
} EBlockQueueCreationFlag;


// OpenVR typedefs

प्रकारनिर्देश uint32_t Property_Type_चिह्नकम्_t;
प्रकारनिर्देश uint32_t SpatialAnchorHandle_t;
प्रकारनिर्देश शून्य * glSharedTextureHandle_t;
प्रकारनिर्देश int32_t glInt_t;
प्रकारनिर्देश uint32_t glUInt_t;
प्रकारनिर्देश uint64_t SharedTextureHandle_t;
प्रकारनिर्देश uint32_t DriverId_t;
प्रकारनिर्देश uint32_t Tracked_Device_सूचकांक_t;
प्रकारनिर्देश uint64_t WebConsoleHandle_t;
प्रकारनिर्देश uint64_t PropertyContainerHandle_t;
प्रकारनिर्देश PropertyContainerHandle_t DriverHandle_t;
प्रकारनिर्देश uint64_t VRActionHandle_t;
प्रकारनिर्देश uint64_t VRAction_समुच्चयः_Handle_t;
प्रकारनिर्देश uint64_t VRInput_मानम्_Handle_t;
प्रकारनिर्देश uint32_t VRComponentProperties;
प्रकारनिर्देश uint64_t VROverlayHandle_t;
प्रकारनिर्देश int32_t Bone_सूचकांक_t;
प्रकारनिर्देश uint64_t TrackedCameraHandle_t;
प्रकारनिर्देश uint32_t ScreenshotHandle_t;
प्रकारनिर्देश int32_t TextureID_t;
प्रकारनिर्देश uint32_t VRNotificationId;
प्रकारनिर्देश uint64_t IOBufferHandle_t;
प्रकारनिर्देश uint64_t VrProfilerEventHandle_t;
प्रकारनिर्देश EVRInitError HmdError;
प्रकारनिर्देश EVREye Hmd_Eye;
प्रकारनिर्देश EColorSpace ColorSpace;
प्रकारनिर्देश ETracking_परिणाम Hmd_Tracking_परिणाम;
प्रकारनिर्देश ETrackedDeviceClass TrackedDeviceClass;
प्रकारनिर्देश ETrackingUniverseOrigin TrackingUniverseOrigin;
प्रकारनिर्देश ETrackedDeviceProperty TrackedDeviceProperty;
प्रकारनिर्देश ETrackedPropertyError TrackedPropertyError;
प्रकारनिर्देश EVRSubmitFlags VRSubmitFlags_t;
प्रकारनिर्देश EVRState VRState_t;
प्रकारनिर्देश ECollisionBoundsStyle CollisionBoundsStyle_t;
प्रकारनिर्देश EVROverlayError VROverlayError;
प्रकारनिर्देश EVRFirmwareError VRFirmwareError;
प्रकारनिर्देश EVRCompositorError VRCompositorError;
प्रकारनिर्देश EVRScreenshotError VRScreenshotsError;
प्रकारनिर्देश uint64_t मार्गः_Handle_t;

// OpenVR Structs

प्रकारनिर्देश संरचना HmdMatrix34_t
{
	भिन्न m[3][4]; //float[3][4]
} HmdMatrix34_t;

प्रकारनिर्देश संरचना HmdMatrix33_t
{
	भिन्न m[3][3]; //float[3][3]
} HmdMatrix33_t;

प्रकारनिर्देश संरचना HmdMatrix44_t
{
	भिन्न m[4][4]; //float[4][4]
} HmdMatrix44_t;

प्रकारनिर्देश संरचना HmdVector3_t
{
	भिन्न v[3]; //float[3]
} HmdVector3_t;

प्रकारनिर्देश संरचना HmdVector4_t
{
	भिन्न v[4]; //float[4]
} HmdVector4_t;

प्रकारनिर्देश संरचना HmdVector3d_t
{
	द्विगुण v[3]; //double[3]
} HmdVector3d_t;

प्रकारनिर्देश संरचना HmdVector2_t
{
	भिन्न v[2]; //float[2]
} HmdVector2_t;

प्रकारनिर्देश संरचना HmdQuaternion_t
{
	द्विगुण w;
	द्विगुण x;
	द्विगुण y;
	द्विगुण z;
} HmdQuaternion_t;

प्रकारनिर्देश संरचना HmdQuaternionf_t
{
	भिन्न w;
	भिन्न x;
	भिन्न y;
	भिन्न z;
} HmdQuaternionf_t;

प्रकारनिर्देश संरचना HmdColor_t
{
	भिन्न r;
	भिन्न g;
	भिन्न b;
	भिन्न a;
} HmdColor_t;

प्रकारनिर्देश संरचना HmdQuad_t
{
	संरचना HmdVector3_t vCorners[4]; //struct vr::HmdVector3_t[4]
} HmdQuad_t;

प्रकारनिर्देश संरचना HmdRect2_t
{
	संरचना HmdVector2_t v_शिखरम्_वामः;
	संरचना HmdVector2_t v_Bottom_दक्षिणः;
} HmdRect2_t;

प्रकारनिर्देश संरचना VRBoneTransform_t
{
	संरचना HmdVector4_t position;
	संरचना HmdQuaternionf_t orientation;
} VRBoneTransform_t;

प्रकारनिर्देश संरचना DistortionCoordinates_t
{
	भिन्न rfRed[2]; //float[2]
	भिन्न rfGreen[2]; //float[2]
	भिन्न rfBlue[2]; //float[2]
} DistortionCoordinates_t;

प्रकारनिर्देश संरचना Texture_t
{
	शून्य * handle; // void *
	गणना ETextureType eType;
	गणना EColorSpace eColorSpace;
} Texture_t;

प्रकारनिर्देश संरचना TrackedDevicePose_t
{
	संरचना HmdMatrix34_t m_Device_गन्तव्यम्_Absolute_Tracking;
	संरचना HmdVector3_t vVelocity;
	संरचना HmdVector3_t vAngularVelocity;
	गणना ETracking_परिणाम e_Tracking_परिणाम;
	bool bPoseIsValid;
	bool bDeviceIsConnected;
} TrackedDevicePose_t;

प्रकारनिर्देश संरचना VRTextureBounds_t
{
	भिन्न uMin;
	भिन्न vMin;
	भिन्न uMax;
	भिन्न vMax;
} VRTextureBounds_t;

प्रकारनिर्देश संरचना VRTextureWithPose_t
{
	शून्य * handle; // void *
	गणना ETextureType eType;
	गणना EColorSpace eColorSpace;
	संरचना HmdMatrix34_t m_Device_गन्तव्यम्_Absolute_Tracking;
} VRTextureWithPose_t;

प्रकारनिर्देश संरचना VRTexture_गभीरता_Info_t
{
	शून्य * handle; // void *
	संरचना HmdMatrix44_t mProjection;
	संरचना HmdVector2_t vRange;
} VRTexture_गभीरता_Info_t;

प्रकारनिर्देश संरचना VRTexture_With_गभीरता_t
{
	शून्य * handle; // void *
	गणना ETextureType eType;
	गणना EColorSpace eColorSpace;
	संरचना VRTexture_गभीरता_Info_t गभीरता_2;
} VRTexture_With_गभीरता_t;

प्रकारनिर्देश संरचना VRTexture_With_Pose_And_गभीरता_t
{
	शून्य * handle; // void *
	गणना ETextureType eType;
	गणना EColorSpace eColorSpace;
	संरचना HmdMatrix34_t m_Device_गन्तव्यम्_Absolute_Tracking;
	संरचना VRTexture_गभीरता_Info_t गभीरता_2;
} VRTexture_With_Pose_And_गभीरता_t;

प्रकारनिर्देश संरचना VRVulkan_Texture_दत्त_t
{
	uint64_t m_nImage;
	संरचना VkDevice_T * m_pDevice; // struct VkDevice_T *
	संरचना VkPhysicalDevice_T * m_pPhysicalDevice; // struct VkPhysicalDevice_T *
	संरचना VkInstance_T * m_pInstance; // struct VkInstance_T *
	संरचना VkQueue_T * m_pQueue; // struct VkQueue_T *
	uint32_t m_n_Queue_Family_सूचकांक;
	uint32_t m_n_विस्तारः;
	uint32_t m_nHeight;
	uint32_t m_nFormat;
	uint32_t m_n_Sample_गणनम्;
} VRVulkan_Texture_दत्त_t;

प्रकारनिर्देश संरचना VRVulkan_Texture_Array_दत्त_t
{
	uint32_t m_un_Array_सूचकांक;
	uint32_t m_un_Array_आकार;
} VRVulkan_Texture_Array_दत्त_t;

प्रकारनिर्देश संरचना D3_D12_Texture_दत्त_t
{
	संरचना ID3D12Resource * m_pResource; // struct ID3D12Resource *
	संरचना ID3D12CommandQueue * m_pCommandQueue; // struct ID3D12CommandQueue *
	uint32_t m_n_ग्रन्थिः_आवरणम्;
} D3_D12_Texture_दत्त_t;

प्रकारनिर्देश संरचना VREvent_Controller_t
{
	uint32_t button;
} VREvent_Controller_t;

प्रकारनिर्देश संरचना VREvent_Mouse_t
{
	भिन्न x;
	भिन्न y;
	uint32_t button;
} VREvent_Mouse_t;

प्रकारनिर्देश संरचना VREvent_Scroll_t
{
	भिन्न xdelta;
	भिन्न ydelta;
	uint32_t अप्रयुक्तम्;
	भिन्न viewportscale;
} VREvent_Scroll_t;

प्रकारनिर्देश संरचना VREvent_TouchPadMove_t
{
	bool b_Finger_अधस्तात्;
	भिन्न fl_Seconds_Finger_अधस्तात्;
	भिन्न f_मानम्_XFirst;
	भिन्न f_मानम्_YFirst;
	भिन्न f_मानम्_XRaw;
	भिन्न f_मानम्_YRaw;
} VREvent_TouchPadMove_t;

प्रकारनिर्देश संरचना VREvent_Notification_t
{
	uint64_t ul_User_मानम्;
	uint32_t notificationId;
} VREvent_Notification_t;

प्रकारनिर्देश संरचना VREvent_Process_t
{
	uint32_t pid;
	uint32_t oldPid;
	bool bForced;
	bool b_Connection_नष्टम्;
} VREvent_Process_t;

प्रकारनिर्देश संरचना VREvent_Overlay_t
{
	uint64_t overlayHandle;
	uint64_t device_मार्गः;
	uint64_t स्मृतिः_खण्डम्_Id;
} VREvent_Overlay_t;

प्रकारनिर्देश संरचना VREvent_स्थितिः_t
{
	uint32_t स्थितिः_State;
} VREvent_स्थितिः_t;

प्रकारनिर्देश संरचना VREvent_Keyboard_t
{
	वर्ण c_New_निवेशः[8]; //char[8]
	uint64_t u_User_मानम्;
} VREvent_Keyboard_t;

प्रकारनिर्देश संरचना VREvent_Ipd_t
{
	भिन्न ipdMeters;
} VREvent_Ipd_t;

प्रकारनिर्देश संरचना VREvent_Chaperone_t
{
	uint64_t m_nPreviousUniverse;
	uint64_t m_nCurrentUniverse;
} VREvent_Chaperone_t;

प्रकारनिर्देश संरचना VREvent_Reserved_t
{
	uint64_t reserved0;
	uint64_t reserved1;
	uint64_t reserved2;
	uint64_t reserved3;
	uint64_t reserved4;
	uint64_t reserved5;
} VREvent_Reserved_t;

प्रकारनिर्देश संरचना VREvent_PerformanceTest_t
{
	uint32_t m_nFidelityLevel;
} VREvent_PerformanceTest_t;

प्रकारनिर्देश संरचना VREvent_SeatedZeroPoseReset_t
{
	bool bResetBySystemMenu;
} VREvent_SeatedZeroPoseReset_t;

प्रकारनिर्देश संरचना VREvent_Screenshot_t
{
	uint32_t handle;
	uint32_t type;
} VREvent_Screenshot_t;

प्रकारनिर्देश संरचना VREvent_Screenshot_प्रगतिः_t
{
	भिन्न प्रगतिः_2;
} VREvent_Screenshot_प्रगतिः_t;

प्रकारनिर्देश संरचना VREvent_ApplicationLaunch_t
{
	uint32_t pid;
	uint32_t un_तर्काः_Handle;
} VREvent_ApplicationLaunch_t;

प्रकारनिर्देश संरचना VREvent_EditingCameraSurface_t
{
	uint64_t overlayHandle;
	uint32_t n_Visual_बहुलकम्;
} VREvent_EditingCameraSurface_t;

प्रकारनिर्देश संरचना VREvent_सन्देशः_Overlay_t
{
	uint32_t unVRMessageOverlayResponse;
} VREvent_सन्देशः_Overlay_t;

प्रकारनिर्देश संरचना VREvent_Property_t
{
	PropertyContainerHandle_t container;
	गणना ETrackedDeviceProperty prop;
} VREvent_Property_t;

प्रकारनिर्देश संरचना VREvent_HapticVibration_t
{
	uint64_t containerHandle;
	uint64_t componentHandle;
	भिन्न fDurationSeconds;
	भिन्न fFrequency;
	भिन्न fAmplitude;
} VREvent_HapticVibration_t;

प्रकारनिर्देश संरचना VREvent_WebConsole_t
{
	WebConsoleHandle_t webConsoleHandle;
} VREvent_WebConsole_t;

प्रकारनिर्देश संरचना VREvent_निवेशः_Binding_आरोपय_t
{
	PropertyContainerHandle_t ulAppContainer;
	uint64_t मार्गः_सन्देशः;
	uint64_t मार्गः_Url;
	uint64_t मार्गः_Controller_Type;
} VREvent_निवेशः_Binding_आरोपय_t;

प्रकारनिर्देश संरचना VREvent_निवेशः_Action_Manifest_आरोपय_t
{
	uint64_t मार्गः_App_कुञ्चिका;
	uint64_t मार्गः_सन्देशः;
	uint64_t मार्गः_सन्देशः_Param;
	uint64_t मार्गः_Manifest_मार्गः;
} VREvent_निवेशः_Action_Manifest_आरोपय_t;

प्रकारनिर्देश संरचना VREvent_SpatialAnchor_t
{
	SpatialAnchorHandle_t unHandle;
} VREvent_SpatialAnchor_t;

प्रकारनिर्देश संरचना VREvent_प्रगतिः_Update_t
{
	uint64_t ulApplicationPropertyContainer;
	uint64_t मार्गः_Device;
	uint64_t मार्गः_निवेशः_Source;
	uint64_t मार्गः_प्रगतिः_Action;
	uint64_t मार्गः_Icon;
	भिन्न f_प्रगतिः;
} VREvent_प्रगतिः_Update_t;

प्रकारनिर्देश संरचना VREvent_ShowUI_t
{
	गणना EShowUIType eType;
} VREvent_ShowUI_t;

प्रकारनिर्देश संरचना VREvent_ShowDevTools_t
{
	int32_t nBrowserIdentifier;
} VREvent_ShowDevTools_t;

प्रकारनिर्देश संरचना VREvent_HDCPError_t
{
	गणना EHDCPError e_संहिता;
} VREvent_HDCPError_t;

प्रकारनिर्देश संरचना RenderModel_ComponentState_t
{
	संरचना HmdMatrix34_t m_Tracking_गन्तव्यम्_Component_Render_Model;
	संरचना HmdMatrix34_t m_Tracking_गन्तव्यम्_Component_Local;
	VRComponentProperties uProperties;
} RenderModel_ComponentState_t;

प्रकारनिर्देश संरचना HiddenAreaMesh_t
{
	संरचना HmdVector2_t * p_Vertex_दत्त; // const struct vr::HmdVector2_t *
	uint32_t un_Triangle_गणनम्;
} HiddenAreaMesh_t;

प्रकारनिर्देश संरचना VRControllerAxis_t
{
	भिन्न x;
	भिन्न y;
} VRControllerAxis_t;

प्रकारनिर्देश संरचना VRControllerState_t
{
	uint32_t un_Packet_अङ्कः;
	uint64_t ulButtonPressed;
	uint64_t ulButtonTouched;
	संरचना VRControllerAxis_t rAxis[5]; //struct vr::VRControllerAxis_t[5]
} VRControllerState_t;

प्रकारनिर्देश संरचना Camera_Video_प्रवाहः_Frame_शीर्षकम्_t
{
	गणना EVRTrackedCameraFrameType eFrameType;
	uint32_t n_विस्तारः;
	uint32_t nHeight;
	uint32_t n_अष्टकानि_प्रत्येकम्_Pixel;
	uint32_t nFrameSequence;
	संरचना TrackedDevicePose_t trackedDevicePose;
	uint64_t ulFrameExposureTime;
} Camera_Video_प्रवाहः_Frame_शीर्षकम्_t;

प्रकारनिर्देश संरचना Compositor_FrameTiming
{
	uint32_t m_n_आकार;
	uint32_t m_n_Frame_सूचकांक;
	uint32_t m_n_अङ्कः_Frame_Presents;
	uint32_t m_n_अङ्कः_Mis_Presented;
	uint32_t m_n_अङ्कः_Dropped_चौकटाः;
	uint32_t m_nReprojectionFlags;
	द्विगुण m_fl_System_Time_अन्तर्_Seconds;
	भिन्न m_flPreSubmitGpuMs;
	भिन्न m_flPostSubmitGpuMs;
	भिन्न m_fl_योग_Render_Gpu_Ms;
	भिन्न m_flCompositorRenderGpuMs;
	भिन्न m_flCompositorRenderCpuMs;
	भिन्न m_flCompositorIdleCpuMs;
	भिन्न m_flClientFrameIntervalMs;
	भिन्न m_flPresentCallCpuMs;
	भिन्न m_flWaitForPresentCpuMs;
	भिन्न m_flSubmitFrameMs;
	भिन्न m_flWaitGetPosesCalledMs;
	भिन्न m_flNewPosesReadyMs;
	भिन्न m_flNewFrameReadyMs;
	भिन्न m_flCompositorUpdateStartMs;
	भिन्न m_fl_Compositor_Update_अन्तः_Ms;
	भिन्न m_flCompositorRenderStartMs;
	TrackedDevicePose_t m_HmdPose;
	uint32_t m_n_अङ्कः_VSyncs_Ready_For_Use;
	uint32_t m_n_अङ्कः_VSyncs_गन्तव्यम्_First_View;
} Compositor_FrameTiming;

प्रकारनिर्देश संरचना Compositor_BenchmarkResults
{
	भिन्न m_fl_Mega_Pixels_प्रत्येकम्_Second;
	भिन्न m_fl_Hmd_Recommended_Mega_Pixels_प्रत्येकम्_Second;
} Compositor_BenchmarkResults;

प्रकारनिर्देश संरचना Driver_प्रत्यक्षम्_बहुलकम्_Frame_Timing
{
	uint32_t m_n_आकार;
	uint32_t m_n_अङ्कः_Frame_Presents;
	uint32_t m_n_अङ्कः_Mis_Presented;
	uint32_t m_n_अङ्कः_Dropped_चौकटाः;
	uint32_t m_nReprojectionFlags;
} Driver_प्रत्यक्षम्_बहुलकम्_Frame_Timing;

प्रकारनिर्देश संरचना ImuSample_t
{
	द्विगुण fSampleTime;
	संरचना HmdVector3d_t vAccel;
	संरचना HmdVector3d_t vGyro;
	uint32_t unOffScaleFlags;
} ImuSample_t;

प्रकारनिर्देश संरचना App_Override_कुञ्चिकाः_t
{
	वर्ण * pch_कुञ्चिका; // const char *
	वर्ण * pch_मानम्; // const char *
} App_Override_कुञ्चिकाः_t;

प्रकारनिर्देश संरचना Compositor_CumulativeStats
{
	uint32_t m_nPid;
	uint32_t m_n_अङ्कः_Frame_Presents;
	uint32_t m_n_अङ्कः_Dropped_चौकटाः;
	uint32_t m_n_अङ्कः_Reprojected_चौकटाः;
	uint32_t m_n_अङ्कः_Frame_Presents_On_Startup;
	uint32_t m_n_अङ्कः_Dropped_चौकटाः_On_Startup;
	uint32_t m_n_अङ्कः_Reprojected_चौकटाः_On_Startup;
	uint32_t m_n_अङ्कः_Loading;
	uint32_t m_n_अङ्कः_Frame_Presents_Loading;
	uint32_t m_n_अङ्कः_Dropped_चौकटाः_Loading;
	uint32_t m_n_अङ्कः_Reprojected_चौकटाः_Loading;
	uint32_t m_n_अङ्कः_Timed_बहिर्गमनम्;
	uint32_t m_n_अङ्कः_Frame_Presents_Timed_बहिर्गमनम्;
	uint32_t m_n_अङ्कः_Dropped_चौकटाः_Timed_बहिर्गमनम्;
	uint32_t m_n_अङ्कः_Reprojected_चौकटाः_Timed_बहिर्गमनम्;
	uint32_t m_n_अङ्कः_Frame_Submits;
	द्विगुण m_fl_योग_Compositor_CPUTime_MS;
	द्विगुण m_fl_योग_Compositor_GPUTime_MS;
	द्विगुण m_fl_योग_Target_Frame_Times;
	द्विगुण m_fl_योग_Application_CPUTime_MS;
	द्विगुण m_fl_योग_Application_GPUTime_MS;
} Compositor_CumulativeStats;

प्रकारनिर्देश संरचना Compositor_StageRenderSettings
{
	संरचना HmdColor_t m_PrimaryColor;
	संरचना HmdColor_t m_SecondaryColor;
	भिन्न m_flVignetteInnerRadius;
	भिन्न m_flVignetteOuterRadius;
	भिन्न m_flFresnelStrength;
	bool m_bBackfaceCulling;
	bool m_bGreyscale;
	bool m_bWireframe;
} Compositor_StageRenderSettings;

प्रकारनिर्देश संरचना VROverlayIntersectionParams_t
{
	संरचना HmdVector3_t vSource;
	संरचना HmdVector3_t vDirection;
	गणना ETrackingUniverseOrigin eOrigin;
} VROverlayIntersectionParams_t;

प्रकारनिर्देश संरचना VROverlayIntersectionResults_t
{
	संरचना HmdVector3_t vPoint;
	संरचना HmdVector3_t v_प्रसामान्यम्;
	संरचना HmdVector2_t vUVs;
	भिन्न fDistance;
} VROverlayIntersectionResults_t;

प्रकारनिर्देश संरचना Intersection_आवरणम्_Rectangle_t
{
	भिन्न m_fl_शिखरम्_वामः_X;
	भिन्न m_fl_शिखरम्_वामः_Y;
	भिन्न m_fl_विस्तारः;
	भिन्न m_flHeight;
} Intersection_आवरणम्_Rectangle_t;

प्रकारनिर्देश संरचना Intersection_आवरणम्_Circle_t
{
	भिन्न m_flCenterX;
	भिन्न m_flCenterY;
	भिन्न m_flRadius;
} Intersection_आवरणम्_Circle_t;

प्रकारनिर्देश संरचना VROverlayProjection_t
{
	भिन्न f_वामः;
	भिन्न f_दक्षिणः;
	भिन्न f_शिखरम्;
	भिन्न fBottom;
} VROverlayProjection_t;

प्रकारनिर्देश संरचना VROverlayView_t
{
	VROverlayHandle_t overlayHandle;
	संरचना Texture_t texture;
	संरचना VRTextureBounds_t textureBounds;
} VROverlayView_t;

प्रकारनिर्देश संरचना VRVulkanDevice_t
{
	संरचना VkInstance_T * m_pInstance; // struct VkInstance_T *
	संरचना VkDevice_T * m_pDevice; // struct VkDevice_T *
	संरचना VkPhysicalDevice_T * m_pPhysicalDevice; // struct VkPhysicalDevice_T *
	संरचना VkQueue_T * m_pQueue; // struct VkQueue_T *
	uint32_t m_u_Queue_Family_सूचकांक;
} VRVulkanDevice_t;

प्रकारनिर्देश संरचना VRNativeDevice_t
{
	शून्य * handle; // void *
	गणना EDeviceType eType;
} VRNativeDevice_t;

प्रकारनिर्देश संरचना RenderModel_Vertex_t
{
	संरचना HmdVector3_t vPosition;
	संरचना HmdVector3_t v_प्रसामान्यम्;
	भिन्न rfTextureCoord[2]; //float[2]
} RenderModel_Vertex_t;

#यदि defined(__linux__) || defined(__APPLE__)
#निर्देशः pack( प्रक्षिप, 4 )
#यदि_अन्तः
प्रकारनिर्देश संरचना RenderModel_TextureMap_t
{
	uint16_t un_विस्तारः;
	uint16_t unHeight;
	uint8_t * rub_Texture_Map_दत्त; // const uint8_t *
	गणना EVRRenderModelTextureFormat format;
	uint16_t un_Mip_स्तराः;
} RenderModel_TextureMap_t;

#यदि defined(__linux__) || defined(__APPLE__)
#निर्देशः pack( निष्कासय )
#यदि_अन्तः
#यदि defined(__linux__) || defined(__APPLE__)
#निर्देशः pack( प्रक्षिप, 4 )
#यदि_अन्तः
प्रकारनिर्देश संरचना RenderModel_t
{
	संरचना RenderModel_Vertex_t * r_Vertex_दत्त; // const struct vr::RenderModel_Vertex_t *
	uint32_t un_Vertex_गणनम्;
	uint16_t * r_सूचकांक_दत्त; // const uint16_t *
	uint32_t un_Triangle_गणनम्;
	TextureID_t diffuseTextureId;
} RenderModel_t;

#यदि defined(__linux__) || defined(__APPLE__)
#निर्देशः pack( निष्कासय )
#यदि_अन्तः
प्रकारनिर्देश संरचना Render_Model_Controller_बहुलकम्_State_t
{
	bool bScrollWheelVisible;
} Render_Model_Controller_बहुलकम्_State_t;

प्रकारनिर्देश संरचना NotificationBitmap_t
{
	शून्य * m_p_Image_दत्त; // void *
	int32_t m_n_विस्तारः;
	int32_t m_nHeight;
	int32_t m_n_अष्टकानि_प्रत्येकम्_Pixel;
} NotificationBitmap_t;

प्रकारनिर्देश संरचना CVRSettingHelper
{
	intptr_t m_pSettings; // class vr::IVRSettings *
} CVRSettingHelper;

प्रकारनिर्देश संरचना निवेशः_Analog_Action_दत्त_t
{
	bool b_सक्रिय;
	VRInput_मानम्_Handle_t सक्रिय_Origin;
	भिन्न x;
	भिन्न y;
	भिन्न z;
	भिन्न deltaX;
	भिन्न deltaY;
	भिन्न deltaZ;
	भिन्न fUpdateTime;
} निवेशः_Analog_Action_दत्त_t;

प्रकारनिर्देश संरचना निवेशः_Digital_Action_दत्त_t
{
	bool b_सक्रिय;
	VRInput_मानम्_Handle_t सक्रिय_Origin;
	bool bState;
	bool b_परिवर्तितम्;
	भिन्न fUpdateTime;
} निवेशः_Digital_Action_दत्त_t;

प्रकारनिर्देश संरचना निवेशः_Pose_Action_दत्त_t
{
	bool b_सक्रिय;
	VRInput_मानम्_Handle_t सक्रिय_Origin;
	संरचना TrackedDevicePose_t pose;
} निवेशः_Pose_Action_दत्त_t;

प्रकारनिर्देश संरचना निवेशः_Skeletal_Action_दत्त_t
{
	bool b_सक्रिय;
	VRInput_मानम्_Handle_t सक्रिय_Origin;
} निवेशः_Skeletal_Action_दत्त_t;

प्रकारनिर्देश संरचना निवेशः_Origin_Info_t
{
	VRInput_मानम्_Handle_t device_मार्गः;
	Tracked_Device_सूचकांक_t tracked_Device_सूचकांक;
	वर्ण rchRenderModelComponentName[128]; //char[128]
} निवेशः_Origin_Info_t;

प्रकारनिर्देश संरचना निवेशः_Binding_Info_t
{
	वर्ण rch_Device_मार्गः_Name[128]; //char[128]
	वर्ण rch_निवेशः_मार्गः_Name[128]; //char[128]
	वर्ण rch_बहुलकम्_Name[128]; //char[128]
	वर्ण rchSlotName[128]; //char[128]
	वर्ण rch_निवेशः_Source_Type[32]; //char[32]
} निवेशः_Binding_Info_t;

प्रकारनिर्देश संरचना VRActive_Action_समुच्चयः_t
{
	VRAction_समुच्चयः_Handle_t ul_Action_समुच्चयः;
	VRInput_मानम्_Handle_t ul_Restricted_गन्तव्यम्_Device;
	VRAction_समुच्चयः_Handle_t ul_Secondary_Action_समुच्चयः;
	uint32_t unPadding;
	int32_t n_प्राथमिकता;
} VRActive_Action_समुच्चयः_t;

प्रकारनिर्देश संरचना VRSkeletal_Summary_दत्त_t
{
	भिन्न flFingerCurl[5]; //float[5]
	भिन्न flFingerSplay[4]; //float[4]
} VRSkeletal_Summary_दत्त_t;

प्रकारनिर्देश संरचना SpatialAnchorPose_t
{
	संरचना HmdMatrix34_t m_Anchor_गन्तव्यम्_Absolute_Tracking;
} SpatialAnchorPose_t;

प्रकारनिर्देश संरचना COpenVRContext
{
	intptr_t m_pVRSystem; // class vr::IVRSystem *
	intptr_t m_pVRChaperone; // class vr::IVRChaperone *
	intptr_t m_p_VRChaperone_सज्जता; // class vr::IVRChaperoneSetup *
	intptr_t m_pVRCompositor; // class vr::IVRCompositor *
	intptr_t m_pVRHeadsetView; // class vr::IVRHeadsetView *
	intptr_t m_pVROverlay; // class vr::IVROverlay *
	intptr_t m_pVROverlayView; // class vr::IVROverlayView *
	intptr_t m_pVRResources; // class vr::IVRResources *
	intptr_t m_pVRRenderModels; // class vr::IVRRenderModels *
	intptr_t m_pVRExtendedDisplay; // class vr::IVRExtendedDisplay *
	intptr_t m_pVRSettings; // class vr::IVRSettings *
	intptr_t m_pVRApplications; // class vr::IVRApplications *
	intptr_t m_pVRTrackedCamera; // class vr::IVRTrackedCamera *
	intptr_t m_pVRScreenshots; // class vr::IVRScreenshots *
	intptr_t m_pVRDriverManager; // class vr::IVRDriverManager *
	intptr_t m_pVRInput; // class vr::IVRInput *
	intptr_t m_pVRIOBuffer; // class vr::IVRIOBuffer *
	intptr_t m_pVRSpatialAnchors; // class vr::IVRSpatialAnchors *
	intptr_t m_pVRDebug; // class vr::IVRDebug *
	intptr_t m_pVRNotifications; // class vr::IVRNotifications *
} COpenVRContext;

प्रकारनिर्देश संरचना PropertyWrite_t
{
	गणना ETrackedDeviceProperty prop;
	गणना EPropertyWriteType writeType;
	गणना ETrackedPropertyError e_समुच्चयः_Error;
	शून्य * pv_बफर; // void *
	uint32_t un_बफर_आकार;
	Property_Type_चिह्नकम्_t un_चिह्नकम्;
	गणना ETrackedPropertyError eError;
} PropertyWrite_t;

प्रकारनिर्देश संरचना PropertyRead_t
{
	गणना ETrackedDeviceProperty prop;
	शून्य * pv_बफर; // void *
	uint32_t un_बफर_आकार;
	Property_Type_चिह्नकम्_t un_चिह्नकम्;
	uint32_t un_Required_बफर_आकार;
	गणना ETrackedPropertyError eError;
} PropertyRead_t;

प्रकारनिर्देश संरचना CVRPropertyHelpers
{
	intptr_t m_pProperties; // class vr::IVRProperties *
} CVRPropertyHelpers;

प्रकारनिर्देश संरचना मार्गः_Write_t
{
	मार्गः_Handle_t ul_मार्गः;
	गणना EPropertyWriteType writeType;
	गणना ETrackedPropertyError e_समुच्चयः_Error;
	शून्य * pv_बफर; // void *
	uint32_t un_बफर_आकार;
	Property_Type_चिह्नकम्_t un_चिह्नकम्;
	गणना ETrackedPropertyError eError;
	वर्ण * psz_मार्गः; // const char *
} मार्गः_Write_t;

प्रकारनिर्देश संरचना मार्गः_Read_t
{
	मार्गः_Handle_t ul_मार्गः;
	शून्य * pv_बफर; // void *
	uint32_t un_बफर_आकार;
	Property_Type_चिह्नकम्_t un_चिह्नकम्;
	uint32_t un_Required_बफर_आकार;
	गणना ETrackedPropertyError eError;
	वर्ण * psz_मार्गः; // const char *
} मार्गः_Read_t;


प्रकारनिर्देश सङ्घ
{
	VREvent_Reserved_t reserved;
	VREvent_Controller_t controller;
	VREvent_Mouse_t mouse;
	VREvent_Scroll_t scroll;
	VREvent_Process_t process;
	VREvent_Notification_t notification;
	VREvent_Overlay_t overlay;
	VREvent_स्थितिः_t स्थितिः;
	VREvent_Keyboard_t keyboard;
	VREvent_Ipd_t ipd;
	VREvent_Chaperone_t chaperone;
	VREvent_PerformanceTest_t performanceTest;
	VREvent_TouchPadMove_t touchPadMove;
	VREvent_SeatedZeroPoseReset_t seatedZeroPoseReset;
	VREvent_Screenshot_t screenshot;
	VREvent_Screenshot_प्रगतिः_t screenshot_प्रगतिः;
	VREvent_ApplicationLaunch_t applicationLaunch;
	VREvent_EditingCameraSurface_t cameraSurface;
	VREvent_सन्देशः_Overlay_t सन्देशः_Overlay;
	VREvent_Property_t property;
	VREvent_HapticVibration_t hapticVibration;
	VREvent_WebConsole_t webConsole;
	VREvent_निवेशः_Binding_आरोपय_t निवेशः_Binding;
	VREvent_निवेशः_Action_Manifest_आरोपय_t actionManifest;
	VREvent_SpatialAnchor_t spatialAnchor;
} VREvent_दत्त_t;

#यदि defined(__linux__) || defined(__APPLE__) 
// This structure was originally defined mis-packed on Linux, preserved for 
// compatibility. 
#निर्देशः pack( प्रक्षिप, 4 )
#यदि_अन्तः

/** An event posted by the server to all running applications */
संरचना VREvent_t
{
	uint32_t eventType; // EVREventType enum
	Tracked_Device_सूचकांक_t tracked_Device_सूचकांक;
	भिन्न eventAgeSeconds;
	// event data must be the end of the struct as its size is variable
	VREvent_दत्त_t दत्त;
};

#यदि defined(__linux__) || defined(__APPLE__) 
#निर्देशः pack( निष्कासय )
#यदि_अन्तः


प्रकारनिर्देश सङ्घ
{
	Intersection_आवरणम्_Rectangle_t m_Rectangle;
	Intersection_आवरणम्_Circle_t m_Circle;
} VROverlay_Intersection_आवरणम्_Primitive_दत्त_t;

संरचना VROverlay_Intersection_आवरणम्_Primitive_t
{
	EVROverlay_Intersection_आवरणम्_Primitive_Type m_nPrimitiveType;
	VROverlay_Intersection_आवरणम्_Primitive_दत्त_t m_Primitive;
};


// OpenVR Function Pointer Tables

संरचना VR_IVRSystem_Fn_सारणी
{
	शून्य (OPENVR_FNTABLE_CALLTYPE *Get_Recommended_Render_Target_आकार)(uint32_t * pn_विस्तारः, uint32_t * pnHeight);
	संरचना HmdMatrix44_t (OPENVR_FNTABLE_CALLTYPE *GetProjectionMatrix)(EVREye eEye, भिन्न fNearZ, भिन्न fFarZ);
	शून्य (OPENVR_FNTABLE_CALLTYPE *GetProjectionRaw)(EVREye eEye, भिन्न * pf_वामः, भिन्न * pf_दक्षिणः, भिन्न * pf_शिखरम्, भिन्न * pfBottom);
	bool (OPENVR_FNTABLE_CALLTYPE *ComputeDistortion)(EVREye eEye, भिन्न fU, भिन्न fV, संरचना DistortionCoordinates_t * pDistortionCoordinates);
	संरचना HmdMatrix34_t (OPENVR_FNTABLE_CALLTYPE *Get_Eye_गन्तव्यम्_शीर्ष_Transform)(EVREye eEye);
	bool (OPENVR_FNTABLE_CALLTYPE *Get_Time_Since_चरमः_Vsync)(भिन्न * pf_Seconds_Since_चरमः_Vsync, uint64_t * pul_Frame_गणक);
	int32_t (OPENVR_FNTABLE_CALLTYPE *Get_D3_D9_Adapter_सूचकांक)();
	शून्य (OPENVR_FNTABLE_CALLTYPE *GetDXGIOutputInfo)(int32_t * pn_Adapter_सूचकांक);
	शून्य (OPENVR_FNTABLE_CALLTYPE *GetOutputDevice)(uint64_t * pnDevice, ETextureType textureType, संरचना VkInstance_T * pInstance);
	bool (OPENVR_FNTABLE_CALLTYPE *IsDisplayOnDesktop)();
	bool (OPENVR_FNTABLE_CALLTYPE *समुच्चयः_Display_Visibility)(bool bIsVisibleOnDesktop);
	शून्य (OPENVR_FNTABLE_CALLTYPE *Get_Device_गन्तव्यम्_Absolute_Tracking_Pose)(ETrackingUniverseOrigin eOrigin, भिन्न f_Predicted_Seconds_गन्तव्यम्_Photons_From_Now, संरचना TrackedDevicePose_t * pTrackedDevicePoseArray, uint32_t un_Tracked_Device_Pose_Array_गणनम्);
	संरचना HmdMatrix34_t (OPENVR_FNTABLE_CALLTYPE *Get_Seated_Zero_Pose_गन्तव्यम्_Standing_Absolute_Tracking_Pose)();
	संरचना HmdMatrix34_t (OPENVR_FNTABLE_CALLTYPE *Get_Raw_Zero_Pose_गन्तव्यम्_Standing_Absolute_Tracking_Pose)();
	uint32_t (OPENVR_FNTABLE_CALLTYPE *Get_Sorted_Tracked_Device_Indices_सम्बन्धि_Class)(ETrackedDeviceClass eTrackedDeviceClass, Tracked_Device_सूचकांक_t * pun_Tracked_Device_सूचकांक_Array, uint32_t un_Tracked_Device_सूचकांक_Array_गणनम्, Tracked_Device_सूचकांक_t un_Relative_गन्तव्यम्_Tracked_Device_सूचकांक);
	EDeviceActivityLevel (OPENVR_FNTABLE_CALLTYPE *GetTrackedDeviceActivityLevel)(Tracked_Device_सूचकांक_t unDeviceId);
	शून्य (OPENVR_FNTABLE_CALLTYPE *ApplyTransform)(संरचना TrackedDevicePose_t * pOutputPose, संरचना TrackedDevicePose_t * pTrackedDevicePose, संरचना HmdMatrix34_t * pTransform);
	Tracked_Device_सूचकांक_t (OPENVR_FNTABLE_CALLTYPE *Get_Tracked_Device_सूचकांक_For_Controller_Role)(ETrackedControllerRole unDeviceType);
	ETrackedControllerRole (OPENVR_FNTABLE_CALLTYPE *Get_Controller_Role_For_Tracked_Device_सूचकांक)(Tracked_Device_सूचकांक_t un_Device_सूचकांक);
	ETrackedDeviceClass (OPENVR_FNTABLE_CALLTYPE *GetTrackedDeviceClass)(Tracked_Device_सूचकांक_t un_Device_सूचकांक);
	bool (OPENVR_FNTABLE_CALLTYPE *IsTrackedDeviceConnected)(Tracked_Device_सूचकांक_t un_Device_सूचकांक);
	bool (OPENVR_FNTABLE_CALLTYPE *GetBoolTrackedDeviceProperty)(Tracked_Device_सूचकांक_t un_Device_सूचकांक, ETrackedDeviceProperty prop, ETrackedPropertyError * pError);
	भिन्न (OPENVR_FNTABLE_CALLTYPE *GetFloatTrackedDeviceProperty)(Tracked_Device_सूचकांक_t un_Device_सूचकांक, ETrackedDeviceProperty prop, ETrackedPropertyError * pError);
	int32_t (OPENVR_FNTABLE_CALLTYPE *GetInt32TrackedDeviceProperty)(Tracked_Device_सूचकांक_t un_Device_सूचकांक, ETrackedDeviceProperty prop, ETrackedPropertyError * pError);
	uint64_t (OPENVR_FNTABLE_CALLTYPE *GetUint64TrackedDeviceProperty)(Tracked_Device_सूचकांक_t un_Device_सूचकांक, ETrackedDeviceProperty prop, ETrackedPropertyError * pError);
	संरचना HmdMatrix34_t (OPENVR_FNTABLE_CALLTYPE *GetMatrix34TrackedDeviceProperty)(Tracked_Device_सूचकांक_t un_Device_सूचकांक, ETrackedDeviceProperty prop, ETrackedPropertyError * pError);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetArrayTrackedDeviceProperty)(Tracked_Device_सूचकांक_t un_Device_सूचकांक, ETrackedDeviceProperty prop, Property_Type_चिह्नकम्_t propType, शून्य * p_बफर, uint32_t un_बफर_आकार, ETrackedPropertyError * pError);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetStringTrackedDeviceProperty)(Tracked_Device_सूचकांक_t un_Device_सूचकांक, ETrackedDeviceProperty prop, वर्ण * pch_मानम्, uint32_t un_बफर_आकार, ETrackedPropertyError * pError);
	वर्ण * (OPENVR_FNTABLE_CALLTYPE *GetPropErrorNameFromEnum)(ETrackedPropertyError error);
	bool (OPENVR_FNTABLE_CALLTYPE *Poll_अग्र_Event)(संरचना VREvent_t * pEvent, uint32_t uncbVREvent);
	bool (OPENVR_FNTABLE_CALLTYPE *Poll_अग्र_Event_With_Pose)(ETrackingUniverseOrigin eOrigin, संरचना VREvent_t * pEvent, uint32_t uncbVREvent, TrackedDevicePose_t * pTrackedDevicePose);
	वर्ण * (OPENVR_FNTABLE_CALLTYPE *GetEventTypeNameFromEnum)(EVREventType eType);
	संरचना HiddenAreaMesh_t (OPENVR_FNTABLE_CALLTYPE *GetHiddenAreaMesh)(EVREye eEye, EHiddenAreaMeshType type);
	bool (OPENVR_FNTABLE_CALLTYPE *GetControllerState)(Tracked_Device_सूचकांक_t un_Controller_Device_सूचकांक, VRControllerState_t * pControllerState, uint32_t un_Controller_State_आकार);
	bool (OPENVR_FNTABLE_CALLTYPE *GetControllerStateWithPose)(ETrackingUniverseOrigin eOrigin, Tracked_Device_सूचकांक_t un_Controller_Device_सूचकांक, VRControllerState_t * pControllerState, uint32_t un_Controller_State_आकार, संरचना TrackedDevicePose_t * pTrackedDevicePose);
	शून्य (OPENVR_FNTABLE_CALLTYPE *TriggerHapticPulse)(Tracked_Device_सूचकांक_t un_Controller_Device_सूचकांक, uint32_t unAxisId, अचिह्नित ह्रस्व usDurationMicroSec);
	वर्ण * (OPENVR_FNTABLE_CALLTYPE *GetButtonIdNameFromEnum)(EVRButtonId eButtonId);
	वर्ण * (OPENVR_FNTABLE_CALLTYPE *GetControllerAxisTypeNameFromEnum)(EVRControllerAxisType eAxisType);
	bool (OPENVR_FNTABLE_CALLTYPE *Is_निवेशः_उपलब्धम्)();
	bool (OPENVR_FNTABLE_CALLTYPE *IsSteamVRDrawingControllers)();
	bool (OPENVR_FNTABLE_CALLTYPE *ShouldApplicationPause)();
	bool (OPENVR_FNTABLE_CALLTYPE *ShouldApplicationReduceRenderingWork)();
	EVRFirmwareError (OPENVR_FNTABLE_CALLTYPE *PerformFirmwareUpdate)(Tracked_Device_सूचकांक_t un_Device_सूचकांक);
	शून्य (OPENVR_FNTABLE_CALLTYPE *AcknowledgeQuit_Exiting)();
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetAppContainerFilePaths)(वर्ण * pch_बफर, uint32_t un_बफर_आकार);
	वर्ण * (OPENVR_FNTABLE_CALLTYPE *Get_Runtime_संस्करणम्)();
};

संरचना VR_IVRExtended_Display_Fn_सारणी
{
	शून्य (OPENVR_FNTABLE_CALLTYPE *Get_गवाक्षः_Bounds)(int32_t * pnX, int32_t * pnY, uint32_t * pn_विस्तारः, uint32_t * pnHeight);
	शून्य (OPENVR_FNTABLE_CALLTYPE *GetEyeOutputViewport)(EVREye eEye, uint32_t * pnX, uint32_t * pnY, uint32_t * pn_विस्तारः, uint32_t * pnHeight);
	शून्य (OPENVR_FNTABLE_CALLTYPE *GetDXGIOutputInfo)(int32_t * pn_Adapter_सूचकांक, int32_t * pn_Adapter_Output_सूचकांक);
};

संरचना VR_IVRTracked_Camera_Fn_सारणी
{
	वर्ण * (OPENVR_FNTABLE_CALLTYPE *GetCameraErrorNameFromEnum)(EVRTrackedCameraError eCameraError);
	EVRTrackedCameraError (OPENVR_FNTABLE_CALLTYPE *HasCamera)(Tracked_Device_सूचकांक_t n_Device_सूचकांक, bool * pHasCamera);
	EVRTrackedCameraError (OPENVR_FNTABLE_CALLTYPE *Get_Camera_Frame_आकार)(Tracked_Device_सूचकांक_t n_Device_सूचकांक, EVRTrackedCameraFrameType eFrameType, uint32_t * pn_विस्तारः, uint32_t * pnHeight, uint32_t * pn_Frame_बफर_आकार);
	EVRTrackedCameraError (OPENVR_FNTABLE_CALLTYPE *GetCameraIntrinsics)(Tracked_Device_सूचकांक_t n_Device_सूचकांक, uint32_t n_Camera_सूचकांक, EVRTrackedCameraFrameType eFrameType, HmdVector2_t * p_Focal_दीर्घता, HmdVector2_t * pCenter);
	EVRTrackedCameraError (OPENVR_FNTABLE_CALLTYPE *GetCameraProjection)(Tracked_Device_सूचकांक_t n_Device_सूचकांक, uint32_t n_Camera_सूचकांक, EVRTrackedCameraFrameType eFrameType, भिन्न flZNear, भिन्न flZFar, HmdMatrix44_t * pProjection);
	EVRTrackedCameraError (OPENVR_FNTABLE_CALLTYPE *AcquireVideoStreamingService)(Tracked_Device_सूचकांक_t n_Device_सूचकांक, TrackedCameraHandle_t * pHandle);
	EVRTrackedCameraError (OPENVR_FNTABLE_CALLTYPE *ReleaseVideoStreamingService)(TrackedCameraHandle_t hTrackedCamera);
	EVRTrackedCameraError (OPENVR_FNTABLE_CALLTYPE *Get_Video_प्रवाहः_Frame_बफर)(TrackedCameraHandle_t hTrackedCamera, EVRTrackedCameraFrameType eFrameType, शून्य * p_Frame_बफर, uint32_t n_Frame_बफर_आकार, Camera_Video_प्रवाहः_Frame_शीर्षकम्_t * p_Frame_शीर्षकम्, uint32_t n_Frame_शीर्षकम्_आकार);
	EVRTrackedCameraError (OPENVR_FNTABLE_CALLTYPE *Get_Video_प्रवाहः_Texture_आकार)(Tracked_Device_सूचकांक_t n_Device_सूचकांक, EVRTrackedCameraFrameType eFrameType, VRTextureBounds_t * pTextureBounds, uint32_t * pn_विस्तारः, uint32_t * pnHeight);
	EVRTrackedCameraError (OPENVR_FNTABLE_CALLTYPE *Get_Video_प्रवाहः_Texture_D3_D11)(TrackedCameraHandle_t hTrackedCamera, EVRTrackedCameraFrameType eFrameType, शून्य * pD3D11DeviceOrResource, शून्य ** ppD3D11ShaderResourceView, Camera_Video_प्रवाहः_Frame_शीर्षकम्_t * p_Frame_शीर्षकम्, uint32_t n_Frame_शीर्षकम्_आकार);
	EVRTrackedCameraError (OPENVR_FNTABLE_CALLTYPE *Get_Video_प्रवाहः_Texture_GL)(TrackedCameraHandle_t hTrackedCamera, EVRTrackedCameraFrameType eFrameType, glUInt_t * pglTextureId, Camera_Video_प्रवाहः_Frame_शीर्षकम्_t * p_Frame_शीर्षकम्, uint32_t n_Frame_शीर्षकम्_आकार);
	EVRTrackedCameraError (OPENVR_FNTABLE_CALLTYPE *Release_Video_प्रवाहः_Texture_GL)(TrackedCameraHandle_t hTrackedCamera, glUInt_t glTextureId);
	शून्य (OPENVR_FNTABLE_CALLTYPE *समुच्चयः_Camera_Tracking_Space)(ETrackingUniverseOrigin eUniverse);
	ETrackingUniverseOrigin (OPENVR_FNTABLE_CALLTYPE *GetCameraTrackingSpace)();
};

संरचना VR_IVRApplications_Fn_सारणी
{
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *सङ्कलय_Application_Manifest)(वर्ण * pch_Application_Manifest_पूर्णम्_मार्गः, bool bTemporary);
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *RemoveApplicationManifest)(वर्ण * pch_Application_Manifest_पूर्णम्_मार्गः);
	bool (OPENVR_FNTABLE_CALLTYPE *IsApplicationInstalled)(वर्ण * pch_App_कुञ्चिका);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *Get_Application_गणनम्)();
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *Get_Application_कुञ्चिका_By_सूचकांक)(uint32_t un_Application_सूचकांक, वर्ण * pch_App_कुञ्चिका_बफर, uint32_t un_App_कुञ्चिका_बफर_Len);
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *Get_Application_कुञ्चिका_By_Process_Id)(uint32_t unProcessId, वर्ण * pch_App_कुञ्चिका_बफर, uint32_t un_App_कुञ्चिका_बफर_Len);
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *LaunchApplication)(वर्ण * pch_App_कुञ्चिका);
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *LaunchTemplateApplication)(वर्ण * pch_Template_App_कुञ्चिका, वर्ण * pch_New_App_कुञ्चिका, संरचना App_Override_कुञ्चिकाः_t * p_कुञ्चिकाः, uint32_t un_कुञ्चिकाः);
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *LaunchApplicationFromMimeType)(वर्ण * pchMimeType, वर्ण * pch_तर्काः);
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *LaunchDashboardOverlay)(वर्ण * pch_App_कुञ्चिका);
	bool (OPENVR_FNTABLE_CALLTYPE *CancelApplicationLaunch)(वर्ण * pch_App_कुञ्चिका);
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *IdentifyApplication)(uint32_t unProcessId, वर्ण * pch_App_कुञ्चिका);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetApplicationProcessId)(वर्ण * pch_App_कुञ्चिका);
	वर्ण * (OPENVR_FNTABLE_CALLTYPE *GetApplicationsErrorNameFromEnum)(EVRApplicationError error);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetApplicationPropertyString)(वर्ण * pch_App_कुञ्चिका, EVRApplicationProperty eProperty, वर्ण * pch_Property_मानम्_बफर, uint32_t un_Property_मानम्_बफर_Len, EVRApplicationError * peError);
	bool (OPENVR_FNTABLE_CALLTYPE *GetApplicationPropertyBool)(वर्ण * pch_App_कुञ्चिका, EVRApplicationProperty eProperty, EVRApplicationError * peError);
	uint64_t (OPENVR_FNTABLE_CALLTYPE *GetApplicationPropertyUint64)(वर्ण * pch_App_कुञ्चिका, EVRApplicationProperty eProperty, EVRApplicationError * peError);
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *समुच्चयः_Application_Auto_Launch)(वर्ण * pch_App_कुञ्चिका, bool bAutoLaunch);
	bool (OPENVR_FNTABLE_CALLTYPE *GetApplicationAutoLaunch)(वर्ण * pch_App_कुञ्चिका);
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *समुच्चयः_Default_Application_For_Mime_Type)(वर्ण * pch_App_कुञ्चिका, वर्ण * pchMimeType);
	bool (OPENVR_FNTABLE_CALLTYPE *GetDefaultApplicationForMimeType)(वर्ण * pchMimeType, वर्ण * pch_App_कुञ्चिका_बफर, uint32_t un_App_कुञ्चिका_बफर_Len);
	bool (OPENVR_FNTABLE_CALLTYPE *GetApplicationSupportedMimeTypes)(वर्ण * pch_App_कुञ्चिका, वर्ण * pch_Mime_Types_बफर, uint32_t un_Mime_Types_बफर);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetApplicationsThatSupportMimeType)(वर्ण * pchMimeType, वर्ण * pch_App_कुञ्चिकाः_That_Support_बफर, uint32_t un_App_कुञ्चिकाः_That_Support_बफर);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetApplicationLaunchArguments)(uint32_t unHandle, वर्ण * pch_तर्काः, uint32_t un_तर्काः);
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *GetStartingApplication)(वर्ण * pch_App_कुञ्चिका_बफर, uint32_t un_App_कुञ्चिका_बफर_Len);
	EVRSceneApplicationState (OPENVR_FNTABLE_CALLTYPE *GetSceneApplicationState)();
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *PerformApplicationPrelaunchCheck)(वर्ण * pch_App_कुञ्चिका);
	वर्ण * (OPENVR_FNTABLE_CALLTYPE *GetSceneApplicationStateNameFromEnum)(EVRSceneApplicationState state);
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *Launch_आन्तरिकम्_Process)(वर्ण * pch_द्विमान_मार्गः, वर्ण * pchArguments, वर्ण * pchWorkingDirectory);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetCurrentSceneProcessId)();
};

संरचना VR_IVRChaperone_Fn_सारणी
{
	ChaperoneCalibrationState (OPENVR_FNTABLE_CALLTYPE *GetCalibrationState)();
	bool (OPENVR_FNTABLE_CALLTYPE *Get_Play_Area_आकार)(भिन्न * p_आकार_X, भिन्न * p_आकार_Z);
	bool (OPENVR_FNTABLE_CALLTYPE *GetPlayAreaRect)(संरचना HmdQuad_t * rect);
	शून्य (OPENVR_FNTABLE_CALLTYPE *ReloadInfo)();
	शून्य (OPENVR_FNTABLE_CALLTYPE *समुच्चयः_Scene_Color)(संरचना HmdColor_t color);
	शून्य (OPENVR_FNTABLE_CALLTYPE *GetBoundsColor)(संरचना HmdColor_t * pOutputColorArray, पूर्णाङ्क n_अङ्कः_Output_Colors, भिन्न flCollisionBoundsFadeDistance, संरचना HmdColor_t * pOutputCameraColor);
	bool (OPENVR_FNTABLE_CALLTYPE *AreBoundsVisible)();
	शून्य (OPENVR_FNTABLE_CALLTYPE *ForceBoundsVisible)(bool bForce);
	शून्य (OPENVR_FNTABLE_CALLTYPE *ResetZeroPose)(ETrackingUniverseOrigin eTrackingUniverseOrigin);
};

संरचना VR_IVRChaperone_सज्जता_Fn_सारणी
{
	bool (OPENVR_FNTABLE_CALLTYPE *CommitWorkingCopy)(EChaperoneConfigFile configFile);
	शून्य (OPENVR_FNTABLE_CALLTYPE *RevertWorkingCopy)();
	bool (OPENVR_FNTABLE_CALLTYPE *Get_Working_Play_Area_आकार)(भिन्न * p_आकार_X, भिन्न * p_आकार_Z);
	bool (OPENVR_FNTABLE_CALLTYPE *GetWorkingPlayAreaRect)(संरचना HmdQuad_t * rect);
	bool (OPENVR_FNTABLE_CALLTYPE *GetWorkingCollisionBoundsInfo)(संरचना HmdQuad_t * p_Quads_बफर, uint32_t * pun_Quads_गणनम्);
	bool (OPENVR_FNTABLE_CALLTYPE *Get_जीवितम्_Collision_Bounds_Info)(संरचना HmdQuad_t * p_Quads_बफर, uint32_t * pun_Quads_गणनम्);
	bool (OPENVR_FNTABLE_CALLTYPE *Get_Working_Seated_Zero_Pose_गन्तव्यम्_Raw_Tracking_Pose)(संरचना HmdMatrix34_t * pmat_Seated_Zero_Pose_गन्तव्यम्_Raw_Tracking_Pose);
	bool (OPENVR_FNTABLE_CALLTYPE *Get_Working_Standing_Zero_Pose_गन्तव्यम्_Raw_Tracking_Pose)(संरचना HmdMatrix34_t * pmat_Standing_Zero_Pose_गन्तव्यम्_Raw_Tracking_Pose);
	शून्य (OPENVR_FNTABLE_CALLTYPE *समुच्चयः_Working_Play_Area_आकार)(भिन्न आकार_X, भिन्न आकार_Z);
	शून्य (OPENVR_FNTABLE_CALLTYPE *समुच्चयः_Working_Collision_Bounds_Info)(संरचना HmdQuad_t * p_Quads_बफर, uint32_t un_Quads_गणनम्);
	शून्य (OPENVR_FNTABLE_CALLTYPE *समुच्चयः_Working_Perimeter)(संरचना HmdVector2_t * p_Point_बफर, uint32_t un_Point_गणनम्);
	शून्य (OPENVR_FNTABLE_CALLTYPE *समुच्चयः_Working_Seated_Zero_Pose_गन्तव्यम्_Raw_Tracking_Pose)(संरचना HmdMatrix34_t * p_Mat_Seated_Zero_Pose_गन्तव्यम्_Raw_Tracking_Pose);
	शून्य (OPENVR_FNTABLE_CALLTYPE *समुच्चयः_Working_Standing_Zero_Pose_गन्तव्यम्_Raw_Tracking_Pose)(संरचना HmdMatrix34_t * p_Mat_Standing_Zero_Pose_गन्तव्यम्_Raw_Tracking_Pose);
	शून्य (OPENVR_FNTABLE_CALLTYPE *ReloadFromDisk)(EChaperoneConfigFile configFile);
	bool (OPENVR_FNTABLE_CALLTYPE *Get_जीवितम्_Seated_Zero_Pose_गन्तव्यम्_Raw_Tracking_Pose)(संरचना HmdMatrix34_t * pmat_Seated_Zero_Pose_गन्तव्यम्_Raw_Tracking_Pose);
	bool (OPENVR_FNTABLE_CALLTYPE *Export_जीवितम्_गन्तव्यम्_बफर)(वर्ण * p_बफर, uint32_t * pn_बफर_दीर्घता);
	bool (OPENVR_FNTABLE_CALLTYPE *Import_From_बफर_गन्तव्यम्_Working)(वर्ण * p_बफर, uint32_t nImportFlags);
	शून्य (OPENVR_FNTABLE_CALLTYPE *Show_Working_समुच्चयः_Preview)();
	शून्य (OPENVR_FNTABLE_CALLTYPE *Hide_Working_समुच्चयः_Preview)();
	शून्य (OPENVR_FNTABLE_CALLTYPE *अवकाशः_सज्जता_Starting)();
};

संरचना VR_IVRCompositor_Fn_सारणी
{
	शून्य (OPENVR_FNTABLE_CALLTYPE *समुच्चयः_Tracking_Space)(ETrackingUniverseOrigin eOrigin);
	ETrackingUniverseOrigin (OPENVR_FNTABLE_CALLTYPE *GetTrackingSpace)();
	EVRCompositorError (OPENVR_FNTABLE_CALLTYPE *WaitGetPoses)(संरचना TrackedDevicePose_t * pRenderPoseArray, uint32_t un_Render_Pose_Array_गणनम्, संरचना TrackedDevicePose_t * pGamePoseArray, uint32_t un_Game_Pose_Array_गणनम्);
	EVRCompositorError (OPENVR_FNTABLE_CALLTYPE *Get_चरमः_Poses)(संरचना TrackedDevicePose_t * pRenderPoseArray, uint32_t un_Render_Pose_Array_गणनम्, संरचना TrackedDevicePose_t * pGamePoseArray, uint32_t un_Game_Pose_Array_गणनम्);
	EVRCompositorError (OPENVR_FNTABLE_CALLTYPE *Get_चरमः_Pose_For_Tracked_Device_सूचकांक)(Tracked_Device_सूचकांक_t un_Device_सूचकांक, संरचना TrackedDevicePose_t * pOutputPose, संरचना TrackedDevicePose_t * pOutputGamePose);
	EVRCompositorError (OPENVR_FNTABLE_CALLTYPE *Submit)(EVREye eEye, संरचना Texture_t * pTexture, संरचना VRTextureBounds_t * pBounds, EVRSubmitFlags nSubmitFlags);
	शून्य (OPENVR_FNTABLE_CALLTYPE *Clear_चरमः_Submitted_Frame)();
	शून्य (OPENVR_FNTABLE_CALLTYPE *PostPresentHandoff)();
	bool (OPENVR_FNTABLE_CALLTYPE *GetFrameTiming)(संरचना Compositor_FrameTiming * pTiming, uint32_t un_चौकटाः_Ago);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetFrameTimings)(संरचना Compositor_FrameTiming * pTiming, uint32_t n_चौकटाः);
	भिन्न (OPENVR_FNTABLE_CALLTYPE *GetFrameTimeRemaining)();
	शून्य (OPENVR_FNTABLE_CALLTYPE *GetCumulativeStats)(संरचना Compositor_CumulativeStats * pStats, uint32_t n_Stats_आकार_अन्तर्_अष्टकानि);
	शून्य (OPENVR_FNTABLE_CALLTYPE *Fade_गन्तव्यम्_Color)(भिन्न fSeconds, भिन्न fRed, भिन्न fGreen, भिन्न fBlue, भिन्न fAlpha, bool bBackground);
	संरचना HmdColor_t (OPENVR_FNTABLE_CALLTYPE *GetCurrentFadeColor)(bool bBackground);
	शून्य (OPENVR_FNTABLE_CALLTYPE *FadeGrid)(भिन्न fSeconds, bool b_Fade_Grid_अन्तर्);
	भिन्न (OPENVR_FNTABLE_CALLTYPE *GetCurrentGridAlpha)();
	EVRCompositorError (OPENVR_FNTABLE_CALLTYPE *समुच्चयः_Skybox_Override)(संरचना Texture_t * pTextures, uint32_t un_Texture_गणनम्);
	शून्य (OPENVR_FNTABLE_CALLTYPE *ClearSkyboxOverride)();
	शून्य (OPENVR_FNTABLE_CALLTYPE *Compositor_Bring_गन्तव्यम्_Front)();
	शून्य (OPENVR_FNTABLE_CALLTYPE *Compositor_Go_गन्तव्यम्_पृष्ठभागः)();
	शून्य (OPENVR_FNTABLE_CALLTYPE *CompositorQuit)();
	bool (OPENVR_FNTABLE_CALLTYPE *IsFullscreen)();
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetCurrentSceneFocusProcess)();
	uint32_t (OPENVR_FNTABLE_CALLTYPE *Get_चरमः_Frame_Renderer)();
	bool (OPENVR_FNTABLE_CALLTYPE *CanRenderScene)();
	शून्य (OPENVR_FNTABLE_CALLTYPE *Show_Mirror_गवाक्षः)();
	शून्य (OPENVR_FNTABLE_CALLTYPE *Hide_Mirror_गवाक्षः)();
	bool (OPENVR_FNTABLE_CALLTYPE *Is_Mirror_गवाक्षः_Visible)();
	शून्य (OPENVR_FNTABLE_CALLTYPE *CompositorDumpImages)();
	bool (OPENVR_FNTABLE_CALLTYPE *Should_App_Render_With_नीचः_Resources)();
	शून्य (OPENVR_FNTABLE_CALLTYPE *ForceInterleavedReprojectionOn)(bool bOverride);
	शून्य (OPENVR_FNTABLE_CALLTYPE *ForceReconnectProcess)();
	शून्य (OPENVR_FNTABLE_CALLTYPE *SuspendRendering)(bool bSuspend);
	EVRCompositorError (OPENVR_FNTABLE_CALLTYPE *GetMirrorTextureD3D11)(EVREye eEye, शून्य * pD3D11DeviceOrResource, शून्य ** ppD3D11ShaderResourceView);
	शून्य (OPENVR_FNTABLE_CALLTYPE *ReleaseMirrorTextureD3D11)(शून्य * pD3D11ShaderResourceView);
	EVRCompositorError (OPENVR_FNTABLE_CALLTYPE *GetMirrorTextureGL)(EVREye eEye, glUInt_t * pglTextureId, glSharedTextureHandle_t * pglSharedTextureHandle);
	bool (OPENVR_FNTABLE_CALLTYPE *ReleaseSharedGLTexture)(glUInt_t glTextureId, glSharedTextureHandle_t glSharedTextureHandle);
	शून्य (OPENVR_FNTABLE_CALLTYPE *तालकम्_GLShared_Texture_For_Access)(glSharedTextureHandle_t glSharedTextureHandle);
	शून्य (OPENVR_FNTABLE_CALLTYPE *UnlockGLSharedTextureForAccess)(glSharedTextureHandle_t glSharedTextureHandle);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetVulkanInstanceExtensionsRequired)(वर्ण * pch_मानम्, uint32_t un_बफर_आकार);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetVulkanDeviceExtensionsRequired)(संरचना VkPhysicalDevice_T * pPhysicalDevice, वर्ण * pch_मानम्, uint32_t un_बफर_आकार);
	शून्य (OPENVR_FNTABLE_CALLTYPE *समुच्चयः_Explicit_Timing_बहुलकम्)(EVRCompositor_Timing_बहुलकम् e_Timing_बहुलकम्);
	EVRCompositorError (OPENVR_FNTABLE_CALLTYPE *Submit_Explicit_Timing_दत्त)();
	bool (OPENVR_FNTABLE_CALLTYPE *IsMotionSmoothingEnabled)();
	bool (OPENVR_FNTABLE_CALLTYPE *IsMotionSmoothingSupported)();
	bool (OPENVR_FNTABLE_CALLTYPE *IsCurrentSceneFocusAppLoading)();
	EVRCompositorError (OPENVR_FNTABLE_CALLTYPE *समुच्चयः_Stage_Override_Async)(वर्ण * pch_Render_Model_मार्गः, संरचना HmdMatrix34_t * pTransform, संरचना Compositor_StageRenderSettings * pRenderSettings, uint32_t n_आकार_सम्बन्धि_Render_Settings);
	शून्य (OPENVR_FNTABLE_CALLTYPE *ClearStageOverride)();
	bool (OPENVR_FNTABLE_CALLTYPE *GetCompositorBenchmarkResults)(संरचना Compositor_BenchmarkResults * pBenchmarkResults, uint32_t n_आकार_सम्बन्धि_Benchmark_Results);
	EVRCompositorError (OPENVR_FNTABLE_CALLTYPE *Get_चरमः_Pose_Prediction_IDs)(uint32_t * pRenderPosePredictionID, uint32_t * pGamePosePredictionID);
	EVRCompositorError (OPENVR_FNTABLE_CALLTYPE *GetPosesForFrame)(uint32_t unPosePredictionID, संरचना TrackedDevicePose_t * pPoseArray, uint32_t un_Pose_Array_गणनम्);
};

संरचना VR_IVROverlay_Fn_सारणी
{
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *FindOverlay)(वर्ण * pch_Overlay_कुञ्चिका, VROverlayHandle_t * pOverlayHandle);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *CreateOverlay)(वर्ण * pch_Overlay_कुञ्चिका, वर्ण * pchOverlayName, VROverlayHandle_t * pOverlayHandle);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *DestroyOverlay)(VROverlayHandle_t ulOverlayHandle);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *Get_Overlay_कुञ्चिका)(VROverlayHandle_t ulOverlayHandle, वर्ण * pch_मानम्, uint32_t un_बफर_आकार, EVROverlayError * pError);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetOverlayName)(VROverlayHandle_t ulOverlayHandle, वर्ण * pch_मानम्, uint32_t un_बफर_आकार, EVROverlayError * pError);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *समुच्चयः_Overlay_Name)(VROverlayHandle_t ulOverlayHandle, वर्ण * pchName);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *Get_Overlay_Image_दत्त)(VROverlayHandle_t ulOverlayHandle, शून्य * pv_बफर, uint32_t un_बफर_आकार, uint32_t * pun_विस्तारः, uint32_t * punHeight);
	वर्ण * (OPENVR_FNTABLE_CALLTYPE *GetOverlayErrorNameFromEnum)(EVROverlayError error);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *समुच्चयः_Overlay_Rendering_Pid)(VROverlayHandle_t ulOverlayHandle, uint32_t unPID);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetOverlayRenderingPid)(VROverlayHandle_t ulOverlayHandle);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *समुच्चयः_Overlay_Flag)(VROverlayHandle_t ulOverlayHandle, VROverlayFlags eOverlayFlag, bool bEnabled);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayFlag)(VROverlayHandle_t ulOverlayHandle, VROverlayFlags eOverlayFlag, bool * pbEnabled);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayFlags)(VROverlayHandle_t ulOverlayHandle, uint32_t * pFlags);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *समुच्चयः_Overlay_Color)(VROverlayHandle_t ulOverlayHandle, भिन्न fRed, भिन्न fGreen, भिन्न fBlue);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayColor)(VROverlayHandle_t ulOverlayHandle, भिन्न * pfRed, भिन्न * pfGreen, भिन्न * pfBlue);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *समुच्चयः_Overlay_Alpha)(VROverlayHandle_t ulOverlayHandle, भिन्न fAlpha);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayAlpha)(VROverlayHandle_t ulOverlayHandle, भिन्न * pfAlpha);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *समुच्चयः_Overlay_Texel_Aspect)(VROverlayHandle_t ulOverlayHandle, भिन्न fTexelAspect);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayTexelAspect)(VROverlayHandle_t ulOverlayHandle, भिन्न * pfTexelAspect);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *समुच्चयः_Overlay_क्रमय_क्रमः)(VROverlayHandle_t ulOverlayHandle, uint32_t un_क्रमय_क्रमः);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *Get_Overlay_क्रमय_क्रमः)(VROverlayHandle_t ulOverlayHandle, uint32_t * pun_क्रमय_क्रमः);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *समुच्चयः_Overlay_विस्तारः_अन्तर्_Meters)(VROverlayHandle_t ulOverlayHandle, भिन्न f_विस्तारः_अन्तर्_Meters);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *Get_Overlay_विस्तारः_अन्तर्_Meters)(VROverlayHandle_t ulOverlayHandle, भिन्न * pf_विस्तारः_अन्तर्_Meters);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *समुच्चयः_Overlay_Curvature)(VROverlayHandle_t ulOverlayHandle, भिन्न fCurvature);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayCurvature)(VROverlayHandle_t ulOverlayHandle, भिन्न * pfCurvature);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *समुच्चयः_Overlay_Pre_वक्रम्_Pitch)(VROverlayHandle_t ulOverlayHandle, भिन्न fRadians);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *Get_Overlay_Pre_वक्रम्_Pitch)(VROverlayHandle_t ulOverlayHandle, भिन्न * pfRadians);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *समुच्चयः_Overlay_Texture_Color_Space)(VROverlayHandle_t ulOverlayHandle, EColorSpace eTextureColorSpace);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayTextureColorSpace)(VROverlayHandle_t ulOverlayHandle, EColorSpace * peTextureColorSpace);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *समुच्चयः_Overlay_Texture_Bounds)(VROverlayHandle_t ulOverlayHandle, संरचना VRTextureBounds_t * pOverlayTextureBounds);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayTextureBounds)(VROverlayHandle_t ulOverlayHandle, संरचना VRTextureBounds_t * pOverlayTextureBounds);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayTransformType)(VROverlayHandle_t ulOverlayHandle, VROverlayTransformType * peTransformType);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *समुच्चयः_Overlay_Transform_Absolute)(VROverlayHandle_t ulOverlayHandle, ETrackingUniverseOrigin eTrackingOrigin, संरचना HmdMatrix34_t * pmat_Tracking_Origin_गन्तव्यम्_Overlay_Transform);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayTransformAbsolute)(VROverlayHandle_t ulOverlayHandle, ETrackingUniverseOrigin * peTrackingOrigin, संरचना HmdMatrix34_t * pmat_Tracking_Origin_गन्तव्यम्_Overlay_Transform);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *समुच्चयः_Overlay_Transform_Tracked_Device_Relative)(VROverlayHandle_t ulOverlayHandle, Tracked_Device_सूचकांक_t unTrackedDevice, संरचना HmdMatrix34_t * pmat_Tracked_Device_गन्तव्यम्_Overlay_Transform);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayTransformTrackedDeviceRelative)(VROverlayHandle_t ulOverlayHandle, Tracked_Device_सूचकांक_t * punTrackedDevice, संरचना HmdMatrix34_t * pmat_Tracked_Device_गन्तव्यम्_Overlay_Transform);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *समुच्चयः_Overlay_Transform_Tracked_Device_Component)(VROverlayHandle_t ulOverlayHandle, Tracked_Device_सूचकांक_t un_Device_सूचकांक, वर्ण * pchComponentName);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayTransformTrackedDeviceComponent)(VROverlayHandle_t ulOverlayHandle, Tracked_Device_सूचकांक_t * pun_Device_सूचकांक, वर्ण * pchComponentName, uint32_t un_Component_Name_आकार);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayTransformOverlayRelative)(VROverlayHandle_t ulOverlayHandle, VROverlayHandle_t * ulOverlayHandleParent, संरचना HmdMatrix34_t * pmat_Parent_Overlay_गन्तव्यम्_Overlay_Transform);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *समुच्चयः_Overlay_Transform_Overlay_Relative)(VROverlayHandle_t ulOverlayHandle, VROverlayHandle_t ulOverlayHandleParent, संरचना HmdMatrix34_t * pmat_Parent_Overlay_गन्तव्यम्_Overlay_Transform);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *समुच्चयः_Overlay_Transform_Cursor)(VROverlayHandle_t ulCursorOverlayHandle, संरचना HmdVector2_t * pvHotspot);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayTransformCursor)(VROverlayHandle_t ulOverlayHandle, संरचना HmdVector2_t * pvHotspot);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *समुच्चयः_Overlay_Transform_Projection)(VROverlayHandle_t ulOverlayHandle, ETrackingUniverseOrigin eTrackingOrigin, संरचना HmdMatrix34_t * pmat_Tracking_Origin_गन्तव्यम्_Overlay_Transform, संरचना VROverlayProjection_t * pProjection, EVREye eEye);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *ShowOverlay)(VROverlayHandle_t ulOverlayHandle);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *HideOverlay)(VROverlayHandle_t ulOverlayHandle);
	bool (OPENVR_FNTABLE_CALLTYPE *IsOverlayVisible)(VROverlayHandle_t ulOverlayHandle);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetTransformForOverlayCoordinates)(VROverlayHandle_t ulOverlayHandle, ETrackingUniverseOrigin eTrackingOrigin, संरचना HmdVector2_t coordinates_अन्तर्_Overlay, संरचना HmdMatrix34_t * pmatTransform);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *WaitFrameSync)(uint32_t nTimeoutMs);
	bool (OPENVR_FNTABLE_CALLTYPE *Poll_अग्र_Overlay_Event)(VROverlayHandle_t ulOverlayHandle, संरचना VREvent_t * pEvent, uint32_t uncbVREvent);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *Get_Overlay_निवेशः_विधानम्)(VROverlayHandle_t ulOverlayHandle, VROverlay_निवेशः_विधानम् * pe_निवेशः_विधानम्);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *समुच्चयः_Overlay_निवेशः_विधानम्)(VROverlayHandle_t ulOverlayHandle, VROverlay_निवेशः_विधानम् e_निवेशः_विधानम्);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayMouseScale)(VROverlayHandle_t ulOverlayHandle, संरचना HmdVector2_t * pvecMouseScale);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *समुच्चयः_Overlay_Mouse_Scale)(VROverlayHandle_t ulOverlayHandle, संरचना HmdVector2_t * pvecMouseScale);
	bool (OPENVR_FNTABLE_CALLTYPE *ComputeOverlayIntersection)(VROverlayHandle_t ulOverlayHandle, संरचना VROverlayIntersectionParams_t * pParams, संरचना VROverlayIntersectionResults_t * pResults);
	bool (OPENVR_FNTABLE_CALLTYPE *IsHoverTargetOverlay)(VROverlayHandle_t ulOverlayHandle);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *समुच्चयः_Overlay_Intersection_आवरणम्)(VROverlayHandle_t ulOverlayHandle, संरचना VROverlay_Intersection_आवरणम्_Primitive_t * p_आवरणम्_Primitives, uint32_t un_अङ्कः_आवरणम्_Primitives, uint32_t un_Primitive_आकार);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *TriggerLaserMouseHapticVibration)(VROverlayHandle_t ulOverlayHandle, भिन्न fDurationSeconds, भिन्न fFrequency, भिन्न fAmplitude);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *समुच्चयः_Overlay_Cursor)(VROverlayHandle_t ulOverlayHandle, VROverlayHandle_t ulCursorHandle);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *समुच्चयः_Overlay_Cursor_Position_Override)(VROverlayHandle_t ulOverlayHandle, संरचना HmdVector2_t * pvCursor);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *ClearOverlayCursorPositionOverride)(VROverlayHandle_t ulOverlayHandle);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *समुच्चयः_Overlay_Texture)(VROverlayHandle_t ulOverlayHandle, संरचना Texture_t * pTexture);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *ClearOverlayTexture)(VROverlayHandle_t ulOverlayHandle);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *समुच्चयः_Overlay_Raw)(VROverlayHandle_t ulOverlayHandle, शून्य * pv_बफर, uint32_t un_विस्तारः, uint32_t unHeight, uint32_t un_अष्टकानि_प्रत्येकम्_Pixel);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *समुच्चयः_Overlay_From_File)(VROverlayHandle_t ulOverlayHandle, वर्ण * pch_File_मार्गः);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayTexture)(VROverlayHandle_t ulOverlayHandle, शून्य ** pNativeTextureHandle, शून्य * pNativeTextureRef, uint32_t * p_विस्तारः, uint32_t * pHeight, uint32_t * pNativeFormat, ETextureType * pAPIType, EColorSpace * pColorSpace, संरचना VRTextureBounds_t * pTextureBounds);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *ReleaseNativeOverlayHandle)(VROverlayHandle_t ulOverlayHandle, शून्य * pNativeTextureHandle);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *Get_Overlay_Texture_आकार)(VROverlayHandle_t ulOverlayHandle, uint32_t * p_विस्तारः, uint32_t * pHeight);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *CreateDashboardOverlay)(वर्ण * pch_Overlay_कुञ्चिका, वर्ण * pchOverlayFriendlyName, VROverlayHandle_t * pMainHandle, VROverlayHandle_t * pThumbnailHandle);
	bool (OPENVR_FNTABLE_CALLTYPE *IsDashboardVisible)();
	bool (OPENVR_FNTABLE_CALLTYPE *Is_सक्रिय_Dashboard_Overlay)(VROverlayHandle_t ulOverlayHandle);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *समुच्चयः_Dashboard_Overlay_Scene_Process)(VROverlayHandle_t ulOverlayHandle, uint32_t unProcessId);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetDashboardOverlaySceneProcess)(VROverlayHandle_t ulOverlayHandle, uint32_t * punProcessId);
	शून्य (OPENVR_FNTABLE_CALLTYPE *ShowDashboard)(वर्ण * pch_Overlay_गन्तव्यम्_Show);
	Tracked_Device_सूचकांक_t (OPENVR_FNTABLE_CALLTYPE *GetPrimaryDashboardDevice)();
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *ShowKeyboard)(EGamepad_Text_निवेशः_बहुलकम् e_निवेशः_बहुलकम्, EGamepad_Text_निवेशः_पङ्क्तिः_बहुलकम् e_पङ्क्तिः_निवेशः_बहुलकम्, uint32_t unFlags, वर्ण * pchDescription, uint32_t unCharMax, वर्ण * pchExistingText, uint64_t u_User_मानम्);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *ShowKeyboardForOverlay)(VROverlayHandle_t ulOverlayHandle, EGamepad_Text_निवेशः_बहुलकम् e_निवेशः_बहुलकम्, EGamepad_Text_निवेशः_पङ्क्तिः_बहुलकम् e_पङ्क्तिः_निवेशः_बहुलकम्, uint32_t unFlags, वर्ण * pchDescription, uint32_t unCharMax, वर्ण * pchExistingText, uint64_t u_User_मानम्);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetKeyboardText)(वर्ण * pchText, uint32_t cchText);
	शून्य (OPENVR_FNTABLE_CALLTYPE *HideKeyboard)();
	शून्य (OPENVR_FNTABLE_CALLTYPE *समुच्चयः_Keyboard_Transform_Absolute)(ETrackingUniverseOrigin eTrackingOrigin, संरचना HmdMatrix34_t * pmat_Tracking_Origin_गन्तव्यम्_Keyboard_Transform);
	शून्य (OPENVR_FNTABLE_CALLTYPE *समुच्चयः_Keyboard_Position_For_Overlay)(VROverlayHandle_t ulOverlayHandle, संरचना HmdRect2_t avoidRect);
	VRMessageOverlayResponse (OPENVR_FNTABLE_CALLTYPE *Show_सन्देशः_Overlay)(वर्ण * pchText, वर्ण * pchCaption, वर्ण * pchButton0Text, वर्ण * pchButton1Text, वर्ण * pchButton2Text, वर्ण * pchButton3Text);
	शून्य (OPENVR_FNTABLE_CALLTYPE *Close_सन्देशः_Overlay)();
};

संरचना VR_IVROverlay_View_Fn_सारणी
{
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *AcquireOverlayView)(VROverlayHandle_t ulOverlayHandle, संरचना VRNativeDevice_t * pNativeDevice, संरचना VROverlayView_t * pOverlayView, uint32_t un_Overlay_View_आकार);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *ReleaseOverlayView)(संरचना VROverlayView_t * pOverlayView);
	शून्य (OPENVR_FNTABLE_CALLTYPE *PostOverlayEvent)(VROverlayHandle_t ulOverlayHandle, संरचना VREvent_t * pvrEvent);
	bool (OPENVR_FNTABLE_CALLTYPE *IsViewingPermitted)(VROverlayHandle_t ulOverlayHandle);
};

संरचना VR_IVRHeadset_View_Fn_सारणी
{
	शून्य (OPENVR_FNTABLE_CALLTYPE *समुच्चयः_Headset_View_आकार)(uint32_t n_विस्तारः, uint32_t nHeight);
	शून्य (OPENVR_FNTABLE_CALLTYPE *Get_Headset_View_आकार)(uint32_t * pn_विस्तारः, uint32_t * pnHeight);
	शून्य (OPENVR_FNTABLE_CALLTYPE *समुच्चयः_Headset_View_बहुलकम्)(Headset_View_बहुलकम्_t e_Headset_View_बहुलकम्);
	Headset_View_बहुलकम्_t (OPENVR_FNTABLE_CALLTYPE *Get_Headset_View_बहुलकम्)();
	शून्य (OPENVR_FNTABLE_CALLTYPE *समुच्चयः_Headset_View_Cropped)(bool bCropped);
	bool (OPENVR_FNTABLE_CALLTYPE *GetHeadsetViewCropped)();
	भिन्न (OPENVR_FNTABLE_CALLTYPE *Get_Headset_View_Aspect_अनुपातः)();
	शून्य (OPENVR_FNTABLE_CALLTYPE *समुच्चयः_Headset_View_Blend_Range)(भिन्न flStartPct, भिन्न fl_अन्तः_Pct);
	शून्य (OPENVR_FNTABLE_CALLTYPE *GetHeadsetViewBlendRange)(भिन्न * pStartPct, भिन्न * p_अन्तः_Pct);
};

संरचना VR_IVRRender_Models_Fn_सारणी
{
	EVRRenderModelError (OPENVR_FNTABLE_CALLTYPE *आरोपय_Render_Model_Async)(वर्ण * pchRenderModelName, संरचना RenderModel_t ** ppRenderModel);
	शून्य (OPENVR_FNTABLE_CALLTYPE *FreeRenderModel)(संरचना RenderModel_t * pRenderModel);
	EVRRenderModelError (OPENVR_FNTABLE_CALLTYPE *आरोपय_Texture_Async)(TextureID_t textureId, संरचना RenderModel_TextureMap_t ** ppTexture);
	शून्य (OPENVR_FNTABLE_CALLTYPE *FreeTexture)(संरचना RenderModel_TextureMap_t * pTexture);
	EVRRenderModelError (OPENVR_FNTABLE_CALLTYPE *आरोपय_Texture_D3_D11_Async)(TextureID_t textureId, शून्य * pD3D11Device, शून्य ** ppD3D11Texture2D);
	EVRRenderModelError (OPENVR_FNTABLE_CALLTYPE *आरोपय_Into_Texture_D3_D11_Async)(TextureID_t textureId, शून्य * pDstTexture);
	शून्य (OPENVR_FNTABLE_CALLTYPE *FreeTextureD3D11)(शून्य * pD3D11Texture2D);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetRenderModelName)(uint32_t un_Render_Model_सूचकांक, वर्ण * pchRenderModelName, uint32_t unRenderModelNameLen);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *Get_Render_Model_गणनम्)();
	uint32_t (OPENVR_FNTABLE_CALLTYPE *Get_Component_गणनम्)(वर्ण * pchRenderModelName);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetComponentName)(वर्ण * pchRenderModelName, uint32_t un_Component_सूचकांक, वर्ण * pchComponentName, uint32_t unComponentNameLen);
	uint64_t (OPENVR_FNTABLE_CALLTYPE *Get_Component_Button_आवरणम्)(वर्ण * pchRenderModelName, वर्ण * pchComponentName);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetComponentRenderModelName)(वर्ण * pchRenderModelName, वर्ण * pchComponentName, वर्ण * pchComponentRenderModelName, uint32_t unComponentRenderModelNameLen);
	bool (OPENVR_FNTABLE_CALLTYPE *Get_Component_State_For_Device_मार्गः)(वर्ण * pchRenderModelName, वर्ण * pchComponentName, VRInput_मानम्_Handle_t device_मार्गः, Render_Model_Controller_बहुलकम्_State_t * pState, RenderModel_ComponentState_t * pComponentState);
	bool (OPENVR_FNTABLE_CALLTYPE *GetComponentState)(वर्ण * pchRenderModelName, वर्ण * pchComponentName, VRControllerState_t * pControllerState, संरचना Render_Model_Controller_बहुलकम्_State_t * pState, संरचना RenderModel_ComponentState_t * pComponentState);
	bool (OPENVR_FNTABLE_CALLTYPE *RenderModelHasComponent)(वर्ण * pchRenderModelName, वर्ण * pchComponentName);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetRenderModelThumbnailURL)(वर्ण * pchRenderModelName, वर्ण * pchThumbnailURL, uint32_t unThumbnailURLLen, EVRRenderModelError * peError);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *Get_Render_Model_Original_मार्गः)(वर्ण * pchRenderModelName, वर्ण * pch_Original_मार्गः, uint32_t un_Original_मार्गः_Len, EVRRenderModelError * peError);
	वर्ण * (OPENVR_FNTABLE_CALLTYPE *GetRenderModelErrorNameFromEnum)(EVRRenderModelError error);
};

संरचना VR_IVRNotifications_Fn_सारणी
{
	EVRNotificationError (OPENVR_FNTABLE_CALLTYPE *CreateNotification)(VROverlayHandle_t ulOverlayHandle, uint64_t ul_User_मानम्, EVRNotificationType type, वर्ण * pchText, EVRNotificationStyle style, संरचना NotificationBitmap_t * pImage, VRNotificationId * pNotificationId);
	EVRNotificationError (OPENVR_FNTABLE_CALLTYPE *RemoveNotification)(VRNotificationId notificationId);
};

संरचना VR_IVRSettings_Fn_सारणी
{
	वर्ण * (OPENVR_FNTABLE_CALLTYPE *GetSettingsErrorNameFromEnum)(EVRSettingsError eError);
	शून्य (OPENVR_FNTABLE_CALLTYPE *समुच्चयः_Bool)(वर्ण * pchSection, वर्ण * pch_Settings_कुञ्चिका, bool b_मानम्, EVRSettingsError * peError);
	शून्य (OPENVR_FNTABLE_CALLTYPE *समुच्चयः_Int32)(वर्ण * pchSection, वर्ण * pch_Settings_कुञ्चिका, int32_t n_मानम्, EVRSettingsError * peError);
	शून्य (OPENVR_FNTABLE_CALLTYPE *समुच्चयः_Float)(वर्ण * pchSection, वर्ण * pch_Settings_कुञ्चिका, भिन्न fl_मानम्, EVRSettingsError * peError);
	शून्य (OPENVR_FNTABLE_CALLTYPE *समुच्चयः_String)(वर्ण * pchSection, वर्ण * pch_Settings_कुञ्चिका, वर्ण * pch_मानम्, EVRSettingsError * peError);
	bool (OPENVR_FNTABLE_CALLTYPE *GetBool)(वर्ण * pchSection, वर्ण * pch_Settings_कुञ्चिका, EVRSettingsError * peError);
	int32_t (OPENVR_FNTABLE_CALLTYPE *GetInt32)(वर्ण * pchSection, वर्ण * pch_Settings_कुञ्चिका, EVRSettingsError * peError);
	भिन्न (OPENVR_FNTABLE_CALLTYPE *GetFloat)(वर्ण * pchSection, वर्ण * pch_Settings_कुञ्चिका, EVRSettingsError * peError);
	शून्य (OPENVR_FNTABLE_CALLTYPE *GetString)(वर्ण * pchSection, वर्ण * pch_Settings_कुञ्चिका, वर्ण * pch_मानम्, uint32_t un_मानम्_Len, EVRSettingsError * peError);
	शून्य (OPENVR_FNTABLE_CALLTYPE *RemoveSection)(वर्ण * pchSection, EVRSettingsError * peError);
	शून्य (OPENVR_FNTABLE_CALLTYPE *Remove_कुञ्चिका_अन्तर्_Section)(वर्ण * pchSection, वर्ण * pch_Settings_कुञ्चिका, EVRSettingsError * peError);
};

संरचना VR_IVRScreenshots_Fn_सारणी
{
	EVRScreenshotError (OPENVR_FNTABLE_CALLTYPE *RequestScreenshot)(ScreenshotHandle_t * p_बहिर्गमनम्_Screenshot_Handle, EVRScreenshotType type, वर्ण * pchPreviewFilename, वर्ण * pchVRFilename);
	EVRScreenshotError (OPENVR_FNTABLE_CALLTYPE *HookScreenshot)(EVRScreenshotType * pSupportedTypes, पूर्णाङ्क अङ्कः_Types);
	EVRScreenshotType (OPENVR_FNTABLE_CALLTYPE *GetScreenshotPropertyType)(ScreenshotHandle_t screenshotHandle, EVRScreenshotError * pError);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetScreenshotPropertyFilename)(ScreenshotHandle_t screenshotHandle, EVRScreenshotPropertyFilenames filenameType, वर्ण * pchFilename, uint32_t cchFilename, EVRScreenshotError * pError);
	EVRScreenshotError (OPENVR_FNTABLE_CALLTYPE *Update_Screenshot_प्रगतिः)(ScreenshotHandle_t screenshotHandle, भिन्न fl_प्रगतिः);
	EVRScreenshotError (OPENVR_FNTABLE_CALLTYPE *TakeStereoScreenshot)(ScreenshotHandle_t * p_बहिर्गमनम्_Screenshot_Handle, वर्ण * pchPreviewFilename, वर्ण * pchVRFilename);
	EVRScreenshotError (OPENVR_FNTABLE_CALLTYPE *SubmitScreenshot)(ScreenshotHandle_t screenshotHandle, EVRScreenshotType type, वर्ण * pchSourcePreviewFilename, वर्ण * pchSourceVRFilename);
};

संरचना VR_IVRResources_Fn_सारणी
{
	uint32_t (OPENVR_FNTABLE_CALLTYPE *आरोपय_Shared_Resource)(वर्ण * pchResourceName, वर्ण * pch_बफर, uint32_t un_बफर_Len);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *Get_Resource_पूर्णम्_मार्गः)(वर्ण * pchResourceName, वर्ण * pchResourceTypeDirectory, वर्ण * pch_मार्गः_बफर, uint32_t un_बफर_Len);
};

संरचना VR_IVRDriver_Manager_Fn_सारणी
{
	uint32_t (OPENVR_FNTABLE_CALLTYPE *Get_Driver_गणनम्)();
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetDriverName)(DriverId_t nDriver, वर्ण * pch_मानम्, uint32_t un_बफर_आकार);
	DriverHandle_t (OPENVR_FNTABLE_CALLTYPE *GetDriverHandle)(वर्ण * pchDriverName);
	bool (OPENVR_FNTABLE_CALLTYPE *IsEnabled)(DriverId_t nDriver);
};

संरचना VR_IVRInput_Fn_सारणी
{
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *समुच्चयः_Action_Manifest_मार्गः)(वर्ण * pch_Action_Manifest_मार्गः);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *Get_Action_समुच्चयः_Handle)(वर्ण * pch_Action_समुच्चयः_Name, VRAction_समुच्चयः_Handle_t * pHandle);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetActionHandle)(वर्ण * pchActionName, VRActionHandle_t * pHandle);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *Get_निवेशः_Source_Handle)(वर्ण * pch_निवेशः_Source_मार्गः, VRInput_मानम्_Handle_t * pHandle);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *UpdateActionState)(संरचना VRActive_Action_समुच्चयः_t * pSets, uint32_t un_आकार_सम्बन्धि_VRSelected_Action_समुच्चयः_t, uint32_t un_समुच्चयः_गणनम्);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *Get_Digital_Action_दत्त)(VRActionHandle_t action, संरचना निवेशः_Digital_Action_दत्त_t * p_Action_दत्त, uint32_t un_Action_दत्त_आकार, VRInput_मानम्_Handle_t ul_Restrict_गन्तव्यम्_Device);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *Get_Analog_Action_दत्त)(VRActionHandle_t action, संरचना निवेशः_Analog_Action_दत्त_t * p_Action_दत्त, uint32_t un_Action_दत्त_आकार, VRInput_मानम्_Handle_t ul_Restrict_गन्तव्यम्_Device);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *Get_Pose_Action_दत्त_Relative_गन्तव्यम्_Now)(VRActionHandle_t action, ETrackingUniverseOrigin eOrigin, भिन्न fPredictedSecondsFromNow, संरचना निवेशः_Pose_Action_दत्त_t * p_Action_दत्त, uint32_t un_Action_दत्त_आकार, VRInput_मानम्_Handle_t ul_Restrict_गन्तव्यम्_Device);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *Get_Pose_Action_दत्त_For_अग्र_Frame)(VRActionHandle_t action, ETrackingUniverseOrigin eOrigin, संरचना निवेशः_Pose_Action_दत्त_t * p_Action_दत्त, uint32_t un_Action_दत्त_आकार, VRInput_मानम्_Handle_t ul_Restrict_गन्तव्यम्_Device);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *Get_Skeletal_Action_दत्त)(VRActionHandle_t action, संरचना निवेशः_Skeletal_Action_दत्त_t * p_Action_दत्त, uint32_t un_Action_दत्त_आकार);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetDominantHand)(ETrackedControllerRole * peDominantHand);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *समुच्चयः_Dominant_Hand)(ETrackedControllerRole eDominantHand);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *Get_Bone_गणनम्)(VRActionHandle_t action, uint32_t * p_Bone_गणनम्);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetBoneHierarchy)(VRActionHandle_t action, Bone_सूचकांक_t * pParentIndices, uint32_t un_सूचकांक_Aray_गणनम्);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetBoneName)(VRActionHandle_t action, Bone_सूचकांक_t n_Bone_सूचकांक, वर्ण * pchBoneName, uint32_t un_Name_बफर_आकार);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetSkeletalReferenceTransforms)(VRActionHandle_t action, EVRSkeletalTransformSpace eTransformSpace, EVRSkeletalReferencePose eReferencePose, संरचना VRBoneTransform_t * pTransformArray, uint32_t un_Transform_Array_गणनम्);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetSkeletalTrackingLevel)(VRActionHandle_t action, EVRSkeletalTrackingLevel * pSkeletalTrackingLevel);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *Get_Skeletal_Bone_दत्त)(VRActionHandle_t action, EVRSkeletalTransformSpace eTransformSpace, EVRSkeletalMotionRange eMotionRange, संरचना VRBoneTransform_t * pTransformArray, uint32_t un_Transform_Array_गणनम्);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *Get_Skeletal_Summary_दत्त)(VRActionHandle_t action, EVRSummaryType eSummaryType, संरचना VRSkeletal_Summary_दत्त_t * p_Skeletal_Summary_दत्त);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *Get_Skeletal_Bone_दत्त_Compressed)(VRActionHandle_t action, EVRSkeletalMotionRange eMotionRange, शून्य * pv_Compressed_दत्त, uint32_t un_Compressed_आकार, uint32_t * pun_Required_Compressed_आकार);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *Decompress_Skeletal_Bone_दत्त)(शून्य * pv_Compressed_बफर, uint32_t un_Compressed_बफर_आकार, EVRSkeletalTransformSpace eTransformSpace, संरचना VRBoneTransform_t * pTransformArray, uint32_t un_Transform_Array_गणनम्);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *TriggerHapticVibrationAction)(VRActionHandle_t action, भिन्न fStartSecondsFromNow, भिन्न fDurationSeconds, भिन्न fFrequency, भिन्न fAmplitude, VRInput_मानम्_Handle_t ul_Restrict_गन्तव्यम्_Device);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetActionOrigins)(VRAction_समुच्चयः_Handle_t action_समुच्चयः_Handle, VRActionHandle_t digitalActionHandle, VRInput_मानम्_Handle_t * origins_बहिर्गमनम्, uint32_t origin_बहिर्गमनम्_गणनम्);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetOriginLocalizedName)(VRInput_मानम्_Handle_t origin, वर्ण * pchNameArray, uint32_t un_Name_Array_आकार, int32_t un_String_Sections_गन्तव्यम्_Include);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetOriginTrackedDeviceInfo)(VRInput_मानम्_Handle_t origin, संरचना निवेशः_Origin_Info_t * pOriginInfo, uint32_t un_Origin_Info_आकार);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetActionBindingInfo)(VRActionHandle_t action, संरचना निवेशः_Binding_Info_t * pOriginInfo, uint32_t un_Binding_Info_आकार, uint32_t un_Binding_Info_गणनम्, uint32_t * pun_Returned_Binding_Info_गणनम्);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *ShowActionOrigins)(VRAction_समुच्चयः_Handle_t action_समुच्चयः_Handle, VRActionHandle_t ulActionHandle);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *Show_Bindings_For_Action_समुच्चयः)(संरचना VRActive_Action_समुच्चयः_t * pSets, uint32_t un_आकार_सम्बन्धि_VRSelected_Action_समुच्चयः_t, uint32_t un_समुच्चयः_गणनम्, VRInput_मानम्_Handle_t origin_गन्तव्यम्_Highlight);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetComponentStateForBinding)(वर्ण * pchRenderModelName, वर्ण * pchComponentName, संरचना निवेशः_Binding_Info_t * pOriginInfo, uint32_t un_Binding_Info_आकार, uint32_t un_Binding_Info_गणनम्, RenderModel_ComponentState_t * pComponentState);
	bool (OPENVR_FNTABLE_CALLTYPE *Is_Using_Legacy_निवेशः)();
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *OpenBindingUI)(वर्ण * pch_App_कुञ्चिका, VRAction_समुच्चयः_Handle_t ul_Action_समुच्चयः_Handle, VRInput_मानम्_Handle_t ulDeviceHandle, bool bShowOnDesktop);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetBindingVariant)(VRInput_मानम्_Handle_t ul_Device_मार्गः, वर्ण * pchVariantArray, uint32_t un_Variant_Array_आकार);
};

संरचना VR_IVRIOBuffer_Fn_सारणी
{
	EIOBufferError (OPENVR_FNTABLE_CALLTYPE *Open)(वर्ण * pch_मार्गः, EIOBuffer_बहुलकम् बहुलकम्, uint32_t un_Element_आकार, uint32_t unElements, IOBufferHandle_t * pul_बफर);
	EIOBufferError (OPENVR_FNTABLE_CALLTYPE *Close)(IOBufferHandle_t ul_बफर);
	EIOBufferError (OPENVR_FNTABLE_CALLTYPE *Read)(IOBufferHandle_t ul_बफर, शून्य * pDst, uint32_t un_अष्टकानि, uint32_t * punRead);
	EIOBufferError (OPENVR_FNTABLE_CALLTYPE *Write)(IOBufferHandle_t ul_बफर, शून्य * pSrc, uint32_t un_अष्टकानि);
	PropertyContainerHandle_t (OPENVR_FNTABLE_CALLTYPE *PropertyContainer)(IOBufferHandle_t ul_बफर);
	bool (OPENVR_FNTABLE_CALLTYPE *HasReaders)(IOBufferHandle_t ul_बफर);
};

संरचना VR_IVRSpatial_Anchors_Fn_सारणी
{
	EVRSpatialAnchorError (OPENVR_FNTABLE_CALLTYPE *CreateSpatialAnchorFromDescriptor)(वर्ण * pchDescriptor, SpatialAnchorHandle_t * p_Handle_बहिर्गमनम्);
	EVRSpatialAnchorError (OPENVR_FNTABLE_CALLTYPE *CreateSpatialAnchorFromPose)(Tracked_Device_सूचकांक_t un_Device_सूचकांक, ETrackingUniverseOrigin eOrigin, संरचना SpatialAnchorPose_t * pPose, SpatialAnchorHandle_t * p_Handle_बहिर्गमनम्);
	EVRSpatialAnchorError (OPENVR_FNTABLE_CALLTYPE *GetSpatialAnchorPose)(SpatialAnchorHandle_t unHandle, ETrackingUniverseOrigin eOrigin, संरचना SpatialAnchorPose_t * p_Pose_बहिर्गमनम्);
	EVRSpatialAnchorError (OPENVR_FNTABLE_CALLTYPE *GetSpatialAnchorDescriptor)(SpatialAnchorHandle_t unHandle, वर्ण * pch_Descriptor_बहिर्गमनम्, uint32_t * pun_Descriptor_बफर_Len_अन्तर्_बहिर्गमनम्);
};

संरचना VR_IVRDebug_Fn_सारणी
{
	EVRDebugError (OPENVR_FNTABLE_CALLTYPE *EmitVrProfilerEvent)(वर्ण * pch_सन्देशः);
	EVRDebugError (OPENVR_FNTABLE_CALLTYPE *BeginVrProfilerEvent)(VrProfilerEventHandle_t * p_Handle_बहिर्गमनम्);
	EVRDebugError (OPENVR_FNTABLE_CALLTYPE *FinishVrProfilerEvent)(VrProfilerEventHandle_t hHandle, वर्ण * pch_सन्देशः);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *DriverDebugRequest)(Tracked_Device_सूचकांक_t un_Device_सूचकांक, वर्ण * pchRequest, वर्ण * pch_Response_बफर, uint32_t un_Response_बफर_आकार);
};

संरचना VR_IVRProperties_Fn_सारणी
{
	ETrackedPropertyError (OPENVR_FNTABLE_CALLTYPE *ReadPropertyBatch)(PropertyContainerHandle_t ulContainerHandle, संरचना PropertyRead_t * pBatch, uint32_t un_Batch_प्रविष्टिः_गणनम्);
	ETrackedPropertyError (OPENVR_FNTABLE_CALLTYPE *WritePropertyBatch)(PropertyContainerHandle_t ulContainerHandle, संरचना PropertyWrite_t * pBatch, uint32_t un_Batch_प्रविष्टिः_गणनम्);
	वर्ण * (OPENVR_FNTABLE_CALLTYPE *GetPropErrorNameFromEnum)(ETrackedPropertyError error);
	PropertyContainerHandle_t (OPENVR_FNTABLE_CALLTYPE *Tracked_Device_गन्तव्यम्_Property_Container)(Tracked_Device_सूचकांक_t nDevice);
};

संरचना VR_IVRPaths_Fn_सारणी
{
	ETrackedPropertyError (OPENVR_FNTABLE_CALLTYPE *Read_मार्गः_Batch)(PropertyContainerHandle_t ul_मूलम्_Handle, संरचना मार्गः_Read_t * pBatch, uint32_t un_Batch_प्रविष्टिः_गणनम्);
	ETrackedPropertyError (OPENVR_FNTABLE_CALLTYPE *Write_मार्गः_Batch)(PropertyContainerHandle_t ul_मूलम्_Handle, संरचना मार्गः_Write_t * pBatch, uint32_t un_Batch_प्रविष्टिः_गणनम्);
	ETrackedPropertyError (OPENVR_FNTABLE_CALLTYPE *String_गन्तव्यम्_Handle)(मार्गः_Handle_t * pHandle, वर्ण * pch_मार्गः);
	ETrackedPropertyError (OPENVR_FNTABLE_CALLTYPE *Handle_गन्तव्यम्_String)(मार्गः_Handle_t pHandle, वर्ण * pch_बफर, uint32_t un_बफर_आकार, uint32_t * pun_बफर_आकार_प्रयुक्तम्);
};

संरचना VR_IVRBlock_Queue_Fn_सारणी
{
	EBlockQueueError (OPENVR_FNTABLE_CALLTYPE *Create)(PropertyContainerHandle_t * pulQueueHandle, वर्ण * pch_मार्गः, uint32_t un_खण्डम्_दत्त_आकार, uint32_t un_खण्डम्_शीर्षकम्_आकार, uint32_t un_खण्डम्_गणनम्, uint32_t unFlags);
	EBlockQueueError (OPENVR_FNTABLE_CALLTYPE *Connect)(PropertyContainerHandle_t * pulQueueHandle, वर्ण * pch_मार्गः);
	EBlockQueueError (OPENVR_FNTABLE_CALLTYPE *Destroy)(PropertyContainerHandle_t ulQueueHandle);
	EBlockQueueError (OPENVR_FNTABLE_CALLTYPE *Acquire_Write_Only_खण्डम्)(PropertyContainerHandle_t ulQueueHandle, PropertyContainerHandle_t * pul_खण्डम्_Handle, शून्य ** ppv_बफर);
	EBlockQueueError (OPENVR_FNTABLE_CALLTYPE *Release_Write_Only_खण्डम्)(PropertyContainerHandle_t ulQueueHandle, PropertyContainerHandle_t ul_खण्डम्_Handle);
	EBlockQueueError (OPENVR_FNTABLE_CALLTYPE *Wait_And_Acquire_Read_Only_खण्डम्)(PropertyContainerHandle_t ulQueueHandle, PropertyContainerHandle_t * pul_खण्डम्_Handle, शून्य ** ppv_बफर, EBlockQueueReadType eReadType, uint32_t unTimeoutMs);
	EBlockQueueError (OPENVR_FNTABLE_CALLTYPE *Acquire_Read_Only_खण्डम्)(PropertyContainerHandle_t ulQueueHandle, PropertyContainerHandle_t * pul_खण्डम्_Handle, शून्य ** ppv_बफर, EBlockQueueReadType eReadType);
	EBlockQueueError (OPENVR_FNTABLE_CALLTYPE *Release_Read_Only_खण्डम्)(PropertyContainerHandle_t ulQueueHandle, PropertyContainerHandle_t ul_खण्डम्_Handle);
	EBlockQueueError (OPENVR_FNTABLE_CALLTYPE *QueueHasReader)(PropertyContainerHandle_t ulQueueHandle, bool * pbHasReaders);
};


#यदि 0
// Global entry points
S_API intptr_t VR_Init_आन्तरिकम्( EVRInitError *peError, EVRApplicationType eType );
S_API शून्य VR_Shutdown_आन्तरिकम्();
S_API bool VR_IsHmdPresent();
S_API intptr_t VR_GetGenericInterface( ध्रुव वर्ण *pch_Interface_संस्करणम्, EVRInitError *peError );
S_API bool VR_IsRuntimeInstalled();
S_API ध्रुव वर्ण * VR_Get_VRInit_Error_As_चिह्नम्( EVRInitError error );
S_API ध्रुव वर्ण * VR_GetVRInitErrorAsEnglishDescription( EVRInitError error );
#यदि_अन्तः

#यदि_अन्तः // __OPENVR_API_FLAT_H__


