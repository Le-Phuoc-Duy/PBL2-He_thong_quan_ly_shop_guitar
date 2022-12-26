#pragma once
#include "QuanLy.h"
#include "List.h"
#include "QuanLyNV.h"
#include "QuanLyHD.h"

class QuanLyNV;
class QuanLyHD;
class ThongKe{
    private:
        double luongNV, doanh_thu, loi_nhuan, von;
    public:
        ThongKe();
        void ThongKeHomNay(QuanLyHD&);
        void ThongKeNgay(QuanLyNV&, QuanLyHD&);
        void ThongKeThang(QuanLyNV&, QuanLyHD&);
        void ThongKeNam(QuanLyNV&, QuanLyHD&);
};