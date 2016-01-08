#ifndef GENSTACK_H_
#define GENSTACK_H_

using namespace std;

template<typename T> 

class GenStack{
public:

	int top;
	int max;

	void push(T obj);
	T pop();
	T peak();
	bool isEmpty();
	bool isFull();
	void doubleSize();

	T *myStackArray;
	T *newArray;

	GenStack() {}

	GenStack(int maxSize) {
		myStackArray = new T[maxSize];
		top = -1;
		max = maxSize;
	}

	~GenStack() {
		delete [] myStackArray;
	}

};

template<typename T>
bool GenStack<T>::isEmpty() {
	return (top == -1);
}

template<typename T>
bool GenStack<T>::isFull() {
	return (top == max-1);
}

template<typename T>
void GenStack<T>::push(T obj) {
	if(isFull()) {
		doubleSize();
	}
	myStackArray[++top] = obj;
}

template<typename T>
T GenStack<T>::pop() {
	if(isEmpty()) {
		throw std::logic_error("The stack is empty.");
	}
	else {
		return myStackArray[top--];
	}
}

template<typename T> 
T GenStack<T>::peak() {
	return myStackArray[top];
}

template<typename T>
void GenStack<T>::doubleSize() {
	max *= 2;
	newArray = new T[max];

	for(int i=0; i<=top; ++i) {

		newArray[i] = myStackArray[i];
		
	}

	myStackArray = newArray;
}

#endif /* GENSTACK_H_ */
