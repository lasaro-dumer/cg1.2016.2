CFLAGS = -std=c++11 -lglut -lGL -lGLU -lGLee -lglfw3 -lGL -lSOIL -lX11 -lXi -lXrandr -lXxf86vm -lXinerama -lXcursor -lrt -lm -pthread -ldl -lao -ldl -lm
OUTDIR = bin
MODELSOUT = $(OUTDIR)/data/models
FONTSOUT = $(OUTDIR)/data/fonts
LEVELSOUT = $(OUTDIR)/data/levels
AUDIOOUT = $(OUTDIR)/data/audio
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
mkdlevels:
	mkdir -p $(LEVELSOUT)
mkdaudio:
	mkdir -p $(AUDIOOUT)
cpmodels:
	cp -r data/models/*.obj $(MODELSOUT)
cpfonts:
	cp -r data/fonts/*.jpg $(FONTSOUT)
cplevels:
	cp -r data/levels/*.lvl $(LEVELSOUT)
cpaudio:
	cp -r data/audio/*.wav $(AUDIOOUT)
cpopt:
	cp options.ini $(OUTDIR)/options.ini
mkout: mkbin cpopt mkdmodels cpmodels mkdfonts cpfonts mkdlevels cplevels mkdaudio cpaudio

clean:
	rm -rf *.o *.gch $(OUTDIR)
