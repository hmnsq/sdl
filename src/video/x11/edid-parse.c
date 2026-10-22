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

#تعریف_کړه TRUE 1
#تعریف_کړه FALSE 0

ساكن صحيح
get_بټ (صحيح دننه_2, صحيح بټ)
{
    أرجع (دننه_2 & (1 << بټ)) >> بټ;
}

ساكن صحيح
get_بټونه (صحيح دننه_2, صحيح begin, صحيح پای_ټکی)
{
    صحيح ماسک = (1 << (پای_ټکی - begin + 1)) - 1;
    
    أرجع (دننه_2 >> begin) & ماسک;
}

ساكن صحيح
decode_سرلیک (ثابت uchar *edid)
{
    إذا (SDL_memcmp (edid, "\x00\xff\xff\xff\xff\xff\xff\x00", 8) == 0)
	أرجع TRUE;
    أرجع FALSE;
}

ساكن صحيح
decode_vendor_and_حاصل_ضرب_identification (ثابت uchar *edid, MonitorInfo *info)
{
    صحيح is_model_year;
    
    /* Manufacturer Code */
    info->manufacturer_کوډ[0]  = get_بټونه (edid[0x08], 2, 6);
    info->manufacturer_کوډ[1]  = get_بټونه (edid[0x08], 0, 1) << 3;
    info->manufacturer_کوډ[1] |= get_بټونه (edid[0x09], 5, 7);
    info->manufacturer_کوډ[2]  = get_بټونه (edid[0x09], 0, 4);
    info->manufacturer_کوډ[3]  = '\0';
    
    info->manufacturer_کوډ[0] += 'A' - 1;
    info->manufacturer_کوډ[1] += 'A' - 1;
    info->manufacturer_کوډ[2] += 'A' - 1;

    /* Product Code */
    info->حاصل_ضرب_کوډ = edid[0x0b] << 8 | edid[0x0a];

    /* Serial Number */
    info->serial_شمېره =
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
decode_edid_نسخه (ثابت uchar *edid, MonitorInfo *info)
{
    info->major_نسخه = edid[0x12];
    info->minor_نسخه = edid[0x13];

    أرجع TRUE;
}

ساكن صحيح
decode_display_parameters (ثابت uchar *edid, MonitorInfo *info)
{
    /* Digital vs Analog */
    info->is_digital = get_بټ (edid[0x14], 7);

    إذا (info->is_digital)
    {
	صحيح بټونه;
	
	ساكن ثابت صحيح بټ_ژوروالی_2[8] =
	{
	    -1, 6, 8, 10, 12, 14, 16, -1
	};

	ساكن ثابت Interface interfaces[6] =
	{
	    UNDEFINED, DVI, HDMI_A, HDMI_B, MDDI, DISPLAY_پورټ
	};

	بټونه = get_بټونه (edid[0x14], 4, 6);
	info->ad.digital.بټونه_فی_primary = بټ_ژوروالی_2[بټونه];

	بټونه = get_بټونه (edid[0x14], 0, 3);
	
	إذا (بټونه <= 5)
	    info->ad.digital.interface = interfaces[بټونه];
	وإلا
	    info->ad.digital.interface = UNDEFINED;
    }
    وإلا
    {
	صحيح بټونه = get_بټونه (edid[0x14], 5, 6);
	
	ساكن ثابت مزدوج پوړونه[][3] =
	{
	    { 0.7,   0.3,    1.0 },
	    { 0.714, 0.286,  1.0 },
	    { 1.0,   0.4,    1.4 },
	    { 0.7,   0.0,    0.7 },
	};

	info->ad.analog.video_signal_level = پوړونه[بټونه][0];
	info->ad.analog.sync_signal_level = پوړونه[بټونه][1];
	info->ad.analog.ټول_signal_level = پوړونه[بټونه][2];

	info->ad.analog.blank_منزل_black = get_بټ (edid[0x14], 4);

	info->ad.analog.separate_hv_sync = get_بټ (edid[0x14], 3);
	info->ad.analog.مرکب_sync_on_h = get_بټ (edid[0x14], 2);
	info->ad.analog.مرکب_sync_on_green = get_بټ (edid[0x14], 1);

	info->ad.analog.serration_on_vsync = get_بټ (edid[0x14], 0);
    }

    /* Screen Size / Aspect Ratio */
    إذا (edid[0x15] == 0 && edid[0x16] == 0)
    {
	info->پلنوالی_mm = -1;
	info->لوړوالی_mm = -1;
	info->aspect_نسبت = -1.0;
    }
    وإلا إذا (edid[0x16] == 0)
    {
	info->پلنوالی_mm = -1;
	info->لوړوالی_mm = -1; 
	info->aspect_نسبت = 100.0 / (edid[0x15] + 99);
    }
    وإلا إذا (edid[0x15] == 0)
    {
	info->پلنوالی_mm = -1;
	info->لوړوالی_mm = -1;
	info->aspect_نسبت = 100.0 / (edid[0x16] + 99);
	info->aspect_نسبت = 1/info->aspect_نسبت; /* portrait */
    }
    وإلا
    {
	info->پلنوالی_mm = 10 * edid[0x15];
	info->لوړوالی_mm = 10 * edid[0x16];
    }

    /* Gamma */
    إذا (edid[0x17] == 0xFF)
	info->gamma = -1.0;
    وإلا
	info->gamma = (edid[0x17] + 100.0) / 100.0;

    /* Features */
    info->standby = get_بټ (edid[0x18], 7);
    info->suspend = get_بټ (edid[0x18], 6);
    info->فعال_off = get_بټ (edid[0x18], 5);

    إذا (info->is_digital)
    {
	info->ad.digital.rgb444 = TRUE;
	إذا (get_بټ (edid[0x18], 3))
	    info->ad.digital.ycrcb444 = 1;
	إذا (get_بټ (edid[0x18], 4))
	    info->ad.digital.ycrcb422 = 1;
    }
    وإلا
    {
	صحيح بټونه = get_بټونه (edid[0x18], 3, 4);
	ColorType color_type[4] =
	{
	    MONOCHROME, RGB, OTHER_COLOR, UNDEFINED_COLOR
	};

	info->ad.analog.color_type = color_type[بټونه];
    }

    info->srgb_is_standard = get_بټ (edid[0x18], 2);

    /* In 1.3 this is called "has preferred timing" */
    info->preferred_timing_includes_native = get_بټ (edid[0x18], 1);

    /* FIXME: In 1.3 this indicates whether the monitor accepts GTF */
    info->continuous_frequency = get_بټ (edid[0x18], 0);
    أرجع TRUE;
}

ساكن مزدوج
decode_fraction (صحيح لوړ, صحيح ټیټ)
{
    مزدوج پایله = 0.0;
    صحيح i;

    لوړ = (لوړ << 2) | ټیټ;

    لكل (i = 0; i < 10; ++i)
	پایله += get_بټ (لوړ, i) * SDL_pow (2, i - 10);

    أرجع پایله;
}

ساكن صحيح
decode_color_characteristics (ثابت uchar *edid, MonitorInfo *info)
{
    info->red_x = decode_fraction (edid[0x1b], get_بټونه (edid[0x19], 6, 7));
    info->red_y = decode_fraction (edid[0x1c], get_بټونه (edid[0x19], 5, 4));
    info->green_x = decode_fraction (edid[0x1d], get_بټونه (edid[0x19], 2, 3));
    info->green_y = decode_fraction (edid[0x1e], get_بټونه (edid[0x19], 0, 1));
    info->blue_x = decode_fraction (edid[0x1f], get_بټونه (edid[0x1a], 6, 7));
    info->blue_y = decode_fraction (edid[0x20], get_بټونه (edid[0x1a], 4, 5));
    info->white_x = decode_fraction (edid[0x21], get_بټونه (edid[0x1a], 2, 3));
    info->white_y = decode_fraction (edid[0x22], get_بټونه (edid[0x1a], 0, 1));

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

	    إذا (get_بټ (byte, j) && established[i][j].frequency != 0)
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
	صحيح لومړی = edid[0x26 + 2 * i];
	صحيح دوهم = edid[0x27 + 2 * i];

	إذا (لومړی != 0x01 && دوهم != 0x01)
	{
	    صحيح w = 8 * (لومړی + 31);
	    صحيح h = 0;

	    بدل (get_بټونه (دوهم, 6, 7))
	    {
	    حالة 0x00: h = (w / 16) * 10; اكسر;
	    حالة 0x01: h = (w / 4) * 3; اكسر;
	    حالة 0x02: h = (w / 5) * 4; اكسر;
	    حالة 0x03: h = (w / 16) * 9; اكسر;
	    }

	    info->standard[i].پلنوالی = w;
	    info->standard[i].لوړوالی = h;
	    info->standard[i].frequency = get_بټونه (دوهم, 0, 5) + 60;
	}
    }
    
    أرجع TRUE;
}

