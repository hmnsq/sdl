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

#که_نه_تعریف_شوی __OPENVR_API_FLAT_H__
#تعریف_کړه __OPENVR_API_FLAT_H__
#إذا defined( _WIN32 ) || defined( __clang__ )
#لارښوونه once
#د_که_پای

#که_تعریف_شوی __cplusplus
#تعریف_کړه EXTERN_C خارجي "C"
#وإلا
#تعریف_کړه EXTERN_C
#د_که_پای

#إذا defined( _WIN32 )
#تعریف_کړه OPENVR_FNTABLE_CALLTYPE __stdcall
#وإلا
#تعریف_کړه OPENVR_FNTABLE_CALLTYPE 
#د_که_پای

// OPENVR API export macro
#إذا defined( _WIN32 ) && !defined( _X360 )
	#إذا defined( OPENVR_API_EXPORTS )
	#تعریف_کړه S_API EXTERN_C __declspec( dllexport )
	#وإلاإذا defined( OPENVR_API_NODLL )
	#تعریف_کړه S_API EXTERN_C
	#وإلا
	#تعریف_کړه S_API خارجي "C" __declspec( dllimport ) 
	#د_که_پای // OPENVR_API_EXPORTS
#وإلاإذا defined( __GNUC__ )
	#إذا defined( OPENVR_API_EXPORTS )
	#تعریف_کړه S_API EXTERN_C __attribute__ ((visibility("default")))
	#وإلا
	#تعریف_کړه S_API EXTERN_C
	#د_که_پای // OPENVR_API_EXPORTS
#وإلا // !WIN32
	#إذا defined( OPENVR_API_EXPORTS )
	#تعریف_کړه S_API EXTERN_C
	#وإلا
	#تعریف_کړه S_API EXTERN_C
	#د_که_پای // OPENVR_API_EXPORTS
#د_که_پای

#که_نه_تعریف_شوی USE_SDL
#ضمن <stdint.h>

#إذا defined( __WIN32 )
تعريفنوع حرف bool;
#وإلا
#ضمن <stdbool.h>
#د_که_پای
#د_که_پای // USE_SDL

// OpenVR Constants

ساكن ثابت بینښه اوږد k_nDriverNone = 4294967295;
ساكن ثابت بینښه اوږد k_un_Max_Driver_Debug_Response_اندازه = 32768;
ساكن ثابت بینښه اوږد k_un_Tracked_Device_شاخص_Hmd = 0;
ساكن ثابت بینښه اوږد k_un_Max_Tracked_Device_شمېر = 64;
ساكن ثابت بینښه اوږد k_un_Tracked_Device_شاخص_Other = 4294967294;
ساكن ثابت بینښه اوږد k_un_Tracked_Device_شاخص_Invalid = 4294967295;
ساكن ثابت بینښه اوږد اوږد k_ulInvalidPropertyContainer = 0;
ساكن ثابت بینښه اوږد k_un_Invalid_Property_نښان = 0;
ساكن ثابت بینښه اوږد اوږد k_ulInvalidDriverHandle = 0;
ساكن ثابت بینښه اوږد k_un_Float_Property_نښان = 1;
ساكن ثابت بینښه اوږد k_un_Int32_Property_نښان = 2;
ساكن ثابت بینښه اوږد k_un_Uint64_Property_نښان = 3;
ساكن ثابت بینښه اوږد k_un_Bool_Property_نښان = 4;
ساكن ثابت بینښه اوږد k_un_String_Property_نښان = 5;
ساكن ثابت بینښه اوږد k_un_Error_Property_نښان = 6;
ساكن ثابت بینښه اوږد k_un_Double_Property_نښان = 7;
ساكن ثابت بینښه اوږد k_un_Hmd_Matrix34_Property_نښان = 20;
ساكن ثابت بینښه اوږد k_un_Hmd_Matrix44_Property_نښان = 21;
ساكن ثابت بینښه اوږد k_un_Hmd_Vector3_Property_نښان = 22;
ساكن ثابت بینښه اوږد k_un_Hmd_Vector4_Property_نښان = 23;
ساكن ثابت بینښه اوږد k_un_Hmd_Vector2_Property_نښان = 24;
ساكن ثابت بینښه اوږد k_un_Hmd_Quad_Property_نښان = 25;
ساكن ثابت بینښه اوږد k_un_Hidden_Area_Property_نښان = 30;
ساكن ثابت بینښه اوږد k_un_لار_Handle_Info_نښان = 31;
ساكن ثابت بینښه اوږد k_un_Action_Property_نښان = 32;
ساكن ثابت بینښه اوږد k_un_ننوت_ارزښت_Property_نښان = 33;
ساكن ثابت بینښه اوږد k_un_Wildcard_Property_نښان = 34;
ساكن ثابت بینښه اوږد k_un_Haptic_Vibration_Property_نښان = 35;
ساكن ثابت بینښه اوږد k_un_Skeleton_Property_نښان = 36;
ساكن ثابت بینښه اوږد k_un_Spatial_Anchor_Pose_Property_نښان = 40;
ساكن ثابت بینښه اوږد k_un_Json_Property_نښان = 41;
ساكن ثابت بینښه اوږد k_un_فعال_Action_سېټ_Property_نښان = 42;
ساكن ثابت بینښه اوږد k_un_Open_VRInternal_Reserved_پیل = 1000;
ساكن ثابت بینښه اوږد k_un_Open_VRInternal_Reserved_پای_ټکی = 10000;
ساكن ثابت بینښه اوږد k_un_Max_Property_String_اندازه = 32768;
ساكن ثابت بینښه اوږد اوږد k_ulInvalidActionHandle = 0;
ساكن ثابت بینښه اوږد اوږد k_ul_Invalid_Action_سېټ_Handle = 0;
ساكن ثابت بینښه اوږد اوږد k_ul_Invalid_ننوت_ارزښت_Handle = 0;
ساكن ثابت بینښه اوږد k_un_Controller_State_Axis_شمېر = 5;
ساكن ثابت بینښه اوږد اوږد k_ulOverlayHandleInvalid = 0;
ساكن ثابت بینښه اوږد k_unMaxDistortionFunctionParameters = 8;
ساكن ثابت بینښه اوږد k_unScreenshotHandleInvalid = 0;
ساكن ثابت حرف * IVRSystem_نسخه = "IVRSystem_022";
ساكن ثابت حرف * IVRExtended_Display_نسخه = "IVRExtendedDisplay_001";
ساكن ثابت حرف * IVRTracked_Camera_نسخه = "IVRTrackedCamera_006";
ساكن ثابت بینښه اوږد k_un_Max_Application_کلی_اوږدتیا = 128;
ساكن ثابت حرف * k_pch_MimeType_HomeApp = "vr/home";
ساكن ثابت حرف * k_pch_MimeType_GameTheater = "vr/game_theater";
ساكن ثابت حرف * IVRApplications_نسخه = "IVRApplications_007";
ساكن ثابت حرف * IVRChaperone_نسخه = "IVRChaperone_004";
ساكن ثابت حرف * IVRChaperone_تیاری_نسخه = "IVRChaperoneSetup_006";
ساكن ثابت حرف * IVRCompositor_نسخه = "IVRCompositor_027";
ساكن ثابت بینښه اوږد k_un_VROverlay_Max_کلی_اوږدتیا = 128;
ساكن ثابت بینښه اوږد k_un_VROverlay_Max_Name_اوږدتیا = 128;
ساكن ثابت بینښه اوږد k_un_Max_Overlay_شمېر = 128;
ساكن ثابت بینښه اوږد k_un_Max_Overlay_Intersection_ماسک_Primitives_شمېر = 32;
ساكن ثابت حرف * IVROverlay_نسخه = "IVROverlay_026";
ساكن ثابت حرف * IVROverlay_View_نسخه = "IVROverlayView_003";
ساكن ثابت بینښه اوږد k_un_Headset_View_Max_پلنوالی = 3840;
ساكن ثابت بینښه اوږد k_un_Headset_View_Max_لوړوالی = 2160;
ساكن ثابت حرف * k_pch_Headset_View_Overlay_کلی = "system.HeadsetView";
ساكن ثابت حرف * IVRHeadset_View_نسخه = "IVRHeadsetView_001";
ساكن ثابت حرف * k_pch_Controller_Component_GDC2015 = "gdc2015";
ساكن ثابت حرف * k_pch_Controller_Component_بنسټ = "base";
ساكن ثابت حرف * k_pch_Controller_Component_Tip = "tip";
ساكن ثابت حرف * k_pch_Controller_Component_OpenXR_Aim = "openxr_aim";
ساكن ثابت حرف * k_pch_Controller_Component_HandGrip = "handgrip";
ساكن ثابت حرف * k_pch_Controller_Component_OpenXR_Grip = "openxr_grip";
ساكن ثابت حرف * k_pch_Controller_Component_OpenXR_HandModel = "openxr_handmodel";
ساكن ثابت حرف * k_pch_Controller_Component_حالت = "status";
ساكن ثابت حرف * IVRRender_Models_نسخه = "IVRRenderModels_006";
ساكن ثابت بینښه اوږد k_un_Notification_متن_Max_اندازه = 256;
ساكن ثابت حرف * IVRNotifications_نسخه = "IVRNotifications_002";
ساكن ثابت بینښه اوږد k_un_Max_Settings_کلی_اوږدتیا = 128;
ساكن ثابت حرف * IVRSettings_نسخه = "IVRSettings_003";
ساكن ثابت حرف * k_pch_SteamVR_Section = "steamvr";
ساكن ثابت حرف * k_pch_SteamVR_RequireHmd_String = "requireHmd";
ساكن ثابت حرف * k_pch_Steam_VR_Forced_Driver_کلی_String = "forcedDriver";
ساكن ثابت حرف * k_pch_Steam_VR_Forced_Hmd_کلی_String = "forcedHmd";
ساكن ثابت حرف * k_pch_SteamVR_DisplayDebug_Bool = "displayDebug";
ساكن ثابت حرف * k_pch_SteamVR_DebugProcessPipe_String = "debugProcessPipe";
ساكن ثابت حرف * k_pch_SteamVR_DisplayDebugX_Int32 = "displayDebugX";
ساكن ثابت حرف * k_pch_SteamVR_DisplayDebugY_Int32 = "displayDebugY";
ساكن ثابت حرف * k_pch_Steam_VR_Send_System_Button_منزل_All_Apps_Bool = "sendSystemButtonToAllApps";
ساكن ثابت حرف * k_pch_SteamVR_LogLevel_Int32 = "loglevel";
ساكن ثابت حرف * k_pch_SteamVR_IPD_Float = "ipd";
ساكن ثابت حرف * k_pch_SteamVR_Background_String = "background";
ساكن ثابت حرف * k_pch_SteamVR_BackgroundUseDomeProjection_Bool = "backgroundUseDomeProjection";
ساكن ثابت حرف * k_pch_Steam_VR_Background_Camera_لوړوالی_Float = "backgroundCameraHeight";
ساكن ثابت حرف * k_pch_SteamVR_BackgroundDomeRadius_Float = "backgroundDomeRadius";
ساكن ثابت حرف * k_pch_SteamVR_GridColor_String = "gridColor";
ساكن ثابت حرف * k_pch_SteamVR_PlayAreaColor_String = "playAreaColor";
ساكن ثابت حرف * k_pch_SteamVR_TrackingLossColor_String = "trackingLossColor";
ساكن ثابت حرف * k_pch_SteamVR_ShowStage_Bool = "showStage";
ساكن ثابت حرف * k_pch_SteamVR_DrawTrackingReferences_Bool = "drawTrackingReferences";
ساكن ثابت حرف * k_pch_Steam_VR_Activate_مضرب_Drivers_Bool = "activateMultipleDrivers";
ساكن ثابت حرف * k_pch_SteamVR_UsingSpeakers_Bool = "usingSpeakers";
ساكن ثابت حرف * k_pch_Steam_VR_Speakers_Forward_Yaw_دننه_واټن_Degrees_Float = "speakersForwardYawOffsetDegrees";
ساكن ثابت حرف * k_pch_Steam_VR_بنسټ_Station_Power_Management_Int32 = "basestationPowerManagement";
ساكن ثابت حرف * k_pch_Steam_VR_Show_بنسټ_Station_Power_Management_Tip_Int32 = "ShowBaseStationPowerManagementTip";
ساكن ثابت حرف * k_pch_SteamVR_NeverKillProcesses_Bool = "neverKillProcesses";
ساكن ثابت حرف * k_pch_SteamVR_SupersampleScale_Float = "supersampleScale";
ساكن ثابت حرف * k_pch_SteamVR_MaxRecommendedResolution_Int32 = "maxRecommendedResolution";
ساكن ثابت حرف * k_pch_SteamVR_MotionSmoothing_Bool = "motionSmoothing";
ساكن ثابت حرف * k_pch_SteamVR_MotionSmoothingOverride_Int32 = "motionSmoothingOverride";
ساكن ثابت حرف * k_pch_Steam_VR_چوکاټونه_منزل_Throttle_Int32 = "framesToThrottle";
ساكن ثابت حرف * k_pch_Steam_VR_Additional_چوکاټونه_منزل_Predict_Int32 = "additionalFramesToPredict";
ساكن ثابت حرف * k_pch_SteamVR_WorldScale_Float = "worldScale";
ساكن ثابت حرف * k_pch_SteamVR_FovScale_Int32 = "fovScale";
ساكن ثابت حرف * k_pch_SteamVR_DisableAsyncReprojection_Bool = "disableAsync";
ساكن ثابت حرف * k_pch_SteamVR_ForceFadeOnBadTracking_Bool = "forceFadeOnBadTracking";
ساكن ثابت حرف * k_pch_SteamVR_DefaultMirrorView_Int32 = "mirrorView";
ساكن ثابت حرف * k_pch_SteamVR_ShowLegacyMirrorView_Bool = "showLegacyMirrorView";
ساكن ثابت حرف * k_pch_SteamVR_MirrorViewVisibility_Bool = "showMirrorView";
ساكن ثابت حرف * k_pch_Steam_VR_Mirror_View_Display_ډېرپېښ_Int32 = "mirrorViewDisplayMode";
ساكن ثابت حرف * k_pch_SteamVR_MirrorViewEye_Int32 = "mirrorViewEye";
ساكن ثابت حرف * k_pch_SteamVR_MirrorViewGeometry_String = "mirrorViewGeometry";
ساكن ثابت حرف * k_pch_SteamVR_MirrorViewGeometryMaximized_String = "mirrorViewGeometryMaximized";
ساكن ثابت حرف * k_pch_Steam_VR_Perf_ګراف_Visibility_Bool = "showPerfGraph";
ساكن ثابت حرف * k_pch_Steam_VR_پیل_Monitor_From_App_Launch = "startMonitorFromAppLaunch";
ساكن ثابت حرف * k_pch_Steam_VR_پیل_Compositor_From_App_Launch_Bool = "startCompositorFromAppLaunch";
ساكن ثابت حرف * k_pch_Steam_VR_پیل_Dashboard_From_App_Launch_Bool = "startDashboardFromAppLaunch";
ساكن ثابت حرف * k_pch_Steam_VR_پیل_Overlay_Apps_From_Dashboard_Bool = "startOverlayAppsFromDashboard";
ساكن ثابت حرف * k_pch_SteamVR_EnableHomeApp = "enableHomeApp";
ساكن ثابت حرف * k_pch_Steam_VR_دوره_Background_Image_وخت_Sec_Int32 = "CycleBackgroundImageTimeSec";
ساكن ثابت حرف * k_pch_SteamVR_RetailDemo_Bool = "retailDemo";
ساكن ثابت حرف * k_pch_Steam_VR_Ipd_دننه_واټن_Float = "ipdOffset";
ساكن ثابت حرف * k_pch_SteamVR_AllowSupersampleFiltering_Bool = "allowSupersampleFiltering";
ساكن ثابت حرف * k_pch_SteamVR_SupersampleManualOverride_Bool = "supersampleManualOverride";
ساكن ثابت حرف * k_pch_SteamVR_EnableLinuxVulkanAsync_Bool = "enableLinuxVulkanAsync";
ساكن ثابت حرف * k_pch_Steam_VR_Allow_Display_Locked_ډېرپېښ_Bool = "allowDisplayLockedMode";
ساكن ثابت حرف * k_pch_SteamVR_HaveStartedTutorialForNativeChaperoneDriver_Bool = "haveStartedTutorialForNativeChaperoneDriver";
ساكن ثابت حرف * k_pch_SteamVR_ForceWindows32bitVRMonitor = "forceWindows32BitVRMonitor";
ساكن ثابت حرف * k_pch_Steam_VR_Debug_ننوت_Binding = "debugInputBinding";
ساكن ثابت حرف * k_pch_Steam_VR_Do_Not_Fade_منزل_Grid = "doNotFadeToGrid";
ساكن ثابت حرف * k_pch_Steam_VR_Render_Camera_ډېرپېښ = "renderCameraMode";
ساكن ثابت حرف * k_pch_SteamVR_EnableSharedResourceJournaling = "enableSharedResourceJournaling";
ساكن ثابت حرف * k_pch_Steam_VR_Enable_خوندي_ډېرپېښ = "enableSafeMode";
ساكن ثابت حرف * k_pch_Steam_VR_Preferred_Refresh_شرح = "preferredRefreshRate";
ساكن ثابت حرف * k_pch_Steam_VR_وروستی_نسخه_Notice = "lastVersionNotice";
ساكن ثابت حرف * k_pch_Steam_VR_وروستی_نسخه_Notice_Date = "lastVersionNoticeDate";
ساكن ثابت حرف * k_pch_SteamVR_HmdDisplayColorGainR_Float = "hmdDisplayColorGainR";
ساكن ثابت حرف * k_pch_SteamVR_HmdDisplayColorGainG_Float = "hmdDisplayColorGainG";
ساكن ثابت حرف * k_pch_SteamVR_HmdDisplayColorGainB_Float = "hmdDisplayColorGainB";
ساكن ثابت حرف * k_pch_SteamVR_CustomIconStyle_String = "customIconStyle";
ساكن ثابت حرف * k_pch_SteamVR_CustomOffIconStyle_String = "customOffIconStyle";
ساكن ثابت حرف * k_pch_SteamVR_CustomIconForceUpdate_String = "customIconForceUpdate";
ساكن ثابت حرف * k_pch_Steam_VR_Allow_Global_Action_سېټ_لومړیتوب = "globalActionSetPriority";
ساكن ثابت حرف * k_pch_SteamVR_OverlayRenderQuality = "overlayRenderQuality_2";
ساكن ثابت حرف * k_pch_Steam_VR_بلاک_Oculus_SDKOn_Open_VRLaunch_Option_Bool = "blockOculusSDKOnOpenVRLaunchOption";
ساكن ثابت حرف * k_pch_Steam_VR_بلاک_Oculus_SDKOn_All_Launches_Bool = "blockOculusSDKOnAllLaunches";
ساكن ثابت حرف * k_pch_SteamVR_HDCPLegacyCompatibility_Bool = "hdcp14legacyCompatibility";
ساكن ثابت حرف * k_pch_Steam_VR_Display_پورټ_Training_ډېرپېښ_Int = "displayPortTrainingMode";
ساكن ثابت حرف * k_pch_SteamVR_UsePrism_Bool = "usePrism";
ساكن ثابت حرف * k_pch_مستقیم_ډېرپېښ_Section = "direct_mode";
ساكن ثابت حرف * k_pch_مستقیم_ډېرپېښ_Enable_Bool = "enable";
ساكن ثابت حرف * k_pch_مستقیم_ډېرپېښ_شمېر_Int32 = "count";
ساكن ثابت حرف * k_pch_مستقیم_ډېرپېښ_Edid_Vid_Int32 = "edidVid";
ساكن ثابت حرف * k_pch_مستقیم_ډېرپېښ_Edid_Pid_Int32 = "edidPid";
ساكن ثابت حرف * k_pch_Lighthouse_Section = "driver_lighthouse";
ساكن ثابت حرف * k_pch_Lighthouse_DisableIMU_Bool = "disableimu";
ساكن ثابت حرف * k_pch_Lighthouse_DisableIMUExceptHMD_Bool = "disableimuexcepthmd";
ساكن ثابت حرف * k_pch_Lighthouse_UseDisambiguation_String = "usedisambiguation";
ساكن ثابت حرف * k_pch_Lighthouse_DisambiguationDebug_Int32 = "disambiguationdebug";
ساكن ثابت حرف * k_pch_Lighthouse_PrimaryBasestation_Int32 = "primarybasestation";
ساكن ثابت حرف * k_pch_Lighthouse_DBHistory_Bool = "dbhistory";
ساكن ثابت حرف * k_pch_Lighthouse_EnableBluetooth_Bool = "enableBluetooth";
ساكن ثابت حرف * k_pch_Lighthouse_Power_Managed_بنسټ_Stations_String = "PowerManagedBaseStations";
ساكن ثابت حرف * k_pch_Lighthouse_Power_Managed_بنسټ_Stations2_String = "PowerManagedBaseStations2";
ساكن ثابت حرف * k_pch_Lighthouse_Inactivity_Timeout_For_بنسټ_Stations_Int32 = "InactivityTimeoutForBaseStations";
ساكن ثابت حرف * k_pch_Lighthouse_EnableImuFallback_Bool = "enableImuFallback";
ساكن ثابت حرف * k_pch_Null_Section = "driver_null";
ساكن ثابت حرف * k_pch_Null_Serial_شمېره_String = "serialNumber";
ساكن ثابت حرف * k_pch_Null_Model_شمېره_String = "modelNumber";
ساكن ثابت حرف * k_pch_Null_کړکۍ_X_Int32 = "windowX";
ساكن ثابت حرف * k_pch_Null_کړکۍ_Y_Int32 = "windowY";
ساكن ثابت حرف * k_pch_Null_کړکۍ_پلنوالی_Int32 = "windowWidth";
ساكن ثابت حرف * k_pch_Null_کړکۍ_لوړوالی_Int32 = "windowHeight";
ساكن ثابت حرف * k_pch_Null_Render_پلنوالی_Int32 = "renderWidth";
ساكن ثابت حرف * k_pch_Null_Render_لوړوالی_Int32 = "renderHeight";
ساكن ثابت حرف * k_pch_Null_Seconds_From_Vsync_منزل_Photons_Float = "secondsFromVsyncToPhotons";
ساكن ثابت حرف * k_pch_Null_DisplayFrequency_Float = "displayFrequency";
ساكن ثابت حرف * k_pch_WindowsMR_Section = "driver_holographic";
ساكن ثابت حرف * k_pch_UserInterface_Section = "userinterface";
ساكن ثابت حرف * k_pch_User_Interface_حالت_Always_On_سر_Bool = "StatusAlwaysOnTop";
ساكن ثابت حرف * k_pch_User_Interface_Minimize_منزل_Tray_Bool = "MinimizeToTray";
ساكن ثابت حرف * k_pch_User_Interface_Hide_Popups_When_حالت_Minimized_Bool = "HidePopupsWhenStatusMinimized";
ساكن ثابت حرف * k_pch_UserInterface_Screenshots_Bool = "screenshots";
ساكن ثابت حرف * k_pch_UserInterface_ScreenshotType_Int = "screenshotType";
ساكن ثابت حرف * k_pch_Notifications_Section = "notifications";
ساكن ثابت حرف * k_pch_Notifications_DoNotDisturb_Bool = "DoNotDisturb";
ساكن ثابت حرف * k_pch_Keyboard_Section = "keyboard";
ساكن ثابت حرف * k_pch_Keyboard_TutorialCompletions = "TutorialCompletions";
ساكن ثابت حرف * k_pch_Keyboard_ScaleX = "ScaleX";
ساكن ثابت حرف * k_pch_Keyboard_ScaleY = "ScaleY";
ساكن ثابت حرف * k_pch_Keyboard_دننه_واټن_کیڼ_X = "OffsetLeftX";
ساكن ثابت حرف * k_pch_Keyboard_دننه_واټن_ښی_X = "OffsetRightX";
ساكن ثابت حرف * k_pch_Keyboard_دننه_واټن_Y = "OffsetY";
ساكن ثابت حرف * k_pch_Keyboard_Smoothing = "Smoothing";
ساكن ثابت حرف * k_pch_Perf_Section = "perfcheck";
ساكن ثابت حرف * k_pch_Perf_Perf_ګراف_دننه_HMD_Bool = "perfGraphInHMD";
ساكن ثابت حرف * k_pch_Perf_AllowTimingStore_Bool = "allowTimingStore";
ساكن ثابت حرف * k_pch_Perf_SaveTimingsOnExit_Bool = "saveTimingsOnExit";
ساكن ثابت حرف * k_pch_Perf_Test_معلومات_Float = "perfTestData";
ساكن ثابت حرف * k_pch_Perf_GPUProfiling_Bool = "GPUProfiling";
ساكن ثابت حرف * k_pch_CollisionBounds_Section = "collisionBounds";
ساكن ثابت حرف * k_pch_CollisionBounds_Style_Int32 = "CollisionBoundsStyle";
ساكن ثابت حرف * k_pch_CollisionBounds_GroundPerimeterOn_Bool = "CollisionBoundsGroundPerimeterOn";
ساكن ثابت حرف * k_pch_CollisionBounds_CenterMarkerOn_Bool = "CollisionBoundsCenterMarkerOn";
ساكن ثابت حرف * k_pch_CollisionBounds_PlaySpaceOn_Bool = "CollisionBoundsPlaySpaceOn";
ساكن ثابت حرف * k_pch_Collision_Bounds_Fade_واټن_Float = "CollisionBoundsFadeDistance";
ساكن ثابت حرف * k_pch_Collision_Bounds_Wall_لوړوالی_Float = "CollisionBoundsWallHeight";
ساكن ثابت حرف * k_pch_CollisionBounds_ColorGammaR_Int32 = "CollisionBoundsColorGammaR";
ساكن ثابت حرف * k_pch_CollisionBounds_ColorGammaG_Int32 = "CollisionBoundsColorGammaG";
ساكن ثابت حرف * k_pch_CollisionBounds_ColorGammaB_Int32 = "CollisionBoundsColorGammaB";
ساكن ثابت حرف * k_pch_CollisionBounds_ColorGammaA_Int32 = "CollisionBoundsColorGammaA";
ساكن ثابت حرف * k_pch_CollisionBounds_EnableDriverImport = "enableDriverBoundsImport";
ساكن ثابت حرف * k_pch_Camera_Section = "camera";
ساكن ثابت حرف * k_pch_Camera_EnableCamera_Bool = "enableCamera";
ساكن ثابت حرف * k_pch_Camera_ShowOnController_Bool = "showOnController";
ساكن ثابت حرف * k_pch_Camera_EnableCameraForCollisionBounds_Bool = "enableCameraForCollisionBounds";
ساكن ثابت حرف * k_pch_Camera_ځای_View_Int32 = "roomView";
ساكن ثابت حرف * k_pch_Camera_BoundsColorGammaR_Int32 = "cameraBoundsColorGammaR";
ساكن ثابت حرف * k_pch_Camera_BoundsColorGammaG_Int32 = "cameraBoundsColorGammaG";
ساكن ثابت حرف * k_pch_Camera_BoundsColorGammaB_Int32 = "cameraBoundsColorGammaB";
ساكن ثابت حرف * k_pch_Camera_BoundsColorGammaA_Int32 = "cameraBoundsColorGammaA";
ساكن ثابت حرف * k_pch_Camera_BoundsStrength_Int32 = "cameraBoundsStrength";
ساكن ثابت حرف * k_pch_Camera_ځای_View_Style_Int32 = "roomViewStyle";
ساكن ثابت حرف * k_pch_audio_Section = "audio";
ساكن ثابت حرف * k_pch_audio_سېټ_Os_Default_Playback_Device_Bool = "setOsDefaultPlaybackDevice";
ساكن ثابت حرف * k_pch_audio_EnablePlaybackDeviceOverride_Bool = "enablePlaybackDeviceOverride";
ساكن ثابت حرف * k_pch_audio_PlaybackDeviceOverride_String = "playbackDeviceOverride";
ساكن ثابت حرف * k_pch_audio_PlaybackDeviceOverrideName_String = "playbackDeviceOverrideName";
ساكن ثابت حرف * k_pch_audio_سېټ_Os_Default_Recording_Device_Bool = "setOsDefaultRecordingDevice";
ساكن ثابت حرف * k_pch_audio_EnableRecordingDeviceOverride_Bool = "enableRecordingDeviceOverride";
ساكن ثابت حرف * k_pch_audio_RecordingDeviceOverride_String = "recordingDeviceOverride";
ساكن ثابت حرف * k_pch_audio_RecordingDeviceOverrideName_String = "recordingDeviceOverrideName";
ساكن ثابت حرف * k_pch_audio_EnablePlaybackMirror_Bool = "enablePlaybackMirror";
ساكن ثابت حرف * k_pch_audio_PlaybackMirrorDevice_String = "playbackMirrorDevice";
ساكن ثابت حرف * k_pch_audio_PlaybackMirrorDeviceName_String = "playbackMirrorDeviceName";
ساكن ثابت حرف * k_pch_audio_OldPlaybackMirrorDevice_String = "onPlaybackMirrorDevice";
ساكن ثابت حرف * k_pch_audio_فعال_Mirror_Device_String = "activePlaybackMirrorDevice";
ساكن ثابت حرف * k_pch_audio_EnablePlaybackMirrorIndependentVolume_Bool = "enablePlaybackMirrorIndependentVolume";
ساكن ثابت حرف * k_pch_audio_وروستی_Hmd_Playback_Device_Id_String = "lastHmdPlaybackDeviceId";
ساكن ثابت حرف * k_pch_audio_VIVEHDMIGain = "viveHDMIGain";
ساكن ثابت حرف * k_pch_audio_DualSpeakerAndJackOutput_Bool = "dualSpeakerAndJackOutput";
ساكن ثابت حرف * k_pch_audio_MuteMicMonitor_Bool = "muteMicMonitor";
ساكن ثابت حرف * k_pch_Power_Section = "power";
ساكن ثابت حرف * k_pch_Power_PowerOffOnExit_Bool = "powerOffOnExit";
ساكن ثابت حرف * k_pch_Power_TurnOffScreensTimeout_Float = "turnOffScreensTimeout";
ساكن ثابت حرف * k_pch_Power_TurnOffControllersTimeout_Float = "turnOffControllersTimeout";
ساكن ثابت حرف * k_pch_Power_Return_منزل_Watchdog_Timeout_Float = "returnToWatchdogTimeout";
ساكن ثابت حرف * k_pch_Power_AutoLaunchSteamVROnButtonPress = "autoLaunchSteamVROnButtonPress";
ساكن ثابت حرف * k_pch_Power_PauseCompositorOnStandby_Bool = "pauseCompositorOnStandby";
ساكن ثابت حرف * k_pch_Dashboard_Section = "dashboard";
ساكن ثابت حرف * k_pch_Dashboard_EnableDashboard_Bool = "enableDashboard";
ساكن ثابت حرف * k_pch_Dashboard_Arcade_ډېرپېښ_Bool = "arcadeMode";
ساكن ثابت حرف * k_pch_Dashboard_Position = "position";
ساكن ثابت حرف * k_pch_Dashboard_DesktopScale = "desktopScale";
ساكن ثابت حرف * k_pch_Dashboard_DashboardScale = "dashboardScale";
ساكن ثابت حرف * k_pch_Dashboard_UseStandaloneSystemLayer = "standaloneSystemLayer";
ساكن ثابت حرف * k_pch_Dashboard_StickyDashboard = "stickyDashboard";
ساكن ثابت حرف * k_pch_modelskin_Section = "modelskins";
ساكن ثابت حرف * k_pch_Driver_Enable_Bool = "enable";
ساكن ثابت حرف * k_pch_Driver_BlockedBySafemode_Bool = "blocked_by_safe_mode";
ساكن ثابت حرف * k_pch_Driver_بارول_لومړیتوب_Int32 = "loadPriority";
ساكن ثابت حرف * k_pch_WebInterface_Section = "WebInterface";
ساكن ثابت حرف * k_pch_VRWebHelper_Section = "VRWebHelper";
ساكن ثابت حرف * k_pch_VRWebHelper_DebuggerEnabled_Bool = "DebuggerEnabled";
ساكن ثابت حرف * k_pch_VRWeb_Helper_Debugger_پورټ_Int32 = "DebuggerPort";
ساكن ثابت حرف * k_pch_TrackingOverride_Section = "TrackingOverrides";
ساكن ثابت حرف * k_pch_App_BindingAutosaveURLSuffix_String = "AutosaveURL";
ساكن ثابت حرف * k_pch_App_BindingLegacyAPISuffix_String = "_legacy";
ساكن ثابت حرف * k_pch_App_BindingSteamVRInputAPISuffix_String = "_steamvrinput";
ساكن ثابت حرف * k_pch_App_BindingOpenXRAPISuffix_String = "_openxr";
ساكن ثابت حرف * k_pch_App_BindingCurrentURLSuffix_String = "CurrentURL";
ساكن ثابت حرف * k_pch_App_Binding_پخوانی_URLSuffix_String = "PreviousURL";
ساكن ثابت حرف * k_pch_App_Need_منزل_Update_Autosave_Suffix_Bool = "NeedToUpdateAutosave";
ساكن ثابت حرف * k_pch_App_DominantHand_Int32 = "DominantHand";
ساكن ثابت حرف * k_pch_App_بلاک_Oculus_SDK_Bool = "blockOculusSDK";
ساكن ثابت حرف * k_pch_Trackers_Section = "trackers";
ساكن ثابت حرف * k_pch_DesktopUI_Section = "DesktopUI";
ساكن ثابت حرف * k_pch_وروستی_معلوم_Section = "LastKnown";
ساكن ثابت حرف * k_pch_وروستی_معلوم_HMDManufacturer_String = "HMDManufacturer";
ساكن ثابت حرف * k_pch_وروستی_معلوم_HMDModel_String = "HMDModel";
ساكن ثابت حرف * k_pch_DismissedWarnings_Section = "DismissedWarnings";
ساكن ثابت حرف * k_pch_ننوت_Section = "input";
ساكن ثابت حرف * k_pch_ننوت_کیڼ_Thumbstick_Rotation_Float = "leftThumbstickRotation";
ساكن ثابت حرف * k_pch_ننوت_ښی_Thumbstick_Rotation_Float = "rightThumbstickRotation";
ساكن ثابت حرف * k_pch_ننوت_Thumbstick_Deadzone_Float = "thumbstickDeadzone";
ساكن ثابت حرف * k_pch_Gpu_چټکتیا_Section = "GpuSpeed";
ساكن ثابت حرف * IVRScreenshots_نسخه = "IVRScreenshots_001";
ساكن ثابت حرف * IVRResources_نسخه = "IVRResources_001";
ساكن ثابت حرف * IVRDriver_Manager_نسخه = "IVRDriverManager_001";
ساكن ثابت بینښه اوږد k_un_Max_Action_Name_اوږدتیا = 64;
ساكن ثابت بینښه اوږد k_un_Max_Action_سېټ_Name_اوږدتیا = 64;
ساكن ثابت بینښه اوږد k_un_Max_Action_Origin_شمېر = 16;
ساكن ثابت بینښه اوږد k_un_Max_Bone_Name_اوږدتیا = 32;
ساكن ثابت صحيح k_n_Action_سېټ_Overlay_Global_لومړیتوب_Min = 16777216;
ساكن ثابت صحيح k_n_Action_سېټ_Overlay_Global_لومړیتوب_Max = 33554431;
ساكن ثابت صحيح k_n_Action_سېټ_لومړیتوب_Reserved_Min = 33554432;
ساكن ثابت حرف * IVRInput_نسخه = "IVRInput_010";
ساكن ثابت بینښه اوږد اوږد k_ulInvalidIOBufferHandle = 0;
ساكن ثابت حرف * IVRIOBuffer_نسخه = "IVRIOBuffer_002";
ساكن ثابت بینښه اوږد k_ulInvalidSpatialAnchorHandle = 0;
ساكن ثابت حرف * IVRSpatial_Anchors_نسخه = "IVRSpatialAnchors_001";
ساكن ثابت حرف * IVRDebug_نسخه = "IVRDebug_001";
ساكن ثابت بینښه اوږد اوږد k_ulDisplayRedirectContainer = 25769803779;
ساكن ثابت حرف * IVRProperties_نسخه = "IVRProperties_001";
ساكن ثابت حرف * k_pch_لار_User_Hand_ښی = "/user/hand/right";
ساكن ثابت حرف * k_pch_لار_User_Hand_کیڼ = "/user/hand/left";
ساكن ثابت حرف * k_pch_لار_User_Hand_Primary = "/user/hand/primary";
ساكن ثابت حرف * k_pch_لار_User_Hand_Secondary = "/user/hand/secondary";
ساكن ثابت حرف * k_pch_لار_User_سر = "/user/head";
ساكن ثابت حرف * k_pch_لار_User_Gamepad = "/user/gamepad";
ساكن ثابت حرف * k_pch_لار_User_Treadmill = "/user/treadmill";
ساكن ثابت حرف * k_pch_لار_User_Stylus = "/user/stylus";
ساكن ثابت حرف * k_pch_لار_Devices = "/devices";
ساكن ثابت حرف * k_pch_لار_Device_لار = "/device_path";
ساكن ثابت حرف * k_pch_لار_غوره_Alias_لار = "/best_alias_path";
ساكن ثابت حرف * k_pch_لار_Bound_Tracker_Alias_لار = "/bound_tracker_path";
ساكن ثابت حرف * k_pch_لار_Bound_Tracker_Role = "/bound_tracker_role";
ساكن ثابت حرف * k_pch_لار_Pose_Raw = "/pose/raw";
ساكن ثابت حرف * k_pch_لار_Pose_Tip = "/pose/tip";
ساكن ثابت حرف * k_pch_لار_Pose_Grip = "/pose/grip";
ساكن ثابت حرف * k_pch_لار_System_Button_Click = "/input/system/click";
ساكن ثابت حرف * k_pch_لار_Proximity = "/proximity";
ساكن ثابت حرف * k_pch_لار_Controller_Type_مختاړی = "/controller_type/";
ساكن ثابت حرف * k_pch_لار_ننوت_Profile_Suffix = "/input_profile";
ساكن ثابت حرف * k_pch_لار_Binding_Name_Suffix = "/binding_name";
ساكن ثابت حرف * k_pch_لار_Binding_Url_Suffix = "/binding_url";
ساكن ثابت حرف * k_pch_لار_Binding_Error_Suffix = "/binding_error";
ساكن ثابت حرف * k_pch_لار_فعال_Action_Sets = "/active_action_sets";
ساكن ثابت حرف * k_pch_لار_Component_Updates = "/total_component_updates";
ساكن ثابت حرف * k_pch_لار_User_Foot_کیڼ = "/user/foot/left";
ساكن ثابت حرف * k_pch_لار_User_Foot_ښی = "/user/foot/right";
ساكن ثابت حرف * k_pch_لار_User_Shoulder_کیڼ = "/user/shoulder/left";
ساكن ثابت حرف * k_pch_لار_User_Shoulder_ښی = "/user/shoulder/right";
ساكن ثابت حرف * k_pch_لار_User_Elbow_کیڼ = "/user/elbow/left";
ساكن ثابت حرف * k_pch_لار_User_Elbow_ښی = "/user/elbow/right";
ساكن ثابت حرف * k_pch_لار_User_Knee_کیڼ = "/user/knee/left";
ساكن ثابت حرف * k_pch_لار_User_Knee_ښی = "/user/knee/right";
ساكن ثابت حرف * k_pch_لار_User_Waist = "/user/waist";
ساكن ثابت حرف * k_pch_لار_User_Chest = "/user/chest";
ساكن ثابت حرف * k_pch_لار_User_Camera = "/user/camera";
ساكن ثابت حرف * k_pch_لار_User_Keyboard = "/user/keyboard";
ساكن ثابت حرف * k_pch_لار_Client_App_کلی = "/client_info/app_key";
ساكن ثابت بینښه اوږد اوږد k_ul_Invalid_لار_Handle = 0;
ساكن ثابت حرف * IVRPaths_نسخه = "IVRPaths_001";
ساكن ثابت حرف * IVRBlock_کتار_نسخه = "IVRBlockQueue_005";

