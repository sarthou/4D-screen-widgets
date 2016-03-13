/*
 * Exemple_window_1.cpp
 *
 *
 *
 */

#include "Exemple_window_1.h"

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
Exemple_window_1::Exemple_window_1(uLCD_4DLibrary* p_lcd) : button_vote1(p_lcd), button_vote2(p_lcd),
                                                            button_return(p_lcd), button_reset(p_lcd),
                                                            title(p_lcd), m_progress_bar_vote1(p_lcd),
                                                            m_progress_bar_vote2(p_lcd)
{
    m_lcd = p_lcd;
    button_vote1.set_delegate(this);
    button_vote2.set_delegate(this);
    button_return.set_delegate(this);
    button_reset.set_delegate(this);

    resp_1 = 0;
    resp_2 = 0;
}

Exemple_window_1::~Exemple_window_1()
{
}


/*
 * private functions
 *
 */



/*
 * public functions
 *
 */

void Exemple_window_1::did_select_button(ulcd_button* button)
{
    if(button == &button_vote1)
    {
        resp_1 ++;
        update_graf();
    }
    else if(button == &button_vote2)
    {
        resp_2 ++;
        update_graf();
    }
    else if(button == &button_return)
    {
        m_delegate->did_select_return_button();
    }
    else if(button ==  &button_reset)
    {
        resp_1 = 0;
        resp_2 = 0;
        update_graf();
    }

}

void Exemple_window_1::set_exemple_window_1()
{
    m_lcd->gfx_clear_screen();

    button_return.creat_button("Return", Color::WHITE, Color::BLACK, 340, 230, 130, 40, ulcd_font_size_1);
    button_reset.creat_button("reset", Color::WHITE, Color::BLACK, 340, 150, 130, 40, ulcd_font_size_1);

    m_progress_bar_vote1.new_progress_bar(Color::BLUE, Color::WHITE, 80-10, 115, 80, 150, 0., v_to_top);
    m_progress_bar_vote2.new_progress_bar(Color::BLUE, Color::WHITE, 3*80-10, 115, 80, 150, 0., v_to_top);

    button_vote1.creat_button("1", Color::WHITE, Color::BLACK, 80, 115 + (150 - 40)/2, 60, 40, ulcd_font_size_1);
    button_vote2.creat_button("2", Color::WHITE, Color::BLACK, 3*80, 115 + (150 - 40)/2, 60, 40, ulcd_font_size_1);

    update_graf();

    title.new_label("Button & progress bar", Color::WHITE, 120, 0, 240, 80, ulcd_font_size_2, h_center, v_center);
}

void Exemple_window_1::update_graf()
{
    float per_cent = 0;
    if(resp_1 + resp_2 == 0)
        per_cent = 0;
    else
        per_cent = (float)resp_1 /(float)(resp_1 +resp_2);
    m_progress_bar_vote1.update(per_cent);
    if(resp_1 + resp_2 ==0)
        per_cent = 0;
    else
        per_cent = (float)resp_2 /(float)(resp_1 +resp_2);
    m_progress_bar_vote2.update(per_cent);
    button_vote1.set_button();
    button_vote2.set_button();
}

void Exemple_window_1::set_delegate(Exemple_window_1_delegate* p_delegate)
{
    m_delegate = p_delegate;
}
