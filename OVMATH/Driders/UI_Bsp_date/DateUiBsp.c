#include "DateUiBsp.h"
#include "ui.h"  // 包含UI定义，用于访问ui_Label1、ui_Label12、ui_Label54等标签
#include <stdio.h>  // 用于sprintf函数格式化字符串

// 获取当前日期时间
void DateUiBsp_GetDateTime(DateTime_t *datetime)
{
    if (datetime == NULL)
        return;
    
    // 从RTC读取当前时间和日期
    RTC_GetDateTime(&datetime->hours, &datetime->minutes, &datetime->seconds,
                   &datetime->year, &datetime->month, &datetime->date, &datetime->weekday);
}

// 更新时间UI显示
void DateUiBsp_UpdateTimeUI(void)
{
    DateTime_t datetime;
    char time_str[6];  // 用于存储时间字符串，格式为"HH:MM"
    char ampm_str[3];  // 用于存储上午/下午字符串，格式为"am"或"pm"
    
    // 获取当前日期时间
    DateUiBsp_GetDateTime(&datetime);
    
    // 格式化时间字符串
    sprintf(time_str, "%02d:%02d", datetime.hours, datetime.minutes);
    
    // 更新时间标签
    lv_label_set_text(ui_Label12, time_str);
    
    // 确定上午/下午
    if (datetime.hours < 12)
    {
        sprintf(ampm_str, "am");
    }
    else
    {
        sprintf(ampm_str, "pm");
    }
    
    // 更新上午/下午标签
    lv_label_set_text(ui_Label54, ampm_str);
}

// 更新日期UI显示
void DateUiBsp_UpdateDateUI(void)
{
    DateTime_t datetime;
    char date_str[20];  // 用于存储日期字符串，格式为"2026年2月17日"
    
    // 获取当前日期时间
    DateUiBsp_GetDateTime(&datetime);
    
    // 格式化日期字符串（年份加上2000，因为RTC存储的是后两位）
    sprintf(date_str, "20%02d年%d月%d日", datetime.year, datetime.month, datetime.date);
    
    // 更新日期标签
    lv_label_set_text(ui_Label1, date_str);
}

// 更新日期时间UI显示
void DateUiBsp_UpdateDateTimeUI(void)
{
    // 更新时间UI
    DateUiBsp_UpdateTimeUI();
    
    // 更新日期UI
    DateUiBsp_UpdateDateUI();
}
