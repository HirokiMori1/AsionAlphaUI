#!/bin/bash

# xrdp audio setting
export PULSE_SERVER=127.0.0.1

source  /opt/ros/melodic/setup.bash
source /home/kufushatec/cartographer_ws/install_isolated/setup.bash
source /home/kufushatec/asion_ws/devel/setup.bash

/usr/bin/gnome-terminal -e /home/kufushatec/build-AsionAlphaUI-unknown-Debug/AsionAlphaUI
