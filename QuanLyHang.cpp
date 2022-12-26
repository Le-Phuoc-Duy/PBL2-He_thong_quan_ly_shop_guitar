#include "QuanLyHang.h"
#include "QuanLyHD.h"

QuanLyHang::QuanLyHang()
{
    this->lengthK = 0;
    this->lengthPL = 0;
}
QuanLyHang::~QuanLyHang() {}

int QuanLyHang::getLengthK()
{
    return this->lengthK;
}

void QuanLyHang::setLengthK(int lengthK)
{
    this->lengthK = lengthK;
}

void QuanLyHang::Insert()
{
    Show(0); Show(1);
    // kiem tra ma va ten hang hoa co trung khong
    string tenHH;
    do{
        try{
            cout << "\t\t\t\t\t\tNhap ten hang hoa: ";
            databaseK[0]->try_catchTenHH(tenHH);
            break;
        }
        catch(const char* e){
            cout << e << endl;
        }
    }while(1);
    HamChuanHoa(tenHH);
    int n = FindIndexTen(tenHH);
    if (n != -1 && databaseK[n]->getCheckDeleteSo() == 1){
        int luachon1;
        do {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);cout << "\n\t\t\t\t\t\tHang hoa da bi xoa khoi kho. Ban muon khoi phuc lai khong? ";SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
            cout << "\n\t\t\t\t\t\t1. Co ";
            cout << "\n\t\t\t\t\t\t0. Khong ";
            cout << "\n\t\t\t\t\t\tNhap lua chon: "; luachon1 = So_nguyen();
            if (luachon1 == 1){
                databaseK[n]->setCheckDelete(0);
                int m = databaseK[n]->getMaHH();
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),6);cout << "\t\t\t\t\t\tKhoi phuc hang hoa thanh cong!" << endl;SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
                throw m; // Nem ma duoc khoi phuc
            }
            else if (luachon1 == 0)
            {
                return;
            }
        } while (1);
    }
    if (n != -1)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);cout << "\t\t\t\t\t\tHang hoa " << tenHH << " da ton tai. Them khong thanh cong!" << endl;SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
        return;
    }
    system("cls");
    // kiem tra ma phan loai ton tai chua
    ShowPL(0);
    cout << "\t\t\t\t\t\tHang hoa thuoc phan loai? ";     int maPL = Nhap_ma();
    int m = FindIndexPL(maPL);
    while (m == -1 || (m != -1 && databaseK[n]->getCheckDeleteSo() == 1)){
        int luachon2;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);cout << "\n\t\t\t\t\t\tMa phan loai chua ton tai! Ban lua chon?";SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
        cout << "\n\t\t\t\t\t\t1. Them phan loai moi/Khoi phuc phan loai";
        cout << "\n\t\t\t\t\t\t2. Nhap lai";
        cout << "\n\t\t\t\t\t\t0. Thoat";
        cout << "\n\t\t\t\t\t\tNhap lua chon: "; luachon2 = So_nguyen();
        if (luachon2 == 0) return;
        else if(luachon2 == 2){
            cout << "\t\t\t\t\t\tHang hoa thuoc phan loai? ";     maPL = Nhap_ma();
            m = FindIndexPL(maPL);
        }
        else if (luachon2 == 1){
            int tmp = lengthPL;
            try{
                InsertPL();
            }catch(int e){
                maPL = e;
                break;
            }
            if (lengthPL != tmp){
                maPL = databasePL[0]->getCountID();
                break;
            }
            else{
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);cout << "\t\t\t\t\t\tThem hang hoa khong thanh cong! Thuc hien lai!" << endl;SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
            }
        }
    }
    Kho *kho = new Kho;
    kho->Input(*this, tenHH, maPL);
    databaseK.push_back(kho);
    this->lengthK++;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),6);cout << "\t\t\t\t\t\tThem hang hoa thanh cong!" << endl;SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
}

