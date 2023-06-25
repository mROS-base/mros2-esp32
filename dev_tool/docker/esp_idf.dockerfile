FROM ubuntu:22.04

ENV TZ=Asia/Tokyo
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone
ENV DEBIAN_FRONTEND=noninteractive

RUN apt update && apt install locales && \
    locale-gen en_US en_US.UTF-8 && \
    update-locale LC_ALL=en_US.UTF-8 LANG=en_US.UTF-8 && \
    apt -y clean && \
    rm -rf /var/lib/apt/lists/*
ENV LANG=en_US.UTF-8

RUN apt-get update && \
    apt-get install -y \
    git wget flex bison gperf python3 python3-venv cmake ninja-build ccache libffi-dev libssl-dev dfu-util libusb-1.0-0

RUN mkdir -p /esp
RUN cd /esp && git clone --recursive https://github.com/espressif/esp-idf.git -b v5.2-dev && \
    cd /esp/esp-idf && \
    ./install.sh all

RUN /bin/bash -c "source /esp/esp-idf/export.sh && \
    pip3 install jinja2"

COPY ./build_mros2.bash /tmp/build_mros2.bash
