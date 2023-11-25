CROSS_COMPLIE 	?= arm-linux-gnueabihf-
TARGET		  	?= printf

CC 				:= $(CROSS_COMPLIE)gcc
LD				:= $(CROSS_COMPLIE)ld 
OBJCOPY			:= $(CROSS_COMPLIE)objcopy 
OBJDUMP			:= $(CROSS_COMPLIE)objdump 

LIBPATH 		:= -lgcc -L /usr/local/arm/gcc-linaro-4.9.4-2017.01-x86_64_arm-linux-gnueabihf/lib/gcc/arm-linux-gnueabihf/4.9.4

INCDIRS			:= imx6ul \
				   stdio/include \
				   bsp/clk \
				   bsp/led \
				   bsp/delay \
				   bsp/beep \
				   bsp/key \
				   bsp/gpio \
				   bsp/exit \
				   bsp/int \
				   bsp/epittimer \
				   bsp/key_filter \
				   bsp/uart
				
SRCDIRS			:= project \
				   stdio/lib \
				   bsp/clk \
				   bsp/led \
				   bsp/delay \
				   bsp/beep \
				   bsp/key \
				   bsp/gpio \
				   bsp/exit \
				   bsp/int \
				   bsp/epittimer \
				   bsp/key_filter \
				   bsp/uart


INCLUDE			:= $(patsubst %, -I %, $(INCDIRS))

SFILES			:= $(foreach dir, $(SRCDIRS), $(wildcard $(dir)/*.s))
CFILEC			:= $(foreach dir, $(SRCDIRS), $(wildcard $(dir)/*.c))

SFILENDIR		:= $(notdir $(SFILES))
CFILENDIR		:= $(notdir $(CFILEC))

SOBJS			:= $(patsubst %, obj/%, $(SFILENDIR:.s=.o))
COBJS			:= $(patsubst %, obj/%, $(CFILENDIR:.c=.o))
OBJS			:= $(SOBJS) $(COBJS)

VPATH			:= $(SRCDIRS)

.PHONY: clean

$(TARGET).bin : $(OBJS)
	$(LD) -Timx6ul.lds $^ -o $(TARGET).elf
	$(OBJCOPY) -O binary -S $(TARGET).elf $@
	$(OBJDUMP) -D -m arm $(TARGET).elf > $(TARGET).dis

$(SOBJS) : obj/%.o : %.s
	$(CC) -Wall -nostdlib -fno-builtin -c -O2 $(INCLUDE) $< -o $@

$(COBJS) : obj/%.o : %.c
	$(CC) -Wall -Wa,-mimplicit-it=thumb -nostdlib -fno-builtin -c -O2 $(INCLUDE) $< -o $@

clean:
	rm -rf $(TARGET).elf $(TARGET).dis $(TARGET).bin $(COBJS) $(SOBJS)
