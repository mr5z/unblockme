all: unblockme.exe

test.exe: main.o Rectangle.o
	 g++  -lOpenGL32 -lGLu32 -lglfwdll $^ -o $@ $<

test.o: main.cpp Rectangle.cpp
	 g++ -c $<
     
clean:
	 rm main.o Rectangle.o unblockme.exe