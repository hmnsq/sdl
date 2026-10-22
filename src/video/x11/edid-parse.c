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
#شامل "SDL_internal.h"

#شامل "edid.h"
#شامل <stdlib.h>
#شامل <string.h>
#شامل <math.h>
#شامل <stdio.h>

#تعریف_کرو TRUE 1
#تعریف_کرو FALSE 0

ساکن صحیح
get_ثنائی_ہندسہ (صحیح اندر_2, صحیح ثنائی_ہندسہ)
{
    واپس (اندر_2 & (1 << ثنائی_ہندسہ)) >> ثنائی_ہندسہ;
}

ساکن صحیح
get_بٹ (صحیح اندر_2, صحیح begin, صحیح انتہا)
{
    صحیح نقاب = (1 << (انتہا - begin + 1)) - 1;
    
    واپس (اندر_2 >> begin) & نقاب;
}

ساکن صحیح
decode_سرخی (ثابت uchar *edid)
{
    اگر (SDL_memcmp (edid, "\x00\xff\xff\xff\xff\xff\xff\x00", 8) == 0)
	واپس TRUE;
    واپس FALSE;
}

ساکن صحیح
decode_vendor_and_حاصل_ضرب_identification (ثابت uchar *edid, MonitorInfo *info)
{
    صحیح is_model_year;
    
    /* Manufacturer Code */
    info->manufacturer_رمز[0]  = get_بٹ (edid[0x08], 2, 6);
    info->manufacturer_رمز[1]  = get_بٹ (edid[0x08], 0, 1) << 3;
    info->manufacturer_رمز[1] |= get_بٹ (edid[0x09], 5, 7);
    info->manufacturer_رمز[2]  = get_بٹ (edid[0x09], 0, 4);
    info->manufacturer_رمز[3]  = '\0';
    
    info->manufacturer_رمز[0] += 'A' - 1;
    info->manufacturer_رمز[1] += 'A' - 1;
    info->manufacturer_رمز[2] += 'A' - 1;

    /* Product Code */
    info->حاصل_ضرب_رمز = edid[0x0b] << 8 | edid[0x0a];

    /* Serial Number */
    info->serial_نمبر =
	edid[0x0c] | edid[0x0d] << 8 | edid[0x0e] << 16 | (Uint32)edid[0x0f] << 24;

    /* Week and Year */
    is_model_year = FALSE;
    انتخاب (edid[0x10])
    {
    حالت 0x00:
	info->production_week = -1;
	توڑو;

    حالت 0xff:
	info->production_week = -1;
	is_model_year = TRUE;
	توڑو;

    طےشدہ:
	info->production_week = edid[0x10];
	توڑو;
    }

    اگر (is_model_year)
    {
	info->production_year = -1;
	info->model_year = 1990 + edid[0x11];
    }
    ورنہ
    {
	info->production_year = 1990 + edid[0x11];
	info->model_year = -1;
    }

    واپس TRUE;
}

ساکن صحیح
decode_edid_نسخہ (ثابت uchar *edid, MonitorInfo *info)
{
    info->major_نسخہ = edid[0x12];
    info->minor_نسخہ = edid[0x13];

    واپس TRUE;
}

