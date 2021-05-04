################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/Buzzer_Timer.c \
../source/CBFIFO.c \
../source/Indication_Led.c \
../source/LFSR_Random.c \
../source/Locker_Keypad.c \
../source/MMA8451Q_I2C.c \
../source/MMA84541Q.c \
../source/Password_Process.c \
../source/System.c \
../source/Test_LFSR.c \
../source/Test_Password_Generation.c \
../source/UART.c \
../source/User_Input.c \
../source/main_fsm.c \
../source/mtb.c \
../source/semihost_hardfault.c \
../source/sysclock.c \
../source/systick.c \
../source/test_cbfifo.c 

OBJS += \
./source/Buzzer_Timer.o \
./source/CBFIFO.o \
./source/Indication_Led.o \
./source/LFSR_Random.o \
./source/Locker_Keypad.o \
./source/MMA8451Q_I2C.o \
./source/MMA84541Q.o \
./source/Password_Process.o \
./source/System.o \
./source/Test_LFSR.o \
./source/Test_Password_Generation.o \
./source/UART.o \
./source/User_Input.o \
./source/main_fsm.o \
./source/mtb.o \
./source/semihost_hardfault.o \
./source/sysclock.o \
./source/systick.o \
./source/test_cbfifo.o 

C_DEPS += \
./source/Buzzer_Timer.d \
./source/CBFIFO.d \
./source/Indication_Led.d \
./source/LFSR_Random.d \
./source/Locker_Keypad.d \
./source/MMA8451Q_I2C.d \
./source/MMA84541Q.d \
./source/Password_Process.d \
./source/System.d \
./source/Test_LFSR.d \
./source/Test_Password_Generation.d \
./source/UART.d \
./source/User_Input.d \
./source/main_fsm.d \
./source/mtb.d \
./source/semihost_hardfault.d \
./source/sysclock.d \
./source/systick.d \
./source/test_cbfifo.d 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DCPU_MKL25Z128VLK4 -DCPU_MKL25Z128VLK4_cm0plus -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -D__REDLIB__ -DSDK_DEBUGCONSOLE=1 -I"C:\Users\Shrikant\Documents\MCUXpressoIDE_11.3.0_5222\workspace\PES_Final_Project_V1.0\board" -I"C:\Users\Shrikant\Documents\MCUXpressoIDE_11.3.0_5222\workspace\PES_Final_Project_V1.0\source" -I"C:\Users\Shrikant\Documents\MCUXpressoIDE_11.3.0_5222\workspace\PES_Final_Project_V1.0" -I"C:\Users\Shrikant\Documents\MCUXpressoIDE_11.3.0_5222\workspace\PES_Final_Project_V1.0\startup" -I"C:\Users\Shrikant\Documents\MCUXpressoIDE_11.3.0_5222\workspace\PES_Final_Project_V1.0\CMSIS" -I"C:\Users\Shrikant\Documents\MCUXpressoIDE_11.3.0_5222\workspace\PES_Final_Project_V1.0\drivers" -I"C:\Users\Shrikant\Documents\MCUXpressoIDE_11.3.0_5222\workspace\PES_Final_Project_V1.0\utilities" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


