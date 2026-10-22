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
#यदि defined( _WIN32 ) || defined( __clang__ )
#pragma once
#endif

#ifdef __cplusplus
#define EXTERN_C बाह्य "C"
#अन्यथा
#define EXTERN_C
#endif

#यदि defined( _WIN32 )
#define OPENVR_FNTABLE_CALLTYPE __stdcall
#अन्यथा
#define OPENVR_FNTABLE_CALLTYPE 
#endif

// OPENVR API export macro
#यदि defined( _WIN32 ) && !defined( _X360 )
	#यदि defined( OPENVR_API_EXPORTS )
	#define S_API EXTERN_C __declspec( dllexport )
	#नोचेद्यदि defined( OPENVR_API_NODLL )
	#define S_API EXTERN_C
	#अन्यथा
	#define S_API बाह्य "C" __declspec( dllimport ) 
	#endif // OPENVR_API_EXPORTS
#नोचेद्यदि defined( __GNUC__ )
	#यदि defined( OPENVR_API_EXPORTS )
	#define S_API EXTERN_C __attribute__ ((visibility("default")))
	#अन्यथा
	#define S_API EXTERN_C
	#endif // OPENVR_API_EXPORTS
#अन्यथा // !WIN32
	#यदि defined( OPENVR_API_EXPORTS )
	#define S_API EXTERN_C
	#अन्यथा
	#define S_API EXTERN_C
	#endif // OPENVR_API_EXPORTS
#endif

#ifndef USE_SDL
#अन्तर्भाव <stdint.h>

#यदि defined( __WIN32 )
प्रकारनिर्देश वर्ण bool;
#अन्यथा
#अन्तर्भाव <stdbool.h>
#endif
#endif // USE_SDL

// OpenVR Constants

