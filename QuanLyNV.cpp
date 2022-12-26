#include "QuanLyNV.h"
#include "QuanLyHD.h"

QuanLyNV::QuanLyNV()
{
    this->lengthNV = 0;
}
QuanLyNV::~QuanLyNV(){}
//Ham getter, setter
void QuanLyNV::setLengthNV(int lengthNV)
{
    this->lengthNV = lengthNV;
}
int QuanLyNV::getLengthNV()
{
    return lengthNV;
}
void QuanLyNV::Readf()
{
    ifstream filein;
    filein.open("NhanVien.txt");

    if (!filein)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);cout << "\n\t\t\t\t\t\tLoi: File khong mo duoc." << endl;SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
        return;
    }
    filein.seekg(0, ios::end);
    if (filein.tellg() == 0) return;
    filein.seekg(0, ios::beg);
    string ho_dem_NV, tenNV, sdt, dia_chi, gioi_tinh_chuoi, chuc_vu_chuoi, check_delete_chuoi;
    int maNV, gioi_tinh, chuc_vu, check_delete;
    Date ngay_sinh(0,0,0),ngay_vao(0,0,0),ngay_nghi(0,0,0);
    double luongcoban, luong;
    while (filein.eof() != true)
    {
        filein >> maNV;
        filein.ignore(2); getline(filein, ho_dem_NV, ',');
        filein.ignore(); getline(filein, tenNV, ',');
        filein.ignore(); getline(filein, gioi_tinh_chuoi, ',');
        filein.ignore(); filein >> ngay_sinh;
        filein.ignore(2); getline(filein, sdt, ',');
        filein.ignore(); getline(filein, dia_chi, ',');
        filein.ignore(); getline(filein, chuc_vu_chuoi, ',');
        filein >> luong;
        filein.ignore(2); getline(filein, check_delete_chuoi, ',');
        filein.ignore(); filein >> ngay_vao;
        // kiem tra bien check co hop le khong
        if (chuc_vu_chuoi == "Quan ly") chuc_vu = 0;
        else chuc_vu = 1;
        if (check_delete_chuoi == "Da Xoa")
        {
            filein.ignore();
            filein >> ngay_nghi;
            check_delete = 1;
        } 
        else if (check_delete_chuoi == "Ton Tai") check_delete = 0;
        
        if (gioi_tinh_chuoi == "Nam") gioi_tinh = 1;  
        else if (gioi_tinh_chuoi == "Nu") gioi_tinh = 0;  
        
        HamChuanHoa(ho_dem_NV); HamChuanHoa(tenNV);
        NhanVien *nv = new NhanVien(maNV, ho_dem_NV, tenNV, gioi_tinh, ngay_sinh, sdt, dia_chi, chuc_vu, luong, check_delete, ngay_vao, ngay_nghi);
        databaseNV.push_back(nv);
        (this->lengthNV)++;
    }
    filein.close();
}
void QuanLyNV::Show(int trang_thai)
{
    if (trang_thai == 0)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
        cout << "\n" << setw(67) << " " << "DANH SACH NHAN VIEN HIEN CO" << endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    }
    else
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
        cout << "\n" << setw(67) << " " << "DANH SACH NHAN VIEN DA XOA" << endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    }
    cout << setw(12) << " "; for (int i = 1; i <= 132;i++) cout << "-";
    cout << "\n" << setw(12) << " " << "| Ma NV |" << "     Ten Nhan Vien     |" << " Gioi Tinh |"
         << " Ngay Sinh |"<< "    SDT    |"<< "          Dia Chi          |"<<"  Chuc Vu  |" << "  Luong  |"
         << "  Ngay Vao  |" << endl;
    cout << setw(12) << " "; for (int i = 1; i <= 132;i++) cout << "-";
    
    for (int i = 0; i < this->lengthNV; i++)
    {
        if (databaseNV[i]->getCheckDeleteSo() == trang_thai) cout << *databaseNV[i];
    }
    cout << "\n" <<setw(12) << " "; for (int i = 1; i <= 132;i++) cout << "-"; cout << endl;
}
void QuanLyNV::Insert()
{
    NhanVien *nv = new NhanVien;
    cin >> *nv;
    string ho = nv->getHoDemNV();   HamChuanHoa(ho);    nv->setHoDemNV(ho);
    string ten = nv->getTenNV();    HamChuanHoa(ten);   nv->setTenNV(ten);
    databaseNV.push_back(nv);
    this->lengthNV++;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
    cout << "\t\t\t\t\t\tThem nhan vien thanh cong!" << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}

