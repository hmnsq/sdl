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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ __OPENVR_API_FLAT_H__
#ವ್ಯಾಖ್ಯಾನಿಸು __OPENVR_API_FLAT_H__
#ಆದರೆ defined( _WIN32 ) || defined( __clang__ )
#ಸೂಚನೆ once
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __cplusplus
#ವ್ಯಾಖ್ಯಾನಿಸು EXTERN_C ಬಾಹ್ಯ "C"
#ಇಲ್ಲದಿದ್ದರೆ
#ವ್ಯಾಖ್ಯಾನಿಸು EXTERN_C
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ defined( _WIN32 )
#ವ್ಯಾಖ್ಯಾನಿಸು OPENVR_FNTABLE_CALLTYPE __stdcall
#ಇಲ್ಲದಿದ್ದರೆ
#ವ್ಯಾಖ್ಯಾನಿಸು OPENVR_FNTABLE_CALLTYPE 
#ಆದರೆ_ಅಂತ್ಯ

// OPENVR API export macro
#ಆದರೆ defined( _WIN32 ) && !defined( _X360 )
	#ಆದರೆ defined( OPENVR_API_EXPORTS )
	#ವ್ಯಾಖ್ಯಾನಿಸು S_API EXTERN_C __declspec( dllexport )
	#ಅಥವಾಆದರೆ defined( OPENVR_API_NODLL )
	#ವ್ಯಾಖ್ಯಾನಿಸು S_API EXTERN_C
	#ಇಲ್ಲದಿದ್ದರೆ
	#ವ್ಯಾಖ್ಯಾನಿಸು S_API ಬಾಹ್ಯ "C" __declspec( dllimport ) 
	#ಆದರೆ_ಅಂತ್ಯ // OPENVR_API_EXPORTS
#ಅಥವಾಆದರೆ defined( __GNUC__ )
	#ಆದರೆ defined( OPENVR_API_EXPORTS )
	#ವ್ಯಾಖ್ಯಾನಿಸು S_API EXTERN_C __attribute__ ((visibility("default")))
	#ಇಲ್ಲದಿದ್ದರೆ
	#ವ್ಯಾಖ್ಯಾನಿಸು S_API EXTERN_C
	#ಆದರೆ_ಅಂತ್ಯ // OPENVR_API_EXPORTS
#ಇಲ್ಲದಿದ್ದರೆ // !WIN32
	#ಆದರೆ defined( OPENVR_API_EXPORTS )
	#ವ್ಯಾಖ್ಯಾನಿಸು S_API EXTERN_C
	#ಇಲ್ಲದಿದ್ದರೆ
	#ವ್ಯಾಖ್ಯಾನಿಸು S_API EXTERN_C
	#ಆದರೆ_ಅಂತ್ಯ // OPENVR_API_EXPORTS
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ USE_SDL
#ಅನ್ತರ್ಭಾವ <stdint.h>

#ಆದರೆ defined( __WIN32 )
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಅಕ್ಷರ bool;
#ಇಲ್ಲದಿದ್ದರೆ
#ಅನ್ತರ್ಭಾವ <stdbool.h>
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ // USE_SDL

// OpenVR Constants

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ k_nDriverNone = 4294967295;
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ k_un_Max_Driver_Debug_Response_ಗಾತ್ರ = 32768;
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ k_un_Tracked_Device_ಸೂಚ್ಯಂಕ_Hmd = 0;
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ k_un_Max_Tracked_Device_ಎಣಿಕೆ = 64;
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ k_un_Tracked_Device_ಸೂಚ್ಯಂಕ_Other = 4294967294;
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ k_un_Tracked_Device_ಸೂಚ್ಯಂಕ_Invalid = 4294967295;
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ ದೀರ್ಘ k_ulInvalidPropertyContainer = 0;
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ k_un_Invalid_Property_ಟ್ಯಾಗ್ = 0;
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ ದೀರ್ಘ k_ulInvalidDriverHandle = 0;
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ k_un_Float_Property_ಟ್ಯಾಗ್ = 1;
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ k_un_Int32_Property_ಟ್ಯಾಗ್ = 2;
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ k_un_Uint64_Property_ಟ್ಯಾಗ್ = 3;
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ k_un_Bool_Property_ಟ್ಯಾಗ್ = 4;
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ k_un_String_Property_ಟ್ಯಾಗ್ = 5;
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ k_un_Error_Property_ಟ್ಯಾಗ್ = 6;
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ k_un_Double_Property_ಟ್ಯಾಗ್ = 7;
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ k_un_Hmd_Matrix34_Property_ಟ್ಯಾಗ್ = 20;
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ k_un_Hmd_Matrix44_Property_ಟ್ಯಾಗ್ = 21;
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ k_un_Hmd_Vector3_Property_ಟ್ಯಾಗ್ = 22;
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ k_un_Hmd_Vector4_Property_ಟ್ಯಾಗ್ = 23;
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ k_un_Hmd_Vector2_Property_ಟ್ಯಾಗ್ = 24;
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ k_un_Hmd_Quad_Property_ಟ್ಯಾಗ್ = 25;
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ k_un_Hidden_Area_Property_ಟ್ಯಾಗ್ = 30;
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ k_un_ಮಾರ್ಗ_Handle_Info_ಟ್ಯಾಗ್ = 31;
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ k_un_Action_Property_ಟ್ಯಾಗ್ = 32;
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ k_un_ಒಳಹರಿವು_ಮೌಲ್ಯ_Property_ಟ್ಯಾಗ್ = 33;
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ k_un_Wildcard_Property_ಟ್ಯಾಗ್ = 34;
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ k_un_Haptic_Vibration_Property_ಟ್ಯಾಗ್ = 35;
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ k_un_Skeleton_Property_ಟ್ಯಾಗ್ = 36;
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ k_un_Spatial_Anchor_Pose_Property_ಟ್ಯಾಗ್ = 40;
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ k_un_Json_Property_ಟ್ಯಾಗ್ = 41;
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ k_un_ಸಕ್ರಿಯ_Action_ಗಣ_Property_ಟ್ಯಾಗ್ = 42;
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ k_un_Open_VRInternal_Reserved_ಆರಂಭ = 1000;
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ k_un_Open_VRInternal_Reserved_ಕೊನೆ = 10000;
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ k_un_Max_Property_String_ಗಾತ್ರ = 32768;
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ ದೀರ್ಘ k_ulInvalidActionHandle = 0;
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ ದೀರ್ಘ k_ul_Invalid_Action_ಗಣ_Handle = 0;
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ ದೀರ್ಘ k_ul_Invalid_ಒಳಹರಿವು_ಮೌಲ್ಯ_Handle = 0;
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ k_un_Controller_State_Axis_ಎಣಿಕೆ = 5;
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ ದೀರ್ಘ k_ulOverlayHandleInvalid = 0;
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ k_unMaxDistortionFunctionParameters = 8;
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ k_unScreenshotHandleInvalid = 0;
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * IVRSystem_ಆವೃತ್ತಿ = "IVRSystem_022";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * IVRExtended_Display_ಆವೃತ್ತಿ = "IVRExtendedDisplay_001";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * IVRTracked_Camera_ಆವೃತ್ತಿ = "IVRTrackedCamera_006";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ k_un_Max_Application_ಕೀಲಿ_ಉದ್ದಳತೆ = 128;
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_MimeType_HomeApp = "vr/home";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_MimeType_GameTheater = "vr/game_theater";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * IVRApplications_ಆವೃತ್ತಿ = "IVRApplications_007";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * IVRChaperone_ಆವೃತ್ತಿ = "IVRChaperone_004";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * IVRChaperone_ಸಿದ್ಧತೆ_ಆವೃತ್ತಿ = "IVRChaperoneSetup_006";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * IVRCompositor_ಆವೃತ್ತಿ = "IVRCompositor_027";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ k_un_VROverlay_Max_ಕೀಲಿ_ಉದ್ದಳತೆ = 128;
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ k_un_VROverlay_Max_Name_ಉದ್ದಳತೆ = 128;
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ k_un_Max_Overlay_ಎಣಿಕೆ = 128;
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ k_un_Max_Overlay_Intersection_ಮುಖವಾಡ_Primitives_ಎಣಿಕೆ = 32;
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * IVROverlay_ಆವೃತ್ತಿ = "IVROverlay_026";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * IVROverlay_View_ಆವೃತ್ತಿ = "IVROverlayView_003";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ k_un_Headset_View_Max_ಅಗಲ = 3840;
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ k_un_Headset_View_Max_ಎತ್ತರ = 2160;
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_Headset_View_Overlay_ಕೀಲಿ = "system.HeadsetView";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * IVRHeadset_View_ಆವೃತ್ತಿ = "IVRHeadsetView_001";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_Controller_Component_GDC2015 = "gdc2015";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_Controller_Component_ತಳ = "base";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_Controller_Component_Tip = "tip";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_Controller_Component_OpenXR_Aim = "openxr_aim";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_Controller_Component_HandGrip = "handgrip";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_Controller_Component_OpenXR_Grip = "openxr_grip";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_Controller_Component_OpenXR_HandModel = "openxr_handmodel";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_Controller_Component_ಸ್ಥಿತಿ = "status";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * IVRRender_Models_ಆವೃತ್ತಿ = "IVRRenderModels_006";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ k_un_Notification_ಪಠ್ಯ_Max_ಗಾತ್ರ = 256;
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * IVRNotifications_ಆವೃತ್ತಿ = "IVRNotifications_002";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ k_un_Max_Settings_ಕೀಲಿ_ಉದ್ದಳತೆ = 128;
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * IVRSettings_ಆವೃತ್ತಿ = "IVRSettings_003";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_SteamVR_Section = "steamvr";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_SteamVR_RequireHmd_String = "requireHmd";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_Steam_VR_Forced_Driver_ಕೀಲಿ_String = "forcedDriver";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_Steam_VR_Forced_Hmd_ಕೀಲಿ_String = "forcedHmd";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_SteamVR_DisplayDebug_Bool = "displayDebug";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_SteamVR_DebugProcessPipe_String = "debugProcessPipe";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_SteamVR_DisplayDebugX_Int32 = "displayDebugX";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_SteamVR_DisplayDebugY_Int32 = "displayDebugY";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_Steam_VR_Send_System_Button_ಗಮ್ಯ_All_Apps_Bool = "sendSystemButtonToAllApps";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_SteamVR_LogLevel_Int32 = "loglevel";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_SteamVR_IPD_Float = "ipd";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_SteamVR_Background_String = "background";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_SteamVR_BackgroundUseDomeProjection_Bool = "backgroundUseDomeProjection";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_Steam_VR_Background_Camera_ಎತ್ತರ_Float = "backgroundCameraHeight";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_SteamVR_BackgroundDomeRadius_Float = "backgroundDomeRadius";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_SteamVR_GridColor_String = "gridColor";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_SteamVR_PlayAreaColor_String = "playAreaColor";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_SteamVR_TrackingLossColor_String = "trackingLossColor";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_SteamVR_ShowStage_Bool = "showStage";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_SteamVR_DrawTrackingReferences_Bool = "drawTrackingReferences";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_Steam_VR_Activate_ಅಪವರ್ತ್ಯ_Drivers_Bool = "activateMultipleDrivers";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_SteamVR_UsingSpeakers_Bool = "usingSpeakers";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_Steam_VR_Speakers_Forward_Yaw_ಸ್ಥಾನಾಂತರ_Degrees_Float = "speakersForwardYawOffsetDegrees";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_Steam_VR_ತಳ_Station_Power_Management_Int32 = "basestationPowerManagement";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_Steam_VR_Show_ತಳ_Station_Power_Management_Tip_Int32 = "ShowBaseStationPowerManagementTip";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_SteamVR_NeverKillProcesses_Bool = "neverKillProcesses";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_SteamVR_SupersampleScale_Float = "supersampleScale";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_SteamVR_MaxRecommendedResolution_Int32 = "maxRecommendedResolution";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_SteamVR_MotionSmoothing_Bool = "motionSmoothing";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_SteamVR_MotionSmoothingOverride_Int32 = "motionSmoothingOverride";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_Steam_VR_ಚೌಕಟ್ಟುಗಳು_ಗಮ್ಯ_Throttle_Int32 = "framesToThrottle";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_Steam_VR_Additional_ಚೌಕಟ್ಟುಗಳು_ಗಮ್ಯ_Predict_Int32 = "additionalFramesToPredict";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_SteamVR_WorldScale_Float = "worldScale";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_SteamVR_FovScale_Int32 = "fovScale";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_SteamVR_DisableAsyncReprojection_Bool = "disableAsync";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_SteamVR_ForceFadeOnBadTracking_Bool = "forceFadeOnBadTracking";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_SteamVR_DefaultMirrorView_Int32 = "mirrorView";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_SteamVR_ShowLegacyMirrorView_Bool = "showLegacyMirrorView";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_SteamVR_MirrorViewVisibility_Bool = "showMirrorView";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_Steam_VR_Mirror_View_Display_ಬಹುಲಕ_Int32 = "mirrorViewDisplayMode";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_SteamVR_MirrorViewEye_Int32 = "mirrorViewEye";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_SteamVR_MirrorViewGeometry_String = "mirrorViewGeometry";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_SteamVR_MirrorViewGeometryMaximized_String = "mirrorViewGeometryMaximized";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_Steam_VR_Perf_ನಕ್ಷೆ_Visibility_Bool = "showPerfGraph";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_Steam_VR_ಆರಂಭ_Monitor_From_App_Launch = "startMonitorFromAppLaunch";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_Steam_VR_ಆರಂಭ_Compositor_From_App_Launch_Bool = "startCompositorFromAppLaunch";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_Steam_VR_ಆರಂಭ_Dashboard_From_App_Launch_Bool = "startDashboardFromAppLaunch";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_Steam_VR_ಆರಂಭ_Overlay_Apps_From_Dashboard_Bool = "startOverlayAppsFromDashboard";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_SteamVR_EnableHomeApp = "enableHomeApp";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_Steam_VR_ಚಕ್ರ_Background_Image_ಸಮಯ_Sec_Int32 = "CycleBackgroundImageTimeSec";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_SteamVR_RetailDemo_Bool = "retailDemo";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_Steam_VR_Ipd_ಸ್ಥಾನಾಂತರ_Float = "ipdOffset";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_SteamVR_AllowSupersampleFiltering_Bool = "allowSupersampleFiltering";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_SteamVR_SupersampleManualOverride_Bool = "supersampleManualOverride";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_SteamVR_EnableLinuxVulkanAsync_Bool = "enableLinuxVulkanAsync";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_Steam_VR_Allow_Display_Locked_ಬಹುಲಕ_Bool = "allowDisplayLockedMode";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_SteamVR_HaveStartedTutorialForNativeChaperoneDriver_Bool = "haveStartedTutorialForNativeChaperoneDriver";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_SteamVR_ForceWindows32bitVRMonitor = "forceWindows32BitVRMonitor";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_Steam_VR_Debug_ಒಳಹರಿವು_Binding = "debugInputBinding";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_Steam_VR_Do_Not_Fade_ಗಮ್ಯ_Grid = "doNotFadeToGrid";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_Steam_VR_Render_Camera_ಬಹುಲಕ = "renderCameraMode";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_SteamVR_EnableSharedResourceJournaling = "enableSharedResourceJournaling";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_Steam_VR_Enable_ಸುರಕ್ಷಿತ_ಬಹುಲಕ = "enableSafeMode";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_Steam_VR_Preferred_Refresh_ದರ = "preferredRefreshRate";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_Steam_VR_ಕೊನೆಯ_ಆವೃತ್ತಿ_Notice = "lastVersionNotice";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_Steam_VR_ಕೊನೆಯ_ಆವೃತ್ತಿ_Notice_Date = "lastVersionNoticeDate";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_SteamVR_HmdDisplayColorGainR_Float = "hmdDisplayColorGainR";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_SteamVR_HmdDisplayColorGainG_Float = "hmdDisplayColorGainG";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_SteamVR_HmdDisplayColorGainB_Float = "hmdDisplayColorGainB";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_SteamVR_CustomIconStyle_String = "customIconStyle";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_SteamVR_CustomOffIconStyle_String = "customOffIconStyle";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_SteamVR_CustomIconForceUpdate_String = "customIconForceUpdate";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_Steam_VR_Allow_Global_Action_ಗಣ_ಆದ್ಯತೆ = "globalActionSetPriority";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_SteamVR_OverlayRenderQuality = "overlayRenderQuality_2";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_Steam_VR_ಖಂಡ_Oculus_SDKOn_Open_VRLaunch_Option_Bool = "blockOculusSDKOnOpenVRLaunchOption";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_Steam_VR_ಖಂಡ_Oculus_SDKOn_All_Launches_Bool = "blockOculusSDKOnAllLaunches";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_SteamVR_HDCPLegacyCompatibility_Bool = "hdcp14legacyCompatibility";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_Steam_VR_Display_ಪೋರ್ಟ್_Training_ಬಹುಲಕ_Int = "displayPortTrainingMode";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_SteamVR_UsePrism_Bool = "usePrism";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_ನೇರ_ಬಹುಲಕ_Section = "direct_mode";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_ನೇರ_ಬಹುಲಕ_Enable_Bool = "enable";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_ನೇರ_ಬಹುಲಕ_ಎಣಿಕೆ_Int32 = "count";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_ನೇರ_ಬಹುಲಕ_Edid_Vid_Int32 = "edidVid";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_ನೇರ_ಬಹುಲಕ_Edid_Pid_Int32 = "edidPid";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_Lighthouse_Section = "driver_lighthouse";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_Lighthouse_DisableIMU_Bool = "disableimu";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_Lighthouse_DisableIMUExceptHMD_Bool = "disableimuexcepthmd";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_Lighthouse_UseDisambiguation_String = "usedisambiguation";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_Lighthouse_DisambiguationDebug_Int32 = "disambiguationdebug";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_Lighthouse_PrimaryBasestation_Int32 = "primarybasestation";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_Lighthouse_DBHistory_Bool = "dbhistory";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_Lighthouse_EnableBluetooth_Bool = "enableBluetooth";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_Lighthouse_Power_Managed_ತಳ_Stations_String = "PowerManagedBaseStations";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_Lighthouse_Power_Managed_ತಳ_Stations2_String = "PowerManagedBaseStations2";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_Lighthouse_Inactivity_Timeout_For_ತಳ_Stations_Int32 = "InactivityTimeoutForBaseStations";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_Lighthouse_EnableImuFallback_Bool = "enableImuFallback";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_Null_Section = "driver_null";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_Null_Serial_ಸಂಖ್ಯೆ_String = "serialNumber";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_Null_Model_ಸಂಖ್ಯೆ_String = "modelNumber";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_Null_ಕಿಟಕಿ_X_Int32 = "windowX";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_Null_ಕಿಟಕಿ_Y_Int32 = "windowY";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_Null_ಕಿಟಕಿ_ಅಗಲ_Int32 = "windowWidth";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_Null_ಕಿಟಕಿ_ಎತ್ತರ_Int32 = "windowHeight";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_Null_Render_ಅಗಲ_Int32 = "renderWidth";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_Null_Render_ಎತ್ತರ_Int32 = "renderHeight";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_Null_Seconds_From_Vsync_ಗಮ್ಯ_Photons_Float = "secondsFromVsyncToPhotons";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_Null_DisplayFrequency_Float = "displayFrequency";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_WindowsMR_Section = "driver_holographic";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_UserInterface_Section = "userinterface";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_User_Interface_ಸ್ಥಿತಿ_Always_On_ತುದಿ_Bool = "StatusAlwaysOnTop";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_User_Interface_Minimize_ಗಮ್ಯ_Tray_Bool = "MinimizeToTray";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_User_Interface_Hide_Popups_When_ಸ್ಥಿತಿ_Minimized_Bool = "HidePopupsWhenStatusMinimized";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_UserInterface_Screenshots_Bool = "screenshots";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_UserInterface_ScreenshotType_Int = "screenshotType";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_Notifications_Section = "notifications";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_Notifications_DoNotDisturb_Bool = "DoNotDisturb";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_Keyboard_Section = "keyboard";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_Keyboard_TutorialCompletions = "TutorialCompletions";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_Keyboard_ScaleX = "ScaleX";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_Keyboard_ScaleY = "ScaleY";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_Keyboard_ಸ್ಥಾನಾಂತರ_ಎಡ_X = "OffsetLeftX";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_Keyboard_ಸ್ಥಾನಾಂತರ_ಬಲ_X = "OffsetRightX";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_Keyboard_ಸ್ಥಾನಾಂತರ_Y = "OffsetY";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_Keyboard_Smoothing = "Smoothing";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_Perf_Section = "perfcheck";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_Perf_Perf_ನಕ್ಷೆ_ಒಳ_HMD_Bool = "perfGraphInHMD";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_Perf_AllowTimingStore_Bool = "allowTimingStore";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_Perf_SaveTimingsOnExit_Bool = "saveTimingsOnExit";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_Perf_Test_ದತ್ತಾಂಶ_Float = "perfTestData";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_Perf_GPUProfiling_Bool = "GPUProfiling";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_CollisionBounds_Section = "collisionBounds";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_CollisionBounds_Style_Int32 = "CollisionBoundsStyle";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_CollisionBounds_GroundPerimeterOn_Bool = "CollisionBoundsGroundPerimeterOn";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_CollisionBounds_CenterMarkerOn_Bool = "CollisionBoundsCenterMarkerOn";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_CollisionBounds_PlaySpaceOn_Bool = "CollisionBoundsPlaySpaceOn";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_Collision_Bounds_Fade_ದೂರ_Float = "CollisionBoundsFadeDistance";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_Collision_Bounds_Wall_ಎತ್ತರ_Float = "CollisionBoundsWallHeight";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_CollisionBounds_ColorGammaR_Int32 = "CollisionBoundsColorGammaR";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_CollisionBounds_ColorGammaG_Int32 = "CollisionBoundsColorGammaG";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_CollisionBounds_ColorGammaB_Int32 = "CollisionBoundsColorGammaB";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_CollisionBounds_ColorGammaA_Int32 = "CollisionBoundsColorGammaA";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_CollisionBounds_EnableDriverImport = "enableDriverBoundsImport";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_Camera_Section = "camera";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_Camera_EnableCamera_Bool = "enableCamera";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_Camera_ShowOnController_Bool = "showOnController";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_Camera_EnableCameraForCollisionBounds_Bool = "enableCameraForCollisionBounds";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_Camera_ಸ್ಥಳ_View_Int32 = "roomView";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_Camera_BoundsColorGammaR_Int32 = "cameraBoundsColorGammaR";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_Camera_BoundsColorGammaG_Int32 = "cameraBoundsColorGammaG";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_Camera_BoundsColorGammaB_Int32 = "cameraBoundsColorGammaB";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_Camera_BoundsColorGammaA_Int32 = "cameraBoundsColorGammaA";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_Camera_BoundsStrength_Int32 = "cameraBoundsStrength";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_Camera_ಸ್ಥಳ_View_Style_Int32 = "roomViewStyle";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_audio_Section = "audio";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_audio_ಗಣ_Os_Default_Playback_Device_Bool = "setOsDefaultPlaybackDevice";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_audio_EnablePlaybackDeviceOverride_Bool = "enablePlaybackDeviceOverride";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_audio_PlaybackDeviceOverride_String = "playbackDeviceOverride";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_audio_PlaybackDeviceOverrideName_String = "playbackDeviceOverrideName";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_audio_ಗಣ_Os_Default_Recording_Device_Bool = "setOsDefaultRecordingDevice";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_audio_EnableRecordingDeviceOverride_Bool = "enableRecordingDeviceOverride";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_audio_RecordingDeviceOverride_String = "recordingDeviceOverride";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_audio_RecordingDeviceOverrideName_String = "recordingDeviceOverrideName";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_audio_EnablePlaybackMirror_Bool = "enablePlaybackMirror";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_audio_PlaybackMirrorDevice_String = "playbackMirrorDevice";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_audio_PlaybackMirrorDeviceName_String = "playbackMirrorDeviceName";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_audio_OldPlaybackMirrorDevice_String = "onPlaybackMirrorDevice";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_audio_ಸಕ್ರಿಯ_Mirror_Device_String = "activePlaybackMirrorDevice";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_audio_EnablePlaybackMirrorIndependentVolume_Bool = "enablePlaybackMirrorIndependentVolume";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_audio_ಕೊನೆಯ_Hmd_Playback_Device_Id_String = "lastHmdPlaybackDeviceId";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_audio_VIVEHDMIGain = "viveHDMIGain";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_audio_DualSpeakerAndJackOutput_Bool = "dualSpeakerAndJackOutput";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_audio_MuteMicMonitor_Bool = "muteMicMonitor";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_Power_Section = "power";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_Power_PowerOffOnExit_Bool = "powerOffOnExit";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_Power_TurnOffScreensTimeout_Float = "turnOffScreensTimeout";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_Power_TurnOffControllersTimeout_Float = "turnOffControllersTimeout";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_Power_Return_ಗಮ್ಯ_Watchdog_Timeout_Float = "returnToWatchdogTimeout";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_Power_AutoLaunchSteamVROnButtonPress = "autoLaunchSteamVROnButtonPress";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_Power_PauseCompositorOnStandby_Bool = "pauseCompositorOnStandby";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_Dashboard_Section = "dashboard";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_Dashboard_EnableDashboard_Bool = "enableDashboard";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_Dashboard_Arcade_ಬಹುಲಕ_Bool = "arcadeMode";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_Dashboard_Position = "position";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_Dashboard_DesktopScale = "desktopScale";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_Dashboard_DashboardScale = "dashboardScale";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_Dashboard_UseStandaloneSystemLayer = "standaloneSystemLayer";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_Dashboard_StickyDashboard = "stickyDashboard";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_modelskin_Section = "modelskins";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_Driver_Enable_Bool = "enable";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_Driver_BlockedBySafemode_Bool = "blocked_by_safe_mode";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_Driver_ತುಂಬು_ಆದ್ಯತೆ_Int32 = "loadPriority";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_WebInterface_Section = "WebInterface";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_VRWebHelper_Section = "VRWebHelper";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_VRWebHelper_DebuggerEnabled_Bool = "DebuggerEnabled";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_VRWeb_Helper_Debugger_ಪೋರ್ಟ್_Int32 = "DebuggerPort";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_TrackingOverride_Section = "TrackingOverrides";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_App_BindingAutosaveURLSuffix_String = "AutosaveURL";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_App_BindingLegacyAPISuffix_String = "_legacy";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_App_BindingSteamVRInputAPISuffix_String = "_steamvrinput";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_App_BindingOpenXRAPISuffix_String = "_openxr";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_App_BindingCurrentURLSuffix_String = "CurrentURL";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_App_Binding_ಹಿಂದಿನ_URLSuffix_String = "PreviousURL";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_App_Need_ಗಮ್ಯ_Update_Autosave_Suffix_Bool = "NeedToUpdateAutosave";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_App_DominantHand_Int32 = "DominantHand";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_App_ಖಂಡ_Oculus_SDK_Bool = "blockOculusSDK";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_Trackers_Section = "trackers";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_DesktopUI_Section = "DesktopUI";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_ಕೊನೆಯ_ತಿಳಿದ_Section = "LastKnown";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_ಕೊನೆಯ_ತಿಳಿದ_HMDManufacturer_String = "HMDManufacturer";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_ಕೊನೆಯ_ತಿಳಿದ_HMDModel_String = "HMDModel";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_DismissedWarnings_Section = "DismissedWarnings";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_ಒಳಹರಿವು_Section = "input";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_ಒಳಹರಿವು_ಎಡ_Thumbstick_Rotation_Float = "leftThumbstickRotation";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_ಒಳಹರಿವು_ಬಲ_Thumbstick_Rotation_Float = "rightThumbstickRotation";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_ಒಳಹರಿವು_Thumbstick_Deadzone_Float = "thumbstickDeadzone";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_Gpu_ವೇಗ_Section = "GpuSpeed";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * IVRScreenshots_ಆವೃತ್ತಿ = "IVRScreenshots_001";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * IVRResources_ಆವೃತ್ತಿ = "IVRResources_001";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * IVRDriver_Manager_ಆವೃತ್ತಿ = "IVRDriverManager_001";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ k_un_Max_Action_Name_ಉದ್ದಳತೆ = 64;
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ k_un_Max_Action_ಗಣ_Name_ಉದ್ದಳತೆ = 64;
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ k_un_Max_Action_Origin_ಎಣಿಕೆ = 16;
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ k_un_Max_Bone_Name_ಉದ್ದಳತೆ = 32;
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ k_n_Action_ಗಣ_Overlay_Global_ಆದ್ಯತೆ_Min = 16777216;
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ k_n_Action_ಗಣ_Overlay_Global_ಆದ್ಯತೆ_Max = 33554431;
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ k_n_Action_ಗಣ_ಆದ್ಯತೆ_Reserved_Min = 33554432;
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * IVRInput_ಆವೃತ್ತಿ = "IVRInput_010";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ ದೀರ್ಘ k_ulInvalidIOBufferHandle = 0;
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * IVRIOBuffer_ಆವೃತ್ತಿ = "IVRIOBuffer_002";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ k_ulInvalidSpatialAnchorHandle = 0;
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * IVRSpatial_Anchors_ಆವೃತ್ತಿ = "IVRSpatialAnchors_001";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * IVRDebug_ಆವೃತ್ತಿ = "IVRDebug_001";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ ದೀರ್ಘ k_ulDisplayRedirectContainer = 25769803779;
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * IVRProperties_ಆವೃತ್ತಿ = "IVRProperties_001";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_ಮಾರ್ಗ_User_Hand_ಬಲ = "/user/hand/right";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_ಮಾರ್ಗ_User_Hand_ಎಡ = "/user/hand/left";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_ಮಾರ್ಗ_User_Hand_Primary = "/user/hand/primary";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_ಮಾರ್ಗ_User_Hand_Secondary = "/user/hand/secondary";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_ಮಾರ್ಗ_User_ತಲೆ = "/user/head";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_ಮಾರ್ಗ_User_Gamepad = "/user/gamepad";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_ಮಾರ್ಗ_User_Treadmill = "/user/treadmill";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_ಮಾರ್ಗ_User_Stylus = "/user/stylus";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_ಮಾರ್ಗ_Devices = "/devices";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_ಮಾರ್ಗ_Device_ಮಾರ್ಗ = "/device_path";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_ಮಾರ್ಗ_ಉತ್ತಮ_Alias_ಮಾರ್ಗ = "/best_alias_path";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_ಮಾರ್ಗ_Bound_Tracker_Alias_ಮಾರ್ಗ = "/bound_tracker_path";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_ಮಾರ್ಗ_Bound_Tracker_Role = "/bound_tracker_role";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_ಮಾರ್ಗ_Pose_Raw = "/pose/raw";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_ಮಾರ್ಗ_Pose_Tip = "/pose/tip";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_ಮಾರ್ಗ_Pose_Grip = "/pose/grip";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_ಮಾರ್ಗ_System_Button_Click = "/input/system/click";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_ಮಾರ್ಗ_Proximity = "/proximity";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_ಮಾರ್ಗ_Controller_Type_ಪೂರ್ವಪ್ರತ್ಯಯ = "/controller_type/";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_ಮಾರ್ಗ_ಒಳಹರಿವು_Profile_Suffix = "/input_profile";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_ಮಾರ್ಗ_Binding_Name_Suffix = "/binding_name";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_ಮಾರ್ಗ_Binding_Url_Suffix = "/binding_url";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_ಮಾರ್ಗ_Binding_Error_Suffix = "/binding_error";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_ಮಾರ್ಗ_ಸಕ್ರಿಯ_Action_Sets = "/active_action_sets";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_ಮಾರ್ಗ_Component_Updates = "/total_component_updates";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_ಮಾರ್ಗ_User_Foot_ಎಡ = "/user/foot/left";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_ಮಾರ್ಗ_User_Foot_ಬಲ = "/user/foot/right";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_ಮಾರ್ಗ_User_Shoulder_ಎಡ = "/user/shoulder/left";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_ಮಾರ್ಗ_User_Shoulder_ಬಲ = "/user/shoulder/right";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_ಮಾರ್ಗ_User_Elbow_ಎಡ = "/user/elbow/left";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_ಮಾರ್ಗ_User_Elbow_ಬಲ = "/user/elbow/right";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_ಮಾರ್ಗ_User_Knee_ಎಡ = "/user/knee/left";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_ಮಾರ್ಗ_User_Knee_ಬಲ = "/user/knee/right";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_ಮಾರ್ಗ_User_Waist = "/user/waist";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_ಮಾರ್ಗ_User_Chest = "/user/chest";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_ಮಾರ್ಗ_User_Camera = "/user/camera";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_ಮಾರ್ಗ_User_Keyboard = "/user/keyboard";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * k_pch_ಮಾರ್ಗ_Client_App_ಕೀಲಿ = "/client_info/app_key";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ ದೀರ್ಘ k_ul_Invalid_ಮಾರ್ಗ_Handle = 0;
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * IVRPaths_ಆವೃತ್ತಿ = "IVRPaths_001";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * IVRBlock_ಸರತಿ_ಆವೃತ್ತಿ = "IVRBlockQueue_005";

