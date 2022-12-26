#pragma once
#include <string>
#include <iomanip>
#include <iostream>
using namespace std;
class PhanLoai
{
private:
    int static count_id;
    int maPL;
    string tenPL;
    int check_delete;

public:
    // Ham constructor & desstructor
    PhanLoai(int = -1, string = "", int = 0);
    ~PhanLoai();
    // Ham getter
    string getTenPL();
    int getMaPL();
    int getCountID();
    int getCheckDeleteSo();
    string getCheckDelete();
    // Ham setter
    void setTenPL(string);
    void setMaPL(int);
    void setCheckDelete(int);
    void setCountID(int);

    friend istream &operator>>(istream &, PhanLoai &);
    friend ostream &operator<<(ostream &, const PhanLoai &);
};