// OpenVR Enums

تعريفنوع تعداد EVREye
{
	EVREye_Eye_کیڼ = 0,
	EVREye_Eye_ښی = 1,
} EVREye;

تعريفنوع تعداد ETextureType
{
	ETextureType_TextureType_Invalid = -1,
	ETexture_Type_Texture_Type_مستقیم_X = 0,
	ETextureType_TextureType_OpenGL = 1,
	ETextureType_TextureType_Vulkan = 2,
	ETextureType_TextureType_IOSurface = 3,
	ETexture_Type_Texture_Type_مستقیم_X12 = 4,
	ETextureType_TextureType_DXGISharedHandle = 5,
	ETextureType_TextureType_Metal = 6,
} ETextureType;

تعريفنوع تعداد EColorSpace
{
	EColorSpace_ColorSpace_Auto = 0,
	EColorSpace_ColorSpace_Gamma = 1,
	EColor_Space_Color_Space_خطي = 2,
} EColorSpace;

تعريفنوع تعداد ETracking_پایله
{
	ETracking_پایله_Tracking_پایله_Uninitialized = 1,
	ETracking_پایله_Tracking_پایله_Calibrating_دننه_پرمختګ = 100,
	ETracking_پایله_Tracking_پایله_Calibrating_بهر_د_Range = 101,
	ETracking_پایله_Tracking_پایله_Running_OK = 200,
	ETracking_پایله_Tracking_پایله_Running_بهر_د_Range = 201,
	ETracking_پایله_Tracking_پایله_Fallback_Rotation_Only = 300,
} ETracking_پایله;

تعريفنوع تعداد ETrackedDeviceClass
{
	ETrackedDeviceClass_TrackedDeviceClass_Invalid = 0,
	ETrackedDeviceClass_TrackedDeviceClass_HMD = 1,
	ETrackedDeviceClass_TrackedDeviceClass_Controller = 2,
	ETrackedDeviceClass_TrackedDeviceClass_GenericTracker = 3,
	ETrackedDeviceClass_TrackedDeviceClass_TrackingReference = 4,
	ETrackedDeviceClass_TrackedDeviceClass_DisplayRedirect = 5,
	ETrackedDeviceClass_TrackedDeviceClass_Max = 6,
} ETrackedDeviceClass;

تعريفنوع تعداد ETrackedControllerRole
{
	ETrackedControllerRole_TrackedControllerRole_Invalid = 0,
	ETracked_Controller_Role_Tracked_Controller_Role_کیڼ_Hand = 1,
	ETracked_Controller_Role_Tracked_Controller_Role_ښی_Hand = 2,
	ETracked_Controller_Role_Tracked_Controller_Role_Opt_بهر = 3,
	ETrackedControllerRole_TrackedControllerRole_Treadmill = 4,
	ETrackedControllerRole_TrackedControllerRole_Stylus = 5,
	ETrackedControllerRole_TrackedControllerRole_Max = 5,
} ETrackedControllerRole;

تعريفنوع تعداد ETrackingUniverseOrigin
{
	ETrackingUniverseOrigin_TrackingUniverseSeated = 0,
	ETrackingUniverseOrigin_TrackingUniverseStanding = 1,
	ETrackingUniverseOrigin_TrackingUniverseRawAndUncalibrated = 2,
} ETrackingUniverseOrigin;

تعريفنوع تعداد EAdditionalRadioFeatures
{
	EAdditionalRadioFeatures_AdditionalRadioFeatures_None = 0,
	EAdditionalRadioFeatures_AdditionalRadioFeatures_HTCLinkBox = 1,
	EAdditional_Radio_Features_Additional_Radio_Features_دننی_Dongle = 2,
	EAdditionalRadioFeatures_AdditionalRadioFeatures_ExternalDongle = 4,
} EAdditionalRadioFeatures;

تعريفنوع تعداد ETrackedDeviceProperty
{
	ETrackedDeviceProperty_Prop_Invalid = 0,
	ETrackedDeviceProperty_Prop_TrackingSystemName_String = 1000,
	ETracked_Device_Property_Prop_Model_شمېره_String = 1001,
	ETracked_Device_Property_Prop_Serial_شمېره_String = 1002,
	ETrackedDeviceProperty_Prop_RenderModelName_String = 1003,
	ETracked_Device_Property_Prop_Will_Drift_دننه_Yaw_Bool = 1004,
	ETrackedDeviceProperty_Prop_ManufacturerName_String = 1005,
	ETracked_Device_Property_Prop_Tracking_Firmware_نسخه_String = 1006,
	ETrackedDeviceProperty_Prop_HardwareRevision_String = 1007,
	ETrackedDeviceProperty_Prop_AllWirelessDongleDescriptions_String = 1008,
	ETrackedDeviceProperty_Prop_ConnectedWirelessDongle_String = 1009,
	ETrackedDeviceProperty_Prop_DeviceIsWireless_Bool = 1010,
	ETrackedDeviceProperty_Prop_DeviceIsCharging_Bool = 1011,
	ETrackedDeviceProperty_Prop_DeviceBatteryPercentage_Float = 1012,
	ETracked_Device_Property_Prop_حالت_Display_Transform_Matrix34 = 1013,
	ETracked_Device_Property_Prop_Firmware_Update_شته_Bool = 1014,
	ETrackedDeviceProperty_Prop_Firmware_ManualUpdate_Bool = 1015,
	ETrackedDeviceProperty_Prop_Firmware_ManualUpdateURL_String = 1016,
	ETrackedDeviceProperty_Prop_HardwareRevision_Uint64 = 1017,
	ETracked_Device_Property_Prop_Firmware_نسخه_Uint64 = 1018,
	ETrackedDeviceProperty_Prop_FPGAVersion_Uint64 = 1019,
	ETrackedDeviceProperty_Prop_VRCVersion_Uint64 = 1020,
	ETracked_Device_Property_Prop_Radio_نسخه_Uint64 = 1021,
	ETracked_Device_Property_Prop_Dongle_نسخه_Uint64 = 1022,
	ETracked_Device_Property_Prop_بلاک_Server_Shutdown_Bool = 1023,
	ETrackedDeviceProperty_Prop_CanUnifyCoordinateSystemWithHmd_Bool = 1024,
	ETracked_Device_Property_Prop_لري_Proximity_Sensor_Bool = 1025,
	ETracked_Device_Property_Prop_Device_Provides_Battery_حالت_Bool = 1026,
	ETrackedDeviceProperty_Prop_DeviceCanPowerOff_Bool = 1027,
	ETracked_Device_Property_Prop_Firmware_Programming_موخه_String = 1028,
	ETrackedDeviceProperty_Prop_DeviceClass_Int32 = 1029,
	ETrackedDeviceProperty_Prop_HasCamera_Bool = 1030,
	ETracked_Device_Property_Prop_Driver_نسخه_String = 1031,
	ETrackedDeviceProperty_Prop_Firmware_ForceUpdateRequired_Bool = 1032,
	ETrackedDeviceProperty_Prop_ViveSystemButtonFixRequired_Bool = 1033,
	ETracked_Device_Property_Prop_پلار_Driver_Uint64 = 1034,
	ETracked_Device_Property_Prop_Resource_ریښه_String = 1035,
	ETrackedDeviceProperty_Prop_RegisteredDeviceType_String = 1036,
	ETracked_Device_Property_Prop_ننوت_Profile_لار_String = 1037,
	ETrackedDeviceProperty_Prop_NeverTracked_Bool = 1038,
	ETracked_Device_Property_Prop_عدد_Cameras_Int32 = 1039,
	ETracked_Device_Property_Prop_Camera_چوکاټ_Layout_Int32 = 1040,
	ETracked_Device_Property_Prop_Camera_بهیر_Format_Int32 = 1041,
	ETracked_Device_Property_Prop_Additional_Device_Settings_لار_String = 1042,
	ETrackedDeviceProperty_Prop_Identifiable_Bool = 1043,
	ETracked_Device_Property_Prop_Bootloader_نسخه_Uint64 = 1044,
	ETracked_Device_Property_Prop_Additional_System_Report_معلومات_String = 1045,
	ETracked_Device_Property_Prop_مرکب_Firmware_نسخه_String = 1046,
	ETrackedDeviceProperty_Prop_Firmware_RemindUpdate_Bool = 1047,
	ETracked_Device_Property_Prop_Peripheral_Application_نسخه_Uint64 = 1048,
	ETracked_Device_Property_Prop_Manufacturer_Serial_شمېره_String = 1049,
	ETracked_Device_Property_Prop_Computed_Serial_شمېره_String = 1050,
	ETracked_Device_Property_Prop_Estimated_Device_لومړی_Use_وخت_Int32 = 1051,
	ETrackedDeviceProperty_Prop_DevicePowerUsage_Float = 1052,
	ETrackedDeviceProperty_Prop_IgnoreMotionForStandby_Bool = 1053,
	ETracked_Device_Property_Prop_Reports_وخت_Since_VSync_Bool = 2000,
	ETracked_Device_Property_Prop_Seconds_From_Vsync_منزل_Photons_Float = 2001,
	ETrackedDeviceProperty_Prop_DisplayFrequency_Float = 2002,
	ETrackedDeviceProperty_Prop_UserIpdMeters_Float = 2003,
	ETrackedDeviceProperty_Prop_CurrentUniverseId_Uint64 = 2004,
	ETracked_Device_Property_Prop_پخوانی_Universe_Id_Uint64 = 2005,
	ETracked_Device_Property_Prop_Display_Firmware_نسخه_Uint64 = 2006,
	ETrackedDeviceProperty_Prop_IsOnDesktop_Bool = 2007,
	ETrackedDeviceProperty_Prop_DisplayMCType_Int32 = 2008,
	ETrackedDeviceProperty_Prop_DisplayMCOffset_Float = 2009,
	ETrackedDeviceProperty_Prop_DisplayMCScale_Float = 2010,
	ETrackedDeviceProperty_Prop_EdidVendorID_Int32 = 2011,
	ETracked_Device_Property_Prop_Display_MCImage_کیڼ_String = 2012,
	ETracked_Device_Property_Prop_Display_MCImage_ښی_String = 2013,
	ETrackedDeviceProperty_Prop_DisplayGCBlackClamp_Float = 2014,
	ETracked_Device_Property_Prop_Edid_حاصل_ضرب_ID_Int32 = 2015,
	ETracked_Device_Property_Prop_Camera_منزل_سر_Transform_Matrix34 = 2016,
	ETrackedDeviceProperty_Prop_DisplayGCType_Int32 = 2017,
	ETrackedDeviceProperty_Prop_DisplayGCOffset_Float = 2018,
	ETrackedDeviceProperty_Prop_DisplayGCScale_Float = 2019,
	ETrackedDeviceProperty_Prop_DisplayGCPrescale_Float = 2020,
	ETrackedDeviceProperty_Prop_DisplayGCImage_String = 2021,
	ETracked_Device_Property_Prop_Lens_Center_کیڼ_U_Float = 2022,
	ETracked_Device_Property_Prop_Lens_Center_کیڼ_V_Float = 2023,
	ETracked_Device_Property_Prop_Lens_Center_ښی_U_Float = 2024,
	ETracked_Device_Property_Prop_Lens_Center_ښی_V_Float = 2025,
	ETracked_Device_Property_Prop_User_سر_منزل_Eye_ژوروالی_Meters_Float = 2026,
	ETracked_Device_Property_Prop_Camera_Firmware_نسخه_Uint64 = 2027,
	ETrackedDeviceProperty_Prop_CameraFirmwareDescription_String = 2028,
	ETrackedDeviceProperty_Prop_DisplayFPGAVersion_Uint64 = 2029,
	ETracked_Device_Property_Prop_Display_Bootloader_نسخه_Uint64 = 2030,
	ETracked_Device_Property_Prop_Display_Hardware_نسخه_Uint64 = 2031,
	ETracked_Device_Property_Prop_Audio_Firmware_نسخه_Uint64 = 2032,
	ETracked_Device_Property_Prop_Camera_Compatibility_ډېرپېښ_Int32 = 2033,
	ETracked_Device_Property_Prop_Screenshot_Horizontal_ډګر_د_View_Degrees_Float = 2034,
	ETracked_Device_Property_Prop_Screenshot_Vertical_ډګر_د_View_Degrees_Float = 2035,
	ETrackedDeviceProperty_Prop_DisplaySuppressed_Bool = 2036,
	ETracked_Device_Property_Prop_Display_Allow_Night_ډېرپېښ_Bool = 2037,
	ETracked_Device_Property_Prop_Display_MCImage_پلنوالی_Int32 = 2038,
	ETracked_Device_Property_Prop_Display_MCImage_لوړوالی_Int32 = 2039,
	ETracked_Device_Property_Prop_Display_MCImage_عدد_Channels_Int32 = 2040,
	ETracked_Device_Property_Prop_Display_MCImage_معلومات_دوګونی = 2041,
	ETracked_Device_Property_Prop_Seconds_From_Photons_منزل_Vblank_Float = 2042,
	ETracked_Device_Property_Prop_Driver_مستقیم_ډېرپېښ_Sends_Vsync_Events_Bool = 2043,
	ETracked_Device_Property_Prop_Display_Debug_ډېرپېښ_Bool = 2044,
	ETrackedDeviceProperty_Prop_GraphicsAdapterLuid_Uint64 = 2045,
	ETracked_Device_Property_Prop_Driver_Provided_Chaperone_لار_String = 2048,
	ETracked_Device_Property_Prop_Expected_Tracking_Reference_شمېر_Int32 = 2049,
	ETracked_Device_Property_Prop_Expected_Controller_شمېر_Int32 = 2050,
	ETracked_Device_Property_Prop_Named_Icon_لار_Controller_کیڼ_Device_Off_String = 2051,
	ETracked_Device_Property_Prop_Named_Icon_لار_Controller_ښی_Device_Off_String = 2052,
	ETracked_Device_Property_Prop_Named_Icon_لار_Tracking_Reference_Device_Off_String = 2053,
	ETrackedDeviceProperty_Prop_DoNotApplyPrediction_Bool = 2054,
	ETracked_Device_Property_Prop_Camera_منزل_سر_Transforms_Matrix34_Array = 2055,
	ETrackedDeviceProperty_Prop_DistortionMeshResolution_Int32 = 2056,
	ETrackedDeviceProperty_Prop_DriverIsDrawingControllers_Bool = 2057,
	ETracked_Device_Property_Prop_Driver_غوښتنې_Application_Pause_Bool = 2058,
	ETracked_Device_Property_Prop_Driver_غوښتنې_Reduced_Rendering_Bool = 2059,
	ETracked_Device_Property_Prop_Minimum_Ipd_ګام_Meters_Float = 2060,
	ETracked_Device_Property_Prop_Audio_Bridge_Firmware_نسخه_Uint64 = 2061,
	ETracked_Device_Property_Prop_Image_Bridge_Firmware_نسخه_Uint64 = 2062,
	ETracked_Device_Property_Prop_Imu_منزل_سر_Transform_Matrix34 = 2063,
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
	ETracked_Device_Property_Prop_Hmd_ستنه_Correction_Setting_مختاړی_String = 2077,
	ETrackedDeviceProperty_Prop_CameraSupportsCompatibilityModes_Bool = 2078,
	ETracked_Device_Property_Prop_Supports_ځای_View_ژوروالی_Projection_Bool = 2079,
	ETracked_Device_Property_Prop_Display_شته_چوکاټ_Rates_Float_Array = 2080,
	ETracked_Device_Property_Prop_Display_Supports_مضرب_Framerates_Bool = 2081,
	ETracked_Device_Property_Prop_Display_Color_Mult_کیڼ_Vector3 = 2082,
	ETracked_Device_Property_Prop_Display_Color_Mult_ښی_Vector3 = 2083,
	ETrackedDeviceProperty_Prop_DisplaySupportsRuntimeFramerateChange_Bool = 2084,
	ETrackedDeviceProperty_Prop_DisplaySupportsAnalogGain_Bool = 2085,
	ETrackedDeviceProperty_Prop_DisplayMinAnalogGain_Float = 2086,
	ETrackedDeviceProperty_Prop_DisplayMaxAnalogGain_Float = 2087,
	ETracked_Device_Property_Prop_Camera_Exposure_وخت_Float = 2088,
	ETrackedDeviceProperty_Prop_CameraGlobalGain_Float = 2089,
	ETrackedDeviceProperty_Prop_DashboardScale_Float = 2091,
	ETrackedDeviceProperty_Prop_PeerButtonInfo_String = 2092,
	ETrackedDeviceProperty_Prop_Hmd_SupportsHDR10_Bool = 2093,
	ETrackedDeviceProperty_Prop_IpdUIRangeMinMeters_Float = 2100,
	ETrackedDeviceProperty_Prop_IpdUIRangeMaxMeters_Float = 2101,
	ETrackedDeviceProperty_Prop_Hmd_SupportsHDCP14LegacyCompat_Bool = 2102,
	ETrackedDeviceProperty_Prop_Hmd_SupportsMicMonitoring_Bool = 2103,
	ETracked_Device_Property_Prop_Hmd_Supports_Display_پورټ_Training_ډېرپېښ_Bool = 2104,
	ETracked_Device_Property_Prop_Supports_ځای_View_مستقیم_Bool = 2105,
	ETrackedDeviceProperty_Prop_SupportsAppThrottling_Bool = 2106,
	ETrackedDeviceProperty_Prop_DSCVersion_Int32 = 2110,
	ETracked_Device_Property_Prop_DSCSlice_شمېر_Int32 = 2111,
	ETrackedDeviceProperty_Prop_DSCBPPx16_Int32 = 2112,
	ETracked_Device_Property_Prop_Driver_Requested_Mura_Correction_ډېرپېښ_Int32 = 2200,
	ETracked_Device_Property_Prop_Driver_Requested_Mura_Feather_Inner_کیڼ_Int32 = 2201,
	ETracked_Device_Property_Prop_Driver_Requested_Mura_Feather_Inner_ښی_Int32 = 2202,
	ETracked_Device_Property_Prop_Driver_Requested_Mura_Feather_Inner_سر_Int32 = 2203,
	ETrackedDeviceProperty_Prop_DriverRequestedMuraFeather_InnerBottom_Int32 = 2204,
	ETracked_Device_Property_Prop_Driver_Requested_Mura_Feather_Outer_کیڼ_Int32 = 2205,
	ETracked_Device_Property_Prop_Driver_Requested_Mura_Feather_Outer_ښی_Int32 = 2206,
	ETracked_Device_Property_Prop_Driver_Requested_Mura_Feather_Outer_سر_Int32 = 2207,
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
	ETracked_Device_Property_Prop_ډګر_د_View_کیڼ_Degrees_Float = 4000,
	ETracked_Device_Property_Prop_ډګر_د_View_ښی_Degrees_Float = 4001,
	ETracked_Device_Property_Prop_ډګر_د_View_سر_Degrees_Float = 4002,
	ETracked_Device_Property_Prop_ډګر_د_View_Bottom_Degrees_Float = 4003,
	ETrackedDeviceProperty_Prop_TrackingRangeMinimumMeters_Float = 4004,
	ETracked_Device_Property_Prop_Tracking_Range_اعظمي_Meters_Float = 4005,
	ETracked_Device_Property_Prop_ډېرپېښ_Label_String = 4006,
	ETrackedDeviceProperty_Prop_CanWirelessIdentify_Bool = 4007,
	ETrackedDeviceProperty_Prop_Nonce_Int32 = 4008,
	ETracked_Device_Property_Prop_Icon_لار_Name_String = 5000,
	ETracked_Device_Property_Prop_Named_Icon_لار_Device_Off_String = 5001,
	ETracked_Device_Property_Prop_Named_Icon_لار_Device_Searching_String = 5002,
	ETracked_Device_Property_Prop_Named_Icon_لار_Device_Searching_Alert_String = 5003,
	ETracked_Device_Property_Prop_Named_Icon_لار_Device_Ready_String = 5004,
	ETracked_Device_Property_Prop_Named_Icon_لار_Device_Ready_Alert_String = 5005,
	ETracked_Device_Property_Prop_Named_Icon_لار_Device_Not_Ready_String = 5006,
	ETracked_Device_Property_Prop_Named_Icon_لار_Device_Standby_String = 5007,
	ETracked_Device_Property_Prop_Named_Icon_لار_Device_Alert_ټیټ_String = 5008,
	ETracked_Device_Property_Prop_Named_Icon_لار_Device_Standby_Alert_String = 5009,
	ETracked_Device_Property_Prop_Display_Hidden_Area_دوګونی_پیل = 5100,
	ETracked_Device_Property_Prop_Display_Hidden_Area_دوګونی_پای_ټکی = 5150,
	ETracked_Device_Property_Prop_پلار_Container = 5151,
	ETrackedDeviceProperty_Prop_OverrideContainer_Uint64 = 5152,
	ETracked_Device_Property_Prop_User_Config_لار_String = 6000,
	ETracked_Device_Property_Prop_Install_لار_String = 6001,
	ETrackedDeviceProperty_Prop_HasDisplayComponent_Bool = 6002,
	ETrackedDeviceProperty_Prop_HasControllerComponent_Bool = 6003,
	ETrackedDeviceProperty_Prop_HasCameraComponent_Bool = 6004,
	ETracked_Device_Property_Prop_Has_Driver_مستقیم_ډېرپېښ_Component_Bool = 6005,
	ETrackedDeviceProperty_Prop_HasVirtualDisplayComponent_Bool = 6006,
	ETrackedDeviceProperty_Prop_HasSpatialAnchorsSupport_Bool = 6007,
	ETrackedDeviceProperty_Prop_ControllerType_String = 7000,
	ETracked_Device_Property_Prop_Controller_Hand_Selection_لومړیتوب_Int32 = 7002,
	ETracked_Device_Property_Prop_Vendor_Specific_Reserved_پیل = 10000,
	ETracked_Device_Property_Prop_Vendor_Specific_Reserved_پای_ټکی = 10999,
	ETrackedDeviceProperty_Prop_TrackedDeviceProperty_Max = 1000000,
} ETrackedDeviceProperty;

