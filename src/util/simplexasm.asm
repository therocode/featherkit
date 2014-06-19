;registers free to use: rax, rcx, rdx, r8-r11, xmm0-xmm5
;float function return value = first dword of xmm0
;xmm6-xmm15 = callee save on win64


%ifdef enableAVX
	%macro vsubps 3
		vsubps   %1,%2,%3
	%endmacro

	%macro vsubps 4
		vsubps   %1,%2,%3
	%endmacro

%else
	%macro vsubps 3    ;if %1 != %3
		movaps   %1,%2
		subps    %1,%3
	%endmacro

	%macro vsubps 4    ;if %1 == %3 
		movaps   %4,%2
		subps    %4,%3
		movaps   %1,%4
	%endmacro

	%macro vunpcklps 3
		movaps   %1,%2
		unpcklps %1,%3
	%endmacro

	%macro vshufps 4
		movaps   %1,%2
		shufps   %1,%3,%4
	%endmacro

	%macro vbroadcastss 2
		movss    %1,%2
		shufps   %1,%1,0
	%endmacro
%endif


section .data
	;simplex
	F3	     dd 0.33333334
	G3	     dd 0.16666667
	one      dd 1.0
	tval     dd 0.6
	retval   dd 32.0

	F2       dd 0.36602542
	G2       dd 0.21132487
	tval2d   dd 0.5
	retval2d dd 70.0

	grad3    db 1,1,0,  -1,1,0,  1,-1,0,  -1,-1,0,\
				1,0,1,  -1,0,1,  1,0,-1,  -1,0,-1,\
				0,1,1,  0,-1,1,  0,1,-1,  0,-1,-1

	;voronoi
	mindist  dd 2147483648.0
	v1000    dd 1000.0

	;white noise
	whiteret dd 255.0

section .text
default rel
	global  asm_raw_noise_3d,\
			asm_raw_noise_2d,\
			asm_VoronoiNoise_2d,\
			asm_WhiteNoise_2d


;-------------------
;3D Simplex
;-------------------
asm_raw_noise_3d:

%ifdef win64
	movups    [rsp-16],xmm6
	movups    [rsp-32],xmm7
	%ifndef enableAVX
		movups    [rsp-48],xmm8
	%endif
	mov       [rsp-112],rbx
	mov       rbx ,r9
	%define   perm rbx

%else ;elf64
	%define   perm rdi
%endif
;0=x 1=y 2=z

	unpcklps  xmm0,xmm1
	addss     xmm1,xmm0
	addss     xmm1,xmm2
	movlhps   xmm0,xmm2
	mulss     xmm1,[F3]
	shufps    xmm1,xmm1,0
	addps     xmm1,xmm0
	roundps   xmm1,xmm1,1
;0=xyz 1=ijk

	pshufd    xmm2,xmm1,1
	movhlps   xmm3,xmm1
	addss     xmm2,xmm1
	vbroadcastss xmm6,[G3]
	addss     xmm2,xmm3
	mulss     xmm2,xmm6
	shufps    xmm2,xmm2,0
	vsubps    xmm3,xmm1,xmm2
	subps     xmm0,xmm3
;0=x0y0z0 1=ijk 6=G3

	vbroadcastss xmm7,[one]
	pshufd    xmm2,xmm0,000001b ;yxx
	pshufd    xmm3,xmm0,100110b ;zyz
	movaps    xmm4,xmm2
	cmpps     xmm2,xmm3,5 ;y>=z  x>=y  x>=z
	cmpps     xmm4,xmm3,1 ;z> y  y> x  z> x
	movss     xmm3,xmm4
	shufps    xmm2,xmm2,010010b
	insertps  xmm4,xmm2,10001000b
	movlhps   xmm2,xmm3
	movaps    xmm3,xmm2
	andps     xmm2,xmm4
	orps      xmm3,xmm4
	andps     xmm2,xmm7
	andps     xmm3,xmm7
;0=x0y0z0 1=ijk 2=i1j1k1 3=i2j2k2 6=G3 7=1.0f

	vsubps    xmm4,xmm0,xmm2
	addps     xmm4,xmm6
	vsubps    xmm5,xmm0,xmm3
	addps     xmm6,xmm6
	addps     xmm5,xmm6
	vsubps    xmm7,xmm0,xmm7,xmm8
	addss     xmm6,[G3]
	shufps    xmm6,xmm6,0
	addps     xmm7,xmm6
