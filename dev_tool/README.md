# mros2-esp32 dev-tool

Building mros2-esp32 tool using docker.

<br>

## Requirements

- USB accessable docker-compose environment

<br>

## Usage

M5Stack CoreS3

```bash
bash build_example.bash /dev/ttyACM0 ../../mros2-esp32 ../workspace/echoback_string esp32s3
```

### Arguments

- 1: Serial port (default: `/dev/ttyUSB0`)
- 2: Path to mros2-esp32 (default: `../../mros2-esp32`)
    - If this directory does not exist, it will be cloned from [mROS-base/mros2-esp32](https://github.com/mROS-base/mros2-esp32).
- 3: Path to workspace (default: `../workspace/echoback_string`)
- 4: Target board (esp32, esp32s2, esp32s3...) (default: `esp32`)

<br>
