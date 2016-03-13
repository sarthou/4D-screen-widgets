/*
 * ulcd_progress_bar.h
 *
 *
 *
 */

#pragma once

#include "ulcd_component.h"
#include <string>
#include "uLCD_4DLibrary.h"

/*
 * public types
 *
 */

typedef enum
{
    v_to_bottom ,
    v_to_top    ,
    h_to_right  ,
    h_to_left

} progress_bar_orientation_t;


/*
 * public class
 *
 */


class ulcd_progress_bar : public ulcd_component
{
private :
    uLCD_4DLibrary* m_lcd;

    progress_bar_orientation_t m_orientation;

    void draw_progress_bar();
    float m_per_cent;

public :

    uint16_t m_foreground_color, m_background_color;

    void show_progress_bar();
    void update(float per_cent);
    void change_orientation(progress_bar_orientation_t orientation);
    void change_color(uint16_t foreground_color, uint16_t background_color);
    void change_size(uint16_t width, uint16_t height);
    void change_origin(uint16_t x_origin, uint16_t y_origin);
    void new_progress_bar(uint16_t foreground_color, uint16_t background_color, uint16_t x_origin, uint16_t y_origin, uint16_t width, uint16_t height, float per_cent, progress_bar_orientation_t orientation = v_to_top);

    // constructor
    ulcd_progress_bar(uLCD_4DLibrary* p_lcd, uint16_t foreground_color, uint16_t background_color, uint16_t x_origin, uint16_t y_origin, uint16_t width, uint16_t height, float per_cent, progress_bar_orientation_t orientation = v_to_top);
    ulcd_progress_bar(uLCD_4DLibrary* p_lcd);

    ~ulcd_progress_bar();

};
