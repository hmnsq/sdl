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

#اگر_تعریف_نشده __OPENVR_API_FLAT_H__
#تعریف_کن __OPENVR_API_FLAT_H__
#إذا defined( _WIN32 ) || defined( __clang__ )
#رهنمود once
#پایان_اگر

#اگر_تعریف_شده __cplusplus
#تعریف_کن EXTERN_C خارجي "C"
#وإلا
#تعریف_کن EXTERN_C
#پایان_اگر

#إذا defined( _WIN32 )
#تعریف_کن OPENVR_FNTABLE_CALLTYPE __stdcall
#وإلا
#تعریف_کن OPENVR_FNTABLE_CALLTYPE 
#پایان_اگر

// OPENVR API export macro
#إذا defined( _WIN32 ) && !defined( _X360 )
	#إذا defined( OPENVR_API_EXPORTS )
	#تعریف_کن S_API EXTERN_C __declspec( dllexport )
	#وإلاإذا defined( OPENVR_API_NODLL )
	#تعریف_کن S_API EXTERN_C
	#وإلا
	#تعریف_کن S_API خارجي "C" __declspec( dllimport ) 
	#پایان_اگر // OPENVR_API_EXPORTS
#وإلاإذا defined( __GNUC__ )
	#إذا defined( OPENVR_API_EXPORTS )
	#تعریف_کن S_API EXTERN_C __attribute__ ((visibility("default")))
	#وإلا
	#تعریف_کن S_API EXTERN_C
	#پایان_اگر // OPENVR_API_EXPORTS
#وإلا // !WIN32
	#إذا defined( OPENVR_API_EXPORTS )
	#تعریف_کن S_API EXTERN_C
	#وإلا
	#تعریف_کن S_API EXTERN_C
	#پایان_اگر // OPENVR_API_EXPORTS
#پایان_اگر

#اگر_تعریف_نشده USE_SDL
#ضمن <stdint.h>

#إذا defined( __WIN32 )
تعريفنوع حرف bool;
#وإلا
#ضمن <stdbool.h>
#پایان_اگر
#پایان_اگر // USE_SDL

// OpenVR Constants

ساكن ثابت بیعلامت دراز k_nDriverNone = 4294967295;
ساكن ثابت بیعلامت دراز k_un_Max_Driver_Debug_Response_اندازه = 32768;
ساكن ثابت بیعلامت دراز k_un_Tracked_Device_شاخص_Hmd = 0;
ساكن ثابت بیعلامت دراز k_un_Max_Tracked_Device_شمار = 64;
ساكن ثابت بیعلامت دراز k_un_Tracked_Device_شاخص_Other = 4294967294;
ساكن ثابت بیعلامت دراز k_un_Tracked_Device_شاخص_Invalid = 4294967295;
ساكن ثابت بیعلامت دراز دراز k_ulInvalidPropertyContainer = 0;
ساكن ثابت بیعلامت دراز k_un_Invalid_Property_برچسب = 0;
ساكن ثابت بیعلامت دراز دراز k_ulInvalidDriverHandle = 0;
ساكن ثابت بیعلامت دراز k_un_Float_Property_برچسب = 1;
ساكن ثابت بیعلامت دراز k_un_Int32_Property_برچسب = 2;
ساكن ثابت بیعلامت دراز k_un_Uint64_Property_برچسب = 3;
ساكن ثابت بیعلامت دراز k_un_Bool_Property_برچسب = 4;
ساكن ثابت بیعلامت دراز k_un_String_Property_برچسب = 5;
ساكن ثابت بیعلامت دراز k_un_Error_Property_برچسب = 6;
ساكن ثابت بیعلامت دراز k_un_Double_Property_برچسب = 7;
ساكن ثابت بیعلامت دراز k_un_Hmd_Matrix34_Property_برچسب = 20;
ساكن ثابت بیعلامت دراز k_un_Hmd_Matrix44_Property_برچسب = 21;
ساكن ثابت بیعلامت دراز k_un_Hmd_Vector3_Property_برچسب = 22;
ساكن ثابت بیعلامت دراز k_un_Hmd_Vector4_Property_برچسب = 23;
ساكن ثابت بیعلامت دراز k_un_Hmd_Vector2_Property_برچسب = 24;
ساكن ثابت بیعلامت دراز k_un_Hmd_Quad_Property_برچسب = 25;
ساكن ثابت بیعلامت دراز k_un_Hidden_Area_Property_برچسب = 30;
ساكن ثابت بیعلامت دراز k_un_مسیر_Handle_Info_برچسب = 31;
ساكن ثابت بیعلامت دراز k_un_Action_Property_برچسب = 32;
ساكن ثابت بیعلامت دراز k_un_درون_داد_مقدار_Property_برچسب = 33;
ساكن ثابت بیعلامت دراز k_un_Wildcard_Property_برچسب = 34;
ساكن ثابت بیعلامت دراز k_un_Haptic_Vibration_Property_برچسب = 35;
ساكن ثابت بیعلامت دراز k_un_Skeleton_Property_برچسب = 36;
ساكن ثابت بیعلامت دراز k_un_Spatial_Anchor_Pose_Property_برچسب = 40;
ساكن ثابت بیعلامت دراز k_un_Json_Property_برچسب = 41;
ساكن ثابت بیعلامت دراز k_un_فعال_Action_مجموعه_Property_برچسب = 42;
ساكن ثابت بیعلامت دراز k_un_Open_VRInternal_Reserved_شروع = 1000;
ساكن ثابت بیعلامت دراز k_un_Open_VRInternal_Reserved_انتها = 10000;
ساكن ثابت بیعلامت دراز k_un_Max_Property_String_اندازه = 32768;
ساكن ثابت بیعلامت دراز دراز k_ulInvalidActionHandle = 0;
ساكن ثابت بیعلامت دراز دراز k_ul_Invalid_Action_مجموعه_Handle = 0;
ساكن ثابت بیعلامت دراز دراز k_ul_Invalid_درون_داد_مقدار_Handle = 0;
ساكن ثابت بیعلامت دراز k_un_Controller_State_Axis_شمار = 5;
ساكن ثابت بیعلامت دراز دراز k_ulOverlayHandleInvalid = 0;
ساكن ثابت بیعلامت دراز k_unMaxDistortionFunctionParameters = 8;
ساكن ثابت بیعلامت دراز k_unScreenshotHandleInvalid = 0;
ساكن ثابت حرف * IVRSystem_نسخه = "IVRSystem_022";
ساكن ثابت حرف * IVRExtended_Display_نسخه = "IVRExtendedDisplay_001";
ساكن ثابت حرف * IVRTracked_Camera_نسخه = "IVRTrackedCamera_006";
ساكن ثابت بیعلامت دراز k_un_Max_Application_کلید_درازی = 128;
ساكن ثابت حرف * k_pch_MimeType_HomeApp = "vr/home";
ساكن ثابت حرف * k_pch_MimeType_GameTheater = "vr/game_theater";
ساكن ثابت حرف * IVRApplications_نسخه = "IVRApplications_007";
ساكن ثابت حرف * IVRChaperone_نسخه = "IVRChaperone_004";
ساكن ثابت حرف * IVRChaperone_راهاندازی_نسخه = "IVRChaperoneSetup_006";
ساكن ثابت حرف * IVRCompositor_نسخه = "IVRCompositor_027";
ساكن ثابت بیعلامت دراز k_un_VROverlay_Max_کلید_درازی = 128;
ساكن ثابت بیعلامت دراز k_un_VROverlay_Max_Name_درازی = 128;
ساكن ثابت بیعلامت دراز k_un_Max_Overlay_شمار = 128;
ساكن ثابت بیعلامت دراز k_un_Max_Overlay_Intersection_ماسک_Primitives_شمار = 32;
ساكن ثابت حرف * IVROverlay_نسخه = "IVROverlay_026";
ساكن ثابت حرف * IVROverlay_View_نسخه = "IVROverlayView_003";
ساكن ثابت بیعلامت دراز k_un_Headset_View_Max_عرض = 3840;
ساكن ثابت بیعلامت دراز k_un_Headset_View_Max_ارتفاع = 2160;
ساكن ثابت حرف * k_pch_Headset_View_Overlay_کلید = "system.HeadsetView";
ساكن ثابت حرف * IVRHeadset_View_نسخه = "IVRHeadsetView_001";
ساكن ثابت حرف * k_pch_Controller_Component_GDC2015 = "gdc2015";
ساكن ثابت حرف * k_pch_Controller_Component_پایه = "base";
ساكن ثابت حرف * k_pch_Controller_Component_Tip = "tip";
ساكن ثابت حرف * k_pch_Controller_Component_OpenXR_Aim = "openxr_aim";
ساكن ثابت حرف * k_pch_Controller_Component_HandGrip = "handgrip";
ساكن ثابت حرف * k_pch_Controller_Component_OpenXR_Grip = "openxr_grip";
ساكن ثابت حرف * k_pch_Controller_Component_OpenXR_HandModel = "openxr_handmodel";
ساكن ثابت حرف * k_pch_Controller_Component_وضعیت = "status";
ساكن ثابت حرف * IVRRender_Models_نسخه = "IVRRenderModels_006";
ساكن ثابت بیعلامت دراز k_un_Notification_متن_Max_اندازه = 256;
ساكن ثابت حرف * IVRNotifications_نسخه = "IVRNotifications_002";
ساكن ثابت بیعلامت دراز k_un_Max_Settings_کلید_درازی = 128;
ساكن ثابت حرف * IVRSettings_نسخه = "IVRSettings_003";
ساكن ثابت حرف * k_pch_SteamVR_Section = "steamvr";
ساكن ثابت حرف * k_pch_SteamVR_RequireHmd_String = "requireHmd";
ساكن ثابت حرف * k_pch_Steam_VR_Forced_Driver_کلید_String = "forcedDriver";
ساكن ثابت حرف * k_pch_Steam_VR_Forced_Hmd_کلید_String = "forcedHmd";
ساكن ثابت حرف * k_pch_SteamVR_DisplayDebug_Bool = "displayDebug";
ساكن ثابت حرف * k_pch_SteamVR_DebugProcessPipe_String = "debugProcessPipe";
ساكن ثابت حرف * k_pch_SteamVR_DisplayDebugX_Int32 = "displayDebugX";
ساكن ثابت حرف * k_pch_SteamVR_DisplayDebugY_Int32 = "displayDebugY";
ساكن ثابت حرف * k_pch_Steam_VR_Send_System_Button_مقصد_All_Apps_Bool = "sendSystemButtonToAllApps";
ساكن ثابت حرف * k_pch_SteamVR_LogLevel_Int32 = "loglevel";
ساكن ثابت حرف * k_pch_SteamVR_IPD_Float = "ipd";
ساكن ثابت حرف * k_pch_SteamVR_Background_String = "background";
ساكن ثابت حرف * k_pch_SteamVR_BackgroundUseDomeProjection_Bool = "backgroundUseDomeProjection";
ساكن ثابت حرف * k_pch_Steam_VR_Background_Camera_ارتفاع_Float = "backgroundCameraHeight";
ساكن ثابت حرف * k_pch_SteamVR_BackgroundDomeRadius_Float = "backgroundDomeRadius";
ساكن ثابت حرف * k_pch_SteamVR_GridColor_String = "gridColor";
ساكن ثابت حرف * k_pch_SteamVR_PlayAreaColor_String = "playAreaColor";
ساكن ثابت حرف * k_pch_SteamVR_TrackingLossColor_String = "trackingLossColor";
ساكن ثابت حرف * k_pch_SteamVR_ShowStage_Bool = "showStage";
ساكن ثابت حرف * k_pch_SteamVR_DrawTrackingReferences_Bool = "drawTrackingReferences";
ساكن ثابت حرف * k_pch_Steam_VR_Activate_مضرب_Drivers_Bool = "activateMultipleDrivers";
ساكن ثابت حرف * k_pch_SteamVR_UsingSpeakers_Bool = "usingSpeakers";
ساكن ثابت حرف * k_pch_Steam_VR_Speakers_Forward_Yaw_جابه_جایی_Degrees_Float = "speakersForwardYawOffsetDegrees";
ساكن ثابت حرف * k_pch_Steam_VR_پایه_Station_Power_Management_Int32 = "basestationPowerManagement";
ساكن ثابت حرف * k_pch_Steam_VR_Show_پایه_Station_Power_Management_Tip_Int32 = "ShowBaseStationPowerManagementTip";
ساكن ثابت حرف * k_pch_SteamVR_NeverKillProcesses_Bool = "neverKillProcesses";
ساكن ثابت حرف * k_pch_SteamVR_SupersampleScale_Float = "supersampleScale";
ساكن ثابت حرف * k_pch_SteamVR_MaxRecommendedResolution_Int32 = "maxRecommendedResolution";
ساكن ثابت حرف * k_pch_SteamVR_MotionSmoothing_Bool = "motionSmoothing";
ساكن ثابت حرف * k_pch_SteamVR_MotionSmoothingOverride_Int32 = "motionSmoothingOverride";
ساكن ثابت حرف * k_pch_Steam_VR_قابها_مقصد_Throttle_Int32 = "framesToThrottle";
ساكن ثابت حرف * k_pch_Steam_VR_Additional_قابها_مقصد_Predict_Int32 = "additionalFramesToPredict";
ساكن ثابت حرف * k_pch_SteamVR_WorldScale_Float = "worldScale";
ساكن ثابت حرف * k_pch_SteamVR_FovScale_Int32 = "fovScale";
ساكن ثابت حرف * k_pch_SteamVR_DisableAsyncReprojection_Bool = "disableAsync";
ساكن ثابت حرف * k_pch_SteamVR_ForceFadeOnBadTracking_Bool = "forceFadeOnBadTracking";
ساكن ثابت حرف * k_pch_SteamVR_DefaultMirrorView_Int32 = "mirrorView";
ساكن ثابت حرف * k_pch_SteamVR_ShowLegacyMirrorView_Bool = "showLegacyMirrorView";
ساكن ثابت حرف * k_pch_SteamVR_MirrorViewVisibility_Bool = "showMirrorView";
ساكن ثابت حرف * k_pch_Steam_VR_Mirror_View_Display_نما_Int32 = "mirrorViewDisplayMode";
ساكن ثابت حرف * k_pch_SteamVR_MirrorViewEye_Int32 = "mirrorViewEye";
ساكن ثابت حرف * k_pch_SteamVR_MirrorViewGeometry_String = "mirrorViewGeometry";
ساكن ثابت حرف * k_pch_SteamVR_MirrorViewGeometryMaximized_String = "mirrorViewGeometryMaximized";
ساكن ثابت حرف * k_pch_Steam_VR_Perf_گراف_Visibility_Bool = "showPerfGraph";
ساكن ثابت حرف * k_pch_Steam_VR_شروع_Monitor_From_App_Launch = "startMonitorFromAppLaunch";
ساكن ثابت حرف * k_pch_Steam_VR_شروع_Compositor_From_App_Launch_Bool = "startCompositorFromAppLaunch";
ساكن ثابت حرف * k_pch_Steam_VR_شروع_Dashboard_From_App_Launch_Bool = "startDashboardFromAppLaunch";
ساكن ثابت حرف * k_pch_Steam_VR_شروع_Overlay_Apps_From_Dashboard_Bool = "startOverlayAppsFromDashboard";
ساكن ثابت حرف * k_pch_SteamVR_EnableHomeApp = "enableHomeApp";
ساكن ثابت حرف * k_pch_Steam_VR_چرخه_Background_Image_زمان_Sec_Int32 = "CycleBackgroundImageTimeSec";
ساكن ثابت حرف * k_pch_SteamVR_RetailDemo_Bool = "retailDemo";
ساكن ثابت حرف * k_pch_Steam_VR_Ipd_جابه_جایی_Float = "ipdOffset";
ساكن ثابت حرف * k_pch_SteamVR_AllowSupersampleFiltering_Bool = "allowSupersampleFiltering";
ساكن ثابت حرف * k_pch_SteamVR_SupersampleManualOverride_Bool = "supersampleManualOverride";
ساكن ثابت حرف * k_pch_SteamVR_EnableLinuxVulkanAsync_Bool = "enableLinuxVulkanAsync";
ساكن ثابت حرف * k_pch_Steam_VR_Allow_Display_Locked_نما_Bool = "allowDisplayLockedMode";
ساكن ثابت حرف * k_pch_SteamVR_HaveStartedTutorialForNativeChaperoneDriver_Bool = "haveStartedTutorialForNativeChaperoneDriver";
ساكن ثابت حرف * k_pch_SteamVR_ForceWindows32bitVRMonitor = "forceWindows32BitVRMonitor";
ساكن ثابت حرف * k_pch_Steam_VR_Debug_درون_داد_Binding = "debugInputBinding";
ساكن ثابت حرف * k_pch_Steam_VR_Do_Not_Fade_مقصد_Grid = "doNotFadeToGrid";
ساكن ثابت حرف * k_pch_Steam_VR_Render_Camera_نما = "renderCameraMode";
ساكن ثابت حرف * k_pch_SteamVR_EnableSharedResourceJournaling = "enableSharedResourceJournaling";
ساكن ثابت حرف * k_pch_Steam_VR_Enable_امن_نما = "enableSafeMode";
ساكن ثابت حرف * k_pch_Steam_VR_Preferred_Refresh_نرخ = "preferredRefreshRate";
ساكن ثابت حرف * k_pch_Steam_VR_آخرین_نسخه_Notice = "lastVersionNotice";
ساكن ثابت حرف * k_pch_Steam_VR_آخرین_نسخه_Notice_Date = "lastVersionNoticeDate";
ساكن ثابت حرف * k_pch_SteamVR_HmdDisplayColorGainR_Float = "hmdDisplayColorGainR";
ساكن ثابت حرف * k_pch_SteamVR_HmdDisplayColorGainG_Float = "hmdDisplayColorGainG";
ساكن ثابت حرف * k_pch_SteamVR_HmdDisplayColorGainB_Float = "hmdDisplayColorGainB";
ساكن ثابت حرف * k_pch_SteamVR_CustomIconStyle_String = "customIconStyle";
ساكن ثابت حرف * k_pch_SteamVR_CustomOffIconStyle_String = "customOffIconStyle";
ساكن ثابت حرف * k_pch_SteamVR_CustomIconForceUpdate_String = "customIconForceUpdate";
ساكن ثابت حرف * k_pch_Steam_VR_Allow_Global_Action_مجموعه_اولویت = "globalActionSetPriority";
ساكن ثابت حرف * k_pch_SteamVR_OverlayRenderQuality = "overlayRenderQuality_2";
ساكن ثابت حرف * k_pch_Steam_VR_بلوک_Oculus_SDKOn_Open_VRLaunch_Option_Bool = "blockOculusSDKOnOpenVRLaunchOption";
ساكن ثابت حرف * k_pch_Steam_VR_بلوک_Oculus_SDKOn_All_Launches_Bool = "blockOculusSDKOnAllLaunches";
ساكن ثابت حرف * k_pch_SteamVR_HDCPLegacyCompatibility_Bool = "hdcp14legacyCompatibility";
ساكن ثابت حرف * k_pch_Steam_VR_Display_پورت_Training_نما_Int = "displayPortTrainingMode";
ساكن ثابت حرف * k_pch_SteamVR_UsePrism_Bool = "usePrism";
ساكن ثابت حرف * k_pch_مستقیم_نما_Section = "direct_mode";
ساكن ثابت حرف * k_pch_مستقیم_نما_Enable_Bool = "enable";
ساكن ثابت حرف * k_pch_مستقیم_نما_شمار_Int32 = "count";
ساكن ثابت حرف * k_pch_مستقیم_نما_Edid_Vid_Int32 = "edidVid";
ساكن ثابت حرف * k_pch_مستقیم_نما_Edid_Pid_Int32 = "edidPid";
ساكن ثابت حرف * k_pch_Lighthouse_Section = "driver_lighthouse";
ساكن ثابت حرف * k_pch_Lighthouse_DisableIMU_Bool = "disableimu";
ساكن ثابت حرف * k_pch_Lighthouse_DisableIMUExceptHMD_Bool = "disableimuexcepthmd";
ساكن ثابت حرف * k_pch_Lighthouse_UseDisambiguation_String = "usedisambiguation";
ساكن ثابت حرف * k_pch_Lighthouse_DisambiguationDebug_Int32 = "disambiguationdebug";
ساكن ثابت حرف * k_pch_Lighthouse_PrimaryBasestation_Int32 = "primarybasestation";
ساكن ثابت حرف * k_pch_Lighthouse_DBHistory_Bool = "dbhistory";
ساكن ثابت حرف * k_pch_Lighthouse_EnableBluetooth_Bool = "enableBluetooth";
ساكن ثابت حرف * k_pch_Lighthouse_Power_Managed_پایه_Stations_String = "PowerManagedBaseStations";
ساكن ثابت حرف * k_pch_Lighthouse_Power_Managed_پایه_Stations2_String = "PowerManagedBaseStations2";
ساكن ثابت حرف * k_pch_Lighthouse_Inactivity_Timeout_For_پایه_Stations_Int32 = "InactivityTimeoutForBaseStations";
ساكن ثابت حرف * k_pch_Lighthouse_EnableImuFallback_Bool = "enableImuFallback";
ساكن ثابت حرف * k_pch_Null_Section = "driver_null";
ساكن ثابت حرف * k_pch_Null_Serial_عدد_String = "serialNumber";
ساكن ثابت حرف * k_pch_Null_Model_عدد_String = "modelNumber";
ساكن ثابت حرف * k_pch_Null_پنجره_X_Int32 = "windowX";
ساكن ثابت حرف * k_pch_Null_پنجره_Y_Int32 = "windowY";
ساكن ثابت حرف * k_pch_Null_پنجره_عرض_Int32 = "windowWidth";
ساكن ثابت حرف * k_pch_Null_پنجره_ارتفاع_Int32 = "windowHeight";
ساكن ثابت حرف * k_pch_Null_Render_عرض_Int32 = "renderWidth";
ساكن ثابت حرف * k_pch_Null_Render_ارتفاع_Int32 = "renderHeight";
ساكن ثابت حرف * k_pch_Null_Seconds_From_Vsync_مقصد_Photons_Float = "secondsFromVsyncToPhotons";
ساكن ثابت حرف * k_pch_Null_DisplayFrequency_Float = "displayFrequency";
ساكن ثابت حرف * k_pch_WindowsMR_Section = "driver_holographic";
ساكن ثابت حرف * k_pch_UserInterface_Section = "userinterface";
ساكن ثابت حرف * k_pch_User_Interface_وضعیت_Always_On_بالاترین_Bool = "StatusAlwaysOnTop";
ساكن ثابت حرف * k_pch_User_Interface_Minimize_مقصد_Tray_Bool = "MinimizeToTray";
ساكن ثابت حرف * k_pch_User_Interface_Hide_Popups_When_وضعیت_Minimized_Bool = "HidePopupsWhenStatusMinimized";
ساكن ثابت حرف * k_pch_UserInterface_Screenshots_Bool = "screenshots";
ساكن ثابت حرف * k_pch_UserInterface_ScreenshotType_Int = "screenshotType";
ساكن ثابت حرف * k_pch_Notifications_Section = "notifications";
ساكن ثابت حرف * k_pch_Notifications_DoNotDisturb_Bool = "DoNotDisturb";
ساكن ثابت حرف * k_pch_Keyboard_Section = "keyboard";
ساكن ثابت حرف * k_pch_Keyboard_TutorialCompletions = "TutorialCompletions";
ساكن ثابت حرف * k_pch_Keyboard_ScaleX = "ScaleX";
ساكن ثابت حرف * k_pch_Keyboard_ScaleY = "ScaleY";
ساكن ثابت حرف * k_pch_Keyboard_جابه_جایی_چپ_X = "OffsetLeftX";
ساكن ثابت حرف * k_pch_Keyboard_جابه_جایی_راست_X = "OffsetRightX";
ساكن ثابت حرف * k_pch_Keyboard_جابه_جایی_Y = "OffsetY";
ساكن ثابت حرف * k_pch_Keyboard_Smoothing = "Smoothing";
ساكن ثابت حرف * k_pch_Perf_Section = "perfcheck";
ساكن ثابت حرف * k_pch_Perf_Perf_گراف_درون_HMD_Bool = "perfGraphInHMD";
ساكن ثابت حرف * k_pch_Perf_AllowTimingStore_Bool = "allowTimingStore";
ساكن ثابت حرف * k_pch_Perf_SaveTimingsOnExit_Bool = "saveTimingsOnExit";
ساكن ثابت حرف * k_pch_Perf_Test_داده_Float = "perfTestData";
ساكن ثابت حرف * k_pch_Perf_GPUProfiling_Bool = "GPUProfiling";
ساكن ثابت حرف * k_pch_CollisionBounds_Section = "collisionBounds";
ساكن ثابت حرف * k_pch_CollisionBounds_Style_Int32 = "CollisionBoundsStyle";
ساكن ثابت حرف * k_pch_CollisionBounds_GroundPerimeterOn_Bool = "CollisionBoundsGroundPerimeterOn";
ساكن ثابت حرف * k_pch_CollisionBounds_CenterMarkerOn_Bool = "CollisionBoundsCenterMarkerOn";
ساكن ثابت حرف * k_pch_CollisionBounds_PlaySpaceOn_Bool = "CollisionBoundsPlaySpaceOn";
ساكن ثابت حرف * k_pch_Collision_Bounds_Fade_فاصله_Float = "CollisionBoundsFadeDistance";
ساكن ثابت حرف * k_pch_Collision_Bounds_Wall_ارتفاع_Float = "CollisionBoundsWallHeight";
ساكن ثابت حرف * k_pch_CollisionBounds_ColorGammaR_Int32 = "CollisionBoundsColorGammaR";
ساكن ثابت حرف * k_pch_CollisionBounds_ColorGammaG_Int32 = "CollisionBoundsColorGammaG";
ساكن ثابت حرف * k_pch_CollisionBounds_ColorGammaB_Int32 = "CollisionBoundsColorGammaB";
ساكن ثابت حرف * k_pch_CollisionBounds_ColorGammaA_Int32 = "CollisionBoundsColorGammaA";
ساكن ثابت حرف * k_pch_CollisionBounds_EnableDriverImport = "enableDriverBoundsImport";
ساكن ثابت حرف * k_pch_Camera_Section = "camera";
ساكن ثابت حرف * k_pch_Camera_EnableCamera_Bool = "enableCamera";
ساكن ثابت حرف * k_pch_Camera_ShowOnController_Bool = "showOnController";
ساكن ثابت حرف * k_pch_Camera_EnableCameraForCollisionBounds_Bool = "enableCameraForCollisionBounds";
ساكن ثابت حرف * k_pch_Camera_جا_View_Int32 = "roomView";
ساكن ثابت حرف * k_pch_Camera_BoundsColorGammaR_Int32 = "cameraBoundsColorGammaR";
ساكن ثابت حرف * k_pch_Camera_BoundsColorGammaG_Int32 = "cameraBoundsColorGammaG";
ساكن ثابت حرف * k_pch_Camera_BoundsColorGammaB_Int32 = "cameraBoundsColorGammaB";
ساكن ثابت حرف * k_pch_Camera_BoundsColorGammaA_Int32 = "cameraBoundsColorGammaA";
ساكن ثابت حرف * k_pch_Camera_BoundsStrength_Int32 = "cameraBoundsStrength";
ساكن ثابت حرف * k_pch_Camera_جا_View_Style_Int32 = "roomViewStyle";
ساكن ثابت حرف * k_pch_audio_Section = "audio";
ساكن ثابت حرف * k_pch_audio_مجموعه_Os_Default_Playback_Device_Bool = "setOsDefaultPlaybackDevice";
ساكن ثابت حرف * k_pch_audio_EnablePlaybackDeviceOverride_Bool = "enablePlaybackDeviceOverride";
ساكن ثابت حرف * k_pch_audio_PlaybackDeviceOverride_String = "playbackDeviceOverride";
ساكن ثابت حرف * k_pch_audio_PlaybackDeviceOverrideName_String = "playbackDeviceOverrideName";
ساكن ثابت حرف * k_pch_audio_مجموعه_Os_Default_Recording_Device_Bool = "setOsDefaultRecordingDevice";
ساكن ثابت حرف * k_pch_audio_EnableRecordingDeviceOverride_Bool = "enableRecordingDeviceOverride";
ساكن ثابت حرف * k_pch_audio_RecordingDeviceOverride_String = "recordingDeviceOverride";
ساكن ثابت حرف * k_pch_audio_RecordingDeviceOverrideName_String = "recordingDeviceOverrideName";
ساكن ثابت حرف * k_pch_audio_EnablePlaybackMirror_Bool = "enablePlaybackMirror";
ساكن ثابت حرف * k_pch_audio_PlaybackMirrorDevice_String = "playbackMirrorDevice";
ساكن ثابت حرف * k_pch_audio_PlaybackMirrorDeviceName_String = "playbackMirrorDeviceName";
ساكن ثابت حرف * k_pch_audio_OldPlaybackMirrorDevice_String = "onPlaybackMirrorDevice";
ساكن ثابت حرف * k_pch_audio_فعال_Mirror_Device_String = "activePlaybackMirrorDevice";
ساكن ثابت حرف * k_pch_audio_EnablePlaybackMirrorIndependentVolume_Bool = "enablePlaybackMirrorIndependentVolume";
ساكن ثابت حرف * k_pch_audio_آخرین_Hmd_Playback_Device_Id_String = "lastHmdPlaybackDeviceId";
ساكن ثابت حرف * k_pch_audio_VIVEHDMIGain = "viveHDMIGain";
ساكن ثابت حرف * k_pch_audio_DualSpeakerAndJackOutput_Bool = "dualSpeakerAndJackOutput";
ساكن ثابت حرف * k_pch_audio_MuteMicMonitor_Bool = "muteMicMonitor";
ساكن ثابت حرف * k_pch_Power_Section = "power";
ساكن ثابت حرف * k_pch_Power_PowerOffOnExit_Bool = "powerOffOnExit";
ساكن ثابت حرف * k_pch_Power_TurnOffScreensTimeout_Float = "turnOffScreensTimeout";
ساكن ثابت حرف * k_pch_Power_TurnOffControllersTimeout_Float = "turnOffControllersTimeout";
ساكن ثابت حرف * k_pch_Power_Return_مقصد_Watchdog_Timeout_Float = "returnToWatchdogTimeout";
ساكن ثابت حرف * k_pch_Power_AutoLaunchSteamVROnButtonPress = "autoLaunchSteamVROnButtonPress";
ساكن ثابت حرف * k_pch_Power_PauseCompositorOnStandby_Bool = "pauseCompositorOnStandby";
ساكن ثابت حرف * k_pch_Dashboard_Section = "dashboard";
ساكن ثابت حرف * k_pch_Dashboard_EnableDashboard_Bool = "enableDashboard";
ساكن ثابت حرف * k_pch_Dashboard_Arcade_نما_Bool = "arcadeMode";
ساكن ثابت حرف * k_pch_Dashboard_Position = "position";
ساكن ثابت حرف * k_pch_Dashboard_DesktopScale = "desktopScale";
ساكن ثابت حرف * k_pch_Dashboard_DashboardScale = "dashboardScale";
ساكن ثابت حرف * k_pch_Dashboard_UseStandaloneSystemLayer = "standaloneSystemLayer";
ساكن ثابت حرف * k_pch_Dashboard_StickyDashboard = "stickyDashboard";
ساكن ثابت حرف * k_pch_modelskin_Section = "modelskins";
ساكن ثابت حرف * k_pch_Driver_Enable_Bool = "enable";
ساكن ثابت حرف * k_pch_Driver_BlockedBySafemode_Bool = "blocked_by_safe_mode";
ساكن ثابت حرف * k_pch_Driver_بارگیری_اولویت_Int32 = "loadPriority";
ساكن ثابت حرف * k_pch_WebInterface_Section = "WebInterface";
ساكن ثابت حرف * k_pch_VRWebHelper_Section = "VRWebHelper";
ساكن ثابت حرف * k_pch_VRWebHelper_DebuggerEnabled_Bool = "DebuggerEnabled";
ساكن ثابت حرف * k_pch_VRWeb_Helper_Debugger_پورت_Int32 = "DebuggerPort";
ساكن ثابت حرف * k_pch_TrackingOverride_Section = "TrackingOverrides";
ساكن ثابت حرف * k_pch_App_BindingAutosaveURLSuffix_String = "AutosaveURL";
ساكن ثابت حرف * k_pch_App_BindingLegacyAPISuffix_String = "_legacy";
ساكن ثابت حرف * k_pch_App_BindingSteamVRInputAPISuffix_String = "_steamvrinput";
ساكن ثابت حرف * k_pch_App_BindingOpenXRAPISuffix_String = "_openxr";
ساكن ثابت حرف * k_pch_App_BindingCurrentURLSuffix_String = "CurrentURL";
ساكن ثابت حرف * k_pch_App_Binding_قبلی_URLSuffix_String = "PreviousURL";
ساكن ثابت حرف * k_pch_App_Need_مقصد_Update_Autosave_Suffix_Bool = "NeedToUpdateAutosave";
ساكن ثابت حرف * k_pch_App_DominantHand_Int32 = "DominantHand";
ساكن ثابت حرف * k_pch_App_بلوک_Oculus_SDK_Bool = "blockOculusSDK";
ساكن ثابت حرف * k_pch_Trackers_Section = "trackers";
ساكن ثابت حرف * k_pch_DesktopUI_Section = "DesktopUI";
ساكن ثابت حرف * k_pch_آخرین_معلوم_Section = "LastKnown";
ساكن ثابت حرف * k_pch_آخرین_معلوم_HMDManufacturer_String = "HMDManufacturer";
ساكن ثابت حرف * k_pch_آخرین_معلوم_HMDModel_String = "HMDModel";
ساكن ثابت حرف * k_pch_DismissedWarnings_Section = "DismissedWarnings";
ساكن ثابت حرف * k_pch_درون_داد_Section = "input";
ساكن ثابت حرف * k_pch_درون_داد_چپ_Thumbstick_Rotation_Float = "leftThumbstickRotation";
ساكن ثابت حرف * k_pch_درون_داد_راست_Thumbstick_Rotation_Float = "rightThumbstickRotation";
ساكن ثابت حرف * k_pch_درون_داد_Thumbstick_Deadzone_Float = "thumbstickDeadzone";
ساكن ثابت حرف * k_pch_Gpu_سرعت_Section = "GpuSpeed";
ساكن ثابت حرف * IVRScreenshots_نسخه = "IVRScreenshots_001";
ساكن ثابت حرف * IVRResources_نسخه = "IVRResources_001";
ساكن ثابت حرف * IVRDriver_Manager_نسخه = "IVRDriverManager_001";
ساكن ثابت بیعلامت دراز k_un_Max_Action_Name_درازی = 64;
ساكن ثابت بیعلامت دراز k_un_Max_Action_مجموعه_Name_درازی = 64;
ساكن ثابت بیعلامت دراز k_un_Max_Action_Origin_شمار = 16;
ساكن ثابت بیعلامت دراز k_un_Max_Bone_Name_درازی = 32;
ساكن ثابت صحيح k_n_Action_مجموعه_Overlay_Global_اولویت_Min = 16777216;
ساكن ثابت صحيح k_n_Action_مجموعه_Overlay_Global_اولویت_Max = 33554431;
ساكن ثابت صحيح k_n_Action_مجموعه_اولویت_Reserved_Min = 33554432;
ساكن ثابت حرف * IVRInput_نسخه = "IVRInput_010";
ساكن ثابت بیعلامت دراز دراز k_ulInvalidIOBufferHandle = 0;
ساكن ثابت حرف * IVRIOBuffer_نسخه = "IVRIOBuffer_002";
ساكن ثابت بیعلامت دراز k_ulInvalidSpatialAnchorHandle = 0;
ساكن ثابت حرف * IVRSpatial_Anchors_نسخه = "IVRSpatialAnchors_001";
ساكن ثابت حرف * IVRDebug_نسخه = "IVRDebug_001";
ساكن ثابت بیعلامت دراز دراز k_ulDisplayRedirectContainer = 25769803779;
ساكن ثابت حرف * IVRProperties_نسخه = "IVRProperties_001";
ساكن ثابت حرف * k_pch_مسیر_User_Hand_راست = "/user/hand/right";
ساكن ثابت حرف * k_pch_مسیر_User_Hand_چپ = "/user/hand/left";
ساكن ثابت حرف * k_pch_مسیر_User_Hand_Primary = "/user/hand/primary";
ساكن ثابت حرف * k_pch_مسیر_User_Hand_Secondary = "/user/hand/secondary";
ساكن ثابت حرف * k_pch_مسیر_User_سر = "/user/head";
ساكن ثابت حرف * k_pch_مسیر_User_Gamepad = "/user/gamepad";
ساكن ثابت حرف * k_pch_مسیر_User_Treadmill = "/user/treadmill";
ساكن ثابت حرف * k_pch_مسیر_User_Stylus = "/user/stylus";
ساكن ثابت حرف * k_pch_مسیر_Devices = "/devices";
ساكن ثابت حرف * k_pch_مسیر_Device_مسیر = "/device_path";
ساكن ثابت حرف * k_pch_مسیر_بهترین_Alias_مسیر = "/best_alias_path";
ساكن ثابت حرف * k_pch_مسیر_Bound_Tracker_Alias_مسیر = "/bound_tracker_path";
ساكن ثابت حرف * k_pch_مسیر_Bound_Tracker_Role = "/bound_tracker_role";
ساكن ثابت حرف * k_pch_مسیر_Pose_Raw = "/pose/raw";
ساكن ثابت حرف * k_pch_مسیر_Pose_Tip = "/pose/tip";
ساكن ثابت حرف * k_pch_مسیر_Pose_Grip = "/pose/grip";
ساكن ثابت حرف * k_pch_مسیر_System_Button_Click = "/input/system/click";
ساكن ثابت حرف * k_pch_مسیر_Proximity = "/proximity";
ساكن ثابت حرف * k_pch_مسیر_Controller_Type_پیشوند = "/controller_type/";
ساكن ثابت حرف * k_pch_مسیر_درون_داد_Profile_Suffix = "/input_profile";
ساكن ثابت حرف * k_pch_مسیر_Binding_Name_Suffix = "/binding_name";
ساكن ثابت حرف * k_pch_مسیر_Binding_Url_Suffix = "/binding_url";
ساكن ثابت حرف * k_pch_مسیر_Binding_Error_Suffix = "/binding_error";
ساكن ثابت حرف * k_pch_مسیر_فعال_Action_Sets = "/active_action_sets";
ساكن ثابت حرف * k_pch_مسیر_Component_Updates = "/total_component_updates";
ساكن ثابت حرف * k_pch_مسیر_User_Foot_چپ = "/user/foot/left";
ساكن ثابت حرف * k_pch_مسیر_User_Foot_راست = "/user/foot/right";
ساكن ثابت حرف * k_pch_مسیر_User_Shoulder_چپ = "/user/shoulder/left";
ساكن ثابت حرف * k_pch_مسیر_User_Shoulder_راست = "/user/shoulder/right";
ساكن ثابت حرف * k_pch_مسیر_User_Elbow_چپ = "/user/elbow/left";
ساكن ثابت حرف * k_pch_مسیر_User_Elbow_راست = "/user/elbow/right";
ساكن ثابت حرف * k_pch_مسیر_User_Knee_چپ = "/user/knee/left";
ساكن ثابت حرف * k_pch_مسیر_User_Knee_راست = "/user/knee/right";
ساكن ثابت حرف * k_pch_مسیر_User_Waist = "/user/waist";
ساكن ثابت حرف * k_pch_مسیر_User_Chest = "/user/chest";
ساكن ثابت حرف * k_pch_مسیر_User_Camera = "/user/camera";
ساكن ثابت حرف * k_pch_مسیر_User_Keyboard = "/user/keyboard";
ساكن ثابت حرف * k_pch_مسیر_Client_App_کلید = "/client_info/app_key";
ساكن ثابت بیعلامت دراز دراز k_ul_Invalid_مسیر_Handle = 0;
ساكن ثابت حرف * IVRPaths_نسخه = "IVRPaths_001";
ساكن ثابت حرف * IVRBlock_صف_نسخه = "IVRBlockQueue_005";

