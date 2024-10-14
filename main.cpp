#include <iostream>
#include <vector>
#include <string>
using namespace std;

void dutchNationalFlag(vector<string>& arr) {
    int thap = 0;
    int giua = 0;
    int cao = arr.size() - 1;

    while (giua <= cao) {
        if (arr[giua] == "đỏ") {
            swap(arr[thap], arr[giua]);
            thap++;
            giua++;
        }
        else if (arr[giua] == "trắng") {
            giua++;
        }
        else {
            swap(arr[giua], arr[cao]);
            cao--;
        }
    }
}

int main() {
   
    vector<string> arr = {"xanh", "đỏ", "xanh", "đỏ", "đỏ", "trắng", "đỏ", "xanh", "trắng"};
    dutchNationalFlag(arr);
    cout << "Kết quả sau khi sắp xếp: {";
    for (int i = 0; i < arr.size(); i++) {
        cout << arr[i];
        if (i != arr.size() - 1) cout << ", ";
    }
    cout << "}" << endl;

    return 0;
}
