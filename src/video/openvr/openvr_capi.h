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

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ __OPENVR_API_FLAT_H__
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ __OPENVR_API_FLAT_H__
#ਜੇ defined( _WIN32 ) || defined( __clang__ )
#ਹਦਾਇਤ once
#ਜੇ_ਅੰਤ

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __cplusplus
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EXTERN_C ਬਾਹਰੀ "C"
#ਨਹੀਂਤਾਂ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EXTERN_C
#ਜੇ_ਅੰਤ

#ਜੇ defined( _WIN32 )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ OPENVR_FNTABLE_CALLTYPE __stdcall
#ਨਹੀਂਤਾਂ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ OPENVR_FNTABLE_CALLTYPE 
#ਜੇ_ਅੰਤ

// OPENVR API export macro
#ਜੇ defined( _WIN32 ) && !defined( _X360 )
	#ਜੇ defined( OPENVR_API_EXPORTS )
	#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ S_API EXTERN_C __declspec( dllexport )
	#ਜਾਂਜੇ defined( OPENVR_API_NODLL )
	#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ S_API EXTERN_C
	#ਨਹੀਂਤਾਂ
	#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ S_API ਬਾਹਰੀ "C" __declspec( dllimport ) 
	#ਜੇ_ਅੰਤ // OPENVR_API_EXPORTS
#ਜਾਂਜੇ defined( __GNUC__ )
	#ਜੇ defined( OPENVR_API_EXPORTS )
	#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ S_API EXTERN_C __attribute__ ((visibility("default")))
	#ਨਹੀਂਤਾਂ
	#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ S_API EXTERN_C
	#ਜੇ_ਅੰਤ // OPENVR_API_EXPORTS
#ਨਹੀਂਤਾਂ // !WIN32
	#ਜੇ defined( OPENVR_API_EXPORTS )
	#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ S_API EXTERN_C
	#ਨਹੀਂਤਾਂ
	#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ S_API EXTERN_C
	#ਜੇ_ਅੰਤ // OPENVR_API_EXPORTS
#ਜੇ_ਅੰਤ

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ USE_SDL
#ਅਨ੍ਤਰ੍ਭਾਵ <stdint.h>

#ਜੇ defined( __WIN32 )
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਅੱਖਰ bool;
#ਨਹੀਂਤਾਂ
#ਅਨ੍ਤਰ੍ਭਾਵ <stdbool.h>
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ // USE_SDL

// OpenVR Constants

ਸਥਿਰ ਅਚਲ ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ k_nDriverNone = 4294967295;
ਸਥਿਰ ਅਚਲ ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ k_un_Max_Driver_Debug_Response_ਮਾਪ = 32768;
ਸਥਿਰ ਅਚਲ ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ k_un_Tracked_Device_ਸੂਚਕਾਂਕ_Hmd = 0;
ਸਥਿਰ ਅਚਲ ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ k_un_Max_Tracked_Device_ਗਿਣਤੀ = 64;
ਸਥਿਰ ਅਚਲ ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ k_un_Tracked_Device_ਸੂਚਕਾਂਕ_Other = 4294967294;
ਸਥਿਰ ਅਚਲ ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ k_un_Tracked_Device_ਸੂਚਕਾਂਕ_Invalid = 4294967295;
ਸਥਿਰ ਅਚਲ ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ ਲੰਮਾ k_ulInvalidPropertyContainer = 0;
ਸਥਿਰ ਅਚਲ ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ k_un_Invalid_Property_ਟੈਗ = 0;
ਸਥਿਰ ਅਚਲ ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ ਲੰਮਾ k_ulInvalidDriverHandle = 0;
ਸਥਿਰ ਅਚਲ ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ k_un_Float_Property_ਟੈਗ = 1;
ਸਥਿਰ ਅਚਲ ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ k_un_Int32_Property_ਟੈਗ = 2;
ਸਥਿਰ ਅਚਲ ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ k_un_Uint64_Property_ਟੈਗ = 3;
ਸਥਿਰ ਅਚਲ ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ k_un_Bool_Property_ਟੈਗ = 4;
ਸਥਿਰ ਅਚਲ ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ k_un_String_Property_ਟੈਗ = 5;
ਸਥਿਰ ਅਚਲ ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ k_un_Error_Property_ਟੈਗ = 6;
ਸਥਿਰ ਅਚਲ ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ k_un_Double_Property_ਟੈਗ = 7;
ਸਥਿਰ ਅਚਲ ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ k_un_Hmd_Matrix34_Property_ਟੈਗ = 20;
ਸਥਿਰ ਅਚਲ ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ k_un_Hmd_Matrix44_Property_ਟੈਗ = 21;
ਸਥਿਰ ਅਚਲ ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ k_un_Hmd_Vector3_Property_ਟੈਗ = 22;
ਸਥਿਰ ਅਚਲ ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ k_un_Hmd_Vector4_Property_ਟੈਗ = 23;
ਸਥਿਰ ਅਚਲ ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ k_un_Hmd_Vector2_Property_ਟੈਗ = 24;
ਸਥਿਰ ਅਚਲ ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ k_un_Hmd_Quad_Property_ਟੈਗ = 25;
ਸਥਿਰ ਅਚਲ ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ k_un_Hidden_Area_Property_ਟੈਗ = 30;
ਸਥਿਰ ਅਚਲ ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ k_un_ਰਸਤਾ_Handle_Info_ਟੈਗ = 31;
ਸਥਿਰ ਅਚਲ ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ k_un_Action_Property_ਟੈਗ = 32;
ਸਥਿਰ ਅਚਲ ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ k_un_ਨਿਵੇਸ਼_ਮੁੱਲ_Property_ਟੈਗ = 33;
ਸਥਿਰ ਅਚਲ ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ k_un_Wildcard_Property_ਟੈਗ = 34;
ਸਥਿਰ ਅਚਲ ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ k_un_Haptic_Vibration_Property_ਟੈਗ = 35;
ਸਥਿਰ ਅਚਲ ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ k_un_Skeleton_Property_ਟੈਗ = 36;
ਸਥਿਰ ਅਚਲ ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ k_un_Spatial_Anchor_Pose_Property_ਟੈਗ = 40;
ਸਥਿਰ ਅਚਲ ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ k_un_Json_Property_ਟੈਗ = 41;
ਸਥਿਰ ਅਚਲ ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ k_un_ਸਰਗਰਮ_Action_ਸੈੱਟ_Property_ਟੈਗ = 42;
ਸਥਿਰ ਅਚਲ ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ k_un_Open_VRInternal_Reserved_ਸ਼ੁਰੂ = 1000;
ਸਥਿਰ ਅਚਲ ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ k_un_Open_VRInternal_Reserved_ਸਿਰਾ = 10000;
ਸਥਿਰ ਅਚਲ ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ k_un_Max_Property_String_ਮਾਪ = 32768;
ਸਥਿਰ ਅਚਲ ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ ਲੰਮਾ k_ulInvalidActionHandle = 0;
ਸਥਿਰ ਅਚਲ ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ ਲੰਮਾ k_ul_Invalid_Action_ਸੈੱਟ_Handle = 0;
ਸਥਿਰ ਅਚਲ ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ ਲੰਮਾ k_ul_Invalid_ਨਿਵੇਸ਼_ਮੁੱਲ_Handle = 0;
ਸਥਿਰ ਅਚਲ ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ k_un_Controller_State_Axis_ਗਿਣਤੀ = 5;
ਸਥਿਰ ਅਚਲ ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ ਲੰਮਾ k_ulOverlayHandleInvalid = 0;
ਸਥਿਰ ਅਚਲ ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ k_unMaxDistortionFunctionParameters = 8;
ਸਥਿਰ ਅਚਲ ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ k_unScreenshotHandleInvalid = 0;
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * IVRSystem_ਸੰਸਕਰਣ = "IVRSystem_022";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * IVRExtended_Display_ਸੰਸਕਰਣ = "IVRExtendedDisplay_001";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * IVRTracked_Camera_ਸੰਸਕਰਣ = "IVRTrackedCamera_006";
ਸਥਿਰ ਅਚਲ ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ k_un_Max_Application_ਕੁੰਜੀ_ਲੰਮਾਈ = 128;
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_MimeType_HomeApp = "vr/home";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_MimeType_GameTheater = "vr/game_theater";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * IVRApplications_ਸੰਸਕਰਣ = "IVRApplications_007";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * IVRChaperone_ਸੰਸਕਰਣ = "IVRChaperone_004";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * IVRChaperone_ਤਿਆਰੀ_ਸੰਸਕਰਣ = "IVRChaperoneSetup_006";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * IVRCompositor_ਸੰਸਕਰਣ = "IVRCompositor_027";
ਸਥਿਰ ਅਚਲ ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ k_un_VROverlay_Max_ਕੁੰਜੀ_ਲੰਮਾਈ = 128;
ਸਥਿਰ ਅਚਲ ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ k_un_VROverlay_Max_Name_ਲੰਮਾਈ = 128;
ਸਥਿਰ ਅਚਲ ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ k_un_Max_Overlay_ਗਿਣਤੀ = 128;
ਸਥਿਰ ਅਚਲ ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ k_un_Max_Overlay_Intersection_ਨਕਾਬ_Primitives_ਗਿਣਤੀ = 32;
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * IVROverlay_ਸੰਸਕਰਣ = "IVROverlay_026";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * IVROverlay_View_ਸੰਸਕਰਣ = "IVROverlayView_003";
ਸਥਿਰ ਅਚਲ ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ k_un_Headset_View_Max_ਚੌੜਾਈ = 3840;
ਸਥਿਰ ਅਚਲ ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ k_un_Headset_View_Max_ਉਚਾਈ = 2160;
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_Headset_View_Overlay_ਕੁੰਜੀ = "system.HeadsetView";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * IVRHeadset_View_ਸੰਸਕਰਣ = "IVRHeadsetView_001";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_Controller_Component_GDC2015 = "gdc2015";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_Controller_Component_ਅਧਾਰ = "base";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_Controller_Component_Tip = "tip";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_Controller_Component_OpenXR_Aim = "openxr_aim";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_Controller_Component_HandGrip = "handgrip";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_Controller_Component_OpenXR_Grip = "openxr_grip";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_Controller_Component_OpenXR_HandModel = "openxr_handmodel";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_Controller_Component_ਸਥਿਤੀ = "status";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * IVRRender_Models_ਸੰਸਕਰਣ = "IVRRenderModels_006";
ਸਥਿਰ ਅਚਲ ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ k_un_Notification_ਪਾਠ_Max_ਮਾਪ = 256;
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * IVRNotifications_ਸੰਸਕਰਣ = "IVRNotifications_002";
ਸਥਿਰ ਅਚਲ ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ k_un_Max_Settings_ਕੁੰਜੀ_ਲੰਮਾਈ = 128;
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * IVRSettings_ਸੰਸਕਰਣ = "IVRSettings_003";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_SteamVR_Section = "steamvr";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_SteamVR_RequireHmd_String = "requireHmd";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_Steam_VR_Forced_Driver_ਕੁੰਜੀ_String = "forcedDriver";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_Steam_VR_Forced_Hmd_ਕੁੰਜੀ_String = "forcedHmd";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_SteamVR_DisplayDebug_Bool = "displayDebug";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_SteamVR_DebugProcessPipe_String = "debugProcessPipe";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_SteamVR_DisplayDebugX_Int32 = "displayDebugX";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_SteamVR_DisplayDebugY_Int32 = "displayDebugY";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_Steam_VR_Send_System_Button_ਮੰਜ਼ਿਲ_All_Apps_Bool = "sendSystemButtonToAllApps";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_SteamVR_LogLevel_Int32 = "loglevel";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_SteamVR_IPD_Float = "ipd";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_SteamVR_Background_String = "background";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_SteamVR_BackgroundUseDomeProjection_Bool = "backgroundUseDomeProjection";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_Steam_VR_Background_Camera_ਉਚਾਈ_Float = "backgroundCameraHeight";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_SteamVR_BackgroundDomeRadius_Float = "backgroundDomeRadius";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_SteamVR_GridColor_String = "gridColor";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_SteamVR_PlayAreaColor_String = "playAreaColor";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_SteamVR_TrackingLossColor_String = "trackingLossColor";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_SteamVR_ShowStage_Bool = "showStage";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_SteamVR_DrawTrackingReferences_Bool = "drawTrackingReferences";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_Steam_VR_Activate_ਗੁਣਜ_Drivers_Bool = "activateMultipleDrivers";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_SteamVR_UsingSpeakers_Bool = "usingSpeakers";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_Steam_VR_Speakers_Forward_Yaw_ਵਿੱਥ_Degrees_Float = "speakersForwardYawOffsetDegrees";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_Steam_VR_ਅਧਾਰ_Station_Power_Management_Int32 = "basestationPowerManagement";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_Steam_VR_Show_ਅਧਾਰ_Station_Power_Management_Tip_Int32 = "ShowBaseStationPowerManagementTip";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_SteamVR_NeverKillProcesses_Bool = "neverKillProcesses";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_SteamVR_SupersampleScale_Float = "supersampleScale";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_SteamVR_MaxRecommendedResolution_Int32 = "maxRecommendedResolution";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_SteamVR_MotionSmoothing_Bool = "motionSmoothing";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_SteamVR_MotionSmoothingOverride_Int32 = "motionSmoothingOverride";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_Steam_VR_ਚੌਖਟੇ_ਮੰਜ਼ਿਲ_Throttle_Int32 = "framesToThrottle";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_Steam_VR_Additional_ਚੌਖਟੇ_ਮੰਜ਼ਿਲ_Predict_Int32 = "additionalFramesToPredict";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_SteamVR_WorldScale_Float = "worldScale";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_SteamVR_FovScale_Int32 = "fovScale";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_SteamVR_DisableAsyncReprojection_Bool = "disableAsync";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_SteamVR_ForceFadeOnBadTracking_Bool = "forceFadeOnBadTracking";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_SteamVR_DefaultMirrorView_Int32 = "mirrorView";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_SteamVR_ShowLegacyMirrorView_Bool = "showLegacyMirrorView";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_SteamVR_MirrorViewVisibility_Bool = "showMirrorView";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_Steam_VR_Mirror_View_Display_ਬਹੁਲਕ_Int32 = "mirrorViewDisplayMode";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_SteamVR_MirrorViewEye_Int32 = "mirrorViewEye";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_SteamVR_MirrorViewGeometry_String = "mirrorViewGeometry";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_SteamVR_MirrorViewGeometryMaximized_String = "mirrorViewGeometryMaximized";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_Steam_VR_Perf_ਗ੍ਰਾਫ_Visibility_Bool = "showPerfGraph";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_Steam_VR_ਸ਼ੁਰੂ_Monitor_From_App_Launch = "startMonitorFromAppLaunch";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_Steam_VR_ਸ਼ੁਰੂ_Compositor_From_App_Launch_Bool = "startCompositorFromAppLaunch";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_Steam_VR_ਸ਼ੁਰੂ_Dashboard_From_App_Launch_Bool = "startDashboardFromAppLaunch";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_Steam_VR_ਸ਼ੁਰੂ_Overlay_Apps_From_Dashboard_Bool = "startOverlayAppsFromDashboard";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_SteamVR_EnableHomeApp = "enableHomeApp";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_Steam_VR_ਚੱਕਰ_Background_Image_ਸਮਾਂ_Sec_Int32 = "CycleBackgroundImageTimeSec";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_SteamVR_RetailDemo_Bool = "retailDemo";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_Steam_VR_Ipd_ਵਿੱਥ_Float = "ipdOffset";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_SteamVR_AllowSupersampleFiltering_Bool = "allowSupersampleFiltering";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_SteamVR_SupersampleManualOverride_Bool = "supersampleManualOverride";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_SteamVR_EnableLinuxVulkanAsync_Bool = "enableLinuxVulkanAsync";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_Steam_VR_Allow_Display_Locked_ਬਹੁਲਕ_Bool = "allowDisplayLockedMode";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_SteamVR_HaveStartedTutorialForNativeChaperoneDriver_Bool = "haveStartedTutorialForNativeChaperoneDriver";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_SteamVR_ForceWindows32bitVRMonitor = "forceWindows32BitVRMonitor";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_Steam_VR_Debug_ਨਿਵੇਸ਼_Binding = "debugInputBinding";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_Steam_VR_Do_Not_Fade_ਮੰਜ਼ਿਲ_Grid = "doNotFadeToGrid";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_Steam_VR_Render_Camera_ਬਹੁਲਕ = "renderCameraMode";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_SteamVR_EnableSharedResourceJournaling = "enableSharedResourceJournaling";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_Steam_VR_Enable_ਸੁਰੱਖਿਅਤ_ਬਹੁਲਕ = "enableSafeMode";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_Steam_VR_Preferred_Refresh_ਦਰ = "preferredRefreshRate";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_Steam_VR_ਆਖਰੀ_ਸੰਸਕਰਣ_Notice = "lastVersionNotice";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_Steam_VR_ਆਖਰੀ_ਸੰਸਕਰਣ_Notice_Date = "lastVersionNoticeDate";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_SteamVR_HmdDisplayColorGainR_Float = "hmdDisplayColorGainR";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_SteamVR_HmdDisplayColorGainG_Float = "hmdDisplayColorGainG";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_SteamVR_HmdDisplayColorGainB_Float = "hmdDisplayColorGainB";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_SteamVR_CustomIconStyle_String = "customIconStyle";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_SteamVR_CustomOffIconStyle_String = "customOffIconStyle";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_SteamVR_CustomIconForceUpdate_String = "customIconForceUpdate";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_Steam_VR_Allow_Global_Action_ਸੈੱਟ_ਤਰਜੀਹ = "globalActionSetPriority";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_SteamVR_OverlayRenderQuality = "overlayRenderQuality_2";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_Steam_VR_ਖੰਡ_Oculus_SDKOn_Open_VRLaunch_Option_Bool = "blockOculusSDKOnOpenVRLaunchOption";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_Steam_VR_ਖੰਡ_Oculus_SDKOn_All_Launches_Bool = "blockOculusSDKOnAllLaunches";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_SteamVR_HDCPLegacyCompatibility_Bool = "hdcp14legacyCompatibility";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_Steam_VR_Display_ਪੋਰਟ_Training_ਬਹੁਲਕ_Int = "displayPortTrainingMode";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_SteamVR_UsePrism_Bool = "usePrism";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_ਸਿੱਧਾ_ਬਹੁਲਕ_Section = "direct_mode";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_ਸਿੱਧਾ_ਬਹੁਲਕ_Enable_Bool = "enable";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_ਸਿੱਧਾ_ਬਹੁਲਕ_ਗਿਣਤੀ_Int32 = "count";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_ਸਿੱਧਾ_ਬਹੁਲਕ_Edid_Vid_Int32 = "edidVid";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_ਸਿੱਧਾ_ਬਹੁਲਕ_Edid_Pid_Int32 = "edidPid";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_Lighthouse_Section = "driver_lighthouse";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_Lighthouse_DisableIMU_Bool = "disableimu";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_Lighthouse_DisableIMUExceptHMD_Bool = "disableimuexcepthmd";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_Lighthouse_UseDisambiguation_String = "usedisambiguation";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_Lighthouse_DisambiguationDebug_Int32 = "disambiguationdebug";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_Lighthouse_PrimaryBasestation_Int32 = "primarybasestation";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_Lighthouse_DBHistory_Bool = "dbhistory";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_Lighthouse_EnableBluetooth_Bool = "enableBluetooth";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_Lighthouse_Power_Managed_ਅਧਾਰ_Stations_String = "PowerManagedBaseStations";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_Lighthouse_Power_Managed_ਅਧਾਰ_Stations2_String = "PowerManagedBaseStations2";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_Lighthouse_Inactivity_Timeout_For_ਅਧਾਰ_Stations_Int32 = "InactivityTimeoutForBaseStations";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_Lighthouse_EnableImuFallback_Bool = "enableImuFallback";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_Null_Section = "driver_null";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_Null_Serial_ਸੰਖਿਆ_String = "serialNumber";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_Null_Model_ਸੰਖਿਆ_String = "modelNumber";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_Null_ਖਿੜਕੀ_X_Int32 = "windowX";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_Null_ਖਿੜਕੀ_Y_Int32 = "windowY";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_Null_ਖਿੜਕੀ_ਚੌੜਾਈ_Int32 = "windowWidth";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_Null_ਖਿੜਕੀ_ਉਚਾਈ_Int32 = "windowHeight";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_Null_Render_ਚੌੜਾਈ_Int32 = "renderWidth";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_Null_Render_ਉਚਾਈ_Int32 = "renderHeight";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_Null_Seconds_From_Vsync_ਮੰਜ਼ਿਲ_Photons_Float = "secondsFromVsyncToPhotons";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_Null_DisplayFrequency_Float = "displayFrequency";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_WindowsMR_Section = "driver_holographic";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_UserInterface_Section = "userinterface";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_User_Interface_ਸਥਿਤੀ_Always_On_ਸਿਖਰ_Bool = "StatusAlwaysOnTop";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_User_Interface_Minimize_ਮੰਜ਼ਿਲ_Tray_Bool = "MinimizeToTray";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_User_Interface_Hide_Popups_When_ਸਥਿਤੀ_Minimized_Bool = "HidePopupsWhenStatusMinimized";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_UserInterface_Screenshots_Bool = "screenshots";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_UserInterface_ScreenshotType_Int = "screenshotType";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_Notifications_Section = "notifications";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_Notifications_DoNotDisturb_Bool = "DoNotDisturb";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_Keyboard_Section = "keyboard";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_Keyboard_TutorialCompletions = "TutorialCompletions";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_Keyboard_ScaleX = "ScaleX";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_Keyboard_ScaleY = "ScaleY";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_Keyboard_ਵਿੱਥ_ਖੱਬਾ_X = "OffsetLeftX";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_Keyboard_ਵਿੱਥ_ਸੱਜਾ_X = "OffsetRightX";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_Keyboard_ਵਿੱਥ_Y = "OffsetY";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_Keyboard_Smoothing = "Smoothing";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_Perf_Section = "perfcheck";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_Perf_Perf_ਗ੍ਰਾਫ_ਵਿੱਚ_HMD_Bool = "perfGraphInHMD";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_Perf_AllowTimingStore_Bool = "allowTimingStore";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_Perf_SaveTimingsOnExit_Bool = "saveTimingsOnExit";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_Perf_Test_ਅੰਕੜੇ_Float = "perfTestData";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_Perf_GPUProfiling_Bool = "GPUProfiling";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_CollisionBounds_Section = "collisionBounds";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_CollisionBounds_Style_Int32 = "CollisionBoundsStyle";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_CollisionBounds_GroundPerimeterOn_Bool = "CollisionBoundsGroundPerimeterOn";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_CollisionBounds_CenterMarkerOn_Bool = "CollisionBoundsCenterMarkerOn";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_CollisionBounds_PlaySpaceOn_Bool = "CollisionBoundsPlaySpaceOn";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_Collision_Bounds_Fade_ਦੂਰੀ_Float = "CollisionBoundsFadeDistance";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_Collision_Bounds_Wall_ਉਚਾਈ_Float = "CollisionBoundsWallHeight";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_CollisionBounds_ColorGammaR_Int32 = "CollisionBoundsColorGammaR";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_CollisionBounds_ColorGammaG_Int32 = "CollisionBoundsColorGammaG";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_CollisionBounds_ColorGammaB_Int32 = "CollisionBoundsColorGammaB";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_CollisionBounds_ColorGammaA_Int32 = "CollisionBoundsColorGammaA";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_CollisionBounds_EnableDriverImport = "enableDriverBoundsImport";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_Camera_Section = "camera";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_Camera_EnableCamera_Bool = "enableCamera";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_Camera_ShowOnController_Bool = "showOnController";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_Camera_EnableCameraForCollisionBounds_Bool = "enableCameraForCollisionBounds";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_Camera_ਗੁੰਜਾਇਸ਼_View_Int32 = "roomView";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_Camera_BoundsColorGammaR_Int32 = "cameraBoundsColorGammaR";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_Camera_BoundsColorGammaG_Int32 = "cameraBoundsColorGammaG";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_Camera_BoundsColorGammaB_Int32 = "cameraBoundsColorGammaB";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_Camera_BoundsColorGammaA_Int32 = "cameraBoundsColorGammaA";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_Camera_BoundsStrength_Int32 = "cameraBoundsStrength";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_Camera_ਗੁੰਜਾਇਸ਼_View_Style_Int32 = "roomViewStyle";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_audio_Section = "audio";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_audio_ਸੈੱਟ_Os_Default_Playback_Device_Bool = "setOsDefaultPlaybackDevice";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_audio_EnablePlaybackDeviceOverride_Bool = "enablePlaybackDeviceOverride";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_audio_PlaybackDeviceOverride_String = "playbackDeviceOverride";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_audio_PlaybackDeviceOverrideName_String = "playbackDeviceOverrideName";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_audio_ਸੈੱਟ_Os_Default_Recording_Device_Bool = "setOsDefaultRecordingDevice";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_audio_EnableRecordingDeviceOverride_Bool = "enableRecordingDeviceOverride";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_audio_RecordingDeviceOverride_String = "recordingDeviceOverride";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_audio_RecordingDeviceOverrideName_String = "recordingDeviceOverrideName";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_audio_EnablePlaybackMirror_Bool = "enablePlaybackMirror";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_audio_PlaybackMirrorDevice_String = "playbackMirrorDevice";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_audio_PlaybackMirrorDeviceName_String = "playbackMirrorDeviceName";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_audio_OldPlaybackMirrorDevice_String = "onPlaybackMirrorDevice";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_audio_ਸਰਗਰਮ_Mirror_Device_String = "activePlaybackMirrorDevice";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_audio_EnablePlaybackMirrorIndependentVolume_Bool = "enablePlaybackMirrorIndependentVolume";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_audio_ਆਖਰੀ_Hmd_Playback_Device_Id_String = "lastHmdPlaybackDeviceId";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_audio_VIVEHDMIGain = "viveHDMIGain";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_audio_DualSpeakerAndJackOutput_Bool = "dualSpeakerAndJackOutput";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_audio_MuteMicMonitor_Bool = "muteMicMonitor";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_Power_Section = "power";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_Power_PowerOffOnExit_Bool = "powerOffOnExit";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_Power_TurnOffScreensTimeout_Float = "turnOffScreensTimeout";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_Power_TurnOffControllersTimeout_Float = "turnOffControllersTimeout";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_Power_Return_ਮੰਜ਼ਿਲ_Watchdog_Timeout_Float = "returnToWatchdogTimeout";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_Power_AutoLaunchSteamVROnButtonPress = "autoLaunchSteamVROnButtonPress";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_Power_PauseCompositorOnStandby_Bool = "pauseCompositorOnStandby";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_Dashboard_Section = "dashboard";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_Dashboard_EnableDashboard_Bool = "enableDashboard";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_Dashboard_Arcade_ਬਹੁਲਕ_Bool = "arcadeMode";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_Dashboard_Position = "position";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_Dashboard_DesktopScale = "desktopScale";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_Dashboard_DashboardScale = "dashboardScale";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_Dashboard_UseStandaloneSystemLayer = "standaloneSystemLayer";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_Dashboard_StickyDashboard = "stickyDashboard";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_modelskin_Section = "modelskins";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_Driver_Enable_Bool = "enable";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_Driver_BlockedBySafemode_Bool = "blocked_by_safe_mode";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_Driver_ਲੱਦੋ_ਤਰਜੀਹ_Int32 = "loadPriority";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_WebInterface_Section = "WebInterface";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_VRWebHelper_Section = "VRWebHelper";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_VRWebHelper_DebuggerEnabled_Bool = "DebuggerEnabled";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_VRWeb_Helper_Debugger_ਪੋਰਟ_Int32 = "DebuggerPort";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_TrackingOverride_Section = "TrackingOverrides";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_App_BindingAutosaveURLSuffix_String = "AutosaveURL";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_App_BindingLegacyAPISuffix_String = "_legacy";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_App_BindingSteamVRInputAPISuffix_String = "_steamvrinput";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_App_BindingOpenXRAPISuffix_String = "_openxr";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_App_BindingCurrentURLSuffix_String = "CurrentURL";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_App_Binding_ਪਿਛਲਾ_URLSuffix_String = "PreviousURL";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_App_Need_ਮੰਜ਼ਿਲ_Update_Autosave_Suffix_Bool = "NeedToUpdateAutosave";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_App_DominantHand_Int32 = "DominantHand";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_App_ਖੰਡ_Oculus_SDK_Bool = "blockOculusSDK";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_Trackers_Section = "trackers";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_DesktopUI_Section = "DesktopUI";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_ਆਖਰੀ_ਗਿਆਤ_Section = "LastKnown";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_ਆਖਰੀ_ਗਿਆਤ_HMDManufacturer_String = "HMDManufacturer";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_ਆਖਰੀ_ਗਿਆਤ_HMDModel_String = "HMDModel";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_DismissedWarnings_Section = "DismissedWarnings";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_ਨਿਵੇਸ਼_Section = "input";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_ਨਿਵੇਸ਼_ਖੱਬਾ_Thumbstick_Rotation_Float = "leftThumbstickRotation";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_ਨਿਵੇਸ਼_ਸੱਜਾ_Thumbstick_Rotation_Float = "rightThumbstickRotation";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_ਨਿਵੇਸ਼_Thumbstick_Deadzone_Float = "thumbstickDeadzone";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_Gpu_ਰਫਤਾਰ_Section = "GpuSpeed";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * IVRScreenshots_ਸੰਸਕਰਣ = "IVRScreenshots_001";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * IVRResources_ਸੰਸਕਰਣ = "IVRResources_001";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * IVRDriver_Manager_ਸੰਸਕਰਣ = "IVRDriverManager_001";
ਸਥਿਰ ਅਚਲ ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ k_un_Max_Action_Name_ਲੰਮਾਈ = 64;
ਸਥਿਰ ਅਚਲ ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ k_un_Max_Action_ਸੈੱਟ_Name_ਲੰਮਾਈ = 64;
ਸਥਿਰ ਅਚਲ ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ k_un_Max_Action_Origin_ਗਿਣਤੀ = 16;
ਸਥਿਰ ਅਚਲ ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ k_un_Max_Bone_Name_ਲੰਮਾਈ = 32;
ਸਥਿਰ ਅਚਲ ਪੂਰਨ k_n_Action_ਸੈੱਟ_Overlay_Global_ਤਰਜੀਹ_Min = 16777216;
ਸਥਿਰ ਅਚਲ ਪੂਰਨ k_n_Action_ਸੈੱਟ_Overlay_Global_ਤਰਜੀਹ_Max = 33554431;
ਸਥਿਰ ਅਚਲ ਪੂਰਨ k_n_Action_ਸੈੱਟ_ਤਰਜੀਹ_Reserved_Min = 33554432;
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * IVRInput_ਸੰਸਕਰਣ = "IVRInput_010";
ਸਥਿਰ ਅਚਲ ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ ਲੰਮਾ k_ulInvalidIOBufferHandle = 0;
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * IVRIOBuffer_ਸੰਸਕਰਣ = "IVRIOBuffer_002";
ਸਥਿਰ ਅਚਲ ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ k_ulInvalidSpatialAnchorHandle = 0;
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * IVRSpatial_Anchors_ਸੰਸਕਰਣ = "IVRSpatialAnchors_001";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * IVRDebug_ਸੰਸਕਰਣ = "IVRDebug_001";
ਸਥਿਰ ਅਚਲ ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ ਲੰਮਾ k_ulDisplayRedirectContainer = 25769803779;
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * IVRProperties_ਸੰਸਕਰਣ = "IVRProperties_001";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_ਰਸਤਾ_User_Hand_ਸੱਜਾ = "/user/hand/right";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_ਰਸਤਾ_User_Hand_ਖੱਬਾ = "/user/hand/left";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_ਰਸਤਾ_User_Hand_Primary = "/user/hand/primary";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_ਰਸਤਾ_User_Hand_Secondary = "/user/hand/secondary";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_ਰਸਤਾ_User_ਸਿਰ = "/user/head";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_ਰਸਤਾ_User_Gamepad = "/user/gamepad";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_ਰਸਤਾ_User_Treadmill = "/user/treadmill";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_ਰਸਤਾ_User_Stylus = "/user/stylus";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_ਰਸਤਾ_Devices = "/devices";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_ਰਸਤਾ_Device_ਰਸਤਾ = "/device_path";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_ਰਸਤਾ_ਉੱਤਮ_Alias_ਰਸਤਾ = "/best_alias_path";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_ਰਸਤਾ_Bound_Tracker_Alias_ਰਸਤਾ = "/bound_tracker_path";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_ਰਸਤਾ_Bound_Tracker_Role = "/bound_tracker_role";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_ਰਸਤਾ_Pose_Raw = "/pose/raw";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_ਰਸਤਾ_Pose_Tip = "/pose/tip";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_ਰਸਤਾ_Pose_Grip = "/pose/grip";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_ਰਸਤਾ_System_Button_Click = "/input/system/click";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_ਰਸਤਾ_Proximity = "/proximity";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_ਰਸਤਾ_Controller_Type_ਅਗੇਤਰ = "/controller_type/";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_ਰਸਤਾ_ਨਿਵੇਸ਼_Profile_Suffix = "/input_profile";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_ਰਸਤਾ_Binding_Name_Suffix = "/binding_name";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_ਰਸਤਾ_Binding_Url_Suffix = "/binding_url";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_ਰਸਤਾ_Binding_Error_Suffix = "/binding_error";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_ਰਸਤਾ_ਸਰਗਰਮ_Action_Sets = "/active_action_sets";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_ਰਸਤਾ_Component_Updates = "/total_component_updates";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_ਰਸਤਾ_User_Foot_ਖੱਬਾ = "/user/foot/left";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_ਰਸਤਾ_User_Foot_ਸੱਜਾ = "/user/foot/right";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_ਰਸਤਾ_User_Shoulder_ਖੱਬਾ = "/user/shoulder/left";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_ਰਸਤਾ_User_Shoulder_ਸੱਜਾ = "/user/shoulder/right";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_ਰਸਤਾ_User_Elbow_ਖੱਬਾ = "/user/elbow/left";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_ਰਸਤਾ_User_Elbow_ਸੱਜਾ = "/user/elbow/right";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_ਰਸਤਾ_User_Knee_ਖੱਬਾ = "/user/knee/left";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_ਰਸਤਾ_User_Knee_ਸੱਜਾ = "/user/knee/right";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_ਰਸਤਾ_User_Waist = "/user/waist";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_ਰਸਤਾ_User_Chest = "/user/chest";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_ਰਸਤਾ_User_Camera = "/user/camera";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_ਰਸਤਾ_User_Keyboard = "/user/keyboard";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * k_pch_ਰਸਤਾ_Client_App_ਕੁੰਜੀ = "/client_info/app_key";
ਸਥਿਰ ਅਚਲ ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ ਲੰਮਾ k_ul_Invalid_ਰਸਤਾ_Handle = 0;
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * IVRPaths_ਸੰਸਕਰਣ = "IVRPaths_001";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * IVRBlock_ਕਤਾਰ_ਸੰਸਕਰਣ = "IVRBlockQueue_005";

