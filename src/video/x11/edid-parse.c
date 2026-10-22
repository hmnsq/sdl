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

#परिभाषय TRUE 1
#परिभाषय FALSE 0

स्थिर पूर्णाङ्क
get_bit (पूर्णाङ्क अन्तर्_2, पूर्णाङ्क bit)
{
    प्रत्यागम (अन्तर्_2 & (1 << bit)) >> bit;
}

स्थिर पूर्णाङ्क
get_द्वयङ्काः (पूर्णाङ्क अन्तर्_2, पूर्णाङ्क begin, पूर्णाङ्क अन्तः)
{
    पूर्णाङ्क आवरणम् = (1 << (अन्तः - begin + 1)) - 1;
    
    प्रत्यागम (अन्तर्_2 >> begin) & आवरणम्;
}

स्थिर पूर्णाङ्क
decode_शीर्षकम् (ध्रुव uchar *edid)
{
    यदि (SDL_memcmp (edid, "\x00\xff\xff\xff\xff\xff\xff\x00", 8) == 0)
	प्रत्यागम TRUE;
    प्रत्यागम FALSE;
}

स्थिर पूर्णाङ्क
decode_vendor_and_गुणनफलम्_identification (ध्रुव uchar *edid, MonitorInfo *info)
{
    पूर्णाङ्क is_model_year;
    
    /* Manufacturer Code */
    info->manufacturer_संहिता[0]  = get_द्वयङ्काः (edid[0x08], 2, 6);
    info->manufacturer_संहिता[1]  = get_द्वयङ्काः (edid[0x08], 0, 1) << 3;
    info->manufacturer_संहिता[1] |= get_द्वयङ्काः (edid[0x09], 5, 7);
    info->manufacturer_संहिता[2]  = get_द्वयङ्काः (edid[0x09], 0, 4);
    info->manufacturer_संहिता[3]  = '\0';
    
    info->manufacturer_संहिता[0] += 'A' - 1;
    info->manufacturer_संहिता[1] += 'A' - 1;
    info->manufacturer_संहिता[2] += 'A' - 1;

    /* Product Code */
    info->गुणनफलम्_संहिता = edid[0x0b] << 8 | edid[0x0a];

    /* Serial Number */
    info->serial_सङ्ख्या =
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
decode_edid_संस्करणम् (ध्रुव uchar *edid, MonitorInfo *info)
{
    info->major_संस्करणम् = edid[0x12];
    info->minor_संस्करणम् = edid[0x13];

    प्रत्यागम TRUE;
}

स्थिर पूर्णाङ्क
decode_display_parameters (ध्रुव uchar *edid, MonitorInfo *info)
{
    /* Digital vs Analog */
    info->is_digital = get_bit (edid[0x14], 7);

    यदि (info->is_digital)
    {
	पूर्णाङ्क द्वयङ्काः;
	
	स्थिर ध्रुव पूर्णाङ्क bit_गभीरता[8] =
	{
	    -1, 6, 8, 10, 12, 14, 16, -1
	};

	स्थिर ध्रुव Interface interfaces[6] =
	{
	    UNDEFINED, DVI, HDMI_A, HDMI_B, MDDI, DISPLAY_पत्तनम्
	};

	द्वयङ्काः = get_द्वयङ्काः (edid[0x14], 4, 6);
	info->ad.digital.द्वयङ्काः_प्रत्येकम्_primary = bit_गभीरता[द्वयङ्काः];

	द्वयङ्काः = get_द्वयङ्काः (edid[0x14], 0, 3);
	
	यदि (द्वयङ्काः <= 5)
	    info->ad.digital.interface = interfaces[द्वयङ्काः];
	अन्यथा
	    info->ad.digital.interface = UNDEFINED;
    }
    अन्यथा
    {
	पूर्णाङ्क द्वयङ्काः = get_द्वयङ्काः (edid[0x14], 5, 6);
	
	स्थिर ध्रुव द्विगुण स्तराः[][3] =
	{
	    { 0.7,   0.3,    1.0 },
	    { 0.714, 0.286,  1.0 },
	    { 1.0,   0.4,    1.4 },
	    { 0.7,   0.0,    0.7 },
	};

	info->ad.analog.video_signal_level = स्तराः[द्वयङ्काः][0];
	info->ad.analog.sync_signal_level = स्तराः[द्वयङ्काः][1];
	info->ad.analog.योग_signal_level = स्तराः[द्वयङ्काः][2];

	info->ad.analog.blank_गन्तव्यम्_black = get_bit (edid[0x14], 4);

	info->ad.analog.separate_hv_sync = get_bit (edid[0x14], 3);
	info->ad.analog.संयुक्त_sync_on_h = get_bit (edid[0x14], 2);
	info->ad.analog.संयुक्त_sync_on_green = get_bit (edid[0x14], 1);

	info->ad.analog.serration_on_vsync = get_bit (edid[0x14], 0);
    }

    /* Screen Size / Aspect Ratio */
    यदि (edid[0x15] == 0 && edid[0x16] == 0)
    {
	info->विस्तारः_mm = -1;
	info->height_mm = -1;
	info->aspect_अनुपातः = -1.0;
    }
    अन्यथा यदि (edid[0x16] == 0)
    {
	info->विस्तारः_mm = -1;
	info->height_mm = -1; 
	info->aspect_अनुपातः = 100.0 / (edid[0x15] + 99);
    }
    अन्यथा यदि (edid[0x15] == 0)
    {
	info->विस्तारः_mm = -1;
	info->height_mm = -1;
	info->aspect_अनुपातः = 100.0 / (edid[0x16] + 99);
	info->aspect_अनुपातः = 1/info->aspect_अनुपातः; /* portrait */
    }
    अन्यथा
    {
	info->विस्तारः_mm = 10 * edid[0x15];
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
    info->सक्रिय_off = get_bit (edid[0x18], 5);

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
	पूर्णाङ्क द्वयङ्काः = get_द्वयङ्काः (edid[0x18], 3, 4);
	ColorType color_type[4] =
	{
	    MONOCHROME, RGB, OTHER_COLOR, UNDEFINED_COLOR
	};

	info->ad.analog.color_type = color_type[द्वयङ्काः];
    }

    info->srgb_is_standard = get_bit (edid[0x18], 2);

    /* In 1.3 this is called "has preferred timing" */
    info->preferred_timing_includes_native = get_bit (edid[0x18], 1);

    /* FIXME: In 1.3 this indicates whether the monitor accepts GTF */
    info->continuous_frequency = get_bit (edid[0x18], 0);
    प्रत्यागम TRUE;
}

स्थिर द्विगुण
decode_fraction (पूर्णाङ्क उच्चः, पूर्णाङ्क नीचः)
{
    द्विगुण परिणाम = 0.0;
    पूर्णाङ्क i;

    उच्चः = (उच्चः << 2) | नीचः;

    प्रति (i = 0; i < 10; ++i)
	परिणाम += get_bit (उच्चः, i) * SDL_pow (2, i - 10);

    प्रत्यागम परिणाम;
}

स्थिर पूर्णाङ्क
decode_color_characteristics (ध्रुव uchar *edid, MonitorInfo *info)
{
    info->red_x = decode_fraction (edid[0x1b], get_द्वयङ्काः (edid[0x19], 6, 7));
    info->red_y = decode_fraction (edid[0x1c], get_द्वयङ्काः (edid[0x19], 5, 4));
    info->green_x = decode_fraction (edid[0x1d], get_द्वयङ्काः (edid[0x19], 2, 3));
    info->green_y = decode_fraction (edid[0x1e], get_द्वयङ्काः (edid[0x19], 0, 1));
    info->blue_x = decode_fraction (edid[0x1f], get_द्वयङ्काः (edid[0x1a], 6, 7));
    info->blue_y = decode_fraction (edid[0x20], get_द्वयङ्काः (edid[0x1a], 4, 5));
    info->white_x = decode_fraction (edid[0x21], get_द्वयङ्काः (edid[0x1a], 2, 3));
    info->white_y = decode_fraction (edid[0x22], get_द्वयङ्काः (edid[0x1a], 0, 1));

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

	    विकल्प (get_द्वयङ्काः (second, 6, 7))
	    {
	    पक्ष 0x00: h = (w / 16) * 10; भङ्ग;
	    पक्ष 0x01: h = (w / 4) * 3; भङ्ग;
	    पक्ष 0x02: h = (w / 5) * 4; भङ्ग;
	    पक्ष 0x03: h = (w / 16) * 9; भङ्ग;
	    }

	    info->standard[i].विस्तारः = w;
	    info->standard[i].height = h;
	    info->standard[i].frequency = get_द्वयङ्काः (second, 0, 5) + 60;
	}
    }
    
    प्रत्यागम TRUE;
}

