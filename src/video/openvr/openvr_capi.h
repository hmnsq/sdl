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

#جيڪڏهن_وصف_نه_ٿيل __OPENVR_API_FLAT_H__
#وصف_ڪريو __OPENVR_API_FLAT_H__
#إذا defined( _WIN32 ) || defined( __clang__ )
#هدايت once
#جيڪڏهن_پورو

#جيڪڏهن_وصف_ٿيل __cplusplus
#وصف_ڪريو EXTERN_C خارجي "C"
#وإلا
#وصف_ڪريو EXTERN_C
#جيڪڏهن_پورو

#إذا defined( _WIN32 )
#وصف_ڪريو OPENVR_FNTABLE_CALLTYPE __stdcall
#وإلا
#وصف_ڪريو OPENVR_FNTABLE_CALLTYPE 
#جيڪڏهن_پورو

// OPENVR API export macro
#إذا defined( _WIN32 ) && !defined( _X360 )
	#إذا defined( OPENVR_API_EXPORTS )
	#وصف_ڪريو S_API EXTERN_C __declspec( dllexport )
	#وإلاإذا defined( OPENVR_API_NODLL )
	#وصف_ڪريو S_API EXTERN_C
	#وإلا
	#وصف_ڪريو S_API خارجي "C" __declspec( dllimport ) 
	#جيڪڏهن_پورو // OPENVR_API_EXPORTS
#وإلاإذا defined( __GNUC__ )
	#إذا defined( OPENVR_API_EXPORTS )
	#وصف_ڪريو S_API EXTERN_C __attribute__ ((visibility("default")))
	#وإلا
	#وصف_ڪريو S_API EXTERN_C
	#جيڪڏهن_پورو // OPENVR_API_EXPORTS
#وإلا // !WIN32
	#إذا defined( OPENVR_API_EXPORTS )
	#وصف_ڪريو S_API EXTERN_C
	#وإلا
	#وصف_ڪريو S_API EXTERN_C
	#جيڪڏهن_پورو // OPENVR_API_EXPORTS
#جيڪڏهن_پورو

#جيڪڏهن_وصف_نه_ٿيل USE_SDL
#ضمن <stdint.h>

#إذا defined( __WIN32 )
تعريفنوع حرف bool;
#وإلا
#ضمن <stdbool.h>
#جيڪڏهن_پورو
#جيڪڏهن_پورو // USE_SDL

// OpenVR Constants

ساكن ثابت بنانشان ڊگهو k_nDriverNone = 4294967295;
ساكن ثابت بنانشان ڊگهو k_un_Max_Driver_Debug_Response_سائيز = 32768;
ساكن ثابت بنانشان ڊگهو k_un_Tracked_Device_اشاريو_Hmd = 0;
ساكن ثابت بنانشان ڊگهو k_un_Max_Tracked_Device_ڳڻپ = 64;
ساكن ثابت بنانشان ڊگهو k_un_Tracked_Device_اشاريو_Other = 4294967294;
ساكن ثابت بنانشان ڊگهو k_un_Tracked_Device_اشاريو_Invalid = 4294967295;
ساكن ثابت بنانشان ڊگهو ڊگهو k_ulInvalidPropertyContainer = 0;
ساكن ثابت بنانشان ڊگهو k_un_Invalid_Property_ٽيگ = 0;
ساكن ثابت بنانشان ڊگهو ڊگهو k_ulInvalidDriverHandle = 0;
ساكن ثابت بنانشان ڊگهو k_un_Float_Property_ٽيگ = 1;
ساكن ثابت بنانشان ڊگهو k_un_Int32_Property_ٽيگ = 2;
ساكن ثابت بنانشان ڊگهو k_un_Uint64_Property_ٽيگ = 3;
ساكن ثابت بنانشان ڊگهو k_un_Bool_Property_ٽيگ = 4;
ساكن ثابت بنانشان ڊگهو k_un_String_Property_ٽيگ = 5;
ساكن ثابت بنانشان ڊگهو k_un_Error_Property_ٽيگ = 6;
ساكن ثابت بنانشان ڊگهو k_un_Double_Property_ٽيگ = 7;
ساكن ثابت بنانشان ڊگهو k_un_Hmd_Matrix34_Property_ٽيگ = 20;
ساكن ثابت بنانشان ڊگهو k_un_Hmd_Matrix44_Property_ٽيگ = 21;
ساكن ثابت بنانشان ڊگهو k_un_Hmd_Vector3_Property_ٽيگ = 22;
ساكن ثابت بنانشان ڊگهو k_un_Hmd_Vector4_Property_ٽيگ = 23;
ساكن ثابت بنانشان ڊگهو k_un_Hmd_Vector2_Property_ٽيگ = 24;
ساكن ثابت بنانشان ڊگهو k_un_Hmd_Quad_Property_ٽيگ = 25;
ساكن ثابت بنانشان ڊگهو k_un_Hidden_Area_Property_ٽيگ = 30;
ساكن ثابت بنانشان ڊگهو k_un_رستو_Handle_Info_ٽيگ = 31;
ساكن ثابت بنانشان ڊگهو k_un_Action_Property_ٽيگ = 32;
ساكن ثابت بنانشان ڊگهو k_un_داخلا_قدر_Property_ٽيگ = 33;
ساكن ثابت بنانشان ڊگهو k_un_Wildcard_Property_ٽيگ = 34;
ساكن ثابت بنانشان ڊگهو k_un_Haptic_Vibration_Property_ٽيگ = 35;
ساكن ثابت بنانشان ڊگهو k_un_Skeleton_Property_ٽيگ = 36;
ساكن ثابت بنانشان ڊگهو k_un_Spatial_Anchor_Pose_Property_ٽيگ = 40;
ساكن ثابت بنانشان ڊگهو k_un_Json_Property_ٽيگ = 41;
ساكن ثابت بنانشان ڊگهو k_un_سرگرم_Action_سيٽ_Property_ٽيگ = 42;
ساكن ثابت بنانشان ڊگهو k_un_Open_VRInternal_Reserved_شروعات = 1000;
ساكن ثابت بنانشان ڊگهو k_un_Open_VRInternal_Reserved_پڇاڙي = 10000;
ساكن ثابت بنانشان ڊگهو k_un_Max_Property_String_سائيز = 32768;
ساكن ثابت بنانشان ڊگهو ڊگهو k_ulInvalidActionHandle = 0;
ساكن ثابت بنانشان ڊگهو ڊگهو k_ul_Invalid_Action_سيٽ_Handle = 0;
ساكن ثابت بنانشان ڊگهو ڊگهو k_ul_Invalid_داخلا_قدر_Handle = 0;
ساكن ثابت بنانشان ڊگهو k_un_Controller_State_Axis_ڳڻپ = 5;
ساكن ثابت بنانشان ڊگهو ڊگهو k_ulOverlayHandleInvalid = 0;
ساكن ثابت بنانشان ڊگهو k_unMaxDistortionFunctionParameters = 8;
ساكن ثابت بنانشان ڊگهو k_unScreenshotHandleInvalid = 0;
ساكن ثابت حرف * IVRSystem_نسخو = "IVRSystem_022";
ساكن ثابت حرف * IVRExtended_Display_نسخو = "IVRExtendedDisplay_001";
ساكن ثابت حرف * IVRTracked_Camera_نسخو = "IVRTrackedCamera_006";
ساكن ثابت بنانشان ڊگهو k_un_Max_Application_ڪنجي_ڊيگهائي = 128;
ساكن ثابت حرف * k_pch_MimeType_HomeApp = "vr/home";
ساكن ثابت حرف * k_pch_MimeType_GameTheater = "vr/game_theater";
ساكن ثابت حرف * IVRApplications_نسخو = "IVRApplications_007";
ساكن ثابت حرف * IVRChaperone_نسخو = "IVRChaperone_004";
ساكن ثابت حرف * IVRChaperone_تياري_نسخو = "IVRChaperoneSetup_006";
ساكن ثابت حرف * IVRCompositor_نسخو = "IVRCompositor_027";
ساكن ثابت بنانشان ڊگهو k_un_VROverlay_Max_ڪنجي_ڊيگهائي = 128;
ساكن ثابت بنانشان ڊگهو k_un_VROverlay_Max_Name_ڊيگهائي = 128;
ساكن ثابت بنانشان ڊگهو k_un_Max_Overlay_ڳڻپ = 128;
ساكن ثابت بنانشان ڊگهو k_un_Max_Overlay_Intersection_نقاب_Primitives_ڳڻپ = 32;
ساكن ثابت حرف * IVROverlay_نسخو = "IVROverlay_026";
ساكن ثابت حرف * IVROverlay_View_نسخو = "IVROverlayView_003";
ساكن ثابت بنانشان ڊگهو k_un_Headset_View_Max_ويڪر = 3840;
ساكن ثابت بنانشان ڊگهو k_un_Headset_View_Max_اوچائي = 2160;
ساكن ثابت حرف * k_pch_Headset_View_Overlay_ڪنجي = "system.HeadsetView";
ساكن ثابت حرف * IVRHeadset_View_نسخو = "IVRHeadsetView_001";
ساكن ثابت حرف * k_pch_Controller_Component_GDC2015 = "gdc2015";
ساكن ثابت حرف * k_pch_Controller_Component_بنياد = "base";
ساكن ثابت حرف * k_pch_Controller_Component_Tip = "tip";
ساكن ثابت حرف * k_pch_Controller_Component_OpenXR_Aim = "openxr_aim";
ساكن ثابت حرف * k_pch_Controller_Component_HandGrip = "handgrip";
ساكن ثابت حرف * k_pch_Controller_Component_OpenXR_Grip = "openxr_grip";
ساكن ثابت حرف * k_pch_Controller_Component_OpenXR_HandModel = "openxr_handmodel";
ساكن ثابت حرف * k_pch_Controller_Component_حالت = "status";
ساكن ثابت حرف * IVRRender_Models_نسخو = "IVRRenderModels_006";
ساكن ثابت بنانشان ڊگهو k_un_Notification_متن_Max_سائيز = 256;
ساكن ثابت حرف * IVRNotifications_نسخو = "IVRNotifications_002";
ساكن ثابت بنانشان ڊگهو k_un_Max_Settings_ڪنجي_ڊيگهائي = 128;
ساكن ثابت حرف * IVRSettings_نسخو = "IVRSettings_003";
ساكن ثابت حرف * k_pch_SteamVR_Section = "steamvr";
ساكن ثابت حرف * k_pch_SteamVR_RequireHmd_String = "requireHmd";
ساكن ثابت حرف * k_pch_Steam_VR_Forced_Driver_ڪنجي_String = "forcedDriver";
ساكن ثابت حرف * k_pch_Steam_VR_Forced_Hmd_ڪنجي_String = "forcedHmd";
ساكن ثابت حرف * k_pch_SteamVR_DisplayDebug_Bool = "displayDebug";
ساكن ثابت حرف * k_pch_SteamVR_DebugProcessPipe_String = "debugProcessPipe";
ساكن ثابت حرف * k_pch_SteamVR_DisplayDebugX_Int32 = "displayDebugX";
ساكن ثابت حرف * k_pch_SteamVR_DisplayDebugY_Int32 = "displayDebugY";
ساكن ثابت حرف * k_pch_Steam_VR_Send_System_Button_منزل_All_Apps_Bool = "sendSystemButtonToAllApps";
ساكن ثابت حرف * k_pch_SteamVR_LogLevel_Int32 = "loglevel";
ساكن ثابت حرف * k_pch_SteamVR_IPD_Float = "ipd";
ساكن ثابت حرف * k_pch_SteamVR_Background_String = "background";
ساكن ثابت حرف * k_pch_SteamVR_BackgroundUseDomeProjection_Bool = "backgroundUseDomeProjection";
ساكن ثابت حرف * k_pch_Steam_VR_Background_Camera_اوچائي_Float = "backgroundCameraHeight";
ساكن ثابت حرف * k_pch_SteamVR_BackgroundDomeRadius_Float = "backgroundDomeRadius";
ساكن ثابت حرف * k_pch_SteamVR_GridColor_String = "gridColor";
ساكن ثابت حرف * k_pch_SteamVR_PlayAreaColor_String = "playAreaColor";
ساكن ثابت حرف * k_pch_SteamVR_TrackingLossColor_String = "trackingLossColor";
ساكن ثابت حرف * k_pch_SteamVR_ShowStage_Bool = "showStage";
ساكن ثابت حرف * k_pch_SteamVR_DrawTrackingReferences_Bool = "drawTrackingReferences";
ساكن ثابت حرف * k_pch_Steam_VR_Activate_گڻو_Drivers_Bool = "activateMultipleDrivers";
ساكن ثابت حرف * k_pch_SteamVR_UsingSpeakers_Bool = "usingSpeakers";
ساكن ثابت حرف * k_pch_Steam_VR_Speakers_Forward_Yaw_وٿي_Degrees_Float = "speakersForwardYawOffsetDegrees";
ساكن ثابت حرف * k_pch_Steam_VR_بنياد_Station_Power_Management_Int32 = "basestationPowerManagement";
ساكن ثابت حرف * k_pch_Steam_VR_Show_بنياد_Station_Power_Management_Tip_Int32 = "ShowBaseStationPowerManagementTip";
ساكن ثابت حرف * k_pch_SteamVR_NeverKillProcesses_Bool = "neverKillProcesses";
ساكن ثابت حرف * k_pch_SteamVR_SupersampleScale_Float = "supersampleScale";
ساكن ثابت حرف * k_pch_SteamVR_MaxRecommendedResolution_Int32 = "maxRecommendedResolution";
ساكن ثابت حرف * k_pch_SteamVR_MotionSmoothing_Bool = "motionSmoothing";
ساكن ثابت حرف * k_pch_SteamVR_MotionSmoothingOverride_Int32 = "motionSmoothingOverride";
ساكن ثابت حرف * k_pch_Steam_VR_چوکٺا_منزل_Throttle_Int32 = "framesToThrottle";
ساكن ثابت حرف * k_pch_Steam_VR_Additional_چوکٺا_منزل_Predict_Int32 = "additionalFramesToPredict";
ساكن ثابت حرف * k_pch_SteamVR_WorldScale_Float = "worldScale";
ساكن ثابت حرف * k_pch_SteamVR_FovScale_Int32 = "fovScale";
ساكن ثابت حرف * k_pch_SteamVR_DisableAsyncReprojection_Bool = "disableAsync";
ساكن ثابت حرف * k_pch_SteamVR_ForceFadeOnBadTracking_Bool = "forceFadeOnBadTracking";
ساكن ثابت حرف * k_pch_SteamVR_DefaultMirrorView_Int32 = "mirrorView";
ساكن ثابت حرف * k_pch_SteamVR_ShowLegacyMirrorView_Bool = "showLegacyMirrorView";
ساكن ثابت حرف * k_pch_SteamVR_MirrorViewVisibility_Bool = "showMirrorView";
ساكن ثابت حرف * k_pch_Steam_VR_Mirror_View_Display_گهڻائي_Int32 = "mirrorViewDisplayMode";
ساكن ثابت حرف * k_pch_SteamVR_MirrorViewEye_Int32 = "mirrorViewEye";
ساكن ثابت حرف * k_pch_SteamVR_MirrorViewGeometry_String = "mirrorViewGeometry";
ساكن ثابت حرف * k_pch_SteamVR_MirrorViewGeometryMaximized_String = "mirrorViewGeometryMaximized";
ساكن ثابت حرف * k_pch_Steam_VR_Perf_گراف_Visibility_Bool = "showPerfGraph";
ساكن ثابت حرف * k_pch_Steam_VR_شروعات_Monitor_From_App_Launch = "startMonitorFromAppLaunch";
ساكن ثابت حرف * k_pch_Steam_VR_شروعات_Compositor_From_App_Launch_Bool = "startCompositorFromAppLaunch";
ساكن ثابت حرف * k_pch_Steam_VR_شروعات_Dashboard_From_App_Launch_Bool = "startDashboardFromAppLaunch";
ساكن ثابت حرف * k_pch_Steam_VR_شروعات_Overlay_Apps_From_Dashboard_Bool = "startOverlayAppsFromDashboard";
ساكن ثابت حرف * k_pch_SteamVR_EnableHomeApp = "enableHomeApp";
ساكن ثابت حرف * k_pch_Steam_VR_چڪر_Background_Image_وقت_Sec_Int32 = "CycleBackgroundImageTimeSec";
ساكن ثابت حرف * k_pch_SteamVR_RetailDemo_Bool = "retailDemo";
ساكن ثابت حرف * k_pch_Steam_VR_Ipd_وٿي_Float = "ipdOffset";
ساكن ثابت حرف * k_pch_SteamVR_AllowSupersampleFiltering_Bool = "allowSupersampleFiltering";
ساكن ثابت حرف * k_pch_SteamVR_SupersampleManualOverride_Bool = "supersampleManualOverride";
ساكن ثابت حرف * k_pch_SteamVR_EnableLinuxVulkanAsync_Bool = "enableLinuxVulkanAsync";
ساكن ثابت حرف * k_pch_Steam_VR_Allow_Display_Locked_گهڻائي_Bool = "allowDisplayLockedMode";
ساكن ثابت حرف * k_pch_SteamVR_HaveStartedTutorialForNativeChaperoneDriver_Bool = "haveStartedTutorialForNativeChaperoneDriver";
ساكن ثابت حرف * k_pch_SteamVR_ForceWindows32bitVRMonitor = "forceWindows32BitVRMonitor";
ساكن ثابت حرف * k_pch_Steam_VR_Debug_داخلا_Binding = "debugInputBinding";
ساكن ثابت حرف * k_pch_Steam_VR_Do_Not_Fade_منزل_Grid = "doNotFadeToGrid";
ساكن ثابت حرف * k_pch_Steam_VR_Render_Camera_گهڻائي = "renderCameraMode";
ساكن ثابت حرف * k_pch_SteamVR_EnableSharedResourceJournaling = "enableSharedResourceJournaling";
ساكن ثابت حرف * k_pch_Steam_VR_Enable_محفوظ_گهڻائي = "enableSafeMode";
ساكن ثابت حرف * k_pch_Steam_VR_Preferred_Refresh_شرح = "preferredRefreshRate";
ساكن ثابت حرف * k_pch_Steam_VR_آخري_نسخو_Notice = "lastVersionNotice";
ساكن ثابت حرف * k_pch_Steam_VR_آخري_نسخو_Notice_Date = "lastVersionNoticeDate";
ساكن ثابت حرف * k_pch_SteamVR_HmdDisplayColorGainR_Float = "hmdDisplayColorGainR";
ساكن ثابت حرف * k_pch_SteamVR_HmdDisplayColorGainG_Float = "hmdDisplayColorGainG";
ساكن ثابت حرف * k_pch_SteamVR_HmdDisplayColorGainB_Float = "hmdDisplayColorGainB";
ساكن ثابت حرف * k_pch_SteamVR_CustomIconStyle_String = "customIconStyle";
ساكن ثابت حرف * k_pch_SteamVR_CustomOffIconStyle_String = "customOffIconStyle";
ساكن ثابت حرف * k_pch_SteamVR_CustomIconForceUpdate_String = "customIconForceUpdate";
ساكن ثابت حرف * k_pch_Steam_VR_Allow_Global_Action_سيٽ_ترجيح = "globalActionSetPriority";
ساكن ثابت حرف * k_pch_SteamVR_OverlayRenderQuality = "overlayRenderQuality_2";
ساكن ثابت حرف * k_pch_Steam_VR_بلاڪ_Oculus_SDKOn_Open_VRLaunch_Option_Bool = "blockOculusSDKOnOpenVRLaunchOption";
ساكن ثابت حرف * k_pch_Steam_VR_بلاڪ_Oculus_SDKOn_All_Launches_Bool = "blockOculusSDKOnAllLaunches";
ساكن ثابت حرف * k_pch_SteamVR_HDCPLegacyCompatibility_Bool = "hdcp14legacyCompatibility";
ساكن ثابت حرف * k_pch_Steam_VR_Display_پورٽ_Training_گهڻائي_Int = "displayPortTrainingMode";
ساكن ثابت حرف * k_pch_SteamVR_UsePrism_Bool = "usePrism";
ساكن ثابت حرف * k_pch_سڌو_گهڻائي_Section = "direct_mode";
ساكن ثابت حرف * k_pch_سڌو_گهڻائي_Enable_Bool = "enable";
ساكن ثابت حرف * k_pch_سڌو_گهڻائي_ڳڻپ_Int32 = "count";
ساكن ثابت حرف * k_pch_سڌو_گهڻائي_Edid_Vid_Int32 = "edidVid";
ساكن ثابت حرف * k_pch_سڌو_گهڻائي_Edid_Pid_Int32 = "edidPid";
ساكن ثابت حرف * k_pch_Lighthouse_Section = "driver_lighthouse";
ساكن ثابت حرف * k_pch_Lighthouse_DisableIMU_Bool = "disableimu";
ساكن ثابت حرف * k_pch_Lighthouse_DisableIMUExceptHMD_Bool = "disableimuexcepthmd";
ساكن ثابت حرف * k_pch_Lighthouse_UseDisambiguation_String = "usedisambiguation";
ساكن ثابت حرف * k_pch_Lighthouse_DisambiguationDebug_Int32 = "disambiguationdebug";
ساكن ثابت حرف * k_pch_Lighthouse_PrimaryBasestation_Int32 = "primarybasestation";
ساكن ثابت حرف * k_pch_Lighthouse_DBHistory_Bool = "dbhistory";
ساكن ثابت حرف * k_pch_Lighthouse_EnableBluetooth_Bool = "enableBluetooth";
ساكن ثابت حرف * k_pch_Lighthouse_Power_Managed_بنياد_Stations_String = "PowerManagedBaseStations";
ساكن ثابت حرف * k_pch_Lighthouse_Power_Managed_بنياد_Stations2_String = "PowerManagedBaseStations2";
ساكن ثابت حرف * k_pch_Lighthouse_Inactivity_Timeout_For_بنياد_Stations_Int32 = "InactivityTimeoutForBaseStations";
ساكن ثابت حرف * k_pch_Lighthouse_EnableImuFallback_Bool = "enableImuFallback";
ساكن ثابت حرف * k_pch_Null_Section = "driver_null";
ساكن ثابت حرف * k_pch_Null_Serial_عدد_String = "serialNumber";
ساكن ثابت حرف * k_pch_Null_Model_عدد_String = "modelNumber";
ساكن ثابت حرف * k_pch_Null_دري_X_Int32 = "windowX";
ساكن ثابت حرف * k_pch_Null_دري_Y_Int32 = "windowY";
ساكن ثابت حرف * k_pch_Null_دري_ويڪر_Int32 = "windowWidth";
ساكن ثابت حرف * k_pch_Null_دري_اوچائي_Int32 = "windowHeight";
ساكن ثابت حرف * k_pch_Null_Render_ويڪر_Int32 = "renderWidth";
ساكن ثابت حرف * k_pch_Null_Render_اوچائي_Int32 = "renderHeight";
ساكن ثابت حرف * k_pch_Null_Seconds_From_Vsync_منزل_Photons_Float = "secondsFromVsyncToPhotons";
ساكن ثابت حرف * k_pch_Null_DisplayFrequency_Float = "displayFrequency";
ساكن ثابت حرف * k_pch_WindowsMR_Section = "driver_holographic";
ساكن ثابت حرف * k_pch_UserInterface_Section = "userinterface";
ساكن ثابت حرف * k_pch_User_Interface_حالت_Always_On_چوٽي_Bool = "StatusAlwaysOnTop";
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
ساكن ثابت حرف * k_pch_Keyboard_وٿي_کاٻو_X = "OffsetLeftX";
ساكن ثابت حرف * k_pch_Keyboard_وٿي_ساڄو_X = "OffsetRightX";
ساكن ثابت حرف * k_pch_Keyboard_وٿي_Y = "OffsetY";
ساكن ثابت حرف * k_pch_Keyboard_Smoothing = "Smoothing";
ساكن ثابت حرف * k_pch_Perf_Section = "perfcheck";
ساكن ثابت حرف * k_pch_Perf_Perf_گراف_اندريون_HMD_Bool = "perfGraphInHMD";
ساكن ثابت حرف * k_pch_Perf_AllowTimingStore_Bool = "allowTimingStore";
ساكن ثابت حرف * k_pch_Perf_SaveTimingsOnExit_Bool = "saveTimingsOnExit";
ساكن ثابت حرف * k_pch_Perf_Test_معلومات_Float = "perfTestData";
ساكن ثابت حرف * k_pch_Perf_GPUProfiling_Bool = "GPUProfiling";
ساكن ثابت حرف * k_pch_CollisionBounds_Section = "collisionBounds";
ساكن ثابت حرف * k_pch_CollisionBounds_Style_Int32 = "CollisionBoundsStyle";
ساكن ثابت حرف * k_pch_CollisionBounds_GroundPerimeterOn_Bool = "CollisionBoundsGroundPerimeterOn";
ساكن ثابت حرف * k_pch_CollisionBounds_CenterMarkerOn_Bool = "CollisionBoundsCenterMarkerOn";
ساكن ثابت حرف * k_pch_CollisionBounds_PlaySpaceOn_Bool = "CollisionBoundsPlaySpaceOn";
ساكن ثابت حرف * k_pch_Collision_Bounds_Fade_مفاصلو_Float = "CollisionBoundsFadeDistance";
ساكن ثابت حرف * k_pch_Collision_Bounds_Wall_اوچائي_Float = "CollisionBoundsWallHeight";
ساكن ثابت حرف * k_pch_CollisionBounds_ColorGammaR_Int32 = "CollisionBoundsColorGammaR";
ساكن ثابت حرف * k_pch_CollisionBounds_ColorGammaG_Int32 = "CollisionBoundsColorGammaG";
ساكن ثابت حرف * k_pch_CollisionBounds_ColorGammaB_Int32 = "CollisionBoundsColorGammaB";
ساكن ثابت حرف * k_pch_CollisionBounds_ColorGammaA_Int32 = "CollisionBoundsColorGammaA";
ساكن ثابت حرف * k_pch_CollisionBounds_EnableDriverImport = "enableDriverBoundsImport";
ساكن ثابت حرف * k_pch_Camera_Section = "camera";
ساكن ثابت حرف * k_pch_Camera_EnableCamera_Bool = "enableCamera";
ساكن ثابت حرف * k_pch_Camera_ShowOnController_Bool = "showOnController";
ساكن ثابت حرف * k_pch_Camera_EnableCameraForCollisionBounds_Bool = "enableCameraForCollisionBounds";
ساكن ثابت حرف * k_pch_Camera_گنجائش_View_Int32 = "roomView";
ساكن ثابت حرف * k_pch_Camera_BoundsColorGammaR_Int32 = "cameraBoundsColorGammaR";
ساكن ثابت حرف * k_pch_Camera_BoundsColorGammaG_Int32 = "cameraBoundsColorGammaG";
ساكن ثابت حرف * k_pch_Camera_BoundsColorGammaB_Int32 = "cameraBoundsColorGammaB";
ساكن ثابت حرف * k_pch_Camera_BoundsColorGammaA_Int32 = "cameraBoundsColorGammaA";
ساكن ثابت حرف * k_pch_Camera_BoundsStrength_Int32 = "cameraBoundsStrength";
ساكن ثابت حرف * k_pch_Camera_گنجائش_View_Style_Int32 = "roomViewStyle";
ساكن ثابت حرف * k_pch_audio_Section = "audio";
ساكن ثابت حرف * k_pch_audio_سيٽ_Os_Default_Playback_Device_Bool = "setOsDefaultPlaybackDevice";
ساكن ثابت حرف * k_pch_audio_EnablePlaybackDeviceOverride_Bool = "enablePlaybackDeviceOverride";
ساكن ثابت حرف * k_pch_audio_PlaybackDeviceOverride_String = "playbackDeviceOverride";
ساكن ثابت حرف * k_pch_audio_PlaybackDeviceOverrideName_String = "playbackDeviceOverrideName";
ساكن ثابت حرف * k_pch_audio_سيٽ_Os_Default_Recording_Device_Bool = "setOsDefaultRecordingDevice";
ساكن ثابت حرف * k_pch_audio_EnableRecordingDeviceOverride_Bool = "enableRecordingDeviceOverride";
ساكن ثابت حرف * k_pch_audio_RecordingDeviceOverride_String = "recordingDeviceOverride";
ساكن ثابت حرف * k_pch_audio_RecordingDeviceOverrideName_String = "recordingDeviceOverrideName";
ساكن ثابت حرف * k_pch_audio_EnablePlaybackMirror_Bool = "enablePlaybackMirror";
ساكن ثابت حرف * k_pch_audio_PlaybackMirrorDevice_String = "playbackMirrorDevice";
ساكن ثابت حرف * k_pch_audio_PlaybackMirrorDeviceName_String = "playbackMirrorDeviceName";
ساكن ثابت حرف * k_pch_audio_OldPlaybackMirrorDevice_String = "onPlaybackMirrorDevice";
ساكن ثابت حرف * k_pch_audio_سرگرم_Mirror_Device_String = "activePlaybackMirrorDevice";
ساكن ثابت حرف * k_pch_audio_EnablePlaybackMirrorIndependentVolume_Bool = "enablePlaybackMirrorIndependentVolume";
ساكن ثابت حرف * k_pch_audio_آخري_Hmd_Playback_Device_Id_String = "lastHmdPlaybackDeviceId";
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
ساكن ثابت حرف * k_pch_Dashboard_Arcade_گهڻائي_Bool = "arcadeMode";
ساكن ثابت حرف * k_pch_Dashboard_Position = "position";
ساكن ثابت حرف * k_pch_Dashboard_DesktopScale = "desktopScale";
ساكن ثابت حرف * k_pch_Dashboard_DashboardScale = "dashboardScale";
ساكن ثابت حرف * k_pch_Dashboard_UseStandaloneSystemLayer = "standaloneSystemLayer";
ساكن ثابت حرف * k_pch_Dashboard_StickyDashboard = "stickyDashboard";
ساكن ثابت حرف * k_pch_modelskin_Section = "modelskins";
ساكن ثابت حرف * k_pch_Driver_Enable_Bool = "enable";
ساكن ثابت حرف * k_pch_Driver_BlockedBySafemode_Bool = "blocked_by_safe_mode";
ساكن ثابت حرف * k_pch_Driver_ڀريو_ترجيح_Int32 = "loadPriority";
ساكن ثابت حرف * k_pch_WebInterface_Section = "WebInterface";
ساكن ثابت حرف * k_pch_VRWebHelper_Section = "VRWebHelper";
ساكن ثابت حرف * k_pch_VRWebHelper_DebuggerEnabled_Bool = "DebuggerEnabled";
ساكن ثابت حرف * k_pch_VRWeb_Helper_Debugger_پورٽ_Int32 = "DebuggerPort";
ساكن ثابت حرف * k_pch_TrackingOverride_Section = "TrackingOverrides";
ساكن ثابت حرف * k_pch_App_BindingAutosaveURLSuffix_String = "AutosaveURL";
ساكن ثابت حرف * k_pch_App_BindingLegacyAPISuffix_String = "_legacy";
ساكن ثابت حرف * k_pch_App_BindingSteamVRInputAPISuffix_String = "_steamvrinput";
ساكن ثابت حرف * k_pch_App_BindingOpenXRAPISuffix_String = "_openxr";
ساكن ثابت حرف * k_pch_App_BindingCurrentURLSuffix_String = "CurrentURL";
ساكن ثابت حرف * k_pch_App_Binding_اڳيون_URLSuffix_String = "PreviousURL";
ساكن ثابت حرف * k_pch_App_Need_منزل_Update_Autosave_Suffix_Bool = "NeedToUpdateAutosave";
ساكن ثابت حرف * k_pch_App_DominantHand_Int32 = "DominantHand";
ساكن ثابت حرف * k_pch_App_بلاڪ_Oculus_SDK_Bool = "blockOculusSDK";
ساكن ثابت حرف * k_pch_Trackers_Section = "trackers";
ساكن ثابت حرف * k_pch_DesktopUI_Section = "DesktopUI";
ساكن ثابت حرف * k_pch_آخري_معلوم_Section = "LastKnown";
ساكن ثابت حرف * k_pch_آخري_معلوم_HMDManufacturer_String = "HMDManufacturer";
ساكن ثابت حرف * k_pch_آخري_معلوم_HMDModel_String = "HMDModel";
ساكن ثابت حرف * k_pch_DismissedWarnings_Section = "DismissedWarnings";
ساكن ثابت حرف * k_pch_داخلا_Section = "input";
ساكن ثابت حرف * k_pch_داخلا_کاٻو_Thumbstick_Rotation_Float = "leftThumbstickRotation";
ساكن ثابت حرف * k_pch_داخلا_ساڄو_Thumbstick_Rotation_Float = "rightThumbstickRotation";
ساكن ثابت حرف * k_pch_داخلا_Thumbstick_Deadzone_Float = "thumbstickDeadzone";
ساكن ثابت حرف * k_pch_Gpu_رفتار_Section = "GpuSpeed";
ساكن ثابت حرف * IVRScreenshots_نسخو = "IVRScreenshots_001";
ساكن ثابت حرف * IVRResources_نسخو = "IVRResources_001";
ساكن ثابت حرف * IVRDriver_Manager_نسخو = "IVRDriverManager_001";
ساكن ثابت بنانشان ڊگهو k_un_Max_Action_Name_ڊيگهائي = 64;
ساكن ثابت بنانشان ڊگهو k_un_Max_Action_سيٽ_Name_ڊيگهائي = 64;
ساكن ثابت بنانشان ڊگهو k_un_Max_Action_Origin_ڳڻپ = 16;
ساكن ثابت بنانشان ڊگهو k_un_Max_Bone_Name_ڊيگهائي = 32;
ساكن ثابت صحيح k_n_Action_سيٽ_Overlay_Global_ترجيح_Min = 16777216;
ساكن ثابت صحيح k_n_Action_سيٽ_Overlay_Global_ترجيح_Max = 33554431;
ساكن ثابت صحيح k_n_Action_سيٽ_ترجيح_Reserved_Min = 33554432;
ساكن ثابت حرف * IVRInput_نسخو = "IVRInput_010";
ساكن ثابت بنانشان ڊگهو ڊگهو k_ulInvalidIOBufferHandle = 0;
ساكن ثابت حرف * IVRIOBuffer_نسخو = "IVRIOBuffer_002";
ساكن ثابت بنانشان ڊگهو k_ulInvalidSpatialAnchorHandle = 0;
ساكن ثابت حرف * IVRSpatial_Anchors_نسخو = "IVRSpatialAnchors_001";
ساكن ثابت حرف * IVRDebug_نسخو = "IVRDebug_001";
ساكن ثابت بنانشان ڊگهو ڊگهو k_ulDisplayRedirectContainer = 25769803779;
ساكن ثابت حرف * IVRProperties_نسخو = "IVRProperties_001";
ساكن ثابت حرف * k_pch_رستو_User_Hand_ساڄو = "/user/hand/right";
ساكن ثابت حرف * k_pch_رستو_User_Hand_کاٻو = "/user/hand/left";
ساكن ثابت حرف * k_pch_رستو_User_Hand_Primary = "/user/hand/primary";
ساكن ثابت حرف * k_pch_رستو_User_Hand_Secondary = "/user/hand/secondary";
ساكن ثابت حرف * k_pch_رستو_User_سر = "/user/head";
ساكن ثابت حرف * k_pch_رستو_User_Gamepad = "/user/gamepad";
ساكن ثابت حرف * k_pch_رستو_User_Treadmill = "/user/treadmill";
ساكن ثابت حرف * k_pch_رستو_User_Stylus = "/user/stylus";
ساكن ثابت حرف * k_pch_رستو_Devices = "/devices";
ساكن ثابت حرف * k_pch_رستو_Device_رستو = "/device_path";
ساكن ثابت حرف * k_pch_رستو_بهترين_Alias_رستو = "/best_alias_path";
ساكن ثابت حرف * k_pch_رستو_Bound_Tracker_Alias_رستو = "/bound_tracker_path";
ساكن ثابت حرف * k_pch_رستو_Bound_Tracker_Role = "/bound_tracker_role";
ساكن ثابت حرف * k_pch_رستو_Pose_Raw = "/pose/raw";
ساكن ثابت حرف * k_pch_رستو_Pose_Tip = "/pose/tip";
ساكن ثابت حرف * k_pch_رستو_Pose_Grip = "/pose/grip";
ساكن ثابت حرف * k_pch_رستو_System_Button_Click = "/input/system/click";
ساكن ثابت حرف * k_pch_رستو_Proximity = "/proximity";
ساكن ثابت حرف * k_pch_رستو_Controller_Type_اڳياڙي = "/controller_type/";
ساكن ثابت حرف * k_pch_رستو_داخلا_Profile_Suffix = "/input_profile";
ساكن ثابت حرف * k_pch_رستو_Binding_Name_Suffix = "/binding_name";
ساكن ثابت حرف * k_pch_رستو_Binding_Url_Suffix = "/binding_url";
ساكن ثابت حرف * k_pch_رستو_Binding_Error_Suffix = "/binding_error";
ساكن ثابت حرف * k_pch_رستو_سرگرم_Action_Sets = "/active_action_sets";
ساكن ثابت حرف * k_pch_رستو_Component_Updates = "/total_component_updates";
ساكن ثابت حرف * k_pch_رستو_User_Foot_کاٻو = "/user/foot/left";
ساكن ثابت حرف * k_pch_رستو_User_Foot_ساڄو = "/user/foot/right";
ساكن ثابت حرف * k_pch_رستو_User_Shoulder_کاٻو = "/user/shoulder/left";
ساكن ثابت حرف * k_pch_رستو_User_Shoulder_ساڄو = "/user/shoulder/right";
ساكن ثابت حرف * k_pch_رستو_User_Elbow_کاٻو = "/user/elbow/left";
ساكن ثابت حرف * k_pch_رستو_User_Elbow_ساڄو = "/user/elbow/right";
ساكن ثابت حرف * k_pch_رستو_User_Knee_کاٻو = "/user/knee/left";
ساكن ثابت حرف * k_pch_رستو_User_Knee_ساڄو = "/user/knee/right";
ساكن ثابت حرف * k_pch_رستو_User_Waist = "/user/waist";
ساكن ثابت حرف * k_pch_رستو_User_Chest = "/user/chest";
ساكن ثابت حرف * k_pch_رستو_User_Camera = "/user/camera";
ساكن ثابت حرف * k_pch_رستو_User_Keyboard = "/user/keyboard";
ساكن ثابت حرف * k_pch_رستو_Client_App_ڪنجي = "/client_info/app_key";
ساكن ثابت بنانشان ڊگهو ڊگهو k_ul_Invalid_رستو_Handle = 0;
ساكن ثابت حرف * IVRPaths_نسخو = "IVRPaths_001";
ساكن ثابت حرف * IVRBlock_قطار_نسخو = "IVRBlockQueue_005";

