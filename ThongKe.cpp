#include "ThongKe.h"

bool CheckNamNhuan(int y)
{
    if ((y % 4 == 0 && y % 100 != 0) || y % 400 == 0) return true;
    else return false;
}
int DemNgayThang(int month, int year)
{
    if (month == 2)
    {
        if (CheckNamNhuan(year)) return 29;
        else return 28;
    }
    else
    {
        if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
            return 31;
        else
            return 30;
    }
}
ThongKe::ThongKe()
{
    this->doanh_thu = 0;
    this->von = 0;
    this->loi_nhuan = 0;
    this->luongNV = 0;
}
void ThongKe::ThongKeHomNay(QuanLyHD &ql_hd)
{
    double doanhthu = 0, loinhuan = 0, von = 0;
    int day, month, year;

    time_t now = time(0);
    tm *ltm = localtime(&now);
    day = ltm->tm_mday;
    month = 1 + ltm->tm_mon;
    year = 1900 + ltm->tm_year;
    Date homnay(day, month, year);
    for (int i = 0; i < ql_hd.getLengthHD(); i++)
    {
        if (ql_hd.databaseHD[i]->getNgayLap().getNgay() == day && ql_hd.databaseHD[i]->getNgayLap().getThang() == month && ql_hd.databaseHD[i]->getNgayLap().getNam() == year)
        {
            if (ql_hd.databaseHD[i]->getTrangThaiSo() == 2)
                doanhthu += ql_hd.databaseHD[i]->getThanhTien();
            if (ql_hd.databaseHD[i]->getTrangThaiSo() == 1)
                von += ql_hd.databaseHD[i]->getThanhTien();
        }
    }
    loinhuan = doanhthu - von;
    cout << "\n" << setw(69) << " " << "BAO CAO NGAY " << homnay << endl;
    cout << setw(56) << " "; for (int i = 1; i <= 49; i++) cout << "-"; cout << endl;
    cout << setw(56) << " " << "|      Von (nghin)      |" << setw(9) << " " << left << setw(14) << round((von / 1000) * 10) / 10 << "|" << endl;
    cout << setw(56) << " "; for (int i = 1; i <= 49; i++) cout << "-"; cout << endl;
    cout << setw(56) << " " << "|   Doanh thu (nghin)   |" << setw(9) << " " << left << setw(14) << round((doanhthu / 1000) * 10) / 10 << "|" << endl;
    cout << setw(56) << " "; for (int i = 1; i <= 49; i++) cout << "-"; cout << endl;
    cout << setw(56) << " " << "|   Loi nhuan (nghin)   |" << setw(9) << " " << left << setw(14) << round((loinhuan / 1000) * 10) / 10 << "|" << endl;
    cout << setw(56) << " "; for (int i = 1; i <= 49; i++) cout << "-"; cout << endl;
}   
void ThongKe::ThongKeNgay(QuanLyNV &nv, QuanLyHD &hd)
{
    this->doanh_thu = 0;
    this->von = 0;
    this->loi_nhuan = 0;
    this->luongNV = 0;

    time_t now = time(0);
    tm *ltm = localtime(&now);
    int yy = 1900 + ltm->tm_year;
    int mm = 1 + ltm->tm_mon;
    int dd = ltm->tm_mday;
    Date hien_tai(dd, mm, yy); // Ngay hien tai
    Date ngay_bd, ngay_kt;

    // Nhap va kiem tra xem muon thong ke co truoc thoi gian hien tai khong
    cout << "\t\t\t\t\t\tThong ke tu ngay: ";
    ngay_bd.Input();
    if (ngay_bd > hien_tai)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
        cout << "\t\t\t\t\t\tKhong co du lieu!" << endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
        return;
    }
    cout << "\t\t\t\t\t\tDen ngay: ";
    ngay_kt.Input();
    if (ngay_kt > hien_tai || ngay_bd > ngay_kt)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
        cout << "\t\t\t\t\t\tKhong co du lieu!" << endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
        return;
    }
    ngay_bd.setGio(0); ngay_bd.setPhut(0); ngay_kt.setGio(0); ngay_kt.setPhut(0);
    for (int j = 0; j < hd.getLengthHD(); j++)
    {

        if (hd.databaseHD[j]->getTrangThaiSo() == 2 && !(hd.databaseHD[j]->getNgayLap() > ngay_kt || ngay_bd > hd.databaseHD[j]->getNgayLap()))
        {
            this->doanh_thu = this->doanh_thu + hd.databaseHD[j]->getThanhTien();
        }
    }
    for (int j = 0; j < hd.getLengthHD(); j++)
    {
        if (hd.databaseHD[j]->getTrangThaiSo() == 1 && !(hd.databaseHD[j]->getNgayLap() > ngay_kt || ngay_bd > hd.databaseHD[j]->getNgayLap()))
            this->von = this->von + hd.databaseHD[j]->getThanhTien();
    }

    cout << "\n" << setw(60) << " " << "BAO CAO TU NGAY " << ngay_bd << " - " << ngay_kt << endl;
    cout << setw(56) << " "; for (int i = 1; i <= 49; i++) cout << "-"; cout << endl;
    cout << setw(56) << " " << "|      Von (nghin)      |" << setw(9) << " " << left << setw(14) << round((von / 1000) * 10) / 10 << "|" << endl;
    cout << setw(56) << " "; for (int i = 1; i <= 49; i++) cout << "-"; cout << endl;
    cout << setw(56) << " " << "|   Doanh thu (nghin)   |" << setw(9) << " " << left << setw(14) << round((doanh_thu / 1000) * 10) / 10 << "|" << endl;
    cout << setw(56) << " "; for (int i = 1; i <= 49; i++) cout << "-"; cout << endl;
}
void ThongKe::ThongKeThang(QuanLyNV &nv, QuanLyHD &hd)
{
    this->luongNV = 0;
    this->loi_nhuan = 0;
    this->doanh_thu = 0;
    this->von = 0;

    int month, year;
    cout << "\t\t\t\t\t\tNhap thang, nam can thong ke: ";
    while (1)
    {
        try
        {
            string x;
            fflush(stdin);      getline(cin, x);
            int n = x.length();
            if (n != 7) throw "";
            for(int j = 0; j < n; j++){
                if (j == 2){
                    if (x[j] != '/') throw "";
                }
                else{
                    if (x[j] < 48 || x[j] > 57) throw "";
                }
            }
            
            month = (int)(x[0] - '0') * 10 + (int)(x[1] - '0');
            year = (int)(x[3] - '0') * 1000 + (int)(x[4] - '0') * 100 + (int)(x[5] - '0') * 10 + (int)(x[6] - '0');

            if (month > 12) throw "";
            break;
        }
        catch (...)
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
            cout << "\t\t\t\t\t\tPhai nhap theo dinh dang mm/yyyy. Nhap lai: ";
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
        }
    }
    Date ngay_nhap(1, month, year); // thoi gian nhap vao
    time_t now = time(0);
    tm *ltm = localtime(&now);
    int yy = 1900 + ltm->tm_year;
    int mm = 1 + ltm->tm_mon;
    Date hien_tai(1, mm, yy); // thoi gian hien tai
    // Thoi gian thong ke phai be hon thoi gian hien tai
    if (hien_tai < ngay_nhap)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
        cout << "\t\t\t\t\t\tKhong co du lieu!" << endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
        return;
    }
    for (int j = 0; j < nv.getLengthNV(); j++)
    {

        int luong_theo_ngay = nv.databaseNV[j]->getLuong() / DemNgayThang(month, year);
        int ngayvao = nv.databaseNV[j]->getNgayVao().getNgay();
        int ngaynghi = nv.databaseNV[j]->getNgayNghi().getNgay();

        // Neu nhan vien j duoc nhan vao thang dang xet va khong nghi viec trong thang do
        if (nv.databaseNV[j]->getNgayVao() == ngay_nhap && nv.databaseNV[j]->getNgayNghi() != ngay_nhap)
        {
            if (nv.databaseNV[j]->getNgayVao().getNgay() == 1)
                this->luongNV += nv.databaseNV[j]->getLuong();
            else
                this->luongNV += luong_theo_ngay * (DemNgayThang(month, year) - ngayvao + 1);
        }
        // Neu nhan vien j duoc nhan vao thang dang xet va nghi viec trong thang do
        else if (nv.databaseNV[j]->getNgayVao() == ngay_nhap && nv.databaseNV[j]->getNgayNghi() == ngay_nhap)
        {
            this->luongNV += luong_theo_ngay * (ngaynghi - ngayvao + 1);
        }
        // Neu nhan vien j duoc nhan vao nhung thanh truoc va nghi viec trong thang dang xet
        else if (nv.databaseNV[j]->getCheckDeleteSo() == 1 && nv.databaseNV[j]->getNgayNghi() == ngay_nhap)
        {
            this->luongNV += luong_theo_ngay * ngaynghi;
        }
        // Neu nhan vien j duoc nhan vao nhung thang truoc va nghi viec trong nhung thang sau
        else if (nv.databaseNV[j]->getCheckDeleteSo() == 1 && ngay_nhap < nv.databaseNV[j]->getNgayNghi() && nv.databaseNV[j]->getNgayVao() < ngay_nhap)
        {
            this->luongNV += nv.databaseNV[j]->getLuong();
        }
        // Nhan vien con hoat dong, duoc nhan truoc thang dang xet
        else if (nv.databaseNV[j]->getCheckDeleteSo() == 0 && nv.databaseNV[j]->getNgayVao() < ngay_nhap)
        {
            this->luongNV += nv.databaseNV[j]->getLuong();
        }
    }
    for (int j = 0; j < hd.getLengthHD(); j++)
    {

        if (hd.databaseHD[j]->getTrangThaiSo() == 2 && hd.databaseHD[j]->getNgayLap() == ngay_nhap)
        {
            this->doanh_thu = this->doanh_thu + hd.databaseHD[j]->getThanhTien();
        }
    }
    for (int j = 0; j < hd.getLengthHD(); j++)
    {
        if (hd.databaseHD[j]->getTrangThaiSo() == 1 && hd.databaseHD[j]->getNgayLap() == ngay_nhap)
            this->von = this->von + hd.databaseHD[j]->getThanhTien();
    }
    this->loi_nhuan = this->doanh_thu - this->luongNV - this->von;

    cout << "\n" << setw(69) << " " << "BAO CAO THANG " << month << "/" << year << endl;
    cout << setw(47) << " "; for (int i = 1; i <= 67; i++) cout << "-"; cout << endl;
    cout << setw(47) << " " << "|  Tong luong nhan vien (nghin)  |" << setw(13) << " " << left << setw(19) << round((this->luongNV / 1000) * 10) / 10 << "|" << endl;
    cout << setw(47) << " "; for (int i = 1; i <= 67; i++) cout << "-"; cout << endl;
    cout << setw(47) << " " << "|          Von (nghin)           |" << setw(13) << " " << left << setw(19) << round((this->von / 1000) * 10) / 10 << "|" << endl;
    cout << setw(47) << " "; for (int i = 1; i <= 67; i++) cout << "-"; cout << endl;
    cout << setw(47) << " " << "|       Doanh thu (nghin)        |" << setw(13) << " " << left << setw(19) << round((this->doanh_thu / 1000) * 10) / 10 << "|" << endl;
    cout << setw(47) << " "; for (int i = 1; i <= 67; i++) cout << "-"; cout << endl;
    cout << setw(47) << " " << "|       Loi nhuan (nghin)        |" << setw(13) << " " << left << setw(19) << round((this->loi_nhuan / 1000) * 10) / 10 << "|" << endl;
    cout << setw(47) << " "; for (int i = 1; i <= 67; i++) cout << "-"; cout << endl;
}

