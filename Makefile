#Makefile utilizado para otimizar a compilacao do projeto
#Copyright 2023 by Marco Tulio Franco Silva
#				   Pedro Henrique Souza Perazza Martins


#Variavel tipo de compilador
CC = g++

#flags utilizadas
CFLAGS = -c -std=c++14

#
all: executavel

#Linka arquivos compilados (objetos) ao executavel "executavel"
executavel: main.o Trabalhador.o
	$(CC) main.o Trabalhador.o -o executavel

#Compila main.cpp
main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

#Compila Trabalhador.cpp
Bmais.o: Trabalhador.cpp
	$(CC) $(CFLAGS) Trabalhador.cpp

#Remove todos os arquivos compilados (objetos) e o executavel (executavel do projeto)
clear:
	rm -rf *.o executavel