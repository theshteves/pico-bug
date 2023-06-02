#include "hardware/adc.h"
#include "pico/cyw43_arch.h"
#include "pico/stdlib.h"


int main(int argv, const char *argc[]) {
  stdio_init_all();
  if (cyw43_arch_init()) {
      printf("Wi-Fi init failed");
      return -1;
  }

  adc_init();
  adc_gpio_init(26);
  adc_select_input(4); // on-board temperature sensor

  while (true) {
    uint16_t result = adc_read();
    float voltage = result * 3.3f / (1 << 12);

    float temperature = 27 - (voltage - 0.706f) / 0.001721f;

    printf("Temperature: %.2f C\n", temperature);

    int delay = 100 * (int)temperature;
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1); // on-board LED
    sleep_ms(delay);
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
    sleep_ms(250);
  }
  return 0;
}
