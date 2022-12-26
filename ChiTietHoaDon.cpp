#include "ChiTietHoaDon.h"
#include "QuanLyHang.h"
using namespace std;

// Ham dung va ham huy
ChiTietHoaDon::ChiTietHoaDon() {}

ChiTietHoaDon::ChiTietHoaDon(int maHH, int so_luong, double don_gia)
{
    this->maHH = maHH;
    this->don_gia = don_gia;
    this->so_luong = so_luong;
}
ChiTietHoaDon::~ChiTietHoaDon() {}

// Ham Setter

void ChiTietHoaDon::setMaHH(int maHH)
{
    this->maHH = maHH;
}
void ChiTietHoaDon::setDonGia(double don_gia)
{
    this->don_gia = don_gia;
}
void ChiTietHoaDon::setSoLuong(int so_luong)
{
    this->so_luong = so_luong;
}

// Ham Getter
int ChiTietHoaDon::getMaHH()
{
    return maHH;
}
double ChiTietHoaDon::getDonGia()
{
    return don_gia;
}
int ChiTietHoaDon::getSoLuong()
{
    return so_luong;
}
void ChiTietHoaDon::InputB(QuanLyHang &ql_hh)
{
    int n;
    do
    {
        cout << "\n\t\t\t\t\t\tMa hang hoa ban: ";
        maHH = ql_hh.Nhap_ma();
        n = ql_hh.FindIndex(maHH);
        if (n == -1 || (n != -1 && ql_hh.databaseK[n]->getCheckDeleteSo() == 1))
        {
            cout << "\t\t\t\t\t\tMa hang hoa chua ton tai hoac da bi xoa." << endl;
            cout << "\t\t\t\t\t\tBan muon nhap lai?      1. Co           0. Khong";
            do
            {
                cout << "\n\t\t\t\t\t\tNhap lua chon: ";
                int luachon1 = ql_hh.So_nguyen();
                if (luachon1 == 0)
                {
                    this->so_luong = 0;
                    this->don_gia = 0; // Khong thay doi so luong ~ khong mua hang nua
                    return;
                }
                else if (luachon1 == 1)
                    break;
            } while (1);
        }
        else
            break;
    } while (1);

    cout << "\t\t\t\t\t\tNhap so luong: ";
    this->so_luong = ql_hh.So_nguyen();
    while ((ql_hh.databaseK[n]->getSoLuong()) < this->so_luong)
    {
        int luachon;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
        cout << "\t\t\t\t\t\tSo luong hang hoa khong du. Kho chi con " << ql_hh.databaseK[n]->getSoLuong() << " mon" << endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
        cout << "\t\t\t\t\t\tBan muon thay doi so luong khong?" << endl;
        cout << "\t\t\t\t\t\t1. Co              0. Khong" << endl;
        cout << "\n\t\t\t\t\t\tNhap lua chon: ";
        luachon = ql_hh.So_nguyen();
        if (luachon == 0)
        {
            so_luong = 0;
            this->don_gia = 0;
            return; // Khong thay doi so luong ~ khong mua hang nua
        }
        else if (luachon == 1)
        {
            cout << "\t\t\t\t\t\tNhap so luong: ";
            this->so_luong = ql_hh.So_nguyen();
        }
    }
    ql_hh.databaseK[n]->setSoLuong(ql_hh.databaseK[n]->getSoLuong() - this->so_luong);
    don_gia = this->so_luong * ql_hh.databaseK[n]->getGiaBan(); // Ban: don gia = so luong * gia ban
}
// chi tiet hoa don cho trang thai mua
void ChiTietHoaDon::InputM(QuanLyHang &ql_hh)
{
    cout << "\n\t\t\t\t\t\tMa hang hoa can mua: ";
    maHH = ql_hh.Nhap_ma();
    int n = ql_hh.FindIndex(maHH);
    int luachon;
    while (n == -1)
    {
        cout << "\n\t\t\t\t\t\tMa hang hoa can mua chua ton tai. Ban lua chon?" << endl;
        cout << "\t\t\t\t\t\t1. Nhap lai" << endl;
        cout << "\t\t\t\t\t\t2. Them hang hoa moi";
        cout << "\n\t\t\t\t\t\tNhap lua chon: ";
        luachon = ql_hh.So_nguyen();
        if (luachon == 1)
        {
            maHH = ql_hh.Nhap_ma();
            n = ql_hh.FindIndex(maHH);
        }
        else if (luachon == 2)
        {
            int tmp = ql_hh.lengthK;
            try
            {
                ql_hh.Insert();
            }
            catch (int e)
            {
                maHH = e;
                break;
            }
            if (tmp != ql_hh.lengthK)
            {
                maHH = ql_hh.databaseK[0]->getCountID();
                n = ql_hh.FindIndex(maHH);
                cout << endl;
                break;
            }
        }
    }

    int luachon1;
    if (ql_hh.databaseK[n]->getCheckDeleteSo() == 1)
    {
        do
        {
            cout << "\n\t\t\t\t\t\tHang hoa da bi xoa khoi kho. Ban muon khoi phuc lai khong? ";
            cout << "\n\t\t\t\t\t\t0. Khong ";
            cout << "\n\t\t\t\t\t\t1. Co ";
            cout << "\n\t\t\t\t\t\tNhap lua chon: ";
            luachon1 = ql_hh.So_nguyen();
            cout << endl;
            if (luachon1 == 1)
            {
                ql_hh.databaseK[n]->setCheckDelete(0);
            }
            else if (luachon1 == 0)
            { /// Khong khoi phuc lai, tuc la khong mua hang hoa do
                so_luong = 0;
                don_gia = 0;
                return;
            }
        } while (luachon1 != 0 && luachon1 != 1);
    }
    cout << "\t\t\t\t\t\tNhap so luong can mua: ";
    this->so_luong = ql_hh.So_nguyen();
    ql_hh.databaseK[n]->setSoLuong(ql_hh.databaseK[n]->getSoLuong() + this->so_luong); // mua: so luong hang trong kho tang len
    don_gia = so_luong * ql_hh.databaseK[n]->getGiaVon();                              // mua: don gia = so luong * gia von
}
void ChiTietHoaDon::Output(QuanLyHang &hh)
{
    int n = hh.FindIndex(this->maHH);
    cout << "\n"
         << setw(48) << " "
         << "|" << left << setw(20) << hh.databaseK[n]->getTenHH() << "|" << left << setw(10) << this->so_luong << "|" << left << setw(11) << setprecision(20) << this->don_gia << "|";
}