# ESP8266
ESP8266 - nodeMCU projects repository.

## Important Notes
-- It's a good pratice to define a serial monitor default baud rate. \
-- The hardware used is a nodeMCU. \
-- To nodeMCU the input is defined to GPIO number. \
-- The input is defined by GPIO number, not Dx number.

## List of Content
digital_ouput  ::  Blink on-board led and setput digital out pin. \
digital_input  ::  Reading a GPIO digital level pin. \
analog_input  ::  Reading the analog input pin. \
timer1_interrupt  ::  How to blink led without delay. \
wifi-connection  ::  How to login in wifi network. \
webserver  ::  Launching a webserver. \
LED_with_webserver  ::  Control a led status from web browser. \
humidity_temperature_sensor  ::  Reading a DHT11 sensor. \
sensor_webserver  ::  Show on browser humidity and temperature from DHT11 sensor. \
mqtt_mosquitto_sensor  ::  Publishing a sensor value to Mosquitto MQTT local broker. \
mqtt_mosquitto_subscripe ::  Receiving a subscripe message from topic. \
mqtt_mosquitto_subscripe_LED :: Control the on-board LED with subscripe message from topic. 
