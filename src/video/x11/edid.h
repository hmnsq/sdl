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
    정수 width;
    정수 height;
    정수 frequency;
};

struct DetailedTiming
{
    정수 pixel_clock;
    정수 h_addr;
    정수 h_blank;
    정수 h_sync;
    정수 h_front_porch;
    정수 v_addr;
    정수 v_blank;
    정수 v_sync;
    정수 v_front_porch;
    정수 width_mm;
    정수 height_mm;
    정수 right_border;
    정수 top_border;
    정수 interlaced;
    StereoType stereo;

    정수 digital_sync;
    union
    {
        struct
        {
            정수 bipolar;
            정수 serrations;
            정수 sync_on_green;
        } analog;

        struct
        {
            정수 composite;
            정수 serrations;
            정수 negative_vsync;
            정수 negative_hsync;
        } digital;
    } ad;
};

struct MonitorInfo
{
    정수 checksum;
    char manufacturer_code[4];
    정수 product_code;
    unsigned 정수 serial_number;

    정수 production_week; // -1 if not specified
    정수 production_year; // -1 if not specified
    정수 model_year;      // -1 if not specified

    정수 major_version;
    정수 minor_version;

    정수 is_digital;

    union
    {
        struct
        {
            정수 bits_per_primary;
            Interface interface;
            정수 rgb444;
            정수 ycrcb444;
            정수 ycrcb422;
        } digital;

        struct
        {
            double video_signal_level;
            double sync_signal_level;
            double total_signal_level;

            정수 blank_to_black;

            정수 separate_hv_sync;
            정수 composite_sync_on_h;
            정수 composite_sync_on_green;
            정수 serration_on_vsync;
            ColorType color_type;
        } analog;
    } ad;

    정수 width_mm;        // -1 if not specified
    정수 height_mm;       // -1 if not specified
    double aspect_ratio; // -1.0 if not specififed

    double gamma; // -1.0 if not specified

    정수 standby;
    정수 suspend;
    정수 active_off;

    정수 srgb_is_standard;
    정수 preferred_timing_includes_native;
    정수 continuous_frequency;

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

    정수 n_detailed_timings;
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
