run: exec
	./sfml-app
exec: obj 
	g++ main.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
obj:
	g++ -c -std=c++11  main.cpp 
