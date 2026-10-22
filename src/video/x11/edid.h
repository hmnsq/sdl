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
    ціле width;
    ціле height;
    ціле frequency;
};

struct DetailedTiming
{
    ціле pixel_clock;
    ціле h_addr;
    ціле h_blank;
    ціле h_sync;
    ціле h_front_porch;
    ціле v_addr;
    ціле v_blank;
    ціле v_sync;
    ціле v_front_porch;
    ціле width_mm;
    ціле height_mm;
    ціле right_border;
    ціле top_border;
    ціле interlaced;
    StereoType stereo;

    ціле digital_sync;
    union
    {
        struct
        {
            ціле bipolar;
            ціле serrations;
            ціле sync_on_green;
        } analog;

        struct
        {
            ціле composite;
            ціле serrations;
            ціле negative_vsync;
            ціле negative_hsync;
        } digital;
    } ad;
};

struct MonitorInfo
{
    ціле checksum;
    char manufacturer_code[4];
    ціле product_code;
    unsigned ціле serial_number;

    ціле production_week; // -1 if not specified
    ціле production_year; // -1 if not specified
    ціле model_year;      // -1 if not specified

    ціле major_version;
    ціле minor_version;

    ціле is_digital;

    union
    {
        struct
        {
            ціле bits_per_primary;
            Interface interface;
            ціле rgb444;
            ціле ycrcb444;
            ціле ycrcb422;
        } digital;

        struct
        {
            double video_signal_level;
            double sync_signal_level;
            double total_signal_level;

            ціле blank_to_black;

            ціле separate_hv_sync;
            ціле composite_sync_on_h;
            ціле composite_sync_on_green;
            ціле serration_on_vsync;
            ColorType color_type;
        } analog;
    } ad;

    ціле width_mm;        // -1 if not specified
    ціле height_mm;       // -1 if not specified
    double aspect_ratio; // -1.0 if not specififed

    double gamma; // -1.0 if not specified

    ціле standby;
    ціле suspend;
    ціле active_off;

    ціле srgb_is_standard;
    ціле preferred_timing_includes_native;
    ціле continuous_frequency;

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

    ціле n_detailed_timings;
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
