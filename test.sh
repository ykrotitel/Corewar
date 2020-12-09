#!/bin/bash


folder="champ111"
path="/Users/ssoraka/Desktop/days/corewar/material/work/valid"
tests=($(ls $path | grep ".cor$"))

save="/Users/ssoraka/Desktop/days/corewar/material/work/$folder.txt"
touch $save

number=(1 20 50 80 150 200 600 800 1400 2400 5000 6000 7000 8000 10000 11000 12000 13000 14000 15000 16000 17000 18000 19000 20000 21000 22000 23000 25000 26000 27000)
##number=(10000 11200 12400 13600 14800 15000)

file1="champs/jumper.cor champs/ex.cor champs/maxidef.cor champs/examples/fluttershy.cor"
file2="youforkmytralala.cor"

  gcc srcs/*.c -I includes/ -I ft_printf/libft/ -I ft_printf -L ft_printf/ -lftprintf
		for (( c=1; c<=20; c++ ))
#		for c in ${!number[@]}
		do
			let num=8526+c*1
#			num="${number[$c]}"

			my=$(./a.out -dump $num $file1)
			notmy=$(./corewar -d $num $file1)

			if [ "$my" == "$notmy" ]
			then
				echo "$file1 $file2	$num: идентичны."
			else
				echo "$file1 $file2	$num: имеют различия."
				diff  <(echo "$my" ) <(echo "$notmy")
				exit 0;
			fi
		done