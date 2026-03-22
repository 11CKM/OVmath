#include "Lvgl_task.h"


void Lvgl_task(void *pvParameters)
{
    uint8_t ID_Moad = 0;
    while(1)
    {
        if (lv_disp_get_inactive_time(NULL) < 1000)
        {
            xQueueSend(IdQueue,&ID_Moad,0);
        }
        
        lv_task_handler();
        delay_ms(1);
    }
}

