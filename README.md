# TTGO_Stocks_Monitor
Simple way to monitor stocks using the TTGO board
![TTGO_stocks](https://user-images.githubusercontent.com/4991664/188702522-1bdbed61-4df3-4bc1-9498-89af43558483.jpg)

# PlatformIO Build

Please install first [PlatformIO](http://platformio.org/) open source ecosystem for IoT development compatible with **Arduino** IDE and its command line tools (Windows, MacOs and Linux).

## Configure

Set your Wifi crendentials and API key in the configuration file: platformio.ini or export your configuration via environment variables like this:

``` bash
export PIO_WIFI_SSID="your-wifi-ssid"
export PIO_WIFI_PASSWORD="your-wifi-password"
export FINHUB_API_KEY="your-api-key"
```

## Firmware upload

For compiling and uploading the firmware via USB cable, you only need execute the next command in the root directory:

``` bash
pio run --target upload
```


