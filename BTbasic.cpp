#include<iostream>
using namespace std;

class node{
    public:
    int data;
    node* left;
    node* right;

    node(int data) {
        this->data = data;
        left = right = NULL;
    }
};

static int idx = -1;

node* buildTree(vector<int> preorder) {
    idx++;
    if(preorder[idx] == -1) {
        return NULL;
    }

    node* root = new node(preorder[idx]);
    root->left = buildTree(preorder); //left
    root->right = buildTree(preorder); //right

    return root;
}

int height(node* root) {
    if(root == NULL) {
        return 0;
    }

    int leftHt = height(root->left);
    int rightHt = height(root->right);

    return max(leftHt,rightHt) + 1;
}

void preorderTraverse(node* root) {
    if(root == NULL) {
        return;
    }

    cout<<root->data<<" ";
    preorderTraverse(root->left);
    preorderTraverse(root->right);
}

void inorderTraverse(node* root) {
    if(root == NULL) {
        return;
    }

    inorderTraverse(root->left);
    cout<<root->data<<" ";
    inorderTraverse(root->right);
}

void postorderTraverse(node* root) {
    if(root == NULL) {
        return;
    }

    postorderTraverse(root->left);
    postorderTraverse(root->right);
    cout << root->data << " ";
}

void levelorderTraverse(node* root) {
    queue<node*> q;

    q.push(root);
    q.push(NULL);

    while(!q.empty()) {
        node* curr = q.front();
        q.pop();
        if(curr == NULL && !q.empty()) {
            cout<<endl;
            q.push(NULL);
            continue;
        }

        else if(curr == NULL && q.empty()) {
            break;
        }

        else cout<< curr->data << " ";

        if(curr->left != NULL) {
            q.push(curr->left);
        }

        if(curr->right != NULL) {
            q.push(curr->right);
        }
    }
}

int count(node* root) {
    if(root == NULL) {
        return 0;
    }

    int leftCount = count(root->left);
    int rightCount = count(root->right);

    return leftCount+rightCount+1;
}

int sum(node* root) {
    if(root == NULL) {
        return 0;
    }

    int leftSum = sum(root->left);
    int rightSum = sum(root->right);

    return leftSum+rightSum+root->data;
}

int main() {
    vector<int> preorder = {1,2,-1,-1,3,4,-1,-1,5,-1,-1};

    node* rootnode = buildTree(preorder);

    // cout<<rootnode->data<<endl;
    // cout<<rootnode->left->data<<endl;
    // cout<<rootnode->right->data<<endl;

    // levelorderTraverse(rootnode);

    // cout << height(rootnode) << endl;

    // cout<< count(rootnode) << endl;

    cout << sum(rootnode) << endl;

    return 0;
}