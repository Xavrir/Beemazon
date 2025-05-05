#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct Node{
	int price;
	char *product;
	int height;
	Node *left;
	Node *right;
}Node;


Node *root = NULL;

Node *create_node(int price, char *product){
	Node *node = (Node*)malloc(sizeof(Node));
	node->price = price;
	node->product = strdup(product);
	node->height = 1;
	node->left = NULL;
	node->right = NULL;
	return node;
}



int get_height(Node* node){
	if(!node) return 0;
	return node->height;
}

int max(int a, int b){
	return (a > b) ? a : b;
}

int calc_height(Node *node){
	if(!node) return 0;
	return max(get_height(node->left), get_height(node->right)) + 1;
}

int calc_balance_vector(Node *node){
	if(!node) return 0;
	return get_height(node->left) - get_height(node->right);
}


Node *left_rotate(Node *node){ //isinya kebalikan
	Node *pivot = node->right;
	Node *cut = pivot->left;
	
	
	pivot->left = node;
	node->right = cut;
	
	node->height = calc_height(node);
	pivot->height = calc_balance_vector(pivot);
	
	return pivot;
}


Node *right_rotate(Node *node){
	Node *pivot = node->left;
	Node *cut = pivot->right;
	
	pivot->right = node;
	node->left = cut;
	
	node->height = calc_height(node);
	pivot->height = calc_height(pivot);
	
	return pivot;
}



Node *insert(Node *node, int price, char* product){
	if(!node){
		return create_node(price, product);
	}
	if(node->price < price){
		node->right = insert(node->right, price, product);	
	}
	else if(node->price > price){
		node->left = insert(node->left, price, product);
	}
	else{
		node->price = price;
		return node;
		
	}
	
	node->height = calc_height(node);
	int balance = calc_balance_vector(node);
	//ll
	if(balance > 1 && price < node->left->price){
		return right_rotate(node);
	}
	if(balance > 1 && price > node->left->price){
		node->left = left_rotate(node->left);
		return right_rotate(node);
	}
	if(balance < -1 && price < node->right->price){
		return left_rotate(node);
	}
	if(balance < -1 && price > node->right->price){
		node->right = right_rotate(node->right);
		return left_rotate(node);
	}
	return node;
}

Node *min_value(Node *node){
	Node *curr = node;
	while(curr->left != NULL){
		curr = curr->left;
	}
	return curr;
}


Node *delete_node(Node *node, int price, char* product){ //delete by price
	if(!node){
		return node;
	}
	if(price < node->price){
		node->left = delete_node(node->left, price, product);
	}
	else if(price > node->price){
		node->right = delete_node(node->right, price, product);
	}
	else{
		if(!node->left || !node->right){
			Node *temp = node->left ? node->left : node->right; //mencek apakah node->left, kalau iya maka node->left, kalau tidak, right
		
			//kasus tanpa anak
			if(!temp){
				temp = node;
				node = NULL;
			}
			else{
				*node = *temp;
			}
			free(temp);
		}
		else{
			Node *temp = min_value(temp);
			node->price = temp->price;
			node->product = strdup(temp->product);
			node->right = delete_node(node->right, temp->price, temp->product);
		}
	}
	if(!node) return node;
	node->height = calc_height(node);
	int balance = calc_balance_vector(node);
	if(balance > 1 && price < node->left->price){
		return right_rotate(node);
	}
	if(balance > 1 && price > node->left->price){
		node->left = left_rotate(node->left);
		return right_rotate(node);
	}
	if(balance < -1 && price < node->right->price){
		return left_rotate(node);
	}
	if(balance < -1 && price > node->right->price){
		node->right = right_rotate(node->right);
		return left_rotate(node);
	}
	return node;
	
}


void inorder(Node *node){
	//lpr
	inorder(node->left);
	printf("%d %s, ", node->price, node->product);
	inorder(node->right);
}













int main(){
	return 0;
}
