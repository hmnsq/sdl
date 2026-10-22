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
#include "SDL_internal.h"

#include "edid.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdio.h>

#define TRUE 1
#define FALSE 0

static цяло
get_bit (цяло in, цяло bit)
{
    върни (in & (1 << bit)) >> bit;
}

static цяло
get_bits (цяло in, цяло begin, цяло end)
{
    цяло mask = (1 << (end - begin + 1)) - 1;
    
    върни (in >> begin) & mask;
}

static цяло
decode_header (const uchar *edid)
{
    ако (SDL_memcmp (edid, "\x00\xff\xff\xff\xff\xff\xff\x00", 8) == 0)
	върни TRUE;
    върни FALSE;
}

static цяло
decode_vendor_and_product_identification (const uchar *edid, MonitorInfo *info)
{
    цяло is_model_year;
    
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
    info->serial_number =
	edid[0x0c] | edid[0x0d] << 8 | edid[0x0e] << 16 | (Uint32)edid[0x0f] << 24;

    /* Week and Year */
    is_model_year = FALSE;
    switch (edid[0x10])
    {
    case 0x00:
	info->production_week = -1;
	break;

    case 0xff:
	info->production_week = -1;
	is_model_year = TRUE;
	break;

    default:
	info->production_week = edid[0x10];
	break;
    }

    ако (is_model_year)
    {
	info->production_year = -1;
	info->model_year = 1990 + edid[0x11];
    }
    иначе
    {
	info->production_year = 1990 + edid[0x11];
	info->model_year = -1;
    }

    върни TRUE;
}

static цяло
decode_edid_version (const uchar *edid, MonitorInfo *info)
{
    info->major_version = edid[0x12];
    info->minor_version = edid[0x13];

    върни TRUE;
}

