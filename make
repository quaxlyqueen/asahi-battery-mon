#!/bin/zsh

gcc -o battery-mon main.c;
./battery-mon --daemonize;
