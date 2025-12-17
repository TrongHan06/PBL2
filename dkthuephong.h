
#ifndef DKTHUEPHONG_H
#define DKTHUEPHONG_H

#include "nguoithue.h"

enum TrangThaiNT { CHO_DUYET_NT, DA_DUYET_NT, TU_CHOI_NT };

class DangKiThue {
private:
    NguoiThue nguoiThue;
    TrangThaiNT status;

public:
    DangKiThue() = default; 
    DangKiThue(const NguoiThue& nT) : nguoiThue(nT), status(CHO_DUYET_NT) {}

    const NguoiThue& getNguoiThue() const { return nguoiThue; }
    TrangThaiNT getStatusNT() const { return status; }
    
    void setStatusNT(TrangThaiNT s) { status = s;}

    void duyet()   { status = DA_DUYET_NT; }
    void tuChoi()  { status = TU_CHOI_NT; }
};

#endif