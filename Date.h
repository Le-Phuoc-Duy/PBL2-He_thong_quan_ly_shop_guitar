#pragma once
#include <iostream>
#include <string>
#include <ctime>
#include <Windows.h>
using namespace std;
class Date
{
private:
    int ngay, thang, nam, gio, phut;

public:
    // Ham getter
    int getNgay();
    int getThang();
    int getNam();
    int getGio();
    int getPhut();
    // Ham setter
    void setNgay(int);
    void setThang(int);
    void setNam(int);
    void setGio(int);
    void setPhut(int);
    // Ham constructor & destructor
    Date();
    Date(int, int, int, int = 0, int = 0);
    ~Date();
    // Ham da nang hoa
    friend ostream &operator<<(ostream &, const Date &);
    friend istream &operator>>(istream &, Date &);
    void Input();
    int operator==(Date);
    int operator!=(Date);
    int operator<(Date);
    int operator>(Date);
    friend bool HamThoiGian(const Date &);
};