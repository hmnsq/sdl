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

#وصف_ڪريو TRUE 1
#وصف_ڪريو FALSE 0

ساكن صحيح
get_ٻٽو_انگ (صحيح اندريون_2, صحيح ٻٽو_انگ)
{
    أرجع (اندريون_2 & (1 << ٻٽو_انگ)) >> ٻٽو_انگ;
}

ساكن صحيح
get_بٽ (صحيح اندريون_2, صحيح begin, صحيح پڇاڙي)
{
    صحيح نقاب = (1 << (پڇاڙي - begin + 1)) - 1;
    
    أرجع (اندريون_2 >> begin) & نقاب;
}

ساكن صحيح
decode_سرو (ثابت uchar *edid)
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
    info->manufacturer_ڪوڊ[0]  = get_بٽ (edid[0x08], 2, 6);
    info->manufacturer_ڪوڊ[1]  = get_بٽ (edid[0x08], 0, 1) << 3;
    info->manufacturer_ڪوڊ[1] |= get_بٽ (edid[0x09], 5, 7);
    info->manufacturer_ڪوڊ[2]  = get_بٽ (edid[0x09], 0, 4);
    info->manufacturer_ڪوڊ[3]  = '\0';
    
    info->manufacturer_ڪوڊ[0] += 'A' - 1;
    info->manufacturer_ڪوڊ[1] += 'A' - 1;
    info->manufacturer_ڪوڊ[2] += 'A' - 1;

    /* Product Code */
    info->حاصل_ضرب_ڪوڊ = edid[0x0b] << 8 | edid[0x0a];

    /* Serial Number */
    info->serial_عدد =
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
decode_edid_نسخو (ثابت uchar *edid, MonitorInfo *info)
{
    info->major_نسخو = edid[0x12];
    info->minor_نسخو = edid[0x13];

    أرجع TRUE;
}

ساكن صحيح
decode_display_parameters (ثابت uchar *edid, MonitorInfo *info)
{
    /* Digital vs Analog */
    info->is_digital = get_ٻٽو_انگ (edid[0x14], 7);

    إذا (info->is_digital)
    {
	صحيح بٽ;
	
	ساكن ثابت صحيح ٻٽو_انگ_اونهائي_2[8] =
	{
	    -1, 6, 8, 10, 12, 14, 16, -1
	};

	ساكن ثابت Interface interfaces[6] =
	{
	    UNDEFINED, DVI, HDMI_A, HDMI_B, MDDI, DISPLAY_پورٽ
	};

	بٽ = get_بٽ (edid[0x14], 4, 6);
	info->ad.digital.بٽ_في_primary = ٻٽو_انگ_اونهائي_2[بٽ];

	بٽ = get_بٽ (edid[0x14], 0, 3);
	
	إذا (بٽ <= 5)
	    info->ad.digital.interface = interfaces[بٽ];
	وإلا
	    info->ad.digital.interface = UNDEFINED;
    }
    وإلا
    {
	صحيح بٽ = get_بٽ (edid[0x14], 5, 6);
	
	ساكن ثابت مزدوج سطحون[][3] =
	{
	    { 0.7,   0.3,    1.0 },
	    { 0.714, 0.286,  1.0 },
	    { 1.0,   0.4,    1.4 },
	    { 0.7,   0.0,    0.7 },
	};

	info->ad.analog.video_signal_level = سطحون[بٽ][0];
	info->ad.analog.sync_signal_level = سطحون[بٽ][1];
	info->ad.analog.ڪل_signal_level = سطحون[بٽ][2];

	info->ad.analog.blank_منزل_black = get_ٻٽو_انگ (edid[0x14], 4);

	info->ad.analog.separate_hv_sync = get_ٻٽو_انگ (edid[0x14], 3);
	info->ad.analog.مرکب_sync_on_h = get_ٻٽو_انگ (edid[0x14], 2);
	info->ad.analog.مرکب_sync_on_green = get_ٻٽو_انگ (edid[0x14], 1);

	info->ad.analog.serration_on_vsync = get_ٻٽو_انگ (edid[0x14], 0);
    }

    /* Screen Size / Aspect Ratio */
    إذا (edid[0x15] == 0 && edid[0x16] == 0)
    {
	info->ويڪر_mm = -1;
	info->اوچائي_mm = -1;
	info->aspect_تناسب = -1.0;
    }
    وإلا إذا (edid[0x16] == 0)
    {
	info->ويڪر_mm = -1;
	info->اوچائي_mm = -1; 
	info->aspect_تناسب = 100.0 / (edid[0x15] + 99);
    }
    وإلا إذا (edid[0x15] == 0)
    {
	info->ويڪر_mm = -1;
	info->اوچائي_mm = -1;
	info->aspect_تناسب = 100.0 / (edid[0x16] + 99);
	info->aspect_تناسب = 1/info->aspect_تناسب; /* portrait */
    }
    وإلا
    {
	info->ويڪر_mm = 10 * edid[0x15];
	info->اوچائي_mm = 10 * edid[0x16];
    }

    /* Gamma */
    إذا (edid[0x17] == 0xFF)
	info->gamma = -1.0;
    وإلا
	info->gamma = (edid[0x17] + 100.0) / 100.0;

    /* Features */
    info->standby = get_ٻٽو_انگ (edid[0x18], 7);
    info->suspend = get_ٻٽو_انگ (edid[0x18], 6);
    info->سرگرم_off = get_ٻٽو_انگ (edid[0x18], 5);

    إذا (info->is_digital)
    {
	info->ad.digital.rgb444 = TRUE;
	إذا (get_ٻٽو_انگ (edid[0x18], 3))
	    info->ad.digital.ycrcb444 = 1;
	إذا (get_ٻٽو_انگ (edid[0x18], 4))
	    info->ad.digital.ycrcb422 = 1;
    }
    وإلا
    {
	صحيح بٽ = get_بٽ (edid[0x18], 3, 4);
	ColorType color_type[4] =
	{
	    MONOCHROME, RGB, OTHER_COLOR, UNDEFINED_COLOR
	};

	info->ad.analog.color_type = color_type[بٽ];
    }

    info->srgb_is_standard = get_ٻٽو_انگ (edid[0x18], 2);

    /* In 1.3 this is called "has preferred timing" */
    info->preferred_timing_includes_native = get_ٻٽو_انگ (edid[0x18], 1);

    /* FIXME: In 1.3 this indicates whether the monitor accepts GTF */
    info->continuous_frequency = get_ٻٽو_انگ (edid[0x18], 0);
    أرجع TRUE;
}

