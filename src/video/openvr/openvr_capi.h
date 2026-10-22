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

#اگر_غیر_تعریف_شدہ __OPENVR_API_FLAT_H__
#تعریف_کرو __OPENVR_API_FLAT_H__
#اگر defined( _WIN32 ) || defined( __clang__ )
#ہدایت once
#اگر_ختم

#اگر_تعریف_شدہ __cplusplus
#تعریف_کرو EXTERN_C خارجی "C"
#ورنہ
#تعریف_کرو EXTERN_C
#اگر_ختم

#اگر defined( _WIN32 )
#تعریف_کرو OPENVR_FNTABLE_CALLTYPE __stdcall
#ورنہ
#تعریف_کرو OPENVR_FNTABLE_CALLTYPE 
#اگر_ختم

// OPENVR API export macro
#اگر defined( _WIN32 ) && !defined( _X360 )
	#اگر defined( OPENVR_API_EXPORTS )
	#تعریف_کرو S_API EXTERN_C __declspec( dllexport )
	#وگرنہ_اگر defined( OPENVR_API_NODLL )
	#تعریف_کرو S_API EXTERN_C
	#ورنہ
	#تعریف_کرو S_API خارجی "C" __declspec( dllimport ) 
	#اگر_ختم // OPENVR_API_EXPORTS
#وگرنہ_اگر defined( __GNUC__ )
	#اگر defined( OPENVR_API_EXPORTS )
	#تعریف_کرو S_API EXTERN_C __attribute__ ((visibility("default")))
	#ورنہ
	#تعریف_کرو S_API EXTERN_C
	#اگر_ختم // OPENVR_API_EXPORTS
#ورنہ // !WIN32
	#اگر defined( OPENVR_API_EXPORTS )
	#تعریف_کرو S_API EXTERN_C
	#ورنہ
	#تعریف_کرو S_API EXTERN_C
	#اگر_ختم // OPENVR_API_EXPORTS
#اگر_ختم

#اگر_غیر_تعریف_شدہ USE_SDL
#شامل <stdint.h>

#اگر defined( __WIN32 )
قسمتعریف حرف bool;
#ورنہ
#شامل <stdbool.h>
#اگر_ختم
#اگر_ختم // USE_SDL

// OpenVR Constants

ساکن ثابت غیرعلامتی طویل k_nDriverNone = 4294967295;
ساکن ثابت غیرعلامتی طویل k_un_Max_Driver_Debug_Response_سائز = 32768;
ساکن ثابت غیرعلامتی طویل k_un_Tracked_Device_اشاریہ_Hmd = 0;
ساکن ثابت غیرعلامتی طویل k_un_Max_Tracked_Device_گنتی = 64;
ساکن ثابت غیرعلامتی طویل k_un_Tracked_Device_اشاریہ_Other = 4294967294;
ساکن ثابت غیرعلامتی طویل k_un_Tracked_Device_اشاریہ_Invalid = 4294967295;
ساکن ثابت غیرعلامتی طویل طویل k_ulInvalidPropertyContainer = 0;
ساکن ثابت غیرعلامتی طویل k_un_Invalid_Property_لیبل = 0;
ساکن ثابت غیرعلامتی طویل طویل k_ulInvalidDriverHandle = 0;
ساکن ثابت غیرعلامتی طویل k_un_Float_Property_لیبل = 1;
ساکن ثابت غیرعلامتی طویل k_un_Int32_Property_لیبل = 2;
ساکن ثابت غیرعلامتی طویل k_un_Uint64_Property_لیبل = 3;
ساکن ثابت غیرعلامتی طویل k_un_Bool_Property_لیبل = 4;
ساکن ثابت غیرعلامتی طویل k_un_String_Property_لیبل = 5;
ساکن ثابت غیرعلامتی طویل k_un_Error_Property_لیبل = 6;
ساکن ثابت غیرعلامتی طویل k_un_Double_Property_لیبل = 7;
ساکن ثابت غیرعلامتی طویل k_un_Hmd_Matrix34_Property_لیبل = 20;
ساکن ثابت غیرعلامتی طویل k_un_Hmd_Matrix44_Property_لیبل = 21;
ساکن ثابت غیرعلامتی طویل k_un_Hmd_Vector3_Property_لیبل = 22;
ساکن ثابت غیرعلامتی طویل k_un_Hmd_Vector4_Property_لیبل = 23;
ساکن ثابت غیرعلامتی طویل k_un_Hmd_Vector2_Property_لیبل = 24;
ساکن ثابت غیرعلامتی طویل k_un_Hmd_Quad_Property_لیبل = 25;
ساکن ثابت غیرعلامتی طویل k_un_Hidden_Area_Property_لیبل = 30;
ساکن ثابت غیرعلامتی طویل k_un_راستہ_Handle_Info_لیبل = 31;
ساکن ثابت غیرعلامتی طویل k_un_Action_Property_لیبل = 32;
ساکن ثابت غیرعلامتی طویل k_un_داخلہ_قدر_Property_لیبل = 33;
ساکن ثابت غیرعلامتی طویل k_un_Wildcard_Property_لیبل = 34;
ساکن ثابت غیرعلامتی طویل k_un_Haptic_Vibration_Property_لیبل = 35;
ساکن ثابت غیرعلامتی طویل k_un_Skeleton_Property_لیبل = 36;
ساکن ثابت غیرعلامتی طویل k_un_Spatial_Anchor_Pose_Property_لیبل = 40;
ساکن ثابت غیرعلامتی طویل k_un_Json_Property_لیبل = 41;
ساکن ثابت غیرعلامتی طویل k_un_فعال_Action_سیٹ_Property_لیبل = 42;
ساکن ثابت غیرعلامتی طویل k_un_Open_VRInternal_Reserved_آغاز = 1000;
ساکن ثابت غیرعلامتی طویل k_un_Open_VRInternal_Reserved_انتہا = 10000;
ساکن ثابت غیرعلامتی طویل k_un_Max_Property_String_سائز = 32768;
ساکن ثابت غیرعلامتی طویل طویل k_ulInvalidActionHandle = 0;
ساکن ثابت غیرعلامتی طویل طویل k_ul_Invalid_Action_سیٹ_Handle = 0;
ساکن ثابت غیرعلامتی طویل طویل k_ul_Invalid_داخلہ_قدر_Handle = 0;
ساکن ثابت غیرعلامتی طویل k_un_Controller_State_Axis_گنتی = 5;
ساکن ثابت غیرعلامتی طویل طویل k_ulOverlayHandleInvalid = 0;
ساکن ثابت غیرعلامتی طویل k_unMaxDistortionFunctionParameters = 8;
ساکن ثابت غیرعلامتی طویل k_unScreenshotHandleInvalid = 0;
ساکن ثابت حرف * IVRSystem_نسخہ = "IVRSystem_022";
ساکن ثابت حرف * IVRExtended_Display_نسخہ = "IVRExtendedDisplay_001";
ساکن ثابت حرف * IVRTracked_Camera_نسخہ = "IVRTrackedCamera_006";
ساکن ثابت غیرعلامتی طویل k_un_Max_Application_کلید_لمبائی = 128;
ساکن ثابت حرف * k_pch_MimeType_HomeApp = "vr/home";
ساکن ثابت حرف * k_pch_MimeType_GameTheater = "vr/game_theater";
ساکن ثابت حرف * IVRApplications_نسخہ = "IVRApplications_007";
ساکن ثابت حرف * IVRChaperone_نسخہ = "IVRChaperone_004";
ساکن ثابت حرف * IVRChaperone_تیاری_نسخہ = "IVRChaperoneSetup_006";
ساکن ثابت حرف * IVRCompositor_نسخہ = "IVRCompositor_027";
ساکن ثابت غیرعلامتی طویل k_un_VROverlay_Max_کلید_لمبائی = 128;
ساکن ثابت غیرعلامتی طویل k_un_VROverlay_Max_Name_لمبائی = 128;
ساکن ثابت غیرعلامتی طویل k_un_Max_Overlay_گنتی = 128;
ساکن ثابت غیرعلامتی طویل k_un_Max_Overlay_Intersection_نقاب_Primitives_گنتی = 32;
ساکن ثابت حرف * IVROverlay_نسخہ = "IVROverlay_026";
ساکن ثابت حرف * IVROverlay_View_نسخہ = "IVROverlayView_003";
ساکن ثابت غیرعلامتی طویل k_un_Headset_View_Max_چوڑائی = 3840;
ساکن ثابت غیرعلامتی طویل k_un_Headset_View_Max_اونچائی = 2160;
ساکن ثابت حرف * k_pch_Headset_View_Overlay_کلید = "system.HeadsetView";
ساکن ثابت حرف * IVRHeadset_View_نسخہ = "IVRHeadsetView_001";
ساکن ثابت حرف * k_pch_Controller_Component_GDC2015 = "gdc2015";
ساکن ثابت حرف * k_pch_Controller_Component_بنیاد = "base";
ساکن ثابت حرف * k_pch_Controller_Component_Tip = "tip";
ساکن ثابت حرف * k_pch_Controller_Component_OpenXR_Aim = "openxr_aim";
ساکن ثابت حرف * k_pch_Controller_Component_HandGrip = "handgrip";
ساکن ثابت حرف * k_pch_Controller_Component_OpenXR_Grip = "openxr_grip";
ساکن ثابت حرف * k_pch_Controller_Component_OpenXR_HandModel = "openxr_handmodel";
ساکن ثابت حرف * k_pch_Controller_Component_حالت = "status";
ساکن ثابت حرف * IVRRender_Models_نسخہ = "IVRRenderModels_006";
ساکن ثابت غیرعلامتی طویل k_un_Notification_متن_Max_سائز = 256;
ساکن ثابت حرف * IVRNotifications_نسخہ = "IVRNotifications_002";
ساکن ثابت غیرعلامتی طویل k_un_Max_Settings_کلید_لمبائی = 128;
ساکن ثابت حرف * IVRSettings_نسخہ = "IVRSettings_003";
ساکن ثابت حرف * k_pch_SteamVR_Section = "steamvr";
ساکن ثابت حرف * k_pch_SteamVR_RequireHmd_String = "requireHmd";
ساکن ثابت حرف * k_pch_Steam_VR_Forced_Driver_کلید_String = "forcedDriver";
ساکن ثابت حرف * k_pch_Steam_VR_Forced_Hmd_کلید_String = "forcedHmd";
ساکن ثابت حرف * k_pch_SteamVR_DisplayDebug_Bool = "displayDebug";
ساکن ثابت حرف * k_pch_SteamVR_DebugProcessPipe_String = "debugProcessPipe";
ساکن ثابت حرف * k_pch_SteamVR_DisplayDebugX_Int32 = "displayDebugX";
ساکن ثابت حرف * k_pch_SteamVR_DisplayDebugY_Int32 = "displayDebugY";
ساکن ثابت حرف * k_pch_Steam_VR_Send_System_Button_مقصد_All_Apps_Bool = "sendSystemButtonToAllApps";
ساکن ثابت حرف * k_pch_SteamVR_LogLevel_Int32 = "loglevel";
ساکن ثابت حرف * k_pch_SteamVR_IPD_Float = "ipd";
ساکن ثابت حرف * k_pch_SteamVR_Background_String = "background";
ساکن ثابت حرف * k_pch_SteamVR_BackgroundUseDomeProjection_Bool = "backgroundUseDomeProjection";
ساکن ثابت حرف * k_pch_Steam_VR_Background_Camera_اونچائی_Float = "backgroundCameraHeight";
ساکن ثابت حرف * k_pch_SteamVR_BackgroundDomeRadius_Float = "backgroundDomeRadius";
ساکن ثابت حرف * k_pch_SteamVR_GridColor_String = "gridColor";
ساکن ثابت حرف * k_pch_SteamVR_PlayAreaColor_String = "playAreaColor";
ساکن ثابت حرف * k_pch_SteamVR_TrackingLossColor_String = "trackingLossColor";
ساکن ثابت حرف * k_pch_SteamVR_ShowStage_Bool = "showStage";
ساکن ثابت حرف * k_pch_SteamVR_DrawTrackingReferences_Bool = "drawTrackingReferences";
ساکن ثابت حرف * k_pch_Steam_VR_Activate_مضرب_Drivers_Bool = "activateMultipleDrivers";
ساکن ثابت حرف * k_pch_SteamVR_UsingSpeakers_Bool = "usingSpeakers";
ساکن ثابت حرف * k_pch_Steam_VR_Speakers_Forward_Yaw_انحراف_Degrees_Float = "speakersForwardYawOffsetDegrees";
ساکن ثابت حرف * k_pch_Steam_VR_بنیاد_Station_Power_Management_Int32 = "basestationPowerManagement";
ساکن ثابت حرف * k_pch_Steam_VR_Show_بنیاد_Station_Power_Management_Tip_Int32 = "ShowBaseStationPowerManagementTip";
ساکن ثابت حرف * k_pch_SteamVR_NeverKillProcesses_Bool = "neverKillProcesses";
ساکن ثابت حرف * k_pch_SteamVR_SupersampleScale_Float = "supersampleScale";
ساکن ثابت حرف * k_pch_SteamVR_MaxRecommendedResolution_Int32 = "maxRecommendedResolution";
ساکن ثابت حرف * k_pch_SteamVR_MotionSmoothing_Bool = "motionSmoothing";
ساکن ثابت حرف * k_pch_SteamVR_MotionSmoothingOverride_Int32 = "motionSmoothingOverride";
ساکن ثابت حرف * k_pch_Steam_VR_چوکھٹے_مقصد_Throttle_Int32 = "framesToThrottle";
ساکن ثابت حرف * k_pch_Steam_VR_Additional_چوکھٹے_مقصد_Predict_Int32 = "additionalFramesToPredict";
ساکن ثابت حرف * k_pch_SteamVR_WorldScale_Float = "worldScale";
ساکن ثابت حرف * k_pch_SteamVR_FovScale_Int32 = "fovScale";
ساکن ثابت حرف * k_pch_SteamVR_DisableAsyncReprojection_Bool = "disableAsync";
ساکن ثابت حرف * k_pch_SteamVR_ForceFadeOnBadTracking_Bool = "forceFadeOnBadTracking";
ساکن ثابت حرف * k_pch_SteamVR_DefaultMirrorView_Int32 = "mirrorView";
ساکن ثابت حرف * k_pch_SteamVR_ShowLegacyMirrorView_Bool = "showLegacyMirrorView";
ساکن ثابت حرف * k_pch_SteamVR_MirrorViewVisibility_Bool = "showMirrorView";
ساکن ثابت حرف * k_pch_Steam_VR_Mirror_View_Display_منوال_Int32 = "mirrorViewDisplayMode";
ساکن ثابت حرف * k_pch_SteamVR_MirrorViewEye_Int32 = "mirrorViewEye";
ساکن ثابت حرف * k_pch_SteamVR_MirrorViewGeometry_String = "mirrorViewGeometry";
ساکن ثابت حرف * k_pch_SteamVR_MirrorViewGeometryMaximized_String = "mirrorViewGeometryMaximized";
ساکن ثابت حرف * k_pch_Steam_VR_Perf_گراف_Visibility_Bool = "showPerfGraph";
ساکن ثابت حرف * k_pch_Steam_VR_آغاز_Monitor_From_App_Launch = "startMonitorFromAppLaunch";
ساکن ثابت حرف * k_pch_Steam_VR_آغاز_Compositor_From_App_Launch_Bool = "startCompositorFromAppLaunch";
ساکن ثابت حرف * k_pch_Steam_VR_آغاز_Dashboard_From_App_Launch_Bool = "startDashboardFromAppLaunch";
ساکن ثابت حرف * k_pch_Steam_VR_آغاز_Overlay_Apps_From_Dashboard_Bool = "startOverlayAppsFromDashboard";
ساکن ثابت حرف * k_pch_SteamVR_EnableHomeApp = "enableHomeApp";
ساکن ثابت حرف * k_pch_Steam_VR_چکر_Background_Image_وقت_Sec_Int32 = "CycleBackgroundImageTimeSec";
ساکن ثابت حرف * k_pch_SteamVR_RetailDemo_Bool = "retailDemo";
ساکن ثابت حرف * k_pch_Steam_VR_Ipd_انحراف_Float = "ipdOffset";
ساکن ثابت حرف * k_pch_SteamVR_AllowSupersampleFiltering_Bool = "allowSupersampleFiltering";
ساکن ثابت حرف * k_pch_SteamVR_SupersampleManualOverride_Bool = "supersampleManualOverride";
ساکن ثابت حرف * k_pch_SteamVR_EnableLinuxVulkanAsync_Bool = "enableLinuxVulkanAsync";
ساکن ثابت حرف * k_pch_Steam_VR_Allow_Display_Locked_منوال_Bool = "allowDisplayLockedMode";
ساکن ثابت حرف * k_pch_SteamVR_HaveStartedTutorialForNativeChaperoneDriver_Bool = "haveStartedTutorialForNativeChaperoneDriver";
ساکن ثابت حرف * k_pch_SteamVR_ForceWindows32bitVRMonitor = "forceWindows32BitVRMonitor";
ساکن ثابت حرف * k_pch_Steam_VR_Debug_داخلہ_Binding = "debugInputBinding";
ساکن ثابت حرف * k_pch_Steam_VR_Do_Not_Fade_مقصد_Grid = "doNotFadeToGrid";
ساکن ثابت حرف * k_pch_Steam_VR_Render_Camera_منوال = "renderCameraMode";
ساکن ثابت حرف * k_pch_SteamVR_EnableSharedResourceJournaling = "enableSharedResourceJournaling";
ساکن ثابت حرف * k_pch_Steam_VR_Enable_محفوظ_منوال = "enableSafeMode";
ساکن ثابت حرف * k_pch_Steam_VR_Preferred_Refresh_شرح = "preferredRefreshRate";
ساکن ثابت حرف * k_pch_Steam_VR_آخری_نسخہ_Notice = "lastVersionNotice";
ساکن ثابت حرف * k_pch_Steam_VR_آخری_نسخہ_Notice_Date = "lastVersionNoticeDate";
ساکن ثابت حرف * k_pch_SteamVR_HmdDisplayColorGainR_Float = "hmdDisplayColorGainR";
ساکن ثابت حرف * k_pch_SteamVR_HmdDisplayColorGainG_Float = "hmdDisplayColorGainG";
ساکن ثابت حرف * k_pch_SteamVR_HmdDisplayColorGainB_Float = "hmdDisplayColorGainB";
ساکن ثابت حرف * k_pch_SteamVR_CustomIconStyle_String = "customIconStyle";
ساکن ثابت حرف * k_pch_SteamVR_CustomOffIconStyle_String = "customOffIconStyle";
ساکن ثابت حرف * k_pch_SteamVR_CustomIconForceUpdate_String = "customIconForceUpdate";
ساکن ثابت حرف * k_pch_Steam_VR_Allow_Global_Action_سیٹ_ترجیح = "globalActionSetPriority";
ساکن ثابت حرف * k_pch_SteamVR_OverlayRenderQuality = "overlayRenderQuality_2";
ساکن ثابت حرف * k_pch_Steam_VR_بلاک_Oculus_SDKOn_Open_VRLaunch_Option_Bool = "blockOculusSDKOnOpenVRLaunchOption";
ساکن ثابت حرف * k_pch_Steam_VR_بلاک_Oculus_SDKOn_All_Launches_Bool = "blockOculusSDKOnAllLaunches";
ساکن ثابت حرف * k_pch_SteamVR_HDCPLegacyCompatibility_Bool = "hdcp14legacyCompatibility";
ساکن ثابت حرف * k_pch_Steam_VR_Display_پورٹ_Training_منوال_Int = "displayPortTrainingMode";
ساکن ثابت حرف * k_pch_SteamVR_UsePrism_Bool = "usePrism";
ساکن ثابت حرف * k_pch_براہ_راست_منوال_Section = "direct_mode";
ساکن ثابت حرف * k_pch_براہ_راست_منوال_Enable_Bool = "enable";
ساکن ثابت حرف * k_pch_براہ_راست_منوال_گنتی_Int32 = "count";
ساکن ثابت حرف * k_pch_براہ_راست_منوال_Edid_Vid_Int32 = "edidVid";
ساکن ثابت حرف * k_pch_براہ_راست_منوال_Edid_Pid_Int32 = "edidPid";
ساکن ثابت حرف * k_pch_Lighthouse_Section = "driver_lighthouse";
ساکن ثابت حرف * k_pch_Lighthouse_DisableIMU_Bool = "disableimu";
ساکن ثابت حرف * k_pch_Lighthouse_DisableIMUExceptHMD_Bool = "disableimuexcepthmd";
ساکن ثابت حرف * k_pch_Lighthouse_UseDisambiguation_String = "usedisambiguation";
ساکن ثابت حرف * k_pch_Lighthouse_DisambiguationDebug_Int32 = "disambiguationdebug";
ساکن ثابت حرف * k_pch_Lighthouse_PrimaryBasestation_Int32 = "primarybasestation";
ساکن ثابت حرف * k_pch_Lighthouse_DBHistory_Bool = "dbhistory";
ساکن ثابت حرف * k_pch_Lighthouse_EnableBluetooth_Bool = "enableBluetooth";
ساکن ثابت حرف * k_pch_Lighthouse_Power_Managed_بنیاد_Stations_String = "PowerManagedBaseStations";
ساکن ثابت حرف * k_pch_Lighthouse_Power_Managed_بنیاد_Stations2_String = "PowerManagedBaseStations2";
ساکن ثابت حرف * k_pch_Lighthouse_Inactivity_Timeout_For_بنیاد_Stations_Int32 = "InactivityTimeoutForBaseStations";
ساکن ثابت حرف * k_pch_Lighthouse_EnableImuFallback_Bool = "enableImuFallback";
ساکن ثابت حرف * k_pch_Null_Section = "driver_null";
ساکن ثابت حرف * k_pch_Null_Serial_نمبر_String = "serialNumber";
ساکن ثابت حرف * k_pch_Null_Model_نمبر_String = "modelNumber";
ساکن ثابت حرف * k_pch_Null_کھڑکی_X_Int32 = "windowX";
ساکن ثابت حرف * k_pch_Null_کھڑکی_Y_Int32 = "windowY";
ساکن ثابت حرف * k_pch_Null_کھڑکی_چوڑائی_Int32 = "windowWidth";
ساکن ثابت حرف * k_pch_Null_کھڑکی_اونچائی_Int32 = "windowHeight";
ساکن ثابت حرف * k_pch_Null_Render_چوڑائی_Int32 = "renderWidth";
ساکن ثابت حرف * k_pch_Null_Render_اونچائی_Int32 = "renderHeight";
ساکن ثابت حرف * k_pch_Null_Seconds_From_Vsync_مقصد_Photons_Float = "secondsFromVsyncToPhotons";
ساکن ثابت حرف * k_pch_Null_DisplayFrequency_Float = "displayFrequency";
ساکن ثابت حرف * k_pch_WindowsMR_Section = "driver_holographic";
ساکن ثابت حرف * k_pch_UserInterface_Section = "userinterface";
ساکن ثابت حرف * k_pch_User_Interface_حالت_Always_On_چوٹی_Bool = "StatusAlwaysOnTop";
ساکن ثابت حرف * k_pch_User_Interface_Minimize_مقصد_Tray_Bool = "MinimizeToTray";
ساکن ثابت حرف * k_pch_User_Interface_Hide_Popups_When_حالت_Minimized_Bool = "HidePopupsWhenStatusMinimized";
ساکن ثابت حرف * k_pch_UserInterface_Screenshots_Bool = "screenshots";
ساکن ثابت حرف * k_pch_UserInterface_ScreenshotType_Int = "screenshotType";
ساکن ثابت حرف * k_pch_Notifications_Section = "notifications";
ساکن ثابت حرف * k_pch_Notifications_DoNotDisturb_Bool = "DoNotDisturb";
ساکن ثابت حرف * k_pch_Keyboard_Section = "keyboard";
ساکن ثابت حرف * k_pch_Keyboard_TutorialCompletions = "TutorialCompletions";
ساکن ثابت حرف * k_pch_Keyboard_ScaleX = "ScaleX";
ساکن ثابت حرف * k_pch_Keyboard_ScaleY = "ScaleY";
ساکن ثابت حرف * k_pch_Keyboard_انحراف_بایاں_X = "OffsetLeftX";
ساکن ثابت حرف * k_pch_Keyboard_انحراف_دایاں_X = "OffsetRightX";
ساکن ثابت حرف * k_pch_Keyboard_انحراف_Y = "OffsetY";
ساکن ثابت حرف * k_pch_Keyboard_Smoothing = "Smoothing";
ساکن ثابت حرف * k_pch_Perf_Section = "perfcheck";
ساکن ثابت حرف * k_pch_Perf_Perf_گراف_اندر_HMD_Bool = "perfGraphInHMD";
ساکن ثابت حرف * k_pch_Perf_AllowTimingStore_Bool = "allowTimingStore";
ساکن ثابت حرف * k_pch_Perf_SaveTimingsOnExit_Bool = "saveTimingsOnExit";
ساکن ثابت حرف * k_pch_Perf_Test_ڈیٹا_Float = "perfTestData";
ساکن ثابت حرف * k_pch_Perf_GPUProfiling_Bool = "GPUProfiling";
ساکن ثابت حرف * k_pch_CollisionBounds_Section = "collisionBounds";
ساکن ثابت حرف * k_pch_CollisionBounds_Style_Int32 = "CollisionBoundsStyle";
ساکن ثابت حرف * k_pch_CollisionBounds_GroundPerimeterOn_Bool = "CollisionBoundsGroundPerimeterOn";
ساکن ثابت حرف * k_pch_CollisionBounds_CenterMarkerOn_Bool = "CollisionBoundsCenterMarkerOn";
ساکن ثابت حرف * k_pch_CollisionBounds_PlaySpaceOn_Bool = "CollisionBoundsPlaySpaceOn";
ساکن ثابت حرف * k_pch_Collision_Bounds_Fade_فاصلہ_Float = "CollisionBoundsFadeDistance";
ساکن ثابت حرف * k_pch_Collision_Bounds_Wall_اونچائی_Float = "CollisionBoundsWallHeight";
ساکن ثابت حرف * k_pch_CollisionBounds_ColorGammaR_Int32 = "CollisionBoundsColorGammaR";
ساکن ثابت حرف * k_pch_CollisionBounds_ColorGammaG_Int32 = "CollisionBoundsColorGammaG";
ساکن ثابت حرف * k_pch_CollisionBounds_ColorGammaB_Int32 = "CollisionBoundsColorGammaB";
ساکن ثابت حرف * k_pch_CollisionBounds_ColorGammaA_Int32 = "CollisionBoundsColorGammaA";
ساکن ثابت حرف * k_pch_CollisionBounds_EnableDriverImport = "enableDriverBoundsImport";
ساکن ثابت حرف * k_pch_Camera_Section = "camera";
ساکن ثابت حرف * k_pch_Camera_EnableCamera_Bool = "enableCamera";
ساکن ثابت حرف * k_pch_Camera_ShowOnController_Bool = "showOnController";
ساکن ثابت حرف * k_pch_Camera_EnableCameraForCollisionBounds_Bool = "enableCameraForCollisionBounds";
ساکن ثابت حرف * k_pch_Camera_گنجائش_View_Int32 = "roomView";
ساکن ثابت حرف * k_pch_Camera_BoundsColorGammaR_Int32 = "cameraBoundsColorGammaR";
ساکن ثابت حرف * k_pch_Camera_BoundsColorGammaG_Int32 = "cameraBoundsColorGammaG";
ساکن ثابت حرف * k_pch_Camera_BoundsColorGammaB_Int32 = "cameraBoundsColorGammaB";
ساکن ثابت حرف * k_pch_Camera_BoundsColorGammaA_Int32 = "cameraBoundsColorGammaA";
ساکن ثابت حرف * k_pch_Camera_BoundsStrength_Int32 = "cameraBoundsStrength";
ساکن ثابت حرف * k_pch_Camera_گنجائش_View_Style_Int32 = "roomViewStyle";
ساکن ثابت حرف * k_pch_audio_Section = "audio";
ساکن ثابت حرف * k_pch_audio_سیٹ_Os_Default_Playback_Device_Bool = "setOsDefaultPlaybackDevice";
ساکن ثابت حرف * k_pch_audio_EnablePlaybackDeviceOverride_Bool = "enablePlaybackDeviceOverride";
ساکن ثابت حرف * k_pch_audio_PlaybackDeviceOverride_String = "playbackDeviceOverride";
ساکن ثابت حرف * k_pch_audio_PlaybackDeviceOverrideName_String = "playbackDeviceOverrideName";
ساکن ثابت حرف * k_pch_audio_سیٹ_Os_Default_Recording_Device_Bool = "setOsDefaultRecordingDevice";
ساکن ثابت حرف * k_pch_audio_EnableRecordingDeviceOverride_Bool = "enableRecordingDeviceOverride";
ساکن ثابت حرف * k_pch_audio_RecordingDeviceOverride_String = "recordingDeviceOverride";
ساکن ثابت حرف * k_pch_audio_RecordingDeviceOverrideName_String = "recordingDeviceOverrideName";
ساکن ثابت حرف * k_pch_audio_EnablePlaybackMirror_Bool = "enablePlaybackMirror";
ساکن ثابت حرف * k_pch_audio_PlaybackMirrorDevice_String = "playbackMirrorDevice";
ساکن ثابت حرف * k_pch_audio_PlaybackMirrorDeviceName_String = "playbackMirrorDeviceName";
ساکن ثابت حرف * k_pch_audio_OldPlaybackMirrorDevice_String = "onPlaybackMirrorDevice";
ساکن ثابت حرف * k_pch_audio_فعال_Mirror_Device_String = "activePlaybackMirrorDevice";
ساکن ثابت حرف * k_pch_audio_EnablePlaybackMirrorIndependentVolume_Bool = "enablePlaybackMirrorIndependentVolume";
ساکن ثابت حرف * k_pch_audio_آخری_Hmd_Playback_Device_Id_String = "lastHmdPlaybackDeviceId";
ساکن ثابت حرف * k_pch_audio_VIVEHDMIGain = "viveHDMIGain";
ساکن ثابت حرف * k_pch_audio_DualSpeakerAndJackOutput_Bool = "dualSpeakerAndJackOutput";
ساکن ثابت حرف * k_pch_audio_MuteMicMonitor_Bool = "muteMicMonitor";
ساکن ثابت حرف * k_pch_Power_Section = "power";
ساکن ثابت حرف * k_pch_Power_PowerOffOnExit_Bool = "powerOffOnExit";
ساکن ثابت حرف * k_pch_Power_TurnOffScreensTimeout_Float = "turnOffScreensTimeout";
ساکن ثابت حرف * k_pch_Power_TurnOffControllersTimeout_Float = "turnOffControllersTimeout";
ساکن ثابت حرف * k_pch_Power_Return_مقصد_Watchdog_Timeout_Float = "returnToWatchdogTimeout";
ساکن ثابت حرف * k_pch_Power_AutoLaunchSteamVROnButtonPress = "autoLaunchSteamVROnButtonPress";
ساکن ثابت حرف * k_pch_Power_PauseCompositorOnStandby_Bool = "pauseCompositorOnStandby";
ساکن ثابت حرف * k_pch_Dashboard_Section = "dashboard";
ساکن ثابت حرف * k_pch_Dashboard_EnableDashboard_Bool = "enableDashboard";
ساکن ثابت حرف * k_pch_Dashboard_Arcade_منوال_Bool = "arcadeMode";
ساکن ثابت حرف * k_pch_Dashboard_Position = "position";
ساکن ثابت حرف * k_pch_Dashboard_DesktopScale = "desktopScale";
ساکن ثابت حرف * k_pch_Dashboard_DashboardScale = "dashboardScale";
ساکن ثابت حرف * k_pch_Dashboard_UseStandaloneSystemLayer = "standaloneSystemLayer";
ساکن ثابت حرف * k_pch_Dashboard_StickyDashboard = "stickyDashboard";
ساکن ثابت حرف * k_pch_modelskin_Section = "modelskins";
ساکن ثابت حرف * k_pch_Driver_Enable_Bool = "enable";
ساکن ثابت حرف * k_pch_Driver_BlockedBySafemode_Bool = "blocked_by_safe_mode";
ساکن ثابت حرف * k_pch_Driver_بھرو_ترجیح_Int32 = "loadPriority";
ساکن ثابت حرف * k_pch_WebInterface_Section = "WebInterface";
ساکن ثابت حرف * k_pch_VRWebHelper_Section = "VRWebHelper";
ساکن ثابت حرف * k_pch_VRWebHelper_DebuggerEnabled_Bool = "DebuggerEnabled";
ساکن ثابت حرف * k_pch_VRWeb_Helper_Debugger_پورٹ_Int32 = "DebuggerPort";
ساکن ثابت حرف * k_pch_TrackingOverride_Section = "TrackingOverrides";
ساکن ثابت حرف * k_pch_App_BindingAutosaveURLSuffix_String = "AutosaveURL";
ساکن ثابت حرف * k_pch_App_BindingLegacyAPISuffix_String = "_legacy";
ساکن ثابت حرف * k_pch_App_BindingSteamVRInputAPISuffix_String = "_steamvrinput";
ساکن ثابت حرف * k_pch_App_BindingOpenXRAPISuffix_String = "_openxr";
ساکن ثابت حرف * k_pch_App_BindingCurrentURLSuffix_String = "CurrentURL";
ساکن ثابت حرف * k_pch_App_Binding_پچھلا_URLSuffix_String = "PreviousURL";
ساکن ثابت حرف * k_pch_App_Need_مقصد_Update_Autosave_Suffix_Bool = "NeedToUpdateAutosave";
ساکن ثابت حرف * k_pch_App_DominantHand_Int32 = "DominantHand";
ساکن ثابت حرف * k_pch_App_بلاک_Oculus_SDK_Bool = "blockOculusSDK";
ساکن ثابت حرف * k_pch_Trackers_Section = "trackers";
ساکن ثابت حرف * k_pch_DesktopUI_Section = "DesktopUI";
ساکن ثابت حرف * k_pch_آخری_معلوم_Section = "LastKnown";
ساکن ثابت حرف * k_pch_آخری_معلوم_HMDManufacturer_String = "HMDManufacturer";
ساکن ثابت حرف * k_pch_آخری_معلوم_HMDModel_String = "HMDModel";
ساکن ثابت حرف * k_pch_DismissedWarnings_Section = "DismissedWarnings";
ساکن ثابت حرف * k_pch_داخلہ_Section = "input";
ساکن ثابت حرف * k_pch_داخلہ_بایاں_Thumbstick_Rotation_Float = "leftThumbstickRotation";
ساکن ثابت حرف * k_pch_داخلہ_دایاں_Thumbstick_Rotation_Float = "rightThumbstickRotation";
ساکن ثابت حرف * k_pch_داخلہ_Thumbstick_Deadzone_Float = "thumbstickDeadzone";
ساکن ثابت حرف * k_pch_Gpu_رفتار_Section = "GpuSpeed";
ساکن ثابت حرف * IVRScreenshots_نسخہ = "IVRScreenshots_001";
ساکن ثابت حرف * IVRResources_نسخہ = "IVRResources_001";
ساکن ثابت حرف * IVRDriver_Manager_نسخہ = "IVRDriverManager_001";
ساکن ثابت غیرعلامتی طویل k_un_Max_Action_Name_لمبائی = 64;
ساکن ثابت غیرعلامتی طویل k_un_Max_Action_سیٹ_Name_لمبائی = 64;
ساکن ثابت غیرعلامتی طویل k_un_Max_Action_Origin_گنتی = 16;
ساکن ثابت غیرعلامتی طویل k_un_Max_Bone_Name_لمبائی = 32;
ساکن ثابت صحیح k_n_Action_سیٹ_Overlay_Global_ترجیح_Min = 16777216;
ساکن ثابت صحیح k_n_Action_سیٹ_Overlay_Global_ترجیح_Max = 33554431;
ساکن ثابت صحیح k_n_Action_سیٹ_ترجیح_Reserved_Min = 33554432;
ساکن ثابت حرف * IVRInput_نسخہ = "IVRInput_010";
ساکن ثابت غیرعلامتی طویل طویل k_ulInvalidIOBufferHandle = 0;
ساکن ثابت حرف * IVRIOBuffer_نسخہ = "IVRIOBuffer_002";
ساکن ثابت غیرعلامتی طویل k_ulInvalidSpatialAnchorHandle = 0;
ساکن ثابت حرف * IVRSpatial_Anchors_نسخہ = "IVRSpatialAnchors_001";
ساکن ثابت حرف * IVRDebug_نسخہ = "IVRDebug_001";
ساکن ثابت غیرعلامتی طویل طویل k_ulDisplayRedirectContainer = 25769803779;
ساکن ثابت حرف * IVRProperties_نسخہ = "IVRProperties_001";
ساکن ثابت حرف * k_pch_راستہ_User_Hand_دایاں = "/user/hand/right";
ساکن ثابت حرف * k_pch_راستہ_User_Hand_بایاں = "/user/hand/left";
ساکن ثابت حرف * k_pch_راستہ_User_Hand_Primary = "/user/hand/primary";
ساکن ثابت حرف * k_pch_راستہ_User_Hand_Secondary = "/user/hand/secondary";
ساکن ثابت حرف * k_pch_راستہ_User_سر = "/user/head";
ساکن ثابت حرف * k_pch_راستہ_User_Gamepad = "/user/gamepad";
ساکن ثابت حرف * k_pch_راستہ_User_Treadmill = "/user/treadmill";
ساکن ثابت حرف * k_pch_راستہ_User_Stylus = "/user/stylus";
ساکن ثابت حرف * k_pch_راستہ_Devices = "/devices";
ساکن ثابت حرف * k_pch_راستہ_Device_راستہ = "/device_path";
ساکن ثابت حرف * k_pch_راستہ_بہترین_Alias_راستہ = "/best_alias_path";
ساکن ثابت حرف * k_pch_راستہ_Bound_Tracker_Alias_راستہ = "/bound_tracker_path";
ساکن ثابت حرف * k_pch_راستہ_Bound_Tracker_Role = "/bound_tracker_role";
ساکن ثابت حرف * k_pch_راستہ_Pose_Raw = "/pose/raw";
ساکن ثابت حرف * k_pch_راستہ_Pose_Tip = "/pose/tip";
ساکن ثابت حرف * k_pch_راستہ_Pose_Grip = "/pose/grip";
ساکن ثابت حرف * k_pch_راستہ_System_Button_Click = "/input/system/click";
ساکن ثابت حرف * k_pch_راستہ_Proximity = "/proximity";
ساکن ثابت حرف * k_pch_راستہ_Controller_Type_سابقہ = "/controller_type/";
ساکن ثابت حرف * k_pch_راستہ_داخلہ_Profile_Suffix = "/input_profile";
ساکن ثابت حرف * k_pch_راستہ_Binding_Name_Suffix = "/binding_name";
ساکن ثابت حرف * k_pch_راستہ_Binding_Url_Suffix = "/binding_url";
ساکن ثابت حرف * k_pch_راستہ_Binding_Error_Suffix = "/binding_error";
ساکن ثابت حرف * k_pch_راستہ_فعال_Action_Sets = "/active_action_sets";
ساکن ثابت حرف * k_pch_راستہ_Component_Updates = "/total_component_updates";
ساکن ثابت حرف * k_pch_راستہ_User_Foot_بایاں = "/user/foot/left";
ساکن ثابت حرف * k_pch_راستہ_User_Foot_دایاں = "/user/foot/right";
ساکن ثابت حرف * k_pch_راستہ_User_Shoulder_بایاں = "/user/shoulder/left";
ساکن ثابت حرف * k_pch_راستہ_User_Shoulder_دایاں = "/user/shoulder/right";
ساکن ثابت حرف * k_pch_راستہ_User_Elbow_بایاں = "/user/elbow/left";
ساکن ثابت حرف * k_pch_راستہ_User_Elbow_دایاں = "/user/elbow/right";
ساکن ثابت حرف * k_pch_راستہ_User_Knee_بایاں = "/user/knee/left";
ساکن ثابت حرف * k_pch_راستہ_User_Knee_دایاں = "/user/knee/right";
ساکن ثابت حرف * k_pch_راستہ_User_Waist = "/user/waist";
ساکن ثابت حرف * k_pch_راستہ_User_Chest = "/user/chest";
ساکن ثابت حرف * k_pch_راستہ_User_Camera = "/user/camera";
ساکن ثابت حرف * k_pch_راستہ_User_Keyboard = "/user/keyboard";
ساکن ثابت حرف * k_pch_راستہ_Client_App_کلید = "/client_info/app_key";
ساکن ثابت غیرعلامتی طویل طویل k_ul_Invalid_راستہ_Handle = 0;
ساکن ثابت حرف * IVRPaths_نسخہ = "IVRPaths_001";
ساکن ثابت حرف * IVRBlock_قطار_نسخہ = "IVRBlockQueue_005";

