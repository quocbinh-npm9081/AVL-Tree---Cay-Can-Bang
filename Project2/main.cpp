#include<iostream>
using namespace std;

struct AVLNODE {
	int key;
	int height;
	AVLNODE* left;
	AVLNODE* right;
};
typedef AVLNODE* node;

void initNode(node &root) {
	root = NULL;
}
int height(node root) { // trả về độ cao của cây
	int h = 0;
	if (root != NULL)
	{
		int h_right = height(root->right);
		int h_left = height(root->left);
		return (h_right > h_left ? h_right : h_left) + 1;
	}
	return h;
}

node createNode(int value) {
	node p = new AVLNODE;
	p->key = value;
	p->left = NULL;
	p->right = NULL;
	p->height = 1;
	return p;
}
//xoay trái ( xem readme)
void leftRotate(node& root) {
	node p;
	p = root->right;
	root->right = p->left;
	p->left = root;
	root = p;
}
//xoay phaỉ ( xem readme)
void rightRotate(node& root) {
	node p = root->left;
	root->left = p->right;
	p->right = root;
	root = p;
}
//xoay trai-phai(xem readme)
void leftRightRotate(node& root) {
	if (root == NULL || root->left == NULL) return;
	leftRotate(root->left);
	rightRotate(root);
}
//xoay phai-trai( xem readme)
void rightLeftRotate(node& root) {
	if (root == NULL || root->right == NULL) return;
	rightRotate(root->right);
	leftRotate(root);
}
//can bang trai khi cay bi lech sang ben phai
void leftBalance(node& root) {
	if (height(root->right) - height(root->left)>1) {// cây bị lệch phải
		node q = root->right;
		if (height(q->right) >= height(q->left)) {
			leftRotate(root);
		}
		else {
			rightLeftRotate(root);
		}
	}
}
//can bang phai khi cay bi lech trai
void rightBalance(node& root) {
	if (height(root->right) - height(root->right) < 0 ) {
		node q = root->left;
		if (height(q->left) >= height(q->right)) {
			rightRotate(root);
		}
		else {
			leftRightRotate(root);
		}
	}
}
int calc_diff(node &root) {
	int detal;
	int h_right = height(root->right);
	int h_left = height(root->left);
	return detal = h_left - h_right;
}
void balance(node &root) {
	int delta = calc_diff(root);
	if (delta > 1)// ben trai dai hon ben phai
	{		
		rightBalance(root);
	}
	if (delta < -1)//ben phai dai hon ben trai
	{
		leftBalance( root);
	}
}
//tim kiem node
node findNode(node root, int data) {
	if (root != NULL){
		if (data == root->key)
		{
			return root;
		}
		if (data > root->key) {
			findNode(root->right, data);
		}
		if (data < root->key)
		{
			findNode(root->left, data);
		}
	}
	return 0;
}
//them node ( input)
void insertNode(node& root, int data) {
	if (root == NULL) {
		node p = createNode(data);
		root = p;
	}
	else {	
	
		if (data > root->key)
		{
			insertNode(root->right, data);
	
		
		}
		if (data < root->key)
		{
			insertNode(root->left, data);
		}
	}
	return balance(root);
}
//Duyet preorder( NLR)
void NLR_preorder(node root) {
	if (root != NULL)
	{
		cout << " | " << root->key << " | ";
		NLR_preorder(root->left);
		NLR_preorder(root->right);
	}
}
//Duyeet inorder( LNR)
void LNR_inorder(node root) {
	if (root != NULL)
	{
		NLR_preorder(root->left);
		cout << " | " << root->key << " | ";
		NLR_preorder(root->right);
	}
}
//Duyet postorder( LRN)
void LRN_postorder(node root) {
	if (root != NULL)
	{
		NLR_preorder(root->left);
		NLR_preorder(root->right);
		cout << " | " << root->key << " | ";
	}
}

void removeAll(node &root) {
	if (root != NULL)
	{
		removeAll(root->left);
		removeAll(root->right);
		delete root;
	}
}
void menu(int& choice) {
	cout << "\nNhap lua chon cua ban ";
	cout << "\nNhap 1 de them vao cay AVL";
	cout << "\nNhap 2 de tim kiem ";
	cout << "\nNhap 3 de tim node theo gia tri";
	cout << "\nNhap 4 de duyet preorder_NLR";
	cout << "\nNhap 5 de duyet inorder_LNR";
	cout << "\nNhap 6 de duyet post-order_LRN";
	cin >> choice;
}
int main() {
	node r; 
	int choice;
	initNode(r);
	int data;
	do {
		menu(choice);
		switch (choice)
		{
		case 1:
			do {
				cout << "\nNhap gia tri(-99 break): ";
				cin >> data;
				if (data == -99)break;
				insertNode(r, data);
			} while (true);
			break;
		case 2:
			cout << "\nNhap gia tri node can tim:";
			cin >> data;
			findNode(r , data);
			break;
		case 3:
			break;
		case 4:
			cout << "\nDuyet Preorder( NLR)";
			NLR_preorder(r);
		case 5:
			break;
		case 6:
			cout << "\nDuyet Preorder( NLR)";
			LNR_inorder(r);
			break;
		case 7:
			cout << "\nDuyet Post-order( NLR)";
			LRN_postorder(r);
			break;
			

		default:
			break;
		}
	} while (choice != 0);
	
	

	
	cout << "Duyet preorder: ";
	NLR_preorder(r);
	removeAll(r);
	return 0;
}