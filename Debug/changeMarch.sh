#!/bin/bash
find ./src/ -type f -print0 | xargs -0 sed -i 's/-march=native/-march=armv6zk -mcpu=arm1176jzf-s -mfloat-abi=hard -mfpu=vfp/g'
find ./src/ -type f -print0 | xargs -0 sed -i 's/-g3//g'
