#include <iostream>
#include <stdlib.h>
#include <iomanip>

void ptrIntro() {

	int myInt{ 10 };
	int* intPointer{ &myInt };

	std::cout << "Address of myInt is " << &myInt << "\n";
	std::cout << "Pointer holds the value " << intPointer << "\n";
}

int f(int* mainIntPtr) {
	int localInt{ 0 };
	int* localIntPtr{ 0 };
	int direction{ 0 };

	std::cout << "Address of mainInt is " << mainIntPtr << "\n";
	std::cout << "Address of localInt is " << &localInt << "\n";

	localIntPtr = &localInt;

	if (localIntPtr < mainIntPtr) {
		direction = -1;
	}
	else {
		direction = 1;
	}

	return direction;
}

void stackDir() {
	int mainInt{ 1 };
	int direction{ f(&mainInt) };

	if (direction == 1) {
		std::cout << "Stack grows from Low to High";
	}
	else {
		std::cout << "Stack grows from High to Low";
	}
}

class base {
protected:
	int a, b;
	int iarray[20];
	char carray[80];

public:
	base() {
		std::cout << "base constructor\n";
		a = 0;
		b = 0;
	}
	int getA();
	int setA();
};

class derived1: public base {
protected:
	int c, d;
	double myDouble;
	long myLong;

public:
	derived1() {
		std::cout << "derived constructor\n";
		c = 0;
		d = 0;
	}
	int getC();
	int setC();
};

class derived2 : public base {
protected:
	int e, f;
	double myDouble2;
	long myLong2;

public:
	derived2() {
		std::cout << "derived constructor\n";
		e = 0;
		f = 0;
	}
	int getE();
	int setE();
};

void f2(base bobj, derived1 d1obj, derived2 d2obj) {
	int bytes{ 0 };

	//memory used storing objects on program stack
	bytes = (int)(&bobj) - (int)(&d2obj);
	if (bytes < 0) {
		bytes *= -1;
	}

	if ((int)&d2obj > (int)&d1obj) {
		bytes += sizeof(d2obj);
	}
	else {
		bytes += sizeof(d1obj);
	}

	std::cout << "Total stack space used for objects is " << bytes << "\n";
}

void stackSpace() {
	base bobj;
	derived1 d1obj;
	derived2 d2obj;
	derived2* d2ptr;

	std::cout << "size of bobj is " << sizeof(bobj) << "\n";
	std::cout << "size of d1obj is " << sizeof(d1obj) << "\n";
	std::cout << "size of d2obj is " << sizeof(d2obj) << "\n";
	f2(bobj, d1obj, d2obj);
	std::cout << "size of pointer to d2obj is " << sizeof(d2ptr) << "\n";
}

int main() {
	stackSpace();
	return 0;
}