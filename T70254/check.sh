#!/bin/bash
while true;do
	./gen
	./bf
	./sqrt
	if diff bf.out sqrt.out;then
		echo AC
	else
		echo WA
		exit 0
	fi
done