// OpenVR Enums

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ EVREye
{
	EVREye_Eye_ਖੱਬਾ = 0,
	EVREye_Eye_ਸੱਜਾ = 1,
} EVREye;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ ETextureType
{
	ETextureType_TextureType_Invalid = -1,
	ETexture_Type_Texture_Type_ਸਿੱਧਾ_X = 0,
	ETextureType_TextureType_OpenGL = 1,
	ETextureType_TextureType_Vulkan = 2,
	ETextureType_TextureType_IOSurface = 3,
	ETexture_Type_Texture_Type_ਸਿੱਧਾ_X12 = 4,
	ETextureType_TextureType_DXGISharedHandle = 5,
	ETextureType_TextureType_Metal = 6,
} ETextureType;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ EColorSpace
{
	EColorSpace_ColorSpace_Auto = 0,
	EColorSpace_ColorSpace_Gamma = 1,
	EColor_Space_Color_Space_ਰੇਖਿਕ = 2,
} EColorSpace;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ ETracking_ਨਤੀਜਾ
{
	ETracking_ਨਤੀਜਾ_Tracking_ਨਤੀਜਾ_Uninitialized = 1,
	ETracking_ਨਤੀਜਾ_Tracking_ਨਤੀਜਾ_Calibrating_ਵਿੱਚ_ਤਰੱਕੀ = 100,
	ETracking_ਨਤੀਜਾ_Tracking_ਨਤੀਜਾ_Calibrating_ਬਾਹਰਲਾ_ਦਾ_Range = 101,
	ETracking_ਨਤੀਜਾ_Tracking_ਨਤੀਜਾ_Running_OK = 200,
	ETracking_ਨਤੀਜਾ_Tracking_ਨਤੀਜਾ_Running_ਬਾਹਰਲਾ_ਦਾ_Range = 201,
	ETracking_ਨਤੀਜਾ_Tracking_ਨਤੀਜਾ_Fallback_Rotation_Only = 300,
} ETracking_ਨਤੀਜਾ;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ ETrackedDeviceClass
{
	ETrackedDeviceClass_TrackedDeviceClass_Invalid = 0,
	ETrackedDeviceClass_TrackedDeviceClass_HMD = 1,
	ETrackedDeviceClass_TrackedDeviceClass_Controller = 2,
	ETrackedDeviceClass_TrackedDeviceClass_GenericTracker = 3,
	ETrackedDeviceClass_TrackedDeviceClass_TrackingReference = 4,
	ETrackedDeviceClass_TrackedDeviceClass_DisplayRedirect = 5,
	ETrackedDeviceClass_TrackedDeviceClass_Max = 6,
} ETrackedDeviceClass;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ ETrackedControllerRole
{
	ETrackedControllerRole_TrackedControllerRole_Invalid = 0,
	ETracked_Controller_Role_Tracked_Controller_Role_ਖੱਬਾ_Hand = 1,
	ETracked_Controller_Role_Tracked_Controller_Role_ਸੱਜਾ_Hand = 2,
	ETracked_Controller_Role_Tracked_Controller_Role_Opt_ਬਾਹਰਲਾ = 3,
	ETrackedControllerRole_TrackedControllerRole_Treadmill = 4,
	ETrackedControllerRole_TrackedControllerRole_Stylus = 5,
	ETrackedControllerRole_TrackedControllerRole_Max = 5,
} ETrackedControllerRole;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ ETrackingUniverseOrigin
{
	ETrackingUniverseOrigin_TrackingUniverseSeated = 0,
	ETrackingUniverseOrigin_TrackingUniverseStanding = 1,
	ETrackingUniverseOrigin_TrackingUniverseRawAndUncalibrated = 2,
} ETrackingUniverseOrigin;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ EAdditionalRadioFeatures
{
	EAdditionalRadioFeatures_AdditionalRadioFeatures_None = 0,
	EAdditionalRadioFeatures_AdditionalRadioFeatures_HTCLinkBox = 1,
	EAdditional_Radio_Features_Additional_Radio_Features_ਅੰਦਰੂਨੀ_Dongle = 2,
	EAdditionalRadioFeatures_AdditionalRadioFeatures_ExternalDongle = 4,
} EAdditionalRadioFeatures;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ ETrackedDeviceProperty
{
	ETrackedDeviceProperty_Prop_Invalid = 0,
	ETrackedDeviceProperty_Prop_TrackingSystemName_String = 1000,
	ETracked_Device_Property_Prop_Model_ਸੰਖਿਆ_String = 1001,
	ETracked_Device_Property_Prop_Serial_ਸੰਖਿਆ_String = 1002,
	ETrackedDeviceProperty_Prop_RenderModelName_String = 1003,
	ETracked_Device_Property_Prop_Will_Drift_ਵਿੱਚ_Yaw_Bool = 1004,
	ETrackedDeviceProperty_Prop_ManufacturerName_String = 1005,
	ETracked_Device_Property_Prop_Tracking_Firmware_ਸੰਸਕਰਣ_String = 1006,
	ETrackedDeviceProperty_Prop_HardwareRevision_String = 1007,
	ETrackedDeviceProperty_Prop_AllWirelessDongleDescriptions_String = 1008,
	ETrackedDeviceProperty_Prop_ConnectedWirelessDongle_String = 1009,
	ETrackedDeviceProperty_Prop_DeviceIsWireless_Bool = 1010,
	ETrackedDeviceProperty_Prop_DeviceIsCharging_Bool = 1011,
	ETrackedDeviceProperty_Prop_DeviceBatteryPercentage_Float = 1012,
	ETracked_Device_Property_Prop_ਸਥਿਤੀ_Display_Transform_Matrix34 = 1013,
	ETracked_Device_Property_Prop_Firmware_Update_ਉਪਲਬਧ_Bool = 1014,
	ETrackedDeviceProperty_Prop_Firmware_ManualUpdate_Bool = 1015,
	ETrackedDeviceProperty_Prop_Firmware_ManualUpdateURL_String = 1016,
	ETrackedDeviceProperty_Prop_HardwareRevision_Uint64 = 1017,
	ETracked_Device_Property_Prop_Firmware_ਸੰਸਕਰਣ_Uint64 = 1018,
	ETrackedDeviceProperty_Prop_FPGAVersion_Uint64 = 1019,
	ETrackedDeviceProperty_Prop_VRCVersion_Uint64 = 1020,
	ETracked_Device_Property_Prop_Radio_ਸੰਸਕਰਣ_Uint64 = 1021,
	ETracked_Device_Property_Prop_Dongle_ਸੰਸਕਰਣ_Uint64 = 1022,
	ETracked_Device_Property_Prop_ਖੰਡ_Server_Shutdown_Bool = 1023,
	ETrackedDeviceProperty_Prop_CanUnifyCoordinateSystemWithHmd_Bool = 1024,
	ETracked_Device_Property_Prop_ਸ਼ਾਮਲ_ਹੈ_Proximity_Sensor_Bool = 1025,
	ETracked_Device_Property_Prop_Device_Provides_Battery_ਸਥਿਤੀ_Bool = 1026,
	ETrackedDeviceProperty_Prop_DeviceCanPowerOff_Bool = 1027,
	ETracked_Device_Property_Prop_Firmware_Programming_ਨਿਸ਼ਾਨਾ_String = 1028,
	ETrackedDeviceProperty_Prop_DeviceClass_Int32 = 1029,
	ETrackedDeviceProperty_Prop_HasCamera_Bool = 1030,
	ETracked_Device_Property_Prop_Driver_ਸੰਸਕਰਣ_String = 1031,
	ETrackedDeviceProperty_Prop_Firmware_ForceUpdateRequired_Bool = 1032,
	ETrackedDeviceProperty_Prop_ViveSystemButtonFixRequired_Bool = 1033,
	ETracked_Device_Property_Prop_ਮਾਪਾ_Driver_Uint64 = 1034,
	ETracked_Device_Property_Prop_Resource_ਜੜ੍ਹ_String = 1035,
	ETrackedDeviceProperty_Prop_RegisteredDeviceType_String = 1036,
	ETracked_Device_Property_Prop_ਨਿਵੇਸ਼_Profile_ਰਸਤਾ_String = 1037,
	ETrackedDeviceProperty_Prop_NeverTracked_Bool = 1038,
	ETracked_Device_Property_Prop_ਅੰਕ_Cameras_Int32 = 1039,
	ETracked_Device_Property_Prop_Camera_ਚੌਖਟਾ_Layout_Int32 = 1040,
	ETracked_Device_Property_Prop_Camera_ਧਾਰਾ_Format_Int32 = 1041,
	ETracked_Device_Property_Prop_Additional_Device_Settings_ਰਸਤਾ_String = 1042,
	ETrackedDeviceProperty_Prop_Identifiable_Bool = 1043,
	ETracked_Device_Property_Prop_Bootloader_ਸੰਸਕਰਣ_Uint64 = 1044,
	ETracked_Device_Property_Prop_Additional_System_Report_ਅੰਕੜੇ_String = 1045,
	ETracked_Device_Property_Prop_ਸੰਯੁਕਤ_Firmware_ਸੰਸਕਰਣ_String = 1046,
	ETrackedDeviceProperty_Prop_Firmware_RemindUpdate_Bool = 1047,
	ETracked_Device_Property_Prop_Peripheral_Application_ਸੰਸਕਰਣ_Uint64 = 1048,
	ETracked_Device_Property_Prop_Manufacturer_Serial_ਸੰਖਿਆ_String = 1049,
	ETracked_Device_Property_Prop_Computed_Serial_ਸੰਖਿਆ_String = 1050,
	ETracked_Device_Property_Prop_Estimated_Device_ਪਹਿਲਾ_Use_ਸਮਾਂ_Int32 = 1051,
	ETrackedDeviceProperty_Prop_DevicePowerUsage_Float = 1052,
	ETrackedDeviceProperty_Prop_IgnoreMotionForStandby_Bool = 1053,
	ETracked_Device_Property_Prop_Reports_ਸਮਾਂ_Since_VSync_Bool = 2000,
	ETracked_Device_Property_Prop_Seconds_From_Vsync_ਮੰਜ਼ਿਲ_Photons_Float = 2001,
	ETrackedDeviceProperty_Prop_DisplayFrequency_Float = 2002,
	ETrackedDeviceProperty_Prop_UserIpdMeters_Float = 2003,
	ETrackedDeviceProperty_Prop_CurrentUniverseId_Uint64 = 2004,
	ETracked_Device_Property_Prop_ਪਿਛਲਾ_Universe_Id_Uint64 = 2005,
	ETracked_Device_Property_Prop_Display_Firmware_ਸੰਸਕਰਣ_Uint64 = 2006,
	ETrackedDeviceProperty_Prop_IsOnDesktop_Bool = 2007,
	ETrackedDeviceProperty_Prop_DisplayMCType_Int32 = 2008,
	ETrackedDeviceProperty_Prop_DisplayMCOffset_Float = 2009,
	ETrackedDeviceProperty_Prop_DisplayMCScale_Float = 2010,
	ETrackedDeviceProperty_Prop_EdidVendorID_Int32 = 2011,
	ETracked_Device_Property_Prop_Display_MCImage_ਖੱਬਾ_String = 2012,
	ETracked_Device_Property_Prop_Display_MCImage_ਸੱਜਾ_String = 2013,
	ETrackedDeviceProperty_Prop_DisplayGCBlackClamp_Float = 2014,
	ETracked_Device_Property_Prop_Edid_ਗੁਣਨਫਲ_ID_Int32 = 2015,
	ETracked_Device_Property_Prop_Camera_ਮੰਜ਼ਿਲ_ਸਿਰ_Transform_Matrix34 = 2016,
	ETrackedDeviceProperty_Prop_DisplayGCType_Int32 = 2017,
	ETrackedDeviceProperty_Prop_DisplayGCOffset_Float = 2018,
	ETrackedDeviceProperty_Prop_DisplayGCScale_Float = 2019,
	ETrackedDeviceProperty_Prop_DisplayGCPrescale_Float = 2020,
	ETrackedDeviceProperty_Prop_DisplayGCImage_String = 2021,
	ETracked_Device_Property_Prop_Lens_Center_ਖੱਬਾ_U_Float = 2022,
	ETracked_Device_Property_Prop_Lens_Center_ਖੱਬਾ_V_Float = 2023,
	ETracked_Device_Property_Prop_Lens_Center_ਸੱਜਾ_U_Float = 2024,
	ETracked_Device_Property_Prop_Lens_Center_ਸੱਜਾ_V_Float = 2025,
	ETracked_Device_Property_Prop_User_ਸਿਰ_ਮੰਜ਼ਿਲ_Eye_ਡੂੰਘਾਈ_Meters_Float = 2026,
	ETracked_Device_Property_Prop_Camera_Firmware_ਸੰਸਕਰਣ_Uint64 = 2027,
	ETrackedDeviceProperty_Prop_CameraFirmwareDescription_String = 2028,
	ETrackedDeviceProperty_Prop_DisplayFPGAVersion_Uint64 = 2029,
	ETracked_Device_Property_Prop_Display_Bootloader_ਸੰਸਕਰਣ_Uint64 = 2030,
	ETracked_Device_Property_Prop_Display_Hardware_ਸੰਸਕਰਣ_Uint64 = 2031,
	ETracked_Device_Property_Prop_Audio_Firmware_ਸੰਸਕਰਣ_Uint64 = 2032,
	ETracked_Device_Property_Prop_Camera_Compatibility_ਬਹੁਲਕ_Int32 = 2033,
	ETracked_Device_Property_Prop_Screenshot_Horizontal_ਖੇਤਰ_ਦਾ_View_Degrees_Float = 2034,
	ETracked_Device_Property_Prop_Screenshot_Vertical_ਖੇਤਰ_ਦਾ_View_Degrees_Float = 2035,
	ETrackedDeviceProperty_Prop_DisplaySuppressed_Bool = 2036,
	ETracked_Device_Property_Prop_Display_Allow_Night_ਬਹੁਲਕ_Bool = 2037,
	ETracked_Device_Property_Prop_Display_MCImage_ਚੌੜਾਈ_Int32 = 2038,
	ETracked_Device_Property_Prop_Display_MCImage_ਉਚਾਈ_Int32 = 2039,
	ETracked_Device_Property_Prop_Display_MCImage_ਅੰਕ_Channels_Int32 = 2040,
	ETracked_Device_Property_Prop_Display_MCImage_ਅੰਕੜੇ_ਦੁਆਧਾਰੀ = 2041,
	ETracked_Device_Property_Prop_Seconds_From_Photons_ਮੰਜ਼ਿਲ_Vblank_Float = 2042,
	ETracked_Device_Property_Prop_Driver_ਸਿੱਧਾ_ਬਹੁਲਕ_Sends_Vsync_Events_Bool = 2043,
	ETracked_Device_Property_Prop_Display_Debug_ਬਹੁਲਕ_Bool = 2044,
	ETrackedDeviceProperty_Prop_GraphicsAdapterLuid_Uint64 = 2045,
	ETracked_Device_Property_Prop_Driver_Provided_Chaperone_ਰਸਤਾ_String = 2048,
	ETracked_Device_Property_Prop_Expected_Tracking_Reference_ਗਿਣਤੀ_Int32 = 2049,
	ETracked_Device_Property_Prop_Expected_Controller_ਗਿਣਤੀ_Int32 = 2050,
	ETracked_Device_Property_Prop_Named_Icon_ਰਸਤਾ_Controller_ਖੱਬਾ_Device_Off_String = 2051,
	ETracked_Device_Property_Prop_Named_Icon_ਰਸਤਾ_Controller_ਸੱਜਾ_Device_Off_String = 2052,
	ETracked_Device_Property_Prop_Named_Icon_ਰਸਤਾ_Tracking_Reference_Device_Off_String = 2053,
	ETrackedDeviceProperty_Prop_DoNotApplyPrediction_Bool = 2054,
	ETracked_Device_Property_Prop_Camera_ਮੰਜ਼ਿਲ_ਸਿਰ_Transforms_Matrix34_Array = 2055,
	ETrackedDeviceProperty_Prop_DistortionMeshResolution_Int32 = 2056,
	ETrackedDeviceProperty_Prop_DriverIsDrawingControllers_Bool = 2057,
	ETracked_Device_Property_Prop_Driver_ਬੇਨਤੀਆਂ_Application_Pause_Bool = 2058,
	ETracked_Device_Property_Prop_Driver_ਬੇਨਤੀਆਂ_Reduced_Rendering_Bool = 2059,
	ETracked_Device_Property_Prop_Minimum_Ipd_ਕਦਮ_Meters_Float = 2060,
	ETracked_Device_Property_Prop_Audio_Bridge_Firmware_ਸੰਸਕਰਣ_Uint64 = 2061,
	ETracked_Device_Property_Prop_Image_Bridge_Firmware_ਸੰਸਕਰਣ_Uint64 = 2062,
	ETracked_Device_Property_Prop_Imu_ਮੰਜ਼ਿਲ_ਸਿਰ_Transform_Matrix34 = 2063,
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
	ETracked_Device_Property_Prop_Hmd_ਕਾਲਮ_Correction_Setting_ਅਗੇਤਰ_String = 2077,
	ETrackedDeviceProperty_Prop_CameraSupportsCompatibilityModes_Bool = 2078,
	ETracked_Device_Property_Prop_Supports_ਗੁੰਜਾਇਸ਼_View_ਡੂੰਘਾਈ_Projection_Bool = 2079,
	ETracked_Device_Property_Prop_Display_ਉਪਲਬਧ_ਚੌਖਟਾ_Rates_Float_Array = 2080,
	ETracked_Device_Property_Prop_Display_Supports_ਗੁਣਜ_Framerates_Bool = 2081,
	ETracked_Device_Property_Prop_Display_Color_Mult_ਖੱਬਾ_Vector3 = 2082,
	ETracked_Device_Property_Prop_Display_Color_Mult_ਸੱਜਾ_Vector3 = 2083,
	ETrackedDeviceProperty_Prop_DisplaySupportsRuntimeFramerateChange_Bool = 2084,
	ETrackedDeviceProperty_Prop_DisplaySupportsAnalogGain_Bool = 2085,
	ETrackedDeviceProperty_Prop_DisplayMinAnalogGain_Float = 2086,
	ETrackedDeviceProperty_Prop_DisplayMaxAnalogGain_Float = 2087,
	ETracked_Device_Property_Prop_Camera_Exposure_ਸਮਾਂ_Float = 2088,
	ETrackedDeviceProperty_Prop_CameraGlobalGain_Float = 2089,
	ETrackedDeviceProperty_Prop_DashboardScale_Float = 2091,
	ETrackedDeviceProperty_Prop_PeerButtonInfo_String = 2092,
	ETrackedDeviceProperty_Prop_Hmd_SupportsHDR10_Bool = 2093,
	ETrackedDeviceProperty_Prop_IpdUIRangeMinMeters_Float = 2100,
	ETrackedDeviceProperty_Prop_IpdUIRangeMaxMeters_Float = 2101,
	ETrackedDeviceProperty_Prop_Hmd_SupportsHDCP14LegacyCompat_Bool = 2102,
	ETrackedDeviceProperty_Prop_Hmd_SupportsMicMonitoring_Bool = 2103,
	ETracked_Device_Property_Prop_Hmd_Supports_Display_ਪੋਰਟ_Training_ਬਹੁਲਕ_Bool = 2104,
	ETracked_Device_Property_Prop_Supports_ਗੁੰਜਾਇਸ਼_View_ਸਿੱਧਾ_Bool = 2105,
	ETrackedDeviceProperty_Prop_SupportsAppThrottling_Bool = 2106,
	ETrackedDeviceProperty_Prop_DSCVersion_Int32 = 2110,
	ETracked_Device_Property_Prop_DSCSlice_ਗਿਣਤੀ_Int32 = 2111,
	ETrackedDeviceProperty_Prop_DSCBPPx16_Int32 = 2112,
	ETracked_Device_Property_Prop_Driver_Requested_Mura_Correction_ਬਹੁਲਕ_Int32 = 2200,
	ETracked_Device_Property_Prop_Driver_Requested_Mura_Feather_Inner_ਖੱਬਾ_Int32 = 2201,
	ETracked_Device_Property_Prop_Driver_Requested_Mura_Feather_Inner_ਸੱਜਾ_Int32 = 2202,
	ETracked_Device_Property_Prop_Driver_Requested_Mura_Feather_Inner_ਸਿਖਰ_Int32 = 2203,
	ETrackedDeviceProperty_Prop_DriverRequestedMuraFeather_InnerBottom_Int32 = 2204,
	ETracked_Device_Property_Prop_Driver_Requested_Mura_Feather_Outer_ਖੱਬਾ_Int32 = 2205,
	ETracked_Device_Property_Prop_Driver_Requested_Mura_Feather_Outer_ਸੱਜਾ_Int32 = 2206,
	ETracked_Device_Property_Prop_Driver_Requested_Mura_Feather_Outer_ਸਿਖਰ_Int32 = 2207,
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
	ETracked_Device_Property_Prop_ਖੇਤਰ_ਦਾ_View_ਖੱਬਾ_Degrees_Float = 4000,
	ETracked_Device_Property_Prop_ਖੇਤਰ_ਦਾ_View_ਸੱਜਾ_Degrees_Float = 4001,
	ETracked_Device_Property_Prop_ਖੇਤਰ_ਦਾ_View_ਸਿਖਰ_Degrees_Float = 4002,
	ETracked_Device_Property_Prop_ਖੇਤਰ_ਦਾ_View_Bottom_Degrees_Float = 4003,
	ETrackedDeviceProperty_Prop_TrackingRangeMinimumMeters_Float = 4004,
	ETracked_Device_Property_Prop_Tracking_Range_ਵੱਧ_ਤੋਂ_ਵੱਧ_Meters_Float = 4005,
	ETracked_Device_Property_Prop_ਬਹੁਲਕ_Label_String = 4006,
	ETrackedDeviceProperty_Prop_CanWirelessIdentify_Bool = 4007,
	ETrackedDeviceProperty_Prop_Nonce_Int32 = 4008,
	ETracked_Device_Property_Prop_Icon_ਰਸਤਾ_Name_String = 5000,
	ETracked_Device_Property_Prop_Named_Icon_ਰਸਤਾ_Device_Off_String = 5001,
	ETracked_Device_Property_Prop_Named_Icon_ਰਸਤਾ_Device_Searching_String = 5002,
	ETracked_Device_Property_Prop_Named_Icon_ਰਸਤਾ_Device_Searching_Alert_String = 5003,
	ETracked_Device_Property_Prop_Named_Icon_ਰਸਤਾ_Device_Ready_String = 5004,
	ETracked_Device_Property_Prop_Named_Icon_ਰਸਤਾ_Device_Ready_Alert_String = 5005,
	ETracked_Device_Property_Prop_Named_Icon_ਰਸਤਾ_Device_Not_Ready_String = 5006,
	ETracked_Device_Property_Prop_Named_Icon_ਰਸਤਾ_Device_Standby_String = 5007,
	ETracked_Device_Property_Prop_Named_Icon_ਰਸਤਾ_Device_Alert_ਨੀਵਾਂ_String = 5008,
	ETracked_Device_Property_Prop_Named_Icon_ਰਸਤਾ_Device_Standby_Alert_String = 5009,
	ETracked_Device_Property_Prop_Display_Hidden_Area_ਦੁਆਧਾਰੀ_ਸ਼ੁਰੂ = 5100,
	ETracked_Device_Property_Prop_Display_Hidden_Area_ਦੁਆਧਾਰੀ_ਸਿਰਾ = 5150,
	ETracked_Device_Property_Prop_ਮਾਪਾ_Container = 5151,
	ETrackedDeviceProperty_Prop_OverrideContainer_Uint64 = 5152,
	ETracked_Device_Property_Prop_User_Config_ਰਸਤਾ_String = 6000,
	ETracked_Device_Property_Prop_Install_ਰਸਤਾ_String = 6001,
	ETrackedDeviceProperty_Prop_HasDisplayComponent_Bool = 6002,
	ETrackedDeviceProperty_Prop_HasControllerComponent_Bool = 6003,
	ETrackedDeviceProperty_Prop_HasCameraComponent_Bool = 6004,
	ETracked_Device_Property_Prop_Has_Driver_ਸਿੱਧਾ_ਬਹੁਲਕ_Component_Bool = 6005,
	ETrackedDeviceProperty_Prop_HasVirtualDisplayComponent_Bool = 6006,
	ETrackedDeviceProperty_Prop_HasSpatialAnchorsSupport_Bool = 6007,
	ETrackedDeviceProperty_Prop_ControllerType_String = 7000,
	ETracked_Device_Property_Prop_Controller_Hand_Selection_ਤਰਜੀਹ_Int32 = 7002,
	ETracked_Device_Property_Prop_Vendor_Specific_Reserved_ਸ਼ੁਰੂ = 10000,
	ETracked_Device_Property_Prop_Vendor_Specific_Reserved_ਸਿਰਾ = 10999,
	ETrackedDeviceProperty_Prop_TrackedDeviceProperty_Max = 1000000,
} ETrackedDeviceProperty;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ ETrackedPropertyError
{
	ETrackedPropertyError_TrackedProp_Success = 0,
	ETracked_Property_Error_Tracked_Prop_Wrong_ਅੰਕੜੇ_Type = 1,
	ETrackedPropertyError_TrackedProp_WrongDeviceClass = 2,
	ETracked_Property_Error_Tracked_Prop_ਬਫਰ_Too_Small = 3,
	ETrackedPropertyError_TrackedProp_UnknownProperty = 4,
	ETrackedPropertyError_TrackedProp_InvalidDevice = 5,
	ETrackedPropertyError_TrackedProp_CouldNotContactServer = 6,
	ETracked_Property_Error_Tracked_Prop_ਮੁੱਲ_Not_Provided_By_Device = 7,
	ETracked_Property_Error_Tracked_Prop_String_Exceeds_ਵੱਧ_ਤੋਂ_ਵੱਧ_ਲੰਮਾਈ = 8,
	ETracked_Property_Error_Tracked_Prop_Not_Yet_ਉਪਲਬਧ = 9,
	ETrackedPropertyError_TrackedProp_PermissionDenied = 10,
	ETrackedPropertyError_TrackedProp_InvalidOperation = 11,
	ETracked_Property_Error_Tracked_Prop_Cannot_Write_ਮੰਜ਼ਿਲ_Wildcards = 12,
	ETrackedPropertyError_TrackedProp_IPCReadFailure = 13,
	ETracked_Property_Error_Tracked_Prop_ਬਾਹਰਲਾ_ਦਾ_ਸਮ੍ਰਿਤੀ = 14,
	ETrackedPropertyError_TrackedProp_InvalidContainer = 15,
} ETrackedPropertyError;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ EHmdTrackingStyle
{
	EHmdTrackingStyle_HmdTrackingStyle_Unknown = 0,
	EHmdTrackingStyle_HmdTrackingStyle_Lighthouse = 1,
	EHmd_Tracking_Style_Hmd_Tracking_Style_Outside_ਵਿੱਚ_Cameras = 2,
	EHmd_Tracking_Style_Hmd_Tracking_Style_Inside_ਬਾਹਰਲਾ_Cameras = 3,
} EHmdTrackingStyle;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ EVRSubmitFlags
{
	EVRSubmitFlags_Submit_Default = 0,
	EVRSubmitFlags_Submit_LensDistortionAlreadyApplied = 1,
	EVRSubmit_Flags_Submit_Gl_Render_ਬਫਰ = 2,
	EVRSubmitFlags_Submit_Reserved = 4,
	EVRSubmitFlags_Submit_TextureWithPose = 8,
	EVRSubmit_Flags_Submit_Texture_With_ਡੂੰਘਾਈ = 16,
	EVRSubmit_Flags_Submit_ਚੌਖਟਾ_Discontinuty = 32,
	EVRSubmit_Flags_Submit_Vulkan_Texture_With_Array_ਅੰਕੜੇ = 64,
	EVRSubmitFlags_Submit_GlArrayTexture = 128,
	EVRSubmitFlags_Submit_Reserved2 = 32768,
	EVRSubmitFlags_Submit_Reserved3 = 65536,
} EVRSubmitFlags;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ EVRState
{
	EVRState_VRState_Undefined = -1,
	EVRState_VRState_Off = 0,
	EVRState_VRState_Searching = 1,
	EVRState_VRState_Searching_Alert = 2,
	EVRState_VRState_Ready = 3,
	EVRState_VRState_Ready_Alert = 4,
	EVRState_VRState_NotReady = 5,
	EVRState_VRState_Standby = 6,
	EVRState_VRState_Ready_Alert_ਨੀਵਾਂ = 7,
} EVRState;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ EVREventType
{
	EVREventType_VREvent_None = 0,
	EVREventType_VREvent_TrackedDeviceActivated = 100,
	EVREventType_VREvent_TrackedDeviceDeactivated = 101,
	EVREventType_VREvent_TrackedDeviceUpdated = 102,
	EVREventType_VREvent_TrackedDeviceUserInteractionStarted = 103,
	EVREventType_VREvent_TrackedDeviceUserInteractionEnded = 104,
	EVREvent_Type_VREvent_Ipd_ਬਦਲਿਆ = 105,
	EVREvent_Type_VREvent_Enter_Standby_ਬਹੁਲਕ = 106,
	EVREvent_Type_VREvent_Leave_Standby_ਬਹੁਲਕ = 107,
	EVREvent_Type_VREvent_Tracked_Device_Role_ਬਦਲਿਆ = 108,
	EVREvent_Type_VREvent_Watchdog_Wake_ਉੱਪਰ_Requested = 109,
	EVREvent_Type_VREvent_Lens_Distortion_ਬਦਲਿਆ = 110,
	EVREvent_Type_VREvent_Property_ਬਦਲਿਆ = 111,
	EVREventType_VREvent_WirelessDisconnect = 112,
	EVREventType_VREvent_WirelessReconnect = 113,
	EVREventType_VREvent_ButtonPress = 200,
	EVREventType_VREvent_ButtonUnpress = 201,
	EVREventType_VREvent_ButtonTouch = 202,
	EVREventType_VREvent_ButtonUntouch = 203,
	EVREventType_VREvent_Modal_Cancel = 257,
	EVREventType_VREvent_MouseMove = 300,
	EVREvent_Type_VREvent_Mouse_Button_ਥੱਲੇ = 301,
	EVREvent_Type_VREvent_Mouse_Button_ਉੱਪਰ = 302,
	EVREventType_VREvent_FocusEnter = 303,
	EVREventType_VREvent_FocusLeave = 304,
	EVREventType_VREvent_ScrollDiscrete = 305,
	EVREventType_VREvent_TouchPadMove = 306,
	EVREvent_Type_VREvent_Overlay_Focus_ਬਦਲਿਆ = 307,
	EVREventType_VREvent_ReloadOverlays = 308,
	EVREventType_VREvent_ScrollSmooth = 309,
	EVREvent_Type_VREvent_ਤਾਲਾ_Mouse_Position = 310,
	EVREventType_VREvent_UnlockMousePosition = 311,
	EVREvent_Type_VREvent_ਨਿਵੇਸ਼_Focus_Captured = 400,
	EVREvent_Type_VREvent_ਨਿਵੇਸ਼_Focus_Released = 401,
	EVREvent_Type_VREvent_Scene_Application_ਬਦਲਿਆ = 404,
	EVREvent_Type_VREvent_ਨਿਵੇਸ਼_Focus_ਬਦਲਿਆ = 406,
	EVREventType_VREvent_SceneApplicationUsingWrongGraphicsAdapter = 408,
	EVREventType_VREvent_ActionBindingReloaded = 409,
	EVREventType_VREvent_HideRenderModels = 410,
	EVREventType_VREvent_ShowRenderModels = 411,
	EVREvent_Type_VREvent_Scene_Application_State_ਬਦਲਿਆ = 412,
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
	EVREvent_Type_VREvent_Overlay_Gamepad_Focus_ਗੁਆਚਾ = 512,
	EVREvent_Type_VREvent_Overlay_Shared_Texture_ਬਦਲਿਆ = 513,
	EVREventType_VREvent_ScreenshotTriggered = 516,
	EVREventType_VREvent_ImageFailed = 517,
	EVREventType_VREvent_DashboardOverlayCreated = 518,
	EVREventType_VREvent_SwitchGamepadFocus = 519,
	EVREventType_VREvent_RequestScreenshot = 520,
	EVREvent_Type_VREvent_Screenshot_ਲਿਆ = 521,
	EVREventType_VREvent_ScreenshotFailed = 522,
	EVREvent_Type_VREvent_Submit_Screenshot_ਮੰਜ਼ਿਲ_Dashboard = 523,
	EVREvent_Type_VREvent_Screenshot_ਤਰੱਕੀ_ਮੰਜ਼ਿਲ_Dashboard = 524,
	EVREvent_Type_VREvent_Primary_Dashboard_Device_ਬਦਲਿਆ = 525,
	EVREvent_Type_VREvent_ਗੁੰਜਾਇਸ਼_View_Shown = 526,
	EVREvent_Type_VREvent_ਗੁੰਜਾਇਸ਼_View_Hidden = 527,
	EVREventType_VREvent_ShowUI = 528,
	EVREventType_VREvent_ShowDevTools = 529,
	EVREventType_VREvent_DesktopViewUpdating = 530,
	EVREventType_VREvent_DesktopViewReady = 531,
	EVREvent_Type_VREvent_ਸ਼ੁਰੂ_Dashboard = 532,
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
	EVREvent_Type_VREvent_Invalidate_ਅਦਲਾ_ਬਦਲੀ_Texture_Sets = 706,
	EVREvent_Type_VREvent_Chaperone_ਅੰਕੜੇ_Has_ਬਦਲਿਆ = 800,
	EVREvent_Type_VREvent_Chaperone_Universe_Has_ਬਦਲਿਆ = 801,
	EVREvent_Type_VREvent_Chaperone_ਆਰਜ਼ੀ_ਅੰਕੜੇ_Has_ਬਦਲਿਆ = 802,
	EVREvent_Type_VREvent_Chaperone_Settings_Have_ਬਦਲਿਆ = 803,
	EVREventType_VREvent_SeatedZeroPoseReset = 804,
	EVREventType_VREvent_ChaperoneFlushCache = 805,
	EVREvent_Type_VREvent_Chaperone_ਗੁੰਜਾਇਸ਼_ਤਿਆਰੀ_Starting = 806,
	EVREvent_Type_VREvent_Chaperone_ਗੁੰਜਾਇਸ਼_ਤਿਆਰੀ_ਮੁਕੰਮਲ = 807,
	EVREventType_VREvent_StandingZeroPoseReset = 808,
	EVREvent_Type_VREvent_Audio_Settings_Have_ਬਦਲਿਆ = 820,
	EVREvent_Type_VREvent_Background_Setting_Has_ਬਦਲਿਆ = 850,
	EVREvent_Type_VREvent_Camera_Settings_Have_ਬਦਲਿਆ = 851,
	EVREvent_Type_VREvent_Reprojection_Setting_Has_ਬਦਲਿਆ = 852,
	EVREvent_Type_VREvent_Model_Skin_Settings_Have_ਬਦਲਿਆ = 853,
	EVREvent_Type_VREvent_Environment_Settings_Have_ਬਦਲਿਆ = 854,
	EVREvent_Type_VREvent_Power_Settings_Have_ਬਦਲਿਆ = 855,
	EVREvent_Type_VREvent_Enable_Home_App_Settings_Have_ਬਦਲਿਆ = 856,
	EVREvent_Type_VREvent_Steam_VRSection_Setting_ਬਦਲਿਆ = 857,
	EVREvent_Type_VREvent_Lighthouse_Section_Setting_ਬਦਲਿਆ = 858,
	EVREvent_Type_VREvent_Null_Section_Setting_ਬਦਲਿਆ = 859,
	EVREvent_Type_VREvent_User_Interface_Section_Setting_ਬਦਲਿਆ = 860,
	EVREvent_Type_VREvent_Notifications_Section_Setting_ਬਦਲਿਆ = 861,
	EVREvent_Type_VREvent_Keyboard_Section_Setting_ਬਦਲਿਆ = 862,
	EVREvent_Type_VREvent_Perf_Section_Setting_ਬਦਲਿਆ = 863,
	EVREvent_Type_VREvent_Dashboard_Section_Setting_ਬਦਲਿਆ = 864,
	EVREvent_Type_VREvent_Web_Interface_Section_Setting_ਬਦਲਿਆ = 865,
	EVREvent_Type_VREvent_Trackers_Section_Setting_ਬਦਲਿਆ = 866,
	EVREvent_Type_VREvent_ਆਖਰੀ_ਗਿਆਤ_Section_Setting_ਬਦਲਿਆ = 867,
	EVREvent_Type_VREvent_Dismissed_Warnings_Section_Setting_ਬਦਲਿਆ = 868,
	EVREvent_Type_VREvent_Gpu_ਰਫਤਾਰ_Section_Setting_ਬਦਲਿਆ = 869,
	EVREvent_Type_VREvent_Windows_MRSection_Setting_ਬਦਲਿਆ = 870,
	EVREvent_Type_VREvent_Other_Section_Setting_ਬਦਲਿਆ = 871,
	EVREvent_Type_VREvent_ਸਥਿਤੀ_Update = 900,
	EVREventType_VREvent_WebInterface_InstallDriverCompleted = 950,
	EVREventType_VREvent_MCImageUpdated = 1000,
	EVREventType_VREvent_FirmwareUpdateStarted = 1100,
	EVREvent_Type_VREvent_Firmware_Update_ਮੁਕੰਮਲ = 1101,
	EVREventType_VREvent_KeyboardClosed = 1200,
	EVREvent_Type_VREvent_Keyboard_Char_ਨਿਵੇਸ਼ = 1201,
	EVREvent_Type_VREvent_Keyboard_ਪੂਰਾ = 1202,
	EVREventType_VREvent_ApplicationListUpdated = 1303,
	EVREvent_Type_VREvent_Application_Mime_Type_ਲੱਦੋ = 1304,
	EVREventType_VREvent_ProcessConnected = 1306,
	EVREventType_VREvent_ProcessDisconnected = 1307,
	EVREventType_VREvent_Compositor_ChaperoneBoundsShown = 1410,
	EVREventType_VREvent_Compositor_ChaperoneBoundsHidden = 1411,
	EVREventType_VREvent_Compositor_DisplayDisconnected = 1412,
	EVREventType_VREvent_Compositor_DisplayReconnected = 1413,
	EVREventType_VREvent_Compositor_HDCPError = 1414,
	EVREventType_VREvent_Compositor_ApplicationNotResponding = 1415,
	EVREventType_VREvent_Compositor_ApplicationResumed = 1416,
	EVREvent_Type_VREvent_Compositor_ਬਾਹਰਲਾ_ਦਾ_Video_ਸਮ੍ਰਿਤੀ = 1417,
	EVREvent_Type_VREvent_Compositor_Display_ਬਹੁਲਕ_Not_Supported = 1418,
	EVREventType_VREvent_Compositor_StageOverrideReady = 1419,
	EVREventType_VREvent_Compositor_RequestDisconnectReconnect = 1420,
	EVREvent_Type_VREvent_Tracked_Camera_ਸ਼ੁਰੂ_Video_ਧਾਰਾ = 1500,
	EVREvent_Type_VREvent_Tracked_Camera_Stop_Video_ਧਾਰਾ = 1501,
	EVREvent_Type_VREvent_Tracked_Camera_Pause_Video_ਧਾਰਾ = 1502,
	EVREvent_Type_VREvent_Tracked_Camera_Resume_Video_ਧਾਰਾ = 1503,
	EVREventType_VREvent_TrackedCamera_EditingSurface = 1550,
	EVREventType_VREvent_PerformanceTest_EnableCapture = 1600,
	EVREventType_VREvent_PerformanceTest_DisableCapture = 1601,
	EVREventType_VREvent_PerformanceTest_FidelityLevel = 1602,
	EVREvent_Type_VREvent_ਸੁਨੇਹਾ_Overlay_Closed = 1650,
	EVREvent_Type_VREvent_ਸੁਨੇਹਾ_Overlay_Close_Requested = 1651,
	EVREvent_Type_VREvent_ਨਿਵੇਸ਼_Haptic_Vibration = 1700,
	EVREvent_Type_VREvent_ਨਿਵੇਸ਼_Binding_ਲੱਦੋ_Failed = 1701,
	EVREvent_Type_VREvent_ਨਿਵੇਸ਼_Binding_ਲੱਦੋ_Successful = 1702,
	EVREvent_Type_VREvent_ਨਿਵੇਸ਼_Action_Manifest_Reloaded = 1703,
	EVREvent_Type_VREvent_ਨਿਵੇਸ਼_Action_Manifest_ਲੱਦੋ_Failed = 1704,
	EVREvent_Type_VREvent_ਨਿਵੇਸ਼_ਤਰੱਕੀ_Update = 1705,
	EVREvent_Type_VREvent_ਨਿਵੇਸ਼_Tracker_Activated = 1706,
	EVREvent_Type_VREvent_ਨਿਵੇਸ਼_Bindings_Updated = 1707,
	EVREvent_Type_VREvent_ਨਿਵੇਸ਼_Binding_Subscription_ਬਦਲਿਆ = 1708,
	EVREventType_VREvent_SpatialAnchors_PoseUpdated = 1800,
	EVREventType_VREvent_SpatialAnchors_DescriptorUpdated = 1801,
	EVREventType_VREvent_SpatialAnchors_RequestPoseUpdate = 1802,
	EVREventType_VREvent_SpatialAnchors_RequestDescriptorUpdate = 1803,
	EVREventType_VREvent_SystemReport_Started = 1900,
	EVREventType_VREvent_Monitor_ShowHeadsetView = 2000,
	EVREventType_VREvent_Monitor_HideHeadsetView = 2001,
	EVREvent_Type_VREvent_Vendor_Specific_Reserved_ਸ਼ੁਰੂ = 10000,
	EVREvent_Type_VREvent_Vendor_Specific_Reserved_ਸਿਰਾ = 19999,
} EVREventType;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ EDeviceActivityLevel
{
	EDeviceActivityLevel_k_EDeviceActivityLevel_Unknown = -1,
	EDeviceActivityLevel_k_EDeviceActivityLevel_Idle = 0,
	EDeviceActivityLevel_k_EDeviceActivityLevel_UserInteraction = 1,
	EDeviceActivityLevel_k_EDeviceActivityLevel_UserInteraction_Timeout = 2,
	EDeviceActivityLevel_k_EDeviceActivityLevel_Standby = 3,
	EDeviceActivityLevel_k_EDeviceActivityLevel_Idle_Timeout = 4,
} EDeviceActivityLevel;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ EVRButtonId
{
	EVRButtonId_k_EButton_System = 0,
	EVRButtonId_k_EButton_ApplicationMenu = 1,
	EVRButtonId_k_EButton_Grip = 2,
	EVRButton_Id_k_EButton_DPad_ਖੱਬਾ = 3,
	EVRButton_Id_k_EButton_DPad_ਉੱਪਰ = 4,
	EVRButton_Id_k_EButton_DPad_ਸੱਜਾ = 5,
	EVRButton_Id_k_EButton_DPad_ਥੱਲੇ = 6,
	EVRButtonId_k_EButton_A = 7,
	EVRButtonId_k_EButton_ProximitySensor = 31,
	EVRButtonId_k_EButton_Axis0 = 32,
	EVRButtonId_k_EButton_Axis1 = 33,
	EVRButtonId_k_EButton_Axis2 = 34,
	EVRButtonId_k_EButton_Axis3 = 35,
	EVRButtonId_k_EButton_Axis4 = 36,
	EVRButtonId_k_EButton_SteamVR_Touchpad = 32,
	EVRButtonId_k_EButton_SteamVR_Trigger = 33,
	EVRButton_Id_k_EButton_Dashboard_ਪਿੱਠ = 2,
	EVRButton_Id_k_EButton_ਸੂਚਕਾਂਕ_Controller_A = 2,
	EVRButton_Id_k_EButton_ਸੂਚਕਾਂਕ_Controller_B = 1,
	EVRButton_Id_k_EButton_ਸੂਚਕਾਂਕ_Controller_Joy_Stick = 35,
	EVRButtonId_k_EButton_Max = 64,
} EVRButtonId;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ EVRMouseButton
{
	EVRMouse_Button_VRMouse_Button_ਖੱਬਾ = 1,
	EVRMouse_Button_VRMouse_Button_ਸੱਜਾ = 2,
	EVRMouse_Button_VRMouse_Button_ਵਿਚਕਾਰ = 4,
} EVRMouseButton;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ EShowUIType
{
	EShowUIType_ShowUI_ControllerBinding = 0,
	EShowUIType_ShowUI_ManageTrackers = 1,
	EShowUIType_ShowUI_Pairing = 3,
	EShowUIType_ShowUI_Settings = 4,
	EShowUIType_ShowUI_DebugCommands = 5,
	EShow_UIType_Show_UI_ਭਰਿਆ_Controller_Binding = 6,
	EShowUIType_ShowUI_ManageDrivers = 7,
} EShowUIType;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ EHDCPError
{
	EHDCPError_HDCPError_None = 0,
	EHDCPError_HDCPError_Link_ਗੁਆਚਾ = 1,
	EHDCPError_HDCPError_Tampered = 2,
	EHDCPError_HDCPError_DeviceRevoked = 3,
	EHDCPError_HDCPError_Unknown = 4,
} EHDCPError;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ EVRComponentProperty
{
	EVRComponentProperty_VRComponentProperty_IsStatic = 1,
	EVRComponentProperty_VRComponentProperty_IsVisible = 2,
	EVRComponentProperty_VRComponentProperty_IsTouched = 4,
	EVRComponentProperty_VRComponentProperty_IsPressed = 8,
	EVRComponentProperty_VRComponentProperty_IsScrolled = 16,
	EVRComponentProperty_VRComponentProperty_IsHighlighted = 32,
} EVRComponentProperty;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ EVRInputError
{
	EVRInputError_VRInputError_None = 0,
	EVRInput_Error_VRInput_Error_Name_Not_ਮਿਲਿਆ = 1,
	EVRInputError_VRInputError_WrongType = 2,
	EVRInputError_VRInputError_InvalidHandle = 3,
	EVRInputError_VRInputError_InvalidParam = 4,
	EVRInputError_VRInputError_NoSteam = 5,
	EVRInput_Error_VRInput_Error_Max_ਸਮਰੱਥਾ_Reached = 6,
	EVRInputError_VRInputError_IPCError = 7,
	EVRInput_Error_VRInput_Error_No_ਸਰਗਰਮ_Action_ਸੈੱਟ = 8,
	EVRInputError_VRInputError_InvalidDevice = 9,
	EVRInputError_VRInputError_InvalidSkeleton = 10,
	EVRInput_Error_VRInput_Error_Invalid_Bone_ਗਿਣਤੀ = 11,
	EVRInput_Error_VRInput_Error_Invalid_Compressed_ਅੰਕੜੇ = 12,
	EVRInput_Error_VRInput_Error_No_ਅੰਕੜੇ = 13,
	EVRInput_Error_VRInput_Error_ਬਫਰ_Too_Small = 14,
	EVRInputError_VRInputError_MismatchedActionManifest = 15,
	EVRInput_Error_VRInput_Error_Missing_Skeleton_ਅੰਕੜੇ = 16,
	EVRInput_Error_VRInput_Error_Invalid_Bone_ਸੂਚਕਾਂਕ = 17,
	EVRInput_Error_VRInput_Error_Invalid_ਤਰਜੀਹ = 18,
	EVRInputError_VRInputError_PermissionDenied = 19,
	EVRInputError_VRInputError_InvalidRenderModel = 20,
} EVRInputError;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ EVRSpatialAnchorError
{
	EVRSpatialAnchorError_VRSpatialAnchorError_Success = 0,
	EVRSpatial_Anchor_Error_VRSpatial_Anchor_Error_ਅੰਦਰੂਨੀ = 1,
	EVRSpatialAnchorError_VRSpatialAnchorError_UnknownHandle = 2,
	EVRSpatialAnchorError_VRSpatialAnchorError_ArrayTooSmall = 3,
	EVRSpatialAnchorError_VRSpatialAnchorError_InvalidDescriptorChar = 4,
	EVRSpatial_Anchor_Error_VRSpatial_Anchor_Error_Not_Yet_ਉਪਲਬਧ = 5,
	EVRSpatial_Anchor_Error_VRSpatial_Anchor_Error_Not_ਉਪਲਬਧ_ਵਿੱਚ_This_Universe = 6,
	EVRSpatialAnchorError_VRSpatialAnchorError_PermanentlyUnavailable = 7,
	EVRSpatialAnchorError_VRSpatialAnchorError_WrongDriver = 8,
	EVRSpatialAnchorError_VRSpatialAnchorError_DescriptorTooLong = 9,
	EVRSpatialAnchorError_VRSpatialAnchorError_Unknown = 10,
	EVRSpatial_Anchor_Error_VRSpatial_Anchor_Error_No_ਗੁੰਜਾਇਸ਼_Calibration = 11,
	EVRSpatial_Anchor_Error_VRSpatial_Anchor_Error_Invalid_ਦਲੀਲ = 12,
	EVRSpatialAnchorError_VRSpatialAnchorError_UnknownDriver = 13,
} EVRSpatialAnchorError;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ EHiddenAreaMeshType
{
	EHiddenAreaMeshType_k_eHiddenAreaMesh_Standard = 0,
	EHiddenAreaMeshType_k_eHiddenAreaMesh_Inverse = 1,
	EHidden_Area_Mesh_Type_k_e_Hidden_Area_Mesh_ਸਤਰ_Loop = 2,
	EHiddenAreaMeshType_k_eHiddenAreaMesh_Max = 3,
} EHiddenAreaMeshType;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ EVRControllerAxisType
{
	EVRControllerAxisType_k_eControllerAxis_None = 0,
	EVRControllerAxisType_k_eControllerAxis_TrackPad = 1,
	EVRControllerAxisType_k_eControllerAxis_Joystick = 2,
	EVRControllerAxisType_k_eControllerAxis_Trigger = 3,
} EVRControllerAxisType;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ EVRControllerEventOutputType
{
	EVRControllerEventOutputType_ControllerEventOutput_OSEvents = 0,
	EVRControllerEventOutputType_ControllerEventOutput_VREvents = 1,
} EVRControllerEventOutputType;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ ECollisionBoundsStyle
{
	ECollisionBoundsStyle_COLLISION_BOUNDS_STYLE_BEGINNER = 0,
	ECollisionBoundsStyle_COLLISION_BOUNDS_STYLE_INTERMEDIATE = 1,
	ECollisionBoundsStyle_COLLISION_BOUNDS_STYLE_SQUARES = 2,
	ECollisionBoundsStyle_COLLISION_BOUNDS_STYLE_ADVANCED = 3,
	ECollisionBoundsStyle_COLLISION_BOUNDS_STYLE_NONE = 4,
	ECollision_Bounds_Style_COLLISION_BOUNDS_STYLE_ਗਿਣਤੀ = 5,
} ECollisionBoundsStyle;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ EVROverlayError
{
	EVROverlayError_VROverlayError_None = 0,
	EVROverlayError_VROverlayError_UnknownOverlay = 10,
	EVROverlayError_VROverlayError_InvalidHandle = 11,
	EVROverlayError_VROverlayError_PermissionDenied = 12,
	EVROverlay_Error_VROverlay_Error_Overlay_ਹੱਦਬੰਦੀ_Exceeded = 13,
	EVROverlayError_VROverlayError_WrongVisibilityType = 14,
	EVROverlay_Error_VROverlay_Error_ਕੁੰਜੀ_Too_Long = 15,
	EVROverlayError_VROverlayError_NameTooLong = 16,
	EVROverlay_Error_VROverlay_Error_ਕੁੰਜੀ_ਵਿੱਚ_Use = 17,
	EVROverlayError_VROverlayError_WrongTransformType = 18,
	EVROverlayError_VROverlayError_InvalidTrackedDevice = 19,
	EVROverlayError_VROverlayError_InvalidParameter = 20,
	EVROverlayError_VROverlayError_ThumbnailCantBeDestroyed = 21,
	EVROverlayError_VROverlayError_ArrayTooSmall = 22,
	EVROverlayError_VROverlayError_RequestFailed = 23,
	EVROverlayError_VROverlayError_InvalidTexture = 24,
	EVROverlay_Error_VROverlay_Error_Unable_ਮੰਜ਼ਿਲ_ਲੱਦੋ_File = 25,
	EVROverlay_Error_VROverlay_Error_Keyboard_Already_ਵਿੱਚ_Use = 26,
	EVROverlayError_VROverlayError_NoNeighbor = 27,
	EVROverlay_Error_VROverlay_Error_Too_Many_ਨਕਾਬ_Primitives = 29,
	EVROverlay_Error_VROverlay_Error_Bad_ਨਕਾਬ_Primitive = 30,
	EVROverlayError_VROverlayError_TextureAlreadyLocked = 31,
	EVROverlay_Error_VROverlay_Error_Texture_ਤਾਲਾ_ਸਮਰੱਥਾ_Reached = 32,
	EVROverlayError_VROverlayError_TextureNotLocked = 33,
	EVROverlay_Error_VROverlay_Error_Timed_ਬਾਹਰਲਾ = 34,
} EVROverlayError;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ EVRApplicationType
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
	EVRApplication_Type_VRApplication_ਗੁੰਜਾਇਸ਼_View = 13,
	EVRApplicationType_VRApplication_Max = 14,
} EVRApplicationType;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ EVRFirmwareError
{
	EVRFirmwareError_VRFirmwareError_None = 0,
	EVRFirmwareError_VRFirmwareError_Success = 1,
	EVRFirmwareError_VRFirmwareError_Fail = 2,
} EVRFirmwareError;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ EVRNotificationError
{
	EVRNotificationError_VRNotificationError_OK = 0,
	EVRNotificationError_VRNotificationError_InvalidNotificationId = 100,
	EVRNotification_Error_VRNotification_Error_Notification_ਕਤਾਰ_ਭਰਿਆ = 101,
	EVRNotificationError_VRNotificationError_InvalidOverlayHandle = 102,
	EVRNotification_Error_VRNotification_Error_System_With_User_ਮੁੱਲ_Already_Exists = 103,
} EVRNotificationError;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ EVRSkeletalMotionRange
{
	EVRSkeletalMotionRange_VRSkeletalMotionRange_WithController = 0,
	EVRSkeletalMotionRange_VRSkeletalMotionRange_WithoutController = 1,
} EVRSkeletalMotionRange;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ EVRSkeletalTrackingLevel
{
	EVRSkeletalTrackingLevel_VRSkeletalTracking_Estimated = 0,
	EVRSkeletalTrackingLevel_VRSkeletalTracking_Partial = 1,
	EVRSkeletal_Tracking_Level_VRSkeletal_Tracking_ਭਰਿਆ = 2,
	EVRSkeletal_Tracking_Level_VRSkeletal_Tracking_Level_ਗਿਣਤੀ = 3,
	EVRSkeletalTrackingLevel_VRSkeletalTrackingLevel_Max = 2,
} EVRSkeletalTrackingLevel;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ EVRInitError
{
	EVRInitError_VRInitError_None = 0,
	EVRInitError_VRInitError_Unknown = 1,
	EVRInit_Error_VRInit_Error_Init_Installation_Not_ਮਿਲਿਆ = 100,
	EVRInitError_VRInitError_Init_InstallationCorrupt = 101,
	EVRInit_Error_VRInit_Error_Init_VRClient_DLLNot_ਮਿਲਿਆ = 102,
	EVRInit_Error_VRInit_Error_Init_File_Not_ਮਿਲਿਆ = 103,
	EVRInit_Error_VRInit_Error_Init_Factory_Not_ਮਿਲਿਆ = 104,
	EVRInit_Error_VRInit_Error_Init_Interface_Not_ਮਿਲਿਆ = 105,
	EVRInitError_VRInitError_Init_InvalidInterface = 106,
	EVRInitError_VRInitError_Init_UserConfigDirectoryInvalid = 107,
	EVRInit_Error_VRInit_Error_Init_Hmd_Not_ਮਿਲਿਆ = 108,
	EVRInitError_VRInitError_Init_NotInitialized = 109,
	EVRInit_Error_VRInit_Error_Init_ਰਸਤਾ_Registry_Not_ਮਿਲਿਆ = 110,
	EVRInit_Error_VRInit_Error_Init_No_Config_ਰਸਤਾ = 111,
	EVRInit_Error_VRInit_Error_Init_No_Log_ਰਸਤਾ = 112,
	EVRInit_Error_VRInit_Error_Init_ਰਸਤਾ_Registry_Not_Writable = 113,
	EVRInitError_VRInitError_Init_AppInfoInitFailed = 114,
	EVRInitError_VRInitError_Init_Retry = 115,
	EVRInitError_VRInitError_Init_InitCanceledByUser = 116,
	EVRInitError_VRInitError_Init_AnotherAppLaunching = 117,
	EVRInitError_VRInitError_Init_SettingsInitFailed = 118,
	EVRInit_Error_VRInit_Error_Init_Shutting_ਥੱਲੇ = 119,
	EVRInitError_VRInitError_Init_TooManyObjects = 120,
	EVRInitError_VRInitError_Init_NoServerForBackgroundApp = 121,
	EVRInitError_VRInitError_Init_NotSupportedWithCompositor = 122,
	EVRInit_Error_VRInit_Error_Init_Not_ਉਪਲਬਧ_ਮੰਜ਼ਿਲ_Utility_Apps = 123,
	EVRInit_Error_VRInit_Error_Init_ਅੰਦਰੂਨੀ = 124,
	EVRInitError_VRInitError_Init_HmdDriverIdIsNone = 125,
	EVRInit_Error_VRInit_Error_Init_Hmd_Not_ਮਿਲਿਆ_Presence_Failed = 126,
	EVRInit_Error_VRInit_Error_Init_VRMonitor_Not_ਮਿਲਿਆ = 127,
	EVRInitError_VRInitError_Init_VRMonitorStartupFailed = 128,
	EVRInit_Error_VRInit_Error_Init_ਨੀਵਾਂ_Power_Watchdog_Not_Supported = 129,
	EVRInitError_VRInitError_Init_InvalidApplicationType = 130,
	EVRInit_Error_VRInit_Error_Init_Not_ਉਪਲਬਧ_ਮੰਜ਼ਿਲ_Watchdog_Apps = 131,
	EVRInit_Error_VRInit_Error_Init_Watchdog_Disabled_ਵਿੱਚ_Settings = 132,
	EVRInit_Error_VRInit_Error_Init_VRDashboard_Not_ਮਿਲਿਆ = 133,
	EVRInitError_VRInitError_Init_VRDashboardStartupFailed = 134,
	EVRInit_Error_VRInit_Error_Init_VRHome_Not_ਮਿਲਿਆ = 135,
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
	EVRInit_Error_VRInit_Error_Init_Prism_Startup_Timed_ਬਾਹਰਲਾ = 152,
	EVRInit_Error_VRInit_Error_Init_Could_Not_ਸ਼ੁਰੂ_Prism = 153,
	EVRInitError_VRInitError_Init_PrismClientInitFailed = 154,
	EVRInit_Error_VRInit_Error_Init_Prism_Client_ਸ਼ੁਰੂ_Failed = 155,
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
	EVRInit_Error_VRInit_Error_Init_VRDashboard_ਰਸਤਾ_Failure = 167,
	EVRInitError_VRInitError_Driver_Failed = 200,
	EVRInitError_VRInitError_Driver_Unknown = 201,
	EVRInitError_VRInitError_Driver_HmdUnknown = 202,
	EVRInitError_VRInitError_Driver_NotLoaded = 203,
	EVRInit_Error_VRInit_Error_Driver_Runtime_ਬਾਹਰਲਾ_ਦਾ_Date = 204,
	EVRInit_Error_VRInit_Error_Driver_Hmd_ਵਿੱਚ_Use = 205,
	EVRInitError_VRInitError_Driver_NotCalibrated = 206,
	EVRInitError_VRInitError_Driver_CalibrationInvalid = 207,
	EVRInit_Error_VRInit_Error_Driver_Hmd_Display_Not_ਮਿਲਿਆ = 208,
	EVRInitError_VRInitError_Driver_TrackedDeviceInterfaceUnknown = 209,
	EVRInit_Error_VRInit_Error_Driver_Hmd_Driver_Id_ਬਾਹਰਲਾ_ਦਾ_Bounds = 211,
	EVRInitError_VRInitError_Driver_HmdDisplayMirrored = 212,
	EVRInit_Error_VRInit_Error_Driver_Hmd_Display_Not_ਮਿਲਿਆ_Laptop = 213,
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
	EVRInit_Error_VRInit_Error_IPC_Connect_Failed_After_ਗੁਣਜ_Attempts = 308,
	EVRInit_Error_VRInit_Error_IPC_Connect_Failed_After_ਨਿਸ਼ਾਨਾ_Exited = 309,
	EVRInitError_VRInitError_IPC_NamespaceUnavailable = 310,
	EVRInitError_VRInitError_Compositor_Failed = 400,
	EVRInitError_VRInitError_Compositor_D3D11HardwareRequired = 401,
	EVRInitError_VRInitError_Compositor_FirmwareRequiresUpdate = 402,
	EVRInitError_VRInitError_Compositor_OverlayInitFailed = 403,
	EVRInitError_VRInitError_Compositor_ScreenshotsInitFailed = 404,
	EVRInit_Error_VRInit_Error_Compositor_Unable_ਮੰਜ਼ਿਲ_Create_Device = 405,
	EVRInitError_VRInitError_Compositor_SharedStateIsNull = 406,
	EVRInitError_VRInitError_Compositor_NotificationManagerIsNull = 407,
	EVRInitError_VRInitError_Compositor_ResourceManagerClientIsNull = 408,
	EVRInit_Error_VRInit_Error_Compositor_ਸੁਨੇਹਾ_Overlay_Shared_State_Init_Failure = 409,
	EVRInitError_VRInitError_Compositor_PropertiesInterfaceIsNull = 410,
	EVRInit_Error_VRInit_Error_Compositor_Create_Fullscreen_ਖਿੜਕੀ_Failed = 411,
	EVRInitError_VRInitError_Compositor_SettingsInterfaceIsNull = 412,
	EVRInit_Error_VRInit_Error_Compositor_Failed_ਮੰਜ਼ਿਲ_Show_ਖਿੜਕੀ = 413,
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
	EVRInit_Error_VRInit_Error_Compositor_Failed_ਮੰਜ਼ਿਲ_ਲੱਭੋ_Display_ਬਹੁਲਕ = 425,
	EVRInit_Error_VRInit_Error_Compositor_Failed_ਮੰਜ਼ਿਲ_Create_ਅਦਲਾ_ਬਦਲੀ_Chain = 426,
	EVRInit_Error_VRInit_Error_Compositor_Failed_ਮੰਜ਼ਿਲ_Get_ਪਿੱਠ_ਬਫਰ = 427,
	EVRInit_Error_VRInit_Error_Compositor_Failed_ਮੰਜ਼ਿਲ_Create_Render_ਨਿਸ਼ਾਨਾ = 428,
	EVRInit_Error_VRInit_Error_Compositor_Failed_ਮੰਜ਼ਿਲ_Create_DXGI2_ਅਦਲਾ_ਬਦਲੀ_Chain = 429,
	EVRInit_Error_VRInit_Error_Compositor_Failedto_Get_DXGI2_ਪਿੱਠ_ਬਫਰ = 430,
	EVRInit_Error_VRInit_Error_Compositor_Failed_ਮੰਜ਼ਿਲ_Create_DXGI2_Render_ਨਿਸ਼ਾਨਾ = 431,
	EVRInit_Error_VRInit_Error_Compositor_Failed_ਮੰਜ਼ਿਲ_Get_DXGIDevice_Interface = 432,
	EVRInit_Error_VRInit_Error_Compositor_Select_Display_ਬਹੁਲਕ = 433,
	EVRInit_Error_VRInit_Error_Compositor_Failed_ਮੰਜ਼ਿਲ_Create_Nv_APIRender_Targets = 434,
	EVRInit_Error_VRInit_Error_Compositor_Nv_APISet_Display_ਬਹੁਲਕ = 435,
	EVRInit_Error_VRInit_Error_Compositor_Failed_ਮੰਜ਼ਿਲ_Create_ਸਿੱਧਾ_ਬਹੁਲਕ_Display = 436,
	EVRInitError_VRInitError_Compositor_InvalidHmdPropertyContainer = 437,
	EVRInitError_VRInitError_Compositor_UpdateDisplayFrequency = 438,
	EVRInitError_VRInitError_Compositor_CreateRasterizerState = 439,
	EVRInitError_VRInitError_Compositor_CreateWireframeRasterizerState = 440,
	EVRInitError_VRInitError_Compositor_CreateSamplerState = 441,
	EVRInit_Error_VRInit_Error_Compositor_Create_Clamp_ਮੰਜ਼ਿਲ_Border_Sampler_State = 442,
	EVRInitError_VRInitError_Compositor_CreateAnisoSamplerState = 443,
	EVRInitError_VRInitError_Compositor_CreateOverlaySamplerState = 444,
	EVRInitError_VRInitError_Compositor_CreatePanoramaSamplerState = 445,
	EVRInitError_VRInitError_Compositor_CreateFontSamplerState = 446,
	EVRInitError_VRInitError_Compositor_CreateNoBlendState = 447,
	EVRInitError_VRInitError_Compositor_CreateBlendState = 448,
	EVRInitError_VRInitError_Compositor_CreateAlphaBlendState = 449,
	EVRInit_Error_VRInit_Error_Compositor_Create_Blend_State_ਨਕਾਬ_R = 450,
	EVRInit_Error_VRInit_Error_Compositor_Create_Blend_State_ਨਕਾਬ_G = 451,
	EVRInit_Error_VRInit_Error_Compositor_Create_Blend_State_ਨਕਾਬ_B = 452,
	EVRInit_Error_VRInit_Error_Compositor_Create_ਡੂੰਘਾਈ_Stencil_State = 453,
	EVRInit_Error_VRInit_Error_Compositor_Create_ਡੂੰਘਾਈ_Stencil_State_No_Write = 454,
	EVRInit_Error_VRInit_Error_Compositor_Create_ਡੂੰਘਾਈ_Stencil_State_No_ਡੂੰਘਾਈ = 455,
	EVRInitError_VRInitError_Compositor_CreateFlushTexture = 456,
	EVRInitError_VRInitError_Compositor_CreateDistortionSurfaces = 457,
	EVRInit_Error_VRInit_Error_Compositor_Create_Constant_ਬਫਰ = 458,
	EVRInit_Error_VRInit_Error_Compositor_Create_Hmd_Pose_Constant_ਬਫਰ = 459,
	EVRInit_Error_VRInit_Error_Compositor_Create_Hmd_Pose_Staging_Constant_ਬਫਰ = 460,
	EVRInit_Error_VRInit_Error_Compositor_Create_Shared_ਚੌਖਟਾ_Info_Constant_ਬਫਰ = 461,
	EVRInit_Error_VRInit_Error_Compositor_Create_Overlay_Constant_ਬਫਰ = 462,
	EVRInit_Error_VRInit_Error_Compositor_Create_Scene_Texture_ਸੂਚਕਾਂਕ_Constant_ਬਫਰ = 463,
	EVRInit_Error_VRInit_Error_Compositor_Create_Readable_Scene_Texture_ਸੂਚਕਾਂਕ_Constant_ਬਫਰ = 464,
	EVRInit_Error_VRInit_Error_Compositor_Create_Layer_Graphics_Texture_ਸੂਚਕਾਂਕ_Constant_ਬਫਰ = 465,
	EVRInit_Error_VRInit_Error_Compositor_Create_Layer_Compute_Texture_ਸੂਚਕਾਂਕ_Constant_ਬਫਰ = 466,
	EVRInit_Error_VRInit_Error_Compositor_Create_Layer_Compute_Scene_Texture_ਸੂਚਕਾਂਕ_Constant_ਬਫਰ = 467,
	EVRInit_Error_VRInit_Error_Compositor_Create_Compute_Hmd_Pose_Constant_ਬਫਰ = 468,
	EVRInit_Error_VRInit_Error_Compositor_Create_Geom_Constant_ਬਫਰ = 469,
	EVRInit_Error_VRInit_Error_Compositor_Create_Panel_ਨਕਾਬ_Constant_ਬਫਰ = 470,
	EVRInitError_VRInitError_Compositor_CreatePixelSimUBO = 471,
	EVRInitError_VRInitError_Compositor_CreateMSAARenderTextures = 472,
	EVRInitError_VRInitError_Compositor_CreateResolveRenderTextures = 473,
	EVRInitError_VRInitError_Compositor_CreateComputeResolveRenderTextures = 474,
	EVRInit_Error_VRInit_Error_Compositor_Create_Driver_ਸਿੱਧਾ_ਬਹੁਲਕ_Resolve_Textures = 475,
	EVRInit_Error_VRInit_Error_Compositor_Open_Driver_ਸਿੱਧਾ_ਬਹੁਲਕ_Resolve_Textures = 476,
	EVRInitError_VRInitError_Compositor_CreateFallbackSyncTexture = 477,
	EVRInitError_VRInitError_Compositor_ShareFallbackSyncTexture = 478,
	EVRInit_Error_VRInit_Error_Compositor_Create_Overlay_ਸੂਚਕਾਂਕ_ਬਫਰ = 479,
	EVRInit_Error_VRInit_Error_Compositor_Create_Overlay_ਸ਼ੀਰਸ਼_ਬਫਰ = 480,
	EVRInit_Error_VRInit_Error_Compositor_Create_ਪਾਠ_ਸ਼ੀਰਸ਼_ਬਫਰ = 481,
	EVRInit_Error_VRInit_Error_Compositor_Create_ਪਾਠ_ਸੂਚਕਾਂਕ_ਬਫਰ = 482,
	EVRInitError_VRInitError_Compositor_CreateMirrorTextures = 483,
	EVRInit_Error_VRInit_Error_Compositor_Create_ਆਖਰੀ_ਚੌਖਟਾ_Render_Texture = 484,
	EVRInitError_VRInitError_Compositor_CreateMirrorOverlay = 485,
	EVRInit_Error_VRInit_Error_Compositor_Failed_ਮੰਜ਼ਿਲ_Create_Virtual_Display_Backbuffer = 486,
	EVRInit_Error_VRInit_Error_Compositor_Display_ਬਹੁਲਕ_Not_Supported = 487,
	EVRInitError_VRInitError_Compositor_CreateOverlayInvalidCall = 488,
	EVRInitError_VRInitError_Compositor_CreateOverlayAlreadyInitialized = 489,
	EVRInit_Error_VRInit_Error_Compositor_Failed_ਮੰਜ਼ਿਲ_Create_Mailbox = 490,
	EVRInit_Error_VRInit_Error_Compositor_ਖਿੜਕੀ_Interface_Is_Null = 491,
	EVRInitError_VRInitError_Compositor_SystemLayerCreateInstance = 492,
	EVRInitError_VRInitError_Compositor_SystemLayerCreateSession = 493,
	EVRInitError_VRInitError_Compoistor_CreateInverseDistortUVs = 494,
	EVRInit_Error_VRInit_Error_Compoistor_Create_Backbuffer_ਡੂੰਘਾਈ = 495,
	EVRInit_Error_VRInit_Error_Vendor_Specific_Unable_ਮੰਜ਼ਿਲ_Connect_ਮੰਜ਼ਿਲ_Oculus_Runtime = 1000,
	EVRInit_Error_VRInit_Error_Vendor_Specific_Windows_Not_ਵਿੱਚ_Dev_ਬਹੁਲਕ = 1001,
	EVRInitError_VRInitError_VendorSpecific_OculusLinkNotEnabled = 1002,
	EVRInit_Error_VRInit_Error_Vendor_Specific_Hmd_ਮਿਲਿਆ_Cant_Open_Device = 1101,
	EVRInit_Error_VRInit_Error_Vendor_Specific_Hmd_ਮਿਲਿਆ_Unable_ਮੰਜ਼ਿਲ_Request_Config_ਸ਼ੁਰੂ = 1102,
	EVRInit_Error_VRInit_Error_Vendor_Specific_Hmd_ਮਿਲਿਆ_No_Stored_Config = 1103,
	EVRInit_Error_VRInit_Error_Vendor_Specific_Hmd_ਮਿਲਿਆ_Config_Too_Big = 1104,
	EVRInit_Error_VRInit_Error_Vendor_Specific_Hmd_ਮਿਲਿਆ_Config_Too_Small = 1105,
	EVRInit_Error_VRInit_Error_Vendor_Specific_Hmd_ਮਿਲਿਆ_Unable_ਮੰਜ਼ਿਲ_Init_ZLib = 1106,
	EVRInit_Error_VRInit_Error_Vendor_Specific_Hmd_ਮਿਲਿਆ_Cant_Read_Firmware_ਸੰਸਕਰਣ = 1107,
	EVRInit_Error_VRInit_Error_Vendor_Specific_Hmd_ਮਿਲਿਆ_Unable_ਮੰਜ਼ਿਲ_Send_User_ਅੰਕੜੇ_ਸ਼ੁਰੂ = 1108,
	EVRInit_Error_VRInit_Error_Vendor_Specific_Hmd_ਮਿਲਿਆ_Unable_ਮੰਜ਼ਿਲ_Get_User_ਅੰਕੜੇ_ਸ਼ੁਰੂ = 1109,
	EVRInit_Error_VRInit_Error_Vendor_Specific_Hmd_ਮਿਲਿਆ_Unable_ਮੰਜ਼ਿਲ_Get_User_ਅੰਕੜੇ_ਅਗਲਾ = 1110,
	EVRInit_Error_VRInit_Error_Vendor_Specific_Hmd_ਮਿਲਿਆ_User_ਅੰਕੜੇ_ਪਤਾ_Range = 1111,
	EVRInit_Error_VRInit_Error_Vendor_Specific_Hmd_ਮਿਲਿਆ_User_ਅੰਕੜੇ_Error = 1112,
	EVRInit_Error_VRInit_Error_Vendor_Specific_Hmd_ਮਿਲਿਆ_Config_Failed_Sanity_Check = 1113,
	EVRInitError_VRInitError_VendorSpecific_OculusRuntimeBadInstall = 1114,
	EVRInit_Error_VRInit_Error_Vendor_Specific_Hmd_ਮਿਲਿਆ_Unexpected_Configuration_1 = 1115,
	EVRInit_Error_VRInit_Error_Steam_Steam_Installation_Not_ਮਿਲਿਆ = 2000,
	EVRInit_Error_VRInit_Error_ਆਖਰੀ_Error = 2001,
} EVRInitError;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ EVRScreenshotType
{
	EVRScreenshotType_VRScreenshotType_None = 0,
	EVRScreenshotType_VRScreenshotType_Mono = 1,
	EVRScreenshotType_VRScreenshotType_Stereo = 2,
	EVRScreenshotType_VRScreenshotType_Cubemap = 3,
	EVRScreenshotType_VRScreenshotType_MonoPanorama = 4,
	EVRScreenshotType_VRScreenshotType_StereoPanorama = 5,
} EVRScreenshotType;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ EVRScreenshotPropertyFilenames
{
	EVRScreenshotPropertyFilenames_VRScreenshotPropertyFilenames_Preview = 0,
	EVRScreenshotPropertyFilenames_VRScreenshotPropertyFilenames_VR = 1,
} EVRScreenshotPropertyFilenames;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ EVRTrackedCameraError
{
	EVRTrackedCameraError_VRTrackedCameraError_None = 0,
	EVRTrackedCameraError_VRTrackedCameraError_OperationFailed = 100,
	EVRTrackedCameraError_VRTrackedCameraError_InvalidHandle = 101,
	EVRTracked_Camera_Error_VRTracked_Camera_Error_Invalid_ਚੌਖਟਾ_ਸਿਰਲੇਖ_ਸੰਸਕਰਣ = 102,
	EVRTracked_Camera_Error_VRTracked_Camera_Error_ਬਾਹਰਲਾ_ਦਾ_Handles = 103,
	EVRTrackedCameraError_VRTrackedCameraError_IPCFailure = 104,
	EVRTrackedCameraError_VRTrackedCameraError_NotSupportedForThisDevice = 105,
	EVRTracked_Camera_Error_VRTracked_Camera_Error_Shared_ਸਮ੍ਰਿਤੀ_Failure = 106,
	EVRTracked_Camera_Error_VRTracked_Camera_Error_ਚੌਖਟਾ_Buffering_Failure = 107,
	EVRTracked_Camera_Error_VRTracked_Camera_Error_ਧਾਰਾ_ਤਿਆਰੀ_Failure = 108,
	EVRTrackedCameraError_VRTrackedCameraError_InvalidGLTextureId = 109,
	EVRTrackedCameraError_VRTrackedCameraError_InvalidSharedTextureHandle = 110,
	EVRTracked_Camera_Error_VRTracked_Camera_Error_Failed_ਮੰਜ਼ਿਲ_Get_GLTexture_Id = 111,
	EVRTrackedCameraError_VRTrackedCameraError_SharedTextureFailure = 112,
	EVRTracked_Camera_Error_VRTracked_Camera_Error_No_ਚੌਖਟਾ_ਉਪਲਬਧ = 113,
	EVRTracked_Camera_Error_VRTracked_Camera_Error_Invalid_ਦਲੀਲ = 114,
	EVRTracked_Camera_Error_VRTracked_Camera_Error_Invalid_ਚੌਖਟਾ_ਬਫਰ_ਮਾਪ = 115,
} EVRTrackedCameraError;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ EVRTracked_Camera_ਚੌਖਟਾ_Layout
{
	EVRTracked_Camera_ਚੌਖਟਾ_Layout_Mono = 1,
	EVRTracked_Camera_ਚੌਖਟਾ_Layout_Stereo = 2,
	EVRTracked_Camera_ਚੌਖਟਾ_Layout_Vertical_Layout = 16,
	EVRTracked_Camera_ਚੌਖਟਾ_Layout_Horizontal_Layout = 32,
} EVRTracked_Camera_ਚੌਖਟਾ_Layout;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ EVRTracked_Camera_ਚੌਖਟਾ_Type
{
	EVRTracked_Camera_ਚੌਖਟਾ_Type_VRTracked_Camera_ਚੌਖਟਾ_Type_Distorted = 0,
	EVRTracked_Camera_ਚੌਖਟਾ_Type_VRTracked_Camera_ਚੌਖਟਾ_Type_Undistorted = 1,
	EVRTracked_Camera_ਚੌਖਟਾ_Type_VRTracked_Camera_ਚੌਖਟਾ_Type_ਵੱਧ_ਤੋਂ_ਵੱਧ_Undistorted = 2,
	EVRTracked_Camera_ਚੌਖਟਾ_Type_MAX_CAMERA_ਚੌਖਟਾ_TYPES = 3,
} EVRTracked_Camera_ਚੌਖਟਾ_Type;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ EVRDistortionFunctionType
{
	EVRDistortionFunctionType_VRDistortionFunctionType_None = 0,
	EVRDistortionFunctionType_VRDistortionFunctionType_FTheta = 1,
	EVRDistortionFunctionType_VRDistortionFunctionType_Extended_FTheta = 2,
	EVRDistortionFunctionType_MAX_DISTORTION_FUNCTION_TYPES = 3,
} EVRDistortionFunctionType;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ EVSync
{
	EVSync_VSync_None = 0,
	EVSync_VSync_WaitRender = 1,
	EVSync_VSync_NoWaitRender = 2,
} EVSync;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ EVRMura_Correction_ਬਹੁਲਕ
{
	EVRMura_Correction_ਬਹੁਲਕ_Default = 0,
	EVRMura_Correction_ਬਹੁਲਕ_No_Correction = 1,
} EVRMura_Correction_ਬਹੁਲਕ;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ Imu_OffScaleFlags
{
	Imu_OffScaleFlags_OffScale_AccelX = 1,
	Imu_OffScaleFlags_OffScale_AccelY = 2,
	Imu_OffScaleFlags_OffScale_AccelZ = 4,
	Imu_OffScaleFlags_OffScale_GyroX = 8,
	Imu_OffScaleFlags_OffScale_GyroY = 16,
	Imu_OffScaleFlags_OffScale_GyroZ = 32,
} Imu_OffScaleFlags;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ EVRApplicationError
{
	EVRApplicationError_VRApplicationError_None = 0,
	EVRApplication_Error_VRApplication_Error_App_ਕੁੰਜੀ_Already_Exists = 100,
	EVRApplicationError_VRApplicationError_NoManifest = 101,
	EVRApplicationError_VRApplicationError_NoApplication = 102,
	EVRApplication_Error_VRApplication_Error_Invalid_ਸੂਚਕਾਂਕ = 103,
	EVRApplicationError_VRApplicationError_UnknownApplication = 104,
	EVRApplicationError_VRApplicationError_IPCFailed = 105,
	EVRApplicationError_VRApplicationError_ApplicationAlreadyRunning = 106,
	EVRApplicationError_VRApplicationError_InvalidManifest = 107,
	EVRApplicationError_VRApplicationError_InvalidApplication = 108,
	EVRApplicationError_VRApplicationError_LaunchFailed = 109,
	EVRApplicationError_VRApplicationError_ApplicationAlreadyStarting = 110,
	EVRApplication_Error_VRApplication_Error_Launch_ਵਿੱਚ_ਤਰੱਕੀ = 111,
	EVRApplicationError_VRApplicationError_OldApplicationQuitting = 112,
	EVRApplicationError_VRApplicationError_TransitionAborted = 113,
	EVRApplicationError_VRApplicationError_IsTemplate = 114,
	EVRApplicationError_VRApplicationError_SteamVRIsExiting = 115,
	EVRApplication_Error_VRApplication_Error_ਬਫਰ_Too_Small = 200,
	EVRApplication_Error_VRApplication_Error_Property_Not_ਸੈੱਟ = 201,
	EVRApplicationError_VRApplicationError_UnknownProperty = 202,
	EVRApplicationError_VRApplicationError_InvalidParameter = 203,
	EVRApplicationError_VRApplicationError_NotImplemented = 300,
} EVRApplicationError;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ EVRApplicationProperty
{
	EVRApplicationProperty_VRApplicationProperty_Name_String = 0,
	EVRApplicationProperty_VRApplicationProperty_LaunchType_String = 11,
	EVRApplicationProperty_VRApplicationProperty_WorkingDirectory_String = 12,
	EVRApplication_Property_VRApplication_Property_ਦੁਆਧਾਰੀ_ਰਸਤਾ_String = 13,
	EVRApplicationProperty_VRApplicationProperty_Arguments_String = 14,
	EVRApplicationProperty_VRApplicationProperty_URL_String = 15,
	EVRApplicationProperty_VRApplicationProperty_Description_String = 50,
	EVRApplicationProperty_VRApplicationProperty_NewsURL_String = 51,
	EVRApplication_Property_VRApplication_Property_Image_ਰਸਤਾ_String = 52,
	EVRApplication_Property_VRApplication_Property_ਸਰੋਤ_String = 53,
	EVRApplicationProperty_VRApplicationProperty_ActionManifestURL_String = 54,
	EVRApplicationProperty_VRApplicationProperty_IsDashboardOverlay_Bool = 60,
	EVRApplicationProperty_VRApplicationProperty_IsTemplate_Bool = 61,
	EVRApplicationProperty_VRApplicationProperty_IsInstanced_Bool = 62,
	EVRApplication_Property_VRApplication_Property_Is_ਅੰਦਰੂਨੀ_Bool = 63,
	EVRApplication_Property_VRApplication_Property_ਚਾਹੁੰਦਾ_Compositor_Pause_ਵਿੱਚ_Standby_Bool = 64,
	EVRApplicationProperty_VRApplicationProperty_IsHidden_Bool = 65,
	EVRApplication_Property_VRApplication_Property_ਆਖਰੀ_Launch_ਸਮਾਂ_Uint64 = 70,
} EVRApplicationProperty;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ EVRSceneApplicationState
{
	EVRSceneApplicationState_None = 0,
	EVRSceneApplicationState_Starting = 1,
	EVRSceneApplicationState_Quitting = 2,
	EVRSceneApplicationState_Running = 3,
	EVRScene_Application_State_ਉਡੀਕ = 4,
} EVRSceneApplicationState;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ ChaperoneCalibrationState
{
	ChaperoneCalibrationState_OK = 1,
	ChaperoneCalibrationState_Warning = 100,
	Chaperone_Calibration_State_Warning_ਅਧਾਰ_Station_May_Have_Moved = 101,
	Chaperone_Calibration_State_Warning_ਅਧਾਰ_Station_Removed = 102,
	ChaperoneCalibrationState_Warning_SeatedBoundsInvalid = 103,
	ChaperoneCalibrationState_Error = 200,
	Chaperone_Calibration_State_Error_ਅਧਾਰ_Station_Uninitialized = 201,
	Chaperone_Calibration_State_Error_ਅਧਾਰ_Station_Conflict = 202,
	ChaperoneCalibrationState_Error_PlayAreaInvalid = 203,
	ChaperoneCalibrationState_Error_CollisionBoundsInvalid = 204,
} ChaperoneCalibrationState;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ EChaperoneConfigFile
{
	EChaperone_Config_File_ਜੀਵਤ = 1,
	EChaperone_Config_File_ਆਰਜ਼ੀ = 2,
} EChaperoneConfigFile;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ EChaperoneImportFlags
{
	EChaperoneImportFlags_EChaperoneImport_BoundsOnly = 1,
} EChaperoneImportFlags;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ EVRCompositorError
{
	EVRCompositorError_VRCompositorError_None = 0,
	EVRCompositorError_VRCompositorError_RequestFailed = 1,
	EVRCompositor_Error_VRCompositor_Error_Incompatible_ਸੰਸਕਰਣ = 100,
	EVRCompositorError_VRCompositorError_DoNotHaveFocus = 101,
	EVRCompositorError_VRCompositorError_InvalidTexture = 102,
	EVRCompositorError_VRCompositorError_IsNotSceneApplication = 103,
	EVRCompositorError_VRCompositorError_TextureIsOnWrongDevice = 104,
	EVRCompositor_Error_VRCompositor_Error_Texture_ਵਰਤਦਾ_Unsupported_Format = 105,
	EVRCompositorError_VRCompositorError_SharedTexturesNotSupported = 106,
	EVRCompositor_Error_VRCompositor_Error_ਸੂਚਕਾਂਕ_ਬਾਹਰਲਾ_ਦਾ_Range = 107,
	EVRCompositorError_VRCompositorError_AlreadySubmitted = 108,
	EVRCompositorError_VRCompositorError_InvalidBounds = 109,
	EVRCompositor_Error_VRCompositor_Error_Already_ਸੈੱਟ = 110,
} EVRCompositorError;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ EVRCompositor_Timing_ਬਹੁਲਕ
{
	EVRCompositor_Timing_ਬਹੁਲਕ_VRCompositor_Timing_ਬਹੁਲਕ_Implicit = 0,
	EVRCompositor_Timing_ਬਹੁਲਕ_VRCompositor_Timing_ਬਹੁਲਕ_Explicit_Runtime_Performs_Post_Present_Handoff = 1,
	EVRCompositor_Timing_ਬਹੁਲਕ_VRCompositor_Timing_ਬਹੁਲਕ_Explicit_Application_Performs_Post_Present_Handoff = 2,
} EVRCompositor_Timing_ਬਹੁਲਕ;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ VROverlay_ਨਿਵੇਸ਼_ਵਿਧੀ
{
	VROverlay_ਨਿਵੇਸ਼_ਵਿਧੀ_None = 0,
	VROverlay_ਨਿਵੇਸ਼_ਵਿਧੀ_Mouse = 1,
} VROverlay_ਨਿਵੇਸ਼_ਵਿਧੀ;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ VROverlayTransformType
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

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ VROverlayFlags
{
	VROverlayFlags_NoDashboardTab = 8,
	VROverlayFlags_SendVRDiscreteScrollEvents = 64,
	VROverlayFlags_SendVRTouchpadEvents = 128,
	VROverlayFlags_ShowTouchPadScrollWheel = 256,
	VROverlay_Flags_Transfer_Ownership_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_Process = 512,
	VROverlayFlags_SideBySide_Parallel = 1024,
	VROverlayFlags_SideBySide_Crossed = 2048,
	VROverlayFlags_Panorama = 4096,
	VROverlayFlags_StereoPanorama = 8192,
	VROverlay_Flags_ਛਾਂਟੋ_With_Non_Scene_Overlays = 16384,
	VROverlay_Flags_Visible_ਵਿੱਚ_Dashboard = 32768,
	VROverlayFlags_MakeOverlaysInteractiveIfVisible = 65536,
	VROverlayFlags_SendVRSmoothScrollEvents = 131072,
	VROverlayFlags_ProtectedContent = 262144,
	VROverlayFlags_HideLaserIntersection = 524288,
	VROverlay_Flags_ਚਾਹੁੰਦਾ_Modal_Behavior = 1048576,
	VROverlayFlags_IsPremultiplied = 2097152,
	VROverlayFlags_IgnoreTextureAlpha = 4194304,
	VROverlayFlags_EnableControlBar = 8388608,
	VROverlayFlags_EnableControlBarKeyboard = 16777216,
	VROverlayFlags_EnableControlBarClose = 33554432,
} VROverlayFlags;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ VRMessageOverlayResponse
{
	VRMessageOverlayResponse_ButtonPress_0 = 0,
	VRMessageOverlayResponse_ButtonPress_1 = 1,
	VRMessageOverlayResponse_ButtonPress_2 = 2,
	VRMessageOverlayResponse_ButtonPress_3 = 3,
	VRMessage_Overlay_Response_Couldnt_ਲੱਭੋ_System_Overlay = 4,
	VRMessage_Overlay_Response_Couldnt_ਲੱਭੋ_Or_Create_Client_Overlay = 5,
	VRMessageOverlayResponse_ApplicationQuit = 6,
} VRMessageOverlayResponse;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ EGamepad_ਪਾਠ_ਨਿਵੇਸ਼_ਬਹੁਲਕ
{
	EGamepad_ਪਾਠ_ਨਿਵੇਸ਼_ਬਹੁਲਕ_k_EGamepad_ਪਾਠ_ਨਿਵੇਸ਼_ਬਹੁਲਕ_ਸਾਧਾਰਨ = 0,
	EGamepad_ਪਾਠ_ਨਿਵੇਸ਼_ਬਹੁਲਕ_k_EGamepad_ਪਾਠ_ਨਿਵੇਸ਼_ਬਹੁਲਕ_Password = 1,
	EGamepad_ਪਾਠ_ਨਿਵੇਸ਼_ਬਹੁਲਕ_k_EGamepad_ਪਾਠ_ਨਿਵੇਸ਼_ਬਹੁਲਕ_Submit = 2,
} EGamepad_ਪਾਠ_ਨਿਵੇਸ਼_ਬਹੁਲਕ;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ EGamepad_ਪਾਠ_ਨਿਵੇਸ਼_ਸਤਰ_ਬਹੁਲਕ
{
	EGamepad_ਪਾਠ_ਨਿਵੇਸ਼_ਸਤਰ_ਬਹੁਲਕ_k_EGamepad_ਪਾਠ_ਨਿਵੇਸ਼_ਸਤਰ_ਬਹੁਲਕ_Single_ਸਤਰ = 0,
	EGamepad_ਪਾਠ_ਨਿਵੇਸ਼_ਸਤਰ_ਬਹੁਲਕ_k_EGamepad_ਪਾਠ_ਨਿਵੇਸ਼_ਸਤਰ_ਬਹੁਲਕ_ਗੁਣਜ_ਸਤਰਾਂ = 1,
} EGamepad_ਪਾਠ_ਨਿਵੇਸ਼_ਸਤਰ_ਬਹੁਲਕ;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ EVROverlay_Intersection_ਨਕਾਬ_Primitive_Type
{
	EVROverlay_Intersection_ਨਕਾਬ_Primitive_Type_Overlay_Intersection_Primitive_Type_Rectangle = 0,
	EVROverlay_Intersection_ਨਕਾਬ_Primitive_Type_Overlay_Intersection_Primitive_Type_Circle = 1,
} EVROverlay_Intersection_ਨਕਾਬ_Primitive_Type;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ EKeyboardFlags
{
	EKeyboard_Flags_Keyboard_Flag_ਨਿਊਨਤਮ = 1,
	EKeyboardFlags_KeyboardFlag_Modal = 2,
} EKeyboardFlags;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ EDeviceType
{
	EDeviceType_DeviceType_Invalid = -1,
	EDevice_Type_Device_Type_ਸਿੱਧਾ_X11 = 0,
	EDeviceType_DeviceType_Vulkan = 1,
} EDeviceType;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ Headset_View_ਬਹੁਲਕ_t
{
	Headset_View_ਬਹੁਲਕ_t_Headset_View_ਬਹੁਲਕ_ਖੱਬਾ = 0,
	Headset_View_ਬਹੁਲਕ_t_Headset_View_ਬਹੁਲਕ_ਸੱਜਾ = 1,
	Headset_View_ਬਹੁਲਕ_t_Headset_View_ਬਹੁਲਕ_Both = 2,
} Headset_View_ਬਹੁਲਕ_t;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ EVRRenderModelError
{
	EVRRenderModelError_VRRenderModelError_None = 0,
	EVRRenderModelError_VRRenderModelError_Loading = 100,
	EVRRenderModelError_VRRenderModelError_NotSupported = 200,
	EVRRenderModelError_VRRenderModelError_InvalidArg = 300,
	EVRRenderModelError_VRRenderModelError_InvalidModel = 301,
	EVRRenderModelError_VRRenderModelError_NoShapes = 302,
	EVRRender_Model_Error_VRRender_Model_Error_ਗੁਣਜ_Shapes = 303,
	EVRRenderModelError_VRRenderModelError_TooManyVertices = 304,
	EVRRender_Model_Error_VRRender_Model_Error_ਗੁਣਜ_Textures = 305,
	EVRRender_Model_Error_VRRender_Model_Error_ਬਫਰ_Too_Small = 306,
	EVRRenderModelError_VRRenderModelError_NotEnoughNormals = 307,
	EVRRenderModelError_VRRenderModelError_NotEnoughTexCoords = 308,
	EVRRenderModelError_VRRenderModelError_InvalidTexture = 400,
} EVRRenderModelError;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ EVRRenderModelTextureFormat
{
	EVRRenderModelTextureFormat_VRRenderModelTextureFormat_RGBA8_SRGB = 0,
	EVRRenderModelTextureFormat_VRRenderModelTextureFormat_BC2 = 1,
	EVRRenderModelTextureFormat_VRRenderModelTextureFormat_BC4 = 2,
	EVRRenderModelTextureFormat_VRRenderModelTextureFormat_BC7 = 3,
	EVRRenderModelTextureFormat_VRRenderModelTextureFormat_BC7_SRGB = 4,
	EVRRenderModelTextureFormat_VRRenderModelTextureFormat_RGBA16_FLOAT = 5,
} EVRRenderModelTextureFormat;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ EVRNotificationType
{
	EVRNotificationType_Transient = 0,
	EVRNotificationType_Persistent = 1,
	EVRNotification_Type_Transient_System_With_User_ਮੁੱਲ = 2,
} EVRNotificationType;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ EVRNotificationStyle
{
	EVRNotificationStyle_None = 0,
	EVRNotificationStyle_Application = 100,
	EVRNotificationStyle_Contact_Disabled = 200,
	EVRNotificationStyle_Contact_Enabled = 201,
	EVRNotification_Style_Contact_ਸਰਗਰਮ = 202,
} EVRNotificationStyle;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ EVRSettingsError
{
	EVRSettingsError_VRSettingsError_None = 0,
	EVRSettingsError_VRSettingsError_IPCFailed = 1,
	EVRSettingsError_VRSettingsError_WriteFailed = 2,
	EVRSettingsError_VRSettingsError_ReadFailed = 3,
	EVRSettingsError_VRSettingsError_JsonParseFailed = 4,
	EVRSettingsError_VRSettingsError_UnsetSettingHasNoDefault = 5,
} EVRSettingsError;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ EVRScreenshotError
{
	EVRScreenshotError_VRScreenshotError_None = 0,
	EVRScreenshotError_VRScreenshotError_RequestFailed = 1,
	EVRScreenshot_Error_VRScreenshot_Error_Incompatible_ਸੰਸਕਰਣ = 100,
	EVRScreenshot_Error_VRScreenshot_Error_Not_ਮਿਲਿਆ = 101,
	EVRScreenshot_Error_VRScreenshot_Error_ਬਫਰ_Too_Small = 102,
	EVRScreenshot_Error_VRScreenshot_Error_Screenshot_Already_ਵਿੱਚ_ਤਰੱਕੀ = 108,
} EVRScreenshotError;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ EVRSkeletalTransformSpace
{
	EVRSkeletalTransformSpace_VRSkeletalTransformSpace_Model = 0,
	EVRSkeletal_Transform_Space_VRSkeletal_Transform_Space_ਮਾਪਾ = 1,
} EVRSkeletalTransformSpace;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ EVRSkeletalReferencePose
{
	EVRSkeletalReferencePose_VRSkeletalReferencePose_BindPose = 0,
	EVRSkeletalReferencePose_VRSkeletalReferencePose_OpenHand = 1,
	EVRSkeletalReferencePose_VRSkeletalReferencePose_Fist = 2,
	EVRSkeletal_Reference_Pose_VRSkeletal_Reference_Pose_Grip_ਹੱਦਬੰਦੀ = 3,
} EVRSkeletalReferencePose;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ EVRFinger
{
	EVRFinger_VRFinger_Thumb = 0,
	EVRFinger_VRFinger_ਸੂਚਕਾਂਕ = 1,
	EVRFinger_VRFinger_ਵਿਚਕਾਰ = 2,
	EVRFinger_VRFinger_Ring = 3,
	EVRFinger_VRFinger_Pinky = 4,
	EVRFinger_VRFinger_ਗਿਣਤੀ = 5,
} EVRFinger;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ EVRFingerSplay
{
	EVRFinger_Splay_VRFinger_Splay_Thumb_ਸੂਚਕਾਂਕ = 0,
	EVRFinger_Splay_VRFinger_Splay_ਸੂਚਕਾਂਕ_ਵਿਚਕਾਰ = 1,
	EVRFinger_Splay_VRFinger_Splay_ਵਿਚਕਾਰ_Ring = 2,
	EVRFingerSplay_VRFingerSplay_Ring_Pinky = 3,
	EVRFinger_Splay_VRFinger_Splay_ਗਿਣਤੀ = 4,
} EVRFingerSplay;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ EVRSummaryType
{
	EVRSummaryType_VRSummaryType_FromAnimation = 0,
	EVRSummaryType_VRSummaryType_FromDevice = 1,
} EVRSummaryType;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ EVRInputFilterCancelType
{
	EVRInputFilterCancelType_VRInputFilterCancel_Timers = 0,
	EVRInputFilterCancelType_VRInputFilterCancel_Momentum = 1,
} EVRInputFilterCancelType;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ EVRInput_String_ਬਿੱਟ
{
	EVRInput_String_ਬਿੱਟ_VRInput_String_Hand = 1,
	EVRInput_String_ਬਿੱਟ_VRInput_String_Controller_Type = 2,
	EVRInput_String_ਬਿੱਟ_VRInput_String_ਨਿਵੇਸ਼_ਸਰੋਤ = 4,
	EVRInput_String_ਬਿੱਟ_VRInput_String_All = -1,
} EVRInput_String_ਬਿੱਟ;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ EIOBufferError
{
	EIOBufferError_IOBuffer_Success = 0,
	EIOBufferError_IOBuffer_OperationFailed = 100,
	EIOBufferError_IOBuffer_InvalidHandle = 101,
	EIOBuffer_Error_IOBuffer_Invalid_ਦਲੀਲ = 102,
	EIOBuffer_Error_IOBuffer_ਰਸਤਾ_Exists = 103,
	EIOBuffer_Error_IOBuffer_ਰਸਤਾ_Does_Not_Exist = 104,
	EIOBufferError_IOBuffer_Permission = 105,
} EIOBufferError;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ EIOBuffer_ਬਹੁਲਕ
{
	EIOBuffer_ਬਹੁਲਕ_IOBuffer_ਬਹੁਲਕ_Read = 1,
	EIOBuffer_ਬਹੁਲਕ_IOBuffer_ਬਹੁਲਕ_Write = 2,
	EIOBuffer_ਬਹੁਲਕ_IOBuffer_ਬਹੁਲਕ_Create = 512,
} EIOBuffer_ਬਹੁਲਕ;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ EVRDebugError
{
	EVRDebugError_VRDebugError_Success = 0,
	EVRDebugError_VRDebugError_BadParameter = 1,
} EVRDebugError;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ EPropertyWriteType
{
	EProperty_Write_Type_Property_Write_ਸੈੱਟ = 0,
	EPropertyWriteType_PropertyWrite_Erase = 1,
	EProperty_Write_Type_Property_Write_ਸੈੱਟ_Error = 2,
} EPropertyWriteType;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ EBlock_ਕਤਾਰ_Error
{
	EBlock_ਕਤਾਰ_Error_ਖੰਡ_ਕਤਾਰ_Error_None = 0,
	EBlock_ਕਤਾਰ_Error_ਖੰਡ_ਕਤਾਰ_Error_ਕਤਾਰ_Already_Exists = 1,
	EBlock_ਕਤਾਰ_Error_ਖੰਡ_ਕਤਾਰ_Error_ਕਤਾਰ_Not_ਮਿਲਿਆ = 2,
	EBlock_ਕਤਾਰ_Error_ਖੰਡ_ਕਤਾਰ_Error_ਖੰਡ_Not_ਉਪਲਬਧ = 3,
	EBlock_ਕਤਾਰ_Error_ਖੰਡ_ਕਤਾਰ_Error_Invalid_Handle = 4,
	EBlock_ਕਤਾਰ_Error_ਖੰਡ_ਕਤਾਰ_Error_Invalid_Param = 5,
	EBlock_ਕਤਾਰ_Error_ਖੰਡ_ਕਤਾਰ_Error_Param_Mismatch = 6,
	EBlock_ਕਤਾਰ_Error_ਖੰਡ_ਕਤਾਰ_Error_ਅੰਦਰੂਨੀ_Error = 7,
	EBlock_ਕਤਾਰ_Error_ਖੰਡ_ਕਤਾਰ_Error_Already_Initialized = 8,
	EBlock_ਕਤਾਰ_Error_ਖੰਡ_ਕਤਾਰ_Error_Operation_Is_Server_Only = 9,
	EBlock_ਕਤਾਰ_Error_ਖੰਡ_ਕਤਾਰ_Error_Too_Many_Connections = 10,
} EBlock_ਕਤਾਰ_Error;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ EBlock_ਕਤਾਰ_Read_Type
{
	EBlock_ਕਤਾਰ_Read_Type_ਖੰਡ_ਕਤਾਰ_Read_Latest = 0,
	EBlock_ਕਤਾਰ_Read_Type_ਖੰਡ_ਕਤਾਰ_Read_New = 1,
	EBlock_ਕਤਾਰ_Read_Type_ਖੰਡ_ਕਤਾਰ_Read_ਅਗਲਾ = 2,
} EBlock_ਕਤਾਰ_Read_Type;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ EBlock_ਕਤਾਰ_Creation_Flag
{
	EBlock_ਕਤਾਰ_Creation_Flag_ਖੰਡ_ਕਤਾਰ_Flag_Owner_Is_Reader = 1,
} EBlock_ਕਤਾਰ_Creation_Flag;


