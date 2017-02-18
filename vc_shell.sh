#!/bin/bash
while [ true ]
do
  cd  ~/git/votechain_alpha.v.01
  ./remote_utils -h "Dell Optiplex-755 agent" -tmp_agent
  sleep 60
done
