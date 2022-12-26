#pragma once
#include <string>
#include <windows.h>
#include <iostream>
#include <math.h>
#include <fstream>
using namespace std;

class QuanLy
{
protected:
public:
    QuanLy();
    virtual ~QuanLy();
    virtual void Readf() = 0;
    virtual void Remove() = 0;
    virtual void Writef() = 0;
    void Insert();
    void Show();
    void Update();
    void Delete();
    void Sort();
    void HamChuanHoa(string &);
    string &KiemTraSDT();
    int So_nguyen();
    int Nhap_ma();
    double In_double();
};