// OpenVR Enums

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ EVREye
{
	EVREye_Eye_ಎಡ = 0,
	EVREye_Eye_ಬಲ = 1,
} EVREye;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ ETextureType
{
	ETextureType_TextureType_Invalid = -1,
	ETexture_Type_Texture_Type_ನೇರ_X = 0,
	ETextureType_TextureType_OpenGL = 1,
	ETextureType_TextureType_Vulkan = 2,
	ETextureType_TextureType_IOSurface = 3,
	ETexture_Type_Texture_Type_ನೇರ_X12 = 4,
	ETextureType_TextureType_DXGISharedHandle = 5,
	ETextureType_TextureType_Metal = 6,
} ETextureType;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ EColorSpace
{
	EColorSpace_ColorSpace_Auto = 0,
	EColorSpace_ColorSpace_Gamma = 1,
	EColor_Space_Color_Space_ರೇಖೀಯ = 2,
} EColorSpace;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ ETracking_ಫಲಿತಾಂಶ
{
	ETracking_ಫಲಿತಾಂಶ_Tracking_ಫಲಿತಾಂಶ_Uninitialized = 1,
	ETracking_ಫಲಿತಾಂಶ_Tracking_ಫಲಿತಾಂಶ_Calibrating_ಒಳ_ಪ್ರಗತಿ = 100,
	ETracking_ಫಲಿತಾಂಶ_Tracking_ಫಲಿತಾಂಶ_Calibrating_ಹೊರಹೋಗು_ದ_Range = 101,
	ETracking_ಫಲಿತಾಂಶ_Tracking_ಫಲಿತಾಂಶ_Running_OK = 200,
	ETracking_ಫಲಿತಾಂಶ_Tracking_ಫಲಿತಾಂಶ_Running_ಹೊರಹೋಗು_ದ_Range = 201,
	ETracking_ಫಲಿತಾಂಶ_Tracking_ಫಲಿತಾಂಶ_Fallback_Rotation_Only = 300,
} ETracking_ಫಲಿತಾಂಶ;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ ETrackedDeviceClass
{
	ETrackedDeviceClass_TrackedDeviceClass_Invalid = 0,
	ETrackedDeviceClass_TrackedDeviceClass_HMD = 1,
	ETrackedDeviceClass_TrackedDeviceClass_Controller = 2,
	ETrackedDeviceClass_TrackedDeviceClass_GenericTracker = 3,
	ETrackedDeviceClass_TrackedDeviceClass_TrackingReference = 4,
	ETrackedDeviceClass_TrackedDeviceClass_DisplayRedirect = 5,
	ETrackedDeviceClass_TrackedDeviceClass_Max = 6,
} ETrackedDeviceClass;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ ETrackedControllerRole
{
	ETrackedControllerRole_TrackedControllerRole_Invalid = 0,
	ETracked_Controller_Role_Tracked_Controller_Role_ಎಡ_Hand = 1,
	ETracked_Controller_Role_Tracked_Controller_Role_ಬಲ_Hand = 2,
	ETracked_Controller_Role_Tracked_Controller_Role_Opt_ಹೊರಹೋಗು = 3,
	ETrackedControllerRole_TrackedControllerRole_Treadmill = 4,
	ETrackedControllerRole_TrackedControllerRole_Stylus = 5,
	ETrackedControllerRole_TrackedControllerRole_Max = 5,
} ETrackedControllerRole;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ ETrackingUniverseOrigin
{
	ETrackingUniverseOrigin_TrackingUniverseSeated = 0,
	ETrackingUniverseOrigin_TrackingUniverseStanding = 1,
	ETrackingUniverseOrigin_TrackingUniverseRawAndUncalibrated = 2,
} ETrackingUniverseOrigin;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ EAdditionalRadioFeatures
{
	EAdditionalRadioFeatures_AdditionalRadioFeatures_None = 0,
	EAdditionalRadioFeatures_AdditionalRadioFeatures_HTCLinkBox = 1,
	EAdditional_Radio_Features_Additional_Radio_Features_ಆಂತರಿಕ_Dongle = 2,
	EAdditionalRadioFeatures_AdditionalRadioFeatures_ExternalDongle = 4,
} EAdditionalRadioFeatures;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ ETrackedDeviceProperty
{
	ETrackedDeviceProperty_Prop_Invalid = 0,
	ETrackedDeviceProperty_Prop_TrackingSystemName_String = 1000,
	ETracked_Device_Property_Prop_Model_ಸಂಖ್ಯೆ_String = 1001,
	ETracked_Device_Property_Prop_Serial_ಸಂಖ್ಯೆ_String = 1002,
	ETrackedDeviceProperty_Prop_RenderModelName_String = 1003,
	ETracked_Device_Property_Prop_Will_Drift_ಒಳ_Yaw_Bool = 1004,
	ETrackedDeviceProperty_Prop_ManufacturerName_String = 1005,
	ETracked_Device_Property_Prop_Tracking_Firmware_ಆವೃತ್ತಿ_String = 1006,
	ETrackedDeviceProperty_Prop_HardwareRevision_String = 1007,
	ETrackedDeviceProperty_Prop_AllWirelessDongleDescriptions_String = 1008,
	ETrackedDeviceProperty_Prop_ConnectedWirelessDongle_String = 1009,
	ETrackedDeviceProperty_Prop_DeviceIsWireless_Bool = 1010,
	ETrackedDeviceProperty_Prop_DeviceIsCharging_Bool = 1011,
	ETrackedDeviceProperty_Prop_DeviceBatteryPercentage_Float = 1012,
	ETracked_Device_Property_Prop_ಸ್ಥಿತಿ_Display_Transform_Matrix34 = 1013,
	ETracked_Device_Property_Prop_Firmware_Update_ಲಭ್ಯ_Bool = 1014,
	ETrackedDeviceProperty_Prop_Firmware_ManualUpdate_Bool = 1015,
	ETrackedDeviceProperty_Prop_Firmware_ManualUpdateURL_String = 1016,
	ETrackedDeviceProperty_Prop_HardwareRevision_Uint64 = 1017,
	ETracked_Device_Property_Prop_Firmware_ಆವೃತ್ತಿ_Uint64 = 1018,
	ETrackedDeviceProperty_Prop_FPGAVersion_Uint64 = 1019,
	ETrackedDeviceProperty_Prop_VRCVersion_Uint64 = 1020,
	ETracked_Device_Property_Prop_Radio_ಆವೃತ್ತಿ_Uint64 = 1021,
	ETracked_Device_Property_Prop_Dongle_ಆವೃತ್ತಿ_Uint64 = 1022,
	ETracked_Device_Property_Prop_ಖಂಡ_Server_Shutdown_Bool = 1023,
	ETrackedDeviceProperty_Prop_CanUnifyCoordinateSystemWithHmd_Bool = 1024,
	ETracked_Device_Property_Prop_ಒಳಗೊಂಡಿದೆ_Proximity_Sensor_Bool = 1025,
	ETracked_Device_Property_Prop_Device_Provides_Battery_ಸ್ಥಿತಿ_Bool = 1026,
	ETrackedDeviceProperty_Prop_DeviceCanPowerOff_Bool = 1027,
	ETracked_Device_Property_Prop_Firmware_Programming_ಗುರಿ_String = 1028,
	ETrackedDeviceProperty_Prop_DeviceClass_Int32 = 1029,
	ETrackedDeviceProperty_Prop_HasCamera_Bool = 1030,
	ETracked_Device_Property_Prop_Driver_ಆವೃತ್ತಿ_String = 1031,
	ETrackedDeviceProperty_Prop_Firmware_ForceUpdateRequired_Bool = 1032,
	ETrackedDeviceProperty_Prop_ViveSystemButtonFixRequired_Bool = 1033,
	ETracked_Device_Property_Prop_ಪೋಷಕ_Driver_Uint64 = 1034,
	ETracked_Device_Property_Prop_Resource_ಬೇರು_String = 1035,
	ETrackedDeviceProperty_Prop_RegisteredDeviceType_String = 1036,
	ETracked_Device_Property_Prop_ಒಳಹರಿವು_Profile_ಮಾರ್ಗ_String = 1037,
	ETrackedDeviceProperty_Prop_NeverTracked_Bool = 1038,
	ETracked_Device_Property_Prop_ಅಂಕೆ_Cameras_Int32 = 1039,
	ETracked_Device_Property_Prop_Camera_ಚೌಕಟ್ಟು_Layout_Int32 = 1040,
	ETracked_Device_Property_Prop_Camera_ಹರಿವು_Format_Int32 = 1041,
	ETracked_Device_Property_Prop_Additional_Device_Settings_ಮಾರ್ಗ_String = 1042,
	ETrackedDeviceProperty_Prop_Identifiable_Bool = 1043,
	ETracked_Device_Property_Prop_Bootloader_ಆವೃತ್ತಿ_Uint64 = 1044,
	ETracked_Device_Property_Prop_Additional_System_Report_ದತ್ತಾಂಶ_String = 1045,
	ETracked_Device_Property_Prop_ಸಂಯುಕ್ತ_Firmware_ಆವೃತ್ತಿ_String = 1046,
	ETrackedDeviceProperty_Prop_Firmware_RemindUpdate_Bool = 1047,
	ETracked_Device_Property_Prop_Peripheral_Application_ಆವೃತ್ತಿ_Uint64 = 1048,
	ETracked_Device_Property_Prop_Manufacturer_Serial_ಸಂಖ್ಯೆ_String = 1049,
	ETracked_Device_Property_Prop_Computed_Serial_ಸಂಖ್ಯೆ_String = 1050,
	ETracked_Device_Property_Prop_Estimated_Device_ಮೊದಲ_Use_ಸಮಯ_Int32 = 1051,
	ETrackedDeviceProperty_Prop_DevicePowerUsage_Float = 1052,
	ETrackedDeviceProperty_Prop_IgnoreMotionForStandby_Bool = 1053,
	ETracked_Device_Property_Prop_Reports_ಸಮಯ_Since_VSync_Bool = 2000,
	ETracked_Device_Property_Prop_Seconds_From_Vsync_ಗಮ್ಯ_Photons_Float = 2001,
	ETrackedDeviceProperty_Prop_DisplayFrequency_Float = 2002,
	ETrackedDeviceProperty_Prop_UserIpdMeters_Float = 2003,
	ETrackedDeviceProperty_Prop_CurrentUniverseId_Uint64 = 2004,
	ETracked_Device_Property_Prop_ಹಿಂದಿನ_Universe_Id_Uint64 = 2005,
	ETracked_Device_Property_Prop_Display_Firmware_ಆವೃತ್ತಿ_Uint64 = 2006,
	ETrackedDeviceProperty_Prop_IsOnDesktop_Bool = 2007,
	ETrackedDeviceProperty_Prop_DisplayMCType_Int32 = 2008,
	ETrackedDeviceProperty_Prop_DisplayMCOffset_Float = 2009,
	ETrackedDeviceProperty_Prop_DisplayMCScale_Float = 2010,
	ETrackedDeviceProperty_Prop_EdidVendorID_Int32 = 2011,
	ETracked_Device_Property_Prop_Display_MCImage_ಎಡ_String = 2012,
	ETracked_Device_Property_Prop_Display_MCImage_ಬಲ_String = 2013,
	ETrackedDeviceProperty_Prop_DisplayGCBlackClamp_Float = 2014,
	ETracked_Device_Property_Prop_Edid_ಗುಣಲಬ್ಧ_ID_Int32 = 2015,
	ETracked_Device_Property_Prop_Camera_ಗಮ್ಯ_ತಲೆ_Transform_Matrix34 = 2016,
	ETrackedDeviceProperty_Prop_DisplayGCType_Int32 = 2017,
	ETrackedDeviceProperty_Prop_DisplayGCOffset_Float = 2018,
	ETrackedDeviceProperty_Prop_DisplayGCScale_Float = 2019,
	ETrackedDeviceProperty_Prop_DisplayGCPrescale_Float = 2020,
	ETrackedDeviceProperty_Prop_DisplayGCImage_String = 2021,
	ETracked_Device_Property_Prop_Lens_Center_ಎಡ_U_Float = 2022,
	ETracked_Device_Property_Prop_Lens_Center_ಎಡ_V_Float = 2023,
	ETracked_Device_Property_Prop_Lens_Center_ಬಲ_U_Float = 2024,
	ETracked_Device_Property_Prop_Lens_Center_ಬಲ_V_Float = 2025,
	ETracked_Device_Property_Prop_User_ತಲೆ_ಗಮ್ಯ_Eye_ಆಳ_Meters_Float = 2026,
	ETracked_Device_Property_Prop_Camera_Firmware_ಆವೃತ್ತಿ_Uint64 = 2027,
	ETrackedDeviceProperty_Prop_CameraFirmwareDescription_String = 2028,
	ETrackedDeviceProperty_Prop_DisplayFPGAVersion_Uint64 = 2029,
	ETracked_Device_Property_Prop_Display_Bootloader_ಆವೃತ್ತಿ_Uint64 = 2030,
	ETracked_Device_Property_Prop_Display_Hardware_ಆವೃತ್ತಿ_Uint64 = 2031,
	ETracked_Device_Property_Prop_Audio_Firmware_ಆವೃತ್ತಿ_Uint64 = 2032,
	ETracked_Device_Property_Prop_Camera_Compatibility_ಬಹುಲಕ_Int32 = 2033,
	ETracked_Device_Property_Prop_Screenshot_Horizontal_ಕ್ಷೇತ್ರ_ದ_View_Degrees_Float = 2034,
	ETracked_Device_Property_Prop_Screenshot_Vertical_ಕ್ಷೇತ್ರ_ದ_View_Degrees_Float = 2035,
	ETrackedDeviceProperty_Prop_DisplaySuppressed_Bool = 2036,
	ETracked_Device_Property_Prop_Display_Allow_Night_ಬಹುಲಕ_Bool = 2037,
	ETracked_Device_Property_Prop_Display_MCImage_ಅಗಲ_Int32 = 2038,
	ETracked_Device_Property_Prop_Display_MCImage_ಎತ್ತರ_Int32 = 2039,
	ETracked_Device_Property_Prop_Display_MCImage_ಅಂಕೆ_Channels_Int32 = 2040,
	ETracked_Device_Property_Prop_Display_MCImage_ದತ್ತಾಂಶ_ದ್ವಿಮಾನ = 2041,
	ETracked_Device_Property_Prop_Seconds_From_Photons_ಗಮ್ಯ_Vblank_Float = 2042,
	ETracked_Device_Property_Prop_Driver_ನೇರ_ಬಹುಲಕ_Sends_Vsync_Events_Bool = 2043,
	ETracked_Device_Property_Prop_Display_Debug_ಬಹುಲಕ_Bool = 2044,
	ETrackedDeviceProperty_Prop_GraphicsAdapterLuid_Uint64 = 2045,
	ETracked_Device_Property_Prop_Driver_Provided_Chaperone_ಮಾರ್ಗ_String = 2048,
	ETracked_Device_Property_Prop_Expected_Tracking_Reference_ಎಣಿಕೆ_Int32 = 2049,
	ETracked_Device_Property_Prop_Expected_Controller_ಎಣಿಕೆ_Int32 = 2050,
	ETracked_Device_Property_Prop_Named_Icon_ಮಾರ್ಗ_Controller_ಎಡ_Device_Off_String = 2051,
	ETracked_Device_Property_Prop_Named_Icon_ಮಾರ್ಗ_Controller_ಬಲ_Device_Off_String = 2052,
	ETracked_Device_Property_Prop_Named_Icon_ಮಾರ್ಗ_Tracking_Reference_Device_Off_String = 2053,
	ETrackedDeviceProperty_Prop_DoNotApplyPrediction_Bool = 2054,
	ETracked_Device_Property_Prop_Camera_ಗಮ್ಯ_ತಲೆ_Transforms_Matrix34_Array = 2055,
	ETrackedDeviceProperty_Prop_DistortionMeshResolution_Int32 = 2056,
	ETrackedDeviceProperty_Prop_DriverIsDrawingControllers_Bool = 2057,
	ETracked_Device_Property_Prop_Driver_ವಿನಂತಿಗಳು_Application_Pause_Bool = 2058,
	ETracked_Device_Property_Prop_Driver_ವಿನಂತಿಗಳು_Reduced_Rendering_Bool = 2059,
	ETracked_Device_Property_Prop_Minimum_Ipd_ಹೆಜ್ಜೆ_Meters_Float = 2060,
	ETracked_Device_Property_Prop_Audio_Bridge_Firmware_ಆವೃತ್ತಿ_Uint64 = 2061,
	ETracked_Device_Property_Prop_Image_Bridge_Firmware_ಆವೃತ್ತಿ_Uint64 = 2062,
	ETracked_Device_Property_Prop_Imu_ಗಮ್ಯ_ತಲೆ_Transform_Matrix34 = 2063,
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
	ETracked_Device_Property_Prop_Hmd_ಸ್ತಂಭ_Correction_Setting_ಪೂರ್ವಪ್ರತ್ಯಯ_String = 2077,
	ETrackedDeviceProperty_Prop_CameraSupportsCompatibilityModes_Bool = 2078,
	ETracked_Device_Property_Prop_Supports_ಸ್ಥಳ_View_ಆಳ_Projection_Bool = 2079,
	ETracked_Device_Property_Prop_Display_ಲಭ್ಯ_ಚೌಕಟ್ಟು_Rates_Float_Array = 2080,
	ETracked_Device_Property_Prop_Display_Supports_ಅಪವರ್ತ್ಯ_Framerates_Bool = 2081,
	ETracked_Device_Property_Prop_Display_Color_Mult_ಎಡ_Vector3 = 2082,
	ETracked_Device_Property_Prop_Display_Color_Mult_ಬಲ_Vector3 = 2083,
	ETrackedDeviceProperty_Prop_DisplaySupportsRuntimeFramerateChange_Bool = 2084,
	ETrackedDeviceProperty_Prop_DisplaySupportsAnalogGain_Bool = 2085,
	ETrackedDeviceProperty_Prop_DisplayMinAnalogGain_Float = 2086,
	ETrackedDeviceProperty_Prop_DisplayMaxAnalogGain_Float = 2087,
	ETracked_Device_Property_Prop_Camera_Exposure_ಸಮಯ_Float = 2088,
	ETrackedDeviceProperty_Prop_CameraGlobalGain_Float = 2089,
	ETrackedDeviceProperty_Prop_DashboardScale_Float = 2091,
	ETrackedDeviceProperty_Prop_PeerButtonInfo_String = 2092,
	ETrackedDeviceProperty_Prop_Hmd_SupportsHDR10_Bool = 2093,
	ETrackedDeviceProperty_Prop_IpdUIRangeMinMeters_Float = 2100,
	ETrackedDeviceProperty_Prop_IpdUIRangeMaxMeters_Float = 2101,
	ETrackedDeviceProperty_Prop_Hmd_SupportsHDCP14LegacyCompat_Bool = 2102,
	ETrackedDeviceProperty_Prop_Hmd_SupportsMicMonitoring_Bool = 2103,
	ETracked_Device_Property_Prop_Hmd_Supports_Display_ಪೋರ್ಟ್_Training_ಬಹುಲಕ_Bool = 2104,
	ETracked_Device_Property_Prop_Supports_ಸ್ಥಳ_View_ನೇರ_Bool = 2105,
	ETrackedDeviceProperty_Prop_SupportsAppThrottling_Bool = 2106,
	ETrackedDeviceProperty_Prop_DSCVersion_Int32 = 2110,
	ETracked_Device_Property_Prop_DSCSlice_ಎಣಿಕೆ_Int32 = 2111,
	ETrackedDeviceProperty_Prop_DSCBPPx16_Int32 = 2112,
	ETracked_Device_Property_Prop_Driver_Requested_Mura_Correction_ಬಹುಲಕ_Int32 = 2200,
	ETracked_Device_Property_Prop_Driver_Requested_Mura_Feather_Inner_ಎಡ_Int32 = 2201,
	ETracked_Device_Property_Prop_Driver_Requested_Mura_Feather_Inner_ಬಲ_Int32 = 2202,
	ETracked_Device_Property_Prop_Driver_Requested_Mura_Feather_Inner_ತುದಿ_Int32 = 2203,
	ETrackedDeviceProperty_Prop_DriverRequestedMuraFeather_InnerBottom_Int32 = 2204,
	ETracked_Device_Property_Prop_Driver_Requested_Mura_Feather_Outer_ಎಡ_Int32 = 2205,
	ETracked_Device_Property_Prop_Driver_Requested_Mura_Feather_Outer_ಬಲ_Int32 = 2206,
	ETracked_Device_Property_Prop_Driver_Requested_Mura_Feather_Outer_ತುದಿ_Int32 = 2207,
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
	ETracked_Device_Property_Prop_ಕ್ಷೇತ್ರ_ದ_View_ಎಡ_Degrees_Float = 4000,
	ETracked_Device_Property_Prop_ಕ್ಷೇತ್ರ_ದ_View_ಬಲ_Degrees_Float = 4001,
	ETracked_Device_Property_Prop_ಕ್ಷೇತ್ರ_ದ_View_ತುದಿ_Degrees_Float = 4002,
	ETracked_Device_Property_Prop_ಕ್ಷೇತ್ರ_ದ_View_Bottom_Degrees_Float = 4003,
	ETrackedDeviceProperty_Prop_TrackingRangeMinimumMeters_Float = 4004,
	ETracked_Device_Property_Prop_Tracking_Range_ಗರಿಷ್ಠ_Meters_Float = 4005,
	ETracked_Device_Property_Prop_ಬಹುಲಕ_Label_String = 4006,
	ETrackedDeviceProperty_Prop_CanWirelessIdentify_Bool = 4007,
	ETrackedDeviceProperty_Prop_Nonce_Int32 = 4008,
	ETracked_Device_Property_Prop_Icon_ಮಾರ್ಗ_Name_String = 5000,
	ETracked_Device_Property_Prop_Named_Icon_ಮಾರ್ಗ_Device_Off_String = 5001,
	ETracked_Device_Property_Prop_Named_Icon_ಮಾರ್ಗ_Device_Searching_String = 5002,
	ETracked_Device_Property_Prop_Named_Icon_ಮಾರ್ಗ_Device_Searching_Alert_String = 5003,
	ETracked_Device_Property_Prop_Named_Icon_ಮಾರ್ಗ_Device_Ready_String = 5004,
	ETracked_Device_Property_Prop_Named_Icon_ಮಾರ್ಗ_Device_Ready_Alert_String = 5005,
	ETracked_Device_Property_Prop_Named_Icon_ಮಾರ್ಗ_Device_Not_Ready_String = 5006,
	ETracked_Device_Property_Prop_Named_Icon_ಮಾರ್ಗ_Device_Standby_String = 5007,
	ETracked_Device_Property_Prop_Named_Icon_ಮಾರ್ಗ_Device_Alert_ಕೆಳಗಿನ_String = 5008,
	ETracked_Device_Property_Prop_Named_Icon_ಮಾರ್ಗ_Device_Standby_Alert_String = 5009,
	ETracked_Device_Property_Prop_Display_Hidden_Area_ದ್ವಿಮಾನ_ಆರಂಭ = 5100,
	ETracked_Device_Property_Prop_Display_Hidden_Area_ದ್ವಿಮಾನ_ಕೊನೆ = 5150,
	ETracked_Device_Property_Prop_ಪೋಷಕ_Container = 5151,
	ETrackedDeviceProperty_Prop_OverrideContainer_Uint64 = 5152,
	ETracked_Device_Property_Prop_User_Config_ಮಾರ್ಗ_String = 6000,
	ETracked_Device_Property_Prop_Install_ಮಾರ್ಗ_String = 6001,
	ETrackedDeviceProperty_Prop_HasDisplayComponent_Bool = 6002,
	ETrackedDeviceProperty_Prop_HasControllerComponent_Bool = 6003,
	ETrackedDeviceProperty_Prop_HasCameraComponent_Bool = 6004,
	ETracked_Device_Property_Prop_Has_Driver_ನೇರ_ಬಹುಲಕ_Component_Bool = 6005,
	ETrackedDeviceProperty_Prop_HasVirtualDisplayComponent_Bool = 6006,
	ETrackedDeviceProperty_Prop_HasSpatialAnchorsSupport_Bool = 6007,
	ETrackedDeviceProperty_Prop_ControllerType_String = 7000,
	ETracked_Device_Property_Prop_Controller_Hand_Selection_ಆದ್ಯತೆ_Int32 = 7002,
	ETracked_Device_Property_Prop_Vendor_Specific_Reserved_ಆರಂಭ = 10000,
	ETracked_Device_Property_Prop_Vendor_Specific_Reserved_ಕೊನೆ = 10999,
	ETrackedDeviceProperty_Prop_TrackedDeviceProperty_Max = 1000000,
} ETrackedDeviceProperty;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ ETrackedPropertyError
{
	ETrackedPropertyError_TrackedProp_Success = 0,
	ETracked_Property_Error_Tracked_Prop_Wrong_ದತ್ತಾಂಶ_Type = 1,
	ETrackedPropertyError_TrackedProp_WrongDeviceClass = 2,
	ETracked_Property_Error_Tracked_Prop_ಬಫರ್_Too_Small = 3,
	ETrackedPropertyError_TrackedProp_UnknownProperty = 4,
	ETrackedPropertyError_TrackedProp_InvalidDevice = 5,
	ETrackedPropertyError_TrackedProp_CouldNotContactServer = 6,
	ETracked_Property_Error_Tracked_Prop_ಮೌಲ್ಯ_Not_Provided_By_Device = 7,
	ETracked_Property_Error_Tracked_Prop_String_Exceeds_ಗರಿಷ್ಠ_ಉದ್ದಳತೆ = 8,
	ETracked_Property_Error_Tracked_Prop_Not_Yet_ಲಭ್ಯ = 9,
	ETrackedPropertyError_TrackedProp_PermissionDenied = 10,
	ETrackedPropertyError_TrackedProp_InvalidOperation = 11,
	ETracked_Property_Error_Tracked_Prop_Cannot_Write_ಗಮ್ಯ_Wildcards = 12,
	ETrackedPropertyError_TrackedProp_IPCReadFailure = 13,
	ETracked_Property_Error_Tracked_Prop_ಹೊರಹೋಗು_ದ_ಸ್ಮರಣೆ = 14,
	ETrackedPropertyError_TrackedProp_InvalidContainer = 15,
} ETrackedPropertyError;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ EHmdTrackingStyle
{
	EHmdTrackingStyle_HmdTrackingStyle_Unknown = 0,
	EHmdTrackingStyle_HmdTrackingStyle_Lighthouse = 1,
	EHmd_Tracking_Style_Hmd_Tracking_Style_Outside_ಒಳ_Cameras = 2,
	EHmd_Tracking_Style_Hmd_Tracking_Style_Inside_ಹೊರಹೋಗು_Cameras = 3,
} EHmdTrackingStyle;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ EVRSubmitFlags
{
	EVRSubmitFlags_Submit_Default = 0,
	EVRSubmitFlags_Submit_LensDistortionAlreadyApplied = 1,
	EVRSubmit_Flags_Submit_Gl_Render_ಬಫರ್ = 2,
	EVRSubmitFlags_Submit_Reserved = 4,
	EVRSubmitFlags_Submit_TextureWithPose = 8,
	EVRSubmit_Flags_Submit_Texture_With_ಆಳ = 16,
	EVRSubmit_Flags_Submit_ಚೌಕಟ್ಟು_Discontinuty = 32,
	EVRSubmit_Flags_Submit_Vulkan_Texture_With_Array_ದತ್ತಾಂಶ = 64,
	EVRSubmitFlags_Submit_GlArrayTexture = 128,
	EVRSubmitFlags_Submit_Reserved2 = 32768,
	EVRSubmitFlags_Submit_Reserved3 = 65536,
} EVRSubmitFlags;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ EVRState
{
	EVRState_VRState_Undefined = -1,
	EVRState_VRState_Off = 0,
	EVRState_VRState_Searching = 1,
	EVRState_VRState_Searching_Alert = 2,
	EVRState_VRState_Ready = 3,
	EVRState_VRState_Ready_Alert = 4,
	EVRState_VRState_NotReady = 5,
	EVRState_VRState_Standby = 6,
	EVRState_VRState_Ready_Alert_ಕೆಳಗಿನ = 7,
} EVRState;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ EVREventType
{
	EVREventType_VREvent_None = 0,
	EVREventType_VREvent_TrackedDeviceActivated = 100,
	EVREventType_VREvent_TrackedDeviceDeactivated = 101,
	EVREventType_VREvent_TrackedDeviceUpdated = 102,
	EVREventType_VREvent_TrackedDeviceUserInteractionStarted = 103,
	EVREventType_VREvent_TrackedDeviceUserInteractionEnded = 104,
	EVREvent_Type_VREvent_Ipd_ಬದಲಾಯಿತು = 105,
	EVREvent_Type_VREvent_Enter_Standby_ಬಹುಲಕ = 106,
	EVREvent_Type_VREvent_Leave_Standby_ಬಹುಲಕ = 107,
	EVREvent_Type_VREvent_Tracked_Device_Role_ಬದಲಾಯಿತು = 108,
	EVREvent_Type_VREvent_Watchdog_Wake_ಮೇಲೆ_Requested = 109,
	EVREvent_Type_VREvent_Lens_Distortion_ಬದಲಾಯಿತು = 110,
	EVREvent_Type_VREvent_Property_ಬದಲಾಯಿತು = 111,
	EVREventType_VREvent_WirelessDisconnect = 112,
	EVREventType_VREvent_WirelessReconnect = 113,
	EVREventType_VREvent_ButtonPress = 200,
	EVREventType_VREvent_ButtonUnpress = 201,
	EVREventType_VREvent_ButtonTouch = 202,
	EVREventType_VREvent_ButtonUntouch = 203,
	EVREventType_VREvent_Modal_Cancel = 257,
	EVREventType_VREvent_MouseMove = 300,
	EVREvent_Type_VREvent_Mouse_Button_ಕೆಳಕ್ಕೆ = 301,
	EVREvent_Type_VREvent_Mouse_Button_ಮೇಲೆ = 302,
	EVREventType_VREvent_FocusEnter = 303,
	EVREventType_VREvent_FocusLeave = 304,
	EVREventType_VREvent_ScrollDiscrete = 305,
	EVREventType_VREvent_TouchPadMove = 306,
	EVREvent_Type_VREvent_Overlay_Focus_ಬದಲಾಯಿತು = 307,
	EVREventType_VREvent_ReloadOverlays = 308,
	EVREventType_VREvent_ScrollSmooth = 309,
	EVREvent_Type_VREvent_ಬೀಗ_Mouse_Position = 310,
	EVREventType_VREvent_UnlockMousePosition = 311,
	EVREvent_Type_VREvent_ಒಳಹರಿವು_Focus_Captured = 400,
	EVREvent_Type_VREvent_ಒಳಹರಿವು_Focus_Released = 401,
	EVREvent_Type_VREvent_Scene_Application_ಬದಲಾಯಿತು = 404,
	EVREvent_Type_VREvent_ಒಳಹರಿವು_Focus_ಬದಲಾಯಿತು = 406,
	EVREventType_VREvent_SceneApplicationUsingWrongGraphicsAdapter = 408,
	EVREventType_VREvent_ActionBindingReloaded = 409,
	EVREventType_VREvent_HideRenderModels = 410,
	EVREventType_VREvent_ShowRenderModels = 411,
	EVREvent_Type_VREvent_Scene_Application_State_ಬದಲಾಯಿತು = 412,
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
	EVREvent_Type_VREvent_Overlay_Gamepad_Focus_ಕಳೆದುಹೋದ = 512,
	EVREvent_Type_VREvent_Overlay_Shared_Texture_ಬದಲಾಯಿತು = 513,
	EVREventType_VREvent_ScreenshotTriggered = 516,
	EVREventType_VREvent_ImageFailed = 517,
	EVREventType_VREvent_DashboardOverlayCreated = 518,
	EVREventType_VREvent_SwitchGamepadFocus = 519,
	EVREventType_VREvent_RequestScreenshot = 520,
	EVREvent_Type_VREvent_Screenshot_ತೆಗೆದುಕೊಂಡ = 521,
	EVREventType_VREvent_ScreenshotFailed = 522,
	EVREvent_Type_VREvent_Submit_Screenshot_ಗಮ್ಯ_Dashboard = 523,
	EVREvent_Type_VREvent_Screenshot_ಪ್ರಗತಿ_ಗಮ್ಯ_Dashboard = 524,
	EVREvent_Type_VREvent_Primary_Dashboard_Device_ಬದಲಾಯಿತು = 525,
	EVREvent_Type_VREvent_ಸ್ಥಳ_View_Shown = 526,
	EVREvent_Type_VREvent_ಸ್ಥಳ_View_Hidden = 527,
	EVREventType_VREvent_ShowUI = 528,
	EVREventType_VREvent_ShowDevTools = 529,
	EVREventType_VREvent_DesktopViewUpdating = 530,
	EVREventType_VREvent_DesktopViewReady = 531,
	EVREvent_Type_VREvent_ಆರಂಭ_Dashboard = 532,
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
	EVREvent_Type_VREvent_Invalidate_ಅದಲುಬದಲು_Texture_Sets = 706,
	EVREvent_Type_VREvent_Chaperone_ದತ್ತಾಂಶ_Has_ಬದಲಾಯಿತು = 800,
	EVREvent_Type_VREvent_Chaperone_Universe_Has_ಬದಲಾಯಿತು = 801,
	EVREvent_Type_VREvent_Chaperone_ತಾತ್ಕಾಲಿಕ_ದತ್ತಾಂಶ_Has_ಬದಲಾಯಿತು = 802,
	EVREvent_Type_VREvent_Chaperone_Settings_Have_ಬದಲಾಯಿತು = 803,
	EVREventType_VREvent_SeatedZeroPoseReset = 804,
	EVREventType_VREvent_ChaperoneFlushCache = 805,
	EVREvent_Type_VREvent_Chaperone_ಸ್ಥಳ_ಸಿದ್ಧತೆ_Starting = 806,
	EVREvent_Type_VREvent_Chaperone_ಸ್ಥಳ_ಸಿದ್ಧತೆ_ಪೂರ್ಣಗೊಂಡ = 807,
	EVREventType_VREvent_StandingZeroPoseReset = 808,
	EVREvent_Type_VREvent_Audio_Settings_Have_ಬದಲಾಯಿತು = 820,
	EVREvent_Type_VREvent_Background_Setting_Has_ಬದಲಾಯಿತು = 850,
	EVREvent_Type_VREvent_Camera_Settings_Have_ಬದಲಾಯಿತು = 851,
	EVREvent_Type_VREvent_Reprojection_Setting_Has_ಬದಲಾಯಿತು = 852,
	EVREvent_Type_VREvent_Model_Skin_Settings_Have_ಬದಲಾಯಿತು = 853,
	EVREvent_Type_VREvent_Environment_Settings_Have_ಬದಲಾಯಿತು = 854,
	EVREvent_Type_VREvent_Power_Settings_Have_ಬದಲಾಯಿತು = 855,
	EVREvent_Type_VREvent_Enable_Home_App_Settings_Have_ಬದಲಾಯಿತು = 856,
	EVREvent_Type_VREvent_Steam_VRSection_Setting_ಬದಲಾಯಿತು = 857,
	EVREvent_Type_VREvent_Lighthouse_Section_Setting_ಬದಲಾಯಿತು = 858,
	EVREvent_Type_VREvent_Null_Section_Setting_ಬದಲಾಯಿತು = 859,
	EVREvent_Type_VREvent_User_Interface_Section_Setting_ಬದಲಾಯಿತು = 860,
	EVREvent_Type_VREvent_Notifications_Section_Setting_ಬದಲಾಯಿತು = 861,
	EVREvent_Type_VREvent_Keyboard_Section_Setting_ಬದಲಾಯಿತು = 862,
	EVREvent_Type_VREvent_Perf_Section_Setting_ಬದಲಾಯಿತು = 863,
	EVREvent_Type_VREvent_Dashboard_Section_Setting_ಬದಲಾಯಿತು = 864,
	EVREvent_Type_VREvent_Web_Interface_Section_Setting_ಬದಲಾಯಿತು = 865,
	EVREvent_Type_VREvent_Trackers_Section_Setting_ಬದಲಾಯಿತು = 866,
	EVREvent_Type_VREvent_ಕೊನೆಯ_ತಿಳಿದ_Section_Setting_ಬದಲಾಯಿತು = 867,
	EVREvent_Type_VREvent_Dismissed_Warnings_Section_Setting_ಬದಲಾಯಿತು = 868,
	EVREvent_Type_VREvent_Gpu_ವೇಗ_Section_Setting_ಬದಲಾಯಿತು = 869,
	EVREvent_Type_VREvent_Windows_MRSection_Setting_ಬದಲಾಯಿತು = 870,
	EVREvent_Type_VREvent_Other_Section_Setting_ಬದಲಾಯಿತು = 871,
	EVREvent_Type_VREvent_ಸ್ಥಿತಿ_Update = 900,
	EVREventType_VREvent_WebInterface_InstallDriverCompleted = 950,
	EVREventType_VREvent_MCImageUpdated = 1000,
	EVREventType_VREvent_FirmwareUpdateStarted = 1100,
	EVREvent_Type_VREvent_Firmware_Update_ಪೂರ್ಣಗೊಂಡ = 1101,
	EVREventType_VREvent_KeyboardClosed = 1200,
	EVREvent_Type_VREvent_Keyboard_Char_ಒಳಹರಿವು = 1201,
	EVREvent_Type_VREvent_Keyboard_ಮುಗಿದ = 1202,
	EVREventType_VREvent_ApplicationListUpdated = 1303,
	EVREvent_Type_VREvent_Application_Mime_Type_ತುಂಬು = 1304,
	EVREventType_VREvent_ProcessConnected = 1306,
	EVREventType_VREvent_ProcessDisconnected = 1307,
	EVREventType_VREvent_Compositor_ChaperoneBoundsShown = 1410,
	EVREventType_VREvent_Compositor_ChaperoneBoundsHidden = 1411,
	EVREventType_VREvent_Compositor_DisplayDisconnected = 1412,
	EVREventType_VREvent_Compositor_DisplayReconnected = 1413,
	EVREventType_VREvent_Compositor_HDCPError = 1414,
	EVREventType_VREvent_Compositor_ApplicationNotResponding = 1415,
	EVREventType_VREvent_Compositor_ApplicationResumed = 1416,
	EVREvent_Type_VREvent_Compositor_ಹೊರಹೋಗು_ದ_Video_ಸ್ಮರಣೆ = 1417,
	EVREvent_Type_VREvent_Compositor_Display_ಬಹುಲಕ_Not_Supported = 1418,
	EVREventType_VREvent_Compositor_StageOverrideReady = 1419,
	EVREventType_VREvent_Compositor_RequestDisconnectReconnect = 1420,
	EVREvent_Type_VREvent_Tracked_Camera_ಆರಂಭ_Video_ಹರಿವು = 1500,
	EVREvent_Type_VREvent_Tracked_Camera_Stop_Video_ಹರಿವು = 1501,
	EVREvent_Type_VREvent_Tracked_Camera_Pause_Video_ಹರಿವು = 1502,
	EVREvent_Type_VREvent_Tracked_Camera_Resume_Video_ಹರಿವು = 1503,
	EVREventType_VREvent_TrackedCamera_EditingSurface = 1550,
	EVREventType_VREvent_PerformanceTest_EnableCapture = 1600,
	EVREventType_VREvent_PerformanceTest_DisableCapture = 1601,
	EVREventType_VREvent_PerformanceTest_FidelityLevel = 1602,
	EVREvent_Type_VREvent_ಸಂದೇಶ_Overlay_Closed = 1650,
	EVREvent_Type_VREvent_ಸಂದೇಶ_Overlay_Close_Requested = 1651,
	EVREvent_Type_VREvent_ಒಳಹರಿವು_Haptic_Vibration = 1700,
	EVREvent_Type_VREvent_ಒಳಹರಿವು_Binding_ತುಂಬು_Failed = 1701,
	EVREvent_Type_VREvent_ಒಳಹರಿವು_Binding_ತುಂಬು_Successful = 1702,
	EVREvent_Type_VREvent_ಒಳಹರಿವು_Action_Manifest_Reloaded = 1703,
	EVREvent_Type_VREvent_ಒಳಹರಿವು_Action_Manifest_ತುಂಬು_Failed = 1704,
	EVREvent_Type_VREvent_ಒಳಹರಿವು_ಪ್ರಗತಿ_Update = 1705,
	EVREvent_Type_VREvent_ಒಳಹರಿವು_Tracker_Activated = 1706,
	EVREvent_Type_VREvent_ಒಳಹರಿವು_Bindings_Updated = 1707,
	EVREvent_Type_VREvent_ಒಳಹರಿವು_Binding_Subscription_ಬದಲಾಯಿತು = 1708,
	EVREventType_VREvent_SpatialAnchors_PoseUpdated = 1800,
	EVREventType_VREvent_SpatialAnchors_DescriptorUpdated = 1801,
	EVREventType_VREvent_SpatialAnchors_RequestPoseUpdate = 1802,
	EVREventType_VREvent_SpatialAnchors_RequestDescriptorUpdate = 1803,
	EVREventType_VREvent_SystemReport_Started = 1900,
	EVREventType_VREvent_Monitor_ShowHeadsetView = 2000,
	EVREventType_VREvent_Monitor_HideHeadsetView = 2001,
	EVREvent_Type_VREvent_Vendor_Specific_Reserved_ಆರಂಭ = 10000,
	EVREvent_Type_VREvent_Vendor_Specific_Reserved_ಕೊನೆ = 19999,
} EVREventType;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ EDeviceActivityLevel
{
	EDeviceActivityLevel_k_EDeviceActivityLevel_Unknown = -1,
	EDeviceActivityLevel_k_EDeviceActivityLevel_Idle = 0,
	EDeviceActivityLevel_k_EDeviceActivityLevel_UserInteraction = 1,
	EDeviceActivityLevel_k_EDeviceActivityLevel_UserInteraction_Timeout = 2,
	EDeviceActivityLevel_k_EDeviceActivityLevel_Standby = 3,
	EDeviceActivityLevel_k_EDeviceActivityLevel_Idle_Timeout = 4,
} EDeviceActivityLevel;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ EVRButtonId
{
	EVRButtonId_k_EButton_System = 0,
	EVRButtonId_k_EButton_ApplicationMenu = 1,
	EVRButtonId_k_EButton_Grip = 2,
	EVRButton_Id_k_EButton_DPad_ಎಡ = 3,
	EVRButton_Id_k_EButton_DPad_ಮೇಲೆ = 4,
	EVRButton_Id_k_EButton_DPad_ಬಲ = 5,
	EVRButton_Id_k_EButton_DPad_ಕೆಳಕ್ಕೆ = 6,
	EVRButtonId_k_EButton_A = 7,
	EVRButtonId_k_EButton_ProximitySensor = 31,
	EVRButtonId_k_EButton_Axis0 = 32,
	EVRButtonId_k_EButton_Axis1 = 33,
	EVRButtonId_k_EButton_Axis2 = 34,
	EVRButtonId_k_EButton_Axis3 = 35,
	EVRButtonId_k_EButton_Axis4 = 36,
	EVRButtonId_k_EButton_SteamVR_Touchpad = 32,
	EVRButtonId_k_EButton_SteamVR_Trigger = 33,
	EVRButton_Id_k_EButton_Dashboard_ಹಿಂಭಾಗ = 2,
	EVRButton_Id_k_EButton_ಸೂಚ್ಯಂಕ_Controller_A = 2,
	EVRButton_Id_k_EButton_ಸೂಚ್ಯಂಕ_Controller_B = 1,
	EVRButton_Id_k_EButton_ಸೂಚ್ಯಂಕ_Controller_Joy_Stick = 35,
	EVRButtonId_k_EButton_Max = 64,
} EVRButtonId;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ EVRMouseButton
{
	EVRMouse_Button_VRMouse_Button_ಎಡ = 1,
	EVRMouse_Button_VRMouse_Button_ಬಲ = 2,
	EVRMouse_Button_VRMouse_Button_ಮಧ್ಯ = 4,
} EVRMouseButton;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ EShowUIType
{
	EShowUIType_ShowUI_ControllerBinding = 0,
	EShowUIType_ShowUI_ManageTrackers = 1,
	EShowUIType_ShowUI_Pairing = 3,
	EShowUIType_ShowUI_Settings = 4,
	EShowUIType_ShowUI_DebugCommands = 5,
	EShow_UIType_Show_UI_ತುಂಬಿದ_Controller_Binding = 6,
	EShowUIType_ShowUI_ManageDrivers = 7,
} EShowUIType;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ EHDCPError
{
	EHDCPError_HDCPError_None = 0,
	EHDCPError_HDCPError_Link_ಕಳೆದುಹೋದ = 1,
	EHDCPError_HDCPError_Tampered = 2,
	EHDCPError_HDCPError_DeviceRevoked = 3,
	EHDCPError_HDCPError_Unknown = 4,
} EHDCPError;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ EVRComponentProperty
{
	EVRComponentProperty_VRComponentProperty_IsStatic = 1,
	EVRComponentProperty_VRComponentProperty_IsVisible = 2,
	EVRComponentProperty_VRComponentProperty_IsTouched = 4,
	EVRComponentProperty_VRComponentProperty_IsPressed = 8,
	EVRComponentProperty_VRComponentProperty_IsScrolled = 16,
	EVRComponentProperty_VRComponentProperty_IsHighlighted = 32,
} EVRComponentProperty;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ EVRInputError
{
	EVRInputError_VRInputError_None = 0,
	EVRInput_Error_VRInput_Error_Name_Not_ಸಿಕ್ಕಿತು = 1,
	EVRInputError_VRInputError_WrongType = 2,
	EVRInputError_VRInputError_InvalidHandle = 3,
	EVRInputError_VRInputError_InvalidParam = 4,
	EVRInputError_VRInputError_NoSteam = 5,
	EVRInput_Error_VRInput_Error_Max_ಸಾಮರ್ಥ್ಯ_Reached = 6,
	EVRInputError_VRInputError_IPCError = 7,
	EVRInput_Error_VRInput_Error_No_ಸಕ್ರಿಯ_Action_ಗಣ = 8,
	EVRInputError_VRInputError_InvalidDevice = 9,
	EVRInputError_VRInputError_InvalidSkeleton = 10,
	EVRInput_Error_VRInput_Error_Invalid_Bone_ಎಣಿಕೆ = 11,
	EVRInput_Error_VRInput_Error_Invalid_Compressed_ದತ್ತಾಂಶ = 12,
	EVRInput_Error_VRInput_Error_No_ದತ್ತಾಂಶ = 13,
	EVRInput_Error_VRInput_Error_ಬಫರ್_Too_Small = 14,
	EVRInputError_VRInputError_MismatchedActionManifest = 15,
	EVRInput_Error_VRInput_Error_Missing_Skeleton_ದತ್ತಾಂಶ = 16,
	EVRInput_Error_VRInput_Error_Invalid_Bone_ಸೂಚ್ಯಂಕ = 17,
	EVRInput_Error_VRInput_Error_Invalid_ಆದ್ಯತೆ = 18,
	EVRInputError_VRInputError_PermissionDenied = 19,
	EVRInputError_VRInputError_InvalidRenderModel = 20,
} EVRInputError;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ EVRSpatialAnchorError
{
	EVRSpatialAnchorError_VRSpatialAnchorError_Success = 0,
	EVRSpatial_Anchor_Error_VRSpatial_Anchor_Error_ಆಂತರಿಕ = 1,
	EVRSpatialAnchorError_VRSpatialAnchorError_UnknownHandle = 2,
	EVRSpatialAnchorError_VRSpatialAnchorError_ArrayTooSmall = 3,
	EVRSpatialAnchorError_VRSpatialAnchorError_InvalidDescriptorChar = 4,
	EVRSpatial_Anchor_Error_VRSpatial_Anchor_Error_Not_Yet_ಲಭ್ಯ = 5,
	EVRSpatial_Anchor_Error_VRSpatial_Anchor_Error_Not_ಲಭ್ಯ_ಒಳ_This_Universe = 6,
	EVRSpatialAnchorError_VRSpatialAnchorError_PermanentlyUnavailable = 7,
	EVRSpatialAnchorError_VRSpatialAnchorError_WrongDriver = 8,
	EVRSpatialAnchorError_VRSpatialAnchorError_DescriptorTooLong = 9,
	EVRSpatialAnchorError_VRSpatialAnchorError_Unknown = 10,
	EVRSpatial_Anchor_Error_VRSpatial_Anchor_Error_No_ಸ್ಥಳ_Calibration = 11,
	EVRSpatial_Anchor_Error_VRSpatial_Anchor_Error_Invalid_ವಾದ = 12,
	EVRSpatialAnchorError_VRSpatialAnchorError_UnknownDriver = 13,
} EVRSpatialAnchorError;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ EHiddenAreaMeshType
{
	EHiddenAreaMeshType_k_eHiddenAreaMesh_Standard = 0,
	EHiddenAreaMeshType_k_eHiddenAreaMesh_Inverse = 1,
	EHidden_Area_Mesh_Type_k_e_Hidden_Area_Mesh_ಸಾಲು_Loop = 2,
	EHiddenAreaMeshType_k_eHiddenAreaMesh_Max = 3,
} EHiddenAreaMeshType;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ EVRControllerAxisType
{
	EVRControllerAxisType_k_eControllerAxis_None = 0,
	EVRControllerAxisType_k_eControllerAxis_TrackPad = 1,
	EVRControllerAxisType_k_eControllerAxis_Joystick = 2,
	EVRControllerAxisType_k_eControllerAxis_Trigger = 3,
} EVRControllerAxisType;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ EVRControllerEventOutputType
{
	EVRControllerEventOutputType_ControllerEventOutput_OSEvents = 0,
	EVRControllerEventOutputType_ControllerEventOutput_VREvents = 1,
} EVRControllerEventOutputType;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ ECollisionBoundsStyle
{
	ECollisionBoundsStyle_COLLISION_BOUNDS_STYLE_BEGINNER = 0,
	ECollisionBoundsStyle_COLLISION_BOUNDS_STYLE_INTERMEDIATE = 1,
	ECollisionBoundsStyle_COLLISION_BOUNDS_STYLE_SQUARES = 2,
	ECollisionBoundsStyle_COLLISION_BOUNDS_STYLE_ADVANCED = 3,
	ECollisionBoundsStyle_COLLISION_BOUNDS_STYLE_NONE = 4,
	ECollision_Bounds_Style_COLLISION_BOUNDS_STYLE_ಎಣಿಕೆ = 5,
} ECollisionBoundsStyle;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ EVROverlayError
{
	EVROverlayError_VROverlayError_None = 0,
	EVROverlayError_VROverlayError_UnknownOverlay = 10,
	EVROverlayError_VROverlayError_InvalidHandle = 11,
	EVROverlayError_VROverlayError_PermissionDenied = 12,
	EVROverlay_Error_VROverlay_Error_Overlay_ಎಲ್ಲೆ_Exceeded = 13,
	EVROverlayError_VROverlayError_WrongVisibilityType = 14,
	EVROverlay_Error_VROverlay_Error_ಕೀಲಿ_Too_Long = 15,
	EVROverlayError_VROverlayError_NameTooLong = 16,
	EVROverlay_Error_VROverlay_Error_ಕೀಲಿ_ಒಳ_Use = 17,
	EVROverlayError_VROverlayError_WrongTransformType = 18,
	EVROverlayError_VROverlayError_InvalidTrackedDevice = 19,
	EVROverlayError_VROverlayError_InvalidParameter = 20,
	EVROverlayError_VROverlayError_ThumbnailCantBeDestroyed = 21,
	EVROverlayError_VROverlayError_ArrayTooSmall = 22,
	EVROverlayError_VROverlayError_RequestFailed = 23,
	EVROverlayError_VROverlayError_InvalidTexture = 24,
	EVROverlay_Error_VROverlay_Error_Unable_ಗಮ್ಯ_ತುಂಬು_File = 25,
	EVROverlay_Error_VROverlay_Error_Keyboard_Already_ಒಳ_Use = 26,
	EVROverlayError_VROverlayError_NoNeighbor = 27,
	EVROverlay_Error_VROverlay_Error_Too_Many_ಮುಖವಾಡ_Primitives = 29,
	EVROverlay_Error_VROverlay_Error_Bad_ಮುಖವಾಡ_Primitive = 30,
	EVROverlayError_VROverlayError_TextureAlreadyLocked = 31,
	EVROverlay_Error_VROverlay_Error_Texture_ಬೀಗ_ಸಾಮರ್ಥ್ಯ_Reached = 32,
	EVROverlayError_VROverlayError_TextureNotLocked = 33,
	EVROverlay_Error_VROverlay_Error_Timed_ಹೊರಹೋಗು = 34,
} EVROverlayError;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ EVRApplicationType
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
	EVRApplication_Type_VRApplication_ಸ್ಥಳ_View = 13,
	EVRApplicationType_VRApplication_Max = 14,
} EVRApplicationType;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ EVRFirmwareError
{
	EVRFirmwareError_VRFirmwareError_None = 0,
	EVRFirmwareError_VRFirmwareError_Success = 1,
	EVRFirmwareError_VRFirmwareError_Fail = 2,
} EVRFirmwareError;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ EVRNotificationError
{
	EVRNotificationError_VRNotificationError_OK = 0,
	EVRNotificationError_VRNotificationError_InvalidNotificationId = 100,
	EVRNotification_Error_VRNotification_Error_Notification_ಸರತಿ_ತುಂಬಿದ = 101,
	EVRNotificationError_VRNotificationError_InvalidOverlayHandle = 102,
	EVRNotification_Error_VRNotification_Error_System_With_User_ಮೌಲ್ಯ_Already_Exists = 103,
} EVRNotificationError;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ EVRSkeletalMotionRange
{
	EVRSkeletalMotionRange_VRSkeletalMotionRange_WithController = 0,
	EVRSkeletalMotionRange_VRSkeletalMotionRange_WithoutController = 1,
} EVRSkeletalMotionRange;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ EVRSkeletalTrackingLevel
{
	EVRSkeletalTrackingLevel_VRSkeletalTracking_Estimated = 0,
	EVRSkeletalTrackingLevel_VRSkeletalTracking_Partial = 1,
	EVRSkeletal_Tracking_Level_VRSkeletal_Tracking_ತುಂಬಿದ = 2,
	EVRSkeletal_Tracking_Level_VRSkeletal_Tracking_Level_ಎಣಿಕೆ = 3,
	EVRSkeletalTrackingLevel_VRSkeletalTrackingLevel_Max = 2,
} EVRSkeletalTrackingLevel;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ EVRInitError
{
	EVRInitError_VRInitError_None = 0,
	EVRInitError_VRInitError_Unknown = 1,
	EVRInit_Error_VRInit_Error_Init_Installation_Not_ಸಿಕ್ಕಿತು = 100,
	EVRInitError_VRInitError_Init_InstallationCorrupt = 101,
	EVRInit_Error_VRInit_Error_Init_VRClient_DLLNot_ಸಿಕ್ಕಿತು = 102,
	EVRInit_Error_VRInit_Error_Init_File_Not_ಸಿಕ್ಕಿತು = 103,
	EVRInit_Error_VRInit_Error_Init_Factory_Not_ಸಿಕ್ಕಿತು = 104,
	EVRInit_Error_VRInit_Error_Init_Interface_Not_ಸಿಕ್ಕಿತು = 105,
	EVRInitError_VRInitError_Init_InvalidInterface = 106,
	EVRInitError_VRInitError_Init_UserConfigDirectoryInvalid = 107,
	EVRInit_Error_VRInit_Error_Init_Hmd_Not_ಸಿಕ್ಕಿತು = 108,
	EVRInitError_VRInitError_Init_NotInitialized = 109,
	EVRInit_Error_VRInit_Error_Init_ಮಾರ್ಗ_Registry_Not_ಸಿಕ್ಕಿತು = 110,
	EVRInit_Error_VRInit_Error_Init_No_Config_ಮಾರ್ಗ = 111,
	EVRInit_Error_VRInit_Error_Init_No_Log_ಮಾರ್ಗ = 112,
	EVRInit_Error_VRInit_Error_Init_ಮಾರ್ಗ_Registry_Not_Writable = 113,
	EVRInitError_VRInitError_Init_AppInfoInitFailed = 114,
	EVRInitError_VRInitError_Init_Retry = 115,
	EVRInitError_VRInitError_Init_InitCanceledByUser = 116,
	EVRInitError_VRInitError_Init_AnotherAppLaunching = 117,
	EVRInitError_VRInitError_Init_SettingsInitFailed = 118,
	EVRInit_Error_VRInit_Error_Init_Shutting_ಕೆಳಕ್ಕೆ = 119,
	EVRInitError_VRInitError_Init_TooManyObjects = 120,
	EVRInitError_VRInitError_Init_NoServerForBackgroundApp = 121,
	EVRInitError_VRInitError_Init_NotSupportedWithCompositor = 122,
	EVRInit_Error_VRInit_Error_Init_Not_ಲಭ್ಯ_ಗಮ್ಯ_Utility_Apps = 123,
	EVRInit_Error_VRInit_Error_Init_ಆಂತರಿಕ = 124,
	EVRInitError_VRInitError_Init_HmdDriverIdIsNone = 125,
	EVRInit_Error_VRInit_Error_Init_Hmd_Not_ಸಿಕ್ಕಿತು_Presence_Failed = 126,
	EVRInit_Error_VRInit_Error_Init_VRMonitor_Not_ಸಿಕ್ಕಿತು = 127,
	EVRInitError_VRInitError_Init_VRMonitorStartupFailed = 128,
	EVRInit_Error_VRInit_Error_Init_ಕೆಳಗಿನ_Power_Watchdog_Not_Supported = 129,
	EVRInitError_VRInitError_Init_InvalidApplicationType = 130,
	EVRInit_Error_VRInit_Error_Init_Not_ಲಭ್ಯ_ಗಮ್ಯ_Watchdog_Apps = 131,
	EVRInit_Error_VRInit_Error_Init_Watchdog_Disabled_ಒಳ_Settings = 132,
	EVRInit_Error_VRInit_Error_Init_VRDashboard_Not_ಸಿಕ್ಕಿತು = 133,
	EVRInitError_VRInitError_Init_VRDashboardStartupFailed = 134,
	EVRInit_Error_VRInit_Error_Init_VRHome_Not_ಸಿಕ್ಕಿತು = 135,
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
	EVRInit_Error_VRInit_Error_Init_Prism_Startup_Timed_ಹೊರಹೋಗು = 152,
	EVRInit_Error_VRInit_Error_Init_Could_Not_ಆರಂಭ_Prism = 153,
	EVRInitError_VRInitError_Init_PrismClientInitFailed = 154,
	EVRInit_Error_VRInit_Error_Init_Prism_Client_ಆರಂಭ_Failed = 155,
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
	EVRInit_Error_VRInit_Error_Init_VRDashboard_ಮಾರ್ಗ_Failure = 167,
	EVRInitError_VRInitError_Driver_Failed = 200,
	EVRInitError_VRInitError_Driver_Unknown = 201,
	EVRInitError_VRInitError_Driver_HmdUnknown = 202,
	EVRInitError_VRInitError_Driver_NotLoaded = 203,
	EVRInit_Error_VRInit_Error_Driver_Runtime_ಹೊರಹೋಗು_ದ_Date = 204,
	EVRInit_Error_VRInit_Error_Driver_Hmd_ಒಳ_Use = 205,
	EVRInitError_VRInitError_Driver_NotCalibrated = 206,
	EVRInitError_VRInitError_Driver_CalibrationInvalid = 207,
	EVRInit_Error_VRInit_Error_Driver_Hmd_Display_Not_ಸಿಕ್ಕಿತು = 208,
	EVRInitError_VRInitError_Driver_TrackedDeviceInterfaceUnknown = 209,
	EVRInit_Error_VRInit_Error_Driver_Hmd_Driver_Id_ಹೊರಹೋಗು_ದ_Bounds = 211,
	EVRInitError_VRInitError_Driver_HmdDisplayMirrored = 212,
	EVRInit_Error_VRInit_Error_Driver_Hmd_Display_Not_ಸಿಕ್ಕಿತು_Laptop = 213,
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
	EVRInit_Error_VRInit_Error_IPC_Connect_Failed_After_ಅಪವರ್ತ್ಯ_Attempts = 308,
	EVRInit_Error_VRInit_Error_IPC_Connect_Failed_After_ಗುರಿ_Exited = 309,
	EVRInitError_VRInitError_IPC_NamespaceUnavailable = 310,
	EVRInitError_VRInitError_Compositor_Failed = 400,
	EVRInitError_VRInitError_Compositor_D3D11HardwareRequired = 401,
	EVRInitError_VRInitError_Compositor_FirmwareRequiresUpdate = 402,
	EVRInitError_VRInitError_Compositor_OverlayInitFailed = 403,
	EVRInitError_VRInitError_Compositor_ScreenshotsInitFailed = 404,
	EVRInit_Error_VRInit_Error_Compositor_Unable_ಗಮ್ಯ_Create_Device = 405,
	EVRInitError_VRInitError_Compositor_SharedStateIsNull = 406,
	EVRInitError_VRInitError_Compositor_NotificationManagerIsNull = 407,
	EVRInitError_VRInitError_Compositor_ResourceManagerClientIsNull = 408,
	EVRInit_Error_VRInit_Error_Compositor_ಸಂದೇಶ_Overlay_Shared_State_Init_Failure = 409,
	EVRInitError_VRInitError_Compositor_PropertiesInterfaceIsNull = 410,
	EVRInit_Error_VRInit_Error_Compositor_Create_Fullscreen_ಕಿಟಕಿ_Failed = 411,
	EVRInitError_VRInitError_Compositor_SettingsInterfaceIsNull = 412,
	EVRInit_Error_VRInit_Error_Compositor_Failed_ಗಮ್ಯ_Show_ಕಿಟಕಿ = 413,
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
	EVRInit_Error_VRInit_Error_Compositor_Failed_ಗಮ್ಯ_ಕಂಡುಹಿಡಿ_Display_ಬಹುಲಕ = 425,
	EVRInit_Error_VRInit_Error_Compositor_Failed_ಗಮ್ಯ_Create_ಅದಲುಬದಲು_Chain = 426,
	EVRInit_Error_VRInit_Error_Compositor_Failed_ಗಮ್ಯ_Get_ಹಿಂಭಾಗ_ಬಫರ್ = 427,
	EVRInit_Error_VRInit_Error_Compositor_Failed_ಗಮ್ಯ_Create_Render_ಗುರಿ = 428,
	EVRInit_Error_VRInit_Error_Compositor_Failed_ಗಮ್ಯ_Create_DXGI2_ಅದಲುಬದಲು_Chain = 429,
	EVRInit_Error_VRInit_Error_Compositor_Failedto_Get_DXGI2_ಹಿಂಭಾಗ_ಬಫರ್ = 430,
	EVRInit_Error_VRInit_Error_Compositor_Failed_ಗಮ್ಯ_Create_DXGI2_Render_ಗುರಿ = 431,
	EVRInit_Error_VRInit_Error_Compositor_Failed_ಗಮ್ಯ_Get_DXGIDevice_Interface = 432,
	EVRInit_Error_VRInit_Error_Compositor_Select_Display_ಬಹುಲಕ = 433,
	EVRInit_Error_VRInit_Error_Compositor_Failed_ಗಮ್ಯ_Create_Nv_APIRender_Targets = 434,
	EVRInit_Error_VRInit_Error_Compositor_Nv_APISet_Display_ಬಹುಲಕ = 435,
	EVRInit_Error_VRInit_Error_Compositor_Failed_ಗಮ್ಯ_Create_ನೇರ_ಬಹುಲಕ_Display = 436,
	EVRInitError_VRInitError_Compositor_InvalidHmdPropertyContainer = 437,
	EVRInitError_VRInitError_Compositor_UpdateDisplayFrequency = 438,
	EVRInitError_VRInitError_Compositor_CreateRasterizerState = 439,
	EVRInitError_VRInitError_Compositor_CreateWireframeRasterizerState = 440,
	EVRInitError_VRInitError_Compositor_CreateSamplerState = 441,
	EVRInit_Error_VRInit_Error_Compositor_Create_Clamp_ಗಮ್ಯ_Border_Sampler_State = 442,
	EVRInitError_VRInitError_Compositor_CreateAnisoSamplerState = 443,
	EVRInitError_VRInitError_Compositor_CreateOverlaySamplerState = 444,
	EVRInitError_VRInitError_Compositor_CreatePanoramaSamplerState = 445,
	EVRInitError_VRInitError_Compositor_CreateFontSamplerState = 446,
	EVRInitError_VRInitError_Compositor_CreateNoBlendState = 447,
	EVRInitError_VRInitError_Compositor_CreateBlendState = 448,
	EVRInitError_VRInitError_Compositor_CreateAlphaBlendState = 449,
	EVRInit_Error_VRInit_Error_Compositor_Create_Blend_State_ಮುಖವಾಡ_R = 450,
	EVRInit_Error_VRInit_Error_Compositor_Create_Blend_State_ಮುಖವಾಡ_G = 451,
	EVRInit_Error_VRInit_Error_Compositor_Create_Blend_State_ಮುಖವಾಡ_B = 452,
	EVRInit_Error_VRInit_Error_Compositor_Create_ಆಳ_Stencil_State = 453,
	EVRInit_Error_VRInit_Error_Compositor_Create_ಆಳ_Stencil_State_No_Write = 454,
	EVRInit_Error_VRInit_Error_Compositor_Create_ಆಳ_Stencil_State_No_ಆಳ = 455,
	EVRInitError_VRInitError_Compositor_CreateFlushTexture = 456,
	EVRInitError_VRInitError_Compositor_CreateDistortionSurfaces = 457,
	EVRInit_Error_VRInit_Error_Compositor_Create_Constant_ಬಫರ್ = 458,
	EVRInit_Error_VRInit_Error_Compositor_Create_Hmd_Pose_Constant_ಬಫರ್ = 459,
	EVRInit_Error_VRInit_Error_Compositor_Create_Hmd_Pose_Staging_Constant_ಬಫರ್ = 460,
	EVRInit_Error_VRInit_Error_Compositor_Create_Shared_ಚೌಕಟ್ಟು_Info_Constant_ಬಫರ್ = 461,
	EVRInit_Error_VRInit_Error_Compositor_Create_Overlay_Constant_ಬಫರ್ = 462,
	EVRInit_Error_VRInit_Error_Compositor_Create_Scene_Texture_ಸೂಚ್ಯಂಕ_Constant_ಬಫರ್ = 463,
	EVRInit_Error_VRInit_Error_Compositor_Create_Readable_Scene_Texture_ಸೂಚ್ಯಂಕ_Constant_ಬಫರ್ = 464,
	EVRInit_Error_VRInit_Error_Compositor_Create_Layer_Graphics_Texture_ಸೂಚ್ಯಂಕ_Constant_ಬಫರ್ = 465,
	EVRInit_Error_VRInit_Error_Compositor_Create_Layer_Compute_Texture_ಸೂಚ್ಯಂಕ_Constant_ಬಫರ್ = 466,
	EVRInit_Error_VRInit_Error_Compositor_Create_Layer_Compute_Scene_Texture_ಸೂಚ್ಯಂಕ_Constant_ಬಫರ್ = 467,
	EVRInit_Error_VRInit_Error_Compositor_Create_Compute_Hmd_Pose_Constant_ಬಫರ್ = 468,
	EVRInit_Error_VRInit_Error_Compositor_Create_Geom_Constant_ಬಫರ್ = 469,
	EVRInit_Error_VRInit_Error_Compositor_Create_Panel_ಮುಖವಾಡ_Constant_ಬಫರ್ = 470,
	EVRInitError_VRInitError_Compositor_CreatePixelSimUBO = 471,
	EVRInitError_VRInitError_Compositor_CreateMSAARenderTextures = 472,
	EVRInitError_VRInitError_Compositor_CreateResolveRenderTextures = 473,
	EVRInitError_VRInitError_Compositor_CreateComputeResolveRenderTextures = 474,
	EVRInit_Error_VRInit_Error_Compositor_Create_Driver_ನೇರ_ಬಹುಲಕ_Resolve_Textures = 475,
	EVRInit_Error_VRInit_Error_Compositor_Open_Driver_ನೇರ_ಬಹುಲಕ_Resolve_Textures = 476,
	EVRInitError_VRInitError_Compositor_CreateFallbackSyncTexture = 477,
	EVRInitError_VRInitError_Compositor_ShareFallbackSyncTexture = 478,
	EVRInit_Error_VRInit_Error_Compositor_Create_Overlay_ಸೂಚ್ಯಂಕ_ಬಫರ್ = 479,
	EVRInit_Error_VRInit_Error_Compositor_Create_Overlay_ಶೃಂಗ_ಬಫರ್ = 480,
	EVRInit_Error_VRInit_Error_Compositor_Create_ಪಠ್ಯ_ಶೃಂಗ_ಬಫರ್ = 481,
	EVRInit_Error_VRInit_Error_Compositor_Create_ಪಠ್ಯ_ಸೂಚ್ಯಂಕ_ಬಫರ್ = 482,
	EVRInitError_VRInitError_Compositor_CreateMirrorTextures = 483,
	EVRInit_Error_VRInit_Error_Compositor_Create_ಕೊನೆಯ_ಚೌಕಟ್ಟು_Render_Texture = 484,
	EVRInitError_VRInitError_Compositor_CreateMirrorOverlay = 485,
	EVRInit_Error_VRInit_Error_Compositor_Failed_ಗಮ್ಯ_Create_Virtual_Display_Backbuffer = 486,
	EVRInit_Error_VRInit_Error_Compositor_Display_ಬಹುಲಕ_Not_Supported = 487,
	EVRInitError_VRInitError_Compositor_CreateOverlayInvalidCall = 488,
	EVRInitError_VRInitError_Compositor_CreateOverlayAlreadyInitialized = 489,
	EVRInit_Error_VRInit_Error_Compositor_Failed_ಗಮ್ಯ_Create_Mailbox = 490,
	EVRInit_Error_VRInit_Error_Compositor_ಕಿಟಕಿ_Interface_Is_Null = 491,
	EVRInitError_VRInitError_Compositor_SystemLayerCreateInstance = 492,
	EVRInitError_VRInitError_Compositor_SystemLayerCreateSession = 493,
	EVRInitError_VRInitError_Compoistor_CreateInverseDistortUVs = 494,
	EVRInit_Error_VRInit_Error_Compoistor_Create_Backbuffer_ಆಳ = 495,
	EVRInit_Error_VRInit_Error_Vendor_Specific_Unable_ಗಮ್ಯ_Connect_ಗಮ್ಯ_Oculus_Runtime = 1000,
	EVRInit_Error_VRInit_Error_Vendor_Specific_Windows_Not_ಒಳ_Dev_ಬಹುಲಕ = 1001,
	EVRInitError_VRInitError_VendorSpecific_OculusLinkNotEnabled = 1002,
	EVRInit_Error_VRInit_Error_Vendor_Specific_Hmd_ಸಿಕ್ಕಿತು_Cant_Open_Device = 1101,
	EVRInit_Error_VRInit_Error_Vendor_Specific_Hmd_ಸಿಕ್ಕಿತು_Unable_ಗಮ್ಯ_Request_Config_ಆರಂಭ = 1102,
	EVRInit_Error_VRInit_Error_Vendor_Specific_Hmd_ಸಿಕ್ಕಿತು_No_Stored_Config = 1103,
	EVRInit_Error_VRInit_Error_Vendor_Specific_Hmd_ಸಿಕ್ಕಿತು_Config_Too_Big = 1104,
	EVRInit_Error_VRInit_Error_Vendor_Specific_Hmd_ಸಿಕ್ಕಿತು_Config_Too_Small = 1105,
	EVRInit_Error_VRInit_Error_Vendor_Specific_Hmd_ಸಿಕ್ಕಿತು_Unable_ಗಮ್ಯ_Init_ZLib = 1106,
	EVRInit_Error_VRInit_Error_Vendor_Specific_Hmd_ಸಿಕ್ಕಿತು_Cant_Read_Firmware_ಆವೃತ್ತಿ = 1107,
	EVRInit_Error_VRInit_Error_Vendor_Specific_Hmd_ಸಿಕ್ಕಿತು_Unable_ಗಮ್ಯ_Send_User_ದತ್ತಾಂಶ_ಆರಂಭ = 1108,
	EVRInit_Error_VRInit_Error_Vendor_Specific_Hmd_ಸಿಕ್ಕಿತು_Unable_ಗಮ್ಯ_Get_User_ದತ್ತಾಂಶ_ಆರಂಭ = 1109,
	EVRInit_Error_VRInit_Error_Vendor_Specific_Hmd_ಸಿಕ್ಕಿತು_Unable_ಗಮ್ಯ_Get_User_ದತ್ತಾಂಶ_ಮುಂದಿನ = 1110,
	EVRInit_Error_VRInit_Error_Vendor_Specific_Hmd_ಸಿಕ್ಕಿತು_User_ದತ್ತಾಂಶ_ವಿಳಾಸ_Range = 1111,
	EVRInit_Error_VRInit_Error_Vendor_Specific_Hmd_ಸಿಕ್ಕಿತು_User_ದತ್ತಾಂಶ_Error = 1112,
	EVRInit_Error_VRInit_Error_Vendor_Specific_Hmd_ಸಿಕ್ಕಿತು_Config_Failed_Sanity_Check = 1113,
	EVRInitError_VRInitError_VendorSpecific_OculusRuntimeBadInstall = 1114,
	EVRInit_Error_VRInit_Error_Vendor_Specific_Hmd_ಸಿಕ್ಕಿತು_Unexpected_Configuration_1 = 1115,
	EVRInit_Error_VRInit_Error_Steam_Steam_Installation_Not_ಸಿಕ್ಕಿತು = 2000,
	EVRInit_Error_VRInit_Error_ಕೊನೆಯ_Error = 2001,
} EVRInitError;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ EVRScreenshotType
{
	EVRScreenshotType_VRScreenshotType_None = 0,
	EVRScreenshotType_VRScreenshotType_Mono = 1,
	EVRScreenshotType_VRScreenshotType_Stereo = 2,
	EVRScreenshotType_VRScreenshotType_Cubemap = 3,
	EVRScreenshotType_VRScreenshotType_MonoPanorama = 4,
	EVRScreenshotType_VRScreenshotType_StereoPanorama = 5,
} EVRScreenshotType;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ EVRScreenshotPropertyFilenames
{
	EVRScreenshotPropertyFilenames_VRScreenshotPropertyFilenames_Preview = 0,
	EVRScreenshotPropertyFilenames_VRScreenshotPropertyFilenames_VR = 1,
} EVRScreenshotPropertyFilenames;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ EVRTrackedCameraError
{
	EVRTrackedCameraError_VRTrackedCameraError_None = 0,
	EVRTrackedCameraError_VRTrackedCameraError_OperationFailed = 100,
	EVRTrackedCameraError_VRTrackedCameraError_InvalidHandle = 101,
	EVRTracked_Camera_Error_VRTracked_Camera_Error_Invalid_ಚೌಕಟ್ಟು_ಶೀರ್ಷಿಕೆ_ಆವೃತ್ತಿ = 102,
	EVRTracked_Camera_Error_VRTracked_Camera_Error_ಹೊರಹೋಗು_ದ_Handles = 103,
	EVRTrackedCameraError_VRTrackedCameraError_IPCFailure = 104,
	EVRTrackedCameraError_VRTrackedCameraError_NotSupportedForThisDevice = 105,
	EVRTracked_Camera_Error_VRTracked_Camera_Error_Shared_ಸ್ಮರಣೆ_Failure = 106,
	EVRTracked_Camera_Error_VRTracked_Camera_Error_ಚೌಕಟ್ಟು_Buffering_Failure = 107,
	EVRTracked_Camera_Error_VRTracked_Camera_Error_ಹರಿವು_ಸಿದ್ಧತೆ_Failure = 108,
	EVRTrackedCameraError_VRTrackedCameraError_InvalidGLTextureId = 109,
	EVRTrackedCameraError_VRTrackedCameraError_InvalidSharedTextureHandle = 110,
	EVRTracked_Camera_Error_VRTracked_Camera_Error_Failed_ಗಮ್ಯ_Get_GLTexture_Id = 111,
	EVRTrackedCameraError_VRTrackedCameraError_SharedTextureFailure = 112,
	EVRTracked_Camera_Error_VRTracked_Camera_Error_No_ಚೌಕಟ್ಟು_ಲಭ್ಯ = 113,
	EVRTracked_Camera_Error_VRTracked_Camera_Error_Invalid_ವಾದ = 114,
	EVRTracked_Camera_Error_VRTracked_Camera_Error_Invalid_ಚೌಕಟ್ಟು_ಬಫರ್_ಗಾತ್ರ = 115,
} EVRTrackedCameraError;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ EVRTracked_Camera_ಚೌಕಟ್ಟು_Layout
{
	EVRTracked_Camera_ಚೌಕಟ್ಟು_Layout_Mono = 1,
	EVRTracked_Camera_ಚೌಕಟ್ಟು_Layout_Stereo = 2,
	EVRTracked_Camera_ಚೌಕಟ್ಟು_Layout_Vertical_Layout = 16,
	EVRTracked_Camera_ಚೌಕಟ್ಟು_Layout_Horizontal_Layout = 32,
} EVRTracked_Camera_ಚೌಕಟ್ಟು_Layout;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ EVRTracked_Camera_ಚೌಕಟ್ಟು_Type
{
	EVRTracked_Camera_ಚೌಕಟ್ಟು_Type_VRTracked_Camera_ಚೌಕಟ್ಟು_Type_Distorted = 0,
	EVRTracked_Camera_ಚೌಕಟ್ಟು_Type_VRTracked_Camera_ಚೌಕಟ್ಟು_Type_Undistorted = 1,
	EVRTracked_Camera_ಚೌಕಟ್ಟು_Type_VRTracked_Camera_ಚೌಕಟ್ಟು_Type_ಗರಿಷ್ಠ_Undistorted = 2,
	EVRTracked_Camera_ಚೌಕಟ್ಟು_Type_MAX_CAMERA_ಚೌಕಟ್ಟು_TYPES = 3,
} EVRTracked_Camera_ಚೌಕಟ್ಟು_Type;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ EVRDistortionFunctionType
{
	EVRDistortionFunctionType_VRDistortionFunctionType_None = 0,
	EVRDistortionFunctionType_VRDistortionFunctionType_FTheta = 1,
	EVRDistortionFunctionType_VRDistortionFunctionType_Extended_FTheta = 2,
	EVRDistortionFunctionType_MAX_DISTORTION_FUNCTION_TYPES = 3,
} EVRDistortionFunctionType;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ EVSync
{
	EVSync_VSync_None = 0,
	EVSync_VSync_WaitRender = 1,
	EVSync_VSync_NoWaitRender = 2,
} EVSync;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ EVRMura_Correction_ಬಹುಲಕ
{
	EVRMura_Correction_ಬಹುಲಕ_Default = 0,
	EVRMura_Correction_ಬಹುಲಕ_No_Correction = 1,
} EVRMura_Correction_ಬಹುಲಕ;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ Imu_OffScaleFlags
{
	Imu_OffScaleFlags_OffScale_AccelX = 1,
	Imu_OffScaleFlags_OffScale_AccelY = 2,
	Imu_OffScaleFlags_OffScale_AccelZ = 4,
	Imu_OffScaleFlags_OffScale_GyroX = 8,
	Imu_OffScaleFlags_OffScale_GyroY = 16,
	Imu_OffScaleFlags_OffScale_GyroZ = 32,
} Imu_OffScaleFlags;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ EVRApplicationError
{
	EVRApplicationError_VRApplicationError_None = 0,
	EVRApplication_Error_VRApplication_Error_App_ಕೀಲಿ_Already_Exists = 100,
	EVRApplicationError_VRApplicationError_NoManifest = 101,
	EVRApplicationError_VRApplicationError_NoApplication = 102,
	EVRApplication_Error_VRApplication_Error_Invalid_ಸೂಚ್ಯಂಕ = 103,
	EVRApplicationError_VRApplicationError_UnknownApplication = 104,
	EVRApplicationError_VRApplicationError_IPCFailed = 105,
	EVRApplicationError_VRApplicationError_ApplicationAlreadyRunning = 106,
	EVRApplicationError_VRApplicationError_InvalidManifest = 107,
	EVRApplicationError_VRApplicationError_InvalidApplication = 108,
	EVRApplicationError_VRApplicationError_LaunchFailed = 109,
	EVRApplicationError_VRApplicationError_ApplicationAlreadyStarting = 110,
	EVRApplication_Error_VRApplication_Error_Launch_ಒಳ_ಪ್ರಗತಿ = 111,
	EVRApplicationError_VRApplicationError_OldApplicationQuitting = 112,
	EVRApplicationError_VRApplicationError_TransitionAborted = 113,
	EVRApplicationError_VRApplicationError_IsTemplate = 114,
	EVRApplicationError_VRApplicationError_SteamVRIsExiting = 115,
	EVRApplication_Error_VRApplication_Error_ಬಫರ್_Too_Small = 200,
	EVRApplication_Error_VRApplication_Error_Property_Not_ಗಣ = 201,
	EVRApplicationError_VRApplicationError_UnknownProperty = 202,
	EVRApplicationError_VRApplicationError_InvalidParameter = 203,
	EVRApplicationError_VRApplicationError_NotImplemented = 300,
} EVRApplicationError;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ EVRApplicationProperty
{
	EVRApplicationProperty_VRApplicationProperty_Name_String = 0,
	EVRApplicationProperty_VRApplicationProperty_LaunchType_String = 11,
	EVRApplicationProperty_VRApplicationProperty_WorkingDirectory_String = 12,
	EVRApplication_Property_VRApplication_Property_ದ್ವಿಮಾನ_ಮಾರ್ಗ_String = 13,
	EVRApplicationProperty_VRApplicationProperty_Arguments_String = 14,
	EVRApplicationProperty_VRApplicationProperty_URL_String = 15,
	EVRApplicationProperty_VRApplicationProperty_Description_String = 50,
	EVRApplicationProperty_VRApplicationProperty_NewsURL_String = 51,
	EVRApplication_Property_VRApplication_Property_Image_ಮಾರ್ಗ_String = 52,
	EVRApplication_Property_VRApplication_Property_ಮೂಲ_String = 53,
	EVRApplicationProperty_VRApplicationProperty_ActionManifestURL_String = 54,
	EVRApplicationProperty_VRApplicationProperty_IsDashboardOverlay_Bool = 60,
	EVRApplicationProperty_VRApplicationProperty_IsTemplate_Bool = 61,
	EVRApplicationProperty_VRApplicationProperty_IsInstanced_Bool = 62,
	EVRApplication_Property_VRApplication_Property_Is_ಆಂತರಿಕ_Bool = 63,
	EVRApplication_Property_VRApplication_Property_ಬಯಸುತ್ತದೆ_Compositor_Pause_ಒಳ_Standby_Bool = 64,
	EVRApplicationProperty_VRApplicationProperty_IsHidden_Bool = 65,
	EVRApplication_Property_VRApplication_Property_ಕೊನೆಯ_Launch_ಸಮಯ_Uint64 = 70,
} EVRApplicationProperty;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ EVRSceneApplicationState
{
	EVRSceneApplicationState_None = 0,
	EVRSceneApplicationState_Starting = 1,
	EVRSceneApplicationState_Quitting = 2,
	EVRSceneApplicationState_Running = 3,
	EVRScene_Application_State_ಕಾಯುವಿಕೆ = 4,
} EVRSceneApplicationState;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ ChaperoneCalibrationState
{
	ChaperoneCalibrationState_OK = 1,
	ChaperoneCalibrationState_Warning = 100,
	Chaperone_Calibration_State_Warning_ತಳ_Station_May_Have_Moved = 101,
	Chaperone_Calibration_State_Warning_ತಳ_Station_Removed = 102,
	ChaperoneCalibrationState_Warning_SeatedBoundsInvalid = 103,
	ChaperoneCalibrationState_Error = 200,
	Chaperone_Calibration_State_Error_ತಳ_Station_Uninitialized = 201,
	Chaperone_Calibration_State_Error_ತಳ_Station_Conflict = 202,
	ChaperoneCalibrationState_Error_PlayAreaInvalid = 203,
	ChaperoneCalibrationState_Error_CollisionBoundsInvalid = 204,
} ChaperoneCalibrationState;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ EChaperoneConfigFile
{
	EChaperone_Config_File_ಜೀವಂತ = 1,
	EChaperone_Config_File_ತಾತ್ಕಾಲಿಕ = 2,
} EChaperoneConfigFile;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ EChaperoneImportFlags
{
	EChaperoneImportFlags_EChaperoneImport_BoundsOnly = 1,
} EChaperoneImportFlags;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ EVRCompositorError
{
	EVRCompositorError_VRCompositorError_None = 0,
	EVRCompositorError_VRCompositorError_RequestFailed = 1,
	EVRCompositor_Error_VRCompositor_Error_Incompatible_ಆವೃತ್ತಿ = 100,
	EVRCompositorError_VRCompositorError_DoNotHaveFocus = 101,
	EVRCompositorError_VRCompositorError_InvalidTexture = 102,
	EVRCompositorError_VRCompositorError_IsNotSceneApplication = 103,
	EVRCompositorError_VRCompositorError_TextureIsOnWrongDevice = 104,
	EVRCompositor_Error_VRCompositor_Error_Texture_ಬಳಸುತ್ತದೆ_Unsupported_Format = 105,
	EVRCompositorError_VRCompositorError_SharedTexturesNotSupported = 106,
	EVRCompositor_Error_VRCompositor_Error_ಸೂಚ್ಯಂಕ_ಹೊರಹೋಗು_ದ_Range = 107,
	EVRCompositorError_VRCompositorError_AlreadySubmitted = 108,
	EVRCompositorError_VRCompositorError_InvalidBounds = 109,
	EVRCompositor_Error_VRCompositor_Error_Already_ಗಣ = 110,
} EVRCompositorError;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ EVRCompositor_Timing_ಬಹುಲಕ
{
	EVRCompositor_Timing_ಬಹುಲಕ_VRCompositor_Timing_ಬಹುಲಕ_Implicit = 0,
	EVRCompositor_Timing_ಬಹುಲಕ_VRCompositor_Timing_ಬಹುಲಕ_Explicit_Runtime_Performs_Post_Present_Handoff = 1,
	EVRCompositor_Timing_ಬಹುಲಕ_VRCompositor_Timing_ಬಹುಲಕ_Explicit_Application_Performs_Post_Present_Handoff = 2,
} EVRCompositor_Timing_ಬಹುಲಕ;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ VROverlay_ಒಳಹರಿವು_ವಿಧಾನ
{
	VROverlay_ಒಳಹರಿವು_ವಿಧಾನ_None = 0,
	VROverlay_ಒಳಹರಿವು_ವಿಧಾನ_Mouse = 1,
} VROverlay_ಒಳಹರಿವು_ವಿಧಾನ;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ VROverlayTransformType
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

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ VROverlayFlags
{
	VROverlayFlags_NoDashboardTab = 8,
	VROverlayFlags_SendVRDiscreteScrollEvents = 64,
	VROverlayFlags_SendVRTouchpadEvents = 128,
	VROverlayFlags_ShowTouchPadScrollWheel = 256,
	VROverlay_Flags_Transfer_Ownership_ಗಮ್ಯ_ಆಂತರಿಕ_Process = 512,
	VROverlayFlags_SideBySide_Parallel = 1024,
	VROverlayFlags_SideBySide_Crossed = 2048,
	VROverlayFlags_Panorama = 4096,
	VROverlayFlags_StereoPanorama = 8192,
	VROverlay_Flags_ವಿಂಗಡಿಸು_With_Non_Scene_Overlays = 16384,
	VROverlay_Flags_Visible_ಒಳ_Dashboard = 32768,
	VROverlayFlags_MakeOverlaysInteractiveIfVisible = 65536,
	VROverlayFlags_SendVRSmoothScrollEvents = 131072,
	VROverlayFlags_ProtectedContent = 262144,
	VROverlayFlags_HideLaserIntersection = 524288,
	VROverlay_Flags_ಬಯಸುತ್ತದೆ_Modal_Behavior = 1048576,
	VROverlayFlags_IsPremultiplied = 2097152,
	VROverlayFlags_IgnoreTextureAlpha = 4194304,
	VROverlayFlags_EnableControlBar = 8388608,
	VROverlayFlags_EnableControlBarKeyboard = 16777216,
	VROverlayFlags_EnableControlBarClose = 33554432,
} VROverlayFlags;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ VRMessageOverlayResponse
{
	VRMessageOverlayResponse_ButtonPress_0 = 0,
	VRMessageOverlayResponse_ButtonPress_1 = 1,
	VRMessageOverlayResponse_ButtonPress_2 = 2,
	VRMessageOverlayResponse_ButtonPress_3 = 3,
	VRMessage_Overlay_Response_Couldnt_ಕಂಡುಹಿಡಿ_System_Overlay = 4,
	VRMessage_Overlay_Response_Couldnt_ಕಂಡುಹಿಡಿ_Or_Create_Client_Overlay = 5,
	VRMessageOverlayResponse_ApplicationQuit = 6,
} VRMessageOverlayResponse;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ EGamepad_ಪಠ್ಯ_ಒಳಹರಿವು_ಬಹುಲಕ
{
	EGamepad_ಪಠ್ಯ_ಒಳಹರಿವು_ಬಹುಲಕ_k_EGamepad_ಪಠ್ಯ_ಒಳಹರಿವು_ಬಹುಲಕ_ಸಾಮಾನ್ಯ = 0,
	EGamepad_ಪಠ್ಯ_ಒಳಹರಿವು_ಬಹುಲಕ_k_EGamepad_ಪಠ್ಯ_ಒಳಹರಿವು_ಬಹುಲಕ_Password = 1,
	EGamepad_ಪಠ್ಯ_ಒಳಹರಿವು_ಬಹುಲಕ_k_EGamepad_ಪಠ್ಯ_ಒಳಹರಿವು_ಬಹುಲಕ_Submit = 2,
} EGamepad_ಪಠ್ಯ_ಒಳಹರಿವು_ಬಹುಲಕ;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ EGamepad_ಪಠ್ಯ_ಒಳಹರಿವು_ಸಾಲು_ಬಹುಲಕ
{
	EGamepad_ಪಠ್ಯ_ಒಳಹರಿವು_ಸಾಲು_ಬಹುಲಕ_k_EGamepad_ಪಠ್ಯ_ಒಳಹರಿವು_ಸಾಲು_ಬಹುಲಕ_Single_ಸಾಲು = 0,
	EGamepad_ಪಠ್ಯ_ಒಳಹರಿವು_ಸಾಲು_ಬಹುಲಕ_k_EGamepad_ಪಠ್ಯ_ಒಳಹರಿವು_ಸಾಲು_ಬಹುಲಕ_ಅಪವರ್ತ್ಯ_ಸಾಲುಗಳು = 1,
} EGamepad_ಪಠ್ಯ_ಒಳಹರಿವು_ಸಾಲು_ಬಹುಲಕ;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ EVROverlay_Intersection_ಮುಖವಾಡ_Primitive_Type
{
	EVROverlay_Intersection_ಮುಖವಾಡ_Primitive_Type_Overlay_Intersection_Primitive_Type_Rectangle = 0,
	EVROverlay_Intersection_ಮುಖವಾಡ_Primitive_Type_Overlay_Intersection_Primitive_Type_Circle = 1,
} EVROverlay_Intersection_ಮುಖವಾಡ_Primitive_Type;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ EKeyboardFlags
{
	EKeyboard_Flags_Keyboard_Flag_ಕನಿಷ್ಠತಮ = 1,
	EKeyboardFlags_KeyboardFlag_Modal = 2,
} EKeyboardFlags;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ EDeviceType
{
	EDeviceType_DeviceType_Invalid = -1,
	EDevice_Type_Device_Type_ನೇರ_X11 = 0,
	EDeviceType_DeviceType_Vulkan = 1,
} EDeviceType;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ Headset_View_ಬಹುಲಕ_t
{
	Headset_View_ಬಹುಲಕ_t_Headset_View_ಬಹುಲಕ_ಎಡ = 0,
	Headset_View_ಬಹುಲಕ_t_Headset_View_ಬಹುಲಕ_ಬಲ = 1,
	Headset_View_ಬಹುಲಕ_t_Headset_View_ಬಹುಲಕ_Both = 2,
} Headset_View_ಬಹುಲಕ_t;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ EVRRenderModelError
{
	EVRRenderModelError_VRRenderModelError_None = 0,
	EVRRenderModelError_VRRenderModelError_Loading = 100,
	EVRRenderModelError_VRRenderModelError_NotSupported = 200,
	EVRRenderModelError_VRRenderModelError_InvalidArg = 300,
	EVRRenderModelError_VRRenderModelError_InvalidModel = 301,
	EVRRenderModelError_VRRenderModelError_NoShapes = 302,
	EVRRender_Model_Error_VRRender_Model_Error_ಅಪವರ್ತ್ಯ_Shapes = 303,
	EVRRenderModelError_VRRenderModelError_TooManyVertices = 304,
	EVRRender_Model_Error_VRRender_Model_Error_ಅಪವರ್ತ್ಯ_Textures = 305,
	EVRRender_Model_Error_VRRender_Model_Error_ಬಫರ್_Too_Small = 306,
	EVRRenderModelError_VRRenderModelError_NotEnoughNormals = 307,
	EVRRenderModelError_VRRenderModelError_NotEnoughTexCoords = 308,
	EVRRenderModelError_VRRenderModelError_InvalidTexture = 400,
} EVRRenderModelError;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ EVRRenderModelTextureFormat
{
	EVRRenderModelTextureFormat_VRRenderModelTextureFormat_RGBA8_SRGB = 0,
	EVRRenderModelTextureFormat_VRRenderModelTextureFormat_BC2 = 1,
	EVRRenderModelTextureFormat_VRRenderModelTextureFormat_BC4 = 2,
	EVRRenderModelTextureFormat_VRRenderModelTextureFormat_BC7 = 3,
	EVRRenderModelTextureFormat_VRRenderModelTextureFormat_BC7_SRGB = 4,
	EVRRenderModelTextureFormat_VRRenderModelTextureFormat_RGBA16_FLOAT = 5,
} EVRRenderModelTextureFormat;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ EVRNotificationType
{
	EVRNotificationType_Transient = 0,
	EVRNotificationType_Persistent = 1,
	EVRNotification_Type_Transient_System_With_User_ಮೌಲ್ಯ = 2,
} EVRNotificationType;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ EVRNotificationStyle
{
	EVRNotificationStyle_None = 0,
	EVRNotificationStyle_Application = 100,
	EVRNotificationStyle_Contact_Disabled = 200,
	EVRNotificationStyle_Contact_Enabled = 201,
	EVRNotification_Style_Contact_ಸಕ್ರಿಯ = 202,
} EVRNotificationStyle;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ EVRSettingsError
{
	EVRSettingsError_VRSettingsError_None = 0,
	EVRSettingsError_VRSettingsError_IPCFailed = 1,
	EVRSettingsError_VRSettingsError_WriteFailed = 2,
	EVRSettingsError_VRSettingsError_ReadFailed = 3,
	EVRSettingsError_VRSettingsError_JsonParseFailed = 4,
	EVRSettingsError_VRSettingsError_UnsetSettingHasNoDefault = 5,
} EVRSettingsError;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ EVRScreenshotError
{
	EVRScreenshotError_VRScreenshotError_None = 0,
	EVRScreenshotError_VRScreenshotError_RequestFailed = 1,
	EVRScreenshot_Error_VRScreenshot_Error_Incompatible_ಆವೃತ್ತಿ = 100,
	EVRScreenshot_Error_VRScreenshot_Error_Not_ಸಿಕ್ಕಿತು = 101,
	EVRScreenshot_Error_VRScreenshot_Error_ಬಫರ್_Too_Small = 102,
	EVRScreenshot_Error_VRScreenshot_Error_Screenshot_Already_ಒಳ_ಪ್ರಗತಿ = 108,
} EVRScreenshotError;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ EVRSkeletalTransformSpace
{
	EVRSkeletalTransformSpace_VRSkeletalTransformSpace_Model = 0,
	EVRSkeletal_Transform_Space_VRSkeletal_Transform_Space_ಪೋಷಕ = 1,
} EVRSkeletalTransformSpace;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ EVRSkeletalReferencePose
{
	EVRSkeletalReferencePose_VRSkeletalReferencePose_BindPose = 0,
	EVRSkeletalReferencePose_VRSkeletalReferencePose_OpenHand = 1,
	EVRSkeletalReferencePose_VRSkeletalReferencePose_Fist = 2,
	EVRSkeletal_Reference_Pose_VRSkeletal_Reference_Pose_Grip_ಎಲ್ಲೆ = 3,
} EVRSkeletalReferencePose;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ EVRFinger
{
	EVRFinger_VRFinger_Thumb = 0,
	EVRFinger_VRFinger_ಸೂಚ್ಯಂಕ = 1,
	EVRFinger_VRFinger_ಮಧ್ಯ = 2,
	EVRFinger_VRFinger_Ring = 3,
	EVRFinger_VRFinger_Pinky = 4,
	EVRFinger_VRFinger_ಎಣಿಕೆ = 5,
} EVRFinger;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ EVRFingerSplay
{
	EVRFinger_Splay_VRFinger_Splay_Thumb_ಸೂಚ್ಯಂಕ = 0,
	EVRFinger_Splay_VRFinger_Splay_ಸೂಚ್ಯಂಕ_ಮಧ್ಯ = 1,
	EVRFinger_Splay_VRFinger_Splay_ಮಧ್ಯ_Ring = 2,
	EVRFingerSplay_VRFingerSplay_Ring_Pinky = 3,
	EVRFinger_Splay_VRFinger_Splay_ಎಣಿಕೆ = 4,
} EVRFingerSplay;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ EVRSummaryType
{
	EVRSummaryType_VRSummaryType_FromAnimation = 0,
	EVRSummaryType_VRSummaryType_FromDevice = 1,
} EVRSummaryType;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ EVRInputFilterCancelType
{
	EVRInputFilterCancelType_VRInputFilterCancel_Timers = 0,
	EVRInputFilterCancelType_VRInputFilterCancel_Momentum = 1,
} EVRInputFilterCancelType;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ EVRInput_String_ಬಿಟ್ಟುಗಳು
{
	EVRInput_String_ಬಿಟ್ಟುಗಳು_VRInput_String_Hand = 1,
	EVRInput_String_ಬಿಟ್ಟುಗಳು_VRInput_String_Controller_Type = 2,
	EVRInput_String_ಬಿಟ್ಟುಗಳು_VRInput_String_ಒಳಹರಿವು_ಮೂಲ = 4,
	EVRInput_String_ಬಿಟ್ಟುಗಳು_VRInput_String_All = -1,
} EVRInput_String_ಬಿಟ್ಟುಗಳು;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ EIOBufferError
{
	EIOBufferError_IOBuffer_Success = 0,
	EIOBufferError_IOBuffer_OperationFailed = 100,
	EIOBufferError_IOBuffer_InvalidHandle = 101,
	EIOBuffer_Error_IOBuffer_Invalid_ವಾದ = 102,
	EIOBuffer_Error_IOBuffer_ಮಾರ್ಗ_Exists = 103,
	EIOBuffer_Error_IOBuffer_ಮಾರ್ಗ_Does_Not_Exist = 104,
	EIOBufferError_IOBuffer_Permission = 105,
} EIOBufferError;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ EIOBuffer_ಬಹುಲಕ
{
	EIOBuffer_ಬಹುಲಕ_IOBuffer_ಬಹುಲಕ_Read = 1,
	EIOBuffer_ಬಹುಲಕ_IOBuffer_ಬಹುಲಕ_Write = 2,
	EIOBuffer_ಬಹುಲಕ_IOBuffer_ಬಹುಲಕ_Create = 512,
} EIOBuffer_ಬಹುಲಕ;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ EVRDebugError
{
	EVRDebugError_VRDebugError_Success = 0,
	EVRDebugError_VRDebugError_BadParameter = 1,
} EVRDebugError;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ EPropertyWriteType
{
	EProperty_Write_Type_Property_Write_ಗಣ = 0,
	EPropertyWriteType_PropertyWrite_Erase = 1,
	EProperty_Write_Type_Property_Write_ಗಣ_Error = 2,
} EPropertyWriteType;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ EBlock_ಸರತಿ_Error
{
	EBlock_ಸರತಿ_Error_ಖಂಡ_ಸರತಿ_Error_None = 0,
	EBlock_ಸರತಿ_Error_ಖಂಡ_ಸರತಿ_Error_ಸರತಿ_Already_Exists = 1,
	EBlock_ಸರತಿ_Error_ಖಂಡ_ಸರತಿ_Error_ಸರತಿ_Not_ಸಿಕ್ಕಿತು = 2,
	EBlock_ಸರತಿ_Error_ಖಂಡ_ಸರತಿ_Error_ಖಂಡ_Not_ಲಭ್ಯ = 3,
	EBlock_ಸರತಿ_Error_ಖಂಡ_ಸರತಿ_Error_Invalid_Handle = 4,
	EBlock_ಸರತಿ_Error_ಖಂಡ_ಸರತಿ_Error_Invalid_Param = 5,
	EBlock_ಸರತಿ_Error_ಖಂಡ_ಸರತಿ_Error_Param_Mismatch = 6,
	EBlock_ಸರತಿ_Error_ಖಂಡ_ಸರತಿ_Error_ಆಂತರಿಕ_Error = 7,
	EBlock_ಸರತಿ_Error_ಖಂಡ_ಸರತಿ_Error_Already_Initialized = 8,
	EBlock_ಸರತಿ_Error_ಖಂಡ_ಸರತಿ_Error_Operation_Is_Server_Only = 9,
	EBlock_ಸರತಿ_Error_ಖಂಡ_ಸರತಿ_Error_Too_Many_Connections = 10,
} EBlock_ಸರತಿ_Error;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ EBlock_ಸರತಿ_Read_Type
{
	EBlock_ಸರತಿ_Read_Type_ಖಂಡ_ಸರತಿ_Read_Latest = 0,
	EBlock_ಸರತಿ_Read_Type_ಖಂಡ_ಸರತಿ_Read_New = 1,
	EBlock_ಸರತಿ_Read_Type_ಖಂಡ_ಸರತಿ_Read_ಮುಂದಿನ = 2,
} EBlock_ಸರತಿ_Read_Type;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ EBlock_ಸರತಿ_Creation_Flag
{
	EBlock_ಸರತಿ_Creation_Flag_ಖಂಡ_ಸರತಿ_Flag_Owner_Is_Reader = 1,
} EBlock_ಸರತಿ_Creation_Flag;


