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
#ଅନ୍ତର୍ଭାଵ "SDL_internal.h"

#ଅନ୍ତର୍ଭାଵ "edid.h"
#ଅନ୍ତର୍ଭାଵ <stdlib.h>
#ଅନ୍ତର୍ଭାଵ <string.h>
#ଅନ୍ତର୍ଭାଵ <math.h>
#ଅନ୍ତର୍ଭାଵ <stdio.h>

#define TRUE 1
#define FALSE 0

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା
get_bit (ପୂର୍ଣ୍ଣସଂଖ୍ୟା in, ପୂର୍ଣ୍ଣସଂଖ୍ୟା bit)
{
    ଫେରନ୍ତୁ (in & (1 << bit)) >> bit;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା
get_bits (ପୂର୍ଣ୍ଣସଂଖ୍ୟା in, ପୂର୍ଣ୍ଣସଂଖ୍ୟା begin, ପୂର୍ଣ୍ଣସଂଖ୍ୟା end)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା mask = (1 << (end - begin + 1)) - 1;
    
    ଫେରନ୍ତୁ (in >> begin) & mask;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା
decode_header (ଅଚଳ uchar *edid)
{
    ଯଦି (SDL_memcmp (edid, "\x00\xff\xff\xff\xff\xff\xff\x00", 8) == 0)
	ଫେରନ୍ତୁ TRUE;
    ଫେରନ୍ତୁ FALSE;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା
decode_vendor_and_product_identification (ଅଚଳ uchar *edid, MonitorInfo *info)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା is_model_year;
    
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
    info->serial_ସଂଖ୍ୟା =
	edid[0x0c] | edid[0x0d] << 8 | edid[0x0e] << 16 | (Uint32)edid[0x0f] << 24;

    /* Week and Year */
    is_model_year = FALSE;
    ବାଛ (edid[0x10])
    {
    ସ୍ଥିତି 0x00:
	info->production_week = -1;
	ଭାଙ୍ଗ;

    ସ୍ଥିତି 0xff:
	info->production_week = -1;
	is_model_year = TRUE;
	ଭାଙ୍ଗ;

    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
	info->production_week = edid[0x10];
	ଭାଙ୍ଗ;
    }

    ଯଦି (is_model_year)
    {
	info->production_year = -1;
	info->model_year = 1990 + edid[0x11];
    }
    ଅନ୍ୟଥା
    {
	info->production_year = 1990 + edid[0x11];
	info->model_year = -1;
    }

    ଫେରନ୍ତୁ TRUE;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା
decode_edid_version (ଅଚଳ uchar *edid, MonitorInfo *info)
{
    info->major_version = edid[0x12];
    info->minor_version = edid[0x13];

    ଫେରନ୍ତୁ TRUE;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା
decode_display_parameters (ଅଚଳ uchar *edid, MonitorInfo *info)
{
    /* Digital vs Analog */
    info->is_digital = get_bit (edid[0x14], 7);

    ଯଦି (info->is_digital)
    {
	ପୂର୍ଣ୍ଣସଂଖ୍ୟା bits;
	
	ସ୍ଥିର ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା bit_depth[8] =
	{
	    -1, 6, 8, 10, 12, 14, 16, -1
	};

	ସ୍ଥିର ଅଚଳ Interface interfaces[6] =
	{
	    UNDEFINED, DVI, HDMI_A, HDMI_B, MDDI, DISPLAY_PORT
	};

	bits = get_bits (edid[0x14], 4, 6);
	info->ad.digital.bits_per_primary = bit_depth[bits];

	bits = get_bits (edid[0x14], 0, 3);
	
	ଯଦି (bits <= 5)
	    info->ad.digital.interface = interfaces[bits];
	ଅନ୍ୟଥା
	    info->ad.digital.interface = UNDEFINED;
    }
    ଅନ୍ୟଥା
    {
	ପୂର୍ଣ୍ଣସଂଖ୍ୟା bits = get_bits (edid[0x14], 5, 6);
	
	ସ୍ଥିର ଅଚଳ ଦ୍ୱିଗୁଣ levels[][3] =
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
    ଯଦି (edid[0x15] == 0 && edid[0x16] == 0)
    {
	info->width_mm = -1;
	info->height_mm = -1;
	info->aspect_ratio = -1.0;
    }
    ଅନ୍ୟଥା ଯଦି (edid[0x16] == 0)
    {
	info->width_mm = -1;
	info->height_mm = -1; 
	info->aspect_ratio = 100.0 / (edid[0x15] + 99);
    }
    ଅନ୍ୟଥା ଯଦି (edid[0x15] == 0)
    {
	info->width_mm = -1;
	info->height_mm = -1;
	info->aspect_ratio = 100.0 / (edid[0x16] + 99);
	info->aspect_ratio = 1/info->aspect_ratio; /* portrait */
    }
    ଅନ୍ୟଥା
    {
	info->width_mm = 10 * edid[0x15];
	info->height_mm = 10 * edid[0x16];
    }

    /* Gamma */
    ଯଦି (edid[0x17] == 0xFF)
	info->gamma = -1.0;
    ଅନ୍ୟଥା
	info->gamma = (edid[0x17] + 100.0) / 100.0;

    /* Features */
    info->standby = get_bit (edid[0x18], 7);
    info->suspend = get_bit (edid[0x18], 6);
    info->active_off = get_bit (edid[0x18], 5);

    ଯଦି (info->is_digital)
    {
	info->ad.digital.rgb444 = TRUE;
	ଯଦି (get_bit (edid[0x18], 3))
	    info->ad.digital.ycrcb444 = 1;
	ଯଦି (get_bit (edid[0x18], 4))
	    info->ad.digital.ycrcb422 = 1;
    }
    ଅନ୍ୟଥା
    {
	ପୂର୍ଣ୍ଣସଂଖ୍ୟା bits = get_bits (edid[0x18], 3, 4);
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
    ଫେରନ୍ତୁ TRUE;
}

ସ୍ଥିର ଦ୍ୱିଗୁଣ
decode_fraction (ପୂର୍ଣ୍ଣସଂଖ୍ୟା ଉପର, ପୂର୍ଣ୍ଣସଂଖ୍ୟା ତଳ)
{
    ଦ୍ୱିଗୁଣ result = 0.0;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i;

    ଉପର = (ଉପର << 2) | ତଳ;

    ପାଇଁ (i = 0; i < 10; ++i)
	result += get_bit (ଉପର, i) * SDL_pow (2, i - 10);

    ଫେରନ୍ତୁ result;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା
decode_color_characteristics (ଅଚଳ uchar *edid, MonitorInfo *info)
{
    info->red_x = decode_fraction (edid[0x1b], get_bits (edid[0x19], 6, 7));
    info->red_y = decode_fraction (edid[0x1c], get_bits (edid[0x19], 5, 4));
    info->green_x = decode_fraction (edid[0x1d], get_bits (edid[0x19], 2, 3));
    info->green_y = decode_fraction (edid[0x1e], get_bits (edid[0x19], 0, 1));
    info->blue_x = decode_fraction (edid[0x1f], get_bits (edid[0x1a], 6, 7));
    info->blue_y = decode_fraction (edid[0x20], get_bits (edid[0x1a], 4, 5));
    info->white_x = decode_fraction (edid[0x21], get_bits (edid[0x1a], 2, 3));
    info->white_y = decode_fraction (edid[0x22], get_bits (edid[0x1a], 0, 1));

    ଫେରନ୍ତୁ TRUE;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା
decode_established_timings (ଅଚଳ uchar *edid, MonitorInfo *info)
{
    ସ୍ଥିର ଅଚଳ Timing established[][8] = 
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

    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i, j, idx;

    idx = 0;
    ପାଇଁ (i = 0; i < 3; ++i)
    {
	ପାଇଁ (j = 0; j < 8; ++j)
	{
	    ପୂର୍ଣ୍ଣସଂଖ୍ୟା byte = edid[0x23 + i];

	    ଯଦି (get_bit (byte, j) && established[i][j].frequency != 0)
		info->established[idx++] = established[i][j];
	}
    }
    ଫେରନ୍ତୁ TRUE;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା
decode_standard_timings (ଅଚଳ uchar *edid, MonitorInfo *info)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i;
    
    ପାଇଁ (i = 0; i < 8; i++)
    {
	ପୂର୍ଣ୍ଣସଂଖ୍ୟା first = edid[0x26 + 2 * i];
	ପୂର୍ଣ୍ଣସଂଖ୍ୟା second = edid[0x27 + 2 * i];

	ଯଦି (first != 0x01 && second != 0x01)
	{
	    ପୂର୍ଣ୍ଣସଂଖ୍ୟା w = 8 * (first + 31);
	    ପୂର୍ଣ୍ଣସଂଖ୍ୟା h = 0;

	    ବାଛ (get_bits (second, 6, 7))
	    {
	    ସ୍ଥିତି 0x00: h = (w / 16) * 10; ଭାଙ୍ଗ;
	    ସ୍ଥିତି 0x01: h = (w / 4) * 3; ଭାଙ୍ଗ;
	    ସ୍ଥିତି 0x02: h = (w / 5) * 4; ଭାଙ୍ଗ;
	    ସ୍ଥିତି 0x03: h = (w / 16) * 9; ଭାଙ୍ଗ;
	    }

	    info->standard[i].width = w;
	    info->standard[i].height = h;
	    info->standard[i].frequency = get_bits (second, 0, 5) + 60;
	}
    }
    
    ଫେରନ୍ତୁ TRUE;
}

ସ୍ଥିର ଶୂନ୍ୟ
decode_lf_string (ଅଚଳ uchar *s, ପୂର୍ଣ୍ଣସଂଖ୍ୟା n_chars, ଅକ୍ଷର *result)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i;
    ପାଇଁ (i = 0; i < n_chars; ++i)
    {
	ଯଦି (s[i] == 0x0a)
	{
	    *result++ = '\0';
	    ଭାଙ୍ଗ;
	}
	ଅନ୍ୟଥା ଯଦି (s[i] == 0x00)
	{
	    /* Convert embedded 0's to spaces */
	    *result++ = ' ';
	}
	ଅନ୍ୟଥା
	{
	    *result++ = s[i];
	}
    }
}

ସ୍ଥିର ଶୂନ୍ୟ
decode_display_descriptor (ଅଚଳ uchar *desc,
			   MonitorInfo *info)
{
    ବାଛ (desc[0x03])
    {
    ସ୍ଥିତି 0xFC:
	decode_lf_string (desc + 5, 13, info->dsc_product_name);
	ଭାଙ୍ଗ;
    ସ୍ଥିତି 0xFF:
	decode_lf_string (desc + 5, 13, info->dsc_serial_ସଂଖ୍ୟା);
	ଭାଙ୍ଗ;
    ସ୍ଥିତି 0xFE:
	decode_lf_string (desc + 5, 13, info->dsc_string);
	ଭାଙ୍ଗ;
    ସ୍ଥିତି 0xFD:
	/* Range Limits */
	ଭାଙ୍ଗ;
    ସ୍ଥିତି 0xFB:
	/* Color Point */
	ଭାଙ୍ଗ;
    ସ୍ଥିତି 0xFA:
	/* Timing Identifications */
	ଭାଙ୍ଗ;
    ସ୍ଥିତି 0xF9:
	/* Color Management */
	ଭାଙ୍ଗ;
    ସ୍ଥିତି 0xF8:
	/* Timing Codes */
	ଭାଙ୍ଗ;
    ସ୍ଥିତି 0xF7:
	/* Established Timings */
	ଭାଙ୍ଗ;
    ସ୍ଥିତି 0x10:
	ଭାଙ୍ଗ;
    }
}

ସ୍ଥିର ଶୂନ୍ୟ
decode_detailed_timing (ଅଚଳ uchar *timing,
			DetailedTiming *detailed)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା bits;
    StereoType stereo[] =
    {
	NO_STEREO, NO_STEREO, FIELD_ଡାହାଣ, FIELD_ବାମ,
	TWO_WAY_ଡାହାଣ_ON_EVEN, TWO_WAY_ବାମ_ON_EVEN,
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
    detailed->ଡାହାଣ_border = timing[0x0f];
    detailed->ଶୀର୍ଷ_border = timing[0x10];

    detailed->interlaced = get_bit (timing[0x11], 7);

    /* Stereo */
    bits = get_bits (timing[0x11], 5, 6) << 1 | get_bit (timing[0x11], 0);
    detailed->stereo = stereo[bits];

    /* Sync */
    bits = timing[0x11];

    detailed->digital_sync = get_bit (bits, 4);
    ଯଦି (detailed->digital_sync)
    {
	detailed->ad.digital.composite = !get_bit (bits, 3);

	ଯଦି (detailed->ad.digital.composite)
	{
	    detailed->ad.digital.serrations = get_bit (bits, 2);
	    detailed->ad.digital.negative_vsync = FALSE;
	}
	ଅନ୍ୟଥା
	{
	    detailed->ad.digital.serrations = FALSE;
	    detailed->ad.digital.negative_vsync = !get_bit (bits, 2);
	}

	detailed->ad.digital.negative_hsync = !get_bit (bits, 0);
    }
    ଅନ୍ୟଥା
    {
	detailed->ad.analog.bipolar = get_bit (bits, 3);
	detailed->ad.analog.serrations = get_bit (bits, 2);
	detailed->ad.analog.sync_on_green = !get_bit (bits, 1);
    }
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା
decode_descriptors (ଅଚଳ uchar *edid, MonitorInfo *info)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା timing_idx;
    
    timing_idx = 0;
    
    ପାଇଁ (i = 0; i < 4; ++i)
    {
	ପୂର୍ଣ୍ଣସଂଖ୍ୟା index = 0x36 + i * 18;

	ଯଦି (edid[index + 0] == 0x00 && edid[index + 1] == 0x00)
	{
	    decode_display_descriptor (edid + index, info);
	}
	ଅନ୍ୟଥା
	{
	    decode_detailed_timing (
		edid + index, &(info->detailed_timings[timing_idx++]));
	}
    }

    info->n_detailed_timings = timing_idx;

    ଫେରନ୍ତୁ TRUE;
}

ସ୍ଥିର ଶୂନ୍ୟ
decode_check_sum (ଅଚଳ uchar *edid,
		  MonitorInfo *info)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i;
    uchar check = 0;

    ପାଇଁ (i = 0; i < 128; ++i)
	check += edid[i];

    info->checksum = check;
}

ସ୍ଥିର ଶୂନ୍ୟ
decode_HDR_metadata_block (ଅଚଳ uchar *data, ପୂର୍ଣ୍ଣସଂଖ୍ୟା length, MonitorInfo *info)
{
    ଯଦି (length >= 3)
	info->max_luminance = 50.0 * SDL_pow(2, data[2] / 32.0);

    ଯଦି (length >= 4)
	info->max_frame_average_luminance = 50.0 * SDL_pow(2, data[3] / 32.0);

    ଯଦି (length >= 5)
	info->min_luminance = 50.0 * SDL_pow(2, data[4] / 32.0);
}


ସ୍ଥିର ଶୂନ୍ୟ
decode_cta_block (ଅଚଳ uchar *edid,
		  MonitorInfo *info)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା offset = 4;
    ଯେତେବେଳେ (offset < 128) {
	ପୂର୍ଣ୍ଣସଂଖ୍ୟା length = edid[offset] & 0x1f;
	ପୂର୍ଣ୍ଣସଂଖ୍ୟା type = edid[offset] >> 5;
	ଯଦି (length == 0) {
	    ଭାଙ୍ଗ;
	}
	ଯଦି (type == 7) {
	    type <<= 8;
	    type |= edid[offset + 1];
	}
	ଯଦି (type == 0x706) {
	    decode_HDR_metadata_block (&edid[offset + 2], length - 1, info);
	}
	offset += (1 + length);
    }
}

MonitorInfo *
decode_edid (ଅଚଳ uchar *edid, size_t size)
{
    ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା EDID_PAGE_SIZE = 128;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ଅଙ୍କ_blocks = (size / EDID_PAGE_SIZE);
    MonitorInfo *info;

    ଯଦି ((size % EDID_PAGE_SIZE) != 0) {
	ଫେରନ୍ତୁ ଖାଲି;
    }

    info = SDL_calloc (1, ଆକାର (MonitorInfo));

    decode_check_sum (edid, info);
    
    ଯଦି (!decode_header (edid) ||
        !decode_vendor_and_product_identification (edid, info) ||
        !decode_edid_version (edid, info) ||
        !decode_display_parameters (edid, info) ||
        !decode_color_characteristics (edid, info) ||
        !decode_established_timings (edid, info) ||
        !decode_standard_timings (edid, info) ||
        !decode_descriptors (edid, info)) {
	SDL_free(info);
	ଫେରନ୍ତୁ ଖାଲି;
    }
    
    ଯଦି (ଅଙ୍କ_blocks > 1) {
	ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 1; i < ଅଙ୍କ_blocks; ++i) {
	    ପୂର୍ଣ୍ଣସଂଖ୍ୟା offset = i * EDID_PAGE_SIZE;
	    uchar extension = edid[offset];
	    ଯଦି (extension == 0x02) {
		// CTA-861 Extension Block
		decode_cta_block (&edid[offset], info);
	    }
	}
    }

    ଫେରନ୍ତୁ info;
}

ସ୍ଥିର ଅଚଳ ଅକ୍ଷର *
yesno (ପୂର୍ଣ୍ଣସଂଖ୍ୟା v)
{
    ଫେରନ୍ତୁ v? "yes" : "no";
}

ଶୂନ୍ୟ
dump_monitor_info (MonitorInfo *info)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i;
    
    printf ("Checksum: %d (%s)\n",
	    info->checksum, info->checksum? "incorrect" : "correct");
    printf ("Manufacturer Code: %s\n", info->manufacturer_code);
    printf ("Product Code: 0x%x\n", info->product_code);
    printf ("Serial Number: %u\n", info->serial_ସଂଖ୍ୟା);
    
    ଯଦି (info->production_week != -1)
	printf ("Production Week: %d\n", info->production_week);
    ଅନ୍ୟଥା
	printf ("Production Week: unspecified\n");
    
    ଯଦି (info->production_year != -1)
	printf ("Production Year: %d\n", info->production_year);
    ଅନ୍ୟଥା
	printf ("Production Year: unspecified\n");
    
    ଯଦି (info->model_year != -1)
	printf ("Model Year: %d\n", info->model_year);
    ଅନ୍ୟଥା
	printf ("Model Year: unspecified\n");
    
    printf ("EDID revision: %d.%d\n", info->major_version, info->minor_version);
    
    printf ("Display is %s\n", info->is_digital? "digital" : "analog");
    ଯଦି (info->is_digital)
    {
	ଅଚଳ ଅକ୍ଷର *interface;
	ଯଦି (info->ad.digital.bits_per_primary != -1)
	    printf ("Bits Per Primary: %d\n", info->ad.digital.bits_per_primary);
	ଅନ୍ୟଥା
	    printf ("Bits Per Primary: undefined\n");
	
	ବାଛ (info->ad.digital.interface)
	{
	ସ୍ଥିତି DVI: interface = "DVI"; ଭାଙ୍ଗ;
	ସ୍ଥିତି HDMI_A: interface = "HDMI-a"; ଭାଙ୍ଗ;
	ସ୍ଥିତି HDMI_B: interface = "HDMI-b"; ଭାଙ୍ଗ;
	ସ୍ଥିତି MDDI: interface = "MDDI"; ଭାଙ୍ଗ;
	ସ୍ଥିତି DISPLAY_PORT: interface = "DisplayPort"; ଭାଙ୍ଗ;
	ସ୍ଥିତି UNDEFINED: interface = "undefined"; ଭାଙ୍ଗ;
	ପୂର୍ବନିର୍ଦ୍ଧାରିତ: interface = "unknown"; ଭାଙ୍ଗ;
	}
	printf ("Interface: %s\n", interface);
	
	printf ("RGB 4:4:4: %s\n", yesno (info->ad.digital.rgb444));
	printf ("YCrCb 4:4:4: %s\n", yesno (info->ad.digital.ycrcb444));
	printf ("YCrCb 4:2:2: %s\n", yesno (info->ad.digital.ycrcb422));
    }
    ଅନ୍ୟଥା
    {
       ଅଚଳ ଅକ୍ଷର *s;
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
	
	ବାଛ (info->ad.analog.color_type)
	{
	ସ୍ଥିତି UNDEFINED_COLOR: s = "undefined"; ଭାଙ୍ଗ;
	ସ୍ଥିତି MONOCHROME: s = "monochrome"; ଭାଙ୍ଗ;
	ସ୍ଥିତି RGB: s = "rgb"; ଭାଙ୍ଗ;
	ସ୍ଥିତି OTHER_COLOR: s = "other color"; ଭାଙ୍ଗ;
	ପୂର୍ବନିର୍ଦ୍ଧାରିତ: s = "unknown"; ଭାଙ୍ଗ;
	}
	
	printf ("Color: %s\n", s);
    }
    
    ଯଦି (info->width_mm == -1)
	printf ("Width: undefined\n");
    ଅନ୍ୟଥା
	printf ("Width: %d mm\n", info->width_mm);
    
    ଯଦି (info->height_mm == -1)
	printf ("Height: undefined\n");
    ଅନ୍ୟଥା
	printf ("Height: %d mm\n", info->height_mm);
    
    ଯଦି (info->aspect_ratio > 0)
	printf ("Aspect Ratio: %f\n", info->aspect_ratio);
    ଅନ୍ୟଥା
	printf ("Aspect Ratio: undefined\n");
    
    ଯଦି (info->gamma >= 0)
	printf ("Gamma: %f\n", info->gamma);
    ଅନ୍ୟଥା
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
    
    ପାଇଁ (i = 0; i < 24; ++i)
    {
	Timing *timing = &(info->established[i]);
	
	ଯଦି (timing->frequency == 0)
	    ଭାଙ୍ଗ;
	
	printf ("  %d x %d @ %d Hz\n",
		timing->width, timing->height, timing->frequency);
	
    }
    
    printf ("Standard Timings:\n");
    ପାଇଁ (i = 0; i < 8; ++i)
    {
	Timing *timing = &(info->standard[i]);
	
	ଯଦି (timing->frequency == 0)
	    ଭାଙ୍ଗ;
	
	printf ("  %d x %d @ %d Hz\n",
		timing->width, timing->height, timing->frequency);
    }
    
    ପାଇଁ (i = 0; i < info->n_detailed_timings; ++i)
    {
	DetailedTiming *timing = &(info->detailed_timings[i]);
	ଅଚଳ ଅକ୍ଷର *s;
	
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
	printf ("  Right Border: %d\n", timing->ଡାହାଣ_border);
	printf ("  Top Border: %d\n", timing->ଶୀର୍ଷ_border);
	ବାଛ (timing->stereo)
	{
	ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
	ସ୍ଥିତି NO_STEREO:   s = "No Stereo"; ଭାଙ୍ଗ;
	ସ୍ଥିତି FIELD_ଡାହାଣ: s = "Field Sequential, Right on Sync"; ଭାଙ୍ଗ;
	ସ୍ଥିତି FIELD_ବାମ:  s = "Field Sequential, Left on Sync"; ଭାଙ୍ଗ;
	ସ୍ଥିତି TWO_WAY_ଡାହାଣ_ON_EVEN: s = "Two-way, Right on Even"; ଭାଙ୍ଗ;
	ସ୍ଥିତି TWO_WAY_ବାମ_ON_EVEN:  s = "Two-way, Left on Even"; ଭାଙ୍ଗ;
	ସ୍ଥିତି FOUR_WAY_INTERLEAVED:  s = "Four-way Interleaved"; ଭାଙ୍ଗ;
	ସ୍ଥିତି SIDE_BY_SIDE:          s = "Side-by-Side"; ଭାଙ୍ଗ;
	}
	printf ("  Stereo: %s\n", s);
	
	ଯଦି (timing->digital_sync)
	{
	    printf ("  Digital Sync:\n");
	    printf ("    composite: %s\n", yesno (timing->ad.digital.composite));
	    printf ("    serrations: %s\n", yesno (timing->ad.digital.serrations));
	    printf ("    negative vsync: %s\n",
		    yesno (timing->ad.digital.negative_vsync));
	    printf ("    negative hsync: %s\n",
		    yesno (timing->ad.digital.negative_hsync));
	}
	ଅନ୍ୟଥା
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
    printf ("  Serial Number: %s\n", info->dsc_serial_ସଂଖ୍ୟା);
    printf ("  Unspecified String: %s\n", info->dsc_string);
}

