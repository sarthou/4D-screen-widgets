/*
 * ulcd_line_chart.h
 *
 *
 *
 */

#ifndef ULCD_LINE_CHART_H
#define ULCD_LINE_CHART_H

#include "ulcd_component.h"
#include "uLCD_4DLibrary.h"

/*
 * public types
 *
 */



/*
 * public class
 *
 */

class ulcd_line_chart : public ulcd_component
{
private :
    uLCD_4DLibrary* m_lcd;

    uint8_t space[249];
    uint16_t m_foreground_color;
    uint16_t m_background_color;

    uint16_t last_point, x;
    uint8_t wait, x_index;

    void space_calculate();

    void wait_calculate();

public :

    void change_size(uint16_t width, uint16_t height);

    void change_origin(uint16_t x, uint16_t y);

    void update_point(int32_t point_y);

    // constructor
    ulcd_line_chart(uLCD_4DLibrary* p_lcd, uint16_t foreground_color = Color::ORANGE, uint16_t background_color = Color::BLACK, uint16_t x_origin = 10, uint16_t y_origin = 10, uint16_t width = 252, uint16_t height = 252);

    ~ulcd_line_chart();

};

#endif
