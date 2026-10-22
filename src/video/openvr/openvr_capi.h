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
#જો defined( _WIN32 ) || defined( __clang__ )
#pragma once
#endif

#ifdef __cplusplus
#define EXTERN_C બાહ્ય "C"
#નહીંતર
#define EXTERN_C
#endif

#જો defined( _WIN32 )
#define OPENVR_FNTABLE_CALLTYPE __stdcall
#નહીંતર
#define OPENVR_FNTABLE_CALLTYPE 
#endif

// OPENVR API export macro
#જો defined( _WIN32 ) && !defined( _X360 )
	#જો defined( OPENVR_API_EXPORTS )
	#define S_API EXTERN_C __declspec( dllexport )
	#અથવાજો defined( OPENVR_API_NODLL )
	#define S_API EXTERN_C
	#નહીંતર
	#define S_API બાહ્ય "C" __declspec( dllimport ) 
	#endif // OPENVR_API_EXPORTS
#અથવાજો defined( __GNUC__ )
	#જો defined( OPENVR_API_EXPORTS )
	#define S_API EXTERN_C __attribute__ ((visibility("default")))
	#નહીંતર
	#define S_API EXTERN_C
	#endif // OPENVR_API_EXPORTS
#નહીંતર // !WIN32
	#જો defined( OPENVR_API_EXPORTS )
	#define S_API EXTERN_C
	#નહીંતર
	#define S_API EXTERN_C
	#endif // OPENVR_API_EXPORTS
#endif

#ifndef USE_SDL
#અન્તર્ભાવ <stdint.h>

#જો defined( __WIN32 )
પ્રકારવ્યાખ્યા અક્ષર bool;
#નહીંતર
#અન્તર્ભાવ <stdbool.h>
#endif
#endif // USE_SDL

// OpenVR Constants

સ્થિર અચલ unsigned long k_nDriverNone = 4294967295;
સ્થિર અચલ unsigned long k_unMaxDriverDebugResponseSize = 32768;
સ્થિર અચલ unsigned long k_unTrackedDeviceIndex_Hmd = 0;
સ્થિર અચલ unsigned long k_un_Max_Tracked_Device_ગણતરી = 64;
સ્થિર અચલ unsigned long k_unTrackedDeviceIndexOther = 4294967294;
સ્થિર અચલ unsigned long k_unTrackedDeviceIndexInvalid = 4294967295;
સ્થિર અચલ unsigned long long k_ulInvalidPropertyContainer = 0;
સ્થિર અચલ unsigned long k_unInvalidPropertyTag = 0;
સ્થિર અચલ unsigned long long k_ulInvalidDriverHandle = 0;
સ્થિર અચલ unsigned long k_unFloatPropertyTag = 1;
સ્થિર અચલ unsigned long k_unInt32PropertyTag = 2;
સ્થિર અચલ unsigned long k_unUint64PropertyTag = 3;
સ્થિર અચલ unsigned long k_unBoolPropertyTag = 4;
સ્થિર અચલ unsigned long k_unStringPropertyTag = 5;
સ્થિર અચલ unsigned long k_unErrorPropertyTag = 6;
સ્થિર અચલ unsigned long k_unDoublePropertyTag = 7;
સ્થિર અચલ unsigned long k_unHmdMatrix34PropertyTag = 20;
સ્થિર અચલ unsigned long k_unHmdMatrix44PropertyTag = 21;
સ્થિર અચલ unsigned long k_unHmdVector3PropertyTag = 22;
સ્થિર અચલ unsigned long k_unHmdVector4PropertyTag = 23;
સ્થિર અચલ unsigned long k_unHmdVector2PropertyTag = 24;
સ્થિર અચલ unsigned long k_unHmdQuadPropertyTag = 25;
સ્થિર અચલ unsigned long k_unHiddenAreaPropertyTag = 30;
સ્થિર અચલ unsigned long k_unPathHandleInfoTag = 31;
સ્થિર અચલ unsigned long k_unActionPropertyTag = 32;
સ્થિર અચલ unsigned long k_un_આગત_કિંમત_Property_Tag = 33;
સ્થિર અચલ unsigned long k_unWildcardPropertyTag = 34;
સ્થિર અચલ unsigned long k_unHapticVibrationPropertyTag = 35;
સ્થિર અચલ unsigned long k_unSkeletonPropertyTag = 36;
સ્થિર અચલ unsigned long k_unSpatialAnchorPosePropertyTag = 40;
સ્થિર અચલ unsigned long k_unJsonPropertyTag = 41;
સ્થિર અચલ unsigned long k_unActiveActionSetPropertyTag = 42;
સ્થિર અચલ unsigned long k_unOpenVRInternalReserved_Start = 1000;
સ્થિર અચલ unsigned long k_unOpenVRInternalReserved_End = 10000;
સ્થિર અચલ unsigned long k_unMaxPropertyStringSize = 32768;
સ્થિર અચલ unsigned long long k_ulInvalidActionHandle = 0;
સ્થિર અચલ unsigned long long k_ulInvalidActionSetHandle = 0;
સ્થિર અચલ unsigned long long k_ul_Invalid_આગત_કિંમત_Handle = 0;
સ્થિર અચલ unsigned long k_un_Controller_State_Axis_ગણતરી = 5;
સ્થિર અચલ unsigned long long k_ulOverlayHandleInvalid = 0;
સ્થિર અચલ unsigned long k_unMaxDistortionFunctionParameters = 8;
સ્થિર અચલ unsigned long k_unScreenshotHandleInvalid = 0;
સ્થિર અચલ અક્ષર * IVRSystem_Version = "IVRSystem_022";
સ્થિર અચલ અક્ષર * IVRExtendedDisplay_Version = "IVRExtendedDisplay_001";
સ્થિર અચલ અક્ષર * IVRTrackedCamera_Version = "IVRTrackedCamera_006";
સ્થિર અચલ unsigned long k_un_Max_Application_ચાવી_Length = 128;
સ્થિર અચલ અક્ષર * k_pch_MimeType_HomeApp = "vr/home";
સ્થિર અચલ અક્ષર * k_pch_MimeType_GameTheater = "vr/game_theater";
સ્થિર અચલ અક્ષર * IVRApplications_Version = "IVRApplications_007";
સ્થિર અચલ અક્ષર * IVRChaperone_Version = "IVRChaperone_004";
સ્થિર અચલ અક્ષર * IVRChaperoneSetup_Version = "IVRChaperoneSetup_006";
સ્થિર અચલ અક્ષર * IVRCompositor_Version = "IVRCompositor_027";
સ્થિર અચલ unsigned long k_un_VROverlay_Max_ચાવી_Length = 128;
સ્થિર અચલ unsigned long k_unVROverlayMaxNameLength = 128;
સ્થિર અચલ unsigned long k_un_Max_Overlay_ગણતરી = 128;
સ્થિર અચલ unsigned long k_un_Max_Overlay_Intersection_Mask_Primitives_ગણતરી = 32;
સ્થિર અચલ અક્ષર * IVROverlay_Version = "IVROverlay_026";
સ્થિર અચલ અક્ષર * IVROverlayView_Version = "IVROverlayView_003";
સ્થિર અચલ unsigned long k_unHeadsetViewMaxWidth = 3840;
સ્થિર અચલ unsigned long k_unHeadsetViewMaxHeight = 2160;
સ્થિર અચલ અક્ષર * k_pch_Headset_View_Overlay_ચાવી = "system.HeadsetView";
સ્થિર અચલ અક્ષર * IVRHeadsetView_Version = "IVRHeadsetView_001";
સ્થિર અચલ અક્ષર * k_pch_Controller_Component_GDC2015 = "gdc2015";
સ્થિર અચલ અક્ષર * k_pch_Controller_Component_Base = "base";
સ્થિર અચલ અક્ષર * k_pch_Controller_Component_Tip = "tip";
સ્થિર અચલ અક્ષર * k_pch_Controller_Component_OpenXR_Aim = "openxr_aim";
સ્થિર અચલ અક્ષર * k_pch_Controller_Component_HandGrip = "handgrip";
સ્થિર અચલ અક્ષર * k_pch_Controller_Component_OpenXR_Grip = "openxr_grip";
સ્થિર અચલ અક્ષર * k_pch_Controller_Component_OpenXR_HandModel = "openxr_handmodel";
સ્થિર અચલ અક્ષર * k_pch_Controller_Component_Status = "status";
સ્થિર અચલ અક્ષર * IVRRenderModels_Version = "IVRRenderModels_006";
સ્થિર અચલ unsigned long k_unNotificationTextMaxSize = 256;
સ્થિર અચલ અક્ષર * IVRNotifications_Version = "IVRNotifications_002";
સ્થિર અચલ unsigned long k_un_Max_Settings_ચાવી_Length = 128;
સ્થિર અચલ અક્ષર * IVRSettings_Version = "IVRSettings_003";
સ્થિર અચલ અક્ષર * k_pch_SteamVR_Section = "steamvr";
સ્થિર અચલ અક્ષર * k_pch_SteamVR_RequireHmd_String = "requireHmd";
સ્થિર અચલ અક્ષર * k_pch_Steam_VR_Forced_Driver_ચાવી_String = "forcedDriver";
સ્થિર અચલ અક્ષર * k_pch_Steam_VR_Forced_Hmd_ચાવી_String = "forcedHmd";
સ્થિર અચલ અક્ષર * k_pch_SteamVR_DisplayDebug_Bool = "displayDebug";
સ્થિર અચલ અક્ષર * k_pch_SteamVR_DebugProcessPipe_String = "debugProcessPipe";
સ્થિર અચલ અક્ષર * k_pch_SteamVR_DisplayDebugX_Int32 = "displayDebugX";
સ્થિર અચલ અક્ષર * k_pch_SteamVR_DisplayDebugY_Int32 = "displayDebugY";
સ્થિર અચલ અક્ષર * k_pch_SteamVR_SendSystemButtonToAllApps_Bool = "sendSystemButtonToAllApps";
સ્થિર અચલ અક્ષર * k_pch_SteamVR_LogLevel_Int32 = "loglevel";
સ્થિર અચલ અક્ષર * k_pch_SteamVR_IPD_Float = "ipd";
સ્થિર અચલ અક્ષર * k_pch_SteamVR_Background_String = "background";
સ્થિર અચલ અક્ષર * k_pch_SteamVR_BackgroundUseDomeProjection_Bool = "backgroundUseDomeProjection";
સ્થિર અચલ અક્ષર * k_pch_SteamVR_BackgroundCameraHeight_Float = "backgroundCameraHeight";
સ્થિર અચલ અક્ષર * k_pch_SteamVR_BackgroundDomeRadius_Float = "backgroundDomeRadius";
સ્થિર અચલ અક્ષર * k_pch_SteamVR_GridColor_String = "gridColor";
સ્થિર અચલ અક્ષર * k_pch_SteamVR_PlayAreaColor_String = "playAreaColor";
સ્થિર અચલ અક્ષર * k_pch_SteamVR_TrackingLossColor_String = "trackingLossColor";
સ્થિર અચલ અક્ષર * k_pch_SteamVR_ShowStage_Bool = "showStage";
સ્થિર અચલ અક્ષર * k_pch_SteamVR_DrawTrackingReferences_Bool = "drawTrackingReferences";
સ્થિર અચલ અક્ષર * k_pch_SteamVR_ActivateMultipleDrivers_Bool = "activateMultipleDrivers";
સ્થિર અચલ અક્ષર * k_pch_SteamVR_UsingSpeakers_Bool = "usingSpeakers";
સ્થિર અચલ અક્ષર * k_pch_SteamVR_SpeakersForwardYawOffsetDegrees_Float = "speakersForwardYawOffsetDegrees";
સ્થિર અચલ અક્ષર * k_pch_SteamVR_BaseStationPowerManagement_Int32 = "basestationPowerManagement";
સ્થિર અચલ અક્ષર * k_pch_SteamVR_ShowBaseStationPowerManagementTip_Int32 = "ShowBaseStationPowerManagementTip";
સ્થિર અચલ અક્ષર * k_pch_SteamVR_NeverKillProcesses_Bool = "neverKillProcesses";
સ્થિર અચલ અક્ષર * k_pch_SteamVR_SupersampleScale_Float = "supersampleScale";
સ્થિર અચલ અક્ષર * k_pch_SteamVR_MaxRecommendedResolution_Int32 = "maxRecommendedResolution";
સ્થિર અચલ અક્ષર * k_pch_SteamVR_MotionSmoothing_Bool = "motionSmoothing";
સ્થિર અચલ અક્ષર * k_pch_SteamVR_MotionSmoothingOverride_Int32 = "motionSmoothingOverride";
સ્થિર અચલ અક્ષર * k_pch_SteamVR_FramesToThrottle_Int32 = "framesToThrottle";
સ્થિર અચલ અક્ષર * k_pch_SteamVR_AdditionalFramesToPredict_Int32 = "additionalFramesToPredict";
સ્થિર અચલ અક્ષર * k_pch_SteamVR_WorldScale_Float = "worldScale";
સ્થિર અચલ અક્ષર * k_pch_SteamVR_FovScale_Int32 = "fovScale";
સ્થિર અચલ અક્ષર * k_pch_SteamVR_DisableAsyncReprojection_Bool = "disableAsync";
સ્થિર અચલ અક્ષર * k_pch_SteamVR_ForceFadeOnBadTracking_Bool = "forceFadeOnBadTracking";
સ્થિર અચલ અક્ષર * k_pch_SteamVR_DefaultMirrorView_Int32 = "mirrorView";
સ્થિર અચલ અક્ષર * k_pch_SteamVR_ShowLegacyMirrorView_Bool = "showLegacyMirrorView";
સ્થિર અચલ અક્ષર * k_pch_SteamVR_MirrorViewVisibility_Bool = "showMirrorView";
સ્થિર અચલ અક્ષર * k_pch_SteamVR_MirrorViewDisplayMode_Int32 = "mirrorViewDisplayMode";
સ્થિર અચલ અક્ષર * k_pch_SteamVR_MirrorViewEye_Int32 = "mirrorViewEye";
સ્થિર અચલ અક્ષર * k_pch_SteamVR_MirrorViewGeometry_String = "mirrorViewGeometry";
સ્થિર અચલ અક્ષર * k_pch_SteamVR_MirrorViewGeometryMaximized_String = "mirrorViewGeometryMaximized";
સ્થિર અચલ અક્ષર * k_pch_SteamVR_PerfGraphVisibility_Bool = "showPerfGraph";
સ્થિર અચલ અક્ષર * k_pch_SteamVR_StartMonitorFromAppLaunch = "startMonitorFromAppLaunch";
સ્થિર અચલ અક્ષર * k_pch_SteamVR_StartCompositorFromAppLaunch_Bool = "startCompositorFromAppLaunch";
સ્થિર અચલ અક્ષર * k_pch_SteamVR_StartDashboardFromAppLaunch_Bool = "startDashboardFromAppLaunch";
સ્થિર અચલ અક્ષર * k_pch_SteamVR_StartOverlayAppsFromDashboard_Bool = "startOverlayAppsFromDashboard";
સ્થિર અચલ અક્ષર * k_pch_SteamVR_EnableHomeApp = "enableHomeApp";
સ્થિર અચલ અક્ષર * k_pch_SteamVR_CycleBackgroundImageTimeSec_Int32 = "CycleBackgroundImageTimeSec";
સ્થિર અચલ અક્ષર * k_pch_SteamVR_RetailDemo_Bool = "retailDemo";
સ્થિર અચલ અક્ષર * k_pch_SteamVR_IpdOffset_Float = "ipdOffset";
સ્થિર અચલ અક્ષર * k_pch_SteamVR_AllowSupersampleFiltering_Bool = "allowSupersampleFiltering";
સ્થિર અચલ અક્ષર * k_pch_SteamVR_SupersampleManualOverride_Bool = "supersampleManualOverride";
સ્થિર અચલ અક્ષર * k_pch_SteamVR_EnableLinuxVulkanAsync_Bool = "enableLinuxVulkanAsync";
સ્થિર અચલ અક્ષર * k_pch_SteamVR_AllowDisplayLockedMode_Bool = "allowDisplayLockedMode";
સ્થિર અચલ અક્ષર * k_pch_SteamVR_HaveStartedTutorialForNativeChaperoneDriver_Bool = "haveStartedTutorialForNativeChaperoneDriver";
સ્થિર અચલ અક્ષર * k_pch_SteamVR_ForceWindows32bitVRMonitor = "forceWindows32BitVRMonitor";
સ્થિર અચલ અક્ષર * k_pch_Steam_VR_Debug_આગત_Binding = "debugInputBinding";
સ્થિર અચલ અક્ષર * k_pch_SteamVR_DoNotFadeToGrid = "doNotFadeToGrid";
સ્થિર અચલ અક્ષર * k_pch_SteamVR_RenderCameraMode = "renderCameraMode";
સ્થિર અચલ અક્ષર * k_pch_SteamVR_EnableSharedResourceJournaling = "enableSharedResourceJournaling";
સ્થિર અચલ અક્ષર * k_pch_SteamVR_EnableSafeMode = "enableSafeMode";
સ્થિર અચલ અક્ષર * k_pch_SteamVR_PreferredRefreshRate = "preferredRefreshRate";
સ્થિર અચલ અક્ષર * k_pch_SteamVR_LastVersionNotice = "lastVersionNotice";
સ્થિર અચલ અક્ષર * k_pch_SteamVR_LastVersionNoticeDate = "lastVersionNoticeDate";
સ્થિર અચલ અક્ષર * k_pch_SteamVR_HmdDisplayColorGainR_Float = "hmdDisplayColorGainR";
સ્થિર અચલ અક્ષર * k_pch_SteamVR_HmdDisplayColorGainG_Float = "hmdDisplayColorGainG";
સ્થિર અચલ અક્ષર * k_pch_SteamVR_HmdDisplayColorGainB_Float = "hmdDisplayColorGainB";
સ્થિર અચલ અક્ષર * k_pch_SteamVR_CustomIconStyle_String = "customIconStyle";
સ્થિર અચલ અક્ષર * k_pch_SteamVR_CustomOffIconStyle_String = "customOffIconStyle";
સ્થિર અચલ અક્ષર * k_pch_SteamVR_CustomIconForceUpdate_String = "customIconForceUpdate";
સ્થિર અચલ અક્ષર * k_pch_SteamVR_AllowGlobalActionSetPriority = "globalActionSetPriority";
સ્થિર અચલ અક્ષર * k_pch_SteamVR_OverlayRenderQuality = "overlayRenderQuality_2";
સ્થિર અચલ અક્ષર * k_pch_SteamVR_BlockOculusSDKOnOpenVRLaunchOption_Bool = "blockOculusSDKOnOpenVRLaunchOption";
સ્થિર અચલ અક્ષર * k_pch_SteamVR_BlockOculusSDKOnAllLaunches_Bool = "blockOculusSDKOnAllLaunches";
સ્થિર અચલ અક્ષર * k_pch_SteamVR_HDCPLegacyCompatibility_Bool = "hdcp14legacyCompatibility";
સ્થિર અચલ અક્ષર * k_pch_SteamVR_DisplayPortTrainingMode_Int = "displayPortTrainingMode";
સ્થિર અચલ અક્ષર * k_pch_SteamVR_UsePrism_Bool = "usePrism";
સ્થિર અચલ અક્ષર * k_pch_DirectMode_Section = "direct_mode";
સ્થિર અચલ અક્ષર * k_pch_DirectMode_Enable_Bool = "enable";
સ્થિર અચલ અક્ષર * k_pch_Direct_Mode_ગણતરી_Int32 = "count";
સ્થિર અચલ અક્ષર * k_pch_DirectMode_EdidVid_Int32 = "edidVid";
સ્થિર અચલ અક્ષર * k_pch_DirectMode_EdidPid_Int32 = "edidPid";
સ્થિર અચલ અક્ષર * k_pch_Lighthouse_Section = "driver_lighthouse";
સ્થિર અચલ અક્ષર * k_pch_Lighthouse_DisableIMU_Bool = "disableimu";
સ્થિર અચલ અક્ષર * k_pch_Lighthouse_DisableIMUExceptHMD_Bool = "disableimuexcepthmd";
સ્થિર અચલ અક્ષર * k_pch_Lighthouse_UseDisambiguation_String = "usedisambiguation";
સ્થિર અચલ અક્ષર * k_pch_Lighthouse_DisambiguationDebug_Int32 = "disambiguationdebug";
સ્થિર અચલ અક્ષર * k_pch_Lighthouse_PrimaryBasestation_Int32 = "primarybasestation";
સ્થિર અચલ અક્ષર * k_pch_Lighthouse_DBHistory_Bool = "dbhistory";
સ્થિર અચલ અક્ષર * k_pch_Lighthouse_EnableBluetooth_Bool = "enableBluetooth";
સ્થિર અચલ અક્ષર * k_pch_Lighthouse_PowerManagedBaseStations_String = "PowerManagedBaseStations";
સ્થિર અચલ અક્ષર * k_pch_Lighthouse_PowerManagedBaseStations2_String = "PowerManagedBaseStations2";
સ્થિર અચલ અક્ષર * k_pch_Lighthouse_InactivityTimeoutForBaseStations_Int32 = "InactivityTimeoutForBaseStations";
સ્થિર અચલ અક્ષર * k_pch_Lighthouse_EnableImuFallback_Bool = "enableImuFallback";
સ્થિર અચલ અક્ષર * k_pch_Null_Section = "driver_null";
સ્થિર અચલ અક્ષર * k_pch_Null_Serial_સંખ્યા_String = "serialNumber";
સ્થિર અચલ અક્ષર * k_pch_Null_Model_સંખ્યા_String = "modelNumber";
સ્થિર અચલ અક્ષર * k_pch_Null_WindowX_Int32 = "windowX";
સ્થિર અચલ અક્ષર * k_pch_Null_WindowY_Int32 = "windowY";
સ્થિર અચલ અક્ષર * k_pch_Null_WindowWidth_Int32 = "windowWidth";
સ્થિર અચલ અક્ષર * k_pch_Null_WindowHeight_Int32 = "windowHeight";
સ્થિર અચલ અક્ષર * k_pch_Null_RenderWidth_Int32 = "renderWidth";
સ્થિર અચલ અક્ષર * k_pch_Null_RenderHeight_Int32 = "renderHeight";
સ્થિર અચલ અક્ષર * k_pch_Null_SecondsFromVsyncToPhotons_Float = "secondsFromVsyncToPhotons";
સ્થિર અચલ અક્ષર * k_pch_Null_DisplayFrequency_Float = "displayFrequency";
સ્થિર અચલ અક્ષર * k_pch_WindowsMR_Section = "driver_holographic";
સ્થિર અચલ અક્ષર * k_pch_UserInterface_Section = "userinterface";
સ્થિર અચલ અક્ષર * k_pch_User_Interface_Status_Always_On_ટોચ_Bool = "StatusAlwaysOnTop";
સ્થિર અચલ અક્ષર * k_pch_UserInterface_MinimizeToTray_Bool = "MinimizeToTray";
સ્થિર અચલ અક્ષર * k_pch_UserInterface_HidePopupsWhenStatusMinimized_Bool = "HidePopupsWhenStatusMinimized";
સ્થિર અચલ અક્ષર * k_pch_UserInterface_Screenshots_Bool = "screenshots";
સ્થિર અચલ અક્ષર * k_pch_UserInterface_ScreenshotType_Int = "screenshotType";
સ્થિર અચલ અક્ષર * k_pch_Notifications_Section = "notifications";
સ્થિર અચલ અક્ષર * k_pch_Notifications_DoNotDisturb_Bool = "DoNotDisturb";
સ્થિર અચલ અક્ષર * k_pch_Keyboard_Section = "keyboard";
સ્થિર અચલ અક્ષર * k_pch_Keyboard_TutorialCompletions = "TutorialCompletions";
સ્થિર અચલ અક્ષર * k_pch_Keyboard_ScaleX = "ScaleX";
સ્થિર અચલ અક્ષર * k_pch_Keyboard_ScaleY = "ScaleY";
સ્થિર અચલ અક્ષર * k_pch_Keyboard_Offset_ડાબું_X = "OffsetLeftX";
સ્થિર અચલ અક્ષર * k_pch_Keyboard_Offset_જમણું_X = "OffsetRightX";
સ્થિર અચલ અક્ષર * k_pch_Keyboard_OffsetY = "OffsetY";
સ્થિર અચલ અક્ષર * k_pch_Keyboard_Smoothing = "Smoothing";
સ્થિર અચલ અક્ષર * k_pch_Perf_Section = "perfcheck";
સ્થિર અચલ અક્ષર * k_pch_Perf_PerfGraphInHMD_Bool = "perfGraphInHMD";
સ્થિર અચલ અક્ષર * k_pch_Perf_AllowTimingStore_Bool = "allowTimingStore";
સ્થિર અચલ અક્ષર * k_pch_Perf_SaveTimingsOnExit_Bool = "saveTimingsOnExit";
સ્થિર અચલ અક્ષર * k_pch_Perf_TestData_Float = "perfTestData";
સ્થિર અચલ અક્ષર * k_pch_Perf_GPUProfiling_Bool = "GPUProfiling";
સ્થિર અચલ અક્ષર * k_pch_CollisionBounds_Section = "collisionBounds";
સ્થિર અચલ અક્ષર * k_pch_CollisionBounds_Style_Int32 = "CollisionBoundsStyle";
સ્થિર અચલ અક્ષર * k_pch_CollisionBounds_GroundPerimeterOn_Bool = "CollisionBoundsGroundPerimeterOn";
સ્થિર અચલ અક્ષર * k_pch_CollisionBounds_CenterMarkerOn_Bool = "CollisionBoundsCenterMarkerOn";
સ્થિર અચલ અક્ષર * k_pch_CollisionBounds_PlaySpaceOn_Bool = "CollisionBoundsPlaySpaceOn";
સ્થિર અચલ અક્ષર * k_pch_CollisionBounds_FadeDistance_Float = "CollisionBoundsFadeDistance";
સ્થિર અચલ અક્ષર * k_pch_CollisionBounds_WallHeight_Float = "CollisionBoundsWallHeight";
સ્થિર અચલ અક્ષર * k_pch_CollisionBounds_ColorGammaR_Int32 = "CollisionBoundsColorGammaR";
સ્થિર અચલ અક્ષર * k_pch_CollisionBounds_ColorGammaG_Int32 = "CollisionBoundsColorGammaG";
સ્થિર અચલ અક્ષર * k_pch_CollisionBounds_ColorGammaB_Int32 = "CollisionBoundsColorGammaB";
સ્થિર અચલ અક્ષર * k_pch_CollisionBounds_ColorGammaA_Int32 = "CollisionBoundsColorGammaA";
સ્થિર અચલ અક્ષર * k_pch_CollisionBounds_EnableDriverImport = "enableDriverBoundsImport";
સ્થિર અચલ અક્ષર * k_pch_Camera_Section = "camera";
સ્થિર અચલ અક્ષર * k_pch_Camera_EnableCamera_Bool = "enableCamera";
સ્થિર અચલ અક્ષર * k_pch_Camera_ShowOnController_Bool = "showOnController";
સ્થિર અચલ અક્ષર * k_pch_Camera_EnableCameraForCollisionBounds_Bool = "enableCameraForCollisionBounds";
સ્થિર અચલ અક્ષર * k_pch_Camera_RoomView_Int32 = "roomView";
સ્થિર અચલ અક્ષર * k_pch_Camera_BoundsColorGammaR_Int32 = "cameraBoundsColorGammaR";
સ્થિર અચલ અક્ષર * k_pch_Camera_BoundsColorGammaG_Int32 = "cameraBoundsColorGammaG";
સ્થિર અચલ અક્ષર * k_pch_Camera_BoundsColorGammaB_Int32 = "cameraBoundsColorGammaB";
સ્થિર અચલ અક્ષર * k_pch_Camera_BoundsColorGammaA_Int32 = "cameraBoundsColorGammaA";
સ્થિર અચલ અક્ષર * k_pch_Camera_BoundsStrength_Int32 = "cameraBoundsStrength";
સ્થિર અચલ અક્ષર * k_pch_Camera_RoomViewStyle_Int32 = "roomViewStyle";
સ્થિર અચલ અક્ષર * k_pch_audio_Section = "audio";
સ્થિર અચલ અક્ષર * k_pch_audio_SetOsDefaultPlaybackDevice_Bool = "setOsDefaultPlaybackDevice";
સ્થિર અચલ અક્ષર * k_pch_audio_EnablePlaybackDeviceOverride_Bool = "enablePlaybackDeviceOverride";
સ્થિર અચલ અક્ષર * k_pch_audio_PlaybackDeviceOverride_String = "playbackDeviceOverride";
સ્થિર અચલ અક્ષર * k_pch_audio_PlaybackDeviceOverrideName_String = "playbackDeviceOverrideName";
સ્થિર અચલ અક્ષર * k_pch_audio_SetOsDefaultRecordingDevice_Bool = "setOsDefaultRecordingDevice";
સ્થિર અચલ અક્ષર * k_pch_audio_EnableRecordingDeviceOverride_Bool = "enableRecordingDeviceOverride";
સ્થિર અચલ અક્ષર * k_pch_audio_RecordingDeviceOverride_String = "recordingDeviceOverride";
સ્થિર અચલ અક્ષર * k_pch_audio_RecordingDeviceOverrideName_String = "recordingDeviceOverrideName";
સ્થિર અચલ અક્ષર * k_pch_audio_EnablePlaybackMirror_Bool = "enablePlaybackMirror";
સ્થિર અચલ અક્ષર * k_pch_audio_PlaybackMirrorDevice_String = "playbackMirrorDevice";
સ્થિર અચલ અક્ષર * k_pch_audio_PlaybackMirrorDeviceName_String = "playbackMirrorDeviceName";
સ્થિર અચલ અક્ષર * k_pch_audio_OldPlaybackMirrorDevice_String = "onPlaybackMirrorDevice";
સ્થિર અચલ અક્ષર * k_pch_audio_ActiveMirrorDevice_String = "activePlaybackMirrorDevice";
સ્થિર અચલ અક્ષર * k_pch_audio_EnablePlaybackMirrorIndependentVolume_Bool = "enablePlaybackMirrorIndependentVolume";
સ્થિર અચલ અક્ષર * k_pch_audio_LastHmdPlaybackDeviceId_String = "lastHmdPlaybackDeviceId";
સ્થિર અચલ અક્ષર * k_pch_audio_VIVEHDMIGain = "viveHDMIGain";
સ્થિર અચલ અક્ષર * k_pch_audio_DualSpeakerAndJackOutput_Bool = "dualSpeakerAndJackOutput";
સ્થિર અચલ અક્ષર * k_pch_audio_MuteMicMonitor_Bool = "muteMicMonitor";
સ્થિર અચલ અક્ષર * k_pch_Power_Section = "power";
સ્થિર અચલ અક્ષર * k_pch_Power_PowerOffOnExit_Bool = "powerOffOnExit";
સ્થિર અચલ અક્ષર * k_pch_Power_TurnOffScreensTimeout_Float = "turnOffScreensTimeout";
સ્થિર અચલ અક્ષર * k_pch_Power_TurnOffControllersTimeout_Float = "turnOffControllersTimeout";
સ્થિર અચલ અક્ષર * k_pch_Power_ReturnToWatchdogTimeout_Float = "returnToWatchdogTimeout";
સ્થિર અચલ અક્ષર * k_pch_Power_AutoLaunchSteamVROnButtonPress = "autoLaunchSteamVROnButtonPress";
સ્થિર અચલ અક્ષર * k_pch_Power_PauseCompositorOnStandby_Bool = "pauseCompositorOnStandby";
સ્થિર અચલ અક્ષર * k_pch_Dashboard_Section = "dashboard";
સ્થિર અચલ અક્ષર * k_pch_Dashboard_EnableDashboard_Bool = "enableDashboard";
સ્થિર અચલ અક્ષર * k_pch_Dashboard_ArcadeMode_Bool = "arcadeMode";
સ્થિર અચલ અક્ષર * k_pch_Dashboard_Position = "position";
સ્થિર અચલ અક્ષર * k_pch_Dashboard_DesktopScale = "desktopScale";
સ્થિર અચલ અક્ષર * k_pch_Dashboard_DashboardScale = "dashboardScale";
સ્થિર અચલ અક્ષર * k_pch_Dashboard_UseStandaloneSystemLayer = "standaloneSystemLayer";
સ્થિર અચલ અક્ષર * k_pch_Dashboard_StickyDashboard = "stickyDashboard";
સ્થિર અચલ અક્ષર * k_pch_modelskin_Section = "modelskins";
સ્થિર અચલ અક્ષર * k_pch_Driver_Enable_Bool = "enable";
સ્થિર અચલ અક્ષર * k_pch_Driver_BlockedBySafemode_Bool = "blocked_by_safe_mode";
સ્થિર અચલ અક્ષર * k_pch_Driver_LoadPriority_Int32 = "loadPriority";
સ્થિર અચલ અક્ષર * k_pch_WebInterface_Section = "WebInterface";
સ્થિર અચલ અક્ષર * k_pch_VRWebHelper_Section = "VRWebHelper";
સ્થિર અચલ અક્ષર * k_pch_VRWebHelper_DebuggerEnabled_Bool = "DebuggerEnabled";
સ્થિર અચલ અક્ષર * k_pch_VRWebHelper_DebuggerPort_Int32 = "DebuggerPort";
સ્થિર અચલ અક્ષર * k_pch_TrackingOverride_Section = "TrackingOverrides";
સ્થિર અચલ અક્ષર * k_pch_App_BindingAutosaveURLSuffix_String = "AutosaveURL";
સ્થિર અચલ અક્ષર * k_pch_App_BindingLegacyAPISuffix_String = "_legacy";
સ્થિર અચલ અક્ષર * k_pch_App_BindingSteamVRInputAPISuffix_String = "_steamvrinput";
સ્થિર અચલ અક્ષર * k_pch_App_BindingOpenXRAPISuffix_String = "_openxr";
સ્થિર અચલ અક્ષર * k_pch_App_BindingCurrentURLSuffix_String = "CurrentURL";
સ્થિર અચલ અક્ષર * k_pch_App_BindingPreviousURLSuffix_String = "PreviousURL";
સ્થિર અચલ અક્ષર * k_pch_App_NeedToUpdateAutosaveSuffix_Bool = "NeedToUpdateAutosave";
સ્થિર અચલ અક્ષર * k_pch_App_DominantHand_Int32 = "DominantHand";
સ્થિર અચલ અક્ષર * k_pch_App_BlockOculusSDK_Bool = "blockOculusSDK";
સ્થિર અચલ અક્ષર * k_pch_Trackers_Section = "trackers";
સ્થિર અચલ અક્ષર * k_pch_DesktopUI_Section = "DesktopUI";
સ્થિર અચલ અક્ષર * k_pch_LastKnown_Section = "LastKnown";
સ્થિર અચલ અક્ષર * k_pch_LastKnown_HMDManufacturer_String = "HMDManufacturer";
સ્થિર અચલ અક્ષર * k_pch_LastKnown_HMDModel_String = "HMDModel";
સ્થિર અચલ અક્ષર * k_pch_DismissedWarnings_Section = "DismissedWarnings";
સ્થિર અચલ અક્ષર * k_pch_આગત_Section = "input";
સ્થિર અચલ અક્ષર * k_pch_આગત_ડાબું_Thumbstick_Rotation_Float = "leftThumbstickRotation";
સ્થિર અચલ અક્ષર * k_pch_આગત_જમણું_Thumbstick_Rotation_Float = "rightThumbstickRotation";
સ્થિર અચલ અક્ષર * k_pch_આગત_Thumbstick_Deadzone_Float = "thumbstickDeadzone";
સ્થિર અચલ અક્ષર * k_pch_GpuSpeed_Section = "GpuSpeed";
સ્થિર અચલ અક્ષર * IVRScreenshots_Version = "IVRScreenshots_001";
સ્થિર અચલ અક્ષર * IVRResources_Version = "IVRResources_001";
સ્થિર અચલ અક્ષર * IVRDriverManager_Version = "IVRDriverManager_001";
સ્થિર અચલ unsigned long k_unMaxActionNameLength = 64;
સ્થિર અચલ unsigned long k_unMaxActionSetNameLength = 64;
સ્થિર અચલ unsigned long k_un_Max_Action_Origin_ગણતરી = 16;
સ્થિર અચલ unsigned long k_unMaxBoneNameLength = 32;
સ્થિર અચલ પૂર્ણાંક k_nActionSetOverlayGlobalPriorityMin = 16777216;
સ્થિર અચલ પૂર્ણાંક k_nActionSetOverlayGlobalPriorityMax = 33554431;
સ્થિર અચલ પૂર્ણાંક k_nActionSetPriorityReservedMin = 33554432;
સ્થિર અચલ અક્ષર * IVRInput_Version = "IVRInput_010";
સ્થિર અચલ unsigned long long k_ulInvalidIOBufferHandle = 0;
સ્થિર અચલ અક્ષર * IVRIOBuffer_Version = "IVRIOBuffer_002";
સ્થિર અચલ unsigned long k_ulInvalidSpatialAnchorHandle = 0;
સ્થિર અચલ અક્ષર * IVRSpatialAnchors_Version = "IVRSpatialAnchors_001";
સ્થિર અચલ અક્ષર * IVRDebug_Version = "IVRDebug_001";
સ્થિર અચલ unsigned long long k_ulDisplayRedirectContainer = 25769803779;
સ્થિર અચલ અક્ષર * IVRProperties_Version = "IVRProperties_001";
સ્થિર અચલ અક્ષર * k_pch_Path_User_Hand_જમણું = "/user/hand/right";
સ્થિર અચલ અક્ષર * k_pch_Path_User_Hand_ડાબું = "/user/hand/left";
સ્થિર અચલ અક્ષર * k_pchPathUserHandPrimary = "/user/hand/primary";
સ્થિર અચલ અક્ષર * k_pchPathUserHandSecondary = "/user/hand/secondary";
સ્થિર અચલ અક્ષર * k_pchPathUserHead = "/user/head";
સ્થિર અચલ અક્ષર * k_pchPathUserGamepad = "/user/gamepad";
સ્થિર અચલ અક્ષર * k_pchPathUserTreadmill = "/user/treadmill";
સ્થિર અચલ અક્ષર * k_pchPathUserStylus = "/user/stylus";
સ્થિર અચલ અક્ષર * k_pchPathDevices = "/devices";
સ્થિર અચલ અક્ષર * k_pchPathDevicePath = "/device_path";
સ્થિર અચલ અક્ષર * k_pchPathBestAliasPath = "/best_alias_path";
સ્થિર અચલ અક્ષર * k_pchPathBoundTrackerAliasPath = "/bound_tracker_path";
સ્થિર અચલ અક્ષર * k_pchPathBoundTrackerRole = "/bound_tracker_role";
સ્થિર અચલ અક્ષર * k_pchPathPoseRaw = "/pose/raw";
સ્થિર અચલ અક્ષર * k_pchPathPoseTip = "/pose/tip";
સ્થિર અચલ અક્ષર * k_pchPathPoseGrip = "/pose/grip";
સ્થિર અચલ અક્ષર * k_pchPathSystemButtonClick = "/input/system/click";
સ્થિર અચલ અક્ષર * k_pchPathProximity = "/proximity";
સ્થિર અચલ અક્ષર * k_pchPathControllerTypePrefix = "/controller_type/";
સ્થિર અચલ અક્ષર * k_pch_Path_આગત_Profile_Suffix = "/input_profile";
સ્થિર અચલ અક્ષર * k_pchPathBindingNameSuffix = "/binding_name";
સ્થિર અચલ અક્ષર * k_pchPathBindingUrlSuffix = "/binding_url";
સ્થિર અચલ અક્ષર * k_pchPathBindingErrorSuffix = "/binding_error";
સ્થિર અચલ અક્ષર * k_pchPathActiveActionSets = "/active_action_sets";
સ્થિર અચલ અક્ષર * k_pchPathComponentUpdates = "/total_component_updates";
સ્થિર અચલ અક્ષર * k_pch_Path_User_Foot_ડાબું = "/user/foot/left";
સ્થિર અચલ અક્ષર * k_pch_Path_User_Foot_જમણું = "/user/foot/right";
સ્થિર અચલ અક્ષર * k_pch_Path_User_Shoulder_ડાબું = "/user/shoulder/left";
સ્થિર અચલ અક્ષર * k_pch_Path_User_Shoulder_જમણું = "/user/shoulder/right";
સ્થિર અચલ અક્ષર * k_pch_Path_User_Elbow_ડાબું = "/user/elbow/left";
સ્થિર અચલ અક્ષર * k_pch_Path_User_Elbow_જમણું = "/user/elbow/right";
સ્થિર અચલ અક્ષર * k_pch_Path_User_Knee_ડાબું = "/user/knee/left";
સ્થિર અચલ અક્ષર * k_pch_Path_User_Knee_જમણું = "/user/knee/right";
સ્થિર અચલ અક્ષર * k_pchPathUserWaist = "/user/waist";
સ્થિર અચલ અક્ષર * k_pchPathUserChest = "/user/chest";
સ્થિર અચલ અક્ષર * k_pchPathUserCamera = "/user/camera";
સ્થિર અચલ અક્ષર * k_pchPathUserKeyboard = "/user/keyboard";
સ્થિર અચલ અક્ષર * k_pch_Path_Client_App_ચાવી = "/client_info/app_key";
સ્થિર અચલ unsigned long long k_ulInvalidPathHandle = 0;
સ્થિર અચલ અક્ષર * IVRPaths_Version = "IVRPaths_001";
સ્થિર અચલ અક્ષર * IVRBlockQueue_Version = "IVRBlockQueue_005";

