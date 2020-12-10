#!/bin/bash
gcc srcs/*.c -I includes/ -I ft_printf/libft/ -I ft_printf -L ft_printf/ -lftprintf
./a.out -h 6 champs/jumper.cor champs/ex.cor champs/maxidef.cor champs/examples/fluttershy.cor | head -$1 > t1
#./a.out champs/jumper.cor champs/ex.cor champs/maxidef.cor champs/examples/fluttershy.cor -dump 13504 | tail -n 100 > t1
./corewar -v 6 champs/jumper.cor champs/ex.cor champs/maxidef.cor champs/examples/fluttershy.cor | head -$1 > t2
#./corewar champs/jumper.cor champs/ex.cor champs/maxidef.cor champs/examples/fluttershy.cor -d 13504 > t2
diff t1 t2