// OpenVR typedefs

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ uint32_t Property_Type_ಟ್ಯಾಗ್_t;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ uint32_t SpatialAnchorHandle_t;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ * glSharedTextureHandle_t;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ int32_t glInt_t;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ uint32_t glUInt_t;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ uint64_t SharedTextureHandle_t;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ uint32_t DriverId_t;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ uint32_t Tracked_Device_ಸೂಚ್ಯಂಕ_t;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ uint64_t WebConsoleHandle_t;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ uint64_t PropertyContainerHandle_t;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ PropertyContainerHandle_t DriverHandle_t;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ uint64_t VRActionHandle_t;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ uint64_t VRAction_ಗಣ_Handle_t;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ uint64_t VRInput_ಮೌಲ್ಯ_Handle_t;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ uint32_t VRComponentProperties;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ uint64_t VROverlayHandle_t;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ int32_t Bone_ಸೂಚ್ಯಂಕ_t;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ uint64_t TrackedCameraHandle_t;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ uint32_t ScreenshotHandle_t;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ int32_t TextureID_t;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ uint32_t VRNotificationId;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ uint64_t IOBufferHandle_t;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ uint64_t VrProfilerEventHandle_t;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ EVRInitError HmdError;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ EVREye Hmd_Eye;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ EColorSpace ColorSpace;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ETracking_ಫಲಿತಾಂಶ Hmd_Tracking_ಫಲಿತಾಂಶ;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ETrackedDeviceClass TrackedDeviceClass;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ETrackingUniverseOrigin TrackingUniverseOrigin;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ETrackedDeviceProperty TrackedDeviceProperty;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ETrackedPropertyError TrackedPropertyError;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ EVRSubmitFlags VRSubmitFlags_t;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ EVRState VRState_t;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ECollisionBoundsStyle CollisionBoundsStyle_t;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ EVROverlayError VROverlayError;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ EVRFirmwareError VRFirmwareError;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ EVRCompositorError VRCompositorError;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ EVRScreenshotError VRScreenshotsError;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ uint64_t ಮಾರ್ಗ_Handle_t;

