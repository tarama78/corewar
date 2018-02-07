make -C asm CFLAGS=-"Wall -Wextra -Werror" 
echo "TEST ASM"
./asm/asm doc/vm_champs/champs/42.s
echo
./asm/asm doc/vm_champs/champs/Gagnant.s
echo
./asm/asm doc/vm_champs/champs/barriere.s
echo
./asm/asm doc/vm_champs/champs/jumper.s
echo
./asm/asm doc/vm_champs/champs/maxidef.s
echo
./asm/asm doc/vm_champs/champs/slider2.s
echo
./asm/asm doc/vm_champs/champs/toto.s
echo
./asm/asm doc/vm_champs/champs/Octobre_Rouge_V4.2.s
echo
./asm/asm doc/vm_champs/champs/lde.s
echo
./asm/asm doc/vm_champs/champs/mortel.s
echo
./asm/asm doc/vm_champs/champs/Car.s
echo
./asm/asm doc/vm_champs/champs/ex.s
