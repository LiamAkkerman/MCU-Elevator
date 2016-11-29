#include <stdbool.h>

typedef bool uint1_t;

static bool init(void);
static bool update_inputs(void);
static bool update_critical(void);
static bool activate_uart(void);
static bool usart_message(char* str);
static bool bcd_display(void);


static bool door_open(void); 
static bool door_open_critical(void); 
static bool door_close(void);
static bool door_cycle(void);
static bool move_up(void);
static bool move_down(void);
static bool move_stop(void);
static bool move_reset(void);


const int door_delay = 15000000;

//TODO intialize all values
static char loc_cur = 0;
static bool loc_floor_1 = 0;
static bool loc_floor_2 = 0;
static bool loc_floor_3 = 0;

static bool door_closed;
static bool moving_up;
static bool moving_down;

static bool butt_f1;
static bool butt_f2_down;
static bool butt_f2_up;
static bool butt_f3;
static bool butt_car_stop;
static bool butt_car_reset;

static bool usart_on = 0;
const static char* password_correct = "MSE Rocks!";
static char pass_array[12];


