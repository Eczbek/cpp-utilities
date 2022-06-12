#! /bin/bash

mkdir temp
for FILE in `ls src`
do
	g++ src/$FILE -o temp/$FILE'.o' -c -std=c++20 -I include/ -l util
done
ar crs util.a `ls -d temp/*`
rm -r temp
