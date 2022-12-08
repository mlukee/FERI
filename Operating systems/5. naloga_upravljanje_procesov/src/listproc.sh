#!/usr/bin/env bash

c_flag="false"										#zastavica za -c
d_flag="false"										#zastavica za -d
e_flag="false"										#zastavica za -e
ukazno_ime=""										#shranim -c [ukazno_ime]
delovna_pot=""										#shranim -d [delovna_pot]
pot_programa=""										#shranim -e [pot_programa]
stevilo_argumentov=(${#})							#stevilo podanih argumentov

if test ${stevilo_argumentov} -eq 0   				#ce nimamo arumentov, toraj -> /.listproc.sh
	then
		echo "Uporaba: ./$0 [-h] [-c ukazno_ime] [-d delovna_pot] [-e pot_programa]"
		exit 0;
	fi

while getopts "hc:d:e:" opt; do
	case "${opt}" in
	h)	#zastavica -h
		echo "Uporaba: ./$0 [-h] [-c ukazno_ime] [-d delovna_pot] [-e pot_programa]"
		exit 0;
		;;
	c)	#zastavica -c
		ukazno_ime="${OPTARG}"
		c_flag="true";
		;;
	d)	#zastavica -d
		delovna_pot="${OPTARG}"
		d_flag="true";
		;;
	e)	#zastavica -e
		pot_programa="${OPTARG}"
		e_flag="true";
		;;
	\?)
		echo "Uporaba: $0 [-h] [-c ukazno_ime] [-d delovna_pot] [-e pot_programa]"
		exit 1;
		;;
	esac
done
shift $((OPTIND-1)) 									#prestavim se na naslednjo zastavico
startingPoint=$(pwd)									#shranim zacetno pot
results=()												#array za shranjevanje procesov		
for dir in $(find /proc -maxdepth 1 -type d -name '*[0-9]*')
do
	if [ -d $dir ]
	then
					
		progName=$(readlink $dir/exe)					#pridobim program procesa
		dirName=$(readlink $dir/cwd)					#pridobim direktorij procesa
		name=$(sed '1q;d' $dir/status)					#pridobim ime procesa
		name=${name:6}									#odstranim 'Name: '
		status=$(sed '3q;d' $dir/status)				#pridobim status procesa 											
		status=${status:7}								#odstranim 'State: '
		status=${status:0:1}							#pridobim status S/R
		vmSize=$(sed '18q;d' $dir/status)				#pridobim vmSize
		vmSize=${vmSize:8}								#odstranim 'VmSize: '
		vmSize=${vmSize::-3}							#odstranim ' kb'
		pid=$(basename $dir)							#pridobim pid
		
		
		# ------------ c_flag ------------	
		if [ $c_flag == "true" ] && [ $d_flag == "false" ] && [ $e_flag == "false" ]; then
			if test "$name" == "$ukazno_ime"						#ce je ukazno ime enako ime procesa, shrani proces
			then
				results+=("$pid:$status:$((vmSize*1024)):$name")	#shranim v array						
			fi			
		fi
		# ------------ d_flag ------------			
		if [ $c_flag == "false" ] && [ $d_flag == "true" ] && [ $e_flag == "false" ]; then	
			if [[ ${delovna_pot::1} == "." ]] 						#ce se delovna pot zacne z . -> relativna pot
			then
				pot=$startingPoint									#pot nastavim na pwd, ki sem si jo shranil zgoraj
				pot+=${delovna_pot:1}								#dodam relativno pot brez . spredaj
			else
				pot=$delovna_pot									#ce ni relativna si jo samo shranim	
			fi
			
			if [[ "$dirName" -ef "$pot" ]]; then					#ce sta poti enaki, shrani proces			
				results+=("$pid:$status:$((vmSize*1024)):$name")
			fi
		fi	
		# ------------ e_flag ------------	
		if [ $c_flag == "false" ] && [ $d_flag == "false" ] && [ $e_flag == "true" ]; then	
			if [[ ${pot_programa::1} == "." ]]						#ce se pot programa zacne z . -> relativna pot
			then
				pot=$startingPoint									#pot nastavim na pwd, ki sem si jo shranil zgoraj
				pot+=${pot_programa:1}								#dodam relativno pot brez . spredaj
			else
				pot=$pot_programa									#ce ni relativna si jo samo shranim
			fi			
			if test "$progName" == "$pot"							#ce sta enaka, shrani proces
			then				
				results+=("$pid:$status:$((vmSize*1024)):$name")
			fi
		fi
		# ------------ c_flag && d_flag ------------	
		if [ $c_flag == "true" ] && [ $d_flag == "true" ] && [ $e_flag == "false" ]; then
			if [[ "$name" == "$ukazno_ime" ]]; then
				if [[ ${delovna_pot::1} == "." ]]
				then
					pot=$startingPoint
					pot+=${delovna_pot:1}
				else
					pot=$delovna_pot	
				fi	
				if [[ "$dirName" -ef "$pot" ]]; then				
					results+=("$pid:$status:$((vmSize*1024)):$name")
				fi
			fi	
		fi
		# ------------ c_flag && e_flag ------------	
		if [ $c_flag == "true" ] && [ $d_flag == "false" ] && [ $e_flag == "true" ]; then
			if [[ "$name" == "$ukazno_ime" ]]; then
				if [[ ${pot_programa::1} == "." ]]
				then
					pot=$startingPoint
					pot+=${pot_programa:1}
				else
					pot=$pot_programa
				fi			
				if test "$progName" == "$pot"
				then				
					results+=("$pid:$status:$((vmSize*1024)):$name")
				fi
			fi
		fi	
		# ------------ d_flag && e_flag ------------	
		if [ $c_flag == "false" ] && [ $d_flag == "true" ] && [ $e_flag == "true" ]; then
			if [[ ${delovna_pot::1} == "." ]]
			then
				pot=$startingPoint
				pot+=${delovna_pot:1}
			else
				pot=$delovna_pot	
			fi	
			if [[ "$dirName" -ef "$pot" ]]; then
				if [[ ${pot_programa::1} == "." ]]
				then
					pot=$startingPoint
					pot+=${pot_programa:1}
				else
					pot=$pot_programa
				fi			
				if test "$progName" == "$pot"
				then				
					results+=("$pid:$status:$((vmSize*1024)):$name")
				fi
			fi
		fi
		# ------------ c_flag && d_flag && e_flag ------------	
		if [ $c_flag == "true" ] && [ $d_flag == "true" ] && [ $e_flag == "true" ]; then
			if [[ "$name" == "$ukazno_ime" ]]; then
				if [[ ${pot_programa::1} == "." ]]
				then
					pot=$startingPoint
					pot+=${pot_programa:1}
				else
					pot=$pot_programa
				fi			
				if test "$progName" == "$pot"
				then
					if [[ ${delovna_pot::1} == "." ]]
					then
						pot=$startingPoint
						pot+=${delovna_pot:1}
					else
						pot=$delovna_pot	
					fi	
					if [[ "$dirName" -ef "$pot" ]]; then				
						results+=("$pid:$status:$((vmSize*1024)):$name")
					fi
				fi
			fi
		fi
	fi
done		

for i in "${results[@]}"								#Sprehodim se skozi polje procesov in izpisujem
do
	echo "$i"
done
exit 0;
