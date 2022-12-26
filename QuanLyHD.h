#pragma once
#include "QuanLy.h"
#include "List.h"
#include "QuanLyHang.h"

class QuanLyHD : public QuanLy
{
private:
    List<HoaDon *> databaseHD;
    int lengthHD;

public:
    QuanLyHD();
    ~QuanLyHD();

    int getLengthHD();
    void setLengthHD(int);

    void Insert(QuanLyNV &, QuanLyKH &, QuanLyHang &);
    int FindIndexHD(const int &);
    int FindIndexNV(const int &);
    int FindIndexKH(const string &);
    int FindIndexHH(const int &);
    void Remove();
    void Show(QuanLyHang &);
    void ShowGeneral(int);
    void Find(QuanLyNV &, QuanLyHang &, QuanLyKH &);
    void Readf();
    void Writef();

    friend class ChiTietHoaDon;
    friend class ThongKe;
    friend void QuanLyKH::Update(QuanLyHD &);
};