// OpenVR Structs

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ HmdMatrix34_t
{
	ದಶಮಾಂಶ m[3][4]; //float[3][4]
} HmdMatrix34_t;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ HmdMatrix33_t
{
	ದಶಮಾಂಶ m[3][3]; //float[3][3]
} HmdMatrix33_t;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ HmdMatrix44_t
{
	ದಶಮಾಂಶ m[4][4]; //float[4][4]
} HmdMatrix44_t;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ HmdVector3_t
{
	ದಶಮಾಂಶ v[3]; //float[3]
} HmdVector3_t;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ HmdVector4_t
{
	ದಶಮಾಂಶ v[4]; //float[4]
} HmdVector4_t;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ HmdVector3d_t
{
	ದ್ವಿಗುಣ v[3]; //double[3]
} HmdVector3d_t;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ HmdVector2_t
{
	ದಶಮಾಂಶ v[2]; //float[2]
} HmdVector2_t;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ HmdQuaternion_t
{
	ದ್ವಿಗುಣ w;
	ದ್ವಿಗುಣ x;
	ದ್ವಿಗುಣ y;
	ದ್ವಿಗುಣ z;
} HmdQuaternion_t;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ HmdQuaternionf_t
{
	ದಶಮಾಂಶ w;
	ದಶಮಾಂಶ x;
	ದಶಮಾಂಶ y;
	ದಶಮಾಂಶ z;
} HmdQuaternionf_t;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ HmdColor_t
{
	ದಶಮಾಂಶ r;
	ದಶಮಾಂಶ g;
	ದಶಮಾಂಶ b;
	ದಶಮಾಂಶ a;
} HmdColor_t;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ HmdQuad_t
{
	ರಚನೆ HmdVector3_t vCorners[4]; //struct vr::HmdVector3_t[4]
} HmdQuad_t;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ HmdRect2_t
{
	ರಚನೆ HmdVector2_t v_ತುದಿ_ಎಡ;
	ರಚನೆ HmdVector2_t v_Bottom_ಬಲ;
} HmdRect2_t;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ VRBoneTransform_t
{
	ರಚನೆ HmdVector4_t position;
	ರಚನೆ HmdQuaternionf_t orientation;
} VRBoneTransform_t;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ DistortionCoordinates_t
{
	ದಶಮಾಂಶ rfRed[2]; //float[2]
	ದಶಮಾಂಶ rfGreen[2]; //float[2]
	ದಶಮಾಂಶ rfBlue[2]; //float[2]
} DistortionCoordinates_t;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ Texture_t
{
	ಶೂನ್ಯ * handle; // void *
	ಎಣಿಕೆ ETextureType eType;
	ಎಣಿಕೆ EColorSpace eColorSpace;
} Texture_t;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ TrackedDevicePose_t
{
	ರಚನೆ HmdMatrix34_t m_Device_ಗಮ್ಯ_Absolute_Tracking;
	ರಚನೆ HmdVector3_t vVelocity;
	ರಚನೆ HmdVector3_t vAngularVelocity;
	ಎಣಿಕೆ ETracking_ಫಲಿತಾಂಶ e_Tracking_ಫಲಿತಾಂಶ;
	bool bPoseIsValid;
	bool bDeviceIsConnected;
} TrackedDevicePose_t;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ VRTextureBounds_t
{
	ದಶಮಾಂಶ uMin;
	ದಶಮಾಂಶ vMin;
	ದಶಮಾಂಶ uMax;
	ದಶಮಾಂಶ vMax;
} VRTextureBounds_t;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ VRTextureWithPose_t
{
	ಶೂನ್ಯ * handle; // void *
	ಎಣಿಕೆ ETextureType eType;
	ಎಣಿಕೆ EColorSpace eColorSpace;
	ರಚನೆ HmdMatrix34_t m_Device_ಗಮ್ಯ_Absolute_Tracking;
} VRTextureWithPose_t;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ VRTexture_ಆಳ_Info_t
{
	ಶೂನ್ಯ * handle; // void *
	ರಚನೆ HmdMatrix44_t mProjection;
	ರಚನೆ HmdVector2_t vRange;
} VRTexture_ಆಳ_Info_t;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ VRTexture_With_ಆಳ_t
{
	ಶೂನ್ಯ * handle; // void *
	ಎಣಿಕೆ ETextureType eType;
	ಎಣಿಕೆ EColorSpace eColorSpace;
	ರಚನೆ VRTexture_ಆಳ_Info_t ಆಳ_2;
} VRTexture_With_ಆಳ_t;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ VRTexture_With_Pose_And_ಆಳ_t
{
	ಶೂನ್ಯ * handle; // void *
	ಎಣಿಕೆ ETextureType eType;
	ಎಣಿಕೆ EColorSpace eColorSpace;
	ರಚನೆ HmdMatrix34_t m_Device_ಗಮ್ಯ_Absolute_Tracking;
	ರಚನೆ VRTexture_ಆಳ_Info_t ಆಳ_2;
} VRTexture_With_Pose_And_ಆಳ_t;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ VRVulkan_Texture_ದತ್ತಾಂಶ_t
{
	uint64_t m_nImage;
	ರಚನೆ VkDevice_T * m_pDevice; // struct VkDevice_T *
	ರಚನೆ VkPhysicalDevice_T * m_pPhysicalDevice; // struct VkPhysicalDevice_T *
	ರಚನೆ VkInstance_T * m_pInstance; // struct VkInstance_T *
	ರಚನೆ Vk_ಸರತಿ_T * m_p_ಸರತಿ; // struct VkQueue_T *
	uint32_t m_n_ಸರತಿ_Family_ಸೂಚ್ಯಂಕ;
	uint32_t m_n_ಅಗಲ;
	uint32_t m_n_ಎತ್ತರ;
	uint32_t m_nFormat;
	uint32_t m_n_Sample_ಎಣಿಕೆ;
} VRVulkan_Texture_ದತ್ತಾಂಶ_t;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ VRVulkan_Texture_Array_ದತ್ತಾಂಶ_t
{
	uint32_t m_un_Array_ಸೂಚ್ಯಂಕ;
	uint32_t m_un_Array_ಗಾತ್ರ;
} VRVulkan_Texture_Array_ದತ್ತಾಂಶ_t;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ D3_D12_Texture_ದತ್ತಾಂಶ_t
{
	ರಚನೆ ID3D12Resource * m_pResource; // struct ID3D12Resource *
	ರಚನೆ ID3_D12_Command_ಸರತಿ * m_p_Command_ಸರತಿ; // struct ID3D12CommandQueue *
	uint32_t m_n_ಗಂಟು_ಮುಖವಾಡ;
} D3_D12_Texture_ದತ್ತಾಂಶ_t;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ VREvent_Controller_t
{
	uint32_t button;
} VREvent_Controller_t;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ VREvent_Mouse_t
{
	ದಶಮಾಂಶ x;
	ದಶಮಾಂಶ y;
	uint32_t button;
} VREvent_Mouse_t;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ VREvent_Scroll_t
{
	ದಶಮಾಂಶ xdelta;
	ದಶಮಾಂಶ ydelta;
	uint32_t ಬಳಸದ;
	ದಶಮಾಂಶ viewportscale;
} VREvent_Scroll_t;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ VREvent_TouchPadMove_t
{
	bool b_Finger_ಕೆಳಕ್ಕೆ;
	ದಶಮಾಂಶ fl_Seconds_Finger_ಕೆಳಕ್ಕೆ;
	ದಶಮಾಂಶ f_ಮೌಲ್ಯ_XFirst;
	ದಶಮಾಂಶ f_ಮೌಲ್ಯ_YFirst;
	ದಶಮಾಂಶ f_ಮೌಲ್ಯ_XRaw;
	ದಶಮಾಂಶ f_ಮೌಲ್ಯ_YRaw;
} VREvent_TouchPadMove_t;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ VREvent_Notification_t
{
	uint64_t ul_User_ಮೌಲ್ಯ;
	uint32_t notificationId;
} VREvent_Notification_t;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ VREvent_Process_t
{
	uint32_t pid;
	uint32_t oldPid;
	bool bForced;
	bool b_Connection_ಕಳೆದುಹೋದ;
} VREvent_Process_t;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ VREvent_Overlay_t
{
	uint64_t overlayHandle;
	uint64_t device_ಮಾರ್ಗ;
	uint64_t ಸ್ಮರಣೆ_ಖಂಡ_Id;
} VREvent_Overlay_t;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ VREvent_ಸ್ಥಿತಿ_t
{
	uint32_t ಸ್ಥಿತಿ_State;
} VREvent_ಸ್ಥಿತಿ_t;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ VREvent_Keyboard_t
{
	ಅಕ್ಷರ c_New_ಒಳಹರಿವು[8]; //char[8]
	uint64_t u_User_ಮೌಲ್ಯ;
} VREvent_Keyboard_t;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ VREvent_Ipd_t
{
	ದಶಮಾಂಶ ipdMeters;
} VREvent_Ipd_t;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ VREvent_Chaperone_t
{
	uint64_t m_n_ಹಿಂದಿನ_Universe;
	uint64_t m_nCurrentUniverse;
} VREvent_Chaperone_t;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ VREvent_Reserved_t
{
	uint64_t reserved0;
	uint64_t reserved1;
	uint64_t reserved2;
	uint64_t reserved3;
	uint64_t reserved4;
	uint64_t reserved5;
} VREvent_Reserved_t;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ VREvent_PerformanceTest_t
{
	uint32_t m_nFidelityLevel;
} VREvent_PerformanceTest_t;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ VREvent_SeatedZeroPoseReset_t
{
	bool bResetBySystemMenu;
} VREvent_SeatedZeroPoseReset_t;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ VREvent_Screenshot_t
{
	uint32_t handle;
	uint32_t type;
} VREvent_Screenshot_t;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ VREvent_Screenshot_ಪ್ರಗತಿ_t
{
	ದಶಮಾಂಶ ಪ್ರಗತಿ_2;
} VREvent_Screenshot_ಪ್ರಗತಿ_t;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ VREvent_ApplicationLaunch_t
{
	uint32_t pid;
	uint32_t un_ವಾದಗಳು_Handle;
} VREvent_ApplicationLaunch_t;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ VREvent_EditingCameraSurface_t
{
	uint64_t overlayHandle;
	uint32_t n_Visual_ಬಹುಲಕ;
} VREvent_EditingCameraSurface_t;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ VREvent_ಸಂದೇಶ_Overlay_t
{
	uint32_t unVRMessageOverlayResponse;
} VREvent_ಸಂದೇಶ_Overlay_t;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ VREvent_Property_t
{
	PropertyContainerHandle_t container;
	ಎಣಿಕೆ ETrackedDeviceProperty prop;
} VREvent_Property_t;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ VREvent_HapticVibration_t
{
	uint64_t containerHandle;
	uint64_t componentHandle;
	ದಶಮಾಂಶ fDurationSeconds;
	ದಶಮಾಂಶ fFrequency;
	ದಶಮಾಂಶ fAmplitude;
} VREvent_HapticVibration_t;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ VREvent_WebConsole_t
{
	WebConsoleHandle_t webConsoleHandle;
} VREvent_WebConsole_t;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ VREvent_ಒಳಹರಿವು_Binding_ತುಂಬು_t
{
	PropertyContainerHandle_t ulAppContainer;
	uint64_t ಮಾರ್ಗ_ಸಂದೇಶ;
	uint64_t ಮಾರ್ಗ_Url;
	uint64_t ಮಾರ್ಗ_Controller_Type;
} VREvent_ಒಳಹರಿವು_Binding_ತುಂಬು_t;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ VREvent_ಒಳಹರಿವು_Action_Manifest_ತುಂಬು_t
{
	uint64_t ಮಾರ್ಗ_App_ಕೀಲಿ;
	uint64_t ಮಾರ್ಗ_ಸಂದೇಶ;
	uint64_t ಮಾರ್ಗ_ಸಂದೇಶ_Param;
	uint64_t ಮಾರ್ಗ_Manifest_ಮಾರ್ಗ;
} VREvent_ಒಳಹರಿವು_Action_Manifest_ತುಂಬು_t;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ VREvent_SpatialAnchor_t
{
	SpatialAnchorHandle_t unHandle;
} VREvent_SpatialAnchor_t;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ VREvent_ಪ್ರಗತಿ_Update_t
{
	uint64_t ulApplicationPropertyContainer;
	uint64_t ಮಾರ್ಗ_Device;
	uint64_t ಮಾರ್ಗ_ಒಳಹರಿವು_ಮೂಲ;
	uint64_t ಮಾರ್ಗ_ಪ್ರಗತಿ_Action;
	uint64_t ಮಾರ್ಗ_Icon;
	ದಶಮಾಂಶ f_ಪ್ರಗತಿ;
} VREvent_ಪ್ರಗತಿ_Update_t;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ VREvent_ShowUI_t
{
	ಎಣಿಕೆ EShowUIType eType;
} VREvent_ShowUI_t;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ VREvent_ShowDevTools_t
{
	int32_t nBrowserIdentifier;
} VREvent_ShowDevTools_t;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ VREvent_HDCPError_t
{
	ಎಣಿಕೆ EHDCPError e_ಸಂಕೇತ;
} VREvent_HDCPError_t;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ RenderModel_ComponentState_t
{
	ರಚನೆ HmdMatrix34_t m_Tracking_ಗಮ್ಯ_Component_Render_Model;
	ರಚನೆ HmdMatrix34_t m_Tracking_ಗಮ್ಯ_Component_Local;
	VRComponentProperties uProperties;
} RenderModel_ComponentState_t;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ HiddenAreaMesh_t
{
	ರಚನೆ HmdVector2_t * p_ಶೃಂಗ_ದತ್ತಾಂಶ; // const struct vr::HmdVector2_t *
	uint32_t un_Triangle_ಎಣಿಕೆ;
} HiddenAreaMesh_t;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ VRControllerAxis_t
{
	ದಶಮಾಂಶ x;
	ದಶಮಾಂಶ y;
} VRControllerAxis_t;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ VRControllerState_t
{
	uint32_t un_Packet_ಅಂಕೆ;
	uint64_t ulButtonPressed;
	uint64_t ulButtonTouched;
	ರಚನೆ VRControllerAxis_t rAxis[5]; //struct vr::VRControllerAxis_t[5]
} VRControllerState_t;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ Camera_Video_ಹರಿವು_ಚೌಕಟ್ಟು_ಶೀರ್ಷಿಕೆ_t
{
	ಎಣಿಕೆ EVRTracked_Camera_ಚೌಕಟ್ಟು_Type e_ಚೌಕಟ್ಟು_Type;
	uint32_t n_ಅಗಲ;
	uint32_t n_ಎತ್ತರ;
	uint32_t n_ಬೈಟುಗಳು_ಪ್ರತಿ_Pixel;
	uint32_t n_ಚೌಕಟ್ಟು_Sequence;
	ರಚನೆ TrackedDevicePose_t trackedDevicePose;
	uint64_t ul_ಚೌಕಟ್ಟು_Exposure_ಸಮಯ;
} Camera_Video_ಹರಿವು_ಚೌಕಟ್ಟು_ಶೀರ್ಷಿಕೆ_t;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ Compositor_ಚೌಕಟ್ಟು_Timing
{
	uint32_t m_n_ಗಾತ್ರ;
	uint32_t m_n_ಚೌಕಟ್ಟು_ಸೂಚ್ಯಂಕ;
	uint32_t m_n_ಅಂಕೆ_ಚೌಕಟ್ಟು_Presents;
	uint32_t m_n_ಅಂಕೆ_Mis_Presented;
	uint32_t m_n_ಅಂಕೆ_Dropped_ಚೌಕಟ್ಟುಗಳು;
	uint32_t m_nReprojectionFlags;
	ದ್ವಿಗುಣ m_fl_System_ಸಮಯ_ಒಳ_Seconds;
	ದಶಮಾಂಶ m_flPreSubmitGpuMs;
	ದಶಮಾಂಶ m_flPostSubmitGpuMs;
	ದಶಮಾಂಶ m_fl_ಒಟ್ಟು_Render_Gpu_Ms;
	ದಶಮಾಂಶ m_flCompositorRenderGpuMs;
	ದಶಮಾಂಶ m_flCompositorRenderCpuMs;
	ದಶಮಾಂಶ m_flCompositorIdleCpuMs;
	ದಶಮಾಂಶ m_fl_Client_ಚೌಕಟ್ಟು_Interval_Ms;
	ದಶಮಾಂಶ m_flPresentCallCpuMs;
	ದಶಮಾಂಶ m_flWaitForPresentCpuMs;
	ದಶಮಾಂಶ m_fl_Submit_ಚೌಕಟ್ಟು_Ms;
	ದಶಮಾಂಶ m_flWaitGetPosesCalledMs;
	ದಶಮಾಂಶ m_flNewPosesReadyMs;
	ದಶಮಾಂಶ m_fl_New_ಚೌಕಟ್ಟು_Ready_Ms;
	ದಶಮಾಂಶ m_fl_Compositor_Update_ಆರಂಭ_Ms;
	ದಶಮಾಂಶ m_fl_Compositor_Update_ಕೊನೆ_Ms;
	ದಶಮಾಂಶ m_fl_Compositor_Render_ಆರಂಭ_Ms;
	TrackedDevicePose_t m_HmdPose;
	uint32_t m_n_ಅಂಕೆ_VSyncs_Ready_For_Use;
	uint32_t m_n_ಅಂಕೆ_VSyncs_ಗಮ್ಯ_ಮೊದಲ_View;
} Compositor_ಚೌಕಟ್ಟು_Timing;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ Compositor_BenchmarkResults
{
	ದಶಮಾಂಶ m_fl_Mega_Pixels_ಪ್ರತಿ_ಎರಡನೇ;
	ದಶಮಾಂಶ m_fl_Hmd_Recommended_Mega_Pixels_ಪ್ರತಿ_ಎರಡನೇ;
} Compositor_BenchmarkResults;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ Driver_ನೇರ_ಬಹುಲಕ_ಚೌಕಟ್ಟು_Timing
{
	uint32_t m_n_ಗಾತ್ರ;
	uint32_t m_n_ಅಂಕೆ_ಚೌಕಟ್ಟು_Presents;
	uint32_t m_n_ಅಂಕೆ_Mis_Presented;
	uint32_t m_n_ಅಂಕೆ_Dropped_ಚೌಕಟ್ಟುಗಳು;
	uint32_t m_nReprojectionFlags;
} Driver_ನೇರ_ಬಹುಲಕ_ಚೌಕಟ್ಟು_Timing;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ ImuSample_t
{
	ದ್ವಿಗುಣ f_Sample_ಸಮಯ;
	ರಚನೆ HmdVector3d_t vAccel;
	ರಚನೆ HmdVector3d_t vGyro;
	uint32_t unOffScaleFlags;
} ImuSample_t;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ App_Override_ಕೀಲಿಗಳು_t
{
	ಅಕ್ಷರ * pch_ಕೀಲಿ; // const char *
	ಅಕ್ಷರ * pch_ಮೌಲ್ಯ; // const char *
} App_Override_ಕೀಲಿಗಳು_t;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ Compositor_CumulativeStats
{
	uint32_t m_nPid;
	uint32_t m_n_ಅಂಕೆ_ಚೌಕಟ್ಟು_Presents;
	uint32_t m_n_ಅಂಕೆ_Dropped_ಚೌಕಟ್ಟುಗಳು;
	uint32_t m_n_ಅಂಕೆ_Reprojected_ಚೌಕಟ್ಟುಗಳು;
	uint32_t m_n_ಅಂಕೆ_ಚೌಕಟ್ಟು_Presents_On_Startup;
	uint32_t m_n_ಅಂಕೆ_Dropped_ಚೌಕಟ್ಟುಗಳು_On_Startup;
	uint32_t m_n_ಅಂಕೆ_Reprojected_ಚೌಕಟ್ಟುಗಳು_On_Startup;
	uint32_t m_n_ಅಂಕೆ_Loading;
	uint32_t m_n_ಅಂಕೆ_ಚೌಕಟ್ಟು_Presents_Loading;
	uint32_t m_n_ಅಂಕೆ_Dropped_ಚೌಕಟ್ಟುಗಳು_Loading;
	uint32_t m_n_ಅಂಕೆ_Reprojected_ಚೌಕಟ್ಟುಗಳು_Loading;
	uint32_t m_n_ಅಂಕೆ_Timed_ಹೊರಹೋಗು;
	uint32_t m_n_ಅಂಕೆ_ಚೌಕಟ್ಟು_Presents_Timed_ಹೊರಹೋಗು;
	uint32_t m_n_ಅಂಕೆ_Dropped_ಚೌಕಟ್ಟುಗಳು_Timed_ಹೊರಹೋಗು;
	uint32_t m_n_ಅಂಕೆ_Reprojected_ಚೌಕಟ್ಟುಗಳು_Timed_ಹೊರಹೋಗು;
	uint32_t m_n_ಅಂಕೆ_ಚೌಕಟ್ಟು_Submits;
	ದ್ವಿಗುಣ m_fl_ಮೊತ್ತ_Compositor_CPUTime_MS;
	ದ್ವಿಗುಣ m_fl_ಮೊತ್ತ_Compositor_GPUTime_MS;
	ದ್ವಿಗುಣ m_fl_ಮೊತ್ತ_ಗುರಿ_ಚೌಕಟ್ಟು_Times;
	ದ್ವಿಗುಣ m_fl_ಮೊತ್ತ_Application_CPUTime_MS;
	ದ್ವಿಗುಣ m_fl_ಮೊತ್ತ_Application_GPUTime_MS;
} Compositor_CumulativeStats;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ Compositor_StageRenderSettings
{
	ರಚನೆ HmdColor_t m_PrimaryColor;
	ರಚನೆ HmdColor_t m_SecondaryColor;
	ದಶಮಾಂಶ m_flVignetteInnerRadius;
	ದಶಮಾಂಶ m_flVignetteOuterRadius;
	ದಶಮಾಂಶ m_flFresnelStrength;
	bool m_bBackfaceCulling;
	bool m_bGreyscale;
	bool m_bWireframe;
} Compositor_StageRenderSettings;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ VROverlayIntersectionParams_t
{
	ರಚನೆ HmdVector3_t v_ಮೂಲ;
	ರಚನೆ HmdVector3_t vDirection;
	ಎಣಿಕೆ ETrackingUniverseOrigin eOrigin;
} VROverlayIntersectionParams_t;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ VROverlayIntersectionResults_t
{
	ರಚನೆ HmdVector3_t v_ಬಿಂದು;
	ರಚನೆ HmdVector3_t v_ಸಾಮಾನ್ಯ;
	ರಚನೆ HmdVector2_t vUVs;
	ದಶಮಾಂಶ f_ದೂರ;
} VROverlayIntersectionResults_t;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ Intersection_ಮುಖವಾಡ_Rectangle_t
{
	ದಶಮಾಂಶ m_fl_ತುದಿ_ಎಡ_X;
	ದಶಮಾಂಶ m_fl_ತುದಿ_ಎಡ_Y;
	ದಶಮಾಂಶ m_fl_ಅಗಲ;
	ದಶಮಾಂಶ m_fl_ಎತ್ತರ;
} Intersection_ಮುಖವಾಡ_Rectangle_t;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ Intersection_ಮುಖವಾಡ_Circle_t
{
	ದಶಮಾಂಶ m_flCenterX;
	ದಶಮಾಂಶ m_flCenterY;
	ದಶಮಾಂಶ m_flRadius;
} Intersection_ಮುಖವಾಡ_Circle_t;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ VROverlayProjection_t
{
	ದಶಮಾಂಶ f_ಎಡ;
	ದಶಮಾಂಶ f_ಬಲ;
	ದಶಮಾಂಶ f_ತುದಿ;
	ದಶಮಾಂಶ fBottom;
} VROverlayProjection_t;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ VROverlayView_t
{
	VROverlayHandle_t overlayHandle;
	ರಚನೆ Texture_t texture;
	ರಚನೆ VRTextureBounds_t textureBounds;
} VROverlayView_t;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ VRVulkanDevice_t
{
	ರಚನೆ VkInstance_T * m_pInstance; // struct VkInstance_T *
	ರಚನೆ VkDevice_T * m_pDevice; // struct VkDevice_T *
	ರಚನೆ VkPhysicalDevice_T * m_pPhysicalDevice; // struct VkPhysicalDevice_T *
	ರಚನೆ Vk_ಸರತಿ_T * m_p_ಸರತಿ; // struct VkQueue_T *
	uint32_t m_u_ಸರತಿ_Family_ಸೂಚ್ಯಂಕ;
} VRVulkanDevice_t;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ VRNativeDevice_t
{
	ಶೂನ್ಯ * handle; // void *
	ಎಣಿಕೆ EDeviceType eType;
} VRNativeDevice_t;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ Render_Model_ಶೃಂಗ_t
{
	ರಚನೆ HmdVector3_t vPosition;
	ರಚನೆ HmdVector3_t v_ಸಾಮಾನ್ಯ;
	ದಶಮಾಂಶ rfTextureCoord[2]; //float[2]
} Render_Model_ಶೃಂಗ_t;

