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

#నిర్వచితం_కాకపోతే __OPENVR_API_FLAT_H__
#నిర్వచించు __OPENVR_API_FLAT_H__
#ఒకవేళ defined( _WIN32 ) || defined( __clang__ )
#సూచన once
#అయితే_ముగింపు

#నిర్వచితమైతే __cplusplus
#నిర్వచించు EXTERN_C బాహ్య "C"
#లేకపోతే
#నిర్వచించు EXTERN_C
#అయితే_ముగింపు

#ఒకవేళ defined( _WIN32 )
#నిర్వచించు OPENVR_FNTABLE_CALLTYPE __stdcall
#లేకపోతే
#నిర్వచించు OPENVR_FNTABLE_CALLTYPE 
#అయితే_ముగింపు

// OPENVR API export macro
#ఒకవేళ defined( _WIN32 ) && !defined( _X360 )
	#ఒకవేళ defined( OPENVR_API_EXPORTS )
	#నిర్వచించు S_API EXTERN_C __declspec( dllexport )
	#లేదావేళ defined( OPENVR_API_NODLL )
	#నిర్వచించు S_API EXTERN_C
	#లేకపోతే
	#నిర్వచించు S_API బాహ్య "C" __declspec( dllimport ) 
	#అయితే_ముగింపు // OPENVR_API_EXPORTS
#లేదావేళ defined( __GNUC__ )
	#ఒకవేళ defined( OPENVR_API_EXPORTS )
	#నిర్వచించు S_API EXTERN_C __attribute__ ((visibility("default")))
	#లేకపోతే
	#నిర్వచించు S_API EXTERN_C
	#అయితే_ముగింపు // OPENVR_API_EXPORTS
#లేకపోతే // !WIN32
	#ఒకవేళ defined( OPENVR_API_EXPORTS )
	#నిర్వచించు S_API EXTERN_C
	#లేకపోతే
	#నిర్వచించు S_API EXTERN_C
	#అయితే_ముగింపు // OPENVR_API_EXPORTS
#అయితే_ముగింపు

#నిర్వచితం_కాకపోతే USE_SDL
#అన్తర్భావ <stdint.h>

#ఒకవేళ defined( __WIN32 )
రకనిర్వచనం అక్షరం bool;
#లేకపోతే
#అన్తర్భావ <stdbool.h>
#అయితే_ముగింపు
#అయితే_ముగింపు // USE_SDL

// OpenVR Constants

స్థిర స్థిరరాశి గుర్తులేని దీర్ఘ k_nDriverNone = 4294967295;
స్థిర స్థిరరాశి గుర్తులేని దీర్ఘ k_un_Max_Driver_Debug_Response_కొలత = 32768;
స్థిర స్థిరరాశి గుర్తులేని దీర్ఘ k_un_Tracked_Device_సూచీ_Hmd = 0;
స్థిర స్థిరరాశి గుర్తులేని దీర్ఘ k_un_Max_Tracked_Device_లెక్క = 64;
స్థిర స్థిరరాశి గుర్తులేని దీర్ఘ k_un_Tracked_Device_సూచీ_Other = 4294967294;
స్థిర స్థిరరాశి గుర్తులేని దీర్ఘ k_un_Tracked_Device_సూచీ_Invalid = 4294967295;
స్థిర స్థిరరాశి గుర్తులేని దీర్ఘ దీర్ఘ k_ulInvalidPropertyContainer = 0;
స్థిర స్థిరరాశి గుర్తులేని దీర్ఘ k_un_Invalid_Property_ట్యాగ్ = 0;
స్థిర స్థిరరాశి గుర్తులేని దీర్ఘ దీర్ఘ k_ulInvalidDriverHandle = 0;
స్థిర స్థిరరాశి గుర్తులేని దీర్ఘ k_un_Float_Property_ట్యాగ్ = 1;
స్థిర స్థిరరాశి గుర్తులేని దీర్ఘ k_un_Int32_Property_ట్యాగ్ = 2;
స్థిర స్థిరరాశి గుర్తులేని దీర్ఘ k_un_Uint64_Property_ట్యాగ్ = 3;
స్థిర స్థిరరాశి గుర్తులేని దీర్ఘ k_un_Bool_Property_ట్యాగ్ = 4;
స్థిర స్థిరరాశి గుర్తులేని దీర్ఘ k_un_String_Property_ట్యాగ్ = 5;
స్థిర స్థిరరాశి గుర్తులేని దీర్ఘ k_un_Error_Property_ట్యాగ్ = 6;
స్థిర స్థిరరాశి గుర్తులేని దీర్ఘ k_un_Double_Property_ట్యాగ్ = 7;
స్థిర స్థిరరాశి గుర్తులేని దీర్ఘ k_un_Hmd_Matrix34_Property_ట్యాగ్ = 20;
స్థిర స్థిరరాశి గుర్తులేని దీర్ఘ k_un_Hmd_Matrix44_Property_ట్యాగ్ = 21;
స్థిర స్థిరరాశి గుర్తులేని దీర్ఘ k_un_Hmd_Vector3_Property_ట్యాగ్ = 22;
స్థిర స్థిరరాశి గుర్తులేని దీర్ఘ k_un_Hmd_Vector4_Property_ట్యాగ్ = 23;
స్థిర స్థిరరాశి గుర్తులేని దీర్ఘ k_un_Hmd_Vector2_Property_ట్యాగ్ = 24;
స్థిర స్థిరరాశి గుర్తులేని దీర్ఘ k_un_Hmd_Quad_Property_ట్యాగ్ = 25;
స్థిర స్థిరరాశి గుర్తులేని దీర్ఘ k_un_Hidden_Area_Property_ట్యాగ్ = 30;
స్థిర స్థిరరాశి గుర్తులేని దీర్ఘ k_un_మార్గం_Handle_Info_ట్యాగ్ = 31;
స్థిర స్థిరరాశి గుర్తులేని దీర్ఘ k_un_Action_Property_ట్యాగ్ = 32;
స్థిర స్థిరరాశి గుర్తులేని దీర్ఘ k_un_ఆదానం_విలువ_Property_ట్యాగ్ = 33;
స్థిర స్థిరరాశి గుర్తులేని దీర్ఘ k_un_Wildcard_Property_ట్యాగ్ = 34;
స్థిర స్థిరరాశి గుర్తులేని దీర్ఘ k_un_Haptic_Vibration_Property_ట్యాగ్ = 35;
స్థిర స్థిరరాశి గుర్తులేని దీర్ఘ k_un_Skeleton_Property_ట్యాగ్ = 36;
స్థిర స్థిరరాశి గుర్తులేని దీర్ఘ k_un_Spatial_Anchor_Pose_Property_ట్యాగ్ = 40;
స్థిర స్థిరరాశి గుర్తులేని దీర్ఘ k_un_Json_Property_ట్యాగ్ = 41;
స్థిర స్థిరరాశి గుర్తులేని దీర్ఘ k_un_చురుకైన_Action_సమితి_Property_ట్యాగ్ = 42;
స్థిర స్థిరరాశి గుర్తులేని దీర్ఘ k_un_Open_VRInternal_Reserved_ప్రారంభం = 1000;
స్థిర స్థిరరాశి గుర్తులేని దీర్ఘ k_un_Open_VRInternal_Reserved_చివర = 10000;
స్థిర స్థిరరాశి గుర్తులేని దీర్ఘ k_un_Max_Property_String_కొలత = 32768;
స్థిర స్థిరరాశి గుర్తులేని దీర్ఘ దీర్ఘ k_ulInvalidActionHandle = 0;
స్థిర స్థిరరాశి గుర్తులేని దీర్ఘ దీర్ఘ k_ul_Invalid_Action_సమితి_Handle = 0;
స్థిర స్థిరరాశి గుర్తులేని దీర్ఘ దీర్ఘ k_ul_Invalid_ఆదానం_విలువ_Handle = 0;
స్థిర స్థిరరాశి గుర్తులేని దీర్ఘ k_un_Controller_State_Axis_లెక్క = 5;
స్థిర స్థిరరాశి గుర్తులేని దీర్ఘ దీర్ఘ k_ulOverlayHandleInvalid = 0;
స్థిర స్థిరరాశి గుర్తులేని దీర్ఘ k_unMaxDistortionFunctionParameters = 8;
స్థిర స్థిరరాశి గుర్తులేని దీర్ఘ k_unScreenshotHandleInvalid = 0;
స్థిర స్థిరరాశి అక్షరం * IVRSystem_సంస్కరణ = "IVRSystem_022";
స్థిర స్థిరరాశి అక్షరం * IVRExtended_Display_సంస్కరణ = "IVRExtendedDisplay_001";
స్థిర స్థిరరాశి అక్షరం * IVRTracked_Camera_సంస్కరణ = "IVRTrackedCamera_006";
స్థిర స్థిరరాశి గుర్తులేని దీర్ఘ k_un_Max_Application_కీలకం_నిడివి = 128;
స్థిర స్థిరరాశి అక్షరం * k_pch_MimeType_HomeApp = "vr/home";
స్థిర స్థిరరాశి అక్షరం * k_pch_MimeType_GameTheater = "vr/game_theater";
స్థిర స్థిరరాశి అక్షరం * IVRApplications_సంస్కరణ = "IVRApplications_007";
స్థిర స్థిరరాశి అక్షరం * IVRChaperone_సంస్కరణ = "IVRChaperone_004";
స్థిర స్థిరరాశి అక్షరం * IVRChaperone_అమరిక_సంస్కరణ = "IVRChaperoneSetup_006";
స్థిర స్థిరరాశి అక్షరం * IVRCompositor_సంస్కరణ = "IVRCompositor_027";
స్థిర స్థిరరాశి గుర్తులేని దీర్ఘ k_un_VROverlay_Max_కీలకం_నిడివి = 128;
స్థిర స్థిరరాశి గుర్తులేని దీర్ఘ k_un_VROverlay_Max_Name_నిడివి = 128;
స్థిర స్థిరరాశి గుర్తులేని దీర్ఘ k_un_Max_Overlay_లెక్క = 128;
స్థిర స్థిరరాశి గుర్తులేని దీర్ఘ k_un_Max_Overlay_Intersection_ముసుగు_Primitives_లెక్క = 32;
స్థిర స్థిరరాశి అక్షరం * IVROverlay_సంస్కరణ = "IVROverlay_026";
స్థిర స్థిరరాశి అక్షరం * IVROverlay_View_సంస్కరణ = "IVROverlayView_003";
స్థిర స్థిరరాశి గుర్తులేని దీర్ఘ k_un_Headset_View_Max_వెడల్పు = 3840;
స్థిర స్థిరరాశి గుర్తులేని దీర్ఘ k_un_Headset_View_Max_ఎత్తు = 2160;
స్థిర స్థిరరాశి అక్షరం * k_pch_Headset_View_Overlay_కీలకం = "system.HeadsetView";
స్థిర స్థిరరాశి అక్షరం * IVRHeadset_View_సంస్కరణ = "IVRHeadsetView_001";
స్థిర స్థిరరాశి అక్షరం * k_pch_Controller_Component_GDC2015 = "gdc2015";
స్థిర స్థిరరాశి అక్షరం * k_pch_Controller_Component_పునాది = "base";
స్థిర స్థిరరాశి అక్షరం * k_pch_Controller_Component_Tip = "tip";
స్థిర స్థిరరాశి అక్షరం * k_pch_Controller_Component_OpenXR_Aim = "openxr_aim";
స్థిర స్థిరరాశి అక్షరం * k_pch_Controller_Component_HandGrip = "handgrip";
స్థిర స్థిరరాశి అక్షరం * k_pch_Controller_Component_OpenXR_Grip = "openxr_grip";
స్థిర స్థిరరాశి అక్షరం * k_pch_Controller_Component_OpenXR_HandModel = "openxr_handmodel";
స్థిర స్థిరరాశి అక్షరం * k_pch_Controller_Component_స్థితి = "status";
స్థిర స్థిరరాశి అక్షరం * IVRRender_Models_సంస్కరణ = "IVRRenderModels_006";
స్థిర స్థిరరాశి గుర్తులేని దీర్ఘ k_un_Notification_పాఠ్యం_Max_కొలత = 256;
స్థిర స్థిరరాశి అక్షరం * IVRNotifications_సంస్కరణ = "IVRNotifications_002";
స్థిర స్థిరరాశి గుర్తులేని దీర్ఘ k_un_Max_Settings_కీలకం_నిడివి = 128;
స్థిర స్థిరరాశి అక్షరం * IVRSettings_సంస్కరణ = "IVRSettings_003";
స్థిర స్థిరరాశి అక్షరం * k_pch_SteamVR_Section = "steamvr";
స్థిర స్థిరరాశి అక్షరం * k_pch_SteamVR_RequireHmd_String = "requireHmd";
స్థిర స్థిరరాశి అక్షరం * k_pch_Steam_VR_Forced_Driver_కీలకం_String = "forcedDriver";
స్థిర స్థిరరాశి అక్షరం * k_pch_Steam_VR_Forced_Hmd_కీలకం_String = "forcedHmd";
స్థిర స్థిరరాశి అక్షరం * k_pch_SteamVR_DisplayDebug_Bool = "displayDebug";
స్థిర స్థిరరాశి అక్షరం * k_pch_SteamVR_DebugProcessPipe_String = "debugProcessPipe";
స్థిర స్థిరరాశి అక్షరం * k_pch_SteamVR_DisplayDebugX_Int32 = "displayDebugX";
స్థిర స్థిరరాశి అక్షరం * k_pch_SteamVR_DisplayDebugY_Int32 = "displayDebugY";
స్థిర స్థిరరాశి అక్షరం * k_pch_Steam_VR_Send_System_Button_గమ్యం_All_Apps_Bool = "sendSystemButtonToAllApps";
స్థిర స్థిరరాశి అక్షరం * k_pch_SteamVR_LogLevel_Int32 = "loglevel";
స్థిర స్థిరరాశి అక్షరం * k_pch_SteamVR_IPD_Float = "ipd";
స్థిర స్థిరరాశి అక్షరం * k_pch_SteamVR_Background_String = "background";
స్థిర స్థిరరాశి అక్షరం * k_pch_SteamVR_BackgroundUseDomeProjection_Bool = "backgroundUseDomeProjection";
స్థిర స్థిరరాశి అక్షరం * k_pch_Steam_VR_Background_Camera_ఎత్తు_Float = "backgroundCameraHeight";
స్థిర స్థిరరాశి అక్షరం * k_pch_SteamVR_BackgroundDomeRadius_Float = "backgroundDomeRadius";
స్థిర స్థిరరాశి అక్షరం * k_pch_SteamVR_GridColor_String = "gridColor";
స్థిర స్థిరరాశి అక్షరం * k_pch_SteamVR_PlayAreaColor_String = "playAreaColor";
స్థిర స్థిరరాశి అక్షరం * k_pch_SteamVR_TrackingLossColor_String = "trackingLossColor";
స్థిర స్థిరరాశి అక్షరం * k_pch_SteamVR_ShowStage_Bool = "showStage";
స్థిర స్థిరరాశి అక్షరం * k_pch_SteamVR_DrawTrackingReferences_Bool = "drawTrackingReferences";
స్థిర స్థిరరాశి అక్షరం * k_pch_Steam_VR_Activate_గుణిజం_Drivers_Bool = "activateMultipleDrivers";
స్థిర స్థిరరాశి అక్షరం * k_pch_SteamVR_UsingSpeakers_Bool = "usingSpeakers";
స్థిర స్థిరరాశి అక్షరం * k_pch_Steam_VR_Speakers_Forward_Yaw_స్థానభ్రంశం_Degrees_Float = "speakersForwardYawOffsetDegrees";
స్థిర స్థిరరాశి అక్షరం * k_pch_Steam_VR_పునాది_Station_Power_Management_Int32 = "basestationPowerManagement";
స్థిర స్థిరరాశి అక్షరం * k_pch_Steam_VR_Show_పునాది_Station_Power_Management_Tip_Int32 = "ShowBaseStationPowerManagementTip";
స్థిర స్థిరరాశి అక్షరం * k_pch_SteamVR_NeverKillProcesses_Bool = "neverKillProcesses";
స్థిర స్థిరరాశి అక్షరం * k_pch_SteamVR_SupersampleScale_Float = "supersampleScale";
స్థిర స్థిరరాశి అక్షరం * k_pch_SteamVR_MaxRecommendedResolution_Int32 = "maxRecommendedResolution";
స్థిర స్థిరరాశి అక్షరం * k_pch_SteamVR_MotionSmoothing_Bool = "motionSmoothing";
స్థిర స్థిరరాశి అక్షరం * k_pch_SteamVR_MotionSmoothingOverride_Int32 = "motionSmoothingOverride";
స్థిర స్థిరరాశి అక్షరం * k_pch_Steam_VR_చట్రాలు_గమ్యం_Throttle_Int32 = "framesToThrottle";
స్థిర స్థిరరాశి అక్షరం * k_pch_Steam_VR_Additional_చట్రాలు_గమ్యం_Predict_Int32 = "additionalFramesToPredict";
స్థిర స్థిరరాశి అక్షరం * k_pch_SteamVR_WorldScale_Float = "worldScale";
స్థిర స్థిరరాశి అక్షరం * k_pch_SteamVR_FovScale_Int32 = "fovScale";
స్థిర స్థిరరాశి అక్షరం * k_pch_SteamVR_DisableAsyncReprojection_Bool = "disableAsync";
స్థిర స్థిరరాశి అక్షరం * k_pch_SteamVR_ForceFadeOnBadTracking_Bool = "forceFadeOnBadTracking";
స్థిర స్థిరరాశి అక్షరం * k_pch_SteamVR_DefaultMirrorView_Int32 = "mirrorView";
స్థిర స్థిరరాశి అక్షరం * k_pch_SteamVR_ShowLegacyMirrorView_Bool = "showLegacyMirrorView";
స్థిర స్థిరరాశి అక్షరం * k_pch_SteamVR_MirrorViewVisibility_Bool = "showMirrorView";
స్థిర స్థిరరాశి అక్షరం * k_pch_Steam_VR_Mirror_View_Display_బహుళకం_Int32 = "mirrorViewDisplayMode";
స్థిర స్థిరరాశి అక్షరం * k_pch_SteamVR_MirrorViewEye_Int32 = "mirrorViewEye";
స్థిర స్థిరరాశి అక్షరం * k_pch_SteamVR_MirrorViewGeometry_String = "mirrorViewGeometry";
స్థిర స్థిరరాశి అక్షరం * k_pch_SteamVR_MirrorViewGeometryMaximized_String = "mirrorViewGeometryMaximized";
స్థిర స్థిరరాశి అక్షరం * k_pch_Steam_VR_Perf_లేఖాచిత్రం_Visibility_Bool = "showPerfGraph";
స్థిర స్థిరరాశి అక్షరం * k_pch_Steam_VR_ప్రారంభం_Monitor_From_App_Launch = "startMonitorFromAppLaunch";
స్థిర స్థిరరాశి అక్షరం * k_pch_Steam_VR_ప్రారంభం_Compositor_From_App_Launch_Bool = "startCompositorFromAppLaunch";
స్థిర స్థిరరాశి అక్షరం * k_pch_Steam_VR_ప్రారంభం_Dashboard_From_App_Launch_Bool = "startDashboardFromAppLaunch";
స్థిర స్థిరరాశి అక్షరం * k_pch_Steam_VR_ప్రారంభం_Overlay_Apps_From_Dashboard_Bool = "startOverlayAppsFromDashboard";
స్థిర స్థిరరాశి అక్షరం * k_pch_SteamVR_EnableHomeApp = "enableHomeApp";
స్థిర స్థిరరాశి అక్షరం * k_pch_Steam_VR_చక్రం_Background_Image_సమయం_Sec_Int32 = "CycleBackgroundImageTimeSec";
స్థిర స్థిరరాశి అక్షరం * k_pch_SteamVR_RetailDemo_Bool = "retailDemo";
స్థిర స్థిరరాశి అక్షరం * k_pch_Steam_VR_Ipd_స్థానభ్రంశం_Float = "ipdOffset";
స్థిర స్థిరరాశి అక్షరం * k_pch_SteamVR_AllowSupersampleFiltering_Bool = "allowSupersampleFiltering";
స్థిర స్థిరరాశి అక్షరం * k_pch_SteamVR_SupersampleManualOverride_Bool = "supersampleManualOverride";
స్థిర స్థిరరాశి అక్షరం * k_pch_SteamVR_EnableLinuxVulkanAsync_Bool = "enableLinuxVulkanAsync";
స్థిర స్థిరరాశి అక్షరం * k_pch_Steam_VR_Allow_Display_Locked_బహుళకం_Bool = "allowDisplayLockedMode";
స్థిర స్థిరరాశి అక్షరం * k_pch_SteamVR_HaveStartedTutorialForNativeChaperoneDriver_Bool = "haveStartedTutorialForNativeChaperoneDriver";
స్థిర స్థిరరాశి అక్షరం * k_pch_SteamVR_ForceWindows32bitVRMonitor = "forceWindows32BitVRMonitor";
స్థిర స్థిరరాశి అక్షరం * k_pch_Steam_VR_Debug_ఆదానం_Binding = "debugInputBinding";
స్థిర స్థిరరాశి అక్షరం * k_pch_Steam_VR_Do_Not_Fade_గమ్యం_Grid = "doNotFadeToGrid";
స్థిర స్థిరరాశి అక్షరం * k_pch_Steam_VR_Render_Camera_బహుళకం = "renderCameraMode";
స్థిర స్థిరరాశి అక్షరం * k_pch_SteamVR_EnableSharedResourceJournaling = "enableSharedResourceJournaling";
స్థిర స్థిరరాశి అక్షరం * k_pch_Steam_VR_Enable_సురక్షిత_బహుళకం = "enableSafeMode";
స్థిర స్థిరరాశి అక్షరం * k_pch_Steam_VR_Preferred_Refresh_రేటు = "preferredRefreshRate";
స్థిర స్థిరరాశి అక్షరం * k_pch_Steam_VR_చివరి_సంస్కరణ_Notice = "lastVersionNotice";
స్థిర స్థిరరాశి అక్షరం * k_pch_Steam_VR_చివరి_సంస్కరణ_Notice_Date = "lastVersionNoticeDate";
స్థిర స్థిరరాశి అక్షరం * k_pch_SteamVR_HmdDisplayColorGainR_Float = "hmdDisplayColorGainR";
స్థిర స్థిరరాశి అక్షరం * k_pch_SteamVR_HmdDisplayColorGainG_Float = "hmdDisplayColorGainG";
స్థిర స్థిరరాశి అక్షరం * k_pch_SteamVR_HmdDisplayColorGainB_Float = "hmdDisplayColorGainB";
స్థిర స్థిరరాశి అక్షరం * k_pch_SteamVR_CustomIconStyle_String = "customIconStyle";
స్థిర స్థిరరాశి అక్షరం * k_pch_SteamVR_CustomOffIconStyle_String = "customOffIconStyle";
స్థిర స్థిరరాశి అక్షరం * k_pch_SteamVR_CustomIconForceUpdate_String = "customIconForceUpdate";
స్థిర స్థిరరాశి అక్షరం * k_pch_Steam_VR_Allow_Global_Action_సమితి_ప్రాధాన్యత = "globalActionSetPriority";
స్థిర స్థిరరాశి అక్షరం * k_pch_SteamVR_OverlayRenderQuality = "overlayRenderQuality_2";
స్థిర స్థిరరాశి అక్షరం * k_pch_Steam_VR_ఖండం_Oculus_SDKOn_Open_VRLaunch_Option_Bool = "blockOculusSDKOnOpenVRLaunchOption";
స్థిర స్థిరరాశి అక్షరం * k_pch_Steam_VR_ఖండం_Oculus_SDKOn_All_Launches_Bool = "blockOculusSDKOnAllLaunches";
స్థిర స్థిరరాశి అక్షరం * k_pch_SteamVR_HDCPLegacyCompatibility_Bool = "hdcp14legacyCompatibility";
స్థిర స్థిరరాశి అక్షరం * k_pch_Steam_VR_Display_పోర్టు_Training_బహుళకం_Int = "displayPortTrainingMode";
స్థిర స్థిరరాశి అక్షరం * k_pch_SteamVR_UsePrism_Bool = "usePrism";
స్థిర స్థిరరాశి అక్షరం * k_pch_ప్రత్యక్ష_బహుళకం_Section = "direct_mode";
స్థిర స్థిరరాశి అక్షరం * k_pch_ప్రత్యక్ష_బహుళకం_Enable_Bool = "enable";
స్థిర స్థిరరాశి అక్షరం * k_pch_ప్రత్యక్ష_బహుళకం_లెక్క_Int32 = "count";
స్థిర స్థిరరాశి అక్షరం * k_pch_ప్రత్యక్ష_బహుళకం_Edid_Vid_Int32 = "edidVid";
స్థిర స్థిరరాశి అక్షరం * k_pch_ప్రత్యక్ష_బహుళకం_Edid_Pid_Int32 = "edidPid";
స్థిర స్థిరరాశి అక్షరం * k_pch_Lighthouse_Section = "driver_lighthouse";
స్థిర స్థిరరాశి అక్షరం * k_pch_Lighthouse_DisableIMU_Bool = "disableimu";
స్థిర స్థిరరాశి అక్షరం * k_pch_Lighthouse_DisableIMUExceptHMD_Bool = "disableimuexcepthmd";
స్థిర స్థిరరాశి అక్షరం * k_pch_Lighthouse_UseDisambiguation_String = "usedisambiguation";
స్థిర స్థిరరాశి అక్షరం * k_pch_Lighthouse_DisambiguationDebug_Int32 = "disambiguationdebug";
స్థిర స్థిరరాశి అక్షరం * k_pch_Lighthouse_PrimaryBasestation_Int32 = "primarybasestation";
స్థిర స్థిరరాశి అక్షరం * k_pch_Lighthouse_DBHistory_Bool = "dbhistory";
స్థిర స్థిరరాశి అక్షరం * k_pch_Lighthouse_EnableBluetooth_Bool = "enableBluetooth";
స్థిర స్థిరరాశి అక్షరం * k_pch_Lighthouse_Power_Managed_పునాది_Stations_String = "PowerManagedBaseStations";
స్థిర స్థిరరాశి అక్షరం * k_pch_Lighthouse_Power_Managed_పునాది_Stations2_String = "PowerManagedBaseStations2";
స్థిర స్థిరరాశి అక్షరం * k_pch_Lighthouse_Inactivity_Timeout_For_పునాది_Stations_Int32 = "InactivityTimeoutForBaseStations";
స్థిర స్థిరరాశి అక్షరం * k_pch_Lighthouse_EnableImuFallback_Bool = "enableImuFallback";
స్థిర స్థిరరాశి అక్షరం * k_pch_Null_Section = "driver_null";
స్థిర స్థిరరాశి అక్షరం * k_pch_Null_Serial_సంఖ్య_String = "serialNumber";
స్థిర స్థిరరాశి అక్షరం * k_pch_Null_Model_సంఖ్య_String = "modelNumber";
స్థిర స్థిరరాశి అక్షరం * k_pch_Null_కిటికీ_X_Int32 = "windowX";
స్థిర స్థిరరాశి అక్షరం * k_pch_Null_కిటికీ_Y_Int32 = "windowY";
స్థిర స్థిరరాశి అక్షరం * k_pch_Null_కిటికీ_వెడల్పు_Int32 = "windowWidth";
స్థిర స్థిరరాశి అక్షరం * k_pch_Null_కిటికీ_ఎత్తు_Int32 = "windowHeight";
స్థిర స్థిరరాశి అక్షరం * k_pch_Null_Render_వెడల్పు_Int32 = "renderWidth";
స్థిర స్థిరరాశి అక్షరం * k_pch_Null_Render_ఎత్తు_Int32 = "renderHeight";
స్థిర స్థిరరాశి అక్షరం * k_pch_Null_Seconds_From_Vsync_గమ్యం_Photons_Float = "secondsFromVsyncToPhotons";
స్థిర స్థిరరాశి అక్షరం * k_pch_Null_DisplayFrequency_Float = "displayFrequency";
స్థిర స్థిరరాశి అక్షరం * k_pch_WindowsMR_Section = "driver_holographic";
స్థిర స్థిరరాశి అక్షరం * k_pch_UserInterface_Section = "userinterface";
స్థిర స్థిరరాశి అక్షరం * k_pch_User_Interface_స్థితి_Always_On_శిఖరం_Bool = "StatusAlwaysOnTop";
స్థిర స్థిరరాశి అక్షరం * k_pch_User_Interface_Minimize_గమ్యం_Tray_Bool = "MinimizeToTray";
స్థిర స్థిరరాశి అక్షరం * k_pch_User_Interface_Hide_Popups_When_స్థితి_Minimized_Bool = "HidePopupsWhenStatusMinimized";
స్థిర స్థిరరాశి అక్షరం * k_pch_UserInterface_Screenshots_Bool = "screenshots";
స్థిర స్థిరరాశి అక్షరం * k_pch_UserInterface_ScreenshotType_Int = "screenshotType";
స్థిర స్థిరరాశి అక్షరం * k_pch_Notifications_Section = "notifications";
స్థిర స్థిరరాశి అక్షరం * k_pch_Notifications_DoNotDisturb_Bool = "DoNotDisturb";
స్థిర స్థిరరాశి అక్షరం * k_pch_Keyboard_Section = "keyboard";
స్థిర స్థిరరాశి అక్షరం * k_pch_Keyboard_TutorialCompletions = "TutorialCompletions";
స్థిర స్థిరరాశి అక్షరం * k_pch_Keyboard_ScaleX = "ScaleX";
స్థిర స్థిరరాశి అక్షరం * k_pch_Keyboard_ScaleY = "ScaleY";
స్థిర స్థిరరాశి అక్షరం * k_pch_Keyboard_స్థానభ్రంశం_ఎడమ_X = "OffsetLeftX";
స్థిర స్థిరరాశి అక్షరం * k_pch_Keyboard_స్థానభ్రంశం_కుడి_X = "OffsetRightX";
స్థిర స్థిరరాశి అక్షరం * k_pch_Keyboard_స్థానభ్రంశం_Y = "OffsetY";
స్థిర స్థిరరాశి అక్షరం * k_pch_Keyboard_Smoothing = "Smoothing";
స్థిర స్థిరరాశి అక్షరం * k_pch_Perf_Section = "perfcheck";
స్థిర స్థిరరాశి అక్షరం * k_pch_Perf_Perf_లేఖాచిత్రం_లోపల_HMD_Bool = "perfGraphInHMD";
స్థిర స్థిరరాశి అక్షరం * k_pch_Perf_AllowTimingStore_Bool = "allowTimingStore";
స్థిర స్థిరరాశి అక్షరం * k_pch_Perf_SaveTimingsOnExit_Bool = "saveTimingsOnExit";
స్థిర స్థిరరాశి అక్షరం * k_pch_Perf_Test_దత్తాంశం_Float = "perfTestData";
స్థిర స్థిరరాశి అక్షరం * k_pch_Perf_GPUProfiling_Bool = "GPUProfiling";
స్థిర స్థిరరాశి అక్షరం * k_pch_CollisionBounds_Section = "collisionBounds";
స్థిర స్థిరరాశి అక్షరం * k_pch_CollisionBounds_Style_Int32 = "CollisionBoundsStyle";
స్థిర స్థిరరాశి అక్షరం * k_pch_CollisionBounds_GroundPerimeterOn_Bool = "CollisionBoundsGroundPerimeterOn";
స్థిర స్థిరరాశి అక్షరం * k_pch_CollisionBounds_CenterMarkerOn_Bool = "CollisionBoundsCenterMarkerOn";
స్థిర స్థిరరాశి అక్షరం * k_pch_CollisionBounds_PlaySpaceOn_Bool = "CollisionBoundsPlaySpaceOn";
స్థిర స్థిరరాశి అక్షరం * k_pch_Collision_Bounds_Fade_దూరం_Float = "CollisionBoundsFadeDistance";
స్థిర స్థిరరాశి అక్షరం * k_pch_Collision_Bounds_Wall_ఎత్తు_Float = "CollisionBoundsWallHeight";
స్థిర స్థిరరాశి అక్షరం * k_pch_CollisionBounds_ColorGammaR_Int32 = "CollisionBoundsColorGammaR";
స్థిర స్థిరరాశి అక్షరం * k_pch_CollisionBounds_ColorGammaG_Int32 = "CollisionBoundsColorGammaG";
స్థిర స్థిరరాశి అక్షరం * k_pch_CollisionBounds_ColorGammaB_Int32 = "CollisionBoundsColorGammaB";
స్థిర స్థిరరాశి అక్షరం * k_pch_CollisionBounds_ColorGammaA_Int32 = "CollisionBoundsColorGammaA";
స్థిర స్థిరరాశి అక్షరం * k_pch_CollisionBounds_EnableDriverImport = "enableDriverBoundsImport";
స్థిర స్థిరరాశి అక్షరం * k_pch_Camera_Section = "camera";
స్థిర స్థిరరాశి అక్షరం * k_pch_Camera_EnableCamera_Bool = "enableCamera";
స్థిర స్థిరరాశి అక్షరం * k_pch_Camera_ShowOnController_Bool = "showOnController";
స్థిర స్థిరరాశి అక్షరం * k_pch_Camera_EnableCameraForCollisionBounds_Bool = "enableCameraForCollisionBounds";
స్థిర స్థిరరాశి అక్షరం * k_pch_Camera_స్థలం_View_Int32 = "roomView";
స్థిర స్థిరరాశి అక్షరం * k_pch_Camera_BoundsColorGammaR_Int32 = "cameraBoundsColorGammaR";
స్థిర స్థిరరాశి అక్షరం * k_pch_Camera_BoundsColorGammaG_Int32 = "cameraBoundsColorGammaG";
స్థిర స్థిరరాశి అక్షరం * k_pch_Camera_BoundsColorGammaB_Int32 = "cameraBoundsColorGammaB";
స్థిర స్థిరరాశి అక్షరం * k_pch_Camera_BoundsColorGammaA_Int32 = "cameraBoundsColorGammaA";
స్థిర స్థిరరాశి అక్షరం * k_pch_Camera_BoundsStrength_Int32 = "cameraBoundsStrength";
స్థిర స్థిరరాశి అక్షరం * k_pch_Camera_స్థలం_View_Style_Int32 = "roomViewStyle";
స్థిర స్థిరరాశి అక్షరం * k_pch_audio_Section = "audio";
స్థిర స్థిరరాశి అక్షరం * k_pch_audio_సమితి_Os_Default_Playback_Device_Bool = "setOsDefaultPlaybackDevice";
స్థిర స్థిరరాశి అక్షరం * k_pch_audio_EnablePlaybackDeviceOverride_Bool = "enablePlaybackDeviceOverride";
స్థిర స్థిరరాశి అక్షరం * k_pch_audio_PlaybackDeviceOverride_String = "playbackDeviceOverride";
స్థిర స్థిరరాశి అక్షరం * k_pch_audio_PlaybackDeviceOverrideName_String = "playbackDeviceOverrideName";
స్థిర స్థిరరాశి అక్షరం * k_pch_audio_సమితి_Os_Default_Recording_Device_Bool = "setOsDefaultRecordingDevice";
స్థిర స్థిరరాశి అక్షరం * k_pch_audio_EnableRecordingDeviceOverride_Bool = "enableRecordingDeviceOverride";
స్థిర స్థిరరాశి అక్షరం * k_pch_audio_RecordingDeviceOverride_String = "recordingDeviceOverride";
స్థిర స్థిరరాశి అక్షరం * k_pch_audio_RecordingDeviceOverrideName_String = "recordingDeviceOverrideName";
స్థిర స్థిరరాశి అక్షరం * k_pch_audio_EnablePlaybackMirror_Bool = "enablePlaybackMirror";
స్థిర స్థిరరాశి అక్షరం * k_pch_audio_PlaybackMirrorDevice_String = "playbackMirrorDevice";
స్థిర స్థిరరాశి అక్షరం * k_pch_audio_PlaybackMirrorDeviceName_String = "playbackMirrorDeviceName";
స్థిర స్థిరరాశి అక్షరం * k_pch_audio_OldPlaybackMirrorDevice_String = "onPlaybackMirrorDevice";
స్థిర స్థిరరాశి అక్షరం * k_pch_audio_చురుకైన_Mirror_Device_String = "activePlaybackMirrorDevice";
స్థిర స్థిరరాశి అక్షరం * k_pch_audio_EnablePlaybackMirrorIndependentVolume_Bool = "enablePlaybackMirrorIndependentVolume";
స్థిర స్థిరరాశి అక్షరం * k_pch_audio_చివరి_Hmd_Playback_Device_Id_String = "lastHmdPlaybackDeviceId";
స్థిర స్థిరరాశి అక్షరం * k_pch_audio_VIVEHDMIGain = "viveHDMIGain";
స్థిర స్థిరరాశి అక్షరం * k_pch_audio_DualSpeakerAndJackOutput_Bool = "dualSpeakerAndJackOutput";
స్థిర స్థిరరాశి అక్షరం * k_pch_audio_MuteMicMonitor_Bool = "muteMicMonitor";
స్థిర స్థిరరాశి అక్షరం * k_pch_Power_Section = "power";
స్థిర స్థిరరాశి అక్షరం * k_pch_Power_PowerOffOnExit_Bool = "powerOffOnExit";
స్థిర స్థిరరాశి అక్షరం * k_pch_Power_TurnOffScreensTimeout_Float = "turnOffScreensTimeout";
స్థిర స్థిరరాశి అక్షరం * k_pch_Power_TurnOffControllersTimeout_Float = "turnOffControllersTimeout";
స్థిర స్థిరరాశి అక్షరం * k_pch_Power_Return_గమ్యం_Watchdog_Timeout_Float = "returnToWatchdogTimeout";
స్థిర స్థిరరాశి అక్షరం * k_pch_Power_AutoLaunchSteamVROnButtonPress = "autoLaunchSteamVROnButtonPress";
స్థిర స్థిరరాశి అక్షరం * k_pch_Power_PauseCompositorOnStandby_Bool = "pauseCompositorOnStandby";
స్థిర స్థిరరాశి అక్షరం * k_pch_Dashboard_Section = "dashboard";
స్థిర స్థిరరాశి అక్షరం * k_pch_Dashboard_EnableDashboard_Bool = "enableDashboard";
స్థిర స్థిరరాశి అక్షరం * k_pch_Dashboard_Arcade_బహుళకం_Bool = "arcadeMode";
స్థిర స్థిరరాశి అక్షరం * k_pch_Dashboard_Position = "position";
స్థిర స్థిరరాశి అక్షరం * k_pch_Dashboard_DesktopScale = "desktopScale";
స్థిర స్థిరరాశి అక్షరం * k_pch_Dashboard_DashboardScale = "dashboardScale";
స్థిర స్థిరరాశి అక్షరం * k_pch_Dashboard_UseStandaloneSystemLayer = "standaloneSystemLayer";
స్థిర స్థిరరాశి అక్షరం * k_pch_Dashboard_StickyDashboard = "stickyDashboard";
స్థిర స్థిరరాశి అక్షరం * k_pch_modelskin_Section = "modelskins";
స్థిర స్థిరరాశి అక్షరం * k_pch_Driver_Enable_Bool = "enable";
స్థిర స్థిరరాశి అక్షరం * k_pch_Driver_BlockedBySafemode_Bool = "blocked_by_safe_mode";
స్థిర స్థిరరాశి అక్షరం * k_pch_Driver_ఎక్కించు_ప్రాధాన్యత_Int32 = "loadPriority";
స్థిర స్థిరరాశి అక్షరం * k_pch_WebInterface_Section = "WebInterface";
స్థిర స్థిరరాశి అక్షరం * k_pch_VRWebHelper_Section = "VRWebHelper";
స్థిర స్థిరరాశి అక్షరం * k_pch_VRWebHelper_DebuggerEnabled_Bool = "DebuggerEnabled";
స్థిర స్థిరరాశి అక్షరం * k_pch_VRWeb_Helper_Debugger_పోర్టు_Int32 = "DebuggerPort";
స్థిర స్థిరరాశి అక్షరం * k_pch_TrackingOverride_Section = "TrackingOverrides";
స్థిర స్థిరరాశి అక్షరం * k_pch_App_BindingAutosaveURLSuffix_String = "AutosaveURL";
స్థిర స్థిరరాశి అక్షరం * k_pch_App_BindingLegacyAPISuffix_String = "_legacy";
స్థిర స్థిరరాశి అక్షరం * k_pch_App_BindingSteamVRInputAPISuffix_String = "_steamvrinput";
స్థిర స్థిరరాశి అక్షరం * k_pch_App_BindingOpenXRAPISuffix_String = "_openxr";
స్థిర స్థిరరాశి అక్షరం * k_pch_App_BindingCurrentURLSuffix_String = "CurrentURL";
స్థిర స్థిరరాశి అక్షరం * k_pch_App_Binding_మునుపటి_URLSuffix_String = "PreviousURL";
స్థిర స్థిరరాశి అక్షరం * k_pch_App_Need_గమ్యం_Update_Autosave_Suffix_Bool = "NeedToUpdateAutosave";
స్థిర స్థిరరాశి అక్షరం * k_pch_App_DominantHand_Int32 = "DominantHand";
స్థిర స్థిరరాశి అక్షరం * k_pch_App_ఖండం_Oculus_SDK_Bool = "blockOculusSDK";
స్థిర స్థిరరాశి అక్షరం * k_pch_Trackers_Section = "trackers";
స్థిర స్థిరరాశి అక్షరం * k_pch_DesktopUI_Section = "DesktopUI";
స్థిర స్థిరరాశి అక్షరం * k_pch_చివరి_తెలిసిన_Section = "LastKnown";
స్థిర స్థిరరాశి అక్షరం * k_pch_చివరి_తెలిసిన_HMDManufacturer_String = "HMDManufacturer";
స్థిర స్థిరరాశి అక్షరం * k_pch_చివరి_తెలిసిన_HMDModel_String = "HMDModel";
స్థిర స్థిరరాశి అక్షరం * k_pch_DismissedWarnings_Section = "DismissedWarnings";
స్థిర స్థిరరాశి అక్షరం * k_pch_ఆదానం_Section = "input";
స్థిర స్థిరరాశి అక్షరం * k_pch_ఆదానం_ఎడమ_Thumbstick_Rotation_Float = "leftThumbstickRotation";
స్థిర స్థిరరాశి అక్షరం * k_pch_ఆదానం_కుడి_Thumbstick_Rotation_Float = "rightThumbstickRotation";
స్థిర స్థిరరాశి అక్షరం * k_pch_ఆదానం_Thumbstick_Deadzone_Float = "thumbstickDeadzone";
స్థిర స్థిరరాశి అక్షరం * k_pch_Gpu_వేగం_Section = "GpuSpeed";
స్థిర స్థిరరాశి అక్షరం * IVRScreenshots_సంస్కరణ = "IVRScreenshots_001";
స్థిర స్థిరరాశి అక్షరం * IVRResources_సంస్కరణ = "IVRResources_001";
స్థిర స్థిరరాశి అక్షరం * IVRDriver_Manager_సంస్కరణ = "IVRDriverManager_001";
స్థిర స్థిరరాశి గుర్తులేని దీర్ఘ k_un_Max_Action_Name_నిడివి = 64;
స్థిర స్థిరరాశి గుర్తులేని దీర్ఘ k_un_Max_Action_సమితి_Name_నిడివి = 64;
స్థిర స్థిరరాశి గుర్తులేని దీర్ఘ k_un_Max_Action_Origin_లెక్క = 16;
స్థిర స్థిరరాశి గుర్తులేని దీర్ఘ k_un_Max_Bone_Name_నిడివి = 32;
స్థిర స్థిరరాశి పూర్ణాంకం k_n_Action_సమితి_Overlay_Global_ప్రాధాన్యత_Min = 16777216;
స్థిర స్థిరరాశి పూర్ణాంకం k_n_Action_సమితి_Overlay_Global_ప్రాధాన్యత_Max = 33554431;
స్థిర స్థిరరాశి పూర్ణాంకం k_n_Action_సమితి_ప్రాధాన్యత_Reserved_Min = 33554432;
స్థిర స్థిరరాశి అక్షరం * IVRInput_సంస్కరణ = "IVRInput_010";
స్థిర స్థిరరాశి గుర్తులేని దీర్ఘ దీర్ఘ k_ulInvalidIOBufferHandle = 0;
స్థిర స్థిరరాశి అక్షరం * IVRIOBuffer_సంస్కరణ = "IVRIOBuffer_002";
స్థిర స్థిరరాశి గుర్తులేని దీర్ఘ k_ulInvalidSpatialAnchorHandle = 0;
స్థిర స్థిరరాశి అక్షరం * IVRSpatial_Anchors_సంస్కరణ = "IVRSpatialAnchors_001";
స్థిర స్థిరరాశి అక్షరం * IVRDebug_సంస్కరణ = "IVRDebug_001";
స్థిర స్థిరరాశి గుర్తులేని దీర్ఘ దీర్ఘ k_ulDisplayRedirectContainer = 25769803779;
స్థిర స్థిరరాశి అక్షరం * IVRProperties_సంస్కరణ = "IVRProperties_001";
స్థిర స్థిరరాశి అక్షరం * k_pch_మార్గం_User_Hand_కుడి = "/user/hand/right";
స్థిర స్థిరరాశి అక్షరం * k_pch_మార్గం_User_Hand_ఎడమ = "/user/hand/left";
స్థిర స్థిరరాశి అక్షరం * k_pch_మార్గం_User_Hand_Primary = "/user/hand/primary";
స్థిర స్థిరరాశి అక్షరం * k_pch_మార్గం_User_Hand_Secondary = "/user/hand/secondary";
స్థిర స్థిరరాశి అక్షరం * k_pch_మార్గం_User_తల = "/user/head";
స్థిర స్థిరరాశి అక్షరం * k_pch_మార్గం_User_Gamepad = "/user/gamepad";
స్థిర స్థిరరాశి అక్షరం * k_pch_మార్గం_User_Treadmill = "/user/treadmill";
స్థిర స్థిరరాశి అక్షరం * k_pch_మార్గం_User_Stylus = "/user/stylus";
స్థిర స్థిరరాశి అక్షరం * k_pch_మార్గం_Devices = "/devices";
స్థిర స్థిరరాశి అక్షరం * k_pch_మార్గం_Device_మార్గం = "/device_path";
స్థిర స్థిరరాశి అక్షరం * k_pch_మార్గం_ఉత్తమ_Alias_మార్గం = "/best_alias_path";
స్థిర స్థిరరాశి అక్షరం * k_pch_మార్గం_Bound_Tracker_Alias_మార్గం = "/bound_tracker_path";
స్థిర స్థిరరాశి అక్షరం * k_pch_మార్గం_Bound_Tracker_Role = "/bound_tracker_role";
స్థిర స్థిరరాశి అక్షరం * k_pch_మార్గం_Pose_Raw = "/pose/raw";
స్థిర స్థిరరాశి అక్షరం * k_pch_మార్గం_Pose_Tip = "/pose/tip";
స్థిర స్థిరరాశి అక్షరం * k_pch_మార్గం_Pose_Grip = "/pose/grip";
స్థిర స్థిరరాశి అక్షరం * k_pch_మార్గం_System_Button_Click = "/input/system/click";
స్థిర స్థిరరాశి అక్షరం * k_pch_మార్గం_Proximity = "/proximity";
స్థిర స్థిరరాశి అక్షరం * k_pch_మార్గం_Controller_Type_ఉపసర్గ = "/controller_type/";
స్థిర స్థిరరాశి అక్షరం * k_pch_మార్గం_ఆదానం_Profile_Suffix = "/input_profile";
స్థిర స్థిరరాశి అక్షరం * k_pch_మార్గం_Binding_Name_Suffix = "/binding_name";
స్థిర స్థిరరాశి అక్షరం * k_pch_మార్గం_Binding_Url_Suffix = "/binding_url";
స్థిర స్థిరరాశి అక్షరం * k_pch_మార్గం_Binding_Error_Suffix = "/binding_error";
స్థిర స్థిరరాశి అక్షరం * k_pch_మార్గం_చురుకైన_Action_Sets = "/active_action_sets";
స్థిర స్థిరరాశి అక్షరం * k_pch_మార్గం_Component_Updates = "/total_component_updates";
స్థిర స్థిరరాశి అక్షరం * k_pch_మార్గం_User_Foot_ఎడమ = "/user/foot/left";
స్థిర స్థిరరాశి అక్షరం * k_pch_మార్గం_User_Foot_కుడి = "/user/foot/right";
స్థిర స్థిరరాశి అక్షరం * k_pch_మార్గం_User_Shoulder_ఎడమ = "/user/shoulder/left";
స్థిర స్థిరరాశి అక్షరం * k_pch_మార్గం_User_Shoulder_కుడి = "/user/shoulder/right";
స్థిర స్థిరరాశి అక్షరం * k_pch_మార్గం_User_Elbow_ఎడమ = "/user/elbow/left";
స్థిర స్థిరరాశి అక్షరం * k_pch_మార్గం_User_Elbow_కుడి = "/user/elbow/right";
స్థిర స్థిరరాశి అక్షరం * k_pch_మార్గం_User_Knee_ఎడమ = "/user/knee/left";
స్థిర స్థిరరాశి అక్షరం * k_pch_మార్గం_User_Knee_కుడి = "/user/knee/right";
స్థిర స్థిరరాశి అక్షరం * k_pch_మార్గం_User_Waist = "/user/waist";
స్థిర స్థిరరాశి అక్షరం * k_pch_మార్గం_User_Chest = "/user/chest";
స్థిర స్థిరరాశి అక్షరం * k_pch_మార్గం_User_Camera = "/user/camera";
స్థిర స్థిరరాశి అక్షరం * k_pch_మార్గం_User_Keyboard = "/user/keyboard";
స్థిర స్థిరరాశి అక్షరం * k_pch_మార్గం_Client_App_కీలకం = "/client_info/app_key";
స్థిర స్థిరరాశి గుర్తులేని దీర్ఘ దీర్ఘ k_ul_Invalid_మార్గం_Handle = 0;
స్థిర స్థిరరాశి అక్షరం * IVRPaths_సంస్కరణ = "IVRPaths_001";
స్థిర స్థిరరాశి అక్షరం * IVRBlock_వరుస_సంస్కరణ = "IVRBlockQueue_005";

