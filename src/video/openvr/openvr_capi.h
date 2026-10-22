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

#अगर_अघोषित __OPENVR_API_FLAT_H__
#घोषणा __OPENVR_API_FLAT_H__
#अगर defined( _WIN32 ) || defined( __clang__ )
#आशय once
#पूर्ण_अगर

#अगर_घोषित __cplusplus
#घोषणा EXTERN_C बाह्य "C"
#अन्यथा
#घोषणा EXTERN_C
#पूर्ण_अगर

#अगर defined( _WIN32 )
#घोषणा OPENVR_FNTABLE_CALLTYPE __stdcall
#अन्यथा
#घोषणा OPENVR_FNTABLE_CALLTYPE 
#पूर्ण_अगर

// OPENVR API export macro
#अगर defined( _WIN32 ) && !defined( _X360 )
	#अगर defined( OPENVR_API_EXPORTS )
	#घोषणा S_API EXTERN_C __declspec( dllexport )
	#या_अगर defined( OPENVR_API_NODLL )
	#घोषणा S_API EXTERN_C
	#अन्यथा
	#घोषणा S_API बाह्य "C" __declspec( dllimport ) 
	#पूर्ण_अगर // OPENVR_API_EXPORTS
#या_अगर defined( __GNUC__ )
	#अगर defined( OPENVR_API_EXPORTS )
	#घोषणा S_API EXTERN_C __attribute__ ((visibility("default")))
	#अन्यथा
	#घोषणा S_API EXTERN_C
	#पूर्ण_अगर // OPENVR_API_EXPORTS
#अन्यथा // !WIN32
	#अगर defined( OPENVR_API_EXPORTS )
	#घोषणा S_API EXTERN_C
	#अन्यथा
	#घोषणा S_API EXTERN_C
	#पूर्ण_अगर // OPENVR_API_EXPORTS
#पूर्ण_अगर

#अगर_अघोषित USE_SDL
#समावेश <stdint.h>

#अगर defined( __WIN32 )
प्रकार अक्षर bool;
#अन्यथा
#समावेश <stdbool.h>
#पूर्ण_अगर
#पूर्ण_अगर // USE_SDL

// OpenVR Constants

अटल स्थिर अचिन्हित दीर्घ k_nDriverNone = 4294967295;
अटल स्थिर अचिन्हित दीर्घ k_un_Max_Driver_Debug_Response_आकार = 32768;
अटल स्थिर अचिन्हित दीर्घ k_un_Tracked_Device_सूचकांक_Hmd = 0;
अटल स्थिर अचिन्हित दीर्घ k_un_Max_Tracked_Device_गिनती = 64;
अटल स्थिर अचिन्हित दीर्घ k_un_Tracked_Device_सूचकांक_Other = 4294967294;
अटल स्थिर अचिन्हित दीर्घ k_un_Tracked_Device_सूचकांक_Invalid = 4294967295;
अटल स्थिर अचिन्हित दीर्घ दीर्घ k_ulInvalidPropertyContainer = 0;
अटल स्थिर अचिन्हित दीर्घ k_unInvalidPropertyTag = 0;
अटल स्थिर अचिन्हित दीर्घ दीर्घ k_ulInvalidDriverHandle = 0;
अटल स्थिर अचिन्हित दीर्घ k_unFloatPropertyTag = 1;
अटल स्थिर अचिन्हित दीर्घ k_unInt32PropertyTag = 2;
अटल स्थिर अचिन्हित दीर्घ k_unUint64PropertyTag = 3;
अटल स्थिर अचिन्हित दीर्घ k_unBoolPropertyTag = 4;
अटल स्थिर अचिन्हित दीर्घ k_unStringPropertyTag = 5;
अटल स्थिर अचिन्हित दीर्घ k_unErrorPropertyTag = 6;
अटल स्थिर अचिन्हित दीर्घ k_unDoublePropertyTag = 7;
अटल स्थिर अचिन्हित दीर्घ k_unHmdMatrix34PropertyTag = 20;
अटल स्थिर अचिन्हित दीर्घ k_unHmdMatrix44PropertyTag = 21;
अटल स्थिर अचिन्हित दीर्घ k_unHmdVector3PropertyTag = 22;
अटल स्थिर अचिन्हित दीर्घ k_unHmdVector4PropertyTag = 23;
अटल स्थिर अचिन्हित दीर्घ k_unHmdVector2PropertyTag = 24;
अटल स्थिर अचिन्हित दीर्घ k_unHmdQuadPropertyTag = 25;
अटल स्थिर अचिन्हित दीर्घ k_unHiddenAreaPropertyTag = 30;
अटल स्थिर अचिन्हित दीर्घ k_unPathHandleInfoTag = 31;
अटल स्थिर अचिन्हित दीर्घ k_unActionPropertyTag = 32;
अटल स्थिर अचिन्हित दीर्घ k_un_निवेश_मूल्य_Property_Tag = 33;
अटल स्थिर अचिन्हित दीर्घ k_unWildcardPropertyTag = 34;
अटल स्थिर अचिन्हित दीर्घ k_unHapticVibrationPropertyTag = 35;
अटल स्थिर अचिन्हित दीर्घ k_unSkeletonPropertyTag = 36;
अटल स्थिर अचिन्हित दीर्घ k_unSpatialAnchorPosePropertyTag = 40;
अटल स्थिर अचिन्हित दीर्घ k_unJsonPropertyTag = 41;
अटल स्थिर अचिन्हित दीर्घ k_unActiveActionSetPropertyTag = 42;
अटल स्थिर अचिन्हित दीर्घ k_unOpenVRInternalReserved_Start = 1000;
अटल स्थिर अचिन्हित दीर्घ k_unOpenVRInternalReserved_End = 10000;
अटल स्थिर अचिन्हित दीर्घ k_un_Max_Property_String_आकार = 32768;
अटल स्थिर अचिन्हित दीर्घ दीर्घ k_ulInvalidActionHandle = 0;
अटल स्थिर अचिन्हित दीर्घ दीर्घ k_ulInvalidActionSetHandle = 0;
अटल स्थिर अचिन्हित दीर्घ दीर्घ k_ul_Invalid_निवेश_मूल्य_Handle = 0;
अटल स्थिर अचिन्हित दीर्घ k_un_Controller_State_Axis_गिनती = 5;
अटल स्थिर अचिन्हित दीर्घ दीर्घ k_ulOverlayHandleInvalid = 0;
अटल स्थिर अचिन्हित दीर्घ k_unMaxDistortionFunctionParameters = 8;
अटल स्थिर अचिन्हित दीर्घ k_unScreenshotHandleInvalid = 0;
अटल स्थिर अक्षर * IVRSystem_Version = "IVRSystem_022";
अटल स्थिर अक्षर * IVRExtendedDisplay_Version = "IVRExtendedDisplay_001";
अटल स्थिर अक्षर * IVRTrackedCamera_Version = "IVRTrackedCamera_006";
अटल स्थिर अचिन्हित दीर्घ k_un_Max_Application_कुंजी_लंबाई = 128;
अटल स्थिर अक्षर * k_pch_MimeType_HomeApp = "vr/home";
अटल स्थिर अक्षर * k_pch_MimeType_GameTheater = "vr/game_theater";
अटल स्थिर अक्षर * IVRApplications_Version = "IVRApplications_007";
अटल स्थिर अक्षर * IVRChaperone_Version = "IVRChaperone_004";
अटल स्थिर अक्षर * IVRChaperoneSetup_Version = "IVRChaperoneSetup_006";
अटल स्थिर अक्षर * IVRCompositor_Version = "IVRCompositor_027";
अटल स्थिर अचिन्हित दीर्घ k_un_VROverlay_Max_कुंजी_लंबाई = 128;
अटल स्थिर अचिन्हित दीर्घ k_un_VROverlay_Max_Name_लंबाई = 128;
अटल स्थिर अचिन्हित दीर्घ k_un_Max_Overlay_गिनती = 128;
अटल स्थिर अचिन्हित दीर्घ k_un_Max_Overlay_Intersection_Mask_Primitives_गिनती = 32;
अटल स्थिर अक्षर * IVROverlay_Version = "IVROverlay_026";
अटल स्थिर अक्षर * IVROverlayView_Version = "IVROverlayView_003";
अटल स्थिर अचिन्हित दीर्घ k_unHeadsetViewMaxWidth = 3840;
अटल स्थिर अचिन्हित दीर्घ k_unHeadsetViewMaxHeight = 2160;
अटल स्थिर अक्षर * k_pch_Headset_View_Overlay_कुंजी = "system.HeadsetView";
अटल स्थिर अक्षर * IVRHeadsetView_Version = "IVRHeadsetView_001";
अटल स्थिर अक्षर * k_pch_Controller_Component_GDC2015 = "gdc2015";
अटल स्थिर अक्षर * k_pch_Controller_Component_Base = "base";
अटल स्थिर अक्षर * k_pch_Controller_Component_Tip = "tip";
अटल स्थिर अक्षर * k_pch_Controller_Component_OpenXR_Aim = "openxr_aim";
अटल स्थिर अक्षर * k_pch_Controller_Component_HandGrip = "handgrip";
अटल स्थिर अक्षर * k_pch_Controller_Component_OpenXR_Grip = "openxr_grip";
अटल स्थिर अक्षर * k_pch_Controller_Component_OpenXR_HandModel = "openxr_handmodel";
अटल स्थिर अक्षर * k_pch_Controller_Component_Status = "status";
अटल स्थिर अक्षर * IVRRenderModels_Version = "IVRRenderModels_006";
अटल स्थिर अचिन्हित दीर्घ k_un_Notification_Text_Max_आकार = 256;
अटल स्थिर अक्षर * IVRNotifications_Version = "IVRNotifications_002";
अटल स्थिर अचिन्हित दीर्घ k_un_Max_Settings_कुंजी_लंबाई = 128;
अटल स्थिर अक्षर * IVRSettings_Version = "IVRSettings_003";
अटल स्थिर अक्षर * k_pch_SteamVR_Section = "steamvr";
अटल स्थिर अक्षर * k_pch_SteamVR_RequireHmd_String = "requireHmd";
अटल स्थिर अक्षर * k_pch_Steam_VR_Forced_Driver_कुंजी_String = "forcedDriver";
अटल स्थिर अक्षर * k_pch_Steam_VR_Forced_Hmd_कुंजी_String = "forcedHmd";
अटल स्थिर अक्षर * k_pch_SteamVR_DisplayDebug_Bool = "displayDebug";
अटल स्थिर अक्षर * k_pch_SteamVR_DebugProcessPipe_String = "debugProcessPipe";
अटल स्थिर अक्षर * k_pch_SteamVR_DisplayDebugX_Int32 = "displayDebugX";
अटल स्थिर अक्षर * k_pch_SteamVR_DisplayDebugY_Int32 = "displayDebugY";
अटल स्थिर अक्षर * k_pch_SteamVR_SendSystemButtonToAllApps_Bool = "sendSystemButtonToAllApps";
अटल स्थिर अक्षर * k_pch_SteamVR_LogLevel_Int32 = "loglevel";
अटल स्थिर अक्षर * k_pch_SteamVR_IPD_Float = "ipd";
अटल स्थिर अक्षर * k_pch_SteamVR_Background_String = "background";
अटल स्थिर अक्षर * k_pch_SteamVR_BackgroundUseDomeProjection_Bool = "backgroundUseDomeProjection";
अटल स्थिर अक्षर * k_pch_SteamVR_BackgroundCameraHeight_Float = "backgroundCameraHeight";
अटल स्थिर अक्षर * k_pch_SteamVR_BackgroundDomeRadius_Float = "backgroundDomeRadius";
अटल स्थिर अक्षर * k_pch_SteamVR_GridColor_String = "gridColor";
अटल स्थिर अक्षर * k_pch_SteamVR_PlayAreaColor_String = "playAreaColor";
अटल स्थिर अक्षर * k_pch_SteamVR_TrackingLossColor_String = "trackingLossColor";
अटल स्थिर अक्षर * k_pch_SteamVR_ShowStage_Bool = "showStage";
अटल स्थिर अक्षर * k_pch_SteamVR_DrawTrackingReferences_Bool = "drawTrackingReferences";
अटल स्थिर अक्षर * k_pch_SteamVR_ActivateMultipleDrivers_Bool = "activateMultipleDrivers";
अटल स्थिर अक्षर * k_pch_SteamVR_UsingSpeakers_Bool = "usingSpeakers";
अटल स्थिर अक्षर * k_pch_SteamVR_SpeakersForwardYawOffsetDegrees_Float = "speakersForwardYawOffsetDegrees";
अटल स्थिर अक्षर * k_pch_SteamVR_BaseStationPowerManagement_Int32 = "basestationPowerManagement";
अटल स्थिर अक्षर * k_pch_SteamVR_ShowBaseStationPowerManagementTip_Int32 = "ShowBaseStationPowerManagementTip";
अटल स्थिर अक्षर * k_pch_SteamVR_NeverKillProcesses_Bool = "neverKillProcesses";
अटल स्थिर अक्षर * k_pch_SteamVR_SupersampleScale_Float = "supersampleScale";
अटल स्थिर अक्षर * k_pch_SteamVR_MaxRecommendedResolution_Int32 = "maxRecommendedResolution";
अटल स्थिर अक्षर * k_pch_SteamVR_MotionSmoothing_Bool = "motionSmoothing";
अटल स्थिर अक्षर * k_pch_SteamVR_MotionSmoothingOverride_Int32 = "motionSmoothingOverride";
अटल स्थिर अक्षर * k_pch_SteamVR_FramesToThrottle_Int32 = "framesToThrottle";
अटल स्थिर अक्षर * k_pch_SteamVR_AdditionalFramesToPredict_Int32 = "additionalFramesToPredict";
अटल स्थिर अक्षर * k_pch_SteamVR_WorldScale_Float = "worldScale";
अटल स्थिर अक्षर * k_pch_SteamVR_FovScale_Int32 = "fovScale";
अटल स्थिर अक्षर * k_pch_SteamVR_DisableAsyncReprojection_Bool = "disableAsync";
अटल स्थिर अक्षर * k_pch_SteamVR_ForceFadeOnBadTracking_Bool = "forceFadeOnBadTracking";
अटल स्थिर अक्षर * k_pch_SteamVR_DefaultMirrorView_Int32 = "mirrorView";
अटल स्थिर अक्षर * k_pch_SteamVR_ShowLegacyMirrorView_Bool = "showLegacyMirrorView";
अटल स्थिर अक्षर * k_pch_SteamVR_MirrorViewVisibility_Bool = "showMirrorView";
अटल स्थिर अक्षर * k_pch_SteamVR_MirrorViewDisplayMode_Int32 = "mirrorViewDisplayMode";
अटल स्थिर अक्षर * k_pch_SteamVR_MirrorViewEye_Int32 = "mirrorViewEye";
अटल स्थिर अक्षर * k_pch_SteamVR_MirrorViewGeometry_String = "mirrorViewGeometry";
अटल स्थिर अक्षर * k_pch_SteamVR_MirrorViewGeometryMaximized_String = "mirrorViewGeometryMaximized";
अटल स्थिर अक्षर * k_pch_SteamVR_PerfGraphVisibility_Bool = "showPerfGraph";
अटल स्थिर अक्षर * k_pch_SteamVR_StartMonitorFromAppLaunch = "startMonitorFromAppLaunch";
अटल स्थिर अक्षर * k_pch_SteamVR_StartCompositorFromAppLaunch_Bool = "startCompositorFromAppLaunch";
अटल स्थिर अक्षर * k_pch_SteamVR_StartDashboardFromAppLaunch_Bool = "startDashboardFromAppLaunch";
अटल स्थिर अक्षर * k_pch_SteamVR_StartOverlayAppsFromDashboard_Bool = "startOverlayAppsFromDashboard";
अटल स्थिर अक्षर * k_pch_SteamVR_EnableHomeApp = "enableHomeApp";
अटल स्थिर अक्षर * k_pch_SteamVR_CycleBackgroundImageTimeSec_Int32 = "CycleBackgroundImageTimeSec";
अटल स्थिर अक्षर * k_pch_SteamVR_RetailDemo_Bool = "retailDemo";
अटल स्थिर अक्षर * k_pch_SteamVR_IpdOffset_Float = "ipdOffset";
अटल स्थिर अक्षर * k_pch_SteamVR_AllowSupersampleFiltering_Bool = "allowSupersampleFiltering";
अटल स्थिर अक्षर * k_pch_SteamVR_SupersampleManualOverride_Bool = "supersampleManualOverride";
अटल स्थिर अक्षर * k_pch_SteamVR_EnableLinuxVulkanAsync_Bool = "enableLinuxVulkanAsync";
अटल स्थिर अक्षर * k_pch_SteamVR_AllowDisplayLockedMode_Bool = "allowDisplayLockedMode";
अटल स्थिर अक्षर * k_pch_SteamVR_HaveStartedTutorialForNativeChaperoneDriver_Bool = "haveStartedTutorialForNativeChaperoneDriver";
अटल स्थिर अक्षर * k_pch_SteamVR_ForceWindows32bitVRMonitor = "forceWindows32BitVRMonitor";
अटल स्थिर अक्षर * k_pch_Steam_VR_Debug_निवेश_Binding = "debugInputBinding";
अटल स्थिर अक्षर * k_pch_SteamVR_DoNotFadeToGrid = "doNotFadeToGrid";
अटल स्थिर अक्षर * k_pch_SteamVR_RenderCameraMode = "renderCameraMode";
अटल स्थिर अक्षर * k_pch_SteamVR_EnableSharedResourceJournaling = "enableSharedResourceJournaling";
अटल स्थिर अक्षर * k_pch_SteamVR_EnableSafeMode = "enableSafeMode";
अटल स्थिर अक्षर * k_pch_SteamVR_PreferredRefreshRate = "preferredRefreshRate";
अटल स्थिर अक्षर * k_pch_SteamVR_LastVersionNotice = "lastVersionNotice";
अटल स्थिर अक्षर * k_pch_SteamVR_LastVersionNoticeDate = "lastVersionNoticeDate";
अटल स्थिर अक्षर * k_pch_SteamVR_HmdDisplayColorGainR_Float = "hmdDisplayColorGainR";
अटल स्थिर अक्षर * k_pch_SteamVR_HmdDisplayColorGainG_Float = "hmdDisplayColorGainG";
अटल स्थिर अक्षर * k_pch_SteamVR_HmdDisplayColorGainB_Float = "hmdDisplayColorGainB";
अटल स्थिर अक्षर * k_pch_SteamVR_CustomIconStyle_String = "customIconStyle";
अटल स्थिर अक्षर * k_pch_SteamVR_CustomOffIconStyle_String = "customOffIconStyle";
अटल स्थिर अक्षर * k_pch_SteamVR_CustomIconForceUpdate_String = "customIconForceUpdate";
अटल स्थिर अक्षर * k_pch_SteamVR_AllowGlobalActionSetPriority = "globalActionSetPriority";
अटल स्थिर अक्षर * k_pch_SteamVR_OverlayRenderQuality = "overlayRenderQuality_2";
अटल स्थिर अक्षर * k_pch_SteamVR_BlockOculusSDKOnOpenVRLaunchOption_Bool = "blockOculusSDKOnOpenVRLaunchOption";
अटल स्थिर अक्षर * k_pch_SteamVR_BlockOculusSDKOnAllLaunches_Bool = "blockOculusSDKOnAllLaunches";
अटल स्थिर अक्षर * k_pch_SteamVR_HDCPLegacyCompatibility_Bool = "hdcp14legacyCompatibility";
अटल स्थिर अक्षर * k_pch_SteamVR_DisplayPortTrainingMode_Int = "displayPortTrainingMode";
अटल स्थिर अक्षर * k_pch_SteamVR_UsePrism_Bool = "usePrism";
अटल स्थिर अक्षर * k_pch_DirectMode_Section = "direct_mode";
अटल स्थिर अक्षर * k_pch_DirectMode_Enable_Bool = "enable";
अटल स्थिर अक्षर * k_pch_Direct_Mode_गिनती_Int32 = "count";
अटल स्थिर अक्षर * k_pch_DirectMode_EdidVid_Int32 = "edidVid";
अटल स्थिर अक्षर * k_pch_DirectMode_EdidPid_Int32 = "edidPid";
अटल स्थिर अक्षर * k_pch_Lighthouse_Section = "driver_lighthouse";
अटल स्थिर अक्षर * k_pch_Lighthouse_DisableIMU_Bool = "disableimu";
अटल स्थिर अक्षर * k_pch_Lighthouse_DisableIMUExceptHMD_Bool = "disableimuexcepthmd";
अटल स्थिर अक्षर * k_pch_Lighthouse_UseDisambiguation_String = "usedisambiguation";
अटल स्थिर अक्षर * k_pch_Lighthouse_DisambiguationDebug_Int32 = "disambiguationdebug";
अटल स्थिर अक्षर * k_pch_Lighthouse_PrimaryBasestation_Int32 = "primarybasestation";
अटल स्थिर अक्षर * k_pch_Lighthouse_DBHistory_Bool = "dbhistory";
अटल स्थिर अक्षर * k_pch_Lighthouse_EnableBluetooth_Bool = "enableBluetooth";
अटल स्थिर अक्षर * k_pch_Lighthouse_PowerManagedBaseStations_String = "PowerManagedBaseStations";
अटल स्थिर अक्षर * k_pch_Lighthouse_PowerManagedBaseStations2_String = "PowerManagedBaseStations2";
अटल स्थिर अक्षर * k_pch_Lighthouse_InactivityTimeoutForBaseStations_Int32 = "InactivityTimeoutForBaseStations";
अटल स्थिर अक्षर * k_pch_Lighthouse_EnableImuFallback_Bool = "enableImuFallback";
अटल स्थिर अक्षर * k_pch_Null_Section = "driver_null";
अटल स्थिर अक्षर * k_pch_Null_Serial_संख्या_String = "serialNumber";
अटल स्थिर अक्षर * k_pch_Null_Model_संख्या_String = "modelNumber";
अटल स्थिर अक्षर * k_pch_Null_WindowX_Int32 = "windowX";
अटल स्थिर अक्षर * k_pch_Null_WindowY_Int32 = "windowY";
अटल स्थिर अक्षर * k_pch_Null_WindowWidth_Int32 = "windowWidth";
अटल स्थिर अक्षर * k_pch_Null_WindowHeight_Int32 = "windowHeight";
अटल स्थिर अक्षर * k_pch_Null_RenderWidth_Int32 = "renderWidth";
अटल स्थिर अक्षर * k_pch_Null_RenderHeight_Int32 = "renderHeight";
अटल स्थिर अक्षर * k_pch_Null_SecondsFromVsyncToPhotons_Float = "secondsFromVsyncToPhotons";
अटल स्थिर अक्षर * k_pch_Null_DisplayFrequency_Float = "displayFrequency";
अटल स्थिर अक्षर * k_pch_WindowsMR_Section = "driver_holographic";
अटल स्थिर अक्षर * k_pch_UserInterface_Section = "userinterface";
अटल स्थिर अक्षर * k_pch_User_Interface_Status_Always_On_शीर्ष_Bool = "StatusAlwaysOnTop";
अटल स्थिर अक्षर * k_pch_UserInterface_MinimizeToTray_Bool = "MinimizeToTray";
अटल स्थिर अक्षर * k_pch_UserInterface_HidePopupsWhenStatusMinimized_Bool = "HidePopupsWhenStatusMinimized";
अटल स्थिर अक्षर * k_pch_UserInterface_Screenshots_Bool = "screenshots";
अटल स्थिर अक्षर * k_pch_UserInterface_ScreenshotType_Int = "screenshotType";
अटल स्थिर अक्षर * k_pch_Notifications_Section = "notifications";
अटल स्थिर अक्षर * k_pch_Notifications_DoNotDisturb_Bool = "DoNotDisturb";
अटल स्थिर अक्षर * k_pch_Keyboard_Section = "keyboard";
अटल स्थिर अक्षर * k_pch_Keyboard_TutorialCompletions = "TutorialCompletions";
अटल स्थिर अक्षर * k_pch_Keyboard_ScaleX = "ScaleX";
अटल स्थिर अक्षर * k_pch_Keyboard_ScaleY = "ScaleY";
अटल स्थिर अक्षर * k_pch_Keyboard_Offset_बायाँ_X = "OffsetLeftX";
अटल स्थिर अक्षर * k_pch_Keyboard_Offset_दायाँ_X = "OffsetRightX";
अटल स्थिर अक्षर * k_pch_Keyboard_OffsetY = "OffsetY";
अटल स्थिर अक्षर * k_pch_Keyboard_Smoothing = "Smoothing";
अटल स्थिर अक्षर * k_pch_Perf_Section = "perfcheck";
अटल स्थिर अक्षर * k_pch_Perf_PerfGraphInHMD_Bool = "perfGraphInHMD";
अटल स्थिर अक्षर * k_pch_Perf_AllowTimingStore_Bool = "allowTimingStore";
अटल स्थिर अक्षर * k_pch_Perf_SaveTimingsOnExit_Bool = "saveTimingsOnExit";
अटल स्थिर अक्षर * k_pch_Perf_Test_तथ्य_Float = "perfTestData";
अटल स्थिर अक्षर * k_pch_Perf_GPUProfiling_Bool = "GPUProfiling";
अटल स्थिर अक्षर * k_pch_CollisionBounds_Section = "collisionBounds";
अटल स्थिर अक्षर * k_pch_CollisionBounds_Style_Int32 = "CollisionBoundsStyle";
अटल स्थिर अक्षर * k_pch_CollisionBounds_GroundPerimeterOn_Bool = "CollisionBoundsGroundPerimeterOn";
अटल स्थिर अक्षर * k_pch_CollisionBounds_CenterMarkerOn_Bool = "CollisionBoundsCenterMarkerOn";
अटल स्थिर अक्षर * k_pch_CollisionBounds_PlaySpaceOn_Bool = "CollisionBoundsPlaySpaceOn";
अटल स्थिर अक्षर * k_pch_CollisionBounds_FadeDistance_Float = "CollisionBoundsFadeDistance";
अटल स्थिर अक्षर * k_pch_CollisionBounds_WallHeight_Float = "CollisionBoundsWallHeight";
अटल स्थिर अक्षर * k_pch_CollisionBounds_ColorGammaR_Int32 = "CollisionBoundsColorGammaR";
अटल स्थिर अक्षर * k_pch_CollisionBounds_ColorGammaG_Int32 = "CollisionBoundsColorGammaG";
अटल स्थिर अक्षर * k_pch_CollisionBounds_ColorGammaB_Int32 = "CollisionBoundsColorGammaB";
अटल स्थिर अक्षर * k_pch_CollisionBounds_ColorGammaA_Int32 = "CollisionBoundsColorGammaA";
अटल स्थिर अक्षर * k_pch_CollisionBounds_EnableDriverImport = "enableDriverBoundsImport";
अटल स्थिर अक्षर * k_pch_Camera_Section = "camera";
अटल स्थिर अक्षर * k_pch_Camera_EnableCamera_Bool = "enableCamera";
अटल स्थिर अक्षर * k_pch_Camera_ShowOnController_Bool = "showOnController";
अटल स्थिर अक्षर * k_pch_Camera_EnableCameraForCollisionBounds_Bool = "enableCameraForCollisionBounds";
अटल स्थिर अक्षर * k_pch_Camera_RoomView_Int32 = "roomView";
अटल स्थिर अक्षर * k_pch_Camera_BoundsColorGammaR_Int32 = "cameraBoundsColorGammaR";
अटल स्थिर अक्षर * k_pch_Camera_BoundsColorGammaG_Int32 = "cameraBoundsColorGammaG";
अटल स्थिर अक्षर * k_pch_Camera_BoundsColorGammaB_Int32 = "cameraBoundsColorGammaB";
अटल स्थिर अक्षर * k_pch_Camera_BoundsColorGammaA_Int32 = "cameraBoundsColorGammaA";
अटल स्थिर अक्षर * k_pch_Camera_BoundsStrength_Int32 = "cameraBoundsStrength";
अटल स्थिर अक्षर * k_pch_Camera_RoomViewStyle_Int32 = "roomViewStyle";
अटल स्थिर अक्षर * k_pch_audio_Section = "audio";
अटल स्थिर अक्षर * k_pch_audio_SetOsDefaultPlaybackDevice_Bool = "setOsDefaultPlaybackDevice";
अटल स्थिर अक्षर * k_pch_audio_EnablePlaybackDeviceOverride_Bool = "enablePlaybackDeviceOverride";
अटल स्थिर अक्षर * k_pch_audio_PlaybackDeviceOverride_String = "playbackDeviceOverride";
अटल स्थिर अक्षर * k_pch_audio_PlaybackDeviceOverrideName_String = "playbackDeviceOverrideName";
अटल स्थिर अक्षर * k_pch_audio_SetOsDefaultRecordingDevice_Bool = "setOsDefaultRecordingDevice";
अटल स्थिर अक्षर * k_pch_audio_EnableRecordingDeviceOverride_Bool = "enableRecordingDeviceOverride";
अटल स्थिर अक्षर * k_pch_audio_RecordingDeviceOverride_String = "recordingDeviceOverride";
अटल स्थिर अक्षर * k_pch_audio_RecordingDeviceOverrideName_String = "recordingDeviceOverrideName";
अटल स्थिर अक्षर * k_pch_audio_EnablePlaybackMirror_Bool = "enablePlaybackMirror";
अटल स्थिर अक्षर * k_pch_audio_PlaybackMirrorDevice_String = "playbackMirrorDevice";
अटल स्थिर अक्षर * k_pch_audio_PlaybackMirrorDeviceName_String = "playbackMirrorDeviceName";
अटल स्थिर अक्षर * k_pch_audio_OldPlaybackMirrorDevice_String = "onPlaybackMirrorDevice";
अटल स्थिर अक्षर * k_pch_audio_ActiveMirrorDevice_String = "activePlaybackMirrorDevice";
अटल स्थिर अक्षर * k_pch_audio_EnablePlaybackMirrorIndependentVolume_Bool = "enablePlaybackMirrorIndependentVolume";
अटल स्थिर अक्षर * k_pch_audio_LastHmdPlaybackDeviceId_String = "lastHmdPlaybackDeviceId";
अटल स्थिर अक्षर * k_pch_audio_VIVEHDMIGain = "viveHDMIGain";
अटल स्थिर अक्षर * k_pch_audio_DualSpeakerAndJackOutput_Bool = "dualSpeakerAndJackOutput";
अटल स्थिर अक्षर * k_pch_audio_MuteMicMonitor_Bool = "muteMicMonitor";
अटल स्थिर अक्षर * k_pch_Power_Section = "power";
अटल स्थिर अक्षर * k_pch_Power_PowerOffOnExit_Bool = "powerOffOnExit";
अटल स्थिर अक्षर * k_pch_Power_TurnOffScreensTimeout_Float = "turnOffScreensTimeout";
अटल स्थिर अक्षर * k_pch_Power_TurnOffControllersTimeout_Float = "turnOffControllersTimeout";
अटल स्थिर अक्षर * k_pch_Power_ReturnToWatchdogTimeout_Float = "returnToWatchdogTimeout";
अटल स्थिर अक्षर * k_pch_Power_AutoLaunchSteamVROnButtonPress = "autoLaunchSteamVROnButtonPress";
अटल स्थिर अक्षर * k_pch_Power_PauseCompositorOnStandby_Bool = "pauseCompositorOnStandby";
अटल स्थिर अक्षर * k_pch_Dashboard_Section = "dashboard";
अटल स्थिर अक्षर * k_pch_Dashboard_EnableDashboard_Bool = "enableDashboard";
अटल स्थिर अक्षर * k_pch_Dashboard_ArcadeMode_Bool = "arcadeMode";
अटल स्थिर अक्षर * k_pch_Dashboard_Position = "position";
अटल स्थिर अक्षर * k_pch_Dashboard_DesktopScale = "desktopScale";
अटल स्थिर अक्षर * k_pch_Dashboard_DashboardScale = "dashboardScale";
अटल स्थिर अक्षर * k_pch_Dashboard_UseStandaloneSystemLayer = "standaloneSystemLayer";
अटल स्थिर अक्षर * k_pch_Dashboard_StickyDashboard = "stickyDashboard";
अटल स्थिर अक्षर * k_pch_modelskin_Section = "modelskins";
अटल स्थिर अक्षर * k_pch_Driver_Enable_Bool = "enable";
अटल स्थिर अक्षर * k_pch_Driver_BlockedBySafemode_Bool = "blocked_by_safe_mode";
अटल स्थिर अक्षर * k_pch_Driver_LoadPriority_Int32 = "loadPriority";
अटल स्थिर अक्षर * k_pch_WebInterface_Section = "WebInterface";
अटल स्थिर अक्षर * k_pch_VRWebHelper_Section = "VRWebHelper";
अटल स्थिर अक्षर * k_pch_VRWebHelper_DebuggerEnabled_Bool = "DebuggerEnabled";
अटल स्थिर अक्षर * k_pch_VRWebHelper_DebuggerPort_Int32 = "DebuggerPort";
अटल स्थिर अक्षर * k_pch_TrackingOverride_Section = "TrackingOverrides";
अटल स्थिर अक्षर * k_pch_App_BindingAutosaveURLSuffix_String = "AutosaveURL";
अटल स्थिर अक्षर * k_pch_App_BindingLegacyAPISuffix_String = "_legacy";
अटल स्थिर अक्षर * k_pch_App_BindingSteamVRInputAPISuffix_String = "_steamvrinput";
अटल स्थिर अक्षर * k_pch_App_BindingOpenXRAPISuffix_String = "_openxr";
अटल स्थिर अक्षर * k_pch_App_BindingCurrentURLSuffix_String = "CurrentURL";
अटल स्थिर अक्षर * k_pch_App_BindingPreviousURLSuffix_String = "PreviousURL";
अटल स्थिर अक्षर * k_pch_App_NeedToUpdateAutosaveSuffix_Bool = "NeedToUpdateAutosave";
अटल स्थिर अक्षर * k_pch_App_DominantHand_Int32 = "DominantHand";
अटल स्थिर अक्षर * k_pch_App_BlockOculusSDK_Bool = "blockOculusSDK";
अटल स्थिर अक्षर * k_pch_Trackers_Section = "trackers";
अटल स्थिर अक्षर * k_pch_DesktopUI_Section = "DesktopUI";
अटल स्थिर अक्षर * k_pch_LastKnown_Section = "LastKnown";
अटल स्थिर अक्षर * k_pch_LastKnown_HMDManufacturer_String = "HMDManufacturer";
अटल स्थिर अक्षर * k_pch_LastKnown_HMDModel_String = "HMDModel";
अटल स्थिर अक्षर * k_pch_DismissedWarnings_Section = "DismissedWarnings";
अटल स्थिर अक्षर * k_pch_निवेश_Section = "input";
अटल स्थिर अक्षर * k_pch_निवेश_बायाँ_Thumbstick_Rotation_Float = "leftThumbstickRotation";
अटल स्थिर अक्षर * k_pch_निवेश_दायाँ_Thumbstick_Rotation_Float = "rightThumbstickRotation";
अटल स्थिर अक्षर * k_pch_निवेश_Thumbstick_Deadzone_Float = "thumbstickDeadzone";
अटल स्थिर अक्षर * k_pch_GpuSpeed_Section = "GpuSpeed";
अटल स्थिर अक्षर * IVRScreenshots_Version = "IVRScreenshots_001";
अटल स्थिर अक्षर * IVRResources_Version = "IVRResources_001";
अटल स्थिर अक्षर * IVRDriverManager_Version = "IVRDriverManager_001";
अटल स्थिर अचिन्हित दीर्घ k_un_Max_Action_Name_लंबाई = 64;
अटल स्थिर अचिन्हित दीर्घ k_un_Max_Action_Set_Name_लंबाई = 64;
अटल स्थिर अचिन्हित दीर्घ k_un_Max_Action_Origin_गिनती = 16;
अटल स्थिर अचिन्हित दीर्घ k_un_Max_Bone_Name_लंबाई = 32;
अटल स्थिर पूर्णांक k_nActionSetOverlayGlobalPriorityMin = 16777216;
अटल स्थिर पूर्णांक k_nActionSetOverlayGlobalPriorityMax = 33554431;
अटल स्थिर पूर्णांक k_nActionSetPriorityReservedMin = 33554432;
अटल स्थिर अक्षर * IVRInput_Version = "IVRInput_010";
अटल स्थिर अचिन्हित दीर्घ दीर्घ k_ulInvalidIOBufferHandle = 0;
अटल स्थिर अक्षर * IVRIOBuffer_Version = "IVRIOBuffer_002";
अटल स्थिर अचिन्हित दीर्घ k_ulInvalidSpatialAnchorHandle = 0;
अटल स्थिर अक्षर * IVRSpatialAnchors_Version = "IVRSpatialAnchors_001";
अटल स्थिर अक्षर * IVRDebug_Version = "IVRDebug_001";
अटल स्थिर अचिन्हित दीर्घ दीर्घ k_ulDisplayRedirectContainer = 25769803779;
अटल स्थिर अक्षर * IVRProperties_Version = "IVRProperties_001";
अटल स्थिर अक्षर * k_pch_Path_User_Hand_दायाँ = "/user/hand/right";
अटल स्थिर अक्षर * k_pch_Path_User_Hand_बायाँ = "/user/hand/left";
अटल स्थिर अक्षर * k_pchPathUserHandPrimary = "/user/hand/primary";
अटल स्थिर अक्षर * k_pchPathUserHandSecondary = "/user/hand/secondary";
अटल स्थिर अक्षर * k_pch_Path_User_शीर्ष = "/user/head";
अटल स्थिर अक्षर * k_pchPathUserGamepad = "/user/gamepad";
अटल स्थिर अक्षर * k_pchPathUserTreadmill = "/user/treadmill";
अटल स्थिर अक्षर * k_pchPathUserStylus = "/user/stylus";
अटल स्थिर अक्षर * k_pchPathDevices = "/devices";
अटल स्थिर अक्षर * k_pchPathDevicePath = "/device_path";
अटल स्थिर अक्षर * k_pchPathBestAliasPath = "/best_alias_path";
अटल स्थिर अक्षर * k_pchPathBoundTrackerAliasPath = "/bound_tracker_path";
अटल स्थिर अक्षर * k_pchPathBoundTrackerRole = "/bound_tracker_role";
अटल स्थिर अक्षर * k_pchPathPoseRaw = "/pose/raw";
अटल स्थिर अक्षर * k_pchPathPoseTip = "/pose/tip";
अटल स्थिर अक्षर * k_pchPathPoseGrip = "/pose/grip";
अटल स्थिर अक्षर * k_pchPathSystemButtonClick = "/input/system/click";
अटल स्थिर अक्षर * k_pchPathProximity = "/proximity";
अटल स्थिर अक्षर * k_pchPathControllerTypePrefix = "/controller_type/";
अटल स्थिर अक्षर * k_pch_Path_निवेश_Profile_Suffix = "/input_profile";
अटल स्थिर अक्षर * k_pchPathBindingNameSuffix = "/binding_name";
अटल स्थिर अक्षर * k_pchPathBindingUrlSuffix = "/binding_url";
अटल स्थिर अक्षर * k_pchPathBindingErrorSuffix = "/binding_error";
अटल स्थिर अक्षर * k_pchPathActiveActionSets = "/active_action_sets";
अटल स्थिर अक्षर * k_pchPathComponentUpdates = "/total_component_updates";
अटल स्थिर अक्षर * k_pch_Path_User_Foot_बायाँ = "/user/foot/left";
अटल स्थिर अक्षर * k_pch_Path_User_Foot_दायाँ = "/user/foot/right";
अटल स्थिर अक्षर * k_pch_Path_User_Shoulder_बायाँ = "/user/shoulder/left";
अटल स्थिर अक्षर * k_pch_Path_User_Shoulder_दायाँ = "/user/shoulder/right";
अटल स्थिर अक्षर * k_pch_Path_User_Elbow_बायाँ = "/user/elbow/left";
अटल स्थिर अक्षर * k_pch_Path_User_Elbow_दायाँ = "/user/elbow/right";
अटल स्थिर अक्षर * k_pch_Path_User_Knee_बायाँ = "/user/knee/left";
अटल स्थिर अक्षर * k_pch_Path_User_Knee_दायाँ = "/user/knee/right";
अटल स्थिर अक्षर * k_pchPathUserWaist = "/user/waist";
अटल स्थिर अक्षर * k_pchPathUserChest = "/user/chest";
अटल स्थिर अक्षर * k_pchPathUserCamera = "/user/camera";
अटल स्थिर अक्षर * k_pchPathUserKeyboard = "/user/keyboard";
अटल स्थिर अक्षर * k_pch_Path_Client_App_कुंजी = "/client_info/app_key";
अटल स्थिर अचिन्हित दीर्घ दीर्घ k_ulInvalidPathHandle = 0;
अटल स्थिर अक्षर * IVRPaths_Version = "IVRPaths_001";
अटल स्थिर अक्षर * IVRBlockQueue_Version = "IVRBlockQueue_005";