// OpenVR Enums

تعريفنوع تعداد EVREye
{
	EVREye_Eye_چپ = 0,
	EVREye_Eye_راست = 1,
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
	EColor_Space_Color_Space_خطی = 2,
} EColorSpace;

تعريفنوع تعداد ETracking_نتیجه
{
	ETracking_نتیجه_Tracking_نتیجه_Uninitialized = 1,
	ETracking_نتیجه_Tracking_نتیجه_Calibrating_درون_پیشرفت = 100,
	ETracking_نتیجه_Tracking_نتیجه_Calibrating_بیرون_از_Range = 101,
	ETracking_نتیجه_Tracking_نتیجه_Running_OK = 200,
	ETracking_نتیجه_Tracking_نتیجه_Running_بیرون_از_Range = 201,
	ETracking_نتیجه_Tracking_نتیجه_Fallback_Rotation_Only = 300,
} ETracking_نتیجه;

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
	ETracked_Controller_Role_Tracked_Controller_Role_چپ_Hand = 1,
	ETracked_Controller_Role_Tracked_Controller_Role_راست_Hand = 2,
	ETracked_Controller_Role_Tracked_Controller_Role_Opt_بیرون = 3,
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
	EAdditional_Radio_Features_Additional_Radio_Features_داخلی_Dongle = 2,
	EAdditionalRadioFeatures_AdditionalRadioFeatures_ExternalDongle = 4,
} EAdditionalRadioFeatures;

تعريفنوع تعداد ETrackedDeviceProperty
{
	ETrackedDeviceProperty_Prop_Invalid = 0,
	ETrackedDeviceProperty_Prop_TrackingSystemName_String = 1000,
	ETracked_Device_Property_Prop_Model_عدد_String = 1001,
	ETracked_Device_Property_Prop_Serial_عدد_String = 1002,
	ETrackedDeviceProperty_Prop_RenderModelName_String = 1003,
	ETracked_Device_Property_Prop_Will_Drift_درون_Yaw_Bool = 1004,
	ETrackedDeviceProperty_Prop_ManufacturerName_String = 1005,
	ETracked_Device_Property_Prop_Tracking_Firmware_نسخه_String = 1006,
	ETrackedDeviceProperty_Prop_HardwareRevision_String = 1007,
	ETrackedDeviceProperty_Prop_AllWirelessDongleDescriptions_String = 1008,
	ETrackedDeviceProperty_Prop_ConnectedWirelessDongle_String = 1009,
	ETrackedDeviceProperty_Prop_DeviceIsWireless_Bool = 1010,
	ETrackedDeviceProperty_Prop_DeviceIsCharging_Bool = 1011,
	ETrackedDeviceProperty_Prop_DeviceBatteryPercentage_Float = 1012,
	ETracked_Device_Property_Prop_وضعیت_Display_Transform_Matrix34 = 1013,
	ETracked_Device_Property_Prop_Firmware_Update_موجود_Bool = 1014,
	ETrackedDeviceProperty_Prop_Firmware_ManualUpdate_Bool = 1015,
	ETrackedDeviceProperty_Prop_Firmware_ManualUpdateURL_String = 1016,
	ETrackedDeviceProperty_Prop_HardwareRevision_Uint64 = 1017,
	ETracked_Device_Property_Prop_Firmware_نسخه_Uint64 = 1018,
	ETrackedDeviceProperty_Prop_FPGAVersion_Uint64 = 1019,
	ETrackedDeviceProperty_Prop_VRCVersion_Uint64 = 1020,
	ETracked_Device_Property_Prop_Radio_نسخه_Uint64 = 1021,
	ETracked_Device_Property_Prop_Dongle_نسخه_Uint64 = 1022,
	ETracked_Device_Property_Prop_بلوک_Server_Shutdown_Bool = 1023,
	ETrackedDeviceProperty_Prop_CanUnifyCoordinateSystemWithHmd_Bool = 1024,
	ETracked_Device_Property_Prop_شامل_است_Proximity_Sensor_Bool = 1025,
	ETracked_Device_Property_Prop_Device_Provides_Battery_وضعیت_Bool = 1026,
	ETrackedDeviceProperty_Prop_DeviceCanPowerOff_Bool = 1027,
	ETracked_Device_Property_Prop_Firmware_Programming_هدف_String = 1028,
	ETrackedDeviceProperty_Prop_DeviceClass_Int32 = 1029,
	ETrackedDeviceProperty_Prop_HasCamera_Bool = 1030,
	ETracked_Device_Property_Prop_Driver_نسخه_String = 1031,
	ETrackedDeviceProperty_Prop_Firmware_ForceUpdateRequired_Bool = 1032,
	ETrackedDeviceProperty_Prop_ViveSystemButtonFixRequired_Bool = 1033,
	ETracked_Device_Property_Prop_والد_Driver_Uint64 = 1034,
	ETracked_Device_Property_Prop_Resource_ریشه_String = 1035,
	ETrackedDeviceProperty_Prop_RegisteredDeviceType_String = 1036,
	ETracked_Device_Property_Prop_درون_داد_Profile_مسیر_String = 1037,
	ETrackedDeviceProperty_Prop_NeverTracked_Bool = 1038,
	ETracked_Device_Property_Prop_رقم_Cameras_Int32 = 1039,
	ETracked_Device_Property_Prop_Camera_قاب_Layout_Int32 = 1040,
	ETracked_Device_Property_Prop_Camera_جریان_Format_Int32 = 1041,
	ETracked_Device_Property_Prop_Additional_Device_Settings_مسیر_String = 1042,
	ETrackedDeviceProperty_Prop_Identifiable_Bool = 1043,
	ETracked_Device_Property_Prop_Bootloader_نسخه_Uint64 = 1044,
	ETracked_Device_Property_Prop_Additional_System_Report_داده_String = 1045,
	ETracked_Device_Property_Prop_مرکب_Firmware_نسخه_String = 1046,
	ETrackedDeviceProperty_Prop_Firmware_RemindUpdate_Bool = 1047,
	ETracked_Device_Property_Prop_Peripheral_Application_نسخه_Uint64 = 1048,
	ETracked_Device_Property_Prop_Manufacturer_Serial_عدد_String = 1049,
	ETracked_Device_Property_Prop_Computed_Serial_عدد_String = 1050,
	ETracked_Device_Property_Prop_Estimated_Device_اولی_Use_زمان_Int32 = 1051,
	ETrackedDeviceProperty_Prop_DevicePowerUsage_Float = 1052,
	ETrackedDeviceProperty_Prop_IgnoreMotionForStandby_Bool = 1053,
	ETracked_Device_Property_Prop_Reports_زمان_Since_VSync_Bool = 2000,
	ETracked_Device_Property_Prop_Seconds_From_Vsync_مقصد_Photons_Float = 2001,
	ETrackedDeviceProperty_Prop_DisplayFrequency_Float = 2002,
	ETrackedDeviceProperty_Prop_UserIpdMeters_Float = 2003,
	ETrackedDeviceProperty_Prop_CurrentUniverseId_Uint64 = 2004,
	ETracked_Device_Property_Prop_قبلی_Universe_Id_Uint64 = 2005,
	ETracked_Device_Property_Prop_Display_Firmware_نسخه_Uint64 = 2006,
	ETrackedDeviceProperty_Prop_IsOnDesktop_Bool = 2007,
	ETrackedDeviceProperty_Prop_DisplayMCType_Int32 = 2008,
	ETrackedDeviceProperty_Prop_DisplayMCOffset_Float = 2009,
	ETrackedDeviceProperty_Prop_DisplayMCScale_Float = 2010,
	ETrackedDeviceProperty_Prop_EdidVendorID_Int32 = 2011,
	ETracked_Device_Property_Prop_Display_MCImage_چپ_String = 2012,
	ETracked_Device_Property_Prop_Display_MCImage_راست_String = 2013,
	ETrackedDeviceProperty_Prop_DisplayGCBlackClamp_Float = 2014,
	ETracked_Device_Property_Prop_Edid_حاصلضرب_ID_Int32 = 2015,
	ETracked_Device_Property_Prop_Camera_مقصد_سر_Transform_Matrix34 = 2016,
	ETrackedDeviceProperty_Prop_DisplayGCType_Int32 = 2017,
	ETrackedDeviceProperty_Prop_DisplayGCOffset_Float = 2018,
	ETrackedDeviceProperty_Prop_DisplayGCScale_Float = 2019,
	ETrackedDeviceProperty_Prop_DisplayGCPrescale_Float = 2020,
	ETrackedDeviceProperty_Prop_DisplayGCImage_String = 2021,
	ETracked_Device_Property_Prop_Lens_Center_چپ_U_Float = 2022,
	ETracked_Device_Property_Prop_Lens_Center_چپ_V_Float = 2023,
	ETracked_Device_Property_Prop_Lens_Center_راست_U_Float = 2024,
	ETracked_Device_Property_Prop_Lens_Center_راست_V_Float = 2025,
	ETracked_Device_Property_Prop_User_سر_مقصد_Eye_عمق_Meters_Float = 2026,
	ETracked_Device_Property_Prop_Camera_Firmware_نسخه_Uint64 = 2027,
	ETrackedDeviceProperty_Prop_CameraFirmwareDescription_String = 2028,
	ETrackedDeviceProperty_Prop_DisplayFPGAVersion_Uint64 = 2029,
	ETracked_Device_Property_Prop_Display_Bootloader_نسخه_Uint64 = 2030,
	ETracked_Device_Property_Prop_Display_Hardware_نسخه_Uint64 = 2031,
	ETracked_Device_Property_Prop_Audio_Firmware_نسخه_Uint64 = 2032,
	ETracked_Device_Property_Prop_Camera_Compatibility_نما_Int32 = 2033,
	ETracked_Device_Property_Prop_Screenshot_Horizontal_فیلد_از_View_Degrees_Float = 2034,
	ETracked_Device_Property_Prop_Screenshot_Vertical_فیلد_از_View_Degrees_Float = 2035,
	ETrackedDeviceProperty_Prop_DisplaySuppressed_Bool = 2036,
	ETracked_Device_Property_Prop_Display_Allow_Night_نما_Bool = 2037,
	ETracked_Device_Property_Prop_Display_MCImage_عرض_Int32 = 2038,
	ETracked_Device_Property_Prop_Display_MCImage_ارتفاع_Int32 = 2039,
	ETracked_Device_Property_Prop_Display_MCImage_رقم_Channels_Int32 = 2040,
	ETracked_Device_Property_Prop_Display_MCImage_داده_دودویی = 2041,
	ETracked_Device_Property_Prop_Seconds_From_Photons_مقصد_Vblank_Float = 2042,
	ETracked_Device_Property_Prop_Driver_مستقیم_نما_Sends_Vsync_Events_Bool = 2043,
	ETracked_Device_Property_Prop_Display_Debug_نما_Bool = 2044,
	ETrackedDeviceProperty_Prop_GraphicsAdapterLuid_Uint64 = 2045,
	ETracked_Device_Property_Prop_Driver_Provided_Chaperone_مسیر_String = 2048,
	ETracked_Device_Property_Prop_Expected_Tracking_Reference_شمار_Int32 = 2049,
	ETracked_Device_Property_Prop_Expected_Controller_شمار_Int32 = 2050,
	ETracked_Device_Property_Prop_Named_Icon_مسیر_Controller_چپ_Device_Off_String = 2051,
	ETracked_Device_Property_Prop_Named_Icon_مسیر_Controller_راست_Device_Off_String = 2052,
	ETracked_Device_Property_Prop_Named_Icon_مسیر_Tracking_Reference_Device_Off_String = 2053,
	ETrackedDeviceProperty_Prop_DoNotApplyPrediction_Bool = 2054,
	ETracked_Device_Property_Prop_Camera_مقصد_سر_Transforms_Matrix34_Array = 2055,
	ETrackedDeviceProperty_Prop_DistortionMeshResolution_Int32 = 2056,
	ETrackedDeviceProperty_Prop_DriverIsDrawingControllers_Bool = 2057,
	ETracked_Device_Property_Prop_Driver_درخواستها_Application_Pause_Bool = 2058,
	ETracked_Device_Property_Prop_Driver_درخواستها_Reduced_Rendering_Bool = 2059,
	ETracked_Device_Property_Prop_Minimum_Ipd_گام_Meters_Float = 2060,
	ETracked_Device_Property_Prop_Audio_Bridge_Firmware_نسخه_Uint64 = 2061,
	ETracked_Device_Property_Prop_Image_Bridge_Firmware_نسخه_Uint64 = 2062,
	ETracked_Device_Property_Prop_Imu_مقصد_سر_Transform_Matrix34 = 2063,
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
	ETracked_Device_Property_Prop_Hmd_ستونی_Correction_Setting_پیشوند_String = 2077,
	ETrackedDeviceProperty_Prop_CameraSupportsCompatibilityModes_Bool = 2078,
	ETracked_Device_Property_Prop_Supports_جا_View_عمق_Projection_Bool = 2079,
	ETracked_Device_Property_Prop_Display_موجود_قاب_Rates_Float_Array = 2080,
	ETracked_Device_Property_Prop_Display_Supports_مضرب_Framerates_Bool = 2081,
	ETracked_Device_Property_Prop_Display_Color_Mult_چپ_Vector3 = 2082,
	ETracked_Device_Property_Prop_Display_Color_Mult_راست_Vector3 = 2083,
	ETrackedDeviceProperty_Prop_DisplaySupportsRuntimeFramerateChange_Bool = 2084,
	ETrackedDeviceProperty_Prop_DisplaySupportsAnalogGain_Bool = 2085,
	ETrackedDeviceProperty_Prop_DisplayMinAnalogGain_Float = 2086,
	ETrackedDeviceProperty_Prop_DisplayMaxAnalogGain_Float = 2087,
	ETracked_Device_Property_Prop_Camera_Exposure_زمان_Float = 2088,
	ETrackedDeviceProperty_Prop_CameraGlobalGain_Float = 2089,
	ETrackedDeviceProperty_Prop_DashboardScale_Float = 2091,
	ETrackedDeviceProperty_Prop_PeerButtonInfo_String = 2092,
	ETrackedDeviceProperty_Prop_Hmd_SupportsHDR10_Bool = 2093,
	ETrackedDeviceProperty_Prop_IpdUIRangeMinMeters_Float = 2100,
	ETrackedDeviceProperty_Prop_IpdUIRangeMaxMeters_Float = 2101,
	ETrackedDeviceProperty_Prop_Hmd_SupportsHDCP14LegacyCompat_Bool = 2102,
	ETrackedDeviceProperty_Prop_Hmd_SupportsMicMonitoring_Bool = 2103,
	ETracked_Device_Property_Prop_Hmd_Supports_Display_پورت_Training_نما_Bool = 2104,
	ETracked_Device_Property_Prop_Supports_جا_View_مستقیم_Bool = 2105,
	ETrackedDeviceProperty_Prop_SupportsAppThrottling_Bool = 2106,
	ETrackedDeviceProperty_Prop_DSCVersion_Int32 = 2110,
	ETracked_Device_Property_Prop_DSCSlice_شمار_Int32 = 2111,
	ETrackedDeviceProperty_Prop_DSCBPPx16_Int32 = 2112,
	ETracked_Device_Property_Prop_Driver_Requested_Mura_Correction_نما_Int32 = 2200,
	ETracked_Device_Property_Prop_Driver_Requested_Mura_Feather_Inner_چپ_Int32 = 2201,
	ETracked_Device_Property_Prop_Driver_Requested_Mura_Feather_Inner_راست_Int32 = 2202,
	ETracked_Device_Property_Prop_Driver_Requested_Mura_Feather_Inner_بالاترین_Int32 = 2203,
	ETrackedDeviceProperty_Prop_DriverRequestedMuraFeather_InnerBottom_Int32 = 2204,
	ETracked_Device_Property_Prop_Driver_Requested_Mura_Feather_Outer_چپ_Int32 = 2205,
	ETracked_Device_Property_Prop_Driver_Requested_Mura_Feather_Outer_راست_Int32 = 2206,
	ETracked_Device_Property_Prop_Driver_Requested_Mura_Feather_Outer_بالاترین_Int32 = 2207,
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
	ETracked_Device_Property_Prop_فیلد_از_View_چپ_Degrees_Float = 4000,
	ETracked_Device_Property_Prop_فیلد_از_View_راست_Degrees_Float = 4001,
	ETracked_Device_Property_Prop_فیلد_از_View_بالاترین_Degrees_Float = 4002,
	ETracked_Device_Property_Prop_فیلد_از_View_Bottom_Degrees_Float = 4003,
	ETrackedDeviceProperty_Prop_TrackingRangeMinimumMeters_Float = 4004,
	ETracked_Device_Property_Prop_Tracking_Range_بیشینه_Meters_Float = 4005,
	ETracked_Device_Property_Prop_نما_Label_String = 4006,
	ETrackedDeviceProperty_Prop_CanWirelessIdentify_Bool = 4007,
	ETrackedDeviceProperty_Prop_Nonce_Int32 = 4008,
	ETracked_Device_Property_Prop_Icon_مسیر_Name_String = 5000,
	ETracked_Device_Property_Prop_Named_Icon_مسیر_Device_Off_String = 5001,
	ETracked_Device_Property_Prop_Named_Icon_مسیر_Device_Searching_String = 5002,
	ETracked_Device_Property_Prop_Named_Icon_مسیر_Device_Searching_Alert_String = 5003,
	ETracked_Device_Property_Prop_Named_Icon_مسیر_Device_Ready_String = 5004,
	ETracked_Device_Property_Prop_Named_Icon_مسیر_Device_Ready_Alert_String = 5005,
	ETracked_Device_Property_Prop_Named_Icon_مسیر_Device_Not_Ready_String = 5006,
	ETracked_Device_Property_Prop_Named_Icon_مسیر_Device_Standby_String = 5007,
	ETracked_Device_Property_Prop_Named_Icon_مسیر_Device_Alert_کم_String = 5008,
	ETracked_Device_Property_Prop_Named_Icon_مسیر_Device_Standby_Alert_String = 5009,
	ETracked_Device_Property_Prop_Display_Hidden_Area_دودویی_شروع = 5100,
	ETracked_Device_Property_Prop_Display_Hidden_Area_دودویی_انتها = 5150,
	ETracked_Device_Property_Prop_والد_Container = 5151,
	ETrackedDeviceProperty_Prop_OverrideContainer_Uint64 = 5152,
	ETracked_Device_Property_Prop_User_Config_مسیر_String = 6000,
	ETracked_Device_Property_Prop_Install_مسیر_String = 6001,
	ETrackedDeviceProperty_Prop_HasDisplayComponent_Bool = 6002,
	ETrackedDeviceProperty_Prop_HasControllerComponent_Bool = 6003,
	ETrackedDeviceProperty_Prop_HasCameraComponent_Bool = 6004,
	ETracked_Device_Property_Prop_Has_Driver_مستقیم_نما_Component_Bool = 6005,
	ETrackedDeviceProperty_Prop_HasVirtualDisplayComponent_Bool = 6006,
	ETrackedDeviceProperty_Prop_HasSpatialAnchorsSupport_Bool = 6007,
	ETrackedDeviceProperty_Prop_ControllerType_String = 7000,
	ETracked_Device_Property_Prop_Controller_Hand_Selection_اولویت_Int32 = 7002,
	ETracked_Device_Property_Prop_Vendor_Specific_Reserved_شروع = 10000,
	ETracked_Device_Property_Prop_Vendor_Specific_Reserved_انتها = 10999,
	ETrackedDeviceProperty_Prop_TrackedDeviceProperty_Max = 1000000,
} ETrackedDeviceProperty;

