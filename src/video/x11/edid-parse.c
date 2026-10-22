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

स्थिर पूर्णांक
get_bit (पूर्णांक in, पूर्णांक bit)
{
    परत (in & (1 << bit)) >> bit;
}

स्थिर पूर्णांक
get_bits (पूर्णांक in, पूर्णांक begin, पूर्णांक end)
{
    पूर्णांक mask = (1 << (end - begin + 1)) - 1;
    
    परत (in >> begin) & mask;
}

स्थिर पूर्णांक
decode_header (स्थिरांक uchar *edid)
{
    जर (SDL_memcmp (edid, "\x00\xff\xff\xff\xff\xff\xff\x00", 8) == 0)
	परत TRUE;
    परत FALSE;
}

स्थिर पूर्णांक
decode_vendor_and_product_identification (स्थिरांक uchar *edid, MonitorInfo *info)
{
    पूर्णांक is_model_year;
    
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
    निवड (edid[0x10])
    {
    स्थिती 0x00:
	info->production_week = -1;
	थांबा;

    स्थिती 0xff:
	info->production_week = -1;
	is_model_year = TRUE;
	थांबा;

    पूर्वनिर्धारित:
	info->production_week = edid[0x10];
	थांबा;
    }

    जर (is_model_year)
    {
	info->production_year = -1;
	info->model_year = 1990 + edid[0x11];
    }
    अन्यथा
    {
	info->production_year = 1990 + edid[0x11];
	info->model_year = -1;
    }

    परत TRUE;
}

स्थिर पूर्णांक
decode_edid_version (स्थिरांक uchar *edid, MonitorInfo *info)
{
    info->major_version = edid[0x12];
    info->minor_version = edid[0x13];

    परत TRUE;
}

