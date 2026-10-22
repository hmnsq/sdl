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

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ uchar;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ MonitorInfo MonitorInfo;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ Timing Timing;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ DetailedTiming DetailedTiming;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ
{
    UNDEFINED,
    DVI,
    HDMI_A,
    HDMI_B,
    MDDI,
    DISPLAY_ಪೋರ್ಟ್
} Interface;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ
{
    UNDEFINED_COLOR,
    MONOCHROME,
    RGB,
    OTHER_COLOR
} ColorType;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ
{
    NO_STEREO,
    ಕ್ಷೇತ್ರ_ಬಲ,
    ಕ್ಷೇತ್ರ_ಎಡ,
    TWO_WAY_ಬಲ_ON_EVEN,
    TWO_WAY_ಎಡ_ON_EVEN,
    FOUR_WAY_INTERLEAVED,
    SIDE_BY_SIDE
} StereoType;

ರಚನೆ Timing
{
    ಪೂರ್ಣಾಂಕ ಅಗಲ;
    ಪೂರ್ಣಾಂಕ ಎತ್ತರ;
    ಪೂರ್ಣಾಂಕ frequency;
};

ರಚನೆ DetailedTiming
{
    ಪೂರ್ಣಾಂಕ pixel_clock;
    ಪೂರ್ಣಾಂಕ h_addr;
    ಪೂರ್ಣಾಂಕ h_blank;
    ಪೂರ್ಣಾಂಕ h_sync;
    ಪೂರ್ಣಾಂಕ h_front_porch;
    ಪೂರ್ಣಾಂಕ v_addr;
    ಪೂರ್ಣಾಂಕ v_blank;
    ಪೂರ್ಣಾಂಕ v_sync;
    ಪೂರ್ಣಾಂಕ v_front_porch;
    ಪೂರ್ಣಾಂಕ ಅಗಲ_mm;
    ಪೂರ್ಣಾಂಕ ಎತ್ತರ_mm;
    ಪೂರ್ಣಾಂಕ ಬಲ_border;
    ಪೂರ್ಣಾಂಕ ತುದಿ_border;
    ಪೂರ್ಣಾಂಕ interlaced;
    StereoType stereo;

    ಪೂರ್ಣಾಂಕ digital_sync;
    ಒಕ್ಕೂಟ
    {
        ರಚನೆ
        {
            ಪೂರ್ಣಾಂಕ bipolar;
            ಪೂರ್ಣಾಂಕ serrations;
            ಪೂರ್ಣಾಂಕ sync_on_green;
        } analog;

        ರಚನೆ
        {
            ಪೂರ್ಣಾಂಕ ಸಂಯುಕ್ತ;
            ಪೂರ್ಣಾಂಕ serrations;
            ಪೂರ್ಣಾಂಕ negative_vsync;
            ಪೂರ್ಣಾಂಕ negative_hsync;
        } digital;
    } ad;
};

ರಚನೆ MonitorInfo
{
    ಪೂರ್ಣಾಂಕ checksum;
    ಅಕ್ಷರ manufacturer_ಸಂಕೇತ[4];
    ಪೂರ್ಣಾಂಕ ಗುಣಲಬ್ಧ_ಸಂಕೇತ;
    ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ serial_ಸಂಖ್ಯೆ;

    ಪೂರ್ಣಾಂಕ production_week; // -1 if not specified
    ಪೂರ್ಣಾಂಕ production_year; // -1 if not specified
    ಪೂರ್ಣಾಂಕ model_year;      // -1 if not specified

    ಪೂರ್ಣಾಂಕ major_ಆವೃತ್ತಿ;
    ಪೂರ್ಣಾಂಕ minor_ಆವೃತ್ತಿ;

    ಪೂರ್ಣಾಂಕ is_digital;

    ಒಕ್ಕೂಟ
    {
        ರಚನೆ
        {
            ಪೂರ್ಣಾಂಕ ಬಿಟ್ಟುಗಳು_ಪ್ರತಿ_primary;
            Interface interface;
            ಪೂರ್ಣಾಂಕ rgb444;
            ಪೂರ್ಣಾಂಕ ycrcb444;
            ಪೂರ್ಣಾಂಕ ycrcb422;
        } digital;

        ರಚನೆ
        {
            ದ್ವಿಗುಣ video_signal_level;
            ದ್ವಿಗುಣ sync_signal_level;
            ದ್ವಿಗುಣ ಒಟ್ಟು_signal_level;

            ಪೂರ್ಣಾಂಕ blank_ಗಮ್ಯ_black;

            ಪೂರ್ಣಾಂಕ separate_hv_sync;
            ಪೂರ್ಣಾಂಕ ಸಂಯುಕ್ತ_sync_on_h;
            ಪೂರ್ಣಾಂಕ ಸಂಯುಕ್ತ_sync_on_green;
            ಪೂರ್ಣಾಂಕ serration_on_vsync;
            ColorType color_type;
        } analog;
    } ad;

    ಪೂರ್ಣಾಂಕ ಅಗಲ_mm;        // -1 if not specified
    ಪೂರ್ಣಾಂಕ ಎತ್ತರ_mm;       // -1 if not specified
    ದ್ವಿಗುಣ aspect_ಅನುಪಾತ; // -1.0 if not specififed

    ದ್ವಿಗುಣ gamma; // -1.0 if not specified

    ಪೂರ್ಣಾಂಕ standby;
    ಪೂರ್ಣಾಂಕ suspend;
    ಪೂರ್ಣಾಂಕ ಸಕ್ರಿಯ_off;

    ಪೂರ್ಣಾಂಕ srgb_is_standard;
    ಪೂರ್ಣಾಂಕ preferred_timing_includes_native;
    ಪೂರ್ಣಾಂಕ continuous_frequency;

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
    ದ್ವಿಗುಣ max_ಚೌಕಟ್ಟು_ಸರಾಸರಿ_ಮೌಲ್ಯ_luminance;

    Timing established[24]; // Terminated by 0x0x0
    Timing standard[8];

    ಪೂರ್ಣಾಂಕ n_detailed_timings;
    DetailedTiming detailed_timings[4]; /* If monitor has a preferred
                                         * mode, it is the first one
                                         * (whether it has, is
                                         * determined by the
                                         * preferred_timing_includes
                                         * bit.
                                         */

    // Optional product description
    ಅಕ್ಷರ dsc_serial_ಸಂಖ್ಯೆ[14];
    ಅಕ್ಷರ dsc_ಗುಣಲಬ್ಧ_name[14];
    ಅಕ್ಷರ dsc_string[14]; // Unspecified ASCII data
};

MonitorInfo *decode_edid(ಸ್ಥಿರಾಂಕ uchar *ದತ್ತಾಂಶ, size_t ಗಾತ್ರ_2);
ಶೂನ್ಯ dump_monitor_info(MonitorInfo *info);
ಅಕ್ಷರ *make_display_name(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *output_name,
                        ಸ್ಥಿರಾಂಕ MonitorInfo *info);
