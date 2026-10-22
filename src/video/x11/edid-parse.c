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
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_internal.h"

#ਅਨ੍ਤਰ੍ਭਾਵ "edid.h"
#ਅਨ੍ਤਰ੍ਭਾਵ <stdlib.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <string.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <math.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <stdio.h>

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ TRUE 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ FALSE 0

ਸਥਿਰ ਪੂਰਨ
get_ਦੋਆਧਾਰੀ_ਅੰਕ (ਪੂਰਨ ਵਿੱਚ_2, ਪੂਰਨ ਦੋਆਧਾਰੀ_ਅੰਕ)
{
    ਵਾਪਸ (ਵਿੱਚ_2 & (1 << ਦੋਆਧਾਰੀ_ਅੰਕ)) >> ਦੋਆਧਾਰੀ_ਅੰਕ;
}

ਸਥਿਰ ਪੂਰਨ
get_ਬਿੱਟ (ਪੂਰਨ ਵਿੱਚ_2, ਪੂਰਨ begin, ਪੂਰਨ ਸਿਰਾ)
{
    ਪੂਰਨ ਨਕਾਬ = (1 << (ਸਿਰਾ - begin + 1)) - 1;
    
    ਵਾਪਸ (ਵਿੱਚ_2 >> begin) & ਨਕਾਬ;
}

ਸਥਿਰ ਪੂਰਨ
decode_ਸਿਰਲੇਖ (ਅਚਲ uchar *edid)
{
    ਜੇ (SDL_memcmp (edid, "\x00\xff\xff\xff\xff\xff\xff\x00", 8) == 0)
	ਵਾਪਸ TRUE;
    ਵਾਪਸ FALSE;
}

ਸਥਿਰ ਪੂਰਨ
decode_vendor_and_ਗੁਣਨਫਲ_identification (ਅਚਲ uchar *edid, MonitorInfo *info)
{
    ਪੂਰਨ is_model_year;
    
    /* Manufacturer Code */
    info->manufacturer_ਕੋਡ[0]  = get_ਬਿੱਟ (edid[0x08], 2, 6);
    info->manufacturer_ਕੋਡ[1]  = get_ਬਿੱਟ (edid[0x08], 0, 1) << 3;
    info->manufacturer_ਕੋਡ[1] |= get_ਬਿੱਟ (edid[0x09], 5, 7);
    info->manufacturer_ਕੋਡ[2]  = get_ਬਿੱਟ (edid[0x09], 0, 4);
    info->manufacturer_ਕੋਡ[3]  = '\0';
    
    info->manufacturer_ਕੋਡ[0] += 'A' - 1;
    info->manufacturer_ਕੋਡ[1] += 'A' - 1;
    info->manufacturer_ਕੋਡ[2] += 'A' - 1;

    /* Product Code */
    info->ਗੁਣਨਫਲ_ਕੋਡ = edid[0x0b] << 8 | edid[0x0a];

    /* Serial Number */
    info->serial_ਸੰਖਿਆ =
	edid[0x0c] | edid[0x0d] << 8 | edid[0x0e] << 16 | (Uint32)edid[0x0f] << 24;

    /* Week and Year */
    is_model_year = FALSE;
    ਚੋਣ (edid[0x10])
    {
    ਹਾਲਤ 0x00:
	info->production_week = -1;
	ਰੋਕੋ;

    ਹਾਲਤ 0xff:
	info->production_week = -1;
	is_model_year = TRUE;
	ਰੋਕੋ;

    ਮੂਲ:
	info->production_week = edid[0x10];
	ਰੋਕੋ;
    }

    ਜੇ (is_model_year)
    {
	info->production_year = -1;
	info->model_year = 1990 + edid[0x11];
    }
    ਨਹੀਂਤਾਂ
    {
	info->production_year = 1990 + edid[0x11];
	info->model_year = -1;
    }

    ਵਾਪਸ TRUE;
}

ਸਥਿਰ ਪੂਰਨ
decode_edid_ਸੰਸਕਰਣ (ਅਚਲ uchar *edid, MonitorInfo *info)
{
    info->major_ਸੰਸਕਰਣ = edid[0x12];
    info->minor_ਸੰਸਕਰਣ = edid[0x13];

    ਵਾਪਸ TRUE;
}