void QuanLyHang::Readf()
{
    ifstream filein;
    filein.open("Kho.txt");

    if (!filein)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);cout << "\n\t\t\t\t\t\tLoi: File khong mo duoc." << endl;SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
        return;
    }
    filein.seekg(0, ios::end);
    if (filein.tellg() == 0) return;
    filein.seekg(0, ios::beg);
        int maHH, so_luong, maPL;
        string tenHH;
        double gia_von, gia_ban;
        string check_delete_chuoi;  int check_delete;
    while (filein.eof() !=true)
    {
        filein >> maHH;
        filein.ignore(2);
        getline(filein, tenHH, ',');
        filein >> gia_von;
        filein.ignore();
        filein >> gia_ban;
        filein.ignore();
        filein >> so_luong;
        filein.ignore();
        filein >> maPL;
        filein.ignore(2);
        getline(filein, check_delete_chuoi);
        // kiem tra bien check co hop le khong
        if (check_delete_chuoi == "Da Xoa") check_delete = 1;
        else if (check_delete_chuoi == "Ton Tai") check_delete = 0;
        Kho *kho = new Kho(maHH, tenHH, gia_von, gia_ban, so_luong, maPL, check_delete);
        databaseK.push_back(kho);
        (this->lengthK)++;
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),6);cout << "\n\t\t\t\t\t\tDoc file thanh cong!" << endl;SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
    filein.close();
}

// Tìm kiếm hang hoa theo mã nhân viên
int QuanLyHang::FindIndex(const int &index)
{
    for (int i = 0; i < this->lengthK; i++)
    {
        if (databaseK[i]->getMaHH() == index) return i;
    }
    return -1;
}

// Tìm kiếm hang hoa theo ten
int QuanLyHang::FindIndexTen(const string &index)
{
    for (int i = 0; i < this->lengthK; i++)
    {
        if (databaseK[i]->getTenHH() == index)
            return i;
    }
    return -1;
}


