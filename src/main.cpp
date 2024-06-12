#include <avr/io.h>
#include <util/delay.h> // Include the delay library

/*#define UBBRO BAUDRATE  16000000/(1 * 9600) -1 */

// Function to initialize the UART
void uart_init(void) {
    // Set the baud rate
    UBRR0H = (unsigned char)(0);  // Higher byte of UBRR
    UBRR0L = (unsigned char)103;  // Lower byte of UBRR

// Enable receiver and transmitter

    UCSR0B = UCSR0B | (1 << 4);
    UCSR0B = UCSR0B | (1 << 3);
    
    //frame count and start bit predefined no need to write

}


void uart_transmit(unsigned char data) {
    // Wait for the transmit buffer to be empty
    while (!(UCSR0A & (1 << UDRE0)));

    // Put data into the buffer, sends the data
    UDR0 = data;
}

// Function to receive a character
unsigned char uart_receive(void) {
    // Wait for data to be received
    while (!(UCSR0A & (1 << RXC0)));

    // Get and return received data from buffer
    return UDR0;
}

int main(void) {
    uart_init(); // Initialize UART with the calculated UBRR value
    
    while (1) {
      
        //Transmit character 'A'
        uart_transmit('A');
        uart_transmit(' ');

        // Receive a character if available
        if (UCSR0A & (1 << RXC0)) {  // Check if data is received
            unsigned char received_data = uart_receive();
            // Echo the received character back
            uart_transmit(received_data);
            // Echo the received character back
        }

        _delay_ms(1000);
    }
    
    return 0;
}
