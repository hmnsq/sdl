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

ಪ್ರಕಾರನಿರ್ದೇಶ unsigned ವರ್ಣ uchar;
ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ MonitorInfo MonitorInfo;
ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ Timing Timing;
ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ DetailedTiming DetailedTiming;

ಪ್ರಕಾರನಿರ್ದೇಶ ಗಣನಾ
{
    UNDEFINED,
    DVI,
    HDMI_A,
    HDMI_B,
    MDDI,
    DISPLAY_PORT
} Interface;

ಪ್ರಕಾರನಿರ್ದೇಶ ಗಣನಾ
{
    UNDEFINED_COLOR,
    MONOCHROME,
    RGB,
    OTHER_COLOR
} ColorType;

ಪ್ರಕಾರನಿರ್ದೇಶ ಗಣನಾ
{
    NO_STEREO,
    FIELD_ಬಲ,
    FIELD_ಎಡ,
    TWO_WAY_ಬಲ_ON_EVEN,
    TWO_WAY_ಎಡ_ON_EVEN,
    FOUR_WAY_INTERLEAVED,
    SIDE_BY_SIDE
} StereoType;

ಸಂರಚನಾ Timing
{
    ಪೂರ್ಣಾಙ್ಕ width;
    ಪೂರ್ಣಾಙ್ಕ height;
    ಪೂರ್ಣಾಙ್ಕ frequency;
};

ಸಂರಚನಾ DetailedTiming
{
    ಪೂರ್ಣಾಙ್ಕ pixel_clock;
    ಪೂರ್ಣಾಙ್ಕ h_addr;
    ಪೂರ್ಣಾಙ್ಕ h_blank;
    ಪೂರ್ಣಾಙ್ಕ h_sync;
    ಪೂರ್ಣಾಙ್ಕ h_front_porch;
    ಪೂರ್ಣಾಙ್ಕ v_addr;
    ಪೂರ್ಣಾಙ್ಕ v_blank;
    ಪೂರ್ಣಾಙ್ಕ v_sync;
    ಪೂರ್ಣಾಙ್ಕ v_front_porch;
    ಪೂರ್ಣಾಙ್ಕ width_mm;
    ಪೂರ್ಣಾಙ್ಕ height_mm;
    ಪೂರ್ಣಾಙ್ಕ ಬಲ_border;
    ಪೂರ್ಣಾಙ್ಕ ತುದಿ_border;
    ಪೂರ್ಣಾಙ್ಕ interlaced;
    StereoType stereo;

    ಪೂರ್ಣಾಙ್ಕ digital_sync;
    ಸಙ್ಘ
    {
        ಸಂರಚನಾ
        {
            ಪೂರ್ಣಾಙ್ಕ bipolar;
            ಪೂರ್ಣಾಙ್ಕ serrations;
            ಪೂರ್ಣಾಙ್ಕ sync_on_green;
        } analog;

        ಸಂರಚನಾ
        {
            ಪೂರ್ಣಾಙ್ಕ composite;
            ಪೂರ್ಣಾಙ್ಕ serrations;
            ಪೂರ್ಣಾಙ್ಕ negative_vsync;
            ಪೂರ್ಣಾಙ್ಕ negative_hsync;
        } digital;
    } ad;
};

ಸಂರಚನಾ MonitorInfo
{
    ಪೂರ್ಣಾಙ್ಕ checksum;
    ವರ್ಣ manufacturer_code[4];
    ಪೂರ್ಣಾಙ್ಕ product_code;
    unsigned ಪೂರ್ಣಾಙ್ಕ serial_ಸಂಖ್ಯೆ;

    ಪೂರ್ಣಾಙ್ಕ production_week; // -1 if not specified
    ಪೂರ್ಣಾಙ್ಕ production_year; // -1 if not specified
    ಪೂರ್ಣಾಙ್ಕ model_year;      // -1 if not specified

    ಪೂರ್ಣಾಙ್ಕ major_version;
    ಪೂರ್ಣಾಙ್ಕ minor_version;

    ಪೂರ್ಣಾಙ್ಕ is_digital;

    ಸಙ್ಘ
    {
        ಸಂರಚನಾ
        {
            ಪೂರ್ಣಾಙ್ಕ bits_per_primary;
            Interface interface;
            ಪೂರ್ಣಾಙ್ಕ rgb444;
            ಪೂರ್ಣಾಙ್ಕ ycrcb444;
            ಪೂರ್ಣಾಙ್ಕ ycrcb422;
        } digital;

        ಸಂರಚನಾ
        {
            ದ್ವಿಗುಣ video_signal_level;
            ದ್ವಿಗುಣ sync_signal_level;
            ದ್ವಿಗುಣ total_signal_level;

            ಪೂರ್ಣಾಙ್ಕ blank_to_black;

            ಪೂರ್ಣಾಙ್ಕ separate_hv_sync;
            ಪೂರ್ಣಾಙ್ಕ composite_sync_on_h;
            ಪೂರ್ಣಾಙ್ಕ composite_sync_on_green;
            ಪೂರ್ಣಾಙ್ಕ serration_on_vsync;
            ColorType color_type;
        } analog;
    } ad;

    ಪೂರ್ಣಾಙ್ಕ width_mm;        // -1 if not specified
    ಪೂರ್ಣಾಙ್ಕ height_mm;       // -1 if not specified
    ದ್ವಿಗುಣ aspect_ratio; // -1.0 if not specififed

    ದ್ವಿಗುಣ gamma; // -1.0 if not specified

    ಪೂರ್ಣಾಙ್ಕ standby;
    ಪೂರ್ಣಾಙ್ಕ suspend;
    ಪೂರ್ಣಾಙ್ಕ active_off;

    ಪೂರ್ಣಾಙ್ಕ srgb_is_standard;
    ಪೂರ್ಣಾಙ್ಕ preferred_timing_includes_native;
    ಪೂರ್ಣಾಙ್ಕ continuous_frequency;

    ದ್ವಿಗುಣ red_x;
    ದ್ವಿಗುಣ red_y;
    ದ್ವಿಗುಣ green_x;
    ದ್ವಿಗುಣ green_y;
    ದ್ವಿಗುಣ blue_x;
    ದ್ವಿಗುಣ blue_y;
    ದ್ವಿಗುಣ white_x;
    ದ್ವಿಗುಣ white_y;

    ದ್ವಿಗುಣ min_luminance;
    ದ್ವಿಗುಣ max_luminance;
    ದ್ವಿಗುಣ max_frame_average_luminance;

    Timing established[24]; // Terminated by 0x0x0
    Timing standard[8];

    ಪೂರ್ಣಾಙ್ಕ n_detailed_timings;
    DetailedTiming detailed_timings[4]; /* If monitor has a preferred
                                         * mode, it is the first one
                                         * (whether it has, is
                                         * determined by the
                                         * preferred_timing_includes
                                         * bit.
                                         */

    // Optional product description
    ವರ್ಣ dsc_serial_ಸಂಖ್ಯೆ[14];
    ವರ್ಣ dsc_product_name[14];
    ವರ್ಣ dsc_string[14]; // Unspecified ASCII data
};

MonitorInfo *decode_edid(ಧ್ರುವ uchar *data, size_t size);
ಶೂನ್ಯ dump_monitor_info(MonitorInfo *info);
ವರ್ಣ *make_display_name(ಧ್ರುವ ವರ್ಣ *output_name,
                        ಧ್ರುವ MonitorInfo *info);
