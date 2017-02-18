#!/bin/bash
while [ true ]
do
echo "[*] test"
cd  ~/git/votechain_alpha.v.01
./remote_utils -h "Intel Edison agent" -n -s
sleep 1000
# just in case something weird happens
done
