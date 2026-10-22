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
#అన్తర్భావ "SDL_internal.h"

#అన్తర్భావ "edid.h"
#అన్తర్భావ <stdlib.h>
#అన్తర్భావ <string.h>
#అన్తర్భావ <math.h>
#అన్తర్భావ <stdio.h>

#నిర్వచించు TRUE 1
#నిర్వచించు FALSE 0

స్థిర పూర్ణాంకం
get_బిట్టు (పూర్ణాంకం లోపల_2, పూర్ణాంకం బిట్టు)
{
    తిరిగి (లోపల_2 & (1 << బిట్టు)) >> బిట్టు;
}

స్థిర పూర్ణాంకం
get_బిట్లు (పూర్ణాంకం లోపల_2, పూర్ణాంకం begin, పూర్ణాంకం చివర)
{
    పూర్ణాంకం ముసుగు = (1 << (చివర - begin + 1)) - 1;
    
    తిరిగి (లోపల_2 >> begin) & ముసుగు;
}

స్థిర పూర్ణాంకం
decode_శీర్షిక (స్థిరరాశి uchar *edid)
{
    ఒకవేళ (SDL_memcmp (edid, "\x00\xff\xff\xff\xff\xff\xff\x00", 8) == 0)
	తిరిగి TRUE;
    తిరిగి FALSE;
}

స్థిర పూర్ణాంకం
decode_vendor_and_లబ్ధం_identification (స్థిరరాశి uchar *edid, MonitorInfo *info)
{
    పూర్ణాంకం is_model_year;
    
    /* Manufacturer Code */
    info->manufacturer_సంకేతం[0]  = get_బిట్లు (edid[0x08], 2, 6);
    info->manufacturer_సంకేతం[1]  = get_బిట్లు (edid[0x08], 0, 1) << 3;
    info->manufacturer_సంకేతం[1] |= get_బిట్లు (edid[0x09], 5, 7);
    info->manufacturer_సంకేతం[2]  = get_బిట్లు (edid[0x09], 0, 4);
    info->manufacturer_సంకేతం[3]  = '\0';
    
    info->manufacturer_సంకేతం[0] += 'A' - 1;
    info->manufacturer_సంకేతం[1] += 'A' - 1;
    info->manufacturer_సంకేతం[2] += 'A' - 1;

    /* Product Code */
    info->లబ్ధం_సంకేతం = edid[0x0b] << 8 | edid[0x0a];

    /* Serial Number */
    info->serial_సంఖ్య =
	edid[0x0c] | edid[0x0d] << 8 | edid[0x0e] << 16 | (Uint32)edid[0x0f] << 24;

    /* Week and Year */
    is_model_year = FALSE;
    ఎంపిక (edid[0x10])
    {
    స్థితి 0x00:
	info->production_week = -1;
	ఆపు;

    స్థితి 0xff:
	info->production_week = -1;
	is_model_year = TRUE;
	ఆపు;

    అప్రమేయ:
	info->production_week = edid[0x10];
	ఆపు;
    }

    ఒకవేళ (is_model_year)
    {
	info->production_year = -1;
	info->model_year = 1990 + edid[0x11];
    }
    లేకపోతే
    {
	info->production_year = 1990 + edid[0x11];
	info->model_year = -1;
    }

    తిరిగి TRUE;
}

స్థిర పూర్ణాంకం
decode_edid_సంస్కరణ (స్థిరరాశి uchar *edid, MonitorInfo *info)
{
    info->major_సంస్కరణ = edid[0x12];
    info->minor_సంస్కరణ = edid[0x13];

    తిరిగి TRUE;
}

