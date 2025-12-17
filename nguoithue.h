#ifndef NGUOITHUE_H
#define NGUOITHUE_H
#include <string>

class NguoiThue{
    private:
    std::string stkNguoiT;
    std::string stkChuT;
    std::string ten;
    std::string queQuan;
    std::string sdt;      
    std::string ngayThue;     
    int phongSo;
    public:
    NguoiThue() {} 
    NguoiThue(const std::string& stkNT,const std::string& stkCT,const std::string& t,const std::string& que,const std::string& so,const std::string& nt,const int& ps)
    :stkNguoiT(stkNT),stkChuT(stkCT),ten(t),queQuan(que),sdt(so),ngayThue(nt),phongSo(ps) {}

    std::string getSTK_NguoiThue() const { return stkNguoiT; }
    std::string getSTK_ChuTro()    const { return stkChuT; }
    std::string getTen() const {return ten;}
    std::string getSdt() const {return sdt;}
    std::string getQueQuan() const {return queQuan;}
    std::string getNgayThue() const   { return ngayThue; }
    int getPhongSo() const    { return phongSo; }

    void setTen(const std::string& n) {ten = n;}
    void setSdt(const std::string& so) {sdt = so;}
    void setQueQuan(const std::string& que) {queQuan = que;}
    void setNgayThue(const std::string& nt) { ngayThue = nt; }
    void setPhongSo(const int& ps)  { phongSo = ps; }
};
#endif 
