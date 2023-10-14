[org 0x7c00]
OS_OFFSET equ 0x1000

[bits 16]
.bpb: ;dummy BIOS Parameter Block (real hardware needs this to recognize this as bootable) 
    jmp short begin
    nop ;needed for padding
    .oem_id: db "MakeOS  " ;very important that this is 8 bytes
    .sector_size: dw 512
    .sect_per_cluster: db 0
    .reserved_sectors: dw 0
    .FATs: db 0
    .roots: dw 0
    .vol_sectors: dw 0
    .mdt: db 0
    .sect_per_FAT: dw 0
    .sect_per_track: dw 32
    .heads: dw 2
    .hidden: dd 0
    .large_count: dd 0

    ; begin EBPB
    .drive_num: db 0
    .reserved: db 0
    .signature: db 0
    .volume_id: dd 0
    .volume_label: db "MakeOpSys  "


[bits 16]
begin:
    cli
    mov [BOOT_DRIVE], dl
    mov bp, 0x9000
    mov sp, bp
    jmp load_kernel

%include "src/boot/gdt.asm"
%include "src/boot/enter_pm.asm"

[bits 16]
load_kernel:
    mov ah, 0x0e
    mov al, 'H'
    int 0x10
    mov al, 'e'
    int 0x10
    mov al, 'l'
    int 0x10
    mov al, 'l'
    int 0x10
    mov al, 'o'
    int 0x10

    mov ah, 2 ;read BIOS chs
    mov al, 20 ;sectors to read
    mov cl, 0x02 ;start at sector 2
    mov ch, 0x00 ;cylinder
    mov dh, 0x00 ;head
    mov bx, OS_OFFSET
    int 0x13 ;do read

    jc err

    call enter_pm

[bits 16]
err:
    mov ah, 0x0e
    mov al, ' '
    int 0x10
    mov al, ':'
    int 0x10
    mov al, '('
    int 0x10
    hlt

[bits 32]
begin_pm:
    call OS_OFFSET
    hlt

times 435 - ($ - $$) db 0 ;padding
BOOT_DRIVE db 0 ; @TODO calc this

UID times 10 db 0

db 0x80 ;set partition 1 to active
db 0 ;
db 1 ;
db 0 ;
db 0 ;partition type
db 0 ;last head
db 21 ;last sector
db 0 ;last cylinder
dd 0 ;lba 0
dd 21 ;so many sectors

PT2 times 16 db 0
PT3 times 16 db 0
PT4 times 16 db 0

dw 0xaa55 ;magic boot sector number