स्थिर ध्रुव unsigned long k_nDriverNone = 4294967295;
स्थिर ध्रुव unsigned long k_unMaxDriverDebugResponseSize = 32768;
स्थिर ध्रुव unsigned long k_unTrackedDeviceIndex_Hmd = 0;
स्थिर ध्रुव unsigned long k_un_Max_Tracked_Device_गिनती = 64;
स्थिर ध्रुव unsigned long k_unTrackedDeviceIndexOther = 4294967294;
स्थिर ध्रुव unsigned long k_unTrackedDeviceIndexInvalid = 4294967295;
स्थिर ध्रुव unsigned long long k_ulInvalidPropertyContainer = 0;
स्थिर ध्रुव unsigned long k_unInvalidPropertyTag = 0;
स्थिर ध्रुव unsigned long long k_ulInvalidDriverHandle = 0;
स्थिर ध्रुव unsigned long k_unFloatPropertyTag = 1;
स्थिर ध्रुव unsigned long k_unInt32PropertyTag = 2;
स्थिर ध्रुव unsigned long k_unUint64PropertyTag = 3;
स्थिर ध्रुव unsigned long k_unBoolPropertyTag = 4;
स्थिर ध्रुव unsigned long k_unStringPropertyTag = 5;
स्थिर ध्रुव unsigned long k_unErrorPropertyTag = 6;
स्थिर ध्रुव unsigned long k_unDoublePropertyTag = 7;
स्थिर ध्रुव unsigned long k_unHmdMatrix34PropertyTag = 20;
स्थिर ध्रुव unsigned long k_unHmdMatrix44PropertyTag = 21;
स्थिर ध्रुव unsigned long k_unHmdVector3PropertyTag = 22;
स्थिर ध्रुव unsigned long k_unHmdVector4PropertyTag = 23;
स्थिर ध्रुव unsigned long k_unHmdVector2PropertyTag = 24;
स्थिर ध्रुव unsigned long k_unHmdQuadPropertyTag = 25;
स्थिर ध्रुव unsigned long k_unHiddenAreaPropertyTag = 30;
स्थिर ध्रुव unsigned long k_unPathHandleInfoTag = 31;
स्थिर ध्रुव unsigned long k_unActionPropertyTag = 32;
स्थिर ध्रुव unsigned long k_un_निवेश_मूल्य_Property_Tag = 33;
स्थिर ध्रुव unsigned long k_unWildcardPropertyTag = 34;
स्थिर ध्रुव unsigned long k_unHapticVibrationPropertyTag = 35;
स्थिर ध्रुव unsigned long k_unSkeletonPropertyTag = 36;
स्थिर ध्रुव unsigned long k_unSpatialAnchorPosePropertyTag = 40;
स्थिर ध्रुव unsigned long k_unJsonPropertyTag = 41;
स्थिर ध्रुव unsigned long k_unActiveActionSetPropertyTag = 42;
स्थिर ध्रुव unsigned long k_unOpenVRInternalReserved_Start = 1000;
स्थिर ध्रुव unsigned long k_unOpenVRInternalReserved_End = 10000;
स्थिर ध्रुव unsigned long k_unMaxPropertyStringSize = 32768;
स्थिर ध्रुव unsigned long long k_ulInvalidActionHandle = 0;
स्थिर ध्रुव unsigned long long k_ulInvalidActionSetHandle = 0;
स्थिर ध्रुव unsigned long long k_ul_Invalid_निवेश_मूल्य_Handle = 0;
स्थिर ध्रुव unsigned long k_un_Controller_State_Axis_गिनती = 5;
स्थिर ध्रुव unsigned long long k_ulOverlayHandleInvalid = 0;
स्थिर ध्रुव unsigned long k_unMaxDistortionFunctionParameters = 8;
स्थिर ध्रुव unsigned long k_unScreenshotHandleInvalid = 0;
स्थिर ध्रुव वर्ण * IVRSystem_Version = "IVRSystem_022";
स्थिर ध्रुव वर्ण * IVRExtendedDisplay_Version = "IVRExtendedDisplay_001";
स्थिर ध्रुव वर्ण * IVRTrackedCamera_Version = "IVRTrackedCamera_006";
स्थिर ध्रुव unsigned long k_un_Max_Application_कुंजी_Length = 128;
स्थिर ध्रुव वर्ण * k_pch_MimeType_HomeApp = "vr/home";
स्थिर ध्रुव वर्ण * k_pch_MimeType_GameTheater = "vr/game_theater";
स्थिर ध्रुव वर्ण * IVRApplications_Version = "IVRApplications_007";
स्थिर ध्रुव वर्ण * IVRChaperone_Version = "IVRChaperone_004";
स्थिर ध्रुव वर्ण * IVRChaperoneSetup_Version = "IVRChaperoneSetup_006";
स्थिर ध्रुव वर्ण * IVRCompositor_Version = "IVRCompositor_027";
स्थिर ध्रुव unsigned long k_un_VROverlay_Max_कुंजी_Length = 128;
स्थिर ध्रुव unsigned long k_unVROverlayMaxNameLength = 128;
स्थिर ध्रुव unsigned long k_un_Max_Overlay_गिनती = 128;
स्थिर ध्रुव unsigned long k_un_Max_Overlay_Intersection_Mask_Primitives_गिनती = 32;
स्थिर ध्रुव वर्ण * IVROverlay_Version = "IVROverlay_026";
स्थिर ध्रुव वर्ण * IVROverlayView_Version = "IVROverlayView_003";
स्थिर ध्रुव unsigned long k_unHeadsetViewMaxWidth = 3840;
स्थिर ध्रुव unsigned long k_unHeadsetViewMaxHeight = 2160;
स्थिर ध्रुव वर्ण * k_pch_Headset_View_Overlay_कुंजी = "system.HeadsetView";
स्थिर ध्रुव वर्ण * IVRHeadsetView_Version = "IVRHeadsetView_001";
स्थिर ध्रुव वर्ण * k_pch_Controller_Component_GDC2015 = "gdc2015";
स्थिर ध्रुव वर्ण * k_pch_Controller_Component_Base = "base";
स्थिर ध्रुव वर्ण * k_pch_Controller_Component_Tip = "tip";
स्थिर ध्रुव वर्ण * k_pch_Controller_Component_OpenXR_Aim = "openxr_aim";
स्थिर ध्रुव वर्ण * k_pch_Controller_Component_HandGrip = "handgrip";
स्थिर ध्रुव वर्ण * k_pch_Controller_Component_OpenXR_Grip = "openxr_grip";
स्थिर ध्रुव वर्ण * k_pch_Controller_Component_OpenXR_HandModel = "openxr_handmodel";
स्थिर ध्रुव वर्ण * k_pch_Controller_Component_Status = "status";
स्थिर ध्रुव वर्ण * IVRRenderModels_Version = "IVRRenderModels_006";
स्थिर ध्रुव unsigned long k_unNotificationTextMaxSize = 256;
स्थिर ध्रुव वर्ण * IVRNotifications_Version = "IVRNotifications_002";
स्थिर ध्रुव unsigned long k_un_Max_Settings_कुंजी_Length = 128;
स्थिर ध्रुव वर्ण * IVRSettings_Version = "IVRSettings_003";
स्थिर ध्रुव वर्ण * k_pch_SteamVR_Section = "steamvr";
स्थिर ध्रुव वर्ण * k_pch_SteamVR_RequireHmd_String = "requireHmd";
स्थिर ध्रुव वर्ण * k_pch_Steam_VR_Forced_Driver_कुंजी_String = "forcedDriver";
स्थिर ध्रुव वर्ण * k_pch_Steam_VR_Forced_Hmd_कुंजी_String = "forcedHmd";
स्थिर ध्रुव वर्ण * k_pch_SteamVR_DisplayDebug_Bool = "displayDebug";
स्थिर ध्रुव वर्ण * k_pch_SteamVR_DebugProcessPipe_String = "debugProcessPipe";
स्थिर ध्रुव वर्ण * k_pch_SteamVR_DisplayDebugX_Int32 = "displayDebugX";
स्थिर ध्रुव वर्ण * k_pch_SteamVR_DisplayDebugY_Int32 = "displayDebugY";
स्थिर ध्रुव वर्ण * k_pch_SteamVR_SendSystemButtonToAllApps_Bool = "sendSystemButtonToAllApps";
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
स्थिर ध्रुव वर्ण * k_pch_SteamVR_ActivateMultipleDrivers_Bool = "activateMultipleDrivers";
स्थिर ध्रुव वर्ण * k_pch_SteamVR_UsingSpeakers_Bool = "usingSpeakers";
स्थिर ध्रुव वर्ण * k_pch_SteamVR_SpeakersForwardYawOffsetDegrees_Float = "speakersForwardYawOffsetDegrees";
स्थिर ध्रुव वर्ण * k_pch_SteamVR_BaseStationPowerManagement_Int32 = "basestationPowerManagement";
स्थिर ध्रुव वर्ण * k_pch_SteamVR_ShowBaseStationPowerManagementTip_Int32 = "ShowBaseStationPowerManagementTip";
स्थिर ध्रुव वर्ण * k_pch_SteamVR_NeverKillProcesses_Bool = "neverKillProcesses";
स्थिर ध्रुव वर्ण * k_pch_SteamVR_SupersampleScale_Float = "supersampleScale";
स्थिर ध्रुव वर्ण * k_pch_SteamVR_MaxRecommendedResolution_Int32 = "maxRecommendedResolution";
स्थिर ध्रुव वर्ण * k_pch_SteamVR_MotionSmoothing_Bool = "motionSmoothing";
स्थिर ध्रुव वर्ण * k_pch_SteamVR_MotionSmoothingOverride_Int32 = "motionSmoothingOverride";
स्थिर ध्रुव वर्ण * k_pch_SteamVR_FramesToThrottle_Int32 = "framesToThrottle";
स्थिर ध्रुव वर्ण * k_pch_SteamVR_AdditionalFramesToPredict_Int32 = "additionalFramesToPredict";
स्थिर ध्रुव वर्ण * k_pch_SteamVR_WorldScale_Float = "worldScale";
स्थिर ध्रुव वर्ण * k_pch_SteamVR_FovScale_Int32 = "fovScale";
स्थिर ध्रुव वर्ण * k_pch_SteamVR_DisableAsyncReprojection_Bool = "disableAsync";
स्थिर ध्रुव वर्ण * k_pch_SteamVR_ForceFadeOnBadTracking_Bool = "forceFadeOnBadTracking";
स्थिर ध्रुव वर्ण * k_pch_SteamVR_DefaultMirrorView_Int32 = "mirrorView";
स्थिर ध्रुव वर्ण * k_pch_SteamVR_ShowLegacyMirrorView_Bool = "showLegacyMirrorView";
स्थिर ध्रुव वर्ण * k_pch_SteamVR_MirrorViewVisibility_Bool = "showMirrorView";
स्थिर ध्रुव वर्ण * k_pch_SteamVR_MirrorViewDisplayMode_Int32 = "mirrorViewDisplayMode";
स्थिर ध्रुव वर्ण * k_pch_SteamVR_MirrorViewEye_Int32 = "mirrorViewEye";
स्थिर ध्रुव वर्ण * k_pch_SteamVR_MirrorViewGeometry_String = "mirrorViewGeometry";
स्थिर ध्रुव वर्ण * k_pch_SteamVR_MirrorViewGeometryMaximized_String = "mirrorViewGeometryMaximized";
स्थिर ध्रुव वर्ण * k_pch_SteamVR_PerfGraphVisibility_Bool = "showPerfGraph";
स्थिर ध्रुव वर्ण * k_pch_SteamVR_StartMonitorFromAppLaunch = "startMonitorFromAppLaunch";
स्थिर ध्रुव वर्ण * k_pch_SteamVR_StartCompositorFromAppLaunch_Bool = "startCompositorFromAppLaunch";
स्थिर ध्रुव वर्ण * k_pch_SteamVR_StartDashboardFromAppLaunch_Bool = "startDashboardFromAppLaunch";
स्थिर ध्रुव वर्ण * k_pch_SteamVR_StartOverlayAppsFromDashboard_Bool = "startOverlayAppsFromDashboard";
स्थिर ध्रुव वर्ण * k_pch_SteamVR_EnableHomeApp = "enableHomeApp";
स्थिर ध्रुव वर्ण * k_pch_SteamVR_CycleBackgroundImageTimeSec_Int32 = "CycleBackgroundImageTimeSec";
स्थिर ध्रुव वर्ण * k_pch_SteamVR_RetailDemo_Bool = "retailDemo";
स्थिर ध्रुव वर्ण * k_pch_SteamVR_IpdOffset_Float = "ipdOffset";
स्थिर ध्रुव वर्ण * k_pch_SteamVR_AllowSupersampleFiltering_Bool = "allowSupersampleFiltering";
स्थिर ध्रुव वर्ण * k_pch_SteamVR_SupersampleManualOverride_Bool = "supersampleManualOverride";
स्थिर ध्रुव वर्ण * k_pch_SteamVR_EnableLinuxVulkanAsync_Bool = "enableLinuxVulkanAsync";
स्थिर ध्रुव वर्ण * k_pch_SteamVR_AllowDisplayLockedMode_Bool = "allowDisplayLockedMode";
स्थिर ध्रुव वर्ण * k_pch_SteamVR_HaveStartedTutorialForNativeChaperoneDriver_Bool = "haveStartedTutorialForNativeChaperoneDriver";
स्थिर ध्रुव वर्ण * k_pch_SteamVR_ForceWindows32bitVRMonitor = "forceWindows32BitVRMonitor";
स्थिर ध्रुव वर्ण * k_pch_Steam_VR_Debug_निवेश_Binding = "debugInputBinding";
स्थिर ध्रुव वर्ण * k_pch_SteamVR_DoNotFadeToGrid = "doNotFadeToGrid";
स्थिर ध्रुव वर्ण * k_pch_SteamVR_RenderCameraMode = "renderCameraMode";
स्थिर ध्रुव वर्ण * k_pch_SteamVR_EnableSharedResourceJournaling = "enableSharedResourceJournaling";
स्थिर ध्रुव वर्ण * k_pch_SteamVR_EnableSafeMode = "enableSafeMode";
स्थिर ध्रुव वर्ण * k_pch_SteamVR_PreferredRefreshRate = "preferredRefreshRate";
स्थिर ध्रुव वर्ण * k_pch_SteamVR_LastVersionNotice = "lastVersionNotice";
स्थिर ध्रुव वर्ण * k_pch_SteamVR_LastVersionNoticeDate = "lastVersionNoticeDate";
स्थिर ध्रुव वर्ण * k_pch_SteamVR_HmdDisplayColorGainR_Float = "hmdDisplayColorGainR";
स्थिर ध्रुव वर्ण * k_pch_SteamVR_HmdDisplayColorGainG_Float = "hmdDisplayColorGainG";
स्थिर ध्रुव वर्ण * k_pch_SteamVR_HmdDisplayColorGainB_Float = "hmdDisplayColorGainB";
स्थिर ध्रुव वर्ण * k_pch_SteamVR_CustomIconStyle_String = "customIconStyle";
स्थिर ध्रुव वर्ण * k_pch_SteamVR_CustomOffIconStyle_String = "customOffIconStyle";
स्थिर ध्रुव वर्ण * k_pch_SteamVR_CustomIconForceUpdate_String = "customIconForceUpdate";
स्थिर ध्रुव वर्ण * k_pch_SteamVR_AllowGlobalActionSetPriority = "globalActionSetPriority";
स्थिर ध्रुव वर्ण * k_pch_SteamVR_OverlayRenderQuality = "overlayRenderQuality_2";
स्थिर ध्रुव वर्ण * k_pch_SteamVR_BlockOculusSDKOnOpenVRLaunchOption_Bool = "blockOculusSDKOnOpenVRLaunchOption";
स्थिर ध्रुव वर्ण * k_pch_SteamVR_BlockOculusSDKOnAllLaunches_Bool = "blockOculusSDKOnAllLaunches";
स्थिर ध्रुव वर्ण * k_pch_SteamVR_HDCPLegacyCompatibility_Bool = "hdcp14legacyCompatibility";
स्थिर ध्रुव वर्ण * k_pch_SteamVR_DisplayPortTrainingMode_Int = "displayPortTrainingMode";
स्थिर ध्रुव वर्ण * k_pch_SteamVR_UsePrism_Bool = "usePrism";
स्थिर ध्रुव वर्ण * k_pch_DirectMode_Section = "direct_mode";
स्थिर ध्रुव वर्ण * k_pch_DirectMode_Enable_Bool = "enable";
स्थिर ध्रुव वर्ण * k_pch_Direct_Mode_गिनती_Int32 = "count";
स्थिर ध्रुव वर्ण * k_pch_DirectMode_EdidVid_Int32 = "edidVid";
स्थिर ध्रुव वर्ण * k_pch_DirectMode_EdidPid_Int32 = "edidPid";
स्थिर ध्रुव वर्ण * k_pch_Lighthouse_Section = "driver_lighthouse";
स्थिर ध्रुव वर्ण * k_pch_Lighthouse_DisableIMU_Bool = "disableimu";
स्थिर ध्रुव वर्ण * k_pch_Lighthouse_DisableIMUExceptHMD_Bool = "disableimuexcepthmd";
स्थिर ध्रुव वर्ण * k_pch_Lighthouse_UseDisambiguation_String = "usedisambiguation";
स्थिर ध्रुव वर्ण * k_pch_Lighthouse_DisambiguationDebug_Int32 = "disambiguationdebug";
स्थिर ध्रुव वर्ण * k_pch_Lighthouse_PrimaryBasestation_Int32 = "primarybasestation";
स्थिर ध्रुव वर्ण * k_pch_Lighthouse_DBHistory_Bool = "dbhistory";
स्थिर ध्रुव वर्ण * k_pch_Lighthouse_EnableBluetooth_Bool = "enableBluetooth";
स्थिर ध्रुव वर्ण * k_pch_Lighthouse_PowerManagedBaseStations_String = "PowerManagedBaseStations";
स्थिर ध्रुव वर्ण * k_pch_Lighthouse_PowerManagedBaseStations2_String = "PowerManagedBaseStations2";
स्थिर ध्रुव वर्ण * k_pch_Lighthouse_InactivityTimeoutForBaseStations_Int32 = "InactivityTimeoutForBaseStations";
स्थिर ध्रुव वर्ण * k_pch_Lighthouse_EnableImuFallback_Bool = "enableImuFallback";
स्थिर ध्रुव वर्ण * k_pch_Null_Section = "driver_null";
स्थिर ध्रुव वर्ण * k_pch_Null_Serial_संख्या_String = "serialNumber";
स्थिर ध्रुव वर्ण * k_pch_Null_Model_संख्या_String = "modelNumber";
स्थिर ध्रुव वर्ण * k_pch_Null_WindowX_Int32 = "windowX";
स्थिर ध्रुव वर्ण * k_pch_Null_WindowY_Int32 = "windowY";
स्थिर ध्रुव वर्ण * k_pch_Null_WindowWidth_Int32 = "windowWidth";
स्थिर ध्रुव वर्ण * k_pch_Null_WindowHeight_Int32 = "windowHeight";
स्थिर ध्रुव वर्ण * k_pch_Null_RenderWidth_Int32 = "renderWidth";
स्थिर ध्रुव वर्ण * k_pch_Null_RenderHeight_Int32 = "renderHeight";
स्थिर ध्रुव वर्ण * k_pch_Null_SecondsFromVsyncToPhotons_Float = "secondsFromVsyncToPhotons";
स्थिर ध्रुव वर्ण * k_pch_Null_DisplayFrequency_Float = "displayFrequency";
स्थिर ध्रुव वर्ण * k_pch_WindowsMR_Section = "driver_holographic";
स्थिर ध्रुव वर्ण * k_pch_UserInterface_Section = "userinterface";
स्थिर ध्रुव वर्ण * k_pch_User_Interface_Status_Always_On_शीर्ष_Bool = "StatusAlwaysOnTop";
स्थिर ध्रुव वर्ण * k_pch_UserInterface_MinimizeToTray_Bool = "MinimizeToTray";
स्थिर ध्रुव वर्ण * k_pch_UserInterface_HidePopupsWhenStatusMinimized_Bool = "HidePopupsWhenStatusMinimized";
स्थिर ध्रुव वर्ण * k_pch_UserInterface_Screenshots_Bool = "screenshots";
स्थिर ध्रुव वर्ण * k_pch_UserInterface_ScreenshotType_Int = "screenshotType";
स्थिर ध्रुव वर्ण * k_pch_Notifications_Section = "notifications";
स्थिर ध्रुव वर्ण * k_pch_Notifications_DoNotDisturb_Bool = "DoNotDisturb";
स्थिर ध्रुव वर्ण * k_pch_Keyboard_Section = "keyboard";
स्थिर ध्रुव वर्ण * k_pch_Keyboard_TutorialCompletions = "TutorialCompletions";
स्थिर ध्रुव वर्ण * k_pch_Keyboard_ScaleX = "ScaleX";
स्थिर ध्रुव वर्ण * k_pch_Keyboard_ScaleY = "ScaleY";
स्थिर ध्रुव वर्ण * k_pch_Keyboard_Offset_बायाँ_X = "OffsetLeftX";
स्थिर ध्रुव वर्ण * k_pch_Keyboard_Offset_दायाँ_X = "OffsetRightX";
स्थिर ध्रुव वर्ण * k_pch_Keyboard_OffsetY = "OffsetY";
स्थिर ध्रुव वर्ण * k_pch_Keyboard_Smoothing = "Smoothing";
स्थिर ध्रुव वर्ण * k_pch_Perf_Section = "perfcheck";
स्थिर ध्रुव वर्ण * k_pch_Perf_PerfGraphInHMD_Bool = "perfGraphInHMD";
स्थिर ध्रुव वर्ण * k_pch_Perf_AllowTimingStore_Bool = "allowTimingStore";
स्थिर ध्रुव वर्ण * k_pch_Perf_SaveTimingsOnExit_Bool = "saveTimingsOnExit";
स्थिर ध्रुव वर्ण * k_pch_Perf_TestData_Float = "perfTestData";
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
स्थिर ध्रुव वर्ण * k_pch_Camera_RoomView_Int32 = "roomView";
स्थिर ध्रुव वर्ण * k_pch_Camera_BoundsColorGammaR_Int32 = "cameraBoundsColorGammaR";
स्थिर ध्रुव वर्ण * k_pch_Camera_BoundsColorGammaG_Int32 = "cameraBoundsColorGammaG";
स्थिर ध्रुव वर्ण * k_pch_Camera_BoundsColorGammaB_Int32 = "cameraBoundsColorGammaB";
स्थिर ध्रुव वर्ण * k_pch_Camera_BoundsColorGammaA_Int32 = "cameraBoundsColorGammaA";
स्थिर ध्रुव वर्ण * k_pch_Camera_BoundsStrength_Int32 = "cameraBoundsStrength";
स्थिर ध्रुव वर्ण * k_pch_Camera_RoomViewStyle_Int32 = "roomViewStyle";
स्थिर ध्रुव वर्ण * k_pch_audio_Section = "audio";
स्थिर ध्रुव वर्ण * k_pch_audio_SetOsDefaultPlaybackDevice_Bool = "setOsDefaultPlaybackDevice";
स्थिर ध्रुव वर्ण * k_pch_audio_EnablePlaybackDeviceOverride_Bool = "enablePlaybackDeviceOverride";
स्थिर ध्रुव वर्ण * k_pch_audio_PlaybackDeviceOverride_String = "playbackDeviceOverride";
स्थिर ध्रुव वर्ण * k_pch_audio_PlaybackDeviceOverrideName_String = "playbackDeviceOverrideName";
स्थिर ध्रुव वर्ण * k_pch_audio_SetOsDefaultRecordingDevice_Bool = "setOsDefaultRecordingDevice";
स्थिर ध्रुव वर्ण * k_pch_audio_EnableRecordingDeviceOverride_Bool = "enableRecordingDeviceOverride";
स्थिर ध्रुव वर्ण * k_pch_audio_RecordingDeviceOverride_String = "recordingDeviceOverride";
स्थिर ध्रुव वर्ण * k_pch_audio_RecordingDeviceOverrideName_String = "recordingDeviceOverrideName";
स्थिर ध्रुव वर्ण * k_pch_audio_EnablePlaybackMirror_Bool = "enablePlaybackMirror";
स्थिर ध्रुव वर्ण * k_pch_audio_PlaybackMirrorDevice_String = "playbackMirrorDevice";
स्थिर ध्रुव वर्ण * k_pch_audio_PlaybackMirrorDeviceName_String = "playbackMirrorDeviceName";
स्थिर ध्रुव वर्ण * k_pch_audio_OldPlaybackMirrorDevice_String = "onPlaybackMirrorDevice";
स्थिर ध्रुव वर्ण * k_pch_audio_ActiveMirrorDevice_String = "activePlaybackMirrorDevice";
स्थिर ध्रुव वर्ण * k_pch_audio_EnablePlaybackMirrorIndependentVolume_Bool = "enablePlaybackMirrorIndependentVolume";
स्थिर ध्रुव वर्ण * k_pch_audio_LastHmdPlaybackDeviceId_String = "lastHmdPlaybackDeviceId";
स्थिर ध्रुव वर्ण * k_pch_audio_VIVEHDMIGain = "viveHDMIGain";
स्थिर ध्रुव वर्ण * k_pch_audio_DualSpeakerAndJackOutput_Bool = "dualSpeakerAndJackOutput";
स्थिर ध्रुव वर्ण * k_pch_audio_MuteMicMonitor_Bool = "muteMicMonitor";
स्थिर ध्रुव वर्ण * k_pch_Power_Section = "power";
स्थिर ध्रुव वर्ण * k_pch_Power_PowerOffOnExit_Bool = "powerOffOnExit";
स्थिर ध्रुव वर्ण * k_pch_Power_TurnOffScreensTimeout_Float = "turnOffScreensTimeout";
स्थिर ध्रुव वर्ण * k_pch_Power_TurnOffControllersTimeout_Float = "turnOffControllersTimeout";
स्थिर ध्रुव वर्ण * k_pch_Power_ReturnToWatchdogTimeout_Float = "returnToWatchdogTimeout";
स्थिर ध्रुव वर्ण * k_pch_Power_AutoLaunchSteamVROnButtonPress = "autoLaunchSteamVROnButtonPress";
स्थिर ध्रुव वर्ण * k_pch_Power_PauseCompositorOnStandby_Bool = "pauseCompositorOnStandby";
स्थिर ध्रुव वर्ण * k_pch_Dashboard_Section = "dashboard";
स्थिर ध्रुव वर्ण * k_pch_Dashboard_EnableDashboard_Bool = "enableDashboard";
स्थिर ध्रुव वर्ण * k_pch_Dashboard_ArcadeMode_Bool = "arcadeMode";
स्थिर ध्रुव वर्ण * k_pch_Dashboard_Position = "position";
स्थिर ध्रुव वर्ण * k_pch_Dashboard_DesktopScale = "desktopScale";
स्थिर ध्रुव वर्ण * k_pch_Dashboard_DashboardScale = "dashboardScale";
स्थिर ध्रुव वर्ण * k_pch_Dashboard_UseStandaloneSystemLayer = "standaloneSystemLayer";
स्थिर ध्रुव वर्ण * k_pch_Dashboard_StickyDashboard = "stickyDashboard";
स्थिर ध्रुव वर्ण * k_pch_modelskin_Section = "modelskins";
स्थिर ध्रुव वर्ण * k_pch_Driver_Enable_Bool = "enable";
स्थिर ध्रुव वर्ण * k_pch_Driver_BlockedBySafemode_Bool = "blocked_by_safe_mode";
स्थिर ध्रुव वर्ण * k_pch_Driver_LoadPriority_Int32 = "loadPriority";
स्थिर ध्रुव वर्ण * k_pch_WebInterface_Section = "WebInterface";
स्थिर ध्रुव वर्ण * k_pch_VRWebHelper_Section = "VRWebHelper";
स्थिर ध्रुव वर्ण * k_pch_VRWebHelper_DebuggerEnabled_Bool = "DebuggerEnabled";
स्थिर ध्रुव वर्ण * k_pch_VRWebHelper_DebuggerPort_Int32 = "DebuggerPort";
स्थिर ध्रुव वर्ण * k_pch_TrackingOverride_Section = "TrackingOverrides";
स्थिर ध्रुव वर्ण * k_pch_App_BindingAutosaveURLSuffix_String = "AutosaveURL";
स्थिर ध्रुव वर्ण * k_pch_App_BindingLegacyAPISuffix_String = "_legacy";
स्थिर ध्रुव वर्ण * k_pch_App_BindingSteamVRInputAPISuffix_String = "_steamvrinput";
स्थिर ध्रुव वर्ण * k_pch_App_BindingOpenXRAPISuffix_String = "_openxr";
स्थिर ध्रुव वर्ण * k_pch_App_BindingCurrentURLSuffix_String = "CurrentURL";
स्थिर ध्रुव वर्ण * k_pch_App_BindingPreviousURLSuffix_String = "PreviousURL";
स्थिर ध्रुव वर्ण * k_pch_App_NeedToUpdateAutosaveSuffix_Bool = "NeedToUpdateAutosave";
स्थिर ध्रुव वर्ण * k_pch_App_DominantHand_Int32 = "DominantHand";
स्थिर ध्रुव वर्ण * k_pch_App_BlockOculusSDK_Bool = "blockOculusSDK";
स्थिर ध्रुव वर्ण * k_pch_Trackers_Section = "trackers";
स्थिर ध्रुव वर्ण * k_pch_DesktopUI_Section = "DesktopUI";
स्थिर ध्रुव वर्ण * k_pch_LastKnown_Section = "LastKnown";
स्थिर ध्रुव वर्ण * k_pch_LastKnown_HMDManufacturer_String = "HMDManufacturer";
स्थिर ध्रुव वर्ण * k_pch_LastKnown_HMDModel_String = "HMDModel";
स्थिर ध्रुव वर्ण * k_pch_DismissedWarnings_Section = "DismissedWarnings";
स्थिर ध्रुव वर्ण * k_pch_निवेश_Section = "input";
स्थिर ध्रुव वर्ण * k_pch_निवेश_बायाँ_Thumbstick_Rotation_Float = "leftThumbstickRotation";
स्थिर ध्रुव वर्ण * k_pch_निवेश_दायाँ_Thumbstick_Rotation_Float = "rightThumbstickRotation";
स्थिर ध्रुव वर्ण * k_pch_निवेश_Thumbstick_Deadzone_Float = "thumbstickDeadzone";
स्थिर ध्रुव वर्ण * k_pch_GpuSpeed_Section = "GpuSpeed";
स्थिर ध्रुव वर्ण * IVRScreenshots_Version = "IVRScreenshots_001";
स्थिर ध्रुव वर्ण * IVRResources_Version = "IVRResources_001";
स्थिर ध्रुव वर्ण * IVRDriverManager_Version = "IVRDriverManager_001";
स्थिर ध्रुव unsigned long k_unMaxActionNameLength = 64;
स्थिर ध्रुव unsigned long k_unMaxActionSetNameLength = 64;
स्थिर ध्रुव unsigned long k_un_Max_Action_Origin_गिनती = 16;
स्थिर ध्रुव unsigned long k_unMaxBoneNameLength = 32;
स्थिर ध्रुव पूर्णाङ्क k_nActionSetOverlayGlobalPriorityMin = 16777216;
स्थिर ध्रुव पूर्णाङ्क k_nActionSetOverlayGlobalPriorityMax = 33554431;
स्थिर ध्रुव पूर्णाङ्क k_nActionSetPriorityReservedMin = 33554432;
स्थिर ध्रुव वर्ण * IVRInput_Version = "IVRInput_010";
स्थिर ध्रुव unsigned long long k_ulInvalidIOBufferHandle = 0;
स्थिर ध्रुव वर्ण * IVRIOBuffer_Version = "IVRIOBuffer_002";
स्थिर ध्रुव unsigned long k_ulInvalidSpatialAnchorHandle = 0;
स्थिर ध्रुव वर्ण * IVRSpatialAnchors_Version = "IVRSpatialAnchors_001";
स्थिर ध्रुव वर्ण * IVRDebug_Version = "IVRDebug_001";
स्थिर ध्रुव unsigned long long k_ulDisplayRedirectContainer = 25769803779;
स्थिर ध्रुव वर्ण * IVRProperties_Version = "IVRProperties_001";
स्थिर ध्रुव वर्ण * k_pch_Path_User_Hand_दायाँ = "/user/hand/right";
स्थिर ध्रुव वर्ण * k_pch_Path_User_Hand_बायाँ = "/user/hand/left";
स्थिर ध्रुव वर्ण * k_pchPathUserHandPrimary = "/user/hand/primary";
स्थिर ध्रुव वर्ण * k_pchPathUserHandSecondary = "/user/hand/secondary";
स्थिर ध्रुव वर्ण * k_pchPathUserHead = "/user/head";
स्थिर ध्रुव वर्ण * k_pchPathUserGamepad = "/user/gamepad";
स्थिर ध्रुव वर्ण * k_pchPathUserTreadmill = "/user/treadmill";
स्थिर ध्रुव वर्ण * k_pchPathUserStylus = "/user/stylus";
स्थिर ध्रुव वर्ण * k_pchPathDevices = "/devices";
स्थिर ध्रुव वर्ण * k_pchPathDevicePath = "/device_path";
स्थिर ध्रुव वर्ण * k_pchPathBestAliasPath = "/best_alias_path";
स्थिर ध्रुव वर्ण * k_pchPathBoundTrackerAliasPath = "/bound_tracker_path";
स्थिर ध्रुव वर्ण * k_pchPathBoundTrackerRole = "/bound_tracker_role";
स्थिर ध्रुव वर्ण * k_pchPathPoseRaw = "/pose/raw";
स्थिर ध्रुव वर्ण * k_pchPathPoseTip = "/pose/tip";
स्थिर ध्रुव वर्ण * k_pchPathPoseGrip = "/pose/grip";
स्थिर ध्रुव वर्ण * k_pchPathSystemButtonClick = "/input/system/click";
स्थिर ध्रुव वर्ण * k_pchPathProximity = "/proximity";
स्थिर ध्रुव वर्ण * k_pchPathControllerTypePrefix = "/controller_type/";
स्थिर ध्रुव वर्ण * k_pch_Path_निवेश_Profile_Suffix = "/input_profile";
स्थिर ध्रुव वर्ण * k_pchPathBindingNameSuffix = "/binding_name";
स्थिर ध्रुव वर्ण * k_pchPathBindingUrlSuffix = "/binding_url";
स्थिर ध्रुव वर्ण * k_pchPathBindingErrorSuffix = "/binding_error";
स्थिर ध्रुव वर्ण * k_pchPathActiveActionSets = "/active_action_sets";
स्थिर ध्रुव वर्ण * k_pchPathComponentUpdates = "/total_component_updates";
स्थिर ध्रुव वर्ण * k_pch_Path_User_Foot_बायाँ = "/user/foot/left";
स्थिर ध्रुव वर्ण * k_pch_Path_User_Foot_दायाँ = "/user/foot/right";
स्थिर ध्रुव वर्ण * k_pch_Path_User_Shoulder_बायाँ = "/user/shoulder/left";
स्थिर ध्रुव वर्ण * k_pch_Path_User_Shoulder_दायाँ = "/user/shoulder/right";
स्थिर ध्रुव वर्ण * k_pch_Path_User_Elbow_बायाँ = "/user/elbow/left";
स्थिर ध्रुव वर्ण * k_pch_Path_User_Elbow_दायाँ = "/user/elbow/right";
स्थिर ध्रुव वर्ण * k_pch_Path_User_Knee_बायाँ = "/user/knee/left";
स्थिर ध्रुव वर्ण * k_pch_Path_User_Knee_दायाँ = "/user/knee/right";
स्थिर ध्रुव वर्ण * k_pchPathUserWaist = "/user/waist";
स्थिर ध्रुव वर्ण * k_pchPathUserChest = "/user/chest";
स्थिर ध्रुव वर्ण * k_pchPathUserCamera = "/user/camera";
स्थिर ध्रुव वर्ण * k_pchPathUserKeyboard = "/user/keyboard";
स्थिर ध्रुव वर्ण * k_pch_Path_Client_App_कुंजी = "/client_info/app_key";
स्थिर ध्रुव unsigned long long k_ulInvalidPathHandle = 0;
स्थिर ध्रुव वर्ण * IVRPaths_Version = "IVRPaths_001";
स्थिर ध्रुव वर्ण * IVRBlockQueue_Version = "IVRBlockQueue_005";

