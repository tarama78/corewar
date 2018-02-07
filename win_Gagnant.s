.name		"champ"
.comment	"worst ?"

			ld		%200, r8
			ld		%200, r10
			ld		%0, r9
			ld		%4, r2
			ld		%42, r4
			ld		%4, r2
			live	%0
			zjmp	%:life
			sti		r1, %:life, %1
			sti		r1, %:ford, %1
			sti		r1, %:ff, %1
ff:			live	%0
			fork	%:ford
life:		live	%0
write:		sti		r4, r8, r9
		#	sti		r4, r10, r9
			ldi		r9, %:ff, r4
			add		r9, r2, r9
			ld		%0, r11
			zjmp	%:life
ford:		live	%0
			fork	%79
			ld		%0, r9

