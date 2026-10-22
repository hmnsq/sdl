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

प्रकारव्याख्या अचिन्हित अक्षर uchar;
प्रकारव्याख्या संरचना MonitorInfo MonitorInfo;
प्रकारव्याख्या संरचना Timing Timing;
प्रकारव्याख्या संरचना DetailedTiming DetailedTiming;

प्रकारव्याख्या गणना
{
    UNDEFINED,
    DVI,
    HDMI_A,
    HDMI_B,
    MDDI,
    DISPLAY_PORT
} Interface;

प्रकारव्याख्या गणना
{
    UNDEFINED_COLOR,
    MONOCHROME,
    RGB,
    OTHER_COLOR
} ColorType;

प्रकारव्याख्या गणना
{
    NO_STEREO,
    FIELD_उजवा,
    FIELD_डावा,
    TWO_WAY_उजवा_ON_EVEN,
    TWO_WAY_डावा_ON_EVEN,
    FOUR_WAY_INTERLEAVED,
    SIDE_BY_SIDE
} StereoType;

संरचना Timing
{
    पूर्णांक width;
    पूर्णांक height;
    पूर्णांक frequency;
};

संरचना DetailedTiming
{
    पूर्णांक pixel_clock;
    पूर्णांक h_addr;
    पूर्णांक h_blank;
    पूर्णांक h_sync;
    पूर्णांक h_front_porch;
    पूर्णांक v_addr;
    पूर्णांक v_blank;
    पूर्णांक v_sync;
    पूर्णांक v_front_porch;
    पूर्णांक width_mm;
    पूर्णांक height_mm;
    पूर्णांक उजवा_border;
    पूर्णांक शीर्ष_border;
    पूर्णांक interlaced;
    StereoType stereo;

    पूर्णांक digital_sync;
    संघ
    {
        संरचना
        {
            पूर्णांक bipolar;
            पूर्णांक serrations;
            पूर्णांक sync_on_green;
        } analog;

        संरचना
        {
            पूर्णांक composite;
            पूर्णांक serrations;
            पूर्णांक negative_vsync;
            पूर्णांक negative_hsync;
        } digital;
    } ad;
};

संरचना MonitorInfo
{
    पूर्णांक checksum;
    अक्षर manufacturer_code[4];
    पूर्णांक product_code;
    अचिन्हित पूर्णांक serial_संख्या;

    पूर्णांक production_week; // -1 if not specified
    पूर्णांक production_year; // -1 if not specified
    पूर्णांक model_year;      // -1 if not specified

    पूर्णांक major_version;
    पूर्णांक minor_version;

    पूर्णांक is_digital;

    संघ
    {
        संरचना
        {
            पूर्णांक bits_per_primary;
            Interface interface;
            पूर्णांक rgb444;
            पूर्णांक ycrcb444;
            पूर्णांक ycrcb422;
        } digital;

        संरचना
        {
            द्विगुण video_signal_level;
            द्विगुण sync_signal_level;
            द्विगुण total_signal_level;

            पूर्णांक blank_to_black;

            पूर्णांक separate_hv_sync;
            पूर्णांक composite_sync_on_h;
            पूर्णांक composite_sync_on_green;
            पूर्णांक serration_on_vsync;
            ColorType color_type;
        } analog;
    } ad;

    पूर्णांक width_mm;        // -1 if not specified
    पूर्णांक height_mm;       // -1 if not specified
    द्विगुण aspect_ratio; // -1.0 if not specififed

    द्विगुण gamma; // -1.0 if not specified

    पूर्णांक standby;
    पूर्णांक suspend;
    पूर्णांक active_off;

    पूर्णांक srgb_is_standard;
    पूर्णांक preferred_timing_includes_native;
    पूर्णांक continuous_frequency;

    द्विगुण red_x;
    द्विगुण red_y;
    द्विगुण green_x;
    द्विगुण green_y;
    द्विगुण blue_x;
    द्विगुण blue_y;
    द्विगुण white_x;
    द्विगुण white_y;

    द्विगुण min_luminance;
    द्विगुण max_luminance;
    द्विगुण max_frame_average_luminance;

    Timing established[24]; // Terminated by 0x0x0
    Timing standard[8];

    पूर्णांक n_detailed_timings;
    DetailedTiming detailed_timings[4]; /* If monitor has a preferred
                                         * mode, it is the first one
                                         * (whether it has, is
                                         * determined by the
                                         * preferred_timing_includes
                                         * bit.
                                         */

    // Optional product description
    अक्षर dsc_serial_संख्या[14];
    अक्षर dsc_product_name[14];
    अक्षर dsc_string[14]; // Unspecified ASCII data
};

MonitorInfo *decode_edid(स्थिरांक uchar *data, माप_प्रकार size);
शून्य dump_monitor_info(MonitorInfo *info);
अक्षर *make_display_name(स्थिरांक अक्षर *output_name,
                        स्थिरांक MonitorInfo *info);
