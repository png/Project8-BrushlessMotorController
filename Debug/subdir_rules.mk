################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: GNU Compiler'
	"C:/ti/ccs910/ccs/tools/compiler/msp430-gcc-8.2.0.52_win32/bin/msp430-elf-gcc-8.2.0.exe" -c -mmcu=msp430g2553 -mhwmult=none -I"C:/ti/ccs910/ccs/ccs_base/msp430/include_gcc" -I"C:/Users/Durendal/Documents/ECE3430/Project8Git" -I"C:/ti/ccs910/ccs/tools/compiler/msp430-gcc-8.2.0.52_win32/msp430-elf/include" -Og -g -gdwarf-3 -gstrict-dwarf -Wall -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


