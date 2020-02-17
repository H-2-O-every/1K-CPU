all: CCode.o CDecode.o
	g++ -o tpu CCode.o CDecode.o CExecute.cpp CRegister.cpp CMemory.cpp main.cpp
#	./tpu file.bin 20 
#	./tpu test.bin 3
#	./tpu Compare2MOV4.bin 46
#	./tpu Compare1MOV4.bin 70
#	./tpu CompareJZ1MOV4.bin 16
#	./tpu CompareJZ2MOV4.bin 13
#	./tpu Matrix.bin 111
#	./tpu Matrix55.bin 61
#	./tpu MatrixExceptJZ.bin 986
#	./tpu MatrixJZMOV1.bin 981
	./tpu MatrixJZMOV1copy.bin 981
#	./tpu Testfile.bin 1
CCode.o: CCode.cpp
	g++ -c CCode.cpp

CDecode.o: CDecode.cpp
	g++ -c CDecode.cpp

clean:
	rm -rf *.o ./tpu
	