స్థిర పూర్ణాంకం
decode_display_parameters (స్థిరరాశి uchar *edid, MonitorInfo *info)
{
    /* Digital vs Analog */
    info->is_digital = get_బిట్టు (edid[0x14], 7);

    ఒకవేళ (info->is_digital)
    {
	పూర్ణాంకం బిట్లు;
	
	స్థిర స్థిరరాశి పూర్ణాంకం బిట్టు_లోతు_2[8] =
	{
	    -1, 6, 8, 10, 12, 14, 16, -1
	};

	స్థిర స్థిరరాశి Interface interfaces[6] =
	{
	    UNDEFINED, DVI, HDMI_A, HDMI_B, MDDI, DISPLAY_పోర్టు
	};

	బిట్లు = get_బిట్లు (edid[0x14], 4, 6);
	info->ad.digital.బిట్లు_చొప్పున_primary = బిట్టు_లోతు_2[బిట్లు];

	బిట్లు = get_బిట్లు (edid[0x14], 0, 3);
	
	ఒకవేళ (బిట్లు <= 5)
	    info->ad.digital.interface = interfaces[బిట్లు];
	లేకపోతే
	    info->ad.digital.interface = UNDEFINED;
    }
    లేకపోతే
    {
	పూర్ణాంకం బిట్లు = get_బిట్లు (edid[0x14], 5, 6);
	
	స్థిర స్థిరరాశి ద్విగుణ స్థాయిలు[][3] =
	{
	    { 0.7,   0.3,    1.0 },
	    { 0.714, 0.286,  1.0 },
	    { 1.0,   0.4,    1.4 },
	    { 0.7,   0.0,    0.7 },
	};

	info->ad.analog.video_signal_level = స్థాయిలు[బిట్లు][0];
	info->ad.analog.sync_signal_level = స్థాయిలు[బిట్లు][1];
	info->ad.analog.మొత్తం_signal_level = స్థాయిలు[బిట్లు][2];

	info->ad.analog.blank_గమ్యం_black = get_బిట్టు (edid[0x14], 4);

	info->ad.analog.separate_hv_sync = get_బిట్టు (edid[0x14], 3);
	info->ad.analog.సంయుక్త_sync_on_h = get_బిట్టు (edid[0x14], 2);
	info->ad.analog.సంయుక్త_sync_on_green = get_బిట్టు (edid[0x14], 1);

	info->ad.analog.serration_on_vsync = get_బిట్టు (edid[0x14], 0);
    }

    /* Screen Size / Aspect Ratio */
    ఒకవేళ (edid[0x15] == 0 && edid[0x16] == 0)
    {
	info->వెడల్పు_mm = -1;
	info->ఎత్తు_mm = -1;
	info->aspect_నిష్పత్తి = -1.0;
    }
    లేకపోతే ఒకవేళ (edid[0x16] == 0)
    {
	info->వెడల్పు_mm = -1;
	info->ఎత్తు_mm = -1; 
	info->aspect_నిష్పత్తి = 100.0 / (edid[0x15] + 99);
    }
    లేకపోతే ఒకవేళ (edid[0x15] == 0)
    {
	info->వెడల్పు_mm = -1;
	info->ఎత్తు_mm = -1;
	info->aspect_నిష్పత్తి = 100.0 / (edid[0x16] + 99);
	info->aspect_నిష్పత్తి = 1/info->aspect_నిష్పత్తి; /* portrait */
    }
    లేకపోతే
    {
	info->వెడల్పు_mm = 10 * edid[0x15];
	info->ఎత్తు_mm = 10 * edid[0x16];
    }

    /* Gamma */
    ఒకవేళ (edid[0x17] == 0xFF)
	info->gamma = -1.0;
    లేకపోతే
	info->gamma = (edid[0x17] + 100.0) / 100.0;

    /* Features */
    info->standby = get_బిట్టు (edid[0x18], 7);
    info->suspend = get_బిట్టు (edid[0x18], 6);
    info->చురుకైన_off = get_బిట్టు (edid[0x18], 5);

    ఒకవేళ (info->is_digital)
    {
	info->ad.digital.rgb444 = TRUE;
	ఒకవేళ (get_బిట్టు (edid[0x18], 3))
	    info->ad.digital.ycrcb444 = 1;
	ఒకవేళ (get_బిట్టు (edid[0x18], 4))
	    info->ad.digital.ycrcb422 = 1;
    }
    లేకపోతే
    {
	పూర్ణాంకం బిట్లు = get_బిట్లు (edid[0x18], 3, 4);
	ColorType color_type[4] =
	{
	    MONOCHROME, RGB, OTHER_COLOR, UNDEFINED_COLOR
	};

	info->ad.analog.color_type = color_type[బిట్లు];
    }

    info->srgb_is_standard = get_బిట్టు (edid[0x18], 2);

    /* In 1.3 this is called "has preferred timing" */
    info->preferred_timing_includes_native = get_బిట్టు (edid[0x18], 1);

    /* FIXME: In 1.3 this indicates whether the monitor accepts GTF */
    info->continuous_frequency = get_బిట్టు (edid[0x18], 0);
    తిరిగి TRUE;
}

