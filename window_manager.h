/*
 * window_manager.h
 *
 *
 *
 */
#ifndef WINDOW_MANAGER_H
#define WINDOW_MANAGER_H

#include "uLCD_4DLibrary.h"

#include "Exemple_window_1.h"
#include "Exemple_window_2.h"
#include "Exemple_window_3.h"
#include "ulcd_button.h"
#include "ulcd_label.h"


/*
 * public types
 *
 */


/*
 * public class
 *
 */

class window_manager :  public Exemple_window_1_delegate, public Exemple_window_2_delegate, public Exemple_window_3_delegate, public ulcd_button_delegate
{

private :

    uLCD_4DLibrary* m_lcd;
    Exemple_window_1 win_1;
    Exemple_window_2 win_2;
    Exemple_window_3 win_3;

    ulcd_button button_win_1;
    ulcd_button button_win_2;
    ulcd_button button_win_3;

    ulcd_label title;

    void did_select_return_button();
    void did_select_button(ulcd_button* button);

    void set_manger_window();

public :

    // constructor

    void run();

    window_manager(uLCD_4DLibrary* p_lcd);

    ~window_manager();
};

#endif
