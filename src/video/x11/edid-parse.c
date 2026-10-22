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

#define TRUE 1
#define FALSE 0

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ
get_bit (ಪೂರ್ಣಾಙ್ಕ in, ಪೂರ್ಣಾಙ್ಕ bit)
{
    ಪ್ರತ್ಯಾಗಮ (in & (1 << bit)) >> bit;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ
get_bits (ಪೂರ್ಣಾಙ್ಕ in, ಪೂರ್ಣಾಙ್ಕ begin, ಪೂರ್ಣಾಙ್ಕ end)
{
    ಪೂರ್ಣಾಙ್ಕ mask = (1 << (end - begin + 1)) - 1;
    
    ಪ್ರತ್ಯಾಗಮ (in >> begin) & mask;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ
decode_header (ಧ್ರುವ uchar *edid)
{
    ಯದಿ (SDL_memcmp (edid, "\x00\xff\xff\xff\xff\xff\xff\x00", 8) == 0)
	ಪ್ರತ್ಯಾಗಮ TRUE;
    ಪ್ರತ್ಯಾಗಮ FALSE;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ
decode_vendor_and_product_identification (ಧ್ರುವ uchar *edid, MonitorInfo *info)
{
    ಪೂರ್ಣಾಙ್ಕ is_model_year;
    
    /* Manufacturer Code */
    info->manufacturer_code[0]  = get_bits (edid[0x08], 2, 6);
    info->manufacturer_code[1]  = get_bits (edid[0x08], 0, 1) << 3;
    info->manufacturer_code[1] |= get_bits (edid[0x09], 5, 7);
    info->manufacturer_code[2]  = get_bits (edid[0x09], 0, 4);
    info->manufacturer_code[3]  = '\0';
    
    info->manufacturer_code[0] += 'A' - 1;
    info->manufacturer_code[1] += 'A' - 1;
    info->manufacturer_code[2] += 'A' - 1;

    /* Product Code */
    info->product_code = edid[0x0b] << 8 | edid[0x0a];

    /* Serial Number */
    info->serial_ಸಂಖ್ಯೆ =
	edid[0x0c] | edid[0x0d] << 8 | edid[0x0e] << 16 | (Uint32)edid[0x0f] << 24;

    /* Week and Year */
    is_model_year = FALSE;
    ವಿಕಲ್ಪ (edid[0x10])
    {
    ಪಕ್ಷ 0x00:
	info->production_week = -1;
	ಭಙ್ಗ;

    ಪಕ್ಷ 0xff:
	info->production_week = -1;
	is_model_year = TRUE;
	ಭಙ್ಗ;

    ಸ್ವಭಾವ:
	info->production_week = edid[0x10];
	ಭಙ್ಗ;
    }

    ಯದಿ (is_model_year)
    {
	info->production_year = -1;
	info->model_year = 1990 + edid[0x11];
    }
    ಅನ್ಯಥಾ
    {
	info->production_year = 1990 + edid[0x11];
	info->model_year = -1;
    }

    ಪ್ರತ್ಯಾಗಮ TRUE;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ
decode_edid_version (ಧ್ರುವ uchar *edid, MonitorInfo *info)
{
    info->major_version = edid[0x12];
    info->minor_version = edid[0x13];

    ಪ್ರತ್ಯಾಗಮ TRUE;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ
decode_display_parameters (ಧ್ರುವ uchar *edid, MonitorInfo *info)
{
    /* Digital vs Analog */
    info->is_digital = get_bit (edid[0x14], 7);

    ಯದಿ (info->is_digital)
    {
	ಪೂರ್ಣಾಙ್ಕ bits;
	
	ಸ್ಥಿರ ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ bit_depth[8] =
	{
	    -1, 6, 8, 10, 12, 14, 16, -1
	};

	ಸ್ಥಿರ ಧ್ರುವ Interface interfaces[6] =
	{
	    UNDEFINED, DVI, HDMI_A, HDMI_B, MDDI, DISPLAY_PORT
	};

	bits = get_bits (edid[0x14], 4, 6);
	info->ad.digital.bits_per_primary = bit_depth[bits];

	bits = get_bits (edid[0x14], 0, 3);
	
	ಯದಿ (bits <= 5)
	    info->ad.digital.interface = interfaces[bits];
	ಅನ್ಯಥಾ
	    info->ad.digital.interface = UNDEFINED;
    }
    ಅನ್ಯಥಾ
    {
	ಪೂರ್ಣಾಙ್ಕ bits = get_bits (edid[0x14], 5, 6);
	
	ಸ್ಥಿರ ಧ್ರುವ ದ್ವಿಗುಣ levels[][3] =
	{
	    { 0.7,   0.3,    1.0 },
	    { 0.714, 0.286,  1.0 },
	    { 1.0,   0.4,    1.4 },
	    { 0.7,   0.0,    0.7 },
	};

	info->ad.analog.video_signal_level = levels[bits][0];
	info->ad.analog.sync_signal_level = levels[bits][1];
	info->ad.analog.total_signal_level = levels[bits][2];

	info->ad.analog.blank_to_black = get_bit (edid[0x14], 4);

	info->ad.analog.separate_hv_sync = get_bit (edid[0x14], 3);
	info->ad.analog.composite_sync_on_h = get_bit (edid[0x14], 2);
	info->ad.analog.composite_sync_on_green = get_bit (edid[0x14], 1);

	info->ad.analog.serration_on_vsync = get_bit (edid[0x14], 0);
    }

    /* Screen Size / Aspect Ratio */
    ಯದಿ (edid[0x15] == 0 && edid[0x16] == 0)
    {
	info->width_mm = -1;
	info->height_mm = -1;
	info->aspect_ratio = -1.0;
    }
    ಅನ್ಯಥಾ ಯದಿ (edid[0x16] == 0)
    {
	info->width_mm = -1;
	info->height_mm = -1; 
	info->aspect_ratio = 100.0 / (edid[0x15] + 99);
    }
    ಅನ್ಯಥಾ ಯದಿ (edid[0x15] == 0)
    {
	info->width_mm = -1;
	info->height_mm = -1;
	info->aspect_ratio = 100.0 / (edid[0x16] + 99);
	info->aspect_ratio = 1/info->aspect_ratio; /* portrait */
    }
    ಅನ್ಯಥಾ
    {
	info->width_mm = 10 * edid[0x15];
	info->height_mm = 10 * edid[0x16];
    }

    /* Gamma */
    ಯದಿ (edid[0x17] == 0xFF)
	info->gamma = -1.0;
    ಅನ್ಯಥಾ
	info->gamma = (edid[0x17] + 100.0) / 100.0;

    /* Features */
    info->standby = get_bit (edid[0x18], 7);
    info->suspend = get_bit (edid[0x18], 6);
    info->active_off = get_bit (edid[0x18], 5);

    ಯದಿ (info->is_digital)
    {
	info->ad.digital.rgb444 = TRUE;
	ಯದಿ (get_bit (edid[0x18], 3))
	    info->ad.digital.ycrcb444 = 1;
	ಯದಿ (get_bit (edid[0x18], 4))
	    info->ad.digital.ycrcb422 = 1;
    }
    ಅನ್ಯಥಾ
    {
	ಪೂರ್ಣಾಙ್ಕ bits = get_bits (edid[0x18], 3, 4);
	ColorType color_type[4] =
	{
	    MONOCHROME, RGB, OTHER_COLOR, UNDEFINED_COLOR
	};

	info->ad.analog.color_type = color_type[bits];
    }

    info->srgb_is_standard = get_bit (edid[0x18], 2);

    /* In 1.3 this is called "has preferred timing" */
    info->preferred_timing_includes_native = get_bit (edid[0x18], 1);

    /* FIXME: In 1.3 this indicates whether the monitor accepts GTF */
    info->continuous_frequency = get_bit (edid[0x18], 0);
    ಪ್ರತ್ಯಾಗಮ TRUE;
}

ಸ್ಥಿರ ದ್ವಿಗುಣ
decode_fraction (ಪೂರ್ಣಾಙ್ಕ ಮೇಲಿನ, ಪೂರ್ಣಾಙ್ಕ ಕೆಳಗಿನ)
{
    ದ್ವಿಗುಣ result = 0.0;
    ಪೂರ್ಣಾಙ್ಕ i;

    ಮೇಲಿನ = (ಮೇಲಿನ << 2) | ಕೆಳಗಿನ;

    ಪ್ರತಿ (i = 0; i < 10; ++i)
	result += get_bit (ಮೇಲಿನ, i) * SDL_pow (2, i - 10);

    ಪ್ರತ್ಯಾಗಮ result;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ
decode_color_characteristics (ಧ್ರುವ uchar *edid, MonitorInfo *info)
{
    info->red_x = decode_fraction (edid[0x1b], get_bits (edid[0x19], 6, 7));
    info->red_y = decode_fraction (edid[0x1c], get_bits (edid[0x19], 5, 4));
    info->green_x = decode_fraction (edid[0x1d], get_bits (edid[0x19], 2, 3));
    info->green_y = decode_fraction (edid[0x1e], get_bits (edid[0x19], 0, 1));
    info->blue_x = decode_fraction (edid[0x1f], get_bits (edid[0x1a], 6, 7));
    info->blue_y = decode_fraction (edid[0x20], get_bits (edid[0x1a], 4, 5));
    info->white_x = decode_fraction (edid[0x21], get_bits (edid[0x1a], 2, 3));
    info->white_y = decode_fraction (edid[0x22], get_bits (edid[0x1a], 0, 1));

    ಪ್ರತ್ಯಾಗಮ TRUE;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ
decode_established_timings (ಧ್ರುವ uchar *edid, MonitorInfo *info)
{
    ಸ್ಥಿರ ಧ್ರುವ Timing established[][8] = 
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

    ಪೂರ್ಣಾಙ್ಕ i, j, idx;

    idx = 0;
    ಪ್ರತಿ (i = 0; i < 3; ++i)
    {
	ಪ್ರತಿ (j = 0; j < 8; ++j)
	{
	    ಪೂರ್ಣಾಙ್ಕ byte = edid[0x23 + i];

	    ಯದಿ (get_bit (byte, j) && established[i][j].frequency != 0)
		info->established[idx++] = established[i][j];
	}
    }
    ಪ್ರತ್ಯಾಗಮ TRUE;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ
decode_standard_timings (ಧ್ರುವ uchar *edid, MonitorInfo *info)
{
    ಪೂರ್ಣಾಙ್ಕ i;
    
    ಪ್ರತಿ (i = 0; i < 8; i++)
    {
	ಪೂರ್ಣಾಙ್ಕ first = edid[0x26 + 2 * i];
	ಪೂರ್ಣಾಙ್ಕ second = edid[0x27 + 2 * i];

	ಯದಿ (first != 0x01 && second != 0x01)
	{
	    ಪೂರ್ಣಾಙ್ಕ w = 8 * (first + 31);
	    ಪೂರ್ಣಾಙ್ಕ h = 0;

	    ವಿಕಲ್ಪ (get_bits (second, 6, 7))
	    {
	    ಪಕ್ಷ 0x00: h = (w / 16) * 10; ಭಙ್ಗ;
	    ಪಕ್ಷ 0x01: h = (w / 4) * 3; ಭಙ್ಗ;
	    ಪಕ್ಷ 0x02: h = (w / 5) * 4; ಭಙ್ಗ;
	    ಪಕ್ಷ 0x03: h = (w / 16) * 9; ಭಙ್ಗ;
	    }

	    info->standard[i].width = w;
	    info->standard[i].height = h;
	    info->standard[i].frequency = get_bits (second, 0, 5) + 60;
	}
    }
    
    ಪ್ರತ್ಯಾಗಮ TRUE;
}

ಸ್ಥಿರ ಶೂನ್ಯ
decode_lf_string (ಧ್ರುವ uchar *s, ಪೂರ್ಣಾಙ್ಕ n_chars, ವರ್ಣ *result)
{
    ಪೂರ್ಣಾಙ್ಕ i;
    ಪ್ರತಿ (i = 0; i < n_chars; ++i)
    {
	ಯದಿ (s[i] == 0x0a)
	{
	    *result++ = '\0';
	    ಭಙ್ಗ;
	}
	ಅನ್ಯಥಾ ಯದಿ (s[i] == 0x00)
	{
	    /* Convert embedded 0's to spaces */
	    *result++ = ' ';
	}
	ಅನ್ಯಥಾ
	{
	    *result++ = s[i];
	}
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ
decode_display_descriptor (ಧ್ರುವ uchar *desc,
			   MonitorInfo *info)
{
    ವಿಕಲ್ಪ (desc[0x03])
    {
    ಪಕ್ಷ 0xFC:
	decode_lf_string (desc + 5, 13, info->dsc_product_name);
	ಭಙ್ಗ;
    ಪಕ್ಷ 0xFF:
	decode_lf_string (desc + 5, 13, info->dsc_serial_ಸಂಖ್ಯೆ);
	ಭಙ್ಗ;
    ಪಕ್ಷ 0xFE:
	decode_lf_string (desc + 5, 13, info->dsc_string);
	ಭಙ್ಗ;
    ಪಕ್ಷ 0xFD:
	/* Range Limits */
	ಭಙ್ಗ;
    ಪಕ್ಷ 0xFB:
	/* Color Point */
	ಭಙ್ಗ;
    ಪಕ್ಷ 0xFA:
	/* Timing Identifications */
	ಭಙ್ಗ;
    ಪಕ್ಷ 0xF9:
	/* Color Management */
	ಭಙ್ಗ;
    ಪಕ್ಷ 0xF8:
	/* Timing Codes */
	ಭಙ್ಗ;
    ಪಕ್ಷ 0xF7:
	/* Established Timings */
	ಭಙ್ಗ;
    ಪಕ್ಷ 0x10:
	ಭಙ್ಗ;
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ
decode_detailed_timing (ಧ್ರುವ uchar *timing,
			DetailedTiming *detailed)
{
    ಪೂರ್ಣಾಙ್ಕ bits;
    StereoType stereo[] =
    {
	NO_STEREO, NO_STEREO, FIELD_ಬಲ, FIELD_ಎಡ,
	TWO_WAY_ಬಲ_ON_EVEN, TWO_WAY_ಎಡ_ON_EVEN,
	FOUR_WAY_INTERLEAVED, SIDE_BY_SIDE
    };
    
    detailed->pixel_clock = (timing[0x00] | timing[0x01] << 8) * 10000;
    detailed->h_addr = timing[0x02] | ((timing[0x04] & 0xf0) << 4);
    detailed->h_blank = timing[0x03] | ((timing[0x04] & 0x0f) << 8);
    detailed->v_addr = timing[0x05] | ((timing[0x07] & 0xf0) << 4);
    detailed->v_blank = timing[0x06] | ((timing[0x07] & 0x0f) << 8);
    detailed->h_front_porch = timing[0x08] | get_bits (timing[0x0b], 6, 7) << 8;
    detailed->h_sync = timing[0x09] | get_bits (timing[0x0b], 4, 5) << 8;
    detailed->v_front_porch =
	get_bits (timing[0x0a], 4, 7) | get_bits (timing[0x0b], 2, 3) << 4;
    detailed->v_sync =
	get_bits (timing[0x0a], 0, 3) | get_bits (timing[0x0b], 0, 1) << 4;
    detailed->width_mm =  timing[0x0c] | get_bits (timing[0x0e], 4, 7) << 8;
    detailed->height_mm = timing[0x0d] | get_bits (timing[0x0e], 0, 3) << 8;
    detailed->ಬಲ_border = timing[0x0f];
    detailed->ತುದಿ_border = timing[0x10];

    detailed->interlaced = get_bit (timing[0x11], 7);

    /* Stereo */
    bits = get_bits (timing[0x11], 5, 6) << 1 | get_bit (timing[0x11], 0);
    detailed->stereo = stereo[bits];

    /* Sync */
    bits = timing[0x11];

    detailed->digital_sync = get_bit (bits, 4);
    ಯದಿ (detailed->digital_sync)
    {
	detailed->ad.digital.composite = !get_bit (bits, 3);

	ಯದಿ (detailed->ad.digital.composite)
	{
	    detailed->ad.digital.serrations = get_bit (bits, 2);
	    detailed->ad.digital.negative_vsync = FALSE;
	}
	ಅನ್ಯಥಾ
	{
	    detailed->ad.digital.serrations = FALSE;
	    detailed->ad.digital.negative_vsync = !get_bit (bits, 2);
	}

	detailed->ad.digital.negative_hsync = !get_bit (bits, 0);
    }
    ಅನ್ಯಥಾ
    {
	detailed->ad.analog.bipolar = get_bit (bits, 3);
	detailed->ad.analog.serrations = get_bit (bits, 2);
	detailed->ad.analog.sync_on_green = !get_bit (bits, 1);
    }
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ
decode_descriptors (ಧ್ರುವ uchar *edid, MonitorInfo *info)
{
    ಪೂರ್ಣಾಙ್ಕ i;
    ಪೂರ್ಣಾಙ್ಕ timing_idx;
    
    timing_idx = 0;
    
    ಪ್ರತಿ (i = 0; i < 4; ++i)
    {
	ಪೂರ್ಣಾಙ್ಕ index = 0x36 + i * 18;

	ಯದಿ (edid[index + 0] == 0x00 && edid[index + 1] == 0x00)
	{
	    decode_display_descriptor (edid + index, info);
	}
	ಅನ್ಯಥಾ
	{
	    decode_detailed_timing (
		edid + index, &(info->detailed_timings[timing_idx++]));
	}
    }

    info->n_detailed_timings = timing_idx;

    ಪ್ರತ್ಯಾಗಮ TRUE;
}

ಸ್ಥಿರ ಶೂನ್ಯ
decode_check_sum (ಧ್ರುವ uchar *edid,
		  MonitorInfo *info)
{
    ಪೂರ್ಣಾಙ್ಕ i;
    uchar check = 0;

    ಪ್ರತಿ (i = 0; i < 128; ++i)
	check += edid[i];

    info->checksum = check;
}

ಸ್ಥಿರ ಶೂನ್ಯ
decode_HDR_metadata_block (ಧ್ರುವ uchar *data, ಪೂರ್ಣಾಙ್ಕ length, MonitorInfo *info)
{
    ಯದಿ (length >= 3)
	info->max_luminance = 50.0 * SDL_pow(2, data[2] / 32.0);

    ಯದಿ (length >= 4)
	info->max_frame_average_luminance = 50.0 * SDL_pow(2, data[3] / 32.0);

    ಯದಿ (length >= 5)
	info->min_luminance = 50.0 * SDL_pow(2, data[4] / 32.0);
}


ಸ್ಥಿರ ಶೂನ್ಯ
decode_cta_block (ಧ್ರುವ uchar *edid,
		  MonitorInfo *info)
{
    ಪೂರ್ಣಾಙ್ಕ offset = 4;
    ಯಾವತ್ (offset < 128) {
	ಪೂರ್ಣಾಙ್ಕ length = edid[offset] & 0x1f;
	ಪೂರ್ಣಾಙ್ಕ type = edid[offset] >> 5;
	ಯದಿ (length == 0) {
	    ಭಙ್ಗ;
	}
	ಯದಿ (type == 7) {
	    type <<= 8;
	    type |= edid[offset + 1];
	}
	ಯದಿ (type == 0x706) {
	    decode_HDR_metadata_block (&edid[offset + 2], length - 1, info);
	}
	offset += (1 + length);
    }
}

MonitorInfo *
decode_edid (ಧ್ರುವ uchar *edid, size_t size)
{
    ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ EDID_PAGE_SIZE = 128;
    ಪೂರ್ಣಾಙ್ಕ ಅಂಕೆ_blocks = (size / EDID_PAGE_SIZE);
    MonitorInfo *info;

    ಯದಿ ((size % EDID_PAGE_SIZE) != 0) {
	ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }

    info = SDL_calloc (1, ಪರಿಮಾಣ (MonitorInfo));

    decode_check_sum (edid, info);
    
    ಯದಿ (!decode_header (edid) ||
        !decode_vendor_and_product_identification (edid, info) ||
        !decode_edid_version (edid, info) ||
        !decode_display_parameters (edid, info) ||
        !decode_color_characteristics (edid, info) ||
        !decode_established_timings (edid, info) ||
        !decode_standard_timings (edid, info) ||
        !decode_descriptors (edid, info)) {
	SDL_free(info);
	ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }
    
    ಯದಿ (ಅಂಕೆ_blocks > 1) {
	ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 1; i < ಅಂಕೆ_blocks; ++i) {
	    ಪೂರ್ಣಾಙ್ಕ offset = i * EDID_PAGE_SIZE;
	    uchar extension = edid[offset];
	    ಯದಿ (extension == 0x02) {
		// CTA-861 Extension Block
		decode_cta_block (&edid[offset], info);
	    }
	}
    }

    ಪ್ರತ್ಯಾಗಮ info;
}

ಸ್ಥಿರ ಧ್ರುವ ವರ್ಣ *
yesno (ಪೂರ್ಣಾಙ್ಕ v)
{
    ಪ್ರತ್ಯಾಗಮ v? "yes" : "no";
}

ಶೂನ್ಯ
dump_monitor_info (MonitorInfo *info)
{
    ಪೂರ್ಣಾಙ್ಕ i;
    
    printf ("Checksum: %d (%s)\n",
	    info->checksum, info->checksum? "incorrect" : "correct");
    printf ("Manufacturer Code: %s\n", info->manufacturer_code);
    printf ("Product Code: 0x%x\n", info->product_code);
    printf ("Serial Number: %u\n", info->serial_ಸಂಖ್ಯೆ);
    
    ಯದಿ (info->production_week != -1)
	printf ("Production Week: %d\n", info->production_week);
    ಅನ್ಯಥಾ
	printf ("Production Week: unspecified\n");
    
    ಯದಿ (info->production_year != -1)
	printf ("Production Year: %d\n", info->production_year);
    ಅನ್ಯಥಾ
	printf ("Production Year: unspecified\n");
    
    ಯದಿ (info->model_year != -1)
	printf ("Model Year: %d\n", info->model_year);
    ಅನ್ಯಥಾ
	printf ("Model Year: unspecified\n");
    
    printf ("EDID revision: %d.%d\n", info->major_version, info->minor_version);
    
    printf ("Display is %s\n", info->is_digital? "digital" : "analog");
    ಯದಿ (info->is_digital)
    {
	ಧ್ರುವ ವರ್ಣ *interface;
	ಯದಿ (info->ad.digital.bits_per_primary != -1)
	    printf ("Bits Per Primary: %d\n", info->ad.digital.bits_per_primary);
	ಅನ್ಯಥಾ
	    printf ("Bits Per Primary: undefined\n");
	
	ವಿಕಲ್ಪ (info->ad.digital.interface)
	{
	ಪಕ್ಷ DVI: interface = "DVI"; ಭಙ್ಗ;
	ಪಕ್ಷ HDMI_A: interface = "HDMI-a"; ಭಙ್ಗ;
	ಪಕ್ಷ HDMI_B: interface = "HDMI-b"; ಭಙ್ಗ;
	ಪಕ್ಷ MDDI: interface = "MDDI"; ಭಙ್ಗ;
	ಪಕ್ಷ DISPLAY_PORT: interface = "DisplayPort"; ಭಙ್ಗ;
	ಪಕ್ಷ UNDEFINED: interface = "undefined"; ಭಙ್ಗ;
	ಸ್ವಭಾವ: interface = "unknown"; ಭಙ್ಗ;
	}
	printf ("Interface: %s\n", interface);
	
	printf ("RGB 4:4:4: %s\n", yesno (info->ad.digital.rgb444));
	printf ("YCrCb 4:4:4: %s\n", yesno (info->ad.digital.ycrcb444));
	printf ("YCrCb 4:2:2: %s\n", yesno (info->ad.digital.ycrcb422));
    }
    ಅನ್ಯಥಾ
    {
       ಧ್ರುವ ವರ್ಣ *s;
	printf ("Video Signal Level: %f\n", info->ad.analog.video_signal_level);
	printf ("Sync Signal Level: %f\n", info->ad.analog.sync_signal_level);
	printf ("Total Signal Level: %f\n", info->ad.analog.total_signal_level);
	
	printf ("Blank to Black: %s\n",
		yesno (info->ad.analog.blank_to_black));
	printf ("Separate HV Sync: %s\n",
		yesno (info->ad.analog.separate_hv_sync));
	printf ("Composite Sync on H: %s\n",
		yesno (info->ad.analog.composite_sync_on_h));
	printf ("Serration on VSync: %s\n",
		yesno (info->ad.analog.serration_on_vsync));
	
	ವಿಕಲ್ಪ (info->ad.analog.color_type)
	{
	ಪಕ್ಷ UNDEFINED_COLOR: s = "undefined"; ಭಙ್ಗ;
	ಪಕ್ಷ MONOCHROME: s = "monochrome"; ಭಙ್ಗ;
	ಪಕ್ಷ RGB: s = "rgb"; ಭಙ್ಗ;
	ಪಕ್ಷ OTHER_COLOR: s = "other color"; ಭಙ್ಗ;
	ಸ್ವಭಾವ: s = "unknown"; ಭಙ್ಗ;
	}
	
	printf ("Color: %s\n", s);
    }
    
    ಯದಿ (info->width_mm == -1)
	printf ("Width: undefined\n");
    ಅನ್ಯಥಾ
	printf ("Width: %d mm\n", info->width_mm);
    
    ಯದಿ (info->height_mm == -1)
	printf ("Height: undefined\n");
    ಅನ್ಯಥಾ
	printf ("Height: %d mm\n", info->height_mm);
    
    ಯದಿ (info->aspect_ratio > 0)
	printf ("Aspect Ratio: %f\n", info->aspect_ratio);
    ಅನ್ಯಥಾ
	printf ("Aspect Ratio: undefined\n");
    
    ಯದಿ (info->gamma >= 0)
	printf ("Gamma: %f\n", info->gamma);
    ಅನ್ಯಥಾ
	printf ("Gamma: undefined\n");
    
    printf ("Standby: %s\n", yesno (info->standby));
    printf ("Suspend: %s\n", yesno (info->suspend));
    printf ("Active Off: %s\n", yesno (info->active_off));
    
    printf ("SRGB is Standard: %s\n", yesno (info->srgb_is_standard));
    printf ("Preferred Timing Includes Native: %s\n",
	    yesno (info->preferred_timing_includes_native));
    printf ("Continuous Frequency: %s\n", yesno (info->continuous_frequency));
    
    printf ("Red X: %f\n", info->red_x);
    printf ("Red Y: %f\n", info->red_y);
    printf ("Green X: %f\n", info->green_x);
    printf ("Green Y: %f\n", info->green_y);
    printf ("Blue X: %f\n", info->blue_x);
    printf ("Blue Y: %f\n", info->blue_y);
    printf ("White X: %f\n", info->white_x);
    printf ("White Y: %f\n", info->white_y);
    printf ("Min luminance: %f\n", info->min_luminance);
    printf ("Max luminance: %f\n", info->max_luminance);
    printf ("Max frame average luminance %f\n", info->max_frame_average_luminance);
    
    printf ("Established Timings:\n");
    
    ಪ್ರತಿ (i = 0; i < 24; ++i)
    {
	Timing *timing = &(info->established[i]);
	
	ಯದಿ (timing->frequency == 0)
	    ಭಙ್ಗ;
	
	printf ("  %d x %d @ %d Hz\n",
		timing->width, timing->height, timing->frequency);
	
    }
    
    printf ("Standard Timings:\n");
    ಪ್ರತಿ (i = 0; i < 8; ++i)
    {
	Timing *timing = &(info->standard[i]);
	
	ಯದಿ (timing->frequency == 0)
	    ಭಙ್ಗ;
	
	printf ("  %d x %d @ %d Hz\n",
		timing->width, timing->height, timing->frequency);
    }
    
    ಪ್ರತಿ (i = 0; i < info->n_detailed_timings; ++i)
    {
	DetailedTiming *timing = &(info->detailed_timings[i]);
	ಧ್ರುವ ವರ್ಣ *s;
	
	printf ("Timing%s: \n",
		(i == 0 && info->preferred_timing_includes_native)?
		" (Preferred)" : "");
	printf ("  Pixel Clock: %d\n", timing->pixel_clock);
	printf ("  H Addressable: %d\n", timing->h_addr);
	printf ("  H Blank: %d\n", timing->h_blank);
	printf ("  H Front Porch: %d\n", timing->h_front_porch);
	printf ("  H Sync: %d\n", timing->h_sync);
	printf ("  V Addressable: %d\n", timing->v_addr);
	printf ("  V Blank: %d\n", timing->v_blank);
	printf ("  V Front Porch: %d\n", timing->v_front_porch);
	printf ("  V Sync: %d\n", timing->v_sync);
	printf ("  Width: %d mm\n", timing->width_mm);
	printf ("  Height: %d mm\n", timing->height_mm);
	printf ("  Right Border: %d\n", timing->ಬಲ_border);
	printf ("  Top Border: %d\n", timing->ತುದಿ_border);
	ವಿಕಲ್ಪ (timing->stereo)
	{
	ಸ್ವಭಾವ:
	ಪಕ್ಷ NO_STEREO:   s = "No Stereo"; ಭಙ್ಗ;
	ಪಕ್ಷ FIELD_ಬಲ: s = "Field Sequential, Right on Sync"; ಭಙ್ಗ;
	ಪಕ್ಷ FIELD_ಎಡ:  s = "Field Sequential, Left on Sync"; ಭಙ್ಗ;
	ಪಕ್ಷ TWO_WAY_ಬಲ_ON_EVEN: s = "Two-way, Right on Even"; ಭಙ್ಗ;
	ಪಕ್ಷ TWO_WAY_ಎಡ_ON_EVEN:  s = "Two-way, Left on Even"; ಭಙ್ಗ;
	ಪಕ್ಷ FOUR_WAY_INTERLEAVED:  s = "Four-way Interleaved"; ಭಙ್ಗ;
	ಪಕ್ಷ SIDE_BY_SIDE:          s = "Side-by-Side"; ಭಙ್ಗ;
	}
	printf ("  Stereo: %s\n", s);
	
	ಯದಿ (timing->digital_sync)
	{
	    printf ("  Digital Sync:\n");
	    printf ("    composite: %s\n", yesno (timing->ad.digital.composite));
	    printf ("    serrations: %s\n", yesno (timing->ad.digital.serrations));
	    printf ("    negative vsync: %s\n",
		    yesno (timing->ad.digital.negative_vsync));
	    printf ("    negative hsync: %s\n",
		    yesno (timing->ad.digital.negative_hsync));
	}
	ಅನ್ಯಥಾ
	{
	    printf ("  Analog Sync:\n");
	    printf ("    bipolar: %s\n", yesno (timing->ad.analog.bipolar));
	    printf ("    serrations: %s\n", yesno (timing->ad.analog.serrations));
	    printf ("    sync on green: %s\n", yesno (
			timing->ad.analog.sync_on_green));
	}
    }
    
    printf ("Detailed Product information:\n");
    printf ("  Product Name: %s\n", info->dsc_product_name);
    printf ("  Serial Number: %s\n", info->dsc_serial_ಸಂಖ್ಯೆ);
    printf ("  Unspecified String: %s\n", info->dsc_string);
}

