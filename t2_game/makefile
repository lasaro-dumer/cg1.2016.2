CFLAGS = -std=c++11 -lglut -lGL -lGLU -lGLee -lglfw3 -lGL -lSOIL -lX11 -lXi -lXrandr -lXxf86vm -lXinerama -lXcursor -lrt -lm -pthread -ldl
OUTDIR = bin
MODELSOUT = $(OUTDIR)/data/models
FONTSOUT = $(OUTDIR)/data/fonts
GNAME = $(OUTDIR)/spaceMission3
BUILDER = g++
SOURCE = *.cpp elements/*.cpp util/*.cpp util/helpers/*.cpp

default: mkout
	$(BUILDER) $(SOURCE) $(CFLAGS) -o $(GNAME)
debugLight: CFLAGS += -DLDEBUG
debugLight: default
debug: CFLAGS += -DDEBUG
debug: default
mkbin:
	mkdir -p $(OUTDIR)
mkdmodels:
	mkdir -p $(MODELSOUT)
mkdfonts:
	mkdir -p $(FONTSOUT)
cpmodels:
	cp -r data/models/*.obj $(MODELSOUT)
cpfonts:
	cp -r data/fonts/*.jpg $(FONTSOUT)
cpopt:
	cp options.ini $(OUTDIR)/options.ini
mkout: mkbin cpopt mkdmodels cpmodels mkdfonts cpfonts

clean:
	rm -rf *.o *.gch $(OUTDIR)
