#pragma once
#include <iostream>
//#include "LinkedBased\BinaryTree.cpp"
#include "LinkedBased\BinarySearchTree.cpp"
#//include "LinkedBased\AVLTree.cpp"
//#include "ArrayBased\MaxHeap.cpp"
//#include "ArrayBased\MinHeap.cpp"
using namespace std;

template<class DataType>
void printItem(DataType & item){
	cout<<item<<" ";
}

//template<class DataType>
//void TestBinaryTree(BinaryTree<DataType> & tree, BinaryTree<DataType> & tree2){
//	int temp;
//	DataType x;
//	bool exit = false;
//	do {
//		cout<<"*****************************************************"<<endl;
//		cout<<"Choose a function:"<<endl;
//		cout<<"[1] isEmpty \n[2] getHeight \n[3] getNumberOfNode \n[4] add \n[5] remove \n[6] clear ";
//		cout<<"\n[7] contains \n[8] isBST \n[9] isComplete \n[10] isBalanced \n[11] isFull ";
//		cout<<"\n[12] LevelOrderTraverse \n[13] preorderTraverse ";
//		cout<<"\n[14] inorderTraverse \n[15] postorderTraverse";
//		cout<<"\n[0] Exit Tree Tester \n";
//		cout<<"*****************************************************"<<endl;
//
//		cin>>temp;
//		switch (temp){
//		case 0:
//			exit = true;
//			break;
//
//		case 1:
//			if (tree.isEmpty())
//				cout<<"Tree is Empty"<<endl;
//			else
//				cout<<"Tree is NOT empty"<<endl;
//			break;
//
//		case 2:
//			cout<<"Tree's Height is "<<tree.getHeight()<<endl;
//			break;
//
//		case 3:
//			cout<<"Tree's nodes = "<<tree.getNumberOfNodes()<<endl;
//			break;
//
//		case 4:
//			cout<<"Enter items to Add in order, -1 to break: ";
//			cin>>x;
//			while (x != -1){
//				tree.add(x);
//				cin>>x;
//			}
//			break;
//
//		case 5:
//			cout<<"Enter item to remove: ";
//			cin>>x;
//			tree.remove(x);
//			break;
//
//		case 6:
//			tree.clear();
//			cout<<"Tree is cleared"<<endl;
//			break;
//
//		case 7:
//			cout<<"Enter item to check if it is in the tree: ";
//			cin>>x;
//			if (tree.contains(x))
//				cout<<"It exists in the tree"<<endl;
//			else
//				cout<<"It does NOT exist in the tree"<<endl;
//			break;
//			
//		case 8:
//			if (tree.isBST())
//				cout<<"Tree is BST"<<endl;
//			else
//				cout<<"Tree is NOT BST"<<endl;
//			break;
//
//		case 9:
//			if (tree.isComplete())
//				cout<<"Tree is Complete"<<endl;
//			else
//				cout<<"Tree is NOT Complete"<<endl;
//			break;
//
//		case 10:
//			if (tree.isBalanced())
//				cout<<"Tree is Balanced"<<endl;
//			else
//				cout<<"Tree is NOT Balanced"<<endl;
//			break;
//		
//		case 11:
//			if (tree.isFull())
//				cout<<"Tree is Full"<<endl;
//			else
//				cout<<"Tree is NOT Full"<<endl;
//			break;
//
//		case 12:
//			cout<<"Tree's items in Level Order Traversal: ";
//			tree.LevelOrderTraverse(printItem);
//			cout<<endl;
//			break;
//			
//		case 13:
//			cout<<"Tree's items in Pre-Order Traversal: ";
//			tree.preorderTraverse(printItem);
//			cout<<endl;
//			break;
//
//		case 14:
//			cout<<"Tree's items in In-Order Traversal: ";
//			tree.inorderTraverse(printItem);
//			cout<<endl;
//			break;
//
//		case 15:
//			cout<<"Tree's items in Post-Order Traversal: ";
//			tree.postorderTraverse(printItem);
//			cout<<endl;
//			break;
//		}
//
//	} while (!exit);
//
//}