void ThongKe::ThongKeNam(QuanLyNV &nv, QuanLyHD &hd)
{
    this->luongNV = 0;
    this->loi_nhuan = 0;
    this->doanh_thu = 0;
    this->von = 0;

    int year;
    cout << "\t\t\t\t\t\tNhap nam can thong ke: ";
    year = hd.In_double();

    time_t now = time(0);
    tm *ltm = localtime(&now);
    int yy = 1900 + ltm->tm_year; // nam hien tai
    int mm = 1 + ltm->tm_mon;     // thang hien tai
    if (year > yy)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
        cout << "\t\t\t\t\t\tKhong co du lieu!" << endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
        return;
    }

    cout << "\n" << setw(72) << " " << "BAO CAO NAM " << year << endl;
    cout << setw(30) << " "; for (int i = 1; i <= 99; i++) cout << "-"; cout << endl;
    cout << setw(30) << " " << "|          |" << " Tong luong nhan vien (nghin) |" << "  Von (nghin)  |" << " Doanh thu (nghin) |" << " Loi nhuan (nghin) |" << endl;
    cout << setw(30) << " "; for (int i = 1; i <= 99; i++) cout << "-"; cout << endl;

    int month;
    if (year < yy) mm = 12;
    for (month = 1; month <= mm; month++)
    {
        Date hientai(1, month, year);
        double tmpLuong = 0, tmpDoanhThu = 0, tmpVon = 0, tmpLoiNhuan = 0;

        for (int j = 0; j < nv.getLengthNV(); j++)
        {
            int luong_theo_ngay = nv.databaseNV[j]->getLuong() / DemNgayThang(month, year);
            int ngayvao = nv.databaseNV[j]->getNgayVao().getNgay();
            int ngaynghi = nv.databaseNV[j]->getNgayNghi().getNgay();

            // Neu nhan vien j duoc nhan vao thang dang xet va khong nghi viec trong thang do
            if (nv.databaseNV[j]->getNgayVao() == hientai && nv.databaseNV[j]->getNgayNghi() != hientai)
            {
                if (nv.databaseNV[j]->getNgayVao().getNgay() == 1)
                {
                    tmpLuong += nv.databaseNV[j]->getLuong();
                    this->luongNV += nv.databaseNV[j]->getLuong();
                }
                else
                {
                    this->luongNV += luong_theo_ngay * (DemNgayThang(month, year) - ngayvao + 1);
                    tmpLuong += luong_theo_ngay * (DemNgayThang(month, year) - ngayvao + 1);
                }
            }
            // Neu nhan vien j duoc nhan vao thang dang xet va nghi viec trong thang do
            else if (nv.databaseNV[j]->getNgayVao() == hientai && nv.databaseNV[j]->getNgayNghi() == hientai)
            {
                this->luongNV += luong_theo_ngay * (ngaynghi - ngayvao + 1);
                tmpLuong += luong_theo_ngay * (ngaynghi - ngayvao + 1);
            }
            // Neu nhan vien j duoc nhan vao nhung thanh truoc va nghi viec trong thang dang xet
            else if (nv.databaseNV[j]->getCheckDeleteSo() == 1 && nv.databaseNV[j]->getNgayNghi() == hientai)
            {
                this->luongNV += luong_theo_ngay * ngaynghi;
                tmpLuong += luong_theo_ngay * ngaynghi;
            }
            // Neu nhan vien j duoc nhan vao nhung thang truoc va nghi viec trong nhung thang sau
            else if (nv.databaseNV[j]->getCheckDeleteSo() == 1 && hientai < nv.databaseNV[j]->getNgayNghi() && nv.databaseNV[j]->getNgayVao() < hientai)
            {
                this->luongNV += nv.databaseNV[j]->getLuong();
                tmpLuong += nv.databaseNV[j]->getLuong();
            }
            // Nhan vien con hoat dong, duoc nhan truoc thang dang xet
            else if (nv.databaseNV[j]->getCheckDeleteSo() == 0 && nv.databaseNV[j]->getNgayVao() < hientai)
            {
                this->luongNV += nv.databaseNV[j]->getLuong();
                tmpLuong += nv.databaseNV[j]->getLuong();
            }
        }
        for (int j = 0; j < hd.getLengthHD(); j++)
        {
            if (hd.databaseHD[j]->getTrangThaiSo() == 2 && hd.databaseHD[j]->getNgayLap() == hientai)
            {
                this->doanh_thu = this->doanh_thu + hd.databaseHD[j]->getThanhTien();
                tmpDoanhThu = tmpDoanhThu + hd.databaseHD[j]->getThanhTien();
            }
        }
        for (int j = 0; j < hd.getLengthHD(); j++)
        {
            if (hd.databaseHD[j]->getTrangThaiSo() == 1 && hd.databaseHD[j]->getNgayLap() == hientai){
                this->von = this->von + hd.databaseHD[j]->getThanhTien();
                tmpVon = tmpVon + hd.databaseHD[j]->getThanhTien();
            } 
        }
        tmpLoiNhuan = tmpDoanhThu - tmpLuong - tmpVon;
        cout << setw(30) << " "
             << "| Thang " << left << setw(3) << month << "|" << setw(12) << " " << left << setw(18) << round((tmpLuong / 1000) * 10) / 10 << "|"
             << setw(5) << " " << left << setw(10) << round((tmpVon / 1000) * 10) / 10 << "|"
             << setw(7) << " " << left << setw(12) << round((tmpDoanhThu / 1000) * 10) / 10 << "|"
             << setw(7) << " " << left << setw(12) << round((tmpLoiNhuan / 1000) * 10) / 10 << "|";
        cout << "\n"
             << setw(30) << " ";
        for (int i = 1; i <= 99; i++)
            cout << "-";
        cout << endl;
    }
    this->loi_nhuan = this->doanh_thu - this->von - this->luongNV;
    cout << setw(30) << " " << "|   Tong   |" << setw(12) << " " << left << setw(18) << round((this->luongNV / 1000) * 10) / 10 << "|"
         << setw(5) << " " << left << setw(10) << round((this->von / 1000) * 10) / 10 << "|"
         << setw(7) << " " << left << setw(12) << round((this->doanh_thu / 1000) * 10) / 10 << "|"
         << setw(7) << " " << left << setw(12) << round((this->loi_nhuan / 1000) * 10) / 10 << "|";
    cout << "\n" << setw(30) << " "; for (int i = 1; i <= 99; i++) cout << "-"; cout << endl;
}