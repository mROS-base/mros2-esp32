set(SRCS "src/mros2.cpp"
        "embeddedRTPS/src/communication/UdpDriver.cpp"
        "embeddedRTPS/src/messages/MessageTypes.cpp"
        "embeddedRTPS/src/messages/MessageReceiver.cpp"
        "embeddedRTPS/src/discovery/TopicData.cpp"
        "embeddedRTPS/src/discovery/ParticipantProxyData.cpp"
        "embeddedRTPS/src/discovery/SEDPAgent.cpp"
        "embeddedRTPS/src/discovery/SPDPAgent.cpp"
        "embeddedRTPS/src/storages/PBufWrapper.cpp"
        "embeddedRTPS/src/ThreadPool.cpp"
        "embeddedRTPS/src/entities/Participant.cpp"
        "embeddedRTPS/src/entities/Domain.cpp"
        "embeddedRTPS/src/entities/StatelessReader.cpp"
        "embeddedRTPS/thirdparty/Micro-CDR/src/c/common.c"
        "embeddedRTPS/thirdparty/Micro-CDR/src/c/types/basic.c"
        "embeddedRTPS/thirdparty/Micro-CDR/src/c/types/string.c"
        "embeddedRTPS/thirdparty/Micro-CDR/src/c/types/sequence.c"
        "embeddedRTPS/thirdparty/Micro-CDR/src/c/types/array.c"
        "embeddedRTPS/thirdparty/lwip/default_netif.c"
        "embeddedRTPS/thirdparty/lwip/lwip.c"
        "cmsis-esp32/cmsis-esp.c")

set(INCS "include"
        "include/mros2"
        "mros2_msgs"
        "custom_msgs"
        "embeddedRTPS/include"
        "embeddedRTPS/thirdparty/lwip"
        "embeddedRTPS/thirdparty/Micro-CDR/include"
        "cmsis-esp32/include")

idf_component_register(
        SRCS ${SRCS}
        INCLUDE_DIRS ${INCS})

add_custom_command(
        OUTPUT templates.hpp
        COMMAND python3 ${COMPONENT_PATH}/mros2_header_generator/templates_generator.py ${CMAKE_SOURCE_DIR}/main ${COMPONENT_PATH})
add_custom_target(Template SOURCES templates.hpp)
add_dependencies(${COMPONENT_LIB} Template)
        