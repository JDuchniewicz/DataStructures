/*
    Hashmap implementation for both custom Vector class and regular array
*/

#include <iostream>
#include <Hashmap.hpp>

// this comparator only allows for int values
struct RegularComp
{
    int operator()(int key)
    {
        return (key * 1'000'007) % MAXSIZE;
    }
};

struct StringComp
{
    int operator()(const char* str) //this is some mumbo-jumbo algorithm, maybe very collision-prone
    {
        const char* c = str;
        int hash = 1'007;
        while (*c != '\n')
        {
            hash += (hash * 1'007 + *c++) % MAXSIZE;
        }
        return hash;
    }

};

int main()
{
    Hashmap<int, RegularComp> intMap;
    HashmapArray<int, int, RegularComp> intArrayMap;
    HashmapArray<int, std::string, StringComp> stringArrayMap;

    std::cout << "IntMap insertion" << std::endl;
    // intMap check
    intMap.insert(1);
    intMap.insert(1);
    intMap.insert(2);
    intMap.insert(100);
    intMap.insert(200);

    std::cout << "IntMap removal" << std::endl;
    std::cout << intMap.remove(200) << std::endl;
    std::cout << intMap.remove(100) << std::endl;
    std::cout << intMap.remove(2) << std::endl;
    std::cout << intMap.remove(1) << std::endl;
    std::cout << intMap.remove(1) << std::endl;
    std::cout << intMap.remove(30) << std::endl;

    std::cout << "IntArrayMap insertion" << std::endl;
    // intArrayMap check
    intArrayMap.insert(1, 10);
    intArrayMap.insert(1, 10);
    intArrayMap.insert(2, 20);
    intArrayMap.insert(3, 30);
    intArrayMap.insert(4, 40);

    std::cout << "IntArrayMap get" << std::endl;
    std::cout << intArrayMap.get(1) << std::endl;
    std::cout << intArrayMap.get(2) << std::endl;
    std::cout << intArrayMap.get(2) << std::endl;
    std::cout << intArrayMap.get(3) << std::endl;
    std::cout << intArrayMap.get(6) << std::endl;

    std::cout << "IntArrayMap removal" << std::endl;
    std::cout << intArrayMap.remove(1) << std::endl;
    std::cout << intArrayMap.remove(2) << std::endl;
    std::cout << intArrayMap.remove(2) << std::endl;
    std::cout << intArrayMap.remove(3) << std::endl;
    std::cout << intArrayMap.remove(6) << std::endl;

    return 0;
}