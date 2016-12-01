

static char init(void);
static char update_inputs(void);
static char update_critical(void);
static char update_location(void);
static char activate_uart(void);
static char usart_message(char* str);
static char bcd_display(void);
static char button_display(void);


static char door_open(void); 
static char door_open_critical(void); 
static char door_close(void);
static char door_cycle(void);
static char move_up(void);
static char move_down(void);
static char move_stop(void);
static char move_reset(void);


const int door_delay = 1500000;
/*const int motor_delay_1;													//TODO delete 1 and 3 if not needed
const int motor_delay_2 = 10000;									//TODO figure out value from physical model
const int motor_delay_3;*/

//TODO intialize all values
static char loc_cur = 0;
static char loc_floor_1 = 0;
static char loc_floor_2 = 0;
static char loc_floor_3 = 0;

static char door_closed;
static char moving_up;
static char moving_down;

static char butt_f1;
static char butt_f2_down;
static char butt_f2_up;
static char butt_f3;
static char butt_car_stop;
static char butt_car_reset;

static char usart_on = 0;
const static char* password_correct = "MSE Rocks!";
static char pass_array[12];


