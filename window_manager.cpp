/*
 * window_manager.cpp
 *
 *
 *
 */

#include "window_manager.h"

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
window_manager::window_manager(uLCD_4DLibrary* p_lcd) : win_1(p_lcd), win_2(p_lcd), win_3(p_lcd),
                                                        button_win_1(p_lcd), button_win_2(p_lcd),
                                                        button_win_3(p_lcd), title(p_lcd)
{
    m_lcd = p_lcd;
    win_1.set_delegate(this);
    win_2.set_delegate(this);
    win_3.set_delegate(this);

    button_win_1.set_delegate(this);
    button_win_2.set_delegate(this);
    button_win_3.set_delegate(this);

    set_manger_window();

}

window_manager::~window_manager()
{
}


/*
 * private functions
 *
 */
void window_manager::did_select_button(ulcd_button* button)
{
    if(button == &button_win_1)
    {
        touch_dispatcher::shared_instance()->clear_components();
        win_1.set_exemple_window_1();
    }
    else if(button == &button_win_2)
    {
        touch_dispatcher::shared_instance()->clear_components();
        win_2.set_exemple_window_2();
    }
    else if(button == &button_win_3)
    {
        touch_dispatcher::shared_instance()->clear_components();
        win_3.set_exemple_window_3();
    }
}

void window_manager::did_select_return_button()
{
    touch_dispatcher::shared_instance()->clear_components();
    set_manger_window();
}

void window_manager::set_manger_window()
{
    m_lcd->gfx_clear_screen();

    button_win_1.creat_button("Button & progress bar", Color::WHITE, Color::BLACK, 10, 10, 150, 50, ulcd_font_size_1);
    button_win_1.creat_button("Button & progress bar", Color::WHITE, Color::BLACK, 10, 10, 150, 50, ulcd_font_size_1);
    button_win_2.creat_button("Num pad & Label", Color::WHITE, Color::BLACK, 10, 2*10 + 50, 150, 50, ulcd_font_size_1);
    button_win_3.creat_button("Slider & progress bar", Color::WHITE, Color::BLACK, 10, 3*10 + 2*50, 150, 50, ulcd_font_size_1);

    title.new_label("Widgets exemples by G.S", Color::WHITE, 170, 0, 140, 300, ulcd_font_size_2, h_center, v_center);
}


/*
 * public functions
 *
 */

void window_manager::run()
{
    touch_dispatcher::shared_instance()->touch_periodic_task();
}

