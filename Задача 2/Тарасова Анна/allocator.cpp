#include <iostream>
#include <cmath>
#include <queue>
#include <cstddef>

using namespace std;

struct node
{
    size_t size;
    bool isAvailable;
    void *blockPointer;
    node *parent;
    node *left;
    node *right;
};

class Allocator
{
  private:
    size_t allocatorSize;
    size_t minBlockSize;
    void *allocatorPointer;
    node *rootNode;

    size_t findBlockSize(size_t allocationSize);
    node *searchNode(void *ptr);
    node *createChild(node *block, void *ptr);
    node *allocateBlock(size_t size);
    node *findAvailableBlock(size_t blockSize);
    void printNode(node *block);
    void splitBlock(node *block);
    void freeParent(node *childPointer);

  public:
    Allocator(size_t size);
    void *Alloc(size_t size);
    void Free(void *ptr);
    void Dump();
       
};

Allocator::Allocator(size_t size)
{
    allocatorSize = size;
    allocatorPointer = (void *)malloc(size);

    rootNode = new node;
    rootNode->blockPointer = allocatorPointer;
    rootNode->parent = NULL;
    rootNode->left = NULL;
    rootNode->right = NULL;
    rootNode->isAvailable = true;
    rootNode->size = allocatorSize;

    minBlockSize = 8;
}

void Allocator::Free(void *ptr)
{
    node *nodeToFree = searchNode(ptr);
    if (nodeToFree == NULL){
        
        throw invalid_argument("Block is not allocated");
    }

    nodeToFree->isAvailable = true;
    freeParent(nodeToFree);
}

void Allocator::freeParent(node *childPointer){
    node * parent = childPointer->parent;
    node * leftChild = parent->left;
    node * rightChild = parent->right;

    if(leftChild->isAvailable == true && rightChild->isAvailable == true){
        parent->left = NULL;
        parent->right = NULL;
        delete(leftChild);
        delete(rightChild);
        parent->isAvailable = true;
    }

}

node *Allocator::searchNode(void *ptr)
{
    queue<node *> nodesQueue;
    node *currentNode = NULL;
    nodesQueue.push(rootNode);
    while (!nodesQueue.empty())
    {
        currentNode = nodesQueue.front();
        nodesQueue.pop();
        if (currentNode->blockPointer == ptr && currentNode->left == NULL && currentNode->right == NULL)
        {
            return currentNode;
        }

        if (currentNode->left != NULL)
        {
            nodesQueue.push(currentNode->left);
        }
        if (currentNode->right != NULL)
        {
            nodesQueue.push(currentNode->right);
        }
    }
    return NULL;
}

void Allocator::Dump()
{
    cout << "Allocated memory dump:" << endl;
    printNode(rootNode);
}

void Allocator::printNode(node *block)
{
    cout << "Size: " << block->size << endl;
    cout << "Block is available: " << block->isAvailable << endl;
    if (block->left == NULL && block->right == NULL){
        cout << "Block is not splited." <<endl;
    } else {
        cout << "Block is splited." << endl;
    }
    cout << "Block pointer:" << block->blockPointer << endl;
    cout << "\n"<< endl;
    if (block->left != NULL)
    {
        printNode(block->left);
    }
    if (block->right != NULL)
    {
        printNode(block->right);
    }
}

node *Allocator::createChild(node *current, void *ptr)
{
    node *newNode = new node;
    newNode->blockPointer = ptr;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->isAvailable = true;
    newNode->size = current->size / 2;
    newNode->parent = current;
    return newNode;
}

void Allocator::splitBlock(node *current)
{
    current->left = createChild(current, current->blockPointer);
    char *ptr = (char *)current->blockPointer;
    ptr = ptr + current->size / 2;
    current->right = createChild(current, (void *)ptr);
    current->isAvailable = false;
}

node *Allocator::findAvailableBlock(size_t blockSize)
{

    queue<node *> nodesQueue;
    node *currentNode = NULL;
    node *availableBlock = NULL;
    nodesQueue.push(rootNode);
    while (!nodesQueue.empty())
    {
        currentNode = nodesQueue.front();
        nodesQueue.pop();
        if (currentNode->isAvailable == true && currentNode->size == blockSize)
        {

            currentNode->isAvailable = false;
            return currentNode;
        }
        if (currentNode->isAvailable == true && currentNode->size > blockSize)
        {
            availableBlock = currentNode;
        }

        if (currentNode->left != NULL)
        {
            nodesQueue.push(currentNode->left);
        }
        if (currentNode->right != NULL)
        {
            nodesQueue.push(currentNode->right);
        }
    }
    if (availableBlock != NULL)
    {
        splitBlock(availableBlock);
        availableBlock = availableBlock->left;
        availableBlock->isAvailable = false;
    }

    return availableBlock;
}
void *Allocator::Alloc(size_t allocationSize)
{
    void *resultPointer = NULL;
    size_t blockSize = findBlockSize(allocationSize);
    resultPointer = findAvailableBlock(blockSize)->blockPointer;
    return resultPointer; 
}

size_t Allocator::findBlockSize(size_t allocationSize)
{
    size_t blockSize = allocatorSize;
    if (allocationSize <= minBlockSize)
    {
        blockSize = minBlockSize;
    }
    if (allocationSize > allocatorSize)
    {
        throw bad_alloc();
    }
    for (size_t i = 0; i <= log2(minBlockSize); i++)
    {
        if (allocationSize > allocatorSize / pow(2, i))
        {
            blockSize = allocatorSize / pow(2, --i);
            break;
        }
    }

    return blockSize;
}

int main()
{
    Allocator alloc(32);
    void *AllocatedBlock1 = alloc.Alloc(15);
    void *AllocatedBlock2 = alloc.Alloc(8);
    alloc.Dump();
    alloc.Free(AllocatedBlock1);
    alloc.Dump();
    alloc.Free(AllocatedBlock2);
    alloc.Dump();
    return 0;
}


