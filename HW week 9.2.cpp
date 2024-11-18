#include <iostream>
#include <string>
#include <unordered_map> // Để sử dụng bảng băm đếm từ
using namespace std;

// Cấu trúc lưu thông tin một từ
struct WordNode {
    string word;        // Từ trong câu
    WordNode* next;     // Con trỏ tới nút tiếp theo

    // Constructor khởi tạo từ
    WordNode(string w) : word(w), next(nullptr) {}
};

// Cấu trúc danh sách liên kết đơn
struct WordLinkedList {
    WordNode* head; // Con trỏ đầu danh sách

    // Khởi tạo danh sách rỗng
    WordLinkedList() : head(nullptr) {}

    // Hàm thêm từ vào cuối danh sách
    void addWord(string w) {
        WordNode* newNode = new WordNode(w);
        if (head == nullptr) {
            head = newNode;
        } else {
            WordNode* current = head;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newNode;
        }
    }

    // Hàm tìm từ xuất hiện nhiều nhất
    string findMostFrequentWord() {
        unordered_map<string, int> wordCount; // Bảng băm đếm số lần xuất hiện
        WordNode* current = head;
        while (current != nullptr) {
            wordCount[current->word]++;
            current = current->next;
        }

        string mostFrequent;
        int maxCount = 0;
        for (const auto& pair : wordCount) {
            if (pair.second > maxCount) {
                maxCount = pair.second;
                mostFrequent = pair.first;
            }
        }
        return mostFrequent;
    }

    // Hàm loại bỏ từ láy (ví dụ: "xanh xanh")
    void removeRedundantWords() {
        WordNode* current = head;
        while (current != nullptr && current->next != nullptr) {
            if (current->word == current->next->word) {
                // Loại bỏ nút lặp
                WordNode* redundant = current->next;
                current->next = redundant->next;
                delete redundant;
            } else {
                current = current->next;
            }
        }
    }

    // Hàm đếm số từ khác nhau trong câu
    int countUniqueWords() {
        unordered_map<string, bool> uniqueWords;
        WordNode* current = head;
        while (current != nullptr) {
            uniqueWords[current->word] = true;
            current = current->next;
        }
        return uniqueWords.size();
    }

    // Hàm hiển thị danh sách từ
    void displayWords() {
        WordNode* current = head;
        while (current != nullptr) {
            cout << current->word << " ";
            current = current->next;
        }
        cout << endl;
    }
};
int main() {
    WordLinkedList sentence;

    // Thêm các từ vào câu
    sentence.addWord("trời");
    sentence.addWord("xanh");
    sentence.addWord("xanh");
    sentence.addWord("cao");
    sentence.addWord("đẹp");
    sentence.addWord("trời");

    // Hiển thị câu ban đầu
    cout << "Original sentence: ";
    sentence.displayWords();

    // Xác định từ xuất hiện nhiều nhất
    string mostFrequentWord = sentence.findMostFrequentWord();
    cout << "Most frequent word: " << mostFrequentWord << endl;

    // Loại bỏ từ láy
    sentence.removeRedundantWords();
    cout << "Sentence after removing redundant words: ";
    sentence.displayWords();

    // Đếm số từ khác nhau
    int uniqueWordCount = sentence.countUniqueWords();
    cout << "Number of unique words: " << uniqueWordCount << endl;

    return 0;
}

