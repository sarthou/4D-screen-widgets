/*
 * ulcd_line_chart.cpp
 *
 *
 *
 */

#include "ulcd_line_chart.h"

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
ulcd_line_chart::ulcd_line_chart(uLCD_4DLibrary* p_lcd, uint16_t foreground_color, uint16_t background_color, uint16_t x_origin, uint16_t y_origin, uint16_t width, uint16_t height)
{
    m_lcd = p_lcd;

    m_foreground_color = foreground_color;
    m_background_color = background_color;
    rect.origin.x = x_origin;
    rect.origin.y = y_origin;
    rect.size.width = width;
    rect.size.height = height;
}

ulcd_line_chart::~ulcd_line_chart()
{

}


/*
 * private functions
 *
 */

void ulcd_line_chart::space_calculate()
{
    uint16_t sum = 0;

    for(uint8_t i = 0; i < 249; i++)
    {
        if(i == 248)
        {
            space[i] = rect.size.width - 3 - sum;
        }
        else
        {
            space[i] = (float)( (((i + 1)*(rect.size.width - 3)/249) - sum) + 0.5);
        }
        sum += space[i];
    }
}

void ulcd_line_chart::wait_calculate()
{
    uint16_t sum = 0;

    for(uint8_t i = 0; i < rect.size.width - 3; i++)
    {
        if(i == rect.size.width - 4)
        {
            space[i] = 249 - sum;
        }
        else
        {
            space[i] = (float)( (((i + 1)*249/(rect.size.width - 3)) - sum) + 0.5);
        }
        sum += space[i];
    }
}

/*
 * public functions
 *
 */

void ulcd_line_chart::update_point(int32_t point_y)
{
    point_y += rect.origin.y;
    if(point_y >rect.size.height - 1 + rect.origin.y)
      point_y = rect.size.height - 1 + rect.origin.y;
    if(point_y < rect.origin.y + 1)
      point_y = rect.origin.y + 1;

    if(rect.size.width < 252)
    {
        wait ++;
        if(x == 0)
        {
            m_lcd->gfx_draw_line(rect.origin.x + 1 + x,1 + rect.origin.y, rect.origin.x + 1 + x, rect.origin.y + (rect.size.height-1), m_background_color);
            m_lcd->gfx_draw_line(rect.origin.x + 1 + x,point_y, rect.origin.x + 1 + (x-1), point_y, m_foreground_color);
            last_point = point_y;
            x++;
            wait = 0;
        }
        else if(wait == space[x_index])
        {
            wait = 0;
            m_lcd->gfx_draw_line(rect.origin.x + 1 + x,1 + rect.origin.y, rect.origin.x + 1 + x, rect.origin.y + (rect.size.height-1), m_background_color);
            m_lcd->gfx_draw_line(rect.origin.x + 1 + x,point_y, rect.origin.x + 1 + (x-1), last_point, m_foreground_color);

            x_index ++;
            x ++;
            last_point = point_y;

            if( x_index > rect.size.width - 4)
            {
                x_index = 0;
                x = 0;
            }
        }
    }
    else
    {
        if(x == 0)
        {
            m_lcd->gfx_draw_line(rect.origin.x + 1 + x, 1 + rect.origin.y, rect.origin.x + 1 + x, rect.origin.y + (rect.size.height-1), m_background_color);
            m_lcd->gfx_draw_line(rect.origin.x + 1 + x,point_y, rect.origin.x + 1 + x, point_y, m_foreground_color);
            last_point = point_y;
            x ++;
        }
        else
        {
            for(uint8_t i = 0; i < space[x_index]; i++)
            {
                m_lcd->gfx_draw_line(rect.origin.x + 1 + x + i, 1 + rect.origin.y, rect.origin.x + 1 + x + i, rect.origin.y + (rect.size.height-1), m_background_color);
            }
            m_lcd->gfx_draw_line(rect.origin.x + 1 + x + (space[x_index] - 1), point_y, rect.origin.x + 1 + (x - 1), last_point, m_foreground_color);


            x += space[x_index];
            x_index ++;
            last_point = point_y;

            if( x_index > 248)
            {
                x_index = 0;
                x = 0;
            }
        }
    }

}

void ulcd_line_chart::change_size(uint16_t width, uint16_t height)
{
    rect.size.width = width;
    rect.size.height = height;

    if(rect.size.width < 252)
        wait_calculate();
    else
        space_calculate();

    wait = 0;
    x_index = 0;
    x = 0;
    m_lcd->gfx_draw_filled_rectangle(rect.origin.x, rect.origin.y, rect.origin.x + rect.size.width, rect.origin.y + rect.size.height, m_background_color);
    m_lcd->gfx_draw_rectangle(rect.origin.x, rect.origin.y, rect.origin.x + rect.size.width, rect.origin.y + rect.size.height, m_foreground_color);
}

void ulcd_line_chart::change_origin(uint16_t x, uint16_t y)
{
    rect.origin.x = x;
    rect.origin.y = y;

    wait = 0;
    x_index = 0;
    x = 0;
    m_lcd->gfx_draw_filled_rectangle(rect.origin.x, rect.origin.y, rect.origin.x + rect.size.width, rect.origin.y + rect.size.height, m_background_color);
    m_lcd->gfx_draw_rectangle(rect.origin.x, rect.origin.y, rect.origin.x + rect.size.width, rect.origin.y + rect.size.height, m_foreground_color);
}
