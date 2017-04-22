TITLE Negative Average     (Prog3_ave.asm)

; Author: Jennifer Frase frasej@onid.oregonstate.edu
; Course / Project ID   CS271-400 Program 3          Date:5/3/15
; Description: Prompts the user to enter as many negative numbers between -1 and -100 inclusive
;              as they want and inputting a non-negative number will end the input process.
;			   the program will then display the number of valid inputs, the sum of those inputs,
;              and the average of the inputs.

INCLUDE Irvine32.inc

LOWER_RANGE = -100

.data
	;variables
		userName	BYTE	30 DUP(?)			;storage for user's name
		userNum		DWORD	0					;storage for the last user number
		userCount	DWORD	0					;stores how many negative numbers the user entered
		sum			DWORD	0					;stores the sum of all the negative numbers

	;prompts
		prompt			BYTE	"Please give one negative number between -1 and -100 inclusive at each", 0
		prompt2			BYTE	"prompt. When you no longer want to continue to give numbers, please give", 0
		prompt3			BYTE	"a non-negative number such as 0 or 1. Then I will calculate the average", 0
		prompt4			BYTE	"of the negative numbers you gave.", 0
		promptNums		BYTE	"Please give a number: ", 0
		warnRange		BYTE	"You cannot give numbers lower than -100.", 0
		promptName		BYTE	"Hello, what is your name? ", 0
		hello			BYTE	"Hi! ", 0	
		myName			BYTE	"My name is Jennifer Frase and this is Negative Average.", 0
		goodbye			BYTE	"Goodbye, ", 0
		thanks			BYTE	", thank you for using Negative Average.", 0
	
	;results
		results1		BYTE	"The sum of the ", 0
		results2		BYTE	" valid numbers you input is ", 0
		periods			BYTE	".", 0
		average			BYTE	"The rounded average is ", 0
		noNumbers		BYTE	"You did not give a negative number, so there are not results to show."

.code
main PROC
	;introduction
		;ask for user name
			mov		edx, OFFSET promptName
			call		WriteString
			mov		edx, OFFSET userName
			mov		ecx, 29
			call		ReadString
			call		Crlf
		;say hi and print intro
			mov		edx, OFFSET hello
			call		WriteString
			mov		edx, OFFSET userName
			call		WriteString
			call		CrLf
			mov		edx, OFFSET myName
			call		WriteString
			call		CrLf
			call		CrLf

	;userInstructions
		mov		edx, OFFSET prompt
		call		WriteString
		call		CrLf
		mov		edx, OFFSET prompt2
		call		WriteString
		call		CrLf
		mov		edx, OFFSET prompt3
		call		WriteString
		call		CrLf
		mov		edx, OFFSET prompt4
		call		WriteString
		call		CrLf
		call		CrLf
		jmp		AskNums

	;getUserData
		BadRange:		;warning for number being lower than -100
			dec		userCount
			sub		sum, eax
			mov		edx, OFFSET warnRange
			call		WriteString
			call		CrLf

		AskNums:		;asks for the numbers until a non-negative is given
			inc		userCount
			mov		edx, OFFSET	promptNums
			call		WriteString
			call		ReadInt
			call		CrLf
			add		sum, eax
			cmp		eax, LOWER_RANGE
			jl		BadRange
			cmp		eax, 0
			jl		AskNums
	
	;display results
		dec		userCount
		cmp		userCount, 0
		je		NonNegative
		sub		sum, eax
		mov		edx, OFFSET results1
		call		WriteString
		mov		eax, userCount
		call		WriteDec
		mov		edx, OFFSET	results2
		call		WriteString
		mov		eax, sum
		call		WriteInt
		cdq
		idiv		userCount
		mov		edx, OFFSET	periods
		call		WriteString
		call		CrLf
		mov		edx, OFFSET	average
		call		WriteString
		call		WriteInt
		mov		edx, OFFSET	periods
		call		WriteString
		jmp		Bye
		NonNegative:			;Statement if the user doesn't give a negative number
			mov		edx, OFFSet	noNumbers
			call		WriteString

	;farewell
		Bye:
			call		CrLf
			call		CrLf
			mov		edx, OFFSET goodbye
			call		WriteString
			mov		edx, OFFSET userName
			call		WriteString
			mov		edx, OFFSET thanks
			call		WriteString
			call		CrLf
			call		CrLf
	exit	; exit to operating system
main ENDP


END main