// OpenVR Enums

प्रकार क्रमागत EVREye
{
	EVREye_Eye_बायाँ = 0,
	EVREye_Eye_दायाँ = 1,
} EVREye;

प्रकार क्रमागत ETextureType
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

प्रकार क्रमागत EColorSpace
{
	EColorSpace_ColorSpace_Auto = 0,
	EColorSpace_ColorSpace_Gamma = 1,
	EColorSpace_ColorSpace_Linear = 2,
} EColorSpace;

प्रकार क्रमागत ETracking_परिणाम
{
	ETracking_परिणाम_Tracking_परिणाम_Uninitialized = 1,
	ETracking_परिणाम_Tracking_परिणाम_Calibrating_In_Progress = 100,
	ETracking_परिणाम_Tracking_परिणाम_Calibrating_Out_Of_Range = 101,
	ETracking_परिणाम_Tracking_परिणाम_Running_OK = 200,
	ETracking_परिणाम_Tracking_परिणाम_Running_Out_Of_Range = 201,
	ETracking_परिणाम_Tracking_परिणाम_Fallback_Rotation_Only = 300,
} ETracking_परिणाम;

प्रकार क्रमागत ETrackedDeviceClass
{
	ETrackedDeviceClass_TrackedDeviceClass_Invalid = 0,
	ETrackedDeviceClass_TrackedDeviceClass_HMD = 1,
	ETrackedDeviceClass_TrackedDeviceClass_Controller = 2,
	ETrackedDeviceClass_TrackedDeviceClass_GenericTracker = 3,
	ETrackedDeviceClass_TrackedDeviceClass_TrackingReference = 4,
	ETrackedDeviceClass_TrackedDeviceClass_DisplayRedirect = 5,
	ETrackedDeviceClass_TrackedDeviceClass_Max = 6,
} ETrackedDeviceClass;

प्रकार क्रमागत ETrackedControllerRole
{
	ETrackedControllerRole_TrackedControllerRole_Invalid = 0,
	ETracked_Controller_Role_Tracked_Controller_Role_बायाँ_Hand = 1,
	ETracked_Controller_Role_Tracked_Controller_Role_दायाँ_Hand = 2,
	ETrackedControllerRole_TrackedControllerRole_OptOut = 3,
	ETrackedControllerRole_TrackedControllerRole_Treadmill = 4,
	ETrackedControllerRole_TrackedControllerRole_Stylus = 5,
	ETrackedControllerRole_TrackedControllerRole_Max = 5,
} ETrackedControllerRole;

