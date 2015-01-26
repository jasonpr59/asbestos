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

trap_handler_17:
	// Push dummy error code.
	push $0
	push $17
	jmp call_handler

trap_handler_18:
	// Push dummy error code.
	push $0
	push $18
	jmp call_handler

trap_handler_19:
	// Push dummy error code.
	push $0
	push $19
	jmp call_handler

trap_handler_20:
	// Push dummy error code.
	push $0
	push $20
	jmp call_handler

trap_handler_21:
	// Push dummy error code.
	push $0
	push $21
	jmp call_handler

trap_handler_22:
	// Push dummy error code.
	push $0
	push $22
	jmp call_handler

trap_handler_23:
	// Push dummy error code.
	push $0
	push $23
	jmp call_handler

trap_handler_24:
	// Push dummy error code.
	push $0
	push $24
	jmp call_handler

trap_handler_25:
	// Push dummy error code.
	push $0
	push $25
	jmp call_handler

trap_handler_26:
	// Push dummy error code.
	push $0
	push $26
	jmp call_handler

trap_handler_27:
	// Push dummy error code.
	push $0
	push $27
	jmp call_handler

trap_handler_28:
	// Push dummy error code.
	push $0
	push $28
	jmp call_handler

trap_handler_29:
	// Push dummy error code.
	push $0
	push $29
	jmp call_handler

trap_handler_30:
	// Push dummy error code.
	push $0
	push $30
	jmp call_handler

trap_handler_31:
	// Push dummy error code.
	push $0
	push $31
	jmp call_handler

trap_handler_32:
	// Push dummy error code.
	push $0
	push $32
	jmp call_handler

trap_handler_33:
	// Push dummy error code.
	push $0
	push $33
	jmp call_handler

trap_handler_34:
	// Push dummy error code.
	push $0
	push $34
	jmp call_handler

trap_handler_35:
	// Push dummy error code.
	push $0
	push $35
	jmp call_handler

trap_handler_36:
	// Push dummy error code.
	push $0
	push $36
	jmp call_handler

trap_handler_37:
	// Push dummy error code.
	push $0
	push $37
	jmp call_handler

trap_handler_38:
	// Push dummy error code.
	push $0
	push $38
	jmp call_handler

trap_handler_39:
	// Push dummy error code.
	push $0
	push $39
	jmp call_handler

trap_handler_40:
	// Push dummy error code.
	push $0
	push $40
	jmp call_handler

trap_handler_41:
	// Push dummy error code.
	push $0
	push $41
	jmp call_handler

trap_handler_42:
	// Push dummy error code.
	push $0
	push $42
	jmp call_handler

trap_handler_43:
	// Push dummy error code.
	push $0
	push $43
	jmp call_handler

trap_handler_44:
	// Push dummy error code.
	push $0
	push $44
	jmp call_handler

trap_handler_45:
	// Push dummy error code.
	push $0
	push $45
	jmp call_handler

trap_handler_46:
	// Push dummy error code.
	push $0
	push $46
	jmp call_handler

trap_handler_47:
	// Push dummy error code.
	push $0
	push $47
	jmp call_handler

trap_handler_48:
	// Push dummy error code.
	push $0
	push $48
	jmp call_handler

trap_handler_49:
	// Push dummy error code.
	push $0
	push $49
	jmp call_handler

trap_handler_50:
	// Push dummy error code.
	push $0
	push $50
	jmp call_handler

trap_handler_51:
	// Push dummy error code.
	push $0
	push $51
	jmp call_handler

trap_handler_52:
	// Push dummy error code.
	push $0
	push $52
	jmp call_handler

trap_handler_53:
	// Push dummy error code.
	push $0
	push $53
	jmp call_handler

trap_handler_54:
	// Push dummy error code.
	push $0
	push $54
	jmp call_handler

trap_handler_55:
	// Push dummy error code.
	push $0
	push $55
	jmp call_handler

trap_handler_56:
	// Push dummy error code.
	push $0
	push $56
	jmp call_handler

trap_handler_57:
	// Push dummy error code.
	push $0
	push $57
	jmp call_handler

trap_handler_58:
	// Push dummy error code.
	push $0
	push $58
	jmp call_handler

trap_handler_59:
	// Push dummy error code.
	push $0
	push $59
	jmp call_handler

trap_handler_60:
	// Push dummy error code.
	push $0
	push $60
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
	.long trap_handler_17
	.long trap_handler_18
	.long trap_handler_19
	.long trap_handler_20
	.long trap_handler_21
	.long trap_handler_22
	.long trap_handler_23
	.long trap_handler_24
	.long trap_handler_25
	.long trap_handler_26
	.long trap_handler_27
	.long trap_handler_28
	.long trap_handler_29
	.long trap_handler_30
	.long trap_handler_31
	.long trap_handler_32
	.long trap_handler_33
	.long trap_handler_34
	.long trap_handler_35
	.long trap_handler_36
	.long trap_handler_37
	.long trap_handler_38
	.long trap_handler_39
	.long trap_handler_40
	.long trap_handler_41
	.long trap_handler_42
	.long trap_handler_43
	.long trap_handler_44
	.long trap_handler_45
	.long trap_handler_46
	.long trap_handler_47
	.long trap_handler_48
	.long trap_handler_49
	.long trap_handler_50
	.long trap_handler_51
	.long trap_handler_52
	.long trap_handler_53
	.long trap_handler_54
	.long trap_handler_55
	.long trap_handler_56
	.long trap_handler_57
	.long trap_handler_58
	.long trap_handler_59
	.long trap_handler_60
