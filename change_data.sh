#!/bin/bash

touch temp.txt
awk '{
	line = "'$1'"
	$line = "'$2'"
print $0}' $3 > temp.txt

cp temp.txt $3
rm temp.txt
