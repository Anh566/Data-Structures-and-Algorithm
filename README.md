#include <iostream>
#include <stack>
#include <string>
using namespace std;

// Node trên cây biểu thức
struct Node {
    string value; // Giá trị tại node (toán tử hoặc toán hạng)
    Node *left, *right;

    Node(string val) : value(val), left(NULL), right(NULL) {}
};

// Cây biểu thức
class ExpressionTree {
private:
    Node* root;

    // Hàm kiểm tra độ ưu tiên của toán tử
    int precedence(char op) {
        if (op == '^') return 3;
        if (op == '*' || op == '/') return 2;
        if (op == '+' || op == '-') return 1;
        return 0;
    }

    // Hàm tạo một node từ toán tử
    Node* createNode(string op, Node* left, Node* right) {
        Node* node = new Node(op);
        node->left = left;
        node->right = right;
        return node;
    }

    // Hàm duyệt Trung tố (Infix)
    void inorder(Node* node) {
        if (node) {
            if (node->left || node->right) cout << "(";
            inorder(node->left);
            cout << node->value;
            inorder(node->right);
            if (node->left || node->right) cout << ")";
        }
    }

    // Hàm duyệt Tiền tố (Prefix)
    void preorder(Node* node) {
        if (node) {
            cout << node->value << " ";
            preorder(node->left);
            preorder(node->right);
        }
    }

    // Hàm duyệt Hậu tố (Postfix)
    void postorder(Node* node) {
        if (node) {
            postorder(node->left);
            postorder(node->right);
            cout << node->value << " ";
        }
    }

public:
    ExpressionTree() : root(NULL) {}

    // Hàm kiểm tra cây rỗng
    bool isEmpty() {
        return root == NULL;
    }

    // Hàm xây dựng cây từ biểu thức trung tố
    void buildTree(string expression) {
        stack<Node*> operands; // Stack lưu toán hạng
        stack<char> operators; // Stack lưu toán tử

        for (size_t i = 0; i < expression.size(); i++) {
            char ch = expression[i];

            if (isalnum(ch)) { // Nếu là toán hạng (chữ hoặc số)
                operands.push(new Node(string(1, ch)));
            } else if (ch == '(') {
                operators.push(ch);
            } else if (ch == ')') {
                while (!operators.empty() && operators.top() != '(') {
                    char op = operators.top(); operators.pop();
                    Node* right = operands.top(); operands.pop();
                    Node* left = operands.top(); operands.pop();
                    operands.push(createNode(string(1, op), left, right));
                }
                operators.pop(); // Loại bỏ '('
            } else if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^') {
                while (!operators.empty() && operators.top() != '(' &&
                       precedence(operators.top()) >= precedence(ch)) {
                    char op = operators.top(); operators.pop();
                    Node* right = operands.top(); operands.pop();
                    Node* left = operands.top(); operands.pop();
                    operands.push(createNode(string(1, op), left, right));
                }
                operators.push(ch);
            }
        }

        while (!operators.empty()) {
            char op = operators.top(); operators.pop();
            Node* right = operands.top(); operands.pop();
            Node* left = operands.top(); operands.pop();
            operands.push(createNode(string(1, op), left, right));
        }

        root = operands.top();
    }

    // Hàm in biểu thức Trung tố
    void printInorder() {
        inorder(root);
        cout << endl;
    }

    // Hàm in biểu thức Tiền tố
    void printPreorder() {
        preorder(root);
        cout << endl;
    }

    // Hàm in biểu thức Hậu tố
    void printPostorder() {
        postorder(root);
        cout << endl;
    }
};

// Chương trình chính
int main() {
    string expression = "a*5-b*c/d+(h-f)*e^1/2";

    ExpressionTree tree;
    tree.buildTree(expression);

    cout << "Trung tố (Infix): ";
    tree.printInorder();

    cout << "Tiền tố (Prefix): ";
    tree.printPreorder();

    cout << "Hậu tố (Postfix): ";
    tree.printPostorder();

    return 0;
}
