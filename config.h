#ifndef CONFIG_H
#define CONFIG_H

#define SW_VER			"v00.01.00" // BL VERSION
#define SYSTICK			100 // every 10ms
#define UPG_FILE		"/update/fw.bin"
#define APP_ADDR		0x00004000 // location of jump to SystemInit at 0x40D4, need to set bit[0] = 1 for BLX 

//
// boot.txt strings
//

#define BOOT_TXT_S0 "+OK bootloader " SW_VER " loaded application successfully\r\n"
#define BOOT_TXT_S1 "+OK bootloader " SW_VER " upgraded application successfully using" UPG_FILE "\r\n"
#define BOOT_TXT_S2 "+ERR bootloader " SW_VER " had problems applying " UPG_FILE "\r\n"

#endif