تعريفنوع تعداد ETrackedPropertyError
{
	ETrackedPropertyError_TrackedProp_Success = 0,
	ETracked_Property_Error_Tracked_Prop_Wrong_معلومات_Type = 1,
	ETrackedPropertyError_TrackedProp_WrongDeviceClass = 2,
	ETracked_Property_Error_Tracked_Prop_بفر_Too_Small = 3,
	ETrackedPropertyError_TrackedProp_UnknownProperty = 4,
	ETrackedPropertyError_TrackedProp_InvalidDevice = 5,
	ETrackedPropertyError_TrackedProp_CouldNotContactServer = 6,
	ETracked_Property_Error_Tracked_Prop_ارزښت_Not_Provided_By_Device = 7,
	ETracked_Property_Error_Tracked_Prop_String_Exceeds_اعظمي_اوږدتیا = 8,
	ETracked_Property_Error_Tracked_Prop_Not_Yet_شته = 9,
	ETrackedPropertyError_TrackedProp_PermissionDenied = 10,
	ETrackedPropertyError_TrackedProp_InvalidOperation = 11,
	ETracked_Property_Error_Tracked_Prop_Cannot_Write_منزل_Wildcards = 12,
	ETrackedPropertyError_TrackedProp_IPCReadFailure = 13,
	ETracked_Property_Error_Tracked_Prop_بهر_د_حافظه = 14,
	ETrackedPropertyError_TrackedProp_InvalidContainer = 15,
} ETrackedPropertyError;

تعريفنوع تعداد EHmdTrackingStyle
{
	EHmdTrackingStyle_HmdTrackingStyle_Unknown = 0,
	EHmdTrackingStyle_HmdTrackingStyle_Lighthouse = 1,
	EHmd_Tracking_Style_Hmd_Tracking_Style_Outside_دننه_Cameras = 2,
	EHmd_Tracking_Style_Hmd_Tracking_Style_Inside_بهر_Cameras = 3,
} EHmdTrackingStyle;

تعريفنوع تعداد EVRSubmitFlags
{
	EVRSubmitFlags_Submit_Default = 0,
	EVRSubmitFlags_Submit_LensDistortionAlreadyApplied = 1,
	EVRSubmit_Flags_Submit_Gl_Render_بفر = 2,
	EVRSubmitFlags_Submit_Reserved = 4,
	EVRSubmitFlags_Submit_TextureWithPose = 8,
	EVRSubmit_Flags_Submit_Texture_With_ژوروالی = 16,
	EVRSubmit_Flags_Submit_چوکاټ_Discontinuty = 32,
	EVRSubmit_Flags_Submit_Vulkan_Texture_With_Array_معلومات = 64,
	EVRSubmitFlags_Submit_GlArrayTexture = 128,
	EVRSubmitFlags_Submit_Reserved2 = 32768,
	EVRSubmitFlags_Submit_Reserved3 = 65536,
} EVRSubmitFlags;

تعريفنوع تعداد EVRState
{
	EVRState_VRState_Undefined = -1,
	EVRState_VRState_Off = 0,
	EVRState_VRState_Searching = 1,
	EVRState_VRState_Searching_Alert = 2,
	EVRState_VRState_Ready = 3,
	EVRState_VRState_Ready_Alert = 4,
	EVRState_VRState_NotReady = 5,
	EVRState_VRState_Standby = 6,
	EVRState_VRState_Ready_Alert_ټیټ = 7,
} EVRState;

تعريفنوع تعداد EVREventType
{
	EVREventType_VREvent_None = 0,
	EVREventType_VREvent_TrackedDeviceActivated = 100,
	EVREventType_VREvent_TrackedDeviceDeactivated = 101,
	EVREventType_VREvent_TrackedDeviceUpdated = 102,
	EVREventType_VREvent_TrackedDeviceUserInteractionStarted = 103,
	EVREventType_VREvent_TrackedDeviceUserInteractionEnded = 104,
	EVREvent_Type_VREvent_Ipd_بدل_شوی = 105,
	EVREvent_Type_VREvent_Enter_Standby_ډېرپېښ = 106,
	EVREvent_Type_VREvent_Leave_Standby_ډېرپېښ = 107,
	EVREvent_Type_VREvent_Tracked_Device_Role_بدل_شوی = 108,
	EVREvent_Type_VREvent_Watchdog_Wake_پورته_Requested = 109,
	EVREvent_Type_VREvent_Lens_Distortion_بدل_شوی = 110,
	EVREvent_Type_VREvent_Property_بدل_شوی = 111,
	EVREventType_VREvent_WirelessDisconnect = 112,
	EVREventType_VREvent_WirelessReconnect = 113,
	EVREventType_VREvent_ButtonPress = 200,
	EVREventType_VREvent_ButtonUnpress = 201,
	EVREventType_VREvent_ButtonTouch = 202,
	EVREventType_VREvent_ButtonUntouch = 203,
	EVREventType_VREvent_Modal_Cancel = 257,
	EVREventType_VREvent_MouseMove = 300,
	EVREvent_Type_VREvent_Mouse_Button_ښکته = 301,
	EVREvent_Type_VREvent_Mouse_Button_پورته = 302,
	EVREventType_VREvent_FocusEnter = 303,
	EVREventType_VREvent_FocusLeave = 304,
	EVREventType_VREvent_ScrollDiscrete = 305,
	EVREventType_VREvent_TouchPadMove = 306,
	EVREvent_Type_VREvent_Overlay_Focus_بدل_شوی = 307,
	EVREventType_VREvent_ReloadOverlays = 308,
	EVREventType_VREvent_ScrollSmooth = 309,
	EVREvent_Type_VREvent_قلف_Mouse_Position = 310,
	EVREventType_VREvent_UnlockMousePosition = 311,
	EVREvent_Type_VREvent_ننوت_Focus_Captured = 400,
	EVREvent_Type_VREvent_ننوت_Focus_Released = 401,
	EVREvent_Type_VREvent_Scene_Application_بدل_شوی = 404,
	EVREvent_Type_VREvent_ننوت_Focus_بدل_شوی = 406,
	EVREventType_VREvent_SceneApplicationUsingWrongGraphicsAdapter = 408,
	EVREventType_VREvent_ActionBindingReloaded = 409,
	EVREventType_VREvent_HideRenderModels = 410,
	EVREventType_VREvent_ShowRenderModels = 411,
	EVREvent_Type_VREvent_Scene_Application_State_بدل_شوی = 412,
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
	EVREvent_Type_VREvent_Overlay_Gamepad_Focus_ورک = 512,
	EVREvent_Type_VREvent_Overlay_Shared_Texture_بدل_شوی = 513,
	EVREventType_VREvent_ScreenshotTriggered = 516,
	EVREventType_VREvent_ImageFailed = 517,
	EVREventType_VREvent_DashboardOverlayCreated = 518,
	EVREventType_VREvent_SwitchGamepadFocus = 519,
	EVREventType_VREvent_RequestScreenshot = 520,
	EVREvent_Type_VREvent_Screenshot_اخیستل_شوی = 521,
	EVREventType_VREvent_ScreenshotFailed = 522,
	EVREvent_Type_VREvent_Submit_Screenshot_منزل_Dashboard = 523,
	EVREvent_Type_VREvent_Screenshot_پرمختګ_منزل_Dashboard = 524,
	EVREvent_Type_VREvent_Primary_Dashboard_Device_بدل_شوی = 525,
	EVREvent_Type_VREvent_ځای_View_Shown = 526,
	EVREvent_Type_VREvent_ځای_View_Hidden = 527,
	EVREventType_VREvent_ShowUI = 528,
	EVREventType_VREvent_ShowDevTools = 529,
	EVREventType_VREvent_DesktopViewUpdating = 530,
	EVREventType_VREvent_DesktopViewReady = 531,
	EVREvent_Type_VREvent_پیل_Dashboard = 532,
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
	EVREvent_Type_VREvent_Invalidate_بدلون_Texture_Sets = 706,
	EVREvent_Type_VREvent_Chaperone_معلومات_Has_بدل_شوی = 800,
	EVREvent_Type_VREvent_Chaperone_Universe_Has_بدل_شوی = 801,
	EVREvent_Type_VREvent_Chaperone_لنډمهاله_معلومات_Has_بدل_شوی = 802,
	EVREvent_Type_VREvent_Chaperone_Settings_Have_بدل_شوی = 803,
	EVREventType_VREvent_SeatedZeroPoseReset = 804,
	EVREventType_VREvent_ChaperoneFlushCache = 805,
	EVREvent_Type_VREvent_Chaperone_ځای_تیاری_Starting = 806,
	EVREvent_Type_VREvent_Chaperone_ځای_تیاری_پای_ته_رسېدلی = 807,
	EVREventType_VREvent_StandingZeroPoseReset = 808,
	EVREvent_Type_VREvent_Audio_Settings_Have_بدل_شوی = 820,
	EVREvent_Type_VREvent_Background_Setting_Has_بدل_شوی = 850,
	EVREvent_Type_VREvent_Camera_Settings_Have_بدل_شوی = 851,
	EVREvent_Type_VREvent_Reprojection_Setting_Has_بدل_شوی = 852,
	EVREvent_Type_VREvent_Model_Skin_Settings_Have_بدل_شوی = 853,
	EVREvent_Type_VREvent_Environment_Settings_Have_بدل_شوی = 854,
	EVREvent_Type_VREvent_Power_Settings_Have_بدل_شوی = 855,
	EVREvent_Type_VREvent_Enable_Home_App_Settings_Have_بدل_شوی = 856,
	EVREvent_Type_VREvent_Steam_VRSection_Setting_بدل_شوی = 857,
	EVREvent_Type_VREvent_Lighthouse_Section_Setting_بدل_شوی = 858,
	EVREvent_Type_VREvent_Null_Section_Setting_بدل_شوی = 859,
	EVREvent_Type_VREvent_User_Interface_Section_Setting_بدل_شوی = 860,
	EVREvent_Type_VREvent_Notifications_Section_Setting_بدل_شوی = 861,
	EVREvent_Type_VREvent_Keyboard_Section_Setting_بدل_شوی = 862,
	EVREvent_Type_VREvent_Perf_Section_Setting_بدل_شوی = 863,
	EVREvent_Type_VREvent_Dashboard_Section_Setting_بدل_شوی = 864,
	EVREvent_Type_VREvent_Web_Interface_Section_Setting_بدل_شوی = 865,
	EVREvent_Type_VREvent_Trackers_Section_Setting_بدل_شوی = 866,
	EVREvent_Type_VREvent_وروستی_معلوم_Section_Setting_بدل_شوی = 867,
	EVREvent_Type_VREvent_Dismissed_Warnings_Section_Setting_بدل_شوی = 868,
	EVREvent_Type_VREvent_Gpu_چټکتیا_Section_Setting_بدل_شوی = 869,
	EVREvent_Type_VREvent_Windows_MRSection_Setting_بدل_شوی = 870,
	EVREvent_Type_VREvent_Other_Section_Setting_بدل_شوی = 871,
	EVREvent_Type_VREvent_حالت_Update = 900,
	EVREventType_VREvent_WebInterface_InstallDriverCompleted = 950,
	EVREventType_VREvent_MCImageUpdated = 1000,
	EVREventType_VREvent_FirmwareUpdateStarted = 1100,
	EVREvent_Type_VREvent_Firmware_Update_پای_ته_رسېدلی = 1101,
	EVREventType_VREvent_KeyboardClosed = 1200,
	EVREvent_Type_VREvent_Keyboard_Char_ننوت = 1201,
	EVREvent_Type_VREvent_Keyboard_بشپړ = 1202,
	EVREventType_VREvent_ApplicationListUpdated = 1303,
	EVREvent_Type_VREvent_Application_Mime_Type_بارول = 1304,
	EVREventType_VREvent_ProcessConnected = 1306,
	EVREventType_VREvent_ProcessDisconnected = 1307,
	EVREventType_VREvent_Compositor_ChaperoneBoundsShown = 1410,
	EVREventType_VREvent_Compositor_ChaperoneBoundsHidden = 1411,
	EVREventType_VREvent_Compositor_DisplayDisconnected = 1412,
	EVREventType_VREvent_Compositor_DisplayReconnected = 1413,
	EVREventType_VREvent_Compositor_HDCPError = 1414,
	EVREventType_VREvent_Compositor_ApplicationNotResponding = 1415,
	EVREventType_VREvent_Compositor_ApplicationResumed = 1416,
	EVREvent_Type_VREvent_Compositor_بهر_د_Video_حافظه = 1417,
	EVREvent_Type_VREvent_Compositor_Display_ډېرپېښ_Not_Supported = 1418,
	EVREventType_VREvent_Compositor_StageOverrideReady = 1419,
	EVREventType_VREvent_Compositor_RequestDisconnectReconnect = 1420,
	EVREvent_Type_VREvent_Tracked_Camera_پیل_Video_بهیر = 1500,
	EVREvent_Type_VREvent_Tracked_Camera_Stop_Video_بهیر = 1501,
	EVREvent_Type_VREvent_Tracked_Camera_Pause_Video_بهیر = 1502,
	EVREvent_Type_VREvent_Tracked_Camera_Resume_Video_بهیر = 1503,
	EVREventType_VREvent_TrackedCamera_EditingSurface = 1550,
	EVREventType_VREvent_PerformanceTest_EnableCapture = 1600,
	EVREventType_VREvent_PerformanceTest_DisableCapture = 1601,
	EVREventType_VREvent_PerformanceTest_FidelityLevel = 1602,
	EVREvent_Type_VREvent_پیغام_Overlay_Closed = 1650,
	EVREvent_Type_VREvent_پیغام_Overlay_Close_Requested = 1651,
	EVREvent_Type_VREvent_ننوت_Haptic_Vibration = 1700,
	EVREvent_Type_VREvent_ننوت_Binding_بارول_Failed = 1701,
	EVREvent_Type_VREvent_ننوت_Binding_بارول_Successful = 1702,
	EVREvent_Type_VREvent_ننوت_Action_Manifest_Reloaded = 1703,
	EVREvent_Type_VREvent_ننوت_Action_Manifest_بارول_Failed = 1704,
	EVREvent_Type_VREvent_ننوت_پرمختګ_Update = 1705,
	EVREvent_Type_VREvent_ننوت_Tracker_Activated = 1706,
	EVREvent_Type_VREvent_ننوت_Bindings_Updated = 1707,
	EVREvent_Type_VREvent_ننوت_Binding_Subscription_بدل_شوی = 1708,
	EVREventType_VREvent_SpatialAnchors_PoseUpdated = 1800,
	EVREventType_VREvent_SpatialAnchors_DescriptorUpdated = 1801,
	EVREventType_VREvent_SpatialAnchors_RequestPoseUpdate = 1802,
	EVREventType_VREvent_SpatialAnchors_RequestDescriptorUpdate = 1803,
	EVREventType_VREvent_SystemReport_Started = 1900,
	EVREventType_VREvent_Monitor_ShowHeadsetView = 2000,
	EVREventType_VREvent_Monitor_HideHeadsetView = 2001,
	EVREvent_Type_VREvent_Vendor_Specific_Reserved_پیل = 10000,
	EVREvent_Type_VREvent_Vendor_Specific_Reserved_پای_ټکی = 19999,
} EVREventType;

تعريفنوع تعداد EDeviceActivityLevel
{
	EDeviceActivityLevel_k_EDeviceActivityLevel_Unknown = -1,
	EDeviceActivityLevel_k_EDeviceActivityLevel_Idle = 0,
	EDeviceActivityLevel_k_EDeviceActivityLevel_UserInteraction = 1,
	EDeviceActivityLevel_k_EDeviceActivityLevel_UserInteraction_Timeout = 2,
	EDeviceActivityLevel_k_EDeviceActivityLevel_Standby = 3,
	EDeviceActivityLevel_k_EDeviceActivityLevel_Idle_Timeout = 4,
} EDeviceActivityLevel;

تعريفنوع تعداد EVRButtonId
{
	EVRButtonId_k_EButton_System = 0,
	EVRButtonId_k_EButton_ApplicationMenu = 1,
	EVRButtonId_k_EButton_Grip = 2,
	EVRButton_Id_k_EButton_DPad_کیڼ = 3,
	EVRButton_Id_k_EButton_DPad_پورته = 4,
	EVRButton_Id_k_EButton_DPad_ښی = 5,
	EVRButton_Id_k_EButton_DPad_ښکته = 6,
	EVRButtonId_k_EButton_A = 7,
	EVRButtonId_k_EButton_ProximitySensor = 31,
	EVRButtonId_k_EButton_Axis0 = 32,
	EVRButtonId_k_EButton_Axis1 = 33,
	EVRButtonId_k_EButton_Axis2 = 34,
	EVRButtonId_k_EButton_Axis3 = 35,
	EVRButtonId_k_EButton_Axis4 = 36,
	EVRButtonId_k_EButton_SteamVR_Touchpad = 32,
	EVRButtonId_k_EButton_SteamVR_Trigger = 33,
	EVRButton_Id_k_EButton_Dashboard_شا = 2,
	EVRButton_Id_k_EButton_شاخص_Controller_A = 2,
	EVRButton_Id_k_EButton_شاخص_Controller_B = 1,
	EVRButton_Id_k_EButton_شاخص_Controller_Joy_Stick = 35,
	EVRButtonId_k_EButton_Max = 64,
} EVRButtonId;

تعريفنوع تعداد EVRMouseButton
{
	EVRMouse_Button_VRMouse_Button_کیڼ = 1,
	EVRMouse_Button_VRMouse_Button_ښی = 2,
	EVRMouse_Button_VRMouse_Button_منځ = 4,
} EVRMouseButton;

تعريفنوع تعداد EShowUIType
{
	EShowUIType_ShowUI_ControllerBinding = 0,
	EShowUIType_ShowUI_ManageTrackers = 1,
	EShowUIType_ShowUI_Pairing = 3,
	EShowUIType_ShowUI_Settings = 4,
	EShowUIType_ShowUI_DebugCommands = 5,
	EShow_UIType_Show_UI_ډک_Controller_Binding = 6,
	EShowUIType_ShowUI_ManageDrivers = 7,
} EShowUIType;

تعريفنوع تعداد EHDCPError
{
	EHDCPError_HDCPError_None = 0,
	EHDCPError_HDCPError_Link_ورک = 1,
	EHDCPError_HDCPError_Tampered = 2,
	EHDCPError_HDCPError_DeviceRevoked = 3,
	EHDCPError_HDCPError_Unknown = 4,
} EHDCPError;

تعريفنوع تعداد EVRComponentProperty
{
	EVRComponentProperty_VRComponentProperty_IsStatic = 1,
	EVRComponentProperty_VRComponentProperty_IsVisible = 2,
	EVRComponentProperty_VRComponentProperty_IsTouched = 4,
	EVRComponentProperty_VRComponentProperty_IsPressed = 8,
	EVRComponentProperty_VRComponentProperty_IsScrolled = 16,
	EVRComponentProperty_VRComponentProperty_IsHighlighted = 32,
} EVRComponentProperty;

تعريفنوع تعداد EVRInputError
{
	EVRInputError_VRInputError_None = 0,
	EVRInput_Error_VRInput_Error_Name_Not_وموندل = 1,
	EVRInputError_VRInputError_WrongType = 2,
	EVRInputError_VRInputError_InvalidHandle = 3,
	EVRInputError_VRInputError_InvalidParam = 4,
	EVRInputError_VRInputError_NoSteam = 5,
	EVRInput_Error_VRInput_Error_Max_ظرفیت_Reached = 6,
	EVRInputError_VRInputError_IPCError = 7,
	EVRInput_Error_VRInput_Error_No_فعال_Action_سېټ = 8,
	EVRInputError_VRInputError_InvalidDevice = 9,
	EVRInputError_VRInputError_InvalidSkeleton = 10,
	EVRInput_Error_VRInput_Error_Invalid_Bone_شمېر = 11,
	EVRInput_Error_VRInput_Error_Invalid_Compressed_معلومات = 12,
	EVRInput_Error_VRInput_Error_No_معلومات = 13,
	EVRInput_Error_VRInput_Error_بفر_Too_Small = 14,
	EVRInputError_VRInputError_MismatchedActionManifest = 15,
	EVRInput_Error_VRInput_Error_Missing_Skeleton_معلومات = 16,
	EVRInput_Error_VRInput_Error_Invalid_Bone_شاخص = 17,
	EVRInput_Error_VRInput_Error_Invalid_لومړیتوب = 18,
	EVRInputError_VRInputError_PermissionDenied = 19,
	EVRInputError_VRInputError_InvalidRenderModel = 20,
} EVRInputError;

تعريفنوع تعداد EVRSpatialAnchorError
{
	EVRSpatialAnchorError_VRSpatialAnchorError_Success = 0,
	EVRSpatial_Anchor_Error_VRSpatial_Anchor_Error_دننی = 1,
	EVRSpatialAnchorError_VRSpatialAnchorError_UnknownHandle = 2,
	EVRSpatialAnchorError_VRSpatialAnchorError_ArrayTooSmall = 3,
	EVRSpatialAnchorError_VRSpatialAnchorError_InvalidDescriptorChar = 4,
	EVRSpatial_Anchor_Error_VRSpatial_Anchor_Error_Not_Yet_شته = 5,
	EVRSpatial_Anchor_Error_VRSpatial_Anchor_Error_Not_شته_دننه_This_Universe = 6,
	EVRSpatialAnchorError_VRSpatialAnchorError_PermanentlyUnavailable = 7,
	EVRSpatialAnchorError_VRSpatialAnchorError_WrongDriver = 8,
	EVRSpatialAnchorError_VRSpatialAnchorError_DescriptorTooLong = 9,
	EVRSpatialAnchorError_VRSpatialAnchorError_Unknown = 10,
	EVRSpatial_Anchor_Error_VRSpatial_Anchor_Error_No_ځای_Calibration = 11,
	EVRSpatial_Anchor_Error_VRSpatial_Anchor_Error_Invalid_دلیل = 12,
	EVRSpatialAnchorError_VRSpatialAnchorError_UnknownDriver = 13,
} EVRSpatialAnchorError;

تعريفنوع تعداد EHiddenAreaMeshType
{
	EHiddenAreaMeshType_k_eHiddenAreaMesh_Standard = 0,
	EHiddenAreaMeshType_k_eHiddenAreaMesh_Inverse = 1,
	EHidden_Area_Mesh_Type_k_e_Hidden_Area_Mesh_کرښه_Loop = 2,
	EHiddenAreaMeshType_k_eHiddenAreaMesh_Max = 3,
} EHiddenAreaMeshType;

تعريفنوع تعداد EVRControllerAxisType
{
	EVRControllerAxisType_k_eControllerAxis_None = 0,
	EVRControllerAxisType_k_eControllerAxis_TrackPad = 1,
	EVRControllerAxisType_k_eControllerAxis_Joystick = 2,
	EVRControllerAxisType_k_eControllerAxis_Trigger = 3,
} EVRControllerAxisType;

تعريفنوع تعداد EVRControllerEventOutputType
{
	EVRControllerEventOutputType_ControllerEventOutput_OSEvents = 0,
	EVRControllerEventOutputType_ControllerEventOutput_VREvents = 1,
} EVRControllerEventOutputType;

تعريفنوع تعداد ECollisionBoundsStyle
{
	ECollisionBoundsStyle_COLLISION_BOUNDS_STYLE_BEGINNER = 0,
	ECollisionBoundsStyle_COLLISION_BOUNDS_STYLE_INTERMEDIATE = 1,
	ECollisionBoundsStyle_COLLISION_BOUNDS_STYLE_SQUARES = 2,
	ECollisionBoundsStyle_COLLISION_BOUNDS_STYLE_ADVANCED = 3,
	ECollisionBoundsStyle_COLLISION_BOUNDS_STYLE_NONE = 4,
	ECollision_Bounds_Style_COLLISION_BOUNDS_STYLE_شمېر = 5,
} ECollisionBoundsStyle;

تعريفنوع تعداد EVROverlayError
{
	EVROverlayError_VROverlayError_None = 0,
	EVROverlayError_VROverlayError_UnknownOverlay = 10,
	EVROverlayError_VROverlayError_InvalidHandle = 11,
	EVROverlayError_VROverlayError_PermissionDenied = 12,
	EVROverlay_Error_VROverlay_Error_Overlay_حد_Exceeded = 13,
	EVROverlayError_VROverlayError_WrongVisibilityType = 14,
	EVROverlay_Error_VROverlay_Error_کلی_Too_Long = 15,
	EVROverlayError_VROverlayError_NameTooLong = 16,
	EVROverlay_Error_VROverlay_Error_کلی_دننه_Use = 17,
	EVROverlayError_VROverlayError_WrongTransformType = 18,
	EVROverlayError_VROverlayError_InvalidTrackedDevice = 19,
	EVROverlayError_VROverlayError_InvalidParameter = 20,
	EVROverlayError_VROverlayError_ThumbnailCantBeDestroyed = 21,
	EVROverlayError_VROverlayError_ArrayTooSmall = 22,
	EVROverlayError_VROverlayError_RequestFailed = 23,
	EVROverlayError_VROverlayError_InvalidTexture = 24,
	EVROverlay_Error_VROverlay_Error_Unable_منزل_بارول_File = 25,
	EVROverlay_Error_VROverlay_Error_Keyboard_Already_دننه_Use = 26,
	EVROverlayError_VROverlayError_NoNeighbor = 27,
	EVROverlay_Error_VROverlay_Error_Too_Many_ماسک_Primitives = 29,
	EVROverlay_Error_VROverlay_Error_Bad_ماسک_Primitive = 30,
	EVROverlayError_VROverlayError_TextureAlreadyLocked = 31,
	EVROverlay_Error_VROverlay_Error_Texture_قلف_ظرفیت_Reached = 32,
	EVROverlayError_VROverlayError_TextureNotLocked = 33,
	EVROverlay_Error_VROverlay_Error_Timed_بهر = 34,
} EVROverlayError;

