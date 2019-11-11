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

## Comments

This section explains how you can write your comments on your code.

### `DO` Write Comments, Please.

Do I need to say more about this?

### `DONT` Write How but `DO` Write What

Readers are not TAs. They don't care how you are smart, how you are so logical, or how you are good at code. Just tell us what you did.

```cpp
// Add even numbers from 0 to 9
int evenSum = 0;
for(int i = 0; i < 10; i++){
  evenSum += i%2 == 0 ? i : 0;
}
```

### `DO` Use Comments Consistently

Make your own rule to use `//` or `/* */`. Please `DONT` use comments like this:

```cpp
// function add
/* This gets two integers */
// returns sum
int add(int a, int b){
  // body
  return a + b;	/* return sum */
}
```

*Personally,* I recommend you to use `/* */` only for explaining your modules because writing `/* */` frequently would be very heavy task compared to `//`. 

```cpp
/*
	This class is for ~~
	~~~~~
*/
class Student {
public:
  Stuudent();	// constructor
}
```

### `DO` Tell Us What Your Functions Do

Your function has its own usage which you made. Please tell us how we can use your function. I strongly recommend you to follow below comment format, which is suggested in *CS320 Programming Language*, KAIST.

```cpp
// function add: int, int -> int
// - gets two integers and return the sum of them
int add(int a, int b){return a+b;}
// test add(0, 0) == 0
// test add(-1, 1) == 0
// test add(2, 3) == 5
```

## Object-Oriented Programming

This section explains how you can write object-oriented codes. The OOP code includes how to use classes in basic, how to dynamically allocate memory safely for the classes, and how to separate an interface and an implementation correctly.

### `DO` Use Classes If Possible

Class, basically, is a unit of object-oriented programming which consists of attributes and methods. Let's start with C code.

```c
int MAXIMUM_STUDENT_ID_ASSIGNED = 0;
typedef struct {
  int studentID;
} Student;

void initStudent(Student *student){
  student->studentID = MAXIMUM_STUDENT_ID_ASSIGNED++;
}

int getStudentID(Student *student){
	return student->studentID;
}
```

For the C code, we cannot say that struct `Student` and methods for Student are highly co-related. This is not very good for maintenance and reproductivity. Let's put methods into the struct.

```c
int MAXIMUM_STUDENT_ID_ASSIGNED = 0;
typedef struct {
  int studentID;
  
  void initStudent(Student *student){
    student->studentID = MAXIMUM_STUDENT_ID_ASSIGNED++;
  }
  
  int getStudentID(Student *student){
    return student->studentID;
  }
} Student;
```

Although this code might not be very familiar to you whom have used C language only this is very basic of C++ Classes. 

```cpp
class Student {
private:
  static int MAXIMUM_STUDENT_ID_ASSIGNED = 0;
  int studentID;
public:
  Student(){
    this->studentID = Student::MAXIMUM_STUDENT_ID_ASSIGNED++;
  }
  
  int getID(){
    return this->studentID;
  }
};
```

This is simple and intuitive. Thus, please `DONT` use struct if possible.

### `DONT` Use malloc, calloc, realloc, and free

You might be very familiar to the `malloc`, `calloc`, `realloc`, and `free`. Please `DONT` use them. They are not type-safe, not object-oriented, and difficult to handle the pointers. Instead, please `DO` use `new` and `delete`.

```cpp
int *buckets = new int[20];	// allocate 20 integers
delete[] buckets;

int *bucket = new int(20);	// allocate a single integer and initialized to 20
delete bucket;
```

`new` helps classes to be initialized without any additional codes. It means, it is necessary to use `new` for allocating the classes dynamically.

### `DO` Separate Interface and Implementation

Remain a header file as the interface. Please `DONT` add any implementation to the interface. You should encapsulate your code not only for securing your idea but also for helping other developers.

```cpp
// Student.hpp

class Student {
private:
  static int MAXIMUM_STUDENT_ID_ASSIGNED = 0;
  int studentID;
public:
  Student();
  int getID();
};
```

```cpp
// Student.cpp

Student::Student(){
	this->studentID = Student::MAXIMUM_STUDENT_ID_ASSIGNED++;
}

int Student::getID(){
	return this->studentID;
}
```

## C++ Functionalities

This section describes C++ functionalities, which might be useful for your projects.

### `DO` Use Reference Type

Reference type gives a variable another name, which shares the same memory space. This is different to the pointer. Pointers themselves do not share the memory space but only contains same memory address pointing to the other variable.

```cpp
int value = 10;
int &ref = value;		// reference
int *pt = &value;		// pointer

cout << "value is " << ref << endl;
cout << "value is " << *pt << endl;

ref = 100; 	// set
*pt = 100;	// set
```

### `DO` Use STL

C++ provides a Standard Template Library(STL), which is a useful set of data sturctures and algorithms. They are written by many AWESOME programmers who may be better than us... STL is time-efficient, space-efficient, and easy to use.

```cpp
#include <iostream>
#include <vector>
using namespace std;

int main(){
  vector<int> vec;
  vec.push_back(100);
  vec.push_back(101);
  
  for(vector<int>iterator:: iter = vec.begin(); iter != vec.end(); iter++){
    cout << *iter << endl;
  }
  
  return 0;
}
```

There are so many useful libraries! Please google it!

### `DO` Use Smart Pointers

Unless you can use reference type but you have to use a pointer, please `DO` use smart pointers. A smart pointer wraps a pointer into class form, which freed the memory space in the destructor. It means that you don't really have to free them by yourself. For example,

```cpp
#include <iostream>
#include <memory>
using namespace std;

int main() {
  unique_ptr<int> ptValue(new int(5));	// initialize
  cout << *ptValue << endl;
  return 0;	// See, you don't have to free the pointer.
}
```

For more reference, Please google `Smart Pointers` or see [Microsoft Document](https://docs.microsoft.com/ko-kr/cpp/cpp/smart-pointers-modern-cpp?view=vs-2019).

## Branching Rules

This section explains how you use git branches.

### `DO` Use Branches

Everyone on the *master*branch conflict everything. For the unit code of your implementation, please `DO` separate branches.

### `DO` Name Correctly

Your branch names are more important than you think. Please `DO` name them correctly. You may shorten the name. Also, please use `-` for branching more from existing branches.

```bash
$ git branch genalg	# for genetic algorithm
$ git checkout genalg
$ git branch genalg-cx	# for crossover operations on GA
```

### `DO` Use Your Lastname For Separation

You may want to write another version of code which is not written by yourself. For example, `Sungwoo Jeon` may want to write another version of crossover that is written by `Kihoon Kwon`. In this case Kihoon may have already made a branch named `genalg-cx` or something like this. Then, Sungwoo may make `genalg-cx-jeon`.

```bash
$ git checkout genalg
$ git branch genalg-cx-jeon
```

### `DONT` Push to the Master Directly

`DONT` push to the *master*branch directly. Only use `merge` to modify *master*.

### `DONT` Merge to the Master by Yourself

`DONT` merge to the master by yourself. Let's leave *master* a completely running version of code. We may set one responsible person to merge, or merge when we all meet together.