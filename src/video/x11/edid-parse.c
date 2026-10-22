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

#تعریف_کن TRUE 1
#تعریف_کن FALSE 0

ساكن صحيح
get_بیت (صحيح درون_2, صحيح بیت)
{
    أرجع (درون_2 & (1 << بیت)) >> بیت;
}

ساكن صحيح
get_بیتها (صحيح درون_2, صحيح begin, صحيح انتها)
{
    صحيح ماسک = (1 << (انتها - begin + 1)) - 1;
    
    أرجع (درون_2 >> begin) & ماسک;
}

ساكن صحيح
decode_سرآیند (ثابت uchar *edid)
{
    إذا (SDL_memcmp (edid, "\x00\xff\xff\xff\xff\xff\xff\x00", 8) == 0)
	أرجع TRUE;
    أرجع FALSE;
}

ساكن صحيح
decode_vendor_and_حاصلضرب_identification (ثابت uchar *edid, MonitorInfo *info)
{
    صحيح is_model_year;
    
    /* Manufacturer Code */
    info->manufacturer_کد[0]  = get_بیتها (edid[0x08], 2, 6);
    info->manufacturer_کد[1]  = get_بیتها (edid[0x08], 0, 1) << 3;
    info->manufacturer_کد[1] |= get_بیتها (edid[0x09], 5, 7);
    info->manufacturer_کد[2]  = get_بیتها (edid[0x09], 0, 4);
    info->manufacturer_کد[3]  = '\0';
    
    info->manufacturer_کد[0] += 'A' - 1;
    info->manufacturer_کد[1] += 'A' - 1;
    info->manufacturer_کد[2] += 'A' - 1;

    /* Product Code */
    info->حاصلضرب_کد = edid[0x0b] << 8 | edid[0x0a];

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
    info->is_digital = get_بیت (edid[0x14], 7);

    إذا (info->is_digital)
    {
	صحيح بیتها;
	
	ساكن ثابت صحيح بیت_عمق_2[8] =
	{
	    -1, 6, 8, 10, 12, 14, 16, -1
	};

	ساكن ثابت Interface interfaces[6] =
	{
	    UNDEFINED, DVI, HDMI_A, HDMI_B, MDDI, DISPLAY_پورت
	};

	بیتها = get_بیتها (edid[0x14], 4, 6);
	info->ad.digital.بیتها_در_هر_primary = بیت_عمق_2[بیتها];

	بیتها = get_بیتها (edid[0x14], 0, 3);
	
	إذا (بیتها <= 5)
	    info->ad.digital.interface = interfaces[بیتها];
	وإلا
	    info->ad.digital.interface = UNDEFINED;
    }
    وإلا
    {
	صحيح بیتها = get_بیتها (edid[0x14], 5, 6);
	
	ساكن ثابت مزدوج سطوح[][3] =
	{
	    { 0.7,   0.3,    1.0 },
	    { 0.714, 0.286,  1.0 },
	    { 1.0,   0.4,    1.4 },
	    { 0.7,   0.0,    0.7 },
	};

	info->ad.analog.video_signal_level = سطوح[بیتها][0];
	info->ad.analog.sync_signal_level = سطوح[بیتها][1];
	info->ad.analog.مجموع_signal_level = سطوح[بیتها][2];

	info->ad.analog.blank_مقصد_black = get_بیت (edid[0x14], 4);

	info->ad.analog.separate_hv_sync = get_بیت (edid[0x14], 3);
	info->ad.analog.مرکب_sync_on_h = get_بیت (edid[0x14], 2);
	info->ad.analog.مرکب_sync_on_green = get_بیت (edid[0x14], 1);

	info->ad.analog.serration_on_vsync = get_بیت (edid[0x14], 0);
    }

    /* Screen Size / Aspect Ratio */
    إذا (edid[0x15] == 0 && edid[0x16] == 0)
    {
	info->عرض_mm = -1;
	info->ارتفاع_mm = -1;
	info->aspect_نسبت = -1.0;
    }
    وإلا إذا (edid[0x16] == 0)
    {
	info->عرض_mm = -1;
	info->ارتفاع_mm = -1; 
	info->aspect_نسبت = 100.0 / (edid[0x15] + 99);
    }
    وإلا إذا (edid[0x15] == 0)
    {
	info->عرض_mm = -1;
	info->ارتفاع_mm = -1;
	info->aspect_نسبت = 100.0 / (edid[0x16] + 99);
	info->aspect_نسبت = 1/info->aspect_نسبت; /* portrait */
    }
    وإلا
    {
	info->عرض_mm = 10 * edid[0x15];
	info->ارتفاع_mm = 10 * edid[0x16];
    }

    /* Gamma */
    إذا (edid[0x17] == 0xFF)
	info->gamma = -1.0;
    وإلا
	info->gamma = (edid[0x17] + 100.0) / 100.0;

    /* Features */
    info->standby = get_بیت (edid[0x18], 7);
    info->suspend = get_بیت (edid[0x18], 6);
    info->فعال_off = get_بیت (edid[0x18], 5);

    إذا (info->is_digital)
    {
	info->ad.digital.rgb444 = TRUE;
	إذا (get_بیت (edid[0x18], 3))
	    info->ad.digital.ycrcb444 = 1;
	إذا (get_بیت (edid[0x18], 4))
	    info->ad.digital.ycrcb422 = 1;
    }
    وإلا
    {
	صحيح بیتها = get_بیتها (edid[0x18], 3, 4);
	ColorType color_type[4] =
	{
	    MONOCHROME, RGB, OTHER_COLOR, UNDEFINED_COLOR
	};

	info->ad.analog.color_type = color_type[بیتها];
    }

    info->srgb_is_standard = get_بیت (edid[0x18], 2);

    /* In 1.3 this is called "has preferred timing" */
    info->preferred_timing_includes_native = get_بیت (edid[0x18], 1);

    /* FIXME: In 1.3 this indicates whether the monitor accepts GTF */
    info->continuous_frequency = get_بیت (edid[0x18], 0);
    أرجع TRUE;
}

