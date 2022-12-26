#pragma once
#include "Date.h"
#include <iomanip>

class QuanLyNV;
class NhanVien
{
private:
    int static count_id;
    int maNV;
    string hodem;
    string tenNV;
    int gioi_tinh;
    Date ngay_sinh;
    string sdt;
    string dia_chi;
    double luong;
    int chuc_vu;
    int check_delete;
    Date ngay_vao;
    Date ngay_nghi;

public:
    NhanVien(int = -1, string = "", string = "", int = 0, Date = Date(0, 0, 0), string = "", string = "", int = 0, double = 0, int = 0, Date = Date(0, 0, 0), Date = Date(0, 0, 0));
    ~NhanVien();
    // Ham Setter
    void setCountID(int);
    void setMaNV(int);
    void setTenNV(string);
    void setHoDemNV(string);
    void setGioiTinh(int);
    void setNgaySinh(Date);
    void setSDT(string);
    void setDiaChi(string);
    void setLuong();
    void setChucVu(int);
    void setCheckDelete(int);
    void setNgayVao();
    void setNgayNghi();
    // Ham Getter
    int getCountID();
    int getMaNV();
    string getTenNV();
    string getHoDemNV();
    string getHoTenNV();
    string getGioiTinh();
    Date getNgaySinh();
    string getSDT();
    string getDiaChi();
    double getLuong();
    string getChucVu();
    string getCheckDelete();
    int getCheckDeleteSo();
    Date getNgayVao();
    Date getNgayNghi();

    void try_catchHoten(string &);
    void try_catchDiaChi(string &);
    // Ham da nang hoa
    friend ostream &operator<<(ostream &, NhanVien &);
    friend istream &operator>>(istream &, NhanVien &);
};