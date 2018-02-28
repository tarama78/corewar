.name		"champi"
.comment	""

			zjmp	%:life
			ld		%20, r8
			ld		%4, r10
			ld		%0, r9
			ld		%-3, r2
			ld		%0, r12
			ld		%8, r13
			ld		%12, r14
			st		r1, r4
			st		r1, r3
			st		r1, r6
			live	%0
			sti		r1, %:life, %1
			sti		r1, %:ff, %1
ff:			live	%0
			fork	%:fork1
			fork	%:run3
			ld		%0, r9
			ldi		%4, %:life, r4
			add		r9, r10, r9
			add		r15, r15, r15
			zjmp	%:life
fork1:		fork	%:run2
			ldi		%0, %:life, r4
			add		r9, r12, r9
			add		r15, r15, r15
			zjmp	%:life
run2:		ldi		%8, %:life, r4
			add		r9, r13, r9
			add		r15, r15, r15
			zjmp	%:life
run3:		ldi		%12, %:life, r4
			add		r9, r14, r9
			add		r15, r15, r15
			zjmp	%:ff
life:		live	%0
write:		sti		r4, r8, r9
			add		r9, r2, r9
