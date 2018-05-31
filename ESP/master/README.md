* Pin assignment:
 
    * slave : ESP32_0
        * GPIO25 is assigned as the data signal of i2c slave port
        * GPIO26 is assigned as the clock signal of i2c slave port
    * master: ESP32_1
        * GPIO18 is assigned as the data signal of i2c master port
        * GPIO19 is assigned as the clock signal of i2c master port
 
* Connection:
 
    * connect GPIO18 from ESP32_1 with GPIO25 from ESP32_0
    * connect GPIO19 from ESP32_1 with GPIO26 from ESP32_0
    * no need to add external pull-up resistors, driver will enable internal pull-up resistors.
 
* Implementation:
 
    * i2c master(ESP32_1) will write data to i2c slave(ESP32_0).
    * i2c master(ESP32_1) will read data from i2c slave(ESP32_0).