FROM espressif/idf:release-v5.1

RUN git clone https://github.com/pallets/jinja.git -b 3.1.2 /jinja2

COPY ./build_mros2.bash /tmp/build_mros2.bash