تعريفنوع تعداد ETrackedPropertyError
{
	ETrackedPropertyError_TrackedProp_Success = 0,
	ETracked_Property_Error_Tracked_Prop_Wrong_داده_Type = 1,
	ETrackedPropertyError_TrackedProp_WrongDeviceClass = 2,
	ETracked_Property_Error_Tracked_Prop_میانگیر_Too_Small = 3,
	ETrackedPropertyError_TrackedProp_UnknownProperty = 4,
	ETrackedPropertyError_TrackedProp_InvalidDevice = 5,
	ETrackedPropertyError_TrackedProp_CouldNotContactServer = 6,
	ETracked_Property_Error_Tracked_Prop_مقدار_Not_Provided_By_Device = 7,
	ETracked_Property_Error_Tracked_Prop_String_Exceeds_بیشینه_درازی = 8,
	ETracked_Property_Error_Tracked_Prop_Not_Yet_موجود = 9,
	ETrackedPropertyError_TrackedProp_PermissionDenied = 10,
	ETrackedPropertyError_TrackedProp_InvalidOperation = 11,
	ETracked_Property_Error_Tracked_Prop_Cannot_Write_مقصد_Wildcards = 12,
	ETrackedPropertyError_TrackedProp_IPCReadFailure = 13,
	ETracked_Property_Error_Tracked_Prop_بیرون_از_حافظه = 14,
	ETrackedPropertyError_TrackedProp_InvalidContainer = 15,
} ETrackedPropertyError;

تعريفنوع تعداد EHmdTrackingStyle
{
	EHmdTrackingStyle_HmdTrackingStyle_Unknown = 0,
	EHmdTrackingStyle_HmdTrackingStyle_Lighthouse = 1,
	EHmd_Tracking_Style_Hmd_Tracking_Style_Outside_درون_Cameras = 2,
	EHmd_Tracking_Style_Hmd_Tracking_Style_Inside_بیرون_Cameras = 3,
} EHmdTrackingStyle;

تعريفنوع تعداد EVRSubmitFlags
{
	EVRSubmitFlags_Submit_Default = 0,
	EVRSubmitFlags_Submit_LensDistortionAlreadyApplied = 1,
	EVRSubmit_Flags_Submit_Gl_Render_میانگیر = 2,
	EVRSubmitFlags_Submit_Reserved = 4,
	EVRSubmitFlags_Submit_TextureWithPose = 8,
	EVRSubmit_Flags_Submit_Texture_With_عمق = 16,
	EVRSubmit_Flags_Submit_قاب_Discontinuty = 32,
	EVRSubmit_Flags_Submit_Vulkan_Texture_With_Array_داده = 64,
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
	EVRState_VRState_Ready_Alert_کم = 7,
} EVRState;

تعريفنوع تعداد EVREventType
{
	EVREventType_VREvent_None = 0,
	EVREventType_VREvent_TrackedDeviceActivated = 100,
	EVREventType_VREvent_TrackedDeviceDeactivated = 101,
	EVREventType_VREvent_TrackedDeviceUpdated = 102,
	EVREventType_VREvent_TrackedDeviceUserInteractionStarted = 103,
	EVREventType_VREvent_TrackedDeviceUserInteractionEnded = 104,
	EVREvent_Type_VREvent_Ipd_تغییریافته = 105,
	EVREvent_Type_VREvent_Enter_Standby_نما = 106,
	EVREvent_Type_VREvent_Leave_Standby_نما = 107,
	EVREvent_Type_VREvent_Tracked_Device_Role_تغییریافته = 108,
	EVREvent_Type_VREvent_Watchdog_Wake_به_بالا_Requested = 109,
	EVREvent_Type_VREvent_Lens_Distortion_تغییریافته = 110,
	EVREvent_Type_VREvent_Property_تغییریافته = 111,
	EVREventType_VREvent_WirelessDisconnect = 112,
	EVREventType_VREvent_WirelessReconnect = 113,
	EVREventType_VREvent_ButtonPress = 200,
	EVREventType_VREvent_ButtonUnpress = 201,
	EVREventType_VREvent_ButtonTouch = 202,
	EVREventType_VREvent_ButtonUntouch = 203,
	EVREventType_VREvent_Modal_Cancel = 257,
	EVREventType_VREvent_MouseMove = 300,
	EVREvent_Type_VREvent_Mouse_Button_پایین = 301,
	EVREvent_Type_VREvent_Mouse_Button_به_بالا = 302,
	EVREventType_VREvent_FocusEnter = 303,
	EVREventType_VREvent_FocusLeave = 304,
	EVREventType_VREvent_ScrollDiscrete = 305,
	EVREventType_VREvent_TouchPadMove = 306,
	EVREvent_Type_VREvent_Overlay_Focus_تغییریافته = 307,
	EVREventType_VREvent_ReloadOverlays = 308,
	EVREventType_VREvent_ScrollSmooth = 309,
	EVREvent_Type_VREvent_قفل_Mouse_Position = 310,
	EVREventType_VREvent_UnlockMousePosition = 311,
	EVREvent_Type_VREvent_درون_داد_Focus_Captured = 400,
	EVREvent_Type_VREvent_درون_داد_Focus_Released = 401,
	EVREvent_Type_VREvent_Scene_Application_تغییریافته = 404,
	EVREvent_Type_VREvent_درون_داد_Focus_تغییریافته = 406,
	EVREventType_VREvent_SceneApplicationUsingWrongGraphicsAdapter = 408,
	EVREventType_VREvent_ActionBindingReloaded = 409,
	EVREventType_VREvent_HideRenderModels = 410,
	EVREventType_VREvent_ShowRenderModels = 411,
	EVREvent_Type_VREvent_Scene_Application_State_تغییریافته = 412,
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
	EVREvent_Type_VREvent_Overlay_Gamepad_Focus_گمشده = 512,
	EVREvent_Type_VREvent_Overlay_Shared_Texture_تغییریافته = 513,
	EVREventType_VREvent_ScreenshotTriggered = 516,
	EVREventType_VREvent_ImageFailed = 517,
	EVREventType_VREvent_DashboardOverlayCreated = 518,
	EVREventType_VREvent_SwitchGamepadFocus = 519,
	EVREventType_VREvent_RequestScreenshot = 520,
	EVREvent_Type_VREvent_Screenshot_گرفته = 521,
	EVREventType_VREvent_ScreenshotFailed = 522,
	EVREvent_Type_VREvent_Submit_Screenshot_مقصد_Dashboard = 523,
	EVREvent_Type_VREvent_Screenshot_پیشرفت_مقصد_Dashboard = 524,
	EVREvent_Type_VREvent_Primary_Dashboard_Device_تغییریافته = 525,
	EVREvent_Type_VREvent_جا_View_Shown = 526,
	EVREvent_Type_VREvent_جا_View_Hidden = 527,
	EVREventType_VREvent_ShowUI = 528,
	EVREventType_VREvent_ShowDevTools = 529,
	EVREventType_VREvent_DesktopViewUpdating = 530,
	EVREventType_VREvent_DesktopViewReady = 531,
	EVREvent_Type_VREvent_شروع_Dashboard = 532,
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
	EVREvent_Type_VREvent_Invalidate_جابجا_Texture_Sets = 706,
	EVREvent_Type_VREvent_Chaperone_داده_Has_تغییریافته = 800,
	EVREvent_Type_VREvent_Chaperone_Universe_Has_تغییریافته = 801,
	EVREvent_Type_VREvent_Chaperone_موقت_داده_Has_تغییریافته = 802,
	EVREvent_Type_VREvent_Chaperone_Settings_Have_تغییریافته = 803,
	EVREventType_VREvent_SeatedZeroPoseReset = 804,
	EVREventType_VREvent_ChaperoneFlushCache = 805,
	EVREvent_Type_VREvent_Chaperone_جا_راهاندازی_Starting = 806,
	EVREvent_Type_VREvent_Chaperone_جا_راهاندازی_پایانیافته = 807,
	EVREventType_VREvent_StandingZeroPoseReset = 808,
	EVREvent_Type_VREvent_Audio_Settings_Have_تغییریافته = 820,
	EVREvent_Type_VREvent_Background_Setting_Has_تغییریافته = 850,
	EVREvent_Type_VREvent_Camera_Settings_Have_تغییریافته = 851,
	EVREvent_Type_VREvent_Reprojection_Setting_Has_تغییریافته = 852,
	EVREvent_Type_VREvent_Model_Skin_Settings_Have_تغییریافته = 853,
	EVREvent_Type_VREvent_Environment_Settings_Have_تغییریافته = 854,
	EVREvent_Type_VREvent_Power_Settings_Have_تغییریافته = 855,
	EVREvent_Type_VREvent_Enable_Home_App_Settings_Have_تغییریافته = 856,
	EVREvent_Type_VREvent_Steam_VRSection_Setting_تغییریافته = 857,
	EVREvent_Type_VREvent_Lighthouse_Section_Setting_تغییریافته = 858,
	EVREvent_Type_VREvent_Null_Section_Setting_تغییریافته = 859,
	EVREvent_Type_VREvent_User_Interface_Section_Setting_تغییریافته = 860,
	EVREvent_Type_VREvent_Notifications_Section_Setting_تغییریافته = 861,
	EVREvent_Type_VREvent_Keyboard_Section_Setting_تغییریافته = 862,
	EVREvent_Type_VREvent_Perf_Section_Setting_تغییریافته = 863,
	EVREvent_Type_VREvent_Dashboard_Section_Setting_تغییریافته = 864,
	EVREvent_Type_VREvent_Web_Interface_Section_Setting_تغییریافته = 865,
	EVREvent_Type_VREvent_Trackers_Section_Setting_تغییریافته = 866,
	EVREvent_Type_VREvent_آخرین_معلوم_Section_Setting_تغییریافته = 867,
	EVREvent_Type_VREvent_Dismissed_Warnings_Section_Setting_تغییریافته = 868,
	EVREvent_Type_VREvent_Gpu_سرعت_Section_Setting_تغییریافته = 869,
	EVREvent_Type_VREvent_Windows_MRSection_Setting_تغییریافته = 870,
	EVREvent_Type_VREvent_Other_Section_Setting_تغییریافته = 871,
	EVREvent_Type_VREvent_وضعیت_Update = 900,
	EVREventType_VREvent_WebInterface_InstallDriverCompleted = 950,
	EVREventType_VREvent_MCImageUpdated = 1000,
	EVREventType_VREvent_FirmwareUpdateStarted = 1100,
	EVREvent_Type_VREvent_Firmware_Update_پایانیافته = 1101,
	EVREventType_VREvent_KeyboardClosed = 1200,
	EVREvent_Type_VREvent_Keyboard_Char_درون_داد = 1201,
	EVREvent_Type_VREvent_Keyboard_انجامشده = 1202,
	EVREventType_VREvent_ApplicationListUpdated = 1303,
	EVREvent_Type_VREvent_Application_Mime_Type_بارگیری = 1304,
	EVREventType_VREvent_ProcessConnected = 1306,
	EVREventType_VREvent_ProcessDisconnected = 1307,
	EVREventType_VREvent_Compositor_ChaperoneBoundsShown = 1410,
	EVREventType_VREvent_Compositor_ChaperoneBoundsHidden = 1411,
	EVREventType_VREvent_Compositor_DisplayDisconnected = 1412,
	EVREventType_VREvent_Compositor_DisplayReconnected = 1413,
	EVREventType_VREvent_Compositor_HDCPError = 1414,
	EVREventType_VREvent_Compositor_ApplicationNotResponding = 1415,
	EVREventType_VREvent_Compositor_ApplicationResumed = 1416,
	EVREvent_Type_VREvent_Compositor_بیرون_از_Video_حافظه = 1417,
	EVREvent_Type_VREvent_Compositor_Display_نما_Not_Supported = 1418,
	EVREventType_VREvent_Compositor_StageOverrideReady = 1419,
	EVREventType_VREvent_Compositor_RequestDisconnectReconnect = 1420,
	EVREvent_Type_VREvent_Tracked_Camera_شروع_Video_جریان = 1500,
	EVREvent_Type_VREvent_Tracked_Camera_Stop_Video_جریان = 1501,
	EVREvent_Type_VREvent_Tracked_Camera_Pause_Video_جریان = 1502,
	EVREvent_Type_VREvent_Tracked_Camera_Resume_Video_جریان = 1503,
	EVREventType_VREvent_TrackedCamera_EditingSurface = 1550,
	EVREventType_VREvent_PerformanceTest_EnableCapture = 1600,
	EVREventType_VREvent_PerformanceTest_DisableCapture = 1601,
	EVREventType_VREvent_PerformanceTest_FidelityLevel = 1602,
	EVREvent_Type_VREvent_پیام_Overlay_Closed = 1650,
	EVREvent_Type_VREvent_پیام_Overlay_Close_Requested = 1651,
	EVREvent_Type_VREvent_درون_داد_Haptic_Vibration = 1700,
	EVREvent_Type_VREvent_درون_داد_Binding_بارگیری_Failed = 1701,
	EVREvent_Type_VREvent_درون_داد_Binding_بارگیری_Successful = 1702,
	EVREvent_Type_VREvent_درون_داد_Action_Manifest_Reloaded = 1703,
	EVREvent_Type_VREvent_درون_داد_Action_Manifest_بارگیری_Failed = 1704,
	EVREvent_Type_VREvent_درون_داد_پیشرفت_Update = 1705,
	EVREvent_Type_VREvent_درون_داد_Tracker_Activated = 1706,
	EVREvent_Type_VREvent_درون_داد_Bindings_Updated = 1707,
	EVREvent_Type_VREvent_درون_داد_Binding_Subscription_تغییریافته = 1708,
	EVREventType_VREvent_SpatialAnchors_PoseUpdated = 1800,
	EVREventType_VREvent_SpatialAnchors_DescriptorUpdated = 1801,
	EVREventType_VREvent_SpatialAnchors_RequestPoseUpdate = 1802,
	EVREventType_VREvent_SpatialAnchors_RequestDescriptorUpdate = 1803,
	EVREventType_VREvent_SystemReport_Started = 1900,
	EVREventType_VREvent_Monitor_ShowHeadsetView = 2000,
	EVREventType_VREvent_Monitor_HideHeadsetView = 2001,
	EVREvent_Type_VREvent_Vendor_Specific_Reserved_شروع = 10000,
	EVREvent_Type_VREvent_Vendor_Specific_Reserved_انتها = 19999,
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
	EVRButton_Id_k_EButton_DPad_چپ = 3,
	EVRButton_Id_k_EButton_DPad_به_بالا = 4,
	EVRButton_Id_k_EButton_DPad_راست = 5,
	EVRButton_Id_k_EButton_DPad_پایین = 6,
	EVRButtonId_k_EButton_A = 7,
	EVRButtonId_k_EButton_ProximitySensor = 31,
	EVRButtonId_k_EButton_Axis0 = 32,
	EVRButtonId_k_EButton_Axis1 = 33,
	EVRButtonId_k_EButton_Axis2 = 34,
	EVRButtonId_k_EButton_Axis3 = 35,
	EVRButtonId_k_EButton_Axis4 = 36,
	EVRButtonId_k_EButton_SteamVR_Touchpad = 32,
	EVRButtonId_k_EButton_SteamVR_Trigger = 33,
	EVRButton_Id_k_EButton_Dashboard_پشت = 2,
	EVRButton_Id_k_EButton_شاخص_Controller_A = 2,
	EVRButton_Id_k_EButton_شاخص_Controller_B = 1,
	EVRButton_Id_k_EButton_شاخص_Controller_Joy_Stick = 35,
	EVRButtonId_k_EButton_Max = 64,
} EVRButtonId;

تعريفنوع تعداد EVRMouseButton
{
	EVRMouse_Button_VRMouse_Button_چپ = 1,
	EVRMouse_Button_VRMouse_Button_راست = 2,
	EVRMouse_Button_VRMouse_Button_میانه = 4,
} EVRMouseButton;

تعريفنوع تعداد EShowUIType
{
	EShowUIType_ShowUI_ControllerBinding = 0,
	EShowUIType_ShowUI_ManageTrackers = 1,
	EShowUIType_ShowUI_Pairing = 3,
	EShowUIType_ShowUI_Settings = 4,
	EShowUIType_ShowUI_DebugCommands = 5,
	EShow_UIType_Show_UI_پر_Controller_Binding = 6,
	EShowUIType_ShowUI_ManageDrivers = 7,
} EShowUIType;

