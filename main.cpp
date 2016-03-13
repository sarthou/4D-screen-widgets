

#include "mbed.h"

#include "touch_dispatcher.h"
#include "window_manager.h"

static uLCD_4DLibrary lcd(PA_11,PA_12, PB_12,115200);
static window_manager manager(&lcd);

int main(void)
{
    touch_dispatcher::shared_instance()->set_lcd(&lcd);
    while(1) {
        manager.run();
    }
}