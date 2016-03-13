/*
 * ulcd_rect.cpp
 *
 * 
 *
 */

#include "ulcd_rect.h"

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
ulcd_rect::ulcd_rect() 
{
    origin.x = 0;
    origin.y = 0;
    size.width = 0;
    size.height = 0;
}

ulcd_rect::~ulcd_rect()
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

bool ulcd_rect::is_inside(ulcd_origin_t point)
{
    if((point.x > origin.x && point.x < origin.x + size.width)&&(point.y < origin.y + size.height && point.y > origin.y))
        return true;
    else
        return false;
}




