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

#تعریف_کرو TRUE 1
#تعریف_کرو FALSE 0

ساكن صحيح
get_ثنائی_ہندسہ (صحيح وچ_2, صحيح ثنائی_ہندسہ)
{
    أرجع (وچ_2 & (1 << ثنائی_ہندسہ)) >> ثنائی_ہندسہ;
}

ساكن صحيح
get_بٹ (صحيح وچ_2, صحيح begin, صحيح سرا)
{
    صحيح نقاب = (1 << (سرا - begin + 1)) - 1;
    
    أرجع (وچ_2 >> begin) & نقاب;
}

ساكن صحيح
decode_سرخی (ثابت uchar *edid)
{
    إذا (SDL_memcmp (edid, "\x00\xff\xff\xff\xff\xff\xff\x00", 8) == 0)
	أرجع TRUE;
    أرجع FALSE;
}

ساكن صحيح
decode_vendor_and_ضرب_حاصل_identification (ثابت uchar *edid, MonitorInfo *info)
{
    صحيح is_model_year;
    
    /* Manufacturer Code */
    info->manufacturer_کوڈ[0]  = get_بٹ (edid[0x08], 2, 6);
    info->manufacturer_کوڈ[1]  = get_بٹ (edid[0x08], 0, 1) << 3;
    info->manufacturer_کوڈ[1] |= get_بٹ (edid[0x09], 5, 7);
    info->manufacturer_کوڈ[2]  = get_بٹ (edid[0x09], 0, 4);
    info->manufacturer_کوڈ[3]  = '\0';
    
    info->manufacturer_کوڈ[0] += 'A' - 1;
    info->manufacturer_کوڈ[1] += 'A' - 1;
    info->manufacturer_کوڈ[2] += 'A' - 1;

    /* Product Code */
    info->ضرب_حاصل_کوڈ = edid[0x0b] << 8 | edid[0x0a];

    /* Serial Number */
    info->serial_نمبر =
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
decode_edid_نسخہ (ثابت uchar *edid, MonitorInfo *info)
{
    info->major_نسخہ = edid[0x12];
    info->minor_نسخہ = edid[0x13];

    أرجع TRUE;
}

ساكن صحيح
decode_display_parameters (ثابت uchar *edid, MonitorInfo *info)
{
    /* Digital vs Analog */
    info->is_digital = get_ثنائی_ہندسہ (edid[0x14], 7);

    إذا (info->is_digital)
    {
	صحيح بٹ;
	
	ساكن ثابت صحيح ثنائی_ہندسہ_ڈونگھائی_2[8] =
	{
	    -1, 6, 8, 10, 12, 14, 16, -1
	};

	ساكن ثابت Interface interfaces[6] =
	{
	    UNDEFINED, DVI, HDMI_A, HDMI_B, MDDI, DISPLAY_پورٹ
	};

	بٹ = get_بٹ (edid[0x14], 4, 6);
	info->ad.digital.بٹ_فی_primary = ثنائی_ہندسہ_ڈونگھائی_2[بٹ];

	بٹ = get_بٹ (edid[0x14], 0, 3);
	
	إذا (بٹ <= 5)
	    info->ad.digital.interface = interfaces[بٹ];
	وإلا
	    info->ad.digital.interface = UNDEFINED;
    }
    وإلا
    {
	صحيح بٹ = get_بٹ (edid[0x14], 5, 6);
	
	ساكن ثابت مزدوج پدھراں[][3] =
	{
	    { 0.7,   0.3,    1.0 },
	    { 0.714, 0.286,  1.0 },
	    { 1.0,   0.4,    1.4 },
	    { 0.7,   0.0,    0.7 },
	};

	info->ad.analog.video_signal_level = پدھراں[بٹ][0];
	info->ad.analog.sync_signal_level = پدھراں[بٹ][1];
	info->ad.analog.کل_signal_level = پدھراں[بٹ][2];

	info->ad.analog.blank_منزل_black = get_ثنائی_ہندسہ (edid[0x14], 4);

	info->ad.analog.separate_hv_sync = get_ثنائی_ہندسہ (edid[0x14], 3);
	info->ad.analog.مرکب_sync_on_h = get_ثنائی_ہندسہ (edid[0x14], 2);
	info->ad.analog.مرکب_sync_on_green = get_ثنائی_ہندسہ (edid[0x14], 1);

	info->ad.analog.serration_on_vsync = get_ثنائی_ہندسہ (edid[0x14], 0);
    }

    /* Screen Size / Aspect Ratio */
    إذا (edid[0x15] == 0 && edid[0x16] == 0)
    {
	info->چوڑائی_mm = -1;
	info->اچائی_mm = -1;
	info->aspect_تناسب = -1.0;
    }
    وإلا إذا (edid[0x16] == 0)
    {
	info->چوڑائی_mm = -1;
	info->اچائی_mm = -1; 
	info->aspect_تناسب = 100.0 / (edid[0x15] + 99);
    }
    وإلا إذا (edid[0x15] == 0)
    {
	info->چوڑائی_mm = -1;
	info->اچائی_mm = -1;
	info->aspect_تناسب = 100.0 / (edid[0x16] + 99);
	info->aspect_تناسب = 1/info->aspect_تناسب; /* portrait */
    }
    وإلا
    {
	info->چوڑائی_mm = 10 * edid[0x15];
	info->اچائی_mm = 10 * edid[0x16];
    }

    /* Gamma */
    إذا (edid[0x17] == 0xFF)
	info->gamma = -1.0;
    وإلا
	info->gamma = (edid[0x17] + 100.0) / 100.0;

    /* Features */
    info->standby = get_ثنائی_ہندسہ (edid[0x18], 7);
    info->suspend = get_ثنائی_ہندسہ (edid[0x18], 6);
    info->سرگرم_off = get_ثنائی_ہندسہ (edid[0x18], 5);

    إذا (info->is_digital)
    {
	info->ad.digital.rgb444 = TRUE;
	إذا (get_ثنائی_ہندسہ (edid[0x18], 3))
	    info->ad.digital.ycrcb444 = 1;
	إذا (get_ثنائی_ہندسہ (edid[0x18], 4))
	    info->ad.digital.ycrcb422 = 1;
    }
    وإلا
    {
	صحيح بٹ = get_بٹ (edid[0x18], 3, 4);
	ColorType color_type[4] =
	{
	    MONOCHROME, RGB, OTHER_COLOR, UNDEFINED_COLOR
	};

	info->ad.analog.color_type = color_type[بٹ];
    }

    info->srgb_is_standard = get_ثنائی_ہندسہ (edid[0x18], 2);

    /* In 1.3 this is called "has preferred timing" */
    info->preferred_timing_includes_native = get_ثنائی_ہندسہ (edid[0x18], 1);

    /* FIXME: In 1.3 this indicates whether the monitor accepts GTF */
    info->continuous_frequency = get_ثنائی_ہندسہ (edid[0x18], 0);
    أرجع TRUE;
}

ساكن مزدوج
decode_fraction (صحيح بلند, صحيح کم_2)
{
    مزدوج نتیجہ = 0.0;
    صحيح i;

    بلند = (بلند << 2) | کم_2;

    لكل (i = 0; i < 10; ++i)
	نتیجہ += get_ثنائی_ہندسہ (بلند, i) * SDL_pow (2, i - 10);

    أرجع نتیجہ;
}

ساكن صحيح
decode_color_characteristics (ثابت uchar *edid, MonitorInfo *info)
{
    info->red_x = decode_fraction (edid[0x1b], get_بٹ (edid[0x19], 6, 7));
    info->red_y = decode_fraction (edid[0x1c], get_بٹ (edid[0x19], 5, 4));
    info->green_x = decode_fraction (edid[0x1d], get_بٹ (edid[0x19], 2, 3));
    info->green_y = decode_fraction (edid[0x1e], get_بٹ (edid[0x19], 0, 1));
    info->blue_x = decode_fraction (edid[0x1f], get_بٹ (edid[0x1a], 6, 7));
    info->blue_y = decode_fraction (edid[0x20], get_بٹ (edid[0x1a], 4, 5));
    info->white_x = decode_fraction (edid[0x21], get_بٹ (edid[0x1a], 2, 3));
    info->white_y = decode_fraction (edid[0x22], get_بٹ (edid[0x1a], 0, 1));

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

	    إذا (get_ثنائی_ہندسہ (byte, j) && established[i][j].frequency != 0)
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
	صحيح پہلا = edid[0x26 + 2 * i];
	صحيح دوجا = edid[0x27 + 2 * i];

	إذا (پہلا != 0x01 && دوجا != 0x01)
	{
	    صحيح w = 8 * (پہلا + 31);
	    صحيح h = 0;

	    بدل (get_بٹ (دوجا, 6, 7))
	    {
	    حالة 0x00: h = (w / 16) * 10; اكسر;
	    حالة 0x01: h = (w / 4) * 3; اكسر;
	    حالة 0x02: h = (w / 5) * 4; اكسر;
	    حالة 0x03: h = (w / 16) * 9; اكسر;
	    }

	    info->standard[i].چوڑائی = w;
	    info->standard[i].اچائی = h;
	    info->standard[i].frequency = get_بٹ (دوجا, 0, 5) + 60;
	}
    }
    
    أرجع TRUE;
}

