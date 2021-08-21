ORACCRSC := /daten/Projekte/Calliope/OpenRoberta/ora-cc-rsc/RobotMbed/libs2017
BUILD := build

MICROBITPATH := $(ORACCRSC)/microbit
MICROBITDALPATH := $(ORACCRSC)/microbit-dal
MBEDCLASSICPATH := $(ORACCRSC)/mbed-classic
BLEPATH := $(ORACCRSC)/ble
BLE_BOOTLOADER_RESERVED_HEX := $(ORACCRSC)/BLE_BOOTLOADER_RESERVED.hex
S110NRF51822_HEX := $(ORACCRSC)/s110_nrf51822_8.0.0_softdevice.hex
NRF51822 := $(ORACCRSC)/NRF51822.ld

CPPLAGS := -fno-exceptions -fno-unwind-tables -ffunction-sections -fdata-sections -Wdeprecated -Wno-unused-variable -Wall -Wextra -fno-rtti -fno-threadsafe-statics -mtune=cortex-m0 -mthumb -D__thumb2__ -std=c++11 -fwrapv -Os -g -gdwarf-3 -DNDEBUG -DTOOLCHAIN_GCC -DTOOLCHAIN_GCC_ARM -DMBED_OPERATORS -DNRF51 -DTARGET_NORDIC -DTARGET_M0 -D__MBED__=1 -DMCU_NORDIC_16K -DTARGET_NRF51_CALLIOPE -DTARGET_MCU_NORDIC_16K -DTARGET_MCU_NRF51_16K_S110 -DTARGET_NRF_LFCLK_RC -DTARGET_MCU_NORDIC_16K -D__CORTEX_M0 -DARM_MATH_CM0 -MMD
LDFLAGS := -fno-exceptions -fno-unwind-tables -Wl,--no-wchar-size-warning -Wl,--gc-sections -Wl,--sort-common -Wl,--sort-section=alignment -Wl,-wrap,main -mcpu=cortex-m0 -mthumb --specs=nano.specs

INCLIB := -I $(MICROBITDALPATH)/inc/drivers \
          -I $(MICROBITDALPATH)/inc/core \
          -I $(MICROBITDALPATH)/inc/platform \
          -I $(MBEDCLASSICPATH)/api \
          -I $(MBEDCLASSICPATH)/targets/hal/TARGET_NORDIC/TARGET_MCU_NRF51822/TARGET_NRF51_CALLIOPE \
          -I $(MBEDCLASSICPATH)/targets/hal/TARGET_NORDIC/TARGET_MCU_NRF51822 \
          -I $(MBEDCLASSICPATH)/targets/cmsis/TARGET_NORDIC/TARGET_MCU_NRF51822 \
          -I $(MBEDCLASSICPATH)/targets/cmsis \
          -I $(MBEDCLASSICPATH)/hal

INCDEMO := $(INCLIB) \
           -I $(MICROBITPATH)/inc \
           -I $(BLEPATH) \
           -I $(MICROBITDALPATH)/inc/types \
           -I $(MICROBITDALPATH)/inc/bluetooth

LDLIBS := -lnosys  -lstdc++ -lsupc++ -lm -lc -lgcc -lstdc++ -lsupc++ -lm -lc -lgcc
CALLIOPELIBS := $(ORACCRSC)/microbit.a \
                $(ORACCRSC)/ble.a \
                $(ORACCRSC)/microbit-dal.a \
                $(ORACCRSC)/ble-nrf51822.a \
                $(ORACCRSC)/nrf51-sdk.a \
                $(ORACCRSC)/mbed-classic.a

all: directories lib demo

directories:
	mkdir -p $(BUILD)
	
lib: DcMotor.a

demo: firmware.hex

           
firmware.hex: MotorTest.hex
	srec_cat $(BLE_BOOTLOADER_RESERVED_HEX) -intel $(S110NRF51822_HEX) -intel $(BUILD)/$< -intel -o $@ -intel --line-length=44

MotorTest.hex: MotorTest
	arm-none-eabi-objcopy -O ihex $(BUILD)/$< $(BUILD)/$@

MotorTest: MotorTest.o DcMotor.a
	arm-none-eabi-g++ $(LDFLAGS) -T $(NRF51822) -Wl,-Map,$(BUILD)/MotorTest.map -Wl,--start-group $(foreach i,$^,$(BUILD)/$(i)) $(LDLIBS) $(CALLIOPELIBS) -Wl,-end-group -o $(BUILD)/$@

MotorTest.o: src/MotorTest.cpp
	arm-none-eabi-g++ $(INCDEMO) $(CPPLAGS) -MT $(BUILD)/$@.cpp.o -MF $(BUILD)/$@.cpp.o.d -o $(BUILD)/$@ -c $<

DcMotor.a: DcMotor.o
	ar rvs $(BUILD)/$@ $(BUILD)/$^
	
DcMotor.o: src/DcMotor.cpp
	arm-none-eabi-g++ $(INCLIB) $(CPPLAGS) -MT $(BUILD)/$@.o -MF $(BUILD)/$@.o.d -c -o $(BUILD)/$@ $<
        
clean:
	-rm firmware.hex $(BUILD)/*
	-rmdir $(BUILD)
	
