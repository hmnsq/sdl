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

#ifndef __OPENVR_API_FLAT_H__
#define __OPENVR_API_FLAT_H__
#যদি defined( _WIN32 ) || defined( __clang__ )
#pragma once
#endif

#ifdef __cplusplus
#define EXTERN_C বাহ্যিক "C"
#অন্যথা
#define EXTERN_C
#endif

#যদি defined( _WIN32 )
#define OPENVR_FNTABLE_CALLTYPE __stdcall
#অন্যথা
#define OPENVR_FNTABLE_CALLTYPE 
#endif

// OPENVR API export macro
#যদি defined( _WIN32 ) && !defined( _X360 )
	#যদি defined( OPENVR_API_EXPORTS )
	#define S_API EXTERN_C __declspec( dllexport )
	#নতুবা_যদি defined( OPENVR_API_NODLL )
	#define S_API EXTERN_C
	#অন্যথা
	#define S_API বাহ্যিক "C" __declspec( dllimport ) 
	#endif // OPENVR_API_EXPORTS
#নতুবা_যদি defined( __GNUC__ )
	#যদি defined( OPENVR_API_EXPORTS )
	#define S_API EXTERN_C __attribute__ ((visibility("default")))
	#অন্যথা
	#define S_API EXTERN_C
	#endif // OPENVR_API_EXPORTS
#অন্যথা // !WIN32
	#যদি defined( OPENVR_API_EXPORTS )
	#define S_API EXTERN_C
	#অন্যথা
	#define S_API EXTERN_C
	#endif // OPENVR_API_EXPORTS
#endif

#ifndef USE_SDL
#অন্তর্ভাব <stdint.h>

#যদি defined( __WIN32 )
প্রকারলেখ অক্ষর bool;
#অন্যথা
#অন্তর্ভাব <stdbool.h>
#endif
#endif // USE_SDL

// OpenVR Constants

স্থির ধ্রুবক unsigned long k_nDriverNone = 4294967295;
স্থির ধ্রুবক unsigned long k_un_Max_Driver_Debug_Response_আকার = 32768;
স্থির ধ্রুবক unsigned long k_un_Tracked_Device_সূচক_Hmd = 0;
স্থির ধ্রুবক unsigned long k_un_Max_Tracked_Device_গুনতি = 64;
স্থির ধ্রুবক unsigned long k_un_Tracked_Device_সূচক_Other = 4294967294;
স্থির ধ্রুবক unsigned long k_un_Tracked_Device_সূচক_Invalid = 4294967295;
স্থির ধ্রুবক unsigned long long k_ulInvalidPropertyContainer = 0;
স্থির ধ্রুবক unsigned long k_unInvalidPropertyTag = 0;
স্থির ধ্রুবক unsigned long long k_ulInvalidDriverHandle = 0;
স্থির ধ্রুবক unsigned long k_unFloatPropertyTag = 1;
স্থির ধ্রুবক unsigned long k_unInt32PropertyTag = 2;
স্থির ধ্রুবক unsigned long k_unUint64PropertyTag = 3;
স্থির ধ্রুবক unsigned long k_unBoolPropertyTag = 4;
স্থির ধ্রুবক unsigned long k_unStringPropertyTag = 5;
স্থির ধ্রুবক unsigned long k_unErrorPropertyTag = 6;
স্থির ধ্রুবক unsigned long k_unDoublePropertyTag = 7;
স্থির ধ্রুবক unsigned long k_unHmdMatrix34PropertyTag = 20;
স্থির ধ্রুবক unsigned long k_unHmdMatrix44PropertyTag = 21;
স্থির ধ্রুবক unsigned long k_unHmdVector3PropertyTag = 22;
স্থির ধ্রুবক unsigned long k_unHmdVector4PropertyTag = 23;
স্থির ধ্রুবক unsigned long k_unHmdVector2PropertyTag = 24;
স্থির ধ্রুবক unsigned long k_unHmdQuadPropertyTag = 25;
স্থির ধ্রুবক unsigned long k_unHiddenAreaPropertyTag = 30;
স্থির ধ্রুবক unsigned long k_unPathHandleInfoTag = 31;
স্থির ধ্রুবক unsigned long k_unActionPropertyTag = 32;
স্থির ধ্রুবক unsigned long k_un_প্রবেশ_মান_Property_Tag = 33;
স্থির ধ্রুবক unsigned long k_unWildcardPropertyTag = 34;
স্থির ধ্রুবক unsigned long k_unHapticVibrationPropertyTag = 35;
স্থির ধ্রুবক unsigned long k_unSkeletonPropertyTag = 36;
স্থির ধ্রুবক unsigned long k_unSpatialAnchorPosePropertyTag = 40;
স্থির ধ্রুবক unsigned long k_unJsonPropertyTag = 41;
স্থির ধ্রুবক unsigned long k_unActiveActionSetPropertyTag = 42;
স্থির ধ্রুবক unsigned long k_unOpenVRInternalReserved_Start = 1000;
স্থির ধ্রুবক unsigned long k_unOpenVRInternalReserved_End = 10000;
স্থির ধ্রুবক unsigned long k_un_Max_Property_String_আকার = 32768;
স্থির ধ্রুবক unsigned long long k_ulInvalidActionHandle = 0;
স্থির ধ্রুবক unsigned long long k_ulInvalidActionSetHandle = 0;
স্থির ধ্রুবক unsigned long long k_ul_Invalid_প্রবেশ_মান_Handle = 0;
স্থির ধ্রুবক unsigned long k_un_Controller_State_Axis_গুনতি = 5;
স্থির ধ্রুবক unsigned long long k_ulOverlayHandleInvalid = 0;
স্থির ধ্রুবক unsigned long k_unMaxDistortionFunctionParameters = 8;
স্থির ধ্রুবক unsigned long k_unScreenshotHandleInvalid = 0;
স্থির ধ্রুবক অক্ষর * IVRSystem_Version = "IVRSystem_022";
স্থির ধ্রুবক অক্ষর * IVRExtendedDisplay_Version = "IVRExtendedDisplay_001";
স্থির ধ্রুবক অক্ষর * IVRTrackedCamera_Version = "IVRTrackedCamera_006";
স্থির ধ্রুবক unsigned long k_un_Max_Application_চাবি_দৈর্ঘ্য = 128;
স্থির ধ্রুবক অক্ষর * k_pch_MimeType_HomeApp = "vr/home";
স্থির ধ্রুবক অক্ষর * k_pch_MimeType_GameTheater = "vr/game_theater";
স্থির ধ্রুবক অক্ষর * IVRApplications_Version = "IVRApplications_007";
স্থির ধ্রুবক অক্ষর * IVRChaperone_Version = "IVRChaperone_004";
স্থির ধ্রুবক অক্ষর * IVRChaperoneSetup_Version = "IVRChaperoneSetup_006";
স্থির ধ্রুবক অক্ষর * IVRCompositor_Version = "IVRCompositor_027";
স্থির ধ্রুবক unsigned long k_un_VROverlay_Max_চাবি_দৈর্ঘ্য = 128;
স্থির ধ্রুবক unsigned long k_un_VROverlay_Max_Name_দৈর্ঘ্য = 128;
স্থির ধ্রুবক unsigned long k_un_Max_Overlay_গুনতি = 128;
স্থির ধ্রুবক unsigned long k_un_Max_Overlay_Intersection_Mask_Primitives_গুনতি = 32;
স্থির ধ্রুবক অক্ষর * IVROverlay_Version = "IVROverlay_026";
স্থির ধ্রুবক অক্ষর * IVROverlayView_Version = "IVROverlayView_003";
স্থির ধ্রুবক unsigned long k_unHeadsetViewMaxWidth = 3840;
স্থির ধ্রুবক unsigned long k_unHeadsetViewMaxHeight = 2160;
স্থির ধ্রুবক অক্ষর * k_pch_Headset_View_Overlay_চাবি = "system.HeadsetView";
স্থির ধ্রুবক অক্ষর * IVRHeadsetView_Version = "IVRHeadsetView_001";
স্থির ধ্রুবক অক্ষর * k_pch_Controller_Component_GDC2015 = "gdc2015";
স্থির ধ্রুবক অক্ষর * k_pch_Controller_Component_Base = "base";
স্থির ধ্রুবক অক্ষর * k_pch_Controller_Component_Tip = "tip";
স্থির ধ্রুবক অক্ষর * k_pch_Controller_Component_OpenXR_Aim = "openxr_aim";
স্থির ধ্রুবক অক্ষর * k_pch_Controller_Component_HandGrip = "handgrip";
স্থির ধ্রুবক অক্ষর * k_pch_Controller_Component_OpenXR_Grip = "openxr_grip";
স্থির ধ্রুবক অক্ষর * k_pch_Controller_Component_OpenXR_HandModel = "openxr_handmodel";
স্থির ধ্রুবক অক্ষর * k_pch_Controller_Component_Status = "status";
স্থির ধ্রুবক অক্ষর * IVRRenderModels_Version = "IVRRenderModels_006";
স্থির ধ্রুবক unsigned long k_un_Notification_Text_Max_আকার = 256;
স্থির ধ্রুবক অক্ষর * IVRNotifications_Version = "IVRNotifications_002";
স্থির ধ্রুবক unsigned long k_un_Max_Settings_চাবি_দৈর্ঘ্য = 128;
স্থির ধ্রুবক অক্ষর * IVRSettings_Version = "IVRSettings_003";
স্থির ধ্রুবক অক্ষর * k_pch_SteamVR_Section = "steamvr";
স্থির ধ্রুবক অক্ষর * k_pch_SteamVR_RequireHmd_String = "requireHmd";
স্থির ধ্রুবক অক্ষর * k_pch_Steam_VR_Forced_Driver_চাবি_String = "forcedDriver";
স্থির ধ্রুবক অক্ষর * k_pch_Steam_VR_Forced_Hmd_চাবি_String = "forcedHmd";
স্থির ধ্রুবক অক্ষর * k_pch_SteamVR_DisplayDebug_Bool = "displayDebug";
স্থির ধ্রুবক অক্ষর * k_pch_SteamVR_DebugProcessPipe_String = "debugProcessPipe";
স্থির ধ্রুবক অক্ষর * k_pch_SteamVR_DisplayDebugX_Int32 = "displayDebugX";
স্থির ধ্রুবক অক্ষর * k_pch_SteamVR_DisplayDebugY_Int32 = "displayDebugY";
স্থির ধ্রুবক অক্ষর * k_pch_SteamVR_SendSystemButtonToAllApps_Bool = "sendSystemButtonToAllApps";
স্থির ধ্রুবক অক্ষর * k_pch_SteamVR_LogLevel_Int32 = "loglevel";
স্থির ধ্রুবক অক্ষর * k_pch_SteamVR_IPD_Float = "ipd";
স্থির ধ্রুবক অক্ষর * k_pch_SteamVR_Background_String = "background";
স্থির ধ্রুবক অক্ষর * k_pch_SteamVR_BackgroundUseDomeProjection_Bool = "backgroundUseDomeProjection";
স্থির ধ্রুবক অক্ষর * k_pch_SteamVR_BackgroundCameraHeight_Float = "backgroundCameraHeight";
স্থির ধ্রুবক অক্ষর * k_pch_SteamVR_BackgroundDomeRadius_Float = "backgroundDomeRadius";
স্থির ধ্রুবক অক্ষর * k_pch_SteamVR_GridColor_String = "gridColor";
স্থির ধ্রুবক অক্ষর * k_pch_SteamVR_PlayAreaColor_String = "playAreaColor";
স্থির ধ্রুবক অক্ষর * k_pch_SteamVR_TrackingLossColor_String = "trackingLossColor";
স্থির ধ্রুবক অক্ষর * k_pch_SteamVR_ShowStage_Bool = "showStage";
স্থির ধ্রুবক অক্ষর * k_pch_SteamVR_DrawTrackingReferences_Bool = "drawTrackingReferences";
স্থির ধ্রুবক অক্ষর * k_pch_SteamVR_ActivateMultipleDrivers_Bool = "activateMultipleDrivers";
স্থির ধ্রুবক অক্ষর * k_pch_SteamVR_UsingSpeakers_Bool = "usingSpeakers";
স্থির ধ্রুবক অক্ষর * k_pch_SteamVR_SpeakersForwardYawOffsetDegrees_Float = "speakersForwardYawOffsetDegrees";
স্থির ধ্রুবক অক্ষর * k_pch_SteamVR_BaseStationPowerManagement_Int32 = "basestationPowerManagement";
স্থির ধ্রুবক অক্ষর * k_pch_SteamVR_ShowBaseStationPowerManagementTip_Int32 = "ShowBaseStationPowerManagementTip";
স্থির ধ্রুবক অক্ষর * k_pch_SteamVR_NeverKillProcesses_Bool = "neverKillProcesses";
স্থির ধ্রুবক অক্ষর * k_pch_SteamVR_SupersampleScale_Float = "supersampleScale";
স্থির ধ্রুবক অক্ষর * k_pch_SteamVR_MaxRecommendedResolution_Int32 = "maxRecommendedResolution";
স্থির ধ্রুবক অক্ষর * k_pch_SteamVR_MotionSmoothing_Bool = "motionSmoothing";
স্থির ধ্রুবক অক্ষর * k_pch_SteamVR_MotionSmoothingOverride_Int32 = "motionSmoothingOverride";
স্থির ধ্রুবক অক্ষর * k_pch_SteamVR_FramesToThrottle_Int32 = "framesToThrottle";
স্থির ধ্রুবক অক্ষর * k_pch_SteamVR_AdditionalFramesToPredict_Int32 = "additionalFramesToPredict";
স্থির ধ্রুবক অক্ষর * k_pch_SteamVR_WorldScale_Float = "worldScale";
স্থির ধ্রুবক অক্ষর * k_pch_SteamVR_FovScale_Int32 = "fovScale";
স্থির ধ্রুবক অক্ষর * k_pch_SteamVR_DisableAsyncReprojection_Bool = "disableAsync";
স্থির ধ্রুবক অক্ষর * k_pch_SteamVR_ForceFadeOnBadTracking_Bool = "forceFadeOnBadTracking";
স্থির ধ্রুবক অক্ষর * k_pch_SteamVR_DefaultMirrorView_Int32 = "mirrorView";
স্থির ধ্রুবক অক্ষর * k_pch_SteamVR_ShowLegacyMirrorView_Bool = "showLegacyMirrorView";
স্থির ধ্রুবক অক্ষর * k_pch_SteamVR_MirrorViewVisibility_Bool = "showMirrorView";
স্থির ধ্রুবক অক্ষর * k_pch_SteamVR_MirrorViewDisplayMode_Int32 = "mirrorViewDisplayMode";
স্থির ধ্রুবক অক্ষর * k_pch_SteamVR_MirrorViewEye_Int32 = "mirrorViewEye";
স্থির ধ্রুবক অক্ষর * k_pch_SteamVR_MirrorViewGeometry_String = "mirrorViewGeometry";
স্থির ধ্রুবক অক্ষর * k_pch_SteamVR_MirrorViewGeometryMaximized_String = "mirrorViewGeometryMaximized";
স্থির ধ্রুবক অক্ষর * k_pch_SteamVR_PerfGraphVisibility_Bool = "showPerfGraph";
স্থির ধ্রুবক অক্ষর * k_pch_SteamVR_StartMonitorFromAppLaunch = "startMonitorFromAppLaunch";
স্থির ধ্রুবক অক্ষর * k_pch_SteamVR_StartCompositorFromAppLaunch_Bool = "startCompositorFromAppLaunch";
স্থির ধ্রুবক অক্ষর * k_pch_SteamVR_StartDashboardFromAppLaunch_Bool = "startDashboardFromAppLaunch";
স্থির ধ্রুবক অক্ষর * k_pch_SteamVR_StartOverlayAppsFromDashboard_Bool = "startOverlayAppsFromDashboard";
স্থির ধ্রুবক অক্ষর * k_pch_SteamVR_EnableHomeApp = "enableHomeApp";
স্থির ধ্রুবক অক্ষর * k_pch_SteamVR_CycleBackgroundImageTimeSec_Int32 = "CycleBackgroundImageTimeSec";
স্থির ধ্রুবক অক্ষর * k_pch_SteamVR_RetailDemo_Bool = "retailDemo";
স্থির ধ্রুবক অক্ষর * k_pch_SteamVR_IpdOffset_Float = "ipdOffset";
স্থির ধ্রুবক অক্ষর * k_pch_SteamVR_AllowSupersampleFiltering_Bool = "allowSupersampleFiltering";
স্থির ধ্রুবক অক্ষর * k_pch_SteamVR_SupersampleManualOverride_Bool = "supersampleManualOverride";
স্থির ধ্রুবক অক্ষর * k_pch_SteamVR_EnableLinuxVulkanAsync_Bool = "enableLinuxVulkanAsync";
স্থির ধ্রুবক অক্ষর * k_pch_SteamVR_AllowDisplayLockedMode_Bool = "allowDisplayLockedMode";
স্থির ধ্রুবক অক্ষর * k_pch_SteamVR_HaveStartedTutorialForNativeChaperoneDriver_Bool = "haveStartedTutorialForNativeChaperoneDriver";
স্থির ধ্রুবক অক্ষর * k_pch_SteamVR_ForceWindows32bitVRMonitor = "forceWindows32BitVRMonitor";
স্থির ধ্রুবক অক্ষর * k_pch_Steam_VR_Debug_প্রবেশ_Binding = "debugInputBinding";
স্থির ধ্রুবক অক্ষর * k_pch_SteamVR_DoNotFadeToGrid = "doNotFadeToGrid";
স্থির ধ্রুবক অক্ষর * k_pch_SteamVR_RenderCameraMode = "renderCameraMode";
স্থির ধ্রুবক অক্ষর * k_pch_SteamVR_EnableSharedResourceJournaling = "enableSharedResourceJournaling";
স্থির ধ্রুবক অক্ষর * k_pch_SteamVR_EnableSafeMode = "enableSafeMode";
স্থির ধ্রুবক অক্ষর * k_pch_SteamVR_PreferredRefreshRate = "preferredRefreshRate";
স্থির ধ্রুবক অক্ষর * k_pch_SteamVR_LastVersionNotice = "lastVersionNotice";
স্থির ধ্রুবক অক্ষর * k_pch_SteamVR_LastVersionNoticeDate = "lastVersionNoticeDate";
স্থির ধ্রুবক অক্ষর * k_pch_SteamVR_HmdDisplayColorGainR_Float = "hmdDisplayColorGainR";
স্থির ধ্রুবক অক্ষর * k_pch_SteamVR_HmdDisplayColorGainG_Float = "hmdDisplayColorGainG";
স্থির ধ্রুবক অক্ষর * k_pch_SteamVR_HmdDisplayColorGainB_Float = "hmdDisplayColorGainB";
স্থির ধ্রুবক অক্ষর * k_pch_SteamVR_CustomIconStyle_String = "customIconStyle";
স্থির ধ্রুবক অক্ষর * k_pch_SteamVR_CustomOffIconStyle_String = "customOffIconStyle";
স্থির ধ্রুবক অক্ষর * k_pch_SteamVR_CustomIconForceUpdate_String = "customIconForceUpdate";
স্থির ধ্রুবক অক্ষর * k_pch_SteamVR_AllowGlobalActionSetPriority = "globalActionSetPriority";
স্থির ধ্রুবক অক্ষর * k_pch_SteamVR_OverlayRenderQuality = "overlayRenderQuality_2";
স্থির ধ্রুবক অক্ষর * k_pch_SteamVR_BlockOculusSDKOnOpenVRLaunchOption_Bool = "blockOculusSDKOnOpenVRLaunchOption";
স্থির ধ্রুবক অক্ষর * k_pch_SteamVR_BlockOculusSDKOnAllLaunches_Bool = "blockOculusSDKOnAllLaunches";
স্থির ধ্রুবক অক্ষর * k_pch_SteamVR_HDCPLegacyCompatibility_Bool = "hdcp14legacyCompatibility";
স্থির ধ্রুবক অক্ষর * k_pch_SteamVR_DisplayPortTrainingMode_Int = "displayPortTrainingMode";
স্থির ধ্রুবক অক্ষর * k_pch_SteamVR_UsePrism_Bool = "usePrism";
স্থির ধ্রুবক অক্ষর * k_pch_DirectMode_Section = "direct_mode";
স্থির ধ্রুবক অক্ষর * k_pch_DirectMode_Enable_Bool = "enable";
স্থির ধ্রুবক অক্ষর * k_pch_Direct_Mode_গুনতি_Int32 = "count";
স্থির ধ্রুবক অক্ষর * k_pch_DirectMode_EdidVid_Int32 = "edidVid";
স্থির ধ্রুবক অক্ষর * k_pch_DirectMode_EdidPid_Int32 = "edidPid";
স্থির ধ্রুবক অক্ষর * k_pch_Lighthouse_Section = "driver_lighthouse";
স্থির ধ্রুবক অক্ষর * k_pch_Lighthouse_DisableIMU_Bool = "disableimu";
স্থির ধ্রুবক অক্ষর * k_pch_Lighthouse_DisableIMUExceptHMD_Bool = "disableimuexcepthmd";
স্থির ধ্রুবক অক্ষর * k_pch_Lighthouse_UseDisambiguation_String = "usedisambiguation";
স্থির ধ্রুবক অক্ষর * k_pch_Lighthouse_DisambiguationDebug_Int32 = "disambiguationdebug";
স্থির ধ্রুবক অক্ষর * k_pch_Lighthouse_PrimaryBasestation_Int32 = "primarybasestation";
স্থির ধ্রুবক অক্ষর * k_pch_Lighthouse_DBHistory_Bool = "dbhistory";
স্থির ধ্রুবক অক্ষর * k_pch_Lighthouse_EnableBluetooth_Bool = "enableBluetooth";
স্থির ধ্রুবক অক্ষর * k_pch_Lighthouse_PowerManagedBaseStations_String = "PowerManagedBaseStations";
স্থির ধ্রুবক অক্ষর * k_pch_Lighthouse_PowerManagedBaseStations2_String = "PowerManagedBaseStations2";
স্থির ধ্রুবক অক্ষর * k_pch_Lighthouse_InactivityTimeoutForBaseStations_Int32 = "InactivityTimeoutForBaseStations";
স্থির ধ্রুবক অক্ষর * k_pch_Lighthouse_EnableImuFallback_Bool = "enableImuFallback";
স্থির ধ্রুবক অক্ষর * k_pch_Null_Section = "driver_null";
স্থির ধ্রুবক অক্ষর * k_pch_Null_Serial_সংখ্যা_String = "serialNumber";
স্থির ধ্রুবক অক্ষর * k_pch_Null_Model_সংখ্যা_String = "modelNumber";
স্থির ধ্রুবক অক্ষর * k_pch_Null_WindowX_Int32 = "windowX";
স্থির ধ্রুবক অক্ষর * k_pch_Null_WindowY_Int32 = "windowY";
স্থির ধ্রুবক অক্ষর * k_pch_Null_WindowWidth_Int32 = "windowWidth";
স্থির ধ্রুবক অক্ষর * k_pch_Null_WindowHeight_Int32 = "windowHeight";
স্থির ধ্রুবক অক্ষর * k_pch_Null_RenderWidth_Int32 = "renderWidth";
স্থির ধ্রুবক অক্ষর * k_pch_Null_RenderHeight_Int32 = "renderHeight";
স্থির ধ্রুবক অক্ষর * k_pch_Null_SecondsFromVsyncToPhotons_Float = "secondsFromVsyncToPhotons";
স্থির ধ্রুবক অক্ষর * k_pch_Null_DisplayFrequency_Float = "displayFrequency";
স্থির ধ্রুবক অক্ষর * k_pch_WindowsMR_Section = "driver_holographic";
স্থির ধ্রুবক অক্ষর * k_pch_UserInterface_Section = "userinterface";
স্থির ধ্রুবক অক্ষর * k_pch_User_Interface_Status_Always_On_শীর্ষ_Bool = "StatusAlwaysOnTop";
স্থির ধ্রুবক অক্ষর * k_pch_UserInterface_MinimizeToTray_Bool = "MinimizeToTray";
স্থির ধ্রুবক অক্ষর * k_pch_UserInterface_HidePopupsWhenStatusMinimized_Bool = "HidePopupsWhenStatusMinimized";
স্থির ধ্রুবক অক্ষর * k_pch_UserInterface_Screenshots_Bool = "screenshots";
স্থির ধ্রুবক অক্ষর * k_pch_UserInterface_ScreenshotType_Int = "screenshotType";
স্থির ধ্রুবক অক্ষর * k_pch_Notifications_Section = "notifications";
স্থির ধ্রুবক অক্ষর * k_pch_Notifications_DoNotDisturb_Bool = "DoNotDisturb";
স্থির ধ্রুবক অক্ষর * k_pch_Keyboard_Section = "keyboard";
স্থির ধ্রুবক অক্ষর * k_pch_Keyboard_TutorialCompletions = "TutorialCompletions";
স্থির ধ্রুবক অক্ষর * k_pch_Keyboard_ScaleX = "ScaleX";
স্থির ধ্রুবক অক্ষর * k_pch_Keyboard_ScaleY = "ScaleY";
স্থির ধ্রুবক অক্ষর * k_pch_Keyboard_Offset_বাম_X = "OffsetLeftX";
স্থির ধ্রুবক অক্ষর * k_pch_Keyboard_Offset_ডান_X = "OffsetRightX";
স্থির ধ্রুবক অক্ষর * k_pch_Keyboard_OffsetY = "OffsetY";
স্থির ধ্রুবক অক্ষর * k_pch_Keyboard_Smoothing = "Smoothing";
স্থির ধ্রুবক অক্ষর * k_pch_Perf_Section = "perfcheck";
স্থির ধ্রুবক অক্ষর * k_pch_Perf_PerfGraphInHMD_Bool = "perfGraphInHMD";
স্থির ধ্রুবক অক্ষর * k_pch_Perf_AllowTimingStore_Bool = "allowTimingStore";
স্থির ধ্রুবক অক্ষর * k_pch_Perf_SaveTimingsOnExit_Bool = "saveTimingsOnExit";
স্থির ধ্রুবক অক্ষর * k_pch_Perf_Test_তথ্য_Float = "perfTestData";
স্থির ধ্রুবক অক্ষর * k_pch_Perf_GPUProfiling_Bool = "GPUProfiling";
স্থির ধ্রুবক অক্ষর * k_pch_CollisionBounds_Section = "collisionBounds";
স্থির ধ্রুবক অক্ষর * k_pch_CollisionBounds_Style_Int32 = "CollisionBoundsStyle";
স্থির ধ্রুবক অক্ষর * k_pch_CollisionBounds_GroundPerimeterOn_Bool = "CollisionBoundsGroundPerimeterOn";
স্থির ধ্রুবক অক্ষর * k_pch_CollisionBounds_CenterMarkerOn_Bool = "CollisionBoundsCenterMarkerOn";
স্থির ধ্রুবক অক্ষর * k_pch_CollisionBounds_PlaySpaceOn_Bool = "CollisionBoundsPlaySpaceOn";
স্থির ধ্রুবক অক্ষর * k_pch_CollisionBounds_FadeDistance_Float = "CollisionBoundsFadeDistance";
স্থির ধ্রুবক অক্ষর * k_pch_CollisionBounds_WallHeight_Float = "CollisionBoundsWallHeight";
স্থির ধ্রুবক অক্ষর * k_pch_CollisionBounds_ColorGammaR_Int32 = "CollisionBoundsColorGammaR";
স্থির ধ্রুবক অক্ষর * k_pch_CollisionBounds_ColorGammaG_Int32 = "CollisionBoundsColorGammaG";
স্থির ধ্রুবক অক্ষর * k_pch_CollisionBounds_ColorGammaB_Int32 = "CollisionBoundsColorGammaB";
স্থির ধ্রুবক অক্ষর * k_pch_CollisionBounds_ColorGammaA_Int32 = "CollisionBoundsColorGammaA";
স্থির ধ্রুবক অক্ষর * k_pch_CollisionBounds_EnableDriverImport = "enableDriverBoundsImport";
স্থির ধ্রুবক অক্ষর * k_pch_Camera_Section = "camera";
স্থির ধ্রুবক অক্ষর * k_pch_Camera_EnableCamera_Bool = "enableCamera";
স্থির ধ্রুবক অক্ষর * k_pch_Camera_ShowOnController_Bool = "showOnController";
স্থির ধ্রুবক অক্ষর * k_pch_Camera_EnableCameraForCollisionBounds_Bool = "enableCameraForCollisionBounds";
স্থির ধ্রুবক অক্ষর * k_pch_Camera_RoomView_Int32 = "roomView";
স্থির ধ্রুবক অক্ষর * k_pch_Camera_BoundsColorGammaR_Int32 = "cameraBoundsColorGammaR";
স্থির ধ্রুবক অক্ষর * k_pch_Camera_BoundsColorGammaG_Int32 = "cameraBoundsColorGammaG";
স্থির ধ্রুবক অক্ষর * k_pch_Camera_BoundsColorGammaB_Int32 = "cameraBoundsColorGammaB";
স্থির ধ্রুবক অক্ষর * k_pch_Camera_BoundsColorGammaA_Int32 = "cameraBoundsColorGammaA";
স্থির ধ্রুবক অক্ষর * k_pch_Camera_BoundsStrength_Int32 = "cameraBoundsStrength";
স্থির ধ্রুবক অক্ষর * k_pch_Camera_RoomViewStyle_Int32 = "roomViewStyle";
স্থির ধ্রুবক অক্ষর * k_pch_audio_Section = "audio";
স্থির ধ্রুবক অক্ষর * k_pch_audio_SetOsDefaultPlaybackDevice_Bool = "setOsDefaultPlaybackDevice";
স্থির ধ্রুবক অক্ষর * k_pch_audio_EnablePlaybackDeviceOverride_Bool = "enablePlaybackDeviceOverride";
স্থির ধ্রুবক অক্ষর * k_pch_audio_PlaybackDeviceOverride_String = "playbackDeviceOverride";
স্থির ধ্রুবক অক্ষর * k_pch_audio_PlaybackDeviceOverrideName_String = "playbackDeviceOverrideName";
স্থির ধ্রুবক অক্ষর * k_pch_audio_SetOsDefaultRecordingDevice_Bool = "setOsDefaultRecordingDevice";
স্থির ধ্রুবক অক্ষর * k_pch_audio_EnableRecordingDeviceOverride_Bool = "enableRecordingDeviceOverride";
স্থির ধ্রুবক অক্ষর * k_pch_audio_RecordingDeviceOverride_String = "recordingDeviceOverride";
স্থির ধ্রুবক অক্ষর * k_pch_audio_RecordingDeviceOverrideName_String = "recordingDeviceOverrideName";
স্থির ধ্রুবক অক্ষর * k_pch_audio_EnablePlaybackMirror_Bool = "enablePlaybackMirror";
স্থির ধ্রুবক অক্ষর * k_pch_audio_PlaybackMirrorDevice_String = "playbackMirrorDevice";
স্থির ধ্রুবক অক্ষর * k_pch_audio_PlaybackMirrorDeviceName_String = "playbackMirrorDeviceName";
স্থির ধ্রুবক অক্ষর * k_pch_audio_OldPlaybackMirrorDevice_String = "onPlaybackMirrorDevice";
স্থির ধ্রুবক অক্ষর * k_pch_audio_ActiveMirrorDevice_String = "activePlaybackMirrorDevice";
স্থির ধ্রুবক অক্ষর * k_pch_audio_EnablePlaybackMirrorIndependentVolume_Bool = "enablePlaybackMirrorIndependentVolume";
স্থির ধ্রুবক অক্ষর * k_pch_audio_LastHmdPlaybackDeviceId_String = "lastHmdPlaybackDeviceId";
স্থির ধ্রুবক অক্ষর * k_pch_audio_VIVEHDMIGain = "viveHDMIGain";
স্থির ধ্রুবক অক্ষর * k_pch_audio_DualSpeakerAndJackOutput_Bool = "dualSpeakerAndJackOutput";
স্থির ধ্রুবক অক্ষর * k_pch_audio_MuteMicMonitor_Bool = "muteMicMonitor";
স্থির ধ্রুবক অক্ষর * k_pch_Power_Section = "power";
স্থির ধ্রুবক অক্ষর * k_pch_Power_PowerOffOnExit_Bool = "powerOffOnExit";
স্থির ধ্রুবক অক্ষর * k_pch_Power_TurnOffScreensTimeout_Float = "turnOffScreensTimeout";
স্থির ধ্রুবক অক্ষর * k_pch_Power_TurnOffControllersTimeout_Float = "turnOffControllersTimeout";
স্থির ধ্রুবক অক্ষর * k_pch_Power_ReturnToWatchdogTimeout_Float = "returnToWatchdogTimeout";
স্থির ধ্রুবক অক্ষর * k_pch_Power_AutoLaunchSteamVROnButtonPress = "autoLaunchSteamVROnButtonPress";
স্থির ধ্রুবক অক্ষর * k_pch_Power_PauseCompositorOnStandby_Bool = "pauseCompositorOnStandby";
স্থির ধ্রুবক অক্ষর * k_pch_Dashboard_Section = "dashboard";
স্থির ধ্রুবক অক্ষর * k_pch_Dashboard_EnableDashboard_Bool = "enableDashboard";
স্থির ধ্রুবক অক্ষর * k_pch_Dashboard_ArcadeMode_Bool = "arcadeMode";
স্থির ধ্রুবক অক্ষর * k_pch_Dashboard_Position = "position";
স্থির ধ্রুবক অক্ষর * k_pch_Dashboard_DesktopScale = "desktopScale";
স্থির ধ্রুবক অক্ষর * k_pch_Dashboard_DashboardScale = "dashboardScale";
স্থির ধ্রুবক অক্ষর * k_pch_Dashboard_UseStandaloneSystemLayer = "standaloneSystemLayer";
স্থির ধ্রুবক অক্ষর * k_pch_Dashboard_StickyDashboard = "stickyDashboard";
স্থির ধ্রুবক অক্ষর * k_pch_modelskin_Section = "modelskins";
স্থির ধ্রুবক অক্ষর * k_pch_Driver_Enable_Bool = "enable";
স্থির ধ্রুবক অক্ষর * k_pch_Driver_BlockedBySafemode_Bool = "blocked_by_safe_mode";
স্থির ধ্রুবক অক্ষর * k_pch_Driver_LoadPriority_Int32 = "loadPriority";
স্থির ধ্রুবক অক্ষর * k_pch_WebInterface_Section = "WebInterface";
স্থির ধ্রুবক অক্ষর * k_pch_VRWebHelper_Section = "VRWebHelper";
স্থির ধ্রুবক অক্ষর * k_pch_VRWebHelper_DebuggerEnabled_Bool = "DebuggerEnabled";
স্থির ধ্রুবক অক্ষর * k_pch_VRWebHelper_DebuggerPort_Int32 = "DebuggerPort";
স্থির ধ্রুবক অক্ষর * k_pch_TrackingOverride_Section = "TrackingOverrides";
স্থির ধ্রুবক অক্ষর * k_pch_App_BindingAutosaveURLSuffix_String = "AutosaveURL";
স্থির ধ্রুবক অক্ষর * k_pch_App_BindingLegacyAPISuffix_String = "_legacy";
স্থির ধ্রুবক অক্ষর * k_pch_App_BindingSteamVRInputAPISuffix_String = "_steamvrinput";
স্থির ধ্রুবক অক্ষর * k_pch_App_BindingOpenXRAPISuffix_String = "_openxr";
স্থির ধ্রুবক অক্ষর * k_pch_App_BindingCurrentURLSuffix_String = "CurrentURL";
স্থির ধ্রুবক অক্ষর * k_pch_App_BindingPreviousURLSuffix_String = "PreviousURL";
স্থির ধ্রুবক অক্ষর * k_pch_App_NeedToUpdateAutosaveSuffix_Bool = "NeedToUpdateAutosave";
স্থির ধ্রুবক অক্ষর * k_pch_App_DominantHand_Int32 = "DominantHand";
স্থির ধ্রুবক অক্ষর * k_pch_App_BlockOculusSDK_Bool = "blockOculusSDK";
স্থির ধ্রুবক অক্ষর * k_pch_Trackers_Section = "trackers";
স্থির ধ্রুবক অক্ষর * k_pch_DesktopUI_Section = "DesktopUI";
স্থির ধ্রুবক অক্ষর * k_pch_LastKnown_Section = "LastKnown";
স্থির ধ্রুবক অক্ষর * k_pch_LastKnown_HMDManufacturer_String = "HMDManufacturer";
স্থির ধ্রুবক অক্ষর * k_pch_LastKnown_HMDModel_String = "HMDModel";
স্থির ধ্রুবক অক্ষর * k_pch_DismissedWarnings_Section = "DismissedWarnings";
স্থির ধ্রুবক অক্ষর * k_pch_প্রবেশ_Section = "input";
স্থির ধ্রুবক অক্ষর * k_pch_প্রবেশ_বাম_Thumbstick_Rotation_Float = "leftThumbstickRotation";
স্থির ধ্রুবক অক্ষর * k_pch_প্রবেশ_ডান_Thumbstick_Rotation_Float = "rightThumbstickRotation";
স্থির ধ্রুবক অক্ষর * k_pch_প্রবেশ_Thumbstick_Deadzone_Float = "thumbstickDeadzone";
স্থির ধ্রুবক অক্ষর * k_pch_GpuSpeed_Section = "GpuSpeed";
স্থির ধ্রুবক অক্ষর * IVRScreenshots_Version = "IVRScreenshots_001";
স্থির ধ্রুবক অক্ষর * IVRResources_Version = "IVRResources_001";
স্থির ধ্রুবক অক্ষর * IVRDriverManager_Version = "IVRDriverManager_001";
স্থির ধ্রুবক unsigned long k_un_Max_Action_Name_দৈর্ঘ্য = 64;
স্থির ধ্রুবক unsigned long k_un_Max_Action_Set_Name_দৈর্ঘ্য = 64;
স্থির ধ্রুবক unsigned long k_un_Max_Action_Origin_গুনতি = 16;
স্থির ধ্রুবক unsigned long k_un_Max_Bone_Name_দৈর্ঘ্য = 32;
স্থির ধ্রুবক পূর্ণসংখ্যা k_nActionSetOverlayGlobalPriorityMin = 16777216;
স্থির ধ্রুবক পূর্ণসংখ্যা k_nActionSetOverlayGlobalPriorityMax = 33554431;
স্থির ধ্রুবক পূর্ণসংখ্যা k_nActionSetPriorityReservedMin = 33554432;
স্থির ধ্রুবক অক্ষর * IVRInput_Version = "IVRInput_010";
স্থির ধ্রুবক unsigned long long k_ulInvalidIOBufferHandle = 0;
স্থির ধ্রুবক অক্ষর * IVRIOBuffer_Version = "IVRIOBuffer_002";
স্থির ধ্রুবক unsigned long k_ulInvalidSpatialAnchorHandle = 0;
স্থির ধ্রুবক অক্ষর * IVRSpatialAnchors_Version = "IVRSpatialAnchors_001";
স্থির ধ্রুবক অক্ষর * IVRDebug_Version = "IVRDebug_001";
স্থির ধ্রুবক unsigned long long k_ulDisplayRedirectContainer = 25769803779;
স্থির ধ্রুবক অক্ষর * IVRProperties_Version = "IVRProperties_001";
স্থির ধ্রুবক অক্ষর * k_pch_Path_User_Hand_ডান = "/user/hand/right";
স্থির ধ্রুবক অক্ষর * k_pch_Path_User_Hand_বাম = "/user/hand/left";
স্থির ধ্রুবক অক্ষর * k_pchPathUserHandPrimary = "/user/hand/primary";
স্থির ধ্রুবক অক্ষর * k_pchPathUserHandSecondary = "/user/hand/secondary";
স্থির ধ্রুবক অক্ষর * k_pch_Path_User_শীর্ষ = "/user/head";
স্থির ধ্রুবক অক্ষর * k_pchPathUserGamepad = "/user/gamepad";
স্থির ধ্রুবক অক্ষর * k_pchPathUserTreadmill = "/user/treadmill";
স্থির ধ্রুবক অক্ষর * k_pchPathUserStylus = "/user/stylus";
স্থির ধ্রুবক অক্ষর * k_pchPathDevices = "/devices";
স্থির ধ্রুবক অক্ষর * k_pchPathDevicePath = "/device_path";
স্থির ধ্রুবক অক্ষর * k_pchPathBestAliasPath = "/best_alias_path";
স্থির ধ্রুবক অক্ষর * k_pchPathBoundTrackerAliasPath = "/bound_tracker_path";
স্থির ধ্রুবক অক্ষর * k_pchPathBoundTrackerRole = "/bound_tracker_role";
স্থির ধ্রুবক অক্ষর * k_pchPathPoseRaw = "/pose/raw";
স্থির ধ্রুবক অক্ষর * k_pchPathPoseTip = "/pose/tip";
স্থির ধ্রুবক অক্ষর * k_pchPathPoseGrip = "/pose/grip";
স্থির ধ্রুবক অক্ষর * k_pchPathSystemButtonClick = "/input/system/click";
স্থির ধ্রুবক অক্ষর * k_pchPathProximity = "/proximity";
স্থির ধ্রুবক অক্ষর * k_pchPathControllerTypePrefix = "/controller_type/";
স্থির ধ্রুবক অক্ষর * k_pch_Path_প্রবেশ_Profile_Suffix = "/input_profile";
স্থির ধ্রুবক অক্ষর * k_pchPathBindingNameSuffix = "/binding_name";
স্থির ধ্রুবক অক্ষর * k_pchPathBindingUrlSuffix = "/binding_url";
স্থির ধ্রুবক অক্ষর * k_pchPathBindingErrorSuffix = "/binding_error";
স্থির ধ্রুবক অক্ষর * k_pchPathActiveActionSets = "/active_action_sets";
স্থির ধ্রুবক অক্ষর * k_pchPathComponentUpdates = "/total_component_updates";
স্থির ধ্রুবক অক্ষর * k_pch_Path_User_Foot_বাম = "/user/foot/left";
স্থির ধ্রুবক অক্ষর * k_pch_Path_User_Foot_ডান = "/user/foot/right";
স্থির ধ্রুবক অক্ষর * k_pch_Path_User_Shoulder_বাম = "/user/shoulder/left";
স্থির ধ্রুবক অক্ষর * k_pch_Path_User_Shoulder_ডান = "/user/shoulder/right";
স্থির ধ্রুবক অক্ষর * k_pch_Path_User_Elbow_বাম = "/user/elbow/left";
স্থির ধ্রুবক অক্ষর * k_pch_Path_User_Elbow_ডান = "/user/elbow/right";
স্থির ধ্রুবক অক্ষর * k_pch_Path_User_Knee_বাম = "/user/knee/left";
স্থির ধ্রুবক অক্ষর * k_pch_Path_User_Knee_ডান = "/user/knee/right";
স্থির ধ্রুবক অক্ষর * k_pchPathUserWaist = "/user/waist";
স্থির ধ্রুবক অক্ষর * k_pchPathUserChest = "/user/chest";
স্থির ধ্রুবক অক্ষর * k_pchPathUserCamera = "/user/camera";
স্থির ধ্রুবক অক্ষর * k_pchPathUserKeyboard = "/user/keyboard";
স্থির ধ্রুবক অক্ষর * k_pch_Path_Client_App_চাবি = "/client_info/app_key";
স্থির ধ্রুবক unsigned long long k_ulInvalidPathHandle = 0;
স্থির ধ্রুবক অক্ষর * IVRPaths_Version = "IVRPaths_001";
স্থির ধ্রুবক অক্ষর * IVRBlockQueue_Version = "IVRBlockQueue_005";

