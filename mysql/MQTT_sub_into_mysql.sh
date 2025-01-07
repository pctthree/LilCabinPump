#!/bin/bash

# Install mosquitto_sub and mysql-client if not present
# sudo apt-get install mosquitto-clients mysql-client

# MQTT and MySQL details
MQTT_TOPIC="lilcabinpump"
MQTT_BROKER="localhost"
MQTT_PORT="1883" # Default MQTT port
MYSQL_HOST="localhost"
MYSQL_USER="pi"
MYSQL_PASSWORD="lilcabin"
MYSQL_DATABASE="LilCabinPump"
MYSQL_TABLE="pumpTemp"


# Function to handle MQTT messages and insert them into MySQL
function insert_into_mysql() {
    message="$1"

    # Local temperature wttr.in
    LOCAL_TEMP="$(/usr/bin/curl -s 'wttr.in/honesdale?m&format=%t')"

    # Escape special characters in the message for safe SQL insertion
    message=$(echo "$message" | sed "s/'/\\'/g")

    # Construct the SQL query
    query="INSERT INTO $MYSQL_TABLE (message, local_temp) VALUES ('$message', '$LOCAL_TEMP')"

    echo $query
    # Execute the SQL query
    mysql -h "$MYSQL_HOST" -u "$MYSQL_USER" -p"$MYSQL_PASSWORD" "$MYSQL_DATABASE" -e "$query"
}

# Subscribe to the MQTT topic and process messages
ControlLoop="Y"
while [ "$ControlLoop" = "Y" ]
do
    mosquitto_sub -h "$MQTT_BROKER" -p "$MQTT_PORT" -t "$MQTT_TOPIC" -C 1 | while read message; do
        insert_into_mysql "$message"
#         echo "received message $message"
    done
done

