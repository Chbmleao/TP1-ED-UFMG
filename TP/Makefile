#
# Copyright 2021 Alysson Ribeiro da Silva - Federal University of Minas Gerais
#
# Permission is hereby granted, free of charge, to any person obtaining a copy 
# of this software and associated documentation files (the "Software"), to deal 
# in the Software without restriction, including without limitation the rights 
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies 
# of the Software, and to permit persons to whom the Software is furnished to do 
# so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all 
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, 
# INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
# PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT 
# HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION 
# OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE 
# SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
#

# cc and flags
CC = g++
CXXFLAGS = -pg -std=c++11 -g -Wall
#CXXFLAGS = -pg -std=c++11 -g -Wall

# folders
INCLUDE_FOLDER = ./include/
BIN_FOLDER = ./bin/
OBJ_FOLDER = ./obj/
SRC_FOLDER = ./src/
ASSETS = ./assets/
# OUT_FOLDER = ./out/

# all sources, objs, and header files
MAIN = Main
TARGET = tp1.exe
SRC = $(wildcard $(SRC_FOLDER)*.cpp)
OBJ = $(patsubst $(SRC_FOLDER)%.cpp, $(OBJ_FOLDER)%.o, $(SRC))
EXE = $(BIN_FOLDER)/run.out
ANALISAMEM = ./analisamem/bin/analisamem

all: build

mem: $(EXE)
	$(EXE) -1 entrada.txt -p /tmp/roundlog.out -l

perf: $(EXE)
	$(EXE) -1 $(ASSETS)entrada50k.txt -p /tmp/entrada50k.out
	$(EXE) -1 $(ASSETS)entrada60k.txt -p /tmp/entrada60k.out
	$(EXE) -1 $(ASSETS)entrada70k.txt -p /tmp/entrada70k.out
	$(EXE) -1 $(ASSETS)entrada80k.txt -p /tmp/entrada80k.out
	$(EXE) -1 $(ASSETS)entrada90k.txt -p /tmp/entrada90k.out
	$(EXE) -1 $(ASSETS)entrada100k.txt -p /tmp/entrada100k.out
	

build: $(OBJ)
	$(CC) $(CXXFLAGS) -o $(BIN_FOLDER)$(TARGET) $(OBJ)

$(OBJ_FOLDER)%.o: $(SRC_FOLDER)%.cpp
	$(CC) $(CXXFLAGS) -c $< -o $@ -I$(INCLUDE_FOLDER)

run: $(EXE)
	$(EXE) -1 entrada.txt -p /tmp/roundlog.out