#ಆದರೆ defined(__linux__) || defined(__APPLE__)
#ಸೂಚನೆ pack( ತಳ್ಳು, 4 )
#ಆದರೆ_ಅಂತ್ಯ
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ RenderModel_TextureMap_t
{
	uint16_t un_ಅಗಲ;
	uint16_t un_ಎತ್ತರ;
	uint8_t * rub_Texture_Map_ದತ್ತಾಂಶ; // const uint8_t *
	ಎಣಿಕೆ EVRRenderModelTextureFormat format;
	uint16_t un_Mip_ಮಟ್ಟಗಳು;
} RenderModel_TextureMap_t;

#ಆದರೆ defined(__linux__) || defined(__APPLE__)
#ಸೂಚನೆ pack( ತೆಗೆ )
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ defined(__linux__) || defined(__APPLE__)
#ಸೂಚನೆ pack( ತಳ್ಳು, 4 )
#ಆದರೆ_ಅಂತ್ಯ
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ RenderModel_t
{
	ರಚನೆ Render_Model_ಶೃಂಗ_t * r_ಶೃಂಗ_ದತ್ತಾಂಶ; // const struct vr::RenderModel_Vertex_t *
	uint32_t un_ಶೃಂಗ_ಎಣಿಕೆ;
	uint16_t * r_ಸೂಚ್ಯಂಕ_ದತ್ತಾಂಶ; // const uint16_t *
	uint32_t un_Triangle_ಎಣಿಕೆ;
	TextureID_t diffuseTextureId;
} RenderModel_t;

