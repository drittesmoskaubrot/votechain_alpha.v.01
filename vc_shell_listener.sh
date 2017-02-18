#!/bin/bash
while [ true ]
do
echo "[*] test"
cd  /home/rogue/git/votechain_alpha.v.01/
./remote_utils -h "Acer Aspire | v5 agent" -n -s
sleep 60
# just in case something weird happens
killall mosquitto_sub
done
