all: hello-hurd

# -nostdlib
hello-hurd: hello-hurd.o exec_startupUser.o machUser.o processUser.c ioUser.c
	gcc -static -nostartfiles -o $@ $^

%.o: %.c
	gcc -c $<

hello-hurd.o: exec_startup.h mach.h process.h io.h

exec_startupUser.c exec_startup.h: /usr/include/i386-gnu/hurd/exec_startup.defs
	mig $<

machUser.c mach.h: /usr/include/i386-gnu/mach/mach.defs
	mig $<

processUser.c process.h: /usr/include/i386-gnu/hurd/process.defs
	mig $<

ioUser.c io.h: /usr/include/i386-gnu/hurd/io.defs
	mig $<

hurd_types.h: /usr/include/i386-gnu/hurd/hurd_types.defs
	mig $<

clean:
	rm -f exec_* mach* process* io* *.o hello-hurd
