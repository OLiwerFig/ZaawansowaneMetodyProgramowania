

__start__: obj __lines_for_space__ ../libs/libInterp4Move.so ../libs/libInterpRotate.so 
	@echo "  Tworzenie wtyczki zakonczone."
	@echo

obj:
	mkdir obj

CPPFLAGS=-Wall -fPIC -pedantic -std=c++17 -Iinc -I../inc
LDFLAGS=-Wall -shared

__lines_for_space__:
	@echo
	@echo
	@echo
	@echo
	@echo

../libs/libInterp4Move.so: obj/Interp4Move.o
	g++ ${LDFLAGS} -o ../libs/libInterp4Move.so obj/Interp4Move.o
	@echo
	@echo "  Wtyczka dla polecenia 'Move' zostala utworzona."
	@echo

../libs/libInterpRotate.so: obj/InterpRotate.o
	g++ ${LDFLAGS} -o ../libs/libInterpRotate.so obj/InterpRotate.o
	@echo
	@echo "  Wtyczka dla polecenia 'Rotate' zostala utworzona."
	@echo


obj/Interp4Move.o: src/Interp4Move.cpp ../inc/AbstractInterp4Command.hh\
                   ../inc/AbstractScene.hh ../inc/AbstractComChannel.hh\
                   inc/Interp4Move.hh 
	g++ -c ${CPPFLAGS} -o obj/Interp4Move.o src/Interp4Move.cpp

obj/InterpRotate.o: src/InterpRotate.cpp ../inc/AbstractInterp4Command.hh\
                   ../inc/AbstractScene.hh ../inc/AbstractComChannel.hh\
                   inc/InterpRotate.hh 
	g++ -c ${CPPFLAGS} -o obj/InterpRotate.o src/InterpRotate.cpp


clean:
	rm -f obj/*

cleanall: clean
	find . -name \*~ -print -exec rm {} \;
	
