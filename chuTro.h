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
    ChuTro(const std::string& t,const std::string& so,std::string& stk,const PhongTro& pt)
    :ten(t),sdt(so),soTK(stk),phongTro(pt) {}
    std::string getTen() const {return ten;}
    std::string getSdt() const {return sdt;}
    std::string getMoTa() const {return phongTro.getMoTa();}
    std::string getDiaChi() const {return phongTro.getDiaChi();}
    std::string getHinhAnh() const {return phongTro.getHinhAnh();}
    std::string getSTK() const {return soTK;}

    void setTen(const std::string& n) {ten = n;}
    void setSdt(const std::string& so) {sdt = so;}
    void setPhongTro(const PhongTro& pt) {phongTro = pt;}
};
#endif 