#include "HoaDon.h"
#include "QuanLyHang.h"

int HoaDon::count_id = 0;
// Ham dung va ham huy
HoaDon::HoaDon(int maHD, int lengthCTHD, int maNV, string sdt, Date ngay_lap, double thanh_tien, int trang_thai)
{
    if (maHD != -1)
    {
        this->maHD = maHD;
        if (count_id < maHD)
            count_id = maHD;
    }
    else
        this->maHD = ++count_id;
    this->maNV = maNV;
    this->sdt = sdt;
    this->ngay_lap = ngay_lap;
    this->thanh_tien = thanh_tien;
    this->lengthCTHD = lengthCTHD;
    this->thanh_tien = thanh_tien;
    this->trang_thai = trang_thai;
}
HoaDon::~HoaDon()
{
    count_id--;
}

// Ham Setter
void HoaDon::setMaHD(int maHD)
{
    this->maHD = maHD;
}

void HoaDon::setSDT(string sdt)
{
    this->sdt = sdt;
}

void HoaDon::setLengthCTHD(int lengthCTHD)
{
    this->lengthCTHD = lengthCTHD;
}

void HoaDon::setNgayLap(Date ngay_lap)
{
    this->ngay_lap = ngay_lap;
}
void HoaDon::setThanhTien(double thanh_tien)
{
    this->thanh_tien = thanh_tien;
}
void HoaDon::setMaNV(int maNV)
{
    this->maNV = maNV;
}
void HoaDon::setTrangThai(int trang_thai)
{
    this->trang_thai = trang_thai;
}
// Ham Getter
int HoaDon::getMaHD()
{
    return this->maHD;
}

string HoaDon::getSDT()
{
    return this->sdt;
}

int HoaDon::getLengthCTHD()
{
    return this->lengthCTHD;
}

Date HoaDon::getNgayLap()
{
    return this->ngay_lap;
}
double HoaDon::getThanhTien()
{
    return this->thanh_tien;
}
int HoaDon::getMaNV()
{
    return this->maNV;
}
int HoaDon::getTrangThaiSo()
{
    return this->trang_thai;
}
string HoaDon::getTrangThai()
{
    if (this->trang_thai == 2)
        return "Ban";
    else
        return "Mua";
}
// Ham chuc nang
void HoaDon::Input(QuanLyKH &kh, QuanLyNV &nv, QuanLyHang &hh)
{
    Date ngay_lap;
    setNgayLap(ngay_lap); // set thoi gian tu dong

    cout << "\t\t\t\t\t\tBan muon mua (ban) bao nhieu loai hang? ";
    this->lengthCTHD = hh.So_nguyen();
    for (int i = 0; i < this->lengthCTHD; i++)
    {
        system("cls");
        hh.Show(0);
        cout << "\n\t\t\t\t\t\tNhap thong tin chi tiet loai " << i + 1;
        ChiTietHoaDon *p = new ChiTietHoaDon;
        // trangthai: 1 - Mua, 2 - Ban
        if (this->trang_thai == 2)
            p->InputB(hh);
        else
            p->InputM(hh);
        this->cthd.push_back(p);
        this->thanh_tien += this->cthd[i]->getDonGia();
    }
    if (this->thanh_tien == 0)
    {
        cout << "\n\t\t\t\t\t\tTHANH TIEN: 0" << endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
        cout << "\t\t\t\t\t\tHoa don khong duoc lap!" << endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
        return;
    }
    //////// Tinh diem tich luy cho khach hang
    if (trang_thai == 2)
    {
        int n = kh.FindIndexSDT(sdt);
        double sd_bd = kh.databaseKH[n]->getSoDiem(); // so diem ban dau
        // neu tren 100 diem thi duoc giam gia (100d = 100k)
        if (sd_bd >= 100)
        {
            if (sd_bd * 1000 <= this->thanh_tien)
            {
                this->thanh_tien -= sd_bd * 1000; // tien tich duoc <= thanh tien
                cout << "\n\t\t\t\t\t\tKhach hang duoc giam " << sd_bd * 1000 << endl;
                sd_bd = 0;
            }
            else
            { // tien tu diem tich duoc > thanh tien
                sd_bd = (sd_bd * 1000 - thanh_tien) / 1000;
                cout << "\n\t\t\t\t\t\tKhach hang duoc giam " << thanh_tien << endl;
                this->thanh_tien = 0;
            }
        }
        double sd_ct = (this->thanh_tien) / 100000; // so diem duoc cong them khi mua: 100k tich 1 diem
        kh.databaseKH[n]->setSoDiem(sd_bd + sd_ct);
        if (sd_ct > 0)
            cout << "\n\t\t\t\t\t\tKhach hang duoc cong them " << sd_ct << " diem" << endl;
    }
    cout << "\n\t\t\t\t\t\tTHANH TIEN: " << setprecision(15) << this->thanh_tien << endl;
}
ostream &operator<<(ostream &out, HoaDon &hd)
{
    out << "\n"
        << setw(53) << " "
        << "|" << left << setw(7) << hd.getMaHD() << "|" << left << setw(7) << hd.getMaNV() << "|" << left << setw(11) << hd.getSDT() << "|"
        << left << setw(12) << setprecision(13) << hd.getThanhTien() << "|" << left << setw(12) << hd.getTrangThai() << "|";
    return out;
}
void HoaDon::Output(QuanLyHang &hh)
{
    cout << "\n\t\t\t\t\t\t1. Ma hoa don: " << maHD;
    cout << "\n\t\t\t\t\t\t2. Trang thai hoa don: ";
    if (trang_thai == 1)
        cout << "Mua";
    else
        cout << "Ban";
    cout << "\n\t\t\t\t\t\t3. Ma nhan vien nhap: " << maNV;
    cout << "\n\t\t\t\t\t\t4. SDT khach hang: " << sdt;
    cout << "\n\t\t\t\t\t\t5. Ngay lap: " << ngay_lap;
    cout << endl;
    cout << setw(48) << " ";
    for (int i = 1; i <= 45; i++)
        cout << "-";
    cout << endl;
    cout << setw(48) << " " << "|    Ten hang hoa    |" << " So luong |" << "  Don gia  |" << endl;
    cout << setw(48) << " ";
    for (int i = 1; i <= 45; i++)
        cout << "-";
    for (int i = 0; i < lengthCTHD; i++)
    {
        cthd[i]->Output(hh);
    }
    cout << "\n"
         << setw(48) << " ";
    for (int i = 1; i <= 45; i++)
        cout << "-";
    cout << "\n\n\t\t\t\t\t\tTHANH TIEN: " << setprecision(15) << thanh_tien << endl;
}