// OpenVR Enums

प्रकारनिर्देश गणना EVREye
{
	EVREye_Eye_बायाँ = 0,
	EVREye_Eye_दायाँ = 1,
} EVREye;

प्रकारनिर्देश गणना ETextureType
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

प्रकारनिर्देश गणना EColorSpace
{
	EColorSpace_ColorSpace_Auto = 0,
	EColorSpace_ColorSpace_Gamma = 1,
	EColorSpace_ColorSpace_Linear = 2,
} EColorSpace;

प्रकारनिर्देश गणना ETrackingResult
{
	ETrackingResult_TrackingResult_Uninitialized = 1,
	ETrackingResult_TrackingResult_Calibrating_InProgress = 100,
	ETrackingResult_TrackingResult_Calibrating_OutOfRange = 101,
	ETrackingResult_TrackingResult_Running_OK = 200,
	ETrackingResult_TrackingResult_Running_OutOfRange = 201,
	ETrackingResult_TrackingResult_Fallback_RotationOnly = 300,
} ETrackingResult;

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
	ETracked_Controller_Role_Tracked_Controller_Role_बायाँ_Hand = 1,
	ETracked_Controller_Role_Tracked_Controller_Role_दायाँ_Hand = 2,
	ETrackedControllerRole_TrackedControllerRole_OptOut = 3,
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
	EAdditionalRadioFeatures_AdditionalRadioFeatures_InternalDongle = 2,
	EAdditionalRadioFeatures_AdditionalRadioFeatures_ExternalDongle = 4,
} EAdditionalRadioFeatures;

प्रकारनिर्देश गणना ETrackedDeviceProperty
{
	ETrackedDeviceProperty_Prop_Invalid = 0,
	ETrackedDeviceProperty_Prop_TrackingSystemName_String = 1000,
	ETracked_Device_Property_Prop_Model_संख्या_String = 1001,
	ETracked_Device_Property_Prop_Serial_संख्या_String = 1002,
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
	ETracked_Device_Property_Prop_Resource_मूल_String = 1035,
	ETrackedDeviceProperty_Prop_RegisteredDeviceType_String = 1036,
	ETracked_Device_Property_Prop_निवेश_Profile_Path_String = 1037,
	ETrackedDeviceProperty_Prop_NeverTracked_Bool = 1038,
	ETracked_Device_Property_Prop_अंक_Cameras_Int32 = 1039,
	ETrackedDeviceProperty_Prop_CameraFrameLayout_Int32 = 1040,
	ETrackedDeviceProperty_Prop_CameraStreamFormat_Int32 = 1041,
	ETrackedDeviceProperty_Prop_AdditionalDeviceSettingsPath_String = 1042,
	ETrackedDeviceProperty_Prop_Identifiable_Bool = 1043,
	ETrackedDeviceProperty_Prop_BootloaderVersion_Uint64 = 1044,
	ETrackedDeviceProperty_Prop_AdditionalSystemReportData_String = 1045,
	ETrackedDeviceProperty_Prop_CompositeFirmwareVersion_String = 1046,
	ETrackedDeviceProperty_Prop_Firmware_RemindUpdate_Bool = 1047,
	ETrackedDeviceProperty_Prop_PeripheralApplicationVersion_Uint64 = 1048,
	ETracked_Device_Property_Prop_Manufacturer_Serial_संख्या_String = 1049,
	ETracked_Device_Property_Prop_Computed_Serial_संख्या_String = 1050,
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
	ETracked_Device_Property_Prop_Display_MCImage_बायाँ_String = 2012,
	ETracked_Device_Property_Prop_Display_MCImage_दायाँ_String = 2013,
	ETrackedDeviceProperty_Prop_DisplayGCBlackClamp_Float = 2014,
	ETrackedDeviceProperty_Prop_EdidProductID_Int32 = 2015,
	ETrackedDeviceProperty_Prop_CameraToHeadTransform_Matrix34 = 2016,
	ETrackedDeviceProperty_Prop_DisplayGCType_Int32 = 2017,
	ETrackedDeviceProperty_Prop_DisplayGCOffset_Float = 2018,
	ETrackedDeviceProperty_Prop_DisplayGCScale_Float = 2019,
	ETrackedDeviceProperty_Prop_DisplayGCPrescale_Float = 2020,
	ETrackedDeviceProperty_Prop_DisplayGCImage_String = 2021,
	ETracked_Device_Property_Prop_Lens_Center_बायाँ_U_Float = 2022,
	ETracked_Device_Property_Prop_Lens_Center_बायाँ_V_Float = 2023,
	ETracked_Device_Property_Prop_Lens_Center_दायाँ_U_Float = 2024,
	ETracked_Device_Property_Prop_Lens_Center_दायाँ_V_Float = 2025,
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
	ETracked_Device_Property_Prop_Display_MCImage_अंक_Channels_Int32 = 2040,
	ETracked_Device_Property_Prop_Display_MCImage_Data_द्विआधारी = 2041,
	ETrackedDeviceProperty_Prop_SecondsFromPhotonsToVblank_Float = 2042,
	ETrackedDeviceProperty_Prop_DriverDirectModeSendsVsyncEvents_Bool = 2043,
	ETrackedDeviceProperty_Prop_DisplayDebugMode_Bool = 2044,
	ETrackedDeviceProperty_Prop_GraphicsAdapterLuid_Uint64 = 2045,
	ETrackedDeviceProperty_Prop_DriverProvidedChaperonePath_String = 2048,
	ETracked_Device_Property_Prop_Expected_Tracking_Reference_गिनती_Int32 = 2049,
	ETracked_Device_Property_Prop_Expected_Controller_गिनती_Int32 = 2050,
	ETracked_Device_Property_Prop_Named_Icon_Path_Controller_बायाँ_Device_Off_String = 2051,
	ETracked_Device_Property_Prop_Named_Icon_Path_Controller_दायाँ_Device_Off_String = 2052,
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
	ETracked_Device_Property_Prop_Display_Color_Mult_बायाँ_Vector3 = 2082,
	ETracked_Device_Property_Prop_Display_Color_Mult_दायाँ_Vector3 = 2083,
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
	ETracked_Device_Property_Prop_DSCSlice_गिनती_Int32 = 2111,
	ETrackedDeviceProperty_Prop_DSCBPPx16_Int32 = 2112,
	ETrackedDeviceProperty_Prop_DriverRequestedMuraCorrectionMode_Int32 = 2200,
	ETracked_Device_Property_Prop_Driver_Requested_Mura_Feather_Inner_बायाँ_Int32 = 2201,
	ETracked_Device_Property_Prop_Driver_Requested_Mura_Feather_Inner_दायाँ_Int32 = 2202,
	ETracked_Device_Property_Prop_Driver_Requested_Mura_Feather_Inner_शीर्ष_Int32 = 2203,
	ETrackedDeviceProperty_Prop_DriverRequestedMuraFeather_InnerBottom_Int32 = 2204,
	ETracked_Device_Property_Prop_Driver_Requested_Mura_Feather_Outer_बायाँ_Int32 = 2205,
	ETracked_Device_Property_Prop_Driver_Requested_Mura_Feather_Outer_दायाँ_Int32 = 2206,
	ETracked_Device_Property_Prop_Driver_Requested_Mura_Feather_Outer_शीर्ष_Int32 = 2207,
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
	ETracked_Device_Property_Prop_Field_Of_View_बायाँ_Degrees_Float = 4000,
	ETracked_Device_Property_Prop_Field_Of_View_दायाँ_Degrees_Float = 4001,
	ETracked_Device_Property_Prop_Field_Of_View_शीर्ष_Degrees_Float = 4002,
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
	ETracked_Device_Property_Prop_Named_Icon_Path_Device_Alert_निचला_String = 5008,
	ETrackedDeviceProperty_Prop_NamedIconPathDeviceStandbyAlert_String = 5009,
	ETracked_Device_Property_Prop_Display_Hidden_Area_द्विआधारी_Start = 5100,
	ETracked_Device_Property_Prop_Display_Hidden_Area_द्विआधारी_End = 5150,
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

प्रकारनिर्देश गणना ETrackedPropertyError
{
	ETrackedPropertyError_TrackedProp_Success = 0,
	ETrackedPropertyError_TrackedProp_WrongDataType = 1,
	ETrackedPropertyError_TrackedProp_WrongDeviceClass = 2,
	ETrackedPropertyError_TrackedProp_BufferTooSmall = 3,
	ETrackedPropertyError_TrackedProp_UnknownProperty = 4,
	ETrackedPropertyError_TrackedProp_InvalidDevice = 5,
	ETrackedPropertyError_TrackedProp_CouldNotContactServer = 6,
	ETracked_Property_Error_Tracked_Prop_मूल्य_Not_Provided_By_Device = 7,
	ETrackedPropertyError_TrackedProp_StringExceedsMaximumLength = 8,
	ETrackedPropertyError_TrackedProp_NotYetAvailable = 9,
	ETrackedPropertyError_TrackedProp_PermissionDenied = 10,
	ETrackedPropertyError_TrackedProp_InvalidOperation = 11,
	ETrackedPropertyError_TrackedProp_CannotWriteToWildcards = 12,
	ETrackedPropertyError_TrackedProp_IPCReadFailure = 13,
	ETrackedPropertyError_TrackedProp_OutOfMemory = 14,
	ETrackedPropertyError_TrackedProp_InvalidContainer = 15,
} ETrackedPropertyError;

प्रकारनिर्देश गणना EHmdTrackingStyle
{
	EHmdTrackingStyle_HmdTrackingStyle_Unknown = 0,
	EHmdTrackingStyle_HmdTrackingStyle_Lighthouse = 1,
	EHmdTrackingStyle_HmdTrackingStyle_OutsideInCameras = 2,
	EHmdTrackingStyle_HmdTrackingStyle_InsideOutCameras = 3,
} EHmdTrackingStyle;

प्रकारनिर्देश गणना EVRSubmitFlags
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
	EVRState_VRState_Ready_Alert_निचला = 7,
} EVRState;

प्रकारनिर्देश गणना EVREventType
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
	EVREvent_Type_VREvent_निवेश_Focus_Captured = 400,
	EVREvent_Type_VREvent_निवेश_Focus_Released = 401,
	EVREventType_VREvent_SceneApplicationChanged = 404,
	EVREvent_Type_VREvent_निवेश_Focus_Changed = 406,
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
	EVREvent_Type_VREvent_Keyboard_Char_निवेश = 1201,
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
	EVREvent_Type_VREvent_निवेश_Haptic_Vibration = 1700,
	EVREvent_Type_VREvent_निवेश_Binding_Load_Failed = 1701,
	EVREvent_Type_VREvent_निवेश_Binding_Load_Successful = 1702,
	EVREvent_Type_VREvent_निवेश_Action_Manifest_Reloaded = 1703,
	EVREvent_Type_VREvent_निवेश_Action_Manifest_Load_Failed = 1704,
	EVREvent_Type_VREvent_निवेश_Progress_Update = 1705,
	EVREvent_Type_VREvent_निवेश_Tracker_Activated = 1706,
	EVREvent_Type_VREvent_निवेश_Bindings_Updated = 1707,
	EVREvent_Type_VREvent_निवेश_Binding_Subscription_Changed = 1708,
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
	EVRButton_Id_k_EButton_DPad_बायाँ = 3,
	EVRButtonId_k_EButton_DPad_Up = 4,
	EVRButton_Id_k_EButton_DPad_दायाँ = 5,
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

प्रकारनिर्देश गणना EVRMouseButton
{
	EVRMouse_Button_VRMouse_Button_बायाँ = 1,
	EVRMouse_Button_VRMouse_Button_दायाँ = 2,
	EVRMouse_Button_VRMouse_Button_मध्य = 4,
} EVRMouseButton;

प्रकारनिर्देश गणना EShowUIType
{
	EShowUIType_ShowUI_ControllerBinding = 0,
	EShowUIType_ShowUI_ManageTrackers = 1,
	EShowUIType_ShowUI_Pairing = 3,
	EShowUIType_ShowUI_Settings = 4,
	EShowUIType_ShowUI_DebugCommands = 5,
	EShowUIType_ShowUI_FullControllerBinding = 6,
	EShowUIType_ShowUI_ManageDrivers = 7,
} EShowUIType;

