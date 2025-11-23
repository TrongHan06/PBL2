#ifndef DANGKI_H
#define DANGKI_H
#include "chuTro.h"
enum TrangThai{
        CHO_DUYET,
        DA_DUYET,
        TU_CHOI
};
class DangKi{
    private:
    ChuTro chutro;
    TrangThai status;
    public:
    DangKi(const ChuTro& ct)
    :chutro(ct),status(CHO_DUYET){}
    TrangThai getStatus() const {return status;}
    const ChuTro&  getChuTro() const {return chutro;}
    
    void setStatus(TrangThai s) { status = s;}

    void duyet() { status = DA_DUYET;}
    void tuChoi() { status = TU_CHOI;}
};
#endif
