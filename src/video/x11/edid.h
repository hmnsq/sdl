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
    số_nguyên width;
    số_nguyên height;
    số_nguyên frequency;
};

struct DetailedTiming
{
    số_nguyên pixel_clock;
    số_nguyên h_addr;
    số_nguyên h_blank;
    số_nguyên h_sync;
    số_nguyên h_front_porch;
    số_nguyên v_addr;
    số_nguyên v_blank;
    số_nguyên v_sync;
    số_nguyên v_front_porch;
    số_nguyên width_mm;
    số_nguyên height_mm;
    số_nguyên right_border;
    số_nguyên top_border;
    số_nguyên interlaced;
    StereoType stereo;

    số_nguyên digital_sync;
    union
    {
        struct
        {
            số_nguyên bipolar;
            số_nguyên serrations;
            số_nguyên sync_on_green;
        } analog;

        struct
        {
            số_nguyên composite;
            số_nguyên serrations;
            số_nguyên negative_vsync;
            số_nguyên negative_hsync;
        } digital;
    } ad;
};

struct MonitorInfo
{
    số_nguyên checksum;
    char manufacturer_code[4];
    số_nguyên product_code;
    unsigned số_nguyên serial_number;

    số_nguyên production_week; // -1 if not specified
    số_nguyên production_year; // -1 if not specified
    số_nguyên model_year;      // -1 if not specified

    số_nguyên major_version;
    số_nguyên minor_version;

    số_nguyên is_digital;

    union
    {
        struct
        {
            số_nguyên bits_per_primary;
            Interface interface;
            số_nguyên rgb444;
            số_nguyên ycrcb444;
            số_nguyên ycrcb422;
        } digital;

        struct
        {
            double video_signal_level;
            double sync_signal_level;
            double total_signal_level;

            số_nguyên blank_to_black;

            số_nguyên separate_hv_sync;
            số_nguyên composite_sync_on_h;
            số_nguyên composite_sync_on_green;
            số_nguyên serration_on_vsync;
            ColorType color_type;
        } analog;
    } ad;

    số_nguyên width_mm;        // -1 if not specified
    số_nguyên height_mm;       // -1 if not specified
    double aspect_ratio; // -1.0 if not specififed

    double gamma; // -1.0 if not specified

    số_nguyên standby;
    số_nguyên suspend;
    số_nguyên active_off;

    số_nguyên srgb_is_standard;
    số_nguyên preferred_timing_includes_native;
    số_nguyên continuous_frequency;

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

    số_nguyên n_detailed_timings;
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
