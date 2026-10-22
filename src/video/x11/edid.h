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

تعريفنوع unsigned حرف uchar;
تعريفنوع بنية MonitorInfo MonitorInfo;
تعريفنوع بنية Timing Timing;
تعريفنوع بنية DetailedTiming DetailedTiming;

تعريفنوع تعداد
{
    UNDEFINED,
    DVI,
    HDMI_A,
    HDMI_B,
    MDDI,
    DISPLAY_PORT
} Interface;

تعريفنوع تعداد
{
    UNDEFINED_COLOR,
    MONOCHROME,
    RGB,
    OTHER_COLOR
} ColorType;

تعريفنوع تعداد
{
    NO_STEREO,
    FIELD_کانن,
    FIELD_کيري,
    TWO_WAY_کانن_ON_EVEN,
    TWO_WAY_کيري_ON_EVEN,
    FOUR_WAY_INTERLEAVED,
    SIDE_BY_SIDE
} StereoType;

بنية Timing
{
    صحيح width;
    صحيح height;
    صحيح frequency;
};

بنية DetailedTiming
{
    صحيح pixel_clock;
    صحيح h_addr;
    صحيح h_blank;
    صحيح h_sync;
    صحيح h_front_porch;
    صحيح v_addr;
    صحيح v_blank;
    صحيح v_sync;
    صحيح v_front_porch;
    صحيح width_mm;
    صحيح height_mm;
    صحيح کانن_border;
    صحيح اتس_border;
    صحيح interlaced;
    StereoType stereo;

    صحيح digital_sync;
    اتحاد
    {
        بنية
        {
            صحيح bipolar;
            صحيح serrations;
            صحيح sync_on_green;
        } analog;

        بنية
        {
            صحيح composite;
            صحيح serrations;
            صحيح negative_vsync;
            صحيح negative_hsync;
        } digital;
    } ad;
};

بنية MonitorInfo
{
    صحيح checksum;
    حرف manufacturer_code[4];
    صحيح product_code;
    unsigned صحيح serial_نومبور;

    صحيح production_week; // -1 if not specified
    صحيح production_year; // -1 if not specified
    صحيح model_year;      // -1 if not specified

    صحيح major_version;
    صحيح minor_version;

    صحيح is_digital;

    اتحاد
    {
        بنية
        {
            صحيح bits_per_primary;
            Interface interface;
            صحيح rgb444;
            صحيح ycrcb444;
            صحيح ycrcb422;
        } digital;

        بنية
        {
            مزدوج video_signal_level;
            مزدوج sync_signal_level;
            مزدوج total_signal_level;

            صحيح blank_to_black;

            صحيح separate_hv_sync;
            صحيح composite_sync_on_h;
            صحيح composite_sync_on_green;
            صحيح serration_on_vsync;
            ColorType color_type;
        } analog;
    } ad;

    صحيح width_mm;        // -1 if not specified
    صحيح height_mm;       // -1 if not specified
    مزدوج aspect_ratio; // -1.0 if not specififed

    مزدوج gamma; // -1.0 if not specified

    صحيح standby;
    صحيح suspend;
    صحيح active_off;

    صحيح srgb_is_standard;
    صحيح preferred_timing_includes_native;
    صحيح continuous_frequency;

    مزدوج red_x;
    مزدوج red_y;
    مزدوج green_x;
    مزدوج green_y;
    مزدوج blue_x;
    مزدوج blue_y;
    مزدوج white_x;
    مزدوج white_y;

    مزدوج min_luminance;
    مزدوج max_luminance;
    مزدوج max_frame_average_luminance;

    Timing established[24]; // Terminated by 0x0x0
    Timing standard[8];

    صحيح n_detailed_timings;
    DetailedTiming detailed_timings[4]; /* If monitor has a preferred
                                         * mode, it is the first one
                                         * (whether it has, is
                                         * determined by the
                                         * preferred_timing_includes
                                         * bit.
                                         */

    // Optional product description
    حرف dsc_serial_نومبور[14];
    حرف dsc_product_name[14];
    حرف dsc_string[14]; // Unspecified ASCII data
};

MonitorInfo *decode_edid(ثابت uchar *data, size_t size);
فراغ dump_monitor_info(MonitorInfo *info);
حرف *make_display_name(ثابت حرف *output_name,
                        ثابت MonitorInfo *info);
