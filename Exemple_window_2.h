/*
 * Exemple_window_2.h
 *
 *
 *
 */
#ifndef EXEMPLE_WINDOW_2_H
#define EXEMPLE_WINDOW_2_H

#include "uLCD_4DLibrary.h"

#include "ulcd_button.h"
#include "ulcd_label.h"
#include "ulcd_num_pad.h"
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
class Exemple_window_2_delegate
{

public :

    virtual ~Exemple_window_2_delegate(){}

    virtual void did_select_return_button() = 0;
};



class Exemple_window_2 :  public ulcd_button_delegate, public ulcd_num_pad_delegate
{

private :

    uLCD_4DLibrary* m_lcd;
    ulcd_button button_return;
    ulcd_label aff;
    ulcd_label title;
    ulcd_num_pad num_pad;

    void text_updated();

    void enter_button_pressed();

    void did_select_button(ulcd_button* button);

public :

    void set_delegate(Exemple_window_2_delegate* p_delegate);

    void set_exemple_window_2();

    // constructor

    Exemple_window_2(uLCD_4DLibrary* p_lcd);

    ~Exemple_window_2();

    Exemple_window_2_delegate* m_delegate;
};

#endif