// OpenVR Enums

రకనిర్వచనం గణన EVREye
{
	EVREye_Eye_ఎడమ = 0,
	EVREye_Eye_కుడి = 1,
} EVREye;

రకనిర్వచనం గణన ETextureType
{
	ETextureType_TextureType_Invalid = -1,
	ETexture_Type_Texture_Type_ప్రత్యక్ష_X = 0,
	ETextureType_TextureType_OpenGL = 1,
	ETextureType_TextureType_Vulkan = 2,
	ETextureType_TextureType_IOSurface = 3,
	ETexture_Type_Texture_Type_ప్రత్యక్ష_X12 = 4,
	ETextureType_TextureType_DXGISharedHandle = 5,
	ETextureType_TextureType_Metal = 6,
} ETextureType;

రకనిర్వచనం గణన EColorSpace
{
	EColorSpace_ColorSpace_Auto = 0,
	EColorSpace_ColorSpace_Gamma = 1,
	EColor_Space_Color_Space_రేఖీయ = 2,
} EColorSpace;

రకనిర్వచనం గణన ETracking_ఫలితం
{
	ETracking_ఫలితం_Tracking_ఫలితం_Uninitialized = 1,
	ETracking_ఫలితం_Tracking_ఫలితం_Calibrating_లోపల_పురోగతి = 100,
	ETracking_ఫలితం_Tracking_ఫలితం_Calibrating_బహిర్గతం_యొక్క_Range = 101,
	ETracking_ఫలితం_Tracking_ఫలితం_Running_OK = 200,
	ETracking_ఫలితం_Tracking_ఫలితం_Running_బహిర్గతం_యొక్క_Range = 201,
	ETracking_ఫలితం_Tracking_ఫలితం_Fallback_Rotation_Only = 300,
} ETracking_ఫలితం;

రకనిర్వచనం గణన ETrackedDeviceClass
{
	ETrackedDeviceClass_TrackedDeviceClass_Invalid = 0,
	ETrackedDeviceClass_TrackedDeviceClass_HMD = 1,
	ETrackedDeviceClass_TrackedDeviceClass_Controller = 2,
	ETrackedDeviceClass_TrackedDeviceClass_GenericTracker = 3,
	ETrackedDeviceClass_TrackedDeviceClass_TrackingReference = 4,
	ETrackedDeviceClass_TrackedDeviceClass_DisplayRedirect = 5,
	ETrackedDeviceClass_TrackedDeviceClass_Max = 6,
} ETrackedDeviceClass;

రకనిర్వచనం గణన ETrackedControllerRole
{
	ETrackedControllerRole_TrackedControllerRole_Invalid = 0,
	ETracked_Controller_Role_Tracked_Controller_Role_ఎడమ_Hand = 1,
	ETracked_Controller_Role_Tracked_Controller_Role_కుడి_Hand = 2,
	ETracked_Controller_Role_Tracked_Controller_Role_Opt_బహిర్గతం = 3,
	ETrackedControllerRole_TrackedControllerRole_Treadmill = 4,
	ETrackedControllerRole_TrackedControllerRole_Stylus = 5,
	ETrackedControllerRole_TrackedControllerRole_Max = 5,
} ETrackedControllerRole;

రకనిర్వచనం గణన ETrackingUniverseOrigin
{
	ETrackingUniverseOrigin_TrackingUniverseSeated = 0,
	ETrackingUniverseOrigin_TrackingUniverseStanding = 1,
	ETrackingUniverseOrigin_TrackingUniverseRawAndUncalibrated = 2,
} ETrackingUniverseOrigin;

రకనిర్వచనం గణన EAdditionalRadioFeatures
{
	EAdditionalRadioFeatures_AdditionalRadioFeatures_None = 0,
	EAdditionalRadioFeatures_AdditionalRadioFeatures_HTCLinkBox = 1,
	EAdditional_Radio_Features_Additional_Radio_Features_అంతర్గత_Dongle = 2,
	EAdditionalRadioFeatures_AdditionalRadioFeatures_ExternalDongle = 4,
} EAdditionalRadioFeatures;

రకనిర్వచనం గణన ETrackedDeviceProperty
{
	ETrackedDeviceProperty_Prop_Invalid = 0,
	ETrackedDeviceProperty_Prop_TrackingSystemName_String = 1000,
	ETracked_Device_Property_Prop_Model_సంఖ్య_String = 1001,
	ETracked_Device_Property_Prop_Serial_సంఖ్య_String = 1002,
	ETrackedDeviceProperty_Prop_RenderModelName_String = 1003,
	ETracked_Device_Property_Prop_Will_Drift_లోపల_Yaw_Bool = 1004,
	ETrackedDeviceProperty_Prop_ManufacturerName_String = 1005,
	ETracked_Device_Property_Prop_Tracking_Firmware_సంస్కరణ_String = 1006,
	ETrackedDeviceProperty_Prop_HardwareRevision_String = 1007,
	ETrackedDeviceProperty_Prop_AllWirelessDongleDescriptions_String = 1008,
	ETrackedDeviceProperty_Prop_ConnectedWirelessDongle_String = 1009,
	ETrackedDeviceProperty_Prop_DeviceIsWireless_Bool = 1010,
	ETrackedDeviceProperty_Prop_DeviceIsCharging_Bool = 1011,
	ETrackedDeviceProperty_Prop_DeviceBatteryPercentage_Float = 1012,
	ETracked_Device_Property_Prop_స్థితి_Display_Transform_Matrix34 = 1013,
	ETracked_Device_Property_Prop_Firmware_Update_అందుబాటు_Bool = 1014,
	ETrackedDeviceProperty_Prop_Firmware_ManualUpdate_Bool = 1015,
	ETrackedDeviceProperty_Prop_Firmware_ManualUpdateURL_String = 1016,
	ETrackedDeviceProperty_Prop_HardwareRevision_Uint64 = 1017,
	ETracked_Device_Property_Prop_Firmware_సంస్కరణ_Uint64 = 1018,
	ETrackedDeviceProperty_Prop_FPGAVersion_Uint64 = 1019,
	ETrackedDeviceProperty_Prop_VRCVersion_Uint64 = 1020,
	ETracked_Device_Property_Prop_Radio_సంస్కరణ_Uint64 = 1021,
	ETracked_Device_Property_Prop_Dongle_సంస్కరణ_Uint64 = 1022,
	ETracked_Device_Property_Prop_ఖండం_Server_Shutdown_Bool = 1023,
	ETrackedDeviceProperty_Prop_CanUnifyCoordinateSystemWithHmd_Bool = 1024,
	ETracked_Device_Property_Prop_కలిగియుంది_Proximity_Sensor_Bool = 1025,
	ETracked_Device_Property_Prop_Device_Provides_Battery_స్థితి_Bool = 1026,
	ETrackedDeviceProperty_Prop_DeviceCanPowerOff_Bool = 1027,
	ETracked_Device_Property_Prop_Firmware_Programming_లక్ష్యం_String = 1028,
	ETrackedDeviceProperty_Prop_DeviceClass_Int32 = 1029,
	ETrackedDeviceProperty_Prop_HasCamera_Bool = 1030,
	ETracked_Device_Property_Prop_Driver_సంస్కరణ_String = 1031,
	ETrackedDeviceProperty_Prop_Firmware_ForceUpdateRequired_Bool = 1032,
	ETrackedDeviceProperty_Prop_ViveSystemButtonFixRequired_Bool = 1033,
	ETracked_Device_Property_Prop_మాతృ_Driver_Uint64 = 1034,
	ETracked_Device_Property_Prop_Resource_మూలం_String = 1035,
	ETrackedDeviceProperty_Prop_RegisteredDeviceType_String = 1036,
	ETracked_Device_Property_Prop_ఆదానం_Profile_మార్గం_String = 1037,
	ETrackedDeviceProperty_Prop_NeverTracked_Bool = 1038,
	ETracked_Device_Property_Prop_అంకె_Cameras_Int32 = 1039,
	ETracked_Device_Property_Prop_Camera_చట్రం_Layout_Int32 = 1040,
	ETracked_Device_Property_Prop_Camera_ప్రవాహం_Format_Int32 = 1041,
	ETracked_Device_Property_Prop_Additional_Device_Settings_మార్గం_String = 1042,
	ETrackedDeviceProperty_Prop_Identifiable_Bool = 1043,
	ETracked_Device_Property_Prop_Bootloader_సంస్కరణ_Uint64 = 1044,
	ETracked_Device_Property_Prop_Additional_System_Report_దత్తాంశం_String = 1045,
	ETracked_Device_Property_Prop_సంయుక్త_Firmware_సంస్కరణ_String = 1046,
	ETrackedDeviceProperty_Prop_Firmware_RemindUpdate_Bool = 1047,
	ETracked_Device_Property_Prop_Peripheral_Application_సంస్కరణ_Uint64 = 1048,
	ETracked_Device_Property_Prop_Manufacturer_Serial_సంఖ్య_String = 1049,
	ETracked_Device_Property_Prop_Computed_Serial_సంఖ్య_String = 1050,
	ETracked_Device_Property_Prop_Estimated_Device_మొదటి_Use_సమయం_Int32 = 1051,
	ETrackedDeviceProperty_Prop_DevicePowerUsage_Float = 1052,
	ETrackedDeviceProperty_Prop_IgnoreMotionForStandby_Bool = 1053,
	ETracked_Device_Property_Prop_Reports_సమయం_Since_VSync_Bool = 2000,
	ETracked_Device_Property_Prop_Seconds_From_Vsync_గమ్యం_Photons_Float = 2001,
	ETrackedDeviceProperty_Prop_DisplayFrequency_Float = 2002,
	ETrackedDeviceProperty_Prop_UserIpdMeters_Float = 2003,
	ETrackedDeviceProperty_Prop_CurrentUniverseId_Uint64 = 2004,
	ETracked_Device_Property_Prop_మునుపటి_Universe_Id_Uint64 = 2005,
	ETracked_Device_Property_Prop_Display_Firmware_సంస్కరణ_Uint64 = 2006,
	ETrackedDeviceProperty_Prop_IsOnDesktop_Bool = 2007,
	ETrackedDeviceProperty_Prop_DisplayMCType_Int32 = 2008,
	ETrackedDeviceProperty_Prop_DisplayMCOffset_Float = 2009,
	ETrackedDeviceProperty_Prop_DisplayMCScale_Float = 2010,
	ETrackedDeviceProperty_Prop_EdidVendorID_Int32 = 2011,
	ETracked_Device_Property_Prop_Display_MCImage_ఎడమ_String = 2012,
	ETracked_Device_Property_Prop_Display_MCImage_కుడి_String = 2013,
	ETrackedDeviceProperty_Prop_DisplayGCBlackClamp_Float = 2014,
	ETracked_Device_Property_Prop_Edid_లబ్ధం_ID_Int32 = 2015,
	ETracked_Device_Property_Prop_Camera_గమ్యం_తల_Transform_Matrix34 = 2016,
	ETrackedDeviceProperty_Prop_DisplayGCType_Int32 = 2017,
	ETrackedDeviceProperty_Prop_DisplayGCOffset_Float = 2018,
	ETrackedDeviceProperty_Prop_DisplayGCScale_Float = 2019,
	ETrackedDeviceProperty_Prop_DisplayGCPrescale_Float = 2020,
	ETrackedDeviceProperty_Prop_DisplayGCImage_String = 2021,
	ETracked_Device_Property_Prop_Lens_Center_ఎడమ_U_Float = 2022,
	ETracked_Device_Property_Prop_Lens_Center_ఎడమ_V_Float = 2023,
	ETracked_Device_Property_Prop_Lens_Center_కుడి_U_Float = 2024,
	ETracked_Device_Property_Prop_Lens_Center_కుడి_V_Float = 2025,
	ETracked_Device_Property_Prop_User_తల_గమ్యం_Eye_లోతు_Meters_Float = 2026,
	ETracked_Device_Property_Prop_Camera_Firmware_సంస్కరణ_Uint64 = 2027,
	ETrackedDeviceProperty_Prop_CameraFirmwareDescription_String = 2028,
	ETrackedDeviceProperty_Prop_DisplayFPGAVersion_Uint64 = 2029,
	ETracked_Device_Property_Prop_Display_Bootloader_సంస్కరణ_Uint64 = 2030,
	ETracked_Device_Property_Prop_Display_Hardware_సంస్కరణ_Uint64 = 2031,
	ETracked_Device_Property_Prop_Audio_Firmware_సంస్కరణ_Uint64 = 2032,
	ETracked_Device_Property_Prop_Camera_Compatibility_బహుళకం_Int32 = 2033,
	ETracked_Device_Property_Prop_Screenshot_Horizontal_క్షేత్రం_యొక్క_View_Degrees_Float = 2034,
	ETracked_Device_Property_Prop_Screenshot_Vertical_క్షేత్రం_యొక్క_View_Degrees_Float = 2035,
	ETrackedDeviceProperty_Prop_DisplaySuppressed_Bool = 2036,
	ETracked_Device_Property_Prop_Display_Allow_Night_బహుళకం_Bool = 2037,
	ETracked_Device_Property_Prop_Display_MCImage_వెడల్పు_Int32 = 2038,
	ETracked_Device_Property_Prop_Display_MCImage_ఎత్తు_Int32 = 2039,
	ETracked_Device_Property_Prop_Display_MCImage_అంకె_Channels_Int32 = 2040,
	ETracked_Device_Property_Prop_Display_MCImage_దత్తాంశం_ద్విమాన = 2041,
	ETracked_Device_Property_Prop_Seconds_From_Photons_గమ్యం_Vblank_Float = 2042,
	ETracked_Device_Property_Prop_Driver_ప్రత్యక్ష_బహుళకం_Sends_Vsync_Events_Bool = 2043,
	ETracked_Device_Property_Prop_Display_Debug_బహుళకం_Bool = 2044,
	ETrackedDeviceProperty_Prop_GraphicsAdapterLuid_Uint64 = 2045,
	ETracked_Device_Property_Prop_Driver_Provided_Chaperone_మార్గం_String = 2048,
	ETracked_Device_Property_Prop_Expected_Tracking_Reference_లెక్క_Int32 = 2049,
	ETracked_Device_Property_Prop_Expected_Controller_లెక్క_Int32 = 2050,
	ETracked_Device_Property_Prop_Named_Icon_మార్గం_Controller_ఎడమ_Device_Off_String = 2051,
	ETracked_Device_Property_Prop_Named_Icon_మార్గం_Controller_కుడి_Device_Off_String = 2052,
	ETracked_Device_Property_Prop_Named_Icon_మార్గం_Tracking_Reference_Device_Off_String = 2053,
	ETrackedDeviceProperty_Prop_DoNotApplyPrediction_Bool = 2054,
	ETracked_Device_Property_Prop_Camera_గమ్యం_తల_Transforms_Matrix34_Array = 2055,
	ETrackedDeviceProperty_Prop_DistortionMeshResolution_Int32 = 2056,
	ETrackedDeviceProperty_Prop_DriverIsDrawingControllers_Bool = 2057,
	ETracked_Device_Property_Prop_Driver_అభ్యర్థనలు_Application_Pause_Bool = 2058,
	ETracked_Device_Property_Prop_Driver_అభ్యర్థనలు_Reduced_Rendering_Bool = 2059,
	ETracked_Device_Property_Prop_Minimum_Ipd_అడుగు_Meters_Float = 2060,
	ETracked_Device_Property_Prop_Audio_Bridge_Firmware_సంస్కరణ_Uint64 = 2061,
	ETracked_Device_Property_Prop_Image_Bridge_Firmware_సంస్కరణ_Uint64 = 2062,
	ETracked_Device_Property_Prop_Imu_గమ్యం_తల_Transform_Matrix34 = 2063,
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
	ETracked_Device_Property_Prop_Hmd_స్తంభం_Correction_Setting_ఉపసర్గ_String = 2077,
	ETrackedDeviceProperty_Prop_CameraSupportsCompatibilityModes_Bool = 2078,
	ETracked_Device_Property_Prop_Supports_స్థలం_View_లోతు_Projection_Bool = 2079,
	ETracked_Device_Property_Prop_Display_అందుబాటు_చట్రం_Rates_Float_Array = 2080,
	ETracked_Device_Property_Prop_Display_Supports_గుణిజం_Framerates_Bool = 2081,
	ETracked_Device_Property_Prop_Display_Color_Mult_ఎడమ_Vector3 = 2082,
	ETracked_Device_Property_Prop_Display_Color_Mult_కుడి_Vector3 = 2083,
	ETrackedDeviceProperty_Prop_DisplaySupportsRuntimeFramerateChange_Bool = 2084,
	ETrackedDeviceProperty_Prop_DisplaySupportsAnalogGain_Bool = 2085,
	ETrackedDeviceProperty_Prop_DisplayMinAnalogGain_Float = 2086,
	ETrackedDeviceProperty_Prop_DisplayMaxAnalogGain_Float = 2087,
	ETracked_Device_Property_Prop_Camera_Exposure_సమయం_Float = 2088,
	ETrackedDeviceProperty_Prop_CameraGlobalGain_Float = 2089,
	ETrackedDeviceProperty_Prop_DashboardScale_Float = 2091,
	ETrackedDeviceProperty_Prop_PeerButtonInfo_String = 2092,
	ETrackedDeviceProperty_Prop_Hmd_SupportsHDR10_Bool = 2093,
	ETrackedDeviceProperty_Prop_IpdUIRangeMinMeters_Float = 2100,
	ETrackedDeviceProperty_Prop_IpdUIRangeMaxMeters_Float = 2101,
	ETrackedDeviceProperty_Prop_Hmd_SupportsHDCP14LegacyCompat_Bool = 2102,
	ETrackedDeviceProperty_Prop_Hmd_SupportsMicMonitoring_Bool = 2103,
	ETracked_Device_Property_Prop_Hmd_Supports_Display_పోర్టు_Training_బహుళకం_Bool = 2104,
	ETracked_Device_Property_Prop_Supports_స్థలం_View_ప్రత్యక్ష_Bool = 2105,
	ETrackedDeviceProperty_Prop_SupportsAppThrottling_Bool = 2106,
	ETrackedDeviceProperty_Prop_DSCVersion_Int32 = 2110,
	ETracked_Device_Property_Prop_DSCSlice_లెక్క_Int32 = 2111,
	ETrackedDeviceProperty_Prop_DSCBPPx16_Int32 = 2112,
	ETracked_Device_Property_Prop_Driver_Requested_Mura_Correction_బహుళకం_Int32 = 2200,
	ETracked_Device_Property_Prop_Driver_Requested_Mura_Feather_Inner_ఎడమ_Int32 = 2201,
	ETracked_Device_Property_Prop_Driver_Requested_Mura_Feather_Inner_కుడి_Int32 = 2202,
	ETracked_Device_Property_Prop_Driver_Requested_Mura_Feather_Inner_శిఖరం_Int32 = 2203,
	ETrackedDeviceProperty_Prop_DriverRequestedMuraFeather_InnerBottom_Int32 = 2204,
	ETracked_Device_Property_Prop_Driver_Requested_Mura_Feather_Outer_ఎడమ_Int32 = 2205,
	ETracked_Device_Property_Prop_Driver_Requested_Mura_Feather_Outer_కుడి_Int32 = 2206,
	ETracked_Device_Property_Prop_Driver_Requested_Mura_Feather_Outer_శిఖరం_Int32 = 2207,
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
	ETracked_Device_Property_Prop_క్షేత్రం_యొక్క_View_ఎడమ_Degrees_Float = 4000,
	ETracked_Device_Property_Prop_క్షేత్రం_యొక్క_View_కుడి_Degrees_Float = 4001,
	ETracked_Device_Property_Prop_క్షేత్రం_యొక్క_View_శిఖరం_Degrees_Float = 4002,
	ETracked_Device_Property_Prop_క్షేత్రం_యొక్క_View_Bottom_Degrees_Float = 4003,
	ETrackedDeviceProperty_Prop_TrackingRangeMinimumMeters_Float = 4004,
	ETracked_Device_Property_Prop_Tracking_Range_గరిష్ఠ_Meters_Float = 4005,
	ETracked_Device_Property_Prop_బహుళకం_Label_String = 4006,
	ETrackedDeviceProperty_Prop_CanWirelessIdentify_Bool = 4007,
	ETrackedDeviceProperty_Prop_Nonce_Int32 = 4008,
	ETracked_Device_Property_Prop_Icon_మార్గం_Name_String = 5000,
	ETracked_Device_Property_Prop_Named_Icon_మార్గం_Device_Off_String = 5001,
	ETracked_Device_Property_Prop_Named_Icon_మార్గం_Device_Searching_String = 5002,
	ETracked_Device_Property_Prop_Named_Icon_మార్గం_Device_Searching_Alert_String = 5003,
	ETracked_Device_Property_Prop_Named_Icon_మార్గం_Device_Ready_String = 5004,
	ETracked_Device_Property_Prop_Named_Icon_మార్గం_Device_Ready_Alert_String = 5005,
	ETracked_Device_Property_Prop_Named_Icon_మార్గం_Device_Not_Ready_String = 5006,
	ETracked_Device_Property_Prop_Named_Icon_మార్గం_Device_Standby_String = 5007,
	ETracked_Device_Property_Prop_Named_Icon_మార్గం_Device_Alert_దిగువ_String = 5008,
	ETracked_Device_Property_Prop_Named_Icon_మార్గం_Device_Standby_Alert_String = 5009,
	ETracked_Device_Property_Prop_Display_Hidden_Area_ద్విమాన_ప్రారంభం = 5100,
	ETracked_Device_Property_Prop_Display_Hidden_Area_ద్విమాన_చివర = 5150,
	ETracked_Device_Property_Prop_మాతృ_Container = 5151,
	ETrackedDeviceProperty_Prop_OverrideContainer_Uint64 = 5152,
	ETracked_Device_Property_Prop_User_Config_మార్గం_String = 6000,
	ETracked_Device_Property_Prop_Install_మార్గం_String = 6001,
	ETrackedDeviceProperty_Prop_HasDisplayComponent_Bool = 6002,
	ETrackedDeviceProperty_Prop_HasControllerComponent_Bool = 6003,
	ETrackedDeviceProperty_Prop_HasCameraComponent_Bool = 6004,
	ETracked_Device_Property_Prop_Has_Driver_ప్రత్యక్ష_బహుళకం_Component_Bool = 6005,
	ETrackedDeviceProperty_Prop_HasVirtualDisplayComponent_Bool = 6006,
	ETrackedDeviceProperty_Prop_HasSpatialAnchorsSupport_Bool = 6007,
	ETrackedDeviceProperty_Prop_ControllerType_String = 7000,
	ETracked_Device_Property_Prop_Controller_Hand_Selection_ప్రాధాన్యత_Int32 = 7002,
	ETracked_Device_Property_Prop_Vendor_Specific_Reserved_ప్రారంభం = 10000,
	ETracked_Device_Property_Prop_Vendor_Specific_Reserved_చివర = 10999,
	ETrackedDeviceProperty_Prop_TrackedDeviceProperty_Max = 1000000,
} ETrackedDeviceProperty;

