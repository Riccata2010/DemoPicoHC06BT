#include <stdio.h>
#include <stdarg.h>
#include "pico/stdlib.h"
#include "hardware/uart.h"
#include "hardware/irq.h"

#define UART_ID                uart1
#define UART_BAUD_RATE         9600
#define UART_PIN_TX            4
#define UART_PIN_RX            5
#define DATA_BITS              8
#define STOP_BITS              1
#define PARITY                 UART_PARITY_NONE

/* ---------------------------------------- */
/* ---------------------------------------- */
/* ---------------------------------------- */

typedef unsigned int uint_t;

const uint_t ON_BOARD_LED_PIN    = 25;
const uint_t LED_1_PIN           = 15; 
const uint_t LED_2_PIN           = 14; 
const uint_t LED_3_PIN           = 13; 

bool led_flag[3] = {false, false, false};

void led(char, bool);
void init_led();
void ginit(uint_t, ...) ;
void my_fun_on_receive();
void show_led_ready_on_pico(); 
void init_uart();
void test_led();

/* ---------------------------------------- */
/* ---------------------------------------- */
/* ---------------------------------------- */

void my_fun_on_receive()
{
	while (uart_is_readable(UART_ID))
	{
		const char READ = uart_getc(UART_ID);
		
		led(READ - 36, led_flag[READ - 49] = !led_flag[READ - 49]);
	}
}

void ginit(uint_t count, ...) 
{
		
	va_list a_ptr;
	va_start(a_ptr, count);

	int i;
	for(i = 0; i < count; i++) {
		
		/* Recupero il numero del pin */	
		int pin = va_arg(a_ptr, int);

		/* Inizializzo ed indico la direzione */
		gpio_init(pin);
		gpio_set_dir(pin, GPIO_OUT);

		/* In avvio pongo tutto a 0 */
		gpio_put(pin, 0);
	}

	va_end(a_ptr);
}

void test_led()
{
	led(LED_1_PIN, true);
	sleep_ms(1000);
	led(LED_2_PIN, true);
	sleep_ms(1000);
	led(LED_3_PIN, true);
	sleep_ms(1000);
	led(LED_1_PIN, false);
	led(LED_2_PIN, false);
	led(LED_3_PIN, false);
}

void init_led()
{
	ginit(4, ON_BOARD_LED_PIN, LED_1_PIN, LED_2_PIN, LED_3_PIN);
}

void show_led_ready_on_pico() 
{
	/* Accendo il led sulla board */	
	gpio_put(ON_BOARD_LED_PIN, 1);
}

void led(char pin, bool show)
{
	/* Attivo i led del semaforo */
	gpio_put(pin, show ? 1 : 0);
}

void init_uart()
{
    /* Inizialmente setto ad un rate di base */
    uart_init(UART_ID, 2400);

    sleep_ms(5000);
    printf("RUN\n");

    /* Imposto i pin TX/RX che voglio usare */
    gpio_set_function(UART_PIN_TX, GPIO_FUNC_UART);
    gpio_set_function(UART_PIN_RX, GPIO_FUNC_UART);

    int speed = uart_set_baudrate(UART_ID, UART_BAUD_RATE);
    printf("BAUD RATE: %d\n", speed);

    /* Imposto off CTS/RTS e format */
    uart_set_hw_flow(UART_ID, false, false);
    uart_set_format(UART_ID, DATA_BITS, STOP_BITS, PARITY);
    uart_set_fifo_enabled(UART_ID, false);

    int irq = UART_ID == uart1 ? UART1_IRQ : UART0_IRQ;
    irq_set_exclusive_handler(irq, my_fun_on_receive);
    irq_set_enabled(irq, true);
    uart_set_irq_enables(UART_ID, true, false);
    
    show_led_ready_on_pico();
    printf("READY\n");
}

int main()
{
	stdio_init_all();
	init_led();
	test_led();
	init_uart();

    while (1)
    {
        tight_loop_contents();
    }

    printf("END\n");

    return 0;
}
