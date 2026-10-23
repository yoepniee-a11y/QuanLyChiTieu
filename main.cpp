#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <string>
#include <vector>
using namespace std;

class GiaoDich {
private:
    string ten;
    double soTien;
    int loai;

public:
    GiaoDich() : ten(""), soTien(0), loai(2) {}

    GiaoDich(const string& tenMoi, double soTienMoi, int loaiMoi)
        : ten(tenMoi),
          soTien(soTienMoi > 0 ? soTienMoi : 0),
          loai((loaiMoi == 1 || loaiMoi == 2) ? loaiMoi : 2) {}

    void setTen(const string& tenMoi) {
        ten = tenMoi;
    }

    string getTen() const {
        return ten;
    }

    bool setSoTien(double soTienMoi) {
        if (soTienMoi <= 0) {
            return false;
        }
        soTien = soTienMoi;
        return true;
    }

    double getSoTien() const {
        return soTien;
    }

    bool setLoai(int loaiMoi) {
        if (loaiMoi != 1 && loaiMoi != 2) {
            return false;
        }
        loai = loaiMoi;
        return true;
    }

    int getLoai() const {
        return loai;
    }
};

void hienThiGiaoDich(const vector<GiaoDich>& ds) {
    if (ds.empty()) {
        cout << "Danh sach giao dich rong!\n";
        return;
    }

    cout << "\n========== DANH SACH GIAO DICH ==========\n";
    cout << left << setw(5) << "STT"
         << setw(25) << "Ten giao dich"
         << setw(15) << "So tien" << "Loai\n";

    for (size_t i = 0; i < ds.size(); i++) {
        cout << left << setw(5) << i + 1
             << setw(25) << ds[i].getTen()
             << setw(15) << ds[i].getSoTien()
             << (ds[i].getLoai() == 1 ? "Thu\n" : "Chi\n");
    }
    cout << "=========================================\n";
}

