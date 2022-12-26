#include "QuanLyKH.h"
#include "QuanLyHD.h"

QuanLyKH::QuanLyKH()
{
    this->lengthKH = 0;
}

QuanLyKH::~QuanLyKH() {}

int QuanLyKH::getLengthKH()
{
    return this->lengthKH;
}
void QuanLyKH::setLengthKh(int length)
{
    this->lengthKH = length;
}
// Tìm kiếm khach hang theo mã KH
int QuanLyKH::FindIndex(const int &index)
{
    for (int i = 0; i < this->lengthKH; i++)
    {
        if (databaseKH[i]->getMaKH() == index)
            return i;
    }
    return -1;
}

// Tìm kiếm khach hang theo tên KH
int QuanLyKH::FindIndexTen(const string &index)
{
    for (int i = 0; i < this->lengthKH; i++)
    {
        if (databaseKH[i]->getTenKH() == index)
            return i;
    }
    return -1;
}
// Tìm kiếm khach hang theo sdt
int QuanLyKH::FindIndexSDT(const string &index)
{
    for (int i = 0; i < this->lengthKH; i++)
    {
        if (databaseKH[i]->getSDT() == index)
            return i;
    }
    return -1;
}
void QuanLyKH::Insert()
{
    KhachHang *khachhang = new KhachHang;
    cin >> *khachhang;
    // kiem tra so dien thoai khach hang co trung khong
    int n = FindIndexSDT(khachhang->getSDT());
    if (n != -1)
    {
        if (databaseKH[n]->getCheckDeleteSo() == 1){
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);cout << "\t\t\t\t\t\tSo dien thoai da bi xoa. Vao thay doi thong tin khach hang de khoi phuc!" << endl;SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
        }
        else {SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);cout << "\t\t\t\t\t\tSo dien thoai da ton tai!" << endl;SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);}
        delete khachhang;
        return;
    }
    string ho = khachhang->getHoDemKH();    HamChuanHoa(ho);    khachhang->setHoDemKH(ho);
    string ten = khachhang->getTenKH();     HamChuanHoa(ten);   khachhang->setTenKH(ten);

    databaseKH.push_back(khachhang);
    this->lengthKH++;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),6);cout << "\t\t\t\t\t\tThem khach hang thanh cong!" << endl;SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
}

void QuanLyKH::Readf()
{
    ifstream filein;
    filein.open("KhachHang.txt");

    if (!filein)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);cout << "\n\t\t\t\t\t\tLoi: File khong mo duoc." << endl;SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
        return;
    }
    filein.seekg(0, ios::end);
    if (filein.tellg() == 0) return;
    filein.seekg(0, ios::beg);
    int maKH, so_diem;
    string tenKH, hodem, sdt;
    char x;
    string check_delete_chuoi; int check_delete;
    while (filein.eof() != true)
    {
        filein >> maKH;
        filein.ignore(2); getline(filein, hodem, ',');
        filein.ignore(); getline(filein, tenKH, ',');
        filein.ignore(); getline(filein, sdt, ',');
        filein.ignore(); filein >> so_diem;
        filein.ignore(2); getline(filein, check_delete_chuoi);
        if (check_delete_chuoi == "Da Xoa") check_delete = 1;
        else if (check_delete_chuoi == "Ton Tai") check_delete = 0;
        HamChuanHoa(tenKH); HamChuanHoa(hodem);
        KhachHang *khachhang = new KhachHang(maKH, hodem, tenKH, sdt, so_diem, check_delete);
        databaseKH.push_back(khachhang);
        (this->lengthKH)++;
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),6);cout << "\n\t\t\t\t\t\tDoc file thanh cong!" << endl;SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
    filein.close();
}