प्रकारनिर्देश गणना EHDCPError
{
	EHDCPError_HDCPError_None = 0,
	EHDCPError_HDCPError_LinkLost = 1,
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
	EVRInput_Error_VRInput_Error_Invalid_Bone_गिनती = 11,
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

प्रकारनिर्देश गणना EVRSpatialAnchorError
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

प्रकारनिर्देश गणना EHiddenAreaMeshType
{
	EHiddenAreaMeshType_k_eHiddenAreaMesh_Standard = 0,
	EHiddenAreaMeshType_k_eHiddenAreaMesh_Inverse = 1,
	EHidden_Area_Mesh_Type_k_e_Hidden_Area_Mesh_पंक्ति_Loop = 2,
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
	ECollision_Bounds_Style_COLLISION_BOUNDS_STYLE_गिनती = 5,
} ECollisionBoundsStyle;

प्रकारनिर्देश गणना EVROverlayError
{
	EVROverlayError_VROverlayError_None = 0,
	EVROverlayError_VROverlayError_UnknownOverlay = 10,
	EVROverlayError_VROverlayError_InvalidHandle = 11,
	EVROverlayError_VROverlayError_PermissionDenied = 12,
	EVROverlayError_VROverlayError_OverlayLimitExceeded = 13,
	EVROverlayError_VROverlayError_WrongVisibilityType = 14,
	EVROverlay_Error_VROverlay_Error_कुंजी_Too_Long = 15,
	EVROverlayError_VROverlayError_NameTooLong = 16,
	EVROverlay_Error_VROverlay_Error_कुंजी_In_Use = 17,
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
	EVRApplicationType_VRApplication_RoomView = 13,
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
	EVRNotificationError_VRNotificationError_NotificationQueueFull = 101,
	EVRNotificationError_VRNotificationError_InvalidOverlayHandle = 102,
	EVRNotification_Error_VRNotification_Error_System_With_User_मूल्य_Already_Exists = 103,
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
	EVRSkeletalTrackingLevel_VRSkeletalTracking_Full = 2,
	EVRSkeletal_Tracking_Level_VRSkeletal_Tracking_Level_गिनती = 3,
	EVRSkeletalTrackingLevel_VRSkeletalTrackingLevel_Max = 2,
} EVRSkeletalTrackingLevel;

प्रकारनिर्देश गणना EVRInitError
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
	EVRInit_Error_VRInit_Error_Init_निचला_Power_Watchdog_Not_Supported = 129,
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
	EVRTrackedCameraFrameType_VRTrackedCameraFrameType_MaximumUndistorted = 2,
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

प्रकारनिर्देश गणना EVRMuraCorrectionMode
{
	EVRMuraCorrectionMode_Default = 0,
	EVRMuraCorrectionMode_NoCorrection = 1,
} EVRMuraCorrectionMode;

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
	EVRApplication_Error_VRApplication_Error_App_कुंजी_Already_Exists = 100,
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

प्रकारनिर्देश गणना EVRApplicationProperty
{
	EVRApplicationProperty_VRApplicationProperty_Name_String = 0,
	EVRApplicationProperty_VRApplicationProperty_LaunchType_String = 11,
	EVRApplicationProperty_VRApplicationProperty_WorkingDirectory_String = 12,
	EVRApplication_Property_VRApplication_Property_द्विआधारी_Path_String = 13,
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

प्रकारनिर्देश गणना EVRSceneApplicationState
{
	EVRSceneApplicationState_None = 0,
	EVRSceneApplicationState_Starting = 1,
	EVRSceneApplicationState_Quitting = 2,
	EVRSceneApplicationState_Running = 3,
	EVRSceneApplicationState_Waiting = 4,
} EVRSceneApplicationState;

प्रकारनिर्देश गणना ChaperoneCalibrationState
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

प्रकारनिर्देश गणना EChaperoneConfigFile
{
	EChaperoneConfigFile_Live = 1,
	EChaperoneConfigFile_Temp = 2,
} EChaperoneConfigFile;

प्रकारनिर्देश गणना EChaperoneImportFlags
{
	EChaperoneImportFlags_EChaperoneImport_BoundsOnly = 1,
} EChaperoneImportFlags;

प्रकारनिर्देश गणना EVRCompositorError
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

प्रकारनिर्देश गणना EVRCompositorTimingMode
{
	EVRCompositorTimingMode_VRCompositorTimingMode_Implicit = 0,
	EVRCompositorTimingMode_VRCompositorTimingMode_Explicit_RuntimePerformsPostPresentHandoff = 1,
	EVRCompositorTimingMode_VRCompositorTimingMode_Explicit_ApplicationPerformsPostPresentHandoff = 2,
} EVRCompositorTimingMode;

प्रकारनिर्देश गणना VROverlay_निवेश_Method
{
	VROverlay_निवेश_Method_None = 0,
	VROverlay_निवेश_Method_Mouse = 1,
} VROverlay_निवेश_Method;

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

प्रकारनिर्देश गणना EGamepad_Text_निवेश_Mode
{
	EGamepad_Text_निवेश_Mode_k_EGamepad_Text_निवेश_Mode_Normal = 0,
	EGamepad_Text_निवेश_Mode_k_EGamepad_Text_निवेश_Mode_Password = 1,
	EGamepad_Text_निवेश_Mode_k_EGamepad_Text_निवेश_Mode_Submit = 2,
} EGamepad_Text_निवेश_Mode;

प्रकारनिर्देश गणना EGamepad_Text_निवेश_पंक्ति_Mode
{
	EGamepad_Text_निवेश_पंक्ति_Mode_k_EGamepad_Text_निवेश_पंक्ति_Mode_Single_पंक्ति = 0,
	EGamepad_Text_निवेश_पंक्ति_Mode_k_EGamepad_Text_निवेश_पंक्ति_Mode_Multiple_पंक्तियाँ = 1,
} EGamepad_Text_निवेश_पंक्ति_Mode;

प्रकारनिर्देश गणना EVROverlayIntersectionMaskPrimitiveType
{
	EVROverlayIntersectionMaskPrimitiveType_OverlayIntersectionPrimitiveType_Rectangle = 0,
	EVROverlayIntersectionMaskPrimitiveType_OverlayIntersectionPrimitiveType_Circle = 1,
} EVROverlayIntersectionMaskPrimitiveType;

प्रकारनिर्देश गणना EKeyboardFlags
{
	EKeyboardFlags_KeyboardFlag_Minimal = 1,
	EKeyboardFlags_KeyboardFlag_Modal = 2,
} EKeyboardFlags;

प्रकारनिर्देश गणना EDeviceType
{
	EDeviceType_DeviceType_Invalid = -1,
	EDeviceType_DeviceType_DirectX11 = 0,
	EDeviceType_DeviceType_Vulkan = 1,
} EDeviceType;

प्रकारनिर्देश गणना HeadsetViewMode_t
{
	Headset_View_Mode_t_Headset_View_Mode_बायाँ = 0,
	Headset_View_Mode_t_Headset_View_Mode_दायाँ = 1,
	HeadsetViewMode_t_HeadsetViewMode_Both = 2,
} HeadsetViewMode_t;

प्रकारनिर्देश गणना EVRRenderModelError
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
	EVRNotification_Type_Transient_System_With_User_मूल्य = 2,
} EVRNotificationType;

प्रकारनिर्देश गणना EVRNotificationStyle
{
	EVRNotificationStyle_None = 0,
	EVRNotificationStyle_Application = 100,
	EVRNotificationStyle_Contact_Disabled = 200,
	EVRNotificationStyle_Contact_Enabled = 201,
	EVRNotificationStyle_Contact_Active = 202,
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
	EVRScreenshotError_VRScreenshotError_IncompatibleVersion = 100,
	EVRScreenshotError_VRScreenshotError_NotFound = 101,
	EVRScreenshotError_VRScreenshotError_BufferTooSmall = 102,
	EVRScreenshotError_VRScreenshotError_ScreenshotAlreadyInProgress = 108,
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
	EVRSkeletalReferencePose_VRSkeletalReferencePose_GripLimit = 3,
} EVRSkeletalReferencePose;

प्रकारनिर्देश गणना EVRFinger
{
	EVRFinger_VRFinger_Thumb = 0,
	EVRFinger_VRFinger_Index = 1,
	EVRFinger_VRFinger_मध्य = 2,
	EVRFinger_VRFinger_Ring = 3,
	EVRFinger_VRFinger_Pinky = 4,
	EVRFinger_VRFinger_गिनती = 5,
} EVRFinger;

प्रकारनिर्देश गणना EVRFingerSplay
{
	EVRFingerSplay_VRFingerSplay_Thumb_Index = 0,
	EVRFinger_Splay_VRFinger_Splay_Index_मध्य = 1,
	EVRFinger_Splay_VRFinger_Splay_मध्य_Ring = 2,
	EVRFingerSplay_VRFingerSplay_Ring_Pinky = 3,
	EVRFinger_Splay_VRFinger_Splay_गिनती = 4,
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

प्रकारनिर्देश गणना EVRInputStringBits
{
	EVRInputStringBits_VRInputString_Hand = 1,
	EVRInputStringBits_VRInputString_ControllerType = 2,
	EVRInput_String_Bits_VRInput_String_निवेश_Source = 4,
	EVRInputStringBits_VRInputString_All = -1,
} EVRInputStringBits;

प्रकारनिर्देश गणना EIOBufferError
{
	EIOBufferError_IOBuffer_Success = 0,
	EIOBufferError_IOBuffer_OperationFailed = 100,
	EIOBufferError_IOBuffer_InvalidHandle = 101,
	EIOBufferError_IOBuffer_InvalidArgument = 102,
	EIOBufferError_IOBuffer_PathExists = 103,
	EIOBufferError_IOBuffer_PathDoesNotExist = 104,
	EIOBufferError_IOBuffer_Permission = 105,
} EIOBufferError;

प्रकारनिर्देश गणना EIOBufferMode
{
	EIOBufferMode_IOBufferMode_Read = 1,
	EIOBufferMode_IOBufferMode_Write = 2,
	EIOBufferMode_IOBufferMode_Create = 512,
} EIOBufferMode;

प्रकारनिर्देश गणना EVRDebugError
{
	EVRDebugError_VRDebugError_Success = 0,
	EVRDebugError_VRDebugError_BadParameter = 1,
} EVRDebugError;

प्रकारनिर्देश गणना EPropertyWriteType
{
	EPropertyWriteType_PropertyWrite_Set = 0,
	EPropertyWriteType_PropertyWrite_Erase = 1,
	EPropertyWriteType_PropertyWrite_SetError = 2,
} EPropertyWriteType;

प्रकारनिर्देश गणना EBlockQueueError
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

प्रकारनिर्देश गणना EBlockQueueReadType
{
	EBlockQueueReadType_BlockQueueRead_Latest = 0,
	EBlockQueueReadType_BlockQueueRead_New = 1,
	EBlockQueueReadType_BlockQueueRead_Next = 2,
} EBlockQueueReadType;

प्रकारनिर्देश गणना EBlockQueueCreationFlag
{
	EBlockQueueCreationFlag_BlockQueueFlag_OwnerIsReader = 1,
} EBlockQueueCreationFlag;


// OpenVR typedefs

प्रकारनिर्देश uint32_t PropertyTypeTag_t;
प्रकारनिर्देश uint32_t SpatialAnchorHandle_t;
प्रकारनिर्देश शून्य * glSharedTextureHandle_t;
प्रकारनिर्देश int32_t glInt_t;
प्रकारनिर्देश uint32_t glUInt_t;
प्रकारनिर्देश uint64_t SharedTextureHandle_t;
प्रकारनिर्देश uint32_t DriverId_t;
प्रकारनिर्देश uint32_t TrackedDeviceIndex_t;
प्रकारनिर्देश uint64_t WebConsoleHandle_t;
प्रकारनिर्देश uint64_t PropertyContainerHandle_t;
प्रकारनिर्देश PropertyContainerHandle_t DriverHandle_t;
प्रकारनिर्देश uint64_t VRActionHandle_t;
प्रकारनिर्देश uint64_t VRActionSetHandle_t;
प्रकारनिर्देश uint64_t VRInput_मूल्य_Handle_t;
प्रकारनिर्देश uint32_t VRComponentProperties;
प्रकारनिर्देश uint64_t VROverlayHandle_t;
प्रकारनिर्देश int32_t BoneIndex_t;
प्रकारनिर्देश uint64_t TrackedCameraHandle_t;
प्रकारनिर्देश uint32_t ScreenshotHandle_t;
प्रकारनिर्देश int32_t TextureID_t;
प्रकारनिर्देश uint32_t VRNotificationId;
प्रकारनिर्देश uint64_t IOBufferHandle_t;
प्रकारनिर्देश uint64_t VrProfilerEventHandle_t;
प्रकारनिर्देश EVRInitError HmdError;
प्रकारनिर्देश EVREye Hmd_Eye;
प्रकारनिर्देश EColorSpace ColorSpace;
प्रकारनिर्देश ETrackingResult HmdTrackingResult;
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
प्रकारनिर्देश uint64_t PathHandle_t;

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
	संरचना HmdVector2_t v_शीर्ष_बायाँ;
	संरचना HmdVector2_t v_Bottom_दायाँ;
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
	संरचना HmdMatrix34_t mDeviceToAbsoluteTracking;
	संरचना HmdVector3_t vVelocity;
	संरचना HmdVector3_t vAngularVelocity;
	गणना ETrackingResult eTrackingResult;
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
	संरचना HmdMatrix34_t mDeviceToAbsoluteTracking;
} VRTextureWithPose_t;

प्रकारनिर्देश संरचना VRTextureDepthInfo_t
{
	शून्य * handle; // void *
	संरचना HmdMatrix44_t mProjection;
	संरचना HmdVector2_t vRange;
} VRTextureDepthInfo_t;

प्रकारनिर्देश संरचना VRTextureWithDepth_t
{
	शून्य * handle; // void *
	गणना ETextureType eType;
	गणना EColorSpace eColorSpace;
	संरचना VRTextureDepthInfo_t depth;
} VRTextureWithDepth_t;

प्रकारनिर्देश संरचना VRTextureWithPoseAndDepth_t
{
	शून्य * handle; // void *
	गणना ETextureType eType;
	गणना EColorSpace eColorSpace;
	संरचना HmdMatrix34_t mDeviceToAbsoluteTracking;
	संरचना VRTextureDepthInfo_t depth;
} VRTextureWithPoseAndDepth_t;

प्रकारनिर्देश संरचना VRVulkanTextureData_t
{
	uint64_t m_nImage;
	संरचना VkDevice_T * m_pDevice; // struct VkDevice_T *
	संरचना VkPhysicalDevice_T * m_pPhysicalDevice; // struct VkPhysicalDevice_T *
	संरचना VkInstance_T * m_pInstance; // struct VkInstance_T *
	संरचना VkQueue_T * m_pQueue; // struct VkQueue_T *
	uint32_t m_nQueueFamilyIndex;
	uint32_t m_nWidth;
	uint32_t m_nHeight;
	uint32_t m_nFormat;
	uint32_t m_n_Sample_गिनती;
} VRVulkanTextureData_t;

प्रकारनिर्देश संरचना VRVulkanTextureArrayData_t
{
	uint32_t m_unArrayIndex;
	uint32_t m_unArraySize;
} VRVulkanTextureArrayData_t;

प्रकारनिर्देश संरचना D3D12TextureData_t
{
	संरचना ID3D12Resource * m_pResource; // struct ID3D12Resource *
	संरचना ID3D12CommandQueue * m_pCommandQueue; // struct ID3D12CommandQueue *
	uint32_t m_n_गाँठ_Mask;
} D3D12TextureData_t;

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
	uint32_t unused;
	भिन्न viewportscale;
} VREvent_Scroll_t;

प्रकारनिर्देश संरचना VREvent_TouchPadMove_t
{
	bool bFingerDown;
	भिन्न flSecondsFingerDown;
	भिन्न f_मूल्य_XFirst;
	भिन्न f_मूल्य_YFirst;
	भिन्न f_मूल्य_XRaw;
	भिन्न f_मूल्य_YRaw;
} VREvent_TouchPadMove_t;

प्रकारनिर्देश संरचना VREvent_Notification_t
{
	uint64_t ul_User_मूल्य;
	uint32_t notificationId;
} VREvent_Notification_t;

प्रकारनिर्देश संरचना VREvent_Process_t
{
	uint32_t pid;
	uint32_t oldPid;
	bool bForced;
	bool bConnectionLost;
} VREvent_Process_t;

प्रकारनिर्देश संरचना VREvent_Overlay_t
{
	uint64_t overlayHandle;
	uint64_t devicePath;
	uint64_t memoryBlockId;
} VREvent_Overlay_t;

प्रकारनिर्देश संरचना VREvent_Status_t
{
	uint32_t statusState;
} VREvent_Status_t;

प्रकारनिर्देश संरचना VREvent_Keyboard_t
{
	वर्ण c_New_निवेश[8]; //char[8]
	uint64_t u_User_मूल्य;
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

प्रकारनिर्देश संरचना VREvent_ScreenshotProgress_t
{
	भिन्न progress;
} VREvent_ScreenshotProgress_t;

प्रकारनिर्देश संरचना VREvent_ApplicationLaunch_t
{
	uint32_t pid;
	uint32_t unArgsHandle;
} VREvent_ApplicationLaunch_t;

प्रकारनिर्देश संरचना VREvent_EditingCameraSurface_t
{
	uint64_t overlayHandle;
	uint32_t nVisualMode;
} VREvent_EditingCameraSurface_t;

प्रकारनिर्देश संरचना VREvent_MessageOverlay_t
{
	uint32_t unVRMessageOverlayResponse;
} VREvent_MessageOverlay_t;

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

प्रकारनिर्देश संरचना VREvent_निवेश_Binding_Load_t
{
	PropertyContainerHandle_t ulAppContainer;
	uint64_t pathMessage;
	uint64_t pathUrl;
	uint64_t pathControllerType;
} VREvent_निवेश_Binding_Load_t;

प्रकारनिर्देश संरचना VREvent_निवेश_Action_Manifest_Load_t
{
	uint64_t path_App_कुंजी;
	uint64_t pathMessage;
	uint64_t pathMessageParam;
	uint64_t pathManifestPath;
} VREvent_निवेश_Action_Manifest_Load_t;

प्रकारनिर्देश संरचना VREvent_SpatialAnchor_t
{
	SpatialAnchorHandle_t unHandle;
} VREvent_SpatialAnchor_t;

प्रकारनिर्देश संरचना VREvent_ProgressUpdate_t
{
	uint64_t ulApplicationPropertyContainer;
	uint64_t pathDevice;
	uint64_t path_निवेश_Source;
	uint64_t pathProgressAction;
	uint64_t pathIcon;
	भिन्न fProgress;
} VREvent_ProgressUpdate_t;

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
	गणना EHDCPError eCode;
} VREvent_HDCPError_t;

प्रकारनिर्देश संरचना RenderModel_ComponentState_t
{
	संरचना HmdMatrix34_t mTrackingToComponentRenderModel;
	संरचना HmdMatrix34_t mTrackingToComponentLocal;
	VRComponentProperties uProperties;
} RenderModel_ComponentState_t;

प्रकारनिर्देश संरचना HiddenAreaMesh_t
{
	संरचना HmdVector2_t * pVertexData; // const struct vr::HmdVector2_t *
	uint32_t un_Triangle_गिनती;
} HiddenAreaMesh_t;

प्रकारनिर्देश संरचना VRControllerAxis_t
{
	भिन्न x;
	भिन्न y;
} VRControllerAxis_t;

प्रकारनिर्देश संरचना VRControllerState_t
{
	uint32_t un_Packet_अंक;
	uint64_t ulButtonPressed;
	uint64_t ulButtonTouched;
	संरचना VRControllerAxis_t rAxis[5]; //struct vr::VRControllerAxis_t[5]
} VRControllerState_t;

प्रकारनिर्देश संरचना CameraVideoStreamFrameHeader_t
{
	गणना EVRTrackedCameraFrameType eFrameType;
	uint32_t nWidth;
	uint32_t nHeight;
	uint32_t nBytesPerPixel;
	uint32_t nFrameSequence;
	संरचना TrackedDevicePose_t trackedDevicePose;
	uint64_t ulFrameExposureTime;
} CameraVideoStreamFrameHeader_t;

प्रकारनिर्देश संरचना Compositor_FrameTiming
{
	uint32_t m_nSize;
	uint32_t m_nFrameIndex;
	uint32_t m_n_अंक_Frame_Presents;
	uint32_t m_n_अंक_Mis_Presented;
	uint32_t m_n_अंक_Dropped_Frames;
	uint32_t m_nReprojectionFlags;
	द्विगुण m_flSystemTimeInSeconds;
	भिन्न m_flPreSubmitGpuMs;
	भिन्न m_flPostSubmitGpuMs;
	भिन्न m_flTotalRenderGpuMs;
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
	भिन्न m_flCompositorUpdateEndMs;
	भिन्न m_flCompositorRenderStartMs;
	TrackedDevicePose_t m_HmdPose;
	uint32_t m_n_अंक_VSyncs_Ready_For_Use;
	uint32_t m_n_अंक_VSyncs_To_First_View;
} Compositor_FrameTiming;

प्रकारनिर्देश संरचना Compositor_BenchmarkResults
{
	भिन्न m_flMegaPixelsPerSecond;
	भिन्न m_flHmdRecommendedMegaPixelsPerSecond;
} Compositor_BenchmarkResults;

प्रकारनिर्देश संरचना DriverDirectMode_FrameTiming
{
	uint32_t m_nSize;
	uint32_t m_n_अंक_Frame_Presents;
	uint32_t m_n_अंक_Mis_Presented;
	uint32_t m_n_अंक_Dropped_Frames;
	uint32_t m_nReprojectionFlags;
} DriverDirectMode_FrameTiming;

प्रकारनिर्देश संरचना ImuSample_t
{
	द्विगुण fSampleTime;
	संरचना HmdVector3d_t vAccel;
	संरचना HmdVector3d_t vGyro;
	uint32_t unOffScaleFlags;
} ImuSample_t;

प्रकारनिर्देश संरचना App_Override_कुंजियाँ_t
{
	वर्ण * pch_कुंजी; // const char *
	वर्ण * pch_मूल्य; // const char *
} App_Override_कुंजियाँ_t;

प्रकारनिर्देश संरचना Compositor_CumulativeStats
{
	uint32_t m_nPid;
	uint32_t m_n_अंक_Frame_Presents;
	uint32_t m_n_अंक_Dropped_Frames;
	uint32_t m_n_अंक_Reprojected_Frames;
	uint32_t m_n_अंक_Frame_Presents_On_Startup;
	uint32_t m_n_अंक_Dropped_Frames_On_Startup;
	uint32_t m_n_अंक_Reprojected_Frames_On_Startup;
	uint32_t m_n_अंक_Loading;
	uint32_t m_n_अंक_Frame_Presents_Loading;
	uint32_t m_n_अंक_Dropped_Frames_Loading;
	uint32_t m_n_अंक_Reprojected_Frames_Loading;
	uint32_t m_n_अंक_Timed_Out;
	uint32_t m_n_अंक_Frame_Presents_Timed_Out;
	uint32_t m_n_अंक_Dropped_Frames_Timed_Out;
	uint32_t m_n_अंक_Reprojected_Frames_Timed_Out;
	uint32_t m_n_अंक_Frame_Submits;
	द्विगुण m_flSumCompositorCPUTimeMS;
	द्विगुण m_flSumCompositorGPUTimeMS;
	द्विगुण m_flSumTargetFrameTimes;
	द्विगुण m_flSumApplicationCPUTimeMS;
	द्विगुण m_flSumApplicationGPUTimeMS;
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
	संरचना HmdVector3_t vNormal;
	संरचना HmdVector2_t vUVs;
	भिन्न fDistance;
} VROverlayIntersectionResults_t;

प्रकारनिर्देश संरचना IntersectionMaskRectangle_t
{
	भिन्न m_fl_शीर्ष_बायाँ_X;
	भिन्न m_fl_शीर्ष_बायाँ_Y;
	भिन्न m_flWidth;
	भिन्न m_flHeight;
} IntersectionMaskRectangle_t;

प्रकारनिर्देश संरचना IntersectionMaskCircle_t
{
	भिन्न m_flCenterX;
	भिन्न m_flCenterY;
	भिन्न m_flRadius;
} IntersectionMaskCircle_t;

