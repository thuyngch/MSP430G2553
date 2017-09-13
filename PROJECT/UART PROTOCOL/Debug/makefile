################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := C:/ti/ccsv6/tools/compiler/ti-cgt-msp430_4.4.7

GEN_OPTS__FLAG := 
GEN_CMDS__FLAG := 

ORDERED_OBJS += \
"./Register-Based Files/CLOCK_1_0_1.obj" \
"./Register-Based Files/ESP8266_1_0_1.obj" \
"./Register-Based Files/GPIO_1_0_1.obj" \
"./Register-Based Files/TIMERA_1_0_1.obj" \
"./Register-Based Files/USCI_UART_1_0_1.obj" \
"./Register-Based Files/WATCHDOG_1_0_1.obj" \
"./Firmware-Based Files/CHIP01/Communication01.obj" \
"./Firmware-Based Files/CHIP01/MAIN01.obj" \
"./Firmware-Based Files/CHIP00/Communication00.obj" \
"./Firmware-Based Files/CHIP00/Firmware00.obj" \
"./Firmware-Based Files/CHIP00/MAIN00.obj" \
"./Firmware-Based Files/CHIP00/Wifi00.obj" \
"../lnk_msp430g2553.cmd" \
$(GEN_CMDS__FLAG) \
-l"libc.a" \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include Register-Based\ Files/subdir_vars.mk
-include Firmware-Based\ Files/CHIP01/subdir_vars.mk
-include Firmware-Based\ Files/CHIP00/subdir_vars.mk
-include subdir_rules.mk
-include Register-Based\ Files/subdir_rules.mk
-include Firmware-Based\ Files/CHIP01/subdir_rules.mk
-include Firmware-Based\ Files/CHIP00/subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
UART\ PROTOCOL.out \

EXE_OUTPUTS__QUOTED += \
"UART PROTOCOL.out" \

BIN_OUTPUTS += \
UART\ PROTOCOL.hex \

BIN_OUTPUTS__QUOTED += \
"UART PROTOCOL.hex" \


# All Target
all: UART\ PROTOCOL.out

# Tool invocations
UART\ PROTOCOL.out: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@echo 'Building target: $@'
	@echo 'Invoking: MSP430 Linker'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-msp430_4.4.7/bin/cl430" -vmsp --abi=eabi --use_hw_mpy=none --advice:power=all -g --define=__MSP430G2553__ --display_error_number --diag_warning=225 --diag_wrap=off --printf_support=minimal -z -m"UART PROTOCOL.map" --stack_size=80 --heap_size=80 -i"C:/ti/ccsv6/ccs_base/msp430/include" -i"C:/ti/ccsv6/tools/compiler/ti-cgt-msp430_4.4.7/lib" -i"C:/ti/ccsv6/tools/compiler/ti-cgt-msp430_4.4.7/include" --reread_libs --diag_wrap=off --display_error_number --warn_sections --xml_link_info="UART PROTOCOL_linkInfo.xml" --use_hw_mpy=none --rom_model -o "UART PROTOCOL.out" $(ORDERED_OBJS)
	@echo 'Finished building target: $@'
	@echo ' '

UART\ PROTOCOL.hex: $(EXE_OUTPUTS)
	@echo 'Invoking: MSP430 Hex Utility'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-msp430_4.4.7/bin/hex430" --memwidth=8 --romwidth=8 -o "UART PROTOCOL.hex" $(EXE_OUTPUTS__QUOTED)
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXE_OUTPUTS__QUOTED)$(BIN_OUTPUTS__QUOTED)
	-$(RM) "Register-Based Files\CLOCK_1_0_1.pp" "Register-Based Files\ESP8266_1_0_1.pp" "Register-Based Files\GPIO_1_0_1.pp" "Register-Based Files\TIMERA_1_0_1.pp" "Register-Based Files\USCI_UART_1_0_1.pp" "Register-Based Files\WATCHDOG_1_0_1.pp" "Firmware-Based Files\CHIP01\Communication01.pp" "Firmware-Based Files\CHIP01\MAIN01.pp" "Firmware-Based Files\CHIP00\Communication00.pp" "Firmware-Based Files\CHIP00\Firmware00.pp" "Firmware-Based Files\CHIP00\MAIN00.pp" "Firmware-Based Files\CHIP00\Wifi00.pp" 
	-$(RM) "Register-Based Files\CLOCK_1_0_1.obj" "Register-Based Files\ESP8266_1_0_1.obj" "Register-Based Files\GPIO_1_0_1.obj" "Register-Based Files\TIMERA_1_0_1.obj" "Register-Based Files\USCI_UART_1_0_1.obj" "Register-Based Files\WATCHDOG_1_0_1.obj" "Firmware-Based Files\CHIP01\Communication01.obj" "Firmware-Based Files\CHIP01\MAIN01.obj" "Firmware-Based Files\CHIP00\Communication00.obj" "Firmware-Based Files\CHIP00\Firmware00.obj" "Firmware-Based Files\CHIP00\MAIN00.obj" "Firmware-Based Files\CHIP00\Wifi00.obj" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