void QuanLyHang::Remove()
{
    int luachon;
    do{    
        system("cls");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);cout << setw(48) << " "; for (int i = 1; i <= 65; i++) cout << "-";SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);
        cout << "\n\n";
        cout << setw(74) << " " << "1. Xoa theo ma" << endl;
        cout << setw(74) << " " << "2. Xoa theo ten" << endl;
        cout << setw(74) << " " << "0. Thoat" << endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);cout << "\n" << setw(48) << " "; for (int i = 1; i <= 65; i++) cout << "-";SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
        cout << "\n\t\t\t\t\t\tNhap lua chon: "; luachon = So_nguyen();

        if (luachon == 1){
            int maHH;
            Show(0);
            cout << "\t\t\t\t\t\tMa can xoa: ";   maHH = Nhap_ma();
            int n = FindIndex(maHH);
            if (n == -1 || databaseK[n]->getCheckDeleteSo() == 1){
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);cout << "\t\t\t\t\t\tMa khong ton tai hoac da bi xoa!" << endl;SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
                cout << "\t\t\t\t\t\t"; system("pause");
                continue;
            }
            this->databaseK[n]->setCheckDelete(1);
            this->databaseK[n]->setSoLuong(0);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),6);cout << "\t\t\t\t\t\tXoa hang hoa thanh cong!" << endl;SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
        } 
        else if (luachon == 2){
            string tenHH;
            Show(0);
            fflush(stdin);
            cout << "\t\t\t\t\t\tNhap ten hang hoa: ";  getline(cin,tenHH);
            HamChuanHoa(tenHH);
            int n = FindIndexTen(tenHH);
            if (n == -1 || databaseK[n]->getCheckDeleteSo() == 1){
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);cout << "\t\t\t\t\t\tTen khong ton tai hoac da bi xoa!" << endl;SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
                cout << "\t\t\t\t\t\t"; system("pause");
                continue;
            }
            this->databaseK[n]->setCheckDelete(1);
            this->databaseK[n]->setSoLuong(0);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),6);cout << "\t\t\t\t\t\tXoa hang hoa thanh cong!" << endl;SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
        }
        else if (luachon){
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);cout << "\t\t\t\t\t\tLua chon khong hop le. Thoat!" << endl;SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
        }
        else break;
        cout << "\t\t\t\t\t\t"; system("pause");
    }while(luachon);
}
void QuanLyHang::Find(){
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
            cout << "\t\t\t\t\t\tMa can tim: ";    int maHH = Nhap_ma();
            int n = FindIndex(maHH);
            if (n == -1){
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);cout << "\t\t\t\t\t\tMa khong ton tai!" << endl;SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
            }else{
                    cout << setw(26) << " "; for (int i = 1; i <= 123;i++) cout << "-";
                    cout << "\n" << setw(26) << " " << "| Ma Hang |" << "           Ten Hang           |" << "    Gia Von    |" << "    Gia Ban    |" << "  So luong  |"
                    <<"      Phan Loai       |" << " Trang Thai |" << endl;
                    cout << setw(26) << " "; for (int i = 1; i <= 123;i++) cout << "-";
                    cout << *databaseK[n] << " " << left << setw(22) << databasePL[FindIndexPL(databaseK[n]->getmaPL())]->getTenPL() << "|" << left << setw(11) << databaseK[n]->getCheckDelete() << "|";
                    cout << "\n" << setw(26) << " "; for (int i = 1; i <= 123;i++) cout << "-"; cout << endl;
            }
        }else if (luachon == 2)
        {
            string tenHH;
            fflush(stdin);
            cout << "\t\t\t\t\t\tNhap ten: ";    getline(cin,tenHH);
            HamChuanHoa(tenHH);
            int n = FindIndexTen(tenHH);
            if (n == -1){
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);cout << "\t\t\t\t\t\tTen khong ton tai!" << endl;SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
            }else{
                cout << setw(26) << " "; for (int i = 1; i <= 123;i++) cout << "-";
                cout << "\n" << setw(26) << " " << "| Ma Hang |" << "           Ten Hang           |" << "    Gia Von    |" << "    Gia Ban    |" << "  So luong  |"
                <<"      Phan Loai       |" << " Trang Thai |" << endl;
                cout << setw(26) << " "; for (int i = 1; i <= 123;i++) cout << "-";
                if (databaseK[n]->getTenHH() == tenHH) cout << *databaseK[n] << " " << left << setw(22) << databasePL[FindIndexPL(databaseK[n]->getmaPL())]->getTenPL() << "|" << left << setw(11) << databaseK[n]->getCheckDelete() << "|";
                cout << "\n" << setw(26) << " "; for (int i = 1; i <= 123;i++) cout << "-"; cout << endl;  
            }
        }
        else if (luachon){
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);cout << "\t\t\t\t\t\tLua chon khong hop le. Thoat!" << endl;SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
        }else break;
        cout << "\t\t\t\t\t\t"; system("pause");
    }while(luachon);
}
void QuanLyHang::Update(){
    int luachon;
    do{   
        system("cls");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);cout << setw(48) << " "; for (int i = 1; i <= 65; i++) cout << "-";SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);
        cout << "\n\n";
        cout << setw(69) << " " << "1. Cap nhat ten" << endl;
        cout << setw(69) << " " << "2. Cap nhat phan loai" << endl;
        cout << setw(69) << " " << "3. Cap nhat gia von" << endl;
        cout << setw(69) << " " << "4. Cap nhat gia ban" << endl;
        cout << setw(69) << " " << "5. Cap nhat so luong" << endl;
        cout << setw(69) << " " << "6. Khoi phuc trang thai" << endl;
        cout << setw(69) << " " << "0. Thoat" << endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);cout << "\n" << setw(48) << " "; for (int i = 1; i <= 65; i++) cout << "-";SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
        cout << "\n\t\t\t\t\t\tNhap lua chon: "; luachon = So_nguyen();

        if (luachon == 0){
            break;
        }else if(luachon < 0 || luachon > 6){
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);cout << "\t\t\t\t\t\tLua chon khong hop le!" << endl;SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
        }
        else{
            if (luachon == 6) Show(1);
            else Show(0);
            int hh; 
            cout << "\t\t\t\t\t\tMa so hang hoa can cap nhat: ";        hh = Nhap_ma();
            int n = FindIndex(hh);
            if (luachon != 6){
                if (n == -1 || databaseK[n]->getCheckDeleteSo() == 1){
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);cout << "\t\t\t\t\t\tMa khong ton tai hoac da xoa!" << endl;SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
                    cout << "\t\t\t\t\t\t"; system("pause");
                    continue;
                }
            }
            else{
                if (n == -1 || databaseK[n]->getCheckDeleteSo() == 0){
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);cout << "\t\t\t\t\t\tKhong ton tai hang hoa da xoa nhu tren!" << endl;SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
                    cout << "\t\t\t\t\t\t"; system("pause");
                    continue;
                }
            }
            switch (luachon){
                case 1:
                {
                    string tenHH;
                    cout << "\t\t\t\t\t\tNhap ten hang hoa moi: ";  fflush(stdin); getline(cin, tenHH);
                    HamChuanHoa(tenHH);
                    while (FindIndexTen(tenHH) != -1 || tenHH.empty() == 1){
                        if (tenHH == databaseK[n]->getTenHH()) break;
                        if (FindIndexTen(tenHH) != -1) {
                            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);cout << "\t\t\t\t\t\tTen hang hoa da ton tai!";SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
                            cout << "\n\t\t\t\t\t\tNhap lai: ";
                        }
                        else cout << "\t\t\t\t\t\tNhap lai: ";
                        fflush(stdin); getline(cin, tenHH);
                        HamChuanHoa(tenHH);
                    }
                    databaseK[n]->setTenHH(tenHH);
                    break;
                }
                case 2:
                {
                    int maPL;
                    ShowPL(0);
                    cout << "\t\t\t\t\t\tMa phan loai moi? "; maPL = Nhap_ma();
                    int a = FindIndexPL(maPL);
                    if (a == -1 ){
                        int opt;
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);cout << "\t\t\t\t\t\tMa phan loai chua ton tai! Ban muon them ma phan loai moi khong?";SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
                        cout << "\n\t\t\t\t\t\t1. Co";
                        cout << "\n\t\t\t\t\t\t0. Khong" << endl;
                        cout << "\n\t\t\t\t\t\tNhap lua chon: "; opt = So_nguyen();

                        if(opt == 0) break;
                        else if (opt == 1){
                            string tenPL ;  fflush(stdin);
                            cout << "\t\t\t\t\t\tNhap ten phan loai: "; getline(cin, tenPL);
                            HamChuanHoa(tenPL);

                            while (FindIndexTenPL(tenPL) != -1 || tenPL.empty() == 1){
                                if (FindIndexTen(tenPL) != -1) {
                                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);cout << "\t\t\t\t\t\tTen phan loai da ton tai!";SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
                                    cout << "\n\t\t\t\t\t\tNhap lai: ";
                                }
                                else cout << "\t\t\t\t\t\tNhap lai: ";
                                fflush(stdin); getline(cin, tenPL);
                                HamChuanHoa(tenPL);
                            }
                    
                            PhanLoai *pl = new PhanLoai(maPL, tenPL);
                            databasePL.push_back(pl);
                            int m = (this->lengthPL) + 1; this->setLengthPL(m);
                            databaseK[n]->setMaPL(pl->getMaPL());
                            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),6);cout << "\t\t\t\t\t\tThem phan loai thanh cong!" << endl;SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
                        }
                        else{
                            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);cout << "\t\t\t\t\t\tLua chon khong hop le!" << endl;SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
                            break;
                        }
                    }else if (databaseK[a]->getCheckDeleteSo() == 1){
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);cout << "\t\t\t\t\t\tTen phan loai da bi xoa. Vao cap nhat de khoi phuc!";SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
                        break;
                    } else databaseK[n]->setMaPL(maPL);
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),6);cout << "\t\t\t\t\t\tCap nhat thanh cong!" << endl;SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
                    break;
                }
                case 3:
                {
                    double giavon;
                    cout << "\t\t\t\t\t\tNhap gia von moi: "; giavon = In_double();
                    databaseK[n]->setGiaVon(giavon);
                    break;
                }
                case 4:
                {
                    double giaban;
                    cout << "\t\t\t\t\t\tNhap gia ban moi: "; giaban = In_double();
                    databaseK[n]->setGiaBan(giaban);
                    break;
                }
                case 5:
                {
                    int soluong;
                    cout << "\t\t\t\t\t\tNhap so luong moi: "; soluong = So_nguyen();
                    databaseK[n]->setSoLuong(soluong);
                    break;
                }
                case 6:
                {
                    databaseK[n]->setCheckDelete(0);
                    break;
                }
                default:
                {
                    break;
                } 
            }
            if (luachon != 2) {SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),6);cout << "\n\t\t\t\t\t\tCap nhat thanh cong!" << endl;SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);}
        }
        cout << "\t\t\t\t\t\t"; system("pause");
    }while(luachon);
}
void QuanLyHang::Show(int trang_thai)
{
    if (trang_thai == 0){
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),6);cout << "\n"<< setw(66) << " " <<"DANH SACH CAC MAT HANG HIEN CO"<< endl;SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
    } 
    else{
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),6);cout << "\n"<< setw(67) << " "<< "DANH SACH CAC MAT HANG DA XOA"<< endl;SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
    } 
    cout << setw(26) << " "; for (int i = 1; i <= 110;i++) cout << "-";
    cout << "\n" << setw(26) << " " << "| Ma Hang |" << "           Ten Hang           |" << "    Gia Von    |" << "    Gia Ban    |" << "  So luong  |"
    <<"      Phan Loai       |" << endl;
    cout << setw(26) << " "; for (int i = 1; i <= 110;i++) cout << "-";
    for (int i = 0; i < this->lengthK; i++)
    {
        if (databaseK[i]->getCheckDeleteSo() == trang_thai){
            cout << *databaseK[i];
            int n = FindIndexPL(databaseK[i]->getmaPL());
            cout << left << setw(22) << databasePL[n]->getTenPL() << "|";
        }
    }
    cout << "\n" <<setw(26) << " "; for (int i = 1; i <= 110;i++) cout << "-";cout << endl;
}

