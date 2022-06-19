/*---------------------------------------
- WeAct Studio Official Link
- taobao: weactstudio.taobao.com
- aliexpress: weactstudio.aliexpress.com
- github: github.com/WeActTC
- gitee: gitee.com/WeAct-TC
- blog: www.weact-tc.cn
---------------------------------------*/

#include "gd32f10x.h"
#include "systick.h"
#include <stdio.h>
#include "main.h"

#include "board.h"

int main(void)
{
    uint32_t tick;
    /* configure systick */
    systick_config();
    /* initilize the LEDs, USART and key */
    board_led_init();
    board_button_init();
    board_usart0_init();

    printf("\r\nWeAct Studio Core Board\r\n");
    printf("weactstudio.taobao.com\r\n");
    printf("weactstudio.aliexpress.com\r\n");
    printf("wwww.weact-tc.cn\r\n\r\n");
    printf("SystemClk:%d\r\n", SystemCoreClock);
    printf("CK_AHB is %d\r\n", rcu_clock_freq_get(CK_AHB));
    printf("CK_APB1 is %d\r\n", rcu_clock_freq_get(CK_APB1));
    printf("CK_APB2 is %d\r\n", rcu_clock_freq_get(CK_APB2));

    printf("Template\r\n");

    tick = systick_get_tick();
    while (1)
    {
        if (tick <= systick_get_tick())
        {
            tick += 100;
            if (!board_button_state_get())
            {
                board_led_toggle();
            }
            else
            {
                board_led_off();
            }
        }
    }
}
