/*
 * ulcd_label.cpp
 *
 *
 *
 */

#include "ulcd_label.h"

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
ulcd_label::ulcd_label(uLCD_4DLibrary* p_lcd,string text, uint16_t foreground_color, uint16_t x_origin, uint16_t y_origin, uint16_t width, uint16_t height, ulcd_font_size font, ulcd_h_alignment h_alignment, ulcd_v_alignment v_alignment)
{
    m_lcd = p_lcd;

    m_alignment.h_alignment = h_alignment;
    m_alignment.v_alignment = v_alignment;
    rect.origin.x = x_origin;
    rect.origin.y = y_origin;
    rect.size.width = width;
    rect.size.height = height;
    m_foreground_color = foreground_color;
    m_background_color = Color::BLACK;
    m_font = font;
    m_text = text;

    update_attributes();
    write_text();
}

ulcd_label::ulcd_label(uLCD_4DLibrary* p_lcd)
{
    m_lcd = p_lcd;

    m_alignment.h_alignment = h_left;
    m_alignment.v_alignment = v_top;
    rect.origin.x = 0;
    rect.origin.y = 0;
    rect.size.width = 20;
    rect.size.height = 20;
    m_foreground_color = Color::WHITE;
    m_background_color = Color::BLACK;
    m_font = ulcd_font_size_1;
}

ulcd_label::~ulcd_label()
{

}


/*
 * private functions
 *
 */
void ulcd_label::update_attributes()
{
    m_lcd->txt_set_font(3);
    m_lcd->txt_width_multiplier(m_font);
    m_lcd->txt_height_multiplier(m_font);
    m_lcd->txt_foreground_color(m_foreground_color);
    m_lcd->txt_background_color(m_background_color);
}

void ulcd_label::write_text()
{
    uint8_t sector = 0;
    uint8_t u = m_lcd->txt_char_width('0');;
    uint8_t nb_car_max = rect.size.width/u;
    uint8_t nb_car_per_sector[100];
    uint8_t car_index_total = 0;
    uint8_t car_index = 0;
    uint16_t size_text = m_text.size();
    string text_cpy;
    char buffer[100];
    text_cpy = m_text;

    uint16_t y_location = 0, x_location = 0;
    if(nb_car_max != 0)
    {
        while(car_index_total < size_text)
        {
            car_index += nb_car_max;

            if(car_index < size_text)
            {
                while((text_cpy[car_index] != ' ') && (car_index_total != car_index))
                {
                    car_index --;
                }

                if(car_index_total == car_index)
                {
                    car_index += nb_car_max;
                }
                else
                {
                    text_cpy.erase(car_index,1);
                    size_text = text_cpy.size();
                }
            }
            else
            {
                car_index = size_text;
            }

            nb_car_per_sector[sector] = car_index - car_index_total;
            sector ++;
            car_index_total = car_index;
        }

        switch(m_alignment.v_alignment)
        {
            case v_top:
            {
                y_location = rect.origin.y;
            }
            break;

            case v_bottom:
            {
                y_location = (rect.origin.y + rect.size.height) - sector*m_lcd->txt_char_height('0');
            }
            break;

            case v_center:
            {
                y_location = ((rect.size.height - sector*m_lcd->txt_char_height('0')) / 2) + rect.origin.y;
            }
            break;
        }

        car_index = 0;
        for(uint8_t i = 0; i < sector; i++)
        {
             switch(m_alignment.h_alignment)
            {
                case h_left:
                {
                    x_location = rect.origin.x;
                }
                break;

                case h_right:
                {
                    x_location = (rect.origin.x + rect.size.width) - nb_car_per_sector[i]*m_lcd->txt_char_width('0');
                }
                break;

                case h_center:
                {
                    x_location = ((rect.size.width - nb_car_per_sector[i]*m_lcd->txt_char_width('0'))/2) + rect.origin.x;
                }
                break;
            }
            text_cpy.copy(buffer,nb_car_per_sector[i], car_index);
            buffer[nb_car_per_sector[i]] = 0;
            car_index += nb_car_per_sector[i];

            m_lcd->gfx_move_origin(x_location, y_location);
            m_lcd->txt_put_str((const int8_t*)buffer);

            y_location += m_lcd->txt_char_height('0');
        }
    }
}

/*
 * public functions
 *
 */

void ulcd_label::show_label()
{
    update_attributes();
    write_text();
}

void ulcd_label::show_delimitation()
{
    m_lcd->gfx_draw_filled_rectangle(rect.origin.x, rect.origin.y, rect.origin.x+rect.size.width, rect.origin.y+rect.size.height, m_background_color);
    write_text();
}

void ulcd_label::change_color(uint16_t foreground_color, uint16_t background_color)
{
    m_foreground_color = foreground_color;
    m_background_color = background_color;
    update_attributes();
    write_text();
}

void ulcd_label::change_size(uint16_t width, uint16_t height)
{
    rect.size.width = width;
    rect.size.height = height;
    update_attributes();
    write_text();
}

void ulcd_label::change_origin(uint16_t x_origin, uint16_t y_origin)
{
    rect.origin.x = x_origin;
    rect.origin.y = y_origin;
    update_attributes();
    write_text();
}

void ulcd_label::change_alignment(ulcd_h_alignment h_alignment, ulcd_v_alignment v_alignment)
{
    m_alignment.h_alignment = h_alignment;
    m_alignment.v_alignment = v_alignment;
    update_attributes();
    write_text();
}

void ulcd_label::change_font_size(ulcd_font_size font)
{
    m_font = font;
    update_attributes();
    write_text();
}

void ulcd_label::change_text(string text)
{
    m_text = text;
    update_attributes();
    write_text();
}

void ulcd_label::change_text2(string text)
{
    m_text = text;
    char buffer[4];
    text.copy(buffer,3, 0);
    m_lcd->gfx_move_origin(96, 34);
    m_lcd->txt_put_str((const int8_t*)buffer);
}

void ulcd_label::new_label(string text, uint16_t foreground_color, uint16_t x_origin, uint16_t y_origin, uint16_t width, uint16_t height, ulcd_font_size font, ulcd_h_alignment h_alignment, ulcd_v_alignment v_alignment)
{
    m_alignment.h_alignment = h_alignment;
    m_alignment.v_alignment = v_alignment;
    rect.origin.x = x_origin;
    rect.origin.y = y_origin;
    rect.size.width = width;
    rect.size.height = height;
    m_foreground_color = foreground_color;
    m_font = font;
    m_text = text;

    update_attributes();
    write_text();
}