రకనిర్వచనం గణన ETrackedPropertyError
{
	ETrackedPropertyError_TrackedProp_Success = 0,
	ETracked_Property_Error_Tracked_Prop_Wrong_దత్తాంశం_Type = 1,
	ETrackedPropertyError_TrackedProp_WrongDeviceClass = 2,
	ETracked_Property_Error_Tracked_Prop_బఫరు_Too_Small = 3,
	ETrackedPropertyError_TrackedProp_UnknownProperty = 4,
	ETrackedPropertyError_TrackedProp_InvalidDevice = 5,
	ETrackedPropertyError_TrackedProp_CouldNotContactServer = 6,
	ETracked_Property_Error_Tracked_Prop_విలువ_Not_Provided_By_Device = 7,
	ETracked_Property_Error_Tracked_Prop_String_Exceeds_గరిష్ఠ_నిడివి = 8,
	ETracked_Property_Error_Tracked_Prop_Not_Yet_అందుబాటు = 9,
	ETrackedPropertyError_TrackedProp_PermissionDenied = 10,
	ETrackedPropertyError_TrackedProp_InvalidOperation = 11,
	ETracked_Property_Error_Tracked_Prop_Cannot_Write_గమ్యం_Wildcards = 12,
	ETrackedPropertyError_TrackedProp_IPCReadFailure = 13,
	ETracked_Property_Error_Tracked_Prop_బహిర్గతం_యొక్క_జ్ఞాపకం = 14,
	ETrackedPropertyError_TrackedProp_InvalidContainer = 15,
} ETrackedPropertyError;

రకనిర్వచనం గణన EHmdTrackingStyle
{
	EHmdTrackingStyle_HmdTrackingStyle_Unknown = 0,
	EHmdTrackingStyle_HmdTrackingStyle_Lighthouse = 1,
	EHmd_Tracking_Style_Hmd_Tracking_Style_Outside_లోపల_Cameras = 2,
	EHmd_Tracking_Style_Hmd_Tracking_Style_Inside_బహిర్గతం_Cameras = 3,
} EHmdTrackingStyle;

రకనిర్వచనం గణన EVRSubmitFlags
{
	EVRSubmitFlags_Submit_Default = 0,
	EVRSubmitFlags_Submit_LensDistortionAlreadyApplied = 1,
	EVRSubmit_Flags_Submit_Gl_Render_బఫరు = 2,
	EVRSubmitFlags_Submit_Reserved = 4,
	EVRSubmitFlags_Submit_TextureWithPose = 8,
	EVRSubmit_Flags_Submit_Texture_With_లోతు = 16,
	EVRSubmit_Flags_Submit_చట్రం_Discontinuty = 32,
	EVRSubmit_Flags_Submit_Vulkan_Texture_With_Array_దత్తాంశం = 64,
	EVRSubmitFlags_Submit_GlArrayTexture = 128,
	EVRSubmitFlags_Submit_Reserved2 = 32768,
	EVRSubmitFlags_Submit_Reserved3 = 65536,
} EVRSubmitFlags;

రకనిర్వచనం గణన EVRState
{
	EVRState_VRState_Undefined = -1,
	EVRState_VRState_Off = 0,
	EVRState_VRState_Searching = 1,
	EVRState_VRState_Searching_Alert = 2,
	EVRState_VRState_Ready = 3,
	EVRState_VRState_Ready_Alert = 4,
	EVRState_VRState_NotReady = 5,
	EVRState_VRState_Standby = 6,
	EVRState_VRState_Ready_Alert_దిగువ = 7,
} EVRState;

రకనిర్వచనం గణన EVREventType
{
	EVREventType_VREvent_None = 0,
	EVREventType_VREvent_TrackedDeviceActivated = 100,
	EVREventType_VREvent_TrackedDeviceDeactivated = 101,
	EVREventType_VREvent_TrackedDeviceUpdated = 102,
	EVREventType_VREvent_TrackedDeviceUserInteractionStarted = 103,
	EVREventType_VREvent_TrackedDeviceUserInteractionEnded = 104,
	EVREvent_Type_VREvent_Ipd_మారింది = 105,
	EVREvent_Type_VREvent_Enter_Standby_బహుళకం = 106,
	EVREvent_Type_VREvent_Leave_Standby_బహుళకం = 107,
	EVREvent_Type_VREvent_Tracked_Device_Role_మారింది = 108,
	EVREvent_Type_VREvent_Watchdog_Wake_పైకి_Requested = 109,
	EVREvent_Type_VREvent_Lens_Distortion_మారింది = 110,
	EVREvent_Type_VREvent_Property_మారింది = 111,
	EVREventType_VREvent_WirelessDisconnect = 112,
	EVREventType_VREvent_WirelessReconnect = 113,
	EVREventType_VREvent_ButtonPress = 200,
	EVREventType_VREvent_ButtonUnpress = 201,
	EVREventType_VREvent_ButtonTouch = 202,
	EVREventType_VREvent_ButtonUntouch = 203,
	EVREventType_VREvent_Modal_Cancel = 257,
	EVREventType_VREvent_MouseMove = 300,
	EVREvent_Type_VREvent_Mouse_Button_కిందికి = 301,
	EVREvent_Type_VREvent_Mouse_Button_పైకి = 302,
	EVREventType_VREvent_FocusEnter = 303,
	EVREventType_VREvent_FocusLeave = 304,
	EVREventType_VREvent_ScrollDiscrete = 305,
	EVREventType_VREvent_TouchPadMove = 306,
	EVREvent_Type_VREvent_Overlay_Focus_మారింది = 307,
	EVREventType_VREvent_ReloadOverlays = 308,
	EVREventType_VREvent_ScrollSmooth = 309,
	EVREvent_Type_VREvent_తాళం_Mouse_Position = 310,
	EVREventType_VREvent_UnlockMousePosition = 311,
	EVREvent_Type_VREvent_ఆదానం_Focus_Captured = 400,
	EVREvent_Type_VREvent_ఆదానం_Focus_Released = 401,
	EVREvent_Type_VREvent_Scene_Application_మారింది = 404,
	EVREvent_Type_VREvent_ఆదానం_Focus_మారింది = 406,
	EVREventType_VREvent_SceneApplicationUsingWrongGraphicsAdapter = 408,
	EVREventType_VREvent_ActionBindingReloaded = 409,
	EVREventType_VREvent_HideRenderModels = 410,
	EVREventType_VREvent_ShowRenderModels = 411,
	EVREvent_Type_VREvent_Scene_Application_State_మారింది = 412,
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
	EVREvent_Type_VREvent_Overlay_Gamepad_Focus_కోల్పోయిన = 512,
	EVREvent_Type_VREvent_Overlay_Shared_Texture_మారింది = 513,
	EVREventType_VREvent_ScreenshotTriggered = 516,
	EVREventType_VREvent_ImageFailed = 517,
	EVREventType_VREvent_DashboardOverlayCreated = 518,
	EVREventType_VREvent_SwitchGamepadFocus = 519,
	EVREventType_VREvent_RequestScreenshot = 520,
	EVREvent_Type_VREvent_Screenshot_తీసుకున్న = 521,
	EVREventType_VREvent_ScreenshotFailed = 522,
	EVREvent_Type_VREvent_Submit_Screenshot_గమ్యం_Dashboard = 523,
	EVREvent_Type_VREvent_Screenshot_పురోగతి_గమ్యం_Dashboard = 524,
	EVREvent_Type_VREvent_Primary_Dashboard_Device_మారింది = 525,
	EVREvent_Type_VREvent_స్థలం_View_Shown = 526,
	EVREvent_Type_VREvent_స్థలం_View_Hidden = 527,
	EVREventType_VREvent_ShowUI = 528,
	EVREventType_VREvent_ShowDevTools = 529,
	EVREventType_VREvent_DesktopViewUpdating = 530,
	EVREventType_VREvent_DesktopViewReady = 531,
	EVREvent_Type_VREvent_ప్రారంభం_Dashboard = 532,
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
	EVREvent_Type_VREvent_Invalidate_మార్పిడి_Texture_Sets = 706,
	EVREvent_Type_VREvent_Chaperone_దత్తాంశం_Has_మారింది = 800,
	EVREvent_Type_VREvent_Chaperone_Universe_Has_మారింది = 801,
	EVREvent_Type_VREvent_Chaperone_తాత్కాలిక_దత్తాంశం_Has_మారింది = 802,
	EVREvent_Type_VREvent_Chaperone_Settings_Have_మారింది = 803,
	EVREventType_VREvent_SeatedZeroPoseReset = 804,
	EVREventType_VREvent_ChaperoneFlushCache = 805,
	EVREvent_Type_VREvent_Chaperone_స్థలం_అమరిక_Starting = 806,
	EVREvent_Type_VREvent_Chaperone_స్థలం_అమరిక_ముగిసిన = 807,
	EVREventType_VREvent_StandingZeroPoseReset = 808,
	EVREvent_Type_VREvent_Audio_Settings_Have_మారింది = 820,
	EVREvent_Type_VREvent_Background_Setting_Has_మారింది = 850,
	EVREvent_Type_VREvent_Camera_Settings_Have_మారింది = 851,
	EVREvent_Type_VREvent_Reprojection_Setting_Has_మారింది = 852,
	EVREvent_Type_VREvent_Model_Skin_Settings_Have_మారింది = 853,
	EVREvent_Type_VREvent_Environment_Settings_Have_మారింది = 854,
	EVREvent_Type_VREvent_Power_Settings_Have_మారింది = 855,
	EVREvent_Type_VREvent_Enable_Home_App_Settings_Have_మారింది = 856,
	EVREvent_Type_VREvent_Steam_VRSection_Setting_మారింది = 857,
	EVREvent_Type_VREvent_Lighthouse_Section_Setting_మారింది = 858,
	EVREvent_Type_VREvent_Null_Section_Setting_మారింది = 859,
	EVREvent_Type_VREvent_User_Interface_Section_Setting_మారింది = 860,
	EVREvent_Type_VREvent_Notifications_Section_Setting_మారింది = 861,
	EVREvent_Type_VREvent_Keyboard_Section_Setting_మారింది = 862,
	EVREvent_Type_VREvent_Perf_Section_Setting_మారింది = 863,
	EVREvent_Type_VREvent_Dashboard_Section_Setting_మారింది = 864,
	EVREvent_Type_VREvent_Web_Interface_Section_Setting_మారింది = 865,
	EVREvent_Type_VREvent_Trackers_Section_Setting_మారింది = 866,
	EVREvent_Type_VREvent_చివరి_తెలిసిన_Section_Setting_మారింది = 867,
	EVREvent_Type_VREvent_Dismissed_Warnings_Section_Setting_మారింది = 868,
	EVREvent_Type_VREvent_Gpu_వేగం_Section_Setting_మారింది = 869,
	EVREvent_Type_VREvent_Windows_MRSection_Setting_మారింది = 870,
	EVREvent_Type_VREvent_Other_Section_Setting_మారింది = 871,
	EVREvent_Type_VREvent_స్థితి_Update = 900,
	EVREventType_VREvent_WebInterface_InstallDriverCompleted = 950,
	EVREventType_VREvent_MCImageUpdated = 1000,
	EVREventType_VREvent_FirmwareUpdateStarted = 1100,
	EVREvent_Type_VREvent_Firmware_Update_ముగిసిన = 1101,
	EVREventType_VREvent_KeyboardClosed = 1200,
	EVREvent_Type_VREvent_Keyboard_Char_ఆదానం = 1201,
	EVREvent_Type_VREvent_Keyboard_పూర్తి = 1202,
	EVREventType_VREvent_ApplicationListUpdated = 1303,
	EVREvent_Type_VREvent_Application_Mime_Type_ఎక్కించు = 1304,
	EVREventType_VREvent_ProcessConnected = 1306,
	EVREventType_VREvent_ProcessDisconnected = 1307,
	EVREventType_VREvent_Compositor_ChaperoneBoundsShown = 1410,
	EVREventType_VREvent_Compositor_ChaperoneBoundsHidden = 1411,
	EVREventType_VREvent_Compositor_DisplayDisconnected = 1412,
	EVREventType_VREvent_Compositor_DisplayReconnected = 1413,
	EVREventType_VREvent_Compositor_HDCPError = 1414,
	EVREventType_VREvent_Compositor_ApplicationNotResponding = 1415,
	EVREventType_VREvent_Compositor_ApplicationResumed = 1416,
	EVREvent_Type_VREvent_Compositor_బహిర్గతం_యొక్క_Video_జ్ఞాపకం = 1417,
	EVREvent_Type_VREvent_Compositor_Display_బహుళకం_Not_Supported = 1418,
	EVREventType_VREvent_Compositor_StageOverrideReady = 1419,
	EVREventType_VREvent_Compositor_RequestDisconnectReconnect = 1420,
	EVREvent_Type_VREvent_Tracked_Camera_ప్రారంభం_Video_ప్రవాహం = 1500,
	EVREvent_Type_VREvent_Tracked_Camera_Stop_Video_ప్రవాహం = 1501,
	EVREvent_Type_VREvent_Tracked_Camera_Pause_Video_ప్రవాహం = 1502,
	EVREvent_Type_VREvent_Tracked_Camera_Resume_Video_ప్రవాహం = 1503,
	EVREventType_VREvent_TrackedCamera_EditingSurface = 1550,
	EVREventType_VREvent_PerformanceTest_EnableCapture = 1600,
	EVREventType_VREvent_PerformanceTest_DisableCapture = 1601,
	EVREventType_VREvent_PerformanceTest_FidelityLevel = 1602,
	EVREvent_Type_VREvent_సందేశం_Overlay_Closed = 1650,
	EVREvent_Type_VREvent_సందేశం_Overlay_Close_Requested = 1651,
	EVREvent_Type_VREvent_ఆదానం_Haptic_Vibration = 1700,
	EVREvent_Type_VREvent_ఆదానం_Binding_ఎక్కించు_Failed = 1701,
	EVREvent_Type_VREvent_ఆదానం_Binding_ఎక్కించు_Successful = 1702,
	EVREvent_Type_VREvent_ఆదానం_Action_Manifest_Reloaded = 1703,
	EVREvent_Type_VREvent_ఆదానం_Action_Manifest_ఎక్కించు_Failed = 1704,
	EVREvent_Type_VREvent_ఆదానం_పురోగతి_Update = 1705,
	EVREvent_Type_VREvent_ఆదానం_Tracker_Activated = 1706,
	EVREvent_Type_VREvent_ఆదానం_Bindings_Updated = 1707,
	EVREvent_Type_VREvent_ఆదానం_Binding_Subscription_మారింది = 1708,
	EVREventType_VREvent_SpatialAnchors_PoseUpdated = 1800,
	EVREventType_VREvent_SpatialAnchors_DescriptorUpdated = 1801,
	EVREventType_VREvent_SpatialAnchors_RequestPoseUpdate = 1802,
	EVREventType_VREvent_SpatialAnchors_RequestDescriptorUpdate = 1803,
	EVREventType_VREvent_SystemReport_Started = 1900,
	EVREventType_VREvent_Monitor_ShowHeadsetView = 2000,
	EVREventType_VREvent_Monitor_HideHeadsetView = 2001,
	EVREvent_Type_VREvent_Vendor_Specific_Reserved_ప్రారంభం = 10000,
	EVREvent_Type_VREvent_Vendor_Specific_Reserved_చివర = 19999,
} EVREventType;

రకనిర్వచనం గణన EDeviceActivityLevel
{
	EDeviceActivityLevel_k_EDeviceActivityLevel_Unknown = -1,
	EDeviceActivityLevel_k_EDeviceActivityLevel_Idle = 0,
	EDeviceActivityLevel_k_EDeviceActivityLevel_UserInteraction = 1,
	EDeviceActivityLevel_k_EDeviceActivityLevel_UserInteraction_Timeout = 2,
	EDeviceActivityLevel_k_EDeviceActivityLevel_Standby = 3,
	EDeviceActivityLevel_k_EDeviceActivityLevel_Idle_Timeout = 4,
} EDeviceActivityLevel;

రకనిర్వచనం గణన EVRButtonId
{
	EVRButtonId_k_EButton_System = 0,
	EVRButtonId_k_EButton_ApplicationMenu = 1,
	EVRButtonId_k_EButton_Grip = 2,
	EVRButton_Id_k_EButton_DPad_ఎడమ = 3,
	EVRButton_Id_k_EButton_DPad_పైకి = 4,
	EVRButton_Id_k_EButton_DPad_కుడి = 5,
	EVRButton_Id_k_EButton_DPad_కిందికి = 6,
	EVRButtonId_k_EButton_A = 7,
	EVRButtonId_k_EButton_ProximitySensor = 31,
	EVRButtonId_k_EButton_Axis0 = 32,
	EVRButtonId_k_EButton_Axis1 = 33,
	EVRButtonId_k_EButton_Axis2 = 34,
	EVRButtonId_k_EButton_Axis3 = 35,
	EVRButtonId_k_EButton_Axis4 = 36,
	EVRButtonId_k_EButton_SteamVR_Touchpad = 32,
	EVRButtonId_k_EButton_SteamVR_Trigger = 33,
	EVRButton_Id_k_EButton_Dashboard_వెనుక = 2,
	EVRButton_Id_k_EButton_సూచీ_Controller_A = 2,
	EVRButton_Id_k_EButton_సూచీ_Controller_B = 1,
	EVRButton_Id_k_EButton_సూచీ_Controller_Joy_Stick = 35,
	EVRButtonId_k_EButton_Max = 64,
} EVRButtonId;

రకనిర్వచనం గణన EVRMouseButton
{
	EVRMouse_Button_VRMouse_Button_ఎడమ = 1,
	EVRMouse_Button_VRMouse_Button_కుడి = 2,
	EVRMouse_Button_VRMouse_Button_మధ్య = 4,
} EVRMouseButton;

రకనిర్వచనం గణన EShowUIType
{
	EShowUIType_ShowUI_ControllerBinding = 0,
	EShowUIType_ShowUI_ManageTrackers = 1,
	EShowUIType_ShowUI_Pairing = 3,
	EShowUIType_ShowUI_Settings = 4,
	EShowUIType_ShowUI_DebugCommands = 5,
	EShow_UIType_Show_UI_నిండిన_Controller_Binding = 6,
	EShowUIType_ShowUI_ManageDrivers = 7,
} EShowUIType;

రకనిర్వచనం గణన EHDCPError
{
	EHDCPError_HDCPError_None = 0,
	EHDCPError_HDCPError_Link_కోల్పోయిన = 1,
	EHDCPError_HDCPError_Tampered = 2,
	EHDCPError_HDCPError_DeviceRevoked = 3,
	EHDCPError_HDCPError_Unknown = 4,
} EHDCPError;

రకనిర్వచనం గణన EVRComponentProperty
{
	EVRComponentProperty_VRComponentProperty_IsStatic = 1,
	EVRComponentProperty_VRComponentProperty_IsVisible = 2,
	EVRComponentProperty_VRComponentProperty_IsTouched = 4,
	EVRComponentProperty_VRComponentProperty_IsPressed = 8,
	EVRComponentProperty_VRComponentProperty_IsScrolled = 16,
	EVRComponentProperty_VRComponentProperty_IsHighlighted = 32,
} EVRComponentProperty;

రకనిర్వచనం గణన EVRInputError
{
	EVRInputError_VRInputError_None = 0,
	EVRInput_Error_VRInput_Error_Name_Not_దొరికింది = 1,
	EVRInputError_VRInputError_WrongType = 2,
	EVRInputError_VRInputError_InvalidHandle = 3,
	EVRInputError_VRInputError_InvalidParam = 4,
	EVRInputError_VRInputError_NoSteam = 5,
	EVRInput_Error_VRInput_Error_Max_సామర్థ్యం_Reached = 6,
	EVRInputError_VRInputError_IPCError = 7,
	EVRInput_Error_VRInput_Error_No_చురుకైన_Action_సమితి = 8,
	EVRInputError_VRInputError_InvalidDevice = 9,
	EVRInputError_VRInputError_InvalidSkeleton = 10,
	EVRInput_Error_VRInput_Error_Invalid_Bone_లెక్క = 11,
	EVRInput_Error_VRInput_Error_Invalid_Compressed_దత్తాంశం = 12,
	EVRInput_Error_VRInput_Error_No_దత్తాంశం = 13,
	EVRInput_Error_VRInput_Error_బఫరు_Too_Small = 14,
	EVRInputError_VRInputError_MismatchedActionManifest = 15,
	EVRInput_Error_VRInput_Error_Missing_Skeleton_దత్తాంశం = 16,
	EVRInput_Error_VRInput_Error_Invalid_Bone_సూచీ = 17,
	EVRInput_Error_VRInput_Error_Invalid_ప్రాధాన్యత = 18,
	EVRInputError_VRInputError_PermissionDenied = 19,
	EVRInputError_VRInputError_InvalidRenderModel = 20,
} EVRInputError;

రకనిర్వచనం గణన EVRSpatialAnchorError
{
	EVRSpatialAnchorError_VRSpatialAnchorError_Success = 0,
	EVRSpatial_Anchor_Error_VRSpatial_Anchor_Error_అంతర్గత = 1,
	EVRSpatialAnchorError_VRSpatialAnchorError_UnknownHandle = 2,
	EVRSpatialAnchorError_VRSpatialAnchorError_ArrayTooSmall = 3,
	EVRSpatialAnchorError_VRSpatialAnchorError_InvalidDescriptorChar = 4,
	EVRSpatial_Anchor_Error_VRSpatial_Anchor_Error_Not_Yet_అందుబాటు = 5,
	EVRSpatial_Anchor_Error_VRSpatial_Anchor_Error_Not_అందుబాటు_లోపల_This_Universe = 6,
	EVRSpatialAnchorError_VRSpatialAnchorError_PermanentlyUnavailable = 7,
	EVRSpatialAnchorError_VRSpatialAnchorError_WrongDriver = 8,
	EVRSpatialAnchorError_VRSpatialAnchorError_DescriptorTooLong = 9,
	EVRSpatialAnchorError_VRSpatialAnchorError_Unknown = 10,
	EVRSpatial_Anchor_Error_VRSpatial_Anchor_Error_No_స్థలం_Calibration = 11,
	EVRSpatial_Anchor_Error_VRSpatial_Anchor_Error_Invalid_వాదం = 12,
	EVRSpatialAnchorError_VRSpatialAnchorError_UnknownDriver = 13,
} EVRSpatialAnchorError;

రకనిర్వచనం గణన EHiddenAreaMeshType
{
	EHiddenAreaMeshType_k_eHiddenAreaMesh_Standard = 0,
	EHiddenAreaMeshType_k_eHiddenAreaMesh_Inverse = 1,
	EHidden_Area_Mesh_Type_k_e_Hidden_Area_Mesh_పంక్తి_Loop = 2,
	EHiddenAreaMeshType_k_eHiddenAreaMesh_Max = 3,
} EHiddenAreaMeshType;

రకనిర్వచనం గణన EVRControllerAxisType
{
	EVRControllerAxisType_k_eControllerAxis_None = 0,
	EVRControllerAxisType_k_eControllerAxis_TrackPad = 1,
	EVRControllerAxisType_k_eControllerAxis_Joystick = 2,
	EVRControllerAxisType_k_eControllerAxis_Trigger = 3,
} EVRControllerAxisType;

రకనిర్వచనం గణన EVRControllerEventOutputType
{
	EVRControllerEventOutputType_ControllerEventOutput_OSEvents = 0,
	EVRControllerEventOutputType_ControllerEventOutput_VREvents = 1,
} EVRControllerEventOutputType;

