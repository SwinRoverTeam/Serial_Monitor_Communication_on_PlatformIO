
/*
-----------------------------------------------------------------------------

WORDS ON SERIAL MONITOR

------------------------------------------------------------------------------
*/

/*
#include <Arduino.h>

const int LED_PIN = GPIO_NUM_45;     // GPIO2 - safe pin on ESP32-S3 devkitm-1
bool ledState = false;

String readSerialLine() {
    String input = "";
    while (Serial.available() > 0) {
        char c = Serial.read();
        if (c == '\n') break;  // end of line
        input += c;
    }
    input.trim();  // remove whitespace
    return input;
}

void setup() {
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, LOW);
    
    Serial.begin(115200);
    delay(2000);
    Serial.println("\n=== ESP32-S3 LED CONTROL ===");
    Serial.println("Type 'on' to turn LED ON");
    Serial.println("Type 'off' to turn LED OFF");
    Serial.println("------------------------");
}

void loop() {
    if (Serial.available() > 0) {
        String command = readSerialLine();
        
        if (command == "on") {
            ledState = true;
            digitalWrite(LED_PIN, HIGH);
            Serial.println("✓ LED ON");
        }
        else if (command == "off") {
            ledState = false;
            digitalWrite(LED_PIN, LOW);
            Serial.println("✓ LED OFF");
        }
        else {
            Serial.print("Unknown command: '");
            Serial.print(command);
            Serial.println("' - use 'on' or 'off'");
        }
        
        Serial.println("------------------------");
    }
    
    delay(10);
}
*/

/*
-----------------------------------------------------------------------------

WORDS ON SERIAL MONITOR WITH NUMBER READER
SO it make it so that number is read after the word on

------------------------------------------------------------------------------
*/

#include <Arduino.h>

const int LED_PIN = GPIO_NUM_45;     // GPIO2 - safe pin on ESP32-S3 devkitm-1
bool ledState = false;

String readSerialLine() {
    String input = "";
    while (Serial.available() > 0) {
        char c = Serial.read();
        if (c == '\n') break;
        input += c;
    }
    input.trim();
    return input;
}

void setup() {
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, LOW);
    
    Serial.begin(115200);
    delay(2000);
    Serial.println("\n=== ESP32-S3 LED CONTROL ===");
    Serial.println("Type 'on 5' to turn LED ON for 5 seconds");
    Serial.println("Type 'off' to turn LED OFF");
    Serial.println("Type 'on' for permanent ON");
    Serial.println("------------------------");
}

void loop() {
    if (Serial.available() > 0) {
        String command = readSerialLine();
        
        if (command.startsWith("on")) {
            // Parse number after "on "
            int duration = 0;
            int spacePos = command.indexOf(' ');
            if (spacePos > 0) {
                String numStr = command.substring(spacePos + 1);
                duration = numStr.toInt();
            }
            
            if (duration > 0) {
                // Timed ON
                digitalWrite(LED_PIN, HIGH);
                Serial.print("✓ LED ON for ");
                Serial.print(duration);
                Serial.println(" seconds");
                
                delay(duration * 1000);  // block for duration
                digitalWrite(LED_PIN, LOW);
                Serial.println("✓ LED OFF (timeout)");
            } else {
                // Permanent ON
                digitalWrite(LED_PIN, HIGH);
                Serial.println("✓ LED ON (permanent)");
            }
        }
        else if (command == "off") {
            digitalWrite(LED_PIN, LOW);
            Serial.println("✓ LED OFF");
        }
        else {
            Serial.print("Unknown: '");
            Serial.print(command);
            Serial.println("' - use 'on 5' or 'off'");
        }
        
        Serial.println("------------------------");
    }
    
    delay(10);
}

/*
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
    
*/
