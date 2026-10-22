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
    целое width;
    целое height;
    целое frequency;
};

struct DetailedTiming
{
    целое pixel_clock;
    целое h_addr;
    целое h_blank;
    целое h_sync;
    целое h_front_porch;
    целое v_addr;
    целое v_blank;
    целое v_sync;
    целое v_front_porch;
    целое width_mm;
    целое height_mm;
    целое right_border;
    целое top_border;
    целое interlaced;
    StereoType stereo;

    целое digital_sync;
    union
    {
        struct
        {
            целое bipolar;
            целое serrations;
            целое sync_on_green;
        } analog;

        struct
        {
            целое composite;
            целое serrations;
            целое negative_vsync;
            целое negative_hsync;
        } digital;
    } ad;
};

struct MonitorInfo
{
    целое checksum;
    char manufacturer_code[4];
    целое product_code;
    unsigned целое serial_number;

    целое production_week; // -1 if not specified
    целое production_year; // -1 if not specified
    целое model_year;      // -1 if not specified

    целое major_version;
    целое minor_version;

    целое is_digital;

    union
    {
        struct
        {
            целое bits_per_primary;
            Interface interface;
            целое rgb444;
            целое ycrcb444;
            целое ycrcb422;
        } digital;

        struct
        {
            double video_signal_level;
            double sync_signal_level;
            double total_signal_level;

            целое blank_to_black;

            целое separate_hv_sync;
            целое composite_sync_on_h;
            целое composite_sync_on_green;
            целое serration_on_vsync;
            ColorType color_type;
        } analog;
    } ad;

    целое width_mm;        // -1 if not specified
    целое height_mm;       // -1 if not specified
    double aspect_ratio; // -1.0 if not specififed

    double gamma; // -1.0 if not specified

    целое standby;
    целое suspend;
    целое active_off;

    целое srgb_is_standard;
    целое preferred_timing_includes_native;
    целое continuous_frequency;

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

    целое n_detailed_timings;
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
