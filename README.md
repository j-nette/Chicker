# Chicker
Chip &amp; Kick Tester for UBC Thunderbots.

## Important Files
- main.py: run this after connecting the board to the laptop to launch the GUI
- main.cpp: found in src folder. Upload this code first.
    - if using Platform.io, build before uploading. The first build will take longer due to downloading the ESP32 core libraries.
    - if not using Platform.io, remove the "#include <Arduino.h>". You will also need to download the [ESP32 core libraries](https://github.com/espressif/arduino-esp32/tree/master). 
 
- Python libraries:
  ```shell
  pip install tkinter
  pip install pyserial
  ```

## Other random things
- in the folder src, you can find all .cpp files 
- in the folder include, you can find all .h files
- in the folder playground, you can find all WIP files and individual functions