प्रकार क्रमागत ETrackingUniverseOrigin
{
	ETrackingUniverseOrigin_TrackingUniverseSeated = 0,
	ETrackingUniverseOrigin_TrackingUniverseStanding = 1,
	ETrackingUniverseOrigin_TrackingUniverseRawAndUncalibrated = 2,
} ETrackingUniverseOrigin;

प्रकार क्रमागत EAdditionalRadioFeatures
{
	EAdditionalRadioFeatures_AdditionalRadioFeatures_None = 0,
	EAdditionalRadioFeatures_AdditionalRadioFeatures_HTCLinkBox = 1,
	EAdditionalRadioFeatures_AdditionalRadioFeatures_InternalDongle = 2,
	EAdditionalRadioFeatures_AdditionalRadioFeatures_ExternalDongle = 4,
} EAdditionalRadioFeatures;

प्रकार क्रमागत ETrackedDeviceProperty
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
	ETracked_Device_Property_Prop_Additional_System_Report_तथ्य_String = 1045,
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
	ETracked_Device_Property_Prop_Camera_To_शीर्ष_Transform_Matrix34 = 2016,
	ETrackedDeviceProperty_Prop_DisplayGCType_Int32 = 2017,
	ETrackedDeviceProperty_Prop_DisplayGCOffset_Float = 2018,
	ETrackedDeviceProperty_Prop_DisplayGCScale_Float = 2019,
	ETrackedDeviceProperty_Prop_DisplayGCPrescale_Float = 2020,
	ETrackedDeviceProperty_Prop_DisplayGCImage_String = 2021,
	ETracked_Device_Property_Prop_Lens_Center_बायाँ_U_Float = 2022,
	ETracked_Device_Property_Prop_Lens_Center_बायाँ_V_Float = 2023,
	ETracked_Device_Property_Prop_Lens_Center_दायाँ_U_Float = 2024,
	ETracked_Device_Property_Prop_Lens_Center_दायाँ_V_Float = 2025,
	ETracked_Device_Property_Prop_User_शीर्ष_To_Eye_Depth_Meters_Float = 2026,
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
	ETracked_Device_Property_Prop_Display_MCImage_तथ्य_द्विआधारी = 2041,
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
	ETracked_Device_Property_Prop_Camera_To_शीर्ष_Transforms_Matrix34_Array = 2055,
	ETrackedDeviceProperty_Prop_DistortionMeshResolution_Int32 = 2056,
	ETrackedDeviceProperty_Prop_DriverIsDrawingControllers_Bool = 2057,
	ETrackedDeviceProperty_Prop_DriverRequestsApplicationPause_Bool = 2058,
	ETrackedDeviceProperty_Prop_DriverRequestsReducedRendering_Bool = 2059,
	ETrackedDeviceProperty_Prop_MinimumIpdStepMeters_Float = 2060,
	ETrackedDeviceProperty_Prop_AudioBridgeFirmwareVersion_Uint64 = 2061,
	ETrackedDeviceProperty_Prop_ImageBridgeFirmwareVersion_Uint64 = 2062,
	ETracked_Device_Property_Prop_Imu_To_शीर्ष_Transform_Matrix34 = 2063,
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

प्रकार क्रमागत ETrackedPropertyError
{
	ETrackedPropertyError_TrackedProp_Success = 0,
	ETracked_Property_Error_Tracked_Prop_Wrong_तथ्य_Type = 1,
	ETrackedPropertyError_TrackedProp_WrongDeviceClass = 2,
	ETracked_Property_Error_Tracked_Prop_बफर_Too_Small = 3,
	ETrackedPropertyError_TrackedProp_UnknownProperty = 4,
	ETrackedPropertyError_TrackedProp_InvalidDevice = 5,
	ETrackedPropertyError_TrackedProp_CouldNotContactServer = 6,
	ETracked_Property_Error_Tracked_Prop_मूल्य_Not_Provided_By_Device = 7,
	ETracked_Property_Error_Tracked_Prop_String_Exceeds_Maximum_लंबाई = 8,
	ETrackedPropertyError_TrackedProp_NotYetAvailable = 9,
	ETrackedPropertyError_TrackedProp_PermissionDenied = 10,
	ETrackedPropertyError_TrackedProp_InvalidOperation = 11,
	ETrackedPropertyError_TrackedProp_CannotWriteToWildcards = 12,
	ETrackedPropertyError_TrackedProp_IPCReadFailure = 13,
	ETrackedPropertyError_TrackedProp_OutOfMemory = 14,
	ETrackedPropertyError_TrackedProp_InvalidContainer = 15,
} ETrackedPropertyError;

प्रकार क्रमागत EHmdTrackingStyle
{
	EHmdTrackingStyle_HmdTrackingStyle_Unknown = 0,
	EHmdTrackingStyle_HmdTrackingStyle_Lighthouse = 1,
	EHmdTrackingStyle_HmdTrackingStyle_OutsideInCameras = 2,
	EHmdTrackingStyle_HmdTrackingStyle_InsideOutCameras = 3,
} EHmdTrackingStyle;

प्रकार क्रमागत EVRSubmitFlags
{
	EVRSubmitFlags_Submit_Default = 0,
	EVRSubmitFlags_Submit_LensDistortionAlreadyApplied = 1,
	EVRSubmit_Flags_Submit_Gl_Render_बफर = 2,
	EVRSubmitFlags_Submit_Reserved = 4,
	EVRSubmitFlags_Submit_TextureWithPose = 8,
	EVRSubmitFlags_Submit_TextureWithDepth = 16,
	EVRSubmitFlags_Submit_FrameDiscontinuty = 32,
	EVRSubmit_Flags_Submit_Vulkan_Texture_With_Array_तथ्य = 64,
	EVRSubmitFlags_Submit_GlArrayTexture = 128,
	EVRSubmitFlags_Submit_Reserved2 = 32768,
	EVRSubmitFlags_Submit_Reserved3 = 65536,
} EVRSubmitFlags;

प्रकार क्रमागत EVRState
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

प्रकार क्रमागत EVREventType
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
	EVREvent_Type_VREvent_Chaperone_तथ्य_Has_Changed = 800,
	EVREventType_VREvent_ChaperoneUniverseHasChanged = 801,
	EVREvent_Type_VREvent_Chaperone_अस्थायी_तथ्य_Has_Changed = 802,
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

प्रकार क्रमागत EDeviceActivityLevel
{
	EDeviceActivityLevel_k_EDeviceActivityLevel_Unknown = -1,
	EDeviceActivityLevel_k_EDeviceActivityLevel_Idle = 0,
	EDeviceActivityLevel_k_EDeviceActivityLevel_UserInteraction = 1,
	EDeviceActivityLevel_k_EDeviceActivityLevel_UserInteraction_Timeout = 2,
	EDeviceActivityLevel_k_EDeviceActivityLevel_Standby = 3,
	EDeviceActivityLevel_k_EDeviceActivityLevel_Idle_Timeout = 4,
} EDeviceActivityLevel;

प्रकार क्रमागत EVRButtonId
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
	EVRButton_Id_k_EButton_सूचकांक_Controller_A = 2,
	EVRButton_Id_k_EButton_सूचकांक_Controller_B = 1,
	EVRButton_Id_k_EButton_सूचकांक_Controller_Joy_Stick = 35,
	EVRButtonId_k_EButton_Max = 64,
} EVRButtonId;

प्रकार क्रमागत EVRMouseButton
{
	EVRMouse_Button_VRMouse_Button_बायाँ = 1,
	EVRMouse_Button_VRMouse_Button_दायाँ = 2,
	EVRMouse_Button_VRMouse_Button_मध्य = 4,
} EVRMouseButton;

प्रकार क्रमागत EShowUIType
{
	EShowUIType_ShowUI_ControllerBinding = 0,
	EShowUIType_ShowUI_ManageTrackers = 1,
	EShowUIType_ShowUI_Pairing = 3,
	EShowUIType_ShowUI_Settings = 4,
	EShowUIType_ShowUI_DebugCommands = 5,
	EShowUIType_ShowUI_FullControllerBinding = 6,
	EShowUIType_ShowUI_ManageDrivers = 7,
} EShowUIType;

प्रकार क्रमागत EHDCPError
{
	EHDCPError_HDCPError_None = 0,
	EHDCPError_HDCPError_LinkLost = 1,
	EHDCPError_HDCPError_Tampered = 2,
	EHDCPError_HDCPError_DeviceRevoked = 3,
	EHDCPError_HDCPError_Unknown = 4,
} EHDCPError;

प्रकार क्रमागत EVRComponentProperty
{
	EVRComponentProperty_VRComponentProperty_IsStatic = 1,
	EVRComponentProperty_VRComponentProperty_IsVisible = 2,
	EVRComponentProperty_VRComponentProperty_IsTouched = 4,
	EVRComponentProperty_VRComponentProperty_IsPressed = 8,
	EVRComponentProperty_VRComponentProperty_IsScrolled = 16,
	EVRComponentProperty_VRComponentProperty_IsHighlighted = 32,
} EVRComponentProperty;

प्रकार क्रमागत EVRInputError
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
	EVRInput_Error_VRInput_Error_Invalid_Compressed_तथ्य = 12,
	EVRInput_Error_VRInput_Error_No_तथ्य = 13,
	EVRInput_Error_VRInput_Error_बफर_Too_Small = 14,
	EVRInputError_VRInputError_MismatchedActionManifest = 15,
	EVRInput_Error_VRInput_Error_Missing_Skeleton_तथ्य = 16,
	EVRInput_Error_VRInput_Error_Invalid_Bone_सूचकांक = 17,
	EVRInputError_VRInputError_InvalidPriority = 18,
	EVRInputError_VRInputError_PermissionDenied = 19,
	EVRInputError_VRInputError_InvalidRenderModel = 20,
} EVRInputError;

प्रकार क्रमागत EVRSpatialAnchorError
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

प्रकार क्रमागत EHiddenAreaMeshType
{
	EHiddenAreaMeshType_k_eHiddenAreaMesh_Standard = 0,
	EHiddenAreaMeshType_k_eHiddenAreaMesh_Inverse = 1,
	EHidden_Area_Mesh_Type_k_e_Hidden_Area_Mesh_पंक्ति_Loop = 2,
	EHiddenAreaMeshType_k_eHiddenAreaMesh_Max = 3,
} EHiddenAreaMeshType;

प्रकार क्रमागत EVRControllerAxisType
{
	EVRControllerAxisType_k_eControllerAxis_None = 0,
	EVRControllerAxisType_k_eControllerAxis_TrackPad = 1,
	EVRControllerAxisType_k_eControllerAxis_Joystick = 2,
	EVRControllerAxisType_k_eControllerAxis_Trigger = 3,
} EVRControllerAxisType;

प्रकार क्रमागत EVRControllerEventOutputType
{
	EVRControllerEventOutputType_ControllerEventOutput_OSEvents = 0,
	EVRControllerEventOutputType_ControllerEventOutput_VREvents = 1,
} EVRControllerEventOutputType;

प्रकार क्रमागत ECollisionBoundsStyle
{
	ECollisionBoundsStyle_COLLISION_BOUNDS_STYLE_BEGINNER = 0,
	ECollisionBoundsStyle_COLLISION_BOUNDS_STYLE_INTERMEDIATE = 1,
	ECollisionBoundsStyle_COLLISION_BOUNDS_STYLE_SQUARES = 2,
	ECollisionBoundsStyle_COLLISION_BOUNDS_STYLE_ADVANCED = 3,
	ECollisionBoundsStyle_COLLISION_BOUNDS_STYLE_NONE = 4,
	ECollision_Bounds_Style_COLLISION_BOUNDS_STYLE_गिनती = 5,
} ECollisionBoundsStyle;

प्रकार क्रमागत EVROverlayError
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

प्रकार क्रमागत EVRApplicationType
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

प्रकार क्रमागत EVRFirmwareError
{
	EVRFirmwareError_VRFirmwareError_None = 0,
	EVRFirmwareError_VRFirmwareError_Success = 1,
	EVRFirmwareError_VRFirmwareError_Fail = 2,
} EVRFirmwareError;

प्रकार क्रमागत EVRNotificationError
{
	EVRNotificationError_VRNotificationError_OK = 0,
	EVRNotificationError_VRNotificationError_InvalidNotificationId = 100,
	EVRNotificationError_VRNotificationError_NotificationQueueFull = 101,
	EVRNotificationError_VRNotificationError_InvalidOverlayHandle = 102,
	EVRNotification_Error_VRNotification_Error_System_With_User_मूल्य_Already_Exists = 103,
} EVRNotificationError;

प्रकार क्रमागत EVRSkeletalMotionRange
{
	EVRSkeletalMotionRange_VRSkeletalMotionRange_WithController = 0,
	EVRSkeletalMotionRange_VRSkeletalMotionRange_WithoutController = 1,
} EVRSkeletalMotionRange;

प्रकार क्रमागत EVRSkeletalTrackingLevel
{
	EVRSkeletalTrackingLevel_VRSkeletalTracking_Estimated = 0,
	EVRSkeletalTrackingLevel_VRSkeletalTracking_Partial = 1,
	EVRSkeletalTrackingLevel_VRSkeletalTracking_Full = 2,
	EVRSkeletal_Tracking_Level_VRSkeletal_Tracking_Level_गिनती = 3,
	EVRSkeletalTrackingLevel_VRSkeletalTrackingLevel_Max = 2,
} EVRSkeletalTrackingLevel;

प्रकार क्रमागत EVRInitError
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
	EVRInit_Error_VRInit_Error_Compositor_Failed_To_Get_Back_बफर = 427,
	EVRInitError_VRInitError_Compositor_FailedToCreateRenderTarget = 428,
	EVRInitError_VRInitError_Compositor_FailedToCreateDXGI2SwapChain = 429,
	EVRInit_Error_VRInit_Error_Compositor_Failedto_Get_DXGI2_Back_बफर = 430,
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
	EVRInit_Error_VRInit_Error_Compositor_Create_Panel_Mask_Constant_बफर = 470,
	EVRInitError_VRInitError_Compositor_CreatePixelSimUBO = 471,
	EVRInitError_VRInitError_Compositor_CreateMSAARenderTextures = 472,
	EVRInitError_VRInitError_Compositor_CreateResolveRenderTextures = 473,
	EVRInitError_VRInitError_Compositor_CreateComputeResolveRenderTextures = 474,
	EVRInitError_VRInitError_Compositor_CreateDriverDirectModeResolveTextures = 475,
	EVRInitError_VRInitError_Compositor_OpenDriverDirectModeResolveTextures = 476,
	EVRInitError_VRInitError_Compositor_CreateFallbackSyncTexture = 477,
	EVRInitError_VRInitError_Compositor_ShareFallbackSyncTexture = 478,
	EVRInit_Error_VRInit_Error_Compositor_Create_Overlay_सूचकांक_बफर = 479,
	EVRInit_Error_VRInit_Error_Compositor_Create_Overlay_Vertex_बफर = 480,
	EVRInit_Error_VRInit_Error_Compositor_Create_Text_Vertex_बफर = 481,
	EVRInit_Error_VRInit_Error_Compositor_Create_Text_सूचकांक_बफर = 482,
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
	EVRInit_Error_VRInit_Error_Vendor_Specific_Hmd_Found_Unable_To_Send_User_तथ्य_Start = 1108,
	EVRInit_Error_VRInit_Error_Vendor_Specific_Hmd_Found_Unable_To_Get_User_तथ्य_Start = 1109,
	EVRInit_Error_VRInit_Error_Vendor_Specific_Hmd_Found_Unable_To_Get_User_तथ्य_अग्र = 1110,
	EVRInit_Error_VRInit_Error_Vendor_Specific_Hmd_Found_User_तथ्य_Address_Range = 1111,
	EVRInit_Error_VRInit_Error_Vendor_Specific_Hmd_Found_User_तथ्य_Error = 1112,
	EVRInitError_VRInitError_VendorSpecific_HmdFound_ConfigFailedSanityCheck = 1113,
	EVRInitError_VRInitError_VendorSpecific_OculusRuntimeBadInstall = 1114,
	EVRInitError_VRInitError_VendorSpecific_HmdFound_UnexpectedConfiguration_1 = 1115,
	EVRInitError_VRInitError_Steam_SteamInstallationNotFound = 2000,
	EVRInitError_VRInitError_LastError = 2001,
} EVRInitError;

प्रकार क्रमागत EVRScreenshotType
{
	EVRScreenshotType_VRScreenshotType_None = 0,
	EVRScreenshotType_VRScreenshotType_Mono = 1,
	EVRScreenshotType_VRScreenshotType_Stereo = 2,
	EVRScreenshotType_VRScreenshotType_Cubemap = 3,
	EVRScreenshotType_VRScreenshotType_MonoPanorama = 4,
	EVRScreenshotType_VRScreenshotType_StereoPanorama = 5,
} EVRScreenshotType;

प्रकार क्रमागत EVRScreenshotPropertyFilenames
{
	EVRScreenshotPropertyFilenames_VRScreenshotPropertyFilenames_Preview = 0,
	EVRScreenshotPropertyFilenames_VRScreenshotPropertyFilenames_VR = 1,
} EVRScreenshotPropertyFilenames;

प्रकार क्रमागत EVRTrackedCameraError
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
	EVRTracked_Camera_Error_VRTracked_Camera_Error_Invalid_Frame_बफर_आकार = 115,
} EVRTrackedCameraError;

प्रकार क्रमागत EVRTrackedCameraFrameLayout
{
	EVRTrackedCameraFrameLayout_Mono = 1,
	EVRTrackedCameraFrameLayout_Stereo = 2,
	EVRTrackedCameraFrameLayout_VerticalLayout = 16,
	EVRTrackedCameraFrameLayout_HorizontalLayout = 32,
} EVRTrackedCameraFrameLayout;

प्रकार क्रमागत EVRTrackedCameraFrameType
{
	EVRTrackedCameraFrameType_VRTrackedCameraFrameType_Distorted = 0,
	EVRTrackedCameraFrameType_VRTrackedCameraFrameType_Undistorted = 1,
	EVRTrackedCameraFrameType_VRTrackedCameraFrameType_MaximumUndistorted = 2,
	EVRTrackedCameraFrameType_MAX_CAMERA_FRAME_TYPES = 3,
} EVRTrackedCameraFrameType;

प्रकार क्रमागत EVRDistortionFunctionType
{
	EVRDistortionFunctionType_VRDistortionFunctionType_None = 0,
	EVRDistortionFunctionType_VRDistortionFunctionType_FTheta = 1,
	EVRDistortionFunctionType_VRDistortionFunctionType_Extended_FTheta = 2,
	EVRDistortionFunctionType_MAX_DISTORTION_FUNCTION_TYPES = 3,
} EVRDistortionFunctionType;

प्रकार क्रमागत EVSync
{
	EVSync_VSync_None = 0,
	EVSync_VSync_WaitRender = 1,
	EVSync_VSync_NoWaitRender = 2,
} EVSync;

प्रकार क्रमागत EVRMuraCorrectionMode
{
	EVRMuraCorrectionMode_Default = 0,
	EVRMuraCorrectionMode_NoCorrection = 1,
} EVRMuraCorrectionMode;

प्रकार क्रमागत Imu_OffScaleFlags
{
	Imu_OffScaleFlags_OffScale_AccelX = 1,
	Imu_OffScaleFlags_OffScale_AccelY = 2,
	Imu_OffScaleFlags_OffScale_AccelZ = 4,
	Imu_OffScaleFlags_OffScale_GyroX = 8,
	Imu_OffScaleFlags_OffScale_GyroY = 16,
	Imu_OffScaleFlags_OffScale_GyroZ = 32,
} Imu_OffScaleFlags;

प्रकार क्रमागत EVRApplicationError
{
	EVRApplicationError_VRApplicationError_None = 0,
	EVRApplication_Error_VRApplication_Error_App_कुंजी_Already_Exists = 100,
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
	EVRApplicationError_VRApplicationError_LaunchInProgress = 111,
	EVRApplicationError_VRApplicationError_OldApplicationQuitting = 112,
	EVRApplicationError_VRApplicationError_TransitionAborted = 113,
	EVRApplicationError_VRApplicationError_IsTemplate = 114,
	EVRApplicationError_VRApplicationError_SteamVRIsExiting = 115,
	EVRApplication_Error_VRApplication_Error_बफर_Too_Small = 200,
	EVRApplicationError_VRApplicationError_PropertyNotSet = 201,
	EVRApplicationError_VRApplicationError_UnknownProperty = 202,
	EVRApplicationError_VRApplicationError_InvalidParameter = 203,
	EVRApplicationError_VRApplicationError_NotImplemented = 300,
} EVRApplicationError;

प्रकार क्रमागत EVRApplicationProperty
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

प्रकार क्रमागत EVRSceneApplicationState
{
	EVRSceneApplicationState_None = 0,
	EVRSceneApplicationState_Starting = 1,
	EVRSceneApplicationState_Quitting = 2,
	EVRSceneApplicationState_Running = 3,
	EVRSceneApplicationState_Waiting = 4,
} EVRSceneApplicationState;

प्रकार क्रमागत ChaperoneCalibrationState
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

प्रकार क्रमागत EChaperoneConfigFile
{
	EChaperoneConfigFile_Live = 1,
	EChaperone_Config_File_अस्थायी = 2,
} EChaperoneConfigFile;

प्रकार क्रमागत EChaperoneImportFlags
{
	EChaperoneImportFlags_EChaperoneImport_BoundsOnly = 1,
} EChaperoneImportFlags;

