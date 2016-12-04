static char init(void);

static char update_inputs(void);
static char update_critical(void);
static char update_location(void);

static char activate_uart(void);
static char usart_message(char* str);

static char bcd_display(void);
//static char button_display(void);

static char door_open(void); 
static char door_open_critical(void); 
static char door_close(void);
static char door_cycle(void);

static char move_up(void);
static char move_down(void);
static char move_stop(void);





static char loc_cur = 0;
static char loc_floor_1 = 0;
static char loc_floor_2 = 0;
static char loc_floor_3 = 0;

//const char* usart_password = "MSE rocks"
static char usart_on = 0;

static char butt_f1 = 0;
static char butt_f2_down = 0;
static char butt_f2_up = 0;
static char butt_f3 = 0;
static char butt_car_stop = 0;
static char butt_car_reset = 0;

const int door_delay = 700000;
static char door_closed = 1;

static char moving_up = 0;
static char moving_down = 0;

