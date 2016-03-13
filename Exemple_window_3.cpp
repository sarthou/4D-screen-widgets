/*
 * Exemple_window_3.cpp
 *
 *
 *
 */

#include "Exemple_window_3.h"

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
Exemple_window_3::Exemple_window_3(uLCD_4DLibrary* p_lcd) : button_return(p_lcd), title(p_lcd), m_slider(p_lcd), m_progress(p_lcd)
{
    m_lcd = p_lcd;
    button_return.set_delegate(this);
    m_slider.set_delegate(this);
}

Exemple_window_3::~Exemple_window_3()
{
}


/*
 * private functions
 *
 */

void Exemple_window_3::did_select_button(ulcd_button* button)
{
    if(button == &button_return)
        m_delegate->did_select_return_button();
}

void Exemple_window_3::did_move_slider(ulcd_slider* slider, float p_per_cent)
{
    m_progress.update(p_per_cent);
}


/*
 * public functions
 *
 */

void Exemple_window_3::set_exemple_window_3()
{
    m_lcd->gfx_clear_screen();
    button_return.creat_button("Return", Color::WHITE, Color::BLACK, 340, 230, 130, 40, ulcd_font_size_1);
    m_slider.creat_slider(Color::WHITE, Color::GREEN, Color::GRAY, 140, 100, 200, 30);
    m_progress.new_progress_bar(Color::WHITE, Color::BLACK, 140, 160, 200, 30, m_slider.get_per_cent(), h_to_right);
    title.new_label("Slider & progress bar", Color::WHITE, 120, 0, 240, 80, ulcd_font_size_2, h_center, v_center);
}

void Exemple_window_3::set_delegate(Exemple_window_3_delegate* p_delegate)
{
    m_delegate = p_delegate;
}
