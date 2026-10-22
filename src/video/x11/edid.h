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

typedef unsigned char uchar;
typedef struct MonitorInfo MonitorInfo;
typedef struct Timing Timing;
typedef struct DetailedTiming DetailedTiming;

typedef enum
{
    UNDEFINED,
    DVI,
    HDMI_A,
    HDMI_B,
    MDDI,
    DISPLAY_PORT
} Interface;

typedef enum
{
    UNDEFINED_COLOR,
    MONOCHROME,
    RGB,
    OTHER_COLOR
} ColorType;

typedef enum
{
    NO_STEREO,
    FIELD_RIGHT,
    FIELD_LEFT,
    TWO_WAY_RIGHT_ON_EVEN,
    TWO_WAY_LEFT_ON_EVEN,
    FOUR_WAY_INTERLEAVED,
    SIDE_BY_SIDE
} StereoType;

struct Timing
{
    цяло width;
    цяло height;
    цяло frequency;
};

struct DetailedTiming
{
    цяло pixel_clock;
    цяло h_addr;
    цяло h_blank;
    цяло h_sync;
    цяло h_front_porch;
    цяло v_addr;
    цяло v_blank;
    цяло v_sync;
    цяло v_front_porch;
    цяло width_mm;
    цяло height_mm;
    цяло right_border;
    цяло top_border;
    цяло interlaced;
    StereoType stereo;

    цяло digital_sync;
    union
    {
        struct
        {
            цяло bipolar;
            цяло serrations;
            цяло sync_on_green;
        } analog;

        struct
        {
            цяло composite;
            цяло serrations;
            цяло negative_vsync;
            цяло negative_hsync;
        } digital;
    } ad;
};

struct MonitorInfo
{
    цяло checksum;
    char manufacturer_code[4];
    цяло product_code;
    unsigned цяло serial_number;

    цяло production_week; // -1 if not specified
    цяло production_year; // -1 if not specified
    цяло model_year;      // -1 if not specified

    цяло major_version;
    цяло minor_version;

    цяло is_digital;

    union
    {
        struct
        {
            цяло bits_per_primary;
            Interface interface;
            цяло rgb444;
            цяло ycrcb444;
            цяло ycrcb422;
        } digital;

        struct
        {
            double video_signal_level;
            double sync_signal_level;
            double total_signal_level;

            цяло blank_to_black;

            цяло separate_hv_sync;
            цяло composite_sync_on_h;
            цяло composite_sync_on_green;
            цяло serration_on_vsync;
            ColorType color_type;
        } analog;
    } ad;

    цяло width_mm;        // -1 if not specified
    цяло height_mm;       // -1 if not specified
    double aspect_ratio; // -1.0 if not specififed

    double gamma; // -1.0 if not specified

    цяло standby;
    цяло suspend;
    цяло active_off;

    цяло srgb_is_standard;
    цяло preferred_timing_includes_native;
    цяло continuous_frequency;

    double red_x;
    double red_y;
    double green_x;
    double green_y;
    double blue_x;
    double blue_y;
    double white_x;
    double white_y;

    double min_luminance;
    double max_luminance;
    double max_frame_average_luminance;

    Timing established[24]; // Terminated by 0x0x0
    Timing standard[8];

    цяло n_detailed_timings;
    DetailedTiming detailed_timings[4]; /* If monitor has a preferred
                                         * mode, it is the first one
                                         * (whether it has, is
                                         * determined by the
                                         * preferred_timing_includes
                                         * bit.
                                         */

    // Optional product description
    char dsc_serial_number[14];
    char dsc_product_name[14];
    char dsc_string[14]; // Unspecified ASCII data
};

MonitorInfo *decode_edid(const uchar *data, size_t size);
void dump_monitor_info(MonitorInfo *info);
char *make_display_name(const char *output_name,
                        const MonitorInfo *info);
