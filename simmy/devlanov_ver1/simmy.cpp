#include "./simmy.h"

using namespace std;


Simmy::Simmy ( hostUInt8* bytes, hostUInt32 lenght)
{
    cur_instr = bytes;
}

int Simmy::readInstr()
{  
    hostUInt8 control;    // write here first 8 byte after (cur_instr + 1) 
                          // in order to know sign_op12 type_op2 sign_bit
     
    opcode = *cur_instr;
    cur_instr++;
    control = *cur_instr;
    
    if ( control & 2)
    {
    	sign_bit = 1;
    } else
    {
    	sign_bit = 0;
    }
    
    if ( control & 4)
    {
    	type_op2  = 1;
    }
    
//   if ( type_op2 == 1)
//    {
    	sign_op2  = control & 8;          //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//    } 
/////////////////////////////////////////////////////////////   
    if ( ( control & 8) && ( type_op2 == 0))
    {
    	cout << "specification Simmy does not provide for such action\n", "command does not execute\n";
    	return -1;
    }
    
    if ( !( control & 8) && ( type_op2 != 0) && ( sign_bit == 1))
    {
    	cout << "specification Simmy does not provide for such action\n", "command does not execute\n";
    	return -1;
    }
//////////////////////////////////////////////////////////////      
    cur_instr++;
    
    number_reg1 = *cur_instr;
    op1         =      reg[ number_reg1];
    sign_op1    = sign_reg[ number_reg1];
   
    cur_instr++;
    
    if ( type_op2 == 0)
    {
    	number_reg2 = *cur_instr;
    	op2         = (hostUInt16)reg[ number_reg2];
    	sign_op2    =        sign_reg[ number_reg2];
    }
    
    cur_instr++; 
    
    if ( type_op2 == 1)
    {
    	op2       = (hostUInt16) *cur_instr;
    }
}

hostSInt32 Simmy::execInstr ()
{
	hostSInt32 status = 0;
	
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
		return 2;
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
	if ( sign_bit != sign_op1)
	{
		if ( sign_op1 == 0)
		{
				 reg[ number_reg1]--;
			sign_reg[ number_reg1] = true;
		} else
		{
				 reg[ number_reg1]++;
			sign_reg[ number_reg1] = false;
		}
	}
}

void Simmy::funcIsgn ()
{
	if ( sign_op1 == 0)
		{
				 reg[ number_reg1]--;
			sign_reg[ number_reg1] = true;
		} else
		{
				 reg[ number_reg1]++;
			sign_reg[ number_reg1] = false;
		}
}

hostSInt32 Simmy::execute ( hostUInt32 numInstr)
{
	short i = 0;
	hostSInt32 status_exit_readInstr = 0;
	hostSInt32 status_exit_execInstr = 0;
    
    for ( i = 0; i < numInstr; i++)
    {cout << i << "\n";
        if ((status_exit_readInstr = readInstr    ()) != 0) goto loop1;
        if ((status_exit_execInstr = execInstr ()) != 0)    goto loop1;
loop1:  cur_instr = cur_instr + 5;
    }
    return reg[ 0] * sign_reg[ 0];
}      

int main ()
{
	//Simmy b( a, 1);
    //cout << b.execute( 1);
	return 0;
}
	
		
    
    
    	
    
    
    