// OpenVR Enums

પ્રકારવ્યાખ્યા ગણના EVREye
{
	EVREye_Eye_ડાબું = 0,
	EVREye_Eye_જમણું = 1,
} EVREye;

પ્રકારવ્યાખ્યા ગણના ETextureType
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

પ્રકારવ્યાખ્યા ગણના EColorSpace
{
	EColorSpace_ColorSpace_Auto = 0,
	EColorSpace_ColorSpace_Gamma = 1,
	EColorSpace_ColorSpace_Linear = 2,
} EColorSpace;

પ્રકારવ્યાખ્યા ગણના ETrackingResult
{
	ETrackingResult_TrackingResult_Uninitialized = 1,
	ETrackingResult_TrackingResult_Calibrating_InProgress = 100,
	ETrackingResult_TrackingResult_Calibrating_OutOfRange = 101,
	ETrackingResult_TrackingResult_Running_OK = 200,
	ETrackingResult_TrackingResult_Running_OutOfRange = 201,
	ETrackingResult_TrackingResult_Fallback_RotationOnly = 300,
} ETrackingResult;

પ્રકારવ્યાખ્યા ગણના ETrackedDeviceClass
{
	ETrackedDeviceClass_TrackedDeviceClass_Invalid = 0,
	ETrackedDeviceClass_TrackedDeviceClass_HMD = 1,
	ETrackedDeviceClass_TrackedDeviceClass_Controller = 2,
	ETrackedDeviceClass_TrackedDeviceClass_GenericTracker = 3,
	ETrackedDeviceClass_TrackedDeviceClass_TrackingReference = 4,
	ETrackedDeviceClass_TrackedDeviceClass_DisplayRedirect = 5,
	ETrackedDeviceClass_TrackedDeviceClass_Max = 6,
} ETrackedDeviceClass;

પ્રકારવ્યાખ્યા ગણના ETrackedControllerRole
{
	ETrackedControllerRole_TrackedControllerRole_Invalid = 0,
	ETracked_Controller_Role_Tracked_Controller_Role_ડાબું_Hand = 1,
	ETracked_Controller_Role_Tracked_Controller_Role_જમણું_Hand = 2,
	ETrackedControllerRole_TrackedControllerRole_OptOut = 3,
	ETrackedControllerRole_TrackedControllerRole_Treadmill = 4,
	ETrackedControllerRole_TrackedControllerRole_Stylus = 5,
	ETrackedControllerRole_TrackedControllerRole_Max = 5,
} ETrackedControllerRole;

પ્રકારવ્યાખ્યા ગણના ETrackingUniverseOrigin
{
	ETrackingUniverseOrigin_TrackingUniverseSeated = 0,
	ETrackingUniverseOrigin_TrackingUniverseStanding = 1,
	ETrackingUniverseOrigin_TrackingUniverseRawAndUncalibrated = 2,
} ETrackingUniverseOrigin;

પ્રકારવ્યાખ્યા ગણના EAdditionalRadioFeatures
{
	EAdditionalRadioFeatures_AdditionalRadioFeatures_None = 0,
	EAdditionalRadioFeatures_AdditionalRadioFeatures_HTCLinkBox = 1,
	EAdditionalRadioFeatures_AdditionalRadioFeatures_InternalDongle = 2,
	EAdditionalRadioFeatures_AdditionalRadioFeatures_ExternalDongle = 4,
} EAdditionalRadioFeatures;