ਸਥਿਰ ਪੂਰਨ
decode_display_parameters (ਅਚਲ uchar *edid, MonitorInfo *info)
{
    /* Digital vs Analog */
    info->is_digital = get_ਦੋਆਧਾਰੀ_ਅੰਕ (edid[0x14], 7);

    ਜੇ (info->is_digital)
    {
	ਪੂਰਨ ਬਿੱਟ;
	
	ਸਥਿਰ ਅਚਲ ਪੂਰਨ ਦੋਆਧਾਰੀ_ਅੰਕ_ਡੂੰਘਾਈ_2[8] =
	{
	    -1, 6, 8, 10, 12, 14, 16, -1
	};

	ਸਥਿਰ ਅਚਲ Interface interfaces[6] =
	{
	    UNDEFINED, DVI, HDMI_A, HDMI_B, MDDI, DISPLAY_ਪੋਰਟ
	};

	ਬਿੱਟ = get_ਬਿੱਟ (edid[0x14], 4, 6);
	info->ad.digital.ਬਿੱਟ_ਪ੍ਰਤੀ_primary = ਦੋਆਧਾਰੀ_ਅੰਕ_ਡੂੰਘਾਈ_2[ਬਿੱਟ];

	ਬਿੱਟ = get_ਬਿੱਟ (edid[0x14], 0, 3);
	
	ਜੇ (ਬਿੱਟ <= 5)
	    info->ad.digital.interface = interfaces[ਬਿੱਟ];
	ਨਹੀਂਤਾਂ
	    info->ad.digital.interface = UNDEFINED;
    }
    ਨਹੀਂਤਾਂ
    {
	ਪੂਰਨ ਬਿੱਟ = get_ਬਿੱਟ (edid[0x14], 5, 6);
	
	ਸਥਿਰ ਅਚਲ ਦੁੱਗਣਾ ਪੱਧਰ[][3] =
	{
	    { 0.7,   0.3,    1.0 },
	    { 0.714, 0.286,  1.0 },
	    { 1.0,   0.4,    1.4 },
	    { 0.7,   0.0,    0.7 },
	};

	info->ad.analog.video_signal_level = ਪੱਧਰ[ਬਿੱਟ][0];
	info->ad.analog.sync_signal_level = ਪੱਧਰ[ਬਿੱਟ][1];
	info->ad.analog.ਕੁੱਲ_signal_level = ਪੱਧਰ[ਬਿੱਟ][2];

	info->ad.analog.blank_ਮੰਜ਼ਿਲ_black = get_ਦੋਆਧਾਰੀ_ਅੰਕ (edid[0x14], 4);

	info->ad.analog.separate_hv_sync = get_ਦੋਆਧਾਰੀ_ਅੰਕ (edid[0x14], 3);
	info->ad.analog.ਸੰਯੁਕਤ_sync_on_h = get_ਦੋਆਧਾਰੀ_ਅੰਕ (edid[0x14], 2);
	info->ad.analog.ਸੰਯੁਕਤ_sync_on_green = get_ਦੋਆਧਾਰੀ_ਅੰਕ (edid[0x14], 1);

	info->ad.analog.serration_on_vsync = get_ਦੋਆਧਾਰੀ_ਅੰਕ (edid[0x14], 0);
    }

    /* Screen Size / Aspect Ratio */
    ਜੇ (edid[0x15] == 0 && edid[0x16] == 0)
    {
	info->ਚੌੜਾਈ_mm = -1;
	info->ਉਚਾਈ_mm = -1;
	info->aspect_ਅਨੁਪਾਤ = -1.0;
    }
    ਨਹੀਂਤਾਂ ਜੇ (edid[0x16] == 0)
    {
	info->ਚੌੜਾਈ_mm = -1;
	info->ਉਚਾਈ_mm = -1; 
	info->aspect_ਅਨੁਪਾਤ = 100.0 / (edid[0x15] + 99);
    }
    ਨਹੀਂਤਾਂ ਜੇ (edid[0x15] == 0)
    {
	info->ਚੌੜਾਈ_mm = -1;
	info->ਉਚਾਈ_mm = -1;
	info->aspect_ਅਨੁਪਾਤ = 100.0 / (edid[0x16] + 99);
	info->aspect_ਅਨੁਪਾਤ = 1/info->aspect_ਅਨੁਪਾਤ; /* portrait */
    }
    ਨਹੀਂਤਾਂ
    {
	info->ਚੌੜਾਈ_mm = 10 * edid[0x15];
	info->ਉਚਾਈ_mm = 10 * edid[0x16];
    }

    /* Gamma */
    ਜੇ (edid[0x17] == 0xFF)
	info->gamma = -1.0;
    ਨਹੀਂਤਾਂ
	info->gamma = (edid[0x17] + 100.0) / 100.0;

    /* Features */
    info->standby = get_ਦੋਆਧਾਰੀ_ਅੰਕ (edid[0x18], 7);
    info->suspend = get_ਦੋਆਧਾਰੀ_ਅੰਕ (edid[0x18], 6);
    info->ਸਰਗਰਮ_off = get_ਦੋਆਧਾਰੀ_ਅੰਕ (edid[0x18], 5);

    ਜੇ (info->is_digital)
    {
	info->ad.digital.rgb444 = TRUE;
	ਜੇ (get_ਦੋਆਧਾਰੀ_ਅੰਕ (edid[0x18], 3))
	    info->ad.digital.ycrcb444 = 1;
	ਜੇ (get_ਦੋਆਧਾਰੀ_ਅੰਕ (edid[0x18], 4))
	    info->ad.digital.ycrcb422 = 1;
    }
    ਨਹੀਂਤਾਂ
    {
	ਪੂਰਨ ਬਿੱਟ = get_ਬਿੱਟ (edid[0x18], 3, 4);
	ColorType color_type[4] =
	{
	    MONOCHROME, RGB, OTHER_COLOR, UNDEFINED_COLOR
	};

	info->ad.analog.color_type = color_type[ਬਿੱਟ];
    }

    info->srgb_is_standard = get_ਦੋਆਧਾਰੀ_ਅੰਕ (edid[0x18], 2);

    /* In 1.3 this is called "has preferred timing" */
    info->preferred_timing_includes_native = get_ਦੋਆਧਾਰੀ_ਅੰਕ (edid[0x18], 1);

    /* FIXME: In 1.3 this indicates whether the monitor accepts GTF */
    info->continuous_frequency = get_ਦੋਆਧਾਰੀ_ਅੰਕ (edid[0x18], 0);
    ਵਾਪਸ TRUE;
}

