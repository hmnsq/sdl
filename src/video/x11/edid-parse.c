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
#অন্তর্ভাৱ "SDL_internal.h"

#অন্তর্ভাৱ "edid.h"
#অন্তর্ভাৱ <stdlib.h>
#অন্তর্ভাৱ <string.h>
#অন্তর্ভাৱ <math.h>
#অন্তর্ভাৱ <stdio.h>

#define TRUE 1
#define FALSE 0

স্থির পূর্ণাঙ্ক
get_bit (পূর্ণাঙ্ক in, পূর্ণাঙ্ক bit)
{
    ঘূৰাই (in & (1 << bit)) >> bit;
}

স্থির পূর্ণাঙ্ক
get_bits (পূর্ণাঙ্ক in, পূর্ণাঙ্ক begin, পূর্ণাঙ্ক end)
{
    পূর্ণাঙ্ক mask = (1 << (end - begin + 1)) - 1;
    
    ঘূৰাই (in >> begin) & mask;
}

স্থির পূর্ণাঙ্ক
decode_header (ধ্রুৱ uchar *edid)
{
    যদি (SDL_memcmp (edid, "\x00\xff\xff\xff\xff\xff\xff\x00", 8) == 0)
	ঘূৰাই TRUE;
    ঘূৰাই FALSE;
}

স্থির পূর্ণাঙ্ক
decode_vendor_and_product_identification (ধ্রুৱ uchar *edid, MonitorInfo *info)
{
    পূর্ণাঙ্ক is_model_year;
    
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
    info->serial_সংখ্যা =
	edid[0x0c] | edid[0x0d] << 8 | edid[0x0e] << 16 | (Uint32)edid[0x0f] << 24;

    /* Week and Year */
    is_model_year = FALSE;
    ৱিকল্প (edid[0x10])
    {
    পক্ষ 0x00:
	info->production_week = -1;
	ভঙ্গ;

    পক্ষ 0xff:
	info->production_week = -1;
	is_model_year = TRUE;
	ভঙ্গ;

    স্ৱভাৱ:
	info->production_week = edid[0x10];
	ভঙ্গ;
    }

    যদি (is_model_year)
    {
	info->production_year = -1;
	info->model_year = 1990 + edid[0x11];
    }
    অন্যথা
    {
	info->production_year = 1990 + edid[0x11];
	info->model_year = -1;
    }

    ঘূৰাই TRUE;
}

স্থির পূর্ণাঙ্ক
decode_edid_version (ধ্রুৱ uchar *edid, MonitorInfo *info)
{
    info->major_version = edid[0x12];
    info->minor_version = edid[0x13];

    ঘূৰাই TRUE;
}