template<class DataType>
void TestBinarySearchTree(BinarySearchTree <DataType> & tree, BinarySearchTree<DataType> & BST){
	int temp;
	DataType x;
	bool exit = false;
	do {
		cout<<"*****************************************************"<<endl;
		cout<<"Choose a function:"<<endl;
		cout<<"[1] isEmpty \n[2] getHeight \n[3] getNumberOfNode \n[4] getMaxItem \n[5] getMinItem \n[6] add \n[7] remove \n[8] clear ";
		cout<<"\n[9] contains \n[10] isBST \n[11] isFull \n[12] MakeBalanced \n[13] LevelOrderTraverse \n[14] preorderTraverse ";
		cout<<"\n[15] inorderTraverse \n[16] postorderTraverse \n[0] Exit Tree Tester \n";
		cout<<"*****************************************************"<<endl;

		cin>>temp;
		switch (temp){
		case 0:
			exit = true;
			break;

		case 1:
			if (tree.isEmpty())
				cout<<"Tree is Empty"<<endl;
			else
				cout<<"Tree is NOT empty"<<endl;
			break;

		case 2:
			cout<<"Tree's Height is "<<tree.getHeight()<<endl;
			break;

		case 3:
			cout<<"Tree's nodes = "<<tree.getNumberOfNodes()<<endl;
			break;


		case 4:
			cout<<"Max value is "<<tree.getMaxItem()<<endl;
			break;

		case 5:
			cout<<"Min value is "<<tree.getMinItem()<<endl;
			break;

		case 6:
			cout<<"Enter items to Add in order, -1 to break: ";
			cin>>x;
			while (x != -1){
				tree.add(x);
				cin>>x;
			}
			break;

		case 7:
			cout<<"Enter item to remove: ";
			cin>>x;
			tree.remove(x);
			break;

		case 8:
			tree.clear();
			cout<<"Tree is cleared"<<endl;
			break;

		case 9:
			cout<<"Enter item to check if it is in the tree: ";
			cin>>x;
			if (tree.contains(x))
				cout<<"It exists in the tree"<<endl;
			else
				cout<<"It does NOT exist in the tree"<<endl;
			break;
			
		case 10:
			if (tree.isBST())
				cout<<"Tree is BST"<<endl;
			else
				cout<<"Tree is NOT BST"<<endl;
			break;

		case 11:
			if (tree.isFull())
				cout<<"Tree is FULL"<<endl;
			else
				cout<<"Tree is NOT FULL"<<endl;
			break;

		case 12:
			if (tree.MakeBalanced())
				cout<<"Tree is perfectly Balanced"<<endl;
			else
				cout<<"Tree is Balanced but not same Height"<<endl;
			break;

		case 13:
			cout<<"Tree's items in Level Order Traversal: ";
			tree.LevelOrderTraverse(printItem);
			cout<<endl;
			break;
			
		case 14:
			cout<<"Tree's items in Pre-Order Traversal: ";
			tree.preorderTraverse(printItem);
			cout<<endl;
			break;

		case 15:
			cout<<"Tree's items in In-Order Traversal: ";
			tree.inorderTraverse(printItem);
			cout<<endl;
			break;

		case 16:
			cout<<"Tree's items in Post-Order Traversal: ";
			tree.postorderTraverse(printItem);
			cout<<endl;
			break;

		}

	} while (!exit);

}

