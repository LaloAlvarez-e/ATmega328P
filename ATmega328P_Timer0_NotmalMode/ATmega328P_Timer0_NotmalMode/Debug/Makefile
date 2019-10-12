################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL := cmd.exe
RM := rm -rf

USER_OBJS :=

LIBS := 
PROJ := 

O_SRCS := 
C_SRCS := 
S_SRCS := 
S_UPPER_SRCS := 
OBJ_SRCS := 
ASM_SRCS := 
PREPROCESSING_SRCS := 
OBJS := 
OBJS_AS_ARGS := 
C_DEPS := 
C_DEPS_AS_ARGS := 
EXECUTABLES := 
OUTPUT_FILE_PATH :=
OUTPUT_FILE_PATH_AS_ARGS :=
AVR_APP_PATH :=$$$AVR_APP_PATH$$$
QUOTE := "
ADDITIONAL_DEPENDENCIES:=
OUTPUT_FILE_DEP:=
LIB_DEP:=
LINKER_SCRIPT_DEP:=

# Every subdirectory with source files must be described here
SUBDIRS :=  \
../Driver_header \
../APP_header \
../APP_source \
../Driver_source/


# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS +=  \
../APP_source/main.c \
../Driver_source/GPIO.c \
../Driver_source/Timer0.c


PREPROCESSING_SRCS += 


ASM_SRCS += 


OBJS +=  \
APP_source/main.o \
Driver_source/GPIO.o \
Driver_source/Timer0.o

OBJS_AS_ARGS +=  \
APP_source/main.o \
Driver_source/GPIO.o \
Driver_source/Timer0.o

C_DEPS +=  \
APP_source/main.d \
Driver_source/GPIO.d \
Driver_source/Timer0.d

C_DEPS_AS_ARGS +=  \
APP_source/main.d \
Driver_source/GPIO.d \
Driver_source/Timer0.d

OUTPUT_FILE_PATH +=ATmega328P_Timer0_NotmalMode.elf

OUTPUT_FILE_PATH_AS_ARGS +=ATmega328P_Timer0_NotmalMode.elf

ADDITIONAL_DEPENDENCIES:=

OUTPUT_FILE_DEP:= ./makedep.mk

LIB_DEP+= 

LINKER_SCRIPT_DEP+= 


# AVR32/GNU C Compiler
APP_source/main.o: ../APP_source/main.c
	@echo Building file: $<
	@echo Invoking: AVR/GNU C Compiler : 5.4.0
	$(QUOTE)C:\Tools\IDE\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-gcc.exe$(QUOTE)  -x c -funsigned-char -funsigned-bitfields -DDEBUG  -I"C:\Tools\IDE\Atmel\Studio\7.0\Packs\atmel\ATmega_DFP\1.3.300\include" -I"../Driver_header" -I"../APP_header"  -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -g2 -Wall -mmcu=atmega328p -B "C:\Tools\IDE\Atmel\Studio\7.0\Packs\atmel\ATmega_DFP\1.3.300\gcc\dev\atmega328p" -c -std=gnu99 -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
	@echo Finished building: $<
	

Driver_source/GPIO.o: ../Driver_source/GPIO.c
	@echo Building file: $<
	@echo Invoking: AVR/GNU C Compiler : 5.4.0
	$(QUOTE)C:\Tools\IDE\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-gcc.exe$(QUOTE)  -x c -funsigned-char -funsigned-bitfields -DDEBUG  -I"C:\Tools\IDE\Atmel\Studio\7.0\Packs\atmel\ATmega_DFP\1.3.300\include" -I"../Driver_header" -I"../APP_header"  -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -g2 -Wall -mmcu=atmega328p -B "C:\Tools\IDE\Atmel\Studio\7.0\Packs\atmel\ATmega_DFP\1.3.300\gcc\dev\atmega328p" -c -std=gnu99 -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
	@echo Finished building: $<
	

Driver_source/Timer0.o: ../Driver_source/Timer0.c
	@echo Building file: $<
	@echo Invoking: AVR/GNU C Compiler : 5.4.0
	$(QUOTE)C:\Tools\IDE\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-gcc.exe$(QUOTE)  -x c -funsigned-char -funsigned-bitfields -DDEBUG  -I"C:\Tools\IDE\Atmel\Studio\7.0\Packs\atmel\ATmega_DFP\1.3.300\include" -I"../Driver_header" -I"../APP_header"  -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -g2 -Wall -mmcu=atmega328p -B "C:\Tools\IDE\Atmel\Studio\7.0\Packs\atmel\ATmega_DFP\1.3.300\gcc\dev\atmega328p" -c -std=gnu99 -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
	@echo Finished building: $<
	




# AVR32/GNU Preprocessing Assembler



# AVR32/GNU Assembler




ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: $(OUTPUT_FILE_PATH) $(ADDITIONAL_DEPENDENCIES)

$(OUTPUT_FILE_PATH): $(OBJS) $(USER_OBJS) $(OUTPUT_FILE_DEP) $(LIB_DEP) $(LINKER_SCRIPT_DEP)
	@echo Building target: $@
	@echo Invoking: AVR/GNU Linker : 5.4.0
	$(QUOTE)C:\Tools\IDE\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-gcc.exe$(QUOTE) -o$(OUTPUT_FILE_PATH_AS_ARGS) $(OBJS_AS_ARGS) $(USER_OBJS) $(LIBS) -Wl,-Map="ATmega328P_Timer0_NotmalMode.map" -Wl,--start-group -Wl,-lm  -Wl,--end-group -Wl,--gc-sections -mmcu=atmega328p -B "C:\Tools\IDE\Atmel\Studio\7.0\Packs\atmel\ATmega_DFP\1.3.300\gcc\dev\atmega328p"  
	@echo Finished building target: $@
	"C:\Tools\IDE\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-objcopy.exe" -O ihex -R .eeprom -R .fuse -R .lock -R .signature -R .user_signatures  "ATmega328P_Timer0_NotmalMode.elf" "ATmega328P_Timer0_NotmalMode.hex"
	"C:\Tools\IDE\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-objcopy.exe" -j .eeprom  --set-section-flags=.eeprom=alloc,load --change-section-lma .eeprom=0  --no-change-warnings -O ihex "ATmega328P_Timer0_NotmalMode.elf" "ATmega328P_Timer0_NotmalMode.eep" || exit 0
	"C:\Tools\IDE\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-objdump.exe" -h -S "ATmega328P_Timer0_NotmalMode.elf" > "ATmega328P_Timer0_NotmalMode.lss"
	"C:\Tools\IDE\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-objcopy.exe" -O srec -R .eeprom -R .fuse -R .lock -R .signature -R .user_signatures "ATmega328P_Timer0_NotmalMode.elf" "ATmega328P_Timer0_NotmalMode.srec"
	"C:\Tools\IDE\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-size.exe" "ATmega328P_Timer0_NotmalMode.elf"
	
	





# Other Targets
clean:
	-$(RM) $(OBJS_AS_ARGS) $(EXECUTABLES)  
	-$(RM) $(C_DEPS_AS_ARGS)   
	rm -rf "ATmega328P_Timer0_NotmalMode.elf" "ATmega328P_Timer0_NotmalMode.a" "ATmega328P_Timer0_NotmalMode.hex" "ATmega328P_Timer0_NotmalMode.lss" "ATmega328P_Timer0_NotmalMode.eep" "ATmega328P_Timer0_NotmalMode.map" "ATmega328P_Timer0_NotmalMode.srec" "ATmega328P_Timer0_NotmalMode.usersignatures"
	