PROGRAM_NAME := my_prog

INCLUDE_PATH := ./include

PRTL_CFLAGS_EXTRA :=

CFLAGS := -m32 -I$(INCLUDE_PATH) -nostdinc -nolibc -nostdlib -ffreestanding -fno-stack-protector -Qn -fno-pic -fno-pie -fno-asynchronous-unwind-tables -fomit-frame-pointer -finput-charset=UTF-8 -fexec-charset=GB2312 -march=pentium -Qn -O0 -w
CPPFLAGS := -m32 -I$(INCLUDE_PATH) -nostdinc -nolibc -nostdlib -ffreestanding -fno-exceptions -fno-stack-protector -Qn -fno-pic -fno-pie -fno-asynchronous-unwind-tables -fomit-frame-pointer -finput-charset=UTF-8 -fexec-charset=GB2312 -Qn -Os -march=pentium -fno-rtti -w

CC := gcc

C := $(CC) $(CFLAGS)
CPP := $(CC) $(CPPFLAGS)
ENTRYPOINT := 0x70000000
LD := ld
LD_FLAGS := -m elf_i386 -static -e Main -Ttext $(ENTRYPOINT)
LINK := $(LD) $(LD_FLAGS)
LIBS_PATH := libs
BASIC_LIB_C := $(LIBS_PATH)/libp.a $(LIBS_PATH)/libtcc1.a
BASIC_LIB_CPP := $(LIBS_PATH)/libp.a $(LIBS_PATH)/libtcc1.a $(LIBS_PATH)/libcpps.a
default:
	make build PRTL_CFLAGS_EXTRA=-DDEBUG
	make run
build:
	mkdir -p temp
	$(C) $(PRTL_CFLAGS_EXTRA) -I./prtl -c prtl/unwind.c -o temp/unwind.o
	$(C) $(PRTL_CFLAGS_EXTRA) -I./prtl -c prtl/errno-loc.c -o temp/errno-loc.o
	$(C) $(PRTL_CFLAGS_EXTRA) -I./prtl -c prtl/syscall.c -o temp/syscall.o
	$(C) $(PRTL_CFLAGS_EXTRA) -I./prtl -c prtl/memrchr.c -o temp/memrchr.o
	ar rcs temp/libprtl.a temp/unwind.o temp/errno-loc.o temp/syscall.o temp/memrchr.o

	$(C) -c src/boot.c -o temp/boot.o

	qemu-img create ./img/disk.img 128M
	mformat -t 64 -h 64 -i ./img/disk.img
	RUSTFLAGS="-C target-feature=-sse" cargo rustc --release --target i686-unknown-linux-musl -Zbuild-std=std,panic_abort,alloc,core -Z build-std-features=panic_immediate_abort
	$(LINK) temp/boot.o target/i686-unknown-linux-musl/release/libmprog.a temp/libprtl.a $(BASIC_LIB_C) -o target/i686-unknown-linux-musl/release/$(PROGRAM_NAME).bin
	mcopy -i ./img/disk.img target/i686-unknown-linux-musl/release/$(PROGRAM_NAME).bin ::
run:
	qemu-system-i386 -net nic,model=pcnet -net user -device sb16 -serial stdio -device floppy -fda ./img/Powerint_DOS_386.img -hdb ./img/disk.img -boot a -m 512 -enable-kvm