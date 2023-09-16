# Please set filename that includes mros2 APIs in main/
# Note that only one file can be specified
set(APP_SRCS
                    "app.cpp"
                    CACHE STRING description)

idf_component_register(SRCS ${APP_SRCS}
                    INCLUDE_DIRS "."
                    PRIV_REQUIRES "mros2-esp32" "wifi")
