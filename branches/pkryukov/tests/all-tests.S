
label0:
	brm %r0, (%r1)
	brm (%r0), %r1

	brr %r0, %r1

	ld $100, %r0
	ld $100, (%r0)



	nop
label:
	add %r0, %r1, %r2
	add $100, %r0

	sub %r0, %r1, %r2
	sub $100, %r0



	jmp %r0
	jmp label

	jgt %r0
	jgt label


	int $5
	hlt

