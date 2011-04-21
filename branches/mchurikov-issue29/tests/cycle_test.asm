main:   
    ld $0, %r0
    brm %r0, (%r0)
    ld $1, %r1
    ld $10, %r2 
       
label1:  add %r0, %r1, %r0
    sub %r0, %r2, %r3
    jgt label_out1
    jmp label1
    
label_out1:
    ld $0, %r2
    sub %r0, %r1, %r0
label2:    
    sub %r0, %r1, %r0
    sub %r2, %r0, %r3
    jgt label_out2
    jmp label2
    
label_out2:
    ld $100, %r2
    sub %r0, %r2, %r0
    hlt