స్థిర ద్విగుణ
decode_fraction (పూర్ణాంకం ఎగువ, పూర్ణాంకం దిగువ)
{
    ద్విగుణ ఫలితం = 0.0;
    పూర్ణాంకం i;

    ఎగువ = (ఎగువ << 2) | దిగువ;

    కొరకు (i = 0; i < 10; ++i)
	ఫలితం += get_బిట్టు (ఎగువ, i) * SDL_pow (2, i - 10);

    తిరిగి ఫలితం;
}

స్థిర పూర్ణాంకం
decode_color_characteristics (స్థిరరాశి uchar *edid, MonitorInfo *info)
{
    info->red_x = decode_fraction (edid[0x1b], get_బిట్లు (edid[0x19], 6, 7));
    info->red_y = decode_fraction (edid[0x1c], get_బిట్లు (edid[0x19], 5, 4));
    info->green_x = decode_fraction (edid[0x1d], get_బిట్లు (edid[0x19], 2, 3));
    info->green_y = decode_fraction (edid[0x1e], get_బిట్లు (edid[0x19], 0, 1));
    info->blue_x = decode_fraction (edid[0x1f], get_బిట్లు (edid[0x1a], 6, 7));
    info->blue_y = decode_fraction (edid[0x20], get_బిట్లు (edid[0x1a], 4, 5));
    info->white_x = decode_fraction (edid[0x21], get_బిట్లు (edid[0x1a], 2, 3));
    info->white_y = decode_fraction (edid[0x22], get_బిట్లు (edid[0x1a], 0, 1));

    తిరిగి TRUE;
}

స్థిర పూర్ణాంకం
decode_established_timings (స్థిరరాశి uchar *edid, MonitorInfo *info)
{
    స్థిర స్థిరరాశి Timing established[][8] = 
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

    పూర్ణాంకం i, j, idx;

    idx = 0;
    కొరకు (i = 0; i < 3; ++i)
    {
	కొరకు (j = 0; j < 8; ++j)
	{
	    పూర్ణాంకం byte = edid[0x23 + i];

	    ఒకవేళ (get_బిట్టు (byte, j) && established[i][j].frequency != 0)
		info->established[idx++] = established[i][j];
	}
    }
    తిరిగి TRUE;
}

స్థిర పూర్ణాంకం
decode_standard_timings (స్థిరరాశి uchar *edid, MonitorInfo *info)
{
    పూర్ణాంకం i;
    
    కొరకు (i = 0; i < 8; i++)
    {
	పూర్ణాంకం మొదటి = edid[0x26 + 2 * i];
	పూర్ణాంకం రెండవ = edid[0x27 + 2 * i];

	ఒకవేళ (మొదటి != 0x01 && రెండవ != 0x01)
	{
	    పూర్ణాంకం w = 8 * (మొదటి + 31);
	    పూర్ణాంకం h = 0;

	    ఎంపిక (get_బిట్లు (రెండవ, 6, 7))
	    {
	    స్థితి 0x00: h = (w / 16) * 10; ఆపు;
	    స్థితి 0x01: h = (w / 4) * 3; ఆపు;
	    స్థితి 0x02: h = (w / 5) * 4; ఆపు;
	    స్థితి 0x03: h = (w / 16) * 9; ఆపు;
	    }

	    info->standard[i].వెడల్పు = w;
	    info->standard[i].ఎత్తు = h;
	    info->standard[i].frequency = get_బిట్లు (రెండవ, 0, 5) + 60;
	}
    }
    
    తిరిగి TRUE;
}

