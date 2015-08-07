#!/bin/bash

mkdir src/ 2> /dev/null
protoc --cpp_out=src/ Connection.proto
protoc --cpp_out=src/ Game.proto
