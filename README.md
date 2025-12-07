# Serial_Monitor_Communication_on_PlatformIO
Communication with serial monitor though PlatformIO 

Makes communitcation though sieral monitor to turn on an LED being contoled by serial. 
Using the ESP32-s3 and on platformIO.

It can be used to turn on an LED for an amount of time, making it read the nuber after the word on,
this can be used in other applications to read a number after an identifiing word/number.

-----------------------------------------------------------------

  This is the platformio.ini part of platform IO
    Copy below this into that

-----------------------------------------------------------------

[env:esp32-s3]
platform = espressif32
board = esp32-s3-devkitc-1    ; for esp32-s3
framework = arduino

monitor_speed = 115200        ; match Serial.begin baud
monitor_port  = COM8          ; COM port of esp (only if auto-detect fails)
upload_port   = COM8          ; COM port of esp (only if auto-detect fails)

monitor_filters =
    esp32_exception_decoder
    send_on_enter

build_flags =
    -D ARDUINO_USB_CDC_ON_BOOT=1
    -D ARDUINO_USB_MODE=1
    