స్థిర శూన్య
decode_lf_string (స్థిరరాశి uchar *s, పూర్ణాంకం n_chars, అక్షరం *ఫలితం)
{
    పూర్ణాంకం i;
    కొరకు (i = 0; i < n_chars; ++i)
    {
	ఒకవేళ (s[i] == 0x0a)
	{
	    *ఫలితం++ = '\0';
	    ఆపు;
	}
	లేకపోతే ఒకవేళ (s[i] == 0x00)
	{
	    /* Convert embedded 0's to spaces */
	    *ఫలితం++ = ' ';
	}
	లేకపోతే
	{
	    *ఫలితం++ = s[i];
	}
    }
}

స్థిర శూన్య
decode_display_descriptor (స్థిరరాశి uchar *desc,
			   MonitorInfo *info)
{
    ఎంపిక (desc[0x03])
    {
    స్థితి 0xFC:
	decode_lf_string (desc + 5, 13, info->dsc_లబ్ధం_name);
	ఆపు;
    స్థితి 0xFF:
	decode_lf_string (desc + 5, 13, info->dsc_serial_సంఖ్య);
	ఆపు;
    స్థితి 0xFE:
	decode_lf_string (desc + 5, 13, info->dsc_string);
	ఆపు;
    స్థితి 0xFD:
	/* Range Limits */
	ఆపు;
    స్థితి 0xFB:
	/* Color Point */
	ఆపు;
    స్థితి 0xFA:
	/* Timing Identifications */
	ఆపు;
    స్థితి 0xF9:
	/* Color Management */
	ఆపు;
    స్థితి 0xF8:
	/* Timing Codes */
	ఆపు;
    స్థితి 0xF7:
	/* Established Timings */
	ఆపు;
    స్థితి 0x10:
	ఆపు;
    }
}

స్థిర శూన్య
decode_detailed_timing (స్థిరరాశి uchar *timing,
			DetailedTiming *detailed)
{
    పూర్ణాంకం బిట్లు;
    StereoType stereo[] =
    {
	NO_STEREO, NO_STEREO, క్షేత్రం_కుడి, క్షేత్రం_ఎడమ,
	TWO_WAY_కుడి_ON_EVEN, TWO_WAY_ఎడమ_ON_EVEN,
	FOUR_WAY_INTERLEAVED, SIDE_BY_SIDE
    };
    
    detailed->pixel_clock = (timing[0x00] | timing[0x01] << 8) * 10000;
    detailed->h_addr = timing[0x02] | ((timing[0x04] & 0xf0) << 4);
    detailed->h_blank = timing[0x03] | ((timing[0x04] & 0x0f) << 8);
    detailed->v_addr = timing[0x05] | ((timing[0x07] & 0xf0) << 4);
    detailed->v_blank = timing[0x06] | ((timing[0x07] & 0x0f) << 8);
    detailed->h_front_porch = timing[0x08] | get_బిట్లు (timing[0x0b], 6, 7) << 8;
    detailed->h_sync = timing[0x09] | get_బిట్లు (timing[0x0b], 4, 5) << 8;
    detailed->v_front_porch =
	get_బిట్లు (timing[0x0a], 4, 7) | get_బిట్లు (timing[0x0b], 2, 3) << 4;
    detailed->v_sync =
	get_బిట్లు (timing[0x0a], 0, 3) | get_బిట్లు (timing[0x0b], 0, 1) << 4;
    detailed->వెడల్పు_mm =  timing[0x0c] | get_బిట్లు (timing[0x0e], 4, 7) << 8;
    detailed->ఎత్తు_mm = timing[0x0d] | get_బిట్లు (timing[0x0e], 0, 3) << 8;
    detailed->కుడి_border = timing[0x0f];
    detailed->శిఖరం_border = timing[0x10];

    detailed->interlaced = get_బిట్టు (timing[0x11], 7);

    /* Stereo */
    బిట్లు = get_బిట్లు (timing[0x11], 5, 6) << 1 | get_బిట్టు (timing[0x11], 0);
    detailed->stereo = stereo[బిట్లు];

    /* Sync */
    బిట్లు = timing[0x11];

    detailed->digital_sync = get_బిట్టు (బిట్లు, 4);
    ఒకవేళ (detailed->digital_sync)
    {
	detailed->ad.digital.సంయుక్త = !get_బిట్టు (బిట్లు, 3);

	ఒకవేళ (detailed->ad.digital.సంయుక్త)
	{
	    detailed->ad.digital.serrations = get_బిట్టు (బిట్లు, 2);
	    detailed->ad.digital.negative_vsync = FALSE;
	}
	లేకపోతే
	{
	    detailed->ad.digital.serrations = FALSE;
	    detailed->ad.digital.negative_vsync = !get_బిట్టు (బిట్లు, 2);
	}

	detailed->ad.digital.negative_hsync = !get_బిట్టు (బిట్లు, 0);
    }
    లేకపోతే
    {
	detailed->ad.analog.bipolar = get_బిట్టు (బిట్లు, 3);
	detailed->ad.analog.serrations = get_బిట్టు (బిట్లు, 2);
	detailed->ad.analog.sync_on_green = !get_బిట్టు (బిట్లు, 1);
    }
}

