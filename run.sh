#!/usr/bin/env bash

export PDAL_DRIVER_PATH=$PWD/cmake-build-debug/src:$PWD/build/src
export ARBITER_CONFIG_FILE=$PWD/arbiter.json

#export CURL_VERBOSE=1

docker run -d --rm --name minio -p 9000:9000 \
       -e MINIO_ACCESS_KEY=defaultkey \
       -e MINIO_SECRET_KEY=defaultkey \
       minio/minio server /data

docker exec minio sh -c "mkdir /data/foo; echo REMOTE_FILE > /data/foo/bar.txt"
if [[ ! -d /tmp/foo ]]; then mkdir /tmp/foo; fi
echo LOCAL_FILE > /tmp/foo/bar.txt

sleep 3 # let minio start

pdal pipeline -i pipeline.json

read -p "Done, press enter to quit"

docker kill minio
