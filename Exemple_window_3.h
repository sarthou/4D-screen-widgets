/*
 * Exemple_window_2.h
 *
 *
 *
 */
#ifndef EXEMPLE_WINDOW_3_H
#define EXEMPLE_WINDOW_3_H

#include "uLCD_4DLibrary.h"

#include "ulcd_button.h"
#include "ulcd_slider.h"
#include "ulcd_label.h"
#include "ulcd_progress_bar.h"
#include <string>
#include <sstream>

/*
 * public types
 *
 */


/*
 * public class
 *
 */
class Exemple_window_3_delegate
{

public :

    virtual ~Exemple_window_3_delegate(){}

    virtual void did_select_return_button() = 0;
};



class Exemple_window_3 :  public ulcd_button_delegate, public ulcd_slider_delegate
{

private :

    uLCD_4DLibrary* m_lcd;
    ulcd_button button_return;
    ulcd_label title;
    ulcd_slider m_slider;
    ulcd_progress_bar m_progress;

    void did_select_button(ulcd_button* button);

    void did_move_slider(ulcd_slider* slider, float p_per_cent);

public :

    void set_delegate(Exemple_window_3_delegate* p_delegate);

    void set_exemple_window_3();

    // constructor

    Exemple_window_3(uLCD_4DLibrary* p_lcd);

    ~Exemple_window_3();

    Exemple_window_3_delegate* m_delegate;
};

#endif