प्रकार क्रमागत EVRCompositorError
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
	EVRCompositor_Error_VRCompositor_Error_सूचकांक_Out_Of_Range = 107,
	EVRCompositorError_VRCompositorError_AlreadySubmitted = 108,
	EVRCompositorError_VRCompositorError_InvalidBounds = 109,
	EVRCompositorError_VRCompositorError_AlreadySet = 110,
} EVRCompositorError;

प्रकार क्रमागत EVRCompositorTimingMode
{
	EVRCompositorTimingMode_VRCompositorTimingMode_Implicit = 0,
	EVRCompositorTimingMode_VRCompositorTimingMode_Explicit_RuntimePerformsPostPresentHandoff = 1,
	EVRCompositorTimingMode_VRCompositorTimingMode_Explicit_ApplicationPerformsPostPresentHandoff = 2,
} EVRCompositorTimingMode;

प्रकार क्रमागत VROverlay_निवेश_Method
{
	VROverlay_निवेश_Method_None = 0,
	VROverlay_निवेश_Method_Mouse = 1,
} VROverlay_निवेश_Method;

प्रकार क्रमागत VROverlayTransformType
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

प्रकार क्रमागत VROverlayFlags
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

प्रकार क्रमागत VRMessageOverlayResponse
{
	VRMessageOverlayResponse_ButtonPress_0 = 0,
	VRMessageOverlayResponse_ButtonPress_1 = 1,
	VRMessageOverlayResponse_ButtonPress_2 = 2,
	VRMessageOverlayResponse_ButtonPress_3 = 3,
	VRMessageOverlayResponse_CouldntFindSystemOverlay = 4,
	VRMessageOverlayResponse_CouldntFindOrCreateClientOverlay = 5,
	VRMessageOverlayResponse_ApplicationQuit = 6,
} VRMessageOverlayResponse;

प्रकार क्रमागत EGamepad_Text_निवेश_Mode
{
	EGamepad_Text_निवेश_Mode_k_EGamepad_Text_निवेश_Mode_Normal = 0,
	EGamepad_Text_निवेश_Mode_k_EGamepad_Text_निवेश_Mode_Password = 1,
	EGamepad_Text_निवेश_Mode_k_EGamepad_Text_निवेश_Mode_Submit = 2,
} EGamepad_Text_निवेश_Mode;

प्रकार क्रमागत EGamepad_Text_निवेश_पंक्ति_Mode
{
	EGamepad_Text_निवेश_पंक्ति_Mode_k_EGamepad_Text_निवेश_पंक्ति_Mode_Single_पंक्ति = 0,
	EGamepad_Text_निवेश_पंक्ति_Mode_k_EGamepad_Text_निवेश_पंक्ति_Mode_Multiple_पंक्तियाँ = 1,
} EGamepad_Text_निवेश_पंक्ति_Mode;

प्रकार क्रमागत EVROverlayIntersectionMaskPrimitiveType
{
	EVROverlayIntersectionMaskPrimitiveType_OverlayIntersectionPrimitiveType_Rectangle = 0,
	EVROverlayIntersectionMaskPrimitiveType_OverlayIntersectionPrimitiveType_Circle = 1,
} EVROverlayIntersectionMaskPrimitiveType;

प्रकार क्रमागत EKeyboardFlags
{
	EKeyboardFlags_KeyboardFlag_Minimal = 1,
	EKeyboardFlags_KeyboardFlag_Modal = 2,
} EKeyboardFlags;

प्रकार क्रमागत EDeviceType
{
	EDeviceType_DeviceType_Invalid = -1,
	EDeviceType_DeviceType_DirectX11 = 0,
	EDeviceType_DeviceType_Vulkan = 1,
} EDeviceType;

प्रकार क्रमागत HeadsetViewMode_t
{
	Headset_View_Mode_t_Headset_View_Mode_बायाँ = 0,
	Headset_View_Mode_t_Headset_View_Mode_दायाँ = 1,
	HeadsetViewMode_t_HeadsetViewMode_Both = 2,
} HeadsetViewMode_t;

प्रकार क्रमागत EVRRenderModelError
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
	EVRRender_Model_Error_VRRender_Model_Error_बफर_Too_Small = 306,
	EVRRenderModelError_VRRenderModelError_NotEnoughNormals = 307,
	EVRRenderModelError_VRRenderModelError_NotEnoughTexCoords = 308,
	EVRRenderModelError_VRRenderModelError_InvalidTexture = 400,
} EVRRenderModelError;

प्रकार क्रमागत EVRRenderModelTextureFormat
{
	EVRRenderModelTextureFormat_VRRenderModelTextureFormat_RGBA8_SRGB = 0,
	EVRRenderModelTextureFormat_VRRenderModelTextureFormat_BC2 = 1,
	EVRRenderModelTextureFormat_VRRenderModelTextureFormat_BC4 = 2,
	EVRRenderModelTextureFormat_VRRenderModelTextureFormat_BC7 = 3,
	EVRRenderModelTextureFormat_VRRenderModelTextureFormat_BC7_SRGB = 4,
	EVRRenderModelTextureFormat_VRRenderModelTextureFormat_RGBA16_FLOAT = 5,
} EVRRenderModelTextureFormat;

प्रकार क्रमागत EVRNotificationType
{
	EVRNotificationType_Transient = 0,
	EVRNotificationType_Persistent = 1,
	EVRNotification_Type_Transient_System_With_User_मूल्य = 2,
} EVRNotificationType;

प्रकार क्रमागत EVRNotificationStyle
{
	EVRNotificationStyle_None = 0,
	EVRNotificationStyle_Application = 100,
	EVRNotificationStyle_Contact_Disabled = 200,
	EVRNotificationStyle_Contact_Enabled = 201,
	EVRNotificationStyle_Contact_Active = 202,
} EVRNotificationStyle;

प्रकार क्रमागत EVRSettingsError
{
	EVRSettingsError_VRSettingsError_None = 0,
	EVRSettingsError_VRSettingsError_IPCFailed = 1,
	EVRSettingsError_VRSettingsError_WriteFailed = 2,
	EVRSettingsError_VRSettingsError_ReadFailed = 3,
	EVRSettingsError_VRSettingsError_JsonParseFailed = 4,
	EVRSettingsError_VRSettingsError_UnsetSettingHasNoDefault = 5,
} EVRSettingsError;

प्रकार क्रमागत EVRScreenshotError
{
	EVRScreenshotError_VRScreenshotError_None = 0,
	EVRScreenshotError_VRScreenshotError_RequestFailed = 1,
	EVRScreenshotError_VRScreenshotError_IncompatibleVersion = 100,
	EVRScreenshotError_VRScreenshotError_NotFound = 101,
	EVRScreenshot_Error_VRScreenshot_Error_बफर_Too_Small = 102,
	EVRScreenshotError_VRScreenshotError_ScreenshotAlreadyInProgress = 108,
} EVRScreenshotError;

प्रकार क्रमागत EVRSkeletalTransformSpace
{
	EVRSkeletalTransformSpace_VRSkeletalTransformSpace_Model = 0,
	EVRSkeletalTransformSpace_VRSkeletalTransformSpace_Parent = 1,
} EVRSkeletalTransformSpace;

प्रकार क्रमागत EVRSkeletalReferencePose
{
	EVRSkeletalReferencePose_VRSkeletalReferencePose_BindPose = 0,
	EVRSkeletalReferencePose_VRSkeletalReferencePose_OpenHand = 1,
	EVRSkeletalReferencePose_VRSkeletalReferencePose_Fist = 2,
	EVRSkeletalReferencePose_VRSkeletalReferencePose_GripLimit = 3,
} EVRSkeletalReferencePose;

प्रकार क्रमागत EVRFinger
{
	EVRFinger_VRFinger_Thumb = 0,
	EVRFinger_VRFinger_सूचकांक = 1,
	EVRFinger_VRFinger_मध्य = 2,
	EVRFinger_VRFinger_Ring = 3,
	EVRFinger_VRFinger_Pinky = 4,
	EVRFinger_VRFinger_गिनती = 5,
} EVRFinger;

प्रकार क्रमागत EVRFingerSplay
{
	EVRFinger_Splay_VRFinger_Splay_Thumb_सूचकांक = 0,
	EVRFinger_Splay_VRFinger_Splay_सूचकांक_मध्य = 1,
	EVRFinger_Splay_VRFinger_Splay_मध्य_Ring = 2,
	EVRFingerSplay_VRFingerSplay_Ring_Pinky = 3,
	EVRFinger_Splay_VRFinger_Splay_गिनती = 4,
} EVRFingerSplay;

प्रकार क्रमागत EVRSummaryType
{
	EVRSummaryType_VRSummaryType_FromAnimation = 0,
	EVRSummaryType_VRSummaryType_FromDevice = 1,
} EVRSummaryType;

प्रकार क्रमागत EVRInputFilterCancelType
{
	EVRInputFilterCancelType_VRInputFilterCancel_Timers = 0,
	EVRInputFilterCancelType_VRInputFilterCancel_Momentum = 1,
} EVRInputFilterCancelType;

प्रकार क्रमागत EVRInputStringBits
{
	EVRInputStringBits_VRInputString_Hand = 1,
	EVRInputStringBits_VRInputString_ControllerType = 2,
	EVRInput_String_Bits_VRInput_String_निवेश_Source = 4,
	EVRInputStringBits_VRInputString_All = -1,
} EVRInputStringBits;

प्रकार क्रमागत EIOBufferError
{
	EIOBufferError_IOBuffer_Success = 0,
	EIOBufferError_IOBuffer_OperationFailed = 100,
	EIOBufferError_IOBuffer_InvalidHandle = 101,
	EIOBufferError_IOBuffer_InvalidArgument = 102,
	EIOBufferError_IOBuffer_PathExists = 103,
	EIOBufferError_IOBuffer_PathDoesNotExist = 104,
	EIOBufferError_IOBuffer_Permission = 105,
} EIOBufferError;

प्रकार क्रमागत EIOBufferMode
{
	EIOBufferMode_IOBufferMode_Read = 1,
	EIOBufferMode_IOBufferMode_Write = 2,
	EIOBufferMode_IOBufferMode_Create = 512,
} EIOBufferMode;

प्रकार क्रमागत EVRDebugError
{
	EVRDebugError_VRDebugError_Success = 0,
	EVRDebugError_VRDebugError_BadParameter = 1,
} EVRDebugError;

प्रकार क्रमागत EPropertyWriteType
{
	EPropertyWriteType_PropertyWrite_Set = 0,
	EPropertyWriteType_PropertyWrite_Erase = 1,
	EPropertyWriteType_PropertyWrite_SetError = 2,
} EPropertyWriteType;

प्रकार क्रमागत EBlockQueueError
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

प्रकार क्रमागत EBlockQueueReadType
{
	EBlockQueueReadType_BlockQueueRead_Latest = 0,
	EBlockQueueReadType_BlockQueueRead_New = 1,
	EBlock_Queue_Read_Type_Block_Queue_Read_अग्र = 2,
} EBlockQueueReadType;

प्रकार क्रमागत EBlockQueueCreationFlag
{
	EBlockQueueCreationFlag_BlockQueueFlag_OwnerIsReader = 1,
} EBlockQueueCreationFlag;


// OpenVR typedefs

प्रकार uint32_t PropertyTypeTag_t;
प्रकार uint32_t SpatialAnchorHandle_t;
प्रकार व्योम * glSharedTextureHandle_t;
प्रकार int32_t glInt_t;
प्रकार uint32_t glUInt_t;
प्रकार uint64_t SharedTextureHandle_t;
प्रकार uint32_t DriverId_t;
प्रकार uint32_t Tracked_Device_सूचकांक_t;
प्रकार uint64_t WebConsoleHandle_t;
प्रकार uint64_t PropertyContainerHandle_t;
प्रकार PropertyContainerHandle_t DriverHandle_t;
प्रकार uint64_t VRActionHandle_t;
प्रकार uint64_t VRActionSetHandle_t;
प्रकार uint64_t VRInput_मूल्य_Handle_t;
प्रकार uint32_t VRComponentProperties;
प्रकार uint64_t VROverlayHandle_t;
प्रकार int32_t Bone_सूचकांक_t;
प्रकार uint64_t TrackedCameraHandle_t;
प्रकार uint32_t ScreenshotHandle_t;
प्रकार int32_t TextureID_t;
प्रकार uint32_t VRNotificationId;
प्रकार uint64_t IOBufferHandle_t;
प्रकार uint64_t VrProfilerEventHandle_t;
प्रकार EVRInitError HmdError;
प्रकार EVREye Hmd_Eye;
प्रकार EColorSpace ColorSpace;
प्रकार ETracking_परिणाम Hmd_Tracking_परिणाम;
प्रकार ETrackedDeviceClass TrackedDeviceClass;
प्रकार ETrackingUniverseOrigin TrackingUniverseOrigin;
प्रकार ETrackedDeviceProperty TrackedDeviceProperty;
प्रकार ETrackedPropertyError TrackedPropertyError;
प्रकार EVRSubmitFlags VRSubmitFlags_t;
प्रकार EVRState VRState_t;
प्रकार ECollisionBoundsStyle CollisionBoundsStyle_t;
प्रकार EVROverlayError VROverlayError;
प्रकार EVRFirmwareError VRFirmwareError;
प्रकार EVRCompositorError VRCompositorError;
प्रकार EVRScreenshotError VRScreenshotsError;
प्रकार uint64_t PathHandle_t;

// OpenVR Structs

प्रकार काष्ठा HmdMatrix34_t
{
	भग्न m[3][4]; //float[3][4]
} HmdMatrix34_t;

प्रकार काष्ठा HmdMatrix33_t
{
	भग्न m[3][3]; //float[3][3]
} HmdMatrix33_t;

प्रकार काष्ठा HmdMatrix44_t
{
	भग्न m[4][4]; //float[4][4]
} HmdMatrix44_t;

प्रकार काष्ठा HmdVector3_t
{
	भग्न v[3]; //float[3]
} HmdVector3_t;

प्रकार काष्ठा HmdVector4_t
{
	भग्न v[4]; //float[4]
} HmdVector4_t;

प्रकार काष्ठा HmdVector3d_t
{
	द्विगुन v[3]; //double[3]
} HmdVector3d_t;

प्रकार काष्ठा HmdVector2_t
{
	भग्न v[2]; //float[2]
} HmdVector2_t;

प्रकार काष्ठा HmdQuaternion_t
{
	द्विगुन w;
	द्विगुन x;
	द्विगुन y;
	द्विगुन z;
} HmdQuaternion_t;

प्रकार काष्ठा HmdQuaternionf_t
{
	भग्न w;
	भग्न x;
	भग्न y;
	भग्न z;
} HmdQuaternionf_t;

प्रकार काष्ठा HmdColor_t
{
	भग्न r;
	भग्न g;
	भग्न b;
	भग्न a;
} HmdColor_t;

प्रकार काष्ठा HmdQuad_t
{
	काष्ठा HmdVector3_t vCorners[4]; //struct vr::HmdVector3_t[4]
} HmdQuad_t;

प्रकार काष्ठा HmdRect2_t
{
	काष्ठा HmdVector2_t v_शीर्ष_बायाँ;
	काष्ठा HmdVector2_t v_Bottom_दायाँ;
} HmdRect2_t;

प्रकार काष्ठा VRBoneTransform_t
{
	काष्ठा HmdVector4_t position;
	काष्ठा HmdQuaternionf_t orientation;
} VRBoneTransform_t;

प्रकार काष्ठा DistortionCoordinates_t
{
	भग्न rfRed[2]; //float[2]
	भग्न rfGreen[2]; //float[2]
	भग्न rfBlue[2]; //float[2]
} DistortionCoordinates_t;

प्रकार काष्ठा Texture_t
{
	व्योम * handle; // void *
	क्रमागत ETextureType eType;
	क्रमागत EColorSpace eColorSpace;
} Texture_t;

प्रकार काष्ठा TrackedDevicePose_t
{
	काष्ठा HmdMatrix34_t mDeviceToAbsoluteTracking;
	काष्ठा HmdVector3_t vVelocity;
	काष्ठा HmdVector3_t vAngularVelocity;
	क्रमागत ETracking_परिणाम e_Tracking_परिणाम;
	bool bPoseIsValid;
	bool bDeviceIsConnected;
} TrackedDevicePose_t;

प्रकार काष्ठा VRTextureBounds_t
{
	भग्न uMin;
	भग्न vMin;
	भग्न uMax;
	भग्न vMax;
} VRTextureBounds_t;

प्रकार काष्ठा VRTextureWithPose_t
{
	व्योम * handle; // void *
	क्रमागत ETextureType eType;
	क्रमागत EColorSpace eColorSpace;
	काष्ठा HmdMatrix34_t mDeviceToAbsoluteTracking;
} VRTextureWithPose_t;

प्रकार काष्ठा VRTextureDepthInfo_t
{
	व्योम * handle; // void *
	काष्ठा HmdMatrix44_t mProjection;
	काष्ठा HmdVector2_t vRange;
} VRTextureDepthInfo_t;

प्रकार काष्ठा VRTextureWithDepth_t
{
	व्योम * handle; // void *
	क्रमागत ETextureType eType;
	क्रमागत EColorSpace eColorSpace;
	काष्ठा VRTextureDepthInfo_t depth;
} VRTextureWithDepth_t;

प्रकार काष्ठा VRTextureWithPoseAndDepth_t
{
	व्योम * handle; // void *
	क्रमागत ETextureType eType;
	क्रमागत EColorSpace eColorSpace;
	काष्ठा HmdMatrix34_t mDeviceToAbsoluteTracking;
	काष्ठा VRTextureDepthInfo_t depth;
} VRTextureWithPoseAndDepth_t;

प्रकार काष्ठा VRVulkan_Texture_तथ्य_t
{
	uint64_t m_nImage;
	काष्ठा VkDevice_T * m_pDevice; // struct VkDevice_T *
	काष्ठा VkPhysicalDevice_T * m_pPhysicalDevice; // struct VkPhysicalDevice_T *
	काष्ठा VkInstance_T * m_pInstance; // struct VkInstance_T *
	काष्ठा VkQueue_T * m_pQueue; // struct VkQueue_T *
	uint32_t m_n_Queue_Family_सूचकांक;
	uint32_t m_nWidth;
	uint32_t m_nHeight;
	uint32_t m_nFormat;
	uint32_t m_n_Sample_गिनती;
} VRVulkan_Texture_तथ्य_t;

प्रकार काष्ठा VRVulkan_Texture_Array_तथ्य_t
{
	uint32_t m_un_Array_सूचकांक;
	uint32_t m_un_Array_आकार;
} VRVulkan_Texture_Array_तथ्य_t;

प्रकार काष्ठा D3_D12_Texture_तथ्य_t
{
	काष्ठा ID3D12Resource * m_pResource; // struct ID3D12Resource *
	काष्ठा ID3D12CommandQueue * m_pCommandQueue; // struct ID3D12CommandQueue *
	uint32_t m_n_गाँठ_Mask;
} D3_D12_Texture_तथ्य_t;

प्रकार काष्ठा VREvent_Controller_t
{
	uint32_t button;
} VREvent_Controller_t;

प्रकार काष्ठा VREvent_Mouse_t
{
	भग्न x;
	भग्न y;
	uint32_t button;
} VREvent_Mouse_t;

प्रकार काष्ठा VREvent_Scroll_t
{
	भग्न xdelta;
	भग्न ydelta;
	uint32_t unused;
	भग्न viewportscale;
} VREvent_Scroll_t;

प्रकार काष्ठा VREvent_TouchPadMove_t
{
	bool bFingerDown;
	भग्न flSecondsFingerDown;
	भग्न f_मूल्य_XFirst;
	भग्न f_मूल्य_YFirst;
	भग्न f_मूल्य_XRaw;
	भग्न f_मूल्य_YRaw;
} VREvent_TouchPadMove_t;

प्रकार काष्ठा VREvent_Notification_t
{
	uint64_t ul_User_मूल्य;
	uint32_t notificationId;
} VREvent_Notification_t;

प्रकार काष्ठा VREvent_Process_t
{
	uint32_t pid;
	uint32_t oldPid;
	bool bForced;
	bool bConnectionLost;
} VREvent_Process_t;

प्रकार काष्ठा VREvent_Overlay_t
{
	uint64_t overlayHandle;
	uint64_t devicePath;
	uint64_t memoryBlockId;
} VREvent_Overlay_t;

प्रकार काष्ठा VREvent_Status_t
{
	uint32_t statusState;
} VREvent_Status_t;

प्रकार काष्ठा VREvent_Keyboard_t
{
	अक्षर c_New_निवेश[8]; //char[8]
	uint64_t u_User_मूल्य;
} VREvent_Keyboard_t;

प्रकार काष्ठा VREvent_Ipd_t
{
	भग्न ipdMeters;
} VREvent_Ipd_t;

प्रकार काष्ठा VREvent_Chaperone_t
{
	uint64_t m_nPreviousUniverse;
	uint64_t m_nCurrentUniverse;
} VREvent_Chaperone_t;

प्रकार काष्ठा VREvent_Reserved_t
{
	uint64_t reserved0;
	uint64_t reserved1;
	uint64_t reserved2;
	uint64_t reserved3;
	uint64_t reserved4;
	uint64_t reserved5;
} VREvent_Reserved_t;

प्रकार काष्ठा VREvent_PerformanceTest_t
{
	uint32_t m_nFidelityLevel;
} VREvent_PerformanceTest_t;

प्रकार काष्ठा VREvent_SeatedZeroPoseReset_t
{
	bool bResetBySystemMenu;
} VREvent_SeatedZeroPoseReset_t;