స్థిర పూర్ణాంకం
decode_descriptors (స్థిరరాశి uchar *edid, MonitorInfo *info)
{
    పూర్ణాంకం i;
    పూర్ణాంకం timing_idx;
    
    timing_idx = 0;
    
    కొరకు (i = 0; i < 4; ++i)
    {
	పూర్ణాంకం సూచీ = 0x36 + i * 18;

	ఒకవేళ (edid[సూచీ + 0] == 0x00 && edid[సూచీ + 1] == 0x00)
	{
	    decode_display_descriptor (edid + సూచీ, info);
	}
	లేకపోతే
	{
	    decode_detailed_timing (
		edid + సూచీ, &(info->detailed_timings[timing_idx++]));
	}
    }

    info->n_detailed_timings = timing_idx;

    తిరిగి TRUE;
}

స్థిర శూన్య
decode_check_కూడిక (స్థిరరాశి uchar *edid,
		  MonitorInfo *info)
{
    పూర్ణాంకం i;
    uchar check = 0;

    కొరకు (i = 0; i < 128; ++i)
	check += edid[i];

    info->checksum = check;
}

స్థిర శూన్య
decode_HDR_metadata_ఖండం (స్థిరరాశి uchar *దత్తాంశం, పూర్ణాంకం నిడివి, MonitorInfo *info)
{
    ఒకవేళ (నిడివి >= 3)
	info->max_luminance = 50.0 * SDL_pow(2, దత్తాంశం[2] / 32.0);

    ఒకవేళ (నిడివి >= 4)
	info->max_చట్రం_సరాసరి_luminance = 50.0 * SDL_pow(2, దత్తాంశం[3] / 32.0);

    ఒకవేళ (నిడివి >= 5)
	info->min_luminance = 50.0 * SDL_pow(2, దత్తాంశం[4] / 32.0);
}


స్థిర శూన్య
decode_cta_ఖండం (స్థిరరాశి uchar *edid,
		  MonitorInfo *info)
{
    పూర్ణాంకం స్థానభ్రంశం_2 = 4;
    అయితే (స్థానభ్రంశం_2 < 128) {
	పూర్ణాంకం నిడివి = edid[స్థానభ్రంశం_2] & 0x1f;
	పూర్ణాంకం type = edid[స్థానభ్రంశం_2] >> 5;
	ఒకవేళ (నిడివి == 0) {
	    ఆపు;
	}
	ఒకవేళ (type == 7) {
	    type <<= 8;
	    type |= edid[స్థానభ్రంశం_2 + 1];
	}
	ఒకవేళ (type == 0x706) {
	    decode_HDR_metadata_ఖండం (&edid[స్థానభ్రంశం_2 + 2], నిడివి - 1, info);
	}
	స్థానభ్రంశం_2 += (1 + నిడివి);
    }
}

