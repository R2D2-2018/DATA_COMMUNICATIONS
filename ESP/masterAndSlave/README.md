* Pin assignment:
 
    * slave :
        * GPIO25 is assigned as the data signal of i2c slave port
        * GPIO26 is assigned as the clock signal of i2c slave port
    * master:
        * GPIO18 is assigned as the data signal of i2c master port
        * GPIO19 is assigned as the clock signal of i2c master port
 
* Connection:
 
    * connect GPIO18 with GPIO25
    * connect GPIO19 with GPIO26
    * no need to add external pull-up resistors, driver will enable internal pull-up resistors.
 
* Implementation:
 
    * i2c master(ESP32) will write data to i2c slave(ESP32).
    * i2c master(ESP32) will read data from i2c slave(ESP32).
