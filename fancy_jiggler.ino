
#define _TASK_SLEEP_ON_IDLE_RUN  // Power saving when nothing to do

#include <avr/wdt.h>
#include <avr/sleep.h>
#include <avr/power.h>
#include <TaskScheduler.h>
#include <Mouse.h>

#define BOOT_BLINK_INTERVAL 500L
#define ACTIVITY_BLINK_INTERVAL 200L
#define JIGGLE_INTERVAL TASK_MINUTE
#define BOOT_BLINK_COUNT 4L
#define WDT_KICK TASK_SECOND

// Forward declarations
void wdt_f();
void blink_f();
void jiggle_f();

Scheduler ts;
Task wdt_task(WDT_KICK, TASK_FOREVER, wdt_f, &ts);
Task boot_task(BOOT_BLINK_INTERVAL, BOOT_BLINK_COUNT*2, blink_f, &ts);
Task activity_blink_task(ACTIVITY_BLINK_INTERVAL, 4, blink_f, &ts);
Task jiggle_task(JIGGLE_INTERVAL, TASK_FOREVER, jiggle_f, &ts);

void wdt_f() {
  // Macro
  wdt_reset();
}

void blink_f() {
  static bool led_state = false;

  // Toggle LED
  if (led_state)  {
    digitalWrite(LED_BUILTIN, LOW);
  } else {
    digitalWrite(LED_BUILTIN, HIGH);
  }
  led_state = !led_state;
}

void jiggle_f() {
  static int parity = -1;

  activity_blink_task.setIterations(4);
  activity_blink_task.enable();
  Mouse.move(parity, 0, 0);
  parity *= -1;
  
}

void setup() {
  // WDT
  wdt_enable(WDTO_2S);
  wdt_reset();

  // Disable components to save power
  power_adc_disable();
  power_spi_disable();
  power_twi_disable(); // I2C
  power_usart0_disable(); // Serial

  // Mouse
  Mouse.begin();

  // Schedule
  wdt_task.enable();
  boot_task.enable();
  jiggle_task.enableDelayed(JIGGLE_INTERVAL/2);
}

void loop() {
  ts.execute();
}