// OpenVR Enums

قسمتعریف شمار EVREye
{
	EVREye_Eye_بایاں = 0,
	EVREye_Eye_دایاں = 1,
} EVREye;

قسمتعریف شمار ETextureType
{
	ETextureType_TextureType_Invalid = -1,
	ETexture_Type_Texture_Type_براہ_راست_X = 0,
	ETextureType_TextureType_OpenGL = 1,
	ETextureType_TextureType_Vulkan = 2,
	ETextureType_TextureType_IOSurface = 3,
	ETexture_Type_Texture_Type_براہ_راست_X12 = 4,
	ETextureType_TextureType_DXGISharedHandle = 5,
	ETextureType_TextureType_Metal = 6,
} ETextureType;

قسمتعریف شمار EColorSpace
{
	EColorSpace_ColorSpace_Auto = 0,
	EColorSpace_ColorSpace_Gamma = 1,
	EColor_Space_Color_Space_خطی = 2,
} EColorSpace;

قسمتعریف شمار ETracking_نتیجہ
{
	ETracking_نتیجہ_Tracking_نتیجہ_Uninitialized = 1,
	ETracking_نتیجہ_Tracking_نتیجہ_Calibrating_اندر_پیش_رفت = 100,
	ETracking_نتیجہ_Tracking_نتیجہ_Calibrating_برآمد_کا_Range = 101,
	ETracking_نتیجہ_Tracking_نتیجہ_Running_OK = 200,
	ETracking_نتیجہ_Tracking_نتیجہ_Running_برآمد_کا_Range = 201,
	ETracking_نتیجہ_Tracking_نتیجہ_Fallback_Rotation_Only = 300,
} ETracking_نتیجہ;

قسمتعریف شمار ETrackedDeviceClass
{
	ETrackedDeviceClass_TrackedDeviceClass_Invalid = 0,
	ETrackedDeviceClass_TrackedDeviceClass_HMD = 1,
	ETrackedDeviceClass_TrackedDeviceClass_Controller = 2,
	ETrackedDeviceClass_TrackedDeviceClass_GenericTracker = 3,
	ETrackedDeviceClass_TrackedDeviceClass_TrackingReference = 4,
	ETrackedDeviceClass_TrackedDeviceClass_DisplayRedirect = 5,
	ETrackedDeviceClass_TrackedDeviceClass_Max = 6,
} ETrackedDeviceClass;

قسمتعریف شمار ETrackedControllerRole
{
	ETrackedControllerRole_TrackedControllerRole_Invalid = 0,
	ETracked_Controller_Role_Tracked_Controller_Role_بایاں_Hand = 1,
	ETracked_Controller_Role_Tracked_Controller_Role_دایاں_Hand = 2,
	ETracked_Controller_Role_Tracked_Controller_Role_Opt_برآمد = 3,
	ETrackedControllerRole_TrackedControllerRole_Treadmill = 4,
	ETrackedControllerRole_TrackedControllerRole_Stylus = 5,
	ETrackedControllerRole_TrackedControllerRole_Max = 5,
} ETrackedControllerRole;

قسمتعریف شمار ETrackingUniverseOrigin
{
	ETrackingUniverseOrigin_TrackingUniverseSeated = 0,
	ETrackingUniverseOrigin_TrackingUniverseStanding = 1,
	ETrackingUniverseOrigin_TrackingUniverseRawAndUncalibrated = 2,
} ETrackingUniverseOrigin;

قسمتعریف شمار EAdditionalRadioFeatures
{
	EAdditionalRadioFeatures_AdditionalRadioFeatures_None = 0,
	EAdditionalRadioFeatures_AdditionalRadioFeatures_HTCLinkBox = 1,
	EAdditional_Radio_Features_Additional_Radio_Features_اندرونی_Dongle = 2,
	EAdditionalRadioFeatures_AdditionalRadioFeatures_ExternalDongle = 4,
} EAdditionalRadioFeatures;

قسمتعریف شمار ETrackedDeviceProperty
{
	ETrackedDeviceProperty_Prop_Invalid = 0,
	ETrackedDeviceProperty_Prop_TrackingSystemName_String = 1000,
	ETracked_Device_Property_Prop_Model_نمبر_String = 1001,
	ETracked_Device_Property_Prop_Serial_نمبر_String = 1002,
	ETrackedDeviceProperty_Prop_RenderModelName_String = 1003,
	ETracked_Device_Property_Prop_Will_Drift_اندر_Yaw_Bool = 1004,
	ETrackedDeviceProperty_Prop_ManufacturerName_String = 1005,
	ETracked_Device_Property_Prop_Tracking_Firmware_نسخہ_String = 1006,
	ETrackedDeviceProperty_Prop_HardwareRevision_String = 1007,
	ETrackedDeviceProperty_Prop_AllWirelessDongleDescriptions_String = 1008,
	ETrackedDeviceProperty_Prop_ConnectedWirelessDongle_String = 1009,
	ETrackedDeviceProperty_Prop_DeviceIsWireless_Bool = 1010,
	ETrackedDeviceProperty_Prop_DeviceIsCharging_Bool = 1011,
	ETrackedDeviceProperty_Prop_DeviceBatteryPercentage_Float = 1012,
	ETracked_Device_Property_Prop_حالت_Display_Transform_Matrix34 = 1013,
	ETracked_Device_Property_Prop_Firmware_Update_دستیاب_Bool = 1014,
	ETrackedDeviceProperty_Prop_Firmware_ManualUpdate_Bool = 1015,
	ETrackedDeviceProperty_Prop_Firmware_ManualUpdateURL_String = 1016,
	ETrackedDeviceProperty_Prop_HardwareRevision_Uint64 = 1017,
	ETracked_Device_Property_Prop_Firmware_نسخہ_Uint64 = 1018,
	ETrackedDeviceProperty_Prop_FPGAVersion_Uint64 = 1019,
	ETrackedDeviceProperty_Prop_VRCVersion_Uint64 = 1020,
	ETracked_Device_Property_Prop_Radio_نسخہ_Uint64 = 1021,
	ETracked_Device_Property_Prop_Dongle_نسخہ_Uint64 = 1022,
	ETracked_Device_Property_Prop_بلاک_Server_Shutdown_Bool = 1023,
	ETrackedDeviceProperty_Prop_CanUnifyCoordinateSystemWithHmd_Bool = 1024,
	ETracked_Device_Property_Prop_شامل_ہے_Proximity_Sensor_Bool = 1025,
	ETracked_Device_Property_Prop_Device_Provides_Battery_حالت_Bool = 1026,
	ETrackedDeviceProperty_Prop_DeviceCanPowerOff_Bool = 1027,
	ETracked_Device_Property_Prop_Firmware_Programming_ہدف_String = 1028,
	ETrackedDeviceProperty_Prop_DeviceClass_Int32 = 1029,
	ETrackedDeviceProperty_Prop_HasCamera_Bool = 1030,
	ETracked_Device_Property_Prop_Driver_نسخہ_String = 1031,
	ETrackedDeviceProperty_Prop_Firmware_ForceUpdateRequired_Bool = 1032,
	ETrackedDeviceProperty_Prop_ViveSystemButtonFixRequired_Bool = 1033,
	ETracked_Device_Property_Prop_والد_Driver_Uint64 = 1034,
	ETracked_Device_Property_Prop_Resource_جڑ_String = 1035,
	ETrackedDeviceProperty_Prop_RegisteredDeviceType_String = 1036,
	ETracked_Device_Property_Prop_داخلہ_Profile_راستہ_String = 1037,
	ETrackedDeviceProperty_Prop_NeverTracked_Bool = 1038,
	ETracked_Device_Property_Prop_عدد_Cameras_Int32 = 1039,
	ETracked_Device_Property_Prop_Camera_چوکھٹا_Layout_Int32 = 1040,
	ETracked_Device_Property_Prop_Camera_دھارا_Format_Int32 = 1041,
	ETracked_Device_Property_Prop_Additional_Device_Settings_راستہ_String = 1042,
	ETrackedDeviceProperty_Prop_Identifiable_Bool = 1043,
	ETracked_Device_Property_Prop_Bootloader_نسخہ_Uint64 = 1044,
	ETracked_Device_Property_Prop_Additional_System_Report_ڈیٹا_String = 1045,
	ETracked_Device_Property_Prop_مرکب_Firmware_نسخہ_String = 1046,
	ETrackedDeviceProperty_Prop_Firmware_RemindUpdate_Bool = 1047,
	ETracked_Device_Property_Prop_Peripheral_Application_نسخہ_Uint64 = 1048,
	ETracked_Device_Property_Prop_Manufacturer_Serial_نمبر_String = 1049,
	ETracked_Device_Property_Prop_Computed_Serial_نمبر_String = 1050,
	ETracked_Device_Property_Prop_Estimated_Device_پہلا_Use_وقت_Int32 = 1051,
	ETrackedDeviceProperty_Prop_DevicePowerUsage_Float = 1052,
	ETrackedDeviceProperty_Prop_IgnoreMotionForStandby_Bool = 1053,
	ETracked_Device_Property_Prop_Reports_وقت_Since_VSync_Bool = 2000,
	ETracked_Device_Property_Prop_Seconds_From_Vsync_مقصد_Photons_Float = 2001,
	ETrackedDeviceProperty_Prop_DisplayFrequency_Float = 2002,
	ETrackedDeviceProperty_Prop_UserIpdMeters_Float = 2003,
	ETrackedDeviceProperty_Prop_CurrentUniverseId_Uint64 = 2004,
	ETracked_Device_Property_Prop_پچھلا_Universe_Id_Uint64 = 2005,
	ETracked_Device_Property_Prop_Display_Firmware_نسخہ_Uint64 = 2006,
	ETrackedDeviceProperty_Prop_IsOnDesktop_Bool = 2007,
	ETrackedDeviceProperty_Prop_DisplayMCType_Int32 = 2008,
	ETrackedDeviceProperty_Prop_DisplayMCOffset_Float = 2009,
	ETrackedDeviceProperty_Prop_DisplayMCScale_Float = 2010,
	ETrackedDeviceProperty_Prop_EdidVendorID_Int32 = 2011,
	ETracked_Device_Property_Prop_Display_MCImage_بایاں_String = 2012,
	ETracked_Device_Property_Prop_Display_MCImage_دایاں_String = 2013,
	ETrackedDeviceProperty_Prop_DisplayGCBlackClamp_Float = 2014,
	ETracked_Device_Property_Prop_Edid_حاصل_ضرب_ID_Int32 = 2015,
	ETracked_Device_Property_Prop_Camera_مقصد_سر_Transform_Matrix34 = 2016,
	ETrackedDeviceProperty_Prop_DisplayGCType_Int32 = 2017,
	ETrackedDeviceProperty_Prop_DisplayGCOffset_Float = 2018,
	ETrackedDeviceProperty_Prop_DisplayGCScale_Float = 2019,
	ETrackedDeviceProperty_Prop_DisplayGCPrescale_Float = 2020,
	ETrackedDeviceProperty_Prop_DisplayGCImage_String = 2021,
	ETracked_Device_Property_Prop_Lens_Center_بایاں_U_Float = 2022,
	ETracked_Device_Property_Prop_Lens_Center_بایاں_V_Float = 2023,
	ETracked_Device_Property_Prop_Lens_Center_دایاں_U_Float = 2024,
	ETracked_Device_Property_Prop_Lens_Center_دایاں_V_Float = 2025,
	ETracked_Device_Property_Prop_User_سر_مقصد_Eye_گہرائی_Meters_Float = 2026,
	ETracked_Device_Property_Prop_Camera_Firmware_نسخہ_Uint64 = 2027,
	ETrackedDeviceProperty_Prop_CameraFirmwareDescription_String = 2028,
	ETrackedDeviceProperty_Prop_DisplayFPGAVersion_Uint64 = 2029,
	ETracked_Device_Property_Prop_Display_Bootloader_نسخہ_Uint64 = 2030,
	ETracked_Device_Property_Prop_Display_Hardware_نسخہ_Uint64 = 2031,
	ETracked_Device_Property_Prop_Audio_Firmware_نسخہ_Uint64 = 2032,
	ETracked_Device_Property_Prop_Camera_Compatibility_منوال_Int32 = 2033,
	ETracked_Device_Property_Prop_Screenshot_Horizontal_میدان_کا_View_Degrees_Float = 2034,
	ETracked_Device_Property_Prop_Screenshot_Vertical_میدان_کا_View_Degrees_Float = 2035,
	ETrackedDeviceProperty_Prop_DisplaySuppressed_Bool = 2036,
	ETracked_Device_Property_Prop_Display_Allow_Night_منوال_Bool = 2037,
	ETracked_Device_Property_Prop_Display_MCImage_چوڑائی_Int32 = 2038,
	ETracked_Device_Property_Prop_Display_MCImage_اونچائی_Int32 = 2039,
	ETracked_Device_Property_Prop_Display_MCImage_عدد_Channels_Int32 = 2040,
	ETracked_Device_Property_Prop_Display_MCImage_ڈیٹا_ثنائی = 2041,
	ETracked_Device_Property_Prop_Seconds_From_Photons_مقصد_Vblank_Float = 2042,
	ETracked_Device_Property_Prop_Driver_براہ_راست_منوال_Sends_Vsync_Events_Bool = 2043,
	ETracked_Device_Property_Prop_Display_Debug_منوال_Bool = 2044,
	ETrackedDeviceProperty_Prop_GraphicsAdapterLuid_Uint64 = 2045,
	ETracked_Device_Property_Prop_Driver_Provided_Chaperone_راستہ_String = 2048,
	ETracked_Device_Property_Prop_Expected_Tracking_Reference_گنتی_Int32 = 2049,
	ETracked_Device_Property_Prop_Expected_Controller_گنتی_Int32 = 2050,
	ETracked_Device_Property_Prop_Named_Icon_راستہ_Controller_بایاں_Device_Off_String = 2051,
	ETracked_Device_Property_Prop_Named_Icon_راستہ_Controller_دایاں_Device_Off_String = 2052,
	ETracked_Device_Property_Prop_Named_Icon_راستہ_Tracking_Reference_Device_Off_String = 2053,
	ETrackedDeviceProperty_Prop_DoNotApplyPrediction_Bool = 2054,
	ETracked_Device_Property_Prop_Camera_مقصد_سر_Transforms_Matrix34_Array = 2055,
	ETrackedDeviceProperty_Prop_DistortionMeshResolution_Int32 = 2056,
	ETrackedDeviceProperty_Prop_DriverIsDrawingControllers_Bool = 2057,
	ETracked_Device_Property_Prop_Driver_درخواستیں_Application_Pause_Bool = 2058,
	ETracked_Device_Property_Prop_Driver_درخواستیں_Reduced_Rendering_Bool = 2059,
	ETracked_Device_Property_Prop_Minimum_Ipd_قدم_Meters_Float = 2060,
	ETracked_Device_Property_Prop_Audio_Bridge_Firmware_نسخہ_Uint64 = 2061,
	ETracked_Device_Property_Prop_Image_Bridge_Firmware_نسخہ_Uint64 = 2062,
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
	ETracked_Device_Property_Prop_Hmd_عمود_Correction_Setting_سابقہ_String = 2077,
	ETrackedDeviceProperty_Prop_CameraSupportsCompatibilityModes_Bool = 2078,
	ETracked_Device_Property_Prop_Supports_گنجائش_View_گہرائی_Projection_Bool = 2079,
	ETracked_Device_Property_Prop_Display_دستیاب_چوکھٹا_Rates_Float_Array = 2080,
	ETracked_Device_Property_Prop_Display_Supports_مضرب_Framerates_Bool = 2081,
	ETracked_Device_Property_Prop_Display_Color_Mult_بایاں_Vector3 = 2082,
	ETracked_Device_Property_Prop_Display_Color_Mult_دایاں_Vector3 = 2083,
	ETrackedDeviceProperty_Prop_DisplaySupportsRuntimeFramerateChange_Bool = 2084,
	ETrackedDeviceProperty_Prop_DisplaySupportsAnalogGain_Bool = 2085,
	ETrackedDeviceProperty_Prop_DisplayMinAnalogGain_Float = 2086,
	ETrackedDeviceProperty_Prop_DisplayMaxAnalogGain_Float = 2087,
	ETracked_Device_Property_Prop_Camera_Exposure_وقت_Float = 2088,
	ETrackedDeviceProperty_Prop_CameraGlobalGain_Float = 2089,
	ETrackedDeviceProperty_Prop_DashboardScale_Float = 2091,
	ETrackedDeviceProperty_Prop_PeerButtonInfo_String = 2092,
	ETrackedDeviceProperty_Prop_Hmd_SupportsHDR10_Bool = 2093,
	ETrackedDeviceProperty_Prop_IpdUIRangeMinMeters_Float = 2100,
	ETrackedDeviceProperty_Prop_IpdUIRangeMaxMeters_Float = 2101,
	ETrackedDeviceProperty_Prop_Hmd_SupportsHDCP14LegacyCompat_Bool = 2102,
	ETrackedDeviceProperty_Prop_Hmd_SupportsMicMonitoring_Bool = 2103,
	ETracked_Device_Property_Prop_Hmd_Supports_Display_پورٹ_Training_منوال_Bool = 2104,
	ETracked_Device_Property_Prop_Supports_گنجائش_View_براہ_راست_Bool = 2105,
	ETrackedDeviceProperty_Prop_SupportsAppThrottling_Bool = 2106,
	ETrackedDeviceProperty_Prop_DSCVersion_Int32 = 2110,
	ETracked_Device_Property_Prop_DSCSlice_گنتی_Int32 = 2111,
	ETrackedDeviceProperty_Prop_DSCBPPx16_Int32 = 2112,
	ETracked_Device_Property_Prop_Driver_Requested_Mura_Correction_منوال_Int32 = 2200,
	ETracked_Device_Property_Prop_Driver_Requested_Mura_Feather_Inner_بایاں_Int32 = 2201,
	ETracked_Device_Property_Prop_Driver_Requested_Mura_Feather_Inner_دایاں_Int32 = 2202,
	ETracked_Device_Property_Prop_Driver_Requested_Mura_Feather_Inner_چوٹی_Int32 = 2203,
	ETrackedDeviceProperty_Prop_DriverRequestedMuraFeather_InnerBottom_Int32 = 2204,
	ETracked_Device_Property_Prop_Driver_Requested_Mura_Feather_Outer_بایاں_Int32 = 2205,
	ETracked_Device_Property_Prop_Driver_Requested_Mura_Feather_Outer_دایاں_Int32 = 2206,
	ETracked_Device_Property_Prop_Driver_Requested_Mura_Feather_Outer_چوٹی_Int32 = 2207,
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
	ETracked_Device_Property_Prop_میدان_کا_View_بایاں_Degrees_Float = 4000,
	ETracked_Device_Property_Prop_میدان_کا_View_دایاں_Degrees_Float = 4001,
	ETracked_Device_Property_Prop_میدان_کا_View_چوٹی_Degrees_Float = 4002,
	ETracked_Device_Property_Prop_میدان_کا_View_Bottom_Degrees_Float = 4003,
	ETrackedDeviceProperty_Prop_TrackingRangeMinimumMeters_Float = 4004,
	ETracked_Device_Property_Prop_Tracking_Range_زیادہ_سے_زیادہ_Meters_Float = 4005,
	ETracked_Device_Property_Prop_منوال_Label_String = 4006,
	ETrackedDeviceProperty_Prop_CanWirelessIdentify_Bool = 4007,
	ETrackedDeviceProperty_Prop_Nonce_Int32 = 4008,
	ETracked_Device_Property_Prop_Icon_راستہ_Name_String = 5000,
	ETracked_Device_Property_Prop_Named_Icon_راستہ_Device_Off_String = 5001,
	ETracked_Device_Property_Prop_Named_Icon_راستہ_Device_Searching_String = 5002,
	ETracked_Device_Property_Prop_Named_Icon_راستہ_Device_Searching_Alert_String = 5003,
	ETracked_Device_Property_Prop_Named_Icon_راستہ_Device_Ready_String = 5004,
	ETracked_Device_Property_Prop_Named_Icon_راستہ_Device_Ready_Alert_String = 5005,
	ETracked_Device_Property_Prop_Named_Icon_راستہ_Device_Not_Ready_String = 5006,
	ETracked_Device_Property_Prop_Named_Icon_راستہ_Device_Standby_String = 5007,
	ETracked_Device_Property_Prop_Named_Icon_راستہ_Device_Alert_کم_String = 5008,
	ETracked_Device_Property_Prop_Named_Icon_راستہ_Device_Standby_Alert_String = 5009,
	ETracked_Device_Property_Prop_Display_Hidden_Area_ثنائی_آغاز = 5100,
	ETracked_Device_Property_Prop_Display_Hidden_Area_ثنائی_انتہا = 5150,
	ETracked_Device_Property_Prop_والد_Container = 5151,
	ETrackedDeviceProperty_Prop_OverrideContainer_Uint64 = 5152,
	ETracked_Device_Property_Prop_User_Config_راستہ_String = 6000,
	ETracked_Device_Property_Prop_Install_راستہ_String = 6001,
	ETrackedDeviceProperty_Prop_HasDisplayComponent_Bool = 6002,
	ETrackedDeviceProperty_Prop_HasControllerComponent_Bool = 6003,
	ETrackedDeviceProperty_Prop_HasCameraComponent_Bool = 6004,
	ETracked_Device_Property_Prop_Has_Driver_براہ_راست_منوال_Component_Bool = 6005,
	ETrackedDeviceProperty_Prop_HasVirtualDisplayComponent_Bool = 6006,
	ETrackedDeviceProperty_Prop_HasSpatialAnchorsSupport_Bool = 6007,
	ETrackedDeviceProperty_Prop_ControllerType_String = 7000,
	ETracked_Device_Property_Prop_Controller_Hand_Selection_ترجیح_Int32 = 7002,
	ETracked_Device_Property_Prop_Vendor_Specific_Reserved_آغاز = 10000,
	ETracked_Device_Property_Prop_Vendor_Specific_Reserved_انتہا = 10999,
	ETrackedDeviceProperty_Prop_TrackedDeviceProperty_Max = 1000000,
} ETrackedDeviceProperty;