تعريفنوع تعداد EHDCPError
{
	EHDCPError_HDCPError_None = 0,
	EHDCPError_HDCPError_Link_گمشده = 1,
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
	EVRInput_Error_VRInput_Error_Name_Not_یافت = 1,
	EVRInputError_VRInputError_WrongType = 2,
	EVRInputError_VRInputError_InvalidHandle = 3,
	EVRInputError_VRInputError_InvalidParam = 4,
	EVRInputError_VRInputError_NoSteam = 5,
	EVRInput_Error_VRInput_Error_Max_ظرفیت_Reached = 6,
	EVRInputError_VRInputError_IPCError = 7,
	EVRInput_Error_VRInput_Error_No_فعال_Action_مجموعه = 8,
	EVRInputError_VRInputError_InvalidDevice = 9,
	EVRInputError_VRInputError_InvalidSkeleton = 10,
	EVRInput_Error_VRInput_Error_Invalid_Bone_شمار = 11,
	EVRInput_Error_VRInput_Error_Invalid_Compressed_داده = 12,
	EVRInput_Error_VRInput_Error_No_داده = 13,
	EVRInput_Error_VRInput_Error_میانگیر_Too_Small = 14,
	EVRInputError_VRInputError_MismatchedActionManifest = 15,
	EVRInput_Error_VRInput_Error_Missing_Skeleton_داده = 16,
	EVRInput_Error_VRInput_Error_Invalid_Bone_شاخص = 17,
	EVRInput_Error_VRInput_Error_Invalid_اولویت = 18,
	EVRInputError_VRInputError_PermissionDenied = 19,
	EVRInputError_VRInputError_InvalidRenderModel = 20,
} EVRInputError;

تعريفنوع تعداد EVRSpatialAnchorError
{
	EVRSpatialAnchorError_VRSpatialAnchorError_Success = 0,
	EVRSpatial_Anchor_Error_VRSpatial_Anchor_Error_داخلی = 1,
	EVRSpatialAnchorError_VRSpatialAnchorError_UnknownHandle = 2,
	EVRSpatialAnchorError_VRSpatialAnchorError_ArrayTooSmall = 3,
	EVRSpatialAnchorError_VRSpatialAnchorError_InvalidDescriptorChar = 4,
	EVRSpatial_Anchor_Error_VRSpatial_Anchor_Error_Not_Yet_موجود = 5,
	EVRSpatial_Anchor_Error_VRSpatial_Anchor_Error_Not_موجود_درون_This_Universe = 6,
	EVRSpatialAnchorError_VRSpatialAnchorError_PermanentlyUnavailable = 7,
	EVRSpatialAnchorError_VRSpatialAnchorError_WrongDriver = 8,
	EVRSpatialAnchorError_VRSpatialAnchorError_DescriptorTooLong = 9,
	EVRSpatialAnchorError_VRSpatialAnchorError_Unknown = 10,
	EVRSpatial_Anchor_Error_VRSpatial_Anchor_Error_No_جا_Calibration = 11,
	EVRSpatial_Anchor_Error_VRSpatial_Anchor_Error_Invalid_آرگومان = 12,
	EVRSpatialAnchorError_VRSpatialAnchorError_UnknownDriver = 13,
} EVRSpatialAnchorError;

تعريفنوع تعداد EHiddenAreaMeshType
{
	EHiddenAreaMeshType_k_eHiddenAreaMesh_Standard = 0,
	EHiddenAreaMeshType_k_eHiddenAreaMesh_Inverse = 1,
	EHidden_Area_Mesh_Type_k_e_Hidden_Area_Mesh_سطر_Loop = 2,
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
	ECollision_Bounds_Style_COLLISION_BOUNDS_STYLE_شمار = 5,
} ECollisionBoundsStyle;

تعريفنوع تعداد EVROverlayError
{
	EVROverlayError_VROverlayError_None = 0,
	EVROverlayError_VROverlayError_UnknownOverlay = 10,
	EVROverlayError_VROverlayError_InvalidHandle = 11,
	EVROverlayError_VROverlayError_PermissionDenied = 12,
	EVROverlay_Error_VROverlay_Error_Overlay_حد_Exceeded = 13,
	EVROverlayError_VROverlayError_WrongVisibilityType = 14,
	EVROverlay_Error_VROverlay_Error_کلید_Too_Long = 15,
	EVROverlayError_VROverlayError_NameTooLong = 16,
	EVROverlay_Error_VROverlay_Error_کلید_درون_Use = 17,
	EVROverlayError_VROverlayError_WrongTransformType = 18,
	EVROverlayError_VROverlayError_InvalidTrackedDevice = 19,
	EVROverlayError_VROverlayError_InvalidParameter = 20,
	EVROverlayError_VROverlayError_ThumbnailCantBeDestroyed = 21,
	EVROverlayError_VROverlayError_ArrayTooSmall = 22,
	EVROverlayError_VROverlayError_RequestFailed = 23,
	EVROverlayError_VROverlayError_InvalidTexture = 24,
	EVROverlay_Error_VROverlay_Error_Unable_مقصد_بارگیری_File = 25,
	EVROverlay_Error_VROverlay_Error_Keyboard_Already_درون_Use = 26,
	EVROverlayError_VROverlayError_NoNeighbor = 27,
	EVROverlay_Error_VROverlay_Error_Too_Many_ماسک_Primitives = 29,
	EVROverlay_Error_VROverlay_Error_Bad_ماسک_Primitive = 30,
	EVROverlayError_VROverlayError_TextureAlreadyLocked = 31,
	EVROverlay_Error_VROverlay_Error_Texture_قفل_ظرفیت_Reached = 32,
	EVROverlayError_VROverlayError_TextureNotLocked = 33,
	EVROverlay_Error_VROverlay_Error_Timed_بیرون = 34,
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
	EVRApplication_Type_VRApplication_جا_View = 13,
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
	EVRNotification_Error_VRNotification_Error_Notification_صف_پر = 101,
	EVRNotificationError_VRNotificationError_InvalidOverlayHandle = 102,
	EVRNotification_Error_VRNotification_Error_System_With_User_مقدار_Already_Exists = 103,
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
	EVRSkeletal_Tracking_Level_VRSkeletal_Tracking_پر = 2,
	EVRSkeletal_Tracking_Level_VRSkeletal_Tracking_Level_شمار = 3,
	EVRSkeletalTrackingLevel_VRSkeletalTrackingLevel_Max = 2,
} EVRSkeletalTrackingLevel;

تعريفنوع تعداد EVRInitError
{
	EVRInitError_VRInitError_None = 0,
	EVRInitError_VRInitError_Unknown = 1,
	EVRInit_Error_VRInit_Error_Init_Installation_Not_یافت = 100,
	EVRInitError_VRInitError_Init_InstallationCorrupt = 101,
	EVRInit_Error_VRInit_Error_Init_VRClient_DLLNot_یافت = 102,
	EVRInit_Error_VRInit_Error_Init_File_Not_یافت = 103,
	EVRInit_Error_VRInit_Error_Init_Factory_Not_یافت = 104,
	EVRInit_Error_VRInit_Error_Init_Interface_Not_یافت = 105,
	EVRInitError_VRInitError_Init_InvalidInterface = 106,
	EVRInitError_VRInitError_Init_UserConfigDirectoryInvalid = 107,
	EVRInit_Error_VRInit_Error_Init_Hmd_Not_یافت = 108,
	EVRInitError_VRInitError_Init_NotInitialized = 109,
	EVRInit_Error_VRInit_Error_Init_مسیر_Registry_Not_یافت = 110,
	EVRInit_Error_VRInit_Error_Init_No_Config_مسیر = 111,
	EVRInit_Error_VRInit_Error_Init_No_Log_مسیر = 112,
	EVRInit_Error_VRInit_Error_Init_مسیر_Registry_Not_Writable = 113,
	EVRInitError_VRInitError_Init_AppInfoInitFailed = 114,
	EVRInitError_VRInitError_Init_Retry = 115,
	EVRInitError_VRInitError_Init_InitCanceledByUser = 116,
	EVRInitError_VRInitError_Init_AnotherAppLaunching = 117,
	EVRInitError_VRInitError_Init_SettingsInitFailed = 118,
	EVRInit_Error_VRInit_Error_Init_Shutting_پایین = 119,
	EVRInitError_VRInitError_Init_TooManyObjects = 120,
	EVRInitError_VRInitError_Init_NoServerForBackgroundApp = 121,
	EVRInitError_VRInitError_Init_NotSupportedWithCompositor = 122,
	EVRInit_Error_VRInit_Error_Init_Not_موجود_مقصد_Utility_Apps = 123,
	EVRInit_Error_VRInit_Error_Init_داخلی = 124,
	EVRInitError_VRInitError_Init_HmdDriverIdIsNone = 125,
	EVRInit_Error_VRInit_Error_Init_Hmd_Not_یافت_Presence_Failed = 126,
	EVRInit_Error_VRInit_Error_Init_VRMonitor_Not_یافت = 127,
	EVRInitError_VRInitError_Init_VRMonitorStartupFailed = 128,
	EVRInit_Error_VRInit_Error_Init_کم_Power_Watchdog_Not_Supported = 129,
	EVRInitError_VRInitError_Init_InvalidApplicationType = 130,
	EVRInit_Error_VRInit_Error_Init_Not_موجود_مقصد_Watchdog_Apps = 131,
	EVRInit_Error_VRInit_Error_Init_Watchdog_Disabled_درون_Settings = 132,
	EVRInit_Error_VRInit_Error_Init_VRDashboard_Not_یافت = 133,
	EVRInitError_VRInitError_Init_VRDashboardStartupFailed = 134,
	EVRInit_Error_VRInit_Error_Init_VRHome_Not_یافت = 135,
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
	EVRInit_Error_VRInit_Error_Init_Prism_Startup_Timed_بیرون = 152,
	EVRInit_Error_VRInit_Error_Init_Could_Not_شروع_Prism = 153,
	EVRInitError_VRInitError_Init_PrismClientInitFailed = 154,
	EVRInit_Error_VRInit_Error_Init_Prism_Client_شروع_Failed = 155,
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
	EVRInit_Error_VRInit_Error_Init_VRDashboard_مسیر_Failure = 167,
	EVRInitError_VRInitError_Driver_Failed = 200,
	EVRInitError_VRInitError_Driver_Unknown = 201,
	EVRInitError_VRInitError_Driver_HmdUnknown = 202,
	EVRInitError_VRInitError_Driver_NotLoaded = 203,
	EVRInit_Error_VRInit_Error_Driver_Runtime_بیرون_از_Date = 204,
	EVRInit_Error_VRInit_Error_Driver_Hmd_درون_Use = 205,
	EVRInitError_VRInitError_Driver_NotCalibrated = 206,
	EVRInitError_VRInitError_Driver_CalibrationInvalid = 207,
	EVRInit_Error_VRInit_Error_Driver_Hmd_Display_Not_یافت = 208,
	EVRInitError_VRInitError_Driver_TrackedDeviceInterfaceUnknown = 209,
	EVRInit_Error_VRInit_Error_Driver_Hmd_Driver_Id_بیرون_از_Bounds = 211,
	EVRInitError_VRInitError_Driver_HmdDisplayMirrored = 212,
	EVRInit_Error_VRInit_Error_Driver_Hmd_Display_Not_یافت_Laptop = 213,
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
	EVRInit_Error_VRInit_Error_IPC_Connect_Failed_After_هدف_Exited = 309,
	EVRInitError_VRInitError_IPC_NamespaceUnavailable = 310,
	EVRInitError_VRInitError_Compositor_Failed = 400,
	EVRInitError_VRInitError_Compositor_D3D11HardwareRequired = 401,
	EVRInitError_VRInitError_Compositor_FirmwareRequiresUpdate = 402,
	EVRInitError_VRInitError_Compositor_OverlayInitFailed = 403,
	EVRInitError_VRInitError_Compositor_ScreenshotsInitFailed = 404,
	EVRInit_Error_VRInit_Error_Compositor_Unable_مقصد_Create_Device = 405,
	EVRInitError_VRInitError_Compositor_SharedStateIsNull = 406,
	EVRInitError_VRInitError_Compositor_NotificationManagerIsNull = 407,
	EVRInitError_VRInitError_Compositor_ResourceManagerClientIsNull = 408,
	EVRInit_Error_VRInit_Error_Compositor_پیام_Overlay_Shared_State_Init_Failure = 409,
	EVRInitError_VRInitError_Compositor_PropertiesInterfaceIsNull = 410,
	EVRInit_Error_VRInit_Error_Compositor_Create_Fullscreen_پنجره_Failed = 411,
	EVRInitError_VRInitError_Compositor_SettingsInterfaceIsNull = 412,
	EVRInit_Error_VRInit_Error_Compositor_Failed_مقصد_Show_پنجره = 413,
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
	EVRInit_Error_VRInit_Error_Compositor_Failed_مقصد_پیدا_کن_Display_نما = 425,
	EVRInit_Error_VRInit_Error_Compositor_Failed_مقصد_Create_جابجا_Chain = 426,
	EVRInit_Error_VRInit_Error_Compositor_Failed_مقصد_Get_پشت_میانگیر = 427,
	EVRInit_Error_VRInit_Error_Compositor_Failed_مقصد_Create_Render_هدف = 428,
	EVRInit_Error_VRInit_Error_Compositor_Failed_مقصد_Create_DXGI2_جابجا_Chain = 429,
	EVRInit_Error_VRInit_Error_Compositor_Failedto_Get_DXGI2_پشت_میانگیر = 430,
	EVRInit_Error_VRInit_Error_Compositor_Failed_مقصد_Create_DXGI2_Render_هدف = 431,
	EVRInit_Error_VRInit_Error_Compositor_Failed_مقصد_Get_DXGIDevice_Interface = 432,
	EVRInit_Error_VRInit_Error_Compositor_Select_Display_نما = 433,
	EVRInit_Error_VRInit_Error_Compositor_Failed_مقصد_Create_Nv_APIRender_Targets = 434,
	EVRInit_Error_VRInit_Error_Compositor_Nv_APISet_Display_نما = 435,
	EVRInit_Error_VRInit_Error_Compositor_Failed_مقصد_Create_مستقیم_نما_Display = 436,
	EVRInitError_VRInitError_Compositor_InvalidHmdPropertyContainer = 437,
	EVRInitError_VRInitError_Compositor_UpdateDisplayFrequency = 438,
	EVRInitError_VRInitError_Compositor_CreateRasterizerState = 439,
	EVRInitError_VRInitError_Compositor_CreateWireframeRasterizerState = 440,
	EVRInitError_VRInitError_Compositor_CreateSamplerState = 441,
	EVRInit_Error_VRInit_Error_Compositor_Create_Clamp_مقصد_Border_Sampler_State = 442,
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
	EVRInit_Error_VRInit_Error_Compositor_Create_عمق_Stencil_State = 453,
	EVRInit_Error_VRInit_Error_Compositor_Create_عمق_Stencil_State_No_Write = 454,
	EVRInit_Error_VRInit_Error_Compositor_Create_عمق_Stencil_State_No_عمق = 455,
	EVRInitError_VRInitError_Compositor_CreateFlushTexture = 456,
	EVRInitError_VRInitError_Compositor_CreateDistortionSurfaces = 457,
	EVRInit_Error_VRInit_Error_Compositor_Create_Constant_میانگیر = 458,
	EVRInit_Error_VRInit_Error_Compositor_Create_Hmd_Pose_Constant_میانگیر = 459,
	EVRInit_Error_VRInit_Error_Compositor_Create_Hmd_Pose_Staging_Constant_میانگیر = 460,
	EVRInit_Error_VRInit_Error_Compositor_Create_Shared_قاب_Info_Constant_میانگیر = 461,
	EVRInit_Error_VRInit_Error_Compositor_Create_Overlay_Constant_میانگیر = 462,
	EVRInit_Error_VRInit_Error_Compositor_Create_Scene_Texture_شاخص_Constant_میانگیر = 463,
	EVRInit_Error_VRInit_Error_Compositor_Create_Readable_Scene_Texture_شاخص_Constant_میانگیر = 464,
	EVRInit_Error_VRInit_Error_Compositor_Create_Layer_Graphics_Texture_شاخص_Constant_میانگیر = 465,
	EVRInit_Error_VRInit_Error_Compositor_Create_Layer_Compute_Texture_شاخص_Constant_میانگیر = 466,
	EVRInit_Error_VRInit_Error_Compositor_Create_Layer_Compute_Scene_Texture_شاخص_Constant_میانگیر = 467,
	EVRInit_Error_VRInit_Error_Compositor_Create_Compute_Hmd_Pose_Constant_میانگیر = 468,
	EVRInit_Error_VRInit_Error_Compositor_Create_Geom_Constant_میانگیر = 469,
	EVRInit_Error_VRInit_Error_Compositor_Create_Panel_ماسک_Constant_میانگیر = 470,
	EVRInitError_VRInitError_Compositor_CreatePixelSimUBO = 471,
	EVRInitError_VRInitError_Compositor_CreateMSAARenderTextures = 472,
	EVRInitError_VRInitError_Compositor_CreateResolveRenderTextures = 473,
	EVRInitError_VRInitError_Compositor_CreateComputeResolveRenderTextures = 474,
	EVRInit_Error_VRInit_Error_Compositor_Create_Driver_مستقیم_نما_Resolve_Textures = 475,
	EVRInit_Error_VRInit_Error_Compositor_Open_Driver_مستقیم_نما_Resolve_Textures = 476,
	EVRInitError_VRInitError_Compositor_CreateFallbackSyncTexture = 477,
	EVRInitError_VRInitError_Compositor_ShareFallbackSyncTexture = 478,
	EVRInit_Error_VRInit_Error_Compositor_Create_Overlay_شاخص_میانگیر = 479,
	EVRInit_Error_VRInit_Error_Compositor_Create_Overlay_رأس_میانگیر = 480,
	EVRInit_Error_VRInit_Error_Compositor_Create_متن_رأس_میانگیر = 481,
	EVRInit_Error_VRInit_Error_Compositor_Create_متن_شاخص_میانگیر = 482,
	EVRInitError_VRInitError_Compositor_CreateMirrorTextures = 483,
	EVRInit_Error_VRInit_Error_Compositor_Create_آخرین_قاب_Render_Texture = 484,
	EVRInitError_VRInitError_Compositor_CreateMirrorOverlay = 485,
	EVRInit_Error_VRInit_Error_Compositor_Failed_مقصد_Create_Virtual_Display_Backbuffer = 486,
	EVRInit_Error_VRInit_Error_Compositor_Display_نما_Not_Supported = 487,
	EVRInitError_VRInitError_Compositor_CreateOverlayInvalidCall = 488,
	EVRInitError_VRInitError_Compositor_CreateOverlayAlreadyInitialized = 489,
	EVRInit_Error_VRInit_Error_Compositor_Failed_مقصد_Create_Mailbox = 490,
	EVRInit_Error_VRInit_Error_Compositor_پنجره_Interface_Is_Null = 491,
	EVRInitError_VRInitError_Compositor_SystemLayerCreateInstance = 492,
	EVRInitError_VRInitError_Compositor_SystemLayerCreateSession = 493,
	EVRInitError_VRInitError_Compoistor_CreateInverseDistortUVs = 494,
	EVRInit_Error_VRInit_Error_Compoistor_Create_Backbuffer_عمق = 495,
	EVRInit_Error_VRInit_Error_Vendor_Specific_Unable_مقصد_Connect_مقصد_Oculus_Runtime = 1000,
	EVRInit_Error_VRInit_Error_Vendor_Specific_Windows_Not_درون_Dev_نما = 1001,
	EVRInitError_VRInitError_VendorSpecific_OculusLinkNotEnabled = 1002,
	EVRInit_Error_VRInit_Error_Vendor_Specific_Hmd_یافت_Cant_Open_Device = 1101,
	EVRInit_Error_VRInit_Error_Vendor_Specific_Hmd_یافت_Unable_مقصد_Request_Config_شروع = 1102,
	EVRInit_Error_VRInit_Error_Vendor_Specific_Hmd_یافت_No_Stored_Config = 1103,
	EVRInit_Error_VRInit_Error_Vendor_Specific_Hmd_یافت_Config_Too_Big = 1104,
	EVRInit_Error_VRInit_Error_Vendor_Specific_Hmd_یافت_Config_Too_Small = 1105,
	EVRInit_Error_VRInit_Error_Vendor_Specific_Hmd_یافت_Unable_مقصد_Init_ZLib = 1106,
	EVRInit_Error_VRInit_Error_Vendor_Specific_Hmd_یافت_Cant_Read_Firmware_نسخه = 1107,
	EVRInit_Error_VRInit_Error_Vendor_Specific_Hmd_یافت_Unable_مقصد_Send_User_داده_شروع = 1108,
	EVRInit_Error_VRInit_Error_Vendor_Specific_Hmd_یافت_Unable_مقصد_Get_User_داده_شروع = 1109,
	EVRInit_Error_VRInit_Error_Vendor_Specific_Hmd_یافت_Unable_مقصد_Get_User_داده_بعدی = 1110,
	EVRInit_Error_VRInit_Error_Vendor_Specific_Hmd_یافت_User_داده_آدرس_Range = 1111,
	EVRInit_Error_VRInit_Error_Vendor_Specific_Hmd_یافت_User_داده_Error = 1112,
	EVRInit_Error_VRInit_Error_Vendor_Specific_Hmd_یافت_Config_Failed_Sanity_Check = 1113,
	EVRInitError_VRInitError_VendorSpecific_OculusRuntimeBadInstall = 1114,
	EVRInit_Error_VRInit_Error_Vendor_Specific_Hmd_یافت_Unexpected_Configuration_1 = 1115,
	EVRInit_Error_VRInit_Error_Steam_Steam_Installation_Not_یافت = 2000,
	EVRInit_Error_VRInit_Error_آخرین_Error = 2001,
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
	EVRTracked_Camera_Error_VRTracked_Camera_Error_Invalid_قاب_سرآیند_نسخه = 102,
	EVRTracked_Camera_Error_VRTracked_Camera_Error_بیرون_از_Handles = 103,
	EVRTrackedCameraError_VRTrackedCameraError_IPCFailure = 104,
	EVRTrackedCameraError_VRTrackedCameraError_NotSupportedForThisDevice = 105,
	EVRTracked_Camera_Error_VRTracked_Camera_Error_Shared_حافظه_Failure = 106,
	EVRTracked_Camera_Error_VRTracked_Camera_Error_قاب_Buffering_Failure = 107,
	EVRTracked_Camera_Error_VRTracked_Camera_Error_جریان_راهاندازی_Failure = 108,
	EVRTrackedCameraError_VRTrackedCameraError_InvalidGLTextureId = 109,
	EVRTrackedCameraError_VRTrackedCameraError_InvalidSharedTextureHandle = 110,
	EVRTracked_Camera_Error_VRTracked_Camera_Error_Failed_مقصد_Get_GLTexture_Id = 111,
	EVRTrackedCameraError_VRTrackedCameraError_SharedTextureFailure = 112,
	EVRTracked_Camera_Error_VRTracked_Camera_Error_No_قاب_موجود = 113,
	EVRTracked_Camera_Error_VRTracked_Camera_Error_Invalid_آرگومان = 114,
	EVRTracked_Camera_Error_VRTracked_Camera_Error_Invalid_قاب_میانگیر_اندازه = 115,
} EVRTrackedCameraError;

تعريفنوع تعداد EVRTracked_Camera_قاب_Layout
{
	EVRTracked_Camera_قاب_Layout_Mono = 1,
	EVRTracked_Camera_قاب_Layout_Stereo = 2,
	EVRTracked_Camera_قاب_Layout_Vertical_Layout = 16,
	EVRTracked_Camera_قاب_Layout_Horizontal_Layout = 32,
} EVRTracked_Camera_قاب_Layout;

تعريفنوع تعداد EVRTracked_Camera_قاب_Type
{
	EVRTracked_Camera_قاب_Type_VRTracked_Camera_قاب_Type_Distorted = 0,
	EVRTracked_Camera_قاب_Type_VRTracked_Camera_قاب_Type_Undistorted = 1,
	EVRTracked_Camera_قاب_Type_VRTracked_Camera_قاب_Type_بیشینه_Undistorted = 2,
	EVRTracked_Camera_قاب_Type_MAX_CAMERA_قاب_TYPES = 3,
} EVRTracked_Camera_قاب_Type;

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

تعريفنوع تعداد EVRMura_Correction_نما
{
	EVRMura_Correction_نما_Default = 0,
	EVRMura_Correction_نما_No_Correction = 1,
} EVRMura_Correction_نما;

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
	EVRApplication_Error_VRApplication_Error_App_کلید_Already_Exists = 100,
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
	EVRApplication_Error_VRApplication_Error_Launch_درون_پیشرفت = 111,
	EVRApplicationError_VRApplicationError_OldApplicationQuitting = 112,
	EVRApplicationError_VRApplicationError_TransitionAborted = 113,
	EVRApplicationError_VRApplicationError_IsTemplate = 114,
	EVRApplicationError_VRApplicationError_SteamVRIsExiting = 115,
	EVRApplication_Error_VRApplication_Error_میانگیر_Too_Small = 200,
	EVRApplication_Error_VRApplication_Error_Property_Not_مجموعه = 201,
	EVRApplicationError_VRApplicationError_UnknownProperty = 202,
	EVRApplicationError_VRApplicationError_InvalidParameter = 203,
	EVRApplicationError_VRApplicationError_NotImplemented = 300,
} EVRApplicationError;