// OpenVR Enums

تعريفنوع تعداد EVREye
{
	EVREye_Eye_کاٻو = 0,
	EVREye_Eye_ساڄو = 1,
} EVREye;

تعريفنوع تعداد ETextureType
{
	ETextureType_TextureType_Invalid = -1,
	ETexture_Type_Texture_Type_سڌو_X = 0,
	ETextureType_TextureType_OpenGL = 1,
	ETextureType_TextureType_Vulkan = 2,
	ETextureType_TextureType_IOSurface = 3,
	ETexture_Type_Texture_Type_سڌو_X12 = 4,
	ETextureType_TextureType_DXGISharedHandle = 5,
	ETextureType_TextureType_Metal = 6,
} ETextureType;

تعريفنوع تعداد EColorSpace
{
	EColorSpace_ColorSpace_Auto = 0,
	EColorSpace_ColorSpace_Gamma = 1,
	EColor_Space_Color_Space_لڪيري = 2,
} EColorSpace;

تعريفنوع تعداد ETracking_نتيجو
{
	ETracking_نتيجو_Tracking_نتيجو_Uninitialized = 1,
	ETracking_نتيجو_Tracking_نتيجو_Calibrating_اندريون_ترقي = 100,
	ETracking_نتيجو_Tracking_نتيجو_Calibrating_ٻاهريون_جو_Range = 101,
	ETracking_نتيجو_Tracking_نتيجو_Running_OK = 200,
	ETracking_نتيجو_Tracking_نتيجو_Running_ٻاهريون_جو_Range = 201,
	ETracking_نتيجو_Tracking_نتيجو_Fallback_Rotation_Only = 300,
} ETracking_نتيجو;

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
	ETracked_Controller_Role_Tracked_Controller_Role_کاٻو_Hand = 1,
	ETracked_Controller_Role_Tracked_Controller_Role_ساڄو_Hand = 2,
	ETracked_Controller_Role_Tracked_Controller_Role_Opt_ٻاهريون = 3,
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
	EAdditional_Radio_Features_Additional_Radio_Features_اندروني_Dongle = 2,
	EAdditionalRadioFeatures_AdditionalRadioFeatures_ExternalDongle = 4,
} EAdditionalRadioFeatures;

تعريفنوع تعداد ETrackedDeviceProperty
{
	ETrackedDeviceProperty_Prop_Invalid = 0,
	ETrackedDeviceProperty_Prop_TrackingSystemName_String = 1000,
	ETracked_Device_Property_Prop_Model_عدد_String = 1001,
	ETracked_Device_Property_Prop_Serial_عدد_String = 1002,
	ETrackedDeviceProperty_Prop_RenderModelName_String = 1003,
	ETracked_Device_Property_Prop_Will_Drift_اندريون_Yaw_Bool = 1004,
	ETrackedDeviceProperty_Prop_ManufacturerName_String = 1005,
	ETracked_Device_Property_Prop_Tracking_Firmware_نسخو_String = 1006,
	ETrackedDeviceProperty_Prop_HardwareRevision_String = 1007,
	ETrackedDeviceProperty_Prop_AllWirelessDongleDescriptions_String = 1008,
	ETrackedDeviceProperty_Prop_ConnectedWirelessDongle_String = 1009,
	ETrackedDeviceProperty_Prop_DeviceIsWireless_Bool = 1010,
	ETrackedDeviceProperty_Prop_DeviceIsCharging_Bool = 1011,
	ETrackedDeviceProperty_Prop_DeviceBatteryPercentage_Float = 1012,
	ETracked_Device_Property_Prop_حالت_Display_Transform_Matrix34 = 1013,
	ETracked_Device_Property_Prop_Firmware_Update_موجود_Bool = 1014,
	ETrackedDeviceProperty_Prop_Firmware_ManualUpdate_Bool = 1015,
	ETrackedDeviceProperty_Prop_Firmware_ManualUpdateURL_String = 1016,
	ETrackedDeviceProperty_Prop_HardwareRevision_Uint64 = 1017,
	ETracked_Device_Property_Prop_Firmware_نسخو_Uint64 = 1018,
	ETrackedDeviceProperty_Prop_FPGAVersion_Uint64 = 1019,
	ETrackedDeviceProperty_Prop_VRCVersion_Uint64 = 1020,
	ETracked_Device_Property_Prop_Radio_نسخو_Uint64 = 1021,
	ETracked_Device_Property_Prop_Dongle_نسخو_Uint64 = 1022,
	ETracked_Device_Property_Prop_بلاڪ_Server_Shutdown_Bool = 1023,
	ETrackedDeviceProperty_Prop_CanUnifyCoordinateSystemWithHmd_Bool = 1024,
	ETracked_Device_Property_Prop_شامل_آهي_Proximity_Sensor_Bool = 1025,
	ETracked_Device_Property_Prop_Device_Provides_Battery_حالت_Bool = 1026,
	ETrackedDeviceProperty_Prop_DeviceCanPowerOff_Bool = 1027,
	ETracked_Device_Property_Prop_Firmware_Programming_هدف_String = 1028,
	ETrackedDeviceProperty_Prop_DeviceClass_Int32 = 1029,
	ETrackedDeviceProperty_Prop_HasCamera_Bool = 1030,
	ETracked_Device_Property_Prop_Driver_نسخو_String = 1031,
	ETrackedDeviceProperty_Prop_Firmware_ForceUpdateRequired_Bool = 1032,
	ETrackedDeviceProperty_Prop_ViveSystemButtonFixRequired_Bool = 1033,
	ETracked_Device_Property_Prop_والد_Driver_Uint64 = 1034,
	ETracked_Device_Property_Prop_Resource_پاڙ_String = 1035,
	ETrackedDeviceProperty_Prop_RegisteredDeviceType_String = 1036,
	ETracked_Device_Property_Prop_داخلا_Profile_رستو_String = 1037,
	ETrackedDeviceProperty_Prop_NeverTracked_Bool = 1038,
	ETracked_Device_Property_Prop_انگ_Cameras_Int32 = 1039,
	ETracked_Device_Property_Prop_Camera_چوکٺو_Layout_Int32 = 1040,
	ETracked_Device_Property_Prop_Camera_وهڪرو_Format_Int32 = 1041,
	ETracked_Device_Property_Prop_Additional_Device_Settings_رستو_String = 1042,
	ETrackedDeviceProperty_Prop_Identifiable_Bool = 1043,
	ETracked_Device_Property_Prop_Bootloader_نسخو_Uint64 = 1044,
	ETracked_Device_Property_Prop_Additional_System_Report_معلومات_String = 1045,
	ETracked_Device_Property_Prop_مرکب_Firmware_نسخو_String = 1046,
	ETrackedDeviceProperty_Prop_Firmware_RemindUpdate_Bool = 1047,
	ETracked_Device_Property_Prop_Peripheral_Application_نسخو_Uint64 = 1048,
	ETracked_Device_Property_Prop_Manufacturer_Serial_عدد_String = 1049,
	ETracked_Device_Property_Prop_Computed_Serial_عدد_String = 1050,
	ETracked_Device_Property_Prop_Estimated_Device_پهريون_Use_وقت_Int32 = 1051,
	ETrackedDeviceProperty_Prop_DevicePowerUsage_Float = 1052,
	ETrackedDeviceProperty_Prop_IgnoreMotionForStandby_Bool = 1053,
	ETracked_Device_Property_Prop_Reports_وقت_Since_VSync_Bool = 2000,
	ETracked_Device_Property_Prop_Seconds_From_Vsync_منزل_Photons_Float = 2001,
	ETrackedDeviceProperty_Prop_DisplayFrequency_Float = 2002,
	ETrackedDeviceProperty_Prop_UserIpdMeters_Float = 2003,
	ETrackedDeviceProperty_Prop_CurrentUniverseId_Uint64 = 2004,
	ETracked_Device_Property_Prop_اڳيون_Universe_Id_Uint64 = 2005,
	ETracked_Device_Property_Prop_Display_Firmware_نسخو_Uint64 = 2006,
	ETrackedDeviceProperty_Prop_IsOnDesktop_Bool = 2007,
	ETrackedDeviceProperty_Prop_DisplayMCType_Int32 = 2008,
	ETrackedDeviceProperty_Prop_DisplayMCOffset_Float = 2009,
	ETrackedDeviceProperty_Prop_DisplayMCScale_Float = 2010,
	ETrackedDeviceProperty_Prop_EdidVendorID_Int32 = 2011,
	ETracked_Device_Property_Prop_Display_MCImage_کاٻو_String = 2012,
	ETracked_Device_Property_Prop_Display_MCImage_ساڄو_String = 2013,
	ETrackedDeviceProperty_Prop_DisplayGCBlackClamp_Float = 2014,
	ETracked_Device_Property_Prop_Edid_حاصل_ضرب_ID_Int32 = 2015,
	ETracked_Device_Property_Prop_Camera_منزل_سر_Transform_Matrix34 = 2016,
	ETrackedDeviceProperty_Prop_DisplayGCType_Int32 = 2017,
	ETrackedDeviceProperty_Prop_DisplayGCOffset_Float = 2018,
	ETrackedDeviceProperty_Prop_DisplayGCScale_Float = 2019,
	ETrackedDeviceProperty_Prop_DisplayGCPrescale_Float = 2020,
	ETrackedDeviceProperty_Prop_DisplayGCImage_String = 2021,
	ETracked_Device_Property_Prop_Lens_Center_کاٻو_U_Float = 2022,
	ETracked_Device_Property_Prop_Lens_Center_کاٻو_V_Float = 2023,
	ETracked_Device_Property_Prop_Lens_Center_ساڄو_U_Float = 2024,
	ETracked_Device_Property_Prop_Lens_Center_ساڄو_V_Float = 2025,
	ETracked_Device_Property_Prop_User_سر_منزل_Eye_اونهائي_Meters_Float = 2026,
	ETracked_Device_Property_Prop_Camera_Firmware_نسخو_Uint64 = 2027,
	ETrackedDeviceProperty_Prop_CameraFirmwareDescription_String = 2028,
	ETrackedDeviceProperty_Prop_DisplayFPGAVersion_Uint64 = 2029,
	ETracked_Device_Property_Prop_Display_Bootloader_نسخو_Uint64 = 2030,
	ETracked_Device_Property_Prop_Display_Hardware_نسخو_Uint64 = 2031,
	ETracked_Device_Property_Prop_Audio_Firmware_نسخو_Uint64 = 2032,
	ETracked_Device_Property_Prop_Camera_Compatibility_گهڻائي_Int32 = 2033,
	ETracked_Device_Property_Prop_Screenshot_Horizontal_ميدان_جو_View_Degrees_Float = 2034,
	ETracked_Device_Property_Prop_Screenshot_Vertical_ميدان_جو_View_Degrees_Float = 2035,
	ETrackedDeviceProperty_Prop_DisplaySuppressed_Bool = 2036,
	ETracked_Device_Property_Prop_Display_Allow_Night_گهڻائي_Bool = 2037,
	ETracked_Device_Property_Prop_Display_MCImage_ويڪر_Int32 = 2038,
	ETracked_Device_Property_Prop_Display_MCImage_اوچائي_Int32 = 2039,
	ETracked_Device_Property_Prop_Display_MCImage_انگ_Channels_Int32 = 2040,
	ETracked_Device_Property_Prop_Display_MCImage_معلومات_ٻٽو = 2041,
	ETracked_Device_Property_Prop_Seconds_From_Photons_منزل_Vblank_Float = 2042,
	ETracked_Device_Property_Prop_Driver_سڌو_گهڻائي_Sends_Vsync_Events_Bool = 2043,
	ETracked_Device_Property_Prop_Display_Debug_گهڻائي_Bool = 2044,
	ETrackedDeviceProperty_Prop_GraphicsAdapterLuid_Uint64 = 2045,
	ETracked_Device_Property_Prop_Driver_Provided_Chaperone_رستو_String = 2048,
	ETracked_Device_Property_Prop_Expected_Tracking_Reference_ڳڻپ_Int32 = 2049,
	ETracked_Device_Property_Prop_Expected_Controller_ڳڻپ_Int32 = 2050,
	ETracked_Device_Property_Prop_Named_Icon_رستو_Controller_کاٻو_Device_Off_String = 2051,
	ETracked_Device_Property_Prop_Named_Icon_رستو_Controller_ساڄو_Device_Off_String = 2052,
	ETracked_Device_Property_Prop_Named_Icon_رستو_Tracking_Reference_Device_Off_String = 2053,
	ETrackedDeviceProperty_Prop_DoNotApplyPrediction_Bool = 2054,
	ETracked_Device_Property_Prop_Camera_منزل_سر_Transforms_Matrix34_Array = 2055,
	ETrackedDeviceProperty_Prop_DistortionMeshResolution_Int32 = 2056,
	ETrackedDeviceProperty_Prop_DriverIsDrawingControllers_Bool = 2057,
	ETracked_Device_Property_Prop_Driver_درخواستون_Application_Pause_Bool = 2058,
	ETracked_Device_Property_Prop_Driver_درخواستون_Reduced_Rendering_Bool = 2059,
	ETracked_Device_Property_Prop_Minimum_Ipd_قدم_Meters_Float = 2060,
	ETracked_Device_Property_Prop_Audio_Bridge_Firmware_نسخو_Uint64 = 2061,
	ETracked_Device_Property_Prop_Image_Bridge_Firmware_نسخو_Uint64 = 2062,
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
	ETracked_Device_Property_Prop_Hmd_ڪالم_Correction_Setting_اڳياڙي_String = 2077,
	ETrackedDeviceProperty_Prop_CameraSupportsCompatibilityModes_Bool = 2078,
	ETracked_Device_Property_Prop_Supports_گنجائش_View_اونهائي_Projection_Bool = 2079,
	ETracked_Device_Property_Prop_Display_موجود_چوکٺو_Rates_Float_Array = 2080,
	ETracked_Device_Property_Prop_Display_Supports_گڻو_Framerates_Bool = 2081,
	ETracked_Device_Property_Prop_Display_Color_Mult_کاٻو_Vector3 = 2082,
	ETracked_Device_Property_Prop_Display_Color_Mult_ساڄو_Vector3 = 2083,
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
	ETracked_Device_Property_Prop_Hmd_Supports_Display_پورٽ_Training_گهڻائي_Bool = 2104,
	ETracked_Device_Property_Prop_Supports_گنجائش_View_سڌو_Bool = 2105,
	ETrackedDeviceProperty_Prop_SupportsAppThrottling_Bool = 2106,
	ETrackedDeviceProperty_Prop_DSCVersion_Int32 = 2110,
	ETracked_Device_Property_Prop_DSCSlice_ڳڻپ_Int32 = 2111,
	ETrackedDeviceProperty_Prop_DSCBPPx16_Int32 = 2112,
	ETracked_Device_Property_Prop_Driver_Requested_Mura_Correction_گهڻائي_Int32 = 2200,
	ETracked_Device_Property_Prop_Driver_Requested_Mura_Feather_Inner_کاٻو_Int32 = 2201,
	ETracked_Device_Property_Prop_Driver_Requested_Mura_Feather_Inner_ساڄو_Int32 = 2202,
	ETracked_Device_Property_Prop_Driver_Requested_Mura_Feather_Inner_چوٽي_Int32 = 2203,
	ETrackedDeviceProperty_Prop_DriverRequestedMuraFeather_InnerBottom_Int32 = 2204,
	ETracked_Device_Property_Prop_Driver_Requested_Mura_Feather_Outer_کاٻو_Int32 = 2205,
	ETracked_Device_Property_Prop_Driver_Requested_Mura_Feather_Outer_ساڄو_Int32 = 2206,
	ETracked_Device_Property_Prop_Driver_Requested_Mura_Feather_Outer_چوٽي_Int32 = 2207,
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
	ETracked_Device_Property_Prop_ميدان_جو_View_کاٻو_Degrees_Float = 4000,
	ETracked_Device_Property_Prop_ميدان_جو_View_ساڄو_Degrees_Float = 4001,
	ETracked_Device_Property_Prop_ميدان_جو_View_چوٽي_Degrees_Float = 4002,
	ETracked_Device_Property_Prop_ميدان_جو_View_Bottom_Degrees_Float = 4003,
	ETrackedDeviceProperty_Prop_TrackingRangeMinimumMeters_Float = 4004,
	ETracked_Device_Property_Prop_Tracking_Range_وڌ_کان_وڌ_Meters_Float = 4005,
	ETracked_Device_Property_Prop_گهڻائي_Label_String = 4006,
	ETrackedDeviceProperty_Prop_CanWirelessIdentify_Bool = 4007,
	ETrackedDeviceProperty_Prop_Nonce_Int32 = 4008,
	ETracked_Device_Property_Prop_Icon_رستو_Name_String = 5000,
	ETracked_Device_Property_Prop_Named_Icon_رستو_Device_Off_String = 5001,
	ETracked_Device_Property_Prop_Named_Icon_رستو_Device_Searching_String = 5002,
	ETracked_Device_Property_Prop_Named_Icon_رستو_Device_Searching_Alert_String = 5003,
	ETracked_Device_Property_Prop_Named_Icon_رستو_Device_Ready_String = 5004,
	ETracked_Device_Property_Prop_Named_Icon_رستو_Device_Ready_Alert_String = 5005,
	ETracked_Device_Property_Prop_Named_Icon_رستو_Device_Not_Ready_String = 5006,
	ETracked_Device_Property_Prop_Named_Icon_رستو_Device_Standby_String = 5007,
	ETracked_Device_Property_Prop_Named_Icon_رستو_Device_Alert_هيٺيون_String = 5008,
	ETracked_Device_Property_Prop_Named_Icon_رستو_Device_Standby_Alert_String = 5009,
	ETracked_Device_Property_Prop_Display_Hidden_Area_ٻٽو_شروعات = 5100,
	ETracked_Device_Property_Prop_Display_Hidden_Area_ٻٽو_پڇاڙي = 5150,
	ETracked_Device_Property_Prop_والد_Container = 5151,
	ETrackedDeviceProperty_Prop_OverrideContainer_Uint64 = 5152,
	ETracked_Device_Property_Prop_User_Config_رستو_String = 6000,
	ETracked_Device_Property_Prop_Install_رستو_String = 6001,
	ETrackedDeviceProperty_Prop_HasDisplayComponent_Bool = 6002,
	ETrackedDeviceProperty_Prop_HasControllerComponent_Bool = 6003,
	ETrackedDeviceProperty_Prop_HasCameraComponent_Bool = 6004,
	ETracked_Device_Property_Prop_Has_Driver_سڌو_گهڻائي_Component_Bool = 6005,
	ETrackedDeviceProperty_Prop_HasVirtualDisplayComponent_Bool = 6006,
	ETrackedDeviceProperty_Prop_HasSpatialAnchorsSupport_Bool = 6007,
	ETrackedDeviceProperty_Prop_ControllerType_String = 7000,
	ETracked_Device_Property_Prop_Controller_Hand_Selection_ترجيح_Int32 = 7002,
	ETracked_Device_Property_Prop_Vendor_Specific_Reserved_شروعات = 10000,
	ETracked_Device_Property_Prop_Vendor_Specific_Reserved_پڇاڙي = 10999,
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
	ETracked_Property_Error_Tracked_Prop_قدر_Not_Provided_By_Device = 7,
	ETracked_Property_Error_Tracked_Prop_String_Exceeds_وڌ_کان_وڌ_ڊيگهائي = 8,
	ETracked_Property_Error_Tracked_Prop_Not_Yet_موجود = 9,
	ETrackedPropertyError_TrackedProp_PermissionDenied = 10,
	ETrackedPropertyError_TrackedProp_InvalidOperation = 11,
	ETracked_Property_Error_Tracked_Prop_Cannot_Write_منزل_Wildcards = 12,
	ETrackedPropertyError_TrackedProp_IPCReadFailure = 13,
	ETracked_Property_Error_Tracked_Prop_ٻاهريون_جو_يادگيري = 14,
	ETrackedPropertyError_TrackedProp_InvalidContainer = 15,
} ETrackedPropertyError;