ساكن مزدوج
decode_fraction (صحيح مٿاهون, صحيح هيٺيون)
{
    مزدوج نتيجو = 0.0;
    صحيح i;

    مٿاهون = (مٿاهون << 2) | هيٺيون;

    لكل (i = 0; i < 10; ++i)
	نتيجو += get_ٻٽو_انگ (مٿاهون, i) * SDL_pow (2, i - 10);

    أرجع نتيجو;
}

ساكن صحيح
decode_color_characteristics (ثابت uchar *edid, MonitorInfo *info)
{
    info->red_x = decode_fraction (edid[0x1b], get_بٽ (edid[0x19], 6, 7));
    info->red_y = decode_fraction (edid[0x1c], get_بٽ (edid[0x19], 5, 4));
    info->green_x = decode_fraction (edid[0x1d], get_بٽ (edid[0x19], 2, 3));
    info->green_y = decode_fraction (edid[0x1e], get_بٽ (edid[0x19], 0, 1));
    info->blue_x = decode_fraction (edid[0x1f], get_بٽ (edid[0x1a], 6, 7));
    info->blue_y = decode_fraction (edid[0x20], get_بٽ (edid[0x1a], 4, 5));
    info->white_x = decode_fraction (edid[0x21], get_بٽ (edid[0x1a], 2, 3));
    info->white_y = decode_fraction (edid[0x22], get_بٽ (edid[0x1a], 0, 1));

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

	    إذا (get_ٻٽو_انگ (byte, j) && established[i][j].frequency != 0)
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
	صحيح پهريون = edid[0x26 + 2 * i];
	صحيح ٻيو = edid[0x27 + 2 * i];

	إذا (پهريون != 0x01 && ٻيو != 0x01)
	{
	    صحيح w = 8 * (پهريون + 31);
	    صحيح h = 0;

	    بدل (get_بٽ (ٻيو, 6, 7))
	    {
	    حالة 0x00: h = (w / 16) * 10; اكسر;
	    حالة 0x01: h = (w / 4) * 3; اكسر;
	    حالة 0x02: h = (w / 5) * 4; اكسر;
	    حالة 0x03: h = (w / 16) * 9; اكسر;
	    }

	    info->standard[i].ويڪر = w;
	    info->standard[i].اوچائي = h;
	    info->standard[i].frequency = get_بٽ (ٻيو, 0, 5) + 60;
	}
    }
    
    أرجع TRUE;
}

