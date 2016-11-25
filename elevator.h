#include <stdbool.h>

typedef bool uint1_t;

static bool update_inputs(void);
static bool open_door(void); 
static bool close_door(void);
static bool move_up(void);
static bool move_down(void);

char loc_cur = 0;
bool loc_floor_1;
bool loc_floor_2;
bool loc_floor_3;

bool door_closed;

bool butt_f1_up;
bool butt_f2_down;
bool butt_f2_up;
bool butt_f3_down;

bool butt_car_f1;
bool butt_car_f2;
bool butt_car_f3;
bool butt_car_stop;
