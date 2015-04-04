/**
* instruction.h - Header of Instructions,
* which defines execute routines
* Copyright 2009 MDSP team
*/
#ifndef INSTRUCTION_H
#define INSTRUCTION_H
#define number_of_move_operations 7
#define number_of_logic_operations 7
#define number_of_shift_operations 7
#define number_of_arithmetic_operations 7
extern void (*moveOperation[number_of_move_operations])(void);
extern void (*logicOperation[number_of_logic_operations])(void);
extern void (*shiftOperation[number_of_shift_operations])(void);
extern void (*arithmeticOperation[number_of_arithmetic_operations])(void);
#endif /* INSTRUCTION_H */ 
