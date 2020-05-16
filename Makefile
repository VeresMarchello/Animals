all:
	gcc -Iinclude/ src/callbacks.c src/camera.c src/draw.c src/init.c src/load.c src/main.c src/model.c src/scene.c src/texture.c src/utils.c -lSOIL -lglut32 -lopengl32 -lglu32 -lm -o animal.exe -Wall

