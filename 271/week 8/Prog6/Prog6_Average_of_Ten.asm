TITLE Average of Ten    (Prog7_Average_of_Ten.asm)

; Author: Jennifer Frase (frasej)
; Course / Project ID CS271-400  Program 6        Date: 6/7/15
; Description: This program will ask the user for 10 numbers (whose sum
;              should fit in a 32 bit register), and then calculate the
;              sum and average of those numbers. All reading and writing
;              will be done with macros.

INCLUDE Irvine32.inc

;Macro to get a string from the user
;receives: the address of a string which will store the user's input, and then
;		   the prompt that the user will read to decide what to input
;returns: a string in the buffer varaible
;preconditions: none
;registers changed: none but edx and ecx are used and then restored
getString MACRO buffer, prompt
	push			edx
	push			ecx
	displayString	prompt
	mov				edx, buffer
	mov				ecx, 20
	call				ReadString
	pop				ecx
	pop				edx
ENDM


;Macro to write a string for the user to see
;receives: the address of a string which will be displayed
;returns: nothing
;preconditions: none
;registers changed: none but edx is used and then restored
displayString MACRO buffer
	push	edx
	mov		edx, buffer
	call		WriteString
	pop		edx
ENDM



.data
	stringNum		BYTE	11  DUP(?)
	numbers			DWORD	10	DUP(0)

;prompts
	intro1			BYTE	"Please give 10 unsigned integers in decimal format, one at each prompt.", 0
	intro2			BYTE	"Once 10 valid numbers are input, I will calculate the sum and the", 0 
	intro3			BYTE	"average of all the valid numbers you input.", 0
	promptNums		BYTE	"Please give an unsigned decimal number: ", 0
	warning			BYTE	"You did not give an unsigned integer.", 0
	tooBig			BYTE	"The integer you gave was too big, please give smaller numbers.", 0
	myName			BYTE	"My name is Jennifer Frase and this is Average of Ten.", 0
	
;results
	average			DWORD	0
	sum				DWORD	0
	sumString		BYTE	"The sum is: ", 0
	aveString		BYTE	"The average is: ", 0
	numDisplay		BYTE	"Your numbers are: ", 0
	commas			BYTE	", ", 0




.code
main PROC

;introduction
	push	OFFSET myName
	push	OFFSET intro1
	push	OFFSET intro2
	push	OFFSET intro3
	call	introduction


;get user data
	mov		ecx, 10
	
	;get a number 10 times
	getData:	
		mov		eax, 10
		sub		eax, ecx
		mov		ebx, 4
		mul		ebx

		push	eax					;index to store number
		push	OFFSET warning
		push	OFFSET tooBig
		push	OFFSET promptNums
		push	OFFSET stringNum
		push	OFFSET numbers
		call	readVal
	loop	getData

;calculate
	push	OFFSET	numbers
	push	OFFSET	sum
	push	OFFSET	average
	call	calculate
	

;write results
	call			CrLf

	;display all 10 numbers
		displayString	OFFSET numDisplay
		call			CrLf

		mov		ecx, 10
		showNums:								;loop through the array and display each number
			mov				eax, 10
			sub				eax, ecx

			push			eax					;index from which to get number
			push			OFFSET stringNum
			push			OFFSET numbers
			call			writeVal
			cmp				ecx, 1
			je				NoComma
			displayString	OFFSET commas
			NoComma:
		loop			showNums
		call			CrLf
		call			CrLf
	
	;display the sum
		displayString	OFFSET sumString
		push			0
		push			OFFSET	stringNum
		push			OFFSET	sum
		call			writeVal
		call			CrLf
		call			CrLf

	;display the average
		displayString	OFFSET	aveString
		push			0
		push			OFFSET	stringNum
		push			OFFSET	average
		call			writeVal
		call			CrLf
		call			CrLf

	exit	; exit to operating system
main ENDP




;Procedure to introduce the user to the program
;receives: references to the program title string and two discription strings
;		   in ascending order on the stack 
;returns: nothing
;preconditions: 
;registers changed:
introduction PROC
	push			ebp
	mov				ebp, esp
	displayString	[ebp+20]			;myName
	call				CrLf
	call				CrLf

	displayString	[ebp+16]			;intro1
	call				CrLf

	displayString	[ebp+12]			;intro2
	call				CrLf
	
	displayString	[ebp+8]			;intro3
	call				CrLf
	call				CrLf

	pop		ebp
	ret		12
introduction ENDP