प्रकार काष्ठा VREvent_Screenshot_t
{
	uint32_t handle;
	uint32_t type;
} VREvent_Screenshot_t;

प्रकार काष्ठा VREvent_ScreenshotProgress_t
{
	भग्न progress;
} VREvent_ScreenshotProgress_t;

प्रकार काष्ठा VREvent_ApplicationLaunch_t
{
	uint32_t pid;
	uint32_t unArgsHandle;
} VREvent_ApplicationLaunch_t;

प्रकार काष्ठा VREvent_EditingCameraSurface_t
{
	uint64_t overlayHandle;
	uint32_t nVisualMode;
} VREvent_EditingCameraSurface_t;

प्रकार काष्ठा VREvent_MessageOverlay_t
{
	uint32_t unVRMessageOverlayResponse;
} VREvent_MessageOverlay_t;

प्रकार काष्ठा VREvent_Property_t
{
	PropertyContainerHandle_t container;
	क्रमागत ETrackedDeviceProperty prop;
} VREvent_Property_t;

प्रकार काष्ठा VREvent_HapticVibration_t
{
	uint64_t containerHandle;
	uint64_t componentHandle;
	भग्न fDurationSeconds;
	भग्न fFrequency;
	भग्न fAmplitude;
} VREvent_HapticVibration_t;

प्रकार काष्ठा VREvent_WebConsole_t
{
	WebConsoleHandle_t webConsoleHandle;
} VREvent_WebConsole_t;

प्रकार काष्ठा VREvent_निवेश_Binding_Load_t
{
	PropertyContainerHandle_t ulAppContainer;
	uint64_t pathMessage;
	uint64_t pathUrl;
	uint64_t pathControllerType;
} VREvent_निवेश_Binding_Load_t;

प्रकार काष्ठा VREvent_निवेश_Action_Manifest_Load_t
{
	uint64_t path_App_कुंजी;
	uint64_t pathMessage;
	uint64_t pathMessageParam;
	uint64_t pathManifestPath;
} VREvent_निवेश_Action_Manifest_Load_t;

प्रकार काष्ठा VREvent_SpatialAnchor_t
{
	SpatialAnchorHandle_t unHandle;
} VREvent_SpatialAnchor_t;

प्रकार काष्ठा VREvent_ProgressUpdate_t
{
	uint64_t ulApplicationPropertyContainer;
	uint64_t pathDevice;
	uint64_t path_निवेश_Source;
	uint64_t pathProgressAction;
	uint64_t pathIcon;
	भग्न fProgress;
} VREvent_ProgressUpdate_t;

प्रकार काष्ठा VREvent_ShowUI_t
{
	क्रमागत EShowUIType eType;
} VREvent_ShowUI_t;

प्रकार काष्ठा VREvent_ShowDevTools_t
{
	int32_t nBrowserIdentifier;
} VREvent_ShowDevTools_t;

प्रकार काष्ठा VREvent_HDCPError_t
{
	क्रमागत EHDCPError eCode;
} VREvent_HDCPError_t;

प्रकार काष्ठा RenderModel_ComponentState_t
{
	काष्ठा HmdMatrix34_t mTrackingToComponentRenderModel;
	काष्ठा HmdMatrix34_t mTrackingToComponentLocal;
	VRComponentProperties uProperties;
} RenderModel_ComponentState_t;

प्रकार काष्ठा HiddenAreaMesh_t
{
	काष्ठा HmdVector2_t * p_Vertex_तथ्य; // const struct vr::HmdVector2_t *
	uint32_t un_Triangle_गिनती;
} HiddenAreaMesh_t;

प्रकार काष्ठा VRControllerAxis_t
{
	भग्न x;
	भग्न y;
} VRControllerAxis_t;

प्रकार काष्ठा VRControllerState_t
{
	uint32_t un_Packet_अंक;
	uint64_t ulButtonPressed;
	uint64_t ulButtonTouched;
	काष्ठा VRControllerAxis_t rAxis[5]; //struct vr::VRControllerAxis_t[5]
} VRControllerState_t;

प्रकार काष्ठा CameraVideoStreamFrameHeader_t
{
	क्रमागत EVRTrackedCameraFrameType eFrameType;
	uint32_t nWidth;
	uint32_t nHeight;
	uint32_t nBytesPerPixel;
	uint32_t nFrameSequence;
	काष्ठा TrackedDevicePose_t trackedDevicePose;
	uint64_t ulFrameExposureTime;
} CameraVideoStreamFrameHeader_t;

प्रकार काष्ठा Compositor_FrameTiming
{
	uint32_t m_n_आकार;
	uint32_t m_n_Frame_सूचकांक;
	uint32_t m_n_अंक_Frame_Presents;
	uint32_t m_n_अंक_Mis_Presented;
	uint32_t m_n_अंक_Dropped_Frames;
	uint32_t m_nReprojectionFlags;
	द्विगुन m_flSystemTimeInSeconds;
	भग्न m_flPreSubmitGpuMs;
	भग्न m_flPostSubmitGpuMs;
	भग्न m_fl_योग_Render_Gpu_Ms;
	भग्न m_flCompositorRenderGpuMs;
	भग्न m_flCompositorRenderCpuMs;
	भग्न m_flCompositorIdleCpuMs;
	भग्न m_flClientFrameIntervalMs;
	भग्न m_flPresentCallCpuMs;
	भग्न m_flWaitForPresentCpuMs;
	भग्न m_flSubmitFrameMs;
	भग्न m_flWaitGetPosesCalledMs;
	भग्न m_flNewPosesReadyMs;
	भग्न m_flNewFrameReadyMs;
	भग्न m_flCompositorUpdateStartMs;
	भग्न m_flCompositorUpdateEndMs;
	भग्न m_flCompositorRenderStartMs;
	TrackedDevicePose_t m_HmdPose;
	uint32_t m_n_अंक_VSyncs_Ready_For_Use;
	uint32_t m_n_अंक_VSyncs_To_First_View;
} Compositor_FrameTiming;

प्रकार काष्ठा Compositor_BenchmarkResults
{
	भग्न m_flMegaPixelsPerSecond;
	भग्न m_flHmdRecommendedMegaPixelsPerSecond;
} Compositor_BenchmarkResults;

प्रकार काष्ठा DriverDirectMode_FrameTiming
{
	uint32_t m_n_आकार;
	uint32_t m_n_अंक_Frame_Presents;
	uint32_t m_n_अंक_Mis_Presented;
	uint32_t m_n_अंक_Dropped_Frames;
	uint32_t m_nReprojectionFlags;
} DriverDirectMode_FrameTiming;

प्रकार काष्ठा ImuSample_t
{
	द्विगुन fSampleTime;
	काष्ठा HmdVector3d_t vAccel;
	काष्ठा HmdVector3d_t vGyro;
	uint32_t unOffScaleFlags;
} ImuSample_t;

प्रकार काष्ठा App_Override_कुंजियाँ_t
{
	अक्षर * pch_कुंजी; // const char *
	अक्षर * pch_मूल्य; // const char *
} App_Override_कुंजियाँ_t;

प्रकार काष्ठा Compositor_CumulativeStats
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
	द्विगुन m_fl_योग_Compositor_CPUTime_MS;
	द्विगुन m_fl_योग_Compositor_GPUTime_MS;
	द्विगुन m_fl_योग_Target_Frame_Times;
	द्विगुन m_fl_योग_Application_CPUTime_MS;
	द्विगुन m_fl_योग_Application_GPUTime_MS;
} Compositor_CumulativeStats;

प्रकार काष्ठा Compositor_StageRenderSettings
{
	काष्ठा HmdColor_t m_PrimaryColor;
	काष्ठा HmdColor_t m_SecondaryColor;
	भग्न m_flVignetteInnerRadius;
	भग्न m_flVignetteOuterRadius;
	भग्न m_flFresnelStrength;
	bool m_bBackfaceCulling;
	bool m_bGreyscale;
	bool m_bWireframe;
} Compositor_StageRenderSettings;

प्रकार काष्ठा VROverlayIntersectionParams_t
{
	काष्ठा HmdVector3_t vSource;
	काष्ठा HmdVector3_t vDirection;
	क्रमागत ETrackingUniverseOrigin eOrigin;
} VROverlayIntersectionParams_t;

प्रकार काष्ठा VROverlayIntersectionResults_t
{
	काष्ठा HmdVector3_t vPoint;
	काष्ठा HmdVector3_t vNormal;
	काष्ठा HmdVector2_t vUVs;
	भग्न fDistance;
} VROverlayIntersectionResults_t;

प्रकार काष्ठा IntersectionMaskRectangle_t
{
	भग्न m_fl_शीर्ष_बायाँ_X;
	भग्न m_fl_शीर्ष_बायाँ_Y;
	भग्न m_flWidth;
	भग्न m_flHeight;
} IntersectionMaskRectangle_t;

प्रकार काष्ठा IntersectionMaskCircle_t
{
	भग्न m_flCenterX;
	भग्न m_flCenterY;
	भग्न m_flRadius;
} IntersectionMaskCircle_t;

प्रकार काष्ठा VROverlayProjection_t
{
	भग्न f_बायाँ;
	भग्न f_दायाँ;
	भग्न f_शीर्ष;
	भग्न fBottom;
} VROverlayProjection_t;

प्रकार काष्ठा VROverlayView_t
{
	VROverlayHandle_t overlayHandle;
	काष्ठा Texture_t texture;
	काष्ठा VRTextureBounds_t textureBounds;
} VROverlayView_t;

प्रकार काष्ठा VRVulkanDevice_t
{
	काष्ठा VkInstance_T * m_pInstance; // struct VkInstance_T *
	काष्ठा VkDevice_T * m_pDevice; // struct VkDevice_T *
	काष्ठा VkPhysicalDevice_T * m_pPhysicalDevice; // struct VkPhysicalDevice_T *
	काष्ठा VkQueue_T * m_pQueue; // struct VkQueue_T *
	uint32_t m_u_Queue_Family_सूचकांक;
} VRVulkanDevice_t;

प्रकार काष्ठा VRNativeDevice_t
{
	व्योम * handle; // void *
	क्रमागत EDeviceType eType;
} VRNativeDevice_t;

प्रकार काष्ठा RenderModel_Vertex_t
{
	काष्ठा HmdVector3_t vPosition;
	काष्ठा HmdVector3_t vNormal;
	भग्न rfTextureCoord[2]; //float[2]
} RenderModel_Vertex_t;

#अगर defined(__linux__) || defined(__APPLE__)
#आशय pack( धकेलो, 4 )
#पूर्ण_अगर
प्रकार काष्ठा RenderModel_TextureMap_t
{
	uint16_t unWidth;
	uint16_t unHeight;
	uint8_t * rub_Texture_Map_तथ्य; // const uint8_t *
	क्रमागत EVRRenderModelTextureFormat format;
	uint16_t unMipLevels;
} RenderModel_TextureMap_t;

#अगर defined(__linux__) || defined(__APPLE__)
#आशय pack( निकालो )
#पूर्ण_अगर
#अगर defined(__linux__) || defined(__APPLE__)
#आशय pack( धकेलो, 4 )
#पूर्ण_अगर
प्रकार काष्ठा RenderModel_t
{
	काष्ठा RenderModel_Vertex_t * r_Vertex_तथ्य; // const struct vr::RenderModel_Vertex_t *
	uint32_t un_Vertex_गिनती;
	uint16_t * r_सूचकांक_तथ्य; // const uint16_t *
	uint32_t un_Triangle_गिनती;
	TextureID_t diffuseTextureId;
} RenderModel_t;

#अगर defined(__linux__) || defined(__APPLE__)
#आशय pack( निकालो )
#पूर्ण_अगर
प्रकार काष्ठा RenderModel_ControllerMode_State_t
{
	bool bScrollWheelVisible;
} RenderModel_ControllerMode_State_t;

प्रकार काष्ठा NotificationBitmap_t
{
	व्योम * m_p_Image_तथ्य; // void *
	int32_t m_nWidth;
	int32_t m_nHeight;
	int32_t m_nBytesPerPixel;
} NotificationBitmap_t;

प्रकार काष्ठा CVRSettingHelper
{
	intptr_t m_pSettings; // class vr::IVRSettings *
} CVRSettingHelper;

प्रकार काष्ठा निवेश_Analog_Action_तथ्य_t
{
	bool bActive;
	VRInput_मूल्य_Handle_t activeOrigin;
	भग्न x;
	भग्न y;
	भग्न z;
	भग्न deltaX;
	भग्न deltaY;
	भग्न deltaZ;
	भग्न fUpdateTime;
} निवेश_Analog_Action_तथ्य_t;

प्रकार काष्ठा निवेश_Digital_Action_तथ्य_t
{
	bool bActive;
	VRInput_मूल्य_Handle_t activeOrigin;
	bool bState;
	bool bChanged;
	भग्न fUpdateTime;
} निवेश_Digital_Action_तथ्य_t;

प्रकार काष्ठा निवेश_Pose_Action_तथ्य_t
{
	bool bActive;
	VRInput_मूल्य_Handle_t activeOrigin;
	काष्ठा TrackedDevicePose_t pose;
} निवेश_Pose_Action_तथ्य_t;

प्रकार काष्ठा निवेश_Skeletal_Action_तथ्य_t
{
	bool bActive;
	VRInput_मूल्य_Handle_t activeOrigin;
} निवेश_Skeletal_Action_तथ्य_t;

प्रकार काष्ठा निवेश_Origin_Info_t
{
	VRInput_मूल्य_Handle_t devicePath;
	Tracked_Device_सूचकांक_t tracked_Device_सूचकांक;
	अक्षर rchRenderModelComponentName[128]; //char[128]
} निवेश_Origin_Info_t;

प्रकार काष्ठा निवेश_Binding_Info_t
{
	अक्षर rchDevicePathName[128]; //char[128]
	अक्षर rch_निवेश_Path_Name[128]; //char[128]
	अक्षर rchModeName[128]; //char[128]
	अक्षर rchSlotName[128]; //char[128]
	अक्षर rch_निवेश_Source_Type[32]; //char[32]
} निवेश_Binding_Info_t;

प्रकार काष्ठा VRActiveActionSet_t
{
	VRActionSetHandle_t ulActionSet;
	VRInput_मूल्य_Handle_t ulRestrictedToDevice;
	VRActionSetHandle_t ulSecondaryActionSet;
	uint32_t unPadding;
	int32_t nPriority;
} VRActiveActionSet_t;

प्रकार काष्ठा VRSkeletal_Summary_तथ्य_t
{
	भग्न flFingerCurl[5]; //float[5]
	भग्न flFingerSplay[4]; //float[4]
} VRSkeletal_Summary_तथ्य_t;

प्रकार काष्ठा SpatialAnchorPose_t
{
	काष्ठा HmdMatrix34_t mAnchorToAbsoluteTracking;
} SpatialAnchorPose_t;

प्रकार काष्ठा COpenVRContext
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

प्रकार काष्ठा PropertyWrite_t
{
	क्रमागत ETrackedDeviceProperty prop;
	क्रमागत EPropertyWriteType writeType;
	क्रमागत ETrackedPropertyError eSetError;
	व्योम * pv_बफर; // void *
	uint32_t un_बफर_आकार;
	PropertyTypeTag_t unTag;
	क्रमागत ETrackedPropertyError eError;
} PropertyWrite_t;

प्रकार काष्ठा PropertyRead_t
{
	क्रमागत ETrackedDeviceProperty prop;
	व्योम * pv_बफर; // void *
	uint32_t un_बफर_आकार;
	PropertyTypeTag_t unTag;
	uint32_t un_Required_बफर_आकार;
	क्रमागत ETrackedPropertyError eError;
} PropertyRead_t;

प्रकार काष्ठा CVRPropertyHelpers
{
	intptr_t m_pProperties; // class vr::IVRProperties *
} CVRPropertyHelpers;

प्रकार काष्ठा PathWrite_t
{
	PathHandle_t ulPath;
	क्रमागत EPropertyWriteType writeType;
	क्रमागत ETrackedPropertyError eSetError;
	व्योम * pv_बफर; // void *
	uint32_t un_बफर_आकार;
	PropertyTypeTag_t unTag;
	क्रमागत ETrackedPropertyError eError;
	अक्षर * pszPath; // const char *
} PathWrite_t;

प्रकार काष्ठा PathRead_t
{
	PathHandle_t ulPath;
	व्योम * pv_बफर; // void *
	uint32_t un_बफर_आकार;
	PropertyTypeTag_t unTag;
	uint32_t un_Required_बफर_आकार;
	क्रमागत ETrackedPropertyError eError;
	अक्षर * pszPath; // const char *
} PathRead_t;


प्रकार जोड़
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
} VREvent_तथ्य_t;

#अगर defined(__linux__) || defined(__APPLE__) 
// This structure was originally defined mis-packed on Linux, preserved for 
// compatibility. 
#आशय pack( धकेलो, 4 )
#पूर्ण_अगर

/** An event posted by the server to all running applications */
काष्ठा VREvent_t
{
	uint32_t eventType; // EVREventType enum
	Tracked_Device_सूचकांक_t tracked_Device_सूचकांक;
	भग्न eventAgeSeconds;
	// event data must be the end of the struct as its size is variable
	VREvent_तथ्य_t तथ्य;
};

#अगर defined(__linux__) || defined(__APPLE__) 
#आशय pack( निकालो )
#पूर्ण_अगर


प्रकार जोड़
{
	IntersectionMaskRectangle_t m_Rectangle;
	IntersectionMaskCircle_t m_Circle;
} VROverlay_Intersection_Mask_Primitive_तथ्य_t;

काष्ठा VROverlayIntersectionMaskPrimitive_t
{
	EVROverlayIntersectionMaskPrimitiveType m_nPrimitiveType;
	VROverlay_Intersection_Mask_Primitive_तथ्य_t m_Primitive;
};


// OpenVR Function Pointer Tables