// OpenVR typedefs

ਕਿਸਮਪਰਿਭਾਸ਼ਾ uint32_t Property_Type_ਟੈਗ_t;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ uint32_t SpatialAnchorHandle_t;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ * glSharedTextureHandle_t;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ int32_t glInt_t;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ uint32_t glUInt_t;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ uint64_t SharedTextureHandle_t;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ uint32_t DriverId_t;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ uint32_t Tracked_Device_ਸੂਚਕਾਂਕ_t;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ uint64_t WebConsoleHandle_t;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ uint64_t PropertyContainerHandle_t;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ PropertyContainerHandle_t DriverHandle_t;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ uint64_t VRActionHandle_t;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ uint64_t VRAction_ਸੈੱਟ_Handle_t;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ uint64_t VRInput_ਮੁੱਲ_Handle_t;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ uint32_t VRComponentProperties;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ uint64_t VROverlayHandle_t;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ int32_t Bone_ਸੂਚਕਾਂਕ_t;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ uint64_t TrackedCameraHandle_t;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ uint32_t ScreenshotHandle_t;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ int32_t TextureID_t;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ uint32_t VRNotificationId;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ uint64_t IOBufferHandle_t;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ uint64_t VrProfilerEventHandle_t;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EVRInitError HmdError;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EVREye Hmd_Eye;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EColorSpace ColorSpace;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ETracking_ਨਤੀਜਾ Hmd_Tracking_ਨਤੀਜਾ;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ETrackedDeviceClass TrackedDeviceClass;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ETrackingUniverseOrigin TrackingUniverseOrigin;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ETrackedDeviceProperty TrackedDeviceProperty;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ETrackedPropertyError TrackedPropertyError;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EVRSubmitFlags VRSubmitFlags_t;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EVRState VRState_t;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ECollisionBoundsStyle CollisionBoundsStyle_t;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EVROverlayError VROverlayError;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EVRFirmwareError VRFirmwareError;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EVRCompositorError VRCompositorError;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EVRScreenshotError VRScreenshotsError;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ uint64_t ਰਸਤਾ_Handle_t;