પ્રકારવ્યાખ્યા ગણના ETrackedDeviceProperty
{
	ETrackedDeviceProperty_Prop_Invalid = 0,
	ETrackedDeviceProperty_Prop_TrackingSystemName_String = 1000,
	ETracked_Device_Property_Prop_Model_સંખ્યા_String = 1001,
	ETracked_Device_Property_Prop_Serial_સંખ્યા_String = 1002,
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
	ETracked_Device_Property_Prop_Resource_મૂળ_String = 1035,
	ETrackedDeviceProperty_Prop_RegisteredDeviceType_String = 1036,
	ETracked_Device_Property_Prop_આગત_Profile_Path_String = 1037,
	ETrackedDeviceProperty_Prop_NeverTracked_Bool = 1038,
	ETracked_Device_Property_Prop_અંક_Cameras_Int32 = 1039,
	ETrackedDeviceProperty_Prop_CameraFrameLayout_Int32 = 1040,
	ETrackedDeviceProperty_Prop_CameraStreamFormat_Int32 = 1041,
	ETrackedDeviceProperty_Prop_AdditionalDeviceSettingsPath_String = 1042,
	ETrackedDeviceProperty_Prop_Identifiable_Bool = 1043,
	ETrackedDeviceProperty_Prop_BootloaderVersion_Uint64 = 1044,
	ETrackedDeviceProperty_Prop_AdditionalSystemReportData_String = 1045,
	ETrackedDeviceProperty_Prop_CompositeFirmwareVersion_String = 1046,
	ETrackedDeviceProperty_Prop_Firmware_RemindUpdate_Bool = 1047,
	ETrackedDeviceProperty_Prop_PeripheralApplicationVersion_Uint64 = 1048,
	ETracked_Device_Property_Prop_Manufacturer_Serial_સંખ્યા_String = 1049,
	ETracked_Device_Property_Prop_Computed_Serial_સંખ્યા_String = 1050,
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
	ETracked_Device_Property_Prop_Display_MCImage_ડાબું_String = 2012,
	ETracked_Device_Property_Prop_Display_MCImage_જમણું_String = 2013,
	ETrackedDeviceProperty_Prop_DisplayGCBlackClamp_Float = 2014,
	ETrackedDeviceProperty_Prop_EdidProductID_Int32 = 2015,
	ETrackedDeviceProperty_Prop_CameraToHeadTransform_Matrix34 = 2016,
	ETrackedDeviceProperty_Prop_DisplayGCType_Int32 = 2017,
	ETrackedDeviceProperty_Prop_DisplayGCOffset_Float = 2018,
	ETrackedDeviceProperty_Prop_DisplayGCScale_Float = 2019,
	ETrackedDeviceProperty_Prop_DisplayGCPrescale_Float = 2020,
	ETrackedDeviceProperty_Prop_DisplayGCImage_String = 2021,
	ETracked_Device_Property_Prop_Lens_Center_ડાબું_U_Float = 2022,
	ETracked_Device_Property_Prop_Lens_Center_ડાબું_V_Float = 2023,
	ETracked_Device_Property_Prop_Lens_Center_જમણું_U_Float = 2024,
	ETracked_Device_Property_Prop_Lens_Center_જમણું_V_Float = 2025,
	ETrackedDeviceProperty_Prop_UserHeadToEyeDepthMeters_Float = 2026,
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
	ETracked_Device_Property_Prop_Display_MCImage_અંક_Channels_Int32 = 2040,
	ETracked_Device_Property_Prop_Display_MCImage_Data_દ્વિઅંકી = 2041,
	ETrackedDeviceProperty_Prop_SecondsFromPhotonsToVblank_Float = 2042,
	ETrackedDeviceProperty_Prop_DriverDirectModeSendsVsyncEvents_Bool = 2043,
	ETrackedDeviceProperty_Prop_DisplayDebugMode_Bool = 2044,
	ETrackedDeviceProperty_Prop_GraphicsAdapterLuid_Uint64 = 2045,
	ETrackedDeviceProperty_Prop_DriverProvidedChaperonePath_String = 2048,
	ETracked_Device_Property_Prop_Expected_Tracking_Reference_ગણતરી_Int32 = 2049,
	ETracked_Device_Property_Prop_Expected_Controller_ગણતરી_Int32 = 2050,
	ETracked_Device_Property_Prop_Named_Icon_Path_Controller_ડાબું_Device_Off_String = 2051,
	ETracked_Device_Property_Prop_Named_Icon_Path_Controller_જમણું_Device_Off_String = 2052,
	ETrackedDeviceProperty_Prop_NamedIconPathTrackingReferenceDeviceOff_String = 2053,
	ETrackedDeviceProperty_Prop_DoNotApplyPrediction_Bool = 2054,
	ETrackedDeviceProperty_Prop_CameraToHeadTransforms_Matrix34_Array = 2055,
	ETrackedDeviceProperty_Prop_DistortionMeshResolution_Int32 = 2056,
	ETrackedDeviceProperty_Prop_DriverIsDrawingControllers_Bool = 2057,
	ETrackedDeviceProperty_Prop_DriverRequestsApplicationPause_Bool = 2058,
	ETrackedDeviceProperty_Prop_DriverRequestsReducedRendering_Bool = 2059,
	ETrackedDeviceProperty_Prop_MinimumIpdStepMeters_Float = 2060,
	ETrackedDeviceProperty_Prop_AudioBridgeFirmwareVersion_Uint64 = 2061,
	ETrackedDeviceProperty_Prop_ImageBridgeFirmwareVersion_Uint64 = 2062,
	ETrackedDeviceProperty_Prop_ImuToHeadTransform_Matrix34 = 2063,
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
	ETracked_Device_Property_Prop_Display_Color_Mult_ડાબું_Vector3 = 2082,
	ETracked_Device_Property_Prop_Display_Color_Mult_જમણું_Vector3 = 2083,
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
	ETracked_Device_Property_Prop_DSCSlice_ગણતરી_Int32 = 2111,
	ETrackedDeviceProperty_Prop_DSCBPPx16_Int32 = 2112,
	ETrackedDeviceProperty_Prop_DriverRequestedMuraCorrectionMode_Int32 = 2200,
	ETracked_Device_Property_Prop_Driver_Requested_Mura_Feather_Inner_ડાબું_Int32 = 2201,
	ETracked_Device_Property_Prop_Driver_Requested_Mura_Feather_Inner_જમણું_Int32 = 2202,
	ETracked_Device_Property_Prop_Driver_Requested_Mura_Feather_Inner_ટોચ_Int32 = 2203,
	ETrackedDeviceProperty_Prop_DriverRequestedMuraFeather_InnerBottom_Int32 = 2204,
	ETracked_Device_Property_Prop_Driver_Requested_Mura_Feather_Outer_ડાબું_Int32 = 2205,
	ETracked_Device_Property_Prop_Driver_Requested_Mura_Feather_Outer_જમણું_Int32 = 2206,
	ETracked_Device_Property_Prop_Driver_Requested_Mura_Feather_Outer_ટોચ_Int32 = 2207,
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
	ETracked_Device_Property_Prop_Field_Of_View_ડાબું_Degrees_Float = 4000,
	ETracked_Device_Property_Prop_Field_Of_View_જમણું_Degrees_Float = 4001,
	ETracked_Device_Property_Prop_Field_Of_View_ટોચ_Degrees_Float = 4002,
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
	ETracked_Device_Property_Prop_Named_Icon_Path_Device_Alert_નીચલું_String = 5008,
	ETrackedDeviceProperty_Prop_NamedIconPathDeviceStandbyAlert_String = 5009,
	ETracked_Device_Property_Prop_Display_Hidden_Area_દ્વિઅંકી_Start = 5100,
	ETracked_Device_Property_Prop_Display_Hidden_Area_દ્વિઅંકી_End = 5150,
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

પ્રકારવ્યાખ્યા ગણના ETrackedPropertyError
{
	ETrackedPropertyError_TrackedProp_Success = 0,
	ETrackedPropertyError_TrackedProp_WrongDataType = 1,
	ETrackedPropertyError_TrackedProp_WrongDeviceClass = 2,
	ETrackedPropertyError_TrackedProp_BufferTooSmall = 3,
	ETrackedPropertyError_TrackedProp_UnknownProperty = 4,
	ETrackedPropertyError_TrackedProp_InvalidDevice = 5,
	ETrackedPropertyError_TrackedProp_CouldNotContactServer = 6,
	ETracked_Property_Error_Tracked_Prop_કિંમત_Not_Provided_By_Device = 7,
	ETrackedPropertyError_TrackedProp_StringExceedsMaximumLength = 8,
	ETrackedPropertyError_TrackedProp_NotYetAvailable = 9,
	ETrackedPropertyError_TrackedProp_PermissionDenied = 10,
	ETrackedPropertyError_TrackedProp_InvalidOperation = 11,
	ETrackedPropertyError_TrackedProp_CannotWriteToWildcards = 12,
	ETrackedPropertyError_TrackedProp_IPCReadFailure = 13,
	ETrackedPropertyError_TrackedProp_OutOfMemory = 14,
	ETrackedPropertyError_TrackedProp_InvalidContainer = 15,
} ETrackedPropertyError;

પ્રકારવ્યાખ્યા ગણના EHmdTrackingStyle
{
	EHmdTrackingStyle_HmdTrackingStyle_Unknown = 0,
	EHmdTrackingStyle_HmdTrackingStyle_Lighthouse = 1,
	EHmdTrackingStyle_HmdTrackingStyle_OutsideInCameras = 2,
	EHmdTrackingStyle_HmdTrackingStyle_InsideOutCameras = 3,
} EHmdTrackingStyle;

પ્રકારવ્યાખ્યા ગણના EVRSubmitFlags
{
	EVRSubmitFlags_Submit_Default = 0,
	EVRSubmitFlags_Submit_LensDistortionAlreadyApplied = 1,
	EVRSubmitFlags_Submit_GlRenderBuffer = 2,
	EVRSubmitFlags_Submit_Reserved = 4,
	EVRSubmitFlags_Submit_TextureWithPose = 8,
	EVRSubmitFlags_Submit_TextureWithDepth = 16,
	EVRSubmitFlags_Submit_FrameDiscontinuty = 32,
	EVRSubmitFlags_Submit_VulkanTextureWithArrayData = 64,
	EVRSubmitFlags_Submit_GlArrayTexture = 128,
	EVRSubmitFlags_Submit_Reserved2 = 32768,
	EVRSubmitFlags_Submit_Reserved3 = 65536,
} EVRSubmitFlags;

પ્રકારવ્યાખ્યા ગણના EVRState
{
	EVRState_VRState_Undefined = -1,
	EVRState_VRState_Off = 0,
	EVRState_VRState_Searching = 1,
	EVRState_VRState_Searching_Alert = 2,
	EVRState_VRState_Ready = 3,
	EVRState_VRState_Ready_Alert = 4,
	EVRState_VRState_NotReady = 5,
	EVRState_VRState_Standby = 6,
	EVRState_VRState_Ready_Alert_નીચલું = 7,
} EVRState;

પ્રકારવ્યાખ્યા ગણના EVREventType
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
	EVREvent_Type_VREvent_આગત_Focus_Captured = 400,
	EVREvent_Type_VREvent_આગત_Focus_Released = 401,
	EVREventType_VREvent_SceneApplicationChanged = 404,
	EVREvent_Type_VREvent_આગત_Focus_Changed = 406,
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
	EVREventType_VREvent_ChaperoneDataHasChanged = 800,
	EVREventType_VREvent_ChaperoneUniverseHasChanged = 801,
	EVREventType_VREvent_ChaperoneTempDataHasChanged = 802,
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
	EVREvent_Type_VREvent_Keyboard_Char_આગત = 1201,
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
	EVREvent_Type_VREvent_આગત_Haptic_Vibration = 1700,
	EVREvent_Type_VREvent_આગત_Binding_Load_Failed = 1701,
	EVREvent_Type_VREvent_આગત_Binding_Load_Successful = 1702,
	EVREvent_Type_VREvent_આગત_Action_Manifest_Reloaded = 1703,
	EVREvent_Type_VREvent_આગત_Action_Manifest_Load_Failed = 1704,
	EVREvent_Type_VREvent_આગત_Progress_Update = 1705,
	EVREvent_Type_VREvent_આગત_Tracker_Activated = 1706,
	EVREvent_Type_VREvent_આગત_Bindings_Updated = 1707,
	EVREvent_Type_VREvent_આગત_Binding_Subscription_Changed = 1708,
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

પ્રકારવ્યાખ્યા ગણના EDeviceActivityLevel
{
	EDeviceActivityLevel_k_EDeviceActivityLevel_Unknown = -1,
	EDeviceActivityLevel_k_EDeviceActivityLevel_Idle = 0,
	EDeviceActivityLevel_k_EDeviceActivityLevel_UserInteraction = 1,
	EDeviceActivityLevel_k_EDeviceActivityLevel_UserInteraction_Timeout = 2,
	EDeviceActivityLevel_k_EDeviceActivityLevel_Standby = 3,
	EDeviceActivityLevel_k_EDeviceActivityLevel_Idle_Timeout = 4,
} EDeviceActivityLevel;

પ્રકારવ્યાખ્યા ગણના EVRButtonId
{
	EVRButtonId_k_EButton_System = 0,
	EVRButtonId_k_EButton_ApplicationMenu = 1,
	EVRButtonId_k_EButton_Grip = 2,
	EVRButton_Id_k_EButton_DPad_ડાબું = 3,
	EVRButtonId_k_EButton_DPad_Up = 4,
	EVRButton_Id_k_EButton_DPad_જમણું = 5,
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
	EVRButtonId_k_EButton_IndexController_A = 2,
	EVRButtonId_k_EButton_IndexController_B = 1,
	EVRButtonId_k_EButton_IndexController_JoyStick = 35,
	EVRButtonId_k_EButton_Max = 64,
} EVRButtonId;

પ્રકારવ્યાખ્યા ગણના EVRMouseButton
{
	EVRMouse_Button_VRMouse_Button_ડાબું = 1,
	EVRMouse_Button_VRMouse_Button_જમણું = 2,
	EVRMouse_Button_VRMouse_Button_મધ્ય = 4,
} EVRMouseButton;

પ્રકારવ્યાખ્યા ગણના EShowUIType
{
	EShowUIType_ShowUI_ControllerBinding = 0,
	EShowUIType_ShowUI_ManageTrackers = 1,
	EShowUIType_ShowUI_Pairing = 3,
	EShowUIType_ShowUI_Settings = 4,
	EShowUIType_ShowUI_DebugCommands = 5,
	EShowUIType_ShowUI_FullControllerBinding = 6,
	EShowUIType_ShowUI_ManageDrivers = 7,
} EShowUIType;

પ્રકારવ્યાખ્યા ગણના EHDCPError
{
	EHDCPError_HDCPError_None = 0,
	EHDCPError_HDCPError_LinkLost = 1,
	EHDCPError_HDCPError_Tampered = 2,
	EHDCPError_HDCPError_DeviceRevoked = 3,
	EHDCPError_HDCPError_Unknown = 4,
} EHDCPError;

પ્રકારવ્યાખ્યા ગણના EVRComponentProperty
{
	EVRComponentProperty_VRComponentProperty_IsStatic = 1,
	EVRComponentProperty_VRComponentProperty_IsVisible = 2,
	EVRComponentProperty_VRComponentProperty_IsTouched = 4,
	EVRComponentProperty_VRComponentProperty_IsPressed = 8,
	EVRComponentProperty_VRComponentProperty_IsScrolled = 16,
	EVRComponentProperty_VRComponentProperty_IsHighlighted = 32,
} EVRComponentProperty;

પ્રકારવ્યાખ્યા ગણના EVRInputError
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
	EVRInput_Error_VRInput_Error_Invalid_Bone_ગણતરી = 11,
	EVRInputError_VRInputError_InvalidCompressedData = 12,
	EVRInputError_VRInputError_NoData = 13,
	EVRInputError_VRInputError_BufferTooSmall = 14,
	EVRInputError_VRInputError_MismatchedActionManifest = 15,
	EVRInputError_VRInputError_MissingSkeletonData = 16,
	EVRInputError_VRInputError_InvalidBoneIndex = 17,
	EVRInputError_VRInputError_InvalidPriority = 18,
	EVRInputError_VRInputError_PermissionDenied = 19,
	EVRInputError_VRInputError_InvalidRenderModel = 20,
} EVRInputError;

પ્રકારવ્યાખ્યા ગણના EVRSpatialAnchorError
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

પ્રકારવ્યાખ્યા ગણના EHiddenAreaMeshType
{
	EHiddenAreaMeshType_k_eHiddenAreaMesh_Standard = 0,
	EHiddenAreaMeshType_k_eHiddenAreaMesh_Inverse = 1,
	EHidden_Area_Mesh_Type_k_e_Hidden_Area_Mesh_લીટી_Loop = 2,
	EHiddenAreaMeshType_k_eHiddenAreaMesh_Max = 3,
} EHiddenAreaMeshType;

પ્રકારવ્યાખ્યા ગણના EVRControllerAxisType
{
	EVRControllerAxisType_k_eControllerAxis_None = 0,
	EVRControllerAxisType_k_eControllerAxis_TrackPad = 1,
	EVRControllerAxisType_k_eControllerAxis_Joystick = 2,
	EVRControllerAxisType_k_eControllerAxis_Trigger = 3,
} EVRControllerAxisType;

પ્રકારવ્યાખ્યા ગણના EVRControllerEventOutputType
{
	EVRControllerEventOutputType_ControllerEventOutput_OSEvents = 0,
	EVRControllerEventOutputType_ControllerEventOutput_VREvents = 1,
} EVRControllerEventOutputType;

પ્રકારવ્યાખ્યા ગણના ECollisionBoundsStyle
{
	ECollisionBoundsStyle_COLLISION_BOUNDS_STYLE_BEGINNER = 0,
	ECollisionBoundsStyle_COLLISION_BOUNDS_STYLE_INTERMEDIATE = 1,
	ECollisionBoundsStyle_COLLISION_BOUNDS_STYLE_SQUARES = 2,
	ECollisionBoundsStyle_COLLISION_BOUNDS_STYLE_ADVANCED = 3,
	ECollisionBoundsStyle_COLLISION_BOUNDS_STYLE_NONE = 4,
	ECollision_Bounds_Style_COLLISION_BOUNDS_STYLE_ગણતરી = 5,
} ECollisionBoundsStyle;

પ્રકારવ્યાખ્યા ગણના EVROverlayError
{
	EVROverlayError_VROverlayError_None = 0,
	EVROverlayError_VROverlayError_UnknownOverlay = 10,
	EVROverlayError_VROverlayError_InvalidHandle = 11,
	EVROverlayError_VROverlayError_PermissionDenied = 12,
	EVROverlayError_VROverlayError_OverlayLimitExceeded = 13,
	EVROverlayError_VROverlayError_WrongVisibilityType = 14,
	EVROverlay_Error_VROverlay_Error_ચાવી_Too_Long = 15,
	EVROverlayError_VROverlayError_NameTooLong = 16,
	EVROverlay_Error_VROverlay_Error_ચાવી_In_Use = 17,
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

પ્રકારવ્યાખ્યા ગણના EVRApplicationType
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

પ્રકારવ્યાખ્યા ગણના EVRFirmwareError
{
	EVRFirmwareError_VRFirmwareError_None = 0,
	EVRFirmwareError_VRFirmwareError_Success = 1,
	EVRFirmwareError_VRFirmwareError_Fail = 2,
} EVRFirmwareError;

પ્રકારવ્યાખ્યા ગણના EVRNotificationError
{
	EVRNotificationError_VRNotificationError_OK = 0,
	EVRNotificationError_VRNotificationError_InvalidNotificationId = 100,
	EVRNotificationError_VRNotificationError_NotificationQueueFull = 101,
	EVRNotificationError_VRNotificationError_InvalidOverlayHandle = 102,
	EVRNotification_Error_VRNotification_Error_System_With_User_કિંમત_Already_Exists = 103,
} EVRNotificationError;

પ્રકારવ્યાખ્યા ગણના EVRSkeletalMotionRange
{
	EVRSkeletalMotionRange_VRSkeletalMotionRange_WithController = 0,
	EVRSkeletalMotionRange_VRSkeletalMotionRange_WithoutController = 1,
} EVRSkeletalMotionRange;

પ્રકારવ્યાખ્યા ગણના EVRSkeletalTrackingLevel
{
	EVRSkeletalTrackingLevel_VRSkeletalTracking_Estimated = 0,
	EVRSkeletalTrackingLevel_VRSkeletalTracking_Partial = 1,
	EVRSkeletalTrackingLevel_VRSkeletalTracking_Full = 2,
	EVRSkeletal_Tracking_Level_VRSkeletal_Tracking_Level_ગણતરી = 3,
	EVRSkeletalTrackingLevel_VRSkeletalTrackingLevel_Max = 2,
} EVRSkeletalTrackingLevel;

પ્રકારવ્યાખ્યા ગણના EVRInitError
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
	EVRInit_Error_VRInit_Error_Init_નીચલું_Power_Watchdog_Not_Supported = 129,
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
	EVRInitError_VRInitError_Compositor_FailedToGetBackBuffer = 427,
	EVRInitError_VRInitError_Compositor_FailedToCreateRenderTarget = 428,
	EVRInitError_VRInitError_Compositor_FailedToCreateDXGI2SwapChain = 429,
	EVRInitError_VRInitError_Compositor_FailedtoGetDXGI2BackBuffer = 430,
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
	EVRInitError_VRInitError_Compositor_CreateConstantBuffer = 458,
	EVRInitError_VRInitError_Compositor_CreateHmdPoseConstantBuffer = 459,
	EVRInitError_VRInitError_Compositor_CreateHmdPoseStagingConstantBuffer = 460,
	EVRInitError_VRInitError_Compositor_CreateSharedFrameInfoConstantBuffer = 461,
	EVRInitError_VRInitError_Compositor_CreateOverlayConstantBuffer = 462,
	EVRInitError_VRInitError_Compositor_CreateSceneTextureIndexConstantBuffer = 463,
	EVRInitError_VRInitError_Compositor_CreateReadableSceneTextureIndexConstantBuffer = 464,
	EVRInitError_VRInitError_Compositor_CreateLayerGraphicsTextureIndexConstantBuffer = 465,
	EVRInitError_VRInitError_Compositor_CreateLayerComputeTextureIndexConstantBuffer = 466,
	EVRInitError_VRInitError_Compositor_CreateLayerComputeSceneTextureIndexConstantBuffer = 467,
	EVRInitError_VRInitError_Compositor_CreateComputeHmdPoseConstantBuffer = 468,
	EVRInitError_VRInitError_Compositor_CreateGeomConstantBuffer = 469,
	EVRInitError_VRInitError_Compositor_CreatePanelMaskConstantBuffer = 470,
	EVRInitError_VRInitError_Compositor_CreatePixelSimUBO = 471,
	EVRInitError_VRInitError_Compositor_CreateMSAARenderTextures = 472,
	EVRInitError_VRInitError_Compositor_CreateResolveRenderTextures = 473,
	EVRInitError_VRInitError_Compositor_CreateComputeResolveRenderTextures = 474,
	EVRInitError_VRInitError_Compositor_CreateDriverDirectModeResolveTextures = 475,
	EVRInitError_VRInitError_Compositor_OpenDriverDirectModeResolveTextures = 476,
	EVRInitError_VRInitError_Compositor_CreateFallbackSyncTexture = 477,
	EVRInitError_VRInitError_Compositor_ShareFallbackSyncTexture = 478,
	EVRInitError_VRInitError_Compositor_CreateOverlayIndexBuffer = 479,
	EVRInitError_VRInitError_Compositor_CreateOverlayVertexBuffer = 480,
	EVRInitError_VRInitError_Compositor_CreateTextVertexBuffer = 481,
	EVRInitError_VRInitError_Compositor_CreateTextIndexBuffer = 482,
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
	EVRInitError_VRInitError_VendorSpecific_HmdFound_UnableToSendUserDataStart = 1108,
	EVRInitError_VRInitError_VendorSpecific_HmdFound_UnableToGetUserDataStart = 1109,
	EVRInitError_VRInitError_VendorSpecific_HmdFound_UnableToGetUserDataNext = 1110,
	EVRInitError_VRInitError_VendorSpecific_HmdFound_UserDataAddressRange = 1111,
	EVRInitError_VRInitError_VendorSpecific_HmdFound_UserDataError = 1112,
	EVRInitError_VRInitError_VendorSpecific_HmdFound_ConfigFailedSanityCheck = 1113,
	EVRInitError_VRInitError_VendorSpecific_OculusRuntimeBadInstall = 1114,
	EVRInitError_VRInitError_VendorSpecific_HmdFound_UnexpectedConfiguration_1 = 1115,
	EVRInitError_VRInitError_Steam_SteamInstallationNotFound = 2000,
	EVRInitError_VRInitError_LastError = 2001,
} EVRInitError;

પ્રકારવ્યાખ્યા ગણના EVRScreenshotType
{
	EVRScreenshotType_VRScreenshotType_None = 0,
	EVRScreenshotType_VRScreenshotType_Mono = 1,
	EVRScreenshotType_VRScreenshotType_Stereo = 2,
	EVRScreenshotType_VRScreenshotType_Cubemap = 3,
	EVRScreenshotType_VRScreenshotType_MonoPanorama = 4,
	EVRScreenshotType_VRScreenshotType_StereoPanorama = 5,
} EVRScreenshotType;

