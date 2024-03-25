/*
 * Project name: Timer 1 Interrupt
 * Description: Handling a timer 1 interrupt
 * Hostpage: https://github.com/LeandroTeodoroRJ/ESP8266
 * Stable: Yes
 * Version: 1.0
 * Last Uptate: 24.03.24
 * Dependences: No
 * Current: Yes
 * Maintainer: leandroteodoro.rj@gmail.com
 * Architecture: ModeMCU Ver3.0 - ESP8266
 * Compile/Interpreter: Arduino IDE Ver 2.3.2
 * Access: Public
 * Changelog: No
 * Readme and Documents: No
 * Links: https://forum.arduino.cc/t/esp8266-interrupters-timer/957874/5
 * Other Notes: The value 312600 is aproximaly 1000ms.
 *
 */

bool led_state = true; 
unsigned long cycle_time = 1; 
unsigned long numPsec = 312600; 

void blink_led(){
  digitalWrite(LED_BUILTIN, led_state);   
  led_state = !led_state; 
}

void timer1_handle()
{
  noInterrupts();
  timer1_write(numPsec*cycle_time);
  blink_led();
  interrupts(); 
}

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  timer1_attachInterrupt(timer1_handle);
  timer1_isr_init();
  timer1_enable(TIM_DIV256, TIM_EDGE, TIM_SINGLE);
  timer1_write(numPsec*cycle_time);
}

void loop() { ; }