ساكن فراغ
decode_lf_string (ثابت uchar *s, صحيح n_chars, حرف *پایله)
{
    صحيح i;
    لكل (i = 0; i < n_chars; ++i)
    {
	إذا (s[i] == 0x0a)
	{
	    *پایله++ = '\0';
	    اكسر;
	}
	وإلا إذا (s[i] == 0x00)
	{
	    /* Convert embedded 0's to spaces */
	    *پایله++ = ' ';
	}
	وإلا
	{
	    *پایله++ = s[i];
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
	decode_lf_string (desc + 5, 13, info->dsc_حاصل_ضرب_name);
	اكسر;
    حالة 0xFF:
	decode_lf_string (desc + 5, 13, info->dsc_serial_شمېره);
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
    صحيح بټونه;
    StereoType stereo[] =
    {
	NO_STEREO, NO_STEREO, ډګر_ښی, ډګر_کیڼ,
	TWO_WAY_ښی_ON_EVEN, TWO_WAY_کیڼ_ON_EVEN,
	FOUR_WAY_INTERLEAVED, SIDE_BY_SIDE
    };
    
    detailed->pixel_clock = (timing[0x00] | timing[0x01] << 8) * 10000;
    detailed->h_addr = timing[0x02] | ((timing[0x04] & 0xf0) << 4);
    detailed->h_blank = timing[0x03] | ((timing[0x04] & 0x0f) << 8);
    detailed->v_addr = timing[0x05] | ((timing[0x07] & 0xf0) << 4);
    detailed->v_blank = timing[0x06] | ((timing[0x07] & 0x0f) << 8);
    detailed->h_front_porch = timing[0x08] | get_بټونه (timing[0x0b], 6, 7) << 8;
    detailed->h_sync = timing[0x09] | get_بټونه (timing[0x0b], 4, 5) << 8;
    detailed->v_front_porch =
	get_بټونه (timing[0x0a], 4, 7) | get_بټونه (timing[0x0b], 2, 3) << 4;
    detailed->v_sync =
	get_بټونه (timing[0x0a], 0, 3) | get_بټونه (timing[0x0b], 0, 1) << 4;
    detailed->پلنوالی_mm =  timing[0x0c] | get_بټونه (timing[0x0e], 4, 7) << 8;
    detailed->لوړوالی_mm = timing[0x0d] | get_بټونه (timing[0x0e], 0, 3) << 8;
    detailed->ښی_border = timing[0x0f];
    detailed->سر_border = timing[0x10];

    detailed->interlaced = get_بټ (timing[0x11], 7);

    /* Stereo */
    بټونه = get_بټونه (timing[0x11], 5, 6) << 1 | get_بټ (timing[0x11], 0);
    detailed->stereo = stereo[بټونه];

    /* Sync */
    بټونه = timing[0x11];

    detailed->digital_sync = get_بټ (بټونه, 4);
    إذا (detailed->digital_sync)
    {
	detailed->ad.digital.مرکب = !get_بټ (بټونه, 3);

	إذا (detailed->ad.digital.مرکب)
	{
	    detailed->ad.digital.serrations = get_بټ (بټونه, 2);
	    detailed->ad.digital.negative_vsync = FALSE;
	}
	وإلا
	{
	    detailed->ad.digital.serrations = FALSE;
	    detailed->ad.digital.negative_vsync = !get_بټ (بټونه, 2);
	}

	detailed->ad.digital.negative_hsync = !get_بټ (بټونه, 0);
    }
    وإلا
    {
	detailed->ad.analog.bipolar = get_بټ (بټونه, 3);
	detailed->ad.analog.serrations = get_بټ (بټونه, 2);
	detailed->ad.analog.sync_on_green = !get_بټ (بټونه, 1);
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
	صحيح شاخص = 0x36 + i * 18;

	إذا (edid[شاخص + 0] == 0x00 && edid[شاخص + 1] == 0x00)
	{
	    decode_display_descriptor (edid + شاخص, info);
	}
	وإلا
	{
	    decode_detailed_timing (
		edid + شاخص, &(info->detailed_timings[timing_idx++]));
	}
    }

    info->n_detailed_timings = timing_idx;

    أرجع TRUE;
}

ساكن فراغ
decode_check_مجموعه (ثابت uchar *edid,
		  MonitorInfo *info)
{
    صحيح i;
    uchar check = 0;

    لكل (i = 0; i < 128; ++i)
	check += edid[i];

    info->checksum = check;
}

ساكن فراغ
decode_HDR_metadata_بلاک (ثابت uchar *معلومات, صحيح اوږدتیا, MonitorInfo *info)
{
    إذا (اوږدتیا >= 3)
	info->max_luminance = 50.0 * SDL_pow(2, معلومات[2] / 32.0);

    إذا (اوږدتیا >= 4)
	info->max_چوکاټ_اوسط_luminance = 50.0 * SDL_pow(2, معلومات[3] / 32.0);

    إذا (اوږدتیا >= 5)
	info->min_luminance = 50.0 * SDL_pow(2, معلومات[4] / 32.0);
}


ساكن فراغ
decode_cta_بلاک (ثابت uchar *edid,
		  MonitorInfo *info)
{
    صحيح دننه_واټن_2 = 4;
    طالما (دننه_واټن_2 < 128) {
	صحيح اوږدتیا = edid[دننه_واټن_2] & 0x1f;
	صحيح type = edid[دننه_واټن_2] >> 5;
	إذا (اوږدتیا == 0) {
	    اكسر;
	}
	إذا (type == 7) {
	    type <<= 8;
	    type |= edid[دننه_واټن_2 + 1];
	}
	إذا (type == 0x706) {
	    decode_HDR_metadata_بلاک (&edid[دننه_واټن_2 + 2], اوږدتیا - 1, info);
	}
	دننه_واټن_2 += (1 + اوږدتیا);
    }
}

MonitorInfo *
decode_edid (ثابت uchar *edid, size_t اندازه)
{
    ثابت صحيح EDID_پاڼه_اندازه = 128;
    صحيح عدد_بلاکونه = (اندازه / EDID_پاڼه_اندازه);
    MonitorInfo *info;

    إذا ((اندازه % EDID_پاڼه_اندازه) != 0) {
	أرجع عدم;
    }

    info = SDL_calloc (1, حجم (MonitorInfo));

    decode_check_مجموعه (edid, info);
    
    إذا (!decode_سرلیک (edid) ||
        !decode_vendor_and_حاصل_ضرب_identification (edid, info) ||
        !decode_edid_نسخه (edid, info) ||
        !decode_display_parameters (edid, info) ||
        !decode_color_characteristics (edid, info) ||
        !decode_established_timings (edid, info) ||
        !decode_standard_timings (edid, info) ||
        !decode_descriptors (edid, info)) {
	SDL_free(info);
	أرجع عدم;
    }
    
    إذا (عدد_بلاکونه > 1) {
	لكل (صحيح i = 1; i < عدد_بلاکونه; ++i) {
	    صحيح دننه_واټن_2 = i * EDID_پاڼه_اندازه;
	    uchar extension = edid[دننه_واټن_2];
	    إذا (extension == 0x02) {
		// CTA-861 Extension Block
		decode_cta_بلاک (&edid[دننه_واټن_2], info);
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
    
    چاپ_کړه ("Checksum: %d (%s)\n",
	    info->checksum, info->checksum? "incorrect" : "correct");
    چاپ_کړه ("Manufacturer Code: %s\n", info->manufacturer_کوډ);
    چاپ_کړه ("Product Code: 0x%x\n", info->حاصل_ضرب_کوډ);
    چاپ_کړه ("Serial Number: %u\n", info->serial_شمېره);
    
    إذا (info->production_week != -1)
	چاپ_کړه ("Production Week: %d\n", info->production_week);
    وإلا
	چاپ_کړه ("Production Week: unspecified\n");
    
    إذا (info->production_year != -1)
	چاپ_کړه ("Production Year: %d\n", info->production_year);
    وإلا
	چاپ_کړه ("Production Year: unspecified\n");
    
    إذا (info->model_year != -1)
	چاپ_کړه ("Model Year: %d\n", info->model_year);
    وإلا
	چاپ_کړه ("Model Year: unspecified\n");
    
    چاپ_کړه ("EDID revision: %d.%d\n", info->major_نسخه, info->minor_نسخه);
    
    چاپ_کړه ("Display is %s\n", info->is_digital? "digital" : "analog");
    إذا (info->is_digital)
    {
	ثابت حرف *interface;
	إذا (info->ad.digital.بټونه_فی_primary != -1)
	    چاپ_کړه ("Bits Per Primary: %d\n", info->ad.digital.بټونه_فی_primary);
	وإلا
	    چاپ_کړه ("Bits Per Primary: undefined\n");
	
	بدل (info->ad.digital.interface)
	{
	حالة DVI: interface = "DVI"; اكسر;
	حالة HDMI_A: interface = "HDMI-a"; اكسر;
	حالة HDMI_B: interface = "HDMI-b"; اكسر;
	حالة MDDI: interface = "MDDI"; اكسر;
	حالة DISPLAY_پورټ: interface = "DisplayPort"; اكسر;
	حالة UNDEFINED: interface = "undefined"; اكسر;
	افتراضي: interface = "unknown"; اكسر;
	}
	چاپ_کړه ("Interface: %s\n", interface);
	
	چاپ_کړه ("RGB 4:4:4: %s\n", yesno (info->ad.digital.rgb444));
	چاپ_کړه ("YCrCb 4:4:4: %s\n", yesno (info->ad.digital.ycrcb444));
	چاپ_کړه ("YCrCb 4:2:2: %s\n", yesno (info->ad.digital.ycrcb422));
    }
    وإلا
    {
       ثابت حرف *s;
	چاپ_کړه ("Video Signal Level: %f\n", info->ad.analog.video_signal_level);
	چاپ_کړه ("Sync Signal Level: %f\n", info->ad.analog.sync_signal_level);
	چاپ_کړه ("Total Signal Level: %f\n", info->ad.analog.ټول_signal_level);
	
	چاپ_کړه ("Blank to Black: %s\n",
		yesno (info->ad.analog.blank_منزل_black));
	چاپ_کړه ("Separate HV Sync: %s\n",
		yesno (info->ad.analog.separate_hv_sync));
	چاپ_کړه ("Composite Sync on H: %s\n",
		yesno (info->ad.analog.مرکب_sync_on_h));
	چاپ_کړه ("Serration on VSync: %s\n",
		yesno (info->ad.analog.serration_on_vsync));
	
	بدل (info->ad.analog.color_type)
	{
	حالة UNDEFINED_COLOR: s = "undefined"; اكسر;
	حالة MONOCHROME: s = "monochrome"; اكسر;
	حالة RGB: s = "rgb"; اكسر;
	حالة OTHER_COLOR: s = "other color"; اكسر;
	افتراضي: s = "unknown"; اكسر;
	}
	
	چاپ_کړه ("Color: %s\n", s);
    }
    
    إذا (info->پلنوالی_mm == -1)
	چاپ_کړه ("Width: undefined\n");
    وإلا
	چاپ_کړه ("Width: %d mm\n", info->پلنوالی_mm);
    
    إذا (info->لوړوالی_mm == -1)
	چاپ_کړه ("Height: undefined\n");
    وإلا
	چاپ_کړه ("Height: %d mm\n", info->لوړوالی_mm);
    
    إذا (info->aspect_نسبت > 0)
	چاپ_کړه ("Aspect Ratio: %f\n", info->aspect_نسبت);
    وإلا
	چاپ_کړه ("Aspect Ratio: undefined\n");
    
    إذا (info->gamma >= 0)
	چاپ_کړه ("Gamma: %f\n", info->gamma);
    وإلا
	چاپ_کړه ("Gamma: undefined\n");
    
    چاپ_کړه ("Standby: %s\n", yesno (info->standby));
    چاپ_کړه ("Suspend: %s\n", yesno (info->suspend));
    چاپ_کړه ("Active Off: %s\n", yesno (info->فعال_off));
    
    چاپ_کړه ("SRGB is Standard: %s\n", yesno (info->srgb_is_standard));
    چاپ_کړه ("Preferred Timing Includes Native: %s\n",
	    yesno (info->preferred_timing_includes_native));
    چاپ_کړه ("Continuous Frequency: %s\n", yesno (info->continuous_frequency));
    
    چاپ_کړه ("Red X: %f\n", info->red_x);
    چاپ_کړه ("Red Y: %f\n", info->red_y);
    چاپ_کړه ("Green X: %f\n", info->green_x);
    چاپ_کړه ("Green Y: %f\n", info->green_y);
    چاپ_کړه ("Blue X: %f\n", info->blue_x);
    چاپ_کړه ("Blue Y: %f\n", info->blue_y);
    چاپ_کړه ("White X: %f\n", info->white_x);
    چاپ_کړه ("White Y: %f\n", info->white_y);
    چاپ_کړه ("Min luminance: %f\n", info->min_luminance);
    چاپ_کړه ("Max luminance: %f\n", info->max_luminance);
    چاپ_کړه ("Max frame average luminance %f\n", info->max_چوکاټ_اوسط_luminance);
    
    چاپ_کړه ("Established Timings:\n");
    
    لكل (i = 0; i < 24; ++i)
    {
	Timing *timing = &(info->established[i]);
	
	إذا (timing->frequency == 0)
	    اكسر;
	
	چاپ_کړه ("  %d x %d @ %d Hz\n",
		timing->پلنوالی, timing->لوړوالی, timing->frequency);
	
    }
    
    چاپ_کړه ("Standard Timings:\n");
    لكل (i = 0; i < 8; ++i)
    {
	Timing *timing = &(info->standard[i]);
	
	إذا (timing->frequency == 0)
	    اكسر;
	
	چاپ_کړه ("  %d x %d @ %d Hz\n",
		timing->پلنوالی, timing->لوړوالی, timing->frequency);
    }
    
    لكل (i = 0; i < info->n_detailed_timings; ++i)
    {
	DetailedTiming *timing = &(info->detailed_timings[i]);
	ثابت حرف *s;
	
	چاپ_کړه ("Timing%s: \n",
		(i == 0 && info->preferred_timing_includes_native)?
		" (Preferred)" : "");
	چاپ_کړه ("  Pixel Clock: %d\n", timing->pixel_clock);
	چاپ_کړه ("  H Addressable: %d\n", timing->h_addr);
	چاپ_کړه ("  H Blank: %d\n", timing->h_blank);
	چاپ_کړه ("  H Front Porch: %d\n", timing->h_front_porch);
	چاپ_کړه ("  H Sync: %d\n", timing->h_sync);
	چاپ_کړه ("  V Addressable: %d\n", timing->v_addr);
	چاپ_کړه ("  V Blank: %d\n", timing->v_blank);
	چاپ_کړه ("  V Front Porch: %d\n", timing->v_front_porch);
	چاپ_کړه ("  V Sync: %d\n", timing->v_sync);
	چاپ_کړه ("  Width: %d mm\n", timing->پلنوالی_mm);
	چاپ_کړه ("  Height: %d mm\n", timing->لوړوالی_mm);
	چاپ_کړه ("  Right Border: %d\n", timing->ښی_border);
	چاپ_کړه ("  Top Border: %d\n", timing->سر_border);
	بدل (timing->stereo)
	{
	افتراضي:
	حالة NO_STEREO:   s = "No Stereo"; اكسر;
	حالة ډګر_ښی: s = "Field Sequential, Right on Sync"; اكسر;
	حالة ډګر_کیڼ:  s = "Field Sequential, Left on Sync"; اكسر;
	حالة TWO_WAY_ښی_ON_EVEN: s = "Two-way, Right on Even"; اكسر;
	حالة TWO_WAY_کیڼ_ON_EVEN:  s = "Two-way, Left on Even"; اكسر;
	حالة FOUR_WAY_INTERLEAVED:  s = "Four-way Interleaved"; اكسر;
	حالة SIDE_BY_SIDE:          s = "Side-by-Side"; اكسر;
	}
	چاپ_کړه ("  Stereo: %s\n", s);
	
	إذا (timing->digital_sync)
	{
	    چاپ_کړه ("  Digital Sync:\n");
	    چاپ_کړه ("    composite: %s\n", yesno (timing->ad.digital.مرکب));
	    چاپ_کړه ("    serrations: %s\n", yesno (timing->ad.digital.serrations));
	    چاپ_کړه ("    negative vsync: %s\n",
		    yesno (timing->ad.digital.negative_vsync));
	    چاپ_کړه ("    negative hsync: %s\n",
		    yesno (timing->ad.digital.negative_hsync));
	}
	وإلا
	{
	    چاپ_کړه ("  Analog Sync:\n");
	    چاپ_کړه ("    bipolar: %s\n", yesno (timing->ad.analog.bipolar));
	    چاپ_کړه ("    serrations: %s\n", yesno (timing->ad.analog.serrations));
	    چاپ_کړه ("    sync on green: %s\n", yesno (
			timing->ad.analog.sync_on_green));
	}
    }
    
    چاپ_کړه ("Detailed Product information:\n");
    چاپ_کړه ("  Product Name: %s\n", info->dsc_حاصل_ضرب_name);
    چاپ_کړه ("  Serial Number: %s\n", info->dsc_serial_شمېره);
    چاپ_کړه ("  Unspecified String: %s\n", info->dsc_string);
}