પ્રકારવ્યાખ્યા ગણના EVRScreenshotPropertyFilenames
{
	EVRScreenshotPropertyFilenames_VRScreenshotPropertyFilenames_Preview = 0,
	EVRScreenshotPropertyFilenames_VRScreenshotPropertyFilenames_VR = 1,
} EVRScreenshotPropertyFilenames;

પ્રકારવ્યાખ્યા ગણના EVRTrackedCameraError
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
	EVRTrackedCameraError_VRTrackedCameraError_InvalidFrameBufferSize = 115,
} EVRTrackedCameraError;

પ્રકારવ્યાખ્યા ગણના EVRTrackedCameraFrameLayout
{
	EVRTrackedCameraFrameLayout_Mono = 1,
	EVRTrackedCameraFrameLayout_Stereo = 2,
	EVRTrackedCameraFrameLayout_VerticalLayout = 16,
	EVRTrackedCameraFrameLayout_HorizontalLayout = 32,
} EVRTrackedCameraFrameLayout;

પ્રકારવ્યાખ્યા ગણના EVRTrackedCameraFrameType
{
	EVRTrackedCameraFrameType_VRTrackedCameraFrameType_Distorted = 0,
	EVRTrackedCameraFrameType_VRTrackedCameraFrameType_Undistorted = 1,
	EVRTrackedCameraFrameType_VRTrackedCameraFrameType_MaximumUndistorted = 2,
	EVRTrackedCameraFrameType_MAX_CAMERA_FRAME_TYPES = 3,
} EVRTrackedCameraFrameType;

પ્રકારવ્યાખ્યા ગણના EVRDistortionFunctionType
{
	EVRDistortionFunctionType_VRDistortionFunctionType_None = 0,
	EVRDistortionFunctionType_VRDistortionFunctionType_FTheta = 1,
	EVRDistortionFunctionType_VRDistortionFunctionType_Extended_FTheta = 2,
	EVRDistortionFunctionType_MAX_DISTORTION_FUNCTION_TYPES = 3,
} EVRDistortionFunctionType;

પ્રકારવ્યાખ્યા ગણના EVSync
{
	EVSync_VSync_None = 0,
	EVSync_VSync_WaitRender = 1,
	EVSync_VSync_NoWaitRender = 2,
} EVSync;

પ્રકારવ્યાખ્યા ગણના EVRMuraCorrectionMode
{
	EVRMuraCorrectionMode_Default = 0,
	EVRMuraCorrectionMode_NoCorrection = 1,
} EVRMuraCorrectionMode;

પ્રકારવ્યાખ્યા ગણના Imu_OffScaleFlags
{
	Imu_OffScaleFlags_OffScale_AccelX = 1,
	Imu_OffScaleFlags_OffScale_AccelY = 2,
	Imu_OffScaleFlags_OffScale_AccelZ = 4,
	Imu_OffScaleFlags_OffScale_GyroX = 8,
	Imu_OffScaleFlags_OffScale_GyroY = 16,
	Imu_OffScaleFlags_OffScale_GyroZ = 32,
} Imu_OffScaleFlags;

પ્રકારવ્યાખ્યા ગણના EVRApplicationError
{
	EVRApplicationError_VRApplicationError_None = 0,
	EVRApplication_Error_VRApplication_Error_App_ચાવી_Already_Exists = 100,
	EVRApplicationError_VRApplicationError_NoManifest = 101,
	EVRApplicationError_VRApplicationError_NoApplication = 102,
	EVRApplicationError_VRApplicationError_InvalidIndex = 103,
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
	EVRApplicationError_VRApplicationError_BufferTooSmall = 200,
	EVRApplicationError_VRApplicationError_PropertyNotSet = 201,
	EVRApplicationError_VRApplicationError_UnknownProperty = 202,
	EVRApplicationError_VRApplicationError_InvalidParameter = 203,
	EVRApplicationError_VRApplicationError_NotImplemented = 300,
} EVRApplicationError;

પ્રકારવ્યાખ્યા ગણના EVRApplicationProperty
{
	EVRApplicationProperty_VRApplicationProperty_Name_String = 0,
	EVRApplicationProperty_VRApplicationProperty_LaunchType_String = 11,
	EVRApplicationProperty_VRApplicationProperty_WorkingDirectory_String = 12,
	EVRApplication_Property_VRApplication_Property_દ્વિઅંકી_Path_String = 13,
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

પ્રકારવ્યાખ્યા ગણના EVRSceneApplicationState
{
	EVRSceneApplicationState_None = 0,
	EVRSceneApplicationState_Starting = 1,
	EVRSceneApplicationState_Quitting = 2,
	EVRSceneApplicationState_Running = 3,
	EVRSceneApplicationState_Waiting = 4,
} EVRSceneApplicationState;

પ્રકારવ્યાખ્યા ગણના ChaperoneCalibrationState
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

પ્રકારવ્યાખ્યા ગણના EChaperoneConfigFile
{
	EChaperoneConfigFile_Live = 1,
	EChaperoneConfigFile_Temp = 2,
} EChaperoneConfigFile;

પ્રકારવ્યાખ્યા ગણના EChaperoneImportFlags
{
	EChaperoneImportFlags_EChaperoneImport_BoundsOnly = 1,
} EChaperoneImportFlags;

પ્રકારવ્યાખ્યા ગણના EVRCompositorError
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
	EVRCompositorError_VRCompositorError_IndexOutOfRange = 107,
	EVRCompositorError_VRCompositorError_AlreadySubmitted = 108,
	EVRCompositorError_VRCompositorError_InvalidBounds = 109,
	EVRCompositorError_VRCompositorError_AlreadySet = 110,
} EVRCompositorError;

પ્રકારવ્યાખ્યા ગણના EVRCompositorTimingMode
{
	EVRCompositorTimingMode_VRCompositorTimingMode_Implicit = 0,
	EVRCompositorTimingMode_VRCompositorTimingMode_Explicit_RuntimePerformsPostPresentHandoff = 1,
	EVRCompositorTimingMode_VRCompositorTimingMode_Explicit_ApplicationPerformsPostPresentHandoff = 2,
} EVRCompositorTimingMode;

પ્રકારવ્યાખ્યા ગણના VROverlay_આગત_Method
{
	VROverlay_આગત_Method_None = 0,
	VROverlay_આગત_Method_Mouse = 1,
} VROverlay_આગત_Method;

પ્રકારવ્યાખ્યા ગણના VROverlayTransformType
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

પ્રકારવ્યાખ્યા ગણના VROverlayFlags
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

પ્રકારવ્યાખ્યા ગણના VRMessageOverlayResponse
{
	VRMessageOverlayResponse_ButtonPress_0 = 0,
	VRMessageOverlayResponse_ButtonPress_1 = 1,
	VRMessageOverlayResponse_ButtonPress_2 = 2,
	VRMessageOverlayResponse_ButtonPress_3 = 3,
	VRMessageOverlayResponse_CouldntFindSystemOverlay = 4,
	VRMessageOverlayResponse_CouldntFindOrCreateClientOverlay = 5,
	VRMessageOverlayResponse_ApplicationQuit = 6,
} VRMessageOverlayResponse;

પ્રકારવ્યાખ્યા ગણના EGamepad_Text_આગત_Mode
{
	EGamepad_Text_આગત_Mode_k_EGamepad_Text_આગત_Mode_Normal = 0,
	EGamepad_Text_આગત_Mode_k_EGamepad_Text_આગત_Mode_Password = 1,
	EGamepad_Text_આગત_Mode_k_EGamepad_Text_આગત_Mode_Submit = 2,
} EGamepad_Text_આગત_Mode;

પ્રકારવ્યાખ્યા ગણના EGamepad_Text_આગત_લીટી_Mode
{
	EGamepad_Text_આગત_લીટી_Mode_k_EGamepad_Text_આગત_લીટી_Mode_Single_લીટી = 0,
	EGamepad_Text_આગત_લીટી_Mode_k_EGamepad_Text_આગત_લીટી_Mode_Multiple_લીટીઓ = 1,
} EGamepad_Text_આગત_લીટી_Mode;

પ્રકારવ્યાખ્યા ગણના EVROverlayIntersectionMaskPrimitiveType
{
	EVROverlayIntersectionMaskPrimitiveType_OverlayIntersectionPrimitiveType_Rectangle = 0,
	EVROverlayIntersectionMaskPrimitiveType_OverlayIntersectionPrimitiveType_Circle = 1,
} EVROverlayIntersectionMaskPrimitiveType;

પ્રકારવ્યાખ્યા ગણના EKeyboardFlags
{
	EKeyboardFlags_KeyboardFlag_Minimal = 1,
	EKeyboardFlags_KeyboardFlag_Modal = 2,
} EKeyboardFlags;

પ્રકારવ્યાખ્યા ગણના EDeviceType
{
	EDeviceType_DeviceType_Invalid = -1,
	EDeviceType_DeviceType_DirectX11 = 0,
	EDeviceType_DeviceType_Vulkan = 1,
} EDeviceType;

પ્રકારવ્યાખ્યા ગણના HeadsetViewMode_t
{
	Headset_View_Mode_t_Headset_View_Mode_ડાબું = 0,
	Headset_View_Mode_t_Headset_View_Mode_જમણું = 1,
	HeadsetViewMode_t_HeadsetViewMode_Both = 2,
} HeadsetViewMode_t;

પ્રકારવ્યાખ્યા ગણના EVRRenderModelError
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
	EVRRenderModelError_VRRenderModelError_BufferTooSmall = 306,
	EVRRenderModelError_VRRenderModelError_NotEnoughNormals = 307,
	EVRRenderModelError_VRRenderModelError_NotEnoughTexCoords = 308,
	EVRRenderModelError_VRRenderModelError_InvalidTexture = 400,
} EVRRenderModelError;

પ્રકારવ્યાખ્યા ગણના EVRRenderModelTextureFormat
{
	EVRRenderModelTextureFormat_VRRenderModelTextureFormat_RGBA8_SRGB = 0,
	EVRRenderModelTextureFormat_VRRenderModelTextureFormat_BC2 = 1,
	EVRRenderModelTextureFormat_VRRenderModelTextureFormat_BC4 = 2,
	EVRRenderModelTextureFormat_VRRenderModelTextureFormat_BC7 = 3,
	EVRRenderModelTextureFormat_VRRenderModelTextureFormat_BC7_SRGB = 4,
	EVRRenderModelTextureFormat_VRRenderModelTextureFormat_RGBA16_FLOAT = 5,
} EVRRenderModelTextureFormat;

પ્રકારવ્યાખ્યા ગણના EVRNotificationType
{
	EVRNotificationType_Transient = 0,
	EVRNotificationType_Persistent = 1,
	EVRNotification_Type_Transient_System_With_User_કિંમત = 2,
} EVRNotificationType;

પ્રકારવ્યાખ્યા ગણના EVRNotificationStyle
{
	EVRNotificationStyle_None = 0,
	EVRNotificationStyle_Application = 100,
	EVRNotificationStyle_Contact_Disabled = 200,
	EVRNotificationStyle_Contact_Enabled = 201,
	EVRNotificationStyle_Contact_Active = 202,
} EVRNotificationStyle;

પ્રકારવ્યાખ્યા ગણના EVRSettingsError
{
	EVRSettingsError_VRSettingsError_None = 0,
	EVRSettingsError_VRSettingsError_IPCFailed = 1,
	EVRSettingsError_VRSettingsError_WriteFailed = 2,
	EVRSettingsError_VRSettingsError_ReadFailed = 3,
	EVRSettingsError_VRSettingsError_JsonParseFailed = 4,
	EVRSettingsError_VRSettingsError_UnsetSettingHasNoDefault = 5,
} EVRSettingsError;

પ્રકારવ્યાખ્યા ગણના EVRScreenshotError
{
	EVRScreenshotError_VRScreenshotError_None = 0,
	EVRScreenshotError_VRScreenshotError_RequestFailed = 1,
	EVRScreenshotError_VRScreenshotError_IncompatibleVersion = 100,
	EVRScreenshotError_VRScreenshotError_NotFound = 101,
	EVRScreenshotError_VRScreenshotError_BufferTooSmall = 102,
	EVRScreenshotError_VRScreenshotError_ScreenshotAlreadyInProgress = 108,
} EVRScreenshotError;

પ્રકારવ્યાખ્યા ગણના EVRSkeletalTransformSpace
{
	EVRSkeletalTransformSpace_VRSkeletalTransformSpace_Model = 0,
	EVRSkeletalTransformSpace_VRSkeletalTransformSpace_Parent = 1,
} EVRSkeletalTransformSpace;

પ્રકારવ્યાખ્યા ગણના EVRSkeletalReferencePose
{
	EVRSkeletalReferencePose_VRSkeletalReferencePose_BindPose = 0,
	EVRSkeletalReferencePose_VRSkeletalReferencePose_OpenHand = 1,
	EVRSkeletalReferencePose_VRSkeletalReferencePose_Fist = 2,
	EVRSkeletalReferencePose_VRSkeletalReferencePose_GripLimit = 3,
} EVRSkeletalReferencePose;

પ્રકારવ્યાખ્યા ગણના EVRFinger
{
	EVRFinger_VRFinger_Thumb = 0,
	EVRFinger_VRFinger_Index = 1,
	EVRFinger_VRFinger_મધ્ય = 2,
	EVRFinger_VRFinger_Ring = 3,
	EVRFinger_VRFinger_Pinky = 4,
	EVRFinger_VRFinger_ગણતરી = 5,
} EVRFinger;

પ્રકારવ્યાખ્યા ગણના EVRFingerSplay
{
	EVRFingerSplay_VRFingerSplay_Thumb_Index = 0,
	EVRFinger_Splay_VRFinger_Splay_Index_મધ્ય = 1,
	EVRFinger_Splay_VRFinger_Splay_મધ્ય_Ring = 2,
	EVRFingerSplay_VRFingerSplay_Ring_Pinky = 3,
	EVRFinger_Splay_VRFinger_Splay_ગણતરી = 4,
} EVRFingerSplay;

પ્રકારવ્યાખ્યા ગણના EVRSummaryType
{
	EVRSummaryType_VRSummaryType_FromAnimation = 0,
	EVRSummaryType_VRSummaryType_FromDevice = 1,
} EVRSummaryType;

પ્રકારવ્યાખ્યા ગણના EVRInputFilterCancelType
{
	EVRInputFilterCancelType_VRInputFilterCancel_Timers = 0,
	EVRInputFilterCancelType_VRInputFilterCancel_Momentum = 1,
} EVRInputFilterCancelType;

પ્રકારવ્યાખ્યા ગણના EVRInputStringBits
{
	EVRInputStringBits_VRInputString_Hand = 1,
	EVRInputStringBits_VRInputString_ControllerType = 2,
	EVRInput_String_Bits_VRInput_String_આગત_Source = 4,
	EVRInputStringBits_VRInputString_All = -1,
} EVRInputStringBits;

પ્રકારવ્યાખ્યા ગણના EIOBufferError
{
	EIOBufferError_IOBuffer_Success = 0,
	EIOBufferError_IOBuffer_OperationFailed = 100,
	EIOBufferError_IOBuffer_InvalidHandle = 101,
	EIOBufferError_IOBuffer_InvalidArgument = 102,
	EIOBufferError_IOBuffer_PathExists = 103,
	EIOBufferError_IOBuffer_PathDoesNotExist = 104,
	EIOBufferError_IOBuffer_Permission = 105,
} EIOBufferError;

પ્રકારવ્યાખ્યા ગણના EIOBufferMode
{
	EIOBufferMode_IOBufferMode_Read = 1,
	EIOBufferMode_IOBufferMode_Write = 2,
	EIOBufferMode_IOBufferMode_Create = 512,
} EIOBufferMode;

પ્રકારવ્યાખ્યા ગણના EVRDebugError
{
	EVRDebugError_VRDebugError_Success = 0,
	EVRDebugError_VRDebugError_BadParameter = 1,
} EVRDebugError;

પ્રકારવ્યાખ્યા ગણના EPropertyWriteType
{
	EPropertyWriteType_PropertyWrite_Set = 0,
	EPropertyWriteType_PropertyWrite_Erase = 1,
	EPropertyWriteType_PropertyWrite_SetError = 2,
} EPropertyWriteType;

પ્રકારવ્યાખ્યા ગણના EBlockQueueError
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

પ્રકારવ્યાખ્યા ગણના EBlockQueueReadType
{
	EBlockQueueReadType_BlockQueueRead_Latest = 0,
	EBlockQueueReadType_BlockQueueRead_New = 1,
	EBlockQueueReadType_BlockQueueRead_Next = 2,
} EBlockQueueReadType;

પ્રકારવ્યાખ્યા ગણના EBlockQueueCreationFlag
{
	EBlockQueueCreationFlag_BlockQueueFlag_OwnerIsReader = 1,
} EBlockQueueCreationFlag;


// OpenVR typedefs

પ્રકારવ્યાખ્યા uint32_t PropertyTypeTag_t;
પ્રકારવ્યાખ્યા uint32_t SpatialAnchorHandle_t;
પ્રકારવ્યાખ્યા શૂન્ય * glSharedTextureHandle_t;
પ્રકારવ્યાખ્યા int32_t glInt_t;
પ્રકારવ્યાખ્યા uint32_t glUInt_t;
પ્રકારવ્યાખ્યા uint64_t SharedTextureHandle_t;
પ્રકારવ્યાખ્યા uint32_t DriverId_t;
પ્રકારવ્યાખ્યા uint32_t TrackedDeviceIndex_t;
પ્રકારવ્યાખ્યા uint64_t WebConsoleHandle_t;
પ્રકારવ્યાખ્યા uint64_t PropertyContainerHandle_t;
પ્રકારવ્યાખ્યા PropertyContainerHandle_t DriverHandle_t;
પ્રકારવ્યાખ્યા uint64_t VRActionHandle_t;
પ્રકારવ્યાખ્યા uint64_t VRActionSetHandle_t;
પ્રકારવ્યાખ્યા uint64_t VRInput_કિંમત_Handle_t;
પ્રકારવ્યાખ્યા uint32_t VRComponentProperties;
પ્રકારવ્યાખ્યા uint64_t VROverlayHandle_t;
પ્રકારવ્યાખ્યા int32_t BoneIndex_t;
પ્રકારવ્યાખ્યા uint64_t TrackedCameraHandle_t;
પ્રકારવ્યાખ્યા uint32_t ScreenshotHandle_t;
પ્રકારવ્યાખ્યા int32_t TextureID_t;
પ્રકારવ્યાખ્યા uint32_t VRNotificationId;
પ્રકારવ્યાખ્યા uint64_t IOBufferHandle_t;
પ્રકારવ્યાખ્યા uint64_t VrProfilerEventHandle_t;
પ્રકારવ્યાખ્યા EVRInitError HmdError;
પ્રકારવ્યાખ્યા EVREye Hmd_Eye;
પ્રકારવ્યાખ્યા EColorSpace ColorSpace;
પ્રકારવ્યાખ્યા ETrackingResult HmdTrackingResult;
પ્રકારવ્યાખ્યા ETrackedDeviceClass TrackedDeviceClass;
પ્રકારવ્યાખ્યા ETrackingUniverseOrigin TrackingUniverseOrigin;
પ્રકારવ્યાખ્યા ETrackedDeviceProperty TrackedDeviceProperty;
પ્રકારવ્યાખ્યા ETrackedPropertyError TrackedPropertyError;
પ્રકારવ્યાખ્યા EVRSubmitFlags VRSubmitFlags_t;
પ્રકારવ્યાખ્યા EVRState VRState_t;
પ્રકારવ્યાખ્યા ECollisionBoundsStyle CollisionBoundsStyle_t;
પ્રકારવ્યાખ્યા EVROverlayError VROverlayError;
પ્રકારવ્યાખ્યા EVRFirmwareError VRFirmwareError;
પ્રકારવ્યાખ્યા EVRCompositorError VRCompositorError;
પ્રકારવ્યાખ્યા EVRScreenshotError VRScreenshotsError;
પ્રકારવ્યાખ્યા uint64_t PathHandle_t;

// OpenVR Structs

પ્રકારવ્યાખ્યા સંરચના HmdMatrix34_t
{
	દશાંશ m[3][4]; //float[3][4]
} HmdMatrix34_t;

પ્રકારવ્યાખ્યા સંરચના HmdMatrix33_t
{
	દશાંશ m[3][3]; //float[3][3]
} HmdMatrix33_t;

પ્રકારવ્યાખ્યા સંરચના HmdMatrix44_t
{
	દશાંશ m[4][4]; //float[4][4]
} HmdMatrix44_t;

પ્રકારવ્યાખ્યા સંરચના HmdVector3_t
{
	દશાંશ v[3]; //float[3]
} HmdVector3_t;

પ્રકારવ્યાખ્યા સંરચના HmdVector4_t
{
	દશાંશ v[4]; //float[4]
} HmdVector4_t;

પ્રકારવ્યાખ્યા સંરચના HmdVector3d_t
{
	દ્વિગુણ v[3]; //double[3]
} HmdVector3d_t;

પ્રકારવ્યાખ્યા સંરચના HmdVector2_t
{
	દશાંશ v[2]; //float[2]
} HmdVector2_t;

પ્રકારવ્યાખ્યા સંરચના HmdQuaternion_t
{
	દ્વિગુણ w;
	દ્વિગુણ x;
	દ્વિગુણ y;
	દ્વિગુણ z;
} HmdQuaternion_t;

પ્રકારવ્યાખ્યા સંરચના HmdQuaternionf_t
{
	દશાંશ w;
	દશાંશ x;
	દશાંશ y;
	દશાંશ z;
} HmdQuaternionf_t;

પ્રકારવ્યાખ્યા સંરચના HmdColor_t
{
	દશાંશ r;
	દશાંશ g;
	દશાંશ b;
	દશાંશ a;
} HmdColor_t;

પ્રકારવ્યાખ્યા સંરચના HmdQuad_t
{
	સંરચના HmdVector3_t vCorners[4]; //struct vr::HmdVector3_t[4]
} HmdQuad_t;

પ્રકારવ્યાખ્યા સંરચના HmdRect2_t
{
	સંરચના HmdVector2_t v_ટોચ_ડાબું;
	સંરચના HmdVector2_t v_Bottom_જમણું;
} HmdRect2_t;

પ્રકારવ્યાખ્યા સંરચના VRBoneTransform_t
{
	સંરચના HmdVector4_t position;
	સંરચના HmdQuaternionf_t orientation;
} VRBoneTransform_t;

પ્રકારવ્યાખ્યા સંરચના DistortionCoordinates_t
{
	દશાંશ rfRed[2]; //float[2]
	દશાંશ rfGreen[2]; //float[2]
	દશાંશ rfBlue[2]; //float[2]
} DistortionCoordinates_t;

પ્રકારવ્યાખ્યા સંરચના Texture_t
{
	શૂન્ય * handle; // void *
	ગણના ETextureType eType;
	ગણના EColorSpace eColorSpace;
} Texture_t;

પ્રકારવ્યાખ્યા સંરચના TrackedDevicePose_t
{
	સંરચના HmdMatrix34_t mDeviceToAbsoluteTracking;
	સંરચના HmdVector3_t vVelocity;
	સંરચના HmdVector3_t vAngularVelocity;
	ગણના ETrackingResult eTrackingResult;
	bool bPoseIsValid;
	bool bDeviceIsConnected;
} TrackedDevicePose_t;

પ્રકારવ્યાખ્યા સંરચના VRTextureBounds_t
{
	દશાંશ uMin;
	દશાંશ vMin;
	દશાંશ uMax;
	દશાંશ vMax;
} VRTextureBounds_t;

