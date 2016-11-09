CFLAGS = -std=c++11 -lglut -lGL -lGLU -lGLee -lglfw3 -lGL -lX11 -lXi -lXrandr -lXxf86vm -lXinerama -lXcursor -lrt -lm -pthread -ldl
OUTDIR = bin
MODELSOUT = $(OUTDIR)/data/models
GNAME = $(OUTDIR)/spaceMission3
BUILDER = g++
SOURCE = *.cpp elements/*.cpp util/*.cpp util/helpers/*.cpp

default: mkout
	$(BUILDER) $(SOURCE) $(CFLAGS) -o $(GNAME)
debugLight: CFLAGS += -DLDEBUG
debugLight: default
mkbin:
	mkdir -p $(OUTDIR)
mkdmodels:
	mkdir -p $(MODELSOUT)
cpmodels:
	cp -r data/models/*.obj $(MODELSOUT)
cpopt:
	cp options.ini $(OUTDIR)/options.ini
mkout: mkbin cpopt mkdmodels cpmodels

clean:
	rm -rf *.o *.gch $(OUTDIR)
