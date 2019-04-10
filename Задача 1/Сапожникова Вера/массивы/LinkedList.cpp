#include "stdafx.h"
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>

template<class T>
class LinkedList {
	struct node {
		T     val;
		node* next;
	};
private:
	node * head;
	size_t cnt;
public:

	LinkedList(void) :head(NULL), cnt(0) {
	}

public:

	void removeall(void) {
		node* prev = NULL;
		while (head->next) {
			prev = head;
			head = head->next;
			free(prev);
			--cnt;
		}
		free(head);
		--cnt;
	}

	int size(void) const { return cnt; }

	void print() {
		node* temp = head;
		while (head != NULL) {
			printf("%d ", head->val);
			head = head->next;
		}
		printf("\n");
		head = temp;
	}

	void set(int n, T val) {
		int i = 0;
		if (n < 0 || n > cnt)
		{
			exit(-1);
		}
		if (n == 0 && head == NULL)
		{
			node* tmp = (node*)malloc(sizeof(node));
			tmp->next = NULL;
			tmp->val = val;
			head = tmp;
			++cnt;
			return;
		}
		
		node* t = head;
		while (i <= n && head->next != NULL) {
			head = head->next;
			i++;
		}		
		if (i == n) {

			head->val = val;
		}
		else {
			node* tmp = (node*)malloc(sizeof(node));
			tmp->val = val;
			tmp->next = NULL;
			head->next = tmp;
			++cnt;
		}
		head = t;
	}

	T get(int n) {
		int counter = 0;
		if (n < 0 || n >= cnt)
		{
			exit(-1);
		}
		node* tmp = head;
		while (counter < n && tmp) {
			tmp = tmp->next;
			counter++;
		}
		return tmp->val;
	}

	T deleteAtIndex(int n) {
		if (n < 0 || n >= cnt)
		{
			exit(-1);
		}
		--cnt;
		if (n == 0) {
			node* prev = NULL;
			T val;
			if (head == NULL) {
				exit(-1);
			}
			prev = head;
			val = prev->val;
			head = head->next;
			free(prev);
			return val;
		}
		else {
			node* prev = getNth(n - 1);
			node* elm = prev->next;
			T val = elm->val;

			prev->next = elm->next;
			free(elm);
			return val;
		}
	}

	void pushBack(T value) {
		node* last = getLast();
		node *tmp = (node*)malloc(sizeof(node));
		tmp->val = value;
		tmp->next = NULL;
		last->next = tmp;
	}

	int popBack() {
		node *pFwd = NULL;
		node *pBwd = NULL;

		if (!head) {
			exit(-1);
		}
		--cnt;
		pFwd = head;
		while (pFwd->next) {
			pBwd = pFwd;
			pFwd = pFwd->next;
		}
		T val;

		if (pBwd == NULL) {
			val = head->val;
			free(head);
			head = NULL;
		}
		else {
			val = pBwd->next->val;
			free(pFwd->next);
			pBwd->next = NULL;		
		}
		return val;
	}

private:

	node * getNth(int n) {
		int counter = 0;
		node* tmp = head;
		while (counter < n && tmp) {
			tmp = tmp->next;
			counter++;
		}
		return tmp;
	}


	node* getLast() {
		node* tmp = head;
		if (tmp == NULL) {
			return NULL;
		}
		while (tmp->next) {
			tmp = tmp->next;
		}
		return tmp;
	}
};

/*int main(void) {
	LinkedList<int> lc;
	for (int i = 0; i < 5; ++i) {
		lc.set(i, i+1);
	}
	lc.print();
	printf(" popBack: %d\n ", lc.popBack());
	printf("size: %d\n ", lc.size());
	printf("get(2): %d\n ", lc.get(2));
	lc.print();
	printf("deleteAtIndex(2): %d\n ", lc.deleteAtIndex(2));
	lc.print();
	lc.pushBack(10);
	lc.print();
	

	lc.removeall();
	//lc.printLinkedList();
	return 0;
}*/