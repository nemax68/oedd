
/**
 * @file main
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>   // for nanosleep
#include "lv_drv_conf.h"
#include "lvgl/lvgl.h"
#include "lv_drivers/display/ST7789.h"
#include "lv_drivers/indev/evdev.h"
#include "lv_drivers/itf/i2c.h"
#include "lv_drivers/itf/spi.h"
#include "lv_drivers/itf/gpio.h"
#include "oegl_app/oe_gui.h"
#include "oegl_app/oe_mqueue.h"
#include <oedd.h>

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/
/**********************
 *  STATIC VARIABLES
 **********************/
/**********************
 *      MACROS
 **********************/
/**********************
 *   GLOBAL FUNCTIONS
 **********************/

void InitGuiLog(void)
{
	setlogmask (LOG_UPTO (LOG_NOTICE));

	openlog (OEGUILOG_NAME, LOG_CONS | LOG_PID | LOG_NDELAY, LOG_LOCAL1);
	syslog (LOG_NOTICE, "Program started by User %d", getuid ());

	closelog ();
}

void GuiLog(const char *fmt, ...)
{
	va_list arg;

	openlog (OEGUILOG_NAME, LOG_CONS | LOG_PID | LOG_NDELAY, LOG_LOCAL1);

	va_start (arg, fmt);
	syslog (LOG_NOTICE, fmt, arg);
	va_end (arg);

	closelog ();
}

int main(void)
{

    InitGuiLog();

    /*Initialize LittlevGL*/
    lv_init();

    /*Initialize posix queues */
    if( posix_command_init()!=0 ) {
    	GuiLog("Failed to init posix queue");
       	return -1;
    }

    if(i2c_init("/dev/i2c-2",0x36)){
    	GuiLog("Failed to init i2c");
       	return -1;
    }

   	if(spi_open("/dev/spidev0.0")){
   		GuiLog("Failed to init spi");
       	return -1;
   	}

   	if(gpio_init("/sys/class/gpio/gpio2_pc5/direction","out","/sys/class/gpio/gpio2_pc5/value",1)){
   		GuiLog("Failed to init gpio");
   		return -1;
   	}

    /*St7789 device init*/
   	if(st7789_init()){
       	GuiLog("Failed to init ST7789");
   		return -1;
   	}

   	evdev_init();

   	init_gui_evdev();

    /*Add a display the LittlevGL sing the frame buffer driver*/
    lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
    disp_drv.disp_flush = st7789_flush;      /*It flushes the internal graphical buffer to the frame buffer*/
    lv_disp_drv_register(&disp_drv);

    /*Create a GUI*/
   	init_gui();

    while(1) {
        lv_tick_inc(5);
        /* Periodically call the lv_task handler.
         * It could be done in a timer interrupt or an OS task too.*/
        lv_task_handler();
        usleep(5 * 1000);       /*Just to let the system breath*/
        handle_posix_command();
    }

    return 0;
}