ساکن صحیح
decode_display_parameters (ثابت uchar *edid, MonitorInfo *info)
{
    /* Digital vs Analog */
    info->is_digital = get_ثنائی_ہندسہ (edid[0x14], 7);

    اگر (info->is_digital)
    {
	صحیح بٹ;
	
	ساکن ثابت صحیح ثنائی_ہندسہ_گہرائی_2[8] =
	{
	    -1, 6, 8, 10, 12, 14, 16, -1
	};

	ساکن ثابت Interface interfaces[6] =
	{
	    UNDEFINED, DVI, HDMI_A, HDMI_B, MDDI, DISPLAY_پورٹ
	};

	بٹ = get_بٹ (edid[0x14], 4, 6);
	info->ad.digital.بٹ_فی_primary = ثنائی_ہندسہ_گہرائی_2[بٹ];

	بٹ = get_بٹ (edid[0x14], 0, 3);
	
	اگر (بٹ <= 5)
	    info->ad.digital.interface = interfaces[بٹ];
	ورنہ
	    info->ad.digital.interface = UNDEFINED;
    }
    ورنہ
    {
	صحیح بٹ = get_بٹ (edid[0x14], 5, 6);
	
	ساکن ثابت دوہرا سطحیں[][3] =
	{
	    { 0.7,   0.3,    1.0 },
	    { 0.714, 0.286,  1.0 },
	    { 1.0,   0.4,    1.4 },
	    { 0.7,   0.0,    0.7 },
	};

	info->ad.analog.video_signal_level = سطحیں[بٹ][0];
	info->ad.analog.sync_signal_level = سطحیں[بٹ][1];
	info->ad.analog.کل_signal_level = سطحیں[بٹ][2];

	info->ad.analog.blank_مقصد_black = get_ثنائی_ہندسہ (edid[0x14], 4);

	info->ad.analog.separate_hv_sync = get_ثنائی_ہندسہ (edid[0x14], 3);
	info->ad.analog.مرکب_sync_on_h = get_ثنائی_ہندسہ (edid[0x14], 2);
	info->ad.analog.مرکب_sync_on_green = get_ثنائی_ہندسہ (edid[0x14], 1);

	info->ad.analog.serration_on_vsync = get_ثنائی_ہندسہ (edid[0x14], 0);
    }

    /* Screen Size / Aspect Ratio */
    اگر (edid[0x15] == 0 && edid[0x16] == 0)
    {
	info->چوڑائی_mm = -1;
	info->اونچائی_mm = -1;
	info->aspect_تناسب = -1.0;
    }
    ورنہ اگر (edid[0x16] == 0)
    {
	info->چوڑائی_mm = -1;
	info->اونچائی_mm = -1; 
	info->aspect_تناسب = 100.0 / (edid[0x15] + 99);
    }
    ورنہ اگر (edid[0x15] == 0)
    {
	info->چوڑائی_mm = -1;
	info->اونچائی_mm = -1;
	info->aspect_تناسب = 100.0 / (edid[0x16] + 99);
	info->aspect_تناسب = 1/info->aspect_تناسب; /* portrait */
    }
    ورنہ
    {
	info->چوڑائی_mm = 10 * edid[0x15];
	info->اونچائی_mm = 10 * edid[0x16];
    }

    /* Gamma */
    اگر (edid[0x17] == 0xFF)
	info->gamma = -1.0;
    ورنہ
	info->gamma = (edid[0x17] + 100.0) / 100.0;

    /* Features */
    info->standby = get_ثنائی_ہندسہ (edid[0x18], 7);
    info->suspend = get_ثنائی_ہندسہ (edid[0x18], 6);
    info->فعال_off = get_ثنائی_ہندسہ (edid[0x18], 5);

    اگر (info->is_digital)
    {
	info->ad.digital.rgb444 = TRUE;
	اگر (get_ثنائی_ہندسہ (edid[0x18], 3))
	    info->ad.digital.ycrcb444 = 1;
	اگر (get_ثنائی_ہندسہ (edid[0x18], 4))
	    info->ad.digital.ycrcb422 = 1;
    }
    ورنہ
    {
	صحیح بٹ = get_بٹ (edid[0x18], 3, 4);
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
    واپس TRUE;
}

ساکن دوہرا
decode_fraction (صحیح بلند, صحیح کم)
{
    دوہرا نتیجہ = 0.0;
    صحیح i;

    بلند = (بلند << 2) | کم;

    برائے (i = 0; i < 10; ++i)
	نتیجہ += get_ثنائی_ہندسہ (بلند, i) * SDL_pow (2, i - 10);

    واپس نتیجہ;
}

ساکن صحیح
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

    واپس TRUE;
}

ساکن صحیح
decode_established_timings (ثابت uchar *edid, MonitorInfo *info)
{
    ساکن ثابت Timing established[][8] = 
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

    صحیح i, j, idx;

    idx = 0;
    برائے (i = 0; i < 3; ++i)
    {
	برائے (j = 0; j < 8; ++j)
	{
	    صحیح byte = edid[0x23 + i];

	    اگر (get_ثنائی_ہندسہ (byte, j) && established[i][j].frequency != 0)
		info->established[idx++] = established[i][j];
	}
    }
    واپس TRUE;
}

