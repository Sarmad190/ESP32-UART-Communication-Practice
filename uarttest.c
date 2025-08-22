#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/uart.h"
#include "driver/gpio.h"

#define UART_PORT   UART_NUM_0
#define TX_PIN      GPIO_NUM_17
#define RX_PIN      GPIO_NUM_16
#define BUFFER_SIZE 1024
#define BAUD_RATE   115200

void app_main(void) {
    // Install driver 
    uart_driver_install(UART_PORT, BUFFER_SIZE, 0, 0, NULL, 0);

    // UART configuration
    uart_config_t sega = {
        .baud_rate = BAUD_RATE,
        .data_bits = UART_DATA_8_BITS,
        .parity    = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .source_clk = UART_SCLK_APB
    };

    // Apply config
    uart_param_config(UART_PORT, &sega);

    // Set pins
    uart_set_pin(UART_PORT, TX_PIN, RX_PIN, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);

    while (1) {
        const char *alpha = "Hello Pakistan\n";
        uart_write_bytes(UART_PORT, alpha, strlen(alpha));
        vTaskDelay(pdMS_TO_TICKS(1000)); // 1 second delay
    }
}