ساكن فراغ
decode_lf_string (ثابت uchar *s, صحيح n_chars, حرف *نتيجو)
{
    صحيح i;
    لكل (i = 0; i < n_chars; ++i)
    {
	إذا (s[i] == 0x0a)
	{
	    *نتيجو++ = '\0';
	    اكسر;
	}
	وإلا إذا (s[i] == 0x00)
	{
	    /* Convert embedded 0's to spaces */
	    *نتيجو++ = ' ';
	}
	وإلا
	{
	    *نتيجو++ = s[i];
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
	decode_lf_string (desc + 5, 13, info->dsc_serial_عدد);
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
    صحيح بٽ;
    StereoType stereo[] =
    {
	NO_STEREO, NO_STEREO, ميدان_ساڄو, ميدان_کاٻو,
	TWO_WAY_ساڄو_ON_EVEN, TWO_WAY_کاٻو_ON_EVEN,
	FOUR_WAY_INTERLEAVED, SIDE_BY_SIDE
    };
    
    detailed->pixel_clock = (timing[0x00] | timing[0x01] << 8) * 10000;
    detailed->h_addr = timing[0x02] | ((timing[0x04] & 0xf0) << 4);
    detailed->h_blank = timing[0x03] | ((timing[0x04] & 0x0f) << 8);
    detailed->v_addr = timing[0x05] | ((timing[0x07] & 0xf0) << 4);
    detailed->v_blank = timing[0x06] | ((timing[0x07] & 0x0f) << 8);
    detailed->h_front_porch = timing[0x08] | get_بٽ (timing[0x0b], 6, 7) << 8;
    detailed->h_sync = timing[0x09] | get_بٽ (timing[0x0b], 4, 5) << 8;
    detailed->v_front_porch =
	get_بٽ (timing[0x0a], 4, 7) | get_بٽ (timing[0x0b], 2, 3) << 4;
    detailed->v_sync =
	get_بٽ (timing[0x0a], 0, 3) | get_بٽ (timing[0x0b], 0, 1) << 4;
    detailed->ويڪر_mm =  timing[0x0c] | get_بٽ (timing[0x0e], 4, 7) << 8;
    detailed->اوچائي_mm = timing[0x0d] | get_بٽ (timing[0x0e], 0, 3) << 8;
    detailed->ساڄو_border = timing[0x0f];
    detailed->چوٽي_border = timing[0x10];

    detailed->interlaced = get_ٻٽو_انگ (timing[0x11], 7);

    /* Stereo */
    بٽ = get_بٽ (timing[0x11], 5, 6) << 1 | get_ٻٽو_انگ (timing[0x11], 0);
    detailed->stereo = stereo[بٽ];

    /* Sync */
    بٽ = timing[0x11];

    detailed->digital_sync = get_ٻٽو_انگ (بٽ, 4);
    إذا (detailed->digital_sync)
    {
	detailed->ad.digital.مرکب = !get_ٻٽو_انگ (بٽ, 3);

	إذا (detailed->ad.digital.مرکب)
	{
	    detailed->ad.digital.serrations = get_ٻٽو_انگ (بٽ, 2);
	    detailed->ad.digital.negative_vsync = FALSE;
	}
	وإلا
	{
	    detailed->ad.digital.serrations = FALSE;
	    detailed->ad.digital.negative_vsync = !get_ٻٽو_انگ (بٽ, 2);
	}

	detailed->ad.digital.negative_hsync = !get_ٻٽو_انگ (بٽ, 0);
    }
    وإلا
    {
	detailed->ad.analog.bipolar = get_ٻٽو_انگ (بٽ, 3);
	detailed->ad.analog.serrations = get_ٻٽو_انگ (بٽ, 2);
	detailed->ad.analog.sync_on_green = !get_ٻٽو_انگ (بٽ, 1);
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
	صحيح اشاريو = 0x36 + i * 18;

	إذا (edid[اشاريو + 0] == 0x00 && edid[اشاريو + 1] == 0x00)
	{
	    decode_display_descriptor (edid + اشاريو, info);
	}
	وإلا
	{
	    decode_detailed_timing (
		edid + اشاريو, &(info->detailed_timings[timing_idx++]));
	}
    }

    info->n_detailed_timings = timing_idx;

    أرجع TRUE;
}

ساكن فراغ
decode_check_جوڙ (ثابت uchar *edid,
		  MonitorInfo *info)
{
    صحيح i;
    uchar check = 0;

    لكل (i = 0; i < 128; ++i)
	check += edid[i];

    info->checksum = check;
}

ساكن فراغ
decode_HDR_metadata_بلاڪ (ثابت uchar *معلومات, صحيح ڊيگهائي, MonitorInfo *info)
{
    إذا (ڊيگهائي >= 3)
	info->max_luminance = 50.0 * SDL_pow(2, معلومات[2] / 32.0);

    إذا (ڊيگهائي >= 4)
	info->max_چوکٺو_اوسط_luminance = 50.0 * SDL_pow(2, معلومات[3] / 32.0);

    إذا (ڊيگهائي >= 5)
	info->min_luminance = 50.0 * SDL_pow(2, معلومات[4] / 32.0);
}


ساكن فراغ
decode_cta_بلاڪ (ثابت uchar *edid,
		  MonitorInfo *info)
{
    صحيح وٿي_2 = 4;
    طالما (وٿي_2 < 128) {
	صحيح ڊيگهائي = edid[وٿي_2] & 0x1f;
	صحيح type = edid[وٿي_2] >> 5;
	إذا (ڊيگهائي == 0) {
	    اكسر;
	}
	إذا (type == 7) {
	    type <<= 8;
	    type |= edid[وٿي_2 + 1];
	}
	إذا (type == 0x706) {
	    decode_HDR_metadata_بلاڪ (&edid[وٿي_2 + 2], ڊيگهائي - 1, info);
	}
	وٿي_2 += (1 + ڊيگهائي);
    }
}

MonitorInfo *
decode_edid (ثابت uchar *edid, size_t سائيز)
{
    ثابت صحيح EDID_صفحو_سائيز = 128;
    صحيح انگ_بلاڪون = (سائيز / EDID_صفحو_سائيز);
    MonitorInfo *info;

    إذا ((سائيز % EDID_صفحو_سائيز) != 0) {
	أرجع عدم;
    }

    info = SDL_calloc (1, حجم (MonitorInfo));

    decode_check_جوڙ (edid, info);
    
    إذا (!decode_سرو (edid) ||
        !decode_vendor_and_حاصل_ضرب_identification (edid, info) ||
        !decode_edid_نسخو (edid, info) ||
        !decode_display_parameters (edid, info) ||
        !decode_color_characteristics (edid, info) ||
        !decode_established_timings (edid, info) ||
        !decode_standard_timings (edid, info) ||
        !decode_descriptors (edid, info)) {
	SDL_free(info);
	أرجع عدم;
    }
    
    إذا (انگ_بلاڪون > 1) {
	لكل (صحيح i = 1; i < انگ_بلاڪون; ++i) {
	    صحيح وٿي_2 = i * EDID_صفحو_سائيز;
	    uchar extension = edid[وٿي_2];
	    إذا (extension == 0x02) {
		// CTA-861 Extension Block
		decode_cta_بلاڪ (&edid[وٿي_2], info);
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
    
    لکو ("Checksum: %d (%s)\n",
	    info->checksum, info->checksum? "incorrect" : "correct");
    لکو ("Manufacturer Code: %s\n", info->manufacturer_ڪوڊ);
    لکو ("Product Code: 0x%x\n", info->حاصل_ضرب_ڪوڊ);
    لکو ("Serial Number: %u\n", info->serial_عدد);
    
    إذا (info->production_week != -1)
	لکو ("Production Week: %d\n", info->production_week);
    وإلا
	لکو ("Production Week: unspecified\n");
    
    إذا (info->production_year != -1)
	لکو ("Production Year: %d\n", info->production_year);
    وإلا
	لکو ("Production Year: unspecified\n");
    
    إذا (info->model_year != -1)
	لکو ("Model Year: %d\n", info->model_year);
    وإلا
	لکو ("Model Year: unspecified\n");
    
    لکو ("EDID revision: %d.%d\n", info->major_نسخو, info->minor_نسخو);
    
    لکو ("Display is %s\n", info->is_digital? "digital" : "analog");
    إذا (info->is_digital)
    {
	ثابت حرف *interface;
	إذا (info->ad.digital.بٽ_في_primary != -1)
	    لکو ("Bits Per Primary: %d\n", info->ad.digital.بٽ_في_primary);
	وإلا
	    لکو ("Bits Per Primary: undefined\n");
	
	بدل (info->ad.digital.interface)
	{
	حالة DVI: interface = "DVI"; اكسر;
	حالة HDMI_A: interface = "HDMI-a"; اكسر;
	حالة HDMI_B: interface = "HDMI-b"; اكسر;
	حالة MDDI: interface = "MDDI"; اكسر;
	حالة DISPLAY_پورٽ: interface = "DisplayPort"; اكسر;
	حالة UNDEFINED: interface = "undefined"; اكسر;
	افتراضي: interface = "unknown"; اكسر;
	}
	لکو ("Interface: %s\n", interface);
	
	لکو ("RGB 4:4:4: %s\n", yesno (info->ad.digital.rgb444));
	لکو ("YCrCb 4:4:4: %s\n", yesno (info->ad.digital.ycrcb444));
	لکو ("YCrCb 4:2:2: %s\n", yesno (info->ad.digital.ycrcb422));
    }
    وإلا
    {
       ثابت حرف *s;
	لکو ("Video Signal Level: %f\n", info->ad.analog.video_signal_level);
	لکو ("Sync Signal Level: %f\n", info->ad.analog.sync_signal_level);
	لکو ("Total Signal Level: %f\n", info->ad.analog.ڪل_signal_level);
	
	لکو ("Blank to Black: %s\n",
		yesno (info->ad.analog.blank_منزل_black));
	لکو ("Separate HV Sync: %s\n",
		yesno (info->ad.analog.separate_hv_sync));
	لکو ("Composite Sync on H: %s\n",
		yesno (info->ad.analog.مرکب_sync_on_h));
	لکو ("Serration on VSync: %s\n",
		yesno (info->ad.analog.serration_on_vsync));
	
	بدل (info->ad.analog.color_type)
	{
	حالة UNDEFINED_COLOR: s = "undefined"; اكسر;
	حالة MONOCHROME: s = "monochrome"; اكسر;
	حالة RGB: s = "rgb"; اكسر;
	حالة OTHER_COLOR: s = "other color"; اكسر;
	افتراضي: s = "unknown"; اكسر;
	}
	
	لکو ("Color: %s\n", s);
    }
    
    إذا (info->ويڪر_mm == -1)
	لکو ("Width: undefined\n");
    وإلا
	لکو ("Width: %d mm\n", info->ويڪر_mm);
    
    إذا (info->اوچائي_mm == -1)
	لکو ("Height: undefined\n");
    وإلا
	لکو ("Height: %d mm\n", info->اوچائي_mm);
    
    إذا (info->aspect_تناسب > 0)
	لکو ("Aspect Ratio: %f\n", info->aspect_تناسب);
    وإلا
	لکو ("Aspect Ratio: undefined\n");
    
    إذا (info->gamma >= 0)
	لکو ("Gamma: %f\n", info->gamma);
    وإلا
	لکو ("Gamma: undefined\n");
    
    لکو ("Standby: %s\n", yesno (info->standby));
    لکو ("Suspend: %s\n", yesno (info->suspend));
    لکو ("Active Off: %s\n", yesno (info->سرگرم_off));
    
    لکو ("SRGB is Standard: %s\n", yesno (info->srgb_is_standard));
    لکو ("Preferred Timing Includes Native: %s\n",
	    yesno (info->preferred_timing_includes_native));
    لکو ("Continuous Frequency: %s\n", yesno (info->continuous_frequency));
    
    لکو ("Red X: %f\n", info->red_x);
    لکو ("Red Y: %f\n", info->red_y);
    لکو ("Green X: %f\n", info->green_x);
    لکو ("Green Y: %f\n", info->green_y);
    لکو ("Blue X: %f\n", info->blue_x);
    لکو ("Blue Y: %f\n", info->blue_y);
    لکو ("White X: %f\n", info->white_x);
    لکو ("White Y: %f\n", info->white_y);
    لکو ("Min luminance: %f\n", info->min_luminance);
    لکو ("Max luminance: %f\n", info->max_luminance);
    لکو ("Max frame average luminance %f\n", info->max_چوکٺو_اوسط_luminance);
    
    لکو ("Established Timings:\n");
    
    لكل (i = 0; i < 24; ++i)
    {
	Timing *timing = &(info->established[i]);
	
	إذا (timing->frequency == 0)
	    اكسر;
	
	لکو ("  %d x %d @ %d Hz\n",
		timing->ويڪر, timing->اوچائي, timing->frequency);
	
    }
    
    لکو ("Standard Timings:\n");
    لكل (i = 0; i < 8; ++i)
    {
	Timing *timing = &(info->standard[i]);
	
	إذا (timing->frequency == 0)
	    اكسر;
	
	لکو ("  %d x %d @ %d Hz\n",
		timing->ويڪر, timing->اوچائي, timing->frequency);
    }
    
    لكل (i = 0; i < info->n_detailed_timings; ++i)
    {
	DetailedTiming *timing = &(info->detailed_timings[i]);
	ثابت حرف *s;
	
	لکو ("Timing%s: \n",
		(i == 0 && info->preferred_timing_includes_native)?
		" (Preferred)" : "");
	لکو ("  Pixel Clock: %d\n", timing->pixel_clock);
	لکو ("  H Addressable: %d\n", timing->h_addr);
	لکو ("  H Blank: %d\n", timing->h_blank);
	لکو ("  H Front Porch: %d\n", timing->h_front_porch);
	لکو ("  H Sync: %d\n", timing->h_sync);
	لکو ("  V Addressable: %d\n", timing->v_addr);
	لکو ("  V Blank: %d\n", timing->v_blank);
	لکو ("  V Front Porch: %d\n", timing->v_front_porch);
	لکو ("  V Sync: %d\n", timing->v_sync);
	لکو ("  Width: %d mm\n", timing->ويڪر_mm);
	لکو ("  Height: %d mm\n", timing->اوچائي_mm);
	لکو ("  Right Border: %d\n", timing->ساڄو_border);
	لکو ("  Top Border: %d\n", timing->چوٽي_border);
	بدل (timing->stereo)
	{
	افتراضي:
	حالة NO_STEREO:   s = "No Stereo"; اكسر;
	حالة ميدان_ساڄو: s = "Field Sequential, Right on Sync"; اكسر;
	حالة ميدان_کاٻو:  s = "Field Sequential, Left on Sync"; اكسر;
	حالة TWO_WAY_ساڄو_ON_EVEN: s = "Two-way, Right on Even"; اكسر;
	حالة TWO_WAY_کاٻو_ON_EVEN:  s = "Two-way, Left on Even"; اكسر;
	حالة FOUR_WAY_INTERLEAVED:  s = "Four-way Interleaved"; اكسر;
	حالة SIDE_BY_SIDE:          s = "Side-by-Side"; اكسر;
	}
	لکو ("  Stereo: %s\n", s);
	
	إذا (timing->digital_sync)
	{
	    لکو ("  Digital Sync:\n");
	    لکو ("    composite: %s\n", yesno (timing->ad.digital.مرکب));
	    لکو ("    serrations: %s\n", yesno (timing->ad.digital.serrations));
	    لکو ("    negative vsync: %s\n",
		    yesno (timing->ad.digital.negative_vsync));
	    لکو ("    negative hsync: %s\n",
		    yesno (timing->ad.digital.negative_hsync));
	}
	وإلا
	{
	    لکو ("  Analog Sync:\n");
	    لکو ("    bipolar: %s\n", yesno (timing->ad.analog.bipolar));
	    لکو ("    serrations: %s\n", yesno (timing->ad.analog.serrations));
	    لکو ("    sync on green: %s\n", yesno (
			timing->ad.analog.sync_on_green));
	}
    }
    
    لکو ("Detailed Product information:\n");
    لکو ("  Product Name: %s\n", info->dsc_حاصل_ضرب_name);
    لکو ("  Serial Number: %s\n", info->dsc_serial_عدد);
    لکو ("  Unspecified String: %s\n", info->dsc_string);
}

