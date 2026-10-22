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

வகைவரை unsigned எழுத்து uchar;
வகைவரை கட்டமைப்பு MonitorInfo MonitorInfo;
வகைவரை கட்டமைப்பு Timing Timing;
வகைவரை கட்டமைப்பு DetailedTiming DetailedTiming;

வகைவரை எண்ணிக்கை
{
    UNDEFINED,
    DVI,
    HDMI_A,
    HDMI_B,
    MDDI,
    DISPLAY_PORT
} Interface;

வகைவரை எண்ணிக்கை
{
    UNDEFINED_COLOR,
    MONOCHROME,
    RGB,
    OTHER_COLOR
} ColorType;

வகைவரை எண்ணிக்கை
{
    NO_STEREO,
    FIELD_வலது,
    FIELD_இடது,
    TWO_WAY_வலது_ON_EVEN,
    TWO_WAY_இடது_ON_EVEN,
    FOUR_WAY_INTERLEAVED,
    SIDE_BY_SIDE
} StereoType;

கட்டமைப்பு Timing
{
    முழு width;
    முழு height;
    முழு frequency;
};

கட்டமைப்பு DetailedTiming
{
    முழு pixel_clock;
    முழு h_addr;
    முழு h_blank;
    முழு h_sync;
    முழு h_front_porch;
    முழு v_addr;
    முழு v_blank;
    முழு v_sync;
    முழு v_front_porch;
    முழு width_mm;
    முழு height_mm;
    முழு வலது_border;
    முழு உச்சி_border;
    முழு interlaced;
    StereoType stereo;

    முழு digital_sync;
    ஒன்றிப்பு
    {
        கட்டமைப்பு
        {
            முழு bipolar;
            முழு serrations;
            முழு sync_on_green;
        } analog;

        கட்டமைப்பு
        {
            முழு composite;
            முழு serrations;
            முழு negative_vsync;
            முழு negative_hsync;
        } digital;
    } ad;
};

கட்டமைப்பு MonitorInfo
{
    முழு checksum;
    எழுத்து manufacturer_code[4];
    முழு product_code;
    unsigned முழு serial_எண்;

    முழு production_week; // -1 if not specified
    முழு production_year; // -1 if not specified
    முழு model_year;      // -1 if not specified

    முழு major_version;
    முழு minor_version;

    முழு is_digital;

    ஒன்றிப்பு
    {
        கட்டமைப்பு
        {
            முழு bits_per_primary;
            Interface interface;
            முழு rgb444;
            முழு ycrcb444;
            முழு ycrcb422;
        } digital;

        கட்டமைப்பு
        {
            இரட்டை video_signal_level;
            இரட்டை sync_signal_level;
            இரட்டை total_signal_level;

            முழு blank_to_black;

            முழு separate_hv_sync;
            முழு composite_sync_on_h;
            முழு composite_sync_on_green;
            முழு serration_on_vsync;
            ColorType color_type;
        } analog;
    } ad;

    முழு width_mm;        // -1 if not specified
    முழு height_mm;       // -1 if not specified
    இரட்டை aspect_ratio; // -1.0 if not specififed

    இரட்டை gamma; // -1.0 if not specified

    முழு standby;
    முழு suspend;
    முழு active_off;

    முழு srgb_is_standard;
    முழு preferred_timing_includes_native;
    முழு continuous_frequency;

    இரட்டை red_x;
    இரட்டை red_y;
    இரட்டை green_x;
    இரட்டை green_y;
    இரட்டை blue_x;
    இரட்டை blue_y;
    இரட்டை white_x;
    இரட்டை white_y;

    இரட்டை min_luminance;
    இரட்டை max_luminance;
    இரட்டை max_frame_average_luminance;

    Timing established[24]; // Terminated by 0x0x0
    Timing standard[8];

    முழு n_detailed_timings;
    DetailedTiming detailed_timings[4]; /* If monitor has a preferred
                                         * mode, it is the first one
                                         * (whether it has, is
                                         * determined by the
                                         * preferred_timing_includes
                                         * bit.
                                         */

    // Optional product description
    எழுத்து dsc_serial_எண்[14];
    எழுத்து dsc_product_name[14];
    எழுத்து dsc_string[14]; // Unspecified ASCII data
};

MonitorInfo *decode_edid(மாறிலி uchar *data, size_t size);
வெறுமை dump_monitor_info(MonitorInfo *info);
எழுத்து *make_display_name(மாறிலி எழுத்து *output_name,
                        மாறிலி MonitorInfo *info);
