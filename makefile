EOSIOCPP=eosiocpp

.PHONY: all clean cont

all : cont

cont : cont.hpp cont.cpp
	$(EOSIOCPP) -o cont.wast cont.cpp
	$(EOSIOCPP) -g cont.abi cont.cpp

clean : 
	rm -f *.wast
	rm -f *.wasm
	rm -f *.abi