قسمتعریف شمار ETrackedPropertyError
{
	ETrackedPropertyError_TrackedProp_Success = 0,
	ETracked_Property_Error_Tracked_Prop_Wrong_ڈیٹا_Type = 1,
	ETrackedPropertyError_TrackedProp_WrongDeviceClass = 2,
	ETracked_Property_Error_Tracked_Prop_بفر_Too_Small = 3,
	ETrackedPropertyError_TrackedProp_UnknownProperty = 4,
	ETrackedPropertyError_TrackedProp_InvalidDevice = 5,
	ETrackedPropertyError_TrackedProp_CouldNotContactServer = 6,
	ETracked_Property_Error_Tracked_Prop_قدر_Not_Provided_By_Device = 7,
	ETracked_Property_Error_Tracked_Prop_String_Exceeds_زیادہ_سے_زیادہ_لمبائی = 8,
	ETracked_Property_Error_Tracked_Prop_Not_Yet_دستیاب = 9,
	ETrackedPropertyError_TrackedProp_PermissionDenied = 10,
	ETrackedPropertyError_TrackedProp_InvalidOperation = 11,
	ETracked_Property_Error_Tracked_Prop_Cannot_Write_مقصد_Wildcards = 12,
	ETrackedPropertyError_TrackedProp_IPCReadFailure = 13,
	ETracked_Property_Error_Tracked_Prop_برآمد_کا_حافظہ = 14,
	ETrackedPropertyError_TrackedProp_InvalidContainer = 15,
} ETrackedPropertyError;

قسمتعریف شمار EHmdTrackingStyle
{
	EHmdTrackingStyle_HmdTrackingStyle_Unknown = 0,
	EHmdTrackingStyle_HmdTrackingStyle_Lighthouse = 1,
	EHmd_Tracking_Style_Hmd_Tracking_Style_Outside_اندر_Cameras = 2,
	EHmd_Tracking_Style_Hmd_Tracking_Style_Inside_برآمد_Cameras = 3,
} EHmdTrackingStyle;

قسمتعریف شمار EVRSubmitFlags
{
	EVRSubmitFlags_Submit_Default = 0,
	EVRSubmitFlags_Submit_LensDistortionAlreadyApplied = 1,
	EVRSubmit_Flags_Submit_Gl_Render_بفر = 2,
	EVRSubmitFlags_Submit_Reserved = 4,
	EVRSubmitFlags_Submit_TextureWithPose = 8,
	EVRSubmit_Flags_Submit_Texture_With_گہرائی = 16,
	EVRSubmit_Flags_Submit_چوکھٹا_Discontinuty = 32,
	EVRSubmit_Flags_Submit_Vulkan_Texture_With_Array_ڈیٹا = 64,
	EVRSubmitFlags_Submit_GlArrayTexture = 128,
	EVRSubmitFlags_Submit_Reserved2 = 32768,
	EVRSubmitFlags_Submit_Reserved3 = 65536,
} EVRSubmitFlags;

قسمتعریف شمار EVRState
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

قسمتعریف شمار EVREventType
{
	EVREventType_VREvent_None = 0,
	EVREventType_VREvent_TrackedDeviceActivated = 100,
	EVREventType_VREvent_TrackedDeviceDeactivated = 101,
	EVREventType_VREvent_TrackedDeviceUpdated = 102,
	EVREventType_VREvent_TrackedDeviceUserInteractionStarted = 103,
	EVREventType_VREvent_TrackedDeviceUserInteractionEnded = 104,
	EVREvent_Type_VREvent_Ipd_بدلا = 105,
	EVREvent_Type_VREvent_Enter_Standby_منوال = 106,
	EVREvent_Type_VREvent_Leave_Standby_منوال = 107,
	EVREvent_Type_VREvent_Tracked_Device_Role_بدلا = 108,
	EVREvent_Type_VREvent_Watchdog_Wake_اوپر_Requested = 109,
	EVREvent_Type_VREvent_Lens_Distortion_بدلا = 110,
	EVREvent_Type_VREvent_Property_بدلا = 111,
	EVREventType_VREvent_WirelessDisconnect = 112,
	EVREventType_VREvent_WirelessReconnect = 113,
	EVREventType_VREvent_ButtonPress = 200,
	EVREventType_VREvent_ButtonUnpress = 201,
	EVREventType_VREvent_ButtonTouch = 202,
	EVREventType_VREvent_ButtonUntouch = 203,
	EVREventType_VREvent_Modal_Cancel = 257,
	EVREventType_VREvent_MouseMove = 300,
	EVREvent_Type_VREvent_Mouse_Button_نیچے_کو = 301,
	EVREvent_Type_VREvent_Mouse_Button_اوپر = 302,
	EVREventType_VREvent_FocusEnter = 303,
	EVREventType_VREvent_FocusLeave = 304,
	EVREventType_VREvent_ScrollDiscrete = 305,
	EVREventType_VREvent_TouchPadMove = 306,
	EVREvent_Type_VREvent_Overlay_Focus_بدلا = 307,
	EVREventType_VREvent_ReloadOverlays = 308,
	EVREventType_VREvent_ScrollSmooth = 309,
	EVREvent_Type_VREvent_تالا_Mouse_Position = 310,
	EVREventType_VREvent_UnlockMousePosition = 311,
	EVREvent_Type_VREvent_داخلہ_Focus_Captured = 400,
	EVREvent_Type_VREvent_داخلہ_Focus_Released = 401,
	EVREvent_Type_VREvent_Scene_Application_بدلا = 404,
	EVREvent_Type_VREvent_داخلہ_Focus_بدلا = 406,
	EVREventType_VREvent_SceneApplicationUsingWrongGraphicsAdapter = 408,
	EVREventType_VREvent_ActionBindingReloaded = 409,
	EVREventType_VREvent_HideRenderModels = 410,
	EVREventType_VREvent_ShowRenderModels = 411,
	EVREvent_Type_VREvent_Scene_Application_State_بدلا = 412,
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
	EVREvent_Type_VREvent_Overlay_Gamepad_Focus_گمشدہ = 512,
	EVREvent_Type_VREvent_Overlay_Shared_Texture_بدلا = 513,
	EVREventType_VREvent_ScreenshotTriggered = 516,
	EVREventType_VREvent_ImageFailed = 517,
	EVREventType_VREvent_DashboardOverlayCreated = 518,
	EVREventType_VREvent_SwitchGamepadFocus = 519,
	EVREventType_VREvent_RequestScreenshot = 520,
	EVREvent_Type_VREvent_Screenshot_لیا_گیا = 521,
	EVREventType_VREvent_ScreenshotFailed = 522,
	EVREvent_Type_VREvent_Submit_Screenshot_مقصد_Dashboard = 523,
	EVREvent_Type_VREvent_Screenshot_پیش_رفت_مقصد_Dashboard = 524,
	EVREvent_Type_VREvent_Primary_Dashboard_Device_بدلا = 525,
	EVREvent_Type_VREvent_گنجائش_View_Shown = 526,
	EVREvent_Type_VREvent_گنجائش_View_Hidden = 527,
	EVREventType_VREvent_ShowUI = 528,
	EVREventType_VREvent_ShowDevTools = 529,
	EVREventType_VREvent_DesktopViewUpdating = 530,
	EVREventType_VREvent_DesktopViewReady = 531,
	EVREvent_Type_VREvent_آغاز_Dashboard = 532,
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
	EVREvent_Type_VREvent_Invalidate_تبادلہ_Texture_Sets = 706,
	EVREvent_Type_VREvent_Chaperone_ڈیٹا_Has_بدلا = 800,
	EVREvent_Type_VREvent_Chaperone_Universe_Has_بدلا = 801,
	EVREvent_Type_VREvent_Chaperone_عارضی_ڈیٹا_Has_بدلا = 802,
	EVREvent_Type_VREvent_Chaperone_Settings_Have_بدلا = 803,
	EVREventType_VREvent_SeatedZeroPoseReset = 804,
	EVREventType_VREvent_ChaperoneFlushCache = 805,
	EVREvent_Type_VREvent_Chaperone_گنجائش_تیاری_Starting = 806,
	EVREvent_Type_VREvent_Chaperone_گنجائش_تیاری_ختم_شدہ = 807,
	EVREventType_VREvent_StandingZeroPoseReset = 808,
	EVREvent_Type_VREvent_Audio_Settings_Have_بدلا = 820,
	EVREvent_Type_VREvent_Background_Setting_Has_بدلا = 850,
	EVREvent_Type_VREvent_Camera_Settings_Have_بدلا = 851,
	EVREvent_Type_VREvent_Reprojection_Setting_Has_بدلا = 852,
	EVREvent_Type_VREvent_Model_Skin_Settings_Have_بدلا = 853,
	EVREvent_Type_VREvent_Environment_Settings_Have_بدلا = 854,
	EVREvent_Type_VREvent_Power_Settings_Have_بدلا = 855,
	EVREvent_Type_VREvent_Enable_Home_App_Settings_Have_بدلا = 856,
	EVREvent_Type_VREvent_Steam_VRSection_Setting_بدلا = 857,
	EVREvent_Type_VREvent_Lighthouse_Section_Setting_بدلا = 858,
	EVREvent_Type_VREvent_Null_Section_Setting_بدلا = 859,
	EVREvent_Type_VREvent_User_Interface_Section_Setting_بدلا = 860,
	EVREvent_Type_VREvent_Notifications_Section_Setting_بدلا = 861,
	EVREvent_Type_VREvent_Keyboard_Section_Setting_بدلا = 862,
	EVREvent_Type_VREvent_Perf_Section_Setting_بدلا = 863,
	EVREvent_Type_VREvent_Dashboard_Section_Setting_بدلا = 864,
	EVREvent_Type_VREvent_Web_Interface_Section_Setting_بدلا = 865,
	EVREvent_Type_VREvent_Trackers_Section_Setting_بدلا = 866,
	EVREvent_Type_VREvent_آخری_معلوم_Section_Setting_بدلا = 867,
	EVREvent_Type_VREvent_Dismissed_Warnings_Section_Setting_بدلا = 868,
	EVREvent_Type_VREvent_Gpu_رفتار_Section_Setting_بدلا = 869,
	EVREvent_Type_VREvent_Windows_MRSection_Setting_بدلا = 870,
	EVREvent_Type_VREvent_Other_Section_Setting_بدلا = 871,
	EVREvent_Type_VREvent_حالت_Update = 900,
	EVREventType_VREvent_WebInterface_InstallDriverCompleted = 950,
	EVREventType_VREvent_MCImageUpdated = 1000,
	EVREventType_VREvent_FirmwareUpdateStarted = 1100,
	EVREvent_Type_VREvent_Firmware_Update_ختم_شدہ = 1101,
	EVREventType_VREvent_KeyboardClosed = 1200,
	EVREvent_Type_VREvent_Keyboard_Char_داخلہ = 1201,
	EVREvent_Type_VREvent_Keyboard_مکمل = 1202,
	EVREventType_VREvent_ApplicationListUpdated = 1303,
	EVREvent_Type_VREvent_Application_Mime_Type_بھرو = 1304,
	EVREventType_VREvent_ProcessConnected = 1306,
	EVREventType_VREvent_ProcessDisconnected = 1307,
	EVREventType_VREvent_Compositor_ChaperoneBoundsShown = 1410,
	EVREventType_VREvent_Compositor_ChaperoneBoundsHidden = 1411,
	EVREventType_VREvent_Compositor_DisplayDisconnected = 1412,
	EVREventType_VREvent_Compositor_DisplayReconnected = 1413,
	EVREventType_VREvent_Compositor_HDCPError = 1414,
	EVREventType_VREvent_Compositor_ApplicationNotResponding = 1415,
	EVREventType_VREvent_Compositor_ApplicationResumed = 1416,
	EVREvent_Type_VREvent_Compositor_برآمد_کا_Video_حافظہ = 1417,
	EVREvent_Type_VREvent_Compositor_Display_منوال_Not_Supported = 1418,
	EVREventType_VREvent_Compositor_StageOverrideReady = 1419,
	EVREventType_VREvent_Compositor_RequestDisconnectReconnect = 1420,
	EVREvent_Type_VREvent_Tracked_Camera_آغاز_Video_دھارا = 1500,
	EVREvent_Type_VREvent_Tracked_Camera_Stop_Video_دھارا = 1501,
	EVREvent_Type_VREvent_Tracked_Camera_Pause_Video_دھارا = 1502,
	EVREvent_Type_VREvent_Tracked_Camera_Resume_Video_دھارا = 1503,
	EVREventType_VREvent_TrackedCamera_EditingSurface = 1550,
	EVREventType_VREvent_PerformanceTest_EnableCapture = 1600,
	EVREventType_VREvent_PerformanceTest_DisableCapture = 1601,
	EVREventType_VREvent_PerformanceTest_FidelityLevel = 1602,
	EVREvent_Type_VREvent_پیغام_Overlay_Closed = 1650,
	EVREvent_Type_VREvent_پیغام_Overlay_Close_Requested = 1651,
	EVREvent_Type_VREvent_داخلہ_Haptic_Vibration = 1700,
	EVREvent_Type_VREvent_داخلہ_Binding_بھرو_Failed = 1701,
	EVREvent_Type_VREvent_داخلہ_Binding_بھرو_Successful = 1702,
	EVREvent_Type_VREvent_داخلہ_Action_Manifest_Reloaded = 1703,
	EVREvent_Type_VREvent_داخلہ_Action_Manifest_بھرو_Failed = 1704,
	EVREvent_Type_VREvent_داخلہ_پیش_رفت_Update = 1705,
	EVREvent_Type_VREvent_داخلہ_Tracker_Activated = 1706,
	EVREvent_Type_VREvent_داخلہ_Bindings_Updated = 1707,
	EVREvent_Type_VREvent_داخلہ_Binding_Subscription_بدلا = 1708,
	EVREventType_VREvent_SpatialAnchors_PoseUpdated = 1800,
	EVREventType_VREvent_SpatialAnchors_DescriptorUpdated = 1801,
	EVREventType_VREvent_SpatialAnchors_RequestPoseUpdate = 1802,
	EVREventType_VREvent_SpatialAnchors_RequestDescriptorUpdate = 1803,
	EVREventType_VREvent_SystemReport_Started = 1900,
	EVREventType_VREvent_Monitor_ShowHeadsetView = 2000,
	EVREventType_VREvent_Monitor_HideHeadsetView = 2001,
	EVREvent_Type_VREvent_Vendor_Specific_Reserved_آغاز = 10000,
	EVREvent_Type_VREvent_Vendor_Specific_Reserved_انتہا = 19999,
} EVREventType;

قسمتعریف شمار EDeviceActivityLevel
{
	EDeviceActivityLevel_k_EDeviceActivityLevel_Unknown = -1,
	EDeviceActivityLevel_k_EDeviceActivityLevel_Idle = 0,
	EDeviceActivityLevel_k_EDeviceActivityLevel_UserInteraction = 1,
	EDeviceActivityLevel_k_EDeviceActivityLevel_UserInteraction_Timeout = 2,
	EDeviceActivityLevel_k_EDeviceActivityLevel_Standby = 3,
	EDeviceActivityLevel_k_EDeviceActivityLevel_Idle_Timeout = 4,
} EDeviceActivityLevel;

قسمتعریف شمار EVRButtonId
{
	EVRButtonId_k_EButton_System = 0,
	EVRButtonId_k_EButton_ApplicationMenu = 1,
	EVRButtonId_k_EButton_Grip = 2,
	EVRButton_Id_k_EButton_DPad_بایاں = 3,
	EVRButton_Id_k_EButton_DPad_اوپر = 4,
	EVRButton_Id_k_EButton_DPad_دایاں = 5,
	EVRButton_Id_k_EButton_DPad_نیچے_کو = 6,
	EVRButtonId_k_EButton_A = 7,
	EVRButtonId_k_EButton_ProximitySensor = 31,
	EVRButtonId_k_EButton_Axis0 = 32,
	EVRButtonId_k_EButton_Axis1 = 33,
	EVRButtonId_k_EButton_Axis2 = 34,
	EVRButtonId_k_EButton_Axis3 = 35,
	EVRButtonId_k_EButton_Axis4 = 36,
	EVRButtonId_k_EButton_SteamVR_Touchpad = 32,
	EVRButtonId_k_EButton_SteamVR_Trigger = 33,
	EVRButton_Id_k_EButton_Dashboard_عقب = 2,
	EVRButton_Id_k_EButton_اشاریہ_Controller_A = 2,
	EVRButton_Id_k_EButton_اشاریہ_Controller_B = 1,
	EVRButton_Id_k_EButton_اشاریہ_Controller_Joy_Stick = 35,
	EVRButtonId_k_EButton_Max = 64,
} EVRButtonId;

قسمتعریف شمار EVRMouseButton
{
	EVRMouse_Button_VRMouse_Button_بایاں = 1,
	EVRMouse_Button_VRMouse_Button_دایاں = 2,
	EVRMouse_Button_VRMouse_Button_درمیان = 4,
} EVRMouseButton;

قسمتعریف شمار EShowUIType
{
	EShowUIType_ShowUI_ControllerBinding = 0,
	EShowUIType_ShowUI_ManageTrackers = 1,
	EShowUIType_ShowUI_Pairing = 3,
	EShowUIType_ShowUI_Settings = 4,
	EShowUIType_ShowUI_DebugCommands = 5,
	EShow_UIType_Show_UI_بھرا_Controller_Binding = 6,
	EShowUIType_ShowUI_ManageDrivers = 7,
} EShowUIType;

قسمتعریف شمار EHDCPError
{
	EHDCPError_HDCPError_None = 0,
	EHDCPError_HDCPError_Link_گمشدہ = 1,
	EHDCPError_HDCPError_Tampered = 2,
	EHDCPError_HDCPError_DeviceRevoked = 3,
	EHDCPError_HDCPError_Unknown = 4,
} EHDCPError;

قسمتعریف شمار EVRComponentProperty
{
	EVRComponentProperty_VRComponentProperty_IsStatic = 1,
	EVRComponentProperty_VRComponentProperty_IsVisible = 2,
	EVRComponentProperty_VRComponentProperty_IsTouched = 4,
	EVRComponentProperty_VRComponentProperty_IsPressed = 8,
	EVRComponentProperty_VRComponentProperty_IsScrolled = 16,
	EVRComponentProperty_VRComponentProperty_IsHighlighted = 32,
} EVRComponentProperty;

قسمتعریف شمار EVRInputError
{
	EVRInputError_VRInputError_None = 0,
	EVRInput_Error_VRInput_Error_Name_Not_ملا = 1,
	EVRInputError_VRInputError_WrongType = 2,
	EVRInputError_VRInputError_InvalidHandle = 3,
	EVRInputError_VRInputError_InvalidParam = 4,
	EVRInputError_VRInputError_NoSteam = 5,
	EVRInput_Error_VRInput_Error_Max_استعداد_Reached = 6,
	EVRInputError_VRInputError_IPCError = 7,
	EVRInput_Error_VRInput_Error_No_فعال_Action_سیٹ = 8,
	EVRInputError_VRInputError_InvalidDevice = 9,
	EVRInputError_VRInputError_InvalidSkeleton = 10,
	EVRInput_Error_VRInput_Error_Invalid_Bone_گنتی = 11,
	EVRInput_Error_VRInput_Error_Invalid_Compressed_ڈیٹا = 12,
	EVRInput_Error_VRInput_Error_No_ڈیٹا = 13,
	EVRInput_Error_VRInput_Error_بفر_Too_Small = 14,
	EVRInputError_VRInputError_MismatchedActionManifest = 15,
	EVRInput_Error_VRInput_Error_Missing_Skeleton_ڈیٹا = 16,
	EVRInput_Error_VRInput_Error_Invalid_Bone_اشاریہ = 17,
	EVRInput_Error_VRInput_Error_Invalid_ترجیح = 18,
	EVRInputError_VRInputError_PermissionDenied = 19,
	EVRInputError_VRInputError_InvalidRenderModel = 20,
} EVRInputError;

قسمتعریف شمار EVRSpatialAnchorError
{
	EVRSpatialAnchorError_VRSpatialAnchorError_Success = 0,
	EVRSpatial_Anchor_Error_VRSpatial_Anchor_Error_اندرونی = 1,
	EVRSpatialAnchorError_VRSpatialAnchorError_UnknownHandle = 2,
	EVRSpatialAnchorError_VRSpatialAnchorError_ArrayTooSmall = 3,
	EVRSpatialAnchorError_VRSpatialAnchorError_InvalidDescriptorChar = 4,
	EVRSpatial_Anchor_Error_VRSpatial_Anchor_Error_Not_Yet_دستیاب = 5,
	EVRSpatial_Anchor_Error_VRSpatial_Anchor_Error_Not_دستیاب_اندر_This_Universe = 6,
	EVRSpatialAnchorError_VRSpatialAnchorError_PermanentlyUnavailable = 7,
	EVRSpatialAnchorError_VRSpatialAnchorError_WrongDriver = 8,
	EVRSpatialAnchorError_VRSpatialAnchorError_DescriptorTooLong = 9,
	EVRSpatialAnchorError_VRSpatialAnchorError_Unknown = 10,
	EVRSpatial_Anchor_Error_VRSpatial_Anchor_Error_No_گنجائش_Calibration = 11,
	EVRSpatial_Anchor_Error_VRSpatial_Anchor_Error_Invalid_دلیل = 12,
	EVRSpatialAnchorError_VRSpatialAnchorError_UnknownDriver = 13,
} EVRSpatialAnchorError;

قسمتعریف شمار EHiddenAreaMeshType
{
	EHiddenAreaMeshType_k_eHiddenAreaMesh_Standard = 0,
	EHiddenAreaMeshType_k_eHiddenAreaMesh_Inverse = 1,
	EHidden_Area_Mesh_Type_k_e_Hidden_Area_Mesh_سطر_Loop = 2,
	EHiddenAreaMeshType_k_eHiddenAreaMesh_Max = 3,
} EHiddenAreaMeshType;

قسمتعریف شمار EVRControllerAxisType
{
	EVRControllerAxisType_k_eControllerAxis_None = 0,
	EVRControllerAxisType_k_eControllerAxis_TrackPad = 1,
	EVRControllerAxisType_k_eControllerAxis_Joystick = 2,
	EVRControllerAxisType_k_eControllerAxis_Trigger = 3,
} EVRControllerAxisType;

قسمتعریف شمار EVRControllerEventOutputType
{
	EVRControllerEventOutputType_ControllerEventOutput_OSEvents = 0,
	EVRControllerEventOutputType_ControllerEventOutput_VREvents = 1,
} EVRControllerEventOutputType;

قسمتعریف شمار ECollisionBoundsStyle
{
	ECollisionBoundsStyle_COLLISION_BOUNDS_STYLE_BEGINNER = 0,
	ECollisionBoundsStyle_COLLISION_BOUNDS_STYLE_INTERMEDIATE = 1,
	ECollisionBoundsStyle_COLLISION_BOUNDS_STYLE_SQUARES = 2,
	ECollisionBoundsStyle_COLLISION_BOUNDS_STYLE_ADVANCED = 3,
	ECollisionBoundsStyle_COLLISION_BOUNDS_STYLE_NONE = 4,
	ECollision_Bounds_Style_COLLISION_BOUNDS_STYLE_گنتی = 5,
} ECollisionBoundsStyle;

قسمتعریف شمار EVROverlayError
{
	EVROverlayError_VROverlayError_None = 0,
	EVROverlayError_VROverlayError_UnknownOverlay = 10,
	EVROverlayError_VROverlayError_InvalidHandle = 11,
	EVROverlayError_VROverlayError_PermissionDenied = 12,
	EVROverlay_Error_VROverlay_Error_Overlay_حد_بندی_Exceeded = 13,
	EVROverlayError_VROverlayError_WrongVisibilityType = 14,
	EVROverlay_Error_VROverlay_Error_کلید_Too_Long = 15,
	EVROverlayError_VROverlayError_NameTooLong = 16,
	EVROverlay_Error_VROverlay_Error_کلید_اندر_Use = 17,
	EVROverlayError_VROverlayError_WrongTransformType = 18,
	EVROverlayError_VROverlayError_InvalidTrackedDevice = 19,
	EVROverlayError_VROverlayError_InvalidParameter = 20,
	EVROverlayError_VROverlayError_ThumbnailCantBeDestroyed = 21,
	EVROverlayError_VROverlayError_ArrayTooSmall = 22,
	EVROverlayError_VROverlayError_RequestFailed = 23,
	EVROverlayError_VROverlayError_InvalidTexture = 24,
	EVROverlay_Error_VROverlay_Error_Unable_مقصد_بھرو_File = 25,
	EVROverlay_Error_VROverlay_Error_Keyboard_Already_اندر_Use = 26,
	EVROverlayError_VROverlayError_NoNeighbor = 27,
	EVROverlay_Error_VROverlay_Error_Too_Many_نقاب_Primitives = 29,
	EVROverlay_Error_VROverlay_Error_Bad_نقاب_Primitive = 30,
	EVROverlayError_VROverlayError_TextureAlreadyLocked = 31,
	EVROverlay_Error_VROverlay_Error_Texture_تالا_استعداد_Reached = 32,
	EVROverlayError_VROverlayError_TextureNotLocked = 33,
	EVROverlay_Error_VROverlay_Error_Timed_برآمد = 34,
} EVROverlayError;

