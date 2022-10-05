#pragma once
#ifndef STACKLL_H
#define STACKLL_H

//Taken from ZyBook Lab
/*
* Stack pushs char into a stack from top to bottom
This class is the stack class it prints out backwards so we use pop function to start remving each char in the linked list
from there we just compare it with the queue class.

*/
template<typename TheType>
class Stack
{


	//NOTE: In an actual class, the StackNode structure, head, and tail would be private.  These are public to aid in grading.
public:
	struct StackNode
	{
		TheType data;
		StackNode* next;
	};

	StackNode* head, * tail;

private:
	void listPrepend(StackNode*&, StackNode*&, StackNode*&);
	void listRemoveAfter(StackNode*&, StackNode*&, StackNode*);


public:
	void push(TheType);
	TheType pop();
	bool isEmpty() const;
	Stack();
	~Stack(); // constructor 
};

template<typename TheType>

void Stack<TheType>::push(TheType val)
{
	StackNode* newNode;
	newNode = new StackNode;
	newNode->data = val;
	newNode->next = nullptr;

	listPrepend(head, tail, newNode);
}

template<typename TheType>
TheType Stack<TheType>::pop()
{
	int val;
	val = head->data;

	listRemoveAfter(head, tail, nullptr);

	return val;
}

template<typename TheType>
bool Stack<TheType>::isEmpty() const
{
	if (head == nullptr)
	{
		return true;
	}
	else
	{
		return false;
	}
	// return head == nullptr;
}

template<typename TheType>
Stack<TheType>::Stack()
{
	head = nullptr;
	tail = nullptr;
}

template<typename TheType>
Stack<TheType>::~Stack()
{
	StackNode* temp, * toDelete = nullptr;

	temp = head;
	while (temp != nullptr)
	{
		toDelete = temp;
		temp = temp->next;
		delete toDelete;
	}

	head = nullptr;
	tail = nullptr;
}


template<typename TheType>
void Stack<TheType>::listRemoveAfter(StackNode*& head, StackNode*& tail, StackNode* curNode) {
	StackNode* sucNode, * toDelete = nullptr;

	// Special case, remove head
	if (curNode == nullptr && head != nullptr) {
		sucNode = head->next;
		toDelete = head;
		head = sucNode;

		if (sucNode == nullptr) { // Removed last item
			tail = nullptr;
		}

	}
	else if (curNode->next != nullptr) {
		toDelete = curNode->next;
		sucNode = curNode->next->next;
		curNode->next = sucNode;

		if (sucNode == nullptr) { // Removed tail
			tail = curNode;
		}

	}

	delete toDelete;

}

template<typename TheType>
void Stack<TheType>::listPrepend(StackNode*& h, StackNode*& t, StackNode*& n)
{
	if (h == nullptr)
	{
		h = n;
		t = n;
	}
	else
	{
		n->next = h;
		h = n;
	}
}

#endif // ! STACKLL_H

