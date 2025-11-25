#ifndef QUANLY_DATA_USER_H
#define QUANLY_DATA_USER_H

#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include "QuanLy.h"
#include "dkchutro.h"



using namespace std;

class QuanLyDataUser : public QuanLy<DangKi>{
private:
    string Folder = "data/";

public:
    QuanLyDataUser() {
        filesystem::create_directories(Folder);
    }
   void taoFileChuTro(const std::string& soTK) {
    std::string filename = Folder + soTK + "_chutro.txt";
    std::ofstream f(filename, std::ios::out); 
    f.close();
}

void taoFileNguoiThue(const std::string& soTK) {
    std::string filename = Folder + soTK + "_nguoithue.txt";
    std::ofstream f(filename, std::ios::out);
    f.close();
}

    void dangKyUser(const string& soTK, const string& matKhau, const string& ten) {
        ofstream fUser("user.txt", ios::app);
        if (fUser.is_open()) {
            fUser << soTK << " " << matKhau << " " << ten << "\n";
            fUser.close();
        }
        taoFileChuTro(soTK);
        taoFileNguoiThue(soTK);
    }

   QuanLy<DangKi> docFileChuTro(const std::string& soTK) {
    std::string filename = Folder + soTK + "_chutro.txt";
    QuanLy<DangKi> temp;
    temp.docFile(filename);
    return temp;
}

   QuanLy<DangKi> docFileNguoiThue(const std::string& soTK) {
    std::string filename = Folder + soTK + "_nguoithue.txt";
    QuanLy<DangKi> temp;
    temp.docFile(filename);
    return temp;
}

   void luuFileChuTro(const string& soTK) {
        string filename = Folder + soTK + "_chutro.txt";
        
        this->luuFile(filename);  
            }

    void luuFileNguoiThue(const string& soTK) {
        string filename = Folder + soTK + "_nguoithue.txt";
        this->luuFile(filename);
    }
};

#endif
