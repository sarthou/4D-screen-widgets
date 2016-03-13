/*
 * ulcd_component.h
 *
 *
 *
 */

#ifndef ULCD_COMPONENT_H
#define ULCD_COMPONENT_H

#include "ulcd_rect.h"
#include "touch_dispatcher.h"

/*
 * public types
 *
 */



/*
 * public class
 *
 */


class ulcd_component : public touch_dispatcher_delegate
{

private :


public :
    ulcd_rect rect;
    // constructor

    ulcd_component();

    ~ulcd_component();

};

#endif
