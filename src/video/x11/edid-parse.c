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
#अन्तर्भाव "SDL_internal.h"

#अन्तर्भाव "edid.h"
#अन्तर्भाव <stdlib.h>
#अन्तर्भाव <string.h>
#अन्तर्भाव <math.h>
#अन्तर्भाव <stdio.h>

#define TRUE 1
#define FALSE 0

स्थिर पूर्णाङ्क
get_bit (पूर्णाङ्क in, पूर्णाङ्क bit)
{
    प्रत्यागम (in & (1 << bit)) >> bit;
}

स्थिर पूर्णाङ्क
get_bits (पूर्णाङ्क in, पूर्णाङ्क begin, पूर्णाङ्क end)
{
    पूर्णाङ्क mask = (1 << (end - begin + 1)) - 1;
    
    प्रत्यागम (in >> begin) & mask;
}

स्थिर पूर्णाङ्क
decode_header (ध्रुव uchar *edid)
{
    यदि (SDL_memcmp (edid, "\x00\xff\xff\xff\xff\xff\xff\x00", 8) == 0)
	प्रत्यागम TRUE;
    प्रत्यागम FALSE;
}

स्थिर पूर्णाङ्क
decode_vendor_and_product_identification (ध्रुव uchar *edid, MonitorInfo *info)
{
    पूर्णाङ्क is_model_year;
    
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
    info->serial_संख्या =
	edid[0x0c] | edid[0x0d] << 8 | edid[0x0e] << 16 | (Uint32)edid[0x0f] << 24;

    /* Week and Year */
    is_model_year = FALSE;
    विकल्प (edid[0x10])
    {
    पक्ष 0x00:
	info->production_week = -1;
	भङ्ग;

    पक्ष 0xff:
	info->production_week = -1;
	is_model_year = TRUE;
	भङ्ग;

    स्वभाव:
	info->production_week = edid[0x10];
	भङ्ग;
    }

    यदि (is_model_year)
    {
	info->production_year = -1;
	info->model_year = 1990 + edid[0x11];
    }
    अन्यथा
    {
	info->production_year = 1990 + edid[0x11];
	info->model_year = -1;
    }

    प्रत्यागम TRUE;
}

स्थिर पूर्णाङ्क
decode_edid_version (ध्रुव uchar *edid, MonitorInfo *info)
{
    info->major_version = edid[0x12];
    info->minor_version = edid[0x13];

    प्रत्यागम TRUE;
}