// OpenVR Structs

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ HmdMatrix34_t
{
	ਦਸ਼ਮਲਵ m[3][4]; //float[3][4]
} HmdMatrix34_t;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ HmdMatrix33_t
{
	ਦਸ਼ਮਲਵ m[3][3]; //float[3][3]
} HmdMatrix33_t;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ HmdMatrix44_t
{
	ਦਸ਼ਮਲਵ m[4][4]; //float[4][4]
} HmdMatrix44_t;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ HmdVector3_t
{
	ਦਸ਼ਮਲਵ v[3]; //float[3]
} HmdVector3_t;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ HmdVector4_t
{
	ਦਸ਼ਮਲਵ v[4]; //float[4]
} HmdVector4_t;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ HmdVector3d_t
{
	ਦੁੱਗਣਾ v[3]; //double[3]
} HmdVector3d_t;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ HmdVector2_t
{
	ਦਸ਼ਮਲਵ v[2]; //float[2]
} HmdVector2_t;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ HmdQuaternion_t
{
	ਦੁੱਗਣਾ w;
	ਦੁੱਗਣਾ x;
	ਦੁੱਗਣਾ y;
	ਦੁੱਗਣਾ z;
} HmdQuaternion_t;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ HmdQuaternionf_t
{
	ਦਸ਼ਮਲਵ w;
	ਦਸ਼ਮਲਵ x;
	ਦਸ਼ਮਲਵ y;
	ਦਸ਼ਮਲਵ z;
} HmdQuaternionf_t;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ HmdColor_t
{
	ਦਸ਼ਮਲਵ r;
	ਦਸ਼ਮਲਵ g;
	ਦਸ਼ਮਲਵ b;
	ਦਸ਼ਮਲਵ a;
} HmdColor_t;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ HmdQuad_t
{
	ਬਣਤਰ HmdVector3_t vCorners[4]; //struct vr::HmdVector3_t[4]
} HmdQuad_t;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ HmdRect2_t
{
	ਬਣਤਰ HmdVector2_t v_ਸਿਖਰ_ਖੱਬਾ;
	ਬਣਤਰ HmdVector2_t v_Bottom_ਸੱਜਾ;
} HmdRect2_t;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ VRBoneTransform_t
{
	ਬਣਤਰ HmdVector4_t position;
	ਬਣਤਰ HmdQuaternionf_t orientation;
} VRBoneTransform_t;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ DistortionCoordinates_t
{
	ਦਸ਼ਮਲਵ rfRed[2]; //float[2]
	ਦਸ਼ਮਲਵ rfGreen[2]; //float[2]
	ਦਸ਼ਮਲਵ rfBlue[2]; //float[2]
} DistortionCoordinates_t;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ Texture_t
{
	ਖਾਲੀ * handle; // void *
	ਗਿਣਤੀ ETextureType eType;
	ਗਿਣਤੀ EColorSpace eColorSpace;
} Texture_t;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ TrackedDevicePose_t
{
	ਬਣਤਰ HmdMatrix34_t m_Device_ਮੰਜ਼ਿਲ_Absolute_Tracking;
	ਬਣਤਰ HmdVector3_t vVelocity;
	ਬਣਤਰ HmdVector3_t vAngularVelocity;
	ਗਿਣਤੀ ETracking_ਨਤੀਜਾ e_Tracking_ਨਤੀਜਾ;
	bool bPoseIsValid;
	bool bDeviceIsConnected;
} TrackedDevicePose_t;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ VRTextureBounds_t
{
	ਦਸ਼ਮਲਵ uMin;
	ਦਸ਼ਮਲਵ vMin;
	ਦਸ਼ਮਲਵ uMax;
	ਦਸ਼ਮਲਵ vMax;
} VRTextureBounds_t;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ VRTextureWithPose_t
{
	ਖਾਲੀ * handle; // void *
	ਗਿਣਤੀ ETextureType eType;
	ਗਿਣਤੀ EColorSpace eColorSpace;
	ਬਣਤਰ HmdMatrix34_t m_Device_ਮੰਜ਼ਿਲ_Absolute_Tracking;
} VRTextureWithPose_t;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ VRTexture_ਡੂੰਘਾਈ_Info_t
{
	ਖਾਲੀ * handle; // void *
	ਬਣਤਰ HmdMatrix44_t mProjection;
	ਬਣਤਰ HmdVector2_t vRange;
} VRTexture_ਡੂੰਘਾਈ_Info_t;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ VRTexture_With_ਡੂੰਘਾਈ_t
{
	ਖਾਲੀ * handle; // void *
	ਗਿਣਤੀ ETextureType eType;
	ਗਿਣਤੀ EColorSpace eColorSpace;
	ਬਣਤਰ VRTexture_ਡੂੰਘਾਈ_Info_t ਡੂੰਘਾਈ_2;
} VRTexture_With_ਡੂੰਘਾਈ_t;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ VRTexture_With_Pose_And_ਡੂੰਘਾਈ_t
{
	ਖਾਲੀ * handle; // void *
	ਗਿਣਤੀ ETextureType eType;
	ਗਿਣਤੀ EColorSpace eColorSpace;
	ਬਣਤਰ HmdMatrix34_t m_Device_ਮੰਜ਼ਿਲ_Absolute_Tracking;
	ਬਣਤਰ VRTexture_ਡੂੰਘਾਈ_Info_t ਡੂੰਘਾਈ_2;
} VRTexture_With_Pose_And_ਡੂੰਘਾਈ_t;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ VRVulkan_Texture_ਅੰਕੜੇ_t
{
	uint64_t m_nImage;
	ਬਣਤਰ VkDevice_T * m_pDevice; // struct VkDevice_T *
	ਬਣਤਰ VkPhysicalDevice_T * m_pPhysicalDevice; // struct VkPhysicalDevice_T *
	ਬਣਤਰ VkInstance_T * m_pInstance; // struct VkInstance_T *
	ਬਣਤਰ Vk_ਕਤਾਰ_T * m_p_ਕਤਾਰ; // struct VkQueue_T *
	uint32_t m_n_ਕਤਾਰ_Family_ਸੂਚਕਾਂਕ;
	uint32_t m_n_ਚੌੜਾਈ;
	uint32_t m_n_ਉਚਾਈ;
	uint32_t m_nFormat;
	uint32_t m_n_Sample_ਗਿਣਤੀ;
} VRVulkan_Texture_ਅੰਕੜੇ_t;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ VRVulkan_Texture_Array_ਅੰਕੜੇ_t
{
	uint32_t m_un_Array_ਸੂਚਕਾਂਕ;
	uint32_t m_un_Array_ਮਾਪ;
} VRVulkan_Texture_Array_ਅੰਕੜੇ_t;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ D3_D12_Texture_ਅੰਕੜੇ_t
{
	ਬਣਤਰ ID3D12Resource * m_pResource; // struct ID3D12Resource *
	ਬਣਤਰ ID3_D12_Command_ਕਤਾਰ * m_p_Command_ਕਤਾਰ; // struct ID3D12CommandQueue *
	uint32_t m_n_ਗੰਢ_ਨਕਾਬ;
} D3_D12_Texture_ਅੰਕੜੇ_t;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ VREvent_Controller_t
{
	uint32_t button;
} VREvent_Controller_t;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ VREvent_Mouse_t
{
	ਦਸ਼ਮਲਵ x;
	ਦਸ਼ਮਲਵ y;
	uint32_t button;
} VREvent_Mouse_t;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ VREvent_Scroll_t
{
	ਦਸ਼ਮਲਵ xdelta;
	ਦਸ਼ਮਲਵ ydelta;
	uint32_t ਅਣਵਰਤਿਆ;
	ਦਸ਼ਮਲਵ viewportscale;
} VREvent_Scroll_t;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ VREvent_TouchPadMove_t
{
	bool b_Finger_ਥੱਲੇ;
	ਦਸ਼ਮਲਵ fl_Seconds_Finger_ਥੱਲੇ;
	ਦਸ਼ਮਲਵ f_ਮੁੱਲ_XFirst;
	ਦਸ਼ਮਲਵ f_ਮੁੱਲ_YFirst;
	ਦਸ਼ਮਲਵ f_ਮੁੱਲ_XRaw;
	ਦਸ਼ਮਲਵ f_ਮੁੱਲ_YRaw;
} VREvent_TouchPadMove_t;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ VREvent_Notification_t
{
	uint64_t ul_User_ਮੁੱਲ;
	uint32_t notificationId;
} VREvent_Notification_t;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ VREvent_Process_t
{
	uint32_t pid;
	uint32_t oldPid;
	bool bForced;
	bool b_Connection_ਗੁਆਚਾ;
} VREvent_Process_t;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ VREvent_Overlay_t
{
	uint64_t overlayHandle;
	uint64_t device_ਰਸਤਾ;
	uint64_t ਸਮ੍ਰਿਤੀ_ਖੰਡ_Id;
} VREvent_Overlay_t;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ VREvent_ਸਥਿਤੀ_t
{
	uint32_t ਸਥਿਤੀ_State;
} VREvent_ਸਥਿਤੀ_t;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ VREvent_Keyboard_t
{
	ਅੱਖਰ c_New_ਨਿਵੇਸ਼[8]; //char[8]
	uint64_t u_User_ਮੁੱਲ;
} VREvent_Keyboard_t;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ VREvent_Ipd_t
{
	ਦਸ਼ਮਲਵ ipdMeters;
} VREvent_Ipd_t;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ VREvent_Chaperone_t
{
	uint64_t m_n_ਪਿਛਲਾ_Universe;
	uint64_t m_nCurrentUniverse;
} VREvent_Chaperone_t;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ VREvent_Reserved_t
{
	uint64_t reserved0;
	uint64_t reserved1;
	uint64_t reserved2;
	uint64_t reserved3;
	uint64_t reserved4;
	uint64_t reserved5;
} VREvent_Reserved_t;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ VREvent_PerformanceTest_t
{
	uint32_t m_nFidelityLevel;
} VREvent_PerformanceTest_t;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ VREvent_SeatedZeroPoseReset_t
{
	bool bResetBySystemMenu;
} VREvent_SeatedZeroPoseReset_t;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ VREvent_Screenshot_t
{
	uint32_t handle;
	uint32_t type;
} VREvent_Screenshot_t;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ VREvent_Screenshot_ਤਰੱਕੀ_t
{
	ਦਸ਼ਮਲਵ ਤਰੱਕੀ_2;
} VREvent_Screenshot_ਤਰੱਕੀ_t;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ VREvent_ApplicationLaunch_t
{
	uint32_t pid;
	uint32_t un_ਦਲੀਲਾਂ_Handle;
} VREvent_ApplicationLaunch_t;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ VREvent_EditingCameraSurface_t
{
	uint64_t overlayHandle;
	uint32_t n_Visual_ਬਹੁਲਕ;
} VREvent_EditingCameraSurface_t;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ VREvent_ਸੁਨੇਹਾ_Overlay_t
{
	uint32_t unVRMessageOverlayResponse;
} VREvent_ਸੁਨੇਹਾ_Overlay_t;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ VREvent_Property_t
{
	PropertyContainerHandle_t container;
	ਗਿਣਤੀ ETrackedDeviceProperty prop;
} VREvent_Property_t;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ VREvent_HapticVibration_t
{
	uint64_t containerHandle;
	uint64_t componentHandle;
	ਦਸ਼ਮਲਵ fDurationSeconds;
	ਦਸ਼ਮਲਵ fFrequency;
	ਦਸ਼ਮਲਵ fAmplitude;
} VREvent_HapticVibration_t;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ VREvent_WebConsole_t
{
	WebConsoleHandle_t webConsoleHandle;
} VREvent_WebConsole_t;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ VREvent_ਨਿਵੇਸ਼_Binding_ਲੱਦੋ_t
{
	PropertyContainerHandle_t ulAppContainer;
	uint64_t ਰਸਤਾ_ਸੁਨੇਹਾ;
	uint64_t ਰਸਤਾ_Url;
	uint64_t ਰਸਤਾ_Controller_Type;
} VREvent_ਨਿਵੇਸ਼_Binding_ਲੱਦੋ_t;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ VREvent_ਨਿਵੇਸ਼_Action_Manifest_ਲੱਦੋ_t
{
	uint64_t ਰਸਤਾ_App_ਕੁੰਜੀ;
	uint64_t ਰਸਤਾ_ਸੁਨੇਹਾ;
	uint64_t ਰਸਤਾ_ਸੁਨੇਹਾ_Param;
	uint64_t ਰਸਤਾ_Manifest_ਰਸਤਾ;
} VREvent_ਨਿਵੇਸ਼_Action_Manifest_ਲੱਦੋ_t;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ VREvent_SpatialAnchor_t
{
	SpatialAnchorHandle_t unHandle;
} VREvent_SpatialAnchor_t;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ VREvent_ਤਰੱਕੀ_Update_t
{
	uint64_t ulApplicationPropertyContainer;
	uint64_t ਰਸਤਾ_Device;
	uint64_t ਰਸਤਾ_ਨਿਵੇਸ਼_ਸਰੋਤ;
	uint64_t ਰਸਤਾ_ਤਰੱਕੀ_Action;
	uint64_t ਰਸਤਾ_Icon;
	ਦਸ਼ਮਲਵ f_ਤਰੱਕੀ;
} VREvent_ਤਰੱਕੀ_Update_t;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ VREvent_ShowUI_t
{
	ਗਿਣਤੀ EShowUIType eType;
} VREvent_ShowUI_t;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ VREvent_ShowDevTools_t
{
	int32_t nBrowserIdentifier;
} VREvent_ShowDevTools_t;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ VREvent_HDCPError_t
{
	ਗਿਣਤੀ EHDCPError e_ਕੋਡ;
} VREvent_HDCPError_t;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ RenderModel_ComponentState_t
{
	ਬਣਤਰ HmdMatrix34_t m_Tracking_ਮੰਜ਼ਿਲ_Component_Render_Model;
	ਬਣਤਰ HmdMatrix34_t m_Tracking_ਮੰਜ਼ਿਲ_Component_Local;
	VRComponentProperties uProperties;
} RenderModel_ComponentState_t;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ HiddenAreaMesh_t
{
	ਬਣਤਰ HmdVector2_t * p_ਸ਼ੀਰਸ਼_ਅੰਕੜੇ; // const struct vr::HmdVector2_t *
	uint32_t un_Triangle_ਗਿਣਤੀ;
} HiddenAreaMesh_t;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ VRControllerAxis_t
{
	ਦਸ਼ਮਲਵ x;
	ਦਸ਼ਮਲਵ y;
} VRControllerAxis_t;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ VRControllerState_t
{
	uint32_t un_Packet_ਅੰਕ;
	uint64_t ulButtonPressed;
	uint64_t ulButtonTouched;
	ਬਣਤਰ VRControllerAxis_t rAxis[5]; //struct vr::VRControllerAxis_t[5]
} VRControllerState_t;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ Camera_Video_ਧਾਰਾ_ਚੌਖਟਾ_ਸਿਰਲੇਖ_t
{
	ਗਿਣਤੀ EVRTracked_Camera_ਚੌਖਟਾ_Type e_ਚੌਖਟਾ_Type;
	uint32_t n_ਚੌੜਾਈ;
	uint32_t n_ਉਚਾਈ;
	uint32_t n_ਬਾਈਟਾਂ_ਪ੍ਰਤੀ_Pixel;
	uint32_t n_ਚੌਖਟਾ_Sequence;
	ਬਣਤਰ TrackedDevicePose_t trackedDevicePose;
	uint64_t ul_ਚੌਖਟਾ_Exposure_ਸਮਾਂ;
} Camera_Video_ਧਾਰਾ_ਚੌਖਟਾ_ਸਿਰਲੇਖ_t;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ Compositor_ਚੌਖਟਾ_Timing
{
	uint32_t m_n_ਮਾਪ;
	uint32_t m_n_ਚੌਖਟਾ_ਸੂਚਕਾਂਕ;
	uint32_t m_n_ਅੰਕ_ਚੌਖਟਾ_Presents;
	uint32_t m_n_ਅੰਕ_Mis_Presented;
	uint32_t m_n_ਅੰਕ_Dropped_ਚੌਖਟੇ;
	uint32_t m_nReprojectionFlags;
	ਦੁੱਗਣਾ m_fl_System_ਸਮਾਂ_ਵਿੱਚ_Seconds;
	ਦਸ਼ਮਲਵ m_flPreSubmitGpuMs;
	ਦਸ਼ਮਲਵ m_flPostSubmitGpuMs;
	ਦਸ਼ਮਲਵ m_fl_ਕੁੱਲ_Render_Gpu_Ms;
	ਦਸ਼ਮਲਵ m_flCompositorRenderGpuMs;
	ਦਸ਼ਮਲਵ m_flCompositorRenderCpuMs;
	ਦਸ਼ਮਲਵ m_flCompositorIdleCpuMs;
	ਦਸ਼ਮਲਵ m_fl_Client_ਚੌਖਟਾ_Interval_Ms;
	ਦਸ਼ਮਲਵ m_flPresentCallCpuMs;
	ਦਸ਼ਮਲਵ m_flWaitForPresentCpuMs;
	ਦਸ਼ਮਲਵ m_fl_Submit_ਚੌਖਟਾ_Ms;
	ਦਸ਼ਮਲਵ m_flWaitGetPosesCalledMs;
	ਦਸ਼ਮਲਵ m_flNewPosesReadyMs;
	ਦਸ਼ਮਲਵ m_fl_New_ਚੌਖਟਾ_Ready_Ms;
	ਦਸ਼ਮਲਵ m_fl_Compositor_Update_ਸ਼ੁਰੂ_Ms;
	ਦਸ਼ਮਲਵ m_fl_Compositor_Update_ਸਿਰਾ_Ms;
	ਦਸ਼ਮਲਵ m_fl_Compositor_Render_ਸ਼ੁਰੂ_Ms;
	TrackedDevicePose_t m_HmdPose;
	uint32_t m_n_ਅੰਕ_VSyncs_Ready_For_Use;
	uint32_t m_n_ਅੰਕ_VSyncs_ਮੰਜ਼ਿਲ_ਪਹਿਲਾ_View;
} Compositor_ਚੌਖਟਾ_Timing;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ Compositor_BenchmarkResults
{
	ਦਸ਼ਮਲਵ m_fl_Mega_Pixels_ਪ੍ਰਤੀ_ਦੂਜਾ;
	ਦਸ਼ਮਲਵ m_fl_Hmd_Recommended_Mega_Pixels_ਪ੍ਰਤੀ_ਦੂਜਾ;
} Compositor_BenchmarkResults;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ Driver_ਸਿੱਧਾ_ਬਹੁਲਕ_ਚੌਖਟਾ_Timing
{
	uint32_t m_n_ਮਾਪ;
	uint32_t m_n_ਅੰਕ_ਚੌਖਟਾ_Presents;
	uint32_t m_n_ਅੰਕ_Mis_Presented;
	uint32_t m_n_ਅੰਕ_Dropped_ਚੌਖਟੇ;
	uint32_t m_nReprojectionFlags;
} Driver_ਸਿੱਧਾ_ਬਹੁਲਕ_ਚੌਖਟਾ_Timing;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ ImuSample_t
{
	ਦੁੱਗਣਾ f_Sample_ਸਮਾਂ;
	ਬਣਤਰ HmdVector3d_t vAccel;
	ਬਣਤਰ HmdVector3d_t vGyro;
	uint32_t unOffScaleFlags;
} ImuSample_t;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ App_Override_ਕੁੰਜੀਆਂ_t
{
	ਅੱਖਰ * pch_ਕੁੰਜੀ; // const char *
	ਅੱਖਰ * pch_ਮੁੱਲ; // const char *
} App_Override_ਕੁੰਜੀਆਂ_t;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ Compositor_CumulativeStats
{
	uint32_t m_nPid;
	uint32_t m_n_ਅੰਕ_ਚੌਖਟਾ_Presents;
	uint32_t m_n_ਅੰਕ_Dropped_ਚੌਖਟੇ;
	uint32_t m_n_ਅੰਕ_Reprojected_ਚੌਖਟੇ;
	uint32_t m_n_ਅੰਕ_ਚੌਖਟਾ_Presents_On_Startup;
	uint32_t m_n_ਅੰਕ_Dropped_ਚੌਖਟੇ_On_Startup;
	uint32_t m_n_ਅੰਕ_Reprojected_ਚੌਖਟੇ_On_Startup;
	uint32_t m_n_ਅੰਕ_Loading;
	uint32_t m_n_ਅੰਕ_ਚੌਖਟਾ_Presents_Loading;
	uint32_t m_n_ਅੰਕ_Dropped_ਚੌਖਟੇ_Loading;
	uint32_t m_n_ਅੰਕ_Reprojected_ਚੌਖਟੇ_Loading;
	uint32_t m_n_ਅੰਕ_Timed_ਬਾਹਰਲਾ;
	uint32_t m_n_ਅੰਕ_ਚੌਖਟਾ_Presents_Timed_ਬਾਹਰਲਾ;
	uint32_t m_n_ਅੰਕ_Dropped_ਚੌਖਟੇ_Timed_ਬਾਹਰਲਾ;
	uint32_t m_n_ਅੰਕ_Reprojected_ਚੌਖਟੇ_Timed_ਬਾਹਰਲਾ;
	uint32_t m_n_ਅੰਕ_ਚੌਖਟਾ_Submits;
	ਦੁੱਗਣਾ m_fl_ਜੋੜ_Compositor_CPUTime_MS;
	ਦੁੱਗਣਾ m_fl_ਜੋੜ_Compositor_GPUTime_MS;
	ਦੁੱਗਣਾ m_fl_ਜੋੜ_ਨਿਸ਼ਾਨਾ_ਚੌਖਟਾ_Times;
	ਦੁੱਗਣਾ m_fl_ਜੋੜ_Application_CPUTime_MS;
	ਦੁੱਗਣਾ m_fl_ਜੋੜ_Application_GPUTime_MS;
} Compositor_CumulativeStats;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ Compositor_StageRenderSettings
{
	ਬਣਤਰ HmdColor_t m_PrimaryColor;
	ਬਣਤਰ HmdColor_t m_SecondaryColor;
	ਦਸ਼ਮਲਵ m_flVignetteInnerRadius;
	ਦਸ਼ਮਲਵ m_flVignetteOuterRadius;
	ਦਸ਼ਮਲਵ m_flFresnelStrength;
	bool m_bBackfaceCulling;
	bool m_bGreyscale;
	bool m_bWireframe;
} Compositor_StageRenderSettings;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ VROverlayIntersectionParams_t
{
	ਬਣਤਰ HmdVector3_t v_ਸਰੋਤ;
	ਬਣਤਰ HmdVector3_t vDirection;
	ਗਿਣਤੀ ETrackingUniverseOrigin eOrigin;
} VROverlayIntersectionParams_t;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ VROverlayIntersectionResults_t
{
	ਬਣਤਰ HmdVector3_t v_ਬਿੰਦੂ;
	ਬਣਤਰ HmdVector3_t v_ਸਾਧਾਰਨ;
	ਬਣਤਰ HmdVector2_t vUVs;
	ਦਸ਼ਮਲਵ f_ਦੂਰੀ;
} VROverlayIntersectionResults_t;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ Intersection_ਨਕਾਬ_Rectangle_t
{
	ਦਸ਼ਮਲਵ m_fl_ਸਿਖਰ_ਖੱਬਾ_X;
	ਦਸ਼ਮਲਵ m_fl_ਸਿਖਰ_ਖੱਬਾ_Y;
	ਦਸ਼ਮਲਵ m_fl_ਚੌੜਾਈ;
	ਦਸ਼ਮਲਵ m_fl_ਉਚਾਈ;
} Intersection_ਨਕਾਬ_Rectangle_t;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ Intersection_ਨਕਾਬ_Circle_t
{
	ਦਸ਼ਮਲਵ m_flCenterX;
	ਦਸ਼ਮਲਵ m_flCenterY;
	ਦਸ਼ਮਲਵ m_flRadius;
} Intersection_ਨਕਾਬ_Circle_t;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ VROverlayProjection_t
{
	ਦਸ਼ਮਲਵ f_ਖੱਬਾ;
	ਦਸ਼ਮਲਵ f_ਸੱਜਾ;
	ਦਸ਼ਮਲਵ f_ਸਿਖਰ;
	ਦਸ਼ਮਲਵ fBottom;
} VROverlayProjection_t;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ VROverlayView_t
{
	VROverlayHandle_t overlayHandle;
	ਬਣਤਰ Texture_t texture;
	ਬਣਤਰ VRTextureBounds_t textureBounds;
} VROverlayView_t;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ VRVulkanDevice_t
{
	ਬਣਤਰ VkInstance_T * m_pInstance; // struct VkInstance_T *
	ਬਣਤਰ VkDevice_T * m_pDevice; // struct VkDevice_T *
	ਬਣਤਰ VkPhysicalDevice_T * m_pPhysicalDevice; // struct VkPhysicalDevice_T *
	ਬਣਤਰ Vk_ਕਤਾਰ_T * m_p_ਕਤਾਰ; // struct VkQueue_T *
	uint32_t m_u_ਕਤਾਰ_Family_ਸੂਚਕਾਂਕ;
} VRVulkanDevice_t;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ VRNativeDevice_t
{
	ਖਾਲੀ * handle; // void *
	ਗਿਣਤੀ EDeviceType eType;
} VRNativeDevice_t;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ Render_Model_ਸ਼ੀਰਸ਼_t
{
	ਬਣਤਰ HmdVector3_t vPosition;
	ਬਣਤਰ HmdVector3_t v_ਸਾਧਾਰਨ;
	ਦਸ਼ਮਲਵ rfTextureCoord[2]; //float[2]
} Render_Model_ਸ਼ੀਰਸ਼_t;