تعريفنوع تعداد EVRApplicationType
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
	EVRApplication_Type_VRApplication_ځای_View = 13,
	EVRApplicationType_VRApplication_Max = 14,
} EVRApplicationType;

تعريفنوع تعداد EVRFirmwareError
{
	EVRFirmwareError_VRFirmwareError_None = 0,
	EVRFirmwareError_VRFirmwareError_Success = 1,
	EVRFirmwareError_VRFirmwareError_Fail = 2,
} EVRFirmwareError;

تعريفنوع تعداد EVRNotificationError
{
	EVRNotificationError_VRNotificationError_OK = 0,
	EVRNotificationError_VRNotificationError_InvalidNotificationId = 100,
	EVRNotification_Error_VRNotification_Error_Notification_کتار_ډک = 101,
	EVRNotificationError_VRNotificationError_InvalidOverlayHandle = 102,
	EVRNotification_Error_VRNotification_Error_System_With_User_ارزښت_Already_Exists = 103,
} EVRNotificationError;

تعريفنوع تعداد EVRSkeletalMotionRange
{
	EVRSkeletalMotionRange_VRSkeletalMotionRange_WithController = 0,
	EVRSkeletalMotionRange_VRSkeletalMotionRange_WithoutController = 1,
} EVRSkeletalMotionRange;

تعريفنوع تعداد EVRSkeletalTrackingLevel
{
	EVRSkeletalTrackingLevel_VRSkeletalTracking_Estimated = 0,
	EVRSkeletalTrackingLevel_VRSkeletalTracking_Partial = 1,
	EVRSkeletal_Tracking_Level_VRSkeletal_Tracking_ډک = 2,
	EVRSkeletal_Tracking_Level_VRSkeletal_Tracking_Level_شمېر = 3,
	EVRSkeletalTrackingLevel_VRSkeletalTrackingLevel_Max = 2,
} EVRSkeletalTrackingLevel;

تعريفنوع تعداد EVRInitError
{
	EVRInitError_VRInitError_None = 0,
	EVRInitError_VRInitError_Unknown = 1,
	EVRInit_Error_VRInit_Error_Init_Installation_Not_وموندل = 100,
	EVRInitError_VRInitError_Init_InstallationCorrupt = 101,
	EVRInit_Error_VRInit_Error_Init_VRClient_DLLNot_وموندل = 102,
	EVRInit_Error_VRInit_Error_Init_File_Not_وموندل = 103,
	EVRInit_Error_VRInit_Error_Init_Factory_Not_وموندل = 104,
	EVRInit_Error_VRInit_Error_Init_Interface_Not_وموندل = 105,
	EVRInitError_VRInitError_Init_InvalidInterface = 106,
	EVRInitError_VRInitError_Init_UserConfigDirectoryInvalid = 107,
	EVRInit_Error_VRInit_Error_Init_Hmd_Not_وموندل = 108,
	EVRInitError_VRInitError_Init_NotInitialized = 109,
	EVRInit_Error_VRInit_Error_Init_لار_Registry_Not_وموندل = 110,
	EVRInit_Error_VRInit_Error_Init_No_Config_لار = 111,
	EVRInit_Error_VRInit_Error_Init_No_Log_لار = 112,
	EVRInit_Error_VRInit_Error_Init_لار_Registry_Not_Writable = 113,
	EVRInitError_VRInitError_Init_AppInfoInitFailed = 114,
	EVRInitError_VRInitError_Init_Retry = 115,
	EVRInitError_VRInitError_Init_InitCanceledByUser = 116,
	EVRInitError_VRInitError_Init_AnotherAppLaunching = 117,
	EVRInitError_VRInitError_Init_SettingsInitFailed = 118,
	EVRInit_Error_VRInit_Error_Init_Shutting_ښکته = 119,
	EVRInitError_VRInitError_Init_TooManyObjects = 120,
	EVRInitError_VRInitError_Init_NoServerForBackgroundApp = 121,
	EVRInitError_VRInitError_Init_NotSupportedWithCompositor = 122,
	EVRInit_Error_VRInit_Error_Init_Not_شته_منزل_Utility_Apps = 123,
	EVRInit_Error_VRInit_Error_Init_دننی = 124,
	EVRInitError_VRInitError_Init_HmdDriverIdIsNone = 125,
	EVRInit_Error_VRInit_Error_Init_Hmd_Not_وموندل_Presence_Failed = 126,
	EVRInit_Error_VRInit_Error_Init_VRMonitor_Not_وموندل = 127,
	EVRInitError_VRInitError_Init_VRMonitorStartupFailed = 128,
	EVRInit_Error_VRInit_Error_Init_ټیټ_Power_Watchdog_Not_Supported = 129,
	EVRInitError_VRInitError_Init_InvalidApplicationType = 130,
	EVRInit_Error_VRInit_Error_Init_Not_شته_منزل_Watchdog_Apps = 131,
	EVRInit_Error_VRInit_Error_Init_Watchdog_Disabled_دننه_Settings = 132,
	EVRInit_Error_VRInit_Error_Init_VRDashboard_Not_وموندل = 133,
	EVRInitError_VRInitError_Init_VRDashboardStartupFailed = 134,
	EVRInit_Error_VRInit_Error_Init_VRHome_Not_وموندل = 135,
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
	EVRInit_Error_VRInit_Error_Init_Prism_Startup_Timed_بهر = 152,
	EVRInit_Error_VRInit_Error_Init_Could_Not_پیل_Prism = 153,
	EVRInitError_VRInitError_Init_PrismClientInitFailed = 154,
	EVRInit_Error_VRInit_Error_Init_Prism_Client_پیل_Failed = 155,
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
	EVRInit_Error_VRInit_Error_Init_VRDashboard_لار_Failure = 167,
	EVRInitError_VRInitError_Driver_Failed = 200,
	EVRInitError_VRInitError_Driver_Unknown = 201,
	EVRInitError_VRInitError_Driver_HmdUnknown = 202,
	EVRInitError_VRInitError_Driver_NotLoaded = 203,
	EVRInit_Error_VRInit_Error_Driver_Runtime_بهر_د_Date = 204,
	EVRInit_Error_VRInit_Error_Driver_Hmd_دننه_Use = 205,
	EVRInitError_VRInitError_Driver_NotCalibrated = 206,
	EVRInitError_VRInitError_Driver_CalibrationInvalid = 207,
	EVRInit_Error_VRInit_Error_Driver_Hmd_Display_Not_وموندل = 208,
	EVRInitError_VRInitError_Driver_TrackedDeviceInterfaceUnknown = 209,
	EVRInit_Error_VRInit_Error_Driver_Hmd_Driver_Id_بهر_د_Bounds = 211,
	EVRInitError_VRInitError_Driver_HmdDisplayMirrored = 212,
	EVRInit_Error_VRInit_Error_Driver_Hmd_Display_Not_وموندل_Laptop = 213,
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
	EVRInit_Error_VRInit_Error_IPC_Connect_Failed_After_مضرب_Attempts = 308,
	EVRInit_Error_VRInit_Error_IPC_Connect_Failed_After_موخه_Exited = 309,
	EVRInitError_VRInitError_IPC_NamespaceUnavailable = 310,
	EVRInitError_VRInitError_Compositor_Failed = 400,
	EVRInitError_VRInitError_Compositor_D3D11HardwareRequired = 401,
	EVRInitError_VRInitError_Compositor_FirmwareRequiresUpdate = 402,
	EVRInitError_VRInitError_Compositor_OverlayInitFailed = 403,
	EVRInitError_VRInitError_Compositor_ScreenshotsInitFailed = 404,
	EVRInit_Error_VRInit_Error_Compositor_Unable_منزل_Create_Device = 405,
	EVRInitError_VRInitError_Compositor_SharedStateIsNull = 406,
	EVRInitError_VRInitError_Compositor_NotificationManagerIsNull = 407,
	EVRInitError_VRInitError_Compositor_ResourceManagerClientIsNull = 408,
	EVRInit_Error_VRInit_Error_Compositor_پیغام_Overlay_Shared_State_Init_Failure = 409,
	EVRInitError_VRInitError_Compositor_PropertiesInterfaceIsNull = 410,
	EVRInit_Error_VRInit_Error_Compositor_Create_Fullscreen_کړکۍ_Failed = 411,
	EVRInitError_VRInitError_Compositor_SettingsInterfaceIsNull = 412,
	EVRInit_Error_VRInit_Error_Compositor_Failed_منزل_Show_کړکۍ = 413,
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
	EVRInit_Error_VRInit_Error_Compositor_Failed_منزل_پیدا_کړه_Display_ډېرپېښ = 425,
	EVRInit_Error_VRInit_Error_Compositor_Failed_منزل_Create_بدلون_Chain = 426,
	EVRInit_Error_VRInit_Error_Compositor_Failed_منزل_Get_شا_بفر = 427,
	EVRInit_Error_VRInit_Error_Compositor_Failed_منزل_Create_Render_موخه = 428,
	EVRInit_Error_VRInit_Error_Compositor_Failed_منزل_Create_DXGI2_بدلون_Chain = 429,
	EVRInit_Error_VRInit_Error_Compositor_Failedto_Get_DXGI2_شا_بفر = 430,
	EVRInit_Error_VRInit_Error_Compositor_Failed_منزل_Create_DXGI2_Render_موخه = 431,
	EVRInit_Error_VRInit_Error_Compositor_Failed_منزل_Get_DXGIDevice_Interface = 432,
	EVRInit_Error_VRInit_Error_Compositor_Select_Display_ډېرپېښ = 433,
	EVRInit_Error_VRInit_Error_Compositor_Failed_منزل_Create_Nv_APIRender_Targets = 434,
	EVRInit_Error_VRInit_Error_Compositor_Nv_APISet_Display_ډېرپېښ = 435,
	EVRInit_Error_VRInit_Error_Compositor_Failed_منزل_Create_مستقیم_ډېرپېښ_Display = 436,
	EVRInitError_VRInitError_Compositor_InvalidHmdPropertyContainer = 437,
	EVRInitError_VRInitError_Compositor_UpdateDisplayFrequency = 438,
	EVRInitError_VRInitError_Compositor_CreateRasterizerState = 439,
	EVRInitError_VRInitError_Compositor_CreateWireframeRasterizerState = 440,
	EVRInitError_VRInitError_Compositor_CreateSamplerState = 441,
	EVRInit_Error_VRInit_Error_Compositor_Create_Clamp_منزل_Border_Sampler_State = 442,
	EVRInitError_VRInitError_Compositor_CreateAnisoSamplerState = 443,
	EVRInitError_VRInitError_Compositor_CreateOverlaySamplerState = 444,
	EVRInitError_VRInitError_Compositor_CreatePanoramaSamplerState = 445,
	EVRInitError_VRInitError_Compositor_CreateFontSamplerState = 446,
	EVRInitError_VRInitError_Compositor_CreateNoBlendState = 447,
	EVRInitError_VRInitError_Compositor_CreateBlendState = 448,
	EVRInitError_VRInitError_Compositor_CreateAlphaBlendState = 449,
	EVRInit_Error_VRInit_Error_Compositor_Create_Blend_State_ماسک_R = 450,
	EVRInit_Error_VRInit_Error_Compositor_Create_Blend_State_ماسک_G = 451,
	EVRInit_Error_VRInit_Error_Compositor_Create_Blend_State_ماسک_B = 452,
	EVRInit_Error_VRInit_Error_Compositor_Create_ژوروالی_Stencil_State = 453,
	EVRInit_Error_VRInit_Error_Compositor_Create_ژوروالی_Stencil_State_No_Write = 454,
	EVRInit_Error_VRInit_Error_Compositor_Create_ژوروالی_Stencil_State_No_ژوروالی = 455,
	EVRInitError_VRInitError_Compositor_CreateFlushTexture = 456,
	EVRInitError_VRInitError_Compositor_CreateDistortionSurfaces = 457,
	EVRInit_Error_VRInit_Error_Compositor_Create_Constant_بفر = 458,
	EVRInit_Error_VRInit_Error_Compositor_Create_Hmd_Pose_Constant_بفر = 459,
	EVRInit_Error_VRInit_Error_Compositor_Create_Hmd_Pose_Staging_Constant_بفر = 460,
	EVRInit_Error_VRInit_Error_Compositor_Create_Shared_چوکاټ_Info_Constant_بفر = 461,
	EVRInit_Error_VRInit_Error_Compositor_Create_Overlay_Constant_بفر = 462,
	EVRInit_Error_VRInit_Error_Compositor_Create_Scene_Texture_شاخص_Constant_بفر = 463,
	EVRInit_Error_VRInit_Error_Compositor_Create_Readable_Scene_Texture_شاخص_Constant_بفر = 464,
	EVRInit_Error_VRInit_Error_Compositor_Create_Layer_Graphics_Texture_شاخص_Constant_بفر = 465,
	EVRInit_Error_VRInit_Error_Compositor_Create_Layer_Compute_Texture_شاخص_Constant_بفر = 466,
	EVRInit_Error_VRInit_Error_Compositor_Create_Layer_Compute_Scene_Texture_شاخص_Constant_بفر = 467,
	EVRInit_Error_VRInit_Error_Compositor_Create_Compute_Hmd_Pose_Constant_بفر = 468,
	EVRInit_Error_VRInit_Error_Compositor_Create_Geom_Constant_بفر = 469,
	EVRInit_Error_VRInit_Error_Compositor_Create_Panel_ماسک_Constant_بفر = 470,
	EVRInitError_VRInitError_Compositor_CreatePixelSimUBO = 471,
	EVRInitError_VRInitError_Compositor_CreateMSAARenderTextures = 472,
	EVRInitError_VRInitError_Compositor_CreateResolveRenderTextures = 473,
	EVRInitError_VRInitError_Compositor_CreateComputeResolveRenderTextures = 474,
	EVRInit_Error_VRInit_Error_Compositor_Create_Driver_مستقیم_ډېرپېښ_Resolve_Textures = 475,
	EVRInit_Error_VRInit_Error_Compositor_Open_Driver_مستقیم_ډېرپېښ_Resolve_Textures = 476,
	EVRInitError_VRInitError_Compositor_CreateFallbackSyncTexture = 477,
	EVRInitError_VRInitError_Compositor_ShareFallbackSyncTexture = 478,
	EVRInit_Error_VRInit_Error_Compositor_Create_Overlay_شاخص_بفر = 479,
	EVRInit_Error_VRInit_Error_Compositor_Create_Overlay_راس_بفر = 480,
	EVRInit_Error_VRInit_Error_Compositor_Create_متن_راس_بفر = 481,
	EVRInit_Error_VRInit_Error_Compositor_Create_متن_شاخص_بفر = 482,
	EVRInitError_VRInitError_Compositor_CreateMirrorTextures = 483,
	EVRInit_Error_VRInit_Error_Compositor_Create_وروستی_چوکاټ_Render_Texture = 484,
	EVRInitError_VRInitError_Compositor_CreateMirrorOverlay = 485,
	EVRInit_Error_VRInit_Error_Compositor_Failed_منزل_Create_Virtual_Display_Backbuffer = 486,
	EVRInit_Error_VRInit_Error_Compositor_Display_ډېرپېښ_Not_Supported = 487,
	EVRInitError_VRInitError_Compositor_CreateOverlayInvalidCall = 488,
	EVRInitError_VRInitError_Compositor_CreateOverlayAlreadyInitialized = 489,
	EVRInit_Error_VRInit_Error_Compositor_Failed_منزل_Create_Mailbox = 490,
	EVRInit_Error_VRInit_Error_Compositor_کړکۍ_Interface_Is_Null = 491,
	EVRInitError_VRInitError_Compositor_SystemLayerCreateInstance = 492,
	EVRInitError_VRInitError_Compositor_SystemLayerCreateSession = 493,
	EVRInitError_VRInitError_Compoistor_CreateInverseDistortUVs = 494,
	EVRInit_Error_VRInit_Error_Compoistor_Create_Backbuffer_ژوروالی = 495,
	EVRInit_Error_VRInit_Error_Vendor_Specific_Unable_منزل_Connect_منزل_Oculus_Runtime = 1000,
	EVRInit_Error_VRInit_Error_Vendor_Specific_Windows_Not_دننه_Dev_ډېرپېښ = 1001,
	EVRInitError_VRInitError_VendorSpecific_OculusLinkNotEnabled = 1002,
	EVRInit_Error_VRInit_Error_Vendor_Specific_Hmd_وموندل_Cant_Open_Device = 1101,
	EVRInit_Error_VRInit_Error_Vendor_Specific_Hmd_وموندل_Unable_منزل_Request_Config_پیل = 1102,
	EVRInit_Error_VRInit_Error_Vendor_Specific_Hmd_وموندل_No_Stored_Config = 1103,
	EVRInit_Error_VRInit_Error_Vendor_Specific_Hmd_وموندل_Config_Too_Big = 1104,
	EVRInit_Error_VRInit_Error_Vendor_Specific_Hmd_وموندل_Config_Too_Small = 1105,
	EVRInit_Error_VRInit_Error_Vendor_Specific_Hmd_وموندل_Unable_منزل_Init_ZLib = 1106,
	EVRInit_Error_VRInit_Error_Vendor_Specific_Hmd_وموندل_Cant_Read_Firmware_نسخه = 1107,
	EVRInit_Error_VRInit_Error_Vendor_Specific_Hmd_وموندل_Unable_منزل_Send_User_معلومات_پیل = 1108,
	EVRInit_Error_VRInit_Error_Vendor_Specific_Hmd_وموندل_Unable_منزل_Get_User_معلومات_پیل = 1109,
	EVRInit_Error_VRInit_Error_Vendor_Specific_Hmd_وموندل_Unable_منزل_Get_User_معلومات_بل = 1110,
	EVRInit_Error_VRInit_Error_Vendor_Specific_Hmd_وموندل_User_معلومات_پته_Range = 1111,
	EVRInit_Error_VRInit_Error_Vendor_Specific_Hmd_وموندل_User_معلومات_Error = 1112,
	EVRInit_Error_VRInit_Error_Vendor_Specific_Hmd_وموندل_Config_Failed_Sanity_Check = 1113,
	EVRInitError_VRInitError_VendorSpecific_OculusRuntimeBadInstall = 1114,
	EVRInit_Error_VRInit_Error_Vendor_Specific_Hmd_وموندل_Unexpected_Configuration_1 = 1115,
	EVRInit_Error_VRInit_Error_Steam_Steam_Installation_Not_وموندل = 2000,
	EVRInit_Error_VRInit_Error_وروستی_Error = 2001,
} EVRInitError;

تعريفنوع تعداد EVRScreenshotType
{
	EVRScreenshotType_VRScreenshotType_None = 0,
	EVRScreenshotType_VRScreenshotType_Mono = 1,
	EVRScreenshotType_VRScreenshotType_Stereo = 2,
	EVRScreenshotType_VRScreenshotType_Cubemap = 3,
	EVRScreenshotType_VRScreenshotType_MonoPanorama = 4,
	EVRScreenshotType_VRScreenshotType_StereoPanorama = 5,
} EVRScreenshotType;

تعريفنوع تعداد EVRScreenshotPropertyFilenames
{
	EVRScreenshotPropertyFilenames_VRScreenshotPropertyFilenames_Preview = 0,
	EVRScreenshotPropertyFilenames_VRScreenshotPropertyFilenames_VR = 1,
} EVRScreenshotPropertyFilenames;

تعريفنوع تعداد EVRTrackedCameraError
{
	EVRTrackedCameraError_VRTrackedCameraError_None = 0,
	EVRTrackedCameraError_VRTrackedCameraError_OperationFailed = 100,
	EVRTrackedCameraError_VRTrackedCameraError_InvalidHandle = 101,
	EVRTracked_Camera_Error_VRTracked_Camera_Error_Invalid_چوکاټ_سرلیک_نسخه = 102,
	EVRTracked_Camera_Error_VRTracked_Camera_Error_بهر_د_Handles = 103,
	EVRTrackedCameraError_VRTrackedCameraError_IPCFailure = 104,
	EVRTrackedCameraError_VRTrackedCameraError_NotSupportedForThisDevice = 105,
	EVRTracked_Camera_Error_VRTracked_Camera_Error_Shared_حافظه_Failure = 106,
	EVRTracked_Camera_Error_VRTracked_Camera_Error_چوکاټ_Buffering_Failure = 107,
	EVRTracked_Camera_Error_VRTracked_Camera_Error_بهیر_تیاری_Failure = 108,
	EVRTrackedCameraError_VRTrackedCameraError_InvalidGLTextureId = 109,
	EVRTrackedCameraError_VRTrackedCameraError_InvalidSharedTextureHandle = 110,
	EVRTracked_Camera_Error_VRTracked_Camera_Error_Failed_منزل_Get_GLTexture_Id = 111,
	EVRTrackedCameraError_VRTrackedCameraError_SharedTextureFailure = 112,
	EVRTracked_Camera_Error_VRTracked_Camera_Error_No_چوکاټ_شته = 113,
	EVRTracked_Camera_Error_VRTracked_Camera_Error_Invalid_دلیل = 114,
	EVRTracked_Camera_Error_VRTracked_Camera_Error_Invalid_چوکاټ_بفر_اندازه = 115,
} EVRTrackedCameraError;

تعريفنوع تعداد EVRTracked_Camera_چوکاټ_Layout
{
	EVRTracked_Camera_چوکاټ_Layout_Mono = 1,
	EVRTracked_Camera_چوکاټ_Layout_Stereo = 2,
	EVRTracked_Camera_چوکاټ_Layout_Vertical_Layout = 16,
	EVRTracked_Camera_چوکاټ_Layout_Horizontal_Layout = 32,
} EVRTracked_Camera_چوکاټ_Layout;

تعريفنوع تعداد EVRTracked_Camera_چوکاټ_Type
{
	EVRTracked_Camera_چوکاټ_Type_VRTracked_Camera_چوکاټ_Type_Distorted = 0,
	EVRTracked_Camera_چوکاټ_Type_VRTracked_Camera_چوکاټ_Type_Undistorted = 1,
	EVRTracked_Camera_چوکاټ_Type_VRTracked_Camera_چوکاټ_Type_اعظمي_Undistorted = 2,
	EVRTracked_Camera_چوکاټ_Type_MAX_CAMERA_چوکاټ_TYPES = 3,
} EVRTracked_Camera_چوکاټ_Type;

تعريفنوع تعداد EVRDistortionFunctionType
{
	EVRDistortionFunctionType_VRDistortionFunctionType_None = 0,
	EVRDistortionFunctionType_VRDistortionFunctionType_FTheta = 1,
	EVRDistortionFunctionType_VRDistortionFunctionType_Extended_FTheta = 2,
	EVRDistortionFunctionType_MAX_DISTORTION_FUNCTION_TYPES = 3,
} EVRDistortionFunctionType;

تعريفنوع تعداد EVSync
{
	EVSync_VSync_None = 0,
	EVSync_VSync_WaitRender = 1,
	EVSync_VSync_NoWaitRender = 2,
} EVSync;

تعريفنوع تعداد EVRMura_Correction_ډېرپېښ
{
	EVRMura_Correction_ډېرپېښ_Default = 0,
	EVRMura_Correction_ډېرپېښ_No_Correction = 1,
} EVRMura_Correction_ډېرپېښ;

تعريفنوع تعداد Imu_OffScaleFlags
{
	Imu_OffScaleFlags_OffScale_AccelX = 1,
	Imu_OffScaleFlags_OffScale_AccelY = 2,
	Imu_OffScaleFlags_OffScale_AccelZ = 4,
	Imu_OffScaleFlags_OffScale_GyroX = 8,
	Imu_OffScaleFlags_OffScale_GyroY = 16,
	Imu_OffScaleFlags_OffScale_GyroZ = 32,
} Imu_OffScaleFlags;

تعريفنوع تعداد EVRApplicationError
{
	EVRApplicationError_VRApplicationError_None = 0,
	EVRApplication_Error_VRApplication_Error_App_کلی_Already_Exists = 100,
	EVRApplicationError_VRApplicationError_NoManifest = 101,
	EVRApplicationError_VRApplicationError_NoApplication = 102,
	EVRApplication_Error_VRApplication_Error_Invalid_شاخص = 103,
	EVRApplicationError_VRApplicationError_UnknownApplication = 104,
	EVRApplicationError_VRApplicationError_IPCFailed = 105,
	EVRApplicationError_VRApplicationError_ApplicationAlreadyRunning = 106,
	EVRApplicationError_VRApplicationError_InvalidManifest = 107,
	EVRApplicationError_VRApplicationError_InvalidApplication = 108,
	EVRApplicationError_VRApplicationError_LaunchFailed = 109,
	EVRApplicationError_VRApplicationError_ApplicationAlreadyStarting = 110,
	EVRApplication_Error_VRApplication_Error_Launch_دننه_پرمختګ = 111,
	EVRApplicationError_VRApplicationError_OldApplicationQuitting = 112,
	EVRApplicationError_VRApplicationError_TransitionAborted = 113,
	EVRApplicationError_VRApplicationError_IsTemplate = 114,
	EVRApplicationError_VRApplicationError_SteamVRIsExiting = 115,
	EVRApplication_Error_VRApplication_Error_بفر_Too_Small = 200,
	EVRApplication_Error_VRApplication_Error_Property_Not_سېټ = 201,
	EVRApplicationError_VRApplicationError_UnknownProperty = 202,
	EVRApplicationError_VRApplicationError_InvalidParameter = 203,
	EVRApplicationError_VRApplicationError_NotImplemented = 300,
} EVRApplicationError;

تعريفنوع تعداد EVRApplicationProperty
{
	EVRApplicationProperty_VRApplicationProperty_Name_String = 0,
	EVRApplicationProperty_VRApplicationProperty_LaunchType_String = 11,
	EVRApplicationProperty_VRApplicationProperty_WorkingDirectory_String = 12,
	EVRApplication_Property_VRApplication_Property_دوګونی_لار_String = 13,
	EVRApplicationProperty_VRApplicationProperty_Arguments_String = 14,
	EVRApplicationProperty_VRApplicationProperty_URL_String = 15,
	EVRApplicationProperty_VRApplicationProperty_Description_String = 50,
	EVRApplicationProperty_VRApplicationProperty_NewsURL_String = 51,
	EVRApplication_Property_VRApplication_Property_Image_لار_String = 52,
	EVRApplication_Property_VRApplication_Property_سرچینه_String = 53,
	EVRApplicationProperty_VRApplicationProperty_ActionManifestURL_String = 54,
	EVRApplicationProperty_VRApplicationProperty_IsDashboardOverlay_Bool = 60,
	EVRApplicationProperty_VRApplicationProperty_IsTemplate_Bool = 61,
	EVRApplicationProperty_VRApplicationProperty_IsInstanced_Bool = 62,
	EVRApplication_Property_VRApplication_Property_Is_دننی_Bool = 63,
	EVRApplication_Property_VRApplication_Property_غواړي_Compositor_Pause_دننه_Standby_Bool = 64,
	EVRApplicationProperty_VRApplicationProperty_IsHidden_Bool = 65,
	EVRApplication_Property_VRApplication_Property_وروستی_Launch_وخت_Uint64 = 70,
} EVRApplicationProperty;

تعريفنوع تعداد EVRSceneApplicationState
{
	EVRSceneApplicationState_None = 0,
	EVRSceneApplicationState_Starting = 1,
	EVRSceneApplicationState_Quitting = 2,
	EVRSceneApplicationState_Running = 3,
	EVRScene_Application_State_انتظار = 4,
} EVRSceneApplicationState;

تعريفنوع تعداد ChaperoneCalibrationState
{
	ChaperoneCalibrationState_OK = 1,
	ChaperoneCalibrationState_Warning = 100,
	Chaperone_Calibration_State_Warning_بنسټ_Station_May_Have_Moved = 101,
	Chaperone_Calibration_State_Warning_بنسټ_Station_Removed = 102,
	ChaperoneCalibrationState_Warning_SeatedBoundsInvalid = 103,
	ChaperoneCalibrationState_Error = 200,
	Chaperone_Calibration_State_Error_بنسټ_Station_Uninitialized = 201,
	Chaperone_Calibration_State_Error_بنسټ_Station_Conflict = 202,
	ChaperoneCalibrationState_Error_PlayAreaInvalid = 203,
	ChaperoneCalibrationState_Error_CollisionBoundsInvalid = 204,
} ChaperoneCalibrationState;

تعريفنوع تعداد EChaperoneConfigFile
{
	EChaperone_Config_File_ژوندی = 1,
	EChaperone_Config_File_لنډمهاله = 2,
} EChaperoneConfigFile;

تعريفنوع تعداد EChaperoneImportFlags
{
	EChaperoneImportFlags_EChaperoneImport_BoundsOnly = 1,
} EChaperoneImportFlags;

