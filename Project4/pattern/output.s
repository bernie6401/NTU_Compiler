.data
_g_g1: .space 4
_g_g2: .space 4
_g_g3: .space 4
_g_g4: .space 4
_g_g5: .space 16
_g_g6: .space 16
_g_g7: .space 16
_g_g8: .space 16
_g_g9: .space 8
_g_g10: .space 8
.text
_start_main:
str x30, [sp, #-8]
str x29, [sp, #-16]
str x19, [sp, #-24]
str x20, [sp, #-32]
str x21, [sp, #-40]
str x22, [sp, #-48]
str x23, [sp, #-56]
str x24, [sp, #-64]
str x25, [sp, #-72]
str x26, [sp, #-80]
str x27, [sp, #-88]
str x28, [sp, #-96]
str x29, [sp, #-104]
add x29, sp, #-112
.data
_AR_SIZE_0: .word 96
.align 3
.text
ldr w19, _AR_SIZE_0
sub sp, x29, w19
.data
_INT_CONST_0: .word 2
.align 3
.text
ldr x19, _INT_CONST_0
.data
_INT_CONST_1: .word 16
.align 3
.text
ldr x20, _INT_CONST_1
sub x20, x29, x20
str w19, [x20, #0]
.data
_INT_CONST_2: .word 2
.align 3
.text
ldr x19, _INT_CONST_2
.data
_INT_CONST_3: .word 32
.align 3
.text
ldr x20, _INT_CONST_3
sub x20, x29, x20
str s19, [x20, #0]
.data
_INT_CONST_4: .word 2
.align 3
.text
ldr x19, _INT_CONST_4
.data
_INT_CONST_5: .word 48
.align 3
.text
ldr x20, _INT_CONST_5
sub x20, x29, x20
str w19, [x20, #0]
.data
_INT_CONST_6: .word 2
.align 3
.text
ldr x19, _INT_CONST_6
.data
_INT_CONST_7: .word 64
.align 3
.text
ldr x20, _INT_CONST_7
sub x20, x29, x20
str s19, [x20, #0]
.data
_INT_CONST_8: .word 1
.align 3
.text
ldr x19, _INT_CONST_8
ldr x20, =_g_g1
str w19, [x20, #0]
.data
_FLOAT_CONST_0: .float 2.000000
.align 3
.text
ldr s19, _FLOAT_CONST_0
ldr x20, =_g_g2
str s19, [x20, #0]
.data
_INT_CONST_9: .word 3
.align 3
.text
ldr x19, _INT_CONST_9
ldr x20, =_g_g3
str w19, [x20, #0]
.data
_FLOAT_CONST_1: .float 4.000000
.align 3
.text
ldr s19, _FLOAT_CONST_1
ldr x20, =_g_g4
str s19, [x20, #0]
.data
_INT_CONST_10: .word 5
.align 3
.text
ldr x19, _INT_CONST_10
ldr x20, =_g_g5
mov x21, #0
.data
_INT_CONST_11: .word 2
.align 3
.text
ldr x22, _INT_CONST_11
mul x21, x21, x22
.data
_INT_CONST_12: .word 0
.align 3
.text
ldr x22, _INT_CONST_12
lsl x22, x22, #2
add x21, x21, x22
add x20, x20, x21
str w19, [x20, #0]
.data
_INT_CONST_13: .word 55
.align 3
.text
ldr x19, _INT_CONST_13
ldr x20, =_g_g5
mov x21, #0
.data
_INT_CONST_14: .word 2
.align 3
.text
ldr x22, _INT_CONST_14
mul x21, x21, x22
.data
_INT_CONST_15: .word 1
.align 3
.text
ldr x22, _INT_CONST_15
lsl x22, x22, #2
add x21, x21, x22
add x20, x20, x21
str w19, [x20, #0]
.data
_FLOAT_CONST_2: .float 6.000000
.align 3
.text
ldr s19, _FLOAT_CONST_2
ldr x20, =_g_g6
mov x21, #0
.data
_INT_CONST_16: .word 2
.align 3
.text
ldr x22, _INT_CONST_16
mul x21, x21, x22
.data
_INT_CONST_17: .word 0
.align 3
.text
ldr x22, _INT_CONST_17
lsl x22, x22, #2
add x21, x21, x22
add x20, x20, x21
str s19, [x20, #0]
.data
_FLOAT_CONST_3: .float 66.000000
.align 3
.text
ldr s19, _FLOAT_CONST_3
ldr x20, =_g_g6
mov x21, #0
.data
_INT_CONST_18: .word 2
.align 3
.text
ldr x22, _INT_CONST_18
mul x21, x21, x22
.data
_INT_CONST_19: .word 1
.align 3
.text
ldr x22, _INT_CONST_19
lsl x22, x22, #2
add x21, x21, x22
add x20, x20, x21
str s19, [x20, #0]
.data
_INT_CONST_20: .word 7
.align 3
.text
ldr x19, _INT_CONST_20
ldr x20, =_g_g7
mov x21, #0
.data
_INT_CONST_21: .word 2
.align 3
.text
ldr x22, _INT_CONST_21
mul x21, x21, x22
.data
_INT_CONST_22: .word 0
.align 3
.text
ldr x22, _INT_CONST_22
lsl x22, x22, #2
add x21, x21, x22
add x20, x20, x21
str w19, [x20, #0]
.data
_INT_CONST_23: .word 77
.align 3
.text
ldr x19, _INT_CONST_23
ldr x20, =_g_g7
mov x21, #0
.data
_INT_CONST_24: .word 2
.align 3
.text
ldr x22, _INT_CONST_24
mul x21, x21, x22
.data
_INT_CONST_25: .word 1
.align 3
.text
ldr x22, _INT_CONST_25
lsl x22, x22, #2
add x21, x21, x22
add x20, x20, x21
str w19, [x20, #0]
.data
_FLOAT_CONST_4: .float 8.000000
.align 3
.text
ldr s19, _FLOAT_CONST_4
ldr x20, =_g_g8
mov x21, #0
.data
_INT_CONST_26: .word 2
.align 3
.text
ldr x22, _INT_CONST_26
mul x21, x21, x22
.data
_INT_CONST_27: .word 0
.align 3
.text
ldr x22, _INT_CONST_27
lsl x22, x22, #2
add x21, x21, x22
add x20, x20, x21
str s19, [x20, #0]
.data
_FLOAT_CONST_5: .float 88.000000
.align 3
.text
ldr s19, _FLOAT_CONST_5
ldr x20, =_g_g8
mov x21, #0
.data
_INT_CONST_28: .word 2
.align 3
.text
ldr x22, _INT_CONST_28
mul x21, x21, x22
.data
_INT_CONST_29: .word 1
.align 3
.text
ldr x22, _INT_CONST_29
lsl x22, x22, #2
add x21, x21, x22
add x20, x20, x21
str s19, [x20, #0]
.data
_INT_CONST_30: .word 9
.align 3
.text
ldr x19, _INT_CONST_30
ldr x20, =_g_g9
mov x21, #0
.data
_INT_CONST_31: .word 2
.align 3
.text
ldr x22, _INT_CONST_31
mul x21, x21, x22
.data
_INT_CONST_32: .word 0
.align 3
.text
ldr x22, _INT_CONST_32
lsl x22, x22, #2
add x21, x21, x22
add x20, x20, x21
str w19, [x20, #0]
.data
_INT_CONST_33: .word 99
.align 3
.text
ldr x19, _INT_CONST_33
ldr x20, =_g_g9
mov x21, #0
.data
_INT_CONST_34: .word 2
.align 3
.text
ldr x22, _INT_CONST_34
mul x21, x21, x22
.data
_INT_CONST_35: .word 1
.align 3
.text
ldr x22, _INT_CONST_35
lsl x22, x22, #2
add x21, x21, x22
add x20, x20, x21
str w19, [x20, #0]
.data
_FLOAT_CONST_6: .float 10.000000
.align 3
.text
ldr s19, _FLOAT_CONST_6
ldr x20, =_g_g10
mov x21, #0
.data
_INT_CONST_36: .word 2
.align 3
.text
ldr x22, _INT_CONST_36
mul x21, x21, x22
.data
_INT_CONST_37: .word 0
.align 3
.text
ldr x22, _INT_CONST_37
lsl x22, x22, #2
add x21, x21, x22
add x20, x20, x21
str s19, [x20, #0]
.data
_FLOAT_CONST_7: .float 100.000000
.align 3
.text
ldr s19, _FLOAT_CONST_7
ldr x20, =_g_g10
mov x21, #0
.data
_INT_CONST_38: .word 2
.align 3
.text
ldr x22, _INT_CONST_38
mul x21, x21, x22
.data
_INT_CONST_39: .word 1
.align 3
.text
ldr x22, _INT_CONST_39
lsl x22, x22, #2
add x21, x21, x22
add x20, x20, x21
str s19, [x20, #0]
.data
_INT_CONST_40: .word 1
.align 3
.text
ldr x19, _INT_CONST_40
.data
_INT_CONST_41: .word 0
.align 3
.text
ldr x20, _INT_CONST_41
sub x20, x29, x20
str w19, [x20, #0]
.data
_FLOAT_CONST_8: .float 2.000000
.align 3
.text
ldr s19, _FLOAT_CONST_8
.data
_INT_CONST_42: .word 4
.align 3
.text
ldr x20, _INT_CONST_42
sub x20, x29, x20
str s19, [x20, #0]
.data
_INT_CONST_43: .word 3
.align 3
.text
ldr x19, _INT_CONST_43
.data
_INT_CONST_44: .word 8
.align 3
.text
ldr x20, _INT_CONST_44
sub x20, x29, x20
str w19, [x20, #0]
.data
_FLOAT_CONST_9: .float 4.000000
.align 3
.text
ldr s19, _FLOAT_CONST_9
.data
_INT_CONST_45: .word 12
.align 3
.text
ldr x20, _INT_CONST_45
sub x20, x29, x20
str s19, [x20, #0]
.data
_INT_CONST_46: .word 5
.align 3
.text
ldr x19, _INT_CONST_46
.data
_INT_CONST_47: .word 16
.align 3
.text
ldr x20, _INT_CONST_47
sub x20, x29, x20
mov x21, #0
.data
_INT_CONST_48: .word 2
.align 3
.text
ldr x22, _INT_CONST_48
mul x21, x21, x22
.data
_INT_CONST_49: .word 0
.align 3
.text
ldr x22, _INT_CONST_49
lsl x22, x22, #2
add x21, x21, x22
sub x20, x20, x21
str w19, [x20, #0]
.data
_INT_CONST_50: .word 55
.align 3
.text
ldr x19, _INT_CONST_50
.data
_INT_CONST_51: .word 16
.align 3
.text
ldr x20, _INT_CONST_51
sub x20, x29, x20
mov x21, #0
.data
_INT_CONST_52: .word 2
.align 3
.text
ldr x22, _INT_CONST_52
mul x21, x21, x22
.data
_INT_CONST_53: .word 1
.align 3
.text
ldr x22, _INT_CONST_53
lsl x22, x22, #2
add x21, x21, x22
sub x20, x20, x21
str w19, [x20, #0]
.data
_FLOAT_CONST_10: .float 6.000000
.align 3
.text
ldr s19, _FLOAT_CONST_10
.data
_INT_CONST_54: .word 32
.align 3
.text
ldr x20, _INT_CONST_54
sub x20, x29, x20
mov x21, #0
.data
_INT_CONST_55: .word 2
.align 3
.text
ldr x22, _INT_CONST_55
mul x21, x21, x22
.data
_INT_CONST_56: .word 0
.align 3
.text
ldr x22, _INT_CONST_56
lsl x22, x22, #2
add x21, x21, x22
sub x20, x20, x21
str s19, [x20, #0]
.data
_FLOAT_CONST_11: .float 66.000000
.align 3
.text
ldr s19, _FLOAT_CONST_11
.data
_INT_CONST_57: .word 32
.align 3
.text
ldr x20, _INT_CONST_57
sub x20, x29, x20
mov x21, #0
.data
_INT_CONST_58: .word 2
.align 3
.text
ldr x22, _INT_CONST_58
mul x21, x21, x22
.data
_INT_CONST_59: .word 1
.align 3
.text
ldr x22, _INT_CONST_59
lsl x22, x22, #2
add x21, x21, x22
sub x20, x20, x21
str s19, [x20, #0]
.data
_INT_CONST_60: .word 7
.align 3
.text
ldr x19, _INT_CONST_60
.data
_INT_CONST_61: .word 48
.align 3
.text
ldr x20, _INT_CONST_61
sub x20, x29, x20
mov x21, #0
.data
_INT_CONST_62: .word 2
.align 3
.text
ldr x22, _INT_CONST_62
mul x21, x21, x22
.data
_INT_CONST_63: .word 0
.align 3
.text
ldr x22, _INT_CONST_63
lsl x22, x22, #2
add x21, x21, x22
sub x20, x20, x21
str w19, [x20, #0]
.data
_INT_CONST_64: .word 77
.align 3
.text
ldr x19, _INT_CONST_64
.data
_INT_CONST_65: .word 48
.align 3
.text
ldr x20, _INT_CONST_65
sub x20, x29, x20
mov x21, #0
.data
_INT_CONST_66: .word 2
.align 3
.text
ldr x22, _INT_CONST_66
mul x21, x21, x22
.data
_INT_CONST_67: .word 1
.align 3
.text
ldr x22, _INT_CONST_67
lsl x22, x22, #2
add x21, x21, x22
sub x20, x20, x21
str w19, [x20, #0]
.data
_FLOAT_CONST_12: .float 8.000000
.align 3
.text
ldr s19, _FLOAT_CONST_12
.data
_INT_CONST_68: .word 64
.align 3
.text
ldr x20, _INT_CONST_68
sub x20, x29, x20
mov x21, #0
.data
_INT_CONST_69: .word 2
.align 3
.text
ldr x22, _INT_CONST_69
mul x21, x21, x22
.data
_INT_CONST_70: .word 0
.align 3
.text
ldr x22, _INT_CONST_70
lsl x22, x22, #2
add x21, x21, x22
sub x20, x20, x21
str s19, [x20, #0]
.data
_FLOAT_CONST_13: .float 88.000000
.align 3
.text
ldr s19, _FLOAT_CONST_13
.data
_INT_CONST_71: .word 64
.align 3
.text
ldr x20, _INT_CONST_71
sub x20, x29, x20
mov x21, #0
.data
_INT_CONST_72: .word 2
.align 3
.text
ldr x22, _INT_CONST_72
mul x21, x21, x22
.data
_INT_CONST_73: .word 1
.align 3
.text
ldr x22, _INT_CONST_73
lsl x22, x22, #2
add x21, x21, x22
sub x20, x20, x21
str s19, [x20, #0]
.data
_INT_CONST_74: .word 9
.align 3
.text
ldr x19, _INT_CONST_74
.data
_INT_CONST_75: .word 80
.align 3
.text
ldr x20, _INT_CONST_75
sub x20, x29, x20
mov x21, #0
.data
_INT_CONST_76: .word 2
.align 3
.text
ldr x22, _INT_CONST_76
mul x21, x21, x22
.data
_INT_CONST_77: .word 0
.align 3
.text
ldr x22, _INT_CONST_77
lsl x22, x22, #2
add x21, x21, x22
sub x20, x20, x21
str w19, [x20, #0]
.data
_INT_CONST_78: .word 99
.align 3
.text
ldr x19, _INT_CONST_78
.data
_INT_CONST_79: .word 80
.align 3
.text
ldr x20, _INT_CONST_79
sub x20, x29, x20
mov x21, #0
.data
_INT_CONST_80: .word 2
.align 3
.text
ldr x22, _INT_CONST_80
mul x21, x21, x22
.data
_INT_CONST_81: .word 1
.align 3
.text
ldr x22, _INT_CONST_81
lsl x22, x22, #2
add x21, x21, x22
sub x20, x20, x21
str w19, [x20, #0]
.data
_FLOAT_CONST_14: .float 10.000000
.align 3
.text
ldr s19, _FLOAT_CONST_14
.data
_INT_CONST_82: .word 88
.align 3
.text
ldr x20, _INT_CONST_82
sub x20, x29, x20
mov x21, #0
.data
_INT_CONST_83: .word 2
.align 3
.text
ldr x22, _INT_CONST_83
mul x21, x21, x22
.data
_INT_CONST_84: .word 0
.align 3
.text
ldr x22, _INT_CONST_84
lsl x22, x22, #2
add x21, x21, x22
sub x20, x20, x21
str s19, [x20, #0]
.data
_FLOAT_CONST_15: .float 100.000000
.align 3
.text
ldr s19, _FLOAT_CONST_15
.data
_INT_CONST_85: .word 88
.align 3
.text
ldr x20, _INT_CONST_85
sub x20, x29, x20
mov x21, #0
.data
_INT_CONST_86: .word 2
.align 3
.text
ldr x22, _INT_CONST_86
mul x21, x21, x22
.data
_INT_CONST_87: .word 1
.align 3
.text
ldr x22, _INT_CONST_87
lsl x22, x22, #2
add x21, x21, x22
sub x20, x20, x21
str s19, [x20, #0]
ldr x19, =_g_g1
ldr w19, [x19, #0]
mov w0, w19
bl _write_int
.data
_STR_CONST_0: .asciz "\n"
.align 3
.text
ldr x19, =_STR_CONST_0
mov x0, x19
bl _write_str
ldr x19, =_g_g2
ldr s19, [x19, #0]
fmov s0, s19
bl _write_float
.data
_STR_CONST_1: .asciz "\n"
.align 3
.text
ldr x19, =_STR_CONST_1
mov x0, x19
bl _write_str
ldr x19, =_g_g3
ldr w19, [x19, #0]
mov w0, w19
bl _write_int
.data
_STR_CONST_2: .asciz "\n"
.align 3
.text
ldr x19, =_STR_CONST_2
mov x0, x19
bl _write_str
ldr x19, =_g_g4
ldr s19, [x19, #0]
fmov s0, s19
bl _write_float
.data
_STR_CONST_3: .asciz "\n"
.align 3
.text
ldr x19, =_STR_CONST_3
mov x0, x19
bl _write_str
ldr x19, =_g_g5
mov x20, #0
.data
_INT_CONST_88: .word 2
.align 3
.text
ldr x21, _INT_CONST_88
mul x20, x20, x21
.data
_INT_CONST_89: .word 0
.align 3
.text
ldr x21, _INT_CONST_89
lsl x21, x21, #2
add x20, x20, x21
add x19, x19, x20
ldr w19, [x19, #0]
mov w0, w19
bl _write_int
.data
_STR_CONST_4: .asciz "\n"
.align 3
.text
ldr x19, =_STR_CONST_4
mov x0, x19
bl _write_str
ldr x19, =_g_g5
mov x20, #0
.data
_INT_CONST_90: .word 2
.align 3
.text
ldr x21, _INT_CONST_90
mul x20, x20, x21
.data
_INT_CONST_91: .word 1
.align 3
.text
ldr x21, _INT_CONST_91
lsl x21, x21, #2
add x20, x20, x21
add x19, x19, x20
ldr w19, [x19, #0]
mov w0, w19
bl _write_int
.data
_STR_CONST_5: .asciz "\n"
.align 3
.text
ldr x19, =_STR_CONST_5
mov x0, x19
bl _write_str
ldr x19, =_g_g6
mov x20, #0
.data
_INT_CONST_92: .word 2
.align 3
.text
ldr x21, _INT_CONST_92
mul x20, x20, x21
.data
_INT_CONST_93: .word 0
.align 3
.text
ldr x21, _INT_CONST_93
lsl x21, x21, #2
add x20, x20, x21
add x19, x19, x20
ldr s19, [x19, #0]
fmov s0, s19
bl _write_float
.data
_STR_CONST_6: .asciz "\n"
.align 3
.text
ldr x19, =_STR_CONST_6
mov x0, x19
bl _write_str
ldr x19, =_g_g6
mov x20, #0
.data
_INT_CONST_94: .word 2
.align 3
.text
ldr x21, _INT_CONST_94
mul x20, x20, x21
.data
_INT_CONST_95: .word 1
.align 3
.text
ldr x21, _INT_CONST_95
lsl x21, x21, #2
add x20, x20, x21
add x19, x19, x20
ldr s19, [x19, #0]
fmov s0, s19
bl _write_float
.data
_STR_CONST_7: .asciz "\n"
.align 3
.text
ldr x19, =_STR_CONST_7
mov x0, x19
bl _write_str
ldr x19, =_g_g7
mov x20, #0
.data
_INT_CONST_96: .word 2
.align 3
.text
ldr x21, _INT_CONST_96
mul x20, x20, x21
.data
_INT_CONST_97: .word 0
.align 3
.text
ldr x21, _INT_CONST_97
lsl x21, x21, #2
add x20, x20, x21
add x19, x19, x20
ldr w19, [x19, #0]
mov w0, w19
bl _write_int
.data
_STR_CONST_8: .asciz "\n"
.align 3
.text
ldr x19, =_STR_CONST_8
mov x0, x19
bl _write_str
ldr x19, =_g_g7
mov x20, #0
.data
_INT_CONST_98: .word 2
.align 3
.text
ldr x21, _INT_CONST_98
mul x20, x20, x21
.data
_INT_CONST_99: .word 1
.align 3
.text
ldr x21, _INT_CONST_99
lsl x21, x21, #2
add x20, x20, x21
add x19, x19, x20
ldr w19, [x19, #0]
mov w0, w19
bl _write_int
.data
_STR_CONST_9: .asciz "\n"
.align 3
.text
ldr x19, =_STR_CONST_9
mov x0, x19
bl _write_str
ldr x19, =_g_g8
mov x20, #0
.data
_INT_CONST_100: .word 2
.align 3
.text
ldr x21, _INT_CONST_100
mul x20, x20, x21
.data
_INT_CONST_101: .word 0
.align 3
.text
ldr x21, _INT_CONST_101
lsl x21, x21, #2
add x20, x20, x21
add x19, x19, x20
ldr s19, [x19, #0]
fmov s0, s19
bl _write_float
.data
_STR_CONST_10: .asciz "\n"
.align 3
.text
ldr x19, =_STR_CONST_10
mov x0, x19
bl _write_str
ldr x19, =_g_g8
mov x20, #0
.data
_INT_CONST_102: .word 2
.align 3
.text
ldr x21, _INT_CONST_102
mul x20, x20, x21
.data
_INT_CONST_103: .word 1
.align 3
.text
ldr x21, _INT_CONST_103
lsl x21, x21, #2
add x20, x20, x21
add x19, x19, x20
ldr s19, [x19, #0]
fmov s0, s19
bl _write_float
.data
_STR_CONST_11: .asciz "\n"
.align 3
.text
ldr x19, =_STR_CONST_11
mov x0, x19
bl _write_str
ldr x19, =_g_g9
mov x20, #0
.data
_INT_CONST_104: .word 2
.align 3
.text
ldr x21, _INT_CONST_104
mul x20, x20, x21
.data
_INT_CONST_105: .word 0
.align 3
.text
ldr x21, _INT_CONST_105
lsl x21, x21, #2
add x20, x20, x21
add x19, x19, x20
ldr w19, [x19, #0]
mov w0, w19
bl _write_int
.data
_STR_CONST_12: .asciz "\n"
.align 3
.text
ldr x19, =_STR_CONST_12
mov x0, x19
bl _write_str
ldr x19, =_g_g9
mov x20, #0
.data
_INT_CONST_106: .word 2
.align 3
.text
ldr x21, _INT_CONST_106
mul x20, x20, x21
.data
_INT_CONST_107: .word 1
.align 3
.text
ldr x21, _INT_CONST_107
lsl x21, x21, #2
add x20, x20, x21
add x19, x19, x20
ldr w19, [x19, #0]
mov w0, w19
bl _write_int
.data
_STR_CONST_13: .asciz "\n"
.align 3
.text
ldr x19, =_STR_CONST_13
mov x0, x19
bl _write_str
ldr x19, =_g_g10
mov x20, #0
.data
_INT_CONST_108: .word 2
.align 3
.text
ldr x21, _INT_CONST_108
mul x20, x20, x21
.data
_INT_CONST_109: .word 0
.align 3
.text
ldr x21, _INT_CONST_109
lsl x21, x21, #2
add x20, x20, x21
add x19, x19, x20
ldr s19, [x19, #0]
fmov s0, s19
bl _write_float
.data
_STR_CONST_14: .asciz "\n"
.align 3
.text
ldr x19, =_STR_CONST_14
mov x0, x19
bl _write_str
ldr x19, =_g_g10
mov x20, #0
.data
_INT_CONST_110: .word 2
.align 3
.text
ldr x21, _INT_CONST_110
mul x20, x20, x21
.data
_INT_CONST_111: .word 1
.align 3
.text
ldr x21, _INT_CONST_111
lsl x21, x21, #2
add x20, x20, x21
add x19, x19, x20
ldr s19, [x19, #0]
fmov s0, s19
bl _write_float
.data
_STR_CONST_15: .asciz "\n"
.align 3
.text
ldr x19, =_STR_CONST_15
mov x0, x19
bl _write_str
.data
_INT_CONST_112: .word 0
.align 3
.text
ldr x19, _INT_CONST_112
sub x19, x29, x19
ldr w19, [x19, #0]
mov w0, w19
bl _write_int
.data
_STR_CONST_16: .asciz "\n"
.align 3
.text
ldr x19, =_STR_CONST_16
mov x0, x19
bl _write_str
.data
_INT_CONST_113: .word 4
.align 3
.text
ldr x19, _INT_CONST_113
sub x19, x29, x19
ldr s19, [x19, #0]
fmov s0, s19
bl _write_float
.data
_STR_CONST_17: .asciz "\n"
.align 3
.text
ldr x19, =_STR_CONST_17
mov x0, x19
bl _write_str
.data
_INT_CONST_114: .word 8
.align 3
.text
ldr x19, _INT_CONST_114
sub x19, x29, x19
ldr w19, [x19, #0]
mov w0, w19
bl _write_int
.data
_STR_CONST_18: .asciz "\n"
.align 3
.text
ldr x19, =_STR_CONST_18
mov x0, x19
bl _write_str
.data
_INT_CONST_115: .word 12
.align 3
.text
ldr x19, _INT_CONST_115
sub x19, x29, x19
ldr s19, [x19, #0]
fmov s0, s19
bl _write_float
.data
_STR_CONST_19: .asciz "\n"
.align 3
.text
ldr x19, =_STR_CONST_19
mov x0, x19
bl _write_str
.data
_INT_CONST_116: .word 16
.align 3
.text
ldr x19, _INT_CONST_116
sub x19, x29, x19
mov x20, #0
.data
_INT_CONST_117: .word 2
.align 3
.text
ldr x21, _INT_CONST_117
mul x20, x20, x21
.data
_INT_CONST_118: .word 0
.align 3
.text
ldr x21, _INT_CONST_118
lsl x21, x21, #2
add x20, x20, x21
sub x19, x19, x20
ldr w19, [x19, #0]
mov w0, w19
bl _write_int
.data
_STR_CONST_20: .asciz "\n"
.align 3
.text
ldr x19, =_STR_CONST_20
mov x0, x19
bl _write_str
.data
_INT_CONST_119: .word 16
.align 3
.text
ldr x19, _INT_CONST_119
sub x19, x29, x19
mov x20, #0
.data
_INT_CONST_120: .word 2
.align 3
.text
ldr x21, _INT_CONST_120
mul x20, x20, x21
.data
_INT_CONST_121: .word 1
.align 3
.text
ldr x21, _INT_CONST_121
lsl x21, x21, #2
add x20, x20, x21
sub x19, x19, x20
ldr w19, [x19, #0]
mov w0, w19
bl _write_int
.data
_STR_CONST_21: .asciz "\n"
.align 3
.text
ldr x19, =_STR_CONST_21
mov x0, x19
bl _write_str
.data
_INT_CONST_122: .word 32
.align 3
.text
ldr x19, _INT_CONST_122
sub x19, x29, x19
mov x20, #0
.data
_INT_CONST_123: .word 2
.align 3
.text
ldr x21, _INT_CONST_123
mul x20, x20, x21
.data
_INT_CONST_124: .word 0
.align 3
.text
ldr x21, _INT_CONST_124
lsl x21, x21, #2
add x20, x20, x21
sub x19, x19, x20
ldr s19, [x19, #0]
fmov s0, s19
bl _write_float
.data
_STR_CONST_22: .asciz "\n"
.align 3
.text
ldr x19, =_STR_CONST_22
mov x0, x19
bl _write_str
.data
_INT_CONST_125: .word 32
.align 3
.text
ldr x19, _INT_CONST_125
sub x19, x29, x19
mov x20, #0
.data
_INT_CONST_126: .word 2
.align 3
.text
ldr x21, _INT_CONST_126
mul x20, x20, x21
.data
_INT_CONST_127: .word 1
.align 3
.text
ldr x21, _INT_CONST_127
lsl x21, x21, #2
add x20, x20, x21
sub x19, x19, x20
ldr s19, [x19, #0]
fmov s0, s19
bl _write_float
.data
_STR_CONST_23: .asciz "\n"
.align 3
.text
ldr x19, =_STR_CONST_23
mov x0, x19
bl _write_str
.data
_INT_CONST_128: .word 48
.align 3
.text
ldr x19, _INT_CONST_128
sub x19, x29, x19
mov x20, #0
.data
_INT_CONST_129: .word 2
.align 3
.text
ldr x21, _INT_CONST_129
mul x20, x20, x21
.data
_INT_CONST_130: .word 0
.align 3
.text
ldr x21, _INT_CONST_130
lsl x21, x21, #2
add x20, x20, x21
sub x19, x19, x20
ldr w19, [x19, #0]
mov w0, w19
bl _write_int
.data
_STR_CONST_24: .asciz "\n"
.align 3
.text
ldr x19, =_STR_CONST_24
mov x0, x19
bl _write_str
.data
_INT_CONST_131: .word 48
.align 3
.text
ldr x19, _INT_CONST_131
sub x19, x29, x19
mov x20, #0
.data
_INT_CONST_132: .word 2
.align 3
.text
ldr x21, _INT_CONST_132
mul x20, x20, x21
.data
_INT_CONST_133: .word 1
.align 3
.text
ldr x21, _INT_CONST_133
lsl x21, x21, #2
add x20, x20, x21
sub x19, x19, x20
ldr w19, [x19, #0]
mov w0, w19
bl _write_int
.data
_STR_CONST_25: .asciz "\n"
.align 3
.text
ldr x19, =_STR_CONST_25
mov x0, x19
bl _write_str
.data
_INT_CONST_134: .word 64
.align 3
.text
ldr x19, _INT_CONST_134
sub x19, x29, x19
mov x20, #0
.data
_INT_CONST_135: .word 2
.align 3
.text
ldr x21, _INT_CONST_135
mul x20, x20, x21
.data
_INT_CONST_136: .word 0
.align 3
.text
ldr x21, _INT_CONST_136
lsl x21, x21, #2
add x20, x20, x21
sub x19, x19, x20
ldr s19, [x19, #0]
fmov s0, s19
bl _write_float
.data
_STR_CONST_26: .asciz "\n"
.align 3
.text
ldr x19, =_STR_CONST_26
mov x0, x19
bl _write_str
.data
_INT_CONST_137: .word 64
.align 3
.text
ldr x19, _INT_CONST_137
sub x19, x29, x19
mov x20, #0
.data
_INT_CONST_138: .word 2
.align 3
.text
ldr x21, _INT_CONST_138
mul x20, x20, x21
.data
_INT_CONST_139: .word 1
.align 3
.text
ldr x21, _INT_CONST_139
lsl x21, x21, #2
add x20, x20, x21
sub x19, x19, x20
ldr s19, [x19, #0]
fmov s0, s19
bl _write_float
.data
_STR_CONST_27: .asciz "\n"
.align 3
.text
ldr x19, =_STR_CONST_27
mov x0, x19
bl _write_str
.data
_INT_CONST_140: .word 80
.align 3
.text
ldr x19, _INT_CONST_140
sub x19, x29, x19
mov x20, #0
.data
_INT_CONST_141: .word 2
.align 3
.text
ldr x21, _INT_CONST_141
mul x20, x20, x21
.data
_INT_CONST_142: .word 0
.align 3
.text
ldr x21, _INT_CONST_142
lsl x21, x21, #2
add x20, x20, x21
sub x19, x19, x20
ldr w19, [x19, #0]
mov w0, w19
bl _write_int
.data
_STR_CONST_28: .asciz "\n"
.align 3
.text
ldr x19, =_STR_CONST_28
mov x0, x19
bl _write_str
.data
_INT_CONST_143: .word 80
.align 3
.text
ldr x19, _INT_CONST_143
sub x19, x29, x19
mov x20, #0
.data
_INT_CONST_144: .word 2
.align 3
.text
ldr x21, _INT_CONST_144
mul x20, x20, x21
.data
_INT_CONST_145: .word 1
.align 3
.text
ldr x21, _INT_CONST_145
lsl x21, x21, #2
add x20, x20, x21
sub x19, x19, x20
ldr w19, [x19, #0]
mov w0, w19
bl _write_int
.data
_STR_CONST_29: .asciz "\n"
.align 3
.text
ldr x19, =_STR_CONST_29
mov x0, x19
bl _write_str
.data
_INT_CONST_146: .word 88
.align 3
.text
ldr x19, _INT_CONST_146
sub x19, x29, x19
mov x20, #0
.data
_INT_CONST_147: .word 2
.align 3
.text
ldr x21, _INT_CONST_147
mul x20, x20, x21
.data
_INT_CONST_148: .word 0
.align 3
.text
ldr x21, _INT_CONST_148
lsl x21, x21, #2
add x20, x20, x21
sub x19, x19, x20
ldr s19, [x19, #0]
fmov s0, s19
bl _write_float
.data
_STR_CONST_30: .asciz "\n"
.align 3
.text
ldr x19, =_STR_CONST_30
mov x0, x19
bl _write_str
.data
_INT_CONST_149: .word 88
.align 3
.text
ldr x19, _INT_CONST_149
sub x19, x29, x19
mov x20, #0
.data
_INT_CONST_150: .word 2
.align 3
.text
ldr x21, _INT_CONST_150
mul x20, x20, x21
.data
_INT_CONST_151: .word 1
.align 3
.text
ldr x21, _INT_CONST_151
lsl x21, x21, #2
add x20, x20, x21
sub x19, x19, x20
ldr s19, [x19, #0]
fmov s0, s19
bl _write_float
.data
_STR_CONST_31: .asciz "\n"
.align 3
.text
ldr x19, =_STR_CONST_31
mov x0, x19
bl _write_str
.data
_INT_CONST_152: .word 0
.align 3
.text
ldr x19, _INT_CONST_152
mov w0, w19
add sp, x29, #112
ldr x29, [x29, #8]
ldr x28, [x29, #16]
ldr x27, [x29, #24]
ldr x26, [x29, #32]
ldr x25, [x29, #40]
ldr x24, [x29, #48]
ldr x23, [x29, #56]
ldr x22, [x29, #64]
ldr x21, [x29, #72]
ldr x20, [x29, #80]
ldr x19, [x29, #88]
ldr x30, [sp, #-8]
ldr x29, [sp, #-16]
ret x30