काष्ठा VR_IVRSystem_FnTable
{
	व्योम (OPENVR_FNTABLE_CALLTYPE *Get_Recommended_Render_Target_आकार)(uint32_t * pnWidth, uint32_t * pnHeight);
	काष्ठा HmdMatrix44_t (OPENVR_FNTABLE_CALLTYPE *GetProjectionMatrix)(EVREye eEye, भग्न fNearZ, भग्न fFarZ);
	व्योम (OPENVR_FNTABLE_CALLTYPE *GetProjectionRaw)(EVREye eEye, भग्न * pf_बायाँ, भग्न * pf_दायाँ, भग्न * pf_शीर्ष, भग्न * pfBottom);
	bool (OPENVR_FNTABLE_CALLTYPE *ComputeDistortion)(EVREye eEye, भग्न fU, भग्न fV, काष्ठा DistortionCoordinates_t * pDistortionCoordinates);
	काष्ठा HmdMatrix34_t (OPENVR_FNTABLE_CALLTYPE *Get_Eye_To_शीर्ष_Transform)(EVREye eEye);
	bool (OPENVR_FNTABLE_CALLTYPE *GetTimeSinceLastVsync)(भग्न * pfSecondsSinceLastVsync, uint64_t * pul_Frame_गणक);
	int32_t (OPENVR_FNTABLE_CALLTYPE *Get_D3_D9_Adapter_सूचकांक)();
	व्योम (OPENVR_FNTABLE_CALLTYPE *GetDXGIOutputInfo)(int32_t * pn_Adapter_सूचकांक);
	व्योम (OPENVR_FNTABLE_CALLTYPE *GetOutputDevice)(uint64_t * pnDevice, ETextureType textureType, काष्ठा VkInstance_T * pInstance);
	bool (OPENVR_FNTABLE_CALLTYPE *IsDisplayOnDesktop)();
	bool (OPENVR_FNTABLE_CALLTYPE *SetDisplayVisibility)(bool bIsVisibleOnDesktop);
	व्योम (OPENVR_FNTABLE_CALLTYPE *GetDeviceToAbsoluteTrackingPose)(ETrackingUniverseOrigin eOrigin, भग्न fPredictedSecondsToPhotonsFromNow, काष्ठा TrackedDevicePose_t * pTrackedDevicePoseArray, uint32_t un_Tracked_Device_Pose_Array_गिनती);
	काष्ठा HmdMatrix34_t (OPENVR_FNTABLE_CALLTYPE *GetSeatedZeroPoseToStandingAbsoluteTrackingPose)();
	काष्ठा HmdMatrix34_t (OPENVR_FNTABLE_CALLTYPE *GetRawZeroPoseToStandingAbsoluteTrackingPose)();
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetSortedTrackedDeviceIndicesOfClass)(ETrackedDeviceClass eTrackedDeviceClass, Tracked_Device_सूचकांक_t * pun_Tracked_Device_सूचकांक_Array, uint32_t un_Tracked_Device_सूचकांक_Array_गिनती, Tracked_Device_सूचकांक_t un_Relative_To_Tracked_Device_सूचकांक);
	EDeviceActivityLevel (OPENVR_FNTABLE_CALLTYPE *GetTrackedDeviceActivityLevel)(Tracked_Device_सूचकांक_t unDeviceId);
	व्योम (OPENVR_FNTABLE_CALLTYPE *ApplyTransform)(काष्ठा TrackedDevicePose_t * pOutputPose, काष्ठा TrackedDevicePose_t * pTrackedDevicePose, काष्ठा HmdMatrix34_t * pTransform);
	Tracked_Device_सूचकांक_t (OPENVR_FNTABLE_CALLTYPE *Get_Tracked_Device_सूचकांक_For_Controller_Role)(ETrackedControllerRole unDeviceType);
	ETrackedControllerRole (OPENVR_FNTABLE_CALLTYPE *Get_Controller_Role_For_Tracked_Device_सूचकांक)(Tracked_Device_सूचकांक_t un_Device_सूचकांक);
	ETrackedDeviceClass (OPENVR_FNTABLE_CALLTYPE *GetTrackedDeviceClass)(Tracked_Device_सूचकांक_t un_Device_सूचकांक);
	bool (OPENVR_FNTABLE_CALLTYPE *IsTrackedDeviceConnected)(Tracked_Device_सूचकांक_t un_Device_सूचकांक);
	bool (OPENVR_FNTABLE_CALLTYPE *GetBoolTrackedDeviceProperty)(Tracked_Device_सूचकांक_t un_Device_सूचकांक, ETrackedDeviceProperty prop, ETrackedPropertyError * pError);
	भग्न (OPENVR_FNTABLE_CALLTYPE *GetFloatTrackedDeviceProperty)(Tracked_Device_सूचकांक_t un_Device_सूचकांक, ETrackedDeviceProperty prop, ETrackedPropertyError * pError);
	int32_t (OPENVR_FNTABLE_CALLTYPE *GetInt32TrackedDeviceProperty)(Tracked_Device_सूचकांक_t un_Device_सूचकांक, ETrackedDeviceProperty prop, ETrackedPropertyError * pError);
	uint64_t (OPENVR_FNTABLE_CALLTYPE *GetUint64TrackedDeviceProperty)(Tracked_Device_सूचकांक_t un_Device_सूचकांक, ETrackedDeviceProperty prop, ETrackedPropertyError * pError);
	काष्ठा HmdMatrix34_t (OPENVR_FNTABLE_CALLTYPE *GetMatrix34TrackedDeviceProperty)(Tracked_Device_सूचकांक_t un_Device_सूचकांक, ETrackedDeviceProperty prop, ETrackedPropertyError * pError);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetArrayTrackedDeviceProperty)(Tracked_Device_सूचकांक_t un_Device_सूचकांक, ETrackedDeviceProperty prop, PropertyTypeTag_t propType, व्योम * p_बफर, uint32_t un_बफर_आकार, ETrackedPropertyError * pError);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetStringTrackedDeviceProperty)(Tracked_Device_सूचकांक_t un_Device_सूचकांक, ETrackedDeviceProperty prop, अक्षर * pch_मूल्य, uint32_t un_बफर_आकार, ETrackedPropertyError * pError);
	अक्षर * (OPENVR_FNTABLE_CALLTYPE *GetPropErrorNameFromEnum)(ETrackedPropertyError error);
	bool (OPENVR_FNTABLE_CALLTYPE *Poll_अग्र_Event)(काष्ठा VREvent_t * pEvent, uint32_t uncbVREvent);
	bool (OPENVR_FNTABLE_CALLTYPE *Poll_अग्र_Event_With_Pose)(ETrackingUniverseOrigin eOrigin, काष्ठा VREvent_t * pEvent, uint32_t uncbVREvent, TrackedDevicePose_t * pTrackedDevicePose);
	अक्षर * (OPENVR_FNTABLE_CALLTYPE *GetEventTypeNameFromEnum)(EVREventType eType);
	काष्ठा HiddenAreaMesh_t (OPENVR_FNTABLE_CALLTYPE *GetHiddenAreaMesh)(EVREye eEye, EHiddenAreaMeshType type);
	bool (OPENVR_FNTABLE_CALLTYPE *GetControllerState)(Tracked_Device_सूचकांक_t un_Controller_Device_सूचकांक, VRControllerState_t * pControllerState, uint32_t un_Controller_State_आकार);
	bool (OPENVR_FNTABLE_CALLTYPE *GetControllerStateWithPose)(ETrackingUniverseOrigin eOrigin, Tracked_Device_सूचकांक_t un_Controller_Device_सूचकांक, VRControllerState_t * pControllerState, uint32_t un_Controller_State_आकार, काष्ठा TrackedDevicePose_t * pTrackedDevicePose);
	व्योम (OPENVR_FNTABLE_CALLTYPE *TriggerHapticPulse)(Tracked_Device_सूचकांक_t un_Controller_Device_सूचकांक, uint32_t unAxisId, अचिन्हित लघु usDurationMicroSec);
	अक्षर * (OPENVR_FNTABLE_CALLTYPE *GetButtonIdNameFromEnum)(EVRButtonId eButtonId);
	अक्षर * (OPENVR_FNTABLE_CALLTYPE *GetControllerAxisTypeNameFromEnum)(EVRControllerAxisType eAxisType);
	bool (OPENVR_FNTABLE_CALLTYPE *Is_निवेश_Available)();
	bool (OPENVR_FNTABLE_CALLTYPE *IsSteamVRDrawingControllers)();
	bool (OPENVR_FNTABLE_CALLTYPE *ShouldApplicationPause)();
	bool (OPENVR_FNTABLE_CALLTYPE *ShouldApplicationReduceRenderingWork)();
	EVRFirmwareError (OPENVR_FNTABLE_CALLTYPE *PerformFirmwareUpdate)(Tracked_Device_सूचकांक_t un_Device_सूचकांक);
	व्योम (OPENVR_FNTABLE_CALLTYPE *AcknowledgeQuit_Exiting)();
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetAppContainerFilePaths)(अक्षर * pch_बफर, uint32_t un_बफर_आकार);
	अक्षर * (OPENVR_FNTABLE_CALLTYPE *GetRuntimeVersion)();
};

काष्ठा VR_IVRExtendedDisplay_FnTable
{
	व्योम (OPENVR_FNTABLE_CALLTYPE *GetWindowBounds)(int32_t * pnX, int32_t * pnY, uint32_t * pnWidth, uint32_t * pnHeight);
	व्योम (OPENVR_FNTABLE_CALLTYPE *GetEyeOutputViewport)(EVREye eEye, uint32_t * pnX, uint32_t * pnY, uint32_t * pnWidth, uint32_t * pnHeight);
	व्योम (OPENVR_FNTABLE_CALLTYPE *GetDXGIOutputInfo)(int32_t * pn_Adapter_सूचकांक, int32_t * pn_Adapter_Output_सूचकांक);
};

काष्ठा VR_IVRTrackedCamera_FnTable
{
	अक्षर * (OPENVR_FNTABLE_CALLTYPE *GetCameraErrorNameFromEnum)(EVRTrackedCameraError eCameraError);
	EVRTrackedCameraError (OPENVR_FNTABLE_CALLTYPE *HasCamera)(Tracked_Device_सूचकांक_t n_Device_सूचकांक, bool * pHasCamera);
	EVRTrackedCameraError (OPENVR_FNTABLE_CALLTYPE *Get_Camera_Frame_आकार)(Tracked_Device_सूचकांक_t n_Device_सूचकांक, EVRTrackedCameraFrameType eFrameType, uint32_t * pnWidth, uint32_t * pnHeight, uint32_t * pn_Frame_बफर_आकार);
	EVRTrackedCameraError (OPENVR_FNTABLE_CALLTYPE *GetCameraIntrinsics)(Tracked_Device_सूचकांक_t n_Device_सूचकांक, uint32_t n_Camera_सूचकांक, EVRTrackedCameraFrameType eFrameType, HmdVector2_t * p_Focal_लंबाई, HmdVector2_t * pCenter);
	EVRTrackedCameraError (OPENVR_FNTABLE_CALLTYPE *GetCameraProjection)(Tracked_Device_सूचकांक_t n_Device_सूचकांक, uint32_t n_Camera_सूचकांक, EVRTrackedCameraFrameType eFrameType, भग्न flZNear, भग्न flZFar, HmdMatrix44_t * pProjection);
	EVRTrackedCameraError (OPENVR_FNTABLE_CALLTYPE *AcquireVideoStreamingService)(Tracked_Device_सूचकांक_t n_Device_सूचकांक, TrackedCameraHandle_t * pHandle);
	EVRTrackedCameraError (OPENVR_FNTABLE_CALLTYPE *ReleaseVideoStreamingService)(TrackedCameraHandle_t hTrackedCamera);
	EVRTrackedCameraError (OPENVR_FNTABLE_CALLTYPE *Get_Video_Stream_Frame_बफर)(TrackedCameraHandle_t hTrackedCamera, EVRTrackedCameraFrameType eFrameType, व्योम * p_Frame_बफर, uint32_t n_Frame_बफर_आकार, CameraVideoStreamFrameHeader_t * pFrameHeader, uint32_t n_Frame_Header_आकार);
	EVRTrackedCameraError (OPENVR_FNTABLE_CALLTYPE *Get_Video_Stream_Texture_आकार)(Tracked_Device_सूचकांक_t n_Device_सूचकांक, EVRTrackedCameraFrameType eFrameType, VRTextureBounds_t * pTextureBounds, uint32_t * pnWidth, uint32_t * pnHeight);
	EVRTrackedCameraError (OPENVR_FNTABLE_CALLTYPE *GetVideoStreamTextureD3D11)(TrackedCameraHandle_t hTrackedCamera, EVRTrackedCameraFrameType eFrameType, व्योम * pD3D11DeviceOrResource, व्योम ** ppD3D11ShaderResourceView, CameraVideoStreamFrameHeader_t * pFrameHeader, uint32_t n_Frame_Header_आकार);
	EVRTrackedCameraError (OPENVR_FNTABLE_CALLTYPE *GetVideoStreamTextureGL)(TrackedCameraHandle_t hTrackedCamera, EVRTrackedCameraFrameType eFrameType, glUInt_t * pglTextureId, CameraVideoStreamFrameHeader_t * pFrameHeader, uint32_t n_Frame_Header_आकार);
	EVRTrackedCameraError (OPENVR_FNTABLE_CALLTYPE *ReleaseVideoStreamTextureGL)(TrackedCameraHandle_t hTrackedCamera, glUInt_t glTextureId);
	व्योम (OPENVR_FNTABLE_CALLTYPE *SetCameraTrackingSpace)(ETrackingUniverseOrigin eUniverse);
	ETrackingUniverseOrigin (OPENVR_FNTABLE_CALLTYPE *GetCameraTrackingSpace)();
};

काष्ठा VR_IVRApplications_FnTable
{
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *AddApplicationManifest)(अक्षर * pchApplicationManifestFullPath, bool bTemporary);
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *RemoveApplicationManifest)(अक्षर * pchApplicationManifestFullPath);
	bool (OPENVR_FNTABLE_CALLTYPE *IsApplicationInstalled)(अक्षर * pch_App_कुंजी);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *Get_Application_गिनती)();
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *Get_Application_कुंजी_By_सूचकांक)(uint32_t un_Application_सूचकांक, अक्षर * pch_App_कुंजी_बफर, uint32_t un_App_कुंजी_बफर_Len);
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *Get_Application_कुंजी_By_Process_Id)(uint32_t unProcessId, अक्षर * pch_App_कुंजी_बफर, uint32_t un_App_कुंजी_बफर_Len);
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *LaunchApplication)(अक्षर * pch_App_कुंजी);
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *LaunchTemplateApplication)(अक्षर * pch_Template_App_कुंजी, अक्षर * pch_New_App_कुंजी, काष्ठा App_Override_कुंजियाँ_t * p_कुंजियाँ, uint32_t un_कुंजियाँ);
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *LaunchApplicationFromMimeType)(अक्षर * pchMimeType, अक्षर * pchArgs);
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *LaunchDashboardOverlay)(अक्षर * pch_App_कुंजी);
	bool (OPENVR_FNTABLE_CALLTYPE *CancelApplicationLaunch)(अक्षर * pch_App_कुंजी);
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *IdentifyApplication)(uint32_t unProcessId, अक्षर * pch_App_कुंजी);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetApplicationProcessId)(अक्षर * pch_App_कुंजी);
	अक्षर * (OPENVR_FNTABLE_CALLTYPE *GetApplicationsErrorNameFromEnum)(EVRApplicationError error);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetApplicationPropertyString)(अक्षर * pch_App_कुंजी, EVRApplicationProperty eProperty, अक्षर * pch_Property_मूल्य_बफर, uint32_t un_Property_मूल्य_बफर_Len, EVRApplicationError * peError);
	bool (OPENVR_FNTABLE_CALLTYPE *GetApplicationPropertyBool)(अक्षर * pch_App_कुंजी, EVRApplicationProperty eProperty, EVRApplicationError * peError);
	uint64_t (OPENVR_FNTABLE_CALLTYPE *GetApplicationPropertyUint64)(अक्षर * pch_App_कुंजी, EVRApplicationProperty eProperty, EVRApplicationError * peError);
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *SetApplicationAutoLaunch)(अक्षर * pch_App_कुंजी, bool bAutoLaunch);
	bool (OPENVR_FNTABLE_CALLTYPE *GetApplicationAutoLaunch)(अक्षर * pch_App_कुंजी);
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *SetDefaultApplicationForMimeType)(अक्षर * pch_App_कुंजी, अक्षर * pchMimeType);
	bool (OPENVR_FNTABLE_CALLTYPE *GetDefaultApplicationForMimeType)(अक्षर * pchMimeType, अक्षर * pch_App_कुंजी_बफर, uint32_t un_App_कुंजी_बफर_Len);
	bool (OPENVR_FNTABLE_CALLTYPE *GetApplicationSupportedMimeTypes)(अक्षर * pch_App_कुंजी, अक्षर * pch_Mime_Types_बफर, uint32_t un_Mime_Types_बफर);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetApplicationsThatSupportMimeType)(अक्षर * pchMimeType, अक्षर * pch_App_कुंजियाँ_That_Support_बफर, uint32_t un_App_कुंजियाँ_That_Support_बफर);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetApplicationLaunchArguments)(uint32_t unHandle, अक्षर * pchArgs, uint32_t unArgs);
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *GetStartingApplication)(अक्षर * pch_App_कुंजी_बफर, uint32_t un_App_कुंजी_बफर_Len);
	EVRSceneApplicationState (OPENVR_FNTABLE_CALLTYPE *GetSceneApplicationState)();
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *PerformApplicationPrelaunchCheck)(अक्षर * pch_App_कुंजी);
	अक्षर * (OPENVR_FNTABLE_CALLTYPE *GetSceneApplicationStateNameFromEnum)(EVRSceneApplicationState state);
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *LaunchInternalProcess)(अक्षर * pch_द्विआधारी_Path, अक्षर * pchArguments, अक्षर * pchWorkingDirectory);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetCurrentSceneProcessId)();
};

काष्ठा VR_IVRChaperone_FnTable
{
	ChaperoneCalibrationState (OPENVR_FNTABLE_CALLTYPE *GetCalibrationState)();
	bool (OPENVR_FNTABLE_CALLTYPE *Get_Play_Area_आकार)(भग्न * p_आकार_X, भग्न * p_आकार_Z);
	bool (OPENVR_FNTABLE_CALLTYPE *GetPlayAreaRect)(काष्ठा HmdQuad_t * rect);
	व्योम (OPENVR_FNTABLE_CALLTYPE *ReloadInfo)();
	व्योम (OPENVR_FNTABLE_CALLTYPE *SetSceneColor)(काष्ठा HmdColor_t color);
	व्योम (OPENVR_FNTABLE_CALLTYPE *GetBoundsColor)(काष्ठा HmdColor_t * pOutputColorArray, पूर्णांक n_अंक_Output_Colors, भग्न flCollisionBoundsFadeDistance, काष्ठा HmdColor_t * pOutputCameraColor);
	bool (OPENVR_FNTABLE_CALLTYPE *AreBoundsVisible)();
	व्योम (OPENVR_FNTABLE_CALLTYPE *ForceBoundsVisible)(bool bForce);
	व्योम (OPENVR_FNTABLE_CALLTYPE *ResetZeroPose)(ETrackingUniverseOrigin eTrackingUniverseOrigin);
};

काष्ठा VR_IVRChaperoneSetup_FnTable
{
	bool (OPENVR_FNTABLE_CALLTYPE *CommitWorkingCopy)(EChaperoneConfigFile configFile);
	व्योम (OPENVR_FNTABLE_CALLTYPE *RevertWorkingCopy)();
	bool (OPENVR_FNTABLE_CALLTYPE *Get_Working_Play_Area_आकार)(भग्न * p_आकार_X, भग्न * p_आकार_Z);
	bool (OPENVR_FNTABLE_CALLTYPE *GetWorkingPlayAreaRect)(काष्ठा HmdQuad_t * rect);
	bool (OPENVR_FNTABLE_CALLTYPE *GetWorkingCollisionBoundsInfo)(काष्ठा HmdQuad_t * p_Quads_बफर, uint32_t * pun_Quads_गिनती);
	bool (OPENVR_FNTABLE_CALLTYPE *GetLiveCollisionBoundsInfo)(काष्ठा HmdQuad_t * p_Quads_बफर, uint32_t * pun_Quads_गिनती);
	bool (OPENVR_FNTABLE_CALLTYPE *GetWorkingSeatedZeroPoseToRawTrackingPose)(काष्ठा HmdMatrix34_t * pmatSeatedZeroPoseToRawTrackingPose);
	bool (OPENVR_FNTABLE_CALLTYPE *GetWorkingStandingZeroPoseToRawTrackingPose)(काष्ठा HmdMatrix34_t * pmatStandingZeroPoseToRawTrackingPose);
	व्योम (OPENVR_FNTABLE_CALLTYPE *Set_Working_Play_Area_आकार)(भग्न आकार_X, भग्न आकार_Z);
	व्योम (OPENVR_FNTABLE_CALLTYPE *SetWorkingCollisionBoundsInfo)(काष्ठा HmdQuad_t * p_Quads_बफर, uint32_t un_Quads_गिनती);
	व्योम (OPENVR_FNTABLE_CALLTYPE *SetWorkingPerimeter)(काष्ठा HmdVector2_t * p_Point_बफर, uint32_t un_Point_गिनती);
	व्योम (OPENVR_FNTABLE_CALLTYPE *SetWorkingSeatedZeroPoseToRawTrackingPose)(काष्ठा HmdMatrix34_t * pMatSeatedZeroPoseToRawTrackingPose);
	व्योम (OPENVR_FNTABLE_CALLTYPE *SetWorkingStandingZeroPoseToRawTrackingPose)(काष्ठा HmdMatrix34_t * pMatStandingZeroPoseToRawTrackingPose);
	व्योम (OPENVR_FNTABLE_CALLTYPE *ReloadFromDisk)(EChaperoneConfigFile configFile);
	bool (OPENVR_FNTABLE_CALLTYPE *GetLiveSeatedZeroPoseToRawTrackingPose)(काष्ठा HmdMatrix34_t * pmatSeatedZeroPoseToRawTrackingPose);
	bool (OPENVR_FNTABLE_CALLTYPE *Export_Live_To_बफर)(अक्षर * p_बफर, uint32_t * pn_बफर_लंबाई);
	bool (OPENVR_FNTABLE_CALLTYPE *Import_From_बफर_To_Working)(अक्षर * p_बफर, uint32_t nImportFlags);
	व्योम (OPENVR_FNTABLE_CALLTYPE *ShowWorkingSetPreview)();
	व्योम (OPENVR_FNTABLE_CALLTYPE *HideWorkingSetPreview)();
	व्योम (OPENVR_FNTABLE_CALLTYPE *RoomSetupStarting)();
};