স্থির পূর্ণাঙ্ক
decode_display_parameters (ধ্রুৱ uchar *edid, MonitorInfo *info)
{
    /* Digital vs Analog */
    info->is_digital = get_bit (edid[0x14], 7);

    যদি (info->is_digital)
    {
	পূর্ণাঙ্ক bits;
	
	স্থির ধ্রুৱ পূর্ণাঙ্ক bit_depth[8] =
	{
	    -1, 6, 8, 10, 12, 14, 16, -1
	};

	স্থির ধ্রুৱ Interface interfaces[6] =
	{
	    UNDEFINED, DVI, HDMI_A, HDMI_B, MDDI, DISPLAY_PORT
	};

	bits = get_bits (edid[0x14], 4, 6);
	info->ad.digital.bits_per_primary = bit_depth[bits];

	bits = get_bits (edid[0x14], 0, 3);
	
	যদি (bits <= 5)
	    info->ad.digital.interface = interfaces[bits];
	অন্যথা
	    info->ad.digital.interface = UNDEFINED;
    }
    অন্যথা
    {
	পূর্ণাঙ্ক bits = get_bits (edid[0x14], 5, 6);
	
	স্থির ধ্রুৱ দ্ৱিগুণ levels[][3] =
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
    যদি (edid[0x15] == 0 && edid[0x16] == 0)
    {
	info->width_mm = -1;
	info->height_mm = -1;
	info->aspect_ratio = -1.0;
    }
    অন্যথা যদি (edid[0x16] == 0)
    {
	info->width_mm = -1;
	info->height_mm = -1; 
	info->aspect_ratio = 100.0 / (edid[0x15] + 99);
    }
    অন্যথা যদি (edid[0x15] == 0)
    {
	info->width_mm = -1;
	info->height_mm = -1;
	info->aspect_ratio = 100.0 / (edid[0x16] + 99);
	info->aspect_ratio = 1/info->aspect_ratio; /* portrait */
    }
    অন্যথা
    {
	info->width_mm = 10 * edid[0x15];
	info->height_mm = 10 * edid[0x16];
    }

    /* Gamma */
    যদি (edid[0x17] == 0xFF)
	info->gamma = -1.0;
    অন্যথা
	info->gamma = (edid[0x17] + 100.0) / 100.0;

    /* Features */
    info->standby = get_bit (edid[0x18], 7);
    info->suspend = get_bit (edid[0x18], 6);
    info->active_off = get_bit (edid[0x18], 5);

    যদি (info->is_digital)
    {
	info->ad.digital.rgb444 = TRUE;
	যদি (get_bit (edid[0x18], 3))
	    info->ad.digital.ycrcb444 = 1;
	যদি (get_bit (edid[0x18], 4))
	    info->ad.digital.ycrcb422 = 1;
    }
    অন্যথা
    {
	পূর্ণাঙ্ক bits = get_bits (edid[0x18], 3, 4);
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
    ঘূৰাই TRUE;
}

স্থির দ্ৱিগুণ
decode_fraction (পূর্ণাঙ্ক উপৰেৰ, পূর্ণাঙ্ক নিচেৰ)
{
    দ্ৱিগুণ result = 0.0;
    পূর্ণাঙ্ক i;

    উপৰেৰ = (উপৰেৰ << 2) | নিচেৰ;

    বাবে (i = 0; i < 10; ++i)
	result += get_bit (উপৰেৰ, i) * SDL_pow (2, i - 10);

    ঘূৰাই result;
}

স্থির পূর্ণাঙ্ক
decode_color_characteristics (ধ্রুৱ uchar *edid, MonitorInfo *info)
{
    info->red_x = decode_fraction (edid[0x1b], get_bits (edid[0x19], 6, 7));
    info->red_y = decode_fraction (edid[0x1c], get_bits (edid[0x19], 5, 4));
    info->green_x = decode_fraction (edid[0x1d], get_bits (edid[0x19], 2, 3));
    info->green_y = decode_fraction (edid[0x1e], get_bits (edid[0x19], 0, 1));
    info->blue_x = decode_fraction (edid[0x1f], get_bits (edid[0x1a], 6, 7));
    info->blue_y = decode_fraction (edid[0x20], get_bits (edid[0x1a], 4, 5));
    info->white_x = decode_fraction (edid[0x21], get_bits (edid[0x1a], 2, 3));
    info->white_y = decode_fraction (edid[0x22], get_bits (edid[0x1a], 0, 1));

    ঘূৰাই TRUE;
}

স্থির পূর্ণাঙ্ক
decode_established_timings (ধ্রুৱ uchar *edid, MonitorInfo *info)
{
    স্থির ধ্রুৱ Timing established[][8] = 
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

    পূর্ণাঙ্ক i, j, idx;

    idx = 0;
    বাবে (i = 0; i < 3; ++i)
    {
	বাবে (j = 0; j < 8; ++j)
	{
	    পূর্ণাঙ্ক byte = edid[0x23 + i];

	    যদি (get_bit (byte, j) && established[i][j].frequency != 0)
		info->established[idx++] = established[i][j];
	}
    }
    ঘূৰাই TRUE;
}

স্থির পূর্ণাঙ্ক
decode_standard_timings (ধ্রুৱ uchar *edid, MonitorInfo *info)
{
    পূর্ণাঙ্ক i;
    
    বাবে (i = 0; i < 8; i++)
    {
	পূর্ণাঙ্ক first = edid[0x26 + 2 * i];
	পূর্ণাঙ্ক second = edid[0x27 + 2 * i];

	যদি (first != 0x01 && second != 0x01)
	{
	    পূর্ণাঙ্ক w = 8 * (first + 31);
	    পূর্ণাঙ্ক h = 0;

	    ৱিকল্প (get_bits (second, 6, 7))
	    {
	    পক্ষ 0x00: h = (w / 16) * 10; ভঙ্গ;
	    পক্ষ 0x01: h = (w / 4) * 3; ভঙ্গ;
	    পক্ষ 0x02: h = (w / 5) * 4; ভঙ্গ;
	    পক্ষ 0x03: h = (w / 16) * 9; ভঙ্গ;
	    }

	    info->standard[i].width = w;
	    info->standard[i].height = h;
	    info->standard[i].frequency = get_bits (second, 0, 5) + 60;
	}
    }
    
    ঘূৰাই TRUE;
}

স্থির শূন্য
decode_lf_string (ধ্রুৱ uchar *s, পূর্ণাঙ্ক n_chars, ৱর্ণ *result)
{
    পূর্ণাঙ্ক i;
    বাবে (i = 0; i < n_chars; ++i)
    {
	যদি (s[i] == 0x0a)
	{
	    *result++ = '\0';
	    ভঙ্গ;
	}
	অন্যথা যদি (s[i] == 0x00)
	{
	    /* Convert embedded 0's to spaces */
	    *result++ = ' ';
	}
	অন্যথা
	{
	    *result++ = s[i];
	}
    }
}

স্থির শূন্য
decode_display_descriptor (ধ্রুৱ uchar *desc,
			   MonitorInfo *info)
{
    ৱিকল্প (desc[0x03])
    {
    পক্ষ 0xFC:
	decode_lf_string (desc + 5, 13, info->dsc_product_name);
	ভঙ্গ;
    পক্ষ 0xFF:
	decode_lf_string (desc + 5, 13, info->dsc_serial_সংখ্যা);
	ভঙ্গ;
    পক্ষ 0xFE:
	decode_lf_string (desc + 5, 13, info->dsc_string);
	ভঙ্গ;
    পক্ষ 0xFD:
	/* Range Limits */
	ভঙ্গ;
    পক্ষ 0xFB:
	/* Color Point */
	ভঙ্গ;
    পক্ষ 0xFA:
	/* Timing Identifications */
	ভঙ্গ;
    পক্ষ 0xF9:
	/* Color Management */
	ভঙ্গ;
    পক্ষ 0xF8:
	/* Timing Codes */
	ভঙ্গ;
    পক্ষ 0xF7:
	/* Established Timings */
	ভঙ্গ;
    পক্ষ 0x10:
	ভঙ্গ;
    }
}

স্থির শূন্য
decode_detailed_timing (ধ্রুৱ uchar *timing,
			DetailedTiming *detailed)
{
    পূর্ণাঙ্ক bits;
    StereoType stereo[] =
    {
	NO_STEREO, NO_STEREO, FIELD_ডান, FIELD_বাম,
	TWO_WAY_ডান_ON_EVEN, TWO_WAY_বাম_ON_EVEN,
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
    detailed->ডান_border = timing[0x0f];
    detailed->শীৰ্ষ_border = timing[0x10];

    detailed->interlaced = get_bit (timing[0x11], 7);

    /* Stereo */
    bits = get_bits (timing[0x11], 5, 6) << 1 | get_bit (timing[0x11], 0);
    detailed->stereo = stereo[bits];

    /* Sync */
    bits = timing[0x11];

    detailed->digital_sync = get_bit (bits, 4);
    যদি (detailed->digital_sync)
    {
	detailed->ad.digital.composite = !get_bit (bits, 3);

	যদি (detailed->ad.digital.composite)
	{
	    detailed->ad.digital.serrations = get_bit (bits, 2);
	    detailed->ad.digital.negative_vsync = FALSE;
	}
	অন্যথা
	{
	    detailed->ad.digital.serrations = FALSE;
	    detailed->ad.digital.negative_vsync = !get_bit (bits, 2);
	}

	detailed->ad.digital.negative_hsync = !get_bit (bits, 0);
    }
    অন্যথা
    {
	detailed->ad.analog.bipolar = get_bit (bits, 3);
	detailed->ad.analog.serrations = get_bit (bits, 2);
	detailed->ad.analog.sync_on_green = !get_bit (bits, 1);
    }
}

স্থির পূর্ণাঙ্ক
decode_descriptors (ধ্রুৱ uchar *edid, MonitorInfo *info)
{
    পূর্ণাঙ্ক i;
    পূর্ণাঙ্ক timing_idx;
    
    timing_idx = 0;
    
    বাবে (i = 0; i < 4; ++i)
    {
	পূর্ণাঙ্ক index = 0x36 + i * 18;

	যদি (edid[index + 0] == 0x00 && edid[index + 1] == 0x00)
	{
	    decode_display_descriptor (edid + index, info);
	}
	অন্যথা
	{
	    decode_detailed_timing (
		edid + index, &(info->detailed_timings[timing_idx++]));
	}
    }

    info->n_detailed_timings = timing_idx;

    ঘূৰাই TRUE;
}

স্থির শূন্য
decode_check_sum (ধ্রুৱ uchar *edid,
		  MonitorInfo *info)
{
    পূর্ণাঙ্ক i;
    uchar check = 0;

    বাবে (i = 0; i < 128; ++i)
	check += edid[i];

    info->checksum = check;
}

স্থির শূন্য
decode_HDR_metadata_block (ধ্রুৱ uchar *data, পূর্ণাঙ্ক length, MonitorInfo *info)
{
    যদি (length >= 3)
	info->max_luminance = 50.0 * SDL_pow(2, data[2] / 32.0);

    যদি (length >= 4)
	info->max_frame_average_luminance = 50.0 * SDL_pow(2, data[3] / 32.0);

    যদি (length >= 5)
	info->min_luminance = 50.0 * SDL_pow(2, data[4] / 32.0);
}


স্থির শূন্য
decode_cta_block (ধ্রুৱ uchar *edid,
		  MonitorInfo *info)
{
    পূর্ণাঙ্ক offset = 4;
    যেতিয়ালৈ (offset < 128) {
	পূর্ণাঙ্ক length = edid[offset] & 0x1f;
	পূর্ণাঙ্ক type = edid[offset] >> 5;
	যদি (length == 0) {
	    ভঙ্গ;
	}
	যদি (type == 7) {
	    type <<= 8;
	    type |= edid[offset + 1];
	}
	যদি (type == 0x706) {
	    decode_HDR_metadata_block (&edid[offset + 2], length - 1, info);
	}
	offset += (1 + length);
    }
}

MonitorInfo *
decode_edid (ধ্রুৱ uchar *edid, size_t size)
{
    ধ্রুৱ পূর্ণাঙ্ক EDID_PAGE_SIZE = 128;
    পূর্ণাঙ্ক অঙ্ক_blocks = (size / EDID_PAGE_SIZE);
    MonitorInfo *info;

    যদি ((size % EDID_PAGE_SIZE) != 0) {
	ঘূৰাই রিক্ত;
    }

    info = SDL_calloc (1, পরিমাণ (MonitorInfo));

    decode_check_sum (edid, info);
    
    যদি (!decode_header (edid) ||
        !decode_vendor_and_product_identification (edid, info) ||
        !decode_edid_version (edid, info) ||
        !decode_display_parameters (edid, info) ||
        !decode_color_characteristics (edid, info) ||
        !decode_established_timings (edid, info) ||
        !decode_standard_timings (edid, info) ||
        !decode_descriptors (edid, info)) {
	SDL_free(info);
	ঘূৰাই রিক্ত;
    }
    
    যদি (অঙ্ক_blocks > 1) {
	বাবে (পূর্ণাঙ্ক i = 1; i < অঙ্ক_blocks; ++i) {
	    পূর্ণাঙ্ক offset = i * EDID_PAGE_SIZE;
	    uchar extension = edid[offset];
	    যদি (extension == 0x02) {
		// CTA-861 Extension Block
		decode_cta_block (&edid[offset], info);
	    }
	}
    }

    ঘূৰাই info;
}

স্থির ধ্রুৱ ৱর্ণ *
yesno (পূর্ণাঙ্ক v)
{
    ঘূৰাই v? "yes" : "no";
}

শূন্য
dump_monitor_info (MonitorInfo *info)
{
    পূর্ণাঙ্ক i;
    
    printf ("Checksum: %d (%s)\n",
	    info->checksum, info->checksum? "incorrect" : "correct");
    printf ("Manufacturer Code: %s\n", info->manufacturer_code);
    printf ("Product Code: 0x%x\n", info->product_code);
    printf ("Serial Number: %u\n", info->serial_সংখ্যা);
    
    যদি (info->production_week != -1)
	printf ("Production Week: %d\n", info->production_week);
    অন্যথা
	printf ("Production Week: unspecified\n");
    
    যদি (info->production_year != -1)
	printf ("Production Year: %d\n", info->production_year);
    অন্যথা
	printf ("Production Year: unspecified\n");
    
    যদি (info->model_year != -1)
	printf ("Model Year: %d\n", info->model_year);
    অন্যথা
	printf ("Model Year: unspecified\n");
    
    printf ("EDID revision: %d.%d\n", info->major_version, info->minor_version);
    
    printf ("Display is %s\n", info->is_digital? "digital" : "analog");
    যদি (info->is_digital)
    {
	ধ্রুৱ ৱর্ণ *interface;
	যদি (info->ad.digital.bits_per_primary != -1)
	    printf ("Bits Per Primary: %d\n", info->ad.digital.bits_per_primary);
	অন্যথা
	    printf ("Bits Per Primary: undefined\n");
	
	ৱিকল্প (info->ad.digital.interface)
	{
	পক্ষ DVI: interface = "DVI"; ভঙ্গ;
	পক্ষ HDMI_A: interface = "HDMI-a"; ভঙ্গ;
	পক্ষ HDMI_B: interface = "HDMI-b"; ভঙ্গ;
	পক্ষ MDDI: interface = "MDDI"; ভঙ্গ;
	পক্ষ DISPLAY_PORT: interface = "DisplayPort"; ভঙ্গ;
	পক্ষ UNDEFINED: interface = "undefined"; ভঙ্গ;
	স্ৱভাৱ: interface = "unknown"; ভঙ্গ;
	}
	printf ("Interface: %s\n", interface);
	
	printf ("RGB 4:4:4: %s\n", yesno (info->ad.digital.rgb444));
	printf ("YCrCb 4:4:4: %s\n", yesno (info->ad.digital.ycrcb444));
	printf ("YCrCb 4:2:2: %s\n", yesno (info->ad.digital.ycrcb422));
    }
    অন্যথা
    {
       ধ্রুৱ ৱর্ণ *s;
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
	
	ৱিকল্প (info->ad.analog.color_type)
	{
	পক্ষ UNDEFINED_COLOR: s = "undefined"; ভঙ্গ;
	পক্ষ MONOCHROME: s = "monochrome"; ভঙ্গ;
	পক্ষ RGB: s = "rgb"; ভঙ্গ;
	পক্ষ OTHER_COLOR: s = "other color"; ভঙ্গ;
	স্ৱভাৱ: s = "unknown"; ভঙ্গ;
	}
	
	printf ("Color: %s\n", s);
    }
    
    যদি (info->width_mm == -1)
	printf ("Width: undefined\n");
    অন্যথা
	printf ("Width: %d mm\n", info->width_mm);
    
    যদি (info->height_mm == -1)
	printf ("Height: undefined\n");
    অন্যথা
	printf ("Height: %d mm\n", info->height_mm);
    
    যদি (info->aspect_ratio > 0)
	printf ("Aspect Ratio: %f\n", info->aspect_ratio);
    অন্যথা
	printf ("Aspect Ratio: undefined\n");
    
    যদি (info->gamma >= 0)
	printf ("Gamma: %f\n", info->gamma);
    অন্যথা
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
    
    বাবে (i = 0; i < 24; ++i)
    {
	Timing *timing = &(info->established[i]);
	
	যদি (timing->frequency == 0)
	    ভঙ্গ;
	
	printf ("  %d x %d @ %d Hz\n",
		timing->width, timing->height, timing->frequency);
	
    }
    
    printf ("Standard Timings:\n");
    বাবে (i = 0; i < 8; ++i)
    {
	Timing *timing = &(info->standard[i]);
	
	যদি (timing->frequency == 0)
	    ভঙ্গ;
	
	printf ("  %d x %d @ %d Hz\n",
		timing->width, timing->height, timing->frequency);
    }
    
    বাবে (i = 0; i < info->n_detailed_timings; ++i)
    {
	DetailedTiming *timing = &(info->detailed_timings[i]);
	ধ্রুৱ ৱর্ণ *s;
	
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
	printf ("  Right Border: %d\n", timing->ডান_border);
	printf ("  Top Border: %d\n", timing->শীৰ্ষ_border);
	ৱিকল্প (timing->stereo)
	{
	স্ৱভাৱ:
	পক্ষ NO_STEREO:   s = "No Stereo"; ভঙ্গ;
	পক্ষ FIELD_ডান: s = "Field Sequential, Right on Sync"; ভঙ্গ;
	পক্ষ FIELD_বাম:  s = "Field Sequential, Left on Sync"; ভঙ্গ;
	পক্ষ TWO_WAY_ডান_ON_EVEN: s = "Two-way, Right on Even"; ভঙ্গ;
	পক্ষ TWO_WAY_বাম_ON_EVEN:  s = "Two-way, Left on Even"; ভঙ্গ;
	পক্ষ FOUR_WAY_INTERLEAVED:  s = "Four-way Interleaved"; ভঙ্গ;
	পক্ষ SIDE_BY_SIDE:          s = "Side-by-Side"; ভঙ্গ;
	}
	printf ("  Stereo: %s\n", s);
	
	যদি (timing->digital_sync)
	{
	    printf ("  Digital Sync:\n");
	    printf ("    composite: %s\n", yesno (timing->ad.digital.composite));
	    printf ("    serrations: %s\n", yesno (timing->ad.digital.serrations));
	    printf ("    negative vsync: %s\n",
		    yesno (timing->ad.digital.negative_vsync));
	    printf ("    negative hsync: %s\n",
		    yesno (timing->ad.digital.negative_hsync));
	}
	অন্যথা
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
    printf ("  Serial Number: %s\n", info->dsc_serial_সংখ্যা);
    printf ("  Unspecified String: %s\n", info->dsc_string);
}

