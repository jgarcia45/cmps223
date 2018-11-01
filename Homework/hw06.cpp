/* Juan Garcia
 * CMPS 223 / Derrick
 * Homework 6
 * May 14, 2013
 */

#include <iostream>
#include <limits>
#include <fstream>
#include <iomanip>
using namespace std;

#ifndef ELEMTYPE
#define ELEMTYPE int
#endif

struct TreeNode
{
    ELEMTYPE data;
    TreeNode *left;
    TreeNode *right;
};

struct BST
{
    TreeNode *root;
};

void initTree(BST *);
void deallocate(BST *);
void deallocateSubtree(TreeNode *);
bool insert(BST *, ELEMTYPE);
bool insertSubtree(TreeNode *, ELEMTYPE);
TreeNode *search(BST *, ELEMTYPE);
TreeNode *searchSubtree(TreeNode *, ELEMTYPE);
void inorderPrint(BST *);
void inorderSubtree(TreeNode *);
bool remove(BST *, ELEMTYPE);
TreeNode *createNode(ELEMTYPE);
void graphAux(int, TreeNode *);

template <class T>
void getData(T &tmp, const char *prompt, int limit = 0)
{
    cout << prompt;
    if(limit)
    {
        cin >> setw(limit) >> tmp;
    }
    else
    {
        cin >> tmp;
    }
    while(cin.fail())
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << prompt;
        if(limit)
        {
            cin >> setw(limit) >> tmp;
        }
        else
        {
            cin >> tmp;
        }
    }
}

int main()
{
    BST tree;
    ELEMTYPE elem;
    TreeNode *result;
    int choice;
    int num;
    char iFile[256];
    ifstream inFile;

    initTree(&tree);

    do
    {
        cout << "           Binary Search Tree Menu" << endl;
        cout << "===============================================" << endl;
        cout << "1. Read values from a file to insert into tree" << endl;
        cout << "2. Search the tree for a value" << endl;
        cout << "3. Delete a value from the tree" << endl;
        cout << "4. Print the values of the tree in sorted order" << endl;
        cout << "5. Print tree" << endl;
        cout << endl;
        cout << "0. Exit" << endl;
        cout << "===============================================" << endl;
        getData(choice, "Enter choice: ");

        switch(choice)
        {
            case 1: cout << "Enter file: ";
                    cin >> setw(256) >> iFile;
                    if(cin.fail())
                    {
                        cout << "File Name is too long" << endl;
                        cout << endl;
                        break;
                    }

                    inFile.open(iFile);
                    if(inFile.fail())
                    {
                        cout << "Couldn't open input file" << endl;
                        cout << endl;
                        break;
                    }
                    while(inFile >> num)
                    {
                        insert(&tree, num);
                    }
                    inFile.close();
                    break;
            case 2: cout << "Enter a value to search for: ";
                    cin >> elem;
                    result = search(&tree, elem);
                    if(result == NULL)
                    {
                        cout << "The value could not be found in the tree." << endl;
                        cout << endl;
                    }
                    else
                    {
                        cout << "Value was found in the tree." << endl;
                        cout << endl;
                    }
                    break;
            case 3: cout << "Enter a value to be deleted: ";
                    cin >> elem;
                    remove(&tree, elem);
                    if(true)
                    {
                        cout << "The value was deleted." << endl;
                        cout << endl;
                    }
                    else
                    {
                        cout << "The value was not found in the tree." << endl;
                        cout << endl;
                    }
                    break;
            case 4: inorderPrint(&tree);
                    cout << endl;
                    break;
            case 5: if(tree.root != NULL)
                    {
                        graphAux(0, tree.root);
                    }
                    cout << endl;
                    break;
            case 0: cout << "Good-bye!" << endl;
                    break;
            default: cout << "Entered Invalid Choice! Try Again." << endl;
        }
    }while(choice != 0);

    deallocate(&tree);

    return 0;
}

void initTree(BST *tree)
{
    tree->root = NULL;
}

void deallocate(BST *tree)
{
    if(tree->root)
    {
        deallocateSubtree(tree->root);
    }
}

