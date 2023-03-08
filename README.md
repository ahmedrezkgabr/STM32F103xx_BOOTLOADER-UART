# STM32F103xx_BOOTLOADER-UART

this is a bootloader for stm32f103xx microcontroller
to use this bootloader you should modify your application's linker script to make flash starts 4KBytes after the recet vector for your MCU and make the size of the flash less with 4KBytes
