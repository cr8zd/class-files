TITLE Random Numbers Sort    (Prog5_Randoms.asm)

; Author: Jennifer Frase (frasej)
; Course / Project ID CS271-400  Program 5        Date: 5/24/15
; Description: This program will ask the user for a number between 10 and 200.
;              It will then generate that many random numbers between 100 and
;              999 and store then in an array. The numbers will be displayed
;              unsorted to the user before they are sorted in descending order.
;			   After being sorted, the median value as well as the sorted
;              array will be displayed to the user.

INCLUDE Irvine32.inc

MIN = 10
MAX = 200
LO = 100
HI = 999



.data
	requested		DWORD	?
	generated		DWORD	MAX DUP(?)

;prompts
	intro1			BYTE	"When you give me a number between 10 and 200, I will generate that many random", 0
	intro2			BYTE	"numbers from 100 to 999. I will then show you them unsorted and sorted, as well", 0 
	intro3			BYTE	"as display the median.", 0
	promptNums		BYTE	"How many random numbers should be generated? [10-200]", 0
	warnRange		BYTE	"Please only give a number between 10 and 200 inclusive.", 0
	myName			BYTE	"My name is Jennifer Frase and this is Random Numbers Sort.", 0
	
;results
	unsorted		BYTE	"The unsorted numbers are:", 0
	sorted			BYTE	"The sorted numbers are:", 0
	medText			BYTE	"The median is: ", 0




.code
main PROC

	call		Randomize
	
;introduction
	push	OFFSET myName
	push	OFFSET intro1
	push	OFFSET intro2
	push	OFFSET intro3
	call	introduction

;get user data
	push	OFFSET warnRange
	push	OFFSET promptNums
	push	OFFSET requested
	call	getData

;fill the array
	push	OFFSET generated
	push	requested
	call	fill

;display the unsorted list
	push	OFFSET unsorted
	push	OFFSET generated
	push	requested
	call	displayList

;sort the list
	push	OFFSET generated
	push	requested
	call	sort

;display the median
	push	OFFSET medText
	push	OFFSET generated
	push	requested
	call	displayMed

;display the list
	push	OFFSET sorted
	push	OFFSET generated
	push	requested
	call	displayList

	exit	; exit to operating system
main ENDP




;Procedure to introduce the user to the program
;receives: references to the program title string and two discription strings
;		   in ascending order on the stack 
;returns: nothing
;preconditions: none 
;registers changed: edx
introduction PROC
	push	ebp
	mov		ebp, esp
	mov		edx, [ebp+20]			;myName
	call		WriteString
	call		CrLf
	call		CrLf

	mov		edx, [ebp+16]			;intro1
	call		WriteString
	call		CrLf

	mov		edx, [ebp+12]			;intro2
	call		WriteString
	call		CrLf
	
	mov		edx, [ebp+8]			;intro3
	call		WriteString
	call		CrLf
	call		CrLf

	pop		ebp
	ret		12
introduction ENDP




;Procedure to get a number from the user between the constants MIN and MAX
;receives: references to a number, a prompt string, a warning string
;          in descending order on the stack
;returns: a value between MIN and MAX in the passed variable
;preconditions: none 
;registers changed: edx, eax, ebx
getData PROC
	push	ebp
	mov		ebp, esp
	
	AskNum:								;ask for a valid number
		mov		edx, [ebp+12]			;print prompt
		call		WriteString
		call		ReadInt
		call		CrLf
		call		CrLf

	cmp		eax, MAX					;check that the number is valid
	jg		BadNum
	cmp		eax, MIN
	jge		GoodNum

	BadNum:								;invalid # so get new number
		mov		edx, [ebp+16]			;print warning message
		call		WriteString
		call		CrLf
		jmp		AskNum

	GoodNum:
		mov		ebx, [ebp+8]			;save value in passed variable
		mov		[ebx], eax
	pop		ebp
	ret		12
getData ENDP




