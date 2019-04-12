struct Node {
public:
	int value;
	Node *right;
	Node *left;
};

class LinkedList {
	Node *end;
	Node *start;
	int last_index;

public:
	LinkedList() {
		start = (Node*)malloc(sizeof(Node));
		start->value = 0;
		start->left = NULL;
		start->right = NULL;
		end = start;
		last_index = 0;
	}

	void set(int index, int value) {
		Node *curr_node = start;
		Node *previous;
		previous = NULL;
		if (index == 0)
			start->value = value;
		else {
			int i = 0;
			while (i != index - 1) {
				previous = curr_node;
				curr_node = curr_node->right;
				if (curr_node == NULL) {
					curr_node = (Node*)malloc(sizeof(Node));
					curr_node->value = 0;
					curr_node->left = previous;
					curr_node->right = NULL;
					previous->right = curr_node;
				}
				i++;
			}
			previous = curr_node;
			curr_node = (Node*)malloc(sizeof(Node));
			curr_node->value = value;
			curr_node->left = previous;
			curr_node->right = NULL;
			previous->right = curr_node;
			end = curr_node;
		}
		if (last_index < index)
			last_index = index;
	}

	int get(int index) {
		if (index > last_index)
			throw std::range_error("wrong index");
		Node *curr_node = start;
		int i = 0;
		while (i != index) {
			curr_node = curr_node->right;
			i++;
		}
		return curr_node->value;
	}

	int pop() {
		return end->value;
	}

	void push_back(int value) {
		if (last_index == -1) {
			start = (Node*)malloc(sizeof(Node));
			start->value = value;
			start->left = NULL;
			start->right = NULL;
			end = start;
		}
		else {
			Node *previous;
			previous = end;
			end = (Node*)malloc(sizeof(Node));
			end->value = value;
			end->left = previous;
			end->right = NULL;
			previous->right = end;
		}
		last_index++;
	}

	int pop_back() {
		if (end == NULL)
			throw std::range_error("stack empty");
		int value = end->value;
		end = end->left;
		end->right = NULL;
		last_index--;
		return value;
	}


	void remove_all() {
		last_index = 0;
		Node *curr_node = start;
		while (curr_node != NULL) {
			Node *child = curr_node->right;
			free(curr_node);
			curr_node = child;
		}
		start = (Node*)malloc(sizeof(Node));
		start->value = 0;
		start->left = NULL;
		start->right = NULL;
		end = start;
	}
};