//template<class DataType>
//void TestAVLTree(AVLTree <DataType> & tree){
//	int temp;
//	DataType x;
//	bool exit = false;
//	do {
//		cout<<"*****************************************************"<<endl;
//		cout<<"Choose a function:"<<endl;
//		cout<<"[1] isEmpty \n[2] getHeight \n[3] getNumberOfNode \n[4] getMaxItem \n[5] getMinItem \n[6] add \n[7] remove \n[8] clear ";
//		cout<<"\n[9] contains \n[10] isFull \n[11] LevelOrderTraverse \n[12] preorderTraverse ";
//		cout<<"\n[13] inorderTraverse \n[14] postorderTraverse \n[0] Exit Tree Tester \n";
//		cout<<"*****************************************************"<<endl;
//
//		cin>>temp;
//		switch (temp){
//		case 0:
//			exit = true;
//			break;
//
//		case 1:
//			if (tree.isEmpty())
//				cout<<"Tree is Empty"<<endl;
//			else
//				cout<<"Tree is NOT empty"<<endl;
//			break;
//
//		case 2:
//			cout<<"Tree's Height is "<<tree.getHeight()<<endl;
//			break;
//
//		case 3:
//			cout<<"Tree's nodes = "<<tree.getNumberOfNodes()<<endl;
//			break;
//
//
//		case 4:
//			cout<<"Max value is "<<tree.getMaxItem()<<endl;
//			break;
//
//		case 5:
//			cout<<"Min value is "<<tree.getMinItem()<<endl;
//			break;
//
//		case 6:
//			cout<<"Enter items to Add in order, -1 to break: ";
//			cin>>x;
//			while (x != -1){
//				tree.add(x);
//				cin>>x;
//			}
//			break;
//
//		case 7:
//			cout<<"Enter item to remove: ";
//			cin>>x;
//			tree.remove(x);
//			break;
//
//		case 8:
//			tree.clear();
//			cout<<"Tree is cleared"<<endl;
//			break;
//
//		case 9:
//			cout<<"Enter item to check if it is in the tree: ";
//			cin>>x;
//			if (tree.contains(x))
//				cout<<"It exists in the tree"<<endl;
//			else
//				cout<<"It does NOT exist in the tree"<<endl;
//			break;
//			
//		case 10:
//			if (tree.isFull())
//				cout<<"Tree is Full"<<endl;
//			else
//				cout<<"Tree is NOT Full"<<endl;
//			break;
//
//		case 11:
//			cout<<"Tree's items in Level Order Traversal: ";
//			tree.LevelOrderTraverse(printItem);
//			cout<<endl;
//			break;
//			
//		case 12:
//			cout<<"Tree's items in Pre-Order Traversal: ";
//			tree.preorderTraverse(printItem);
//			cout<<endl;
//			break;
//
//		case 13:
//			cout<<"Tree's items in In-Order Traversal: ";
//			tree.inorderTraverse(printItem);
//			cout<<endl;
//			break;
//
//		case 14:
//			cout<<"Tree's items in Post-Order Traversal: ";
//			tree.postorderTraverse(printItem);
//			cout<<endl;
//			break;
//
//		}
//
//	} while (!exit);
//
//}

//template<class DataType>
//void TestHeap(MinHeap<DataType> & heap){
//	int temp;
//	DataType x;
//	bool exit = false;
//	do {
//		cout<<"*****************************************************"<<endl;
//		cout<<"Choose a function:"<<endl;
//		cout<<"[1] isEmpty \n[2] getHeight \n[3] getNumberOfNode \n[4] peekTop \n[5] add \n[6] remove \n[7] clear ";
//		cout<<"\n[8] LevelOrderTraverse \n[0] Exit Tree Tester \n";
//		cout<<"*****************************************************"<<endl;
//
//		cin>>temp;
//		switch (temp){
//		case 0:
//			exit = true;
//			break;
//
//		case 1:
//			if (heap.isEmpty())
//				cout<<"Heap is Empty"<<endl;
//			else
//				cout<<"Heap is NOT empty"<<endl;
//			break;
//
//		case 2:
//			cout<<"Heap's Height is "<<heap.getHeight()<<endl;
//			break;
//
//		case 3:
//			cout<<"Heap's nodes = "<<heap.getNumberOfNodes()<<endl;
//			break;
//
//
//		case 4:
//			cout<<"Top value is "<<heap.peekTop()<<endl;
//			break;
//
//		case 5:
//			cout<<"Enter items to Add in order, -1 to break: ";
//			cin>>x;
//			while (x != -1){
//				heap.add(x);
//				cin>>x;
//			}
//			break;
//
//		case 6:
//			if(heap.remove())
//				cout<<"Item is removed"<<endl;
//			else
//				cout<<"Item is NOT removed"<<endl;
//			break;
//
//		case 7:
//			heap.clear();
//			cout<<"Heap is cleared"<<endl;
//			break;
//
//		case 8:
//			cout<<"Heap's items in Level Order Traversal: ";
//			heap.LevelOrderTraverse(printItem);
//			cout<<endl;
//			break;
//		}
//
//	} while (!exit);
//
//}


void main(){
	BinarySearchTree<int> BST, BST2;
	TestBinarySearchTree(BST, BST2);
}