;Procedure to get an integer from the user as a string. It will then validate
;         that the integer is unsigned and fits in a 32bit register as it
;         converts the string into a decimal
;receives: push the index number in bytes, then push a warning prompt
;               for an invalid number, then push a warning prompt for a
;               number that is too big, then push a prompt for a number,
;               then push the address for the string used to get the number,
;               then push the address of the array used to store the integer
;returns: an integer in the given index in an array of numbers 
;preconditions: none
;registers changed: no registers are changed, but ebp, esi, ecx, eax, ebx,
;                   edi, and edx are used and then restored
readVal PROC
	push		ebp
	mov			ebp, esp 
	pushad
	
	;get number as a string
	GetNumber:
		getString	[ebp+12], [ebp+16]
		cmp			eax, 10
		jge			TooLarge
	
	
	;convert string to decimal number while validating
	mov			ecx, eax	
	mov			esi, [ebp+12]
	mov			edi, [ebp+28]

	loopChar:	
		mov			ebx, [ebp+8]
		mov			eax, [ebx+edi]		;move current value into eax
		mov			ebx, 10				
		mul			ebx					
		mov			ebx, [ebp+8]
		mov			[ebx+edi], eax		;move the increase value back to the array
		mov			eax, 0				;zero extend the register
		lodsb							;get the next digit
		sub			eax, 48				;convert to decimal

	;check if the number is valid
		cmp			eax, 0
		jl			Invalid
		cmp			eax, 9
		jg			Invalid
	
	;if number is valid add it to the number in the array
		mov			ebx, [ebp+8]
		add			[ebx+edi], eax
		loop		loopChar
	jmp			AllGood

	TooLarge:
		call				CrLf
		displayString	[ebp+20]
		call				CrLf
		jmp				GetNumber

	Invalid:
		call				CrLf
		displayString	[ebp+24]
		call				CrLf
		jmp				GetNumber
	
	AllGood:
	
	popad
	pop			ebp
	ret			24
readVal ENDP



;Procedure to calculate the sum and average of a passed in array of
;          integers
;receives: need to push the array of numbers, then the address of the
;				sum, then the address of the average
;returns: the average of the passed in numbers in [ebp+8] and the sum of the
;         numbers in [ebp+12]
;preconditions: none
;registers changed: no registers are changed, but ebp, esi, ecx, eax, ebx,
;                   and edx are used and then restored
calculate PROC
	push		ebp
	mov			ebp, esp
	pushad

	mov			esi, [ebp+16]
	mov			eax, 0
	mov			ecx, 10
	
	;add all the numbers to eax
		AddNums:
			add			eax, [esi]
			add			esi, 4
		loop		AddNums
	
		mov			ebx, [ebp+12]
		mov			[ebx], eax			;move the sum into the sum variable
	
	;calculate the average
		mov			ebx, 10
		mov			edx, 0
		div			ebx
		mov			ebx, [ebp+8]
		mov			[ebx], eax
	
	popad
	pop			ebp
	ret			12
calculate ENDP




;Procedure convert a decimal into a string and then print it using the
;		displayString macro
;receives: push an index value for the number (0 if not in array), 
;               then push the address of the string, then push the
;               address of the number/number array  
;returns: nothing
;preconditions: none
;registers changed: no registers are changed, but ebp, edi, esi, ecx, eax,
;                   ebx, and edx are used and then restored
writeVal PROC
	push		ebp
	mov			ebp, esp 
	pushad
	
	;convert string to decimal number while validating
	mov			edi, [ebp+12]
	mov			esi, [ebp+12]
	mov			ecx, [ebp+16]
	mov			eax, 4
	mul			ecx
	mov			ecx, eax				;index (in bytes) of current number working with
	
	mov			ebx, 100000000
	push		ebx
	mov			ebx, [ebp+8]
	mov			eax, [ebx+ecx]		;mov number into eax
	pop			ebx
	LoopDigits:	
		mov			edx, 0
		div			ebx
		cmp			edi, esi			;check if first number is added
		jne			AddNum
		cmp			eax, 0				;haven't added first number so see if we found it yet
		je			SmallNum
		
		AddNum:							;found a number
			add			al, 48
			stosb							;move the digit into the string

		SmallNum:
			push		edx
			mov			eax, ebx
			mov			ebx, 10
			mov			edx, 0
			div			ebx
			mov			ebx, eax
			pop			eax
			cmp			ebx, 0
			jg			LoopDigits
		
		cmp			edi, esi
		jne			AddNull
		mov		al, 48
		stosb
		
		AddNull:
			mov			al, 0
			stosb
	
	displayString	[ebp+12]	
	popad
	pop			ebp
	ret			12
writeVal ENDP

END main