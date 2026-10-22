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
#ضمن "SDL_internal.h"

#ضمن "edid.h"
#ضمن <stdlib.h>
#ضمن <string.h>
#ضمن <math.h>
#ضمن <stdio.h>

#define TRUE 1
#define FALSE 0

ساكن صحيح
get_bit (صحيح in, صحيح bit)
{
    أرجع (in & (1 << bit)) >> bit;
}

ساكن صحيح
get_bits (صحيح in, صحيح begin, صحيح end)
{
    صحيح mask = (1 << (end - begin + 1)) - 1;
    
    أرجع (in >> begin) & mask;
}

ساكن صحيح
decode_header (ثابت uchar *edid)
{
    إذا (SDL_memcmp (edid, "\x00\xff\xff\xff\xff\xff\xff\x00", 8) == 0)
	أرجع TRUE;
    أرجع FALSE;
}

ساكن صحيح
decode_vendor_and_product_identification (ثابت uchar *edid, MonitorInfo *info)
{
    صحيح is_model_year;
    
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
    info->serial_لمب =
	edid[0x0c] | edid[0x0d] << 8 | edid[0x0e] << 16 | (Uint32)edid[0x0f] << 24;

    /* Week and Year */
    is_model_year = FALSE;
    بدل (edid[0x10])
    {
    حالة 0x00:
	info->production_week = -1;
	اكسر;

    حالة 0xff:
	info->production_week = -1;
	is_model_year = TRUE;
	اكسر;

    افتراضي:
	info->production_week = edid[0x10];
	اكسر;
    }

    إذا (is_model_year)
    {
	info->production_year = -1;
	info->model_year = 1990 + edid[0x11];
    }
    وإلا
    {
	info->production_year = 1990 + edid[0x11];
	info->model_year = -1;
    }

    أرجع TRUE;
}

ساكن صحيح
decode_edid_version (ثابت uchar *edid, MonitorInfo *info)
{
    info->major_version = edid[0x12];
    info->minor_version = edid[0x13];

    أرجع TRUE;
}