ساكن فراغ
decode_lf_string (ثابت uchar *s, صحيح n_chars, حرف *نتیجہ)
{
    صحيح i;
    لكل (i = 0; i < n_chars; ++i)
    {
	إذا (s[i] == 0x0a)
	{
	    *نتیجہ++ = '\0';
	    اكسر;
	}
	وإلا إذا (s[i] == 0x00)
	{
	    /* Convert embedded 0's to spaces */
	    *نتیجہ++ = ' ';
	}
	وإلا
	{
	    *نتیجہ++ = s[i];
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
	decode_lf_string (desc + 5, 13, info->dsc_ضرب_حاصل_name);
	اكسر;
    حالة 0xFF:
	decode_lf_string (desc + 5, 13, info->dsc_serial_نمبر);
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
    صحيح بٹ;
    StereoType stereo[] =
    {
	NO_STEREO, NO_STEREO, میدان_دایاں, میدان_بایاں,
	TWO_WAY_دایاں_ON_EVEN, TWO_WAY_بایاں_ON_EVEN,
	FOUR_WAY_INTERLEAVED, SIDE_BY_SIDE
    };
    
    detailed->pixel_clock = (timing[0x00] | timing[0x01] << 8) * 10000;
    detailed->h_addr = timing[0x02] | ((timing[0x04] & 0xf0) << 4);
    detailed->h_blank = timing[0x03] | ((timing[0x04] & 0x0f) << 8);
    detailed->v_addr = timing[0x05] | ((timing[0x07] & 0xf0) << 4);
    detailed->v_blank = timing[0x06] | ((timing[0x07] & 0x0f) << 8);
    detailed->h_front_porch = timing[0x08] | get_بٹ (timing[0x0b], 6, 7) << 8;
    detailed->h_sync = timing[0x09] | get_بٹ (timing[0x0b], 4, 5) << 8;
    detailed->v_front_porch =
	get_بٹ (timing[0x0a], 4, 7) | get_بٹ (timing[0x0b], 2, 3) << 4;
    detailed->v_sync =
	get_بٹ (timing[0x0a], 0, 3) | get_بٹ (timing[0x0b], 0, 1) << 4;
    detailed->چوڑائی_mm =  timing[0x0c] | get_بٹ (timing[0x0e], 4, 7) << 8;
    detailed->اچائی_mm = timing[0x0d] | get_بٹ (timing[0x0e], 0, 3) << 8;
    detailed->دایاں_border = timing[0x0f];
    detailed->چوٹی_border = timing[0x10];

    detailed->interlaced = get_ثنائی_ہندسہ (timing[0x11], 7);

    /* Stereo */
    بٹ = get_بٹ (timing[0x11], 5, 6) << 1 | get_ثنائی_ہندسہ (timing[0x11], 0);
    detailed->stereo = stereo[بٹ];

    /* Sync */
    بٹ = timing[0x11];

    detailed->digital_sync = get_ثنائی_ہندسہ (بٹ, 4);
    إذا (detailed->digital_sync)
    {
	detailed->ad.digital.مرکب = !get_ثنائی_ہندسہ (بٹ, 3);

	إذا (detailed->ad.digital.مرکب)
	{
	    detailed->ad.digital.serrations = get_ثنائی_ہندسہ (بٹ, 2);
	    detailed->ad.digital.negative_vsync = FALSE;
	}
	وإلا
	{
	    detailed->ad.digital.serrations = FALSE;
	    detailed->ad.digital.negative_vsync = !get_ثنائی_ہندسہ (بٹ, 2);
	}

	detailed->ad.digital.negative_hsync = !get_ثنائی_ہندسہ (بٹ, 0);
    }
    وإلا
    {
	detailed->ad.analog.bipolar = get_ثنائی_ہندسہ (بٹ, 3);
	detailed->ad.analog.serrations = get_ثنائی_ہندسہ (بٹ, 2);
	detailed->ad.analog.sync_on_green = !get_ثنائی_ہندسہ (بٹ, 1);
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
	صحيح اشاریہ = 0x36 + i * 18;

	إذا (edid[اشاریہ + 0] == 0x00 && edid[اشاریہ + 1] == 0x00)
	{
	    decode_display_descriptor (edid + اشاریہ, info);
	}
	وإلا
	{
	    decode_detailed_timing (
		edid + اشاریہ, &(info->detailed_timings[timing_idx++]));
	}
    }

    info->n_detailed_timings = timing_idx;

    أرجع TRUE;
}

ساكن فراغ
decode_check_جوڑ (ثابت uchar *edid,
		  MonitorInfo *info)
{
    صحيح i;
    uchar check = 0;

    لكل (i = 0; i < 128; ++i)
	check += edid[i];

    info->checksum = check;
}

ساكن فراغ
decode_HDR_metadata_بلاک (ثابت uchar *انکڑے, صحيح لمائی, MonitorInfo *info)
{
    إذا (لمائی >= 3)
	info->max_luminance = 50.0 * SDL_pow(2, انکڑے[2] / 32.0);

    إذا (لمائی >= 4)
	info->max_چوکھٹا_اوسطن_luminance = 50.0 * SDL_pow(2, انکڑے[3] / 32.0);

    إذا (لمائی >= 5)
	info->min_luminance = 50.0 * SDL_pow(2, انکڑے[4] / 32.0);
}


ساكن فراغ
decode_cta_بلاک (ثابت uchar *edid,
		  MonitorInfo *info)
{
    صحيح وتھ_2 = 4;
    طالما (وتھ_2 < 128) {
	صحيح لمائی = edid[وتھ_2] & 0x1f;
	صحيح type = edid[وتھ_2] >> 5;
	إذا (لمائی == 0) {
	    اكسر;
	}
	إذا (type == 7) {
	    type <<= 8;
	    type |= edid[وتھ_2 + 1];
	}
	إذا (type == 0x706) {
	    decode_HDR_metadata_بلاک (&edid[وتھ_2 + 2], لمائی - 1, info);
	}
	وتھ_2 += (1 + لمائی);
    }
}

MonitorInfo *
decode_edid (ثابت uchar *edid, size_t ناپ)
{
    ثابت صحيح EDID_ورقہ_ناپ = 128;
    صحيح عدد_بلاکاں = (ناپ / EDID_ورقہ_ناپ);
    MonitorInfo *info;

    إذا ((ناپ % EDID_ورقہ_ناپ) != 0) {
	أرجع عدم;
    }

    info = SDL_calloc (1, حجم (MonitorInfo));

    decode_check_جوڑ (edid, info);
    
    إذا (!decode_سرخی (edid) ||
        !decode_vendor_and_ضرب_حاصل_identification (edid, info) ||
        !decode_edid_نسخہ (edid, info) ||
        !decode_display_parameters (edid, info) ||
        !decode_color_characteristics (edid, info) ||
        !decode_established_timings (edid, info) ||
        !decode_standard_timings (edid, info) ||
        !decode_descriptors (edid, info)) {
	SDL_free(info);
	أرجع عدم;
    }
    
    إذا (عدد_بلاکاں > 1) {
	لكل (صحيح i = 1; i < عدد_بلاکاں; ++i) {
	    صحيح وتھ_2 = i * EDID_ورقہ_ناپ;
	    uchar extension = edid[وتھ_2];
	    إذا (extension == 0x02) {
		// CTA-861 Extension Block
		decode_cta_بلاک (&edid[وتھ_2], info);
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
    
    لکھو ("Checksum: %d (%s)\n",
	    info->checksum, info->checksum? "incorrect" : "correct");
    لکھو ("Manufacturer Code: %s\n", info->manufacturer_کوڈ);
    لکھو ("Product Code: 0x%x\n", info->ضرب_حاصل_کوڈ);
    لکھو ("Serial Number: %u\n", info->serial_نمبر);
    
    إذا (info->production_week != -1)
	لکھو ("Production Week: %d\n", info->production_week);
    وإلا
	لکھو ("Production Week: unspecified\n");
    
    إذا (info->production_year != -1)
	لکھو ("Production Year: %d\n", info->production_year);
    وإلا
	لکھو ("Production Year: unspecified\n");
    
    إذا (info->model_year != -1)
	لکھو ("Model Year: %d\n", info->model_year);
    وإلا
	لکھو ("Model Year: unspecified\n");
    
    لکھو ("EDID revision: %d.%d\n", info->major_نسخہ, info->minor_نسخہ);
    
    لکھو ("Display is %s\n", info->is_digital? "digital" : "analog");
    إذا (info->is_digital)
    {
	ثابت حرف *interface;
	إذا (info->ad.digital.بٹ_فی_primary != -1)
	    لکھو ("Bits Per Primary: %d\n", info->ad.digital.بٹ_فی_primary);
	وإلا
	    لکھو ("Bits Per Primary: undefined\n");
	
	بدل (info->ad.digital.interface)
	{
	حالة DVI: interface = "DVI"; اكسر;
	حالة HDMI_A: interface = "HDMI-a"; اكسر;
	حالة HDMI_B: interface = "HDMI-b"; اكسر;
	حالة MDDI: interface = "MDDI"; اكسر;
	حالة DISPLAY_پورٹ: interface = "DisplayPort"; اكسر;
	حالة UNDEFINED: interface = "undefined"; اكسر;
	افتراضي: interface = "unknown"; اكسر;
	}
	لکھو ("Interface: %s\n", interface);
	
	لکھو ("RGB 4:4:4: %s\n", yesno (info->ad.digital.rgb444));
	لکھو ("YCrCb 4:4:4: %s\n", yesno (info->ad.digital.ycrcb444));
	لکھو ("YCrCb 4:2:2: %s\n", yesno (info->ad.digital.ycrcb422));
    }
    وإلا
    {
       ثابت حرف *s;
	لکھو ("Video Signal Level: %f\n", info->ad.analog.video_signal_level);
	لکھو ("Sync Signal Level: %f\n", info->ad.analog.sync_signal_level);
	لکھو ("Total Signal Level: %f\n", info->ad.analog.کل_signal_level);
	
	لکھو ("Blank to Black: %s\n",
		yesno (info->ad.analog.blank_منزل_black));
	لکھو ("Separate HV Sync: %s\n",
		yesno (info->ad.analog.separate_hv_sync));
	لکھو ("Composite Sync on H: %s\n",
		yesno (info->ad.analog.مرکب_sync_on_h));
	لکھو ("Serration on VSync: %s\n",
		yesno (info->ad.analog.serration_on_vsync));
	
	بدل (info->ad.analog.color_type)
	{
	حالة UNDEFINED_COLOR: s = "undefined"; اكسر;
	حالة MONOCHROME: s = "monochrome"; اكسر;
	حالة RGB: s = "rgb"; اكسر;
	حالة OTHER_COLOR: s = "other color"; اكسر;
	افتراضي: s = "unknown"; اكسر;
	}
	
	لکھو ("Color: %s\n", s);
    }
    
    إذا (info->چوڑائی_mm == -1)
	لکھو ("Width: undefined\n");
    وإلا
	لکھو ("Width: %d mm\n", info->چوڑائی_mm);
    
    إذا (info->اچائی_mm == -1)
	لکھو ("Height: undefined\n");
    وإلا
	لکھو ("Height: %d mm\n", info->اچائی_mm);
    
    إذا (info->aspect_تناسب > 0)
	لکھو ("Aspect Ratio: %f\n", info->aspect_تناسب);
    وإلا
	لکھو ("Aspect Ratio: undefined\n");
    
    إذا (info->gamma >= 0)
	لکھو ("Gamma: %f\n", info->gamma);
    وإلا
	لکھو ("Gamma: undefined\n");
    
    لکھو ("Standby: %s\n", yesno (info->standby));
    لکھو ("Suspend: %s\n", yesno (info->suspend));
    لکھو ("Active Off: %s\n", yesno (info->سرگرم_off));
    
    لکھو ("SRGB is Standard: %s\n", yesno (info->srgb_is_standard));
    لکھو ("Preferred Timing Includes Native: %s\n",
	    yesno (info->preferred_timing_includes_native));
    لکھو ("Continuous Frequency: %s\n", yesno (info->continuous_frequency));
    
    لکھو ("Red X: %f\n", info->red_x);
    لکھو ("Red Y: %f\n", info->red_y);
    لکھو ("Green X: %f\n", info->green_x);
    لکھو ("Green Y: %f\n", info->green_y);
    لکھو ("Blue X: %f\n", info->blue_x);
    لکھو ("Blue Y: %f\n", info->blue_y);
    لکھو ("White X: %f\n", info->white_x);
    لکھو ("White Y: %f\n", info->white_y);
    لکھو ("Min luminance: %f\n", info->min_luminance);
    لکھو ("Max luminance: %f\n", info->max_luminance);
    لکھو ("Max frame average luminance %f\n", info->max_چوکھٹا_اوسطن_luminance);
    
    لکھو ("Established Timings:\n");
    
    لكل (i = 0; i < 24; ++i)
    {
	Timing *timing = &(info->established[i]);
	
	إذا (timing->frequency == 0)
	    اكسر;
	
	لکھو ("  %d x %d @ %d Hz\n",
		timing->چوڑائی, timing->اچائی, timing->frequency);
	
    }
    
    لکھو ("Standard Timings:\n");
    لكل (i = 0; i < 8; ++i)
    {
	Timing *timing = &(info->standard[i]);
	
	إذا (timing->frequency == 0)
	    اكسر;
	
	لکھو ("  %d x %d @ %d Hz\n",
		timing->چوڑائی, timing->اچائی, timing->frequency);
    }
    
    لكل (i = 0; i < info->n_detailed_timings; ++i)
    {
	DetailedTiming *timing = &(info->detailed_timings[i]);
	ثابت حرف *s;
	
	لکھو ("Timing%s: \n",
		(i == 0 && info->preferred_timing_includes_native)?
		" (Preferred)" : "");
	لکھو ("  Pixel Clock: %d\n", timing->pixel_clock);
	لکھو ("  H Addressable: %d\n", timing->h_addr);
	لکھو ("  H Blank: %d\n", timing->h_blank);
	لکھو ("  H Front Porch: %d\n", timing->h_front_porch);
	لکھو ("  H Sync: %d\n", timing->h_sync);
	لکھو ("  V Addressable: %d\n", timing->v_addr);
	لکھو ("  V Blank: %d\n", timing->v_blank);
	لکھو ("  V Front Porch: %d\n", timing->v_front_porch);
	لکھو ("  V Sync: %d\n", timing->v_sync);
	لکھو ("  Width: %d mm\n", timing->چوڑائی_mm);
	لکھو ("  Height: %d mm\n", timing->اچائی_mm);
	لکھو ("  Right Border: %d\n", timing->دایاں_border);
	لکھو ("  Top Border: %d\n", timing->چوٹی_border);
	بدل (timing->stereo)
	{
	افتراضي:
	حالة NO_STEREO:   s = "No Stereo"; اكسر;
	حالة میدان_دایاں: s = "Field Sequential, Right on Sync"; اكسر;
	حالة میدان_بایاں:  s = "Field Sequential, Left on Sync"; اكسر;
	حالة TWO_WAY_دایاں_ON_EVEN: s = "Two-way, Right on Even"; اكسر;
	حالة TWO_WAY_بایاں_ON_EVEN:  s = "Two-way, Left on Even"; اكسر;
	حالة FOUR_WAY_INTERLEAVED:  s = "Four-way Interleaved"; اكسر;
	حالة SIDE_BY_SIDE:          s = "Side-by-Side"; اكسر;
	}
	لکھو ("  Stereo: %s\n", s);
	
	إذا (timing->digital_sync)
	{
	    لکھو ("  Digital Sync:\n");
	    لکھو ("    composite: %s\n", yesno (timing->ad.digital.مرکب));
	    لکھو ("    serrations: %s\n", yesno (timing->ad.digital.serrations));
	    لکھو ("    negative vsync: %s\n",
		    yesno (timing->ad.digital.negative_vsync));
	    لکھو ("    negative hsync: %s\n",
		    yesno (timing->ad.digital.negative_hsync));
	}
	وإلا
	{
	    لکھو ("  Analog Sync:\n");
	    لکھو ("    bipolar: %s\n", yesno (timing->ad.analog.bipolar));
	    لکھو ("    serrations: %s\n", yesno (timing->ad.analog.serrations));
	    لکھو ("    sync on green: %s\n", yesno (
			timing->ad.analog.sync_on_green));
	}
    }
    
    لکھو ("Detailed Product information:\n");
    لکھو ("  Product Name: %s\n", info->dsc_ضرب_حاصل_name);
    لکھو ("  Serial Number: %s\n", info->dsc_serial_نمبر);
    لکھو ("  Unspecified String: %s\n", info->dsc_string);
}