स्थिर शून्य
decode_lf_string (ध्रुव uchar *s, पूर्णाङ्क n_chars, वर्ण *परिणाम)
{
    पूर्णाङ्क i;
    प्रति (i = 0; i < n_chars; ++i)
    {
	यदि (s[i] == 0x0a)
	{
	    *परिणाम++ = '\0';
	    भङ्ग;
	}
	अन्यथा यदि (s[i] == 0x00)
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

स्थिर शून्य
decode_display_descriptor (ध्रुव uchar *desc,
			   MonitorInfo *info)
{
    विकल्प (desc[0x03])
    {
    पक्ष 0xFC:
	decode_lf_string (desc + 5, 13, info->dsc_गुणनफलम्_name);
	भङ्ग;
    पक्ष 0xFF:
	decode_lf_string (desc + 5, 13, info->dsc_serial_सङ्ख्या);
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
    पूर्णाङ्क द्वयङ्काः;
    StereoType stereo[] =
    {
	NO_STEREO, NO_STEREO, क्षेत्रम्_दक्षिणः, क्षेत्रम्_वामः,
	TWO_WAY_दक्षिणः_ON_EVEN, TWO_WAY_वामः_ON_EVEN,
	FOUR_WAY_INTERLEAVED, SIDE_BY_SIDE
    };
    
    detailed->pixel_clock = (timing[0x00] | timing[0x01] << 8) * 10000;
    detailed->h_addr = timing[0x02] | ((timing[0x04] & 0xf0) << 4);
    detailed->h_blank = timing[0x03] | ((timing[0x04] & 0x0f) << 8);
    detailed->v_addr = timing[0x05] | ((timing[0x07] & 0xf0) << 4);
    detailed->v_blank = timing[0x06] | ((timing[0x07] & 0x0f) << 8);
    detailed->h_front_porch = timing[0x08] | get_द्वयङ्काः (timing[0x0b], 6, 7) << 8;
    detailed->h_sync = timing[0x09] | get_द्वयङ्काः (timing[0x0b], 4, 5) << 8;
    detailed->v_front_porch =
	get_द्वयङ्काः (timing[0x0a], 4, 7) | get_द्वयङ्काः (timing[0x0b], 2, 3) << 4;
    detailed->v_sync =
	get_द्वयङ्काः (timing[0x0a], 0, 3) | get_द्वयङ्काः (timing[0x0b], 0, 1) << 4;
    detailed->विस्तारः_mm =  timing[0x0c] | get_द्वयङ्काः (timing[0x0e], 4, 7) << 8;
    detailed->height_mm = timing[0x0d] | get_द्वयङ्काः (timing[0x0e], 0, 3) << 8;
    detailed->दक्षिणः_border = timing[0x0f];
    detailed->शिखरम्_border = timing[0x10];

    detailed->interlaced = get_bit (timing[0x11], 7);

    /* Stereo */
    द्वयङ्काः = get_द्वयङ्काः (timing[0x11], 5, 6) << 1 | get_bit (timing[0x11], 0);
    detailed->stereo = stereo[द्वयङ्काः];

    /* Sync */
    द्वयङ्काः = timing[0x11];

    detailed->digital_sync = get_bit (द्वयङ्काः, 4);
    यदि (detailed->digital_sync)
    {
	detailed->ad.digital.संयुक्त = !get_bit (द्वयङ्काः, 3);

	यदि (detailed->ad.digital.संयुक्त)
	{
	    detailed->ad.digital.serrations = get_bit (द्वयङ्काः, 2);
	    detailed->ad.digital.negative_vsync = FALSE;
	}
	अन्यथा
	{
	    detailed->ad.digital.serrations = FALSE;
	    detailed->ad.digital.negative_vsync = !get_bit (द्वयङ्काः, 2);
	}

	detailed->ad.digital.negative_hsync = !get_bit (द्वयङ्काः, 0);
    }
    अन्यथा
    {
	detailed->ad.analog.bipolar = get_bit (द्वयङ्काः, 3);
	detailed->ad.analog.serrations = get_bit (द्वयङ्काः, 2);
	detailed->ad.analog.sync_on_green = !get_bit (द्वयङ्काः, 1);
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
	पूर्णाङ्क सूचकांक = 0x36 + i * 18;

	यदि (edid[सूचकांक + 0] == 0x00 && edid[सूचकांक + 1] == 0x00)
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

    प्रत्यागम TRUE;
}

स्थिर शून्य
decode_check_योग (ध्रुव uchar *edid,
		  MonitorInfo *info)
{
    पूर्णाङ्क i;
    uchar check = 0;

    प्रति (i = 0; i < 128; ++i)
	check += edid[i];

    info->checksum = check;
}

स्थिर शून्य
decode_HDR_metadata_खण्डम् (ध्रुव uchar *दत्त, पूर्णाङ्क दीर्घता, MonitorInfo *info)
{
    यदि (दीर्घता >= 3)
	info->max_luminance = 50.0 * SDL_pow(2, दत्त[2] / 32.0);

    यदि (दीर्घता >= 4)
	info->max_frame_मध्यमानम्_luminance = 50.0 * SDL_pow(2, दत्त[3] / 32.0);

    यदि (दीर्घता >= 5)
	info->min_luminance = 50.0 * SDL_pow(2, दत्त[4] / 32.0);
}


स्थिर शून्य
decode_cta_खण्डम् (ध्रुव uchar *edid,
		  MonitorInfo *info)
{
    पूर्णाङ्क विस्थापनम्_2 = 4;
    यावत् (विस्थापनम्_2 < 128) {
	पूर्णाङ्क दीर्घता = edid[विस्थापनम्_2] & 0x1f;
	पूर्णाङ्क type = edid[विस्थापनम्_2] >> 5;
	यदि (दीर्घता == 0) {
	    भङ्ग;
	}
	यदि (type == 7) {
	    type <<= 8;
	    type |= edid[विस्थापनम्_2 + 1];
	}
	यदि (type == 0x706) {
	    decode_HDR_metadata_खण्डम् (&edid[विस्थापनम्_2 + 2], दीर्घता - 1, info);
	}
	विस्थापनम्_2 += (1 + दीर्घता);
    }
}

MonitorInfo *
decode_edid (ध्रुव uchar *edid, size_t आकार)
{
    ध्रुव पूर्णाङ्क EDID_PAGE_आकार = 128;
    पूर्णाङ्क अङ्कः_खण्डानि = (आकार / EDID_PAGE_आकार);
    MonitorInfo *info;

    यदि ((आकार % EDID_PAGE_आकार) != 0) {
	प्रत्यागम रिक्त;
    }

    info = SDL_calloc (1, परिमाण (MonitorInfo));

    decode_check_योग (edid, info);
    
    यदि (!decode_शीर्षकम् (edid) ||
        !decode_vendor_and_गुणनफलम्_identification (edid, info) ||
        !decode_edid_संस्करणम् (edid, info) ||
        !decode_display_parameters (edid, info) ||
        !decode_color_characteristics (edid, info) ||
        !decode_established_timings (edid, info) ||
        !decode_standard_timings (edid, info) ||
        !decode_descriptors (edid, info)) {
	SDL_free(info);
	प्रत्यागम रिक्त;
    }
    
    यदि (अङ्कः_खण्डानि > 1) {
	प्रति (पूर्णाङ्क i = 1; i < अङ्कः_खण्डानि; ++i) {
	    पूर्णाङ्क विस्थापनम्_2 = i * EDID_PAGE_आकार;
	    uchar extension = edid[विस्थापनम्_2];
	    यदि (extension == 0x02) {
		// CTA-861 Extension Block
		decode_cta_खण्डम् (&edid[विस्थापनम्_2], info);
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
    
    प्रारूप_लिख ("Checksum: %d (%s)\n",
	    info->checksum, info->checksum? "incorrect" : "correct");
    प्रारूप_लिख ("Manufacturer Code: %s\n", info->manufacturer_संहिता);
    प्रारूप_लिख ("Product Code: 0x%x\n", info->गुणनफलम्_संहिता);
    प्रारूप_लिख ("Serial Number: %u\n", info->serial_सङ्ख्या);
    
    यदि (info->production_week != -1)
	प्रारूप_लिख ("Production Week: %d\n", info->production_week);
    अन्यथा
	प्रारूप_लिख ("Production Week: unspecified\n");
    
    यदि (info->production_year != -1)
	प्रारूप_लिख ("Production Year: %d\n", info->production_year);
    अन्यथा
	प्रारूप_लिख ("Production Year: unspecified\n");
    
    यदि (info->model_year != -1)
	प्रारूप_लिख ("Model Year: %d\n", info->model_year);
    अन्यथा
	प्रारूप_लिख ("Model Year: unspecified\n");
    
    प्रारूप_लिख ("EDID revision: %d.%d\n", info->major_संस्करणम्, info->minor_संस्करणम्);
    
    प्रारूप_लिख ("Display is %s\n", info->is_digital? "digital" : "analog");
    यदि (info->is_digital)
    {
	ध्रुव वर्ण *interface;
	यदि (info->ad.digital.द्वयङ्काः_प्रत्येकम्_primary != -1)
	    प्रारूप_लिख ("Bits Per Primary: %d\n", info->ad.digital.द्वयङ्काः_प्रत्येकम्_primary);
	अन्यथा
	    प्रारूप_लिख ("Bits Per Primary: undefined\n");
	
	विकल्प (info->ad.digital.interface)
	{
	पक्ष DVI: interface = "DVI"; भङ्ग;
	पक्ष HDMI_A: interface = "HDMI-a"; भङ्ग;
	पक्ष HDMI_B: interface = "HDMI-b"; भङ्ग;
	पक्ष MDDI: interface = "MDDI"; भङ्ग;
	पक्ष DISPLAY_पत्तनम्: interface = "DisplayPort"; भङ्ग;
	पक्ष UNDEFINED: interface = "undefined"; भङ्ग;
	स्वभाव: interface = "unknown"; भङ्ग;
	}
	प्रारूप_लिख ("Interface: %s\n", interface);
	
	प्रारूप_लिख ("RGB 4:4:4: %s\n", yesno (info->ad.digital.rgb444));
	प्रारूप_लिख ("YCrCb 4:4:4: %s\n", yesno (info->ad.digital.ycrcb444));
	प्रारूप_लिख ("YCrCb 4:2:2: %s\n", yesno (info->ad.digital.ycrcb422));
    }
    अन्यथा
    {
       ध्रुव वर्ण *s;
	प्रारूप_लिख ("Video Signal Level: %f\n", info->ad.analog.video_signal_level);
	प्रारूप_लिख ("Sync Signal Level: %f\n", info->ad.analog.sync_signal_level);
	प्रारूप_लिख ("Total Signal Level: %f\n", info->ad.analog.योग_signal_level);
	
	प्रारूप_लिख ("Blank to Black: %s\n",
		yesno (info->ad.analog.blank_गन्तव्यम्_black));
	प्रारूप_लिख ("Separate HV Sync: %s\n",
		yesno (info->ad.analog.separate_hv_sync));
	प्रारूप_लिख ("Composite Sync on H: %s\n",
		yesno (info->ad.analog.संयुक्त_sync_on_h));
	प्रारूप_लिख ("Serration on VSync: %s\n",
		yesno (info->ad.analog.serration_on_vsync));
	
	विकल्प (info->ad.analog.color_type)
	{
	पक्ष UNDEFINED_COLOR: s = "undefined"; भङ्ग;
	पक्ष MONOCHROME: s = "monochrome"; भङ्ग;
	पक्ष RGB: s = "rgb"; भङ्ग;
	पक्ष OTHER_COLOR: s = "other color"; भङ्ग;
	स्वभाव: s = "unknown"; भङ्ग;
	}
	
	प्रारूप_लिख ("Color: %s\n", s);
    }
    
    यदि (info->विस्तारः_mm == -1)
	प्रारूप_लिख ("Width: undefined\n");
    अन्यथा
	प्रारूप_लिख ("Width: %d mm\n", info->विस्तारः_mm);
    
    यदि (info->height_mm == -1)
	प्रारूप_लिख ("Height: undefined\n");
    अन्यथा
	प्रारूप_लिख ("Height: %d mm\n", info->height_mm);
    
    यदि (info->aspect_अनुपातः > 0)
	प्रारूप_लिख ("Aspect Ratio: %f\n", info->aspect_अनुपातः);
    अन्यथा
	प्रारूप_लिख ("Aspect Ratio: undefined\n");
    
    यदि (info->gamma >= 0)
	प्रारूप_लिख ("Gamma: %f\n", info->gamma);
    अन्यथा
	प्रारूप_लिख ("Gamma: undefined\n");
    
    प्रारूप_लिख ("Standby: %s\n", yesno (info->standby));
    प्रारूप_लिख ("Suspend: %s\n", yesno (info->suspend));
    प्रारूप_लिख ("Active Off: %s\n", yesno (info->सक्रिय_off));
    
    प्रारूप_लिख ("SRGB is Standard: %s\n", yesno (info->srgb_is_standard));
    प्रारूप_लिख ("Preferred Timing Includes Native: %s\n",
	    yesno (info->preferred_timing_includes_native));
    प्रारूप_लिख ("Continuous Frequency: %s\n", yesno (info->continuous_frequency));
    
    प्रारूप_लिख ("Red X: %f\n", info->red_x);
    प्रारूप_लिख ("Red Y: %f\n", info->red_y);
    प्रारूप_लिख ("Green X: %f\n", info->green_x);
    प्रारूप_लिख ("Green Y: %f\n", info->green_y);
    प्रारूप_लिख ("Blue X: %f\n", info->blue_x);
    प्रारूप_लिख ("Blue Y: %f\n", info->blue_y);
    प्रारूप_लिख ("White X: %f\n", info->white_x);
    प्रारूप_लिख ("White Y: %f\n", info->white_y);
    प्रारूप_लिख ("Min luminance: %f\n", info->min_luminance);
    प्रारूप_लिख ("Max luminance: %f\n", info->max_luminance);
    प्रारूप_लिख ("Max frame average luminance %f\n", info->max_frame_मध्यमानम्_luminance);
    
    प्रारूप_लिख ("Established Timings:\n");
    
    प्रति (i = 0; i < 24; ++i)
    {
	Timing *timing = &(info->established[i]);
	
	यदि (timing->frequency == 0)
	    भङ्ग;
	
	प्रारूप_लिख ("  %d x %d @ %d Hz\n",
		timing->विस्तारः, timing->height, timing->frequency);
	
    }
    
    प्रारूप_लिख ("Standard Timings:\n");
    प्रति (i = 0; i < 8; ++i)
    {
	Timing *timing = &(info->standard[i]);
	
	यदि (timing->frequency == 0)
	    भङ्ग;
	
	प्रारूप_लिख ("  %d x %d @ %d Hz\n",
		timing->विस्तारः, timing->height, timing->frequency);
    }
    
    प्रति (i = 0; i < info->n_detailed_timings; ++i)
    {
	DetailedTiming *timing = &(info->detailed_timings[i]);
	ध्रुव वर्ण *s;
	
	प्रारूप_लिख ("Timing%s: \n",
		(i == 0 && info->preferred_timing_includes_native)?
		" (Preferred)" : "");
	प्रारूप_लिख ("  Pixel Clock: %d\n", timing->pixel_clock);
	प्रारूप_लिख ("  H Addressable: %d\n", timing->h_addr);
	प्रारूप_लिख ("  H Blank: %d\n", timing->h_blank);
	प्रारूप_लिख ("  H Front Porch: %d\n", timing->h_front_porch);
	प्रारूप_लिख ("  H Sync: %d\n", timing->h_sync);
	प्रारूप_लिख ("  V Addressable: %d\n", timing->v_addr);
	प्रारूप_लिख ("  V Blank: %d\n", timing->v_blank);
	प्रारूप_लिख ("  V Front Porch: %d\n", timing->v_front_porch);
	प्रारूप_लिख ("  V Sync: %d\n", timing->v_sync);
	प्रारूप_लिख ("  Width: %d mm\n", timing->विस्तारः_mm);
	प्रारूप_लिख ("  Height: %d mm\n", timing->height_mm);
	प्रारूप_लिख ("  Right Border: %d\n", timing->दक्षिणः_border);
	प्रारूप_लिख ("  Top Border: %d\n", timing->शिखरम्_border);
	विकल्प (timing->stereo)
	{
	स्वभाव:
	पक्ष NO_STEREO:   s = "No Stereo"; भङ्ग;
	पक्ष क्षेत्रम्_दक्षिणः: s = "Field Sequential, Right on Sync"; भङ्ग;
	पक्ष क्षेत्रम्_वामः:  s = "Field Sequential, Left on Sync"; भङ्ग;
	पक्ष TWO_WAY_दक्षिणः_ON_EVEN: s = "Two-way, Right on Even"; भङ्ग;
	पक्ष TWO_WAY_वामः_ON_EVEN:  s = "Two-way, Left on Even"; भङ्ग;
	पक्ष FOUR_WAY_INTERLEAVED:  s = "Four-way Interleaved"; भङ्ग;
	पक्ष SIDE_BY_SIDE:          s = "Side-by-Side"; भङ्ग;
	}
	प्रारूप_लिख ("  Stereo: %s\n", s);
	
	यदि (timing->digital_sync)
	{
	    प्रारूप_लिख ("  Digital Sync:\n");
	    प्रारूप_लिख ("    composite: %s\n", yesno (timing->ad.digital.संयुक्त));
	    प्रारूप_लिख ("    serrations: %s\n", yesno (timing->ad.digital.serrations));
	    प्रारूप_लिख ("    negative vsync: %s\n",
		    yesno (timing->ad.digital.negative_vsync));
	    प्रारूप_लिख ("    negative hsync: %s\n",
		    yesno (timing->ad.digital.negative_hsync));
	}
	अन्यथा
	{
	    प्रारूप_लिख ("  Analog Sync:\n");
	    प्रारूप_लिख ("    bipolar: %s\n", yesno (timing->ad.analog.bipolar));
	    प्रारूप_लिख ("    serrations: %s\n", yesno (timing->ad.analog.serrations));
	    प्रारूप_लिख ("    sync on green: %s\n", yesno (
			timing->ad.analog.sync_on_green));
	}
    }
    
    प्रारूप_लिख ("Detailed Product information:\n");
    प्रारूप_लिख ("  Product Name: %s\n", info->dsc_गुणनफलम्_name);
    प्रारूप_लिख ("  Serial Number: %s\n", info->dsc_serial_सङ्ख्या);
    प्रारूप_लिख ("  Unspecified String: %s\n", info->dsc_string);
}