;0=x0y0z0 1=ijk 2=i1j1k1 3=i2j2k2 4=x1y1z1 5=x2y2z2 7=x3y3z3

	cvtps2dq  xmm1,xmm1
	cvtps2dq  xmm2,xmm2
	cvtps2dq  xmm3,xmm3

	pextrb    r9d ,xmm1,8 ;kk
	pextrb    r10d,xmm2,8 ;k1
	pextrb    r11d,xmm3,8 ;k2
	add       r9  ,perm
	movzx     rax ,byte [r9]
	movzx     rcx ,byte [r9+r10]
	movzx     rdx ,byte [r9+r11]
	movzx     r8  ,byte [r9+1]

	pextrb    r9d ,xmm1,4 ;jj
	pextrb    r10d,xmm2,4 ;j1
	pextrb    r11d,xmm3,4 ;j2
	add       r9  ,perm
	add       r10 ,rcx
	add       r11 ,rdx
	mov       al  ,byte [r9+rax]
	mov       cl  ,byte [r9+r10]
	mov       dl  ,byte [r9+r11]
	mov       r8b ,byte [r9+r8+1]
    
	pextrb    r9d ,xmm1,0 ;ii
	movd      r10d,xmm2   ;i1
	movd      r11d,xmm3   ;i2
	add       r9  ,perm
	add       r10 ,rcx
	add       r11 ,rdx
	mov       al  ,byte [r9+rax]
	mov       cl  ,byte [r9+r10]
	mov       dl  ,byte [r9+r11]
	mov       r8b ,byte [r9+r8+1]

	mov       r9  ,12
	div       r9b
	shr       ax  ,8                 ;gi0
lea eax,[eax+eax*2]
mov r10,qword grad3
pmovsxbd xmm1,[rax+r10]
	;pmovsxbd  xmm1,[grad3+rax+rax*2] ;grad3[gi0]
	mov       rax ,rcx
	div       r9b
	shr       ax  ,8
lea eax,[eax+eax*2]
pmovsxbd xmm2,[rax+r10]
	;pmovsxbd  xmm2,[grad3+rax+rax*2]
	mov       rax ,rdx
	div       r9b
	shr       ax  ,8
lea eax,[eax+eax*2]
pmovsxbd xmm3,[rax+r10]
	;pmovsxbd  xmm3,[grad3+rax+rax*2]
	mov       rax ,r8
	div       r9b
	shr       ax  ,8
lea eax,[eax+eax*2]
pmovsxbd xmm6,[rax+r10]
	;pmovsxbd  xmm6,[grad3+rax+rax*2]

	cvtdq2ps  xmm1,xmm1
	cvtdq2ps  xmm2,xmm2
	cvtdq2ps  xmm3,xmm3
	cvtdq2ps  xmm6,xmm6
;0=x0y0z0 1=grad3[gi0] 2=grad3[gi1] 3=grad3[gi2] 4=x1y1z1 5=x2y2z2 6=grad3[gi3] 7=x3y3z3

	dpps      xmm1,xmm0,01110001b
	dpps      xmm2,xmm4,01110001b
	dpps      xmm3,xmm5,01110001b
	dpps      xmm6,xmm7,01110001b

	unpcklps  xmm1,xmm2
	unpcklps  xmm3,xmm6
	movlhps   xmm1,xmm3

	mulps     xmm0,xmm0
	mulps     xmm4,xmm4
	mulps     xmm5,xmm5
	mulps     xmm7,xmm7

	vunpcklps xmm2,xmm0,xmm5  ;0819
	vunpcklps xmm3,xmm4,xmm7  ;4C5D
	unpckhps  xmm0,xmm5       ;2A3B
	unpckhps  xmm4,xmm7       ;6E7F

	vunpcklps xmm5,xmm2,xmm3  ;048C
	unpckhps  xmm2,xmm3       ;159D
	unpcklps  xmm0,xmm4       ;26AE

	vbroadcastss xmm4,[tval]
	subps     xmm4,xmm5
	subps     xmm4,xmm2
	subps     xmm4,xmm0       ;t0t1t2t3

	pxor      xmm2,xmm2
	cmpps     xmm2,xmm4,1
	andps     xmm2,xmm4
	mulps     xmm2,xmm2
	mulps     xmm2,xmm2

	mulps     xmm2,xmm1       ;n0n1n2n3