قسمتعریف شمار EVRApplicationType
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
	EVRApplication_Type_VRApplication_گنجائش_View = 13,
	EVRApplicationType_VRApplication_Max = 14,
} EVRApplicationType;

قسمتعریف شمار EVRFirmwareError
{
	EVRFirmwareError_VRFirmwareError_None = 0,
	EVRFirmwareError_VRFirmwareError_Success = 1,
	EVRFirmwareError_VRFirmwareError_Fail = 2,
} EVRFirmwareError;

قسمتعریف شمار EVRNotificationError
{
	EVRNotificationError_VRNotificationError_OK = 0,
	EVRNotificationError_VRNotificationError_InvalidNotificationId = 100,
	EVRNotification_Error_VRNotification_Error_Notification_قطار_بھرا = 101,
	EVRNotificationError_VRNotificationError_InvalidOverlayHandle = 102,
	EVRNotification_Error_VRNotification_Error_System_With_User_قدر_Already_Exists = 103,
} EVRNotificationError;

قسمتعریف شمار EVRSkeletalMotionRange
{
	EVRSkeletalMotionRange_VRSkeletalMotionRange_WithController = 0,
	EVRSkeletalMotionRange_VRSkeletalMotionRange_WithoutController = 1,
} EVRSkeletalMotionRange;

قسمتعریف شمار EVRSkeletalTrackingLevel
{
	EVRSkeletalTrackingLevel_VRSkeletalTracking_Estimated = 0,
	EVRSkeletalTrackingLevel_VRSkeletalTracking_Partial = 1,
	EVRSkeletal_Tracking_Level_VRSkeletal_Tracking_بھرا = 2,
	EVRSkeletal_Tracking_Level_VRSkeletal_Tracking_Level_گنتی = 3,
	EVRSkeletalTrackingLevel_VRSkeletalTrackingLevel_Max = 2,
} EVRSkeletalTrackingLevel;

قسمتعریف شمار EVRInitError
{
	EVRInitError_VRInitError_None = 0,
	EVRInitError_VRInitError_Unknown = 1,
	EVRInit_Error_VRInit_Error_Init_Installation_Not_ملا = 100,
	EVRInitError_VRInitError_Init_InstallationCorrupt = 101,
	EVRInit_Error_VRInit_Error_Init_VRClient_DLLNot_ملا = 102,
	EVRInit_Error_VRInit_Error_Init_File_Not_ملا = 103,
	EVRInit_Error_VRInit_Error_Init_Factory_Not_ملا = 104,
	EVRInit_Error_VRInit_Error_Init_Interface_Not_ملا = 105,
	EVRInitError_VRInitError_Init_InvalidInterface = 106,
	EVRInitError_VRInitError_Init_UserConfigDirectoryInvalid = 107,
	EVRInit_Error_VRInit_Error_Init_Hmd_Not_ملا = 108,
	EVRInitError_VRInitError_Init_NotInitialized = 109,
	EVRInit_Error_VRInit_Error_Init_راستہ_Registry_Not_ملا = 110,
	EVRInit_Error_VRInit_Error_Init_No_Config_راستہ = 111,
	EVRInit_Error_VRInit_Error_Init_No_Log_راستہ = 112,
	EVRInit_Error_VRInit_Error_Init_راستہ_Registry_Not_Writable = 113,
	EVRInitError_VRInitError_Init_AppInfoInitFailed = 114,
	EVRInitError_VRInitError_Init_Retry = 115,
	EVRInitError_VRInitError_Init_InitCanceledByUser = 116,
	EVRInitError_VRInitError_Init_AnotherAppLaunching = 117,
	EVRInitError_VRInitError_Init_SettingsInitFailed = 118,
	EVRInit_Error_VRInit_Error_Init_Shutting_نیچے_کو = 119,
	EVRInitError_VRInitError_Init_TooManyObjects = 120,
	EVRInitError_VRInitError_Init_NoServerForBackgroundApp = 121,
	EVRInitError_VRInitError_Init_NotSupportedWithCompositor = 122,
	EVRInit_Error_VRInit_Error_Init_Not_دستیاب_مقصد_Utility_Apps = 123,
	EVRInit_Error_VRInit_Error_Init_اندرونی = 124,
	EVRInitError_VRInitError_Init_HmdDriverIdIsNone = 125,
	EVRInit_Error_VRInit_Error_Init_Hmd_Not_ملا_Presence_Failed = 126,
	EVRInit_Error_VRInit_Error_Init_VRMonitor_Not_ملا = 127,
	EVRInitError_VRInitError_Init_VRMonitorStartupFailed = 128,
	EVRInit_Error_VRInit_Error_Init_کم_Power_Watchdog_Not_Supported = 129,
	EVRInitError_VRInitError_Init_InvalidApplicationType = 130,
	EVRInit_Error_VRInit_Error_Init_Not_دستیاب_مقصد_Watchdog_Apps = 131,
	EVRInit_Error_VRInit_Error_Init_Watchdog_Disabled_اندر_Settings = 132,
	EVRInit_Error_VRInit_Error_Init_VRDashboard_Not_ملا = 133,
	EVRInitError_VRInitError_Init_VRDashboardStartupFailed = 134,
	EVRInit_Error_VRInit_Error_Init_VRHome_Not_ملا = 135,
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
	EVRInit_Error_VRInit_Error_Init_Prism_Startup_Timed_برآمد = 152,
	EVRInit_Error_VRInit_Error_Init_Could_Not_آغاز_Prism = 153,
	EVRInitError_VRInitError_Init_PrismClientInitFailed = 154,
	EVRInit_Error_VRInit_Error_Init_Prism_Client_آغاز_Failed = 155,
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
	EVRInit_Error_VRInit_Error_Init_VRDashboard_راستہ_Failure = 167,
	EVRInitError_VRInitError_Driver_Failed = 200,
	EVRInitError_VRInitError_Driver_Unknown = 201,
	EVRInitError_VRInitError_Driver_HmdUnknown = 202,
	EVRInitError_VRInitError_Driver_NotLoaded = 203,
	EVRInit_Error_VRInit_Error_Driver_Runtime_برآمد_کا_Date = 204,
	EVRInit_Error_VRInit_Error_Driver_Hmd_اندر_Use = 205,
	EVRInitError_VRInitError_Driver_NotCalibrated = 206,
	EVRInitError_VRInitError_Driver_CalibrationInvalid = 207,
	EVRInit_Error_VRInit_Error_Driver_Hmd_Display_Not_ملا = 208,
	EVRInitError_VRInitError_Driver_TrackedDeviceInterfaceUnknown = 209,
	EVRInit_Error_VRInit_Error_Driver_Hmd_Driver_Id_برآمد_کا_Bounds = 211,
	EVRInitError_VRInitError_Driver_HmdDisplayMirrored = 212,
	EVRInit_Error_VRInit_Error_Driver_Hmd_Display_Not_ملا_Laptop = 213,
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
	EVRInit_Error_VRInit_Error_IPC_Connect_Failed_After_ہدف_Exited = 309,
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
	EVRInit_Error_VRInit_Error_Compositor_پیغام_Overlay_Shared_State_Init_Failure = 409,
	EVRInitError_VRInitError_Compositor_PropertiesInterfaceIsNull = 410,
	EVRInit_Error_VRInit_Error_Compositor_Create_Fullscreen_کھڑکی_Failed = 411,
	EVRInitError_VRInitError_Compositor_SettingsInterfaceIsNull = 412,
	EVRInit_Error_VRInit_Error_Compositor_Failed_مقصد_Show_کھڑکی = 413,
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
	EVRInit_Error_VRInit_Error_Compositor_Failed_مقصد_ڈھونڈو_Display_منوال = 425,
	EVRInit_Error_VRInit_Error_Compositor_Failed_مقصد_Create_تبادلہ_Chain = 426,
	EVRInit_Error_VRInit_Error_Compositor_Failed_مقصد_Get_عقب_بفر = 427,
	EVRInit_Error_VRInit_Error_Compositor_Failed_مقصد_Create_Render_ہدف = 428,
	EVRInit_Error_VRInit_Error_Compositor_Failed_مقصد_Create_DXGI2_تبادلہ_Chain = 429,
	EVRInit_Error_VRInit_Error_Compositor_Failedto_Get_DXGI2_عقب_بفر = 430,
	EVRInit_Error_VRInit_Error_Compositor_Failed_مقصد_Create_DXGI2_Render_ہدف = 431,
	EVRInit_Error_VRInit_Error_Compositor_Failed_مقصد_Get_DXGIDevice_Interface = 432,
	EVRInit_Error_VRInit_Error_Compositor_Select_Display_منوال = 433,
	EVRInit_Error_VRInit_Error_Compositor_Failed_مقصد_Create_Nv_APIRender_Targets = 434,
	EVRInit_Error_VRInit_Error_Compositor_Nv_APISet_Display_منوال = 435,
	EVRInit_Error_VRInit_Error_Compositor_Failed_مقصد_Create_براہ_راست_منوال_Display = 436,
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
	EVRInit_Error_VRInit_Error_Compositor_Create_Blend_State_نقاب_R = 450,
	EVRInit_Error_VRInit_Error_Compositor_Create_Blend_State_نقاب_G = 451,
	EVRInit_Error_VRInit_Error_Compositor_Create_Blend_State_نقاب_B = 452,
	EVRInit_Error_VRInit_Error_Compositor_Create_گہرائی_Stencil_State = 453,
	EVRInit_Error_VRInit_Error_Compositor_Create_گہرائی_Stencil_State_No_Write = 454,
	EVRInit_Error_VRInit_Error_Compositor_Create_گہرائی_Stencil_State_No_گہرائی = 455,
	EVRInitError_VRInitError_Compositor_CreateFlushTexture = 456,
	EVRInitError_VRInitError_Compositor_CreateDistortionSurfaces = 457,
	EVRInit_Error_VRInit_Error_Compositor_Create_Constant_بفر = 458,
	EVRInit_Error_VRInit_Error_Compositor_Create_Hmd_Pose_Constant_بفر = 459,
	EVRInit_Error_VRInit_Error_Compositor_Create_Hmd_Pose_Staging_Constant_بفر = 460,
	EVRInit_Error_VRInit_Error_Compositor_Create_Shared_چوکھٹا_Info_Constant_بفر = 461,
	EVRInit_Error_VRInit_Error_Compositor_Create_Overlay_Constant_بفر = 462,
	EVRInit_Error_VRInit_Error_Compositor_Create_Scene_Texture_اشاریہ_Constant_بفر = 463,
	EVRInit_Error_VRInit_Error_Compositor_Create_Readable_Scene_Texture_اشاریہ_Constant_بفر = 464,
	EVRInit_Error_VRInit_Error_Compositor_Create_Layer_Graphics_Texture_اشاریہ_Constant_بفر = 465,
	EVRInit_Error_VRInit_Error_Compositor_Create_Layer_Compute_Texture_اشاریہ_Constant_بفر = 466,
	EVRInit_Error_VRInit_Error_Compositor_Create_Layer_Compute_Scene_Texture_اشاریہ_Constant_بفر = 467,
	EVRInit_Error_VRInit_Error_Compositor_Create_Compute_Hmd_Pose_Constant_بفر = 468,
	EVRInit_Error_VRInit_Error_Compositor_Create_Geom_Constant_بفر = 469,
	EVRInit_Error_VRInit_Error_Compositor_Create_Panel_نقاب_Constant_بفر = 470,
	EVRInitError_VRInitError_Compositor_CreatePixelSimUBO = 471,
	EVRInitError_VRInitError_Compositor_CreateMSAARenderTextures = 472,
	EVRInitError_VRInitError_Compositor_CreateResolveRenderTextures = 473,
	EVRInitError_VRInitError_Compositor_CreateComputeResolveRenderTextures = 474,
	EVRInit_Error_VRInit_Error_Compositor_Create_Driver_براہ_راست_منوال_Resolve_Textures = 475,
	EVRInit_Error_VRInit_Error_Compositor_Open_Driver_براہ_راست_منوال_Resolve_Textures = 476,
	EVRInitError_VRInitError_Compositor_CreateFallbackSyncTexture = 477,
	EVRInitError_VRInitError_Compositor_ShareFallbackSyncTexture = 478,
	EVRInit_Error_VRInit_Error_Compositor_Create_Overlay_اشاریہ_بفر = 479,
	EVRInit_Error_VRInit_Error_Compositor_Create_Overlay_راس_بفر = 480,
	EVRInit_Error_VRInit_Error_Compositor_Create_متن_راس_بفر = 481,
	EVRInit_Error_VRInit_Error_Compositor_Create_متن_اشاریہ_بفر = 482,
	EVRInitError_VRInitError_Compositor_CreateMirrorTextures = 483,
	EVRInit_Error_VRInit_Error_Compositor_Create_آخری_چوکھٹا_Render_Texture = 484,
	EVRInitError_VRInitError_Compositor_CreateMirrorOverlay = 485,
	EVRInit_Error_VRInit_Error_Compositor_Failed_مقصد_Create_Virtual_Display_Backbuffer = 486,
	EVRInit_Error_VRInit_Error_Compositor_Display_منوال_Not_Supported = 487,
	EVRInitError_VRInitError_Compositor_CreateOverlayInvalidCall = 488,
	EVRInitError_VRInitError_Compositor_CreateOverlayAlreadyInitialized = 489,
	EVRInit_Error_VRInit_Error_Compositor_Failed_مقصد_Create_Mailbox = 490,
	EVRInit_Error_VRInit_Error_Compositor_کھڑکی_Interface_Is_Null = 491,
	EVRInitError_VRInitError_Compositor_SystemLayerCreateInstance = 492,
	EVRInitError_VRInitError_Compositor_SystemLayerCreateSession = 493,
	EVRInitError_VRInitError_Compoistor_CreateInverseDistortUVs = 494,
	EVRInit_Error_VRInit_Error_Compoistor_Create_Backbuffer_گہرائی = 495,
	EVRInit_Error_VRInit_Error_Vendor_Specific_Unable_مقصد_Connect_مقصد_Oculus_Runtime = 1000,
	EVRInit_Error_VRInit_Error_Vendor_Specific_Windows_Not_اندر_Dev_منوال = 1001,
	EVRInitError_VRInitError_VendorSpecific_OculusLinkNotEnabled = 1002,
	EVRInit_Error_VRInit_Error_Vendor_Specific_Hmd_ملا_Cant_Open_Device = 1101,
	EVRInit_Error_VRInit_Error_Vendor_Specific_Hmd_ملا_Unable_مقصد_Request_Config_آغاز = 1102,
	EVRInit_Error_VRInit_Error_Vendor_Specific_Hmd_ملا_No_Stored_Config = 1103,
	EVRInit_Error_VRInit_Error_Vendor_Specific_Hmd_ملا_Config_Too_Big = 1104,
	EVRInit_Error_VRInit_Error_Vendor_Specific_Hmd_ملا_Config_Too_Small = 1105,
	EVRInit_Error_VRInit_Error_Vendor_Specific_Hmd_ملا_Unable_مقصد_Init_ZLib = 1106,
	EVRInit_Error_VRInit_Error_Vendor_Specific_Hmd_ملا_Cant_Read_Firmware_نسخہ = 1107,
	EVRInit_Error_VRInit_Error_Vendor_Specific_Hmd_ملا_Unable_مقصد_Send_User_ڈیٹا_آغاز = 1108,
	EVRInit_Error_VRInit_Error_Vendor_Specific_Hmd_ملا_Unable_مقصد_Get_User_ڈیٹا_آغاز = 1109,
	EVRInit_Error_VRInit_Error_Vendor_Specific_Hmd_ملا_Unable_مقصد_Get_User_ڈیٹا_اگلا = 1110,
	EVRInit_Error_VRInit_Error_Vendor_Specific_Hmd_ملا_User_ڈیٹا_پتہ_Range = 1111,
	EVRInit_Error_VRInit_Error_Vendor_Specific_Hmd_ملا_User_ڈیٹا_Error = 1112,
	EVRInit_Error_VRInit_Error_Vendor_Specific_Hmd_ملا_Config_Failed_Sanity_Check = 1113,
	EVRInitError_VRInitError_VendorSpecific_OculusRuntimeBadInstall = 1114,
	EVRInit_Error_VRInit_Error_Vendor_Specific_Hmd_ملا_Unexpected_Configuration_1 = 1115,
	EVRInit_Error_VRInit_Error_Steam_Steam_Installation_Not_ملا = 2000,
	EVRInit_Error_VRInit_Error_آخری_Error = 2001,
} EVRInitError;

قسمتعریف شمار EVRScreenshotType
{
	EVRScreenshotType_VRScreenshotType_None = 0,
	EVRScreenshotType_VRScreenshotType_Mono = 1,
	EVRScreenshotType_VRScreenshotType_Stereo = 2,
	EVRScreenshotType_VRScreenshotType_Cubemap = 3,
	EVRScreenshotType_VRScreenshotType_MonoPanorama = 4,
	EVRScreenshotType_VRScreenshotType_StereoPanorama = 5,
} EVRScreenshotType;

قسمتعریف شمار EVRScreenshotPropertyFilenames
{
	EVRScreenshotPropertyFilenames_VRScreenshotPropertyFilenames_Preview = 0,
	EVRScreenshotPropertyFilenames_VRScreenshotPropertyFilenames_VR = 1,
} EVRScreenshotPropertyFilenames;

قسمتعریف شمار EVRTrackedCameraError
{
	EVRTrackedCameraError_VRTrackedCameraError_None = 0,
	EVRTrackedCameraError_VRTrackedCameraError_OperationFailed = 100,
	EVRTrackedCameraError_VRTrackedCameraError_InvalidHandle = 101,
	EVRTracked_Camera_Error_VRTracked_Camera_Error_Invalid_چوکھٹا_سرخی_نسخہ = 102,
	EVRTracked_Camera_Error_VRTracked_Camera_Error_برآمد_کا_Handles = 103,
	EVRTrackedCameraError_VRTrackedCameraError_IPCFailure = 104,
	EVRTrackedCameraError_VRTrackedCameraError_NotSupportedForThisDevice = 105,
	EVRTracked_Camera_Error_VRTracked_Camera_Error_Shared_حافظہ_Failure = 106,
	EVRTracked_Camera_Error_VRTracked_Camera_Error_چوکھٹا_Buffering_Failure = 107,
	EVRTracked_Camera_Error_VRTracked_Camera_Error_دھارا_تیاری_Failure = 108,
	EVRTrackedCameraError_VRTrackedCameraError_InvalidGLTextureId = 109,
	EVRTrackedCameraError_VRTrackedCameraError_InvalidSharedTextureHandle = 110,
	EVRTracked_Camera_Error_VRTracked_Camera_Error_Failed_مقصد_Get_GLTexture_Id = 111,
	EVRTrackedCameraError_VRTrackedCameraError_SharedTextureFailure = 112,
	EVRTracked_Camera_Error_VRTracked_Camera_Error_No_چوکھٹا_دستیاب = 113,
	EVRTracked_Camera_Error_VRTracked_Camera_Error_Invalid_دلیل = 114,
	EVRTracked_Camera_Error_VRTracked_Camera_Error_Invalid_چوکھٹا_بفر_سائز = 115,
} EVRTrackedCameraError;

قسمتعریف شمار EVRTracked_Camera_چوکھٹا_Layout
{
	EVRTracked_Camera_چوکھٹا_Layout_Mono = 1,
	EVRTracked_Camera_چوکھٹا_Layout_Stereo = 2,
	EVRTracked_Camera_چوکھٹا_Layout_Vertical_Layout = 16,
	EVRTracked_Camera_چوکھٹا_Layout_Horizontal_Layout = 32,
} EVRTracked_Camera_چوکھٹا_Layout;

قسمتعریف شمار EVRTracked_Camera_چوکھٹا_Type
{
	EVRTracked_Camera_چوکھٹا_Type_VRTracked_Camera_چوکھٹا_Type_Distorted = 0,
	EVRTracked_Camera_چوکھٹا_Type_VRTracked_Camera_چوکھٹا_Type_Undistorted = 1,
	EVRTracked_Camera_چوکھٹا_Type_VRTracked_Camera_چوکھٹا_Type_زیادہ_سے_زیادہ_Undistorted = 2,
	EVRTracked_Camera_چوکھٹا_Type_MAX_CAMERA_چوکھٹا_TYPES = 3,
} EVRTracked_Camera_چوکھٹا_Type;

قسمتعریف شمار EVRDistortionFunctionType
{
	EVRDistortionFunctionType_VRDistortionFunctionType_None = 0,
	EVRDistortionFunctionType_VRDistortionFunctionType_FTheta = 1,
	EVRDistortionFunctionType_VRDistortionFunctionType_Extended_FTheta = 2,
	EVRDistortionFunctionType_MAX_DISTORTION_FUNCTION_TYPES = 3,
} EVRDistortionFunctionType;

قسمتعریف شمار EVSync
{
	EVSync_VSync_None = 0,
	EVSync_VSync_WaitRender = 1,
	EVSync_VSync_NoWaitRender = 2,
} EVSync;

قسمتعریف شمار EVRMura_Correction_منوال
{
	EVRMura_Correction_منوال_Default = 0,
	EVRMura_Correction_منوال_No_Correction = 1,
} EVRMura_Correction_منوال;

قسمتعریف شمار Imu_OffScaleFlags
{
	Imu_OffScaleFlags_OffScale_AccelX = 1,
	Imu_OffScaleFlags_OffScale_AccelY = 2,
	Imu_OffScaleFlags_OffScale_AccelZ = 4,
	Imu_OffScaleFlags_OffScale_GyroX = 8,
	Imu_OffScaleFlags_OffScale_GyroY = 16,
	Imu_OffScaleFlags_OffScale_GyroZ = 32,
} Imu_OffScaleFlags;

قسمتعریف شمار EVRApplicationError
{
	EVRApplicationError_VRApplicationError_None = 0,
	EVRApplication_Error_VRApplication_Error_App_کلید_Already_Exists = 100,
	EVRApplicationError_VRApplicationError_NoManifest = 101,
	EVRApplicationError_VRApplicationError_NoApplication = 102,
	EVRApplication_Error_VRApplication_Error_Invalid_اشاریہ = 103,
	EVRApplicationError_VRApplicationError_UnknownApplication = 104,
	EVRApplicationError_VRApplicationError_IPCFailed = 105,
	EVRApplicationError_VRApplicationError_ApplicationAlreadyRunning = 106,
	EVRApplicationError_VRApplicationError_InvalidManifest = 107,
	EVRApplicationError_VRApplicationError_InvalidApplication = 108,
	EVRApplicationError_VRApplicationError_LaunchFailed = 109,
	EVRApplicationError_VRApplicationError_ApplicationAlreadyStarting = 110,
	EVRApplication_Error_VRApplication_Error_Launch_اندر_پیش_رفت = 111,
	EVRApplicationError_VRApplicationError_OldApplicationQuitting = 112,
	EVRApplicationError_VRApplicationError_TransitionAborted = 113,
	EVRApplicationError_VRApplicationError_IsTemplate = 114,
	EVRApplicationError_VRApplicationError_SteamVRIsExiting = 115,
	EVRApplication_Error_VRApplication_Error_بفر_Too_Small = 200,
	EVRApplication_Error_VRApplication_Error_Property_Not_سیٹ = 201,
	EVRApplicationError_VRApplicationError_UnknownProperty = 202,
	EVRApplicationError_VRApplicationError_InvalidParameter = 203,
	EVRApplicationError_VRApplicationError_NotImplemented = 300,
} EVRApplicationError;

قسمتعریف شمار EVRApplicationProperty
{
	EVRApplicationProperty_VRApplicationProperty_Name_String = 0,
	EVRApplicationProperty_VRApplicationProperty_LaunchType_String = 11,
	EVRApplicationProperty_VRApplicationProperty_WorkingDirectory_String = 12,
	EVRApplication_Property_VRApplication_Property_ثنائی_راستہ_String = 13,
	EVRApplicationProperty_VRApplicationProperty_Arguments_String = 14,
	EVRApplicationProperty_VRApplicationProperty_URL_String = 15,
	EVRApplicationProperty_VRApplicationProperty_Description_String = 50,
	EVRApplicationProperty_VRApplicationProperty_NewsURL_String = 51,
	EVRApplication_Property_VRApplication_Property_Image_راستہ_String = 52,
	EVRApplication_Property_VRApplication_Property_ماخذ_String = 53,
	EVRApplicationProperty_VRApplicationProperty_ActionManifestURL_String = 54,
	EVRApplicationProperty_VRApplicationProperty_IsDashboardOverlay_Bool = 60,
	EVRApplicationProperty_VRApplicationProperty_IsTemplate_Bool = 61,
	EVRApplicationProperty_VRApplicationProperty_IsInstanced_Bool = 62,
	EVRApplication_Property_VRApplication_Property_Is_اندرونی_Bool = 63,
	EVRApplication_Property_VRApplication_Property_چاہتا_Compositor_Pause_اندر_Standby_Bool = 64,
	EVRApplicationProperty_VRApplicationProperty_IsHidden_Bool = 65,
	EVRApplication_Property_VRApplication_Property_آخری_Launch_وقت_Uint64 = 70,
} EVRApplicationProperty;

قسمتعریف شمار EVRSceneApplicationState
{
	EVRSceneApplicationState_None = 0,
	EVRSceneApplicationState_Starting = 1,
	EVRSceneApplicationState_Quitting = 2,
	EVRSceneApplicationState_Running = 3,
	EVRScene_Application_State_انتظار = 4,
} EVRSceneApplicationState;

قسمتعریف شمار ChaperoneCalibrationState
{
	ChaperoneCalibrationState_OK = 1,
	ChaperoneCalibrationState_Warning = 100,
	Chaperone_Calibration_State_Warning_بنیاد_Station_May_Have_Moved = 101,
	Chaperone_Calibration_State_Warning_بنیاد_Station_Removed = 102,
	ChaperoneCalibrationState_Warning_SeatedBoundsInvalid = 103,
	ChaperoneCalibrationState_Error = 200,
	Chaperone_Calibration_State_Error_بنیاد_Station_Uninitialized = 201,
	Chaperone_Calibration_State_Error_بنیاد_Station_Conflict = 202,
	ChaperoneCalibrationState_Error_PlayAreaInvalid = 203,
	ChaperoneCalibrationState_Error_CollisionBoundsInvalid = 204,
} ChaperoneCalibrationState;

قسمتعریف شمار EChaperoneConfigFile
{
	EChaperone_Config_File_زندہ = 1,
	EChaperone_Config_File_عارضی = 2,
} EChaperoneConfigFile;

قسمتعریف شمار EChaperoneImportFlags
{
	EChaperoneImportFlags_EChaperoneImport_BoundsOnly = 1,
} EChaperoneImportFlags;

قسمتعریف شمار EVRCompositorError
{
	EVRCompositorError_VRCompositorError_None = 0,
	EVRCompositorError_VRCompositorError_RequestFailed = 1,
	EVRCompositor_Error_VRCompositor_Error_Incompatible_نسخہ = 100,
	EVRCompositorError_VRCompositorError_DoNotHaveFocus = 101,
	EVRCompositorError_VRCompositorError_InvalidTexture = 102,
	EVRCompositorError_VRCompositorError_IsNotSceneApplication = 103,
	EVRCompositorError_VRCompositorError_TextureIsOnWrongDevice = 104,
	EVRCompositor_Error_VRCompositor_Error_Texture_استعمال_کرتا_Unsupported_Format = 105,
	EVRCompositorError_VRCompositorError_SharedTexturesNotSupported = 106,
	EVRCompositor_Error_VRCompositor_Error_اشاریہ_برآمد_کا_Range = 107,
	EVRCompositorError_VRCompositorError_AlreadySubmitted = 108,
	EVRCompositorError_VRCompositorError_InvalidBounds = 109,
	EVRCompositor_Error_VRCompositor_Error_Already_سیٹ = 110,
} EVRCompositorError;

قسمتعریف شمار EVRCompositor_Timing_منوال
{
	EVRCompositor_Timing_منوال_VRCompositor_Timing_منوال_Implicit = 0,
	EVRCompositor_Timing_منوال_VRCompositor_Timing_منوال_Explicit_Runtime_Performs_Post_Present_Handoff = 1,
	EVRCompositor_Timing_منوال_VRCompositor_Timing_منوال_Explicit_Application_Performs_Post_Present_Handoff = 2,
} EVRCompositor_Timing_منوال;