void QuanLyNV::Writef()
{
    ofstream fileout;
    fileout.open("NhanVien.txt");
    for (int i = 0; i < this->getLengthNV(); i++)
    {
        if (i != 0) fileout << endl;
        fileout << databaseNV[i]->getMaNV() << ", " <<  databaseNV[i]->getHoDemNV() << ", " <<  databaseNV[i]->getTenNV() << ", " 
        << databaseNV[i]->getGioiTinh() <<  ", " << databaseNV[i]->getNgaySinh() << ", " << databaseNV[i]->getSDT() << ", " 
        << databaseNV[i]->getDiaChi() << ", " << databaseNV[i]->getChucVu() << ", " << (size_t)databaseNV[i]->getLuong() 
        << ", " << databaseNV[i]->getCheckDelete() << ", " << databaseNV[i]->getNgayVao();
        if (databaseNV[i]->getCheckDelete() == "Da Xoa") fileout << ", " << databaseNV[i]->getNgayNghi();  
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
    cout << "\t\t\t\t\t\tGhi vao file thanh cong!" << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    fileout.close();
}
void QuanLyNV::Find()
{
    int luachon;
    do{
        system("cls");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);cout << setw(48) << " "; for (int i = 1; i <= 65; i++) cout << "-";SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);
        cout << "\n\n";
        cout << setw(74) << " " << "1. Tim theo ma" << endl;
        cout << setw(74) << " " << "2. Tim theo ten" << endl;
        cout << setw(74) << " " << "0. Thoat" << endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);cout << "\n" << setw(48) << " "; for (int i = 1; i <= 65; i++) cout << "-";SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
        cout << "\n\t\t\t\t\t\tNhap lua chon: "; luachon = So_nguyen();
        if (luachon == 1){
            cout << "\t\t\t\t\t\tMa can tim:";      int maNV = Nhap_ma();
            int n = FindIndex(maNV);
            if (n == -1){
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);cout << "\t\t\t\t\t\tMa khong ton tai!" << endl;SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
            }else{
                cout << setw(12) << " "; for (int i = 1; i <= 144;i++) cout << "-";
                cout << "\n" << setw(12) << " " << "| Ma NV |" << "     Ten Nhan Vien     |" << " Gioi Tinh |"
                << " Ngay Sinh |"<< "    SDT    |"<< "          Dia Chi          |"<<"  Chuc Vu  |" << "  Luong  |"
                << "  Ngay Vao  |"<< " Ngay Nghi |" << endl;
                cout << setw(12) << " "; for (int i = 1; i <= 144;i++) cout << "-";
                if(databaseNV[n]->getCheckDeleteSo() == 0) cout << *databaseNV[n] << "           |";
                else cout << *databaseNV[n] << right << setw(2) << databaseNV[n]->getNgayNghi() << " |";
                cout << "\n" << setw(12) << " "; for (int i = 1; i <= 144; i++) cout << "-"; cout << endl;
            }
        }else if (luachon == 2)
        {
            string tenNV;
            fflush(stdin);
            cout << "\t\t\t\t\t\tNhap ten: ";    getline(cin,tenNV);
            HamChuanHoa(tenNV);
            if (FindIndexTen(tenNV) == -1){
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);cout << "\t\t\t\t\t\tTen khong ton tai!" << endl;SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
            }else{
                cout << setw(12) << " "; for (int i = 1; i <= 144;i++) cout << "-";
                cout << "\n" << setw(12) << " " << "| Ma NV |" << "     Ten Nhan Vien     |" << " Gioi Tinh |"
                << " Ngay Sinh |"<< "    SDT    |"<< "          Dia Chi          |"<<"  Chuc Vu  |" << "  Luong  |"
                << "  Ngay Vao  |"<< " Ngay Nghi |" << endl;
                cout << setw(12) << " "; for (int i = 1; i <= 144;i++) cout << "-";
                for (int i = 0; i < this->lengthNV; i++)
                {
                    if (databaseNV[i]->getTenNV() == tenNV){
                        if (databaseNV[i]->getCheckDeleteSo() == 0) cout << *databaseNV[i] << "           |";
                        else cout << *databaseNV[i] << right << setw(1) << databaseNV[i]->getNgayNghi() << " |";
                    }       
                }
                cout << "\n" << setw(12) << " "; for (int i = 1; i <= 144; i++) cout << "-"; cout << endl;
            }
        } else if (luachon != 0){
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);cout << "\t\t\t\t\t\tLua chon khong hop le!" << endl;SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
        }
        else break;
        cout << "\t\t\t\t\t\t"; system("pause");
    }while(luachon);
}
int QuanLyNV::FindIndex(const int& index){
    for (int i = 0; i < this->lengthNV; i++)
    {
        if (databaseNV[i]->getMaNV() == index) return i;
    }
    return -1;
}
int QuanLyNV::FindIndexTen(const string& index){
    for (int i = 0; i < this->lengthNV; i++)
    {
        if (databaseNV[i]->getTenNV() == index) return i;
    }
    return -1;
}
bool down(string x, string y)
{
    return (x < y) ? true : false;
}
bool up(string x, string y)
{
    return (x > y) ? true : false;
}