static цяло
decode_display_parameters (const uchar *edid, MonitorInfo *info)
{
    /* Digital vs Analog */
    info->is_digital = get_bit (edid[0x14], 7);

    ако (info->is_digital)
    {
	цяло bits;
	
	static const цяло bit_depth[8] =
	{
	    -1, 6, 8, 10, 12, 14, 16, -1
	};

	static const Interface interfaces[6] =
	{
	    UNDEFINED, DVI, HDMI_A, HDMI_B, MDDI, DISPLAY_PORT
	};

	bits = get_bits (edid[0x14], 4, 6);
	info->ad.digital.bits_per_primary = bit_depth[bits];

	bits = get_bits (edid[0x14], 0, 3);
	
	ако (bits <= 5)
	    info->ad.digital.interface = interfaces[bits];
	иначе
	    info->ad.digital.interface = UNDEFINED;
    }
    иначе
    {
	цяло bits = get_bits (edid[0x14], 5, 6);
	
	static const double levels[][3] =
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
    ако (edid[0x15] == 0 && edid[0x16] == 0)
    {
	info->width_mm = -1;
	info->height_mm = -1;
	info->aspect_ratio = -1.0;
    }
    иначе ако (edid[0x16] == 0)
    {
	info->width_mm = -1;
	info->height_mm = -1; 
	info->aspect_ratio = 100.0 / (edid[0x15] + 99);
    }
    иначе ако (edid[0x15] == 0)
    {
	info->width_mm = -1;
	info->height_mm = -1;
	info->aspect_ratio = 100.0 / (edid[0x16] + 99);
	info->aspect_ratio = 1/info->aspect_ratio; /* portrait */
    }
    иначе
    {
	info->width_mm = 10 * edid[0x15];
	info->height_mm = 10 * edid[0x16];
    }

    /* Gamma */
    ако (edid[0x17] == 0xFF)
	info->gamma = -1.0;
    иначе
	info->gamma = (edid[0x17] + 100.0) / 100.0;

    /* Features */
    info->standby = get_bit (edid[0x18], 7);
    info->suspend = get_bit (edid[0x18], 6);
    info->active_off = get_bit (edid[0x18], 5);

    ако (info->is_digital)
    {
	info->ad.digital.rgb444 = TRUE;
	ако (get_bit (edid[0x18], 3))
	    info->ad.digital.ycrcb444 = 1;
	ако (get_bit (edid[0x18], 4))
	    info->ad.digital.ycrcb422 = 1;
    }
    иначе
    {
	цяло bits = get_bits (edid[0x18], 3, 4);
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
    върни TRUE;
}

static double
decode_fraction (цяло high, цяло low)
{
    double result = 0.0;
    цяло i;

    high = (high << 2) | low;

    за (i = 0; i < 10; ++i)
	result += get_bit (high, i) * SDL_pow (2, i - 10);

    върни result;
}

static цяло
decode_color_characteristics (const uchar *edid, MonitorInfo *info)
{
    info->red_x = decode_fraction (edid[0x1b], get_bits (edid[0x19], 6, 7));
    info->red_y = decode_fraction (edid[0x1c], get_bits (edid[0x19], 5, 4));
    info->green_x = decode_fraction (edid[0x1d], get_bits (edid[0x19], 2, 3));
    info->green_y = decode_fraction (edid[0x1e], get_bits (edid[0x19], 0, 1));
    info->blue_x = decode_fraction (edid[0x1f], get_bits (edid[0x1a], 6, 7));
    info->blue_y = decode_fraction (edid[0x20], get_bits (edid[0x1a], 4, 5));
    info->white_x = decode_fraction (edid[0x21], get_bits (edid[0x1a], 2, 3));
    info->white_y = decode_fraction (edid[0x22], get_bits (edid[0x1a], 0, 1));

    върни TRUE;
}

static цяло
decode_established_timings (const uchar *edid, MonitorInfo *info)
{
    static const Timing established[][8] = 
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

    цяло i, j, idx;

    idx = 0;
    за (i = 0; i < 3; ++i)
    {
	за (j = 0; j < 8; ++j)
	{
	    цяло byte = edid[0x23 + i];

	    ако (get_bit (byte, j) && established[i][j].frequency != 0)
		info->established[idx++] = established[i][j];
	}
    }
    върни TRUE;
}

static цяло
decode_standard_timings (const uchar *edid, MonitorInfo *info)
{
    цяло i;
    
    за (i = 0; i < 8; i++)
    {
	цяло first = edid[0x26 + 2 * i];
	цяло second = edid[0x27 + 2 * i];

	ако (first != 0x01 && second != 0x01)
	{
	    цяло w = 8 * (first + 31);
	    цяло h = 0;

	    switch (get_bits (second, 6, 7))
	    {
	    case 0x00: h = (w / 16) * 10; break;
	    case 0x01: h = (w / 4) * 3; break;
	    case 0x02: h = (w / 5) * 4; break;
	    case 0x03: h = (w / 16) * 9; break;
	    }

	    info->standard[i].width = w;
	    info->standard[i].height = h;
	    info->standard[i].frequency = get_bits (second, 0, 5) + 60;
	}
    }
    
    върни TRUE;
}

static void
decode_lf_string (const uchar *s, цяло n_chars, char *result)
{
    цяло i;
    за (i = 0; i < n_chars; ++i)
    {
	ако (s[i] == 0x0a)
	{
	    *result++ = '\0';
	    break;
	}
	иначе ако (s[i] == 0x00)
	{
	    /* Convert embedded 0's to spaces */
	    *result++ = ' ';
	}
	иначе
	{
	    *result++ = s[i];
	}
    }
}

static void
decode_display_descriptor (const uchar *desc,
			   MonitorInfo *info)
{
    switch (desc[0x03])
    {
    case 0xFC:
	decode_lf_string (desc + 5, 13, info->dsc_product_name);
	break;
    case 0xFF:
	decode_lf_string (desc + 5, 13, info->dsc_serial_number);
	break;
    case 0xFE:
	decode_lf_string (desc + 5, 13, info->dsc_string);
	break;
    case 0xFD:
	/* Range Limits */
	break;
    case 0xFB:
	/* Color Point */
	break;
    case 0xFA:
	/* Timing Identifications */
	break;
    case 0xF9:
	/* Color Management */
	break;
    case 0xF8:
	/* Timing Codes */
	break;
    case 0xF7:
	/* Established Timings */
	break;
    case 0x10:
	break;
    }
}

static void
decode_detailed_timing (const uchar *timing,
			DetailedTiming *detailed)
{
    цяло bits;
    StereoType stereo[] =
    {
	NO_STEREO, NO_STEREO, FIELD_RIGHT, FIELD_LEFT,
	TWO_WAY_RIGHT_ON_EVEN, TWO_WAY_LEFT_ON_EVEN,
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
    detailed->right_border = timing[0x0f];
    detailed->top_border = timing[0x10];

    detailed->interlaced = get_bit (timing[0x11], 7);

    /* Stereo */
    bits = get_bits (timing[0x11], 5, 6) << 1 | get_bit (timing[0x11], 0);
    detailed->stereo = stereo[bits];

    /* Sync */
    bits = timing[0x11];

    detailed->digital_sync = get_bit (bits, 4);
    ако (detailed->digital_sync)
    {
	detailed->ad.digital.composite = !get_bit (bits, 3);

	ако (detailed->ad.digital.composite)
	{
	    detailed->ad.digital.serrations = get_bit (bits, 2);
	    detailed->ad.digital.negative_vsync = FALSE;
	}
	иначе
	{
	    detailed->ad.digital.serrations = FALSE;
	    detailed->ad.digital.negative_vsync = !get_bit (bits, 2);
	}

	detailed->ad.digital.negative_hsync = !get_bit (bits, 0);
    }
    иначе
    {
	detailed->ad.analog.bipolar = get_bit (bits, 3);
	detailed->ad.analog.serrations = get_bit (bits, 2);
	detailed->ad.analog.sync_on_green = !get_bit (bits, 1);
    }
}

static цяло
decode_descriptors (const uchar *edid, MonitorInfo *info)
{
    цяло i;
    цяло timing_idx;
    
    timing_idx = 0;
    
    за (i = 0; i < 4; ++i)
    {
	цяло index = 0x36 + i * 18;

	ако (edid[index + 0] == 0x00 && edid[index + 1] == 0x00)
	{
	    decode_display_descriptor (edid + index, info);
	}
	иначе
	{
	    decode_detailed_timing (
		edid + index, &(info->detailed_timings[timing_idx++]));
	}
    }

    info->n_detailed_timings = timing_idx;

    върни TRUE;
}

static void
decode_check_sum (const uchar *edid,
		  MonitorInfo *info)
{
    цяло i;
    uchar check = 0;

    за (i = 0; i < 128; ++i)
	check += edid[i];

    info->checksum = check;
}

static void
decode_HDR_metadata_block (const uchar *data, цяло length, MonitorInfo *info)
{
    ако (length >= 3)
	info->max_luminance = 50.0 * SDL_pow(2, data[2] / 32.0);

    ако (length >= 4)
	info->max_frame_average_luminance = 50.0 * SDL_pow(2, data[3] / 32.0);

    ако (length >= 5)
	info->min_luminance = 50.0 * SDL_pow(2, data[4] / 32.0);
}


static void
decode_cta_block (const uchar *edid,
		  MonitorInfo *info)
{
    цяло offset = 4;
    докато (offset < 128) {
	цяло length = edid[offset] & 0x1f;
	цяло type = edid[offset] >> 5;
	ако (length == 0) {
	    break;
	}
	ако (type == 7) {
	    type <<= 8;
	    type |= edid[offset + 1];
	}
	ако (type == 0x706) {
	    decode_HDR_metadata_block (&edid[offset + 2], length - 1, info);
	}
	offset += (1 + length);
    }
}

MonitorInfo *
decode_edid (const uchar *edid, size_t size)
{
    const цяло EDID_PAGE_SIZE = 128;
    цяло num_blocks = (size / EDID_PAGE_SIZE);
    MonitorInfo *info;

    ако ((size % EDID_PAGE_SIZE) != 0) {
	върни NULL;
    }

    info = SDL_calloc (1, sizeof (MonitorInfo));

    decode_check_sum (edid, info);
    
    ако (!decode_header (edid) ||
        !decode_vendor_and_product_identification (edid, info) ||
        !decode_edid_version (edid, info) ||
        !decode_display_parameters (edid, info) ||
        !decode_color_characteristics (edid, info) ||
        !decode_established_timings (edid, info) ||
        !decode_standard_timings (edid, info) ||
        !decode_descriptors (edid, info)) {
	SDL_free(info);
	върни NULL;
    }
    
    ако (num_blocks > 1) {
	за (цяло i = 1; i < num_blocks; ++i) {
	    цяло offset = i * EDID_PAGE_SIZE;
	    uchar extension = edid[offset];
	    ако (extension == 0x02) {
		// CTA-861 Extension Block
		decode_cta_block (&edid[offset], info);
	    }
	}
    }

    върни info;
}

static const char *
yesno (цяло v)
{
    върни v? "yes" : "no";
}

void
dump_monitor_info (MonitorInfo *info)
{
    цяло i;
    
    printf ("Checksum: %d (%s)\n",
	    info->checksum, info->checksum? "incorrect" : "correct");
    printf ("Manufacturer Code: %s\n", info->manufacturer_code);
    printf ("Product Code: 0x%x\n", info->product_code);
    printf ("Serial Number: %u\n", info->serial_number);
    
    ако (info->production_week != -1)
	printf ("Production Week: %d\n", info->production_week);
    иначе
	printf ("Production Week: unspecified\n");
    
    ако (info->production_year != -1)
	printf ("Production Year: %d\n", info->production_year);
    иначе
	printf ("Production Year: unspecified\n");
    
    ако (info->model_year != -1)
	printf ("Model Year: %d\n", info->model_year);
    иначе
	printf ("Model Year: unspecified\n");
    
    printf ("EDID revision: %d.%d\n", info->major_version, info->minor_version);
    
    printf ("Display is %s\n", info->is_digital? "digital" : "analog");
    ако (info->is_digital)
    {
	const char *interface;
	ако (info->ad.digital.bits_per_primary != -1)
	    printf ("Bits Per Primary: %d\n", info->ad.digital.bits_per_primary);
	иначе
	    printf ("Bits Per Primary: undefined\n");
	
	switch (info->ad.digital.interface)
	{
	case DVI: interface = "DVI"; break;
	case HDMI_A: interface = "HDMI-a"; break;
	case HDMI_B: interface = "HDMI-b"; break;
	case MDDI: interface = "MDDI"; break;
	case DISPLAY_PORT: interface = "DisplayPort"; break;
	case UNDEFINED: interface = "undefined"; break;
	default: interface = "unknown"; break;
	}
	printf ("Interface: %s\n", interface);
	
	printf ("RGB 4:4:4: %s\n", yesno (info->ad.digital.rgb444));
	printf ("YCrCb 4:4:4: %s\n", yesno (info->ad.digital.ycrcb444));
	printf ("YCrCb 4:2:2: %s\n", yesno (info->ad.digital.ycrcb422));
    }
    иначе
    {
       const char *s;
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
	
	switch (info->ad.analog.color_type)
	{
	case UNDEFINED_COLOR: s = "undefined"; break;
	case MONOCHROME: s = "monochrome"; break;
	case RGB: s = "rgb"; break;
	case OTHER_COLOR: s = "other color"; break;
	default: s = "unknown"; break;
	}
	
	printf ("Color: %s\n", s);
    }
    
    ако (info->width_mm == -1)
	printf ("Width: undefined\n");
    иначе
	printf ("Width: %d mm\n", info->width_mm);
    
    ако (info->height_mm == -1)
	printf ("Height: undefined\n");
    иначе
	printf ("Height: %d mm\n", info->height_mm);
    
    ако (info->aspect_ratio > 0)
	printf ("Aspect Ratio: %f\n", info->aspect_ratio);
    иначе
	printf ("Aspect Ratio: undefined\n");
    
    ако (info->gamma >= 0)
	printf ("Gamma: %f\n", info->gamma);
    иначе
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
    
    за (i = 0; i < 24; ++i)
    {
	Timing *timing = &(info->established[i]);
	
	ако (timing->frequency == 0)
	    break;
	
	printf ("  %d x %d @ %d Hz\n",
		timing->width, timing->height, timing->frequency);
	
    }
    
    printf ("Standard Timings:\n");
    за (i = 0; i < 8; ++i)
    {
	Timing *timing = &(info->standard[i]);
	
	ако (timing->frequency == 0)
	    break;
	
	printf ("  %d x %d @ %d Hz\n",
		timing->width, timing->height, timing->frequency);
    }
    
    за (i = 0; i < info->n_detailed_timings; ++i)
    {
	DetailedTiming *timing = &(info->detailed_timings[i]);
	const char *s;
	
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
	printf ("  Right Border: %d\n", timing->right_border);
	printf ("  Top Border: %d\n", timing->top_border);
	switch (timing->stereo)
	{
	default:
	case NO_STEREO:   s = "No Stereo"; break;
	case FIELD_RIGHT: s = "Field Sequential, Right on Sync"; break;
	case FIELD_LEFT:  s = "Field Sequential, Left on Sync"; break;
	case TWO_WAY_RIGHT_ON_EVEN: s = "Two-way, Right on Even"; break;
	case TWO_WAY_LEFT_ON_EVEN:  s = "Two-way, Left on Even"; break;
	case FOUR_WAY_INTERLEAVED:  s = "Four-way Interleaved"; break;
	case SIDE_BY_SIDE:          s = "Side-by-Side"; break;
	}
	printf ("  Stereo: %s\n", s);
	
	ако (timing->digital_sync)
	{
	    printf ("  Digital Sync:\n");
	    printf ("    composite: %s\n", yesno (timing->ad.digital.composite));
	    printf ("    serrations: %s\n", yesno (timing->ad.digital.serrations));
	    printf ("    negative vsync: %s\n",
		    yesno (timing->ad.digital.negative_vsync));
	    printf ("    negative hsync: %s\n",
		    yesno (timing->ad.digital.negative_hsync));
	}
	иначе
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
    printf ("  Serial Number: %s\n", info->dsc_serial_number);
    printf ("  Unspecified String: %s\n", info->dsc_string);
}