MonitorInfo *
decode_edid (స్థిరరాశి uchar *edid, size_t కొలత)
{
    స్థిరరాశి పూర్ణాంకం EDID_పుట_కొలత = 128;
    పూర్ణాంకం అంకె_ఖండాలు = (కొలత / EDID_పుట_కొలత);
    MonitorInfo *info;

    ఒకవేళ ((కొలత % EDID_పుట_కొలత) != 0) {
	తిరిగి ఖాళీ;
    }

    info = SDL_calloc (1, పరిమాణం (MonitorInfo));

    decode_check_కూడిక (edid, info);
    
    ఒకవేళ (!decode_శీర్షిక (edid) ||
        !decode_vendor_and_లబ్ధం_identification (edid, info) ||
        !decode_edid_సంస్కరణ (edid, info) ||
        !decode_display_parameters (edid, info) ||
        !decode_color_characteristics (edid, info) ||
        !decode_established_timings (edid, info) ||
        !decode_standard_timings (edid, info) ||
        !decode_descriptors (edid, info)) {
	SDL_free(info);
	తిరిగి ఖాళీ;
    }
    
    ఒకవేళ (అంకె_ఖండాలు > 1) {
	కొరకు (పూర్ణాంకం i = 1; i < అంకె_ఖండాలు; ++i) {
	    పూర్ణాంకం స్థానభ్రంశం_2 = i * EDID_పుట_కొలత;
	    uchar extension = edid[స్థానభ్రంశం_2];
	    ఒకవేళ (extension == 0x02) {
		// CTA-861 Extension Block
		decode_cta_ఖండం (&edid[స్థానభ్రంశం_2], info);
	    }
	}
    }

    తిరిగి info;
}

స్థిర స్థిరరాశి అక్షరం *
yesno (పూర్ణాంకం v)
{
    తిరిగి v? "yes" : "no";
}