ساکن صحیح
decode_standard_timings (ثابت uchar *edid, MonitorInfo *info)
{
    صحیح i;
    
    برائے (i = 0; i < 8; i++)
    {
	صحیح پہلا = edid[0x26 + 2 * i];
	صحیح دوسرا = edid[0x27 + 2 * i];

	اگر (پہلا != 0x01 && دوسرا != 0x01)
	{
	    صحیح w = 8 * (پہلا + 31);
	    صحیح h = 0;

	    انتخاب (get_بٹ (دوسرا, 6, 7))
	    {
	    حالت 0x00: h = (w / 16) * 10; توڑو;
	    حالت 0x01: h = (w / 4) * 3; توڑو;
	    حالت 0x02: h = (w / 5) * 4; توڑو;
	    حالت 0x03: h = (w / 16) * 9; توڑو;
	    }

	    info->standard[i].چوڑائی = w;
	    info->standard[i].اونچائی = h;
	    info->standard[i].frequency = get_بٹ (دوسرا, 0, 5) + 60;
	}
    }
    
    واپس TRUE;
}

ساکن خالی
decode_lf_string (ثابت uchar *s, صحیح n_chars, حرف *نتیجہ)
{
    صحیح i;
    برائے (i = 0; i < n_chars; ++i)
    {
	اگر (s[i] == 0x0a)
	{
	    *نتیجہ++ = '\0';
	    توڑو;
	}
	ورنہ اگر (s[i] == 0x00)
	{
	    /* Convert embedded 0's to spaces */
	    *نتیجہ++ = ' ';
	}
	ورنہ
	{
	    *نتیجہ++ = s[i];
	}
    }
}

ساکن خالی
decode_display_descriptor (ثابت uchar *desc,
			   MonitorInfo *info)
{
    انتخاب (desc[0x03])
    {
    حالت 0xFC:
	decode_lf_string (desc + 5, 13, info->dsc_حاصل_ضرب_name);
	توڑو;
    حالت 0xFF:
	decode_lf_string (desc + 5, 13, info->dsc_serial_نمبر);
	توڑو;
    حالت 0xFE:
	decode_lf_string (desc + 5, 13, info->dsc_string);
	توڑو;
    حالت 0xFD:
	/* Range Limits */
	توڑو;
    حالت 0xFB:
	/* Color Point */
	توڑو;
    حالت 0xFA:
	/* Timing Identifications */
	توڑو;
    حالت 0xF9:
	/* Color Management */
	توڑو;
    حالت 0xF8:
	/* Timing Codes */
	توڑو;
    حالت 0xF7:
	/* Established Timings */
	توڑو;
    حالت 0x10:
	توڑو;
    }
}

ساکن خالی
decode_detailed_timing (ثابت uchar *timing,
			DetailedTiming *detailed)
{
    صحیح بٹ;
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
    detailed->اونچائی_mm = timing[0x0d] | get_بٹ (timing[0x0e], 0, 3) << 8;
    detailed->دایاں_border = timing[0x0f];
    detailed->چوٹی_border = timing[0x10];

    detailed->interlaced = get_ثنائی_ہندسہ (timing[0x11], 7);

    /* Stereo */
    بٹ = get_بٹ (timing[0x11], 5, 6) << 1 | get_ثنائی_ہندسہ (timing[0x11], 0);
    detailed->stereo = stereo[بٹ];

    /* Sync */
    بٹ = timing[0x11];

    detailed->digital_sync = get_ثنائی_ہندسہ (بٹ, 4);
    اگر (detailed->digital_sync)
    {
	detailed->ad.digital.مرکب = !get_ثنائی_ہندسہ (بٹ, 3);

	اگر (detailed->ad.digital.مرکب)
	{
	    detailed->ad.digital.serrations = get_ثنائی_ہندسہ (بٹ, 2);
	    detailed->ad.digital.negative_vsync = FALSE;
	}
	ورنہ
	{
	    detailed->ad.digital.serrations = FALSE;
	    detailed->ad.digital.negative_vsync = !get_ثنائی_ہندسہ (بٹ, 2);
	}

	detailed->ad.digital.negative_hsync = !get_ثنائی_ہندسہ (بٹ, 0);
    }
    ورنہ
    {
	detailed->ad.analog.bipolar = get_ثنائی_ہندسہ (بٹ, 3);
	detailed->ad.analog.serrations = get_ثنائی_ہندسہ (بٹ, 2);
	detailed->ad.analog.sync_on_green = !get_ثنائی_ہندسہ (بٹ, 1);
    }
}