#ಆದರೆ defined(__linux__) || defined(__APPLE__)
#ಸೂಚನೆ pack( ತೆಗೆ )
#ಆದರೆ_ಅಂತ್ಯ
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ Render_Model_Controller_ಬಹುಲಕ_State_t
{
	bool bScrollWheelVisible;
} Render_Model_Controller_ಬಹುಲಕ_State_t;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ NotificationBitmap_t
{
	ಶೂನ್ಯ * m_p_Image_ದತ್ತಾಂಶ; // void *
	int32_t m_n_ಅಗಲ;
	int32_t m_n_ಎತ್ತರ;
	int32_t m_n_ಬೈಟುಗಳು_ಪ್ರತಿ_Pixel;
} NotificationBitmap_t;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ CVRSettingHelper
{
	intptr_t m_pSettings; // class vr::IVRSettings *
} CVRSettingHelper;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ ಒಳಹರಿವು_Analog_Action_ದತ್ತಾಂಶ_t
{
	bool b_ಸಕ್ರಿಯ;
	VRInput_ಮೌಲ್ಯ_Handle_t ಸಕ್ರಿಯ_Origin;
	ದಶಮಾಂಶ x;
	ದಶಮಾಂಶ y;
	ದಶಮಾಂಶ z;
	ದಶಮಾಂಶ deltaX;
	ದಶಮಾಂಶ deltaY;
	ದಶಮಾಂಶ deltaZ;
	ದಶಮಾಂಶ f_Update_ಸಮಯ;
} ಒಳಹರಿವು_Analog_Action_ದತ್ತಾಂಶ_t;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ ಒಳಹರಿವು_Digital_Action_ದತ್ತಾಂಶ_t
{
	bool b_ಸಕ್ರಿಯ;
	VRInput_ಮೌಲ್ಯ_Handle_t ಸಕ್ರಿಯ_Origin;
	bool bState;
	bool b_ಬದಲಾಯಿತು;
	ದಶಮಾಂಶ f_Update_ಸಮಯ;
} ಒಳಹರಿವು_Digital_Action_ದತ್ತಾಂಶ_t;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ ಒಳಹರಿವು_Pose_Action_ದತ್ತಾಂಶ_t
{
	bool b_ಸಕ್ರಿಯ;
	VRInput_ಮೌಲ್ಯ_Handle_t ಸಕ್ರಿಯ_Origin;
	ರಚನೆ TrackedDevicePose_t pose;
} ಒಳಹರಿವು_Pose_Action_ದತ್ತಾಂಶ_t;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ ಒಳಹರಿವು_Skeletal_Action_ದತ್ತಾಂಶ_t
{
	bool b_ಸಕ್ರಿಯ;
	VRInput_ಮೌಲ್ಯ_Handle_t ಸಕ್ರಿಯ_Origin;
} ಒಳಹರಿವು_Skeletal_Action_ದತ್ತಾಂಶ_t;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ ಒಳಹರಿವು_Origin_Info_t
{
	VRInput_ಮೌಲ್ಯ_Handle_t device_ಮಾರ್ಗ;
	Tracked_Device_ಸೂಚ್ಯಂಕ_t tracked_Device_ಸೂಚ್ಯಂಕ;
	ಅಕ್ಷರ rchRenderModelComponentName[128]; //char[128]
} ಒಳಹರಿವು_Origin_Info_t;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ ಒಳಹರಿವು_Binding_Info_t
{
	ಅಕ್ಷರ rch_Device_ಮಾರ್ಗ_Name[128]; //char[128]
	ಅಕ್ಷರ rch_ಒಳಹರಿವು_ಮಾರ್ಗ_Name[128]; //char[128]
	ಅಕ್ಷರ rch_ಬಹುಲಕ_Name[128]; //char[128]
	ಅಕ್ಷರ rch_ಸ್ಥಾನ_Name[128]; //char[128]
	ಅಕ್ಷರ rch_ಒಳಹರಿವು_ಮೂಲ_Type[32]; //char[32]
} ಒಳಹರಿವು_Binding_Info_t;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ VRActive_Action_ಗಣ_t
{
	VRAction_ಗಣ_Handle_t ul_Action_ಗಣ;
	VRInput_ಮೌಲ್ಯ_Handle_t ul_Restricted_ಗಮ್ಯ_Device;
	VRAction_ಗಣ_Handle_t ul_Secondary_Action_ಗಣ;
	uint32_t unPadding;
	int32_t n_ಆದ್ಯತೆ;
} VRActive_Action_ಗಣ_t;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ VRSkeletal_Summary_ದತ್ತಾಂಶ_t
{
	ದಶಮಾಂಶ flFingerCurl[5]; //float[5]
	ದಶಮಾಂಶ flFingerSplay[4]; //float[4]
} VRSkeletal_Summary_ದತ್ತಾಂಶ_t;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ SpatialAnchorPose_t
{
	ರಚನೆ HmdMatrix34_t m_Anchor_ಗಮ್ಯ_Absolute_Tracking;
} SpatialAnchorPose_t;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ COpenVRContext
{
	intptr_t m_pVRSystem; // class vr::IVRSystem *
	intptr_t m_pVRChaperone; // class vr::IVRChaperone *
	intptr_t m_p_VRChaperone_ಸಿದ್ಧತೆ; // class vr::IVRChaperoneSetup *
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

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ PropertyWrite_t
{
	ಎಣಿಕೆ ETrackedDeviceProperty prop;
	ಎಣಿಕೆ EPropertyWriteType writeType;
	ಎಣಿಕೆ ETrackedPropertyError e_ಗಣ_Error;
	ಶೂನ್ಯ * pv_ಬಫರ್; // void *
	uint32_t un_ಬಫರ್_ಗಾತ್ರ;
	Property_Type_ಟ್ಯಾಗ್_t un_ಟ್ಯಾಗ್;
	ಎಣಿಕೆ ETrackedPropertyError eError;
} PropertyWrite_t;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ PropertyRead_t
{
	ಎಣಿಕೆ ETrackedDeviceProperty prop;
	ಶೂನ್ಯ * pv_ಬಫರ್; // void *
	uint32_t un_ಬಫರ್_ಗಾತ್ರ;
	Property_Type_ಟ್ಯಾಗ್_t un_ಟ್ಯಾಗ್;
	uint32_t un_Required_ಬಫರ್_ಗಾತ್ರ;
	ಎಣಿಕೆ ETrackedPropertyError eError;
} PropertyRead_t;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ CVRPropertyHelpers
{
	intptr_t m_pProperties; // class vr::IVRProperties *
} CVRPropertyHelpers;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ ಮಾರ್ಗ_Write_t
{
	ಮಾರ್ಗ_Handle_t ul_ಮಾರ್ಗ;
	ಎಣಿಕೆ EPropertyWriteType writeType;
	ಎಣಿಕೆ ETrackedPropertyError e_ಗಣ_Error;
	ಶೂನ್ಯ * pv_ಬಫರ್; // void *
	uint32_t un_ಬಫರ್_ಗಾತ್ರ;
	Property_Type_ಟ್ಯಾಗ್_t un_ಟ್ಯಾಗ್;
	ಎಣಿಕೆ ETrackedPropertyError eError;
	ಅಕ್ಷರ * psz_ಮಾರ್ಗ; // const char *
} ಮಾರ್ಗ_Write_t;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ ಮಾರ್ಗ_Read_t
{
	ಮಾರ್ಗ_Handle_t ul_ಮಾರ್ಗ;
	ಶೂನ್ಯ * pv_ಬಫರ್; // void *
	uint32_t un_ಬಫರ್_ಗಾತ್ರ;
	Property_Type_ಟ್ಯಾಗ್_t un_ಟ್ಯಾಗ್;
	uint32_t un_Required_ಬಫರ್_ಗಾತ್ರ;
	ಎಣಿಕೆ ETrackedPropertyError eError;
	ಅಕ್ಷರ * psz_ಮಾರ್ಗ; // const char *
} ಮಾರ್ಗ_Read_t;


ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಒಕ್ಕೂಟ
{
	VREvent_Reserved_t reserved;
	VREvent_Controller_t controller;
	VREvent_Mouse_t mouse;
	VREvent_Scroll_t scroll;
	VREvent_Process_t process;
	VREvent_Notification_t notification;
	VREvent_Overlay_t overlay;
	VREvent_ಸ್ಥಿತಿ_t ಸ್ಥಿತಿ_2;
	VREvent_Keyboard_t keyboard;
	VREvent_Ipd_t ipd;
	VREvent_Chaperone_t chaperone;
	VREvent_PerformanceTest_t performanceTest;
	VREvent_TouchPadMove_t touchPadMove;
	VREvent_SeatedZeroPoseReset_t seatedZeroPoseReset;
	VREvent_Screenshot_t screenshot;
	VREvent_Screenshot_ಪ್ರಗತಿ_t screenshot_ಪ್ರಗತಿ;
	VREvent_ApplicationLaunch_t applicationLaunch;
	VREvent_EditingCameraSurface_t cameraSurface;
	VREvent_ಸಂದೇಶ_Overlay_t ಸಂದೇಶ_Overlay;
	VREvent_Property_t property;
	VREvent_HapticVibration_t hapticVibration;
	VREvent_WebConsole_t webConsole;
	VREvent_ಒಳಹರಿವು_Binding_ತುಂಬು_t ಒಳಹರಿವು_Binding;
	VREvent_ಒಳಹರಿವು_Action_Manifest_ತುಂಬು_t actionManifest;
	VREvent_SpatialAnchor_t spatialAnchor;
} VREvent_ದತ್ತಾಂಶ_t;

#ಆದರೆ defined(__linux__) || defined(__APPLE__) 
// This structure was originally defined mis-packed on Linux, preserved for 
// compatibility. 
#ಸೂಚನೆ pack( ತಳ್ಳು, 4 )
#ಆದರೆ_ಅಂತ್ಯ

/** An event posted by the server to all running applications */
ರಚನೆ VREvent_t
{
	uint32_t eventType; // EVREventType enum
	Tracked_Device_ಸೂಚ್ಯಂಕ_t tracked_Device_ಸೂಚ್ಯಂಕ;
	ದಶಮಾಂಶ eventAgeSeconds;
	// event data must be the end of the struct as its size is variable
	VREvent_ದತ್ತಾಂಶ_t ದತ್ತಾಂಶ;
};

#ಆದರೆ defined(__linux__) || defined(__APPLE__) 
#ಸೂಚನೆ pack( ತೆಗೆ )
#ಆದರೆ_ಅಂತ್ಯ


ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಒಕ್ಕೂಟ
{
	Intersection_ಮುಖವಾಡ_Rectangle_t m_Rectangle;
	Intersection_ಮುಖವಾಡ_Circle_t m_Circle;
} VROverlay_Intersection_ಮುಖವಾಡ_Primitive_ದತ್ತಾಂಶ_t;

ರಚನೆ VROverlay_Intersection_ಮುಖವಾಡ_Primitive_t
{
	EVROverlay_Intersection_ಮುಖವಾಡ_Primitive_Type m_nPrimitiveType;
	VROverlay_Intersection_ಮುಖವಾಡ_Primitive_ದತ್ತಾಂಶ_t m_Primitive;
};


// OpenVR Function Pointer Tables

ರಚನೆ VR_IVRSystem_Fn_ಕೋಷ್ಟಕ
{
	ಶೂನ್ಯ (OPENVR_FNTABLE_CALLTYPE *Get_Recommended_Render_ಗುರಿ_ಗಾತ್ರ)(uint32_t * pn_ಅಗಲ, uint32_t * pn_ಎತ್ತರ);
	ರಚನೆ HmdMatrix44_t (OPENVR_FNTABLE_CALLTYPE *Get_Projection_ಮಾತೃಕೆ)(EVREye eEye, ದಶಮಾಂಶ fNearZ, ದಶಮಾಂಶ fFarZ);
	ಶೂನ್ಯ (OPENVR_FNTABLE_CALLTYPE *GetProjectionRaw)(EVREye eEye, ದಶಮಾಂಶ * pf_ಎಡ, ದಶಮಾಂಶ * pf_ಬಲ, ದಶಮಾಂಶ * pf_ತುದಿ, ದಶಮಾಂಶ * pfBottom);
	bool (OPENVR_FNTABLE_CALLTYPE *ComputeDistortion)(EVREye eEye, ದಶಮಾಂಶ fU, ದಶಮಾಂಶ fV, ರಚನೆ DistortionCoordinates_t * pDistortionCoordinates);
	ರಚನೆ HmdMatrix34_t (OPENVR_FNTABLE_CALLTYPE *Get_Eye_ಗಮ್ಯ_ತಲೆ_Transform)(EVREye eEye);
	bool (OPENVR_FNTABLE_CALLTYPE *Get_ಸಮಯ_Since_ಕೊನೆಯ_Vsync)(ದಶಮಾಂಶ * pf_Seconds_Since_ಕೊನೆಯ_Vsync, uint64_t * pul_ಚೌಕಟ್ಟು_Counter);
	int32_t (OPENVR_FNTABLE_CALLTYPE *Get_D3_D9_Adapter_ಸೂಚ್ಯಂಕ)();
	ಶೂನ್ಯ (OPENVR_FNTABLE_CALLTYPE *GetDXGIOutputInfo)(int32_t * pn_Adapter_ಸೂಚ್ಯಂಕ);
	ಶೂನ್ಯ (OPENVR_FNTABLE_CALLTYPE *GetOutputDevice)(uint64_t * pnDevice, ETextureType textureType, ರಚನೆ VkInstance_T * pInstance);
	bool (OPENVR_FNTABLE_CALLTYPE *IsDisplayOnDesktop)();
	bool (OPENVR_FNTABLE_CALLTYPE *ಗಣ_Display_Visibility)(bool bIsVisibleOnDesktop);
	ಶೂನ್ಯ (OPENVR_FNTABLE_CALLTYPE *Get_Device_ಗಮ್ಯ_Absolute_Tracking_Pose)(ETrackingUniverseOrigin eOrigin, ದಶಮಾಂಶ f_Predicted_Seconds_ಗಮ್ಯ_Photons_From_Now, ರಚನೆ TrackedDevicePose_t * pTrackedDevicePoseArray, uint32_t un_Tracked_Device_Pose_Array_ಎಣಿಕೆ);
	ರಚನೆ HmdMatrix34_t (OPENVR_FNTABLE_CALLTYPE *Get_Seated_Zero_Pose_ಗಮ್ಯ_Standing_Absolute_Tracking_Pose)();
	ರಚನೆ HmdMatrix34_t (OPENVR_FNTABLE_CALLTYPE *Get_Raw_Zero_Pose_ಗಮ್ಯ_Standing_Absolute_Tracking_Pose)();
	uint32_t (OPENVR_FNTABLE_CALLTYPE *Get_Sorted_Tracked_Device_Indices_ದ_Class)(ETrackedDeviceClass eTrackedDeviceClass, Tracked_Device_ಸೂಚ್ಯಂಕ_t * pun_Tracked_Device_ಸೂಚ್ಯಂಕ_Array, uint32_t un_Tracked_Device_ಸೂಚ್ಯಂಕ_Array_ಎಣಿಕೆ, Tracked_Device_ಸೂಚ್ಯಂಕ_t un_Relative_ಗಮ್ಯ_Tracked_Device_ಸೂಚ್ಯಂಕ);
	EDeviceActivityLevel (OPENVR_FNTABLE_CALLTYPE *GetTrackedDeviceActivityLevel)(Tracked_Device_ಸೂಚ್ಯಂಕ_t unDeviceId);
	ಶೂನ್ಯ (OPENVR_FNTABLE_CALLTYPE *ApplyTransform)(ರಚನೆ TrackedDevicePose_t * pOutputPose, ರಚನೆ TrackedDevicePose_t * pTrackedDevicePose, ರಚನೆ HmdMatrix34_t * pTransform);
	Tracked_Device_ಸೂಚ್ಯಂಕ_t (OPENVR_FNTABLE_CALLTYPE *Get_Tracked_Device_ಸೂಚ್ಯಂಕ_For_Controller_Role)(ETrackedControllerRole unDeviceType);
	ETrackedControllerRole (OPENVR_FNTABLE_CALLTYPE *Get_Controller_Role_For_Tracked_Device_ಸೂಚ್ಯಂಕ)(Tracked_Device_ಸೂಚ್ಯಂಕ_t un_Device_ಸೂಚ್ಯಂಕ);
	ETrackedDeviceClass (OPENVR_FNTABLE_CALLTYPE *GetTrackedDeviceClass)(Tracked_Device_ಸೂಚ್ಯಂಕ_t un_Device_ಸೂಚ್ಯಂಕ);
	bool (OPENVR_FNTABLE_CALLTYPE *IsTrackedDeviceConnected)(Tracked_Device_ಸೂಚ್ಯಂಕ_t un_Device_ಸೂಚ್ಯಂಕ);
	bool (OPENVR_FNTABLE_CALLTYPE *GetBoolTrackedDeviceProperty)(Tracked_Device_ಸೂಚ್ಯಂಕ_t un_Device_ಸೂಚ್ಯಂಕ, ETrackedDeviceProperty prop, ETrackedPropertyError * pError);
	ದಶಮಾಂಶ (OPENVR_FNTABLE_CALLTYPE *GetFloatTrackedDeviceProperty)(Tracked_Device_ಸೂಚ್ಯಂಕ_t un_Device_ಸೂಚ್ಯಂಕ, ETrackedDeviceProperty prop, ETrackedPropertyError * pError);
	int32_t (OPENVR_FNTABLE_CALLTYPE *GetInt32TrackedDeviceProperty)(Tracked_Device_ಸೂಚ್ಯಂಕ_t un_Device_ಸೂಚ್ಯಂಕ, ETrackedDeviceProperty prop, ETrackedPropertyError * pError);
	uint64_t (OPENVR_FNTABLE_CALLTYPE *GetUint64TrackedDeviceProperty)(Tracked_Device_ಸೂಚ್ಯಂಕ_t un_Device_ಸೂಚ್ಯಂಕ, ETrackedDeviceProperty prop, ETrackedPropertyError * pError);
	ರಚನೆ HmdMatrix34_t (OPENVR_FNTABLE_CALLTYPE *GetMatrix34TrackedDeviceProperty)(Tracked_Device_ಸೂಚ್ಯಂಕ_t un_Device_ಸೂಚ್ಯಂಕ, ETrackedDeviceProperty prop, ETrackedPropertyError * pError);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetArrayTrackedDeviceProperty)(Tracked_Device_ಸೂಚ್ಯಂಕ_t un_Device_ಸೂಚ್ಯಂಕ, ETrackedDeviceProperty prop, Property_Type_ಟ್ಯಾಗ್_t propType, ಶೂನ್ಯ * p_ಬಫರ್, uint32_t un_ಬಫರ್_ಗಾತ್ರ, ETrackedPropertyError * pError);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetStringTrackedDeviceProperty)(Tracked_Device_ಸೂಚ್ಯಂಕ_t un_Device_ಸೂಚ್ಯಂಕ, ETrackedDeviceProperty prop, ಅಕ್ಷರ * pch_ಮೌಲ್ಯ, uint32_t un_ಬಫರ್_ಗಾತ್ರ, ETrackedPropertyError * pError);
	ಅಕ್ಷರ * (OPENVR_FNTABLE_CALLTYPE *GetPropErrorNameFromEnum)(ETrackedPropertyError error);
	bool (OPENVR_FNTABLE_CALLTYPE *Poll_ಮುಂದಿನ_Event)(ರಚನೆ VREvent_t * pEvent, uint32_t uncbVREvent);
	bool (OPENVR_FNTABLE_CALLTYPE *Poll_ಮುಂದಿನ_Event_With_Pose)(ETrackingUniverseOrigin eOrigin, ರಚನೆ VREvent_t * pEvent, uint32_t uncbVREvent, TrackedDevicePose_t * pTrackedDevicePose);
	ಅಕ್ಷರ * (OPENVR_FNTABLE_CALLTYPE *GetEventTypeNameFromEnum)(EVREventType eType);
	ರಚನೆ HiddenAreaMesh_t (OPENVR_FNTABLE_CALLTYPE *GetHiddenAreaMesh)(EVREye eEye, EHiddenAreaMeshType type);
	bool (OPENVR_FNTABLE_CALLTYPE *GetControllerState)(Tracked_Device_ಸೂಚ್ಯಂಕ_t un_Controller_Device_ಸೂಚ್ಯಂಕ, VRControllerState_t * pControllerState, uint32_t un_Controller_State_ಗಾತ್ರ);
	bool (OPENVR_FNTABLE_CALLTYPE *GetControllerStateWithPose)(ETrackingUniverseOrigin eOrigin, Tracked_Device_ಸೂಚ್ಯಂಕ_t un_Controller_Device_ಸೂಚ್ಯಂಕ, VRControllerState_t * pControllerState, uint32_t un_Controller_State_ಗಾತ್ರ, ರಚನೆ TrackedDevicePose_t * pTrackedDevicePose);
	ಶೂನ್ಯ (OPENVR_FNTABLE_CALLTYPE *TriggerHapticPulse)(Tracked_Device_ಸೂಚ್ಯಂಕ_t un_Controller_Device_ಸೂಚ್ಯಂಕ, uint32_t unAxisId, ಚಿಹ್ನೆರಹಿತ ಗಿಡ್ಡ usDurationMicroSec);
	ಅಕ್ಷರ * (OPENVR_FNTABLE_CALLTYPE *GetButtonIdNameFromEnum)(EVRButtonId eButtonId);
	ಅಕ್ಷರ * (OPENVR_FNTABLE_CALLTYPE *GetControllerAxisTypeNameFromEnum)(EVRControllerAxisType eAxisType);
	bool (OPENVR_FNTABLE_CALLTYPE *Is_ಒಳಹರಿವು_ಲಭ್ಯ)();
	bool (OPENVR_FNTABLE_CALLTYPE *IsSteamVRDrawingControllers)();
	bool (OPENVR_FNTABLE_CALLTYPE *ShouldApplicationPause)();
	bool (OPENVR_FNTABLE_CALLTYPE *ShouldApplicationReduceRenderingWork)();
	EVRFirmwareError (OPENVR_FNTABLE_CALLTYPE *PerformFirmwareUpdate)(Tracked_Device_ಸೂಚ್ಯಂಕ_t un_Device_ಸೂಚ್ಯಂಕ);
	ಶೂನ್ಯ (OPENVR_FNTABLE_CALLTYPE *AcknowledgeQuit_Exiting)();
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetAppContainerFilePaths)(ಅಕ್ಷರ * pch_ಬಫರ್, uint32_t un_ಬಫರ್_ಗಾತ್ರ);
	ಅಕ್ಷರ * (OPENVR_FNTABLE_CALLTYPE *Get_Runtime_ಆವೃತ್ತಿ)();
};

ರಚನೆ VR_IVRExtended_Display_Fn_ಕೋಷ್ಟಕ
{
	ಶೂನ್ಯ (OPENVR_FNTABLE_CALLTYPE *Get_ಕಿಟಕಿ_Bounds)(int32_t * pnX, int32_t * pnY, uint32_t * pn_ಅಗಲ, uint32_t * pn_ಎತ್ತರ);
	ಶೂನ್ಯ (OPENVR_FNTABLE_CALLTYPE *GetEyeOutputViewport)(EVREye eEye, uint32_t * pnX, uint32_t * pnY, uint32_t * pn_ಅಗಲ, uint32_t * pn_ಎತ್ತರ);
	ಶೂನ್ಯ (OPENVR_FNTABLE_CALLTYPE *GetDXGIOutputInfo)(int32_t * pn_Adapter_ಸೂಚ್ಯಂಕ, int32_t * pn_Adapter_Output_ಸೂಚ್ಯಂಕ);
};

ರಚನೆ VR_IVRTracked_Camera_Fn_ಕೋಷ್ಟಕ
{
	ಅಕ್ಷರ * (OPENVR_FNTABLE_CALLTYPE *GetCameraErrorNameFromEnum)(EVRTrackedCameraError eCameraError);
	EVRTrackedCameraError (OPENVR_FNTABLE_CALLTYPE *HasCamera)(Tracked_Device_ಸೂಚ್ಯಂಕ_t n_Device_ಸೂಚ್ಯಂಕ, bool * pHasCamera);
	EVRTrackedCameraError (OPENVR_FNTABLE_CALLTYPE *Get_Camera_ಚೌಕಟ್ಟು_ಗಾತ್ರ)(Tracked_Device_ಸೂಚ್ಯಂಕ_t n_Device_ಸೂಚ್ಯಂಕ, EVRTracked_Camera_ಚೌಕಟ್ಟು_Type e_ಚೌಕಟ್ಟು_Type, uint32_t * pn_ಅಗಲ, uint32_t * pn_ಎತ್ತರ, uint32_t * pn_ಚೌಕಟ್ಟು_ಬಫರ್_ಗಾತ್ರ);
	EVRTrackedCameraError (OPENVR_FNTABLE_CALLTYPE *GetCameraIntrinsics)(Tracked_Device_ಸೂಚ್ಯಂಕ_t n_Device_ಸೂಚ್ಯಂಕ, uint32_t n_Camera_ಸೂಚ್ಯಂಕ, EVRTracked_Camera_ಚೌಕಟ್ಟು_Type e_ಚೌಕಟ್ಟು_Type, HmdVector2_t * p_Focal_ಉದ್ದಳತೆ, HmdVector2_t * pCenter);
	EVRTrackedCameraError (OPENVR_FNTABLE_CALLTYPE *GetCameraProjection)(Tracked_Device_ಸೂಚ್ಯಂಕ_t n_Device_ಸೂಚ್ಯಂಕ, uint32_t n_Camera_ಸೂಚ್ಯಂಕ, EVRTracked_Camera_ಚೌಕಟ್ಟು_Type e_ಚೌಕಟ್ಟು_Type, ದಶಮಾಂಶ flZNear, ದಶಮಾಂಶ flZFar, HmdMatrix44_t * pProjection);
	EVRTrackedCameraError (OPENVR_FNTABLE_CALLTYPE *AcquireVideoStreamingService)(Tracked_Device_ಸೂಚ್ಯಂಕ_t n_Device_ಸೂಚ್ಯಂಕ, TrackedCameraHandle_t * pHandle);
	EVRTrackedCameraError (OPENVR_FNTABLE_CALLTYPE *ReleaseVideoStreamingService)(TrackedCameraHandle_t hTrackedCamera);
	EVRTrackedCameraError (OPENVR_FNTABLE_CALLTYPE *Get_Video_ಹರಿವು_ಚೌಕಟ್ಟು_ಬಫರ್)(TrackedCameraHandle_t hTrackedCamera, EVRTracked_Camera_ಚೌಕಟ್ಟು_Type e_ಚೌಕಟ್ಟು_Type, ಶೂನ್ಯ * p_ಚೌಕಟ್ಟು_ಬಫರ್, uint32_t n_ಚೌಕಟ್ಟು_ಬಫರ್_ಗಾತ್ರ, Camera_Video_ಹರಿವು_ಚೌಕಟ್ಟು_ಶೀರ್ಷಿಕೆ_t * p_ಚೌಕಟ್ಟು_ಶೀರ್ಷಿಕೆ, uint32_t n_ಚೌಕಟ್ಟು_ಶೀರ್ಷಿಕೆ_ಗಾತ್ರ);
	EVRTrackedCameraError (OPENVR_FNTABLE_CALLTYPE *Get_Video_ಹರಿವು_Texture_ಗಾತ್ರ)(Tracked_Device_ಸೂಚ್ಯಂಕ_t n_Device_ಸೂಚ್ಯಂಕ, EVRTracked_Camera_ಚೌಕಟ್ಟು_Type e_ಚೌಕಟ್ಟು_Type, VRTextureBounds_t * pTextureBounds, uint32_t * pn_ಅಗಲ, uint32_t * pn_ಎತ್ತರ);
	EVRTrackedCameraError (OPENVR_FNTABLE_CALLTYPE *Get_Video_ಹರಿವು_Texture_D3_D11)(TrackedCameraHandle_t hTrackedCamera, EVRTracked_Camera_ಚೌಕಟ್ಟು_Type e_ಚೌಕಟ್ಟು_Type, ಶೂನ್ಯ * pD3D11DeviceOrResource, ಶೂನ್ಯ ** ppD3D11ShaderResourceView, Camera_Video_ಹರಿವು_ಚೌಕಟ್ಟು_ಶೀರ್ಷಿಕೆ_t * p_ಚೌಕಟ್ಟು_ಶೀರ್ಷಿಕೆ, uint32_t n_ಚೌಕಟ್ಟು_ಶೀರ್ಷಿಕೆ_ಗಾತ್ರ);
	EVRTrackedCameraError (OPENVR_FNTABLE_CALLTYPE *Get_Video_ಹರಿವು_Texture_GL)(TrackedCameraHandle_t hTrackedCamera, EVRTracked_Camera_ಚೌಕಟ್ಟು_Type e_ಚೌಕಟ್ಟು_Type, glUInt_t * pglTextureId, Camera_Video_ಹರಿವು_ಚೌಕಟ್ಟು_ಶೀರ್ಷಿಕೆ_t * p_ಚೌಕಟ್ಟು_ಶೀರ್ಷಿಕೆ, uint32_t n_ಚೌಕಟ್ಟು_ಶೀರ್ಷಿಕೆ_ಗಾತ್ರ);
	EVRTrackedCameraError (OPENVR_FNTABLE_CALLTYPE *Release_Video_ಹರಿವು_Texture_GL)(TrackedCameraHandle_t hTrackedCamera, glUInt_t glTextureId);
	ಶೂನ್ಯ (OPENVR_FNTABLE_CALLTYPE *ಗಣ_Camera_Tracking_Space)(ETrackingUniverseOrigin eUniverse);
	ETrackingUniverseOrigin (OPENVR_FNTABLE_CALLTYPE *GetCameraTrackingSpace)();
};

ರಚನೆ VR_IVRApplications_Fn_ಕೋಷ್ಟಕ
{
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *ಕೂಡಿಸು_Application_Manifest)(ಅಕ್ಷರ * pch_Application_Manifest_ತುಂಬಿದ_ಮಾರ್ಗ, bool bTemporary);
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *RemoveApplicationManifest)(ಅಕ್ಷರ * pch_Application_Manifest_ತುಂಬಿದ_ಮಾರ್ಗ);
	bool (OPENVR_FNTABLE_CALLTYPE *IsApplicationInstalled)(ಅಕ್ಷರ * pch_App_ಕೀಲಿ);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *Get_Application_ಎಣಿಕೆ)();
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *Get_Application_ಕೀಲಿ_By_ಸೂಚ್ಯಂಕ)(uint32_t un_Application_ಸೂಚ್ಯಂಕ, ಅಕ್ಷರ * pch_App_ಕೀಲಿ_ಬಫರ್, uint32_t un_App_ಕೀಲಿ_ಬಫರ್_Len);
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *Get_Application_ಕೀಲಿ_By_Process_Id)(uint32_t unProcessId, ಅಕ್ಷರ * pch_App_ಕೀಲಿ_ಬಫರ್, uint32_t un_App_ಕೀಲಿ_ಬಫರ್_Len);
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *LaunchApplication)(ಅಕ್ಷರ * pch_App_ಕೀಲಿ);
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *LaunchTemplateApplication)(ಅಕ್ಷರ * pch_Template_App_ಕೀಲಿ, ಅಕ್ಷರ * pch_New_App_ಕೀಲಿ, ರಚನೆ App_Override_ಕೀಲಿಗಳು_t * p_ಕೀಲಿಗಳು, uint32_t un_ಕೀಲಿಗಳು);
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *LaunchApplicationFromMimeType)(ಅಕ್ಷರ * pchMimeType, ಅಕ್ಷರ * pch_ವಾದಗಳು);
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *LaunchDashboardOverlay)(ಅಕ್ಷರ * pch_App_ಕೀಲಿ);
	bool (OPENVR_FNTABLE_CALLTYPE *CancelApplicationLaunch)(ಅಕ್ಷರ * pch_App_ಕೀಲಿ);
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *IdentifyApplication)(uint32_t unProcessId, ಅಕ್ಷರ * pch_App_ಕೀಲಿ);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetApplicationProcessId)(ಅಕ್ಷರ * pch_App_ಕೀಲಿ);
	ಅಕ್ಷರ * (OPENVR_FNTABLE_CALLTYPE *GetApplicationsErrorNameFromEnum)(EVRApplicationError error);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetApplicationPropertyString)(ಅಕ್ಷರ * pch_App_ಕೀಲಿ, EVRApplicationProperty eProperty, ಅಕ್ಷರ * pch_Property_ಮೌಲ್ಯ_ಬಫರ್, uint32_t un_Property_ಮೌಲ್ಯ_ಬಫರ್_Len, EVRApplicationError * peError);
	bool (OPENVR_FNTABLE_CALLTYPE *GetApplicationPropertyBool)(ಅಕ್ಷರ * pch_App_ಕೀಲಿ, EVRApplicationProperty eProperty, EVRApplicationError * peError);
	uint64_t (OPENVR_FNTABLE_CALLTYPE *GetApplicationPropertyUint64)(ಅಕ್ಷರ * pch_App_ಕೀಲಿ, EVRApplicationProperty eProperty, EVRApplicationError * peError);
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *ಗಣ_Application_Auto_Launch)(ಅಕ್ಷರ * pch_App_ಕೀಲಿ, bool bAutoLaunch);
	bool (OPENVR_FNTABLE_CALLTYPE *GetApplicationAutoLaunch)(ಅಕ್ಷರ * pch_App_ಕೀಲಿ);
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *ಗಣ_Default_Application_For_Mime_Type)(ಅಕ್ಷರ * pch_App_ಕೀಲಿ, ಅಕ್ಷರ * pchMimeType);
	bool (OPENVR_FNTABLE_CALLTYPE *GetDefaultApplicationForMimeType)(ಅಕ್ಷರ * pchMimeType, ಅಕ್ಷರ * pch_App_ಕೀಲಿ_ಬಫರ್, uint32_t un_App_ಕೀಲಿ_ಬಫರ್_Len);
	bool (OPENVR_FNTABLE_CALLTYPE *GetApplicationSupportedMimeTypes)(ಅಕ್ಷರ * pch_App_ಕೀಲಿ, ಅಕ್ಷರ * pch_Mime_Types_ಬಫರ್, uint32_t un_Mime_Types_ಬಫರ್);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetApplicationsThatSupportMimeType)(ಅಕ್ಷರ * pchMimeType, ಅಕ್ಷರ * pch_App_ಕೀಲಿಗಳು_That_Support_ಬಫರ್, uint32_t un_App_ಕೀಲಿಗಳು_That_Support_ಬಫರ್);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetApplicationLaunchArguments)(uint32_t unHandle, ಅಕ್ಷರ * pch_ವಾದಗಳು, uint32_t un_ವಾದಗಳು);
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *GetStartingApplication)(ಅಕ್ಷರ * pch_App_ಕೀಲಿ_ಬಫರ್, uint32_t un_App_ಕೀಲಿ_ಬಫರ್_Len);
	EVRSceneApplicationState (OPENVR_FNTABLE_CALLTYPE *GetSceneApplicationState)();
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *PerformApplicationPrelaunchCheck)(ಅಕ್ಷರ * pch_App_ಕೀಲಿ);
	ಅಕ್ಷರ * (OPENVR_FNTABLE_CALLTYPE *GetSceneApplicationStateNameFromEnum)(EVRSceneApplicationState state);
	EVRApplicationError (OPENVR_FNTABLE_CALLTYPE *Launch_ಆಂತರಿಕ_Process)(ಅಕ್ಷರ * pch_ದ್ವಿಮಾನ_ಮಾರ್ಗ, ಅಕ್ಷರ * pchArguments, ಅಕ್ಷರ * pchWorkingDirectory);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetCurrentSceneProcessId)();
};

ರಚನೆ VR_IVRChaperone_Fn_ಕೋಷ್ಟಕ
{
	ChaperoneCalibrationState (OPENVR_FNTABLE_CALLTYPE *GetCalibrationState)();
	bool (OPENVR_FNTABLE_CALLTYPE *Get_Play_Area_ಗಾತ್ರ)(ದಶಮಾಂಶ * p_ಗಾತ್ರ_X, ದಶಮಾಂಶ * p_ಗಾತ್ರ_Z);
	bool (OPENVR_FNTABLE_CALLTYPE *GetPlayAreaRect)(ರಚನೆ HmdQuad_t * rect);
	ಶೂನ್ಯ (OPENVR_FNTABLE_CALLTYPE *ReloadInfo)();
	ಶೂನ್ಯ (OPENVR_FNTABLE_CALLTYPE *ಗಣ_Scene_Color)(ರಚನೆ HmdColor_t color);
	ಶೂನ್ಯ (OPENVR_FNTABLE_CALLTYPE *GetBoundsColor)(ರಚನೆ HmdColor_t * pOutputColorArray, ಪೂರ್ಣಾಂಕ n_ಅಂಕೆ_Output_Colors, ದಶಮಾಂಶ fl_Collision_Bounds_Fade_ದೂರ, ರಚನೆ HmdColor_t * pOutputCameraColor);
	bool (OPENVR_FNTABLE_CALLTYPE *AreBoundsVisible)();
	ಶೂನ್ಯ (OPENVR_FNTABLE_CALLTYPE *ForceBoundsVisible)(bool bForce);
	ಶೂನ್ಯ (OPENVR_FNTABLE_CALLTYPE *ResetZeroPose)(ETrackingUniverseOrigin eTrackingUniverseOrigin);
};