ਸਥਿਰ ਦੁੱਗਣਾ
decode_fraction (ਪੂਰਨ ਉੱਚਾ, ਪੂਰਨ ਨੀਵਾਂ)
{
    ਦੁੱਗਣਾ ਨਤੀਜਾ = 0.0;
    ਪੂਰਨ i;

    ਉੱਚਾ = (ਉੱਚਾ << 2) | ਨੀਵਾਂ;

    ਲਈ (i = 0; i < 10; ++i)
	ਨਤੀਜਾ += get_ਦੋਆਧਾਰੀ_ਅੰਕ (ਉੱਚਾ, i) * SDL_pow (2, i - 10);

    ਵਾਪਸ ਨਤੀਜਾ;
}

ਸਥਿਰ ਪੂਰਨ
decode_color_characteristics (ਅਚਲ uchar *edid, MonitorInfo *info)
{
    info->red_x = decode_fraction (edid[0x1b], get_ਬਿੱਟ (edid[0x19], 6, 7));
    info->red_y = decode_fraction (edid[0x1c], get_ਬਿੱਟ (edid[0x19], 5, 4));
    info->green_x = decode_fraction (edid[0x1d], get_ਬਿੱਟ (edid[0x19], 2, 3));
    info->green_y = decode_fraction (edid[0x1e], get_ਬਿੱਟ (edid[0x19], 0, 1));
    info->blue_x = decode_fraction (edid[0x1f], get_ਬਿੱਟ (edid[0x1a], 6, 7));
    info->blue_y = decode_fraction (edid[0x20], get_ਬਿੱਟ (edid[0x1a], 4, 5));
    info->white_x = decode_fraction (edid[0x21], get_ਬਿੱਟ (edid[0x1a], 2, 3));
    info->white_y = decode_fraction (edid[0x22], get_ਬਿੱਟ (edid[0x1a], 0, 1));

    ਵਾਪਸ TRUE;
}

ਸਥਿਰ ਪੂਰਨ
decode_established_timings (ਅਚਲ uchar *edid, MonitorInfo *info)
{
    ਸਥਿਰ ਅਚਲ Timing established[][8] = 
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

    ਪੂਰਨ i, j, idx;

    idx = 0;
    ਲਈ (i = 0; i < 3; ++i)
    {
	ਲਈ (j = 0; j < 8; ++j)
	{
	    ਪੂਰਨ byte = edid[0x23 + i];

	    ਜੇ (get_ਦੋਆਧਾਰੀ_ਅੰਕ (byte, j) && established[i][j].frequency != 0)
		info->established[idx++] = established[i][j];
	}
    }
    ਵਾਪਸ TRUE;
}

ਸਥਿਰ ਪੂਰਨ
decode_standard_timings (ਅਚਲ uchar *edid, MonitorInfo *info)
{
    ਪੂਰਨ i;
    
    ਲਈ (i = 0; i < 8; i++)
    {
	ਪੂਰਨ ਪਹਿਲਾ = edid[0x26 + 2 * i];
	ਪੂਰਨ ਦੂਜਾ = edid[0x27 + 2 * i];

	ਜੇ (ਪਹਿਲਾ != 0x01 && ਦੂਜਾ != 0x01)
	{
	    ਪੂਰਨ w = 8 * (ਪਹਿਲਾ + 31);
	    ਪੂਰਨ h = 0;

	    ਚੋਣ (get_ਬਿੱਟ (ਦੂਜਾ, 6, 7))
	    {
	    ਹਾਲਤ 0x00: h = (w / 16) * 10; ਰੋਕੋ;
	    ਹਾਲਤ 0x01: h = (w / 4) * 3; ਰੋਕੋ;
	    ਹਾਲਤ 0x02: h = (w / 5) * 4; ਰੋਕੋ;
	    ਹਾਲਤ 0x03: h = (w / 16) * 9; ਰੋਕੋ;
	    }

	    info->standard[i].ਚੌੜਾਈ = w;
	    info->standard[i].ਉਚਾਈ = h;
	    info->standard[i].frequency = get_ਬਿੱਟ (ਦੂਜਾ, 0, 5) + 60;
	}
    }
    
    ਵਾਪਸ TRUE;
}

