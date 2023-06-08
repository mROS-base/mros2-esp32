# if mros2-esp32 not found : clone https://github.com/mROS-base/mros2-esp32.git --recursive
SCRIPT_DIR=$(cd $(dirname $0); pwd)
PORT=${1:-/dev/ttyUSB0}
MROS2_DIR=${2:-${SCRIPT_DIR}/../../mros2-esp32}
WORKSPACE=${3:-${SCRIPT_DIR}/../workspace/echoback_string}
TARGET=${4:-esp32}

echo "====================="
echo "PORT: ${PORT}"
echo "MROS2_DIR: ${MROS2_DIR}"
echo "WORKSPACE: ${WORKSPACE}"
echo "TARGET: ${TARGET}"
echo "====================="

rm -rf ${SCRIPT_DIR}/.env
echo "PORT=${PORT}" > ${SCRIPT_DIR}/.env
echo "MROS2_DIR=${MROS2_DIR}" >> ${SCRIPT_DIR}/.env
echo "WORKSPACE=${WORKSPACE}" >> ${SCRIPT_DIR}/.env
echo "TARGET=${TARGET}" >> ${SCRIPT_DIR}/.env


cd ${SCRIPT_DIR}

if [ ! -d ${MROS2_DIR} ]; then
    git clone --recursive https://github.com/mROS-base/mros2-esp32.git -b main
fi

docker-compose up --build mros2_esp32
