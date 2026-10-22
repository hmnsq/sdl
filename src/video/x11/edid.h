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

પ્રકારવ્યાખ્યા unsigned અક્ષર uchar;
પ્રકારવ્યાખ્યા સંરચના MonitorInfo MonitorInfo;
પ્રકારવ્યાખ્યા સંરચના Timing Timing;
પ્રકારવ્યાખ્યા સંરચના DetailedTiming DetailedTiming;

પ્રકારવ્યાખ્યા ગણના
{
    UNDEFINED,
    DVI,
    HDMI_A,
    HDMI_B,
    MDDI,
    DISPLAY_PORT
} Interface;

પ્રકારવ્યાખ્યા ગણના
{
    UNDEFINED_COLOR,
    MONOCHROME,
    RGB,
    OTHER_COLOR
} ColorType;

પ્રકારવ્યાખ્યા ગણના
{
    NO_STEREO,
    FIELD_જમણું,
    FIELD_ડાબું,
    TWO_WAY_જમણું_ON_EVEN,
    TWO_WAY_ડાબું_ON_EVEN,
    FOUR_WAY_INTERLEAVED,
    SIDE_BY_SIDE
} StereoType;

સંરચના Timing
{
    પૂર્ણાંક width;
    પૂર્ણાંક height;
    પૂર્ણાંક frequency;
};

સંરચના DetailedTiming
{
    પૂર્ણાંક pixel_clock;
    પૂર્ણાંક h_addr;
    પૂર્ણાંક h_blank;
    પૂર્ણાંક h_sync;
    પૂર્ણાંક h_front_porch;
    પૂર્ણાંક v_addr;
    પૂર્ણાંક v_blank;
    પૂર્ણાંક v_sync;
    પૂર્ણાંક v_front_porch;
    પૂર્ણાંક width_mm;
    પૂર્ણાંક height_mm;
    પૂર્ણાંક જમણું_border;
    પૂર્ણાંક ટોચ_border;
    પૂર્ણાંક interlaced;
    StereoType stereo;

    પૂર્ણાંક digital_sync;
    સંઘ
    {
        સંરચના
        {
            પૂર્ણાંક bipolar;
            પૂર્ણાંક serrations;
            પૂર્ણાંક sync_on_green;
        } analog;

        સંરચના
        {
            પૂર્ણાંક composite;
            પૂર્ણાંક serrations;
            પૂર્ણાંક negative_vsync;
            પૂર્ણાંક negative_hsync;
        } digital;
    } ad;
};

સંરચના MonitorInfo
{
    પૂર્ણાંક checksum;
    અક્ષર manufacturer_code[4];
    પૂર્ણાંક product_code;
    unsigned પૂર્ણાંક serial_સંખ્યા;

    પૂર્ણાંક production_week; // -1 if not specified
    પૂર્ણાંક production_year; // -1 if not specified
    પૂર્ણાંક model_year;      // -1 if not specified

    પૂર્ણાંક major_version;
    પૂર્ણાંક minor_version;

    પૂર્ણાંક is_digital;

    સંઘ
    {
        સંરચના
        {
            પૂર્ણાંક bits_per_primary;
            Interface interface;
            પૂર્ણાંક rgb444;
            પૂર્ણાંક ycrcb444;
            પૂર્ણાંક ycrcb422;
        } digital;

        સંરચના
        {
            દ્વિગુણ video_signal_level;
            દ્વિગુણ sync_signal_level;
            દ્વિગુણ total_signal_level;

            પૂર્ણાંક blank_to_black;

            પૂર્ણાંક separate_hv_sync;
            પૂર્ણાંક composite_sync_on_h;
            પૂર્ણાંક composite_sync_on_green;
            પૂર્ણાંક serration_on_vsync;
            ColorType color_type;
        } analog;
    } ad;

    પૂર્ણાંક width_mm;        // -1 if not specified
    પૂર્ણાંક height_mm;       // -1 if not specified
    દ્વિગુણ aspect_ratio; // -1.0 if not specififed

    દ્વિગુણ gamma; // -1.0 if not specified

    પૂર્ણાંક standby;
    પૂર્ણાંક suspend;
    પૂર્ણાંક active_off;

    પૂર્ણાંક srgb_is_standard;
    પૂર્ણાંક preferred_timing_includes_native;
    પૂર્ણાંક continuous_frequency;

    દ્વિગુણ red_x;
    દ્વિગુણ red_y;
    દ્વિગુણ green_x;
    દ્વિગુણ green_y;
    દ્વિગુણ blue_x;
    દ્વિગુણ blue_y;
    દ્વિગુણ white_x;
    દ્વિગુણ white_y;

    દ્વિગુણ min_luminance;
    દ્વિગુણ max_luminance;
    દ્વિગુણ max_frame_average_luminance;

    Timing established[24]; // Terminated by 0x0x0
    Timing standard[8];

    પૂર્ણાંક n_detailed_timings;
    DetailedTiming detailed_timings[4]; /* If monitor has a preferred
                                         * mode, it is the first one
                                         * (whether it has, is
                                         * determined by the
                                         * preferred_timing_includes
                                         * bit.
                                         */

    // Optional product description
    અક્ષર dsc_serial_સંખ્યા[14];
    અક્ષર dsc_product_name[14];
    અક્ષર dsc_string[14]; // Unspecified ASCII data
};

MonitorInfo *decode_edid(અચલ uchar *data, size_t size);
શૂન્ય dump_monitor_info(MonitorInfo *info);
અક્ષર *make_display_name(અચલ અક્ષર *output_name,
                        અચલ MonitorInfo *info);
