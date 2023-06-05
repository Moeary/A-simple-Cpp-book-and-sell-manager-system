#include <Windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <algorithm>
#include <sstream>
#include <cstdio>

#include "book.hpp"
#include "buyer.hpp"
#include "order.hpp"

using namespace std;

void Set_Font(){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    // 设置前景色为白色，背景色为深蓝色，属性为加粗
    SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | BACKGROUND_INTENSITY | BACKGROUND_BLUE);

    HFONT hFont = CreateFontW(16, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
                        DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
                        DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"微软雅黑");
    // 将字体选入设备环境中
    SelectObject((HDC)hConsole, hFont);
}
void press_any_key_to_continue() {
    cout<<"Press input any words to continue . . . "<<endl;
    string t;
    cin>>t;
}

void showBook(const vector<book*>& books) {
    std::cout << "\x1B[2J\x1B[H"; 
    cout << "Current books in the library: " << endl;
    cout << "Book ID\tBook Name\tAuthor\tPublishing Company\tPrice" << endl;
    for (const auto& b : books) {
        cout << b->getbook_ID() << "\t" << b->getbook_name() << "\t\t" << b->getauthor() << "\t" << b->getpublishing() << "\t\t\t" << b->getprice() << endl;
    }
    cout << "Press 1 to query by ID or press any other key to return to the main program." << endl;
    int input;
    cin>>input;

    if (input == 1) {
        cout << "Please enter the ID of the buyer you want to find:" << endl;
        string input1;
        cin>>input1;
        for (const auto& b : books) {
            if (b->getbook_ID() == input1) {
                b->display();
            }
        }
    }
}
void showBuyer(const vector<buyer*>& buyers) {
    std::cout << "\x1B[2J\x1B[H"; 
    cout << "Current buyers in the library:" << endl;
    cout << "Name\tBuyer ID\tAddress\tPay Amount\t type\t\t off?" << endl;

    for (const auto& b : buyers) {
        string type = b->get_type();
        if (type == "member") {
            member* m = dynamic_cast<member*>(b);
            cout << m->getbuyname() << "\t" << m->getid() << "\t\t" << m->getaddress() << "\t\t" << m->getpay() << "\t"<<type<<"\t\t"<<m->getLeaguerGrade()<<endl;
        } else if (type == "honoured_guest") {
            honoured_guest* h = dynamic_cast<honoured_guest*>(b);
            cout << h->getbuyname() << "\t" << h->getid() << "\t\t" << h->getaddress() << "\t" << h->getpay() << "\t"<<type<<"\t"<<h->get_discount_rate()<<endl;
        } else if (type == "layfolk") {
            cout << b->getbuyname() << "\t" << b->getid() << "\t\t" << b->getaddress() << "\t\t" << b->getpay() << "\t"<<type<<"\t\t"<<"no special off"<<endl;
        }
    }
    cout << "Press 1 to query by ID or press any other key to return to the main program." << endl;
    int input;
    cin>>input;

    if (input == 1) {
        cout << "Please enter the ID of the buyer you want to find:" << endl;
        cin>>input;
        for (const auto& b : buyers) {
            if (b->getid() == input) {
                b->display();
            }
        }
    }
}


void readBuyersFromFile(vector<buyer*>& buyers) {
    ifstream buyerFile("buyer.dat");
    buyers.clear();
    if (buyerFile.is_open()) {
        string name, address;
        int buyerID, leaguerGrade;
        int type=-1,fun;
        double pay,rate=1;
        // 读取buyer数据并创建buyer对象
        while (buyerFile >> name >> buyerID >> type >> address>> fun) {
            if (type==0) {
                fun=0;
                buyers.push_back(new layfolk(name, buyerID, address,0));
            }
            else if (type == 1) {
                leaguerGrade=fun;
                buyers.push_back(new member(name, buyerID, leaguerGrade, address, 0));
            }
            else{
                rate=fun;
                buyers.push_back(new honoured_guest(name,buyerID,rate,address,0));
            }
        }
        buyerFile.close();
    }
    else {
        cout << "Error opening buyer.dat file" << endl;
        exit(1);
    }
}
bool bookExists(vector<book*>& books,string id) {
    for(const auto& b : books) {
        if(b->getbook_ID() == id) {
            return true;
        }
    }
    return false;
}

bool buyerExists(vector<buyer*>& buyers,int id) {
    for(const auto& b : buyers) {
        if(b->getid() == id) {
            return true;
        }
    }
    return false;
}


