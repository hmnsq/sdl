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

प्रकारनिर्देश अचिन्हित वर्ण uchar;
प्रकारनिर्देश संरचना MonitorInfo MonitorInfo;
प्रकारनिर्देश संरचना Timing Timing;
प्रकारनिर्देश संरचना DetailedTiming DetailedTiming;

प्रकारनिर्देश गणना
{
    UNDEFINED,
    DVI,
    HDMI_A,
    HDMI_B,
    MDDI,
    DISPLAY_PORT
} Interface;

प्रकारनिर्देश गणना
{
    UNDEFINED_COLOR,
    MONOCHROME,
    RGB,
    OTHER_COLOR
} ColorType;

प्रकारनिर्देश गणना
{
    NO_STEREO,
    FIELD_दायाँ,
    FIELD_बायाँ,
    TWO_WAY_दायाँ_ON_EVEN,
    TWO_WAY_बायाँ_ON_EVEN,
    FOUR_WAY_INTERLEAVED,
    SIDE_BY_SIDE
} StereoType;

संरचना Timing
{
    पूर्णाङ्क width;
    पूर्णाङ्क height;
    पूर्णाङ्क frequency;
};

संरचना DetailedTiming
{
    पूर्णाङ्क pixel_clock;
    पूर्णाङ्क h_addr;
    पूर्णाङ्क h_blank;
    पूर्णाङ्क h_sync;
    पूर्णाङ्क h_front_porch;
    पूर्णाङ्क v_addr;
    पूर्णाङ्क v_blank;
    पूर्णाङ्क v_sync;
    पूर्णाङ्क v_front_porch;
    पूर्णाङ्क width_mm;
    पूर्णाङ्क height_mm;
    पूर्णाङ्क दायाँ_border;
    पूर्णाङ्क शीर्ष_border;
    पूर्णाङ्क interlaced;
    StereoType stereo;

    पूर्णाङ्क digital_sync;
    सङ्घ
    {
        संरचना
        {
            पूर्णाङ्क bipolar;
            पूर्णाङ्क serrations;
            पूर्णाङ्क sync_on_green;
        } analog;

        संरचना
        {
            पूर्णाङ्क composite;
            पूर्णाङ्क serrations;
            पूर्णाङ्क negative_vsync;
            पूर्णाङ्क negative_hsync;
        } digital;
    } ad;
};

संरचना MonitorInfo
{
    पूर्णाङ्क checksum;
    वर्ण manufacturer_code[4];
    पूर्णाङ्क product_code;
    अचिन्हित पूर्णाङ्क serial_संख्या;

    पूर्णाङ्क production_week; // -1 if not specified
    पूर्णाङ्क production_year; // -1 if not specified
    पूर्णाङ्क model_year;      // -1 if not specified

    पूर्णाङ्क major_version;
    पूर्णाङ्क minor_version;

    पूर्णाङ्क is_digital;

    सङ्घ
    {
        संरचना
        {
            पूर्णाङ्क bits_per_primary;
            Interface interface;
            पूर्णाङ्क rgb444;
            पूर्णाङ्क ycrcb444;
            पूर्णाङ्क ycrcb422;
        } digital;

        संरचना
        {
            द्विगुण video_signal_level;
            द्विगुण sync_signal_level;
            द्विगुण total_signal_level;

            पूर्णाङ्क blank_to_black;

            पूर्णाङ्क separate_hv_sync;
            पूर्णाङ्क composite_sync_on_h;
            पूर्णाङ्क composite_sync_on_green;
            पूर्णाङ्क serration_on_vsync;
            ColorType color_type;
        } analog;
    } ad;

    पूर्णाङ्क width_mm;        // -1 if not specified
    पूर्णाङ्क height_mm;       // -1 if not specified
    द्विगुण aspect_ratio; // -1.0 if not specififed

    द्विगुण gamma; // -1.0 if not specified

    पूर्णाङ्क standby;
    पूर्णाङ्क suspend;
    पूर्णाङ्क active_off;

    पूर्णाङ्क srgb_is_standard;
    पूर्णाङ्क preferred_timing_includes_native;
    पूर्णाङ्क continuous_frequency;

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

    पूर्णाङ्क n_detailed_timings;
    DetailedTiming detailed_timings[4]; /* If monitor has a preferred
                                         * mode, it is the first one
                                         * (whether it has, is
                                         * determined by the
                                         * preferred_timing_includes
                                         * bit.
                                         */

    // Optional product description
    वर्ण dsc_serial_संख्या[14];
    वर्ण dsc_product_name[14];
    वर्ण dsc_string[14]; // Unspecified ASCII data
};

MonitorInfo *decode_edid(ध्रुव uchar *data, माप_प्रकार size);
शून्य dump_monitor_info(MonitorInfo *info);
वर्ण *make_display_name(ध्रुव वर्ण *output_name,
                        ध्रुव MonitorInfo *info);
