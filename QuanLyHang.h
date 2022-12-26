#pragma once
#include "QuanLy.h"
#include "List.h"
#include "Kho.h"
#include "HoaDon.h"

class QuanLyHD;
class QuanLyHang : public QuanLy
{
private:
    List<Kho *> databaseK;
    List<PhanLoai *> databasePL;
    int lengthK;
    int lengthPL;

public:
    QuanLyHang();
    ~QuanLyHang();
    // Ham getter setter
    int getLengthK();
    void setLengthK(int);
    int getLengthPL();
    void setLengthPL(int);
    // Ham thao tac voi kho
    void Readf();
    void Show(int);
    void Insert();
    void Update();
    void Remove();
    void Writef();
    void Find();
    void Sort();
    void selectionsortGiaBan(bool (*cmp)(double, double));
    void selectionsortGiaVon(bool (*cmp)(double, double));
    int FindIndex(const int &);
    int FindIndexTen(const string &);
    int FindIndexDM(const int &);
    // Ham thao tac voi phan loai
    void ReadfPL();
    void ShowPL(int);
    void InsertPL();
    void RemovePL();
    void WritefPL();
    void FindPL();
    int FindIndexPL(const int &);
    int FindIndexTenPL(const string &);
    void UpdatePL();

    friend void Input(QuanLyHang &);
    friend void ChiTietHoaDon::InputB(QuanLyHang &hh);
    friend void ChiTietHoaDon::InputM(QuanLyHang &hh);
    friend void ChiTietHoaDon::Output(QuanLyHang &hh);
};