#ਜੇ defined(__linux__) || defined(__APPLE__)
#ਹਦਾਇਤ pack( ਧੱਕੋ, 4 )
#ਜੇ_ਅੰਤ
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ RenderModel_TextureMap_t
{
	uint16_t un_ਚੌੜਾਈ;
	uint16_t un_ਉਚਾਈ;
	uint8_t * rub_Texture_Map_ਅੰਕੜੇ; // const uint8_t *
	ਗਿਣਤੀ EVRRenderModelTextureFormat format;
	uint16_t un_Mip_ਪੱਧਰ;
} RenderModel_TextureMap_t;

#ਜੇ defined(__linux__) || defined(__APPLE__)
#ਹਦਾਇਤ pack( ਕੱਢੋ )
#ਜੇ_ਅੰਤ
#ਜੇ defined(__linux__) || defined(__APPLE__)
#ਹਦਾਇਤ pack( ਧੱਕੋ, 4 )
#ਜੇ_ਅੰਤ
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ RenderModel_t
{
	ਬਣਤਰ Render_Model_ਸ਼ੀਰਸ਼_t * r_ਸ਼ੀਰਸ਼_ਅੰਕੜੇ; // const struct vr::RenderModel_Vertex_t *
	uint32_t un_ਸ਼ੀਰਸ਼_ਗਿਣਤੀ;
	uint16_t * r_ਸੂਚਕਾਂਕ_ਅੰਕੜੇ; // const uint16_t *
	uint32_t un_Triangle_ਗਿਣਤੀ;
	TextureID_t diffuseTextureId;
} RenderModel_t;

