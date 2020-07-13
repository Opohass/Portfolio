; software to check if a number is almost a palindrome
.MODEL SMALL
.STACK 100h
.DATA
	ARR DB 10 DUP (?)
	InpStr DB 'Please enter long number (from 0 to 2147483647):','$'
	WrongInp DB 13,10,13,10,'WORNG INPUT','$'
	WrongOut DB 13,10,13,10,'Not a Palindrome!!!!!','$'
	RightOut db 13,10,13,10,'Almost a Palindrome','$'
	Count DW (?)
	Two DB 2
	TIME DW (?)
	Num DD 0
	Ten DD 10
	C1 DW 0
	
.CODE
.386
 
Check_Poli PROC NEAR  		;procedure to check if the input is almost a Palindrome
;//
Continu_Increment:			
		CMP BX,SI
		JE INCREMENT
		CMP BP,SI
		JE INCREMENT
Continu_Decrement:
		CMP BP,DI
		JE DECREMENT
		CMP BX,DI
		JE DECREMENT
		MOV DL,ARR[DI]
		CMP ARR[SI],DL
		JNE ENDLOOP
		INC C1
		CMP AX,C1
		JE POLI
		RET 
		Check_Poli ENDP
;//

	
Check_Input PROC NEAR  				;procedure to get the input from the user 
;//
	MOV AH,1
	INT 21h
	MOV AH,0
	CMP AL,13		;if the user input was ENTER we continue the program 
	JE CONT
	CMP AL,'9'		;checks if the char we got is not a number between 0-9	
	JA Error_Msg
	CMP AL,'0'
	JB Error_Msg
	MOV ARR[SI],AL	;Puting the input in ARR[SI]
	INC SI
	INC Count		;Count how many digits the user insert for later calculation 
	JMP loopRec
	RET 
	Check_Input ENDP
;//
	
Main:
	MOV AX,@DATA
	MOV DS,AX
	MOV DX,OFFSET InpStr
	MOV AH,9
	INT 21h
	MOV SI,0
loopRec:
	CMP SI,10
	JAE Check_Size
	CALL Check_Input
Check_Size: 				;Check to evaluate number if larger than max input
	MOV SI,0
	CMP Count,10	; compare amount of digits
	JB CONT			; jump to CONT if below 10
	CMP ARR[0],'2'
	JA Error_Msg	; if digits = 10 and first digit larger than 2 display error
	JB CONT			; if digits = 10 and first digit lower than 2 jump to CONT
	MOV CX,10		; amount of iterations for Loop_Check
Loop_Check:	
;//							; building the number to compare to max input
	MOV EAX,0
	MOV EAX,Num
	MUL Ten
	MOV EDX,0
	MOV DL,ARR[SI]
	SUB DL,'0'
	ADD EAX,EDX 
	INC SI
	MOV NUM,EAX
	LOOP Loop_Check
	CMP NUM,2147483647	;If the input is larger ot equal to 2147485648 
	JA Error_Msg
;//
CONT:   					; PREPARE FOR THE LOOP
;//
	CMP Count,3				;If the user input was only three digits or less the number is already a Palindrome
	JBE POLI			
;//
	MOV AX,Count			;Number of iterations of the two loops we are using 
	DIV Two
	MOV AH,0
	DEC AX
	MOV CX,Count
	DEC CX
	MOV BX,0
	MOV BX,OFFSET ARR
	MOV BP,OFFSET ARR
	ADD BP,CX
	MOV SI,OFFSET ARR
	INC SI
	MOV DI,BP
	DEC DI
	MOV DX,0
	
LOOP1:
	MOV TIME,CX 
	LOOP2: ; 
		CALL Check_Poli  	;check for palindrome with procedure
		INC SI
		DEC DI
		CALL Check_Poli		;check for palindrome with procedure
		INC SI
		DEC DI
		CALL Check_Poli		;check for palindrome with procedure
		INC SI
		DEC DI
		CALL Check_Poli		;check for palindrome with procedure
		ENDLOOP:
		DEC BP				; move BP one value lower
		MOV SI,OFFSET ARR	;reset SI
		MOV DI,OFFSET ARR	;reset DI
		ADD DI,Count
		DEC DI
		MOV C1,0
		LOOP LOOP2
	MOV CX,TIME				;return outer loop count to CX
	INC BX					;move BX one value up
	MOV BP,COUNT			;reset BP to last arr value
	DEC BP					
	LOOP LOOP1
	
NOTP:
	MOV DX, OFFSET WrongOut		;prints a message in case the input is not a Palindrome
	JMP FINISH
	
INCREMENT:						;In case SI and BP/BX has the same index
	INC SI
	JMP Continu_Increment	;Continue the procedure
	
DECREMENT:						;In case DI and BP/BX has the same index 

	DEC DI
	JMP Continu_Decrement	;Continue the procedure
	
Error_Msg:						;prints a message in case the input is worng
 
	MOV DX, OFFSET WrongInp
	JMP FINISH

POLI:							;prints a message in case the input is a Palindrome
	MOV DX, OFFSET RightOut
	JMP FINISH

FINISH:							;Finish and exit the program 
	MOV AH,9
	INT 21h
	MOV AH,4CH  
	INT 21h
	END Main
	
	
	
