.name "ok"
.comment "ok"

sti r1, %:live1, %1
ld %:end, r2 #pointer to the end
ld %12, r3 #size of the loop
ld %:loop, r4 #adresse of the loop
ld %2, r5 # add to ld
loop:
	live1:live %1
	add r4, r5, r4
	sti r4, %:end, %1
	add r2, r3, r2
	and r1, %0, r1
	zjmp %:loop

end:
