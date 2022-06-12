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

#include "usbd_msc_core.h"
#include "usbd_hw.h"

usb_dev usb_msc;

/*!
    \brief      release PA12 USB DP,RESET PA12
    \param[in]  none
    \param[out] none
    \retval     none
*/
void usbd_check_reset(void)
{
	if(RESET == rcu_flag_get(RCU_FLAG_PORRST))
	{
		rcu_periph_clock_enable(RCU_GPIOA);
		gpio_init(GPIOA, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_12);
		
		gpio_bit_reset(GPIOA,GPIO_PIN_12);
		delay(50/SysTick_Tick);
		gpio_bit_set(GPIOA,GPIO_PIN_12);
        gpio_init(GPIOA, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, GPIO_PIN_12);

		delay(50/SysTick_Tick);
		gpio_bit_reset(GPIOB,GPIO_PIN_2);
		delay(100/SysTick_Tick);
		gpio_bit_set(GPIOB,GPIO_PIN_2);
		delay(50/SysTick_Tick);
		gpio_bit_reset(GPIOB,GPIO_PIN_2);		
	}
	rcu_all_reset_flag_clear();
}

int main(void)
{
    uint32_t tick;
    /* configure systick */
    systick_config();
    /* initilize the LEDs, USART and key */
    board_led_init();
    board_button_init();
    board_usart0_init();

    rcu_config();
    usbd_check_reset();
    usbd_init(&usb_msc, &msc_desc, &msc_class);
    nvic_config();
    usbd_connect(&usb_msc);

    printf("\r\nWeAct Studio Core Board\r\n");
    printf("weactstudio.taobao.com\r\n");
    printf("wwww.weact-tc.cn\r\n\r\n");
    printf("SystemClk:%d\r\n", SystemCoreClock);
    printf("CK_AHB is %d\r\n", rcu_clock_freq_get(CK_AHB));
    printf("CK_APB1 is %d\r\n", rcu_clock_freq_get(CK_APB1));
    printf("CK_APB2 is %d\r\n", rcu_clock_freq_get(CK_APB2));
    
    printf("msc Test\r\n");
    
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