ساكن مزدوج
decode_fraction (صحيح بالا, صحيح کم)
{
    مزدوج نتیجه = 0.0;
    صحيح i;

    بالا = (بالا << 2) | کم;

    لكل (i = 0; i < 10; ++i)
	نتیجه += get_بیت (بالا, i) * SDL_pow (2, i - 10);

    أرجع نتیجه;
}

ساكن صحيح
decode_color_characteristics (ثابت uchar *edid, MonitorInfo *info)
{
    info->red_x = decode_fraction (edid[0x1b], get_بیتها (edid[0x19], 6, 7));
    info->red_y = decode_fraction (edid[0x1c], get_بیتها (edid[0x19], 5, 4));
    info->green_x = decode_fraction (edid[0x1d], get_بیتها (edid[0x19], 2, 3));
    info->green_y = decode_fraction (edid[0x1e], get_بیتها (edid[0x19], 0, 1));
    info->blue_x = decode_fraction (edid[0x1f], get_بیتها (edid[0x1a], 6, 7));
    info->blue_y = decode_fraction (edid[0x20], get_بیتها (edid[0x1a], 4, 5));
    info->white_x = decode_fraction (edid[0x21], get_بیتها (edid[0x1a], 2, 3));
    info->white_y = decode_fraction (edid[0x22], get_بیتها (edid[0x1a], 0, 1));

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

	    إذا (get_بیت (byte, j) && established[i][j].frequency != 0)
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
	صحيح اولی = edid[0x26 + 2 * i];
	صحيح دومی = edid[0x27 + 2 * i];

	إذا (اولی != 0x01 && دومی != 0x01)
	{
	    صحيح w = 8 * (اولی + 31);
	    صحيح h = 0;

	    بدل (get_بیتها (دومی, 6, 7))
	    {
	    حالة 0x00: h = (w / 16) * 10; اكسر;
	    حالة 0x01: h = (w / 4) * 3; اكسر;
	    حالة 0x02: h = (w / 5) * 4; اكسر;
	    حالة 0x03: h = (w / 16) * 9; اكسر;
	    }

	    info->standard[i].عرض = w;
	    info->standard[i].ارتفاع = h;
	    info->standard[i].frequency = get_بیتها (دومی, 0, 5) + 60;
	}
    }
    
    أرجع TRUE;
}

