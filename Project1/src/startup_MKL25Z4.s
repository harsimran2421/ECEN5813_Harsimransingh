# 1 "startup_MKL25Z4.S"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "startup_MKL25Z4.S"
# 40 "startup_MKL25Z4.S"
    .syntax unified
    .arch armv6-m

    .section .isr_vector, "a"
    .align 2
    .globl __isr_vector
__isr_vector:
    .long __StackTop
    .long Reset_Handler
    .long NMI_Handler
    .long HardFault_Handler
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long SVC_Handler
    .long 0
    .long 0
    .long PendSV_Handler
    .long SysTick_Handler


    .long DMA0_IRQHandler
    .long DMA1_IRQHandler
    .long DMA2_IRQHandler
    .long DMA3_IRQHandler
    .long Reserved20_IRQHandler
    .long FTFA_IRQHandler
    .long LVD_LVW_IRQHandler
    .long LLWU_IRQHandler
    .long I2C0_IRQHandler
    .long I2C1_IRQHandler
    .long SPI0_IRQHandler
    .long SPI1_IRQHandler
    .long UART0_IRQHandler
    .long UART1_IRQHandler
    .long UART2_IRQHandler
    .long ADC0_IRQHandler
    .long CMP0_IRQHandler
    .long TPM0_IRQHandler
    .long TPM1_IRQHandler
    .long TPM2_IRQHandler
    .long RTC_IRQHandler
    .long RTC_Seconds_IRQHandler
    .long PIT_IRQHandler
    .long Reserved39_IRQHandler
    .long USB0_IRQHandler
    .long DAC0_IRQHandler
    .long TSI0_IRQHandler
    .long MCG_IRQHandler
    .long LPTMR0_IRQHandler
    .long Reserved45_IRQHandler
    .long PORTA_IRQHandler
    .long PORTD_IRQHandler

    .size __isr_vector, . - __isr_vector


    .section .FlashConfig, "a"
    .long 0xFFFFFFFF
    .long 0xFFFFFFFF
    .long 0xFFFFFFFF
    .long 0xFFFFFFFE

    .text
    .thumb



    .thumb_func
    .align 2
    .globl Reset_Handler
    .weak Reset_Handler
    .type Reset_Handler, %function
Reset_Handler:
    cpsid i

    bl SystemInit

    cpsie i







    ldr r1, =__etext
    ldr r2, =__data_start__
    ldr r3, =__data_end__

    subs r3, r2
    ble .LC0

.LC1:
    subs r3, 4
    ldr r0, [r1,r3]
    str r0, [r2,r3]
    bgt .LC1
.LC0:
# 169 "startup_MKL25Z4.S"
    bl _start
    .pool
    .size Reset_Handler, . - Reset_Handler

    .align 1
    .thumb_func
    .weak DefaultISR
    .type DefaultISR, %function
DefaultISR:
    ldr r0, =DefaultISR
    bx r0
    .size DefaultISR, . - DefaultISR




    .macro def_irq_handler handler_name
    .weak \handler_name
    .set \handler_name, DefaultISR
    .endm


    def_irq_handler NMI_Handler
    def_irq_handler HardFault_Handler
    def_irq_handler SVC_Handler
    def_irq_handler PendSV_Handler
    def_irq_handler SysTick_Handler
    def_irq_handler DMA0_IRQHandler
    def_irq_handler DMA1_IRQHandler
    def_irq_handler DMA2_IRQHandler
    def_irq_handler DMA3_IRQHandler
    def_irq_handler Reserved20_IRQHandler
    def_irq_handler FTFA_IRQHandler
    def_irq_handler LVD_LVW_IRQHandler
    def_irq_handler LLWU_IRQHandler
    def_irq_handler I2C0_IRQHandler
    def_irq_handler I2C1_IRQHandler
    def_irq_handler SPI0_IRQHandler
    def_irq_handler SPI1_IRQHandler
    def_irq_handler UART0_IRQHandler
    def_irq_handler UART1_IRQHandler
    def_irq_handler UART2_IRQHandler
    def_irq_handler ADC0_IRQHandler
    def_irq_handler CMP0_IRQHandler
    def_irq_handler TPM0_IRQHandler
    def_irq_handler TPM1_IRQHandler
    def_irq_handler TPM2_IRQHandler
    def_irq_handler RTC_IRQHandler
    def_irq_handler RTC_Seconds_IRQHandler
    def_irq_handler PIT_IRQHandler
    def_irq_handler Reserved39_IRQHandler
    def_irq_handler USB0_IRQHandler
    def_irq_handler DAC0_IRQHandler
    def_irq_handler TSI0_IRQHandler
    def_irq_handler MCG_IRQHandler
    def_irq_handler LPTMR0_IRQHandler
    def_irq_handler Reserved45_IRQHandler
    def_irq_handler PORTA_IRQHandler
    def_irq_handler PORTD_IRQHandler

    .end
