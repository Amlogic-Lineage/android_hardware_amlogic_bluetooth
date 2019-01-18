#include <linux/gpio.h>
#include <linux/delay.h>
#include <linux/mmc/host.h>

#include "btmtk_sdio.h"

#include "inc/hi_drv_gpio.h"
#include "inc/hi_type.h"
#include "inc/hardware.h"
#include "inc/io.h"

#ifdef SWITCH_MODULE_H
//=================================================================================================
/*
* This code segment is to power up MT7668s PMU_Enable 
* pin and push platform detect SDIO device.
*/
extern set_usb_bt_power(int is_power);
#if 0
typedef enum hi_GPIO_DIR_E
 {
     HI_DIR_OUT = 0,
     HI_DIR_IN  = 1,
 } HI_GPIO_DIR_E;

#define RTL_REG_ON_GPIO            (4*8 + 3) // for GIOP 4-3, MT7668s PMU_Enable pin
#define REG_BASE_CTRL              __io_address(0xf8a20008)
extern set_usb_bt_power(int is_power);
/*SDIO1~bit0, better WIFI TP
**SDIO0~bit1, low SDIO CLK*/
#define SDIO_INDEX_0 (0x02) //bit1,LOW CLK
#define SDIO_INDEX_1 (0x01) //bit0,CLK=200M
#define SDIO_DETECT_MASK SDIO_INDEX_1

static HI_S32 power_mt7668s_pmu(HI_U32 value)
{
    HI_S32  s32Status, ret = HI_SUCCESS;
    s32Status = HI_DRV_GPIO_SetDirBit(RTL_REG_ON_GPIO, HI_DIR_OUT);
    if ( s32Status!= HI_SUCCESS )
    {
         pr_info("gpio(%d) HI_DRV_GPIO_SetDirBit HI_DIR_OUT failed(%d) \n", RTL_REG_ON_GPIO, s32Status);
         ret = s32Status;
    }

    s32Status = HI_DRV_GPIO_WriteBit(RTL_REG_ON_GPIO, 0); //pull down first.
    if ( s32Status!= HI_SUCCESS )
    {
        pr_info("gpio(%d) HI_DRV_GPIO_WriteBit value(%d) failed(%d) \n", RTL_REG_ON_GPIO, value, s32Status);
        ret = s32Status;
    }


    if(value == 0)
        goto finish;

    mdelay(100);                                           //then delay

    s32Status = HI_DRV_GPIO_WriteBit(RTL_REG_ON_GPIO, 1);  //pull up again
    if ( s32Status!= HI_SUCCESS )
    {
        pr_info("gpio(%d) HI_DRV_GPIO_WriteBit value(%d) failed(%d) \n", RTL_REG_ON_GPIO, value, s32Status);
        ret = s32Status;
    }

finish:
    pr_info("##%s##: Power %s PMU %s", __this_module.name, value == 1? "ON" : "OFF", ret == HI_SUCCESS? "succeed!":"failed!");
    return ret;
}

void detect_mt7668s(bool present) {
    u32 regval;
    if(present)
    {
        regval = readl(REG_BASE_CTRL);
        regval |= SDIO_DETECT_MASK;
        writel(regval, REG_BASE_CTRL);
    }
    else
    {
        regval = readl(REG_BASE_CTRL);
        regval &= ~(SDIO_DETECT_MASK);
        writel(regval, REG_BASE_CTRL);
    }
    regval = readl(REG_BASE_CTRL);
    regval &= SDIO_DETECT_MASK;
    pr_info("##%s##: %s SDIO device %s", __this_module.name, present == 1? "Catch" : "Drop", regval? "succeed!":"failed!");
}
#endif
void platform_bt_power_on(void)
{
   // return;
    //power_mt7668s_pmu(1);
    set_usb_bt_power(0);
    mdelay(200);
    //detect_mt7668s(1);
    set_usb_bt_power(1);
    mdelay(2000);
    
    pr_info("##%s##: %s done!", __this_module.name, __FUNCTION__);
}

void platform_bt_power_off(void)
{
    set_usb_bt_power(0);
    pr_info("##%s##: %s done!", __this_module.name, __FUNCTION__);
}

void platform_dongle_reset(void)
{

    return;
    //power_mt7668s_pmu(1);
    pr_info("##%s##: %s done!", __this_module.name, __FUNCTION__);
}
EXPORT_SYMBOL_GPL(platform_dongle_reset);
EXPORT_SYMBOL_GPL(platform_bt_power_on);
EXPORT_SYMBOL_GPL(platform_bt_power_off);
//========================================================================
#endif

