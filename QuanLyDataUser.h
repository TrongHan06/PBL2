
#ifndef QUANLY_DATA_USER_H
#define QUANLY_DATA_USER_H

#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include "QuanLy.h"
#include "dkchutro.h"
#include "dkthuephong.h"

using namespace std;

class QuanLyDataUser {
private:
    string Folder = "data/";

public:
    QuanLyDataUser() {
        filesystem::create_directories(Folder);
    }

    void taoFolderUser(const std::string& soTK) {
        filesystem::create_directories(Folder + soTK);
    }

    void taoFileMacDinhUser(const std::string& soTK) {
        string userFolder = Folder + soTK + "/";
        ofstream(userFolder + "chutro.txt").close();
        ofstream(userFolder + "nguoithue.txt").close();
        ofstream(userFolder + "quanlynt.txt").close();
        ofstream(userFolder + "quanlypt.txt").close();
        ofstream(userFolder + "dondkthuept.txt").close();
    }

    void dangKyUser(const string& soTK, const string& matKhau, const string& ten) {
        ofstream fUser("user.txt", ios::app);
        if (fUser.is_open()) {
            fUser << soTK << " " << matKhau << " " << ten << "\n";
            fUser.close();
        }
        taoFolderUser(soTK);
        taoFileMacDinhUser(soTK);
    }
    QuanLy<DangKi> docFileChuTro(const std::string& soTK) {
        QuanLy<DangKi> temp;
        string filename = Folder + soTK + "/chutro.txt";
        if (filesystem::exists(filename)) temp.docFile(filename);
        return temp;
    }

    QuanLy<DangKi> docFileQuanLyPT(const std::string& soTK) {
        QuanLy<DangKi> temp;
        string filename = Folder + soTK + "/quanlypt.txt";
        if (filesystem::exists(filename)) temp.docFile(filename);
        return temp;
    }
    QuanLy<DangKiThue> docFileNguoiThue(const std::string& soTK) {
        QuanLy<DangKiThue> temp;
        string filename = Folder + soTK + "/nguoithue.txt";
        if (filesystem::exists(filename)) temp.docFile(filename);
        return temp;
    }
    QuanLy<DangKiThue> docFiledk(const std::string& soTK) {
        QuanLy<DangKiThue> temp;
        string filename = Folder + soTK + "/dondkthuept.txt";
        if (filesystem::exists(filename)) temp.docFile(filename);
        return temp;
    }
    QuanLy<DangKiThue> docFileQuanLyNT(const std::string& soTK) {
        QuanLy<DangKiThue> temp;
        string filename = Folder + soTK + "/quanlynt.txt";
        if (filesystem::exists(filename)) temp.docFile(filename);
        return temp;
    }
};

#endif