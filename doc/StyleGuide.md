# Coding Style Guides

All of these guidelines are *Recommendations.* You don't have to strictly follow all the suggestions, however, if a commitment of your code violates those policies and is hardly readable the commitment may be rejected without detailed explanations. `DO` means *we recommend you to follow the style* and `DONT` means *please do not use such styles.*

## Naming Rules

This section explains how to name your variables, files, or anything that needs to be named. 

### `DONT` Use A Meaningless Word for Your Name

Please `DONT` use a meaningless word for your name. This is not only for your interfaces, global variable, or public methods, but also for your local variable. Remember that even you will be a third-party person in a few days.

```cpp
/* DONT */
int a, b, i, s, t;
char *c, p, **pp;
```

However, this guide can be relaxed only for some special cases such as a variable for temporary iteration or variables for obvious purposes.  

```cpp
int add(int a, int b);					// might be obvious
for(int i = 0; i < 10; i++);		// we may guess the purpose intuitively
```

### `DO` Use camelCase for Your Variables

Please `DO` use **camelCase** for your variables. Start with a lower-case letter and continue with a upper-case letter if you need more than one words in a single name. Also, we recommend you to name your variable starting with a noun.

```cpp
int numberOfObjects;
```

### `DO` Use camelCase for Your Methods

Please `DO` use **camelCase** for your methods. Start with a lower-case letter and continue with a upper-case letter if you need more than one words in a single name. Also, we recommend you to name your variable starting with a root verb.

```cpp
int getNumberOfObjects(int objectID){
  // codes here
}
```

### `DO` Use PascalCase for Your Classes

Please `DO` use **PascalCase** for your methods. Start with a upper-case letter and continue with a upper-case letter if you need more than one words in a single name. Also, we recommend you to name your variable starting with a noun.

```cpp
class Student {
  // codes here
}

class UndergraduateStudent : public Student {
  // codes here
}
```

This guide shall apply mutatis mutandis if you use struct in C. In such cases, please `DO` use typedef keyword.

```c
typedef struct {
  // codes here
} GraduateStudent;
```

### `DO` Use SNAKE_CASE with All Upper Letters for Your Constants

Please `DO` use **SNAKE_CASE** with all upper letters for your constants. Constants in this section basically means constants defined by macro grammar. 

```cpp
#define NUMBER_OF_GENERATIONS 1000
```

## Naming Conventions

This section explains some conventions that might be useful for your namings. 

### `DO` Use `pt` Prefix for Your Pointers

Please `DO` use `pt` prefix for your pointer variables. For the pointers with double or more than double depths, please do not duplicate the prefix but use a meaningful word for the variable.

```cpp
int *ptNumberOfObjects = &numberOfObjects;
int **ptObjectTable;
```

