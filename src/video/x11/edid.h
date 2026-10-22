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

ପ୍ରକାରବ୍ୟାଖ୍ୟା unsigned ଅକ୍ଷର uchar;
ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା MonitorInfo MonitorInfo;
ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା Timing Timing;
ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା DetailedTiming DetailedTiming;

ପ୍ରକାରବ୍ୟାଖ୍ୟା ଗଣନା
{
    UNDEFINED,
    DVI,
    HDMI_A,
    HDMI_B,
    MDDI,
    DISPLAY_PORT
} Interface;

ପ୍ରକାରବ୍ୟାଖ୍ୟା ଗଣନା
{
    UNDEFINED_COLOR,
    MONOCHROME,
    RGB,
    OTHER_COLOR
} ColorType;

ପ୍ରକାରବ୍ୟାଖ୍ୟା ଗଣନା
{
    NO_STEREO,
    FIELD_ଡାହାଣ,
    FIELD_ବାମ,
    TWO_WAY_ଡାହାଣ_ON_EVEN,
    TWO_WAY_ବାମ_ON_EVEN,
    FOUR_WAY_INTERLEAVED,
    SIDE_BY_SIDE
} StereoType;

ସଂରଚନା Timing
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା width;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା height;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା frequency;
};

ସଂରଚନା DetailedTiming
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା pixel_clock;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା h_addr;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା h_blank;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା h_sync;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା h_front_porch;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା v_addr;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା v_blank;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା v_sync;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା v_front_porch;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା width_mm;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା height_mm;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ଡାହାଣ_border;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ଶୀର୍ଷ_border;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା interlaced;
    StereoType stereo;

    ପୂର୍ଣ୍ଣସଂଖ୍ୟା digital_sync;
    ସଂଘ
    {
        ସଂରଚନା
        {
            ପୂର୍ଣ୍ଣସଂଖ୍ୟା bipolar;
            ପୂର୍ଣ୍ଣସଂଖ୍ୟା serrations;
            ପୂର୍ଣ୍ଣସଂଖ୍ୟା sync_on_green;
        } analog;

        ସଂରଚନା
        {
            ପୂର୍ଣ୍ଣସଂଖ୍ୟା composite;
            ପୂର୍ଣ୍ଣସଂଖ୍ୟା serrations;
            ପୂର୍ଣ୍ଣସଂଖ୍ୟା negative_vsync;
            ପୂର୍ଣ୍ଣସଂଖ୍ୟା negative_hsync;
        } digital;
    } ad;
};

ସଂରଚନା MonitorInfo
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା checksum;
    ଅକ୍ଷର manufacturer_code[4];
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା product_code;
    unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା serial_ସଂଖ୍ୟା;

    ପୂର୍ଣ୍ଣସଂଖ୍ୟା production_week; // -1 if not specified
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା production_year; // -1 if not specified
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା model_year;      // -1 if not specified

    ପୂର୍ଣ୍ଣସଂଖ୍ୟା major_version;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା minor_version;

    ପୂର୍ଣ୍ଣସଂଖ୍ୟା is_digital;

    ସଂଘ
    {
        ସଂରଚନା
        {
            ପୂର୍ଣ୍ଣସଂଖ୍ୟା bits_per_primary;
            Interface interface;
            ପୂର୍ଣ୍ଣସଂଖ୍ୟା rgb444;
            ପୂର୍ଣ୍ଣସଂଖ୍ୟା ycrcb444;
            ପୂର୍ଣ୍ଣସଂଖ୍ୟା ycrcb422;
        } digital;

        ସଂରଚନା
        {
            ଦ୍ୱିଗୁଣ video_signal_level;
            ଦ୍ୱିଗୁଣ sync_signal_level;
            ଦ୍ୱିଗୁଣ total_signal_level;

            ପୂର୍ଣ୍ଣସଂଖ୍ୟା blank_to_black;

            ପୂର୍ଣ୍ଣସଂଖ୍ୟା separate_hv_sync;
            ପୂର୍ଣ୍ଣସଂଖ୍ୟା composite_sync_on_h;
            ପୂର୍ଣ୍ଣସଂଖ୍ୟା composite_sync_on_green;
            ପୂର୍ଣ୍ଣସଂଖ୍ୟା serration_on_vsync;
            ColorType color_type;
        } analog;
    } ad;

    ପୂର୍ଣ୍ଣସଂଖ୍ୟା width_mm;        // -1 if not specified
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା height_mm;       // -1 if not specified
    ଦ୍ୱିଗୁଣ aspect_ratio; // -1.0 if not specififed

    ଦ୍ୱିଗୁଣ gamma; // -1.0 if not specified

    ପୂର୍ଣ୍ଣସଂଖ୍ୟା standby;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା suspend;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା active_off;

    ପୂର୍ଣ୍ଣସଂଖ୍ୟା srgb_is_standard;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା preferred_timing_includes_native;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା continuous_frequency;

    ଦ୍ୱିଗୁଣ red_x;
    ଦ୍ୱିଗୁଣ red_y;
    ଦ୍ୱିଗୁଣ green_x;
    ଦ୍ୱିଗୁଣ green_y;
    ଦ୍ୱିଗୁଣ blue_x;
    ଦ୍ୱିଗୁଣ blue_y;
    ଦ୍ୱିଗୁଣ white_x;
    ଦ୍ୱିଗୁଣ white_y;

    ଦ୍ୱିଗୁଣ min_luminance;
    ଦ୍ୱିଗୁଣ max_luminance;
    ଦ୍ୱିଗୁଣ max_frame_average_luminance;

    Timing established[24]; // Terminated by 0x0x0
    Timing standard[8];

    ପୂର୍ଣ୍ଣସଂଖ୍ୟା n_detailed_timings;
    DetailedTiming detailed_timings[4]; /* If monitor has a preferred
                                         * mode, it is the first one
                                         * (whether it has, is
                                         * determined by the
                                         * preferred_timing_includes
                                         * bit.
                                         */

    // Optional product description
    ଅକ୍ଷର dsc_serial_ସଂଖ୍ୟା[14];
    ଅକ୍ଷର dsc_product_name[14];
    ଅକ୍ଷର dsc_string[14]; // Unspecified ASCII data
};

MonitorInfo *decode_edid(ଅଚଳ uchar *data, size_t size);
ଶୂନ୍ୟ dump_monitor_info(MonitorInfo *info);
ଅକ୍ଷର *make_display_name(ଅଚଳ ଅକ୍ଷର *output_name,
                        ଅଚଳ MonitorInfo *info);
