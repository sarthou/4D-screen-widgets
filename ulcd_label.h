/*
 * ulcd_label.h
 *
 *
 *
 */

#ifndef ULCD_LABEL_H
#define ULCD_LABEL_H

#include "ulcd_component.h"
//#include <iostream>
#include <string>
#include "uLCD_4DLibrary.h"

/*
 * public types
 *
 */

typedef enum
{
    ulcd_font_size_1  = 1,
    ulcd_font_size_2  = 2,
    ulcd_font_size_3  = 3,
    ulcd_font_size_4  = 4,
    ulcd_font_size_5  = 5,
    ulcd_font_size_6  = 6,
    ulcd_font_size_7  = 7,
    ulcd_font_size_8  = 8,
    ulcd_font_size_9  = 9,
    ulcd_font_size_10 = 10,
    ulcd_font_size_11 = 11,
    ulcd_font_size_12 = 12,
    ulcd_font_size_13 = 13,
    ulcd_font_size_14 = 14,
    ulcd_font_size_15 = 15,
    ulcd_font_size_16 = 16

} ulcd_font_size;

typedef enum
{
    h_center    ,
    h_right     ,
    h_left

} ulcd_h_alignment;

typedef enum
{
    v_center    ,
    v_top       ,
    v_bottom

} ulcd_v_alignment;

typedef struct
{
    ulcd_v_alignment v_alignment;
    ulcd_h_alignment h_alignment;

} ulcd_alignment_t;


/*
 * public class
 *
 */


class ulcd_label : public ulcd_component
{
private :
    uLCD_4DLibrary* m_lcd;



    void write_text();

public :

    ulcd_alignment_t m_alignment;
    string m_text;
    uint16_t m_foreground_color, m_background_color;
    ulcd_font_size m_font;

    void update_attributes();

    void show_label();
    void show_delimitation();
    void change_color(uint16_t foreground_color, uint16_t background_color);
    void change_size(uint16_t width, uint16_t height);
    void change_origin(uint16_t x_origin, uint16_t y_origin);
    void change_alignment(ulcd_h_alignment h_alignment, ulcd_v_alignment v_alignment);
    void change_font_size(ulcd_font_size font);
    void change_text(string text);
    void change_text2(string text);
    void new_label(string text, uint16_t foreground_color, uint16_t x_origin, uint16_t y_origin, uint16_t width, uint16_t height, ulcd_font_size font, ulcd_h_alignment h_alignment, ulcd_v_alignment v_alignment);

    // constructor
    ulcd_label(uLCD_4DLibrary* p_lcd, string text, uint16_t foreground_color = Color::WHITE, uint16_t x_origin = 0, uint16_t y_origin = 0, uint16_t width = 20, uint16_t height = 20, ulcd_font_size font = ulcd_font_size_1, ulcd_h_alignment h_alignment = h_left, ulcd_v_alignment v_alignmen = v_top);
    ulcd_label(uLCD_4DLibrary* p_lcd);

    ~ulcd_label();

};

#endif
