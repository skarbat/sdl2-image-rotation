#
# build sdl2-imgrotate.cpp - A simple SDL2 app that rotates an image on the screen
#
# You need libsdl2-dev package installed
#

# replace the gcc compiler if needed
#CXX = g++-4.7

CXXFLAGS = -Wall -c -DHAVE_OPENGL -DBCMHOST=1 -std=c++11
LDFLAGS = -lSDL2

app = sdl2-imgrotate

all: $(app)

$(app): $(app).o
	$(CXX) $(LDFLAGS) $(app).o -o $@

$(app).o: $(app.cpp)
	$(CXX) $(CXXFLAGS) $(app).cpp -o $@

clean:
	rm *.o && rm $(app)
