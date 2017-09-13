################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
Firmware-Based\ Files/CHIP01/Communication01.obj: ../Firmware-Based\ Files/CHIP01/Communication01.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-msp430_4.4.7/bin/cl430" -vmsp --abi=eabi --use_hw_mpy=none --include_path="C:/ti/ccsv6/ccs_base/msp430/include" --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-msp430_4.4.7/include" --include_path="C:/Users/Chinh Thuy/Google Drive/WORKSPACE/CCS WORKSPACE/MSP430G2553/LIBRARY" --advice:power=all -g --define=__MSP430G2553__ --display_error_number --diag_warning=225 --diag_wrap=off --printf_support=minimal --preproc_with_compile --preproc_dependency="Firmware-Based Files/CHIP01/Communication01.pp" --obj_directory="Firmware-Based Files/CHIP01" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

Firmware-Based\ Files/CHIP01/MAIN01.obj: ../Firmware-Based\ Files/CHIP01/MAIN01.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-msp430_4.4.7/bin/cl430" -vmsp --abi=eabi --use_hw_mpy=none --include_path="C:/ti/ccsv6/ccs_base/msp430/include" --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-msp430_4.4.7/include" --include_path="C:/Users/Chinh Thuy/Google Drive/WORKSPACE/CCS WORKSPACE/MSP430G2553/LIBRARY" --advice:power=all -g --define=__MSP430G2553__ --display_error_number --diag_warning=225 --diag_wrap=off --printf_support=minimal --preproc_with_compile --preproc_dependency="Firmware-Based Files/CHIP01/MAIN01.pp" --obj_directory="Firmware-Based Files/CHIP01" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