ರಚನೆ VR_IVRChaperone_ಸಿದ್ಧತೆ_Fn_ಕೋಷ್ಟಕ
{
	bool (OPENVR_FNTABLE_CALLTYPE *CommitWorkingCopy)(EChaperoneConfigFile configFile);
	ಶೂನ್ಯ (OPENVR_FNTABLE_CALLTYPE *RevertWorkingCopy)();
	bool (OPENVR_FNTABLE_CALLTYPE *Get_Working_Play_Area_ಗಾತ್ರ)(ದಶಮಾಂಶ * p_ಗಾತ್ರ_X, ದಶಮಾಂಶ * p_ಗಾತ್ರ_Z);
	bool (OPENVR_FNTABLE_CALLTYPE *GetWorkingPlayAreaRect)(ರಚನೆ HmdQuad_t * rect);
	bool (OPENVR_FNTABLE_CALLTYPE *GetWorkingCollisionBoundsInfo)(ರಚನೆ HmdQuad_t * p_Quads_ಬಫರ್, uint32_t * pun_Quads_ಎಣಿಕೆ);
	bool (OPENVR_FNTABLE_CALLTYPE *Get_ಜೀವಂತ_Collision_Bounds_Info)(ರಚನೆ HmdQuad_t * p_Quads_ಬಫರ್, uint32_t * pun_Quads_ಎಣಿಕೆ);
	bool (OPENVR_FNTABLE_CALLTYPE *Get_Working_Seated_Zero_Pose_ಗಮ್ಯ_Raw_Tracking_Pose)(ರಚನೆ HmdMatrix34_t * pmat_Seated_Zero_Pose_ಗಮ್ಯ_Raw_Tracking_Pose);
	bool (OPENVR_FNTABLE_CALLTYPE *Get_Working_Standing_Zero_Pose_ಗಮ್ಯ_Raw_Tracking_Pose)(ರಚನೆ HmdMatrix34_t * pmat_Standing_Zero_Pose_ಗಮ್ಯ_Raw_Tracking_Pose);
	ಶೂನ್ಯ (OPENVR_FNTABLE_CALLTYPE *ಗಣ_Working_Play_Area_ಗಾತ್ರ)(ದಶಮಾಂಶ ಗಾತ್ರ_X, ದಶಮಾಂಶ ಗಾತ್ರ_Z);
	ಶೂನ್ಯ (OPENVR_FNTABLE_CALLTYPE *ಗಣ_Working_Collision_Bounds_Info)(ರಚನೆ HmdQuad_t * p_Quads_ಬಫರ್, uint32_t un_Quads_ಎಣಿಕೆ);
	ಶೂನ್ಯ (OPENVR_FNTABLE_CALLTYPE *ಗಣ_Working_Perimeter)(ರಚನೆ HmdVector2_t * p_ಬಿಂದು_ಬಫರ್, uint32_t un_ಬಿಂದು_ಎಣಿಕೆ);
	ಶೂನ್ಯ (OPENVR_FNTABLE_CALLTYPE *ಗಣ_Working_Seated_Zero_Pose_ಗಮ್ಯ_Raw_Tracking_Pose)(ರಚನೆ HmdMatrix34_t * p_Mat_Seated_Zero_Pose_ಗಮ್ಯ_Raw_Tracking_Pose);
	ಶೂನ್ಯ (OPENVR_FNTABLE_CALLTYPE *ಗಣ_Working_Standing_Zero_Pose_ಗಮ್ಯ_Raw_Tracking_Pose)(ರಚನೆ HmdMatrix34_t * p_Mat_Standing_Zero_Pose_ಗಮ್ಯ_Raw_Tracking_Pose);
	ಶೂನ್ಯ (OPENVR_FNTABLE_CALLTYPE *ReloadFromDisk)(EChaperoneConfigFile configFile);
	bool (OPENVR_FNTABLE_CALLTYPE *Get_ಜೀವಂತ_Seated_Zero_Pose_ಗಮ್ಯ_Raw_Tracking_Pose)(ರಚನೆ HmdMatrix34_t * pmat_Seated_Zero_Pose_ಗಮ್ಯ_Raw_Tracking_Pose);
	bool (OPENVR_FNTABLE_CALLTYPE *Export_ಜೀವಂತ_ಗಮ್ಯ_ಬಫರ್)(ಅಕ್ಷರ * p_ಬಫರ್, uint32_t * pn_ಬಫರ್_ಉದ್ದಳತೆ);
	bool (OPENVR_FNTABLE_CALLTYPE *Import_From_ಬಫರ್_ಗಮ್ಯ_Working)(ಅಕ್ಷರ * p_ಬಫರ್, uint32_t nImportFlags);
	ಶೂನ್ಯ (OPENVR_FNTABLE_CALLTYPE *Show_Working_ಗಣ_Preview)();
	ಶೂನ್ಯ (OPENVR_FNTABLE_CALLTYPE *Hide_Working_ಗಣ_Preview)();
	ಶೂನ್ಯ (OPENVR_FNTABLE_CALLTYPE *ಸ್ಥಳ_ಸಿದ್ಧತೆ_Starting)();
};

ರಚನೆ VR_IVRCompositor_Fn_ಕೋಷ್ಟಕ
{
	ಶೂನ್ಯ (OPENVR_FNTABLE_CALLTYPE *ಗಣ_Tracking_Space)(ETrackingUniverseOrigin eOrigin);
	ETrackingUniverseOrigin (OPENVR_FNTABLE_CALLTYPE *GetTrackingSpace)();
	EVRCompositorError (OPENVR_FNTABLE_CALLTYPE *WaitGetPoses)(ರಚನೆ TrackedDevicePose_t * pRenderPoseArray, uint32_t un_Render_Pose_Array_ಎಣಿಕೆ, ರಚನೆ TrackedDevicePose_t * pGamePoseArray, uint32_t un_Game_Pose_Array_ಎಣಿಕೆ);
	EVRCompositorError (OPENVR_FNTABLE_CALLTYPE *Get_ಕೊನೆಯ_Poses)(ರಚನೆ TrackedDevicePose_t * pRenderPoseArray, uint32_t un_Render_Pose_Array_ಎಣಿಕೆ, ರಚನೆ TrackedDevicePose_t * pGamePoseArray, uint32_t un_Game_Pose_Array_ಎಣಿಕೆ);
	EVRCompositorError (OPENVR_FNTABLE_CALLTYPE *Get_ಕೊನೆಯ_Pose_For_Tracked_Device_ಸೂಚ್ಯಂಕ)(Tracked_Device_ಸೂಚ್ಯಂಕ_t un_Device_ಸೂಚ್ಯಂಕ, ರಚನೆ TrackedDevicePose_t * pOutputPose, ರಚನೆ TrackedDevicePose_t * pOutputGamePose);
	EVRCompositorError (OPENVR_FNTABLE_CALLTYPE *Submit)(EVREye eEye, ರಚನೆ Texture_t * pTexture, ರಚನೆ VRTextureBounds_t * pBounds, EVRSubmitFlags nSubmitFlags);
	ಶೂನ್ಯ (OPENVR_FNTABLE_CALLTYPE *Clear_ಕೊನೆಯ_Submitted_ಚೌಕಟ್ಟು)();
	ಶೂನ್ಯ (OPENVR_FNTABLE_CALLTYPE *PostPresentHandoff)();
	bool (OPENVR_FNTABLE_CALLTYPE *Get_ಚೌಕಟ್ಟು_Timing)(ರಚನೆ Compositor_ಚೌಕಟ್ಟು_Timing * pTiming, uint32_t un_ಚೌಕಟ್ಟುಗಳು_Ago);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *Get_ಚೌಕಟ್ಟು_Timings)(ರಚನೆ Compositor_ಚೌಕಟ್ಟು_Timing * pTiming, uint32_t n_ಚೌಕಟ್ಟುಗಳು);
	ದಶಮಾಂಶ (OPENVR_FNTABLE_CALLTYPE *Get_ಚೌಕಟ್ಟು_ಸಮಯ_ಉಳಿದ)();
	ಶೂನ್ಯ (OPENVR_FNTABLE_CALLTYPE *GetCumulativeStats)(ರಚನೆ Compositor_CumulativeStats * pStats, uint32_t n_Stats_ಗಾತ್ರ_ಒಳ_ಬೈಟುಗಳು);
	ಶೂನ್ಯ (OPENVR_FNTABLE_CALLTYPE *Fade_ಗಮ್ಯ_Color)(ದಶಮಾಂಶ fSeconds, ದಶಮಾಂಶ fRed, ದಶಮಾಂಶ fGreen, ದಶಮಾಂಶ fBlue, ದಶಮಾಂಶ fAlpha, bool bBackground);
	ರಚನೆ HmdColor_t (OPENVR_FNTABLE_CALLTYPE *GetCurrentFadeColor)(bool bBackground);
	ಶೂನ್ಯ (OPENVR_FNTABLE_CALLTYPE *FadeGrid)(ದಶಮಾಂಶ fSeconds, bool b_Fade_Grid_ಒಳ);
	ದಶಮಾಂಶ (OPENVR_FNTABLE_CALLTYPE *GetCurrentGridAlpha)();
	EVRCompositorError (OPENVR_FNTABLE_CALLTYPE *ಗಣ_Skybox_Override)(ರಚನೆ Texture_t * pTextures, uint32_t un_Texture_ಎಣಿಕೆ);
	ಶೂನ್ಯ (OPENVR_FNTABLE_CALLTYPE *ClearSkyboxOverride)();
	ಶೂನ್ಯ (OPENVR_FNTABLE_CALLTYPE *Compositor_Bring_ಗಮ್ಯ_Front)();
	ಶೂನ್ಯ (OPENVR_FNTABLE_CALLTYPE *Compositor_Go_ಗಮ್ಯ_ಹಿಂಭಾಗ)();
	ಶೂನ್ಯ (OPENVR_FNTABLE_CALLTYPE *CompositorQuit)();
	bool (OPENVR_FNTABLE_CALLTYPE *IsFullscreen)();
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetCurrentSceneFocusProcess)();
	uint32_t (OPENVR_FNTABLE_CALLTYPE *Get_ಕೊನೆಯ_ಚೌಕಟ್ಟು_Renderer)();
	bool (OPENVR_FNTABLE_CALLTYPE *CanRenderScene)();
	ಶೂನ್ಯ (OPENVR_FNTABLE_CALLTYPE *Show_Mirror_ಕಿಟಕಿ)();
	ಶೂನ್ಯ (OPENVR_FNTABLE_CALLTYPE *Hide_Mirror_ಕಿಟಕಿ)();
	bool (OPENVR_FNTABLE_CALLTYPE *Is_Mirror_ಕಿಟಕಿ_Visible)();
	ಶೂನ್ಯ (OPENVR_FNTABLE_CALLTYPE *CompositorDumpImages)();
	bool (OPENVR_FNTABLE_CALLTYPE *Should_App_Render_With_ಕೆಳಗಿನ_Resources)();
	ಶೂನ್ಯ (OPENVR_FNTABLE_CALLTYPE *ForceInterleavedReprojectionOn)(bool bOverride);
	ಶೂನ್ಯ (OPENVR_FNTABLE_CALLTYPE *ForceReconnectProcess)();
	ಶೂನ್ಯ (OPENVR_FNTABLE_CALLTYPE *SuspendRendering)(bool bSuspend);
	EVRCompositorError (OPENVR_FNTABLE_CALLTYPE *GetMirrorTextureD3D11)(EVREye eEye, ಶೂನ್ಯ * pD3D11DeviceOrResource, ಶೂನ್ಯ ** ppD3D11ShaderResourceView);
	ಶೂನ್ಯ (OPENVR_FNTABLE_CALLTYPE *ReleaseMirrorTextureD3D11)(ಶೂನ್ಯ * pD3D11ShaderResourceView);
	EVRCompositorError (OPENVR_FNTABLE_CALLTYPE *GetMirrorTextureGL)(EVREye eEye, glUInt_t * pglTextureId, glSharedTextureHandle_t * pglSharedTextureHandle);
	bool (OPENVR_FNTABLE_CALLTYPE *ReleaseSharedGLTexture)(glUInt_t glTextureId, glSharedTextureHandle_t glSharedTextureHandle);
	ಶೂನ್ಯ (OPENVR_FNTABLE_CALLTYPE *ಬೀಗ_GLShared_Texture_For_Access)(glSharedTextureHandle_t glSharedTextureHandle);
	ಶೂನ್ಯ (OPENVR_FNTABLE_CALLTYPE *UnlockGLSharedTextureForAccess)(glSharedTextureHandle_t glSharedTextureHandle);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetVulkanInstanceExtensionsRequired)(ಅಕ್ಷರ * pch_ಮೌಲ್ಯ, uint32_t un_ಬಫರ್_ಗಾತ್ರ);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetVulkanDeviceExtensionsRequired)(ರಚನೆ VkPhysicalDevice_T * pPhysicalDevice, ಅಕ್ಷರ * pch_ಮೌಲ್ಯ, uint32_t un_ಬಫರ್_ಗಾತ್ರ);
	ಶೂನ್ಯ (OPENVR_FNTABLE_CALLTYPE *ಗಣ_Explicit_Timing_ಬಹುಲಕ)(EVRCompositor_Timing_ಬಹುಲಕ e_Timing_ಬಹುಲಕ);
	EVRCompositorError (OPENVR_FNTABLE_CALLTYPE *Submit_Explicit_Timing_ದತ್ತಾಂಶ)();
	bool (OPENVR_FNTABLE_CALLTYPE *IsMotionSmoothingEnabled)();
	bool (OPENVR_FNTABLE_CALLTYPE *IsMotionSmoothingSupported)();
	bool (OPENVR_FNTABLE_CALLTYPE *IsCurrentSceneFocusAppLoading)();
	EVRCompositorError (OPENVR_FNTABLE_CALLTYPE *ಗಣ_Stage_Override_Async)(ಅಕ್ಷರ * pch_Render_Model_ಮಾರ್ಗ, ರಚನೆ HmdMatrix34_t * pTransform, ರಚನೆ Compositor_StageRenderSettings * pRenderSettings, uint32_t n_ಗಾತ್ರ_ದ_Render_Settings);
	ಶೂನ್ಯ (OPENVR_FNTABLE_CALLTYPE *ClearStageOverride)();
	bool (OPENVR_FNTABLE_CALLTYPE *GetCompositorBenchmarkResults)(ರಚನೆ Compositor_BenchmarkResults * pBenchmarkResults, uint32_t n_ಗಾತ್ರ_ದ_Benchmark_Results);
	EVRCompositorError (OPENVR_FNTABLE_CALLTYPE *Get_ಕೊನೆಯ_Pose_Prediction_IDs)(uint32_t * pRenderPosePredictionID, uint32_t * pGamePosePredictionID);
	EVRCompositorError (OPENVR_FNTABLE_CALLTYPE *Get_Poses_For_ಚೌಕಟ್ಟು)(uint32_t unPosePredictionID, ರಚನೆ TrackedDevicePose_t * pPoseArray, uint32_t un_Pose_Array_ಎಣಿಕೆ);
};

ರಚನೆ VR_IVROverlay_Fn_ಕೋಷ್ಟಕ
{
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *ಕಂಡುಹಿಡಿ_Overlay)(ಅಕ್ಷರ * pch_Overlay_ಕೀಲಿ, VROverlayHandle_t * pOverlayHandle);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *CreateOverlay)(ಅಕ್ಷರ * pch_Overlay_ಕೀಲಿ, ಅಕ್ಷರ * pchOverlayName, VROverlayHandle_t * pOverlayHandle);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *DestroyOverlay)(VROverlayHandle_t ulOverlayHandle);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *Get_Overlay_ಕೀಲಿ)(VROverlayHandle_t ulOverlayHandle, ಅಕ್ಷರ * pch_ಮೌಲ್ಯ, uint32_t un_ಬಫರ್_ಗಾತ್ರ, EVROverlayError * pError);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetOverlayName)(VROverlayHandle_t ulOverlayHandle, ಅಕ್ಷರ * pch_ಮೌಲ್ಯ, uint32_t un_ಬಫರ್_ಗಾತ್ರ, EVROverlayError * pError);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *ಗಣ_Overlay_Name)(VROverlayHandle_t ulOverlayHandle, ಅಕ್ಷರ * pchName);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *Get_Overlay_Image_ದತ್ತಾಂಶ)(VROverlayHandle_t ulOverlayHandle, ಶೂನ್ಯ * pv_ಬಫರ್, uint32_t un_ಬಫರ್_ಗಾತ್ರ, uint32_t * pun_ಅಗಲ, uint32_t * pun_ಎತ್ತರ);
	ಅಕ್ಷರ * (OPENVR_FNTABLE_CALLTYPE *GetOverlayErrorNameFromEnum)(EVROverlayError error);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *ಗಣ_Overlay_Rendering_Pid)(VROverlayHandle_t ulOverlayHandle, uint32_t unPID);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetOverlayRenderingPid)(VROverlayHandle_t ulOverlayHandle);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *ಗಣ_Overlay_Flag)(VROverlayHandle_t ulOverlayHandle, VROverlayFlags eOverlayFlag, bool bEnabled);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayFlag)(VROverlayHandle_t ulOverlayHandle, VROverlayFlags eOverlayFlag, bool * pbEnabled);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayFlags)(VROverlayHandle_t ulOverlayHandle, uint32_t * pFlags);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *ಗಣ_Overlay_Color)(VROverlayHandle_t ulOverlayHandle, ದಶಮಾಂಶ fRed, ದಶಮಾಂಶ fGreen, ದಶಮಾಂಶ fBlue);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayColor)(VROverlayHandle_t ulOverlayHandle, ದಶಮಾಂಶ * pfRed, ದಶಮಾಂಶ * pfGreen, ದಶಮಾಂಶ * pfBlue);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *ಗಣ_Overlay_Alpha)(VROverlayHandle_t ulOverlayHandle, ದಶಮಾಂಶ fAlpha);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayAlpha)(VROverlayHandle_t ulOverlayHandle, ದಶಮಾಂಶ * pfAlpha);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *ಗಣ_Overlay_Texel_Aspect)(VROverlayHandle_t ulOverlayHandle, ದಶಮಾಂಶ fTexelAspect);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayTexelAspect)(VROverlayHandle_t ulOverlayHandle, ದಶಮಾಂಶ * pfTexelAspect);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *ಗಣ_Overlay_ವಿಂಗಡಿಸು_ಕ್ರಮ)(VROverlayHandle_t ulOverlayHandle, uint32_t un_ವಿಂಗಡಿಸು_ಕ್ರಮ);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *Get_Overlay_ವಿಂಗಡಿಸು_ಕ್ರಮ)(VROverlayHandle_t ulOverlayHandle, uint32_t * pun_ವಿಂಗಡಿಸು_ಕ್ರಮ);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *ಗಣ_Overlay_ಅಗಲ_ಒಳ_Meters)(VROverlayHandle_t ulOverlayHandle, ದಶಮಾಂಶ f_ಅಗಲ_ಒಳ_Meters);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *Get_Overlay_ಅಗಲ_ಒಳ_Meters)(VROverlayHandle_t ulOverlayHandle, ದಶಮಾಂಶ * pf_ಅಗಲ_ಒಳ_Meters);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *ಗಣ_Overlay_Curvature)(VROverlayHandle_t ulOverlayHandle, ದಶಮಾಂಶ fCurvature);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayCurvature)(VROverlayHandle_t ulOverlayHandle, ದಶಮಾಂಶ * pfCurvature);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *ಗಣ_Overlay_Pre_ವಕ್ರ_Pitch)(VROverlayHandle_t ulOverlayHandle, ದಶಮಾಂಶ fRadians);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *Get_Overlay_Pre_ವಕ್ರ_Pitch)(VROverlayHandle_t ulOverlayHandle, ದಶಮಾಂಶ * pfRadians);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *ಗಣ_Overlay_Texture_Color_Space)(VROverlayHandle_t ulOverlayHandle, EColorSpace eTextureColorSpace);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayTextureColorSpace)(VROverlayHandle_t ulOverlayHandle, EColorSpace * peTextureColorSpace);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *ಗಣ_Overlay_Texture_Bounds)(VROverlayHandle_t ulOverlayHandle, ರಚನೆ VRTextureBounds_t * pOverlayTextureBounds);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayTextureBounds)(VROverlayHandle_t ulOverlayHandle, ರಚನೆ VRTextureBounds_t * pOverlayTextureBounds);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayTransformType)(VROverlayHandle_t ulOverlayHandle, VROverlayTransformType * peTransformType);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *ಗಣ_Overlay_Transform_Absolute)(VROverlayHandle_t ulOverlayHandle, ETrackingUniverseOrigin eTrackingOrigin, ರಚನೆ HmdMatrix34_t * pmat_Tracking_Origin_ಗಮ್ಯ_Overlay_Transform);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayTransformAbsolute)(VROverlayHandle_t ulOverlayHandle, ETrackingUniverseOrigin * peTrackingOrigin, ರಚನೆ HmdMatrix34_t * pmat_Tracking_Origin_ಗಮ್ಯ_Overlay_Transform);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *ಗಣ_Overlay_Transform_Tracked_Device_Relative)(VROverlayHandle_t ulOverlayHandle, Tracked_Device_ಸೂಚ್ಯಂಕ_t unTrackedDevice, ರಚನೆ HmdMatrix34_t * pmat_Tracked_Device_ಗಮ್ಯ_Overlay_Transform);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayTransformTrackedDeviceRelative)(VROverlayHandle_t ulOverlayHandle, Tracked_Device_ಸೂಚ್ಯಂಕ_t * punTrackedDevice, ರಚನೆ HmdMatrix34_t * pmat_Tracked_Device_ಗಮ್ಯ_Overlay_Transform);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *ಗಣ_Overlay_Transform_Tracked_Device_Component)(VROverlayHandle_t ulOverlayHandle, Tracked_Device_ಸೂಚ್ಯಂಕ_t un_Device_ಸೂಚ್ಯಂಕ, ಅಕ್ಷರ * pchComponentName);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayTransformTrackedDeviceComponent)(VROverlayHandle_t ulOverlayHandle, Tracked_Device_ಸೂಚ್ಯಂಕ_t * pun_Device_ಸೂಚ್ಯಂಕ, ಅಕ್ಷರ * pchComponentName, uint32_t un_Component_Name_ಗಾತ್ರ);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayTransformOverlayRelative)(VROverlayHandle_t ulOverlayHandle, VROverlayHandle_t * ul_Overlay_Handle_ಪೋಷಕ, ರಚನೆ HmdMatrix34_t * pmat_ಪೋಷಕ_Overlay_ಗಮ್ಯ_Overlay_Transform);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *ಗಣ_Overlay_Transform_Overlay_Relative)(VROverlayHandle_t ulOverlayHandle, VROverlayHandle_t ul_Overlay_Handle_ಪೋಷಕ, ರಚನೆ HmdMatrix34_t * pmat_ಪೋಷಕ_Overlay_ಗಮ್ಯ_Overlay_Transform);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *ಗಣ_Overlay_Transform_Cursor)(VROverlayHandle_t ulCursorOverlayHandle, ರಚನೆ HmdVector2_t * pvHotspot);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayTransformCursor)(VROverlayHandle_t ulOverlayHandle, ರಚನೆ HmdVector2_t * pvHotspot);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *ಗಣ_Overlay_Transform_Projection)(VROverlayHandle_t ulOverlayHandle, ETrackingUniverseOrigin eTrackingOrigin, ರಚನೆ HmdMatrix34_t * pmat_Tracking_Origin_ಗಮ್ಯ_Overlay_Transform, ರಚನೆ VROverlayProjection_t * pProjection, EVREye eEye);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *ShowOverlay)(VROverlayHandle_t ulOverlayHandle);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *HideOverlay)(VROverlayHandle_t ulOverlayHandle);
	bool (OPENVR_FNTABLE_CALLTYPE *IsOverlayVisible)(VROverlayHandle_t ulOverlayHandle);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetTransformForOverlayCoordinates)(VROverlayHandle_t ulOverlayHandle, ETrackingUniverseOrigin eTrackingOrigin, ರಚನೆ HmdVector2_t coordinates_ಒಳ_Overlay, ರಚನೆ HmdMatrix34_t * pmatTransform);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *Wait_ಚೌಕಟ್ಟು_Sync)(uint32_t nTimeoutMs);
	bool (OPENVR_FNTABLE_CALLTYPE *Poll_ಮುಂದಿನ_Overlay_Event)(VROverlayHandle_t ulOverlayHandle, ರಚನೆ VREvent_t * pEvent, uint32_t uncbVREvent);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *Get_Overlay_ಒಳಹರಿವು_ವಿಧಾನ)(VROverlayHandle_t ulOverlayHandle, VROverlay_ಒಳಹರಿವು_ವಿಧಾನ * pe_ಒಳಹರಿವು_ವಿಧಾನ);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *ಗಣ_Overlay_ಒಳಹರಿವು_ವಿಧಾನ)(VROverlayHandle_t ulOverlayHandle, VROverlay_ಒಳಹರಿವು_ವಿಧಾನ e_ಒಳಹರಿವು_ವಿಧಾನ);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayMouseScale)(VROverlayHandle_t ulOverlayHandle, ರಚನೆ HmdVector2_t * pvecMouseScale);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *ಗಣ_Overlay_Mouse_Scale)(VROverlayHandle_t ulOverlayHandle, ರಚನೆ HmdVector2_t * pvecMouseScale);
	bool (OPENVR_FNTABLE_CALLTYPE *ComputeOverlayIntersection)(VROverlayHandle_t ulOverlayHandle, ರಚನೆ VROverlayIntersectionParams_t * pParams, ರಚನೆ VROverlayIntersectionResults_t * pResults);
	bool (OPENVR_FNTABLE_CALLTYPE *Is_Hover_ಗುರಿ_Overlay)(VROverlayHandle_t ulOverlayHandle);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *ಗಣ_Overlay_Intersection_ಮುಖವಾಡ)(VROverlayHandle_t ulOverlayHandle, ರಚನೆ VROverlay_Intersection_ಮುಖವಾಡ_Primitive_t * p_ಮುಖವಾಡ_Primitives, uint32_t un_ಅಂಕೆ_ಮುಖವಾಡ_Primitives, uint32_t un_Primitive_ಗಾತ್ರ);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *TriggerLaserMouseHapticVibration)(VROverlayHandle_t ulOverlayHandle, ದಶಮಾಂಶ fDurationSeconds, ದಶಮಾಂಶ fFrequency, ದಶಮಾಂಶ fAmplitude);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *ಗಣ_Overlay_Cursor)(VROverlayHandle_t ulOverlayHandle, VROverlayHandle_t ulCursorHandle);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *ಗಣ_Overlay_Cursor_Position_Override)(VROverlayHandle_t ulOverlayHandle, ರಚನೆ HmdVector2_t * pvCursor);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *ClearOverlayCursorPositionOverride)(VROverlayHandle_t ulOverlayHandle);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *ಗಣ_Overlay_Texture)(VROverlayHandle_t ulOverlayHandle, ರಚನೆ Texture_t * pTexture);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *ClearOverlayTexture)(VROverlayHandle_t ulOverlayHandle);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *ಗಣ_Overlay_Raw)(VROverlayHandle_t ulOverlayHandle, ಶೂನ್ಯ * pv_ಬಫರ್, uint32_t un_ಅಗಲ, uint32_t un_ಎತ್ತರ, uint32_t un_ಬೈಟುಗಳು_ಪ್ರತಿ_Pixel);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *ಗಣ_Overlay_From_File)(VROverlayHandle_t ulOverlayHandle, ಅಕ್ಷರ * pch_File_ಮಾರ್ಗ);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetOverlayTexture)(VROverlayHandle_t ulOverlayHandle, ಶೂನ್ಯ ** pNativeTextureHandle, ಶೂನ್ಯ * pNativeTextureRef, uint32_t * p_ಅಗಲ, uint32_t * p_ಎತ್ತರ, uint32_t * pNativeFormat, ETextureType * pAPIType, EColorSpace * pColorSpace, ರಚನೆ VRTextureBounds_t * pTextureBounds);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *ReleaseNativeOverlayHandle)(VROverlayHandle_t ulOverlayHandle, ಶೂನ್ಯ * pNativeTextureHandle);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *Get_Overlay_Texture_ಗಾತ್ರ)(VROverlayHandle_t ulOverlayHandle, uint32_t * p_ಅಗಲ, uint32_t * p_ಎತ್ತರ);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *CreateDashboardOverlay)(ಅಕ್ಷರ * pch_Overlay_ಕೀಲಿ, ಅಕ್ಷರ * pchOverlayFriendlyName, VROverlayHandle_t * pMainHandle, VROverlayHandle_t * pThumbnailHandle);
	bool (OPENVR_FNTABLE_CALLTYPE *IsDashboardVisible)();
	bool (OPENVR_FNTABLE_CALLTYPE *Is_ಸಕ್ರಿಯ_Dashboard_Overlay)(VROverlayHandle_t ulOverlayHandle);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *ಗಣ_Dashboard_Overlay_Scene_Process)(VROverlayHandle_t ulOverlayHandle, uint32_t unProcessId);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *GetDashboardOverlaySceneProcess)(VROverlayHandle_t ulOverlayHandle, uint32_t * punProcessId);
	ಶೂನ್ಯ (OPENVR_FNTABLE_CALLTYPE *ShowDashboard)(ಅಕ್ಷರ * pch_Overlay_ಗಮ್ಯ_Show);
	Tracked_Device_ಸೂಚ್ಯಂಕ_t (OPENVR_FNTABLE_CALLTYPE *GetPrimaryDashboardDevice)();
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *ShowKeyboard)(EGamepad_ಪಠ್ಯ_ಒಳಹರಿವು_ಬಹುಲಕ e_ಒಳಹರಿವು_ಬಹುಲಕ, EGamepad_ಪಠ್ಯ_ಒಳಹರಿವು_ಸಾಲು_ಬಹುಲಕ e_ಸಾಲು_ಒಳಹರಿವು_ಬಹುಲಕ, uint32_t unFlags, ಅಕ್ಷರ * pchDescription, uint32_t unCharMax, ಅಕ್ಷರ * pch_Existing_ಪಠ್ಯ, uint64_t u_User_ಮೌಲ್ಯ);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *ShowKeyboardForOverlay)(VROverlayHandle_t ulOverlayHandle, EGamepad_ಪಠ್ಯ_ಒಳಹರಿವು_ಬಹುಲಕ e_ಒಳಹರಿವು_ಬಹುಲಕ, EGamepad_ಪಠ್ಯ_ಒಳಹರಿವು_ಸಾಲು_ಬಹುಲಕ e_ಸಾಲು_ಒಳಹರಿವು_ಬಹುಲಕ, uint32_t unFlags, ಅಕ್ಷರ * pchDescription, uint32_t unCharMax, ಅಕ್ಷರ * pch_Existing_ಪಠ್ಯ, uint64_t u_User_ಮೌಲ್ಯ);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *Get_Keyboard_ಪಠ್ಯ)(ಅಕ್ಷರ * pch_ಪಠ್ಯ, uint32_t cch_ಪಠ್ಯ);
	ಶೂನ್ಯ (OPENVR_FNTABLE_CALLTYPE *HideKeyboard)();
	ಶೂನ್ಯ (OPENVR_FNTABLE_CALLTYPE *ಗಣ_Keyboard_Transform_Absolute)(ETrackingUniverseOrigin eTrackingOrigin, ರಚನೆ HmdMatrix34_t * pmat_Tracking_Origin_ಗಮ್ಯ_Keyboard_Transform);
	ಶೂನ್ಯ (OPENVR_FNTABLE_CALLTYPE *ಗಣ_Keyboard_Position_For_Overlay)(VROverlayHandle_t ulOverlayHandle, ರಚನೆ HmdRect2_t avoidRect);
	VRMessageOverlayResponse (OPENVR_FNTABLE_CALLTYPE *Show_ಸಂದೇಶ_Overlay)(ಅಕ್ಷರ * pch_ಪಠ್ಯ, ಅಕ್ಷರ * pchCaption, ಅಕ್ಷರ * pch_Button0_ಪಠ್ಯ, ಅಕ್ಷರ * pch_Button1_ಪಠ್ಯ, ಅಕ್ಷರ * pch_Button2_ಪಠ್ಯ, ಅಕ್ಷರ * pch_Button3_ಪಠ್ಯ);
	ಶೂನ್ಯ (OPENVR_FNTABLE_CALLTYPE *Close_ಸಂದೇಶ_Overlay)();
};

ರಚನೆ VR_IVROverlay_View_Fn_ಕೋಷ್ಟಕ
{
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *AcquireOverlayView)(VROverlayHandle_t ulOverlayHandle, ರಚನೆ VRNativeDevice_t * pNativeDevice, ರಚನೆ VROverlayView_t * pOverlayView, uint32_t un_Overlay_View_ಗಾತ್ರ);
	EVROverlayError (OPENVR_FNTABLE_CALLTYPE *ReleaseOverlayView)(ರಚನೆ VROverlayView_t * pOverlayView);
	ಶೂನ್ಯ (OPENVR_FNTABLE_CALLTYPE *PostOverlayEvent)(VROverlayHandle_t ulOverlayHandle, ರಚನೆ VREvent_t * pvrEvent);
	bool (OPENVR_FNTABLE_CALLTYPE *IsViewingPermitted)(VROverlayHandle_t ulOverlayHandle);
};