قسمتعریف شمار VROverlay_داخلہ_طریقہ
{
	VROverlay_داخلہ_طریقہ_None = 0,
	VROverlay_داخلہ_طریقہ_Mouse = 1,
} VROverlay_داخلہ_طریقہ;

قسمتعریف شمار VROverlayTransformType
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

قسمتعریف شمار VROverlayFlags
{
	VROverlayFlags_NoDashboardTab = 8,
	VROverlayFlags_SendVRDiscreteScrollEvents = 64,
	VROverlayFlags_SendVRTouchpadEvents = 128,
	VROverlayFlags_ShowTouchPadScrollWheel = 256,
	VROverlay_Flags_Transfer_Ownership_مقصد_اندرونی_Process = 512,
	VROverlayFlags_SideBySide_Parallel = 1024,
	VROverlayFlags_SideBySide_Crossed = 2048,
	VROverlayFlags_Panorama = 4096,
	VROverlayFlags_StereoPanorama = 8192,
	VROverlay_Flags_ترتیب_دو_With_Non_Scene_Overlays = 16384,
	VROverlay_Flags_Visible_اندر_Dashboard = 32768,
	VROverlayFlags_MakeOverlaysInteractiveIfVisible = 65536,
	VROverlayFlags_SendVRSmoothScrollEvents = 131072,
	VROverlayFlags_ProtectedContent = 262144,
	VROverlayFlags_HideLaserIntersection = 524288,
	VROverlay_Flags_چاہتا_Modal_Behavior = 1048576,
	VROverlayFlags_IsPremultiplied = 2097152,
	VROverlayFlags_IgnoreTextureAlpha = 4194304,
	VROverlayFlags_EnableControlBar = 8388608,
	VROverlayFlags_EnableControlBarKeyboard = 16777216,
	VROverlayFlags_EnableControlBarClose = 33554432,
} VROverlayFlags;

قسمتعریف شمار VRMessageOverlayResponse
{
	VRMessageOverlayResponse_ButtonPress_0 = 0,
	VRMessageOverlayResponse_ButtonPress_1 = 1,
	VRMessageOverlayResponse_ButtonPress_2 = 2,
	VRMessageOverlayResponse_ButtonPress_3 = 3,
	VRMessage_Overlay_Response_Couldnt_ڈھونڈو_System_Overlay = 4,
	VRMessage_Overlay_Response_Couldnt_ڈھونڈو_Or_Create_Client_Overlay = 5,
	VRMessageOverlayResponse_ApplicationQuit = 6,
} VRMessageOverlayResponse;

قسمتعریف شمار EGamepad_متن_داخلہ_منوال
{
	EGamepad_متن_داخلہ_منوال_k_EGamepad_متن_داخلہ_منوال_معمول = 0,
	EGamepad_متن_داخلہ_منوال_k_EGamepad_متن_داخلہ_منوال_Password = 1,
	EGamepad_متن_داخلہ_منوال_k_EGamepad_متن_داخلہ_منوال_Submit = 2,
} EGamepad_متن_داخلہ_منوال;

قسمتعریف شمار EGamepad_متن_داخلہ_سطر_منوال
{
	EGamepad_متن_داخلہ_سطر_منوال_k_EGamepad_متن_داخلہ_سطر_منوال_Single_سطر = 0,
	EGamepad_متن_داخلہ_سطر_منوال_k_EGamepad_متن_داخلہ_سطر_منوال_مضرب_سطریں = 1,
} EGamepad_متن_داخلہ_سطر_منوال;

قسمتعریف شمار EVROverlay_Intersection_نقاب_Primitive_Type
{
	EVROverlay_Intersection_نقاب_Primitive_Type_Overlay_Intersection_Primitive_Type_Rectangle = 0,
	EVROverlay_Intersection_نقاب_Primitive_Type_Overlay_Intersection_Primitive_Type_Circle = 1,
} EVROverlay_Intersection_نقاب_Primitive_Type;

قسمتعریف شمار EKeyboardFlags
{
	EKeyboard_Flags_Keyboard_Flag_اقل = 1,
	EKeyboardFlags_KeyboardFlag_Modal = 2,
} EKeyboardFlags;

قسمتعریف شمار EDeviceType
{
	EDeviceType_DeviceType_Invalid = -1,
	EDevice_Type_Device_Type_براہ_راست_X11 = 0,
	EDeviceType_DeviceType_Vulkan = 1,
} EDeviceType;

قسمتعریف شمار Headset_View_منوال_t
{
	Headset_View_منوال_t_Headset_View_منوال_بایاں = 0,
	Headset_View_منوال_t_Headset_View_منوال_دایاں = 1,
	Headset_View_منوال_t_Headset_View_منوال_Both = 2,
} Headset_View_منوال_t;

قسمتعریف شمار EVRRenderModelError
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

قسمتعریف شمار EVRRenderModelTextureFormat
{
	EVRRenderModelTextureFormat_VRRenderModelTextureFormat_RGBA8_SRGB = 0,
	EVRRenderModelTextureFormat_VRRenderModelTextureFormat_BC2 = 1,
	EVRRenderModelTextureFormat_VRRenderModelTextureFormat_BC4 = 2,
	EVRRenderModelTextureFormat_VRRenderModelTextureFormat_BC7 = 3,
	EVRRenderModelTextureFormat_VRRenderModelTextureFormat_BC7_SRGB = 4,
	EVRRenderModelTextureFormat_VRRenderModelTextureFormat_RGBA16_FLOAT = 5,
} EVRRenderModelTextureFormat;

قسمتعریف شمار EVRNotificationType
{
	EVRNotificationType_Transient = 0,
	EVRNotificationType_Persistent = 1,
	EVRNotification_Type_Transient_System_With_User_قدر = 2,
} EVRNotificationType;

قسمتعریف شمار EVRNotificationStyle
{
	EVRNotificationStyle_None = 0,
	EVRNotificationStyle_Application = 100,
	EVRNotificationStyle_Contact_Disabled = 200,
	EVRNotificationStyle_Contact_Enabled = 201,
	EVRNotification_Style_Contact_فعال = 202,
} EVRNotificationStyle;

قسمتعریف شمار EVRSettingsError
{
	EVRSettingsError_VRSettingsError_None = 0,
	EVRSettingsError_VRSettingsError_IPCFailed = 1,
	EVRSettingsError_VRSettingsError_WriteFailed = 2,
	EVRSettingsError_VRSettingsError_ReadFailed = 3,
	EVRSettingsError_VRSettingsError_JsonParseFailed = 4,
	EVRSettingsError_VRSettingsError_UnsetSettingHasNoDefault = 5,
} EVRSettingsError;

قسمتعریف شمار EVRScreenshotError
{
	EVRScreenshotError_VRScreenshotError_None = 0,
	EVRScreenshotError_VRScreenshotError_RequestFailed = 1,
	EVRScreenshot_Error_VRScreenshot_Error_Incompatible_نسخہ = 100,
	EVRScreenshot_Error_VRScreenshot_Error_Not_ملا = 101,
	EVRScreenshot_Error_VRScreenshot_Error_بفر_Too_Small = 102,
	EVRScreenshot_Error_VRScreenshot_Error_Screenshot_Already_اندر_پیش_رفت = 108,
} EVRScreenshotError;

قسمتعریف شمار EVRSkeletalTransformSpace
{
	EVRSkeletalTransformSpace_VRSkeletalTransformSpace_Model = 0,
	EVRSkeletal_Transform_Space_VRSkeletal_Transform_Space_والد = 1,
} EVRSkeletalTransformSpace;

قسمتعریف شمار EVRSkeletalReferencePose
{
	EVRSkeletalReferencePose_VRSkeletalReferencePose_BindPose = 0,
	EVRSkeletalReferencePose_VRSkeletalReferencePose_OpenHand = 1,
	EVRSkeletalReferencePose_VRSkeletalReferencePose_Fist = 2,
	EVRSkeletal_Reference_Pose_VRSkeletal_Reference_Pose_Grip_حد_بندی = 3,
} EVRSkeletalReferencePose;

قسمتعریف شمار EVRFinger
{
	EVRFinger_VRFinger_Thumb = 0,
	EVRFinger_VRFinger_اشاریہ = 1,
	EVRFinger_VRFinger_درمیان = 2,
	EVRFinger_VRFinger_Ring = 3,
	EVRFinger_VRFinger_Pinky = 4,
	EVRFinger_VRFinger_گنتی = 5,
} EVRFinger;

قسمتعریف شمار EVRFingerSplay
{
	EVRFinger_Splay_VRFinger_Splay_Thumb_اشاریہ = 0,
	EVRFinger_Splay_VRFinger_Splay_اشاریہ_درمیان = 1,
	EVRFinger_Splay_VRFinger_Splay_درمیان_Ring = 2,
	EVRFingerSplay_VRFingerSplay_Ring_Pinky = 3,
	EVRFinger_Splay_VRFinger_Splay_گنتی = 4,
} EVRFingerSplay;

قسمتعریف شمار EVRSummaryType
{
	EVRSummaryType_VRSummaryType_FromAnimation = 0,
	EVRSummaryType_VRSummaryType_FromDevice = 1,
} EVRSummaryType;

قسمتعریف شمار EVRInputFilterCancelType
{
	EVRInputFilterCancelType_VRInputFilterCancel_Timers = 0,
	EVRInputFilterCancelType_VRInputFilterCancel_Momentum = 1,
} EVRInputFilterCancelType;

قسمتعریف شمار EVRInput_String_بٹ
{
	EVRInput_String_بٹ_VRInput_String_Hand = 1,
	EVRInput_String_بٹ_VRInput_String_Controller_Type = 2,
	EVRInput_String_بٹ_VRInput_String_داخلہ_ماخذ = 4,
	EVRInput_String_بٹ_VRInput_String_All = -1,
} EVRInput_String_بٹ;

قسمتعریف شمار EIOBufferError
{
	EIOBufferError_IOBuffer_Success = 0,
	EIOBufferError_IOBuffer_OperationFailed = 100,
	EIOBufferError_IOBuffer_InvalidHandle = 101,
	EIOBuffer_Error_IOBuffer_Invalid_دلیل = 102,
	EIOBuffer_Error_IOBuffer_راستہ_Exists = 103,
	EIOBuffer_Error_IOBuffer_راستہ_Does_Not_Exist = 104,
	EIOBufferError_IOBuffer_Permission = 105,
} EIOBufferError;

قسمتعریف شمار EIOBuffer_منوال
{
	EIOBuffer_منوال_IOBuffer_منوال_Read = 1,
	EIOBuffer_منوال_IOBuffer_منوال_Write = 2,
	EIOBuffer_منوال_IOBuffer_منوال_Create = 512,
} EIOBuffer_منوال;

قسمتعریف شمار EVRDebugError
{
	EVRDebugError_VRDebugError_Success = 0,
	EVRDebugError_VRDebugError_BadParameter = 1,
} EVRDebugError;

قسمتعریف شمار EPropertyWriteType
{
	EProperty_Write_Type_Property_Write_سیٹ = 0,
	EPropertyWriteType_PropertyWrite_Erase = 1,
	EProperty_Write_Type_Property_Write_سیٹ_Error = 2,
} EPropertyWriteType;

قسمتعریف شمار EBlock_قطار_Error
{
	EBlock_قطار_Error_بلاک_قطار_Error_None = 0,
	EBlock_قطار_Error_بلاک_قطار_Error_قطار_Already_Exists = 1,
	EBlock_قطار_Error_بلاک_قطار_Error_قطار_Not_ملا = 2,
	EBlock_قطار_Error_بلاک_قطار_Error_بلاک_Not_دستیاب = 3,
	EBlock_قطار_Error_بلاک_قطار_Error_Invalid_Handle = 4,
	EBlock_قطار_Error_بلاک_قطار_Error_Invalid_Param = 5,
	EBlock_قطار_Error_بلاک_قطار_Error_Param_Mismatch = 6,
	EBlock_قطار_Error_بلاک_قطار_Error_اندرونی_Error = 7,
	EBlock_قطار_Error_بلاک_قطار_Error_Already_Initialized = 8,
	EBlock_قطار_Error_بلاک_قطار_Error_Operation_Is_Server_Only = 9,
	EBlock_قطار_Error_بلاک_قطار_Error_Too_Many_Connections = 10,
} EBlock_قطار_Error;

قسمتعریف شمار EBlock_قطار_Read_Type
{
	EBlock_قطار_Read_Type_بلاک_قطار_Read_Latest = 0,
	EBlock_قطار_Read_Type_بلاک_قطار_Read_New = 1,
	EBlock_قطار_Read_Type_بلاک_قطار_Read_اگلا = 2,
} EBlock_قطار_Read_Type;

قسمتعریف شمار EBlock_قطار_Creation_Flag
{
	EBlock_قطار_Creation_Flag_بلاک_قطار_Flag_Owner_Is_Reader = 1,
} EBlock_قطار_Creation_Flag;


// OpenVR typedefs

قسمتعریف uint32_t Property_Type_لیبل_t;
قسمتعریف uint32_t SpatialAnchorHandle_t;
قسمتعریف خالی * glSharedTextureHandle_t;
قسمتعریف int32_t glInt_t;
قسمتعریف uint32_t glUInt_t;
قسمتعریف uint64_t SharedTextureHandle_t;
قسمتعریف uint32_t DriverId_t;
قسمتعریف uint32_t Tracked_Device_اشاریہ_t;
قسمتعریف uint64_t WebConsoleHandle_t;
قسمتعریف uint64_t PropertyContainerHandle_t;
قسمتعریف PropertyContainerHandle_t DriverHandle_t;
قسمتعریف uint64_t VRActionHandle_t;
قسمتعریف uint64_t VRAction_سیٹ_Handle_t;
قسمتعریف uint64_t VRInput_قدر_Handle_t;
قسمتعریف uint32_t VRComponentProperties;
قسمتعریف uint64_t VROverlayHandle_t;
قسمتعریف int32_t Bone_اشاریہ_t;
قسمتعریف uint64_t TrackedCameraHandle_t;
قسمتعریف uint32_t ScreenshotHandle_t;
قسمتعریف int32_t TextureID_t;
قسمتعریف uint32_t VRNotificationId;
قسمتعریف uint64_t IOBufferHandle_t;
قسمتعریف uint64_t VrProfilerEventHandle_t;
قسمتعریف EVRInitError HmdError;
قسمتعریف EVREye Hmd_Eye;
قسمتعریف EColorSpace ColorSpace;
قسمتعریف ETracking_نتیجہ Hmd_Tracking_نتیجہ;
قسمتعریف ETrackedDeviceClass TrackedDeviceClass;
قسمتعریف ETrackingUniverseOrigin TrackingUniverseOrigin;
قسمتعریف ETrackedDeviceProperty TrackedDeviceProperty;
قسمتعریف ETrackedPropertyError TrackedPropertyError;
قسمتعریف EVRSubmitFlags VRSubmitFlags_t;
قسمتعریف EVRState VRState_t;
قسمتعریف ECollisionBoundsStyle CollisionBoundsStyle_t;
قسمتعریف EVROverlayError VROverlayError;
قسمتعریف EVRFirmwareError VRFirmwareError;
قسمتعریف EVRCompositorError VRCompositorError;
قسمتعریف EVRScreenshotError VRScreenshotsError;
قسمتعریف uint64_t راستہ_Handle_t;

// OpenVR Structs

قسمتعریف ساخت HmdMatrix34_t
{
	اعشاری m[3][4]; //float[3][4]
} HmdMatrix34_t;

قسمتعریف ساخت HmdMatrix33_t
{
	اعشاری m[3][3]; //float[3][3]
} HmdMatrix33_t;

قسمتعریف ساخت HmdMatrix44_t
{
	اعشاری m[4][4]; //float[4][4]
} HmdMatrix44_t;

قسمتعریف ساخت HmdVector3_t
{
	اعشاری v[3]; //float[3]
} HmdVector3_t;

قسمتعریف ساخت HmdVector4_t
{
	اعشاری v[4]; //float[4]
} HmdVector4_t;

قسمتعریف ساخت HmdVector3d_t
{
	دوہرا v[3]; //double[3]
} HmdVector3d_t;

قسمتعریف ساخت HmdVector2_t
{
	اعشاری v[2]; //float[2]
} HmdVector2_t;

قسمتعریف ساخت HmdQuaternion_t
{
	دوہرا w;
	دوہرا x;
	دوہرا y;
	دوہرا z;
} HmdQuaternion_t;

قسمتعریف ساخت HmdQuaternionf_t
{
	اعشاری w;
	اعشاری x;
	اعشاری y;
	اعشاری z;
} HmdQuaternionf_t;

قسمتعریف ساخت HmdColor_t
{
	اعشاری r;
	اعشاری g;
	اعشاری b;
	اعشاری a;
} HmdColor_t;

قسمتعریف ساخت HmdQuad_t
{
	ساخت HmdVector3_t vCorners[4]; //struct vr::HmdVector3_t[4]
} HmdQuad_t;

قسمتعریف ساخت HmdRect2_t
{
	ساخت HmdVector2_t v_چوٹی_بایاں;
	ساخت HmdVector2_t v_Bottom_دایاں;
} HmdRect2_t;

قسمتعریف ساخت VRBoneTransform_t
{
	ساخت HmdVector4_t position;
	ساخت HmdQuaternionf_t orientation;
} VRBoneTransform_t;

قسمتعریف ساخت DistortionCoordinates_t
{
	اعشاری rfRed[2]; //float[2]
	اعشاری rfGreen[2]; //float[2]
	اعشاری rfBlue[2]; //float[2]
} DistortionCoordinates_t;

قسمتعریف ساخت Texture_t
{
	خالی * handle; // void *
	شمار ETextureType eType;
	شمار EColorSpace eColorSpace;
} Texture_t;

قسمتعریف ساخت TrackedDevicePose_t
{
	ساخت HmdMatrix34_t m_Device_مقصد_Absolute_Tracking;
	ساخت HmdVector3_t vVelocity;
	ساخت HmdVector3_t vAngularVelocity;
	شمار ETracking_نتیجہ e_Tracking_نتیجہ;
	bool bPoseIsValid;
	bool bDeviceIsConnected;
} TrackedDevicePose_t;

قسمتعریف ساخت VRTextureBounds_t
{
	اعشاری uMin;
	اعشاری vMin;
	اعشاری uMax;
	اعشاری vMax;
} VRTextureBounds_t;

قسمتعریف ساخت VRTextureWithPose_t
{
	خالی * handle; // void *
	شمار ETextureType eType;
	شمار EColorSpace eColorSpace;
	ساخت HmdMatrix34_t m_Device_مقصد_Absolute_Tracking;
} VRTextureWithPose_t;

قسمتعریف ساخت VRTexture_گہرائی_Info_t
{
	خالی * handle; // void *
	ساخت HmdMatrix44_t mProjection;
	ساخت HmdVector2_t vRange;
} VRTexture_گہرائی_Info_t;

قسمتعریف ساخت VRTexture_With_گہرائی_t
{
	خالی * handle; // void *
	شمار ETextureType eType;
	شمار EColorSpace eColorSpace;
	ساخت VRTexture_گہرائی_Info_t گہرائی_2;
} VRTexture_With_گہرائی_t;

قسمتعریف ساخت VRTexture_With_Pose_And_گہرائی_t
{
	خالی * handle; // void *
	شمار ETextureType eType;
	شمار EColorSpace eColorSpace;
	ساخت HmdMatrix34_t m_Device_مقصد_Absolute_Tracking;
	ساخت VRTexture_گہرائی_Info_t گہرائی_2;
} VRTexture_With_Pose_And_گہرائی_t;

قسمتعریف ساخت VRVulkan_Texture_ڈیٹا_t
{
	uint64_t m_nImage;
	ساخت VkDevice_T * m_pDevice; // struct VkDevice_T *
	ساخت VkPhysicalDevice_T * m_pPhysicalDevice; // struct VkPhysicalDevice_T *
	ساخت VkInstance_T * m_pInstance; // struct VkInstance_T *
	ساخت Vk_قطار_T * m_p_قطار; // struct VkQueue_T *
	uint32_t m_n_قطار_Family_اشاریہ;
	uint32_t m_n_چوڑائی;
	uint32_t m_n_اونچائی;
	uint32_t m_nFormat;
	uint32_t m_n_Sample_گنتی;
} VRVulkan_Texture_ڈیٹا_t;

قسمتعریف ساخت VRVulkan_Texture_Array_ڈیٹا_t
{
	uint32_t m_un_Array_اشاریہ;
	uint32_t m_un_Array_سائز;
} VRVulkan_Texture_Array_ڈیٹا_t;

قسمتعریف ساخت D3_D12_Texture_ڈیٹا_t
{
	ساخت ID3D12Resource * m_pResource; // struct ID3D12Resource *
	ساخت ID3_D12_Command_قطار * m_p_Command_قطار; // struct ID3D12CommandQueue *
	uint32_t m_n_گرہ_نقاب;
} D3_D12_Texture_ڈیٹا_t;

قسمتعریف ساخت VREvent_Controller_t
{
	uint32_t button;
} VREvent_Controller_t;

قسمتعریف ساخت VREvent_Mouse_t
{
	اعشاری x;
	اعشاری y;
	uint32_t button;
} VREvent_Mouse_t;

قسمتعریف ساخت VREvent_Scroll_t
{
	اعشاری xdelta;
	اعشاری ydelta;
	uint32_t غیر_مستعمل;
	اعشاری viewportscale;
} VREvent_Scroll_t;

قسمتعریف ساخت VREvent_TouchPadMove_t
{
	bool b_Finger_نیچے_کو;
	اعشاری fl_Seconds_Finger_نیچے_کو;
	اعشاری f_قدر_XFirst;
	اعشاری f_قدر_YFirst;
	اعشاری f_قدر_XRaw;
	اعشاری f_قدر_YRaw;
} VREvent_TouchPadMove_t;

قسمتعریف ساخت VREvent_Notification_t
{
	uint64_t ul_User_قدر;
	uint32_t notificationId;
} VREvent_Notification_t;

قسمتعریف ساخت VREvent_Process_t
{
	uint32_t pid;
	uint32_t oldPid;
	bool bForced;
	bool b_Connection_گمشدہ;
} VREvent_Process_t;

قسمتعریف ساخت VREvent_Overlay_t
{
	uint64_t overlayHandle;
	uint64_t device_راستہ;
	uint64_t حافظہ_بلاک_Id;
} VREvent_Overlay_t;

قسمتعریف ساخت VREvent_حالت_t
{
	uint32_t حالت_State;
} VREvent_حالت_t;

قسمتعریف ساخت VREvent_Keyboard_t
{
	حرف c_New_داخلہ[8]; //char[8]
	uint64_t u_User_قدر;
} VREvent_Keyboard_t;

قسمتعریف ساخت VREvent_Ipd_t
{
	اعشاری ipdMeters;
} VREvent_Ipd_t;

قسمتعریف ساخت VREvent_Chaperone_t
{
	uint64_t m_n_پچھلا_Universe;
	uint64_t m_nCurrentUniverse;
} VREvent_Chaperone_t;

قسمتعریف ساخت VREvent_Reserved_t
{
	uint64_t reserved0;
	uint64_t reserved1;
	uint64_t reserved2;
	uint64_t reserved3;
	uint64_t reserved4;
	uint64_t reserved5;
} VREvent_Reserved_t;

قسمتعریف ساخت VREvent_PerformanceTest_t
{
	uint32_t m_nFidelityLevel;
} VREvent_PerformanceTest_t;

قسمتعریف ساخت VREvent_SeatedZeroPoseReset_t
{
	bool bResetBySystemMenu;
} VREvent_SeatedZeroPoseReset_t;

قسمتعریف ساخت VREvent_Screenshot_t
{
	uint32_t handle;
	uint32_t type;
} VREvent_Screenshot_t;

قسمتعریف ساخت VREvent_Screenshot_پیش_رفت_t
{
	اعشاری پیش_رفت_2;
} VREvent_Screenshot_پیش_رفت_t;

قسمتعریف ساخت VREvent_ApplicationLaunch_t
{
	uint32_t pid;
	uint32_t un_دلائل_Handle;
} VREvent_ApplicationLaunch_t;

قسمتعریف ساخت VREvent_EditingCameraSurface_t
{
	uint64_t overlayHandle;
	uint32_t n_Visual_منوال;
} VREvent_EditingCameraSurface_t;

قسمتعریف ساخت VREvent_پیغام_Overlay_t
{
	uint32_t unVRMessageOverlayResponse;
} VREvent_پیغام_Overlay_t;

قسمتعریف ساخت VREvent_Property_t
{
	PropertyContainerHandle_t container;
	شمار ETrackedDeviceProperty prop;
} VREvent_Property_t;

قسمتعریف ساخت VREvent_HapticVibration_t
{
	uint64_t containerHandle;
	uint64_t componentHandle;
	اعشاری fDurationSeconds;
	اعشاری fFrequency;
	اعشاری fAmplitude;
} VREvent_HapticVibration_t;

قسمتعریف ساخت VREvent_WebConsole_t
{
	WebConsoleHandle_t webConsoleHandle;
} VREvent_WebConsole_t;

قسمتعریف ساخت VREvent_داخلہ_Binding_بھرو_t
{
	PropertyContainerHandle_t ulAppContainer;
	uint64_t راستہ_پیغام;
	uint64_t راستہ_Url;
	uint64_t راستہ_Controller_Type;
} VREvent_داخلہ_Binding_بھرو_t;

قسمتعریف ساخت VREvent_داخلہ_Action_Manifest_بھرو_t
{
	uint64_t راستہ_App_کلید;
	uint64_t راستہ_پیغام;
	uint64_t راستہ_پیغام_Param;
	uint64_t راستہ_Manifest_راستہ;
} VREvent_داخلہ_Action_Manifest_بھرو_t;

قسمتعریف ساخت VREvent_SpatialAnchor_t
{
	SpatialAnchorHandle_t unHandle;
} VREvent_SpatialAnchor_t;

قسمتعریف ساخت VREvent_پیش_رفت_Update_t
{
	uint64_t ulApplicationPropertyContainer;
	uint64_t راستہ_Device;
	uint64_t راستہ_داخلہ_ماخذ;
	uint64_t راستہ_پیش_رفت_Action;
	uint64_t راستہ_Icon;
	اعشاری f_پیش_رفت;
} VREvent_پیش_رفت_Update_t;

قسمتعریف ساخت VREvent_ShowUI_t
{
	شمار EShowUIType eType;
} VREvent_ShowUI_t;

قسمتعریف ساخت VREvent_ShowDevTools_t
{
	int32_t nBrowserIdentifier;
} VREvent_ShowDevTools_t;

قسمتعریف ساخت VREvent_HDCPError_t
{
	شمار EHDCPError e_رمز;
} VREvent_HDCPError_t;

قسمتعریف ساخت RenderModel_ComponentState_t
{
	ساخت HmdMatrix34_t m_Tracking_مقصد_Component_Render_Model;
	ساخت HmdMatrix34_t m_Tracking_مقصد_Component_Local;
	VRComponentProperties uProperties;
} RenderModel_ComponentState_t;

قسمتعریف ساخت HiddenAreaMesh_t
{
	ساخت HmdVector2_t * p_راس_ڈیٹا; // const struct vr::HmdVector2_t *
	uint32_t un_Triangle_گنتی;
} HiddenAreaMesh_t;

قسمتعریف ساخت VRControllerAxis_t
{
	اعشاری x;
	اعشاری y;
} VRControllerAxis_t;

قسمتعریف ساخت VRControllerState_t
{
	uint32_t un_Packet_عدد;
	uint64_t ulButtonPressed;
	uint64_t ulButtonTouched;
	ساخت VRControllerAxis_t rAxis[5]; //struct vr::VRControllerAxis_t[5]
} VRControllerState_t;

قسمتعریف ساخت Camera_Video_دھارا_چوکھٹا_سرخی_t
{
	شمار EVRTracked_Camera_چوکھٹا_Type e_چوکھٹا_Type;
	uint32_t n_چوڑائی;
	uint32_t n_اونچائی;
	uint32_t n_بائٹیں_فی_Pixel;
	uint32_t n_چوکھٹا_Sequence;
	ساخت TrackedDevicePose_t trackedDevicePose;
	uint64_t ul_چوکھٹا_Exposure_وقت;
} Camera_Video_دھارا_چوکھٹا_سرخی_t;