ساکن صحیح
decode_descriptors (ثابت uchar *edid, MonitorInfo *info)
{
    صحیح i;
    صحیح timing_idx;
    
    timing_idx = 0;
    
    برائے (i = 0; i < 4; ++i)
    {
	صحیح اشاریہ = 0x36 + i * 18;

	اگر (edid[اشاریہ + 0] == 0x00 && edid[اشاریہ + 1] == 0x00)
	{
	    decode_display_descriptor (edid + اشاریہ, info);
	}
	ورنہ
	{
	    decode_detailed_timing (
		edid + اشاریہ, &(info->detailed_timings[timing_idx++]));
	}
    }

    info->n_detailed_timings = timing_idx;

    واپس TRUE;
}

ساکن خالی
decode_check_مجموع (ثابت uchar *edid,
		  MonitorInfo *info)
{
    صحیح i;
    uchar check = 0;

    برائے (i = 0; i < 128; ++i)
	check += edid[i];

    info->checksum = check;
}

ساکن خالی
decode_HDR_metadata_بلاک (ثابت uchar *ڈیٹا, صحیح لمبائی, MonitorInfo *info)
{
    اگر (لمبائی >= 3)
	info->max_luminance = 50.0 * SDL_pow(2, ڈیٹا[2] / 32.0);

    اگر (لمبائی >= 4)
	info->max_چوکھٹا_اوسط_قدر_luminance = 50.0 * SDL_pow(2, ڈیٹا[3] / 32.0);

    اگر (لمبائی >= 5)
	info->min_luminance = 50.0 * SDL_pow(2, ڈیٹا[4] / 32.0);
}


ساکن خالی
decode_cta_بلاک (ثابت uchar *edid,
		  MonitorInfo *info)
{
    صحیح انحراف_2 = 4;
    جب (انحراف_2 < 128) {
	صحیح لمبائی = edid[انحراف_2] & 0x1f;
	صحیح type = edid[انحراف_2] >> 5;
	اگر (لمبائی == 0) {
	    توڑو;
	}
	اگر (type == 7) {
	    type <<= 8;
	    type |= edid[انحراف_2 + 1];
	}
	اگر (type == 0x706) {
	    decode_HDR_metadata_بلاک (&edid[انحراف_2 + 2], لمبائی - 1, info);
	}
	انحراف_2 += (1 + لمبائی);
    }
}

MonitorInfo *
decode_edid (ثابت uchar *edid, size_t سائز)
{
    ثابت صحیح EDID_صفحہ_سائز = 128;
    صحیح عدد_بلاکیں = (سائز / EDID_صفحہ_سائز);
    MonitorInfo *info;

    اگر ((سائز % EDID_صفحہ_سائز) != 0) {
	واپس تہی;
    }

    info = SDL_calloc (1, حجم (MonitorInfo));

    decode_check_مجموع (edid, info);
    
    اگر (!decode_سرخی (edid) ||
        !decode_vendor_and_حاصل_ضرب_identification (edid, info) ||
        !decode_edid_نسخہ (edid, info) ||
        !decode_display_parameters (edid, info) ||
        !decode_color_characteristics (edid, info) ||
        !decode_established_timings (edid, info) ||
        !decode_standard_timings (edid, info) ||
        !decode_descriptors (edid, info)) {
	SDL_free(info);
	واپس تہی;
    }
    
    اگر (عدد_بلاکیں > 1) {
	برائے (صحیح i = 1; i < عدد_بلاکیں; ++i) {
	    صحیح انحراف_2 = i * EDID_صفحہ_سائز;
	    uchar extension = edid[انحراف_2];
	    اگر (extension == 0x02) {
		// CTA-861 Extension Block
		decode_cta_بلاک (&edid[انحراف_2], info);
	    }
	}
    }

    واپس info;
}

