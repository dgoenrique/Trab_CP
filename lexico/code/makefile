# Makefile para o Falso Analisador Sintático da Linguagem Goinaninha

TARGET = goianinha

LEX_SRC = lex.yy.cc
MAIN_SRC = fake_analSint.cpp
TOKENS = tokens.h

CXX = g++
CXXFLAGS = -std=c++11 -Wall
LIBS = -lfl

all: $(TARGET)

$(TARGET): $(LEX_SRC) $(MAIN_SRC) $(TOKENS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(LEX_SRC) $(MAIN_SRC) $(LIBS)

lex.yy.cc: goianinha.l tokens.h
	flex --c++ goianinha.l

clean:
	rm -f $(TARGET) lex.yy.cc
