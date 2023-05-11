idf_component_register(SRCS "app.cpp"
                    INCLUDE_DIRS "."
                    PRIV_REQUIRES "mros2"
                    REQUIRES esp_wifi nvs_flash)
