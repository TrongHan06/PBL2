#ifndef QUANLY_H
#define QUANLY_H

#include <vector>
#include <stdexcept>
#include <fstream>
#include <sstream>
#include <string>
#include "dkchutro.h"

template <typename T>
class QuanLy {
private:
    std::vector<T> ds;
    int SelectedIndex =-1;

public:
    QuanLy(){}
    QuanLy(int cap){
        ds.reserve(cap);   
    }
    void them(const T& item) {
        ds.push_back(item);
    }

    T& lay(int index) {
        if (index < 0 || index >= ds.size())
            throw std::out_of_range("Index sai!");
        return ds.at(index);
    }

    int size() const {
        return ds.size();
    }
    void erase(int index) {
    if (index >= 0 && index < ds.size())
        ds.erase(ds.begin() + index);
}

    const std::vector<T>& getAll() const {
        return ds;
    }
    void luuFile(const std::string& filename){
        std::ofstream fsave(filename,std::ios::out);
        if(!fsave) return;
        for(const DangKi& dk : ds){
            const ChuTro& ct = dk.getChuTro();
            fsave << ct.getTen() << ','
                 << ct.getSdt() << ','
                 << ct.getDiaChi() << ','
                 << ct.getMoTa() << ','
                 << ct.getHinhAnh() << ','
                 << dk.getStatus() << '\n';
        }
        fsave.close();
    }
    void docFile(const std::string& fileName){
    std::ifstream fin(fileName);
    if(!fin) return;
    ds.clear();
    std::string line;
    while(std::getline(fin,line)){
        if(line.empty()) continue;
        std::stringstream ss(line);
        std::string ten,sdt,diaChi,moTa,hinhAnh,trangThai;

        std::getline(ss, ten, ',');
        std::getline(ss, sdt, ',');
        std::getline(ss, diaChi, ',');
        std::getline(ss, moTa, ',');
        std::getline(ss, hinhAnh, ',');
        std::getline(ss, trangThai);

        ChuTro ct(ten,sdt,PhongTro(moTa,diaChi,hinhAnh));
        DangKi dk(ct);
        dk.setStatus(static_cast<TrangThai>(std::stoi(trangThai)));

        ds.push_back(dk);
    }
    fin.close();
   }

   void setSelected(int i){SelectedIndex = i;}
   int getSelected() { return SelectedIndex;}
   void clearSelected() {SelectedIndex = -1;}
};

#endif