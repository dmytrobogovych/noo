#!/bin/bash

#number=`cat build_number.h`
number=`sed -n -e 's/#define APP_BUILD_NUMBER *//p' build_number.h | tr -d '\r'`
let number++
printf "// Auto generated file ! Please do not edit !\r\n#define APP_BUILD_NUMBER $number" > build_number.h 