تعريفنوع تعداد EVRCompositorError
{
	EVRCompositorError_VRCompositorError_None = 0,
	EVRCompositorError_VRCompositorError_RequestFailed = 1,
	EVRCompositor_Error_VRCompositor_Error_Incompatible_نسخه = 100,
	EVRCompositorError_VRCompositorError_DoNotHaveFocus = 101,
	EVRCompositorError_VRCompositorError_InvalidTexture = 102,
	EVRCompositorError_VRCompositorError_IsNotSceneApplication = 103,
	EVRCompositorError_VRCompositorError_TextureIsOnWrongDevice = 104,
	EVRCompositor_Error_VRCompositor_Error_Texture_کاروي_Unsupported_Format = 105,
	EVRCompositorError_VRCompositorError_SharedTexturesNotSupported = 106,
	EVRCompositor_Error_VRCompositor_Error_شاخص_بهر_د_Range = 107,
	EVRCompositorError_VRCompositorError_AlreadySubmitted = 108,
	EVRCompositorError_VRCompositorError_InvalidBounds = 109,
	EVRCompositor_Error_VRCompositor_Error_Already_سېټ = 110,
} EVRCompositorError;

تعريفنوع تعداد EVRCompositor_Timing_ډېرپېښ
{
	EVRCompositor_Timing_ډېرپېښ_VRCompositor_Timing_ډېرپېښ_Implicit = 0,
	EVRCompositor_Timing_ډېرپېښ_VRCompositor_Timing_ډېرپېښ_Explicit_Runtime_Performs_Post_Present_Handoff = 1,
	EVRCompositor_Timing_ډېرپېښ_VRCompositor_Timing_ډېرپېښ_Explicit_Application_Performs_Post_Present_Handoff = 2,
} EVRCompositor_Timing_ډېرپېښ;

تعريفنوع تعداد VROverlay_ننوت_لاره
{
	VROverlay_ننوت_لاره_None = 0,
	VROverlay_ننوت_لاره_Mouse = 1,
} VROverlay_ننوت_لاره;

تعريفنوع تعداد VROverlayTransformType
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

تعريفنوع تعداد VROverlayFlags
{
	VROverlayFlags_NoDashboardTab = 8,
	VROverlayFlags_SendVRDiscreteScrollEvents = 64,
	VROverlayFlags_SendVRTouchpadEvents = 128,
	VROverlayFlags_ShowTouchPadScrollWheel = 256,
	VROverlay_Flags_Transfer_Ownership_منزل_دننی_Process = 512,
	VROverlayFlags_SideBySide_Parallel = 1024,
	VROverlayFlags_SideBySide_Crossed = 2048,
	VROverlayFlags_Panorama = 4096,
	VROverlayFlags_StereoPanorama = 8192,
	VROverlay_Flags_ترتیبول_With_Non_Scene_Overlays = 16384,
	VROverlay_Flags_Visible_دننه_Dashboard = 32768,
	VROverlayFlags_MakeOverlaysInteractiveIfVisible = 65536,
	VROverlayFlags_SendVRSmoothScrollEvents = 131072,
	VROverlayFlags_ProtectedContent = 262144,
	VROverlayFlags_HideLaserIntersection = 524288,
	VROverlay_Flags_غواړي_Modal_Behavior = 1048576,
	VROverlayFlags_IsPremultiplied = 2097152,
	VROverlayFlags_IgnoreTextureAlpha = 4194304,
	VROverlayFlags_EnableControlBar = 8388608,
	VROverlayFlags_EnableControlBarKeyboard = 16777216,
	VROverlayFlags_EnableControlBarClose = 33554432,
} VROverlayFlags;

تعريفنوع تعداد VRMessageOverlayResponse
{
	VRMessageOverlayResponse_ButtonPress_0 = 0,
	VRMessageOverlayResponse_ButtonPress_1 = 1,
	VRMessageOverlayResponse_ButtonPress_2 = 2,
	VRMessageOverlayResponse_ButtonPress_3 = 3,
	VRMessage_Overlay_Response_Couldnt_پیدا_کړه_System_Overlay = 4,
	VRMessage_Overlay_Response_Couldnt_پیدا_کړه_Or_Create_Client_Overlay = 5,
	VRMessageOverlayResponse_ApplicationQuit = 6,
} VRMessageOverlayResponse;

تعريفنوع تعداد EGamepad_متن_ننوت_ډېرپېښ
{
	EGamepad_متن_ننوت_ډېرپېښ_k_EGamepad_متن_ننوت_ډېرپېښ_نورمال = 0,
	EGamepad_متن_ننوت_ډېرپېښ_k_EGamepad_متن_ننوت_ډېرپېښ_Password = 1,
	EGamepad_متن_ننوت_ډېرپېښ_k_EGamepad_متن_ننوت_ډېرپېښ_Submit = 2,
} EGamepad_متن_ننوت_ډېرپېښ;

تعريفنوع تعداد EGamepad_متن_ننوت_کرښه_ډېرپېښ
{
	EGamepad_متن_ننوت_کرښه_ډېرپېښ_k_EGamepad_متن_ننوت_کرښه_ډېرپېښ_Single_کرښه = 0,
	EGamepad_متن_ننوت_کرښه_ډېرپېښ_k_EGamepad_متن_ننوت_کرښه_ډېرپېښ_مضرب_کرښې = 1,
} EGamepad_متن_ننوت_کرښه_ډېرپېښ;

تعريفنوع تعداد EVROverlay_Intersection_ماسک_Primitive_Type
{
	EVROverlay_Intersection_ماسک_Primitive_Type_Overlay_Intersection_Primitive_Type_Rectangle = 0,
	EVROverlay_Intersection_ماسک_Primitive_Type_Overlay_Intersection_Primitive_Type_Circle = 1,
} EVROverlay_Intersection_ماسک_Primitive_Type;

تعريفنوع تعداد EKeyboardFlags
{
	EKeyboard_Flags_Keyboard_Flag_اصغري = 1,
	EKeyboardFlags_KeyboardFlag_Modal = 2,
} EKeyboardFlags;

تعريفنوع تعداد EDeviceType
{
	EDeviceType_DeviceType_Invalid = -1,
	EDevice_Type_Device_Type_مستقیم_X11 = 0,
	EDeviceType_DeviceType_Vulkan = 1,
} EDeviceType;

تعريفنوع تعداد Headset_View_ډېرپېښ_t
{
	Headset_View_ډېرپېښ_t_Headset_View_ډېرپېښ_کیڼ = 0,
	Headset_View_ډېرپېښ_t_Headset_View_ډېرپېښ_ښی = 1,
	Headset_View_ډېرپېښ_t_Headset_View_ډېرپېښ_Both = 2,
} Headset_View_ډېرپېښ_t;

تعريفنوع تعداد EVRRenderModelError
{
	EVRRenderModelError_VRRenderModelError_None = 0,
	EVRRenderModelError_VRRenderModelError_Loading = 100,
	EVRRenderModelError_VRRenderModelError_NotSupported = 200,
	EVRRenderModelError_VRRenderModelError_InvalidArg = 300,
	EVRRenderModelError_VRRenderModelError_InvalidModel = 301,
	EVRRenderModelError_VRRenderModelError_NoShapes = 302,
	EVRRender_Model_Error_VRRender_Model_Error_مضرب_Shapes = 303,
	EVRRenderModelError_VRRenderModelError_TooManyVertices = 304,
	EVRRender_Model_Error_VRRender_Model_Error_مضرب_Textures = 305,
	EVRRender_Model_Error_VRRender_Model_Error_بفر_Too_Small = 306,
	EVRRenderModelError_VRRenderModelError_NotEnoughNormals = 307,
	EVRRenderModelError_VRRenderModelError_NotEnoughTexCoords = 308,
	EVRRenderModelError_VRRenderModelError_InvalidTexture = 400,
} EVRRenderModelError;

تعريفنوع تعداد EVRRenderModelTextureFormat
{
	EVRRenderModelTextureFormat_VRRenderModelTextureFormat_RGBA8_SRGB = 0,
	EVRRenderModelTextureFormat_VRRenderModelTextureFormat_BC2 = 1,
	EVRRenderModelTextureFormat_VRRenderModelTextureFormat_BC4 = 2,
	EVRRenderModelTextureFormat_VRRenderModelTextureFormat_BC7 = 3,
	EVRRenderModelTextureFormat_VRRenderModelTextureFormat_BC7_SRGB = 4,
	EVRRenderModelTextureFormat_VRRenderModelTextureFormat_RGBA16_FLOAT = 5,
} EVRRenderModelTextureFormat;

تعريفنوع تعداد EVRNotificationType
{
	EVRNotificationType_Transient = 0,
	EVRNotificationType_Persistent = 1,
	EVRNotification_Type_Transient_System_With_User_ارزښت = 2,
} EVRNotificationType;

تعريفنوع تعداد EVRNotificationStyle
{
	EVRNotificationStyle_None = 0,
	EVRNotificationStyle_Application = 100,
	EVRNotificationStyle_Contact_Disabled = 200,
	EVRNotificationStyle_Contact_Enabled = 201,
	EVRNotification_Style_Contact_فعال = 202,
} EVRNotificationStyle;

تعريفنوع تعداد EVRSettingsError
{
	EVRSettingsError_VRSettingsError_None = 0,
	EVRSettingsError_VRSettingsError_IPCFailed = 1,
	EVRSettingsError_VRSettingsError_WriteFailed = 2,
	EVRSettingsError_VRSettingsError_ReadFailed = 3,
	EVRSettingsError_VRSettingsError_JsonParseFailed = 4,
	EVRSettingsError_VRSettingsError_UnsetSettingHasNoDefault = 5,
} EVRSettingsError;

تعريفنوع تعداد EVRScreenshotError
{
	EVRScreenshotError_VRScreenshotError_None = 0,
	EVRScreenshotError_VRScreenshotError_RequestFailed = 1,
	EVRScreenshot_Error_VRScreenshot_Error_Incompatible_نسخه = 100,
	EVRScreenshot_Error_VRScreenshot_Error_Not_وموندل = 101,
	EVRScreenshot_Error_VRScreenshot_Error_بفر_Too_Small = 102,
	EVRScreenshot_Error_VRScreenshot_Error_Screenshot_Already_دننه_پرمختګ = 108,
} EVRScreenshotError;

تعريفنوع تعداد EVRSkeletalTransformSpace
{
	EVRSkeletalTransformSpace_VRSkeletalTransformSpace_Model = 0,
	EVRSkeletal_Transform_Space_VRSkeletal_Transform_Space_پلار = 1,
} EVRSkeletalTransformSpace;

تعريفنوع تعداد EVRSkeletalReferencePose
{
	EVRSkeletalReferencePose_VRSkeletalReferencePose_BindPose = 0,
	EVRSkeletalReferencePose_VRSkeletalReferencePose_OpenHand = 1,
	EVRSkeletalReferencePose_VRSkeletalReferencePose_Fist = 2,
	EVRSkeletal_Reference_Pose_VRSkeletal_Reference_Pose_Grip_حد = 3,
} EVRSkeletalReferencePose;

تعريفنوع تعداد EVRFinger
{
	EVRFinger_VRFinger_Thumb = 0,
	EVRFinger_VRFinger_شاخص = 1,
	EVRFinger_VRFinger_منځ = 2,
	EVRFinger_VRFinger_Ring = 3,
	EVRFinger_VRFinger_Pinky = 4,
	EVRFinger_VRFinger_شمېر = 5,
} EVRFinger;

تعريفنوع تعداد EVRFingerSplay
{
	EVRFinger_Splay_VRFinger_Splay_Thumb_شاخص = 0,
	EVRFinger_Splay_VRFinger_Splay_شاخص_منځ = 1,
	EVRFinger_Splay_VRFinger_Splay_منځ_Ring = 2,
	EVRFingerSplay_VRFingerSplay_Ring_Pinky = 3,
	EVRFinger_Splay_VRFinger_Splay_شمېر = 4,
} EVRFingerSplay;

تعريفنوع تعداد EVRSummaryType
{
	EVRSummaryType_VRSummaryType_FromAnimation = 0,
	EVRSummaryType_VRSummaryType_FromDevice = 1,
} EVRSummaryType;

تعريفنوع تعداد EVRInputFilterCancelType
{
	EVRInputFilterCancelType_VRInputFilterCancel_Timers = 0,
	EVRInputFilterCancelType_VRInputFilterCancel_Momentum = 1,
} EVRInputFilterCancelType;

تعريفنوع تعداد EVRInput_String_بټونه
{
	EVRInput_String_بټونه_VRInput_String_Hand = 1,
	EVRInput_String_بټونه_VRInput_String_Controller_Type = 2,
	EVRInput_String_بټونه_VRInput_String_ننوت_سرچینه = 4,
	EVRInput_String_بټونه_VRInput_String_All = -1,
} EVRInput_String_بټونه;

تعريفنوع تعداد EIOBufferError
{
	EIOBufferError_IOBuffer_Success = 0,
	EIOBufferError_IOBuffer_OperationFailed = 100,
	EIOBufferError_IOBuffer_InvalidHandle = 101,
	EIOBuffer_Error_IOBuffer_Invalid_دلیل = 102,
	EIOBuffer_Error_IOBuffer_لار_Exists = 103,
	EIOBuffer_Error_IOBuffer_لار_Does_Not_Exist = 104,
	EIOBufferError_IOBuffer_Permission = 105,
} EIOBufferError;

تعريفنوع تعداد EIOBuffer_ډېرپېښ
{
	EIOBuffer_ډېرپېښ_IOBuffer_ډېرپېښ_Read = 1,
	EIOBuffer_ډېرپېښ_IOBuffer_ډېرپېښ_Write = 2,
	EIOBuffer_ډېرپېښ_IOBuffer_ډېرپېښ_Create = 512,
} EIOBuffer_ډېرپېښ;

تعريفنوع تعداد EVRDebugError
{
	EVRDebugError_VRDebugError_Success = 0,
	EVRDebugError_VRDebugError_BadParameter = 1,
} EVRDebugError;

تعريفنوع تعداد EPropertyWriteType
{
	EProperty_Write_Type_Property_Write_سېټ = 0,
	EPropertyWriteType_PropertyWrite_Erase = 1,
	EProperty_Write_Type_Property_Write_سېټ_Error = 2,
} EPropertyWriteType;

تعريفنوع تعداد EBlock_کتار_Error
{
	EBlock_کتار_Error_بلاک_کتار_Error_None = 0,
	EBlock_کتار_Error_بلاک_کتار_Error_کتار_Already_Exists = 1,
	EBlock_کتار_Error_بلاک_کتار_Error_کتار_Not_وموندل = 2,
	EBlock_کتار_Error_بلاک_کتار_Error_بلاک_Not_شته = 3,
	EBlock_کتار_Error_بلاک_کتار_Error_Invalid_Handle = 4,
	EBlock_کتار_Error_بلاک_کتار_Error_Invalid_Param = 5,
	EBlock_کتار_Error_بلاک_کتار_Error_Param_Mismatch = 6,
	EBlock_کتار_Error_بلاک_کتار_Error_دننی_Error = 7,
	EBlock_کتار_Error_بلاک_کتار_Error_Already_Initialized = 8,
	EBlock_کتار_Error_بلاک_کتار_Error_Operation_Is_Server_Only = 9,
	EBlock_کتار_Error_بلاک_کتار_Error_Too_Many_Connections = 10,
} EBlock_کتار_Error;

تعريفنوع تعداد EBlock_کتار_Read_Type
{
	EBlock_کتار_Read_Type_بلاک_کتار_Read_Latest = 0,
	EBlock_کتار_Read_Type_بلاک_کتار_Read_New = 1,
	EBlock_کتار_Read_Type_بلاک_کتار_Read_بل = 2,
} EBlock_کتار_Read_Type;

تعريفنوع تعداد EBlock_کتار_Creation_Flag
{
	EBlock_کتار_Creation_Flag_بلاک_کتار_Flag_Owner_Is_Reader = 1,
} EBlock_کتار_Creation_Flag;


// OpenVR typedefs

تعريفنوع uint32_t Property_Type_نښان_t;
تعريفنوع uint32_t SpatialAnchorHandle_t;
تعريفنوع فراغ * glSharedTextureHandle_t;
تعريفنوع int32_t glInt_t;
تعريفنوع uint32_t glUInt_t;
تعريفنوع uint64_t SharedTextureHandle_t;
تعريفنوع uint32_t DriverId_t;
تعريفنوع uint32_t Tracked_Device_شاخص_t;
تعريفنوع uint64_t WebConsoleHandle_t;
تعريفنوع uint64_t PropertyContainerHandle_t;
تعريفنوع PropertyContainerHandle_t DriverHandle_t;
تعريفنوع uint64_t VRActionHandle_t;
تعريفنوع uint64_t VRAction_سېټ_Handle_t;
تعريفنوع uint64_t VRInput_ارزښت_Handle_t;
تعريفنوع uint32_t VRComponentProperties;
تعريفنوع uint64_t VROverlayHandle_t;
تعريفنوع int32_t Bone_شاخص_t;
تعريفنوع uint64_t TrackedCameraHandle_t;
تعريفنوع uint32_t ScreenshotHandle_t;
تعريفنوع int32_t TextureID_t;
تعريفنوع uint32_t VRNotificationId;
تعريفنوع uint64_t IOBufferHandle_t;
تعريفنوع uint64_t VrProfilerEventHandle_t;
تعريفنوع EVRInitError HmdError;
تعريفنوع EVREye Hmd_Eye;
تعريفنوع EColorSpace ColorSpace;
تعريفنوع ETracking_پایله Hmd_Tracking_پایله;
تعريفنوع ETrackedDeviceClass TrackedDeviceClass;
تعريفنوع ETrackingUniverseOrigin TrackingUniverseOrigin;
تعريفنوع ETrackedDeviceProperty TrackedDeviceProperty;
تعريفنوع ETrackedPropertyError TrackedPropertyError;
تعريفنوع EVRSubmitFlags VRSubmitFlags_t;
تعريفنوع EVRState VRState_t;
تعريفنوع ECollisionBoundsStyle CollisionBoundsStyle_t;
تعريفنوع EVROverlayError VROverlayError;
تعريفنوع EVRFirmwareError VRFirmwareError;
تعريفنوع EVRCompositorError VRCompositorError;
تعريفنوع EVRScreenshotError VRScreenshotsError;
تعريفنوع uint64_t لار_Handle_t;

// OpenVR Structs

تعريفنوع بنية HmdMatrix34_t
{
	عائم m[3][4]; //float[3][4]
} HmdMatrix34_t;

تعريفنوع بنية HmdMatrix33_t
{
	عائم m[3][3]; //float[3][3]
} HmdMatrix33_t;

تعريفنوع بنية HmdMatrix44_t
{
	عائم m[4][4]; //float[4][4]
} HmdMatrix44_t;

تعريفنوع بنية HmdVector3_t
{
	عائم v[3]; //float[3]
} HmdVector3_t;

تعريفنوع بنية HmdVector4_t
{
	عائم v[4]; //float[4]
} HmdVector4_t;

تعريفنوع بنية HmdVector3d_t
{
	مزدوج v[3]; //double[3]
} HmdVector3d_t;

تعريفنوع بنية HmdVector2_t
{
	عائم v[2]; //float[2]
} HmdVector2_t;

تعريفنوع بنية HmdQuaternion_t
{
	مزدوج w;
	مزدوج x;
	مزدوج y;
	مزدوج z;
} HmdQuaternion_t;

تعريفنوع بنية HmdQuaternionf_t
{
	عائم w;
	عائم x;
	عائم y;
	عائم z;
} HmdQuaternionf_t;

تعريفنوع بنية HmdColor_t
{
	عائم r;
	عائم g;
	عائم b;
	عائم a;
} HmdColor_t;

تعريفنوع بنية HmdQuad_t
{
	بنية HmdVector3_t vCorners[4]; //struct vr::HmdVector3_t[4]
} HmdQuad_t;

تعريفنوع بنية HmdRect2_t
{
	بنية HmdVector2_t v_سر_کیڼ;
	بنية HmdVector2_t v_Bottom_ښی;
} HmdRect2_t;

تعريفنوع بنية VRBoneTransform_t
{
	بنية HmdVector4_t position;
	بنية HmdQuaternionf_t orientation;
} VRBoneTransform_t;

تعريفنوع بنية DistortionCoordinates_t
{
	عائم rfRed[2]; //float[2]
	عائم rfGreen[2]; //float[2]
	عائم rfBlue[2]; //float[2]
} DistortionCoordinates_t;

تعريفنوع بنية Texture_t
{
	فراغ * handle; // void *
	تعداد ETextureType eType;
	تعداد EColorSpace eColorSpace;
} Texture_t;

تعريفنوع بنية TrackedDevicePose_t
{
	بنية HmdMatrix34_t m_Device_منزل_Absolute_Tracking;
	بنية HmdVector3_t vVelocity;
	بنية HmdVector3_t vAngularVelocity;
	تعداد ETracking_پایله e_Tracking_پایله;
	bool bPoseIsValid;
	bool bDeviceIsConnected;
} TrackedDevicePose_t;

تعريفنوع بنية VRTextureBounds_t
{
	عائم uMin;
	عائم vMin;
	عائم uMax;
	عائم vMax;
} VRTextureBounds_t;

تعريفنوع بنية VRTextureWithPose_t
{
	فراغ * handle; // void *
	تعداد ETextureType eType;
	تعداد EColorSpace eColorSpace;
	بنية HmdMatrix34_t m_Device_منزل_Absolute_Tracking;
} VRTextureWithPose_t;

تعريفنوع بنية VRTexture_ژوروالی_Info_t
{
	فراغ * handle; // void *
	بنية HmdMatrix44_t mProjection;
	بنية HmdVector2_t vRange;
} VRTexture_ژوروالی_Info_t;

تعريفنوع بنية VRTexture_With_ژوروالی_t
{
	فراغ * handle; // void *
	تعداد ETextureType eType;
	تعداد EColorSpace eColorSpace;
	بنية VRTexture_ژوروالی_Info_t ژوروالی_2;
} VRTexture_With_ژوروالی_t;

تعريفنوع بنية VRTexture_With_Pose_And_ژوروالی_t
{
	فراغ * handle; // void *
	تعداد ETextureType eType;
	تعداد EColorSpace eColorSpace;
	بنية HmdMatrix34_t m_Device_منزل_Absolute_Tracking;
	بنية VRTexture_ژوروالی_Info_t ژوروالی_2;
} VRTexture_With_Pose_And_ژوروالی_t;

تعريفنوع بنية VRVulkan_Texture_معلومات_t
{
	uint64_t m_nImage;
	بنية VkDevice_T * m_pDevice; // struct VkDevice_T *
	بنية VkPhysicalDevice_T * m_pPhysicalDevice; // struct VkPhysicalDevice_T *
	بنية VkInstance_T * m_pInstance; // struct VkInstance_T *
	بنية Vk_کتار_T * m_p_کتار; // struct VkQueue_T *
	uint32_t m_n_کتار_Family_شاخص;
	uint32_t m_n_پلنوالی;
	uint32_t m_n_لوړوالی;
	uint32_t m_nFormat;
	uint32_t m_n_Sample_شمېر;
} VRVulkan_Texture_معلومات_t;

تعريفنوع بنية VRVulkan_Texture_Array_معلومات_t
{
	uint32_t m_un_Array_شاخص;
	uint32_t m_un_Array_اندازه;
} VRVulkan_Texture_Array_معلومات_t;

تعريفنوع بنية D3_D12_Texture_معلومات_t
{
	بنية ID3D12Resource * m_pResource; // struct ID3D12Resource *
	بنية ID3_D12_Command_کتار * m_p_Command_کتار; // struct ID3D12CommandQueue *
	uint32_t m_n_غوټه_ماسک;
} D3_D12_Texture_معلومات_t;

تعريفنوع بنية VREvent_Controller_t
{
	uint32_t button;
} VREvent_Controller_t;

تعريفنوع بنية VREvent_Mouse_t
{
	عائم x;
	عائم y;
	uint32_t button;
} VREvent_Mouse_t;

تعريفنوع بنية VREvent_Scroll_t
{
	عائم xdelta;
	عائم ydelta;
	uint32_t ناکارول_شوی;
	عائم viewportscale;
} VREvent_Scroll_t;

تعريفنوع بنية VREvent_TouchPadMove_t
{
	bool b_Finger_ښکته;
	عائم fl_Seconds_Finger_ښکته;
	عائم f_ارزښت_XFirst;
	عائم f_ارزښت_YFirst;
	عائم f_ارزښت_XRaw;
	عائم f_ارزښت_YRaw;
} VREvent_TouchPadMove_t;

تعريفنوع بنية VREvent_Notification_t
{
	uint64_t ul_User_ارزښت;
	uint32_t notificationId;
} VREvent_Notification_t;

تعريفنوع بنية VREvent_Process_t
{
	uint32_t pid;
	uint32_t oldPid;
	bool bForced;
	bool b_Connection_ورک;
} VREvent_Process_t;

تعريفنوع بنية VREvent_Overlay_t
{
	uint64_t overlayHandle;
	uint64_t device_لار;
	uint64_t حافظه_بلاک_Id;
} VREvent_Overlay_t;

تعريفنوع بنية VREvent_حالت_t
{
	uint32_t حالت_State;
} VREvent_حالت_t;

تعريفنوع بنية VREvent_Keyboard_t
{
	حرف c_New_ننوت[8]; //char[8]
	uint64_t u_User_ارزښت;
} VREvent_Keyboard_t;

تعريفنوع بنية VREvent_Ipd_t
{
	عائم ipdMeters;
} VREvent_Ipd_t;

تعريفنوع بنية VREvent_Chaperone_t
{
	uint64_t m_n_پخوانی_Universe;
	uint64_t m_nCurrentUniverse;
} VREvent_Chaperone_t;

تعريفنوع بنية VREvent_Reserved_t
{
	uint64_t reserved0;
	uint64_t reserved1;
	uint64_t reserved2;
	uint64_t reserved3;
	uint64_t reserved4;
	uint64_t reserved5;
} VREvent_Reserved_t;

تعريفنوع بنية VREvent_PerformanceTest_t
{
	uint32_t m_nFidelityLevel;
} VREvent_PerformanceTest_t;

تعريفنوع بنية VREvent_SeatedZeroPoseReset_t
{
	bool bResetBySystemMenu;
} VREvent_SeatedZeroPoseReset_t;

تعريفنوع بنية VREvent_Screenshot_t
{
	uint32_t handle;
	uint32_t type;
} VREvent_Screenshot_t;

تعريفنوع بنية VREvent_Screenshot_پرمختګ_t
{
	عائم پرمختګ_2;
} VREvent_Screenshot_پرمختګ_t;

تعريفنوع بنية VREvent_ApplicationLaunch_t
{
	uint32_t pid;
	uint32_t un_دلیلونه_Handle;
} VREvent_ApplicationLaunch_t;

تعريفنوع بنية VREvent_EditingCameraSurface_t
{
	uint64_t overlayHandle;
	uint32_t n_Visual_ډېرپېښ;
} VREvent_EditingCameraSurface_t;

تعريفنوع بنية VREvent_پیغام_Overlay_t
{
	uint32_t unVRMessageOverlayResponse;
} VREvent_پیغام_Overlay_t;

تعريفنوع بنية VREvent_Property_t
{
	PropertyContainerHandle_t container;
	تعداد ETrackedDeviceProperty prop;
} VREvent_Property_t;

تعريفنوع بنية VREvent_HapticVibration_t
{
	uint64_t containerHandle;
	uint64_t componentHandle;
	عائم fDurationSeconds;
	عائم fFrequency;
	عائم fAmplitude;
} VREvent_HapticVibration_t;

تعريفنوع بنية VREvent_WebConsole_t
{
	WebConsoleHandle_t webConsoleHandle;
} VREvent_WebConsole_t;

تعريفنوع بنية VREvent_ننوت_Binding_بارول_t
{
	PropertyContainerHandle_t ulAppContainer;
	uint64_t لار_پیغام;
	uint64_t لار_Url;
	uint64_t لار_Controller_Type;
} VREvent_ننوت_Binding_بارول_t;

تعريفنوع بنية VREvent_ننوت_Action_Manifest_بارول_t
{
	uint64_t لار_App_کلی;
	uint64_t لار_پیغام;
	uint64_t لار_پیغام_Param;
	uint64_t لار_Manifest_لار;
} VREvent_ننوت_Action_Manifest_بارول_t;

تعريفنوع بنية VREvent_SpatialAnchor_t
{
	SpatialAnchorHandle_t unHandle;
} VREvent_SpatialAnchor_t;

تعريفنوع بنية VREvent_پرمختګ_Update_t
{
	uint64_t ulApplicationPropertyContainer;
	uint64_t لار_Device;
	uint64_t لار_ننوت_سرچینه;
	uint64_t لار_پرمختګ_Action;
	uint64_t لار_Icon;
	عائم f_پرمختګ;
} VREvent_پرمختګ_Update_t;

تعريفنوع بنية VREvent_ShowUI_t
{
	تعداد EShowUIType eType;
} VREvent_ShowUI_t;

تعريفنوع بنية VREvent_ShowDevTools_t
{
	int32_t nBrowserIdentifier;
} VREvent_ShowDevTools_t;

تعريفنوع بنية VREvent_HDCPError_t
{
	تعداد EHDCPError e_کوډ;
} VREvent_HDCPError_t;

تعريفنوع بنية RenderModel_ComponentState_t
{
	بنية HmdMatrix34_t m_Tracking_منزل_Component_Render_Model;
	بنية HmdMatrix34_t m_Tracking_منزل_Component_Local;
	VRComponentProperties uProperties;
} RenderModel_ComponentState_t;