రకనిర్వచనం గణన ECollisionBoundsStyle
{
	ECollisionBoundsStyle_COLLISION_BOUNDS_STYLE_BEGINNER = 0,
	ECollisionBoundsStyle_COLLISION_BOUNDS_STYLE_INTERMEDIATE = 1,
	ECollisionBoundsStyle_COLLISION_BOUNDS_STYLE_SQUARES = 2,
	ECollisionBoundsStyle_COLLISION_BOUNDS_STYLE_ADVANCED = 3,
	ECollisionBoundsStyle_COLLISION_BOUNDS_STYLE_NONE = 4,
	ECollision_Bounds_Style_COLLISION_BOUNDS_STYLE_లెక్క = 5,
} ECollisionBoundsStyle;

రకనిర్వచనం గణన EVROverlayError
{
	EVROverlayError_VROverlayError_None = 0,
	EVROverlayError_VROverlayError_UnknownOverlay = 10,
	EVROverlayError_VROverlayError_InvalidHandle = 11,
	EVROverlayError_VROverlayError_PermissionDenied = 12,
	EVROverlay_Error_VROverlay_Error_Overlay_హద్దు_Exceeded = 13,
	EVROverlayError_VROverlayError_WrongVisibilityType = 14,
	EVROverlay_Error_VROverlay_Error_కీలకం_Too_Long = 15,
	EVROverlayError_VROverlayError_NameTooLong = 16,
	EVROverlay_Error_VROverlay_Error_కీలకం_లోపల_Use = 17,
	EVROverlayError_VROverlayError_WrongTransformType = 18,
	EVROverlayError_VROverlayError_InvalidTrackedDevice = 19,
	EVROverlayError_VROverlayError_InvalidParameter = 20,
	EVROverlayError_VROverlayError_ThumbnailCantBeDestroyed = 21,
	EVROverlayError_VROverlayError_ArrayTooSmall = 22,
	EVROverlayError_VROverlayError_RequestFailed = 23,
	EVROverlayError_VROverlayError_InvalidTexture = 24,
	EVROverlay_Error_VROverlay_Error_Unable_గమ్యం_ఎక్కించు_File = 25,
	EVROverlay_Error_VROverlay_Error_Keyboard_Already_లోపల_Use = 26,
	EVROverlayError_VROverlayError_NoNeighbor = 27,
	EVROverlay_Error_VROverlay_Error_Too_Many_ముసుగు_Primitives = 29,
	EVROverlay_Error_VROverlay_Error_Bad_ముసుగు_Primitive = 30,
	EVROverlayError_VROverlayError_TextureAlreadyLocked = 31,
	EVROverlay_Error_VROverlay_Error_Texture_తాళం_సామర్థ్యం_Reached = 32,
	EVROverlayError_VROverlayError_TextureNotLocked = 33,
	EVROverlay_Error_VROverlay_Error_Timed_బహిర్గతం = 34,
} EVROverlayError;

రకనిర్వచనం గణన EVRApplicationType
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
	EVRApplication_Type_VRApplication_స్థలం_View = 13,
	EVRApplicationType_VRApplication_Max = 14,
} EVRApplicationType;

రకనిర్వచనం గణన EVRFirmwareError
{
	EVRFirmwareError_VRFirmwareError_None = 0,
	EVRFirmwareError_VRFirmwareError_Success = 1,
	EVRFirmwareError_VRFirmwareError_Fail = 2,
} EVRFirmwareError;

రకనిర్వచనం గణన EVRNotificationError
{
	EVRNotificationError_VRNotificationError_OK = 0,
	EVRNotificationError_VRNotificationError_InvalidNotificationId = 100,
	EVRNotification_Error_VRNotification_Error_Notification_వరుస_నిండిన = 101,
	EVRNotificationError_VRNotificationError_InvalidOverlayHandle = 102,
	EVRNotification_Error_VRNotification_Error_System_With_User_విలువ_Already_Exists = 103,
} EVRNotificationError;

రకనిర్వచనం గణన EVRSkeletalMotionRange
{
	EVRSkeletalMotionRange_VRSkeletalMotionRange_WithController = 0,
	EVRSkeletalMotionRange_VRSkeletalMotionRange_WithoutController = 1,
} EVRSkeletalMotionRange;

రకనిర్వచనం గణన EVRSkeletalTrackingLevel
{
	EVRSkeletalTrackingLevel_VRSkeletalTracking_Estimated = 0,
	EVRSkeletalTrackingLevel_VRSkeletalTracking_Partial = 1,
	EVRSkeletal_Tracking_Level_VRSkeletal_Tracking_నిండిన = 2,
	EVRSkeletal_Tracking_Level_VRSkeletal_Tracking_Level_లెక్క = 3,
	EVRSkeletalTrackingLevel_VRSkeletalTrackingLevel_Max = 2,
} EVRSkeletalTrackingLevel;

రకనిర్వచనం గణన EVRInitError
{
	EVRInitError_VRInitError_None = 0,
	EVRInitError_VRInitError_Unknown = 1,
	EVRInit_Error_VRInit_Error_Init_Installation_Not_దొరికింది = 100,
	EVRInitError_VRInitError_Init_InstallationCorrupt = 101,
	EVRInit_Error_VRInit_Error_Init_VRClient_DLLNot_దొరికింది = 102,
	EVRInit_Error_VRInit_Error_Init_File_Not_దొరికింది = 103,
	EVRInit_Error_VRInit_Error_Init_Factory_Not_దొరికింది = 104,
	EVRInit_Error_VRInit_Error_Init_Interface_Not_దొరికింది = 105,
	EVRInitError_VRInitError_Init_InvalidInterface = 106,
	EVRInitError_VRInitError_Init_UserConfigDirectoryInvalid = 107,
	EVRInit_Error_VRInit_Error_Init_Hmd_Not_దొరికింది = 108,
	EVRInitError_VRInitError_Init_NotInitialized = 109,
	EVRInit_Error_VRInit_Error_Init_మార్గం_Registry_Not_దొరికింది = 110,
	EVRInit_Error_VRInit_Error_Init_No_Config_మార్గం = 111,
	EVRInit_Error_VRInit_Error_Init_No_Log_మార్గం = 112,
	EVRInit_Error_VRInit_Error_Init_మార్గం_Registry_Not_Writable = 113,
	EVRInitError_VRInitError_Init_AppInfoInitFailed = 114,
	EVRInitError_VRInitError_Init_Retry = 115,
	EVRInitError_VRInitError_Init_InitCanceledByUser = 116,
	EVRInitError_VRInitError_Init_AnotherAppLaunching = 117,
	EVRInitError_VRInitError_Init_SettingsInitFailed = 118,
	EVRInit_Error_VRInit_Error_Init_Shutting_కిందికి = 119,
	EVRInitError_VRInitError_Init_TooManyObjects = 120,
	EVRInitError_VRInitError_Init_NoServerForBackgroundApp = 121,
	EVRInitError_VRInitError_Init_NotSupportedWithCompositor = 122,
	EVRInit_Error_VRInit_Error_Init_Not_అందుబాటు_గమ్యం_Utility_Apps = 123,
	EVRInit_Error_VRInit_Error_Init_అంతర్గత = 124,
	EVRInitError_VRInitError_Init_HmdDriverIdIsNone = 125,
	EVRInit_Error_VRInit_Error_Init_Hmd_Not_దొరికింది_Presence_Failed = 126,
	EVRInit_Error_VRInit_Error_Init_VRMonitor_Not_దొరికింది = 127,
	EVRInitError_VRInitError_Init_VRMonitorStartupFailed = 128,
	EVRInit_Error_VRInit_Error_Init_దిగువ_Power_Watchdog_Not_Supported = 129,
	EVRInitError_VRInitError_Init_InvalidApplicationType = 130,
	EVRInit_Error_VRInit_Error_Init_Not_అందుబాటు_గమ్యం_Watchdog_Apps = 131,
	EVRInit_Error_VRInit_Error_Init_Watchdog_Disabled_లోపల_Settings = 132,
	EVRInit_Error_VRInit_Error_Init_VRDashboard_Not_దొరికింది = 133,
	EVRInitError_VRInitError_Init_VRDashboardStartupFailed = 134,
	EVRInit_Error_VRInit_Error_Init_VRHome_Not_దొరికింది = 135,
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
	EVRInit_Error_VRInit_Error_Init_Prism_Startup_Timed_బహిర్గతం = 152,
	EVRInit_Error_VRInit_Error_Init_Could_Not_ప్రారంభం_Prism = 153,
	EVRInitError_VRInitError_Init_PrismClientInitFailed = 154,
	EVRInit_Error_VRInit_Error_Init_Prism_Client_ప్రారంభం_Failed = 155,
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
	EVRInit_Error_VRInit_Error_Init_VRDashboard_మార్గం_Failure = 167,
	EVRInitError_VRInitError_Driver_Failed = 200,
	EVRInitError_VRInitError_Driver_Unknown = 201,
	EVRInitError_VRInitError_Driver_HmdUnknown = 202,
	EVRInitError_VRInitError_Driver_NotLoaded = 203,
	EVRInit_Error_VRInit_Error_Driver_Runtime_బహిర్గతం_యొక్క_Date = 204,
	EVRInit_Error_VRInit_Error_Driver_Hmd_లోపల_Use = 205,
	EVRInitError_VRInitError_Driver_NotCalibrated = 206,
	EVRInitError_VRInitError_Driver_CalibrationInvalid = 207,
	EVRInit_Error_VRInit_Error_Driver_Hmd_Display_Not_దొరికింది = 208,
	EVRInitError_VRInitError_Driver_TrackedDeviceInterfaceUnknown = 209,
	EVRInit_Error_VRInit_Error_Driver_Hmd_Driver_Id_బహిర్గతం_యొక్క_Bounds = 211,
	EVRInitError_VRInitError_Driver_HmdDisplayMirrored = 212,
	EVRInit_Error_VRInit_Error_Driver_Hmd_Display_Not_దొరికింది_Laptop = 213,
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
	EVRInit_Error_VRInit_Error_IPC_Connect_Failed_After_గుణిజం_Attempts = 308,
	EVRInit_Error_VRInit_Error_IPC_Connect_Failed_After_లక్ష్యం_Exited = 309,
	EVRInitError_VRInitError_IPC_NamespaceUnavailable = 310,
	EVRInitError_VRInitError_Compositor_Failed = 400,
	EVRInitError_VRInitError_Compositor_D3D11HardwareRequired = 401,
	EVRInitError_VRInitError_Compositor_FirmwareRequiresUpdate = 402,
	EVRInitError_VRInitError_Compositor_OverlayInitFailed = 403,
	EVRInitError_VRInitError_Compositor_ScreenshotsInitFailed = 404,
	EVRInit_Error_VRInit_Error_Compositor_Unable_గమ్యం_Create_Device = 405,
	EVRInitError_VRInitError_Compositor_SharedStateIsNull = 406,
	EVRInitError_VRInitError_Compositor_NotificationManagerIsNull = 407,
	EVRInitError_VRInitError_Compositor_ResourceManagerClientIsNull = 408,
	EVRInit_Error_VRInit_Error_Compositor_సందేశం_Overlay_Shared_State_Init_Failure = 409,
	EVRInitError_VRInitError_Compositor_PropertiesInterfaceIsNull = 410,
	EVRInit_Error_VRInit_Error_Compositor_Create_Fullscreen_కిటికీ_Failed = 411,
	EVRInitError_VRInitError_Compositor_SettingsInterfaceIsNull = 412,
	EVRInit_Error_VRInit_Error_Compositor_Failed_గమ్యం_Show_కిటికీ = 413,
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
	EVRInit_Error_VRInit_Error_Compositor_Failed_గమ్యం_కనుగొను_Display_బహుళకం = 425,
	EVRInit_Error_VRInit_Error_Compositor_Failed_గమ్యం_Create_మార్పిడి_Chain = 426,
	EVRInit_Error_VRInit_Error_Compositor_Failed_గమ్యం_Get_వెనుక_బఫరు = 427,
	EVRInit_Error_VRInit_Error_Compositor_Failed_గమ్యం_Create_Render_లక్ష్యం = 428,
	EVRInit_Error_VRInit_Error_Compositor_Failed_గమ్యం_Create_DXGI2_మార్పిడి_Chain = 429,
	EVRInit_Error_VRInit_Error_Compositor_Failedto_Get_DXGI2_వెనుక_బఫరు = 430,
	EVRInit_Error_VRInit_Error_Compositor_Failed_గమ్యం_Create_DXGI2_Render_లక్ష్యం = 431,
	EVRInit_Error_VRInit_Error_Compositor_Failed_గమ్యం_Get_DXGIDevice_Interface = 432,
	EVRInit_Error_VRInit_Error_Compositor_Select_Display_బహుళకం = 433,
	EVRInit_Error_VRInit_Error_Compositor_Failed_గమ్యం_Create_Nv_APIRender_Targets = 434,
	EVRInit_Error_VRInit_Error_Compositor_Nv_APISet_Display_బహుళకం = 435,
	EVRInit_Error_VRInit_Error_Compositor_Failed_గమ్యం_Create_ప్రత్యక్ష_బహుళకం_Display = 436,
	EVRInitError_VRInitError_Compositor_InvalidHmdPropertyContainer = 437,
	EVRInitError_VRInitError_Compositor_UpdateDisplayFrequency = 438,
	EVRInitError_VRInitError_Compositor_CreateRasterizerState = 439,
	EVRInitError_VRInitError_Compositor_CreateWireframeRasterizerState = 440,
	EVRInitError_VRInitError_Compositor_CreateSamplerState = 441,
	EVRInit_Error_VRInit_Error_Compositor_Create_Clamp_గమ్యం_Border_Sampler_State = 442,
	EVRInitError_VRInitError_Compositor_CreateAnisoSamplerState = 443,
	EVRInitError_VRInitError_Compositor_CreateOverlaySamplerState = 444,
	EVRInitError_VRInitError_Compositor_CreatePanoramaSamplerState = 445,
	EVRInitError_VRInitError_Compositor_CreateFontSamplerState = 446,
	EVRInitError_VRInitError_Compositor_CreateNoBlendState = 447,
	EVRInitError_VRInitError_Compositor_CreateBlendState = 448,
	EVRInitError_VRInitError_Compositor_CreateAlphaBlendState = 449,
	EVRInit_Error_VRInit_Error_Compositor_Create_Blend_State_ముసుగు_R = 450,
	EVRInit_Error_VRInit_Error_Compositor_Create_Blend_State_ముసుగు_G = 451,
	EVRInit_Error_VRInit_Error_Compositor_Create_Blend_State_ముసుగు_B = 452,
	EVRInit_Error_VRInit_Error_Compositor_Create_లోతు_Stencil_State = 453,
	EVRInit_Error_VRInit_Error_Compositor_Create_లోతు_Stencil_State_No_Write = 454,
	EVRInit_Error_VRInit_Error_Compositor_Create_లోతు_Stencil_State_No_లోతు = 455,
	EVRInitError_VRInitError_Compositor_CreateFlushTexture = 456,
	EVRInitError_VRInitError_Compositor_CreateDistortionSurfaces = 457,
	EVRInit_Error_VRInit_Error_Compositor_Create_Constant_బఫరు = 458,
	EVRInit_Error_VRInit_Error_Compositor_Create_Hmd_Pose_Constant_బఫరు = 459,
	EVRInit_Error_VRInit_Error_Compositor_Create_Hmd_Pose_Staging_Constant_బఫరు = 460,
	EVRInit_Error_VRInit_Error_Compositor_Create_Shared_చట్రం_Info_Constant_బఫరు = 461,
	EVRInit_Error_VRInit_Error_Compositor_Create_Overlay_Constant_బఫరు = 462,
	EVRInit_Error_VRInit_Error_Compositor_Create_Scene_Texture_సూచీ_Constant_బఫరు = 463,
	EVRInit_Error_VRInit_Error_Compositor_Create_Readable_Scene_Texture_సూచీ_Constant_బఫరు = 464,
	EVRInit_Error_VRInit_Error_Compositor_Create_Layer_Graphics_Texture_సూచీ_Constant_బఫరు = 465,
	EVRInit_Error_VRInit_Error_Compositor_Create_Layer_Compute_Texture_సూచీ_Constant_బఫరు = 466,
	EVRInit_Error_VRInit_Error_Compositor_Create_Layer_Compute_Scene_Texture_సూచీ_Constant_బఫరు = 467,
	EVRInit_Error_VRInit_Error_Compositor_Create_Compute_Hmd_Pose_Constant_బఫరు = 468,
	EVRInit_Error_VRInit_Error_Compositor_Create_Geom_Constant_బఫరు = 469,
	EVRInit_Error_VRInit_Error_Compositor_Create_Panel_ముసుగు_Constant_బఫరు = 470,
	EVRInitError_VRInitError_Compositor_CreatePixelSimUBO = 471,
	EVRInitError_VRInitError_Compositor_CreateMSAARenderTextures = 472,
	EVRInitError_VRInitError_Compositor_CreateResolveRenderTextures = 473,
	EVRInitError_VRInitError_Compositor_CreateComputeResolveRenderTextures = 474,
	EVRInit_Error_VRInit_Error_Compositor_Create_Driver_ప్రత్యక్ష_బహుళకం_Resolve_Textures = 475,
	EVRInit_Error_VRInit_Error_Compositor_Open_Driver_ప్రత్యక్ష_బహుళకం_Resolve_Textures = 476,
	EVRInitError_VRInitError_Compositor_CreateFallbackSyncTexture = 477,
	EVRInitError_VRInitError_Compositor_ShareFallbackSyncTexture = 478,
	EVRInit_Error_VRInit_Error_Compositor_Create_Overlay_సూచీ_బఫరు = 479,
	EVRInit_Error_VRInit_Error_Compositor_Create_Overlay_శీర్షం_బఫరు = 480,
	EVRInit_Error_VRInit_Error_Compositor_Create_పాఠ్యం_శీర్షం_బఫరు = 481,
	EVRInit_Error_VRInit_Error_Compositor_Create_పాఠ్యం_సూచీ_బఫరు = 482,
	EVRInitError_VRInitError_Compositor_CreateMirrorTextures = 483,
	EVRInit_Error_VRInit_Error_Compositor_Create_చివరి_చట్రం_Render_Texture = 484,
	EVRInitError_VRInitError_Compositor_CreateMirrorOverlay = 485,
	EVRInit_Error_VRInit_Error_Compositor_Failed_గమ్యం_Create_Virtual_Display_Backbuffer = 486,
	EVRInit_Error_VRInit_Error_Compositor_Display_బహుళకం_Not_Supported = 487,
	EVRInitError_VRInitError_Compositor_CreateOverlayInvalidCall = 488,
	EVRInitError_VRInitError_Compositor_CreateOverlayAlreadyInitialized = 489,
	EVRInit_Error_VRInit_Error_Compositor_Failed_గమ్యం_Create_Mailbox = 490,
	EVRInit_Error_VRInit_Error_Compositor_కిటికీ_Interface_Is_Null = 491,
	EVRInitError_VRInitError_Compositor_SystemLayerCreateInstance = 492,
	EVRInitError_VRInitError_Compositor_SystemLayerCreateSession = 493,
	EVRInitError_VRInitError_Compoistor_CreateInverseDistortUVs = 494,
	EVRInit_Error_VRInit_Error_Compoistor_Create_Backbuffer_లోతు = 495,
	EVRInit_Error_VRInit_Error_Vendor_Specific_Unable_గమ్యం_Connect_గమ్యం_Oculus_Runtime = 1000,
	EVRInit_Error_VRInit_Error_Vendor_Specific_Windows_Not_లోపల_Dev_బహుళకం = 1001,
	EVRInitError_VRInitError_VendorSpecific_OculusLinkNotEnabled = 1002,
	EVRInit_Error_VRInit_Error_Vendor_Specific_Hmd_దొరికింది_Cant_Open_Device = 1101,
	EVRInit_Error_VRInit_Error_Vendor_Specific_Hmd_దొరికింది_Unable_గమ్యం_Request_Config_ప్రారంభం = 1102,
	EVRInit_Error_VRInit_Error_Vendor_Specific_Hmd_దొరికింది_No_Stored_Config = 1103,
	EVRInit_Error_VRInit_Error_Vendor_Specific_Hmd_దొరికింది_Config_Too_Big = 1104,
	EVRInit_Error_VRInit_Error_Vendor_Specific_Hmd_దొరికింది_Config_Too_Small = 1105,
	EVRInit_Error_VRInit_Error_Vendor_Specific_Hmd_దొరికింది_Unable_గమ్యం_Init_ZLib = 1106,
	EVRInit_Error_VRInit_Error_Vendor_Specific_Hmd_దొరికింది_Cant_Read_Firmware_సంస్కరణ = 1107,
	EVRInit_Error_VRInit_Error_Vendor_Specific_Hmd_దొరికింది_Unable_గమ్యం_Send_User_దత్తాంశం_ప్రారంభం = 1108,
	EVRInit_Error_VRInit_Error_Vendor_Specific_Hmd_దొరికింది_Unable_గమ్యం_Get_User_దత్తాంశం_ప్రారంభం = 1109,
	EVRInit_Error_VRInit_Error_Vendor_Specific_Hmd_దొరికింది_Unable_గమ్యం_Get_User_దత్తాంశం_తదుపరి = 1110,
	EVRInit_Error_VRInit_Error_Vendor_Specific_Hmd_దొరికింది_User_దత్తాంశం_చిరునామా_Range = 1111,
	EVRInit_Error_VRInit_Error_Vendor_Specific_Hmd_దొరికింది_User_దత్తాంశం_Error = 1112,
	EVRInit_Error_VRInit_Error_Vendor_Specific_Hmd_దొరికింది_Config_Failed_Sanity_Check = 1113,
	EVRInitError_VRInitError_VendorSpecific_OculusRuntimeBadInstall = 1114,
	EVRInit_Error_VRInit_Error_Vendor_Specific_Hmd_దొరికింది_Unexpected_Configuration_1 = 1115,
	EVRInit_Error_VRInit_Error_Steam_Steam_Installation_Not_దొరికింది = 2000,
	EVRInit_Error_VRInit_Error_చివరి_Error = 2001,
} EVRInitError;

రకనిర్వచనం గణన EVRScreenshotType
{
	EVRScreenshotType_VRScreenshotType_None = 0,
	EVRScreenshotType_VRScreenshotType_Mono = 1,
	EVRScreenshotType_VRScreenshotType_Stereo = 2,
	EVRScreenshotType_VRScreenshotType_Cubemap = 3,
	EVRScreenshotType_VRScreenshotType_MonoPanorama = 4,
	EVRScreenshotType_VRScreenshotType_StereoPanorama = 5,
} EVRScreenshotType;

రకనిర్వచనం గణన EVRScreenshotPropertyFilenames
{
	EVRScreenshotPropertyFilenames_VRScreenshotPropertyFilenames_Preview = 0,
	EVRScreenshotPropertyFilenames_VRScreenshotPropertyFilenames_VR = 1,
} EVRScreenshotPropertyFilenames;

రకనిర్వచనం గణన EVRTrackedCameraError
{
	EVRTrackedCameraError_VRTrackedCameraError_None = 0,
	EVRTrackedCameraError_VRTrackedCameraError_OperationFailed = 100,
	EVRTrackedCameraError_VRTrackedCameraError_InvalidHandle = 101,
	EVRTracked_Camera_Error_VRTracked_Camera_Error_Invalid_చట్రం_శీర్షిక_సంస్కరణ = 102,
	EVRTracked_Camera_Error_VRTracked_Camera_Error_బహిర్గతం_యొక్క_Handles = 103,
	EVRTrackedCameraError_VRTrackedCameraError_IPCFailure = 104,
	EVRTrackedCameraError_VRTrackedCameraError_NotSupportedForThisDevice = 105,
	EVRTracked_Camera_Error_VRTracked_Camera_Error_Shared_జ్ఞాపకం_Failure = 106,
	EVRTracked_Camera_Error_VRTracked_Camera_Error_చట్రం_Buffering_Failure = 107,
	EVRTracked_Camera_Error_VRTracked_Camera_Error_ప్రవాహం_అమరిక_Failure = 108,
	EVRTrackedCameraError_VRTrackedCameraError_InvalidGLTextureId = 109,
	EVRTrackedCameraError_VRTrackedCameraError_InvalidSharedTextureHandle = 110,
	EVRTracked_Camera_Error_VRTracked_Camera_Error_Failed_గమ్యం_Get_GLTexture_Id = 111,
	EVRTrackedCameraError_VRTrackedCameraError_SharedTextureFailure = 112,
	EVRTracked_Camera_Error_VRTracked_Camera_Error_No_చట్రం_అందుబాటు = 113,
	EVRTracked_Camera_Error_VRTracked_Camera_Error_Invalid_వాదం = 114,
	EVRTracked_Camera_Error_VRTracked_Camera_Error_Invalid_చట్రం_బఫరు_కొలత = 115,
} EVRTrackedCameraError;

రకనిర్వచనం గణన EVRTracked_Camera_చట్రం_Layout
{
	EVRTracked_Camera_చట్రం_Layout_Mono = 1,
	EVRTracked_Camera_చట్రం_Layout_Stereo = 2,
	EVRTracked_Camera_చట్రం_Layout_Vertical_Layout = 16,
	EVRTracked_Camera_చట్రం_Layout_Horizontal_Layout = 32,
} EVRTracked_Camera_చట్రం_Layout;

రకనిర్వచనం గణన EVRTracked_Camera_చట్రం_Type
{
	EVRTracked_Camera_చట్రం_Type_VRTracked_Camera_చట్రం_Type_Distorted = 0,
	EVRTracked_Camera_చట్రం_Type_VRTracked_Camera_చట్రం_Type_Undistorted = 1,
	EVRTracked_Camera_చట్రం_Type_VRTracked_Camera_చట్రం_Type_గరిష్ఠ_Undistorted = 2,
	EVRTracked_Camera_చట్రం_Type_MAX_CAMERA_చట్రం_TYPES = 3,
} EVRTracked_Camera_చట్రం_Type;

రకనిర్వచనం గణన EVRDistortionFunctionType
{
	EVRDistortionFunctionType_VRDistortionFunctionType_None = 0,
	EVRDistortionFunctionType_VRDistortionFunctionType_FTheta = 1,
	EVRDistortionFunctionType_VRDistortionFunctionType_Extended_FTheta = 2,
	EVRDistortionFunctionType_MAX_DISTORTION_FUNCTION_TYPES = 3,
} EVRDistortionFunctionType;

రకనిర్వచనం గణన EVSync
{
	EVSync_VSync_None = 0,
	EVSync_VSync_WaitRender = 1,
	EVSync_VSync_NoWaitRender = 2,
} EVSync;

రకనిర్వచనం గణన EVRMura_Correction_బహుళకం
{
	EVRMura_Correction_బహుళకం_Default = 0,
	EVRMura_Correction_బహుళకం_No_Correction = 1,
} EVRMura_Correction_బహుళకం;

రకనిర్వచనం గణన Imu_OffScaleFlags
{
	Imu_OffScaleFlags_OffScale_AccelX = 1,
	Imu_OffScaleFlags_OffScale_AccelY = 2,
	Imu_OffScaleFlags_OffScale_AccelZ = 4,
	Imu_OffScaleFlags_OffScale_GyroX = 8,
	Imu_OffScaleFlags_OffScale_GyroY = 16,
	Imu_OffScaleFlags_OffScale_GyroZ = 32,
} Imu_OffScaleFlags;

రకనిర్వచనం గణన EVRApplicationError
{
	EVRApplicationError_VRApplicationError_None = 0,
	EVRApplication_Error_VRApplication_Error_App_కీలకం_Already_Exists = 100,
	EVRApplicationError_VRApplicationError_NoManifest = 101,
	EVRApplicationError_VRApplicationError_NoApplication = 102,
	EVRApplication_Error_VRApplication_Error_Invalid_సూచీ = 103,
	EVRApplicationError_VRApplicationError_UnknownApplication = 104,
	EVRApplicationError_VRApplicationError_IPCFailed = 105,
	EVRApplicationError_VRApplicationError_ApplicationAlreadyRunning = 106,
	EVRApplicationError_VRApplicationError_InvalidManifest = 107,
	EVRApplicationError_VRApplicationError_InvalidApplication = 108,
	EVRApplicationError_VRApplicationError_LaunchFailed = 109,
	EVRApplicationError_VRApplicationError_ApplicationAlreadyStarting = 110,
	EVRApplication_Error_VRApplication_Error_Launch_లోపల_పురోగతి = 111,
	EVRApplicationError_VRApplicationError_OldApplicationQuitting = 112,
	EVRApplicationError_VRApplicationError_TransitionAborted = 113,
	EVRApplicationError_VRApplicationError_IsTemplate = 114,
	EVRApplicationError_VRApplicationError_SteamVRIsExiting = 115,
	EVRApplication_Error_VRApplication_Error_బఫరు_Too_Small = 200,
	EVRApplication_Error_VRApplication_Error_Property_Not_సమితి = 201,
	EVRApplicationError_VRApplicationError_UnknownProperty = 202,
	EVRApplicationError_VRApplicationError_InvalidParameter = 203,
	EVRApplicationError_VRApplicationError_NotImplemented = 300,
} EVRApplicationError;

రకనిర్వచనం గణన EVRApplicationProperty
{
	EVRApplicationProperty_VRApplicationProperty_Name_String = 0,
	EVRApplicationProperty_VRApplicationProperty_LaunchType_String = 11,
	EVRApplicationProperty_VRApplicationProperty_WorkingDirectory_String = 12,
	EVRApplication_Property_VRApplication_Property_ద్విమాన_మార్గం_String = 13,
	EVRApplicationProperty_VRApplicationProperty_Arguments_String = 14,
	EVRApplicationProperty_VRApplicationProperty_URL_String = 15,
	EVRApplicationProperty_VRApplicationProperty_Description_String = 50,
	EVRApplicationProperty_VRApplicationProperty_NewsURL_String = 51,
	EVRApplication_Property_VRApplication_Property_Image_మార్గం_String = 52,
	EVRApplication_Property_VRApplication_Property_ఆధారం_String = 53,
	EVRApplicationProperty_VRApplicationProperty_ActionManifestURL_String = 54,
	EVRApplicationProperty_VRApplicationProperty_IsDashboardOverlay_Bool = 60,
	EVRApplicationProperty_VRApplicationProperty_IsTemplate_Bool = 61,
	EVRApplicationProperty_VRApplicationProperty_IsInstanced_Bool = 62,
	EVRApplication_Property_VRApplication_Property_Is_అంతర్గత_Bool = 63,
	EVRApplication_Property_VRApplication_Property_కోరుతుంది_Compositor_Pause_లోపల_Standby_Bool = 64,
	EVRApplicationProperty_VRApplicationProperty_IsHidden_Bool = 65,
	EVRApplication_Property_VRApplication_Property_చివరి_Launch_సమయం_Uint64 = 70,
} EVRApplicationProperty;

రకనిర్వచనం గణన EVRSceneApplicationState
{
	EVRSceneApplicationState_None = 0,
	EVRSceneApplicationState_Starting = 1,
	EVRSceneApplicationState_Quitting = 2,
	EVRSceneApplicationState_Running = 3,
	EVRScene_Application_State_నిరీక్షణ = 4,
} EVRSceneApplicationState;

రకనిర్వచనం గణన ChaperoneCalibrationState
{
	ChaperoneCalibrationState_OK = 1,
	ChaperoneCalibrationState_Warning = 100,
	Chaperone_Calibration_State_Warning_పునాది_Station_May_Have_Moved = 101,
	Chaperone_Calibration_State_Warning_పునాది_Station_Removed = 102,
	ChaperoneCalibrationState_Warning_SeatedBoundsInvalid = 103,
	ChaperoneCalibrationState_Error = 200,
	Chaperone_Calibration_State_Error_పునాది_Station_Uninitialized = 201,
	Chaperone_Calibration_State_Error_పునాది_Station_Conflict = 202,
	ChaperoneCalibrationState_Error_PlayAreaInvalid = 203,
	ChaperoneCalibrationState_Error_CollisionBoundsInvalid = 204,
} ChaperoneCalibrationState;

రకనిర్వచనం గణన EChaperoneConfigFile
{
	EChaperone_Config_File_సజీవ = 1,
	EChaperone_Config_File_తాత్కాలిక = 2,
} EChaperoneConfigFile;

రకనిర్వచనం గణన EChaperoneImportFlags
{
	EChaperoneImportFlags_EChaperoneImport_BoundsOnly = 1,
} EChaperoneImportFlags;