પ્રકારવ્યાખ્યા સંરચના VRTextureWithPose_t
{
	શૂન્ય * handle; // void *
	ગણના ETextureType eType;
	ગણના EColorSpace eColorSpace;
	સંરચના HmdMatrix34_t mDeviceToAbsoluteTracking;
} VRTextureWithPose_t;

પ્રકારવ્યાખ્યા સંરચના VRTextureDepthInfo_t
{
	શૂન્ય * handle; // void *
	સંરચના HmdMatrix44_t mProjection;
	સંરચના HmdVector2_t vRange;
} VRTextureDepthInfo_t;

પ્રકારવ્યાખ્યા સંરચના VRTextureWithDepth_t
{
	શૂન્ય * handle; // void *
	ગણના ETextureType eType;
	ગણના EColorSpace eColorSpace;
	સંરચના VRTextureDepthInfo_t depth;
} VRTextureWithDepth_t;

પ્રકારવ્યાખ્યા સંરચના VRTextureWithPoseAndDepth_t
{
	શૂન્ય * handle; // void *
	ગણના ETextureType eType;
	ગણના EColorSpace eColorSpace;
	સંરચના HmdMatrix34_t mDeviceToAbsoluteTracking;
	સંરચના VRTextureDepthInfo_t depth;
} VRTextureWithPoseAndDepth_t;

પ્રકારવ્યાખ્યા સંરચના VRVulkanTextureData_t
{
	uint64_t m_nImage;
	સંરચના VkDevice_T * m_pDevice; // struct VkDevice_T *
	સંરચના VkPhysicalDevice_T * m_pPhysicalDevice; // struct VkPhysicalDevice_T *
	સંરચના VkInstance_T * m_pInstance; // struct VkInstance_T *
	સંરચના VkQueue_T * m_pQueue; // struct VkQueue_T *
	uint32_t m_nQueueFamilyIndex;
	uint32_t m_nWidth;
	uint32_t m_nHeight;
	uint32_t m_nFormat;
	uint32_t m_n_Sample_ગણતરી;
} VRVulkanTextureData_t;

પ્રકારવ્યાખ્યા સંરચના VRVulkanTextureArrayData_t
{
	uint32_t m_unArrayIndex;
	uint32_t m_unArraySize;
} VRVulkanTextureArrayData_t;

પ્રકારવ્યાખ્યા સંરચના D3D12TextureData_t
{
	સંરચના ID3D12Resource * m_pResource; // struct ID3D12Resource *
	સંરચના ID3D12CommandQueue * m_pCommandQueue; // struct ID3D12CommandQueue *
	uint32_t m_n_ગાંઠ_Mask;
} D3D12TextureData_t;

પ્રકારવ્યાખ્યા સંરચના VREvent_Controller_t
{
	uint32_t button;
} VREvent_Controller_t;

પ્રકારવ્યાખ્યા સંરચના VREvent_Mouse_t
{
	દશાંશ x;
	દશાંશ y;
	uint32_t button;
} VREvent_Mouse_t;

પ્રકારવ્યાખ્યા સંરચના VREvent_Scroll_t
{
	દશાંશ xdelta;
	દશાંશ ydelta;
	uint32_t unused;
	દશાંશ viewportscale;
} VREvent_Scroll_t;

પ્રકારવ્યાખ્યા સંરચના VREvent_TouchPadMove_t
{
	bool bFingerDown;
	દશાંશ flSecondsFingerDown;
	દશાંશ f_કિંમત_XFirst;
	દશાંશ f_કિંમત_YFirst;
	દશાંશ f_કિંમત_XRaw;
	દશાંશ f_કિંમત_YRaw;
} VREvent_TouchPadMove_t;

પ્રકારવ્યાખ્યા સંરચના VREvent_Notification_t
{
	uint64_t ul_User_કિંમત;
	uint32_t notificationId;
} VREvent_Notification_t;

પ્રકારવ્યાખ્યા સંરચના VREvent_Process_t
{
	uint32_t pid;
	uint32_t oldPid;
	bool bForced;
	bool bConnectionLost;
} VREvent_Process_t;

પ્રકારવ્યાખ્યા સંરચના VREvent_Overlay_t
{
	uint64_t overlayHandle;
	uint64_t devicePath;
	uint64_t memoryBlockId;
} VREvent_Overlay_t;

પ્રકારવ્યાખ્યા સંરચના VREvent_Status_t
{
	uint32_t statusState;
} VREvent_Status_t;

પ્રકારવ્યાખ્યા સંરચના VREvent_Keyboard_t
{
	અક્ષર c_New_આગત[8]; //char[8]
	uint64_t u_User_કિંમત;
} VREvent_Keyboard_t;

પ્રકારવ્યાખ્યા સંરચના VREvent_Ipd_t
{
	દશાંશ ipdMeters;
} VREvent_Ipd_t;

પ્રકારવ્યાખ્યા સંરચના VREvent_Chaperone_t
{
	uint64_t m_nPreviousUniverse;
	uint64_t m_nCurrentUniverse;
} VREvent_Chaperone_t;

પ્રકારવ્યાખ્યા સંરચના VREvent_Reserved_t
{
	uint64_t reserved0;
	uint64_t reserved1;
	uint64_t reserved2;
	uint64_t reserved3;
	uint64_t reserved4;
	uint64_t reserved5;
} VREvent_Reserved_t;

પ્રકારવ્યાખ્યા સંરચના VREvent_PerformanceTest_t
{
	uint32_t m_nFidelityLevel;
} VREvent_PerformanceTest_t;

પ્રકારવ્યાખ્યા સંરચના VREvent_SeatedZeroPoseReset_t
{
	bool bResetBySystemMenu;
} VREvent_SeatedZeroPoseReset_t;

પ્રકારવ્યાખ્યા સંરચના VREvent_Screenshot_t
{
	uint32_t handle;
	uint32_t type;
} VREvent_Screenshot_t;

પ્રકારવ્યાખ્યા સંરચના VREvent_ScreenshotProgress_t
{
	દશાંશ progress;
} VREvent_ScreenshotProgress_t;

પ્રકારવ્યાખ્યા સંરચના VREvent_ApplicationLaunch_t
{
	uint32_t pid;
	uint32_t unArgsHandle;
} VREvent_ApplicationLaunch_t;

પ્રકારવ્યાખ્યા સંરચના VREvent_EditingCameraSurface_t
{
	uint64_t overlayHandle;
	uint32_t nVisualMode;
} VREvent_EditingCameraSurface_t;

પ્રકારવ્યાખ્યા સંરચના VREvent_MessageOverlay_t
{
	uint32_t unVRMessageOverlayResponse;
} VREvent_MessageOverlay_t;

પ્રકારવ્યાખ્યા સંરચના VREvent_Property_t
{
	PropertyContainerHandle_t container;
	ગણના ETrackedDeviceProperty prop;
} VREvent_Property_t;

પ્રકારવ્યાખ્યા સંરચના VREvent_HapticVibration_t
{
	uint64_t containerHandle;
	uint64_t componentHandle;
	દશાંશ fDurationSeconds;
	દશાંશ fFrequency;
	દશાંશ fAmplitude;
} VREvent_HapticVibration_t;

પ્રકારવ્યાખ્યા સંરચના VREvent_WebConsole_t
{
	WebConsoleHandle_t webConsoleHandle;
} VREvent_WebConsole_t;

પ્રકારવ્યાખ્યા સંરચના VREvent_આગત_Binding_Load_t
{
	PropertyContainerHandle_t ulAppContainer;
	uint64_t pathMessage;
	uint64_t pathUrl;
	uint64_t pathControllerType;
} VREvent_આગત_Binding_Load_t;

પ્રકારવ્યાખ્યા સંરચના VREvent_આગત_Action_Manifest_Load_t
{
	uint64_t path_App_ચાવી;
	uint64_t pathMessage;
	uint64_t pathMessageParam;
	uint64_t pathManifestPath;
} VREvent_આગત_Action_Manifest_Load_t;

પ્રકારવ્યાખ્યા સંરચના VREvent_SpatialAnchor_t
{
	SpatialAnchorHandle_t unHandle;
} VREvent_SpatialAnchor_t;

પ્રકારવ્યાખ્યા સંરચના VREvent_ProgressUpdate_t
{
	uint64_t ulApplicationPropertyContainer;
	uint64_t pathDevice;
	uint64_t path_આગત_Source;
	uint64_t pathProgressAction;
	uint64_t pathIcon;
	દશાંશ fProgress;
} VREvent_ProgressUpdate_t;

પ્રકારવ્યાખ્યા સંરચના VREvent_ShowUI_t
{
	ગણના EShowUIType eType;
} VREvent_ShowUI_t;

પ્રકારવ્યાખ્યા સંરચના VREvent_ShowDevTools_t
{
	int32_t nBrowserIdentifier;
} VREvent_ShowDevTools_t;

પ્રકારવ્યાખ્યા સંરચના VREvent_HDCPError_t
{
	ગણના EHDCPError eCode;
} VREvent_HDCPError_t;

પ્રકારવ્યાખ્યા સંરચના RenderModel_ComponentState_t
{
	સંરચના HmdMatrix34_t mTrackingToComponentRenderModel;
	સંરચના HmdMatrix34_t mTrackingToComponentLocal;
	VRComponentProperties uProperties;
} RenderModel_ComponentState_t;

પ્રકારવ્યાખ્યા સંરચના HiddenAreaMesh_t
{
	સંરચના HmdVector2_t * pVertexData; // const struct vr::HmdVector2_t *
	uint32_t un_Triangle_ગણતરી;
} HiddenAreaMesh_t;

પ્રકારવ્યાખ્યા સંરચના VRControllerAxis_t
{
	દશાંશ x;
	દશાંશ y;
} VRControllerAxis_t;

પ્રકારવ્યાખ્યા સંરચના VRControllerState_t
{
	uint32_t un_Packet_અંક;
	uint64_t ulButtonPressed;
	uint64_t ulButtonTouched;
	સંરચના VRControllerAxis_t rAxis[5]; //struct vr::VRControllerAxis_t[5]
} VRControllerState_t;

પ્રકારવ્યાખ્યા સંરચના CameraVideoStreamFrameHeader_t
{
	ગણના EVRTrackedCameraFrameType eFrameType;
	uint32_t nWidth;
	uint32_t nHeight;
	uint32_t nBytesPerPixel;
	uint32_t nFrameSequence;
	સંરચના TrackedDevicePose_t trackedDevicePose;
	uint64_t ulFrameExposureTime;
} CameraVideoStreamFrameHeader_t;

પ્રકારવ્યાખ્યા સંરચના Compositor_FrameTiming
{
	uint32_t m_nSize;
	uint32_t m_nFrameIndex;
	uint32_t m_n_અંક_Frame_Presents;
	uint32_t m_n_અંક_Mis_Presented;
	uint32_t m_n_અંક_Dropped_Frames;
	uint32_t m_nReprojectionFlags;
	દ્વિગુણ m_flSystemTimeInSeconds;
	દશાંશ m_flPreSubmitGpuMs;
	દશાંશ m_flPostSubmitGpuMs;
	દશાંશ m_flTotalRenderGpuMs;
	દશાંશ m_flCompositorRenderGpuMs;
	દશાંશ m_flCompositorRenderCpuMs;
	દશાંશ m_flCompositorIdleCpuMs;
	દશાંશ m_flClientFrameIntervalMs;
	દશાંશ m_flPresentCallCpuMs;
	દશાંશ m_flWaitForPresentCpuMs;
	દશાંશ m_flSubmitFrameMs;
	દશાંશ m_flWaitGetPosesCalledMs;
	દશાંશ m_flNewPosesReadyMs;
	દશાંશ m_flNewFrameReadyMs;
	દશાંશ m_flCompositorUpdateStartMs;
	દશાંશ m_flCompositorUpdateEndMs;
	દશાંશ m_flCompositorRenderStartMs;
	TrackedDevicePose_t m_HmdPose;
	uint32_t m_n_અંક_VSyncs_Ready_For_Use;
	uint32_t m_n_અંક_VSyncs_To_First_View;
} Compositor_FrameTiming;

પ્રકારવ્યાખ્યા સંરચના Compositor_BenchmarkResults
{
	દશાંશ m_flMegaPixelsPerSecond;
	દશાંશ m_flHmdRecommendedMegaPixelsPerSecond;
} Compositor_BenchmarkResults;

પ્રકારવ્યાખ્યા સંરચના DriverDirectMode_FrameTiming
{
	uint32_t m_nSize;
	uint32_t m_n_અંક_Frame_Presents;
	uint32_t m_n_અંક_Mis_Presented;
	uint32_t m_n_અંક_Dropped_Frames;
	uint32_t m_nReprojectionFlags;
} DriverDirectMode_FrameTiming;

પ્રકારવ્યાખ્યા સંરચના ImuSample_t
{
	દ્વિગુણ fSampleTime;
	સંરચના HmdVector3d_t vAccel;
	સંરચના HmdVector3d_t vGyro;
	uint32_t unOffScaleFlags;
} ImuSample_t;

પ્રકારવ્યાખ્યા સંરચના App_Override_ચાવીઓ_t
{
	અક્ષર * pch_ચાવી; // const char *
	અક્ષર * pch_કિંમત; // const char *
} App_Override_ચાવીઓ_t;

પ્રકારવ્યાખ્યા સંરચના Compositor_CumulativeStats
{
	uint32_t m_nPid;
	uint32_t m_n_અંક_Frame_Presents;
	uint32_t m_n_અંક_Dropped_Frames;
	uint32_t m_n_અંક_Reprojected_Frames;
	uint32_t m_n_અંક_Frame_Presents_On_Startup;
	uint32_t m_n_અંક_Dropped_Frames_On_Startup;
	uint32_t m_n_અંક_Reprojected_Frames_On_Startup;
	uint32_t m_n_અંક_Loading;
	uint32_t m_n_અંક_Frame_Presents_Loading;
	uint32_t m_n_અંક_Dropped_Frames_Loading;
	uint32_t m_n_અંક_Reprojected_Frames_Loading;
	uint32_t m_n_અંક_Timed_Out;
	uint32_t m_n_અંક_Frame_Presents_Timed_Out;
	uint32_t m_n_અંક_Dropped_Frames_Timed_Out;
	uint32_t m_n_અંક_Reprojected_Frames_Timed_Out;
	uint32_t m_n_અંક_Frame_Submits;
	દ્વિગુણ m_flSumCompositorCPUTimeMS;
	દ્વિગુણ m_flSumCompositorGPUTimeMS;
	દ્વિગુણ m_flSumTargetFrameTimes;
	દ્વિગુણ m_flSumApplicationCPUTimeMS;
	દ્વિગુણ m_flSumApplicationGPUTimeMS;
} Compositor_CumulativeStats;

પ્રકારવ્યાખ્યા સંરચના Compositor_StageRenderSettings
{
	સંરચના HmdColor_t m_PrimaryColor;
	સંરચના HmdColor_t m_SecondaryColor;
	દશાંશ m_flVignetteInnerRadius;
	દશાંશ m_flVignetteOuterRadius;
	દશાંશ m_flFresnelStrength;
	bool m_bBackfaceCulling;
	bool m_bGreyscale;
	bool m_bWireframe;
} Compositor_StageRenderSettings;

પ્રકારવ્યાખ્યા સંરચના VROverlayIntersectionParams_t
{
	સંરચના HmdVector3_t vSource;
	સંરચના HmdVector3_t vDirection;
	ગણના ETrackingUniverseOrigin eOrigin;
} VROverlayIntersectionParams_t;

પ્રકારવ્યાખ્યા સંરચના VROverlayIntersectionResults_t
{
	સંરચના HmdVector3_t vPoint;
	સંરચના HmdVector3_t vNormal;
	સંરચના HmdVector2_t vUVs;
	દશાંશ fDistance;
} VROverlayIntersectionResults_t;

પ્રકારવ્યાખ્યા સંરચના IntersectionMaskRectangle_t
{
	દશાંશ m_fl_ટોચ_ડાબું_X;
	દશાંશ m_fl_ટોચ_ડાબું_Y;
	દશાંશ m_flWidth;
	દશાંશ m_flHeight;
} IntersectionMaskRectangle_t;

પ્રકારવ્યાખ્યા સંરચના IntersectionMaskCircle_t
{
	દશાંશ m_flCenterX;
	દશાંશ m_flCenterY;
	દશાંશ m_flRadius;
} IntersectionMaskCircle_t;

પ્રકારવ્યાખ્યા સંરચના VROverlayProjection_t
{
	દશાંશ f_ડાબું;
	દશાંશ f_જમણું;
	દશાંશ f_ટોચ;
	દશાંશ fBottom;
} VROverlayProjection_t;

પ્રકારવ્યાખ્યા સંરચના VROverlayView_t
{
	VROverlayHandle_t overlayHandle;
	સંરચના Texture_t texture;
	સંરચના VRTextureBounds_t textureBounds;
} VROverlayView_t;

પ્રકારવ્યાખ્યા સંરચના VRVulkanDevice_t
{
	સંરચના VkInstance_T * m_pInstance; // struct VkInstance_T *
	સંરચના VkDevice_T * m_pDevice; // struct VkDevice_T *
	સંરચના VkPhysicalDevice_T * m_pPhysicalDevice; // struct VkPhysicalDevice_T *
	સંરચના VkQueue_T * m_pQueue; // struct VkQueue_T *
	uint32_t m_uQueueFamilyIndex;
} VRVulkanDevice_t;

પ્રકારવ્યાખ્યા સંરચના VRNativeDevice_t
{
	શૂન્ય * handle; // void *
	ગણના EDeviceType eType;
} VRNativeDevice_t;

પ્રકારવ્યાખ્યા સંરચના RenderModel_Vertex_t
{
	સંરચના HmdVector3_t vPosition;
	સંરચના HmdVector3_t vNormal;
	દશાંશ rfTextureCoord[2]; //float[2]
} RenderModel_Vertex_t;

#જો defined(__linux__) || defined(__APPLE__)
#pragma pack( ધકેલો, 4 )
#endif
પ્રકારવ્યાખ્યા સંરચના RenderModel_TextureMap_t
{
	uint16_t unWidth;
	uint16_t unHeight;
	uint8_t * rubTextureMapData; // const uint8_t *
	ગણના EVRRenderModelTextureFormat format;
	uint16_t unMipLevels;
} RenderModel_TextureMap_t;

#જો defined(__linux__) || defined(__APPLE__)
#pragma pack( કાઢો )
#endif
#જો defined(__linux__) || defined(__APPLE__)
#pragma pack( ધકેલો, 4 )
#endif
પ્રકારવ્યાખ્યા સંરચના RenderModel_t
{
	સંરચના RenderModel_Vertex_t * rVertexData; // const struct vr::RenderModel_Vertex_t *
	uint32_t un_Vertex_ગણતરી;
	uint16_t * rIndexData; // const uint16_t *
	uint32_t un_Triangle_ગણતરી;
	TextureID_t diffuseTextureId;
} RenderModel_t;

#જો defined(__linux__) || defined(__APPLE__)
#pragma pack( કાઢો )
#endif
પ્રકારવ્યાખ્યા સંરચના RenderModel_ControllerMode_State_t
{
	bool bScrollWheelVisible;
} RenderModel_ControllerMode_State_t;

પ્રકારવ્યાખ્યા સંરચના NotificationBitmap_t
{
	શૂન્ય * m_pImageData; // void *
	int32_t m_nWidth;
	int32_t m_nHeight;
	int32_t m_nBytesPerPixel;
} NotificationBitmap_t;

પ્રકારવ્યાખ્યા સંરચના CVRSettingHelper
{
	intptr_t m_pSettings; // class vr::IVRSettings *
} CVRSettingHelper;

પ્રકારવ્યાખ્યા સંરચના આગત_Analog_Action_Data_t
{
	bool bActive;
	VRInput_કિંમત_Handle_t activeOrigin;
	દશાંશ x;
	દશાંશ y;
	દશાંશ z;
	દશાંશ deltaX;
	દશાંશ deltaY;
	દશાંશ deltaZ;
	દશાંશ fUpdateTime;
} આગત_Analog_Action_Data_t;

પ્રકારવ્યાખ્યા સંરચના આગત_Digital_Action_Data_t
{
	bool bActive;
	VRInput_કિંમત_Handle_t activeOrigin;
	bool bState;
	bool bChanged;
	દશાંશ fUpdateTime;
} આગત_Digital_Action_Data_t;

પ્રકારવ્યાખ્યા સંરચના આગત_Pose_Action_Data_t
{
	bool bActive;
	VRInput_કિંમત_Handle_t activeOrigin;
	સંરચના TrackedDevicePose_t pose;
} આગત_Pose_Action_Data_t;

પ્રકારવ્યાખ્યા સંરચના આગત_Skeletal_Action_Data_t
{
	bool bActive;
	VRInput_કિંમત_Handle_t activeOrigin;
} આગત_Skeletal_Action_Data_t;

પ્રકારવ્યાખ્યા સંરચના આગત_Origin_Info_t
{
	VRInput_કિંમત_Handle_t devicePath;
	TrackedDeviceIndex_t trackedDeviceIndex;
	અક્ષર rchRenderModelComponentName[128]; //char[128]
} આગત_Origin_Info_t;

પ્રકારવ્યાખ્યા સંરચના આગત_Binding_Info_t
{
	અક્ષર rchDevicePathName[128]; //char[128]
	અક્ષર rch_આગત_Path_Name[128]; //char[128]
	અક્ષર rchModeName[128]; //char[128]
	અક્ષર rchSlotName[128]; //char[128]
	અક્ષર rch_આગત_Source_Type[32]; //char[32]
} આગત_Binding_Info_t;

પ્રકારવ્યાખ્યા સંરચના VRActiveActionSet_t
{
	VRActionSetHandle_t ulActionSet;
	VRInput_કિંમત_Handle_t ulRestrictedToDevice;
	VRActionSetHandle_t ulSecondaryActionSet;
	uint32_t unPadding;
	int32_t nPriority;
} VRActiveActionSet_t;

પ્રકારવ્યાખ્યા સંરચના VRSkeletalSummaryData_t
{
	દશાંશ flFingerCurl[5]; //float[5]
	દશાંશ flFingerSplay[4]; //float[4]
} VRSkeletalSummaryData_t;

પ્રકારવ્યાખ્યા સંરચના SpatialAnchorPose_t
{
	સંરચના HmdMatrix34_t mAnchorToAbsoluteTracking;
} SpatialAnchorPose_t;

પ્રકારવ્યાખ્યા સંરચના COpenVRContext
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

પ્રકારવ્યાખ્યા સંરચના PropertyWrite_t
{
	ગણના ETrackedDeviceProperty prop;
	ગણના EPropertyWriteType writeType;
	ગણના ETrackedPropertyError eSetError;
	શૂન્ય * pvBuffer; // void *
	uint32_t unBufferSize;
	PropertyTypeTag_t unTag;
	ગણના ETrackedPropertyError eError;
} PropertyWrite_t;

પ્રકારવ્યાખ્યા સંરચના PropertyRead_t
{
	ગણના ETrackedDeviceProperty prop;
	શૂન્ય * pvBuffer; // void *
	uint32_t unBufferSize;
	PropertyTypeTag_t unTag;
	uint32_t unRequiredBufferSize;
	ગણના ETrackedPropertyError eError;
} PropertyRead_t;

પ્રકારવ્યાખ્યા સંરચના CVRPropertyHelpers
{
	intptr_t m_pProperties; // class vr::IVRProperties *
} CVRPropertyHelpers;