void QuanLyKH::Show(int trang_thai)
{
    if (trang_thai == 0){
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),6);cout << "\n"<< setw(71) << " " <<"DANH SACH KHACH HANG"<< endl;SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
    }else{
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),6);cout << "\n"<< setw(67) << " " <<"DANH SACH KHACH HANG DA XOA"<< endl;SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
    }
    cout << setw(52) << " "; for (int i = 1; i <= 58;i++) cout << "-";
    cout << "\n" << setw(52) << " " << "| Ma KH |" << "    Ten Khach Hang    |" << "     SDT     |" << "  So Diem  |" << endl;
    cout << setw(52) << " "; for (int i = 1; i <= 58;i++) cout << "-";

    for (int i = 0; i < this->getLengthKH(); i++)
    {
        if (databaseKH[i]->getCheckDeleteSo() == trang_thai) cout << *databaseKH[i];
    }
    cout << "\n" << setw(52) << " "; for (int i = 1; i <= 58;i++) cout << "-";cout << endl;
}
void QuanLyKH::Find()
{
    int luachon;
    do{    
        system("cls");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);cout << setw(48) << " "; for (int i = 1; i <= 65; i++) cout << "-";SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11); 
        cout << "\n\n";
        cout << setw(74) << " " << "1. Tim theo SDT" << endl;
        cout << setw(74) << " " << "2. Tim theo ten" << endl;
        cout << setw(74) << " " << "0. Thoat" << endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);cout << "\n" << setw(48) << " "; for (int i = 1; i <= 65; i++) cout << "-";SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
        cout << "\n\t\t\t\t\t\tNhap lua chon: "; luachon = So_nguyen();
        if (luachon == 1){
            string sdt = KiemTraSDT();
            int n = FindIndexSDT(sdt);
            if (n == -1)
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);cout << "\t\t\t\t\t\tSDT khong ton tai!" << endl;SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
            }
            else
            {
                cout << setw(52) << " "; for (int i = 1; i <= 71;i++) cout << "-";
                cout << "\n" << setw(52) << " " << "| Ma KH |" << "    Ten Khach Hang    |" << "     SDT     |" << "  So Diem  |" << " Trang Thai |"<<endl;
                cout << setw(52) << " "; for (int i = 1; i <= 71;i++) cout << "-";
                cout << *databaseKH[n] <<" " << left << setw(11) << databaseKH[n]->getCheckDelete() << "|";
                cout << "\n" <<setw(52) << " "; for (int i = 1; i <= 71;i++) cout << "-";cout << endl;
            }
        }else if (luachon == 2)
        {
            string tenKH;
            fflush(stdin);
            cout << "\t\t\t\t\t\tNhap ten: ";    getline(cin,tenKH);
            HamChuanHoa(tenKH);
            if (FindIndexTen(tenKH) == -1){
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);cout << "\t\t\t\t\t\tTen khong ton tai!" << endl;SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
            }else{
                cout << setw(52) << " "; for (int i = 1; i <= 71;i++) cout << "-";
                cout << "\n" << setw(52) << " " << "| Ma KH |" << "    Ten Khach Hang    |" << "     SDT     |" << "  So Diem  |" << " Trang Thai |"<<endl;
                cout << setw(52) << " "; for (int i = 1; i <= 71;i++) cout << "-";
                for (int i = 0; i < this->lengthKH; i++)
                {
                    if (databaseKH[i]->getTenKH() == tenKH) cout << *databaseKH[i] <<" " << left << setw(11) << databaseKH[i]->getCheckDelete() << "|";      
                }
                cout << "\n" <<setw(52) << " "; for (int i = 1; i <= 71;i++) cout << "-";cout << endl;
            }
        }
        else if (luachon){
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);cout << "\t\t\t\t\t\tLua chon khong hop le!" << endl;SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
        }
        else break;
    cout << "\t\t\t\t\t\t"; system("pause");
    }while(luachon);
}
void QuanLyKH::Writef()
{
    ofstream fileout;
    fileout.open("KhachHang.txt");
    for (int i = 0; i < this->getLengthKH(); i++)
    {
        if (i != 0) fileout << endl;
        fileout << databaseKH[i]->getMaKH() << ", " <<  databaseKH[i]->getHoDemKH() << ", "<<  databaseKH[i]->getTenKH() 
        << ", " << databaseKH[i]->getSDT() << ", " <<  databaseKH[i]->getSoDiem() << ", " << databaseKH[i]->getCheckDelete();
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),6);cout << "\t\t\t\t\t\tGhi vao file thanh cong!" << endl;SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
    fileout.close();
}

void QuanLyKH::Remove()
{
    int ma;
    Show(0);
    cout << "\t\t\t\t\t\tMa khach hang can xoa: "; ma = Nhap_ma();
    int n = FindIndex(ma);
    if (n == -1 || databaseKH[n]->getCheckDeleteSo() == 1)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);cout << "\t\t\t\t\t\tMa khong ton tai hoac da bi xoa!" << endl;SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
        return;
    }
    else{
        this->databaseKH[n]->setCheckDelete(1);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),6);cout << "\t\t\t\t\t\tXoa thanh cong!" << endl;SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
    }
}

