/*
*
*   Note:
*   -- main bios interrupt codes --
*   Int 13/AH=00h - DISK - RESET DISK SYSTEM
*   Int 13/AH=01h - DISK - GET STATUS OF LAST OPERATION
*   Int 13/AH=02h - DISK - READ SECTOR(S) INTO MEMORY
*   Int 13/AH=03h - DISK - WRITE DISK SECTOR(S)
*   Int 13/AH=04h - DISK - VERIFY DISK SECTOR(S)
*   Int 13/AH=05h - FIXED DISK - FORMAT TRACK
*   Int 13/AH=07h - FIXED DISK - FORMAT DRIVE STARTING AT GIVEN TRACK (XT,PORT)
*   Int 13/AH=08h - DISK - GET DRIVE PARAMETERS (PC,XT286,CONV,PS,ESDI,SCSI)
*
*   https://wiki.osdev.org/BIOS             - osdev wiki BIOS documentation
*   http://www.ctyme.com/intr/int-13.htm    - all BIOS interrupt codes
*   
*   the BIOS functions are organized by interrupt number:
*   INT 0x10 = Video display functions (including VESA/VBE)
*   INT 0x13 = mass storage (disk, floppy) access
*   INT 0x15 = memory size functions
*   INT 0x16 = keyboard functions
*
*/