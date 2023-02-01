game: main.o application.o bike.o hitbox.o trail.o menu.o sound.o client.o server
	gcc -o game main.o application.o bike.o hitbox.o trail.o menu.o sound.o client.o -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_net -lSDL2_ttf -lm
main.o: main.c
	gcc -c main.c
applicaiton.o: application.c
	gcc -c application.c
bike.o: bike.c
	gcc -c bike.c
hitbox.o: hitbox.c
	gcc -c hitbox.c
trail.o:
	gcc -c trail.c
menu.o:
	gcc -c menu.c
sound.o:
	gcc -c sound.c
client.o: client.c
	gcc -c client.c
server:
	gcc -o server server.c -lSDL2 -lSDL2_net