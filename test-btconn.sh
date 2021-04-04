BTID=<BT_ID_HERE>

echo "EXIT picocom PRESS CTRL+a+x"
sleep 5

sudo rfcomm connect hci0 $BTID &
sleep 6

sudo picocom -c /dev/rfcomm0

