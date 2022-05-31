#! /bin/bash

mkdir bin
cd bin
for FILE in `ls ../src`
do
	g++ ../src/$FILE -o $FILE'.o' -c -std=c++20 -I ../include -lutil
done
ar rcs ../lib/util.a `ls -d $PWD/*`
cd ..
rm -rf bin
