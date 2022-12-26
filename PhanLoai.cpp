#include "PhanLoai.h"

int PhanLoai::count_id = 0;
// Ham getter
string PhanLoai::getTenPL()
{
    return this->tenPL;
}
int PhanLoai::getMaPL()
{
    return this->maPL;
}
int PhanLoai::getCountID()
{
    return this->count_id;
}
int PhanLoai::getCheckDeleteSo()
{
    return this->check_delete;
}
string PhanLoai::getCheckDelete()
{
    if (check_delete == 0) return "Ton Tai";
    else return "Da Xoa";
}
// Ham setter
void PhanLoai::setTenPL(string tenPL)
{
    this->tenPL = tenPL;
}
void PhanLoai::setMaPL(int maPL)
{
    this->maPL = maPL;
}
void PhanLoai::setCheckDelete(int check_delete)
{
    this->check_delete = check_delete;
}
void PhanLoai::setCountID(int count_id)
{
    this->count_id = count_id;
}
// Ham constructor & destructor
PhanLoai::PhanLoai(int maPL, string tenPL, int check_delete)
{
    if (maPL != -1)
    {
        this->maPL = maPL;
        if (count_id < maPL) count_id = maPL;
    }
    else this->maPL = ++count_id;
    this->tenPL = tenPL;
    this->check_delete = check_delete;
}
PhanLoai::~PhanLoai()
{
    count_id--;
}
istream &operator>>(istream &in, PhanLoai &pl)
{
    do
    {
        try
        {
            fflush(stdin);
            cout << "\t\t\t\t\t\tNhap ten phan loai: ";
            getline(cin, pl.tenPL);
            while (pl.tenPL[0] == ' ')
                pl.tenPL.erase(pl.tenPL.begin() + 0);
            if (pl.tenPL.empty() == 1)
                throw "\t\t\t\t\t\tNhap lai!";
            break;
        }
        catch (const char *e)
        {
            cout << e << endl;
        }
    } while (1);
    return in;
}
ostream &operator<<(ostream &out, const PhanLoai &pl)
{
    out << "\n" << right << setw(62) << "|" << left << setw(14) << pl.maPL << "|" << left << setw(23) << pl.tenPL << "|";
    return out;
}