void QuanLyHang::Writef(){
    ofstream fileout;
    fileout.open("Kho.txt");
    for (int i = 0; i < this->getLengthK(); i++)
    {
        if (i != 0) fileout << endl;
        fileout << databaseK[i]->getMaHH() << ", " <<  databaseK[i]->getTenHH() << ", " << setprecision(10) <<  databaseK[i]->getGiaVon() 
        << ", " << databaseK[i]->getGiaBan() << ", " << databaseK[i]->getSoLuong() << ", "<< databaseK[i]->getmaPL()<< ", " 
        << databaseK[i]->getCheckDelete();
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),6);cout << "\t\t\t\t\t\tGhi vao file thanh cong!" << endl;SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
    fileout.close();
}
bool up(double x, double y)
{
    return (x > y) ? true : false;
}
bool down(double x, double y)
{
    return (x < y) ? true : false;
}

void QuanLyHang::selectionsortGiaBan(bool (*cmp)(double,double)){
    for(int i = 0; i< this->lengthK-1;i++){
        int tmp = i;
        for (int j = i + 1; j < this->lengthK; j++){
            if ((*cmp)(databaseK[tmp]->getGiaBan(),databaseK[j]->getGiaBan())){
                tmp = j;                
            }
        }
        swap(databaseK[i],databaseK[tmp]);
    }
}
void QuanLyHang::selectionsortGiaVon(bool (*cmp)(double,double)){
    for(int i = 0; i< this->lengthK-1;i++){
        int tmp = i;
        for (int j = i + 1; j < this->lengthK; j++){
            if ((*cmp)(databaseK[tmp]->getGiaVon(),databaseK[j]->getGiaVon())){
                tmp = j;
            }
        }
        swap(databaseK[i],databaseK[tmp]);
    }
}
void QuanLyHang::Sort(){
    int luachon;
    do{
        system("cls");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);cout << setw(48) << " "; for (int i = 1; i <= 65; i++) cout << "-";SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);
        cout << "\n\n";
        cout << setw(62)<< " " << "1. Sap xep theo chieu giam cua gia ban" << endl;
        cout << setw(62)<< " " << "2. Sap xep theo chieu tang cua gia ban" << endl;
        cout << setw(62)<< " " << "3. Sap xep theo chieu giam cua gia von" << endl;
        cout << setw(62)<< " " << "4. Sap xep theo chieu tang cua gia von" << endl;
        cout << setw(62)<< " " << "0. Thoat" << endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);cout << "\n" << setw(48) << " "; for (int i = 1; i <= 65; i++) cout << "-";SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
        cout << "\n\t\t\t\t\t\tNhap lua chon: "; luachon = So_nguyen();
        if (luachon == 0) break;
        switch(luachon){
            case 1:
            {
                selectionsortGiaBan(down);
                Show(0);
                break;
            }
            case 2:
            {
                selectionsortGiaBan(up);
                Show(0);
                break;
            }
            case 3:
            {
                selectionsortGiaVon(down);
                Show(0);
                break;
            }
            case 4:
            {
                selectionsortGiaVon(up);
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
int QuanLyHang::FindIndexDM(const int &index)
{
    for (int i = 0; i < this->lengthK; i++)
    {
        if (databaseK[i]->getmaPL() == index)
            return i;
    }
    return -1;
}

///// THAO TAC VOI PHAN LOAI HANG
int QuanLyHang::getLengthPL() { return this->lengthPL;}
void QuanLyHang::setLengthPL(int lengthPL){ this->lengthPL = lengthPL;}

void QuanLyHang::ReadfPL(){
    ifstream filein;
    filein.open("PhanLoai.txt");

    if (!filein)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);cout << "\n\t\t\t\t\t\tLoi: File khong mo duoc." << endl;SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
        return;
    }
    filein.seekg(0, ios::end);
    if (filein.tellg() == 0) return;
    filein.seekg(0, ios::beg);
    
    while (filein.eof() != true)
    {
        int maPL;
        string tenPL;
        string check_delete_chuoi;      int check_delete;
        filein >> maPL;
        filein.ignore();
        getline(filein, tenPL, ',');
        HamChuanHoa(tenPL);
        getline(filein, check_delete_chuoi);
        HamChuanHoa(check_delete_chuoi);
        // kiem tra bien check co hop le khong
        if (check_delete_chuoi == "Da Xoa") check_delete = 1;
        else if (check_delete_chuoi == "Ton Tai") check_delete = 0;
        else{
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);cout << "\n\t\t\t\t\t\tTrang thai phan loai " << maPL << " khong hop le!" << endl; SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);   
            continue;
        }
        if (FindIndexPL(maPL) != -1 && FindIndexTenPL(tenPL) != -1)
        {
            cout << "\t\t\t\t\t\tMa phan loai " << maPL << " va ten phan loai " << tenPL << " da ton tai" << endl;
            continue;
        }
        else if (FindIndexPL(maPL) != -1)
        {
            cout << "\t\t\t\t\t\tMa phan loai " << maPL << " da ton tai" << endl;
            continue;
        }
        else if (FindIndexTenPL(tenPL) != -1)
        {
            cout << "\t\t\t\t\t\tTen phan loai " << tenPL << " da ton tai" << endl;
            continue;
        }

        PhanLoai *phan_loai = new PhanLoai(maPL, tenPL, check_delete);
        databasePL.push_back(phan_loai);
        this->lengthPL++;
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),6);cout << "\n\t\t\t\t\t\tDoc file thanh cong!" << endl;SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
    filein.close();
}

