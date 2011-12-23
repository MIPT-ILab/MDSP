#include "./simmy.h"

using namespace std;


void Simmy::initAllParams ()
{
	
    memset ( reg, NULL, NUMBER_OF_REG);
    opcode = 0; 	    
    op1 = 0;          
    op2 = 0;             	
    sign_op1 = 0; 
    sign_op2 = 0; 
    type_op2 = 0;
    sign_bit = 0;
    number_reg1 = 0;
    number_reg2 = 0;
}
Simmy::Simmy ( hostUInt8* bytes, hostUInt32 lenght)
{
    cur_instr = bytes;
}

hostSInt32 Simmy::readInstr ()
{  
    hostUInt8 control;    // write here first 8 byte after (cur_instr + 1) 
                          // in order to know sign_op12 type_op2 sign_bit
     
    hostUInt8* adr_instr = cur_instr;
    hostUInt8 sign_list_op2;
    hostUInt8 sign_most_op2;
    
    opcode = *cur_instr; cout << "opcode = " << (int)opcode << endl;
    adr_instr++;
    control = *adr_instr; 
    
    if ( control & 2)
    {
    	sign_bit = 1; cout << "sign_bit = " << (int)sign_bit << endl;
    } else
    {
    	sign_bit = 0; cout << "sign_bit = " << (int)sign_bit << endl;
    }
    
    if ( control & 4)
    {
    	type_op2  = 1; cout << "type_op2 = " << (int)sign_bit << endl;
    } else
    {
    	type_op2  = 0; cout << "type_op2 = " << (int)sign_bit << endl;
    }

   	sign_op2  = control & 8;          cout << "sign_op2 = " << (int)sign_op2 << endl;
 
    if ( ( control & 8) && ( type_op2 == 0))
    {
    	cout << "specification Simmy does not provide for such action\n" << "command does not execute\n";
    	return NOT_SUPPORT;
    }
    
    if ( !( control & 8) && ( type_op2 != 0) && ( sign_bit == 1))
    {
    	cout << "specification Simmy does not provide for such action\n" << "command does not execute\n";
    	return NOT_SUPPORT;
    }
      
    adr_instr++;
    
    number_reg1 = *adr_instr;
    op1         =      reg[ number_reg1]; cout << "op1 = " << op1 << endl;
    sign_op1    = sign_reg[ number_reg1]; cout << "sign_op1 = " << sign_op1 << endl;
   
    adr_instr++;
    
    if ( type_op2 == 0)
    {//cout << "number_reg2 = " << number_reg2 << "\n";
    	number_reg2 = *adr_instr; cout << "number_reg2 = " << (int)number_reg2 << "\n";
    	op2         = ( hostUInt16)reg[ number_reg2];
    	sign_op2    =         sign_reg[ number_reg2];
    }
    
    sign_list_op2 = *adr_instr;
    
    adr_instr++; 
    
    if ( type_op2 == 1)
    {
    	sign_most_op2  = *adr_instr;
    	op2 = sign_most_op2 * 256 + sign_list_op2;
    }
    cout << "op2 = " << op2 << "\n";
    return EXIT_SUCCESS;
}

hostSInt32 Simmy::execInstr ()
{
	hostSInt32 status = 0;
	
	if ( opcode == 0)
	{
		funcNop ();
	}
	if ( opcode == 1)
	{
		funcAnd ();
	}
	if ( opcode == 2)
	{
		funcOr ();
	}
	if ( opcode == 3)
	{
		funcXor ();
	}
	if ( opcode == 130)
	{
		funcAdd ();
	}
	if ( opcode == 131)
	{
		sign_op2 = !sign_op2;
		funcAdd ();               //funcSub ();
	}
	if ( opcode == 129)
	{
		funcMul ();
	}
	if ( opcode == 128)
	{
		status = funcDiv ();
	}
	if ( opcode == 132)
	{
		funcMov (); 
	}
	if ( opcode == 68)
	{
		funcNot ();
	}
	if ( opcode == 192)
	{
		funcDec ();
	}
	if ( opcode == 193)
	{
		funcInc ();
	}
	if ( opcode == 194)
	{
		funcSsgn ();
	}
	if ( opcode == 195)
	{
		funcIsgn ();
	}
	
	return status;
}

void Simmy::funcNop  ()
{
	//this function does not execute
}