قسمتعریف ساخت Compositor_چوکھٹا_Timing
{
	uint32_t m_n_سائز;
	uint32_t m_n_چوکھٹا_اشاریہ;
	uint32_t m_n_عدد_چوکھٹا_Presents;
	uint32_t m_n_عدد_Mis_Presented;
	uint32_t m_n_عدد_Dropped_چوکھٹے;
	uint32_t m_nReprojectionFlags;
	دوہرا m_fl_System_وقت_اندر_Seconds;
	اعشاری m_flPreSubmitGpuMs;
	اعشاری m_flPostSubmitGpuMs;
	اعشاری m_fl_کل_Render_Gpu_Ms;
	اعشاری m_flCompositorRenderGpuMs;
	اعشاری m_flCompositorRenderCpuMs;
	اعشاری m_flCompositorIdleCpuMs;
	اعشاری m_fl_Client_چوکھٹا_Interval_Ms;
	اعشاری m_flPresentCallCpuMs;
	اعشاری m_flWaitForPresentCpuMs;
	اعشاری m_fl_Submit_چوکھٹا_Ms;
	اعشاری m_flWaitGetPosesCalledMs;
	اعشاری m_flNewPosesReadyMs;
	اعشاری m_fl_New_چوکھٹا_Ready_Ms;
	اعشاری m_fl_Compositor_Update_آغاز_Ms;
	اعشاری m_fl_Compositor_Update_انتہا_Ms;
	اعشاری m_fl_Compositor_Render_آغاز_Ms;
	TrackedDevicePose_t m_HmdPose;
	uint32_t m_n_عدد_VSyncs_Ready_For_Use;
	uint32_t m_n_عدد_VSyncs_مقصد_پہلا_View;
} Compositor_چوکھٹا_Timing;

قسمتعریف ساخت Compositor_BenchmarkResults
{
	اعشاری m_fl_Mega_Pixels_فی_دوسرا;
	اعشاری m_fl_Hmd_Recommended_Mega_Pixels_فی_دوسرا;
} Compositor_BenchmarkResults;

قسمتعریف ساخت Driver_براہ_راست_منوال_چوکھٹا_Timing
{
	uint32_t m_n_سائز;
	uint32_t m_n_عدد_چوکھٹا_Presents;
	uint32_t m_n_عدد_Mis_Presented;
	uint32_t m_n_عدد_Dropped_چوکھٹے;
	uint32_t m_nReprojectionFlags;
} Driver_براہ_راست_منوال_چوکھٹا_Timing;

قسمتعریف ساخت ImuSample_t
{
	دوہرا f_Sample_وقت;
	ساخت HmdVector3d_t vAccel;
	ساخت HmdVector3d_t vGyro;
	uint32_t unOffScaleFlags;
} ImuSample_t;

قسمتعریف ساخت App_Override_کلیدیں_t
{
	حرف * pch_کلید; // const char *
	حرف * pch_قدر; // const char *
} App_Override_کلیدیں_t;

قسمتعریف ساخت Compositor_CumulativeStats
{
	uint32_t m_nPid;
	uint32_t m_n_عدد_چوکھٹا_Presents;
	uint32_t m_n_عدد_Dropped_چوکھٹے;
	uint32_t m_n_عدد_Reprojected_چوکھٹے;
	uint32_t m_n_عدد_چوکھٹا_Presents_On_Startup;
	uint32_t m_n_عدد_Dropped_چوکھٹے_On_Startup;
	uint32_t m_n_عدد_Reprojected_چوکھٹے_On_Startup;
	uint32_t m_n_عدد_Loading;
	uint32_t m_n_عدد_چوکھٹا_Presents_Loading;
	uint32_t m_n_عدد_Dropped_چوکھٹے_Loading;
	uint32_t m_n_عدد_Reprojected_چوکھٹے_Loading;
	uint32_t m_n_عدد_Timed_برآمد;
	uint32_t m_n_عدد_چوکھٹا_Presents_Timed_برآمد;
	uint32_t m_n_عدد_Dropped_چوکھٹے_Timed_برآمد;
	uint32_t m_n_عدد_Reprojected_چوکھٹے_Timed_برآمد;
	uint32_t m_n_عدد_چوکھٹا_Submits;
	دوہرا m_fl_مجموع_Compositor_CPUTime_MS;
	دوہرا m_fl_مجموع_Compositor_GPUTime_MS;
	دوہرا m_fl_مجموع_ہدف_چوکھٹا_Times;
	دوہرا m_fl_مجموع_Application_CPUTime_MS;
	دوہرا m_fl_مجموع_Application_GPUTime_MS;
} Compositor_CumulativeStats;

قسمتعریف ساخت Compositor_StageRenderSettings
{
	ساخت HmdColor_t m_PrimaryColor;
	ساخت HmdColor_t m_SecondaryColor;
	اعشاری m_flVignetteInnerRadius;
	اعشاری m_flVignetteOuterRadius;
	اعشاری m_flFresnelStrength;
	bool m_bBackfaceCulling;
	bool m_bGreyscale;
	bool m_bWireframe;
} Compositor_StageRenderSettings;

قسمتعریف ساخت VROverlayIntersectionParams_t
{
	ساخت HmdVector3_t v_ماخذ;
	ساخت HmdVector3_t vDirection;
	شمار ETrackingUniverseOrigin eOrigin;
} VROverlayIntersectionParams_t;

قسمتعریف ساخت VROverlayIntersectionResults_t
{
	ساخت HmdVector3_t v_نقطہ;
	ساخت HmdVector3_t v_معمول;
	ساخت HmdVector2_t vUVs;
	اعشاری f_فاصلہ;
} VROverlayIntersectionResults_t;

قسمتعریف ساخت Intersection_نقاب_Rectangle_t
{
	اعشاری m_fl_چوٹی_بایاں_X;
	اعشاری m_fl_چوٹی_بایاں_Y;
	اعشاری m_fl_چوڑائی;
	اعشاری m_fl_اونچائی;
} Intersection_نقاب_Rectangle_t;

قسمتعریف ساخت Intersection_نقاب_Circle_t
{
	اعشاری m_flCenterX;
	اعشاری m_flCenterY;
	اعشاری m_flRadius;
} Intersection_نقاب_Circle_t;

قسمتعریف ساخت VROverlayProjection_t
{
	اعشاری f_بایاں;
	اعشاری f_دایاں;
	اعشاری f_چوٹی;
	اعشاری fBottom;
} VROverlayProjection_t;

قسمتعریف ساخت VROverlayView_t
{
	VROverlayHandle_t overlayHandle;
	ساخت Texture_t texture;
	ساخت VRTextureBounds_t textureBounds;
} VROverlayView_t;

قسمتعریف ساخت VRVulkanDevice_t
{
	ساخت VkInstance_T * m_pInstance; // struct VkInstance_T *
	ساخت VkDevice_T * m_pDevice; // struct VkDevice_T *
	ساخت VkPhysicalDevice_T * m_pPhysicalDevice; // struct VkPhysicalDevice_T *
	ساخت Vk_قطار_T * m_p_قطار; // struct VkQueue_T *
	uint32_t m_u_قطار_Family_اشاریہ;
} VRVulkanDevice_t;

قسمتعریف ساخت VRNativeDevice_t
{
	خالی * handle; // void *
	شمار EDeviceType eType;
} VRNativeDevice_t;

قسمتعریف ساخت Render_Model_راس_t
{
	ساخت HmdVector3_t vPosition;
	ساخت HmdVector3_t v_معمول;
	اعشاری rfTextureCoord[2]; //float[2]
} Render_Model_راس_t;

#اگر defined(__linux__) || defined(__APPLE__)
#ہدایت pack( ڈالو, 4 )
#اگر_ختم
قسمتعریف ساخت RenderModel_TextureMap_t
{
	uint16_t un_چوڑائی;
	uint16_t un_اونچائی;
	uint8_t * rub_Texture_Map_ڈیٹا; // const uint8_t *
	شمار EVRRenderModelTextureFormat format;
	uint16_t un_Mip_سطحیں;
} RenderModel_TextureMap_t;

#اگر defined(__linux__) || defined(__APPLE__)
#ہدایت pack( نکالو )
#اگر_ختم
#اگر defined(__linux__) || defined(__APPLE__)
#ہدایت pack( ڈالو, 4 )
#اگر_ختم
قسمتعریف ساخت RenderModel_t
{
	ساخت Render_Model_راس_t * r_راس_ڈیٹا; // const struct vr::RenderModel_Vertex_t *
	uint32_t un_راس_گنتی;
	uint16_t * r_اشاریہ_ڈیٹا; // const uint16_t *
	uint32_t un_Triangle_گنتی;
	TextureID_t diffuseTextureId;
} RenderModel_t;

#اگر defined(__linux__) || defined(__APPLE__)
#ہدایت pack( نکالو )
#اگر_ختم
قسمتعریف ساخت Render_Model_Controller_منوال_State_t
{
	bool bScrollWheelVisible;
} Render_Model_Controller_منوال_State_t;

قسمتعریف ساخت NotificationBitmap_t
{
	خالی * m_p_Image_ڈیٹا; // void *
	int32_t m_n_چوڑائی;
	int32_t m_n_اونچائی;
	int32_t m_n_بائٹیں_فی_Pixel;
} NotificationBitmap_t;

قسمتعریف ساخت CVRSettingHelper
{
	intptr_t m_pSettings; // class vr::IVRSettings *
} CVRSettingHelper;

قسمتعریف ساخت داخلہ_Analog_Action_ڈیٹا_t
{
	bool b_فعال;
	VRInput_قدر_Handle_t فعال_Origin;
	اعشاری x;
	اعشاری y;
	اعشاری z;
	اعشاری deltaX;
	اعشاری deltaY;
	اعشاری deltaZ;
	اعشاری f_Update_وقت;
} داخلہ_Analog_Action_ڈیٹا_t;

قسمتعریف ساخت داخلہ_Digital_Action_ڈیٹا_t
{
	bool b_فعال;
	VRInput_قدر_Handle_t فعال_Origin;
	bool bState;
	bool b_بدلا;
	اعشاری f_Update_وقت;
} داخلہ_Digital_Action_ڈیٹا_t;

قسمتعریف ساخت داخلہ_Pose_Action_ڈیٹا_t
{
	bool b_فعال;
	VRInput_قدر_Handle_t فعال_Origin;
	ساخت TrackedDevicePose_t pose;
} داخلہ_Pose_Action_ڈیٹا_t;

قسمتعریف ساخت داخلہ_Skeletal_Action_ڈیٹا_t
{
	bool b_فعال;
	VRInput_قدر_Handle_t فعال_Origin;
} داخلہ_Skeletal_Action_ڈیٹا_t;

قسمتعریف ساخت داخلہ_Origin_Info_t
{
	VRInput_قدر_Handle_t device_راستہ;
	Tracked_Device_اشاریہ_t tracked_Device_اشاریہ;
	حرف rchRenderModelComponentName[128]; //char[128]
} داخلہ_Origin_Info_t;

قسمتعریف ساخت داخلہ_Binding_Info_t
{
	حرف rch_Device_راستہ_Name[128]; //char[128]
	حرف rch_داخلہ_راستہ_Name[128]; //char[128]
	حرف rch_منوال_Name[128]; //char[128]
	حرف rch_خانہ_Name[128]; //char[128]
	حرف rch_داخلہ_ماخذ_Type[32]; //char[32]
} داخلہ_Binding_Info_t;

قسمتعریف ساخت VRActive_Action_سیٹ_t
{
	VRAction_سیٹ_Handle_t ul_Action_سیٹ;
	VRInput_قدر_Handle_t ul_Restricted_مقصد_Device;
	VRAction_سیٹ_Handle_t ul_Secondary_Action_سیٹ;
	uint32_t unPadding;
	int32_t n_ترجیح;
} VRActive_Action_سیٹ_t;

قسمتعریف ساخت VRSkeletal_Summary_ڈیٹا_t
{
	اعشاری flFingerCurl[5]; //float[5]
	اعشاری flFingerSplay[4]; //float[4]
} VRSkeletal_Summary_ڈیٹا_t;

قسمتعریف ساخت SpatialAnchorPose_t
{
	ساخت HmdMatrix34_t m_Anchor_مقصد_Absolute_Tracking;
} SpatialAnchorPose_t;

قسمتعریف ساخت COpenVRContext
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

قسمتعریف ساخت PropertyWrite_t
{
	شمار ETrackedDeviceProperty prop;
	شمار EPropertyWriteType writeType;
	شمار ETrackedPropertyError e_سیٹ_Error;
	خالی * pv_بفر; // void *
	uint32_t un_بفر_سائز;
	Property_Type_لیبل_t un_لیبل;
	شمار ETrackedPropertyError eError;
} PropertyWrite_t;

قسمتعریف ساخت PropertyRead_t
{
	شمار ETrackedDeviceProperty prop;
	خالی * pv_بفر; // void *
	uint32_t un_بفر_سائز;
	Property_Type_لیبل_t un_لیبل;
	uint32_t un_Required_بفر_سائز;
	شمار ETrackedPropertyError eError;
} PropertyRead_t;

قسمتعریف ساخت CVRPropertyHelpers
{
	intptr_t m_pProperties; // class vr::IVRProperties *
} CVRPropertyHelpers;

قسمتعریف ساخت راستہ_Write_t
{
	راستہ_Handle_t ul_راستہ;
	شمار EPropertyWriteType writeType;
	شمار ETrackedPropertyError e_سیٹ_Error;
	خالی * pv_بفر; // void *
	uint32_t un_بفر_سائز;
	Property_Type_لیبل_t un_لیبل;
	شمار ETrackedPropertyError eError;
	حرف * psz_راستہ; // const char *
} راستہ_Write_t;

قسمتعریف ساخت راستہ_Read_t
{
	راستہ_Handle_t ul_راستہ;
	خالی * pv_بفر; // void *
	uint32_t un_بفر_سائز;
	Property_Type_لیبل_t un_لیبل;
	uint32_t un_Required_بفر_سائز;
	شمار ETrackedPropertyError eError;
	حرف * psz_راستہ; // const char *
} راستہ_Read_t;


قسمتعریف اتحاد
{
	VREvent_Reserved_t reserved;
	VREvent_Controller_t controller;
	VREvent_Mouse_t mouse;
	VREvent_Scroll_t scroll;
	VREvent_Process_t process;
	VREvent_Notification_t notification;
	VREvent_Overlay_t overlay;
	VREvent_حالت_t حالت_2;
	VREvent_Keyboard_t keyboard;
	VREvent_Ipd_t ipd;
	VREvent_Chaperone_t chaperone;
	VREvent_PerformanceTest_t performanceTest;
	VREvent_TouchPadMove_t touchPadMove;
	VREvent_SeatedZeroPoseReset_t seatedZeroPoseReset;
	VREvent_Screenshot_t screenshot;
	VREvent_Screenshot_پیش_رفت_t screenshot_پیش_رفت;
	VREvent_ApplicationLaunch_t applicationLaunch;
	VREvent_EditingCameraSurface_t cameraSurface;
	VREvent_پیغام_Overlay_t پیغام_Overlay;
	VREvent_Property_t property;
	VREvent_HapticVibration_t hapticVibration;
	VREvent_WebConsole_t webConsole;
	VREvent_داخلہ_Binding_بھرو_t داخلہ_Binding;
	VREvent_داخلہ_Action_Manifest_بھرو_t actionManifest;
	VREvent_SpatialAnchor_t spatialAnchor;
} VREvent_ڈیٹا_t;

#اگر defined(__linux__) || defined(__APPLE__) 
// This structure was originally defined mis-packed on Linux, preserved for 
// compatibility. 
#ہدایت pack( ڈالو, 4 )
#اگر_ختم

/** An event posted by the server to all running applications */
ساخت VREvent_t
{
	uint32_t eventType; // EVREventType enum
	Tracked_Device_اشاریہ_t tracked_Device_اشاریہ;
	اعشاری eventAgeSeconds;
	// event data must be the end of the struct as its size is variable
	VREvent_ڈیٹا_t ڈیٹا;
};

#اگر defined(__linux__) || defined(__APPLE__) 
#ہدایت pack( نکالو )
#اگر_ختم


قسمتعریف اتحاد
{
	Intersection_نقاب_Rectangle_t m_Rectangle;
	Intersection_نقاب_Circle_t m_Circle;
} VROverlay_Intersection_نقاب_Primitive_ڈیٹا_t;

ساخت VROverlay_Intersection_نقاب_Primitive_t
{
	EVROverlay_Intersection_نقاب_Primitive_Type m_nPrimitiveType;
	VROverlay_Intersection_نقاب_Primitive_ڈیٹا_t m_Primitive;
};


// OpenVR Function Pointer Tables

ساخت VR_IVRSystem_Fn_جدول
{
	خالی (OPENVR_FNTABLE_CALLTYPE *Get_Recommended_Render_ہدف_سائز)(uint32_t * pn_چوڑائی, uint32_t * pn_اونچائی);
	ساخت HmdMatrix44_t (OPENVR_FNTABLE_CALLTYPE *Get_Projection_میٹرکس)(EVREye eEye, اعشاری fNearZ, اعشاری fFarZ);
	خالی (OPENVR_FNTABLE_CALLTYPE *GetProjectionRaw)(EVREye eEye, اعشاری * pf_بایاں, اعشاری * pf_دایاں, اعشاری * pf_چوٹی, اعشاری * pfBottom);
	bool (OPENVR_FNTABLE_CALLTYPE *ComputeDistortion)(EVREye eEye, اعشاری fU, اعشاری fV, ساخت DistortionCoordinates_t * pDistortionCoordinates);
	ساخت HmdMatrix34_t (OPENVR_FNTABLE_CALLTYPE *Get_Eye_مقصد_سر_Transform)(EVREye eEye);
	bool (OPENVR_FNTABLE_CALLTYPE *Get_وقت_Since_آخری_Vsync)(اعشاری * pf_Seconds_Since_آخری_Vsync, uint64_t * pul_چوکھٹا_شمار);
	int32_t (OPENVR_FNTABLE_CALLTYPE *Get_D3_D9_Adapter_اشاریہ)();
	خالی (OPENVR_FNTABLE_CALLTYPE *GetDXGIOutputInfo)(int32_t * pn_Adapter_اشاریہ);
	خالی (OPENVR_FNTABLE_CALLTYPE *GetOutputDevice)(uint64_t * pnDevice, ETextureType textureType, ساخت VkInstance_T * pInstance);
	bool (OPENVR_FNTABLE_CALLTYPE *IsDisplayOnDesktop)();
	bool (OPENVR_FNTABLE_CALLTYPE *سیٹ_Display_Visibility)(bool bIsVisibleOnDesktop);
	خالی (OPENVR_FNTABLE_CALLTYPE *Get_Device_مقصد_Absolute_Tracking_Pose)(ETrackingUniverseOrigin eOrigin, اعشاری f_Predicted_Seconds_مقصد_Photons_From_Now, ساخت TrackedDevicePose_t * pTrackedDevicePoseArray, uint32_t un_Tracked_Device_Pose_Array_گنتی);
	ساخت HmdMatrix34_t (OPENVR_FNTABLE_CALLTYPE *Get_Seated_Zero_Pose_مقصد_Standing_Absolute_Tracking_Pose)();
	ساخت HmdMatrix34_t (OPENVR_FNTABLE_CALLTYPE *Get_Raw_Zero_Pose_مقصد_Standing_Absolute_Tracking_Pose)();
	uint32_t (OPENVR_FNTABLE_CALLTYPE *Get_Sorted_Tracked_Device_Indices_کا_Class)(ETrackedDeviceClass eTrackedDeviceClass, Tracked_Device_اشاریہ_t * pun_Tracked_Device_اشاریہ_Array, uint32_t un_Tracked_Device_اشاریہ_Array_گنتی, Tracked_Device_اشاریہ_t un_Relative_مقصد_Tracked_Device_اشاریہ);
	EDeviceActivityLevel (OPENVR_FNTABLE_CALLTYPE *GetTrackedDeviceActivityLevel)(Tracked_Device_اشاریہ_t unDeviceId);
	خالی (OPENVR_FNTABLE_CALLTYPE *ApplyTransform)(ساخت TrackedDevicePose_t * pOutputPose, ساخت TrackedDevicePose_t * pTrackedDevicePose, ساخت HmdMatrix34_t * pTransform);
	Tracked_Device_اشاریہ_t (OPENVR_FNTABLE_CALLTYPE *Get_Tracked_Device_اشاریہ_For_Controller_Role)(ETrackedControllerRole unDeviceType);
	ETrackedControllerRole (OPENVR_FNTABLE_CALLTYPE *Get_Controller_Role_For_Tracked_Device_اشاریہ)(Tracked_Device_اشاریہ_t un_Device_اشاریہ);
	ETrackedDeviceClass (OPENVR_FNTABLE_CALLTYPE *GetTrackedDeviceClass)(Tracked_Device_اشاریہ_t un_Device_اشاریہ);
	bool (OPENVR_FNTABLE_CALLTYPE *IsTrackedDeviceConnected)(Tracked_Device_اشاریہ_t un_Device_اشاریہ);
	bool (OPENVR_FNTABLE_CALLTYPE *GetBoolTrackedDeviceProperty)(Tracked_Device_اشاریہ_t un_Device_اشاریہ, ETrackedDeviceProperty prop, ETrackedPropertyError * pError);
	اعشاری (OPENVR_FNTABLE_CALLTYPE *GetFloatTrackedDeviceProperty)(Tracked_Device_اشاریہ_t un_Device_اشاریہ, ETrackedDeviceProperty prop, ETrackedPropertyError * pError);
	int32_t (OPENVR_FNTABLE_CALLTYPE *GetInt32TrackedDeviceProperty)(Tracked_Device_اشاریہ_t un_Device_اشاریہ, ETrackedDeviceProperty prop, ETrackedPropertyError * pError);
	uint64_t (OPENVR_FNTABLE_CALLTYPE *GetUint64TrackedDeviceProperty)(Tracked_Device_اشاریہ_t un_Device_اشاریہ, ETrackedDeviceProperty prop, ETrackedPropertyError * pError);
	ساخت HmdMatrix34_t (OPENVR_FNTABLE_CALLTYPE *GetMatrix34TrackedDeviceProperty)(Tracked_Device_اشاریہ_t un_Device_اشاریہ, ETrackedDeviceProperty prop, ETrackedPropertyError * pError);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetArrayTrackedDeviceProperty)(Tracked_Device_اشاریہ_t un_Device_اشاریہ, ETrackedDeviceProperty prop, Property_Type_لیبل_t propType, خالی * p_بفر, uint32_t un_بفر_سائز, ETrackedPropertyError * pError);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetStringTrackedDeviceProperty)(Tracked_Device_اشاریہ_t un_Device_اشاریہ, ETrackedDeviceProperty prop, حرف * pch_قدر, uint32_t un_بفر_سائز, ETrackedPropertyError * pError);
	حرف * (OPENVR_FNTABLE_CALLTYPE *GetPropErrorNameFromEnum)(ETrackedPropertyError error);
	bool (OPENVR_FNTABLE_CALLTYPE *Poll_اگلا_Event)(ساخت VREvent_t * pEvent, uint32_t uncbVREvent);
	bool (OPENVR_FNTABLE_CALLTYPE *Poll_اگلا_Event_With_Pose)(ETrackingUniverseOrigin eOrigin, ساخت VREvent_t * pEvent, uint32_t uncbVREvent, TrackedDevicePose_t * pTrackedDevicePose);
	حرف * (OPENVR_FNTABLE_CALLTYPE *GetEventTypeNameFromEnum)(EVREventType eType);
	ساخت HiddenAreaMesh_t (OPENVR_FNTABLE_CALLTYPE *GetHiddenAreaMesh)(EVREye eEye, EHiddenAreaMeshType type);
	bool (OPENVR_FNTABLE_CALLTYPE *GetControllerState)(Tracked_Device_اشاریہ_t un_Controller_Device_اشاریہ, VRControllerState_t * pControllerState, uint32_t un_Controller_State_سائز);
	bool (OPENVR_FNTABLE_CALLTYPE *GetControllerStateWithPose)(ETrackingUniverseOrigin eOrigin, Tracked_Device_اشاریہ_t un_Controller_Device_اشاریہ, VRControllerState_t * pControllerState, uint32_t un_Controller_State_سائز, ساخت TrackedDevicePose_t * pTrackedDevicePose);
	خالی (OPENVR_FNTABLE_CALLTYPE *TriggerHapticPulse)(Tracked_Device_اشاریہ_t un_Controller_Device_اشاریہ, uint32_t unAxisId, غیرعلامتی مختصر usDurationMicroSec);
	حرف * (OPENVR_FNTABLE_CALLTYPE *GetButtonIdNameFromEnum)(EVRButtonId eButtonId);
	حرف * (OPENVR_FNTABLE_CALLTYPE *GetControllerAxisTypeNameFromEnum)(EVRControllerAxisType eAxisType);
	bool (OPENVR_FNTABLE_CALLTYPE *Is_داخلہ_دستیاب)();
	bool (OPENVR_FNTABLE_CALLTYPE *IsSteamVRDrawingControllers)();
	bool (OPENVR_FNTABLE_CALLTYPE *ShouldApplicationPause)();
	bool (OPENVR_FNTABLE_CALLTYPE *ShouldApplicationReduceRenderingWork)();
	EVRFirmwareError (OPENVR_FNTABLE_CALLTYPE *PerformFirmwareUpdate)(Tracked_Device_اشاریہ_t un_Device_اشاریہ);
	خالی (OPENVR_FNTABLE_CALLTYPE *AcknowledgeQuit_Exiting)();
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetAppContainerFilePaths)(حرف * pch_بفر, uint32_t un_بفر_سائز);
	حرف * (OPENVR_FNTABLE_CALLTYPE *Get_Runtime_نسخہ)();
};

ساخت VR_IVRExtended_Display_Fn_جدول
{
	خالی (OPENVR_FNTABLE_CALLTYPE *Get_کھڑکی_Bounds)(int32_t * pnX, int32_t * pnY, uint32_t * pn_چوڑائی, uint32_t * pn_اونچائی);
	خالی (OPENVR_FNTABLE_CALLTYPE *GetEyeOutputViewport)(EVREye eEye, uint32_t * pnX, uint32_t * pnY, uint32_t * pn_چوڑائی, uint32_t * pn_اونچائی);
	خالی (OPENVR_FNTABLE_CALLTYPE *GetDXGIOutputInfo)(int32_t * pn_Adapter_اشاریہ, int32_t * pn_Adapter_Output_اشاریہ);
};

ساخت VR_IVRTracked_Camera_Fn_جدول
{
	حرف * (OPENVR_FNTABLE_CALLTYPE *GetCameraErrorNameFromEnum)(EVRTrackedCameraError eCameraError);
	EVRTrackedCameraError (OPENVR_FNTABLE_CALLTYPE *HasCamera)(Tracked_Device_اشاریہ_t n_Device_اشاریہ, bool * pHasCamera);
	EVRTrackedCameraError (OPENVR_FNTABLE_CALLTYPE *Get_Camera_چوکھٹا_سائز)(Tracked_Device_اشاریہ_t n_Device_اشاریہ, EVRTracked_Camera_چوکھٹا_Type e_چوکھٹا_Type, uint32_t * pn_چوڑائی, uint32_t * pn_اونچائی, uint32_t * pn_چوکھٹا_بفر_سائز);
	EVRTrackedCameraError (OPENVR_FNTABLE_CALLTYPE *GetCameraIntrinsics)(Tracked_Device_اشاریہ_t n_Device_اشاریہ, uint32_t n_Camera_اشاریہ, EVRTracked_Camera_چوکھٹا_Type e_چوکھٹا_Type, HmdVector2_t * p_Focal_لمبائی, HmdVector2_t * pCenter);
	EVRTrackedCameraError (OPENVR_FNTABLE_CALLTYPE *GetCameraProjection)(Tracked_Device_اشاریہ_t n_Device_اشاریہ, uint32_t n_Camera_اشاریہ, EVRTracked_Camera_چوکھٹا_Type e_چوکھٹا_Type, اعشاری flZNear, اعشاری flZFar, HmdMatrix44_t * pProjection);
	EVRTrackedCameraError (OPENVR_FNTABLE_CALLTYPE *AcquireVideoStreamingService)(Tracked_Device_اشاریہ_t n_Device_اشاریہ, TrackedCameraHandle_t * pHandle);
	EVRTrackedCameraError (OPENVR_FNTABLE_CALLTYPE *ReleaseVideoStreamingService)(TrackedCameraHandle_t hTrackedCamera);
	EVRTrackedCameraError (OPENVR_FNTABLE_CALLTYPE *Get_Video_دھارا_چوکھٹا_بفر)(TrackedCameraHandle_t hTrackedCamera, EVRTracked_Camera_چوکھٹا_Type e_چوکھٹا_Type, خالی * p_چوکھٹا_بفر, uint32_t n_چوکھٹا_بفر_سائز, Camera_Video_دھارا_چوکھٹا_سرخی_t * p_چوکھٹا_سرخی, uint32_t n_چوکھٹا_سرخی_سائز);
	EVRTrackedCameraError (OPENVR_FNTABLE_CALLTYPE *Get_Video_دھارا_Texture_سائز)(Tracked_Device_اشاریہ_t n_Device_اشاریہ, EVRTracked_Camera_چوکھٹا_Type e_چوکھٹا_Type, VRTextureBounds_t * pTextureBounds, uint32_t * pn_چوڑائی, uint32_t * pn_اونچائی);
	EVRTrackedCameraError (OPENVR_FNTABLE_CALLTYPE *Get_Video_دھارا_Texture_D3_D11)(TrackedCameraHandle_t hTrackedCamera, EVRTracked_Camera_چوکھٹا_Type e_چوکھٹا_Type, خالی * pD3D11DeviceOrResource, خالی ** ppD3D11ShaderResourceView, Camera_Video_دھارا_چوکھٹا_سرخی_t * p_چوکھٹا_سرخی, uint32_t n_چوکھٹا_سرخی_سائز);
	EVRTrackedCameraError (OPENVR_FNTABLE_CALLTYPE *Get_Video_دھارا_Texture_GL)(TrackedCameraHandle_t hTrackedCamera, EVRTracked_Camera_چوکھٹا_Type e_چوکھٹا_Type, glUInt_t * pglTextureId, Camera_Video_دھارا_چوکھٹا_سرخی_t * p_چوکھٹا_سرخی, uint32_t n_چوکھٹا_سرخی_سائز);
	EVRTrackedCameraError (OPENVR_FNTABLE_CALLTYPE *Release_Video_دھارا_Texture_GL)(TrackedCameraHandle_t hTrackedCamera, glUInt_t glTextureId);
	خالی (OPENVR_FNTABLE_CALLTYPE *سیٹ_Camera_Tracking_Space)(ETrackingUniverseOrigin eUniverse);
	ETrackingUniverseOrigin (OPENVR_FNTABLE_CALLTYPE *GetCameraTrackingSpace)();
};

