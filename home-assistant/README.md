# ESPHome ePaper Calendar: Software Guide

## Setting Up ESPHome

This guide details the process for compiling and uploading the firmware to an Inkplate 6 board for your ePaper calendar device using ESPHome.

### 1. Firmware Preparation:

- Install ESPHome, you can follow [this guide](https://esphome.io/guides/getting_started_hassio#installing-esphome-dashboard) to get started.
- If you are using [Hass.io](https://www.home-assistant.io/blog/2017/07/25/introducing-hassio/), you will need the [Samba share](https://github.com/home-assistant/addons/blob/master/samba/DOCS.md) add-on to access the required folders within your Home Assistant installation.

   - Locate the `esphome` directory within the project files of this repository.
   - Transfer all contents from this directory to your ESPHome configuration directory.
     - If your configuration directory has existing `fonts` or `includes` directories, merge their contents instead of overwriting.
     - The same applies to an existing `secrets.yaml` file.

### 2. Font Configuration:
   - Download the required fonts and add them to the appropriate subdirectories within the `fonts` folder in your ESPHome directory.

### 3. WiFi Credentials:
   - Add your WiFi SSID and password to the `secrets.yaml` file, if not already done.

### 4. Configuration File Adjustments:
   - Open `epaper-frame-calendar.yaml`.
   - Modify the settings at the beginning of the file as needed. Mandatory changes include:
     - Adding an `api_key` (generate one [here](https://esphome.io/components/api.html)).
     - Adding an `ota_key` for protection against unauthorized firmware updates.
   - See the **ESPHome Configuration File Details** at the end for more information on the available settings.

### 5. Firmware Flashing:
   - Connect the Inkplate device to your computer via USB.
   - Compile and upload the firmware to the device using ESPHome.

## Integrating with Home Assistant

To make your ePaper calendar work properly, you need to add some sensors to Home Assistant by following these additional steps:

### 1. Configuration Sensors and Integrations:
   - Append the contents of `configuration.yaml` from this project to your Home Assistant `configuration.yaml` file without overwriting existing configurations you have made.
   - If sections like `template:` or `input_boolean:` already exist, append the new configurations below them without duplicating section names.

### 2. Entity IDs Update:
   - Update the entity IDs  (`calendar.x`, `calendar.y` ...) in `configuration.yaml` to match those of your Home Assistant calendars.

### 3. Script Setup:
   - Copy the `python_scripts` folder into your Home Assistant configuration directory. If a `python_scripts` folder already exists, transfer the `esp_calendar_data_conversion.py` file into it.

### 4. Calendar Name Adjustments:
   - If using multi-word calendar names, add these to the `CALENDAR_NAMES` list in `esp_calendar_data_conversion.py`, for example:
     ```python
     CALENDAR_NAMES = {"calendar.family_events": "Family Events", "calendar.work_events": "Work Events"}
     ```

### 5. Home Assistant Restart:
   - Restart Home Assistant to apply the changes.

### 6. Adding your device to Home Assistant:
   - After the firmware is compiled and uploaded, and the Inkplate board is powered, add it to Home Assistant for data synchronization. It should be detected under `Settings -> Devices`.

## ESPHome Configuration File Details

Customize your device further with these configurations in `epaper-frame-calendar.yaml`:

- **Device Information:** Set unique device names, sleep durations, and calendar data entity IDs.
  - `device_name`: This should be a unique name on your network, restricted to lower case letters, numbers and hyphens, and up to 24 characters long.
  - `friendly_name`: Name used in Home Assistant as the integration and device name. Entities that the device provides are automatically prefixed with it.
  - `deep_sleep_duration`: The amount of time the device will sleep after checking for an updated calendar. Increasing this will increase battery life, but will also increase the time it takes to update the display.
  - `night_time_deep_sleep_duration`: Extended sleep time from 0 am to 6 am to save battery overnight.
  - `calendar_data_entity_id`: The entity ID of the calendar sensor added in the Home Assistant configuration step. Normally you will not need to change this, but if you are running multiple ePaper calendars you may want each one to use a different data source, and if you have set up a second sensor in Home Assistant you can set this here.
  - `calendar_data_update_during_deep_sleep_entity_id`: As with the last one, you should not need to change this unless you are running multiple ePaper calendars. The entity named here is used to indicate whether the screen should be refreshed after waking from deep sleep.
- **API and OTA Keys:** Secure your device and communication.
  - `api_key`: Encrypts communication with Home Assistant. Generate a random one [here](https://esphome.io/components/api.html).
  - `ota_key`: This key protects your device from unauthorised OTA updates and is required to send a firmware update to the device over the network.
- **Fonts and Display:** Adjust font paths if necessary.
   - `font_medium`: The path to a font file that contains the medium version of the font you are using.
  - `font_bold`: The path to a font file that contains the bold version of the font you are using.
  - `font_mdi`: The path to a font file containing the Material Design Icons web font.
  - **Note:** If you are using custom fonts, you will need to adjust some of the positioning within the lambda code that draws the display.
- **Battery Voltage Settings:** Specify the full and empty voltage levels for accurate battery status display.
  - `battery_full_voltage`: The voltage of the battery you are using when fully charged.
  - `battery_empty_voltage`: Conservative voltage when the battery is considered empty (e.g. if empty at 3V, use 3.2V).

The `Danger Zone` section contains advanced configurations and the code responsible for drawing display content. Don't change this section unless you are familiar with ESPHome and understand the potential impact on device behaviour.
