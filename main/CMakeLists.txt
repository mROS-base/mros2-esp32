idf_component_register(SRCS "mros2-esp32.cpp" "wifi.cpp"
                    INCLUDE_DIRS "."
                    PRIV_REQUIRES "mros2"
                    REQUIRES esp_wifi nvs_flash)
