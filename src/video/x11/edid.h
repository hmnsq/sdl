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

تعریفنوع unsigned نویسه uchar;
تعریفنوع ساختار MonitorInfo MonitorInfo;
تعریفنوع ساختار Timing Timing;
تعریفنوع ساختار DetailedTiming DetailedTiming;

تعریفنوع شمارش
{
    UNDEFINED,
    DVI,
    HDMI_A,
    HDMI_B,
    MDDI,
    DISPLAY_PORT
} Interface;

تعریفنوع شمارش
{
    UNDEFINED_COLOR,
    MONOCHROME,
    RGB,
    OTHER_COLOR
} ColorType;

تعریفنوع شمارش
{
    NO_STEREO,
    FIELD_راست,
    FIELD_چپ,
    TWO_WAY_راست_ON_EVEN,
    TWO_WAY_چپ_ON_EVEN,
    FOUR_WAY_INTERLEAVED,
    SIDE_BY_SIDE
} StereoType;

ساختار Timing
{
    صحیح width;
    صحیح height;
    صحیح frequency;
};

ساختار DetailedTiming
{
    صحیح pixel_clock;
    صحیح h_addr;
    صحیح h_blank;
    صحیح h_sync;
    صحیح h_front_porch;
    صحیح v_addr;
    صحیح v_blank;
    صحیح v_sync;
    صحیح v_front_porch;
    صحیح width_mm;
    صحیح height_mm;
    صحیح راست_border;
    صحیح بالاترین_border;
    صحیح interlaced;
    StereoType stereo;

    صحیح digital_sync;
    اجتماع
    {
        ساختار
        {
            صحیح bipolar;
            صحیح serrations;
            صحیح sync_on_green;
        } analog;

        ساختار
        {
            صحیح composite;
            صحیح serrations;
            صحیح negative_vsync;
            صحیح negative_hsync;
        } digital;
    } ad;
};

ساختار MonitorInfo
{
    صحیح checksum;
    نویسه manufacturer_code[4];
    صحیح product_code;
    unsigned صحیح serial_عدد;

    صحیح production_week; // -1 if not specified
    صحیح production_year; // -1 if not specified
    صحیح model_year;      // -1 if not specified

    صحیح major_version;
    صحیح minor_version;

    صحیح is_digital;

    اجتماع
    {
        ساختار
        {
            صحیح bits_per_primary;
            Interface interface;
            صحیح rgb444;
            صحیح ycrcb444;
            صحیح ycrcb422;
        } digital;

        ساختار
        {
            دوگانه video_signal_level;
            دوگانه sync_signal_level;
            دوگانه total_signal_level;

            صحیح blank_to_black;

            صحیح separate_hv_sync;
            صحیح composite_sync_on_h;
            صحیح composite_sync_on_green;
            صحیح serration_on_vsync;
            ColorType color_type;
        } analog;
    } ad;

    صحیح width_mm;        // -1 if not specified
    صحیح height_mm;       // -1 if not specified
    دوگانه aspect_ratio; // -1.0 if not specififed

    دوگانه gamma; // -1.0 if not specified

    صحیح standby;
    صحیح suspend;
    صحیح active_off;

    صحیح srgb_is_standard;
    صحیح preferred_timing_includes_native;
    صحیح continuous_frequency;

    دوگانه red_x;
    دوگانه red_y;
    دوگانه green_x;
    دوگانه green_y;
    دوگانه blue_x;
    دوگانه blue_y;
    دوگانه white_x;
    دوگانه white_y;

    دوگانه min_luminance;
    دوگانه max_luminance;
    دوگانه max_frame_average_luminance;

    Timing established[24]; // Terminated by 0x0x0
    Timing standard[8];

    صحیح n_detailed_timings;
    DetailedTiming detailed_timings[4]; /* If monitor has a preferred
                                         * mode, it is the first one
                                         * (whether it has, is
                                         * determined by the
                                         * preferred_timing_includes
                                         * bit.
                                         */

    // Optional product description
    نویسه dsc_serial_عدد[14];
    نویسه dsc_product_name[14];
    نویسه dsc_string[14]; // Unspecified ASCII data
};

MonitorInfo *decode_edid(ثابت uchar *data, size_t size);
تهی dump_monitor_info(MonitorInfo *info);
نویسه *make_display_name(ثابت نویسه *output_name,
                        ثابت MonitorInfo *info);