రకనిర్వచనం గణన EVRCompositorError
{
	EVRCompositorError_VRCompositorError_None = 0,
	EVRCompositorError_VRCompositorError_RequestFailed = 1,
	EVRCompositor_Error_VRCompositor_Error_Incompatible_సంస్కరణ = 100,
	EVRCompositorError_VRCompositorError_DoNotHaveFocus = 101,
	EVRCompositorError_VRCompositorError_InvalidTexture = 102,
	EVRCompositorError_VRCompositorError_IsNotSceneApplication = 103,
	EVRCompositorError_VRCompositorError_TextureIsOnWrongDevice = 104,
	EVRCompositor_Error_VRCompositor_Error_Texture_ఉపయోగిస్తుంది_Unsupported_Format = 105,
	EVRCompositorError_VRCompositorError_SharedTexturesNotSupported = 106,
	EVRCompositor_Error_VRCompositor_Error_సూచీ_బహిర్గతం_యొక్క_Range = 107,
	EVRCompositorError_VRCompositorError_AlreadySubmitted = 108,
	EVRCompositorError_VRCompositorError_InvalidBounds = 109,
	EVRCompositor_Error_VRCompositor_Error_Already_సమితి = 110,
} EVRCompositorError;

రకనిర్వచనం గణన EVRCompositor_Timing_బహుళకం
{
	EVRCompositor_Timing_బహుళకం_VRCompositor_Timing_బహుళకం_Implicit = 0,
	EVRCompositor_Timing_బహుళకం_VRCompositor_Timing_బహుళకం_Explicit_Runtime_Performs_Post_Present_Handoff = 1,
	EVRCompositor_Timing_బహుళకం_VRCompositor_Timing_బహుళకం_Explicit_Application_Performs_Post_Present_Handoff = 2,
} EVRCompositor_Timing_బహుళకం;

రకనిర్వచనం గణన VROverlay_ఆదానం_పద్ధతి
{
	VROverlay_ఆదానం_పద్ధతి_None = 0,
	VROverlay_ఆదానం_పద్ధతి_Mouse = 1,
} VROverlay_ఆదానం_పద్ధతి;

రకనిర్వచనం గణన VROverlayTransformType
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

రకనిర్వచనం గణన VROverlayFlags
{
	VROverlayFlags_NoDashboardTab = 8,
	VROverlayFlags_SendVRDiscreteScrollEvents = 64,
	VROverlayFlags_SendVRTouchpadEvents = 128,
	VROverlayFlags_ShowTouchPadScrollWheel = 256,
	VROverlay_Flags_Transfer_Ownership_గమ్యం_అంతర్గత_Process = 512,
	VROverlayFlags_SideBySide_Parallel = 1024,
	VROverlayFlags_SideBySide_Crossed = 2048,
	VROverlayFlags_Panorama = 4096,
	VROverlayFlags_StereoPanorama = 8192,
	VROverlay_Flags_క్రమీకరించు_With_Non_Scene_Overlays = 16384,
	VROverlay_Flags_Visible_లోపల_Dashboard = 32768,
	VROverlayFlags_MakeOverlaysInteractiveIfVisible = 65536,
	VROverlayFlags_SendVRSmoothScrollEvents = 131072,
	VROverlayFlags_ProtectedContent = 262144,
	VROverlayFlags_HideLaserIntersection = 524288,
	VROverlay_Flags_కోరుతుంది_Modal_Behavior = 1048576,
	VROverlayFlags_IsPremultiplied = 2097152,
	VROverlayFlags_IgnoreTextureAlpha = 4194304,
	VROverlayFlags_EnableControlBar = 8388608,
	VROverlayFlags_EnableControlBarKeyboard = 16777216,
	VROverlayFlags_EnableControlBarClose = 33554432,
} VROverlayFlags;

రకనిర్వచనం గణన VRMessageOverlayResponse
{
	VRMessageOverlayResponse_ButtonPress_0 = 0,
	VRMessageOverlayResponse_ButtonPress_1 = 1,
	VRMessageOverlayResponse_ButtonPress_2 = 2,
	VRMessageOverlayResponse_ButtonPress_3 = 3,
	VRMessage_Overlay_Response_Couldnt_కనుగొను_System_Overlay = 4,
	VRMessage_Overlay_Response_Couldnt_కనుగొను_Or_Create_Client_Overlay = 5,
	VRMessageOverlayResponse_ApplicationQuit = 6,
} VRMessageOverlayResponse;

రకనిర్వచనం గణన EGamepad_పాఠ్యం_ఆదానం_బహుళకం
{
	EGamepad_పాఠ్యం_ఆదానం_బహుళకం_k_EGamepad_పాఠ్యం_ఆదానం_బహుళకం_సాధారణ = 0,
	EGamepad_పాఠ్యం_ఆదానం_బహుళకం_k_EGamepad_పాఠ్యం_ఆదానం_బహుళకం_Password = 1,
	EGamepad_పాఠ్యం_ఆదానం_బహుళకం_k_EGamepad_పాఠ్యం_ఆదానం_బహుళకం_Submit = 2,
} EGamepad_పాఠ్యం_ఆదానం_బహుళకం;

రకనిర్వచనం గణన EGamepad_పాఠ్యం_ఆదానం_పంక్తి_బహుళకం
{
	EGamepad_పాఠ్యం_ఆదానం_పంక్తి_బహుళకం_k_EGamepad_పాఠ్యం_ఆదానం_పంక్తి_బహుళకం_Single_పంక్తి = 0,
	EGamepad_పాఠ్యం_ఆదానం_పంక్తి_బహుళకం_k_EGamepad_పాఠ్యం_ఆదానం_పంక్తి_బహుళకం_గుణిజం_పంక్తులు = 1,
} EGamepad_పాఠ్యం_ఆదానం_పంక్తి_బహుళకం;

రకనిర్వచనం గణన EVROverlay_Intersection_ముసుగు_Primitive_Type
{
	EVROverlay_Intersection_ముసుగు_Primitive_Type_Overlay_Intersection_Primitive_Type_Rectangle = 0,
	EVROverlay_Intersection_ముసుగు_Primitive_Type_Overlay_Intersection_Primitive_Type_Circle = 1,
} EVROverlay_Intersection_ముసుగు_Primitive_Type;

రకనిర్వచనం గణన EKeyboardFlags
{
	EKeyboard_Flags_Keyboard_Flag_కనీస = 1,
	EKeyboardFlags_KeyboardFlag_Modal = 2,
} EKeyboardFlags;

రకనిర్వచనం గణన EDeviceType
{
	EDeviceType_DeviceType_Invalid = -1,
	EDevice_Type_Device_Type_ప్రత్యక్ష_X11 = 0,
	EDeviceType_DeviceType_Vulkan = 1,
} EDeviceType;

రకనిర్వచనం గణన Headset_View_బహుళకం_t
{
	Headset_View_బహుళకం_t_Headset_View_బహుళకం_ఎడమ = 0,
	Headset_View_బహుళకం_t_Headset_View_బహుళకం_కుడి = 1,
	Headset_View_బహుళకం_t_Headset_View_బహుళకం_Both = 2,
} Headset_View_బహుళకం_t;

రకనిర్వచనం గణన EVRRenderModelError
{
	EVRRenderModelError_VRRenderModelError_None = 0,
	EVRRenderModelError_VRRenderModelError_Loading = 100,
	EVRRenderModelError_VRRenderModelError_NotSupported = 200,
	EVRRenderModelError_VRRenderModelError_InvalidArg = 300,
	EVRRenderModelError_VRRenderModelError_InvalidModel = 301,
	EVRRenderModelError_VRRenderModelError_NoShapes = 302,
	EVRRender_Model_Error_VRRender_Model_Error_గుణిజం_Shapes = 303,
	EVRRenderModelError_VRRenderModelError_TooManyVertices = 304,
	EVRRender_Model_Error_VRRender_Model_Error_గుణిజం_Textures = 305,
	EVRRender_Model_Error_VRRender_Model_Error_బఫరు_Too_Small = 306,
	EVRRenderModelError_VRRenderModelError_NotEnoughNormals = 307,
	EVRRenderModelError_VRRenderModelError_NotEnoughTexCoords = 308,
	EVRRenderModelError_VRRenderModelError_InvalidTexture = 400,
} EVRRenderModelError;

రకనిర్వచనం గణన EVRRenderModelTextureFormat
{
	EVRRenderModelTextureFormat_VRRenderModelTextureFormat_RGBA8_SRGB = 0,
	EVRRenderModelTextureFormat_VRRenderModelTextureFormat_BC2 = 1,
	EVRRenderModelTextureFormat_VRRenderModelTextureFormat_BC4 = 2,
	EVRRenderModelTextureFormat_VRRenderModelTextureFormat_BC7 = 3,
	EVRRenderModelTextureFormat_VRRenderModelTextureFormat_BC7_SRGB = 4,
	EVRRenderModelTextureFormat_VRRenderModelTextureFormat_RGBA16_FLOAT = 5,
} EVRRenderModelTextureFormat;

రకనిర్వచనం గణన EVRNotificationType
{
	EVRNotificationType_Transient = 0,
	EVRNotificationType_Persistent = 1,
	EVRNotification_Type_Transient_System_With_User_విలువ = 2,
} EVRNotificationType;

రకనిర్వచనం గణన EVRNotificationStyle
{
	EVRNotificationStyle_None = 0,
	EVRNotificationStyle_Application = 100,
	EVRNotificationStyle_Contact_Disabled = 200,
	EVRNotificationStyle_Contact_Enabled = 201,
	EVRNotification_Style_Contact_చురుకైన = 202,
} EVRNotificationStyle;

రకనిర్వచనం గణన EVRSettingsError
{
	EVRSettingsError_VRSettingsError_None = 0,
	EVRSettingsError_VRSettingsError_IPCFailed = 1,
	EVRSettingsError_VRSettingsError_WriteFailed = 2,
	EVRSettingsError_VRSettingsError_ReadFailed = 3,
	EVRSettingsError_VRSettingsError_JsonParseFailed = 4,
	EVRSettingsError_VRSettingsError_UnsetSettingHasNoDefault = 5,
} EVRSettingsError;

రకనిర్వచనం గణన EVRScreenshotError
{
	EVRScreenshotError_VRScreenshotError_None = 0,
	EVRScreenshotError_VRScreenshotError_RequestFailed = 1,
	EVRScreenshot_Error_VRScreenshot_Error_Incompatible_సంస్కరణ = 100,
	EVRScreenshot_Error_VRScreenshot_Error_Not_దొరికింది = 101,
	EVRScreenshot_Error_VRScreenshot_Error_బఫరు_Too_Small = 102,
	EVRScreenshot_Error_VRScreenshot_Error_Screenshot_Already_లోపల_పురోగతి = 108,
} EVRScreenshotError;

రకనిర్వచనం గణన EVRSkeletalTransformSpace
{
	EVRSkeletalTransformSpace_VRSkeletalTransformSpace_Model = 0,
	EVRSkeletal_Transform_Space_VRSkeletal_Transform_Space_మాతృ = 1,
} EVRSkeletalTransformSpace;

రకనిర్వచనం గణన EVRSkeletalReferencePose
{
	EVRSkeletalReferencePose_VRSkeletalReferencePose_BindPose = 0,
	EVRSkeletalReferencePose_VRSkeletalReferencePose_OpenHand = 1,
	EVRSkeletalReferencePose_VRSkeletalReferencePose_Fist = 2,
	EVRSkeletal_Reference_Pose_VRSkeletal_Reference_Pose_Grip_హద్దు = 3,
} EVRSkeletalReferencePose;

రకనిర్వచనం గణన EVRFinger
{
	EVRFinger_VRFinger_Thumb = 0,
	EVRFinger_VRFinger_సూచీ = 1,
	EVRFinger_VRFinger_మధ్య = 2,
	EVRFinger_VRFinger_Ring = 3,
	EVRFinger_VRFinger_Pinky = 4,
	EVRFinger_VRFinger_లెక్క = 5,
} EVRFinger;

రకనిర్వచనం గణన EVRFingerSplay
{
	EVRFinger_Splay_VRFinger_Splay_Thumb_సూచీ = 0,
	EVRFinger_Splay_VRFinger_Splay_సూచీ_మధ్య = 1,
	EVRFinger_Splay_VRFinger_Splay_మధ్య_Ring = 2,
	EVRFingerSplay_VRFingerSplay_Ring_Pinky = 3,
	EVRFinger_Splay_VRFinger_Splay_లెక్క = 4,
} EVRFingerSplay;

రకనిర్వచనం గణన EVRSummaryType
{
	EVRSummaryType_VRSummaryType_FromAnimation = 0,
	EVRSummaryType_VRSummaryType_FromDevice = 1,
} EVRSummaryType;

రకనిర్వచనం గణన EVRInputFilterCancelType
{
	EVRInputFilterCancelType_VRInputFilterCancel_Timers = 0,
	EVRInputFilterCancelType_VRInputFilterCancel_Momentum = 1,
} EVRInputFilterCancelType;

రకనిర్వచనం గణన EVRInput_String_బిట్లు
{
	EVRInput_String_బిట్లు_VRInput_String_Hand = 1,
	EVRInput_String_బిట్లు_VRInput_String_Controller_Type = 2,
	EVRInput_String_బిట్లు_VRInput_String_ఆదానం_ఆధారం = 4,
	EVRInput_String_బిట్లు_VRInput_String_All = -1,
} EVRInput_String_బిట్లు;

రకనిర్వచనం గణన EIOBufferError
{
	EIOBufferError_IOBuffer_Success = 0,
	EIOBufferError_IOBuffer_OperationFailed = 100,
	EIOBufferError_IOBuffer_InvalidHandle = 101,
	EIOBuffer_Error_IOBuffer_Invalid_వాదం = 102,
	EIOBuffer_Error_IOBuffer_మార్గం_Exists = 103,
	EIOBuffer_Error_IOBuffer_మార్గం_Does_Not_Exist = 104,
	EIOBufferError_IOBuffer_Permission = 105,
} EIOBufferError;

రకనిర్వచనం గణన EIOBuffer_బహుళకం
{
	EIOBuffer_బహుళకం_IOBuffer_బహుళకం_Read = 1,
	EIOBuffer_బహుళకం_IOBuffer_బహుళకం_Write = 2,
	EIOBuffer_బహుళకం_IOBuffer_బహుళకం_Create = 512,
} EIOBuffer_బహుళకం;

రకనిర్వచనం గణన EVRDebugError
{
	EVRDebugError_VRDebugError_Success = 0,
	EVRDebugError_VRDebugError_BadParameter = 1,
} EVRDebugError;

రకనిర్వచనం గణన EPropertyWriteType
{
	EProperty_Write_Type_Property_Write_సమితి = 0,
	EPropertyWriteType_PropertyWrite_Erase = 1,
	EProperty_Write_Type_Property_Write_సమితి_Error = 2,
} EPropertyWriteType;

రకనిర్వచనం గణన EBlock_వరుస_Error
{
	EBlock_వరుస_Error_ఖండం_వరుస_Error_None = 0,
	EBlock_వరుస_Error_ఖండం_వరుస_Error_వరుస_Already_Exists = 1,
	EBlock_వరుస_Error_ఖండం_వరుస_Error_వరుస_Not_దొరికింది = 2,
	EBlock_వరుస_Error_ఖండం_వరుస_Error_ఖండం_Not_అందుబాటు = 3,
	EBlock_వరుస_Error_ఖండం_వరుస_Error_Invalid_Handle = 4,
	EBlock_వరుస_Error_ఖండం_వరుస_Error_Invalid_Param = 5,
	EBlock_వరుస_Error_ఖండం_వరుస_Error_Param_Mismatch = 6,
	EBlock_వరుస_Error_ఖండం_వరుస_Error_అంతర్గత_Error = 7,
	EBlock_వరుస_Error_ఖండం_వరుస_Error_Already_Initialized = 8,
	EBlock_వరుస_Error_ఖండం_వరుస_Error_Operation_Is_Server_Only = 9,
	EBlock_వరుస_Error_ఖండం_వరుస_Error_Too_Many_Connections = 10,
} EBlock_వరుస_Error;

రకనిర్వచనం గణన EBlock_వరుస_Read_Type
{
	EBlock_వరుస_Read_Type_ఖండం_వరుస_Read_Latest = 0,
	EBlock_వరుస_Read_Type_ఖండం_వరుస_Read_New = 1,
	EBlock_వరుస_Read_Type_ఖండం_వరుస_Read_తదుపరి = 2,
} EBlock_వరుస_Read_Type;

రకనిర్వచనం గణన EBlock_వరుస_Creation_Flag
{
	EBlock_వరుస_Creation_Flag_ఖండం_వరుస_Flag_Owner_Is_Reader = 1,
} EBlock_వరుస_Creation_Flag;


// OpenVR typedefs

రకనిర్వచనం uint32_t Property_Type_ట్యాగ్_t;
రకనిర్వచనం uint32_t SpatialAnchorHandle_t;
రకనిర్వచనం శూన్య * glSharedTextureHandle_t;
రకనిర్వచనం int32_t glInt_t;
రకనిర్వచనం uint32_t glUInt_t;
రకనిర్వచనం uint64_t SharedTextureHandle_t;
రకనిర్వచనం uint32_t DriverId_t;
రకనిర్వచనం uint32_t Tracked_Device_సూచీ_t;
రకనిర్వచనం uint64_t WebConsoleHandle_t;
రకనిర్వచనం uint64_t PropertyContainerHandle_t;
రకనిర్వచనం PropertyContainerHandle_t DriverHandle_t;
రకనిర్వచనం uint64_t VRActionHandle_t;
రకనిర్వచనం uint64_t VRAction_సమితి_Handle_t;
రకనిర్వచనం uint64_t VRInput_విలువ_Handle_t;
రకనిర్వచనం uint32_t VRComponentProperties;
రకనిర్వచనం uint64_t VROverlayHandle_t;
రకనిర్వచనం int32_t Bone_సూచీ_t;
రకనిర్వచనం uint64_t TrackedCameraHandle_t;
రకనిర్వచనం uint32_t ScreenshotHandle_t;
రకనిర్వచనం int32_t TextureID_t;
రకనిర్వచనం uint32_t VRNotificationId;
రకనిర్వచనం uint64_t IOBufferHandle_t;
రకనిర్వచనం uint64_t VrProfilerEventHandle_t;
రకనిర్వచనం EVRInitError HmdError;
రకనిర్వచనం EVREye Hmd_Eye;
రకనిర్వచనం EColorSpace ColorSpace;
రకనిర్వచనం ETracking_ఫలితం Hmd_Tracking_ఫలితం;
రకనిర్వచనం ETrackedDeviceClass TrackedDeviceClass;
రకనిర్వచనం ETrackingUniverseOrigin TrackingUniverseOrigin;
రకనిర్వచనం ETrackedDeviceProperty TrackedDeviceProperty;
రకనిర్వచనం ETrackedPropertyError TrackedPropertyError;
రకనిర్వచనం EVRSubmitFlags VRSubmitFlags_t;
రకనిర్వచనం EVRState VRState_t;
రకనిర్వచనం ECollisionBoundsStyle CollisionBoundsStyle_t;
రకనిర్వచనం EVROverlayError VROverlayError;
రకనిర్వచనం EVRFirmwareError VRFirmwareError;
రకనిర్వచనం EVRCompositorError VRCompositorError;
రకనిర్వచనం EVRScreenshotError VRScreenshotsError;
రకనిర్వచనం uint64_t మార్గం_Handle_t;

// OpenVR Structs

రకనిర్వచనం నిర్మాణం HmdMatrix34_t
{
	దశాంశం m[3][4]; //float[3][4]
} HmdMatrix34_t;

రకనిర్వచనం నిర్మాణం HmdMatrix33_t
{
	దశాంశం m[3][3]; //float[3][3]
} HmdMatrix33_t;

రకనిర్వచనం నిర్మాణం HmdMatrix44_t
{
	దశాంశం m[4][4]; //float[4][4]
} HmdMatrix44_t;

రకనిర్వచనం నిర్మాణం HmdVector3_t
{
	దశాంశం v[3]; //float[3]
} HmdVector3_t;

రకనిర్వచనం నిర్మాణం HmdVector4_t
{
	దశాంశం v[4]; //float[4]
} HmdVector4_t;

రకనిర్వచనం నిర్మాణం HmdVector3d_t
{
	ద్విగుణ v[3]; //double[3]
} HmdVector3d_t;

రకనిర్వచనం నిర్మాణం HmdVector2_t
{
	దశాంశం v[2]; //float[2]
} HmdVector2_t;

రకనిర్వచనం నిర్మాణం HmdQuaternion_t
{
	ద్విగుణ w;
	ద్విగుణ x;
	ద్విగుణ y;
	ద్విగుణ z;
} HmdQuaternion_t;

రకనిర్వచనం నిర్మాణం HmdQuaternionf_t
{
	దశాంశం w;
	దశాంశం x;
	దశాంశం y;
	దశాంశం z;
} HmdQuaternionf_t;

రకనిర్వచనం నిర్మాణం HmdColor_t
{
	దశాంశం r;
	దశాంశం g;
	దశాంశం b;
	దశాంశం a;
} HmdColor_t;

రకనిర్వచనం నిర్మాణం HmdQuad_t
{
	నిర్మాణం HmdVector3_t vCorners[4]; //struct vr::HmdVector3_t[4]
} HmdQuad_t;

రకనిర్వచనం నిర్మాణం HmdRect2_t
{
	నిర్మాణం HmdVector2_t v_శిఖరం_ఎడమ;
	నిర్మాణం HmdVector2_t v_Bottom_కుడి;
} HmdRect2_t;

రకనిర్వచనం నిర్మాణం VRBoneTransform_t
{
	నిర్మాణం HmdVector4_t position;
	నిర్మాణం HmdQuaternionf_t orientation;
} VRBoneTransform_t;

రకనిర్వచనం నిర్మాణం DistortionCoordinates_t
{
	దశాంశం rfRed[2]; //float[2]
	దశాంశం rfGreen[2]; //float[2]
	దశాంశం rfBlue[2]; //float[2]
} DistortionCoordinates_t;

రకనిర్వచనం నిర్మాణం Texture_t
{
	శూన్య * handle; // void *
	గణన ETextureType eType;
	గణన EColorSpace eColorSpace;
} Texture_t;

రకనిర్వచనం నిర్మాణం TrackedDevicePose_t
{
	నిర్మాణం HmdMatrix34_t m_Device_గమ్యం_Absolute_Tracking;
	నిర్మాణం HmdVector3_t vVelocity;
	నిర్మాణం HmdVector3_t vAngularVelocity;
	గణన ETracking_ఫలితం e_Tracking_ఫలితం;
	bool bPoseIsValid;
	bool bDeviceIsConnected;
} TrackedDevicePose_t;

రకనిర్వచనం నిర్మాణం VRTextureBounds_t
{
	దశాంశం uMin;
	దశాంశం vMin;
	దశాంశం uMax;
	దశాంశం vMax;
} VRTextureBounds_t;

రకనిర్వచనం నిర్మాణం VRTextureWithPose_t
{
	శూన్య * handle; // void *
	గణన ETextureType eType;
	గణన EColorSpace eColorSpace;
	నిర్మాణం HmdMatrix34_t m_Device_గమ్యం_Absolute_Tracking;
} VRTextureWithPose_t;

రకనిర్వచనం నిర్మాణం VRTexture_లోతు_Info_t
{
	శూన్య * handle; // void *
	నిర్మాణం HmdMatrix44_t mProjection;
	నిర్మాణం HmdVector2_t vRange;
} VRTexture_లోతు_Info_t;

రకనిర్వచనం నిర్మాణం VRTexture_With_లోతు_t
{
	శూన్య * handle; // void *
	గణన ETextureType eType;
	గణన EColorSpace eColorSpace;
	నిర్మాణం VRTexture_లోతు_Info_t లోతు_2;
} VRTexture_With_లోతు_t;

రకనిర్వచనం నిర్మాణం VRTexture_With_Pose_And_లోతు_t
{
	శూన్య * handle; // void *
	గణన ETextureType eType;
	గణన EColorSpace eColorSpace;
	నిర్మాణం HmdMatrix34_t m_Device_గమ్యం_Absolute_Tracking;
	నిర్మాణం VRTexture_లోతు_Info_t లోతు_2;
} VRTexture_With_Pose_And_లోతు_t;

రకనిర్వచనం నిర్మాణం VRVulkan_Texture_దత్తాంశం_t
{
	uint64_t m_nImage;
	నిర్మాణం VkDevice_T * m_pDevice; // struct VkDevice_T *
	నిర్మాణం VkPhysicalDevice_T * m_pPhysicalDevice; // struct VkPhysicalDevice_T *
	నిర్మాణం VkInstance_T * m_pInstance; // struct VkInstance_T *
	నిర్మాణం Vk_వరుస_T * m_p_వరుస; // struct VkQueue_T *
	uint32_t m_n_వరుస_Family_సూచీ;
	uint32_t m_n_వెడల్పు;
	uint32_t m_n_ఎత్తు;
	uint32_t m_nFormat;
	uint32_t m_n_Sample_లెక్క;
} VRVulkan_Texture_దత్తాంశం_t;

రకనిర్వచనం నిర్మాణం VRVulkan_Texture_Array_దత్తాంశం_t
{
	uint32_t m_un_Array_సూచీ;
	uint32_t m_un_Array_కొలత;
} VRVulkan_Texture_Array_దత్తాంశం_t;

రకనిర్వచనం నిర్మాణం D3_D12_Texture_దత్తాంశం_t
{
	నిర్మాణం ID3D12Resource * m_pResource; // struct ID3D12Resource *
	నిర్మాణం ID3_D12_Command_వరుస * m_p_Command_వరుస; // struct ID3D12CommandQueue *
	uint32_t m_n_కణుపు_ముసుగు;
} D3_D12_Texture_దత్తాంశం_t;

రకనిర్వచనం నిర్మాణం VREvent_Controller_t
{
	uint32_t button;
} VREvent_Controller_t;

రకనిర్వచనం నిర్మాణం VREvent_Mouse_t
{
	దశాంశం x;
	దశాంశం y;
	uint32_t button;
} VREvent_Mouse_t;

రకనిర్వచనం నిర్మాణం VREvent_Scroll_t
{
	దశాంశం xdelta;
	దశాంశం ydelta;
	uint32_t వాడని;
	దశాంశం viewportscale;
} VREvent_Scroll_t;

రకనిర్వచనం నిర్మాణం VREvent_TouchPadMove_t
{
	bool b_Finger_కిందికి;
	దశాంశం fl_Seconds_Finger_కిందికి;
	దశాంశం f_విలువ_XFirst;
	దశాంశం f_విలువ_YFirst;
	దశాంశం f_విలువ_XRaw;
	దశాంశం f_విలువ_YRaw;
} VREvent_TouchPadMove_t;

రకనిర్వచనం నిర్మాణం VREvent_Notification_t
{
	uint64_t ul_User_విలువ;
	uint32_t notificationId;
} VREvent_Notification_t;

రకనిర్వచనం నిర్మాణం VREvent_Process_t
{
	uint32_t pid;
	uint32_t oldPid;
	bool bForced;
	bool b_Connection_కోల్పోయిన;
} VREvent_Process_t;

రకనిర్వచనం నిర్మాణం VREvent_Overlay_t
{
	uint64_t overlayHandle;
	uint64_t device_మార్గం;
	uint64_t జ్ఞాపకం_ఖండం_Id;
} VREvent_Overlay_t;

రకనిర్వచనం నిర్మాణం VREvent_స్థితి_t
{
	uint32_t స్థితి_State;
} VREvent_స్థితి_t;

రకనిర్వచనం నిర్మాణం VREvent_Keyboard_t
{
	అక్షరం c_New_ఆదానం[8]; //char[8]
	uint64_t u_User_విలువ;
} VREvent_Keyboard_t;

రకనిర్వచనం నిర్మాణం VREvent_Ipd_t
{
	దశాంశం ipdMeters;
} VREvent_Ipd_t;

రకనిర్వచనం నిర్మాణం VREvent_Chaperone_t
{
	uint64_t m_n_మునుపటి_Universe;
	uint64_t m_nCurrentUniverse;
} VREvent_Chaperone_t;

రకనిర్వచనం నిర్మాణం VREvent_Reserved_t
{
	uint64_t reserved0;
	uint64_t reserved1;
	uint64_t reserved2;
	uint64_t reserved3;
	uint64_t reserved4;
	uint64_t reserved5;
} VREvent_Reserved_t;

రకనిర్వచనం నిర్మాణం VREvent_PerformanceTest_t
{
	uint32_t m_nFidelityLevel;
} VREvent_PerformanceTest_t;

రకనిర్వచనం నిర్మాణం VREvent_SeatedZeroPoseReset_t
{
	bool bResetBySystemMenu;
} VREvent_SeatedZeroPoseReset_t;

రకనిర్వచనం నిర్మాణం VREvent_Screenshot_t
{
	uint32_t handle;
	uint32_t type;
} VREvent_Screenshot_t;

రకనిర్వచనం నిర్మాణం VREvent_Screenshot_పురోగతి_t
{
	దశాంశం పురోగతి_2;
} VREvent_Screenshot_పురోగతి_t;

రకనిర్వచనం నిర్మాణం VREvent_ApplicationLaunch_t
{
	uint32_t pid;
	uint32_t un_వాదనలు_Handle;
} VREvent_ApplicationLaunch_t;

రకనిర్వచనం నిర్మాణం VREvent_EditingCameraSurface_t
{
	uint64_t overlayHandle;
	uint32_t n_Visual_బహుళకం;
} VREvent_EditingCameraSurface_t;

రకనిర్వచనం నిర్మాణం VREvent_సందేశం_Overlay_t
{
	uint32_t unVRMessageOverlayResponse;
} VREvent_సందేశం_Overlay_t;

రకనిర్వచనం నిర్మాణం VREvent_Property_t
{
	PropertyContainerHandle_t container;
	గణన ETrackedDeviceProperty prop;
} VREvent_Property_t;

రకనిర్వచనం నిర్మాణం VREvent_HapticVibration_t
{
	uint64_t containerHandle;
	uint64_t componentHandle;
	దశాంశం fDurationSeconds;
	దశాంశం fFrequency;
	దశాంశం fAmplitude;
} VREvent_HapticVibration_t;

రకనిర్వచనం నిర్మాణం VREvent_WebConsole_t
{
	WebConsoleHandle_t webConsoleHandle;
} VREvent_WebConsole_t;

రకనిర్వచనం నిర్మాణం VREvent_ఆదానం_Binding_ఎక్కించు_t
{
	PropertyContainerHandle_t ulAppContainer;
	uint64_t మార్గం_సందేశం;
	uint64_t మార్గం_Url;
	uint64_t మార్గం_Controller_Type;
} VREvent_ఆదానం_Binding_ఎక్కించు_t;

రకనిర్వచనం నిర్మాణం VREvent_ఆదానం_Action_Manifest_ఎక్కించు_t
{
	uint64_t మార్గం_App_కీలకం;
	uint64_t మార్గం_సందేశం;
	uint64_t మార్గం_సందేశం_Param;
	uint64_t మార్గం_Manifest_మార్గం;
} VREvent_ఆదానం_Action_Manifest_ఎక్కించు_t;

రకనిర్వచనం నిర్మాణం VREvent_SpatialAnchor_t
{
	SpatialAnchorHandle_t unHandle;
} VREvent_SpatialAnchor_t;

రకనిర్వచనం నిర్మాణం VREvent_పురోగతి_Update_t
{
	uint64_t ulApplicationPropertyContainer;
	uint64_t మార్గం_Device;
	uint64_t మార్గం_ఆదానం_ఆధారం;
	uint64_t మార్గం_పురోగతి_Action;
	uint64_t మార్గం_Icon;
	దశాంశం f_పురోగతి;
} VREvent_పురోగతి_Update_t;

రకనిర్వచనం నిర్మాణం VREvent_ShowUI_t
{
	గణన EShowUIType eType;
} VREvent_ShowUI_t;

రకనిర్వచనం నిర్మాణం VREvent_ShowDevTools_t
{
	int32_t nBrowserIdentifier;
} VREvent_ShowDevTools_t;

రకనిర్వచనం నిర్మాణం VREvent_HDCPError_t
{
	గణన EHDCPError e_సంకేతం;
} VREvent_HDCPError_t;

