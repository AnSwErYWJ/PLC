#!/bin/bash

datetime=$(date +%Y%m%d-%H%M%S)
if [ -s sensordata.txt ]; then
	cp sensordata.txt ./backup/data-$datetime.txt
fi
echo '' > sensordata.txt

if [ -s log.txt ]; then
	cp log.txt ./backup/log-$datetime.txt
fi
echo '' > log.txt

if [ -s sensor_raw.txt ]; then
	cp sensor_raw.txt ./backup/raw-$datetime.txt
fi
echo '' > sensor_raw.txt

echo "backup complete..."
