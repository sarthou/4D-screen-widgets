
/*
 * ulcd_num_pad.cpp
 *
 *
 *
 */

#include "ulcd_num_pad.h"

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
ulcd_num_pad::ulcd_num_pad(uLCD_4DLibrary* p_lcd, uint16_t foreground_color, uint16_t background_color, uint16_t x_origin, uint16_t y_origin, uint16_t width, uint16_t height) :
    button_0(p_lcd), button_1(p_lcd), button_2(p_lcd), button_3(p_lcd), button_4(p_lcd),button_5(p_lcd),
    button_6(p_lcd),button_7(p_lcd),button_8(p_lcd),button_9(p_lcd),
    button_point(p_lcd), button_cancel(p_lcd), button_enter(p_lcd)
{
    m_lcd = p_lcd;
    m_delegate = NULL;

    set_button_delegate();

    rect.origin.x = x_origin;
    rect.origin.y = y_origin;
    rect.size.width = width;
    rect.size.height = height;
    m_foreground_color = foreground_color;
    m_background_color = background_color;

    x_size = (rect.size.width-2) / 3.;
    y_size = (rect.size.height-2) / 5.;

    m_len = 0;
    m_text = "";

    draw_num_pad();
}

ulcd_num_pad::ulcd_num_pad(uLCD_4DLibrary* p_lcd):
    button_0(p_lcd), button_1(p_lcd), button_2(p_lcd), button_3(p_lcd), button_4(p_lcd),button_5(p_lcd),
    button_6(p_lcd),button_7(p_lcd),button_8(p_lcd),button_9(p_lcd),
    button_point(p_lcd), button_cancel(p_lcd), button_enter(p_lcd)
{
    m_lcd = p_lcd;
    m_delegate  = NULL;

    set_button_delegate();

    rect.origin.x = 0;
    rect.origin.y = 0;
    rect.size.width = 20;
    rect.size.height = 20;
    m_foreground_color = Color::WHITE;
    m_background_color = Color::BLACK;

    x_size = (rect.size.width-2) / 3.;
    y_size = (rect.size.height-2) / 5.;

    m_len = 0;
    m_text = "";
}

ulcd_num_pad::~ulcd_num_pad()
{

}


/*
 * private functions
 *
 */

void ulcd_num_pad::set_button_delegate()
{
    button_0.set_delegate(this);
    button_1.set_delegate(this);
    button_2.set_delegate(this);
    button_3.set_delegate(this);
    button_4.set_delegate(this);
    button_5.set_delegate(this);
    button_6.set_delegate(this);
    button_7.set_delegate(this);
    button_8.set_delegate(this);
    button_9.set_delegate(this);
    button_point.set_delegate(this);
    button_cancel.set_delegate(this);
    button_enter.set_delegate(this);
}