void QuanLyKH::Update(QuanLyHD& ql_hd){
    int luachon;
    do{    
        system("cls");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);cout << setw(48) << " "; for (int i = 1; i <= 65; i++) cout << "-";SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);
        cout << "\n\n";
        cout << setw(69) << " " << "1. Cap nhat ten" << endl;
        cout << setw(69) << " " << "2. Cap nhat so dien thoai" << endl;
        cout << setw(69) << " " << "3. Khoi phuc trang thai" << endl;
        cout << setw(69) << " " << "0. Thoat" << endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);cout << "\n" << setw(48) << " "; for (int i = 1; i <= 65; i++) cout << "-";SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
        cout << "\n\t\t\t\t\t\tNhap lua chon: "; luachon = So_nguyen();
        
        if (luachon < 0 || luachon > 3){
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);  cout << "\t\t\t\t\t\tLua chon khong hop le!" << endl;SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
            cout << "\t\t\t\t\t\t"; system("pause");
            continue;
        }
        else if (luachon){
            if (luachon == 3) Show(1);
            else Show(0);
            int ma; 
            cout << "\n\t\t\t\t\t\tMa so khach hang can cap nhat: ";        ma = Nhap_ma();
            int n = FindIndex(ma);
            if (luachon != 3){
                if (n == -1 || databaseKH[n]->getCheckDeleteSo() == 1){
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);cout << "\t\t\t\t\t\tMa khong ton tai hoac da xoa!" << endl;SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
                    cout << "\t\t\t\t\t\t"; system("pause");
                    continue;
                }
            }
            else{
                if (n == -1 || databaseKH[n]->getCheckDeleteSo() == 0){
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);cout << "\t\t\t\t\t\tKhong ton tai khach hang da xoa nhu tren!" << endl;SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
                    cout << "\t\t\t\t\t\t"; system("pause");
                    continue;
                }
            }
            switch (luachon){
                case 1:
                {
                    string ten, hodem;
                    do{
                        try{
                            cout << "\t\t\t\t\t\tNhap ho dem khach hang: ";
                            databaseKH[n]->try_catchHoten(hodem);
                            break;
                        }
                        catch(const char* e){
                            cout << e << endl;
                        }
                    }while(1);

                    do{
                        try{
                            cout << "\t\t\t\t\t\tNhap ten nhan vien: ";
                            databaseKH[n]->try_catchHoten(ten);
                            break;
                        }
                        catch(const char* e){
                            cout << e << endl;
                        }
                    }while(1);
                    HamChuanHoa(ten);   HamChuanHoa(hodem);
                    databaseKH[n]->setTenKH(ten);
                    databaseKH[n]->setHoDemKH(hodem);
                    break;
                }
                case 2:
                {
                    string sdt = KiemTraSDT();
                    if (FindIndexSDT(sdt) != -1){
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),6);cout << "\t\t\t\t\t\tSDT da ton tai. Cap nhat khong thanh cong!" << endl;SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
                        break;
                    }
                    // bien SDT luu SDT cu
                    string SDT = databaseKH[FindIndex(ma)]->getSDT();
                    databaseKH[n]->setSDT(sdt);
                    // cap nhat so dien thoai moi trong danh sach hoa don
                    int m = ql_hd.FindIndexKH(SDT);
                    while (m != -1){
                        ql_hd.databaseHD[m]->setSDT(sdt);
                        m = ql_hd.FindIndexKH(SDT);
                    }
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),6);cout << "\n\t\t\t\t\t\tCap nhat thanh cong!" << endl;SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
                    break;
                }
                case 3:
                {
                    databaseKH[n]->setCheckDelete(0);
                    break;
                }
                default:
                {
                    break;
                } 
            }
            if (luachon != 2) {SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),6);cout << "\n\t\t\t\t\t\tCap nhat thanh cong!" << endl;SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);}
        }
        else break;
    cout << "\t\t\t\t\t\t"; system("pause");
    }while(luachon);
}
bool increase(string x, string y)
{
    return (x < y) ? true : false;
}
bool descrease(string x, string y)
{
    return (x > y) ? true : false;
}

void QuanLyKH::selectionsortTen(bool (*cmp)(string,string)){
    for(int i = 0; i < this->lengthKH - 1; i++){
        int tmp = i;
        for (int j = i + 1; j < this->lengthKH; j++){
            if ((*cmp)(databaseKH[tmp]->getTenKH(), databaseKH[j]->getTenKH())){
                tmp = j;
            }
            if (databaseKH[tmp]->getTenKH() == databaseKH[j]->getTenKH()){
                if ((*cmp)(databaseKH[tmp]->getHoDemKH(), databaseKH[j]->getHoDemKH())){
                    tmp = j;
                }
            }
        }
        swap(databaseKH[i], databaseKH[tmp]);
    }
}
void QuanLyKH::Sort()
{
    int luachon;
    do{ 
        system("cls");   
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);cout << setw(48) << " "; for (int i = 1; i <= 65; i++) cout << "-";SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);
        cout << "\n\n";
        cout << setw(62)<< " " << "1. Sap xep ten khach hang theo chieu giam" << endl;
        cout << setw(62)<< " " << "2. Sap xep ten khach hang theo chieu tang" << endl;
        cout << setw(62)<< " " << "0. Thoat" << endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);cout << "\n" << setw(48) << " "; for (int i = 1; i <= 65; i++) cout << "-";SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
        cout << "\n\t\t\t\t\t\tNhap lua chon: "; luachon = So_nguyen();
        
        if (luachon == 0) break;
        switch(luachon){
            case 1:
            {
                selectionsortTen(increase);
                Show(0);
                break;
            }
            case 2:
            {
                selectionsortTen(descrease);
                Show(0);
                break;
            }
            default:
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);cout << "\t\t\t\t\t\tLua chon khong hop le!" << endl;SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
                break;

            }
        }
    cout << "\t\t\t\t\t\t"; system("pause");
    }while(luachon);
}