#!/bin/bash
cd `dirname $0`
rm -rf build
mkdir -p build
cd build
cmake ..
make
sudo cp `dirname $0`/liblfxSpeed.so /usr/lib/dde-dock/plugins/liblfxSpeed.so
killall dde-dock
cd ..
rm -rf build