// OpenVR Enums

প্রকারলেখ গণনা EVREye
{
	EVREye_Eye_বাম = 0,
	EVREye_Eye_ডান = 1,
} EVREye;

প্রকারলেখ গণনা ETextureType
{
	ETextureType_TextureType_Invalid = -1,
	ETextureType_TextureType_DirectX = 0,
	ETextureType_TextureType_OpenGL = 1,
	ETextureType_TextureType_Vulkan = 2,
	ETextureType_TextureType_IOSurface = 3,
	ETextureType_TextureType_DirectX12 = 4,
	ETextureType_TextureType_DXGISharedHandle = 5,
	ETextureType_TextureType_Metal = 6,
} ETextureType;

প্রকারলেখ গণনা EColorSpace
{
	EColorSpace_ColorSpace_Auto = 0,
	EColorSpace_ColorSpace_Gamma = 1,
	EColorSpace_ColorSpace_Linear = 2,
} EColorSpace;

প্রকারলেখ গণনা ETracking_ফলাফল
{
	ETracking_ফলাফল_Tracking_ফলাফল_Uninitialized = 1,
	ETracking_ফলাফল_Tracking_ফলাফল_Calibrating_In_Progress = 100,
	ETracking_ফলাফল_Tracking_ফলাফল_Calibrating_Out_Of_Range = 101,
	ETracking_ফলাফল_Tracking_ফলাফল_Running_OK = 200,
	ETracking_ফলাফল_Tracking_ফলাফল_Running_Out_Of_Range = 201,
	ETracking_ফলাফল_Tracking_ফলাফল_Fallback_Rotation_Only = 300,
} ETracking_ফলাফল;

প্রকারলেখ গণনা ETrackedDeviceClass
{
	ETrackedDeviceClass_TrackedDeviceClass_Invalid = 0,
	ETrackedDeviceClass_TrackedDeviceClass_HMD = 1,
	ETrackedDeviceClass_TrackedDeviceClass_Controller = 2,
	ETrackedDeviceClass_TrackedDeviceClass_GenericTracker = 3,
	ETrackedDeviceClass_TrackedDeviceClass_TrackingReference = 4,
	ETrackedDeviceClass_TrackedDeviceClass_DisplayRedirect = 5,
	ETrackedDeviceClass_TrackedDeviceClass_Max = 6,
} ETrackedDeviceClass;

প্রকারলেখ গণনা ETrackedControllerRole
{
	ETrackedControllerRole_TrackedControllerRole_Invalid = 0,
	ETracked_Controller_Role_Tracked_Controller_Role_বাম_Hand = 1,
	ETracked_Controller_Role_Tracked_Controller_Role_ডান_Hand = 2,
	ETrackedControllerRole_TrackedControllerRole_OptOut = 3,
	ETrackedControllerRole_TrackedControllerRole_Treadmill = 4,
	ETrackedControllerRole_TrackedControllerRole_Stylus = 5,
	ETrackedControllerRole_TrackedControllerRole_Max = 5,
} ETrackedControllerRole;

প্রকারলেখ গণনা ETrackingUniverseOrigin
{
	ETrackingUniverseOrigin_TrackingUniverseSeated = 0,
	ETrackingUniverseOrigin_TrackingUniverseStanding = 1,
	ETrackingUniverseOrigin_TrackingUniverseRawAndUncalibrated = 2,
} ETrackingUniverseOrigin;

প্রকারলেখ গণনা EAdditionalRadioFeatures
{
	EAdditionalRadioFeatures_AdditionalRadioFeatures_None = 0,
	EAdditionalRadioFeatures_AdditionalRadioFeatures_HTCLinkBox = 1,
	EAdditionalRadioFeatures_AdditionalRadioFeatures_InternalDongle = 2,
	EAdditionalRadioFeatures_AdditionalRadioFeatures_ExternalDongle = 4,
} EAdditionalRadioFeatures;

প্রকারলেখ গণনা ETrackedDeviceProperty
{
	ETrackedDeviceProperty_Prop_Invalid = 0,
	ETrackedDeviceProperty_Prop_TrackingSystemName_String = 1000,
	ETracked_Device_Property_Prop_Model_সংখ্যা_String = 1001,
	ETracked_Device_Property_Prop_Serial_সংখ্যা_String = 1002,
	ETrackedDeviceProperty_Prop_RenderModelName_String = 1003,
	ETrackedDeviceProperty_Prop_WillDriftInYaw_Bool = 1004,
	ETrackedDeviceProperty_Prop_ManufacturerName_String = 1005,
	ETrackedDeviceProperty_Prop_TrackingFirmwareVersion_String = 1006,
	ETrackedDeviceProperty_Prop_HardwareRevision_String = 1007,
	ETrackedDeviceProperty_Prop_AllWirelessDongleDescriptions_String = 1008,
	ETrackedDeviceProperty_Prop_ConnectedWirelessDongle_String = 1009,
	ETrackedDeviceProperty_Prop_DeviceIsWireless_Bool = 1010,
	ETrackedDeviceProperty_Prop_DeviceIsCharging_Bool = 1011,
	ETrackedDeviceProperty_Prop_DeviceBatteryPercentage_Float = 1012,
	ETrackedDeviceProperty_Prop_StatusDisplayTransform_Matrix34 = 1013,
	ETrackedDeviceProperty_Prop_Firmware_UpdateAvailable_Bool = 1014,
	ETrackedDeviceProperty_Prop_Firmware_ManualUpdate_Bool = 1015,
	ETrackedDeviceProperty_Prop_Firmware_ManualUpdateURL_String = 1016,
	ETrackedDeviceProperty_Prop_HardwareRevision_Uint64 = 1017,
	ETrackedDeviceProperty_Prop_FirmwareVersion_Uint64 = 1018,
	ETrackedDeviceProperty_Prop_FPGAVersion_Uint64 = 1019,
	ETrackedDeviceProperty_Prop_VRCVersion_Uint64 = 1020,
	ETrackedDeviceProperty_Prop_RadioVersion_Uint64 = 1021,
	ETrackedDeviceProperty_Prop_DongleVersion_Uint64 = 1022,
	ETrackedDeviceProperty_Prop_BlockServerShutdown_Bool = 1023,
	ETrackedDeviceProperty_Prop_CanUnifyCoordinateSystemWithHmd_Bool = 1024,
	ETrackedDeviceProperty_Prop_ContainsProximitySensor_Bool = 1025,
	ETrackedDeviceProperty_Prop_DeviceProvidesBatteryStatus_Bool = 1026,
	ETrackedDeviceProperty_Prop_DeviceCanPowerOff_Bool = 1027,
	ETrackedDeviceProperty_Prop_Firmware_ProgrammingTarget_String = 1028,
	ETrackedDeviceProperty_Prop_DeviceClass_Int32 = 1029,
	ETrackedDeviceProperty_Prop_HasCamera_Bool = 1030,
	ETrackedDeviceProperty_Prop_DriverVersion_String = 1031,
	ETrackedDeviceProperty_Prop_Firmware_ForceUpdateRequired_Bool = 1032,
	ETrackedDeviceProperty_Prop_ViveSystemButtonFixRequired_Bool = 1033,
	ETrackedDeviceProperty_Prop_ParentDriver_Uint64 = 1034,
	ETracked_Device_Property_Prop_Resource_মূল_String = 1035,
	ETrackedDeviceProperty_Prop_RegisteredDeviceType_String = 1036,
	ETracked_Device_Property_Prop_প্রবেশ_Profile_Path_String = 1037,
	ETrackedDeviceProperty_Prop_NeverTracked_Bool = 1038,
	ETracked_Device_Property_Prop_অঙ্ক_Cameras_Int32 = 1039,
	ETrackedDeviceProperty_Prop_CameraFrameLayout_Int32 = 1040,
	ETrackedDeviceProperty_Prop_CameraStreamFormat_Int32 = 1041,
	ETrackedDeviceProperty_Prop_AdditionalDeviceSettingsPath_String = 1042,
	ETrackedDeviceProperty_Prop_Identifiable_Bool = 1043,
	ETrackedDeviceProperty_Prop_BootloaderVersion_Uint64 = 1044,
	ETracked_Device_Property_Prop_Additional_System_Report_তথ্য_String = 1045,
	ETrackedDeviceProperty_Prop_CompositeFirmwareVersion_String = 1046,
	ETrackedDeviceProperty_Prop_Firmware_RemindUpdate_Bool = 1047,
	ETrackedDeviceProperty_Prop_PeripheralApplicationVersion_Uint64 = 1048,
	ETracked_Device_Property_Prop_Manufacturer_Serial_সংখ্যা_String = 1049,
	ETracked_Device_Property_Prop_Computed_Serial_সংখ্যা_String = 1050,
	ETrackedDeviceProperty_Prop_EstimatedDeviceFirstUseTime_Int32 = 1051,
	ETrackedDeviceProperty_Prop_DevicePowerUsage_Float = 1052,
	ETrackedDeviceProperty_Prop_IgnoreMotionForStandby_Bool = 1053,
	ETrackedDeviceProperty_Prop_ReportsTimeSinceVSync_Bool = 2000,
	ETrackedDeviceProperty_Prop_SecondsFromVsyncToPhotons_Float = 2001,
	ETrackedDeviceProperty_Prop_DisplayFrequency_Float = 2002,
	ETrackedDeviceProperty_Prop_UserIpdMeters_Float = 2003,
	ETrackedDeviceProperty_Prop_CurrentUniverseId_Uint64 = 2004,
	ETrackedDeviceProperty_Prop_PreviousUniverseId_Uint64 = 2005,
	ETrackedDeviceProperty_Prop_DisplayFirmwareVersion_Uint64 = 2006,
	ETrackedDeviceProperty_Prop_IsOnDesktop_Bool = 2007,
	ETrackedDeviceProperty_Prop_DisplayMCType_Int32 = 2008,
	ETrackedDeviceProperty_Prop_DisplayMCOffset_Float = 2009,
	ETrackedDeviceProperty_Prop_DisplayMCScale_Float = 2010,
	ETrackedDeviceProperty_Prop_EdidVendorID_Int32 = 2011,
	ETracked_Device_Property_Prop_Display_MCImage_বাম_String = 2012,
	ETracked_Device_Property_Prop_Display_MCImage_ডান_String = 2013,
	ETrackedDeviceProperty_Prop_DisplayGCBlackClamp_Float = 2014,
	ETrackedDeviceProperty_Prop_EdidProductID_Int32 = 2015,
	ETracked_Device_Property_Prop_Camera_To_শীর্ষ_Transform_Matrix34 = 2016,
	ETrackedDeviceProperty_Prop_DisplayGCType_Int32 = 2017,
	ETrackedDeviceProperty_Prop_DisplayGCOffset_Float = 2018,
	ETrackedDeviceProperty_Prop_DisplayGCScale_Float = 2019,
	ETrackedDeviceProperty_Prop_DisplayGCPrescale_Float = 2020,
	ETrackedDeviceProperty_Prop_DisplayGCImage_String = 2021,
	ETracked_Device_Property_Prop_Lens_Center_বাম_U_Float = 2022,
	ETracked_Device_Property_Prop_Lens_Center_বাম_V_Float = 2023,
	ETracked_Device_Property_Prop_Lens_Center_ডান_U_Float = 2024,
	ETracked_Device_Property_Prop_Lens_Center_ডান_V_Float = 2025,
	ETracked_Device_Property_Prop_User_শীর্ষ_To_Eye_Depth_Meters_Float = 2026,
	ETrackedDeviceProperty_Prop_CameraFirmwareVersion_Uint64 = 2027,
	ETrackedDeviceProperty_Prop_CameraFirmwareDescription_String = 2028,
	ETrackedDeviceProperty_Prop_DisplayFPGAVersion_Uint64 = 2029,
	ETrackedDeviceProperty_Prop_DisplayBootloaderVersion_Uint64 = 2030,
	ETrackedDeviceProperty_Prop_DisplayHardwareVersion_Uint64 = 2031,
	ETrackedDeviceProperty_Prop_AudioFirmwareVersion_Uint64 = 2032,
	ETrackedDeviceProperty_Prop_CameraCompatibilityMode_Int32 = 2033,
	ETrackedDeviceProperty_Prop_ScreenshotHorizontalFieldOfViewDegrees_Float = 2034,
	ETrackedDeviceProperty_Prop_ScreenshotVerticalFieldOfViewDegrees_Float = 2035,
	ETrackedDeviceProperty_Prop_DisplaySuppressed_Bool = 2036,
	ETrackedDeviceProperty_Prop_DisplayAllowNightMode_Bool = 2037,
	ETrackedDeviceProperty_Prop_DisplayMCImageWidth_Int32 = 2038,
	ETrackedDeviceProperty_Prop_DisplayMCImageHeight_Int32 = 2039,
	ETracked_Device_Property_Prop_Display_MCImage_অঙ্ক_Channels_Int32 = 2040,
	ETracked_Device_Property_Prop_Display_MCImage_তথ্য_দ্বিমিক = 2041,
	ETrackedDeviceProperty_Prop_SecondsFromPhotonsToVblank_Float = 2042,
	ETrackedDeviceProperty_Prop_DriverDirectModeSendsVsyncEvents_Bool = 2043,
	ETrackedDeviceProperty_Prop_DisplayDebugMode_Bool = 2044,
	ETrackedDeviceProperty_Prop_GraphicsAdapterLuid_Uint64 = 2045,
	ETrackedDeviceProperty_Prop_DriverProvidedChaperonePath_String = 2048,
	ETracked_Device_Property_Prop_Expected_Tracking_Reference_গুনতি_Int32 = 2049,
	ETracked_Device_Property_Prop_Expected_Controller_গুনতি_Int32 = 2050,
	ETracked_Device_Property_Prop_Named_Icon_Path_Controller_বাম_Device_Off_String = 2051,
	ETracked_Device_Property_Prop_Named_Icon_Path_Controller_ডান_Device_Off_String = 2052,
	ETrackedDeviceProperty_Prop_NamedIconPathTrackingReferenceDeviceOff_String = 2053,
	ETrackedDeviceProperty_Prop_DoNotApplyPrediction_Bool = 2054,
	ETracked_Device_Property_Prop_Camera_To_শীর্ষ_Transforms_Matrix34_Array = 2055,
	ETrackedDeviceProperty_Prop_DistortionMeshResolution_Int32 = 2056,
	ETrackedDeviceProperty_Prop_DriverIsDrawingControllers_Bool = 2057,
	ETrackedDeviceProperty_Prop_DriverRequestsApplicationPause_Bool = 2058,
	ETrackedDeviceProperty_Prop_DriverRequestsReducedRendering_Bool = 2059,
	ETrackedDeviceProperty_Prop_MinimumIpdStepMeters_Float = 2060,
	ETrackedDeviceProperty_Prop_AudioBridgeFirmwareVersion_Uint64 = 2061,
	ETrackedDeviceProperty_Prop_ImageBridgeFirmwareVersion_Uint64 = 2062,
	ETracked_Device_Property_Prop_Imu_To_শীর্ষ_Transform_Matrix34 = 2063,
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
	ETrackedDeviceProperty_Prop_HmdColumnCorrectionSettingPrefix_String = 2077,
	ETrackedDeviceProperty_Prop_CameraSupportsCompatibilityModes_Bool = 2078,
	ETrackedDeviceProperty_Prop_SupportsRoomViewDepthProjection_Bool = 2079,
	ETrackedDeviceProperty_Prop_DisplayAvailableFrameRates_Float_Array = 2080,
	ETrackedDeviceProperty_Prop_DisplaySupportsMultipleFramerates_Bool = 2081,
	ETracked_Device_Property_Prop_Display_Color_Mult_বাম_Vector3 = 2082,
	ETracked_Device_Property_Prop_Display_Color_Mult_ডান_Vector3 = 2083,
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
	ETrackedDeviceProperty_Prop_Hmd_SupportsDisplayPortTrainingMode_Bool = 2104,
	ETrackedDeviceProperty_Prop_SupportsRoomViewDirect_Bool = 2105,
	ETrackedDeviceProperty_Prop_SupportsAppThrottling_Bool = 2106,
	ETrackedDeviceProperty_Prop_DSCVersion_Int32 = 2110,
	ETracked_Device_Property_Prop_DSCSlice_গুনতি_Int32 = 2111,
	ETrackedDeviceProperty_Prop_DSCBPPx16_Int32 = 2112,
	ETrackedDeviceProperty_Prop_DriverRequestedMuraCorrectionMode_Int32 = 2200,
	ETracked_Device_Property_Prop_Driver_Requested_Mura_Feather_Inner_বাম_Int32 = 2201,
	ETracked_Device_Property_Prop_Driver_Requested_Mura_Feather_Inner_ডান_Int32 = 2202,
	ETracked_Device_Property_Prop_Driver_Requested_Mura_Feather_Inner_শীর্ষ_Int32 = 2203,
	ETrackedDeviceProperty_Prop_DriverRequestedMuraFeather_InnerBottom_Int32 = 2204,
	ETracked_Device_Property_Prop_Driver_Requested_Mura_Feather_Outer_বাম_Int32 = 2205,
	ETracked_Device_Property_Prop_Driver_Requested_Mura_Feather_Outer_ডান_Int32 = 2206,
	ETracked_Device_Property_Prop_Driver_Requested_Mura_Feather_Outer_শীর্ষ_Int32 = 2207,
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
	ETracked_Device_Property_Prop_Field_Of_View_বাম_Degrees_Float = 4000,
	ETracked_Device_Property_Prop_Field_Of_View_ডান_Degrees_Float = 4001,
	ETracked_Device_Property_Prop_Field_Of_View_শীর্ষ_Degrees_Float = 4002,
	ETrackedDeviceProperty_Prop_FieldOfViewBottomDegrees_Float = 4003,
	ETrackedDeviceProperty_Prop_TrackingRangeMinimumMeters_Float = 4004,
	ETrackedDeviceProperty_Prop_TrackingRangeMaximumMeters_Float = 4005,
	ETrackedDeviceProperty_Prop_ModeLabel_String = 4006,
	ETrackedDeviceProperty_Prop_CanWirelessIdentify_Bool = 4007,
	ETrackedDeviceProperty_Prop_Nonce_Int32 = 4008,
	ETrackedDeviceProperty_Prop_IconPathName_String = 5000,
	ETrackedDeviceProperty_Prop_NamedIconPathDeviceOff_String = 5001,
	ETrackedDeviceProperty_Prop_NamedIconPathDeviceSearching_String = 5002,
	ETrackedDeviceProperty_Prop_NamedIconPathDeviceSearchingAlert_String = 5003,
	ETrackedDeviceProperty_Prop_NamedIconPathDeviceReady_String = 5004,
	ETrackedDeviceProperty_Prop_NamedIconPathDeviceReadyAlert_String = 5005,
	ETrackedDeviceProperty_Prop_NamedIconPathDeviceNotReady_String = 5006,
	ETrackedDeviceProperty_Prop_NamedIconPathDeviceStandby_String = 5007,
	ETracked_Device_Property_Prop_Named_Icon_Path_Device_Alert_নিচের_String = 5008,
	ETrackedDeviceProperty_Prop_NamedIconPathDeviceStandbyAlert_String = 5009,
	ETracked_Device_Property_Prop_Display_Hidden_Area_দ্বিমিক_Start = 5100,
	ETracked_Device_Property_Prop_Display_Hidden_Area_দ্বিমিক_End = 5150,
	ETrackedDeviceProperty_Prop_ParentContainer = 5151,
	ETrackedDeviceProperty_Prop_OverrideContainer_Uint64 = 5152,
	ETrackedDeviceProperty_Prop_UserConfigPath_String = 6000,
	ETrackedDeviceProperty_Prop_InstallPath_String = 6001,
	ETrackedDeviceProperty_Prop_HasDisplayComponent_Bool = 6002,
	ETrackedDeviceProperty_Prop_HasControllerComponent_Bool = 6003,
	ETrackedDeviceProperty_Prop_HasCameraComponent_Bool = 6004,
	ETrackedDeviceProperty_Prop_HasDriverDirectModeComponent_Bool = 6005,
	ETrackedDeviceProperty_Prop_HasVirtualDisplayComponent_Bool = 6006,
	ETrackedDeviceProperty_Prop_HasSpatialAnchorsSupport_Bool = 6007,
	ETrackedDeviceProperty_Prop_ControllerType_String = 7000,
	ETrackedDeviceProperty_Prop_ControllerHandSelectionPriority_Int32 = 7002,
	ETrackedDeviceProperty_Prop_VendorSpecific_Reserved_Start = 10000,
	ETrackedDeviceProperty_Prop_VendorSpecific_Reserved_End = 10999,
	ETrackedDeviceProperty_Prop_TrackedDeviceProperty_Max = 1000000,
} ETrackedDeviceProperty;