void QuanLyHang::InsertPL(){
    ShowPL(0); ShowPL(1);
    PhanLoai *pl = new PhanLoai;
    cin >> *pl;
    // Cuan hoa ten dung
    string tenPL = pl->getTenPL(); HamChuanHoa(tenPL); pl->setTenPL(tenPL);
    int n = FindIndexTenPL(pl->getTenPL());
    if (n != -1 && databasePL[n]->getCheckDeleteSo() == 1){
        int luachon1;
        do {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);cout << "\n\t\t\t\t\t\tPhan loai da bi xoa khoi kho. Ban muon khoi phuc lai khong? ";SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
            cout << "\n\t\t\t\t\t\t1. Co ";
            cout << "\n\t\t\t\t\t\t0. Khong ";
            cout << "\n\t\t\t\t\t\tNhap lua chon: "; luachon1 = So_nguyen();
            if (luachon1 == 1){
                databasePL[n]->setCheckDelete(0);
                int m = pl->getMaPL();
                delete pl;
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),6);cout << "\t\t\t\t\t\tKhoi phuc phan loai thanh cong!" << endl;SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
                throw m; // Nem ma duoc khoi phuc
            }
            else if (luachon1 == 0)
            {
                delete pl;
                return;
            }
        } while (luachon1 != 0 && luachon1 != 1 );
    }
    if (n != -1)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);cout << "\t\t\t\t\t\tTen phan loai " << pl->getTenPL() << " da ton tai" << endl;SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
        delete pl;
        return;
    }
    databasePL.push_back(pl);
    this->lengthPL++;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),6);cout << "\t\t\t\t\t\tThem phan loai thanh cong!" << endl;SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
}
void QuanLyHang::RemovePL(){
    int maPL;
    ShowPL(0);
    cout << "\t\t\t\t\t\tMa phan loai: ";   maPL = Nhap_ma();
    int n = FindIndexPL(maPL);
    if (n == -1 || databasePL[n]->getCheckDeleteSo() == 1){
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);cout << "\t\t\t\t\t\tMa khong ton tai hoac da xoa!" << endl;SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
        return;
    } else{
        this->databasePL[n]->setCheckDelete(1);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),6);cout << "\t\t\t\t\t\tXoa thanh cong!" << endl;SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
    }
}
void QuanLyHang::WritefPL(){
    ofstream fileout;
    fileout.open("PhanLoai.txt");
    for (int i = 0; i < this->getLengthPL(); i++)
    {
        if (i != 0) fileout << endl;
        fileout << databasePL[i]->getMaPL() << ", " << databasePL[i]->getTenPL() << ", " << databasePL[i]->getCheckDelete();
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),6);cout << "\t\t\t\t\t\tGhi vao file thanh cong!" << endl;SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
    fileout.close();
}

