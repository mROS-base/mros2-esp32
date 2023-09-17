set(SRCS "mros2/src/mros2.cpp"
        "mros2/embeddedRTPS/src/communication/UdpDriver.cpp"
        "mros2/embeddedRTPS/src/messages/MessageTypes.cpp"
        "mros2/embeddedRTPS/src/messages/MessageReceiver.cpp"
        "mros2/embeddedRTPS/src/discovery/TopicData.cpp"
        "mros2/embeddedRTPS/src/discovery/ParticipantProxyData.cpp"
        "mros2/embeddedRTPS/src/discovery/SEDPAgent.cpp"
        "mros2/embeddedRTPS/src/discovery/SPDPAgent.cpp"
        "mros2/embeddedRTPS/src/storages/PBufWrapper.cpp"
        "mros2/embeddedRTPS/src/ThreadPool.cpp"
        "mros2/embeddedRTPS/src/entities/Participant.cpp"
        "mros2/embeddedRTPS/src/entities/Domain.cpp"
        "mros2/embeddedRTPS/src/entities/StatelessReader.cpp"
        "mros2/embeddedRTPS/thirdparty/Micro-CDR/src/c/common.c"
        "mros2/embeddedRTPS/thirdparty/Micro-CDR/src/c/types/basic.c"
        "mros2/embeddedRTPS/thirdparty/Micro-CDR/src/c/types/string.c"
        "mros2/embeddedRTPS/thirdparty/Micro-CDR/src/c/types/sequence.c"
        "mros2/embeddedRTPS/thirdparty/Micro-CDR/src/c/types/array.c"
        "mros2/embeddedRTPS/thirdparty/lwip/default_netif.c"
        "cmsis-esp32/lwip.c"
        "cmsis-esp32/cmsis-esp.c"
        "platform/wifi/wifi.c"
        "platform/mros2-platform.cpp"
        )

set(INCS "mros2/include"
        "mros2/include/mros2"
        "mros2/mros2_msgs"
        "mros2/embeddedRTPS/include"
        "mros2/embeddedRTPS/thirdparty/lwip"
        "mros2/embeddedRTPS/thirdparty/Micro-CDR/include"
        "cmsis-esp32/include"
        "platform"
        "platform/wifi"
        "workspace/custom_msgs"
        ${CMAKE_SOURCE_DIR}/main
        )

idf_component_register(
        SRCS ${SRCS}
        INCLUDE_DIRS ${INCS}
        REQUIRES nvs_flash esp_wifi)

# Generate plaform/templates.hpp from mros2 application code
## You can add dir(s) in `--indir` if you have several dirs 
## that contain application code files
add_custom_command(
        OUTPUT templates.hpp
        COMMAND python3 ${COMPONENT_PATH}/mros2/mros2_header_generator/templates_generator.py --outdir ${COMPONENT_PATH}/platform --indir ${CMAKE_SOURCE_DIR}/main)
add_custom_target(Template SOURCES templates.hpp)
add_dependencies(${COMPONENT_LIB} Template)

# Disable CONFIG_LWIP_IPV6 in sdkconfig
add_custom_command(
        OUTPUT sdkconfig
        COMMAND sed -i 's/CONFIG_LWIP_IPV6=y/CONFIG_LWIP_IPV6=n/g' ${CMAKE_SOURCE_DIR}/sdkconfig)
add_custom_target(Sdkconfig SOURCES sdkconfig)
add_dependencies(${COMPONENT_LIB} Sdkconfig)