প্রকারলেখ গণনা ETrackedPropertyError
{
	ETrackedPropertyError_TrackedProp_Success = 0,
	ETracked_Property_Error_Tracked_Prop_Wrong_তথ্য_Type = 1,
	ETrackedPropertyError_TrackedProp_WrongDeviceClass = 2,
	ETracked_Property_Error_Tracked_Prop_বাফার_Too_Small = 3,
	ETrackedPropertyError_TrackedProp_UnknownProperty = 4,
	ETrackedPropertyError_TrackedProp_InvalidDevice = 5,
	ETrackedPropertyError_TrackedProp_CouldNotContactServer = 6,
	ETracked_Property_Error_Tracked_Prop_মান_Not_Provided_By_Device = 7,
	ETracked_Property_Error_Tracked_Prop_String_Exceeds_Maximum_দৈর্ঘ্য = 8,
	ETrackedPropertyError_TrackedProp_NotYetAvailable = 9,
	ETrackedPropertyError_TrackedProp_PermissionDenied = 10,
	ETrackedPropertyError_TrackedProp_InvalidOperation = 11,
	ETrackedPropertyError_TrackedProp_CannotWriteToWildcards = 12,
	ETrackedPropertyError_TrackedProp_IPCReadFailure = 13,
	ETrackedPropertyError_TrackedProp_OutOfMemory = 14,
	ETrackedPropertyError_TrackedProp_InvalidContainer = 15,
} ETrackedPropertyError;

প্রকারলেখ গণনা EHmdTrackingStyle
{
	EHmdTrackingStyle_HmdTrackingStyle_Unknown = 0,
	EHmdTrackingStyle_HmdTrackingStyle_Lighthouse = 1,
	EHmdTrackingStyle_HmdTrackingStyle_OutsideInCameras = 2,
	EHmdTrackingStyle_HmdTrackingStyle_InsideOutCameras = 3,
} EHmdTrackingStyle;

প্রকারলেখ গণনা EVRSubmitFlags
{
	EVRSubmitFlags_Submit_Default = 0,
	EVRSubmitFlags_Submit_LensDistortionAlreadyApplied = 1,
	EVRSubmit_Flags_Submit_Gl_Render_বাফার = 2,
	EVRSubmitFlags_Submit_Reserved = 4,
	EVRSubmitFlags_Submit_TextureWithPose = 8,
	EVRSubmitFlags_Submit_TextureWithDepth = 16,
	EVRSubmitFlags_Submit_FrameDiscontinuty = 32,
	EVRSubmit_Flags_Submit_Vulkan_Texture_With_Array_তথ্য = 64,
	EVRSubmitFlags_Submit_GlArrayTexture = 128,
	EVRSubmitFlags_Submit_Reserved2 = 32768,
	EVRSubmitFlags_Submit_Reserved3 = 65536,
} EVRSubmitFlags;

প্রকারলেখ গণনা EVRState
{
	EVRState_VRState_Undefined = -1,
	EVRState_VRState_Off = 0,
	EVRState_VRState_Searching = 1,
	EVRState_VRState_Searching_Alert = 2,
	EVRState_VRState_Ready = 3,
	EVRState_VRState_Ready_Alert = 4,
	EVRState_VRState_NotReady = 5,
	EVRState_VRState_Standby = 6,
	EVRState_VRState_Ready_Alert_নিচের = 7,
} EVRState;

প্রকারলেখ গণনা EVREventType
{
	EVREventType_VREvent_None = 0,
	EVREventType_VREvent_TrackedDeviceActivated = 100,
	EVREventType_VREvent_TrackedDeviceDeactivated = 101,
	EVREventType_VREvent_TrackedDeviceUpdated = 102,
	EVREventType_VREvent_TrackedDeviceUserInteractionStarted = 103,
	EVREventType_VREvent_TrackedDeviceUserInteractionEnded = 104,
	EVREventType_VREvent_IpdChanged = 105,
	EVREventType_VREvent_EnterStandbyMode = 106,
	EVREventType_VREvent_LeaveStandbyMode = 107,
	EVREventType_VREvent_TrackedDeviceRoleChanged = 108,
	EVREventType_VREvent_WatchdogWakeUpRequested = 109,
	EVREventType_VREvent_LensDistortionChanged = 110,
	EVREventType_VREvent_PropertyChanged = 111,
	EVREventType_VREvent_WirelessDisconnect = 112,
	EVREventType_VREvent_WirelessReconnect = 113,
	EVREventType_VREvent_ButtonPress = 200,
	EVREventType_VREvent_ButtonUnpress = 201,
	EVREventType_VREvent_ButtonTouch = 202,
	EVREventType_VREvent_ButtonUntouch = 203,
	EVREventType_VREvent_Modal_Cancel = 257,
	EVREventType_VREvent_MouseMove = 300,
	EVREventType_VREvent_MouseButtonDown = 301,
	EVREventType_VREvent_MouseButtonUp = 302,
	EVREventType_VREvent_FocusEnter = 303,
	EVREventType_VREvent_FocusLeave = 304,
	EVREventType_VREvent_ScrollDiscrete = 305,
	EVREventType_VREvent_TouchPadMove = 306,
	EVREventType_VREvent_OverlayFocusChanged = 307,
	EVREventType_VREvent_ReloadOverlays = 308,
	EVREventType_VREvent_ScrollSmooth = 309,
	EVREventType_VREvent_LockMousePosition = 310,
	EVREventType_VREvent_UnlockMousePosition = 311,
	EVREvent_Type_VREvent_প্রবেশ_Focus_Captured = 400,
	EVREvent_Type_VREvent_প্রবেশ_Focus_Released = 401,
	EVREventType_VREvent_SceneApplicationChanged = 404,
	EVREvent_Type_VREvent_প্রবেশ_Focus_Changed = 406,
	EVREventType_VREvent_SceneApplicationUsingWrongGraphicsAdapter = 408,
	EVREventType_VREvent_ActionBindingReloaded = 409,
	EVREventType_VREvent_HideRenderModels = 410,
	EVREventType_VREvent_ShowRenderModels = 411,
	EVREventType_VREvent_SceneApplicationStateChanged = 412,
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
	EVREventType_VREvent_OverlayGamepadFocusLost = 512,
	EVREventType_VREvent_OverlaySharedTextureChanged = 513,
	EVREventType_VREvent_ScreenshotTriggered = 516,
	EVREventType_VREvent_ImageFailed = 517,
	EVREventType_VREvent_DashboardOverlayCreated = 518,
	EVREventType_VREvent_SwitchGamepadFocus = 519,
	EVREventType_VREvent_RequestScreenshot = 520,
	EVREventType_VREvent_ScreenshotTaken = 521,
	EVREventType_VREvent_ScreenshotFailed = 522,
	EVREventType_VREvent_SubmitScreenshotToDashboard = 523,
	EVREventType_VREvent_ScreenshotProgressToDashboard = 524,
	EVREventType_VREvent_PrimaryDashboardDeviceChanged = 525,
	EVREventType_VREvent_RoomViewShown = 526,
	EVREventType_VREvent_RoomViewHidden = 527,
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
	EVREvent_Type_VREvent_Chaperone_তথ্য_Has_Changed = 800,
	EVREventType_VREvent_ChaperoneUniverseHasChanged = 801,
	EVREvent_Type_VREvent_Chaperone_অস্থায়ী_তথ্য_Has_Changed = 802,
	EVREventType_VREvent_ChaperoneSettingsHaveChanged = 803,
	EVREventType_VREvent_SeatedZeroPoseReset = 804,
	EVREventType_VREvent_ChaperoneFlushCache = 805,
	EVREventType_VREvent_ChaperoneRoomSetupStarting = 806,
	EVREventType_VREvent_ChaperoneRoomSetupFinished = 807,
	EVREventType_VREvent_StandingZeroPoseReset = 808,
	EVREventType_VREvent_AudioSettingsHaveChanged = 820,
	EVREventType_VREvent_BackgroundSettingHasChanged = 850,
	EVREventType_VREvent_CameraSettingsHaveChanged = 851,
	EVREventType_VREvent_ReprojectionSettingHasChanged = 852,
	EVREventType_VREvent_ModelSkinSettingsHaveChanged = 853,
	EVREventType_VREvent_EnvironmentSettingsHaveChanged = 854,
	EVREventType_VREvent_PowerSettingsHaveChanged = 855,
	EVREventType_VREvent_EnableHomeAppSettingsHaveChanged = 856,
	EVREventType_VREvent_SteamVRSectionSettingChanged = 857,
	EVREventType_VREvent_LighthouseSectionSettingChanged = 858,
	EVREventType_VREvent_NullSectionSettingChanged = 859,
	EVREventType_VREvent_UserInterfaceSectionSettingChanged = 860,
	EVREventType_VREvent_NotificationsSectionSettingChanged = 861,
	EVREventType_VREvent_KeyboardSectionSettingChanged = 862,
	EVREventType_VREvent_PerfSectionSettingChanged = 863,
	EVREventType_VREvent_DashboardSectionSettingChanged = 864,
	EVREventType_VREvent_WebInterfaceSectionSettingChanged = 865,
	EVREventType_VREvent_TrackersSectionSettingChanged = 866,
	EVREventType_VREvent_LastKnownSectionSettingChanged = 867,
	EVREventType_VREvent_DismissedWarningsSectionSettingChanged = 868,
	EVREventType_VREvent_GpuSpeedSectionSettingChanged = 869,
	EVREventType_VREvent_WindowsMRSectionSettingChanged = 870,
	EVREventType_VREvent_OtherSectionSettingChanged = 871,
	EVREventType_VREvent_StatusUpdate = 900,
	EVREventType_VREvent_WebInterface_InstallDriverCompleted = 950,
	EVREventType_VREvent_MCImageUpdated = 1000,
	EVREventType_VREvent_FirmwareUpdateStarted = 1100,
	EVREventType_VREvent_FirmwareUpdateFinished = 1101,
	EVREventType_VREvent_KeyboardClosed = 1200,
	EVREvent_Type_VREvent_Keyboard_Char_প্রবেশ = 1201,
	EVREventType_VREvent_KeyboardDone = 1202,
	EVREventType_VREvent_ApplicationListUpdated = 1303,
	EVREventType_VREvent_ApplicationMimeTypeLoad = 1304,
	EVREventType_VREvent_ProcessConnected = 1306,
	EVREventType_VREvent_ProcessDisconnected = 1307,
	EVREventType_VREvent_Compositor_ChaperoneBoundsShown = 1410,
	EVREventType_VREvent_Compositor_ChaperoneBoundsHidden = 1411,
	EVREventType_VREvent_Compositor_DisplayDisconnected = 1412,
	EVREventType_VREvent_Compositor_DisplayReconnected = 1413,
	EVREventType_VREvent_Compositor_HDCPError = 1414,
	EVREventType_VREvent_Compositor_ApplicationNotResponding = 1415,
	EVREventType_VREvent_Compositor_ApplicationResumed = 1416,
	EVREventType_VREvent_Compositor_OutOfVideoMemory = 1417,
	EVREventType_VREvent_Compositor_DisplayModeNotSupported = 1418,
	EVREventType_VREvent_Compositor_StageOverrideReady = 1419,
	EVREventType_VREvent_Compositor_RequestDisconnectReconnect = 1420,
	EVREventType_VREvent_TrackedCamera_StartVideoStream = 1500,
	EVREventType_VREvent_TrackedCamera_StopVideoStream = 1501,
	EVREventType_VREvent_TrackedCamera_PauseVideoStream = 1502,
	EVREventType_VREvent_TrackedCamera_ResumeVideoStream = 1503,
	EVREventType_VREvent_TrackedCamera_EditingSurface = 1550,
	EVREventType_VREvent_PerformanceTest_EnableCapture = 1600,
	EVREventType_VREvent_PerformanceTest_DisableCapture = 1601,
	EVREventType_VREvent_PerformanceTest_FidelityLevel = 1602,
	EVREventType_VREvent_MessageOverlay_Closed = 1650,
	EVREventType_VREvent_MessageOverlayCloseRequested = 1651,
	EVREvent_Type_VREvent_প্রবেশ_Haptic_Vibration = 1700,
	EVREvent_Type_VREvent_প্রবেশ_Binding_Load_Failed = 1701,
	EVREvent_Type_VREvent_প্রবেশ_Binding_Load_Successful = 1702,
	EVREvent_Type_VREvent_প্রবেশ_Action_Manifest_Reloaded = 1703,
	EVREvent_Type_VREvent_প্রবেশ_Action_Manifest_Load_Failed = 1704,
	EVREvent_Type_VREvent_প্রবেশ_Progress_Update = 1705,
	EVREvent_Type_VREvent_প্রবেশ_Tracker_Activated = 1706,
	EVREvent_Type_VREvent_প্রবেশ_Bindings_Updated = 1707,
	EVREvent_Type_VREvent_প্রবেশ_Binding_Subscription_Changed = 1708,
	EVREventType_VREvent_SpatialAnchors_PoseUpdated = 1800,
	EVREventType_VREvent_SpatialAnchors_DescriptorUpdated = 1801,
	EVREventType_VREvent_SpatialAnchors_RequestPoseUpdate = 1802,
	EVREventType_VREvent_SpatialAnchors_RequestDescriptorUpdate = 1803,
	EVREventType_VREvent_SystemReport_Started = 1900,
	EVREventType_VREvent_Monitor_ShowHeadsetView = 2000,
	EVREventType_VREvent_Monitor_HideHeadsetView = 2001,
	EVREventType_VREvent_VendorSpecific_Reserved_Start = 10000,
	EVREventType_VREvent_VendorSpecific_Reserved_End = 19999,
} EVREventType;

প্রকারলেখ গণনা EDeviceActivityLevel
{
	EDeviceActivityLevel_k_EDeviceActivityLevel_Unknown = -1,
	EDeviceActivityLevel_k_EDeviceActivityLevel_Idle = 0,
	EDeviceActivityLevel_k_EDeviceActivityLevel_UserInteraction = 1,
	EDeviceActivityLevel_k_EDeviceActivityLevel_UserInteraction_Timeout = 2,
	EDeviceActivityLevel_k_EDeviceActivityLevel_Standby = 3,
	EDeviceActivityLevel_k_EDeviceActivityLevel_Idle_Timeout = 4,
} EDeviceActivityLevel;

প্রকারলেখ গণনা EVRButtonId
{
	EVRButtonId_k_EButton_System = 0,
	EVRButtonId_k_EButton_ApplicationMenu = 1,
	EVRButtonId_k_EButton_Grip = 2,
	EVRButton_Id_k_EButton_DPad_বাম = 3,
	EVRButtonId_k_EButton_DPad_Up = 4,
	EVRButton_Id_k_EButton_DPad_ডান = 5,
	EVRButtonId_k_EButton_DPad_Down = 6,
	EVRButtonId_k_EButton_A = 7,
	EVRButtonId_k_EButton_ProximitySensor = 31,
	EVRButtonId_k_EButton_Axis0 = 32,
	EVRButtonId_k_EButton_Axis1 = 33,
	EVRButtonId_k_EButton_Axis2 = 34,
	EVRButtonId_k_EButton_Axis3 = 35,
	EVRButtonId_k_EButton_Axis4 = 36,
	EVRButtonId_k_EButton_SteamVR_Touchpad = 32,
	EVRButtonId_k_EButton_SteamVR_Trigger = 33,
	EVRButtonId_k_EButton_Dashboard_Back = 2,
	EVRButton_Id_k_EButton_সূচক_Controller_A = 2,
	EVRButton_Id_k_EButton_সূচক_Controller_B = 1,
	EVRButton_Id_k_EButton_সূচক_Controller_Joy_Stick = 35,
	EVRButtonId_k_EButton_Max = 64,
} EVRButtonId;

প্রকারলেখ গণনা EVRMouseButton
{
	EVRMouse_Button_VRMouse_Button_বাম = 1,
	EVRMouse_Button_VRMouse_Button_ডান = 2,
	EVRMouse_Button_VRMouse_Button_মধ্য = 4,
} EVRMouseButton;

প্রকারলেখ গণনা EShowUIType
{
	EShowUIType_ShowUI_ControllerBinding = 0,
	EShowUIType_ShowUI_ManageTrackers = 1,
	EShowUIType_ShowUI_Pairing = 3,
	EShowUIType_ShowUI_Settings = 4,
	EShowUIType_ShowUI_DebugCommands = 5,
	EShowUIType_ShowUI_FullControllerBinding = 6,
	EShowUIType_ShowUI_ManageDrivers = 7,
} EShowUIType;

প্রকারলেখ গণনা EHDCPError
{
	EHDCPError_HDCPError_None = 0,
	EHDCPError_HDCPError_LinkLost = 1,
	EHDCPError_HDCPError_Tampered = 2,
	EHDCPError_HDCPError_DeviceRevoked = 3,
	EHDCPError_HDCPError_Unknown = 4,
} EHDCPError;

প্রকারলেখ গণনা EVRComponentProperty
{
	EVRComponentProperty_VRComponentProperty_IsStatic = 1,
	EVRComponentProperty_VRComponentProperty_IsVisible = 2,
	EVRComponentProperty_VRComponentProperty_IsTouched = 4,
	EVRComponentProperty_VRComponentProperty_IsPressed = 8,
	EVRComponentProperty_VRComponentProperty_IsScrolled = 16,
	EVRComponentProperty_VRComponentProperty_IsHighlighted = 32,
} EVRComponentProperty;

প্রকারলেখ গণনা EVRInputError
{
	EVRInputError_VRInputError_None = 0,
	EVRInputError_VRInputError_NameNotFound = 1,
	EVRInputError_VRInputError_WrongType = 2,
	EVRInputError_VRInputError_InvalidHandle = 3,
	EVRInputError_VRInputError_InvalidParam = 4,
	EVRInputError_VRInputError_NoSteam = 5,
	EVRInputError_VRInputError_MaxCapacityReached = 6,
	EVRInputError_VRInputError_IPCError = 7,
	EVRInputError_VRInputError_NoActiveActionSet = 8,
	EVRInputError_VRInputError_InvalidDevice = 9,
	EVRInputError_VRInputError_InvalidSkeleton = 10,
	EVRInput_Error_VRInput_Error_Invalid_Bone_গুনতি = 11,
	EVRInput_Error_VRInput_Error_Invalid_Compressed_তথ্য = 12,
	EVRInput_Error_VRInput_Error_No_তথ্য = 13,
	EVRInput_Error_VRInput_Error_বাফার_Too_Small = 14,
	EVRInputError_VRInputError_MismatchedActionManifest = 15,
	EVRInput_Error_VRInput_Error_Missing_Skeleton_তথ্য = 16,
	EVRInput_Error_VRInput_Error_Invalid_Bone_সূচক = 17,
	EVRInputError_VRInputError_InvalidPriority = 18,
	EVRInputError_VRInputError_PermissionDenied = 19,
	EVRInputError_VRInputError_InvalidRenderModel = 20,
} EVRInputError;

প্রকারলেখ গণনা EVRSpatialAnchorError
{
	EVRSpatialAnchorError_VRSpatialAnchorError_Success = 0,
	EVRSpatialAnchorError_VRSpatialAnchorError_Internal = 1,
	EVRSpatialAnchorError_VRSpatialAnchorError_UnknownHandle = 2,
	EVRSpatialAnchorError_VRSpatialAnchorError_ArrayTooSmall = 3,
	EVRSpatialAnchorError_VRSpatialAnchorError_InvalidDescriptorChar = 4,
	EVRSpatialAnchorError_VRSpatialAnchorError_NotYetAvailable = 5,
	EVRSpatialAnchorError_VRSpatialAnchorError_NotAvailableInThisUniverse = 6,
	EVRSpatialAnchorError_VRSpatialAnchorError_PermanentlyUnavailable = 7,
	EVRSpatialAnchorError_VRSpatialAnchorError_WrongDriver = 8,
	EVRSpatialAnchorError_VRSpatialAnchorError_DescriptorTooLong = 9,
	EVRSpatialAnchorError_VRSpatialAnchorError_Unknown = 10,
	EVRSpatialAnchorError_VRSpatialAnchorError_NoRoomCalibration = 11,
	EVRSpatialAnchorError_VRSpatialAnchorError_InvalidArgument = 12,
	EVRSpatialAnchorError_VRSpatialAnchorError_UnknownDriver = 13,
} EVRSpatialAnchorError;

প্রকারলেখ গণনা EHiddenAreaMeshType
{
	EHiddenAreaMeshType_k_eHiddenAreaMesh_Standard = 0,
	EHiddenAreaMeshType_k_eHiddenAreaMesh_Inverse = 1,
	EHidden_Area_Mesh_Type_k_e_Hidden_Area_Mesh_সারি_Loop = 2,
	EHiddenAreaMeshType_k_eHiddenAreaMesh_Max = 3,
} EHiddenAreaMeshType;

প্রকারলেখ গণনা EVRControllerAxisType
{
	EVRControllerAxisType_k_eControllerAxis_None = 0,
	EVRControllerAxisType_k_eControllerAxis_TrackPad = 1,
	EVRControllerAxisType_k_eControllerAxis_Joystick = 2,
	EVRControllerAxisType_k_eControllerAxis_Trigger = 3,
} EVRControllerAxisType;

প্রকারলেখ গণনা EVRControllerEventOutputType
{
	EVRControllerEventOutputType_ControllerEventOutput_OSEvents = 0,
	EVRControllerEventOutputType_ControllerEventOutput_VREvents = 1,
} EVRControllerEventOutputType;

প্রকারলেখ গণনা ECollisionBoundsStyle
{
	ECollisionBoundsStyle_COLLISION_BOUNDS_STYLE_BEGINNER = 0,
	ECollisionBoundsStyle_COLLISION_BOUNDS_STYLE_INTERMEDIATE = 1,
	ECollisionBoundsStyle_COLLISION_BOUNDS_STYLE_SQUARES = 2,
	ECollisionBoundsStyle_COLLISION_BOUNDS_STYLE_ADVANCED = 3,
	ECollisionBoundsStyle_COLLISION_BOUNDS_STYLE_NONE = 4,
	ECollision_Bounds_Style_COLLISION_BOUNDS_STYLE_গুনতি = 5,
} ECollisionBoundsStyle;