تعريفنوع بنية HiddenAreaMesh_t
{
	بنية HmdVector2_t * p_راس_معلومات; // const struct vr::HmdVector2_t *
	uint32_t un_Triangle_شمېر;
} HiddenAreaMesh_t;

تعريفنوع بنية VRControllerAxis_t
{
	عائم x;
	عائم y;
} VRControllerAxis_t;

تعريفنوع بنية VRControllerState_t
{
	uint32_t un_Packet_عدد;
	uint64_t ulButtonPressed;
	uint64_t ulButtonTouched;
	بنية VRControllerAxis_t rAxis[5]; //struct vr::VRControllerAxis_t[5]
} VRControllerState_t;

تعريفنوع بنية Camera_Video_بهیر_چوکاټ_سرلیک_t
{
	تعداد EVRTracked_Camera_چوکاټ_Type e_چوکاټ_Type;
	uint32_t n_پلنوالی;
	uint32_t n_لوړوالی;
	uint32_t n_بایټونه_فی_Pixel;
	uint32_t n_چوکاټ_Sequence;
	بنية TrackedDevicePose_t trackedDevicePose;
	uint64_t ul_چوکاټ_Exposure_وخت;
} Camera_Video_بهیر_چوکاټ_سرلیک_t;

تعريفنوع بنية Compositor_چوکاټ_Timing
{
	uint32_t m_n_اندازه;
	uint32_t m_n_چوکاټ_شاخص;
	uint32_t m_n_عدد_چوکاټ_Presents;
	uint32_t m_n_عدد_Mis_Presented;
	uint32_t m_n_عدد_Dropped_چوکاټونه;
	uint32_t m_nReprojectionFlags;
	مزدوج m_fl_System_وخت_دننه_Seconds;
	عائم m_flPreSubmitGpuMs;
	عائم m_flPostSubmitGpuMs;
	عائم m_fl_ټول_Render_Gpu_Ms;
	عائم m_flCompositorRenderGpuMs;
	عائم m_flCompositorRenderCpuMs;
	عائم m_flCompositorIdleCpuMs;
	عائم m_fl_Client_چوکاټ_Interval_Ms;
	عائم m_flPresentCallCpuMs;
	عائم m_flWaitForPresentCpuMs;
	عائم m_fl_Submit_چوکاټ_Ms;
	عائم m_flWaitGetPosesCalledMs;
	عائم m_flNewPosesReadyMs;
	عائم m_fl_New_چوکاټ_Ready_Ms;
	عائم m_fl_Compositor_Update_پیل_Ms;
	عائم m_fl_Compositor_Update_پای_ټکی_Ms;
	عائم m_fl_Compositor_Render_پیل_Ms;
	TrackedDevicePose_t m_HmdPose;
	uint32_t m_n_عدد_VSyncs_Ready_For_Use;
	uint32_t m_n_عدد_VSyncs_منزل_لومړی_View;
} Compositor_چوکاټ_Timing;

تعريفنوع بنية Compositor_BenchmarkResults
{
	عائم m_fl_Mega_Pixels_فی_دوهم;
	عائم m_fl_Hmd_Recommended_Mega_Pixels_فی_دوهم;
} Compositor_BenchmarkResults;

تعريفنوع بنية Driver_مستقیم_ډېرپېښ_چوکاټ_Timing
{
	uint32_t m_n_اندازه;
	uint32_t m_n_عدد_چوکاټ_Presents;
	uint32_t m_n_عدد_Mis_Presented;
	uint32_t m_n_عدد_Dropped_چوکاټونه;
	uint32_t m_nReprojectionFlags;
} Driver_مستقیم_ډېرپېښ_چوکاټ_Timing;

تعريفنوع بنية ImuSample_t
{
	مزدوج f_Sample_وخت;
	بنية HmdVector3d_t vAccel;
	بنية HmdVector3d_t vGyro;
	uint32_t unOffScaleFlags;
} ImuSample_t;

تعريفنوع بنية App_Override_کلیګانې_t
{
	حرف * pch_کلی; // const char *
	حرف * pch_ارزښت; // const char *
} App_Override_کلیګانې_t;

تعريفنوع بنية Compositor_CumulativeStats
{
	uint32_t m_nPid;
	uint32_t m_n_عدد_چوکاټ_Presents;
	uint32_t m_n_عدد_Dropped_چوکاټونه;
	uint32_t m_n_عدد_Reprojected_چوکاټونه;
	uint32_t m_n_عدد_چوکاټ_Presents_On_Startup;
	uint32_t m_n_عدد_Dropped_چوکاټونه_On_Startup;
	uint32_t m_n_عدد_Reprojected_چوکاټونه_On_Startup;
	uint32_t m_n_عدد_Loading;
	uint32_t m_n_عدد_چوکاټ_Presents_Loading;
	uint32_t m_n_عدد_Dropped_چوکاټونه_Loading;
	uint32_t m_n_عدد_Reprojected_چوکاټونه_Loading;
	uint32_t m_n_عدد_Timed_بهر;
	uint32_t m_n_عدد_چوکاټ_Presents_Timed_بهر;
	uint32_t m_n_عدد_Dropped_چوکاټونه_Timed_بهر;
	uint32_t m_n_عدد_Reprojected_چوکاټونه_Timed_بهر;
	uint32_t m_n_عدد_چوکاټ_Submits;
	مزدوج m_fl_مجموعه_Compositor_CPUTime_MS;
	مزدوج m_fl_مجموعه_Compositor_GPUTime_MS;
	مزدوج m_fl_مجموعه_موخه_چوکاټ_Times;
	مزدوج m_fl_مجموعه_Application_CPUTime_MS;
	مزدوج m_fl_مجموعه_Application_GPUTime_MS;
} Compositor_CumulativeStats;

تعريفنوع بنية Compositor_StageRenderSettings
{
	بنية HmdColor_t m_PrimaryColor;
	بنية HmdColor_t m_SecondaryColor;
	عائم m_flVignetteInnerRadius;
	عائم m_flVignetteOuterRadius;
	عائم m_flFresnelStrength;
	bool m_bBackfaceCulling;
	bool m_bGreyscale;
	bool m_bWireframe;
} Compositor_StageRenderSettings;

تعريفنوع بنية VROverlayIntersectionParams_t
{
	بنية HmdVector3_t v_سرچینه;
	بنية HmdVector3_t vDirection;
	تعداد ETrackingUniverseOrigin eOrigin;
} VROverlayIntersectionParams_t;

تعريفنوع بنية VROverlayIntersectionResults_t
{
	بنية HmdVector3_t v_ټکی;
	بنية HmdVector3_t v_نورمال;
	بنية HmdVector2_t vUVs;
	عائم f_واټن;
} VROverlayIntersectionResults_t;

تعريفنوع بنية Intersection_ماسک_Rectangle_t
{
	عائم m_fl_سر_کیڼ_X;
	عائم m_fl_سر_کیڼ_Y;
	عائم m_fl_پلنوالی;
	عائم m_fl_لوړوالی;
} Intersection_ماسک_Rectangle_t;

تعريفنوع بنية Intersection_ماسک_Circle_t
{
	عائم m_flCenterX;
	عائم m_flCenterY;
	عائم m_flRadius;
} Intersection_ماسک_Circle_t;

تعريفنوع بنية VROverlayProjection_t
{
	عائم f_کیڼ;
	عائم f_ښی;
	عائم f_سر;
	عائم fBottom;
} VROverlayProjection_t;

تعريفنوع بنية VROverlayView_t
{
	VROverlayHandle_t overlayHandle;
	بنية Texture_t texture;
	بنية VRTextureBounds_t textureBounds;
} VROverlayView_t;

تعريفنوع بنية VRVulkanDevice_t
{
	بنية VkInstance_T * m_pInstance; // struct VkInstance_T *
	بنية VkDevice_T * m_pDevice; // struct VkDevice_T *
	بنية VkPhysicalDevice_T * m_pPhysicalDevice; // struct VkPhysicalDevice_T *
	بنية Vk_کتار_T * m_p_کتار; // struct VkQueue_T *
	uint32_t m_u_کتار_Family_شاخص;
} VRVulkanDevice_t;

تعريفنوع بنية VRNativeDevice_t
{
	فراغ * handle; // void *
	تعداد EDeviceType eType;
} VRNativeDevice_t;

تعريفنوع بنية Render_Model_راس_t
{
	بنية HmdVector3_t vPosition;
	بنية HmdVector3_t v_نورمال;
	عائم rfTextureCoord[2]; //float[2]
} Render_Model_راس_t;

#إذا defined(__linux__) || defined(__APPLE__)
#لارښوونه pack( ټېل, 4 )
#د_که_پای
تعريفنوع بنية RenderModel_TextureMap_t
{
	uint16_t un_پلنوالی;
	uint16_t un_لوړوالی;
	uint8_t * rub_Texture_Map_معلومات; // const uint8_t *
	تعداد EVRRenderModelTextureFormat format;
	uint16_t un_Mip_پوړونه;
} RenderModel_TextureMap_t;

#إذا defined(__linux__) || defined(__APPLE__)
#لارښوونه pack( راوباسه )
#د_که_پای
#إذا defined(__linux__) || defined(__APPLE__)
#لارښوونه pack( ټېل, 4 )
#د_که_پای
تعريفنوع بنية RenderModel_t
{
	بنية Render_Model_راس_t * r_راس_معلومات; // const struct vr::RenderModel_Vertex_t *
	uint32_t un_راس_شمېر;
	uint16_t * r_شاخص_معلومات; // const uint16_t *
	uint32_t un_Triangle_شمېر;
	TextureID_t diffuseTextureId;
} RenderModel_t;

#إذا defined(__linux__) || defined(__APPLE__)
#لارښوونه pack( راوباسه )
#د_که_پای
تعريفنوع بنية Render_Model_Controller_ډېرپېښ_State_t
{
	bool bScrollWheelVisible;
} Render_Model_Controller_ډېرپېښ_State_t;

تعريفنوع بنية NotificationBitmap_t
{
	فراغ * m_p_Image_معلومات; // void *
	int32_t m_n_پلنوالی;
	int32_t m_n_لوړوالی;
	int32_t m_n_بایټونه_فی_Pixel;
} NotificationBitmap_t;

تعريفنوع بنية CVRSettingHelper
{
	intptr_t m_pSettings; // class vr::IVRSettings *
} CVRSettingHelper;

تعريفنوع بنية ننوت_Analog_Action_معلومات_t
{
	bool b_فعال;
	VRInput_ارزښت_Handle_t فعال_Origin;
	عائم x;
	عائم y;
	عائم z;
	عائم deltaX;
	عائم deltaY;
	عائم deltaZ;
	عائم f_Update_وخت;
} ننوت_Analog_Action_معلومات_t;

تعريفنوع بنية ننوت_Digital_Action_معلومات_t
{
	bool b_فعال;
	VRInput_ارزښت_Handle_t فعال_Origin;
	bool bState;
	bool b_بدل_شوی;
	عائم f_Update_وخت;
} ننوت_Digital_Action_معلومات_t;

تعريفنوع بنية ننوت_Pose_Action_معلومات_t
{
	bool b_فعال;
	VRInput_ارزښت_Handle_t فعال_Origin;
	بنية TrackedDevicePose_t pose;
} ننوت_Pose_Action_معلومات_t;

تعريفنوع بنية ننوت_Skeletal_Action_معلومات_t
{
	bool b_فعال;
	VRInput_ارزښت_Handle_t فعال_Origin;
} ننوت_Skeletal_Action_معلومات_t;

تعريفنوع بنية ننوت_Origin_Info_t
{
	VRInput_ارزښت_Handle_t device_لار;
	Tracked_Device_شاخص_t tracked_Device_شاخص;
	حرف rchRenderModelComponentName[128]; //char[128]
} ننوت_Origin_Info_t;

تعريفنوع بنية ننوت_Binding_Info_t
{
	حرف rch_Device_لار_Name[128]; //char[128]
	حرف rch_ننوت_لار_Name[128]; //char[128]
	حرف rch_ډېرپېښ_Name[128]; //char[128]
	حرف rch_خونه_Name[128]; //char[128]
	حرف rch_ننوت_سرچینه_Type[32]; //char[32]
} ننوت_Binding_Info_t;

تعريفنوع بنية VRActive_Action_سېټ_t
{
	VRAction_سېټ_Handle_t ul_Action_سېټ;
	VRInput_ارزښت_Handle_t ul_Restricted_منزل_Device;
	VRAction_سېټ_Handle_t ul_Secondary_Action_سېټ;
	uint32_t unPadding;
	int32_t n_لومړیتوب;
} VRActive_Action_سېټ_t;

تعريفنوع بنية VRSkeletal_Summary_معلومات_t
{
	عائم flFingerCurl[5]; //float[5]
	عائم flFingerSplay[4]; //float[4]
} VRSkeletal_Summary_معلومات_t;

تعريفنوع بنية SpatialAnchorPose_t
{
	بنية HmdMatrix34_t m_Anchor_منزل_Absolute_Tracking;
} SpatialAnchorPose_t;

تعريفنوع بنية COpenVRContext
{
	intptr_t m_pVRSystem; // class vr::IVRSystem *
	intptr_t m_pVRChaperone; // class vr::IVRChaperone *
	intptr_t m_p_VRChaperone_تیاری; // class vr::IVRChaperoneSetup *
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

تعريفنوع بنية PropertyWrite_t
{
	تعداد ETrackedDeviceProperty prop;
	تعداد EPropertyWriteType writeType;
	تعداد ETrackedPropertyError e_سېټ_Error;
	فراغ * pv_بفر; // void *
	uint32_t un_بفر_اندازه;
	Property_Type_نښان_t un_نښان;
	تعداد ETrackedPropertyError eError;
} PropertyWrite_t;

تعريفنوع بنية PropertyRead_t
{
	تعداد ETrackedDeviceProperty prop;
	فراغ * pv_بفر; // void *
	uint32_t un_بفر_اندازه;
	Property_Type_نښان_t un_نښان;
	uint32_t un_Required_بفر_اندازه;
	تعداد ETrackedPropertyError eError;
} PropertyRead_t;

تعريفنوع بنية CVRPropertyHelpers
{
	intptr_t m_pProperties; // class vr::IVRProperties *
} CVRPropertyHelpers;

تعريفنوع بنية لار_Write_t
{
	لار_Handle_t ul_لار;
	تعداد EPropertyWriteType writeType;
	تعداد ETrackedPropertyError e_سېټ_Error;
	فراغ * pv_بفر; // void *
	uint32_t un_بفر_اندازه;
	Property_Type_نښان_t un_نښان;
	تعداد ETrackedPropertyError eError;
	حرف * psz_لار; // const char *
} لار_Write_t;

تعريفنوع بنية لار_Read_t
{
	لار_Handle_t ul_لار;
	فراغ * pv_بفر; // void *
	uint32_t un_بفر_اندازه;
	Property_Type_نښان_t un_نښان;
	uint32_t un_Required_بفر_اندازه;
	تعداد ETrackedPropertyError eError;
	حرف * psz_لار; // const char *
} لار_Read_t;


تعريفنوع اتحاد
{
	VREvent_Reserved_t reserved;
	VREvent_Controller_t controller;
	VREvent_Mouse_t mouse;
	VREvent_Scroll_t scroll;
	VREvent_Process_t process;
	VREvent_Notification_t notification;
	VREvent_Overlay_t overlay;
	VREvent_حالت_t حالت;
	VREvent_Keyboard_t keyboard;
	VREvent_Ipd_t ipd;
	VREvent_Chaperone_t chaperone;
	VREvent_PerformanceTest_t performanceTest;
	VREvent_TouchPadMove_t touchPadMove;
	VREvent_SeatedZeroPoseReset_t seatedZeroPoseReset;
	VREvent_Screenshot_t screenshot;
	VREvent_Screenshot_پرمختګ_t screenshot_پرمختګ;
	VREvent_ApplicationLaunch_t applicationLaunch;
	VREvent_EditingCameraSurface_t cameraSurface;
	VREvent_پیغام_Overlay_t پیغام_Overlay;
	VREvent_Property_t property;
	VREvent_HapticVibration_t hapticVibration;
	VREvent_WebConsole_t webConsole;
	VREvent_ننوت_Binding_بارول_t ننوت_Binding;
	VREvent_ننوت_Action_Manifest_بارول_t actionManifest;
	VREvent_SpatialAnchor_t spatialAnchor;
} VREvent_معلومات_t;

#إذا defined(__linux__) || defined(__APPLE__) 
// This structure was originally defined mis-packed on Linux, preserved for 
// compatibility. 
#لارښوونه pack( ټېل, 4 )
#د_که_پای

/** An event posted by the server to all running applications */
بنية VREvent_t
{
	uint32_t eventType; // EVREventType enum
	Tracked_Device_شاخص_t tracked_Device_شاخص;
	عائم eventAgeSeconds;
	// event data must be the end of the struct as its size is variable
	VREvent_معلومات_t معلومات;
};

#إذا defined(__linux__) || defined(__APPLE__) 
#لارښوونه pack( راوباسه )
#د_که_پای


تعريفنوع اتحاد
{
	Intersection_ماسک_Rectangle_t m_Rectangle;
	Intersection_ماسک_Circle_t m_Circle;
} VROverlay_Intersection_ماسک_Primitive_معلومات_t;

بنية VROverlay_Intersection_ماسک_Primitive_t
{
	EVROverlay_Intersection_ماسک_Primitive_Type m_nPrimitiveType;
	VROverlay_Intersection_ماسک_Primitive_معلومات_t m_Primitive;
};


// OpenVR Function Pointer Tables

بنية VR_IVRSystem_Fn_جدول
{
	فراغ (OPENVR_FNTABLE_CALLTYPE *Get_Recommended_Render_موخه_اندازه)(uint32_t * pn_پلنوالی, uint32_t * pn_لوړوالی);
	بنية HmdMatrix44_t (OPENVR_FNTABLE_CALLTYPE *Get_Projection_ماتریکس)(EVREye eEye, عائم fNearZ, عائم fFarZ);
	فراغ (OPENVR_FNTABLE_CALLTYPE *GetProjectionRaw)(EVREye eEye, عائم * pf_کیڼ, عائم * pf_ښی, عائم * pf_سر, عائم * pfBottom);
	bool (OPENVR_FNTABLE_CALLTYPE *ComputeDistortion)(EVREye eEye, عائم fU, عائم fV, بنية DistortionCoordinates_t * pDistortionCoordinates);
	بنية HmdMatrix34_t (OPENVR_FNTABLE_CALLTYPE *Get_Eye_منزل_سر_Transform)(EVREye eEye);
	bool (OPENVR_FNTABLE_CALLTYPE *Get_وخت_Since_وروستی_Vsync)(عائم * pf_Seconds_Since_وروستی_Vsync, uint64_t * pul_چوکاټ_Counter);
	int32_t (OPENVR_FNTABLE_CALLTYPE *Get_D3_D9_Adapter_شاخص)();
	فراغ (OPENVR_FNTABLE_CALLTYPE *GetDXGIOutputInfo)(int32_t * pn_Adapter_شاخص);
	فراغ (OPENVR_FNTABLE_CALLTYPE *GetOutputDevice)(uint64_t * pnDevice, ETextureType textureType, بنية VkInstance_T * pInstance);
	bool (OPENVR_FNTABLE_CALLTYPE *IsDisplayOnDesktop)();
	bool (OPENVR_FNTABLE_CALLTYPE *سېټ_Display_Visibility)(bool bIsVisibleOnDesktop);
	فراغ (OPENVR_FNTABLE_CALLTYPE *Get_Device_منزل_Absolute_Tracking_Pose)(ETrackingUniverseOrigin eOrigin, عائم f_Predicted_Seconds_منزل_Photons_From_Now, بنية TrackedDevicePose_t * pTrackedDevicePoseArray, uint32_t un_Tracked_Device_Pose_Array_شمېر);
	بنية HmdMatrix34_t (OPENVR_FNTABLE_CALLTYPE *Get_Seated_Zero_Pose_منزل_Standing_Absolute_Tracking_Pose)();
	بنية HmdMatrix34_t (OPENVR_FNTABLE_CALLTYPE *Get_Raw_Zero_Pose_منزل_Standing_Absolute_Tracking_Pose)();
	uint32_t (OPENVR_FNTABLE_CALLTYPE *Get_Sorted_Tracked_Device_Indices_د_Class)(ETrackedDeviceClass eTrackedDeviceClass, Tracked_Device_شاخص_t * pun_Tracked_Device_شاخص_Array, uint32_t un_Tracked_Device_شاخص_Array_شمېر, Tracked_Device_شاخص_t un_Relative_منزل_Tracked_Device_شاخص);
	EDeviceActivityLevel (OPENVR_FNTABLE_CALLTYPE *GetTrackedDeviceActivityLevel)(Tracked_Device_شاخص_t unDeviceId);
	فراغ (OPENVR_FNTABLE_CALLTYPE *ApplyTransform)(بنية TrackedDevicePose_t * pOutputPose, بنية TrackedDevicePose_t * pTrackedDevicePose, بنية HmdMatrix34_t * pTransform);
	Tracked_Device_شاخص_t (OPENVR_FNTABLE_CALLTYPE *Get_Tracked_Device_شاخص_For_Controller_Role)(ETrackedControllerRole unDeviceType);
	ETrackedControllerRole (OPENVR_FNTABLE_CALLTYPE *Get_Controller_Role_For_Tracked_Device_شاخص)(Tracked_Device_شاخص_t un_Device_شاخص);
	ETrackedDeviceClass (OPENVR_FNTABLE_CALLTYPE *GetTrackedDeviceClass)(Tracked_Device_شاخص_t un_Device_شاخص);
	bool (OPENVR_FNTABLE_CALLTYPE *IsTrackedDeviceConnected)(Tracked_Device_شاخص_t un_Device_شاخص);
	bool (OPENVR_FNTABLE_CALLTYPE *GetBoolTrackedDeviceProperty)(Tracked_Device_شاخص_t un_Device_شاخص, ETrackedDeviceProperty prop, ETrackedPropertyError * pError);
	عائم (OPENVR_FNTABLE_CALLTYPE *GetFloatTrackedDeviceProperty)(Tracked_Device_شاخص_t un_Device_شاخص, ETrackedDeviceProperty prop, ETrackedPropertyError * pError);
	int32_t (OPENVR_FNTABLE_CALLTYPE *GetInt32TrackedDeviceProperty)(Tracked_Device_شاخص_t un_Device_شاخص, ETrackedDeviceProperty prop, ETrackedPropertyError * pError);
	uint64_t (OPENVR_FNTABLE_CALLTYPE *GetUint64TrackedDeviceProperty)(Tracked_Device_شاخص_t un_Device_شاخص, ETrackedDeviceProperty prop, ETrackedPropertyError * pError);
	بنية HmdMatrix34_t (OPENVR_FNTABLE_CALLTYPE *GetMatrix34TrackedDeviceProperty)(Tracked_Device_شاخص_t un_Device_شاخص, ETrackedDeviceProperty prop, ETrackedPropertyError * pError);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetArrayTrackedDeviceProperty)(Tracked_Device_شاخص_t un_Device_شاخص, ETrackedDeviceProperty prop, Property_Type_نښان_t propType, فراغ * p_بفر, uint32_t un_بفر_اندازه, ETrackedPropertyError * pError);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetStringTrackedDeviceProperty)(Tracked_Device_شاخص_t un_Device_شاخص, ETrackedDeviceProperty prop, حرف * pch_ارزښت, uint32_t un_بفر_اندازه, ETrackedPropertyError * pError);
	حرف * (OPENVR_FNTABLE_CALLTYPE *GetPropErrorNameFromEnum)(ETrackedPropertyError error);
	bool (OPENVR_FNTABLE_CALLTYPE *Poll_بل_Event)(بنية VREvent_t * pEvent, uint32_t uncbVREvent);
	bool (OPENVR_FNTABLE_CALLTYPE *Poll_بل_Event_With_Pose)(ETrackingUniverseOrigin eOrigin, بنية VREvent_t * pEvent, uint32_t uncbVREvent, TrackedDevicePose_t * pTrackedDevicePose);
	حرف * (OPENVR_FNTABLE_CALLTYPE *GetEventTypeNameFromEnum)(EVREventType eType);
	بنية HiddenAreaMesh_t (OPENVR_FNTABLE_CALLTYPE *GetHiddenAreaMesh)(EVREye eEye, EHiddenAreaMeshType type);
	bool (OPENVR_FNTABLE_CALLTYPE *GetControllerState)(Tracked_Device_شاخص_t un_Controller_Device_شاخص, VRControllerState_t * pControllerState, uint32_t un_Controller_State_اندازه);
	bool (OPENVR_FNTABLE_CALLTYPE *GetControllerStateWithPose)(ETrackingUniverseOrigin eOrigin, Tracked_Device_شاخص_t un_Controller_Device_شاخص, VRControllerState_t * pControllerState, uint32_t un_Controller_State_اندازه, بنية TrackedDevicePose_t * pTrackedDevicePose);
	فراغ (OPENVR_FNTABLE_CALLTYPE *TriggerHapticPulse)(Tracked_Device_شاخص_t un_Controller_Device_شاخص, uint32_t unAxisId, بینښه لنډ usDurationMicroSec);
	حرف * (OPENVR_FNTABLE_CALLTYPE *GetButtonIdNameFromEnum)(EVRButtonId eButtonId);
	حرف * (OPENVR_FNTABLE_CALLTYPE *GetControllerAxisTypeNameFromEnum)(EVRControllerAxisType eAxisType);
	bool (OPENVR_FNTABLE_CALLTYPE *Is_ننوت_شته)();
	bool (OPENVR_FNTABLE_CALLTYPE *IsSteamVRDrawingControllers)();
	bool (OPENVR_FNTABLE_CALLTYPE *ShouldApplicationPause)();
	bool (OPENVR_FNTABLE_CALLTYPE *ShouldApplicationReduceRenderingWork)();
	EVRFirmwareError (OPENVR_FNTABLE_CALLTYPE *PerformFirmwareUpdate)(Tracked_Device_شاخص_t un_Device_شاخص);
	فراغ (OPENVR_FNTABLE_CALLTYPE *AcknowledgeQuit_Exiting)();
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetAppContainerFilePaths)(حرف * pch_بفر, uint32_t un_بفر_اندازه);
	حرف * (OPENVR_FNTABLE_CALLTYPE *Get_Runtime_نسخه)();
};

بنية VR_IVRExtended_Display_Fn_جدول
{
	فراغ (OPENVR_FNTABLE_CALLTYPE *Get_کړکۍ_Bounds)(int32_t * pnX, int32_t * pnY, uint32_t * pn_پلنوالی, uint32_t * pn_لوړوالی);
	فراغ (OPENVR_FNTABLE_CALLTYPE *GetEyeOutputViewport)(EVREye eEye, uint32_t * pnX, uint32_t * pnY, uint32_t * pn_پلنوالی, uint32_t * pn_لوړوالی);
	فراغ (OPENVR_FNTABLE_CALLTYPE *GetDXGIOutputInfo)(int32_t * pn_Adapter_شاخص, int32_t * pn_Adapter_Output_شاخص);
};

