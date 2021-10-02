#!/bin/bash

# shellcheck disable=SC2034
STARTING_DIR=$(pwd)
SCRIPT_DIR="$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )"
STM32CUBE_LOCATION="$SCRIPT_DIR"/build
TARGET_NAME=MotorDriverCard.elf

STM32CUBE_VERSION=STM32Cube_FW_F0_V1.11.3
STM32CUBE_SERIES=STM32CubeF0
STM32CUBE_BRANCH=v1.11.3


function prepare_fun() {
    echo "Preparing environment"

    cd "$SCRIPT_DIR" || exit
    mkdir build
    cd build || exit

    git clone --depth 1 --branch "$STM32CUBE_BRANCH"\
      git@github.com:STMicroelectronics/"$STM32CUBE_SERIES".git \
      "$STM32CUBE_LOCATION"/STM32Cube/Repository/"$STM32CUBE_VERSION"

    cd "$SCRIPT_DIR" || exit
    python3.9 env_configuration.py -p "$STM32CUBE_LOCATION"

    echo "STM32Cube environment available in $STM32CUBE_LOCATION"
}

function build_fun() {
    echo "Building application"
    if [[ ! -d "$STM32CUBE_LOCATION" ]]
    then
        echo "$STM32CUBE_LOCATION directory does not exist. Did you forgot about environment preparation?"
        mkdir "$STM32CUBE_LOCATION"
    fi

    cd "$STM32CUBE_LOCATION" || exit
    CMAKE_FLAGS=( -DSTM32_REPO_LOCATION="$STM32CUBE_LOCATION" )
    cmake "${CMAKE_FLAGS[@]}" ..
    make "$TARGET_NAME"
    echo "Project MotorDriverCard binary built."
}

function usage() {
    echo "=================================================="
    echo "Usage: bootstrapper.sh OPTION";
    echo
    echo "Available commands in OPTION:"
    echo "prepare - Prepare environment with STM32Cube_FW_H7_V1.9.0.";
    echo "help - show this information.";
    echo
    echo "=================================================="
}

case $1 in
    prepare)
        prepare_fun
        ;;
    build)
        build_fun
        ;;
    help)
        usage
        exit 0
        ;;
    *)
        echo "Error: Invalid option"
        usage
        exit 1
        ;;
esac
