#ifndef PHONGTRO_H
#define PHONGTRO_H
#include <string>
class PhongTro{
    private:
    std::string moTa;
    std::string diaChi;
    std::string hinhAnh;
    public:
    PhongTro() = default;

    PhongTro(const std::string& mt,const std::string& dc,const std::string& anh = "")
    : moTa(mt),diaChi(dc),hinhAnh(anh) {};

    std::string getMoTa() const {return moTa;}
    std::string getDiaChi() const {return diaChi;}
    std::string getHinhAnh() const {return hinhAnh;}
    
    void setMoTa(const std::string& mt) {moTa = mt;}
    void setDiaChi(const std::string& dc) {diaChi = dc;}
    void setHinhAnh(const std::string& anh) {hinhAnh = anh;}

};
#endif