تعريفنوع تعداد EVRApplicationProperty
{
	EVRApplicationProperty_VRApplicationProperty_Name_String = 0,
	EVRApplicationProperty_VRApplicationProperty_LaunchType_String = 11,
	EVRApplicationProperty_VRApplicationProperty_WorkingDirectory_String = 12,
	EVRApplication_Property_VRApplication_Property_دودویی_مسیر_String = 13,
	EVRApplicationProperty_VRApplicationProperty_Arguments_String = 14,
	EVRApplicationProperty_VRApplicationProperty_URL_String = 15,
	EVRApplicationProperty_VRApplicationProperty_Description_String = 50,
	EVRApplicationProperty_VRApplicationProperty_NewsURL_String = 51,
	EVRApplication_Property_VRApplication_Property_Image_مسیر_String = 52,
	EVRApplication_Property_VRApplication_Property_منبع_String = 53,
	EVRApplicationProperty_VRApplicationProperty_ActionManifestURL_String = 54,
	EVRApplicationProperty_VRApplicationProperty_IsDashboardOverlay_Bool = 60,
	EVRApplicationProperty_VRApplicationProperty_IsTemplate_Bool = 61,
	EVRApplicationProperty_VRApplicationProperty_IsInstanced_Bool = 62,
	EVRApplication_Property_VRApplication_Property_Is_داخلی_Bool = 63,
	EVRApplication_Property_VRApplication_Property_میخواهد_Compositor_Pause_درون_Standby_Bool = 64,
	EVRApplicationProperty_VRApplicationProperty_IsHidden_Bool = 65,
	EVRApplication_Property_VRApplication_Property_آخرین_Launch_زمان_Uint64 = 70,
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
	Chaperone_Calibration_State_Warning_پایه_Station_May_Have_Moved = 101,
	Chaperone_Calibration_State_Warning_پایه_Station_Removed = 102,
	ChaperoneCalibrationState_Warning_SeatedBoundsInvalid = 103,
	ChaperoneCalibrationState_Error = 200,
	Chaperone_Calibration_State_Error_پایه_Station_Uninitialized = 201,
	Chaperone_Calibration_State_Error_پایه_Station_Conflict = 202,
	ChaperoneCalibrationState_Error_PlayAreaInvalid = 203,
	ChaperoneCalibrationState_Error_CollisionBoundsInvalid = 204,
} ChaperoneCalibrationState;

تعريفنوع تعداد EChaperoneConfigFile
{
	EChaperone_Config_File_زنده = 1,
	EChaperone_Config_File_موقت = 2,
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
	EVRCompositor_Error_VRCompositor_Error_Texture_استفاده_میکند_Unsupported_Format = 105,
	EVRCompositorError_VRCompositorError_SharedTexturesNotSupported = 106,
	EVRCompositor_Error_VRCompositor_Error_شاخص_بیرون_از_Range = 107,
	EVRCompositorError_VRCompositorError_AlreadySubmitted = 108,
	EVRCompositorError_VRCompositorError_InvalidBounds = 109,
	EVRCompositor_Error_VRCompositor_Error_Already_مجموعه = 110,
} EVRCompositorError;

تعريفنوع تعداد EVRCompositor_Timing_نما
{
	EVRCompositor_Timing_نما_VRCompositor_Timing_نما_Implicit = 0,
	EVRCompositor_Timing_نما_VRCompositor_Timing_نما_Explicit_Runtime_Performs_Post_Present_Handoff = 1,
	EVRCompositor_Timing_نما_VRCompositor_Timing_نما_Explicit_Application_Performs_Post_Present_Handoff = 2,
} EVRCompositor_Timing_نما;

تعريفنوع تعداد VROverlay_درون_داد_روش
{
	VROverlay_درون_داد_روش_None = 0,
	VROverlay_درون_داد_روش_Mouse = 1,
} VROverlay_درون_داد_روش;

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
	VROverlay_Flags_Transfer_Ownership_مقصد_داخلی_Process = 512,
	VROverlayFlags_SideBySide_Parallel = 1024,
	VROverlayFlags_SideBySide_Crossed = 2048,
	VROverlayFlags_Panorama = 4096,
	VROverlayFlags_StereoPanorama = 8192,
	VROverlay_Flags_مرتب_سازی_With_Non_Scene_Overlays = 16384,
	VROverlay_Flags_Visible_درون_Dashboard = 32768,
	VROverlayFlags_MakeOverlaysInteractiveIfVisible = 65536,
	VROverlayFlags_SendVRSmoothScrollEvents = 131072,
	VROverlayFlags_ProtectedContent = 262144,
	VROverlayFlags_HideLaserIntersection = 524288,
	VROverlay_Flags_میخواهد_Modal_Behavior = 1048576,
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
	VRMessage_Overlay_Response_Couldnt_پیدا_کن_System_Overlay = 4,
	VRMessage_Overlay_Response_Couldnt_پیدا_کن_Or_Create_Client_Overlay = 5,
	VRMessageOverlayResponse_ApplicationQuit = 6,
} VRMessageOverlayResponse;

تعريفنوع تعداد EGamepad_متن_درون_داد_نما
{
	EGamepad_متن_درون_داد_نما_k_EGamepad_متن_درون_داد_نما_نرمال = 0,
	EGamepad_متن_درون_داد_نما_k_EGamepad_متن_درون_داد_نما_Password = 1,
	EGamepad_متن_درون_داد_نما_k_EGamepad_متن_درون_داد_نما_Submit = 2,
} EGamepad_متن_درون_داد_نما;

تعريفنوع تعداد EGamepad_متن_درون_داد_سطر_نما
{
	EGamepad_متن_درون_داد_سطر_نما_k_EGamepad_متن_درون_داد_سطر_نما_Single_سطر = 0,
	EGamepad_متن_درون_داد_سطر_نما_k_EGamepad_متن_درون_داد_سطر_نما_مضرب_سطرها = 1,
} EGamepad_متن_درون_داد_سطر_نما;

تعريفنوع تعداد EVROverlay_Intersection_ماسک_Primitive_Type
{
	EVROverlay_Intersection_ماسک_Primitive_Type_Overlay_Intersection_Primitive_Type_Rectangle = 0,
	EVROverlay_Intersection_ماسک_Primitive_Type_Overlay_Intersection_Primitive_Type_Circle = 1,
} EVROverlay_Intersection_ماسک_Primitive_Type;

تعريفنوع تعداد EKeyboardFlags
{
	EKeyboard_Flags_Keyboard_Flag_کمینه = 1,
	EKeyboardFlags_KeyboardFlag_Modal = 2,
} EKeyboardFlags;

تعريفنوع تعداد EDeviceType
{
	EDeviceType_DeviceType_Invalid = -1,
	EDevice_Type_Device_Type_مستقیم_X11 = 0,
	EDeviceType_DeviceType_Vulkan = 1,
} EDeviceType;

تعريفنوع تعداد Headset_View_نما_t
{
	Headset_View_نما_t_Headset_View_نما_چپ = 0,
	Headset_View_نما_t_Headset_View_نما_راست = 1,
	Headset_View_نما_t_Headset_View_نما_Both = 2,
} Headset_View_نما_t;

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
	EVRRender_Model_Error_VRRender_Model_Error_میانگیر_Too_Small = 306,
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
	EVRNotification_Type_Transient_System_With_User_مقدار = 2,
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
	EVRScreenshot_Error_VRScreenshot_Error_Not_یافت = 101,
	EVRScreenshot_Error_VRScreenshot_Error_میانگیر_Too_Small = 102,
	EVRScreenshot_Error_VRScreenshot_Error_Screenshot_Already_درون_پیشرفت = 108,
} EVRScreenshotError;

تعريفنوع تعداد EVRSkeletalTransformSpace
{
	EVRSkeletalTransformSpace_VRSkeletalTransformSpace_Model = 0,
	EVRSkeletal_Transform_Space_VRSkeletal_Transform_Space_والد = 1,
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
	EVRFinger_VRFinger_میانه = 2,
	EVRFinger_VRFinger_Ring = 3,
	EVRFinger_VRFinger_Pinky = 4,
	EVRFinger_VRFinger_شمار = 5,
} EVRFinger;

تعريفنوع تعداد EVRFingerSplay
{
	EVRFinger_Splay_VRFinger_Splay_Thumb_شاخص = 0,
	EVRFinger_Splay_VRFinger_Splay_شاخص_میانه = 1,
	EVRFinger_Splay_VRFinger_Splay_میانه_Ring = 2,
	EVRFingerSplay_VRFingerSplay_Ring_Pinky = 3,
	EVRFinger_Splay_VRFinger_Splay_شمار = 4,
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

تعريفنوع تعداد EVRInput_String_بیتها
{
	EVRInput_String_بیتها_VRInput_String_Hand = 1,
	EVRInput_String_بیتها_VRInput_String_Controller_Type = 2,
	EVRInput_String_بیتها_VRInput_String_درون_داد_منبع = 4,
	EVRInput_String_بیتها_VRInput_String_All = -1,
} EVRInput_String_بیتها;

تعريفنوع تعداد EIOBufferError
{
	EIOBufferError_IOBuffer_Success = 0,
	EIOBufferError_IOBuffer_OperationFailed = 100,
	EIOBufferError_IOBuffer_InvalidHandle = 101,
	EIOBuffer_Error_IOBuffer_Invalid_آرگومان = 102,
	EIOBuffer_Error_IOBuffer_مسیر_Exists = 103,
	EIOBuffer_Error_IOBuffer_مسیر_Does_Not_Exist = 104,
	EIOBufferError_IOBuffer_Permission = 105,
} EIOBufferError;

تعريفنوع تعداد EIOBuffer_نما
{
	EIOBuffer_نما_IOBuffer_نما_Read = 1,
	EIOBuffer_نما_IOBuffer_نما_Write = 2,
	EIOBuffer_نما_IOBuffer_نما_Create = 512,
} EIOBuffer_نما;

تعريفنوع تعداد EVRDebugError
{
	EVRDebugError_VRDebugError_Success = 0,
	EVRDebugError_VRDebugError_BadParameter = 1,
} EVRDebugError;

تعريفنوع تعداد EPropertyWriteType
{
	EProperty_Write_Type_Property_Write_مجموعه = 0,
	EPropertyWriteType_PropertyWrite_Erase = 1,
	EProperty_Write_Type_Property_Write_مجموعه_Error = 2,
} EPropertyWriteType;

تعريفنوع تعداد EBlock_صف_Error
{
	EBlock_صف_Error_بلوک_صف_Error_None = 0,
	EBlock_صف_Error_بلوک_صف_Error_صف_Already_Exists = 1,
	EBlock_صف_Error_بلوک_صف_Error_صف_Not_یافت = 2,
	EBlock_صف_Error_بلوک_صف_Error_بلوک_Not_موجود = 3,
	EBlock_صف_Error_بلوک_صف_Error_Invalid_Handle = 4,
	EBlock_صف_Error_بلوک_صف_Error_Invalid_Param = 5,
	EBlock_صف_Error_بلوک_صف_Error_Param_Mismatch = 6,
	EBlock_صف_Error_بلوک_صف_Error_داخلی_Error = 7,
	EBlock_صف_Error_بلوک_صف_Error_Already_Initialized = 8,
	EBlock_صف_Error_بلوک_صف_Error_Operation_Is_Server_Only = 9,
	EBlock_صف_Error_بلوک_صف_Error_Too_Many_Connections = 10,
} EBlock_صف_Error;

تعريفنوع تعداد EBlock_صف_Read_Type
{
	EBlock_صف_Read_Type_بلوک_صف_Read_Latest = 0,
	EBlock_صف_Read_Type_بلوک_صف_Read_New = 1,
	EBlock_صف_Read_Type_بلوک_صف_Read_بعدی = 2,
} EBlock_صف_Read_Type;

تعريفنوع تعداد EBlock_صف_Creation_Flag
{
	EBlock_صف_Creation_Flag_بلوک_صف_Flag_Owner_Is_Reader = 1,
} EBlock_صف_Creation_Flag;


// OpenVR typedefs

تعريفنوع uint32_t Property_Type_برچسب_t;
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
تعريفنوع uint64_t VRAction_مجموعه_Handle_t;
تعريفنوع uint64_t VRInput_مقدار_Handle_t;
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
تعريفنوع ETracking_نتیجه Hmd_Tracking_نتیجه;
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
تعريفنوع uint64_t مسیر_Handle_t;

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
	بنية HmdVector2_t v_بالاترین_چپ;
	بنية HmdVector2_t v_Bottom_راست;
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
	بنية HmdMatrix34_t m_Device_مقصد_Absolute_Tracking;
	بنية HmdVector3_t vVelocity;
	بنية HmdVector3_t vAngularVelocity;
	تعداد ETracking_نتیجه e_Tracking_نتیجه;
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
	بنية HmdMatrix34_t m_Device_مقصد_Absolute_Tracking;
} VRTextureWithPose_t;

تعريفنوع بنية VRTexture_عمق_Info_t
{
	فراغ * handle; // void *
	بنية HmdMatrix44_t mProjection;
	بنية HmdVector2_t vRange;
} VRTexture_عمق_Info_t;

تعريفنوع بنية VRTexture_With_عمق_t
{
	فراغ * handle; // void *
	تعداد ETextureType eType;
	تعداد EColorSpace eColorSpace;
	بنية VRTexture_عمق_Info_t عمق_2;
} VRTexture_With_عمق_t;

تعريفنوع بنية VRTexture_With_Pose_And_عمق_t
{
	فراغ * handle; // void *
	تعداد ETextureType eType;
	تعداد EColorSpace eColorSpace;
	بنية HmdMatrix34_t m_Device_مقصد_Absolute_Tracking;
	بنية VRTexture_عمق_Info_t عمق_2;
} VRTexture_With_Pose_And_عمق_t;

تعريفنوع بنية VRVulkan_Texture_داده_t
{
	uint64_t m_nImage;
	بنية VkDevice_T * m_pDevice; // struct VkDevice_T *
	بنية VkPhysicalDevice_T * m_pPhysicalDevice; // struct VkPhysicalDevice_T *
	بنية VkInstance_T * m_pInstance; // struct VkInstance_T *
	بنية Vk_صف_T * m_p_صف; // struct VkQueue_T *
	uint32_t m_n_صف_Family_شاخص;
	uint32_t m_n_عرض;
	uint32_t m_n_ارتفاع;
	uint32_t m_nFormat;
	uint32_t m_n_Sample_شمار;
} VRVulkan_Texture_داده_t;

تعريفنوع بنية VRVulkan_Texture_Array_داده_t
{
	uint32_t m_un_Array_شاخص;
	uint32_t m_un_Array_اندازه;
} VRVulkan_Texture_Array_داده_t;

تعريفنوع بنية D3_D12_Texture_داده_t
{
	بنية ID3D12Resource * m_pResource; // struct ID3D12Resource *
	بنية ID3_D12_Command_صف * m_p_Command_صف; // struct ID3D12CommandQueue *
	uint32_t m_n_گره_ماسک;
} D3_D12_Texture_داده_t;

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
	uint32_t استفادهنشده;
	عائم viewportscale;
} VREvent_Scroll_t;

تعريفنوع بنية VREvent_TouchPadMove_t
{
	bool b_Finger_پایین;
	عائم fl_Seconds_Finger_پایین;
	عائم f_مقدار_XFirst;
	عائم f_مقدار_YFirst;
	عائم f_مقدار_XRaw;
	عائم f_مقدار_YRaw;
} VREvent_TouchPadMove_t;

تعريفنوع بنية VREvent_Notification_t
{
	uint64_t ul_User_مقدار;
	uint32_t notificationId;
} VREvent_Notification_t;

تعريفنوع بنية VREvent_Process_t
{
	uint32_t pid;
	uint32_t oldPid;
	bool bForced;
	bool b_Connection_گمشده;
} VREvent_Process_t;

تعريفنوع بنية VREvent_Overlay_t
{
	uint64_t overlayHandle;
	uint64_t device_مسیر;
	uint64_t حافظه_بلوک_Id;
} VREvent_Overlay_t;

تعريفنوع بنية VREvent_وضعیت_t
{
	uint32_t وضعیت_State;
} VREvent_وضعیت_t;

تعريفنوع بنية VREvent_Keyboard_t
{
	حرف c_New_درون_داد[8]; //char[8]
	uint64_t u_User_مقدار;
} VREvent_Keyboard_t;

تعريفنوع بنية VREvent_Ipd_t
{
	عائم ipdMeters;
} VREvent_Ipd_t;

تعريفنوع بنية VREvent_Chaperone_t
{
	uint64_t m_n_قبلی_Universe;
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

تعريفنوع بنية VREvent_Screenshot_پیشرفت_t
{
	عائم پیشرفت_2;
} VREvent_Screenshot_پیشرفت_t;

تعريفنوع بنية VREvent_ApplicationLaunch_t
{
	uint32_t pid;
	uint32_t un_آرگومانها_Handle;
} VREvent_ApplicationLaunch_t;

تعريفنوع بنية VREvent_EditingCameraSurface_t
{
	uint64_t overlayHandle;
	uint32_t n_Visual_نما;
} VREvent_EditingCameraSurface_t;

تعريفنوع بنية VREvent_پیام_Overlay_t
{
	uint32_t unVRMessageOverlayResponse;
} VREvent_پیام_Overlay_t;

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

تعريفنوع بنية VREvent_درون_داد_Binding_بارگیری_t
{
	PropertyContainerHandle_t ulAppContainer;
	uint64_t مسیر_پیام;
	uint64_t مسیر_Url;
	uint64_t مسیر_Controller_Type;
} VREvent_درون_داد_Binding_بارگیری_t;

تعريفنوع بنية VREvent_درون_داد_Action_Manifest_بارگیری_t
{
	uint64_t مسیر_App_کلید;
	uint64_t مسیر_پیام;
	uint64_t مسیر_پیام_Param;
	uint64_t مسیر_Manifest_مسیر;
} VREvent_درون_داد_Action_Manifest_بارگیری_t;

تعريفنوع بنية VREvent_SpatialAnchor_t
{
	SpatialAnchorHandle_t unHandle;
} VREvent_SpatialAnchor_t;

تعريفنوع بنية VREvent_پیشرفت_Update_t
{
	uint64_t ulApplicationPropertyContainer;
	uint64_t مسیر_Device;
	uint64_t مسیر_درون_داد_منبع;
	uint64_t مسیر_پیشرفت_Action;
	uint64_t مسیر_Icon;
	عائم f_پیشرفت;
} VREvent_پیشرفت_Update_t;

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
	تعداد EHDCPError e_کد;
} VREvent_HDCPError_t;

تعريفنوع بنية RenderModel_ComponentState_t
{
	بنية HmdMatrix34_t m_Tracking_مقصد_Component_Render_Model;
	بنية HmdMatrix34_t m_Tracking_مقصد_Component_Local;
	VRComponentProperties uProperties;
} RenderModel_ComponentState_t;

تعريفنوع بنية HiddenAreaMesh_t
{
	بنية HmdVector2_t * p_رأس_داده; // const struct vr::HmdVector2_t *
	uint32_t un_Triangle_شمار;
} HiddenAreaMesh_t;

تعريفنوع بنية VRControllerAxis_t
{
	عائم x;
	عائم y;
} VRControllerAxis_t;

تعريفنوع بنية VRControllerState_t
{
	uint32_t un_Packet_رقم;
	uint64_t ulButtonPressed;
	uint64_t ulButtonTouched;
	بنية VRControllerAxis_t rAxis[5]; //struct vr::VRControllerAxis_t[5]
} VRControllerState_t;

تعريفنوع بنية Camera_Video_جریان_قاب_سرآیند_t
{
	تعداد EVRTracked_Camera_قاب_Type e_قاب_Type;
	uint32_t n_عرض;
	uint32_t n_ارتفاع;
	uint32_t n_بایتها_در_هر_Pixel;
	uint32_t n_قاب_Sequence;
	بنية TrackedDevicePose_t trackedDevicePose;
	uint64_t ul_قاب_Exposure_زمان;
} Camera_Video_جریان_قاب_سرآیند_t;

تعريفنوع بنية Compositor_قاب_Timing
{
	uint32_t m_n_اندازه;
	uint32_t m_n_قاب_شاخص;
	uint32_t m_n_رقم_قاب_Presents;
	uint32_t m_n_رقم_Mis_Presented;
	uint32_t m_n_رقم_Dropped_قابها;
	uint32_t m_nReprojectionFlags;
	مزدوج m_fl_System_زمان_درون_Seconds;
	عائم m_flPreSubmitGpuMs;
	عائم m_flPostSubmitGpuMs;
	عائم m_fl_مجموع_Render_Gpu_Ms;
	عائم m_flCompositorRenderGpuMs;
	عائم m_flCompositorRenderCpuMs;
	عائم m_flCompositorIdleCpuMs;
	عائم m_fl_Client_قاب_Interval_Ms;
	عائم m_flPresentCallCpuMs;
	عائم m_flWaitForPresentCpuMs;
	عائم m_fl_Submit_قاب_Ms;
	عائم m_flWaitGetPosesCalledMs;
	عائم m_flNewPosesReadyMs;
	عائم m_fl_New_قاب_Ready_Ms;
	عائم m_fl_Compositor_Update_شروع_Ms;
	عائم m_fl_Compositor_Update_انتها_Ms;
	عائم m_fl_Compositor_Render_شروع_Ms;
	TrackedDevicePose_t m_HmdPose;
	uint32_t m_n_رقم_VSyncs_Ready_For_Use;
	uint32_t m_n_رقم_VSyncs_مقصد_اولی_View;
} Compositor_قاب_Timing;

تعريفنوع بنية Compositor_BenchmarkResults
{
	عائم m_fl_Mega_Pixels_در_هر_دومی;
	عائم m_fl_Hmd_Recommended_Mega_Pixels_در_هر_دومی;
} Compositor_BenchmarkResults;

تعريفنوع بنية Driver_مستقیم_نما_قاب_Timing
{
	uint32_t m_n_اندازه;
	uint32_t m_n_رقم_قاب_Presents;
	uint32_t m_n_رقم_Mis_Presented;
	uint32_t m_n_رقم_Dropped_قابها;
	uint32_t m_nReprojectionFlags;
} Driver_مستقیم_نما_قاب_Timing;

تعريفنوع بنية ImuSample_t
{
	مزدوج f_Sample_زمان;
	بنية HmdVector3d_t vAccel;
	بنية HmdVector3d_t vGyro;
	uint32_t unOffScaleFlags;
} ImuSample_t;

تعريفنوع بنية App_Override_کلیدها_t
{
	حرف * pch_کلید; // const char *
	حرف * pch_مقدار; // const char *
} App_Override_کلیدها_t;

تعريفنوع بنية Compositor_CumulativeStats
{
	uint32_t m_nPid;
	uint32_t m_n_رقم_قاب_Presents;
	uint32_t m_n_رقم_Dropped_قابها;
	uint32_t m_n_رقم_Reprojected_قابها;
	uint32_t m_n_رقم_قاب_Presents_On_Startup;
	uint32_t m_n_رقم_Dropped_قابها_On_Startup;
	uint32_t m_n_رقم_Reprojected_قابها_On_Startup;
	uint32_t m_n_رقم_Loading;
	uint32_t m_n_رقم_قاب_Presents_Loading;
	uint32_t m_n_رقم_Dropped_قابها_Loading;
	uint32_t m_n_رقم_Reprojected_قابها_Loading;
	uint32_t m_n_رقم_Timed_بیرون;
	uint32_t m_n_رقم_قاب_Presents_Timed_بیرون;
	uint32_t m_n_رقم_Dropped_قابها_Timed_بیرون;
	uint32_t m_n_رقم_Reprojected_قابها_Timed_بیرون;
	uint32_t m_n_رقم_قاب_Submits;
	مزدوج m_fl_جمع_Compositor_CPUTime_MS;
	مزدوج m_fl_جمع_Compositor_GPUTime_MS;
	مزدوج m_fl_جمع_هدف_قاب_Times;
	مزدوج m_fl_جمع_Application_CPUTime_MS;
	مزدوج m_fl_جمع_Application_GPUTime_MS;
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
	بنية HmdVector3_t v_منبع;
	بنية HmdVector3_t vDirection;
	تعداد ETrackingUniverseOrigin eOrigin;
} VROverlayIntersectionParams_t;

تعريفنوع بنية VROverlayIntersectionResults_t
{
	بنية HmdVector3_t v_نقطه;
	بنية HmdVector3_t v_نرمال;
	بنية HmdVector2_t vUVs;
	عائم f_فاصله;
} VROverlayIntersectionResults_t;

تعريفنوع بنية Intersection_ماسک_Rectangle_t
{
	عائم m_fl_بالاترین_چپ_X;
	عائم m_fl_بالاترین_چپ_Y;
	عائم m_fl_عرض;
	عائم m_fl_ارتفاع;
} Intersection_ماسک_Rectangle_t;

تعريفنوع بنية Intersection_ماسک_Circle_t
{
	عائم m_flCenterX;
	عائم m_flCenterY;
	عائم m_flRadius;
} Intersection_ماسک_Circle_t;

تعريفنوع بنية VROverlayProjection_t
{
	عائم f_چپ;
	عائم f_راست;
	عائم f_بالاترین;
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
	بنية Vk_صف_T * m_p_صف; // struct VkQueue_T *
	uint32_t m_u_صف_Family_شاخص;
} VRVulkanDevice_t;

