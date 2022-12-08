##!/bin/bash
filePaths=()
neuspesniPosli=()
homeDir=$(pwd)

#solution za while zanko: https://stackoverflow.com/questions/23356779/how-can-i-store-the-find-command-results-as-an-array-in-bash
#naredim array vseh direktorijov, poddirektorijov in datotek
while IFS= read -r -d $'\0'; do
	filePaths+=("$REPLY")
done < <(find . -print0)

for i in "${filePaths[@]}"
do
	if [[ $i == *sh ]]
	then
		head=$(head -n 1 "$i") #dobim prvo vrstico datoteke
		if [[ "$head" == "#!/bin/bash" ]]
		then
			parentDir=$(dirname "$i")
			baseName=$(basename "$i")
			#~ #pridobim ime posla
			imePosla=${baseName##*posel_} #odstranim prefix
			imePosla=${imePosla%".sh"} #odstranim suffix
			cd "$parentDir"	 #premaknem se v direktorij kjer je datoteka
			if [[ $baseName == posel_* ]]	#preverjam, da je datoteka pravilno poimenovana
			then
				output=$(bash "$baseName") #pridobim ouput OK/Fail
				bash "$baseName" > posel_"$imePosla".out #shranim v .out datoteko
				tail=$(echo $output|awk '{print$NF}') #pridobim zadni output
				if [[ "$tail" == "Fail" ]] #ce je output fail ga dodam v neuspesne posle
				then
					neuspesniPosli+=("$baseName")
				fi
			fi
			cd $homeDir #se premaknem nazaj v direktorij kjer sem zacel
		fi
	fi
done
#Izpisem neuspesne posle
echo "Neuspesni posli: "
for i in "${neuspesniPosli[@]}"
do
  echo $i
done