void readBooksFromFile(vector<book*>& books) {
    ifstream bookFile("book.dat");
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
        cout << "Error opening book.dat file" << endl;
        exit(1);
    }
}



void addBook(vector<book*>& books) {
    std::cout << "\x1B[2J\x1B[H"; 
    string bookID, bookName, author, publishing;
    double price;

    // 提示用户输入书籍信息
    cout << "Enter book ID: ";
    cin >> bookID;
    if(bookExists(books, bookID)) {
        cout << "Book ID already exists" << endl;
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
    cout << "Book added successfully!" << endl;
    ofstream bookFile("book.dat", ios::app);
    if (bookFile.is_open()) {
        bookFile << bookID << " " << bookName << " " << author << " " << publishing << " " << price << endl;
        bookFile.close();
        cout << "Book saved to file!" << endl;
    }
    else {
        cout << "Error saving book to file!" << endl;
    }
}

void addBuyer(vector<buyer*>& buyers) {
    std::cout << "\x1B[2J\x1B[H"; 
    int buyerType = -1; // 默认为贵宾

    do {
        string name, address;
        int buyerID, leaguerGrade;
        double pay,rate;
        int fun;

        // 提示用户输入买家信息
        cout << "Enter buyer ID: ";
        cin >> buyerID;
        if(buyerExists(buyers, buyerID)) {
            cout << "Buyer ID already exists" << endl;
            return;
        }
        cout << "Enter buyer name: ";
        cin >> name;
        

        // 根据用户输入的买家类型选择不同的添加方法
        cout << "Enter buyer type (0 for layfolk, 1 for member, 2 for honoured guest): ";
        cin >> buyerType;
        switch (buyerType) {
        case 0: // 普通人
            cout << "Enter address: ";
            cin >> address;
            fun=0;
            buyers.push_back(new layfolk(name, buyerID, address,0));
            break;
        case 1: // 会员
            cout << "Enter leaguer grade: ";
            cin >> leaguerGrade;
            fun=leaguerGrade;
            cout << "Enter address: ";
            cin >> address;
            buyers.push_back(new member(name, buyerID, leaguerGrade, address,0));
            break;
        case 2: // 贵宾
            cout << "Enter discount rate: ";
            cin >> rate;
            cout << "Enter address: ";
            cin >> address;
            fun=rate*100;
            buyers.push_back(new honoured_guest(name, buyerID, rate, address,0));
            break;
        default: // 非法输入
            cout << "Invalid buyer type!" << endl;
            continue;
        }

        // 提示买家成功添加
        cout << "Buyer added successfully!" << endl;

        // 将新买家保存到文件
        ofstream buyerFile("buyer.dat", ios::app);
        if (buyerFile.is_open()) {
            buyerFile << name << " " << buyerID << " " << buyerType << " " << address << " " << 0 <<fun<<endl;
            buyerFile.close();
            cout << "Buyer saved to file!" << endl;
        }
        else {
            cout << "Error saving buyer to file!" << endl;
        }
        
        // 继续提醒用户可以继续添加，或者输入负数退出添加
        cout << "Enter any positive number to add another buyer, or any negative number to exit: ";
        cin >> buyerType;
    } while (buyerType >= 0);
}
void saveOrderToFile(const order& o) {
    ofstream ofs("order.dat", ios::app);
    if (ofs) {
        ofs << o.getBuyerID() << " ";
        for (const auto& bookID : o.getBookIDs()) {
            ofs << bookID << ",";
        }
        ofs << " " << o.getTime() << endl;
    }
}

vector<order> loadOrdersFromFile() {
    vector<order> orders;

    ifstream ifs("order.dat");
    if (ifs) {
        string line;
        while (getline(ifs, line)) {
            istringstream iss(line);
            string buyerID;
            getline(iss, buyerID, ' ');

            vector<string> bookIDs;
            string bookID;
            getline(iss, bookID, ' ');
            istringstream bookISS(bookID);
            while (getline(bookISS, bookID, ',')) {
                bookIDs.push_back(bookID);
            }

            time_t time;
            iss >> time;

            orders.emplace_back(buyerID, bookIDs, time);
        }
    }

    return orders;
}

void addOrder(vector<buyer*>& buyers, vector<book*>& books) {
    std::cout << "\x1B[2J\x1B[H"; 
    int buyerID;
    cout << "Enter buyer ID: ";
    cin >> buyerID;
    if (!buyerExists(buyers, buyerID)) {
        cout << "Invalid buyer ID!" << endl; //查找是否存在用户id 不存在就返回
        return;
    }

    vector<string> bookIDs;
    bool exit = false;
    
    string bookID;
    cout << "Enter book ID (enter -1 to exit): ";
    cin >> bookID;
    if (bookID == "-1") {
        return; 
    }
    else{
        /*迭代器查找,找到了push到bookID中去*/
        auto it = find_if(books.begin(), books.end(),[&bookID](const auto& b) {return b->getbook_ID() == bookID; });
        if (it == books.end()) {
            cout << "Invalid book ID!" << endl;
        }
        else {
            bookIDs.push_back(bookID);
        }
    }

    if (bookIDs.empty()) {
        cout << "No book added!" << endl;
        return;
    }
    order o(to_string(buyerID), bookIDs);
    saveOrderToFile(o);
    cout << "Order added successfully!" << endl;
}
void showorder(vector<order>& orders, vector<buyer*>& buyers, vector<book*>& books) {
    std::cout << "\x1B[2J\x1B[H"; 
    int len = orders.size();
    for (int i = 0; i < len; i++) {
        string buyerID = orders[i].getBuyerID();
        vector<string> bookIDs = orders[i].getBookIDs();
        
        // 输出买家信息
        for (auto& b : buyers) {
            if (to_string(b->getid()) == buyerID) {
                cout << b->getbuyname() << " ";
                string type = b->get_type();
                if(type=="honoured_guest"){
                    cout << "贵宾 ";
                }
                else if(type=="member"){
                    cout << "会员 ";
                }
                else{
                    cout << "普通人";
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
                    cout << "书名" << b->getbook_name() << " 作者:" << b->getauthor() <<" 价格:"<<b->getprice()<<endl;
                    break;
                }
            }
        }
        time_t time = orders[i].getTime();
        tm* time_info = localtime(&time);
        cout << "购买时间: " << asctime(time_info) << endl;
    }
    cout<<endl;
}
void select(vector<order>& orders, vector<buyer*>& buyers, vector<book*>& books){
    std::cout << "\x1B[2J\x1B[H"; 
    int len = orders.size(),buyer_id =-1;
    bool flag = false;
    cin.clear();
    cout<<"Please print your BuyerId"<<endl;
    cin>>buyer_id;
    for (const auto& order : orders) {
        if (order.getBuyerID() == to_string(buyer_id)) {
            for (const auto& b : buyers) {
                if (order.getBuyerID() == to_string(b->getid())) {
                    cout << "Buyer name: " << b->getbuyname() << endl;
                    flag = true;
                    break;
                }
            }
            if (flag) {
                break;
            }
        }
    }

    if (!flag) {
        cout << "Invalid BuyerId" << endl;
        return;
    }
    if(flag == false){
        cout<<"BuyerID is not in order table"<<endl;
        return;
    }
    double sum = 0;
    for (const auto& order : orders) { //嵌套循环查书籍名
        if (order.getBuyerID() == to_string(buyer_id)) {
            for (const auto& book_id : order.getBookIDs()) {
                for (const auto& book : books) {
                    if (book->getbook_ID() == book_id) {
                        sum += book->getprice();
                        break;
                    }
                }
            }
        }
    }
    
    for (int i = 0; i < len; i++) {
        string buyerID = orders[i].getBuyerID();
        for (auto& b : buyers) {
            if (to_string(b->getid()) == buyerID and buyerID == to_string(buyer_id)) {
                string type="-1";
                type=b->get_type();
                cout << "应付: " << sum << endl;
                if (type == "member") {
                    member* m = dynamic_cast<member*>(b);
                    m->setpay(sum);
                    cout <<"事会员"<<endl<< "实付: "<<b->getpay()<<endl;
                }
                else if (type == "honoured_guest") {
                    honoured_guest* h = dynamic_cast<honoured_guest*>(b);
                    h->setpay(sum);
                    cout <<"事贵宾"<<endl<< "实付: "<<h->getpay()<<endl;
                }
                else if( type == "layfolk"){
                     layfolk* l = dynamic_cast<layfolk*>(b);
                     l->setpay(sum);
                     cout <<"事普通人"<< "实付: "<<l->getpay()<<endl;
                }
                else{
                    cout<<"ERROR"<<endl;
                }
                return;
            }
        }
    }
}
