; Home assignment section BP
;	 An awesome program
;			By Y&R

.MODEL LARGE
.DATA
	Denom DD 0
	
.CODE
.386
_mod_sort PROC FAR
PUBLIC _mod_sort
	PUSH BP						;SAVING THE VALUE OF BP
	MOV BP,SP					;
	PUSH SI						;SAVING THE VALUE OF SI
	PUSH DI						;SAVING THE VALUE OF DI
	PUSH ES						;SAVING THE VALUE OF ES
	PUSH FS						;SAVING THE VALUE OF FS
	PUSH GS						;SAVING THE VALUE OF GS
	MOV SI, [BP+16]     		;SI recieves count_arr
	MOV ES,[BP+18]				;ES = COUNT_ARR SEGMENT
	MOV DI, [BP+20]				;DI recieves pos_arr
	MOV FS,[BP+22]				;FS = POS_ARR SEGMENT
	MOV BX,0					;Initialize BX for the loop
	MOV WORD PTR DI[BX],0		;pos_arr[0] = 0
	MOV EAX,DWORD PTR [BP+12]	;denom
	MOV Denom,EAX
	MOV ECX,Denom				;ecx = number of iterations
	DEC ECX
	
	; Loop for pos_arr values
	
	Loop1pos:					
		MOV WORD PTR FS:DI[BX+2],0	;initialize pos_arr[i]
		MOV AX,FS:DI[BX+2]
		ADD AX,ES:SI[BX]			;pos[i] = pos[i] + count[i-1]
		SHL AX,2				;positions X 4 (size of long int)
		ADD AX,FS:DI[BX]			;pos[i] = Pos[i] + pos[i-1]
		MOV WORD PTR FS:DI[BX+2],AX
		ADD BX,2				;inc index
		LOOP Loop1pos			;
	MOV SI,[BP+24]				;SI = mod_sorted
	MOV ES,[BP+26]				;ES = mod_sorted segment
	MOV CX,[BP+10]				;cx = N
	MOV AX,[BP+6]				;BP = ARR1
	MOV GS,[BP+8]				;GS = arr1 segment
	MOV BP,AX
	MOV BX,0
	
	;arrange arr1 values by remainder in arr2 in increasing order
	
	LoopSort:					
		MOV EAX,GS:[BP]			;EAX = arr1[BP]
		MOV EDX,0				;initialize EDX
		DIV Denom				;Getting REM
		MOV BX,DX				;BX = REM
		SHL BX,1				;BX X 2 (size of int)
		MOV EAX,0				
		MOV AX,BX				;Saving the value (index) of bx in arr for later calculation 
		MOV DX,FS:DI[BX]			;Getting the index of [pos_arr[rem]]
		MOV BX,DX				
		MOV EDX,GS:[BP]			;EDX = arr1[BP]
		MOV DWORD PTR ES:SI[BX],EDX;arr2[pos_arr[rem]]=arr1[BP]
		ADD BX,4				;BP++
		MOV DX,BX				
		MOV BX,AX				;BX get the origibal index (rem X 2)
		MOV WORD PTR FS:DI[BX],DX	;pos_arr[rem]++
		ADD BP,4				;BP++
		LOOP LoopSort
;---  Returning values  ---
	POP GS
	POP FS
	POP ES
	POP DI
	POP SI
	POP BP
	RET
	_mod_sort ENDP
	END