void QuanLyNV::selectionsortTen(bool (*cmp)(string,string)){
    for(int i = 0; i < this->lengthNV - 1; i++){
        int tmp = i;
        for (int j = i + 1; j < this->lengthNV; j++){
            if ((*cmp)(databaseNV[tmp]->getTenNV(), databaseNV[j]->getTenNV())){
                tmp = j;
            }
            if (databaseNV[tmp]->getTenNV() == databaseNV[j]->getTenNV()){
                if ((*cmp)(databaseNV[i]->getHoDemNV(), databaseNV[j]->getHoDemNV())){
                    tmp = j;
                }
            }
        }
        swap(databaseNV[i], databaseNV[tmp]);
    }
}

void QuanLyNV::Sort()
{
    int luachon;
    do{   
        system("cls");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);cout << setw(48) << " "; for (int i = 1; i <= 65; i++) cout << "-";SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);
        cout << "\n\n";
        cout << setw(62)<< " " << "1. Sap xep ten nhan vien theo chieu giam" << endl;
        cout << setw(62)<< " " << "2. Sap xep ten nhan vien theo chieu tang" << endl;
        cout << setw(62)<< " " << "0. Thoat" << endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);cout << "\n" << setw(48) << " "; for (int i = 1; i <= 65; i++) cout << "-";SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
        cout << "\n\t\t\t\t\t\tNhap lua chon: "; luachon = So_nguyen();
        if (luachon == 0) break;
        switch(luachon){
            case 1:
            {
                selectionsortTen(down);
                Show(0);
                break;
            }
            case 2:
            {
                selectionsortTen(up);
                Show(0);
                break;
            }
            default:
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
                cout << "\t\t\t\t\t\tLua chon khong hop le!" << endl;
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
                break;

            }
        }
        cout << "\t\t\t\t\t\t"; system("pause");
    }while(luachon);
}

