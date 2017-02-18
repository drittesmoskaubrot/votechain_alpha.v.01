#!/bin/bash
while [ true ]
do
  cd  ~/git/votechain_alpha.v.01
  ./remote_utils -h "HP 32bit agent" -tmp_agent
  sleep 60
done
