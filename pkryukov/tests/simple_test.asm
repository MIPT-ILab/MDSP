
label:
	brm %r0, (%r1)
	brm (%r0), %r1

	brr %r0, %r1

	ld $100, %r0
	ld $100, (%r0)

	add %r0, %r1, %r2
	add (%r0), (%r1), (%r2)

	hlt
