TITLE Fibonacci Flags     (Prog2_fib.asm)

; Author: Jennifer Frase
; Course / Project ID   CS271 Program 2          Date:4/19/15
; Description: Asks the user for a number and displays that many fibonacci numbers

INCLUDE Irvine32.inc

UPPER_RANGE = 46

.data
	userName	BYTE	30 DUP(?)			;storage for user's name
	firstNum	DWORD	0					;storage for the last printed number
	secondNum	DWORD	1					;storage for printed numbers
	loopTimes	DWORD	?					;number of fibonacci numbers to print
	sum			DWORD	?					;temp storage for sums
	counter		DWORD	0					;used to determine when a row is done

	;prompts
	instruct	BYTE	"In Fibonacci Flags, you will give a number between 1 and 46 and then", 0
	instruct2	BYTE	"I will give you that many fibonacci numbers in the sequence.", 0
	instruct3	BYTE	'The more numbers you want to see, the bigger the "flags" will become.', 0
	prompt		BYTE	"How many fibinacci numbers do you want to see? (1 - 46)", 0
	credit		BYTE	"**EC: As per the extra credit, this program has alligned columns", 0
	warnPrompt	BYTE	"Please only give a number between 1 and 46 inclusive.", 0
	promptName	BYTE	"Hello, what is your name? ", 0

	hello		BYTE	"Hi! ", 0	
	myName		BYTE	"My name is Jennifer Frase and this is Fibonacci Flags.", 0
	goodbye		BYTE	"Thank you for using Fibonacci Flags.", 0
	space		BYTE	"      ", 0					;basic space between numbers
	singleSpace BYTE	" ", 0						;used for added spaces between numbers
	firstSpace	BYTE	"              ", 0			;used for the spaces after the first number


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

	;userInstructions
		mov		edx, OFFSET instruct
		call		WriteString
		call		CrLf
		mov		edx, OFFSET instruct2
		call		WriteString
		call		CrLf
		mov		edx, OFFSET instruct3
		call		WriteString
		call		CrLf
		mov		edx, OFFSET	credit
		call		WriteString
		call		CrLf
		call		CrLf
		jmp		AskNum

	;getUserData
		BadNum:			;warning for invalid input number
			mov		edx, OFFSET warnPrompt
			call		WriteString
			call		CrLf

		AskNum:			;asks for the number of fibonacci number to display
			mov		edx, OFFSET	prompt
			call		WriteString
			call		ReadInt
			mov		loopTimes, eax
			call		CrLf
			cmp		eax, UPPER_RANGE
			jg		BadNum
			cmp		eax, 1
			jl		BadNum
	
	;displayFibs
		mov		eax, secondNum
		call		WriteDec
		mov		edx, OFFSET firstSpace
		call		WriteString
		mov		eax, counter
		add		eax, 1
		mov		counter, eax
		mov		ecx, loopTimes
		sub		ecx, 1
		cmp		ecx, 0
		je		Bye

		FibLoop:		;calculates and prints out the numbers
			mov		eax, firstNum
			add		eax, secondNum
			call		WriteDec
			mov		edx, OFFSET space
			call		WriteString
			mov		sum, eax
			cmp		eax, 100000000
			jge		MoveNums

			SpaceLoop:		;prints the right number of spaces so numbers are alligned
				mov		edx, OFFSET singleSpace
				call		WriteString
				mov		ebx, 10
				mul		ebx
				cmp		eax, 100000000
				jl		SpaceLoop
			
			MoveNums:		;moves second number to first number and sum to second number
			mov		eax, secondNum
			mov		firstNum, eax
			mov		eax, sum
			mov		secondNum, eax
			mov		eax, counter
			add		eax, 1
			cmp		eax, 5
			jne		NoCol

			NewCol:			;starts a new line after every 5 numbers
				call		Crlf
				mov		eax, 0
			
			NoCol:		;adjusts counter and checks if there is another number to print
			mov		counter, eax
			loop	FibLoop

	;farewell
		Bye:
			call		Crlf
			call		Crlf
			mov		edx, OFFSET goodbye
			call		WriteString
			call		Crlf
			call		Crlf
	exit	; exit to operating system
main ENDP


END main