تعريفنوع تعداد EHmdTrackingStyle
{
	EHmdTrackingStyle_HmdTrackingStyle_Unknown = 0,
	EHmdTrackingStyle_HmdTrackingStyle_Lighthouse = 1,
	EHmd_Tracking_Style_Hmd_Tracking_Style_Outside_اندريون_Cameras = 2,
	EHmd_Tracking_Style_Hmd_Tracking_Style_Inside_ٻاهريون_Cameras = 3,
} EHmdTrackingStyle;

تعريفنوع تعداد EVRSubmitFlags
{
	EVRSubmitFlags_Submit_Default = 0,
	EVRSubmitFlags_Submit_LensDistortionAlreadyApplied = 1,
	EVRSubmit_Flags_Submit_Gl_Render_بفر = 2,
	EVRSubmitFlags_Submit_Reserved = 4,
	EVRSubmitFlags_Submit_TextureWithPose = 8,
	EVRSubmit_Flags_Submit_Texture_With_اونهائي = 16,
	EVRSubmit_Flags_Submit_چوکٺو_Discontinuty = 32,
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
	EVRState_VRState_Ready_Alert_هيٺيون = 7,
} EVRState;

تعريفنوع تعداد EVREventType
{
	EVREventType_VREvent_None = 0,
	EVREventType_VREvent_TrackedDeviceActivated = 100,
	EVREventType_VREvent_TrackedDeviceDeactivated = 101,
	EVREventType_VREvent_TrackedDeviceUpdated = 102,
	EVREventType_VREvent_TrackedDeviceUserInteractionStarted = 103,
	EVREventType_VREvent_TrackedDeviceUserInteractionEnded = 104,
	EVREvent_Type_VREvent_Ipd_بدليو = 105,
	EVREvent_Type_VREvent_Enter_Standby_گهڻائي = 106,
	EVREvent_Type_VREvent_Leave_Standby_گهڻائي = 107,
	EVREvent_Type_VREvent_Tracked_Device_Role_بدليو = 108,
	EVREvent_Type_VREvent_Watchdog_Wake_مٿي_Requested = 109,
	EVREvent_Type_VREvent_Lens_Distortion_بدليو = 110,
	EVREvent_Type_VREvent_Property_بدليو = 111,
	EVREventType_VREvent_WirelessDisconnect = 112,
	EVREventType_VREvent_WirelessReconnect = 113,
	EVREventType_VREvent_ButtonPress = 200,
	EVREventType_VREvent_ButtonUnpress = 201,
	EVREventType_VREvent_ButtonTouch = 202,
	EVREventType_VREvent_ButtonUntouch = 203,
	EVREventType_VREvent_Modal_Cancel = 257,
	EVREventType_VREvent_MouseMove = 300,
	EVREvent_Type_VREvent_Mouse_Button_هيٺ_ڏانهن = 301,
	EVREvent_Type_VREvent_Mouse_Button_مٿي = 302,
	EVREventType_VREvent_FocusEnter = 303,
	EVREventType_VREvent_FocusLeave = 304,
	EVREventType_VREvent_ScrollDiscrete = 305,
	EVREventType_VREvent_TouchPadMove = 306,
	EVREvent_Type_VREvent_Overlay_Focus_بدليو = 307,
	EVREventType_VREvent_ReloadOverlays = 308,
	EVREventType_VREvent_ScrollSmooth = 309,
	EVREvent_Type_VREvent_تالو_Mouse_Position = 310,
	EVREventType_VREvent_UnlockMousePosition = 311,
	EVREvent_Type_VREvent_داخلا_Focus_Captured = 400,
	EVREvent_Type_VREvent_داخلا_Focus_Released = 401,
	EVREvent_Type_VREvent_Scene_Application_بدليو = 404,
	EVREvent_Type_VREvent_داخلا_Focus_بدليو = 406,
	EVREventType_VREvent_SceneApplicationUsingWrongGraphicsAdapter = 408,
	EVREventType_VREvent_ActionBindingReloaded = 409,
	EVREventType_VREvent_HideRenderModels = 410,
	EVREventType_VREvent_ShowRenderModels = 411,
	EVREvent_Type_VREvent_Scene_Application_State_بدليو = 412,
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
	EVREvent_Type_VREvent_Overlay_Gamepad_Focus_گم = 512,
	EVREvent_Type_VREvent_Overlay_Shared_Texture_بدليو = 513,
	EVREventType_VREvent_ScreenshotTriggered = 516,
	EVREventType_VREvent_ImageFailed = 517,
	EVREventType_VREvent_DashboardOverlayCreated = 518,
	EVREventType_VREvent_SwitchGamepadFocus = 519,
	EVREventType_VREvent_RequestScreenshot = 520,
	EVREvent_Type_VREvent_Screenshot_ورتل = 521,
	EVREventType_VREvent_ScreenshotFailed = 522,
	EVREvent_Type_VREvent_Submit_Screenshot_منزل_Dashboard = 523,
	EVREvent_Type_VREvent_Screenshot_ترقي_منزل_Dashboard = 524,
	EVREvent_Type_VREvent_Primary_Dashboard_Device_بدليو = 525,
	EVREvent_Type_VREvent_گنجائش_View_Shown = 526,
	EVREvent_Type_VREvent_گنجائش_View_Hidden = 527,
	EVREventType_VREvent_ShowUI = 528,
	EVREventType_VREvent_ShowDevTools = 529,
	EVREventType_VREvent_DesktopViewUpdating = 530,
	EVREventType_VREvent_DesktopViewReady = 531,
	EVREvent_Type_VREvent_شروعات_Dashboard = 532,
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
	EVREvent_Type_VREvent_Invalidate_مٽا_سٽا_Texture_Sets = 706,
	EVREvent_Type_VREvent_Chaperone_معلومات_Has_بدليو = 800,
	EVREvent_Type_VREvent_Chaperone_Universe_Has_بدليو = 801,
	EVREvent_Type_VREvent_Chaperone_عارضي_معلومات_Has_بدليو = 802,
	EVREvent_Type_VREvent_Chaperone_Settings_Have_بدليو = 803,
	EVREventType_VREvent_SeatedZeroPoseReset = 804,
	EVREventType_VREvent_ChaperoneFlushCache = 805,
	EVREvent_Type_VREvent_Chaperone_گنجائش_تياري_Starting = 806,
	EVREvent_Type_VREvent_Chaperone_گنجائش_تياري_ختم = 807,
	EVREventType_VREvent_StandingZeroPoseReset = 808,
	EVREvent_Type_VREvent_Audio_Settings_Have_بدليو = 820,
	EVREvent_Type_VREvent_Background_Setting_Has_بدليو = 850,
	EVREvent_Type_VREvent_Camera_Settings_Have_بدليو = 851,
	EVREvent_Type_VREvent_Reprojection_Setting_Has_بدليو = 852,
	EVREvent_Type_VREvent_Model_Skin_Settings_Have_بدليو = 853,
	EVREvent_Type_VREvent_Environment_Settings_Have_بدليو = 854,
	EVREvent_Type_VREvent_Power_Settings_Have_بدليو = 855,
	EVREvent_Type_VREvent_Enable_Home_App_Settings_Have_بدليو = 856,
	EVREvent_Type_VREvent_Steam_VRSection_Setting_بدليو = 857,
	EVREvent_Type_VREvent_Lighthouse_Section_Setting_بدليو = 858,
	EVREvent_Type_VREvent_Null_Section_Setting_بدليو = 859,
	EVREvent_Type_VREvent_User_Interface_Section_Setting_بدليو = 860,
	EVREvent_Type_VREvent_Notifications_Section_Setting_بدليو = 861,
	EVREvent_Type_VREvent_Keyboard_Section_Setting_بدليو = 862,
	EVREvent_Type_VREvent_Perf_Section_Setting_بدليو = 863,
	EVREvent_Type_VREvent_Dashboard_Section_Setting_بدليو = 864,
	EVREvent_Type_VREvent_Web_Interface_Section_Setting_بدليو = 865,
	EVREvent_Type_VREvent_Trackers_Section_Setting_بدليو = 866,
	EVREvent_Type_VREvent_آخري_معلوم_Section_Setting_بدليو = 867,
	EVREvent_Type_VREvent_Dismissed_Warnings_Section_Setting_بدليو = 868,
	EVREvent_Type_VREvent_Gpu_رفتار_Section_Setting_بدليو = 869,
	EVREvent_Type_VREvent_Windows_MRSection_Setting_بدليو = 870,
	EVREvent_Type_VREvent_Other_Section_Setting_بدليو = 871,
	EVREvent_Type_VREvent_حالت_Update = 900,
	EVREventType_VREvent_WebInterface_InstallDriverCompleted = 950,
	EVREventType_VREvent_MCImageUpdated = 1000,
	EVREventType_VREvent_FirmwareUpdateStarted = 1100,
	EVREvent_Type_VREvent_Firmware_Update_ختم = 1101,
	EVREventType_VREvent_KeyboardClosed = 1200,
	EVREvent_Type_VREvent_Keyboard_Char_داخلا = 1201,
	EVREvent_Type_VREvent_Keyboard_پورو = 1202,
	EVREventType_VREvent_ApplicationListUpdated = 1303,
	EVREvent_Type_VREvent_Application_Mime_Type_ڀريو = 1304,
	EVREventType_VREvent_ProcessConnected = 1306,
	EVREventType_VREvent_ProcessDisconnected = 1307,
	EVREventType_VREvent_Compositor_ChaperoneBoundsShown = 1410,
	EVREventType_VREvent_Compositor_ChaperoneBoundsHidden = 1411,
	EVREventType_VREvent_Compositor_DisplayDisconnected = 1412,
	EVREventType_VREvent_Compositor_DisplayReconnected = 1413,
	EVREventType_VREvent_Compositor_HDCPError = 1414,
	EVREventType_VREvent_Compositor_ApplicationNotResponding = 1415,
	EVREventType_VREvent_Compositor_ApplicationResumed = 1416,
	EVREvent_Type_VREvent_Compositor_ٻاهريون_جو_Video_يادگيري = 1417,
	EVREvent_Type_VREvent_Compositor_Display_گهڻائي_Not_Supported = 1418,
	EVREventType_VREvent_Compositor_StageOverrideReady = 1419,
	EVREventType_VREvent_Compositor_RequestDisconnectReconnect = 1420,
	EVREvent_Type_VREvent_Tracked_Camera_شروعات_Video_وهڪرو = 1500,
	EVREvent_Type_VREvent_Tracked_Camera_Stop_Video_وهڪرو = 1501,
	EVREvent_Type_VREvent_Tracked_Camera_Pause_Video_وهڪرو = 1502,
	EVREvent_Type_VREvent_Tracked_Camera_Resume_Video_وهڪرو = 1503,
	EVREventType_VREvent_TrackedCamera_EditingSurface = 1550,
	EVREventType_VREvent_PerformanceTest_EnableCapture = 1600,
	EVREventType_VREvent_PerformanceTest_DisableCapture = 1601,
	EVREventType_VREvent_PerformanceTest_FidelityLevel = 1602,
	EVREvent_Type_VREvent_پيغام_Overlay_Closed = 1650,
	EVREvent_Type_VREvent_پيغام_Overlay_Close_Requested = 1651,
	EVREvent_Type_VREvent_داخلا_Haptic_Vibration = 1700,
	EVREvent_Type_VREvent_داخلا_Binding_ڀريو_Failed = 1701,
	EVREvent_Type_VREvent_داخلا_Binding_ڀريو_Successful = 1702,
	EVREvent_Type_VREvent_داخلا_Action_Manifest_Reloaded = 1703,
	EVREvent_Type_VREvent_داخلا_Action_Manifest_ڀريو_Failed = 1704,
	EVREvent_Type_VREvent_داخلا_ترقي_Update = 1705,
	EVREvent_Type_VREvent_داخلا_Tracker_Activated = 1706,
	EVREvent_Type_VREvent_داخلا_Bindings_Updated = 1707,
	EVREvent_Type_VREvent_داخلا_Binding_Subscription_بدليو = 1708,
	EVREventType_VREvent_SpatialAnchors_PoseUpdated = 1800,
	EVREventType_VREvent_SpatialAnchors_DescriptorUpdated = 1801,
	EVREventType_VREvent_SpatialAnchors_RequestPoseUpdate = 1802,
	EVREventType_VREvent_SpatialAnchors_RequestDescriptorUpdate = 1803,
	EVREventType_VREvent_SystemReport_Started = 1900,
	EVREventType_VREvent_Monitor_ShowHeadsetView = 2000,
	EVREventType_VREvent_Monitor_HideHeadsetView = 2001,
	EVREvent_Type_VREvent_Vendor_Specific_Reserved_شروعات = 10000,
	EVREvent_Type_VREvent_Vendor_Specific_Reserved_پڇاڙي = 19999,
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
	EVRButton_Id_k_EButton_DPad_کاٻو = 3,
	EVRButton_Id_k_EButton_DPad_مٿي = 4,
	EVRButton_Id_k_EButton_DPad_ساڄو = 5,
	EVRButton_Id_k_EButton_DPad_هيٺ_ڏانهن = 6,
	EVRButtonId_k_EButton_A = 7,
	EVRButtonId_k_EButton_ProximitySensor = 31,
	EVRButtonId_k_EButton_Axis0 = 32,
	EVRButtonId_k_EButton_Axis1 = 33,
	EVRButtonId_k_EButton_Axis2 = 34,
	EVRButtonId_k_EButton_Axis3 = 35,
	EVRButtonId_k_EButton_Axis4 = 36,
	EVRButtonId_k_EButton_SteamVR_Touchpad = 32,
	EVRButtonId_k_EButton_SteamVR_Trigger = 33,
	EVRButton_Id_k_EButton_Dashboard_پٺ = 2,
	EVRButton_Id_k_EButton_اشاريو_Controller_A = 2,
	EVRButton_Id_k_EButton_اشاريو_Controller_B = 1,
	EVRButton_Id_k_EButton_اشاريو_Controller_Joy_Stick = 35,
	EVRButtonId_k_EButton_Max = 64,
} EVRButtonId;

تعريفنوع تعداد EVRMouseButton
{
	EVRMouse_Button_VRMouse_Button_کاٻو = 1,
	EVRMouse_Button_VRMouse_Button_ساڄو = 2,
	EVRMouse_Button_VRMouse_Button_وچ = 4,
} EVRMouseButton;

تعريفنوع تعداد EShowUIType
{
	EShowUIType_ShowUI_ControllerBinding = 0,
	EShowUIType_ShowUI_ManageTrackers = 1,
	EShowUIType_ShowUI_Pairing = 3,
	EShowUIType_ShowUI_Settings = 4,
	EShowUIType_ShowUI_DebugCommands = 5,
	EShow_UIType_Show_UI_ڀريل_Controller_Binding = 6,
	EShowUIType_ShowUI_ManageDrivers = 7,
} EShowUIType;

تعريفنوع تعداد EHDCPError
{
	EHDCPError_HDCPError_None = 0,
	EHDCPError_HDCPError_Link_گم = 1,
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
	EVRInput_Error_VRInput_Error_Name_Not_مليو = 1,
	EVRInputError_VRInputError_WrongType = 2,
	EVRInputError_VRInputError_InvalidHandle = 3,
	EVRInputError_VRInputError_InvalidParam = 4,
	EVRInputError_VRInputError_NoSteam = 5,
	EVRInput_Error_VRInput_Error_Max_صلاحيت_Reached = 6,
	EVRInputError_VRInputError_IPCError = 7,
	EVRInput_Error_VRInput_Error_No_سرگرم_Action_سيٽ = 8,
	EVRInputError_VRInputError_InvalidDevice = 9,
	EVRInputError_VRInputError_InvalidSkeleton = 10,
	EVRInput_Error_VRInput_Error_Invalid_Bone_ڳڻپ = 11,
	EVRInput_Error_VRInput_Error_Invalid_Compressed_معلومات = 12,
	EVRInput_Error_VRInput_Error_No_معلومات = 13,
	EVRInput_Error_VRInput_Error_بفر_Too_Small = 14,
	EVRInputError_VRInputError_MismatchedActionManifest = 15,
	EVRInput_Error_VRInput_Error_Missing_Skeleton_معلومات = 16,
	EVRInput_Error_VRInput_Error_Invalid_Bone_اشاريو = 17,
	EVRInput_Error_VRInput_Error_Invalid_ترجيح = 18,
	EVRInputError_VRInputError_PermissionDenied = 19,
	EVRInputError_VRInputError_InvalidRenderModel = 20,
} EVRInputError;

تعريفنوع تعداد EVRSpatialAnchorError
{
	EVRSpatialAnchorError_VRSpatialAnchorError_Success = 0,
	EVRSpatial_Anchor_Error_VRSpatial_Anchor_Error_اندروني = 1,
	EVRSpatialAnchorError_VRSpatialAnchorError_UnknownHandle = 2,
	EVRSpatialAnchorError_VRSpatialAnchorError_ArrayTooSmall = 3,
	EVRSpatialAnchorError_VRSpatialAnchorError_InvalidDescriptorChar = 4,
	EVRSpatial_Anchor_Error_VRSpatial_Anchor_Error_Not_Yet_موجود = 5,
	EVRSpatial_Anchor_Error_VRSpatial_Anchor_Error_Not_موجود_اندريون_This_Universe = 6,
	EVRSpatialAnchorError_VRSpatialAnchorError_PermanentlyUnavailable = 7,
	EVRSpatialAnchorError_VRSpatialAnchorError_WrongDriver = 8,
	EVRSpatialAnchorError_VRSpatialAnchorError_DescriptorTooLong = 9,
	EVRSpatialAnchorError_VRSpatialAnchorError_Unknown = 10,
	EVRSpatial_Anchor_Error_VRSpatial_Anchor_Error_No_گنجائش_Calibration = 11,
	EVRSpatial_Anchor_Error_VRSpatial_Anchor_Error_Invalid_دليل = 12,
	EVRSpatialAnchorError_VRSpatialAnchorError_UnknownDriver = 13,
} EVRSpatialAnchorError;

تعريفنوع تعداد EHiddenAreaMeshType
{
	EHiddenAreaMeshType_k_eHiddenAreaMesh_Standard = 0,
	EHiddenAreaMeshType_k_eHiddenAreaMesh_Inverse = 1,
	EHidden_Area_Mesh_Type_k_e_Hidden_Area_Mesh_سٽ_Loop = 2,
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
	ECollision_Bounds_Style_COLLISION_BOUNDS_STYLE_ڳڻپ = 5,
} ECollisionBoundsStyle;