ਸਥਿਰ ਖਾਲੀ
decode_lf_string (ਅਚਲ uchar *s, ਪੂਰਨ n_chars, ਅੱਖਰ *ਨਤੀਜਾ)
{
    ਪੂਰਨ i;
    ਲਈ (i = 0; i < n_chars; ++i)
    {
	ਜੇ (s[i] == 0x0a)
	{
	    *ਨਤੀਜਾ++ = '\0';
	    ਰੋਕੋ;
	}
	ਨਹੀਂਤਾਂ ਜੇ (s[i] == 0x00)
	{
	    /* Convert embedded 0's to spaces */
	    *ਨਤੀਜਾ++ = ' ';
	}
	ਨਹੀਂਤਾਂ
	{
	    *ਨਤੀਜਾ++ = s[i];
	}
    }
}

ਸਥਿਰ ਖਾਲੀ
decode_display_descriptor (ਅਚਲ uchar *desc,
			   MonitorInfo *info)
{
    ਚੋਣ (desc[0x03])
    {
    ਹਾਲਤ 0xFC:
	decode_lf_string (desc + 5, 13, info->dsc_ਗੁਣਨਫਲ_name);
	ਰੋਕੋ;
    ਹਾਲਤ 0xFF:
	decode_lf_string (desc + 5, 13, info->dsc_serial_ਸੰਖਿਆ);
	ਰੋਕੋ;
    ਹਾਲਤ 0xFE:
	decode_lf_string (desc + 5, 13, info->dsc_string);
	ਰੋਕੋ;
    ਹਾਲਤ 0xFD:
	/* Range Limits */
	ਰੋਕੋ;
    ਹਾਲਤ 0xFB:
	/* Color Point */
	ਰੋਕੋ;
    ਹਾਲਤ 0xFA:
	/* Timing Identifications */
	ਰੋਕੋ;
    ਹਾਲਤ 0xF9:
	/* Color Management */
	ਰੋਕੋ;
    ਹਾਲਤ 0xF8:
	/* Timing Codes */
	ਰੋਕੋ;
    ਹਾਲਤ 0xF7:
	/* Established Timings */
	ਰੋਕੋ;
    ਹਾਲਤ 0x10:
	ਰੋਕੋ;
    }
}

ਸਥਿਰ ਖਾਲੀ
decode_detailed_timing (ਅਚਲ uchar *timing,
			DetailedTiming *detailed)
{
    ਪੂਰਨ ਬਿੱਟ;
    StereoType stereo[] =
    {
	NO_STEREO, NO_STEREO, ਖੇਤਰ_ਸੱਜਾ, ਖੇਤਰ_ਖੱਬਾ,
	TWO_WAY_ਸੱਜਾ_ON_EVEN, TWO_WAY_ਖੱਬਾ_ON_EVEN,
	FOUR_WAY_INTERLEAVED, SIDE_BY_SIDE
    };
    
    detailed->pixel_clock = (timing[0x00] | timing[0x01] << 8) * 10000;
    detailed->h_addr = timing[0x02] | ((timing[0x04] & 0xf0) << 4);
    detailed->h_blank = timing[0x03] | ((timing[0x04] & 0x0f) << 8);
    detailed->v_addr = timing[0x05] | ((timing[0x07] & 0xf0) << 4);
    detailed->v_blank = timing[0x06] | ((timing[0x07] & 0x0f) << 8);
    detailed->h_front_porch = timing[0x08] | get_ਬਿੱਟ (timing[0x0b], 6, 7) << 8;
    detailed->h_sync = timing[0x09] | get_ਬਿੱਟ (timing[0x0b], 4, 5) << 8;
    detailed->v_front_porch =
	get_ਬਿੱਟ (timing[0x0a], 4, 7) | get_ਬਿੱਟ (timing[0x0b], 2, 3) << 4;
    detailed->v_sync =
	get_ਬਿੱਟ (timing[0x0a], 0, 3) | get_ਬਿੱਟ (timing[0x0b], 0, 1) << 4;
    detailed->ਚੌੜਾਈ_mm =  timing[0x0c] | get_ਬਿੱਟ (timing[0x0e], 4, 7) << 8;
    detailed->ਉਚਾਈ_mm = timing[0x0d] | get_ਬਿੱਟ (timing[0x0e], 0, 3) << 8;
    detailed->ਸੱਜਾ_border = timing[0x0f];
    detailed->ਸਿਖਰ_border = timing[0x10];

    detailed->interlaced = get_ਦੋਆਧਾਰੀ_ਅੰਕ (timing[0x11], 7);

    /* Stereo */
    ਬਿੱਟ = get_ਬਿੱਟ (timing[0x11], 5, 6) << 1 | get_ਦੋਆਧਾਰੀ_ਅੰਕ (timing[0x11], 0);
    detailed->stereo = stereo[ਬਿੱਟ];

    /* Sync */
    ਬਿੱਟ = timing[0x11];

    detailed->digital_sync = get_ਦੋਆਧਾਰੀ_ਅੰਕ (ਬਿੱਟ, 4);
    ਜੇ (detailed->digital_sync)
    {
	detailed->ad.digital.ਸੰਯੁਕਤ = !get_ਦੋਆਧਾਰੀ_ਅੰਕ (ਬਿੱਟ, 3);

	ਜੇ (detailed->ad.digital.ਸੰਯੁਕਤ)
	{
	    detailed->ad.digital.serrations = get_ਦੋਆਧਾਰੀ_ਅੰਕ (ਬਿੱਟ, 2);
	    detailed->ad.digital.negative_vsync = FALSE;
	}
	ਨਹੀਂਤਾਂ
	{
	    detailed->ad.digital.serrations = FALSE;
	    detailed->ad.digital.negative_vsync = !get_ਦੋਆਧਾਰੀ_ਅੰਕ (ਬਿੱਟ, 2);
	}

	detailed->ad.digital.negative_hsync = !get_ਦੋਆਧਾਰੀ_ਅੰਕ (ਬਿੱਟ, 0);
    }
    ਨਹੀਂਤਾਂ
    {
	detailed->ad.analog.bipolar = get_ਦੋਆਧਾਰੀ_ਅੰਕ (ਬਿੱਟ, 3);
	detailed->ad.analog.serrations = get_ਦੋਆਧਾਰੀ_ਅੰਕ (ਬਿੱਟ, 2);
	detailed->ad.analog.sync_on_green = !get_ਦੋਆਧਾਰੀ_ਅੰਕ (ਬਿੱਟ, 1);
    }
}