void ulcd_num_pad::draw_num_pad()
{
    m_lcd->gfx_draw_filled_rectangle(rect.origin.x, rect.origin.y, rect.origin.x+rect.size.width , rect.origin.y+rect.size.height, m_foreground_color);

    button_1.creat_button("1", m_foreground_color, m_background_color, rect.origin.x+1            , rect.origin.y+1, x_size, y_size, ulcd_font_size_2);
    button_2.creat_button("2", m_foreground_color, m_background_color, rect.origin.x+x_size+1     , rect.origin.y+1, x_size, y_size, ulcd_font_size_2);
    button_3.creat_button("3", m_foreground_color, m_background_color, rect.origin.x+x_size*2+1   , rect.origin.y+1, x_size, y_size, ulcd_font_size_2);

    button_4.creat_button("4", m_foreground_color, m_background_color, rect.origin.x+1            , rect.origin.y+y_size+1, x_size, y_size, ulcd_font_size_2);
    button_5.creat_button("5", m_foreground_color, m_background_color, rect.origin.x+x_size+1     , rect.origin.y+y_size+1, x_size, y_size, ulcd_font_size_2);
    button_6.creat_button("6", m_foreground_color, m_background_color, rect.origin.x+x_size*2+1   , rect.origin.y+y_size+1, x_size, y_size, ulcd_font_size_2);

    button_7.creat_button("7", m_foreground_color, m_background_color, rect.origin.x+1            , rect.origin.y+y_size*2+1, x_size, y_size, ulcd_font_size_2);
    button_8.creat_button("8", m_foreground_color, m_background_color, rect.origin.x+x_size+1     , rect.origin.y+y_size*2+1, x_size, y_size, ulcd_font_size_2);
    button_9.creat_button("9", m_foreground_color, m_background_color, rect.origin.x+x_size*2+1   , rect.origin.y+y_size*2+1, x_size, y_size, ulcd_font_size_2);

    button_point.creat_button(".", m_foreground_color, m_background_color, rect.origin.x+1            , rect.origin.y+y_size*3+1, x_size, y_size, ulcd_font_size_2);
    button_0.creat_button("0", m_foreground_color, m_background_color, rect.origin.x+x_size+1         , rect.origin.y+y_size*3+1, x_size, y_size, ulcd_font_size_2);
    button_cancel.creat_button("C", m_foreground_color, m_background_color, rect.origin.x+x_size*2+1  , rect.origin.y+y_size*3+1, x_size, y_size, ulcd_font_size_2);

    button_enter.creat_button("ENTER", m_foreground_color, m_background_color, rect.origin.x+1  , rect.origin.y+y_size*4+1, x_size*3, rect.size.height - 2 - 4*y_size, ulcd_font_size_2);
}

void ulcd_num_pad::did_select_button(ulcd_button* button)
{
    if(m_len < MAX_LEN)
    {
        m_len ++;
       if(button == &button_cancel)
        {
            m_len -= 2;
            if(m_len < 0)
                m_len = 0;
            m_text.substr(0, m_len);
        }
        else if(button == &button_enter)
            m_len -= 1;
        else
            m_text += button->get_label();
    }
    else
    {
        if(button == &button_cancel)
        {
            m_len -= 1;
            if(m_len < 0)
                m_len = 0;
            m_text.substr(0, m_len);
        }
    }

    if(button == &button_enter)
        m_delegate->enter_button_pressed();
    else
        m_delegate->text_updated();
}

/*
 * public functions
 *
 */

int16_t ulcd_num_pad::get_text(const string &p_text)
{
    m_text = p_text;
    m_len = m_text.length();
    return m_len;
}

uint16_t ulcd_num_pad::get_value()
{
    std::istringstream is(m_text);
    uint16_t ret;
    is >> ret;
    return ret;
}

void ulcd_num_pad::set_initial_value(uint16_t value)
{
    std::ostringstream os;
    os << value;
    m_text = os.str();
}

void ulcd_num_pad::clear_text()
{
    m_text = "";
    m_len = 0;
}

void ulcd_num_pad::show_num_pad()
{
    draw_num_pad();
}

void ulcd_num_pad::change_color(uint16_t foreground_color, uint16_t background_color)
{
    m_foreground_color = foreground_color;
    m_background_color = background_color;
    draw_num_pad();
}

void ulcd_num_pad::change_size(uint16_t width, uint16_t height)
{
    rect.size.width = width;
    rect.size.height = height;

    x_size = (rect.size.width - 2) / 3.;
    y_size = (rect.size.height - 2) / 5.;

    draw_num_pad();
}

void ulcd_num_pad::change_origin(uint16_t x_origin, uint16_t y_origin)
{
    rect.origin.x = x_origin;
    rect.origin.y = y_origin;
    draw_num_pad();
}

void ulcd_num_pad::new_num_pad(uint16_t foreground_color, uint16_t background_color, uint16_t x_origin, uint16_t y_origin, uint16_t width, uint16_t height)
{
    rect.origin.x = x_origin;
    rect.origin.y = y_origin;
    rect.size.width = width;
    rect.size.height = height;
    m_foreground_color = foreground_color;
    m_background_color = background_color;

    x_size = (rect.size.width - 2) / 3.;
    y_size = (rect.size.height - 2) / 5.;

    draw_num_pad();
}

void ulcd_num_pad::set_delegate(ulcd_num_pad_delegate* p_delegate)
{
    m_delegate = p_delegate;
}