تعريفنوع بنية VRNativeDevice_t
{
	فراغ * handle; // void *
	تعداد EDeviceType eType;
} VRNativeDevice_t;

تعريفنوع بنية Render_Model_رأس_t
{
	بنية HmdVector3_t vPosition;
	بنية HmdVector3_t v_نرمال;
	عائم rfTextureCoord[2]; //float[2]
} Render_Model_رأس_t;

#إذا defined(__linux__) || defined(__APPLE__)
#رهنمود pack( افزودن, 4 )
#پایان_اگر
تعريفنوع بنية RenderModel_TextureMap_t
{
	uint16_t un_عرض;
	uint16_t un_ارتفاع;
	uint8_t * rub_Texture_Map_داده; // const uint8_t *
	تعداد EVRRenderModelTextureFormat format;
	uint16_t un_Mip_سطوح;
} RenderModel_TextureMap_t;

#إذا defined(__linux__) || defined(__APPLE__)
#رهنمود pack( برداشت )
#پایان_اگر
#إذا defined(__linux__) || defined(__APPLE__)
#رهنمود pack( افزودن, 4 )
#پایان_اگر
تعريفنوع بنية RenderModel_t
{
	بنية Render_Model_رأس_t * r_رأس_داده; // const struct vr::RenderModel_Vertex_t *
	uint32_t un_رأس_شمار;
	uint16_t * r_شاخص_داده; // const uint16_t *
	uint32_t un_Triangle_شمار;
	TextureID_t diffuseTextureId;
} RenderModel_t;

#إذا defined(__linux__) || defined(__APPLE__)
#رهنمود pack( برداشت )
#پایان_اگر
تعريفنوع بنية Render_Model_Controller_نما_State_t
{
	bool bScrollWheelVisible;
} Render_Model_Controller_نما_State_t;

تعريفنوع بنية NotificationBitmap_t
{
	فراغ * m_p_Image_داده; // void *
	int32_t m_n_عرض;
	int32_t m_n_ارتفاع;
	int32_t m_n_بایتها_در_هر_Pixel;
} NotificationBitmap_t;

تعريفنوع بنية CVRSettingHelper
{
	intptr_t m_pSettings; // class vr::IVRSettings *
} CVRSettingHelper;

تعريفنوع بنية درون_داد_Analog_Action_داده_t
{
	bool b_فعال;
	VRInput_مقدار_Handle_t فعال_Origin;
	عائم x;
	عائم y;
	عائم z;
	عائم deltaX;
	عائم deltaY;
	عائم deltaZ;
	عائم f_Update_زمان;
} درون_داد_Analog_Action_داده_t;

تعريفنوع بنية درون_داد_Digital_Action_داده_t
{
	bool b_فعال;
	VRInput_مقدار_Handle_t فعال_Origin;
	bool bState;
	bool b_تغییریافته;
	عائم f_Update_زمان;
} درون_داد_Digital_Action_داده_t;

تعريفنوع بنية درون_داد_Pose_Action_داده_t
{
	bool b_فعال;
	VRInput_مقدار_Handle_t فعال_Origin;
	بنية TrackedDevicePose_t pose;
} درون_داد_Pose_Action_داده_t;

تعريفنوع بنية درون_داد_Skeletal_Action_داده_t
{
	bool b_فعال;
	VRInput_مقدار_Handle_t فعال_Origin;
} درون_داد_Skeletal_Action_داده_t;

تعريفنوع بنية درون_داد_Origin_Info_t
{
	VRInput_مقدار_Handle_t device_مسیر;
	Tracked_Device_شاخص_t tracked_Device_شاخص;
	حرف rchRenderModelComponentName[128]; //char[128]
} درون_داد_Origin_Info_t;

تعريفنوع بنية درون_داد_Binding_Info_t
{
	حرف rch_Device_مسیر_Name[128]; //char[128]
	حرف rch_درون_داد_مسیر_Name[128]; //char[128]
	حرف rch_نما_Name[128]; //char[128]
	حرف rch_جایگاه_Name[128]; //char[128]
	حرف rch_درون_داد_منبع_Type[32]; //char[32]
} درون_داد_Binding_Info_t;

تعريفنوع بنية VRActive_Action_مجموعه_t
{
	VRAction_مجموعه_Handle_t ul_Action_مجموعه;
	VRInput_مقدار_Handle_t ul_Restricted_مقصد_Device;
	VRAction_مجموعه_Handle_t ul_Secondary_Action_مجموعه;
	uint32_t unPadding;
	int32_t n_اولویت;
} VRActive_Action_مجموعه_t;

تعريفنوع بنية VRSkeletal_Summary_داده_t
{
	عائم flFingerCurl[5]; //float[5]
	عائم flFingerSplay[4]; //float[4]
} VRSkeletal_Summary_داده_t;

تعريفنوع بنية SpatialAnchorPose_t
{
	بنية HmdMatrix34_t m_Anchor_مقصد_Absolute_Tracking;
} SpatialAnchorPose_t;

تعريفنوع بنية COpenVRContext
{
	intptr_t m_pVRSystem; // class vr::IVRSystem *
	intptr_t m_pVRChaperone; // class vr::IVRChaperone *
	intptr_t m_p_VRChaperone_راهاندازی; // class vr::IVRChaperoneSetup *
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
	تعداد ETrackedPropertyError e_مجموعه_Error;
	فراغ * pv_میانگیر; // void *
	uint32_t un_میانگیر_اندازه;
	Property_Type_برچسب_t un_برچسب;
	تعداد ETrackedPropertyError eError;
} PropertyWrite_t;

تعريفنوع بنية PropertyRead_t
{
	تعداد ETrackedDeviceProperty prop;
	فراغ * pv_میانگیر; // void *
	uint32_t un_میانگیر_اندازه;
	Property_Type_برچسب_t un_برچسب;
	uint32_t un_Required_میانگیر_اندازه;
	تعداد ETrackedPropertyError eError;
} PropertyRead_t;

تعريفنوع بنية CVRPropertyHelpers
{
	intptr_t m_pProperties; // class vr::IVRProperties *
} CVRPropertyHelpers;

تعريفنوع بنية مسیر_Write_t
{
	مسیر_Handle_t ul_مسیر;
	تعداد EPropertyWriteType writeType;
	تعداد ETrackedPropertyError e_مجموعه_Error;
	فراغ * pv_میانگیر; // void *
	uint32_t un_میانگیر_اندازه;
	Property_Type_برچسب_t un_برچسب;
	تعداد ETrackedPropertyError eError;
	حرف * psz_مسیر; // const char *
} مسیر_Write_t;

تعريفنوع بنية مسیر_Read_t
{
	مسیر_Handle_t ul_مسیر;
	فراغ * pv_میانگیر; // void *
	uint32_t un_میانگیر_اندازه;
	Property_Type_برچسب_t un_برچسب;
	uint32_t un_Required_میانگیر_اندازه;
	تعداد ETrackedPropertyError eError;
	حرف * psz_مسیر; // const char *
} مسیر_Read_t;


تعريفنوع اتحاد
{
	VREvent_Reserved_t reserved;
	VREvent_Controller_t controller;
	VREvent_Mouse_t mouse;
	VREvent_Scroll_t scroll;
	VREvent_Process_t process;
	VREvent_Notification_t notification;
	VREvent_Overlay_t overlay;
	VREvent_وضعیت_t وضعیت;
	VREvent_Keyboard_t keyboard;
	VREvent_Ipd_t ipd;
	VREvent_Chaperone_t chaperone;
	VREvent_PerformanceTest_t performanceTest;
	VREvent_TouchPadMove_t touchPadMove;
	VREvent_SeatedZeroPoseReset_t seatedZeroPoseReset;
	VREvent_Screenshot_t screenshot;
	VREvent_Screenshot_پیشرفت_t screenshot_پیشرفت;
	VREvent_ApplicationLaunch_t applicationLaunch;
	VREvent_EditingCameraSurface_t cameraSurface;
	VREvent_پیام_Overlay_t پیام_Overlay;
	VREvent_Property_t property;
	VREvent_HapticVibration_t hapticVibration;
	VREvent_WebConsole_t webConsole;
	VREvent_درون_داد_Binding_بارگیری_t درون_داد_Binding;
	VREvent_درون_داد_Action_Manifest_بارگیری_t actionManifest;
	VREvent_SpatialAnchor_t spatialAnchor;
} VREvent_داده_t;

#إذا defined(__linux__) || defined(__APPLE__) 
// This structure was originally defined mis-packed on Linux, preserved for 
// compatibility. 
#رهنمود pack( افزودن, 4 )
#پایان_اگر

/** An event posted by the server to all running applications */
بنية VREvent_t
{
	uint32_t eventType; // EVREventType enum
	Tracked_Device_شاخص_t tracked_Device_شاخص;
	عائم eventAgeSeconds;
	// event data must be the end of the struct as its size is variable
	VREvent_داده_t داده;
};

#إذا defined(__linux__) || defined(__APPLE__) 
#رهنمود pack( برداشت )
#پایان_اگر


تعريفنوع اتحاد
{
	Intersection_ماسک_Rectangle_t m_Rectangle;
	Intersection_ماسک_Circle_t m_Circle;
} VROverlay_Intersection_ماسک_Primitive_داده_t;

بنية VROverlay_Intersection_ماسک_Primitive_t
{
	EVROverlay_Intersection_ماسک_Primitive_Type m_nPrimitiveType;
	VROverlay_Intersection_ماسک_Primitive_داده_t m_Primitive;
};


// OpenVR Function Pointer Tables

بنية VR_IVRSystem_Fn_جدول
{
	فراغ (OPENVR_FNTABLE_CALLTYPE *Get_Recommended_Render_هدف_اندازه)(uint32_t * pn_عرض, uint32_t * pn_ارتفاع);
	بنية HmdMatrix44_t (OPENVR_FNTABLE_CALLTYPE *Get_Projection_ماتریس)(EVREye eEye, عائم fNearZ, عائم fFarZ);
	فراغ (OPENVR_FNTABLE_CALLTYPE *GetProjectionRaw)(EVREye eEye, عائم * pf_چپ, عائم * pf_راست, عائم * pf_بالاترین, عائم * pfBottom);
	bool (OPENVR_FNTABLE_CALLTYPE *ComputeDistortion)(EVREye eEye, عائم fU, عائم fV, بنية DistortionCoordinates_t * pDistortionCoordinates);
	بنية HmdMatrix34_t (OPENVR_FNTABLE_CALLTYPE *Get_Eye_مقصد_سر_Transform)(EVREye eEye);
	bool (OPENVR_FNTABLE_CALLTYPE *Get_زمان_Since_آخرین_Vsync)(عائم * pf_Seconds_Since_آخرین_Vsync, uint64_t * pul_قاب_Counter);
	int32_t (OPENVR_FNTABLE_CALLTYPE *Get_D3_D9_Adapter_شاخص)();
	فراغ (OPENVR_FNTABLE_CALLTYPE *GetDXGIOutputInfo)(int32_t * pn_Adapter_شاخص);
	فراغ (OPENVR_FNTABLE_CALLTYPE *GetOutputDevice)(uint64_t * pnDevice, ETextureType textureType, بنية VkInstance_T * pInstance);
	bool (OPENVR_FNTABLE_CALLTYPE *IsDisplayOnDesktop)();
	bool (OPENVR_FNTABLE_CALLTYPE *مجموعه_Display_Visibility)(bool bIsVisibleOnDesktop);
	فراغ (OPENVR_FNTABLE_CALLTYPE *Get_Device_مقصد_Absolute_Tracking_Pose)(ETrackingUniverseOrigin eOrigin, عائم f_Predicted_Seconds_مقصد_Photons_From_Now, بنية TrackedDevicePose_t * pTrackedDevicePoseArray, uint32_t un_Tracked_Device_Pose_Array_شمار);
	بنية HmdMatrix34_t (OPENVR_FNTABLE_CALLTYPE *Get_Seated_Zero_Pose_مقصد_Standing_Absolute_Tracking_Pose)();
	بنية HmdMatrix34_t (OPENVR_FNTABLE_CALLTYPE *Get_Raw_Zero_Pose_مقصد_Standing_Absolute_Tracking_Pose)();
	uint32_t (OPENVR_FNTABLE_CALLTYPE *Get_Sorted_Tracked_Device_Indices_از_Class)(ETrackedDeviceClass eTrackedDeviceClass, Tracked_Device_شاخص_t * pun_Tracked_Device_شاخص_Array, uint32_t un_Tracked_Device_شاخص_Array_شمار, Tracked_Device_شاخص_t un_Relative_مقصد_Tracked_Device_شاخص);
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
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetArrayTrackedDeviceProperty)(Tracked_Device_شاخص_t un_Device_شاخص, ETrackedDeviceProperty prop, Property_Type_برچسب_t propType, فراغ * p_میانگیر, uint32_t un_میانگیر_اندازه, ETrackedPropertyError * pError);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetStringTrackedDeviceProperty)(Tracked_Device_شاخص_t un_Device_شاخص, ETrackedDeviceProperty prop, حرف * pch_مقدار, uint32_t un_میانگیر_اندازه, ETrackedPropertyError * pError);
	حرف * (OPENVR_FNTABLE_CALLTYPE *GetPropErrorNameFromEnum)(ETrackedPropertyError error);
	bool (OPENVR_FNTABLE_CALLTYPE *Poll_بعدی_Event)(بنية VREvent_t * pEvent, uint32_t uncbVREvent);
	bool (OPENVR_FNTABLE_CALLTYPE *Poll_بعدی_Event_With_Pose)(ETrackingUniverseOrigin eOrigin, بنية VREvent_t * pEvent, uint32_t uncbVREvent, TrackedDevicePose_t * pTrackedDevicePose);
	حرف * (OPENVR_FNTABLE_CALLTYPE *GetEventTypeNameFromEnum)(EVREventType eType);
	بنية HiddenAreaMesh_t (OPENVR_FNTABLE_CALLTYPE *GetHiddenAreaMesh)(EVREye eEye, EHiddenAreaMeshType type);
	bool (OPENVR_FNTABLE_CALLTYPE *GetControllerState)(Tracked_Device_شاخص_t un_Controller_Device_شاخص, VRControllerState_t * pControllerState, uint32_t un_Controller_State_اندازه);
	bool (OPENVR_FNTABLE_CALLTYPE *GetControllerStateWithPose)(ETrackingUniverseOrigin eOrigin, Tracked_Device_شاخص_t un_Controller_Device_شاخص, VRControllerState_t * pControllerState, uint32_t un_Controller_State_اندازه, بنية TrackedDevicePose_t * pTrackedDevicePose);
	فراغ (OPENVR_FNTABLE_CALLTYPE *TriggerHapticPulse)(Tracked_Device_شاخص_t un_Controller_Device_شاخص, uint32_t unAxisId, بیعلامت کوتاه usDurationMicroSec);
	حرف * (OPENVR_FNTABLE_CALLTYPE *GetButtonIdNameFromEnum)(EVRButtonId eButtonId);
	حرف * (OPENVR_FNTABLE_CALLTYPE *GetControllerAxisTypeNameFromEnum)(EVRControllerAxisType eAxisType);
	bool (OPENVR_FNTABLE_CALLTYPE *Is_درون_داد_موجود)();
	bool (OPENVR_FNTABLE_CALLTYPE *IsSteamVRDrawingControllers)();
	bool (OPENVR_FNTABLE_CALLTYPE *ShouldApplicationPause)();
	bool (OPENVR_FNTABLE_CALLTYPE *ShouldApplicationReduceRenderingWork)();
	EVRFirmwareError (OPENVR_FNTABLE_CALLTYPE *PerformFirmwareUpdate)(Tracked_Device_شاخص_t un_Device_شاخص);
	فراغ (OPENVR_FNTABLE_CALLTYPE *AcknowledgeQuit_Exiting)();
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetAppContainerFilePaths)(حرف * pch_میانگیر, uint32_t un_میانگیر_اندازه);
	حرف * (OPENVR_FNTABLE_CALLTYPE *Get_Runtime_نسخه)();
};

بنية VR_IVRExtended_Display_Fn_جدول
{
	فراغ (OPENVR_FNTABLE_CALLTYPE *Get_پنجره_Bounds)(int32_t * pnX, int32_t * pnY, uint32_t * pn_عرض, uint32_t * pn_ارتفاع);
	فراغ (OPENVR_FNTABLE_CALLTYPE *GetEyeOutputViewport)(EVREye eEye, uint32_t * pnX, uint32_t * pnY, uint32_t * pn_عرض, uint32_t * pn_ارتفاع);
	فراغ (OPENVR_FNTABLE_CALLTYPE *GetDXGIOutputInfo)(int32_t * pn_Adapter_شاخص, int32_t * pn_Adapter_Output_شاخص);
};

بنية VR_IVRTracked_Camera_Fn_جدول
{
	حرف * (OPENVR_FNTABLE_CALLTYPE *GetCameraErrorNameFromEnum)(EVRTrackedCameraError eCameraError);
	EVRTrackedCameraError (OPENVR_FNTABLE_CALLTYPE *HasCamera)(Tracked_Device_شاخص_t n_Device_شاخص, bool * pHasCamera);
	EVRTrackedCameraError (OPENVR_FNTABLE_CALLTYPE *Get_Camera_قاب_اندازه)(Tracked_Device_شاخص_t n_Device_شاخص, EVRTracked_Camera_قاب_Type e_قاب_Type, uint32_t * pn_عرض, uint32_t * pn_ارتفاع, uint32_t * pn_قاب_میانگیر_اندازه);
	EVRTrackedCameraError (OPENVR_FNTABLE_CALLTYPE *GetCameraIntrinsics)(Tracked_Device_شاخص_t n_Device_شاخص, uint32_t n_Camera_شاخص, EVRTracked_Camera_قاب_Type e_قاب_Type, HmdVector2_t * p_Focal_درازی, HmdVector2_t * pCenter);
	EVRTrackedCameraError (OPENVR_FNTABLE_CALLTYPE *GetCameraProjection)(Tracked_Device_شاخص_t n_Device_شاخص, uint32_t n_Camera_شاخص, EVRTracked_Camera_قاب_Type e_قاب_Type, عائم flZNear, عائم flZFar, HmdMatrix44_t * pProjection);
	EVRTrackedCameraError (OPENVR_FNTABLE_CALLTYPE *AcquireVideoStreamingService)(Tracked_Device_شاخص_t n_Device_شاخص, TrackedCameraHandle_t * pHandle);
	EVRTrackedCameraError (OPENVR_FNTABLE_CALLTYPE *ReleaseVideoStreamingService)(TrackedCameraHandle_t hTrackedCamera);
	EVRTrackedCameraError (OPENVR_FNTABLE_CALLTYPE *Get_Video_جریان_قاب_میانگیر)(TrackedCameraHandle_t hTrackedCamera, EVRTracked_Camera_قاب_Type e_قاب_Type, فراغ * p_قاب_میانگیر, uint32_t n_قاب_میانگیر_اندازه, Camera_Video_جریان_قاب_سرآیند_t * p_قاب_سرآیند, uint32_t n_قاب_سرآیند_اندازه);
	EVRTrackedCameraError (OPENVR_FNTABLE_CALLTYPE *Get_Video_جریان_Texture_اندازه)(Tracked_Device_شاخص_t n_Device_شاخص, EVRTracked_Camera_قاب_Type e_قاب_Type, VRTextureBounds_t * pTextureBounds, uint32_t * pn_عرض, uint32_t * pn_ارتفاع);
	EVRTrackedCameraError (OPENVR_FNTABLE_CALLTYPE *Get_Video_جریان_Texture_D3_D11)(TrackedCameraHandle_t hTrackedCamera, EVRTracked_Camera_قاب_Type e_قاب_Type, فراغ * pD3D11DeviceOrResource, فراغ ** ppD3D11ShaderResourceView, Camera_Video_جریان_قاب_سرآیند_t * p_قاب_سرآیند, uint32_t n_قاب_سرآیند_اندازه);
	EVRTrackedCameraError (OPENVR_FNTABLE_CALLTYPE *Get_Video_جریان_Texture_GL)(TrackedCameraHandle_t hTrackedCamera, EVRTracked_Camera_قاب_Type e_قاب_Type, glUInt_t * pglTextureId, Camera_Video_جریان_قاب_سرآیند_t * p_قاب_سرآیند, uint32_t n_قاب_سرآیند_اندازه);
	EVRTrackedCameraError (OPENVR_FNTABLE_CALLTYPE *Release_Video_جریان_Texture_GL)(TrackedCameraHandle_t hTrackedCamera, glUInt_t glTextureId);
	فراغ (OPENVR_FNTABLE_CALLTYPE *مجموعه_Camera_Tracking_Space)(ETrackingUniverseOrigin eUniverse);
	ETrackingUniverseOrigin (OPENVR_FNTABLE_CALLTYPE *GetCameraTrackingSpace)();
};

بنية VR_IVRApplications_Fn_جدول
{
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *جمع_کن_Application_Manifest)(حرف * pch_Application_Manifest_پر_مسیر, bool bTemporary);
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *RemoveApplicationManifest)(حرف * pch_Application_Manifest_پر_مسیر);
	bool (OPENVR_FNTABLE_CALLTYPE *IsApplicationInstalled)(حرف * pch_App_کلید);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *Get_Application_شمار)();
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *Get_Application_کلید_By_شاخص)(uint32_t un_Application_شاخص, حرف * pch_App_کلید_میانگیر, uint32_t un_App_کلید_میانگیر_Len);
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *Get_Application_کلید_By_Process_Id)(uint32_t unProcessId, حرف * pch_App_کلید_میانگیر, uint32_t un_App_کلید_میانگیر_Len);
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *LaunchApplication)(حرف * pch_App_کلید);
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *LaunchTemplateApplication)(حرف * pch_Template_App_کلید, حرف * pch_New_App_کلید, بنية App_Override_کلیدها_t * p_کلیدها, uint32_t un_کلیدها);
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *LaunchApplicationFromMimeType)(حرف * pchMimeType, حرف * pch_آرگومانها);
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *LaunchDashboardOverlay)(حرف * pch_App_کلید);
	bool (OPENVR_FNTABLE_CALLTYPE *CancelApplicationLaunch)(حرف * pch_App_کلید);
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *IdentifyApplication)(uint32_t unProcessId, حرف * pch_App_کلید);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetApplicationProcessId)(حرف * pch_App_کلید);
	حرف * (OPENVR_FNTABLE_CALLTYPE *GetApplicationsErrorNameFromEnum)(EVRApplicationError error);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetApplicationPropertyString)(حرف * pch_App_کلید, EVRApplicationProperty eProperty, حرف * pch_Property_مقدار_میانگیر, uint32_t un_Property_مقدار_میانگیر_Len, EVRApplicationError * peError);
	bool (OPENVR_FNTABLE_CALLTYPE *GetApplicationPropertyBool)(حرف * pch_App_کلید, EVRApplicationProperty eProperty, EVRApplicationError * peError);
	uint64_t (OPENVR_FNTABLE_CALLTYPE *GetApplicationPropertyUint64)(حرف * pch_App_کلید, EVRApplicationProperty eProperty, EVRApplicationError * peError);
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *مجموعه_Application_Auto_Launch)(حرف * pch_App_کلید, bool bAutoLaunch);
	bool (OPENVR_FNTABLE_CALLTYPE *GetApplicationAutoLaunch)(حرف * pch_App_کلید);
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *مجموعه_Default_Application_For_Mime_Type)(حرف * pch_App_کلید, حرف * pchMimeType);
	bool (OPENVR_FNTABLE_CALLTYPE *GetDefaultApplicationForMimeType)(حرف * pchMimeType, حرف * pch_App_کلید_میانگیر, uint32_t un_App_کلید_میانگیر_Len);
	bool (OPENVR_FNTABLE_CALLTYPE *GetApplicationSupportedMimeTypes)(حرف * pch_App_کلید, حرف * pch_Mime_Types_میانگیر, uint32_t un_Mime_Types_میانگیر);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetApplicationsThatSupportMimeType)(حرف * pchMimeType, حرف * pch_App_کلیدها_That_Support_میانگیر, uint32_t un_App_کلیدها_That_Support_میانگیر);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetApplicationLaunchArguments)(uint32_t unHandle, حرف * pch_آرگومانها, uint32_t un_آرگومانها);
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *GetStartingApplication)(حرف * pch_App_کلید_میانگیر, uint32_t un_App_کلید_میانگیر_Len);
	EVRSceneApplicationState (OPENVR_FNTABLE_CALLTYPE *GetSceneApplicationState)();
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *PerformApplicationPrelaunchCheck)(حرف * pch_App_کلید);
	حرف * (OPENVR_FNTABLE_CALLTYPE *GetSceneApplicationStateNameFromEnum)(EVRSceneApplicationState state);
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *Launch_داخلی_Process)(حرف * pch_دودویی_مسیر, حرف * pchArguments, حرف * pchWorkingDirectory);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetCurrentSceneProcessId)();
};

