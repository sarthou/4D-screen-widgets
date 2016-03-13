/*
 * ulcd_rect.h
 *
 *
 *
 */

#ifndef ULCD_RECT_H
#define ULCD_RECT_H

#include "mbed.h"

/*
 * public types
 *
 */

typedef struct
{
    uint16_t x;
    uint16_t y;

} ulcd_origin_t;

typedef struct
{
    uint16_t width;
    uint16_t height;

} ulcd_size_t;


/*
 * public class
 *
 */


class ulcd_rect
{

private :


public :
    ulcd_origin_t origin;
    ulcd_size_t size;

    bool is_inside(ulcd_origin_t point);

    // constructor

    ulcd_rect();

    ~ulcd_rect();

};

#endif