تعريفنوع تعداد EVROverlayError
{
	EVROverlayError_VROverlayError_None = 0,
	EVROverlayError_VROverlayError_UnknownOverlay = 10,
	EVROverlayError_VROverlayError_InvalidHandle = 11,
	EVROverlayError_VROverlayError_PermissionDenied = 12,
	EVROverlay_Error_VROverlay_Error_Overlay_حد_بندي_Exceeded = 13,
	EVROverlayError_VROverlayError_WrongVisibilityType = 14,
	EVROverlay_Error_VROverlay_Error_ڪنجي_Too_Long = 15,
	EVROverlayError_VROverlayError_NameTooLong = 16,
	EVROverlay_Error_VROverlay_Error_ڪنجي_اندريون_Use = 17,
	EVROverlayError_VROverlayError_WrongTransformType = 18,
	EVROverlayError_VROverlayError_InvalidTrackedDevice = 19,
	EVROverlayError_VROverlayError_InvalidParameter = 20,
	EVROverlayError_VROverlayError_ThumbnailCantBeDestroyed = 21,
	EVROverlayError_VROverlayError_ArrayTooSmall = 22,
	EVROverlayError_VROverlayError_RequestFailed = 23,
	EVROverlayError_VROverlayError_InvalidTexture = 24,
	EVROverlay_Error_VROverlay_Error_Unable_منزل_ڀريو_File = 25,
	EVROverlay_Error_VROverlay_Error_Keyboard_Already_اندريون_Use = 26,
	EVROverlayError_VROverlayError_NoNeighbor = 27,
	EVROverlay_Error_VROverlay_Error_Too_Many_نقاب_Primitives = 29,
	EVROverlay_Error_VROverlay_Error_Bad_نقاب_Primitive = 30,
	EVROverlayError_VROverlayError_TextureAlreadyLocked = 31,
	EVROverlay_Error_VROverlay_Error_Texture_تالو_صلاحيت_Reached = 32,
	EVROverlayError_VROverlayError_TextureNotLocked = 33,
	EVROverlay_Error_VROverlay_Error_Timed_ٻاهريون = 34,
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
	EVRApplication_Type_VRApplication_گنجائش_View = 13,
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
	EVRNotification_Error_VRNotification_Error_Notification_قطار_ڀريل = 101,
	EVRNotificationError_VRNotificationError_InvalidOverlayHandle = 102,
	EVRNotification_Error_VRNotification_Error_System_With_User_قدر_Already_Exists = 103,
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
	EVRSkeletal_Tracking_Level_VRSkeletal_Tracking_ڀريل = 2,
	EVRSkeletal_Tracking_Level_VRSkeletal_Tracking_Level_ڳڻپ = 3,
	EVRSkeletalTrackingLevel_VRSkeletalTrackingLevel_Max = 2,
} EVRSkeletalTrackingLevel;

تعريفنوع تعداد EVRInitError
{
	EVRInitError_VRInitError_None = 0,
	EVRInitError_VRInitError_Unknown = 1,
	EVRInit_Error_VRInit_Error_Init_Installation_Not_مليو = 100,
	EVRInitError_VRInitError_Init_InstallationCorrupt = 101,
	EVRInit_Error_VRInit_Error_Init_VRClient_DLLNot_مليو = 102,
	EVRInit_Error_VRInit_Error_Init_File_Not_مليو = 103,
	EVRInit_Error_VRInit_Error_Init_Factory_Not_مليو = 104,
	EVRInit_Error_VRInit_Error_Init_Interface_Not_مليو = 105,
	EVRInitError_VRInitError_Init_InvalidInterface = 106,
	EVRInitError_VRInitError_Init_UserConfigDirectoryInvalid = 107,
	EVRInit_Error_VRInit_Error_Init_Hmd_Not_مليو = 108,
	EVRInitError_VRInitError_Init_NotInitialized = 109,
	EVRInit_Error_VRInit_Error_Init_رستو_Registry_Not_مليو = 110,
	EVRInit_Error_VRInit_Error_Init_No_Config_رستو = 111,
	EVRInit_Error_VRInit_Error_Init_No_Log_رستو = 112,
	EVRInit_Error_VRInit_Error_Init_رستو_Registry_Not_Writable = 113,
	EVRInitError_VRInitError_Init_AppInfoInitFailed = 114,
	EVRInitError_VRInitError_Init_Retry = 115,
	EVRInitError_VRInitError_Init_InitCanceledByUser = 116,
	EVRInitError_VRInitError_Init_AnotherAppLaunching = 117,
	EVRInitError_VRInitError_Init_SettingsInitFailed = 118,
	EVRInit_Error_VRInit_Error_Init_Shutting_هيٺ_ڏانهن = 119,
	EVRInitError_VRInitError_Init_TooManyObjects = 120,
	EVRInitError_VRInitError_Init_NoServerForBackgroundApp = 121,
	EVRInitError_VRInitError_Init_NotSupportedWithCompositor = 122,
	EVRInit_Error_VRInit_Error_Init_Not_موجود_منزل_Utility_Apps = 123,
	EVRInit_Error_VRInit_Error_Init_اندروني = 124,
	EVRInitError_VRInitError_Init_HmdDriverIdIsNone = 125,
	EVRInit_Error_VRInit_Error_Init_Hmd_Not_مليو_Presence_Failed = 126,
	EVRInit_Error_VRInit_Error_Init_VRMonitor_Not_مليو = 127,
	EVRInitError_VRInitError_Init_VRMonitorStartupFailed = 128,
	EVRInit_Error_VRInit_Error_Init_هيٺيون_Power_Watchdog_Not_Supported = 129,
	EVRInitError_VRInitError_Init_InvalidApplicationType = 130,
	EVRInit_Error_VRInit_Error_Init_Not_موجود_منزل_Watchdog_Apps = 131,
	EVRInit_Error_VRInit_Error_Init_Watchdog_Disabled_اندريون_Settings = 132,
	EVRInit_Error_VRInit_Error_Init_VRDashboard_Not_مليو = 133,
	EVRInitError_VRInitError_Init_VRDashboardStartupFailed = 134,
	EVRInit_Error_VRInit_Error_Init_VRHome_Not_مليو = 135,
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
	EVRInit_Error_VRInit_Error_Init_Prism_Startup_Timed_ٻاهريون = 152,
	EVRInit_Error_VRInit_Error_Init_Could_Not_شروعات_Prism = 153,
	EVRInitError_VRInitError_Init_PrismClientInitFailed = 154,
	EVRInit_Error_VRInit_Error_Init_Prism_Client_شروعات_Failed = 155,
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
	EVRInit_Error_VRInit_Error_Init_VRDashboard_رستو_Failure = 167,
	EVRInitError_VRInitError_Driver_Failed = 200,
	EVRInitError_VRInitError_Driver_Unknown = 201,
	EVRInitError_VRInitError_Driver_HmdUnknown = 202,
	EVRInitError_VRInitError_Driver_NotLoaded = 203,
	EVRInit_Error_VRInit_Error_Driver_Runtime_ٻاهريون_جو_Date = 204,
	EVRInit_Error_VRInit_Error_Driver_Hmd_اندريون_Use = 205,
	EVRInitError_VRInitError_Driver_NotCalibrated = 206,
	EVRInitError_VRInitError_Driver_CalibrationInvalid = 207,
	EVRInit_Error_VRInit_Error_Driver_Hmd_Display_Not_مليو = 208,
	EVRInitError_VRInitError_Driver_TrackedDeviceInterfaceUnknown = 209,
	EVRInit_Error_VRInit_Error_Driver_Hmd_Driver_Id_ٻاهريون_جو_Bounds = 211,
	EVRInitError_VRInitError_Driver_HmdDisplayMirrored = 212,
	EVRInit_Error_VRInit_Error_Driver_Hmd_Display_Not_مليو_Laptop = 213,
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
	EVRInit_Error_VRInit_Error_IPC_Connect_Failed_After_گڻو_Attempts = 308,
	EVRInit_Error_VRInit_Error_IPC_Connect_Failed_After_هدف_Exited = 309,
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
	EVRInit_Error_VRInit_Error_Compositor_پيغام_Overlay_Shared_State_Init_Failure = 409,
	EVRInitError_VRInitError_Compositor_PropertiesInterfaceIsNull = 410,
	EVRInit_Error_VRInit_Error_Compositor_Create_Fullscreen_دري_Failed = 411,
	EVRInitError_VRInitError_Compositor_SettingsInterfaceIsNull = 412,
	EVRInit_Error_VRInit_Error_Compositor_Failed_منزل_Show_دري = 413,
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
	EVRInit_Error_VRInit_Error_Compositor_Failed_منزل_ڳوليو_Display_گهڻائي = 425,
	EVRInit_Error_VRInit_Error_Compositor_Failed_منزل_Create_مٽا_سٽا_Chain = 426,
	EVRInit_Error_VRInit_Error_Compositor_Failed_منزل_Get_پٺ_بفر = 427,
	EVRInit_Error_VRInit_Error_Compositor_Failed_منزل_Create_Render_هدف = 428,
	EVRInit_Error_VRInit_Error_Compositor_Failed_منزل_Create_DXGI2_مٽا_سٽا_Chain = 429,
	EVRInit_Error_VRInit_Error_Compositor_Failedto_Get_DXGI2_پٺ_بفر = 430,
	EVRInit_Error_VRInit_Error_Compositor_Failed_منزل_Create_DXGI2_Render_هدف = 431,
	EVRInit_Error_VRInit_Error_Compositor_Failed_منزل_Get_DXGIDevice_Interface = 432,
	EVRInit_Error_VRInit_Error_Compositor_Select_Display_گهڻائي = 433,
	EVRInit_Error_VRInit_Error_Compositor_Failed_منزل_Create_Nv_APIRender_Targets = 434,
	EVRInit_Error_VRInit_Error_Compositor_Nv_APISet_Display_گهڻائي = 435,
	EVRInit_Error_VRInit_Error_Compositor_Failed_منزل_Create_سڌو_گهڻائي_Display = 436,
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
	EVRInit_Error_VRInit_Error_Compositor_Create_Blend_State_نقاب_R = 450,
	EVRInit_Error_VRInit_Error_Compositor_Create_Blend_State_نقاب_G = 451,
	EVRInit_Error_VRInit_Error_Compositor_Create_Blend_State_نقاب_B = 452,
	EVRInit_Error_VRInit_Error_Compositor_Create_اونهائي_Stencil_State = 453,
	EVRInit_Error_VRInit_Error_Compositor_Create_اونهائي_Stencil_State_No_Write = 454,
	EVRInit_Error_VRInit_Error_Compositor_Create_اونهائي_Stencil_State_No_اونهائي = 455,
	EVRInitError_VRInitError_Compositor_CreateFlushTexture = 456,
	EVRInitError_VRInitError_Compositor_CreateDistortionSurfaces = 457,
	EVRInit_Error_VRInit_Error_Compositor_Create_Constant_بفر = 458,
	EVRInit_Error_VRInit_Error_Compositor_Create_Hmd_Pose_Constant_بفر = 459,
	EVRInit_Error_VRInit_Error_Compositor_Create_Hmd_Pose_Staging_Constant_بفر = 460,
	EVRInit_Error_VRInit_Error_Compositor_Create_Shared_چوکٺو_Info_Constant_بفر = 461,
	EVRInit_Error_VRInit_Error_Compositor_Create_Overlay_Constant_بفر = 462,
	EVRInit_Error_VRInit_Error_Compositor_Create_Scene_Texture_اشاريو_Constant_بفر = 463,
	EVRInit_Error_VRInit_Error_Compositor_Create_Readable_Scene_Texture_اشاريو_Constant_بفر = 464,
	EVRInit_Error_VRInit_Error_Compositor_Create_Layer_Graphics_Texture_اشاريو_Constant_بفر = 465,
	EVRInit_Error_VRInit_Error_Compositor_Create_Layer_Compute_Texture_اشاريو_Constant_بفر = 466,
	EVRInit_Error_VRInit_Error_Compositor_Create_Layer_Compute_Scene_Texture_اشاريو_Constant_بفر = 467,
	EVRInit_Error_VRInit_Error_Compositor_Create_Compute_Hmd_Pose_Constant_بفر = 468,
	EVRInit_Error_VRInit_Error_Compositor_Create_Geom_Constant_بفر = 469,
	EVRInit_Error_VRInit_Error_Compositor_Create_Panel_نقاب_Constant_بفر = 470,
	EVRInitError_VRInitError_Compositor_CreatePixelSimUBO = 471,
	EVRInitError_VRInitError_Compositor_CreateMSAARenderTextures = 472,
	EVRInitError_VRInitError_Compositor_CreateResolveRenderTextures = 473,
	EVRInitError_VRInitError_Compositor_CreateComputeResolveRenderTextures = 474,
	EVRInit_Error_VRInit_Error_Compositor_Create_Driver_سڌو_گهڻائي_Resolve_Textures = 475,
	EVRInit_Error_VRInit_Error_Compositor_Open_Driver_سڌو_گهڻائي_Resolve_Textures = 476,
	EVRInitError_VRInitError_Compositor_CreateFallbackSyncTexture = 477,
	EVRInitError_VRInitError_Compositor_ShareFallbackSyncTexture = 478,
	EVRInit_Error_VRInit_Error_Compositor_Create_Overlay_اشاريو_بفر = 479,
	EVRInit_Error_VRInit_Error_Compositor_Create_Overlay_راس_بفر = 480,
	EVRInit_Error_VRInit_Error_Compositor_Create_متن_راس_بفر = 481,
	EVRInit_Error_VRInit_Error_Compositor_Create_متن_اشاريو_بفر = 482,
	EVRInitError_VRInitError_Compositor_CreateMirrorTextures = 483,
	EVRInit_Error_VRInit_Error_Compositor_Create_آخري_چوکٺو_Render_Texture = 484,
	EVRInitError_VRInitError_Compositor_CreateMirrorOverlay = 485,
	EVRInit_Error_VRInit_Error_Compositor_Failed_منزل_Create_Virtual_Display_Backbuffer = 486,
	EVRInit_Error_VRInit_Error_Compositor_Display_گهڻائي_Not_Supported = 487,
	EVRInitError_VRInitError_Compositor_CreateOverlayInvalidCall = 488,
	EVRInitError_VRInitError_Compositor_CreateOverlayAlreadyInitialized = 489,
	EVRInit_Error_VRInit_Error_Compositor_Failed_منزل_Create_Mailbox = 490,
	EVRInit_Error_VRInit_Error_Compositor_دري_Interface_Is_Null = 491,
	EVRInitError_VRInitError_Compositor_SystemLayerCreateInstance = 492,
	EVRInitError_VRInitError_Compositor_SystemLayerCreateSession = 493,
	EVRInitError_VRInitError_Compoistor_CreateInverseDistortUVs = 494,
	EVRInit_Error_VRInit_Error_Compoistor_Create_Backbuffer_اونهائي = 495,
	EVRInit_Error_VRInit_Error_Vendor_Specific_Unable_منزل_Connect_منزل_Oculus_Runtime = 1000,
	EVRInit_Error_VRInit_Error_Vendor_Specific_Windows_Not_اندريون_Dev_گهڻائي = 1001,
	EVRInitError_VRInitError_VendorSpecific_OculusLinkNotEnabled = 1002,
	EVRInit_Error_VRInit_Error_Vendor_Specific_Hmd_مليو_Cant_Open_Device = 1101,
	EVRInit_Error_VRInit_Error_Vendor_Specific_Hmd_مليو_Unable_منزل_Request_Config_شروعات = 1102,
	EVRInit_Error_VRInit_Error_Vendor_Specific_Hmd_مليو_No_Stored_Config = 1103,
	EVRInit_Error_VRInit_Error_Vendor_Specific_Hmd_مليو_Config_Too_Big = 1104,
	EVRInit_Error_VRInit_Error_Vendor_Specific_Hmd_مليو_Config_Too_Small = 1105,
	EVRInit_Error_VRInit_Error_Vendor_Specific_Hmd_مليو_Unable_منزل_Init_ZLib = 1106,
	EVRInit_Error_VRInit_Error_Vendor_Specific_Hmd_مليو_Cant_Read_Firmware_نسخو = 1107,
	EVRInit_Error_VRInit_Error_Vendor_Specific_Hmd_مليو_Unable_منزل_Send_User_معلومات_شروعات = 1108,
	EVRInit_Error_VRInit_Error_Vendor_Specific_Hmd_مليو_Unable_منزل_Get_User_معلومات_شروعات = 1109,
	EVRInit_Error_VRInit_Error_Vendor_Specific_Hmd_مليو_Unable_منزل_Get_User_معلومات_ايندڙ = 1110,
	EVRInit_Error_VRInit_Error_Vendor_Specific_Hmd_مليو_User_معلومات_پتو_Range = 1111,
	EVRInit_Error_VRInit_Error_Vendor_Specific_Hmd_مليو_User_معلومات_Error = 1112,
	EVRInit_Error_VRInit_Error_Vendor_Specific_Hmd_مليو_Config_Failed_Sanity_Check = 1113,
	EVRInitError_VRInitError_VendorSpecific_OculusRuntimeBadInstall = 1114,
	EVRInit_Error_VRInit_Error_Vendor_Specific_Hmd_مليو_Unexpected_Configuration_1 = 1115,
	EVRInit_Error_VRInit_Error_Steam_Steam_Installation_Not_مليو = 2000,
	EVRInit_Error_VRInit_Error_آخري_Error = 2001,
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
	EVRTracked_Camera_Error_VRTracked_Camera_Error_Invalid_چوکٺو_سرو_نسخو = 102,
	EVRTracked_Camera_Error_VRTracked_Camera_Error_ٻاهريون_جو_Handles = 103,
	EVRTrackedCameraError_VRTrackedCameraError_IPCFailure = 104,
	EVRTrackedCameraError_VRTrackedCameraError_NotSupportedForThisDevice = 105,
	EVRTracked_Camera_Error_VRTracked_Camera_Error_Shared_يادگيري_Failure = 106,
	EVRTracked_Camera_Error_VRTracked_Camera_Error_چوکٺو_Buffering_Failure = 107,
	EVRTracked_Camera_Error_VRTracked_Camera_Error_وهڪرو_تياري_Failure = 108,
	EVRTrackedCameraError_VRTrackedCameraError_InvalidGLTextureId = 109,
	EVRTrackedCameraError_VRTrackedCameraError_InvalidSharedTextureHandle = 110,
	EVRTracked_Camera_Error_VRTracked_Camera_Error_Failed_منزل_Get_GLTexture_Id = 111,
	EVRTrackedCameraError_VRTrackedCameraError_SharedTextureFailure = 112,
	EVRTracked_Camera_Error_VRTracked_Camera_Error_No_چوکٺو_موجود = 113,
	EVRTracked_Camera_Error_VRTracked_Camera_Error_Invalid_دليل = 114,
	EVRTracked_Camera_Error_VRTracked_Camera_Error_Invalid_چوکٺو_بفر_سائيز = 115,
} EVRTrackedCameraError;

تعريفنوع تعداد EVRTracked_Camera_چوکٺو_Layout
{
	EVRTracked_Camera_چوکٺو_Layout_Mono = 1,
	EVRTracked_Camera_چوکٺو_Layout_Stereo = 2,
	EVRTracked_Camera_چوکٺو_Layout_Vertical_Layout = 16,
	EVRTracked_Camera_چوکٺو_Layout_Horizontal_Layout = 32,
} EVRTracked_Camera_چوکٺو_Layout;

تعريفنوع تعداد EVRTracked_Camera_چوکٺو_Type
{
	EVRTracked_Camera_چوکٺو_Type_VRTracked_Camera_چوکٺو_Type_Distorted = 0,
	EVRTracked_Camera_چوکٺو_Type_VRTracked_Camera_چوکٺو_Type_Undistorted = 1,
	EVRTracked_Camera_چوکٺو_Type_VRTracked_Camera_چوکٺو_Type_وڌ_کان_وڌ_Undistorted = 2,
	EVRTracked_Camera_چوکٺو_Type_MAX_CAMERA_چوکٺو_TYPES = 3,
} EVRTracked_Camera_چوکٺو_Type;

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

تعريفنوع تعداد EVRMura_Correction_گهڻائي
{
	EVRMura_Correction_گهڻائي_Default = 0,
	EVRMura_Correction_گهڻائي_No_Correction = 1,
} EVRMura_Correction_گهڻائي;

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
	EVRApplication_Error_VRApplication_Error_App_ڪنجي_Already_Exists = 100,
	EVRApplicationError_VRApplicationError_NoManifest = 101,
	EVRApplicationError_VRApplicationError_NoApplication = 102,
	EVRApplication_Error_VRApplication_Error_Invalid_اشاريو = 103,
	EVRApplicationError_VRApplicationError_UnknownApplication = 104,
	EVRApplicationError_VRApplicationError_IPCFailed = 105,
	EVRApplicationError_VRApplicationError_ApplicationAlreadyRunning = 106,
	EVRApplicationError_VRApplicationError_InvalidManifest = 107,
	EVRApplicationError_VRApplicationError_InvalidApplication = 108,
	EVRApplicationError_VRApplicationError_LaunchFailed = 109,
	EVRApplicationError_VRApplicationError_ApplicationAlreadyStarting = 110,
	EVRApplication_Error_VRApplication_Error_Launch_اندريون_ترقي = 111,
	EVRApplicationError_VRApplicationError_OldApplicationQuitting = 112,
	EVRApplicationError_VRApplicationError_TransitionAborted = 113,
	EVRApplicationError_VRApplicationError_IsTemplate = 114,
	EVRApplicationError_VRApplicationError_SteamVRIsExiting = 115,
	EVRApplication_Error_VRApplication_Error_بفر_Too_Small = 200,
	EVRApplication_Error_VRApplication_Error_Property_Not_سيٽ = 201,
	EVRApplicationError_VRApplicationError_UnknownProperty = 202,
	EVRApplicationError_VRApplicationError_InvalidParameter = 203,
	EVRApplicationError_VRApplicationError_NotImplemented = 300,
} EVRApplicationError;

تعريفنوع تعداد EVRApplicationProperty
{
	EVRApplicationProperty_VRApplicationProperty_Name_String = 0,
	EVRApplicationProperty_VRApplicationProperty_LaunchType_String = 11,
	EVRApplicationProperty_VRApplicationProperty_WorkingDirectory_String = 12,
	EVRApplication_Property_VRApplication_Property_ٻٽو_رستو_String = 13,
	EVRApplicationProperty_VRApplicationProperty_Arguments_String = 14,
	EVRApplicationProperty_VRApplicationProperty_URL_String = 15,
	EVRApplicationProperty_VRApplicationProperty_Description_String = 50,
	EVRApplicationProperty_VRApplicationProperty_NewsURL_String = 51,
	EVRApplication_Property_VRApplication_Property_Image_رستو_String = 52,
	EVRApplication_Property_VRApplication_Property_ذريعو_String = 53,
	EVRApplicationProperty_VRApplicationProperty_ActionManifestURL_String = 54,
	EVRApplicationProperty_VRApplicationProperty_IsDashboardOverlay_Bool = 60,
	EVRApplicationProperty_VRApplicationProperty_IsTemplate_Bool = 61,
	EVRApplicationProperty_VRApplicationProperty_IsInstanced_Bool = 62,
	EVRApplication_Property_VRApplication_Property_Is_اندروني_Bool = 63,
	EVRApplication_Property_VRApplication_Property_چاهي_Compositor_Pause_اندريون_Standby_Bool = 64,
	EVRApplicationProperty_VRApplicationProperty_IsHidden_Bool = 65,
	EVRApplication_Property_VRApplication_Property_آخري_Launch_وقت_Uint64 = 70,
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
	Chaperone_Calibration_State_Warning_بنياد_Station_May_Have_Moved = 101,
	Chaperone_Calibration_State_Warning_بنياد_Station_Removed = 102,
	ChaperoneCalibrationState_Warning_SeatedBoundsInvalid = 103,
	ChaperoneCalibrationState_Error = 200,
	Chaperone_Calibration_State_Error_بنياد_Station_Uninitialized = 201,
	Chaperone_Calibration_State_Error_بنياد_Station_Conflict = 202,
	ChaperoneCalibrationState_Error_PlayAreaInvalid = 203,
	ChaperoneCalibrationState_Error_CollisionBoundsInvalid = 204,
} ChaperoneCalibrationState;

تعريفنوع تعداد EChaperoneConfigFile
{
	EChaperone_Config_File_جيئرو = 1,
	EChaperone_Config_File_عارضي = 2,
} EChaperoneConfigFile;

تعريفنوع تعداد EChaperoneImportFlags
{
	EChaperoneImportFlags_EChaperoneImport_BoundsOnly = 1,
} EChaperoneImportFlags;

تعريفنوع تعداد EVRCompositorError
{
	EVRCompositorError_VRCompositorError_None = 0,
	EVRCompositorError_VRCompositorError_RequestFailed = 1,
	EVRCompositor_Error_VRCompositor_Error_Incompatible_نسخو = 100,
	EVRCompositorError_VRCompositorError_DoNotHaveFocus = 101,
	EVRCompositorError_VRCompositorError_InvalidTexture = 102,
	EVRCompositorError_VRCompositorError_IsNotSceneApplication = 103,
	EVRCompositorError_VRCompositorError_TextureIsOnWrongDevice = 104,
	EVRCompositor_Error_VRCompositor_Error_Texture_استعمال_ڪري_Unsupported_Format = 105,
	EVRCompositorError_VRCompositorError_SharedTexturesNotSupported = 106,
	EVRCompositor_Error_VRCompositor_Error_اشاريو_ٻاهريون_جو_Range = 107,
	EVRCompositorError_VRCompositorError_AlreadySubmitted = 108,
	EVRCompositorError_VRCompositorError_InvalidBounds = 109,
	EVRCompositor_Error_VRCompositor_Error_Already_سيٽ = 110,
} EVRCompositorError;

تعريفنوع تعداد EVRCompositor_Timing_گهڻائي
{
	EVRCompositor_Timing_گهڻائي_VRCompositor_Timing_گهڻائي_Implicit = 0,
	EVRCompositor_Timing_گهڻائي_VRCompositor_Timing_گهڻائي_Explicit_Runtime_Performs_Post_Present_Handoff = 1,
	EVRCompositor_Timing_گهڻائي_VRCompositor_Timing_گهڻائي_Explicit_Application_Performs_Post_Present_Handoff = 2,
} EVRCompositor_Timing_گهڻائي;