بنية VR_IVRChaperone_Fn_جدول
{
	ChaperoneCalibrationState (OPENVR_FNTABLE_CALLTYPE *GetCalibrationState)();
	bool (OPENVR_FNTABLE_CALLTYPE *Get_Play_Area_اندازه)(عائم * p_اندازه_X, عائم * p_اندازه_Z);
	bool (OPENVR_FNTABLE_CALLTYPE *GetPlayAreaRect)(بنية HmdQuad_t * rect);
	فراغ (OPENVR_FNTABLE_CALLTYPE *ReloadInfo)();
	فراغ (OPENVR_FNTABLE_CALLTYPE *مجموعه_Scene_Color)(بنية HmdColor_t color);
	فراغ (OPENVR_FNTABLE_CALLTYPE *GetBoundsColor)(بنية HmdColor_t * pOutputColorArray, صحيح n_رقم_Output_Colors, عائم fl_Collision_Bounds_Fade_فاصله, بنية HmdColor_t * pOutputCameraColor);
	bool (OPENVR_FNTABLE_CALLTYPE *AreBoundsVisible)();
	فراغ (OPENVR_FNTABLE_CALLTYPE *ForceBoundsVisible)(bool bForce);
	فراغ (OPENVR_FNTABLE_CALLTYPE *ResetZeroPose)(ETrackingUniverseOrigin eTrackingUniverseOrigin);
};

بنية VR_IVRChaperone_راهاندازی_Fn_جدول
{
	bool (OPENVR_FNTABLE_CALLTYPE *CommitWorkingCopy)(EChaperoneConfigFile configFile);
	فراغ (OPENVR_FNTABLE_CALLTYPE *RevertWorkingCopy)();
	bool (OPENVR_FNTABLE_CALLTYPE *Get_Working_Play_Area_اندازه)(عائم * p_اندازه_X, عائم * p_اندازه_Z);
	bool (OPENVR_FNTABLE_CALLTYPE *GetWorkingPlayAreaRect)(بنية HmdQuad_t * rect);
	bool (OPENVR_FNTABLE_CALLTYPE *GetWorkingCollisionBoundsInfo)(بنية HmdQuad_t * p_Quads_میانگیر, uint32_t * pun_Quads_شمار);
	bool (OPENVR_FNTABLE_CALLTYPE *Get_زنده_Collision_Bounds_Info)(بنية HmdQuad_t * p_Quads_میانگیر, uint32_t * pun_Quads_شمار);
	bool (OPENVR_FNTABLE_CALLTYPE *Get_Working_Seated_Zero_Pose_مقصد_Raw_Tracking_Pose)(بنية HmdMatrix34_t * pmat_Seated_Zero_Pose_مقصد_Raw_Tracking_Pose);
	bool (OPENVR_FNTABLE_CALLTYPE *Get_Working_Standing_Zero_Pose_مقصد_Raw_Tracking_Pose)(بنية HmdMatrix34_t * pmat_Standing_Zero_Pose_مقصد_Raw_Tracking_Pose);
	فراغ (OPENVR_FNTABLE_CALLTYPE *مجموعه_Working_Play_Area_اندازه)(عائم اندازه_X, عائم اندازه_Z);
	فراغ (OPENVR_FNTABLE_CALLTYPE *مجموعه_Working_Collision_Bounds_Info)(بنية HmdQuad_t * p_Quads_میانگیر, uint32_t un_Quads_شمار);
	فراغ (OPENVR_FNTABLE_CALLTYPE *مجموعه_Working_Perimeter)(بنية HmdVector2_t * p_نقطه_میانگیر, uint32_t un_نقطه_شمار);
	فراغ (OPENVR_FNTABLE_CALLTYPE *مجموعه_Working_Seated_Zero_Pose_مقصد_Raw_Tracking_Pose)(بنية HmdMatrix34_t * p_Mat_Seated_Zero_Pose_مقصد_Raw_Tracking_Pose);
	فراغ (OPENVR_FNTABLE_CALLTYPE *مجموعه_Working_Standing_Zero_Pose_مقصد_Raw_Tracking_Pose)(بنية HmdMatrix34_t * p_Mat_Standing_Zero_Pose_مقصد_Raw_Tracking_Pose);
	فراغ (OPENVR_FNTABLE_CALLTYPE *ReloadFromDisk)(EChaperoneConfigFile configFile);
	bool (OPENVR_FNTABLE_CALLTYPE *Get_زنده_Seated_Zero_Pose_مقصد_Raw_Tracking_Pose)(بنية HmdMatrix34_t * pmat_Seated_Zero_Pose_مقصد_Raw_Tracking_Pose);
	bool (OPENVR_FNTABLE_CALLTYPE *Export_زنده_مقصد_میانگیر)(حرف * p_میانگیر, uint32_t * pn_میانگیر_درازی);
	bool (OPENVR_FNTABLE_CALLTYPE *Import_From_میانگیر_مقصد_Working)(حرف * p_میانگیر, uint32_t nImportFlags);
	فراغ (OPENVR_FNTABLE_CALLTYPE *Show_Working_مجموعه_Preview)();
	فراغ (OPENVR_FNTABLE_CALLTYPE *Hide_Working_مجموعه_Preview)();
	فراغ (OPENVR_FNTABLE_CALLTYPE *جا_راهاندازی_Starting)();
};

بنية VR_IVRCompositor_Fn_جدول
{
	فراغ (OPENVR_FNTABLE_CALLTYPE *مجموعه_Tracking_Space)(ETrackingUniverseOrigin eOrigin);
	ETrackingUniverseOrigin (OPENVR_FNTABLE_CALLTYPE *GetTrackingSpace)();
	EVRCompositorError (OPENVR_FNTABLE_CALLTYPE *WaitGetPoses)(بنية TrackedDevicePose_t * pRenderPoseArray, uint32_t un_Render_Pose_Array_شمار, بنية TrackedDevicePose_t * pGamePoseArray, uint32_t un_Game_Pose_Array_شمار);
	EVRCompositorError (OPENVR_FNTABLE_CALLTYPE *Get_آخرین_Poses)(بنية TrackedDevicePose_t * pRenderPoseArray, uint32_t un_Render_Pose_Array_شمار, بنية TrackedDevicePose_t * pGamePoseArray, uint32_t un_Game_Pose_Array_شمار);
	EVRCompositorError (OPENVR_FNTABLE_CALLTYPE *Get_آخرین_Pose_For_Tracked_Device_شاخص)(Tracked_Device_شاخص_t un_Device_شاخص, بنية TrackedDevicePose_t * pOutputPose, بنية TrackedDevicePose_t * pOutputGamePose);
	EVRCompositorError (OPENVR_FNTABLE_CALLTYPE *Submit)(EVREye eEye, بنية Texture_t * pTexture, بنية VRTextureBounds_t * pBounds, EVRSubmitFlags nSubmitFlags);
	فراغ (OPENVR_FNTABLE_CALLTYPE *Clear_آخرین_Submitted_قاب)();
	فراغ (OPENVR_FNTABLE_CALLTYPE *PostPresentHandoff)();
	bool (OPENVR_FNTABLE_CALLTYPE *Get_قاب_Timing)(بنية Compositor_قاب_Timing * pTiming, uint32_t un_قابها_Ago);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *Get_قاب_Timings)(بنية Compositor_قاب_Timing * pTiming, uint32_t n_قابها);
	عائم (OPENVR_FNTABLE_CALLTYPE *Get_قاب_زمان_مانده)();
	فراغ (OPENVR_FNTABLE_CALLTYPE *GetCumulativeStats)(بنية Compositor_CumulativeStats * pStats, uint32_t n_Stats_اندازه_درون_بایتها);
	فراغ (OPENVR_FNTABLE_CALLTYPE *Fade_مقصد_Color)(عائم fSeconds, عائم fRed, عائم fGreen, عائم fBlue, عائم fAlpha, bool bBackground);
	بنية HmdColor_t (OPENVR_FNTABLE_CALLTYPE *GetCurrentFadeColor)(bool bBackground);
	فراغ (OPENVR_FNTABLE_CALLTYPE *FadeGrid)(عائم fSeconds, bool b_Fade_Grid_درون);
	عائم (OPENVR_FNTABLE_CALLTYPE *GetCurrentGridAlpha)();
	EVRCompositorError (OPENVR_FNTABLE_CALLTYPE *مجموعه_Skybox_Override)(بنية Texture_t * pTextures, uint32_t un_Texture_شمار);
	فراغ (OPENVR_FNTABLE_CALLTYPE *ClearSkyboxOverride)();
	فراغ (OPENVR_FNTABLE_CALLTYPE *Compositor_Bring_مقصد_Front)();
	فراغ (OPENVR_FNTABLE_CALLTYPE *Compositor_Go_مقصد_پشت)();
	فراغ (OPENVR_FNTABLE_CALLTYPE *CompositorQuit)();
	bool (OPENVR_FNTABLE_CALLTYPE *IsFullscreen)();
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetCurrentSceneFocusProcess)();
	uint32_t (OPENVR_FNTABLE_CALLTYPE *Get_آخرین_قاب_Renderer)();
	bool (OPENVR_FNTABLE_CALLTYPE *CanRenderScene)();
	فراغ (OPENVR_FNTABLE_CALLTYPE *Show_Mirror_پنجره)();
	فراغ (OPENVR_FNTABLE_CALLTYPE *Hide_Mirror_پنجره)();
	bool (OPENVR_FNTABLE_CALLTYPE *Is_Mirror_پنجره_Visible)();
	فراغ (OPENVR_FNTABLE_CALLTYPE *CompositorDumpImages)();
	bool (OPENVR_FNTABLE_CALLTYPE *Should_App_Render_With_کم_Resources)();
	فراغ (OPENVR_FNTABLE_CALLTYPE *ForceInterleavedReprojectionOn)(bool bOverride);
	فراغ (OPENVR_FNTABLE_CALLTYPE *ForceReconnectProcess)();
	فراغ (OPENVR_FNTABLE_CALLTYPE *SuspendRendering)(bool bSuspend);
	EVRCompositorError (OPENVR_FNTABLE_CALLTYPE *GetMirrorTextureD3D11)(EVREye eEye, فراغ * pD3D11DeviceOrResource, فراغ ** ppD3D11ShaderResourceView);
	فراغ (OPENVR_FNTABLE_CALLTYPE *ReleaseMirrorTextureD3D11)(فراغ * pD3D11ShaderResourceView);
	EVRCompositorError (OPENVR_FNTABLE_CALLTYPE *GetMirrorTextureGL)(EVREye eEye, glUInt_t * pglTextureId, glSharedTextureHandle_t * pglSharedTextureHandle);
	bool (OPENVR_FNTABLE_CALLTYPE *ReleaseSharedGLTexture)(glUInt_t glTextureId, glSharedTextureHandle_t glSharedTextureHandle);
	فراغ (OPENVR_FNTABLE_CALLTYPE *قفل_GLShared_Texture_For_Access)(glSharedTextureHandle_t glSharedTextureHandle);
	فراغ (OPENVR_FNTABLE_CALLTYPE *UnlockGLSharedTextureForAccess)(glSharedTextureHandle_t glSharedTextureHandle);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetVulkanInstanceExtensionsRequired)(حرف * pch_مقدار, uint32_t un_میانگیر_اندازه);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetVulkanDeviceExtensionsRequired)(بنية VkPhysicalDevice_T * pPhysicalDevice, حرف * pch_مقدار, uint32_t un_میانگیر_اندازه);
	فراغ (OPENVR_FNTABLE_CALLTYPE *مجموعه_Explicit_Timing_نما)(EVRCompositor_Timing_نما e_Timing_نما);
	EVRCompositorError (OPENVR_FNTABLE_CALLTYPE *Submit_Explicit_Timing_داده)();
	bool (OPENVR_FNTABLE_CALLTYPE *IsMotionSmoothingEnabled)();
	bool (OPENVR_FNTABLE_CALLTYPE *IsMotionSmoothingSupported)();
	bool (OPENVR_FNTABLE_CALLTYPE *IsCurrentSceneFocusAppLoading)();
	EVRCompositorError (OPENVR_FNTABLE_CALLTYPE *مجموعه_Stage_Override_Async)(حرف * pch_Render_Model_مسیر, بنية HmdMatrix34_t * pTransform, بنية Compositor_StageRenderSettings * pRenderSettings, uint32_t n_اندازه_از_Render_Settings);
	فراغ (OPENVR_FNTABLE_CALLTYPE *ClearStageOverride)();
	bool (OPENVR_FNTABLE_CALLTYPE *GetCompositorBenchmarkResults)(بنية Compositor_BenchmarkResults * pBenchmarkResults, uint32_t n_اندازه_از_Benchmark_Results);
	EVRCompositorError (OPENVR_FNTABLE_CALLTYPE *Get_آخرین_Pose_Prediction_IDs)(uint32_t * pRenderPosePredictionID, uint32_t * pGamePosePredictionID);
	EVRCompositorError (OPENVR_FNTABLE_CALLTYPE *Get_Poses_For_قاب)(uint32_t unPosePredictionID, بنية TrackedDevicePose_t * pPoseArray, uint32_t un_Pose_Array_شمار);
};

بنية VR_IVROverlay_Fn_جدول
{
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *پیدا_کن_Overlay)(حرف * pch_Overlay_کلید, VROverlayHandle_t * pOverlayHandle);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *CreateOverlay)(حرف * pch_Overlay_کلید, حرف * pchOverlayName, VROverlayHandle_t * pOverlayHandle);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *DestroyOverlay)(VROverlayHandle_t ulOverlayHandle);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *Get_Overlay_کلید)(VROverlayHandle_t ulOverlayHandle, حرف * pch_مقدار, uint32_t un_میانگیر_اندازه, EVROverlayError * pError);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetOverlayName)(VROverlayHandle_t ulOverlayHandle, حرف * pch_مقدار, uint32_t un_میانگیر_اندازه, EVROverlayError * pError);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *مجموعه_Overlay_Name)(VROverlayHandle_t ulOverlayHandle, حرف * pchName);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *Get_Overlay_Image_داده)(VROverlayHandle_t ulOverlayHandle, فراغ * pv_میانگیر, uint32_t un_میانگیر_اندازه, uint32_t * pun_عرض, uint32_t * pun_ارتفاع);
	حرف * (OPENVR_FNTABLE_CALLTYPE *GetOverlayErrorNameFromEnum)(EVROverlayError error);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *مجموعه_Overlay_Rendering_Pid)(VROverlayHandle_t ulOverlayHandle, uint32_t unPID);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetOverlayRenderingPid)(VROverlayHandle_t ulOverlayHandle);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *مجموعه_Overlay_Flag)(VROverlayHandle_t ulOverlayHandle, VROverlayFlags eOverlayFlag, bool bEnabled);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayFlag)(VROverlayHandle_t ulOverlayHandle, VROverlayFlags eOverlayFlag, bool * pbEnabled);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayFlags)(VROverlayHandle_t ulOverlayHandle, uint32_t * pFlags);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *مجموعه_Overlay_Color)(VROverlayHandle_t ulOverlayHandle, عائم fRed, عائم fGreen, عائم fBlue);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayColor)(VROverlayHandle_t ulOverlayHandle, عائم * pfRed, عائم * pfGreen, عائم * pfBlue);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *مجموعه_Overlay_Alpha)(VROverlayHandle_t ulOverlayHandle, عائم fAlpha);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayAlpha)(VROverlayHandle_t ulOverlayHandle, عائم * pfAlpha);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *مجموعه_Overlay_Texel_Aspect)(VROverlayHandle_t ulOverlayHandle, عائم fTexelAspect);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayTexelAspect)(VROverlayHandle_t ulOverlayHandle, عائم * pfTexelAspect);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *مجموعه_Overlay_مرتب_سازی_ترتیب)(VROverlayHandle_t ulOverlayHandle, uint32_t un_مرتب_سازی_ترتیب);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *Get_Overlay_مرتب_سازی_ترتیب)(VROverlayHandle_t ulOverlayHandle, uint32_t * pun_مرتب_سازی_ترتیب);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *مجموعه_Overlay_عرض_درون_Meters)(VROverlayHandle_t ulOverlayHandle, عائم f_عرض_درون_Meters);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *Get_Overlay_عرض_درون_Meters)(VROverlayHandle_t ulOverlayHandle, عائم * pf_عرض_درون_Meters);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *مجموعه_Overlay_Curvature)(VROverlayHandle_t ulOverlayHandle, عائم fCurvature);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayCurvature)(VROverlayHandle_t ulOverlayHandle, عائم * pfCurvature);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *مجموعه_Overlay_Pre_منحنی_Pitch)(VROverlayHandle_t ulOverlayHandle, عائم fRadians);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *Get_Overlay_Pre_منحنی_Pitch)(VROverlayHandle_t ulOverlayHandle, عائم * pfRadians);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *مجموعه_Overlay_Texture_Color_Space)(VROverlayHandle_t ulOverlayHandle, EColorSpace eTextureColorSpace);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayTextureColorSpace)(VROverlayHandle_t ulOverlayHandle, EColorSpace * peTextureColorSpace);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *مجموعه_Overlay_Texture_Bounds)(VROverlayHandle_t ulOverlayHandle, بنية VRTextureBounds_t * pOverlayTextureBounds);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayTextureBounds)(VROverlayHandle_t ulOverlayHandle, بنية VRTextureBounds_t * pOverlayTextureBounds);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayTransformType)(VROverlayHandle_t ulOverlayHandle, VROverlayTransformType * peTransformType);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *مجموعه_Overlay_Transform_Absolute)(VROverlayHandle_t ulOverlayHandle, ETrackingUniverseOrigin eTrackingOrigin, بنية HmdMatrix34_t * pmat_Tracking_Origin_مقصد_Overlay_Transform);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayTransformAbsolute)(VROverlayHandle_t ulOverlayHandle, ETrackingUniverseOrigin * peTrackingOrigin, بنية HmdMatrix34_t * pmat_Tracking_Origin_مقصد_Overlay_Transform);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *مجموعه_Overlay_Transform_Tracked_Device_Relative)(VROverlayHandle_t ulOverlayHandle, Tracked_Device_شاخص_t unTrackedDevice, بنية HmdMatrix34_t * pmat_Tracked_Device_مقصد_Overlay_Transform);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayTransformTrackedDeviceRelative)(VROverlayHandle_t ulOverlayHandle, Tracked_Device_شاخص_t * punTrackedDevice, بنية HmdMatrix34_t * pmat_Tracked_Device_مقصد_Overlay_Transform);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *مجموعه_Overlay_Transform_Tracked_Device_Component)(VROverlayHandle_t ulOverlayHandle, Tracked_Device_شاخص_t un_Device_شاخص, حرف * pchComponentName);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayTransformTrackedDeviceComponent)(VROverlayHandle_t ulOverlayHandle, Tracked_Device_شاخص_t * pun_Device_شاخص, حرف * pchComponentName, uint32_t un_Component_Name_اندازه);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayTransformOverlayRelative)(VROverlayHandle_t ulOverlayHandle, VROverlayHandle_t * ul_Overlay_Handle_والد, بنية HmdMatrix34_t * pmat_والد_Overlay_مقصد_Overlay_Transform);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *مجموعه_Overlay_Transform_Overlay_Relative)(VROverlayHandle_t ulOverlayHandle, VROverlayHandle_t ul_Overlay_Handle_والد, بنية HmdMatrix34_t * pmat_والد_Overlay_مقصد_Overlay_Transform);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *مجموعه_Overlay_Transform_Cursor)(VROverlayHandle_t ulCursorOverlayHandle, بنية HmdVector2_t * pvHotspot);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayTransformCursor)(VROverlayHandle_t ulOverlayHandle, بنية HmdVector2_t * pvHotspot);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *مجموعه_Overlay_Transform_Projection)(VROverlayHandle_t ulOverlayHandle, ETrackingUniverseOrigin eTrackingOrigin, بنية HmdMatrix34_t * pmat_Tracking_Origin_مقصد_Overlay_Transform, بنية VROverlayProjection_t * pProjection, EVREye eEye);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *ShowOverlay)(VROverlayHandle_t ulOverlayHandle);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *HideOverlay)(VROverlayHandle_t ulOverlayHandle);
	bool (OPENVR_FNTABLE_CALLTYPE *IsOverlayVisible)(VROverlayHandle_t ulOverlayHandle);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetTransformForOverlayCoordinates)(VROverlayHandle_t ulOverlayHandle, ETrackingUniverseOrigin eTrackingOrigin, بنية HmdVector2_t coordinates_درون_Overlay, بنية HmdMatrix34_t * pmatTransform);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *Wait_قاب_Sync)(uint32_t nTimeoutMs);
	bool (OPENVR_FNTABLE_CALLTYPE *Poll_بعدی_Overlay_Event)(VROverlayHandle_t ulOverlayHandle, بنية VREvent_t * pEvent, uint32_t uncbVREvent);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *Get_Overlay_درون_داد_روش)(VROverlayHandle_t ulOverlayHandle, VROverlay_درون_داد_روش * pe_درون_داد_روش);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *مجموعه_Overlay_درون_داد_روش)(VROverlayHandle_t ulOverlayHandle, VROverlay_درون_داد_روش e_درون_داد_روش);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayMouseScale)(VROverlayHandle_t ulOverlayHandle, بنية HmdVector2_t * pvecMouseScale);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *مجموعه_Overlay_Mouse_Scale)(VROverlayHandle_t ulOverlayHandle, بنية HmdVector2_t * pvecMouseScale);
	bool (OPENVR_FNTABLE_CALLTYPE *ComputeOverlayIntersection)(VROverlayHandle_t ulOverlayHandle, بنية VROverlayIntersectionParams_t * pParams, بنية VROverlayIntersectionResults_t * pResults);
	bool (OPENVR_FNTABLE_CALLTYPE *Is_Hover_هدف_Overlay)(VROverlayHandle_t ulOverlayHandle);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *مجموعه_Overlay_Intersection_ماسک)(VROverlayHandle_t ulOverlayHandle, بنية VROverlay_Intersection_ماسک_Primitive_t * p_ماسک_Primitives, uint32_t un_رقم_ماسک_Primitives, uint32_t un_Primitive_اندازه);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *TriggerLaserMouseHapticVibration)(VROverlayHandle_t ulOverlayHandle, عائم fDurationSeconds, عائم fFrequency, عائم fAmplitude);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *مجموعه_Overlay_Cursor)(VROverlayHandle_t ulOverlayHandle, VROverlayHandle_t ulCursorHandle);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *مجموعه_Overlay_Cursor_Position_Override)(VROverlayHandle_t ulOverlayHandle, بنية HmdVector2_t * pvCursor);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *ClearOverlayCursorPositionOverride)(VROverlayHandle_t ulOverlayHandle);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *مجموعه_Overlay_Texture)(VROverlayHandle_t ulOverlayHandle, بنية Texture_t * pTexture);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *ClearOverlayTexture)(VROverlayHandle_t ulOverlayHandle);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *مجموعه_Overlay_Raw)(VROverlayHandle_t ulOverlayHandle, فراغ * pv_میانگیر, uint32_t un_عرض, uint32_t un_ارتفاع, uint32_t un_بایتها_در_هر_Pixel);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *مجموعه_Overlay_From_File)(VROverlayHandle_t ulOverlayHandle, حرف * pch_File_مسیر);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayTexture)(VROverlayHandle_t ulOverlayHandle, فراغ ** pNativeTextureHandle, فراغ * pNativeTextureRef, uint32_t * p_عرض, uint32_t * p_ارتفاع, uint32_t * pNativeFormat, ETextureType * pAPIType, EColorSpace * pColorSpace, بنية VRTextureBounds_t * pTextureBounds);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *ReleaseNativeOverlayHandle)(VROverlayHandle_t ulOverlayHandle, فراغ * pNativeTextureHandle);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *Get_Overlay_Texture_اندازه)(VROverlayHandle_t ulOverlayHandle, uint32_t * p_عرض, uint32_t * p_ارتفاع);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *CreateDashboardOverlay)(حرف * pch_Overlay_کلید, حرف * pchOverlayFriendlyName, VROverlayHandle_t * pMainHandle, VROverlayHandle_t * pThumbnailHandle);
	bool (OPENVR_FNTABLE_CALLTYPE *IsDashboardVisible)();
	bool (OPENVR_FNTABLE_CALLTYPE *Is_فعال_Dashboard_Overlay)(VROverlayHandle_t ulOverlayHandle);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *مجموعه_Dashboard_Overlay_Scene_Process)(VROverlayHandle_t ulOverlayHandle, uint32_t unProcessId);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetDashboardOverlaySceneProcess)(VROverlayHandle_t ulOverlayHandle, uint32_t * punProcessId);
	فراغ (OPENVR_FNTABLE_CALLTYPE *ShowDashboard)(حرف * pch_Overlay_مقصد_Show);
	Tracked_Device_شاخص_t (OPENVR_FNTABLE_CALLTYPE *GetPrimaryDashboardDevice)();
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *ShowKeyboard)(EGamepad_متن_درون_داد_نما e_درون_داد_نما, EGamepad_متن_درون_داد_سطر_نما e_سطر_درون_داد_نما, uint32_t unFlags, حرف * pchDescription, uint32_t unCharMax, حرف * pch_Existing_متن, uint64_t u_User_مقدار);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *ShowKeyboardForOverlay)(VROverlayHandle_t ulOverlayHandle, EGamepad_متن_درون_داد_نما e_درون_داد_نما, EGamepad_متن_درون_داد_سطر_نما e_سطر_درون_داد_نما, uint32_t unFlags, حرف * pchDescription, uint32_t unCharMax, حرف * pch_Existing_متن, uint64_t u_User_مقدار);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *Get_Keyboard_متن)(حرف * pch_متن, uint32_t cch_متن);
	فراغ (OPENVR_FNTABLE_CALLTYPE *HideKeyboard)();
	فراغ (OPENVR_FNTABLE_CALLTYPE *مجموعه_Keyboard_Transform_Absolute)(ETrackingUniverseOrigin eTrackingOrigin, بنية HmdMatrix34_t * pmat_Tracking_Origin_مقصد_Keyboard_Transform);
	فراغ (OPENVR_FNTABLE_CALLTYPE *مجموعه_Keyboard_Position_For_Overlay)(VROverlayHandle_t ulOverlayHandle, بنية HmdRect2_t avoidRect);
	VRMessageOverlayResponse (OPENVR_FNTABLE_CALLTYPE *Show_پیام_Overlay)(حرف * pch_متن, حرف * pchCaption, حرف * pch_Button0_متن, حرف * pch_Button1_متن, حرف * pch_Button2_متن, حرف * pch_Button3_متن);
	فراغ (OPENVR_FNTABLE_CALLTYPE *Close_پیام_Overlay)();
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
	فراغ (OPENVR_FNTABLE_CALLTYPE *مجموعه_Headset_View_اندازه)(uint32_t n_عرض, uint32_t n_ارتفاع);
	فراغ (OPENVR_FNTABLE_CALLTYPE *Get_Headset_View_اندازه)(uint32_t * pn_عرض, uint32_t * pn_ارتفاع);
	فراغ (OPENVR_FNTABLE_CALLTYPE *مجموعه_Headset_View_نما)(Headset_View_نما_t e_Headset_View_نما);
	Headset_View_نما_t (OPENVR_FNTABLE_CALLTYPE *Get_Headset_View_نما)();
	فراغ (OPENVR_FNTABLE_CALLTYPE *مجموعه_Headset_View_Cropped)(bool bCropped);
	bool (OPENVR_FNTABLE_CALLTYPE *GetHeadsetViewCropped)();
	عائم (OPENVR_FNTABLE_CALLTYPE *Get_Headset_View_Aspect_نسبت)();
	فراغ (OPENVR_FNTABLE_CALLTYPE *مجموعه_Headset_View_Blend_Range)(عائم fl_شروع_Pct, عائم fl_انتها_Pct);
	فراغ (OPENVR_FNTABLE_CALLTYPE *GetHeadsetViewBlendRange)(عائم * p_شروع_Pct, عائم * p_انتها_Pct);
};