प्रकारनिर्देश संरचना VROverlayProjection_t
{
	भिन्न f_बायाँ;
	भिन्न f_दायाँ;
	भिन्न f_शीर्ष;
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
	uint32_t m_uQueueFamilyIndex;
} VRVulkanDevice_t;

प्रकारनिर्देश संरचना VRNativeDevice_t
{
	शून्य * handle; // void *
	गणना EDeviceType eType;
} VRNativeDevice_t;

प्रकारनिर्देश संरचना RenderModel_Vertex_t
{
	संरचना HmdVector3_t vPosition;
	संरचना HmdVector3_t vNormal;
	भिन्न rfTextureCoord[2]; //float[2]
} RenderModel_Vertex_t;

#यदि defined(__linux__) || defined(__APPLE__)
#pragma pack( धकेलो, 4 )
#endif
प्रकारनिर्देश संरचना RenderModel_TextureMap_t
{
	uint16_t unWidth;
	uint16_t unHeight;
	uint8_t * rubTextureMapData; // const uint8_t *
	गणना EVRRenderModelTextureFormat format;
	uint16_t unMipLevels;
} RenderModel_TextureMap_t;

#यदि defined(__linux__) || defined(__APPLE__)
#pragma pack( निकालो )
#endif
#यदि defined(__linux__) || defined(__APPLE__)
#pragma pack( धकेलो, 4 )
#endif
प्रकारनिर्देश संरचना RenderModel_t
{
	संरचना RenderModel_Vertex_t * rVertexData; // const struct vr::RenderModel_Vertex_t *
	uint32_t un_Vertex_गिनती;
	uint16_t * rIndexData; // const uint16_t *
	uint32_t un_Triangle_गिनती;
	TextureID_t diffuseTextureId;
} RenderModel_t;

#यदि defined(__linux__) || defined(__APPLE__)
#pragma pack( निकालो )
#endif
प्रकारनिर्देश संरचना RenderModel_ControllerMode_State_t
{
	bool bScrollWheelVisible;
} RenderModel_ControllerMode_State_t;

प्रकारनिर्देश संरचना NotificationBitmap_t
{
	शून्य * m_pImageData; // void *
	int32_t m_nWidth;
	int32_t m_nHeight;
	int32_t m_nBytesPerPixel;
} NotificationBitmap_t;

प्रकारनिर्देश संरचना CVRSettingHelper
{
	intptr_t m_pSettings; // class vr::IVRSettings *
} CVRSettingHelper;

प्रकारनिर्देश संरचना निवेश_Analog_Action_Data_t
{
	bool bActive;
	VRInput_मूल्य_Handle_t activeOrigin;
	भिन्न x;
	भिन्न y;
	भिन्न z;
	भिन्न deltaX;
	भिन्न deltaY;
	भिन्न deltaZ;
	भिन्न fUpdateTime;
} निवेश_Analog_Action_Data_t;

प्रकारनिर्देश संरचना निवेश_Digital_Action_Data_t
{
	bool bActive;
	VRInput_मूल्य_Handle_t activeOrigin;
	bool bState;
	bool bChanged;
	भिन्न fUpdateTime;
} निवेश_Digital_Action_Data_t;

प्रकारनिर्देश संरचना निवेश_Pose_Action_Data_t
{
	bool bActive;
	VRInput_मूल्य_Handle_t activeOrigin;
	संरचना TrackedDevicePose_t pose;
} निवेश_Pose_Action_Data_t;

प्रकारनिर्देश संरचना निवेश_Skeletal_Action_Data_t
{
	bool bActive;
	VRInput_मूल्य_Handle_t activeOrigin;
} निवेश_Skeletal_Action_Data_t;

प्रकारनिर्देश संरचना निवेश_Origin_Info_t
{
	VRInput_मूल्य_Handle_t devicePath;
	TrackedDeviceIndex_t trackedDeviceIndex;
	वर्ण rchRenderModelComponentName[128]; //char[128]
} निवेश_Origin_Info_t;

प्रकारनिर्देश संरचना निवेश_Binding_Info_t
{
	वर्ण rchDevicePathName[128]; //char[128]
	वर्ण rch_निवेश_Path_Name[128]; //char[128]
	वर्ण rchModeName[128]; //char[128]
	वर्ण rchSlotName[128]; //char[128]
	वर्ण rch_निवेश_Source_Type[32]; //char[32]
} निवेश_Binding_Info_t;

प्रकारनिर्देश संरचना VRActiveActionSet_t
{
	VRActionSetHandle_t ulActionSet;
	VRInput_मूल्य_Handle_t ulRestrictedToDevice;
	VRActionSetHandle_t ulSecondaryActionSet;
	uint32_t unPadding;
	int32_t nPriority;
} VRActiveActionSet_t;

प्रकारनिर्देश संरचना VRSkeletalSummaryData_t
{
	भिन्न flFingerCurl[5]; //float[5]
	भिन्न flFingerSplay[4]; //float[4]
} VRSkeletalSummaryData_t;

प्रकारनिर्देश संरचना SpatialAnchorPose_t
{
	संरचना HmdMatrix34_t mAnchorToAbsoluteTracking;
} SpatialAnchorPose_t;

प्रकारनिर्देश संरचना COpenVRContext
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

प्रकारनिर्देश संरचना PropertyWrite_t
{
	गणना ETrackedDeviceProperty prop;
	गणना EPropertyWriteType writeType;
	गणना ETrackedPropertyError eSetError;
	शून्य * pvBuffer; // void *
	uint32_t unBufferSize;
	PropertyTypeTag_t unTag;
	गणना ETrackedPropertyError eError;
} PropertyWrite_t;

प्रकारनिर्देश संरचना PropertyRead_t
{
	गणना ETrackedDeviceProperty prop;
	शून्य * pvBuffer; // void *
	uint32_t unBufferSize;
	PropertyTypeTag_t unTag;
	uint32_t unRequiredBufferSize;
	गणना ETrackedPropertyError eError;
} PropertyRead_t;

प्रकारनिर्देश संरचना CVRPropertyHelpers
{
	intptr_t m_pProperties; // class vr::IVRProperties *
} CVRPropertyHelpers;

प्रकारनिर्देश संरचना PathWrite_t
{
	PathHandle_t ulPath;
	गणना EPropertyWriteType writeType;
	गणना ETrackedPropertyError eSetError;
	शून्य * pvBuffer; // void *
	uint32_t unBufferSize;
	PropertyTypeTag_t unTag;
	गणना ETrackedPropertyError eError;
	वर्ण * pszPath; // const char *
} PathWrite_t;

प्रकारनिर्देश संरचना PathRead_t
{
	PathHandle_t ulPath;
	शून्य * pvBuffer; // void *
	uint32_t unBufferSize;
	PropertyTypeTag_t unTag;
	uint32_t unRequiredBufferSize;
	गणना ETrackedPropertyError eError;
	वर्ण * pszPath; // const char *
} PathRead_t;


प्रकारनिर्देश सङ्घ
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
	VREvent_निवेश_Binding_Load_t निवेश_Binding;
	VREvent_निवेश_Action_Manifest_Load_t actionManifest;
	VREvent_SpatialAnchor_t spatialAnchor;
} VREvent_Data_t;

#यदि defined(__linux__) || defined(__APPLE__) 
// This structure was originally defined mis-packed on Linux, preserved for 
// compatibility. 
#pragma pack( धकेलो, 4 )
#endif

/** An event posted by the server to all running applications */
संरचना VREvent_t
{
	uint32_t eventType; // EVREventType enum
	TrackedDeviceIndex_t trackedDeviceIndex;
	भिन्न eventAgeSeconds;
	// event data must be the end of the struct as its size is variable
	VREvent_Data_t data;
};

#यदि defined(__linux__) || defined(__APPLE__) 
#pragma pack( निकालो )
#endif


प्रकारनिर्देश सङ्घ
{
	IntersectionMaskRectangle_t m_Rectangle;
	IntersectionMaskCircle_t m_Circle;
} VROverlayIntersectionMaskPrimitive_Data_t;

संरचना VROverlayIntersectionMaskPrimitive_t
{
	EVROverlayIntersectionMaskPrimitiveType m_nPrimitiveType;
	VROverlayIntersectionMaskPrimitive_Data_t m_Primitive;
};


// OpenVR Function Pointer Tables

संरचना VR_IVRSystem_FnTable
{
	शून्य (OPENVR_FNTABLE_CALLTYPE *GetRecommendedRenderTargetSize)(uint32_t * pnWidth, uint32_t * pnHeight);
	संरचना HmdMatrix44_t (OPENVR_FNTABLE_CALLTYPE *GetProjectionMatrix)(EVREye eEye, भिन्न fNearZ, भिन्न fFarZ);
	शून्य (OPENVR_FNTABLE_CALLTYPE *GetProjectionRaw)(EVREye eEye, भिन्न * pf_बायाँ, भिन्न * pf_दायाँ, भिन्न * pf_शीर्ष, भिन्न * pfBottom);
	bool (OPENVR_FNTABLE_CALLTYPE *ComputeDistortion)(EVREye eEye, भिन्न fU, भिन्न fV, संरचना DistortionCoordinates_t * pDistortionCoordinates);
	संरचना HmdMatrix34_t (OPENVR_FNTABLE_CALLTYPE *GetEyeToHeadTransform)(EVREye eEye);
	bool (OPENVR_FNTABLE_CALLTYPE *GetTimeSinceLastVsync)(भिन्न * pfSecondsSinceLastVsync, uint64_t * pulFrameCounter);
	int32_t (OPENVR_FNTABLE_CALLTYPE *GetD3D9AdapterIndex)();
	शून्य (OPENVR_FNTABLE_CALLTYPE *GetDXGIOutputInfo)(int32_t * pnAdapterIndex);
	शून्य (OPENVR_FNTABLE_CALLTYPE *GetOutputDevice)(uint64_t * pnDevice, ETextureType textureType, संरचना VkInstance_T * pInstance);
	bool (OPENVR_FNTABLE_CALLTYPE *IsDisplayOnDesktop)();
	bool (OPENVR_FNTABLE_CALLTYPE *SetDisplayVisibility)(bool bIsVisibleOnDesktop);
	शून्य (OPENVR_FNTABLE_CALLTYPE *GetDeviceToAbsoluteTrackingPose)(ETrackingUniverseOrigin eOrigin, भिन्न fPredictedSecondsToPhotonsFromNow, संरचना TrackedDevicePose_t * pTrackedDevicePoseArray, uint32_t un_Tracked_Device_Pose_Array_गिनती);
	संरचना HmdMatrix34_t (OPENVR_FNTABLE_CALLTYPE *GetSeatedZeroPoseToStandingAbsoluteTrackingPose)();
	संरचना HmdMatrix34_t (OPENVR_FNTABLE_CALLTYPE *GetRawZeroPoseToStandingAbsoluteTrackingPose)();
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetSortedTrackedDeviceIndicesOfClass)(ETrackedDeviceClass eTrackedDeviceClass, TrackedDeviceIndex_t * punTrackedDeviceIndexArray, uint32_t un_Tracked_Device_Index_Array_गिनती, TrackedDeviceIndex_t unRelativeToTrackedDeviceIndex);
	EDeviceActivityLevel (OPENVR_FNTABLE_CALLTYPE *GetTrackedDeviceActivityLevel)(TrackedDeviceIndex_t unDeviceId);
	शून्य (OPENVR_FNTABLE_CALLTYPE *ApplyTransform)(संरचना TrackedDevicePose_t * pOutputPose, संरचना TrackedDevicePose_t * pTrackedDevicePose, संरचना HmdMatrix34_t * pTransform);
	TrackedDeviceIndex_t (OPENVR_FNTABLE_CALLTYPE *GetTrackedDeviceIndexForControllerRole)(ETrackedControllerRole unDeviceType);
	ETrackedControllerRole (OPENVR_FNTABLE_CALLTYPE *GetControllerRoleForTrackedDeviceIndex)(TrackedDeviceIndex_t unDeviceIndex);
	ETrackedDeviceClass (OPENVR_FNTABLE_CALLTYPE *GetTrackedDeviceClass)(TrackedDeviceIndex_t unDeviceIndex);
	bool (OPENVR_FNTABLE_CALLTYPE *IsTrackedDeviceConnected)(TrackedDeviceIndex_t unDeviceIndex);
	bool (OPENVR_FNTABLE_CALLTYPE *GetBoolTrackedDeviceProperty)(TrackedDeviceIndex_t unDeviceIndex, ETrackedDeviceProperty prop, ETrackedPropertyError * pError);
	भिन्न (OPENVR_FNTABLE_CALLTYPE *GetFloatTrackedDeviceProperty)(TrackedDeviceIndex_t unDeviceIndex, ETrackedDeviceProperty prop, ETrackedPropertyError * pError);
	int32_t (OPENVR_FNTABLE_CALLTYPE *GetInt32TrackedDeviceProperty)(TrackedDeviceIndex_t unDeviceIndex, ETrackedDeviceProperty prop, ETrackedPropertyError * pError);
	uint64_t (OPENVR_FNTABLE_CALLTYPE *GetUint64TrackedDeviceProperty)(TrackedDeviceIndex_t unDeviceIndex, ETrackedDeviceProperty prop, ETrackedPropertyError * pError);
	संरचना HmdMatrix34_t (OPENVR_FNTABLE_CALLTYPE *GetMatrix34TrackedDeviceProperty)(TrackedDeviceIndex_t unDeviceIndex, ETrackedDeviceProperty prop, ETrackedPropertyError * pError);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetArrayTrackedDeviceProperty)(TrackedDeviceIndex_t unDeviceIndex, ETrackedDeviceProperty prop, PropertyTypeTag_t propType, शून्य * pBuffer, uint32_t unBufferSize, ETrackedPropertyError * pError);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetStringTrackedDeviceProperty)(TrackedDeviceIndex_t unDeviceIndex, ETrackedDeviceProperty prop, वर्ण * pch_मूल्य, uint32_t unBufferSize, ETrackedPropertyError * pError);
	वर्ण * (OPENVR_FNTABLE_CALLTYPE *GetPropErrorNameFromEnum)(ETrackedPropertyError error);
	bool (OPENVR_FNTABLE_CALLTYPE *PollNextEvent)(संरचना VREvent_t * pEvent, uint32_t uncbVREvent);
	bool (OPENVR_FNTABLE_CALLTYPE *PollNextEventWithPose)(ETrackingUniverseOrigin eOrigin, संरचना VREvent_t * pEvent, uint32_t uncbVREvent, TrackedDevicePose_t * pTrackedDevicePose);
	वर्ण * (OPENVR_FNTABLE_CALLTYPE *GetEventTypeNameFromEnum)(EVREventType eType);
	संरचना HiddenAreaMesh_t (OPENVR_FNTABLE_CALLTYPE *GetHiddenAreaMesh)(EVREye eEye, EHiddenAreaMeshType type);
	bool (OPENVR_FNTABLE_CALLTYPE *GetControllerState)(TrackedDeviceIndex_t unControllerDeviceIndex, VRControllerState_t * pControllerState, uint32_t unControllerStateSize);
	bool (OPENVR_FNTABLE_CALLTYPE *GetControllerStateWithPose)(ETrackingUniverseOrigin eOrigin, TrackedDeviceIndex_t unControllerDeviceIndex, VRControllerState_t * pControllerState, uint32_t unControllerStateSize, संरचना TrackedDevicePose_t * pTrackedDevicePose);
	शून्य (OPENVR_FNTABLE_CALLTYPE *TriggerHapticPulse)(TrackedDeviceIndex_t unControllerDeviceIndex, uint32_t unAxisId, unsigned short usDurationMicroSec);
	वर्ण * (OPENVR_FNTABLE_CALLTYPE *GetButtonIdNameFromEnum)(EVRButtonId eButtonId);
	वर्ण * (OPENVR_FNTABLE_CALLTYPE *GetControllerAxisTypeNameFromEnum)(EVRControllerAxisType eAxisType);
	bool (OPENVR_FNTABLE_CALLTYPE *Is_निवेश_Available)();
	bool (OPENVR_FNTABLE_CALLTYPE *IsSteamVRDrawingControllers)();
	bool (OPENVR_FNTABLE_CALLTYPE *ShouldApplicationPause)();
	bool (OPENVR_FNTABLE_CALLTYPE *ShouldApplicationReduceRenderingWork)();
	EVRFirmwareError (OPENVR_FNTABLE_CALLTYPE *PerformFirmwareUpdate)(TrackedDeviceIndex_t unDeviceIndex);
	शून्य (OPENVR_FNTABLE_CALLTYPE *AcknowledgeQuit_Exiting)();
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetAppContainerFilePaths)(वर्ण * pchBuffer, uint32_t unBufferSize);
	वर्ण * (OPENVR_FNTABLE_CALLTYPE *GetRuntimeVersion)();
};

संरचना VR_IVRExtendedDisplay_FnTable
{
	शून्य (OPENVR_FNTABLE_CALLTYPE *GetWindowBounds)(int32_t * pnX, int32_t * pnY, uint32_t * pnWidth, uint32_t * pnHeight);
	शून्य (OPENVR_FNTABLE_CALLTYPE *GetEyeOutputViewport)(EVREye eEye, uint32_t * pnX, uint32_t * pnY, uint32_t * pnWidth, uint32_t * pnHeight);
	शून्य (OPENVR_FNTABLE_CALLTYPE *GetDXGIOutputInfo)(int32_t * pnAdapterIndex, int32_t * pnAdapterOutputIndex);
};