ساکن ثابت حرف *
yesno (صحیح v)
{
    واپس v? "yes" : "no";
}

خالی
dump_monitor_info (MonitorInfo *info)
{
    صحیح i;
    
    لکھو ("Checksum: %d (%s)\n",
	    info->checksum, info->checksum? "incorrect" : "correct");
    لکھو ("Manufacturer Code: %s\n", info->manufacturer_رمز);
    لکھو ("Product Code: 0x%x\n", info->حاصل_ضرب_رمز);
    لکھو ("Serial Number: %u\n", info->serial_نمبر);
    
    اگر (info->production_week != -1)
	لکھو ("Production Week: %d\n", info->production_week);
    ورنہ
	لکھو ("Production Week: unspecified\n");
    
    اگر (info->production_year != -1)
	لکھو ("Production Year: %d\n", info->production_year);
    ورنہ
	لکھو ("Production Year: unspecified\n");
    
    اگر (info->model_year != -1)
	لکھو ("Model Year: %d\n", info->model_year);
    ورنہ
	لکھو ("Model Year: unspecified\n");
    
    لکھو ("EDID revision: %d.%d\n", info->major_نسخہ, info->minor_نسخہ);
    
    لکھو ("Display is %s\n", info->is_digital? "digital" : "analog");
    اگر (info->is_digital)
    {
	ثابت حرف *interface;
	اگر (info->ad.digital.بٹ_فی_primary != -1)
	    لکھو ("Bits Per Primary: %d\n", info->ad.digital.بٹ_فی_primary);
	ورنہ
	    لکھو ("Bits Per Primary: undefined\n");
	
	انتخاب (info->ad.digital.interface)
	{
	حالت DVI: interface = "DVI"; توڑو;
	حالت HDMI_A: interface = "HDMI-a"; توڑو;
	حالت HDMI_B: interface = "HDMI-b"; توڑو;
	حالت MDDI: interface = "MDDI"; توڑو;
	حالت DISPLAY_پورٹ: interface = "DisplayPort"; توڑو;
	حالت UNDEFINED: interface = "undefined"; توڑو;
	طےشدہ: interface = "unknown"; توڑو;
	}
	لکھو ("Interface: %s\n", interface);
	
	لکھو ("RGB 4:4:4: %s\n", yesno (info->ad.digital.rgb444));
	لکھو ("YCrCb 4:4:4: %s\n", yesno (info->ad.digital.ycrcb444));
	لکھو ("YCrCb 4:2:2: %s\n", yesno (info->ad.digital.ycrcb422));
    }
    ورنہ
    {
       ثابت حرف *s;
	لکھو ("Video Signal Level: %f\n", info->ad.analog.video_signal_level);
	لکھو ("Sync Signal Level: %f\n", info->ad.analog.sync_signal_level);
	لکھو ("Total Signal Level: %f\n", info->ad.analog.کل_signal_level);
	
	لکھو ("Blank to Black: %s\n",
		yesno (info->ad.analog.blank_مقصد_black));
	لکھو ("Separate HV Sync: %s\n",
		yesno (info->ad.analog.separate_hv_sync));
	لکھو ("Composite Sync on H: %s\n",
		yesno (info->ad.analog.مرکب_sync_on_h));
	لکھو ("Serration on VSync: %s\n",
		yesno (info->ad.analog.serration_on_vsync));
	
	انتخاب (info->ad.analog.color_type)
	{
	حالت UNDEFINED_COLOR: s = "undefined"; توڑو;
	حالت MONOCHROME: s = "monochrome"; توڑو;
	حالت RGB: s = "rgb"; توڑو;
	حالت OTHER_COLOR: s = "other color"; توڑو;
	طےشدہ: s = "unknown"; توڑو;
	}
	
	لکھو ("Color: %s\n", s);
    }
    
    اگر (info->چوڑائی_mm == -1)
	لکھو ("Width: undefined\n");
    ورنہ
	لکھو ("Width: %d mm\n", info->چوڑائی_mm);
    
    اگر (info->اونچائی_mm == -1)
	لکھو ("Height: undefined\n");
    ورنہ
	لکھو ("Height: %d mm\n", info->اونچائی_mm);
    
    اگر (info->aspect_تناسب > 0)
	لکھو ("Aspect Ratio: %f\n", info->aspect_تناسب);
    ورنہ
	لکھو ("Aspect Ratio: undefined\n");
    
    اگر (info->gamma >= 0)
	لکھو ("Gamma: %f\n", info->gamma);
    ورنہ
	لکھو ("Gamma: undefined\n");
    
    لکھو ("Standby: %s\n", yesno (info->standby));
    لکھو ("Suspend: %s\n", yesno (info->suspend));
    لکھو ("Active Off: %s\n", yesno (info->فعال_off));
    
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
    لکھو ("Max frame average luminance %f\n", info->max_چوکھٹا_اوسط_قدر_luminance);
    
    لکھو ("Established Timings:\n");
    
    برائے (i = 0; i < 24; ++i)
    {
	Timing *timing = &(info->established[i]);
	
	اگر (timing->frequency == 0)
	    توڑو;
	
	لکھو ("  %d x %d @ %d Hz\n",
		timing->چوڑائی, timing->اونچائی, timing->frequency);
	
    }
    
    لکھو ("Standard Timings:\n");
    برائے (i = 0; i < 8; ++i)
    {
	Timing *timing = &(info->standard[i]);
	
	اگر (timing->frequency == 0)
	    توڑو;
	
	لکھو ("  %d x %d @ %d Hz\n",
		timing->چوڑائی, timing->اونچائی, timing->frequency);
    }
    
    برائے (i = 0; i < info->n_detailed_timings; ++i)
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
	لکھو ("  Height: %d mm\n", timing->اونچائی_mm);
	لکھو ("  Right Border: %d\n", timing->دایاں_border);
	لکھو ("  Top Border: %d\n", timing->چوٹی_border);
	انتخاب (timing->stereo)
	{
	طےشدہ:
	حالت NO_STEREO:   s = "No Stereo"; توڑو;
	حالت میدان_دایاں: s = "Field Sequential, Right on Sync"; توڑو;
	حالت میدان_بایاں:  s = "Field Sequential, Left on Sync"; توڑو;
	حالت TWO_WAY_دایاں_ON_EVEN: s = "Two-way, Right on Even"; توڑو;
	حالت TWO_WAY_بایاں_ON_EVEN:  s = "Two-way, Left on Even"; توڑو;
	حالت FOUR_WAY_INTERLEAVED:  s = "Four-way Interleaved"; توڑو;
	حالت SIDE_BY_SIDE:          s = "Side-by-Side"; توڑو;
	}
	لکھو ("  Stereo: %s\n", s);
	
	اگر (timing->digital_sync)
	{
	    لکھو ("  Digital Sync:\n");
	    لکھو ("    composite: %s\n", yesno (timing->ad.digital.مرکب));
	    لکھو ("    serrations: %s\n", yesno (timing->ad.digital.serrations));
	    لکھو ("    negative vsync: %s\n",
		    yesno (timing->ad.digital.negative_vsync));
	    لکھو ("    negative hsync: %s\n",
		    yesno (timing->ad.digital.negative_hsync));
	}
	ورنہ
	{
	    لکھو ("  Analog Sync:\n");
	    لکھو ("    bipolar: %s\n", yesno (timing->ad.analog.bipolar));
	    لکھو ("    serrations: %s\n", yesno (timing->ad.analog.serrations));
	    لکھو ("    sync on green: %s\n", yesno (
			timing->ad.analog.sync_on_green));
	}
    }
    
    لکھو ("Detailed Product information:\n");
    لکھو ("  Product Name: %s\n", info->dsc_حاصل_ضرب_name);
    لکھو ("  Serial Number: %s\n", info->dsc_serial_نمبر);
    لکھو ("  Unspecified String: %s\n", info->dsc_string);
}