بنية VR_IVRRender_Models_Fn_جدول
{
	EVRRenderModelError (OPENVR_FNTABLE_CALLTYPE *بارگیری_Render_Model_Async)(حرف * pchRenderModelName, بنية RenderModel_t ** ppRenderModel);
	فراغ (OPENVR_FNTABLE_CALLTYPE *FreeRenderModel)(بنية RenderModel_t * pRenderModel);
	EVRRenderModelError (OPENVR_FNTABLE_CALLTYPE *بارگیری_Texture_Async)(TextureID_t textureId, بنية RenderModel_TextureMap_t ** ppTexture);
	فراغ (OPENVR_FNTABLE_CALLTYPE *FreeTexture)(بنية RenderModel_TextureMap_t * pTexture);
	EVRRenderModelError (OPENVR_FNTABLE_CALLTYPE *بارگیری_Texture_D3_D11_Async)(TextureID_t textureId, فراغ * pD3D11Device, فراغ ** ppD3D11Texture2D);
	EVRRenderModelError (OPENVR_FNTABLE_CALLTYPE *بارگیری_Into_Texture_D3_D11_Async)(TextureID_t textureId, فراغ * pDstTexture);
	فراغ (OPENVR_FNTABLE_CALLTYPE *FreeTextureD3D11)(فراغ * pD3D11Texture2D);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetRenderModelName)(uint32_t un_Render_Model_شاخص, حرف * pchRenderModelName, uint32_t unRenderModelNameLen);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *Get_Render_Model_شمار)();
	uint32_t (OPENVR_FNTABLE_CALLTYPE *Get_Component_شمار)(حرف * pchRenderModelName);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetComponentName)(حرف * pchRenderModelName, uint32_t un_Component_شاخص, حرف * pchComponentName, uint32_t unComponentNameLen);
	uint64_t (OPENVR_FNTABLE_CALLTYPE *Get_Component_Button_ماسک)(حرف * pchRenderModelName, حرف * pchComponentName);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetComponentRenderModelName)(حرف * pchRenderModelName, حرف * pchComponentName, حرف * pchComponentRenderModelName, uint32_t unComponentRenderModelNameLen);
	bool (OPENVR_FNTABLE_CALLTYPE *Get_Component_State_For_Device_مسیر)(حرف * pchRenderModelName, حرف * pchComponentName, VRInput_مقدار_Handle_t device_مسیر, Render_Model_Controller_نما_State_t * pState, RenderModel_ComponentState_t * pComponentState);
	bool (OPENVR_FNTABLE_CALLTYPE *GetComponentState)(حرف * pchRenderModelName, حرف * pchComponentName, VRControllerState_t * pControllerState, بنية Render_Model_Controller_نما_State_t * pState, بنية RenderModel_ComponentState_t * pComponentState);
	bool (OPENVR_FNTABLE_CALLTYPE *RenderModelHasComponent)(حرف * pchRenderModelName, حرف * pchComponentName);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetRenderModelThumbnailURL)(حرف * pchRenderModelName, حرف * pchThumbnailURL, uint32_t unThumbnailURLLen, EVRRenderModelError * peError);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *Get_Render_Model_Original_مسیر)(حرف * pchRenderModelName, حرف * pch_Original_مسیر, uint32_t un_Original_مسیر_Len, EVRRenderModelError * peError);
	حرف * (OPENVR_FNTABLE_CALLTYPE *GetRenderModelErrorNameFromEnum)(EVRRenderModelError error);
};

بنية VR_IVRNotifications_Fn_جدول
{
	EVRNotificationError (OPENVR_FNTABLE_CALLTYPE *CreateNotification)(VROverlayHandle_t ulOverlayHandle, uint64_t ul_User_مقدار, EVRNotificationType type, حرف * pch_متن, EVRNotificationStyle style, بنية NotificationBitmap_t * pImage, VRNotificationId * pNotificationId);
	EVRNotificationError (OPENVR_FNTABLE_CALLTYPE *RemoveNotification)(VRNotificationId notificationId);
};

بنية VR_IVRSettings_Fn_جدول
{
	حرف * (OPENVR_FNTABLE_CALLTYPE *GetSettingsErrorNameFromEnum)(EVRSettingsError eError);
	فراغ (OPENVR_FNTABLE_CALLTYPE *مجموعه_Bool)(حرف * pchSection, حرف * pch_Settings_کلید, bool b_مقدار, EVRSettingsError * peError);
	فراغ (OPENVR_FNTABLE_CALLTYPE *مجموعه_Int32)(حرف * pchSection, حرف * pch_Settings_کلید, int32_t n_مقدار, EVRSettingsError * peError);
	فراغ (OPENVR_FNTABLE_CALLTYPE *مجموعه_Float)(حرف * pchSection, حرف * pch_Settings_کلید, عائم fl_مقدار, EVRSettingsError * peError);
	فراغ (OPENVR_FNTABLE_CALLTYPE *مجموعه_String)(حرف * pchSection, حرف * pch_Settings_کلید, حرف * pch_مقدار, EVRSettingsError * peError);
	bool (OPENVR_FNTABLE_CALLTYPE *GetBool)(حرف * pchSection, حرف * pch_Settings_کلید, EVRSettingsError * peError);
	int32_t (OPENVR_FNTABLE_CALLTYPE *GetInt32)(حرف * pchSection, حرف * pch_Settings_کلید, EVRSettingsError * peError);
	عائم (OPENVR_FNTABLE_CALLTYPE *GetFloat)(حرف * pchSection, حرف * pch_Settings_کلید, EVRSettingsError * peError);
	فراغ (OPENVR_FNTABLE_CALLTYPE *GetString)(حرف * pchSection, حرف * pch_Settings_کلید, حرف * pch_مقدار, uint32_t un_مقدار_Len, EVRSettingsError * peError);
	فراغ (OPENVR_FNTABLE_CALLTYPE *RemoveSection)(حرف * pchSection, EVRSettingsError * peError);
	فراغ (OPENVR_FNTABLE_CALLTYPE *Remove_کلید_درون_Section)(حرف * pchSection, حرف * pch_Settings_کلید, EVRSettingsError * peError);
};

بنية VR_IVRScreenshots_Fn_جدول
{
	EVRScreenshotError (OPENVR_FNTABLE_CALLTYPE *RequestScreenshot)(ScreenshotHandle_t * p_بیرون_Screenshot_Handle, EVRScreenshotType type, حرف * pchPreviewFilename, حرف * pchVRFilename);
	EVRScreenshotError (OPENVR_FNTABLE_CALLTYPE *HookScreenshot)(EVRScreenshotType * pSupportedTypes, صحيح رقم_Types);
	EVRScreenshotType (OPENVR_FNTABLE_CALLTYPE *GetScreenshotPropertyType)(ScreenshotHandle_t screenshotHandle, EVRScreenshotError * pError);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetScreenshotPropertyFilename)(ScreenshotHandle_t screenshotHandle, EVRScreenshotPropertyFilenames filenameType, حرف * pchFilename, uint32_t cchFilename, EVRScreenshotError * pError);
	EVRScreenshotError (OPENVR_FNTABLE_CALLTYPE *Update_Screenshot_پیشرفت)(ScreenshotHandle_t screenshotHandle, عائم fl_پیشرفت);
	EVRScreenshotError (OPENVR_FNTABLE_CALLTYPE *TakeStereoScreenshot)(ScreenshotHandle_t * p_بیرون_Screenshot_Handle, حرف * pchPreviewFilename, حرف * pchVRFilename);
	EVRScreenshotError (OPENVR_FNTABLE_CALLTYPE *SubmitScreenshot)(ScreenshotHandle_t screenshotHandle, EVRScreenshotType type, حرف * pch_منبع_Preview_Filename, حرف * pch_منبع_VRFilename);
};

بنية VR_IVRResources_Fn_جدول
{
	uint32_t (OPENVR_FNTABLE_CALLTYPE *بارگیری_Shared_Resource)(حرف * pchResourceName, حرف * pch_میانگیر, uint32_t un_میانگیر_Len);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *Get_Resource_پر_مسیر)(حرف * pchResourceName, حرف * pchResourceTypeDirectory, حرف * pch_مسیر_میانگیر, uint32_t un_میانگیر_Len);
};

بنية VR_IVRDriver_Manager_Fn_جدول
{
	uint32_t (OPENVR_FNTABLE_CALLTYPE *Get_Driver_شمار)();
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetDriverName)(DriverId_t nDriver, حرف * pch_مقدار, uint32_t un_میانگیر_اندازه);
	DriverHandle_t (OPENVR_FNTABLE_CALLTYPE *GetDriverHandle)(حرف * pchDriverName);
	bool (OPENVR_FNTABLE_CALLTYPE *IsEnabled)(DriverId_t nDriver);
};

بنية VR_IVRInput_Fn_جدول
{
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *مجموعه_Action_Manifest_مسیر)(حرف * pch_Action_Manifest_مسیر);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *Get_Action_مجموعه_Handle)(حرف * pch_Action_مجموعه_Name, VRAction_مجموعه_Handle_t * pHandle);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetActionHandle)(حرف * pchActionName, VRActionHandle_t * pHandle);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *Get_درون_داد_منبع_Handle)(حرف * pch_درون_داد_منبع_مسیر, VRInput_مقدار_Handle_t * pHandle);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *UpdateActionState)(بنية VRActive_Action_مجموعه_t * pSets, uint32_t un_اندازه_از_VRSelected_Action_مجموعه_t, uint32_t un_مجموعه_شمار);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *Get_Digital_Action_داده)(VRActionHandle_t action, بنية درون_داد_Digital_Action_داده_t * p_Action_داده, uint32_t un_Action_داده_اندازه, VRInput_مقدار_Handle_t ul_Restrict_مقصد_Device);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *Get_Analog_Action_داده)(VRActionHandle_t action, بنية درون_داد_Analog_Action_داده_t * p_Action_داده, uint32_t un_Action_داده_اندازه, VRInput_مقدار_Handle_t ul_Restrict_مقصد_Device);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *Get_Pose_Action_داده_Relative_مقصد_Now)(VRActionHandle_t action, ETrackingUniverseOrigin eOrigin, عائم fPredictedSecondsFromNow, بنية درون_داد_Pose_Action_داده_t * p_Action_داده, uint32_t un_Action_داده_اندازه, VRInput_مقدار_Handle_t ul_Restrict_مقصد_Device);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *Get_Pose_Action_داده_For_بعدی_قاب)(VRActionHandle_t action, ETrackingUniverseOrigin eOrigin, بنية درون_داد_Pose_Action_داده_t * p_Action_داده, uint32_t un_Action_داده_اندازه, VRInput_مقدار_Handle_t ul_Restrict_مقصد_Device);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *Get_Skeletal_Action_داده)(VRActionHandle_t action, بنية درون_داد_Skeletal_Action_داده_t * p_Action_داده, uint32_t un_Action_داده_اندازه);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetDominantHand)(ETrackedControllerRole * peDominantHand);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *مجموعه_Dominant_Hand)(ETrackedControllerRole eDominantHand);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *Get_Bone_شمار)(VRActionHandle_t action, uint32_t * p_Bone_شمار);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetBoneHierarchy)(VRActionHandle_t action, Bone_شاخص_t * p_والد_Indices, uint32_t un_شاخص_Aray_شمار);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetBoneName)(VRActionHandle_t action, Bone_شاخص_t n_Bone_شاخص, حرف * pchBoneName, uint32_t un_Name_میانگیر_اندازه);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetSkeletalReferenceTransforms)(VRActionHandle_t action, EVRSkeletalTransformSpace eTransformSpace, EVRSkeletalReferencePose eReferencePose, بنية VRBoneTransform_t * pTransformArray, uint32_t un_Transform_Array_شمار);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetSkeletalTrackingLevel)(VRActionHandle_t action, EVRSkeletalTrackingLevel * pSkeletalTrackingLevel);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *Get_Skeletal_Bone_داده)(VRActionHandle_t action, EVRSkeletalTransformSpace eTransformSpace, EVRSkeletalMotionRange eMotionRange, بنية VRBoneTransform_t * pTransformArray, uint32_t un_Transform_Array_شمار);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *Get_Skeletal_Summary_داده)(VRActionHandle_t action, EVRSummaryType eSummaryType, بنية VRSkeletal_Summary_داده_t * p_Skeletal_Summary_داده);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *Get_Skeletal_Bone_داده_Compressed)(VRActionHandle_t action, EVRSkeletalMotionRange eMotionRange, فراغ * pv_Compressed_داده, uint32_t un_Compressed_اندازه, uint32_t * pun_Required_Compressed_اندازه);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *Decompress_Skeletal_Bone_داده)(فراغ * pv_Compressed_میانگیر, uint32_t un_Compressed_میانگیر_اندازه, EVRSkeletalTransformSpace eTransformSpace, بنية VRBoneTransform_t * pTransformArray, uint32_t un_Transform_Array_شمار);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *TriggerHapticVibrationAction)(VRActionHandle_t action, عائم f_شروع_Seconds_From_Now, عائم fDurationSeconds, عائم fFrequency, عائم fAmplitude, VRInput_مقدار_Handle_t ul_Restrict_مقصد_Device);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetActionOrigins)(VRAction_مجموعه_Handle_t action_مجموعه_Handle, VRActionHandle_t digitalActionHandle, VRInput_مقدار_Handle_t * origins_بیرون, uint32_t origin_بیرون_شمار);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetOriginLocalizedName)(VRInput_مقدار_Handle_t origin, حرف * pchNameArray, uint32_t un_Name_Array_اندازه, int32_t un_String_Sections_مقصد_Include);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetOriginTrackedDeviceInfo)(VRInput_مقدار_Handle_t origin, بنية درون_داد_Origin_Info_t * pOriginInfo, uint32_t un_Origin_Info_اندازه);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetActionBindingInfo)(VRActionHandle_t action, بنية درون_داد_Binding_Info_t * pOriginInfo, uint32_t un_Binding_Info_اندازه, uint32_t un_Binding_Info_شمار, uint32_t * pun_Returned_Binding_Info_شمار);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *ShowActionOrigins)(VRAction_مجموعه_Handle_t action_مجموعه_Handle, VRActionHandle_t ulActionHandle);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *Show_Bindings_For_Action_مجموعه)(بنية VRActive_Action_مجموعه_t * pSets, uint32_t un_اندازه_از_VRSelected_Action_مجموعه_t, uint32_t un_مجموعه_شمار, VRInput_مقدار_Handle_t origin_مقصد_Highlight);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetComponentStateForBinding)(حرف * pchRenderModelName, حرف * pchComponentName, بنية درون_داد_Binding_Info_t * pOriginInfo, uint32_t un_Binding_Info_اندازه, uint32_t un_Binding_Info_شمار, RenderModel_ComponentState_t * pComponentState);
	bool (OPENVR_FNTABLE_CALLTYPE *Is_Using_Legacy_درون_داد)();
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *OpenBindingUI)(حرف * pch_App_کلید, VRAction_مجموعه_Handle_t ul_Action_مجموعه_Handle, VRInput_مقدار_Handle_t ulDeviceHandle, bool bShowOnDesktop);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetBindingVariant)(VRInput_مقدار_Handle_t ul_Device_مسیر, حرف * pchVariantArray, uint32_t un_Variant_Array_اندازه);
};

بنية VR_IVRIOBuffer_Fn_جدول
{
	EIOBufferError (OPENVR_FNTABLE_CALLTYPE *Open)(حرف * pch_مسیر, EIOBuffer_نما نما, uint32_t un_Element_اندازه, uint32_t unElements, IOBufferHandle_t * pul_میانگیر);
	EIOBufferError (OPENVR_FNTABLE_CALLTYPE *Close)(IOBufferHandle_t ul_میانگیر);
	EIOBufferError (OPENVR_FNTABLE_CALLTYPE *Read)(IOBufferHandle_t ul_میانگیر, فراغ * pDst, uint32_t un_بایتها, uint32_t * punRead);
	EIOBufferError (OPENVR_FNTABLE_CALLTYPE *Write)(IOBufferHandle_t ul_میانگیر, فراغ * pSrc, uint32_t un_بایتها);
	PropertyContainerHandle_t (OPENVR_FNTABLE_CALLTYPE *PropertyContainer)(IOBufferHandle_t ul_میانگیر);
	bool (OPENVR_FNTABLE_CALLTYPE *HasReaders)(IOBufferHandle_t ul_میانگیر);
};

بنية VR_IVRSpatial_Anchors_Fn_جدول
{
	EVRSpatialAnchorError (OPENVR_FNTABLE_CALLTYPE *CreateSpatialAnchorFromDescriptor)(حرف * pchDescriptor, SpatialAnchorHandle_t * p_Handle_بیرون);
	EVRSpatialAnchorError (OPENVR_FNTABLE_CALLTYPE *CreateSpatialAnchorFromPose)(Tracked_Device_شاخص_t un_Device_شاخص, ETrackingUniverseOrigin eOrigin, بنية SpatialAnchorPose_t * pPose, SpatialAnchorHandle_t * p_Handle_بیرون);
	EVRSpatialAnchorError (OPENVR_FNTABLE_CALLTYPE *GetSpatialAnchorPose)(SpatialAnchorHandle_t unHandle, ETrackingUniverseOrigin eOrigin, بنية SpatialAnchorPose_t * p_Pose_بیرون);
	EVRSpatialAnchorError (OPENVR_FNTABLE_CALLTYPE *GetSpatialAnchorDescriptor)(SpatialAnchorHandle_t unHandle, حرف * pch_Descriptor_بیرون, uint32_t * pun_Descriptor_میانگیر_Len_درون_بیرون);
};

بنية VR_IVRDebug_Fn_جدول
{
	EVRDebugError (OPENVR_FNTABLE_CALLTYPE *EmitVrProfilerEvent)(حرف * pch_پیام);
	EVRDebugError (OPENVR_FNTABLE_CALLTYPE *BeginVrProfilerEvent)(VrProfilerEventHandle_t * p_Handle_بیرون);
	EVRDebugError (OPENVR_FNTABLE_CALLTYPE *پایان_Vr_Profiler_Event)(VrProfilerEventHandle_t hHandle, حرف * pch_پیام);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *DriverDebugRequest)(Tracked_Device_شاخص_t un_Device_شاخص, حرف * pchRequest, حرف * pch_Response_میانگیر, uint32_t un_Response_میانگیر_اندازه);
};

بنية VR_IVRProperties_Fn_جدول
{
	ETrackedPropertyError (OPENVR_FNTABLE_CALLTYPE *ReadPropertyBatch)(PropertyContainerHandle_t ulContainerHandle, بنية PropertyRead_t * pBatch, uint32_t un_Batch_مدخل_شمار);
	ETrackedPropertyError (OPENVR_FNTABLE_CALLTYPE *WritePropertyBatch)(PropertyContainerHandle_t ulContainerHandle, بنية PropertyWrite_t * pBatch, uint32_t un_Batch_مدخل_شمار);
	حرف * (OPENVR_FNTABLE_CALLTYPE *GetPropErrorNameFromEnum)(ETrackedPropertyError error);
	PropertyContainerHandle_t (OPENVR_FNTABLE_CALLTYPE *Tracked_Device_مقصد_Property_Container)(Tracked_Device_شاخص_t nDevice);
};

بنية VR_IVRPaths_Fn_جدول
{
	ETrackedPropertyError (OPENVR_FNTABLE_CALLTYPE *Read_مسیر_Batch)(PropertyContainerHandle_t ul_ریشه_Handle, بنية مسیر_Read_t * pBatch, uint32_t un_Batch_مدخل_شمار);
	ETrackedPropertyError (OPENVR_FNTABLE_CALLTYPE *Write_مسیر_Batch)(PropertyContainerHandle_t ul_ریشه_Handle, بنية مسیر_Write_t * pBatch, uint32_t un_Batch_مدخل_شمار);
	ETrackedPropertyError (OPENVR_FNTABLE_CALLTYPE *String_مقصد_Handle)(مسیر_Handle_t * pHandle, حرف * pch_مسیر);
	ETrackedPropertyError (OPENVR_FNTABLE_CALLTYPE *Handle_مقصد_String)(مسیر_Handle_t pHandle, حرف * pch_میانگیر, uint32_t un_میانگیر_اندازه, uint32_t * pun_میانگیر_اندازه_استفاده_شده);
};

بنية VR_IVRBlock_صف_Fn_جدول
{
	EBlock_صف_Error (OPENVR_FNTABLE_CALLTYPE *Create)(PropertyContainerHandle_t * pul_صف_Handle, حرف * pch_مسیر, uint32_t un_بلوک_داده_اندازه, uint32_t un_بلوک_سرآیند_اندازه, uint32_t un_بلوک_شمار, uint32_t unFlags);
	EBlock_صف_Error (OPENVR_FNTABLE_CALLTYPE *Connect)(PropertyContainerHandle_t * pul_صف_Handle, حرف * pch_مسیر);
	EBlock_صف_Error (OPENVR_FNTABLE_CALLTYPE *Destroy)(PropertyContainerHandle_t ul_صف_Handle);
	EBlock_صف_Error (OPENVR_FNTABLE_CALLTYPE *Acquire_Write_Only_بلوک)(PropertyContainerHandle_t ul_صف_Handle, PropertyContainerHandle_t * pul_بلوک_Handle, فراغ ** ppv_میانگیر);
	EBlock_صف_Error (OPENVR_FNTABLE_CALLTYPE *Release_Write_Only_بلوک)(PropertyContainerHandle_t ul_صف_Handle, PropertyContainerHandle_t ul_بلوک_Handle);
	EBlock_صف_Error (OPENVR_FNTABLE_CALLTYPE *Wait_And_Acquire_Read_Only_بلوک)(PropertyContainerHandle_t ul_صف_Handle, PropertyContainerHandle_t * pul_بلوک_Handle, فراغ ** ppv_میانگیر, EBlock_صف_Read_Type eReadType, uint32_t unTimeoutMs);
	EBlock_صف_Error (OPENVR_FNTABLE_CALLTYPE *Acquire_Read_Only_بلوک)(PropertyContainerHandle_t ul_صف_Handle, PropertyContainerHandle_t * pul_بلوک_Handle, فراغ ** ppv_میانگیر, EBlock_صف_Read_Type eReadType);
	EBlock_صف_Error (OPENVR_FNTABLE_CALLTYPE *Release_Read_Only_بلوک)(PropertyContainerHandle_t ul_صف_Handle, PropertyContainerHandle_t ul_بلوک_Handle);
	EBlock_صف_Error (OPENVR_FNTABLE_CALLTYPE *صف_Has_Reader)(PropertyContainerHandle_t ul_صف_Handle, bool * pbHasReaders);
};


#إذا 0
// Global entry points
S_API intptr_t VR_Init_داخلی( EVRInitError *peError, EVRApplicationType eType );
S_API فراغ VR_Shutdown_داخلی();
S_API bool VR_IsHmdPresent();
S_API intptr_t VR_GetGenericInterface( ثابت حرف *pch_Interface_نسخه, EVRInitError *peError );
S_API bool VR_IsRuntimeInstalled();
S_API ثابت حرف * VR_Get_VRInit_Error_As_نماد( EVRInitError error );
S_API ثابت حرف * VR_GetVRInitErrorAsEnglishDescription( EVRInitError error );
#پایان_اگر

#پایان_اگر // __OPENVR_API_FLAT_H__


