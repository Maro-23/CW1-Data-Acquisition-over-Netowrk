//function declarations

void uart_SetBaudRate(int BRate);
void uart_init(int BRate);
void uart_transmit(unsigned char data);
unsigned char uart_receive(void);
int uart_receive_ready(void);
void uart_transmit_array(char* data, int size);

