/*
 * ulcd_button.cpp
 *
 *
 *
 */

#include "ulcd_button.h"

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
ulcd_button::ulcd_button(uLCD_4DLibrary* p_lcd,string text, uint16_t color1, uint16_t color2, uint16_t x_origin, uint16_t y_origin, uint16_t width, uint16_t height, ulcd_font_size font) : m_label(p_lcd)
{
    m_lcd = p_lcd;

    m_label.m_alignment.h_alignment = h_center;
    m_label.m_alignment.v_alignment = v_center;

    m_label.rect.origin.x = x_origin + 2;
    rect.origin.x = x_origin;
    m_label.rect.origin.y = y_origin + 2;
    rect.origin.y = y_origin;

    m_label.rect.size.height = height;
    rect.size.height = height;
    m_label.rect.size.width = width;
    rect.size.width = width;

    m_color1 = color1;
    m_label.m_foreground_color = color1;
    m_color2 = color2;

    m_label.m_text = text;
    m_label.m_font = font;

    touch = 0;

    set_button();

    touch_dispatcher::shared_instance()->add_register_component(this);
}

ulcd_button::ulcd_button(uLCD_4DLibrary* p_lcd) : m_label(p_lcd)
{
    m_lcd = p_lcd;

    m_label.m_alignment.h_alignment = h_center;
    m_label.m_alignment.v_alignment = v_center;

    m_label.rect.origin.x = 0;
    rect.origin.x = 0;
    m_label.rect.origin.y = 0;
    rect.origin.y = 0;

    m_label.rect.size.height = 20 - 4;
    rect.size.height = 20;
    m_label.rect.size.width = 20 - 4;
    rect.size.width = 20;

    m_color1 = Color::ORANGE;
    m_label.m_foreground_color = Color::ORANGE;
    m_color2 = Color::BLACK;

    m_label.m_font = ulcd_font_size_1;

    touch = 0;
}

ulcd_button::~ulcd_button()
{

}


/*
 * private functions
 *
 */
void ulcd_button::round_angle(uint16_t color)
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

    m_lcd->gfx_draw_pixel(rect.origin.x + 2, rect.origin.y + 2, color);
    m_lcd->gfx_draw_pixel(rect.origin.x + rect.size.width - 2, rect.origin.y + 2, color);
    m_lcd->gfx_draw_pixel(rect.origin.x + 2, rect.origin.y + rect.size.height - 2, color);
    m_lcd->gfx_draw_pixel(rect.origin.x + rect.size.width - 2, rect.origin.y + rect.size.height - 2, color);
}

void ulcd_button::did_touch_screen(ulcd_origin_t touch_point, touch_event_t touch_state)
{
    switch(touch_state)
    {
        case touch_began:
        {
            if(rect.is_inside(touch_point))
            {
                inverse_button();
                touch = 1;
            }
        }
        break;
        case touch_ended :
        {
             if(touch == 1)
            {
                set_button();
                if(rect.is_inside(touch_point))
                {
                    m_delegate->did_select_button(this);
                }
                touch=0;
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

void ulcd_button::set_button()
{
    m_lcd->gfx_draw_filled_rectangle(rect.origin.x, rect.origin.y, rect.origin.x + rect.size.width, rect.origin.y + rect.size.height, m_color1);
    m_lcd->gfx_draw_filled_rectangle(rect.origin.x + 2, rect.origin.y + 2, rect.origin.x + rect.size.width - 2, rect.origin.y + rect.size.height - 2, m_color2);
    m_label.change_color(m_color1, m_color2);
    round_angle(m_color1);
}

void ulcd_button::inverse_button()
{
    m_lcd->gfx_draw_filled_rectangle(rect.origin.x, rect.origin.y, rect.origin.x + rect.size.width, rect.origin.y + rect.size.height, m_color2);
    m_lcd->gfx_draw_filled_rectangle(rect.origin.x + 2, rect.origin.y + 2, rect.origin.x + rect.size.width - 2, rect.origin.y + rect.size.height - 2, m_color1);
    m_label.change_color(m_color2, m_color1);
    round_angle(m_color2);
}

void ulcd_button::change_color(uint16_t color1, uint16_t color2)
{
    m_color1 = color1;
    m_color2 = color2;
    set_button();
}

void ulcd_button::change_size(uint16_t width, uint16_t height)
{
    m_label.rect.size.height = height;
    rect.size.height = height;
    m_label.rect.size.width = width;
    rect.size.width = width;
    set_button();
}

void ulcd_button::change_origin(uint16_t x_origin, uint16_t y_origin)
{
    m_label.rect.origin.x = x_origin + 2;
    rect.origin.x = x_origin;
    m_label.rect.origin.y = y_origin + 2;
    rect.origin.y = y_origin;
    set_button();
}

void ulcd_button::change_font_size(ulcd_font_size font)
{
    m_label.m_font = font;
    set_button();
}

void ulcd_button::change_text(string text)
{
    m_label.m_text = text;
    set_button();
}

void ulcd_button::creat_button(string text, uint16_t color1, uint16_t color2, uint16_t x_origin, uint16_t y_origin, uint16_t width, uint16_t height, ulcd_font_size font)
{
    m_label.m_alignment.h_alignment = h_center;
    m_label.m_alignment.v_alignment = v_center;

    m_label.rect.origin.x = x_origin + 2;
    rect.origin.x = x_origin;
    m_label.rect.origin.y = y_origin + 2;
    rect.origin.y = y_origin;

    m_label.rect.size.height = height;
    rect.size.height = height;
    m_label.rect.size.width = width;
    rect.size.width = width;

    m_color1 = color1;
    m_label.m_foreground_color = color1;
    m_color2 = color2;

    m_label.m_text = text;
    m_label.m_font = font;

    touch = 0;

    set_button();

    touch_dispatcher::shared_instance()->add_register_component(this);
}

void ulcd_button::set_delegate(ulcd_button_delegate* p_delegate)
{
    m_delegate = p_delegate;
}
