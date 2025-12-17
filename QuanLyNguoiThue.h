#ifndef QUANLYNGUOITHUE_H
#define QUANLYNGUOITHUE_H

#include "QuanLy.h"
#include "NguoiThue.h"
#include "dkthuephong.h"
#include <fstream>
#include <sstream>

template <>
class QuanLy<NguoiThue> {
protected:
    Vector<NguoiThue> ds;   
    int SelectedIndex = -1;

public:
    QuanLy() = default;
    QuanLy(int cap) { ds.reserve(cap); }

    void them(const NguoiThue& item) {
        ds.push_back(item);
    }

    NguoiThue& layTheoViTri(size_t i) {
        if (i >= ds.size()) throw std::out_of_range("Index out of range");
        return ds[i];
    }

    const NguoiThue& layTheoViTri(size_t i) const {
        if (i >= ds.size()) throw std::out_of_range("Index out of range");
        return ds[i];
    }

    int soLuong() const { return static_cast<int>(ds.size()); }

    void xoa(size_t i) {
        if (i < ds.size()) ds.erase(i);
    }

    void sua(size_t i, const NguoiThue& item) {
        if (i < ds.size()) ds[i] = item;
    }

    void luuFile(const std::string& filename) {
        std::ofstream out(filename);
        if (!out.is_open()) return;

        for (const NguoiThue& nt : ds) {  
            out << nt.getSTK_NguoiThue() << ','
                << nt.getSTK_ChuTro() << ','
                << nt.getTen() << ','
                << nt.getQueQuan() << ','
                << nt.getSdt() << ','
                << nt.getNgayThue() << ','
                << nt.getPhongSo() << '\n';
              
        }
        out.close();
    }
    void docFile(const std::string& filename) {
        std::ifstream in(filename);
        if (!in.is_open()) return;

        ds.clear();
        std::string line;

        while (std::getline(in, line)) {
            if (line.empty()) continue;

            std::stringstream ss(line);
            std::string stkNT, stkCT, ten, que, sdt, ngay, phong, statusStr;

            std::getline(ss, stkNT, ',');
            std::getline(ss, stkCT, ',');
            std::getline(ss, ten, ',');
            std::getline(ss, que, ',');
            std::getline(ss, sdt, ',');
            std::getline(ss, ngay, ',');
            std::getline(ss, phong, ',');
            std::getline(ss, statusStr);
            
           int PhongSo = 0;
           if (!phong.empty())
           {PhongSo = std::stoi(phong);}
            NguoiThue nt(stkNT, stkCT, ten, que, sdt, ngay, PhongSo);
            ds.push_back(nt);
        }
        in.close();
    };
    void setSelected(int i) { SelectedIndex = i; }
    int getSelected() const { return SelectedIndex; }
    void clearSelected() { SelectedIndex = -1; }

    const Vector<NguoiThue>& getAll() const { return ds; }
    
};

#endif 