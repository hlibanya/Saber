#include <cstdio>
#include <string>
struct ListNode {
    ListNode *      prev{};
    ListNode *      next{};
    ListNode *      rand{}; // указатель на произвольный элемент данного списка, либо NULL
    std::string     data{};
};

class List {
public:
    void Serialize   (FILE * file);  // сохранение в файл (файл открыт с помощью fopen(path, "wb"))
    void Deserialize (FILE * file);  // загрузка из файла (файл открыт с помощью fopen(path, "rb"))
    
    ListNode* getTail() { return tail; }
    ListNode* getHead() { return head; }
    ListNode* addNode(std::string str, int rand);
    
    List() = default;
    List(List&&) = default;
    List& operator=(List&&) = default;
    List(const List&) = default;
    List& operator=(const List&) = default;
    ~List();
private:
    ListNode* head{};
    ListNode* tail{};
    int       count{};
};
