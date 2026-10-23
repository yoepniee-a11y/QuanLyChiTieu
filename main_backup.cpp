#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
using namespace std;

struct GiaoDich {
    string ten;
    double soTien;
    int loai;
};

int main() {
    cout << fixed << setprecision(0);
    
    GiaoDich ds[100];
    int n = 0;
    int luaChon;

    ifstream fileDoc("giaodich.txt");

    if (fileDoc.is_open()) {
        while (n < 100 &&
               getline(fileDoc, ds[n].ten, '|') &&
               fileDoc >> ds[n].soTien &&
               fileDoc.ignore(1, '|') &&
               fileDoc >> ds[n].loai) {

            fileDoc.ignore(1000, '\n');
            n++;
        }

        fileDoc.close();
    }

    cout << "Da tai " << n << " giao dich tu file." << endl;

    string tenGiaoDich;
    double soTien;
    int loai;
    char tiepTuc;

    do {
        cout << "\n=== QUAN LY CHI TIEU CA NHAN ===" << endl;
        cout << "1. Thu tien" << endl;
        cout << "2. Chi tien" << endl;
        cout << "Chon loai giao dich: ";
        cin >> loai;

        cin.ignore();

        if (loai != 1 && loai != 2) {
            cout << "Loai giao dich khong hop le!" << endl;
        } else {
            cout << "Nhap ten giao dich: ";
            getline(cin, tenGiaoDich);

            cout << "Nhap so tien: ";
            cin >> soTien;

            if (soTien <= 0) {
                cout << "So tien phai lon hon 0!" << endl;
            } else {
                cout << "\n=== THONG TIN GIAO DICH ===" << endl;

                if (loai == 1) {
                    cout << "Loai: Thu tien" << endl;
                } else {
                    cout << "Loai: Chi tien" << endl;
                }

if (n < 100) {
    ds[n].ten = tenGiaoDich;
    ds[n].soTien = soTien;
    ds[n].loai = loai;

    n++;

    cout << "Da luu giao dich thanh cong!" << endl;
} else {
    cout << "Danh sach da day!" << endl;
}

                cout << "Ten giao dich: "
                     << tenGiaoDich << endl;
                cout << "So tien: "
                     << soTien << " VND" << endl;
            }
        }

        cout << "\nBan co muon nhap giao dich khac? (y/n): ";
        cin >> tiepTuc;

    } while (tiepTuc == 'y' || tiepTuc == 'Y');

    cout << "\n=== DANH SACH GIAO DICH DA NHAP ===" << endl;

    if (n == 0) {
        cout << "Chua co giao dich nao!" << endl;
    } else {
        for (int i = 0; i < n; i++) {
            cout << "\nGiao dich thu " << i + 1 << endl;

            cout << "Loai: ";
            if (ds[i].loai == 1) {
                cout << "Thu tien" << endl;
            } else {
                cout << "Chi tien" << endl;
            }

            cout << "Ten giao dich: " << ds[i].ten << endl;
            cout << "So tien: " << ds[i].soTien << " VND" << endl;
        }
    }

    double tongThu = 0;
    double tongChi = 0;

    for (int i = 0; i < n; i++) {
        if (ds[i].loai == 1) {
            tongThu += ds[i].soTien;
        } else if (ds[i].loai == 2) {
            tongChi += ds[i].soTien;
        }
    }

    double soDu = tongThu - tongChi;

    cout << "\n=== THONG KE THU CHI ===" << endl;
    cout << "Tong thu: " << tongThu << " VND" << endl;
    cout << "Tong chi: " << tongChi << " VND" << endl;
    cout << "So du: " << soDu << " VND" << endl;

    string tuKhoa;
    bool timThay = false;

    cout << "\nNhap ten giao dich can tim: ";
    getline(cin >> ws, tuKhoa);

    for (int i = 0; i < n; i++) {
        if (ds[i].ten.find(tuKhoa) != string::npos) {
            cout << "\nTim thay giao dich:" << endl;
            cout << "Ten: " << ds[i].ten << endl;
            cout << "So tien: " << ds[i].soTien << " VND" << endl;

            if (ds[i].loai == 1) {
                cout << "Loai: Thu tien" << endl;
            } else {
                cout << "Loai: Chi tien" << endl;
            }

            timThay = true;
        }
    }

    if (!timThay) {
        cout << "Khong tim thay giao dich!" << endl;
    }

    ofstream fileGhi("giaodich.txt");

    if (fileGhi.is_open()) {
        for (int i = 0; i < n; i++) {
            fileGhi << ds[i].ten << "|"
                    << ds[i].soTien << "|"
                    << ds[i].loai << endl;
        }

        fileGhi.close();
        cout << "\nDa luu du lieu vao file giaodich.txt" << endl;
    } else {
        cout << "\nKhong the mo file de ghi!" << endl;
    }

    cout << "\nKet thuc chuong trinh!" << endl;

    return 0;
}
