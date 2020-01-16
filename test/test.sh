#!/bin/sh

SCRIPTPATH="$( cd "$(dirname "$0")" ; pwd -P )"

outFile="$SCRIPTPATH/out.txt"

rm -rf $outFile

for i in `seq 0 200`; do
	$SCRIPTPATH/../bin/pi $i $outFile
done

out=$(cat $SCRIPTPATH/out.txt)
ref=$(cat $SCRIPTPATH/ref.txt)

if [ "$out" = "$ref" ]; then
	echo "OK"
	return 0
else
	echo "NOK"
	return 1
fi

