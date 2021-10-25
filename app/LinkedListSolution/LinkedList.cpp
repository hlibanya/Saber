#include "LinkedList.hpp"

#include <exception>
#include <unordered_map>

/*
Binary format desription:
int count: num of elements in list
struct StringInfo [count]
{

    std::string::size_type stringSize
    char stringData[stringSize]
}
int randNodesPositions[count]: indexes of which node`s[n] rand is pointed to
*/

//NOTE:
//every new call should be replaced with alocator call to store all nodes in contiguous memory
//I think it is out of scope of test

//NOTE:
//File mapping may be considered if optimization needed

void List::Serialize(FILE* file)
{
    int writeRes = fwrite(&count, sizeof(count), 1, file);
    if(writeRes < 1) throw std::exception{};
    std::unordered_map<ListNode*, int> map;//node ptr -> node pos in list
    map.reserve(count);
    //POSSIBLE OPTIMIZATION:
    //accumulate n results in local buffer to reduce num of fwrites
    int nodeIndex = 0;
    for(auto node = head; ; node = node->next)
    {
        auto stringSize = node->data.size();
        auto stringData = node->data.data();
        writeRes = fwrite(&stringSize, sizeof(std::string::size_type), 1, file);
        if(writeRes < 1) throw std::exception{};
        fwrite(stringData, stringSize, 1, file);
        if(ferror(file) != 0) throw std::exception{}; //stringSize may be 0

        map[node] = nodeIndex;
        nodeIndex++;
        if (node == tail) break;
    }
    for(auto node = head; ; node = node->next)
    {
        int randNodeIndex = map[node->rand];
        writeRes = fwrite(&randNodeIndex, sizeof(randNodeIndex), 1, file);
        if (writeRes < 1) throw std::exception{};
        if (node == tail) break;
    }
}

//NOTE: 
//Calling Deserialize on non-empty list is not defined
//so I don`t handle this case and assume List is empty
void List::Deserialize(FILE* file)
{
    int readRes = fread(&count, sizeof(count), 1, file);
    if (readRes < 1) throw std::exception{};
    if(count == 0)
    {
        return;
    }
    
    std::unordered_map<int, ListNode*> map;//node pos in list -> node ptr
    map.reserve(count);
    
    head = new ListNode;
    ListNode* currentNode = head;
    ListNode* prevNode = nullptr;
    ListNode* nextNode = nullptr;

    for(int nodeIndex = 0; nodeIndex < count; nodeIndex++)
    {
        std::string::size_type stringSize{};
        readRes = fread(&stringSize, sizeof(stringSize), 1, file);
        if (readRes < 1) throw std::exception{};
        currentNode->data.resize(stringSize);
        fread(currentNode->data.data(), stringSize, 1, file);
        if (ferror(file) != 0) throw std::exception{}; //stringSize may be 0
        
        map[nodeIndex] = currentNode;

        currentNode->prev = prevNode;
        prevNode = currentNode;
        if(nodeIndex != count - 1)//Last node condition
        {
            currentNode->next = new ListNode;
            currentNode = currentNode->next;
        }
    }
    tail = currentNode;

    int nodeIndex = 0;
    for(auto node = head; ; node = node->next)
    {
        int randNodeIndex{};
        readRes = fread(&randNodeIndex, sizeof(int), 1, file);
        if (readRes < 1) throw std::exception{};
        node->rand = map[randNodeIndex];
        nodeIndex++;
        if (node == tail) break;
    }
}

ListNode* List::addNode(std::string str, int rand)
{
    //NOTE: 
    //added only for testing. Probably O(n^2) on adding n nodes
    if (rand > count) throw std::bad_alloc{};
    count++;
    auto newNode = new ListNode;
    newNode->data = str;
    if (head == nullptr)
    {
        head = newNode;
        tail = newNode;
        newNode->rand = head;
    }
    tail->next = newNode;
    newNode->prev = tail;
    tail = newNode;

    ListNode* prev{};
    int nodeIndex{0};
    for (auto node = head; ; node = node->next)
    {
        if (nodeIndex == rand)
        {
            newNode->rand = node;
            break;
        }
        nodeIndex++;
        if (node == tail) break;
    }

    return newNode;
}

List::~List()
{
    if (count == 1)
    {
        delete head;
        return;
    }

    for (auto node = head->next; ; node = node->next)
    {
        delete node->prev;
        if (node == tail) break;
    }
    delete tail;
}
