echo "Compiling $1"
arduino-cli compile --fqbn esp8266:esp8266:nodemcu $1
echo "Upload $1 (Y/n)? "
read UploadVar
if [ "$UploadVar" = "Y" ]
then
        echo "Uploading $1..."
        arduino-cli upload -p /dev/tty$2 --fqbn esp8266:esp8266:nodemcu $1
fi
        echo "Process complete"
printf "\nOpen Serial Monitor (Y/n)? "
read OpenSerialMonitor
if [ "$OpenSerialMonitor" = "Y" ]
then
        arduino-cli monitor -p /dev/tty$2
fi