تعريفنوع تعداد VROverlay_داخلا_طريقو
{
	VROverlay_داخلا_طريقو_None = 0,
	VROverlay_داخلا_طريقو_Mouse = 1,
} VROverlay_داخلا_طريقو;

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
	VROverlay_Flags_Transfer_Ownership_منزل_اندروني_Process = 512,
	VROverlayFlags_SideBySide_Parallel = 1024,
	VROverlayFlags_SideBySide_Crossed = 2048,
	VROverlayFlags_Panorama = 4096,
	VROverlayFlags_StereoPanorama = 8192,
	VROverlay_Flags_ترتيب_ڏيو_With_Non_Scene_Overlays = 16384,
	VROverlay_Flags_Visible_اندريون_Dashboard = 32768,
	VROverlayFlags_MakeOverlaysInteractiveIfVisible = 65536,
	VROverlayFlags_SendVRSmoothScrollEvents = 131072,
	VROverlayFlags_ProtectedContent = 262144,
	VROverlayFlags_HideLaserIntersection = 524288,
	VROverlay_Flags_چاهي_Modal_Behavior = 1048576,
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
	VRMessage_Overlay_Response_Couldnt_ڳوليو_System_Overlay = 4,
	VRMessage_Overlay_Response_Couldnt_ڳوليو_Or_Create_Client_Overlay = 5,
	VRMessageOverlayResponse_ApplicationQuit = 6,
} VRMessageOverlayResponse;

تعريفنوع تعداد EGamepad_متن_داخلا_گهڻائي
{
	EGamepad_متن_داخلا_گهڻائي_k_EGamepad_متن_داخلا_گهڻائي_عام = 0,
	EGamepad_متن_داخلا_گهڻائي_k_EGamepad_متن_داخلا_گهڻائي_Password = 1,
	EGamepad_متن_داخلا_گهڻائي_k_EGamepad_متن_داخلا_گهڻائي_Submit = 2,
} EGamepad_متن_داخلا_گهڻائي;

تعريفنوع تعداد EGamepad_متن_داخلا_سٽ_گهڻائي
{
	EGamepad_متن_داخلا_سٽ_گهڻائي_k_EGamepad_متن_داخلا_سٽ_گهڻائي_Single_سٽ = 0,
	EGamepad_متن_داخلا_سٽ_گهڻائي_k_EGamepad_متن_داخلا_سٽ_گهڻائي_گڻو_سٽون = 1,
} EGamepad_متن_داخلا_سٽ_گهڻائي;

تعريفنوع تعداد EVROverlay_Intersection_نقاب_Primitive_Type
{
	EVROverlay_Intersection_نقاب_Primitive_Type_Overlay_Intersection_Primitive_Type_Rectangle = 0,
	EVROverlay_Intersection_نقاب_Primitive_Type_Overlay_Intersection_Primitive_Type_Circle = 1,
} EVROverlay_Intersection_نقاب_Primitive_Type;

تعريفنوع تعداد EKeyboardFlags
{
	EKeyboard_Flags_Keyboard_Flag_گهٽتر = 1,
	EKeyboardFlags_KeyboardFlag_Modal = 2,
} EKeyboardFlags;

تعريفنوع تعداد EDeviceType
{
	EDeviceType_DeviceType_Invalid = -1,
	EDevice_Type_Device_Type_سڌو_X11 = 0,
	EDeviceType_DeviceType_Vulkan = 1,
} EDeviceType;

تعريفنوع تعداد Headset_View_گهڻائي_t
{
	Headset_View_گهڻائي_t_Headset_View_گهڻائي_کاٻو = 0,
	Headset_View_گهڻائي_t_Headset_View_گهڻائي_ساڄو = 1,
	Headset_View_گهڻائي_t_Headset_View_گهڻائي_Both = 2,
} Headset_View_گهڻائي_t;

تعريفنوع تعداد EVRRenderModelError
{
	EVRRenderModelError_VRRenderModelError_None = 0,
	EVRRenderModelError_VRRenderModelError_Loading = 100,
	EVRRenderModelError_VRRenderModelError_NotSupported = 200,
	EVRRenderModelError_VRRenderModelError_InvalidArg = 300,
	EVRRenderModelError_VRRenderModelError_InvalidModel = 301,
	EVRRenderModelError_VRRenderModelError_NoShapes = 302,
	EVRRender_Model_Error_VRRender_Model_Error_گڻو_Shapes = 303,
	EVRRenderModelError_VRRenderModelError_TooManyVertices = 304,
	EVRRender_Model_Error_VRRender_Model_Error_گڻو_Textures = 305,
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
	EVRNotification_Type_Transient_System_With_User_قدر = 2,
} EVRNotificationType;

تعريفنوع تعداد EVRNotificationStyle
{
	EVRNotificationStyle_None = 0,
	EVRNotificationStyle_Application = 100,
	EVRNotificationStyle_Contact_Disabled = 200,
	EVRNotificationStyle_Contact_Enabled = 201,
	EVRNotification_Style_Contact_سرگرم = 202,
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
	EVRScreenshot_Error_VRScreenshot_Error_Incompatible_نسخو = 100,
	EVRScreenshot_Error_VRScreenshot_Error_Not_مليو = 101,
	EVRScreenshot_Error_VRScreenshot_Error_بفر_Too_Small = 102,
	EVRScreenshot_Error_VRScreenshot_Error_Screenshot_Already_اندريون_ترقي = 108,
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
	EVRSkeletal_Reference_Pose_VRSkeletal_Reference_Pose_Grip_حد_بندي = 3,
} EVRSkeletalReferencePose;

تعريفنوع تعداد EVRFinger
{
	EVRFinger_VRFinger_Thumb = 0,
	EVRFinger_VRFinger_اشاريو = 1,
	EVRFinger_VRFinger_وچ = 2,
	EVRFinger_VRFinger_Ring = 3,
	EVRFinger_VRFinger_Pinky = 4,
	EVRFinger_VRFinger_ڳڻپ = 5,
} EVRFinger;

تعريفنوع تعداد EVRFingerSplay
{
	EVRFinger_Splay_VRFinger_Splay_Thumb_اشاريو = 0,
	EVRFinger_Splay_VRFinger_Splay_اشاريو_وچ = 1,
	EVRFinger_Splay_VRFinger_Splay_وچ_Ring = 2,
	EVRFingerSplay_VRFingerSplay_Ring_Pinky = 3,
	EVRFinger_Splay_VRFinger_Splay_ڳڻپ = 4,
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

تعريفنوع تعداد EVRInput_String_بٽ
{
	EVRInput_String_بٽ_VRInput_String_Hand = 1,
	EVRInput_String_بٽ_VRInput_String_Controller_Type = 2,
	EVRInput_String_بٽ_VRInput_String_داخلا_ذريعو = 4,
	EVRInput_String_بٽ_VRInput_String_All = -1,
} EVRInput_String_بٽ;

تعريفنوع تعداد EIOBufferError
{
	EIOBufferError_IOBuffer_Success = 0,
	EIOBufferError_IOBuffer_OperationFailed = 100,
	EIOBufferError_IOBuffer_InvalidHandle = 101,
	EIOBuffer_Error_IOBuffer_Invalid_دليل = 102,
	EIOBuffer_Error_IOBuffer_رستو_Exists = 103,
	EIOBuffer_Error_IOBuffer_رستو_Does_Not_Exist = 104,
	EIOBufferError_IOBuffer_Permission = 105,
} EIOBufferError;

تعريفنوع تعداد EIOBuffer_گهڻائي
{
	EIOBuffer_گهڻائي_IOBuffer_گهڻائي_Read = 1,
	EIOBuffer_گهڻائي_IOBuffer_گهڻائي_Write = 2,
	EIOBuffer_گهڻائي_IOBuffer_گهڻائي_Create = 512,
} EIOBuffer_گهڻائي;

تعريفنوع تعداد EVRDebugError
{
	EVRDebugError_VRDebugError_Success = 0,
	EVRDebugError_VRDebugError_BadParameter = 1,
} EVRDebugError;

تعريفنوع تعداد EPropertyWriteType
{
	EProperty_Write_Type_Property_Write_سيٽ = 0,
	EPropertyWriteType_PropertyWrite_Erase = 1,
	EProperty_Write_Type_Property_Write_سيٽ_Error = 2,
} EPropertyWriteType;

تعريفنوع تعداد EBlock_قطار_Error
{
	EBlock_قطار_Error_بلاڪ_قطار_Error_None = 0,
	EBlock_قطار_Error_بلاڪ_قطار_Error_قطار_Already_Exists = 1,
	EBlock_قطار_Error_بلاڪ_قطار_Error_قطار_Not_مليو = 2,
	EBlock_قطار_Error_بلاڪ_قطار_Error_بلاڪ_Not_موجود = 3,
	EBlock_قطار_Error_بلاڪ_قطار_Error_Invalid_Handle = 4,
	EBlock_قطار_Error_بلاڪ_قطار_Error_Invalid_Param = 5,
	EBlock_قطار_Error_بلاڪ_قطار_Error_Param_Mismatch = 6,
	EBlock_قطار_Error_بلاڪ_قطار_Error_اندروني_Error = 7,
	EBlock_قطار_Error_بلاڪ_قطار_Error_Already_Initialized = 8,
	EBlock_قطار_Error_بلاڪ_قطار_Error_Operation_Is_Server_Only = 9,
	EBlock_قطار_Error_بلاڪ_قطار_Error_Too_Many_Connections = 10,
} EBlock_قطار_Error;

تعريفنوع تعداد EBlock_قطار_Read_Type
{
	EBlock_قطار_Read_Type_بلاڪ_قطار_Read_Latest = 0,
	EBlock_قطار_Read_Type_بلاڪ_قطار_Read_New = 1,
	EBlock_قطار_Read_Type_بلاڪ_قطار_Read_ايندڙ = 2,
} EBlock_قطار_Read_Type;

تعريفنوع تعداد EBlock_قطار_Creation_Flag
{
	EBlock_قطار_Creation_Flag_بلاڪ_قطار_Flag_Owner_Is_Reader = 1,
} EBlock_قطار_Creation_Flag;


// OpenVR typedefs

تعريفنوع uint32_t Property_Type_ٽيگ_t;
تعريفنوع uint32_t SpatialAnchorHandle_t;
تعريفنوع فراغ * glSharedTextureHandle_t;
تعريفنوع int32_t glInt_t;
تعريفنوع uint32_t glUInt_t;
تعريفنوع uint64_t SharedTextureHandle_t;
تعريفنوع uint32_t DriverId_t;
تعريفنوع uint32_t Tracked_Device_اشاريو_t;
تعريفنوع uint64_t WebConsoleHandle_t;
تعريفنوع uint64_t PropertyContainerHandle_t;
تعريفنوع PropertyContainerHandle_t DriverHandle_t;
تعريفنوع uint64_t VRActionHandle_t;
تعريفنوع uint64_t VRAction_سيٽ_Handle_t;
تعريفنوع uint64_t VRInput_قدر_Handle_t;
تعريفنوع uint32_t VRComponentProperties;
تعريفنوع uint64_t VROverlayHandle_t;
تعريفنوع int32_t Bone_اشاريو_t;
تعريفنوع uint64_t TrackedCameraHandle_t;
تعريفنوع uint32_t ScreenshotHandle_t;
تعريفنوع int32_t TextureID_t;
تعريفنوع uint32_t VRNotificationId;
تعريفنوع uint64_t IOBufferHandle_t;
تعريفنوع uint64_t VrProfilerEventHandle_t;
تعريفنوع EVRInitError HmdError;
تعريفنوع EVREye Hmd_Eye;
تعريفنوع EColorSpace ColorSpace;
تعريفنوع ETracking_نتيجو Hmd_Tracking_نتيجو;
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
تعريفنوع uint64_t رستو_Handle_t;

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
	بنية HmdVector2_t v_چوٽي_کاٻو;
	بنية HmdVector2_t v_Bottom_ساڄو;
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
	تعداد ETracking_نتيجو e_Tracking_نتيجو;
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

تعريفنوع بنية VRTexture_اونهائي_Info_t
{
	فراغ * handle; // void *
	بنية HmdMatrix44_t mProjection;
	بنية HmdVector2_t vRange;
} VRTexture_اونهائي_Info_t;

تعريفنوع بنية VRTexture_With_اونهائي_t
{
	فراغ * handle; // void *
	تعداد ETextureType eType;
	تعداد EColorSpace eColorSpace;
	بنية VRTexture_اونهائي_Info_t اونهائي_2;
} VRTexture_With_اونهائي_t;

تعريفنوع بنية VRTexture_With_Pose_And_اونهائي_t
{
	فراغ * handle; // void *
	تعداد ETextureType eType;
	تعداد EColorSpace eColorSpace;
	بنية HmdMatrix34_t m_Device_منزل_Absolute_Tracking;
	بنية VRTexture_اونهائي_Info_t اونهائي_2;
} VRTexture_With_Pose_And_اونهائي_t;

تعريفنوع بنية VRVulkan_Texture_معلومات_t
{
	uint64_t m_nImage;
	بنية VkDevice_T * m_pDevice; // struct VkDevice_T *
	بنية VkPhysicalDevice_T * m_pPhysicalDevice; // struct VkPhysicalDevice_T *
	بنية VkInstance_T * m_pInstance; // struct VkInstance_T *
	بنية Vk_قطار_T * m_p_قطار; // struct VkQueue_T *
	uint32_t m_n_قطار_Family_اشاريو;
	uint32_t m_n_ويڪر;
	uint32_t m_n_اوچائي;
	uint32_t m_nFormat;
	uint32_t m_n_Sample_ڳڻپ;
} VRVulkan_Texture_معلومات_t;

تعريفنوع بنية VRVulkan_Texture_Array_معلومات_t
{
	uint32_t m_un_Array_اشاريو;
	uint32_t m_un_Array_سائيز;
} VRVulkan_Texture_Array_معلومات_t;

تعريفنوع بنية D3_D12_Texture_معلومات_t
{
	بنية ID3D12Resource * m_pResource; // struct ID3D12Resource *
	بنية ID3_D12_Command_قطار * m_p_Command_قطار; // struct ID3D12CommandQueue *
	uint32_t m_n_ڳنڍ_نقاب;
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
	uint32_t اڻ_استعمال_ٿيل;
	عائم viewportscale;
} VREvent_Scroll_t;

تعريفنوع بنية VREvent_TouchPadMove_t
{
	bool b_Finger_هيٺ_ڏانهن;
	عائم fl_Seconds_Finger_هيٺ_ڏانهن;
	عائم f_قدر_XFirst;
	عائم f_قدر_YFirst;
	عائم f_قدر_XRaw;
	عائم f_قدر_YRaw;
} VREvent_TouchPadMove_t;

تعريفنوع بنية VREvent_Notification_t
{
	uint64_t ul_User_قدر;
	uint32_t notificationId;
} VREvent_Notification_t;

تعريفنوع بنية VREvent_Process_t
{
	uint32_t pid;
	uint32_t oldPid;
	bool bForced;
	bool b_Connection_گم;
} VREvent_Process_t;

تعريفنوع بنية VREvent_Overlay_t
{
	uint64_t overlayHandle;
	uint64_t device_رستو;
	uint64_t يادگيري_بلاڪ_Id;
} VREvent_Overlay_t;

تعريفنوع بنية VREvent_حالت_t
{
	uint32_t حالت_State;
} VREvent_حالت_t;

تعريفنوع بنية VREvent_Keyboard_t
{
	حرف c_New_داخلا[8]; //char[8]
	uint64_t u_User_قدر;
} VREvent_Keyboard_t;

تعريفنوع بنية VREvent_Ipd_t
{
	عائم ipdMeters;
} VREvent_Ipd_t;

تعريفنوع بنية VREvent_Chaperone_t
{
	uint64_t m_n_اڳيون_Universe;
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

تعريفنوع بنية VREvent_Screenshot_ترقي_t
{
	عائم ترقي_2;
} VREvent_Screenshot_ترقي_t;

تعريفنوع بنية VREvent_ApplicationLaunch_t
{
	uint32_t pid;
	uint32_t un_دليلون_Handle;
} VREvent_ApplicationLaunch_t;

تعريفنوع بنية VREvent_EditingCameraSurface_t
{
	uint64_t overlayHandle;
	uint32_t n_Visual_گهڻائي;
} VREvent_EditingCameraSurface_t;

تعريفنوع بنية VREvent_پيغام_Overlay_t
{
	uint32_t unVRMessageOverlayResponse;
} VREvent_پيغام_Overlay_t;

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

تعريفنوع بنية VREvent_داخلا_Binding_ڀريو_t
{
	PropertyContainerHandle_t ulAppContainer;
	uint64_t رستو_پيغام;
	uint64_t رستو_Url;
	uint64_t رستو_Controller_Type;
} VREvent_داخلا_Binding_ڀريو_t;

تعريفنوع بنية VREvent_داخلا_Action_Manifest_ڀريو_t
{
	uint64_t رستو_App_ڪنجي;
	uint64_t رستو_پيغام;
	uint64_t رستو_پيغام_Param;
	uint64_t رستو_Manifest_رستو;
} VREvent_داخلا_Action_Manifest_ڀريو_t;

تعريفنوع بنية VREvent_SpatialAnchor_t
{
	SpatialAnchorHandle_t unHandle;
} VREvent_SpatialAnchor_t;

تعريفنوع بنية VREvent_ترقي_Update_t
{
	uint64_t ulApplicationPropertyContainer;
	uint64_t رستو_Device;
	uint64_t رستو_داخلا_ذريعو;
	uint64_t رستو_ترقي_Action;
	uint64_t رستو_Icon;
	عائم f_ترقي;
} VREvent_ترقي_Update_t;

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
	تعداد EHDCPError e_ڪوڊ;
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
	uint32_t un_Triangle_ڳڻپ;
} HiddenAreaMesh_t;

تعريفنوع بنية VRControllerAxis_t
{
	عائم x;
	عائم y;
} VRControllerAxis_t;

تعريفنوع بنية VRControllerState_t
{
	uint32_t un_Packet_انگ;
	uint64_t ulButtonPressed;
	uint64_t ulButtonTouched;
	بنية VRControllerAxis_t rAxis[5]; //struct vr::VRControllerAxis_t[5]
} VRControllerState_t;

تعريفنوع بنية Camera_Video_وهڪرو_چوکٺو_سرو_t
{
	تعداد EVRTracked_Camera_چوکٺو_Type e_چوکٺو_Type;
	uint32_t n_ويڪر;
	uint32_t n_اوچائي;
	uint32_t n_بائيٽون_في_Pixel;
	uint32_t n_چوکٺو_Sequence;
	بنية TrackedDevicePose_t trackedDevicePose;
	uint64_t ul_چوکٺو_Exposure_وقت;
} Camera_Video_وهڪرو_چوکٺو_سرو_t;

تعريفنوع بنية Compositor_چوکٺو_Timing
{
	uint32_t m_n_سائيز;
	uint32_t m_n_چوکٺو_اشاريو;
	uint32_t m_n_انگ_چوکٺو_Presents;
	uint32_t m_n_انگ_Mis_Presented;
	uint32_t m_n_انگ_Dropped_چوکٺا;
	uint32_t m_nReprojectionFlags;
	مزدوج m_fl_System_وقت_اندريون_Seconds;
	عائم m_flPreSubmitGpuMs;
	عائم m_flPostSubmitGpuMs;
	عائم m_fl_ڪل_Render_Gpu_Ms;
	عائم m_flCompositorRenderGpuMs;
	عائم m_flCompositorRenderCpuMs;
	عائم m_flCompositorIdleCpuMs;
	عائم m_fl_Client_چوکٺو_Interval_Ms;
	عائم m_flPresentCallCpuMs;
	عائم m_flWaitForPresentCpuMs;
	عائم m_fl_Submit_چوکٺو_Ms;
	عائم m_flWaitGetPosesCalledMs;
	عائم m_flNewPosesReadyMs;
	عائم m_fl_New_چوکٺو_Ready_Ms;
	عائم m_fl_Compositor_Update_شروعات_Ms;
	عائم m_fl_Compositor_Update_پڇاڙي_Ms;
	عائم m_fl_Compositor_Render_شروعات_Ms;
	TrackedDevicePose_t m_HmdPose;
	uint32_t m_n_انگ_VSyncs_Ready_For_Use;
	uint32_t m_n_انگ_VSyncs_منزل_پهريون_View;
} Compositor_چوکٺو_Timing;

تعريفنوع بنية Compositor_BenchmarkResults
{
	عائم m_fl_Mega_Pixels_في_ٻيو;
	عائم m_fl_Hmd_Recommended_Mega_Pixels_في_ٻيو;
} Compositor_BenchmarkResults;

تعريفنوع بنية Driver_سڌو_گهڻائي_چوکٺو_Timing
{
	uint32_t m_n_سائيز;
	uint32_t m_n_انگ_چوکٺو_Presents;
	uint32_t m_n_انگ_Mis_Presented;
	uint32_t m_n_انگ_Dropped_چوکٺا;
	uint32_t m_nReprojectionFlags;
} Driver_سڌو_گهڻائي_چوکٺو_Timing;

تعريفنوع بنية ImuSample_t
{
	مزدوج f_Sample_وقت;
	بنية HmdVector3d_t vAccel;
	بنية HmdVector3d_t vGyro;
	uint32_t unOffScaleFlags;
} ImuSample_t;

تعريفنوع بنية App_Override_ڪنجيون_t
{
	حرف * pch_ڪنجي; // const char *
	حرف * pch_قدر; // const char *
} App_Override_ڪنجيون_t;

تعريفنوع بنية Compositor_CumulativeStats
{
	uint32_t m_nPid;
	uint32_t m_n_انگ_چوکٺو_Presents;
	uint32_t m_n_انگ_Dropped_چوکٺا;
	uint32_t m_n_انگ_Reprojected_چوکٺا;
	uint32_t m_n_انگ_چوکٺو_Presents_On_Startup;
	uint32_t m_n_انگ_Dropped_چوکٺا_On_Startup;
	uint32_t m_n_انگ_Reprojected_چوکٺا_On_Startup;
	uint32_t m_n_انگ_Loading;
	uint32_t m_n_انگ_چوکٺو_Presents_Loading;
	uint32_t m_n_انگ_Dropped_چوکٺا_Loading;
	uint32_t m_n_انگ_Reprojected_چوکٺا_Loading;
	uint32_t m_n_انگ_Timed_ٻاهريون;
	uint32_t m_n_انگ_چوکٺو_Presents_Timed_ٻاهريون;
	uint32_t m_n_انگ_Dropped_چوکٺا_Timed_ٻاهريون;
	uint32_t m_n_انگ_Reprojected_چوکٺا_Timed_ٻاهريون;
	uint32_t m_n_انگ_چوکٺو_Submits;
	مزدوج m_fl_جوڙ_Compositor_CPUTime_MS;
	مزدوج m_fl_جوڙ_Compositor_GPUTime_MS;
	مزدوج m_fl_جوڙ_هدف_چوکٺو_Times;
	مزدوج m_fl_جوڙ_Application_CPUTime_MS;
	مزدوج m_fl_جوڙ_Application_GPUTime_MS;
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
	بنية HmdVector3_t v_ذريعو;
	بنية HmdVector3_t vDirection;
	تعداد ETrackingUniverseOrigin eOrigin;
} VROverlayIntersectionParams_t;

تعريفنوع بنية VROverlayIntersectionResults_t
{
	بنية HmdVector3_t v_نقطو;
	بنية HmdVector3_t v_عام;
	بنية HmdVector2_t vUVs;
	عائم f_مفاصلو;
} VROverlayIntersectionResults_t;

تعريفنوع بنية Intersection_نقاب_Rectangle_t
{
	عائم m_fl_چوٽي_کاٻو_X;
	عائم m_fl_چوٽي_کاٻو_Y;
	عائم m_fl_ويڪر;
	عائم m_fl_اوچائي;
} Intersection_نقاب_Rectangle_t;

تعريفنوع بنية Intersection_نقاب_Circle_t
{
	عائم m_flCenterX;
	عائم m_flCenterY;
	عائم m_flRadius;
} Intersection_نقاب_Circle_t;

تعريفنوع بنية VROverlayProjection_t
{
	عائم f_کاٻو;
	عائم f_ساڄو;
	عائم f_چوٽي;
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
	بنية Vk_قطار_T * m_p_قطار; // struct VkQueue_T *
	uint32_t m_u_قطار_Family_اشاريو;
} VRVulkanDevice_t;

تعريفنوع بنية VRNativeDevice_t
{
	فراغ * handle; // void *
	تعداد EDeviceType eType;
} VRNativeDevice_t;

تعريفنوع بنية Render_Model_راس_t
{
	بنية HmdVector3_t vPosition;
	بنية HmdVector3_t v_عام;
	عائم rfTextureCoord[2]; //float[2]
} Render_Model_راس_t;

#إذا defined(__linux__) || defined(__APPLE__)
#هدايت pack( ڌڪو, 4 )
#جيڪڏهن_پورو
تعريفنوع بنية RenderModel_TextureMap_t
{
	uint16_t un_ويڪر;
	uint16_t un_اوچائي;
	uint8_t * rub_Texture_Map_معلومات; // const uint8_t *
	تعداد EVRRenderModelTextureFormat format;
	uint16_t un_Mip_سطحون;
} RenderModel_TextureMap_t;

#إذا defined(__linux__) || defined(__APPLE__)
#هدايت pack( ڪڍو )
#جيڪڏهن_پورو
#إذا defined(__linux__) || defined(__APPLE__)
#هدايت pack( ڌڪو, 4 )
#جيڪڏهن_پورو
تعريفنوع بنية RenderModel_t
{
	بنية Render_Model_راس_t * r_راس_معلومات; // const struct vr::RenderModel_Vertex_t *
	uint32_t un_راس_ڳڻپ;
	uint16_t * r_اشاريو_معلومات; // const uint16_t *
	uint32_t un_Triangle_ڳڻپ;
	TextureID_t diffuseTextureId;
} RenderModel_t;

#إذا defined(__linux__) || defined(__APPLE__)
#هدايت pack( ڪڍو )
#جيڪڏهن_پورو
تعريفنوع بنية Render_Model_Controller_گهڻائي_State_t
{
	bool bScrollWheelVisible;
} Render_Model_Controller_گهڻائي_State_t;

تعريفنوع بنية NotificationBitmap_t
{
	فراغ * m_p_Image_معلومات; // void *
	int32_t m_n_ويڪر;
	int32_t m_n_اوچائي;
	int32_t m_n_بائيٽون_في_Pixel;
} NotificationBitmap_t;

تعريفنوع بنية CVRSettingHelper
{
	intptr_t m_pSettings; // class vr::IVRSettings *
} CVRSettingHelper;

تعريفنوع بنية داخلا_Analog_Action_معلومات_t
{
	bool b_سرگرم;
	VRInput_قدر_Handle_t سرگرم_Origin;
	عائم x;
	عائم y;
	عائم z;
	عائم deltaX;
	عائم deltaY;
	عائم deltaZ;
	عائم f_Update_وقت;
} داخلا_Analog_Action_معلومات_t;

تعريفنوع بنية داخلا_Digital_Action_معلومات_t
{
	bool b_سرگرم;
	VRInput_قدر_Handle_t سرگرم_Origin;
	bool bState;
	bool b_بدليو;
	عائم f_Update_وقت;
} داخلا_Digital_Action_معلومات_t;

تعريفنوع بنية داخلا_Pose_Action_معلومات_t
{
	bool b_سرگرم;
	VRInput_قدر_Handle_t سرگرم_Origin;
	بنية TrackedDevicePose_t pose;
} داخلا_Pose_Action_معلومات_t;

تعريفنوع بنية داخلا_Skeletal_Action_معلومات_t
{
	bool b_سرگرم;
	VRInput_قدر_Handle_t سرگرم_Origin;
} داخلا_Skeletal_Action_معلومات_t;

تعريفنوع بنية داخلا_Origin_Info_t
{
	VRInput_قدر_Handle_t device_رستو;
	Tracked_Device_اشاريو_t tracked_Device_اشاريو;
	حرف rchRenderModelComponentName[128]; //char[128]
} داخلا_Origin_Info_t;

تعريفنوع بنية داخلا_Binding_Info_t
{
	حرف rch_Device_رستو_Name[128]; //char[128]
	حرف rch_داخلا_رستو_Name[128]; //char[128]
	حرف rch_گهڻائي_Name[128]; //char[128]
	حرف rch_جڳهه_Name[128]; //char[128]
	حرف rch_داخلا_ذريعو_Type[32]; //char[32]
} داخلا_Binding_Info_t;

تعريفنوع بنية VRActive_Action_سيٽ_t
{
	VRAction_سيٽ_Handle_t ul_Action_سيٽ;
	VRInput_قدر_Handle_t ul_Restricted_منزل_Device;
	VRAction_سيٽ_Handle_t ul_Secondary_Action_سيٽ;
	uint32_t unPadding;
	int32_t n_ترجيح;
} VRActive_Action_سيٽ_t;

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
	intptr_t m_p_VRChaperone_تياري; // class vr::IVRChaperoneSetup *
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
	تعداد ETrackedPropertyError e_سيٽ_Error;
	فراغ * pv_بفر; // void *
	uint32_t un_بفر_سائيز;
	Property_Type_ٽيگ_t un_ٽيگ;
	تعداد ETrackedPropertyError eError;
} PropertyWrite_t;