स्थिर पूर्णांक
decode_display_parameters (स्थिरांक uchar *edid, MonitorInfo *info)
{
    /* Digital vs Analog */
    info->is_digital = get_bit (edid[0x14], 7);

    जर (info->is_digital)
    {
	पूर्णांक bits;
	
	स्थिर स्थिरांक पूर्णांक bit_depth[8] =
	{
	    -1, 6, 8, 10, 12, 14, 16, -1
	};

	स्थिर स्थिरांक Interface interfaces[6] =
	{
	    UNDEFINED, DVI, HDMI_A, HDMI_B, MDDI, DISPLAY_PORT
	};

	bits = get_bits (edid[0x14], 4, 6);
	info->ad.digital.bits_per_primary = bit_depth[bits];

	bits = get_bits (edid[0x14], 0, 3);
	
	जर (bits <= 5)
	    info->ad.digital.interface = interfaces[bits];
	अन्यथा
	    info->ad.digital.interface = UNDEFINED;
    }
    अन्यथा
    {
	पूर्णांक bits = get_bits (edid[0x14], 5, 6);
	
	स्थिर स्थिरांक द्विगुण levels[][3] =
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
    जर (edid[0x15] == 0 && edid[0x16] == 0)
    {
	info->width_mm = -1;
	info->height_mm = -1;
	info->aspect_ratio = -1.0;
    }
    अन्यथा जर (edid[0x16] == 0)
    {
	info->width_mm = -1;
	info->height_mm = -1; 
	info->aspect_ratio = 100.0 / (edid[0x15] + 99);
    }
    अन्यथा जर (edid[0x15] == 0)
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
    जर (edid[0x17] == 0xFF)
	info->gamma = -1.0;
    अन्यथा
	info->gamma = (edid[0x17] + 100.0) / 100.0;

    /* Features */
    info->standby = get_bit (edid[0x18], 7);
    info->suspend = get_bit (edid[0x18], 6);
    info->active_off = get_bit (edid[0x18], 5);

    जर (info->is_digital)
    {
	info->ad.digital.rgb444 = TRUE;
	जर (get_bit (edid[0x18], 3))
	    info->ad.digital.ycrcb444 = 1;
	जर (get_bit (edid[0x18], 4))
	    info->ad.digital.ycrcb422 = 1;
    }
    अन्यथा
    {
	पूर्णांक bits = get_bits (edid[0x18], 3, 4);
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
    परत TRUE;
}

स्थिर द्विगुण
decode_fraction (पूर्णांक वरचा, पूर्णांक खालचा)
{
    द्विगुण result = 0.0;
    पूर्णांक i;

    वरचा = (वरचा << 2) | खालचा;

    साठी (i = 0; i < 10; ++i)
	result += get_bit (वरचा, i) * SDL_pow (2, i - 10);

    परत result;
}

स्थिर पूर्णांक
decode_color_characteristics (स्थिरांक uchar *edid, MonitorInfo *info)
{
    info->red_x = decode_fraction (edid[0x1b], get_bits (edid[0x19], 6, 7));
    info->red_y = decode_fraction (edid[0x1c], get_bits (edid[0x19], 5, 4));
    info->green_x = decode_fraction (edid[0x1d], get_bits (edid[0x19], 2, 3));
    info->green_y = decode_fraction (edid[0x1e], get_bits (edid[0x19], 0, 1));
    info->blue_x = decode_fraction (edid[0x1f], get_bits (edid[0x1a], 6, 7));
    info->blue_y = decode_fraction (edid[0x20], get_bits (edid[0x1a], 4, 5));
    info->white_x = decode_fraction (edid[0x21], get_bits (edid[0x1a], 2, 3));
    info->white_y = decode_fraction (edid[0x22], get_bits (edid[0x1a], 0, 1));

    परत TRUE;
}

स्थिर पूर्णांक
decode_established_timings (स्थिरांक uchar *edid, MonitorInfo *info)
{
    स्थिर स्थिरांक Timing established[][8] = 
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

    पूर्णांक i, j, idx;

    idx = 0;
    साठी (i = 0; i < 3; ++i)
    {
	साठी (j = 0; j < 8; ++j)
	{
	    पूर्णांक byte = edid[0x23 + i];

	    जर (get_bit (byte, j) && established[i][j].frequency != 0)
		info->established[idx++] = established[i][j];
	}
    }
    परत TRUE;
}

स्थिर पूर्णांक
decode_standard_timings (स्थिरांक uchar *edid, MonitorInfo *info)
{
    पूर्णांक i;
    
    साठी (i = 0; i < 8; i++)
    {
	पूर्णांक first = edid[0x26 + 2 * i];
	पूर्णांक second = edid[0x27 + 2 * i];

	जर (first != 0x01 && second != 0x01)
	{
	    पूर्णांक w = 8 * (first + 31);
	    पूर्णांक h = 0;

	    निवड (get_bits (second, 6, 7))
	    {
	    स्थिती 0x00: h = (w / 16) * 10; थांबा;
	    स्थिती 0x01: h = (w / 4) * 3; थांबा;
	    स्थिती 0x02: h = (w / 5) * 4; थांबा;
	    स्थिती 0x03: h = (w / 16) * 9; थांबा;
	    }

	    info->standard[i].width = w;
	    info->standard[i].height = h;
	    info->standard[i].frequency = get_bits (second, 0, 5) + 60;
	}
    }
    
    परत TRUE;
}

स्थिर शून्य
decode_lf_string (स्थिरांक uchar *s, पूर्णांक n_chars, अक्षर *result)
{
    पूर्णांक i;
    साठी (i = 0; i < n_chars; ++i)
    {
	जर (s[i] == 0x0a)
	{
	    *result++ = '\0';
	    थांबा;
	}
	अन्यथा जर (s[i] == 0x00)
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
decode_display_descriptor (स्थिरांक uchar *desc,
			   MonitorInfo *info)
{
    निवड (desc[0x03])
    {
    स्थिती 0xFC:
	decode_lf_string (desc + 5, 13, info->dsc_product_name);
	थांबा;
    स्थिती 0xFF:
	decode_lf_string (desc + 5, 13, info->dsc_serial_संख्या);
	थांबा;
    स्थिती 0xFE:
	decode_lf_string (desc + 5, 13, info->dsc_string);
	थांबा;
    स्थिती 0xFD:
	/* Range Limits */
	थांबा;
    स्थिती 0xFB:
	/* Color Point */
	थांबा;
    स्थिती 0xFA:
	/* Timing Identifications */
	थांबा;
    स्थिती 0xF9:
	/* Color Management */
	थांबा;
    स्थिती 0xF8:
	/* Timing Codes */
	थांबा;
    स्थिती 0xF7:
	/* Established Timings */
	थांबा;
    स्थिती 0x10:
	थांबा;
    }
}

स्थिर शून्य
decode_detailed_timing (स्थिरांक uchar *timing,
			DetailedTiming *detailed)
{
    पूर्णांक bits;
    StereoType stereo[] =
    {
	NO_STEREO, NO_STEREO, FIELD_उजवा, FIELD_डावा,
	TWO_WAY_उजवा_ON_EVEN, TWO_WAY_डावा_ON_EVEN,
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
    detailed->उजवा_border = timing[0x0f];
    detailed->शीर्ष_border = timing[0x10];

    detailed->interlaced = get_bit (timing[0x11], 7);

    /* Stereo */
    bits = get_bits (timing[0x11], 5, 6) << 1 | get_bit (timing[0x11], 0);
    detailed->stereo = stereo[bits];

    /* Sync */
    bits = timing[0x11];

    detailed->digital_sync = get_bit (bits, 4);
    जर (detailed->digital_sync)
    {
	detailed->ad.digital.composite = !get_bit (bits, 3);

	जर (detailed->ad.digital.composite)
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

स्थिर पूर्णांक
decode_descriptors (स्थिरांक uchar *edid, MonitorInfo *info)
{
    पूर्णांक i;
    पूर्णांक timing_idx;
    
    timing_idx = 0;
    
    साठी (i = 0; i < 4; ++i)
    {
	पूर्णांक index = 0x36 + i * 18;

	जर (edid[index + 0] == 0x00 && edid[index + 1] == 0x00)
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

    परत TRUE;
}

स्थिर शून्य
decode_check_sum (स्थिरांक uchar *edid,
		  MonitorInfo *info)
{
    पूर्णांक i;
    uchar check = 0;

    साठी (i = 0; i < 128; ++i)
	check += edid[i];

    info->checksum = check;
}

स्थिर शून्य
decode_HDR_metadata_block (स्थिरांक uchar *data, पूर्णांक length, MonitorInfo *info)
{
    जर (length >= 3)
	info->max_luminance = 50.0 * SDL_pow(2, data[2] / 32.0);

    जर (length >= 4)
	info->max_frame_average_luminance = 50.0 * SDL_pow(2, data[3] / 32.0);

    जर (length >= 5)
	info->min_luminance = 50.0 * SDL_pow(2, data[4] / 32.0);
}


स्थिर शून्य
decode_cta_block (स्थिरांक uchar *edid,
		  MonitorInfo *info)
{
    पूर्णांक offset = 4;
    पर्यंत (offset < 128) {
	पूर्णांक length = edid[offset] & 0x1f;
	पूर्णांक type = edid[offset] >> 5;
	जर (length == 0) {
	    थांबा;
	}
	जर (type == 7) {
	    type <<= 8;
	    type |= edid[offset + 1];
	}
	जर (type == 0x706) {
	    decode_HDR_metadata_block (&edid[offset + 2], length - 1, info);
	}
	offset += (1 + length);
    }
}

MonitorInfo *
decode_edid (स्थिरांक uchar *edid, माप_प्रकार size)
{
    स्थिरांक पूर्णांक EDID_PAGE_SIZE = 128;
    पूर्णांक अंक_blocks = (size / EDID_PAGE_SIZE);
    MonitorInfo *info;

    जर ((size % EDID_PAGE_SIZE) != 0) {
	परत रिक्त;
    }

    info = SDL_calloc (1, आकार (MonitorInfo));

    decode_check_sum (edid, info);
    
    जर (!decode_header (edid) ||
        !decode_vendor_and_product_identification (edid, info) ||
        !decode_edid_version (edid, info) ||
        !decode_display_parameters (edid, info) ||
        !decode_color_characteristics (edid, info) ||
        !decode_established_timings (edid, info) ||
        !decode_standard_timings (edid, info) ||
        !decode_descriptors (edid, info)) {
	SDL_free(info);
	परत रिक्त;
    }
    
    जर (अंक_blocks > 1) {
	साठी (पूर्णांक i = 1; i < अंक_blocks; ++i) {
	    पूर्णांक offset = i * EDID_PAGE_SIZE;
	    uchar extension = edid[offset];
	    जर (extension == 0x02) {
		// CTA-861 Extension Block
		decode_cta_block (&edid[offset], info);
	    }
	}
    }

    परत info;
}

स्थिर स्थिरांक अक्षर *
yesno (पूर्णांक v)
{
    परत v? "yes" : "no";
}

शून्य
dump_monitor_info (MonitorInfo *info)
{
    पूर्णांक i;
    
    म_लिखो ("Checksum: %d (%s)\n",
	    info->checksum, info->checksum? "incorrect" : "correct");
    म_लिखो ("Manufacturer Code: %s\n", info->manufacturer_code);
    म_लिखो ("Product Code: 0x%x\n", info->product_code);
    म_लिखो ("Serial Number: %u\n", info->serial_संख्या);
    
    जर (info->production_week != -1)
	म_लिखो ("Production Week: %d\n", info->production_week);
    अन्यथा
	म_लिखो ("Production Week: unspecified\n");
    
    जर (info->production_year != -1)
	म_लिखो ("Production Year: %d\n", info->production_year);
    अन्यथा
	म_लिखो ("Production Year: unspecified\n");
    
    जर (info->model_year != -1)
	म_लिखो ("Model Year: %d\n", info->model_year);
    अन्यथा
	म_लिखो ("Model Year: unspecified\n");
    
    म_लिखो ("EDID revision: %d.%d\n", info->major_version, info->minor_version);
    
    म_लिखो ("Display is %s\n", info->is_digital? "digital" : "analog");
    जर (info->is_digital)
    {
	स्थिरांक अक्षर *interface;
	जर (info->ad.digital.bits_per_primary != -1)
	    म_लिखो ("Bits Per Primary: %d\n", info->ad.digital.bits_per_primary);
	अन्यथा
	    म_लिखो ("Bits Per Primary: undefined\n");
	
	निवड (info->ad.digital.interface)
	{
	स्थिती DVI: interface = "DVI"; थांबा;
	स्थिती HDMI_A: interface = "HDMI-a"; थांबा;
	स्थिती HDMI_B: interface = "HDMI-b"; थांबा;
	स्थिती MDDI: interface = "MDDI"; थांबा;
	स्थिती DISPLAY_PORT: interface = "DisplayPort"; थांबा;
	स्थिती UNDEFINED: interface = "undefined"; थांबा;
	पूर्वनिर्धारित: interface = "unknown"; थांबा;
	}
	म_लिखो ("Interface: %s\n", interface);
	
	म_लिखो ("RGB 4:4:4: %s\n", yesno (info->ad.digital.rgb444));
	म_लिखो ("YCrCb 4:4:4: %s\n", yesno (info->ad.digital.ycrcb444));
	म_लिखो ("YCrCb 4:2:2: %s\n", yesno (info->ad.digital.ycrcb422));
    }
    अन्यथा
    {
       स्थिरांक अक्षर *s;
	म_लिखो ("Video Signal Level: %f\n", info->ad.analog.video_signal_level);
	म_लिखो ("Sync Signal Level: %f\n", info->ad.analog.sync_signal_level);
	म_लिखो ("Total Signal Level: %f\n", info->ad.analog.total_signal_level);
	
	म_लिखो ("Blank to Black: %s\n",
		yesno (info->ad.analog.blank_to_black));
	म_लिखो ("Separate HV Sync: %s\n",
		yesno (info->ad.analog.separate_hv_sync));
	म_लिखो ("Composite Sync on H: %s\n",
		yesno (info->ad.analog.composite_sync_on_h));
	म_लिखो ("Serration on VSync: %s\n",
		yesno (info->ad.analog.serration_on_vsync));
	
	निवड (info->ad.analog.color_type)
	{
	स्थिती UNDEFINED_COLOR: s = "undefined"; थांबा;
	स्थिती MONOCHROME: s = "monochrome"; थांबा;
	स्थिती RGB: s = "rgb"; थांबा;
	स्थिती OTHER_COLOR: s = "other color"; थांबा;
	पूर्वनिर्धारित: s = "unknown"; थांबा;
	}
	
	म_लिखो ("Color: %s\n", s);
    }
    
    जर (info->width_mm == -1)
	म_लिखो ("Width: undefined\n");
    अन्यथा
	म_लिखो ("Width: %d mm\n", info->width_mm);
    
    जर (info->height_mm == -1)
	म_लिखो ("Height: undefined\n");
    अन्यथा
	म_लिखो ("Height: %d mm\n", info->height_mm);
    
    जर (info->aspect_ratio > 0)
	म_लिखो ("Aspect Ratio: %f\n", info->aspect_ratio);
    अन्यथा
	म_लिखो ("Aspect Ratio: undefined\n");
    
    जर (info->gamma >= 0)
	म_लिखो ("Gamma: %f\n", info->gamma);
    अन्यथा
	म_लिखो ("Gamma: undefined\n");
    
    म_लिखो ("Standby: %s\n", yesno (info->standby));
    म_लिखो ("Suspend: %s\n", yesno (info->suspend));
    म_लिखो ("Active Off: %s\n", yesno (info->active_off));
    
    म_लिखो ("SRGB is Standard: %s\n", yesno (info->srgb_is_standard));
    म_लिखो ("Preferred Timing Includes Native: %s\n",
	    yesno (info->preferred_timing_includes_native));
    म_लिखो ("Continuous Frequency: %s\n", yesno (info->continuous_frequency));
    
    म_लिखो ("Red X: %f\n", info->red_x);
    म_लिखो ("Red Y: %f\n", info->red_y);
    म_लिखो ("Green X: %f\n", info->green_x);
    म_लिखो ("Green Y: %f\n", info->green_y);
    म_लिखो ("Blue X: %f\n", info->blue_x);
    म_लिखो ("Blue Y: %f\n", info->blue_y);
    म_लिखो ("White X: %f\n", info->white_x);
    म_लिखो ("White Y: %f\n", info->white_y);
    म_लिखो ("Min luminance: %f\n", info->min_luminance);
    म_लिखो ("Max luminance: %f\n", info->max_luminance);
    म_लिखो ("Max frame average luminance %f\n", info->max_frame_average_luminance);
    
    म_लिखो ("Established Timings:\n");
    
    साठी (i = 0; i < 24; ++i)
    {
	Timing *timing = &(info->established[i]);
	
	जर (timing->frequency == 0)
	    थांबा;
	
	म_लिखो ("  %d x %d @ %d Hz\n",
		timing->width, timing->height, timing->frequency);
	
    }
    
    म_लिखो ("Standard Timings:\n");
    साठी (i = 0; i < 8; ++i)
    {
	Timing *timing = &(info->standard[i]);
	
	जर (timing->frequency == 0)
	    थांबा;
	
	म_लिखो ("  %d x %d @ %d Hz\n",
		timing->width, timing->height, timing->frequency);
    }
    
    साठी (i = 0; i < info->n_detailed_timings; ++i)
    {
	DetailedTiming *timing = &(info->detailed_timings[i]);
	स्थिरांक अक्षर *s;
	
	म_लिखो ("Timing%s: \n",
		(i == 0 && info->preferred_timing_includes_native)?
		" (Preferred)" : "");
	म_लिखो ("  Pixel Clock: %d\n", timing->pixel_clock);
	म_लिखो ("  H Addressable: %d\n", timing->h_addr);
	म_लिखो ("  H Blank: %d\n", timing->h_blank);
	म_लिखो ("  H Front Porch: %d\n", timing->h_front_porch);
	म_लिखो ("  H Sync: %d\n", timing->h_sync);
	म_लिखो ("  V Addressable: %d\n", timing->v_addr);
	म_लिखो ("  V Blank: %d\n", timing->v_blank);
	म_लिखो ("  V Front Porch: %d\n", timing->v_front_porch);
	म_लिखो ("  V Sync: %d\n", timing->v_sync);
	म_लिखो ("  Width: %d mm\n", timing->width_mm);
	म_लिखो ("  Height: %d mm\n", timing->height_mm);
	म_लिखो ("  Right Border: %d\n", timing->उजवा_border);
	म_लिखो ("  Top Border: %d\n", timing->शीर्ष_border);
	निवड (timing->stereo)
	{
	पूर्वनिर्धारित:
	स्थिती NO_STEREO:   s = "No Stereo"; थांबा;
	स्थिती FIELD_उजवा: s = "Field Sequential, Right on Sync"; थांबा;
	स्थिती FIELD_डावा:  s = "Field Sequential, Left on Sync"; थांबा;
	स्थिती TWO_WAY_उजवा_ON_EVEN: s = "Two-way, Right on Even"; थांबा;
	स्थिती TWO_WAY_डावा_ON_EVEN:  s = "Two-way, Left on Even"; थांबा;
	स्थिती FOUR_WAY_INTERLEAVED:  s = "Four-way Interleaved"; थांबा;
	स्थिती SIDE_BY_SIDE:          s = "Side-by-Side"; थांबा;
	}
	म_लिखो ("  Stereo: %s\n", s);
	
	जर (timing->digital_sync)
	{
	    म_लिखो ("  Digital Sync:\n");
	    म_लिखो ("    composite: %s\n", yesno (timing->ad.digital.composite));
	    म_लिखो ("    serrations: %s\n", yesno (timing->ad.digital.serrations));
	    म_लिखो ("    negative vsync: %s\n",
		    yesno (timing->ad.digital.negative_vsync));
	    म_लिखो ("    negative hsync: %s\n",
		    yesno (timing->ad.digital.negative_hsync));
	}
	अन्यथा
	{
	    म_लिखो ("  Analog Sync:\n");
	    म_लिखो ("    bipolar: %s\n", yesno (timing->ad.analog.bipolar));
	    म_लिखो ("    serrations: %s\n", yesno (timing->ad.analog.serrations));
	    म_लिखो ("    sync on green: %s\n", yesno (
			timing->ad.analog.sync_on_green));
	}
    }
    
    म_लिखो ("Detailed Product information:\n");
    म_लिखो ("  Product Name: %s\n", info->dsc_product_name);
    म_लिखो ("  Serial Number: %s\n", info->dsc_serial_संख्या);
    म_लिखो ("  Unspecified String: %s\n", info->dsc_string);
}