संरचना VR_IVRTrackedCamera_FnTable
{
	वर्ण * (OPENVR_FNTABLE_CALLTYPE *GetCameraErrorNameFromEnum)(EVRTrackedCameraError eCameraError);
	EVRTrackedCameraError (OPENVR_FNTABLE_CALLTYPE *HasCamera)(TrackedDeviceIndex_t nDeviceIndex, bool * pHasCamera);
	EVRTrackedCameraError (OPENVR_FNTABLE_CALLTYPE *GetCameraFrameSize)(TrackedDeviceIndex_t nDeviceIndex, EVRTrackedCameraFrameType eFrameType, uint32_t * pnWidth, uint32_t * pnHeight, uint32_t * pnFrameBufferSize);
	EVRTrackedCameraError (OPENVR_FNTABLE_CALLTYPE *GetCameraIntrinsics)(TrackedDeviceIndex_t nDeviceIndex, uint32_t nCameraIndex, EVRTrackedCameraFrameType eFrameType, HmdVector2_t * pFocalLength, HmdVector2_t * pCenter);
	EVRTrackedCameraError (OPENVR_FNTABLE_CALLTYPE *GetCameraProjection)(TrackedDeviceIndex_t nDeviceIndex, uint32_t nCameraIndex, EVRTrackedCameraFrameType eFrameType, भिन्न flZNear, भिन्न flZFar, HmdMatrix44_t * pProjection);
	EVRTrackedCameraError (OPENVR_FNTABLE_CALLTYPE *AcquireVideoStreamingService)(TrackedDeviceIndex_t nDeviceIndex, TrackedCameraHandle_t * pHandle);
	EVRTrackedCameraError (OPENVR_FNTABLE_CALLTYPE *ReleaseVideoStreamingService)(TrackedCameraHandle_t hTrackedCamera);
	EVRTrackedCameraError (OPENVR_FNTABLE_CALLTYPE *GetVideoStreamFrameBuffer)(TrackedCameraHandle_t hTrackedCamera, EVRTrackedCameraFrameType eFrameType, शून्य * pFrameBuffer, uint32_t nFrameBufferSize, CameraVideoStreamFrameHeader_t * pFrameHeader, uint32_t nFrameHeaderSize);
	EVRTrackedCameraError (OPENVR_FNTABLE_CALLTYPE *GetVideoStreamTextureSize)(TrackedDeviceIndex_t nDeviceIndex, EVRTrackedCameraFrameType eFrameType, VRTextureBounds_t * pTextureBounds, uint32_t * pnWidth, uint32_t * pnHeight);
	EVRTrackedCameraError (OPENVR_FNTABLE_CALLTYPE *GetVideoStreamTextureD3D11)(TrackedCameraHandle_t hTrackedCamera, EVRTrackedCameraFrameType eFrameType, शून्य * pD3D11DeviceOrResource, शून्य ** ppD3D11ShaderResourceView, CameraVideoStreamFrameHeader_t * pFrameHeader, uint32_t nFrameHeaderSize);
	EVRTrackedCameraError (OPENVR_FNTABLE_CALLTYPE *GetVideoStreamTextureGL)(TrackedCameraHandle_t hTrackedCamera, EVRTrackedCameraFrameType eFrameType, glUInt_t * pglTextureId, CameraVideoStreamFrameHeader_t * pFrameHeader, uint32_t nFrameHeaderSize);
	EVRTrackedCameraError (OPENVR_FNTABLE_CALLTYPE *ReleaseVideoStreamTextureGL)(TrackedCameraHandle_t hTrackedCamera, glUInt_t glTextureId);
	शून्य (OPENVR_FNTABLE_CALLTYPE *SetCameraTrackingSpace)(ETrackingUniverseOrigin eUniverse);
	ETrackingUniverseOrigin (OPENVR_FNTABLE_CALLTYPE *GetCameraTrackingSpace)();
};

संरचना VR_IVRApplications_FnTable
{
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *AddApplicationManifest)(वर्ण * pchApplicationManifestFullPath, bool bTemporary);
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *RemoveApplicationManifest)(वर्ण * pchApplicationManifestFullPath);
	bool (OPENVR_FNTABLE_CALLTYPE *IsApplicationInstalled)(वर्ण * pch_App_कुंजी);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *Get_Application_गिनती)();
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *Get_Application_कुंजी_By_Index)(uint32_t unApplicationIndex, वर्ण * pch_App_कुंजी_Buffer, uint32_t un_App_कुंजी_Buffer_Len);
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *Get_Application_कुंजी_By_Process_Id)(uint32_t unProcessId, वर्ण * pch_App_कुंजी_Buffer, uint32_t un_App_कुंजी_Buffer_Len);
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *LaunchApplication)(वर्ण * pch_App_कुंजी);
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *LaunchTemplateApplication)(वर्ण * pch_Template_App_कुंजी, वर्ण * pch_New_App_कुंजी, संरचना App_Override_कुंजियाँ_t * p_कुंजियाँ, uint32_t un_कुंजियाँ);
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *LaunchApplicationFromMimeType)(वर्ण * pchMimeType, वर्ण * pchArgs);
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *LaunchDashboardOverlay)(वर्ण * pch_App_कुंजी);
	bool (OPENVR_FNTABLE_CALLTYPE *CancelApplicationLaunch)(वर्ण * pch_App_कुंजी);
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *IdentifyApplication)(uint32_t unProcessId, वर्ण * pch_App_कुंजी);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetApplicationProcessId)(वर्ण * pch_App_कुंजी);
	वर्ण * (OPENVR_FNTABLE_CALLTYPE *GetApplicationsErrorNameFromEnum)(EVRApplicationError error);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetApplicationPropertyString)(वर्ण * pch_App_कुंजी, EVRApplicationProperty eProperty, वर्ण * pch_Property_मूल्य_Buffer, uint32_t un_Property_मूल्य_Buffer_Len, EVRApplicationError * peError);
	bool (OPENVR_FNTABLE_CALLTYPE *GetApplicationPropertyBool)(वर्ण * pch_App_कुंजी, EVRApplicationProperty eProperty, EVRApplicationError * peError);
	uint64_t (OPENVR_FNTABLE_CALLTYPE *GetApplicationPropertyUint64)(वर्ण * pch_App_कुंजी, EVRApplicationProperty eProperty, EVRApplicationError * peError);
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *SetApplicationAutoLaunch)(वर्ण * pch_App_कुंजी, bool bAutoLaunch);
	bool (OPENVR_FNTABLE_CALLTYPE *GetApplicationAutoLaunch)(वर्ण * pch_App_कुंजी);
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *SetDefaultApplicationForMimeType)(वर्ण * pch_App_कुंजी, वर्ण * pchMimeType);
	bool (OPENVR_FNTABLE_CALLTYPE *GetDefaultApplicationForMimeType)(वर्ण * pchMimeType, वर्ण * pch_App_कुंजी_Buffer, uint32_t un_App_कुंजी_Buffer_Len);
	bool (OPENVR_FNTABLE_CALLTYPE *GetApplicationSupportedMimeTypes)(वर्ण * pch_App_कुंजी, वर्ण * pchMimeTypesBuffer, uint32_t unMimeTypesBuffer);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetApplicationsThatSupportMimeType)(वर्ण * pchMimeType, वर्ण * pch_App_कुंजियाँ_That_Support_Buffer, uint32_t un_App_कुंजियाँ_That_Support_Buffer);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetApplicationLaunchArguments)(uint32_t unHandle, वर्ण * pchArgs, uint32_t unArgs);
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *GetStartingApplication)(वर्ण * pch_App_कुंजी_Buffer, uint32_t un_App_कुंजी_Buffer_Len);
	EVRSceneApplicationState (OPENVR_FNTABLE_CALLTYPE *GetSceneApplicationState)();
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *PerformApplicationPrelaunchCheck)(वर्ण * pch_App_कुंजी);
	वर्ण * (OPENVR_FNTABLE_CALLTYPE *GetSceneApplicationStateNameFromEnum)(EVRSceneApplicationState state);
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *LaunchInternalProcess)(वर्ण * pch_द्विआधारी_Path, वर्ण * pchArguments, वर्ण * pchWorkingDirectory);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetCurrentSceneProcessId)();
};

संरचना VR_IVRChaperone_FnTable
{
	ChaperoneCalibrationState (OPENVR_FNTABLE_CALLTYPE *GetCalibrationState)();
	bool (OPENVR_FNTABLE_CALLTYPE *GetPlayAreaSize)(भिन्न * pSizeX, भिन्न * pSizeZ);
	bool (OPENVR_FNTABLE_CALLTYPE *GetPlayAreaRect)(संरचना HmdQuad_t * rect);
	शून्य (OPENVR_FNTABLE_CALLTYPE *ReloadInfo)();
	शून्य (OPENVR_FNTABLE_CALLTYPE *SetSceneColor)(संरचना HmdColor_t color);
	शून्य (OPENVR_FNTABLE_CALLTYPE *GetBoundsColor)(संरचना HmdColor_t * pOutputColorArray, पूर्णाङ्क n_अंक_Output_Colors, भिन्न flCollisionBoundsFadeDistance, संरचना HmdColor_t * pOutputCameraColor);
	bool (OPENVR_FNTABLE_CALLTYPE *AreBoundsVisible)();
	शून्य (OPENVR_FNTABLE_CALLTYPE *ForceBoundsVisible)(bool bForce);
	शून्य (OPENVR_FNTABLE_CALLTYPE *ResetZeroPose)(ETrackingUniverseOrigin eTrackingUniverseOrigin);
};

संरचना VR_IVRChaperoneSetup_FnTable
{
	bool (OPENVR_FNTABLE_CALLTYPE *CommitWorkingCopy)(EChaperoneConfigFile configFile);
	शून्य (OPENVR_FNTABLE_CALLTYPE *RevertWorkingCopy)();
	bool (OPENVR_FNTABLE_CALLTYPE *GetWorkingPlayAreaSize)(भिन्न * pSizeX, भिन्न * pSizeZ);
	bool (OPENVR_FNTABLE_CALLTYPE *GetWorkingPlayAreaRect)(संरचना HmdQuad_t * rect);
	bool (OPENVR_FNTABLE_CALLTYPE *GetWorkingCollisionBoundsInfo)(संरचना HmdQuad_t * pQuadsBuffer, uint32_t * pun_Quads_गिनती);
	bool (OPENVR_FNTABLE_CALLTYPE *GetLiveCollisionBoundsInfo)(संरचना HmdQuad_t * pQuadsBuffer, uint32_t * pun_Quads_गिनती);
	bool (OPENVR_FNTABLE_CALLTYPE *GetWorkingSeatedZeroPoseToRawTrackingPose)(संरचना HmdMatrix34_t * pmatSeatedZeroPoseToRawTrackingPose);
	bool (OPENVR_FNTABLE_CALLTYPE *GetWorkingStandingZeroPoseToRawTrackingPose)(संरचना HmdMatrix34_t * pmatStandingZeroPoseToRawTrackingPose);
	शून्य (OPENVR_FNTABLE_CALLTYPE *SetWorkingPlayAreaSize)(भिन्न sizeX, भिन्न sizeZ);
	शून्य (OPENVR_FNTABLE_CALLTYPE *SetWorkingCollisionBoundsInfo)(संरचना HmdQuad_t * pQuadsBuffer, uint32_t un_Quads_गिनती);
	शून्य (OPENVR_FNTABLE_CALLTYPE *SetWorkingPerimeter)(संरचना HmdVector2_t * pPointBuffer, uint32_t un_Point_गिनती);
	शून्य (OPENVR_FNTABLE_CALLTYPE *SetWorkingSeatedZeroPoseToRawTrackingPose)(संरचना HmdMatrix34_t * pMatSeatedZeroPoseToRawTrackingPose);
	शून्य (OPENVR_FNTABLE_CALLTYPE *SetWorkingStandingZeroPoseToRawTrackingPose)(संरचना HmdMatrix34_t * pMatStandingZeroPoseToRawTrackingPose);
	शून्य (OPENVR_FNTABLE_CALLTYPE *ReloadFromDisk)(EChaperoneConfigFile configFile);
	bool (OPENVR_FNTABLE_CALLTYPE *GetLiveSeatedZeroPoseToRawTrackingPose)(संरचना HmdMatrix34_t * pmatSeatedZeroPoseToRawTrackingPose);
	bool (OPENVR_FNTABLE_CALLTYPE *ExportLiveToBuffer)(वर्ण * pBuffer, uint32_t * pnBufferLength);
	bool (OPENVR_FNTABLE_CALLTYPE *ImportFromBufferToWorking)(वर्ण * pBuffer, uint32_t nImportFlags);
	शून्य (OPENVR_FNTABLE_CALLTYPE *ShowWorkingSetPreview)();
	शून्य (OPENVR_FNTABLE_CALLTYPE *HideWorkingSetPreview)();
	शून्य (OPENVR_FNTABLE_CALLTYPE *RoomSetupStarting)();
};

संरचना VR_IVRCompositor_FnTable
{
	शून्य (OPENVR_FNTABLE_CALLTYPE *SetTrackingSpace)(ETrackingUniverseOrigin eOrigin);
	ETrackingUniverseOrigin (OPENVR_FNTABLE_CALLTYPE *GetTrackingSpace)();
	EVRCompositorError (OPENVR_FNTABLE_CALLTYPE *WaitGetPoses)(संरचना TrackedDevicePose_t * pRenderPoseArray, uint32_t un_Render_Pose_Array_गिनती, संरचना TrackedDevicePose_t * pGamePoseArray, uint32_t un_Game_Pose_Array_गिनती);
	EVRCompositorError (OPENVR_FNTABLE_CALLTYPE *GetLastPoses)(संरचना TrackedDevicePose_t * pRenderPoseArray, uint32_t un_Render_Pose_Array_गिनती, संरचना TrackedDevicePose_t * pGamePoseArray, uint32_t un_Game_Pose_Array_गिनती);
	EVRCompositorError (OPENVR_FNTABLE_CALLTYPE *GetLastPoseForTrackedDeviceIndex)(TrackedDeviceIndex_t unDeviceIndex, संरचना TrackedDevicePose_t * pOutputPose, संरचना TrackedDevicePose_t * pOutputGamePose);
	EVRCompositorError (OPENVR_FNTABLE_CALLTYPE *Submit)(EVREye eEye, संरचना Texture_t * pTexture, संरचना VRTextureBounds_t * pBounds, EVRSubmitFlags nSubmitFlags);
	शून्य (OPENVR_FNTABLE_CALLTYPE *ClearLastSubmittedFrame)();
	शून्य (OPENVR_FNTABLE_CALLTYPE *PostPresentHandoff)();
	bool (OPENVR_FNTABLE_CALLTYPE *GetFrameTiming)(संरचना Compositor_FrameTiming * pTiming, uint32_t unFramesAgo);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetFrameTimings)(संरचना Compositor_FrameTiming * pTiming, uint32_t nFrames);
	भिन्न (OPENVR_FNTABLE_CALLTYPE *GetFrameTimeRemaining)();
	शून्य (OPENVR_FNTABLE_CALLTYPE *GetCumulativeStats)(संरचना Compositor_CumulativeStats * pStats, uint32_t nStatsSizeInBytes);
	शून्य (OPENVR_FNTABLE_CALLTYPE *FadeToColor)(भिन्न fSeconds, भिन्न fRed, भिन्न fGreen, भिन्न fBlue, भिन्न fAlpha, bool bBackground);
	संरचना HmdColor_t (OPENVR_FNTABLE_CALLTYPE *GetCurrentFadeColor)(bool bBackground);
	शून्य (OPENVR_FNTABLE_CALLTYPE *FadeGrid)(भिन्न fSeconds, bool bFadeGridIn);
	भिन्न (OPENVR_FNTABLE_CALLTYPE *GetCurrentGridAlpha)();
	EVRCompositorError (OPENVR_FNTABLE_CALLTYPE *SetSkyboxOverride)(संरचना Texture_t * pTextures, uint32_t un_Texture_गिनती);
	शून्य (OPENVR_FNTABLE_CALLTYPE *ClearSkyboxOverride)();
	शून्य (OPENVR_FNTABLE_CALLTYPE *CompositorBringToFront)();
	शून्य (OPENVR_FNTABLE_CALLTYPE *CompositorGoToBack)();
	शून्य (OPENVR_FNTABLE_CALLTYPE *CompositorQuit)();
	bool (OPENVR_FNTABLE_CALLTYPE *IsFullscreen)();
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetCurrentSceneFocusProcess)();
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetLastFrameRenderer)();
	bool (OPENVR_FNTABLE_CALLTYPE *CanRenderScene)();
	शून्य (OPENVR_FNTABLE_CALLTYPE *ShowMirrorWindow)();
	शून्य (OPENVR_FNTABLE_CALLTYPE *HideMirrorWindow)();
	bool (OPENVR_FNTABLE_CALLTYPE *IsMirrorWindowVisible)();
	शून्य (OPENVR_FNTABLE_CALLTYPE *CompositorDumpImages)();
	bool (OPENVR_FNTABLE_CALLTYPE *Should_App_Render_With_निचला_Resources)();
	शून्य (OPENVR_FNTABLE_CALLTYPE *ForceInterleavedReprojectionOn)(bool bOverride);
	शून्य (OPENVR_FNTABLE_CALLTYPE *ForceReconnectProcess)();
	शून्य (OPENVR_FNTABLE_CALLTYPE *SuspendRendering)(bool bSuspend);
	EVRCompositorError (OPENVR_FNTABLE_CALLTYPE *GetMirrorTextureD3D11)(EVREye eEye, शून्य * pD3D11DeviceOrResource, शून्य ** ppD3D11ShaderResourceView);
	शून्य (OPENVR_FNTABLE_CALLTYPE *ReleaseMirrorTextureD3D11)(शून्य * pD3D11ShaderResourceView);
	EVRCompositorError (OPENVR_FNTABLE_CALLTYPE *GetMirrorTextureGL)(EVREye eEye, glUInt_t * pglTextureId, glSharedTextureHandle_t * pglSharedTextureHandle);
	bool (OPENVR_FNTABLE_CALLTYPE *ReleaseSharedGLTexture)(glUInt_t glTextureId, glSharedTextureHandle_t glSharedTextureHandle);
	शून्य (OPENVR_FNTABLE_CALLTYPE *LockGLSharedTextureForAccess)(glSharedTextureHandle_t glSharedTextureHandle);
	शून्य (OPENVR_FNTABLE_CALLTYPE *UnlockGLSharedTextureForAccess)(glSharedTextureHandle_t glSharedTextureHandle);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetVulkanInstanceExtensionsRequired)(वर्ण * pch_मूल्य, uint32_t unBufferSize);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetVulkanDeviceExtensionsRequired)(संरचना VkPhysicalDevice_T * pPhysicalDevice, वर्ण * pch_मूल्य, uint32_t unBufferSize);
	शून्य (OPENVR_FNTABLE_CALLTYPE *SetExplicitTimingMode)(EVRCompositorTimingMode eTimingMode);
	EVRCompositorError (OPENVR_FNTABLE_CALLTYPE *SubmitExplicitTimingData)();
	bool (OPENVR_FNTABLE_CALLTYPE *IsMotionSmoothingEnabled)();
	bool (OPENVR_FNTABLE_CALLTYPE *IsMotionSmoothingSupported)();
	bool (OPENVR_FNTABLE_CALLTYPE *IsCurrentSceneFocusAppLoading)();
	EVRCompositorError (OPENVR_FNTABLE_CALLTYPE *SetStageOverride_Async)(वर्ण * pchRenderModelPath, संरचना HmdMatrix34_t * pTransform, संरचना Compositor_StageRenderSettings * pRenderSettings, uint32_t nSizeOfRenderSettings);
	शून्य (OPENVR_FNTABLE_CALLTYPE *ClearStageOverride)();
	bool (OPENVR_FNTABLE_CALLTYPE *GetCompositorBenchmarkResults)(संरचना Compositor_BenchmarkResults * pBenchmarkResults, uint32_t nSizeOfBenchmarkResults);
	EVRCompositorError (OPENVR_FNTABLE_CALLTYPE *GetLastPosePredictionIDs)(uint32_t * pRenderPosePredictionID, uint32_t * pGamePosePredictionID);
	EVRCompositorError (OPENVR_FNTABLE_CALLTYPE *GetPosesForFrame)(uint32_t unPosePredictionID, संरचना TrackedDevicePose_t * pPoseArray, uint32_t un_Pose_Array_गिनती);
};