প্রকারলেখ গণনা EVROverlayError
{
	EVROverlayError_VROverlayError_None = 0,
	EVROverlayError_VROverlayError_UnknownOverlay = 10,
	EVROverlayError_VROverlayError_InvalidHandle = 11,
	EVROverlayError_VROverlayError_PermissionDenied = 12,
	EVROverlayError_VROverlayError_OverlayLimitExceeded = 13,
	EVROverlayError_VROverlayError_WrongVisibilityType = 14,
	EVROverlay_Error_VROverlay_Error_চাবি_Too_Long = 15,
	EVROverlayError_VROverlayError_NameTooLong = 16,
	EVROverlay_Error_VROverlay_Error_চাবি_In_Use = 17,
	EVROverlayError_VROverlayError_WrongTransformType = 18,
	EVROverlayError_VROverlayError_InvalidTrackedDevice = 19,
	EVROverlayError_VROverlayError_InvalidParameter = 20,
	EVROverlayError_VROverlayError_ThumbnailCantBeDestroyed = 21,
	EVROverlayError_VROverlayError_ArrayTooSmall = 22,
	EVROverlayError_VROverlayError_RequestFailed = 23,
	EVROverlayError_VROverlayError_InvalidTexture = 24,
	EVROverlayError_VROverlayError_UnableToLoadFile = 25,
	EVROverlayError_VROverlayError_KeyboardAlreadyInUse = 26,
	EVROverlayError_VROverlayError_NoNeighbor = 27,
	EVROverlayError_VROverlayError_TooManyMaskPrimitives = 29,
	EVROverlayError_VROverlayError_BadMaskPrimitive = 30,
	EVROverlayError_VROverlayError_TextureAlreadyLocked = 31,
	EVROverlayError_VROverlayError_TextureLockCapacityReached = 32,
	EVROverlayError_VROverlayError_TextureNotLocked = 33,
	EVROverlayError_VROverlayError_TimedOut = 34,
} EVROverlayError;

প্রকারলেখ গণনা EVRApplicationType
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
	EVRApplicationType_VRApplication_RoomView = 13,
	EVRApplicationType_VRApplication_Max = 14,
} EVRApplicationType;

প্রকারলেখ গণনা EVRFirmwareError
{
	EVRFirmwareError_VRFirmwareError_None = 0,
	EVRFirmwareError_VRFirmwareError_Success = 1,
	EVRFirmwareError_VRFirmwareError_Fail = 2,
} EVRFirmwareError;

প্রকারলেখ গণনা EVRNotificationError
{
	EVRNotificationError_VRNotificationError_OK = 0,
	EVRNotificationError_VRNotificationError_InvalidNotificationId = 100,
	EVRNotificationError_VRNotificationError_NotificationQueueFull = 101,
	EVRNotificationError_VRNotificationError_InvalidOverlayHandle = 102,
	EVRNotification_Error_VRNotification_Error_System_With_User_মান_Already_Exists = 103,
} EVRNotificationError;

প্রকারলেখ গণনা EVRSkeletalMotionRange
{
	EVRSkeletalMotionRange_VRSkeletalMotionRange_WithController = 0,
	EVRSkeletalMotionRange_VRSkeletalMotionRange_WithoutController = 1,
} EVRSkeletalMotionRange;

প্রকারলেখ গণনা EVRSkeletalTrackingLevel
{
	EVRSkeletalTrackingLevel_VRSkeletalTracking_Estimated = 0,
	EVRSkeletalTrackingLevel_VRSkeletalTracking_Partial = 1,
	EVRSkeletalTrackingLevel_VRSkeletalTracking_Full = 2,
	EVRSkeletal_Tracking_Level_VRSkeletal_Tracking_Level_গুনতি = 3,
	EVRSkeletalTrackingLevel_VRSkeletalTrackingLevel_Max = 2,
} EVRSkeletalTrackingLevel;

প্রকারলেখ গণনা EVRInitError
{
	EVRInitError_VRInitError_None = 0,
	EVRInitError_VRInitError_Unknown = 1,
	EVRInitError_VRInitError_Init_InstallationNotFound = 100,
	EVRInitError_VRInitError_Init_InstallationCorrupt = 101,
	EVRInitError_VRInitError_Init_VRClientDLLNotFound = 102,
	EVRInitError_VRInitError_Init_FileNotFound = 103,
	EVRInitError_VRInitError_Init_FactoryNotFound = 104,
	EVRInitError_VRInitError_Init_InterfaceNotFound = 105,
	EVRInitError_VRInitError_Init_InvalidInterface = 106,
	EVRInitError_VRInitError_Init_UserConfigDirectoryInvalid = 107,
	EVRInitError_VRInitError_Init_HmdNotFound = 108,
	EVRInitError_VRInitError_Init_NotInitialized = 109,
	EVRInitError_VRInitError_Init_PathRegistryNotFound = 110,
	EVRInitError_VRInitError_Init_NoConfigPath = 111,
	EVRInitError_VRInitError_Init_NoLogPath = 112,
	EVRInitError_VRInitError_Init_PathRegistryNotWritable = 113,
	EVRInitError_VRInitError_Init_AppInfoInitFailed = 114,
	EVRInitError_VRInitError_Init_Retry = 115,
	EVRInitError_VRInitError_Init_InitCanceledByUser = 116,
	EVRInitError_VRInitError_Init_AnotherAppLaunching = 117,
	EVRInitError_VRInitError_Init_SettingsInitFailed = 118,
	EVRInitError_VRInitError_Init_ShuttingDown = 119,
	EVRInitError_VRInitError_Init_TooManyObjects = 120,
	EVRInitError_VRInitError_Init_NoServerForBackgroundApp = 121,
	EVRInitError_VRInitError_Init_NotSupportedWithCompositor = 122,
	EVRInitError_VRInitError_Init_NotAvailableToUtilityApps = 123,
	EVRInitError_VRInitError_Init_Internal = 124,
	EVRInitError_VRInitError_Init_HmdDriverIdIsNone = 125,
	EVRInitError_VRInitError_Init_HmdNotFoundPresenceFailed = 126,
	EVRInitError_VRInitError_Init_VRMonitorNotFound = 127,
	EVRInitError_VRInitError_Init_VRMonitorStartupFailed = 128,
	EVRInit_Error_VRInit_Error_Init_নিচের_Power_Watchdog_Not_Supported = 129,
	EVRInitError_VRInitError_Init_InvalidApplicationType = 130,
	EVRInitError_VRInitError_Init_NotAvailableToWatchdogApps = 131,
	EVRInitError_VRInitError_Init_WatchdogDisabledInSettings = 132,
	EVRInitError_VRInitError_Init_VRDashboardNotFound = 133,
	EVRInitError_VRInitError_Init_VRDashboardStartupFailed = 134,
	EVRInitError_VRInitError_Init_VRHomeNotFound = 135,
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
	EVRInitError_VRInitError_Init_PrismStartupTimedOut = 152,
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
	EVRInitError_VRInitError_Init_VRDashboardPathFailure = 167,
	EVRInitError_VRInitError_Driver_Failed = 200,
	EVRInitError_VRInitError_Driver_Unknown = 201,
	EVRInitError_VRInitError_Driver_HmdUnknown = 202,
	EVRInitError_VRInitError_Driver_NotLoaded = 203,
	EVRInitError_VRInitError_Driver_RuntimeOutOfDate = 204,
	EVRInitError_VRInitError_Driver_HmdInUse = 205,
	EVRInitError_VRInitError_Driver_NotCalibrated = 206,
	EVRInitError_VRInitError_Driver_CalibrationInvalid = 207,
	EVRInitError_VRInitError_Driver_HmdDisplayNotFound = 208,
	EVRInitError_VRInitError_Driver_TrackedDeviceInterfaceUnknown = 209,
	EVRInitError_VRInitError_Driver_HmdDriverIdOutOfBounds = 211,
	EVRInitError_VRInitError_Driver_HmdDisplayMirrored = 212,
	EVRInitError_VRInitError_Driver_HmdDisplayNotFoundLaptop = 213,
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
	EVRInitError_VRInitError_IPC_ConnectFailedAfterMultipleAttempts = 308,
	EVRInitError_VRInitError_IPC_ConnectFailedAfterTargetExited = 309,
	EVRInitError_VRInitError_IPC_NamespaceUnavailable = 310,
	EVRInitError_VRInitError_Compositor_Failed = 400,
	EVRInitError_VRInitError_Compositor_D3D11HardwareRequired = 401,
	EVRInitError_VRInitError_Compositor_FirmwareRequiresUpdate = 402,
	EVRInitError_VRInitError_Compositor_OverlayInitFailed = 403,
	EVRInitError_VRInitError_Compositor_ScreenshotsInitFailed = 404,
	EVRInitError_VRInitError_Compositor_UnableToCreateDevice = 405,
	EVRInitError_VRInitError_Compositor_SharedStateIsNull = 406,
	EVRInitError_VRInitError_Compositor_NotificationManagerIsNull = 407,
	EVRInitError_VRInitError_Compositor_ResourceManagerClientIsNull = 408,
	EVRInitError_VRInitError_Compositor_MessageOverlaySharedStateInitFailure = 409,
	EVRInitError_VRInitError_Compositor_PropertiesInterfaceIsNull = 410,
	EVRInitError_VRInitError_Compositor_CreateFullscreenWindowFailed = 411,
	EVRInitError_VRInitError_Compositor_SettingsInterfaceIsNull = 412,
	EVRInitError_VRInitError_Compositor_FailedToShowWindow = 413,
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
	EVRInitError_VRInitError_Compositor_FailedToFindDisplayMode = 425,
	EVRInitError_VRInitError_Compositor_FailedToCreateSwapChain = 426,
	EVRInit_Error_VRInit_Error_Compositor_Failed_To_Get_Back_বাফার = 427,
	EVRInitError_VRInitError_Compositor_FailedToCreateRenderTarget = 428,
	EVRInitError_VRInitError_Compositor_FailedToCreateDXGI2SwapChain = 429,
	EVRInit_Error_VRInit_Error_Compositor_Failedto_Get_DXGI2_Back_বাফার = 430,
	EVRInitError_VRInitError_Compositor_FailedToCreateDXGI2RenderTarget = 431,
	EVRInitError_VRInitError_Compositor_FailedToGetDXGIDeviceInterface = 432,
	EVRInitError_VRInitError_Compositor_SelectDisplayMode = 433,
	EVRInitError_VRInitError_Compositor_FailedToCreateNvAPIRenderTargets = 434,
	EVRInitError_VRInitError_Compositor_NvAPISetDisplayMode = 435,
	EVRInitError_VRInitError_Compositor_FailedToCreateDirectModeDisplay = 436,
	EVRInitError_VRInitError_Compositor_InvalidHmdPropertyContainer = 437,
	EVRInitError_VRInitError_Compositor_UpdateDisplayFrequency = 438,
	EVRInitError_VRInitError_Compositor_CreateRasterizerState = 439,
	EVRInitError_VRInitError_Compositor_CreateWireframeRasterizerState = 440,
	EVRInitError_VRInitError_Compositor_CreateSamplerState = 441,
	EVRInitError_VRInitError_Compositor_CreateClampToBorderSamplerState = 442,
	EVRInitError_VRInitError_Compositor_CreateAnisoSamplerState = 443,
	EVRInitError_VRInitError_Compositor_CreateOverlaySamplerState = 444,
	EVRInitError_VRInitError_Compositor_CreatePanoramaSamplerState = 445,
	EVRInitError_VRInitError_Compositor_CreateFontSamplerState = 446,
	EVRInitError_VRInitError_Compositor_CreateNoBlendState = 447,
	EVRInitError_VRInitError_Compositor_CreateBlendState = 448,
	EVRInitError_VRInitError_Compositor_CreateAlphaBlendState = 449,
	EVRInitError_VRInitError_Compositor_CreateBlendStateMaskR = 450,
	EVRInitError_VRInitError_Compositor_CreateBlendStateMaskG = 451,
	EVRInitError_VRInitError_Compositor_CreateBlendStateMaskB = 452,
	EVRInitError_VRInitError_Compositor_CreateDepthStencilState = 453,
	EVRInitError_VRInitError_Compositor_CreateDepthStencilStateNoWrite = 454,
	EVRInitError_VRInitError_Compositor_CreateDepthStencilStateNoDepth = 455,
	EVRInitError_VRInitError_Compositor_CreateFlushTexture = 456,
	EVRInitError_VRInitError_Compositor_CreateDistortionSurfaces = 457,
	EVRInit_Error_VRInit_Error_Compositor_Create_Constant_বাফার = 458,
	EVRInit_Error_VRInit_Error_Compositor_Create_Hmd_Pose_Constant_বাফার = 459,
	EVRInit_Error_VRInit_Error_Compositor_Create_Hmd_Pose_Staging_Constant_বাফার = 460,
	EVRInit_Error_VRInit_Error_Compositor_Create_Shared_Frame_Info_Constant_বাফার = 461,
	EVRInit_Error_VRInit_Error_Compositor_Create_Overlay_Constant_বাফার = 462,
	EVRInit_Error_VRInit_Error_Compositor_Create_Scene_Texture_সূচক_Constant_বাফার = 463,
	EVRInit_Error_VRInit_Error_Compositor_Create_Readable_Scene_Texture_সূচক_Constant_বাফার = 464,
	EVRInit_Error_VRInit_Error_Compositor_Create_Layer_Graphics_Texture_সূচক_Constant_বাফার = 465,
	EVRInit_Error_VRInit_Error_Compositor_Create_Layer_Compute_Texture_সূচক_Constant_বাফার = 466,
	EVRInit_Error_VRInit_Error_Compositor_Create_Layer_Compute_Scene_Texture_সূচক_Constant_বাফার = 467,
	EVRInit_Error_VRInit_Error_Compositor_Create_Compute_Hmd_Pose_Constant_বাফার = 468,
	EVRInit_Error_VRInit_Error_Compositor_Create_Geom_Constant_বাফার = 469,
	EVRInit_Error_VRInit_Error_Compositor_Create_Panel_Mask_Constant_বাফার = 470,
	EVRInitError_VRInitError_Compositor_CreatePixelSimUBO = 471,
	EVRInitError_VRInitError_Compositor_CreateMSAARenderTextures = 472,
	EVRInitError_VRInitError_Compositor_CreateResolveRenderTextures = 473,
	EVRInitError_VRInitError_Compositor_CreateComputeResolveRenderTextures = 474,
	EVRInitError_VRInitError_Compositor_CreateDriverDirectModeResolveTextures = 475,
	EVRInitError_VRInitError_Compositor_OpenDriverDirectModeResolveTextures = 476,
	EVRInitError_VRInitError_Compositor_CreateFallbackSyncTexture = 477,
	EVRInitError_VRInitError_Compositor_ShareFallbackSyncTexture = 478,
	EVRInit_Error_VRInit_Error_Compositor_Create_Overlay_সূচক_বাফার = 479,
	EVRInit_Error_VRInit_Error_Compositor_Create_Overlay_Vertex_বাফার = 480,
	EVRInit_Error_VRInit_Error_Compositor_Create_Text_Vertex_বাফার = 481,
	EVRInit_Error_VRInit_Error_Compositor_Create_Text_সূচক_বাফার = 482,
	EVRInitError_VRInitError_Compositor_CreateMirrorTextures = 483,
	EVRInitError_VRInitError_Compositor_CreateLastFrameRenderTexture = 484,
	EVRInitError_VRInitError_Compositor_CreateMirrorOverlay = 485,
	EVRInitError_VRInitError_Compositor_FailedToCreateVirtualDisplayBackbuffer = 486,
	EVRInitError_VRInitError_Compositor_DisplayModeNotSupported = 487,
	EVRInitError_VRInitError_Compositor_CreateOverlayInvalidCall = 488,
	EVRInitError_VRInitError_Compositor_CreateOverlayAlreadyInitialized = 489,
	EVRInitError_VRInitError_Compositor_FailedToCreateMailbox = 490,
	EVRInitError_VRInitError_Compositor_WindowInterfaceIsNull = 491,
	EVRInitError_VRInitError_Compositor_SystemLayerCreateInstance = 492,
	EVRInitError_VRInitError_Compositor_SystemLayerCreateSession = 493,
	EVRInitError_VRInitError_Compoistor_CreateInverseDistortUVs = 494,
	EVRInitError_VRInitError_Compoistor_CreateBackbufferDepth = 495,
	EVRInitError_VRInitError_VendorSpecific_UnableToConnectToOculusRuntime = 1000,
	EVRInitError_VRInitError_VendorSpecific_WindowsNotInDevMode = 1001,
	EVRInitError_VRInitError_VendorSpecific_OculusLinkNotEnabled = 1002,
	EVRInitError_VRInitError_VendorSpecific_HmdFound_CantOpenDevice = 1101,
	EVRInitError_VRInitError_VendorSpecific_HmdFound_UnableToRequestConfigStart = 1102,
	EVRInitError_VRInitError_VendorSpecific_HmdFound_NoStoredConfig = 1103,
	EVRInitError_VRInitError_VendorSpecific_HmdFound_ConfigTooBig = 1104,
	EVRInitError_VRInitError_VendorSpecific_HmdFound_ConfigTooSmall = 1105,
	EVRInitError_VRInitError_VendorSpecific_HmdFound_UnableToInitZLib = 1106,
	EVRInitError_VRInitError_VendorSpecific_HmdFound_CantReadFirmwareVersion = 1107,
	EVRInit_Error_VRInit_Error_Vendor_Specific_Hmd_Found_Unable_To_Send_User_তথ্য_Start = 1108,
	EVRInit_Error_VRInit_Error_Vendor_Specific_Hmd_Found_Unable_To_Get_User_তথ্য_Start = 1109,
	EVRInit_Error_VRInit_Error_Vendor_Specific_Hmd_Found_Unable_To_Get_User_তথ্য_পরবর্তী = 1110,
	EVRInit_Error_VRInit_Error_Vendor_Specific_Hmd_Found_User_তথ্য_Address_Range = 1111,
	EVRInit_Error_VRInit_Error_Vendor_Specific_Hmd_Found_User_তথ্য_Error = 1112,
	EVRInitError_VRInitError_VendorSpecific_HmdFound_ConfigFailedSanityCheck = 1113,
	EVRInitError_VRInitError_VendorSpecific_OculusRuntimeBadInstall = 1114,
	EVRInitError_VRInitError_VendorSpecific_HmdFound_UnexpectedConfiguration_1 = 1115,
	EVRInitError_VRInitError_Steam_SteamInstallationNotFound = 2000,
	EVRInitError_VRInitError_LastError = 2001,
} EVRInitError;

প্রকারলেখ গণনা EVRScreenshotType
{
	EVRScreenshotType_VRScreenshotType_None = 0,
	EVRScreenshotType_VRScreenshotType_Mono = 1,
	EVRScreenshotType_VRScreenshotType_Stereo = 2,
	EVRScreenshotType_VRScreenshotType_Cubemap = 3,
	EVRScreenshotType_VRScreenshotType_MonoPanorama = 4,
	EVRScreenshotType_VRScreenshotType_StereoPanorama = 5,
} EVRScreenshotType;

প্রকারলেখ গণনা EVRScreenshotPropertyFilenames
{
	EVRScreenshotPropertyFilenames_VRScreenshotPropertyFilenames_Preview = 0,
	EVRScreenshotPropertyFilenames_VRScreenshotPropertyFilenames_VR = 1,
} EVRScreenshotPropertyFilenames;

প্রকারলেখ গণনা EVRTrackedCameraError
{
	EVRTrackedCameraError_VRTrackedCameraError_None = 0,
	EVRTrackedCameraError_VRTrackedCameraError_OperationFailed = 100,
	EVRTrackedCameraError_VRTrackedCameraError_InvalidHandle = 101,
	EVRTrackedCameraError_VRTrackedCameraError_InvalidFrameHeaderVersion = 102,
	EVRTrackedCameraError_VRTrackedCameraError_OutOfHandles = 103,
	EVRTrackedCameraError_VRTrackedCameraError_IPCFailure = 104,
	EVRTrackedCameraError_VRTrackedCameraError_NotSupportedForThisDevice = 105,
	EVRTrackedCameraError_VRTrackedCameraError_SharedMemoryFailure = 106,
	EVRTrackedCameraError_VRTrackedCameraError_FrameBufferingFailure = 107,
	EVRTrackedCameraError_VRTrackedCameraError_StreamSetupFailure = 108,
	EVRTrackedCameraError_VRTrackedCameraError_InvalidGLTextureId = 109,
	EVRTrackedCameraError_VRTrackedCameraError_InvalidSharedTextureHandle = 110,
	EVRTrackedCameraError_VRTrackedCameraError_FailedToGetGLTextureId = 111,
	EVRTrackedCameraError_VRTrackedCameraError_SharedTextureFailure = 112,
	EVRTrackedCameraError_VRTrackedCameraError_NoFrameAvailable = 113,
	EVRTrackedCameraError_VRTrackedCameraError_InvalidArgument = 114,
	EVRTracked_Camera_Error_VRTracked_Camera_Error_Invalid_Frame_বাফার_আকার = 115,
} EVRTrackedCameraError;

প্রকারলেখ গণনা EVRTrackedCameraFrameLayout
{
	EVRTrackedCameraFrameLayout_Mono = 1,
	EVRTrackedCameraFrameLayout_Stereo = 2,
	EVRTrackedCameraFrameLayout_VerticalLayout = 16,
	EVRTrackedCameraFrameLayout_HorizontalLayout = 32,
} EVRTrackedCameraFrameLayout;

প্রকারলেখ গণনা EVRTrackedCameraFrameType
{
	EVRTrackedCameraFrameType_VRTrackedCameraFrameType_Distorted = 0,
	EVRTrackedCameraFrameType_VRTrackedCameraFrameType_Undistorted = 1,
	EVRTrackedCameraFrameType_VRTrackedCameraFrameType_MaximumUndistorted = 2,
	EVRTrackedCameraFrameType_MAX_CAMERA_FRAME_TYPES = 3,
} EVRTrackedCameraFrameType;

প্রকারলেখ গণনা EVRDistortionFunctionType
{
	EVRDistortionFunctionType_VRDistortionFunctionType_None = 0,
	EVRDistortionFunctionType_VRDistortionFunctionType_FTheta = 1,
	EVRDistortionFunctionType_VRDistortionFunctionType_Extended_FTheta = 2,
	EVRDistortionFunctionType_MAX_DISTORTION_FUNCTION_TYPES = 3,
} EVRDistortionFunctionType;

প্রকারলেখ গণনা EVSync
{
	EVSync_VSync_None = 0,
	EVSync_VSync_WaitRender = 1,
	EVSync_VSync_NoWaitRender = 2,
} EVSync;

প্রকারলেখ গণনা EVRMuraCorrectionMode
{
	EVRMuraCorrectionMode_Default = 0,
	EVRMuraCorrectionMode_NoCorrection = 1,
} EVRMuraCorrectionMode;

প্রকারলেখ গণনা Imu_OffScaleFlags
{
	Imu_OffScaleFlags_OffScale_AccelX = 1,
	Imu_OffScaleFlags_OffScale_AccelY = 2,
	Imu_OffScaleFlags_OffScale_AccelZ = 4,
	Imu_OffScaleFlags_OffScale_GyroX = 8,
	Imu_OffScaleFlags_OffScale_GyroY = 16,
	Imu_OffScaleFlags_OffScale_GyroZ = 32,
} Imu_OffScaleFlags;

প্রকারলেখ গণনা EVRApplicationError
{
	EVRApplicationError_VRApplicationError_None = 0,
	EVRApplication_Error_VRApplication_Error_App_চাবি_Already_Exists = 100,
	EVRApplicationError_VRApplicationError_NoManifest = 101,
	EVRApplicationError_VRApplicationError_NoApplication = 102,
	EVRApplication_Error_VRApplication_Error_Invalid_সূচক = 103,
	EVRApplicationError_VRApplicationError_UnknownApplication = 104,
	EVRApplicationError_VRApplicationError_IPCFailed = 105,
	EVRApplicationError_VRApplicationError_ApplicationAlreadyRunning = 106,
	EVRApplicationError_VRApplicationError_InvalidManifest = 107,
	EVRApplicationError_VRApplicationError_InvalidApplication = 108,
	EVRApplicationError_VRApplicationError_LaunchFailed = 109,
	EVRApplicationError_VRApplicationError_ApplicationAlreadyStarting = 110,
	EVRApplicationError_VRApplicationError_LaunchInProgress = 111,
	EVRApplicationError_VRApplicationError_OldApplicationQuitting = 112,
	EVRApplicationError_VRApplicationError_TransitionAborted = 113,
	EVRApplicationError_VRApplicationError_IsTemplate = 114,
	EVRApplicationError_VRApplicationError_SteamVRIsExiting = 115,
	EVRApplication_Error_VRApplication_Error_বাফার_Too_Small = 200,
	EVRApplicationError_VRApplicationError_PropertyNotSet = 201,
	EVRApplicationError_VRApplicationError_UnknownProperty = 202,
	EVRApplicationError_VRApplicationError_InvalidParameter = 203,
	EVRApplicationError_VRApplicationError_NotImplemented = 300,
} EVRApplicationError;

প্রকারলেখ গণনা EVRApplicationProperty
{
	EVRApplicationProperty_VRApplicationProperty_Name_String = 0,
	EVRApplicationProperty_VRApplicationProperty_LaunchType_String = 11,
	EVRApplicationProperty_VRApplicationProperty_WorkingDirectory_String = 12,
	EVRApplication_Property_VRApplication_Property_দ্বিমিক_Path_String = 13,
	EVRApplicationProperty_VRApplicationProperty_Arguments_String = 14,
	EVRApplicationProperty_VRApplicationProperty_URL_String = 15,
	EVRApplicationProperty_VRApplicationProperty_Description_String = 50,
	EVRApplicationProperty_VRApplicationProperty_NewsURL_String = 51,
	EVRApplicationProperty_VRApplicationProperty_ImagePath_String = 52,
	EVRApplicationProperty_VRApplicationProperty_Source_String = 53,
	EVRApplicationProperty_VRApplicationProperty_ActionManifestURL_String = 54,
	EVRApplicationProperty_VRApplicationProperty_IsDashboardOverlay_Bool = 60,
	EVRApplicationProperty_VRApplicationProperty_IsTemplate_Bool = 61,
	EVRApplicationProperty_VRApplicationProperty_IsInstanced_Bool = 62,
	EVRApplicationProperty_VRApplicationProperty_IsInternal_Bool = 63,
	EVRApplicationProperty_VRApplicationProperty_WantsCompositorPauseInStandby_Bool = 64,
	EVRApplicationProperty_VRApplicationProperty_IsHidden_Bool = 65,
	EVRApplicationProperty_VRApplicationProperty_LastLaunchTime_Uint64 = 70,
} EVRApplicationProperty;

প্রকারলেখ গণনা EVRSceneApplicationState
{
	EVRSceneApplicationState_None = 0,
	EVRSceneApplicationState_Starting = 1,
	EVRSceneApplicationState_Quitting = 2,
	EVRSceneApplicationState_Running = 3,
	EVRSceneApplicationState_Waiting = 4,
} EVRSceneApplicationState;

প্রকারলেখ গণনা ChaperoneCalibrationState
{
	ChaperoneCalibrationState_OK = 1,
	ChaperoneCalibrationState_Warning = 100,
	ChaperoneCalibrationState_Warning_BaseStationMayHaveMoved = 101,
	ChaperoneCalibrationState_Warning_BaseStationRemoved = 102,
	ChaperoneCalibrationState_Warning_SeatedBoundsInvalid = 103,
	ChaperoneCalibrationState_Error = 200,
	ChaperoneCalibrationState_Error_BaseStationUninitialized = 201,
	ChaperoneCalibrationState_Error_BaseStationConflict = 202,
	ChaperoneCalibrationState_Error_PlayAreaInvalid = 203,
	ChaperoneCalibrationState_Error_CollisionBoundsInvalid = 204,
} ChaperoneCalibrationState;

প্রকারলেখ গণনা EChaperoneConfigFile
{
	EChaperoneConfigFile_Live = 1,
	EChaperone_Config_File_অস্থায়ী = 2,
} EChaperoneConfigFile;

প্রকারলেখ গণনা EChaperoneImportFlags
{
	EChaperoneImportFlags_EChaperoneImport_BoundsOnly = 1,
} EChaperoneImportFlags;

প্রকারলেখ গণনা EVRCompositorError
{
	EVRCompositorError_VRCompositorError_None = 0,
	EVRCompositorError_VRCompositorError_RequestFailed = 1,
	EVRCompositorError_VRCompositorError_IncompatibleVersion = 100,
	EVRCompositorError_VRCompositorError_DoNotHaveFocus = 101,
	EVRCompositorError_VRCompositorError_InvalidTexture = 102,
	EVRCompositorError_VRCompositorError_IsNotSceneApplication = 103,
	EVRCompositorError_VRCompositorError_TextureIsOnWrongDevice = 104,
	EVRCompositorError_VRCompositorError_TextureUsesUnsupportedFormat = 105,
	EVRCompositorError_VRCompositorError_SharedTexturesNotSupported = 106,
	EVRCompositor_Error_VRCompositor_Error_সূচক_Out_Of_Range = 107,
	EVRCompositorError_VRCompositorError_AlreadySubmitted = 108,
	EVRCompositorError_VRCompositorError_InvalidBounds = 109,
	EVRCompositorError_VRCompositorError_AlreadySet = 110,
} EVRCompositorError;

