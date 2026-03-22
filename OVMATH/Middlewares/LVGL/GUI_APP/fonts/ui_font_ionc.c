/*******************************************************************************
 * Size: 16 px
 * Bpp: 1
 * Opts: --bpp 1 --size 16 --font D:/lvgl_gc/lvgl_ui_1/assets/iconfont.ttf -o D:/lvgl_gc/lvgl_ui_1/assets\ui_font_ionc.c --format lvgl -r 0xe666 -r 0xe62a -r 0xeb2a -r 0xe6bd -r 0xe9e3 -r 0xe65f -r 0xe643 --no-compress --no-prefilter
 ******************************************************************************/

#include "../ui.h"

#ifndef UI_FONT_IONC
#define UI_FONT_IONC 1
#endif

#if UI_FONT_IONC

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+E62A "" */
    0x4, 0x0, 0x30, 0x0, 0xc4, 0x2, 0x90, 0x12,
    0xa0, 0x46, 0x8f, 0x11, 0xc0, 0x0, 0x4, 0x80,
    0x0, 0x0, 0x0, 0x0, 0xc0,

    /* U+E643 "" */
    0x6, 0x30, 0xd, 0xee, 0x4, 0x1, 0x2, 0x0,
    0x81, 0x0, 0x43, 0x1e, 0x1b, 0x19, 0x87, 0x8,
    0x41, 0x84, 0x20, 0xe3, 0x30, 0xd8, 0xf0, 0xc2,
    0x0, 0x81, 0x0, 0x40, 0x84, 0x20, 0x6f, 0x70,
    0xc, 0x60,

    /* U+E65F "" */
    0x40, 0x60, 0x30, 0x8, 0x4, 0x2, 0x1, 0x1,
    0x6, 0xc, 0x18, 0x30, 0x60, 0x40,

    /* U+E666 "" */
    0x1, 0x0, 0x2, 0x0, 0xc4, 0x63, 0x8, 0x44,
    0x10, 0x50, 0x20, 0x60, 0x0, 0xc0, 0x1, 0x80,
    0x3, 0x0, 0x6, 0x0, 0x1a, 0x0, 0x24, 0x0,
    0xc4, 0x3, 0x6, 0x1c, 0x1, 0xe0,

    /* U+E6BD "" */
    0x0, 0x9c, 0x0, 0x51, 0xc, 0x8, 0x82, 0x74,
    0x40, 0x62, 0x20, 0x61, 0x10, 0x20, 0xa8, 0x10,
    0x54, 0xf8, 0x2a, 0x4, 0x15, 0x3, 0x12, 0x40,
    0xd3, 0xb1, 0x29, 0xc9, 0x82, 0xe8, 0x1, 0x8c,
    0x0, 0x7c,

    /* U+E9E3 "" */
    0x0, 0x0, 0xc0, 0xc, 0x0, 0xc0, 0x12, 0x81,
    0xe8, 0x21, 0xc2, 0x14, 0x41, 0x24, 0x22, 0x7f,
    0xe0,

    /* U+EB2A "" */
    0x31, 0xbf, 0xf8, 0x6, 0x1, 0x95, 0x60, 0x19,
    0x56, 0x1, 0xff, 0xc0
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 256, .box_w = 14, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 21, .adv_w = 271, .box_w = 17, .box_h = 16, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 55, .adv_w = 256, .box_w = 8, .box_h = 14, .ofs_x = 4, .ofs_y = -1},
    {.bitmap_index = 69, .adv_w = 256, .box_w = 15, .box_h = 16, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 99, .adv_w = 256, .box_w = 17, .box_h = 16, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 133, .adv_w = 256, .box_w = 12, .box_h = 11, .ofs_x = 2, .ofs_y = 1},
    {.bitmap_index = 150, .adv_w = 256, .box_w = 10, .box_h = 9, .ofs_x = 3, .ofs_y = 2}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/

static const uint16_t unicode_list_0[] = {
    0x0, 0x19, 0x35, 0x3c, 0x93, 0x3b9, 0x500
};

/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 58922, .range_length = 1281, .glyph_id_start = 1,
        .unicode_list = unicode_list_0, .glyph_id_ofs_list = NULL, .list_length = 7, .type = LV_FONT_FMT_TXT_CMAP_SPARSE_TINY
    }
};



/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

#if LVGL_VERSION_MAJOR == 8
/*Store all the custom data of the font*/
static  lv_font_fmt_txt_glyph_cache_t cache;
#endif

#if LVGL_VERSION_MAJOR >= 8
static const lv_font_fmt_txt_dsc_t font_dsc = {
#else
static lv_font_fmt_txt_dsc_t font_dsc = {
#endif
    .glyph_bitmap = glyph_bitmap,
    .glyph_dsc = glyph_dsc,
    .cmaps = cmaps,
    .kern_dsc = NULL,
    .kern_scale = 0,
    .cmap_num = 1,
    .bpp = 1,
    .kern_classes = 0,
    .bitmap_format = 0,
#if LVGL_VERSION_MAJOR == 8
    .cache = &cache
#endif
};



/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
#if LVGL_VERSION_MAJOR >= 8
const lv_font_t ui_font_ionc = {
#else
lv_font_t ui_font_ionc = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 16,          /*The maximum line height required by the font*/
    .base_line = 2,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = 0,
    .underline_thickness = 0,
#endif
    .dsc = &font_dsc,          /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
#if LV_VERSION_CHECK(8, 2, 0) || LVGL_VERSION_MAJOR >= 9
    .fallback = NULL,
#endif
    .user_data = NULL,
};



#endif /*#if UI_FONT_IONC*/

