#ifndef PHONGTRO_H
#define PHONGTRO_H
#include <string>
class PhongTro{
    private:
    std::string  tienDien;
    std::string tienNuoc;
    std::string tienPhong;
    int soLuongPhong;
    std::string diaChi;
    std::string hinhAnh;
    public:
    PhongTro() = default;

    PhongTro(const std::string& dc,const int& slp,const std::string& tp,const std::string&td,const std::string& tn,const std::string& anh = "")
    : diaChi(dc),soLuongPhong(slp),tienPhong(tp),tienDien(td),tienNuoc(tn),hinhAnh(anh) {};
    
    std::string getDiaChi() const {return diaChi;}
    int getSoLuongPhong() const {return soLuongPhong;}
    std::string getTienPhong() const {return tienPhong;}
    std::string getTienDien() const {return tienDien;}
    std::string getTienNuoc() const {return tienNuoc;}
    std::string getHinhAnh() const {return hinhAnh;}
    
    void setSoLuongPhong(const int& slp) {soLuongPhong = slp;}
    void setTienDien(const std::string& td) {tienDien = td;}
    void setTienNuoc(const std::string& tn) {tienNuoc = tn;}
    void setTienPhong(const std::string& tp) {tienPhong= tp;}
    void setDiaChi(const std::string& dc) {diaChi = dc;}
    void setHinhAnh(const std::string& anh) {hinhAnh = anh;}

};
#endif