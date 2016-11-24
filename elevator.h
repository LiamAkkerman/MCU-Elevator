#include "stm32f4xx_hal.h"
#include <stdbool.h>

typedef bool uint1_t;

static bool update_inputs();
static bool open_door(); 
static bool close_door();
static bool move_up();
static bool move_down();

char loc_cur = 0;
bool loc_floor_1;
bool loc_floor_2;
bool loc_floor_3;