تعريفنوع بنية PropertyRead_t
{
	تعداد ETrackedDeviceProperty prop;
	فراغ * pv_بفر; // void *
	uint32_t un_بفر_سائيز;
	Property_Type_ٽيگ_t un_ٽيگ;
	uint32_t un_Required_بفر_سائيز;
	تعداد ETrackedPropertyError eError;
} PropertyRead_t;

تعريفنوع بنية CVRPropertyHelpers
{
	intptr_t m_pProperties; // class vr::IVRProperties *
} CVRPropertyHelpers;

تعريفنوع بنية رستو_Write_t
{
	رستو_Handle_t ul_رستو;
	تعداد EPropertyWriteType writeType;
	تعداد ETrackedPropertyError e_سيٽ_Error;
	فراغ * pv_بفر; // void *
	uint32_t un_بفر_سائيز;
	Property_Type_ٽيگ_t un_ٽيگ;
	تعداد ETrackedPropertyError eError;
	حرف * psz_رستو; // const char *
} رستو_Write_t;

تعريفنوع بنية رستو_Read_t
{
	رستو_Handle_t ul_رستو;
	فراغ * pv_بفر; // void *
	uint32_t un_بفر_سائيز;
	Property_Type_ٽيگ_t un_ٽيگ;
	uint32_t un_Required_بفر_سائيز;
	تعداد ETrackedPropertyError eError;
	حرف * psz_رستو; // const char *
} رستو_Read_t;


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
	VREvent_Screenshot_ترقي_t screenshot_ترقي;
	VREvent_ApplicationLaunch_t applicationLaunch;
	VREvent_EditingCameraSurface_t cameraSurface;
	VREvent_پيغام_Overlay_t پيغام_Overlay;
	VREvent_Property_t property;
	VREvent_HapticVibration_t hapticVibration;
	VREvent_WebConsole_t webConsole;
	VREvent_داخلا_Binding_ڀريو_t داخلا_Binding;
	VREvent_داخلا_Action_Manifest_ڀريو_t actionManifest;
	VREvent_SpatialAnchor_t spatialAnchor;
} VREvent_معلومات_t;

#إذا defined(__linux__) || defined(__APPLE__) 
// This structure was originally defined mis-packed on Linux, preserved for 
// compatibility. 
#هدايت pack( ڌڪو, 4 )
#جيڪڏهن_پورو

/** An event posted by the server to all running applications */
بنية VREvent_t
{
	uint32_t eventType; // EVREventType enum
	Tracked_Device_اشاريو_t tracked_Device_اشاريو;
	عائم eventAgeSeconds;
	// event data must be the end of the struct as its size is variable
	VREvent_معلومات_t معلومات;
};

#إذا defined(__linux__) || defined(__APPLE__) 
#هدايت pack( ڪڍو )
#جيڪڏهن_پورو


تعريفنوع اتحاد
{
	Intersection_نقاب_Rectangle_t m_Rectangle;
	Intersection_نقاب_Circle_t m_Circle;
} VROverlay_Intersection_نقاب_Primitive_معلومات_t;

بنية VROverlay_Intersection_نقاب_Primitive_t
{
	EVROverlay_Intersection_نقاب_Primitive_Type m_nPrimitiveType;
	VROverlay_Intersection_نقاب_Primitive_معلومات_t m_Primitive;
};


// OpenVR Function Pointer Tables

بنية VR_IVRSystem_Fn_جدول
{
	فراغ (OPENVR_FNTABLE_CALLTYPE *Get_Recommended_Render_هدف_سائيز)(uint32_t * pn_ويڪر, uint32_t * pn_اوچائي);
	بنية HmdMatrix44_t (OPENVR_FNTABLE_CALLTYPE *Get_Projection_ميٽرڪس)(EVREye eEye, عائم fNearZ, عائم fFarZ);
	فراغ (OPENVR_FNTABLE_CALLTYPE *GetProjectionRaw)(EVREye eEye, عائم * pf_کاٻو, عائم * pf_ساڄو, عائم * pf_چوٽي, عائم * pfBottom);
	bool (OPENVR_FNTABLE_CALLTYPE *ComputeDistortion)(EVREye eEye, عائم fU, عائم fV, بنية DistortionCoordinates_t * pDistortionCoordinates);
	بنية HmdMatrix34_t (OPENVR_FNTABLE_CALLTYPE *Get_Eye_منزل_سر_Transform)(EVREye eEye);
	bool (OPENVR_FNTABLE_CALLTYPE *Get_وقت_Since_آخري_Vsync)(عائم * pf_Seconds_Since_آخري_Vsync, uint64_t * pul_چوکٺو_Counter);
	int32_t (OPENVR_FNTABLE_CALLTYPE *Get_D3_D9_Adapter_اشاريو)();
	فراغ (OPENVR_FNTABLE_CALLTYPE *GetDXGIOutputInfo)(int32_t * pn_Adapter_اشاريو);
	فراغ (OPENVR_FNTABLE_CALLTYPE *GetOutputDevice)(uint64_t * pnDevice, ETextureType textureType, بنية VkInstance_T * pInstance);
	bool (OPENVR_FNTABLE_CALLTYPE *IsDisplayOnDesktop)();
	bool (OPENVR_FNTABLE_CALLTYPE *سيٽ_Display_Visibility)(bool bIsVisibleOnDesktop);
	فراغ (OPENVR_FNTABLE_CALLTYPE *Get_Device_منزل_Absolute_Tracking_Pose)(ETrackingUniverseOrigin eOrigin, عائم f_Predicted_Seconds_منزل_Photons_From_Now, بنية TrackedDevicePose_t * pTrackedDevicePoseArray, uint32_t un_Tracked_Device_Pose_Array_ڳڻپ);
	بنية HmdMatrix34_t (OPENVR_FNTABLE_CALLTYPE *Get_Seated_Zero_Pose_منزل_Standing_Absolute_Tracking_Pose)();
	بنية HmdMatrix34_t (OPENVR_FNTABLE_CALLTYPE *Get_Raw_Zero_Pose_منزل_Standing_Absolute_Tracking_Pose)();
	uint32_t (OPENVR_FNTABLE_CALLTYPE *Get_Sorted_Tracked_Device_Indices_جو_Class)(ETrackedDeviceClass eTrackedDeviceClass, Tracked_Device_اشاريو_t * pun_Tracked_Device_اشاريو_Array, uint32_t un_Tracked_Device_اشاريو_Array_ڳڻپ, Tracked_Device_اشاريو_t un_Relative_منزل_Tracked_Device_اشاريو);
	EDeviceActivityLevel (OPENVR_FNTABLE_CALLTYPE *GetTrackedDeviceActivityLevel)(Tracked_Device_اشاريو_t unDeviceId);
	فراغ (OPENVR_FNTABLE_CALLTYPE *ApplyTransform)(بنية TrackedDevicePose_t * pOutputPose, بنية TrackedDevicePose_t * pTrackedDevicePose, بنية HmdMatrix34_t * pTransform);
	Tracked_Device_اشاريو_t (OPENVR_FNTABLE_CALLTYPE *Get_Tracked_Device_اشاريو_For_Controller_Role)(ETrackedControllerRole unDeviceType);
	ETrackedControllerRole (OPENVR_FNTABLE_CALLTYPE *Get_Controller_Role_For_Tracked_Device_اشاريو)(Tracked_Device_اشاريو_t un_Device_اشاريو);
	ETrackedDeviceClass (OPENVR_FNTABLE_CALLTYPE *GetTrackedDeviceClass)(Tracked_Device_اشاريو_t un_Device_اشاريو);
	bool (OPENVR_FNTABLE_CALLTYPE *IsTrackedDeviceConnected)(Tracked_Device_اشاريو_t un_Device_اشاريو);
	bool (OPENVR_FNTABLE_CALLTYPE *GetBoolTrackedDeviceProperty)(Tracked_Device_اشاريو_t un_Device_اشاريو, ETrackedDeviceProperty prop, ETrackedPropertyError * pError);
	عائم (OPENVR_FNTABLE_CALLTYPE *GetFloatTrackedDeviceProperty)(Tracked_Device_اشاريو_t un_Device_اشاريو, ETrackedDeviceProperty prop, ETrackedPropertyError * pError);
	int32_t (OPENVR_FNTABLE_CALLTYPE *GetInt32TrackedDeviceProperty)(Tracked_Device_اشاريو_t un_Device_اشاريو, ETrackedDeviceProperty prop, ETrackedPropertyError * pError);
	uint64_t (OPENVR_FNTABLE_CALLTYPE *GetUint64TrackedDeviceProperty)(Tracked_Device_اشاريو_t un_Device_اشاريو, ETrackedDeviceProperty prop, ETrackedPropertyError * pError);
	بنية HmdMatrix34_t (OPENVR_FNTABLE_CALLTYPE *GetMatrix34TrackedDeviceProperty)(Tracked_Device_اشاريو_t un_Device_اشاريو, ETrackedDeviceProperty prop, ETrackedPropertyError * pError);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetArrayTrackedDeviceProperty)(Tracked_Device_اشاريو_t un_Device_اشاريو, ETrackedDeviceProperty prop, Property_Type_ٽيگ_t propType, فراغ * p_بفر, uint32_t un_بفر_سائيز, ETrackedPropertyError * pError);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetStringTrackedDeviceProperty)(Tracked_Device_اشاريو_t un_Device_اشاريو, ETrackedDeviceProperty prop, حرف * pch_قدر, uint32_t un_بفر_سائيز, ETrackedPropertyError * pError);
	حرف * (OPENVR_FNTABLE_CALLTYPE *GetPropErrorNameFromEnum)(ETrackedPropertyError error);
	bool (OPENVR_FNTABLE_CALLTYPE *Poll_ايندڙ_Event)(بنية VREvent_t * pEvent, uint32_t uncbVREvent);
	bool (OPENVR_FNTABLE_CALLTYPE *Poll_ايندڙ_Event_With_Pose)(ETrackingUniverseOrigin eOrigin, بنية VREvent_t * pEvent, uint32_t uncbVREvent, TrackedDevicePose_t * pTrackedDevicePose);
	حرف * (OPENVR_FNTABLE_CALLTYPE *GetEventTypeNameFromEnum)(EVREventType eType);
	بنية HiddenAreaMesh_t (OPENVR_FNTABLE_CALLTYPE *GetHiddenAreaMesh)(EVREye eEye, EHiddenAreaMeshType type);
	bool (OPENVR_FNTABLE_CALLTYPE *GetControllerState)(Tracked_Device_اشاريو_t un_Controller_Device_اشاريو, VRControllerState_t * pControllerState, uint32_t un_Controller_State_سائيز);
	bool (OPENVR_FNTABLE_CALLTYPE *GetControllerStateWithPose)(ETrackingUniverseOrigin eOrigin, Tracked_Device_اشاريو_t un_Controller_Device_اشاريو, VRControllerState_t * pControllerState, uint32_t un_Controller_State_سائيز, بنية TrackedDevicePose_t * pTrackedDevicePose);
	فراغ (OPENVR_FNTABLE_CALLTYPE *TriggerHapticPulse)(Tracked_Device_اشاريو_t un_Controller_Device_اشاريو, uint32_t unAxisId, بنانشان ننڍو usDurationMicroSec);
	حرف * (OPENVR_FNTABLE_CALLTYPE *GetButtonIdNameFromEnum)(EVRButtonId eButtonId);
	حرف * (OPENVR_FNTABLE_CALLTYPE *GetControllerAxisTypeNameFromEnum)(EVRControllerAxisType eAxisType);
	bool (OPENVR_FNTABLE_CALLTYPE *Is_داخلا_موجود)();
	bool (OPENVR_FNTABLE_CALLTYPE *IsSteamVRDrawingControllers)();
	bool (OPENVR_FNTABLE_CALLTYPE *ShouldApplicationPause)();
	bool (OPENVR_FNTABLE_CALLTYPE *ShouldApplicationReduceRenderingWork)();
	EVRFirmwareError (OPENVR_FNTABLE_CALLTYPE *PerformFirmwareUpdate)(Tracked_Device_اشاريو_t un_Device_اشاريو);
	فراغ (OPENVR_FNTABLE_CALLTYPE *AcknowledgeQuit_Exiting)();
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetAppContainerFilePaths)(حرف * pch_بفر, uint32_t un_بفر_سائيز);
	حرف * (OPENVR_FNTABLE_CALLTYPE *Get_Runtime_نسخو)();
};

بنية VR_IVRExtended_Display_Fn_جدول
{
	فراغ (OPENVR_FNTABLE_CALLTYPE *Get_دري_Bounds)(int32_t * pnX, int32_t * pnY, uint32_t * pn_ويڪر, uint32_t * pn_اوچائي);
	فراغ (OPENVR_FNTABLE_CALLTYPE *GetEyeOutputViewport)(EVREye eEye, uint32_t * pnX, uint32_t * pnY, uint32_t * pn_ويڪر, uint32_t * pn_اوچائي);
	فراغ (OPENVR_FNTABLE_CALLTYPE *GetDXGIOutputInfo)(int32_t * pn_Adapter_اشاريو, int32_t * pn_Adapter_Output_اشاريو);
};

بنية VR_IVRTracked_Camera_Fn_جدول
{
	حرف * (OPENVR_FNTABLE_CALLTYPE *GetCameraErrorNameFromEnum)(EVRTrackedCameraError eCameraError);
	EVRTrackedCameraError (OPENVR_FNTABLE_CALLTYPE *HasCamera)(Tracked_Device_اشاريو_t n_Device_اشاريو, bool * pHasCamera);
	EVRTrackedCameraError (OPENVR_FNTABLE_CALLTYPE *Get_Camera_چوکٺو_سائيز)(Tracked_Device_اشاريو_t n_Device_اشاريو, EVRTracked_Camera_چوکٺو_Type e_چوکٺو_Type, uint32_t * pn_ويڪر, uint32_t * pn_اوچائي, uint32_t * pn_چوکٺو_بفر_سائيز);
	EVRTrackedCameraError (OPENVR_FNTABLE_CALLTYPE *GetCameraIntrinsics)(Tracked_Device_اشاريو_t n_Device_اشاريو, uint32_t n_Camera_اشاريو, EVRTracked_Camera_چوکٺو_Type e_چوکٺو_Type, HmdVector2_t * p_Focal_ڊيگهائي, HmdVector2_t * pCenter);
	EVRTrackedCameraError (OPENVR_FNTABLE_CALLTYPE *GetCameraProjection)(Tracked_Device_اشاريو_t n_Device_اشاريو, uint32_t n_Camera_اشاريو, EVRTracked_Camera_چوکٺو_Type e_چوکٺو_Type, عائم flZNear, عائم flZFar, HmdMatrix44_t * pProjection);
	EVRTrackedCameraError (OPENVR_FNTABLE_CALLTYPE *AcquireVideoStreamingService)(Tracked_Device_اشاريو_t n_Device_اشاريو, TrackedCameraHandle_t * pHandle);
	EVRTrackedCameraError (OPENVR_FNTABLE_CALLTYPE *ReleaseVideoStreamingService)(TrackedCameraHandle_t hTrackedCamera);
	EVRTrackedCameraError (OPENVR_FNTABLE_CALLTYPE *Get_Video_وهڪرو_چوکٺو_بفر)(TrackedCameraHandle_t hTrackedCamera, EVRTracked_Camera_چوکٺو_Type e_چوکٺو_Type, فراغ * p_چوکٺو_بفر, uint32_t n_چوکٺو_بفر_سائيز, Camera_Video_وهڪرو_چوکٺو_سرو_t * p_چوکٺو_سرو, uint32_t n_چوکٺو_سرو_سائيز);
	EVRTrackedCameraError (OPENVR_FNTABLE_CALLTYPE *Get_Video_وهڪرو_Texture_سائيز)(Tracked_Device_اشاريو_t n_Device_اشاريو, EVRTracked_Camera_چوکٺو_Type e_چوکٺو_Type, VRTextureBounds_t * pTextureBounds, uint32_t * pn_ويڪر, uint32_t * pn_اوچائي);
	EVRTrackedCameraError (OPENVR_FNTABLE_CALLTYPE *Get_Video_وهڪرو_Texture_D3_D11)(TrackedCameraHandle_t hTrackedCamera, EVRTracked_Camera_چوکٺو_Type e_چوکٺو_Type, فراغ * pD3D11DeviceOrResource, فراغ ** ppD3D11ShaderResourceView, Camera_Video_وهڪرو_چوکٺو_سرو_t * p_چوکٺو_سرو, uint32_t n_چوکٺو_سرو_سائيز);
	EVRTrackedCameraError (OPENVR_FNTABLE_CALLTYPE *Get_Video_وهڪرو_Texture_GL)(TrackedCameraHandle_t hTrackedCamera, EVRTracked_Camera_چوکٺو_Type e_چوکٺو_Type, glUInt_t * pglTextureId, Camera_Video_وهڪرو_چوکٺو_سرو_t * p_چوکٺو_سرو, uint32_t n_چوکٺو_سرو_سائيز);
	EVRTrackedCameraError (OPENVR_FNTABLE_CALLTYPE *Release_Video_وهڪرو_Texture_GL)(TrackedCameraHandle_t hTrackedCamera, glUInt_t glTextureId);
	فراغ (OPENVR_FNTABLE_CALLTYPE *سيٽ_Camera_Tracking_Space)(ETrackingUniverseOrigin eUniverse);
	ETrackingUniverseOrigin (OPENVR_FNTABLE_CALLTYPE *GetCameraTrackingSpace)();
};

بنية VR_IVRApplications_Fn_جدول
{
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *جوڙيو_Application_Manifest)(حرف * pch_Application_Manifest_ڀريل_رستو, bool bTemporary);
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *RemoveApplicationManifest)(حرف * pch_Application_Manifest_ڀريل_رستو);
	bool (OPENVR_FNTABLE_CALLTYPE *IsApplicationInstalled)(حرف * pch_App_ڪنجي);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *Get_Application_ڳڻپ)();
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *Get_Application_ڪنجي_By_اشاريو)(uint32_t un_Application_اشاريو, حرف * pch_App_ڪنجي_بفر, uint32_t un_App_ڪنجي_بفر_Len);
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *Get_Application_ڪنجي_By_Process_Id)(uint32_t unProcessId, حرف * pch_App_ڪنجي_بفر, uint32_t un_App_ڪنجي_بفر_Len);
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *LaunchApplication)(حرف * pch_App_ڪنجي);
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *LaunchTemplateApplication)(حرف * pch_Template_App_ڪنجي, حرف * pch_New_App_ڪنجي, بنية App_Override_ڪنجيون_t * p_ڪنجيون, uint32_t un_ڪنجيون);
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *LaunchApplicationFromMimeType)(حرف * pchMimeType, حرف * pch_دليلون);
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *LaunchDashboardOverlay)(حرف * pch_App_ڪنجي);
	bool (OPENVR_FNTABLE_CALLTYPE *CancelApplicationLaunch)(حرف * pch_App_ڪنجي);
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *IdentifyApplication)(uint32_t unProcessId, حرف * pch_App_ڪنجي);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetApplicationProcessId)(حرف * pch_App_ڪنجي);
	حرف * (OPENVR_FNTABLE_CALLTYPE *GetApplicationsErrorNameFromEnum)(EVRApplicationError error);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetApplicationPropertyString)(حرف * pch_App_ڪنجي, EVRApplicationProperty eProperty, حرف * pch_Property_قدر_بفر, uint32_t un_Property_قدر_بفر_Len, EVRApplicationError * peError);
	bool (OPENVR_FNTABLE_CALLTYPE *GetApplicationPropertyBool)(حرف * pch_App_ڪنجي, EVRApplicationProperty eProperty, EVRApplicationError * peError);
	uint64_t (OPENVR_FNTABLE_CALLTYPE *GetApplicationPropertyUint64)(حرف * pch_App_ڪنجي, EVRApplicationProperty eProperty, EVRApplicationError * peError);
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *سيٽ_Application_Auto_Launch)(حرف * pch_App_ڪنجي, bool bAutoLaunch);
	bool (OPENVR_FNTABLE_CALLTYPE *GetApplicationAutoLaunch)(حرف * pch_App_ڪنجي);
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *سيٽ_Default_Application_For_Mime_Type)(حرف * pch_App_ڪنجي, حرف * pchMimeType);
	bool (OPENVR_FNTABLE_CALLTYPE *GetDefaultApplicationForMimeType)(حرف * pchMimeType, حرف * pch_App_ڪنجي_بفر, uint32_t un_App_ڪنجي_بفر_Len);
	bool (OPENVR_FNTABLE_CALLTYPE *GetApplicationSupportedMimeTypes)(حرف * pch_App_ڪنجي, حرف * pch_Mime_Types_بفر, uint32_t un_Mime_Types_بفر);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetApplicationsThatSupportMimeType)(حرف * pchMimeType, حرف * pch_App_ڪنجيون_That_Support_بفر, uint32_t un_App_ڪنجيون_That_Support_بفر);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetApplicationLaunchArguments)(uint32_t unHandle, حرف * pch_دليلون, uint32_t un_دليلون);
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *GetStartingApplication)(حرف * pch_App_ڪنجي_بفر, uint32_t un_App_ڪنجي_بفر_Len);
	EVRSceneApplicationState (OPENVR_FNTABLE_CALLTYPE *GetSceneApplicationState)();
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *PerformApplicationPrelaunchCheck)(حرف * pch_App_ڪنجي);
	حرف * (OPENVR_FNTABLE_CALLTYPE *GetSceneApplicationStateNameFromEnum)(EVRSceneApplicationState state);
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *Launch_اندروني_Process)(حرف * pch_ٻٽو_رستو, حرف * pchArguments, حرف * pchWorkingDirectory);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetCurrentSceneProcessId)();
};

بنية VR_IVRChaperone_Fn_جدول
{
	ChaperoneCalibrationState (OPENVR_FNTABLE_CALLTYPE *GetCalibrationState)();
	bool (OPENVR_FNTABLE_CALLTYPE *Get_Play_Area_سائيز)(عائم * p_سائيز_X, عائم * p_سائيز_Z);
	bool (OPENVR_FNTABLE_CALLTYPE *GetPlayAreaRect)(بنية HmdQuad_t * rect);
	فراغ (OPENVR_FNTABLE_CALLTYPE *ReloadInfo)();
	فراغ (OPENVR_FNTABLE_CALLTYPE *سيٽ_Scene_Color)(بنية HmdColor_t color);
	فراغ (OPENVR_FNTABLE_CALLTYPE *GetBoundsColor)(بنية HmdColor_t * pOutputColorArray, صحيح n_انگ_Output_Colors, عائم fl_Collision_Bounds_Fade_مفاصلو, بنية HmdColor_t * pOutputCameraColor);
	bool (OPENVR_FNTABLE_CALLTYPE *AreBoundsVisible)();
	فراغ (OPENVR_FNTABLE_CALLTYPE *ForceBoundsVisible)(bool bForce);
	فراغ (OPENVR_FNTABLE_CALLTYPE *ResetZeroPose)(ETrackingUniverseOrigin eTrackingUniverseOrigin);
};

