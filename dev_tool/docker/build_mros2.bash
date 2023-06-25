#!/bin/bash
SCRIPT_DIR=/mros2-esp32/workspace/target/

. /esp/esp-idf/export.sh

cd ${SCRIPT_DIR}
rm -rf ${SCRIPT_DIR}/build/

idf.py set-target ${TARGET}
if [ $? -ne 0 ]; then
    echo "Failed to set target"
    exit 1
fi

sed -i 's/CONFIG_LWIP_IPV6=y/CONFIG_LWIP_IPV6=n/g' ${SCRIPT_DIR}/sdkconfig

idf.py build
idf.py -p ${PORT} flash
if [ $? -ne 0 ]; then
    echo "Failed to flash"
    exit 1
fi