ರಚನೆ VR_IVRHeadset_View_Fn_ಕೋಷ್ಟಕ
{
	ಶೂನ್ಯ (OPENVR_FNTABLE_CALLTYPE *ಗಣ_Headset_View_ಗಾತ್ರ)(uint32_t n_ಅಗಲ, uint32_t n_ಎತ್ತರ);
	ಶೂನ್ಯ (OPENVR_FNTABLE_CALLTYPE *Get_Headset_View_ಗಾತ್ರ)(uint32_t * pn_ಅಗಲ, uint32_t * pn_ಎತ್ತರ);
	ಶೂನ್ಯ (OPENVR_FNTABLE_CALLTYPE *ಗಣ_Headset_View_ಬಹುಲಕ)(Headset_View_ಬಹುಲಕ_t e_Headset_View_ಬಹುಲಕ);
	Headset_View_ಬಹುಲಕ_t (OPENVR_FNTABLE_CALLTYPE *Get_Headset_View_ಬಹುಲಕ)();
	ಶೂನ್ಯ (OPENVR_FNTABLE_CALLTYPE *ಗಣ_Headset_View_Cropped)(bool bCropped);
	bool (OPENVR_FNTABLE_CALLTYPE *GetHeadsetViewCropped)();
	ದಶಮಾಂಶ (OPENVR_FNTABLE_CALLTYPE *Get_Headset_View_Aspect_ಅನುಪಾತ)();
	ಶೂನ್ಯ (OPENVR_FNTABLE_CALLTYPE *ಗಣ_Headset_View_Blend_Range)(ದಶಮಾಂಶ fl_ಆರಂಭ_Pct, ದಶಮಾಂಶ fl_ಕೊನೆ_Pct);
	ಶೂನ್ಯ (OPENVR_FNTABLE_CALLTYPE *GetHeadsetViewBlendRange)(ದಶಮಾಂಶ * p_ಆರಂಭ_Pct, ದಶಮಾಂಶ * p_ಕೊನೆ_Pct);
};

ರಚನೆ VR_IVRRender_Models_Fn_ಕೋಷ್ಟಕ
{
	EVRRenderModelError (OPENVR_FNTABLE_CALLTYPE *ತುಂಬು_Render_Model_Async)(ಅಕ್ಷರ * pchRenderModelName, ರಚನೆ RenderModel_t ** ppRenderModel);
	ಶೂನ್ಯ (OPENVR_FNTABLE_CALLTYPE *FreeRenderModel)(ರಚನೆ RenderModel_t * pRenderModel);
	EVRRenderModelError (OPENVR_FNTABLE_CALLTYPE *ತುಂಬು_Texture_Async)(TextureID_t textureId, ರಚನೆ RenderModel_TextureMap_t ** ppTexture);
	ಶೂನ್ಯ (OPENVR_FNTABLE_CALLTYPE *FreeTexture)(ರಚನೆ RenderModel_TextureMap_t * pTexture);
	EVRRenderModelError (OPENVR_FNTABLE_CALLTYPE *ತುಂಬು_Texture_D3_D11_Async)(TextureID_t textureId, ಶೂನ್ಯ * pD3D11Device, ಶೂನ್ಯ ** ppD3D11Texture2D);
	EVRRenderModelError (OPENVR_FNTABLE_CALLTYPE *ತುಂಬು_Into_Texture_D3_D11_Async)(TextureID_t textureId, ಶೂನ್ಯ * pDstTexture);
	ಶೂನ್ಯ (OPENVR_FNTABLE_CALLTYPE *FreeTextureD3D11)(ಶೂನ್ಯ * pD3D11Texture2D);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetRenderModelName)(uint32_t un_Render_Model_ಸೂಚ್ಯಂಕ, ಅಕ್ಷರ * pchRenderModelName, uint32_t unRenderModelNameLen);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *Get_Render_Model_ಎಣಿಕೆ)();
	uint32_t (OPENVR_FNTABLE_CALLTYPE *Get_Component_ಎಣಿಕೆ)(ಅಕ್ಷರ * pchRenderModelName);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetComponentName)(ಅಕ್ಷರ * pchRenderModelName, uint32_t un_Component_ಸೂಚ್ಯಂಕ, ಅಕ್ಷರ * pchComponentName, uint32_t unComponentNameLen);
	uint64_t (OPENVR_FNTABLE_CALLTYPE *Get_Component_Button_ಮುಖವಾಡ)(ಅಕ್ಷರ * pchRenderModelName, ಅಕ್ಷರ * pchComponentName);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetComponentRenderModelName)(ಅಕ್ಷರ * pchRenderModelName, ಅಕ್ಷರ * pchComponentName, ಅಕ್ಷರ * pchComponentRenderModelName, uint32_t unComponentRenderModelNameLen);
	bool (OPENVR_FNTABLE_CALLTYPE *Get_Component_State_For_Device_ಮಾರ್ಗ)(ಅಕ್ಷರ * pchRenderModelName, ಅಕ್ಷರ * pchComponentName, VRInput_ಮೌಲ್ಯ_Handle_t device_ಮಾರ್ಗ, Render_Model_Controller_ಬಹುಲಕ_State_t * pState, RenderModel_ComponentState_t * pComponentState);
	bool (OPENVR_FNTABLE_CALLTYPE *GetComponentState)(ಅಕ್ಷರ * pchRenderModelName, ಅಕ್ಷರ * pchComponentName, VRControllerState_t * pControllerState, ರಚನೆ Render_Model_Controller_ಬಹುಲಕ_State_t * pState, ರಚನೆ RenderModel_ComponentState_t * pComponentState);
	bool (OPENVR_FNTABLE_CALLTYPE *RenderModelHasComponent)(ಅಕ್ಷರ * pchRenderModelName, ಅಕ್ಷರ * pchComponentName);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetRenderModelThumbnailURL)(ಅಕ್ಷರ * pchRenderModelName, ಅಕ್ಷರ * pchThumbnailURL, uint32_t unThumbnailURLLen, EVRRenderModelError * peError);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *Get_Render_Model_Original_ಮಾರ್ಗ)(ಅಕ್ಷರ * pchRenderModelName, ಅಕ್ಷರ * pch_Original_ಮಾರ್ಗ, uint32_t un_Original_ಮಾರ್ಗ_Len, EVRRenderModelError * peError);
	ಅಕ್ಷರ * (OPENVR_FNTABLE_CALLTYPE *GetRenderModelErrorNameFromEnum)(EVRRenderModelError error);
};

ರಚನೆ VR_IVRNotifications_Fn_ಕೋಷ್ಟಕ
{
	EVRNotificationError (OPENVR_FNTABLE_CALLTYPE *CreateNotification)(VROverlayHandle_t ulOverlayHandle, uint64_t ul_User_ಮೌಲ್ಯ, EVRNotificationType type, ಅಕ್ಷರ * pch_ಪಠ್ಯ, EVRNotificationStyle style, ರಚನೆ NotificationBitmap_t * pImage, VRNotificationId * pNotificationId);
	EVRNotificationError (OPENVR_FNTABLE_CALLTYPE *RemoveNotification)(VRNotificationId notificationId);
};

ರಚನೆ VR_IVRSettings_Fn_ಕೋಷ್ಟಕ
{
	ಅಕ್ಷರ * (OPENVR_FNTABLE_CALLTYPE *GetSettingsErrorNameFromEnum)(EVRSettingsError eError);
	ಶೂನ್ಯ (OPENVR_FNTABLE_CALLTYPE *ಗಣ_Bool)(ಅಕ್ಷರ * pchSection, ಅಕ್ಷರ * pch_Settings_ಕೀಲಿ, bool b_ಮೌಲ್ಯ, EVRSettingsError * peError);
	ಶೂನ್ಯ (OPENVR_FNTABLE_CALLTYPE *ಗಣ_Int32)(ಅಕ್ಷರ * pchSection, ಅಕ್ಷರ * pch_Settings_ಕೀಲಿ, int32_t n_ಮೌಲ್ಯ, EVRSettingsError * peError);
	ಶೂನ್ಯ (OPENVR_FNTABLE_CALLTYPE *ಗಣ_Float)(ಅಕ್ಷರ * pchSection, ಅಕ್ಷರ * pch_Settings_ಕೀಲಿ, ದಶಮಾಂಶ fl_ಮೌಲ್ಯ, EVRSettingsError * peError);
	ಶೂನ್ಯ (OPENVR_FNTABLE_CALLTYPE *ಗಣ_String)(ಅಕ್ಷರ * pchSection, ಅಕ್ಷರ * pch_Settings_ಕೀಲಿ, ಅಕ್ಷರ * pch_ಮೌಲ್ಯ, EVRSettingsError * peError);
	bool (OPENVR_FNTABLE_CALLTYPE *GetBool)(ಅಕ್ಷರ * pchSection, ಅಕ್ಷರ * pch_Settings_ಕೀಲಿ, EVRSettingsError * peError);
	int32_t (OPENVR_FNTABLE_CALLTYPE *GetInt32)(ಅಕ್ಷರ * pchSection, ಅಕ್ಷರ * pch_Settings_ಕೀಲಿ, EVRSettingsError * peError);
	ದಶಮಾಂಶ (OPENVR_FNTABLE_CALLTYPE *GetFloat)(ಅಕ್ಷರ * pchSection, ಅಕ್ಷರ * pch_Settings_ಕೀಲಿ, EVRSettingsError * peError);
	ಶೂನ್ಯ (OPENVR_FNTABLE_CALLTYPE *GetString)(ಅಕ್ಷರ * pchSection, ಅಕ್ಷರ * pch_Settings_ಕೀಲಿ, ಅಕ್ಷರ * pch_ಮೌಲ್ಯ, uint32_t un_ಮೌಲ್ಯ_Len, EVRSettingsError * peError);
	ಶೂನ್ಯ (OPENVR_FNTABLE_CALLTYPE *RemoveSection)(ಅಕ್ಷರ * pchSection, EVRSettingsError * peError);
	ಶೂನ್ಯ (OPENVR_FNTABLE_CALLTYPE *Remove_ಕೀಲಿ_ಒಳ_Section)(ಅಕ್ಷರ * pchSection, ಅಕ್ಷರ * pch_Settings_ಕೀಲಿ, EVRSettingsError * peError);
};

ರಚನೆ VR_IVRScreenshots_Fn_ಕೋಷ್ಟಕ
{
	EVRScreenshotError (OPENVR_FNTABLE_CALLTYPE *RequestScreenshot)(ScreenshotHandle_t * p_ಹೊರಹೋಗು_Screenshot_Handle, EVRScreenshotType type, ಅಕ್ಷರ * pchPreviewFilename, ಅಕ್ಷರ * pchVRFilename);
	EVRScreenshotError (OPENVR_FNTABLE_CALLTYPE *HookScreenshot)(EVRScreenshotType * pSupportedTypes, ಪೂರ್ಣಾಂಕ ಅಂಕೆ_Types);
	EVRScreenshotType (OPENVR_FNTABLE_CALLTYPE *GetScreenshotPropertyType)(ScreenshotHandle_t screenshotHandle, EVRScreenshotError * pError);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetScreenshotPropertyFilename)(ScreenshotHandle_t screenshotHandle, EVRScreenshotPropertyFilenames filenameType, ಅಕ್ಷರ * pchFilename, uint32_t cchFilename, EVRScreenshotError * pError);
	EVRScreenshotError (OPENVR_FNTABLE_CALLTYPE *Update_Screenshot_ಪ್ರಗತಿ)(ScreenshotHandle_t screenshotHandle, ದಶಮಾಂಶ fl_ಪ್ರಗತಿ);
	EVRScreenshotError (OPENVR_FNTABLE_CALLTYPE *TakeStereoScreenshot)(ScreenshotHandle_t * p_ಹೊರಹೋಗು_Screenshot_Handle, ಅಕ್ಷರ * pchPreviewFilename, ಅಕ್ಷರ * pchVRFilename);
	EVRScreenshotError (OPENVR_FNTABLE_CALLTYPE *SubmitScreenshot)(ScreenshotHandle_t screenshotHandle, EVRScreenshotType type, ಅಕ್ಷರ * pch_ಮೂಲ_Preview_Filename, ಅಕ್ಷರ * pch_ಮೂಲ_VRFilename);
};

ರಚನೆ VR_IVRResources_Fn_ಕೋಷ್ಟಕ
{
	uint32_t (OPENVR_FNTABLE_CALLTYPE *ತುಂಬು_Shared_Resource)(ಅಕ್ಷರ * pchResourceName, ಅಕ್ಷರ * pch_ಬಫರ್, uint32_t un_ಬಫರ್_Len);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *Get_Resource_ತುಂಬಿದ_ಮಾರ್ಗ)(ಅಕ್ಷರ * pchResourceName, ಅಕ್ಷರ * pchResourceTypeDirectory, ಅಕ್ಷರ * pch_ಮಾರ್ಗ_ಬಫರ್, uint32_t un_ಬಫರ್_Len);
};

ರಚನೆ VR_IVRDriver_Manager_Fn_ಕೋಷ್ಟಕ
{
	uint32_t (OPENVR_FNTABLE_CALLTYPE *Get_Driver_ಎಣಿಕೆ)();
	uint32_t (OPENVR_FNTABLE_CALLTYPE *GetDriverName)(DriverId_t nDriver, ಅಕ್ಷರ * pch_ಮೌಲ್ಯ, uint32_t un_ಬಫರ್_ಗಾತ್ರ);
	DriverHandle_t (OPENVR_FNTABLE_CALLTYPE *GetDriverHandle)(ಅಕ್ಷರ * pchDriverName);
	bool (OPENVR_FNTABLE_CALLTYPE *IsEnabled)(DriverId_t nDriver);
};

ರಚನೆ VR_IVRInput_Fn_ಕೋಷ್ಟಕ
{
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *ಗಣ_Action_Manifest_ಮಾರ್ಗ)(ಅಕ್ಷರ * pch_Action_Manifest_ಮಾರ್ಗ);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *Get_Action_ಗಣ_Handle)(ಅಕ್ಷರ * pch_Action_ಗಣ_Name, VRAction_ಗಣ_Handle_t * pHandle);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetActionHandle)(ಅಕ್ಷರ * pchActionName, VRActionHandle_t * pHandle);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *Get_ಒಳಹರಿವು_ಮೂಲ_Handle)(ಅಕ್ಷರ * pch_ಒಳಹರಿವು_ಮೂಲ_ಮಾರ್ಗ, VRInput_ಮೌಲ್ಯ_Handle_t * pHandle);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *UpdateActionState)(ರಚನೆ VRActive_Action_ಗಣ_t * pSets, uint32_t un_ಗಾತ್ರ_ದ_VRSelected_Action_ಗಣ_t, uint32_t un_ಗಣ_ಎಣಿಕೆ);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *Get_Digital_Action_ದತ್ತಾಂಶ)(VRActionHandle_t action, ರಚನೆ ಒಳಹರಿವು_Digital_Action_ದತ್ತಾಂಶ_t * p_Action_ದತ್ತಾಂಶ, uint32_t un_Action_ದತ್ತಾಂಶ_ಗಾತ್ರ, VRInput_ಮೌಲ್ಯ_Handle_t ul_Restrict_ಗಮ್ಯ_Device);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *Get_Analog_Action_ದತ್ತಾಂಶ)(VRActionHandle_t action, ರಚನೆ ಒಳಹರಿವು_Analog_Action_ದತ್ತಾಂಶ_t * p_Action_ದತ್ತಾಂಶ, uint32_t un_Action_ದತ್ತಾಂಶ_ಗಾತ್ರ, VRInput_ಮೌಲ್ಯ_Handle_t ul_Restrict_ಗಮ್ಯ_Device);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *Get_Pose_Action_ದತ್ತಾಂಶ_Relative_ಗಮ್ಯ_Now)(VRActionHandle_t action, ETrackingUniverseOrigin eOrigin, ದಶಮಾಂಶ fPredictedSecondsFromNow, ರಚನೆ ಒಳಹರಿವು_Pose_Action_ದತ್ತಾಂಶ_t * p_Action_ದತ್ತಾಂಶ, uint32_t un_Action_ದತ್ತಾಂಶ_ಗಾತ್ರ, VRInput_ಮೌಲ್ಯ_Handle_t ul_Restrict_ಗಮ್ಯ_Device);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *Get_Pose_Action_ದತ್ತಾಂಶ_For_ಮುಂದಿನ_ಚೌಕಟ್ಟು)(VRActionHandle_t action, ETrackingUniverseOrigin eOrigin, ರಚನೆ ಒಳಹರಿವು_Pose_Action_ದತ್ತಾಂಶ_t * p_Action_ದತ್ತಾಂಶ, uint32_t un_Action_ದತ್ತಾಂಶ_ಗಾತ್ರ, VRInput_ಮೌಲ್ಯ_Handle_t ul_Restrict_ಗಮ್ಯ_Device);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *Get_Skeletal_Action_ದತ್ತಾಂಶ)(VRActionHandle_t action, ರಚನೆ ಒಳಹರಿವು_Skeletal_Action_ದತ್ತಾಂಶ_t * p_Action_ದತ್ತಾಂಶ, uint32_t un_Action_ದತ್ತಾಂಶ_ಗಾತ್ರ);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetDominantHand)(ETrackedControllerRole * peDominantHand);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *ಗಣ_Dominant_Hand)(ETrackedControllerRole eDominantHand);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *Get_Bone_ಎಣಿಕೆ)(VRActionHandle_t action, uint32_t * p_Bone_ಎಣಿಕೆ);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetBoneHierarchy)(VRActionHandle_t action, Bone_ಸೂಚ್ಯಂಕ_t * p_ಪೋಷಕ_Indices, uint32_t un_ಸೂಚ್ಯಂಕ_Aray_ಎಣಿಕೆ);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetBoneName)(VRActionHandle_t action, Bone_ಸೂಚ್ಯಂಕ_t n_Bone_ಸೂಚ್ಯಂಕ, ಅಕ್ಷರ * pchBoneName, uint32_t un_Name_ಬಫರ್_ಗಾತ್ರ);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetSkeletalReferenceTransforms)(VRActionHandle_t action, EVRSkeletalTransformSpace eTransformSpace, EVRSkeletalReferencePose eReferencePose, ರಚನೆ VRBoneTransform_t * pTransformArray, uint32_t un_Transform_Array_ಎಣಿಕೆ);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetSkeletalTrackingLevel)(VRActionHandle_t action, EVRSkeletalTrackingLevel * pSkeletalTrackingLevel);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *Get_Skeletal_Bone_ದತ್ತಾಂಶ)(VRActionHandle_t action, EVRSkeletalTransformSpace eTransformSpace, EVRSkeletalMotionRange eMotionRange, ರಚನೆ VRBoneTransform_t * pTransformArray, uint32_t un_Transform_Array_ಎಣಿಕೆ);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *Get_Skeletal_Summary_ದತ್ತಾಂಶ)(VRActionHandle_t action, EVRSummaryType eSummaryType, ರಚನೆ VRSkeletal_Summary_ದತ್ತಾಂಶ_t * p_Skeletal_Summary_ದತ್ತಾಂಶ);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *Get_Skeletal_Bone_ದತ್ತಾಂಶ_Compressed)(VRActionHandle_t action, EVRSkeletalMotionRange eMotionRange, ಶೂನ್ಯ * pv_Compressed_ದತ್ತಾಂಶ, uint32_t un_Compressed_ಗಾತ್ರ, uint32_t * pun_Required_Compressed_ಗಾತ್ರ);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *Decompress_Skeletal_Bone_ದತ್ತಾಂಶ)(ಶೂನ್ಯ * pv_Compressed_ಬಫರ್, uint32_t un_Compressed_ಬಫರ್_ಗಾತ್ರ, EVRSkeletalTransformSpace eTransformSpace, ರಚನೆ VRBoneTransform_t * pTransformArray, uint32_t un_Transform_Array_ಎಣಿಕೆ);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *TriggerHapticVibrationAction)(VRActionHandle_t action, ದಶಮಾಂಶ f_ಆರಂಭ_Seconds_From_Now, ದಶಮಾಂಶ fDurationSeconds, ದಶಮಾಂಶ fFrequency, ದಶಮಾಂಶ fAmplitude, VRInput_ಮೌಲ್ಯ_Handle_t ul_Restrict_ಗಮ್ಯ_Device);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetActionOrigins)(VRAction_ಗಣ_Handle_t action_ಗಣ_Handle, VRActionHandle_t digitalActionHandle, VRInput_ಮೌಲ್ಯ_Handle_t * origins_ಹೊರಹೋಗು, uint32_t origin_ಹೊರಹೋಗು_ಎಣಿಕೆ);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetOriginLocalizedName)(VRInput_ಮೌಲ್ಯ_Handle_t origin, ಅಕ್ಷರ * pchNameArray, uint32_t un_Name_Array_ಗಾತ್ರ, int32_t un_String_Sections_ಗಮ್ಯ_Include);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetOriginTrackedDeviceInfo)(VRInput_ಮೌಲ್ಯ_Handle_t origin, ರಚನೆ ಒಳಹರಿವು_Origin_Info_t * pOriginInfo, uint32_t un_Origin_Info_ಗಾತ್ರ);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetActionBindingInfo)(VRActionHandle_t action, ರಚನೆ ಒಳಹರಿವು_Binding_Info_t * pOriginInfo, uint32_t un_Binding_Info_ಗಾತ್ರ, uint32_t un_Binding_Info_ಎಣಿಕೆ, uint32_t * pun_Returned_Binding_Info_ಎಣಿಕೆ);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *ShowActionOrigins)(VRAction_ಗಣ_Handle_t action_ಗಣ_Handle, VRActionHandle_t ulActionHandle);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *Show_Bindings_For_Action_ಗಣ)(ರಚನೆ VRActive_Action_ಗಣ_t * pSets, uint32_t un_ಗಾತ್ರ_ದ_VRSelected_Action_ಗಣ_t, uint32_t un_ಗಣ_ಎಣಿಕೆ, VRInput_ಮೌಲ್ಯ_Handle_t origin_ಗಮ್ಯ_Highlight);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetComponentStateForBinding)(ಅಕ್ಷರ * pchRenderModelName, ಅಕ್ಷರ * pchComponentName, ರಚನೆ ಒಳಹರಿವು_Binding_Info_t * pOriginInfo, uint32_t un_Binding_Info_ಗಾತ್ರ, uint32_t un_Binding_Info_ಎಣಿಕೆ, RenderModel_ComponentState_t * pComponentState);
	bool (OPENVR_FNTABLE_CALLTYPE *Is_Using_Legacy_ಒಳಹರಿವು)();
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *OpenBindingUI)(ಅಕ್ಷರ * pch_App_ಕೀಲಿ, VRAction_ಗಣ_Handle_t ul_Action_ಗಣ_Handle, VRInput_ಮೌಲ್ಯ_Handle_t ulDeviceHandle, bool bShowOnDesktop);
	EVRInputError (OPENVR_FNTABLE_CALLTYPE *GetBindingVariant)(VRInput_ಮೌಲ್ಯ_Handle_t ul_Device_ಮಾರ್ಗ, ಅಕ್ಷರ * pchVariantArray, uint32_t un_Variant_Array_ಗಾತ್ರ);
};

ರಚನೆ VR_IVRIOBuffer_Fn_ಕೋಷ್ಟಕ
{
	EIOBufferError (OPENVR_FNTABLE_CALLTYPE *Open)(ಅಕ್ಷರ * pch_ಮಾರ್ಗ, EIOBuffer_ಬಹುಲಕ ಬಹುಲಕ, uint32_t un_Element_ಗಾತ್ರ, uint32_t unElements, IOBufferHandle_t * pul_ಬಫರ್);
	EIOBufferError (OPENVR_FNTABLE_CALLTYPE *Close)(IOBufferHandle_t ul_ಬಫರ್);
	EIOBufferError (OPENVR_FNTABLE_CALLTYPE *Read)(IOBufferHandle_t ul_ಬಫರ್, ಶೂನ್ಯ * pDst, uint32_t un_ಬೈಟುಗಳು, uint32_t * punRead);
	EIOBufferError (OPENVR_FNTABLE_CALLTYPE *Write)(IOBufferHandle_t ul_ಬಫರ್, ಶೂನ್ಯ * pSrc, uint32_t un_ಬೈಟುಗಳು);
	PropertyContainerHandle_t (OPENVR_FNTABLE_CALLTYPE *PropertyContainer)(IOBufferHandle_t ul_ಬಫರ್);
	bool (OPENVR_FNTABLE_CALLTYPE *HasReaders)(IOBufferHandle_t ul_ಬಫರ್);
};

ರಚನೆ VR_IVRSpatial_Anchors_Fn_ಕೋಷ್ಟಕ
{
	EVRSpatialAnchorError (OPENVR_FNTABLE_CALLTYPE *CreateSpatialAnchorFromDescriptor)(ಅಕ್ಷರ * pchDescriptor, SpatialAnchorHandle_t * p_Handle_ಹೊರಹೋಗು);
	EVRSpatialAnchorError (OPENVR_FNTABLE_CALLTYPE *CreateSpatialAnchorFromPose)(Tracked_Device_ಸೂಚ್ಯಂಕ_t un_Device_ಸೂಚ್ಯಂಕ, ETrackingUniverseOrigin eOrigin, ರಚನೆ SpatialAnchorPose_t * pPose, SpatialAnchorHandle_t * p_Handle_ಹೊರಹೋಗು);
	EVRSpatialAnchorError (OPENVR_FNTABLE_CALLTYPE *GetSpatialAnchorPose)(SpatialAnchorHandle_t unHandle, ETrackingUniverseOrigin eOrigin, ರಚನೆ SpatialAnchorPose_t * p_Pose_ಹೊರಹೋಗು);
	EVRSpatialAnchorError (OPENVR_FNTABLE_CALLTYPE *GetSpatialAnchorDescriptor)(SpatialAnchorHandle_t unHandle, ಅಕ್ಷರ * pch_Descriptor_ಹೊರಹೋಗು, uint32_t * pun_Descriptor_ಬಫರ್_Len_ಒಳ_ಹೊರಹೋಗು);
};

ರಚನೆ VR_IVRDebug_Fn_ಕೋಷ್ಟಕ
{
	EVRDebugError (OPENVR_FNTABLE_CALLTYPE *EmitVrProfilerEvent)(ಅಕ್ಷರ * pch_ಸಂದೇಶ);
	EVRDebugError (OPENVR_FNTABLE_CALLTYPE *BeginVrProfilerEvent)(VrProfilerEventHandle_t * p_Handle_ಹೊರಹೋಗು);
	EVRDebugError (OPENVR_FNTABLE_CALLTYPE *ಮುಕ್ತಾಯ_Vr_Profiler_Event)(VrProfilerEventHandle_t hHandle, ಅಕ್ಷರ * pch_ಸಂದೇಶ);
	uint32_t (OPENVR_FNTABLE_CALLTYPE *DriverDebugRequest)(Tracked_Device_ಸೂಚ್ಯಂಕ_t un_Device_ಸೂಚ್ಯಂಕ, ಅಕ್ಷರ * pchRequest, ಅಕ್ಷರ * pch_Response_ಬಫರ್, uint32_t un_Response_ಬಫರ್_ಗಾತ್ರ);
};

ರಚನೆ VR_IVRProperties_Fn_ಕೋಷ್ಟಕ
{
	ETrackedPropertyError (OPENVR_FNTABLE_CALLTYPE *ReadPropertyBatch)(PropertyContainerHandle_t ulContainerHandle, ರಚನೆ PropertyRead_t * pBatch, uint32_t un_Batch_ನಮೂದು_ಎಣಿಕೆ);
	ETrackedPropertyError (OPENVR_FNTABLE_CALLTYPE *WritePropertyBatch)(PropertyContainerHandle_t ulContainerHandle, ರಚನೆ PropertyWrite_t * pBatch, uint32_t un_Batch_ನಮೂದು_ಎಣಿಕೆ);
	ಅಕ್ಷರ * (OPENVR_FNTABLE_CALLTYPE *GetPropErrorNameFromEnum)(ETrackedPropertyError error);
	PropertyContainerHandle_t (OPENVR_FNTABLE_CALLTYPE *Tracked_Device_ಗಮ್ಯ_Property_Container)(Tracked_Device_ಸೂಚ್ಯಂಕ_t nDevice);
};

ರಚನೆ VR_IVRPaths_Fn_ಕೋಷ್ಟಕ
{
	ETrackedPropertyError (OPENVR_FNTABLE_CALLTYPE *Read_ಮಾರ್ಗ_Batch)(PropertyContainerHandle_t ul_ಬೇರು_Handle, ರಚನೆ ಮಾರ್ಗ_Read_t * pBatch, uint32_t un_Batch_ನಮೂದು_ಎಣಿಕೆ);
	ETrackedPropertyError (OPENVR_FNTABLE_CALLTYPE *Write_ಮಾರ್ಗ_Batch)(PropertyContainerHandle_t ul_ಬೇರು_Handle, ರಚನೆ ಮಾರ್ಗ_Write_t * pBatch, uint32_t un_Batch_ನಮೂದು_ಎಣಿಕೆ);
	ETrackedPropertyError (OPENVR_FNTABLE_CALLTYPE *String_ಗಮ್ಯ_Handle)(ಮಾರ್ಗ_Handle_t * pHandle, ಅಕ್ಷರ * pch_ಮಾರ್ಗ);
	ETrackedPropertyError (OPENVR_FNTABLE_CALLTYPE *Handle_ಗಮ್ಯ_String)(ಮಾರ್ಗ_Handle_t pHandle, ಅಕ್ಷರ * pch_ಬಫರ್, uint32_t un_ಬಫರ್_ಗಾತ್ರ, uint32_t * pun_ಬಫರ್_ಗಾತ್ರ_ಬಳಸಿದ);
};

ರಚನೆ VR_IVRBlock_ಸರತಿ_Fn_ಕೋಷ್ಟಕ
{
	EBlock_ಸರತಿ_Error (OPENVR_FNTABLE_CALLTYPE *Create)(PropertyContainerHandle_t * pul_ಸರತಿ_Handle, ಅಕ್ಷರ * pch_ಮಾರ್ಗ, uint32_t un_ಖಂಡ_ದತ್ತಾಂಶ_ಗಾತ್ರ, uint32_t un_ಖಂಡ_ಶೀರ್ಷಿಕೆ_ಗಾತ್ರ, uint32_t un_ಖಂಡ_ಎಣಿಕೆ, uint32_t unFlags);
	EBlock_ಸರತಿ_Error (OPENVR_FNTABLE_CALLTYPE *Connect)(PropertyContainerHandle_t * pul_ಸರತಿ_Handle, ಅಕ್ಷರ * pch_ಮಾರ್ಗ);
	EBlock_ಸರತಿ_Error (OPENVR_FNTABLE_CALLTYPE *Destroy)(PropertyContainerHandle_t ul_ಸರತಿ_Handle);
	EBlock_ಸರತಿ_Error (OPENVR_FNTABLE_CALLTYPE *Acquire_Write_Only_ಖಂಡ)(PropertyContainerHandle_t ul_ಸರತಿ_Handle, PropertyContainerHandle_t * pul_ಖಂಡ_Handle, ಶೂನ್ಯ ** ppv_ಬಫರ್);
	EBlock_ಸರತಿ_Error (OPENVR_FNTABLE_CALLTYPE *Release_Write_Only_ಖಂಡ)(PropertyContainerHandle_t ul_ಸರತಿ_Handle, PropertyContainerHandle_t ul_ಖಂಡ_Handle);
	EBlock_ಸರತಿ_Error (OPENVR_FNTABLE_CALLTYPE *Wait_And_Acquire_Read_Only_ಖಂಡ)(PropertyContainerHandle_t ul_ಸರತಿ_Handle, PropertyContainerHandle_t * pul_ಖಂಡ_Handle, ಶೂನ್ಯ ** ppv_ಬಫರ್, EBlock_ಸರತಿ_Read_Type eReadType, uint32_t unTimeoutMs);
	EBlock_ಸರತಿ_Error (OPENVR_FNTABLE_CALLTYPE *Acquire_Read_Only_ಖಂಡ)(PropertyContainerHandle_t ul_ಸರತಿ_Handle, PropertyContainerHandle_t * pul_ಖಂಡ_Handle, ಶೂನ್ಯ ** ppv_ಬಫರ್, EBlock_ಸರತಿ_Read_Type eReadType);
	EBlock_ಸರತಿ_Error (OPENVR_FNTABLE_CALLTYPE *Release_Read_Only_ಖಂಡ)(PropertyContainerHandle_t ul_ಸರತಿ_Handle, PropertyContainerHandle_t ul_ಖಂಡ_Handle);
	EBlock_ಸರತಿ_Error (OPENVR_FNTABLE_CALLTYPE *ಸರತಿ_Has_Reader)(PropertyContainerHandle_t ul_ಸರತಿ_Handle, bool * pbHasReaders);
};


#ಆದರೆ 0
// Global entry points
S_API intptr_t VR_Init_ಆಂತರಿಕ( EVRInitError *peError, EVRApplicationType eType );
S_API ಶೂನ್ಯ VR_Shutdown_ಆಂತರಿಕ();
S_API bool VR_IsHmdPresent();
S_API intptr_t VR_GetGenericInterface( ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *pch_Interface_ಆವೃತ್ತಿ, EVRInitError *peError );
S_API bool VR_IsRuntimeInstalled();
S_API ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * VR_Get_VRInit_Error_As_ಚಿಹ್ನೆ( EVRInitError error );
S_API ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * VR_GetVRInitErrorAsEnglishDescription( EVRInitError error );
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ_ಅಂತ್ಯ // __OPENVR_API_FLAT_H__