#ਜੇ defined(__linux__) || defined(__APPLE__)
#ਹਦਾਇਤ pack( ਕੱਢੋ )
#ਜੇ_ਅੰਤ
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ Render_Model_Controller_ਬਹੁਲਕ_State_t
{
	bool bScrollWheelVisible;
} Render_Model_Controller_ਬਹੁਲਕ_State_t;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ NotificationBitmap_t
{
	ਖਾਲੀ * m_p_Image_ਅੰਕੜੇ; // void *
	int32_t m_n_ਚੌੜਾਈ;
	int32_t m_n_ਉਚਾਈ;
	int32_t m_n_ਬਾਈਟਾਂ_ਪ੍ਰਤੀ_Pixel;
} NotificationBitmap_t;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ CVRSettingHelper
{
	intptr_t m_pSettings; // class vr::IVRSettings *
} CVRSettingHelper;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ ਨਿਵੇਸ਼_Analog_Action_ਅੰਕੜੇ_t
{
	bool b_ਸਰਗਰਮ;
	VRInput_ਮੁੱਲ_Handle_t ਸਰਗਰਮ_Origin;
	ਦਸ਼ਮਲਵ x;
	ਦਸ਼ਮਲਵ y;
	ਦਸ਼ਮਲਵ z;
	ਦਸ਼ਮਲਵ deltaX;
	ਦਸ਼ਮਲਵ deltaY;
	ਦਸ਼ਮਲਵ deltaZ;
	ਦਸ਼ਮਲਵ f_Update_ਸਮਾਂ;
} ਨਿਵੇਸ਼_Analog_Action_ਅੰਕੜੇ_t;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ ਨਿਵੇਸ਼_Digital_Action_ਅੰਕੜੇ_t
{
	bool b_ਸਰਗਰਮ;
	VRInput_ਮੁੱਲ_Handle_t ਸਰਗਰਮ_Origin;
	bool bState;
	bool b_ਬਦਲਿਆ;
	ਦਸ਼ਮਲਵ f_Update_ਸਮਾਂ;
} ਨਿਵੇਸ਼_Digital_Action_ਅੰਕੜੇ_t;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ ਨਿਵੇਸ਼_Pose_Action_ਅੰਕੜੇ_t
{
	bool b_ਸਰਗਰਮ;
	VRInput_ਮੁੱਲ_Handle_t ਸਰਗਰਮ_Origin;
	ਬਣਤਰ TrackedDevicePose_t pose;
} ਨਿਵੇਸ਼_Pose_Action_ਅੰਕੜੇ_t;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ ਨਿਵੇਸ਼_Skeletal_Action_ਅੰਕੜੇ_t
{
	bool b_ਸਰਗਰਮ;
	VRInput_ਮੁੱਲ_Handle_t ਸਰਗਰਮ_Origin;
} ਨਿਵੇਸ਼_Skeletal_Action_ਅੰਕੜੇ_t;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ ਨਿਵੇਸ਼_Origin_Info_t
{
	VRInput_ਮੁੱਲ_Handle_t device_ਰਸਤਾ;
	Tracked_Device_ਸੂਚਕਾਂਕ_t tracked_Device_ਸੂਚਕਾਂਕ;
	ਅੱਖਰ rchRenderModelComponentName[128]; //char[128]
} ਨਿਵੇਸ਼_Origin_Info_t;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ ਨਿਵੇਸ਼_Binding_Info_t
{
	ਅੱਖਰ rch_Device_ਰਸਤਾ_Name[128]; //char[128]
	ਅੱਖਰ rch_ਨਿਵੇਸ਼_ਰਸਤਾ_Name[128]; //char[128]
	ਅੱਖਰ rch_ਬਹੁਲਕ_Name[128]; //char[128]
	ਅੱਖਰ rch_ਥਾਂ_Name[128]; //char[128]
	ਅੱਖਰ rch_ਨਿਵੇਸ਼_ਸਰੋਤ_Type[32]; //char[32]
} ਨਿਵੇਸ਼_Binding_Info_t;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ VRActive_Action_ਸੈੱਟ_t
{
	VRAction_ਸੈੱਟ_Handle_t ul_Action_ਸੈੱਟ;
	VRInput_ਮੁੱਲ_Handle_t ul_Restricted_ਮੰਜ਼ਿਲ_Device;
	VRAction_ਸੈੱਟ_Handle_t ul_Secondary_Action_ਸੈੱਟ;
	uint32_t unPadding;
	int32_t n_ਤਰਜੀਹ;
} VRActive_Action_ਸੈੱਟ_t;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ VRSkeletal_Summary_ਅੰਕੜੇ_t
{
	ਦਸ਼ਮਲਵ flFingerCurl[5]; //float[5]
	ਦਸ਼ਮਲਵ flFingerSplay[4]; //float[4]
} VRSkeletal_Summary_ਅੰਕੜੇ_t;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ SpatialAnchorPose_t
{
	ਬਣਤਰ HmdMatrix34_t m_Anchor_ਮੰਜ਼ਿਲ_Absolute_Tracking;
} SpatialAnchorPose_t;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ COpenVRContext
{
	intptr_t m_pVRSystem; // class vr::IVRSystem *
	intptr_t m_pVRChaperone; // class vr::IVRChaperone *
	intptr_t m_p_VRChaperone_ਤਿਆਰੀ; // class vr::IVRChaperoneSetup *
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

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ PropertyWrite_t
{
	ਗਿਣਤੀ ETrackedDeviceProperty prop;
	ਗਿਣਤੀ EPropertyWriteType writeType;
	ਗਿਣਤੀ ETrackedPropertyError e_ਸੈੱਟ_Error;
	ਖਾਲੀ * pv_ਬਫਰ; // void *
	uint32_t un_ਬਫਰ_ਮਾਪ;
	Property_Type_ਟੈਗ_t un_ਟੈਗ;
	ਗਿਣਤੀ ETrackedPropertyError eError;
} PropertyWrite_t;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ PropertyRead_t
{
	ਗਿਣਤੀ ETrackedDeviceProperty prop;
	ਖਾਲੀ * pv_ਬਫਰ; // void *
	uint32_t un_ਬਫਰ_ਮਾਪ;
	Property_Type_ਟੈਗ_t un_ਟੈਗ;
	uint32_t un_Required_ਬਫਰ_ਮਾਪ;
	ਗਿਣਤੀ ETrackedPropertyError eError;
} PropertyRead_t;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ CVRPropertyHelpers
{
	intptr_t m_pProperties; // class vr::IVRProperties *
} CVRPropertyHelpers;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ ਰਸਤਾ_Write_t
{
	ਰਸਤਾ_Handle_t ul_ਰਸਤਾ;
	ਗਿਣਤੀ EPropertyWriteType writeType;
	ਗਿਣਤੀ ETrackedPropertyError e_ਸੈੱਟ_Error;
	ਖਾਲੀ * pv_ਬਫਰ; // void *
	uint32_t un_ਬਫਰ_ਮਾਪ;
	Property_Type_ਟੈਗ_t un_ਟੈਗ;
	ਗਿਣਤੀ ETrackedPropertyError eError;
	ਅੱਖਰ * psz_ਰਸਤਾ; // const char *
} ਰਸਤਾ_Write_t;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ ਰਸਤਾ_Read_t
{
	ਰਸਤਾ_Handle_t ul_ਰਸਤਾ;
	ਖਾਲੀ * pv_ਬਫਰ; // void *
	uint32_t un_ਬਫਰ_ਮਾਪ;
	Property_Type_ਟੈਗ_t un_ਟੈਗ;
	uint32_t un_Required_ਬਫਰ_ਮਾਪ;
	ਗਿਣਤੀ ETrackedPropertyError eError;
	ਅੱਖਰ * psz_ਰਸਤਾ; // const char *
} ਰਸਤਾ_Read_t;


ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਸੰਘ
{
	VREvent_Reserved_t reserved;
	VREvent_Controller_t controller;
	VREvent_Mouse_t mouse;
	VREvent_Scroll_t scroll;
	VREvent_Process_t process;
	VREvent_Notification_t notification;
	VREvent_Overlay_t overlay;
	VREvent_ਸਥਿਤੀ_t ਸਥਿਤੀ;
	VREvent_Keyboard_t keyboard;
	VREvent_Ipd_t ipd;
	VREvent_Chaperone_t chaperone;
	VREvent_PerformanceTest_t performanceTest;
	VREvent_TouchPadMove_t touchPadMove;
	VREvent_SeatedZeroPoseReset_t seatedZeroPoseReset;
	VREvent_Screenshot_t screenshot;
	VREvent_Screenshot_ਤਰੱਕੀ_t screenshot_ਤਰੱਕੀ;
	VREvent_ApplicationLaunch_t applicationLaunch;
	VREvent_EditingCameraSurface_t cameraSurface;
	VREvent_ਸੁਨੇਹਾ_Overlay_t ਸੁਨੇਹਾ_Overlay;
	VREvent_Property_t property;
	VREvent_HapticVibration_t hapticVibration;
	VREvent_WebConsole_t webConsole;
	VREvent_ਨਿਵੇਸ਼_Binding_ਲੱਦੋ_t ਨਿਵੇਸ਼_Binding;
	VREvent_ਨਿਵੇਸ਼_Action_Manifest_ਲੱਦੋ_t actionManifest;
	VREvent_SpatialAnchor_t spatialAnchor;
} VREvent_ਅੰਕੜੇ_t;

#ਜੇ defined(__linux__) || defined(__APPLE__) 
// This structure was originally defined mis-packed on Linux, preserved for 
// compatibility. 
#ਹਦਾਇਤ pack( ਧੱਕੋ, 4 )
#ਜੇ_ਅੰਤ

/** An event posted by the server to all running applications */
ਬਣਤਰ VREvent_t
{
	uint32_t eventType; // EVREventType enum
	Tracked_Device_ਸੂਚਕਾਂਕ_t tracked_Device_ਸੂਚਕਾਂਕ;
	ਦਸ਼ਮਲਵ eventAgeSeconds;
	// event data must be the end of the struct as its size is variable
	VREvent_ਅੰਕੜੇ_t ਅੰਕੜੇ;
};

#ਜੇ defined(__linux__) || defined(__APPLE__) 
#ਹਦਾਇਤ pack( ਕੱਢੋ )
#ਜੇ_ਅੰਤ


ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਸੰਘ
{
	Intersection_ਨਕਾਬ_Rectangle_t m_Rectangle;
	Intersection_ਨਕਾਬ_Circle_t m_Circle;
} VROverlay_Intersection_ਨਕਾਬ_Primitive_ਅੰਕੜੇ_t;

ਬਣਤਰ VROverlay_Intersection_ਨਕਾਬ_Primitive_t
{
	EVROverlay_Intersection_ਨਕਾਬ_Primitive_Type m_nPrimitiveType;
	VROverlay_Intersection_ਨਕਾਬ_Primitive_ਅੰਕੜੇ_t m_Primitive;
};


// OpenVR Function Pointer Tables

ਬਣਤਰ VR_IVRSystem_Fn_ਸਾਰਣੀ
{
	ਖਾਲੀ (OPENVR_FNTABLE_CALLTYPE *Get_Recommended_Render_ਨਿਸ਼ਾਨਾ_ਮਾਪ)(uint32_t * pn_ਚੌੜਾਈ, uint32_t * pn_ਉਚਾਈ);
	ਬਣਤਰ HmdMatrix44_t (OPENVR_FNTABLE_CALLTYPE *Get_Projection_ਮੈਟ੍ਰਿਕਸ)(EVREye eEye, ਦਸ਼ਮਲਵ fNearZ, ਦਸ਼ਮਲਵ fFarZ);
	ਖਾਲੀ (OPENVR_FNTABLE_CALLTYPE *GetProjectionRaw)(EVREye eEye, ਦਸ਼ਮਲਵ * pf_ਖੱਬਾ, ਦਸ਼ਮਲਵ * pf_ਸੱਜਾ, ਦਸ਼ਮਲਵ * pf_ਸਿਖਰ, ਦਸ਼ਮਲਵ * pfBottom);
	bool (OPENVR_FNTABLE_CALLTYPE *ComputeDistortion)(EVREye eEye, ਦਸ਼ਮਲਵ fU, ਦਸ਼ਮਲਵ fV, ਬਣਤਰ DistortionCoordinates_t * pDistortionCoordinates);
	ਬਣਤਰ HmdMatrix34_t (OPENVR_FNTABLE_CALLTYPE *Get_Eye_ਮੰਜ਼ਿਲ_ਸਿਰ_Transform)(EVREye eEye);
	bool (OPENVR_FNTABLE_CALLTYPE *Get_ਸਮਾਂ_Since_ਆਖਰੀ_Vsync)(ਦਸ਼ਮਲਵ * pf_Seconds_Since_ਆਖਰੀ_Vsync, uint64_t * pul_ਚੌਖਟਾ_Counter);
	int32_t (OPENVR_FNTABLE_CALLTYPE *Get_D3_D9_Adapter_ਸੂਚਕਾਂਕ)();
	ਖਾਲੀ (OPENVR_FNTABLE_CALLTYPE *GetDXGIOutputInfo)(int32_t * pn_Adapter_ਸੂਚਕਾਂਕ);
	ਖਾਲੀ (OPENVR_FNTABLE_CALLTYPE *GetOutputDevice)(uint64_t * pnDevice, ETextureType textureType, ਬਣਤਰ VkInstance_T * pInstance);
	bool (OPENVR_FNTABLE_CALLTYPE *IsDisplayOnDesktop)();
	bool (OPENVR_FNTABLE_CALLTYPE *ਸੈੱਟ_Display_Visibility)(bool bIsVisibleOnDesktop);
	ਖਾਲੀ (OPENVR_FNTABLE_CALLTYPE *Get_Device_ਮੰਜ਼ਿਲ_Absolute_Tracking_Pose)(ETrackingUniverseOrigin eOrigin, ਦਸ਼ਮਲਵ f_Predicted_Seconds_ਮੰਜ਼ਿਲ_Photons_From_Now, ਬਣਤਰ TrackedDevicePose_t * pTrackedDevicePoseArray, uint32_t un_Tracked_Device_Pose_Array_ਗਿਣਤੀ);
	ਬਣਤਰ HmdMatrix34_t (OPENVR_FNTABLE_CALLTYPE *Get_Seated_Zero_Pose_ਮੰਜ਼ਿਲ_Standing_Absolute_Tracking_Pose)();
	ਬਣਤਰ HmdMatrix34_t (OPENVR_FNTABLE_CALLTYPE *Get_Raw_Zero_Pose_ਮੰਜ਼ਿਲ_Standing_Absolute_Tracking_Pose)();
	uint32_t (OPENVR_FNTABLE_CALLTYPE *Get_Sorted_Tracked_Device_Indices_ਦਾ_Class)(ETrackedDeviceClass eTrackedDeviceClass, Tracked_Device_ਸੂਚਕਾਂਕ_t * pun_Tracked_Device_ਸੂਚਕਾਂਕ_Array, uint32_t un_Tracked_Device_ਸੂਚਕਾਂਕ_Array_ਗਿਣਤੀ, Tracked_Device_ਸੂਚਕਾਂਕ_t un_Relative_ਮੰਜ਼ਿਲ_Tracked_Device_ਸੂਚਕਾਂਕ);
	EDeviceActivityLevel (OPENVR_FNTABLE_CALLTYPE *GetTrackedDeviceActivityLevel)(Tracked_Device_ਸੂਚਕਾਂਕ_t unDeviceId);
	ਖਾਲੀ (OPENVR_FNTABLE_CALLTYPE *ApplyTransform)(ਬਣਤਰ TrackedDevicePose_t * pOutputPose, ਬਣਤਰ TrackedDevicePose_t * pTrackedDevicePose, ਬਣਤਰ HmdMatrix34_t * pTransform);
	Tracked_Device_ਸੂਚਕਾਂਕ_t (OPENVR_FNTABLE_CALLTYPE *Get_Tracked_Device_ਸੂਚਕਾਂਕ_For_Controller_Role)(ETrackedControllerRole unDeviceType);
	ETrackedControllerRole (OPENVR_FNTABLE_CALLTYPE *Get_Controller_Role_For_Tracked_Device_ਸੂਚਕਾਂਕ)(Tracked_Device_ਸੂਚਕਾਂਕ_t un_Device_ਸੂਚਕਾਂਕ);
	ETrackedDeviceClass (OPENVR_FNTABLE_CALLTYPE *GetTrackedDeviceClass)(Tracked_Device_ਸੂਚਕਾਂਕ_t un_Device_ਸੂਚਕਾਂਕ);
	bool (OPENVR_FNTABLE_CALLTYPE *IsTrackedDeviceConnected)(Tracked_Device_ਸੂਚਕਾਂਕ_t un_Device_ਸੂਚਕਾਂਕ);
	bool (OPENVR_FNTABLE_CALLTYPE *GetBoolTrackedDeviceProperty)(Tracked_Device_ਸੂਚਕਾਂਕ_t un_Device_ਸੂਚਕਾਂਕ, ETrackedDeviceProperty prop, ETrackedPropertyError * pError);
	ਦਸ਼ਮਲਵ (OPENVR_FNTABLE_CALLTYPE *GetFloatTrackedDeviceProperty)(Tracked_Device_ਸੂਚਕਾਂਕ_t un_Device_ਸੂਚਕਾਂਕ, ETrackedDeviceProperty prop, ETrackedPropertyError * pError);
	int32_t (OPENVR_FNTABLE_CALLTYPE *GetInt32TrackedDeviceProperty)(Tracked_Device_ਸੂਚਕਾਂਕ_t un_Device_ਸੂਚਕਾਂਕ, ETrackedDeviceProperty prop, ETrackedPropertyError * pError);
	uint64_t (OPENVR_FNTABLE_CALLTYPE *GetUint64TrackedDeviceProperty)(Tracked_Device_ਸੂਚਕਾਂਕ_t un_Device_ਸੂਚਕਾਂਕ, ETrackedDeviceProperty prop, ETrackedPropertyError * pError);
	ਬਣਤਰ HmdMatrix34_t (OPENVR_FNTABLE_CALLTYPE *GetMatrix34TrackedDeviceProperty)(Tracked_Device_ਸੂਚਕਾਂਕ_t un_Device_ਸੂਚਕਾਂਕ, ETrackedDeviceProperty prop, ETrackedPropertyError * pError);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetArrayTrackedDeviceProperty)(Tracked_Device_ਸੂਚਕਾਂਕ_t un_Device_ਸੂਚਕਾਂਕ, ETrackedDeviceProperty prop, Property_Type_ਟੈਗ_t propType, ਖਾਲੀ * p_ਬਫਰ, uint32_t un_ਬਫਰ_ਮਾਪ, ETrackedPropertyError * pError);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetStringTrackedDeviceProperty)(Tracked_Device_ਸੂਚਕਾਂਕ_t un_Device_ਸੂਚਕਾਂਕ, ETrackedDeviceProperty prop, ਅੱਖਰ * pch_ਮੁੱਲ, uint32_t un_ਬਫਰ_ਮਾਪ, ETrackedPropertyError * pError);
	ਅੱਖਰ * (OPENVR_FNTABLE_CALLTYPE *GetPropErrorNameFromEnum)(ETrackedPropertyError error);
	bool (OPENVR_FNTABLE_CALLTYPE *Poll_ਅਗਲਾ_Event)(ਬਣਤਰ VREvent_t * pEvent, uint32_t uncbVREvent);
	bool (OPENVR_FNTABLE_CALLTYPE *Poll_ਅਗਲਾ_Event_With_Pose)(ETrackingUniverseOrigin eOrigin, ਬਣਤਰ VREvent_t * pEvent, uint32_t uncbVREvent, TrackedDevicePose_t * pTrackedDevicePose);
	ਅੱਖਰ * (OPENVR_FNTABLE_CALLTYPE *GetEventTypeNameFromEnum)(EVREventType eType);
	ਬਣਤਰ HiddenAreaMesh_t (OPENVR_FNTABLE_CALLTYPE *GetHiddenAreaMesh)(EVREye eEye, EHiddenAreaMeshType type);
	bool (OPENVR_FNTABLE_CALLTYPE *GetControllerState)(Tracked_Device_ਸੂਚਕਾਂਕ_t un_Controller_Device_ਸੂਚਕਾਂਕ, VRControllerState_t * pControllerState, uint32_t un_Controller_State_ਮਾਪ);
	bool (OPENVR_FNTABLE_CALLTYPE *GetControllerStateWithPose)(ETrackingUniverseOrigin eOrigin, Tracked_Device_ਸੂਚਕਾਂਕ_t un_Controller_Device_ਸੂਚਕਾਂਕ, VRControllerState_t * pControllerState, uint32_t un_Controller_State_ਮਾਪ, ਬਣਤਰ TrackedDevicePose_t * pTrackedDevicePose);
	ਖਾਲੀ (OPENVR_FNTABLE_CALLTYPE *TriggerHapticPulse)(Tracked_Device_ਸੂਚਕਾਂਕ_t un_Controller_Device_ਸੂਚਕਾਂਕ, uint32_t unAxisId, ਬਿਨਾਨਿਸ਼ਾਨੀ ਛੋਟਾ usDurationMicroSec);
	ਅੱਖਰ * (OPENVR_FNTABLE_CALLTYPE *GetButtonIdNameFromEnum)(EVRButtonId eButtonId);
	ਅੱਖਰ * (OPENVR_FNTABLE_CALLTYPE *GetControllerAxisTypeNameFromEnum)(EVRControllerAxisType eAxisType);
	bool (OPENVR_FNTABLE_CALLTYPE *Is_ਨਿਵੇਸ਼_ਉਪਲਬਧ)();
	bool (OPENVR_FNTABLE_CALLTYPE *IsSteamVRDrawingControllers)();
	bool (OPENVR_FNTABLE_CALLTYPE *ShouldApplicationPause)();
	bool (OPENVR_FNTABLE_CALLTYPE *ShouldApplicationReduceRenderingWork)();
	EVRFirmwareError (OPENVR_FNTABLE_CALLTYPE *PerformFirmwareUpdate)(Tracked_Device_ਸੂਚਕਾਂਕ_t un_Device_ਸੂਚਕਾਂਕ);
	ਖਾਲੀ (OPENVR_FNTABLE_CALLTYPE *AcknowledgeQuit_Exiting)();
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetAppContainerFilePaths)(ਅੱਖਰ * pch_ਬਫਰ, uint32_t un_ਬਫਰ_ਮਾਪ);
	ਅੱਖਰ * (OPENVR_FNTABLE_CALLTYPE *Get_Runtime_ਸੰਸਕਰਣ)();
};

ਬਣਤਰ VR_IVRExtended_Display_Fn_ਸਾਰਣੀ
{
	ਖਾਲੀ (OPENVR_FNTABLE_CALLTYPE *Get_ਖਿੜਕੀ_Bounds)(int32_t * pnX, int32_t * pnY, uint32_t * pn_ਚੌੜਾਈ, uint32_t * pn_ਉਚਾਈ);
	ਖਾਲੀ (OPENVR_FNTABLE_CALLTYPE *GetEyeOutputViewport)(EVREye eEye, uint32_t * pnX, uint32_t * pnY, uint32_t * pn_ਚੌੜਾਈ, uint32_t * pn_ਉਚਾਈ);
	ਖਾਲੀ (OPENVR_FNTABLE_CALLTYPE *GetDXGIOutputInfo)(int32_t * pn_Adapter_ਸੂਚਕਾਂਕ, int32_t * pn_Adapter_Output_ਸੂਚਕਾਂਕ);
};

ਬਣਤਰ VR_IVRTracked_Camera_Fn_ਸਾਰਣੀ
{
	ਅੱਖਰ * (OPENVR_FNTABLE_CALLTYPE *GetCameraErrorNameFromEnum)(EVRTrackedCameraError eCameraError);
	EVRTrackedCameraError (OPENVR_FNTABLE_CALLTYPE *HasCamera)(Tracked_Device_ਸੂਚਕਾਂਕ_t n_Device_ਸੂਚਕਾਂਕ, bool * pHasCamera);
	EVRTrackedCameraError (OPENVR_FNTABLE_CALLTYPE *Get_Camera_ਚੌਖਟਾ_ਮਾਪ)(Tracked_Device_ਸੂਚਕਾਂਕ_t n_Device_ਸੂਚਕਾਂਕ, EVRTracked_Camera_ਚੌਖਟਾ_Type e_ਚੌਖਟਾ_Type, uint32_t * pn_ਚੌੜਾਈ, uint32_t * pn_ਉਚਾਈ, uint32_t * pn_ਚੌਖਟਾ_ਬਫਰ_ਮਾਪ);
	EVRTrackedCameraError (OPENVR_FNTABLE_CALLTYPE *GetCameraIntrinsics)(Tracked_Device_ਸੂਚਕਾਂਕ_t n_Device_ਸੂਚਕਾਂਕ, uint32_t n_Camera_ਸੂਚਕਾਂਕ, EVRTracked_Camera_ਚੌਖਟਾ_Type e_ਚੌਖਟਾ_Type, HmdVector2_t * p_Focal_ਲੰਮਾਈ, HmdVector2_t * pCenter);
	EVRTrackedCameraError (OPENVR_FNTABLE_CALLTYPE *GetCameraProjection)(Tracked_Device_ਸੂਚਕਾਂਕ_t n_Device_ਸੂਚਕਾਂਕ, uint32_t n_Camera_ਸੂਚਕਾਂਕ, EVRTracked_Camera_ਚੌਖਟਾ_Type e_ਚੌਖਟਾ_Type, ਦਸ਼ਮਲਵ flZNear, ਦਸ਼ਮਲਵ flZFar, HmdMatrix44_t * pProjection);
	EVRTrackedCameraError (OPENVR_FNTABLE_CALLTYPE *AcquireVideoStreamingService)(Tracked_Device_ਸੂਚਕਾਂਕ_t n_Device_ਸੂਚਕਾਂਕ, TrackedCameraHandle_t * pHandle);
	EVRTrackedCameraError (OPENVR_FNTABLE_CALLTYPE *ReleaseVideoStreamingService)(TrackedCameraHandle_t hTrackedCamera);
	EVRTrackedCameraError (OPENVR_FNTABLE_CALLTYPE *Get_Video_ਧਾਰਾ_ਚੌਖਟਾ_ਬਫਰ)(TrackedCameraHandle_t hTrackedCamera, EVRTracked_Camera_ਚੌਖਟਾ_Type e_ਚੌਖਟਾ_Type, ਖਾਲੀ * p_ਚੌਖਟਾ_ਬਫਰ, uint32_t n_ਚੌਖਟਾ_ਬਫਰ_ਮਾਪ, Camera_Video_ਧਾਰਾ_ਚੌਖਟਾ_ਸਿਰਲੇਖ_t * p_ਚੌਖਟਾ_ਸਿਰਲੇਖ, uint32_t n_ਚੌਖਟਾ_ਸਿਰਲੇਖ_ਮਾਪ);
	EVRTrackedCameraError (OPENVR_FNTABLE_CALLTYPE *Get_Video_ਧਾਰਾ_Texture_ਮਾਪ)(Tracked_Device_ਸੂਚਕਾਂਕ_t n_Device_ਸੂਚਕਾਂਕ, EVRTracked_Camera_ਚੌਖਟਾ_Type e_ਚੌਖਟਾ_Type, VRTextureBounds_t * pTextureBounds, uint32_t * pn_ਚੌੜਾਈ, uint32_t * pn_ਉਚਾਈ);
	EVRTrackedCameraError (OPENVR_FNTABLE_CALLTYPE *Get_Video_ਧਾਰਾ_Texture_D3_D11)(TrackedCameraHandle_t hTrackedCamera, EVRTracked_Camera_ਚੌਖਟਾ_Type e_ਚੌਖਟਾ_Type, ਖਾਲੀ * pD3D11DeviceOrResource, ਖਾਲੀ ** ppD3D11ShaderResourceView, Camera_Video_ਧਾਰਾ_ਚੌਖਟਾ_ਸਿਰਲੇਖ_t * p_ਚੌਖਟਾ_ਸਿਰਲੇਖ, uint32_t n_ਚੌਖਟਾ_ਸਿਰਲੇਖ_ਮਾਪ);
	EVRTrackedCameraError (OPENVR_FNTABLE_CALLTYPE *Get_Video_ਧਾਰਾ_Texture_GL)(TrackedCameraHandle_t hTrackedCamera, EVRTracked_Camera_ਚੌਖਟਾ_Type e_ਚੌਖਟਾ_Type, glUInt_t * pglTextureId, Camera_Video_ਧਾਰਾ_ਚੌਖਟਾ_ਸਿਰਲੇਖ_t * p_ਚੌਖਟਾ_ਸਿਰਲੇਖ, uint32_t n_ਚੌਖਟਾ_ਸਿਰਲੇਖ_ਮਾਪ);
	EVRTrackedCameraError (OPENVR_FNTABLE_CALLTYPE *Release_Video_ਧਾਰਾ_Texture_GL)(TrackedCameraHandle_t hTrackedCamera, glUInt_t glTextureId);
	ਖਾਲੀ (OPENVR_FNTABLE_CALLTYPE *ਸੈੱਟ_Camera_Tracking_Space)(ETrackingUniverseOrigin eUniverse);
	ETrackingUniverseOrigin (OPENVR_FNTABLE_CALLTYPE *GetCameraTrackingSpace)();
};

ਬਣਤਰ VR_IVRApplications_Fn_ਸਾਰਣੀ
{
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *ਜੋੜੋ_Application_Manifest)(ਅੱਖਰ * pch_Application_Manifest_ਭਰਿਆ_ਰਸਤਾ, bool bTemporary);
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *RemoveApplicationManifest)(ਅੱਖਰ * pch_Application_Manifest_ਭਰਿਆ_ਰਸਤਾ);
	bool (OPENVR_FNTABLE_CALLTYPE *IsApplicationInstalled)(ਅੱਖਰ * pch_App_ਕੁੰਜੀ);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *Get_Application_ਗਿਣਤੀ)();
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *Get_Application_ਕੁੰਜੀ_By_ਸੂਚਕਾਂਕ)(uint32_t un_Application_ਸੂਚਕਾਂਕ, ਅੱਖਰ * pch_App_ਕੁੰਜੀ_ਬਫਰ, uint32_t un_App_ਕੁੰਜੀ_ਬਫਰ_Len);
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *Get_Application_ਕੁੰਜੀ_By_Process_Id)(uint32_t unProcessId, ਅੱਖਰ * pch_App_ਕੁੰਜੀ_ਬਫਰ, uint32_t un_App_ਕੁੰਜੀ_ਬਫਰ_Len);
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *LaunchApplication)(ਅੱਖਰ * pch_App_ਕੁੰਜੀ);
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *LaunchTemplateApplication)(ਅੱਖਰ * pch_Template_App_ਕੁੰਜੀ, ਅੱਖਰ * pch_New_App_ਕੁੰਜੀ, ਬਣਤਰ App_Override_ਕੁੰਜੀਆਂ_t * p_ਕੁੰਜੀਆਂ, uint32_t un_ਕੁੰਜੀਆਂ);
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *LaunchApplicationFromMimeType)(ਅੱਖਰ * pchMimeType, ਅੱਖਰ * pch_ਦਲੀਲਾਂ);
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *LaunchDashboardOverlay)(ਅੱਖਰ * pch_App_ਕੁੰਜੀ);
	bool (OPENVR_FNTABLE_CALLTYPE *CancelApplicationLaunch)(ਅੱਖਰ * pch_App_ਕੁੰਜੀ);
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *IdentifyApplication)(uint32_t unProcessId, ਅੱਖਰ * pch_App_ਕੁੰਜੀ);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetApplicationProcessId)(ਅੱਖਰ * pch_App_ਕੁੰਜੀ);
	ਅੱਖਰ * (OPENVR_FNTABLE_CALLTYPE *GetApplicationsErrorNameFromEnum)(EVRApplicationError error);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetApplicationPropertyString)(ਅੱਖਰ * pch_App_ਕੁੰਜੀ, EVRApplicationProperty eProperty, ਅੱਖਰ * pch_Property_ਮੁੱਲ_ਬਫਰ, uint32_t un_Property_ਮੁੱਲ_ਬਫਰ_Len, EVRApplicationError * peError);
	bool (OPENVR_FNTABLE_CALLTYPE *GetApplicationPropertyBool)(ਅੱਖਰ * pch_App_ਕੁੰਜੀ, EVRApplicationProperty eProperty, EVRApplicationError * peError);
	uint64_t (OPENVR_FNTABLE_CALLTYPE *GetApplicationPropertyUint64)(ਅੱਖਰ * pch_App_ਕੁੰਜੀ, EVRApplicationProperty eProperty, EVRApplicationError * peError);
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *ਸੈੱਟ_Application_Auto_Launch)(ਅੱਖਰ * pch_App_ਕੁੰਜੀ, bool bAutoLaunch);
	bool (OPENVR_FNTABLE_CALLTYPE *GetApplicationAutoLaunch)(ਅੱਖਰ * pch_App_ਕੁੰਜੀ);
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *ਸੈੱਟ_Default_Application_For_Mime_Type)(ਅੱਖਰ * pch_App_ਕੁੰਜੀ, ਅੱਖਰ * pchMimeType);
	bool (OPENVR_FNTABLE_CALLTYPE *GetDefaultApplicationForMimeType)(ਅੱਖਰ * pchMimeType, ਅੱਖਰ * pch_App_ਕੁੰਜੀ_ਬਫਰ, uint32_t un_App_ਕੁੰਜੀ_ਬਫਰ_Len);
	bool (OPENVR_FNTABLE_CALLTYPE *GetApplicationSupportedMimeTypes)(ਅੱਖਰ * pch_App_ਕੁੰਜੀ, ਅੱਖਰ * pch_Mime_Types_ਬਫਰ, uint32_t un_Mime_Types_ਬਫਰ);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetApplicationsThatSupportMimeType)(ਅੱਖਰ * pchMimeType, ਅੱਖਰ * pch_App_ਕੁੰਜੀਆਂ_That_Support_ਬਫਰ, uint32_t un_App_ਕੁੰਜੀਆਂ_That_Support_ਬਫਰ);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetApplicationLaunchArguments)(uint32_t unHandle, ਅੱਖਰ * pch_ਦਲੀਲਾਂ, uint32_t un_ਦਲੀਲਾਂ);
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *GetStartingApplication)(ਅੱਖਰ * pch_App_ਕੁੰਜੀ_ਬਫਰ, uint32_t un_App_ਕੁੰਜੀ_ਬਫਰ_Len);
	EVRSceneApplicationState (OPENVR_FNTABLE_CALLTYPE *GetSceneApplicationState)();
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *PerformApplicationPrelaunchCheck)(ਅੱਖਰ * pch_App_ਕੁੰਜੀ);
	ਅੱਖਰ * (OPENVR_FNTABLE_CALLTYPE *GetSceneApplicationStateNameFromEnum)(EVRSceneApplicationState state);
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *Launch_ਅੰਦਰੂਨੀ_Process)(ਅੱਖਰ * pch_ਦੁਆਧਾਰੀ_ਰਸਤਾ, ਅੱਖਰ * pchArguments, ਅੱਖਰ * pchWorkingDirectory);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetCurrentSceneProcessId)();
};

ਬਣਤਰ VR_IVRChaperone_Fn_ਸਾਰਣੀ
{
	ChaperoneCalibrationState (OPENVR_FNTABLE_CALLTYPE *GetCalibrationState)();
	bool (OPENVR_FNTABLE_CALLTYPE *Get_Play_Area_ਮਾਪ)(ਦਸ਼ਮਲਵ * p_ਮਾਪ_X, ਦਸ਼ਮਲਵ * p_ਮਾਪ_Z);
	bool (OPENVR_FNTABLE_CALLTYPE *GetPlayAreaRect)(ਬਣਤਰ HmdQuad_t * rect);
	ਖਾਲੀ (OPENVR_FNTABLE_CALLTYPE *ReloadInfo)();
	ਖਾਲੀ (OPENVR_FNTABLE_CALLTYPE *ਸੈੱਟ_Scene_Color)(ਬਣਤਰ HmdColor_t color);
	ਖਾਲੀ (OPENVR_FNTABLE_CALLTYPE *GetBoundsColor)(ਬਣਤਰ HmdColor_t * pOutputColorArray, ਪੂਰਨ n_ਅੰਕ_Output_Colors, ਦਸ਼ਮਲਵ fl_Collision_Bounds_Fade_ਦੂਰੀ, ਬਣਤਰ HmdColor_t * pOutputCameraColor);
	bool (OPENVR_FNTABLE_CALLTYPE *AreBoundsVisible)();
	ਖਾਲੀ (OPENVR_FNTABLE_CALLTYPE *ForceBoundsVisible)(bool bForce);
	ਖਾਲੀ (OPENVR_FNTABLE_CALLTYPE *ResetZeroPose)(ETrackingUniverseOrigin eTrackingUniverseOrigin);
};

