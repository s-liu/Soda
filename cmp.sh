#!/bin/bash
for i in `seq 3 3 9999`
do
	./1soda soda.config $i >> output1
done
