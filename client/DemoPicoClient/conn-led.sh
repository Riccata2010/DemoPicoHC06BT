#!/bin/bash

BTID=<BT_ID_HERE>

wait() {
    FILE=/dev/rfcomm0
    if [[ -e "$FILE" ]]; then
        echo "EXISTS! Exit.";
        exit 0;
    else
        echo "not exists...";
        sleep 1;
        wait;
    fi
}

rfcomm connect hci0 $BTID &

wait;
