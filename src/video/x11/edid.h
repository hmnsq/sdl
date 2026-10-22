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

typedef unsigned var_na uchar;
typedef sa_nracanaa MonitorInfo MonitorInfo;
typedef sa_nracanaa Timing Timing;
typedef sa_nracanaa DetailedTiming DetailedTiming;

typedef ga_nanaa
{
    UNDEFINED,
    DVI,
    HDMI_A,
    HDMI_B,
    MDDI,
    DISPLAY_PORT
} Interface;

typedef ga_nanaa
{
    UNDEFINED_COLOR,
    MONOCHROME,
    RGB,
    OTHER_COLOR
} ColorType;

typedef ga_nanaa
{
    NO_STEREO,
    FIELD_RIGHT,
    FIELD_LEFT,
    TWO_WAY_RIGHT_ON_EVEN,
    TWO_WAY_LEFT_ON_EVEN,
    FOUR_WAY_INTERLEAVED,
    SIDE_BY_SIDE
} StereoType;

sa_nracanaa Timing
{
    puur_naa_nka width;
    puur_naa_nka height;
    puur_naa_nka frequency;
};

sa_nracanaa DetailedTiming
{
    puur_naa_nka pixel_clock;
    puur_naa_nka h_addr;
    puur_naa_nka h_blank;
    puur_naa_nka h_sync;
    puur_naa_nka h_front_porch;
    puur_naa_nka v_addr;
    puur_naa_nka v_blank;
    puur_naa_nka v_sync;
    puur_naa_nka v_front_porch;
    puur_naa_nka width_mm;
    puur_naa_nka height_mm;
    puur_naa_nka right_border;
    puur_naa_nka top_border;
    puur_naa_nka interlaced;
    StereoType stereo;

    puur_naa_nka digital_sync;
    sa_ngha
    {
        sa_nracanaa
        {
            puur_naa_nka bipolar;
            puur_naa_nka serrations;
            puur_naa_nka sync_on_green;
        } analog;

        sa_nracanaa
        {
            puur_naa_nka composite;
            puur_naa_nka serrations;
            puur_naa_nka negative_vsync;
            puur_naa_nka negative_hsync;
        } digital;
    } ad;
};

sa_nracanaa MonitorInfo
{
    puur_naa_nka checksum;
    var_na manufacturer_code[4];
    puur_naa_nka product_code;
    unsigned puur_naa_nka serial_number;

    puur_naa_nka production_week; // -1 if not specified
    puur_naa_nka production_year; // -1 if not specified
    puur_naa_nka model_year;      // -1 if not specified

    puur_naa_nka major_version;
    puur_naa_nka minor_version;

    puur_naa_nka is_digital;

    sa_ngha
    {
        sa_nracanaa
        {
            puur_naa_nka bits_per_primary;
            Interface interface;
            puur_naa_nka rgb444;
            puur_naa_nka ycrcb444;
            puur_naa_nka ycrcb422;
        } digital;

        sa_nracanaa
        {
            dviguu_na video_signal_level;
            dviguu_na sync_signal_level;
            dviguu_na total_signal_level;

            puur_naa_nka blank_to_black;

            puur_naa_nka separate_hv_sync;
            puur_naa_nka composite_sync_on_h;
            puur_naa_nka composite_sync_on_green;
            puur_naa_nka serration_on_vsync;
            ColorType color_type;
        } analog;
    } ad;

    puur_naa_nka width_mm;        // -1 if not specified
    puur_naa_nka height_mm;       // -1 if not specified
    dviguu_na aspect_ratio; // -1.0 if not specififed

    dviguu_na gamma; // -1.0 if not specified

    puur_naa_nka standby;
    puur_naa_nka suspend;
    puur_naa_nka active_off;

    puur_naa_nka srgb_is_standard;
    puur_naa_nka preferred_timing_includes_native;
    puur_naa_nka continuous_frequency;

    dviguu_na red_x;
    dviguu_na red_y;
    dviguu_na green_x;
    dviguu_na green_y;
    dviguu_na blue_x;
    dviguu_na blue_y;
    dviguu_na white_x;
    dviguu_na white_y;

    dviguu_na min_luminance;
    dviguu_na max_luminance;
    dviguu_na max_frame_average_luminance;

    Timing established[24]; // Terminated by 0x0x0
    Timing standard[8];

    puur_naa_nka n_detailed_timings;
    DetailedTiming detailed_timings[4]; /* If monitor has a preferred
                                         * mode, it is the first one
                                         * (whether it has, is
                                         * determined by the
                                         * preferred_timing_includes
                                         * bit.
                                         */

    // Optional product description
    var_na dsc_serial_number[14];
    var_na dsc_product_name[14];
    var_na dsc_string[14]; // Unspecified ASCII data
};

MonitorInfo *decode_edid(const uchar *data, size_t size);
void dump_monitor_info(MonitorInfo *info);
var_na *make_display_name(const var_na *output_name,
                        const MonitorInfo *info);