প্রকারলেখ গণনা EVRCompositorTimingMode
{
	EVRCompositorTimingMode_VRCompositorTimingMode_Implicit = 0,
	EVRCompositorTimingMode_VRCompositorTimingMode_Explicit_RuntimePerformsPostPresentHandoff = 1,
	EVRCompositorTimingMode_VRCompositorTimingMode_Explicit_ApplicationPerformsPostPresentHandoff = 2,
} EVRCompositorTimingMode;

প্রকারলেখ গণনা VROverlay_প্রবেশ_Method
{
	VROverlay_প্রবেশ_Method_None = 0,
	VROverlay_প্রবেশ_Method_Mouse = 1,
} VROverlay_প্রবেশ_Method;

প্রকারলেখ গণনা VROverlayTransformType
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

প্রকারলেখ গণনা VROverlayFlags
{
	VROverlayFlags_NoDashboardTab = 8,
	VROverlayFlags_SendVRDiscreteScrollEvents = 64,
	VROverlayFlags_SendVRTouchpadEvents = 128,
	VROverlayFlags_ShowTouchPadScrollWheel = 256,
	VROverlayFlags_TransferOwnershipToInternalProcess = 512,
	VROverlayFlags_SideBySide_Parallel = 1024,
	VROverlayFlags_SideBySide_Crossed = 2048,
	VROverlayFlags_Panorama = 4096,
	VROverlayFlags_StereoPanorama = 8192,
	VROverlayFlags_SortWithNonSceneOverlays = 16384,
	VROverlayFlags_VisibleInDashboard = 32768,
	VROverlayFlags_MakeOverlaysInteractiveIfVisible = 65536,
	VROverlayFlags_SendVRSmoothScrollEvents = 131072,
	VROverlayFlags_ProtectedContent = 262144,
	VROverlayFlags_HideLaserIntersection = 524288,
	VROverlayFlags_WantsModalBehavior = 1048576,
	VROverlayFlags_IsPremultiplied = 2097152,
	VROverlayFlags_IgnoreTextureAlpha = 4194304,
	VROverlayFlags_EnableControlBar = 8388608,
	VROverlayFlags_EnableControlBarKeyboard = 16777216,
	VROverlayFlags_EnableControlBarClose = 33554432,
} VROverlayFlags;

প্রকারলেখ গণনা VRMessageOverlayResponse
{
	VRMessageOverlayResponse_ButtonPress_0 = 0,
	VRMessageOverlayResponse_ButtonPress_1 = 1,
	VRMessageOverlayResponse_ButtonPress_2 = 2,
	VRMessageOverlayResponse_ButtonPress_3 = 3,
	VRMessageOverlayResponse_CouldntFindSystemOverlay = 4,
	VRMessageOverlayResponse_CouldntFindOrCreateClientOverlay = 5,
	VRMessageOverlayResponse_ApplicationQuit = 6,
} VRMessageOverlayResponse;

প্রকারলেখ গণনা EGamepad_Text_প্রবেশ_Mode
{
	EGamepad_Text_প্রবেশ_Mode_k_EGamepad_Text_প্রবেশ_Mode_Normal = 0,
	EGamepad_Text_প্রবেশ_Mode_k_EGamepad_Text_প্রবেশ_Mode_Password = 1,
	EGamepad_Text_প্রবেশ_Mode_k_EGamepad_Text_প্রবেশ_Mode_Submit = 2,
} EGamepad_Text_প্রবেশ_Mode;

প্রকারলেখ গণনা EGamepad_Text_প্রবেশ_সারি_Mode
{
	EGamepad_Text_প্রবেশ_সারি_Mode_k_EGamepad_Text_প্রবেশ_সারি_Mode_Single_সারি = 0,
	EGamepad_Text_প্রবেশ_সারি_Mode_k_EGamepad_Text_প্রবেশ_সারি_Mode_Multiple_সারিগুলি = 1,
} EGamepad_Text_প্রবেশ_সারি_Mode;

প্রকারলেখ গণনা EVROverlayIntersectionMaskPrimitiveType
{
	EVROverlayIntersectionMaskPrimitiveType_OverlayIntersectionPrimitiveType_Rectangle = 0,
	EVROverlayIntersectionMaskPrimitiveType_OverlayIntersectionPrimitiveType_Circle = 1,
} EVROverlayIntersectionMaskPrimitiveType;

প্রকারলেখ গণনা EKeyboardFlags
{
	EKeyboardFlags_KeyboardFlag_Minimal = 1,
	EKeyboardFlags_KeyboardFlag_Modal = 2,
} EKeyboardFlags;

প্রকারলেখ গণনা EDeviceType
{
	EDeviceType_DeviceType_Invalid = -1,
	EDeviceType_DeviceType_DirectX11 = 0,
	EDeviceType_DeviceType_Vulkan = 1,
} EDeviceType;

প্রকারলেখ গণনা HeadsetViewMode_t
{
	Headset_View_Mode_t_Headset_View_Mode_বাম = 0,
	Headset_View_Mode_t_Headset_View_Mode_ডান = 1,
	HeadsetViewMode_t_HeadsetViewMode_Both = 2,
} HeadsetViewMode_t;

প্রকারলেখ গণনা EVRRenderModelError
{
	EVRRenderModelError_VRRenderModelError_None = 0,
	EVRRenderModelError_VRRenderModelError_Loading = 100,
	EVRRenderModelError_VRRenderModelError_NotSupported = 200,
	EVRRenderModelError_VRRenderModelError_InvalidArg = 300,
	EVRRenderModelError_VRRenderModelError_InvalidModel = 301,
	EVRRenderModelError_VRRenderModelError_NoShapes = 302,
	EVRRenderModelError_VRRenderModelError_MultipleShapes = 303,
	EVRRenderModelError_VRRenderModelError_TooManyVertices = 304,
	EVRRenderModelError_VRRenderModelError_MultipleTextures = 305,
	EVRRender_Model_Error_VRRender_Model_Error_বাফার_Too_Small = 306,
	EVRRenderModelError_VRRenderModelError_NotEnoughNormals = 307,
	EVRRenderModelError_VRRenderModelError_NotEnoughTexCoords = 308,
	EVRRenderModelError_VRRenderModelError_InvalidTexture = 400,
} EVRRenderModelError;

প্রকারলেখ গণনা EVRRenderModelTextureFormat
{
	EVRRenderModelTextureFormat_VRRenderModelTextureFormat_RGBA8_SRGB = 0,
	EVRRenderModelTextureFormat_VRRenderModelTextureFormat_BC2 = 1,
	EVRRenderModelTextureFormat_VRRenderModelTextureFormat_BC4 = 2,
	EVRRenderModelTextureFormat_VRRenderModelTextureFormat_BC7 = 3,
	EVRRenderModelTextureFormat_VRRenderModelTextureFormat_BC7_SRGB = 4,
	EVRRenderModelTextureFormat_VRRenderModelTextureFormat_RGBA16_FLOAT = 5,
} EVRRenderModelTextureFormat;

প্রকারলেখ গণনা EVRNotificationType
{
	EVRNotificationType_Transient = 0,
	EVRNotificationType_Persistent = 1,
	EVRNotification_Type_Transient_System_With_User_মান = 2,
} EVRNotificationType;

প্রকারলেখ গণনা EVRNotificationStyle
{
	EVRNotificationStyle_None = 0,
	EVRNotificationStyle_Application = 100,
	EVRNotificationStyle_Contact_Disabled = 200,
	EVRNotificationStyle_Contact_Enabled = 201,
	EVRNotificationStyle_Contact_Active = 202,
} EVRNotificationStyle;

প্রকারলেখ গণনা EVRSettingsError
{
	EVRSettingsError_VRSettingsError_None = 0,
	EVRSettingsError_VRSettingsError_IPCFailed = 1,
	EVRSettingsError_VRSettingsError_WriteFailed = 2,
	EVRSettingsError_VRSettingsError_ReadFailed = 3,
	EVRSettingsError_VRSettingsError_JsonParseFailed = 4,
	EVRSettingsError_VRSettingsError_UnsetSettingHasNoDefault = 5,
} EVRSettingsError;

প্রকারলেখ গণনা EVRScreenshotError
{
	EVRScreenshotError_VRScreenshotError_None = 0,
	EVRScreenshotError_VRScreenshotError_RequestFailed = 1,
	EVRScreenshotError_VRScreenshotError_IncompatibleVersion = 100,
	EVRScreenshotError_VRScreenshotError_NotFound = 101,
	EVRScreenshot_Error_VRScreenshot_Error_বাফার_Too_Small = 102,
	EVRScreenshotError_VRScreenshotError_ScreenshotAlreadyInProgress = 108,
} EVRScreenshotError;

প্রকারলেখ গণনা EVRSkeletalTransformSpace
{
	EVRSkeletalTransformSpace_VRSkeletalTransformSpace_Model = 0,
	EVRSkeletalTransformSpace_VRSkeletalTransformSpace_Parent = 1,
} EVRSkeletalTransformSpace;

প্রকারলেখ গণনা EVRSkeletalReferencePose
{
	EVRSkeletalReferencePose_VRSkeletalReferencePose_BindPose = 0,
	EVRSkeletalReferencePose_VRSkeletalReferencePose_OpenHand = 1,
	EVRSkeletalReferencePose_VRSkeletalReferencePose_Fist = 2,
	EVRSkeletalReferencePose_VRSkeletalReferencePose_GripLimit = 3,
} EVRSkeletalReferencePose;

প্রকারলেখ গণনা EVRFinger
{
	EVRFinger_VRFinger_Thumb = 0,
	EVRFinger_VRFinger_সূচক = 1,
	EVRFinger_VRFinger_মধ্য = 2,
	EVRFinger_VRFinger_Ring = 3,
	EVRFinger_VRFinger_Pinky = 4,
	EVRFinger_VRFinger_গুনতি = 5,
} EVRFinger;

প্রকারলেখ গণনা EVRFingerSplay
{
	EVRFinger_Splay_VRFinger_Splay_Thumb_সূচক = 0,
	EVRFinger_Splay_VRFinger_Splay_সূচক_মধ্য = 1,
	EVRFinger_Splay_VRFinger_Splay_মধ্য_Ring = 2,
	EVRFingerSplay_VRFingerSplay_Ring_Pinky = 3,
	EVRFinger_Splay_VRFinger_Splay_গুনতি = 4,
} EVRFingerSplay;

প্রকারলেখ গণনা EVRSummaryType
{
	EVRSummaryType_VRSummaryType_FromAnimation = 0,
	EVRSummaryType_VRSummaryType_FromDevice = 1,
} EVRSummaryType;

প্রকারলেখ গণনা EVRInputFilterCancelType
{
	EVRInputFilterCancelType_VRInputFilterCancel_Timers = 0,
	EVRInputFilterCancelType_VRInputFilterCancel_Momentum = 1,
} EVRInputFilterCancelType;

প্রকারলেখ গণনা EVRInputStringBits
{
	EVRInputStringBits_VRInputString_Hand = 1,
	EVRInputStringBits_VRInputString_ControllerType = 2,
	EVRInput_String_Bits_VRInput_String_প্রবেশ_Source = 4,
	EVRInputStringBits_VRInputString_All = -1,
} EVRInputStringBits;

প্রকারলেখ গণনা EIOBufferError
{
	EIOBufferError_IOBuffer_Success = 0,
	EIOBufferError_IOBuffer_OperationFailed = 100,
	EIOBufferError_IOBuffer_InvalidHandle = 101,
	EIOBufferError_IOBuffer_InvalidArgument = 102,
	EIOBufferError_IOBuffer_PathExists = 103,
	EIOBufferError_IOBuffer_PathDoesNotExist = 104,
	EIOBufferError_IOBuffer_Permission = 105,
} EIOBufferError;

প্রকারলেখ গণনা EIOBufferMode
{
	EIOBufferMode_IOBufferMode_Read = 1,
	EIOBufferMode_IOBufferMode_Write = 2,
	EIOBufferMode_IOBufferMode_Create = 512,
} EIOBufferMode;

প্রকারলেখ গণনা EVRDebugError
{
	EVRDebugError_VRDebugError_Success = 0,
	EVRDebugError_VRDebugError_BadParameter = 1,
} EVRDebugError;

প্রকারলেখ গণনা EPropertyWriteType
{
	EPropertyWriteType_PropertyWrite_Set = 0,
	EPropertyWriteType_PropertyWrite_Erase = 1,
	EPropertyWriteType_PropertyWrite_SetError = 2,
} EPropertyWriteType;

প্রকারলেখ গণনা EBlockQueueError
{
	EBlockQueueError_BlockQueueError_None = 0,
	EBlockQueueError_BlockQueueError_QueueAlreadyExists = 1,
	EBlockQueueError_BlockQueueError_QueueNotFound = 2,
	EBlockQueueError_BlockQueueError_BlockNotAvailable = 3,
	EBlockQueueError_BlockQueueError_InvalidHandle = 4,
	EBlockQueueError_BlockQueueError_InvalidParam = 5,
	EBlockQueueError_BlockQueueError_ParamMismatch = 6,
	EBlockQueueError_BlockQueueError_InternalError = 7,
	EBlockQueueError_BlockQueueError_AlreadyInitialized = 8,
	EBlockQueueError_BlockQueueError_OperationIsServerOnly = 9,
	EBlockQueueError_BlockQueueError_TooManyConnections = 10,
} EBlockQueueError;

প্রকারলেখ গণনা EBlockQueueReadType
{
	EBlockQueueReadType_BlockQueueRead_Latest = 0,
	EBlockQueueReadType_BlockQueueRead_New = 1,
	EBlock_Queue_Read_Type_Block_Queue_Read_পরবর্তী = 2,
} EBlockQueueReadType;

প্রকারলেখ গণনা EBlockQueueCreationFlag
{
	EBlockQueueCreationFlag_BlockQueueFlag_OwnerIsReader = 1,
} EBlockQueueCreationFlag;


// OpenVR typedefs

প্রকারলেখ uint32_t PropertyTypeTag_t;
প্রকারলেখ uint32_t SpatialAnchorHandle_t;
প্রকারলেখ শূন্য * glSharedTextureHandle_t;
প্রকারলেখ int32_t glInt_t;
প্রকারলেখ uint32_t glUInt_t;
প্রকারলেখ uint64_t SharedTextureHandle_t;
প্রকারলেখ uint32_t DriverId_t;
প্রকারলেখ uint32_t Tracked_Device_সূচক_t;
প্রকারলেখ uint64_t WebConsoleHandle_t;
প্রকারলেখ uint64_t PropertyContainerHandle_t;
প্রকারলেখ PropertyContainerHandle_t DriverHandle_t;
প্রকারলেখ uint64_t VRActionHandle_t;
প্রকারলেখ uint64_t VRActionSetHandle_t;
প্রকারলেখ uint64_t VRInput_মান_Handle_t;
প্রকারলেখ uint32_t VRComponentProperties;
প্রকারলেখ uint64_t VROverlayHandle_t;
প্রকারলেখ int32_t Bone_সূচক_t;
প্রকারলেখ uint64_t TrackedCameraHandle_t;
প্রকারলেখ uint32_t ScreenshotHandle_t;
প্রকারলেখ int32_t TextureID_t;
প্রকারলেখ uint32_t VRNotificationId;
প্রকারলেখ uint64_t IOBufferHandle_t;
প্রকারলেখ uint64_t VrProfilerEventHandle_t;
প্রকারলেখ EVRInitError HmdError;
প্রকারলেখ EVREye Hmd_Eye;
প্রকারলেখ EColorSpace ColorSpace;
প্রকারলেখ ETracking_ফলাফল Hmd_Tracking_ফলাফল;
প্রকারলেখ ETrackedDeviceClass TrackedDeviceClass;
প্রকারলেখ ETrackingUniverseOrigin TrackingUniverseOrigin;
প্রকারলেখ ETrackedDeviceProperty TrackedDeviceProperty;
প্রকারলেখ ETrackedPropertyError TrackedPropertyError;
প্রকারলেখ EVRSubmitFlags VRSubmitFlags_t;
প্রকারলেখ EVRState VRState_t;
প্রকারলেখ ECollisionBoundsStyle CollisionBoundsStyle_t;
প্রকারলেখ EVROverlayError VROverlayError;
প্রকারলেখ EVRFirmwareError VRFirmwareError;
প্রকারলেখ EVRCompositorError VRCompositorError;
প্রকারলেখ EVRScreenshotError VRScreenshotsError;
প্রকারলেখ uint64_t PathHandle_t;

// OpenVR Structs

প্রকারলেখ কাঠামো HmdMatrix34_t
{
	দশমিক m[3][4]; //float[3][4]
} HmdMatrix34_t;

প্রকারলেখ কাঠামো HmdMatrix33_t
{
	দশমিক m[3][3]; //float[3][3]
} HmdMatrix33_t;

প্রকারলেখ কাঠামো HmdMatrix44_t
{
	দশমিক m[4][4]; //float[4][4]
} HmdMatrix44_t;

প্রকারলেখ কাঠামো HmdVector3_t
{
	দশমিক v[3]; //float[3]
} HmdVector3_t;

প্রকারলেখ কাঠামো HmdVector4_t
{
	দশমিক v[4]; //float[4]
} HmdVector4_t;

প্রকারলেখ কাঠামো HmdVector3d_t
{
	দ্বিগুণ v[3]; //double[3]
} HmdVector3d_t;

প্রকারলেখ কাঠামো HmdVector2_t
{
	দশমিক v[2]; //float[2]
} HmdVector2_t;

প্রকারলেখ কাঠামো HmdQuaternion_t
{
	দ্বিগুণ w;
	দ্বিগুণ x;
	দ্বিগুণ y;
	দ্বিগুণ z;
} HmdQuaternion_t;

প্রকারলেখ কাঠামো HmdQuaternionf_t
{
	দশমিক w;
	দশমিক x;
	দশমিক y;
	দশমিক z;
} HmdQuaternionf_t;

প্রকারলেখ কাঠামো HmdColor_t
{
	দশমিক r;
	দশমিক g;
	দশমিক b;
	দশমিক a;
} HmdColor_t;

প্রকারলেখ কাঠামো HmdQuad_t
{
	কাঠামো HmdVector3_t vCorners[4]; //struct vr::HmdVector3_t[4]
} HmdQuad_t;

প্রকারলেখ কাঠামো HmdRect2_t
{
	কাঠামো HmdVector2_t v_শীর্ষ_বাম;
	কাঠামো HmdVector2_t v_Bottom_ডান;
} HmdRect2_t;

প্রকারলেখ কাঠামো VRBoneTransform_t
{
	কাঠামো HmdVector4_t position;
	কাঠামো HmdQuaternionf_t orientation;
} VRBoneTransform_t;

প্রকারলেখ কাঠামো DistortionCoordinates_t
{
	দশমিক rfRed[2]; //float[2]
	দশমিক rfGreen[2]; //float[2]
	দশমিক rfBlue[2]; //float[2]
} DistortionCoordinates_t;

প্রকারলেখ কাঠামো Texture_t
{
	শূন্য * handle; // void *
	গণনা ETextureType eType;
	গণনা EColorSpace eColorSpace;
} Texture_t;

প্রকারলেখ কাঠামো TrackedDevicePose_t
{
	কাঠামো HmdMatrix34_t mDeviceToAbsoluteTracking;
	কাঠামো HmdVector3_t vVelocity;
	কাঠামো HmdVector3_t vAngularVelocity;
	গণনা ETracking_ফলাফল e_Tracking_ফলাফল;
	bool bPoseIsValid;
	bool bDeviceIsConnected;
} TrackedDevicePose_t;

প্রকারলেখ কাঠামো VRTextureBounds_t
{
	দশমিক uMin;
	দশমিক vMin;
	দশমিক uMax;
	দশমিক vMax;
} VRTextureBounds_t;

প্রকারলেখ কাঠামো VRTextureWithPose_t
{
	শূন্য * handle; // void *
	গণনা ETextureType eType;
	গণনা EColorSpace eColorSpace;
	কাঠামো HmdMatrix34_t mDeviceToAbsoluteTracking;
} VRTextureWithPose_t;

প্রকারলেখ কাঠামো VRTextureDepthInfo_t
{
	শূন্য * handle; // void *
	কাঠামো HmdMatrix44_t mProjection;
	কাঠামো HmdVector2_t vRange;
} VRTextureDepthInfo_t;

প্রকারলেখ কাঠামো VRTextureWithDepth_t
{
	শূন্য * handle; // void *
	গণনা ETextureType eType;
	গণনা EColorSpace eColorSpace;
	কাঠামো VRTextureDepthInfo_t depth;
} VRTextureWithDepth_t;

প্রকারলেখ কাঠামো VRTextureWithPoseAndDepth_t
{
	শূন্য * handle; // void *
	গণনা ETextureType eType;
	গণনা EColorSpace eColorSpace;
	কাঠামো HmdMatrix34_t mDeviceToAbsoluteTracking;
	কাঠামো VRTextureDepthInfo_t depth;
} VRTextureWithPoseAndDepth_t;

প্রকারলেখ কাঠামো VRVulkan_Texture_তথ্য_t
{
	uint64_t m_nImage;
	কাঠামো VkDevice_T * m_pDevice; // struct VkDevice_T *
	কাঠামো VkPhysicalDevice_T * m_pPhysicalDevice; // struct VkPhysicalDevice_T *
	কাঠামো VkInstance_T * m_pInstance; // struct VkInstance_T *
	কাঠামো VkQueue_T * m_pQueue; // struct VkQueue_T *
	uint32_t m_n_Queue_Family_সূচক;
	uint32_t m_nWidth;
	uint32_t m_nHeight;
	uint32_t m_nFormat;
	uint32_t m_n_Sample_গুনতি;
} VRVulkan_Texture_তথ্য_t;

প্রকারলেখ কাঠামো VRVulkan_Texture_Array_তথ্য_t
{
	uint32_t m_un_Array_সূচক;
	uint32_t m_un_Array_আকার;
} VRVulkan_Texture_Array_তথ্য_t;

প্রকারলেখ কাঠামো D3_D12_Texture_তথ্য_t
{
	কাঠামো ID3D12Resource * m_pResource; // struct ID3D12Resource *
	কাঠামো ID3D12CommandQueue * m_pCommandQueue; // struct ID3D12CommandQueue *
	uint32_t m_n_গ্রন্থি_Mask;
} D3_D12_Texture_তথ্য_t;

প্রকারলেখ কাঠামো VREvent_Controller_t
{
	uint32_t button;
} VREvent_Controller_t;

প্রকারলেখ কাঠামো VREvent_Mouse_t
{
	দশমিক x;
	দশমিক y;
	uint32_t button;
} VREvent_Mouse_t;

প্রকারলেখ কাঠামো VREvent_Scroll_t
{
	দশমিক xdelta;
	দশমিক ydelta;
	uint32_t unused;
	দশমিক viewportscale;
} VREvent_Scroll_t;

প্রকারলেখ কাঠামো VREvent_TouchPadMove_t
{
	bool bFingerDown;
	দশমিক flSecondsFingerDown;
	দশমিক f_মান_XFirst;
	দশমিক f_মান_YFirst;
	দশমিক f_মান_XRaw;
	দশমিক f_মান_YRaw;
} VREvent_TouchPadMove_t;

প্রকারলেখ কাঠামো VREvent_Notification_t
{
	uint64_t ul_User_মান;
	uint32_t notificationId;
} VREvent_Notification_t;

প্রকারলেখ কাঠামো VREvent_Process_t
{
	uint32_t pid;
	uint32_t oldPid;
	bool bForced;
	bool bConnectionLost;
} VREvent_Process_t;

প্রকারলেখ কাঠামো VREvent_Overlay_t
{
	uint64_t overlayHandle;
	uint64_t devicePath;
	uint64_t memoryBlockId;
} VREvent_Overlay_t;

প্রকারলেখ কাঠামো VREvent_Status_t
{
	uint32_t statusState;
} VREvent_Status_t;

প্রকারলেখ কাঠামো VREvent_Keyboard_t
{
	অক্ষর c_New_প্রবেশ[8]; //char[8]
	uint64_t u_User_মান;
} VREvent_Keyboard_t;

প্রকারলেখ কাঠামো VREvent_Ipd_t
{
	দশমিক ipdMeters;
} VREvent_Ipd_t;

প্রকারলেখ কাঠামো VREvent_Chaperone_t
{
	uint64_t m_nPreviousUniverse;
	uint64_t m_nCurrentUniverse;
} VREvent_Chaperone_t;

প্রকারলেখ কাঠামো VREvent_Reserved_t
{
	uint64_t reserved0;
	uint64_t reserved1;
	uint64_t reserved2;
	uint64_t reserved3;
	uint64_t reserved4;
	uint64_t reserved5;
} VREvent_Reserved_t;

প্রকারলেখ কাঠামো VREvent_PerformanceTest_t
{
	uint32_t m_nFidelityLevel;
} VREvent_PerformanceTest_t;

প্রকারলেখ কাঠামো VREvent_SeatedZeroPoseReset_t
{
	bool bResetBySystemMenu;
} VREvent_SeatedZeroPoseReset_t;

প্রকারলেখ কাঠামো VREvent_Screenshot_t
{
	uint32_t handle;
	uint32_t type;
} VREvent_Screenshot_t;

প্রকারলেখ কাঠামো VREvent_ScreenshotProgress_t
{
	দশমিক progress;
} VREvent_ScreenshotProgress_t;

প্রকারলেখ কাঠামো VREvent_ApplicationLaunch_t
{
	uint32_t pid;
	uint32_t unArgsHandle;
} VREvent_ApplicationLaunch_t;

প্রকারলেখ কাঠামো VREvent_EditingCameraSurface_t
{
	uint64_t overlayHandle;
	uint32_t nVisualMode;
} VREvent_EditingCameraSurface_t;

প্রকারলেখ কাঠামো VREvent_MessageOverlay_t
{
	uint32_t unVRMessageOverlayResponse;
} VREvent_MessageOverlay_t;

প্রকারলেখ কাঠামো VREvent_Property_t
{
	PropertyContainerHandle_t container;
	গণনা ETrackedDeviceProperty prop;
} VREvent_Property_t;

প্রকারলেখ কাঠামো VREvent_HapticVibration_t
{
	uint64_t containerHandle;
	uint64_t componentHandle;
	দশমিক fDurationSeconds;
	দশমিক fFrequency;
	দশমিক fAmplitude;
} VREvent_HapticVibration_t;

প্রকারলেখ কাঠামো VREvent_WebConsole_t
{
	WebConsoleHandle_t webConsoleHandle;
} VREvent_WebConsole_t;

প্রকারলেখ কাঠামো VREvent_প্রবেশ_Binding_Load_t
{
	PropertyContainerHandle_t ulAppContainer;
	uint64_t pathMessage;
	uint64_t pathUrl;
	uint64_t pathControllerType;
} VREvent_প্রবেশ_Binding_Load_t;

প্রকারলেখ কাঠামো VREvent_প্রবেশ_Action_Manifest_Load_t
{
	uint64_t path_App_চাবি;
	uint64_t pathMessage;
	uint64_t pathMessageParam;
	uint64_t pathManifestPath;
} VREvent_প্রবেশ_Action_Manifest_Load_t;

প্রকারলেখ কাঠামো VREvent_SpatialAnchor_t
{
	SpatialAnchorHandle_t unHandle;
} VREvent_SpatialAnchor_t;

প্রকারলেখ কাঠামো VREvent_ProgressUpdate_t
{
	uint64_t ulApplicationPropertyContainer;
	uint64_t pathDevice;
	uint64_t path_প্রবেশ_Source;
	uint64_t pathProgressAction;
	uint64_t pathIcon;
	দশমিক fProgress;
} VREvent_ProgressUpdate_t;

প্রকারলেখ কাঠামো VREvent_ShowUI_t
{
	গণনা EShowUIType eType;
} VREvent_ShowUI_t;

প্রকারলেখ কাঠামো VREvent_ShowDevTools_t
{
	int32_t nBrowserIdentifier;
} VREvent_ShowDevTools_t;

প্রকারলেখ কাঠামো VREvent_HDCPError_t
{
	গণনা EHDCPError eCode;
} VREvent_HDCPError_t;

প্রকারলেখ কাঠামো RenderModel_ComponentState_t
{
	কাঠামো HmdMatrix34_t mTrackingToComponentRenderModel;
	কাঠামো HmdMatrix34_t mTrackingToComponentLocal;
	VRComponentProperties uProperties;
} RenderModel_ComponentState_t;

প্রকারলেখ কাঠামো HiddenAreaMesh_t
{
	কাঠামো HmdVector2_t * p_Vertex_তথ্য; // const struct vr::HmdVector2_t *
	uint32_t un_Triangle_গুনতি;
} HiddenAreaMesh_t;

