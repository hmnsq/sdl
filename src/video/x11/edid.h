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

قسمتعریف غیرعلامتی حرف uchar;
قسمتعریف ساخت MonitorInfo MonitorInfo;
قسمتعریف ساخت Timing Timing;
قسمتعریف ساخت DetailedTiming DetailedTiming;

قسمتعریف شمار
{
    UNDEFINED,
    DVI,
    HDMI_A,
    HDMI_B,
    MDDI,
    DISPLAY_پورٹ
} Interface;

قسمتعریف شمار
{
    UNDEFINED_COLOR,
    MONOCHROME,
    RGB,
    OTHER_COLOR
} ColorType;

قسمتعریف شمار
{
    NO_STEREO,
    میدان_دایاں,
    میدان_بایاں,
    TWO_WAY_دایاں_ON_EVEN,
    TWO_WAY_بایاں_ON_EVEN,
    FOUR_WAY_INTERLEAVED,
    SIDE_BY_SIDE
} StereoType;

ساخت Timing
{
    صحیح چوڑائی;
    صحیح اونچائی;
    صحیح frequency;
};

ساخت DetailedTiming
{
    صحیح pixel_clock;
    صحیح h_addr;
    صحیح h_blank;
    صحیح h_sync;
    صحیح h_front_porch;
    صحیح v_addr;
    صحیح v_blank;
    صحیح v_sync;
    صحیح v_front_porch;
    صحیح چوڑائی_mm;
    صحیح اونچائی_mm;
    صحیح دایاں_border;
    صحیح چوٹی_border;
    صحیح interlaced;
    StereoType stereo;

    صحیح digital_sync;
    اتحاد
    {
        ساخت
        {
            صحیح bipolar;
            صحیح serrations;
            صحیح sync_on_green;
        } analog;

        ساخت
        {
            صحیح مرکب;
            صحیح serrations;
            صحیح negative_vsync;
            صحیح negative_hsync;
        } digital;
    } ad;
};

ساخت MonitorInfo
{
    صحیح checksum;
    حرف manufacturer_رمز[4];
    صحیح حاصل_ضرب_رمز;
    غیرعلامتی صحیح serial_نمبر;

    صحیح production_week; // -1 if not specified
    صحیح production_year; // -1 if not specified
    صحیح model_year;      // -1 if not specified

    صحیح major_نسخہ;
    صحیح minor_نسخہ;

    صحیح is_digital;

    اتحاد
    {
        ساخت
        {
            صحیح بٹ_فی_primary;
            Interface interface;
            صحیح rgb444;
            صحیح ycrcb444;
            صحیح ycrcb422;
        } digital;

        ساخت
        {
            دوہرا video_signal_level;
            دوہرا sync_signal_level;
            دوہرا کل_signal_level;

            صحیح blank_مقصد_black;

            صحیح separate_hv_sync;
            صحیح مرکب_sync_on_h;
            صحیح مرکب_sync_on_green;
            صحیح serration_on_vsync;
            ColorType color_type;
        } analog;
    } ad;

    صحیح چوڑائی_mm;        // -1 if not specified
    صحیح اونچائی_mm;       // -1 if not specified
    دوہرا aspect_تناسب; // -1.0 if not specififed

    دوہرا gamma; // -1.0 if not specified

    صحیح standby;
    صحیح suspend;
    صحیح فعال_off;

    صحیح srgb_is_standard;
    صحیح preferred_timing_includes_native;
    صحیح continuous_frequency;

    دوہرا red_x;
    دوہرا red_y;
    دوہرا green_x;
    دوہرا green_y;
    دوہرا blue_x;
    دوہرا blue_y;
    دوہرا white_x;
    دوہرا white_y;

    دوہرا min_luminance;
    دوہرا max_luminance;
    دوہرا max_چوکھٹا_اوسط_قدر_luminance;

    Timing established[24]; // Terminated by 0x0x0
    Timing standard[8];

    صحیح n_detailed_timings;
    DetailedTiming detailed_timings[4]; /* If monitor has a preferred
                                         * mode, it is the first one
                                         * (whether it has, is
                                         * determined by the
                                         * preferred_timing_includes
                                         * bit.
                                         */

    // Optional product description
    حرف dsc_serial_نمبر[14];
    حرف dsc_حاصل_ضرب_name[14];
    حرف dsc_string[14]; // Unspecified ASCII data
};

MonitorInfo *decode_edid(ثابت uchar *ڈیٹا, size_t سائز);
خالی dump_monitor_info(MonitorInfo *info);
حرف *make_display_name(ثابت حرف *output_name,
                        ثابت MonitorInfo *info);
