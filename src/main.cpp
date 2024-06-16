#include "uart.h"

int main(void) {
    uart_init(); // Initialize UART

    char received_string[MAX_STRING_LENGTH]; // Buffer to store received string

    while (1) {
        // Receive a string and store it in the buffer
        uart_receive_string(received_string);

        // Echo the received string back
        uart_transmit_string("Received: ");
        uart_transmit_string(received_string);
        uart_transmit_string("\r\n");
    }
    
    return 0;
}
