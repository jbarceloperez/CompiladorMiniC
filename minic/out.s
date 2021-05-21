############################
.data

# STRINGS ##################
$str0:	.asciiz "Inicio del programa\n"
$str1:	.asciiz "a"
$str2:	.asciiz "\n"
$str3:	.asciiz "No a y b\n"
$str4:	.asciiz "c ="
$str5:	.asciiz "\n"
$str6:	.asciiz "Final"
$str7:	.asciiz "\n"

# IDENTIFIERS ##############
_a:	.word 0
_b:	.word 0
_c:	.word 0
_d:	.word 0

############################
# Seccion de codigo
.text
.globl main

main:
##LongDeclarations=10
li	$t0,0
sw	$t0,_a
li	$t0,0
sw	$t0,_b
li	$t0,5
li	$t1,20
add	$t2,$t0,$t1
li	$t0,20
sub	$t1,$t2,$t0
sw	$t1,_c
##LongStatements=52
la	$a0,$str0
li	$v0,4
syscall
li	$v0,5
syscall
sw	$v0,_d
lw	$t0,_a
beqz	$t0,ET4
la	$a0,$str1
li	$v0,4
syscall
la	$a0,$str2
li	$v0,4
syscall
b	ET5
ET4:
lw	$t1,_b
beqz	$t1,ET2
la	$a0,$str3
li	$v0,4
syscall
b	ET3
ET2:
ET0:
lw	$t2,_c
beqz	$t2,ET1
la	$a0,$str4
li	$v0,4
syscall
lw	$t3,_c
move	$a0,$t3
li	$v0,1
syscall
la	$a0,$str5
li	$v0,4
syscall
lw	$t3,_c
li	$t4,2
sub	$t5,$t3,$t4
li	$t3,1
add	$t4,$t5,$t3
sw	$t4,_c
b	ET0
ET1:
ET3:
ET5:
la	$a0,$str6
li	$v0,4
syscall
la	$a0,$str7
li	$v0,4
syscall
li	$v0, 10
syscall
############################
# Fin de la ejecución ######
############################

##Regs:[0][0][0][0][0][0][0][0][0][0]