ਸਥਿਰ ਪੂਰਨ
decode_descriptors (ਅਚਲ uchar *edid, MonitorInfo *info)
{
    ਪੂਰਨ i;
    ਪੂਰਨ timing_idx;
    
    timing_idx = 0;
    
    ਲਈ (i = 0; i < 4; ++i)
    {
	ਪੂਰਨ ਸੂਚਕਾਂਕ = 0x36 + i * 18;

	ਜੇ (edid[ਸੂਚਕਾਂਕ + 0] == 0x00 && edid[ਸੂਚਕਾਂਕ + 1] == 0x00)
	{
	    decode_display_descriptor (edid + ਸੂਚਕਾਂਕ, info);
	}
	ਨਹੀਂਤਾਂ
	{
	    decode_detailed_timing (
		edid + ਸੂਚਕਾਂਕ, &(info->detailed_timings[timing_idx++]));
	}
    }

    info->n_detailed_timings = timing_idx;

    ਵਾਪਸ TRUE;
}

ਸਥਿਰ ਖਾਲੀ
decode_check_ਜੋੜ (ਅਚਲ uchar *edid,
		  MonitorInfo *info)
{
    ਪੂਰਨ i;
    uchar check = 0;

    ਲਈ (i = 0; i < 128; ++i)
	check += edid[i];

    info->checksum = check;
}

ਸਥਿਰ ਖਾਲੀ
decode_HDR_metadata_ਖੰਡ (ਅਚਲ uchar *ਅੰਕੜੇ, ਪੂਰਨ ਲੰਮਾਈ, MonitorInfo *info)
{
    ਜੇ (ਲੰਮਾਈ >= 3)
	info->max_luminance = 50.0 * SDL_pow(2, ਅੰਕੜੇ[2] / 32.0);

    ਜੇ (ਲੰਮਾਈ >= 4)
	info->max_ਚੌਖਟਾ_ਔਸਤਨ_luminance = 50.0 * SDL_pow(2, ਅੰਕੜੇ[3] / 32.0);

    ਜੇ (ਲੰਮਾਈ >= 5)
	info->min_luminance = 50.0 * SDL_pow(2, ਅੰਕੜੇ[4] / 32.0);
}


ਸਥਿਰ ਖਾਲੀ
decode_cta_ਖੰਡ (ਅਚਲ uchar *edid,
		  MonitorInfo *info)
{
    ਪੂਰਨ ਵਿੱਥ_2 = 4;
    ਜਦੋਂ (ਵਿੱਥ_2 < 128) {
	ਪੂਰਨ ਲੰਮਾਈ = edid[ਵਿੱਥ_2] & 0x1f;
	ਪੂਰਨ type = edid[ਵਿੱਥ_2] >> 5;
	ਜੇ (ਲੰਮਾਈ == 0) {
	    ਰੋਕੋ;
	}
	ਜੇ (type == 7) {
	    type <<= 8;
	    type |= edid[ਵਿੱਥ_2 + 1];
	}
	ਜੇ (type == 0x706) {
	    decode_HDR_metadata_ਖੰਡ (&edid[ਵਿੱਥ_2 + 2], ਲੰਮਾਈ - 1, info);
	}
	ਵਿੱਥ_2 += (1 + ਲੰਮਾਈ);
    }
}

