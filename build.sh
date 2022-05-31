#! /bin/bash

mkdir temp
for FILE in `ls src`
do
	g++ src/$FILE -o temp/$FILE'.o' -c -std=c++20 -I include -lutil
done
ar crs lib/util.a `ls -d temp/*`
rm -r temp
