
#ifndef TIMKIEM_H
#define TIMKIEM_H

#include <vector>
#include <string>
#include <algorithm>
#include <cctype>
#include "chuTro.h"
#include "dkchutro.h"
#include "QuanLy.h"

inline std::string trim(const std::string& str) {
    size_t first = str.find_first_not_of(" \t\r\n");
    size_t last  = str.find_last_not_of(" \t\r\n");
    if (first == std::string::npos) return "";
    return str.substr(first, last - first + 1);
}

inline std::string toLowerCase(std::string s) {
    std::transform(s.begin(), s.end(), s.begin(),
                   [](unsigned char c){ return std::tolower(c); });
    return s;
}

struct KQTimKiem {
    std::string tenChuTro;
    std::string diaChi;     
    int index;
};

class TimKiem {
public:
    static std::vector<KQTimKiem> LocTheoDiaChi(const QuanLy<DangKi>& ds, const std::string& tuKhoa) {
        std::vector<KQTimKiem> ketQua;

        if (tuKhoa.empty()) return ketQua;

        std::string key = trim(toLowerCase(tuKhoa)); 

        for (int i = 0; i < ds.size(); i++) {
            const DangKi& dk = ds.lay(i);
            const ChuTro& ct = dk.getChuTro();
            std::string diaChiDB = trim(toLowerCase(ct.getDiaChi()));
            if (diaChiDB.find(key) != std::string::npos) {
                ketQua.push_back({ ct.getTen(), ct.getDiaChi(), i });
                continue;
            }
            std::string reversedKey;
            size_t pos = key.find('/');
            if (pos != std::string::npos) {
                reversedKey = key.substr(pos + 1) + "/" + key.substr(0, pos);
                if (diaChiDB.find(reversedKey) != std::string::npos) {
                    ketQua.push_back({ ct.getTen(), ct.getDiaChi(), i });
                }
            }
        }

        return ketQua;
    }
};

#endif