TITLE Composite Numbers     (Prog4_CompNums.asm)

; Author: Jennifer Frase (frasej)
; Course / Project ID CS271-400  Program 4        Date: 5/10/15
; Description: This program will ask for an integer from the user. If the integer
;			   is greater than 400 or less than 1 it will ask for a new number until
;			   it gets a valid integer. It will then display that many composite
;			   numbers. It gets a composite number by dividing it by values less than
;              or equal to half (interger division) the number and greater than 1. It
;              then sees if the result is a whole number. If it is then the number is
;			   composite, and so it prints the number.

INCLUDE Irvine32.inc

UPPER_LIMIT = 400

.data
;prompts
	prompt			BYTE	"At the prompt please tell me how many composite numbers (not prime) you", 0
	prompt2			BYTE	"would like to see. You can see up to 400 numbers.", 0
	promptNums		BYTE	"How many composites should be displayed? ", 0
	warnRange		BYTE	"Please only give a number between 1 and 400 inclusive.", 0
	myName			BYTE	"My name is Jennifer Frase and this is Composite Numbers.", 0
	goodbye			BYTE	"Goodbye, thank you for using Composite Numbers.", 0
	
;results
	count			DWORD	0							;count of numbers already displayed
	compNum			DWORD	4							;current number to check if composite
	space			BYTE	"   ", 0					;basic space between numbers
	singleSpace		BYTE	" ", 0						;used to indent over small numbers

.code
main PROC

	call	intro
	call	getUserData
	call	showComposites
	call	farewell

	exit	; exit to operating system
main ENDP


;Procedure to introduce the user to the program
;receives: myName, prompt, and prompt2 are global variables 
;returns: nothing
;preconditions: none 
;registers changed: edx
intro PROC
	mov		edx, OFFSET myName
	call		WriteString
	call		CrLf
	call		CrLf

	mov		edx, OFFSET prompt
	call		WriteString
	call		CrLf

	mov		edx, OFFSET prompt2
	call		WriteString
	call		CrLf
	call		CrLf
	ret
intro ENDP



;Gets the number of times to  display a composite number
;receives: promptNums is a global variable 
;returns: a valid number in ecx
;preconditions: none
;registers changed: edx, eax, ecx
getUserData PROC
	mov		edx, OFFSET	promptNums
	call		WriteString
	call		ReadInt
	call		CrLf
	call	validate
	mov		ecx, eax
	ret
getUserData ENDP



;Validates that the number in eax is between 1 and 400 inclusive
;receives: warnRange is a global variable 
;returns: an integer between 1 and 400 inclusive
;preconditions: none 
;registers changed: edx
validate PROC
	cmp		eax, UPPER_LIMIT
	jg		BadNum
	cmp		eax, 1
	jge		GoodNum

	BadNum:								;invalid # so get new number
		mov		edx, OFFSET warnRange
			call		WriteString
			call		CrLf
		call	getUserData

	GoodNum:
	ret
validate ENDP



;Procedure to print composite numbers
;receives: space, compNum, count are global variables 
;returns: nothing
;preconditions: ecx must be greater than 0
;registers changed: edx, eax, ecx, ebx
showComposites PROC
		mov		ebx, 10				;used to determine if a new line is needed
	PrintNums:						;prints the composite numbers
		cmp		count, 0
		je		SameLine			;first number so no new line
		mov		eax, count
		mov		edx, 0
		div		ebx
		cmp		edx, 0
		jne		SameLine			;prints a new line every 10 numbers
		call		CrLf

		SameLine:					;gets 1 composite number and prints it
			push	ecx
			call	isComposite
			pop		ecx
			cmp		compNum, 100
			jge		NoSpace
			cmp		compNum, 10
			jge		OneSpace
			mov		al, ' '
			call		WriteChar		;prints a space for # < 10

			OneSpace:					;prints a space for # < 100
				mov		al, ' '
				call		WriteChar

			NoSpace:					;prints the number with space afterward
				mov		eax, compNum
				call		WriteDec
				mov		edx, OFFSET space
				call		WriteString
				inc		count
				inc		compNum
	loop	PrintNums					;gets next composite
	ret
showComposites ENDP



;Procedure to find the next composite number
;receives: compNum is a global variable 
;returns: the next composite number in eax and the next number to check in
;         compNum
;preconditions: compNum must be positive
;registers changed: eax, ecx, edx
isComposite PROC
	FindComp:
		mov		eax, compNum
		mov		ecx, 2
		mov		edx, 0
		div		ecx
		mov		ecx, eax

		Check:					;checks the current number for factors
			mov		eax, compNum
			mov		edx, 0
			div		ecx
			cmp		edx, 0		;found a factor so is composite
			je		Comp
			dec		ecx
			cmp		ecx, 1
			jg		Check		;if ecx got to 1 then there were no factors
			inc		compNum		;so go to next number
			jmp		FindComp	;start procedure over with new number
	Comp:
	ret
isComposite ENDP



;Procedure to say goodbye
;receives: goodbye is a global variable 
;returns: nothing
;preconditions: none 
;registers changed: edx
farewell PROC
	call		CrLf
	call		CrLf
	mov		edx, OFFSET goodbye
	call		WriteString
	call		CrLf
	call		CrLf
	ret
farewell ENDP

END main