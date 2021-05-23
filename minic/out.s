############################
.data

# STRINGS ##################
$str0:	.asciiz "Inicio del programa\n"
$str1:	.asciiz "a"
$str2:	.asciiz "\n"
$str3:	.asciiz "No a y b\n"
$str4:	.asciiz "c ="
$str5:	.asciiz "d ="
$str6:	.asciiz "Final"

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
##Declarations
li	$t0, 0
sw	$t0, _a
li	$t0, 0
sw	$t0, _b
li	$t0, 5
li	$t1, 2
add	$t2, $t0, $t1
li	$t0, 2
sub	$t1, $t2, $t0
sw	$t1, _c
li	$t0, 0
sw	$t0, _d
##Statements
la	$a0, $str0
li	$v0, 4
syscall
lw	$t0, _a
beqz	$t0, $l4
la	$a0, $str1
li	$v0, 4
syscall
la	$a0, $str2
li	$v0, 4
syscall
b	$l5
$l4:
lw	$t1, _b
beqz	$t1, $l2
la	$a0, $str3
li	$v0, 4
syscall
b	$l3
$l2:
$l0:
lw	$t2, _c
beqz	$t2, $l1
la	$a0, $str4
li	$v0, 4
syscall
lw	$t3, _c
move	$a0, $t3
li	$v0, 1
syscall
la	$a0, $str2
li	$v0, 4
syscall
lw	$t3, _c
li	$t4, 2
sub	$t5, $t3, $t4
li	$t3, 1
add	$t4, $t5, $t3
sw	$t4, _c
b	$l0
$l1:
$l3:
$l5:
$l6:
la	$a0, $str5
li	$v0, 4
syscall
lw	$t0, _d
move	$a0, $t0
li	$v0, 1
syscall
la	$a0, $str2
li	$v0, 4
syscall
lw	$t0, _d
li	$t1, 1
add	$t2, $t0, $t1
sw	$t2, _d
lw	$t0, _d
li	$t1, 5
sub	$t2, $t0, $t1
bnez	$t2, $l6
la	$a0, $str6
li	$v0, 4
syscall
la	$a0, $str2
li	$v0, 4
syscall
li	$v0, 10
syscall
############################
# Fin de la ejecución ######
############################

