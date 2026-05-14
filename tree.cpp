#include <iostream>
using namespace std;

class tree
{
public:    int data;
    tree* left;
    tree* right;
    tree(int value)    {
        data = value;
        left = NULL;
        right = NULL;
    }
};

void insertAtLeft(tree* &root, int value)
{
    tree* n = new tree(value);
    if(root == NULL)    {
        root = n;
        return;
    }
    root->left = n;
}

void insertAtRight(tree* &root, int value)
{
    tree* n = new tree(value);
    if(root == NULL)    {
        root = n;
        return;
    }
    root->right = n;
}

void display(tree* root)
{
    if(root == NULL)    {
        return;
    }
    cout << root->data << " ";
    display(root->left);
    display(root->right);
}

int main()
{
    tree* root = NULL;
    insertAtLeft(root, 1);
    insertAtRight(root, 2);
    insertAtLeft(root->left, 3);
    insertAtRight(root->left, 4);
    display(root);
    return 0;
}