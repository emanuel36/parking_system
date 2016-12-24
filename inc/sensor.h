#define LED_B		23
#define LED_G		26
#define LED_Y		47
#define LED_R		46
#define BUZZER 		60
#define CLK			30
#define LOAD		31
#define MSG			48

void init_system();
void alerta(unsigned int level);
void show_number(int number);
void send_spi(int msg);
void display(int number);