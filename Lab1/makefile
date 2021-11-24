TimVideo: TimVideo.cpp
	g++ -o TimVideo.out TimVideo.cpp `pkg-config --cflags --libs opencv4`

clean: 
	rm -f TimVideo
	rm -f out.avi

all: clean TimVideo

run: all
	./TimVideo.out ./data