MonitorInfo *
decode_edid (ਅਚਲ uchar *edid, size_t ਮਾਪ)
{
    ਅਚਲ ਪੂਰਨ EDID_ਪੰਨਾ_ਮਾਪ = 128;
    ਪੂਰਨ ਅੰਕ_ਖੰਡਾਂ = (ਮਾਪ / EDID_ਪੰਨਾ_ਮਾਪ);
    MonitorInfo *info;

    ਜੇ ((ਮਾਪ % EDID_ਪੰਨਾ_ਮਾਪ) != 0) {
	ਵਾਪਸ ਨਿਰਾ;
    }

    info = SDL_calloc (1, ਆਕਾਰ (MonitorInfo));

    decode_check_ਜੋੜ (edid, info);
    
    ਜੇ (!decode_ਸਿਰਲੇਖ (edid) ||
        !decode_vendor_and_ਗੁਣਨਫਲ_identification (edid, info) ||
        !decode_edid_ਸੰਸਕਰਣ (edid, info) ||
        !decode_display_parameters (edid, info) ||
        !decode_color_characteristics (edid, info) ||
        !decode_established_timings (edid, info) ||
        !decode_standard_timings (edid, info) ||
        !decode_descriptors (edid, info)) {
	SDL_free(info);
	ਵਾਪਸ ਨਿਰਾ;
    }
    
    ਜੇ (ਅੰਕ_ਖੰਡਾਂ > 1) {
	ਲਈ (ਪੂਰਨ i = 1; i < ਅੰਕ_ਖੰਡਾਂ; ++i) {
	    ਪੂਰਨ ਵਿੱਥ_2 = i * EDID_ਪੰਨਾ_ਮਾਪ;
	    uchar extension = edid[ਵਿੱਥ_2];
	    ਜੇ (extension == 0x02) {
		// CTA-861 Extension Block
		decode_cta_ਖੰਡ (&edid[ਵਿੱਥ_2], info);
	    }
	}
    }

    ਵਾਪਸ info;
}

ਸਥਿਰ ਅਚਲ ਅੱਖਰ *
yesno (ਪੂਰਨ v)
{
    ਵਾਪਸ v? "yes" : "no";
}