संरचना VR_IVROverlay_FnTable
{
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *FindOverlay)(वर्ण * pch_Overlay_कुंजी, VROverlayHandle_t * pOverlayHandle);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *CreateOverlay)(वर्ण * pch_Overlay_कुंजी, वर्ण * pchOverlayName, VROverlayHandle_t * pOverlayHandle);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *DestroyOverlay)(VROverlayHandle_t ulOverlayHandle);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *Get_Overlay_कुंजी)(VROverlayHandle_t ulOverlayHandle, वर्ण * pch_मूल्य, uint32_t unBufferSize, EVROverlayError * pError);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetOverlayName)(VROverlayHandle_t ulOverlayHandle, वर्ण * pch_मूल्य, uint32_t unBufferSize, EVROverlayError * pError);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *SetOverlayName)(VROverlayHandle_t ulOverlayHandle, वर्ण * pchName);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayImageData)(VROverlayHandle_t ulOverlayHandle, शून्य * pvBuffer, uint32_t unBufferSize, uint32_t * punWidth, uint32_t * punHeight);
	वर्ण * (OPENVR_FNTABLE_CALLTYPE *GetOverlayErrorNameFromEnum)(EVROverlayError error);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *SetOverlayRenderingPid)(VROverlayHandle_t ulOverlayHandle, uint32_t unPID);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetOverlayRenderingPid)(VROverlayHandle_t ulOverlayHandle);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *SetOverlayFlag)(VROverlayHandle_t ulOverlayHandle, VROverlayFlags eOverlayFlag, bool bEnabled);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayFlag)(VROverlayHandle_t ulOverlayHandle, VROverlayFlags eOverlayFlag, bool * pbEnabled);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayFlags)(VROverlayHandle_t ulOverlayHandle, uint32_t * pFlags);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *SetOverlayColor)(VROverlayHandle_t ulOverlayHandle, भिन्न fRed, भिन्न fGreen, भिन्न fBlue);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayColor)(VROverlayHandle_t ulOverlayHandle, भिन्न * pfRed, भिन्न * pfGreen, भिन्न * pfBlue);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *SetOverlayAlpha)(VROverlayHandle_t ulOverlayHandle, भिन्न fAlpha);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayAlpha)(VROverlayHandle_t ulOverlayHandle, भिन्न * pfAlpha);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *SetOverlayTexelAspect)(VROverlayHandle_t ulOverlayHandle, भिन्न fTexelAspect);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayTexelAspect)(VROverlayHandle_t ulOverlayHandle, भिन्न * pfTexelAspect);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *SetOverlaySortOrder)(VROverlayHandle_t ulOverlayHandle, uint32_t unSortOrder);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlaySortOrder)(VROverlayHandle_t ulOverlayHandle, uint32_t * punSortOrder);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *SetOverlayWidthInMeters)(VROverlayHandle_t ulOverlayHandle, भिन्न fWidthInMeters);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayWidthInMeters)(VROverlayHandle_t ulOverlayHandle, भिन्न * pfWidthInMeters);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *SetOverlayCurvature)(VROverlayHandle_t ulOverlayHandle, भिन्न fCurvature);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayCurvature)(VROverlayHandle_t ulOverlayHandle, भिन्न * pfCurvature);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *SetOverlayPreCurvePitch)(VROverlayHandle_t ulOverlayHandle, भिन्न fRadians);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayPreCurvePitch)(VROverlayHandle_t ulOverlayHandle, भिन्न * pfRadians);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *SetOverlayTextureColorSpace)(VROverlayHandle_t ulOverlayHandle, EColorSpace eTextureColorSpace);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayTextureColorSpace)(VROverlayHandle_t ulOverlayHandle, EColorSpace * peTextureColorSpace);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *SetOverlayTextureBounds)(VROverlayHandle_t ulOverlayHandle, संरचना VRTextureBounds_t * pOverlayTextureBounds);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayTextureBounds)(VROverlayHandle_t ulOverlayHandle, संरचना VRTextureBounds_t * pOverlayTextureBounds);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayTransformType)(VROverlayHandle_t ulOverlayHandle, VROverlayTransformType * peTransformType);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *SetOverlayTransformAbsolute)(VROverlayHandle_t ulOverlayHandle, ETrackingUniverseOrigin eTrackingOrigin, संरचना HmdMatrix34_t * pmatTrackingOriginToOverlayTransform);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayTransformAbsolute)(VROverlayHandle_t ulOverlayHandle, ETrackingUniverseOrigin * peTrackingOrigin, संरचना HmdMatrix34_t * pmatTrackingOriginToOverlayTransform);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *SetOverlayTransformTrackedDeviceRelative)(VROverlayHandle_t ulOverlayHandle, TrackedDeviceIndex_t unTrackedDevice, संरचना HmdMatrix34_t * pmatTrackedDeviceToOverlayTransform);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayTransformTrackedDeviceRelative)(VROverlayHandle_t ulOverlayHandle, TrackedDeviceIndex_t * punTrackedDevice, संरचना HmdMatrix34_t * pmatTrackedDeviceToOverlayTransform);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *SetOverlayTransformTrackedDeviceComponent)(VROverlayHandle_t ulOverlayHandle, TrackedDeviceIndex_t unDeviceIndex, वर्ण * pchComponentName);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayTransformTrackedDeviceComponent)(VROverlayHandle_t ulOverlayHandle, TrackedDeviceIndex_t * punDeviceIndex, वर्ण * pchComponentName, uint32_t unComponentNameSize);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayTransformOverlayRelative)(VROverlayHandle_t ulOverlayHandle, VROverlayHandle_t * ulOverlayHandleParent, संरचना HmdMatrix34_t * pmatParentOverlayToOverlayTransform);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *SetOverlayTransformOverlayRelative)(VROverlayHandle_t ulOverlayHandle, VROverlayHandle_t ulOverlayHandleParent, संरचना HmdMatrix34_t * pmatParentOverlayToOverlayTransform);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *SetOverlayTransformCursor)(VROverlayHandle_t ulCursorOverlayHandle, संरचना HmdVector2_t * pvHotspot);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayTransformCursor)(VROverlayHandle_t ulOverlayHandle, संरचना HmdVector2_t * pvHotspot);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *SetOverlayTransformProjection)(VROverlayHandle_t ulOverlayHandle, ETrackingUniverseOrigin eTrackingOrigin, संरचना HmdMatrix34_t * pmatTrackingOriginToOverlayTransform, संरचना VROverlayProjection_t * pProjection, EVREye eEye);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *ShowOverlay)(VROverlayHandle_t ulOverlayHandle);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *HideOverlay)(VROverlayHandle_t ulOverlayHandle);
	bool (OPENVR_FNTABLE_CALLTYPE *IsOverlayVisible)(VROverlayHandle_t ulOverlayHandle);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetTransformForOverlayCoordinates)(VROverlayHandle_t ulOverlayHandle, ETrackingUniverseOrigin eTrackingOrigin, संरचना HmdVector2_t coordinatesInOverlay, संरचना HmdMatrix34_t * pmatTransform);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *WaitFrameSync)(uint32_t nTimeoutMs);
	bool (OPENVR_FNTABLE_CALLTYPE *PollNextOverlayEvent)(VROverlayHandle_t ulOverlayHandle, संरचना VREvent_t * pEvent, uint32_t uncbVREvent);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *Get_Overlay_निवेश_Method)(VROverlayHandle_t ulOverlayHandle, VROverlay_निवेश_Method * pe_निवेश_Method);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *Set_Overlay_निवेश_Method)(VROverlayHandle_t ulOverlayHandle, VROverlay_निवेश_Method e_निवेश_Method);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayMouseScale)(VROverlayHandle_t ulOverlayHandle, संरचना HmdVector2_t * pvecMouseScale);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *SetOverlayMouseScale)(VROverlayHandle_t ulOverlayHandle, संरचना HmdVector2_t * pvecMouseScale);
	bool (OPENVR_FNTABLE_CALLTYPE *ComputeOverlayIntersection)(VROverlayHandle_t ulOverlayHandle, संरचना VROverlayIntersectionParams_t * pParams, संरचना VROverlayIntersectionResults_t * pResults);
	bool (OPENVR_FNTABLE_CALLTYPE *IsHoverTargetOverlay)(VROverlayHandle_t ulOverlayHandle);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *SetOverlayIntersectionMask)(VROverlayHandle_t ulOverlayHandle, संरचना VROverlayIntersectionMaskPrimitive_t * pMaskPrimitives, uint32_t un_अंक_Mask_Primitives, uint32_t unPrimitiveSize);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *TriggerLaserMouseHapticVibration)(VROverlayHandle_t ulOverlayHandle, भिन्न fDurationSeconds, भिन्न fFrequency, भिन्न fAmplitude);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *SetOverlayCursor)(VROverlayHandle_t ulOverlayHandle, VROverlayHandle_t ulCursorHandle);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *SetOverlayCursorPositionOverride)(VROverlayHandle_t ulOverlayHandle, संरचना HmdVector2_t * pvCursor);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *ClearOverlayCursorPositionOverride)(VROverlayHandle_t ulOverlayHandle);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *SetOverlayTexture)(VROverlayHandle_t ulOverlayHandle, संरचना Texture_t * pTexture);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *ClearOverlayTexture)(VROverlayHandle_t ulOverlayHandle);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *SetOverlayRaw)(VROverlayHandle_t ulOverlayHandle, शून्य * pvBuffer, uint32_t unWidth, uint32_t unHeight, uint32_t unBytesPerPixel);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *SetOverlayFromFile)(VROverlayHandle_t ulOverlayHandle, वर्ण * pchFilePath);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayTexture)(VROverlayHandle_t ulOverlayHandle, शून्य ** pNativeTextureHandle, शून्य * pNativeTextureRef, uint32_t * pWidth, uint32_t * pHeight, uint32_t * pNativeFormat, ETextureType * pAPIType, EColorSpace * pColorSpace, संरचना VRTextureBounds_t * pTextureBounds);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *ReleaseNativeOverlayHandle)(VROverlayHandle_t ulOverlayHandle, शून्य * pNativeTextureHandle);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayTextureSize)(VROverlayHandle_t ulOverlayHandle, uint32_t * pWidth, uint32_t * pHeight);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *CreateDashboardOverlay)(वर्ण * pch_Overlay_कुंजी, वर्ण * pchOverlayFriendlyName, VROverlayHandle_t * pMainHandle, VROverlayHandle_t * pThumbnailHandle);
	bool (OPENVR_FNTABLE_CALLTYPE *IsDashboardVisible)();
	bool (OPENVR_FNTABLE_CALLTYPE *IsActiveDashboardOverlay)(VROverlayHandle_t ulOverlayHandle);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *SetDashboardOverlaySceneProcess)(VROverlayHandle_t ulOverlayHandle, uint32_t unProcessId);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetDashboardOverlaySceneProcess)(VROverlayHandle_t ulOverlayHandle, uint32_t * punProcessId);
	शून्य (OPENVR_FNTABLE_CALLTYPE *ShowDashboard)(वर्ण * pchOverlayToShow);
	TrackedDeviceIndex_t (OPENVR_FNTABLE_CALLTYPE *GetPrimaryDashboardDevice)();
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *ShowKeyboard)(EGamepad_Text_निवेश_Mode e_निवेश_Mode, EGamepad_Text_निवेश_पंक्ति_Mode e_पंक्ति_निवेश_Mode, uint32_t unFlags, वर्ण * pchDescription, uint32_t unCharMax, वर्ण * pchExistingText, uint64_t u_User_मूल्य);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *ShowKeyboardForOverlay)(VROverlayHandle_t ulOverlayHandle, EGamepad_Text_निवेश_Mode e_निवेश_Mode, EGamepad_Text_निवेश_पंक्ति_Mode e_पंक्ति_निवेश_Mode, uint32_t unFlags, वर्ण * pchDescription, uint32_t unCharMax, वर्ण * pchExistingText, uint64_t u_User_मूल्य);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetKeyboardText)(वर्ण * pchText, uint32_t cchText);
	शून्य (OPENVR_FNTABLE_CALLTYPE *HideKeyboard)();
	शून्य (OPENVR_FNTABLE_CALLTYPE *SetKeyboardTransformAbsolute)(ETrackingUniverseOrigin eTrackingOrigin, संरचना HmdMatrix34_t * pmatTrackingOriginToKeyboardTransform);
	शून्य (OPENVR_FNTABLE_CALLTYPE *SetKeyboardPositionForOverlay)(VROverlayHandle_t ulOverlayHandle, संरचना HmdRect2_t avoidRect);
	VRMessageOverlayResponse (OPENVR_FNTABLE_CALLTYPE *ShowMessageOverlay)(वर्ण * pchText, वर्ण * pchCaption, वर्ण * pchButton0Text, वर्ण * pchButton1Text, वर्ण * pchButton2Text, वर्ण * pchButton3Text);
	शून्य (OPENVR_FNTABLE_CALLTYPE *CloseMessageOverlay)();
};

संरचना VR_IVROverlayView_FnTable
{
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *AcquireOverlayView)(VROverlayHandle_t ulOverlayHandle, संरचना VRNativeDevice_t * pNativeDevice, संरचना VROverlayView_t * pOverlayView, uint32_t unOverlayViewSize);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *ReleaseOverlayView)(संरचना VROverlayView_t * pOverlayView);
	शून्य (OPENVR_FNTABLE_CALLTYPE *PostOverlayEvent)(VROverlayHandle_t ulOverlayHandle, संरचना VREvent_t * pvrEvent);
	bool (OPENVR_FNTABLE_CALLTYPE *IsViewingPermitted)(VROverlayHandle_t ulOverlayHandle);
};

संरचना VR_IVRHeadsetView_FnTable
{
	शून्य (OPENVR_FNTABLE_CALLTYPE *SetHeadsetViewSize)(uint32_t nWidth, uint32_t nHeight);
	शून्य (OPENVR_FNTABLE_CALLTYPE *GetHeadsetViewSize)(uint32_t * pnWidth, uint32_t * pnHeight);
	शून्य (OPENVR_FNTABLE_CALLTYPE *SetHeadsetViewMode)(HeadsetViewMode_t eHeadsetViewMode);
	HeadsetViewMode_t (OPENVR_FNTABLE_CALLTYPE *GetHeadsetViewMode)();
	शून्य (OPENVR_FNTABLE_CALLTYPE *SetHeadsetViewCropped)(bool bCropped);
	bool (OPENVR_FNTABLE_CALLTYPE *GetHeadsetViewCropped)();
	भिन्न (OPENVR_FNTABLE_CALLTYPE *GetHeadsetViewAspectRatio)();
	शून्य (OPENVR_FNTABLE_CALLTYPE *SetHeadsetViewBlendRange)(भिन्न flStartPct, भिन्न flEndPct);
	शून्य (OPENVR_FNTABLE_CALLTYPE *GetHeadsetViewBlendRange)(भिन्न * pStartPct, भिन्न * pEndPct);
};

संरचना VR_IVRRenderModels_FnTable
{
	EVRRenderModelError (OPENVR_FNTABLE_CALLTYPE *LoadRenderModel_Async)(वर्ण * pchRenderModelName, संरचना RenderModel_t ** ppRenderModel);
	शून्य (OPENVR_FNTABLE_CALLTYPE *FreeRenderModel)(संरचना RenderModel_t * pRenderModel);
	EVRRenderModelError (OPENVR_FNTABLE_CALLTYPE *LoadTexture_Async)(TextureID_t textureId, संरचना RenderModel_TextureMap_t ** ppTexture);
	शून्य (OPENVR_FNTABLE_CALLTYPE *FreeTexture)(संरचना RenderModel_TextureMap_t * pTexture);
	EVRRenderModelError (OPENVR_FNTABLE_CALLTYPE *LoadTextureD3D11_Async)(TextureID_t textureId, शून्य * pD3D11Device, शून्य ** ppD3D11Texture2D);
	EVRRenderModelError (OPENVR_FNTABLE_CALLTYPE *LoadIntoTextureD3D11_Async)(TextureID_t textureId, शून्य * pDstTexture);
	शून्य (OPENVR_FNTABLE_CALLTYPE *FreeTextureD3D11)(शून्य * pD3D11Texture2D);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetRenderModelName)(uint32_t unRenderModelIndex, वर्ण * pchRenderModelName, uint32_t unRenderModelNameLen);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *Get_Render_Model_गिनती)();
	uint32_t (OPENVR_FNTABLE_CALLTYPE *Get_Component_गिनती)(वर्ण * pchRenderModelName);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetComponentName)(वर्ण * pchRenderModelName, uint32_t unComponentIndex, वर्ण * pchComponentName, uint32_t unComponentNameLen);
	uint64_t (OPENVR_FNTABLE_CALLTYPE *GetComponentButtonMask)(वर्ण * pchRenderModelName, वर्ण * pchComponentName);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetComponentRenderModelName)(वर्ण * pchRenderModelName, वर्ण * pchComponentName, वर्ण * pchComponentRenderModelName, uint32_t unComponentRenderModelNameLen);
	bool (OPENVR_FNTABLE_CALLTYPE *GetComponentStateForDevicePath)(वर्ण * pchRenderModelName, वर्ण * pchComponentName, VRInput_मूल्य_Handle_t devicePath, RenderModel_ControllerMode_State_t * pState, RenderModel_ComponentState_t * pComponentState);
	bool (OPENVR_FNTABLE_CALLTYPE *GetComponentState)(वर्ण * pchRenderModelName, वर्ण * pchComponentName, VRControllerState_t * pControllerState, संरचना RenderModel_ControllerMode_State_t * pState, संरचना RenderModel_ComponentState_t * pComponentState);
	bool (OPENVR_FNTABLE_CALLTYPE *RenderModelHasComponent)(वर्ण * pchRenderModelName, वर्ण * pchComponentName);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetRenderModelThumbnailURL)(वर्ण * pchRenderModelName, वर्ण * pchThumbnailURL, uint32_t unThumbnailURLLen, EVRRenderModelError * peError);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetRenderModelOriginalPath)(वर्ण * pchRenderModelName, वर्ण * pchOriginalPath, uint32_t unOriginalPathLen, EVRRenderModelError * peError);
	वर्ण * (OPENVR_FNTABLE_CALLTYPE *GetRenderModelErrorNameFromEnum)(EVRRenderModelError error);
};

