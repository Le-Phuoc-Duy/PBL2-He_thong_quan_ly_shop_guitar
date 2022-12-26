#include "Date.h"

// Ham getter
int Date::getNgay()
{
    return this->ngay;
}
int Date::getThang()
{
    return this->thang;
}
int Date::getNam()
{
    return this->nam;
}
int Date::getGio()
{
    return this->gio;
}
int Date::getPhut()
{
    return this->phut;
}

// Ham setter
void Date::setNgay(int ngay)
{
    this->ngay = ngay;
}
void Date::setThang(int thang)
{
    this->thang = thang;
}
void Date::setNam(int nam)
{
    this->nam = nam;
}
void Date::setGio(int gio)
{
    this->gio = gio;
}
void Date::setPhut(int phut)
{
    this->phut = phut;
}

// Ham constructor & destructor
Date::Date()
{
    time_t now = time(0);
    tm *ltm = localtime(&now);
    setGio(ltm->tm_hour);
    setPhut(ltm->tm_min);
    setNgay(ltm->tm_mday);
    setThang(1 + ltm->tm_mon);
    setNam(1900 + ltm->tm_year);
}
Date::Date(int ngay, int thang, int nam, int gio, int phut)
{
    this->ngay = ngay;
    this->thang = thang;
    this->nam = nam;
    this->gio = gio;
    this->phut = phut;
}
Date::~Date() {}
void Date::Input()
{
    while (1)
    {
        try
        {
            string x;
            fflush(stdin);
            getline(cin, x);
            int n = x.length();
            if (n != 10)
                throw "";

            for (int j = 0; j < n; j++)
            {
                if (j == 2 || j == 5)
                {
                    if (x[j] != '/') throw "";
                }
                else
                {
                    if (x[j] < 48 || x[j] > 57) throw "";
                }
            }

            this->ngay = (int)(x[0] - '0') * 10 + (int)(x[1] - '0');
            this->thang = (int)(x[3] - '0') * 10 + (int)(x[4] - '0');
            this->nam = (int)(x[6] - '0') * 1000 + (int)(x[7] - '0') * 100 + (int)(x[8] - '0') * 10 + (int)(x[9] - '0');

            if (HamThoiGian(*this) == false) throw "";
            break;
        }
        catch (...)
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
            cout << "\t\t\t\t\t\tPhai nhap theo dinh dang dd/mm/yyyy (yyyy >= 1900). Nhap lai: ";
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
        }
    }
}
ostream &operator<<(ostream &out, const Date &date)
{
    if (date.gio != 0 || date.phut != 0) out << date.gio << ":" << date.phut << " ";
    if (date.ngay < 10) out << "0";
    out << date.ngay << "/";
    if (date.thang < 10) out << "0";
    out << date.thang << "/";
    out << date.nam;
    return out;
};

istream &operator>>(istream &in, Date &date)
{
    char a, b;
    in >> date.ngay >> a >> date.thang >> b >> date.nam;
    if (HamThoiGian(date) == false)
    {
        date.ngay = date.thang = 1;
        date.nam = 2000;
    }
    return in;
}
int Date::operator==(Date b)
{
    if (this->getNam() != b.getNam())
        return 0;
    else
    {
        if (this->getThang() != b.getThang())
            return 0;
        else
            return 1;
    }
}
int Date::operator!=(Date b)
{
    if (this->getNam() != b.getNam()) return 1;
    else
    {
        if (this->getThang() != b.getThang()) return 1;
        else return 0;
    }
}
int Date::operator<(Date b)
{
    if (this->getNam() > b.getNam()) return 0;
    else if (this->getNam() < b.getNam()) return 1;
    else
    {
        if (this->getThang() >= b.getThang()) return 0;
        else return 1;
    }
}
int Date::operator>(Date b)
{
    if (this->getNam() < b.getNam())
        return 0;
    else if (this->getNam() > b.getNam())
        return 1;
    if (this->getThang() < b.getThang())
        return 0;
    else if (this->getThang() > b.getThang())
        return 1;
    if (this->getNgay() <= b.getNgay())
        return 0;
    return 1;
}
bool HamThoiGian(const Date &date)
{
    bool check = true;
    if (date.thang > 12 || date.nam < 1900)
        return false;

    if (date.thang == 4 || date.thang == 6 || date.thang == 9 || date.thang == 11)
    {
        if (date.ngay > 30) return false;
    }
    else if (date.thang == 2)
    {
        if ((date.nam % 400 == 0) || (date.thang % 4 == 0 && date.nam % 100 != 0))
        {
            if (date.ngay > 29) return false;
        }
        else
        {
            if (date.ngay > 28) return false;
        }
    }
    else
    {
        if (date.ngay > 31) return false;
    }
    return check;
}