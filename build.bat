@echo off

g++ -o inv.exe *.cpp inc/glad.c -Iinc/ -lopengl32 -lglfw3 -lkernel32 -lshell32 -luser32 -lgdi32
