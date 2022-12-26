#include "KhachHang.h"

int KhachHang::count_id = 0;
// Ham constructor & destructor
KhachHang::KhachHang(int maKH, string hodem, string tenKH, string sdt, int so_diem, int check_delete)
{
    if (maKH != -1)
    {
        this->maKH = maKH;
        if (count_id < maKH)
            count_id = maKH;
    }
    else
        this->maKH = ++count_id;
    this->hodem = hodem;
    this->sdt = sdt;
    this->tenKH = tenKH;
    this->so_diem = so_diem;
    this->check_delete = check_delete;
}
KhachHang::~KhachHang()
{
    count_id--;
}
// Ham getter
int KhachHang::getMaKH()
{
    return this->maKH;
}
string KhachHang::getHoDemKH()
{
    return this->hodem;
}
string KhachHang::getTenKH()
{
    return this->tenKH;
}
string KhachHang::getSDT()
{
    return this->sdt;
}
int KhachHang::getSoDiem()
{
    return this->so_diem;
}
string KhachHang::getCheckDelete()
{
    if (check_delete == 0)
        return "Ton Tai";
    else
        return "Da Xoa";
}
int KhachHang::getCheckDeleteSo()
{
    return check_delete;
}
// Ham setter
void KhachHang::setMaKH(int maKH)
{
    this->maKH = maKH;
}
void KhachHang::setHoDemKH(string hodem)
{
    this->hodem = hodem;
}
void KhachHang::setTenKH(string tenKH)
{
    this->tenKH = tenKH;
}
void KhachHang::setSDT(string sdt)
{
    this->sdt = sdt;
}
void KhachHang::setSoDiem(int so_diem)
{
    this->so_diem = so_diem;
}
void KhachHang::setCheckDelete(int check)
{
    this->check_delete = check;
}

void KhachHang::try_catchHoten(string &ten)
{
    fflush(stdin);
    getline(cin, ten);
    /// Kiem tra ten va ho co rong khong?
    while (ten[0] == ' ')
        ten.erase(ten.begin() + 0);
    if (ten.empty() == 1)
        throw "\t\t\t\t\t\tNhap lai!";
    /// Kiem tra ho co ki tu dac biet khong?
    for (int i = 0; i < ten.length(); i++)
    {
        if (!(ten[i] >= 97 && ten[i] <= 122) && !(ten[i] >= 65 && ten[i] <= 90) && ten[i] != ' ')
            throw "\t\t\t\t\t\tNhap lai!";
    }
}
istream &operator>>(istream &in, KhachHang &kh)
{
    /// Kiem tra ten va ho co rong khong?
    do
    {
        try
        {
            cout << "\t\t\t\t\t\tNhap ho dem khach hang: ";
            kh.try_catchHoten(kh.hodem);
            break;
        }
        catch (const char *e)
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
            cout << e << endl;
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
        }
    } while (1);

    do
    {
        try
        {
            cout << "\t\t\t\t\t\tNhap ten khach hang: ";
            kh.try_catchHoten(kh.tenKH);
            break;
        }
        catch (const char *e)
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
            cout << e << endl;
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
        }
    } while (1);
    ///

    /// Kiem tra so dien thoai co hop le khong
    while (1)
    {
        try
        {
            cout << "\t\t\t\t\t\tNhap so dien thoai: ";
            in >> kh.sdt;
            if (kh.sdt.length() != 10) throw "";
            if (kh.sdt[0] != '0') throw "";
            for (int i = 1; i < kh.sdt.length(); i++)
            {
                if (kh.sdt[i] < 48 || kh.sdt[i] > 57) throw "";
            }
            break;
        }
        catch (...)
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
            cout << "\t\t\t\t\t\tSo dien thoai khong hop le. Nhap lai!" << endl;
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
        }
    }
    kh.so_diem = 0;
    return in;
}

ostream &operator<<(ostream &out, KhachHang &khachhang)
{
    out << "\n" << setw(52) << " " << "|" << left << setw(7) << khachhang.maKH << "|" 
        << left << setw(17) << khachhang.hodem + " " << left << setw(5) << khachhang.tenKH
        << "|" << left << setw(13) << khachhang.sdt << "|" << setw(11) << khachhang.so_diem << "|";
    return out;
}