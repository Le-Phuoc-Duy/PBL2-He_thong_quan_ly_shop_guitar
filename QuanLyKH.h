#pragma once
#include "QuanLy.h"
#include "List.h"
#include "KhachHang.h"

class QuanLyHD;
class QuanLyKH : public QuanLy{
    private:
        List<KhachHang*> databaseKH;
        int lengthKH;
    public:
        QuanLyKH();
        ~QuanLyKH();
        int getLengthKH();
        void setLengthKh(int);

        void Readf();
        void Insert();
        void Show(int);
        void Find();
        void Writef();
        void Remove();
        void Update(QuanLyHD&);
        void Sort();
        void selectionsortTen(bool (*cmp)(string, string));
        int FindIndex(const int&);
        int FindIndexSDT(const string &);
        int FindIndexTen(const string&);
        friend class QuanLyHD;
        friend class HoaDon;
};