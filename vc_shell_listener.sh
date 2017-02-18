#!/bin/bash
while [ true ]
do
echo "[*] test"
cd  ~/git/votechain_alpha.v.01/
./remote_utils -h "HP 32bit agent" -n -s
sleep 60
# just in case something weird happens
killall mosquitto_sub
done
