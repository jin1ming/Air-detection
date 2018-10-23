#!/bin/bash
for((i=1;;i++));  
do   
	iotx-sdk-c/output/release/bin/./SensorAll
	iotx-sdk-c/output/release/bin/./mqtt-example
	sleep 5
done  
