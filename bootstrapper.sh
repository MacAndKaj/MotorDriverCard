#!/usr/bin/bash

fun_build()
{

}

fun_deploy()
{

}

fun_test()
{

}

echo "Running bootsrapper for MotorDriverCard"

case $1 in
    build)
        echo "here build";;

    *)
        echo "Unknown command. FAIL!"
        exit 1;;
esac