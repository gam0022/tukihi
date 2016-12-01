CFLAGS = -std=c++11 -I . -framework OpenGL -lglfw3

main: main.cpp
	g++ $(CFLAGS) -o tsukihi main.cpp

em: main.cpp
	emcc $(CFLAGS) -o tsukihi.html main.cpp
