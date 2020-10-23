main:
		gcc signos.c borrar.c guardar.c añadir.c main.c -o parkins

clean:
		rm parkins
		rm *.txt
