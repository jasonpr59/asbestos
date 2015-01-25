#include <src/kernel/interrupts.h>

trap_handler_0:
	push $0
	call handle_interrupt

trap_handler_1:
	push $1
	call handle_interrupt

trap_handler_2:
	push $2
	call handle_interrupt

trap_handler_3:
	push $3
	call handle_interrupt

trap_handler_4:
	push $4
	call handle_interrupt

trap_handler_5:
	push $5
	call handle_interrupt

trap_handler_6:
	push $6
	call handle_interrupt

trap_handler_7:
	push $7
	call handle_interrupt

trap_handler_8:
	push $8
	call handle_interrupt

trap_handler_9:
	push $9
	call handle_interrupt

trap_handler_10:
	push $10
	call handle_interrupt

trap_handler_11:
	push $11
	call handle_interrupt

trap_handler_12:
	push $12
	call handle_interrupt

trap_handler_13:
	push $13
	call handle_interrupt

trap_handler_14:
	push $14
	call handle_interrupt

trap_handler_15:
	push $15
	call handle_interrupt

trap_handler_16:
	push $16
	call handle_interrupt

.align 4
.global trap_functions
trap_functions:
	.long trap_handler_0
	.long trap_handler_1
	.long trap_handler_2
	.long trap_handler_3
	.long trap_handler_4
	.long trap_handler_5
	.long trap_handler_6
	.long trap_handler_7
	.long trap_handler_8
	.long trap_handler_9
	.long trap_handler_10
	.long trap_handler_11
	.long trap_handler_12
	.long trap_handler_13
	.long trap_handler_14
	.long trap_handler_15
	.long trap_handler_16
