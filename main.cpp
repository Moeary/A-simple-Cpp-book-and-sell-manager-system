#include "function.hpp"

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
    vector<book*> books;
    vector<buyer*> buyers;
    vector<order> orders;
    Set_Font();
    orders=loadOrdersFromFile();
    int choice=-1;
    while (true) {
        std::cout << "\x1B[2J\x1B[H"; 
        //逃逸序列清屏
        cout << "Choose an option: " << endl;
        cout << "1. Read books from file" << endl;
        cout << "2. Read buyers from file" << endl;
        cout << "3. Add a book" << endl;
        cout << "4. Add a buyer" << endl;
        cout << "5. Add a order" << endl;
        cout << "6. Show orders" << endl;
        cout << "7. Select count(book money) from order,buyer,book group by order.buyerID having order.bookID=book.bookID and order.buyerID='X'" << endl;
        cout << "0. Exit" << endl;
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
                press_any_key_to_continue();
                break;
            case 4:
                readBuyersFromFile(buyers);
                addBuyer(buyers);
                press_any_key_to_continue();
                break;
            case 5:
                readBooksFromFile(books);
                readBuyersFromFile(buyers);
                addOrder(buyers,books);
                press_any_key_to_continue();
                break;
            case 6:
                readBooksFromFile(books);
                readBuyersFromFile(buyers);//把文件数据都读到vector中去
                showorder(orders,buyers,books);
                press_any_key_to_continue();
                break;
            case 7:
                readBooksFromFile(books);
                readBuyersFromFile(buyers);
                select(orders,buyers,books);
                press_any_key_to_continue();
            case 0:
                flag = 1;
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice, Please choose again" << endl;
                press_any_key_to_continue();
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