संरचना VR_IVRNotifications_FnTable
{
	EVRNotificationError (OPENVR_FNTABLE_CALLTYPE *CreateNotification)(VROverlayHandle_t ulOverlayHandle, uint64_t ul_User_मूल्य, EVRNotificationType type, वर्ण * pchText, EVRNotificationStyle style, संरचना NotificationBitmap_t * pImage, VRNotificationId * pNotificationId);
	EVRNotificationError (OPENVR_FNTABLE_CALLTYPE *RemoveNotification)(VRNotificationId notificationId);
};

संरचना VR_IVRSettings_FnTable
{
	वर्ण * (OPENVR_FNTABLE_CALLTYPE *GetSettingsErrorNameFromEnum)(EVRSettingsError eError);
	शून्य (OPENVR_FNTABLE_CALLTYPE *SetBool)(वर्ण * pchSection, वर्ण * pch_Settings_कुंजी, bool b_मूल्य, EVRSettingsError * peError);
	शून्य (OPENVR_FNTABLE_CALLTYPE *SetInt32)(वर्ण * pchSection, वर्ण * pch_Settings_कुंजी, int32_t n_मूल्य, EVRSettingsError * peError);
	शून्य (OPENVR_FNTABLE_CALLTYPE *SetFloat)(वर्ण * pchSection, वर्ण * pch_Settings_कुंजी, भिन्न fl_मूल्य, EVRSettingsError * peError);
	शून्य (OPENVR_FNTABLE_CALLTYPE *SetString)(वर्ण * pchSection, वर्ण * pch_Settings_कुंजी, वर्ण * pch_मूल्य, EVRSettingsError * peError);
	bool (OPENVR_FNTABLE_CALLTYPE *GetBool)(वर्ण * pchSection, वर्ण * pch_Settings_कुंजी, EVRSettingsError * peError);
	int32_t (OPENVR_FNTABLE_CALLTYPE *GetInt32)(वर्ण * pchSection, वर्ण * pch_Settings_कुंजी, EVRSettingsError * peError);
	भिन्न (OPENVR_FNTABLE_CALLTYPE *GetFloat)(वर्ण * pchSection, वर्ण * pch_Settings_कुंजी, EVRSettingsError * peError);
	शून्य (OPENVR_FNTABLE_CALLTYPE *GetString)(वर्ण * pchSection, वर्ण * pch_Settings_कुंजी, वर्ण * pch_मूल्य, uint32_t un_मूल्य_Len, EVRSettingsError * peError);
	शून्य (OPENVR_FNTABLE_CALLTYPE *RemoveSection)(वर्ण * pchSection, EVRSettingsError * peError);
	शून्य (OPENVR_FNTABLE_CALLTYPE *Remove_कुंजी_In_Section)(वर्ण * pchSection, वर्ण * pch_Settings_कुंजी, EVRSettingsError * peError);
};

संरचना VR_IVRScreenshots_FnTable
{
	EVRScreenshotError (OPENVR_FNTABLE_CALLTYPE *RequestScreenshot)(ScreenshotHandle_t * pOutScreenshotHandle, EVRScreenshotType type, वर्ण * pchPreviewFilename, वर्ण * pchVRFilename);
	EVRScreenshotError (OPENVR_FNTABLE_CALLTYPE *HookScreenshot)(EVRScreenshotType * pSupportedTypes, पूर्णाङ्क अंक_Types);
	EVRScreenshotType (OPENVR_FNTABLE_CALLTYPE *GetScreenshotPropertyType)(ScreenshotHandle_t screenshotHandle, EVRScreenshotError * pError);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetScreenshotPropertyFilename)(ScreenshotHandle_t screenshotHandle, EVRScreenshotPropertyFilenames filenameType, वर्ण * pchFilename, uint32_t cchFilename, EVRScreenshotError * pError);
	EVRScreenshotError (OPENVR_FNTABLE_CALLTYPE *UpdateScreenshotProgress)(ScreenshotHandle_t screenshotHandle, भिन्न flProgress);
	EVRScreenshotError (OPENVR_FNTABLE_CALLTYPE *TakeStereoScreenshot)(ScreenshotHandle_t * pOutScreenshotHandle, वर्ण * pchPreviewFilename, वर्ण * pchVRFilename);
	EVRScreenshotError (OPENVR_FNTABLE_CALLTYPE *SubmitScreenshot)(ScreenshotHandle_t screenshotHandle, EVRScreenshotType type, वर्ण * pchSourcePreviewFilename, वर्ण * pchSourceVRFilename);
};

संरचना VR_IVRResources_FnTable
{
	uint32_t (OPENVR_FNTABLE_CALLTYPE *LoadSharedResource)(वर्ण * pchResourceName, वर्ण * pchBuffer, uint32_t unBufferLen);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetResourceFullPath)(वर्ण * pchResourceName, वर्ण * pchResourceTypeDirectory, वर्ण * pchPathBuffer, uint32_t unBufferLen);
};

संरचना VR_IVRDriverManager_FnTable
{
	uint32_t (OPENVR_FNTABLE_CALLTYPE *Get_Driver_गिनती)();
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetDriverName)(DriverId_t nDriver, वर्ण * pch_मूल्य, uint32_t unBufferSize);
	DriverHandle_t (OPENVR_FNTABLE_CALLTYPE *GetDriverHandle)(वर्ण * pchDriverName);
	bool (OPENVR_FNTABLE_CALLTYPE *IsEnabled)(DriverId_t nDriver);
};

संरचना VR_IVRInput_FnTable
{
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *SetActionManifestPath)(वर्ण * pchActionManifestPath);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetActionSetHandle)(वर्ण * pchActionSetName, VRActionSetHandle_t * pHandle);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetActionHandle)(वर्ण * pchActionName, VRActionHandle_t * pHandle);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *Get_निवेश_Source_Handle)(वर्ण * pch_निवेश_Source_Path, VRInput_मूल्य_Handle_t * pHandle);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *UpdateActionState)(संरचना VRActiveActionSet_t * pSets, uint32_t unSizeOfVRSelectedActionSet_t, uint32_t un_Set_गिनती);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetDigitalActionData)(VRActionHandle_t action, संरचना निवेश_Digital_Action_Data_t * pActionData, uint32_t unActionDataSize, VRInput_मूल्य_Handle_t ulRestrictToDevice);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetAnalogActionData)(VRActionHandle_t action, संरचना निवेश_Analog_Action_Data_t * pActionData, uint32_t unActionDataSize, VRInput_मूल्य_Handle_t ulRestrictToDevice);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetPoseActionDataRelativeToNow)(VRActionHandle_t action, ETrackingUniverseOrigin eOrigin, भिन्न fPredictedSecondsFromNow, संरचना निवेश_Pose_Action_Data_t * pActionData, uint32_t unActionDataSize, VRInput_मूल्य_Handle_t ulRestrictToDevice);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetPoseActionDataForNextFrame)(VRActionHandle_t action, ETrackingUniverseOrigin eOrigin, संरचना निवेश_Pose_Action_Data_t * pActionData, uint32_t unActionDataSize, VRInput_मूल्य_Handle_t ulRestrictToDevice);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetSkeletalActionData)(VRActionHandle_t action, संरचना निवेश_Skeletal_Action_Data_t * pActionData, uint32_t unActionDataSize);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetDominantHand)(ETrackedControllerRole * peDominantHand);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *SetDominantHand)(ETrackedControllerRole eDominantHand);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *Get_Bone_गिनती)(VRActionHandle_t action, uint32_t * p_Bone_गिनती);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetBoneHierarchy)(VRActionHandle_t action, BoneIndex_t * pParentIndices, uint32_t un_Index_Aray_गिनती);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetBoneName)(VRActionHandle_t action, BoneIndex_t nBoneIndex, वर्ण * pchBoneName, uint32_t unNameBufferSize);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetSkeletalReferenceTransforms)(VRActionHandle_t action, EVRSkeletalTransformSpace eTransformSpace, EVRSkeletalReferencePose eReferencePose, संरचना VRBoneTransform_t * pTransformArray, uint32_t un_Transform_Array_गिनती);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetSkeletalTrackingLevel)(VRActionHandle_t action, EVRSkeletalTrackingLevel * pSkeletalTrackingLevel);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetSkeletalBoneData)(VRActionHandle_t action, EVRSkeletalTransformSpace eTransformSpace, EVRSkeletalMotionRange eMotionRange, संरचना VRBoneTransform_t * pTransformArray, uint32_t un_Transform_Array_गिनती);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetSkeletalSummaryData)(VRActionHandle_t action, EVRSummaryType eSummaryType, संरचना VRSkeletalSummaryData_t * pSkeletalSummaryData);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetSkeletalBoneDataCompressed)(VRActionHandle_t action, EVRSkeletalMotionRange eMotionRange, शून्य * pvCompressedData, uint32_t unCompressedSize, uint32_t * punRequiredCompressedSize);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *DecompressSkeletalBoneData)(शून्य * pvCompressedBuffer, uint32_t unCompressedBufferSize, EVRSkeletalTransformSpace eTransformSpace, संरचना VRBoneTransform_t * pTransformArray, uint32_t un_Transform_Array_गिनती);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *TriggerHapticVibrationAction)(VRActionHandle_t action, भिन्न fStartSecondsFromNow, भिन्न fDurationSeconds, भिन्न fFrequency, भिन्न fAmplitude, VRInput_मूल्य_Handle_t ulRestrictToDevice);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetActionOrigins)(VRActionSetHandle_t actionSetHandle, VRActionHandle_t digitalActionHandle, VRInput_मूल्य_Handle_t * originsOut, uint32_t origin_Out_गिनती);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetOriginLocalizedName)(VRInput_मूल्य_Handle_t origin, वर्ण * pchNameArray, uint32_t unNameArraySize, int32_t unStringSectionsToInclude);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetOriginTrackedDeviceInfo)(VRInput_मूल्य_Handle_t origin, संरचना निवेश_Origin_Info_t * pOriginInfo, uint32_t unOriginInfoSize);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetActionBindingInfo)(VRActionHandle_t action, संरचना निवेश_Binding_Info_t * pOriginInfo, uint32_t unBindingInfoSize, uint32_t un_Binding_Info_गिनती, uint32_t * pun_Returned_Binding_Info_गिनती);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *ShowActionOrigins)(VRActionSetHandle_t actionSetHandle, VRActionHandle_t ulActionHandle);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *ShowBindingsForActionSet)(संरचना VRActiveActionSet_t * pSets, uint32_t unSizeOfVRSelectedActionSet_t, uint32_t un_Set_गिनती, VRInput_मूल्य_Handle_t originToHighlight);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetComponentStateForBinding)(वर्ण * pchRenderModelName, वर्ण * pchComponentName, संरचना निवेश_Binding_Info_t * pOriginInfo, uint32_t unBindingInfoSize, uint32_t un_Binding_Info_गिनती, RenderModel_ComponentState_t * pComponentState);
	bool (OPENVR_FNTABLE_CALLTYPE *Is_Using_Legacy_निवेश)();
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *OpenBindingUI)(वर्ण * pch_App_कुंजी, VRActionSetHandle_t ulActionSetHandle, VRInput_मूल्य_Handle_t ulDeviceHandle, bool bShowOnDesktop);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetBindingVariant)(VRInput_मूल्य_Handle_t ulDevicePath, वर्ण * pchVariantArray, uint32_t unVariantArraySize);
};

संरचना VR_IVRIOBuffer_FnTable
{
	EIOBufferError (OPENVR_FNTABLE_CALLTYPE *Open)(वर्ण * pchPath, EIOBufferMode mode, uint32_t unElementSize, uint32_t unElements, IOBufferHandle_t * pulBuffer);
	EIOBufferError (OPENVR_FNTABLE_CALLTYPE *Close)(IOBufferHandle_t ulBuffer);
	EIOBufferError (OPENVR_FNTABLE_CALLTYPE *Read)(IOBufferHandle_t ulBuffer, शून्य * pDst, uint32_t unBytes, uint32_t * punRead);
	EIOBufferError (OPENVR_FNTABLE_CALLTYPE *Write)(IOBufferHandle_t ulBuffer, शून्य * pSrc, uint32_t unBytes);
	PropertyContainerHandle_t (OPENVR_FNTABLE_CALLTYPE *PropertyContainer)(IOBufferHandle_t ulBuffer);
	bool (OPENVR_FNTABLE_CALLTYPE *HasReaders)(IOBufferHandle_t ulBuffer);
};

संरचना VR_IVRSpatialAnchors_FnTable
{
	EVRSpatialAnchorError (OPENVR_FNTABLE_CALLTYPE *CreateSpatialAnchorFromDescriptor)(वर्ण * pchDescriptor, SpatialAnchorHandle_t * pHandleOut);
	EVRSpatialAnchorError (OPENVR_FNTABLE_CALLTYPE *CreateSpatialAnchorFromPose)(TrackedDeviceIndex_t unDeviceIndex, ETrackingUniverseOrigin eOrigin, संरचना SpatialAnchorPose_t * pPose, SpatialAnchorHandle_t * pHandleOut);
	EVRSpatialAnchorError (OPENVR_FNTABLE_CALLTYPE *GetSpatialAnchorPose)(SpatialAnchorHandle_t unHandle, ETrackingUniverseOrigin eOrigin, संरचना SpatialAnchorPose_t * pPoseOut);
	EVRSpatialAnchorError (OPENVR_FNTABLE_CALLTYPE *GetSpatialAnchorDescriptor)(SpatialAnchorHandle_t unHandle, वर्ण * pchDescriptorOut, uint32_t * punDescriptorBufferLenInOut);
};

संरचना VR_IVRDebug_FnTable
{
	EVRDebugError (OPENVR_FNTABLE_CALLTYPE *EmitVrProfilerEvent)(वर्ण * pchMessage);
	EVRDebugError (OPENVR_FNTABLE_CALLTYPE *BeginVrProfilerEvent)(VrProfilerEventHandle_t * pHandleOut);
	EVRDebugError (OPENVR_FNTABLE_CALLTYPE *FinishVrProfilerEvent)(VrProfilerEventHandle_t hHandle, वर्ण * pchMessage);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *DriverDebugRequest)(TrackedDeviceIndex_t unDeviceIndex, वर्ण * pchRequest, वर्ण * pchResponseBuffer, uint32_t unResponseBufferSize);
};

संरचना VR_IVRProperties_FnTable
{
	ETrackedPropertyError (OPENVR_FNTABLE_CALLTYPE *ReadPropertyBatch)(PropertyContainerHandle_t ulContainerHandle, संरचना PropertyRead_t * pBatch, uint32_t un_Batch_Entry_गिनती);
	ETrackedPropertyError (OPENVR_FNTABLE_CALLTYPE *WritePropertyBatch)(PropertyContainerHandle_t ulContainerHandle, संरचना PropertyWrite_t * pBatch, uint32_t un_Batch_Entry_गिनती);
	वर्ण * (OPENVR_FNTABLE_CALLTYPE *GetPropErrorNameFromEnum)(ETrackedPropertyError error);
	PropertyContainerHandle_t (OPENVR_FNTABLE_CALLTYPE *TrackedDeviceToPropertyContainer)(TrackedDeviceIndex_t nDevice);
};

संरचना VR_IVRPaths_FnTable
{
	ETrackedPropertyError (OPENVR_FNTABLE_CALLTYPE *ReadPathBatch)(PropertyContainerHandle_t ul_मूल_Handle, संरचना PathRead_t * pBatch, uint32_t un_Batch_Entry_गिनती);
	ETrackedPropertyError (OPENVR_FNTABLE_CALLTYPE *WritePathBatch)(PropertyContainerHandle_t ul_मूल_Handle, संरचना PathWrite_t * pBatch, uint32_t un_Batch_Entry_गिनती);
	ETrackedPropertyError (OPENVR_FNTABLE_CALLTYPE *StringToHandle)(PathHandle_t * pHandle, वर्ण * pchPath);
	ETrackedPropertyError (OPENVR_FNTABLE_CALLTYPE *HandleToString)(PathHandle_t pHandle, वर्ण * pchBuffer, uint32_t unBufferSize, uint32_t * punBufferSizeUsed);
};

संरचना VR_IVRBlockQueue_FnTable
{
	EBlockQueueError (OPENVR_FNTABLE_CALLTYPE *Create)(PropertyContainerHandle_t * pulQueueHandle, वर्ण * pchPath, uint32_t unBlockDataSize, uint32_t unBlockHeaderSize, uint32_t un_Block_गिनती, uint32_t unFlags);
	EBlockQueueError (OPENVR_FNTABLE_CALLTYPE *Connect)(PropertyContainerHandle_t * pulQueueHandle, वर्ण * pchPath);
	EBlockQueueError (OPENVR_FNTABLE_CALLTYPE *Destroy)(PropertyContainerHandle_t ulQueueHandle);
	EBlockQueueError (OPENVR_FNTABLE_CALLTYPE *AcquireWriteOnlyBlock)(PropertyContainerHandle_t ulQueueHandle, PropertyContainerHandle_t * pulBlockHandle, शून्य ** ppvBuffer);
	EBlockQueueError (OPENVR_FNTABLE_CALLTYPE *ReleaseWriteOnlyBlock)(PropertyContainerHandle_t ulQueueHandle, PropertyContainerHandle_t ulBlockHandle);
	EBlockQueueError (OPENVR_FNTABLE_CALLTYPE *WaitAndAcquireReadOnlyBlock)(PropertyContainerHandle_t ulQueueHandle, PropertyContainerHandle_t * pulBlockHandle, शून्य ** ppvBuffer, EBlockQueueReadType eReadType, uint32_t unTimeoutMs);
	EBlockQueueError (OPENVR_FNTABLE_CALLTYPE *AcquireReadOnlyBlock)(PropertyContainerHandle_t ulQueueHandle, PropertyContainerHandle_t * pulBlockHandle, शून्य ** ppvBuffer, EBlockQueueReadType eReadType);
	EBlockQueueError (OPENVR_FNTABLE_CALLTYPE *ReleaseReadOnlyBlock)(PropertyContainerHandle_t ulQueueHandle, PropertyContainerHandle_t ulBlockHandle);
	EBlockQueueError (OPENVR_FNTABLE_CALLTYPE *QueueHasReader)(PropertyContainerHandle_t ulQueueHandle, bool * pbHasReaders);
};


#यदि 0
// Global entry points
S_API intptr_t VR_InitInternal( EVRInitError *peError, EVRApplicationType eType );
S_API शून्य VR_ShutdownInternal();
S_API bool VR_IsHmdPresent();
S_API intptr_t VR_GetGenericInterface( ध्रुव वर्ण *pchInterfaceVersion, EVRInitError *peError );
S_API bool VR_IsRuntimeInstalled();
S_API ध्रुव वर्ण * VR_Get_VRInit_Error_As_प्रतीक( EVRInitError error );
S_API ध्रुव वर्ण * VR_GetVRInitErrorAsEnglishDescription( EVRInitError error );
#endif

#endif // __OPENVR_API_FLAT_H__


