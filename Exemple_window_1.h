/*
 * Exemple_window_1.h
 *
 *
 *
 */
#ifndef EXEMPLE_WINDOW_1_H
#define EXEMPLE_WINDOW_1_H

#include "uLCD_4DLibrary.h"

#include "ulcd_button.h"
#include "ulcd_progress_bar.h"

/*
 * public types
 *
 */


/*
 * public class
 *
 */
class Exemple_window_1_delegate
{

public :

  virtual ~Exemple_window_1_delegate(){}

  virtual void did_select_return_button() = 0;
};



class Exemple_window_1 :  public ulcd_button_delegate
{

private :

    uLCD_4DLibrary* m_lcd;
    ulcd_button button_vote1;
    ulcd_button button_vote2;
    ulcd_button button_return;
    ulcd_button button_reset;
    ulcd_label title;
    ulcd_progress_bar m_progress_bar_vote1;
    ulcd_progress_bar m_progress_bar_vote2;

    uint16_t resp_1;
    uint16_t resp_2;

public :

    void set_delegate(Exemple_window_1_delegate* p_delegate);

    void set_exemple_window_1();
    void update_graf();

    void did_select_button(ulcd_button* button);

    // constructor

    Exemple_window_1(uLCD_4DLibrary* p_lcd);

    ~Exemple_window_1();

    Exemple_window_1_delegate* m_delegate;
};

#endif
