#include "oled.h"

void oled_0in96_init(void)
{
    OLED_Bsp_Init();
    OLED_Init(); //初始化OLED
    OLED_Display_On();
    OLED_Clear();
    //	LED_ON;
    OLED_ShowCHinese(0, 0, 0);   //中
    OLED_ShowCHinese(18, 0, 1);  //景
    OLED_ShowCHinese(36, 0, 2);  //园
    OLED_ShowCHinese(54, 0, 3);  //电
    OLED_ShowCHinese(72, 0, 4);  //子
    OLED_ShowCHinese(90, 0, 5);  //科
    OLED_ShowCHinese(108, 0, 6); //技
    OLED_ShowString(0, 3, "1.3' OLED TEST");
    // OLED_ShowString(8,2,"ZHONGJINGYUAN");
    //	OLED_ShowString(20,4,"2014/05/01");

}

void oled_oin96_freshtest(void)
{
    static char t=' ';
    OLED_Clear();
    OLED_ShowString(0, 6, "ASCII:");
    OLED_ShowString(63, 6, "CODE:");
    OLED_ShowChar(48, 6, t); //显示ASCII字符
    t++;
    if (t > '~')
        t = ' ';
    OLED_ShowNum(103, 6, t, 3, 16); //显示ASCII字符的码值
}

void main_task()
{
    oled_0in96_init();

    while (1)
    {
        oled_oin96_freshtest();
        /*delay 1s*/
    }
}