ساخت VR_IVRApplications_Fn_جدول
{
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *جوڑو_Application_Manifest)(حرف * pch_Application_Manifest_بھرا_راستہ, bool bTemporary);
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *RemoveApplicationManifest)(حرف * pch_Application_Manifest_بھرا_راستہ);
	bool (OPENVR_FNTABLE_CALLTYPE *IsApplicationInstalled)(حرف * pch_App_کلید);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *Get_Application_گنتی)();
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *Get_Application_کلید_By_اشاریہ)(uint32_t un_Application_اشاریہ, حرف * pch_App_کلید_بفر, uint32_t un_App_کلید_بفر_Len);
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *Get_Application_کلید_By_Process_Id)(uint32_t unProcessId, حرف * pch_App_کلید_بفر, uint32_t un_App_کلید_بفر_Len);
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *LaunchApplication)(حرف * pch_App_کلید);
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *LaunchTemplateApplication)(حرف * pch_Template_App_کلید, حرف * pch_New_App_کلید, ساخت App_Override_کلیدیں_t * p_کلیدیں, uint32_t un_کلیدیں);
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *LaunchApplicationFromMimeType)(حرف * pchMimeType, حرف * pch_دلائل);
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *LaunchDashboardOverlay)(حرف * pch_App_کلید);
	bool (OPENVR_FNTABLE_CALLTYPE *CancelApplicationLaunch)(حرف * pch_App_کلید);
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *IdentifyApplication)(uint32_t unProcessId, حرف * pch_App_کلید);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetApplicationProcessId)(حرف * pch_App_کلید);
	حرف * (OPENVR_FNTABLE_CALLTYPE *GetApplicationsErrorNameFromEnum)(EVRApplicationError error);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetApplicationPropertyString)(حرف * pch_App_کلید, EVRApplicationProperty eProperty, حرف * pch_Property_قدر_بفر, uint32_t un_Property_قدر_بفر_Len, EVRApplicationError * peError);
	bool (OPENVR_FNTABLE_CALLTYPE *GetApplicationPropertyBool)(حرف * pch_App_کلید, EVRApplicationProperty eProperty, EVRApplicationError * peError);
	uint64_t (OPENVR_FNTABLE_CALLTYPE *GetApplicationPropertyUint64)(حرف * pch_App_کلید, EVRApplicationProperty eProperty, EVRApplicationError * peError);
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *سیٹ_Application_Auto_Launch)(حرف * pch_App_کلید, bool bAutoLaunch);
	bool (OPENVR_FNTABLE_CALLTYPE *GetApplicationAutoLaunch)(حرف * pch_App_کلید);
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *سیٹ_Default_Application_For_Mime_Type)(حرف * pch_App_کلید, حرف * pchMimeType);
	bool (OPENVR_FNTABLE_CALLTYPE *GetDefaultApplicationForMimeType)(حرف * pchMimeType, حرف * pch_App_کلید_بفر, uint32_t un_App_کلید_بفر_Len);
	bool (OPENVR_FNTABLE_CALLTYPE *GetApplicationSupportedMimeTypes)(حرف * pch_App_کلید, حرف * pch_Mime_Types_بفر, uint32_t un_Mime_Types_بفر);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetApplicationsThatSupportMimeType)(حرف * pchMimeType, حرف * pch_App_کلیدیں_That_Support_بفر, uint32_t un_App_کلیدیں_That_Support_بفر);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetApplicationLaunchArguments)(uint32_t unHandle, حرف * pch_دلائل, uint32_t un_دلائل);
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *GetStartingApplication)(حرف * pch_App_کلید_بفر, uint32_t un_App_کلید_بفر_Len);
	EVRSceneApplicationState (OPENVR_FNTABLE_CALLTYPE *GetSceneApplicationState)();
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *PerformApplicationPrelaunchCheck)(حرف * pch_App_کلید);
	حرف * (OPENVR_FNTABLE_CALLTYPE *GetSceneApplicationStateNameFromEnum)(EVRSceneApplicationState state);
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *Launch_اندرونی_Process)(حرف * pch_ثنائی_راستہ, حرف * pchArguments, حرف * pchWorkingDirectory);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetCurrentSceneProcessId)();
};

ساخت VR_IVRChaperone_Fn_جدول
{
	ChaperoneCalibrationState (OPENVR_FNTABLE_CALLTYPE *GetCalibrationState)();
	bool (OPENVR_FNTABLE_CALLTYPE *Get_Play_Area_سائز)(اعشاری * p_سائز_X, اعشاری * p_سائز_Z);
	bool (OPENVR_FNTABLE_CALLTYPE *GetPlayAreaRect)(ساخت HmdQuad_t * rect);
	خالی (OPENVR_FNTABLE_CALLTYPE *ReloadInfo)();
	خالی (OPENVR_FNTABLE_CALLTYPE *سیٹ_Scene_Color)(ساخت HmdColor_t color);
	خالی (OPENVR_FNTABLE_CALLTYPE *GetBoundsColor)(ساخت HmdColor_t * pOutputColorArray, صحیح n_عدد_Output_Colors, اعشاری fl_Collision_Bounds_Fade_فاصلہ, ساخت HmdColor_t * pOutputCameraColor);
	bool (OPENVR_FNTABLE_CALLTYPE *AreBoundsVisible)();
	خالی (OPENVR_FNTABLE_CALLTYPE *ForceBoundsVisible)(bool bForce);
	خالی (OPENVR_FNTABLE_CALLTYPE *ResetZeroPose)(ETrackingUniverseOrigin eTrackingUniverseOrigin);
};

ساخت VR_IVRChaperone_تیاری_Fn_جدول
{
	bool (OPENVR_FNTABLE_CALLTYPE *CommitWorkingCopy)(EChaperoneConfigFile configFile);
	خالی (OPENVR_FNTABLE_CALLTYPE *RevertWorkingCopy)();
	bool (OPENVR_FNTABLE_CALLTYPE *Get_Working_Play_Area_سائز)(اعشاری * p_سائز_X, اعشاری * p_سائز_Z);
	bool (OPENVR_FNTABLE_CALLTYPE *GetWorkingPlayAreaRect)(ساخت HmdQuad_t * rect);
	bool (OPENVR_FNTABLE_CALLTYPE *GetWorkingCollisionBoundsInfo)(ساخت HmdQuad_t * p_Quads_بفر, uint32_t * pun_Quads_گنتی);
	bool (OPENVR_FNTABLE_CALLTYPE *Get_زندہ_Collision_Bounds_Info)(ساخت HmdQuad_t * p_Quads_بفر, uint32_t * pun_Quads_گنتی);
	bool (OPENVR_FNTABLE_CALLTYPE *Get_Working_Seated_Zero_Pose_مقصد_Raw_Tracking_Pose)(ساخت HmdMatrix34_t * pmat_Seated_Zero_Pose_مقصد_Raw_Tracking_Pose);
	bool (OPENVR_FNTABLE_CALLTYPE *Get_Working_Standing_Zero_Pose_مقصد_Raw_Tracking_Pose)(ساخت HmdMatrix34_t * pmat_Standing_Zero_Pose_مقصد_Raw_Tracking_Pose);
	خالی (OPENVR_FNTABLE_CALLTYPE *سیٹ_Working_Play_Area_سائز)(اعشاری سائز_X, اعشاری سائز_Z);
	خالی (OPENVR_FNTABLE_CALLTYPE *سیٹ_Working_Collision_Bounds_Info)(ساخت HmdQuad_t * p_Quads_بفر, uint32_t un_Quads_گنتی);
	خالی (OPENVR_FNTABLE_CALLTYPE *سیٹ_Working_Perimeter)(ساخت HmdVector2_t * p_نقطہ_بفر, uint32_t un_نقطہ_گنتی);
	خالی (OPENVR_FNTABLE_CALLTYPE *سیٹ_Working_Seated_Zero_Pose_مقصد_Raw_Tracking_Pose)(ساخت HmdMatrix34_t * p_Mat_Seated_Zero_Pose_مقصد_Raw_Tracking_Pose);
	خالی (OPENVR_FNTABLE_CALLTYPE *سیٹ_Working_Standing_Zero_Pose_مقصد_Raw_Tracking_Pose)(ساخت HmdMatrix34_t * p_Mat_Standing_Zero_Pose_مقصد_Raw_Tracking_Pose);
	خالی (OPENVR_FNTABLE_CALLTYPE *ReloadFromDisk)(EChaperoneConfigFile configFile);
	bool (OPENVR_FNTABLE_CALLTYPE *Get_زندہ_Seated_Zero_Pose_مقصد_Raw_Tracking_Pose)(ساخت HmdMatrix34_t * pmat_Seated_Zero_Pose_مقصد_Raw_Tracking_Pose);
	bool (OPENVR_FNTABLE_CALLTYPE *Export_زندہ_مقصد_بفر)(حرف * p_بفر, uint32_t * pn_بفر_لمبائی);
	bool (OPENVR_FNTABLE_CALLTYPE *Import_From_بفر_مقصد_Working)(حرف * p_بفر, uint32_t nImportFlags);
	خالی (OPENVR_FNTABLE_CALLTYPE *Show_Working_سیٹ_Preview)();
	خالی (OPENVR_FNTABLE_CALLTYPE *Hide_Working_سیٹ_Preview)();
	خالی (OPENVR_FNTABLE_CALLTYPE *گنجائش_تیاری_Starting)();
};

ساخت VR_IVRCompositor_Fn_جدول
{
	خالی (OPENVR_FNTABLE_CALLTYPE *سیٹ_Tracking_Space)(ETrackingUniverseOrigin eOrigin);
	ETrackingUniverseOrigin (OPENVR_FNTABLE_CALLTYPE *GetTrackingSpace)();
	EVRCompositorError (OPENVR_FNTABLE_CALLTYPE *WaitGetPoses)(ساخت TrackedDevicePose_t * pRenderPoseArray, uint32_t un_Render_Pose_Array_گنتی, ساخت TrackedDevicePose_t * pGamePoseArray, uint32_t un_Game_Pose_Array_گنتی);
	EVRCompositorError (OPENVR_FNTABLE_CALLTYPE *Get_آخری_Poses)(ساخت TrackedDevicePose_t * pRenderPoseArray, uint32_t un_Render_Pose_Array_گنتی, ساخت TrackedDevicePose_t * pGamePoseArray, uint32_t un_Game_Pose_Array_گنتی);
	EVRCompositorError (OPENVR_FNTABLE_CALLTYPE *Get_آخری_Pose_For_Tracked_Device_اشاریہ)(Tracked_Device_اشاریہ_t un_Device_اشاریہ, ساخت TrackedDevicePose_t * pOutputPose, ساخت TrackedDevicePose_t * pOutputGamePose);
	EVRCompositorError (OPENVR_FNTABLE_CALLTYPE *Submit)(EVREye eEye, ساخت Texture_t * pTexture, ساخت VRTextureBounds_t * pBounds, EVRSubmitFlags nSubmitFlags);
	خالی (OPENVR_FNTABLE_CALLTYPE *Clear_آخری_Submitted_چوکھٹا)();
	خالی (OPENVR_FNTABLE_CALLTYPE *PostPresentHandoff)();
	bool (OPENVR_FNTABLE_CALLTYPE *Get_چوکھٹا_Timing)(ساخت Compositor_چوکھٹا_Timing * pTiming, uint32_t un_چوکھٹے_Ago);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *Get_چوکھٹا_Timings)(ساخت Compositor_چوکھٹا_Timing * pTiming, uint32_t n_چوکھٹے);
	اعشاری (OPENVR_FNTABLE_CALLTYPE *Get_چوکھٹا_وقت_بقایا)();
	خالی (OPENVR_FNTABLE_CALLTYPE *GetCumulativeStats)(ساخت Compositor_CumulativeStats * pStats, uint32_t n_Stats_سائز_اندر_بائٹیں);
	خالی (OPENVR_FNTABLE_CALLTYPE *Fade_مقصد_Color)(اعشاری fSeconds, اعشاری fRed, اعشاری fGreen, اعشاری fBlue, اعشاری fAlpha, bool bBackground);
	ساخت HmdColor_t (OPENVR_FNTABLE_CALLTYPE *GetCurrentFadeColor)(bool bBackground);
	خالی (OPENVR_FNTABLE_CALLTYPE *FadeGrid)(اعشاری fSeconds, bool b_Fade_Grid_اندر);
	اعشاری (OPENVR_FNTABLE_CALLTYPE *GetCurrentGridAlpha)();
	EVRCompositorError (OPENVR_FNTABLE_CALLTYPE *سیٹ_Skybox_Override)(ساخت Texture_t * pTextures, uint32_t un_Texture_گنتی);
	خالی (OPENVR_FNTABLE_CALLTYPE *ClearSkyboxOverride)();
	خالی (OPENVR_FNTABLE_CALLTYPE *Compositor_Bring_مقصد_Front)();
	خالی (OPENVR_FNTABLE_CALLTYPE *Compositor_Go_مقصد_عقب)();
	خالی (OPENVR_FNTABLE_CALLTYPE *CompositorQuit)();
	bool (OPENVR_FNTABLE_CALLTYPE *IsFullscreen)();
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetCurrentSceneFocusProcess)();
	uint32_t (OPENVR_FNTABLE_CALLTYPE *Get_آخری_چوکھٹا_Renderer)();
	bool (OPENVR_FNTABLE_CALLTYPE *CanRenderScene)();
	خالی (OPENVR_FNTABLE_CALLTYPE *Show_Mirror_کھڑکی)();
	خالی (OPENVR_FNTABLE_CALLTYPE *Hide_Mirror_کھڑکی)();
	bool (OPENVR_FNTABLE_CALLTYPE *Is_Mirror_کھڑکی_Visible)();
	خالی (OPENVR_FNTABLE_CALLTYPE *CompositorDumpImages)();
	bool (OPENVR_FNTABLE_CALLTYPE *Should_App_Render_With_کم_Resources)();
	خالی (OPENVR_FNTABLE_CALLTYPE *ForceInterleavedReprojectionOn)(bool bOverride);
	خالی (OPENVR_FNTABLE_CALLTYPE *ForceReconnectProcess)();
	خالی (OPENVR_FNTABLE_CALLTYPE *SuspendRendering)(bool bSuspend);
	EVRCompositorError (OPENVR_FNTABLE_CALLTYPE *GetMirrorTextureD3D11)(EVREye eEye, خالی * pD3D11DeviceOrResource, خالی ** ppD3D11ShaderResourceView);
	خالی (OPENVR_FNTABLE_CALLTYPE *ReleaseMirrorTextureD3D11)(خالی * pD3D11ShaderResourceView);
	EVRCompositorError (OPENVR_FNTABLE_CALLTYPE *GetMirrorTextureGL)(EVREye eEye, glUInt_t * pglTextureId, glSharedTextureHandle_t * pglSharedTextureHandle);
	bool (OPENVR_FNTABLE_CALLTYPE *ReleaseSharedGLTexture)(glUInt_t glTextureId, glSharedTextureHandle_t glSharedTextureHandle);
	خالی (OPENVR_FNTABLE_CALLTYPE *تالا_GLShared_Texture_For_Access)(glSharedTextureHandle_t glSharedTextureHandle);
	خالی (OPENVR_FNTABLE_CALLTYPE *UnlockGLSharedTextureForAccess)(glSharedTextureHandle_t glSharedTextureHandle);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetVulkanInstanceExtensionsRequired)(حرف * pch_قدر, uint32_t un_بفر_سائز);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetVulkanDeviceExtensionsRequired)(ساخت VkPhysicalDevice_T * pPhysicalDevice, حرف * pch_قدر, uint32_t un_بفر_سائز);
	خالی (OPENVR_FNTABLE_CALLTYPE *سیٹ_Explicit_Timing_منوال)(EVRCompositor_Timing_منوال e_Timing_منوال);
	EVRCompositorError (OPENVR_FNTABLE_CALLTYPE *Submit_Explicit_Timing_ڈیٹا)();
	bool (OPENVR_FNTABLE_CALLTYPE *IsMotionSmoothingEnabled)();
	bool (OPENVR_FNTABLE_CALLTYPE *IsMotionSmoothingSupported)();
	bool (OPENVR_FNTABLE_CALLTYPE *IsCurrentSceneFocusAppLoading)();
	EVRCompositorError (OPENVR_FNTABLE_CALLTYPE *سیٹ_Stage_Override_Async)(حرف * pch_Render_Model_راستہ, ساخت HmdMatrix34_t * pTransform, ساخت Compositor_StageRenderSettings * pRenderSettings, uint32_t n_سائز_کا_Render_Settings);
	خالی (OPENVR_FNTABLE_CALLTYPE *ClearStageOverride)();
	bool (OPENVR_FNTABLE_CALLTYPE *GetCompositorBenchmarkResults)(ساخت Compositor_BenchmarkResults * pBenchmarkResults, uint32_t n_سائز_کا_Benchmark_Results);
	EVRCompositorError (OPENVR_FNTABLE_CALLTYPE *Get_آخری_Pose_Prediction_IDs)(uint32_t * pRenderPosePredictionID, uint32_t * pGamePosePredictionID);
	EVRCompositorError (OPENVR_FNTABLE_CALLTYPE *Get_Poses_For_چوکھٹا)(uint32_t unPosePredictionID, ساخت TrackedDevicePose_t * pPoseArray, uint32_t un_Pose_Array_گنتی);
};

ساخت VR_IVROverlay_Fn_جدول
{
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *ڈھونڈو_Overlay)(حرف * pch_Overlay_کلید, VROverlayHandle_t * pOverlayHandle);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *CreateOverlay)(حرف * pch_Overlay_کلید, حرف * pchOverlayName, VROverlayHandle_t * pOverlayHandle);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *DestroyOverlay)(VROverlayHandle_t ulOverlayHandle);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *Get_Overlay_کلید)(VROverlayHandle_t ulOverlayHandle, حرف * pch_قدر, uint32_t un_بفر_سائز, EVROverlayError * pError);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetOverlayName)(VROverlayHandle_t ulOverlayHandle, حرف * pch_قدر, uint32_t un_بفر_سائز, EVROverlayError * pError);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *سیٹ_Overlay_Name)(VROverlayHandle_t ulOverlayHandle, حرف * pchName);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *Get_Overlay_Image_ڈیٹا)(VROverlayHandle_t ulOverlayHandle, خالی * pv_بفر, uint32_t un_بفر_سائز, uint32_t * pun_چوڑائی, uint32_t * pun_اونچائی);
	حرف * (OPENVR_FNTABLE_CALLTYPE *GetOverlayErrorNameFromEnum)(EVROverlayError error);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *سیٹ_Overlay_Rendering_Pid)(VROverlayHandle_t ulOverlayHandle, uint32_t unPID);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetOverlayRenderingPid)(VROverlayHandle_t ulOverlayHandle);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *سیٹ_Overlay_Flag)(VROverlayHandle_t ulOverlayHandle, VROverlayFlags eOverlayFlag, bool bEnabled);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayFlag)(VROverlayHandle_t ulOverlayHandle, VROverlayFlags eOverlayFlag, bool * pbEnabled);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayFlags)(VROverlayHandle_t ulOverlayHandle, uint32_t * pFlags);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *سیٹ_Overlay_Color)(VROverlayHandle_t ulOverlayHandle, اعشاری fRed, اعشاری fGreen, اعشاری fBlue);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayColor)(VROverlayHandle_t ulOverlayHandle, اعشاری * pfRed, اعشاری * pfGreen, اعشاری * pfBlue);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *سیٹ_Overlay_Alpha)(VROverlayHandle_t ulOverlayHandle, اعشاری fAlpha);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayAlpha)(VROverlayHandle_t ulOverlayHandle, اعشاری * pfAlpha);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *سیٹ_Overlay_Texel_Aspect)(VROverlayHandle_t ulOverlayHandle, اعشاری fTexelAspect);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayTexelAspect)(VROverlayHandle_t ulOverlayHandle, اعشاری * pfTexelAspect);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *سیٹ_Overlay_ترتیب_دو_ترتیب)(VROverlayHandle_t ulOverlayHandle, uint32_t un_ترتیب_دو_ترتیب);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *Get_Overlay_ترتیب_دو_ترتیب)(VROverlayHandle_t ulOverlayHandle, uint32_t * pun_ترتیب_دو_ترتیب);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *سیٹ_Overlay_چوڑائی_اندر_Meters)(VROverlayHandle_t ulOverlayHandle, اعشاری f_چوڑائی_اندر_Meters);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *Get_Overlay_چوڑائی_اندر_Meters)(VROverlayHandle_t ulOverlayHandle, اعشاری * pf_چوڑائی_اندر_Meters);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *سیٹ_Overlay_Curvature)(VROverlayHandle_t ulOverlayHandle, اعشاری fCurvature);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayCurvature)(VROverlayHandle_t ulOverlayHandle, اعشاری * pfCurvature);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *سیٹ_Overlay_Pre_خم_Pitch)(VROverlayHandle_t ulOverlayHandle, اعشاری fRadians);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *Get_Overlay_Pre_خم_Pitch)(VROverlayHandle_t ulOverlayHandle, اعشاری * pfRadians);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *سیٹ_Overlay_Texture_Color_Space)(VROverlayHandle_t ulOverlayHandle, EColorSpace eTextureColorSpace);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayTextureColorSpace)(VROverlayHandle_t ulOverlayHandle, EColorSpace * peTextureColorSpace);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *سیٹ_Overlay_Texture_Bounds)(VROverlayHandle_t ulOverlayHandle, ساخت VRTextureBounds_t * pOverlayTextureBounds);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayTextureBounds)(VROverlayHandle_t ulOverlayHandle, ساخت VRTextureBounds_t * pOverlayTextureBounds);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayTransformType)(VROverlayHandle_t ulOverlayHandle, VROverlayTransformType * peTransformType);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *سیٹ_Overlay_Transform_Absolute)(VROverlayHandle_t ulOverlayHandle, ETrackingUniverseOrigin eTrackingOrigin, ساخت HmdMatrix34_t * pmat_Tracking_Origin_مقصد_Overlay_Transform);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayTransformAbsolute)(VROverlayHandle_t ulOverlayHandle, ETrackingUniverseOrigin * peTrackingOrigin, ساخت HmdMatrix34_t * pmat_Tracking_Origin_مقصد_Overlay_Transform);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *سیٹ_Overlay_Transform_Tracked_Device_Relative)(VROverlayHandle_t ulOverlayHandle, Tracked_Device_اشاریہ_t unTrackedDevice, ساخت HmdMatrix34_t * pmat_Tracked_Device_مقصد_Overlay_Transform);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayTransformTrackedDeviceRelative)(VROverlayHandle_t ulOverlayHandle, Tracked_Device_اشاریہ_t * punTrackedDevice, ساخت HmdMatrix34_t * pmat_Tracked_Device_مقصد_Overlay_Transform);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *سیٹ_Overlay_Transform_Tracked_Device_Component)(VROverlayHandle_t ulOverlayHandle, Tracked_Device_اشاریہ_t un_Device_اشاریہ, حرف * pchComponentName);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayTransformTrackedDeviceComponent)(VROverlayHandle_t ulOverlayHandle, Tracked_Device_اشاریہ_t * pun_Device_اشاریہ, حرف * pchComponentName, uint32_t un_Component_Name_سائز);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayTransformOverlayRelative)(VROverlayHandle_t ulOverlayHandle, VROverlayHandle_t * ul_Overlay_Handle_والد, ساخت HmdMatrix34_t * pmat_والد_Overlay_مقصد_Overlay_Transform);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *سیٹ_Overlay_Transform_Overlay_Relative)(VROverlayHandle_t ulOverlayHandle, VROverlayHandle_t ul_Overlay_Handle_والد, ساخت HmdMatrix34_t * pmat_والد_Overlay_مقصد_Overlay_Transform);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *سیٹ_Overlay_Transform_Cursor)(VROverlayHandle_t ulCursorOverlayHandle, ساخت HmdVector2_t * pvHotspot);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayTransformCursor)(VROverlayHandle_t ulOverlayHandle, ساخت HmdVector2_t * pvHotspot);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *سیٹ_Overlay_Transform_Projection)(VROverlayHandle_t ulOverlayHandle, ETrackingUniverseOrigin eTrackingOrigin, ساخت HmdMatrix34_t * pmat_Tracking_Origin_مقصد_Overlay_Transform, ساخت VROverlayProjection_t * pProjection, EVREye eEye);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *ShowOverlay)(VROverlayHandle_t ulOverlayHandle);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *HideOverlay)(VROverlayHandle_t ulOverlayHandle);
	bool (OPENVR_FNTABLE_CALLTYPE *IsOverlayVisible)(VROverlayHandle_t ulOverlayHandle);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetTransformForOverlayCoordinates)(VROverlayHandle_t ulOverlayHandle, ETrackingUniverseOrigin eTrackingOrigin, ساخت HmdVector2_t coordinates_اندر_Overlay, ساخت HmdMatrix34_t * pmatTransform);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *Wait_چوکھٹا_Sync)(uint32_t nTimeoutMs);
	bool (OPENVR_FNTABLE_CALLTYPE *Poll_اگلا_Overlay_Event)(VROverlayHandle_t ulOverlayHandle, ساخت VREvent_t * pEvent, uint32_t uncbVREvent);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *Get_Overlay_داخلہ_طریقہ)(VROverlayHandle_t ulOverlayHandle, VROverlay_داخلہ_طریقہ * pe_داخلہ_طریقہ);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *سیٹ_Overlay_داخلہ_طریقہ)(VROverlayHandle_t ulOverlayHandle, VROverlay_داخلہ_طریقہ e_داخلہ_طریقہ);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayMouseScale)(VROverlayHandle_t ulOverlayHandle, ساخت HmdVector2_t * pvecMouseScale);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *سیٹ_Overlay_Mouse_Scale)(VROverlayHandle_t ulOverlayHandle, ساخت HmdVector2_t * pvecMouseScale);
	bool (OPENVR_FNTABLE_CALLTYPE *ComputeOverlayIntersection)(VROverlayHandle_t ulOverlayHandle, ساخت VROverlayIntersectionParams_t * pParams, ساخت VROverlayIntersectionResults_t * pResults);
	bool (OPENVR_FNTABLE_CALLTYPE *Is_Hover_ہدف_Overlay)(VROverlayHandle_t ulOverlayHandle);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *سیٹ_Overlay_Intersection_نقاب)(VROverlayHandle_t ulOverlayHandle, ساخت VROverlay_Intersection_نقاب_Primitive_t * p_نقاب_Primitives, uint32_t un_عدد_نقاب_Primitives, uint32_t un_Primitive_سائز);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *TriggerLaserMouseHapticVibration)(VROverlayHandle_t ulOverlayHandle, اعشاری fDurationSeconds, اعشاری fFrequency, اعشاری fAmplitude);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *سیٹ_Overlay_Cursor)(VROverlayHandle_t ulOverlayHandle, VROverlayHandle_t ulCursorHandle);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *سیٹ_Overlay_Cursor_Position_Override)(VROverlayHandle_t ulOverlayHandle, ساخت HmdVector2_t * pvCursor);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *ClearOverlayCursorPositionOverride)(VROverlayHandle_t ulOverlayHandle);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *سیٹ_Overlay_Texture)(VROverlayHandle_t ulOverlayHandle, ساخت Texture_t * pTexture);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *ClearOverlayTexture)(VROverlayHandle_t ulOverlayHandle);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *سیٹ_Overlay_Raw)(VROverlayHandle_t ulOverlayHandle, خالی * pv_بفر, uint32_t un_چوڑائی, uint32_t un_اونچائی, uint32_t un_بائٹیں_فی_Pixel);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *سیٹ_Overlay_From_File)(VROverlayHandle_t ulOverlayHandle, حرف * pch_File_راستہ);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayTexture)(VROverlayHandle_t ulOverlayHandle, خالی ** pNativeTextureHandle, خالی * pNativeTextureRef, uint32_t * p_چوڑائی, uint32_t * p_اونچائی, uint32_t * pNativeFormat, ETextureType * pAPIType, EColorSpace * pColorSpace, ساخت VRTextureBounds_t * pTextureBounds);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *ReleaseNativeOverlayHandle)(VROverlayHandle_t ulOverlayHandle, خالی * pNativeTextureHandle);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *Get_Overlay_Texture_سائز)(VROverlayHandle_t ulOverlayHandle, uint32_t * p_چوڑائی, uint32_t * p_اونچائی);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *CreateDashboardOverlay)(حرف * pch_Overlay_کلید, حرف * pchOverlayFriendlyName, VROverlayHandle_t * pMainHandle, VROverlayHandle_t * pThumbnailHandle);
	bool (OPENVR_FNTABLE_CALLTYPE *IsDashboardVisible)();
	bool (OPENVR_FNTABLE_CALLTYPE *Is_فعال_Dashboard_Overlay)(VROverlayHandle_t ulOverlayHandle);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *سیٹ_Dashboard_Overlay_Scene_Process)(VROverlayHandle_t ulOverlayHandle, uint32_t unProcessId);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetDashboardOverlaySceneProcess)(VROverlayHandle_t ulOverlayHandle, uint32_t * punProcessId);
	خالی (OPENVR_FNTABLE_CALLTYPE *ShowDashboard)(حرف * pch_Overlay_مقصد_Show);
	Tracked_Device_اشاریہ_t (OPENVR_FNTABLE_CALLTYPE *GetPrimaryDashboardDevice)();
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *ShowKeyboard)(EGamepad_متن_داخلہ_منوال e_داخلہ_منوال, EGamepad_متن_داخلہ_سطر_منوال e_سطر_داخلہ_منوال, uint32_t unFlags, حرف * pchDescription, uint32_t unCharMax, حرف * pch_Existing_متن, uint64_t u_User_قدر);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *ShowKeyboardForOverlay)(VROverlayHandle_t ulOverlayHandle, EGamepad_متن_داخلہ_منوال e_داخلہ_منوال, EGamepad_متن_داخلہ_سطر_منوال e_سطر_داخلہ_منوال, uint32_t unFlags, حرف * pchDescription, uint32_t unCharMax, حرف * pch_Existing_متن, uint64_t u_User_قدر);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *Get_Keyboard_متن)(حرف * pch_متن, uint32_t cch_متن);
	خالی (OPENVR_FNTABLE_CALLTYPE *HideKeyboard)();
	خالی (OPENVR_FNTABLE_CALLTYPE *سیٹ_Keyboard_Transform_Absolute)(ETrackingUniverseOrigin eTrackingOrigin, ساخت HmdMatrix34_t * pmat_Tracking_Origin_مقصد_Keyboard_Transform);
	خالی (OPENVR_FNTABLE_CALLTYPE *سیٹ_Keyboard_Position_For_Overlay)(VROverlayHandle_t ulOverlayHandle, ساخت HmdRect2_t avoidRect);
	VRMessageOverlayResponse (OPENVR_FNTABLE_CALLTYPE *Show_پیغام_Overlay)(حرف * pch_متن, حرف * pchCaption, حرف * pch_Button0_متن, حرف * pch_Button1_متن, حرف * pch_Button2_متن, حرف * pch_Button3_متن);
	خالی (OPENVR_FNTABLE_CALLTYPE *Close_پیغام_Overlay)();
};