ساكن صحيح
decode_display_parameters (ثابت uchar *edid, MonitorInfo *info)
{
    /* Digital vs Analog */
    info->is_digital = get_bit (edid[0x14], 7);

    إذا (info->is_digital)
    {
	صحيح bits;
	
	ساكن ثابت صحيح bit_depth[8] =
	{
	    -1, 6, 8, 10, 12, 14, 16, -1
	};

	ساكن ثابت Interface interfaces[6] =
	{
	    UNDEFINED, DVI, HDMI_A, HDMI_B, MDDI, DISPLAY_PORT
	};

	bits = get_bits (edid[0x14], 4, 6);
	info->ad.digital.bits_per_primary = bit_depth[bits];

	bits = get_bits (edid[0x14], 0, 3);
	
	إذا (bits <= 5)
	    info->ad.digital.interface = interfaces[bits];
	وإلا
	    info->ad.digital.interface = UNDEFINED;
    }
    وإلا
    {
	صحيح bits = get_bits (edid[0x14], 5, 6);
	
	ساكن ثابت مزدوج levels[][3] =
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
    إذا (edid[0x15] == 0 && edid[0x16] == 0)
    {
	info->width_mm = -1;
	info->height_mm = -1;
	info->aspect_ratio = -1.0;
    }
    وإلا إذا (edid[0x16] == 0)
    {
	info->width_mm = -1;
	info->height_mm = -1; 
	info->aspect_ratio = 100.0 / (edid[0x15] + 99);
    }
    وإلا إذا (edid[0x15] == 0)
    {
	info->width_mm = -1;
	info->height_mm = -1;
	info->aspect_ratio = 100.0 / (edid[0x16] + 99);
	info->aspect_ratio = 1/info->aspect_ratio; /* portrait */
    }
    وإلا
    {
	info->width_mm = 10 * edid[0x15];
	info->height_mm = 10 * edid[0x16];
    }

    /* Gamma */
    إذا (edid[0x17] == 0xFF)
	info->gamma = -1.0;
    وإلا
	info->gamma = (edid[0x17] + 100.0) / 100.0;

    /* Features */
    info->standby = get_bit (edid[0x18], 7);
    info->suspend = get_bit (edid[0x18], 6);
    info->active_off = get_bit (edid[0x18], 5);

    إذا (info->is_digital)
    {
	info->ad.digital.rgb444 = TRUE;
	إذا (get_bit (edid[0x18], 3))
	    info->ad.digital.ycrcb444 = 1;
	إذا (get_bit (edid[0x18], 4))
	    info->ad.digital.ycrcb422 = 1;
    }
    وإلا
    {
	صحيح bits = get_bits (edid[0x18], 3, 4);
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
    أرجع TRUE;
}

ساكن مزدوج
decode_fraction (صحيح سم, صحيح كس)
{
    مزدوج result = 0.0;
    صحيح i;

    سم = (سم << 2) | كس;

    لكل (i = 0; i < 10; ++i)
	result += get_bit (سم, i) * SDL_pow (2, i - 10);

    أرجع result;
}

ساكن صحيح
decode_color_characteristics (ثابت uchar *edid, MonitorInfo *info)
{
    info->red_x = decode_fraction (edid[0x1b], get_bits (edid[0x19], 6, 7));
    info->red_y = decode_fraction (edid[0x1c], get_bits (edid[0x19], 5, 4));
    info->green_x = decode_fraction (edid[0x1d], get_bits (edid[0x19], 2, 3));
    info->green_y = decode_fraction (edid[0x1e], get_bits (edid[0x19], 0, 1));
    info->blue_x = decode_fraction (edid[0x1f], get_bits (edid[0x1a], 6, 7));
    info->blue_y = decode_fraction (edid[0x20], get_bits (edid[0x1a], 4, 5));
    info->white_x = decode_fraction (edid[0x21], get_bits (edid[0x1a], 2, 3));
    info->white_y = decode_fraction (edid[0x22], get_bits (edid[0x1a], 0, 1));

    أرجع TRUE;
}

ساكن صحيح
decode_established_timings (ثابت uchar *edid, MonitorInfo *info)
{
    ساكن ثابت Timing established[][8] = 
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

    صحيح i, j, idx;

    idx = 0;
    لكل (i = 0; i < 3; ++i)
    {
	لكل (j = 0; j < 8; ++j)
	{
	    صحيح byte = edid[0x23 + i];

	    إذا (get_bit (byte, j) && established[i][j].frequency != 0)
		info->established[idx++] = established[i][j];
	}
    }
    أرجع TRUE;
}

ساكن صحيح
decode_standard_timings (ثابت uchar *edid, MonitorInfo *info)
{
    صحيح i;
    
    لكل (i = 0; i < 8; i++)
    {
	صحيح first = edid[0x26 + 2 * i];
	صحيح second = edid[0x27 + 2 * i];

	إذا (first != 0x01 && second != 0x01)
	{
	    صحيح w = 8 * (first + 31);
	    صحيح h = 0;

	    بدل (get_bits (second, 6, 7))
	    {
	    حالة 0x00: h = (w / 16) * 10; اكسر;
	    حالة 0x01: h = (w / 4) * 3; اكسر;
	    حالة 0x02: h = (w / 5) * 4; اكسر;
	    حالة 0x03: h = (w / 16) * 9; اكسر;
	    }

	    info->standard[i].width = w;
	    info->standard[i].height = h;
	    info->standard[i].frequency = get_bits (second, 0, 5) + 60;
	}
    }
    
    أرجع TRUE;
}

ساكن فراغ
decode_lf_string (ثابت uchar *s, صحيح n_chars, حرف *result)
{
    صحيح i;
    لكل (i = 0; i < n_chars; ++i)
    {
	إذا (s[i] == 0x0a)
	{
	    *result++ = '\0';
	    اكسر;
	}
	وإلا إذا (s[i] == 0x00)
	{
	    /* Convert embedded 0's to spaces */
	    *result++ = ' ';
	}
	وإلا
	{
	    *result++ = s[i];
	}
    }
}

ساكن فراغ
decode_display_descriptor (ثابت uchar *desc,
			   MonitorInfo *info)
{
    بدل (desc[0x03])
    {
    حالة 0xFC:
	decode_lf_string (desc + 5, 13, info->dsc_product_name);
	اكسر;
    حالة 0xFF:
	decode_lf_string (desc + 5, 13, info->dsc_serial_لمب);
	اكسر;
    حالة 0xFE:
	decode_lf_string (desc + 5, 13, info->dsc_string);
	اكسر;
    حالة 0xFD:
	/* Range Limits */
	اكسر;
    حالة 0xFB:
	/* Color Point */
	اكسر;
    حالة 0xFA:
	/* Timing Identifications */
	اكسر;
    حالة 0xF9:
	/* Color Management */
	اكسر;
    حالة 0xF8:
	/* Timing Codes */
	اكسر;
    حالة 0xF7:
	/* Established Timings */
	اكسر;
    حالة 0x10:
	اكسر;
    }
}

ساكن فراغ
decode_detailed_timing (ثابت uchar *timing,
			DetailedTiming *detailed)
{
    صحيح bits;
    StereoType stereo[] =
    {
	NO_STEREO, NO_STEREO, FIELD_دام, FIELD_هغو,
	TWO_WAY_دام_ON_EVEN, TWO_WAY_هغو_ON_EVEN,
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
    detailed->دام_border = timing[0x0f];
    detailed->كولي_border = timing[0x10];

    detailed->interlaced = get_bit (timing[0x11], 7);

    /* Stereo */
    bits = get_bits (timing[0x11], 5, 6) << 1 | get_bit (timing[0x11], 0);
    detailed->stereo = stereo[bits];

    /* Sync */
    bits = timing[0x11];

    detailed->digital_sync = get_bit (bits, 4);
    إذا (detailed->digital_sync)
    {
	detailed->ad.digital.composite = !get_bit (bits, 3);

	إذا (detailed->ad.digital.composite)
	{
	    detailed->ad.digital.serrations = get_bit (bits, 2);
	    detailed->ad.digital.negative_vsync = FALSE;
	}
	وإلا
	{
	    detailed->ad.digital.serrations = FALSE;
	    detailed->ad.digital.negative_vsync = !get_bit (bits, 2);
	}

	detailed->ad.digital.negative_hsync = !get_bit (bits, 0);
    }
    وإلا
    {
	detailed->ad.analog.bipolar = get_bit (bits, 3);
	detailed->ad.analog.serrations = get_bit (bits, 2);
	detailed->ad.analog.sync_on_green = !get_bit (bits, 1);
    }
}

ساكن صحيح
decode_descriptors (ثابت uchar *edid, MonitorInfo *info)
{
    صحيح i;
    صحيح timing_idx;
    
    timing_idx = 0;
    
    لكل (i = 0; i < 4; ++i)
    {
	صحيح index = 0x36 + i * 18;

	إذا (edid[index + 0] == 0x00 && edid[index + 1] == 0x00)
	{
	    decode_display_descriptor (edid + index, info);
	}
	وإلا
	{
	    decode_detailed_timing (
		edid + index, &(info->detailed_timings[timing_idx++]));
	}
    }

    info->n_detailed_timings = timing_idx;

    أرجع TRUE;
}

ساكن فراغ
decode_check_sum (ثابت uchar *edid,
		  MonitorInfo *info)
{
    صحيح i;
    uchar check = 0;

    لكل (i = 0; i < 128; ++i)
	check += edid[i];

    info->checksum = check;
}

ساكن فراغ
decode_HDR_metadata_block (ثابت uchar *data, صحيح length, MonitorInfo *info)
{
    إذا (length >= 3)
	info->max_luminance = 50.0 * SDL_pow(2, data[2] / 32.0);

    إذا (length >= 4)
	info->max_frame_average_luminance = 50.0 * SDL_pow(2, data[3] / 32.0);

    إذا (length >= 5)
	info->min_luminance = 50.0 * SDL_pow(2, data[4] / 32.0);
}


ساكن فراغ
decode_cta_block (ثابت uchar *edid,
		  MonitorInfo *info)
{
    صحيح offset = 4;
    طالما (offset < 128) {
	صحيح length = edid[offset] & 0x1f;
	صحيح type = edid[offset] >> 5;
	إذا (length == 0) {
	    اكسر;
	}
	إذا (type == 7) {
	    type <<= 8;
	    type |= edid[offset + 1];
	}
	إذا (type == 0x706) {
	    decode_HDR_metadata_block (&edid[offset + 2], length - 1, info);
	}
	offset += (1 + length);
    }
}

MonitorInfo *
decode_edid (ثابت uchar *edid, size_t size)
{
    ثابت صحيح EDID_PAGE_SIZE = 128;
    صحيح لمب_blocks = (size / EDID_PAGE_SIZE);
    MonitorInfo *info;

    إذا ((size % EDID_PAGE_SIZE) != 0) {
	أرجع عدم;
    }

    info = SDL_calloc (1, حجم (MonitorInfo));

    decode_check_sum (edid, info);
    
    إذا (!decode_header (edid) ||
        !decode_vendor_and_product_identification (edid, info) ||
        !decode_edid_version (edid, info) ||
        !decode_display_parameters (edid, info) ||
        !decode_color_characteristics (edid, info) ||
        !decode_established_timings (edid, info) ||
        !decode_standard_timings (edid, info) ||
        !decode_descriptors (edid, info)) {
	SDL_free(info);
	أرجع عدم;
    }
    
    إذا (لمب_blocks > 1) {
	لكل (صحيح i = 1; i < لمب_blocks; ++i) {
	    صحيح offset = i * EDID_PAGE_SIZE;
	    uchar extension = edid[offset];
	    إذا (extension == 0x02) {
		// CTA-861 Extension Block
		decode_cta_block (&edid[offset], info);
	    }
	}
    }

    أرجع info;
}

ساكن ثابت حرف *
yesno (صحيح v)
{
    أرجع v? "yes" : "no";
}

فراغ
dump_monitor_info (MonitorInfo *info)
{
    صحيح i;
    
    printf ("Checksum: %d (%s)\n",
	    info->checksum, info->checksum? "incorrect" : "correct");
    printf ("Manufacturer Code: %s\n", info->manufacturer_code);
    printf ("Product Code: 0x%x\n", info->product_code);
    printf ("Serial Number: %u\n", info->serial_لمب);
    
    إذا (info->production_week != -1)
	printf ("Production Week: %d\n", info->production_week);
    وإلا
	printf ("Production Week: unspecified\n");
    
    إذا (info->production_year != -1)
	printf ("Production Year: %d\n", info->production_year);
    وإلا
	printf ("Production Year: unspecified\n");
    
    إذا (info->model_year != -1)
	printf ("Model Year: %d\n", info->model_year);
    وإلا
	printf ("Model Year: unspecified\n");
    
    printf ("EDID revision: %d.%d\n", info->major_version, info->minor_version);
    
    printf ("Display is %s\n", info->is_digital? "digital" : "analog");
    إذا (info->is_digital)
    {
	ثابت حرف *interface;
	إذا (info->ad.digital.bits_per_primary != -1)
	    printf ("Bits Per Primary: %d\n", info->ad.digital.bits_per_primary);
	وإلا
	    printf ("Bits Per Primary: undefined\n");
	
	بدل (info->ad.digital.interface)
	{
	حالة DVI: interface = "DVI"; اكسر;
	حالة HDMI_A: interface = "HDMI-a"; اكسر;
	حالة HDMI_B: interface = "HDMI-b"; اكسر;
	حالة MDDI: interface = "MDDI"; اكسر;
	حالة DISPLAY_PORT: interface = "DisplayPort"; اكسر;
	حالة UNDEFINED: interface = "undefined"; اكسر;
	افتراضي: interface = "unknown"; اكسر;
	}
	printf ("Interface: %s\n", interface);
	
	printf ("RGB 4:4:4: %s\n", yesno (info->ad.digital.rgb444));
	printf ("YCrCb 4:4:4: %s\n", yesno (info->ad.digital.ycrcb444));
	printf ("YCrCb 4:2:2: %s\n", yesno (info->ad.digital.ycrcb422));
    }
    وإلا
    {
       ثابت حرف *s;
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
	
	بدل (info->ad.analog.color_type)
	{
	حالة UNDEFINED_COLOR: s = "undefined"; اكسر;
	حالة MONOCHROME: s = "monochrome"; اكسر;
	حالة RGB: s = "rgb"; اكسر;
	حالة OTHER_COLOR: s = "other color"; اكسر;
	افتراضي: s = "unknown"; اكسر;
	}
	
	printf ("Color: %s\n", s);
    }
    
    إذا (info->width_mm == -1)
	printf ("Width: undefined\n");
    وإلا
	printf ("Width: %d mm\n", info->width_mm);
    
    إذا (info->height_mm == -1)
	printf ("Height: undefined\n");
    وإلا
	printf ("Height: %d mm\n", info->height_mm);
    
    إذا (info->aspect_ratio > 0)
	printf ("Aspect Ratio: %f\n", info->aspect_ratio);
    وإلا
	printf ("Aspect Ratio: undefined\n");
    
    إذا (info->gamma >= 0)
	printf ("Gamma: %f\n", info->gamma);
    وإلا
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
    
    لكل (i = 0; i < 24; ++i)
    {
	Timing *timing = &(info->established[i]);
	
	إذا (timing->frequency == 0)
	    اكسر;
	
	printf ("  %d x %d @ %d Hz\n",
		timing->width, timing->height, timing->frequency);
	
    }
    
    printf ("Standard Timings:\n");
    لكل (i = 0; i < 8; ++i)
    {
	Timing *timing = &(info->standard[i]);
	
	إذا (timing->frequency == 0)
	    اكسر;
	
	printf ("  %d x %d @ %d Hz\n",
		timing->width, timing->height, timing->frequency);
    }
    
    لكل (i = 0; i < info->n_detailed_timings; ++i)
    {
	DetailedTiming *timing = &(info->detailed_timings[i]);
	ثابت حرف *s;
	
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
	printf ("  Right Border: %d\n", timing->دام_border);
	printf ("  Top Border: %d\n", timing->كولي_border);
	بدل (timing->stereo)
	{
	افتراضي:
	حالة NO_STEREO:   s = "No Stereo"; اكسر;
	حالة FIELD_دام: s = "Field Sequential, Right on Sync"; اكسر;
	حالة FIELD_هغو:  s = "Field Sequential, Left on Sync"; اكسر;
	حالة TWO_WAY_دام_ON_EVEN: s = "Two-way, Right on Even"; اكسر;
	حالة TWO_WAY_هغو_ON_EVEN:  s = "Two-way, Left on Even"; اكسر;
	حالة FOUR_WAY_INTERLEAVED:  s = "Four-way Interleaved"; اكسر;
	حالة SIDE_BY_SIDE:          s = "Side-by-Side"; اكسر;
	}
	printf ("  Stereo: %s\n", s);
	
	إذا (timing->digital_sync)
	{
	    printf ("  Digital Sync:\n");
	    printf ("    composite: %s\n", yesno (timing->ad.digital.composite));
	    printf ("    serrations: %s\n", yesno (timing->ad.digital.serrations));
	    printf ("    negative vsync: %s\n",
		    yesno (timing->ad.digital.negative_vsync));
	    printf ("    negative hsync: %s\n",
		    yesno (timing->ad.digital.negative_hsync));
	}
	وإلا
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
    printf ("  Serial Number: %s\n", info->dsc_serial_لمب);
    printf ("  Unspecified String: %s\n", info->dsc_string);
}