void deallocateSubtree(TreeNode *subtree)
{
    if(subtree->left)
    {
        deallocateSubtree(subtree->left);
    }
    if(subtree->right)
    {
        deallocateSubtree(subtree->right);
    }
    delete subtree;
}

bool insert(BST *tree, ELEMTYPE elem)
{
    if(tree->root != NULL)
    {
        return (insertSubtree(tree->root, elem));
    }
    tree->root = createNode(elem);
    return (tree->root);
}

bool insertSubtree(TreeNode *subroot, ELEMTYPE elem)
{
    if(subroot->data == elem)
    {
        cout << "Error... ";
        return false;
    }
    else if(elem < subroot->data)
    {
        if(subroot->left != NULL)
        {
            return(insertSubtree(subroot->left, elem));
        }
        subroot->left = createNode(elem);
        return (subroot->left);
    }
    else
    {
        if(subroot->right != NULL)
        {
            return (insertSubtree(subroot->right, elem));
        }
        subroot->right = createNode(elem);
        return (subroot->right);
    }
}

TreeNode *search(BST *tree, ELEMTYPE elem)
{
    if(tree->root != NULL)
    {
        return (searchSubtree(tree->root, elem));
    }
    return (NULL);
}

TreeNode *searchSubtree(TreeNode *subroot, ELEMTYPE elem)
{
    if(subroot->data == elem)
    {
        return (subroot);
    }
    else if(elem < subroot->data)
    {
        if(subroot->left != NULL)
        {
            return (searchSubtree(subroot->left, elem));
        }
        return (NULL);
    }
    else
    {
        if(subroot->right != NULL)
        {
            return (searchSubtree(subroot->right, elem));
        }
        return (NULL);
    }
}

void inorderPrint(BST *tree)
{
    if(tree->root != NULL)
    {
        inorderSubtree(tree->root);
    }
}

void inorderSubtree(TreeNode *subroot)
{
    if(subroot->left)
    {
        inorderSubtree(subroot->left);
    }

    cout << subroot->data << " ";

    if(subroot->right)
    {
        inorderSubtree(subroot->right);
    }
}

bool remove(BST *tree, ELEMTYPE elem)
{
    bool found = false;
    TreeNode *node = tree->root;
    TreeNode *parent = NULL;
    TreeNode *child = NULL;
    TreeNode *replacement = NULL;
    TreeNode *rparent = NULL;

    while(!found && node != NULL)
    {
        if(elem == node->data)
        {
            found = true;
            break;
        }
        else if(elem < node->data)
        {
            parent = node;
            node = node->left;
        }
        else
        {
            parent = node;
            node = node->right;
        }
    }

    if(!found)
    {
        return false;
    }
    if(node->left && node->right)
    {
        replacement = node->left;
        rparent = node;

        while(replacement->right)
        {
            rparent = replacement;
            replacement = replacement->right;
        }

        node->data = replacement->data;
        node = replacement;
        parent = rparent;
    }

    if(node->left)
    {
        child = node->left;
    }
    else if(node->right)
    {
        child = node->right;
    }
    else
    {
        child = NULL;
    }

    if(parent == NULL)
    {
        tree->root = child;
    }
    else if(node->data <= parent->data)
    {
        parent->left = child;
    }
    else
    {
        parent->right = child;
    }

    delete node;

    return true;
}

TreeNode *createNode(ELEMTYPE tree)
{
    TreeNode *node = NULL;

    try
    {
        node = new TreeNode;
    }
    catch(bad_alloc)
    {
        node = NULL;
    }
    if(node)
    {
        node->data = tree;
    }

    return (node);
}

void graphAux(int width, TreeNode *subroot)
{
    if(subroot != NULL)
    {
        /*if(subroot->right)
        {*/
            graphAux(width + 8, subroot->right);
        //}

        cout << setw(width) << " " << subroot->data << endl;
        //cout << endl;

        /*if(subroot->left)
        {*/
            graphAux(width + 8, subroot->left);
        //}
    }
}
