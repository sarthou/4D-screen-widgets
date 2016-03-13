/*
 * ulcd_button.h
 *
 *
 *
 */

#ifndef ULCD_BUTTON_H
#define ULCD_BUTTON_H

#include "ulcd_component.h"
//#include <iostream>
#include <string>
#include "uLCD_4DLibrary.h"
#include "ulcd_label.h"

/*
 * public types
 *
 */


/*
 * public class
 *
 */
class ulcd_button;

class ulcd_button_delegate
{

public :

  virtual ~ulcd_button_delegate(){}

  virtual void did_select_button(ulcd_button* button) = 0;

};

class ulcd_button : public ulcd_component
{
private :
    uLCD_4DLibrary* m_lcd;
    ulcd_label m_label;

    ulcd_button_delegate* m_delegate;

    uint16_t m_color1, m_color2;
    uint16_t x_release,y_release,touch;

    void round_angle(uint16_t color);

    virtual void did_touch_screen(ulcd_origin_t touch_point, touch_event_t touch_state);

public :
    void set_button();

    void inverse_button();

    void change_color(uint16_t color1, uint16_t color2);

    void change_size(uint16_t width, uint16_t height);

    void change_origin(uint16_t x_origin, uint16_t y_origin);

    void change_font_size(ulcd_font_size font);

    void change_text(string text);

    void creat_button(string text, uint16_t color1, uint16_t color2, uint16_t x_origin, uint16_t y_origin, uint16_t width, uint16_t height, ulcd_font_size font);

    string get_label() const {return m_label.m_text;}

    //delegate
    void set_delegate(ulcd_button_delegate* p_delegate);

    // constructor
    ulcd_button(uLCD_4DLibrary* p_lcd, string text, uint16_t color1 = Color::ORANGE, uint16_t color2 = Color::BLACK, uint16_t x_origin = 0, uint16_t y_origin = 0, uint16_t width = 20, uint16_t height = 20, ulcd_font_size font = ulcd_font_size_1);
    ulcd_button(uLCD_4DLibrary* p_lcd);

    ~ulcd_button();

};

#endif