void QuanLyHang::ShowPL(int trang_thai){
    if (trang_thai == 0) cout << "\n"<< setw(65) << " " <<"DANH SACH CAC PHAN LOAI HIEN CO"<< endl;
    else cout << "\n"<< setw(65) << " "<< "DANH SACH CAC PHAN LOAI DA XOA"<< endl;
    cout << setw(61) << " ";for (int i = 1; i <= 40; i++) cout << "-";
    cout << "\n" << setw(61) << " " << "| Ma Phan Loai |" << "     Ten Phan Loai     |" << endl;
    cout << setw(61) << " ";for (int i = 1; i <= 40; i++) cout << "-";
    for (int i = 0; i < this->lengthPL; i++)
    {
        if (databasePL[i]->getCheckDeleteSo() == trang_thai) cout << *databasePL[i];
    }
    cout << "\n" << setw(61) << " ";for (int i = 1; i <= 40; i++) cout << "-";cout << endl;
}
void QuanLyHang::FindPL(){
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
            cout << "\t\t\t\t\t\tMa can tim:";
            int maPL = Nhap_ma();
            int n = FindIndexPL(maPL);
            if (n == -1){
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);cout << "\t\t\t\t\t\tMa khong ton tai!" << endl;SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
            }else{
                cout << setw(61) << " ";for (int i = 1; i <= 53; i++) cout << "-";
                cout << "\n" << setw(61) << " " << "| Ma Phan Loai |" << "     Ten Phan Loai     |" << " Trang Thai |" << endl;
                cout << setw(61) << " ";for (int i = 1; i <= 53; i++) cout << "-";
                cout << *databasePL[n] << " " << left << setw(11) << databasePL[n]->getCheckDelete() << "|";
                cout << "\n" << setw(61) << " ";for (int i = 1; i <= 53; i++) cout << "-"; cout << endl;
            }
        } else if (luachon ==  2)
        {
            string tenPL;
            fflush(stdin);
            cout << "\t\t\t\t\t\tNhap ten: ";    getline(cin,tenPL);
            HamChuanHoa(tenPL);
            int n = FindIndexTenPL(tenPL);
            if ( n == -1){
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);cout << "\t\t\t\t\t\tTen khong ton tai!" << endl;SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
            }else{
                cout << setw(61) << " ";for (int i = 1; i <= 53; i++) cout << "-";
                cout << "\n" << setw(61) << " " << "| Ma Phan Loai |" << "     Ten Phan Loai     |" << " Trang Thai |" << endl;
                cout << setw(61) << " ";for (int i = 1; i <= 53; i++) cout << "-";
                cout << *databasePL[n] << " " << left << setw(11) << databasePL[n]->getCheckDelete() << "|";
                cout << "\n" << setw(61) << " ";for (int i = 1; i <= 53; i++) cout << "-"; cout << endl;
            }
        }
        else if (luachon != 0){
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);cout << "\t\t\t\t\t\tLua chon khong hop le!" << endl;SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
        } else break;
        cout << "\t\t\t\t\t\t"; system("pause");
    }while(luachon);
}

