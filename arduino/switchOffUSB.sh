ControlFlag="Y"
while [ "$ControlFlag" = "Y" ]
do
  echo 0 | sudo tee /sys/devices/platform/soc/3f980000.usb/buspower >/dev/null
  sleep 5
  echo 1 | sudo tee /sys/devices/platform/soc/3f980000.usb/buspower >/dev/null
done
