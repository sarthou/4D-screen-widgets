/*
 * Exemple_window_2.cpp
 *
 *
 *
 */

#include "Exemple_window_2.h"

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
Exemple_window_2::Exemple_window_2(uLCD_4DLibrary* p_lcd) : button_return(p_lcd), aff(p_lcd), title(p_lcd), num_pad(p_lcd)
{
    m_lcd = p_lcd;
    button_return.set_delegate(this);
    num_pad.set_delegate(this);
}

Exemple_window_2::~Exemple_window_2()
{
}


/*
 * private functions
 *
 */

 void Exemple_window_2::text_updated()
 {
    aff.change_text(num_pad.m_text);
    aff.show_delimitation();
 }

 void Exemple_window_2::enter_button_pressed()
 {
     num_pad.clear_text();
     aff.change_text(num_pad.m_text);
     aff.show_delimitation();
 }

void Exemple_window_2::did_select_button(ulcd_button* button)
{
    if(button == &button_return)
        m_delegate->did_select_return_button();
}

/*
 * public functions
 *
 */

void Exemple_window_2::set_exemple_window_2()
{
    m_lcd->gfx_clear_screen();
    button_return.creat_button("Return", Color::WHITE, Color::BLACK, 340, 230, 130, 40, ulcd_font_size_1);
    num_pad.new_num_pad(Color::RED, Color::BLACK, 0, 10, 300, 250);
    aff.new_label(num_pad.m_text, Color::WHITE, 340, 80, 130, 130, ulcd_font_size_2, h_center, v_center);
    aff.change_color(Color::WHITE, Color::GRAY);
    aff.show_delimitation();
    title.new_label("Num pad & Label", Color::WHITE, 340, 10, 130, 60, ulcd_font_size_2, h_center, v_center);
}

void Exemple_window_2::set_delegate(Exemple_window_2_delegate* p_delegate)
{
    m_delegate = p_delegate;
}
