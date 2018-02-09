.name		"champ"
.comment	"worst ?"

			ld		%255, r8
			ld		%250, r10
			ld		%0, r9
			ld		%8, r2
			ld		%4, r12
			ld		%8, r2
			live	%0
			zjmp	%:life
			sti		r1, %:life, %1
			sti		r1, %:ford, %1
			sti		r1, %:ff, %1
ff:			live	%0
			fork	%:ford
life:		live	%0
write:		ldi		r9, %:ff, r4
			ldi		r12, %:ff, r5
			sti		r4, r8, r9
			sti		r5, r10, r12
			add		r9, r2, r9
			add		r12, r2, r12
			ld		%0, r11
			zjmp	%:life
ford:		live	%0
			fork	%200
			ld		%0, r9
