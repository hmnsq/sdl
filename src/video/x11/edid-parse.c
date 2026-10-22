/*
 * Copyright 2007 Red Hat, Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * on the rights to use, copy, modify, merge, publish, distribute, sub
 * license, and/or sell copies of the Software, and to permit persons to whom
 * the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/* Author: Soren Sandmann <sandmann@redhat.com> */
#ಅನ್ತರ್ಭಾವ "SDL_internal.h"

#ಅನ್ತರ್ಭಾವ "edid.h"
#ಅನ್ತರ್ಭಾವ <stdlib.h>
#ಅನ್ತರ್ಭಾವ <string.h>
#ಅನ್ತರ್ಭಾವ <math.h>
#ಅನ್ತರ್ಭಾವ <stdio.h>

#ವ್ಯಾಖ್ಯಾನಿಸು TRUE 1
#ವ್ಯಾಖ್ಯಾನಿಸು FALSE 0

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ
get_ಬಿಟ್ (ಪೂರ್ಣಾಂಕ ಒಳ_2, ಪೂರ್ಣಾಂಕ ಬಿಟ್)
{
    ಹಿಂತಿರುಗಿ (ಒಳ_2 & (1 << ಬಿಟ್)) >> ಬಿಟ್;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ
get_ಬಿಟ್ಟುಗಳು (ಪೂರ್ಣಾಂಕ ಒಳ_2, ಪೂರ್ಣಾಂಕ begin, ಪೂರ್ಣಾಂಕ ಕೊನೆ)
{
    ಪೂರ್ಣಾಂಕ ಮುಖವಾಡ = (1 << (ಕೊನೆ - begin + 1)) - 1;
    
    ಹಿಂತಿರುಗಿ (ಒಳ_2 >> begin) & ಮುಖವಾಡ;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ
decode_ಶೀರ್ಷಿಕೆ (ಸ್ಥಿರಾಂಕ uchar *edid)
{
    ಆದರೆ (SDL_memcmp (edid, "\x00\xff\xff\xff\xff\xff\xff\x00", 8) == 0)
	ಹಿಂತಿರುಗಿ TRUE;
    ಹಿಂತಿರುಗಿ FALSE;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ
decode_vendor_and_ಗುಣಲಬ್ಧ_identification (ಸ್ಥಿರಾಂಕ uchar *edid, MonitorInfo *info)
{
    ಪೂರ್ಣಾಂಕ is_model_year;
    
    /* Manufacturer Code */
    info->manufacturer_ಸಂಕೇತ[0]  = get_ಬಿಟ್ಟುಗಳು (edid[0x08], 2, 6);
    info->manufacturer_ಸಂಕೇತ[1]  = get_ಬಿಟ್ಟುಗಳು (edid[0x08], 0, 1) << 3;
    info->manufacturer_ಸಂಕೇತ[1] |= get_ಬಿಟ್ಟುಗಳು (edid[0x09], 5, 7);
    info->manufacturer_ಸಂಕೇತ[2]  = get_ಬಿಟ್ಟುಗಳು (edid[0x09], 0, 4);
    info->manufacturer_ಸಂಕೇತ[3]  = '\0';
    
    info->manufacturer_ಸಂಕೇತ[0] += 'A' - 1;
    info->manufacturer_ಸಂಕೇತ[1] += 'A' - 1;
    info->manufacturer_ಸಂಕೇತ[2] += 'A' - 1;

    /* Product Code */
    info->ಗುಣಲಬ್ಧ_ಸಂಕೇತ = edid[0x0b] << 8 | edid[0x0a];

    /* Serial Number */
    info->serial_ಸಂಖ್ಯೆ =
	edid[0x0c] | edid[0x0d] << 8 | edid[0x0e] << 16 | (Uint32)edid[0x0f] << 24;

    /* Week and Year */
    is_model_year = FALSE;
    ಆಯ್ಕೆ (edid[0x10])
    {
    ಸ್ಥಿತಿ 0x00:
	info->production_week = -1;
	ನಿಲ್ಲಿಸು;

    ಸ್ಥಿತಿ 0xff:
	info->production_week = -1;
	is_model_year = TRUE;
	ನಿಲ್ಲಿಸು;

    ಪೂರ್ವನಿಯೋಜಿತ:
	info->production_week = edid[0x10];
	ನಿಲ್ಲಿಸು;
    }

    ಆದರೆ (is_model_year)
    {
	info->production_year = -1;
	info->model_year = 1990 + edid[0x11];
    }
    ಇಲ್ಲದಿದ್ದರೆ
    {
	info->production_year = 1990 + edid[0x11];
	info->model_year = -1;
    }

    ಹಿಂತಿರುಗಿ TRUE;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ
decode_edid_ಆವೃತ್ತಿ (ಸ್ಥಿರಾಂಕ uchar *edid, MonitorInfo *info)
{
    info->major_ಆವೃತ್ತಿ = edid[0x12];
    info->minor_ಆವೃತ್ತಿ = edid[0x13];

    ಹಿಂತಿರುಗಿ TRUE;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ
decode_display_parameters (ಸ್ಥಿರಾಂಕ uchar *edid, MonitorInfo *info)
{
    /* Digital vs Analog */
    info->is_digital = get_ಬಿಟ್ (edid[0x14], 7);

    ಆದರೆ (info->is_digital)
    {
	ಪೂರ್ಣಾಂಕ ಬಿಟ್ಟುಗಳು;
	
	ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ ಬಿಟ್_ಆಳ_2[8] =
	{
	    -1, 6, 8, 10, 12, 14, 16, -1
	};

	ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ Interface interfaces[6] =
	{
	    UNDEFINED, DVI, HDMI_A, HDMI_B, MDDI, DISPLAY_ಪೋರ್ಟ್
	};

	ಬಿಟ್ಟುಗಳು = get_ಬಿಟ್ಟುಗಳು (edid[0x14], 4, 6);
	info->ad.digital.ಬಿಟ್ಟುಗಳು_ಪ್ರತಿ_primary = ಬಿಟ್_ಆಳ_2[ಬಿಟ್ಟುಗಳು];

	ಬಿಟ್ಟುಗಳು = get_ಬಿಟ್ಟುಗಳು (edid[0x14], 0, 3);
	
	ಆದರೆ (ಬಿಟ್ಟುಗಳು <= 5)
	    info->ad.digital.interface = interfaces[ಬಿಟ್ಟುಗಳು];
	ಇಲ್ಲದಿದ್ದರೆ
	    info->ad.digital.interface = UNDEFINED;
    }
    ಇಲ್ಲದಿದ್ದರೆ
    {
	ಪೂರ್ಣಾಂಕ ಬಿಟ್ಟುಗಳು = get_ಬಿಟ್ಟುಗಳು (edid[0x14], 5, 6);
	
	ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ದ್ವಿಗುಣ ಮಟ್ಟಗಳು[][3] =
	{
	    { 0.7,   0.3,    1.0 },
	    { 0.714, 0.286,  1.0 },
	    { 1.0,   0.4,    1.4 },
	    { 0.7,   0.0,    0.7 },
	};

	info->ad.analog.video_signal_level = ಮಟ್ಟಗಳು[ಬಿಟ್ಟುಗಳು][0];
	info->ad.analog.sync_signal_level = ಮಟ್ಟಗಳು[ಬಿಟ್ಟುಗಳು][1];
	info->ad.analog.ಒಟ್ಟು_signal_level = ಮಟ್ಟಗಳು[ಬಿಟ್ಟುಗಳು][2];

	info->ad.analog.blank_ಗಮ್ಯ_black = get_ಬಿಟ್ (edid[0x14], 4);

	info->ad.analog.separate_hv_sync = get_ಬಿಟ್ (edid[0x14], 3);
	info->ad.analog.ಸಂಯುಕ್ತ_sync_on_h = get_ಬಿಟ್ (edid[0x14], 2);
	info->ad.analog.ಸಂಯುಕ್ತ_sync_on_green = get_ಬಿಟ್ (edid[0x14], 1);

	info->ad.analog.serration_on_vsync = get_ಬಿಟ್ (edid[0x14], 0);
    }

    /* Screen Size / Aspect Ratio */
    ಆದರೆ (edid[0x15] == 0 && edid[0x16] == 0)
    {
	info->ಅಗಲ_mm = -1;
	info->ಎತ್ತರ_mm = -1;
	info->aspect_ಅನುಪಾತ = -1.0;
    }
    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (edid[0x16] == 0)
    {
	info->ಅಗಲ_mm = -1;
	info->ಎತ್ತರ_mm = -1; 
	info->aspect_ಅನುಪಾತ = 100.0 / (edid[0x15] + 99);
    }
    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (edid[0x15] == 0)
    {
	info->ಅಗಲ_mm = -1;
	info->ಎತ್ತರ_mm = -1;
	info->aspect_ಅನುಪಾತ = 100.0 / (edid[0x16] + 99);
	info->aspect_ಅನುಪಾತ = 1/info->aspect_ಅನುಪಾತ; /* portrait */
    }
    ಇಲ್ಲದಿದ್ದರೆ
    {
	info->ಅಗಲ_mm = 10 * edid[0x15];
	info->ಎತ್ತರ_mm = 10 * edid[0x16];
    }

    /* Gamma */
    ಆದರೆ (edid[0x17] == 0xFF)
	info->gamma = -1.0;
    ಇಲ್ಲದಿದ್ದರೆ
	info->gamma = (edid[0x17] + 100.0) / 100.0;

    /* Features */
    info->standby = get_ಬಿಟ್ (edid[0x18], 7);
    info->suspend = get_ಬಿಟ್ (edid[0x18], 6);
    info->ಸಕ್ರಿಯ_off = get_ಬಿಟ್ (edid[0x18], 5);

    ಆದರೆ (info->is_digital)
    {
	info->ad.digital.rgb444 = TRUE;
	ಆದರೆ (get_ಬಿಟ್ (edid[0x18], 3))
	    info->ad.digital.ycrcb444 = 1;
	ಆದರೆ (get_ಬಿಟ್ (edid[0x18], 4))
	    info->ad.digital.ycrcb422 = 1;
    }
    ಇಲ್ಲದಿದ್ದರೆ
    {
	ಪೂರ್ಣಾಂಕ ಬಿಟ್ಟುಗಳು = get_ಬಿಟ್ಟುಗಳು (edid[0x18], 3, 4);
	ColorType color_type[4] =
	{
	    MONOCHROME, RGB, OTHER_COLOR, UNDEFINED_COLOR
	};

	info->ad.analog.color_type = color_type[ಬಿಟ್ಟುಗಳು];
    }

    info->srgb_is_standard = get_ಬಿಟ್ (edid[0x18], 2);

    /* In 1.3 this is called "has preferred timing" */
    info->preferred_timing_includes_native = get_ಬಿಟ್ (edid[0x18], 1);

    /* FIXME: In 1.3 this indicates whether the monitor accepts GTF */
    info->continuous_frequency = get_ಬಿಟ್ (edid[0x18], 0);
    ಹಿಂತಿರುಗಿ TRUE;
}

ಸ್ಥಿರ ದ್ವಿಗುಣ
decode_fraction (ಪೂರ್ಣಾಂಕ ಮೇಲಿನ, ಪೂರ್ಣಾಂಕ ಕೆಳಗಿನ)
{
    ದ್ವಿಗುಣ ಫಲಿತಾಂಶ = 0.0;
    ಪೂರ್ಣಾಂಕ i;

    ಮೇಲಿನ = (ಮೇಲಿನ << 2) | ಕೆಳಗಿನ;

    ಗಾಗಿ (i = 0; i < 10; ++i)
	ಫಲಿತಾಂಶ += get_ಬಿಟ್ (ಮೇಲಿನ, i) * SDL_pow (2, i - 10);

    ಹಿಂತಿರುಗಿ ಫಲಿತಾಂಶ;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ
decode_color_characteristics (ಸ್ಥಿರಾಂಕ uchar *edid, MonitorInfo *info)
{
    info->red_x = decode_fraction (edid[0x1b], get_ಬಿಟ್ಟುಗಳು (edid[0x19], 6, 7));
    info->red_y = decode_fraction (edid[0x1c], get_ಬಿಟ್ಟುಗಳು (edid[0x19], 5, 4));
    info->green_x = decode_fraction (edid[0x1d], get_ಬಿಟ್ಟುಗಳು (edid[0x19], 2, 3));
    info->green_y = decode_fraction (edid[0x1e], get_ಬಿಟ್ಟುಗಳು (edid[0x19], 0, 1));
    info->blue_x = decode_fraction (edid[0x1f], get_ಬಿಟ್ಟುಗಳು (edid[0x1a], 6, 7));
    info->blue_y = decode_fraction (edid[0x20], get_ಬಿಟ್ಟುಗಳು (edid[0x1a], 4, 5));
    info->white_x = decode_fraction (edid[0x21], get_ಬಿಟ್ಟುಗಳು (edid[0x1a], 2, 3));
    info->white_y = decode_fraction (edid[0x22], get_ಬಿಟ್ಟುಗಳು (edid[0x1a], 0, 1));

    ಹಿಂತಿರುಗಿ TRUE;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ
decode_established_timings (ಸ್ಥಿರಾಂಕ uchar *edid, MonitorInfo *info)
{
    ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ Timing established[][8] = 
    {
	{
	    { 800, 600, 60 },
	    { 800, 600, 56 },
	    { 640, 480, 75 },
	    { 640, 480, 72 },
	    { 640, 480, 67 },
	    { 640, 480, 60 },
	    { 720, 400, 88 },
	    { 720, 400, 70 }
	},
	{
	    { 1280, 1024, 75 },
	    { 1024, 768, 75 },
	    { 1024, 768, 70 },
	    { 1024, 768, 60 },
	    { 1024, 768, 87 },
	    { 832, 624, 75 },
	    { 800, 600, 75 },
	    { 800, 600, 72 }
	},
	{
	    { 0, 0, 0 },
	    { 0, 0, 0 },
	    { 0, 0, 0 },
	    { 0, 0, 0 },
	    { 0, 0, 0 },
	    { 0, 0, 0 },
	    { 0, 0, 0 },
	    { 1152, 870, 75 }
	},
    };

    ಪೂರ್ಣಾಂಕ i, j, idx;

    idx = 0;
    ಗಾಗಿ (i = 0; i < 3; ++i)
    {
	ಗಾಗಿ (j = 0; j < 8; ++j)
	{
	    ಪೂರ್ಣಾಂಕ byte = edid[0x23 + i];

	    ಆದರೆ (get_ಬಿಟ್ (byte, j) && established[i][j].frequency != 0)
		info->established[idx++] = established[i][j];
	}
    }
    ಹಿಂತಿರುಗಿ TRUE;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ
decode_standard_timings (ಸ್ಥಿರಾಂಕ uchar *edid, MonitorInfo *info)
{
    ಪೂರ್ಣಾಂಕ i;
    
    ಗಾಗಿ (i = 0; i < 8; i++)
    {
	ಪೂರ್ಣಾಂಕ ಮೊದಲ = edid[0x26 + 2 * i];
	ಪೂರ್ಣಾಂಕ ಎರಡನೇ = edid[0x27 + 2 * i];

	ಆದರೆ (ಮೊದಲ != 0x01 && ಎರಡನೇ != 0x01)
	{
	    ಪೂರ್ಣಾಂಕ w = 8 * (ಮೊದಲ + 31);
	    ಪೂರ್ಣಾಂಕ h = 0;

	    ಆಯ್ಕೆ (get_ಬಿಟ್ಟುಗಳು (ಎರಡನೇ, 6, 7))
	    {
	    ಸ್ಥಿತಿ 0x00: h = (w / 16) * 10; ನಿಲ್ಲಿಸು;
	    ಸ್ಥಿತಿ 0x01: h = (w / 4) * 3; ನಿಲ್ಲಿಸು;
	    ಸ್ಥಿತಿ 0x02: h = (w / 5) * 4; ನಿಲ್ಲಿಸು;
	    ಸ್ಥಿತಿ 0x03: h = (w / 16) * 9; ನಿಲ್ಲಿಸು;
	    }

	    info->standard[i].ಅಗಲ = w;
	    info->standard[i].ಎತ್ತರ = h;
	    info->standard[i].frequency = get_ಬಿಟ್ಟುಗಳು (ಎರಡನೇ, 0, 5) + 60;
	}
    }
    
    ಹಿಂತಿರುಗಿ TRUE;
}

ಸ್ಥಿರ ಶೂನ್ಯ
decode_lf_string (ಸ್ಥಿರಾಂಕ uchar *s, ಪೂರ್ಣಾಂಕ n_chars, ಅಕ್ಷರ *ಫಲಿತಾಂಶ)
{
    ಪೂರ್ಣಾಂಕ i;
    ಗಾಗಿ (i = 0; i < n_chars; ++i)
    {
	ಆದರೆ (s[i] == 0x0a)
	{
	    *ಫಲಿತಾಂಶ++ = '\0';
	    ನಿಲ್ಲಿಸು;
	}
	ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (s[i] == 0x00)
	{
	    /* Convert embedded 0's to spaces */
	    *ಫಲಿತಾಂಶ++ = ' ';
	}
	ಇಲ್ಲದಿದ್ದರೆ
	{
	    *ಫಲಿತಾಂಶ++ = s[i];
	}
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ
decode_display_descriptor (ಸ್ಥಿರಾಂಕ uchar *desc,
			   MonitorInfo *info)
{
    ಆಯ್ಕೆ (desc[0x03])
    {
    ಸ್ಥಿತಿ 0xFC:
	decode_lf_string (desc + 5, 13, info->dsc_ಗುಣಲಬ್ಧ_name);
	ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ 0xFF:
	decode_lf_string (desc + 5, 13, info->dsc_serial_ಸಂಖ್ಯೆ);
	ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ 0xFE:
	decode_lf_string (desc + 5, 13, info->dsc_string);
	ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ 0xFD:
	/* Range Limits */
	ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ 0xFB:
	/* Color Point */
	ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ 0xFA:
	/* Timing Identifications */
	ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ 0xF9:
	/* Color Management */
	ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ 0xF8:
	/* Timing Codes */
	ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ 0xF7:
	/* Established Timings */
	ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ 0x10:
	ನಿಲ್ಲಿಸು;
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ
decode_detailed_timing (ಸ್ಥಿರಾಂಕ uchar *timing,
			DetailedTiming *detailed)
{
    ಪೂರ್ಣಾಂಕ ಬಿಟ್ಟುಗಳು;
    StereoType stereo[] =
    {
	NO_STEREO, NO_STEREO, ಕ್ಷೇತ್ರ_ಬಲ, ಕ್ಷೇತ್ರ_ಎಡ,
	TWO_WAY_ಬಲ_ON_EVEN, TWO_WAY_ಎಡ_ON_EVEN,
	FOUR_WAY_INTERLEAVED, SIDE_BY_SIDE
    };
    
    detailed->pixel_clock = (timing[0x00] | timing[0x01] << 8) * 10000;
    detailed->h_addr = timing[0x02] | ((timing[0x04] & 0xf0) << 4);
    detailed->h_blank = timing[0x03] | ((timing[0x04] & 0x0f) << 8);
    detailed->v_addr = timing[0x05] | ((timing[0x07] & 0xf0) << 4);
    detailed->v_blank = timing[0x06] | ((timing[0x07] & 0x0f) << 8);
    detailed->h_front_porch = timing[0x08] | get_ಬಿಟ್ಟುಗಳು (timing[0x0b], 6, 7) << 8;
    detailed->h_sync = timing[0x09] | get_ಬಿಟ್ಟುಗಳು (timing[0x0b], 4, 5) << 8;
    detailed->v_front_porch =
	get_ಬಿಟ್ಟುಗಳು (timing[0x0a], 4, 7) | get_ಬಿಟ್ಟುಗಳು (timing[0x0b], 2, 3) << 4;
    detailed->v_sync =
	get_ಬಿಟ್ಟುಗಳು (timing[0x0a], 0, 3) | get_ಬಿಟ್ಟುಗಳು (timing[0x0b], 0, 1) << 4;
    detailed->ಅಗಲ_mm =  timing[0x0c] | get_ಬಿಟ್ಟುಗಳು (timing[0x0e], 4, 7) << 8;
    detailed->ಎತ್ತರ_mm = timing[0x0d] | get_ಬಿಟ್ಟುಗಳು (timing[0x0e], 0, 3) << 8;
    detailed->ಬಲ_border = timing[0x0f];
    detailed->ತುದಿ_border = timing[0x10];

    detailed->interlaced = get_ಬಿಟ್ (timing[0x11], 7);

    /* Stereo */
    ಬಿಟ್ಟುಗಳು = get_ಬಿಟ್ಟುಗಳು (timing[0x11], 5, 6) << 1 | get_ಬಿಟ್ (timing[0x11], 0);
    detailed->stereo = stereo[ಬಿಟ್ಟುಗಳು];

    /* Sync */
    ಬಿಟ್ಟುಗಳು = timing[0x11];

    detailed->digital_sync = get_ಬಿಟ್ (ಬಿಟ್ಟುಗಳು, 4);
    ಆದರೆ (detailed->digital_sync)
    {
	detailed->ad.digital.ಸಂಯುಕ್ತ = !get_ಬಿಟ್ (ಬಿಟ್ಟುಗಳು, 3);

	ಆದರೆ (detailed->ad.digital.ಸಂಯುಕ್ತ)
	{
	    detailed->ad.digital.serrations = get_ಬಿಟ್ (ಬಿಟ್ಟುಗಳು, 2);
	    detailed->ad.digital.negative_vsync = FALSE;
	}
	ಇಲ್ಲದಿದ್ದರೆ
	{
	    detailed->ad.digital.serrations = FALSE;
	    detailed->ad.digital.negative_vsync = !get_ಬಿಟ್ (ಬಿಟ್ಟುಗಳು, 2);
	}

	detailed->ad.digital.negative_hsync = !get_ಬಿಟ್ (ಬಿಟ್ಟುಗಳು, 0);
    }
    ಇಲ್ಲದಿದ್ದರೆ
    {
	detailed->ad.analog.bipolar = get_ಬಿಟ್ (ಬಿಟ್ಟುಗಳು, 3);
	detailed->ad.analog.serrations = get_ಬಿಟ್ (ಬಿಟ್ಟುಗಳು, 2);
	detailed->ad.analog.sync_on_green = !get_ಬಿಟ್ (ಬಿಟ್ಟುಗಳು, 1);
    }
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ
decode_descriptors (ಸ್ಥಿರಾಂಕ uchar *edid, MonitorInfo *info)
{
    ಪೂರ್ಣಾಂಕ i;
    ಪೂರ್ಣಾಂಕ timing_idx;
    
    timing_idx = 0;
    
    ಗಾಗಿ (i = 0; i < 4; ++i)
    {
	ಪೂರ್ಣಾಂಕ ಸೂಚ್ಯಂಕ = 0x36 + i * 18;

	ಆದರೆ (edid[ಸೂಚ್ಯಂಕ + 0] == 0x00 && edid[ಸೂಚ್ಯಂಕ + 1] == 0x00)
	{
	    decode_display_descriptor (edid + ಸೂಚ್ಯಂಕ, info);
	}
	ಇಲ್ಲದಿದ್ದರೆ
	{
	    decode_detailed_timing (
		edid + ಸೂಚ್ಯಂಕ, &(info->detailed_timings[timing_idx++]));
	}
    }

    info->n_detailed_timings = timing_idx;

    ಹಿಂತಿರುಗಿ TRUE;
}

ಸ್ಥಿರ ಶೂನ್ಯ
decode_check_ಮೊತ್ತ (ಸ್ಥಿರಾಂಕ uchar *edid,
		  MonitorInfo *info)
{
    ಪೂರ್ಣಾಂಕ i;
    uchar check = 0;

    ಗಾಗಿ (i = 0; i < 128; ++i)
	check += edid[i];

    info->checksum = check;
}

ಸ್ಥಿರ ಶೂನ್ಯ
decode_HDR_metadata_ಖಂಡ (ಸ್ಥಿರಾಂಕ uchar *ದತ್ತಾಂಶ, ಪೂರ್ಣಾಂಕ ಉದ್ದಳತೆ, MonitorInfo *info)
{
    ಆದರೆ (ಉದ್ದಳತೆ >= 3)
	info->max_luminance = 50.0 * SDL_pow(2, ದತ್ತಾಂಶ[2] / 32.0);

    ಆದರೆ (ಉದ್ದಳತೆ >= 4)
	info->max_ಚೌಕಟ್ಟು_ಸರಾಸರಿ_ಮೌಲ್ಯ_luminance = 50.0 * SDL_pow(2, ದತ್ತಾಂಶ[3] / 32.0);

    ಆದರೆ (ಉದ್ದಳತೆ >= 5)
	info->min_luminance = 50.0 * SDL_pow(2, ದತ್ತಾಂಶ[4] / 32.0);
}


ಸ್ಥಿರ ಶೂನ್ಯ
decode_cta_ಖಂಡ (ಸ್ಥಿರಾಂಕ uchar *edid,
		  MonitorInfo *info)
{
    ಪೂರ್ಣಾಂಕ ಸ್ಥಾನಾಂತರ_2 = 4;
    ಆಗ (ಸ್ಥಾನಾಂತರ_2 < 128) {
	ಪೂರ್ಣಾಂಕ ಉದ್ದಳತೆ = edid[ಸ್ಥಾನಾಂತರ_2] & 0x1f;
	ಪೂರ್ಣಾಂಕ type = edid[ಸ್ಥಾನಾಂತರ_2] >> 5;
	ಆದರೆ (ಉದ್ದಳತೆ == 0) {
	    ನಿಲ್ಲಿಸು;
	}
	ಆದರೆ (type == 7) {
	    type <<= 8;
	    type |= edid[ಸ್ಥಾನಾಂತರ_2 + 1];
	}
	ಆದರೆ (type == 0x706) {
	    decode_HDR_metadata_ಖಂಡ (&edid[ಸ್ಥಾನಾಂತರ_2 + 2], ಉದ್ದಳತೆ - 1, info);
	}
	ಸ್ಥಾನಾಂತರ_2 += (1 + ಉದ್ದಳತೆ);
    }
}

MonitorInfo *
decode_edid (ಸ್ಥಿರಾಂಕ uchar *edid, size_t ಗಾತ್ರ_2)
{
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ EDID_ಪುಟ_ಗಾತ್ರ = 128;
    ಪೂರ್ಣಾಂಕ ಅಂಕೆ_ಖಂಡಗಳು = (ಗಾತ್ರ_2 / EDID_ಪುಟ_ಗಾತ್ರ);
    MonitorInfo *info;

    ಆದರೆ ((ಗಾತ್ರ_2 % EDID_ಪುಟ_ಗಾತ್ರ) != 0) {
	ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    info = SDL_calloc (1, ಗಾತ್ರ (MonitorInfo));

    decode_check_ಮೊತ್ತ (edid, info);
    
    ಆದರೆ (!decode_ಶೀರ್ಷಿಕೆ (edid) ||
        !decode_vendor_and_ಗುಣಲಬ್ಧ_identification (edid, info) ||
        !decode_edid_ಆವೃತ್ತಿ (edid, info) ||
        !decode_display_parameters (edid, info) ||
        !decode_color_characteristics (edid, info) ||
        !decode_established_timings (edid, info) ||
        !decode_standard_timings (edid, info) ||
        !decode_descriptors (edid, info)) {
	SDL_free(info);
	ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }
    
    ಆದರೆ (ಅಂಕೆ_ಖಂಡಗಳು > 1) {
	ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 1; i < ಅಂಕೆ_ಖಂಡಗಳು; ++i) {
	    ಪೂರ್ಣಾಂಕ ಸ್ಥಾನಾಂತರ_2 = i * EDID_ಪುಟ_ಗಾತ್ರ;
	    uchar extension = edid[ಸ್ಥಾನಾಂತರ_2];
	    ಆದರೆ (extension == 0x02) {
		// CTA-861 Extension Block
		decode_cta_ಖಂಡ (&edid[ಸ್ಥಾನಾಂತರ_2], info);
	    }
	}
    }

    ಹಿಂತಿರುಗಿ info;
}

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *
yesno (ಪೂರ್ಣಾಂಕ v)
{
    ಹಿಂತಿರುಗಿ v? "yes" : "no";
}

ಶೂನ್ಯ
dump_monitor_info (MonitorInfo *info)
{
    ಪೂರ್ಣಾಂಕ i;
    
    ಬರೆ ("Checksum: %d (%s)\n",
	    info->checksum, info->checksum? "incorrect" : "correct");
    ಬರೆ ("Manufacturer Code: %s\n", info->manufacturer_ಸಂಕೇತ);
    ಬರೆ ("Product Code: 0x%x\n", info->ಗುಣಲಬ್ಧ_ಸಂಕೇತ);
    ಬರೆ ("Serial Number: %u\n", info->serial_ಸಂಖ್ಯೆ);
    
    ಆದರೆ (info->production_week != -1)
	ಬರೆ ("Production Week: %d\n", info->production_week);
    ಇಲ್ಲದಿದ್ದರೆ
	ಬರೆ ("Production Week: unspecified\n");
    
    ಆದರೆ (info->production_year != -1)
	ಬರೆ ("Production Year: %d\n", info->production_year);
    ಇಲ್ಲದಿದ್ದರೆ
	ಬರೆ ("Production Year: unspecified\n");
    
    ಆದರೆ (info->model_year != -1)
	ಬರೆ ("Model Year: %d\n", info->model_year);
    ಇಲ್ಲದಿದ್ದರೆ
	ಬರೆ ("Model Year: unspecified\n");
    
    ಬರೆ ("EDID revision: %d.%d\n", info->major_ಆವೃತ್ತಿ, info->minor_ಆವೃತ್ತಿ);
    
    ಬರೆ ("Display is %s\n", info->is_digital? "digital" : "analog");
    ಆದರೆ (info->is_digital)
    {
	ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *interface;
	ಆದರೆ (info->ad.digital.ಬಿಟ್ಟುಗಳು_ಪ್ರತಿ_primary != -1)
	    ಬರೆ ("Bits Per Primary: %d\n", info->ad.digital.ಬಿಟ್ಟುಗಳು_ಪ್ರತಿ_primary);
	ಇಲ್ಲದಿದ್ದರೆ
	    ಬರೆ ("Bits Per Primary: undefined\n");
	
	ಆಯ್ಕೆ (info->ad.digital.interface)
	{
	ಸ್ಥಿತಿ DVI: interface = "DVI"; ನಿಲ್ಲಿಸು;
	ಸ್ಥಿತಿ HDMI_A: interface = "HDMI-a"; ನಿಲ್ಲಿಸು;
	ಸ್ಥಿತಿ HDMI_B: interface = "HDMI-b"; ನಿಲ್ಲಿಸು;
	ಸ್ಥಿತಿ MDDI: interface = "MDDI"; ನಿಲ್ಲಿಸು;
	ಸ್ಥಿತಿ DISPLAY_ಪೋರ್ಟ್: interface = "DisplayPort"; ನಿಲ್ಲಿಸು;
	ಸ್ಥಿತಿ UNDEFINED: interface = "undefined"; ನಿಲ್ಲಿಸು;
	ಪೂರ್ವನಿಯೋಜಿತ: interface = "unknown"; ನಿಲ್ಲಿಸು;
	}
	ಬರೆ ("Interface: %s\n", interface);
	
	ಬರೆ ("RGB 4:4:4: %s\n", yesno (info->ad.digital.rgb444));
	ಬರೆ ("YCrCb 4:4:4: %s\n", yesno (info->ad.digital.ycrcb444));
	ಬರೆ ("YCrCb 4:2:2: %s\n", yesno (info->ad.digital.ycrcb422));
    }
    ಇಲ್ಲದಿದ್ದರೆ
    {
       ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *s;
	ಬರೆ ("Video Signal Level: %f\n", info->ad.analog.video_signal_level);
	ಬರೆ ("Sync Signal Level: %f\n", info->ad.analog.sync_signal_level);
	ಬರೆ ("Total Signal Level: %f\n", info->ad.analog.ಒಟ್ಟು_signal_level);
	
	ಬರೆ ("Blank to Black: %s\n",
		yesno (info->ad.analog.blank_ಗಮ್ಯ_black));
	ಬರೆ ("Separate HV Sync: %s\n",
		yesno (info->ad.analog.separate_hv_sync));
	ಬರೆ ("Composite Sync on H: %s\n",
		yesno (info->ad.analog.ಸಂಯುಕ್ತ_sync_on_h));
	ಬರೆ ("Serration on VSync: %s\n",
		yesno (info->ad.analog.serration_on_vsync));
	
	ಆಯ್ಕೆ (info->ad.analog.color_type)
	{
	ಸ್ಥಿತಿ UNDEFINED_COLOR: s = "undefined"; ನಿಲ್ಲಿಸು;
	ಸ್ಥಿತಿ MONOCHROME: s = "monochrome"; ನಿಲ್ಲಿಸು;
	ಸ್ಥಿತಿ RGB: s = "rgb"; ನಿಲ್ಲಿಸು;
	ಸ್ಥಿತಿ OTHER_COLOR: s = "other color"; ನಿಲ್ಲಿಸು;
	ಪೂರ್ವನಿಯೋಜಿತ: s = "unknown"; ನಿಲ್ಲಿಸು;
	}
	
	ಬರೆ ("Color: %s\n", s);
    }
    
    ಆದರೆ (info->ಅಗಲ_mm == -1)
	ಬರೆ ("Width: undefined\n");
    ಇಲ್ಲದಿದ್ದರೆ
	ಬರೆ ("Width: %d mm\n", info->ಅಗಲ_mm);
    
    ಆದರೆ (info->ಎತ್ತರ_mm == -1)
	ಬರೆ ("Height: undefined\n");
    ಇಲ್ಲದಿದ್ದರೆ
	ಬರೆ ("Height: %d mm\n", info->ಎತ್ತರ_mm);
    
    ಆದರೆ (info->aspect_ಅನುಪಾತ > 0)
	ಬರೆ ("Aspect Ratio: %f\n", info->aspect_ಅನುಪಾತ);
    ಇಲ್ಲದಿದ್ದರೆ
	ಬರೆ ("Aspect Ratio: undefined\n");
    
    ಆದರೆ (info->gamma >= 0)
	ಬರೆ ("Gamma: %f\n", info->gamma);
    ಇಲ್ಲದಿದ್ದರೆ
	ಬರೆ ("Gamma: undefined\n");
    
    ಬರೆ ("Standby: %s\n", yesno (info->standby));
    ಬರೆ ("Suspend: %s\n", yesno (info->suspend));
    ಬರೆ ("Active Off: %s\n", yesno (info->ಸಕ್ರಿಯ_off));
    
    ಬರೆ ("SRGB is Standard: %s\n", yesno (info->srgb_is_standard));
    ಬರೆ ("Preferred Timing Includes Native: %s\n",
	    yesno (info->preferred_timing_includes_native));
    ಬರೆ ("Continuous Frequency: %s\n", yesno (info->continuous_frequency));
    
    ಬರೆ ("Red X: %f\n", info->red_x);
    ಬರೆ ("Red Y: %f\n", info->red_y);
    ಬರೆ ("Green X: %f\n", info->green_x);
    ಬರೆ ("Green Y: %f\n", info->green_y);
    ಬರೆ ("Blue X: %f\n", info->blue_x);
    ಬರೆ ("Blue Y: %f\n", info->blue_y);
    ಬರೆ ("White X: %f\n", info->white_x);
    ಬರೆ ("White Y: %f\n", info->white_y);
    ಬರೆ ("Min luminance: %f\n", info->min_luminance);
    ಬರೆ ("Max luminance: %f\n", info->max_luminance);
    ಬರೆ ("Max frame average luminance %f\n", info->max_ಚೌಕಟ್ಟು_ಸರಾಸರಿ_ಮೌಲ್ಯ_luminance);
    
    ಬರೆ ("Established Timings:\n");
    
    ಗಾಗಿ (i = 0; i < 24; ++i)
    {
	Timing *timing = &(info->established[i]);
	
	ಆದರೆ (timing->frequency == 0)
	    ನಿಲ್ಲಿಸು;
	
	ಬರೆ ("  %d x %d @ %d Hz\n",
		timing->ಅಗಲ, timing->ಎತ್ತರ, timing->frequency);
	
    }
    
    ಬರೆ ("Standard Timings:\n");
    ಗಾಗಿ (i = 0; i < 8; ++i)
    {
	Timing *timing = &(info->standard[i]);
	
	ಆದರೆ (timing->frequency == 0)
	    ನಿಲ್ಲಿಸು;
	
	ಬರೆ ("  %d x %d @ %d Hz\n",
		timing->ಅಗಲ, timing->ಎತ್ತರ, timing->frequency);
    }
    
    ಗಾಗಿ (i = 0; i < info->n_detailed_timings; ++i)
    {
	DetailedTiming *timing = &(info->detailed_timings[i]);
	ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *s;
	
	ಬರೆ ("Timing%s: \n",
		(i == 0 && info->preferred_timing_includes_native)?
		" (Preferred)" : "");
	ಬರೆ ("  Pixel Clock: %d\n", timing->pixel_clock);
	ಬರೆ ("  H Addressable: %d\n", timing->h_addr);
	ಬರೆ ("  H Blank: %d\n", timing->h_blank);
	ಬರೆ ("  H Front Porch: %d\n", timing->h_front_porch);
	ಬರೆ ("  H Sync: %d\n", timing->h_sync);
	ಬರೆ ("  V Addressable: %d\n", timing->v_addr);
	ಬರೆ ("  V Blank: %d\n", timing->v_blank);
	ಬರೆ ("  V Front Porch: %d\n", timing->v_front_porch);
	ಬರೆ ("  V Sync: %d\n", timing->v_sync);
	ಬರೆ ("  Width: %d mm\n", timing->ಅಗಲ_mm);
	ಬರೆ ("  Height: %d mm\n", timing->ಎತ್ತರ_mm);
	ಬರೆ ("  Right Border: %d\n", timing->ಬಲ_border);
	ಬರೆ ("  Top Border: %d\n", timing->ತುದಿ_border);
	ಆಯ್ಕೆ (timing->stereo)
	{
	ಪೂರ್ವನಿಯೋಜಿತ:
	ಸ್ಥಿತಿ NO_STEREO:   s = "No Stereo"; ನಿಲ್ಲಿಸು;
	ಸ್ಥಿತಿ ಕ್ಷೇತ್ರ_ಬಲ: s = "Field Sequential, Right on Sync"; ನಿಲ್ಲಿಸು;
	ಸ್ಥಿತಿ ಕ್ಷೇತ್ರ_ಎಡ:  s = "Field Sequential, Left on Sync"; ನಿಲ್ಲಿಸು;
	ಸ್ಥಿತಿ TWO_WAY_ಬಲ_ON_EVEN: s = "Two-way, Right on Even"; ನಿಲ್ಲಿಸು;
	ಸ್ಥಿತಿ TWO_WAY_ಎಡ_ON_EVEN:  s = "Two-way, Left on Even"; ನಿಲ್ಲಿಸು;
	ಸ್ಥಿತಿ FOUR_WAY_INTERLEAVED:  s = "Four-way Interleaved"; ನಿಲ್ಲಿಸು;
	ಸ್ಥಿತಿ SIDE_BY_SIDE:          s = "Side-by-Side"; ನಿಲ್ಲಿಸು;
	}
	ಬರೆ ("  Stereo: %s\n", s);
	
	ಆದರೆ (timing->digital_sync)
	{
	    ಬರೆ ("  Digital Sync:\n");
	    ಬರೆ ("    composite: %s\n", yesno (timing->ad.digital.ಸಂಯುಕ್ತ));
	    ಬರೆ ("    serrations: %s\n", yesno (timing->ad.digital.serrations));
	    ಬರೆ ("    negative vsync: %s\n",
		    yesno (timing->ad.digital.negative_vsync));
	    ಬರೆ ("    negative hsync: %s\n",
		    yesno (timing->ad.digital.negative_hsync));
	}
	ಇಲ್ಲದಿದ್ದರೆ
	{
	    ಬರೆ ("  Analog Sync:\n");
	    ಬರೆ ("    bipolar: %s\n", yesno (timing->ad.analog.bipolar));
	    ಬರೆ ("    serrations: %s\n", yesno (timing->ad.analog.serrations));
	    ಬರೆ ("    sync on green: %s\n", yesno (
			timing->ad.analog.sync_on_green));
	}
    }
    
    ಬರೆ ("Detailed Product information:\n");
    ಬರೆ ("  Product Name: %s\n", info->dsc_ಗುಣಲಬ್ಧ_name);
    ಬರೆ ("  Serial Number: %s\n", info->dsc_serial_ಸಂಖ್ಯೆ);
    ಬರೆ ("  Unspecified String: %s\n", info->dsc_string);
}