প্রকারলেখ কাঠামো VRControllerAxis_t
{
	দশমিক x;
	দশমিক y;
} VRControllerAxis_t;

প্রকারলেখ কাঠামো VRControllerState_t
{
	uint32_t un_Packet_অঙ্ক;
	uint64_t ulButtonPressed;
	uint64_t ulButtonTouched;
	কাঠামো VRControllerAxis_t rAxis[5]; //struct vr::VRControllerAxis_t[5]
} VRControllerState_t;

প্রকারলেখ কাঠামো CameraVideoStreamFrameHeader_t
{
	গণনা EVRTrackedCameraFrameType eFrameType;
	uint32_t nWidth;
	uint32_t nHeight;
	uint32_t nBytesPerPixel;
	uint32_t nFrameSequence;
	কাঠামো TrackedDevicePose_t trackedDevicePose;
	uint64_t ulFrameExposureTime;
} CameraVideoStreamFrameHeader_t;

প্রকারলেখ কাঠামো Compositor_FrameTiming
{
	uint32_t m_n_আকার;
	uint32_t m_n_Frame_সূচক;
	uint32_t m_n_অঙ্ক_Frame_Presents;
	uint32_t m_n_অঙ্ক_Mis_Presented;
	uint32_t m_n_অঙ্ক_Dropped_Frames;
	uint32_t m_nReprojectionFlags;
	দ্বিগুণ m_flSystemTimeInSeconds;
	দশমিক m_flPreSubmitGpuMs;
	দশমিক m_flPostSubmitGpuMs;
	দশমিক m_fl_যোগ_Render_Gpu_Ms;
	দশমিক m_flCompositorRenderGpuMs;
	দশমিক m_flCompositorRenderCpuMs;
	দশমিক m_flCompositorIdleCpuMs;
	দশমিক m_flClientFrameIntervalMs;
	দশমিক m_flPresentCallCpuMs;
	দশমিক m_flWaitForPresentCpuMs;
	দশমিক m_flSubmitFrameMs;
	দশমিক m_flWaitGetPosesCalledMs;
	দশমিক m_flNewPosesReadyMs;
	দশমিক m_flNewFrameReadyMs;
	দশমিক m_flCompositorUpdateStartMs;
	দশমিক m_flCompositorUpdateEndMs;
	দশমিক m_flCompositorRenderStartMs;
	TrackedDevicePose_t m_HmdPose;
	uint32_t m_n_অঙ্ক_VSyncs_Ready_For_Use;
	uint32_t m_n_অঙ্ক_VSyncs_To_First_View;
} Compositor_FrameTiming;

প্রকারলেখ কাঠামো Compositor_BenchmarkResults
{
	দশমিক m_flMegaPixelsPerSecond;
	দশমিক m_flHmdRecommendedMegaPixelsPerSecond;
} Compositor_BenchmarkResults;

প্রকারলেখ কাঠামো DriverDirectMode_FrameTiming
{
	uint32_t m_n_আকার;
	uint32_t m_n_অঙ্ক_Frame_Presents;
	uint32_t m_n_অঙ্ক_Mis_Presented;
	uint32_t m_n_অঙ্ক_Dropped_Frames;
	uint32_t m_nReprojectionFlags;
} DriverDirectMode_FrameTiming;

প্রকারলেখ কাঠামো ImuSample_t
{
	দ্বিগুণ fSampleTime;
	কাঠামো HmdVector3d_t vAccel;
	কাঠামো HmdVector3d_t vGyro;
	uint32_t unOffScaleFlags;
} ImuSample_t;

প্রকারলেখ কাঠামো App_Override_চাবিগুলি_t
{
	অক্ষর * pch_চাবি; // const char *
	অক্ষর * pch_মান; // const char *
} App_Override_চাবিগুলি_t;

প্রকারলেখ কাঠামো Compositor_CumulativeStats
{
	uint32_t m_nPid;
	uint32_t m_n_অঙ্ক_Frame_Presents;
	uint32_t m_n_অঙ্ক_Dropped_Frames;
	uint32_t m_n_অঙ্ক_Reprojected_Frames;
	uint32_t m_n_অঙ্ক_Frame_Presents_On_Startup;
	uint32_t m_n_অঙ্ক_Dropped_Frames_On_Startup;
	uint32_t m_n_অঙ্ক_Reprojected_Frames_On_Startup;
	uint32_t m_n_অঙ্ক_Loading;
	uint32_t m_n_অঙ্ক_Frame_Presents_Loading;
	uint32_t m_n_অঙ্ক_Dropped_Frames_Loading;
	uint32_t m_n_অঙ্ক_Reprojected_Frames_Loading;
	uint32_t m_n_অঙ্ক_Timed_Out;
	uint32_t m_n_অঙ্ক_Frame_Presents_Timed_Out;
	uint32_t m_n_অঙ্ক_Dropped_Frames_Timed_Out;
	uint32_t m_n_অঙ্ক_Reprojected_Frames_Timed_Out;
	uint32_t m_n_অঙ্ক_Frame_Submits;
	দ্বিগুণ m_fl_যোগ_Compositor_CPUTime_MS;
	দ্বিগুণ m_fl_যোগ_Compositor_GPUTime_MS;
	দ্বিগুণ m_fl_যোগ_Target_Frame_Times;
	দ্বিগুণ m_fl_যোগ_Application_CPUTime_MS;
	দ্বিগুণ m_fl_যোগ_Application_GPUTime_MS;
} Compositor_CumulativeStats;

প্রকারলেখ কাঠামো Compositor_StageRenderSettings
{
	কাঠামো HmdColor_t m_PrimaryColor;
	কাঠামো HmdColor_t m_SecondaryColor;
	দশমিক m_flVignetteInnerRadius;
	দশমিক m_flVignetteOuterRadius;
	দশমিক m_flFresnelStrength;
	bool m_bBackfaceCulling;
	bool m_bGreyscale;
	bool m_bWireframe;
} Compositor_StageRenderSettings;

প্রকারলেখ কাঠামো VROverlayIntersectionParams_t
{
	কাঠামো HmdVector3_t vSource;
	কাঠামো HmdVector3_t vDirection;
	গণনা ETrackingUniverseOrigin eOrigin;
} VROverlayIntersectionParams_t;

প্রকারলেখ কাঠামো VROverlayIntersectionResults_t
{
	কাঠামো HmdVector3_t vPoint;
	কাঠামো HmdVector3_t vNormal;
	কাঠামো HmdVector2_t vUVs;
	দশমিক fDistance;
} VROverlayIntersectionResults_t;

প্রকারলেখ কাঠামো IntersectionMaskRectangle_t
{
	দশমিক m_fl_শীর্ষ_বাম_X;
	দশমিক m_fl_শীর্ষ_বাম_Y;
	দশমিক m_flWidth;
	দশমিক m_flHeight;
} IntersectionMaskRectangle_t;

প্রকারলেখ কাঠামো IntersectionMaskCircle_t
{
	দশমিক m_flCenterX;
	দশমিক m_flCenterY;
	দশমিক m_flRadius;
} IntersectionMaskCircle_t;

প্রকারলেখ কাঠামো VROverlayProjection_t
{
	দশমিক f_বাম;
	দশমিক f_ডান;
	দশমিক f_শীর্ষ;
	দশমিক fBottom;
} VROverlayProjection_t;

প্রকারলেখ কাঠামো VROverlayView_t
{
	VROverlayHandle_t overlayHandle;
	কাঠামো Texture_t texture;
	কাঠামো VRTextureBounds_t textureBounds;
} VROverlayView_t;

প্রকারলেখ কাঠামো VRVulkanDevice_t
{
	কাঠামো VkInstance_T * m_pInstance; // struct VkInstance_T *
	কাঠামো VkDevice_T * m_pDevice; // struct VkDevice_T *
	কাঠামো VkPhysicalDevice_T * m_pPhysicalDevice; // struct VkPhysicalDevice_T *
	কাঠামো VkQueue_T * m_pQueue; // struct VkQueue_T *
	uint32_t m_u_Queue_Family_সূচক;
} VRVulkanDevice_t;

প্রকারলেখ কাঠামো VRNativeDevice_t
{
	শূন্য * handle; // void *
	গণনা EDeviceType eType;
} VRNativeDevice_t;

প্রকারলেখ কাঠামো RenderModel_Vertex_t
{
	কাঠামো HmdVector3_t vPosition;
	কাঠামো HmdVector3_t vNormal;
	দশমিক rfTextureCoord[2]; //float[2]
} RenderModel_Vertex_t;

#যদি defined(__linux__) || defined(__APPLE__)
#pragma pack( ঠেলো, 4 )
#endif
প্রকারলেখ কাঠামো RenderModel_TextureMap_t
{
	uint16_t unWidth;
	uint16_t unHeight;
	uint8_t * rub_Texture_Map_তথ্য; // const uint8_t *
	গণনা EVRRenderModelTextureFormat format;
	uint16_t unMipLevels;
} RenderModel_TextureMap_t;

#যদি defined(__linux__) || defined(__APPLE__)
#pragma pack( বের_করো )
#endif
#যদি defined(__linux__) || defined(__APPLE__)
#pragma pack( ঠেলো, 4 )
#endif
প্রকারলেখ কাঠামো RenderModel_t
{
	কাঠামো RenderModel_Vertex_t * r_Vertex_তথ্য; // const struct vr::RenderModel_Vertex_t *
	uint32_t un_Vertex_গুনতি;
	uint16_t * r_সূচক_তথ্য; // const uint16_t *
	uint32_t un_Triangle_গুনতি;
	TextureID_t diffuseTextureId;
} RenderModel_t;

#যদি defined(__linux__) || defined(__APPLE__)
#pragma pack( বের_করো )
#endif
প্রকারলেখ কাঠামো RenderModel_ControllerMode_State_t
{
	bool bScrollWheelVisible;
} RenderModel_ControllerMode_State_t;

প্রকারলেখ কাঠামো NotificationBitmap_t
{
	শূন্য * m_p_Image_তথ্য; // void *
	int32_t m_nWidth;
	int32_t m_nHeight;
	int32_t m_nBytesPerPixel;
} NotificationBitmap_t;

প্রকারলেখ কাঠামো CVRSettingHelper
{
	intptr_t m_pSettings; // class vr::IVRSettings *
} CVRSettingHelper;

প্রকারলেখ কাঠামো প্রবেশ_Analog_Action_তথ্য_t
{
	bool bActive;
	VRInput_মান_Handle_t activeOrigin;
	দশমিক x;
	দশমিক y;
	দশমিক z;
	দশমিক deltaX;
	দশমিক deltaY;
	দশমিক deltaZ;
	দশমিক fUpdateTime;
} প্রবেশ_Analog_Action_তথ্য_t;

প্রকারলেখ কাঠামো প্রবেশ_Digital_Action_তথ্য_t
{
	bool bActive;
	VRInput_মান_Handle_t activeOrigin;
	bool bState;
	bool bChanged;
	দশমিক fUpdateTime;
} প্রবেশ_Digital_Action_তথ্য_t;

প্রকারলেখ কাঠামো প্রবেশ_Pose_Action_তথ্য_t
{
	bool bActive;
	VRInput_মান_Handle_t activeOrigin;
	কাঠামো TrackedDevicePose_t pose;
} প্রবেশ_Pose_Action_তথ্য_t;

প্রকারলেখ কাঠামো প্রবেশ_Skeletal_Action_তথ্য_t
{
	bool bActive;
	VRInput_মান_Handle_t activeOrigin;
} প্রবেশ_Skeletal_Action_তথ্য_t;

প্রকারলেখ কাঠামো প্রবেশ_Origin_Info_t
{
	VRInput_মান_Handle_t devicePath;
	Tracked_Device_সূচক_t tracked_Device_সূচক;
	অক্ষর rchRenderModelComponentName[128]; //char[128]
} প্রবেশ_Origin_Info_t;

প্রকারলেখ কাঠামো প্রবেশ_Binding_Info_t
{
	অক্ষর rchDevicePathName[128]; //char[128]
	অক্ষর rch_প্রবেশ_Path_Name[128]; //char[128]
	অক্ষর rchModeName[128]; //char[128]
	অক্ষর rchSlotName[128]; //char[128]
	অক্ষর rch_প্রবেশ_Source_Type[32]; //char[32]
} প্রবেশ_Binding_Info_t;

প্রকারলেখ কাঠামো VRActiveActionSet_t
{
	VRActionSetHandle_t ulActionSet;
	VRInput_মান_Handle_t ulRestrictedToDevice;
	VRActionSetHandle_t ulSecondaryActionSet;
	uint32_t unPadding;
	int32_t nPriority;
} VRActiveActionSet_t;

প্রকারলেখ কাঠামো VRSkeletal_Summary_তথ্য_t
{
	দশমিক flFingerCurl[5]; //float[5]
	দশমিক flFingerSplay[4]; //float[4]
} VRSkeletal_Summary_তথ্য_t;

প্রকারলেখ কাঠামো SpatialAnchorPose_t
{
	কাঠামো HmdMatrix34_t mAnchorToAbsoluteTracking;
} SpatialAnchorPose_t;

প্রকারলেখ কাঠামো COpenVRContext
{
	intptr_t m_pVRSystem; // class vr::IVRSystem *
	intptr_t m_pVRChaperone; // class vr::IVRChaperone *
	intptr_t m_pVRChaperoneSetup; // class vr::IVRChaperoneSetup *
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

প্রকারলেখ কাঠামো PropertyWrite_t
{
	গণনা ETrackedDeviceProperty prop;
	গণনা EPropertyWriteType writeType;
	গণনা ETrackedPropertyError eSetError;
	শূন্য * pv_বাফার; // void *
	uint32_t un_বাফার_আকার;
	PropertyTypeTag_t unTag;
	গণনা ETrackedPropertyError eError;
} PropertyWrite_t;

প্রকারলেখ কাঠামো PropertyRead_t
{
	গণনা ETrackedDeviceProperty prop;
	শূন্য * pv_বাফার; // void *
	uint32_t un_বাফার_আকার;
	PropertyTypeTag_t unTag;
	uint32_t un_Required_বাফার_আকার;
	গণনা ETrackedPropertyError eError;
} PropertyRead_t;

প্রকারলেখ কাঠামো CVRPropertyHelpers
{
	intptr_t m_pProperties; // class vr::IVRProperties *
} CVRPropertyHelpers;

প্রকারলেখ কাঠামো PathWrite_t
{
	PathHandle_t ulPath;
	গণনা EPropertyWriteType writeType;
	গণনা ETrackedPropertyError eSetError;
	শূন্য * pv_বাফার; // void *
	uint32_t un_বাফার_আকার;
	PropertyTypeTag_t unTag;
	গণনা ETrackedPropertyError eError;
	অক্ষর * pszPath; // const char *
} PathWrite_t;

প্রকারলেখ কাঠামো PathRead_t
{
	PathHandle_t ulPath;
	শূন্য * pv_বাফার; // void *
	uint32_t un_বাফার_আকার;
	PropertyTypeTag_t unTag;
	uint32_t un_Required_বাফার_আকার;
	গণনা ETrackedPropertyError eError;
	অক্ষর * pszPath; // const char *
} PathRead_t;


প্রকারলেখ সংঘ
{
	VREvent_Reserved_t reserved;
	VREvent_Controller_t controller;
	VREvent_Mouse_t mouse;
	VREvent_Scroll_t scroll;
	VREvent_Process_t process;
	VREvent_Notification_t notification;
	VREvent_Overlay_t overlay;
	VREvent_Status_t status;
	VREvent_Keyboard_t keyboard;
	VREvent_Ipd_t ipd;
	VREvent_Chaperone_t chaperone;
	VREvent_PerformanceTest_t performanceTest;
	VREvent_TouchPadMove_t touchPadMove;
	VREvent_SeatedZeroPoseReset_t seatedZeroPoseReset;
	VREvent_Screenshot_t screenshot;
	VREvent_ScreenshotProgress_t screenshotProgress;
	VREvent_ApplicationLaunch_t applicationLaunch;
	VREvent_EditingCameraSurface_t cameraSurface;
	VREvent_MessageOverlay_t messageOverlay;
	VREvent_Property_t property;
	VREvent_HapticVibration_t hapticVibration;
	VREvent_WebConsole_t webConsole;
	VREvent_প্রবেশ_Binding_Load_t প্রবেশ_Binding;
	VREvent_প্রবেশ_Action_Manifest_Load_t actionManifest;
	VREvent_SpatialAnchor_t spatialAnchor;
} VREvent_তথ্য_t;

#যদি defined(__linux__) || defined(__APPLE__) 
// This structure was originally defined mis-packed on Linux, preserved for 
// compatibility. 
#pragma pack( ঠেলো, 4 )
#endif

/** An event posted by the server to all running applications */
কাঠামো VREvent_t
{
	uint32_t eventType; // EVREventType enum
	Tracked_Device_সূচক_t tracked_Device_সূচক;
	দশমিক eventAgeSeconds;
	// event data must be the end of the struct as its size is variable
	VREvent_তথ্য_t তথ্য;
};

#যদি defined(__linux__) || defined(__APPLE__) 
#pragma pack( বের_করো )
#endif


প্রকারলেখ সংঘ
{
	IntersectionMaskRectangle_t m_Rectangle;
	IntersectionMaskCircle_t m_Circle;
} VROverlay_Intersection_Mask_Primitive_তথ্য_t;

কাঠামো VROverlayIntersectionMaskPrimitive_t
{
	EVROverlayIntersectionMaskPrimitiveType m_nPrimitiveType;
	VROverlay_Intersection_Mask_Primitive_তথ্য_t m_Primitive;
};


// OpenVR Function Pointer Tables

কাঠামো VR_IVRSystem_FnTable
{
	শূন্য (OPENVR_FNTABLE_CALLTYPE *Get_Recommended_Render_Target_আকার)(uint32_t * pnWidth, uint32_t * pnHeight);
	কাঠামো HmdMatrix44_t (OPENVR_FNTABLE_CALLTYPE *GetProjectionMatrix)(EVREye eEye, দশমিক fNearZ, দশমিক fFarZ);
	শূন্য (OPENVR_FNTABLE_CALLTYPE *GetProjectionRaw)(EVREye eEye, দশমিক * pf_বাম, দশমিক * pf_ডান, দশমিক * pf_শীর্ষ, দশমিক * pfBottom);
	bool (OPENVR_FNTABLE_CALLTYPE *ComputeDistortion)(EVREye eEye, দশমিক fU, দশমিক fV, কাঠামো DistortionCoordinates_t * pDistortionCoordinates);
	কাঠামো HmdMatrix34_t (OPENVR_FNTABLE_CALLTYPE *Get_Eye_To_শীর্ষ_Transform)(EVREye eEye);
	bool (OPENVR_FNTABLE_CALLTYPE *GetTimeSinceLastVsync)(দশমিক * pfSecondsSinceLastVsync, uint64_t * pul_Frame_গণক);
	int32_t (OPENVR_FNTABLE_CALLTYPE *Get_D3_D9_Adapter_সূচক)();
	শূন্য (OPENVR_FNTABLE_CALLTYPE *GetDXGIOutputInfo)(int32_t * pn_Adapter_সূচক);
	শূন্য (OPENVR_FNTABLE_CALLTYPE *GetOutputDevice)(uint64_t * pnDevice, ETextureType textureType, কাঠামো VkInstance_T * pInstance);
	bool (OPENVR_FNTABLE_CALLTYPE *IsDisplayOnDesktop)();
	bool (OPENVR_FNTABLE_CALLTYPE *SetDisplayVisibility)(bool bIsVisibleOnDesktop);
	শূন্য (OPENVR_FNTABLE_CALLTYPE *GetDeviceToAbsoluteTrackingPose)(ETrackingUniverseOrigin eOrigin, দশমিক fPredictedSecondsToPhotonsFromNow, কাঠামো TrackedDevicePose_t * pTrackedDevicePoseArray, uint32_t un_Tracked_Device_Pose_Array_গুনতি);
	কাঠামো HmdMatrix34_t (OPENVR_FNTABLE_CALLTYPE *GetSeatedZeroPoseToStandingAbsoluteTrackingPose)();
	কাঠামো HmdMatrix34_t (OPENVR_FNTABLE_CALLTYPE *GetRawZeroPoseToStandingAbsoluteTrackingPose)();
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetSortedTrackedDeviceIndicesOfClass)(ETrackedDeviceClass eTrackedDeviceClass, Tracked_Device_সূচক_t * pun_Tracked_Device_সূচক_Array, uint32_t un_Tracked_Device_সূচক_Array_গুনতি, Tracked_Device_সূচক_t un_Relative_To_Tracked_Device_সূচক);
	EDeviceActivityLevel (OPENVR_FNTABLE_CALLTYPE *GetTrackedDeviceActivityLevel)(Tracked_Device_সূচক_t unDeviceId);
	শূন্য (OPENVR_FNTABLE_CALLTYPE *ApplyTransform)(কাঠামো TrackedDevicePose_t * pOutputPose, কাঠামো TrackedDevicePose_t * pTrackedDevicePose, কাঠামো HmdMatrix34_t * pTransform);
	Tracked_Device_সূচক_t (OPENVR_FNTABLE_CALLTYPE *Get_Tracked_Device_সূচক_For_Controller_Role)(ETrackedControllerRole unDeviceType);
	ETrackedControllerRole (OPENVR_FNTABLE_CALLTYPE *Get_Controller_Role_For_Tracked_Device_সূচক)(Tracked_Device_সূচক_t un_Device_সূচক);
	ETrackedDeviceClass (OPENVR_FNTABLE_CALLTYPE *GetTrackedDeviceClass)(Tracked_Device_সূচক_t un_Device_সূচক);
	bool (OPENVR_FNTABLE_CALLTYPE *IsTrackedDeviceConnected)(Tracked_Device_সূচক_t un_Device_সূচক);
	bool (OPENVR_FNTABLE_CALLTYPE *GetBoolTrackedDeviceProperty)(Tracked_Device_সূচক_t un_Device_সূচক, ETrackedDeviceProperty prop, ETrackedPropertyError * pError);
	দশমিক (OPENVR_FNTABLE_CALLTYPE *GetFloatTrackedDeviceProperty)(Tracked_Device_সূচক_t un_Device_সূচক, ETrackedDeviceProperty prop, ETrackedPropertyError * pError);
	int32_t (OPENVR_FNTABLE_CALLTYPE *GetInt32TrackedDeviceProperty)(Tracked_Device_সূচক_t un_Device_সূচক, ETrackedDeviceProperty prop, ETrackedPropertyError * pError);
	uint64_t (OPENVR_FNTABLE_CALLTYPE *GetUint64TrackedDeviceProperty)(Tracked_Device_সূচক_t un_Device_সূচক, ETrackedDeviceProperty prop, ETrackedPropertyError * pError);
	কাঠামো HmdMatrix34_t (OPENVR_FNTABLE_CALLTYPE *GetMatrix34TrackedDeviceProperty)(Tracked_Device_সূচক_t un_Device_সূচক, ETrackedDeviceProperty prop, ETrackedPropertyError * pError);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetArrayTrackedDeviceProperty)(Tracked_Device_সূচক_t un_Device_সূচক, ETrackedDeviceProperty prop, PropertyTypeTag_t propType, শূন্য * p_বাফার, uint32_t un_বাফার_আকার, ETrackedPropertyError * pError);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetStringTrackedDeviceProperty)(Tracked_Device_সূচক_t un_Device_সূচক, ETrackedDeviceProperty prop, অক্ষর * pch_মান, uint32_t un_বাফার_আকার, ETrackedPropertyError * pError);
	অক্ষর * (OPENVR_FNTABLE_CALLTYPE *GetPropErrorNameFromEnum)(ETrackedPropertyError error);
	bool (OPENVR_FNTABLE_CALLTYPE *Poll_পরবর্তী_Event)(কাঠামো VREvent_t * pEvent, uint32_t uncbVREvent);
	bool (OPENVR_FNTABLE_CALLTYPE *Poll_পরবর্তী_Event_With_Pose)(ETrackingUniverseOrigin eOrigin, কাঠামো VREvent_t * pEvent, uint32_t uncbVREvent, TrackedDevicePose_t * pTrackedDevicePose);
	অক্ষর * (OPENVR_FNTABLE_CALLTYPE *GetEventTypeNameFromEnum)(EVREventType eType);
	কাঠামো HiddenAreaMesh_t (OPENVR_FNTABLE_CALLTYPE *GetHiddenAreaMesh)(EVREye eEye, EHiddenAreaMeshType type);
	bool (OPENVR_FNTABLE_CALLTYPE *GetControllerState)(Tracked_Device_সূচক_t un_Controller_Device_সূচক, VRControllerState_t * pControllerState, uint32_t un_Controller_State_আকার);
	bool (OPENVR_FNTABLE_CALLTYPE *GetControllerStateWithPose)(ETrackingUniverseOrigin eOrigin, Tracked_Device_সূচক_t un_Controller_Device_সূচক, VRControllerState_t * pControllerState, uint32_t un_Controller_State_আকার, কাঠামো TrackedDevicePose_t * pTrackedDevicePose);
	শূন্য (OPENVR_FNTABLE_CALLTYPE *TriggerHapticPulse)(Tracked_Device_সূচক_t un_Controller_Device_সূচক, uint32_t unAxisId, unsigned short usDurationMicroSec);
	অক্ষর * (OPENVR_FNTABLE_CALLTYPE *GetButtonIdNameFromEnum)(EVRButtonId eButtonId);
	অক্ষর * (OPENVR_FNTABLE_CALLTYPE *GetControllerAxisTypeNameFromEnum)(EVRControllerAxisType eAxisType);
	bool (OPENVR_FNTABLE_CALLTYPE *Is_প্রবেশ_Available)();
	bool (OPENVR_FNTABLE_CALLTYPE *IsSteamVRDrawingControllers)();
	bool (OPENVR_FNTABLE_CALLTYPE *ShouldApplicationPause)();
	bool (OPENVR_FNTABLE_CALLTYPE *ShouldApplicationReduceRenderingWork)();
	EVRFirmwareError (OPENVR_FNTABLE_CALLTYPE *PerformFirmwareUpdate)(Tracked_Device_সূচক_t un_Device_সূচক);
	শূন্য (OPENVR_FNTABLE_CALLTYPE *AcknowledgeQuit_Exiting)();
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetAppContainerFilePaths)(অক্ষর * pch_বাফার, uint32_t un_বাফার_আকার);
	অক্ষর * (OPENVR_FNTABLE_CALLTYPE *GetRuntimeVersion)();
};

কাঠামো VR_IVRExtendedDisplay_FnTable
{
	শূন্য (OPENVR_FNTABLE_CALLTYPE *GetWindowBounds)(int32_t * pnX, int32_t * pnY, uint32_t * pnWidth, uint32_t * pnHeight);
	শূন্য (OPENVR_FNTABLE_CALLTYPE *GetEyeOutputViewport)(EVREye eEye, uint32_t * pnX, uint32_t * pnY, uint32_t * pnWidth, uint32_t * pnHeight);
	শূন্য (OPENVR_FNTABLE_CALLTYPE *GetDXGIOutputInfo)(int32_t * pn_Adapter_সূচক, int32_t * pn_Adapter_Output_সূচক);
};