;2=n0n1n2n3

	movhlps   xmm0,xmm2
	addps     xmm0,xmm2
	pshufd    xmm1,xmm0,1
	addss     xmm0,xmm1

	mulss     xmm0,[retval]

%ifdef win64
	movups    xmm6,[rsp-16]
	movups    xmm7,[rsp-32]
	%ifndef enableAVX
		movups    xmm8,[rsp-48]
	%endif
	mov       rbx ,[rsp-112]
%endif

	%undef    perm
	ret


;-------------------
;2D Simplex
;-------------------
asm_raw_noise_2d:

%ifdef win64
	%ifndef enableAVX
		movups    [rsp-16],xmm6
	%endif
	%define   perm r8

%else ;elf64
	%define   perm rdi
%endif
;0=x 1=y

	unpcklps  xmm0,xmm1
	addss     xmm1,xmm0
	mulss     xmm1,[F2]
	shufps    xmm1,xmm1,0
	addps     xmm1,xmm0
	roundps   xmm1,xmm1,1
;0=xy 1=ij

	vbroadcastss xmm2,[G2]
	pshufd    xmm4,xmm1,1
	addss     xmm4,xmm1
	mulss     xmm4,xmm2
	shufps    xmm4,xmm4,0
	vsubps    xmm5,xmm1,xmm4
	subps     xmm0,xmm5
;0=x0y0 1=ij 2=G2

	vbroadcastss xmm5,[one]
	pshufd    xmm3,xmm0,0001b
	cmpss     xmm3,xmm0,5
	shufps    xmm3,xmm3,0001b
	shufps    xmm0,xmm0,0001b
	cmpss     xmm3,xmm0,6
	andps     xmm3,xmm5
	shufps    xmm0,xmm0,0001b ;can this be done better?
;0=x0y0 1=ij 2=G2 3=i1j1 5=1.0

	vsubps    xmm4,xmm0,xmm3
	addps     xmm4,xmm2
	addps     xmm2,xmm2
	vsubps    xmm5,xmm0,xmm5,xmm6
	addps     xmm2,xmm5
;0=x0y0 1=ij 2=x2y2 3=i1j1 4=x1y1

	cvtps2dq  xmm1,xmm1
	cvtps2dq  xmm3,xmm3

	pextrb    r9d ,xmm1,4 ;jj
	pextrb    r10d,xmm3,4 ;j1
	add       r9  ,perm
	movzx     rax ,byte [r9]
	movzx     rcx ,byte [r9+r10]
	movzx     rdx ,byte [r9+1]

	pextrb	  r9d ,xmm1,0 ;ii
	movd      r10d,xmm3   ;i1
	add       r9  ,perm
	add       r10 ,rcx
	mov       al  ,byte [r9+rax]
	mov       cl  ,byte [r9+r10]
	mov       dl  ,byte [r9+rdx+1]

	mov       r8  ,12
	div       r8b
	shr       ax  ,8                 ;gi0
lea eax,[eax+eax*2]
add rax,[grad3 wrt rip]
pmovsxbd xmm1,[rax]
	;pmovsxbd  xmm1,[grad3+rax+rax*2] ;grad3[gi0]
	mov       rax ,rcx
	div       r8b
	shr       ax  ,8
lea eax,[eax+eax*2]
add rax,[grad3 wrt rip]
pmovsxbd xmm3,[rax]
	;pmovsxbd  xmm3,[grad3+rax+rax*2]
	mov       rax ,rdx
	div       r8b
	shr       ax  ,8
lea eax,[eax+eax*2]
add rax,[grad3 wrt rip]
pmovsxbd xmm5,[rax]
	;pmovsxbd  xmm5,[grad3+rax+rax*2]

	cvtdq2ps  xmm1,xmm1
	cvtdq2ps  xmm3,xmm3
	cvtdq2ps  xmm5,xmm5
