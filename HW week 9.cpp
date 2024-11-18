#include <iostream>
#include <string>
using namespace std;

// Cấu trúc lưu thông tin một file
struct FileNode {
    string fileName;     // Tên file
    double fileSize;     // Kích thước file (MB)
    string createdDate;  // Ngày tạo (định dạng: YYYY-MM-DD)
    FileNode* next;      // Con trỏ tới nút tiếp theo

    // Constructor khởi tạo file
    FileNode(string name, double size, string date)
        : fileName(name), fileSize(size), createdDate(date), next(nullptr) {}
};

// Cấu trúc danh sách liên kết đơn
struct FileLinkedList {
    FileNode* head; // Con trỏ đầu danh sách

    // Khởi tạo danh sách rỗng
    FileLinkedList() : head(nullptr) {}

    // Hàm thêm file theo thứ tự thời gian
    void addFile(string name, double size, string date) {
        FileNode* newNode = new FileNode(name, size, date);

        // Trường hợp danh sách rỗng hoặc file mới có ngày tạo sớm hơn
        if (head == nullptr || head->createdDate > date) {
            newNode->next = head;
            head = newNode;
        } else {
            // Tìm vị trí thích hợp để chèn file
            FileNode* current = head;
            while (current->next != nullptr && current->next->createdDate <= date) {
                current = current->next;
            }
            newNode->next = current->next;
            current->next = newNode;
        }
    }

    // Hàm tính tổng kích thước các file
    double calculateTotalSize() {
        double totalSize = 0.0;
        FileNode* current = head;
        while (current != nullptr) {
            totalSize += current->fileSize;
            current = current->next;
        }
        return totalSize;
    }

    // Loại bỏ file có kích thước nhỏ nhất để giảm tổng dung lượng
    void removeSmallestFile() {
        if (head == nullptr) return; // Danh sách rỗng

        FileNode* prev = nullptr;
        FileNode* current = head;
        FileNode* smallestPrev = nullptr;
        FileNode* smallest = head;

        // Tìm file có kích thước nhỏ nhất
        while (current != nullptr) {
            if (current->fileSize < smallest->fileSize) {
                smallest = current;
                smallestPrev = prev;
            }
            prev = current;
            current = current->next;
        }

        // Loại bỏ file nhỏ nhất
        if (smallestPrev == nullptr) {
            // Trường hợp file nhỏ nhất là head
            head = head->next;
        } else {
            smallestPrev->next = smallest->next;
        }
        delete smallest;
    }

    // Hàm hiển thị danh sách file
    void displayFiles() {
        FileNode* current = head;
        while (current != nullptr) {
            cout << "File Name: " << current->fileName << endl;
            cout << "Size: " << current->fileSize << " MB" << endl;
            cout << "Created Date: " << current->createdDate << endl;
            cout << "---------------------------" << endl;
            current = current->next;
        }
    }
};