কাঠামো VR_IVRTrackedCamera_FnTable
{
	অক্ষর * (OPENVR_FNTABLE_CALLTYPE *GetCameraErrorNameFromEnum)(EVRTrackedCameraError eCameraError);
	EVRTrackedCameraError (OPENVR_FNTABLE_CALLTYPE *HasCamera)(Tracked_Device_সূচক_t n_Device_সূচক, bool * pHasCamera);
	EVRTrackedCameraError (OPENVR_FNTABLE_CALLTYPE *Get_Camera_Frame_আকার)(Tracked_Device_সূচক_t n_Device_সূচক, EVRTrackedCameraFrameType eFrameType, uint32_t * pnWidth, uint32_t * pnHeight, uint32_t * pn_Frame_বাফার_আকার);
	EVRTrackedCameraError (OPENVR_FNTABLE_CALLTYPE *GetCameraIntrinsics)(Tracked_Device_সূচক_t n_Device_সূচক, uint32_t n_Camera_সূচক, EVRTrackedCameraFrameType eFrameType, HmdVector2_t * p_Focal_দৈর্ঘ্য, HmdVector2_t * pCenter);
	EVRTrackedCameraError (OPENVR_FNTABLE_CALLTYPE *GetCameraProjection)(Tracked_Device_সূচক_t n_Device_সূচক, uint32_t n_Camera_সূচক, EVRTrackedCameraFrameType eFrameType, দশমিক flZNear, দশমিক flZFar, HmdMatrix44_t * pProjection);
	EVRTrackedCameraError (OPENVR_FNTABLE_CALLTYPE *AcquireVideoStreamingService)(Tracked_Device_সূচক_t n_Device_সূচক, TrackedCameraHandle_t * pHandle);
	EVRTrackedCameraError (OPENVR_FNTABLE_CALLTYPE *ReleaseVideoStreamingService)(TrackedCameraHandle_t hTrackedCamera);
	EVRTrackedCameraError (OPENVR_FNTABLE_CALLTYPE *Get_Video_Stream_Frame_বাফার)(TrackedCameraHandle_t hTrackedCamera, EVRTrackedCameraFrameType eFrameType, শূন্য * p_Frame_বাফার, uint32_t n_Frame_বাফার_আকার, CameraVideoStreamFrameHeader_t * pFrameHeader, uint32_t n_Frame_Header_আকার);
	EVRTrackedCameraError (OPENVR_FNTABLE_CALLTYPE *Get_Video_Stream_Texture_আকার)(Tracked_Device_সূচক_t n_Device_সূচক, EVRTrackedCameraFrameType eFrameType, VRTextureBounds_t * pTextureBounds, uint32_t * pnWidth, uint32_t * pnHeight);
	EVRTrackedCameraError (OPENVR_FNTABLE_CALLTYPE *GetVideoStreamTextureD3D11)(TrackedCameraHandle_t hTrackedCamera, EVRTrackedCameraFrameType eFrameType, শূন্য * pD3D11DeviceOrResource, শূন্য ** ppD3D11ShaderResourceView, CameraVideoStreamFrameHeader_t * pFrameHeader, uint32_t n_Frame_Header_আকার);
	EVRTrackedCameraError (OPENVR_FNTABLE_CALLTYPE *GetVideoStreamTextureGL)(TrackedCameraHandle_t hTrackedCamera, EVRTrackedCameraFrameType eFrameType, glUInt_t * pglTextureId, CameraVideoStreamFrameHeader_t * pFrameHeader, uint32_t n_Frame_Header_আকার);
	EVRTrackedCameraError (OPENVR_FNTABLE_CALLTYPE *ReleaseVideoStreamTextureGL)(TrackedCameraHandle_t hTrackedCamera, glUInt_t glTextureId);
	শূন্য (OPENVR_FNTABLE_CALLTYPE *SetCameraTrackingSpace)(ETrackingUniverseOrigin eUniverse);
	ETrackingUniverseOrigin (OPENVR_FNTABLE_CALLTYPE *GetCameraTrackingSpace)();
};

কাঠামো VR_IVRApplications_FnTable
{
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *AddApplicationManifest)(অক্ষর * pchApplicationManifestFullPath, bool bTemporary);
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *RemoveApplicationManifest)(অক্ষর * pchApplicationManifestFullPath);
	bool (OPENVR_FNTABLE_CALLTYPE *IsApplicationInstalled)(অক্ষর * pch_App_চাবি);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *Get_Application_গুনতি)();
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *Get_Application_চাবি_By_সূচক)(uint32_t un_Application_সূচক, অক্ষর * pch_App_চাবি_বাফার, uint32_t un_App_চাবি_বাফার_Len);
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *Get_Application_চাবি_By_Process_Id)(uint32_t unProcessId, অক্ষর * pch_App_চাবি_বাফার, uint32_t un_App_চাবি_বাফার_Len);
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *LaunchApplication)(অক্ষর * pch_App_চাবি);
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *LaunchTemplateApplication)(অক্ষর * pch_Template_App_চাবি, অক্ষর * pch_New_App_চাবি, কাঠামো App_Override_চাবিগুলি_t * p_চাবিগুলি, uint32_t un_চাবিগুলি);
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *LaunchApplicationFromMimeType)(অক্ষর * pchMimeType, অক্ষর * pchArgs);
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *LaunchDashboardOverlay)(অক্ষর * pch_App_চাবি);
	bool (OPENVR_FNTABLE_CALLTYPE *CancelApplicationLaunch)(অক্ষর * pch_App_চাবি);
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *IdentifyApplication)(uint32_t unProcessId, অক্ষর * pch_App_চাবি);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetApplicationProcessId)(অক্ষর * pch_App_চাবি);
	অক্ষর * (OPENVR_FNTABLE_CALLTYPE *GetApplicationsErrorNameFromEnum)(EVRApplicationError error);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetApplicationPropertyString)(অক্ষর * pch_App_চাবি, EVRApplicationProperty eProperty, অক্ষর * pch_Property_মান_বাফার, uint32_t un_Property_মান_বাফার_Len, EVRApplicationError * peError);
	bool (OPENVR_FNTABLE_CALLTYPE *GetApplicationPropertyBool)(অক্ষর * pch_App_চাবি, EVRApplicationProperty eProperty, EVRApplicationError * peError);
	uint64_t (OPENVR_FNTABLE_CALLTYPE *GetApplicationPropertyUint64)(অক্ষর * pch_App_চাবি, EVRApplicationProperty eProperty, EVRApplicationError * peError);
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *SetApplicationAutoLaunch)(অক্ষর * pch_App_চাবি, bool bAutoLaunch);
	bool (OPENVR_FNTABLE_CALLTYPE *GetApplicationAutoLaunch)(অক্ষর * pch_App_চাবি);
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *SetDefaultApplicationForMimeType)(অক্ষর * pch_App_চাবি, অক্ষর * pchMimeType);
	bool (OPENVR_FNTABLE_CALLTYPE *GetDefaultApplicationForMimeType)(অক্ষর * pchMimeType, অক্ষর * pch_App_চাবি_বাফার, uint32_t un_App_চাবি_বাফার_Len);
	bool (OPENVR_FNTABLE_CALLTYPE *GetApplicationSupportedMimeTypes)(অক্ষর * pch_App_চাবি, অক্ষর * pch_Mime_Types_বাফার, uint32_t un_Mime_Types_বাফার);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetApplicationsThatSupportMimeType)(অক্ষর * pchMimeType, অক্ষর * pch_App_চাবিগুলি_That_Support_বাফার, uint32_t un_App_চাবিগুলি_That_Support_বাফার);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetApplicationLaunchArguments)(uint32_t unHandle, অক্ষর * pchArgs, uint32_t unArgs);
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *GetStartingApplication)(অক্ষর * pch_App_চাবি_বাফার, uint32_t un_App_চাবি_বাফার_Len);
	EVRSceneApplicationState (OPENVR_FNTABLE_CALLTYPE *GetSceneApplicationState)();
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *PerformApplicationPrelaunchCheck)(অক্ষর * pch_App_চাবি);
	অক্ষর * (OPENVR_FNTABLE_CALLTYPE *GetSceneApplicationStateNameFromEnum)(EVRSceneApplicationState state);
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *LaunchInternalProcess)(অক্ষর * pch_দ্বিমিক_Path, অক্ষর * pchArguments, অক্ষর * pchWorkingDirectory);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetCurrentSceneProcessId)();
};

কাঠামো VR_IVRChaperone_FnTable
{
	ChaperoneCalibrationState (OPENVR_FNTABLE_CALLTYPE *GetCalibrationState)();
	bool (OPENVR_FNTABLE_CALLTYPE *Get_Play_Area_আকার)(দশমিক * p_আকার_X, দশমিক * p_আকার_Z);
	bool (OPENVR_FNTABLE_CALLTYPE *GetPlayAreaRect)(কাঠামো HmdQuad_t * rect);
	শূন্য (OPENVR_FNTABLE_CALLTYPE *ReloadInfo)();
	শূন্য (OPENVR_FNTABLE_CALLTYPE *SetSceneColor)(কাঠামো HmdColor_t color);
	শূন্য (OPENVR_FNTABLE_CALLTYPE *GetBoundsColor)(কাঠামো HmdColor_t * pOutputColorArray, পূর্ণসংখ্যা n_অঙ্ক_Output_Colors, দশমিক flCollisionBoundsFadeDistance, কাঠামো HmdColor_t * pOutputCameraColor);
	bool (OPENVR_FNTABLE_CALLTYPE *AreBoundsVisible)();
	শূন্য (OPENVR_FNTABLE_CALLTYPE *ForceBoundsVisible)(bool bForce);
	শূন্য (OPENVR_FNTABLE_CALLTYPE *ResetZeroPose)(ETrackingUniverseOrigin eTrackingUniverseOrigin);
};

কাঠামো VR_IVRChaperoneSetup_FnTable
{
	bool (OPENVR_FNTABLE_CALLTYPE *CommitWorkingCopy)(EChaperoneConfigFile configFile);
	শূন্য (OPENVR_FNTABLE_CALLTYPE *RevertWorkingCopy)();
	bool (OPENVR_FNTABLE_CALLTYPE *Get_Working_Play_Area_আকার)(দশমিক * p_আকার_X, দশমিক * p_আকার_Z);
	bool (OPENVR_FNTABLE_CALLTYPE *GetWorkingPlayAreaRect)(কাঠামো HmdQuad_t * rect);
	bool (OPENVR_FNTABLE_CALLTYPE *GetWorkingCollisionBoundsInfo)(কাঠামো HmdQuad_t * p_Quads_বাফার, uint32_t * pun_Quads_গুনতি);
	bool (OPENVR_FNTABLE_CALLTYPE *GetLiveCollisionBoundsInfo)(কাঠামো HmdQuad_t * p_Quads_বাফার, uint32_t * pun_Quads_গুনতি);
	bool (OPENVR_FNTABLE_CALLTYPE *GetWorkingSeatedZeroPoseToRawTrackingPose)(কাঠামো HmdMatrix34_t * pmatSeatedZeroPoseToRawTrackingPose);
	bool (OPENVR_FNTABLE_CALLTYPE *GetWorkingStandingZeroPoseToRawTrackingPose)(কাঠামো HmdMatrix34_t * pmatStandingZeroPoseToRawTrackingPose);
	শূন্য (OPENVR_FNTABLE_CALLTYPE *Set_Working_Play_Area_আকার)(দশমিক আকার_X, দশমিক আকার_Z);
	শূন্য (OPENVR_FNTABLE_CALLTYPE *SetWorkingCollisionBoundsInfo)(কাঠামো HmdQuad_t * p_Quads_বাফার, uint32_t un_Quads_গুনতি);
	শূন্য (OPENVR_FNTABLE_CALLTYPE *SetWorkingPerimeter)(কাঠামো HmdVector2_t * p_Point_বাফার, uint32_t un_Point_গুনতি);
	শূন্য (OPENVR_FNTABLE_CALLTYPE *SetWorkingSeatedZeroPoseToRawTrackingPose)(কাঠামো HmdMatrix34_t * pMatSeatedZeroPoseToRawTrackingPose);
	শূন্য (OPENVR_FNTABLE_CALLTYPE *SetWorkingStandingZeroPoseToRawTrackingPose)(কাঠামো HmdMatrix34_t * pMatStandingZeroPoseToRawTrackingPose);
	শূন্য (OPENVR_FNTABLE_CALLTYPE *ReloadFromDisk)(EChaperoneConfigFile configFile);
	bool (OPENVR_FNTABLE_CALLTYPE *GetLiveSeatedZeroPoseToRawTrackingPose)(কাঠামো HmdMatrix34_t * pmatSeatedZeroPoseToRawTrackingPose);
	bool (OPENVR_FNTABLE_CALLTYPE *Export_Live_To_বাফার)(অক্ষর * p_বাফার, uint32_t * pn_বাফার_দৈর্ঘ্য);
	bool (OPENVR_FNTABLE_CALLTYPE *Import_From_বাফার_To_Working)(অক্ষর * p_বাফার, uint32_t nImportFlags);
	শূন্য (OPENVR_FNTABLE_CALLTYPE *ShowWorkingSetPreview)();
	শূন্য (OPENVR_FNTABLE_CALLTYPE *HideWorkingSetPreview)();
	শূন্য (OPENVR_FNTABLE_CALLTYPE *RoomSetupStarting)();
};

কাঠামো VR_IVRCompositor_FnTable
{
	শূন্য (OPENVR_FNTABLE_CALLTYPE *SetTrackingSpace)(ETrackingUniverseOrigin eOrigin);
	ETrackingUniverseOrigin (OPENVR_FNTABLE_CALLTYPE *GetTrackingSpace)();
	EVRCompositorError (OPENVR_FNTABLE_CALLTYPE *WaitGetPoses)(কাঠামো TrackedDevicePose_t * pRenderPoseArray, uint32_t un_Render_Pose_Array_গুনতি, কাঠামো TrackedDevicePose_t * pGamePoseArray, uint32_t un_Game_Pose_Array_গুনতি);
	EVRCompositorError (OPENVR_FNTABLE_CALLTYPE *GetLastPoses)(কাঠামো TrackedDevicePose_t * pRenderPoseArray, uint32_t un_Render_Pose_Array_গুনতি, কাঠামো TrackedDevicePose_t * pGamePoseArray, uint32_t un_Game_Pose_Array_গুনতি);
	EVRCompositorError (OPENVR_FNTABLE_CALLTYPE *Get_Last_Pose_For_Tracked_Device_সূচক)(Tracked_Device_সূচক_t un_Device_সূচক, কাঠামো TrackedDevicePose_t * pOutputPose, কাঠামো TrackedDevicePose_t * pOutputGamePose);
	EVRCompositorError (OPENVR_FNTABLE_CALLTYPE *Submit)(EVREye eEye, কাঠামো Texture_t * pTexture, কাঠামো VRTextureBounds_t * pBounds, EVRSubmitFlags nSubmitFlags);
	শূন্য (OPENVR_FNTABLE_CALLTYPE *ClearLastSubmittedFrame)();
	শূন্য (OPENVR_FNTABLE_CALLTYPE *PostPresentHandoff)();
	bool (OPENVR_FNTABLE_CALLTYPE *GetFrameTiming)(কাঠামো Compositor_FrameTiming * pTiming, uint32_t unFramesAgo);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetFrameTimings)(কাঠামো Compositor_FrameTiming * pTiming, uint32_t nFrames);
	দশমিক (OPENVR_FNTABLE_CALLTYPE *GetFrameTimeRemaining)();
	শূন্য (OPENVR_FNTABLE_CALLTYPE *GetCumulativeStats)(কাঠামো Compositor_CumulativeStats * pStats, uint32_t n_Stats_আকার_In_Bytes);
	শূন্য (OPENVR_FNTABLE_CALLTYPE *FadeToColor)(দশমিক fSeconds, দশমিক fRed, দশমিক fGreen, দশমিক fBlue, দশমিক fAlpha, bool bBackground);
	কাঠামো HmdColor_t (OPENVR_FNTABLE_CALLTYPE *GetCurrentFadeColor)(bool bBackground);
	শূন্য (OPENVR_FNTABLE_CALLTYPE *FadeGrid)(দশমিক fSeconds, bool bFadeGridIn);
	দশমিক (OPENVR_FNTABLE_CALLTYPE *GetCurrentGridAlpha)();
	EVRCompositorError (OPENVR_FNTABLE_CALLTYPE *SetSkyboxOverride)(কাঠামো Texture_t * pTextures, uint32_t un_Texture_গুনতি);
	শূন্য (OPENVR_FNTABLE_CALLTYPE *ClearSkyboxOverride)();
	শূন্য (OPENVR_FNTABLE_CALLTYPE *CompositorBringToFront)();
	শূন্য (OPENVR_FNTABLE_CALLTYPE *CompositorGoToBack)();
	শূন্য (OPENVR_FNTABLE_CALLTYPE *CompositorQuit)();
	bool (OPENVR_FNTABLE_CALLTYPE *IsFullscreen)();
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetCurrentSceneFocusProcess)();
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetLastFrameRenderer)();
	bool (OPENVR_FNTABLE_CALLTYPE *CanRenderScene)();
	শূন্য (OPENVR_FNTABLE_CALLTYPE *ShowMirrorWindow)();
	শূন্য (OPENVR_FNTABLE_CALLTYPE *HideMirrorWindow)();
	bool (OPENVR_FNTABLE_CALLTYPE *IsMirrorWindowVisible)();
	শূন্য (OPENVR_FNTABLE_CALLTYPE *CompositorDumpImages)();
	bool (OPENVR_FNTABLE_CALLTYPE *Should_App_Render_With_নিচের_Resources)();
	শূন্য (OPENVR_FNTABLE_CALLTYPE *ForceInterleavedReprojectionOn)(bool bOverride);
	শূন্য (OPENVR_FNTABLE_CALLTYPE *ForceReconnectProcess)();
	শূন্য (OPENVR_FNTABLE_CALLTYPE *SuspendRendering)(bool bSuspend);
	EVRCompositorError (OPENVR_FNTABLE_CALLTYPE *GetMirrorTextureD3D11)(EVREye eEye, শূন্য * pD3D11DeviceOrResource, শূন্য ** ppD3D11ShaderResourceView);
	শূন্য (OPENVR_FNTABLE_CALLTYPE *ReleaseMirrorTextureD3D11)(শূন্য * pD3D11ShaderResourceView);
	EVRCompositorError (OPENVR_FNTABLE_CALLTYPE *GetMirrorTextureGL)(EVREye eEye, glUInt_t * pglTextureId, glSharedTextureHandle_t * pglSharedTextureHandle);
	bool (OPENVR_FNTABLE_CALLTYPE *ReleaseSharedGLTexture)(glUInt_t glTextureId, glSharedTextureHandle_t glSharedTextureHandle);
	শূন্য (OPENVR_FNTABLE_CALLTYPE *LockGLSharedTextureForAccess)(glSharedTextureHandle_t glSharedTextureHandle);
	শূন্য (OPENVR_FNTABLE_CALLTYPE *UnlockGLSharedTextureForAccess)(glSharedTextureHandle_t glSharedTextureHandle);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetVulkanInstanceExtensionsRequired)(অক্ষর * pch_মান, uint32_t un_বাফার_আকার);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetVulkanDeviceExtensionsRequired)(কাঠামো VkPhysicalDevice_T * pPhysicalDevice, অক্ষর * pch_মান, uint32_t un_বাফার_আকার);
	শূন্য (OPENVR_FNTABLE_CALLTYPE *SetExplicitTimingMode)(EVRCompositorTimingMode eTimingMode);
	EVRCompositorError (OPENVR_FNTABLE_CALLTYPE *Submit_Explicit_Timing_তথ্য)();
	bool (OPENVR_FNTABLE_CALLTYPE *IsMotionSmoothingEnabled)();
	bool (OPENVR_FNTABLE_CALLTYPE *IsMotionSmoothingSupported)();
	bool (OPENVR_FNTABLE_CALLTYPE *IsCurrentSceneFocusAppLoading)();
	EVRCompositorError (OPENVR_FNTABLE_CALLTYPE *SetStageOverride_Async)(অক্ষর * pchRenderModelPath, কাঠামো HmdMatrix34_t * pTransform, কাঠামো Compositor_StageRenderSettings * pRenderSettings, uint32_t n_আকার_Of_Render_Settings);
	শূন্য (OPENVR_FNTABLE_CALLTYPE *ClearStageOverride)();
	bool (OPENVR_FNTABLE_CALLTYPE *GetCompositorBenchmarkResults)(কাঠামো Compositor_BenchmarkResults * pBenchmarkResults, uint32_t n_আকার_Of_Benchmark_Results);
	EVRCompositorError (OPENVR_FNTABLE_CALLTYPE *GetLastPosePredictionIDs)(uint32_t * pRenderPosePredictionID, uint32_t * pGamePosePredictionID);
	EVRCompositorError (OPENVR_FNTABLE_CALLTYPE *GetPosesForFrame)(uint32_t unPosePredictionID, কাঠামো TrackedDevicePose_t * pPoseArray, uint32_t un_Pose_Array_গুনতি);
};

কাঠামো VR_IVROverlay_FnTable
{
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *FindOverlay)(অক্ষর * pch_Overlay_চাবি, VROverlayHandle_t * pOverlayHandle);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *CreateOverlay)(অক্ষর * pch_Overlay_চাবি, অক্ষর * pchOverlayName, VROverlayHandle_t * pOverlayHandle);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *DestroyOverlay)(VROverlayHandle_t ulOverlayHandle);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *Get_Overlay_চাবি)(VROverlayHandle_t ulOverlayHandle, অক্ষর * pch_মান, uint32_t un_বাফার_আকার, EVROverlayError * pError);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetOverlayName)(VROverlayHandle_t ulOverlayHandle, অক্ষর * pch_মান, uint32_t un_বাফার_আকার, EVROverlayError * pError);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *SetOverlayName)(VROverlayHandle_t ulOverlayHandle, অক্ষর * pchName);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *Get_Overlay_Image_তথ্য)(VROverlayHandle_t ulOverlayHandle, শূন্য * pv_বাফার, uint32_t un_বাফার_আকার, uint32_t * punWidth, uint32_t * punHeight);
	অক্ষর * (OPENVR_FNTABLE_CALLTYPE *GetOverlayErrorNameFromEnum)(EVROverlayError error);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *SetOverlayRenderingPid)(VROverlayHandle_t ulOverlayHandle, uint32_t unPID);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetOverlayRenderingPid)(VROverlayHandle_t ulOverlayHandle);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *SetOverlayFlag)(VROverlayHandle_t ulOverlayHandle, VROverlayFlags eOverlayFlag, bool bEnabled);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayFlag)(VROverlayHandle_t ulOverlayHandle, VROverlayFlags eOverlayFlag, bool * pbEnabled);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayFlags)(VROverlayHandle_t ulOverlayHandle, uint32_t * pFlags);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *SetOverlayColor)(VROverlayHandle_t ulOverlayHandle, দশমিক fRed, দশমিক fGreen, দশমিক fBlue);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayColor)(VROverlayHandle_t ulOverlayHandle, দশমিক * pfRed, দশমিক * pfGreen, দশমিক * pfBlue);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *SetOverlayAlpha)(VROverlayHandle_t ulOverlayHandle, দশমিক fAlpha);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayAlpha)(VROverlayHandle_t ulOverlayHandle, দশমিক * pfAlpha);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *SetOverlayTexelAspect)(VROverlayHandle_t ulOverlayHandle, দশমিক fTexelAspect);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayTexelAspect)(VROverlayHandle_t ulOverlayHandle, দশমিক * pfTexelAspect);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *SetOverlaySortOrder)(VROverlayHandle_t ulOverlayHandle, uint32_t unSortOrder);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlaySortOrder)(VROverlayHandle_t ulOverlayHandle, uint32_t * punSortOrder);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *SetOverlayWidthInMeters)(VROverlayHandle_t ulOverlayHandle, দশমিক fWidthInMeters);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayWidthInMeters)(VROverlayHandle_t ulOverlayHandle, দশমিক * pfWidthInMeters);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *SetOverlayCurvature)(VROverlayHandle_t ulOverlayHandle, দশমিক fCurvature);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayCurvature)(VROverlayHandle_t ulOverlayHandle, দশমিক * pfCurvature);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *SetOverlayPreCurvePitch)(VROverlayHandle_t ulOverlayHandle, দশমিক fRadians);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayPreCurvePitch)(VROverlayHandle_t ulOverlayHandle, দশমিক * pfRadians);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *SetOverlayTextureColorSpace)(VROverlayHandle_t ulOverlayHandle, EColorSpace eTextureColorSpace);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayTextureColorSpace)(VROverlayHandle_t ulOverlayHandle, EColorSpace * peTextureColorSpace);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *SetOverlayTextureBounds)(VROverlayHandle_t ulOverlayHandle, কাঠামো VRTextureBounds_t * pOverlayTextureBounds);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayTextureBounds)(VROverlayHandle_t ulOverlayHandle, কাঠামো VRTextureBounds_t * pOverlayTextureBounds);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayTransformType)(VROverlayHandle_t ulOverlayHandle, VROverlayTransformType * peTransformType);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *SetOverlayTransformAbsolute)(VROverlayHandle_t ulOverlayHandle, ETrackingUniverseOrigin eTrackingOrigin, কাঠামো HmdMatrix34_t * pmatTrackingOriginToOverlayTransform);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayTransformAbsolute)(VROverlayHandle_t ulOverlayHandle, ETrackingUniverseOrigin * peTrackingOrigin, কাঠামো HmdMatrix34_t * pmatTrackingOriginToOverlayTransform);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *SetOverlayTransformTrackedDeviceRelative)(VROverlayHandle_t ulOverlayHandle, Tracked_Device_সূচক_t unTrackedDevice, কাঠামো HmdMatrix34_t * pmatTrackedDeviceToOverlayTransform);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayTransformTrackedDeviceRelative)(VROverlayHandle_t ulOverlayHandle, Tracked_Device_সূচক_t * punTrackedDevice, কাঠামো HmdMatrix34_t * pmatTrackedDeviceToOverlayTransform);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *SetOverlayTransformTrackedDeviceComponent)(VROverlayHandle_t ulOverlayHandle, Tracked_Device_সূচক_t un_Device_সূচক, অক্ষর * pchComponentName);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayTransformTrackedDeviceComponent)(VROverlayHandle_t ulOverlayHandle, Tracked_Device_সূচক_t * pun_Device_সূচক, অক্ষর * pchComponentName, uint32_t un_Component_Name_আকার);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayTransformOverlayRelative)(VROverlayHandle_t ulOverlayHandle, VROverlayHandle_t * ulOverlayHandleParent, কাঠামো HmdMatrix34_t * pmatParentOverlayToOverlayTransform);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *SetOverlayTransformOverlayRelative)(VROverlayHandle_t ulOverlayHandle, VROverlayHandle_t ulOverlayHandleParent, কাঠামো HmdMatrix34_t * pmatParentOverlayToOverlayTransform);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *SetOverlayTransformCursor)(VROverlayHandle_t ulCursorOverlayHandle, কাঠামো HmdVector2_t * pvHotspot);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayTransformCursor)(VROverlayHandle_t ulOverlayHandle, কাঠামো HmdVector2_t * pvHotspot);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *SetOverlayTransformProjection)(VROverlayHandle_t ulOverlayHandle, ETrackingUniverseOrigin eTrackingOrigin, কাঠামো HmdMatrix34_t * pmatTrackingOriginToOverlayTransform, কাঠামো VROverlayProjection_t * pProjection, EVREye eEye);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *ShowOverlay)(VROverlayHandle_t ulOverlayHandle);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *HideOverlay)(VROverlayHandle_t ulOverlayHandle);
	bool (OPENVR_FNTABLE_CALLTYPE *IsOverlayVisible)(VROverlayHandle_t ulOverlayHandle);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetTransformForOverlayCoordinates)(VROverlayHandle_t ulOverlayHandle, ETrackingUniverseOrigin eTrackingOrigin, কাঠামো HmdVector2_t coordinatesInOverlay, কাঠামো HmdMatrix34_t * pmatTransform);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *WaitFrameSync)(uint32_t nTimeoutMs);
	bool (OPENVR_FNTABLE_CALLTYPE *Poll_পরবর্তী_Overlay_Event)(VROverlayHandle_t ulOverlayHandle, কাঠামো VREvent_t * pEvent, uint32_t uncbVREvent);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *Get_Overlay_প্রবেশ_Method)(VROverlayHandle_t ulOverlayHandle, VROverlay_প্রবেশ_Method * pe_প্রবেশ_Method);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *Set_Overlay_প্রবেশ_Method)(VROverlayHandle_t ulOverlayHandle, VROverlay_প্রবেশ_Method e_প্রবেশ_Method);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayMouseScale)(VROverlayHandle_t ulOverlayHandle, কাঠামো HmdVector2_t * pvecMouseScale);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *SetOverlayMouseScale)(VROverlayHandle_t ulOverlayHandle, কাঠামো HmdVector2_t * pvecMouseScale);
	bool (OPENVR_FNTABLE_CALLTYPE *ComputeOverlayIntersection)(VROverlayHandle_t ulOverlayHandle, কাঠামো VROverlayIntersectionParams_t * pParams, কাঠামো VROverlayIntersectionResults_t * pResults);
	bool (OPENVR_FNTABLE_CALLTYPE *IsHoverTargetOverlay)(VROverlayHandle_t ulOverlayHandle);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *SetOverlayIntersectionMask)(VROverlayHandle_t ulOverlayHandle, কাঠামো VROverlayIntersectionMaskPrimitive_t * pMaskPrimitives, uint32_t un_অঙ্ক_Mask_Primitives, uint32_t un_Primitive_আকার);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *TriggerLaserMouseHapticVibration)(VROverlayHandle_t ulOverlayHandle, দশমিক fDurationSeconds, দশমিক fFrequency, দশমিক fAmplitude);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *SetOverlayCursor)(VROverlayHandle_t ulOverlayHandle, VROverlayHandle_t ulCursorHandle);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *SetOverlayCursorPositionOverride)(VROverlayHandle_t ulOverlayHandle, কাঠামো HmdVector2_t * pvCursor);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *ClearOverlayCursorPositionOverride)(VROverlayHandle_t ulOverlayHandle);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *SetOverlayTexture)(VROverlayHandle_t ulOverlayHandle, কাঠামো Texture_t * pTexture);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *ClearOverlayTexture)(VROverlayHandle_t ulOverlayHandle);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *SetOverlayRaw)(VROverlayHandle_t ulOverlayHandle, শূন্য * pv_বাফার, uint32_t unWidth, uint32_t unHeight, uint32_t unBytesPerPixel);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *SetOverlayFromFile)(VROverlayHandle_t ulOverlayHandle, অক্ষর * pchFilePath);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayTexture)(VROverlayHandle_t ulOverlayHandle, শূন্য ** pNativeTextureHandle, শূন্য * pNativeTextureRef, uint32_t * pWidth, uint32_t * pHeight, uint32_t * pNativeFormat, ETextureType * pAPIType, EColorSpace * pColorSpace, কাঠামো VRTextureBounds_t * pTextureBounds);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *ReleaseNativeOverlayHandle)(VROverlayHandle_t ulOverlayHandle, শূন্য * pNativeTextureHandle);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *Get_Overlay_Texture_আকার)(VROverlayHandle_t ulOverlayHandle, uint32_t * pWidth, uint32_t * pHeight);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *CreateDashboardOverlay)(অক্ষর * pch_Overlay_চাবি, অক্ষর * pchOverlayFriendlyName, VROverlayHandle_t * pMainHandle, VROverlayHandle_t * pThumbnailHandle);
	bool (OPENVR_FNTABLE_CALLTYPE *IsDashboardVisible)();
	bool (OPENVR_FNTABLE_CALLTYPE *IsActiveDashboardOverlay)(VROverlayHandle_t ulOverlayHandle);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *SetDashboardOverlaySceneProcess)(VROverlayHandle_t ulOverlayHandle, uint32_t unProcessId);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetDashboardOverlaySceneProcess)(VROverlayHandle_t ulOverlayHandle, uint32_t * punProcessId);
	শূন্য (OPENVR_FNTABLE_CALLTYPE *ShowDashboard)(অক্ষর * pchOverlayToShow);
	Tracked_Device_সূচক_t (OPENVR_FNTABLE_CALLTYPE *GetPrimaryDashboardDevice)();
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *ShowKeyboard)(EGamepad_Text_প্রবেশ_Mode e_প্রবেশ_Mode, EGamepad_Text_প্রবেশ_সারি_Mode e_সারি_প্রবেশ_Mode, uint32_t unFlags, অক্ষর * pchDescription, uint32_t unCharMax, অক্ষর * pchExistingText, uint64_t u_User_মান);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *ShowKeyboardForOverlay)(VROverlayHandle_t ulOverlayHandle, EGamepad_Text_প্রবেশ_Mode e_প্রবেশ_Mode, EGamepad_Text_প্রবেশ_সারি_Mode e_সারি_প্রবেশ_Mode, uint32_t unFlags, অক্ষর * pchDescription, uint32_t unCharMax, অক্ষর * pchExistingText, uint64_t u_User_মান);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetKeyboardText)(অক্ষর * pchText, uint32_t cchText);
	শূন্য (OPENVR_FNTABLE_CALLTYPE *HideKeyboard)();
	শূন্য (OPENVR_FNTABLE_CALLTYPE *SetKeyboardTransformAbsolute)(ETrackingUniverseOrigin eTrackingOrigin, কাঠামো HmdMatrix34_t * pmatTrackingOriginToKeyboardTransform);
	শূন্য (OPENVR_FNTABLE_CALLTYPE *SetKeyboardPositionForOverlay)(VROverlayHandle_t ulOverlayHandle, কাঠামো HmdRect2_t avoidRect);
	VRMessageOverlayResponse (OPENVR_FNTABLE_CALLTYPE *ShowMessageOverlay)(অক্ষর * pchText, অক্ষর * pchCaption, অক্ষর * pchButton0Text, অক্ষর * pchButton1Text, অক্ষর * pchButton2Text, অক্ষর * pchButton3Text);
	শূন্য (OPENVR_FNTABLE_CALLTYPE *CloseMessageOverlay)();
};

