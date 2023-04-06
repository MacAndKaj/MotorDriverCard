#!/bin/bash

# shellcheck disable=SC2034
STARTING_DIR=$(pwd)
SCRIPT_DIR="$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )"
STM32CUBE_LOCATION="$STM32F0_PATH"
TARGET_NAME=MotorDriverCard.elf

. config/config.env

function build_fun() {
    echo "Preparing..."

    cd "$SCRIPT_DIR" || exit
    mkdir build
    cd build || exit

    if [[ ! -d "$STM32CUBE_LOCATION" ]]
    then
        echo "$STM32CUBE_LOCATION directory does not exist. Did you forgot about environment preparation?"
        exit 1
    fi

    CMAKE_FLAGS=( -DSTM32_REPO_LOCATION="$STM32CUBE_LOCATION" )
    cmake "${CMAKE_FLAGS[@]}" ..
    if [[ ! $? = 0 ]]
    then
      echo "cmake failure"
      exit 1
    fi

    echo "Building application"

    make "$TARGET_NAME"
    if [[ ! $? = 0 ]]
    then
      echo "make failure"
      exit 1
    fi

    echo "Project MotorDriverCard binary built."
}

function usage() {
    echo "=================================================="
    echo "Usage: bootstrapper.sh OPTION";
    echo
    echo "Available commands in OPTION:"
    echo "build - build basic application.";
    echo "help - show this information.";
    echo
    echo "=================================================="
}

case $1 in
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