int QuanLyHang::FindIndexPL(const int &index)
{
    for (int i = 0; i < this->lengthPL; i++)
    {
        if (databasePL[i]->getMaPL() == index)
            return i;
    }
    return -1;
}
int QuanLyHang::FindIndexTenPL(const string &index)
{
    for (int i = 0; i < this->lengthPL; i++)
    {
        if (databasePL[i]->getTenPL() == index)
            return i;
    }
    return -1;
}
void QuanLyHang::UpdatePL(){
    int luachon;
    do{    
        system("cls");
        int maPL; 
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);cout << setw(48) << " "; for (int i = 1; i <= 65; i++) cout << "-";SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);
        cout << "\n\n";
        cout << setw(69) << " " << "1. Cap nhat ten" << endl;
        cout << setw(69) << " " << "2. Khoi phuc trang thai" << endl;
        cout << setw(69) << " " << "0. Thoat" << endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);cout << "\n" << setw(48) << " "; for (int i = 1; i <= 65; i++) cout << "-";SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
        cout << "\n\t\t\t\t\t\tNhap lua chon: "; luachon = So_nguyen();
        
        if (luachon == 0) break;
        if (luachon < 0 || luachon > 2){
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);cout << "\t\t\t\t\t\tLua chon khong hop le!" << endl;SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
            cout << "\t\t\t\t\t\t"; system("pause");
            continue;
        }
        if (luachon == 2) ShowPL(1);
        else ShowPL(0);
        cout << "\t\t\t\t\t\tMa so phan loai can cap nhat: ";   maPL = Nhap_ma();
        int n = FindIndexPL(maPL);
        if (luachon == 1){
            if (n == -1 || databasePL[n]->getCheckDeleteSo() == 1){
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);cout << "\t\t\t\t\t\tMa khong ton tai hoac da xoa!" << endl;SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
                cout << "\t\t\t\t\t\t"; system("pause");
                continue;
            }
        }
        else{
            if (n == -1 || databasePL[n]->getCheckDeleteSo() == 0){
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);cout << "\t\t\t\t\t\tKhong ton tai phan loai da xoa nhu tren!" << endl;SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
                cout << "\t\t\t\t\t\t"; system("pause");
                continue;
            }
        }
        switch (luachon)
        {
            case 1:
            {
                string tenPL;
                cout << "\t\t\t\t\t\tNhap ten phan loai moi: ";
                fflush(stdin); getline(cin, tenPL);
                HamChuanHoa(tenPL);
                while (FindIndexTenPL(tenPL) != -1 || tenPL.empty() == 1){
                    if (tenPL == databasePL[n]->getTenPL()) break;
                    if (FindIndexTenPL(tenPL) != -1) {
                            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);cout << "\t\t\t\t\t\tTen hang hoa da ton tai!";SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
                            cout << "\n\t\t\t\t\t\tNhap lai: ";
                    }
                    else cout << "\t\t\t\t\t\tNhap lai: ";
                    fflush(stdin); getline(cin, tenPL);
                    HamChuanHoa(tenPL);
                }
                databasePL[FindIndexPL(maPL)]->setTenPL(tenPL);
                break;
            }
            case 2:
            {
                databasePL[n]->setCheckDelete(0);
                break;
            }
        }
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),6);cout << "\n\t\t\t\t\t\tCap nhat thanh cong!" << endl;SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
        cout << "\t\t\t\t\t\t"; system("pause");
    }while(luachon);
}