ساخت VR_IVROverlay_View_Fn_جدول
{
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *AcquireOverlayView)(VROverlayHandle_t ulOverlayHandle, ساخت VRNativeDevice_t * pNativeDevice, ساخت VROverlayView_t * pOverlayView, uint32_t un_Overlay_View_سائز);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *ReleaseOverlayView)(ساخت VROverlayView_t * pOverlayView);
	خالی (OPENVR_FNTABLE_CALLTYPE *PostOverlayEvent)(VROverlayHandle_t ulOverlayHandle, ساخت VREvent_t * pvrEvent);
	bool (OPENVR_FNTABLE_CALLTYPE *IsViewingPermitted)(VROverlayHandle_t ulOverlayHandle);
};

ساخت VR_IVRHeadset_View_Fn_جدول
{
	خالی (OPENVR_FNTABLE_CALLTYPE *سیٹ_Headset_View_سائز)(uint32_t n_چوڑائی, uint32_t n_اونچائی);
	خالی (OPENVR_FNTABLE_CALLTYPE *Get_Headset_View_سائز)(uint32_t * pn_چوڑائی, uint32_t * pn_اونچائی);
	خالی (OPENVR_FNTABLE_CALLTYPE *سیٹ_Headset_View_منوال)(Headset_View_منوال_t e_Headset_View_منوال);
	Headset_View_منوال_t (OPENVR_FNTABLE_CALLTYPE *Get_Headset_View_منوال)();
	خالی (OPENVR_FNTABLE_CALLTYPE *سیٹ_Headset_View_Cropped)(bool bCropped);
	bool (OPENVR_FNTABLE_CALLTYPE *GetHeadsetViewCropped)();
	اعشاری (OPENVR_FNTABLE_CALLTYPE *Get_Headset_View_Aspect_تناسب)();
	خالی (OPENVR_FNTABLE_CALLTYPE *سیٹ_Headset_View_Blend_Range)(اعشاری fl_آغاز_Pct, اعشاری fl_انتہا_Pct);
	خالی (OPENVR_FNTABLE_CALLTYPE *GetHeadsetViewBlendRange)(اعشاری * p_آغاز_Pct, اعشاری * p_انتہا_Pct);
};

ساخت VR_IVRRender_Models_Fn_جدول
{
	EVRRenderModelError (OPENVR_FNTABLE_CALLTYPE *بھرو_Render_Model_Async)(حرف * pchRenderModelName, ساخت RenderModel_t ** ppRenderModel);
	خالی (OPENVR_FNTABLE_CALLTYPE *FreeRenderModel)(ساخت RenderModel_t * pRenderModel);
	EVRRenderModelError (OPENVR_FNTABLE_CALLTYPE *بھرو_Texture_Async)(TextureID_t textureId, ساخت RenderModel_TextureMap_t ** ppTexture);
	خالی (OPENVR_FNTABLE_CALLTYPE *FreeTexture)(ساخت RenderModel_TextureMap_t * pTexture);
	EVRRenderModelError (OPENVR_FNTABLE_CALLTYPE *بھرو_Texture_D3_D11_Async)(TextureID_t textureId, خالی * pD3D11Device, خالی ** ppD3D11Texture2D);
	EVRRenderModelError (OPENVR_FNTABLE_CALLTYPE *بھرو_Into_Texture_D3_D11_Async)(TextureID_t textureId, خالی * pDstTexture);
	خالی (OPENVR_FNTABLE_CALLTYPE *FreeTextureD3D11)(خالی * pD3D11Texture2D);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetRenderModelName)(uint32_t un_Render_Model_اشاریہ, حرف * pchRenderModelName, uint32_t unRenderModelNameLen);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *Get_Render_Model_گنتی)();
	uint32_t (OPENVR_FNTABLE_CALLTYPE *Get_Component_گنتی)(حرف * pchRenderModelName);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetComponentName)(حرف * pchRenderModelName, uint32_t un_Component_اشاریہ, حرف * pchComponentName, uint32_t unComponentNameLen);
	uint64_t (OPENVR_FNTABLE_CALLTYPE *Get_Component_Button_نقاب)(حرف * pchRenderModelName, حرف * pchComponentName);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetComponentRenderModelName)(حرف * pchRenderModelName, حرف * pchComponentName, حرف * pchComponentRenderModelName, uint32_t unComponentRenderModelNameLen);
	bool (OPENVR_FNTABLE_CALLTYPE *Get_Component_State_For_Device_راستہ)(حرف * pchRenderModelName, حرف * pchComponentName, VRInput_قدر_Handle_t device_راستہ, Render_Model_Controller_منوال_State_t * pState, RenderModel_ComponentState_t * pComponentState);
	bool (OPENVR_FNTABLE_CALLTYPE *GetComponentState)(حرف * pchRenderModelName, حرف * pchComponentName, VRControllerState_t * pControllerState, ساخت Render_Model_Controller_منوال_State_t * pState, ساخت RenderModel_ComponentState_t * pComponentState);
	bool (OPENVR_FNTABLE_CALLTYPE *RenderModelHasComponent)(حرف * pchRenderModelName, حرف * pchComponentName);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetRenderModelThumbnailURL)(حرف * pchRenderModelName, حرف * pchThumbnailURL, uint32_t unThumbnailURLLen, EVRRenderModelError * peError);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *Get_Render_Model_Original_راستہ)(حرف * pchRenderModelName, حرف * pch_Original_راستہ, uint32_t un_Original_راستہ_Len, EVRRenderModelError * peError);
	حرف * (OPENVR_FNTABLE_CALLTYPE *GetRenderModelErrorNameFromEnum)(EVRRenderModelError error);
};

ساخت VR_IVRNotifications_Fn_جدول
{
	EVRNotificationError (OPENVR_FNTABLE_CALLTYPE *CreateNotification)(VROverlayHandle_t ulOverlayHandle, uint64_t ul_User_قدر, EVRNotificationType type, حرف * pch_متن, EVRNotificationStyle style, ساخت NotificationBitmap_t * pImage, VRNotificationId * pNotificationId);
	EVRNotificationError (OPENVR_FNTABLE_CALLTYPE *RemoveNotification)(VRNotificationId notificationId);
};

ساخت VR_IVRSettings_Fn_جدول
{
	حرف * (OPENVR_FNTABLE_CALLTYPE *GetSettingsErrorNameFromEnum)(EVRSettingsError eError);
	خالی (OPENVR_FNTABLE_CALLTYPE *سیٹ_Bool)(حرف * pchSection, حرف * pch_Settings_کلید, bool b_قدر, EVRSettingsError * peError);
	خالی (OPENVR_FNTABLE_CALLTYPE *سیٹ_Int32)(حرف * pchSection, حرف * pch_Settings_کلید, int32_t n_قدر, EVRSettingsError * peError);
	خالی (OPENVR_FNTABLE_CALLTYPE *سیٹ_Float)(حرف * pchSection, حرف * pch_Settings_کلید, اعشاری fl_قدر, EVRSettingsError * peError);
	خالی (OPENVR_FNTABLE_CALLTYPE *سیٹ_String)(حرف * pchSection, حرف * pch_Settings_کلید, حرف * pch_قدر, EVRSettingsError * peError);
	bool (OPENVR_FNTABLE_CALLTYPE *GetBool)(حرف * pchSection, حرف * pch_Settings_کلید, EVRSettingsError * peError);
	int32_t (OPENVR_FNTABLE_CALLTYPE *GetInt32)(حرف * pchSection, حرف * pch_Settings_کلید, EVRSettingsError * peError);
	اعشاری (OPENVR_FNTABLE_CALLTYPE *GetFloat)(حرف * pchSection, حرف * pch_Settings_کلید, EVRSettingsError * peError);
	خالی (OPENVR_FNTABLE_CALLTYPE *GetString)(حرف * pchSection, حرف * pch_Settings_کلید, حرف * pch_قدر, uint32_t un_قدر_Len, EVRSettingsError * peError);
	خالی (OPENVR_FNTABLE_CALLTYPE *RemoveSection)(حرف * pchSection, EVRSettingsError * peError);
	خالی (OPENVR_FNTABLE_CALLTYPE *Remove_کلید_اندر_Section)(حرف * pchSection, حرف * pch_Settings_کلید, EVRSettingsError * peError);
};

ساخت VR_IVRScreenshots_Fn_جدول
{
	EVRScreenshotError (OPENVR_FNTABLE_CALLTYPE *RequestScreenshot)(ScreenshotHandle_t * p_برآمد_Screenshot_Handle, EVRScreenshotType type, حرف * pchPreviewFilename, حرف * pchVRFilename);
	EVRScreenshotError (OPENVR_FNTABLE_CALLTYPE *HookScreenshot)(EVRScreenshotType * pSupportedTypes, صحیح عدد_Types);
	EVRScreenshotType (OPENVR_FNTABLE_CALLTYPE *GetScreenshotPropertyType)(ScreenshotHandle_t screenshotHandle, EVRScreenshotError * pError);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetScreenshotPropertyFilename)(ScreenshotHandle_t screenshotHandle, EVRScreenshotPropertyFilenames filenameType, حرف * pchFilename, uint32_t cchFilename, EVRScreenshotError * pError);
	EVRScreenshotError (OPENVR_FNTABLE_CALLTYPE *Update_Screenshot_پیش_رفت)(ScreenshotHandle_t screenshotHandle, اعشاری fl_پیش_رفت);
	EVRScreenshotError (OPENVR_FNTABLE_CALLTYPE *TakeStereoScreenshot)(ScreenshotHandle_t * p_برآمد_Screenshot_Handle, حرف * pchPreviewFilename, حرف * pchVRFilename);
	EVRScreenshotError (OPENVR_FNTABLE_CALLTYPE *SubmitScreenshot)(ScreenshotHandle_t screenshotHandle, EVRScreenshotType type, حرف * pch_ماخذ_Preview_Filename, حرف * pch_ماخذ_VRFilename);
};

ساخت VR_IVRResources_Fn_جدول
{
	uint32_t (OPENVR_FNTABLE_CALLTYPE *بھرو_Shared_Resource)(حرف * pchResourceName, حرف * pch_بفر, uint32_t un_بفر_Len);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *Get_Resource_بھرا_راستہ)(حرف * pchResourceName, حرف * pchResourceTypeDirectory, حرف * pch_راستہ_بفر, uint32_t un_بفر_Len);
};

ساخت VR_IVRDriver_Manager_Fn_جدول
{
	uint32_t (OPENVR_FNTABLE_CALLTYPE *Get_Driver_گنتی)();
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetDriverName)(DriverId_t nDriver, حرف * pch_قدر, uint32_t un_بفر_سائز);
	DriverHandle_t (OPENVR_FNTABLE_CALLTYPE *GetDriverHandle)(حرف * pchDriverName);
	bool (OPENVR_FNTABLE_CALLTYPE *IsEnabled)(DriverId_t nDriver);
};

ساخت VR_IVRInput_Fn_جدول
{
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *سیٹ_Action_Manifest_راستہ)(حرف * pch_Action_Manifest_راستہ);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *Get_Action_سیٹ_Handle)(حرف * pch_Action_سیٹ_Name, VRAction_سیٹ_Handle_t * pHandle);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetActionHandle)(حرف * pchActionName, VRActionHandle_t * pHandle);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *Get_داخلہ_ماخذ_Handle)(حرف * pch_داخلہ_ماخذ_راستہ, VRInput_قدر_Handle_t * pHandle);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *UpdateActionState)(ساخت VRActive_Action_سیٹ_t * pSets, uint32_t un_سائز_کا_VRSelected_Action_سیٹ_t, uint32_t un_سیٹ_گنتی);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *Get_Digital_Action_ڈیٹا)(VRActionHandle_t action, ساخت داخلہ_Digital_Action_ڈیٹا_t * p_Action_ڈیٹا, uint32_t un_Action_ڈیٹا_سائز, VRInput_قدر_Handle_t ul_Restrict_مقصد_Device);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *Get_Analog_Action_ڈیٹا)(VRActionHandle_t action, ساخت داخلہ_Analog_Action_ڈیٹا_t * p_Action_ڈیٹا, uint32_t un_Action_ڈیٹا_سائز, VRInput_قدر_Handle_t ul_Restrict_مقصد_Device);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *Get_Pose_Action_ڈیٹا_Relative_مقصد_Now)(VRActionHandle_t action, ETrackingUniverseOrigin eOrigin, اعشاری fPredictedSecondsFromNow, ساخت داخلہ_Pose_Action_ڈیٹا_t * p_Action_ڈیٹا, uint32_t un_Action_ڈیٹا_سائز, VRInput_قدر_Handle_t ul_Restrict_مقصد_Device);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *Get_Pose_Action_ڈیٹا_For_اگلا_چوکھٹا)(VRActionHandle_t action, ETrackingUniverseOrigin eOrigin, ساخت داخلہ_Pose_Action_ڈیٹا_t * p_Action_ڈیٹا, uint32_t un_Action_ڈیٹا_سائز, VRInput_قدر_Handle_t ul_Restrict_مقصد_Device);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *Get_Skeletal_Action_ڈیٹا)(VRActionHandle_t action, ساخت داخلہ_Skeletal_Action_ڈیٹا_t * p_Action_ڈیٹا, uint32_t un_Action_ڈیٹا_سائز);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetDominantHand)(ETrackedControllerRole * peDominantHand);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *سیٹ_Dominant_Hand)(ETrackedControllerRole eDominantHand);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *Get_Bone_گنتی)(VRActionHandle_t action, uint32_t * p_Bone_گنتی);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetBoneHierarchy)(VRActionHandle_t action, Bone_اشاریہ_t * p_والد_Indices, uint32_t un_اشاریہ_Aray_گنتی);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetBoneName)(VRActionHandle_t action, Bone_اشاریہ_t n_Bone_اشاریہ, حرف * pchBoneName, uint32_t un_Name_بفر_سائز);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetSkeletalReferenceTransforms)(VRActionHandle_t action, EVRSkeletalTransformSpace eTransformSpace, EVRSkeletalReferencePose eReferencePose, ساخت VRBoneTransform_t * pTransformArray, uint32_t un_Transform_Array_گنتی);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetSkeletalTrackingLevel)(VRActionHandle_t action, EVRSkeletalTrackingLevel * pSkeletalTrackingLevel);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *Get_Skeletal_Bone_ڈیٹا)(VRActionHandle_t action, EVRSkeletalTransformSpace eTransformSpace, EVRSkeletalMotionRange eMotionRange, ساخت VRBoneTransform_t * pTransformArray, uint32_t un_Transform_Array_گنتی);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *Get_Skeletal_Summary_ڈیٹا)(VRActionHandle_t action, EVRSummaryType eSummaryType, ساخت VRSkeletal_Summary_ڈیٹا_t * p_Skeletal_Summary_ڈیٹا);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *Get_Skeletal_Bone_ڈیٹا_Compressed)(VRActionHandle_t action, EVRSkeletalMotionRange eMotionRange, خالی * pv_Compressed_ڈیٹا, uint32_t un_Compressed_سائز, uint32_t * pun_Required_Compressed_سائز);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *Decompress_Skeletal_Bone_ڈیٹا)(خالی * pv_Compressed_بفر, uint32_t un_Compressed_بفر_سائز, EVRSkeletalTransformSpace eTransformSpace, ساخت VRBoneTransform_t * pTransformArray, uint32_t un_Transform_Array_گنتی);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *TriggerHapticVibrationAction)(VRActionHandle_t action, اعشاری f_آغاز_Seconds_From_Now, اعشاری fDurationSeconds, اعشاری fFrequency, اعشاری fAmplitude, VRInput_قدر_Handle_t ul_Restrict_مقصد_Device);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetActionOrigins)(VRAction_سیٹ_Handle_t action_سیٹ_Handle, VRActionHandle_t digitalActionHandle, VRInput_قدر_Handle_t * origins_برآمد, uint32_t origin_برآمد_گنتی);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetOriginLocalizedName)(VRInput_قدر_Handle_t origin, حرف * pchNameArray, uint32_t un_Name_Array_سائز, int32_t un_String_Sections_مقصد_Include);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetOriginTrackedDeviceInfo)(VRInput_قدر_Handle_t origin, ساخت داخلہ_Origin_Info_t * pOriginInfo, uint32_t un_Origin_Info_سائز);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetActionBindingInfo)(VRActionHandle_t action, ساخت داخلہ_Binding_Info_t * pOriginInfo, uint32_t un_Binding_Info_سائز, uint32_t un_Binding_Info_گنتی, uint32_t * pun_Returned_Binding_Info_گنتی);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *ShowActionOrigins)(VRAction_سیٹ_Handle_t action_سیٹ_Handle, VRActionHandle_t ulActionHandle);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *Show_Bindings_For_Action_سیٹ)(ساخت VRActive_Action_سیٹ_t * pSets, uint32_t un_سائز_کا_VRSelected_Action_سیٹ_t, uint32_t un_سیٹ_گنتی, VRInput_قدر_Handle_t origin_مقصد_Highlight);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetComponentStateForBinding)(حرف * pchRenderModelName, حرف * pchComponentName, ساخت داخلہ_Binding_Info_t * pOriginInfo, uint32_t un_Binding_Info_سائز, uint32_t un_Binding_Info_گنتی, RenderModel_ComponentState_t * pComponentState);
	bool (OPENVR_FNTABLE_CALLTYPE *Is_Using_Legacy_داخلہ)();
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *OpenBindingUI)(حرف * pch_App_کلید, VRAction_سیٹ_Handle_t ul_Action_سیٹ_Handle, VRInput_قدر_Handle_t ulDeviceHandle, bool bShowOnDesktop);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetBindingVariant)(VRInput_قدر_Handle_t ul_Device_راستہ, حرف * pchVariantArray, uint32_t un_Variant_Array_سائز);
};

ساخت VR_IVRIOBuffer_Fn_جدول
{
	EIOBufferError (OPENVR_FNTABLE_CALLTYPE *Open)(حرف * pch_راستہ, EIOBuffer_منوال منوال, uint32_t un_Element_سائز, uint32_t unElements, IOBufferHandle_t * pul_بفر);
	EIOBufferError (OPENVR_FNTABLE_CALLTYPE *Close)(IOBufferHandle_t ul_بفر);
	EIOBufferError (OPENVR_FNTABLE_CALLTYPE *Read)(IOBufferHandle_t ul_بفر, خالی * pDst, uint32_t un_بائٹیں, uint32_t * punRead);
	EIOBufferError (OPENVR_FNTABLE_CALLTYPE *Write)(IOBufferHandle_t ul_بفر, خالی * pSrc, uint32_t un_بائٹیں);
	PropertyContainerHandle_t (OPENVR_FNTABLE_CALLTYPE *PropertyContainer)(IOBufferHandle_t ul_بفر);
	bool (OPENVR_FNTABLE_CALLTYPE *HasReaders)(IOBufferHandle_t ul_بفر);
};

ساخت VR_IVRSpatial_Anchors_Fn_جدول
{
	EVRSpatialAnchorError (OPENVR_FNTABLE_CALLTYPE *CreateSpatialAnchorFromDescriptor)(حرف * pchDescriptor, SpatialAnchorHandle_t * p_Handle_برآمد);
	EVRSpatialAnchorError (OPENVR_FNTABLE_CALLTYPE *CreateSpatialAnchorFromPose)(Tracked_Device_اشاریہ_t un_Device_اشاریہ, ETrackingUniverseOrigin eOrigin, ساخت SpatialAnchorPose_t * pPose, SpatialAnchorHandle_t * p_Handle_برآمد);
	EVRSpatialAnchorError (OPENVR_FNTABLE_CALLTYPE *GetSpatialAnchorPose)(SpatialAnchorHandle_t unHandle, ETrackingUniverseOrigin eOrigin, ساخت SpatialAnchorPose_t * p_Pose_برآمد);
	EVRSpatialAnchorError (OPENVR_FNTABLE_CALLTYPE *GetSpatialAnchorDescriptor)(SpatialAnchorHandle_t unHandle, حرف * pch_Descriptor_برآمد, uint32_t * pun_Descriptor_بفر_Len_اندر_برآمد);
};

ساخت VR_IVRDebug_Fn_جدول
{
	EVRDebugError (OPENVR_FNTABLE_CALLTYPE *EmitVrProfilerEvent)(حرف * pch_پیغام);
	EVRDebugError (OPENVR_FNTABLE_CALLTYPE *BeginVrProfilerEvent)(VrProfilerEventHandle_t * p_Handle_برآمد);
	EVRDebugError (OPENVR_FNTABLE_CALLTYPE *اختتام_Vr_Profiler_Event)(VrProfilerEventHandle_t hHandle, حرف * pch_پیغام);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *DriverDebugRequest)(Tracked_Device_اشاریہ_t un_Device_اشاریہ, حرف * pchRequest, حرف * pch_Response_بفر, uint32_t un_Response_بفر_سائز);
};

ساخت VR_IVRProperties_Fn_جدول
{
	ETrackedPropertyError (OPENVR_FNTABLE_CALLTYPE *ReadPropertyBatch)(PropertyContainerHandle_t ulContainerHandle, ساخت PropertyRead_t * pBatch, uint32_t un_Batch_اندراج_گنتی);
	ETrackedPropertyError (OPENVR_FNTABLE_CALLTYPE *WritePropertyBatch)(PropertyContainerHandle_t ulContainerHandle, ساخت PropertyWrite_t * pBatch, uint32_t un_Batch_اندراج_گنتی);
	حرف * (OPENVR_FNTABLE_CALLTYPE *GetPropErrorNameFromEnum)(ETrackedPropertyError error);
	PropertyContainerHandle_t (OPENVR_FNTABLE_CALLTYPE *Tracked_Device_مقصد_Property_Container)(Tracked_Device_اشاریہ_t nDevice);
};

ساخت VR_IVRPaths_Fn_جدول
{
	ETrackedPropertyError (OPENVR_FNTABLE_CALLTYPE *Read_راستہ_Batch)(PropertyContainerHandle_t ul_جڑ_Handle, ساخت راستہ_Read_t * pBatch, uint32_t un_Batch_اندراج_گنتی);
	ETrackedPropertyError (OPENVR_FNTABLE_CALLTYPE *Write_راستہ_Batch)(PropertyContainerHandle_t ul_جڑ_Handle, ساخت راستہ_Write_t * pBatch, uint32_t un_Batch_اندراج_گنتی);
	ETrackedPropertyError (OPENVR_FNTABLE_CALLTYPE *String_مقصد_Handle)(راستہ_Handle_t * pHandle, حرف * pch_راستہ);
	ETrackedPropertyError (OPENVR_FNTABLE_CALLTYPE *Handle_مقصد_String)(راستہ_Handle_t pHandle, حرف * pch_بفر, uint32_t un_بفر_سائز, uint32_t * pun_بفر_سائز_مستعمل);
};

ساخت VR_IVRBlock_قطار_Fn_جدول
{
	EBlock_قطار_Error (OPENVR_FNTABLE_CALLTYPE *Create)(PropertyContainerHandle_t * pul_قطار_Handle, حرف * pch_راستہ, uint32_t un_بلاک_ڈیٹا_سائز, uint32_t un_بلاک_سرخی_سائز, uint32_t un_بلاک_گنتی, uint32_t unFlags);
	EBlock_قطار_Error (OPENVR_FNTABLE_CALLTYPE *Connect)(PropertyContainerHandle_t * pul_قطار_Handle, حرف * pch_راستہ);
	EBlock_قطار_Error (OPENVR_FNTABLE_CALLTYPE *Destroy)(PropertyContainerHandle_t ul_قطار_Handle);
	EBlock_قطار_Error (OPENVR_FNTABLE_CALLTYPE *Acquire_Write_Only_بلاک)(PropertyContainerHandle_t ul_قطار_Handle, PropertyContainerHandle_t * pul_بلاک_Handle, خالی ** ppv_بفر);
	EBlock_قطار_Error (OPENVR_FNTABLE_CALLTYPE *Release_Write_Only_بلاک)(PropertyContainerHandle_t ul_قطار_Handle, PropertyContainerHandle_t ul_بلاک_Handle);
	EBlock_قطار_Error (OPENVR_FNTABLE_CALLTYPE *Wait_And_Acquire_Read_Only_بلاک)(PropertyContainerHandle_t ul_قطار_Handle, PropertyContainerHandle_t * pul_بلاک_Handle, خالی ** ppv_بفر, EBlock_قطار_Read_Type eReadType, uint32_t unTimeoutMs);
	EBlock_قطار_Error (OPENVR_FNTABLE_CALLTYPE *Acquire_Read_Only_بلاک)(PropertyContainerHandle_t ul_قطار_Handle, PropertyContainerHandle_t * pul_بلاک_Handle, خالی ** ppv_بفر, EBlock_قطار_Read_Type eReadType);
	EBlock_قطار_Error (OPENVR_FNTABLE_CALLTYPE *Release_Read_Only_بلاک)(PropertyContainerHandle_t ul_قطار_Handle, PropertyContainerHandle_t ul_بلاک_Handle);
	EBlock_قطار_Error (OPENVR_FNTABLE_CALLTYPE *قطار_Has_Reader)(PropertyContainerHandle_t ul_قطار_Handle, bool * pbHasReaders);
};


#اگر 0
// Global entry points
S_API intptr_t VR_Init_اندرونی( EVRInitError *peError, EVRApplicationType eType );
S_API خالی VR_Shutdown_اندرونی();
S_API bool VR_IsHmdPresent();
S_API intptr_t VR_GetGenericInterface( ثابت حرف *pch_Interface_نسخہ, EVRInitError *peError );
S_API bool VR_IsRuntimeInstalled();
S_API ثابت حرف * VR_Get_VRInit_Error_As_علامت( EVRInitError error );
S_API ثابت حرف * VR_GetVRInitErrorAsEnglishDescription( EVRInitError error );
#اگر_ختم

#اگر_ختم // __OPENVR_API_FLAT_H__


