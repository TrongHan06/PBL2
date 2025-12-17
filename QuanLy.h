#ifndef QUANLY_H
#define QUANLY_H

#include "vector.h"
#include <stdexcept>
#include <string>
#include <fstream>
#include <sstream>



template <typename T>
class QuanLy {
protected: 
    Vector<T> ds;
    int SelectedIndex = -1;

public:
    QuanLy() = default;
    QuanLy(int cap) { ds.reserve(cap); }

    void them(const T& item) { ds.push_back(item); }

    T& lay(int index) {
        if (index < 0 || index >= static_cast<int>(ds.size()))
            throw std::out_of_range("Index sai!");
        return ds[index];
    }
    const T& lay(int index) const {
        if (index < 0 || index >= static_cast<int>(ds.size()))
            throw std::out_of_range("Index sai!");
        return ds[index];
    }

    int size() const { return static_cast<int>(ds.size()); }

    void erase(int index) {
        if (index >= 0 && index < static_cast<int>(ds.size()))
            ds.erase(ds.begin() + index);
    }

    const Vector<T>& getAll() const { return ds; }

    virtual void luuFile(const std::string&) {}
    virtual void docFile(const std::string&) {}

    void setSelected(int i) { SelectedIndex = i; }
    int getSelected() const { return SelectedIndex; }
    void clearSelected() { SelectedIndex = -1; }

    virtual ~QuanLy() = default;
};
#include "dkchutro.h" 

template <>
class QuanLy<DangKi> {
protected:
    Vector<DangKi> ds;
    int SelectedIndex = -1;

public:
    QuanLy() = default;
    QuanLy(int cap) { ds.reserve(cap); }

    void them(const DangKi& item) { ds.push_back(item); }

    DangKi& lay(int index) {
        if (index < 0 || index >= static_cast<int>(ds.size()))
            throw std::out_of_range("Index sai!");
        return ds[index];
    }
    const DangKi& lay(int index) const {
        if (index < 0 || index >= static_cast<int>(ds.size()))
            throw std::out_of_range("Index sai!");
        return ds[index];
    }

    int size() const { return static_cast<int>(ds.size()); }
    void erase(int index) {
        if (index >= 0 && index < static_cast<int>(ds.size()))
            ds.erase(index);
    }

    const Vector<DangKi>& getAll() const { return ds; }

    void luuFile(const std::string& filename) {
        std::ofstream fsave(filename);
        if (!fsave.is_open()) return;

        for (const DangKi& dk : ds) {
            const ChuTro& ct = dk.getChuTro();
            fsave << ct.getSTK() << ','
                  << ct.getTen() << ','
                  << ct.getSdt() << ','
                  << ct.getDiaChi() << ','
                  << ct.getSoLuongPhong() << ','
                  << ct.getTienPhong() << ','
                  << ct.getTienDien() << ','
                  << ct.getTienNuoc() << ','
                  << ct.getHinhAnh() << ','
                  << static_cast<int>(dk.getStatus()) << '\n';
        }
    }
    void docFile(const std::string& fileName) {
        std::ifstream fin(fileName);
        if (!fin.is_open()) return;
        ds.clear();
        std::string line;
        while (std::getline(fin, line)) {
            if (line.empty()) continue;

            std::stringstream ss(line);
            std::string soTK, ten, sdt, diaChi, hinhAnh, trangThai;
            std::string s_slp, s_tp, s_td, s_tn;
          
            std::getline(ss, soTK, ',');
            std::getline(ss, ten, ',');
            std::getline(ss, sdt, ',');
            std::getline(ss, diaChi, ',');
            std::getline(ss, s_slp, ',');
            std::getline(ss, s_tp, ',');
            std::getline(ss, s_td, ',');
            std::getline(ss, s_tn, ',');
            std::getline(ss, hinhAnh, ',');
            std::getline(ss, trangThai);
 
           int soLuongPhong = 0;
           if (!s_slp.empty())
           {soLuongPhong = std::stoi(s_slp);}

            PhongTro pt(diaChi, soLuongPhong, s_tp, s_td, s_tn, hinhAnh);
            ChuTro ct(soTK, ten, sdt, pt);
            DangKi dk(ct);
            dk.setStatus(static_cast<TrangThai>(std::stoi(trangThai)));

            ds.push_back(dk);
        }
    }

    void setSelected(int i) { SelectedIndex = i; }
    int getSelected() const { return SelectedIndex; }
    void clearSelected() { SelectedIndex = -1; }
};
#include "dkthuephong.h"
#include <fstream>
#include <sstream>

template<>
class QuanLy<DangKiThue>
{
protected:
    Vector<DangKiThue> ds;
    int SelectedIndex = -1;

public:
    void them(const DangKiThue& item) { ds.push_back(item); }

    DangKiThue& lay(int i) {
        if (i < 0 || i >= (int)ds.size()) throw std::out_of_range("Index out");
        return ds[i];
    }
    const DangKiThue& lay(int i) const { return const_cast<QuanLy*>(this)->lay(i); }

    int size() const { return (int)ds.size(); }
    void erase(int i) { if (i >= 0 && i < (int)ds.size()) ds.erase(i); }

    void setSelected(int i) { SelectedIndex = i; }
    int getSelected() const { return SelectedIndex; }
    void clearSelected() { SelectedIndex = -1; }
    void luuFile(const std::string& filename)
    {
        std::ofstream out(filename);
        if (!out.is_open()) return;

        for (const DangKiThue& dk : ds)
        {
            const NguoiThue& nt = dk.getNguoiThue();
            out << nt.getSTK_NguoiThue() << ','
                << nt.getSTK_ChuTro()    << ','
                << nt.getTen()           << ','
                << nt.getQueQuan()       << ','
                << nt.getSdt()           << ','
                << nt.getNgayThue()      << ','
                << nt.getPhongSo()       << ','
                << dk.getStatusNT()      << '\n';   
        }
    }

    void docFile(const std::string& filename)
    {
        std::ifstream in(filename);
        if (!in.is_open()) return;

        ds.clear();
        std::string line;
        while (std::getline(in, line))
        {
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
            DangKiThue dk(nt);
            dk.setStatusNT(static_cast<TrangThaiNT>(std::stoi(statusStr)));

            ds.push_back(dk);
        }
    }
};

#endif