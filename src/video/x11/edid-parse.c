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
#समावेश "SDL_internal.h"

#समावेश "edid.h"
#समावेश <stdlib.h>
#समावेश <string.h>
#समावेश <math.h>
#समावेश <stdio.h>

#घोषणा TRUE 1
#घोषणा FALSE 0

अटल पूर्णांक
get_bit (पूर्णांक in, पूर्णांक bit)
{
    वापस (in & (1 << bit)) >> bit;
}

अटल पूर्णांक
get_bits (पूर्णांक in, पूर्णांक begin, पूर्णांक end)
{
    पूर्णांक mask = (1 << (end - begin + 1)) - 1;
    
    वापस (in >> begin) & mask;
}

अटल पूर्णांक
decode_header (स्थिर uchar *edid)
{
    अगर (SDL_memcmp (edid, "\x00\xff\xff\xff\xff\xff\xff\x00", 8) == 0)
	वापस TRUE;
    वापस FALSE;
}

अटल पूर्णांक
decode_vendor_and_product_identification (स्थिर uchar *edid, MonitorInfo *info)
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
    चयन (edid[0x10])
    {
    हाल 0x00:
	info->production_week = -1;
	अवरोध;

    हाल 0xff:
	info->production_week = -1;
	is_model_year = TRUE;
	अवरोध;

    शेष:
	info->production_week = edid[0x10];
	अवरोध;
    }

    अगर (is_model_year)
    {
	info->production_year = -1;
	info->model_year = 1990 + edid[0x11];
    }
    अन्यथा
    {
	info->production_year = 1990 + edid[0x11];
	info->model_year = -1;
    }

    वापस TRUE;
}

अटल पूर्णांक
decode_edid_version (स्थिर uchar *edid, MonitorInfo *info)
{
    info->major_version = edid[0x12];
    info->minor_version = edid[0x13];

    वापस TRUE;
}

