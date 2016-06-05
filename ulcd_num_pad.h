
/*
 * ulcd_num_pad.h
 *
 *
 *
 */

#pragma once

#include "ulcd_component.h"
#include <string>
#include <sstream>
#include "uLCD_4DLibrary.h"
#include "ulcd_button.h"

#define MAX_LEN 20

/*
 * public types
 *
 */


/*
 * public class
 *
 */

 class ulcd_num_pad_delegate
{

public :

  virtual ~ulcd_num_pad_delegate(){}

  virtual void text_updated(){};

  virtual void enter_button_pressed(){};

};


class ulcd_num_pad : public ulcd_component, public ulcd_button_delegate
{
private :
    uLCD_4DLibrary* m_lcd;

    ulcd_button button_0;
    ulcd_button button_1;
    ulcd_button button_2;
    ulcd_button button_3;
    ulcd_button button_4;
    ulcd_button button_5;
    ulcd_button button_6;
    ulcd_button button_7;
    ulcd_button button_8;
    ulcd_button button_9;
    ulcd_button button_point;
    ulcd_button button_cancel;
    ulcd_button button_enter;

    ulcd_num_pad_delegate* m_delegate;

    void draw_num_pad();

    void did_select_button(ulcd_button* button);

    void set_button_delegate();

    uint16_t x_size, y_size;
    int16_t m_len;


public :
    string m_text;
    uint16_t m_foreground_color, m_background_color;

    int16_t get_text(const string &p_text);
    uint16_t get_value();
    void set_initial_value(uint16_t value);
    void clear_text();
    void show_num_pad();
    void change_color(uint16_t foreground_color, uint16_t background_color);
    void change_size(uint16_t width, uint16_t height);
    void change_origin(uint16_t x_origin, uint16_t y_origin);
    void new_num_pad(uint16_t foreground_color, uint16_t background_color, uint16_t x_origin, uint16_t y_origin, uint16_t width, uint16_t height);

    //delegate
    void set_delegate(ulcd_num_pad_delegate* p_delegate);

    // constructor
    ulcd_num_pad(uLCD_4DLibrary* p_lcd, uint16_t foreground_color, uint16_t background_color, uint16_t x_origin, uint16_t y_origin, uint16_t width, uint16_t height);
    ulcd_num_pad(uLCD_4DLibrary* p_lcd);

    ~ulcd_num_pad();

};