రకనిర్వచనం నిర్మాణం RenderModel_ComponentState_t
{
	నిర్మాణం HmdMatrix34_t m_Tracking_గమ్యం_Component_Render_Model;
	నిర్మాణం HmdMatrix34_t m_Tracking_గమ్యం_Component_Local;
	VRComponentProperties uProperties;
} RenderModel_ComponentState_t;

రకనిర్వచనం నిర్మాణం HiddenAreaMesh_t
{
	నిర్మాణం HmdVector2_t * p_శీర్షం_దత్తాంశం; // const struct vr::HmdVector2_t *
	uint32_t un_Triangle_లెక్క;
} HiddenAreaMesh_t;

రకనిర్వచనం నిర్మాణం VRControllerAxis_t
{
	దశాంశం x;
	దశాంశం y;
} VRControllerAxis_t;

రకనిర్వచనం నిర్మాణం VRControllerState_t
{
	uint32_t un_Packet_అంకె;
	uint64_t ulButtonPressed;
	uint64_t ulButtonTouched;
	నిర్మాణం VRControllerAxis_t rAxis[5]; //struct vr::VRControllerAxis_t[5]
} VRControllerState_t;

రకనిర్వచనం నిర్మాణం Camera_Video_ప్రవాహం_చట్రం_శీర్షిక_t
{
	గణన EVRTracked_Camera_చట్రం_Type e_చట్రం_Type;
	uint32_t n_వెడల్పు;
	uint32_t n_ఎత్తు;
	uint32_t n_బైట్లు_చొప్పున_Pixel;
	uint32_t n_చట్రం_Sequence;
	నిర్మాణం TrackedDevicePose_t trackedDevicePose;
	uint64_t ul_చట్రం_Exposure_సమయం;
} Camera_Video_ప్రవాహం_చట్రం_శీర్షిక_t;

రకనిర్వచనం నిర్మాణం Compositor_చట్రం_Timing
{
	uint32_t m_n_కొలత;
	uint32_t m_n_చట్రం_సూచీ;
	uint32_t m_n_అంకె_చట్రం_Presents;
	uint32_t m_n_అంకె_Mis_Presented;
	uint32_t m_n_అంకె_Dropped_చట్రాలు;
	uint32_t m_nReprojectionFlags;
	ద్విగుణ m_fl_System_సమయం_లోపల_Seconds;
	దశాంశం m_flPreSubmitGpuMs;
	దశాంశం m_flPostSubmitGpuMs;
	దశాంశం m_fl_మొత్తం_Render_Gpu_Ms;
	దశాంశం m_flCompositorRenderGpuMs;
	దశాంశం m_flCompositorRenderCpuMs;
	దశాంశం m_flCompositorIdleCpuMs;
	దశాంశం m_fl_Client_చట్రం_Interval_Ms;
	దశాంశం m_flPresentCallCpuMs;
	దశాంశం m_flWaitForPresentCpuMs;
	దశాంశం m_fl_Submit_చట్రం_Ms;
	దశాంశం m_flWaitGetPosesCalledMs;
	దశాంశం m_flNewPosesReadyMs;
	దశాంశం m_fl_New_చట్రం_Ready_Ms;
	దశాంశం m_fl_Compositor_Update_ప్రారంభం_Ms;
	దశాంశం m_fl_Compositor_Update_చివర_Ms;
	దశాంశం m_fl_Compositor_Render_ప్రారంభం_Ms;
	TrackedDevicePose_t m_HmdPose;
	uint32_t m_n_అంకె_VSyncs_Ready_For_Use;
	uint32_t m_n_అంకె_VSyncs_గమ్యం_మొదటి_View;
} Compositor_చట్రం_Timing;

రకనిర్వచనం నిర్మాణం Compositor_BenchmarkResults
{
	దశాంశం m_fl_Mega_Pixels_చొప్పున_రెండవ;
	దశాంశం m_fl_Hmd_Recommended_Mega_Pixels_చొప్పున_రెండవ;
} Compositor_BenchmarkResults;

రకనిర్వచనం నిర్మాణం Driver_ప్రత్యక్ష_బహుళకం_చట్రం_Timing
{
	uint32_t m_n_కొలత;
	uint32_t m_n_అంకె_చట్రం_Presents;
	uint32_t m_n_అంకె_Mis_Presented;
	uint32_t m_n_అంకె_Dropped_చట్రాలు;
	uint32_t m_nReprojectionFlags;
} Driver_ప్రత్యక్ష_బహుళకం_చట్రం_Timing;

రకనిర్వచనం నిర్మాణం ImuSample_t
{
	ద్విగుణ f_Sample_సమయం;
	నిర్మాణం HmdVector3d_t vAccel;
	నిర్మాణం HmdVector3d_t vGyro;
	uint32_t unOffScaleFlags;
} ImuSample_t;

రకనిర్వచనం నిర్మాణం App_Override_కీలకాలు_t
{
	అక్షరం * pch_కీలకం; // const char *
	అక్షరం * pch_విలువ; // const char *
} App_Override_కీలకాలు_t;

రకనిర్వచనం నిర్మాణం Compositor_CumulativeStats
{
	uint32_t m_nPid;
	uint32_t m_n_అంకె_చట్రం_Presents;
	uint32_t m_n_అంకె_Dropped_చట్రాలు;
	uint32_t m_n_అంకె_Reprojected_చట్రాలు;
	uint32_t m_n_అంకె_చట్రం_Presents_On_Startup;
	uint32_t m_n_అంకె_Dropped_చట్రాలు_On_Startup;
	uint32_t m_n_అంకె_Reprojected_చట్రాలు_On_Startup;
	uint32_t m_n_అంకె_Loading;
	uint32_t m_n_అంకె_చట్రం_Presents_Loading;
	uint32_t m_n_అంకె_Dropped_చట్రాలు_Loading;
	uint32_t m_n_అంకె_Reprojected_చట్రాలు_Loading;
	uint32_t m_n_అంకె_Timed_బహిర్గతం;
	uint32_t m_n_అంకె_చట్రం_Presents_Timed_బహిర్గతం;
	uint32_t m_n_అంకె_Dropped_చట్రాలు_Timed_బహిర్గతం;
	uint32_t m_n_అంకె_Reprojected_చట్రాలు_Timed_బహిర్గతం;
	uint32_t m_n_అంకె_చట్రం_Submits;
	ద్విగుణ m_fl_కూడిక_Compositor_CPUTime_MS;
	ద్విగుణ m_fl_కూడిక_Compositor_GPUTime_MS;
	ద్విగుణ m_fl_కూడిక_లక్ష్యం_చట్రం_Times;
	ద్విగుణ m_fl_కూడిక_Application_CPUTime_MS;
	ద్విగుణ m_fl_కూడిక_Application_GPUTime_MS;
} Compositor_CumulativeStats;

రకనిర్వచనం నిర్మాణం Compositor_StageRenderSettings
{
	నిర్మాణం HmdColor_t m_PrimaryColor;
	నిర్మాణం HmdColor_t m_SecondaryColor;
	దశాంశం m_flVignetteInnerRadius;
	దశాంశం m_flVignetteOuterRadius;
	దశాంశం m_flFresnelStrength;
	bool m_bBackfaceCulling;
	bool m_bGreyscale;
	bool m_bWireframe;
} Compositor_StageRenderSettings;

రకనిర్వచనం నిర్మాణం VROverlayIntersectionParams_t
{
	నిర్మాణం HmdVector3_t v_ఆధారం;
	నిర్మాణం HmdVector3_t vDirection;
	గణన ETrackingUniverseOrigin eOrigin;
} VROverlayIntersectionParams_t;

రకనిర్వచనం నిర్మాణం VROverlayIntersectionResults_t
{
	నిర్మాణం HmdVector3_t v_బిందువు;
	నిర్మాణం HmdVector3_t v_సాధారణ;
	నిర్మాణం HmdVector2_t vUVs;
	దశాంశం f_దూరం;
} VROverlayIntersectionResults_t;

రకనిర్వచనం నిర్మాణం Intersection_ముసుగు_Rectangle_t
{
	దశాంశం m_fl_శిఖరం_ఎడమ_X;
	దశాంశం m_fl_శిఖరం_ఎడమ_Y;
	దశాంశం m_fl_వెడల్పు;
	దశాంశం m_fl_ఎత్తు;
} Intersection_ముసుగు_Rectangle_t;

రకనిర్వచనం నిర్మాణం Intersection_ముసుగు_Circle_t
{
	దశాంశం m_flCenterX;
	దశాంశం m_flCenterY;
	దశాంశం m_flRadius;
} Intersection_ముసుగు_Circle_t;

రకనిర్వచనం నిర్మాణం VROverlayProjection_t
{
	దశాంశం f_ఎడమ;
	దశాంశం f_కుడి;
	దశాంశం f_శిఖరం;
	దశాంశం fBottom;
} VROverlayProjection_t;

రకనిర్వచనం నిర్మాణం VROverlayView_t
{
	VROverlayHandle_t overlayHandle;
	నిర్మాణం Texture_t texture;
	నిర్మాణం VRTextureBounds_t textureBounds;
} VROverlayView_t;

రకనిర్వచనం నిర్మాణం VRVulkanDevice_t
{
	నిర్మాణం VkInstance_T * m_pInstance; // struct VkInstance_T *
	నిర్మాణం VkDevice_T * m_pDevice; // struct VkDevice_T *
	నిర్మాణం VkPhysicalDevice_T * m_pPhysicalDevice; // struct VkPhysicalDevice_T *
	నిర్మాణం Vk_వరుస_T * m_p_వరుస; // struct VkQueue_T *
	uint32_t m_u_వరుస_Family_సూచీ;
} VRVulkanDevice_t;

రకనిర్వచనం నిర్మాణం VRNativeDevice_t
{
	శూన్య * handle; // void *
	గణన EDeviceType eType;
} VRNativeDevice_t;

రకనిర్వచనం నిర్మాణం Render_Model_శీర్షం_t
{
	నిర్మాణం HmdVector3_t vPosition;
	నిర్మాణం HmdVector3_t v_సాధారణ;
	దశాంశం rfTextureCoord[2]; //float[2]
} Render_Model_శీర్షం_t;

#ఒకవేళ defined(__linux__) || defined(__APPLE__)
#సూచన pack( నెట్టు, 4 )
#అయితే_ముగింపు
రకనిర్వచనం నిర్మాణం RenderModel_TextureMap_t
{
	uint16_t un_వెడల్పు;
	uint16_t un_ఎత్తు;
	uint8_t * rub_Texture_Map_దత్తాంశం; // const uint8_t *
	గణన EVRRenderModelTextureFormat format;
	uint16_t un_Mip_స్థాయిలు;
} RenderModel_TextureMap_t;

#ఒకవేళ defined(__linux__) || defined(__APPLE__)
#సూచన pack( తీయి )
#అయితే_ముగింపు
#ఒకవేళ defined(__linux__) || defined(__APPLE__)
#సూచన pack( నెట్టు, 4 )
#అయితే_ముగింపు
రకనిర్వచనం నిర్మాణం RenderModel_t
{
	నిర్మాణం Render_Model_శీర్షం_t * r_శీర్షం_దత్తాంశం; // const struct vr::RenderModel_Vertex_t *
	uint32_t un_శీర్షం_లెక్క;
	uint16_t * r_సూచీ_దత్తాంశం; // const uint16_t *
	uint32_t un_Triangle_లెక్క;
	TextureID_t diffuseTextureId;
} RenderModel_t;

#ఒకవేళ defined(__linux__) || defined(__APPLE__)
#సూచన pack( తీయి )
#అయితే_ముగింపు
రకనిర్వచనం నిర్మాణం Render_Model_Controller_బహుళకం_State_t
{
	bool bScrollWheelVisible;
} Render_Model_Controller_బహుళకం_State_t;

రకనిర్వచనం నిర్మాణం NotificationBitmap_t
{
	శూన్య * m_p_Image_దత్తాంశం; // void *
	int32_t m_n_వెడల్పు;
	int32_t m_n_ఎత్తు;
	int32_t m_n_బైట్లు_చొప్పున_Pixel;
} NotificationBitmap_t;

రకనిర్వచనం నిర్మాణం CVRSettingHelper
{
	intptr_t m_pSettings; // class vr::IVRSettings *
} CVRSettingHelper;

రకనిర్వచనం నిర్మాణం ఆదానం_Analog_Action_దత్తాంశం_t
{
	bool b_చురుకైన;
	VRInput_విలువ_Handle_t చురుకైన_Origin;
	దశాంశం x;
	దశాంశం y;
	దశాంశం z;
	దశాంశం deltaX;
	దశాంశం deltaY;
	దశాంశం deltaZ;
	దశాంశం f_Update_సమయం;
} ఆదానం_Analog_Action_దత్తాంశం_t;

రకనిర్వచనం నిర్మాణం ఆదానం_Digital_Action_దత్తాంశం_t
{
	bool b_చురుకైన;
	VRInput_విలువ_Handle_t చురుకైన_Origin;
	bool bState;
	bool b_మారింది;
	దశాంశం f_Update_సమయం;
} ఆదానం_Digital_Action_దత్తాంశం_t;

రకనిర్వచనం నిర్మాణం ఆదానం_Pose_Action_దత్తాంశం_t
{
	bool b_చురుకైన;
	VRInput_విలువ_Handle_t చురుకైన_Origin;
	నిర్మాణం TrackedDevicePose_t pose;
} ఆదానం_Pose_Action_దత్తాంశం_t;

రకనిర్వచనం నిర్మాణం ఆదానం_Skeletal_Action_దత్తాంశం_t
{
	bool b_చురుకైన;
	VRInput_విలువ_Handle_t చురుకైన_Origin;
} ఆదానం_Skeletal_Action_దత్తాంశం_t;

రకనిర్వచనం నిర్మాణం ఆదానం_Origin_Info_t
{
	VRInput_విలువ_Handle_t device_మార్గం;
	Tracked_Device_సూచీ_t tracked_Device_సూచీ;
	అక్షరం rchRenderModelComponentName[128]; //char[128]
} ఆదానం_Origin_Info_t;

రకనిర్వచనం నిర్మాణం ఆదానం_Binding_Info_t
{
	అక్షరం rch_Device_మార్గం_Name[128]; //char[128]
	అక్షరం rch_ఆదానం_మార్గం_Name[128]; //char[128]
	అక్షరం rch_బహుళకం_Name[128]; //char[128]
	అక్షరం rch_స్థానం_Name[128]; //char[128]
	అక్షరం rch_ఆదానం_ఆధారం_Type[32]; //char[32]
} ఆదానం_Binding_Info_t;

రకనిర్వచనం నిర్మాణం VRActive_Action_సమితి_t
{
	VRAction_సమితి_Handle_t ul_Action_సమితి;
	VRInput_విలువ_Handle_t ul_Restricted_గమ్యం_Device;
	VRAction_సమితి_Handle_t ul_Secondary_Action_సమితి;
	uint32_t unPadding;
	int32_t n_ప్రాధాన్యత;
} VRActive_Action_సమితి_t;

రకనిర్వచనం నిర్మాణం VRSkeletal_Summary_దత్తాంశం_t
{
	దశాంశం flFingerCurl[5]; //float[5]
	దశాంశం flFingerSplay[4]; //float[4]
} VRSkeletal_Summary_దత్తాంశం_t;

రకనిర్వచనం నిర్మాణం SpatialAnchorPose_t
{
	నిర్మాణం HmdMatrix34_t m_Anchor_గమ్యం_Absolute_Tracking;
} SpatialAnchorPose_t;

రకనిర్వచనం నిర్మాణం COpenVRContext
{
	intptr_t m_pVRSystem; // class vr::IVRSystem *
	intptr_t m_pVRChaperone; // class vr::IVRChaperone *
	intptr_t m_p_VRChaperone_అమరిక; // class vr::IVRChaperoneSetup *
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

రకనిర్వచనం నిర్మాణం PropertyWrite_t
{
	గణన ETrackedDeviceProperty prop;
	గణన EPropertyWriteType writeType;
	గణన ETrackedPropertyError e_సమితి_Error;
	శూన్య * pv_బఫరు; // void *
	uint32_t un_బఫరు_కొలత;
	Property_Type_ట్యాగ్_t un_ట్యాగ్;
	గణన ETrackedPropertyError eError;
} PropertyWrite_t;

రకనిర్వచనం నిర్మాణం PropertyRead_t
{
	గణన ETrackedDeviceProperty prop;
	శూన్య * pv_బఫరు; // void *
	uint32_t un_బఫరు_కొలత;
	Property_Type_ట్యాగ్_t un_ట్యాగ్;
	uint32_t un_Required_బఫరు_కొలత;
	గణన ETrackedPropertyError eError;
} PropertyRead_t;

రకనిర్వచనం నిర్మాణం CVRPropertyHelpers
{
	intptr_t m_pProperties; // class vr::IVRProperties *
} CVRPropertyHelpers;

రకనిర్వచనం నిర్మాణం మార్గం_Write_t
{
	మార్గం_Handle_t ul_మార్గం;
	గణన EPropertyWriteType writeType;
	గణన ETrackedPropertyError e_సమితి_Error;
	శూన్య * pv_బఫరు; // void *
	uint32_t un_బఫరు_కొలత;
	Property_Type_ట్యాగ్_t un_ట్యాగ్;
	గణన ETrackedPropertyError eError;
	అక్షరం * psz_మార్గం; // const char *
} మార్గం_Write_t;

రకనిర్వచనం నిర్మాణం మార్గం_Read_t
{
	మార్గం_Handle_t ul_మార్గం;
	శూన్య * pv_బఫరు; // void *
	uint32_t un_బఫరు_కొలత;
	Property_Type_ట్యాగ్_t un_ట్యాగ్;
	uint32_t un_Required_బఫరు_కొలత;
	గణన ETrackedPropertyError eError;
	అక్షరం * psz_మార్గం; // const char *
} మార్గం_Read_t;


రకనిర్వచనం సంఘం
{
	VREvent_Reserved_t reserved;
	VREvent_Controller_t controller;
	VREvent_Mouse_t mouse;
	VREvent_Scroll_t scroll;
	VREvent_Process_t process;
	VREvent_Notification_t notification;
	VREvent_Overlay_t overlay;
	VREvent_స్థితి_t స్థితి_2;
	VREvent_Keyboard_t keyboard;
	VREvent_Ipd_t ipd;
	VREvent_Chaperone_t chaperone;
	VREvent_PerformanceTest_t performanceTest;
	VREvent_TouchPadMove_t touchPadMove;
	VREvent_SeatedZeroPoseReset_t seatedZeroPoseReset;
	VREvent_Screenshot_t screenshot;
	VREvent_Screenshot_పురోగతి_t screenshot_పురోగతి;
	VREvent_ApplicationLaunch_t applicationLaunch;
	VREvent_EditingCameraSurface_t cameraSurface;
	VREvent_సందేశం_Overlay_t సందేశం_Overlay;
	VREvent_Property_t property;
	VREvent_HapticVibration_t hapticVibration;
	VREvent_WebConsole_t webConsole;
	VREvent_ఆదానం_Binding_ఎక్కించు_t ఆదానం_Binding;
	VREvent_ఆదానం_Action_Manifest_ఎక్కించు_t actionManifest;
	VREvent_SpatialAnchor_t spatialAnchor;
} VREvent_దత్తాంశం_t;

#ఒకవేళ defined(__linux__) || defined(__APPLE__) 
// This structure was originally defined mis-packed on Linux, preserved for 
// compatibility. 
#సూచన pack( నెట్టు, 4 )
#అయితే_ముగింపు

/** An event posted by the server to all running applications */
నిర్మాణం VREvent_t
{
	uint32_t eventType; // EVREventType enum
	Tracked_Device_సూచీ_t tracked_Device_సూచీ;
	దశాంశం eventAgeSeconds;
	// event data must be the end of the struct as its size is variable
	VREvent_దత్తాంశం_t దత్తాంశం;
};

#ఒకవేళ defined(__linux__) || defined(__APPLE__) 
#సూచన pack( తీయి )
#అయితే_ముగింపు


రకనిర్వచనం సంఘం
{
	Intersection_ముసుగు_Rectangle_t m_Rectangle;
	Intersection_ముసుగు_Circle_t m_Circle;
} VROverlay_Intersection_ముసుగు_Primitive_దత్తాంశం_t;

నిర్మాణం VROverlay_Intersection_ముసుగు_Primitive_t
{
	EVROverlay_Intersection_ముసుగు_Primitive_Type m_nPrimitiveType;
	VROverlay_Intersection_ముసుగు_Primitive_దత్తాంశం_t m_Primitive;
};


// OpenVR Function Pointer Tables

నిర్మాణం VR_IVRSystem_Fn_పట్టిక
{
	శూన్య (OPENVR_FNTABLE_CALLTYPE *Get_Recommended_Render_లక్ష్యం_కొలత)(uint32_t * pn_వెడల్పు, uint32_t * pn_ఎత్తు);
	నిర్మాణం HmdMatrix44_t (OPENVR_FNTABLE_CALLTYPE *Get_Projection_మాతృక)(EVREye eEye, దశాంశం fNearZ, దశాంశం fFarZ);
	శూన్య (OPENVR_FNTABLE_CALLTYPE *GetProjectionRaw)(EVREye eEye, దశాంశం * pf_ఎడమ, దశాంశం * pf_కుడి, దశాంశం * pf_శిఖరం, దశాంశం * pfBottom);
	bool (OPENVR_FNTABLE_CALLTYPE *ComputeDistortion)(EVREye eEye, దశాంశం fU, దశాంశం fV, నిర్మాణం DistortionCoordinates_t * pDistortionCoordinates);
	నిర్మాణం HmdMatrix34_t (OPENVR_FNTABLE_CALLTYPE *Get_Eye_గమ్యం_తల_Transform)(EVREye eEye);
	bool (OPENVR_FNTABLE_CALLTYPE *Get_సమయం_Since_చివరి_Vsync)(దశాంశం * pf_Seconds_Since_చివరి_Vsync, uint64_t * pul_చట్రం_Counter);
	int32_t (OPENVR_FNTABLE_CALLTYPE *Get_D3_D9_Adapter_సూచీ)();
	శూన్య (OPENVR_FNTABLE_CALLTYPE *GetDXGIOutputInfo)(int32_t * pn_Adapter_సూచీ);
	శూన్య (OPENVR_FNTABLE_CALLTYPE *GetOutputDevice)(uint64_t * pnDevice, ETextureType textureType, నిర్మాణం VkInstance_T * pInstance);
	bool (OPENVR_FNTABLE_CALLTYPE *IsDisplayOnDesktop)();
	bool (OPENVR_FNTABLE_CALLTYPE *సమితి_Display_Visibility)(bool bIsVisibleOnDesktop);
	శూన్య (OPENVR_FNTABLE_CALLTYPE *Get_Device_గమ్యం_Absolute_Tracking_Pose)(ETrackingUniverseOrigin eOrigin, దశాంశం f_Predicted_Seconds_గమ్యం_Photons_From_Now, నిర్మాణం TrackedDevicePose_t * pTrackedDevicePoseArray, uint32_t un_Tracked_Device_Pose_Array_లెక్క);
	నిర్మాణం HmdMatrix34_t (OPENVR_FNTABLE_CALLTYPE *Get_Seated_Zero_Pose_గమ్యం_Standing_Absolute_Tracking_Pose)();
	నిర్మాణం HmdMatrix34_t (OPENVR_FNTABLE_CALLTYPE *Get_Raw_Zero_Pose_గమ్యం_Standing_Absolute_Tracking_Pose)();
	uint32_t (OPENVR_FNTABLE_CALLTYPE *Get_Sorted_Tracked_Device_Indices_యొక్క_Class)(ETrackedDeviceClass eTrackedDeviceClass, Tracked_Device_సూచీ_t * pun_Tracked_Device_సూచీ_Array, uint32_t un_Tracked_Device_సూచీ_Array_లెక్క, Tracked_Device_సూచీ_t un_Relative_గమ్యం_Tracked_Device_సూచీ);
	EDeviceActivityLevel (OPENVR_FNTABLE_CALLTYPE *GetTrackedDeviceActivityLevel)(Tracked_Device_సూచీ_t unDeviceId);
	శూన్య (OPENVR_FNTABLE_CALLTYPE *ApplyTransform)(నిర్మాణం TrackedDevicePose_t * pOutputPose, నిర్మాణం TrackedDevicePose_t * pTrackedDevicePose, నిర్మాణం HmdMatrix34_t * pTransform);
	Tracked_Device_సూచీ_t (OPENVR_FNTABLE_CALLTYPE *Get_Tracked_Device_సూచీ_For_Controller_Role)(ETrackedControllerRole unDeviceType);
	ETrackedControllerRole (OPENVR_FNTABLE_CALLTYPE *Get_Controller_Role_For_Tracked_Device_సూచీ)(Tracked_Device_సూచీ_t un_Device_సూచీ);
	ETrackedDeviceClass (OPENVR_FNTABLE_CALLTYPE *GetTrackedDeviceClass)(Tracked_Device_సూచీ_t un_Device_సూచీ);
	bool (OPENVR_FNTABLE_CALLTYPE *IsTrackedDeviceConnected)(Tracked_Device_సూచీ_t un_Device_సూచీ);
	bool (OPENVR_FNTABLE_CALLTYPE *GetBoolTrackedDeviceProperty)(Tracked_Device_సూచీ_t un_Device_సూచీ, ETrackedDeviceProperty prop, ETrackedPropertyError * pError);
	దశాంశం (OPENVR_FNTABLE_CALLTYPE *GetFloatTrackedDeviceProperty)(Tracked_Device_సూచీ_t un_Device_సూచీ, ETrackedDeviceProperty prop, ETrackedPropertyError * pError);
	int32_t (OPENVR_FNTABLE_CALLTYPE *GetInt32TrackedDeviceProperty)(Tracked_Device_సూచీ_t un_Device_సూచీ, ETrackedDeviceProperty prop, ETrackedPropertyError * pError);
	uint64_t (OPENVR_FNTABLE_CALLTYPE *GetUint64TrackedDeviceProperty)(Tracked_Device_సూచీ_t un_Device_సూచీ, ETrackedDeviceProperty prop, ETrackedPropertyError * pError);
	నిర్మాణం HmdMatrix34_t (OPENVR_FNTABLE_CALLTYPE *GetMatrix34TrackedDeviceProperty)(Tracked_Device_సూచీ_t un_Device_సూచీ, ETrackedDeviceProperty prop, ETrackedPropertyError * pError);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetArrayTrackedDeviceProperty)(Tracked_Device_సూచీ_t un_Device_సూచీ, ETrackedDeviceProperty prop, Property_Type_ట్యాగ్_t propType, శూన్య * p_బఫరు, uint32_t un_బఫరు_కొలత, ETrackedPropertyError * pError);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetStringTrackedDeviceProperty)(Tracked_Device_సూచీ_t un_Device_సూచీ, ETrackedDeviceProperty prop, అక్షరం * pch_విలువ, uint32_t un_బఫరు_కొలత, ETrackedPropertyError * pError);
	అక్షరం * (OPENVR_FNTABLE_CALLTYPE *GetPropErrorNameFromEnum)(ETrackedPropertyError error);
	bool (OPENVR_FNTABLE_CALLTYPE *Poll_తదుపరి_Event)(నిర్మాణం VREvent_t * pEvent, uint32_t uncbVREvent);
	bool (OPENVR_FNTABLE_CALLTYPE *Poll_తదుపరి_Event_With_Pose)(ETrackingUniverseOrigin eOrigin, నిర్మాణం VREvent_t * pEvent, uint32_t uncbVREvent, TrackedDevicePose_t * pTrackedDevicePose);
	అక్షరం * (OPENVR_FNTABLE_CALLTYPE *GetEventTypeNameFromEnum)(EVREventType eType);
	నిర్మాణం HiddenAreaMesh_t (OPENVR_FNTABLE_CALLTYPE *GetHiddenAreaMesh)(EVREye eEye, EHiddenAreaMeshType type);
	bool (OPENVR_FNTABLE_CALLTYPE *GetControllerState)(Tracked_Device_సూచీ_t un_Controller_Device_సూచీ, VRControllerState_t * pControllerState, uint32_t un_Controller_State_కొలత);
	bool (OPENVR_FNTABLE_CALLTYPE *GetControllerStateWithPose)(ETrackingUniverseOrigin eOrigin, Tracked_Device_సూచీ_t un_Controller_Device_సూచీ, VRControllerState_t * pControllerState, uint32_t un_Controller_State_కొలత, నిర్మాణం TrackedDevicePose_t * pTrackedDevicePose);
	శూన్య (OPENVR_FNTABLE_CALLTYPE *TriggerHapticPulse)(Tracked_Device_సూచీ_t un_Controller_Device_సూచీ, uint32_t unAxisId, గుర్తులేని పొట్టి usDurationMicroSec);
	అక్షరం * (OPENVR_FNTABLE_CALLTYPE *GetButtonIdNameFromEnum)(EVRButtonId eButtonId);
	అక్షరం * (OPENVR_FNTABLE_CALLTYPE *GetControllerAxisTypeNameFromEnum)(EVRControllerAxisType eAxisType);
	bool (OPENVR_FNTABLE_CALLTYPE *Is_ఆదానం_అందుబాటు)();
	bool (OPENVR_FNTABLE_CALLTYPE *IsSteamVRDrawingControllers)();
	bool (OPENVR_FNTABLE_CALLTYPE *ShouldApplicationPause)();
	bool (OPENVR_FNTABLE_CALLTYPE *ShouldApplicationReduceRenderingWork)();
	EVRFirmwareError (OPENVR_FNTABLE_CALLTYPE *PerformFirmwareUpdate)(Tracked_Device_సూచీ_t un_Device_సూచీ);
	శూన్య (OPENVR_FNTABLE_CALLTYPE *AcknowledgeQuit_Exiting)();
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetAppContainerFilePaths)(అక్షరం * pch_బఫరు, uint32_t un_బఫరు_కొలత);
	అక్షరం * (OPENVR_FNTABLE_CALLTYPE *Get_Runtime_సంస్కరణ)();
};

నిర్మాణం VR_IVRExtended_Display_Fn_పట్టిక
{
	శూన్య (OPENVR_FNTABLE_CALLTYPE *Get_కిటికీ_Bounds)(int32_t * pnX, int32_t * pnY, uint32_t * pn_వెడల్పు, uint32_t * pn_ఎత్తు);
	శూన్య (OPENVR_FNTABLE_CALLTYPE *GetEyeOutputViewport)(EVREye eEye, uint32_t * pnX, uint32_t * pnY, uint32_t * pn_వెడల్పు, uint32_t * pn_ఎత్తు);
	శూన్య (OPENVR_FNTABLE_CALLTYPE *GetDXGIOutputInfo)(int32_t * pn_Adapter_సూచీ, int32_t * pn_Adapter_Output_సూచీ);
};

