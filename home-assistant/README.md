# ESPHome ePaper Calendar: Software

## ESPHome
The `esphome` directory contains the files you need to compile a firmware for your device. 
1. Move the files and folders contained in the directory to the directory containing the configuration files of your ESPHome installation.
2. Add the required fonts to the folder `fonts`.
3. If you haven’t yet, add your WiFi credentials to `secrets.yaml`.
4. Open `epaper-frame-calendar.yaml` and change the settings at the top accordantly.
3. Connect the USB port of the Inkplate to your computer and flash it with the ESPHome firmware.

## Home Assistant
1. Add the configurations from `configuration.yaml` to the `configuration.yaml` file of your Home Assistant installation (don't just overwrite yours!).
2. Modify the entity ids in `configuration.yaml' to reflect your calendars. 
3. Copy the `python_scripts` folder into your Home Assistant config folder.
4. Add your calendar names to `CALENDAR_NAMES` in `esp_calendar_data_conversion.py` if they contain more than one word.
5. Restart Home Assistant.
6. After having compiled and installed the firmware, add your device to Home Assistant. It should automatically appear as a device to add under `Settings -> Devices`.
