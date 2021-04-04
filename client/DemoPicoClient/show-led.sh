#!/bin/bash
echo $* | sudo picocom -qri /dev/rfcomm0
echo "show led number $*"
exit 0
