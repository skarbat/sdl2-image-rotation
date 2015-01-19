#
# build sdl2-imgrotate.cpp - A simple SDL2 app that rotates an image on the screen
#

CXX = g++-4.7

# Change paths below to your environment
INC_SDL2 = /opt/sdl2-raspberrypi/include/

CXXFLAGS = -Wall -c -DHAVE_OPENGL -DBCMHOST=1 -std=c++11 -I $(INC_SDL2)
LDFLAGS = -L /opt/sdl2-raspberrypi/lib/ -lSDL2

app = sdl2-imgrotate
all: $(app)

$(app): $(app).o
	$(CXX) $(LDFLAGS) $(app).o -o $@

$(app).o: $(app.cpp)
	$(CXX) $(CXXFLAGS) $(app).cpp -o $@

clean:
	rm *.o && rm $(app)
