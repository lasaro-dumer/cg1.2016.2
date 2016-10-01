CFLAGS = -lglut -lGL -lGLU -lGLee -lglfw
GNAME = bin/spaceMission3
BUILDER = g++

default: mkbin
	$(BUILDER) *.cpp $(CFLAGS) -o $(GNAME)
mkbin:
	mkdir -p bin
clean:
	rm -rf $(GNAME) *.o *.gch
