g++ -c -std=c++11  vc_shell.cpp
g++ -c  -std=c++11 remote_utils.cpp
g++  -std=c++11 vc_shell.o remote_utils.o -o remote_utils