بنية VR_IVRChaperone_تياري_Fn_جدول
{
	bool (OPENVR_FNTABLE_CALLTYPE *CommitWorkingCopy)(EChaperoneConfigFile configFile);
	فراغ (OPENVR_FNTABLE_CALLTYPE *RevertWorkingCopy)();
	bool (OPENVR_FNTABLE_CALLTYPE *Get_Working_Play_Area_سائيز)(عائم * p_سائيز_X, عائم * p_سائيز_Z);
	bool (OPENVR_FNTABLE_CALLTYPE *GetWorkingPlayAreaRect)(بنية HmdQuad_t * rect);
	bool (OPENVR_FNTABLE_CALLTYPE *GetWorkingCollisionBoundsInfo)(بنية HmdQuad_t * p_Quads_بفر, uint32_t * pun_Quads_ڳڻپ);
	bool (OPENVR_FNTABLE_CALLTYPE *Get_جيئرو_Collision_Bounds_Info)(بنية HmdQuad_t * p_Quads_بفر, uint32_t * pun_Quads_ڳڻپ);
	bool (OPENVR_FNTABLE_CALLTYPE *Get_Working_Seated_Zero_Pose_منزل_Raw_Tracking_Pose)(بنية HmdMatrix34_t * pmat_Seated_Zero_Pose_منزل_Raw_Tracking_Pose);
	bool (OPENVR_FNTABLE_CALLTYPE *Get_Working_Standing_Zero_Pose_منزل_Raw_Tracking_Pose)(بنية HmdMatrix34_t * pmat_Standing_Zero_Pose_منزل_Raw_Tracking_Pose);
	فراغ (OPENVR_FNTABLE_CALLTYPE *سيٽ_Working_Play_Area_سائيز)(عائم سائيز_X, عائم سائيز_Z);
	فراغ (OPENVR_FNTABLE_CALLTYPE *سيٽ_Working_Collision_Bounds_Info)(بنية HmdQuad_t * p_Quads_بفر, uint32_t un_Quads_ڳڻپ);
	فراغ (OPENVR_FNTABLE_CALLTYPE *سيٽ_Working_Perimeter)(بنية HmdVector2_t * p_نقطو_بفر, uint32_t un_نقطو_ڳڻپ);
	فراغ (OPENVR_FNTABLE_CALLTYPE *سيٽ_Working_Seated_Zero_Pose_منزل_Raw_Tracking_Pose)(بنية HmdMatrix34_t * p_Mat_Seated_Zero_Pose_منزل_Raw_Tracking_Pose);
	فراغ (OPENVR_FNTABLE_CALLTYPE *سيٽ_Working_Standing_Zero_Pose_منزل_Raw_Tracking_Pose)(بنية HmdMatrix34_t * p_Mat_Standing_Zero_Pose_منزل_Raw_Tracking_Pose);
	فراغ (OPENVR_FNTABLE_CALLTYPE *ReloadFromDisk)(EChaperoneConfigFile configFile);
	bool (OPENVR_FNTABLE_CALLTYPE *Get_جيئرو_Seated_Zero_Pose_منزل_Raw_Tracking_Pose)(بنية HmdMatrix34_t * pmat_Seated_Zero_Pose_منزل_Raw_Tracking_Pose);
	bool (OPENVR_FNTABLE_CALLTYPE *Export_جيئرو_منزل_بفر)(حرف * p_بفر, uint32_t * pn_بفر_ڊيگهائي);
	bool (OPENVR_FNTABLE_CALLTYPE *Import_From_بفر_منزل_Working)(حرف * p_بفر, uint32_t nImportFlags);
	فراغ (OPENVR_FNTABLE_CALLTYPE *Show_Working_سيٽ_Preview)();
	فراغ (OPENVR_FNTABLE_CALLTYPE *Hide_Working_سيٽ_Preview)();
	فراغ (OPENVR_FNTABLE_CALLTYPE *گنجائش_تياري_Starting)();
};

بنية VR_IVRCompositor_Fn_جدول
{
	فراغ (OPENVR_FNTABLE_CALLTYPE *سيٽ_Tracking_Space)(ETrackingUniverseOrigin eOrigin);
	ETrackingUniverseOrigin (OPENVR_FNTABLE_CALLTYPE *GetTrackingSpace)();
	EVRCompositorError (OPENVR_FNTABLE_CALLTYPE *WaitGetPoses)(بنية TrackedDevicePose_t * pRenderPoseArray, uint32_t un_Render_Pose_Array_ڳڻپ, بنية TrackedDevicePose_t * pGamePoseArray, uint32_t un_Game_Pose_Array_ڳڻپ);
	EVRCompositorError (OPENVR_FNTABLE_CALLTYPE *Get_آخري_Poses)(بنية TrackedDevicePose_t * pRenderPoseArray, uint32_t un_Render_Pose_Array_ڳڻپ, بنية TrackedDevicePose_t * pGamePoseArray, uint32_t un_Game_Pose_Array_ڳڻپ);
	EVRCompositorError (OPENVR_FNTABLE_CALLTYPE *Get_آخري_Pose_For_Tracked_Device_اشاريو)(Tracked_Device_اشاريو_t un_Device_اشاريو, بنية TrackedDevicePose_t * pOutputPose, بنية TrackedDevicePose_t * pOutputGamePose);
	EVRCompositorError (OPENVR_FNTABLE_CALLTYPE *Submit)(EVREye eEye, بنية Texture_t * pTexture, بنية VRTextureBounds_t * pBounds, EVRSubmitFlags nSubmitFlags);
	فراغ (OPENVR_FNTABLE_CALLTYPE *Clear_آخري_Submitted_چوکٺو)();
	فراغ (OPENVR_FNTABLE_CALLTYPE *PostPresentHandoff)();
	bool (OPENVR_FNTABLE_CALLTYPE *Get_چوکٺو_Timing)(بنية Compositor_چوکٺو_Timing * pTiming, uint32_t un_چوکٺا_Ago);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *Get_چوکٺو_Timings)(بنية Compositor_چوکٺو_Timing * pTiming, uint32_t n_چوکٺا);
	عائم (OPENVR_FNTABLE_CALLTYPE *Get_چوکٺو_وقت_بچيل)();
	فراغ (OPENVR_FNTABLE_CALLTYPE *GetCumulativeStats)(بنية Compositor_CumulativeStats * pStats, uint32_t n_Stats_سائيز_اندريون_بائيٽون);
	فراغ (OPENVR_FNTABLE_CALLTYPE *Fade_منزل_Color)(عائم fSeconds, عائم fRed, عائم fGreen, عائم fBlue, عائم fAlpha, bool bBackground);
	بنية HmdColor_t (OPENVR_FNTABLE_CALLTYPE *GetCurrentFadeColor)(bool bBackground);
	فراغ (OPENVR_FNTABLE_CALLTYPE *FadeGrid)(عائم fSeconds, bool b_Fade_Grid_اندريون);
	عائم (OPENVR_FNTABLE_CALLTYPE *GetCurrentGridAlpha)();
	EVRCompositorError (OPENVR_FNTABLE_CALLTYPE *سيٽ_Skybox_Override)(بنية Texture_t * pTextures, uint32_t un_Texture_ڳڻپ);
	فراغ (OPENVR_FNTABLE_CALLTYPE *ClearSkyboxOverride)();
	فراغ (OPENVR_FNTABLE_CALLTYPE *Compositor_Bring_منزل_Front)();
	فراغ (OPENVR_FNTABLE_CALLTYPE *Compositor_Go_منزل_پٺ)();
	فراغ (OPENVR_FNTABLE_CALLTYPE *CompositorQuit)();
	bool (OPENVR_FNTABLE_CALLTYPE *IsFullscreen)();
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetCurrentSceneFocusProcess)();
	uint32_t (OPENVR_FNTABLE_CALLTYPE *Get_آخري_چوکٺو_Renderer)();
	bool (OPENVR_FNTABLE_CALLTYPE *CanRenderScene)();
	فراغ (OPENVR_FNTABLE_CALLTYPE *Show_Mirror_دري)();
	فراغ (OPENVR_FNTABLE_CALLTYPE *Hide_Mirror_دري)();
	bool (OPENVR_FNTABLE_CALLTYPE *Is_Mirror_دري_Visible)();
	فراغ (OPENVR_FNTABLE_CALLTYPE *CompositorDumpImages)();
	bool (OPENVR_FNTABLE_CALLTYPE *Should_App_Render_With_هيٺيون_Resources)();
	فراغ (OPENVR_FNTABLE_CALLTYPE *ForceInterleavedReprojectionOn)(bool bOverride);
	فراغ (OPENVR_FNTABLE_CALLTYPE *ForceReconnectProcess)();
	فراغ (OPENVR_FNTABLE_CALLTYPE *SuspendRendering)(bool bSuspend);
	EVRCompositorError (OPENVR_FNTABLE_CALLTYPE *GetMirrorTextureD3D11)(EVREye eEye, فراغ * pD3D11DeviceOrResource, فراغ ** ppD3D11ShaderResourceView);
	فراغ (OPENVR_FNTABLE_CALLTYPE *ReleaseMirrorTextureD3D11)(فراغ * pD3D11ShaderResourceView);
	EVRCompositorError (OPENVR_FNTABLE_CALLTYPE *GetMirrorTextureGL)(EVREye eEye, glUInt_t * pglTextureId, glSharedTextureHandle_t * pglSharedTextureHandle);
	bool (OPENVR_FNTABLE_CALLTYPE *ReleaseSharedGLTexture)(glUInt_t glTextureId, glSharedTextureHandle_t glSharedTextureHandle);
	فراغ (OPENVR_FNTABLE_CALLTYPE *تالو_GLShared_Texture_For_Access)(glSharedTextureHandle_t glSharedTextureHandle);
	فراغ (OPENVR_FNTABLE_CALLTYPE *UnlockGLSharedTextureForAccess)(glSharedTextureHandle_t glSharedTextureHandle);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetVulkanInstanceExtensionsRequired)(حرف * pch_قدر, uint32_t un_بفر_سائيز);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetVulkanDeviceExtensionsRequired)(بنية VkPhysicalDevice_T * pPhysicalDevice, حرف * pch_قدر, uint32_t un_بفر_سائيز);
	فراغ (OPENVR_FNTABLE_CALLTYPE *سيٽ_Explicit_Timing_گهڻائي)(EVRCompositor_Timing_گهڻائي e_Timing_گهڻائي);
	EVRCompositorError (OPENVR_FNTABLE_CALLTYPE *Submit_Explicit_Timing_معلومات)();
	bool (OPENVR_FNTABLE_CALLTYPE *IsMotionSmoothingEnabled)();
	bool (OPENVR_FNTABLE_CALLTYPE *IsMotionSmoothingSupported)();
	bool (OPENVR_FNTABLE_CALLTYPE *IsCurrentSceneFocusAppLoading)();
	EVRCompositorError (OPENVR_FNTABLE_CALLTYPE *سيٽ_Stage_Override_Async)(حرف * pch_Render_Model_رستو, بنية HmdMatrix34_t * pTransform, بنية Compositor_StageRenderSettings * pRenderSettings, uint32_t n_سائيز_جو_Render_Settings);
	فراغ (OPENVR_FNTABLE_CALLTYPE *ClearStageOverride)();
	bool (OPENVR_FNTABLE_CALLTYPE *GetCompositorBenchmarkResults)(بنية Compositor_BenchmarkResults * pBenchmarkResults, uint32_t n_سائيز_جو_Benchmark_Results);
	EVRCompositorError (OPENVR_FNTABLE_CALLTYPE *Get_آخري_Pose_Prediction_IDs)(uint32_t * pRenderPosePredictionID, uint32_t * pGamePosePredictionID);
	EVRCompositorError (OPENVR_FNTABLE_CALLTYPE *Get_Poses_For_چوکٺو)(uint32_t unPosePredictionID, بنية TrackedDevicePose_t * pPoseArray, uint32_t un_Pose_Array_ڳڻپ);
};

بنية VR_IVROverlay_Fn_جدول
{
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *ڳوليو_Overlay)(حرف * pch_Overlay_ڪنجي, VROverlayHandle_t * pOverlayHandle);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *CreateOverlay)(حرف * pch_Overlay_ڪنجي, حرف * pchOverlayName, VROverlayHandle_t * pOverlayHandle);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *DestroyOverlay)(VROverlayHandle_t ulOverlayHandle);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *Get_Overlay_ڪنجي)(VROverlayHandle_t ulOverlayHandle, حرف * pch_قدر, uint32_t un_بفر_سائيز, EVROverlayError * pError);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetOverlayName)(VROverlayHandle_t ulOverlayHandle, حرف * pch_قدر, uint32_t un_بفر_سائيز, EVROverlayError * pError);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *سيٽ_Overlay_Name)(VROverlayHandle_t ulOverlayHandle, حرف * pchName);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *Get_Overlay_Image_معلومات)(VROverlayHandle_t ulOverlayHandle, فراغ * pv_بفر, uint32_t un_بفر_سائيز, uint32_t * pun_ويڪر, uint32_t * pun_اوچائي);
	حرف * (OPENVR_FNTABLE_CALLTYPE *GetOverlayErrorNameFromEnum)(EVROverlayError error);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *سيٽ_Overlay_Rendering_Pid)(VROverlayHandle_t ulOverlayHandle, uint32_t unPID);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetOverlayRenderingPid)(VROverlayHandle_t ulOverlayHandle);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *سيٽ_Overlay_Flag)(VROverlayHandle_t ulOverlayHandle, VROverlayFlags eOverlayFlag, bool bEnabled);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayFlag)(VROverlayHandle_t ulOverlayHandle, VROverlayFlags eOverlayFlag, bool * pbEnabled);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayFlags)(VROverlayHandle_t ulOverlayHandle, uint32_t * pFlags);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *سيٽ_Overlay_Color)(VROverlayHandle_t ulOverlayHandle, عائم fRed, عائم fGreen, عائم fBlue);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayColor)(VROverlayHandle_t ulOverlayHandle, عائم * pfRed, عائم * pfGreen, عائم * pfBlue);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *سيٽ_Overlay_Alpha)(VROverlayHandle_t ulOverlayHandle, عائم fAlpha);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayAlpha)(VROverlayHandle_t ulOverlayHandle, عائم * pfAlpha);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *سيٽ_Overlay_Texel_Aspect)(VROverlayHandle_t ulOverlayHandle, عائم fTexelAspect);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayTexelAspect)(VROverlayHandle_t ulOverlayHandle, عائم * pfTexelAspect);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *سيٽ_Overlay_ترتيب_ڏيو_ترتيب)(VROverlayHandle_t ulOverlayHandle, uint32_t un_ترتيب_ڏيو_ترتيب);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *Get_Overlay_ترتيب_ڏيو_ترتيب)(VROverlayHandle_t ulOverlayHandle, uint32_t * pun_ترتيب_ڏيو_ترتيب);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *سيٽ_Overlay_ويڪر_اندريون_Meters)(VROverlayHandle_t ulOverlayHandle, عائم f_ويڪر_اندريون_Meters);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *Get_Overlay_ويڪر_اندريون_Meters)(VROverlayHandle_t ulOverlayHandle, عائم * pf_ويڪر_اندريون_Meters);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *سيٽ_Overlay_Curvature)(VROverlayHandle_t ulOverlayHandle, عائم fCurvature);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayCurvature)(VROverlayHandle_t ulOverlayHandle, عائم * pfCurvature);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *سيٽ_Overlay_Pre_وڪر_Pitch)(VROverlayHandle_t ulOverlayHandle, عائم fRadians);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *Get_Overlay_Pre_وڪر_Pitch)(VROverlayHandle_t ulOverlayHandle, عائم * pfRadians);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *سيٽ_Overlay_Texture_Color_Space)(VROverlayHandle_t ulOverlayHandle, EColorSpace eTextureColorSpace);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayTextureColorSpace)(VROverlayHandle_t ulOverlayHandle, EColorSpace * peTextureColorSpace);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *سيٽ_Overlay_Texture_Bounds)(VROverlayHandle_t ulOverlayHandle, بنية VRTextureBounds_t * pOverlayTextureBounds);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayTextureBounds)(VROverlayHandle_t ulOverlayHandle, بنية VRTextureBounds_t * pOverlayTextureBounds);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayTransformType)(VROverlayHandle_t ulOverlayHandle, VROverlayTransformType * peTransformType);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *سيٽ_Overlay_Transform_Absolute)(VROverlayHandle_t ulOverlayHandle, ETrackingUniverseOrigin eTrackingOrigin, بنية HmdMatrix34_t * pmat_Tracking_Origin_منزل_Overlay_Transform);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayTransformAbsolute)(VROverlayHandle_t ulOverlayHandle, ETrackingUniverseOrigin * peTrackingOrigin, بنية HmdMatrix34_t * pmat_Tracking_Origin_منزل_Overlay_Transform);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *سيٽ_Overlay_Transform_Tracked_Device_Relative)(VROverlayHandle_t ulOverlayHandle, Tracked_Device_اشاريو_t unTrackedDevice, بنية HmdMatrix34_t * pmat_Tracked_Device_منزل_Overlay_Transform);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayTransformTrackedDeviceRelative)(VROverlayHandle_t ulOverlayHandle, Tracked_Device_اشاريو_t * punTrackedDevice, بنية HmdMatrix34_t * pmat_Tracked_Device_منزل_Overlay_Transform);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *سيٽ_Overlay_Transform_Tracked_Device_Component)(VROverlayHandle_t ulOverlayHandle, Tracked_Device_اشاريو_t un_Device_اشاريو, حرف * pchComponentName);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayTransformTrackedDeviceComponent)(VROverlayHandle_t ulOverlayHandle, Tracked_Device_اشاريو_t * pun_Device_اشاريو, حرف * pchComponentName, uint32_t un_Component_Name_سائيز);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayTransformOverlayRelative)(VROverlayHandle_t ulOverlayHandle, VROverlayHandle_t * ul_Overlay_Handle_والد, بنية HmdMatrix34_t * pmat_والد_Overlay_منزل_Overlay_Transform);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *سيٽ_Overlay_Transform_Overlay_Relative)(VROverlayHandle_t ulOverlayHandle, VROverlayHandle_t ul_Overlay_Handle_والد, بنية HmdMatrix34_t * pmat_والد_Overlay_منزل_Overlay_Transform);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *سيٽ_Overlay_Transform_Cursor)(VROverlayHandle_t ulCursorOverlayHandle, بنية HmdVector2_t * pvHotspot);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayTransformCursor)(VROverlayHandle_t ulOverlayHandle, بنية HmdVector2_t * pvHotspot);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *سيٽ_Overlay_Transform_Projection)(VROverlayHandle_t ulOverlayHandle, ETrackingUniverseOrigin eTrackingOrigin, بنية HmdMatrix34_t * pmat_Tracking_Origin_منزل_Overlay_Transform, بنية VROverlayProjection_t * pProjection, EVREye eEye);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *ShowOverlay)(VROverlayHandle_t ulOverlayHandle);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *HideOverlay)(VROverlayHandle_t ulOverlayHandle);
	bool (OPENVR_FNTABLE_CALLTYPE *IsOverlayVisible)(VROverlayHandle_t ulOverlayHandle);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetTransformForOverlayCoordinates)(VROverlayHandle_t ulOverlayHandle, ETrackingUniverseOrigin eTrackingOrigin, بنية HmdVector2_t coordinates_اندريون_Overlay, بنية HmdMatrix34_t * pmatTransform);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *Wait_چوکٺو_Sync)(uint32_t nTimeoutMs);
	bool (OPENVR_FNTABLE_CALLTYPE *Poll_ايندڙ_Overlay_Event)(VROverlayHandle_t ulOverlayHandle, بنية VREvent_t * pEvent, uint32_t uncbVREvent);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *Get_Overlay_داخلا_طريقو)(VROverlayHandle_t ulOverlayHandle, VROverlay_داخلا_طريقو * pe_داخلا_طريقو);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *سيٽ_Overlay_داخلا_طريقو)(VROverlayHandle_t ulOverlayHandle, VROverlay_داخلا_طريقو e_داخلا_طريقو);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayMouseScale)(VROverlayHandle_t ulOverlayHandle, بنية HmdVector2_t * pvecMouseScale);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *سيٽ_Overlay_Mouse_Scale)(VROverlayHandle_t ulOverlayHandle, بنية HmdVector2_t * pvecMouseScale);
	bool (OPENVR_FNTABLE_CALLTYPE *ComputeOverlayIntersection)(VROverlayHandle_t ulOverlayHandle, بنية VROverlayIntersectionParams_t * pParams, بنية VROverlayIntersectionResults_t * pResults);
	bool (OPENVR_FNTABLE_CALLTYPE *Is_Hover_هدف_Overlay)(VROverlayHandle_t ulOverlayHandle);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *سيٽ_Overlay_Intersection_نقاب)(VROverlayHandle_t ulOverlayHandle, بنية VROverlay_Intersection_نقاب_Primitive_t * p_نقاب_Primitives, uint32_t un_انگ_نقاب_Primitives, uint32_t un_Primitive_سائيز);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *TriggerLaserMouseHapticVibration)(VROverlayHandle_t ulOverlayHandle, عائم fDurationSeconds, عائم fFrequency, عائم fAmplitude);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *سيٽ_Overlay_Cursor)(VROverlayHandle_t ulOverlayHandle, VROverlayHandle_t ulCursorHandle);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *سيٽ_Overlay_Cursor_Position_Override)(VROverlayHandle_t ulOverlayHandle, بنية HmdVector2_t * pvCursor);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *ClearOverlayCursorPositionOverride)(VROverlayHandle_t ulOverlayHandle);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *سيٽ_Overlay_Texture)(VROverlayHandle_t ulOverlayHandle, بنية Texture_t * pTexture);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *ClearOverlayTexture)(VROverlayHandle_t ulOverlayHandle);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *سيٽ_Overlay_Raw)(VROverlayHandle_t ulOverlayHandle, فراغ * pv_بفر, uint32_t un_ويڪر, uint32_t un_اوچائي, uint32_t un_بائيٽون_في_Pixel);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *سيٽ_Overlay_From_File)(VROverlayHandle_t ulOverlayHandle, حرف * pch_File_رستو);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayTexture)(VROverlayHandle_t ulOverlayHandle, فراغ ** pNativeTextureHandle, فراغ * pNativeTextureRef, uint32_t * p_ويڪر, uint32_t * p_اوچائي, uint32_t * pNativeFormat, ETextureType * pAPIType, EColorSpace * pColorSpace, بنية VRTextureBounds_t * pTextureBounds);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *ReleaseNativeOverlayHandle)(VROverlayHandle_t ulOverlayHandle, فراغ * pNativeTextureHandle);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *Get_Overlay_Texture_سائيز)(VROverlayHandle_t ulOverlayHandle, uint32_t * p_ويڪر, uint32_t * p_اوچائي);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *CreateDashboardOverlay)(حرف * pch_Overlay_ڪنجي, حرف * pchOverlayFriendlyName, VROverlayHandle_t * pMainHandle, VROverlayHandle_t * pThumbnailHandle);
	bool (OPENVR_FNTABLE_CALLTYPE *IsDashboardVisible)();
	bool (OPENVR_FNTABLE_CALLTYPE *Is_سرگرم_Dashboard_Overlay)(VROverlayHandle_t ulOverlayHandle);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *سيٽ_Dashboard_Overlay_Scene_Process)(VROverlayHandle_t ulOverlayHandle, uint32_t unProcessId);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetDashboardOverlaySceneProcess)(VROverlayHandle_t ulOverlayHandle, uint32_t * punProcessId);
	فراغ (OPENVR_FNTABLE_CALLTYPE *ShowDashboard)(حرف * pch_Overlay_منزل_Show);
	Tracked_Device_اشاريو_t (OPENVR_FNTABLE_CALLTYPE *GetPrimaryDashboardDevice)();
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *ShowKeyboard)(EGamepad_متن_داخلا_گهڻائي e_داخلا_گهڻائي, EGamepad_متن_داخلا_سٽ_گهڻائي e_سٽ_داخلا_گهڻائي, uint32_t unFlags, حرف * pchDescription, uint32_t unCharMax, حرف * pch_Existing_متن, uint64_t u_User_قدر);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *ShowKeyboardForOverlay)(VROverlayHandle_t ulOverlayHandle, EGamepad_متن_داخلا_گهڻائي e_داخلا_گهڻائي, EGamepad_متن_داخلا_سٽ_گهڻائي e_سٽ_داخلا_گهڻائي, uint32_t unFlags, حرف * pchDescription, uint32_t unCharMax, حرف * pch_Existing_متن, uint64_t u_User_قدر);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *Get_Keyboard_متن)(حرف * pch_متن, uint32_t cch_متن);
	فراغ (OPENVR_FNTABLE_CALLTYPE *HideKeyboard)();
	فراغ (OPENVR_FNTABLE_CALLTYPE *سيٽ_Keyboard_Transform_Absolute)(ETrackingUniverseOrigin eTrackingOrigin, بنية HmdMatrix34_t * pmat_Tracking_Origin_منزل_Keyboard_Transform);
	فراغ (OPENVR_FNTABLE_CALLTYPE *سيٽ_Keyboard_Position_For_Overlay)(VROverlayHandle_t ulOverlayHandle, بنية HmdRect2_t avoidRect);
	VRMessageOverlayResponse (OPENVR_FNTABLE_CALLTYPE *Show_پيغام_Overlay)(حرف * pch_متن, حرف * pchCaption, حرف * pch_Button0_متن, حرف * pch_Button1_متن, حرف * pch_Button2_متن, حرف * pch_Button3_متن);
	فراغ (OPENVR_FNTABLE_CALLTYPE *Close_پيغام_Overlay)();
};