ਖਾਲੀ
dump_monitor_info (MonitorInfo *info)
{
    ਪੂਰਨ i;
    
    ਲਿਖੋ ("Checksum: %d (%s)\n",
	    info->checksum, info->checksum? "incorrect" : "correct");
    ਲਿਖੋ ("Manufacturer Code: %s\n", info->manufacturer_ਕੋਡ);
    ਲਿਖੋ ("Product Code: 0x%x\n", info->ਗੁਣਨਫਲ_ਕੋਡ);
    ਲਿਖੋ ("Serial Number: %u\n", info->serial_ਸੰਖਿਆ);
    
    ਜੇ (info->production_week != -1)
	ਲਿਖੋ ("Production Week: %d\n", info->production_week);
    ਨਹੀਂਤਾਂ
	ਲਿਖੋ ("Production Week: unspecified\n");
    
    ਜੇ (info->production_year != -1)
	ਲਿਖੋ ("Production Year: %d\n", info->production_year);
    ਨਹੀਂਤਾਂ
	ਲਿਖੋ ("Production Year: unspecified\n");
    
    ਜੇ (info->model_year != -1)
	ਲਿਖੋ ("Model Year: %d\n", info->model_year);
    ਨਹੀਂਤਾਂ
	ਲਿਖੋ ("Model Year: unspecified\n");
    
    ਲਿਖੋ ("EDID revision: %d.%d\n", info->major_ਸੰਸਕਰਣ, info->minor_ਸੰਸਕਰਣ);
    
    ਲਿਖੋ ("Display is %s\n", info->is_digital? "digital" : "analog");
    ਜੇ (info->is_digital)
    {
	ਅਚਲ ਅੱਖਰ *interface;
	ਜੇ (info->ad.digital.ਬਿੱਟ_ਪ੍ਰਤੀ_primary != -1)
	    ਲਿਖੋ ("Bits Per Primary: %d\n", info->ad.digital.ਬਿੱਟ_ਪ੍ਰਤੀ_primary);
	ਨਹੀਂਤਾਂ
	    ਲਿਖੋ ("Bits Per Primary: undefined\n");
	
	ਚੋਣ (info->ad.digital.interface)
	{
	ਹਾਲਤ DVI: interface = "DVI"; ਰੋਕੋ;
	ਹਾਲਤ HDMI_A: interface = "HDMI-a"; ਰੋਕੋ;
	ਹਾਲਤ HDMI_B: interface = "HDMI-b"; ਰੋਕੋ;
	ਹਾਲਤ MDDI: interface = "MDDI"; ਰੋਕੋ;
	ਹਾਲਤ DISPLAY_ਪੋਰਟ: interface = "DisplayPort"; ਰੋਕੋ;
	ਹਾਲਤ UNDEFINED: interface = "undefined"; ਰੋਕੋ;
	ਮੂਲ: interface = "unknown"; ਰੋਕੋ;
	}
	ਲਿਖੋ ("Interface: %s\n", interface);
	
	ਲਿਖੋ ("RGB 4:4:4: %s\n", yesno (info->ad.digital.rgb444));
	ਲਿਖੋ ("YCrCb 4:4:4: %s\n", yesno (info->ad.digital.ycrcb444));
	ਲਿਖੋ ("YCrCb 4:2:2: %s\n", yesno (info->ad.digital.ycrcb422));
    }
    ਨਹੀਂਤਾਂ
    {
       ਅਚਲ ਅੱਖਰ *s;
	ਲਿਖੋ ("Video Signal Level: %f\n", info->ad.analog.video_signal_level);
	ਲਿਖੋ ("Sync Signal Level: %f\n", info->ad.analog.sync_signal_level);
	ਲਿਖੋ ("Total Signal Level: %f\n", info->ad.analog.ਕੁੱਲ_signal_level);
	
	ਲਿਖੋ ("Blank to Black: %s\n",
		yesno (info->ad.analog.blank_ਮੰਜ਼ਿਲ_black));
	ਲਿਖੋ ("Separate HV Sync: %s\n",
		yesno (info->ad.analog.separate_hv_sync));
	ਲਿਖੋ ("Composite Sync on H: %s\n",
		yesno (info->ad.analog.ਸੰਯੁਕਤ_sync_on_h));
	ਲਿਖੋ ("Serration on VSync: %s\n",
		yesno (info->ad.analog.serration_on_vsync));
	
	ਚੋਣ (info->ad.analog.color_type)
	{
	ਹਾਲਤ UNDEFINED_COLOR: s = "undefined"; ਰੋਕੋ;
	ਹਾਲਤ MONOCHROME: s = "monochrome"; ਰੋਕੋ;
	ਹਾਲਤ RGB: s = "rgb"; ਰੋਕੋ;
	ਹਾਲਤ OTHER_COLOR: s = "other color"; ਰੋਕੋ;
	ਮੂਲ: s = "unknown"; ਰੋਕੋ;
	}
	
	ਲਿਖੋ ("Color: %s\n", s);
    }
    
    ਜੇ (info->ਚੌੜਾਈ_mm == -1)
	ਲਿਖੋ ("Width: undefined\n");
    ਨਹੀਂਤਾਂ
	ਲਿਖੋ ("Width: %d mm\n", info->ਚੌੜਾਈ_mm);
    
    ਜੇ (info->ਉਚਾਈ_mm == -1)
	ਲਿਖੋ ("Height: undefined\n");
    ਨਹੀਂਤਾਂ
	ਲਿਖੋ ("Height: %d mm\n", info->ਉਚਾਈ_mm);
    
    ਜੇ (info->aspect_ਅਨੁਪਾਤ > 0)
	ਲਿਖੋ ("Aspect Ratio: %f\n", info->aspect_ਅਨੁਪਾਤ);
    ਨਹੀਂਤਾਂ
	ਲਿਖੋ ("Aspect Ratio: undefined\n");
    
    ਜੇ (info->gamma >= 0)
	ਲਿਖੋ ("Gamma: %f\n", info->gamma);
    ਨਹੀਂਤਾਂ
	ਲਿਖੋ ("Gamma: undefined\n");
    
    ਲਿਖੋ ("Standby: %s\n", yesno (info->standby));
    ਲਿਖੋ ("Suspend: %s\n", yesno (info->suspend));
    ਲਿਖੋ ("Active Off: %s\n", yesno (info->ਸਰਗਰਮ_off));
    
    ਲਿਖੋ ("SRGB is Standard: %s\n", yesno (info->srgb_is_standard));
    ਲਿਖੋ ("Preferred Timing Includes Native: %s\n",
	    yesno (info->preferred_timing_includes_native));
    ਲਿਖੋ ("Continuous Frequency: %s\n", yesno (info->continuous_frequency));
    
    ਲਿਖੋ ("Red X: %f\n", info->red_x);
    ਲਿਖੋ ("Red Y: %f\n", info->red_y);
    ਲਿਖੋ ("Green X: %f\n", info->green_x);
    ਲਿਖੋ ("Green Y: %f\n", info->green_y);
    ਲਿਖੋ ("Blue X: %f\n", info->blue_x);
    ਲਿਖੋ ("Blue Y: %f\n", info->blue_y);
    ਲਿਖੋ ("White X: %f\n", info->white_x);
    ਲਿਖੋ ("White Y: %f\n", info->white_y);
    ਲਿਖੋ ("Min luminance: %f\n", info->min_luminance);
    ਲਿਖੋ ("Max luminance: %f\n", info->max_luminance);
    ਲਿਖੋ ("Max frame average luminance %f\n", info->max_ਚੌਖਟਾ_ਔਸਤਨ_luminance);
    
    ਲਿਖੋ ("Established Timings:\n");
    
    ਲਈ (i = 0; i < 24; ++i)
    {
	Timing *timing = &(info->established[i]);
	
	ਜੇ (timing->frequency == 0)
	    ਰੋਕੋ;
	
	ਲਿਖੋ ("  %d x %d @ %d Hz\n",
		timing->ਚੌੜਾਈ, timing->ਉਚਾਈ, timing->frequency);
	
    }
    
    ਲਿਖੋ ("Standard Timings:\n");
    ਲਈ (i = 0; i < 8; ++i)
    {
	Timing *timing = &(info->standard[i]);
	
	ਜੇ (timing->frequency == 0)
	    ਰੋਕੋ;
	
	ਲਿਖੋ ("  %d x %d @ %d Hz\n",
		timing->ਚੌੜਾਈ, timing->ਉਚਾਈ, timing->frequency);
    }
    
    ਲਈ (i = 0; i < info->n_detailed_timings; ++i)
    {
	DetailedTiming *timing = &(info->detailed_timings[i]);
	ਅਚਲ ਅੱਖਰ *s;
	
	ਲਿਖੋ ("Timing%s: \n",
		(i == 0 && info->preferred_timing_includes_native)?
		" (Preferred)" : "");
	ਲਿਖੋ ("  Pixel Clock: %d\n", timing->pixel_clock);
	ਲਿਖੋ ("  H Addressable: %d\n", timing->h_addr);
	ਲਿਖੋ ("  H Blank: %d\n", timing->h_blank);
	ਲਿਖੋ ("  H Front Porch: %d\n", timing->h_front_porch);
	ਲਿਖੋ ("  H Sync: %d\n", timing->h_sync);
	ਲਿਖੋ ("  V Addressable: %d\n", timing->v_addr);
	ਲਿਖੋ ("  V Blank: %d\n", timing->v_blank);
	ਲਿਖੋ ("  V Front Porch: %d\n", timing->v_front_porch);
	ਲਿਖੋ ("  V Sync: %d\n", timing->v_sync);
	ਲਿਖੋ ("  Width: %d mm\n", timing->ਚੌੜਾਈ_mm);
	ਲਿਖੋ ("  Height: %d mm\n", timing->ਉਚਾਈ_mm);
	ਲਿਖੋ ("  Right Border: %d\n", timing->ਸੱਜਾ_border);
	ਲਿਖੋ ("  Top Border: %d\n", timing->ਸਿਖਰ_border);
	ਚੋਣ (timing->stereo)
	{
	ਮੂਲ:
	ਹਾਲਤ NO_STEREO:   s = "No Stereo"; ਰੋਕੋ;
	ਹਾਲਤ ਖੇਤਰ_ਸੱਜਾ: s = "Field Sequential, Right on Sync"; ਰੋਕੋ;
	ਹਾਲਤ ਖੇਤਰ_ਖੱਬਾ:  s = "Field Sequential, Left on Sync"; ਰੋਕੋ;
	ਹਾਲਤ TWO_WAY_ਸੱਜਾ_ON_EVEN: s = "Two-way, Right on Even"; ਰੋਕੋ;
	ਹਾਲਤ TWO_WAY_ਖੱਬਾ_ON_EVEN:  s = "Two-way, Left on Even"; ਰੋਕੋ;
	ਹਾਲਤ FOUR_WAY_INTERLEAVED:  s = "Four-way Interleaved"; ਰੋਕੋ;
	ਹਾਲਤ SIDE_BY_SIDE:          s = "Side-by-Side"; ਰੋਕੋ;
	}
	ਲਿਖੋ ("  Stereo: %s\n", s);
	
	ਜੇ (timing->digital_sync)
	{
	    ਲਿਖੋ ("  Digital Sync:\n");
	    ਲਿਖੋ ("    composite: %s\n", yesno (timing->ad.digital.ਸੰਯੁਕਤ));
	    ਲਿਖੋ ("    serrations: %s\n", yesno (timing->ad.digital.serrations));
	    ਲਿਖੋ ("    negative vsync: %s\n",
		    yesno (timing->ad.digital.negative_vsync));
	    ਲਿਖੋ ("    negative hsync: %s\n",
		    yesno (timing->ad.digital.negative_hsync));
	}
	ਨਹੀਂਤਾਂ
	{
	    ਲਿਖੋ ("  Analog Sync:\n");
	    ਲਿਖੋ ("    bipolar: %s\n", yesno (timing->ad.analog.bipolar));
	    ਲਿਖੋ ("    serrations: %s\n", yesno (timing->ad.analog.serrations));
	    ਲਿਖੋ ("    sync on green: %s\n", yesno (
			timing->ad.analog.sync_on_green));
	}
    }
    
    ਲਿਖੋ ("Detailed Product information:\n");
    ਲਿਖੋ ("  Product Name: %s\n", info->dsc_ਗੁਣਨਫਲ_name);
    ਲਿਖੋ ("  Serial Number: %s\n", info->dsc_serial_ਸੰਖਿਆ);
    ਲਿਖੋ ("  Unspecified String: %s\n", info->dsc_string);
}

