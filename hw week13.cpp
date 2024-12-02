#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Cấu trúc sản phẩm
struct Product {
    string name;    // Tên sản phẩm
    int quantity;   // Số lượng sản phẩm
    double price;   // Giá tiền một sản phẩm
};

// Cấu trúc node trong hàng đợi
struct Node {
    int cartID;                    // ID giỏ hàng
    vector<Product> items;         // Danh sách sản phẩm trong giỏ
    double totalAmount;            // Tổng tiền trong giỏ hàng
    Node* next;                    // Con trỏ đến node tiếp theo
};

// Cấu trúc hàng đợi
struct Queue {
    Node* front;                   // Phần tử đầu hàng đợi
    Node* rear;                    // Phần tử cuối hàng đợi

    Queue() : front(nullptr), rear(nullptr) {}
};
void enqueue(Queue& q, int cartID, vector<Product> items) {
    Node* newNode = new Node;
    newNode->cartID = cartID;
    newNode->items = items;
    newNode->totalAmount = 0;
    for (const auto& item : items) {
        newNode->totalAmount += item.quantity * item.price;
    }
    newNode->next = nullptr;

    if (q.rear == nullptr) {
        q.front = q.rear = newNode;
    } else {
        q.rear->next = newNode;
        q.rear = newNode;
    }
}
void dequeue(Queue& q) {
    if (q.front == nullptr) {
        cout << "Hàng đợi rỗng, không có người cần thanh toán.\n";
        return;
    }

    Node* temp = q.front;
    q.front = q.front->next;

    if (q.front == nullptr) {
        q.rear = nullptr;
    }

    cout << "Giỏ hàng ID " << temp->cartID << " đã thanh toán xong. Tổng tiền: " << temp->totalAmount << " VND\n";
    delete temp;
}
double calculateTotalRevenue(Queue q) {
    double totalRevenue = 0;
    Node* current = q.front;
    while (current != nullptr) {
        totalRevenue += current->totalAmount;
        current = current->next;
    }
    return totalRevenue;
}
int countProductSold(Queue q, const string& productName) {
    int totalQuantity = 0;
    Node* current = q.front;
    while (current != nullptr) {
        for (const auto& item : current->items) {
            if (item.name == productName) {
                totalQuantity += item.quantity;
            }
        }
        current = current->next;
    }
    return totalQuantity;
}
int main() {
    Queue q;

    // Thêm giỏ hàng vào hàng đợi
    vector<Product> cart1 = {{"A", 2, 10000}, {"B", 1, 20000}};
    vector<Product> cart2 = {{"A", 3, 10000}, {"C", 5, 15000}};
    enqueue(q, 1, cart1);
    enqueue(q, 2, cart2);

    // Loại bỏ người đầu tiên khỏi hàng đợi
    dequeue(q);

    // Tính tổng số tiền thu ngân thu được
    cout << "Tổng doanh thu: " << calculateTotalRevenue(q) << " VND\n";

    // Đếm số lượng sản phẩm "A" đã bán
    cout << "Số lượng sản phẩm A đã bán: " << countProductSold(q, "A") << "\n";

    return 0;
}

