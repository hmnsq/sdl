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

প্রকারলেখ unsigned অক্ষর uchar;
প্রকারলেখ কাঠামো MonitorInfo MonitorInfo;
প্রকারলেখ কাঠামো Timing Timing;
প্রকারলেখ কাঠামো DetailedTiming DetailedTiming;

প্রকারলেখ গণনা
{
    UNDEFINED,
    DVI,
    HDMI_A,
    HDMI_B,
    MDDI,
    DISPLAY_PORT
} Interface;

প্রকারলেখ গণনা
{
    UNDEFINED_COLOR,
    MONOCHROME,
    RGB,
    OTHER_COLOR
} ColorType;

প্রকারলেখ গণনা
{
    NO_STEREO,
    FIELD_ডান,
    FIELD_বাম,
    TWO_WAY_ডান_ON_EVEN,
    TWO_WAY_বাম_ON_EVEN,
    FOUR_WAY_INTERLEAVED,
    SIDE_BY_SIDE
} StereoType;

কাঠামো Timing
{
    পূর্ণসংখ্যা width;
    পূর্ণসংখ্যা height;
    পূর্ণসংখ্যা frequency;
};

কাঠামো DetailedTiming
{
    পূর্ণসংখ্যা pixel_clock;
    পূর্ণসংখ্যা h_addr;
    পূর্ণসংখ্যা h_blank;
    পূর্ণসংখ্যা h_sync;
    পূর্ণসংখ্যা h_front_porch;
    পূর্ণসংখ্যা v_addr;
    পূর্ণসংখ্যা v_blank;
    পূর্ণসংখ্যা v_sync;
    পূর্ণসংখ্যা v_front_porch;
    পূর্ণসংখ্যা width_mm;
    পূর্ণসংখ্যা height_mm;
    পূর্ণসংখ্যা ডান_border;
    পূর্ণসংখ্যা শীর্ষ_border;
    পূর্ণসংখ্যা interlaced;
    StereoType stereo;

    পূর্ণসংখ্যা digital_sync;
    সংঘ
    {
        কাঠামো
        {
            পূর্ণসংখ্যা bipolar;
            পূর্ণসংখ্যা serrations;
            পূর্ণসংখ্যা sync_on_green;
        } analog;

        কাঠামো
        {
            পূর্ণসংখ্যা composite;
            পূর্ণসংখ্যা serrations;
            পূর্ণসংখ্যা negative_vsync;
            পূর্ণসংখ্যা negative_hsync;
        } digital;
    } ad;
};

কাঠামো MonitorInfo
{
    পূর্ণসংখ্যা checksum;
    অক্ষর manufacturer_code[4];
    পূর্ণসংখ্যা product_code;
    unsigned পূর্ণসংখ্যা serial_সংখ্যা;

    পূর্ণসংখ্যা production_week; // -1 if not specified
    পূর্ণসংখ্যা production_year; // -1 if not specified
    পূর্ণসংখ্যা model_year;      // -1 if not specified

    পূর্ণসংখ্যা major_version;
    পূর্ণসংখ্যা minor_version;

    পূর্ণসংখ্যা is_digital;

    সংঘ
    {
        কাঠামো
        {
            পূর্ণসংখ্যা bits_per_primary;
            Interface interface;
            পূর্ণসংখ্যা rgb444;
            পূর্ণসংখ্যা ycrcb444;
            পূর্ণসংখ্যা ycrcb422;
        } digital;

        কাঠামো
        {
            দ্বিগুণ video_signal_level;
            দ্বিগুণ sync_signal_level;
            দ্বিগুণ যোগ_signal_level;

            পূর্ণসংখ্যা blank_to_black;

            পূর্ণসংখ্যা separate_hv_sync;
            পূর্ণসংখ্যা composite_sync_on_h;
            পূর্ণসংখ্যা composite_sync_on_green;
            পূর্ণসংখ্যা serration_on_vsync;
            ColorType color_type;
        } analog;
    } ad;

    পূর্ণসংখ্যা width_mm;        // -1 if not specified
    পূর্ণসংখ্যা height_mm;       // -1 if not specified
    দ্বিগুণ aspect_ratio; // -1.0 if not specififed

    দ্বিগুণ gamma; // -1.0 if not specified

    পূর্ণসংখ্যা standby;
    পূর্ণসংখ্যা suspend;
    পূর্ণসংখ্যা active_off;

    পূর্ণসংখ্যা srgb_is_standard;
    পূর্ণসংখ্যা preferred_timing_includes_native;
    পূর্ণসংখ্যা continuous_frequency;

    দ্বিগুণ red_x;
    দ্বিগুণ red_y;
    দ্বিগুণ green_x;
    দ্বিগুণ green_y;
    দ্বিগুণ blue_x;
    দ্বিগুণ blue_y;
    দ্বিগুণ white_x;
    দ্বিগুণ white_y;

    দ্বিগুণ min_luminance;
    দ্বিগুণ max_luminance;
    দ্বিগুণ max_frame_average_luminance;

    Timing established[24]; // Terminated by 0x0x0
    Timing standard[8];

    পূর্ণসংখ্যা n_detailed_timings;
    DetailedTiming detailed_timings[4]; /* If monitor has a preferred
                                         * mode, it is the first one
                                         * (whether it has, is
                                         * determined by the
                                         * preferred_timing_includes
                                         * bit.
                                         */

    // Optional product description
    অক্ষর dsc_serial_সংখ্যা[14];
    অক্ষর dsc_product_name[14];
    অক্ষর dsc_string[14]; // Unspecified ASCII data
};

MonitorInfo *decode_edid(ধ্রুবক uchar *তথ্য, size_t আকার_2);
শূন্য dump_monitor_info(MonitorInfo *info);
অক্ষর *make_display_name(ধ্রুবক অক্ষর *output_name,
                        ধ্রুবক MonitorInfo *info);
