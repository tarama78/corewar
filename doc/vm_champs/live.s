.name "zork"
.comment "just a basic living prog"

sti r1, %:live, %1
ld %42, r2
ld %12, r3
ld %:nothing, r4
and r1, %0, r1
fork %:init
live:live %1
lfork %:init2
live %1
loop:
	sti r2, r4, %1
	add r4, r3 ,r4
	live:live %1
	and r1, %0, r1
	zjmp %:loop
live:live %1

init:
	live %1
	fork %:init3
	ld %16, r3
	and r1, %0, r1
	zjmp %:loop

init2:
	live %1
	fork %:init3
	ld %16, r3
	and r1, %0, r1
	zjmp %:loop

init3:
	live %1
	lfork %:init2
	ld %16, r3
	and r1, %0, r1
	zjmp %:loop

nothing:
