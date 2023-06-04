#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <algorithm>
#include <sstream>

#include "book.hpp"
#include "buyer.hpp"
#include "order.hpp"

using namespace std;

void showBook(const std::vector<book*>& books) {
    std::cout << "Current books in the library: " << std::endl;
    std::cout << "Book ID\tBook Name\tAuthor\tPublishing Company\tPrice" << std::endl;
    for (const auto& b : books) {
        std::cout << b->getbook_ID() << "\t" << b->getbook_name() << "\t        " << b->getauthor() << "\t" << b->getpublishing() << "\t                " << b->getprice() << std::endl;
    }
}
void showBuyer(const std::vector<buyer*>& buyers) {
    std::cout << "Current buyers in the library:" << std::endl;
    std::cout << "Name\tBuyer ID\tAddress\tPay Amount" << std::endl;
    std::cout << "Member:" << std::endl;
    for (const auto& b : buyers) {
        if (b->is_member() && !b->is_honoured()) {
            member* m = dynamic_cast<member*>(b); //动态类型转换为对应的类
            std::cout << m->getbuyname() << "\t" << m->getid() << "\t" << m->getaddress() << "\t" << m->getpay() << std::endl;
        }
    }

    std::cout << "Honoured Guest:" << std::endl;
    for (const auto& b : buyers) {
        if (b->is_honoured()) { //判断是否为贵宾
            honoured_guest* h = dynamic_cast<honoured_guest*>(b);
            std::cout << h->getbuyname() << "\t" << h->getid() << "\t" << h->getaddress() << "\t" << h->getpay() << std::endl;
        }
    }
    std::cout << "layfolk:" << std::endl;
    for (const auto& b : buyers) {
        if (!b->is_member() && !b->is_honoured()) {
            std::cout << b->getbuyname() << "\t" << b->getid() << "\t" << b->getaddress() << "\t" << b->getpay() << std::endl;
        }
    }
}