నిర్మాణం VR_IVRTracked_Camera_Fn_పట్టిక
{
	అక్షరం * (OPENVR_FNTABLE_CALLTYPE *GetCameraErrorNameFromEnum)(EVRTrackedCameraError eCameraError);
	EVRTrackedCameraError (OPENVR_FNTABLE_CALLTYPE *HasCamera)(Tracked_Device_సూచీ_t n_Device_సూచీ, bool * pHasCamera);
	EVRTrackedCameraError (OPENVR_FNTABLE_CALLTYPE *Get_Camera_చట్రం_కొలత)(Tracked_Device_సూచీ_t n_Device_సూచీ, EVRTracked_Camera_చట్రం_Type e_చట్రం_Type, uint32_t * pn_వెడల్పు, uint32_t * pn_ఎత్తు, uint32_t * pn_చట్రం_బఫరు_కొలత);
	EVRTrackedCameraError (OPENVR_FNTABLE_CALLTYPE *GetCameraIntrinsics)(Tracked_Device_సూచీ_t n_Device_సూచీ, uint32_t n_Camera_సూచీ, EVRTracked_Camera_చట్రం_Type e_చట్రం_Type, HmdVector2_t * p_Focal_నిడివి, HmdVector2_t * pCenter);
	EVRTrackedCameraError (OPENVR_FNTABLE_CALLTYPE *GetCameraProjection)(Tracked_Device_సూచీ_t n_Device_సూచీ, uint32_t n_Camera_సూచీ, EVRTracked_Camera_చట్రం_Type e_చట్రం_Type, దశాంశం flZNear, దశాంశం flZFar, HmdMatrix44_t * pProjection);
	EVRTrackedCameraError (OPENVR_FNTABLE_CALLTYPE *AcquireVideoStreamingService)(Tracked_Device_సూచీ_t n_Device_సూచీ, TrackedCameraHandle_t * pHandle);
	EVRTrackedCameraError (OPENVR_FNTABLE_CALLTYPE *ReleaseVideoStreamingService)(TrackedCameraHandle_t hTrackedCamera);
	EVRTrackedCameraError (OPENVR_FNTABLE_CALLTYPE *Get_Video_ప్రవాహం_చట్రం_బఫరు)(TrackedCameraHandle_t hTrackedCamera, EVRTracked_Camera_చట్రం_Type e_చట్రం_Type, శూన్య * p_చట్రం_బఫరు, uint32_t n_చట్రం_బఫరు_కొలత, Camera_Video_ప్రవాహం_చట్రం_శీర్షిక_t * p_చట్రం_శీర్షిక, uint32_t n_చట్రం_శీర్షిక_కొలత);
	EVRTrackedCameraError (OPENVR_FNTABLE_CALLTYPE *Get_Video_ప్రవాహం_Texture_కొలత)(Tracked_Device_సూచీ_t n_Device_సూచీ, EVRTracked_Camera_చట్రం_Type e_చట్రం_Type, VRTextureBounds_t * pTextureBounds, uint32_t * pn_వెడల్పు, uint32_t * pn_ఎత్తు);
	EVRTrackedCameraError (OPENVR_FNTABLE_CALLTYPE *Get_Video_ప్రవాహం_Texture_D3_D11)(TrackedCameraHandle_t hTrackedCamera, EVRTracked_Camera_చట్రం_Type e_చట్రం_Type, శూన్య * pD3D11DeviceOrResource, శూన్య ** ppD3D11ShaderResourceView, Camera_Video_ప్రవాహం_చట్రం_శీర్షిక_t * p_చట్రం_శీర్షిక, uint32_t n_చట్రం_శీర్షిక_కొలత);
	EVRTrackedCameraError (OPENVR_FNTABLE_CALLTYPE *Get_Video_ప్రవాహం_Texture_GL)(TrackedCameraHandle_t hTrackedCamera, EVRTracked_Camera_చట్రం_Type e_చట్రం_Type, glUInt_t * pglTextureId, Camera_Video_ప్రవాహం_చట్రం_శీర్షిక_t * p_చట్రం_శీర్షిక, uint32_t n_చట్రం_శీర్షిక_కొలత);
	EVRTrackedCameraError (OPENVR_FNTABLE_CALLTYPE *Release_Video_ప్రవాహం_Texture_GL)(TrackedCameraHandle_t hTrackedCamera, glUInt_t glTextureId);
	శూన్య (OPENVR_FNTABLE_CALLTYPE *సమితి_Camera_Tracking_Space)(ETrackingUniverseOrigin eUniverse);
	ETrackingUniverseOrigin (OPENVR_FNTABLE_CALLTYPE *GetCameraTrackingSpace)();
};

నిర్మాణం VR_IVRApplications_Fn_పట్టిక
{
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *కూడు_Application_Manifest)(అక్షరం * pch_Application_Manifest_నిండిన_మార్గం, bool bTemporary);
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *RemoveApplicationManifest)(అక్షరం * pch_Application_Manifest_నిండిన_మార్గం);
	bool (OPENVR_FNTABLE_CALLTYPE *IsApplicationInstalled)(అక్షరం * pch_App_కీలకం);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *Get_Application_లెక్క)();
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *Get_Application_కీలకం_By_సూచీ)(uint32_t un_Application_సూచీ, అక్షరం * pch_App_కీలకం_బఫరు, uint32_t un_App_కీలకం_బఫరు_Len);
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *Get_Application_కీలకం_By_Process_Id)(uint32_t unProcessId, అక్షరం * pch_App_కీలకం_బఫరు, uint32_t un_App_కీలకం_బఫరు_Len);
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *LaunchApplication)(అక్షరం * pch_App_కీలకం);
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *LaunchTemplateApplication)(అక్షరం * pch_Template_App_కీలకం, అక్షరం * pch_New_App_కీలకం, నిర్మాణం App_Override_కీలకాలు_t * p_కీలకాలు, uint32_t un_కీలకాలు);
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *LaunchApplicationFromMimeType)(అక్షరం * pchMimeType, అక్షరం * pch_వాదనలు);
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *LaunchDashboardOverlay)(అక్షరం * pch_App_కీలకం);
	bool (OPENVR_FNTABLE_CALLTYPE *CancelApplicationLaunch)(అక్షరం * pch_App_కీలకం);
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *IdentifyApplication)(uint32_t unProcessId, అక్షరం * pch_App_కీలకం);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetApplicationProcessId)(అక్షరం * pch_App_కీలకం);
	అక్షరం * (OPENVR_FNTABLE_CALLTYPE *GetApplicationsErrorNameFromEnum)(EVRApplicationError error);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetApplicationPropertyString)(అక్షరం * pch_App_కీలకం, EVRApplicationProperty eProperty, అక్షరం * pch_Property_విలువ_బఫరు, uint32_t un_Property_విలువ_బఫరు_Len, EVRApplicationError * peError);
	bool (OPENVR_FNTABLE_CALLTYPE *GetApplicationPropertyBool)(అక్షరం * pch_App_కీలకం, EVRApplicationProperty eProperty, EVRApplicationError * peError);
	uint64_t (OPENVR_FNTABLE_CALLTYPE *GetApplicationPropertyUint64)(అక్షరం * pch_App_కీలకం, EVRApplicationProperty eProperty, EVRApplicationError * peError);
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *సమితి_Application_Auto_Launch)(అక్షరం * pch_App_కీలకం, bool bAutoLaunch);
	bool (OPENVR_FNTABLE_CALLTYPE *GetApplicationAutoLaunch)(అక్షరం * pch_App_కీలకం);
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *సమితి_Default_Application_For_Mime_Type)(అక్షరం * pch_App_కీలకం, అక్షరం * pchMimeType);
	bool (OPENVR_FNTABLE_CALLTYPE *GetDefaultApplicationForMimeType)(అక్షరం * pchMimeType, అక్షరం * pch_App_కీలకం_బఫరు, uint32_t un_App_కీలకం_బఫరు_Len);
	bool (OPENVR_FNTABLE_CALLTYPE *GetApplicationSupportedMimeTypes)(అక్షరం * pch_App_కీలకం, అక్షరం * pch_Mime_Types_బఫరు, uint32_t un_Mime_Types_బఫరు);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetApplicationsThatSupportMimeType)(అక్షరం * pchMimeType, అక్షరం * pch_App_కీలకాలు_That_Support_బఫరు, uint32_t un_App_కీలకాలు_That_Support_బఫరు);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetApplicationLaunchArguments)(uint32_t unHandle, అక్షరం * pch_వాదనలు, uint32_t un_వాదనలు);
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *GetStartingApplication)(అక్షరం * pch_App_కీలకం_బఫరు, uint32_t un_App_కీలకం_బఫరు_Len);
	EVRSceneApplicationState (OPENVR_FNTABLE_CALLTYPE *GetSceneApplicationState)();
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *PerformApplicationPrelaunchCheck)(అక్షరం * pch_App_కీలకం);
	అక్షరం * (OPENVR_FNTABLE_CALLTYPE *GetSceneApplicationStateNameFromEnum)(EVRSceneApplicationState state);
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *Launch_అంతర్గత_Process)(అక్షరం * pch_ద్విమాన_మార్గం, అక్షరం * pchArguments, అక్షరం * pchWorkingDirectory);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetCurrentSceneProcessId)();
};

నిర్మాణం VR_IVRChaperone_Fn_పట్టిక
{
	ChaperoneCalibrationState (OPENVR_FNTABLE_CALLTYPE *GetCalibrationState)();
	bool (OPENVR_FNTABLE_CALLTYPE *Get_Play_Area_కొలత)(దశాంశం * p_కొలత_X, దశాంశం * p_కొలత_Z);
	bool (OPENVR_FNTABLE_CALLTYPE *GetPlayAreaRect)(నిర్మాణం HmdQuad_t * rect);
	శూన్య (OPENVR_FNTABLE_CALLTYPE *ReloadInfo)();
	శూన్య (OPENVR_FNTABLE_CALLTYPE *సమితి_Scene_Color)(నిర్మాణం HmdColor_t color);
	శూన్య (OPENVR_FNTABLE_CALLTYPE *GetBoundsColor)(నిర్మాణం HmdColor_t * pOutputColorArray, పూర్ణాంకం n_అంకె_Output_Colors, దశాంశం fl_Collision_Bounds_Fade_దూరం, నిర్మాణం HmdColor_t * pOutputCameraColor);
	bool (OPENVR_FNTABLE_CALLTYPE *AreBoundsVisible)();
	శూన్య (OPENVR_FNTABLE_CALLTYPE *ForceBoundsVisible)(bool bForce);
	శూన్య (OPENVR_FNTABLE_CALLTYPE *ResetZeroPose)(ETrackingUniverseOrigin eTrackingUniverseOrigin);
};

నిర్మాణం VR_IVRChaperone_అమరిక_Fn_పట్టిక
{
	bool (OPENVR_FNTABLE_CALLTYPE *CommitWorkingCopy)(EChaperoneConfigFile configFile);
	శూన్య (OPENVR_FNTABLE_CALLTYPE *RevertWorkingCopy)();
	bool (OPENVR_FNTABLE_CALLTYPE *Get_Working_Play_Area_కొలత)(దశాంశం * p_కొలత_X, దశాంశం * p_కొలత_Z);
	bool (OPENVR_FNTABLE_CALLTYPE *GetWorkingPlayAreaRect)(నిర్మాణం HmdQuad_t * rect);
	bool (OPENVR_FNTABLE_CALLTYPE *GetWorkingCollisionBoundsInfo)(నిర్మాణం HmdQuad_t * p_Quads_బఫరు, uint32_t * pun_Quads_లెక్క);
	bool (OPENVR_FNTABLE_CALLTYPE *Get_సజీవ_Collision_Bounds_Info)(నిర్మాణం HmdQuad_t * p_Quads_బఫరు, uint32_t * pun_Quads_లెక్క);
	bool (OPENVR_FNTABLE_CALLTYPE *Get_Working_Seated_Zero_Pose_గమ్యం_Raw_Tracking_Pose)(నిర్మాణం HmdMatrix34_t * pmat_Seated_Zero_Pose_గమ్యం_Raw_Tracking_Pose);
	bool (OPENVR_FNTABLE_CALLTYPE *Get_Working_Standing_Zero_Pose_గమ్యం_Raw_Tracking_Pose)(నిర్మాణం HmdMatrix34_t * pmat_Standing_Zero_Pose_గమ్యం_Raw_Tracking_Pose);
	శూన్య (OPENVR_FNTABLE_CALLTYPE *సమితి_Working_Play_Area_కొలత)(దశాంశం కొలత_X, దశాంశం కొలత_Z);
	శూన్య (OPENVR_FNTABLE_CALLTYPE *సమితి_Working_Collision_Bounds_Info)(నిర్మాణం HmdQuad_t * p_Quads_బఫరు, uint32_t un_Quads_లెక్క);
	శూన్య (OPENVR_FNTABLE_CALLTYPE *సమితి_Working_Perimeter)(నిర్మాణం HmdVector2_t * p_బిందువు_బఫరు, uint32_t un_బిందువు_లెక్క);
	శూన్య (OPENVR_FNTABLE_CALLTYPE *సమితి_Working_Seated_Zero_Pose_గమ్యం_Raw_Tracking_Pose)(నిర్మాణం HmdMatrix34_t * p_Mat_Seated_Zero_Pose_గమ్యం_Raw_Tracking_Pose);
	శూన్య (OPENVR_FNTABLE_CALLTYPE *సమితి_Working_Standing_Zero_Pose_గమ్యం_Raw_Tracking_Pose)(నిర్మాణం HmdMatrix34_t * p_Mat_Standing_Zero_Pose_గమ్యం_Raw_Tracking_Pose);
	శూన్య (OPENVR_FNTABLE_CALLTYPE *ReloadFromDisk)(EChaperoneConfigFile configFile);
	bool (OPENVR_FNTABLE_CALLTYPE *Get_సజీవ_Seated_Zero_Pose_గమ్యం_Raw_Tracking_Pose)(నిర్మాణం HmdMatrix34_t * pmat_Seated_Zero_Pose_గమ్యం_Raw_Tracking_Pose);
	bool (OPENVR_FNTABLE_CALLTYPE *Export_సజీవ_గమ్యం_బఫరు)(అక్షరం * p_బఫరు, uint32_t * pn_బఫరు_నిడివి);
	bool (OPENVR_FNTABLE_CALLTYPE *Import_From_బఫరు_గమ్యం_Working)(అక్షరం * p_బఫరు, uint32_t nImportFlags);
	శూన్య (OPENVR_FNTABLE_CALLTYPE *Show_Working_సమితి_Preview)();
	శూన్య (OPENVR_FNTABLE_CALLTYPE *Hide_Working_సమితి_Preview)();
	శూన్య (OPENVR_FNTABLE_CALLTYPE *స్థలం_అమరిక_Starting)();
};

నిర్మాణం VR_IVRCompositor_Fn_పట్టిక
{
	శూన్య (OPENVR_FNTABLE_CALLTYPE *సమితి_Tracking_Space)(ETrackingUniverseOrigin eOrigin);
	ETrackingUniverseOrigin (OPENVR_FNTABLE_CALLTYPE *GetTrackingSpace)();
	EVRCompositorError (OPENVR_FNTABLE_CALLTYPE *WaitGetPoses)(నిర్మాణం TrackedDevicePose_t * pRenderPoseArray, uint32_t un_Render_Pose_Array_లెక్క, నిర్మాణం TrackedDevicePose_t * pGamePoseArray, uint32_t un_Game_Pose_Array_లెక్క);
	EVRCompositorError (OPENVR_FNTABLE_CALLTYPE *Get_చివరి_Poses)(నిర్మాణం TrackedDevicePose_t * pRenderPoseArray, uint32_t un_Render_Pose_Array_లెక్క, నిర్మాణం TrackedDevicePose_t * pGamePoseArray, uint32_t un_Game_Pose_Array_లెక్క);
	EVRCompositorError (OPENVR_FNTABLE_CALLTYPE *Get_చివరి_Pose_For_Tracked_Device_సూచీ)(Tracked_Device_సూచీ_t un_Device_సూచీ, నిర్మాణం TrackedDevicePose_t * pOutputPose, నిర్మాణం TrackedDevicePose_t * pOutputGamePose);
	EVRCompositorError (OPENVR_FNTABLE_CALLTYPE *Submit)(EVREye eEye, నిర్మాణం Texture_t * pTexture, నిర్మాణం VRTextureBounds_t * pBounds, EVRSubmitFlags nSubmitFlags);
	శూన్య (OPENVR_FNTABLE_CALLTYPE *Clear_చివరి_Submitted_చట్రం)();
	శూన్య (OPENVR_FNTABLE_CALLTYPE *PostPresentHandoff)();
	bool (OPENVR_FNTABLE_CALLTYPE *Get_చట్రం_Timing)(నిర్మాణం Compositor_చట్రం_Timing * pTiming, uint32_t un_చట్రాలు_Ago);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *Get_చట్రం_Timings)(నిర్మాణం Compositor_చట్రం_Timing * pTiming, uint32_t n_చట్రాలు);
	దశాంశం (OPENVR_FNTABLE_CALLTYPE *Get_చట్రం_సమయం_మిగిలిన)();
	శూన్య (OPENVR_FNTABLE_CALLTYPE *GetCumulativeStats)(నిర్మాణం Compositor_CumulativeStats * pStats, uint32_t n_Stats_కొలత_లోపల_బైట్లు);
	శూన్య (OPENVR_FNTABLE_CALLTYPE *Fade_గమ్యం_Color)(దశాంశం fSeconds, దశాంశం fRed, దశాంశం fGreen, దశాంశం fBlue, దశాంశం fAlpha, bool bBackground);
	నిర్మాణం HmdColor_t (OPENVR_FNTABLE_CALLTYPE *GetCurrentFadeColor)(bool bBackground);
	శూన్య (OPENVR_FNTABLE_CALLTYPE *FadeGrid)(దశాంశం fSeconds, bool b_Fade_Grid_లోపల);
	దశాంశం (OPENVR_FNTABLE_CALLTYPE *GetCurrentGridAlpha)();
	EVRCompositorError (OPENVR_FNTABLE_CALLTYPE *సమితి_Skybox_Override)(నిర్మాణం Texture_t * pTextures, uint32_t un_Texture_లెక్క);
	శూన్య (OPENVR_FNTABLE_CALLTYPE *ClearSkyboxOverride)();
	శూన్య (OPENVR_FNTABLE_CALLTYPE *Compositor_Bring_గమ్యం_Front)();
	శూన్య (OPENVR_FNTABLE_CALLTYPE *Compositor_Go_గమ్యం_వెనుక)();
	శూన్య (OPENVR_FNTABLE_CALLTYPE *CompositorQuit)();
	bool (OPENVR_FNTABLE_CALLTYPE *IsFullscreen)();
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetCurrentSceneFocusProcess)();
	uint32_t (OPENVR_FNTABLE_CALLTYPE *Get_చివరి_చట్రం_Renderer)();
	bool (OPENVR_FNTABLE_CALLTYPE *CanRenderScene)();
	శూన్య (OPENVR_FNTABLE_CALLTYPE *Show_Mirror_కిటికీ)();
	శూన్య (OPENVR_FNTABLE_CALLTYPE *Hide_Mirror_కిటికీ)();
	bool (OPENVR_FNTABLE_CALLTYPE *Is_Mirror_కిటికీ_Visible)();
	శూన్య (OPENVR_FNTABLE_CALLTYPE *CompositorDumpImages)();
	bool (OPENVR_FNTABLE_CALLTYPE *Should_App_Render_With_దిగువ_Resources)();
	శూన్య (OPENVR_FNTABLE_CALLTYPE *ForceInterleavedReprojectionOn)(bool bOverride);
	శూన్య (OPENVR_FNTABLE_CALLTYPE *ForceReconnectProcess)();
	శూన్య (OPENVR_FNTABLE_CALLTYPE *SuspendRendering)(bool bSuspend);
	EVRCompositorError (OPENVR_FNTABLE_CALLTYPE *GetMirrorTextureD3D11)(EVREye eEye, శూన్య * pD3D11DeviceOrResource, శూన్య ** ppD3D11ShaderResourceView);
	శూన్య (OPENVR_FNTABLE_CALLTYPE *ReleaseMirrorTextureD3D11)(శూన్య * pD3D11ShaderResourceView);
	EVRCompositorError (OPENVR_FNTABLE_CALLTYPE *GetMirrorTextureGL)(EVREye eEye, glUInt_t * pglTextureId, glSharedTextureHandle_t * pglSharedTextureHandle);
	bool (OPENVR_FNTABLE_CALLTYPE *ReleaseSharedGLTexture)(glUInt_t glTextureId, glSharedTextureHandle_t glSharedTextureHandle);
	శూన్య (OPENVR_FNTABLE_CALLTYPE *తాళం_GLShared_Texture_For_Access)(glSharedTextureHandle_t glSharedTextureHandle);
	శూన్య (OPENVR_FNTABLE_CALLTYPE *UnlockGLSharedTextureForAccess)(glSharedTextureHandle_t glSharedTextureHandle);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetVulkanInstanceExtensionsRequired)(అక్షరం * pch_విలువ, uint32_t un_బఫరు_కొలత);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetVulkanDeviceExtensionsRequired)(నిర్మాణం VkPhysicalDevice_T * pPhysicalDevice, అక్షరం * pch_విలువ, uint32_t un_బఫరు_కొలత);
	శూన్య (OPENVR_FNTABLE_CALLTYPE *సమితి_Explicit_Timing_బహుళకం)(EVRCompositor_Timing_బహుళకం e_Timing_బహుళకం);
	EVRCompositorError (OPENVR_FNTABLE_CALLTYPE *Submit_Explicit_Timing_దత్తాంశం)();
	bool (OPENVR_FNTABLE_CALLTYPE *IsMotionSmoothingEnabled)();
	bool (OPENVR_FNTABLE_CALLTYPE *IsMotionSmoothingSupported)();
	bool (OPENVR_FNTABLE_CALLTYPE *IsCurrentSceneFocusAppLoading)();
	EVRCompositorError (OPENVR_FNTABLE_CALLTYPE *సమితి_Stage_Override_Async)(అక్షరం * pch_Render_Model_మార్గం, నిర్మాణం HmdMatrix34_t * pTransform, నిర్మాణం Compositor_StageRenderSettings * pRenderSettings, uint32_t n_కొలత_యొక్క_Render_Settings);
	శూన్య (OPENVR_FNTABLE_CALLTYPE *ClearStageOverride)();
	bool (OPENVR_FNTABLE_CALLTYPE *GetCompositorBenchmarkResults)(నిర్మాణం Compositor_BenchmarkResults * pBenchmarkResults, uint32_t n_కొలత_యొక్క_Benchmark_Results);
	EVRCompositorError (OPENVR_FNTABLE_CALLTYPE *Get_చివరి_Pose_Prediction_IDs)(uint32_t * pRenderPosePredictionID, uint32_t * pGamePosePredictionID);
	EVRCompositorError (OPENVR_FNTABLE_CALLTYPE *Get_Poses_For_చట్రం)(uint32_t unPosePredictionID, నిర్మాణం TrackedDevicePose_t * pPoseArray, uint32_t un_Pose_Array_లెక్క);
};

నిర్మాణం VR_IVROverlay_Fn_పట్టిక
{
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *కనుగొను_Overlay)(అక్షరం * pch_Overlay_కీలకం, VROverlayHandle_t * pOverlayHandle);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *CreateOverlay)(అక్షరం * pch_Overlay_కీలకం, అక్షరం * pchOverlayName, VROverlayHandle_t * pOverlayHandle);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *DestroyOverlay)(VROverlayHandle_t ulOverlayHandle);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *Get_Overlay_కీలకం)(VROverlayHandle_t ulOverlayHandle, అక్షరం * pch_విలువ, uint32_t un_బఫరు_కొలత, EVROverlayError * pError);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetOverlayName)(VROverlayHandle_t ulOverlayHandle, అక్షరం * pch_విలువ, uint32_t un_బఫరు_కొలత, EVROverlayError * pError);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *సమితి_Overlay_Name)(VROverlayHandle_t ulOverlayHandle, అక్షరం * pchName);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *Get_Overlay_Image_దత్తాంశం)(VROverlayHandle_t ulOverlayHandle, శూన్య * pv_బఫరు, uint32_t un_బఫరు_కొలత, uint32_t * pun_వెడల్పు, uint32_t * pun_ఎత్తు);
	అక్షరం * (OPENVR_FNTABLE_CALLTYPE *GetOverlayErrorNameFromEnum)(EVROverlayError error);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *సమితి_Overlay_Rendering_Pid)(VROverlayHandle_t ulOverlayHandle, uint32_t unPID);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetOverlayRenderingPid)(VROverlayHandle_t ulOverlayHandle);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *సమితి_Overlay_Flag)(VROverlayHandle_t ulOverlayHandle, VROverlayFlags eOverlayFlag, bool bEnabled);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayFlag)(VROverlayHandle_t ulOverlayHandle, VROverlayFlags eOverlayFlag, bool * pbEnabled);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayFlags)(VROverlayHandle_t ulOverlayHandle, uint32_t * pFlags);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *సమితి_Overlay_Color)(VROverlayHandle_t ulOverlayHandle, దశాంశం fRed, దశాంశం fGreen, దశాంశం fBlue);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayColor)(VROverlayHandle_t ulOverlayHandle, దశాంశం * pfRed, దశాంశం * pfGreen, దశాంశం * pfBlue);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *సమితి_Overlay_Alpha)(VROverlayHandle_t ulOverlayHandle, దశాంశం fAlpha);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayAlpha)(VROverlayHandle_t ulOverlayHandle, దశాంశం * pfAlpha);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *సమితి_Overlay_Texel_Aspect)(VROverlayHandle_t ulOverlayHandle, దశాంశం fTexelAspect);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayTexelAspect)(VROverlayHandle_t ulOverlayHandle, దశాంశం * pfTexelAspect);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *సమితి_Overlay_క్రమీకరించు_క్రమం)(VROverlayHandle_t ulOverlayHandle, uint32_t un_క్రమీకరించు_క్రమం);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *Get_Overlay_క్రమీకరించు_క్రమం)(VROverlayHandle_t ulOverlayHandle, uint32_t * pun_క్రమీకరించు_క్రమం);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *సమితి_Overlay_వెడల్పు_లోపల_Meters)(VROverlayHandle_t ulOverlayHandle, దశాంశం f_వెడల్పు_లోపల_Meters);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *Get_Overlay_వెడల్పు_లోపల_Meters)(VROverlayHandle_t ulOverlayHandle, దశాంశం * pf_వెడల్పు_లోపల_Meters);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *సమితి_Overlay_Curvature)(VROverlayHandle_t ulOverlayHandle, దశాంశం fCurvature);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayCurvature)(VROverlayHandle_t ulOverlayHandle, దశాంశం * pfCurvature);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *సమితి_Overlay_Pre_వక్రం_Pitch)(VROverlayHandle_t ulOverlayHandle, దశాంశం fRadians);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *Get_Overlay_Pre_వక్రం_Pitch)(VROverlayHandle_t ulOverlayHandle, దశాంశం * pfRadians);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *సమితి_Overlay_Texture_Color_Space)(VROverlayHandle_t ulOverlayHandle, EColorSpace eTextureColorSpace);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayTextureColorSpace)(VROverlayHandle_t ulOverlayHandle, EColorSpace * peTextureColorSpace);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *సమితి_Overlay_Texture_Bounds)(VROverlayHandle_t ulOverlayHandle, నిర్మాణం VRTextureBounds_t * pOverlayTextureBounds);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayTextureBounds)(VROverlayHandle_t ulOverlayHandle, నిర్మాణం VRTextureBounds_t * pOverlayTextureBounds);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayTransformType)(VROverlayHandle_t ulOverlayHandle, VROverlayTransformType * peTransformType);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *సమితి_Overlay_Transform_Absolute)(VROverlayHandle_t ulOverlayHandle, ETrackingUniverseOrigin eTrackingOrigin, నిర్మాణం HmdMatrix34_t * pmat_Tracking_Origin_గమ్యం_Overlay_Transform);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayTransformAbsolute)(VROverlayHandle_t ulOverlayHandle, ETrackingUniverseOrigin * peTrackingOrigin, నిర్మాణం HmdMatrix34_t * pmat_Tracking_Origin_గమ్యం_Overlay_Transform);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *సమితి_Overlay_Transform_Tracked_Device_Relative)(VROverlayHandle_t ulOverlayHandle, Tracked_Device_సూచీ_t unTrackedDevice, నిర్మాణం HmdMatrix34_t * pmat_Tracked_Device_గమ్యం_Overlay_Transform);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayTransformTrackedDeviceRelative)(VROverlayHandle_t ulOverlayHandle, Tracked_Device_సూచీ_t * punTrackedDevice, నిర్మాణం HmdMatrix34_t * pmat_Tracked_Device_గమ్యం_Overlay_Transform);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *సమితి_Overlay_Transform_Tracked_Device_Component)(VROverlayHandle_t ulOverlayHandle, Tracked_Device_సూచీ_t un_Device_సూచీ, అక్షరం * pchComponentName);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayTransformTrackedDeviceComponent)(VROverlayHandle_t ulOverlayHandle, Tracked_Device_సూచీ_t * pun_Device_సూచీ, అక్షరం * pchComponentName, uint32_t un_Component_Name_కొలత);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayTransformOverlayRelative)(VROverlayHandle_t ulOverlayHandle, VROverlayHandle_t * ul_Overlay_Handle_మాతృ, నిర్మాణం HmdMatrix34_t * pmat_మాతృ_Overlay_గమ్యం_Overlay_Transform);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *సమితి_Overlay_Transform_Overlay_Relative)(VROverlayHandle_t ulOverlayHandle, VROverlayHandle_t ul_Overlay_Handle_మాతృ, నిర్మాణం HmdMatrix34_t * pmat_మాతృ_Overlay_గమ్యం_Overlay_Transform);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *సమితి_Overlay_Transform_Cursor)(VROverlayHandle_t ulCursorOverlayHandle, నిర్మాణం HmdVector2_t * pvHotspot);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayTransformCursor)(VROverlayHandle_t ulOverlayHandle, నిర్మాణం HmdVector2_t * pvHotspot);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *సమితి_Overlay_Transform_Projection)(VROverlayHandle_t ulOverlayHandle, ETrackingUniverseOrigin eTrackingOrigin, నిర్మాణం HmdMatrix34_t * pmat_Tracking_Origin_గమ్యం_Overlay_Transform, నిర్మాణం VROverlayProjection_t * pProjection, EVREye eEye);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *ShowOverlay)(VROverlayHandle_t ulOverlayHandle);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *HideOverlay)(VROverlayHandle_t ulOverlayHandle);
	bool (OPENVR_FNTABLE_CALLTYPE *IsOverlayVisible)(VROverlayHandle_t ulOverlayHandle);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetTransformForOverlayCoordinates)(VROverlayHandle_t ulOverlayHandle, ETrackingUniverseOrigin eTrackingOrigin, నిర్మాణం HmdVector2_t coordinates_లోపల_Overlay, నిర్మాణం HmdMatrix34_t * pmatTransform);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *Wait_చట్రం_Sync)(uint32_t nTimeoutMs);
	bool (OPENVR_FNTABLE_CALLTYPE *Poll_తదుపరి_Overlay_Event)(VROverlayHandle_t ulOverlayHandle, నిర్మాణం VREvent_t * pEvent, uint32_t uncbVREvent);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *Get_Overlay_ఆదానం_పద్ధతి)(VROverlayHandle_t ulOverlayHandle, VROverlay_ఆదానం_పద్ధతి * pe_ఆదానం_పద్ధతి);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *సమితి_Overlay_ఆదానం_పద్ధతి)(VROverlayHandle_t ulOverlayHandle, VROverlay_ఆదానం_పద్ధతి e_ఆదానం_పద్ధతి);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayMouseScale)(VROverlayHandle_t ulOverlayHandle, నిర్మాణం HmdVector2_t * pvecMouseScale);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *సమితి_Overlay_Mouse_Scale)(VROverlayHandle_t ulOverlayHandle, నిర్మాణం HmdVector2_t * pvecMouseScale);
	bool (OPENVR_FNTABLE_CALLTYPE *ComputeOverlayIntersection)(VROverlayHandle_t ulOverlayHandle, నిర్మాణం VROverlayIntersectionParams_t * pParams, నిర్మాణం VROverlayIntersectionResults_t * pResults);
	bool (OPENVR_FNTABLE_CALLTYPE *Is_Hover_లక్ష్యం_Overlay)(VROverlayHandle_t ulOverlayHandle);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *సమితి_Overlay_Intersection_ముసుగు)(VROverlayHandle_t ulOverlayHandle, నిర్మాణం VROverlay_Intersection_ముసుగు_Primitive_t * p_ముసుగు_Primitives, uint32_t un_అంకె_ముసుగు_Primitives, uint32_t un_Primitive_కొలత);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *TriggerLaserMouseHapticVibration)(VROverlayHandle_t ulOverlayHandle, దశాంశం fDurationSeconds, దశాంశం fFrequency, దశాంశం fAmplitude);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *సమితి_Overlay_Cursor)(VROverlayHandle_t ulOverlayHandle, VROverlayHandle_t ulCursorHandle);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *సమితి_Overlay_Cursor_Position_Override)(VROverlayHandle_t ulOverlayHandle, నిర్మాణం HmdVector2_t * pvCursor);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *ClearOverlayCursorPositionOverride)(VROverlayHandle_t ulOverlayHandle);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *సమితి_Overlay_Texture)(VROverlayHandle_t ulOverlayHandle, నిర్మాణం Texture_t * pTexture);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *ClearOverlayTexture)(VROverlayHandle_t ulOverlayHandle);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *సమితి_Overlay_Raw)(VROverlayHandle_t ulOverlayHandle, శూన్య * pv_బఫరు, uint32_t un_వెడల్పు, uint32_t un_ఎత్తు, uint32_t un_బైట్లు_చొప్పున_Pixel);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *సమితి_Overlay_From_File)(VROverlayHandle_t ulOverlayHandle, అక్షరం * pch_File_మార్గం);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayTexture)(VROverlayHandle_t ulOverlayHandle, శూన్య ** pNativeTextureHandle, శూన్య * pNativeTextureRef, uint32_t * p_వెడల్పు, uint32_t * p_ఎత్తు, uint32_t * pNativeFormat, ETextureType * pAPIType, EColorSpace * pColorSpace, నిర్మాణం VRTextureBounds_t * pTextureBounds);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *ReleaseNativeOverlayHandle)(VROverlayHandle_t ulOverlayHandle, శూన్య * pNativeTextureHandle);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *Get_Overlay_Texture_కొలత)(VROverlayHandle_t ulOverlayHandle, uint32_t * p_వెడల్పు, uint32_t * p_ఎత్తు);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *CreateDashboardOverlay)(అక్షరం * pch_Overlay_కీలకం, అక్షరం * pchOverlayFriendlyName, VROverlayHandle_t * pMainHandle, VROverlayHandle_t * pThumbnailHandle);
	bool (OPENVR_FNTABLE_CALLTYPE *IsDashboardVisible)();
	bool (OPENVR_FNTABLE_CALLTYPE *Is_చురుకైన_Dashboard_Overlay)(VROverlayHandle_t ulOverlayHandle);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *సమితి_Dashboard_Overlay_Scene_Process)(VROverlayHandle_t ulOverlayHandle, uint32_t unProcessId);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetDashboardOverlaySceneProcess)(VROverlayHandle_t ulOverlayHandle, uint32_t * punProcessId);
	శూన్య (OPENVR_FNTABLE_CALLTYPE *ShowDashboard)(అక్షరం * pch_Overlay_గమ్యం_Show);
	Tracked_Device_సూచీ_t (OPENVR_FNTABLE_CALLTYPE *GetPrimaryDashboardDevice)();
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *ShowKeyboard)(EGamepad_పాఠ్యం_ఆదానం_బహుళకం e_ఆదానం_బహుళకం, EGamepad_పాఠ్యం_ఆదానం_పంక్తి_బహుళకం e_పంక్తి_ఆదానం_బహుళకం, uint32_t unFlags, అక్షరం * pchDescription, uint32_t unCharMax, అక్షరం * pch_Existing_పాఠ్యం, uint64_t u_User_విలువ);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *ShowKeyboardForOverlay)(VROverlayHandle_t ulOverlayHandle, EGamepad_పాఠ్యం_ఆదానం_బహుళకం e_ఆదానం_బహుళకం, EGamepad_పాఠ్యం_ఆదానం_పంక్తి_బహుళకం e_పంక్తి_ఆదానం_బహుళకం, uint32_t unFlags, అక్షరం * pchDescription, uint32_t unCharMax, అక్షరం * pch_Existing_పాఠ్యం, uint64_t u_User_విలువ);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *Get_Keyboard_పాఠ్యం)(అక్షరం * pch_పాఠ్యం, uint32_t cch_పాఠ్యం);
	శూన్య (OPENVR_FNTABLE_CALLTYPE *HideKeyboard)();
	శూన్య (OPENVR_FNTABLE_CALLTYPE *సమితి_Keyboard_Transform_Absolute)(ETrackingUniverseOrigin eTrackingOrigin, నిర్మాణం HmdMatrix34_t * pmat_Tracking_Origin_గమ్యం_Keyboard_Transform);
	శూన్య (OPENVR_FNTABLE_CALLTYPE *సమితి_Keyboard_Position_For_Overlay)(VROverlayHandle_t ulOverlayHandle, నిర్మాణం HmdRect2_t avoidRect);
	VRMessageOverlayResponse (OPENVR_FNTABLE_CALLTYPE *Show_సందేశం_Overlay)(అక్షరం * pch_పాఠ్యం, అక్షరం * pchCaption, అక్షరం * pch_Button0_పాఠ్యం, అక్షరం * pch_Button1_పాఠ్యం, అక్షరం * pch_Button2_పాఠ్యం, అక్షరం * pch_Button3_పాఠ్యం);
	శూన్య (OPENVR_FNTABLE_CALLTYPE *Close_సందేశం_Overlay)();
};

