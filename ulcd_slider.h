/*
 * ulcd_slider.h
 *
 *
 *
 */

#ifndef ULCD_SLIDER_H
#define ULCD_SLIDER_H

#include "ulcd_component.h"
//#include <iostream>
#include <string>
#include "uLCD_4DLibrary.h"

/*
 * public types
 *
 */

 typedef struct
{
    ulcd_size_t standard;
    ulcd_size_t press;

} ulcd_slider_button_size_t;


/*
 * public class
 *
 */
class ulcd_slider;

class ulcd_slider_delegate
{

public :

  virtual ~ulcd_slider_delegate(){}

  virtual void did_move_slider(ulcd_slider* slider, float per_cent = 0.5) = 0;

};

class ulcd_slider : public ulcd_component
{
private :
    uLCD_4DLibrary* m_lcd;

    ulcd_slider_delegate* m_delegate;

    uint16_t m_color1, m_color2, m_button_color;
    uint16_t x_release,y_release,touch;
    float m_per_cent;
    ulcd_slider_button_size_t slider_button_size;

    void round_angle(uint16_t color);

    void update_button();

    void did_touch_screen(ulcd_origin_t touch_point, touch_event_t touch_state);

public :
    void set_slider();

    void change_color(uint16_t color1, uint16_t color2);

    void change_size(uint16_t width, uint16_t height);

    void change_origin(uint16_t x_origin, uint16_t y_origin);

    void creat_slider(uint16_t color1 = Color::ORANGE, uint16_t color2 = Color::BLACK, uint16_t button_color = Color::GRAY, uint16_t x_origin = 0, uint16_t y_origin = 0, uint16_t width = 20, uint16_t height = 20);

    float get_per_cent() const {return m_per_cent;}

    //delegate
    void set_delegate(ulcd_slider_delegate* p_delegate);

    // constructor
    ulcd_slider(uLCD_4DLibrary* p_lcd, uint16_t color1, uint16_t color2 = Color::BLACK, uint16_t button_color = Color::GRAY, uint16_t x_origin = 0, uint16_t y_origin = 0, uint16_t width = 20, uint16_t height = 20);
    ulcd_slider(uLCD_4DLibrary* p_lcd);

    ~ulcd_slider();

};

#endif