void readBuyersFromFile(std::vector<buyer*>& buyers) {
    std::ifstream buyerFile("buyer.dat");
    buyers.clear();
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
bool bookExists(std::vector<book*>& books,string id) {
    for(const auto& b : books) {
        if(b->getbook_ID() == id) {
            return true;
        }
    }
    return false;
}

bool buyerExists(std::vector<buyer*>& buyers,int id) {
    for(const auto& b : buyers) {
        if(b->getid() == id) {
            return true;
        }
    }
    return false;
}


void readBooksFromFile(std::vector<book*>& books) {
    std::ifstream bookFile("book.dat");
    books.clear();
    if (bookFile.is_open()) {
        string bookID, bookName, author, publishing;
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



void addBook(std::vector<book*>& books) {
    string bookID, bookName, author, publishing;
    double price;

    // 提示用户输入书籍信息
    std::cout << "Enter book ID: ";
    std::cin >> bookID;
    if(bookExists(books, bookID)) {
        std::cout << "Book ID already exists" << std::endl;
        return;
    }
    cout << "Enter book name: ";
    cin >> bookName;
    cout << "Enter author name: ";
    cin >> author;
    cout << "Enter publishing company: ";
    cin >> publishing;
    cout << "Enter price: ";
    cin >> price;

    // 提示书籍成功添加
    std::cout << "Book added successfully!" << std::endl;
    std::ofstream bookFile("book.dat", std::ios::app);
    if (bookFile.is_open()) {
        bookFile << bookID << " " << bookName << " " << author << " " << publishing << " " << price << std::endl;
        bookFile.close();
        std::cout << "Book saved to file!" << std::endl;
    }
    else {
        std::cout << "Error saving book to file!" << std::endl;
    }
}

void addBuyer(std::vector<buyer*>& buyers) {

    int buyerType = -1; // 默认为贵宾

    do {
        std::string name, address;
        int buyerID, leaguerGrade;
        double pay;

        // 提示用户输入买家信息
        std::cout << "Enter buyer ID: ";
        std::cin >> buyerID;
        if(buyerExists(buyers, buyerID)) {
            std::cout << "Buyer ID already exists" << std::endl;
            return;
        }
        std::cout << "Enter buyer name: ";
        std::cin >> name;
        

        // 根据用户输入的买家类型选择不同的添加方法
        std::cout << "Enter buyer type (0 for layfolk, 1 for member, 2 for honoured guest): ";
        std::cin >> buyerType;
        switch (buyerType) {
        case 0: // 普通人
            std::cout << "Enter address: ";
            std::cin >> address;
            std::cout << "Enter pay amount: ";
            buyers.push_back(new layfolk(name, buyerID, address,0));
            break;
        case 1: // 会员
            std::cout << "Enter leaguer grade: ";
            std::cin >> leaguerGrade;
            std::cout << "Enter address: ";
            std::cin >> address;
            std::cout << "Enter pay amount: ";
            std::cin >> pay;
            buyers.push_back(new member(name, buyerID, leaguerGrade, address,0));
            break;
        case 2: // 贵宾
            std::cout << "Enter discount rate: ";
            std::cin >> pay;
            std::cout << "Enter address: ";
            std::cin >> address;
            std::cout << "Enter pay amount: ";
            std::cin >> pay;
            buyers.push_back(new honoured_guest(name, buyerID, pay, address,0));
            break;
        default: // 非法输入
            std::cout << "Invalid buyer type!" << std::endl;
            continue;
        }

        // 提示买家成功添加
        std::cout << "Buyer added successfully!" << std::endl;

        // 将新买家保存到文件
        std::ofstream buyerFile("buyer.dat", std::ios::app);
        if (buyerFile.is_open()) {
            buyerFile << name << " " << buyerID << " " << buyerType << " " << address << " " << pay << std::endl;
            buyerFile.close();
            std::cout << "Buyer saved to file!" << std::endl;
        }
        else {
            std::cout << "Error saving buyer to file!" << std::endl;
        }
        
        // 继续提醒用户可以继续添加，或者输入负数退出添加
        std::cout << "Enter any positive number to add another buyer, or any negative number to exit: ";
        std::cin >> buyerType;
    } while (buyerType >= 0);
}
void saveOrderToFile(const order& o) {
    std::ofstream ofs("order.dat", std::ios::app);
    if (ofs) {
        ofs << o.getBuyerID() << " ";
        for (const auto& bookID : o.getBookIDs()) {
            ofs << bookID << ",";
        }
        ofs << " " << o.getTime() << std::endl;
    }
}

std::vector<order> loadOrdersFromFile() {
    std::vector<order> orders;

    std::ifstream ifs("order.dat");
    if (ifs) {
        std::string line;
        while (std::getline(ifs, line)) {
            std::istringstream iss(line);
            std::string buyerID;
            std::getline(iss, buyerID, ' ');

            std::vector<std::string> bookIDs;
            std::string bookID;
            std::getline(iss, bookID, ' ');
            std::istringstream bookISS(bookID);
            while (std::getline(bookISS, bookID, ',')) {
                bookIDs.push_back(bookID);
            }

            std::time_t time;
            iss >> time;

            orders.emplace_back(buyerID, bookIDs, time);
        }
    }

    return orders;
}

void addOrder(std::vector<buyer*>& buyers, std::vector<book*>& books) {
    int buyerID;
    std::cout << "Enter buyer ID: ";
    std::cin >> buyerID;
    if (!buyerExists(buyers, buyerID)) {
        std::cout << "Invalid buyer ID!" << std::endl; //查找是否存在用户id 不存在就返回
        return;
    }

    std::vector<std::string> bookIDs;
    bool exit = false;
    do {
        std::string bookID;
        std::cout << "Enter book ID (enter -1 to exit): ";
        std::cin >> bookID;
        if (bookID == "-1") {
            exit = true;
        }
        else{
            /*迭代器查找,找到了push到bookID中去*/
            auto it = std::find_if(books.begin(), books.end(),[&bookID](const auto& b) {return b->getbook_ID() == bookID; });
            if (it == books.end()) {
                std::cout << "Invalid book ID!" << std::endl;
            }
            else {
                bookIDs.push_back(bookID);
            }
        }
    } while (!exit);

    if (bookIDs.empty()) {
        std::cout << "No book added!" << std::endl;
        return;
    }
    order o(std::to_string(buyerID), bookIDs);
    saveOrderToFile(o);
    std::cout << "Order added successfully!" << std::endl;
}
void showorder(std::vector<order>& orders, std::vector<buyer*>& buyers, std::vector<book*>& books) {
    int len = orders.size();
    for (int i = 0; i < len; i++) {
        std::string buyerID = orders[i].getBuyerID();
        std::vector<std::string> bookIDs = orders[i].getBookIDs();
        
        // 输出买家信息
        for (auto& b : buyers) {
            if (to_string(b->getid()) == buyerID) {
                std::cout << b->getbuyname() << " ";
                if(b->is_honoured()&&!b->is_member()){
                    std::cout << "贵宾有请 ";
                }
                if(b->is_member()&&!b->is_honoured()){
                    std::cout << "会员有请 ";
                }
                else{
                    std::cout << "乡巴佬有请 ";
                }
                break;
            }
        }
        cout<<endl;
        // 输出书籍信息
        cout<<"购买书籍: ";
        for (auto& book_id : bookIDs) {
            for (auto& b : books) {
                if (b->getbook_ID() == book_id) {
                    std::cout << "书名" << b->getbook_name() << " 作者:" << b->getauthor() <<" 价格:"<<b->getprice()<<endl;
                    break;
                }
            }
        }
        std::time_t time = orders[i].getTime();
        std::tm* time_info = std::localtime(&time);
        std::cout << "购买时间: " << std::asctime(time_info) << std::endl;
    }
    cout<<endl;
}
/*
 * 
 * 　　┏┓　　　┏┓+ +
 * 　┏┛┻━━━┛┻┓ + +
 * 　┃　　　　　　　┃ 　
 * 　┃　　　━　　　┃ ++ + + +
 *  ████━████ ┃+
 * 　┃　　　　　　　┃ +
 * 　┃　　　┻　　　┃
 * 　┃　　　　　　　┃ + +
 * 　┗━┓　　　┏━┛
 * 　　　┃　　　┃　　　　　　　　　　　
 * 　　　┃　　　┃ + + + +
 * 　　　┃　　　┃
 * 　　　┃　　　┃ +  神兽保佑
 * 　　　┃　　　┃    代码无bug　　
 * 　　　┃　　　┃　　+　　　　　　　　　
 * 　　　┃　 　　┗━━━┓ + +
 * 　　　┃ 　　　　　　　┣┓
 * 　　　┃ 　　　　　　　┏┛
 * 　　　┗┓┓┏━┳┓┏┛ + + + +
 * 　　　　┃┫┫　┃┫┫
 * 　　　　┗┻┛　┗┻┛+ + + +
 * 
 */

int main(int argc, char** argv){
    std::vector<book*> books;
    std::vector<buyer*> buyers;
    std::vector<order> orders;

    int choice;
    while (true) {
        cout << "Choose an option: " << std::endl;
        cout << "1. Read books from file" << std::endl;
        cout << "2. Read buyers from file" << std::endl;
        cout << "3. Add a book" << std::endl;
        cout << "4. Add a buyer" << std::endl;
        cout << "5. Add a order" << std::endl;
        cout << "6. show orders" << std::endl;
        cout << "0. Exit" << std::endl;
        cin >> choice;

        // 清除输入缓冲区
        cin.clear();
        
        int flag = 0;
        switch (choice) {
            case 1:
                readBooksFromFile(books);
                showBook(books);
                break;
            case 2:
                readBuyersFromFile(buyers);
                showBuyer(buyers);
                break;
            case 3:
                readBooksFromFile(books);
                addBook(books);
                break;
            case 4:
                readBuyersFromFile(buyers);
                addBuyer(buyers);
                break;
            case 5:
                readBooksFromFile(books);
                readBuyersFromFile(buyers);
                addOrder(buyers,books);
                break;
            case 6:
                orders=loadOrdersFromFile();
                readBooksFromFile(books);
                readBuyersFromFile(buyers);//把文件数据都读到vector中去
                showorder(orders,buyers,books);
                break;
            case 0:
                flag = 1;
                std::cout << "Exiting..." << std::endl;
                break;
            default:
                std::cout << "Invalid choice, Please choose again" << std::endl;
                break;
            if (flag == 1) {
                break;
            }
        }
    }

    // 其他逻辑...

    // 清理资源，释放内存
    for (book* b : books) {
        delete b;
    }
    for (buyer* b : buyers) {
        delete b;
    }
    return 0;
}