int main() {
    cout << fixed << setprecision(0);

    vector<GiaoDich> ds;
    int luaChon = -1;

    ifstream fileDoc("giaodich.txt");
    if (fileDoc.is_open()) {
        while (true) {
            string ten;
            double soTien;
            int loai;

            if (!getline(fileDoc, ten, '|')) {
                break;
            }

            if (!(fileDoc >> soTien)) {
                cout << "Du lieu so tien trong file khong hop le!\n";
                break;
            }

            char dauPhanCach;
            if (!fileDoc.get(dauPhanCach) || dauPhanCach != '|') {
                cout << "Dinh dang file khong hop le!\n";
                break;
            }

            if (!(fileDoc >> loai)) {
                cout << "Du lieu loai giao dich trong file khong hop le!\n";
                break;
            }

            fileDoc.ignore(numeric_limits<streamsize>::max(), '\n');

            if (ten.empty() || soTien <= 0 ||
                (loai != 1 && loai != 2)) {
                cout << "Bo qua giao dich khong hop le trong file!\n";
                continue;
            }

            ds.emplace_back(ten, soTien, loai);
        }
        fileDoc.close();
    }

    cout << "Da tai " << ds.size() << " giao dich tu file.\n";

    do {
        cout << "\n================================\n";
        cout << "   QUAN LY CHI TIEU CA NHAN\n";
        cout << "================================\n";
        cout << "1. Them giao dich\n";
        cout << "2. Hien thi danh sach giao dich\n";
        cout << "3. Tim kiem giao dich\n";
        cout << "4. Thong ke thu chi\n";
        cout << "5. Sua giao dich\n";
        cout << "6. Xoa giao dich\n";
        cout << "0. Luu va thoat\n";
        cout << "================================\n";
        cout << "Nhap lua chon: ";

        if (!(cin >> luaChon)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Vui long nhap mot so nguyen!\n";
            luaChon = -1;
            continue;
        }

        switch (luaChon) {
        case 1: {
            string tenMoi;
            double soTienMoi;
            int loaiMoi;

            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Nhap ten giao dich: ";
            getline(cin, tenMoi);

            if (tenMoi.empty()) {
                cout << "Ten giao dich khong duoc de trong!\n";
                break;
            }

            cout << "Nhap so tien: ";
            if (!(cin >> soTienMoi)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "So tien khong hop le!\n";
                break;
            }
            if (soTienMoi <= 0) {
                cout << "So tien phai lon hon 0!\n";
                break;
            }

            cout << "Chon loai giao dich (1. Thu, 2. Chi): ";
            if (!(cin >> loaiMoi)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Loai giao dich khong hop le!\n";
                break;
            }
            if (loaiMoi != 1 && loaiMoi != 2) {
                cout << "Loai giao dich khong hop le!\n";
                break;
            }

            ds.emplace_back(tenMoi, soTienMoi, loaiMoi);
            cout << "Them giao dich thanh cong!\n";
            break;
        }

        case 2:
            hienThiGiaoDich(ds);
            break;

        case 3: {
            string tuKhoa;
            bool timThay = false;

            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Nhap ten giao dich can tim: ";
            getline(cin, tuKhoa);

            for (const GiaoDich& gd : ds) {
                if (gd.getTen().find(tuKhoa) != string::npos) {
                    cout << "\nTen giao dich: " << gd.getTen() << '\n';
                    cout << "So tien: " << gd.getSoTien() << '\n';
                    cout << "Loai: " << (gd.getLoai() == 1 ? "Thu" : "Chi") << '\n';
                    timThay = true;
                }
            }

            if (!timThay) {
                cout << "Khong tim thay giao dich phu hop!\n";
            }
            break;
        }

        case 4: {
            double tongThu = 0;
            double tongChi = 0;

            for (const GiaoDich& gd : ds) {
                if (gd.getLoai() == 1) {
                    tongThu += gd.getSoTien();
                } else {
                    tongChi += gd.getSoTien();
                }
            }

            cout << "\n========== THONG KE THU CHI ==========\n";
            cout << "Tong tien thu: " << tongThu << " VND\n";
            cout << "Tong tien chi: " << tongChi << " VND\n";
            cout << "So du hien tai: " << tongThu - tongChi << " VND\n";
            cout << "======================================\n";
            break;
        }

        case 5: {
            if (ds.empty()) {
                cout << "Danh sach giao dich rong!\n";
                break;
            }

            hienThiGiaoDich(ds);

            size_t stt;
            cout << "Nhap STT giao dich can sua: ";
            if (!(cin >> stt)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "STT phai la mot so nguyen!\n";
                break;
            }
            if (stt < 1 || stt > ds.size()) {
                cout << "STT khong hop le!\n";
                break;
            }

            string tenMoi;
            double soTienMoi;
            int loaiMoi;

            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Nhap ten moi: ";
            getline(cin, tenMoi);
            if (tenMoi.empty()) {
                cout << "Ten giao dich khong duoc de trong!\n";
                break;
            }

            cout << "Nhap so tien moi: ";
            if (!(cin >> soTienMoi)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "So tien khong hop le!\n";
                break;
            }
            if (soTienMoi <= 0) {
                cout << "So tien phai lon hon 0!\n";
                break;
            }

            cout << "Nhap loai moi (1. Thu, 2. Chi): ";
            if (!(cin >> loaiMoi)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Loai giao dich khong hop le!\n";
                break;
            }
            if (loaiMoi != 1 && loaiMoi != 2) {
                cout << "Loai giao dich khong hop le!\n";
                break;
            }

            ds[stt - 1] = GiaoDich(tenMoi, soTienMoi, loaiMoi);
            cout << "Sua giao dich thanh cong!\n";
            break;
        }

        case 6: {
            if (ds.empty()) {
                cout << "Danh sach giao dich rong!\n";
                break;
            }

            hienThiGiaoDich(ds);

            size_t stt;
            cout << "Nhap STT giao dich can xoa: ";
            if (!(cin >> stt)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "STT phai la mot so nguyen!\n";
                break;
            }
            if (stt < 1 || stt > ds.size()) {
                cout << "STT khong hop le!\n";
                break;
            }

            char xacNhan;
            cout << "Ban co chac chan muon xoa giao dich nay? (y/n): ";
            cin >> xacNhan;

            if (xacNhan == 'y' || xacNhan == 'Y') {
                ds.erase(ds.begin() + static_cast<vector<GiaoDich>::difference_type>(stt - 1));
                cout << "Xoa giao dich thanh cong!\n";
            } else {
                cout << "Da huy thao tac xoa.\n";
            }
            break;
        }

        case 0: {
            ofstream fileGhi("giaodich.txt");
            if (fileGhi.is_open()) {
                for (const GiaoDich& gd : ds) {
                    fileGhi << gd.getTen() << '|'
                            << fixed << setprecision(0) << gd.getSoTien() << '|'
                            << gd.getLoai() << '\n';
                }
                fileGhi.close();
                cout << "Da luu " << ds.size() << " giao dich vao file!\n";
                cout << "Ket thuc chuong trinh!\n";
            } else {
                cout << "Loi: Khong the mo file de ghi du lieu!\n";
                luaChon = -1;
            }
            break;
        }

        default:
            cout << "Lua chon khong hop le! Vui long chon lai.\n";
        }
    } while (luaChon != 0);

    return 0;
}