ساكن فراغ
decode_lf_string (ثابت uchar *s, صحيح n_chars, حرف *نتیجه)
{
    صحيح i;
    لكل (i = 0; i < n_chars; ++i)
    {
	إذا (s[i] == 0x0a)
	{
	    *نتیجه++ = '\0';
	    اكسر;
	}
	وإلا إذا (s[i] == 0x00)
	{
	    /* Convert embedded 0's to spaces */
	    *نتیجه++ = ' ';
	}
	وإلا
	{
	    *نتیجه++ = s[i];
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
	decode_lf_string (desc + 5, 13, info->dsc_حاصلضرب_name);
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
    صحيح بیتها;
    StereoType stereo[] =
    {
	NO_STEREO, NO_STEREO, فیلد_راست, فیلد_چپ,
	TWO_WAY_راست_ON_EVEN, TWO_WAY_چپ_ON_EVEN,
	FOUR_WAY_INTERLEAVED, SIDE_BY_SIDE
    };
    
    detailed->pixel_clock = (timing[0x00] | timing[0x01] << 8) * 10000;
    detailed->h_addr = timing[0x02] | ((timing[0x04] & 0xf0) << 4);
    detailed->h_blank = timing[0x03] | ((timing[0x04] & 0x0f) << 8);
    detailed->v_addr = timing[0x05] | ((timing[0x07] & 0xf0) << 4);
    detailed->v_blank = timing[0x06] | ((timing[0x07] & 0x0f) << 8);
    detailed->h_front_porch = timing[0x08] | get_بیتها (timing[0x0b], 6, 7) << 8;
    detailed->h_sync = timing[0x09] | get_بیتها (timing[0x0b], 4, 5) << 8;
    detailed->v_front_porch =
	get_بیتها (timing[0x0a], 4, 7) | get_بیتها (timing[0x0b], 2, 3) << 4;
    detailed->v_sync =
	get_بیتها (timing[0x0a], 0, 3) | get_بیتها (timing[0x0b], 0, 1) << 4;
    detailed->عرض_mm =  timing[0x0c] | get_بیتها (timing[0x0e], 4, 7) << 8;
    detailed->ارتفاع_mm = timing[0x0d] | get_بیتها (timing[0x0e], 0, 3) << 8;
    detailed->راست_border = timing[0x0f];
    detailed->بالاترین_border = timing[0x10];

    detailed->interlaced = get_بیت (timing[0x11], 7);

    /* Stereo */
    بیتها = get_بیتها (timing[0x11], 5, 6) << 1 | get_بیت (timing[0x11], 0);
    detailed->stereo = stereo[بیتها];

    /* Sync */
    بیتها = timing[0x11];

    detailed->digital_sync = get_بیت (بیتها, 4);
    إذا (detailed->digital_sync)
    {
	detailed->ad.digital.مرکب = !get_بیت (بیتها, 3);

	إذا (detailed->ad.digital.مرکب)
	{
	    detailed->ad.digital.serrations = get_بیت (بیتها, 2);
	    detailed->ad.digital.negative_vsync = FALSE;
	}
	وإلا
	{
	    detailed->ad.digital.serrations = FALSE;
	    detailed->ad.digital.negative_vsync = !get_بیت (بیتها, 2);
	}

	detailed->ad.digital.negative_hsync = !get_بیت (بیتها, 0);
    }
    وإلا
    {
	detailed->ad.analog.bipolar = get_بیت (بیتها, 3);
	detailed->ad.analog.serrations = get_بیت (بیتها, 2);
	detailed->ad.analog.sync_on_green = !get_بیت (بیتها, 1);
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
decode_check_جمع (ثابت uchar *edid,
		  MonitorInfo *info)
{
    صحيح i;
    uchar check = 0;

    لكل (i = 0; i < 128; ++i)
	check += edid[i];

    info->checksum = check;
}

ساكن فراغ
decode_HDR_metadata_بلوک (ثابت uchar *داده, صحيح درازی, MonitorInfo *info)
{
    إذا (درازی >= 3)
	info->max_luminance = 50.0 * SDL_pow(2, داده[2] / 32.0);

    إذا (درازی >= 4)
	info->max_قاب_معدل_luminance = 50.0 * SDL_pow(2, داده[3] / 32.0);

    إذا (درازی >= 5)
	info->min_luminance = 50.0 * SDL_pow(2, داده[4] / 32.0);
}


ساكن فراغ
decode_cta_بلوک (ثابت uchar *edid,
		  MonitorInfo *info)
{
    صحيح جابه_جایی_2 = 4;
    طالما (جابه_جایی_2 < 128) {
	صحيح درازی = edid[جابه_جایی_2] & 0x1f;
	صحيح type = edid[جابه_جایی_2] >> 5;
	إذا (درازی == 0) {
	    اكسر;
	}
	إذا (type == 7) {
	    type <<= 8;
	    type |= edid[جابه_جایی_2 + 1];
	}
	إذا (type == 0x706) {
	    decode_HDR_metadata_بلوک (&edid[جابه_جایی_2 + 2], درازی - 1, info);
	}
	جابه_جایی_2 += (1 + درازی);
    }
}

MonitorInfo *
decode_edid (ثابت uchar *edid, size_t اندازه)
{
    ثابت صحيح EDID_صفحه_اندازه = 128;
    صحيح رقم_بلوکها = (اندازه / EDID_صفحه_اندازه);
    MonitorInfo *info;

    إذا ((اندازه % EDID_صفحه_اندازه) != 0) {
	أرجع عدم;
    }

    info = SDL_calloc (1, حجم (MonitorInfo));

    decode_check_جمع (edid, info);
    
    إذا (!decode_سرآیند (edid) ||
        !decode_vendor_and_حاصلضرب_identification (edid, info) ||
        !decode_edid_نسخه (edid, info) ||
        !decode_display_parameters (edid, info) ||
        !decode_color_characteristics (edid, info) ||
        !decode_established_timings (edid, info) ||
        !decode_standard_timings (edid, info) ||
        !decode_descriptors (edid, info)) {
	SDL_free(info);
	أرجع عدم;
    }
    
    إذا (رقم_بلوکها > 1) {
	لكل (صحيح i = 1; i < رقم_بلوکها; ++i) {
	    صحيح جابه_جایی_2 = i * EDID_صفحه_اندازه;
	    uchar extension = edid[جابه_جایی_2];
	    إذا (extension == 0x02) {
		// CTA-861 Extension Block
		decode_cta_بلوک (&edid[جابه_جایی_2], info);
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
    
    چاپ_کن ("Checksum: %d (%s)\n",
	    info->checksum, info->checksum? "incorrect" : "correct");
    چاپ_کن ("Manufacturer Code: %s\n", info->manufacturer_کد);
    چاپ_کن ("Product Code: 0x%x\n", info->حاصلضرب_کد);
    چاپ_کن ("Serial Number: %u\n", info->serial_عدد);
    
    إذا (info->production_week != -1)
	چاپ_کن ("Production Week: %d\n", info->production_week);
    وإلا
	چاپ_کن ("Production Week: unspecified\n");
    
    إذا (info->production_year != -1)
	چاپ_کن ("Production Year: %d\n", info->production_year);
    وإلا
	چاپ_کن ("Production Year: unspecified\n");
    
    إذا (info->model_year != -1)
	چاپ_کن ("Model Year: %d\n", info->model_year);
    وإلا
	چاپ_کن ("Model Year: unspecified\n");
    
    چاپ_کن ("EDID revision: %d.%d\n", info->major_نسخه, info->minor_نسخه);
    
    چاپ_کن ("Display is %s\n", info->is_digital? "digital" : "analog");
    إذا (info->is_digital)
    {
	ثابت حرف *interface;
	إذا (info->ad.digital.بیتها_در_هر_primary != -1)
	    چاپ_کن ("Bits Per Primary: %d\n", info->ad.digital.بیتها_در_هر_primary);
	وإلا
	    چاپ_کن ("Bits Per Primary: undefined\n");
	
	بدل (info->ad.digital.interface)
	{
	حالة DVI: interface = "DVI"; اكسر;
	حالة HDMI_A: interface = "HDMI-a"; اكسر;
	حالة HDMI_B: interface = "HDMI-b"; اكسر;
	حالة MDDI: interface = "MDDI"; اكسر;
	حالة DISPLAY_پورت: interface = "DisplayPort"; اكسر;
	حالة UNDEFINED: interface = "undefined"; اكسر;
	افتراضي: interface = "unknown"; اكسر;
	}
	چاپ_کن ("Interface: %s\n", interface);
	
	چاپ_کن ("RGB 4:4:4: %s\n", yesno (info->ad.digital.rgb444));
	چاپ_کن ("YCrCb 4:4:4: %s\n", yesno (info->ad.digital.ycrcb444));
	چاپ_کن ("YCrCb 4:2:2: %s\n", yesno (info->ad.digital.ycrcb422));
    }
    وإلا
    {
       ثابت حرف *s;
	چاپ_کن ("Video Signal Level: %f\n", info->ad.analog.video_signal_level);
	چاپ_کن ("Sync Signal Level: %f\n", info->ad.analog.sync_signal_level);
	چاپ_کن ("Total Signal Level: %f\n", info->ad.analog.مجموع_signal_level);
	
	چاپ_کن ("Blank to Black: %s\n",
		yesno (info->ad.analog.blank_مقصد_black));
	چاپ_کن ("Separate HV Sync: %s\n",
		yesno (info->ad.analog.separate_hv_sync));
	چاپ_کن ("Composite Sync on H: %s\n",
		yesno (info->ad.analog.مرکب_sync_on_h));
	چاپ_کن ("Serration on VSync: %s\n",
		yesno (info->ad.analog.serration_on_vsync));
	
	بدل (info->ad.analog.color_type)
	{
	حالة UNDEFINED_COLOR: s = "undefined"; اكسر;
	حالة MONOCHROME: s = "monochrome"; اكسر;
	حالة RGB: s = "rgb"; اكسر;
	حالة OTHER_COLOR: s = "other color"; اكسر;
	افتراضي: s = "unknown"; اكسر;
	}
	
	چاپ_کن ("Color: %s\n", s);
    }
    
    إذا (info->عرض_mm == -1)
	چاپ_کن ("Width: undefined\n");
    وإلا
	چاپ_کن ("Width: %d mm\n", info->عرض_mm);
    
    إذا (info->ارتفاع_mm == -1)
	چاپ_کن ("Height: undefined\n");
    وإلا
	چاپ_کن ("Height: %d mm\n", info->ارتفاع_mm);
    
    إذا (info->aspect_نسبت > 0)
	چاپ_کن ("Aspect Ratio: %f\n", info->aspect_نسبت);
    وإلا
	چاپ_کن ("Aspect Ratio: undefined\n");
    
    إذا (info->gamma >= 0)
	چاپ_کن ("Gamma: %f\n", info->gamma);
    وإلا
	چاپ_کن ("Gamma: undefined\n");
    
    چاپ_کن ("Standby: %s\n", yesno (info->standby));
    چاپ_کن ("Suspend: %s\n", yesno (info->suspend));
    چاپ_کن ("Active Off: %s\n", yesno (info->فعال_off));
    
    چاپ_کن ("SRGB is Standard: %s\n", yesno (info->srgb_is_standard));
    چاپ_کن ("Preferred Timing Includes Native: %s\n",
	    yesno (info->preferred_timing_includes_native));
    چاپ_کن ("Continuous Frequency: %s\n", yesno (info->continuous_frequency));
    
    چاپ_کن ("Red X: %f\n", info->red_x);
    چاپ_کن ("Red Y: %f\n", info->red_y);
    چاپ_کن ("Green X: %f\n", info->green_x);
    چاپ_کن ("Green Y: %f\n", info->green_y);
    چاپ_کن ("Blue X: %f\n", info->blue_x);
    چاپ_کن ("Blue Y: %f\n", info->blue_y);
    چاپ_کن ("White X: %f\n", info->white_x);
    چاپ_کن ("White Y: %f\n", info->white_y);
    چاپ_کن ("Min luminance: %f\n", info->min_luminance);
    چاپ_کن ("Max luminance: %f\n", info->max_luminance);
    چاپ_کن ("Max frame average luminance %f\n", info->max_قاب_معدل_luminance);
    
    چاپ_کن ("Established Timings:\n");
    
    لكل (i = 0; i < 24; ++i)
    {
	Timing *timing = &(info->established[i]);
	
	إذا (timing->frequency == 0)
	    اكسر;
	
	چاپ_کن ("  %d x %d @ %d Hz\n",
		timing->عرض, timing->ارتفاع, timing->frequency);
	
    }
    
    چاپ_کن ("Standard Timings:\n");
    لكل (i = 0; i < 8; ++i)
    {
	Timing *timing = &(info->standard[i]);
	
	إذا (timing->frequency == 0)
	    اكسر;
	
	چاپ_کن ("  %d x %d @ %d Hz\n",
		timing->عرض, timing->ارتفاع, timing->frequency);
    }
    
    لكل (i = 0; i < info->n_detailed_timings; ++i)
    {
	DetailedTiming *timing = &(info->detailed_timings[i]);
	ثابت حرف *s;
	
	چاپ_کن ("Timing%s: \n",
		(i == 0 && info->preferred_timing_includes_native)?
		" (Preferred)" : "");
	چاپ_کن ("  Pixel Clock: %d\n", timing->pixel_clock);
	چاپ_کن ("  H Addressable: %d\n", timing->h_addr);
	چاپ_کن ("  H Blank: %d\n", timing->h_blank);
	چاپ_کن ("  H Front Porch: %d\n", timing->h_front_porch);
	چاپ_کن ("  H Sync: %d\n", timing->h_sync);
	چاپ_کن ("  V Addressable: %d\n", timing->v_addr);
	چاپ_کن ("  V Blank: %d\n", timing->v_blank);
	چاپ_کن ("  V Front Porch: %d\n", timing->v_front_porch);
	چاپ_کن ("  V Sync: %d\n", timing->v_sync);
	چاپ_کن ("  Width: %d mm\n", timing->عرض_mm);
	چاپ_کن ("  Height: %d mm\n", timing->ارتفاع_mm);
	چاپ_کن ("  Right Border: %d\n", timing->راست_border);
	چاپ_کن ("  Top Border: %d\n", timing->بالاترین_border);
	بدل (timing->stereo)
	{
	افتراضي:
	حالة NO_STEREO:   s = "No Stereo"; اكسر;
	حالة فیلد_راست: s = "Field Sequential, Right on Sync"; اكسر;
	حالة فیلد_چپ:  s = "Field Sequential, Left on Sync"; اكسر;
	حالة TWO_WAY_راست_ON_EVEN: s = "Two-way, Right on Even"; اكسر;
	حالة TWO_WAY_چپ_ON_EVEN:  s = "Two-way, Left on Even"; اكسر;
	حالة FOUR_WAY_INTERLEAVED:  s = "Four-way Interleaved"; اكسر;
	حالة SIDE_BY_SIDE:          s = "Side-by-Side"; اكسر;
	}
	چاپ_کن ("  Stereo: %s\n", s);
	
	إذا (timing->digital_sync)
	{
	    چاپ_کن ("  Digital Sync:\n");
	    چاپ_کن ("    composite: %s\n", yesno (timing->ad.digital.مرکب));
	    چاپ_کن ("    serrations: %s\n", yesno (timing->ad.digital.serrations));
	    چاپ_کن ("    negative vsync: %s\n",
		    yesno (timing->ad.digital.negative_vsync));
	    چاپ_کن ("    negative hsync: %s\n",
		    yesno (timing->ad.digital.negative_hsync));
	}
	وإلا
	{
	    چاپ_کن ("  Analog Sync:\n");
	    چاپ_کن ("    bipolar: %s\n", yesno (timing->ad.analog.bipolar));
	    چاپ_کن ("    serrations: %s\n", yesno (timing->ad.analog.serrations));
	    چاپ_کن ("    sync on green: %s\n", yesno (
			timing->ad.analog.sync_on_green));
	}
    }
    
    چاپ_کن ("Detailed Product information:\n");
    چاپ_کن ("  Product Name: %s\n", info->dsc_حاصلضرب_name);
    چاپ_کن ("  Serial Number: %s\n", info->dsc_serial_عدد);
    چاپ_کن ("  Unspecified String: %s\n", info->dsc_string);
}

