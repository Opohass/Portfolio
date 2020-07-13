.MODEL SMALL
.DATA
	FX0 DQ ?
	FDX0 DQ ?
	X0 DQ ?
	ANS DQ ?
	
.CODE
.386
.387
_compute_approx PROC NEAR
PUBLIC _compute_approx
	;--CODE--;
	PUSH BP
	MOV BP,SP
	;extern double compute_approx(double (*f)(double), double (*fd)(double),double x0, double x);
								;  [BP + 4]             [BP + 6]           [BP + 8]   [BP + 16]
	;--F(X0)--;
	MOV BX,[BP + 4]
	FLD QWORD PTR[BP + 8]
	FSTP QWORD PTR X0
	PUSH X0
	CALL BX
	ADD SP,8
	FSTP QWORD PTR FX0
	;--FD(X0)--;
	MOV BX,[BP + 6]
	PUSH X0
	CALL BX
	ADD SP,8 
	FSTP QWORD PTR FDX0
	;--CALCULATION--;
	FLD QWORD PTR [BP + 16]		;ST(0) = X
	FSUB X0						;ST(0) = X - X0
	FMUL FDX0					;ST(0) = ST(0)*FD(X0)
	FADD FX0					;ST(0) = ST(0) + F(X0) //ST(0)=F(X0)+(X-X0)*FD(X0)
	POP BP
	RET
	_compute_approx ENDP
	END