بنية VR_IVRTracked_Camera_Fn_جدول
{
	حرف * (OPENVR_FNTABLE_CALLTYPE *GetCameraErrorNameFromEnum)(EVRTrackedCameraError eCameraError);
	EVRTrackedCameraError (OPENVR_FNTABLE_CALLTYPE *HasCamera)(Tracked_Device_شاخص_t n_Device_شاخص, bool * pHasCamera);
	EVRTrackedCameraError (OPENVR_FNTABLE_CALLTYPE *Get_Camera_چوکاټ_اندازه)(Tracked_Device_شاخص_t n_Device_شاخص, EVRTracked_Camera_چوکاټ_Type e_چوکاټ_Type, uint32_t * pn_پلنوالی, uint32_t * pn_لوړوالی, uint32_t * pn_چوکاټ_بفر_اندازه);
	EVRTrackedCameraError (OPENVR_FNTABLE_CALLTYPE *GetCameraIntrinsics)(Tracked_Device_شاخص_t n_Device_شاخص, uint32_t n_Camera_شاخص, EVRTracked_Camera_چوکاټ_Type e_چوکاټ_Type, HmdVector2_t * p_Focal_اوږدتیا, HmdVector2_t * pCenter);
	EVRTrackedCameraError (OPENVR_FNTABLE_CALLTYPE *GetCameraProjection)(Tracked_Device_شاخص_t n_Device_شاخص, uint32_t n_Camera_شاخص, EVRTracked_Camera_چوکاټ_Type e_چوکاټ_Type, عائم flZNear, عائم flZFar, HmdMatrix44_t * pProjection);
	EVRTrackedCameraError (OPENVR_FNTABLE_CALLTYPE *AcquireVideoStreamingService)(Tracked_Device_شاخص_t n_Device_شاخص, TrackedCameraHandle_t * pHandle);
	EVRTrackedCameraError (OPENVR_FNTABLE_CALLTYPE *ReleaseVideoStreamingService)(TrackedCameraHandle_t hTrackedCamera);
	EVRTrackedCameraError (OPENVR_FNTABLE_CALLTYPE *Get_Video_بهیر_چوکاټ_بفر)(TrackedCameraHandle_t hTrackedCamera, EVRTracked_Camera_چوکاټ_Type e_چوکاټ_Type, فراغ * p_چوکاټ_بفر, uint32_t n_چوکاټ_بفر_اندازه, Camera_Video_بهیر_چوکاټ_سرلیک_t * p_چوکاټ_سرلیک, uint32_t n_چوکاټ_سرلیک_اندازه);
	EVRTrackedCameraError (OPENVR_FNTABLE_CALLTYPE *Get_Video_بهیر_Texture_اندازه)(Tracked_Device_شاخص_t n_Device_شاخص, EVRTracked_Camera_چوکاټ_Type e_چوکاټ_Type, VRTextureBounds_t * pTextureBounds, uint32_t * pn_پلنوالی, uint32_t * pn_لوړوالی);
	EVRTrackedCameraError (OPENVR_FNTABLE_CALLTYPE *Get_Video_بهیر_Texture_D3_D11)(TrackedCameraHandle_t hTrackedCamera, EVRTracked_Camera_چوکاټ_Type e_چوکاټ_Type, فراغ * pD3D11DeviceOrResource, فراغ ** ppD3D11ShaderResourceView, Camera_Video_بهیر_چوکاټ_سرلیک_t * p_چوکاټ_سرلیک, uint32_t n_چوکاټ_سرلیک_اندازه);
	EVRTrackedCameraError (OPENVR_FNTABLE_CALLTYPE *Get_Video_بهیر_Texture_GL)(TrackedCameraHandle_t hTrackedCamera, EVRTracked_Camera_چوکاټ_Type e_چوکاټ_Type, glUInt_t * pglTextureId, Camera_Video_بهیر_چوکاټ_سرلیک_t * p_چوکاټ_سرلیک, uint32_t n_چوکاټ_سرلیک_اندازه);
	EVRTrackedCameraError (OPENVR_FNTABLE_CALLTYPE *Release_Video_بهیر_Texture_GL)(TrackedCameraHandle_t hTrackedCamera, glUInt_t glTextureId);
	فراغ (OPENVR_FNTABLE_CALLTYPE *سېټ_Camera_Tracking_Space)(ETrackingUniverseOrigin eUniverse);
	ETrackingUniverseOrigin (OPENVR_FNTABLE_CALLTYPE *GetCameraTrackingSpace)();
};

بنية VR_IVRApplications_Fn_جدول
{
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *جمع_کړه_Application_Manifest)(حرف * pch_Application_Manifest_ډک_لار, bool bTemporary);
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *RemoveApplicationManifest)(حرف * pch_Application_Manifest_ډک_لار);
	bool (OPENVR_FNTABLE_CALLTYPE *IsApplicationInstalled)(حرف * pch_App_کلی);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *Get_Application_شمېر)();
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *Get_Application_کلی_By_شاخص)(uint32_t un_Application_شاخص, حرف * pch_App_کلی_بفر, uint32_t un_App_کلی_بفر_Len);
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *Get_Application_کلی_By_Process_Id)(uint32_t unProcessId, حرف * pch_App_کلی_بفر, uint32_t un_App_کلی_بفر_Len);
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *LaunchApplication)(حرف * pch_App_کلی);
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *LaunchTemplateApplication)(حرف * pch_Template_App_کلی, حرف * pch_New_App_کلی, بنية App_Override_کلیګانې_t * p_کلیګانې, uint32_t un_کلیګانې);
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *LaunchApplicationFromMimeType)(حرف * pchMimeType, حرف * pch_دلیلونه);
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *LaunchDashboardOverlay)(حرف * pch_App_کلی);
	bool (OPENVR_FNTABLE_CALLTYPE *CancelApplicationLaunch)(حرف * pch_App_کلی);
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *IdentifyApplication)(uint32_t unProcessId, حرف * pch_App_کلی);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetApplicationProcessId)(حرف * pch_App_کلی);
	حرف * (OPENVR_FNTABLE_CALLTYPE *GetApplicationsErrorNameFromEnum)(EVRApplicationError error);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetApplicationPropertyString)(حرف * pch_App_کلی, EVRApplicationProperty eProperty, حرف * pch_Property_ارزښت_بفر, uint32_t un_Property_ارزښت_بفر_Len, EVRApplicationError * peError);
	bool (OPENVR_FNTABLE_CALLTYPE *GetApplicationPropertyBool)(حرف * pch_App_کلی, EVRApplicationProperty eProperty, EVRApplicationError * peError);
	uint64_t (OPENVR_FNTABLE_CALLTYPE *GetApplicationPropertyUint64)(حرف * pch_App_کلی, EVRApplicationProperty eProperty, EVRApplicationError * peError);
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *سېټ_Application_Auto_Launch)(حرف * pch_App_کلی, bool bAutoLaunch);
	bool (OPENVR_FNTABLE_CALLTYPE *GetApplicationAutoLaunch)(حرف * pch_App_کلی);
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *سېټ_Default_Application_For_Mime_Type)(حرف * pch_App_کلی, حرف * pchMimeType);
	bool (OPENVR_FNTABLE_CALLTYPE *GetDefaultApplicationForMimeType)(حرف * pchMimeType, حرف * pch_App_کلی_بفر, uint32_t un_App_کلی_بفر_Len);
	bool (OPENVR_FNTABLE_CALLTYPE *GetApplicationSupportedMimeTypes)(حرف * pch_App_کلی, حرف * pch_Mime_Types_بفر, uint32_t un_Mime_Types_بفر);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetApplicationsThatSupportMimeType)(حرف * pchMimeType, حرف * pch_App_کلیګانې_That_Support_بفر, uint32_t un_App_کلیګانې_That_Support_بفر);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetApplicationLaunchArguments)(uint32_t unHandle, حرف * pch_دلیلونه, uint32_t un_دلیلونه);
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *GetStartingApplication)(حرف * pch_App_کلی_بفر, uint32_t un_App_کلی_بفر_Len);
	EVRSceneApplicationState (OPENVR_FNTABLE_CALLTYPE *GetSceneApplicationState)();
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *PerformApplicationPrelaunchCheck)(حرف * pch_App_کلی);
	حرف * (OPENVR_FNTABLE_CALLTYPE *GetSceneApplicationStateNameFromEnum)(EVRSceneApplicationState state);
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *Launch_دننی_Process)(حرف * pch_دوګونی_لار, حرف * pchArguments, حرف * pchWorkingDirectory);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetCurrentSceneProcessId)();
};

بنية VR_IVRChaperone_Fn_جدول
{
	ChaperoneCalibrationState (OPENVR_FNTABLE_CALLTYPE *GetCalibrationState)();
	bool (OPENVR_FNTABLE_CALLTYPE *Get_Play_Area_اندازه)(عائم * p_اندازه_X, عائم * p_اندازه_Z);
	bool (OPENVR_FNTABLE_CALLTYPE *GetPlayAreaRect)(بنية HmdQuad_t * rect);
	فراغ (OPENVR_FNTABLE_CALLTYPE *ReloadInfo)();
	فراغ (OPENVR_FNTABLE_CALLTYPE *سېټ_Scene_Color)(بنية HmdColor_t color);
	فراغ (OPENVR_FNTABLE_CALLTYPE *GetBoundsColor)(بنية HmdColor_t * pOutputColorArray, صحيح n_عدد_Output_Colors, عائم fl_Collision_Bounds_Fade_واټن, بنية HmdColor_t * pOutputCameraColor);
	bool (OPENVR_FNTABLE_CALLTYPE *AreBoundsVisible)();
	فراغ (OPENVR_FNTABLE_CALLTYPE *ForceBoundsVisible)(bool bForce);
	فراغ (OPENVR_FNTABLE_CALLTYPE *ResetZeroPose)(ETrackingUniverseOrigin eTrackingUniverseOrigin);
};

بنية VR_IVRChaperone_تیاری_Fn_جدول
{
	bool (OPENVR_FNTABLE_CALLTYPE *CommitWorkingCopy)(EChaperoneConfigFile configFile);
	فراغ (OPENVR_FNTABLE_CALLTYPE *RevertWorkingCopy)();
	bool (OPENVR_FNTABLE_CALLTYPE *Get_Working_Play_Area_اندازه)(عائم * p_اندازه_X, عائم * p_اندازه_Z);
	bool (OPENVR_FNTABLE_CALLTYPE *GetWorkingPlayAreaRect)(بنية HmdQuad_t * rect);
	bool (OPENVR_FNTABLE_CALLTYPE *GetWorkingCollisionBoundsInfo)(بنية HmdQuad_t * p_Quads_بفر, uint32_t * pun_Quads_شمېر);
	bool (OPENVR_FNTABLE_CALLTYPE *Get_ژوندی_Collision_Bounds_Info)(بنية HmdQuad_t * p_Quads_بفر, uint32_t * pun_Quads_شمېر);
	bool (OPENVR_FNTABLE_CALLTYPE *Get_Working_Seated_Zero_Pose_منزل_Raw_Tracking_Pose)(بنية HmdMatrix34_t * pmat_Seated_Zero_Pose_منزل_Raw_Tracking_Pose);
	bool (OPENVR_FNTABLE_CALLTYPE *Get_Working_Standing_Zero_Pose_منزل_Raw_Tracking_Pose)(بنية HmdMatrix34_t * pmat_Standing_Zero_Pose_منزل_Raw_Tracking_Pose);
	فراغ (OPENVR_FNTABLE_CALLTYPE *سېټ_Working_Play_Area_اندازه)(عائم اندازه_X, عائم اندازه_Z);
	فراغ (OPENVR_FNTABLE_CALLTYPE *سېټ_Working_Collision_Bounds_Info)(بنية HmdQuad_t * p_Quads_بفر, uint32_t un_Quads_شمېر);
	فراغ (OPENVR_FNTABLE_CALLTYPE *سېټ_Working_Perimeter)(بنية HmdVector2_t * p_ټکی_بفر, uint32_t un_ټکی_شمېر);
	فراغ (OPENVR_FNTABLE_CALLTYPE *سېټ_Working_Seated_Zero_Pose_منزل_Raw_Tracking_Pose)(بنية HmdMatrix34_t * p_Mat_Seated_Zero_Pose_منزل_Raw_Tracking_Pose);
	فراغ (OPENVR_FNTABLE_CALLTYPE *سېټ_Working_Standing_Zero_Pose_منزل_Raw_Tracking_Pose)(بنية HmdMatrix34_t * p_Mat_Standing_Zero_Pose_منزل_Raw_Tracking_Pose);
	فراغ (OPENVR_FNTABLE_CALLTYPE *ReloadFromDisk)(EChaperoneConfigFile configFile);
	bool (OPENVR_FNTABLE_CALLTYPE *Get_ژوندی_Seated_Zero_Pose_منزل_Raw_Tracking_Pose)(بنية HmdMatrix34_t * pmat_Seated_Zero_Pose_منزل_Raw_Tracking_Pose);
	bool (OPENVR_FNTABLE_CALLTYPE *Export_ژوندی_منزل_بفر)(حرف * p_بفر, uint32_t * pn_بفر_اوږدتیا);
	bool (OPENVR_FNTABLE_CALLTYPE *Import_From_بفر_منزل_Working)(حرف * p_بفر, uint32_t nImportFlags);
	فراغ (OPENVR_FNTABLE_CALLTYPE *Show_Working_سېټ_Preview)();
	فراغ (OPENVR_FNTABLE_CALLTYPE *Hide_Working_سېټ_Preview)();
	فراغ (OPENVR_FNTABLE_CALLTYPE *ځای_تیاری_Starting)();
};

بنية VR_IVRCompositor_Fn_جدول
{
	فراغ (OPENVR_FNTABLE_CALLTYPE *سېټ_Tracking_Space)(ETrackingUniverseOrigin eOrigin);
	ETrackingUniverseOrigin (OPENVR_FNTABLE_CALLTYPE *GetTrackingSpace)();
	EVRCompositorError (OPENVR_FNTABLE_CALLTYPE *WaitGetPoses)(بنية TrackedDevicePose_t * pRenderPoseArray, uint32_t un_Render_Pose_Array_شمېر, بنية TrackedDevicePose_t * pGamePoseArray, uint32_t un_Game_Pose_Array_شمېر);
	EVRCompositorError (OPENVR_FNTABLE_CALLTYPE *Get_وروستی_Poses)(بنية TrackedDevicePose_t * pRenderPoseArray, uint32_t un_Render_Pose_Array_شمېر, بنية TrackedDevicePose_t * pGamePoseArray, uint32_t un_Game_Pose_Array_شمېر);
	EVRCompositorError (OPENVR_FNTABLE_CALLTYPE *Get_وروستی_Pose_For_Tracked_Device_شاخص)(Tracked_Device_شاخص_t un_Device_شاخص, بنية TrackedDevicePose_t * pOutputPose, بنية TrackedDevicePose_t * pOutputGamePose);
	EVRCompositorError (OPENVR_FNTABLE_CALLTYPE *Submit)(EVREye eEye, بنية Texture_t * pTexture, بنية VRTextureBounds_t * pBounds, EVRSubmitFlags nSubmitFlags);
	فراغ (OPENVR_FNTABLE_CALLTYPE *Clear_وروستی_Submitted_چوکاټ)();
	فراغ (OPENVR_FNTABLE_CALLTYPE *PostPresentHandoff)();
	bool (OPENVR_FNTABLE_CALLTYPE *Get_چوکاټ_Timing)(بنية Compositor_چوکاټ_Timing * pTiming, uint32_t un_چوکاټونه_Ago);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *Get_چوکاټ_Timings)(بنية Compositor_چوکاټ_Timing * pTiming, uint32_t n_چوکاټونه);
	عائم (OPENVR_FNTABLE_CALLTYPE *Get_چوکاټ_وخت_پاتې_شوی)();
	فراغ (OPENVR_FNTABLE_CALLTYPE *GetCumulativeStats)(بنية Compositor_CumulativeStats * pStats, uint32_t n_Stats_اندازه_دننه_بایټونه);
	فراغ (OPENVR_FNTABLE_CALLTYPE *Fade_منزل_Color)(عائم fSeconds, عائم fRed, عائم fGreen, عائم fBlue, عائم fAlpha, bool bBackground);
	بنية HmdColor_t (OPENVR_FNTABLE_CALLTYPE *GetCurrentFadeColor)(bool bBackground);
	فراغ (OPENVR_FNTABLE_CALLTYPE *FadeGrid)(عائم fSeconds, bool b_Fade_Grid_دننه);
	عائم (OPENVR_FNTABLE_CALLTYPE *GetCurrentGridAlpha)();
	EVRCompositorError (OPENVR_FNTABLE_CALLTYPE *سېټ_Skybox_Override)(بنية Texture_t * pTextures, uint32_t un_Texture_شمېر);
	فراغ (OPENVR_FNTABLE_CALLTYPE *ClearSkyboxOverride)();
	فراغ (OPENVR_FNTABLE_CALLTYPE *Compositor_Bring_منزل_Front)();
	فراغ (OPENVR_FNTABLE_CALLTYPE *Compositor_Go_منزل_شا)();
	فراغ (OPENVR_FNTABLE_CALLTYPE *CompositorQuit)();
	bool (OPENVR_FNTABLE_CALLTYPE *IsFullscreen)();
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetCurrentSceneFocusProcess)();
	uint32_t (OPENVR_FNTABLE_CALLTYPE *Get_وروستی_چوکاټ_Renderer)();
	bool (OPENVR_FNTABLE_CALLTYPE *CanRenderScene)();
	فراغ (OPENVR_FNTABLE_CALLTYPE *Show_Mirror_کړکۍ)();
	فراغ (OPENVR_FNTABLE_CALLTYPE *Hide_Mirror_کړکۍ)();
	bool (OPENVR_FNTABLE_CALLTYPE *Is_Mirror_کړکۍ_Visible)();
	فراغ (OPENVR_FNTABLE_CALLTYPE *CompositorDumpImages)();
	bool (OPENVR_FNTABLE_CALLTYPE *Should_App_Render_With_ټیټ_Resources)();
	فراغ (OPENVR_FNTABLE_CALLTYPE *ForceInterleavedReprojectionOn)(bool bOverride);
	فراغ (OPENVR_FNTABLE_CALLTYPE *ForceReconnectProcess)();
	فراغ (OPENVR_FNTABLE_CALLTYPE *SuspendRendering)(bool bSuspend);
	EVRCompositorError (OPENVR_FNTABLE_CALLTYPE *GetMirrorTextureD3D11)(EVREye eEye, فراغ * pD3D11DeviceOrResource, فراغ ** ppD3D11ShaderResourceView);
	فراغ (OPENVR_FNTABLE_CALLTYPE *ReleaseMirrorTextureD3D11)(فراغ * pD3D11ShaderResourceView);
	EVRCompositorError (OPENVR_FNTABLE_CALLTYPE *GetMirrorTextureGL)(EVREye eEye, glUInt_t * pglTextureId, glSharedTextureHandle_t * pglSharedTextureHandle);
	bool (OPENVR_FNTABLE_CALLTYPE *ReleaseSharedGLTexture)(glUInt_t glTextureId, glSharedTextureHandle_t glSharedTextureHandle);
	فراغ (OPENVR_FNTABLE_CALLTYPE *قلف_GLShared_Texture_For_Access)(glSharedTextureHandle_t glSharedTextureHandle);
	فراغ (OPENVR_FNTABLE_CALLTYPE *UnlockGLSharedTextureForAccess)(glSharedTextureHandle_t glSharedTextureHandle);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetVulkanInstanceExtensionsRequired)(حرف * pch_ارزښت, uint32_t un_بفر_اندازه);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetVulkanDeviceExtensionsRequired)(بنية VkPhysicalDevice_T * pPhysicalDevice, حرف * pch_ارزښت, uint32_t un_بفر_اندازه);
	فراغ (OPENVR_FNTABLE_CALLTYPE *سېټ_Explicit_Timing_ډېرپېښ)(EVRCompositor_Timing_ډېرپېښ e_Timing_ډېرپېښ);
	EVRCompositorError (OPENVR_FNTABLE_CALLTYPE *Submit_Explicit_Timing_معلومات)();
	bool (OPENVR_FNTABLE_CALLTYPE *IsMotionSmoothingEnabled)();
	bool (OPENVR_FNTABLE_CALLTYPE *IsMotionSmoothingSupported)();
	bool (OPENVR_FNTABLE_CALLTYPE *IsCurrentSceneFocusAppLoading)();
	EVRCompositorError (OPENVR_FNTABLE_CALLTYPE *سېټ_Stage_Override_Async)(حرف * pch_Render_Model_لار, بنية HmdMatrix34_t * pTransform, بنية Compositor_StageRenderSettings * pRenderSettings, uint32_t n_اندازه_د_Render_Settings);
	فراغ (OPENVR_FNTABLE_CALLTYPE *ClearStageOverride)();
	bool (OPENVR_FNTABLE_CALLTYPE *GetCompositorBenchmarkResults)(بنية Compositor_BenchmarkResults * pBenchmarkResults, uint32_t n_اندازه_د_Benchmark_Results);
	EVRCompositorError (OPENVR_FNTABLE_CALLTYPE *Get_وروستی_Pose_Prediction_IDs)(uint32_t * pRenderPosePredictionID, uint32_t * pGamePosePredictionID);
	EVRCompositorError (OPENVR_FNTABLE_CALLTYPE *Get_Poses_For_چوکاټ)(uint32_t unPosePredictionID, بنية TrackedDevicePose_t * pPoseArray, uint32_t un_Pose_Array_شمېر);
};

بنية VR_IVROverlay_Fn_جدول
{
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *پیدا_کړه_Overlay)(حرف * pch_Overlay_کلی, VROverlayHandle_t * pOverlayHandle);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *CreateOverlay)(حرف * pch_Overlay_کلی, حرف * pchOverlayName, VROverlayHandle_t * pOverlayHandle);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *DestroyOverlay)(VROverlayHandle_t ulOverlayHandle);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *Get_Overlay_کلی)(VROverlayHandle_t ulOverlayHandle, حرف * pch_ارزښت, uint32_t un_بفر_اندازه, EVROverlayError * pError);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetOverlayName)(VROverlayHandle_t ulOverlayHandle, حرف * pch_ارزښت, uint32_t un_بفر_اندازه, EVROverlayError * pError);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *سېټ_Overlay_Name)(VROverlayHandle_t ulOverlayHandle, حرف * pchName);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *Get_Overlay_Image_معلومات)(VROverlayHandle_t ulOverlayHandle, فراغ * pv_بفر, uint32_t un_بفر_اندازه, uint32_t * pun_پلنوالی, uint32_t * pun_لوړوالی);
	حرف * (OPENVR_FNTABLE_CALLTYPE *GetOverlayErrorNameFromEnum)(EVROverlayError error);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *سېټ_Overlay_Rendering_Pid)(VROverlayHandle_t ulOverlayHandle, uint32_t unPID);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetOverlayRenderingPid)(VROverlayHandle_t ulOverlayHandle);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *سېټ_Overlay_Flag)(VROverlayHandle_t ulOverlayHandle, VROverlayFlags eOverlayFlag, bool bEnabled);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayFlag)(VROverlayHandle_t ulOverlayHandle, VROverlayFlags eOverlayFlag, bool * pbEnabled);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayFlags)(VROverlayHandle_t ulOverlayHandle, uint32_t * pFlags);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *سېټ_Overlay_Color)(VROverlayHandle_t ulOverlayHandle, عائم fRed, عائم fGreen, عائم fBlue);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayColor)(VROverlayHandle_t ulOverlayHandle, عائم * pfRed, عائم * pfGreen, عائم * pfBlue);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *سېټ_Overlay_Alpha)(VROverlayHandle_t ulOverlayHandle, عائم fAlpha);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayAlpha)(VROverlayHandle_t ulOverlayHandle, عائم * pfAlpha);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *سېټ_Overlay_Texel_Aspect)(VROverlayHandle_t ulOverlayHandle, عائم fTexelAspect);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayTexelAspect)(VROverlayHandle_t ulOverlayHandle, عائم * pfTexelAspect);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *سېټ_Overlay_ترتیبول_ترتیب)(VROverlayHandle_t ulOverlayHandle, uint32_t un_ترتیبول_ترتیب);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *Get_Overlay_ترتیبول_ترتیب)(VROverlayHandle_t ulOverlayHandle, uint32_t * pun_ترتیبول_ترتیب);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *سېټ_Overlay_پلنوالی_دننه_Meters)(VROverlayHandle_t ulOverlayHandle, عائم f_پلنوالی_دننه_Meters);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *Get_Overlay_پلنوالی_دننه_Meters)(VROverlayHandle_t ulOverlayHandle, عائم * pf_پلنوالی_دننه_Meters);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *سېټ_Overlay_Curvature)(VROverlayHandle_t ulOverlayHandle, عائم fCurvature);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayCurvature)(VROverlayHandle_t ulOverlayHandle, عائم * pfCurvature);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *سېټ_Overlay_Pre_منحني_Pitch)(VROverlayHandle_t ulOverlayHandle, عائم fRadians);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *Get_Overlay_Pre_منحني_Pitch)(VROverlayHandle_t ulOverlayHandle, عائم * pfRadians);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *سېټ_Overlay_Texture_Color_Space)(VROverlayHandle_t ulOverlayHandle, EColorSpace eTextureColorSpace);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayTextureColorSpace)(VROverlayHandle_t ulOverlayHandle, EColorSpace * peTextureColorSpace);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *سېټ_Overlay_Texture_Bounds)(VROverlayHandle_t ulOverlayHandle, بنية VRTextureBounds_t * pOverlayTextureBounds);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayTextureBounds)(VROverlayHandle_t ulOverlayHandle, بنية VRTextureBounds_t * pOverlayTextureBounds);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayTransformType)(VROverlayHandle_t ulOverlayHandle, VROverlayTransformType * peTransformType);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *سېټ_Overlay_Transform_Absolute)(VROverlayHandle_t ulOverlayHandle, ETrackingUniverseOrigin eTrackingOrigin, بنية HmdMatrix34_t * pmat_Tracking_Origin_منزل_Overlay_Transform);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayTransformAbsolute)(VROverlayHandle_t ulOverlayHandle, ETrackingUniverseOrigin * peTrackingOrigin, بنية HmdMatrix34_t * pmat_Tracking_Origin_منزل_Overlay_Transform);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *سېټ_Overlay_Transform_Tracked_Device_Relative)(VROverlayHandle_t ulOverlayHandle, Tracked_Device_شاخص_t unTrackedDevice, بنية HmdMatrix34_t * pmat_Tracked_Device_منزل_Overlay_Transform);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayTransformTrackedDeviceRelative)(VROverlayHandle_t ulOverlayHandle, Tracked_Device_شاخص_t * punTrackedDevice, بنية HmdMatrix34_t * pmat_Tracked_Device_منزل_Overlay_Transform);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *سېټ_Overlay_Transform_Tracked_Device_Component)(VROverlayHandle_t ulOverlayHandle, Tracked_Device_شاخص_t un_Device_شاخص, حرف * pchComponentName);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayTransformTrackedDeviceComponent)(VROverlayHandle_t ulOverlayHandle, Tracked_Device_شاخص_t * pun_Device_شاخص, حرف * pchComponentName, uint32_t un_Component_Name_اندازه);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayTransformOverlayRelative)(VROverlayHandle_t ulOverlayHandle, VROverlayHandle_t * ul_Overlay_Handle_پلار, بنية HmdMatrix34_t * pmat_پلار_Overlay_منزل_Overlay_Transform);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *سېټ_Overlay_Transform_Overlay_Relative)(VROverlayHandle_t ulOverlayHandle, VROverlayHandle_t ul_Overlay_Handle_پلار, بنية HmdMatrix34_t * pmat_پلار_Overlay_منزل_Overlay_Transform);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *سېټ_Overlay_Transform_Cursor)(VROverlayHandle_t ulCursorOverlayHandle, بنية HmdVector2_t * pvHotspot);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayTransformCursor)(VROverlayHandle_t ulOverlayHandle, بنية HmdVector2_t * pvHotspot);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *سېټ_Overlay_Transform_Projection)(VROverlayHandle_t ulOverlayHandle, ETrackingUniverseOrigin eTrackingOrigin, بنية HmdMatrix34_t * pmat_Tracking_Origin_منزل_Overlay_Transform, بنية VROverlayProjection_t * pProjection, EVREye eEye);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *ShowOverlay)(VROverlayHandle_t ulOverlayHandle);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *HideOverlay)(VROverlayHandle_t ulOverlayHandle);
	bool (OPENVR_FNTABLE_CALLTYPE *IsOverlayVisible)(VROverlayHandle_t ulOverlayHandle);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetTransformForOverlayCoordinates)(VROverlayHandle_t ulOverlayHandle, ETrackingUniverseOrigin eTrackingOrigin, بنية HmdVector2_t coordinates_دننه_Overlay, بنية HmdMatrix34_t * pmatTransform);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *Wait_چوکاټ_Sync)(uint32_t nTimeoutMs);
	bool (OPENVR_FNTABLE_CALLTYPE *Poll_بل_Overlay_Event)(VROverlayHandle_t ulOverlayHandle, بنية VREvent_t * pEvent, uint32_t uncbVREvent);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *Get_Overlay_ننوت_لاره)(VROverlayHandle_t ulOverlayHandle, VROverlay_ننوت_لاره * pe_ننوت_لاره);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *سېټ_Overlay_ننوت_لاره)(VROverlayHandle_t ulOverlayHandle, VROverlay_ننوت_لاره e_ننوت_لاره);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayMouseScale)(VROverlayHandle_t ulOverlayHandle, بنية HmdVector2_t * pvecMouseScale);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *سېټ_Overlay_Mouse_Scale)(VROverlayHandle_t ulOverlayHandle, بنية HmdVector2_t * pvecMouseScale);
	bool (OPENVR_FNTABLE_CALLTYPE *ComputeOverlayIntersection)(VROverlayHandle_t ulOverlayHandle, بنية VROverlayIntersectionParams_t * pParams, بنية VROverlayIntersectionResults_t * pResults);
	bool (OPENVR_FNTABLE_CALLTYPE *Is_Hover_موخه_Overlay)(VROverlayHandle_t ulOverlayHandle);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *سېټ_Overlay_Intersection_ماسک)(VROverlayHandle_t ulOverlayHandle, بنية VROverlay_Intersection_ماسک_Primitive_t * p_ماسک_Primitives, uint32_t un_عدد_ماسک_Primitives, uint32_t un_Primitive_اندازه);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *TriggerLaserMouseHapticVibration)(VROverlayHandle_t ulOverlayHandle, عائم fDurationSeconds, عائم fFrequency, عائم fAmplitude);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *سېټ_Overlay_Cursor)(VROverlayHandle_t ulOverlayHandle, VROverlayHandle_t ulCursorHandle);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *سېټ_Overlay_Cursor_Position_Override)(VROverlayHandle_t ulOverlayHandle, بنية HmdVector2_t * pvCursor);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *ClearOverlayCursorPositionOverride)(VROverlayHandle_t ulOverlayHandle);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *سېټ_Overlay_Texture)(VROverlayHandle_t ulOverlayHandle, بنية Texture_t * pTexture);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *ClearOverlayTexture)(VROverlayHandle_t ulOverlayHandle);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *سېټ_Overlay_Raw)(VROverlayHandle_t ulOverlayHandle, فراغ * pv_بفر, uint32_t un_پلنوالی, uint32_t un_لوړوالی, uint32_t un_بایټونه_فی_Pixel);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *سېټ_Overlay_From_File)(VROverlayHandle_t ulOverlayHandle, حرف * pch_File_لار);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayTexture)(VROverlayHandle_t ulOverlayHandle, فراغ ** pNativeTextureHandle, فراغ * pNativeTextureRef, uint32_t * p_پلنوالی, uint32_t * p_لوړوالی, uint32_t * pNativeFormat, ETextureType * pAPIType, EColorSpace * pColorSpace, بنية VRTextureBounds_t * pTextureBounds);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *ReleaseNativeOverlayHandle)(VROverlayHandle_t ulOverlayHandle, فراغ * pNativeTextureHandle);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *Get_Overlay_Texture_اندازه)(VROverlayHandle_t ulOverlayHandle, uint32_t * p_پلنوالی, uint32_t * p_لوړوالی);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *CreateDashboardOverlay)(حرف * pch_Overlay_کلی, حرف * pchOverlayFriendlyName, VROverlayHandle_t * pMainHandle, VROverlayHandle_t * pThumbnailHandle);
	bool (OPENVR_FNTABLE_CALLTYPE *IsDashboardVisible)();
	bool (OPENVR_FNTABLE_CALLTYPE *Is_فعال_Dashboard_Overlay)(VROverlayHandle_t ulOverlayHandle);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *سېټ_Dashboard_Overlay_Scene_Process)(VROverlayHandle_t ulOverlayHandle, uint32_t unProcessId);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetDashboardOverlaySceneProcess)(VROverlayHandle_t ulOverlayHandle, uint32_t * punProcessId);
	فراغ (OPENVR_FNTABLE_CALLTYPE *ShowDashboard)(حرف * pch_Overlay_منزل_Show);
	Tracked_Device_شاخص_t (OPENVR_FNTABLE_CALLTYPE *GetPrimaryDashboardDevice)();
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *ShowKeyboard)(EGamepad_متن_ننوت_ډېرپېښ e_ننوت_ډېرپېښ, EGamepad_متن_ننوت_کرښه_ډېرپېښ e_کرښه_ننوت_ډېرپېښ, uint32_t unFlags, حرف * pchDescription, uint32_t unCharMax, حرف * pch_Existing_متن, uint64_t u_User_ارزښت);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *ShowKeyboardForOverlay)(VROverlayHandle_t ulOverlayHandle, EGamepad_متن_ننوت_ډېرپېښ e_ننوت_ډېرپېښ, EGamepad_متن_ننوت_کرښه_ډېرپېښ e_کرښه_ننوت_ډېرپېښ, uint32_t unFlags, حرف * pchDescription, uint32_t unCharMax, حرف * pch_Existing_متن, uint64_t u_User_ارزښت);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *Get_Keyboard_متن)(حرف * pch_متن, uint32_t cch_متن);
	فراغ (OPENVR_FNTABLE_CALLTYPE *HideKeyboard)();
	فراغ (OPENVR_FNTABLE_CALLTYPE *سېټ_Keyboard_Transform_Absolute)(ETrackingUniverseOrigin eTrackingOrigin, بنية HmdMatrix34_t * pmat_Tracking_Origin_منزل_Keyboard_Transform);
	فراغ (OPENVR_FNTABLE_CALLTYPE *سېټ_Keyboard_Position_For_Overlay)(VROverlayHandle_t ulOverlayHandle, بنية HmdRect2_t avoidRect);
	VRMessageOverlayResponse (OPENVR_FNTABLE_CALLTYPE *Show_پیغام_Overlay)(حرف * pch_متن, حرف * pchCaption, حرف * pch_Button0_متن, حرف * pch_Button1_متن, حرف * pch_Button2_متن, حرف * pch_Button3_متن);
	فراغ (OPENVR_FNTABLE_CALLTYPE *Close_پیغام_Overlay)();
};

