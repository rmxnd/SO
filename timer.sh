#!/bin/bash
h=0
m=0
t=30
for ((s=0; ;s+=30))
	do
		if [ $s -ge 60 ]; then
			if [ $m -ge 59 ]; then
				m=$(( m - 60 ))
				h=$(( h + 1 ))
			fi
			s=$(( s - 60 ))
			m=$(( m + 1 ))
		fi
	echo $h ore $m minuti $s secondi
	sleep $t
	done
