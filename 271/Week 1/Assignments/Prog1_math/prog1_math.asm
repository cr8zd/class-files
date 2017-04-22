TITLE My Math     (prog1_math.asm)

; Author: Jennifer Frase
; Course / Project ID :  CS371  Program 1       Date: 4/12/15
; Description: Displays my name and the basic math of two user input numbers

INCLUDE Irvine32.inc

.data
;user variables and result variables
	firstNum		DWORD	?
	secondNum		DWORD	?
	sum				DWORD	?
	product			DWORD	?
	diff			DWORD	?
	quotent			DWORD	?
	remain			DWORD	?
	remainDub		DWORD	?
	quotentDub		DWORD	?

;constants used to calculate floating point division
	factoring		DWORD	10
	counter			DWORD	3

;prompts
	prompt			BYTE	"Please give two numbers where the first is larger than the second.", 0
	prompt2			BYTE	"Then I will give you the sum, the difference, the product, the quotent,", 0
	prompt3			BYTE	"and the remainder.", 0
	promptNum1		BYTE	"1st Number : ", 0
	promptNum2		BYTE	"2nd Number : ", 0

myName			BYTE	"My name is Jennifer Frase and this is My Math.", 0
goodbye			BYTE	"Thank you for using My Math.", 0

;math symbols
	addResult		BYTE	" + ", 0
	equalResult		BYTE	" = ", 0
	subResult		BYTE	" - ", 0
	divResult		BYTE	" / ", 0
	multResult		BYTE	" x ", 0
	modResult		BYTE	" remainder of ", 0
	decResult		BYTE	".", 0

;repeat variables
	warn			BYTE	"The first number was not bigger than the second, please give new numbers.", 0
	askAgain		BYTE	"Do you want to do another set of calculations? Type 0 for no and 1 for yes. ", 0
	againVal		DWORD	?
	againWarn		BYTE	"Please only type 1 or 0.", 0

.code
main PROC
;intro
	;give name and program title
		mov		edx, OFFSET myName
		call		WriteString
		call		CrLf
		call		CrLf

ProgStart:
	;ask for two numbers
		mov		edx, OFFSET prompt
		call		WriteString
		call		CrLf
		mov		edx, OFFSET prompt2
		call		WriteString
		call		CrLf
		mov		edx, OFFSET prompt3
		call		WriteString
		call		CrLf
		call		CrLf
		jmp			GetNumbers

;get first and second numbers
	NotBigger:
		mov		edx, OFFSET warn
		call		WriteString
		call		CrLf

	GetNumbers:
	;first num
		mov		edx, OFFSET promptNum1
		call		WriteString
		call		ReadInt
		mov		firstNum, eax
		call		CrLf

	;second num
		mov		edx, OFFSET promptNum2
		call		WriteString
		call		ReadInt
		mov		secondNum, eax
		call		CrLf
		cmp		eax, firstNum
		jg		NotBigger

;calculate sum, difference, product, quotent, remainder
	;get sum
		mov		eax, firstNum
		add		eax, secondNum
		mov		sum, eax

	;get diff	
		mov		eax, firstNum
		sub		eax, secondNum
		mov		diff, eax

	;get product
		mov		eax, firstNum
		mul		secondNum
		mov		product, eax

	;get quotent
		mov		eax, firstNum
		div		secondNum
		mov		quotent, eax

	;get remain
		mov		remain, edx

	;get quotentDub
		mov		remainDub, edx
		mov		ecx, 3
		mov		eax, 0
		mov		quotentDub, eax

		CalcRemain:
			mov		counter, ecx
			mov		eax, remainDub
			mul		factoring
			div		secondNum
			mov		remainDub, edx
			CalcDub:
				mul		factoring
				loop	CalcDub
			mov		ecx, counter
			div		factoring
			add		quotentDub, eax
			loop	CalcRemain
		
;display results
	;display sum
		mov		eax, firstNum
		call		WriteDec
		mov		edx, OFFSET addResult
		call		WriteString
		mov		eax, secondNum
		call		WriteDec
		mov		edx, OFFSET equalResult
		call		WriteString
		mov		eax, sum
		call		WriteDec
		call		CrLf

	;display diff
		mov		eax, firstNum
		call		WriteDec
		mov		edx, OFFSET subResult
		call		WriteString
		mov		eax, secondNum
		call		WriteDec
		mov		edx, OFFSET equalResult
		call		WriteString
		mov		eax, diff
		call		WriteDec
		call		CrLf

	;display product
		mov		eax, firstNum
		call		WriteDec
		mov		edx, OFFSET multResult
		call		WriteString
		mov		eax, secondNum
		call		WriteDec
		mov		edx, OFFSET equalResult
		call		WriteString
		mov		eax, product
		call		WriteDec
		call		CrLf

	;display quotent and remain
		mov		eax, firstNum
		call		WriteDec
		mov		edx, OFFSET divResult
		call		WriteString
		mov		eax, secondNum
		call		WriteDec
		mov		edx, OFFSET equalResult
		call		WriteString
		mov		eax, quotent
		call		WriteDec
		mov		edx, OFFSET modResult
		call		WriteString
		mov		eax, remain
		call		WriteDec

	;display floating point quotent
		mov		edx, OFFSET equalResult
		call		WriteString
		mov		eax, quotent
		call		WriteDec
		mov		edx, OFFSET	decResult
		call		WriteString
		mov		eax, quotentDub
		call		WriteDec
		call		CrLf
		jmp			AgainBlock

;ask if user wants to repeat
	WarnBlock:
		mov		edx, OFFSET againWarn
		call		WriteString
		call		CrLf
	
	AgainBlock:
		mov		edx, OFFSET askAgain
		call		WriteString
		call		ReadInt
		call		Crlf
		mov		againVal, eax
		cmp		againVal, 1
		je		ProgStart
		cmp		againVal, 0
		jne		WarnBlock

;say goodbye
		mov		edx, OFFSET goodbye
		call		WriteString
		call		CrLf
		call		CrLf
	exit	; exit to operating system
main ENDP

END main