#include <iostream>
#include <map>
#include <vector>

using namespace std;

// Cấu trúc lưu thông tin năm và số người sinh ra
struct NamSinh {
    int nam;
    int soLuongNguoi;
};

// Hàm tìm năm có số lượng người sinh ra lớn nhất và nhỏ nhất
void timSoLuongLonNhatBeNhat(vector<NamSinh> &danhsach) {
    map<int, int> soLuongTheoNam; // Map lưu năm và số lượng người sinh ra

    // Đưa thông tin vào map
    for (const auto &ns : danhsach) {
        soLuongTheoNam[ns.nam] += ns.soLuongNguoi;
    }

    // Khởi tạo giá trị cho số lượng lớn nhất và nhỏ nhất
    int soLuongLonNhat = -1;
    int soLuongBeNhat = INT_MAX;
    
    // Duyệt qua map để tìm giá trị lớn nhất và nhỏ nhất
    for (const auto &pair : soLuongTheoNam) {
        if (pair.second > soLuongLonNhat) {
            soLuongLonNhat = pair.second;
        }
        if (pair.second < soLuongBeNhat) {
            soLuongBeNhat = pair.second;
        }
    }

    // In ra các năm có số lượng người sinh ra là lớn nhất
    cout << "Nam co so luong nguoi sinh ra lon nhat (" << soLuongLonNhat << "): ";
    for (const auto &pair : soLuongTheoNam) {
        if (pair.second == soLuongLonNhat) {
            cout << pair.first << " ";
        }
    }
    cout << endl;

    // In ra các năm có số lượng người sinh ra là nhỏ nhất
    cout << "Nam co so luong nguoi sinh ra be nhat (" << soLuongBeNhat << "): ";
    for (const auto &pair : soLuongTheoNam) {
        if (pair.second == soLuongBeNhat) {
            cout << pair.first << " ";
        }
    }
    cout << endl;
}

int main() {
    // Tạo danh sách dân số với năm và số lượng người sinh ra
    vector<NamSinh> danhsach = {
        {1990, 100},
        {1991, 150},
        {1992, 80},
        {1993, 100},
        {1994, 150},
        {1995, 200}
    };

    // Gọi hàm để tìm và in ra kết quả
    timSoLuongLonNhatBeNhat(danhsach);

    return 0;
}

