#! /bin/bash
for i in {1..100000}
do
echo $(( $( od -An -t u4 -N4 < /dev/urandom ) % $1 )) $(( $( od -An -t u4 -N4 < /dev/urandom ) % $1 ))
done