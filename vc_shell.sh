#!/bin/bash
while [ true ]
do
  cd  ~/git/votechain_alpha.v.01
  ./remote_utils -h "Raspberry Pi" -tmp_agent
  sleep 60
done