;0=x0y0 1=grad3[gi0] 2=x2y2 3=grad3[gi1] 4=x1y1 5=grad3[gi2]

	dpps      xmm1,xmm0,00110001b
	dpps      xmm3,xmm4,00110001b
	dpps      xmm5,xmm2,00110001b

	movlhps   xmm0,xmm4
	mulps     xmm0,xmm0
	mulps     xmm2,xmm2

	vshufps   xmm4,xmm0,xmm2,001000b
	shufps    xmm0,xmm2,011101b

	vbroadcastss xmm2,[tval2d]
	subps     xmm2,xmm4
	subps     xmm2,xmm0 ;t0t1t2

	pxor      xmm4,xmm4
	cmpps     xmm4,xmm2,1
	andps     xmm4,xmm2
	mulps     xmm4,xmm4
	mulps     xmm4,xmm4

	unpcklps  xmm1,xmm3
	movlhps   xmm1,xmm5
	mulps     xmm4,xmm1 ;n0n1n2
;7=n0n1n2

	pshufd    xmm0,xmm4,01b
	movhlps   xmm1,xmm4
	addss     xmm0,xmm4
	addss     xmm0,xmm1
	mulss     xmm0,[retval2d]

%ifdef win64
	%ifndef enableAVX
		movups    xmm6,[rsp-16]
	%endif
%endif

	%undef    perm
	ret


;-------------------
; Voronoi 2D
;-------------------
asm_VoronoiNoise_2d:

%ifdef win64
	movups    [rsp-16],xmm6
	movups    [rsp-32],xmm7
	movups    [rsp-48],xmm8
	movups    [rsp-64],xmm9
	movups    [rsp-80],xmm10
%endif
;0=x 1=y r8=perm

	vunpcklps xmm3,xmm0,xmm1
	roundps   xmm4,xmm3,1
;3=xy 4=xyInt

	vbroadcastss xmm5,[one]
	subps     xmm4,xmm5
	subps     xmm4,xmm5           ;xycur
	movss     xmm10,xmm4
	movss     xmm7,[v1000]
	movss     xmm8,[mindist]
	mov       al  ,6
	mov       cl  ,6
findcube:
	movss     xmm0,xmm4
	pshufd    xmm1,xmm4,1
	call      asm_WhiteNoise_2d
	movss     xmm6,xmm0
	movss     xmm0,xmm4
	addss     xmm1,xmm7
	call      asm_WhiteNoise_2d
	unpcklps  xmm6,xmm0
	addps     xmm6,xmm4           ;xyPos
	vsubps    xmm2,xmm6,xmm3
	dpps      xmm2,xmm2,00110001b ;dist
	vcmpss    xmm0,xmm2,xmm8,1
	shufps    xmm0,xmm0,0
	blendvps  xmm9,xmm6           ;xyCandidate
	minss     xmm8,xmm2

	addss     xmm4,xmm5
	sub       al  ,1
	jnz       findcube
	mov       al  ,6
	movss     xmm4,xmm10
	shufps    xmm4,xmm4,1
	addss     xmm4,xmm5  ;...
	shufps    xmm4,xmm4,1
	sub       cl  ,1
	jnz       findcube
;9=xyCandidate

	roundps   xmm0,xmm9,1
	pshufd    xmm1,xmm0,1
	call      asm_WhiteNoise_2d

%ifdef win64
	movups    xmm6,[rsp-16]
	movups    xmm7,[rsp-32]
	movups    xmm8,[rsp-48]
	movups    xmm9,[rsp-64]
	movups    xmm10,[rsp-80]
%endif
	ret


;-------------------
; White Noise 2D
;-------------------
asm_WhiteNoise_2d:

%ifdef win64
	%define  perm r8
%else ;elf64
	%define  perm rdi
%endif
;0=x 1=y

	roundss  xmm0,xmm0,1
	roundss  xmm2,xmm1,1
	cvtss2si edx ,xmm0
	cvtss2si r9d ,xmm2
	and      edx ,255
	and      r9  ,255
	mov      r9b ,[perm+r9]
	add      rdx ,r9
	mov      r9b ,[perm+rdx]
	cvtsi2ss xmm0,r9d
	divss    xmm0,[whiteret]

	%undef   perm
	ret