কাঠামো VR_IVROverlayView_FnTable
{
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *AcquireOverlayView)(VROverlayHandle_t ulOverlayHandle, কাঠামো VRNativeDevice_t * pNativeDevice, কাঠামো VROverlayView_t * pOverlayView, uint32_t un_Overlay_View_আকার);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *ReleaseOverlayView)(কাঠামো VROverlayView_t * pOverlayView);
	শূন্য (OPENVR_FNTABLE_CALLTYPE *PostOverlayEvent)(VROverlayHandle_t ulOverlayHandle, কাঠামো VREvent_t * pvrEvent);
	bool (OPENVR_FNTABLE_CALLTYPE *IsViewingPermitted)(VROverlayHandle_t ulOverlayHandle);
};

কাঠামো VR_IVRHeadsetView_FnTable
{
	শূন্য (OPENVR_FNTABLE_CALLTYPE *Set_Headset_View_আকার)(uint32_t nWidth, uint32_t nHeight);
	শূন্য (OPENVR_FNTABLE_CALLTYPE *Get_Headset_View_আকার)(uint32_t * pnWidth, uint32_t * pnHeight);
	শূন্য (OPENVR_FNTABLE_CALLTYPE *SetHeadsetViewMode)(HeadsetViewMode_t eHeadsetViewMode);
	HeadsetViewMode_t (OPENVR_FNTABLE_CALLTYPE *GetHeadsetViewMode)();
	শূন্য (OPENVR_FNTABLE_CALLTYPE *SetHeadsetViewCropped)(bool bCropped);
	bool (OPENVR_FNTABLE_CALLTYPE *GetHeadsetViewCropped)();
	দশমিক (OPENVR_FNTABLE_CALLTYPE *GetHeadsetViewAspectRatio)();
	শূন্য (OPENVR_FNTABLE_CALLTYPE *SetHeadsetViewBlendRange)(দশমিক flStartPct, দশমিক flEndPct);
	শূন্য (OPENVR_FNTABLE_CALLTYPE *GetHeadsetViewBlendRange)(দশমিক * pStartPct, দশমিক * pEndPct);
};

কাঠামো VR_IVRRenderModels_FnTable
{
	EVRRenderModelError (OPENVR_FNTABLE_CALLTYPE *LoadRenderModel_Async)(অক্ষর * pchRenderModelName, কাঠামো RenderModel_t ** ppRenderModel);
	শূন্য (OPENVR_FNTABLE_CALLTYPE *FreeRenderModel)(কাঠামো RenderModel_t * pRenderModel);
	EVRRenderModelError (OPENVR_FNTABLE_CALLTYPE *LoadTexture_Async)(TextureID_t textureId, কাঠামো RenderModel_TextureMap_t ** ppTexture);
	শূন্য (OPENVR_FNTABLE_CALLTYPE *FreeTexture)(কাঠামো RenderModel_TextureMap_t * pTexture);
	EVRRenderModelError (OPENVR_FNTABLE_CALLTYPE *LoadTextureD3D11_Async)(TextureID_t textureId, শূন্য * pD3D11Device, শূন্য ** ppD3D11Texture2D);
	EVRRenderModelError (OPENVR_FNTABLE_CALLTYPE *LoadIntoTextureD3D11_Async)(TextureID_t textureId, শূন্য * pDstTexture);
	শূন্য (OPENVR_FNTABLE_CALLTYPE *FreeTextureD3D11)(শূন্য * pD3D11Texture2D);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetRenderModelName)(uint32_t un_Render_Model_সূচক, অক্ষর * pchRenderModelName, uint32_t unRenderModelNameLen);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *Get_Render_Model_গুনতি)();
	uint32_t (OPENVR_FNTABLE_CALLTYPE *Get_Component_গুনতি)(অক্ষর * pchRenderModelName);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetComponentName)(অক্ষর * pchRenderModelName, uint32_t un_Component_সূচক, অক্ষর * pchComponentName, uint32_t unComponentNameLen);
	uint64_t (OPENVR_FNTABLE_CALLTYPE *GetComponentButtonMask)(অক্ষর * pchRenderModelName, অক্ষর * pchComponentName);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetComponentRenderModelName)(অক্ষর * pchRenderModelName, অক্ষর * pchComponentName, অক্ষর * pchComponentRenderModelName, uint32_t unComponentRenderModelNameLen);
	bool (OPENVR_FNTABLE_CALLTYPE *GetComponentStateForDevicePath)(অক্ষর * pchRenderModelName, অক্ষর * pchComponentName, VRInput_মান_Handle_t devicePath, RenderModel_ControllerMode_State_t * pState, RenderModel_ComponentState_t * pComponentState);
	bool (OPENVR_FNTABLE_CALLTYPE *GetComponentState)(অক্ষর * pchRenderModelName, অক্ষর * pchComponentName, VRControllerState_t * pControllerState, কাঠামো RenderModel_ControllerMode_State_t * pState, কাঠামো RenderModel_ComponentState_t * pComponentState);
	bool (OPENVR_FNTABLE_CALLTYPE *RenderModelHasComponent)(অক্ষর * pchRenderModelName, অক্ষর * pchComponentName);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetRenderModelThumbnailURL)(অক্ষর * pchRenderModelName, অক্ষর * pchThumbnailURL, uint32_t unThumbnailURLLen, EVRRenderModelError * peError);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetRenderModelOriginalPath)(অক্ষর * pchRenderModelName, অক্ষর * pchOriginalPath, uint32_t unOriginalPathLen, EVRRenderModelError * peError);
	অক্ষর * (OPENVR_FNTABLE_CALLTYPE *GetRenderModelErrorNameFromEnum)(EVRRenderModelError error);
};

কাঠামো VR_IVRNotifications_FnTable
{
	EVRNotificationError (OPENVR_FNTABLE_CALLTYPE *CreateNotification)(VROverlayHandle_t ulOverlayHandle, uint64_t ul_User_মান, EVRNotificationType type, অক্ষর * pchText, EVRNotificationStyle style, কাঠামো NotificationBitmap_t * pImage, VRNotificationId * pNotificationId);
	EVRNotificationError (OPENVR_FNTABLE_CALLTYPE *RemoveNotification)(VRNotificationId notificationId);
};

কাঠামো VR_IVRSettings_FnTable
{
	অক্ষর * (OPENVR_FNTABLE_CALLTYPE *GetSettingsErrorNameFromEnum)(EVRSettingsError eError);
	শূন্য (OPENVR_FNTABLE_CALLTYPE *SetBool)(অক্ষর * pchSection, অক্ষর * pch_Settings_চাবি, bool b_মান, EVRSettingsError * peError);
	শূন্য (OPENVR_FNTABLE_CALLTYPE *SetInt32)(অক্ষর * pchSection, অক্ষর * pch_Settings_চাবি, int32_t n_মান, EVRSettingsError * peError);
	শূন্য (OPENVR_FNTABLE_CALLTYPE *SetFloat)(অক্ষর * pchSection, অক্ষর * pch_Settings_চাবি, দশমিক fl_মান, EVRSettingsError * peError);
	শূন্য (OPENVR_FNTABLE_CALLTYPE *SetString)(অক্ষর * pchSection, অক্ষর * pch_Settings_চাবি, অক্ষর * pch_মান, EVRSettingsError * peError);
	bool (OPENVR_FNTABLE_CALLTYPE *GetBool)(অক্ষর * pchSection, অক্ষর * pch_Settings_চাবি, EVRSettingsError * peError);
	int32_t (OPENVR_FNTABLE_CALLTYPE *GetInt32)(অক্ষর * pchSection, অক্ষর * pch_Settings_চাবি, EVRSettingsError * peError);
	দশমিক (OPENVR_FNTABLE_CALLTYPE *GetFloat)(অক্ষর * pchSection, অক্ষর * pch_Settings_চাবি, EVRSettingsError * peError);
	শূন্য (OPENVR_FNTABLE_CALLTYPE *GetString)(অক্ষর * pchSection, অক্ষর * pch_Settings_চাবি, অক্ষর * pch_মান, uint32_t un_মান_Len, EVRSettingsError * peError);
	শূন্য (OPENVR_FNTABLE_CALLTYPE *RemoveSection)(অক্ষর * pchSection, EVRSettingsError * peError);
	শূন্য (OPENVR_FNTABLE_CALLTYPE *Remove_চাবি_In_Section)(অক্ষর * pchSection, অক্ষর * pch_Settings_চাবি, EVRSettingsError * peError);
};

কাঠামো VR_IVRScreenshots_FnTable
{
	EVRScreenshotError (OPENVR_FNTABLE_CALLTYPE *RequestScreenshot)(ScreenshotHandle_t * pOutScreenshotHandle, EVRScreenshotType type, অক্ষর * pchPreviewFilename, অক্ষর * pchVRFilename);
	EVRScreenshotError (OPENVR_FNTABLE_CALLTYPE *HookScreenshot)(EVRScreenshotType * pSupportedTypes, পূর্ণসংখ্যা অঙ্ক_Types);
	EVRScreenshotType (OPENVR_FNTABLE_CALLTYPE *GetScreenshotPropertyType)(ScreenshotHandle_t screenshotHandle, EVRScreenshotError * pError);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetScreenshotPropertyFilename)(ScreenshotHandle_t screenshotHandle, EVRScreenshotPropertyFilenames filenameType, অক্ষর * pchFilename, uint32_t cchFilename, EVRScreenshotError * pError);
	EVRScreenshotError (OPENVR_FNTABLE_CALLTYPE *UpdateScreenshotProgress)(ScreenshotHandle_t screenshotHandle, দশমিক flProgress);
	EVRScreenshotError (OPENVR_FNTABLE_CALLTYPE *TakeStereoScreenshot)(ScreenshotHandle_t * pOutScreenshotHandle, অক্ষর * pchPreviewFilename, অক্ষর * pchVRFilename);
	EVRScreenshotError (OPENVR_FNTABLE_CALLTYPE *SubmitScreenshot)(ScreenshotHandle_t screenshotHandle, EVRScreenshotType type, অক্ষর * pchSourcePreviewFilename, অক্ষর * pchSourceVRFilename);
};

কাঠামো VR_IVRResources_FnTable
{
	uint32_t (OPENVR_FNTABLE_CALLTYPE *LoadSharedResource)(অক্ষর * pchResourceName, অক্ষর * pch_বাফার, uint32_t un_বাফার_Len);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetResourceFullPath)(অক্ষর * pchResourceName, অক্ষর * pchResourceTypeDirectory, অক্ষর * pch_Path_বাফার, uint32_t un_বাফার_Len);
};

কাঠামো VR_IVRDriverManager_FnTable
{
	uint32_t (OPENVR_FNTABLE_CALLTYPE *Get_Driver_গুনতি)();
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetDriverName)(DriverId_t nDriver, অক্ষর * pch_মান, uint32_t un_বাফার_আকার);
	DriverHandle_t (OPENVR_FNTABLE_CALLTYPE *GetDriverHandle)(অক্ষর * pchDriverName);
	bool (OPENVR_FNTABLE_CALLTYPE *IsEnabled)(DriverId_t nDriver);
};

কাঠামো VR_IVRInput_FnTable
{
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *SetActionManifestPath)(অক্ষর * pchActionManifestPath);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetActionSetHandle)(অক্ষর * pchActionSetName, VRActionSetHandle_t * pHandle);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetActionHandle)(অক্ষর * pchActionName, VRActionHandle_t * pHandle);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *Get_প্রবেশ_Source_Handle)(অক্ষর * pch_প্রবেশ_Source_Path, VRInput_মান_Handle_t * pHandle);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *UpdateActionState)(কাঠামো VRActiveActionSet_t * pSets, uint32_t un_আকার_Of_VRSelected_Action_Set_t, uint32_t un_Set_গুনতি);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *Get_Digital_Action_তথ্য)(VRActionHandle_t action, কাঠামো প্রবেশ_Digital_Action_তথ্য_t * p_Action_তথ্য, uint32_t un_Action_তথ্য_আকার, VRInput_মান_Handle_t ulRestrictToDevice);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *Get_Analog_Action_তথ্য)(VRActionHandle_t action, কাঠামো প্রবেশ_Analog_Action_তথ্য_t * p_Action_তথ্য, uint32_t un_Action_তথ্য_আকার, VRInput_মান_Handle_t ulRestrictToDevice);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *Get_Pose_Action_তথ্য_Relative_To_Now)(VRActionHandle_t action, ETrackingUniverseOrigin eOrigin, দশমিক fPredictedSecondsFromNow, কাঠামো প্রবেশ_Pose_Action_তথ্য_t * p_Action_তথ্য, uint32_t un_Action_তথ্য_আকার, VRInput_মান_Handle_t ulRestrictToDevice);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *Get_Pose_Action_তথ্য_For_পরবর্তী_Frame)(VRActionHandle_t action, ETrackingUniverseOrigin eOrigin, কাঠামো প্রবেশ_Pose_Action_তথ্য_t * p_Action_তথ্য, uint32_t un_Action_তথ্য_আকার, VRInput_মান_Handle_t ulRestrictToDevice);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *Get_Skeletal_Action_তথ্য)(VRActionHandle_t action, কাঠামো প্রবেশ_Skeletal_Action_তথ্য_t * p_Action_তথ্য, uint32_t un_Action_তথ্য_আকার);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetDominantHand)(ETrackedControllerRole * peDominantHand);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *SetDominantHand)(ETrackedControllerRole eDominantHand);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *Get_Bone_গুনতি)(VRActionHandle_t action, uint32_t * p_Bone_গুনতি);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetBoneHierarchy)(VRActionHandle_t action, Bone_সূচক_t * pParentIndices, uint32_t un_সূচক_Aray_গুনতি);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetBoneName)(VRActionHandle_t action, Bone_সূচক_t n_Bone_সূচক, অক্ষর * pchBoneName, uint32_t un_Name_বাফার_আকার);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetSkeletalReferenceTransforms)(VRActionHandle_t action, EVRSkeletalTransformSpace eTransformSpace, EVRSkeletalReferencePose eReferencePose, কাঠামো VRBoneTransform_t * pTransformArray, uint32_t un_Transform_Array_গুনতি);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetSkeletalTrackingLevel)(VRActionHandle_t action, EVRSkeletalTrackingLevel * pSkeletalTrackingLevel);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *Get_Skeletal_Bone_তথ্য)(VRActionHandle_t action, EVRSkeletalTransformSpace eTransformSpace, EVRSkeletalMotionRange eMotionRange, কাঠামো VRBoneTransform_t * pTransformArray, uint32_t un_Transform_Array_গুনতি);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *Get_Skeletal_Summary_তথ্য)(VRActionHandle_t action, EVRSummaryType eSummaryType, কাঠামো VRSkeletal_Summary_তথ্য_t * p_Skeletal_Summary_তথ্য);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *Get_Skeletal_Bone_তথ্য_Compressed)(VRActionHandle_t action, EVRSkeletalMotionRange eMotionRange, শূন্য * pv_Compressed_তথ্য, uint32_t un_Compressed_আকার, uint32_t * pun_Required_Compressed_আকার);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *Decompress_Skeletal_Bone_তথ্য)(শূন্য * pv_Compressed_বাফার, uint32_t un_Compressed_বাফার_আকার, EVRSkeletalTransformSpace eTransformSpace, কাঠামো VRBoneTransform_t * pTransformArray, uint32_t un_Transform_Array_গুনতি);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *TriggerHapticVibrationAction)(VRActionHandle_t action, দশমিক fStartSecondsFromNow, দশমিক fDurationSeconds, দশমিক fFrequency, দশমিক fAmplitude, VRInput_মান_Handle_t ulRestrictToDevice);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetActionOrigins)(VRActionSetHandle_t actionSetHandle, VRActionHandle_t digitalActionHandle, VRInput_মান_Handle_t * originsOut, uint32_t origin_Out_গুনতি);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetOriginLocalizedName)(VRInput_মান_Handle_t origin, অক্ষর * pchNameArray, uint32_t un_Name_Array_আকার, int32_t unStringSectionsToInclude);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetOriginTrackedDeviceInfo)(VRInput_মান_Handle_t origin, কাঠামো প্রবেশ_Origin_Info_t * pOriginInfo, uint32_t un_Origin_Info_আকার);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetActionBindingInfo)(VRActionHandle_t action, কাঠামো প্রবেশ_Binding_Info_t * pOriginInfo, uint32_t un_Binding_Info_আকার, uint32_t un_Binding_Info_গুনতি, uint32_t * pun_Returned_Binding_Info_গুনতি);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *ShowActionOrigins)(VRActionSetHandle_t actionSetHandle, VRActionHandle_t ulActionHandle);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *ShowBindingsForActionSet)(কাঠামো VRActiveActionSet_t * pSets, uint32_t un_আকার_Of_VRSelected_Action_Set_t, uint32_t un_Set_গুনতি, VRInput_মান_Handle_t originToHighlight);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetComponentStateForBinding)(অক্ষর * pchRenderModelName, অক্ষর * pchComponentName, কাঠামো প্রবেশ_Binding_Info_t * pOriginInfo, uint32_t un_Binding_Info_আকার, uint32_t un_Binding_Info_গুনতি, RenderModel_ComponentState_t * pComponentState);
	bool (OPENVR_FNTABLE_CALLTYPE *Is_Using_Legacy_প্রবেশ)();
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *OpenBindingUI)(অক্ষর * pch_App_চাবি, VRActionSetHandle_t ulActionSetHandle, VRInput_মান_Handle_t ulDeviceHandle, bool bShowOnDesktop);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetBindingVariant)(VRInput_মান_Handle_t ulDevicePath, অক্ষর * pchVariantArray, uint32_t un_Variant_Array_আকার);
};

কাঠামো VR_IVRIOBuffer_FnTable
{
	EIOBufferError (OPENVR_FNTABLE_CALLTYPE *Open)(অক্ষর * pchPath, EIOBufferMode mode, uint32_t un_Element_আকার, uint32_t unElements, IOBufferHandle_t * pul_বাফার);
	EIOBufferError (OPENVR_FNTABLE_CALLTYPE *Close)(IOBufferHandle_t ul_বাফার);
	EIOBufferError (OPENVR_FNTABLE_CALLTYPE *Read)(IOBufferHandle_t ul_বাফার, শূন্য * pDst, uint32_t unBytes, uint32_t * punRead);
	EIOBufferError (OPENVR_FNTABLE_CALLTYPE *Write)(IOBufferHandle_t ul_বাফার, শূন্য * pSrc, uint32_t unBytes);
	PropertyContainerHandle_t (OPENVR_FNTABLE_CALLTYPE *PropertyContainer)(IOBufferHandle_t ul_বাফার);
	bool (OPENVR_FNTABLE_CALLTYPE *HasReaders)(IOBufferHandle_t ul_বাফার);
};

কাঠামো VR_IVRSpatialAnchors_FnTable
{
	EVRSpatialAnchorError (OPENVR_FNTABLE_CALLTYPE *CreateSpatialAnchorFromDescriptor)(অক্ষর * pchDescriptor, SpatialAnchorHandle_t * pHandleOut);
	EVRSpatialAnchorError (OPENVR_FNTABLE_CALLTYPE *CreateSpatialAnchorFromPose)(Tracked_Device_সূচক_t un_Device_সূচক, ETrackingUniverseOrigin eOrigin, কাঠামো SpatialAnchorPose_t * pPose, SpatialAnchorHandle_t * pHandleOut);
	EVRSpatialAnchorError (OPENVR_FNTABLE_CALLTYPE *GetSpatialAnchorPose)(SpatialAnchorHandle_t unHandle, ETrackingUniverseOrigin eOrigin, কাঠামো SpatialAnchorPose_t * pPoseOut);
	EVRSpatialAnchorError (OPENVR_FNTABLE_CALLTYPE *GetSpatialAnchorDescriptor)(SpatialAnchorHandle_t unHandle, অক্ষর * pchDescriptorOut, uint32_t * pun_Descriptor_বাফার_Len_In_Out);
};

কাঠামো VR_IVRDebug_FnTable
{
	EVRDebugError (OPENVR_FNTABLE_CALLTYPE *EmitVrProfilerEvent)(অক্ষর * pchMessage);
	EVRDebugError (OPENVR_FNTABLE_CALLTYPE *BeginVrProfilerEvent)(VrProfilerEventHandle_t * pHandleOut);
	EVRDebugError (OPENVR_FNTABLE_CALLTYPE *FinishVrProfilerEvent)(VrProfilerEventHandle_t hHandle, অক্ষর * pchMessage);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *DriverDebugRequest)(Tracked_Device_সূচক_t un_Device_সূচক, অক্ষর * pchRequest, অক্ষর * pch_Response_বাফার, uint32_t un_Response_বাফার_আকার);
};

কাঠামো VR_IVRProperties_FnTable
{
	ETrackedPropertyError (OPENVR_FNTABLE_CALLTYPE *ReadPropertyBatch)(PropertyContainerHandle_t ulContainerHandle, কাঠামো PropertyRead_t * pBatch, uint32_t un_Batch_Entry_গুনতি);
	ETrackedPropertyError (OPENVR_FNTABLE_CALLTYPE *WritePropertyBatch)(PropertyContainerHandle_t ulContainerHandle, কাঠামো PropertyWrite_t * pBatch, uint32_t un_Batch_Entry_গুনতি);
	অক্ষর * (OPENVR_FNTABLE_CALLTYPE *GetPropErrorNameFromEnum)(ETrackedPropertyError error);
	PropertyContainerHandle_t (OPENVR_FNTABLE_CALLTYPE *TrackedDeviceToPropertyContainer)(Tracked_Device_সূচক_t nDevice);
};

কাঠামো VR_IVRPaths_FnTable
{
	ETrackedPropertyError (OPENVR_FNTABLE_CALLTYPE *ReadPathBatch)(PropertyContainerHandle_t ul_মূল_Handle, কাঠামো PathRead_t * pBatch, uint32_t un_Batch_Entry_গুনতি);
	ETrackedPropertyError (OPENVR_FNTABLE_CALLTYPE *WritePathBatch)(PropertyContainerHandle_t ul_মূল_Handle, কাঠামো PathWrite_t * pBatch, uint32_t un_Batch_Entry_গুনতি);
	ETrackedPropertyError (OPENVR_FNTABLE_CALLTYPE *StringToHandle)(PathHandle_t * pHandle, অক্ষর * pchPath);
	ETrackedPropertyError (OPENVR_FNTABLE_CALLTYPE *HandleToString)(PathHandle_t pHandle, অক্ষর * pch_বাফার, uint32_t un_বাফার_আকার, uint32_t * pun_বাফার_আকার_Used);
};

কাঠামো VR_IVRBlockQueue_FnTable
{
	EBlockQueueError (OPENVR_FNTABLE_CALLTYPE *Create)(PropertyContainerHandle_t * pulQueueHandle, অক্ষর * pchPath, uint32_t un_Block_তথ্য_আকার, uint32_t un_Block_Header_আকার, uint32_t un_Block_গুনতি, uint32_t unFlags);
	EBlockQueueError (OPENVR_FNTABLE_CALLTYPE *Connect)(PropertyContainerHandle_t * pulQueueHandle, অক্ষর * pchPath);
	EBlockQueueError (OPENVR_FNTABLE_CALLTYPE *Destroy)(PropertyContainerHandle_t ulQueueHandle);
	EBlockQueueError (OPENVR_FNTABLE_CALLTYPE *AcquireWriteOnlyBlock)(PropertyContainerHandle_t ulQueueHandle, PropertyContainerHandle_t * pulBlockHandle, শূন্য ** ppv_বাফার);
	EBlockQueueError (OPENVR_FNTABLE_CALLTYPE *ReleaseWriteOnlyBlock)(PropertyContainerHandle_t ulQueueHandle, PropertyContainerHandle_t ulBlockHandle);
	EBlockQueueError (OPENVR_FNTABLE_CALLTYPE *WaitAndAcquireReadOnlyBlock)(PropertyContainerHandle_t ulQueueHandle, PropertyContainerHandle_t * pulBlockHandle, শূন্য ** ppv_বাফার, EBlockQueueReadType eReadType, uint32_t unTimeoutMs);
	EBlockQueueError (OPENVR_FNTABLE_CALLTYPE *AcquireReadOnlyBlock)(PropertyContainerHandle_t ulQueueHandle, PropertyContainerHandle_t * pulBlockHandle, শূন্য ** ppv_বাফার, EBlockQueueReadType eReadType);
	EBlockQueueError (OPENVR_FNTABLE_CALLTYPE *ReleaseReadOnlyBlock)(PropertyContainerHandle_t ulQueueHandle, PropertyContainerHandle_t ulBlockHandle);
	EBlockQueueError (OPENVR_FNTABLE_CALLTYPE *QueueHasReader)(PropertyContainerHandle_t ulQueueHandle, bool * pbHasReaders);
};


#যদি 0
// Global entry points
S_API intptr_t VR_InitInternal( EVRInitError *peError, EVRApplicationType eType );
S_API শূন্য VR_ShutdownInternal();
S_API bool VR_IsHmdPresent();
S_API intptr_t VR_GetGenericInterface( ধ্রুবক অক্ষর *pchInterfaceVersion, EVRInitError *peError );
S_API bool VR_IsRuntimeInstalled();
S_API ধ্রুবক অক্ষর * VR_Get_VRInit_Error_As_প্রতীক( EVRInitError error );
S_API ধ্রুবক অক্ষর * VR_GetVRInitErrorAsEnglishDescription( EVRInitError error );
#endif

#endif // __OPENVR_API_FLAT_H__