నిర్మాణం VR_IVROverlay_View_Fn_పట్టిక
{
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *AcquireOverlayView)(VROverlayHandle_t ulOverlayHandle, నిర్మాణం VRNativeDevice_t * pNativeDevice, నిర్మాణం VROverlayView_t * pOverlayView, uint32_t un_Overlay_View_కొలత);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *ReleaseOverlayView)(నిర్మాణం VROverlayView_t * pOverlayView);
	శూన్య (OPENVR_FNTABLE_CALLTYPE *PostOverlayEvent)(VROverlayHandle_t ulOverlayHandle, నిర్మాణం VREvent_t * pvrEvent);
	bool (OPENVR_FNTABLE_CALLTYPE *IsViewingPermitted)(VROverlayHandle_t ulOverlayHandle);
};

నిర్మాణం VR_IVRHeadset_View_Fn_పట్టిక
{
	శూన్య (OPENVR_FNTABLE_CALLTYPE *సమితి_Headset_View_కొలత)(uint32_t n_వెడల్పు, uint32_t n_ఎత్తు);
	శూన్య (OPENVR_FNTABLE_CALLTYPE *Get_Headset_View_కొలత)(uint32_t * pn_వెడల్పు, uint32_t * pn_ఎత్తు);
	శూన్య (OPENVR_FNTABLE_CALLTYPE *సమితి_Headset_View_బహుళకం)(Headset_View_బహుళకం_t e_Headset_View_బహుళకం);
	Headset_View_బహుళకం_t (OPENVR_FNTABLE_CALLTYPE *Get_Headset_View_బహుళకం)();
	శూన్య (OPENVR_FNTABLE_CALLTYPE *సమితి_Headset_View_Cropped)(bool bCropped);
	bool (OPENVR_FNTABLE_CALLTYPE *GetHeadsetViewCropped)();
	దశాంశం (OPENVR_FNTABLE_CALLTYPE *Get_Headset_View_Aspect_నిష్పత్తి)();
	శూన్య (OPENVR_FNTABLE_CALLTYPE *సమితి_Headset_View_Blend_Range)(దశాంశం fl_ప్రారంభం_Pct, దశాంశం fl_చివర_Pct);
	శూన్య (OPENVR_FNTABLE_CALLTYPE *GetHeadsetViewBlendRange)(దశాంశం * p_ప్రారంభం_Pct, దశాంశం * p_చివర_Pct);
};

నిర్మాణం VR_IVRRender_Models_Fn_పట్టిక
{
	EVRRenderModelError (OPENVR_FNTABLE_CALLTYPE *ఎక్కించు_Render_Model_Async)(అక్షరం * pchRenderModelName, నిర్మాణం RenderModel_t ** ppRenderModel);
	శూన్య (OPENVR_FNTABLE_CALLTYPE *FreeRenderModel)(నిర్మాణం RenderModel_t * pRenderModel);
	EVRRenderModelError (OPENVR_FNTABLE_CALLTYPE *ఎక్కించు_Texture_Async)(TextureID_t textureId, నిర్మాణం RenderModel_TextureMap_t ** ppTexture);
	శూన్య (OPENVR_FNTABLE_CALLTYPE *FreeTexture)(నిర్మాణం RenderModel_TextureMap_t * pTexture);
	EVRRenderModelError (OPENVR_FNTABLE_CALLTYPE *ఎక్కించు_Texture_D3_D11_Async)(TextureID_t textureId, శూన్య * pD3D11Device, శూన్య ** ppD3D11Texture2D);
	EVRRenderModelError (OPENVR_FNTABLE_CALLTYPE *ఎక్కించు_Into_Texture_D3_D11_Async)(TextureID_t textureId, శూన్య * pDstTexture);
	శూన్య (OPENVR_FNTABLE_CALLTYPE *FreeTextureD3D11)(శూన్య * pD3D11Texture2D);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetRenderModelName)(uint32_t un_Render_Model_సూచీ, అక్షరం * pchRenderModelName, uint32_t unRenderModelNameLen);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *Get_Render_Model_లెక్క)();
	uint32_t (OPENVR_FNTABLE_CALLTYPE *Get_Component_లెక్క)(అక్షరం * pchRenderModelName);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetComponentName)(అక్షరం * pchRenderModelName, uint32_t un_Component_సూచీ, అక్షరం * pchComponentName, uint32_t unComponentNameLen);
	uint64_t (OPENVR_FNTABLE_CALLTYPE *Get_Component_Button_ముసుగు)(అక్షరం * pchRenderModelName, అక్షరం * pchComponentName);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetComponentRenderModelName)(అక్షరం * pchRenderModelName, అక్షరం * pchComponentName, అక్షరం * pchComponentRenderModelName, uint32_t unComponentRenderModelNameLen);
	bool (OPENVR_FNTABLE_CALLTYPE *Get_Component_State_For_Device_మార్గం)(అక్షరం * pchRenderModelName, అక్షరం * pchComponentName, VRInput_విలువ_Handle_t device_మార్గం, Render_Model_Controller_బహుళకం_State_t * pState, RenderModel_ComponentState_t * pComponentState);
	bool (OPENVR_FNTABLE_CALLTYPE *GetComponentState)(అక్షరం * pchRenderModelName, అక్షరం * pchComponentName, VRControllerState_t * pControllerState, నిర్మాణం Render_Model_Controller_బహుళకం_State_t * pState, నిర్మాణం RenderModel_ComponentState_t * pComponentState);
	bool (OPENVR_FNTABLE_CALLTYPE *RenderModelHasComponent)(అక్షరం * pchRenderModelName, అక్షరం * pchComponentName);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetRenderModelThumbnailURL)(అక్షరం * pchRenderModelName, అక్షరం * pchThumbnailURL, uint32_t unThumbnailURLLen, EVRRenderModelError * peError);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *Get_Render_Model_Original_మార్గం)(అక్షరం * pchRenderModelName, అక్షరం * pch_Original_మార్గం, uint32_t un_Original_మార్గం_Len, EVRRenderModelError * peError);
	అక్షరం * (OPENVR_FNTABLE_CALLTYPE *GetRenderModelErrorNameFromEnum)(EVRRenderModelError error);
};

నిర్మాణం VR_IVRNotifications_Fn_పట్టిక
{
	EVRNotificationError (OPENVR_FNTABLE_CALLTYPE *CreateNotification)(VROverlayHandle_t ulOverlayHandle, uint64_t ul_User_విలువ, EVRNotificationType type, అక్షరం * pch_పాఠ్యం, EVRNotificationStyle style, నిర్మాణం NotificationBitmap_t * pImage, VRNotificationId * pNotificationId);
	EVRNotificationError (OPENVR_FNTABLE_CALLTYPE *RemoveNotification)(VRNotificationId notificationId);
};

నిర్మాణం VR_IVRSettings_Fn_పట్టిక
{
	అక్షరం * (OPENVR_FNTABLE_CALLTYPE *GetSettingsErrorNameFromEnum)(EVRSettingsError eError);
	శూన్య (OPENVR_FNTABLE_CALLTYPE *సమితి_Bool)(అక్షరం * pchSection, అక్షరం * pch_Settings_కీలకం, bool b_విలువ, EVRSettingsError * peError);
	శూన్య (OPENVR_FNTABLE_CALLTYPE *సమితి_Int32)(అక్షరం * pchSection, అక్షరం * pch_Settings_కీలకం, int32_t n_విలువ, EVRSettingsError * peError);
	శూన్య (OPENVR_FNTABLE_CALLTYPE *సమితి_Float)(అక్షరం * pchSection, అక్షరం * pch_Settings_కీలకం, దశాంశం fl_విలువ, EVRSettingsError * peError);
	శూన్య (OPENVR_FNTABLE_CALLTYPE *సమితి_String)(అక్షరం * pchSection, అక్షరం * pch_Settings_కీలకం, అక్షరం * pch_విలువ, EVRSettingsError * peError);
	bool (OPENVR_FNTABLE_CALLTYPE *GetBool)(అక్షరం * pchSection, అక్షరం * pch_Settings_కీలకం, EVRSettingsError * peError);
	int32_t (OPENVR_FNTABLE_CALLTYPE *GetInt32)(అక్షరం * pchSection, అక్షరం * pch_Settings_కీలకం, EVRSettingsError * peError);
	దశాంశం (OPENVR_FNTABLE_CALLTYPE *GetFloat)(అక్షరం * pchSection, అక్షరం * pch_Settings_కీలకం, EVRSettingsError * peError);
	శూన్య (OPENVR_FNTABLE_CALLTYPE *GetString)(అక్షరం * pchSection, అక్షరం * pch_Settings_కీలకం, అక్షరం * pch_విలువ, uint32_t un_విలువ_Len, EVRSettingsError * peError);
	శూన్య (OPENVR_FNTABLE_CALLTYPE *RemoveSection)(అక్షరం * pchSection, EVRSettingsError * peError);
	శూన్య (OPENVR_FNTABLE_CALLTYPE *Remove_కీలకం_లోపల_Section)(అక్షరం * pchSection, అక్షరం * pch_Settings_కీలకం, EVRSettingsError * peError);
};

నిర్మాణం VR_IVRScreenshots_Fn_పట్టిక
{
	EVRScreenshotError (OPENVR_FNTABLE_CALLTYPE *RequestScreenshot)(ScreenshotHandle_t * p_బహిర్గతం_Screenshot_Handle, EVRScreenshotType type, అక్షరం * pchPreviewFilename, అక్షరం * pchVRFilename);
	EVRScreenshotError (OPENVR_FNTABLE_CALLTYPE *HookScreenshot)(EVRScreenshotType * pSupportedTypes, పూర్ణాంకం అంకె_Types);
	EVRScreenshotType (OPENVR_FNTABLE_CALLTYPE *GetScreenshotPropertyType)(ScreenshotHandle_t screenshotHandle, EVRScreenshotError * pError);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetScreenshotPropertyFilename)(ScreenshotHandle_t screenshotHandle, EVRScreenshotPropertyFilenames filenameType, అక్షరం * pchFilename, uint32_t cchFilename, EVRScreenshotError * pError);
	EVRScreenshotError (OPENVR_FNTABLE_CALLTYPE *Update_Screenshot_పురోగతి)(ScreenshotHandle_t screenshotHandle, దశాంశం fl_పురోగతి);
	EVRScreenshotError (OPENVR_FNTABLE_CALLTYPE *TakeStereoScreenshot)(ScreenshotHandle_t * p_బహిర్గతం_Screenshot_Handle, అక్షరం * pchPreviewFilename, అక్షరం * pchVRFilename);
	EVRScreenshotError (OPENVR_FNTABLE_CALLTYPE *SubmitScreenshot)(ScreenshotHandle_t screenshotHandle, EVRScreenshotType type, అక్షరం * pch_ఆధారం_Preview_Filename, అక్షరం * pch_ఆధారం_VRFilename);
};

నిర్మాణం VR_IVRResources_Fn_పట్టిక
{
	uint32_t (OPENVR_FNTABLE_CALLTYPE *ఎక్కించు_Shared_Resource)(అక్షరం * pchResourceName, అక్షరం * pch_బఫరు, uint32_t un_బఫరు_Len);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *Get_Resource_నిండిన_మార్గం)(అక్షరం * pchResourceName, అక్షరం * pchResourceTypeDirectory, అక్షరం * pch_మార్గం_బఫరు, uint32_t un_బఫరు_Len);
};

నిర్మాణం VR_IVRDriver_Manager_Fn_పట్టిక
{
	uint32_t (OPENVR_FNTABLE_CALLTYPE *Get_Driver_లెక్క)();
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetDriverName)(DriverId_t nDriver, అక్షరం * pch_విలువ, uint32_t un_బఫరు_కొలత);
	DriverHandle_t (OPENVR_FNTABLE_CALLTYPE *GetDriverHandle)(అక్షరం * pchDriverName);
	bool (OPENVR_FNTABLE_CALLTYPE *IsEnabled)(DriverId_t nDriver);
};

నిర్మాణం VR_IVRInput_Fn_పట్టిక
{
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *సమితి_Action_Manifest_మార్గం)(అక్షరం * pch_Action_Manifest_మార్గం);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *Get_Action_సమితి_Handle)(అక్షరం * pch_Action_సమితి_Name, VRAction_సమితి_Handle_t * pHandle);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetActionHandle)(అక్షరం * pchActionName, VRActionHandle_t * pHandle);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *Get_ఆదానం_ఆధారం_Handle)(అక్షరం * pch_ఆదానం_ఆధారం_మార్గం, VRInput_విలువ_Handle_t * pHandle);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *UpdateActionState)(నిర్మాణం VRActive_Action_సమితి_t * pSets, uint32_t un_కొలత_యొక్క_VRSelected_Action_సమితి_t, uint32_t un_సమితి_లెక్క);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *Get_Digital_Action_దత్తాంశం)(VRActionHandle_t action, నిర్మాణం ఆదానం_Digital_Action_దత్తాంశం_t * p_Action_దత్తాంశం, uint32_t un_Action_దత్తాంశం_కొలత, VRInput_విలువ_Handle_t ul_Restrict_గమ్యం_Device);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *Get_Analog_Action_దత్తాంశం)(VRActionHandle_t action, నిర్మాణం ఆదానం_Analog_Action_దత్తాంశం_t * p_Action_దత్తాంశం, uint32_t un_Action_దత్తాంశం_కొలత, VRInput_విలువ_Handle_t ul_Restrict_గమ్యం_Device);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *Get_Pose_Action_దత్తాంశం_Relative_గమ్యం_Now)(VRActionHandle_t action, ETrackingUniverseOrigin eOrigin, దశాంశం fPredictedSecondsFromNow, నిర్మాణం ఆదానం_Pose_Action_దత్తాంశం_t * p_Action_దత్తాంశం, uint32_t un_Action_దత్తాంశం_కొలత, VRInput_విలువ_Handle_t ul_Restrict_గమ్యం_Device);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *Get_Pose_Action_దత్తాంశం_For_తదుపరి_చట్రం)(VRActionHandle_t action, ETrackingUniverseOrigin eOrigin, నిర్మాణం ఆదానం_Pose_Action_దత్తాంశం_t * p_Action_దత్తాంశం, uint32_t un_Action_దత్తాంశం_కొలత, VRInput_విలువ_Handle_t ul_Restrict_గమ్యం_Device);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *Get_Skeletal_Action_దత్తాంశం)(VRActionHandle_t action, నిర్మాణం ఆదానం_Skeletal_Action_దత్తాంశం_t * p_Action_దత్తాంశం, uint32_t un_Action_దత్తాంశం_కొలత);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetDominantHand)(ETrackedControllerRole * peDominantHand);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *సమితి_Dominant_Hand)(ETrackedControllerRole eDominantHand);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *Get_Bone_లెక్క)(VRActionHandle_t action, uint32_t * p_Bone_లెక్క);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetBoneHierarchy)(VRActionHandle_t action, Bone_సూచీ_t * p_మాతృ_Indices, uint32_t un_సూచీ_Aray_లెక్క);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetBoneName)(VRActionHandle_t action, Bone_సూచీ_t n_Bone_సూచీ, అక్షరం * pchBoneName, uint32_t un_Name_బఫరు_కొలత);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetSkeletalReferenceTransforms)(VRActionHandle_t action, EVRSkeletalTransformSpace eTransformSpace, EVRSkeletalReferencePose eReferencePose, నిర్మాణం VRBoneTransform_t * pTransformArray, uint32_t un_Transform_Array_లెక్క);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetSkeletalTrackingLevel)(VRActionHandle_t action, EVRSkeletalTrackingLevel * pSkeletalTrackingLevel);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *Get_Skeletal_Bone_దత్తాంశం)(VRActionHandle_t action, EVRSkeletalTransformSpace eTransformSpace, EVRSkeletalMotionRange eMotionRange, నిర్మాణం VRBoneTransform_t * pTransformArray, uint32_t un_Transform_Array_లెక్క);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *Get_Skeletal_Summary_దత్తాంశం)(VRActionHandle_t action, EVRSummaryType eSummaryType, నిర్మాణం VRSkeletal_Summary_దత్తాంశం_t * p_Skeletal_Summary_దత్తాంశం);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *Get_Skeletal_Bone_దత్తాంశం_Compressed)(VRActionHandle_t action, EVRSkeletalMotionRange eMotionRange, శూన్య * pv_Compressed_దత్తాంశం, uint32_t un_Compressed_కొలత, uint32_t * pun_Required_Compressed_కొలత);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *Decompress_Skeletal_Bone_దత్తాంశం)(శూన్య * pv_Compressed_బఫరు, uint32_t un_Compressed_బఫరు_కొలత, EVRSkeletalTransformSpace eTransformSpace, నిర్మాణం VRBoneTransform_t * pTransformArray, uint32_t un_Transform_Array_లెక్క);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *TriggerHapticVibrationAction)(VRActionHandle_t action, దశాంశం f_ప్రారంభం_Seconds_From_Now, దశాంశం fDurationSeconds, దశాంశం fFrequency, దశాంశం fAmplitude, VRInput_విలువ_Handle_t ul_Restrict_గమ్యం_Device);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetActionOrigins)(VRAction_సమితి_Handle_t action_సమితి_Handle, VRActionHandle_t digitalActionHandle, VRInput_విలువ_Handle_t * origins_బహిర్గతం, uint32_t origin_బహిర్గతం_లెక్క);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetOriginLocalizedName)(VRInput_విలువ_Handle_t origin, అక్షరం * pchNameArray, uint32_t un_Name_Array_కొలత, int32_t un_String_Sections_గమ్యం_Include);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetOriginTrackedDeviceInfo)(VRInput_విలువ_Handle_t origin, నిర్మాణం ఆదానం_Origin_Info_t * pOriginInfo, uint32_t un_Origin_Info_కొలత);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetActionBindingInfo)(VRActionHandle_t action, నిర్మాణం ఆదానం_Binding_Info_t * pOriginInfo, uint32_t un_Binding_Info_కొలత, uint32_t un_Binding_Info_లెక్క, uint32_t * pun_Returned_Binding_Info_లెక్క);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *ShowActionOrigins)(VRAction_సమితి_Handle_t action_సమితి_Handle, VRActionHandle_t ulActionHandle);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *Show_Bindings_For_Action_సమితి)(నిర్మాణం VRActive_Action_సమితి_t * pSets, uint32_t un_కొలత_యొక్క_VRSelected_Action_సమితి_t, uint32_t un_సమితి_లెక్క, VRInput_విలువ_Handle_t origin_గమ్యం_Highlight);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetComponentStateForBinding)(అక్షరం * pchRenderModelName, అక్షరం * pchComponentName, నిర్మాణం ఆదానం_Binding_Info_t * pOriginInfo, uint32_t un_Binding_Info_కొలత, uint32_t un_Binding_Info_లెక్క, RenderModel_ComponentState_t * pComponentState);
	bool (OPENVR_FNTABLE_CALLTYPE *Is_Using_Legacy_ఆదానం)();
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *OpenBindingUI)(అక్షరం * pch_App_కీలకం, VRAction_సమితి_Handle_t ul_Action_సమితి_Handle, VRInput_విలువ_Handle_t ulDeviceHandle, bool bShowOnDesktop);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetBindingVariant)(VRInput_విలువ_Handle_t ul_Device_మార్గం, అక్షరం * pchVariantArray, uint32_t un_Variant_Array_కొలత);
};

నిర్మాణం VR_IVRIOBuffer_Fn_పట్టిక
{
	EIOBufferError (OPENVR_FNTABLE_CALLTYPE *Open)(అక్షరం * pch_మార్గం, EIOBuffer_బహుళకం బహుళకం, uint32_t un_Element_కొలత, uint32_t unElements, IOBufferHandle_t * pul_బఫరు);
	EIOBufferError (OPENVR_FNTABLE_CALLTYPE *Close)(IOBufferHandle_t ul_బఫరు);
	EIOBufferError (OPENVR_FNTABLE_CALLTYPE *Read)(IOBufferHandle_t ul_బఫరు, శూన్య * pDst, uint32_t un_బైట్లు, uint32_t * punRead);
	EIOBufferError (OPENVR_FNTABLE_CALLTYPE *Write)(IOBufferHandle_t ul_బఫరు, శూన్య * pSrc, uint32_t un_బైట్లు);
	PropertyContainerHandle_t (OPENVR_FNTABLE_CALLTYPE *PropertyContainer)(IOBufferHandle_t ul_బఫరు);
	bool (OPENVR_FNTABLE_CALLTYPE *HasReaders)(IOBufferHandle_t ul_బఫరు);
};

నిర్మాణం VR_IVRSpatial_Anchors_Fn_పట్టిక
{
	EVRSpatialAnchorError (OPENVR_FNTABLE_CALLTYPE *CreateSpatialAnchorFromDescriptor)(అక్షరం * pchDescriptor, SpatialAnchorHandle_t * p_Handle_బహిర్గతం);
	EVRSpatialAnchorError (OPENVR_FNTABLE_CALLTYPE *CreateSpatialAnchorFromPose)(Tracked_Device_సూచీ_t un_Device_సూచీ, ETrackingUniverseOrigin eOrigin, నిర్మాణం SpatialAnchorPose_t * pPose, SpatialAnchorHandle_t * p_Handle_బహిర్గతం);
	EVRSpatialAnchorError (OPENVR_FNTABLE_CALLTYPE *GetSpatialAnchorPose)(SpatialAnchorHandle_t unHandle, ETrackingUniverseOrigin eOrigin, నిర్మాణం SpatialAnchorPose_t * p_Pose_బహిర్గతం);
	EVRSpatialAnchorError (OPENVR_FNTABLE_CALLTYPE *GetSpatialAnchorDescriptor)(SpatialAnchorHandle_t unHandle, అక్షరం * pch_Descriptor_బహిర్గతం, uint32_t * pun_Descriptor_బఫరు_Len_లోపల_బహిర్గతం);
};

నిర్మాణం VR_IVRDebug_Fn_పట్టిక
{
	EVRDebugError (OPENVR_FNTABLE_CALLTYPE *EmitVrProfilerEvent)(అక్షరం * pch_సందేశం);
	EVRDebugError (OPENVR_FNTABLE_CALLTYPE *BeginVrProfilerEvent)(VrProfilerEventHandle_t * p_Handle_బహిర్గతం);
	EVRDebugError (OPENVR_FNTABLE_CALLTYPE *ముగింపు_Vr_Profiler_Event)(VrProfilerEventHandle_t hHandle, అక్షరం * pch_సందేశం);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *DriverDebugRequest)(Tracked_Device_సూచీ_t un_Device_సూచీ, అక్షరం * pchRequest, అక్షరం * pch_Response_బఫరు, uint32_t un_Response_బఫరు_కొలత);
};

నిర్మాణం VR_IVRProperties_Fn_పట్టిక
{
	ETrackedPropertyError (OPENVR_FNTABLE_CALLTYPE *ReadPropertyBatch)(PropertyContainerHandle_t ulContainerHandle, నిర్మాణం PropertyRead_t * pBatch, uint32_t un_Batch_నమోదు_లెక్క);
	ETrackedPropertyError (OPENVR_FNTABLE_CALLTYPE *WritePropertyBatch)(PropertyContainerHandle_t ulContainerHandle, నిర్మాణం PropertyWrite_t * pBatch, uint32_t un_Batch_నమోదు_లెక్క);
	అక్షరం * (OPENVR_FNTABLE_CALLTYPE *GetPropErrorNameFromEnum)(ETrackedPropertyError error);
	PropertyContainerHandle_t (OPENVR_FNTABLE_CALLTYPE *Tracked_Device_గమ్యం_Property_Container)(Tracked_Device_సూచీ_t nDevice);
};

నిర్మాణం VR_IVRPaths_Fn_పట్టిక
{
	ETrackedPropertyError (OPENVR_FNTABLE_CALLTYPE *Read_మార్గం_Batch)(PropertyContainerHandle_t ul_మూలం_Handle, నిర్మాణం మార్గం_Read_t * pBatch, uint32_t un_Batch_నమోదు_లెక్క);
	ETrackedPropertyError (OPENVR_FNTABLE_CALLTYPE *Write_మార్గం_Batch)(PropertyContainerHandle_t ul_మూలం_Handle, నిర్మాణం మార్గం_Write_t * pBatch, uint32_t un_Batch_నమోదు_లెక్క);
	ETrackedPropertyError (OPENVR_FNTABLE_CALLTYPE *String_గమ్యం_Handle)(మార్గం_Handle_t * pHandle, అక్షరం * pch_మార్గం);
	ETrackedPropertyError (OPENVR_FNTABLE_CALLTYPE *Handle_గమ్యం_String)(మార్గం_Handle_t pHandle, అక్షరం * pch_బఫరు, uint32_t un_బఫరు_కొలత, uint32_t * pun_బఫరు_కొలత_వాడిన);
};

నిర్మాణం VR_IVRBlock_వరుస_Fn_పట్టిక
{
	EBlock_వరుస_Error (OPENVR_FNTABLE_CALLTYPE *Create)(PropertyContainerHandle_t * pul_వరుస_Handle, అక్షరం * pch_మార్గం, uint32_t un_ఖండం_దత్తాంశం_కొలత, uint32_t un_ఖండం_శీర్షిక_కొలత, uint32_t un_ఖండం_లెక్క, uint32_t unFlags);
	EBlock_వరుస_Error (OPENVR_FNTABLE_CALLTYPE *Connect)(PropertyContainerHandle_t * pul_వరుస_Handle, అక్షరం * pch_మార్గం);
	EBlock_వరుస_Error (OPENVR_FNTABLE_CALLTYPE *Destroy)(PropertyContainerHandle_t ul_వరుస_Handle);
	EBlock_వరుస_Error (OPENVR_FNTABLE_CALLTYPE *Acquire_Write_Only_ఖండం)(PropertyContainerHandle_t ul_వరుస_Handle, PropertyContainerHandle_t * pul_ఖండం_Handle, శూన్య ** ppv_బఫరు);
	EBlock_వరుస_Error (OPENVR_FNTABLE_CALLTYPE *Release_Write_Only_ఖండం)(PropertyContainerHandle_t ul_వరుస_Handle, PropertyContainerHandle_t ul_ఖండం_Handle);
	EBlock_వరుస_Error (OPENVR_FNTABLE_CALLTYPE *Wait_And_Acquire_Read_Only_ఖండం)(PropertyContainerHandle_t ul_వరుస_Handle, PropertyContainerHandle_t * pul_ఖండం_Handle, శూన్య ** ppv_బఫరు, EBlock_వరుస_Read_Type eReadType, uint32_t unTimeoutMs);
	EBlock_వరుస_Error (OPENVR_FNTABLE_CALLTYPE *Acquire_Read_Only_ఖండం)(PropertyContainerHandle_t ul_వరుస_Handle, PropertyContainerHandle_t * pul_ఖండం_Handle, శూన్య ** ppv_బఫరు, EBlock_వరుస_Read_Type eReadType);
	EBlock_వరుస_Error (OPENVR_FNTABLE_CALLTYPE *Release_Read_Only_ఖండం)(PropertyContainerHandle_t ul_వరుస_Handle, PropertyContainerHandle_t ul_ఖండం_Handle);
	EBlock_వరుస_Error (OPENVR_FNTABLE_CALLTYPE *వరుస_Has_Reader)(PropertyContainerHandle_t ul_వరుస_Handle, bool * pbHasReaders);
};


#ఒకవేళ 0
// Global entry points
S_API intptr_t VR_Init_అంతర్గత( EVRInitError *peError, EVRApplicationType eType );
S_API శూన్య VR_Shutdown_అంతర్గత();
S_API bool VR_IsHmdPresent();
S_API intptr_t VR_GetGenericInterface( స్థిరరాశి అక్షరం *pch_Interface_సంస్కరణ, EVRInitError *peError );
S_API bool VR_IsRuntimeInstalled();
S_API స్థిరరాశి అక్షరం * VR_Get_VRInit_Error_As_చిహ్నం( EVRInitError error );
S_API స్థిరరాశి అక్షరం * VR_GetVRInitErrorAsEnglishDescription( EVRInitError error );
#అయితే_ముగింపు

#అయితే_ముగింపు // __OPENVR_API_FLAT_H__