void QuanLyNV::Update(){
    int luachon;
    do{    
        system("cls");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);cout << setw(48) << " "; for (int i = 1; i <= 65; i++) cout << "-";SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);
        cout << "\n\n";
        cout << setw(68) << " " << "1. Cap nhat ten" << endl;
        cout << setw(68) << " " << "2. Cap nhat gioi tinh" << endl;
        cout << setw(68) << " " << "3. Cap nhat ngay sinh" << endl;
        cout << setw(68) << " " << "4. Cap nhat so dien thoai" << endl;
        cout << setw(68) << " " << "5. Cap nhat dia chi" << endl;
        cout << setw(68) << " " << "6. Cap nhat chuc vu" << endl;
        cout << setw(68) << " " << "0. Thoat" << endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);cout << "\n" << setw(48) << " "; for (int i = 1; i <= 65; i++) cout << "-";SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
        cout << "\n\t\t\t\t\t\tNhap lua chon: "; luachon = So_nguyen();

        if (luachon < 0 || luachon > 6){
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);cout << "\t\t\t\t\t\tLua chon khong hop le!"<< endl;SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
            cout << "\t\t\t\t\t\t"; system("pause");
            continue;
        }
        else if (luachon != 0){
            Show(0);
            int nv; cout << "\n\t\t\t\t\t\tMa so nhan vien can cap nhat: ";
            nv = Nhap_ma();
            int n = FindIndex(nv);
            // Kiem tra xem ma co ton tai khong
            if (n == -1 || databaseNV[n]->getCheckDeleteSo() == 1){
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);cout << "\t\t\t\t\t\tMa khong ton tai hoac da xoa!" << endl;SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
                cout << "\t\t\t\t\t\t"; system("pause");
                continue;
            }
            switch (luachon){
                case 1:
                {
                    string tenNV, hodem;
                    do{
                        try{
                            cout << "\t\t\t\t\t\tNhap ho dem nhan vien: ";
                            databaseNV[n]->try_catchHoten(hodem);
                            break;
                        }
                        catch(const char* e){
                            cout << e << endl;
                        }
                    }while(1);

                    do{
                        try{
                            cout << "\t\t\t\t\t\tNhap ten nhan vien: ";
                            databaseNV[n]->try_catchHoten(tenNV);
                            break;
                        }
                        catch(const char* e){
                            cout << e << endl;
                        }
                    }while(1);
                    HamChuanHoa(tenNV); HamChuanHoa(hodem);
                    databaseNV[n]->setTenNV(tenNV);
                    databaseNV[n]->setHoDemNV(hodem);
                    break;
                }
                case 2:
                {
                    int gioitinh;
                    do{
                        cout << "\t\t\t\t\t\tGioi tinh :    1.Nam       0. Nu" << endl;
                        cout << "\n\t\t\t\t\t\tNhap lua chon: "; gioitinh = So_nguyen();
                    }while(gioitinh != 0 && gioitinh != 1);
                    databaseNV[n]->setGioiTinh(gioitinh);
                    break;
                }
                case 3:
                {
                    Date ngaysinh(0, 0, 0);
                    cout << "\t\t\t\t\t\tNhap ngay sinh nhan vien: ";   ngaysinh.Input();
                    databaseNV[n]->setNgaySinh(ngaysinh);
                    break;
                }
                case 4:
                {
                    string sdt = KiemTraSDT();
                    databaseNV[n]->setSDT(sdt);
                    break;
                }
                case 5:
                {
                    string diachi;
                    do{
                        try{
                            cout << "\t\t\t\t\t\tNhap dia chi: ";
                            databaseNV[n]->try_catchDiaChi(diachi);
                            break;
                        }
                        catch(const char* e){
                            cout << e << endl;
                        }
                    }while(1);
                    databaseNV[n]->setDiaChi(diachi);
                    break;
                }
                case 6:
                {
                    int chucvu;
                    cout << "\t\t\t\t\t\tChuc vu:     0. Quan Ly              1. Nhan vien" << endl;
                    do{ 
                        cout << "\t\t\t\t\t\tNhap lua chon: "; chucvu = So_nguyen();
                    }while(chucvu != 0 && chucvu != 1);
                    databaseNV[n]->setChucVu(chucvu);
                    databaseNV[n]->setLuong();
                    break;
                }
                default:
                {
                    break;
                } 
            }
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),6);cout << "\n\t\t\t\t\t\tCap nhat thanh cong!" << endl;SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
        }else break;
        cout << "\t\t\t\t\t\t"; system("pause");
    }while(luachon);
}
void QuanLyNV::Remove()
{
    int manv;
    Show(0);
    cout << "\t\t\t\t\t\tMa can xoa: ";   manv = Nhap_ma();
    int n = FindIndex(manv);
    if (n == -1 || databaseNV[n]->getCheckDeleteSo() == 1){
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
        cout << "\t\t\t\t\t\tMa khong ton tai hoac da bi xoa!" << endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
        return;
    }
    else{
        this->databaseNV[n]->setNgayNghi();
        this->databaseNV[n]->setCheckDelete(1);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
        cout << "\t\t\t\t\t\tXoa nhan vien thanh cong!" << endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    }
}