काष्ठा VR_IVRCompositor_FnTable
{
	व्योम (OPENVR_FNTABLE_CALLTYPE *SetTrackingSpace)(ETrackingUniverseOrigin eOrigin);
	ETrackingUniverseOrigin (OPENVR_FNTABLE_CALLTYPE *GetTrackingSpace)();
	EVRCompositorError (OPENVR_FNTABLE_CALLTYPE *WaitGetPoses)(काष्ठा TrackedDevicePose_t * pRenderPoseArray, uint32_t un_Render_Pose_Array_गिनती, काष्ठा TrackedDevicePose_t * pGamePoseArray, uint32_t un_Game_Pose_Array_गिनती);
	EVRCompositorError (OPENVR_FNTABLE_CALLTYPE *GetLastPoses)(काष्ठा TrackedDevicePose_t * pRenderPoseArray, uint32_t un_Render_Pose_Array_गिनती, काष्ठा TrackedDevicePose_t * pGamePoseArray, uint32_t un_Game_Pose_Array_गिनती);
	EVRCompositorError (OPENVR_FNTABLE_CALLTYPE *Get_Last_Pose_For_Tracked_Device_सूचकांक)(Tracked_Device_सूचकांक_t un_Device_सूचकांक, काष्ठा TrackedDevicePose_t * pOutputPose, काष्ठा TrackedDevicePose_t * pOutputGamePose);
	EVRCompositorError (OPENVR_FNTABLE_CALLTYPE *Submit)(EVREye eEye, काष्ठा Texture_t * pTexture, काष्ठा VRTextureBounds_t * pBounds, EVRSubmitFlags nSubmitFlags);
	व्योम (OPENVR_FNTABLE_CALLTYPE *ClearLastSubmittedFrame)();
	व्योम (OPENVR_FNTABLE_CALLTYPE *PostPresentHandoff)();
	bool (OPENVR_FNTABLE_CALLTYPE *GetFrameTiming)(काष्ठा Compositor_FrameTiming * pTiming, uint32_t unFramesAgo);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetFrameTimings)(काष्ठा Compositor_FrameTiming * pTiming, uint32_t nFrames);
	भग्न (OPENVR_FNTABLE_CALLTYPE *GetFrameTimeRemaining)();
	व्योम (OPENVR_FNTABLE_CALLTYPE *GetCumulativeStats)(काष्ठा Compositor_CumulativeStats * pStats, uint32_t n_Stats_आकार_In_Bytes);
	व्योम (OPENVR_FNTABLE_CALLTYPE *FadeToColor)(भग्न fSeconds, भग्न fRed, भग्न fGreen, भग्न fBlue, भग्न fAlpha, bool bBackground);
	काष्ठा HmdColor_t (OPENVR_FNTABLE_CALLTYPE *GetCurrentFadeColor)(bool bBackground);
	व्योम (OPENVR_FNTABLE_CALLTYPE *FadeGrid)(भग्न fSeconds, bool bFadeGridIn);
	भग्न (OPENVR_FNTABLE_CALLTYPE *GetCurrentGridAlpha)();
	EVRCompositorError (OPENVR_FNTABLE_CALLTYPE *SetSkyboxOverride)(काष्ठा Texture_t * pTextures, uint32_t un_Texture_गिनती);
	व्योम (OPENVR_FNTABLE_CALLTYPE *ClearSkyboxOverride)();
	व्योम (OPENVR_FNTABLE_CALLTYPE *CompositorBringToFront)();
	व्योम (OPENVR_FNTABLE_CALLTYPE *CompositorGoToBack)();
	व्योम (OPENVR_FNTABLE_CALLTYPE *CompositorQuit)();
	bool (OPENVR_FNTABLE_CALLTYPE *IsFullscreen)();
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetCurrentSceneFocusProcess)();
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetLastFrameRenderer)();
	bool (OPENVR_FNTABLE_CALLTYPE *CanRenderScene)();
	व्योम (OPENVR_FNTABLE_CALLTYPE *ShowMirrorWindow)();
	व्योम (OPENVR_FNTABLE_CALLTYPE *HideMirrorWindow)();
	bool (OPENVR_FNTABLE_CALLTYPE *IsMirrorWindowVisible)();
	व्योम (OPENVR_FNTABLE_CALLTYPE *CompositorDumpImages)();
	bool (OPENVR_FNTABLE_CALLTYPE *Should_App_Render_With_निचला_Resources)();
	व्योम (OPENVR_FNTABLE_CALLTYPE *ForceInterleavedReprojectionOn)(bool bOverride);
	व्योम (OPENVR_FNTABLE_CALLTYPE *ForceReconnectProcess)();
	व्योम (OPENVR_FNTABLE_CALLTYPE *SuspendRendering)(bool bSuspend);
	EVRCompositorError (OPENVR_FNTABLE_CALLTYPE *GetMirrorTextureD3D11)(EVREye eEye, व्योम * pD3D11DeviceOrResource, व्योम ** ppD3D11ShaderResourceView);
	व्योम (OPENVR_FNTABLE_CALLTYPE *ReleaseMirrorTextureD3D11)(व्योम * pD3D11ShaderResourceView);
	EVRCompositorError (OPENVR_FNTABLE_CALLTYPE *GetMirrorTextureGL)(EVREye eEye, glUInt_t * pglTextureId, glSharedTextureHandle_t * pglSharedTextureHandle);
	bool (OPENVR_FNTABLE_CALLTYPE *ReleaseSharedGLTexture)(glUInt_t glTextureId, glSharedTextureHandle_t glSharedTextureHandle);
	व्योम (OPENVR_FNTABLE_CALLTYPE *LockGLSharedTextureForAccess)(glSharedTextureHandle_t glSharedTextureHandle);
	व्योम (OPENVR_FNTABLE_CALLTYPE *UnlockGLSharedTextureForAccess)(glSharedTextureHandle_t glSharedTextureHandle);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetVulkanInstanceExtensionsRequired)(अक्षर * pch_मूल्य, uint32_t un_बफर_आकार);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetVulkanDeviceExtensionsRequired)(काष्ठा VkPhysicalDevice_T * pPhysicalDevice, अक्षर * pch_मूल्य, uint32_t un_बफर_आकार);
	व्योम (OPENVR_FNTABLE_CALLTYPE *SetExplicitTimingMode)(EVRCompositorTimingMode eTimingMode);
	EVRCompositorError (OPENVR_FNTABLE_CALLTYPE *Submit_Explicit_Timing_तथ्य)();
	bool (OPENVR_FNTABLE_CALLTYPE *IsMotionSmoothingEnabled)();
	bool (OPENVR_FNTABLE_CALLTYPE *IsMotionSmoothingSupported)();
	bool (OPENVR_FNTABLE_CALLTYPE *IsCurrentSceneFocusAppLoading)();
	EVRCompositorError (OPENVR_FNTABLE_CALLTYPE *SetStageOverride_Async)(अक्षर * pchRenderModelPath, काष्ठा HmdMatrix34_t * pTransform, काष्ठा Compositor_StageRenderSettings * pRenderSettings, uint32_t n_आकार_Of_Render_Settings);
	व्योम (OPENVR_FNTABLE_CALLTYPE *ClearStageOverride)();
	bool (OPENVR_FNTABLE_CALLTYPE *GetCompositorBenchmarkResults)(काष्ठा Compositor_BenchmarkResults * pBenchmarkResults, uint32_t n_आकार_Of_Benchmark_Results);
	EVRCompositorError (OPENVR_FNTABLE_CALLTYPE *GetLastPosePredictionIDs)(uint32_t * pRenderPosePredictionID, uint32_t * pGamePosePredictionID);
	EVRCompositorError (OPENVR_FNTABLE_CALLTYPE *GetPosesForFrame)(uint32_t unPosePredictionID, काष्ठा TrackedDevicePose_t * pPoseArray, uint32_t un_Pose_Array_गिनती);
};

काष्ठा VR_IVROverlay_FnTable
{
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *FindOverlay)(अक्षर * pch_Overlay_कुंजी, VROverlayHandle_t * pOverlayHandle);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *CreateOverlay)(अक्षर * pch_Overlay_कुंजी, अक्षर * pchOverlayName, VROverlayHandle_t * pOverlayHandle);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *DestroyOverlay)(VROverlayHandle_t ulOverlayHandle);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *Get_Overlay_कुंजी)(VROverlayHandle_t ulOverlayHandle, अक्षर * pch_मूल्य, uint32_t un_बफर_आकार, EVROverlayError * pError);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetOverlayName)(VROverlayHandle_t ulOverlayHandle, अक्षर * pch_मूल्य, uint32_t un_बफर_आकार, EVROverlayError * pError);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *SetOverlayName)(VROverlayHandle_t ulOverlayHandle, अक्षर * pchName);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *Get_Overlay_Image_तथ्य)(VROverlayHandle_t ulOverlayHandle, व्योम * pv_बफर, uint32_t un_बफर_आकार, uint32_t * punWidth, uint32_t * punHeight);
	अक्षर * (OPENVR_FNTABLE_CALLTYPE *GetOverlayErrorNameFromEnum)(EVROverlayError error);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *SetOverlayRenderingPid)(VROverlayHandle_t ulOverlayHandle, uint32_t unPID);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetOverlayRenderingPid)(VROverlayHandle_t ulOverlayHandle);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *SetOverlayFlag)(VROverlayHandle_t ulOverlayHandle, VROverlayFlags eOverlayFlag, bool bEnabled);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayFlag)(VROverlayHandle_t ulOverlayHandle, VROverlayFlags eOverlayFlag, bool * pbEnabled);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayFlags)(VROverlayHandle_t ulOverlayHandle, uint32_t * pFlags);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *SetOverlayColor)(VROverlayHandle_t ulOverlayHandle, भग्न fRed, भग्न fGreen, भग्न fBlue);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayColor)(VROverlayHandle_t ulOverlayHandle, भग्न * pfRed, भग्न * pfGreen, भग्न * pfBlue);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *SetOverlayAlpha)(VROverlayHandle_t ulOverlayHandle, भग्न fAlpha);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayAlpha)(VROverlayHandle_t ulOverlayHandle, भग्न * pfAlpha);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *SetOverlayTexelAspect)(VROverlayHandle_t ulOverlayHandle, भग्न fTexelAspect);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayTexelAspect)(VROverlayHandle_t ulOverlayHandle, भग्न * pfTexelAspect);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *SetOverlaySortOrder)(VROverlayHandle_t ulOverlayHandle, uint32_t unSortOrder);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlaySortOrder)(VROverlayHandle_t ulOverlayHandle, uint32_t * punSortOrder);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *SetOverlayWidthInMeters)(VROverlayHandle_t ulOverlayHandle, भग्न fWidthInMeters);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayWidthInMeters)(VROverlayHandle_t ulOverlayHandle, भग्न * pfWidthInMeters);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *SetOverlayCurvature)(VROverlayHandle_t ulOverlayHandle, भग्न fCurvature);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayCurvature)(VROverlayHandle_t ulOverlayHandle, भग्न * pfCurvature);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *SetOverlayPreCurvePitch)(VROverlayHandle_t ulOverlayHandle, भग्न fRadians);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayPreCurvePitch)(VROverlayHandle_t ulOverlayHandle, भग्न * pfRadians);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *SetOverlayTextureColorSpace)(VROverlayHandle_t ulOverlayHandle, EColorSpace eTextureColorSpace);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayTextureColorSpace)(VROverlayHandle_t ulOverlayHandle, EColorSpace * peTextureColorSpace);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *SetOverlayTextureBounds)(VROverlayHandle_t ulOverlayHandle, काष्ठा VRTextureBounds_t * pOverlayTextureBounds);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayTextureBounds)(VROverlayHandle_t ulOverlayHandle, काष्ठा VRTextureBounds_t * pOverlayTextureBounds);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayTransformType)(VROverlayHandle_t ulOverlayHandle, VROverlayTransformType * peTransformType);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *SetOverlayTransformAbsolute)(VROverlayHandle_t ulOverlayHandle, ETrackingUniverseOrigin eTrackingOrigin, काष्ठा HmdMatrix34_t * pmatTrackingOriginToOverlayTransform);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayTransformAbsolute)(VROverlayHandle_t ulOverlayHandle, ETrackingUniverseOrigin * peTrackingOrigin, काष्ठा HmdMatrix34_t * pmatTrackingOriginToOverlayTransform);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *SetOverlayTransformTrackedDeviceRelative)(VROverlayHandle_t ulOverlayHandle, Tracked_Device_सूचकांक_t unTrackedDevice, काष्ठा HmdMatrix34_t * pmatTrackedDeviceToOverlayTransform);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayTransformTrackedDeviceRelative)(VROverlayHandle_t ulOverlayHandle, Tracked_Device_सूचकांक_t * punTrackedDevice, काष्ठा HmdMatrix34_t * pmatTrackedDeviceToOverlayTransform);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *SetOverlayTransformTrackedDeviceComponent)(VROverlayHandle_t ulOverlayHandle, Tracked_Device_सूचकांक_t un_Device_सूचकांक, अक्षर * pchComponentName);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayTransformTrackedDeviceComponent)(VROverlayHandle_t ulOverlayHandle, Tracked_Device_सूचकांक_t * pun_Device_सूचकांक, अक्षर * pchComponentName, uint32_t un_Component_Name_आकार);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayTransformOverlayRelative)(VROverlayHandle_t ulOverlayHandle, VROverlayHandle_t * ulOverlayHandleParent, काष्ठा HmdMatrix34_t * pmatParentOverlayToOverlayTransform);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *SetOverlayTransformOverlayRelative)(VROverlayHandle_t ulOverlayHandle, VROverlayHandle_t ulOverlayHandleParent, काष्ठा HmdMatrix34_t * pmatParentOverlayToOverlayTransform);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *SetOverlayTransformCursor)(VROverlayHandle_t ulCursorOverlayHandle, काष्ठा HmdVector2_t * pvHotspot);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayTransformCursor)(VROverlayHandle_t ulOverlayHandle, काष्ठा HmdVector2_t * pvHotspot);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *SetOverlayTransformProjection)(VROverlayHandle_t ulOverlayHandle, ETrackingUniverseOrigin eTrackingOrigin, काष्ठा HmdMatrix34_t * pmatTrackingOriginToOverlayTransform, काष्ठा VROverlayProjection_t * pProjection, EVREye eEye);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *ShowOverlay)(VROverlayHandle_t ulOverlayHandle);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *HideOverlay)(VROverlayHandle_t ulOverlayHandle);
	bool (OPENVR_FNTABLE_CALLTYPE *IsOverlayVisible)(VROverlayHandle_t ulOverlayHandle);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetTransformForOverlayCoordinates)(VROverlayHandle_t ulOverlayHandle, ETrackingUniverseOrigin eTrackingOrigin, काष्ठा HmdVector2_t coordinatesInOverlay, काष्ठा HmdMatrix34_t * pmatTransform);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *WaitFrameSync)(uint32_t nTimeoutMs);
	bool (OPENVR_FNTABLE_CALLTYPE *Poll_अग्र_Overlay_Event)(VROverlayHandle_t ulOverlayHandle, काष्ठा VREvent_t * pEvent, uint32_t uncbVREvent);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *Get_Overlay_निवेश_Method)(VROverlayHandle_t ulOverlayHandle, VROverlay_निवेश_Method * pe_निवेश_Method);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *Set_Overlay_निवेश_Method)(VROverlayHandle_t ulOverlayHandle, VROverlay_निवेश_Method e_निवेश_Method);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayMouseScale)(VROverlayHandle_t ulOverlayHandle, काष्ठा HmdVector2_t * pvecMouseScale);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *SetOverlayMouseScale)(VROverlayHandle_t ulOverlayHandle, काष्ठा HmdVector2_t * pvecMouseScale);
	bool (OPENVR_FNTABLE_CALLTYPE *ComputeOverlayIntersection)(VROverlayHandle_t ulOverlayHandle, काष्ठा VROverlayIntersectionParams_t * pParams, काष्ठा VROverlayIntersectionResults_t * pResults);
	bool (OPENVR_FNTABLE_CALLTYPE *IsHoverTargetOverlay)(VROverlayHandle_t ulOverlayHandle);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *SetOverlayIntersectionMask)(VROverlayHandle_t ulOverlayHandle, काष्ठा VROverlayIntersectionMaskPrimitive_t * pMaskPrimitives, uint32_t un_अंक_Mask_Primitives, uint32_t un_Primitive_आकार);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *TriggerLaserMouseHapticVibration)(VROverlayHandle_t ulOverlayHandle, भग्न fDurationSeconds, भग्न fFrequency, भग्न fAmplitude);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *SetOverlayCursor)(VROverlayHandle_t ulOverlayHandle, VROverlayHandle_t ulCursorHandle);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *SetOverlayCursorPositionOverride)(VROverlayHandle_t ulOverlayHandle, काष्ठा HmdVector2_t * pvCursor);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *ClearOverlayCursorPositionOverride)(VROverlayHandle_t ulOverlayHandle);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *SetOverlayTexture)(VROverlayHandle_t ulOverlayHandle, काष्ठा Texture_t * pTexture);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *ClearOverlayTexture)(VROverlayHandle_t ulOverlayHandle);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *SetOverlayRaw)(VROverlayHandle_t ulOverlayHandle, व्योम * pv_बफर, uint32_t unWidth, uint32_t unHeight, uint32_t unBytesPerPixel);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *SetOverlayFromFile)(VROverlayHandle_t ulOverlayHandle, अक्षर * pchFilePath);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayTexture)(VROverlayHandle_t ulOverlayHandle, व्योम ** pNativeTextureHandle, व्योम * pNativeTextureRef, uint32_t * pWidth, uint32_t * pHeight, uint32_t * pNativeFormat, ETextureType * pAPIType, EColorSpace * pColorSpace, काष्ठा VRTextureBounds_t * pTextureBounds);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *ReleaseNativeOverlayHandle)(VROverlayHandle_t ulOverlayHandle, व्योम * pNativeTextureHandle);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *Get_Overlay_Texture_आकार)(VROverlayHandle_t ulOverlayHandle, uint32_t * pWidth, uint32_t * pHeight);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *CreateDashboardOverlay)(अक्षर * pch_Overlay_कुंजी, अक्षर * pchOverlayFriendlyName, VROverlayHandle_t * pMainHandle, VROverlayHandle_t * pThumbnailHandle);
	bool (OPENVR_FNTABLE_CALLTYPE *IsDashboardVisible)();
	bool (OPENVR_FNTABLE_CALLTYPE *IsActiveDashboardOverlay)(VROverlayHandle_t ulOverlayHandle);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *SetDashboardOverlaySceneProcess)(VROverlayHandle_t ulOverlayHandle, uint32_t unProcessId);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetDashboardOverlaySceneProcess)(VROverlayHandle_t ulOverlayHandle, uint32_t * punProcessId);
	व्योम (OPENVR_FNTABLE_CALLTYPE *ShowDashboard)(अक्षर * pchOverlayToShow);
	Tracked_Device_सूचकांक_t (OPENVR_FNTABLE_CALLTYPE *GetPrimaryDashboardDevice)();
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *ShowKeyboard)(EGamepad_Text_निवेश_Mode e_निवेश_Mode, EGamepad_Text_निवेश_पंक्ति_Mode e_पंक्ति_निवेश_Mode, uint32_t unFlags, अक्षर * pchDescription, uint32_t unCharMax, अक्षर * pchExistingText, uint64_t u_User_मूल्य);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *ShowKeyboardForOverlay)(VROverlayHandle_t ulOverlayHandle, EGamepad_Text_निवेश_Mode e_निवेश_Mode, EGamepad_Text_निवेश_पंक्ति_Mode e_पंक्ति_निवेश_Mode, uint32_t unFlags, अक्षर * pchDescription, uint32_t unCharMax, अक्षर * pchExistingText, uint64_t u_User_मूल्य);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetKeyboardText)(अक्षर * pchText, uint32_t cchText);
	व्योम (OPENVR_FNTABLE_CALLTYPE *HideKeyboard)();
	व्योम (OPENVR_FNTABLE_CALLTYPE *SetKeyboardTransformAbsolute)(ETrackingUniverseOrigin eTrackingOrigin, काष्ठा HmdMatrix34_t * pmatTrackingOriginToKeyboardTransform);
	व्योम (OPENVR_FNTABLE_CALLTYPE *SetKeyboardPositionForOverlay)(VROverlayHandle_t ulOverlayHandle, काष्ठा HmdRect2_t avoidRect);
	VRMessageOverlayResponse (OPENVR_FNTABLE_CALLTYPE *ShowMessageOverlay)(अक्षर * pchText, अक्षर * pchCaption, अक्षर * pchButton0Text, अक्षर * pchButton1Text, अक्षर * pchButton2Text, अक्षर * pchButton3Text);
	व्योम (OPENVR_FNTABLE_CALLTYPE *CloseMessageOverlay)();
};

काष्ठा VR_IVROverlayView_FnTable
{
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *AcquireOverlayView)(VROverlayHandle_t ulOverlayHandle, काष्ठा VRNativeDevice_t * pNativeDevice, काष्ठा VROverlayView_t * pOverlayView, uint32_t un_Overlay_View_आकार);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *ReleaseOverlayView)(काष्ठा VROverlayView_t * pOverlayView);
	व्योम (OPENVR_FNTABLE_CALLTYPE *PostOverlayEvent)(VROverlayHandle_t ulOverlayHandle, काष्ठा VREvent_t * pvrEvent);
	bool (OPENVR_FNTABLE_CALLTYPE *IsViewingPermitted)(VROverlayHandle_t ulOverlayHandle);
};

काष्ठा VR_IVRHeadsetView_FnTable
{
	व्योम (OPENVR_FNTABLE_CALLTYPE *Set_Headset_View_आकार)(uint32_t nWidth, uint32_t nHeight);
	व्योम (OPENVR_FNTABLE_CALLTYPE *Get_Headset_View_आकार)(uint32_t * pnWidth, uint32_t * pnHeight);
	व्योम (OPENVR_FNTABLE_CALLTYPE *SetHeadsetViewMode)(HeadsetViewMode_t eHeadsetViewMode);
	HeadsetViewMode_t (OPENVR_FNTABLE_CALLTYPE *GetHeadsetViewMode)();
	व्योम (OPENVR_FNTABLE_CALLTYPE *SetHeadsetViewCropped)(bool bCropped);
	bool (OPENVR_FNTABLE_CALLTYPE *GetHeadsetViewCropped)();
	भग्न (OPENVR_FNTABLE_CALLTYPE *GetHeadsetViewAspectRatio)();
	व्योम (OPENVR_FNTABLE_CALLTYPE *SetHeadsetViewBlendRange)(भग्न flStartPct, भग्न flEndPct);
	व्योम (OPENVR_FNTABLE_CALLTYPE *GetHeadsetViewBlendRange)(भग्न * pStartPct, भग्न * pEndPct);
};

