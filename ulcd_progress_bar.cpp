/*
 * ulcd_progress_bar.cpp
 *
 *
 *
 */

#include "ulcd_progress_bar.h"

/*
 * private defines
 *
 */


/*
 * private variables
 *
 */


/*
 * constructor
 *
 */
ulcd_progress_bar::ulcd_progress_bar(uLCD_4DLibrary* p_lcd, uint16_t foreground_color, uint16_t background_color, uint16_t x_origin, uint16_t y_origin, uint16_t width, uint16_t height, float per_cent, progress_bar_orientation_t orientation)
{
    m_lcd = p_lcd;

    rect.origin.x = x_origin;
    rect.origin.y = y_origin;
    rect.size.width = width;
    rect.size.height = height;
    m_foreground_color = foreground_color;
    m_background_color = background_color;

    m_per_cent = per_cent;

    m_orientation = orientation;

    draw_progress_bar();
}

ulcd_progress_bar::ulcd_progress_bar(uLCD_4DLibrary* p_lcd)
{
    m_lcd = p_lcd;

    rect.origin.x = 0;
    rect.origin.y = 0;
    rect.size.width = 20;
    rect.size.height = 20;
    m_foreground_color = Color::WHITE;
    m_background_color = Color::BLACK;

    m_per_cent = 0.;
    m_orientation = v_to_top;
}

ulcd_progress_bar::~ulcd_progress_bar()
{

}


/*
 * private functions
 *
 */

void ulcd_progress_bar::draw_progress_bar()
{
    switch(m_orientation)
    {
        case v_to_top:
        {
            m_lcd->gfx_draw_filled_rectangle(rect.origin.x, rect.origin.y, rect.origin.x + rect.size.width, (uint16_t)(rect.origin.y+ (rect.size.height* (1. - m_per_cent))), m_background_color);
            m_lcd->gfx_draw_filled_rectangle(rect.origin.x, (uint16_t)(rect.origin.y+ (rect.size.height* (1. - m_per_cent))), rect.origin.x + rect.size.width, rect.origin.y + rect.size.height , m_foreground_color);
            m_lcd->gfx_draw_rectangle(rect.origin.x, rect.origin.y, rect.origin.x + rect.size.width, rect.origin.y + rect.size.height , m_foreground_color);
        }
        break;
        case v_to_bottom:
        {
            m_lcd->gfx_draw_filled_rectangle(rect.origin.x, rect.origin.y, rect.origin.x + rect.size.width, (uint16_t)(rect.origin.y+ (rect.size.height* m_per_cent)), m_foreground_color);
            m_lcd->gfx_draw_filled_rectangle(rect.origin.x, (uint16_t)(rect.origin.y+ (rect.size.height* m_per_cent)), rect.origin.x + rect.size.width, rect.origin.y + rect.size.height , m_background_color);
            m_lcd->gfx_draw_rectangle(rect.origin.x, rect.origin.y, rect.origin.x + rect.size.width, rect.origin.y + rect.size.height , m_foreground_color);
        }
        break;
        case h_to_right:
        {
            m_lcd->gfx_draw_filled_rectangle(rect.origin.x, rect.origin.y, rect.origin.x + (uint16_t)(rect.size.width * m_per_cent), (rect.origin.y+ rect.size.height), m_foreground_color);
            m_lcd->gfx_draw_filled_rectangle((uint16_t)(rect.origin.x + (rect.size.width* m_per_cent)), rect.origin.y, rect.origin.x + rect.size.width, rect.origin.y + rect.size.height , m_background_color);
            m_lcd->gfx_draw_rectangle(rect.origin.x, rect.origin.y, rect.origin.x + rect.size.width, rect.origin.y + rect.size.height , m_foreground_color);
        }
        break;
        case h_to_left:
        {
            m_lcd->gfx_draw_filled_rectangle(rect.origin.x, rect.origin.y, rect.origin.x + (uint16_t)(rect.size.width * (1. - m_per_cent)), (rect.origin.y+ rect.size.height), m_background_color);
            m_lcd->gfx_draw_filled_rectangle((uint16_t)(rect.origin.x + (rect.size.width* (1. - m_per_cent))), rect.origin.y, rect.origin.x + rect.size.width, rect.origin.y + rect.size.height , m_foreground_color);
            m_lcd->gfx_draw_rectangle(rect.origin.x, rect.origin.y, rect.origin.x + rect.size.width, rect.origin.y + rect.size.height , m_foreground_color);
        }
        break;
    }
    /*m_lcd->gfx_draw_filled_rectangle(rect.origin.x, rect.origin.y, rect.origin.x + rect.size.width, (uint16_t)(rect.origin.y+ (rect.size.height* (1. - m_per_cent))), m_background_color);
    m_lcd->gfx_draw_filled_rectangle(rect.origin.x, (uint16_t)(rect.origin.y+ (rect.size.height* (1. - m_per_cent))), rect.origin.x + rect.size.width, rect.origin.y + rect.size.height , m_foreground_color);
    m_lcd->gfx_draw_rectangle(rect.origin.x, rect.origin.y, rect.origin.x + rect.size.width, rect.origin.y + rect.size.height , m_foreground_color);
    */
}

/*
 * public functions
 *
 */

void ulcd_progress_bar::show_progress_bar()
{
    draw_progress_bar();
}

void ulcd_progress_bar::update(float per_cent)
{
    m_per_cent = per_cent;
    draw_progress_bar();
}

void ulcd_progress_bar::change_orientation(progress_bar_orientation_t orientation)
{
    m_orientation = orientation;
    draw_progress_bar();
}

void ulcd_progress_bar::change_color(uint16_t foreground_color, uint16_t background_color)
{
    m_foreground_color = foreground_color;
    m_background_color = background_color;
    draw_progress_bar();
}

void ulcd_progress_bar::change_size(uint16_t width, uint16_t height)
{
    rect.size.width = width;
    rect.size.height = height;
    draw_progress_bar();
}

void ulcd_progress_bar::change_origin(uint16_t x_origin, uint16_t y_origin)
{
    rect.origin.x = x_origin;
    rect.origin.y = y_origin;
    draw_progress_bar();
}

void ulcd_progress_bar::new_progress_bar(uint16_t foreground_color, uint16_t background_color, uint16_t x_origin, uint16_t y_origin, uint16_t width, uint16_t height, float per_cent, progress_bar_orientation_t orientation)
{
    rect.origin.x = x_origin;
    rect.origin.y = y_origin;
    rect.size.width = width;
    rect.size.height = height;
    m_foreground_color = foreground_color;
    m_background_color = background_color;

    m_per_cent = per_cent;

    m_orientation = orientation;

    draw_progress_bar();
}
