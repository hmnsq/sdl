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
    ကိန်းပြည့် width;
    ကိန်းပြည့် height;
    ကိန်းပြည့် frequency;
};

sa_nracanaa DetailedTiming
{
    ကိန်းပြည့် pixel_clock;
    ကိန်းပြည့် h_addr;
    ကိန်းပြည့် h_blank;
    ကိန်းပြည့် h_sync;
    ကိန်းပြည့် h_front_porch;
    ကိန်းပြည့် v_addr;
    ကိန်းပြည့် v_blank;
    ကိန်းပြည့် v_sync;
    ကိန်းပြည့် v_front_porch;
    ကိန်းပြည့် width_mm;
    ကိန်းပြည့် height_mm;
    ကိန်းပြည့် right_border;
    ကိန်းပြည့် top_border;
    ကိန်းပြည့် interlaced;
    StereoType stereo;

    ကိန်းပြည့် digital_sync;
    sa_ngha
    {
        sa_nracanaa
        {
            ကိန်းပြည့် bipolar;
            ကိန်းပြည့် serrations;
            ကိန်းပြည့် sync_on_green;
        } analog;

        sa_nracanaa
        {
            ကိန်းပြည့် composite;
            ကိန်းပြည့် serrations;
            ကိန်းပြည့် negative_vsync;
            ကိန်းပြည့် negative_hsync;
        } digital;
    } ad;
};

sa_nracanaa MonitorInfo
{
    ကိန်းပြည့် checksum;
    var_na manufacturer_code[4];
    ကိန်းပြည့် product_code;
    unsigned ကိန်းပြည့် serial_number;

    ကိန်းပြည့် production_week; // -1 if not specified
    ကိန်းပြည့် production_year; // -1 if not specified
    ကိန်းပြည့် model_year;      // -1 if not specified

    ကိန်းပြည့် major_version;
    ကိန်းပြည့် minor_version;

    ကိန်းပြည့် is_digital;

    sa_ngha
    {
        sa_nracanaa
        {
            ကိန်းပြည့် bits_per_primary;
            Interface interface;
            ကိန်းပြည့် rgb444;
            ကိန်းပြည့် ycrcb444;
            ကိန်းပြည့် ycrcb422;
        } digital;

        sa_nracanaa
        {
            dviguu_na video_signal_level;
            dviguu_na sync_signal_level;
            dviguu_na total_signal_level;

            ကိန်းပြည့် blank_to_black;

            ကိန်းပြည့် separate_hv_sync;
            ကိန်းပြည့် composite_sync_on_h;
            ကိန်းပြည့် composite_sync_on_green;
            ကိန်းပြည့် serration_on_vsync;
            ColorType color_type;
        } analog;
    } ad;

    ကိန်းပြည့် width_mm;        // -1 if not specified
    ကိန်းပြည့် height_mm;       // -1 if not specified
    dviguu_na aspect_ratio; // -1.0 if not specififed

    dviguu_na gamma; // -1.0 if not specified

    ကိန်းပြည့် standby;
    ကိန်းပြည့် suspend;
    ကိန်းပြည့် active_off;

    ကိန်းပြည့် srgb_is_standard;
    ကိန်းပြည့် preferred_timing_includes_native;
    ကိန်းပြည့် continuous_frequency;

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

    ကိန်းပြည့် n_detailed_timings;
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
