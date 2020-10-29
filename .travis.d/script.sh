#!/usr/bin/env bash

set -e

if [ -n "$AUTH" ]; then
	AUTH="--auth $AUTH"
fi

# Basic NIDs ordering and existence
.travis.d/definition_check.py
.travis.d/definition_ordering.sh db.yml
.travis.d/definition_ordering.sh db_365.yml

# Install SDK
git clone --depth=1 https://github.com/DolceSDK/ddpm.git
python3 ddpm/dolcesdk-update.py $AUTH
rm -rf ddpm

# Check headers with gcc/g++ -c
INCLUDE_DIR=./include
find "$INCLUDE_DIR" -type f -name '*.h' | xargs -I FN -n 1 -P $(nproc) arm-dolce-eabi-gcc -I"$INCLUDE_DIR" -c FN -o /dev/null
find "$INCLUDE_DIR" -type f -name '*.h' | xargs -I FN -n 1 -P $(nproc) arm-dolce-eabi-g++ -I"$INCLUDE_DIR" -c FN -o /dev/null

# Remove installed headers and stubs
cd "$DOLCESDK/arm-dolce-eabi/include"
rm -rf psp2{,kern,common} dolcesdk dolcesdk{,kern}.h
cd "$DOLCESDK/arm-dolce-eabi/lib"
rm -rf *_stub{,_weak}.a

# Build headers and stubs and install
cd "$TRAVIS_BUILD_DIR"
cmake .
make install install-stubs

# Install packages
dolcesdk-update-packages $AUTH

# Build samples
git clone --depth=1 https://github.com/DolceSDK/samples.git
cd samples
cmake .
make # use only 1 job to avoid race condition
