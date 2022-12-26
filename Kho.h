#pragma once
#include "Date.h"
#include "PhanLoai.h"

class QuanLyHang;
class Kho
{
private:
    int static count_id;
    int maHH;
    string tenHH;
    int maPL;
    double gia_von;
    double gia_ban;
    int so_luong;
    int check_delete;

public:
    // Ham constructor & destructor
    Kho(int = -1, string = "", double = 0, double = 0, int = 0, int = 0, int = 0);
    ~Kho();
    // Ham getter
    int getMaHH();
    string getTenHH();
    int getmaPL();
    double getGiaVon();
    double getGiaBan();
    int getSoLuong();
    int getCheckDeleteSo();
    string getCheckDelete();
    int getCountID();
    // Ham setter
    void setMaHH(int);
    void setTenHH(string);
    void setGiaVon(double);
    void setGiaBan(double);
    void setSoLuong(int);
    void setNgayNhap(Date);
    void setMaPL(int);
    void setCheckDelete(int);

    void try_catchTenHH(string &);
    friend ostream &operator<<(ostream &, Kho &);
    void Input(QuanLyHang &, string, int);
};