ਬਣਤਰ VR_IVRChaperone_ਤਿਆਰੀ_Fn_ਸਾਰਣੀ
{
	bool (OPENVR_FNTABLE_CALLTYPE *CommitWorkingCopy)(EChaperoneConfigFile configFile);
	ਖਾਲੀ (OPENVR_FNTABLE_CALLTYPE *RevertWorkingCopy)();
	bool (OPENVR_FNTABLE_CALLTYPE *Get_Working_Play_Area_ਮਾਪ)(ਦਸ਼ਮਲਵ * p_ਮਾਪ_X, ਦਸ਼ਮਲਵ * p_ਮਾਪ_Z);
	bool (OPENVR_FNTABLE_CALLTYPE *GetWorkingPlayAreaRect)(ਬਣਤਰ HmdQuad_t * rect);
	bool (OPENVR_FNTABLE_CALLTYPE *GetWorkingCollisionBoundsInfo)(ਬਣਤਰ HmdQuad_t * p_Quads_ਬਫਰ, uint32_t * pun_Quads_ਗਿਣਤੀ);
	bool (OPENVR_FNTABLE_CALLTYPE *Get_ਜੀਵਤ_Collision_Bounds_Info)(ਬਣਤਰ HmdQuad_t * p_Quads_ਬਫਰ, uint32_t * pun_Quads_ਗਿਣਤੀ);
	bool (OPENVR_FNTABLE_CALLTYPE *Get_Working_Seated_Zero_Pose_ਮੰਜ਼ਿਲ_Raw_Tracking_Pose)(ਬਣਤਰ HmdMatrix34_t * pmat_Seated_Zero_Pose_ਮੰਜ਼ਿਲ_Raw_Tracking_Pose);
	bool (OPENVR_FNTABLE_CALLTYPE *Get_Working_Standing_Zero_Pose_ਮੰਜ਼ਿਲ_Raw_Tracking_Pose)(ਬਣਤਰ HmdMatrix34_t * pmat_Standing_Zero_Pose_ਮੰਜ਼ਿਲ_Raw_Tracking_Pose);
	ਖਾਲੀ (OPENVR_FNTABLE_CALLTYPE *ਸੈੱਟ_Working_Play_Area_ਮਾਪ)(ਦਸ਼ਮਲਵ ਮਾਪ_X, ਦਸ਼ਮਲਵ ਮਾਪ_Z);
	ਖਾਲੀ (OPENVR_FNTABLE_CALLTYPE *ਸੈੱਟ_Working_Collision_Bounds_Info)(ਬਣਤਰ HmdQuad_t * p_Quads_ਬਫਰ, uint32_t un_Quads_ਗਿਣਤੀ);
	ਖਾਲੀ (OPENVR_FNTABLE_CALLTYPE *ਸੈੱਟ_Working_Perimeter)(ਬਣਤਰ HmdVector2_t * p_ਬਿੰਦੂ_ਬਫਰ, uint32_t un_ਬਿੰਦੂ_ਗਿਣਤੀ);
	ਖਾਲੀ (OPENVR_FNTABLE_CALLTYPE *ਸੈੱਟ_Working_Seated_Zero_Pose_ਮੰਜ਼ਿਲ_Raw_Tracking_Pose)(ਬਣਤਰ HmdMatrix34_t * p_Mat_Seated_Zero_Pose_ਮੰਜ਼ਿਲ_Raw_Tracking_Pose);
	ਖਾਲੀ (OPENVR_FNTABLE_CALLTYPE *ਸੈੱਟ_Working_Standing_Zero_Pose_ਮੰਜ਼ਿਲ_Raw_Tracking_Pose)(ਬਣਤਰ HmdMatrix34_t * p_Mat_Standing_Zero_Pose_ਮੰਜ਼ਿਲ_Raw_Tracking_Pose);
	ਖਾਲੀ (OPENVR_FNTABLE_CALLTYPE *ReloadFromDisk)(EChaperoneConfigFile configFile);
	bool (OPENVR_FNTABLE_CALLTYPE *Get_ਜੀਵਤ_Seated_Zero_Pose_ਮੰਜ਼ਿਲ_Raw_Tracking_Pose)(ਬਣਤਰ HmdMatrix34_t * pmat_Seated_Zero_Pose_ਮੰਜ਼ਿਲ_Raw_Tracking_Pose);
	bool (OPENVR_FNTABLE_CALLTYPE *Export_ਜੀਵਤ_ਮੰਜ਼ਿਲ_ਬਫਰ)(ਅੱਖਰ * p_ਬਫਰ, uint32_t * pn_ਬਫਰ_ਲੰਮਾਈ);
	bool (OPENVR_FNTABLE_CALLTYPE *Import_From_ਬਫਰ_ਮੰਜ਼ਿਲ_Working)(ਅੱਖਰ * p_ਬਫਰ, uint32_t nImportFlags);
	ਖਾਲੀ (OPENVR_FNTABLE_CALLTYPE *Show_Working_ਸੈੱਟ_Preview)();
	ਖਾਲੀ (OPENVR_FNTABLE_CALLTYPE *Hide_Working_ਸੈੱਟ_Preview)();
	ਖਾਲੀ (OPENVR_FNTABLE_CALLTYPE *ਗੁੰਜਾਇਸ਼_ਤਿਆਰੀ_Starting)();
};

ਬਣਤਰ VR_IVRCompositor_Fn_ਸਾਰਣੀ
{
	ਖਾਲੀ (OPENVR_FNTABLE_CALLTYPE *ਸੈੱਟ_Tracking_Space)(ETrackingUniverseOrigin eOrigin);
	ETrackingUniverseOrigin (OPENVR_FNTABLE_CALLTYPE *GetTrackingSpace)();
	EVRCompositorError (OPENVR_FNTABLE_CALLTYPE *WaitGetPoses)(ਬਣਤਰ TrackedDevicePose_t * pRenderPoseArray, uint32_t un_Render_Pose_Array_ਗਿਣਤੀ, ਬਣਤਰ TrackedDevicePose_t * pGamePoseArray, uint32_t un_Game_Pose_Array_ਗਿਣਤੀ);
	EVRCompositorError (OPENVR_FNTABLE_CALLTYPE *Get_ਆਖਰੀ_Poses)(ਬਣਤਰ TrackedDevicePose_t * pRenderPoseArray, uint32_t un_Render_Pose_Array_ਗਿਣਤੀ, ਬਣਤਰ TrackedDevicePose_t * pGamePoseArray, uint32_t un_Game_Pose_Array_ਗਿਣਤੀ);
	EVRCompositorError (OPENVR_FNTABLE_CALLTYPE *Get_ਆਖਰੀ_Pose_For_Tracked_Device_ਸੂਚਕਾਂਕ)(Tracked_Device_ਸੂਚਕਾਂਕ_t un_Device_ਸੂਚਕਾਂਕ, ਬਣਤਰ TrackedDevicePose_t * pOutputPose, ਬਣਤਰ TrackedDevicePose_t * pOutputGamePose);
	EVRCompositorError (OPENVR_FNTABLE_CALLTYPE *Submit)(EVREye eEye, ਬਣਤਰ Texture_t * pTexture, ਬਣਤਰ VRTextureBounds_t * pBounds, EVRSubmitFlags nSubmitFlags);
	ਖਾਲੀ (OPENVR_FNTABLE_CALLTYPE *Clear_ਆਖਰੀ_Submitted_ਚੌਖਟਾ)();
	ਖਾਲੀ (OPENVR_FNTABLE_CALLTYPE *PostPresentHandoff)();
	bool (OPENVR_FNTABLE_CALLTYPE *Get_ਚੌਖਟਾ_Timing)(ਬਣਤਰ Compositor_ਚੌਖਟਾ_Timing * pTiming, uint32_t un_ਚੌਖਟੇ_Ago);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *Get_ਚੌਖਟਾ_Timings)(ਬਣਤਰ Compositor_ਚੌਖਟਾ_Timing * pTiming, uint32_t n_ਚੌਖਟੇ);
	ਦਸ਼ਮਲਵ (OPENVR_FNTABLE_CALLTYPE *Get_ਚੌਖਟਾ_ਸਮਾਂ_ਬਚਿਆ)();
	ਖਾਲੀ (OPENVR_FNTABLE_CALLTYPE *GetCumulativeStats)(ਬਣਤਰ Compositor_CumulativeStats * pStats, uint32_t n_Stats_ਮਾਪ_ਵਿੱਚ_ਬਾਈਟਾਂ);
	ਖਾਲੀ (OPENVR_FNTABLE_CALLTYPE *Fade_ਮੰਜ਼ਿਲ_Color)(ਦਸ਼ਮਲਵ fSeconds, ਦਸ਼ਮਲਵ fRed, ਦਸ਼ਮਲਵ fGreen, ਦਸ਼ਮਲਵ fBlue, ਦਸ਼ਮਲਵ fAlpha, bool bBackground);
	ਬਣਤਰ HmdColor_t (OPENVR_FNTABLE_CALLTYPE *GetCurrentFadeColor)(bool bBackground);
	ਖਾਲੀ (OPENVR_FNTABLE_CALLTYPE *FadeGrid)(ਦਸ਼ਮਲਵ fSeconds, bool b_Fade_Grid_ਵਿੱਚ);
	ਦਸ਼ਮਲਵ (OPENVR_FNTABLE_CALLTYPE *GetCurrentGridAlpha)();
	EVRCompositorError (OPENVR_FNTABLE_CALLTYPE *ਸੈੱਟ_Skybox_Override)(ਬਣਤਰ Texture_t * pTextures, uint32_t un_Texture_ਗਿਣਤੀ);
	ਖਾਲੀ (OPENVR_FNTABLE_CALLTYPE *ClearSkyboxOverride)();
	ਖਾਲੀ (OPENVR_FNTABLE_CALLTYPE *Compositor_Bring_ਮੰਜ਼ਿਲ_Front)();
	ਖਾਲੀ (OPENVR_FNTABLE_CALLTYPE *Compositor_Go_ਮੰਜ਼ਿਲ_ਪਿੱਠ)();
	ਖਾਲੀ (OPENVR_FNTABLE_CALLTYPE *CompositorQuit)();
	bool (OPENVR_FNTABLE_CALLTYPE *IsFullscreen)();
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetCurrentSceneFocusProcess)();
	uint32_t (OPENVR_FNTABLE_CALLTYPE *Get_ਆਖਰੀ_ਚੌਖਟਾ_Renderer)();
	bool (OPENVR_FNTABLE_CALLTYPE *CanRenderScene)();
	ਖਾਲੀ (OPENVR_FNTABLE_CALLTYPE *Show_Mirror_ਖਿੜਕੀ)();
	ਖਾਲੀ (OPENVR_FNTABLE_CALLTYPE *Hide_Mirror_ਖਿੜਕੀ)();
	bool (OPENVR_FNTABLE_CALLTYPE *Is_Mirror_ਖਿੜਕੀ_Visible)();
	ਖਾਲੀ (OPENVR_FNTABLE_CALLTYPE *CompositorDumpImages)();
	bool (OPENVR_FNTABLE_CALLTYPE *Should_App_Render_With_ਨੀਵਾਂ_Resources)();
	ਖਾਲੀ (OPENVR_FNTABLE_CALLTYPE *ForceInterleavedReprojectionOn)(bool bOverride);
	ਖਾਲੀ (OPENVR_FNTABLE_CALLTYPE *ForceReconnectProcess)();
	ਖਾਲੀ (OPENVR_FNTABLE_CALLTYPE *SuspendRendering)(bool bSuspend);
	EVRCompositorError (OPENVR_FNTABLE_CALLTYPE *GetMirrorTextureD3D11)(EVREye eEye, ਖਾਲੀ * pD3D11DeviceOrResource, ਖਾਲੀ ** ppD3D11ShaderResourceView);
	ਖਾਲੀ (OPENVR_FNTABLE_CALLTYPE *ReleaseMirrorTextureD3D11)(ਖਾਲੀ * pD3D11ShaderResourceView);
	EVRCompositorError (OPENVR_FNTABLE_CALLTYPE *GetMirrorTextureGL)(EVREye eEye, glUInt_t * pglTextureId, glSharedTextureHandle_t * pglSharedTextureHandle);
	bool (OPENVR_FNTABLE_CALLTYPE *ReleaseSharedGLTexture)(glUInt_t glTextureId, glSharedTextureHandle_t glSharedTextureHandle);
	ਖਾਲੀ (OPENVR_FNTABLE_CALLTYPE *ਤਾਲਾ_GLShared_Texture_For_Access)(glSharedTextureHandle_t glSharedTextureHandle);
	ਖਾਲੀ (OPENVR_FNTABLE_CALLTYPE *UnlockGLSharedTextureForAccess)(glSharedTextureHandle_t glSharedTextureHandle);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetVulkanInstanceExtensionsRequired)(ਅੱਖਰ * pch_ਮੁੱਲ, uint32_t un_ਬਫਰ_ਮਾਪ);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetVulkanDeviceExtensionsRequired)(ਬਣਤਰ VkPhysicalDevice_T * pPhysicalDevice, ਅੱਖਰ * pch_ਮੁੱਲ, uint32_t un_ਬਫਰ_ਮਾਪ);
	ਖਾਲੀ (OPENVR_FNTABLE_CALLTYPE *ਸੈੱਟ_Explicit_Timing_ਬਹੁਲਕ)(EVRCompositor_Timing_ਬਹੁਲਕ e_Timing_ਬਹੁਲਕ);
	EVRCompositorError (OPENVR_FNTABLE_CALLTYPE *Submit_Explicit_Timing_ਅੰਕੜੇ)();
	bool (OPENVR_FNTABLE_CALLTYPE *IsMotionSmoothingEnabled)();
	bool (OPENVR_FNTABLE_CALLTYPE *IsMotionSmoothingSupported)();
	bool (OPENVR_FNTABLE_CALLTYPE *IsCurrentSceneFocusAppLoading)();
	EVRCompositorError (OPENVR_FNTABLE_CALLTYPE *ਸੈੱਟ_Stage_Override_Async)(ਅੱਖਰ * pch_Render_Model_ਰਸਤਾ, ਬਣਤਰ HmdMatrix34_t * pTransform, ਬਣਤਰ Compositor_StageRenderSettings * pRenderSettings, uint32_t n_ਮਾਪ_ਦਾ_Render_Settings);
	ਖਾਲੀ (OPENVR_FNTABLE_CALLTYPE *ClearStageOverride)();
	bool (OPENVR_FNTABLE_CALLTYPE *GetCompositorBenchmarkResults)(ਬਣਤਰ Compositor_BenchmarkResults * pBenchmarkResults, uint32_t n_ਮਾਪ_ਦਾ_Benchmark_Results);
	EVRCompositorError (OPENVR_FNTABLE_CALLTYPE *Get_ਆਖਰੀ_Pose_Prediction_IDs)(uint32_t * pRenderPosePredictionID, uint32_t * pGamePosePredictionID);
	EVRCompositorError (OPENVR_FNTABLE_CALLTYPE *Get_Poses_For_ਚੌਖਟਾ)(uint32_t unPosePredictionID, ਬਣਤਰ TrackedDevicePose_t * pPoseArray, uint32_t un_Pose_Array_ਗਿਣਤੀ);
};

ਬਣਤਰ VR_IVROverlay_Fn_ਸਾਰਣੀ
{
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *ਲੱਭੋ_Overlay)(ਅੱਖਰ * pch_Overlay_ਕੁੰਜੀ, VROverlayHandle_t * pOverlayHandle);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *CreateOverlay)(ਅੱਖਰ * pch_Overlay_ਕੁੰਜੀ, ਅੱਖਰ * pchOverlayName, VROverlayHandle_t * pOverlayHandle);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *DestroyOverlay)(VROverlayHandle_t ulOverlayHandle);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *Get_Overlay_ਕੁੰਜੀ)(VROverlayHandle_t ulOverlayHandle, ਅੱਖਰ * pch_ਮੁੱਲ, uint32_t un_ਬਫਰ_ਮਾਪ, EVROverlayError * pError);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetOverlayName)(VROverlayHandle_t ulOverlayHandle, ਅੱਖਰ * pch_ਮੁੱਲ, uint32_t un_ਬਫਰ_ਮਾਪ, EVROverlayError * pError);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *ਸੈੱਟ_Overlay_Name)(VROverlayHandle_t ulOverlayHandle, ਅੱਖਰ * pchName);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *Get_Overlay_Image_ਅੰਕੜੇ)(VROverlayHandle_t ulOverlayHandle, ਖਾਲੀ * pv_ਬਫਰ, uint32_t un_ਬਫਰ_ਮਾਪ, uint32_t * pun_ਚੌੜਾਈ, uint32_t * pun_ਉਚਾਈ);
	ਅੱਖਰ * (OPENVR_FNTABLE_CALLTYPE *GetOverlayErrorNameFromEnum)(EVROverlayError error);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *ਸੈੱਟ_Overlay_Rendering_Pid)(VROverlayHandle_t ulOverlayHandle, uint32_t unPID);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetOverlayRenderingPid)(VROverlayHandle_t ulOverlayHandle);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *ਸੈੱਟ_Overlay_Flag)(VROverlayHandle_t ulOverlayHandle, VROverlayFlags eOverlayFlag, bool bEnabled);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayFlag)(VROverlayHandle_t ulOverlayHandle, VROverlayFlags eOverlayFlag, bool * pbEnabled);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayFlags)(VROverlayHandle_t ulOverlayHandle, uint32_t * pFlags);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *ਸੈੱਟ_Overlay_Color)(VROverlayHandle_t ulOverlayHandle, ਦਸ਼ਮਲਵ fRed, ਦਸ਼ਮਲਵ fGreen, ਦਸ਼ਮਲਵ fBlue);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayColor)(VROverlayHandle_t ulOverlayHandle, ਦਸ਼ਮਲਵ * pfRed, ਦਸ਼ਮਲਵ * pfGreen, ਦਸ਼ਮਲਵ * pfBlue);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *ਸੈੱਟ_Overlay_Alpha)(VROverlayHandle_t ulOverlayHandle, ਦਸ਼ਮਲਵ fAlpha);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayAlpha)(VROverlayHandle_t ulOverlayHandle, ਦਸ਼ਮਲਵ * pfAlpha);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *ਸੈੱਟ_Overlay_Texel_Aspect)(VROverlayHandle_t ulOverlayHandle, ਦਸ਼ਮਲਵ fTexelAspect);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayTexelAspect)(VROverlayHandle_t ulOverlayHandle, ਦਸ਼ਮਲਵ * pfTexelAspect);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *ਸੈੱਟ_Overlay_ਛਾਂਟੋ_ਕ੍ਰਮ)(VROverlayHandle_t ulOverlayHandle, uint32_t un_ਛਾਂਟੋ_ਕ੍ਰਮ);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *Get_Overlay_ਛਾਂਟੋ_ਕ੍ਰਮ)(VROverlayHandle_t ulOverlayHandle, uint32_t * pun_ਛਾਂਟੋ_ਕ੍ਰਮ);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *ਸੈੱਟ_Overlay_ਚੌੜਾਈ_ਵਿੱਚ_Meters)(VROverlayHandle_t ulOverlayHandle, ਦਸ਼ਮਲਵ f_ਚੌੜਾਈ_ਵਿੱਚ_Meters);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *Get_Overlay_ਚੌੜਾਈ_ਵਿੱਚ_Meters)(VROverlayHandle_t ulOverlayHandle, ਦਸ਼ਮਲਵ * pf_ਚੌੜਾਈ_ਵਿੱਚ_Meters);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *ਸੈੱਟ_Overlay_Curvature)(VROverlayHandle_t ulOverlayHandle, ਦਸ਼ਮਲਵ fCurvature);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayCurvature)(VROverlayHandle_t ulOverlayHandle, ਦਸ਼ਮਲਵ * pfCurvature);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *ਸੈੱਟ_Overlay_Pre_ਵਕਰ_Pitch)(VROverlayHandle_t ulOverlayHandle, ਦਸ਼ਮਲਵ fRadians);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *Get_Overlay_Pre_ਵਕਰ_Pitch)(VROverlayHandle_t ulOverlayHandle, ਦਸ਼ਮਲਵ * pfRadians);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *ਸੈੱਟ_Overlay_Texture_Color_Space)(VROverlayHandle_t ulOverlayHandle, EColorSpace eTextureColorSpace);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayTextureColorSpace)(VROverlayHandle_t ulOverlayHandle, EColorSpace * peTextureColorSpace);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *ਸੈੱਟ_Overlay_Texture_Bounds)(VROverlayHandle_t ulOverlayHandle, ਬਣਤਰ VRTextureBounds_t * pOverlayTextureBounds);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayTextureBounds)(VROverlayHandle_t ulOverlayHandle, ਬਣਤਰ VRTextureBounds_t * pOverlayTextureBounds);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayTransformType)(VROverlayHandle_t ulOverlayHandle, VROverlayTransformType * peTransformType);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *ਸੈੱਟ_Overlay_Transform_Absolute)(VROverlayHandle_t ulOverlayHandle, ETrackingUniverseOrigin eTrackingOrigin, ਬਣਤਰ HmdMatrix34_t * pmat_Tracking_Origin_ਮੰਜ਼ਿਲ_Overlay_Transform);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayTransformAbsolute)(VROverlayHandle_t ulOverlayHandle, ETrackingUniverseOrigin * peTrackingOrigin, ਬਣਤਰ HmdMatrix34_t * pmat_Tracking_Origin_ਮੰਜ਼ਿਲ_Overlay_Transform);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *ਸੈੱਟ_Overlay_Transform_Tracked_Device_Relative)(VROverlayHandle_t ulOverlayHandle, Tracked_Device_ਸੂਚਕਾਂਕ_t unTrackedDevice, ਬਣਤਰ HmdMatrix34_t * pmat_Tracked_Device_ਮੰਜ਼ਿਲ_Overlay_Transform);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayTransformTrackedDeviceRelative)(VROverlayHandle_t ulOverlayHandle, Tracked_Device_ਸੂਚਕਾਂਕ_t * punTrackedDevice, ਬਣਤਰ HmdMatrix34_t * pmat_Tracked_Device_ਮੰਜ਼ਿਲ_Overlay_Transform);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *ਸੈੱਟ_Overlay_Transform_Tracked_Device_Component)(VROverlayHandle_t ulOverlayHandle, Tracked_Device_ਸੂਚਕਾਂਕ_t un_Device_ਸੂਚਕਾਂਕ, ਅੱਖਰ * pchComponentName);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayTransformTrackedDeviceComponent)(VROverlayHandle_t ulOverlayHandle, Tracked_Device_ਸੂਚਕਾਂਕ_t * pun_Device_ਸੂਚਕਾਂਕ, ਅੱਖਰ * pchComponentName, uint32_t un_Component_Name_ਮਾਪ);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayTransformOverlayRelative)(VROverlayHandle_t ulOverlayHandle, VROverlayHandle_t * ul_Overlay_Handle_ਮਾਪਾ, ਬਣਤਰ HmdMatrix34_t * pmat_ਮਾਪਾ_Overlay_ਮੰਜ਼ਿਲ_Overlay_Transform);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *ਸੈੱਟ_Overlay_Transform_Overlay_Relative)(VROverlayHandle_t ulOverlayHandle, VROverlayHandle_t ul_Overlay_Handle_ਮਾਪਾ, ਬਣਤਰ HmdMatrix34_t * pmat_ਮਾਪਾ_Overlay_ਮੰਜ਼ਿਲ_Overlay_Transform);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *ਸੈੱਟ_Overlay_Transform_Cursor)(VROverlayHandle_t ulCursorOverlayHandle, ਬਣਤਰ HmdVector2_t * pvHotspot);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayTransformCursor)(VROverlayHandle_t ulOverlayHandle, ਬਣਤਰ HmdVector2_t * pvHotspot);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *ਸੈੱਟ_Overlay_Transform_Projection)(VROverlayHandle_t ulOverlayHandle, ETrackingUniverseOrigin eTrackingOrigin, ਬਣਤਰ HmdMatrix34_t * pmat_Tracking_Origin_ਮੰਜ਼ਿਲ_Overlay_Transform, ਬਣਤਰ VROverlayProjection_t * pProjection, EVREye eEye);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *ShowOverlay)(VROverlayHandle_t ulOverlayHandle);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *HideOverlay)(VROverlayHandle_t ulOverlayHandle);
	bool (OPENVR_FNTABLE_CALLTYPE *IsOverlayVisible)(VROverlayHandle_t ulOverlayHandle);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetTransformForOverlayCoordinates)(VROverlayHandle_t ulOverlayHandle, ETrackingUniverseOrigin eTrackingOrigin, ਬਣਤਰ HmdVector2_t coordinates_ਵਿੱਚ_Overlay, ਬਣਤਰ HmdMatrix34_t * pmatTransform);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *Wait_ਚੌਖਟਾ_Sync)(uint32_t nTimeoutMs);
	bool (OPENVR_FNTABLE_CALLTYPE *Poll_ਅਗਲਾ_Overlay_Event)(VROverlayHandle_t ulOverlayHandle, ਬਣਤਰ VREvent_t * pEvent, uint32_t uncbVREvent);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *Get_Overlay_ਨਿਵੇਸ਼_ਵਿਧੀ)(VROverlayHandle_t ulOverlayHandle, VROverlay_ਨਿਵੇਸ਼_ਵਿਧੀ * pe_ਨਿਵੇਸ਼_ਵਿਧੀ);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *ਸੈੱਟ_Overlay_ਨਿਵੇਸ਼_ਵਿਧੀ)(VROverlayHandle_t ulOverlayHandle, VROverlay_ਨਿਵੇਸ਼_ਵਿਧੀ e_ਨਿਵੇਸ਼_ਵਿਧੀ);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayMouseScale)(VROverlayHandle_t ulOverlayHandle, ਬਣਤਰ HmdVector2_t * pvecMouseScale);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *ਸੈੱਟ_Overlay_Mouse_Scale)(VROverlayHandle_t ulOverlayHandle, ਬਣਤਰ HmdVector2_t * pvecMouseScale);
	bool (OPENVR_FNTABLE_CALLTYPE *ComputeOverlayIntersection)(VROverlayHandle_t ulOverlayHandle, ਬਣਤਰ VROverlayIntersectionParams_t * pParams, ਬਣਤਰ VROverlayIntersectionResults_t * pResults);
	bool (OPENVR_FNTABLE_CALLTYPE *Is_Hover_ਨਿਸ਼ਾਨਾ_Overlay)(VROverlayHandle_t ulOverlayHandle);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *ਸੈੱਟ_Overlay_Intersection_ਨਕਾਬ)(VROverlayHandle_t ulOverlayHandle, ਬਣਤਰ VROverlay_Intersection_ਨਕਾਬ_Primitive_t * p_ਨਕਾਬ_Primitives, uint32_t un_ਅੰਕ_ਨਕਾਬ_Primitives, uint32_t un_Primitive_ਮਾਪ);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *TriggerLaserMouseHapticVibration)(VROverlayHandle_t ulOverlayHandle, ਦਸ਼ਮਲਵ fDurationSeconds, ਦਸ਼ਮਲਵ fFrequency, ਦਸ਼ਮਲਵ fAmplitude);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *ਸੈੱਟ_Overlay_Cursor)(VROverlayHandle_t ulOverlayHandle, VROverlayHandle_t ulCursorHandle);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *ਸੈੱਟ_Overlay_Cursor_Position_Override)(VROverlayHandle_t ulOverlayHandle, ਬਣਤਰ HmdVector2_t * pvCursor);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *ClearOverlayCursorPositionOverride)(VROverlayHandle_t ulOverlayHandle);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *ਸੈੱਟ_Overlay_Texture)(VROverlayHandle_t ulOverlayHandle, ਬਣਤਰ Texture_t * pTexture);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *ClearOverlayTexture)(VROverlayHandle_t ulOverlayHandle);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *ਸੈੱਟ_Overlay_Raw)(VROverlayHandle_t ulOverlayHandle, ਖਾਲੀ * pv_ਬਫਰ, uint32_t un_ਚੌੜਾਈ, uint32_t un_ਉਚਾਈ, uint32_t un_ਬਾਈਟਾਂ_ਪ੍ਰਤੀ_Pixel);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *ਸੈੱਟ_Overlay_From_File)(VROverlayHandle_t ulOverlayHandle, ਅੱਖਰ * pch_File_ਰਸਤਾ);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayTexture)(VROverlayHandle_t ulOverlayHandle, ਖਾਲੀ ** pNativeTextureHandle, ਖਾਲੀ * pNativeTextureRef, uint32_t * p_ਚੌੜਾਈ, uint32_t * p_ਉਚਾਈ, uint32_t * pNativeFormat, ETextureType * pAPIType, EColorSpace * pColorSpace, ਬਣਤਰ VRTextureBounds_t * pTextureBounds);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *ReleaseNativeOverlayHandle)(VROverlayHandle_t ulOverlayHandle, ਖਾਲੀ * pNativeTextureHandle);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *Get_Overlay_Texture_ਮਾਪ)(VROverlayHandle_t ulOverlayHandle, uint32_t * p_ਚੌੜਾਈ, uint32_t * p_ਉਚਾਈ);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *CreateDashboardOverlay)(ਅੱਖਰ * pch_Overlay_ਕੁੰਜੀ, ਅੱਖਰ * pchOverlayFriendlyName, VROverlayHandle_t * pMainHandle, VROverlayHandle_t * pThumbnailHandle);
	bool (OPENVR_FNTABLE_CALLTYPE *IsDashboardVisible)();
	bool (OPENVR_FNTABLE_CALLTYPE *Is_ਸਰਗਰਮ_Dashboard_Overlay)(VROverlayHandle_t ulOverlayHandle);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *ਸੈੱਟ_Dashboard_Overlay_Scene_Process)(VROverlayHandle_t ulOverlayHandle, uint32_t unProcessId);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetDashboardOverlaySceneProcess)(VROverlayHandle_t ulOverlayHandle, uint32_t * punProcessId);
	ਖਾਲੀ (OPENVR_FNTABLE_CALLTYPE *ShowDashboard)(ਅੱਖਰ * pch_Overlay_ਮੰਜ਼ਿਲ_Show);
	Tracked_Device_ਸੂਚਕਾਂਕ_t (OPENVR_FNTABLE_CALLTYPE *GetPrimaryDashboardDevice)();
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *ShowKeyboard)(EGamepad_ਪਾਠ_ਨਿਵੇਸ਼_ਬਹੁਲਕ e_ਨਿਵੇਸ਼_ਬਹੁਲਕ, EGamepad_ਪਾਠ_ਨਿਵੇਸ਼_ਸਤਰ_ਬਹੁਲਕ e_ਸਤਰ_ਨਿਵੇਸ਼_ਬਹੁਲਕ, uint32_t unFlags, ਅੱਖਰ * pchDescription, uint32_t unCharMax, ਅੱਖਰ * pch_Existing_ਪਾਠ, uint64_t u_User_ਮੁੱਲ);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *ShowKeyboardForOverlay)(VROverlayHandle_t ulOverlayHandle, EGamepad_ਪਾਠ_ਨਿਵੇਸ਼_ਬਹੁਲਕ e_ਨਿਵੇਸ਼_ਬਹੁਲਕ, EGamepad_ਪਾਠ_ਨਿਵੇਸ਼_ਸਤਰ_ਬਹੁਲਕ e_ਸਤਰ_ਨਿਵੇਸ਼_ਬਹੁਲਕ, uint32_t unFlags, ਅੱਖਰ * pchDescription, uint32_t unCharMax, ਅੱਖਰ * pch_Existing_ਪਾਠ, uint64_t u_User_ਮੁੱਲ);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *Get_Keyboard_ਪਾਠ)(ਅੱਖਰ * pch_ਪਾਠ, uint32_t cch_ਪਾਠ);
	ਖਾਲੀ (OPENVR_FNTABLE_CALLTYPE *HideKeyboard)();
	ਖਾਲੀ (OPENVR_FNTABLE_CALLTYPE *ਸੈੱਟ_Keyboard_Transform_Absolute)(ETrackingUniverseOrigin eTrackingOrigin, ਬਣਤਰ HmdMatrix34_t * pmat_Tracking_Origin_ਮੰਜ਼ਿਲ_Keyboard_Transform);
	ਖਾਲੀ (OPENVR_FNTABLE_CALLTYPE *ਸੈੱਟ_Keyboard_Position_For_Overlay)(VROverlayHandle_t ulOverlayHandle, ਬਣਤਰ HmdRect2_t avoidRect);
	VRMessageOverlayResponse (OPENVR_FNTABLE_CALLTYPE *Show_ਸੁਨੇਹਾ_Overlay)(ਅੱਖਰ * pch_ਪਾਠ, ਅੱਖਰ * pchCaption, ਅੱਖਰ * pch_Button0_ਪਾਠ, ਅੱਖਰ * pch_Button1_ਪਾਠ, ਅੱਖਰ * pch_Button2_ਪਾਠ, ਅੱਖਰ * pch_Button3_ਪਾਠ);
	ਖਾਲੀ (OPENVR_FNTABLE_CALLTYPE *Close_ਸੁਨੇਹਾ_Overlay)();
};

