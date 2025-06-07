build:
	gcc -Wall -Wextra --pedantic main.c abb.c -o main.bin

clean:
	rm -rf *.bin

run:
	cat entrada.txt | ./main.bin > saida.txt

entrada:
	cat entrada.txt

saida:
	cat saida.txt