પ્રકારવ્યાખ્યા સંરચના PathWrite_t
{
	PathHandle_t ulPath;
	ગણના EPropertyWriteType writeType;
	ગણના ETrackedPropertyError eSetError;
	શૂન્ય * pvBuffer; // void *
	uint32_t unBufferSize;
	PropertyTypeTag_t unTag;
	ગણના ETrackedPropertyError eError;
	અક્ષર * pszPath; // const char *
} PathWrite_t;

પ્રકારવ્યાખ્યા સંરચના PathRead_t
{
	PathHandle_t ulPath;
	શૂન્ય * pvBuffer; // void *
	uint32_t unBufferSize;
	PropertyTypeTag_t unTag;
	uint32_t unRequiredBufferSize;
	ગણના ETrackedPropertyError eError;
	અક્ષર * pszPath; // const char *
} PathRead_t;


પ્રકારવ્યાખ્યા સંઘ
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
	VREvent_આગત_Binding_Load_t આગત_Binding;
	VREvent_આગત_Action_Manifest_Load_t actionManifest;
	VREvent_SpatialAnchor_t spatialAnchor;
} VREvent_Data_t;

#જો defined(__linux__) || defined(__APPLE__) 
// This structure was originally defined mis-packed on Linux, preserved for 
// compatibility. 
#pragma pack( ધકેલો, 4 )
#endif

/** An event posted by the server to all running applications */
સંરચના VREvent_t
{
	uint32_t eventType; // EVREventType enum
	TrackedDeviceIndex_t trackedDeviceIndex;
	દશાંશ eventAgeSeconds;
	// event data must be the end of the struct as its size is variable
	VREvent_Data_t data;
};

#જો defined(__linux__) || defined(__APPLE__) 
#pragma pack( કાઢો )
#endif


પ્રકારવ્યાખ્યા સંઘ
{
	IntersectionMaskRectangle_t m_Rectangle;
	IntersectionMaskCircle_t m_Circle;
} VROverlayIntersectionMaskPrimitive_Data_t;

સંરચના VROverlayIntersectionMaskPrimitive_t
{
	EVROverlayIntersectionMaskPrimitiveType m_nPrimitiveType;
	VROverlayIntersectionMaskPrimitive_Data_t m_Primitive;
};


// OpenVR Function Pointer Tables

સંરચના VR_IVRSystem_FnTable
{
	શૂન્ય (OPENVR_FNTABLE_CALLTYPE *GetRecommendedRenderTargetSize)(uint32_t * pnWidth, uint32_t * pnHeight);
	સંરચના HmdMatrix44_t (OPENVR_FNTABLE_CALLTYPE *GetProjectionMatrix)(EVREye eEye, દશાંશ fNearZ, દશાંશ fFarZ);
	શૂન્ય (OPENVR_FNTABLE_CALLTYPE *GetProjectionRaw)(EVREye eEye, દશાંશ * pf_ડાબું, દશાંશ * pf_જમણું, દશાંશ * pf_ટોચ, દશાંશ * pfBottom);
	bool (OPENVR_FNTABLE_CALLTYPE *ComputeDistortion)(EVREye eEye, દશાંશ fU, દશાંશ fV, સંરચના DistortionCoordinates_t * pDistortionCoordinates);
	સંરચના HmdMatrix34_t (OPENVR_FNTABLE_CALLTYPE *GetEyeToHeadTransform)(EVREye eEye);
	bool (OPENVR_FNTABLE_CALLTYPE *GetTimeSinceLastVsync)(દશાંશ * pfSecondsSinceLastVsync, uint64_t * pulFrameCounter);
	int32_t (OPENVR_FNTABLE_CALLTYPE *GetD3D9AdapterIndex)();
	શૂન્ય (OPENVR_FNTABLE_CALLTYPE *GetDXGIOutputInfo)(int32_t * pnAdapterIndex);
	શૂન્ય (OPENVR_FNTABLE_CALLTYPE *GetOutputDevice)(uint64_t * pnDevice, ETextureType textureType, સંરચના VkInstance_T * pInstance);
	bool (OPENVR_FNTABLE_CALLTYPE *IsDisplayOnDesktop)();
	bool (OPENVR_FNTABLE_CALLTYPE *SetDisplayVisibility)(bool bIsVisibleOnDesktop);
	શૂન્ય (OPENVR_FNTABLE_CALLTYPE *GetDeviceToAbsoluteTrackingPose)(ETrackingUniverseOrigin eOrigin, દશાંશ fPredictedSecondsToPhotonsFromNow, સંરચના TrackedDevicePose_t * pTrackedDevicePoseArray, uint32_t un_Tracked_Device_Pose_Array_ગણતરી);
	સંરચના HmdMatrix34_t (OPENVR_FNTABLE_CALLTYPE *GetSeatedZeroPoseToStandingAbsoluteTrackingPose)();
	સંરચના HmdMatrix34_t (OPENVR_FNTABLE_CALLTYPE *GetRawZeroPoseToStandingAbsoluteTrackingPose)();
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetSortedTrackedDeviceIndicesOfClass)(ETrackedDeviceClass eTrackedDeviceClass, TrackedDeviceIndex_t * punTrackedDeviceIndexArray, uint32_t un_Tracked_Device_Index_Array_ગણતરી, TrackedDeviceIndex_t unRelativeToTrackedDeviceIndex);
	EDeviceActivityLevel (OPENVR_FNTABLE_CALLTYPE *GetTrackedDeviceActivityLevel)(TrackedDeviceIndex_t unDeviceId);
	શૂન્ય (OPENVR_FNTABLE_CALLTYPE *ApplyTransform)(સંરચના TrackedDevicePose_t * pOutputPose, સંરચના TrackedDevicePose_t * pTrackedDevicePose, સંરચના HmdMatrix34_t * pTransform);
	TrackedDeviceIndex_t (OPENVR_FNTABLE_CALLTYPE *GetTrackedDeviceIndexForControllerRole)(ETrackedControllerRole unDeviceType);
	ETrackedControllerRole (OPENVR_FNTABLE_CALLTYPE *GetControllerRoleForTrackedDeviceIndex)(TrackedDeviceIndex_t unDeviceIndex);
	ETrackedDeviceClass (OPENVR_FNTABLE_CALLTYPE *GetTrackedDeviceClass)(TrackedDeviceIndex_t unDeviceIndex);
	bool (OPENVR_FNTABLE_CALLTYPE *IsTrackedDeviceConnected)(TrackedDeviceIndex_t unDeviceIndex);
	bool (OPENVR_FNTABLE_CALLTYPE *GetBoolTrackedDeviceProperty)(TrackedDeviceIndex_t unDeviceIndex, ETrackedDeviceProperty prop, ETrackedPropertyError * pError);
	દશાંશ (OPENVR_FNTABLE_CALLTYPE *GetFloatTrackedDeviceProperty)(TrackedDeviceIndex_t unDeviceIndex, ETrackedDeviceProperty prop, ETrackedPropertyError * pError);
	int32_t (OPENVR_FNTABLE_CALLTYPE *GetInt32TrackedDeviceProperty)(TrackedDeviceIndex_t unDeviceIndex, ETrackedDeviceProperty prop, ETrackedPropertyError * pError);
	uint64_t (OPENVR_FNTABLE_CALLTYPE *GetUint64TrackedDeviceProperty)(TrackedDeviceIndex_t unDeviceIndex, ETrackedDeviceProperty prop, ETrackedPropertyError * pError);
	સંરચના HmdMatrix34_t (OPENVR_FNTABLE_CALLTYPE *GetMatrix34TrackedDeviceProperty)(TrackedDeviceIndex_t unDeviceIndex, ETrackedDeviceProperty prop, ETrackedPropertyError * pError);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetArrayTrackedDeviceProperty)(TrackedDeviceIndex_t unDeviceIndex, ETrackedDeviceProperty prop, PropertyTypeTag_t propType, શૂન્ય * pBuffer, uint32_t unBufferSize, ETrackedPropertyError * pError);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetStringTrackedDeviceProperty)(TrackedDeviceIndex_t unDeviceIndex, ETrackedDeviceProperty prop, અક્ષર * pch_કિંમત, uint32_t unBufferSize, ETrackedPropertyError * pError);
	અક્ષર * (OPENVR_FNTABLE_CALLTYPE *GetPropErrorNameFromEnum)(ETrackedPropertyError error);
	bool (OPENVR_FNTABLE_CALLTYPE *PollNextEvent)(સંરચના VREvent_t * pEvent, uint32_t uncbVREvent);
	bool (OPENVR_FNTABLE_CALLTYPE *PollNextEventWithPose)(ETrackingUniverseOrigin eOrigin, સંરચના VREvent_t * pEvent, uint32_t uncbVREvent, TrackedDevicePose_t * pTrackedDevicePose);
	અક્ષર * (OPENVR_FNTABLE_CALLTYPE *GetEventTypeNameFromEnum)(EVREventType eType);
	સંરચના HiddenAreaMesh_t (OPENVR_FNTABLE_CALLTYPE *GetHiddenAreaMesh)(EVREye eEye, EHiddenAreaMeshType type);
	bool (OPENVR_FNTABLE_CALLTYPE *GetControllerState)(TrackedDeviceIndex_t unControllerDeviceIndex, VRControllerState_t * pControllerState, uint32_t unControllerStateSize);
	bool (OPENVR_FNTABLE_CALLTYPE *GetControllerStateWithPose)(ETrackingUniverseOrigin eOrigin, TrackedDeviceIndex_t unControllerDeviceIndex, VRControllerState_t * pControllerState, uint32_t unControllerStateSize, સંરચના TrackedDevicePose_t * pTrackedDevicePose);
	શૂન્ય (OPENVR_FNTABLE_CALLTYPE *TriggerHapticPulse)(TrackedDeviceIndex_t unControllerDeviceIndex, uint32_t unAxisId, unsigned short usDurationMicroSec);
	અક્ષર * (OPENVR_FNTABLE_CALLTYPE *GetButtonIdNameFromEnum)(EVRButtonId eButtonId);
	અક્ષર * (OPENVR_FNTABLE_CALLTYPE *GetControllerAxisTypeNameFromEnum)(EVRControllerAxisType eAxisType);
	bool (OPENVR_FNTABLE_CALLTYPE *Is_આગત_Available)();
	bool (OPENVR_FNTABLE_CALLTYPE *IsSteamVRDrawingControllers)();
	bool (OPENVR_FNTABLE_CALLTYPE *ShouldApplicationPause)();
	bool (OPENVR_FNTABLE_CALLTYPE *ShouldApplicationReduceRenderingWork)();
	EVRFirmwareError (OPENVR_FNTABLE_CALLTYPE *PerformFirmwareUpdate)(TrackedDeviceIndex_t unDeviceIndex);
	શૂન્ય (OPENVR_FNTABLE_CALLTYPE *AcknowledgeQuit_Exiting)();
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetAppContainerFilePaths)(અક્ષર * pchBuffer, uint32_t unBufferSize);
	અક્ષર * (OPENVR_FNTABLE_CALLTYPE *GetRuntimeVersion)();
};

સંરચના VR_IVRExtendedDisplay_FnTable
{
	શૂન્ય (OPENVR_FNTABLE_CALLTYPE *GetWindowBounds)(int32_t * pnX, int32_t * pnY, uint32_t * pnWidth, uint32_t * pnHeight);
	શૂન્ય (OPENVR_FNTABLE_CALLTYPE *GetEyeOutputViewport)(EVREye eEye, uint32_t * pnX, uint32_t * pnY, uint32_t * pnWidth, uint32_t * pnHeight);
	શૂન્ય (OPENVR_FNTABLE_CALLTYPE *GetDXGIOutputInfo)(int32_t * pnAdapterIndex, int32_t * pnAdapterOutputIndex);
};

સંરચના VR_IVRTrackedCamera_FnTable
{
	અક્ષર * (OPENVR_FNTABLE_CALLTYPE *GetCameraErrorNameFromEnum)(EVRTrackedCameraError eCameraError);
	EVRTrackedCameraError (OPENVR_FNTABLE_CALLTYPE *HasCamera)(TrackedDeviceIndex_t nDeviceIndex, bool * pHasCamera);
	EVRTrackedCameraError (OPENVR_FNTABLE_CALLTYPE *GetCameraFrameSize)(TrackedDeviceIndex_t nDeviceIndex, EVRTrackedCameraFrameType eFrameType, uint32_t * pnWidth, uint32_t * pnHeight, uint32_t * pnFrameBufferSize);
	EVRTrackedCameraError (OPENVR_FNTABLE_CALLTYPE *GetCameraIntrinsics)(TrackedDeviceIndex_t nDeviceIndex, uint32_t nCameraIndex, EVRTrackedCameraFrameType eFrameType, HmdVector2_t * pFocalLength, HmdVector2_t * pCenter);
	EVRTrackedCameraError (OPENVR_FNTABLE_CALLTYPE *GetCameraProjection)(TrackedDeviceIndex_t nDeviceIndex, uint32_t nCameraIndex, EVRTrackedCameraFrameType eFrameType, દશાંશ flZNear, દશાંશ flZFar, HmdMatrix44_t * pProjection);
	EVRTrackedCameraError (OPENVR_FNTABLE_CALLTYPE *AcquireVideoStreamingService)(TrackedDeviceIndex_t nDeviceIndex, TrackedCameraHandle_t * pHandle);
	EVRTrackedCameraError (OPENVR_FNTABLE_CALLTYPE *ReleaseVideoStreamingService)(TrackedCameraHandle_t hTrackedCamera);
	EVRTrackedCameraError (OPENVR_FNTABLE_CALLTYPE *GetVideoStreamFrameBuffer)(TrackedCameraHandle_t hTrackedCamera, EVRTrackedCameraFrameType eFrameType, શૂન્ય * pFrameBuffer, uint32_t nFrameBufferSize, CameraVideoStreamFrameHeader_t * pFrameHeader, uint32_t nFrameHeaderSize);
	EVRTrackedCameraError (OPENVR_FNTABLE_CALLTYPE *GetVideoStreamTextureSize)(TrackedDeviceIndex_t nDeviceIndex, EVRTrackedCameraFrameType eFrameType, VRTextureBounds_t * pTextureBounds, uint32_t * pnWidth, uint32_t * pnHeight);
	EVRTrackedCameraError (OPENVR_FNTABLE_CALLTYPE *GetVideoStreamTextureD3D11)(TrackedCameraHandle_t hTrackedCamera, EVRTrackedCameraFrameType eFrameType, શૂન્ય * pD3D11DeviceOrResource, શૂન્ય ** ppD3D11ShaderResourceView, CameraVideoStreamFrameHeader_t * pFrameHeader, uint32_t nFrameHeaderSize);
	EVRTrackedCameraError (OPENVR_FNTABLE_CALLTYPE *GetVideoStreamTextureGL)(TrackedCameraHandle_t hTrackedCamera, EVRTrackedCameraFrameType eFrameType, glUInt_t * pglTextureId, CameraVideoStreamFrameHeader_t * pFrameHeader, uint32_t nFrameHeaderSize);
	EVRTrackedCameraError (OPENVR_FNTABLE_CALLTYPE *ReleaseVideoStreamTextureGL)(TrackedCameraHandle_t hTrackedCamera, glUInt_t glTextureId);
	શૂન્ય (OPENVR_FNTABLE_CALLTYPE *SetCameraTrackingSpace)(ETrackingUniverseOrigin eUniverse);
	ETrackingUniverseOrigin (OPENVR_FNTABLE_CALLTYPE *GetCameraTrackingSpace)();
};

સંરચના VR_IVRApplications_FnTable
{
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *AddApplicationManifest)(અક્ષર * pchApplicationManifestFullPath, bool bTemporary);
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *RemoveApplicationManifest)(અક્ષર * pchApplicationManifestFullPath);
	bool (OPENVR_FNTABLE_CALLTYPE *IsApplicationInstalled)(અક્ષર * pch_App_ચાવી);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *Get_Application_ગણતરી)();
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *Get_Application_ચાવી_By_Index)(uint32_t unApplicationIndex, અક્ષર * pch_App_ચાવી_Buffer, uint32_t un_App_ચાવી_Buffer_Len);
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *Get_Application_ચાવી_By_Process_Id)(uint32_t unProcessId, અક્ષર * pch_App_ચાવી_Buffer, uint32_t un_App_ચાવી_Buffer_Len);
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *LaunchApplication)(અક્ષર * pch_App_ચાવી);
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *LaunchTemplateApplication)(અક્ષર * pch_Template_App_ચાવી, અક્ષર * pch_New_App_ચાવી, સંરચના App_Override_ચાવીઓ_t * p_ચાવીઓ, uint32_t un_ચાવીઓ);
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *LaunchApplicationFromMimeType)(અક્ષર * pchMimeType, અક્ષર * pchArgs);
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *LaunchDashboardOverlay)(અક્ષર * pch_App_ચાવી);
	bool (OPENVR_FNTABLE_CALLTYPE *CancelApplicationLaunch)(અક્ષર * pch_App_ચાવી);
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *IdentifyApplication)(uint32_t unProcessId, અક્ષર * pch_App_ચાવી);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetApplicationProcessId)(અક્ષર * pch_App_ચાવી);
	અક્ષર * (OPENVR_FNTABLE_CALLTYPE *GetApplicationsErrorNameFromEnum)(EVRApplicationError error);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetApplicationPropertyString)(અક્ષર * pch_App_ચાવી, EVRApplicationProperty eProperty, અક્ષર * pch_Property_કિંમત_Buffer, uint32_t un_Property_કિંમત_Buffer_Len, EVRApplicationError * peError);
	bool (OPENVR_FNTABLE_CALLTYPE *GetApplicationPropertyBool)(અક્ષર * pch_App_ચાવી, EVRApplicationProperty eProperty, EVRApplicationError * peError);
	uint64_t (OPENVR_FNTABLE_CALLTYPE *GetApplicationPropertyUint64)(અક્ષર * pch_App_ચાવી, EVRApplicationProperty eProperty, EVRApplicationError * peError);
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *SetApplicationAutoLaunch)(અક્ષર * pch_App_ચાવી, bool bAutoLaunch);
	bool (OPENVR_FNTABLE_CALLTYPE *GetApplicationAutoLaunch)(અક્ષર * pch_App_ચાવી);
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *SetDefaultApplicationForMimeType)(અક્ષર * pch_App_ચાવી, અક્ષર * pchMimeType);
	bool (OPENVR_FNTABLE_CALLTYPE *GetDefaultApplicationForMimeType)(અક્ષર * pchMimeType, અક્ષર * pch_App_ચાવી_Buffer, uint32_t un_App_ચાવી_Buffer_Len);
	bool (OPENVR_FNTABLE_CALLTYPE *GetApplicationSupportedMimeTypes)(અક્ષર * pch_App_ચાવી, અક્ષર * pchMimeTypesBuffer, uint32_t unMimeTypesBuffer);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetApplicationsThatSupportMimeType)(અક્ષર * pchMimeType, અક્ષર * pch_App_ચાવીઓ_That_Support_Buffer, uint32_t un_App_ચાવીઓ_That_Support_Buffer);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetApplicationLaunchArguments)(uint32_t unHandle, અક્ષર * pchArgs, uint32_t unArgs);
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *GetStartingApplication)(અક્ષર * pch_App_ચાવી_Buffer, uint32_t un_App_ચાવી_Buffer_Len);
	EVRSceneApplicationState (OPENVR_FNTABLE_CALLTYPE *GetSceneApplicationState)();
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *PerformApplicationPrelaunchCheck)(અક્ષર * pch_App_ચાવી);
	અક્ષર * (OPENVR_FNTABLE_CALLTYPE *GetSceneApplicationStateNameFromEnum)(EVRSceneApplicationState state);
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *LaunchInternalProcess)(અક્ષર * pch_દ્વિઅંકી_Path, અક્ષર * pchArguments, અક્ષર * pchWorkingDirectory);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetCurrentSceneProcessId)();
};

સંરચના VR_IVRChaperone_FnTable
{
	ChaperoneCalibrationState (OPENVR_FNTABLE_CALLTYPE *GetCalibrationState)();
	bool (OPENVR_FNTABLE_CALLTYPE *GetPlayAreaSize)(દશાંશ * pSizeX, દશાંશ * pSizeZ);
	bool (OPENVR_FNTABLE_CALLTYPE *GetPlayAreaRect)(સંરચના HmdQuad_t * rect);
	શૂન્ય (OPENVR_FNTABLE_CALLTYPE *ReloadInfo)();
	શૂન્ય (OPENVR_FNTABLE_CALLTYPE *SetSceneColor)(સંરચના HmdColor_t color);
	શૂન્ય (OPENVR_FNTABLE_CALLTYPE *GetBoundsColor)(સંરચના HmdColor_t * pOutputColorArray, પૂર્ણાંક n_અંક_Output_Colors, દશાંશ flCollisionBoundsFadeDistance, સંરચના HmdColor_t * pOutputCameraColor);
	bool (OPENVR_FNTABLE_CALLTYPE *AreBoundsVisible)();
	શૂન્ય (OPENVR_FNTABLE_CALLTYPE *ForceBoundsVisible)(bool bForce);
	શૂન્ય (OPENVR_FNTABLE_CALLTYPE *ResetZeroPose)(ETrackingUniverseOrigin eTrackingUniverseOrigin);
};

સંરચના VR_IVRChaperoneSetup_FnTable
{
	bool (OPENVR_FNTABLE_CALLTYPE *CommitWorkingCopy)(EChaperoneConfigFile configFile);
	શૂન્ય (OPENVR_FNTABLE_CALLTYPE *RevertWorkingCopy)();
	bool (OPENVR_FNTABLE_CALLTYPE *GetWorkingPlayAreaSize)(દશાંશ * pSizeX, દશાંશ * pSizeZ);
	bool (OPENVR_FNTABLE_CALLTYPE *GetWorkingPlayAreaRect)(સંરચના HmdQuad_t * rect);
	bool (OPENVR_FNTABLE_CALLTYPE *GetWorkingCollisionBoundsInfo)(સંરચના HmdQuad_t * pQuadsBuffer, uint32_t * pun_Quads_ગણતરી);
	bool (OPENVR_FNTABLE_CALLTYPE *GetLiveCollisionBoundsInfo)(સંરચના HmdQuad_t * pQuadsBuffer, uint32_t * pun_Quads_ગણતરી);
	bool (OPENVR_FNTABLE_CALLTYPE *GetWorkingSeatedZeroPoseToRawTrackingPose)(સંરચના HmdMatrix34_t * pmatSeatedZeroPoseToRawTrackingPose);
	bool (OPENVR_FNTABLE_CALLTYPE *GetWorkingStandingZeroPoseToRawTrackingPose)(સંરચના HmdMatrix34_t * pmatStandingZeroPoseToRawTrackingPose);
	શૂન્ય (OPENVR_FNTABLE_CALLTYPE *SetWorkingPlayAreaSize)(દશાંશ sizeX, દશાંશ sizeZ);
	શૂન્ય (OPENVR_FNTABLE_CALLTYPE *SetWorkingCollisionBoundsInfo)(સંરચના HmdQuad_t * pQuadsBuffer, uint32_t un_Quads_ગણતરી);
	શૂન્ય (OPENVR_FNTABLE_CALLTYPE *SetWorkingPerimeter)(સંરચના HmdVector2_t * pPointBuffer, uint32_t un_Point_ગણતરી);
	શૂન્ય (OPENVR_FNTABLE_CALLTYPE *SetWorkingSeatedZeroPoseToRawTrackingPose)(સંરચના HmdMatrix34_t * pMatSeatedZeroPoseToRawTrackingPose);
	શૂન્ય (OPENVR_FNTABLE_CALLTYPE *SetWorkingStandingZeroPoseToRawTrackingPose)(સંરચના HmdMatrix34_t * pMatStandingZeroPoseToRawTrackingPose);
	શૂન્ય (OPENVR_FNTABLE_CALLTYPE *ReloadFromDisk)(EChaperoneConfigFile configFile);
	bool (OPENVR_FNTABLE_CALLTYPE *GetLiveSeatedZeroPoseToRawTrackingPose)(સંરચના HmdMatrix34_t * pmatSeatedZeroPoseToRawTrackingPose);
	bool (OPENVR_FNTABLE_CALLTYPE *ExportLiveToBuffer)(અક્ષર * pBuffer, uint32_t * pnBufferLength);
	bool (OPENVR_FNTABLE_CALLTYPE *ImportFromBufferToWorking)(અક્ષર * pBuffer, uint32_t nImportFlags);
	શૂન્ય (OPENVR_FNTABLE_CALLTYPE *ShowWorkingSetPreview)();
	શૂન્ય (OPENVR_FNTABLE_CALLTYPE *HideWorkingSetPreview)();
	શૂન્ય (OPENVR_FNTABLE_CALLTYPE *RoomSetupStarting)();
};