अटल पूर्णांक
decode_display_parameters (स्थिर uchar *edid, MonitorInfo *info)
{
    /* Digital vs Analog */
    info->is_digital = get_bit (edid[0x14], 7);

    अगर (info->is_digital)
    {
	पूर्णांक bits;
	
	अटल स्थिर पूर्णांक bit_depth[8] =
	{
	    -1, 6, 8, 10, 12, 14, 16, -1
	};

	अटल स्थिर Interface interfaces[6] =
	{
	    UNDEFINED, DVI, HDMI_A, HDMI_B, MDDI, DISPLAY_PORT
	};

	bits = get_bits (edid[0x14], 4, 6);
	info->ad.digital.bits_per_primary = bit_depth[bits];

	bits = get_bits (edid[0x14], 0, 3);
	
	अगर (bits <= 5)
	    info->ad.digital.interface = interfaces[bits];
	अन्यथा
	    info->ad.digital.interface = UNDEFINED;
    }
    अन्यथा
    {
	पूर्णांक bits = get_bits (edid[0x14], 5, 6);
	
	अटल स्थिर द्विगुन levels[][3] =
	{
	    { 0.7,   0.3,    1.0 },
	    { 0.714, 0.286,  1.0 },
	    { 1.0,   0.4,    1.4 },
	    { 0.7,   0.0,    0.7 },
	};

	info->ad.analog.video_signal_level = levels[bits][0];
	info->ad.analog.sync_signal_level = levels[bits][1];
	info->ad.analog.योग_signal_level = levels[bits][2];

	info->ad.analog.blank_to_black = get_bit (edid[0x14], 4);

	info->ad.analog.separate_hv_sync = get_bit (edid[0x14], 3);
	info->ad.analog.composite_sync_on_h = get_bit (edid[0x14], 2);
	info->ad.analog.composite_sync_on_green = get_bit (edid[0x14], 1);

	info->ad.analog.serration_on_vsync = get_bit (edid[0x14], 0);
    }

    /* Screen Size / Aspect Ratio */
    अगर (edid[0x15] == 0 && edid[0x16] == 0)
    {
	info->width_mm = -1;
	info->height_mm = -1;
	info->aspect_ratio = -1.0;
    }
    अन्यथा अगर (edid[0x16] == 0)
    {
	info->width_mm = -1;
	info->height_mm = -1; 
	info->aspect_ratio = 100.0 / (edid[0x15] + 99);
    }
    अन्यथा अगर (edid[0x15] == 0)
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
    अगर (edid[0x17] == 0xFF)
	info->gamma = -1.0;
    अन्यथा
	info->gamma = (edid[0x17] + 100.0) / 100.0;

    /* Features */
    info->standby = get_bit (edid[0x18], 7);
    info->suspend = get_bit (edid[0x18], 6);
    info->active_off = get_bit (edid[0x18], 5);

    अगर (info->is_digital)
    {
	info->ad.digital.rgb444 = TRUE;
	अगर (get_bit (edid[0x18], 3))
	    info->ad.digital.ycrcb444 = 1;
	अगर (get_bit (edid[0x18], 4))
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
    वापस TRUE;
}

अटल द्विगुन
decode_fraction (पूर्णांक ऊपरी, पूर्णांक निचला)
{
    द्विगुन परिणाम = 0.0;
    पूर्णांक i;

    ऊपरी = (ऊपरी << 2) | निचला;

    क्रम (i = 0; i < 10; ++i)
	परिणाम += get_bit (ऊपरी, i) * SDL_pow (2, i - 10);

    वापस परिणाम;
}

अटल पूर्णांक
decode_color_characteristics (स्थिर uchar *edid, MonitorInfo *info)
{
    info->red_x = decode_fraction (edid[0x1b], get_bits (edid[0x19], 6, 7));
    info->red_y = decode_fraction (edid[0x1c], get_bits (edid[0x19], 5, 4));
    info->green_x = decode_fraction (edid[0x1d], get_bits (edid[0x19], 2, 3));
    info->green_y = decode_fraction (edid[0x1e], get_bits (edid[0x19], 0, 1));
    info->blue_x = decode_fraction (edid[0x1f], get_bits (edid[0x1a], 6, 7));
    info->blue_y = decode_fraction (edid[0x20], get_bits (edid[0x1a], 4, 5));
    info->white_x = decode_fraction (edid[0x21], get_bits (edid[0x1a], 2, 3));
    info->white_y = decode_fraction (edid[0x22], get_bits (edid[0x1a], 0, 1));

    वापस TRUE;
}

अटल पूर्णांक
decode_established_timings (स्थिर uchar *edid, MonitorInfo *info)
{
    अटल स्थिर Timing established[][8] = 
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
    क्रम (i = 0; i < 3; ++i)
    {
	क्रम (j = 0; j < 8; ++j)
	{
	    पूर्णांक byte = edid[0x23 + i];

	    अगर (get_bit (byte, j) && established[i][j].frequency != 0)
		info->established[idx++] = established[i][j];
	}
    }
    वापस TRUE;
}

अटल पूर्णांक
decode_standard_timings (स्थिर uchar *edid, MonitorInfo *info)
{
    पूर्णांक i;
    
    क्रम (i = 0; i < 8; i++)
    {
	पूर्णांक first = edid[0x26 + 2 * i];
	पूर्णांक second = edid[0x27 + 2 * i];

	अगर (first != 0x01 && second != 0x01)
	{
	    पूर्णांक w = 8 * (first + 31);
	    पूर्णांक h = 0;

	    चयन (get_bits (second, 6, 7))
	    {
	    हाल 0x00: h = (w / 16) * 10; अवरोध;
	    हाल 0x01: h = (w / 4) * 3; अवरोध;
	    हाल 0x02: h = (w / 5) * 4; अवरोध;
	    हाल 0x03: h = (w / 16) * 9; अवरोध;
	    }

	    info->standard[i].width = w;
	    info->standard[i].height = h;
	    info->standard[i].frequency = get_bits (second, 0, 5) + 60;
	}
    }
    
    वापस TRUE;
}

अटल व्योम
decode_lf_string (स्थिर uchar *s, पूर्णांक n_chars, अक्षर *परिणाम)
{
    पूर्णांक i;
    क्रम (i = 0; i < n_chars; ++i)
    {
	अगर (s[i] == 0x0a)
	{
	    *परिणाम++ = '\0';
	    अवरोध;
	}
	अन्यथा अगर (s[i] == 0x00)
	{
	    /* Convert embedded 0's to spaces */
	    *परिणाम++ = ' ';
	}
	अन्यथा
	{
	    *परिणाम++ = s[i];
	}
    }
}

अटल व्योम
decode_display_descriptor (स्थिर uchar *desc,
			   MonitorInfo *info)
{
    चयन (desc[0x03])
    {
    हाल 0xFC:
	decode_lf_string (desc + 5, 13, info->dsc_product_name);
	अवरोध;
    हाल 0xFF:
	decode_lf_string (desc + 5, 13, info->dsc_serial_संख्या);
	अवरोध;
    हाल 0xFE:
	decode_lf_string (desc + 5, 13, info->dsc_string);
	अवरोध;
    हाल 0xFD:
	/* Range Limits */
	अवरोध;
    हाल 0xFB:
	/* Color Point */
	अवरोध;
    हाल 0xFA:
	/* Timing Identifications */
	अवरोध;
    हाल 0xF9:
	/* Color Management */
	अवरोध;
    हाल 0xF8:
	/* Timing Codes */
	अवरोध;
    हाल 0xF7:
	/* Established Timings */
	अवरोध;
    हाल 0x10:
	अवरोध;
    }
}

अटल व्योम
decode_detailed_timing (स्थिर uchar *timing,
			DetailedTiming *detailed)
{
    पूर्णांक bits;
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
    अगर (detailed->digital_sync)
    {
	detailed->ad.digital.composite = !get_bit (bits, 3);

	अगर (detailed->ad.digital.composite)
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

अटल पूर्णांक
decode_descriptors (स्थिर uchar *edid, MonitorInfo *info)
{
    पूर्णांक i;
    पूर्णांक timing_idx;
    
    timing_idx = 0;
    
    क्रम (i = 0; i < 4; ++i)
    {
	पूर्णांक सूचकांक = 0x36 + i * 18;

	अगर (edid[सूचकांक + 0] == 0x00 && edid[सूचकांक + 1] == 0x00)
	{
	    decode_display_descriptor (edid + सूचकांक, info);
	}
	अन्यथा
	{
	    decode_detailed_timing (
		edid + सूचकांक, &(info->detailed_timings[timing_idx++]));
	}
    }

    info->n_detailed_timings = timing_idx;

    वापस TRUE;
}

अटल व्योम
decode_check_योग (स्थिर uchar *edid,
		  MonitorInfo *info)
{
    पूर्णांक i;
    uchar check = 0;

    क्रम (i = 0; i < 128; ++i)
	check += edid[i];

    info->checksum = check;
}

अटल व्योम
decode_HDR_metadata_block (स्थिर uchar *तथ्य, पूर्णांक लंबाई, MonitorInfo *info)
{
    अगर (लंबाई >= 3)
	info->max_luminance = 50.0 * SDL_pow(2, तथ्य[2] / 32.0);

    अगर (लंबाई >= 4)
	info->max_frame_average_luminance = 50.0 * SDL_pow(2, तथ्य[3] / 32.0);

    अगर (लंबाई >= 5)
	info->min_luminance = 50.0 * SDL_pow(2, तथ्य[4] / 32.0);
}


अटल व्योम
decode_cta_block (स्थिर uchar *edid,
		  MonitorInfo *info)
{
    पूर्णांक offset = 4;
    जबतक (offset < 128) {
	पूर्णांक लंबाई = edid[offset] & 0x1f;
	पूर्णांक type = edid[offset] >> 5;
	अगर (लंबाई == 0) {
	    अवरोध;
	}
	अगर (type == 7) {
	    type <<= 8;
	    type |= edid[offset + 1];
	}
	अगर (type == 0x706) {
	    decode_HDR_metadata_block (&edid[offset + 2], लंबाई - 1, info);
	}
	offset += (1 + लंबाई);
    }
}

MonitorInfo *
decode_edid (स्थिर uchar *edid, माप_प्रकार आकार)
{
    स्थिर पूर्णांक EDID_PAGE_आकार = 128;
    पूर्णांक अंक_blocks = (आकार / EDID_PAGE_आकार);
    MonitorInfo *info;

    अगर ((आकार % EDID_PAGE_आकार) != 0) {
	वापस शून्य;
    }

    info = SDL_calloc (1, माप (MonitorInfo));

    decode_check_योग (edid, info);
    
    अगर (!decode_header (edid) ||
        !decode_vendor_and_product_identification (edid, info) ||
        !decode_edid_version (edid, info) ||
        !decode_display_parameters (edid, info) ||
        !decode_color_characteristics (edid, info) ||
        !decode_established_timings (edid, info) ||
        !decode_standard_timings (edid, info) ||
        !decode_descriptors (edid, info)) {
	SDL_free(info);
	वापस शून्य;
    }
    
    अगर (अंक_blocks > 1) {
	क्रम (पूर्णांक i = 1; i < अंक_blocks; ++i) {
	    पूर्णांक offset = i * EDID_PAGE_आकार;
	    uchar extension = edid[offset];
	    अगर (extension == 0x02) {
		// CTA-861 Extension Block
		decode_cta_block (&edid[offset], info);
	    }
	}
    }

    वापस info;
}

अटल स्थिर अक्षर *
yesno (पूर्णांक v)
{
    वापस v? "yes" : "no";
}

व्योम
dump_monitor_info (MonitorInfo *info)
{
    पूर्णांक i;
    
    म_लिखो ("Checksum: %d (%s)\n",
	    info->checksum, info->checksum? "incorrect" : "correct");
    म_लिखो ("Manufacturer Code: %s\n", info->manufacturer_code);
    म_लिखो ("Product Code: 0x%x\n", info->product_code);
    म_लिखो ("Serial Number: %u\n", info->serial_संख्या);
    
    अगर (info->production_week != -1)
	म_लिखो ("Production Week: %d\n", info->production_week);
    अन्यथा
	म_लिखो ("Production Week: unspecified\n");
    
    अगर (info->production_year != -1)
	म_लिखो ("Production Year: %d\n", info->production_year);
    अन्यथा
	म_लिखो ("Production Year: unspecified\n");
    
    अगर (info->model_year != -1)
	म_लिखो ("Model Year: %d\n", info->model_year);
    अन्यथा
	म_लिखो ("Model Year: unspecified\n");
    
    म_लिखो ("EDID revision: %d.%d\n", info->major_version, info->minor_version);
    
    म_लिखो ("Display is %s\n", info->is_digital? "digital" : "analog");
    अगर (info->is_digital)
    {
	स्थिर अक्षर *interface;
	अगर (info->ad.digital.bits_per_primary != -1)
	    म_लिखो ("Bits Per Primary: %d\n", info->ad.digital.bits_per_primary);
	अन्यथा
	    म_लिखो ("Bits Per Primary: undefined\n");
	
	चयन (info->ad.digital.interface)
	{
	हाल DVI: interface = "DVI"; अवरोध;
	हाल HDMI_A: interface = "HDMI-a"; अवरोध;
	हाल HDMI_B: interface = "HDMI-b"; अवरोध;
	हाल MDDI: interface = "MDDI"; अवरोध;
	हाल DISPLAY_PORT: interface = "DisplayPort"; अवरोध;
	हाल UNDEFINED: interface = "undefined"; अवरोध;
	शेष: interface = "unknown"; अवरोध;
	}
	म_लिखो ("Interface: %s\n", interface);
	
	म_लिखो ("RGB 4:4:4: %s\n", yesno (info->ad.digital.rgb444));
	म_लिखो ("YCrCb 4:4:4: %s\n", yesno (info->ad.digital.ycrcb444));
	म_लिखो ("YCrCb 4:2:2: %s\n", yesno (info->ad.digital.ycrcb422));
    }
    अन्यथा
    {
       स्थिर अक्षर *s;
	म_लिखो ("Video Signal Level: %f\n", info->ad.analog.video_signal_level);
	म_लिखो ("Sync Signal Level: %f\n", info->ad.analog.sync_signal_level);
	म_लिखो ("Total Signal Level: %f\n", info->ad.analog.योग_signal_level);
	
	म_लिखो ("Blank to Black: %s\n",
		yesno (info->ad.analog.blank_to_black));
	म_लिखो ("Separate HV Sync: %s\n",
		yesno (info->ad.analog.separate_hv_sync));
	म_लिखो ("Composite Sync on H: %s\n",
		yesno (info->ad.analog.composite_sync_on_h));
	म_लिखो ("Serration on VSync: %s\n",
		yesno (info->ad.analog.serration_on_vsync));
	
	चयन (info->ad.analog.color_type)
	{
	हाल UNDEFINED_COLOR: s = "undefined"; अवरोध;
	हाल MONOCHROME: s = "monochrome"; अवरोध;
	हाल RGB: s = "rgb"; अवरोध;
	हाल OTHER_COLOR: s = "other color"; अवरोध;
	शेष: s = "unknown"; अवरोध;
	}
	
	म_लिखो ("Color: %s\n", s);
    }
    
    अगर (info->width_mm == -1)
	म_लिखो ("Width: undefined\n");
    अन्यथा
	म_लिखो ("Width: %d mm\n", info->width_mm);
    
    अगर (info->height_mm == -1)
	म_लिखो ("Height: undefined\n");
    अन्यथा
	म_लिखो ("Height: %d mm\n", info->height_mm);
    
    अगर (info->aspect_ratio > 0)
	म_लिखो ("Aspect Ratio: %f\n", info->aspect_ratio);
    अन्यथा
	म_लिखो ("Aspect Ratio: undefined\n");
    
    अगर (info->gamma >= 0)
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
    
    क्रम (i = 0; i < 24; ++i)
    {
	Timing *timing = &(info->established[i]);
	
	अगर (timing->frequency == 0)
	    अवरोध;
	
	म_लिखो ("  %d x %d @ %d Hz\n",
		timing->width, timing->height, timing->frequency);
	
    }
    
    म_लिखो ("Standard Timings:\n");
    क्रम (i = 0; i < 8; ++i)
    {
	Timing *timing = &(info->standard[i]);
	
	अगर (timing->frequency == 0)
	    अवरोध;
	
	म_लिखो ("  %d x %d @ %d Hz\n",
		timing->width, timing->height, timing->frequency);
    }
    
    क्रम (i = 0; i < info->n_detailed_timings; ++i)
    {
	DetailedTiming *timing = &(info->detailed_timings[i]);
	स्थिर अक्षर *s;
	
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
	म_लिखो ("  Right Border: %d\n", timing->दायाँ_border);
	म_लिखो ("  Top Border: %d\n", timing->शीर्ष_border);
	चयन (timing->stereo)
	{
	शेष:
	हाल NO_STEREO:   s = "No Stereo"; अवरोध;
	हाल FIELD_दायाँ: s = "Field Sequential, Right on Sync"; अवरोध;
	हाल FIELD_बायाँ:  s = "Field Sequential, Left on Sync"; अवरोध;
	हाल TWO_WAY_दायाँ_ON_EVEN: s = "Two-way, Right on Even"; अवरोध;
	हाल TWO_WAY_बायाँ_ON_EVEN:  s = "Two-way, Left on Even"; अवरोध;
	हाल FOUR_WAY_INTERLEAVED:  s = "Four-way Interleaved"; अवरोध;
	हाल SIDE_BY_SIDE:          s = "Side-by-Side"; अवरोध;
	}
	म_लिखो ("  Stereo: %s\n", s);
	
	अगर (timing->digital_sync)
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

