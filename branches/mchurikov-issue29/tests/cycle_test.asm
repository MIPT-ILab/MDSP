main:
    ld $100, %r0
    brm %r0, (%r0)
    ld $1, %r1
    ld $200, %r2
    
label1:
    add %r0, %r1, %r0
    sub %r0, %r2, %r3
    jgt label1
    
    sub %r0, %r1, %r0
label2:
    sub %r0, %r1, %r0
    sub %r0, %r2, %r3
    jgt label2
    
    ld $100, %r2
    sub %r0, %r2, %r0
    
    hlt
