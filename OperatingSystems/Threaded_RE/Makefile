# DO NOT EDIT -------------------------------
C=/afs/nd.edu/user14/csesoft/new/bin/gcc
CFLAGS=-Wall
CPP=/afs/nd.edu/user14/csesoft/new/bin/g++
CPPFLAGS=-Wall
LD=/afs/nd.edu/user14/csesoft/new/bin/g++
LDFLAGS=-lpthread
# # ---------------------------- END DO NOT EDIT
TARGETS=	threadedRE
all:		$(TARGETS)

CPPFLAGS += -std=c++11 -g -I/afs/nd.edu/coursesp.18/cse/cse30341.01/support/gcc-libpcap/include
LDFLAGS += -L/afs/nd.edu/coursesp.18/cse/cse30341.01/support/gcc-libpcap/lib -lpcap

threadedRE: threadedRE.o
	@echo Making threadedRE...
	@$(LD) $^ $(LDFLAGS) -o $@

# C++ compiler
%.o: %.cpp
	@$(CPP) $(CPPFLAGS) -c $<

# C compiler
#%.o: %.c
#	@$(C) $(CFLAGS) -c $<

.PHONY: clean
clean:
	@echo Cleaning...
	@rm -f $(TARGETS) *.o

