CFLAGS = -lglut -lGL -lGLU -lGLee -lglfw3 -lGL -lX11 -lXi -lXrandr -lXxf86vm -lXinerama -lXcursor -lrt -lm -pthread -ldl
GNAME = bin/spaceMission3
BUILDER = g++

default: mkbin
	$(BUILDER) *.cpp $(CFLAGS) -o $(GNAME)
mkbin:
	mkdir -p bin
clean:
	rm -rf $(GNAME) *.o *.gch
