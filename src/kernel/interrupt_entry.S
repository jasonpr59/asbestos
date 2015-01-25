#include <src/kernel/interrupts.h>

trap_handler_0:
	// Push dummy error code.
	push $0
	push $0
	jmp call_handler

trap_handler_1:
	// Push dummy error code.
	push $0
	push $1
	jmp call_handler

trap_handler_2:
	push $2
	jmp call_handler

trap_handler_3:
	// Push dummy error code.
	push $0
	push $3
	jmp call_handler

trap_handler_4:
	// Push dummy error code.
	push $0
	push $4
	jmp call_handler

trap_handler_5:
	// Push dummy error code.
	push $0
	push $5
	jmp call_handler

trap_handler_6:
	// Push dummy error code.
	push $0
	push $6
	jmp call_handler

trap_handler_7:
	// Push dummy error code.
	push $0
	push $7
	jmp call_handler

trap_handler_8:
	push $8
	jmp call_handler

trap_handler_9:
	// Push dummy error code.
	push $0
	push $9
	jmp call_handler

trap_handler_10:
	push $10
	jmp call_handler

trap_handler_11:
	push $11
	jmp call_handler

trap_handler_12:
	push $12
	jmp call_handler

trap_handler_13:
	push $13
	jmp call_handler

trap_handler_14:
	push $14
	jmp call_handler

trap_handler_15:
	push $15
	jmp call_handler

trap_handler_16:
	// Push dummy error code.
	push $0
	push $16
	jmp call_handler

// Call the interrupt handler. Pass the trap frame as an argument.
call_handler:
	pushal
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