સંરચના VR_IVRCompositor_FnTable
{
	શૂન્ય (OPENVR_FNTABLE_CALLTYPE *SetTrackingSpace)(ETrackingUniverseOrigin eOrigin);
	ETrackingUniverseOrigin (OPENVR_FNTABLE_CALLTYPE *GetTrackingSpace)();
	EVRCompositorError (OPENVR_FNTABLE_CALLTYPE *WaitGetPoses)(સંરચના TrackedDevicePose_t * pRenderPoseArray, uint32_t un_Render_Pose_Array_ગણતરી, સંરચના TrackedDevicePose_t * pGamePoseArray, uint32_t un_Game_Pose_Array_ગણતરી);
	EVRCompositorError (OPENVR_FNTABLE_CALLTYPE *GetLastPoses)(સંરચના TrackedDevicePose_t * pRenderPoseArray, uint32_t un_Render_Pose_Array_ગણતરી, સંરચના TrackedDevicePose_t * pGamePoseArray, uint32_t un_Game_Pose_Array_ગણતરી);
	EVRCompositorError (OPENVR_FNTABLE_CALLTYPE *GetLastPoseForTrackedDeviceIndex)(TrackedDeviceIndex_t unDeviceIndex, સંરચના TrackedDevicePose_t * pOutputPose, સંરચના TrackedDevicePose_t * pOutputGamePose);
	EVRCompositorError (OPENVR_FNTABLE_CALLTYPE *Submit)(EVREye eEye, સંરચના Texture_t * pTexture, સંરચના VRTextureBounds_t * pBounds, EVRSubmitFlags nSubmitFlags);
	શૂન્ય (OPENVR_FNTABLE_CALLTYPE *ClearLastSubmittedFrame)();
	શૂન્ય (OPENVR_FNTABLE_CALLTYPE *PostPresentHandoff)();
	bool (OPENVR_FNTABLE_CALLTYPE *GetFrameTiming)(સંરચના Compositor_FrameTiming * pTiming, uint32_t unFramesAgo);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetFrameTimings)(સંરચના Compositor_FrameTiming * pTiming, uint32_t nFrames);
	દશાંશ (OPENVR_FNTABLE_CALLTYPE *GetFrameTimeRemaining)();
	શૂન્ય (OPENVR_FNTABLE_CALLTYPE *GetCumulativeStats)(સંરચના Compositor_CumulativeStats * pStats, uint32_t nStatsSizeInBytes);
	શૂન્ય (OPENVR_FNTABLE_CALLTYPE *FadeToColor)(દશાંશ fSeconds, દશાંશ fRed, દશાંશ fGreen, દશાંશ fBlue, દશાંશ fAlpha, bool bBackground);
	સંરચના HmdColor_t (OPENVR_FNTABLE_CALLTYPE *GetCurrentFadeColor)(bool bBackground);
	શૂન્ય (OPENVR_FNTABLE_CALLTYPE *FadeGrid)(દશાંશ fSeconds, bool bFadeGridIn);
	દશાંશ (OPENVR_FNTABLE_CALLTYPE *GetCurrentGridAlpha)();
	EVRCompositorError (OPENVR_FNTABLE_CALLTYPE *SetSkyboxOverride)(સંરચના Texture_t * pTextures, uint32_t un_Texture_ગણતરી);
	શૂન્ય (OPENVR_FNTABLE_CALLTYPE *ClearSkyboxOverride)();
	શૂન્ય (OPENVR_FNTABLE_CALLTYPE *CompositorBringToFront)();
	શૂન્ય (OPENVR_FNTABLE_CALLTYPE *CompositorGoToBack)();
	શૂન્ય (OPENVR_FNTABLE_CALLTYPE *CompositorQuit)();
	bool (OPENVR_FNTABLE_CALLTYPE *IsFullscreen)();
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetCurrentSceneFocusProcess)();
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetLastFrameRenderer)();
	bool (OPENVR_FNTABLE_CALLTYPE *CanRenderScene)();
	શૂન્ય (OPENVR_FNTABLE_CALLTYPE *ShowMirrorWindow)();
	શૂન્ય (OPENVR_FNTABLE_CALLTYPE *HideMirrorWindow)();
	bool (OPENVR_FNTABLE_CALLTYPE *IsMirrorWindowVisible)();
	શૂન્ય (OPENVR_FNTABLE_CALLTYPE *CompositorDumpImages)();
	bool (OPENVR_FNTABLE_CALLTYPE *Should_App_Render_With_નીચલું_Resources)();
	શૂન્ય (OPENVR_FNTABLE_CALLTYPE *ForceInterleavedReprojectionOn)(bool bOverride);
	શૂન્ય (OPENVR_FNTABLE_CALLTYPE *ForceReconnectProcess)();
	શૂન્ય (OPENVR_FNTABLE_CALLTYPE *SuspendRendering)(bool bSuspend);
	EVRCompositorError (OPENVR_FNTABLE_CALLTYPE *GetMirrorTextureD3D11)(EVREye eEye, શૂન્ય * pD3D11DeviceOrResource, શૂન્ય ** ppD3D11ShaderResourceView);
	શૂન્ય (OPENVR_FNTABLE_CALLTYPE *ReleaseMirrorTextureD3D11)(શૂન્ય * pD3D11ShaderResourceView);
	EVRCompositorError (OPENVR_FNTABLE_CALLTYPE *GetMirrorTextureGL)(EVREye eEye, glUInt_t * pglTextureId, glSharedTextureHandle_t * pglSharedTextureHandle);
	bool (OPENVR_FNTABLE_CALLTYPE *ReleaseSharedGLTexture)(glUInt_t glTextureId, glSharedTextureHandle_t glSharedTextureHandle);
	શૂન્ય (OPENVR_FNTABLE_CALLTYPE *LockGLSharedTextureForAccess)(glSharedTextureHandle_t glSharedTextureHandle);
	શૂન્ય (OPENVR_FNTABLE_CALLTYPE *UnlockGLSharedTextureForAccess)(glSharedTextureHandle_t glSharedTextureHandle);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetVulkanInstanceExtensionsRequired)(અક્ષર * pch_કિંમત, uint32_t unBufferSize);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetVulkanDeviceExtensionsRequired)(સંરચના VkPhysicalDevice_T * pPhysicalDevice, અક્ષર * pch_કિંમત, uint32_t unBufferSize);
	શૂન્ય (OPENVR_FNTABLE_CALLTYPE *SetExplicitTimingMode)(EVRCompositorTimingMode eTimingMode);
	EVRCompositorError (OPENVR_FNTABLE_CALLTYPE *SubmitExplicitTimingData)();
	bool (OPENVR_FNTABLE_CALLTYPE *IsMotionSmoothingEnabled)();
	bool (OPENVR_FNTABLE_CALLTYPE *IsMotionSmoothingSupported)();
	bool (OPENVR_FNTABLE_CALLTYPE *IsCurrentSceneFocusAppLoading)();
	EVRCompositorError (OPENVR_FNTABLE_CALLTYPE *SetStageOverride_Async)(અક્ષર * pchRenderModelPath, સંરચના HmdMatrix34_t * pTransform, સંરચના Compositor_StageRenderSettings * pRenderSettings, uint32_t nSizeOfRenderSettings);
	શૂન્ય (OPENVR_FNTABLE_CALLTYPE *ClearStageOverride)();
	bool (OPENVR_FNTABLE_CALLTYPE *GetCompositorBenchmarkResults)(સંરચના Compositor_BenchmarkResults * pBenchmarkResults, uint32_t nSizeOfBenchmarkResults);
	EVRCompositorError (OPENVR_FNTABLE_CALLTYPE *GetLastPosePredictionIDs)(uint32_t * pRenderPosePredictionID, uint32_t * pGamePosePredictionID);
	EVRCompositorError (OPENVR_FNTABLE_CALLTYPE *GetPosesForFrame)(uint32_t unPosePredictionID, સંરચના TrackedDevicePose_t * pPoseArray, uint32_t un_Pose_Array_ગણતરી);
};

સંરચના VR_IVROverlay_FnTable
{
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *FindOverlay)(અક્ષર * pch_Overlay_ચાવી, VROverlayHandle_t * pOverlayHandle);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *CreateOverlay)(અક્ષર * pch_Overlay_ચાવી, અક્ષર * pchOverlayName, VROverlayHandle_t * pOverlayHandle);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *DestroyOverlay)(VROverlayHandle_t ulOverlayHandle);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *Get_Overlay_ચાવી)(VROverlayHandle_t ulOverlayHandle, અક્ષર * pch_કિંમત, uint32_t unBufferSize, EVROverlayError * pError);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetOverlayName)(VROverlayHandle_t ulOverlayHandle, અક્ષર * pch_કિંમત, uint32_t unBufferSize, EVROverlayError * pError);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *SetOverlayName)(VROverlayHandle_t ulOverlayHandle, અક્ષર * pchName);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayImageData)(VROverlayHandle_t ulOverlayHandle, શૂન્ય * pvBuffer, uint32_t unBufferSize, uint32_t * punWidth, uint32_t * punHeight);
	અક્ષર * (OPENVR_FNTABLE_CALLTYPE *GetOverlayErrorNameFromEnum)(EVROverlayError error);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *SetOverlayRenderingPid)(VROverlayHandle_t ulOverlayHandle, uint32_t unPID);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetOverlayRenderingPid)(VROverlayHandle_t ulOverlayHandle);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *SetOverlayFlag)(VROverlayHandle_t ulOverlayHandle, VROverlayFlags eOverlayFlag, bool bEnabled);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayFlag)(VROverlayHandle_t ulOverlayHandle, VROverlayFlags eOverlayFlag, bool * pbEnabled);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayFlags)(VROverlayHandle_t ulOverlayHandle, uint32_t * pFlags);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *SetOverlayColor)(VROverlayHandle_t ulOverlayHandle, દશાંશ fRed, દશાંશ fGreen, દશાંશ fBlue);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayColor)(VROverlayHandle_t ulOverlayHandle, દશાંશ * pfRed, દશાંશ * pfGreen, દશાંશ * pfBlue);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *SetOverlayAlpha)(VROverlayHandle_t ulOverlayHandle, દશાંશ fAlpha);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayAlpha)(VROverlayHandle_t ulOverlayHandle, દશાંશ * pfAlpha);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *SetOverlayTexelAspect)(VROverlayHandle_t ulOverlayHandle, દશાંશ fTexelAspect);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayTexelAspect)(VROverlayHandle_t ulOverlayHandle, દશાંશ * pfTexelAspect);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *SetOverlaySortOrder)(VROverlayHandle_t ulOverlayHandle, uint32_t unSortOrder);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlaySortOrder)(VROverlayHandle_t ulOverlayHandle, uint32_t * punSortOrder);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *SetOverlayWidthInMeters)(VROverlayHandle_t ulOverlayHandle, દશાંશ fWidthInMeters);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayWidthInMeters)(VROverlayHandle_t ulOverlayHandle, દશાંશ * pfWidthInMeters);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *SetOverlayCurvature)(VROverlayHandle_t ulOverlayHandle, દશાંશ fCurvature);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayCurvature)(VROverlayHandle_t ulOverlayHandle, દશાંશ * pfCurvature);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *SetOverlayPreCurvePitch)(VROverlayHandle_t ulOverlayHandle, દશાંશ fRadians);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayPreCurvePitch)(VROverlayHandle_t ulOverlayHandle, દશાંશ * pfRadians);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *SetOverlayTextureColorSpace)(VROverlayHandle_t ulOverlayHandle, EColorSpace eTextureColorSpace);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayTextureColorSpace)(VROverlayHandle_t ulOverlayHandle, EColorSpace * peTextureColorSpace);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *SetOverlayTextureBounds)(VROverlayHandle_t ulOverlayHandle, સંરચના VRTextureBounds_t * pOverlayTextureBounds);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayTextureBounds)(VROverlayHandle_t ulOverlayHandle, સંરચના VRTextureBounds_t * pOverlayTextureBounds);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayTransformType)(VROverlayHandle_t ulOverlayHandle, VROverlayTransformType * peTransformType);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *SetOverlayTransformAbsolute)(VROverlayHandle_t ulOverlayHandle, ETrackingUniverseOrigin eTrackingOrigin, સંરચના HmdMatrix34_t * pmatTrackingOriginToOverlayTransform);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayTransformAbsolute)(VROverlayHandle_t ulOverlayHandle, ETrackingUniverseOrigin * peTrackingOrigin, સંરચના HmdMatrix34_t * pmatTrackingOriginToOverlayTransform);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *SetOverlayTransformTrackedDeviceRelative)(VROverlayHandle_t ulOverlayHandle, TrackedDeviceIndex_t unTrackedDevice, સંરચના HmdMatrix34_t * pmatTrackedDeviceToOverlayTransform);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayTransformTrackedDeviceRelative)(VROverlayHandle_t ulOverlayHandle, TrackedDeviceIndex_t * punTrackedDevice, સંરચના HmdMatrix34_t * pmatTrackedDeviceToOverlayTransform);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *SetOverlayTransformTrackedDeviceComponent)(VROverlayHandle_t ulOverlayHandle, TrackedDeviceIndex_t unDeviceIndex, અક્ષર * pchComponentName);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayTransformTrackedDeviceComponent)(VROverlayHandle_t ulOverlayHandle, TrackedDeviceIndex_t * punDeviceIndex, અક્ષર * pchComponentName, uint32_t unComponentNameSize);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayTransformOverlayRelative)(VROverlayHandle_t ulOverlayHandle, VROverlayHandle_t * ulOverlayHandleParent, સંરચના HmdMatrix34_t * pmatParentOverlayToOverlayTransform);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *SetOverlayTransformOverlayRelative)(VROverlayHandle_t ulOverlayHandle, VROverlayHandle_t ulOverlayHandleParent, સંરચના HmdMatrix34_t * pmatParentOverlayToOverlayTransform);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *SetOverlayTransformCursor)(VROverlayHandle_t ulCursorOverlayHandle, સંરચના HmdVector2_t * pvHotspot);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayTransformCursor)(VROverlayHandle_t ulOverlayHandle, સંરચના HmdVector2_t * pvHotspot);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *SetOverlayTransformProjection)(VROverlayHandle_t ulOverlayHandle, ETrackingUniverseOrigin eTrackingOrigin, સંરચના HmdMatrix34_t * pmatTrackingOriginToOverlayTransform, સંરચના VROverlayProjection_t * pProjection, EVREye eEye);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *ShowOverlay)(VROverlayHandle_t ulOverlayHandle);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *HideOverlay)(VROverlayHandle_t ulOverlayHandle);
	bool (OPENVR_FNTABLE_CALLTYPE *IsOverlayVisible)(VROverlayHandle_t ulOverlayHandle);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetTransformForOverlayCoordinates)(VROverlayHandle_t ulOverlayHandle, ETrackingUniverseOrigin eTrackingOrigin, સંરચના HmdVector2_t coordinatesInOverlay, સંરચના HmdMatrix34_t * pmatTransform);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *WaitFrameSync)(uint32_t nTimeoutMs);
	bool (OPENVR_FNTABLE_CALLTYPE *PollNextOverlayEvent)(VROverlayHandle_t ulOverlayHandle, સંરચના VREvent_t * pEvent, uint32_t uncbVREvent);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *Get_Overlay_આગત_Method)(VROverlayHandle_t ulOverlayHandle, VROverlay_આગત_Method * pe_આગત_Method);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *Set_Overlay_આગત_Method)(VROverlayHandle_t ulOverlayHandle, VROverlay_આગત_Method e_આગત_Method);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayMouseScale)(VROverlayHandle_t ulOverlayHandle, સંરચના HmdVector2_t * pvecMouseScale);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *SetOverlayMouseScale)(VROverlayHandle_t ulOverlayHandle, સંરચના HmdVector2_t * pvecMouseScale);
	bool (OPENVR_FNTABLE_CALLTYPE *ComputeOverlayIntersection)(VROverlayHandle_t ulOverlayHandle, સંરચના VROverlayIntersectionParams_t * pParams, સંરચના VROverlayIntersectionResults_t * pResults);
	bool (OPENVR_FNTABLE_CALLTYPE *IsHoverTargetOverlay)(VROverlayHandle_t ulOverlayHandle);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *SetOverlayIntersectionMask)(VROverlayHandle_t ulOverlayHandle, સંરચના VROverlayIntersectionMaskPrimitive_t * pMaskPrimitives, uint32_t un_અંક_Mask_Primitives, uint32_t unPrimitiveSize);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *TriggerLaserMouseHapticVibration)(VROverlayHandle_t ulOverlayHandle, દશાંશ fDurationSeconds, દશાંશ fFrequency, દશાંશ fAmplitude);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *SetOverlayCursor)(VROverlayHandle_t ulOverlayHandle, VROverlayHandle_t ulCursorHandle);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *SetOverlayCursorPositionOverride)(VROverlayHandle_t ulOverlayHandle, સંરચના HmdVector2_t * pvCursor);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *ClearOverlayCursorPositionOverride)(VROverlayHandle_t ulOverlayHandle);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *SetOverlayTexture)(VROverlayHandle_t ulOverlayHandle, સંરચના Texture_t * pTexture);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *ClearOverlayTexture)(VROverlayHandle_t ulOverlayHandle);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *SetOverlayRaw)(VROverlayHandle_t ulOverlayHandle, શૂન્ય * pvBuffer, uint32_t unWidth, uint32_t unHeight, uint32_t unBytesPerPixel);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *SetOverlayFromFile)(VROverlayHandle_t ulOverlayHandle, અક્ષર * pchFilePath);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayTexture)(VROverlayHandle_t ulOverlayHandle, શૂન્ય ** pNativeTextureHandle, શૂન્ય * pNativeTextureRef, uint32_t * pWidth, uint32_t * pHeight, uint32_t * pNativeFormat, ETextureType * pAPIType, EColorSpace * pColorSpace, સંરચના VRTextureBounds_t * pTextureBounds);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *ReleaseNativeOverlayHandle)(VROverlayHandle_t ulOverlayHandle, શૂન્ય * pNativeTextureHandle);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayTextureSize)(VROverlayHandle_t ulOverlayHandle, uint32_t * pWidth, uint32_t * pHeight);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *CreateDashboardOverlay)(અક્ષર * pch_Overlay_ચાવી, અક્ષર * pchOverlayFriendlyName, VROverlayHandle_t * pMainHandle, VROverlayHandle_t * pThumbnailHandle);
	bool (OPENVR_FNTABLE_CALLTYPE *IsDashboardVisible)();
	bool (OPENVR_FNTABLE_CALLTYPE *IsActiveDashboardOverlay)(VROverlayHandle_t ulOverlayHandle);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *SetDashboardOverlaySceneProcess)(VROverlayHandle_t ulOverlayHandle, uint32_t unProcessId);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetDashboardOverlaySceneProcess)(VROverlayHandle_t ulOverlayHandle, uint32_t * punProcessId);
	શૂન્ય (OPENVR_FNTABLE_CALLTYPE *ShowDashboard)(અક્ષર * pchOverlayToShow);
	TrackedDeviceIndex_t (OPENVR_FNTABLE_CALLTYPE *GetPrimaryDashboardDevice)();
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *ShowKeyboard)(EGamepad_Text_આગત_Mode e_આગત_Mode, EGamepad_Text_આગત_લીટી_Mode e_લીટી_આગત_Mode, uint32_t unFlags, અક્ષર * pchDescription, uint32_t unCharMax, અક્ષર * pchExistingText, uint64_t u_User_કિંમત);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *ShowKeyboardForOverlay)(VROverlayHandle_t ulOverlayHandle, EGamepad_Text_આગત_Mode e_આગત_Mode, EGamepad_Text_આગત_લીટી_Mode e_લીટી_આગત_Mode, uint32_t unFlags, અક્ષર * pchDescription, uint32_t unCharMax, અક્ષર * pchExistingText, uint64_t u_User_કિંમત);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetKeyboardText)(અક્ષર * pchText, uint32_t cchText);
	શૂન્ય (OPENVR_FNTABLE_CALLTYPE *HideKeyboard)();
	શૂન્ય (OPENVR_FNTABLE_CALLTYPE *SetKeyboardTransformAbsolute)(ETrackingUniverseOrigin eTrackingOrigin, સંરચના HmdMatrix34_t * pmatTrackingOriginToKeyboardTransform);
	શૂન્ય (OPENVR_FNTABLE_CALLTYPE *SetKeyboardPositionForOverlay)(VROverlayHandle_t ulOverlayHandle, સંરચના HmdRect2_t avoidRect);
	VRMessageOverlayResponse (OPENVR_FNTABLE_CALLTYPE *ShowMessageOverlay)(અક્ષર * pchText, અક્ષર * pchCaption, અક્ષર * pchButton0Text, અક્ષર * pchButton1Text, અક્ષર * pchButton2Text, અક્ષર * pchButton3Text);
	શૂન્ય (OPENVR_FNTABLE_CALLTYPE *CloseMessageOverlay)();
};

સંરચના VR_IVROverlayView_FnTable
{
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *AcquireOverlayView)(VROverlayHandle_t ulOverlayHandle, સંરચના VRNativeDevice_t * pNativeDevice, સંરચના VROverlayView_t * pOverlayView, uint32_t unOverlayViewSize);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *ReleaseOverlayView)(સંરચના VROverlayView_t * pOverlayView);
	શૂન્ય (OPENVR_FNTABLE_CALLTYPE *PostOverlayEvent)(VROverlayHandle_t ulOverlayHandle, સંરચના VREvent_t * pvrEvent);
	bool (OPENVR_FNTABLE_CALLTYPE *IsViewingPermitted)(VROverlayHandle_t ulOverlayHandle);
};

