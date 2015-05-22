#!/bin/bash

datetime=$(date +%Y%m%d-%H%M%S)
if [ -s sensordata.txt ]; then
	cp sensordata.txt ./backup/$datetime.txt
fi
echo '' > sensordata.txt

if [ -s log.txt ]; then
    cp log.txt ./backup/log-$datetime.txt
fi
echo '' > log.txt

echo "backup complete..."
echo "Restart Successfully, Getting data... Input ctrl+c to interrupt"
#sudo ./Serial
