/*
 * ulcd_slider.cpp
 *
 *
 *
 */

#include "ulcd_slider.h"

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
ulcd_slider::ulcd_slider(uLCD_4DLibrary* p_lcd, uint16_t color1, uint16_t color2, uint16_t button_color, uint16_t x_origin, uint16_t y_origin, uint16_t width, uint16_t height)
{
    m_lcd = p_lcd;

    rect.origin.x = x_origin;
    rect.origin.y = y_origin;

    rect.size.height = height;
    rect.size.width = width;

    m_color1 = color1;
    m_color2 = color2;
    m_button_color = button_color;

    slider_button_size.press.width = 6;
    slider_button_size.press.height = height - 4;
    slider_button_size.standard.width = 12;
    slider_button_size.standard.height = height;

    touch = 0;
    m_per_cent = 0.5;

    set_slider();

    touch_dispatcher::shared_instance()->add_register_component(this);
}

ulcd_slider::ulcd_slider(uLCD_4DLibrary* p_lcd)
{
    m_lcd = p_lcd;

    m_per_cent = 0.5;

    rect.origin.x = 0;
    rect.origin.y = 0;

    rect.size.height = 20;
    rect.size.width = 20;

    m_color1 = Color::ORANGE;
    m_color2 = Color::BLACK;
    m_button_color = Color::GRAY;

    slider_button_size.press.width = 6;
    slider_button_size.press.height = rect.size.height - 4;
    slider_button_size.standard.width = 12;
    slider_button_size.standard.height = rect.size.height;

    touch = 0;
}

ulcd_slider::~ulcd_slider()
{

}


/*
 * private functions
 *
 */
void ulcd_slider::round_angle(uint16_t color)
{
    uint16_t pixel_color;

    pixel_color = m_lcd->gfx_read_pixel(rect.origin.x-1, rect.origin.y-1);
    m_lcd->gfx_draw_pixel(rect.origin.x, rect.origin.y, pixel_color);
    m_lcd->gfx_draw_pixel(rect.origin.x+1, rect.origin.y, pixel_color);
    m_lcd->gfx_draw_pixel(rect.origin.x, rect.origin.y+1, pixel_color);

    pixel_color = m_lcd->gfx_read_pixel(rect.origin.x + rect.size.width +1, rect.origin.y-1);
    m_lcd->gfx_draw_pixel(rect.origin.x + rect.size.width, rect.origin.y, pixel_color);
    m_lcd->gfx_draw_pixel(rect.origin.x + rect.size.width - 1, rect.origin.y, pixel_color);
    m_lcd->gfx_draw_pixel(rect.origin.x + rect.size.width , rect.origin.y+1, pixel_color);

    pixel_color = m_lcd->gfx_read_pixel(rect.origin.x-1, rect.origin.y + rect.size.height + 1);
    m_lcd->gfx_draw_pixel(rect.origin.x, rect.origin.y + rect.size.height, pixel_color);
    m_lcd->gfx_draw_pixel(rect.origin.x+1, rect.origin.y + rect.size.height, pixel_color);
    m_lcd->gfx_draw_pixel(rect.origin.x, rect.origin.y + rect.size.height - 1, pixel_color);

    pixel_color = m_lcd->gfx_read_pixel(rect.origin.x + rect.size.width +1, rect.origin.y + rect.size.height + 1);
    m_lcd->gfx_draw_pixel(rect.origin.x + rect.size.width, rect.origin.y + rect.size.height, pixel_color);
    m_lcd->gfx_draw_pixel(rect.origin.x + rect.size.width - 1, rect.origin.y +rect.size.height, pixel_color);
    m_lcd->gfx_draw_pixel(rect.origin.x + rect.size.width, rect.origin.y + rect.size.height - 1, pixel_color);
}

void ulcd_slider::did_touch_screen(ulcd_origin_t touch_point, touch_event_t touch_state)
{
    switch(touch_state)
    {
        case touch_began:
        {
            if(rect.is_inside(touch_point))
            {
                m_per_cent = (float)(touch_point.x - rect.origin.x) / (float)(rect.size.width);

                m_lcd->gfx_draw_filled_rectangle(rect.origin.x, rect.origin.y, rect.origin.x + rect.size.width, rect.origin.y + rect.size.height, m_color1);
                round_angle(m_color1);
                update_button();
                m_delegate->did_move_slider(this, m_per_cent);
                touch = 1;
            }
        }
        break;
        case touch_ended :
        {
             if(touch == 1)
            {
                set_slider();
                touch=0;
            }
        }
        break;
        case touch_moved:
        {
            if(rect.is_inside(touch_point))
            {
                m_per_cent = (float)(touch_point.x - rect.origin.x) / (float)(rect.size.width - 4);
                update_button();
                m_delegate->did_move_slider(this, m_per_cent);
            }
        }
        break;
        default :
        {

        }
        break;
    }
}