;Procedure to introduce the user to the program
;receives: a number as a value and an array reference in descending
;          order on the stack
;returns: the passed number of values between LO and HI stored
;         in the array
;preconditions: none 
;registers changed: eax, ecx, edi
fill PROC
	push	ebp
	mov		ebp, esp
	mov		edi, [ebp+12]		;array
	mov		ecx, [ebp+8]		;# of elements
		
	GetNum:						;loop through the array, filling with random number
		mov		eax, HI
		sub		eax, LO
		inc		eax
		call		RandomRange
		add		eax, LO
		mov		[edi], eax
		add		edi, 4
		loop	GetNum

	pop		ebp
	ret		8
fill ENDP




;Procedure to sort the given array from largest to smallest
;		   using selection sort
;receives: an array reference and the number of elements in that
;          array as a value, in ascending order on the stack
;returns: an array that is sorted in descending order
;preconditions: none 
;registers changed: ecx, ebx, eax, edx, esi
sort PROC
	LOCAL temp: DWORD
	mov		ecx, [ebp+8]				;# elements in array
	mov		esi, [ebp+12]				;array
	dec		ecx
	mov		ebx, 0						;index
	
	Order:								
		push	ecx						;set ecx counter for inner loop
		mov		ecx, [ebp+8]			;# of elements
		sub		ecx, ebx
		dec		ecx						
		mov		edx, ebx				;get starting index for inner loop
		inc		edx
		push	ebx						;save ebx, now used as maximum's index 
	
		Find:
			mov		eax, [esi+4*edx]	;store the number being checked in temp
			mov		temp, eax
			mov		eax, [esi+4*ebx]	;move the current maximum to eax
			cmp		temp, eax			;compare current maximum to current index's value
			jl		GreaterThan
			mov		ebx, edx			;if old max is smaller, then make max the current index
			GreaterThan:
				inc		edx				;increment edx to loop through all values
			loop	Find
	
		mov		ecx, ebx				;ecx is now the maximum's index
		pop		ebx						;ebx is the index being swapped
		mov		eax, [esi+4*ebx]		;swap values
		mov		temp, eax
		mov		eax, [esi+4*ecx]
		mov		[esi+4*ebx], eax
		mov		eax, temp
		mov		[esi+4*ecx], eax
		pop		ecx						;restore ecx and increment ebx to loop all index except last
		inc		ebx						
	loop	Order
	
	ret		8
sort ENDP




;Procedure find and display the median of the provided array
;receives: a number as a value and an array reference in descending
;          order on the stack
;returns: nothing
;preconditions: none 
;registers changed: edx, eax, ebx, esi
displayMed PROC
	push	ebp
	mov		ebp, esp
	mov		edx, [ebp+16]			;display median message
	call		WriteString

	mov		eax, [ebp+8]			;# of elements
	mov		esi, [ebp+12]			;array
	mov		edx, 0					;calculate if number of elements is even
	mov		ebx, 2
	div		ebx
	cmp		edx, 0
	jne		One
	
	mov		edx, [esi+4*eax]		;number of elements is odd so find average
	mov		eax, [esi-4+4*eax]
	add		eax, edx
	mov		edx, 0
	div		ebx
	jmp		Done

	One:
		mov		eax, [esi+4*eax]
		 
	Done:							;write the median
		call		WriteDec
		call		CrLf
		call		CrLF
	pop		ebp
	ret		8
displayMed ENDP




;Procedure to display a given number of elements in a given array with
;		   10 elements per line
;receives: a number as a value, an array reference, and a reference
;          to a string which is the title of the array in descending
;		   order on the stack
;returns: nothing
;preconditions: none 
;registers changed: edx, esi, ecx, eax
displayList PROC
	LOCAL   count:DWORD
	mov		count, 0
	mov		esi, [ebp+12]				;array
	mov		ecx, [ebp+8]				;# of elements
	mov		edx, [ebp+16]				;print title
	call		WriteString
	call		CrLf
	
	Display:
		mov		eax, [esi]
		call		WriteDec
		mov		al, ' '
		call		WriteChar
		call		WriteChar
		call		WriteChar
		add		esi, 4
		inc		count
		cmp		count, 10
		jne		SameLine
		cmp		ecx, 1
		je		SameLine
		call		CrLf
		mov		count, 0	
		SameLine:		
		loop Display

	call		CrLf
	call		CrLf
	ret		12
displayList ENDP

END main