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

రకనిర్వచనం గుర్తులేని అక్షరం uchar;
రకనిర్వచనం నిర్మాణం MonitorInfo MonitorInfo;
రకనిర్వచనం నిర్మాణం Timing Timing;
రకనిర్వచనం నిర్మాణం DetailedTiming DetailedTiming;

రకనిర్వచనం గణన
{
    UNDEFINED,
    DVI,
    HDMI_A,
    HDMI_B,
    MDDI,
    DISPLAY_పోర్టు
} Interface;

రకనిర్వచనం గణన
{
    UNDEFINED_COLOR,
    MONOCHROME,
    RGB,
    OTHER_COLOR
} ColorType;

రకనిర్వచనం గణన
{
    NO_STEREO,
    క్షేత్రం_కుడి,
    క్షేత్రం_ఎడమ,
    TWO_WAY_కుడి_ON_EVEN,
    TWO_WAY_ఎడమ_ON_EVEN,
    FOUR_WAY_INTERLEAVED,
    SIDE_BY_SIDE
} StereoType;

నిర్మాణం Timing
{
    పూర్ణాంకం వెడల్పు;
    పూర్ణాంకం ఎత్తు;
    పూర్ణాంకం frequency;
};

నిర్మాణం DetailedTiming
{
    పూర్ణాంకం pixel_clock;
    పూర్ణాంకం h_addr;
    పూర్ణాంకం h_blank;
    పూర్ణాంకం h_sync;
    పూర్ణాంకం h_front_porch;
    పూర్ణాంకం v_addr;
    పూర్ణాంకం v_blank;
    పూర్ణాంకం v_sync;
    పూర్ణాంకం v_front_porch;
    పూర్ణాంకం వెడల్పు_mm;
    పూర్ణాంకం ఎత్తు_mm;
    పూర్ణాంకం కుడి_border;
    పూర్ణాంకం శిఖరం_border;
    పూర్ణాంకం interlaced;
    StereoType stereo;

    పూర్ణాంకం digital_sync;
    సంఘం
    {
        నిర్మాణం
        {
            పూర్ణాంకం bipolar;
            పూర్ణాంకం serrations;
            పూర్ణాంకం sync_on_green;
        } analog;

        నిర్మాణం
        {
            పూర్ణాంకం సంయుక్త;
            పూర్ణాంకం serrations;
            పూర్ణాంకం negative_vsync;
            పూర్ణాంకం negative_hsync;
        } digital;
    } ad;
};

నిర్మాణం MonitorInfo
{
    పూర్ణాంకం checksum;
    అక్షరం manufacturer_సంకేతం[4];
    పూర్ణాంకం లబ్ధం_సంకేతం;
    గుర్తులేని పూర్ణాంకం serial_సంఖ్య;

    పూర్ణాంకం production_week; // -1 if not specified
    పూర్ణాంకం production_year; // -1 if not specified
    పూర్ణాంకం model_year;      // -1 if not specified

    పూర్ణాంకం major_సంస్కరణ;
    పూర్ణాంకం minor_సంస్కరణ;

    పూర్ణాంకం is_digital;

    సంఘం
    {
        నిర్మాణం
        {
            పూర్ణాంకం బిట్లు_చొప్పున_primary;
            Interface interface;
            పూర్ణాంకం rgb444;
            పూర్ణాంకం ycrcb444;
            పూర్ణాంకం ycrcb422;
        } digital;

        నిర్మాణం
        {
            ద్విగుణ video_signal_level;
            ద్విగుణ sync_signal_level;
            ద్విగుణ మొత్తం_signal_level;

            పూర్ణాంకం blank_గమ్యం_black;

            పూర్ణాంకం separate_hv_sync;
            పూర్ణాంకం సంయుక్త_sync_on_h;
            పూర్ణాంకం సంయుక్త_sync_on_green;
            పూర్ణాంకం serration_on_vsync;
            ColorType color_type;
        } analog;
    } ad;

    పూర్ణాంకం వెడల్పు_mm;        // -1 if not specified
    పూర్ణాంకం ఎత్తు_mm;       // -1 if not specified
    ద్విగుణ aspect_నిష్పత్తి; // -1.0 if not specififed

    ద్విగుణ gamma; // -1.0 if not specified

    పూర్ణాంకం standby;
    పూర్ణాంకం suspend;
    పూర్ణాంకం చురుకైన_off;

    పూర్ణాంకం srgb_is_standard;
    పూర్ణాంకం preferred_timing_includes_native;
    పూర్ణాంకం continuous_frequency;

    ద్విగుణ red_x;
    ద్విగుణ red_y;
    ద్విగుణ green_x;
    ద్విగుణ green_y;
    ద్విగుణ blue_x;
    ద్విగుణ blue_y;
    ద్విగుణ white_x;
    ద్విగుణ white_y;

    ద్విగుణ min_luminance;
    ద్విగుణ max_luminance;
    ద్విగుణ max_చట్రం_సరాసరి_luminance;

    Timing established[24]; // Terminated by 0x0x0
    Timing standard[8];

    పూర్ణాంకం n_detailed_timings;
    DetailedTiming detailed_timings[4]; /* If monitor has a preferred
                                         * mode, it is the first one
                                         * (whether it has, is
                                         * determined by the
                                         * preferred_timing_includes
                                         * bit.
                                         */

    // Optional product description
    అక్షరం dsc_serial_సంఖ్య[14];
    అక్షరం dsc_లబ్ధం_name[14];
    అక్షరం dsc_string[14]; // Unspecified ASCII data
};

MonitorInfo *decode_edid(స్థిరరాశి uchar *దత్తాంశం, size_t కొలత);
శూన్య dump_monitor_info(MonitorInfo *info);
అక్షరం *make_display_name(స్థిరరాశి అక్షరం *output_name,
                        స్థిరరాశి MonitorInfo *info);
