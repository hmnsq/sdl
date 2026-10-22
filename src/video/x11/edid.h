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

തരനിർവചനം unsigned അക്ഷരം uchar;
തരനിർവചനം ഘടന MonitorInfo MonitorInfo;
തരനിർവചനം ഘടന Timing Timing;
തരനിർവചനം ഘടന DetailedTiming DetailedTiming;

തരനിർവചനം എണ്ണൽ
{
    UNDEFINED,
    DVI,
    HDMI_A,
    HDMI_B,
    MDDI,
    DISPLAY_PORT
} Interface;

തരനിർവചനം എണ്ണൽ
{
    UNDEFINED_COLOR,
    MONOCHROME,
    RGB,
    OTHER_COLOR
} ColorType;

തരനിർവചനം എണ്ണൽ
{
    NO_STEREO,
    FIELD_വലത്,
    FIELD_ഇടത്,
    TWO_WAY_വലത്_ON_EVEN,
    TWO_WAY_ഇടത്_ON_EVEN,
    FOUR_WAY_INTERLEAVED,
    SIDE_BY_SIDE
} StereoType;

ഘടന Timing
{
    പൂർണ്ണസംഖ്യ width;
    പൂർണ്ണസംഖ്യ height;
    പൂർണ്ണസംഖ്യ frequency;
};

ഘടന DetailedTiming
{
    പൂർണ്ണസംഖ്യ pixel_clock;
    പൂർണ്ണസംഖ്യ h_addr;
    പൂർണ്ണസംഖ്യ h_blank;
    പൂർണ്ണസംഖ്യ h_sync;
    പൂർണ്ണസംഖ്യ h_front_porch;
    പൂർണ്ണസംഖ്യ v_addr;
    പൂർണ്ണസംഖ്യ v_blank;
    പൂർണ്ണസംഖ്യ v_sync;
    പൂർണ്ണസംഖ്യ v_front_porch;
    പൂർണ്ണസംഖ്യ width_mm;
    പൂർണ്ണസംഖ്യ height_mm;
    പൂർണ്ണസംഖ്യ വലത്_border;
    പൂർണ്ണസംഖ്യ മുകൾ_border;
    പൂർണ്ണസംഖ്യ interlaced;
    StereoType stereo;

    പൂർണ്ണസംഖ്യ digital_sync;
    സംഘം
    {
        ഘടന
        {
            പൂർണ്ണസംഖ്യ bipolar;
            പൂർണ്ണസംഖ്യ serrations;
            പൂർണ്ണസംഖ്യ sync_on_green;
        } analog;

        ഘടന
        {
            പൂർണ്ണസംഖ്യ composite;
            പൂർണ്ണസംഖ്യ serrations;
            പൂർണ്ണസംഖ്യ negative_vsync;
            പൂർണ്ണസംഖ്യ negative_hsync;
        } digital;
    } ad;
};

ഘടന MonitorInfo
{
    പൂർണ്ണസംഖ്യ checksum;
    അക്ഷരം manufacturer_code[4];
    പൂർണ്ണസംഖ്യ product_code;
    unsigned പൂർണ്ണസംഖ്യ serial_സംഖ്യ;

    പൂർണ്ണസംഖ്യ production_week; // -1 if not specified
    പൂർണ്ണസംഖ്യ production_year; // -1 if not specified
    പൂർണ്ണസംഖ്യ model_year;      // -1 if not specified

    പൂർണ്ണസംഖ്യ major_version;
    പൂർണ്ണസംഖ്യ minor_version;

    പൂർണ്ണസംഖ്യ is_digital;

    സംഘം
    {
        ഘടന
        {
            പൂർണ്ണസംഖ്യ bits_per_primary;
            Interface interface;
            പൂർണ്ണസംഖ്യ rgb444;
            പൂർണ്ണസംഖ്യ ycrcb444;
            പൂർണ്ണസംഖ്യ ycrcb422;
        } digital;

        ഘടന
        {
            ഇരട്ട video_signal_level;
            ഇരട്ട sync_signal_level;
            ഇരട്ട total_signal_level;

            പൂർണ്ണസംഖ്യ blank_to_black;

            പൂർണ്ണസംഖ്യ separate_hv_sync;
            പൂർണ്ണസംഖ്യ composite_sync_on_h;
            പൂർണ്ണസംഖ്യ composite_sync_on_green;
            പൂർണ്ണസംഖ്യ serration_on_vsync;
            ColorType color_type;
        } analog;
    } ad;

    പൂർണ്ണസംഖ്യ width_mm;        // -1 if not specified
    പൂർണ്ണസംഖ്യ height_mm;       // -1 if not specified
    ഇരട്ട aspect_ratio; // -1.0 if not specififed

    ഇരട്ട gamma; // -1.0 if not specified

    പൂർണ്ണസംഖ്യ standby;
    പൂർണ്ണസംഖ്യ suspend;
    പൂർണ്ണസംഖ്യ active_off;

    പൂർണ്ണസംഖ്യ srgb_is_standard;
    പൂർണ്ണസംഖ്യ preferred_timing_includes_native;
    പൂർണ്ണസംഖ്യ continuous_frequency;

    ഇരട്ട red_x;
    ഇരട്ട red_y;
    ഇരട്ട green_x;
    ഇരട്ട green_y;
    ഇരട്ട blue_x;
    ഇരട്ട blue_y;
    ഇരട്ട white_x;
    ഇരട്ട white_y;

    ഇരട്ട min_luminance;
    ഇരട്ട max_luminance;
    ഇരട്ട max_frame_average_luminance;

    Timing established[24]; // Terminated by 0x0x0
    Timing standard[8];

    പൂർണ്ണസംഖ്യ n_detailed_timings;
    DetailedTiming detailed_timings[4]; /* If monitor has a preferred
                                         * mode, it is the first one
                                         * (whether it has, is
                                         * determined by the
                                         * preferred_timing_includes
                                         * bit.
                                         */

    // Optional product description
    അക്ഷരം dsc_serial_സംഖ്യ[14];
    അക്ഷരം dsc_product_name[14];
    അക്ഷരം dsc_string[14]; // Unspecified ASCII data
};

MonitorInfo *decode_edid(സ്ഥിരം uchar *data, size_t size);
ശൂന്യം dump_monitor_info(MonitorInfo *info);
അക്ഷരം *make_display_name(സ്ഥിരം അക്ഷരം *output_name,
                        സ്ഥിരം MonitorInfo *info);
