make -C asm CFLAGS=-"Wall -Wextra -Werror" 
echo "TEST ASM"
./asm/asm doc/vm_champs/champs/42.s
mv doc/vm_champs/champs/42.cor diff.cor
./doc/vm_champs/asm doc/vm_champs/champs/42.s
diff diff.cor doc/vm_champs/champs/42.cor
echo
./asm/asm doc/vm_champs/champs/Gagnant.s
mv doc/vm_champs/champs/Gagnant.cor diff.cor
./doc/vm_champs/asm doc/vm_champs/champs/Gagnant.s
diff diff.cor doc/vm_champs/champs/Gagnant.cor
echo
./asm/asm doc/vm_champs/champs/barriere.s
mv doc/vm_champs/champs/barriere.cor diff.cor
./doc/vm_champs/asm doc/vm_champs/champs/barriere.s
diff diff.cor doc/vm_champs/champs/barriere.cor
echo
./asm/asm doc/vm_champs/champs/jumper.s
mv doc/vm_champs/champs/jumper.cor diff.cor
./doc/vm_champs/asm doc/vm_champs/champs/jumper.s
diff diff.cor doc/vm_champs/champs/jumper.cor
echo
./asm/asm doc/vm_champs/champs/maxidef.s
mv doc/vm_champs/champs/maxidef.cor diff.cor
./doc/vm_champs/asm doc/vm_champs/champs/maxidef.s
diff diff.cor doc/vm_champs/champs/maxidef.cor
echo
./asm/asm doc/vm_champs/champs/slider2.s
mv doc/vm_champs/champs/slider2.cor diff.cor
./doc/vm_champs/asm doc/vm_champs/champs/slider2.s
diff diff.cor doc/vm_champs/champs/slider2.cor
echo
./asm/asm doc/vm_champs/champs/toto.s
mv doc/vm_champs/champs/toto.cor diff.cor
./doc/vm_champs/asm doc/vm_champs/champs/toto.s
diff diff.cor doc/vm_champs/champs/toto.cor
echo
./asm/asm doc/vm_champs/champs/Octobre_Rouge_V4.2.s
mv doc/vm_champs/champs/Octobre_Rouge_V4.2.cor diff.cor
./doc/vm_champs/asm doc/vm_champs/champs/Octobre_Rouge_V4.2.s
diff diff.cor doc/vm_champs/champs/Octobre_Rouge_V4.2.cor
echo
./asm/asm doc/vm_champs/champs/mortel.s
mv doc/vm_champs/champs/mortel.cor diff.cor
./doc/vm_champs/asm doc/vm_champs/champs/mortel.s
diff diff.cor doc/vm_champs/champs/mortel.cor
echo
./asm/asm doc/vm_champs/champs/Car.s
mv doc/vm_champs/champs/Car.cor diff.cor
./doc/vm_champs/asm doc/vm_champs/champs/Car.s
diff diff.cor doc/vm_champs/champs/Car.cor
echo
./asm/asm doc/vm_champs/champs/ex.s
mv doc/vm_champs/champs/ex.cor diff.cor
./doc/vm_champs/asm doc/vm_champs/champs/ex.s
diff diff.cor doc/vm_champs/champs/ex.cor
echo "\nTEST WARNING"
./asm/asm doc/vm_champs/champs/lde.s
