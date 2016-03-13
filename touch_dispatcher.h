/*
 * touch_dispatcher.h
 *
 *
 *
 */
#ifndef TOUCH_DISPATCHER_H
#define TOUCH_DISPATCHER_H

#include "mbed.h"
#include <vector>
#include "uLCD_4DLibrary.h"
#include "singleton.h"
#include "ulcd_rect.h"

/*
 * public types
 *
 */

typedef enum
{
    not_touched,
    touch_began,
    touch_moved,
    touch_ended
} touch_event_t;



/*
 * public class
 *
 */
class ulcd_component;

class touch_dispatcher_delegate
{

public :

  virtual ~touch_dispatcher_delegate(){}

  virtual void did_touch_screen(ulcd_origin_t touch_point, touch_event_t touch_state){}

};

class touch_dispatcher : public singleton<touch_dispatcher>
{
    friend class singleton<touch_dispatcher>;

private :

    vector<ulcd_component*> m_listening_components;

    uLCD_4DLibrary* m_lcd;

	touch_dispatcher();

	~touch_dispatcher();

public :

    void touch_periodic_task();

    void add_register_component(ulcd_component* component);

    void clear_components();

    void set_lcd(uLCD_4DLibrary* p_lcd);

};

#endif
