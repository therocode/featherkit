section .text
	global CheckSse41

;-------------------
;CheckSse41: looks for sse4.1; returns 1 if true, otherwise 0
;-------------------
CheckSse41:
	push rbx
	mov  eax ,1
	cpuid
	shr  ecx ,19 ;sse4.1 (ecx:19)
	and  ecx ,1
	mov  eax ,ecx
	pop  rbx
	ret