સંરચના VR_IVRHeadsetView_FnTable
{
	શૂન્ય (OPENVR_FNTABLE_CALLTYPE *SetHeadsetViewSize)(uint32_t nWidth, uint32_t nHeight);
	શૂન્ય (OPENVR_FNTABLE_CALLTYPE *GetHeadsetViewSize)(uint32_t * pnWidth, uint32_t * pnHeight);
	શૂન્ય (OPENVR_FNTABLE_CALLTYPE *SetHeadsetViewMode)(HeadsetViewMode_t eHeadsetViewMode);
	HeadsetViewMode_t (OPENVR_FNTABLE_CALLTYPE *GetHeadsetViewMode)();
	શૂન્ય (OPENVR_FNTABLE_CALLTYPE *SetHeadsetViewCropped)(bool bCropped);
	bool (OPENVR_FNTABLE_CALLTYPE *GetHeadsetViewCropped)();
	દશાંશ (OPENVR_FNTABLE_CALLTYPE *GetHeadsetViewAspectRatio)();
	શૂન્ય (OPENVR_FNTABLE_CALLTYPE *SetHeadsetViewBlendRange)(દશાંશ flStartPct, દશાંશ flEndPct);
	શૂન્ય (OPENVR_FNTABLE_CALLTYPE *GetHeadsetViewBlendRange)(દશાંશ * pStartPct, દશાંશ * pEndPct);
};

સંરચના VR_IVRRenderModels_FnTable
{
	EVRRenderModelError (OPENVR_FNTABLE_CALLTYPE *LoadRenderModel_Async)(અક્ષર * pchRenderModelName, સંરચના RenderModel_t ** ppRenderModel);
	શૂન્ય (OPENVR_FNTABLE_CALLTYPE *FreeRenderModel)(સંરચના RenderModel_t * pRenderModel);
	EVRRenderModelError (OPENVR_FNTABLE_CALLTYPE *LoadTexture_Async)(TextureID_t textureId, સંરચના RenderModel_TextureMap_t ** ppTexture);
	શૂન્ય (OPENVR_FNTABLE_CALLTYPE *FreeTexture)(સંરચના RenderModel_TextureMap_t * pTexture);
	EVRRenderModelError (OPENVR_FNTABLE_CALLTYPE *LoadTextureD3D11_Async)(TextureID_t textureId, શૂન્ય * pD3D11Device, શૂન્ય ** ppD3D11Texture2D);
	EVRRenderModelError (OPENVR_FNTABLE_CALLTYPE *LoadIntoTextureD3D11_Async)(TextureID_t textureId, શૂન્ય * pDstTexture);
	શૂન્ય (OPENVR_FNTABLE_CALLTYPE *FreeTextureD3D11)(શૂન્ય * pD3D11Texture2D);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetRenderModelName)(uint32_t unRenderModelIndex, અક્ષર * pchRenderModelName, uint32_t unRenderModelNameLen);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *Get_Render_Model_ગણતરી)();
	uint32_t (OPENVR_FNTABLE_CALLTYPE *Get_Component_ગણતરી)(અક્ષર * pchRenderModelName);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetComponentName)(અક્ષર * pchRenderModelName, uint32_t unComponentIndex, અક્ષર * pchComponentName, uint32_t unComponentNameLen);
	uint64_t (OPENVR_FNTABLE_CALLTYPE *GetComponentButtonMask)(અક્ષર * pchRenderModelName, અક્ષર * pchComponentName);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetComponentRenderModelName)(અક્ષર * pchRenderModelName, અક્ષર * pchComponentName, અક્ષર * pchComponentRenderModelName, uint32_t unComponentRenderModelNameLen);
	bool (OPENVR_FNTABLE_CALLTYPE *GetComponentStateForDevicePath)(અક્ષર * pchRenderModelName, અક્ષર * pchComponentName, VRInput_કિંમત_Handle_t devicePath, RenderModel_ControllerMode_State_t * pState, RenderModel_ComponentState_t * pComponentState);
	bool (OPENVR_FNTABLE_CALLTYPE *GetComponentState)(અક્ષર * pchRenderModelName, અક્ષર * pchComponentName, VRControllerState_t * pControllerState, સંરચના RenderModel_ControllerMode_State_t * pState, સંરચના RenderModel_ComponentState_t * pComponentState);
	bool (OPENVR_FNTABLE_CALLTYPE *RenderModelHasComponent)(અક્ષર * pchRenderModelName, અક્ષર * pchComponentName);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetRenderModelThumbnailURL)(અક્ષર * pchRenderModelName, અક્ષર * pchThumbnailURL, uint32_t unThumbnailURLLen, EVRRenderModelError * peError);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetRenderModelOriginalPath)(અક્ષર * pchRenderModelName, અક્ષર * pchOriginalPath, uint32_t unOriginalPathLen, EVRRenderModelError * peError);
	અક્ષર * (OPENVR_FNTABLE_CALLTYPE *GetRenderModelErrorNameFromEnum)(EVRRenderModelError error);
};

સંરચના VR_IVRNotifications_FnTable
{
	EVRNotificationError (OPENVR_FNTABLE_CALLTYPE *CreateNotification)(VROverlayHandle_t ulOverlayHandle, uint64_t ul_User_કિંમત, EVRNotificationType type, અક્ષર * pchText, EVRNotificationStyle style, સંરચના NotificationBitmap_t * pImage, VRNotificationId * pNotificationId);
	EVRNotificationError (OPENVR_FNTABLE_CALLTYPE *RemoveNotification)(VRNotificationId notificationId);
};

સંરચના VR_IVRSettings_FnTable
{
	અક્ષર * (OPENVR_FNTABLE_CALLTYPE *GetSettingsErrorNameFromEnum)(EVRSettingsError eError);
	શૂન્ય (OPENVR_FNTABLE_CALLTYPE *SetBool)(અક્ષર * pchSection, અક્ષર * pch_Settings_ચાવી, bool b_કિંમત, EVRSettingsError * peError);
	શૂન્ય (OPENVR_FNTABLE_CALLTYPE *SetInt32)(અક્ષર * pchSection, અક્ષર * pch_Settings_ચાવી, int32_t n_કિંમત, EVRSettingsError * peError);
	શૂન્ય (OPENVR_FNTABLE_CALLTYPE *SetFloat)(અક્ષર * pchSection, અક્ષર * pch_Settings_ચાવી, દશાંશ fl_કિંમત, EVRSettingsError * peError);
	શૂન્ય (OPENVR_FNTABLE_CALLTYPE *SetString)(અક્ષર * pchSection, અક્ષર * pch_Settings_ચાવી, અક્ષર * pch_કિંમત, EVRSettingsError * peError);
	bool (OPENVR_FNTABLE_CALLTYPE *GetBool)(અક્ષર * pchSection, અક્ષર * pch_Settings_ચાવી, EVRSettingsError * peError);
	int32_t (OPENVR_FNTABLE_CALLTYPE *GetInt32)(અક્ષર * pchSection, અક્ષર * pch_Settings_ચાવી, EVRSettingsError * peError);
	દશાંશ (OPENVR_FNTABLE_CALLTYPE *GetFloat)(અક્ષર * pchSection, અક્ષર * pch_Settings_ચાવી, EVRSettingsError * peError);
	શૂન્ય (OPENVR_FNTABLE_CALLTYPE *GetString)(અક્ષર * pchSection, અક્ષર * pch_Settings_ચાવી, અક્ષર * pch_કિંમત, uint32_t un_કિંમત_Len, EVRSettingsError * peError);
	શૂન્ય (OPENVR_FNTABLE_CALLTYPE *RemoveSection)(અક્ષર * pchSection, EVRSettingsError * peError);
	શૂન્ય (OPENVR_FNTABLE_CALLTYPE *Remove_ચાવી_In_Section)(અક્ષર * pchSection, અક્ષર * pch_Settings_ચાવી, EVRSettingsError * peError);
};

સંરચના VR_IVRScreenshots_FnTable
{
	EVRScreenshotError (OPENVR_FNTABLE_CALLTYPE *RequestScreenshot)(ScreenshotHandle_t * pOutScreenshotHandle, EVRScreenshotType type, અક્ષર * pchPreviewFilename, અક્ષર * pchVRFilename);
	EVRScreenshotError (OPENVR_FNTABLE_CALLTYPE *HookScreenshot)(EVRScreenshotType * pSupportedTypes, પૂર્ણાંક અંક_Types);
	EVRScreenshotType (OPENVR_FNTABLE_CALLTYPE *GetScreenshotPropertyType)(ScreenshotHandle_t screenshotHandle, EVRScreenshotError * pError);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetScreenshotPropertyFilename)(ScreenshotHandle_t screenshotHandle, EVRScreenshotPropertyFilenames filenameType, અક્ષર * pchFilename, uint32_t cchFilename, EVRScreenshotError * pError);
	EVRScreenshotError (OPENVR_FNTABLE_CALLTYPE *UpdateScreenshotProgress)(ScreenshotHandle_t screenshotHandle, દશાંશ flProgress);
	EVRScreenshotError (OPENVR_FNTABLE_CALLTYPE *TakeStereoScreenshot)(ScreenshotHandle_t * pOutScreenshotHandle, અક્ષર * pchPreviewFilename, અક્ષર * pchVRFilename);
	EVRScreenshotError (OPENVR_FNTABLE_CALLTYPE *SubmitScreenshot)(ScreenshotHandle_t screenshotHandle, EVRScreenshotType type, અક્ષર * pchSourcePreviewFilename, અક્ષર * pchSourceVRFilename);
};

સંરચના VR_IVRResources_FnTable
{
	uint32_t (OPENVR_FNTABLE_CALLTYPE *LoadSharedResource)(અક્ષર * pchResourceName, અક્ષર * pchBuffer, uint32_t unBufferLen);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetResourceFullPath)(અક્ષર * pchResourceName, અક્ષર * pchResourceTypeDirectory, અક્ષર * pchPathBuffer, uint32_t unBufferLen);
};

સંરચના VR_IVRDriverManager_FnTable
{
	uint32_t (OPENVR_FNTABLE_CALLTYPE *Get_Driver_ગણતરી)();
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetDriverName)(DriverId_t nDriver, અક્ષર * pch_કિંમત, uint32_t unBufferSize);
	DriverHandle_t (OPENVR_FNTABLE_CALLTYPE *GetDriverHandle)(અક્ષર * pchDriverName);
	bool (OPENVR_FNTABLE_CALLTYPE *IsEnabled)(DriverId_t nDriver);
};

સંરચના VR_IVRInput_FnTable
{
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *SetActionManifestPath)(અક્ષર * pchActionManifestPath);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetActionSetHandle)(અક્ષર * pchActionSetName, VRActionSetHandle_t * pHandle);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetActionHandle)(અક્ષર * pchActionName, VRActionHandle_t * pHandle);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *Get_આગત_Source_Handle)(અક્ષર * pch_આગત_Source_Path, VRInput_કિંમત_Handle_t * pHandle);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *UpdateActionState)(સંરચના VRActiveActionSet_t * pSets, uint32_t unSizeOfVRSelectedActionSet_t, uint32_t un_Set_ગણતરી);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetDigitalActionData)(VRActionHandle_t action, સંરચના આગત_Digital_Action_Data_t * pActionData, uint32_t unActionDataSize, VRInput_કિંમત_Handle_t ulRestrictToDevice);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetAnalogActionData)(VRActionHandle_t action, સંરચના આગત_Analog_Action_Data_t * pActionData, uint32_t unActionDataSize, VRInput_કિંમત_Handle_t ulRestrictToDevice);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetPoseActionDataRelativeToNow)(VRActionHandle_t action, ETrackingUniverseOrigin eOrigin, દશાંશ fPredictedSecondsFromNow, સંરચના આગત_Pose_Action_Data_t * pActionData, uint32_t unActionDataSize, VRInput_કિંમત_Handle_t ulRestrictToDevice);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetPoseActionDataForNextFrame)(VRActionHandle_t action, ETrackingUniverseOrigin eOrigin, સંરચના આગત_Pose_Action_Data_t * pActionData, uint32_t unActionDataSize, VRInput_કિંમત_Handle_t ulRestrictToDevice);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetSkeletalActionData)(VRActionHandle_t action, સંરચના આગત_Skeletal_Action_Data_t * pActionData, uint32_t unActionDataSize);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetDominantHand)(ETrackedControllerRole * peDominantHand);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *SetDominantHand)(ETrackedControllerRole eDominantHand);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *Get_Bone_ગણતરી)(VRActionHandle_t action, uint32_t * p_Bone_ગણતરી);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetBoneHierarchy)(VRActionHandle_t action, BoneIndex_t * pParentIndices, uint32_t un_Index_Aray_ગણતરી);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetBoneName)(VRActionHandle_t action, BoneIndex_t nBoneIndex, અક્ષર * pchBoneName, uint32_t unNameBufferSize);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetSkeletalReferenceTransforms)(VRActionHandle_t action, EVRSkeletalTransformSpace eTransformSpace, EVRSkeletalReferencePose eReferencePose, સંરચના VRBoneTransform_t * pTransformArray, uint32_t un_Transform_Array_ગણતરી);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetSkeletalTrackingLevel)(VRActionHandle_t action, EVRSkeletalTrackingLevel * pSkeletalTrackingLevel);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetSkeletalBoneData)(VRActionHandle_t action, EVRSkeletalTransformSpace eTransformSpace, EVRSkeletalMotionRange eMotionRange, સંરચના VRBoneTransform_t * pTransformArray, uint32_t un_Transform_Array_ગણતરી);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetSkeletalSummaryData)(VRActionHandle_t action, EVRSummaryType eSummaryType, સંરચના VRSkeletalSummaryData_t * pSkeletalSummaryData);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetSkeletalBoneDataCompressed)(VRActionHandle_t action, EVRSkeletalMotionRange eMotionRange, શૂન્ય * pvCompressedData, uint32_t unCompressedSize, uint32_t * punRequiredCompressedSize);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *DecompressSkeletalBoneData)(શૂન્ય * pvCompressedBuffer, uint32_t unCompressedBufferSize, EVRSkeletalTransformSpace eTransformSpace, સંરચના VRBoneTransform_t * pTransformArray, uint32_t un_Transform_Array_ગણતરી);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *TriggerHapticVibrationAction)(VRActionHandle_t action, દશાંશ fStartSecondsFromNow, દશાંશ fDurationSeconds, દશાંશ fFrequency, દશાંશ fAmplitude, VRInput_કિંમત_Handle_t ulRestrictToDevice);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetActionOrigins)(VRActionSetHandle_t actionSetHandle, VRActionHandle_t digitalActionHandle, VRInput_કિંમત_Handle_t * originsOut, uint32_t origin_Out_ગણતરી);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetOriginLocalizedName)(VRInput_કિંમત_Handle_t origin, અક્ષર * pchNameArray, uint32_t unNameArraySize, int32_t unStringSectionsToInclude);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetOriginTrackedDeviceInfo)(VRInput_કિંમત_Handle_t origin, સંરચના આગત_Origin_Info_t * pOriginInfo, uint32_t unOriginInfoSize);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetActionBindingInfo)(VRActionHandle_t action, સંરચના આગત_Binding_Info_t * pOriginInfo, uint32_t unBindingInfoSize, uint32_t un_Binding_Info_ગણતરી, uint32_t * pun_Returned_Binding_Info_ગણતરી);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *ShowActionOrigins)(VRActionSetHandle_t actionSetHandle, VRActionHandle_t ulActionHandle);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *ShowBindingsForActionSet)(સંરચના VRActiveActionSet_t * pSets, uint32_t unSizeOfVRSelectedActionSet_t, uint32_t un_Set_ગણતરી, VRInput_કિંમત_Handle_t originToHighlight);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetComponentStateForBinding)(અક્ષર * pchRenderModelName, અક્ષર * pchComponentName, સંરચના આગત_Binding_Info_t * pOriginInfo, uint32_t unBindingInfoSize, uint32_t un_Binding_Info_ગણતરી, RenderModel_ComponentState_t * pComponentState);
	bool (OPENVR_FNTABLE_CALLTYPE *Is_Using_Legacy_આગત)();
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *OpenBindingUI)(અક્ષર * pch_App_ચાવી, VRActionSetHandle_t ulActionSetHandle, VRInput_કિંમત_Handle_t ulDeviceHandle, bool bShowOnDesktop);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetBindingVariant)(VRInput_કિંમત_Handle_t ulDevicePath, અક્ષર * pchVariantArray, uint32_t unVariantArraySize);
};

સંરચના VR_IVRIOBuffer_FnTable
{
	EIOBufferError (OPENVR_FNTABLE_CALLTYPE *Open)(અક્ષર * pchPath, EIOBufferMode mode, uint32_t unElementSize, uint32_t unElements, IOBufferHandle_t * pulBuffer);
	EIOBufferError (OPENVR_FNTABLE_CALLTYPE *Close)(IOBufferHandle_t ulBuffer);
	EIOBufferError (OPENVR_FNTABLE_CALLTYPE *Read)(IOBufferHandle_t ulBuffer, શૂન્ય * pDst, uint32_t unBytes, uint32_t * punRead);
	EIOBufferError (OPENVR_FNTABLE_CALLTYPE *Write)(IOBufferHandle_t ulBuffer, શૂન્ય * pSrc, uint32_t unBytes);
	PropertyContainerHandle_t (OPENVR_FNTABLE_CALLTYPE *PropertyContainer)(IOBufferHandle_t ulBuffer);
	bool (OPENVR_FNTABLE_CALLTYPE *HasReaders)(IOBufferHandle_t ulBuffer);
};

સંરચના VR_IVRSpatialAnchors_FnTable
{
	EVRSpatialAnchorError (OPENVR_FNTABLE_CALLTYPE *CreateSpatialAnchorFromDescriptor)(અક્ષર * pchDescriptor, SpatialAnchorHandle_t * pHandleOut);
	EVRSpatialAnchorError (OPENVR_FNTABLE_CALLTYPE *CreateSpatialAnchorFromPose)(TrackedDeviceIndex_t unDeviceIndex, ETrackingUniverseOrigin eOrigin, સંરચના SpatialAnchorPose_t * pPose, SpatialAnchorHandle_t * pHandleOut);
	EVRSpatialAnchorError (OPENVR_FNTABLE_CALLTYPE *GetSpatialAnchorPose)(SpatialAnchorHandle_t unHandle, ETrackingUniverseOrigin eOrigin, સંરચના SpatialAnchorPose_t * pPoseOut);
	EVRSpatialAnchorError (OPENVR_FNTABLE_CALLTYPE *GetSpatialAnchorDescriptor)(SpatialAnchorHandle_t unHandle, અક્ષર * pchDescriptorOut, uint32_t * punDescriptorBufferLenInOut);
};

સંરચના VR_IVRDebug_FnTable
{
	EVRDebugError (OPENVR_FNTABLE_CALLTYPE *EmitVrProfilerEvent)(અક્ષર * pchMessage);
	EVRDebugError (OPENVR_FNTABLE_CALLTYPE *BeginVrProfilerEvent)(VrProfilerEventHandle_t * pHandleOut);
	EVRDebugError (OPENVR_FNTABLE_CALLTYPE *FinishVrProfilerEvent)(VrProfilerEventHandle_t hHandle, અક્ષર * pchMessage);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *DriverDebugRequest)(TrackedDeviceIndex_t unDeviceIndex, અક્ષર * pchRequest, અક્ષર * pchResponseBuffer, uint32_t unResponseBufferSize);
};

સંરચના VR_IVRProperties_FnTable
{
	ETrackedPropertyError (OPENVR_FNTABLE_CALLTYPE *ReadPropertyBatch)(PropertyContainerHandle_t ulContainerHandle, સંરચના PropertyRead_t * pBatch, uint32_t un_Batch_Entry_ગણતરી);
	ETrackedPropertyError (OPENVR_FNTABLE_CALLTYPE *WritePropertyBatch)(PropertyContainerHandle_t ulContainerHandle, સંરચના PropertyWrite_t * pBatch, uint32_t un_Batch_Entry_ગણતરી);
	અક્ષર * (OPENVR_FNTABLE_CALLTYPE *GetPropErrorNameFromEnum)(ETrackedPropertyError error);
	PropertyContainerHandle_t (OPENVR_FNTABLE_CALLTYPE *TrackedDeviceToPropertyContainer)(TrackedDeviceIndex_t nDevice);
};

સંરચના VR_IVRPaths_FnTable
{
	ETrackedPropertyError (OPENVR_FNTABLE_CALLTYPE *ReadPathBatch)(PropertyContainerHandle_t ul_મૂળ_Handle, સંરચના PathRead_t * pBatch, uint32_t un_Batch_Entry_ગણતરી);
	ETrackedPropertyError (OPENVR_FNTABLE_CALLTYPE *WritePathBatch)(PropertyContainerHandle_t ul_મૂળ_Handle, સંરચના PathWrite_t * pBatch, uint32_t un_Batch_Entry_ગણતરી);
	ETrackedPropertyError (OPENVR_FNTABLE_CALLTYPE *StringToHandle)(PathHandle_t * pHandle, અક્ષર * pchPath);
	ETrackedPropertyError (OPENVR_FNTABLE_CALLTYPE *HandleToString)(PathHandle_t pHandle, અક્ષર * pchBuffer, uint32_t unBufferSize, uint32_t * punBufferSizeUsed);
};

સંરચના VR_IVRBlockQueue_FnTable
{
	EBlockQueueError (OPENVR_FNTABLE_CALLTYPE *Create)(PropertyContainerHandle_t * pulQueueHandle, અક્ષર * pchPath, uint32_t unBlockDataSize, uint32_t unBlockHeaderSize, uint32_t un_Block_ગણતરી, uint32_t unFlags);
	EBlockQueueError (OPENVR_FNTABLE_CALLTYPE *Connect)(PropertyContainerHandle_t * pulQueueHandle, અક્ષર * pchPath);
	EBlockQueueError (OPENVR_FNTABLE_CALLTYPE *Destroy)(PropertyContainerHandle_t ulQueueHandle);
	EBlockQueueError (OPENVR_FNTABLE_CALLTYPE *AcquireWriteOnlyBlock)(PropertyContainerHandle_t ulQueueHandle, PropertyContainerHandle_t * pulBlockHandle, શૂન્ય ** ppvBuffer);
	EBlockQueueError (OPENVR_FNTABLE_CALLTYPE *ReleaseWriteOnlyBlock)(PropertyContainerHandle_t ulQueueHandle, PropertyContainerHandle_t ulBlockHandle);
	EBlockQueueError (OPENVR_FNTABLE_CALLTYPE *WaitAndAcquireReadOnlyBlock)(PropertyContainerHandle_t ulQueueHandle, PropertyContainerHandle_t * pulBlockHandle, શૂન્ય ** ppvBuffer, EBlockQueueReadType eReadType, uint32_t unTimeoutMs);
	EBlockQueueError (OPENVR_FNTABLE_CALLTYPE *AcquireReadOnlyBlock)(PropertyContainerHandle_t ulQueueHandle, PropertyContainerHandle_t * pulBlockHandle, શૂન્ય ** ppvBuffer, EBlockQueueReadType eReadType);
	EBlockQueueError (OPENVR_FNTABLE_CALLTYPE *ReleaseReadOnlyBlock)(PropertyContainerHandle_t ulQueueHandle, PropertyContainerHandle_t ulBlockHandle);
	EBlockQueueError (OPENVR_FNTABLE_CALLTYPE *QueueHasReader)(PropertyContainerHandle_t ulQueueHandle, bool * pbHasReaders);
};


#જો 0
// Global entry points
S_API intptr_t VR_InitInternal( EVRInitError *peError, EVRApplicationType eType );
S_API શૂન્ય VR_ShutdownInternal();
S_API bool VR_IsHmdPresent();
S_API intptr_t VR_GetGenericInterface( અચલ અક્ષર *pchInterfaceVersion, EVRInitError *peError );
S_API bool VR_IsRuntimeInstalled();
S_API અચલ અક્ષર * VR_Get_VRInit_Error_As_પ્રતીક( EVRInitError error );
S_API અચલ અક્ષર * VR_GetVRInitErrorAsEnglishDescription( EVRInitError error );
#endif

#endif // __OPENVR_API_FLAT_H__