ਬਣਤਰ VR_IVROverlay_View_Fn_ਸਾਰਣੀ
{
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *AcquireOverlayView)(VROverlayHandle_t ulOverlayHandle, ਬਣਤਰ VRNativeDevice_t * pNativeDevice, ਬਣਤਰ VROverlayView_t * pOverlayView, uint32_t un_Overlay_View_ਮਾਪ);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *ReleaseOverlayView)(ਬਣਤਰ VROverlayView_t * pOverlayView);
	ਖਾਲੀ (OPENVR_FNTABLE_CALLTYPE *PostOverlayEvent)(VROverlayHandle_t ulOverlayHandle, ਬਣਤਰ VREvent_t * pvrEvent);
	bool (OPENVR_FNTABLE_CALLTYPE *IsViewingPermitted)(VROverlayHandle_t ulOverlayHandle);
};

ਬਣਤਰ VR_IVRHeadset_View_Fn_ਸਾਰਣੀ
{
	ਖਾਲੀ (OPENVR_FNTABLE_CALLTYPE *ਸੈੱਟ_Headset_View_ਮਾਪ)(uint32_t n_ਚੌੜਾਈ, uint32_t n_ਉਚਾਈ);
	ਖਾਲੀ (OPENVR_FNTABLE_CALLTYPE *Get_Headset_View_ਮਾਪ)(uint32_t * pn_ਚੌੜਾਈ, uint32_t * pn_ਉਚਾਈ);
	ਖਾਲੀ (OPENVR_FNTABLE_CALLTYPE *ਸੈੱਟ_Headset_View_ਬਹੁਲਕ)(Headset_View_ਬਹੁਲਕ_t e_Headset_View_ਬਹੁਲਕ);
	Headset_View_ਬਹੁਲਕ_t (OPENVR_FNTABLE_CALLTYPE *Get_Headset_View_ਬਹੁਲਕ)();
	ਖਾਲੀ (OPENVR_FNTABLE_CALLTYPE *ਸੈੱਟ_Headset_View_Cropped)(bool bCropped);
	bool (OPENVR_FNTABLE_CALLTYPE *GetHeadsetViewCropped)();
	ਦਸ਼ਮਲਵ (OPENVR_FNTABLE_CALLTYPE *Get_Headset_View_Aspect_ਅਨੁਪਾਤ)();
	ਖਾਲੀ (OPENVR_FNTABLE_CALLTYPE *ਸੈੱਟ_Headset_View_Blend_Range)(ਦਸ਼ਮਲਵ fl_ਸ਼ੁਰੂ_Pct, ਦਸ਼ਮਲਵ fl_ਸਿਰਾ_Pct);
	ਖਾਲੀ (OPENVR_FNTABLE_CALLTYPE *GetHeadsetViewBlendRange)(ਦਸ਼ਮਲਵ * p_ਸ਼ੁਰੂ_Pct, ਦਸ਼ਮਲਵ * p_ਸਿਰਾ_Pct);
};

ਬਣਤਰ VR_IVRRender_Models_Fn_ਸਾਰਣੀ
{
	EVRRenderModelError (OPENVR_FNTABLE_CALLTYPE *ਲੱਦੋ_Render_Model_Async)(ਅੱਖਰ * pchRenderModelName, ਬਣਤਰ RenderModel_t ** ppRenderModel);
	ਖਾਲੀ (OPENVR_FNTABLE_CALLTYPE *FreeRenderModel)(ਬਣਤਰ RenderModel_t * pRenderModel);
	EVRRenderModelError (OPENVR_FNTABLE_CALLTYPE *ਲੱਦੋ_Texture_Async)(TextureID_t textureId, ਬਣਤਰ RenderModel_TextureMap_t ** ppTexture);
	ਖਾਲੀ (OPENVR_FNTABLE_CALLTYPE *FreeTexture)(ਬਣਤਰ RenderModel_TextureMap_t * pTexture);
	EVRRenderModelError (OPENVR_FNTABLE_CALLTYPE *ਲੱਦੋ_Texture_D3_D11_Async)(TextureID_t textureId, ਖਾਲੀ * pD3D11Device, ਖਾਲੀ ** ppD3D11Texture2D);
	EVRRenderModelError (OPENVR_FNTABLE_CALLTYPE *ਲੱਦੋ_Into_Texture_D3_D11_Async)(TextureID_t textureId, ਖਾਲੀ * pDstTexture);
	ਖਾਲੀ (OPENVR_FNTABLE_CALLTYPE *FreeTextureD3D11)(ਖਾਲੀ * pD3D11Texture2D);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetRenderModelName)(uint32_t un_Render_Model_ਸੂਚਕਾਂਕ, ਅੱਖਰ * pchRenderModelName, uint32_t unRenderModelNameLen);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *Get_Render_Model_ਗਿਣਤੀ)();
	uint32_t (OPENVR_FNTABLE_CALLTYPE *Get_Component_ਗਿਣਤੀ)(ਅੱਖਰ * pchRenderModelName);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetComponentName)(ਅੱਖਰ * pchRenderModelName, uint32_t un_Component_ਸੂਚਕਾਂਕ, ਅੱਖਰ * pchComponentName, uint32_t unComponentNameLen);
	uint64_t (OPENVR_FNTABLE_CALLTYPE *Get_Component_Button_ਨਕਾਬ)(ਅੱਖਰ * pchRenderModelName, ਅੱਖਰ * pchComponentName);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetComponentRenderModelName)(ਅੱਖਰ * pchRenderModelName, ਅੱਖਰ * pchComponentName, ਅੱਖਰ * pchComponentRenderModelName, uint32_t unComponentRenderModelNameLen);
	bool (OPENVR_FNTABLE_CALLTYPE *Get_Component_State_For_Device_ਰਸਤਾ)(ਅੱਖਰ * pchRenderModelName, ਅੱਖਰ * pchComponentName, VRInput_ਮੁੱਲ_Handle_t device_ਰਸਤਾ, Render_Model_Controller_ਬਹੁਲਕ_State_t * pState, RenderModel_ComponentState_t * pComponentState);
	bool (OPENVR_FNTABLE_CALLTYPE *GetComponentState)(ਅੱਖਰ * pchRenderModelName, ਅੱਖਰ * pchComponentName, VRControllerState_t * pControllerState, ਬਣਤਰ Render_Model_Controller_ਬਹੁਲਕ_State_t * pState, ਬਣਤਰ RenderModel_ComponentState_t * pComponentState);
	bool (OPENVR_FNTABLE_CALLTYPE *RenderModelHasComponent)(ਅੱਖਰ * pchRenderModelName, ਅੱਖਰ * pchComponentName);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetRenderModelThumbnailURL)(ਅੱਖਰ * pchRenderModelName, ਅੱਖਰ * pchThumbnailURL, uint32_t unThumbnailURLLen, EVRRenderModelError * peError);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *Get_Render_Model_Original_ਰਸਤਾ)(ਅੱਖਰ * pchRenderModelName, ਅੱਖਰ * pch_Original_ਰਸਤਾ, uint32_t un_Original_ਰਸਤਾ_Len, EVRRenderModelError * peError);
	ਅੱਖਰ * (OPENVR_FNTABLE_CALLTYPE *GetRenderModelErrorNameFromEnum)(EVRRenderModelError error);
};

ਬਣਤਰ VR_IVRNotifications_Fn_ਸਾਰਣੀ
{
	EVRNotificationError (OPENVR_FNTABLE_CALLTYPE *CreateNotification)(VROverlayHandle_t ulOverlayHandle, uint64_t ul_User_ਮੁੱਲ, EVRNotificationType type, ਅੱਖਰ * pch_ਪਾਠ, EVRNotificationStyle style, ਬਣਤਰ NotificationBitmap_t * pImage, VRNotificationId * pNotificationId);
	EVRNotificationError (OPENVR_FNTABLE_CALLTYPE *RemoveNotification)(VRNotificationId notificationId);
};

ਬਣਤਰ VR_IVRSettings_Fn_ਸਾਰਣੀ
{
	ਅੱਖਰ * (OPENVR_FNTABLE_CALLTYPE *GetSettingsErrorNameFromEnum)(EVRSettingsError eError);
	ਖਾਲੀ (OPENVR_FNTABLE_CALLTYPE *ਸੈੱਟ_Bool)(ਅੱਖਰ * pchSection, ਅੱਖਰ * pch_Settings_ਕੁੰਜੀ, bool b_ਮੁੱਲ, EVRSettingsError * peError);
	ਖਾਲੀ (OPENVR_FNTABLE_CALLTYPE *ਸੈੱਟ_Int32)(ਅੱਖਰ * pchSection, ਅੱਖਰ * pch_Settings_ਕੁੰਜੀ, int32_t n_ਮੁੱਲ, EVRSettingsError * peError);
	ਖਾਲੀ (OPENVR_FNTABLE_CALLTYPE *ਸੈੱਟ_Float)(ਅੱਖਰ * pchSection, ਅੱਖਰ * pch_Settings_ਕੁੰਜੀ, ਦਸ਼ਮਲਵ fl_ਮੁੱਲ, EVRSettingsError * peError);
	ਖਾਲੀ (OPENVR_FNTABLE_CALLTYPE *ਸੈੱਟ_String)(ਅੱਖਰ * pchSection, ਅੱਖਰ * pch_Settings_ਕੁੰਜੀ, ਅੱਖਰ * pch_ਮੁੱਲ, EVRSettingsError * peError);
	bool (OPENVR_FNTABLE_CALLTYPE *GetBool)(ਅੱਖਰ * pchSection, ਅੱਖਰ * pch_Settings_ਕੁੰਜੀ, EVRSettingsError * peError);
	int32_t (OPENVR_FNTABLE_CALLTYPE *GetInt32)(ਅੱਖਰ * pchSection, ਅੱਖਰ * pch_Settings_ਕੁੰਜੀ, EVRSettingsError * peError);
	ਦਸ਼ਮਲਵ (OPENVR_FNTABLE_CALLTYPE *GetFloat)(ਅੱਖਰ * pchSection, ਅੱਖਰ * pch_Settings_ਕੁੰਜੀ, EVRSettingsError * peError);
	ਖਾਲੀ (OPENVR_FNTABLE_CALLTYPE *GetString)(ਅੱਖਰ * pchSection, ਅੱਖਰ * pch_Settings_ਕੁੰਜੀ, ਅੱਖਰ * pch_ਮੁੱਲ, uint32_t un_ਮੁੱਲ_Len, EVRSettingsError * peError);
	ਖਾਲੀ (OPENVR_FNTABLE_CALLTYPE *RemoveSection)(ਅੱਖਰ * pchSection, EVRSettingsError * peError);
	ਖਾਲੀ (OPENVR_FNTABLE_CALLTYPE *Remove_ਕੁੰਜੀ_ਵਿੱਚ_Section)(ਅੱਖਰ * pchSection, ਅੱਖਰ * pch_Settings_ਕੁੰਜੀ, EVRSettingsError * peError);
};

ਬਣਤਰ VR_IVRScreenshots_Fn_ਸਾਰਣੀ
{
	EVRScreenshotError (OPENVR_FNTABLE_CALLTYPE *RequestScreenshot)(ScreenshotHandle_t * p_ਬਾਹਰਲਾ_Screenshot_Handle, EVRScreenshotType type, ਅੱਖਰ * pchPreviewFilename, ਅੱਖਰ * pchVRFilename);
	EVRScreenshotError (OPENVR_FNTABLE_CALLTYPE *HookScreenshot)(EVRScreenshotType * pSupportedTypes, ਪੂਰਨ ਅੰਕ_Types);
	EVRScreenshotType (OPENVR_FNTABLE_CALLTYPE *GetScreenshotPropertyType)(ScreenshotHandle_t screenshotHandle, EVRScreenshotError * pError);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetScreenshotPropertyFilename)(ScreenshotHandle_t screenshotHandle, EVRScreenshotPropertyFilenames filenameType, ਅੱਖਰ * pchFilename, uint32_t cchFilename, EVRScreenshotError * pError);
	EVRScreenshotError (OPENVR_FNTABLE_CALLTYPE *Update_Screenshot_ਤਰੱਕੀ)(ScreenshotHandle_t screenshotHandle, ਦਸ਼ਮਲਵ fl_ਤਰੱਕੀ);
	EVRScreenshotError (OPENVR_FNTABLE_CALLTYPE *TakeStereoScreenshot)(ScreenshotHandle_t * p_ਬਾਹਰਲਾ_Screenshot_Handle, ਅੱਖਰ * pchPreviewFilename, ਅੱਖਰ * pchVRFilename);
	EVRScreenshotError (OPENVR_FNTABLE_CALLTYPE *SubmitScreenshot)(ScreenshotHandle_t screenshotHandle, EVRScreenshotType type, ਅੱਖਰ * pch_ਸਰੋਤ_Preview_Filename, ਅੱਖਰ * pch_ਸਰੋਤ_VRFilename);
};

ਬਣਤਰ VR_IVRResources_Fn_ਸਾਰਣੀ
{
	uint32_t (OPENVR_FNTABLE_CALLTYPE *ਲੱਦੋ_Shared_Resource)(ਅੱਖਰ * pchResourceName, ਅੱਖਰ * pch_ਬਫਰ, uint32_t un_ਬਫਰ_Len);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *Get_Resource_ਭਰਿਆ_ਰਸਤਾ)(ਅੱਖਰ * pchResourceName, ਅੱਖਰ * pchResourceTypeDirectory, ਅੱਖਰ * pch_ਰਸਤਾ_ਬਫਰ, uint32_t un_ਬਫਰ_Len);
};

ਬਣਤਰ VR_IVRDriver_Manager_Fn_ਸਾਰਣੀ
{
	uint32_t (OPENVR_FNTABLE_CALLTYPE *Get_Driver_ਗਿਣਤੀ)();
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetDriverName)(DriverId_t nDriver, ਅੱਖਰ * pch_ਮੁੱਲ, uint32_t un_ਬਫਰ_ਮਾਪ);
	DriverHandle_t (OPENVR_FNTABLE_CALLTYPE *GetDriverHandle)(ਅੱਖਰ * pchDriverName);
	bool (OPENVR_FNTABLE_CALLTYPE *IsEnabled)(DriverId_t nDriver);
};

ਬਣਤਰ VR_IVRInput_Fn_ਸਾਰਣੀ
{
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *ਸੈੱਟ_Action_Manifest_ਰਸਤਾ)(ਅੱਖਰ * pch_Action_Manifest_ਰਸਤਾ);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *Get_Action_ਸੈੱਟ_Handle)(ਅੱਖਰ * pch_Action_ਸੈੱਟ_Name, VRAction_ਸੈੱਟ_Handle_t * pHandle);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetActionHandle)(ਅੱਖਰ * pchActionName, VRActionHandle_t * pHandle);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *Get_ਨਿਵੇਸ਼_ਸਰੋਤ_Handle)(ਅੱਖਰ * pch_ਨਿਵੇਸ਼_ਸਰੋਤ_ਰਸਤਾ, VRInput_ਮੁੱਲ_Handle_t * pHandle);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *UpdateActionState)(ਬਣਤਰ VRActive_Action_ਸੈੱਟ_t * pSets, uint32_t un_ਮਾਪ_ਦਾ_VRSelected_Action_ਸੈੱਟ_t, uint32_t un_ਸੈੱਟ_ਗਿਣਤੀ);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *Get_Digital_Action_ਅੰਕੜੇ)(VRActionHandle_t action, ਬਣਤਰ ਨਿਵੇਸ਼_Digital_Action_ਅੰਕੜੇ_t * p_Action_ਅੰਕੜੇ, uint32_t un_Action_ਅੰਕੜੇ_ਮਾਪ, VRInput_ਮੁੱਲ_Handle_t ul_Restrict_ਮੰਜ਼ਿਲ_Device);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *Get_Analog_Action_ਅੰਕੜੇ)(VRActionHandle_t action, ਬਣਤਰ ਨਿਵੇਸ਼_Analog_Action_ਅੰਕੜੇ_t * p_Action_ਅੰਕੜੇ, uint32_t un_Action_ਅੰਕੜੇ_ਮਾਪ, VRInput_ਮੁੱਲ_Handle_t ul_Restrict_ਮੰਜ਼ਿਲ_Device);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *Get_Pose_Action_ਅੰਕੜੇ_Relative_ਮੰਜ਼ਿਲ_Now)(VRActionHandle_t action, ETrackingUniverseOrigin eOrigin, ਦਸ਼ਮਲਵ fPredictedSecondsFromNow, ਬਣਤਰ ਨਿਵੇਸ਼_Pose_Action_ਅੰਕੜੇ_t * p_Action_ਅੰਕੜੇ, uint32_t un_Action_ਅੰਕੜੇ_ਮਾਪ, VRInput_ਮੁੱਲ_Handle_t ul_Restrict_ਮੰਜ਼ਿਲ_Device);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *Get_Pose_Action_ਅੰਕੜੇ_For_ਅਗਲਾ_ਚੌਖਟਾ)(VRActionHandle_t action, ETrackingUniverseOrigin eOrigin, ਬਣਤਰ ਨਿਵੇਸ਼_Pose_Action_ਅੰਕੜੇ_t * p_Action_ਅੰਕੜੇ, uint32_t un_Action_ਅੰਕੜੇ_ਮਾਪ, VRInput_ਮੁੱਲ_Handle_t ul_Restrict_ਮੰਜ਼ਿਲ_Device);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *Get_Skeletal_Action_ਅੰਕੜੇ)(VRActionHandle_t action, ਬਣਤਰ ਨਿਵੇਸ਼_Skeletal_Action_ਅੰਕੜੇ_t * p_Action_ਅੰਕੜੇ, uint32_t un_Action_ਅੰਕੜੇ_ਮਾਪ);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetDominantHand)(ETrackedControllerRole * peDominantHand);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *ਸੈੱਟ_Dominant_Hand)(ETrackedControllerRole eDominantHand);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *Get_Bone_ਗਿਣਤੀ)(VRActionHandle_t action, uint32_t * p_Bone_ਗਿਣਤੀ);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetBoneHierarchy)(VRActionHandle_t action, Bone_ਸੂਚਕਾਂਕ_t * p_ਮਾਪਾ_Indices, uint32_t un_ਸੂਚਕਾਂਕ_Aray_ਗਿਣਤੀ);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetBoneName)(VRActionHandle_t action, Bone_ਸੂਚਕਾਂਕ_t n_Bone_ਸੂਚਕਾਂਕ, ਅੱਖਰ * pchBoneName, uint32_t un_Name_ਬਫਰ_ਮਾਪ);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetSkeletalReferenceTransforms)(VRActionHandle_t action, EVRSkeletalTransformSpace eTransformSpace, EVRSkeletalReferencePose eReferencePose, ਬਣਤਰ VRBoneTransform_t * pTransformArray, uint32_t un_Transform_Array_ਗਿਣਤੀ);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetSkeletalTrackingLevel)(VRActionHandle_t action, EVRSkeletalTrackingLevel * pSkeletalTrackingLevel);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *Get_Skeletal_Bone_ਅੰਕੜੇ)(VRActionHandle_t action, EVRSkeletalTransformSpace eTransformSpace, EVRSkeletalMotionRange eMotionRange, ਬਣਤਰ VRBoneTransform_t * pTransformArray, uint32_t un_Transform_Array_ਗਿਣਤੀ);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *Get_Skeletal_Summary_ਅੰਕੜੇ)(VRActionHandle_t action, EVRSummaryType eSummaryType, ਬਣਤਰ VRSkeletal_Summary_ਅੰਕੜੇ_t * p_Skeletal_Summary_ਅੰਕੜੇ);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *Get_Skeletal_Bone_ਅੰਕੜੇ_Compressed)(VRActionHandle_t action, EVRSkeletalMotionRange eMotionRange, ਖਾਲੀ * pv_Compressed_ਅੰਕੜੇ, uint32_t un_Compressed_ਮਾਪ, uint32_t * pun_Required_Compressed_ਮਾਪ);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *Decompress_Skeletal_Bone_ਅੰਕੜੇ)(ਖਾਲੀ * pv_Compressed_ਬਫਰ, uint32_t un_Compressed_ਬਫਰ_ਮਾਪ, EVRSkeletalTransformSpace eTransformSpace, ਬਣਤਰ VRBoneTransform_t * pTransformArray, uint32_t un_Transform_Array_ਗਿਣਤੀ);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *TriggerHapticVibrationAction)(VRActionHandle_t action, ਦਸ਼ਮਲਵ f_ਸ਼ੁਰੂ_Seconds_From_Now, ਦਸ਼ਮਲਵ fDurationSeconds, ਦਸ਼ਮਲਵ fFrequency, ਦਸ਼ਮਲਵ fAmplitude, VRInput_ਮੁੱਲ_Handle_t ul_Restrict_ਮੰਜ਼ਿਲ_Device);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetActionOrigins)(VRAction_ਸੈੱਟ_Handle_t action_ਸੈੱਟ_Handle, VRActionHandle_t digitalActionHandle, VRInput_ਮੁੱਲ_Handle_t * origins_ਬਾਹਰਲਾ, uint32_t origin_ਬਾਹਰਲਾ_ਗਿਣਤੀ);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetOriginLocalizedName)(VRInput_ਮੁੱਲ_Handle_t origin, ਅੱਖਰ * pchNameArray, uint32_t un_Name_Array_ਮਾਪ, int32_t un_String_Sections_ਮੰਜ਼ਿਲ_Include);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetOriginTrackedDeviceInfo)(VRInput_ਮੁੱਲ_Handle_t origin, ਬਣਤਰ ਨਿਵੇਸ਼_Origin_Info_t * pOriginInfo, uint32_t un_Origin_Info_ਮਾਪ);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetActionBindingInfo)(VRActionHandle_t action, ਬਣਤਰ ਨਿਵੇਸ਼_Binding_Info_t * pOriginInfo, uint32_t un_Binding_Info_ਮਾਪ, uint32_t un_Binding_Info_ਗਿਣਤੀ, uint32_t * pun_Returned_Binding_Info_ਗਿਣਤੀ);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *ShowActionOrigins)(VRAction_ਸੈੱਟ_Handle_t action_ਸੈੱਟ_Handle, VRActionHandle_t ulActionHandle);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *Show_Bindings_For_Action_ਸੈੱਟ)(ਬਣਤਰ VRActive_Action_ਸੈੱਟ_t * pSets, uint32_t un_ਮਾਪ_ਦਾ_VRSelected_Action_ਸੈੱਟ_t, uint32_t un_ਸੈੱਟ_ਗਿਣਤੀ, VRInput_ਮੁੱਲ_Handle_t origin_ਮੰਜ਼ਿਲ_Highlight);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetComponentStateForBinding)(ਅੱਖਰ * pchRenderModelName, ਅੱਖਰ * pchComponentName, ਬਣਤਰ ਨਿਵੇਸ਼_Binding_Info_t * pOriginInfo, uint32_t un_Binding_Info_ਮਾਪ, uint32_t un_Binding_Info_ਗਿਣਤੀ, RenderModel_ComponentState_t * pComponentState);
	bool (OPENVR_FNTABLE_CALLTYPE *Is_Using_Legacy_ਨਿਵੇਸ਼)();
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *OpenBindingUI)(ਅੱਖਰ * pch_App_ਕੁੰਜੀ, VRAction_ਸੈੱਟ_Handle_t ul_Action_ਸੈੱਟ_Handle, VRInput_ਮੁੱਲ_Handle_t ulDeviceHandle, bool bShowOnDesktop);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetBindingVariant)(VRInput_ਮੁੱਲ_Handle_t ul_Device_ਰਸਤਾ, ਅੱਖਰ * pchVariantArray, uint32_t un_Variant_Array_ਮਾਪ);
};

ਬਣਤਰ VR_IVRIOBuffer_Fn_ਸਾਰਣੀ
{
	EIOBufferError (OPENVR_FNTABLE_CALLTYPE *Open)(ਅੱਖਰ * pch_ਰਸਤਾ, EIOBuffer_ਬਹੁਲਕ ਬਹੁਲਕ, uint32_t un_Element_ਮਾਪ, uint32_t unElements, IOBufferHandle_t * pul_ਬਫਰ);
	EIOBufferError (OPENVR_FNTABLE_CALLTYPE *Close)(IOBufferHandle_t ul_ਬਫਰ);
	EIOBufferError (OPENVR_FNTABLE_CALLTYPE *Read)(IOBufferHandle_t ul_ਬਫਰ, ਖਾਲੀ * pDst, uint32_t un_ਬਾਈਟਾਂ, uint32_t * punRead);
	EIOBufferError (OPENVR_FNTABLE_CALLTYPE *Write)(IOBufferHandle_t ul_ਬਫਰ, ਖਾਲੀ * pSrc, uint32_t un_ਬਾਈਟਾਂ);
	PropertyContainerHandle_t (OPENVR_FNTABLE_CALLTYPE *PropertyContainer)(IOBufferHandle_t ul_ਬਫਰ);
	bool (OPENVR_FNTABLE_CALLTYPE *HasReaders)(IOBufferHandle_t ul_ਬਫਰ);
};

ਬਣਤਰ VR_IVRSpatial_Anchors_Fn_ਸਾਰਣੀ
{
	EVRSpatialAnchorError (OPENVR_FNTABLE_CALLTYPE *CreateSpatialAnchorFromDescriptor)(ਅੱਖਰ * pchDescriptor, SpatialAnchorHandle_t * p_Handle_ਬਾਹਰਲਾ);
	EVRSpatialAnchorError (OPENVR_FNTABLE_CALLTYPE *CreateSpatialAnchorFromPose)(Tracked_Device_ਸੂਚਕਾਂਕ_t un_Device_ਸੂਚਕਾਂਕ, ETrackingUniverseOrigin eOrigin, ਬਣਤਰ SpatialAnchorPose_t * pPose, SpatialAnchorHandle_t * p_Handle_ਬਾਹਰਲਾ);
	EVRSpatialAnchorError (OPENVR_FNTABLE_CALLTYPE *GetSpatialAnchorPose)(SpatialAnchorHandle_t unHandle, ETrackingUniverseOrigin eOrigin, ਬਣਤਰ SpatialAnchorPose_t * p_Pose_ਬਾਹਰਲਾ);
	EVRSpatialAnchorError (OPENVR_FNTABLE_CALLTYPE *GetSpatialAnchorDescriptor)(SpatialAnchorHandle_t unHandle, ਅੱਖਰ * pch_Descriptor_ਬਾਹਰਲਾ, uint32_t * pun_Descriptor_ਬਫਰ_Len_ਵਿੱਚ_ਬਾਹਰਲਾ);
};

ਬਣਤਰ VR_IVRDebug_Fn_ਸਾਰਣੀ
{
	EVRDebugError (OPENVR_FNTABLE_CALLTYPE *EmitVrProfilerEvent)(ਅੱਖਰ * pch_ਸੁਨੇਹਾ);
	EVRDebugError (OPENVR_FNTABLE_CALLTYPE *BeginVrProfilerEvent)(VrProfilerEventHandle_t * p_Handle_ਬਾਹਰਲਾ);
	EVRDebugError (OPENVR_FNTABLE_CALLTYPE *ਅੰਤ_Vr_Profiler_Event)(VrProfilerEventHandle_t hHandle, ਅੱਖਰ * pch_ਸੁਨੇਹਾ);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *DriverDebugRequest)(Tracked_Device_ਸੂਚਕਾਂਕ_t un_Device_ਸੂਚਕਾਂਕ, ਅੱਖਰ * pchRequest, ਅੱਖਰ * pch_Response_ਬਫਰ, uint32_t un_Response_ਬਫਰ_ਮਾਪ);
};

ਬਣਤਰ VR_IVRProperties_Fn_ਸਾਰਣੀ
{
	ETrackedPropertyError (OPENVR_FNTABLE_CALLTYPE *ReadPropertyBatch)(PropertyContainerHandle_t ulContainerHandle, ਬਣਤਰ PropertyRead_t * pBatch, uint32_t un_Batch_ਇੰਦਰਾਜ_ਗਿਣਤੀ);
	ETrackedPropertyError (OPENVR_FNTABLE_CALLTYPE *WritePropertyBatch)(PropertyContainerHandle_t ulContainerHandle, ਬਣਤਰ PropertyWrite_t * pBatch, uint32_t un_Batch_ਇੰਦਰਾਜ_ਗਿਣਤੀ);
	ਅੱਖਰ * (OPENVR_FNTABLE_CALLTYPE *GetPropErrorNameFromEnum)(ETrackedPropertyError error);
	PropertyContainerHandle_t (OPENVR_FNTABLE_CALLTYPE *Tracked_Device_ਮੰਜ਼ਿਲ_Property_Container)(Tracked_Device_ਸੂਚਕਾਂਕ_t nDevice);
};

ਬਣਤਰ VR_IVRPaths_Fn_ਸਾਰਣੀ
{
	ETrackedPropertyError (OPENVR_FNTABLE_CALLTYPE *Read_ਰਸਤਾ_Batch)(PropertyContainerHandle_t ul_ਜੜ੍ਹ_Handle, ਬਣਤਰ ਰਸਤਾ_Read_t * pBatch, uint32_t un_Batch_ਇੰਦਰਾਜ_ਗਿਣਤੀ);
	ETrackedPropertyError (OPENVR_FNTABLE_CALLTYPE *Write_ਰਸਤਾ_Batch)(PropertyContainerHandle_t ul_ਜੜ੍ਹ_Handle, ਬਣਤਰ ਰਸਤਾ_Write_t * pBatch, uint32_t un_Batch_ਇੰਦਰਾਜ_ਗਿਣਤੀ);
	ETrackedPropertyError (OPENVR_FNTABLE_CALLTYPE *String_ਮੰਜ਼ਿਲ_Handle)(ਰਸਤਾ_Handle_t * pHandle, ਅੱਖਰ * pch_ਰਸਤਾ);
	ETrackedPropertyError (OPENVR_FNTABLE_CALLTYPE *Handle_ਮੰਜ਼ਿਲ_String)(ਰਸਤਾ_Handle_t pHandle, ਅੱਖਰ * pch_ਬਫਰ, uint32_t un_ਬਫਰ_ਮਾਪ, uint32_t * pun_ਬਫਰ_ਮਾਪ_ਵਰਤਿਆ);
};

ਬਣਤਰ VR_IVRBlock_ਕਤਾਰ_Fn_ਸਾਰਣੀ
{
	EBlock_ਕਤਾਰ_Error (OPENVR_FNTABLE_CALLTYPE *Create)(PropertyContainerHandle_t * pul_ਕਤਾਰ_Handle, ਅੱਖਰ * pch_ਰਸਤਾ, uint32_t un_ਖੰਡ_ਅੰਕੜੇ_ਮਾਪ, uint32_t un_ਖੰਡ_ਸਿਰਲੇਖ_ਮਾਪ, uint32_t un_ਖੰਡ_ਗਿਣਤੀ, uint32_t unFlags);
	EBlock_ਕਤਾਰ_Error (OPENVR_FNTABLE_CALLTYPE *Connect)(PropertyContainerHandle_t * pul_ਕਤਾਰ_Handle, ਅੱਖਰ * pch_ਰਸਤਾ);
	EBlock_ਕਤਾਰ_Error (OPENVR_FNTABLE_CALLTYPE *Destroy)(PropertyContainerHandle_t ul_ਕਤਾਰ_Handle);
	EBlock_ਕਤਾਰ_Error (OPENVR_FNTABLE_CALLTYPE *Acquire_Write_Only_ਖੰਡ)(PropertyContainerHandle_t ul_ਕਤਾਰ_Handle, PropertyContainerHandle_t * pul_ਖੰਡ_Handle, ਖਾਲੀ ** ppv_ਬਫਰ);
	EBlock_ਕਤਾਰ_Error (OPENVR_FNTABLE_CALLTYPE *Release_Write_Only_ਖੰਡ)(PropertyContainerHandle_t ul_ਕਤਾਰ_Handle, PropertyContainerHandle_t ul_ਖੰਡ_Handle);
	EBlock_ਕਤਾਰ_Error (OPENVR_FNTABLE_CALLTYPE *Wait_And_Acquire_Read_Only_ਖੰਡ)(PropertyContainerHandle_t ul_ਕਤਾਰ_Handle, PropertyContainerHandle_t * pul_ਖੰਡ_Handle, ਖਾਲੀ ** ppv_ਬਫਰ, EBlock_ਕਤਾਰ_Read_Type eReadType, uint32_t unTimeoutMs);
	EBlock_ਕਤਾਰ_Error (OPENVR_FNTABLE_CALLTYPE *Acquire_Read_Only_ਖੰਡ)(PropertyContainerHandle_t ul_ਕਤਾਰ_Handle, PropertyContainerHandle_t * pul_ਖੰਡ_Handle, ਖਾਲੀ ** ppv_ਬਫਰ, EBlock_ਕਤਾਰ_Read_Type eReadType);
	EBlock_ਕਤਾਰ_Error (OPENVR_FNTABLE_CALLTYPE *Release_Read_Only_ਖੰਡ)(PropertyContainerHandle_t ul_ਕਤਾਰ_Handle, PropertyContainerHandle_t ul_ਖੰਡ_Handle);
	EBlock_ਕਤਾਰ_Error (OPENVR_FNTABLE_CALLTYPE *ਕਤਾਰ_Has_Reader)(PropertyContainerHandle_t ul_ਕਤਾਰ_Handle, bool * pbHasReaders);
};


#ਜੇ 0
// Global entry points
S_API intptr_t VR_Init_ਅੰਦਰੂਨੀ( EVRInitError *peError, EVRApplicationType eType );
S_API ਖਾਲੀ VR_Shutdown_ਅੰਦਰੂਨੀ();
S_API bool VR_IsHmdPresent();
S_API intptr_t VR_GetGenericInterface( ਅਚਲ ਅੱਖਰ *pch_Interface_ਸੰਸਕਰਣ, EVRInitError *peError );
S_API bool VR_IsRuntimeInstalled();
S_API ਅਚਲ ਅੱਖਰ * VR_Get_VRInit_Error_As_ਚਿੰਨ੍ਹ( EVRInitError error );
S_API ਅਚਲ ਅੱਖਰ * VR_GetVRInitErrorAsEnglishDescription( EVRInitError error );
#ਜੇ_ਅੰਤ

#ਜੇ_ਅੰਤ // __OPENVR_API_FLAT_H__


