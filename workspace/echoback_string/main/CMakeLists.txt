# Please set filename of mros2 application in main/
set(APP_SRCS "app.cpp")

idf_component_register(SRCS ${APP_SRCS}
                    INCLUDE_DIRS "."
                    PRIV_REQUIRES "mros2-esp32" "wifi")