/*
 * public functions
 *
 */

void ulcd_slider::set_slider()
{
    m_lcd->gfx_draw_filled_rectangle(rect.origin.x, rect.origin.y, rect.origin.x + rect.size.width, rect.origin.y + rect.size.height, m_color1);
    m_lcd->gfx_draw_filled_rectangle(rect.origin.x + 2, rect.origin.y + 2, rect.origin.x + rect.size.width - 2, rect.origin.y + rect.size.height - 2, m_color2);
    round_angle(m_color1);
    if(rect.size.width*m_per_cent - slider_button_size.standard.width/2 < 2)
        m_lcd->gfx_draw_filled_rectangle(rect.origin.x + 2, rect.origin.y + 1, rect.origin.x + (rect.size.width - 4)*m_per_cent + slider_button_size.standard.width/2, rect.origin.y + rect.size.height - 1, m_button_color);
    else if(rect.size.width*m_per_cent + slider_button_size.standard.width/2 > rect.size.width - 2)
        m_lcd->gfx_draw_filled_rectangle(rect.origin.x + (rect.size.width - 4)*m_per_cent - slider_button_size.standard.width/2, rect.origin.y + 1, rect.origin.x + rect.size.width - 2, rect.origin.y + rect.size.height - 1, m_button_color);
    else
        m_lcd->gfx_draw_filled_rectangle(rect.origin.x + (rect.size.width - 4)*m_per_cent - slider_button_size.standard.width/2, rect.origin.y + 1, rect.origin.x + (rect.size.width - 4)*m_per_cent + slider_button_size.standard.width/2, rect.origin.y + rect.size.height - 1, m_button_color);
}

void ulcd_slider::update_button()
{
    m_lcd->gfx_draw_filled_rectangle(rect.origin.x + 2, rect.origin.y + 2, rect.origin.x + rect.size.width - 2, rect.origin.y + rect.size.height - 2, m_color2);
    if(rect.size.width*m_per_cent - slider_button_size.press.width/2 < 2)
        m_lcd->gfx_draw_filled_rectangle(rect.origin.x + 2, rect.origin.y + 2, rect.origin.x + (rect.size.width - 4)*m_per_cent + slider_button_size.press.width/2, rect.origin.y + rect.size.height - 2, m_button_color);
    else if(rect.size.width*m_per_cent + slider_button_size.press.width/2 > rect.size.width - 2)
        m_lcd->gfx_draw_filled_rectangle(rect.origin.x + (rect.size.width - 4)*m_per_cent - slider_button_size.press.width/2, rect.origin.y + 2, rect.origin.x + rect.size.width - 2, rect.origin.y + rect.size.height - 2, m_button_color);
    else
        m_lcd->gfx_draw_filled_rectangle(rect.origin.x + (rect.size.width - 4)*m_per_cent - slider_button_size.press.width/2, rect.origin.y + 2, rect.origin.x + (rect.size.width - 4)*m_per_cent + slider_button_size.press.width/2, rect.origin.y + rect.size.height - 2, m_button_color);
}

void ulcd_slider::change_color(uint16_t color1, uint16_t color2)
{
    m_color1 = color1;
    m_color2 = color2;
    set_slider();
}

void ulcd_slider::change_size(uint16_t width, uint16_t height)
{
    rect.size.height = height;
    rect.size.width = width;
    set_slider();
}

void ulcd_slider::change_origin(uint16_t x_origin, uint16_t y_origin)
{
    rect.origin.x = x_origin;
    rect.origin.y = y_origin;
    set_slider();
}

void ulcd_slider::creat_slider(uint16_t color1, uint16_t color2, uint16_t button_color, uint16_t x_origin, uint16_t y_origin, uint16_t width, uint16_t height)
{
    rect.origin.x = x_origin;
    rect.origin.y = y_origin;

    rect.size.height = height;
    rect.size.width = width;

    m_color1 = color1;
    m_color2 = color2;
    m_button_color = button_color;

    touch = 0;

    set_slider();

    touch_dispatcher::shared_instance()->add_register_component(this);
}

void ulcd_slider::set_delegate(ulcd_slider_delegate* p_delegate)
{
    m_delegate = p_delegate;
}

