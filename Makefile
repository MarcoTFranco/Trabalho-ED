#Makefile utilizado para otimizar a compilacao do projeto
#Copyright 2020 by Marco Tulio Franco Silva
#				   Pedro Henrique Souza Perazza Martins


#Variavel tipo de compilador
CC = g++

#flags utilizadas
CFLAGS = -c -std=c++14

#
all: executavel

#Linka arquivos compilados (objetos) ao executavel "executavel"
executavel: main.o Employee.o
	$(CC) main.o Employee.o -o executavel

#compila main.cpp
main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

#compila Employee.cpp
Bmais.o: Employee.cpp
	$(CC) $(CFLAGS) Employee.cpp

#remove todos os arquivos compilados (objetos) e o executavel (executavel do projeto)
clear:
	rm -rf *.o executavel