make:
	g++ -c main.cpp gameobjects.cpp input.cpp music.cpp sound.cpp render.cpp state.cpp ui.cpp input.cpp particles.cpp helpers.cpp -std=c++11

link:
	g++ main.o gameobjects.o music.o sound.o render.o state.o ui.o input.o particles.o helpers.o -lsfml-system -lsfml-audio -lsfml-window -lsfml-graphics -o ../bin/planetdefense

clean:
	rm main.o gameobjects.o music.o sound.o render.o state.o ui.o input.o particles.o helpers.o
