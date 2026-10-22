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

प्रकार अचिन्हित अक्षर uchar;
प्रकार काष्ठा MonitorInfo MonitorInfo;
प्रकार काष्ठा Timing Timing;
प्रकार काष्ठा DetailedTiming DetailedTiming;

प्रकार क्रमागत
{
    UNDEFINED,
    DVI,
    HDMI_A,
    HDMI_B,
    MDDI,
    DISPLAY_PORT
} Interface;

प्रकार क्रमागत
{
    UNDEFINED_COLOR,
    MONOCHROME,
    RGB,
    OTHER_COLOR
} ColorType;

प्रकार क्रमागत
{
    NO_STEREO,
    FIELD_दायाँ,
    FIELD_बायाँ,
    TWO_WAY_दायाँ_ON_EVEN,
    TWO_WAY_बायाँ_ON_EVEN,
    FOUR_WAY_INTERLEAVED,
    SIDE_BY_SIDE
} StereoType;

काष्ठा Timing
{
    पूर्णांक width;
    पूर्णांक height;
    पूर्णांक frequency;
};

काष्ठा DetailedTiming
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
    पूर्णांक दायाँ_border;
    पूर्णांक शीर्ष_border;
    पूर्णांक interlaced;
    StereoType stereo;

    पूर्णांक digital_sync;
    जोड़
    {
        काष्ठा
        {
            पूर्णांक bipolar;
            पूर्णांक serrations;
            पूर्णांक sync_on_green;
        } analog;

        काष्ठा
        {
            पूर्णांक composite;
            पूर्णांक serrations;
            पूर्णांक negative_vsync;
            पूर्णांक negative_hsync;
        } digital;
    } ad;
};

काष्ठा MonitorInfo
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

    जोड़
    {
        काष्ठा
        {
            पूर्णांक bits_per_primary;
            Interface interface;
            पूर्णांक rgb444;
            पूर्णांक ycrcb444;
            पूर्णांक ycrcb422;
        } digital;

        काष्ठा
        {
            द्विगुन video_signal_level;
            द्विगुन sync_signal_level;
            द्विगुन योग_signal_level;

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
    द्विगुन aspect_ratio; // -1.0 if not specififed

    द्विगुन gamma; // -1.0 if not specified

    पूर्णांक standby;
    पूर्णांक suspend;
    पूर्णांक active_off;

    पूर्णांक srgb_is_standard;
    पूर्णांक preferred_timing_includes_native;
    पूर्णांक continuous_frequency;

    द्विगुन red_x;
    द्विगुन red_y;
    द्विगुन green_x;
    द्विगुन green_y;
    द्विगुन blue_x;
    द्विगुन blue_y;
    द्विगुन white_x;
    द्विगुन white_y;

    द्विगुन min_luminance;
    द्विगुन max_luminance;
    द्विगुन max_frame_average_luminance;

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

MonitorInfo *decode_edid(स्थिर uchar *तथ्य, माप_प्रकार आकार);
व्योम dump_monitor_info(MonitorInfo *info);
अक्षर *make_display_name(स्थिर अक्षर *output_name,
                        स्थिर MonitorInfo *info);
