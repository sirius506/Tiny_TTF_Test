/**v_sc
 * @file main
 *
 */

/*********************
 *      INCLUDES
 *********************/
#define _DEFAULT_SOURCE /* needed for usleep() */
#include <stdlib.h>
#include <unistd.h>
#define SDL_MAIN_HANDLED /*To fix SDL's "undefined reference to WinMain" issue*/
#include <SDL2/SDL.h>
#include "lvgl/lvgl.h"
#include "lvgl/examples/lv_examples.h"
#include "lvgl/demos/lv_demos.h"
#include "lvgl/src/dev/sdl/lv_sdl_window.h"
#include "lvgl/src/dev/sdl/lv_sdl_mouse.h"
#include "lvgl/src/dev/sdl/lv_sdl_mousewheel.h"
#include "lvgl/src/dev/sdl/lv_sdl_keyboard.h"
#include <pthread.h>

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/
static lv_disp_t * hal_init(lv_coord_t w, lv_coord_t h);

/**********************
 *  STATIC VARIABLES
 **********************/
static lv_obj_t *slider;
/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *      VARIABLES
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/


int main(int argc, char **argv)
{
  (void)argc; /*Unused*/
  (void)argv; /*Unused*/

  /*Initialize LVGL*/
  lv_init();
  hal_init(320, 240);

  lv_example_tiny_ttf_3();

  while(1) {
      /* Periodically call the lv_task handler.
       * It could be done in a timer interrupt or an OS task too.*/
      lv_timer_handler();
      usleep(1 * 1000);
  }

  return 0;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

/**
 * Initialize the Hardware Abstraction Layer (HAL) for the LVGL graphics
 * library
 */
static lv_disp_t * hal_init(lv_coord_t w, lv_coord_t h)
{

  lv_disp_t * disp = lv_sdl_window_create(w, h);
  lv_indev_t * mouse = lv_sdl_mouse_create();
  lv_indev_set_group(mouse, lv_group_get_default());
  lv_indev_set_disp(mouse, disp);

  LV_IMG_DECLARE(mouse_cursor_icon); /*Declare the image file.*/
  lv_obj_t * cursor_obj;
  cursor_obj = lv_img_create(lv_scr_act()); /*Create an image object for the cursor */
  lv_img_set_src(cursor_obj, &mouse_cursor_icon);           /*Set the image source*/
  lv_indev_set_cursor(mouse, cursor_obj);             /*Connect the image  object to the driver*/

  lv_indev_t * mousewheel = lv_sdl_mousewheel_create();
  lv_indev_set_disp(mousewheel, disp);

  lv_indev_t * keyboard = lv_sdl_keyboard_create();
  lv_indev_set_disp(keyboard, disp);
  return disp;
}
