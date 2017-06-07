// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Fill.asm

// Runs an infinite loop that listens to the keyboard input. 
// When a key is pressed (any key), the program blackens the screen,
// i.e. writes "black" in every pixel. When no key is pressed, the
// program clears the screen, i.e. writes "white" in every pixel.

// Put your code here.
(LOOP)
@SCREEN
D=A
@X
M=D	

(PRESSKEY)

@KBD
D=M
@BLACK
D;JGT	
@WHITE
D;JEQ	

@PRESSKEY
0;JMP

(BLACK)
@1
M=-1	
@CHANGE
0;JMP

(WHITE)
@1
M=0	
@CHANGE
0;JMP

(CHANGE)
@1	
D=M	

@X
A=M	
M=D	

@X
D=M+1

@KBD
D=A-D	

@X
M=M+1	
A=M

@CHANGE
D;JGT	

@LOOP
0;JMP