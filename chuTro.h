#ifndef CHUTRO_H
#define CHUTRO_H
#include <string>
#include "PhongTro.h"
class ChuTro{
    private:
    std::string ten;
    std::string sdt;
    std::string soTK;
    PhongTro phongTro;
    public:
    ChuTro() {} 
    ChuTro(const std::string& stk,const std::string& t,const std::string& so,const PhongTro& pt)
    :soTK(stk),ten(t),sdt(so),phongTro(pt) {}
    std::string getTen() const {return ten;}
    std::string getSdt() const {return sdt;}
    std::string getDiaChi() const {return phongTro.getDiaChi();}
    int getSoLuongPhong() const {return phongTro.getSoLuongPhong();}
    std::string getTienPhong() const {return phongTro.getTienPhong();}
    std::string  getTienDien() const {return phongTro.getTienDien();}
    std::string getTienNuoc() const {return phongTro.getTienNuoc();}
    std::string getHinhAnh() const {return phongTro.getHinhAnh();}
    std::string getSTK() const {return soTK;}

    void setTen(const std::string& n) {ten = n;}
    void setSdt(const std::string& so) {sdt = so;}
    void setPhongTro(const PhongTro& pt) {phongTro = pt;}
};
#endif 