بنية VR_IVROverlay_View_Fn_جدول
{
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *AcquireOverlayView)(VROverlayHandle_t ulOverlayHandle, بنية VRNativeDevice_t * pNativeDevice, بنية VROverlayView_t * pOverlayView, uint32_t un_Overlay_View_اندازه);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *ReleaseOverlayView)(بنية VROverlayView_t * pOverlayView);
	فراغ (OPENVR_FNTABLE_CALLTYPE *PostOverlayEvent)(VROverlayHandle_t ulOverlayHandle, بنية VREvent_t * pvrEvent);
	bool (OPENVR_FNTABLE_CALLTYPE *IsViewingPermitted)(VROverlayHandle_t ulOverlayHandle);
};

بنية VR_IVRHeadset_View_Fn_جدول
{
	فراغ (OPENVR_FNTABLE_CALLTYPE *سېټ_Headset_View_اندازه)(uint32_t n_پلنوالی, uint32_t n_لوړوالی);
	فراغ (OPENVR_FNTABLE_CALLTYPE *Get_Headset_View_اندازه)(uint32_t * pn_پلنوالی, uint32_t * pn_لوړوالی);
	فراغ (OPENVR_FNTABLE_CALLTYPE *سېټ_Headset_View_ډېرپېښ)(Headset_View_ډېرپېښ_t e_Headset_View_ډېرپېښ);
	Headset_View_ډېرپېښ_t (OPENVR_FNTABLE_CALLTYPE *Get_Headset_View_ډېرپېښ)();
	فراغ (OPENVR_FNTABLE_CALLTYPE *سېټ_Headset_View_Cropped)(bool bCropped);
	bool (OPENVR_FNTABLE_CALLTYPE *GetHeadsetViewCropped)();
	عائم (OPENVR_FNTABLE_CALLTYPE *Get_Headset_View_Aspect_نسبت)();
	فراغ (OPENVR_FNTABLE_CALLTYPE *سېټ_Headset_View_Blend_Range)(عائم fl_پیل_Pct, عائم fl_پای_ټکی_Pct);
	فراغ (OPENVR_FNTABLE_CALLTYPE *GetHeadsetViewBlendRange)(عائم * p_پیل_Pct, عائم * p_پای_ټکی_Pct);
};

بنية VR_IVRRender_Models_Fn_جدول
{
	EVRRenderModelError (OPENVR_FNTABLE_CALLTYPE *بارول_Render_Model_Async)(حرف * pchRenderModelName, بنية RenderModel_t ** ppRenderModel);
	فراغ (OPENVR_FNTABLE_CALLTYPE *FreeRenderModel)(بنية RenderModel_t * pRenderModel);
	EVRRenderModelError (OPENVR_FNTABLE_CALLTYPE *بارول_Texture_Async)(TextureID_t textureId, بنية RenderModel_TextureMap_t ** ppTexture);
	فراغ (OPENVR_FNTABLE_CALLTYPE *FreeTexture)(بنية RenderModel_TextureMap_t * pTexture);
	EVRRenderModelError (OPENVR_FNTABLE_CALLTYPE *بارول_Texture_D3_D11_Async)(TextureID_t textureId, فراغ * pD3D11Device, فراغ ** ppD3D11Texture2D);
	EVRRenderModelError (OPENVR_FNTABLE_CALLTYPE *بارول_Into_Texture_D3_D11_Async)(TextureID_t textureId, فراغ * pDstTexture);
	فراغ (OPENVR_FNTABLE_CALLTYPE *FreeTextureD3D11)(فراغ * pD3D11Texture2D);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetRenderModelName)(uint32_t un_Render_Model_شاخص, حرف * pchRenderModelName, uint32_t unRenderModelNameLen);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *Get_Render_Model_شمېر)();
	uint32_t (OPENVR_FNTABLE_CALLTYPE *Get_Component_شمېر)(حرف * pchRenderModelName);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetComponentName)(حرف * pchRenderModelName, uint32_t un_Component_شاخص, حرف * pchComponentName, uint32_t unComponentNameLen);
	uint64_t (OPENVR_FNTABLE_CALLTYPE *Get_Component_Button_ماسک)(حرف * pchRenderModelName, حرف * pchComponentName);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetComponentRenderModelName)(حرف * pchRenderModelName, حرف * pchComponentName, حرف * pchComponentRenderModelName, uint32_t unComponentRenderModelNameLen);
	bool (OPENVR_FNTABLE_CALLTYPE *Get_Component_State_For_Device_لار)(حرف * pchRenderModelName, حرف * pchComponentName, VRInput_ارزښت_Handle_t device_لار, Render_Model_Controller_ډېرپېښ_State_t * pState, RenderModel_ComponentState_t * pComponentState);
	bool (OPENVR_FNTABLE_CALLTYPE *GetComponentState)(حرف * pchRenderModelName, حرف * pchComponentName, VRControllerState_t * pControllerState, بنية Render_Model_Controller_ډېرپېښ_State_t * pState, بنية RenderModel_ComponentState_t * pComponentState);
	bool (OPENVR_FNTABLE_CALLTYPE *RenderModelHasComponent)(حرف * pchRenderModelName, حرف * pchComponentName);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetRenderModelThumbnailURL)(حرف * pchRenderModelName, حرف * pchThumbnailURL, uint32_t unThumbnailURLLen, EVRRenderModelError * peError);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *Get_Render_Model_Original_لار)(حرف * pchRenderModelName, حرف * pch_Original_لار, uint32_t un_Original_لار_Len, EVRRenderModelError * peError);
	حرف * (OPENVR_FNTABLE_CALLTYPE *GetRenderModelErrorNameFromEnum)(EVRRenderModelError error);
};

بنية VR_IVRNotifications_Fn_جدول
{
	EVRNotificationError (OPENVR_FNTABLE_CALLTYPE *CreateNotification)(VROverlayHandle_t ulOverlayHandle, uint64_t ul_User_ارزښت, EVRNotificationType type, حرف * pch_متن, EVRNotificationStyle style, بنية NotificationBitmap_t * pImage, VRNotificationId * pNotificationId);
	EVRNotificationError (OPENVR_FNTABLE_CALLTYPE *RemoveNotification)(VRNotificationId notificationId);
};

بنية VR_IVRSettings_Fn_جدول
{
	حرف * (OPENVR_FNTABLE_CALLTYPE *GetSettingsErrorNameFromEnum)(EVRSettingsError eError);
	فراغ (OPENVR_FNTABLE_CALLTYPE *سېټ_Bool)(حرف * pchSection, حرف * pch_Settings_کلی, bool b_ارزښت, EVRSettingsError * peError);
	فراغ (OPENVR_FNTABLE_CALLTYPE *سېټ_Int32)(حرف * pchSection, حرف * pch_Settings_کلی, int32_t n_ارزښت, EVRSettingsError * peError);
	فراغ (OPENVR_FNTABLE_CALLTYPE *سېټ_Float)(حرف * pchSection, حرف * pch_Settings_کلی, عائم fl_ارزښت, EVRSettingsError * peError);
	فراغ (OPENVR_FNTABLE_CALLTYPE *سېټ_String)(حرف * pchSection, حرف * pch_Settings_کلی, حرف * pch_ارزښت, EVRSettingsError * peError);
	bool (OPENVR_FNTABLE_CALLTYPE *GetBool)(حرف * pchSection, حرف * pch_Settings_کلی, EVRSettingsError * peError);
	int32_t (OPENVR_FNTABLE_CALLTYPE *GetInt32)(حرف * pchSection, حرف * pch_Settings_کلی, EVRSettingsError * peError);
	عائم (OPENVR_FNTABLE_CALLTYPE *GetFloat)(حرف * pchSection, حرف * pch_Settings_کلی, EVRSettingsError * peError);
	فراغ (OPENVR_FNTABLE_CALLTYPE *GetString)(حرف * pchSection, حرف * pch_Settings_کلی, حرف * pch_ارزښت, uint32_t un_ارزښت_Len, EVRSettingsError * peError);
	فراغ (OPENVR_FNTABLE_CALLTYPE *RemoveSection)(حرف * pchSection, EVRSettingsError * peError);
	فراغ (OPENVR_FNTABLE_CALLTYPE *Remove_کلی_دننه_Section)(حرف * pchSection, حرف * pch_Settings_کلی, EVRSettingsError * peError);
};

بنية VR_IVRScreenshots_Fn_جدول
{
	EVRScreenshotError (OPENVR_FNTABLE_CALLTYPE *RequestScreenshot)(ScreenshotHandle_t * p_بهر_Screenshot_Handle, EVRScreenshotType type, حرف * pchPreviewFilename, حرف * pchVRFilename);
	EVRScreenshotError (OPENVR_FNTABLE_CALLTYPE *HookScreenshot)(EVRScreenshotType * pSupportedTypes, صحيح عدد_Types);
	EVRScreenshotType (OPENVR_FNTABLE_CALLTYPE *GetScreenshotPropertyType)(ScreenshotHandle_t screenshotHandle, EVRScreenshotError * pError);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetScreenshotPropertyFilename)(ScreenshotHandle_t screenshotHandle, EVRScreenshotPropertyFilenames filenameType, حرف * pchFilename, uint32_t cchFilename, EVRScreenshotError * pError);
	EVRScreenshotError (OPENVR_FNTABLE_CALLTYPE *Update_Screenshot_پرمختګ)(ScreenshotHandle_t screenshotHandle, عائم fl_پرمختګ);
	EVRScreenshotError (OPENVR_FNTABLE_CALLTYPE *TakeStereoScreenshot)(ScreenshotHandle_t * p_بهر_Screenshot_Handle, حرف * pchPreviewFilename, حرف * pchVRFilename);
	EVRScreenshotError (OPENVR_FNTABLE_CALLTYPE *SubmitScreenshot)(ScreenshotHandle_t screenshotHandle, EVRScreenshotType type, حرف * pch_سرچینه_Preview_Filename, حرف * pch_سرچینه_VRFilename);
};

بنية VR_IVRResources_Fn_جدول
{
	uint32_t (OPENVR_FNTABLE_CALLTYPE *بارول_Shared_Resource)(حرف * pchResourceName, حرف * pch_بفر, uint32_t un_بفر_Len);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *Get_Resource_ډک_لار)(حرف * pchResourceName, حرف * pchResourceTypeDirectory, حرف * pch_لار_بفر, uint32_t un_بفر_Len);
};

بنية VR_IVRDriver_Manager_Fn_جدول
{
	uint32_t (OPENVR_FNTABLE_CALLTYPE *Get_Driver_شمېر)();
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetDriverName)(DriverId_t nDriver, حرف * pch_ارزښت, uint32_t un_بفر_اندازه);
	DriverHandle_t (OPENVR_FNTABLE_CALLTYPE *GetDriverHandle)(حرف * pchDriverName);
	bool (OPENVR_FNTABLE_CALLTYPE *IsEnabled)(DriverId_t nDriver);
};

بنية VR_IVRInput_Fn_جدول
{
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *سېټ_Action_Manifest_لار)(حرف * pch_Action_Manifest_لار);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *Get_Action_سېټ_Handle)(حرف * pch_Action_سېټ_Name, VRAction_سېټ_Handle_t * pHandle);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetActionHandle)(حرف * pchActionName, VRActionHandle_t * pHandle);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *Get_ننوت_سرچینه_Handle)(حرف * pch_ننوت_سرچینه_لار, VRInput_ارزښت_Handle_t * pHandle);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *UpdateActionState)(بنية VRActive_Action_سېټ_t * pSets, uint32_t un_اندازه_د_VRSelected_Action_سېټ_t, uint32_t un_سېټ_شمېر);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *Get_Digital_Action_معلومات)(VRActionHandle_t action, بنية ننوت_Digital_Action_معلومات_t * p_Action_معلومات, uint32_t un_Action_معلومات_اندازه, VRInput_ارزښت_Handle_t ul_Restrict_منزل_Device);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *Get_Analog_Action_معلومات)(VRActionHandle_t action, بنية ننوت_Analog_Action_معلومات_t * p_Action_معلومات, uint32_t un_Action_معلومات_اندازه, VRInput_ارزښت_Handle_t ul_Restrict_منزل_Device);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *Get_Pose_Action_معلومات_Relative_منزل_Now)(VRActionHandle_t action, ETrackingUniverseOrigin eOrigin, عائم fPredictedSecondsFromNow, بنية ننوت_Pose_Action_معلومات_t * p_Action_معلومات, uint32_t un_Action_معلومات_اندازه, VRInput_ارزښت_Handle_t ul_Restrict_منزل_Device);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *Get_Pose_Action_معلومات_For_بل_چوکاټ)(VRActionHandle_t action, ETrackingUniverseOrigin eOrigin, بنية ننوت_Pose_Action_معلومات_t * p_Action_معلومات, uint32_t un_Action_معلومات_اندازه, VRInput_ارزښت_Handle_t ul_Restrict_منزل_Device);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *Get_Skeletal_Action_معلومات)(VRActionHandle_t action, بنية ننوت_Skeletal_Action_معلومات_t * p_Action_معلومات, uint32_t un_Action_معلومات_اندازه);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetDominantHand)(ETrackedControllerRole * peDominantHand);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *سېټ_Dominant_Hand)(ETrackedControllerRole eDominantHand);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *Get_Bone_شمېر)(VRActionHandle_t action, uint32_t * p_Bone_شمېر);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetBoneHierarchy)(VRActionHandle_t action, Bone_شاخص_t * p_پلار_Indices, uint32_t un_شاخص_Aray_شمېر);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetBoneName)(VRActionHandle_t action, Bone_شاخص_t n_Bone_شاخص, حرف * pchBoneName, uint32_t un_Name_بفر_اندازه);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetSkeletalReferenceTransforms)(VRActionHandle_t action, EVRSkeletalTransformSpace eTransformSpace, EVRSkeletalReferencePose eReferencePose, بنية VRBoneTransform_t * pTransformArray, uint32_t un_Transform_Array_شمېر);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetSkeletalTrackingLevel)(VRActionHandle_t action, EVRSkeletalTrackingLevel * pSkeletalTrackingLevel);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *Get_Skeletal_Bone_معلومات)(VRActionHandle_t action, EVRSkeletalTransformSpace eTransformSpace, EVRSkeletalMotionRange eMotionRange, بنية VRBoneTransform_t * pTransformArray, uint32_t un_Transform_Array_شمېر);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *Get_Skeletal_Summary_معلومات)(VRActionHandle_t action, EVRSummaryType eSummaryType, بنية VRSkeletal_Summary_معلومات_t * p_Skeletal_Summary_معلومات);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *Get_Skeletal_Bone_معلومات_Compressed)(VRActionHandle_t action, EVRSkeletalMotionRange eMotionRange, فراغ * pv_Compressed_معلومات, uint32_t un_Compressed_اندازه, uint32_t * pun_Required_Compressed_اندازه);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *Decompress_Skeletal_Bone_معلومات)(فراغ * pv_Compressed_بفر, uint32_t un_Compressed_بفر_اندازه, EVRSkeletalTransformSpace eTransformSpace, بنية VRBoneTransform_t * pTransformArray, uint32_t un_Transform_Array_شمېر);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *TriggerHapticVibrationAction)(VRActionHandle_t action, عائم f_پیل_Seconds_From_Now, عائم fDurationSeconds, عائم fFrequency, عائم fAmplitude, VRInput_ارزښت_Handle_t ul_Restrict_منزل_Device);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetActionOrigins)(VRAction_سېټ_Handle_t action_سېټ_Handle, VRActionHandle_t digitalActionHandle, VRInput_ارزښت_Handle_t * origins_بهر, uint32_t origin_بهر_شمېر);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetOriginLocalizedName)(VRInput_ارزښت_Handle_t origin, حرف * pchNameArray, uint32_t un_Name_Array_اندازه, int32_t un_String_Sections_منزل_Include);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetOriginTrackedDeviceInfo)(VRInput_ارزښت_Handle_t origin, بنية ننوت_Origin_Info_t * pOriginInfo, uint32_t un_Origin_Info_اندازه);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetActionBindingInfo)(VRActionHandle_t action, بنية ننوت_Binding_Info_t * pOriginInfo, uint32_t un_Binding_Info_اندازه, uint32_t un_Binding_Info_شمېر, uint32_t * pun_Returned_Binding_Info_شمېر);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *ShowActionOrigins)(VRAction_سېټ_Handle_t action_سېټ_Handle, VRActionHandle_t ulActionHandle);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *Show_Bindings_For_Action_سېټ)(بنية VRActive_Action_سېټ_t * pSets, uint32_t un_اندازه_د_VRSelected_Action_سېټ_t, uint32_t un_سېټ_شمېر, VRInput_ارزښت_Handle_t origin_منزل_Highlight);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetComponentStateForBinding)(حرف * pchRenderModelName, حرف * pchComponentName, بنية ننوت_Binding_Info_t * pOriginInfo, uint32_t un_Binding_Info_اندازه, uint32_t un_Binding_Info_شمېر, RenderModel_ComponentState_t * pComponentState);
	bool (OPENVR_FNTABLE_CALLTYPE *Is_Using_Legacy_ننوت)();
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *OpenBindingUI)(حرف * pch_App_کلی, VRAction_سېټ_Handle_t ul_Action_سېټ_Handle, VRInput_ارزښت_Handle_t ulDeviceHandle, bool bShowOnDesktop);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetBindingVariant)(VRInput_ارزښت_Handle_t ul_Device_لار, حرف * pchVariantArray, uint32_t un_Variant_Array_اندازه);
};

بنية VR_IVRIOBuffer_Fn_جدول
{
	EIOBufferError (OPENVR_FNTABLE_CALLTYPE *Open)(حرف * pch_لار, EIOBuffer_ډېرپېښ ډېرپېښ, uint32_t un_Element_اندازه, uint32_t unElements, IOBufferHandle_t * pul_بفر);
	EIOBufferError (OPENVR_FNTABLE_CALLTYPE *Close)(IOBufferHandle_t ul_بفر);
	EIOBufferError (OPENVR_FNTABLE_CALLTYPE *Read)(IOBufferHandle_t ul_بفر, فراغ * pDst, uint32_t un_بایټونه, uint32_t * punRead);
	EIOBufferError (OPENVR_FNTABLE_CALLTYPE *Write)(IOBufferHandle_t ul_بفر, فراغ * pSrc, uint32_t un_بایټونه);
	PropertyContainerHandle_t (OPENVR_FNTABLE_CALLTYPE *PropertyContainer)(IOBufferHandle_t ul_بفر);
	bool (OPENVR_FNTABLE_CALLTYPE *HasReaders)(IOBufferHandle_t ul_بفر);
};

بنية VR_IVRSpatial_Anchors_Fn_جدول
{
	EVRSpatialAnchorError (OPENVR_FNTABLE_CALLTYPE *CreateSpatialAnchorFromDescriptor)(حرف * pchDescriptor, SpatialAnchorHandle_t * p_Handle_بهر);
	EVRSpatialAnchorError (OPENVR_FNTABLE_CALLTYPE *CreateSpatialAnchorFromPose)(Tracked_Device_شاخص_t un_Device_شاخص, ETrackingUniverseOrigin eOrigin, بنية SpatialAnchorPose_t * pPose, SpatialAnchorHandle_t * p_Handle_بهر);
	EVRSpatialAnchorError (OPENVR_FNTABLE_CALLTYPE *GetSpatialAnchorPose)(SpatialAnchorHandle_t unHandle, ETrackingUniverseOrigin eOrigin, بنية SpatialAnchorPose_t * p_Pose_بهر);
	EVRSpatialAnchorError (OPENVR_FNTABLE_CALLTYPE *GetSpatialAnchorDescriptor)(SpatialAnchorHandle_t unHandle, حرف * pch_Descriptor_بهر, uint32_t * pun_Descriptor_بفر_Len_دننه_بهر);
};

بنية VR_IVRDebug_Fn_جدول
{
	EVRDebugError (OPENVR_FNTABLE_CALLTYPE *EmitVrProfilerEvent)(حرف * pch_پیغام);
	EVRDebugError (OPENVR_FNTABLE_CALLTYPE *BeginVrProfilerEvent)(VrProfilerEventHandle_t * p_Handle_بهر);
	EVRDebugError (OPENVR_FNTABLE_CALLTYPE *پای_Vr_Profiler_Event)(VrProfilerEventHandle_t hHandle, حرف * pch_پیغام);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *DriverDebugRequest)(Tracked_Device_شاخص_t un_Device_شاخص, حرف * pchRequest, حرف * pch_Response_بفر, uint32_t un_Response_بفر_اندازه);
};

بنية VR_IVRProperties_Fn_جدول
{
	ETrackedPropertyError (OPENVR_FNTABLE_CALLTYPE *ReadPropertyBatch)(PropertyContainerHandle_t ulContainerHandle, بنية PropertyRead_t * pBatch, uint32_t un_Batch_ثبت_شمېر);
	ETrackedPropertyError (OPENVR_FNTABLE_CALLTYPE *WritePropertyBatch)(PropertyContainerHandle_t ulContainerHandle, بنية PropertyWrite_t * pBatch, uint32_t un_Batch_ثبت_شمېر);
	حرف * (OPENVR_FNTABLE_CALLTYPE *GetPropErrorNameFromEnum)(ETrackedPropertyError error);
	PropertyContainerHandle_t (OPENVR_FNTABLE_CALLTYPE *Tracked_Device_منزل_Property_Container)(Tracked_Device_شاخص_t nDevice);
};

بنية VR_IVRPaths_Fn_جدول
{
	ETrackedPropertyError (OPENVR_FNTABLE_CALLTYPE *Read_لار_Batch)(PropertyContainerHandle_t ul_ریښه_Handle, بنية لار_Read_t * pBatch, uint32_t un_Batch_ثبت_شمېر);
	ETrackedPropertyError (OPENVR_FNTABLE_CALLTYPE *Write_لار_Batch)(PropertyContainerHandle_t ul_ریښه_Handle, بنية لار_Write_t * pBatch, uint32_t un_Batch_ثبت_شمېر);
	ETrackedPropertyError (OPENVR_FNTABLE_CALLTYPE *String_منزل_Handle)(لار_Handle_t * pHandle, حرف * pch_لار);
	ETrackedPropertyError (OPENVR_FNTABLE_CALLTYPE *Handle_منزل_String)(لار_Handle_t pHandle, حرف * pch_بفر, uint32_t un_بفر_اندازه, uint32_t * pun_بفر_اندازه_کارول_شوی);
};

بنية VR_IVRBlock_کتار_Fn_جدول
{
	EBlock_کتار_Error (OPENVR_FNTABLE_CALLTYPE *Create)(PropertyContainerHandle_t * pul_کتار_Handle, حرف * pch_لار, uint32_t un_بلاک_معلومات_اندازه, uint32_t un_بلاک_سرلیک_اندازه, uint32_t un_بلاک_شمېر, uint32_t unFlags);
	EBlock_کتار_Error (OPENVR_FNTABLE_CALLTYPE *Connect)(PropertyContainerHandle_t * pul_کتار_Handle, حرف * pch_لار);
	EBlock_کتار_Error (OPENVR_FNTABLE_CALLTYPE *Destroy)(PropertyContainerHandle_t ul_کتار_Handle);
	EBlock_کتار_Error (OPENVR_FNTABLE_CALLTYPE *Acquire_Write_Only_بلاک)(PropertyContainerHandle_t ul_کتار_Handle, PropertyContainerHandle_t * pul_بلاک_Handle, فراغ ** ppv_بفر);
	EBlock_کتار_Error (OPENVR_FNTABLE_CALLTYPE *Release_Write_Only_بلاک)(PropertyContainerHandle_t ul_کتار_Handle, PropertyContainerHandle_t ul_بلاک_Handle);
	EBlock_کتار_Error (OPENVR_FNTABLE_CALLTYPE *Wait_And_Acquire_Read_Only_بلاک)(PropertyContainerHandle_t ul_کتار_Handle, PropertyContainerHandle_t * pul_بلاک_Handle, فراغ ** ppv_بفر, EBlock_کتار_Read_Type eReadType, uint32_t unTimeoutMs);
	EBlock_کتار_Error (OPENVR_FNTABLE_CALLTYPE *Acquire_Read_Only_بلاک)(PropertyContainerHandle_t ul_کتار_Handle, PropertyContainerHandle_t * pul_بلاک_Handle, فراغ ** ppv_بفر, EBlock_کتار_Read_Type eReadType);
	EBlock_کتار_Error (OPENVR_FNTABLE_CALLTYPE *Release_Read_Only_بلاک)(PropertyContainerHandle_t ul_کتار_Handle, PropertyContainerHandle_t ul_بلاک_Handle);
	EBlock_کتار_Error (OPENVR_FNTABLE_CALLTYPE *کتار_Has_Reader)(PropertyContainerHandle_t ul_کتار_Handle, bool * pbHasReaders);
};


#إذا 0
// Global entry points
S_API intptr_t VR_Init_دننی( EVRInitError *peError, EVRApplicationType eType );
S_API فراغ VR_Shutdown_دننی();
S_API bool VR_IsHmdPresent();
S_API intptr_t VR_GetGenericInterface( ثابت حرف *pch_Interface_نسخه, EVRInitError *peError );
S_API bool VR_IsRuntimeInstalled();
S_API ثابت حرف * VR_Get_VRInit_Error_As_نښه( EVRInitError error );
S_API ثابت حرف * VR_GetVRInitErrorAsEnglishDescription( EVRInitError error );
#د_که_پای

#د_که_پای // __OPENVR_API_FLAT_H__


