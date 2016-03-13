/*
 * touch_dispatcher.cpp
 *
 * 
 *
 */

#include "touch_dispatcher.h"
#include "ulcd_component.h"

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
touch_dispatcher::touch_dispatcher()
{
}

touch_dispatcher::~touch_dispatcher()
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
void touch_dispatcher::touch_periodic_task()
{
   touch_event_t touch_state;
   uint8_t vector_index;
   
   
    switch(m_lcd->touch_get(0))
    {
        case 1 :
        {
            touch_state = touch_began;
        }
        break;
        case 2 :
        {
            touch_state = touch_ended;
        }
        break;
        case 3 :
        {
            touch_state = touch_moved;
        }
        break;
        default :
        {
            touch_state = not_touched;
        }
        break;
    }
    
    if(touch_state != not_touched)
    {
        ulcd_origin_t touch_point;
        touch_point.x = m_lcd->touch_get(1);
        touch_point.y = m_lcd->touch_get(2);
        
        for(vector_index = 0; vector_index < m_listening_components.size(); vector_index ++)
        {
            ulcd_component *component = m_listening_components[vector_index];
            component->did_touch_screen(touch_point, touch_state);
        }
    }
}
    
void touch_dispatcher::add_register_component(ulcd_component* component)
{
    m_listening_components.push_back(component); 
}
    
void touch_dispatcher::clear_components()
{
    m_listening_components.clear();
}
  
void touch_dispatcher::set_lcd(uLCD_4DLibrary* p_lcd)
{    
    m_lcd = p_lcd;
    
    m_lcd->touch_set(0);
    m_lcd->touch_detect_region(0,0,480,480);
}

