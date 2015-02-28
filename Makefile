run: exec
	./sfml-app
exec: obj 
	g++ main.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system
obj:
	g++ -c main.cpp
