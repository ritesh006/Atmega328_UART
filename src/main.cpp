#include <avr/io.h>
#include <util/delay.h> // Include the delay library
#define MAX_STRING_LENGTH 64 // Maximum length of the received string
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


// Function to transmit a null-terminated string
void uart_transmit_string(const char *str) {
    // Transmit each character until null terminator is reached
    while (*str != '\0') {
        uart_transmit(*str);
        str++;
    }
}


// Function to receive a character
unsigned char uart_receive(void) {
    // Wait for data to be received
    while (!(UCSR0A & (1 << RXC0)));

    // Get and return received data from buffer
    return UDR0;
}

// Function to receive a string terminated by '\r' or '\n'
void uart_receive_string(char *buffer) {
    char received_char;
    uint8_t index = 0;

    // Receive characters until '\r' or '\n' is received
    while (1) {
        received_char = uart_receive();
        if (received_char == '\r' || received_char == '\n') {
            break;
        }
        buffer[index++] = received_char;

        // Check if buffer overflow occurred
        if (index >= (MAX_STRING_LENGTH - 1)) {
            break;
        }
    }

    // Null-terminate the string
    buffer[index] = '\0';
}

int main(void) {
    uart_init(); // Initialize UART with the calculated UBRR value
    
    while (1) {
         char received_string[MAX_STRING_LENGTH]; // Buffer to store received string
        //  uart_transmit_string("Hello, World!\r\n");
        //Transmit character 'A'
        // uart_transmit('A');
        // uart_transmit(' ');

        // Receive a character if available
        // if (UCSR0A & (1 << RXC0)) {  // Check if data is received
        //     unsigned char received_data = uart_receive();
        //     // Echo the received character back
        //     uart_transmit(received_data);
        //     // Echo the received character back
        // }

        // _delay_ms(1000);



         // Receive a string and store it in the buffer
        uart_receive_string(received_string);

        // Echo the received string back
        uart_transmit_string("Received: ");
        uart_transmit_string(received_string);
        uart_transmit_string("\r\n");
    }
    
    return 0;
}