శూన్య
dump_monitor_info (MonitorInfo *info)
{
    పూర్ణాంకం i;
    
    రాయి ("Checksum: %d (%s)\n",
	    info->checksum, info->checksum? "incorrect" : "correct");
    రాయి ("Manufacturer Code: %s\n", info->manufacturer_సంకేతం);
    రాయి ("Product Code: 0x%x\n", info->లబ్ధం_సంకేతం);
    రాయి ("Serial Number: %u\n", info->serial_సంఖ్య);
    
    ఒకవేళ (info->production_week != -1)
	రాయి ("Production Week: %d\n", info->production_week);
    లేకపోతే
	రాయి ("Production Week: unspecified\n");
    
    ఒకవేళ (info->production_year != -1)
	రాయి ("Production Year: %d\n", info->production_year);
    లేకపోతే
	రాయి ("Production Year: unspecified\n");
    
    ఒకవేళ (info->model_year != -1)
	రాయి ("Model Year: %d\n", info->model_year);
    లేకపోతే
	రాయి ("Model Year: unspecified\n");
    
    రాయి ("EDID revision: %d.%d\n", info->major_సంస్కరణ, info->minor_సంస్కరణ);
    
    రాయి ("Display is %s\n", info->is_digital? "digital" : "analog");
    ఒకవేళ (info->is_digital)
    {
	స్థిరరాశి అక్షరం *interface;
	ఒకవేళ (info->ad.digital.బిట్లు_చొప్పున_primary != -1)
	    రాయి ("Bits Per Primary: %d\n", info->ad.digital.బిట్లు_చొప్పున_primary);
	లేకపోతే
	    రాయి ("Bits Per Primary: undefined\n");
	
	ఎంపిక (info->ad.digital.interface)
	{
	స్థితి DVI: interface = "DVI"; ఆపు;
	స్థితి HDMI_A: interface = "HDMI-a"; ఆపు;
	స్థితి HDMI_B: interface = "HDMI-b"; ఆపు;
	స్థితి MDDI: interface = "MDDI"; ఆపు;
	స్థితి DISPLAY_పోర్టు: interface = "DisplayPort"; ఆపు;
	స్థితి UNDEFINED: interface = "undefined"; ఆపు;
	అప్రమేయ: interface = "unknown"; ఆపు;
	}
	రాయి ("Interface: %s\n", interface);
	
	రాయి ("RGB 4:4:4: %s\n", yesno (info->ad.digital.rgb444));
	రాయి ("YCrCb 4:4:4: %s\n", yesno (info->ad.digital.ycrcb444));
	రాయి ("YCrCb 4:2:2: %s\n", yesno (info->ad.digital.ycrcb422));
    }
    లేకపోతే
    {
       స్థిరరాశి అక్షరం *s;
	రాయి ("Video Signal Level: %f\n", info->ad.analog.video_signal_level);
	రాయి ("Sync Signal Level: %f\n", info->ad.analog.sync_signal_level);
	రాయి ("Total Signal Level: %f\n", info->ad.analog.మొత్తం_signal_level);
	
	రాయి ("Blank to Black: %s\n",
		yesno (info->ad.analog.blank_గమ్యం_black));
	రాయి ("Separate HV Sync: %s\n",
		yesno (info->ad.analog.separate_hv_sync));
	రాయి ("Composite Sync on H: %s\n",
		yesno (info->ad.analog.సంయుక్త_sync_on_h));
	రాయి ("Serration on VSync: %s\n",
		yesno (info->ad.analog.serration_on_vsync));
	
	ఎంపిక (info->ad.analog.color_type)
	{
	స్థితి UNDEFINED_COLOR: s = "undefined"; ఆపు;
	స్థితి MONOCHROME: s = "monochrome"; ఆపు;
	స్థితి RGB: s = "rgb"; ఆపు;
	స్థితి OTHER_COLOR: s = "other color"; ఆపు;
	అప్రమేయ: s = "unknown"; ఆపు;
	}
	
	రాయి ("Color: %s\n", s);
    }
    
    ఒకవేళ (info->వెడల్పు_mm == -1)
	రాయి ("Width: undefined\n");
    లేకపోతే
	రాయి ("Width: %d mm\n", info->వెడల్పు_mm);
    
    ఒకవేళ (info->ఎత్తు_mm == -1)
	రాయి ("Height: undefined\n");
    లేకపోతే
	రాయి ("Height: %d mm\n", info->ఎత్తు_mm);
    
    ఒకవేళ (info->aspect_నిష్పత్తి > 0)
	రాయి ("Aspect Ratio: %f\n", info->aspect_నిష్పత్తి);
    లేకపోతే
	రాయి ("Aspect Ratio: undefined\n");
    
    ఒకవేళ (info->gamma >= 0)
	రాయి ("Gamma: %f\n", info->gamma);
    లేకపోతే
	రాయి ("Gamma: undefined\n");
    
    రాయి ("Standby: %s\n", yesno (info->standby));
    రాయి ("Suspend: %s\n", yesno (info->suspend));
    రాయి ("Active Off: %s\n", yesno (info->చురుకైన_off));
    
    రాయి ("SRGB is Standard: %s\n", yesno (info->srgb_is_standard));
    రాయి ("Preferred Timing Includes Native: %s\n",
	    yesno (info->preferred_timing_includes_native));
    రాయి ("Continuous Frequency: %s\n", yesno (info->continuous_frequency));
    
    రాయి ("Red X: %f\n", info->red_x);
    రాయి ("Red Y: %f\n", info->red_y);
    రాయి ("Green X: %f\n", info->green_x);
    రాయి ("Green Y: %f\n", info->green_y);
    రాయి ("Blue X: %f\n", info->blue_x);
    రాయి ("Blue Y: %f\n", info->blue_y);
    రాయి ("White X: %f\n", info->white_x);
    రాయి ("White Y: %f\n", info->white_y);
    రాయి ("Min luminance: %f\n", info->min_luminance);
    రాయి ("Max luminance: %f\n", info->max_luminance);
    రాయి ("Max frame average luminance %f\n", info->max_చట్రం_సరాసరి_luminance);
    
    రాయి ("Established Timings:\n");
    
    కొరకు (i = 0; i < 24; ++i)
    {
	Timing *timing = &(info->established[i]);
	
	ఒకవేళ (timing->frequency == 0)
	    ఆపు;
	
	రాయి ("  %d x %d @ %d Hz\n",
		timing->వెడల్పు, timing->ఎత్తు, timing->frequency);
	
    }
    
    రాయి ("Standard Timings:\n");
    కొరకు (i = 0; i < 8; ++i)
    {
	Timing *timing = &(info->standard[i]);
	
	ఒకవేళ (timing->frequency == 0)
	    ఆపు;
	
	రాయి ("  %d x %d @ %d Hz\n",
		timing->వెడల్పు, timing->ఎత్తు, timing->frequency);
    }
    
    కొరకు (i = 0; i < info->n_detailed_timings; ++i)
    {
	DetailedTiming *timing = &(info->detailed_timings[i]);
	స్థిరరాశి అక్షరం *s;
	
	రాయి ("Timing%s: \n",
		(i == 0 && info->preferred_timing_includes_native)?
		" (Preferred)" : "");
	రాయి ("  Pixel Clock: %d\n", timing->pixel_clock);
	రాయి ("  H Addressable: %d\n", timing->h_addr);
	రాయి ("  H Blank: %d\n", timing->h_blank);
	రాయి ("  H Front Porch: %d\n", timing->h_front_porch);
	రాయి ("  H Sync: %d\n", timing->h_sync);
	రాయి ("  V Addressable: %d\n", timing->v_addr);
	రాయి ("  V Blank: %d\n", timing->v_blank);
	రాయి ("  V Front Porch: %d\n", timing->v_front_porch);
	రాయి ("  V Sync: %d\n", timing->v_sync);
	రాయి ("  Width: %d mm\n", timing->వెడల్పు_mm);
	రాయి ("  Height: %d mm\n", timing->ఎత్తు_mm);
	రాయి ("  Right Border: %d\n", timing->కుడి_border);
	రాయి ("  Top Border: %d\n", timing->శిఖరం_border);
	ఎంపిక (timing->stereo)
	{
	అప్రమేయ:
	స్థితి NO_STEREO:   s = "No Stereo"; ఆపు;
	స్థితి క్షేత్రం_కుడి: s = "Field Sequential, Right on Sync"; ఆపు;
	స్థితి క్షేత్రం_ఎడమ:  s = "Field Sequential, Left on Sync"; ఆపు;
	స్థితి TWO_WAY_కుడి_ON_EVEN: s = "Two-way, Right on Even"; ఆపు;
	స్థితి TWO_WAY_ఎడమ_ON_EVEN:  s = "Two-way, Left on Even"; ఆపు;
	స్థితి FOUR_WAY_INTERLEAVED:  s = "Four-way Interleaved"; ఆపు;
	స్థితి SIDE_BY_SIDE:          s = "Side-by-Side"; ఆపు;
	}
	రాయి ("  Stereo: %s\n", s);
	
	ఒకవేళ (timing->digital_sync)
	{
	    రాయి ("  Digital Sync:\n");
	    రాయి ("    composite: %s\n", yesno (timing->ad.digital.సంయుక్త));
	    రాయి ("    serrations: %s\n", yesno (timing->ad.digital.serrations));
	    రాయి ("    negative vsync: %s\n",
		    yesno (timing->ad.digital.negative_vsync));
	    రాయి ("    negative hsync: %s\n",
		    yesno (timing->ad.digital.negative_hsync));
	}
	లేకపోతే
	{
	    రాయి ("  Analog Sync:\n");
	    రాయి ("    bipolar: %s\n", yesno (timing->ad.analog.bipolar));
	    రాయి ("    serrations: %s\n", yesno (timing->ad.analog.serrations));
	    రాయి ("    sync on green: %s\n", yesno (
			timing->ad.analog.sync_on_green));
	}
    }
    
    రాయి ("Detailed Product information:\n");
    రాయి ("  Product Name: %s\n", info->dsc_లబ్ధం_name);
    రాయి ("  Serial Number: %s\n", info->dsc_serial_సంఖ్య);
    రాయి ("  Unspecified String: %s\n", info->dsc_string);
}

