#!/bin/bash
while [ true ]
do
echo "[*] test"
cd  ~/git/votechain_alpha.v.01/
./remote_utils -h "Acer | v5  agent" -n -s
sleep 60
# just in case something weird happens
done
