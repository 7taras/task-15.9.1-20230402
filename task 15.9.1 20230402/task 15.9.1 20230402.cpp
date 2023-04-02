// task 15.9.1 20230402.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "UsersData.h"
#include "SHA1.h"

int main()
{
    UsersData usersData4chat;
    usersData4chat.add((char*)"pasha32", (char*)sha1((char*)"pasha32", 7));
    std::cout << usersData4chat.find((char*)"pasha32") << "\n";
    usersData4chat.remove((char*)"pasha32");    
}

