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

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ uchar;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ MonitorInfo MonitorInfo;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ Timing Timing;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ DetailedTiming DetailedTiming;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ
{
    UNDEFINED,
    DVI,
    HDMI_A,
    HDMI_B,
    MDDI,
    DISPLAY_ਪੋਰਟ
} Interface;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ
{
    UNDEFINED_COLOR,
    MONOCHROME,
    RGB,
    OTHER_COLOR
} ColorType;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ
{
    NO_STEREO,
    ਖੇਤਰ_ਸੱਜਾ,
    ਖੇਤਰ_ਖੱਬਾ,
    TWO_WAY_ਸੱਜਾ_ON_EVEN,
    TWO_WAY_ਖੱਬਾ_ON_EVEN,
    FOUR_WAY_INTERLEAVED,
    SIDE_BY_SIDE
} StereoType;

ਬਣਤਰ Timing
{
    ਪੂਰਨ ਚੌੜਾਈ;
    ਪੂਰਨ ਉਚਾਈ;
    ਪੂਰਨ frequency;
};

ਬਣਤਰ DetailedTiming
{
    ਪੂਰਨ pixel_clock;
    ਪੂਰਨ h_addr;
    ਪੂਰਨ h_blank;
    ਪੂਰਨ h_sync;
    ਪੂਰਨ h_front_porch;
    ਪੂਰਨ v_addr;
    ਪੂਰਨ v_blank;
    ਪੂਰਨ v_sync;
    ਪੂਰਨ v_front_porch;
    ਪੂਰਨ ਚੌੜਾਈ_mm;
    ਪੂਰਨ ਉਚਾਈ_mm;
    ਪੂਰਨ ਸੱਜਾ_border;
    ਪੂਰਨ ਸਿਖਰ_border;
    ਪੂਰਨ interlaced;
    StereoType stereo;

    ਪੂਰਨ digital_sync;
    ਸੰਘ
    {
        ਬਣਤਰ
        {
            ਪੂਰਨ bipolar;
            ਪੂਰਨ serrations;
            ਪੂਰਨ sync_on_green;
        } analog;

        ਬਣਤਰ
        {
            ਪੂਰਨ ਸੰਯੁਕਤ;
            ਪੂਰਨ serrations;
            ਪੂਰਨ negative_vsync;
            ਪੂਰਨ negative_hsync;
        } digital;
    } ad;
};

ਬਣਤਰ MonitorInfo
{
    ਪੂਰਨ checksum;
    ਅੱਖਰ manufacturer_ਕੋਡ[4];
    ਪੂਰਨ ਗੁਣਨਫਲ_ਕੋਡ;
    ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ serial_ਸੰਖਿਆ;

    ਪੂਰਨ production_week; // -1 if not specified
    ਪੂਰਨ production_year; // -1 if not specified
    ਪੂਰਨ model_year;      // -1 if not specified

    ਪੂਰਨ major_ਸੰਸਕਰਣ;
    ਪੂਰਨ minor_ਸੰਸਕਰਣ;

    ਪੂਰਨ is_digital;

    ਸੰਘ
    {
        ਬਣਤਰ
        {
            ਪੂਰਨ ਬਿੱਟ_ਪ੍ਰਤੀ_primary;
            Interface interface;
            ਪੂਰਨ rgb444;
            ਪੂਰਨ ycrcb444;
            ਪੂਰਨ ycrcb422;
        } digital;

        ਬਣਤਰ
        {
            ਦੁੱਗਣਾ video_signal_level;
            ਦੁੱਗਣਾ sync_signal_level;
            ਦੁੱਗਣਾ ਕੁੱਲ_signal_level;

            ਪੂਰਨ blank_ਮੰਜ਼ਿਲ_black;

            ਪੂਰਨ separate_hv_sync;
            ਪੂਰਨ ਸੰਯੁਕਤ_sync_on_h;
            ਪੂਰਨ ਸੰਯੁਕਤ_sync_on_green;
            ਪੂਰਨ serration_on_vsync;
            ColorType color_type;
        } analog;
    } ad;

    ਪੂਰਨ ਚੌੜਾਈ_mm;        // -1 if not specified
    ਪੂਰਨ ਉਚਾਈ_mm;       // -1 if not specified
    ਦੁੱਗਣਾ aspect_ਅਨੁਪਾਤ; // -1.0 if not specififed

    ਦੁੱਗਣਾ gamma; // -1.0 if not specified

    ਪੂਰਨ standby;
    ਪੂਰਨ suspend;
    ਪੂਰਨ ਸਰਗਰਮ_off;

    ਪੂਰਨ srgb_is_standard;
    ਪੂਰਨ preferred_timing_includes_native;
    ਪੂਰਨ continuous_frequency;

    ਦੁੱਗਣਾ red_x;
    ਦੁੱਗਣਾ red_y;
    ਦੁੱਗਣਾ green_x;
    ਦੁੱਗਣਾ green_y;
    ਦੁੱਗਣਾ blue_x;
    ਦੁੱਗਣਾ blue_y;
    ਦੁੱਗਣਾ white_x;
    ਦੁੱਗਣਾ white_y;

    ਦੁੱਗਣਾ min_luminance;
    ਦੁੱਗਣਾ max_luminance;
    ਦੁੱਗਣਾ max_ਚੌਖਟਾ_ਔਸਤਨ_luminance;

    Timing established[24]; // Terminated by 0x0x0
    Timing standard[8];

    ਪੂਰਨ n_detailed_timings;
    DetailedTiming detailed_timings[4]; /* If monitor has a preferred
                                         * mode, it is the first one
                                         * (whether it has, is
                                         * determined by the
                                         * preferred_timing_includes
                                         * bit.
                                         */

    // Optional product description
    ਅੱਖਰ dsc_serial_ਸੰਖਿਆ[14];
    ਅੱਖਰ dsc_ਗੁਣਨਫਲ_name[14];
    ਅੱਖਰ dsc_string[14]; // Unspecified ASCII data
};

MonitorInfo *decode_edid(ਅਚਲ uchar *ਅੰਕੜੇ, size_t ਮਾਪ);
ਖਾਲੀ dump_monitor_info(MonitorInfo *info);
ਅੱਖਰ *make_display_name(ਅਚਲ ਅੱਖਰ *output_name,
                        ਅਚਲ MonitorInfo *info);
