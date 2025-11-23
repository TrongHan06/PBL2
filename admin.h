#ifndef ADMIN_H
#define ADMIN_H
#include "chuTro.h"
#include "dkchutro.h"
#include "QuanLy.h"
class Admin{
    private:
    QuanLy<DangKi>& danhsachDK;
    QuanLy<ChuTro>& danhsachChuTro;
    public:
    Admin(QuanLy<DangKi>& dsDK,QuanLy<ChuTro>& dsChuTro)
    : danhsachDK(dsDK),danhsachChuTro(dsChuTro){}

    int soDon() const {
        return danhsachDK.size();
    }

    void duyetDon(int index){
        DangKi& dk = danhsachDK.lay(index);
        dk.duyet();
        danhsachChuTro.them(dk.getChuTro());
    }

    void tuChoiDon(int index){
        DangKi& dk = danhsachDK.lay(index);
        dk.tuChoi();
    }
    


};
#endif