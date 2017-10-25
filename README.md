# ModernCpp

ModenCpp Demo

## RValue-Move

```
g++ -std=c++11 r_value_move_syntax.cpp
./a.out
```

```zsh

case0
default constructor, acquire resource
destructor
release resource, size:111

case1
default constructor, acquire resource
destructor
release resource, size:10

case2
default constructor, acquire resource
copy constructor
destructor
release resource, size:20
destructor
release resource, size:20

case3
default constructor, acquire resource
move constructor
destructor
release resource, size:30
destructor

case4
default constructor, acquire resource
default constructor, acquire resource
release resource, size:40
copy assignment
destructor
release resource, size:4
destructor
release resource, size:4

case5
default constructor, acquire resource
default constructor, acquire resource
release resource, size:50
move assignment
destructor
release resource, size:5
destructor
```