स्थिर पूर्णाङ्क
decode_display_parameters (ध्रुव uchar *edid, MonitorInfo *info)
{
    /* Digital vs Analog */
    info->is_digital = get_bit (edid[0x14], 7);

    यदि (info->is_digital)
    {
	पूर्णाङ्क bits;
	
	स्थिर ध्रुव पूर्णाङ्क bit_depth[8] =
	{
	    -1, 6, 8, 10, 12, 14, 16, -1
	};

	स्थिर ध्रुव Interface interfaces[6] =
	{
	    UNDEFINED, DVI, HDMI_A, HDMI_B, MDDI, DISPLAY_PORT
	};

	bits = get_bits (edid[0x14], 4, 6);
	info->ad.digital.bits_per_primary = bit_depth[bits];

	bits = get_bits (edid[0x14], 0, 3);
	
	यदि (bits <= 5)
	    info->ad.digital.interface = interfaces[bits];
	अन्यथा
	    info->ad.digital.interface = UNDEFINED;
    }
    अन्यथा
    {
	पूर्णाङ्क bits = get_bits (edid[0x14], 5, 6);
	
	स्थिर ध्रुव द्विगुण levels[][3] =
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
    यदि (edid[0x15] == 0 && edid[0x16] == 0)
    {
	info->width_mm = -1;
	info->height_mm = -1;
	info->aspect_ratio = -1.0;
    }
    अन्यथा यदि (edid[0x16] == 0)
    {
	info->width_mm = -1;
	info->height_mm = -1; 
	info->aspect_ratio = 100.0 / (edid[0x15] + 99);
    }
    अन्यथा यदि (edid[0x15] == 0)
    {
	info->width_mm = -1;
	info->height_mm = -1;
	info->aspect_ratio = 100.0 / (edid[0x16] + 99);
	info->aspect_ratio = 1/info->aspect_ratio; /* portrait */
    }
    अन्यथा
    {
	info->width_mm = 10 * edid[0x15];
	info->height_mm = 10 * edid[0x16];
    }

    /* Gamma */
    यदि (edid[0x17] == 0xFF)
	info->gamma = -1.0;
    अन्यथा
	info->gamma = (edid[0x17] + 100.0) / 100.0;

    /* Features */
    info->standby = get_bit (edid[0x18], 7);
    info->suspend = get_bit (edid[0x18], 6);
    info->active_off = get_bit (edid[0x18], 5);

    यदि (info->is_digital)
    {
	info->ad.digital.rgb444 = TRUE;
	यदि (get_bit (edid[0x18], 3))
	    info->ad.digital.ycrcb444 = 1;
	यदि (get_bit (edid[0x18], 4))
	    info->ad.digital.ycrcb422 = 1;
    }
    अन्यथा
    {
	पूर्णाङ्क bits = get_bits (edid[0x18], 3, 4);
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
    प्रत्यागम TRUE;
}

स्थिर द्विगुण
decode_fraction (पूर्णाङ्क ऊपरी, पूर्णाङ्क निचला)
{
    द्विगुण result = 0.0;
    पूर्णाङ्क i;

    ऊपरी = (ऊपरी << 2) | निचला;

    प्रति (i = 0; i < 10; ++i)
	result += get_bit (ऊपरी, i) * SDL_pow (2, i - 10);

    प्रत्यागम result;
}

स्थिर पूर्णाङ्क
decode_color_characteristics (ध्रुव uchar *edid, MonitorInfo *info)
{
    info->red_x = decode_fraction (edid[0x1b], get_bits (edid[0x19], 6, 7));
    info->red_y = decode_fraction (edid[0x1c], get_bits (edid[0x19], 5, 4));
    info->green_x = decode_fraction (edid[0x1d], get_bits (edid[0x19], 2, 3));
    info->green_y = decode_fraction (edid[0x1e], get_bits (edid[0x19], 0, 1));
    info->blue_x = decode_fraction (edid[0x1f], get_bits (edid[0x1a], 6, 7));
    info->blue_y = decode_fraction (edid[0x20], get_bits (edid[0x1a], 4, 5));
    info->white_x = decode_fraction (edid[0x21], get_bits (edid[0x1a], 2, 3));
    info->white_y = decode_fraction (edid[0x22], get_bits (edid[0x1a], 0, 1));

    प्रत्यागम TRUE;
}

स्थिर पूर्णाङ्क
decode_established_timings (ध्रुव uchar *edid, MonitorInfo *info)
{
    स्थिर ध्रुव Timing established[][8] = 
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

    पूर्णाङ्क i, j, idx;

    idx = 0;
    प्रति (i = 0; i < 3; ++i)
    {
	प्रति (j = 0; j < 8; ++j)
	{
	    पूर्णाङ्क byte = edid[0x23 + i];

	    यदि (get_bit (byte, j) && established[i][j].frequency != 0)
		info->established[idx++] = established[i][j];
	}
    }
    प्रत्यागम TRUE;
}

स्थिर पूर्णाङ्क
decode_standard_timings (ध्रुव uchar *edid, MonitorInfo *info)
{
    पूर्णाङ्क i;
    
    प्रति (i = 0; i < 8; i++)
    {
	पूर्णाङ्क first = edid[0x26 + 2 * i];
	पूर्णाङ्क second = edid[0x27 + 2 * i];

	यदि (first != 0x01 && second != 0x01)
	{
	    पूर्णाङ्क w = 8 * (first + 31);
	    पूर्णाङ्क h = 0;

	    विकल्प (get_bits (second, 6, 7))
	    {
	    पक्ष 0x00: h = (w / 16) * 10; भङ्ग;
	    पक्ष 0x01: h = (w / 4) * 3; भङ्ग;
	    पक्ष 0x02: h = (w / 5) * 4; भङ्ग;
	    पक्ष 0x03: h = (w / 16) * 9; भङ्ग;
	    }

	    info->standard[i].width = w;
	    info->standard[i].height = h;
	    info->standard[i].frequency = get_bits (second, 0, 5) + 60;
	}
    }
    
    प्रत्यागम TRUE;
}

स्थिर शून्य
decode_lf_string (ध्रुव uchar *s, पूर्णाङ्क n_chars, वर्ण *result)
{
    पूर्णाङ्क i;
    प्रति (i = 0; i < n_chars; ++i)
    {
	यदि (s[i] == 0x0a)
	{
	    *result++ = '\0';
	    भङ्ग;
	}
	अन्यथा यदि (s[i] == 0x00)
	{
	    /* Convert embedded 0's to spaces */
	    *result++ = ' ';
	}
	अन्यथा
	{
	    *result++ = s[i];
	}
    }
}

स्थिर शून्य
decode_display_descriptor (ध्रुव uchar *desc,
			   MonitorInfo *info)
{
    विकल्प (desc[0x03])
    {
    पक्ष 0xFC:
	decode_lf_string (desc + 5, 13, info->dsc_product_name);
	भङ्ग;
    पक्ष 0xFF:
	decode_lf_string (desc + 5, 13, info->dsc_serial_संख्या);
	भङ्ग;
    पक्ष 0xFE:
	decode_lf_string (desc + 5, 13, info->dsc_string);
	भङ्ग;
    पक्ष 0xFD:
	/* Range Limits */
	भङ्ग;
    पक्ष 0xFB:
	/* Color Point */
	भङ्ग;
    पक्ष 0xFA:
	/* Timing Identifications */
	भङ्ग;
    पक्ष 0xF9:
	/* Color Management */
	भङ्ग;
    पक्ष 0xF8:
	/* Timing Codes */
	भङ्ग;
    पक्ष 0xF7:
	/* Established Timings */
	भङ्ग;
    पक्ष 0x10:
	भङ्ग;
    }
}

स्थिर शून्य
decode_detailed_timing (ध्रुव uchar *timing,
			DetailedTiming *detailed)
{
    पूर्णाङ्क bits;
    StereoType stereo[] =
    {
	NO_STEREO, NO_STEREO, FIELD_दायाँ, FIELD_बायाँ,
	TWO_WAY_दायाँ_ON_EVEN, TWO_WAY_बायाँ_ON_EVEN,
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
    detailed->दायाँ_border = timing[0x0f];
    detailed->शीर्ष_border = timing[0x10];

    detailed->interlaced = get_bit (timing[0x11], 7);

    /* Stereo */
    bits = get_bits (timing[0x11], 5, 6) << 1 | get_bit (timing[0x11], 0);
    detailed->stereo = stereo[bits];

    /* Sync */
    bits = timing[0x11];

    detailed->digital_sync = get_bit (bits, 4);
    यदि (detailed->digital_sync)
    {
	detailed->ad.digital.composite = !get_bit (bits, 3);

	यदि (detailed->ad.digital.composite)
	{
	    detailed->ad.digital.serrations = get_bit (bits, 2);
	    detailed->ad.digital.negative_vsync = FALSE;
	}
	अन्यथा
	{
	    detailed->ad.digital.serrations = FALSE;
	    detailed->ad.digital.negative_vsync = !get_bit (bits, 2);
	}

	detailed->ad.digital.negative_hsync = !get_bit (bits, 0);
    }
    अन्यथा
    {
	detailed->ad.analog.bipolar = get_bit (bits, 3);
	detailed->ad.analog.serrations = get_bit (bits, 2);
	detailed->ad.analog.sync_on_green = !get_bit (bits, 1);
    }
}

स्थिर पूर्णाङ्क
decode_descriptors (ध्रुव uchar *edid, MonitorInfo *info)
{
    पूर्णाङ्क i;
    पूर्णाङ्क timing_idx;
    
    timing_idx = 0;
    
    प्रति (i = 0; i < 4; ++i)
    {
	पूर्णाङ्क index = 0x36 + i * 18;

	यदि (edid[index + 0] == 0x00 && edid[index + 1] == 0x00)
	{
	    decode_display_descriptor (edid + index, info);
	}
	अन्यथा
	{
	    decode_detailed_timing (
		edid + index, &(info->detailed_timings[timing_idx++]));
	}
    }

    info->n_detailed_timings = timing_idx;

    प्रत्यागम TRUE;
}

स्थिर शून्य
decode_check_sum (ध्रुव uchar *edid,
		  MonitorInfo *info)
{
    पूर्णाङ्क i;
    uchar check = 0;

    प्रति (i = 0; i < 128; ++i)
	check += edid[i];

    info->checksum = check;
}

स्थिर शून्य
decode_HDR_metadata_block (ध्रुव uchar *data, पूर्णाङ्क length, MonitorInfo *info)
{
    यदि (length >= 3)
	info->max_luminance = 50.0 * SDL_pow(2, data[2] / 32.0);

    यदि (length >= 4)
	info->max_frame_average_luminance = 50.0 * SDL_pow(2, data[3] / 32.0);

    यदि (length >= 5)
	info->min_luminance = 50.0 * SDL_pow(2, data[4] / 32.0);
}


स्थिर शून्य
decode_cta_block (ध्रुव uchar *edid,
		  MonitorInfo *info)
{
    पूर्णाङ्क offset = 4;
    यावत् (offset < 128) {
	पूर्णाङ्क length = edid[offset] & 0x1f;
	पूर्णाङ्क type = edid[offset] >> 5;
	यदि (length == 0) {
	    भङ्ग;
	}
	यदि (type == 7) {
	    type <<= 8;
	    type |= edid[offset + 1];
	}
	यदि (type == 0x706) {
	    decode_HDR_metadata_block (&edid[offset + 2], length - 1, info);
	}
	offset += (1 + length);
    }
}

MonitorInfo *
decode_edid (ध्रुव uchar *edid, size_t size)
{
    ध्रुव पूर्णाङ्क EDID_PAGE_SIZE = 128;
    पूर्णाङ्क अंक_blocks = (size / EDID_PAGE_SIZE);
    MonitorInfo *info;

    यदि ((size % EDID_PAGE_SIZE) != 0) {
	प्रत्यागम रिक्त;
    }

    info = SDL_calloc (1, परिमाण (MonitorInfo));

    decode_check_sum (edid, info);
    
    यदि (!decode_header (edid) ||
        !decode_vendor_and_product_identification (edid, info) ||
        !decode_edid_version (edid, info) ||
        !decode_display_parameters (edid, info) ||
        !decode_color_characteristics (edid, info) ||
        !decode_established_timings (edid, info) ||
        !decode_standard_timings (edid, info) ||
        !decode_descriptors (edid, info)) {
	SDL_free(info);
	प्रत्यागम रिक्त;
    }
    
    यदि (अंक_blocks > 1) {
	प्रति (पूर्णाङ्क i = 1; i < अंक_blocks; ++i) {
	    पूर्णाङ्क offset = i * EDID_PAGE_SIZE;
	    uchar extension = edid[offset];
	    यदि (extension == 0x02) {
		// CTA-861 Extension Block
		decode_cta_block (&edid[offset], info);
	    }
	}
    }

    प्रत्यागम info;
}

स्थिर ध्रुव वर्ण *
yesno (पूर्णाङ्क v)
{
    प्रत्यागम v? "yes" : "no";
}

शून्य
dump_monitor_info (MonitorInfo *info)
{
    पूर्णाङ्क i;
    
    printf ("Checksum: %d (%s)\n",
	    info->checksum, info->checksum? "incorrect" : "correct");
    printf ("Manufacturer Code: %s\n", info->manufacturer_code);
    printf ("Product Code: 0x%x\n", info->product_code);
    printf ("Serial Number: %u\n", info->serial_संख्या);
    
    यदि (info->production_week != -1)
	printf ("Production Week: %d\n", info->production_week);
    अन्यथा
	printf ("Production Week: unspecified\n");
    
    यदि (info->production_year != -1)
	printf ("Production Year: %d\n", info->production_year);
    अन्यथा
	printf ("Production Year: unspecified\n");
    
    यदि (info->model_year != -1)
	printf ("Model Year: %d\n", info->model_year);
    अन्यथा
	printf ("Model Year: unspecified\n");
    
    printf ("EDID revision: %d.%d\n", info->major_version, info->minor_version);
    
    printf ("Display is %s\n", info->is_digital? "digital" : "analog");
    यदि (info->is_digital)
    {
	ध्रुव वर्ण *interface;
	यदि (info->ad.digital.bits_per_primary != -1)
	    printf ("Bits Per Primary: %d\n", info->ad.digital.bits_per_primary);
	अन्यथा
	    printf ("Bits Per Primary: undefined\n");
	
	विकल्प (info->ad.digital.interface)
	{
	पक्ष DVI: interface = "DVI"; भङ्ग;
	पक्ष HDMI_A: interface = "HDMI-a"; भङ्ग;
	पक्ष HDMI_B: interface = "HDMI-b"; भङ्ग;
	पक्ष MDDI: interface = "MDDI"; भङ्ग;
	पक्ष DISPLAY_PORT: interface = "DisplayPort"; भङ्ग;
	पक्ष UNDEFINED: interface = "undefined"; भङ्ग;
	स्वभाव: interface = "unknown"; भङ्ग;
	}
	printf ("Interface: %s\n", interface);
	
	printf ("RGB 4:4:4: %s\n", yesno (info->ad.digital.rgb444));
	printf ("YCrCb 4:4:4: %s\n", yesno (info->ad.digital.ycrcb444));
	printf ("YCrCb 4:2:2: %s\n", yesno (info->ad.digital.ycrcb422));
    }
    अन्यथा
    {
       ध्रुव वर्ण *s;
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
	
	विकल्प (info->ad.analog.color_type)
	{
	पक्ष UNDEFINED_COLOR: s = "undefined"; भङ्ग;
	पक्ष MONOCHROME: s = "monochrome"; भङ्ग;
	पक्ष RGB: s = "rgb"; भङ्ग;
	पक्ष OTHER_COLOR: s = "other color"; भङ्ग;
	स्वभाव: s = "unknown"; भङ्ग;
	}
	
	printf ("Color: %s\n", s);
    }
    
    यदि (info->width_mm == -1)
	printf ("Width: undefined\n");
    अन्यथा
	printf ("Width: %d mm\n", info->width_mm);
    
    यदि (info->height_mm == -1)
	printf ("Height: undefined\n");
    अन्यथा
	printf ("Height: %d mm\n", info->height_mm);
    
    यदि (info->aspect_ratio > 0)
	printf ("Aspect Ratio: %f\n", info->aspect_ratio);
    अन्यथा
	printf ("Aspect Ratio: undefined\n");
    
    यदि (info->gamma >= 0)
	printf ("Gamma: %f\n", info->gamma);
    अन्यथा
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
    
    प्रति (i = 0; i < 24; ++i)
    {
	Timing *timing = &(info->established[i]);
	
	यदि (timing->frequency == 0)
	    भङ्ग;
	
	printf ("  %d x %d @ %d Hz\n",
		timing->width, timing->height, timing->frequency);
	
    }
    
    printf ("Standard Timings:\n");
    प्रति (i = 0; i < 8; ++i)
    {
	Timing *timing = &(info->standard[i]);
	
	यदि (timing->frequency == 0)
	    भङ्ग;
	
	printf ("  %d x %d @ %d Hz\n",
		timing->width, timing->height, timing->frequency);
    }
    
    प्रति (i = 0; i < info->n_detailed_timings; ++i)
    {
	DetailedTiming *timing = &(info->detailed_timings[i]);
	ध्रुव वर्ण *s;
	
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
	printf ("  Right Border: %d\n", timing->दायाँ_border);
	printf ("  Top Border: %d\n", timing->शीर्ष_border);
	विकल्प (timing->stereo)
	{
	स्वभाव:
	पक्ष NO_STEREO:   s = "No Stereo"; भङ्ग;
	पक्ष FIELD_दायाँ: s = "Field Sequential, Right on Sync"; भङ्ग;
	पक्ष FIELD_बायाँ:  s = "Field Sequential, Left on Sync"; भङ्ग;
	पक्ष TWO_WAY_दायाँ_ON_EVEN: s = "Two-way, Right on Even"; भङ्ग;
	पक्ष TWO_WAY_बायाँ_ON_EVEN:  s = "Two-way, Left on Even"; भङ्ग;
	पक्ष FOUR_WAY_INTERLEAVED:  s = "Four-way Interleaved"; भङ्ग;
	पक्ष SIDE_BY_SIDE:          s = "Side-by-Side"; भङ्ग;
	}
	printf ("  Stereo: %s\n", s);
	
	यदि (timing->digital_sync)
	{
	    printf ("  Digital Sync:\n");
	    printf ("    composite: %s\n", yesno (timing->ad.digital.composite));
	    printf ("    serrations: %s\n", yesno (timing->ad.digital.serrations));
	    printf ("    negative vsync: %s\n",
		    yesno (timing->ad.digital.negative_vsync));
	    printf ("    negative hsync: %s\n",
		    yesno (timing->ad.digital.negative_hsync));
	}
	अन्यथा
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
    printf ("  Serial Number: %s\n", info->dsc_serial_संख्या);
    printf ("  Unspecified String: %s\n", info->dsc_string);
}