بنية VR_IVROverlay_View_Fn_جدول
{
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *AcquireOverlayView)(VROverlayHandle_t ulOverlayHandle, بنية VRNativeDevice_t * pNativeDevice, بنية VROverlayView_t * pOverlayView, uint32_t un_Overlay_View_سائيز);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *ReleaseOverlayView)(بنية VROverlayView_t * pOverlayView);
	فراغ (OPENVR_FNTABLE_CALLTYPE *PostOverlayEvent)(VROverlayHandle_t ulOverlayHandle, بنية VREvent_t * pvrEvent);
	bool (OPENVR_FNTABLE_CALLTYPE *IsViewingPermitted)(VROverlayHandle_t ulOverlayHandle);
};

بنية VR_IVRHeadset_View_Fn_جدول
{
	فراغ (OPENVR_FNTABLE_CALLTYPE *سيٽ_Headset_View_سائيز)(uint32_t n_ويڪر, uint32_t n_اوچائي);
	فراغ (OPENVR_FNTABLE_CALLTYPE *Get_Headset_View_سائيز)(uint32_t * pn_ويڪر, uint32_t * pn_اوچائي);
	فراغ (OPENVR_FNTABLE_CALLTYPE *سيٽ_Headset_View_گهڻائي)(Headset_View_گهڻائي_t e_Headset_View_گهڻائي);
	Headset_View_گهڻائي_t (OPENVR_FNTABLE_CALLTYPE *Get_Headset_View_گهڻائي)();
	فراغ (OPENVR_FNTABLE_CALLTYPE *سيٽ_Headset_View_Cropped)(bool bCropped);
	bool (OPENVR_FNTABLE_CALLTYPE *GetHeadsetViewCropped)();
	عائم (OPENVR_FNTABLE_CALLTYPE *Get_Headset_View_Aspect_تناسب)();
	فراغ (OPENVR_FNTABLE_CALLTYPE *سيٽ_Headset_View_Blend_Range)(عائم fl_شروعات_Pct, عائم fl_پڇاڙي_Pct);
	فراغ (OPENVR_FNTABLE_CALLTYPE *GetHeadsetViewBlendRange)(عائم * p_شروعات_Pct, عائم * p_پڇاڙي_Pct);
};

بنية VR_IVRRender_Models_Fn_جدول
{
	EVRRenderModelError (OPENVR_FNTABLE_CALLTYPE *ڀريو_Render_Model_Async)(حرف * pchRenderModelName, بنية RenderModel_t ** ppRenderModel);
	فراغ (OPENVR_FNTABLE_CALLTYPE *FreeRenderModel)(بنية RenderModel_t * pRenderModel);
	EVRRenderModelError (OPENVR_FNTABLE_CALLTYPE *ڀريو_Texture_Async)(TextureID_t textureId, بنية RenderModel_TextureMap_t ** ppTexture);
	فراغ (OPENVR_FNTABLE_CALLTYPE *FreeTexture)(بنية RenderModel_TextureMap_t * pTexture);
	EVRRenderModelError (OPENVR_FNTABLE_CALLTYPE *ڀريو_Texture_D3_D11_Async)(TextureID_t textureId, فراغ * pD3D11Device, فراغ ** ppD3D11Texture2D);
	EVRRenderModelError (OPENVR_FNTABLE_CALLTYPE *ڀريو_Into_Texture_D3_D11_Async)(TextureID_t textureId, فراغ * pDstTexture);
	فراغ (OPENVR_FNTABLE_CALLTYPE *FreeTextureD3D11)(فراغ * pD3D11Texture2D);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetRenderModelName)(uint32_t un_Render_Model_اشاريو, حرف * pchRenderModelName, uint32_t unRenderModelNameLen);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *Get_Render_Model_ڳڻپ)();
	uint32_t (OPENVR_FNTABLE_CALLTYPE *Get_Component_ڳڻپ)(حرف * pchRenderModelName);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetComponentName)(حرف * pchRenderModelName, uint32_t un_Component_اشاريو, حرف * pchComponentName, uint32_t unComponentNameLen);
	uint64_t (OPENVR_FNTABLE_CALLTYPE *Get_Component_Button_نقاب)(حرف * pchRenderModelName, حرف * pchComponentName);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetComponentRenderModelName)(حرف * pchRenderModelName, حرف * pchComponentName, حرف * pchComponentRenderModelName, uint32_t unComponentRenderModelNameLen);
	bool (OPENVR_FNTABLE_CALLTYPE *Get_Component_State_For_Device_رستو)(حرف * pchRenderModelName, حرف * pchComponentName, VRInput_قدر_Handle_t device_رستو, Render_Model_Controller_گهڻائي_State_t * pState, RenderModel_ComponentState_t * pComponentState);
	bool (OPENVR_FNTABLE_CALLTYPE *GetComponentState)(حرف * pchRenderModelName, حرف * pchComponentName, VRControllerState_t * pControllerState, بنية Render_Model_Controller_گهڻائي_State_t * pState, بنية RenderModel_ComponentState_t * pComponentState);
	bool (OPENVR_FNTABLE_CALLTYPE *RenderModelHasComponent)(حرف * pchRenderModelName, حرف * pchComponentName);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetRenderModelThumbnailURL)(حرف * pchRenderModelName, حرف * pchThumbnailURL, uint32_t unThumbnailURLLen, EVRRenderModelError * peError);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *Get_Render_Model_Original_رستو)(حرف * pchRenderModelName, حرف * pch_Original_رستو, uint32_t un_Original_رستو_Len, EVRRenderModelError * peError);
	حرف * (OPENVR_FNTABLE_CALLTYPE *GetRenderModelErrorNameFromEnum)(EVRRenderModelError error);
};

بنية VR_IVRNotifications_Fn_جدول
{
	EVRNotificationError (OPENVR_FNTABLE_CALLTYPE *CreateNotification)(VROverlayHandle_t ulOverlayHandle, uint64_t ul_User_قدر, EVRNotificationType type, حرف * pch_متن, EVRNotificationStyle style, بنية NotificationBitmap_t * pImage, VRNotificationId * pNotificationId);
	EVRNotificationError (OPENVR_FNTABLE_CALLTYPE *RemoveNotification)(VRNotificationId notificationId);
};

بنية VR_IVRSettings_Fn_جدول
{
	حرف * (OPENVR_FNTABLE_CALLTYPE *GetSettingsErrorNameFromEnum)(EVRSettingsError eError);
	فراغ (OPENVR_FNTABLE_CALLTYPE *سيٽ_Bool)(حرف * pchSection, حرف * pch_Settings_ڪنجي, bool b_قدر, EVRSettingsError * peError);
	فراغ (OPENVR_FNTABLE_CALLTYPE *سيٽ_Int32)(حرف * pchSection, حرف * pch_Settings_ڪنجي, int32_t n_قدر, EVRSettingsError * peError);
	فراغ (OPENVR_FNTABLE_CALLTYPE *سيٽ_Float)(حرف * pchSection, حرف * pch_Settings_ڪنجي, عائم fl_قدر, EVRSettingsError * peError);
	فراغ (OPENVR_FNTABLE_CALLTYPE *سيٽ_String)(حرف * pchSection, حرف * pch_Settings_ڪنجي, حرف * pch_قدر, EVRSettingsError * peError);
	bool (OPENVR_FNTABLE_CALLTYPE *GetBool)(حرف * pchSection, حرف * pch_Settings_ڪنجي, EVRSettingsError * peError);
	int32_t (OPENVR_FNTABLE_CALLTYPE *GetInt32)(حرف * pchSection, حرف * pch_Settings_ڪنجي, EVRSettingsError * peError);
	عائم (OPENVR_FNTABLE_CALLTYPE *GetFloat)(حرف * pchSection, حرف * pch_Settings_ڪنجي, EVRSettingsError * peError);
	فراغ (OPENVR_FNTABLE_CALLTYPE *GetString)(حرف * pchSection, حرف * pch_Settings_ڪنجي, حرف * pch_قدر, uint32_t un_قدر_Len, EVRSettingsError * peError);
	فراغ (OPENVR_FNTABLE_CALLTYPE *RemoveSection)(حرف * pchSection, EVRSettingsError * peError);
	فراغ (OPENVR_FNTABLE_CALLTYPE *Remove_ڪنجي_اندريون_Section)(حرف * pchSection, حرف * pch_Settings_ڪنجي, EVRSettingsError * peError);
};

بنية VR_IVRScreenshots_Fn_جدول
{
	EVRScreenshotError (OPENVR_FNTABLE_CALLTYPE *RequestScreenshot)(ScreenshotHandle_t * p_ٻاهريون_Screenshot_Handle, EVRScreenshotType type, حرف * pchPreviewFilename, حرف * pchVRFilename);
	EVRScreenshotError (OPENVR_FNTABLE_CALLTYPE *HookScreenshot)(EVRScreenshotType * pSupportedTypes, صحيح انگ_Types);
	EVRScreenshotType (OPENVR_FNTABLE_CALLTYPE *GetScreenshotPropertyType)(ScreenshotHandle_t screenshotHandle, EVRScreenshotError * pError);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetScreenshotPropertyFilename)(ScreenshotHandle_t screenshotHandle, EVRScreenshotPropertyFilenames filenameType, حرف * pchFilename, uint32_t cchFilename, EVRScreenshotError * pError);
	EVRScreenshotError (OPENVR_FNTABLE_CALLTYPE *Update_Screenshot_ترقي)(ScreenshotHandle_t screenshotHandle, عائم fl_ترقي);
	EVRScreenshotError (OPENVR_FNTABLE_CALLTYPE *TakeStereoScreenshot)(ScreenshotHandle_t * p_ٻاهريون_Screenshot_Handle, حرف * pchPreviewFilename, حرف * pchVRFilename);
	EVRScreenshotError (OPENVR_FNTABLE_CALLTYPE *SubmitScreenshot)(ScreenshotHandle_t screenshotHandle, EVRScreenshotType type, حرف * pch_ذريعو_Preview_Filename, حرف * pch_ذريعو_VRFilename);
};

بنية VR_IVRResources_Fn_جدول
{
	uint32_t (OPENVR_FNTABLE_CALLTYPE *ڀريو_Shared_Resource)(حرف * pchResourceName, حرف * pch_بفر, uint32_t un_بفر_Len);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *Get_Resource_ڀريل_رستو)(حرف * pchResourceName, حرف * pchResourceTypeDirectory, حرف * pch_رستو_بفر, uint32_t un_بفر_Len);
};

بنية VR_IVRDriver_Manager_Fn_جدول
{
	uint32_t (OPENVR_FNTABLE_CALLTYPE *Get_Driver_ڳڻپ)();
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetDriverName)(DriverId_t nDriver, حرف * pch_قدر, uint32_t un_بفر_سائيز);
	DriverHandle_t (OPENVR_FNTABLE_CALLTYPE *GetDriverHandle)(حرف * pchDriverName);
	bool (OPENVR_FNTABLE_CALLTYPE *IsEnabled)(DriverId_t nDriver);
};

بنية VR_IVRInput_Fn_جدول
{
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *سيٽ_Action_Manifest_رستو)(حرف * pch_Action_Manifest_رستو);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *Get_Action_سيٽ_Handle)(حرف * pch_Action_سيٽ_Name, VRAction_سيٽ_Handle_t * pHandle);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetActionHandle)(حرف * pchActionName, VRActionHandle_t * pHandle);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *Get_داخلا_ذريعو_Handle)(حرف * pch_داخلا_ذريعو_رستو, VRInput_قدر_Handle_t * pHandle);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *UpdateActionState)(بنية VRActive_Action_سيٽ_t * pSets, uint32_t un_سائيز_جو_VRSelected_Action_سيٽ_t, uint32_t un_سيٽ_ڳڻپ);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *Get_Digital_Action_معلومات)(VRActionHandle_t action, بنية داخلا_Digital_Action_معلومات_t * p_Action_معلومات, uint32_t un_Action_معلومات_سائيز, VRInput_قدر_Handle_t ul_Restrict_منزل_Device);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *Get_Analog_Action_معلومات)(VRActionHandle_t action, بنية داخلا_Analog_Action_معلومات_t * p_Action_معلومات, uint32_t un_Action_معلومات_سائيز, VRInput_قدر_Handle_t ul_Restrict_منزل_Device);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *Get_Pose_Action_معلومات_Relative_منزل_Now)(VRActionHandle_t action, ETrackingUniverseOrigin eOrigin, عائم fPredictedSecondsFromNow, بنية داخلا_Pose_Action_معلومات_t * p_Action_معلومات, uint32_t un_Action_معلومات_سائيز, VRInput_قدر_Handle_t ul_Restrict_منزل_Device);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *Get_Pose_Action_معلومات_For_ايندڙ_چوکٺو)(VRActionHandle_t action, ETrackingUniverseOrigin eOrigin, بنية داخلا_Pose_Action_معلومات_t * p_Action_معلومات, uint32_t un_Action_معلومات_سائيز, VRInput_قدر_Handle_t ul_Restrict_منزل_Device);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *Get_Skeletal_Action_معلومات)(VRActionHandle_t action, بنية داخلا_Skeletal_Action_معلومات_t * p_Action_معلومات, uint32_t un_Action_معلومات_سائيز);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetDominantHand)(ETrackedControllerRole * peDominantHand);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *سيٽ_Dominant_Hand)(ETrackedControllerRole eDominantHand);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *Get_Bone_ڳڻپ)(VRActionHandle_t action, uint32_t * p_Bone_ڳڻپ);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetBoneHierarchy)(VRActionHandle_t action, Bone_اشاريو_t * p_والد_Indices, uint32_t un_اشاريو_Aray_ڳڻپ);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetBoneName)(VRActionHandle_t action, Bone_اشاريو_t n_Bone_اشاريو, حرف * pchBoneName, uint32_t un_Name_بفر_سائيز);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetSkeletalReferenceTransforms)(VRActionHandle_t action, EVRSkeletalTransformSpace eTransformSpace, EVRSkeletalReferencePose eReferencePose, بنية VRBoneTransform_t * pTransformArray, uint32_t un_Transform_Array_ڳڻپ);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetSkeletalTrackingLevel)(VRActionHandle_t action, EVRSkeletalTrackingLevel * pSkeletalTrackingLevel);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *Get_Skeletal_Bone_معلومات)(VRActionHandle_t action, EVRSkeletalTransformSpace eTransformSpace, EVRSkeletalMotionRange eMotionRange, بنية VRBoneTransform_t * pTransformArray, uint32_t un_Transform_Array_ڳڻپ);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *Get_Skeletal_Summary_معلومات)(VRActionHandle_t action, EVRSummaryType eSummaryType, بنية VRSkeletal_Summary_معلومات_t * p_Skeletal_Summary_معلومات);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *Get_Skeletal_Bone_معلومات_Compressed)(VRActionHandle_t action, EVRSkeletalMotionRange eMotionRange, فراغ * pv_Compressed_معلومات, uint32_t un_Compressed_سائيز, uint32_t * pun_Required_Compressed_سائيز);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *Decompress_Skeletal_Bone_معلومات)(فراغ * pv_Compressed_بفر, uint32_t un_Compressed_بفر_سائيز, EVRSkeletalTransformSpace eTransformSpace, بنية VRBoneTransform_t * pTransformArray, uint32_t un_Transform_Array_ڳڻپ);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *TriggerHapticVibrationAction)(VRActionHandle_t action, عائم f_شروعات_Seconds_From_Now, عائم fDurationSeconds, عائم fFrequency, عائم fAmplitude, VRInput_قدر_Handle_t ul_Restrict_منزل_Device);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetActionOrigins)(VRAction_سيٽ_Handle_t action_سيٽ_Handle, VRActionHandle_t digitalActionHandle, VRInput_قدر_Handle_t * origins_ٻاهريون, uint32_t origin_ٻاهريون_ڳڻپ);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetOriginLocalizedName)(VRInput_قدر_Handle_t origin, حرف * pchNameArray, uint32_t un_Name_Array_سائيز, int32_t un_String_Sections_منزل_Include);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetOriginTrackedDeviceInfo)(VRInput_قدر_Handle_t origin, بنية داخلا_Origin_Info_t * pOriginInfo, uint32_t un_Origin_Info_سائيز);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetActionBindingInfo)(VRActionHandle_t action, بنية داخلا_Binding_Info_t * pOriginInfo, uint32_t un_Binding_Info_سائيز, uint32_t un_Binding_Info_ڳڻپ, uint32_t * pun_Returned_Binding_Info_ڳڻپ);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *ShowActionOrigins)(VRAction_سيٽ_Handle_t action_سيٽ_Handle, VRActionHandle_t ulActionHandle);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *Show_Bindings_For_Action_سيٽ)(بنية VRActive_Action_سيٽ_t * pSets, uint32_t un_سائيز_جو_VRSelected_Action_سيٽ_t, uint32_t un_سيٽ_ڳڻپ, VRInput_قدر_Handle_t origin_منزل_Highlight);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetComponentStateForBinding)(حرف * pchRenderModelName, حرف * pchComponentName, بنية داخلا_Binding_Info_t * pOriginInfo, uint32_t un_Binding_Info_سائيز, uint32_t un_Binding_Info_ڳڻپ, RenderModel_ComponentState_t * pComponentState);
	bool (OPENVR_FNTABLE_CALLTYPE *Is_Using_Legacy_داخلا)();
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *OpenBindingUI)(حرف * pch_App_ڪنجي, VRAction_سيٽ_Handle_t ul_Action_سيٽ_Handle, VRInput_قدر_Handle_t ulDeviceHandle, bool bShowOnDesktop);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetBindingVariant)(VRInput_قدر_Handle_t ul_Device_رستو, حرف * pchVariantArray, uint32_t un_Variant_Array_سائيز);
};

بنية VR_IVRIOBuffer_Fn_جدول
{
	EIOBufferError (OPENVR_FNTABLE_CALLTYPE *Open)(حرف * pch_رستو, EIOBuffer_گهڻائي گهڻائي, uint32_t un_Element_سائيز, uint32_t unElements, IOBufferHandle_t * pul_بفر);
	EIOBufferError (OPENVR_FNTABLE_CALLTYPE *Close)(IOBufferHandle_t ul_بفر);
	EIOBufferError (OPENVR_FNTABLE_CALLTYPE *Read)(IOBufferHandle_t ul_بفر, فراغ * pDst, uint32_t un_بائيٽون, uint32_t * punRead);
	EIOBufferError (OPENVR_FNTABLE_CALLTYPE *Write)(IOBufferHandle_t ul_بفر, فراغ * pSrc, uint32_t un_بائيٽون);
	PropertyContainerHandle_t (OPENVR_FNTABLE_CALLTYPE *PropertyContainer)(IOBufferHandle_t ul_بفر);
	bool (OPENVR_FNTABLE_CALLTYPE *HasReaders)(IOBufferHandle_t ul_بفر);
};

بنية VR_IVRSpatial_Anchors_Fn_جدول
{
	EVRSpatialAnchorError (OPENVR_FNTABLE_CALLTYPE *CreateSpatialAnchorFromDescriptor)(حرف * pchDescriptor, SpatialAnchorHandle_t * p_Handle_ٻاهريون);
	EVRSpatialAnchorError (OPENVR_FNTABLE_CALLTYPE *CreateSpatialAnchorFromPose)(Tracked_Device_اشاريو_t un_Device_اشاريو, ETrackingUniverseOrigin eOrigin, بنية SpatialAnchorPose_t * pPose, SpatialAnchorHandle_t * p_Handle_ٻاهريون);
	EVRSpatialAnchorError (OPENVR_FNTABLE_CALLTYPE *GetSpatialAnchorPose)(SpatialAnchorHandle_t unHandle, ETrackingUniverseOrigin eOrigin, بنية SpatialAnchorPose_t * p_Pose_ٻاهريون);
	EVRSpatialAnchorError (OPENVR_FNTABLE_CALLTYPE *GetSpatialAnchorDescriptor)(SpatialAnchorHandle_t unHandle, حرف * pch_Descriptor_ٻاهريون, uint32_t * pun_Descriptor_بفر_Len_اندريون_ٻاهريون);
};

بنية VR_IVRDebug_Fn_جدول
{
	EVRDebugError (OPENVR_FNTABLE_CALLTYPE *EmitVrProfilerEvent)(حرف * pch_پيغام);
	EVRDebugError (OPENVR_FNTABLE_CALLTYPE *BeginVrProfilerEvent)(VrProfilerEventHandle_t * p_Handle_ٻاهريون);
	EVRDebugError (OPENVR_FNTABLE_CALLTYPE *پڄاڻي_Vr_Profiler_Event)(VrProfilerEventHandle_t hHandle, حرف * pch_پيغام);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *DriverDebugRequest)(Tracked_Device_اشاريو_t un_Device_اشاريو, حرف * pchRequest, حرف * pch_Response_بفر, uint32_t un_Response_بفر_سائيز);
};

بنية VR_IVRProperties_Fn_جدول
{
	ETrackedPropertyError (OPENVR_FNTABLE_CALLTYPE *ReadPropertyBatch)(PropertyContainerHandle_t ulContainerHandle, بنية PropertyRead_t * pBatch, uint32_t un_Batch_داخلا_ڳڻپ);
	ETrackedPropertyError (OPENVR_FNTABLE_CALLTYPE *WritePropertyBatch)(PropertyContainerHandle_t ulContainerHandle, بنية PropertyWrite_t * pBatch, uint32_t un_Batch_داخلا_ڳڻپ);
	حرف * (OPENVR_FNTABLE_CALLTYPE *GetPropErrorNameFromEnum)(ETrackedPropertyError error);
	PropertyContainerHandle_t (OPENVR_FNTABLE_CALLTYPE *Tracked_Device_منزل_Property_Container)(Tracked_Device_اشاريو_t nDevice);
};

بنية VR_IVRPaths_Fn_جدول
{
	ETrackedPropertyError (OPENVR_FNTABLE_CALLTYPE *Read_رستو_Batch)(PropertyContainerHandle_t ul_پاڙ_Handle, بنية رستو_Read_t * pBatch, uint32_t un_Batch_داخلا_ڳڻپ);
	ETrackedPropertyError (OPENVR_FNTABLE_CALLTYPE *Write_رستو_Batch)(PropertyContainerHandle_t ul_پاڙ_Handle, بنية رستو_Write_t * pBatch, uint32_t un_Batch_داخلا_ڳڻپ);
	ETrackedPropertyError (OPENVR_FNTABLE_CALLTYPE *String_منزل_Handle)(رستو_Handle_t * pHandle, حرف * pch_رستو);
	ETrackedPropertyError (OPENVR_FNTABLE_CALLTYPE *Handle_منزل_String)(رستو_Handle_t pHandle, حرف * pch_بفر, uint32_t un_بفر_سائيز, uint32_t * pun_بفر_سائيز_استعمال_ٿيل);
};

بنية VR_IVRBlock_قطار_Fn_جدول
{
	EBlock_قطار_Error (OPENVR_FNTABLE_CALLTYPE *Create)(PropertyContainerHandle_t * pul_قطار_Handle, حرف * pch_رستو, uint32_t un_بلاڪ_معلومات_سائيز, uint32_t un_بلاڪ_سرو_سائيز, uint32_t un_بلاڪ_ڳڻپ, uint32_t unFlags);
	EBlock_قطار_Error (OPENVR_FNTABLE_CALLTYPE *Connect)(PropertyContainerHandle_t * pul_قطار_Handle, حرف * pch_رستو);
	EBlock_قطار_Error (OPENVR_FNTABLE_CALLTYPE *Destroy)(PropertyContainerHandle_t ul_قطار_Handle);
	EBlock_قطار_Error (OPENVR_FNTABLE_CALLTYPE *Acquire_Write_Only_بلاڪ)(PropertyContainerHandle_t ul_قطار_Handle, PropertyContainerHandle_t * pul_بلاڪ_Handle, فراغ ** ppv_بفر);
	EBlock_قطار_Error (OPENVR_FNTABLE_CALLTYPE *Release_Write_Only_بلاڪ)(PropertyContainerHandle_t ul_قطار_Handle, PropertyContainerHandle_t ul_بلاڪ_Handle);
	EBlock_قطار_Error (OPENVR_FNTABLE_CALLTYPE *Wait_And_Acquire_Read_Only_بلاڪ)(PropertyContainerHandle_t ul_قطار_Handle, PropertyContainerHandle_t * pul_بلاڪ_Handle, فراغ ** ppv_بفر, EBlock_قطار_Read_Type eReadType, uint32_t unTimeoutMs);
	EBlock_قطار_Error (OPENVR_FNTABLE_CALLTYPE *Acquire_Read_Only_بلاڪ)(PropertyContainerHandle_t ul_قطار_Handle, PropertyContainerHandle_t * pul_بلاڪ_Handle, فراغ ** ppv_بفر, EBlock_قطار_Read_Type eReadType);
	EBlock_قطار_Error (OPENVR_FNTABLE_CALLTYPE *Release_Read_Only_بلاڪ)(PropertyContainerHandle_t ul_قطار_Handle, PropertyContainerHandle_t ul_بلاڪ_Handle);
	EBlock_قطار_Error (OPENVR_FNTABLE_CALLTYPE *قطار_Has_Reader)(PropertyContainerHandle_t ul_قطار_Handle, bool * pbHasReaders);
};


#إذا 0
// Global entry points
S_API intptr_t VR_Init_اندروني( EVRInitError *peError, EVRApplicationType eType );
S_API فراغ VR_Shutdown_اندروني();
S_API bool VR_IsHmdPresent();
S_API intptr_t VR_GetGenericInterface( ثابت حرف *pch_Interface_نسخو, EVRInitError *peError );
S_API bool VR_IsRuntimeInstalled();
S_API ثابت حرف * VR_Get_VRInit_Error_As_نشان( EVRInitError error );
S_API ثابت حرف * VR_GetVRInitErrorAsEnglishDescription( EVRInitError error );
#جيڪڏهن_پورو

#جيڪڏهن_پورو // __OPENVR_API_FLAT_H__


