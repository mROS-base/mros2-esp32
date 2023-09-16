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
        )

set(INCS "mros2/include"
        "mros2/include/mros2"
        "mros2/mros2_msgs"
        "mros2/embeddedRTPS/include"
        "mros2/embeddedRTPS/thirdparty/lwip"
        "mros2/embeddedRTPS/thirdparty/Micro-CDR/include"
        "cmsis-esp32/include"
        "platform"
        "workspace/custom_msgs"
        ${CMAKE_SOURCE_DIR}/main
        )

idf_component_register(
        SRCS ${SRCS}
        INCLUDE_DIRS ${INCS})

add_custom_command(
        OUTPUT templates.hpp
        COMMAND python3 ${COMPONENT_PATH}/mros2/mros2_header_generator/templates_generator.py --outdir ${COMPONENT_PATH}/platform --file ${CMAKE_SOURCE_DIR}/main/${APP_SRCS})
add_custom_target(Template SOURCES templates.hpp)
add_dependencies(${COMPONENT_LIB} Template)
