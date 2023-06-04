#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "book.hpp"
#include "buyer.hpp"
#include "order.hpp"

using namespace std;

void readBooksFromFile(std::vector<book*>& books) {
    std::ifstream bookFile("book.dat");
    if (bookFile.is_open()) {
        std::string bookID, bookName, author, publishing;
        double price;
        // 读取book数据并创建book对象
        while (books.size() < 100 && bookFile >> bookID >> bookName >> author >> publishing >> price) {
            books.push_back(new book(bookID, bookName, author, publishing, price));
        }
        bookFile.close();
    }
    else {
        std::cout << "Error opening book.dat file" << std::endl;
        exit(1);
    }
}

void readBuyersFromFile(std::vector<buyer*>& buyers) {
    std::ifstream buyerFile("buyer.dat");
    if (buyerFile.is_open()) {
        std::string name, address;
        int buyerID, leaguerGrade;
        double pay;
        // 读取buyer数据并创建buyer对象
        while (buyers.size() < 100 && buyerFile >> name >> buyerID >> leaguerGrade >> address >> pay) {
            if (leaguerGrade > 0) {
                buyers.push_back(new member(name, buyerID, leaguerGrade, address, pay));
            }
            else if (leaguerGrade == 0) {
                buyers.push_back(new layfolk(name, buyerID, address, pay));
            }
        }
        buyerFile.close();
    }
    else {
        std::cout << "Error opening buyer.dat file" << std::endl;
        exit(1);
    }
}