#pragma once
#include "Date.h"
#include "List.h"
#include "ChiTietHoaDon.h"
#include "QuanLyKH.h"
#include "QuanLyNV.h"
#include <iomanip>
class HoaDon
{
private:
    int static count_id;
    int maHD;
    Date ngay_lap;
    double thanh_tien;
    string sdt;
    int maNV;
    List<ChiTietHoaDon *> cthd;
    int lengthCTHD;
    int trang_thai;

public:
    HoaDon(int = -1, int = 0, int = 0, string = "", Date = Date(0, 0, 0), double = 0, int = 0);
    ~HoaDon();
    // getter
    int getMaHD();
    string getSDT();
    int getLengthCTHD();
    Date getNgayLap();
    double getThanhTien();
    int getMaNV();
    int getTrangThaiSo();
    string getTrangThai();
    // setter
    void setMaHD(int);
    void setSDT(string);
    void setLengthCTHD(int);
    void setNgayLap(Date);
    void setThanhTien(double);
    void setMaNV(int);
    void setTrangThai(int);

    void Input(QuanLyKH &, QuanLyNV &, QuanLyHang &);
    friend ostream &operator<<(ostream &, HoaDon &);
    void Output(QuanLyHang &);
    friend class QuanLyHD;
};