काष्ठा VR_IVRRenderModels_FnTable
{
	EVRRenderModelError (OPENVR_FNTABLE_CALLTYPE *LoadRenderModel_Async)(अक्षर * pchRenderModelName, काष्ठा RenderModel_t ** ppRenderModel);
	व्योम (OPENVR_FNTABLE_CALLTYPE *FreeRenderModel)(काष्ठा RenderModel_t * pRenderModel);
	EVRRenderModelError (OPENVR_FNTABLE_CALLTYPE *LoadTexture_Async)(TextureID_t textureId, काष्ठा RenderModel_TextureMap_t ** ppTexture);
	व्योम (OPENVR_FNTABLE_CALLTYPE *FreeTexture)(काष्ठा RenderModel_TextureMap_t * pTexture);
	EVRRenderModelError (OPENVR_FNTABLE_CALLTYPE *LoadTextureD3D11_Async)(TextureID_t textureId, व्योम * pD3D11Device, व्योम ** ppD3D11Texture2D);
	EVRRenderModelError (OPENVR_FNTABLE_CALLTYPE *LoadIntoTextureD3D11_Async)(TextureID_t textureId, व्योम * pDstTexture);
	व्योम (OPENVR_FNTABLE_CALLTYPE *FreeTextureD3D11)(व्योम * pD3D11Texture2D);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetRenderModelName)(uint32_t un_Render_Model_सूचकांक, अक्षर * pchRenderModelName, uint32_t unRenderModelNameLen);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *Get_Render_Model_गिनती)();
	uint32_t (OPENVR_FNTABLE_CALLTYPE *Get_Component_गिनती)(अक्षर * pchRenderModelName);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetComponentName)(अक्षर * pchRenderModelName, uint32_t un_Component_सूचकांक, अक्षर * pchComponentName, uint32_t unComponentNameLen);
	uint64_t (OPENVR_FNTABLE_CALLTYPE *GetComponentButtonMask)(अक्षर * pchRenderModelName, अक्षर * pchComponentName);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetComponentRenderModelName)(अक्षर * pchRenderModelName, अक्षर * pchComponentName, अक्षर * pchComponentRenderModelName, uint32_t unComponentRenderModelNameLen);
	bool (OPENVR_FNTABLE_CALLTYPE *GetComponentStateForDevicePath)(अक्षर * pchRenderModelName, अक्षर * pchComponentName, VRInput_मूल्य_Handle_t devicePath, RenderModel_ControllerMode_State_t * pState, RenderModel_ComponentState_t * pComponentState);
	bool (OPENVR_FNTABLE_CALLTYPE *GetComponentState)(अक्षर * pchRenderModelName, अक्षर * pchComponentName, VRControllerState_t * pControllerState, काष्ठा RenderModel_ControllerMode_State_t * pState, काष्ठा RenderModel_ComponentState_t * pComponentState);
	bool (OPENVR_FNTABLE_CALLTYPE *RenderModelHasComponent)(अक्षर * pchRenderModelName, अक्षर * pchComponentName);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetRenderModelThumbnailURL)(अक्षर * pchRenderModelName, अक्षर * pchThumbnailURL, uint32_t unThumbnailURLLen, EVRRenderModelError * peError);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetRenderModelOriginalPath)(अक्षर * pchRenderModelName, अक्षर * pchOriginalPath, uint32_t unOriginalPathLen, EVRRenderModelError * peError);
	अक्षर * (OPENVR_FNTABLE_CALLTYPE *GetRenderModelErrorNameFromEnum)(EVRRenderModelError error);
};

काष्ठा VR_IVRNotifications_FnTable
{
	EVRNotificationError (OPENVR_FNTABLE_CALLTYPE *CreateNotification)(VROverlayHandle_t ulOverlayHandle, uint64_t ul_User_मूल्य, EVRNotificationType type, अक्षर * pchText, EVRNotificationStyle style, काष्ठा NotificationBitmap_t * pImage, VRNotificationId * pNotificationId);
	EVRNotificationError (OPENVR_FNTABLE_CALLTYPE *RemoveNotification)(VRNotificationId notificationId);
};

काष्ठा VR_IVRSettings_FnTable
{
	अक्षर * (OPENVR_FNTABLE_CALLTYPE *GetSettingsErrorNameFromEnum)(EVRSettingsError eError);
	व्योम (OPENVR_FNTABLE_CALLTYPE *SetBool)(अक्षर * pchSection, अक्षर * pch_Settings_कुंजी, bool b_मूल्य, EVRSettingsError * peError);
	व्योम (OPENVR_FNTABLE_CALLTYPE *SetInt32)(अक्षर * pchSection, अक्षर * pch_Settings_कुंजी, int32_t n_मूल्य, EVRSettingsError * peError);
	व्योम (OPENVR_FNTABLE_CALLTYPE *SetFloat)(अक्षर * pchSection, अक्षर * pch_Settings_कुंजी, भग्न fl_मूल्य, EVRSettingsError * peError);
	व्योम (OPENVR_FNTABLE_CALLTYPE *SetString)(अक्षर * pchSection, अक्षर * pch_Settings_कुंजी, अक्षर * pch_मूल्य, EVRSettingsError * peError);
	bool (OPENVR_FNTABLE_CALLTYPE *GetBool)(अक्षर * pchSection, अक्षर * pch_Settings_कुंजी, EVRSettingsError * peError);
	int32_t (OPENVR_FNTABLE_CALLTYPE *GetInt32)(अक्षर * pchSection, अक्षर * pch_Settings_कुंजी, EVRSettingsError * peError);
	भग्न (OPENVR_FNTABLE_CALLTYPE *GetFloat)(अक्षर * pchSection, अक्षर * pch_Settings_कुंजी, EVRSettingsError * peError);
	व्योम (OPENVR_FNTABLE_CALLTYPE *GetString)(अक्षर * pchSection, अक्षर * pch_Settings_कुंजी, अक्षर * pch_मूल्य, uint32_t un_मूल्य_Len, EVRSettingsError * peError);
	व्योम (OPENVR_FNTABLE_CALLTYPE *RemoveSection)(अक्षर * pchSection, EVRSettingsError * peError);
	व्योम (OPENVR_FNTABLE_CALLTYPE *Remove_कुंजी_In_Section)(अक्षर * pchSection, अक्षर * pch_Settings_कुंजी, EVRSettingsError * peError);
};

काष्ठा VR_IVRScreenshots_FnTable
{
	EVRScreenshotError (OPENVR_FNTABLE_CALLTYPE *RequestScreenshot)(ScreenshotHandle_t * pOutScreenshotHandle, EVRScreenshotType type, अक्षर * pchPreviewFilename, अक्षर * pchVRFilename);
	EVRScreenshotError (OPENVR_FNTABLE_CALLTYPE *HookScreenshot)(EVRScreenshotType * pSupportedTypes, पूर्णांक अंक_Types);
	EVRScreenshotType (OPENVR_FNTABLE_CALLTYPE *GetScreenshotPropertyType)(ScreenshotHandle_t screenshotHandle, EVRScreenshotError * pError);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetScreenshotPropertyFilename)(ScreenshotHandle_t screenshotHandle, EVRScreenshotPropertyFilenames filenameType, अक्षर * pchFilename, uint32_t cchFilename, EVRScreenshotError * pError);
	EVRScreenshotError (OPENVR_FNTABLE_CALLTYPE *UpdateScreenshotProgress)(ScreenshotHandle_t screenshotHandle, भग्न flProgress);
	EVRScreenshotError (OPENVR_FNTABLE_CALLTYPE *TakeStereoScreenshot)(ScreenshotHandle_t * pOutScreenshotHandle, अक्षर * pchPreviewFilename, अक्षर * pchVRFilename);
	EVRScreenshotError (OPENVR_FNTABLE_CALLTYPE *SubmitScreenshot)(ScreenshotHandle_t screenshotHandle, EVRScreenshotType type, अक्षर * pchSourcePreviewFilename, अक्षर * pchSourceVRFilename);
};

काष्ठा VR_IVRResources_FnTable
{
	uint32_t (OPENVR_FNTABLE_CALLTYPE *LoadSharedResource)(अक्षर * pchResourceName, अक्षर * pch_बफर, uint32_t un_बफर_Len);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetResourceFullPath)(अक्षर * pchResourceName, अक्षर * pchResourceTypeDirectory, अक्षर * pch_Path_बफर, uint32_t un_बफर_Len);
};

काष्ठा VR_IVRDriverManager_FnTable
{
	uint32_t (OPENVR_FNTABLE_CALLTYPE *Get_Driver_गिनती)();
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetDriverName)(DriverId_t nDriver, अक्षर * pch_मूल्य, uint32_t un_बफर_आकार);
	DriverHandle_t (OPENVR_FNTABLE_CALLTYPE *GetDriverHandle)(अक्षर * pchDriverName);
	bool (OPENVR_FNTABLE_CALLTYPE *IsEnabled)(DriverId_t nDriver);
};

काष्ठा VR_IVRInput_FnTable
{
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *SetActionManifestPath)(अक्षर * pchActionManifestPath);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetActionSetHandle)(अक्षर * pchActionSetName, VRActionSetHandle_t * pHandle);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetActionHandle)(अक्षर * pchActionName, VRActionHandle_t * pHandle);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *Get_निवेश_Source_Handle)(अक्षर * pch_निवेश_Source_Path, VRInput_मूल्य_Handle_t * pHandle);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *UpdateActionState)(काष्ठा VRActiveActionSet_t * pSets, uint32_t un_आकार_Of_VRSelected_Action_Set_t, uint32_t un_Set_गिनती);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *Get_Digital_Action_तथ्य)(VRActionHandle_t action, काष्ठा निवेश_Digital_Action_तथ्य_t * p_Action_तथ्य, uint32_t un_Action_तथ्य_आकार, VRInput_मूल्य_Handle_t ulRestrictToDevice);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *Get_Analog_Action_तथ्य)(VRActionHandle_t action, काष्ठा निवेश_Analog_Action_तथ्य_t * p_Action_तथ्य, uint32_t un_Action_तथ्य_आकार, VRInput_मूल्य_Handle_t ulRestrictToDevice);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *Get_Pose_Action_तथ्य_Relative_To_Now)(VRActionHandle_t action, ETrackingUniverseOrigin eOrigin, भग्न fPredictedSecondsFromNow, काष्ठा निवेश_Pose_Action_तथ्य_t * p_Action_तथ्य, uint32_t un_Action_तथ्य_आकार, VRInput_मूल्य_Handle_t ulRestrictToDevice);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *Get_Pose_Action_तथ्य_For_अग्र_Frame)(VRActionHandle_t action, ETrackingUniverseOrigin eOrigin, काष्ठा निवेश_Pose_Action_तथ्य_t * p_Action_तथ्य, uint32_t un_Action_तथ्य_आकार, VRInput_मूल्य_Handle_t ulRestrictToDevice);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *Get_Skeletal_Action_तथ्य)(VRActionHandle_t action, काष्ठा निवेश_Skeletal_Action_तथ्य_t * p_Action_तथ्य, uint32_t un_Action_तथ्य_आकार);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetDominantHand)(ETrackedControllerRole * peDominantHand);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *SetDominantHand)(ETrackedControllerRole eDominantHand);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *Get_Bone_गिनती)(VRActionHandle_t action, uint32_t * p_Bone_गिनती);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetBoneHierarchy)(VRActionHandle_t action, Bone_सूचकांक_t * pParentIndices, uint32_t un_सूचकांक_Aray_गिनती);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetBoneName)(VRActionHandle_t action, Bone_सूचकांक_t n_Bone_सूचकांक, अक्षर * pchBoneName, uint32_t un_Name_बफर_आकार);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetSkeletalReferenceTransforms)(VRActionHandle_t action, EVRSkeletalTransformSpace eTransformSpace, EVRSkeletalReferencePose eReferencePose, काष्ठा VRBoneTransform_t * pTransformArray, uint32_t un_Transform_Array_गिनती);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetSkeletalTrackingLevel)(VRActionHandle_t action, EVRSkeletalTrackingLevel * pSkeletalTrackingLevel);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *Get_Skeletal_Bone_तथ्य)(VRActionHandle_t action, EVRSkeletalTransformSpace eTransformSpace, EVRSkeletalMotionRange eMotionRange, काष्ठा VRBoneTransform_t * pTransformArray, uint32_t un_Transform_Array_गिनती);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *Get_Skeletal_Summary_तथ्य)(VRActionHandle_t action, EVRSummaryType eSummaryType, काष्ठा VRSkeletal_Summary_तथ्य_t * p_Skeletal_Summary_तथ्य);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *Get_Skeletal_Bone_तथ्य_Compressed)(VRActionHandle_t action, EVRSkeletalMotionRange eMotionRange, व्योम * pv_Compressed_तथ्य, uint32_t un_Compressed_आकार, uint32_t * pun_Required_Compressed_आकार);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *Decompress_Skeletal_Bone_तथ्य)(व्योम * pv_Compressed_बफर, uint32_t un_Compressed_बफर_आकार, EVRSkeletalTransformSpace eTransformSpace, काष्ठा VRBoneTransform_t * pTransformArray, uint32_t un_Transform_Array_गिनती);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *TriggerHapticVibrationAction)(VRActionHandle_t action, भग्न fStartSecondsFromNow, भग्न fDurationSeconds, भग्न fFrequency, भग्न fAmplitude, VRInput_मूल्य_Handle_t ulRestrictToDevice);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetActionOrigins)(VRActionSetHandle_t actionSetHandle, VRActionHandle_t digitalActionHandle, VRInput_मूल्य_Handle_t * originsOut, uint32_t origin_Out_गिनती);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetOriginLocalizedName)(VRInput_मूल्य_Handle_t origin, अक्षर * pchNameArray, uint32_t un_Name_Array_आकार, int32_t unStringSectionsToInclude);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetOriginTrackedDeviceInfo)(VRInput_मूल्य_Handle_t origin, काष्ठा निवेश_Origin_Info_t * pOriginInfo, uint32_t un_Origin_Info_आकार);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetActionBindingInfo)(VRActionHandle_t action, काष्ठा निवेश_Binding_Info_t * pOriginInfo, uint32_t un_Binding_Info_आकार, uint32_t un_Binding_Info_गिनती, uint32_t * pun_Returned_Binding_Info_गिनती);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *ShowActionOrigins)(VRActionSetHandle_t actionSetHandle, VRActionHandle_t ulActionHandle);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *ShowBindingsForActionSet)(काष्ठा VRActiveActionSet_t * pSets, uint32_t un_आकार_Of_VRSelected_Action_Set_t, uint32_t un_Set_गिनती, VRInput_मूल्य_Handle_t originToHighlight);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetComponentStateForBinding)(अक्षर * pchRenderModelName, अक्षर * pchComponentName, काष्ठा निवेश_Binding_Info_t * pOriginInfo, uint32_t un_Binding_Info_आकार, uint32_t un_Binding_Info_गिनती, RenderModel_ComponentState_t * pComponentState);
	bool (OPENVR_FNTABLE_CALLTYPE *Is_Using_Legacy_निवेश)();
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *OpenBindingUI)(अक्षर * pch_App_कुंजी, VRActionSetHandle_t ulActionSetHandle, VRInput_मूल्य_Handle_t ulDeviceHandle, bool bShowOnDesktop);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetBindingVariant)(VRInput_मूल्य_Handle_t ulDevicePath, अक्षर * pchVariantArray, uint32_t un_Variant_Array_आकार);
};

काष्ठा VR_IVRIOBuffer_FnTable
{
	EIOBufferError (OPENVR_FNTABLE_CALLTYPE *Open)(अक्षर * pchPath, EIOBufferMode mode, uint32_t un_Element_आकार, uint32_t unElements, IOBufferHandle_t * pul_बफर);
	EIOBufferError (OPENVR_FNTABLE_CALLTYPE *Close)(IOBufferHandle_t ul_बफर);
	EIOBufferError (OPENVR_FNTABLE_CALLTYPE *Read)(IOBufferHandle_t ul_बफर, व्योम * pDst, uint32_t unBytes, uint32_t * punRead);
	EIOBufferError (OPENVR_FNTABLE_CALLTYPE *Write)(IOBufferHandle_t ul_बफर, व्योम * pSrc, uint32_t unBytes);
	PropertyContainerHandle_t (OPENVR_FNTABLE_CALLTYPE *PropertyContainer)(IOBufferHandle_t ul_बफर);
	bool (OPENVR_FNTABLE_CALLTYPE *HasReaders)(IOBufferHandle_t ul_बफर);
};

काष्ठा VR_IVRSpatialAnchors_FnTable
{
	EVRSpatialAnchorError (OPENVR_FNTABLE_CALLTYPE *CreateSpatialAnchorFromDescriptor)(अक्षर * pchDescriptor, SpatialAnchorHandle_t * pHandleOut);
	EVRSpatialAnchorError (OPENVR_FNTABLE_CALLTYPE *CreateSpatialAnchorFromPose)(Tracked_Device_सूचकांक_t un_Device_सूचकांक, ETrackingUniverseOrigin eOrigin, काष्ठा SpatialAnchorPose_t * pPose, SpatialAnchorHandle_t * pHandleOut);
	EVRSpatialAnchorError (OPENVR_FNTABLE_CALLTYPE *GetSpatialAnchorPose)(SpatialAnchorHandle_t unHandle, ETrackingUniverseOrigin eOrigin, काष्ठा SpatialAnchorPose_t * pPoseOut);
	EVRSpatialAnchorError (OPENVR_FNTABLE_CALLTYPE *GetSpatialAnchorDescriptor)(SpatialAnchorHandle_t unHandle, अक्षर * pchDescriptorOut, uint32_t * pun_Descriptor_बफर_Len_In_Out);
};

काष्ठा VR_IVRDebug_FnTable
{
	EVRDebugError (OPENVR_FNTABLE_CALLTYPE *EmitVrProfilerEvent)(अक्षर * pchMessage);
	EVRDebugError (OPENVR_FNTABLE_CALLTYPE *BeginVrProfilerEvent)(VrProfilerEventHandle_t * pHandleOut);
	EVRDebugError (OPENVR_FNTABLE_CALLTYPE *FinishVrProfilerEvent)(VrProfilerEventHandle_t hHandle, अक्षर * pchMessage);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *DriverDebugRequest)(Tracked_Device_सूचकांक_t un_Device_सूचकांक, अक्षर * pchRequest, अक्षर * pch_Response_बफर, uint32_t un_Response_बफर_आकार);
};

काष्ठा VR_IVRProperties_FnTable
{
	ETrackedPropertyError (OPENVR_FNTABLE_CALLTYPE *ReadPropertyBatch)(PropertyContainerHandle_t ulContainerHandle, काष्ठा PropertyRead_t * pBatch, uint32_t un_Batch_Entry_गिनती);
	ETrackedPropertyError (OPENVR_FNTABLE_CALLTYPE *WritePropertyBatch)(PropertyContainerHandle_t ulContainerHandle, काष्ठा PropertyWrite_t * pBatch, uint32_t un_Batch_Entry_गिनती);
	अक्षर * (OPENVR_FNTABLE_CALLTYPE *GetPropErrorNameFromEnum)(ETrackedPropertyError error);
	PropertyContainerHandle_t (OPENVR_FNTABLE_CALLTYPE *TrackedDeviceToPropertyContainer)(Tracked_Device_सूचकांक_t nDevice);
};

काष्ठा VR_IVRPaths_FnTable
{
	ETrackedPropertyError (OPENVR_FNTABLE_CALLTYPE *ReadPathBatch)(PropertyContainerHandle_t ul_मूल_Handle, काष्ठा PathRead_t * pBatch, uint32_t un_Batch_Entry_गिनती);
	ETrackedPropertyError (OPENVR_FNTABLE_CALLTYPE *WritePathBatch)(PropertyContainerHandle_t ul_मूल_Handle, काष्ठा PathWrite_t * pBatch, uint32_t un_Batch_Entry_गिनती);
	ETrackedPropertyError (OPENVR_FNTABLE_CALLTYPE *StringToHandle)(PathHandle_t * pHandle, अक्षर * pchPath);
	ETrackedPropertyError (OPENVR_FNTABLE_CALLTYPE *HandleToString)(PathHandle_t pHandle, अक्षर * pch_बफर, uint32_t un_बफर_आकार, uint32_t * pun_बफर_आकार_Used);
};

काष्ठा VR_IVRBlockQueue_FnTable
{
	EBlockQueueError (OPENVR_FNTABLE_CALLTYPE *Create)(PropertyContainerHandle_t * pulQueueHandle, अक्षर * pchPath, uint32_t un_Block_तथ्य_आकार, uint32_t un_Block_Header_आकार, uint32_t un_Block_गिनती, uint32_t unFlags);
	EBlockQueueError (OPENVR_FNTABLE_CALLTYPE *Connect)(PropertyContainerHandle_t * pulQueueHandle, अक्षर * pchPath);
	EBlockQueueError (OPENVR_FNTABLE_CALLTYPE *Destroy)(PropertyContainerHandle_t ulQueueHandle);
	EBlockQueueError (OPENVR_FNTABLE_CALLTYPE *AcquireWriteOnlyBlock)(PropertyContainerHandle_t ulQueueHandle, PropertyContainerHandle_t * pulBlockHandle, व्योम ** ppv_बफर);
	EBlockQueueError (OPENVR_FNTABLE_CALLTYPE *ReleaseWriteOnlyBlock)(PropertyContainerHandle_t ulQueueHandle, PropertyContainerHandle_t ulBlockHandle);
	EBlockQueueError (OPENVR_FNTABLE_CALLTYPE *WaitAndAcquireReadOnlyBlock)(PropertyContainerHandle_t ulQueueHandle, PropertyContainerHandle_t * pulBlockHandle, व्योम ** ppv_बफर, EBlockQueueReadType eReadType, uint32_t unTimeoutMs);
	EBlockQueueError (OPENVR_FNTABLE_CALLTYPE *AcquireReadOnlyBlock)(PropertyContainerHandle_t ulQueueHandle, PropertyContainerHandle_t * pulBlockHandle, व्योम ** ppv_बफर, EBlockQueueReadType eReadType);
	EBlockQueueError (OPENVR_FNTABLE_CALLTYPE *ReleaseReadOnlyBlock)(PropertyContainerHandle_t ulQueueHandle, PropertyContainerHandle_t ulBlockHandle);
	EBlockQueueError (OPENVR_FNTABLE_CALLTYPE *QueueHasReader)(PropertyContainerHandle_t ulQueueHandle, bool * pbHasReaders);
};


#अगर 0
// Global entry points
S_API intptr_t VR_InitInternal( EVRInitError *peError, EVRApplicationType eType );
S_API व्योम VR_ShutdownInternal();
S_API bool VR_IsHmdPresent();
S_API intptr_t VR_GetGenericInterface( स्थिर अक्षर *pchInterfaceVersion, EVRInitError *peError );
S_API bool VR_IsRuntimeInstalled();
S_API स्थिर अक्षर * VR_Get_VRInit_Error_As_प्रतीक( EVRInitError error );
S_API स्थिर अक्षर * VR_GetVRInitErrorAsEnglishDescription( EVRInitError error );
#पूर्ण_अगर

#पूर्ण_अगर // __OPENVR_API_FLAT_H__