void Simmy::funcAnd  ()
{
	     reg[ number_reg1] =      op1 &      op2;
	sign_reg[ number_reg1] = sign_op1 * sign_op2;	
}

void Simmy::funcOr   ()
{
		 reg[ number_reg1] =      op1 |      op2;
	sign_reg[ number_reg1] = sign_op1 | sign_op2;
}
	
void Simmy::funcXor  ()
{
		 reg[ number_reg1] =      op1 ^      op2;
	sign_reg[ number_reg1] = sign_op1 ^ sign_op2;
}

void Simmy::funcAdd  ()
{
	if ( ( sign_op1 && sign_op2) || ( !sign_op1 && !sign_op2))
	{
			 reg[ number_reg1] =      op1 +      op2;
		sign_reg[ number_reg1] = sign_op1 | sign_op2;
	} else
	{
		if ( op1 > op2)
		{
				reg[ number_reg1] = op1 - op2;
		} else
		{
			
			     reg[ number_reg1] = op2 - op1;
			sign_reg[ number_reg1] = sign_op2;
		}
	}
}
		
void Simmy::funcSub  ()  // this function never called
{

}
void Simmy::funcMul  ()
{
	reg[ number_reg1] = op1 * op2;
	
	if ( ( sign_op1 && sign_op2) || ( !sign_op1 && !sign_op2))
	{
		sign_reg[ number_reg1] = true;
	} else
	{
		sign_reg[ number_reg1] = false;
	}
}
		
int  Simmy::funcDiv  ()
{
	if ( op2 == 0)
	{
		cout << "devided by null\n" << "command DIV does not execute\n";
		return DEVIDED_BY_NULL;
	}
	
	reg[ number_reg1] = op1 / op2;
	
	if ( ( sign_op1 && sign_op2) || ( !sign_op1 && !sign_op2))
	{
		sign_reg[ number_reg1] = true;
	} else
	{
		sign_reg[ number_reg1] = false;
	}
}
	
void Simmy::funcMov  ()
{
		 reg[ number_reg1] =      op2;
	sign_reg[ number_reg1] = sign_op2;
}

void Simmy::funcNot  ()
{
	     reg[ number_reg1] =      ~op1;
	sign_reg[ number_reg1] = ~sign_op1;
}

void Simmy::funcDec  ()
{
	if ( op1 == 0)
	{
			 reg[ number_reg1] = 1;
		sign_reg[ number_reg1] = false;
	}
	
	     reg[ number_reg1]--;
	sign_reg[ number_reg1] = sign_op1;
}
		
void Simmy::funcInc  ()
{
	if ( op1 == 0)
	{
			 reg[ number_reg1] = 1;
		sign_reg[ number_reg1] = true;
	}
	
	     reg[ number_reg1]++;
	sign_reg[ number_reg1] = sign_op1;
}

void Simmy::funcSsgn ()
{
	sign_reg[ number_reg1] = sign_bit;
}
	
void Simmy::funcIsgn ()
{
	sign_reg[ number_reg1] = !sign_reg[ number_reg1];
}

int Simmy::execute ( hostUInt32 numInstr)
{
	initAllParams ();
	
	short i = 0;
	hostSInt32 status_exit_readInstr = 0;
	hostSInt32 status_exit_execInstr = 0;
    
    for ( i = 0; i < numInstr; i++)
    {cout <<"i = "<< i << "\n";
        if ( ( status_exit_readInstr = readInstr ()) != 0) 
        {
        	goto loop1;
        }
        
        if ( ( status_exit_execInstr = execInstr ()) != 0) 
        {
        	goto loop1;
        }
loop1:  cur_instr = cur_instr + 5;
    }
    
    if ( sign_reg[ 1] == true)
    {
    	return ( int)reg[ 0];
    }
    if ( sign_reg[ 1] == false)
    {
    	return -1 * ( int)reg[ 0];
    }
}      

int main ()
{
	 unsigned char a[100] = {

        /* MOV r1, 5 */
        132,
        12,   ///////##############
        1,  
        7, 
        0, 
        
        /* MOV r0, r1 */
        132,
        0,  
        0,  
        1, 
        0, 
        
        /* ADD r0, r1 */
        130,
        0,  
        0,  
        1, 
        0, 
        
       
        
        /* ADD r0, 20 */
        130,
        4,  
        0,  
        20, 
        0, 
    };

	Simmy b( a, 1);
    cout << b.execute( 5) << endl;
	return 0;
}
	
		
    
    
    	
    
    
    
