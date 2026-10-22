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

প্রকারনির্দেশ unsigned বর্ণ uchar;
প্রকারনির্দেশ সংরচনা MonitorInfo MonitorInfo;
প্রকারনির্দেশ সংরচনা Timing Timing;
প্রকারনির্দেশ সংরচনা DetailedTiming DetailedTiming;

প্রকারনির্দেশ গণনা
{
    UNDEFINED,
    DVI,
    HDMI_A,
    HDMI_B,
    MDDI,
    DISPLAY_PORT
} Interface;

প্রকারনির্দেশ গণনা
{
    UNDEFINED_COLOR,
    MONOCHROME,
    RGB,
    OTHER_COLOR
} ColorType;

প্রকারনির্দেশ গণনা
{
    NO_STEREO,
    FIELD_ডান,
    FIELD_বাম,
    TWO_WAY_ডান_ON_EVEN,
    TWO_WAY_বাম_ON_EVEN,
    FOUR_WAY_INTERLEAVED,
    SIDE_BY_SIDE
} StereoType;

সংরচনা Timing
{
    পূর্ণাঙ্ক width;
    পূর্ণাঙ্ক height;
    পূর্ণাঙ্ক frequency;
};

সংরচনা DetailedTiming
{
    পূর্ণাঙ্ক pixel_clock;
    পূর্ণাঙ্ক h_addr;
    পূর্ণাঙ্ক h_blank;
    পূর্ণাঙ্ক h_sync;
    পূর্ণাঙ্ক h_front_porch;
    পূর্ণাঙ্ক v_addr;
    পূর্ণাঙ্ক v_blank;
    পূর্ণাঙ্ক v_sync;
    পূর্ণাঙ্ক v_front_porch;
    পূর্ণাঙ্ক width_mm;
    পূর্ণাঙ্ক height_mm;
    পূর্ণাঙ্ক ডান_border;
    পূর্ণাঙ্ক শীর্ষ_border;
    পূর্ণাঙ্ক interlaced;
    StereoType stereo;

    পূর্ণাঙ্ক digital_sync;
    সঙ্ঘ
    {
        সংরচনা
        {
            পূর্ণাঙ্ক bipolar;
            পূর্ণাঙ্ক serrations;
            পূর্ণাঙ্ক sync_on_green;
        } analog;

        সংরচনা
        {
            পূর্ণাঙ্ক composite;
            পূর্ণাঙ্ক serrations;
            পূর্ণাঙ্ক negative_vsync;
            পূর্ণাঙ্ক negative_hsync;
        } digital;
    } ad;
};

সংরচনা MonitorInfo
{
    পূর্ণাঙ্ক checksum;
    বর্ণ manufacturer_code[4];
    পূর্ণাঙ্ক product_code;
    unsigned পূর্ণাঙ্ক serial_সংখ্যা;

    পূর্ণাঙ্ক production_week; // -1 if not specified
    পূর্ণাঙ্ক production_year; // -1 if not specified
    পূর্ণাঙ্ক model_year;      // -1 if not specified

    পূর্ণাঙ্ক major_version;
    পূর্ণাঙ্ক minor_version;

    পূর্ণাঙ্ক is_digital;

    সঙ্ঘ
    {
        সংরচনা
        {
            পূর্ণাঙ্ক bits_per_primary;
            Interface interface;
            পূর্ণাঙ্ক rgb444;
            পূর্ণাঙ্ক ycrcb444;
            পূর্ণাঙ্ক ycrcb422;
        } digital;

        সংরচনা
        {
            দ্বিগুণ video_signal_level;
            দ্বিগুণ sync_signal_level;
            দ্বিগুণ total_signal_level;

            পূর্ণাঙ্ক blank_to_black;

            পূর্ণাঙ্ক separate_hv_sync;
            পূর্ণাঙ্ক composite_sync_on_h;
            পূর্ণাঙ্ক composite_sync_on_green;
            পূর্ণাঙ্ক serration_on_vsync;
            ColorType color_type;
        } analog;
    } ad;

    পূর্ণাঙ্ক width_mm;        // -1 if not specified
    পূর্ণাঙ্ক height_mm;       // -1 if not specified
    দ্বিগুণ aspect_ratio; // -1.0 if not specififed

    দ্বিগুণ gamma; // -1.0 if not specified

    পূর্ণাঙ্ক standby;
    পূর্ণাঙ্ক suspend;
    পূর্ণাঙ্ক active_off;

    পূর্ণাঙ্ক srgb_is_standard;
    পূর্ণাঙ্ক preferred_timing_includes_native;
    পূর্ণাঙ্ক continuous_frequency;

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

    পূর্ণাঙ্ক n_detailed_timings;
    DetailedTiming detailed_timings[4]; /* If monitor has a preferred
                                         * mode, it is the first one
                                         * (whether it has, is
                                         * determined by the
                                         * preferred_timing_includes
                                         * bit.
                                         */

    // Optional product description
    বর্ণ dsc_serial_সংখ্যা[14];
    বর্ণ dsc_product_name[14];
    বর্ণ dsc_string[14]; // Unspecified ASCII data
};

MonitorInfo *decode_edid(ধ্রুব uchar *data, size_t size);
শূন্য dump_monitor_info(MonitorInfo *info);
বর্ণ *make_display_name(ধ্রুব বর্ণ *output_name,
                        ধ্রুব MonitorInfo *info);
