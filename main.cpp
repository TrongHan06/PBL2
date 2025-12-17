// shift ctrl p Configure Default Build Task
#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include "TaiKhoan.h"
#include "QuanLy.h"
#include "admin.h"
#include "chuTro.h"
#include "dkchutro.h"
#include "PhongTro.h"
#include "hinhAnh.h"
#include "QuanLyDataUser.h"
#include "timkiem.h"
#include "nguoithue.h"
#include "dkthuephong.h"
#include "QuanLyNguoiThue.h"

QuanLyDataUser  userData;
std::string currentUserSoTK = "";
std::string currentChuTroSTK = "";
HashTable<TaiKhoan> adminTable; 
HashTable<TaiKhoan> userTable;
QuanLy<DangKi>     myChuTro;     
QuanLy<DangKi>     myQuanLypt;    
QuanLy<DangKiThue> myNguoiThue;    
QuanLy<DangKiThue> mydondk;        
QuanLy<DangKiThue> myQuanLynt;   
QuanLy<DangKiThue> dsDKThue; 


#define MAX_INPUT_CHARS 20

float ScreenWidth = 600;
float ScreenHeigth = 400;

char ten[64] = "";
char sdt[64] = "";
char soLuongPhong1[16] = "";
char tienDien[16] = "";
char tienNuoc[16] = "";
char tienPhong[16] = "";
char hinhAnh[64] = "";
char tenNguoiThue[64] = "";
char sdtNguoiThue[16] = "";
char diaChiNguoiThue[100] = "";
char ngaBatDauThue[12] = "01/12/2025";
char phongSo[16] = "";
const char* dsTinh[] = {
    "Da Nang",
    "Quang Nam",
};
const char* dsQuanDaNang[] = {
   "Hai Chau",
   "Thanh Khue",
   "Son Tra",
   "Lien Chieu",
   "Cam Le",
   "Ngu Hanh Son"
};
const char* dsQuanQuangNam[] = {"Tam Ky", "Hoi An", "Dai Loc", "Dien Ban"};
int soHuyenQuangNam = 4;
int selectedTinhIndex = -1;
static std::string diaChi = "";
static std::string diaChiPt = "";
int soTinh = 2;
int soQuanDaNang = 6;

bool focusTen = false;
bool focusSdt = false;
bool focusDiaChi = false;
bool focusSoLuongPhong = false;
bool focusTienDien = false;
bool focusTienNuoc = false;
bool focusTienPhong = false;
bool focusHinhAnh = false;
static bool focusTenNT = false;
static bool focusSdtNT = false;
static bool focusDiaChiNT = false;
static bool focusNgayNT = false;
static bool focusPhongNT = false;
static int phongMuonThue = 0;
static int phongDangXem = 0;
static int soLuongPhong = 0;
static bool phongDaThue[101] = {false};          
static NguoiThue dsNguoiThuePhong[101];  

bool showMessage = false;

typedef enum{
    SCREEN_LOGIN,
    SCREEN_ADMIN_LOGIN,
    SCREEN_USER_LOGIN,
    SCREEN_ADMIN,
    SCREEN_USER,
    SCREEN_CHUTRO,
    SCREEN_THUETRO,
    SCREEN_DANGKI,
    SCREEN_AD_DUYET,
    SCREEN_TIMKIEM,
    SCREEN_CHITIET,
    SCREEN_AD_DADUYET,
    SCREEN_INNKEEPER,
    SCREEN_TENANT,
    SCREEN_QUANLY_DAYTRO,
    SCREEN_QUANLY_PHONGTRO,
    SCREEN_CHITIET_DADUYET,
    SCREEN_DANGKI_USER, 
    SCREEN_THONGTIN, 
    SCREEN_CHONTINH,
    SCREEN_CHONQUAN,
    SCREEN_PHONGTRO,
    SCREEN_TKQUAN,
    SCREEN_TKTINH,
    SCREEN_CHITIET_PHONGTRO,
    SCREEN_DK_THUE,
    SCREEN_NTAD_DADUYET,
    SCREEN_NTAD_DUYET,
    SCREEN_NTAD_CHITIET,
    SCREEN_DS_CD,
    SCREEN_CT_CHITIET_DON,
    SCREEN_CT_CHITIET_NGUOITHUE,
    SCREEN_DS_NGUOI_THUE,
    SCREEN_DS_PHONGTRO,
    SCREEN_CHITIET_DADUYET2,
    SCREEN_CHONPHONG,
    SCREEN_NTAD,
    SCREEN_CHITIET_NTAD
}ScreenState;
ScreenState DrawScreenLogin(){
    ClearBackground(RAYWHITE);
    GuiSetStyle(DEFAULT,TEXT_SIZE,20);
    float fontSize = 50;
    const char *title = "DANG NHAP";
    int textWibth = MeasureText(title,fontSize);
    int textX = (ScreenWidth - textWibth)/2;
    DrawText(title,textX,40,fontSize,DARKBLUE);
    const char *title1 = "Chon che do dang nhap";
    float fontSize1 = 40;
    int textWibth1 = MeasureText(title1,fontSize1);
    int textX1 = (ScreenWidth - textWibth1)/2;
    DrawText(title1,textX1,100,fontSize1,DARKBROWN);

 
    Rectangle rAdminTab = {140,200,150,40};
    Rectangle rUserTab = {310,200,150,40};
    if(GuiButton(rAdminTab,"Admin") )
    return SCREEN_ADMIN_LOGIN;
    if(GuiButton(rUserTab,"User"))
    return SCREEN_USER_LOGIN;
return SCREEN_LOGIN;

}
ScreenState DrawScreenADLogin(char* adminName,char* adminPass){
   ClearBackground(RAYWHITE);
   GuiSetStyle(DEFAULT,TEXT_SIZE,19);
    float fontSize = 50;
    const char *title = "DANG NHAP ADMIN";
    int textWibth = MeasureText(title,fontSize);
    int textX = (ScreenWidth - textWibth)/2;
   
    DrawText(title,textX,40,fontSize,DARKBLUE);

    Rectangle accountBox = {150,107,300,35};
    Rectangle passwordBox = {150,167,300,35};
    Rectangle loginButton = {250,237,100,35};
    
    static bool nameEditMode = false;
    static bool passEditMode = false;
    string loginMessage = "";
    static string errorMessage = "";

    int labelWidth1 = MeasureText("Mat Khau",15);
    int labelWidth2 = MeasureText("So Tai Khoan",15);

    DrawText("So Tai Khoan :",accountBox.x - labelWidth1 - 70,accountBox.y + (passwordBox.height -15)/2,15,BLACK);
    DrawText("Mat khau :",passwordBox.x - labelWidth2 - 10,passwordBox.y + (passwordBox.height -15)/2,15,BLACK);
    
    Vector2 mouse = GetMousePosition();
    bool mouseClicked = IsMouseButtonPressed(MOUSE_LEFT_BUTTON);

    if (mouseClicked) {
    if (CheckCollisionPointRec(mouse, accountBox)) {
        nameEditMode = true;
        passEditMode = false;
    }
    else if (CheckCollisionPointRec(mouse, passwordBox)) {
        passEditMode = true;
        nameEditMode = false;
    }
    else {
        nameEditMode = false;
        passEditMode = false;
    }
}
 if (GuiTextBox(accountBox, adminName, 64, nameEditMode))
        nameEditMode = !nameEditMode;

 if (GuiTextBox(passwordBox, adminPass, 64, passEditMode))
        passEditMode = !passEditMode;
      static Color messagesColor = RED;
      Rectangle btnBack = {200,370,200,24};
       if(GuiButton(btnBack,"QUAY LAI MENU")){
        return SCREEN_LOGIN;
       }
       if (GuiButton(loginButton, "Dang nhap")) {

    TaiKhoan* tk = adminTable.find(adminName, adminPass);
    if (tk) {
     
     loginMessage = "Dang Nhap Thanh Cong";
     messagesColor = GREEN;
     return SCREEN_ADMIN;
    
    } else {
        errorMessage = "Sai tai khoan hoac mat khau!";
        messagesColor = RED;
    }
}
    if(!loginMessage.empty()){
        DrawText(loginMessage.c_str(),180,300,20,messagesColor);
    }
    else if(!errorMessage.empty()){
        DrawText(errorMessage.c_str(),150,300,20,messagesColor);
    }
       return SCREEN_ADMIN_LOGIN;
}
ScreenState DrawScreenUserLogin(char* userName,char* userPass){
    ClearBackground(RAYWHITE);
    GuiSetStyle(DEFAULT,TEXT_SIZE,19);
    float fontSize = 50;
    const char *title = "DANG NHAP USER";
    int textWibth = MeasureText(title,fontSize);
    int textX = (ScreenWidth - textWibth)/2;
    DrawText(title,textX,40,fontSize,DARKBLUE);

    Rectangle accountBox = {150,107,300,35};
    Rectangle passwordBox = {150,167,300,35};
    Rectangle loginButton = {325,237,100,35};
    Rectangle registerButton = {175,237,100,35};

    if(GuiButton(registerButton,"Dang Ky")){
        return SCREEN_DANGKI_USER;
    }
    
    static bool nameEditMode = false;
    static bool passEditMode = false;
    string loginMessage = ""; 
    static string errorMessage = "";

    int labelWidth1 = MeasureText("Mat Khau",15);
    int labelWidth2 = MeasureText("So Tai Khoan",15);

    DrawText("So Tai Khoan :",accountBox.x - labelWidth1 - 70,accountBox.y + (passwordBox.height -15)/2,15,BLACK);
    DrawText("Mat khau :",passwordBox.x - labelWidth2 - 10,passwordBox.y + (passwordBox.height -15)/2,15,BLACK);
    
    Vector2 mouse = GetMousePosition();
    bool mouseClicked = IsMouseButtonPressed(MOUSE_LEFT_BUTTON);

    if (mouseClicked) {
    if (CheckCollisionPointRec(mouse, accountBox)) {
        nameEditMode = true;
        passEditMode = false;
    }
    else if (CheckCollisionPointRec(mouse, passwordBox)) {
        passEditMode = true;
        nameEditMode = false;
    }
    else {
        nameEditMode = false;
        passEditMode = false;
    }
}
 if (GuiTextBox(accountBox, userName, 64, nameEditMode))
        nameEditMode = !nameEditMode;

 if (GuiTextBox(passwordBox, userPass, 64, passEditMode))
        passEditMode = !passEditMode;

      Rectangle btnBack = {200,370,200,24};    
    static Color colorMessage = RED;     

    if (GuiButton(btnBack, "QUAY LAI MENU")) {
        loginMessage.clear();            
        return SCREEN_LOGIN;
    }

    if (GuiButton(loginButton, "Dang nhap")) {
        TaiKhoan* tk = userTable.find(userName, userPass);

        if (tk) {
            currentUserSoTK = tk->getSoTK();


            myChuTro    = userData.docFileChuTro(currentUserSoTK);
            myQuanLypt  = userData.docFileQuanLyPT(currentUserSoTK);   
            myNguoiThue = userData.docFileNguoiThue(currentUserSoTK);  
            mydondk     = userData.docFiledk(currentUserSoTK);         
            loginMessage = "Dang nhap thanh cong!";
            colorMessage = GREEN;      
            return SCREEN_USER;
        } else {
            errorMessage = "Sai tai khoan hoac mat khau!";
            colorMessage = RED;
        }
    }

    if (!loginMessage.empty()) {
        DrawText(loginMessage.c_str(), 180, 300, 20, colorMessage); }
    else if (!errorMessage.empty()){
        DrawText(errorMessage.c_str(), 150, 300, 20, colorMessage);
    }
 
       return SCREEN_USER_LOGIN;


}
ScreenState DrawScreenAd(char* adminName,char* adminPass){
    ClearBackground(RAYWHITE);
    GuiSetStyle(DEFAULT,TEXT_SIZE,20);
    float fontSize = 30;
    const char *title = "HE THONG QUAN LY THUE PHONG TRO - ADMIN";
    int textWibth = MeasureText(title,fontSize);
    int textX = (1000 - textWibth)/2;
    DrawText(title,textX,40,fontSize,DARKBLUE);

    const char *chuTro = "Quan Ly Chu Tro";
    int textXChuTro = (1000 - 300)/2;
    if(GuiButton({textXChuTro,200,300,50},chuTro)){
        return SCREEN_CHUTRO;}

    const char *thueTro = "Quan Ly Nguoi Thue TRo";
    int textXthueTro = (1000 - 300)/2;
    if(GuiButton({textXthueTro,400,300,50},thueTro)){
        return SCREEN_THUETRO;}

         string loginMessage;

    if(GuiButton({400,700,200,30},"Dang xuat")){
        adminName[0] = '\0';
        adminPass[0] = '\0';
         static bool nameEditMode = false;
         static bool passEditMode = false;
         loginMessage.clear();
         
        return SCREEN_ADMIN_LOGIN;
    }
    
    return SCREEN_ADMIN;
}
ScreenState DrawScreenUser(char* userName,char* userPass){
    ClearBackground(RAYWHITE);
    GuiSetStyle(DEFAULT,TEXT_SIZE,20);
     float fontSize = 30;
    const char *title = "HE THONG CHU TRO VA NGUOI THUE";
    int textWibth = MeasureText(title,fontSize);
    int textX = (1000 - textWibth)/2;
    DrawText(title,textX,40,fontSize,DARKBLUE);
    const char *ChuTro = "CHU TRO";
    int textXChuTro = (1000 - 300)/2;
    if(GuiButton({textXChuTro,200,300,50},ChuTro)){
        return SCREEN_INNKEEPER;}   
     DrawText(title,textX,40,fontSize,DARKBLUE);
    const char *NguoiThue = "NGUOI THUE";
    int textXNguoiThue = (1000 - 300)/2;
    if(GuiButton({textXNguoiThue,300,300,50},NguoiThue)){
        return SCREEN_TENANT;}   

    string loginMessage;

    if(GuiButton({400,700,200,30},"Dang xuat")){
          
        userName[0] = '\0';
        userPass[0] = '\0';
         static bool nameEditMode = false;
         static bool passEditMode = false;
         loginMessage.clear();
         
        return SCREEN_USER_LOGIN;
    }
   return SCREEN_USER;
}
void resetDangKy() {
    ten[0] = sdt[0] = diaChi[0] = hinhAnh[0] = '\0';
    soLuongPhong1[0] = tienDien[0] = tienNuoc[0] = tienPhong[0] = '\0';
    showMessage = false;
    focusTen = focusSdt = focusDiaChi = focusSoLuongPhong = false;
    focusTienDien = focusTienNuoc = focusTienPhong = focusHinhAnh = false;
}
ScreenState DrawSCreenDK(QuanLy<DangKi>& dsDangKy, HinhAnh& hinhAnhManager,std::string& diaChi){
    ClearBackground(RAYWHITE);
    GuiSetStyle(DEFAULT, TEXT_SIZE, 20);

    float fontSize = 30;
    const char* title = "DANG KI CHU TRO";
    int textWidth = MeasureText(title, fontSize);
    float textX = (1000 - textWidth) / 2.0f; 
    DrawText(title, textX, 40, fontSize, DARKBLUE);

    Vector2 mouse = GetMousePosition();
    bool mouseClicked = IsMouseButtonPressed(MOUSE_LEFT_BUTTON);

    static bool focusTen = false, focusSdt = false, focusDiaChi = false, focusSoLuongPhong = false;
    static bool focusTienPhong = false, focusTienDien = false, focusTienNuoc = false, focusHinhAnh = false;
    static bool chonHinhAnh = false;
    static std::string hinhAnh = "";
    if(mouseClicked){
        focusTen         = CheckCollisionPointRec(mouse, {350,100,300,30});
        focusSdt         = CheckCollisionPointRec(mouse, {350,150,300,30});
        focusDiaChi      = CheckCollisionPointRec(mouse, {350,200,300,30});
        focusSoLuongPhong= CheckCollisionPointRec(mouse, {350,250,300,30});
        focusTienPhong   = CheckCollisionPointRec(mouse, {350,300,300,30});
        focusTienDien    = CheckCollisionPointRec(mouse, {350,350,300,30});
        focusTienNuoc    = CheckCollisionPointRec(mouse, {350,400,300,30});
        focusHinhAnh     = CheckCollisionPointRec(mouse, {350,450,300,30});

        if(focusTen) focusSdt = focusDiaChi = focusSoLuongPhong = focusTienPhong = focusTienDien = focusTienNuoc = focusHinhAnh = false;
        else if(focusSdt) focusTen = focusDiaChi = focusSoLuongPhong = focusTienPhong = focusTienDien = focusTienNuoc = focusHinhAnh = false;
        else if(focusDiaChi) focusTen = focusSdt = focusSoLuongPhong = focusTienPhong = focusTienDien = focusTienNuoc = focusHinhAnh = false;
        else if(focusSoLuongPhong) focusTen = focusSdt = focusDiaChi = focusTienPhong = focusTienDien = focusTienNuoc = focusHinhAnh = false;
        else if(focusTienPhong) focusTen = focusSdt = focusDiaChi = focusSoLuongPhong = focusTienDien = focusTienNuoc = focusHinhAnh = false;
        else if(focusTienDien) focusTen = focusSdt = focusDiaChi = focusSoLuongPhong = focusTienPhong = focusTienNuoc = focusHinhAnh = false;
        else if(focusTienNuoc) focusTen = focusSdt = focusDiaChi = focusSoLuongPhong = focusTienPhong = focusTienDien = focusHinhAnh = false;
        else if(focusHinhAnh) focusTen = focusSdt = focusDiaChi = focusSoLuongPhong = focusTienPhong = focusTienDien = focusTienNuoc = false;
    }

    GuiLabel({200,100,150,30}, "Ho va Ten:");
    if(GuiTextBox({350,100,300,30}, ten, 64, focusTen)) focusTen = false;

    GuiLabel({200,150,150,30}, "So Dien Thoai:");
    if(GuiTextBox({350,150,300,30}, sdt, 64, focusSdt)) focusSdt = false;
    GuiLabel({200,200,150,30}, "Dia Chi:");
    
    if (GuiButton({350,200,300,30}, diaChi.empty() ? "Chon dia chi" : diaChi.c_str())) {
    return SCREEN_CHONTINH;
}

    GuiLabel({200,250,150,30}, "So Luong Phong:");
    if(GuiTextBox({350,250,300,30}, soLuongPhong1, 16, focusSoLuongPhong)) focusSoLuongPhong = false;

    GuiLabel({200,300,150,30}, "Tien Phong:");
    if(GuiTextBox({350,300,300,30}, tienPhong, 16, focusTienPhong)) focusTienPhong = false;

    GuiLabel({200,350,150,30}, "Tien Dien:");
    if(GuiTextBox({350,350,300,30}, tienDien, 16, focusTienDien)) focusTienDien = false;

    GuiLabel({200,400,150,30}, "Tien Nuoc:");
    if(GuiTextBox({350,400,300,30}, tienNuoc, 16, focusTienNuoc)) focusTienNuoc = false;

    GuiLabel({200,450,150,30}, "Hinh Anh:");
    if(GuiButton({350,450,300,30}, hinhAnh.empty() ? "Chon hinh anh" : hinhAnh.c_str())){
        chonHinhAnh = true;
    }

    if(chonHinhAnh){
        DrawRectangle(200,200,600,400,LIGHTGRAY);
        DrawText("Chon Anh", 400, 210, 20, DARKBLUE);

        int startY = 250;
        int i = 0;
        for(const auto& [name, tex] : hinhAnhManager.getAll()){
            if(GuiButton({300, float(startY + i*60), 200, 50}, name.c_str())){
                hinhAnh = name;
                chonHinhAnh = false;
            }
            i++;
        }
        if(GuiButton({250, 500, 100, 30}, "Huy")) chonHinhAnh = false;
    }
    static std::string errorMessage = "";
    static bool showSuccess = false;
    static bool showMessage = false;
    if(GuiButton({425,600,150,40}, "Dang Ky")){
        errorMessage = "";
        showSuccess = false;
    if (strlen(ten) == 0)
        errorMessage = "Vui long nhap day du thong tin!";
    else if (strlen(sdt) == 0)
        errorMessage = "Vui long nhap day du thong tin!";
    else if (diaChi.empty())
        errorMessage = "Vui long nhap day du thong tin!";
    else if (strlen(soLuongPhong1) == 0)
        errorMessage = "Vui long nhap day du thong tin!";
    else if (strlen(tienPhong) == 0)
        errorMessage = "Vui long nhap day du thong tin!";
    else if (strlen(tienDien) == 0)
        errorMessage = "Vui long nhap day du thong tin!";
    else if (strlen(tienNuoc) == 0)
        errorMessage = "Vui long nhap day du thong tin!";
    else if (hinhAnh.empty())
        errorMessage = "Vui long nhap day du thong tin!";
    
    if(!errorMessage.empty())
    goto SHOW_MES;
    int slp = std::stoi(soLuongPhong1);
    try{
        PhongTro pt(
            diaChi,
            slp,
            std::string(tienPhong),
            std::string(tienDien),
            std::string(tienNuoc),
            hinhAnh
        );
        ChuTro ct(currentUserSoTK,ten,sdt,pt);
        DangKi dk(ct);
        dsDangKy.them(dk);
        dsDangKy.luuFile("dangky.txt");

        showSuccess = true;
    }
    catch(...){
            errorMessage = "Loi!Vui Long Thu Lai.";
    }
    }
    SHOW_MES:
    if(!errorMessage.empty()){
        DrawText(errorMessage.c_str(),350,650,20,RED);

    }
    else if(showSuccess)
   {
    DrawText("Dang Ky Thanh Cong.",400,650,20,GREEN);
   }

    if(GuiButton({400,700,200,30}, "Quay Lai")){
        ten[0] = sdt[0]  = '\0';
        soLuongPhong1[0] = tienDien[0] = tienNuoc[0] = tienPhong[0] = '\0';
        hinhAnh = "";
        diaChi = "";
        focusTen = focusSdt = focusDiaChi = focusSoLuongPhong = false;
        focusTienDien = focusTienNuoc = focusTienPhong = false;
        showSuccess = false;
        errorMessage = false;
        chonHinhAnh = false;
        return SCREEN_USER;
    }

    return SCREEN_DANGKI;
}
ScreenState DrawScreenChonTinh(std::string &diaChi)
{
    ClearBackground(RAYWHITE);
    GuiSetStyle(DEFAULT,TEXT_SIZE,20);
    float fontSize = 30;
    const char *title = "CHON TINH/THANH PHO";
    int textWibth = MeasureText(title,fontSize);
    int textX = (600- textWibth)/2;
    DrawText(title,textX,40,fontSize,DARKBLUE);

    for (int i = 0; i < soTinh; i++)
    {
        if (GuiButton({200, 100 + i * 60, 200, 40}, dsTinh[i]))
        {   
            selectedTinhIndex = i;
            diaChi = dsTinh[i];         
            return SCREEN_CHONQUAN; 
        }
    }

    if (GuiButton({200, 350, 200, 40}, "Quay Lai"))
        return SCREEN_DANGKI;

    return SCREEN_CHONTINH;
}
void ResetTimKiem() {
    selectedTinhIndex = -1;
    diaChiPt.clear();
}
ScreenState DrawScreenTKTinh(std::string &diaChiPt)
{
    ClearBackground(RAYWHITE);
    GuiSetStyle(DEFAULT,TEXT_SIZE,20);
    float fontSize = 30;
    const char *title = "CHON TINH/THANH PHO";
    int textWibth = MeasureText(title,fontSize);
    int textX = (600- textWibth)/2;
    DrawText(title,textX,40,fontSize,DARKBLUE);

    for (int i = 0; i < soTinh; i++)
    {
        if (GuiButton({200, 100 + i * 60, 200, 40}, dsTinh[i]))
        {   
            selectedTinhIndex = i;
            diaChiPt = dsTinh[i];         
            return SCREEN_TKQUAN; 
        }
    }

    if (GuiButton({200, 350, 200, 40}, "Quay Lai")){
        ResetTimKiem(); 
        return SCREEN_TIMKIEM;
    }
    return SCREEN_TKTINH;
}
ScreenState DrawScreenChonQuan(std::string &diaChi)
{
    ClearBackground(RAYWHITE);
    GuiSetStyle(DEFAULT,TEXT_SIZE,20);
    float fontSize = 30;
    const char *title = "CHON QUAN/HUYEN";
    int textWibth = MeasureText(title,fontSize);
    int textX = (600- textWibth)/2;
    DrawText(title,textX,40,fontSize,DARKBLUE);

    const char** dsQuan;
    int soQuan;


    if (selectedTinhIndex == 0) 
    {
        dsQuan = dsQuanDaNang;
        soQuan = soQuanDaNang;
    }
    else if (selectedTinhIndex == 1)
    {
        dsQuan = dsQuanQuangNam;
        soQuan = soHuyenQuangNam;
    }
    else
    {
        dsQuan = nullptr;
        soQuan = 0;
    }
    for (int i = 0; i < soQuan; i++)
    {
        if (GuiButton({400, 150 + i * 60, 200, 40}, dsQuan[i]))
        {   
            diaChi = std::string(dsQuan[i]) + "/" + diaChi;         
            return SCREEN_DANGKI; 
        }
    }

    if (GuiButton({400, 700, 200, 40}, "Quay Lai"))
        return SCREEN_CHONTINH;

    return SCREEN_CHONQUAN;
}

ScreenState DrawScreenTimKiemQuan(std::string &diaChiPt)
{
    ClearBackground(RAYWHITE);
    GuiSetStyle(DEFAULT,TEXT_SIZE,20);
    float fontSize = 30;
    const char *title = "CHON QUAN/HUYEN";
    int textWibth = MeasureText(title,fontSize);
    int textX = (1000- textWibth)/2;
    DrawText(title,textX,40,fontSize,DARKBLUE);

    const char** dsQuan;
    int soQuan;
    if (selectedTinhIndex == 0)
    {
        dsQuan = dsQuanDaNang;
        soQuan = soQuanDaNang;
    }
    else if (selectedTinhIndex == 1) 
    {
        dsQuan = dsQuanQuangNam;
        soQuan = soHuyenQuangNam;
    }
    else
    {
        dsQuan = nullptr;
        soQuan = 0;
    }
    for (int i = 0; i < soQuan; i++)
    {
        if (GuiButton({400, 150 + i * 60, 200, 40}, dsQuan[i]))
        {   
            diaChiPt = std::string(dsQuan[i]) + "/" + diaChiPt;         
            return SCREEN_PHONGTRO;
        }
    }

    if (GuiButton({400, 700, 200, 40}, "Quay Lai")){
        return SCREEN_TKTINH;
    }
    return SCREEN_TKQUAN;
}
ScreenState DrawScreenPhongTro(QuanLy<DangKi>& dsChuTro, std::string& diaChiDaChon)
{
    dsChuTro.docFile("quanlyct.txt");   
    
    ClearBackground(RAYWHITE);
    GuiSetStyle(DEFAULT, TEXT_SIZE, 20);

    float fontSize = 30;
    const char* title = "DANH SACH PHONG TRO";
    int textWidth = MeasureText(title, fontSize);
    int textX = (1000 - textWidth) / 2;
    DrawText(title, textX, 40, fontSize, DARKBLUE);

    DrawText(TextFormat("Khu vuc: %s", diaChiDaChon.c_str()), 50, 80, 20, DARKGRAY);

    auto dsKetQua = TimKiem::LocTheoDiaChi(dsChuTro, diaChiDaChon);

    int y = 140;
    if (dsKetQua.empty()) {
        DrawText("Khong tim thay phong tro nao o khu vuc nay!", 250, 200, 25, RED);
    } else {
        for (const auto& kq : dsKetQua) {
            std::string nut = kq.tenChuTro + " - " + kq.diaChi;
            if (GuiButton({250, (float)y, 500, 60}, nut.c_str())) {
                dsChuTro.setSelected(kq.index);
                currentChuTroSTK = dsChuTro.lay(kq.index).getChuTro().getSTK();
                return SCREEN_CHITIET_PHONGTRO;
            }
            y += 80;
        }
    }
    if (GuiButton({400, 700, 200, 40}, "Quay Lai"))
    {
        ResetTimKiem();
        return SCREEN_TIMKIEM;
    }

    return SCREEN_PHONGTRO;
}
ScreenState DrawScreenChiTietPhongTro(){
    ClearBackground(RAYWHITE);
    GuiSetStyle(DEFAULT,TEXT_SIZE,20);
    float fontSize = 30;
    const char *title = "CHI TIET";
    int textWibth = MeasureText(title,fontSize);
    int textX = (1000- textWibth)/2;
    DrawText(title,textX,40,fontSize,DARKBLUE);
    if (GuiButton({250, 240, 500, 50}, "Thong Tin"))
        return SCREEN_CHITIET_DADUYET2;
     if (GuiButton({250, 310, 500, 50}, "Dang Ky Thue"))
        return SCREEN_DK_THUE;
    
     if (GuiButton({400, 700, 200, 30}, "Quay Lai"))
    {
        return SCREEN_PHONGTRO;
    }
    return SCREEN_CHITIET_PHONGTRO;
}
ScreenState DrawScreenDangKyThue(QuanLy<DangKiThue>& dsDKiThue)
{
    ClearBackground(RAYWHITE);
    GuiSetStyle(DEFAULT, TEXT_SIZE, 20);

    float fontSize = 30;
    const char* title = "DANG KY THUE";
    int textWibth = MeasureText(title, fontSize);
    int textX = (1000 - textWibth) / 2;
    DrawText(title, textX, 40, fontSize, DARKBLUE);

    Vector2 mouse = GetMousePosition();
    bool mouseClicked = IsMouseButtonPressed(MOUSE_LEFT_BUTTON);

    if (mouseClicked) {
        focusTenNT    = CheckCollisionPointRec(mouse, {350,120,300,30});
        focusSdtNT    = CheckCollisionPointRec(mouse, {350,170,300,30});
        focusDiaChiNT = CheckCollisionPointRec(mouse, {350,220,300,30});
        focusNgayNT   = CheckCollisionPointRec(mouse, {350,270,300,30});
        focusPhongNT  = CheckCollisionPointRec(mouse, {350,320,300,30});

        if(focusTenNT)    focusSdtNT = focusDiaChiNT = focusNgayNT = focusPhongNT = false;
        else if(focusSdtNT)   focusTenNT = focusDiaChiNT = focusNgayNT = focusPhongNT = false;
        else if(focusDiaChiNT)focusTenNT = focusSdtNT = focusNgayNT = focusPhongNT = false;
        else if(focusNgayNT) focusTenNT = focusSdtNT = focusDiaChiNT = focusPhongNT = false;
        else if(focusPhongNT) focusTenNT = focusSdtNT = focusDiaChiNT = focusNgayNT = false;
    }

    GuiLabel({180,120,150,30}, "Ho va Ten:");
    if(GuiTextBox({350,120,300,30}, tenNguoiThue, 64, focusTenNT)) focusTenNT = false;

    GuiLabel({180,170,150,30}, "So Dien Thoai:");
    if(GuiTextBox({350,170,300,30}, sdtNguoiThue, 16, focusSdtNT)) focusSdtNT = false;

    GuiLabel({180,220,150,30}, "Que Quan:");
    if(GuiTextBox({350,220,300,30}, diaChiNguoiThue, 100, focusDiaChiNT)) focusDiaChiNT = false;

    GuiLabel({180,270,150,30}, "Ngay Bat thue:");
    if(GuiTextBox({350,270,300,30}, ngaBatDauThue, 12, focusNgayNT)) focusNgayNT = false;

    GuiLabel({180,320,150,30}, "Phong muon thue:");
    std::string nutPhong = (phongMuonThue == 0) ? "Chon Phong" : ("Phong " + std::to_string(phongMuonThue));
    if(GuiButton({350,320,300,30},nutPhong.c_str())){
        return SCREEN_CHONPHONG;
    }

    static std::string errorMessage = "";
    static bool showSuccess = false;

    if (GuiButton({425, 420, 150, 40}, "Dang Ky"))
    {
        errorMessage = "";
        showSuccess = false;
       
        if (currentUserSoTK == currentChuTroSTK)
    {
        errorMessage = "Khong the thue phong tro cua chinh minh.";
        goto SHOW_MES;
    }
        if (strlen(tenNguoiThue) == 0)
            errorMessage = "Vui long nhap day du thong tin!";
        else if (strlen(sdtNguoiThue) == 0)
            errorMessage = "Vui long nhap day du thong tin!";
        else if (strlen(diaChiNguoiThue) == 0)
            errorMessage = "Vui long nhap day du thong tin!";
        else if (strlen(ngaBatDauThue) == 0)
            errorMessage = "Vui long nhap day du thong tin!";
        else if (phongMuonThue == 0)
            errorMessage = "Vui long nhap day du thong tin!";

        if (!errorMessage.empty())
            goto SHOW_MES;
       try {
           
    NguoiThue nt(
            currentUserSoTK,      
            currentChuTroSTK,     
            tenNguoiThue,         
            diaChiNguoiThue,      
            sdtNguoiThue,         
            ngaBatDauThue,    
            phongMuonThue     
        );
        DangKiThue dkThue(nt); 
        dkThue.setStatusNT(CHO_DUYET_NT);
        dsDKiThue.them(dkThue);
        dsDKiThue.luuFile("dangkithuephong.txt");

        showSuccess = true;
        
    }
    catch (...) {
        errorMessage = "Loi he thong!";
    }
}

    SHOW_MES:
    if (!errorMessage.empty()) {
        DrawText(errorMessage.c_str(), 330, 480, 20, RED);
    }
    else if (showSuccess) {
        DrawText("Dang ky thanh cong", 390, 480, 20, GREEN);
    }

    if (GuiButton({400, 700, 200, 30}, "Quay Lai"))
    {
        tenNguoiThue[0] = sdtNguoiThue[0] = diaChiNguoiThue[0] = phongSo[0] = '\0';
        phongMuonThue = 0;
        errorMessage = "";
        showSuccess = false;
        return SCREEN_CHITIET_PHONGTRO;
    }

    return SCREEN_DK_THUE;
}
ScreenState DrawScreenTimKiem(){
    ClearBackground(RAYWHITE);
    GuiSetStyle(DEFAULT, TEXT_SIZE, 20);

    float fontSize = 30;
    const char* title = "TIM KIEM PHONG TRO";
    int textWidth = MeasureText(title, fontSize);
    int textX = (1000 - textWidth) / 2;
    DrawText(title, textX, 40, fontSize, DARKBLUE);


  if (GuiButton({350, 300, 300, 50}, "Chon Dia Chi"))
        return SCREEN_TKTINH;

    if(GuiButton({400,700,200,30}, "Quay Lai")){
        return SCREEN_TENANT;

     }
    return SCREEN_TIMKIEM;
}
ScreenState DrawScreenDanhSach(QuanLy<DangKi>& dsDangKi)
{

    static bool firstLoad = true;
    if (firstLoad) {
        dsDangKi.docFile("dangky.txt");
        firstLoad = false;
    }

    ClearBackground(RAYWHITE);
    GuiSetStyle(DEFAULT, TEXT_SIZE, 20);

    float fontSize = 30;
    const char* title = "DANH SACH CHO DUYET";
    int textWidth = MeasureText(title, fontSize);
    int textX = (1000 - textWidth) / 2;
    DrawText(title, textX, 40, fontSize, DARKBLUE);

    int y = 120;
    bool hasPending = false;
    for (int i = 0; i < dsDangKi.size(); i++)
    {
        DangKi& dk = dsDangKi.lay(i);

        if (dk.getStatus() == CHO_DUYET)
        {
            const ChuTro& ct = dk.getChuTro();

            if (GuiButton({300, (float)y, 400, 50}, ct.getTen().c_str()))
            {
                dsDangKi.setSelected(i);
                return SCREEN_CHITIET;
            }

            y += 70;
            hasPending = true;
        }
    }

    if (!hasPending)
    {
        DrawText("Khong co chu tro nao cho duyet", 300, 350, 25, RED);
    }

    if (GuiButton({400, 700, 200, 30}, "Quay Lai"))
        return SCREEN_CHUTRO;

    return SCREEN_AD_DUYET;
}

ScreenState DrawScreenChiTiet(QuanLy<DangKi>& dsDangKi,  QuanLy<DangKi>& dsDaDuyet,HinhAnh& anh) {
    int index = dsDangKi.getSelected();
    if (index < 0 || index >= dsDangKi.size()) return SCREEN_AD_DUYET;

    DangKi& dk = dsDangKi.lay(index);
    const ChuTro& ct = dk.getChuTro();

    ClearBackground(RAYWHITE);
    GuiSetStyle(DEFAULT, TEXT_SIZE, 20);

    float fontSize = 30;
    const char* title = "THONG TIN DANG KI";
    int textWidth = MeasureText(title, fontSize);
    int textX = (1000 - textWidth) / 2;
    DrawText(title, textX, 40, fontSize, DARKBLUE);
    GuiLabel({200, 100, 400, 30}, ("Ten: " + ct.getTen()).c_str());
    GuiLabel({200, 150, 400, 30}, ("SDT: " + ct.getSdt()).c_str());
    GuiLabel({200, 200, 400, 30}, ("Dia Chi: " + ct.getDiaChi()).c_str());
    GuiLabel({200, 250, 400, 30}, ("So Luong Phong:"+ std::to_string(ct.getSoLuongPhong())).c_str());
    GuiLabel({200, 300, 400, 30}, ("Tien Phong: " + ct.getTienPhong() + " VND").c_str());
    GuiLabel({200, 350, 400, 30}, ("Don Gia Dien: " + ct.getTienDien() + " VND").c_str());
    GuiLabel({200, 400, 400, 30}, ("Don Gia Nuoc: " + ct.getTienNuoc() + " VND").c_str());
    if (!ct.getHinhAnh().empty() && anh.has(ct.getHinhAnh())) {
        Texture2D tex = anh.get(ct.getHinhAnh());
        DrawTextureEx(tex, {600, 120}, 0, 0.35f, WHITE);
        GuiLabel({600, 100, 200, 25}, "Anh");
    }
    if (GuiButton({250, 600, 150, 50}, "DUYET")) {
        dk.setStatus(TrangThai::DA_DUYET);

        if (!ct.getHinhAnh().empty()) {
            std::string src = "hinhanh/" + ct.getHinhAnh();
            std::string dest = "hinhanhdatai/" + ct.getHinhAnh();
            std::filesystem::copy_file(src, dest, std::filesystem::copy_options::overwrite_existing);
        }

        std::string userFile = "data/" + ct.getSTK() + "/chutro.txt";
        dsDaDuyet.them(dk);
        dsDaDuyet.luuFile("quanlyct.txt");
        dsDaDuyet.docFile(userFile);
        dsDaDuyet.them(dk);
        dsDaDuyet.luuFile(userFile);

        dsDangKi.erase(index);
        dsDangKi.luuFile("dangky.txt");
        dsDangKi.clearSelected();
        return SCREEN_AD_DUYET;
    }
    if (GuiButton({600, 600, 150, 50}, "TU CHOI")) {
        dsDangKi.erase(index);
        dsDangKi.luuFile("dangky.txt");
        dsDangKi.clearSelected();
        return SCREEN_AD_DUYET;
    }
    if (GuiButton({400, 700, 200, 30}, "Quay Lai")) {
        dsDangKi.clearSelected();
        return SCREEN_AD_DUYET;
    }

    return SCREEN_CHITIET;
}


ScreenState DrawScreenChuTro()
{
    ClearBackground(RAYWHITE);
    GuiSetStyle(DEFAULT, TEXT_SIZE, 20);

    float fontSize = 30;
    const char* title = "QUAN LY CHU TRO";
    int textWidth = MeasureText(title, fontSize);
    int textX = (1000 - textWidth) / 2;
    DrawText(title, textX, 40, fontSize, DARKBLUE);

    if (GuiButton({350, 200, 300, 50}, "DANH SACH CHU TRO"))
    {
        return SCREEN_AD_DADUYET; 
    }

    if (GuiButton({350, 300, 300, 50}, "DANH SACH CHO DUYET"))
    {
        return SCREEN_AD_DUYET;
    }

    if (GuiButton({350, 500, 300, 50}, "QUAY LAI"))
    {
        return SCREEN_ADMIN;
    }
    return SCREEN_CHUTRO;
}
ScreenState DrawScreenDsDaDuyet(QuanLy<DangKi>& dsDaDuyet)
{

    static bool firstLoad = true;
    if (firstLoad) {
        dsDaDuyet.docFile("quanlyct.txt");
        firstLoad = false;
    }

    ClearBackground(RAYWHITE);
    GuiSetStyle(DEFAULT, TEXT_SIZE, 20);

    float fontSize = 30;
    const char* title = "DANH SACH CHU TRO";
    int textWidth = MeasureText(title, fontSize);
    int textX = (1000 - textWidth) / 2;
    DrawText(title, textX, 40, fontSize, DARKBLUE);

    int y = 120;
    bool hasPending = false;
    for (int i = 0; i < dsDaDuyet.size(); i++)
    {
        DangKi& dk = dsDaDuyet.lay(i);
        const ChuTro& ct = dk.getChuTro();

            if (GuiButton({300, (float)y, 400, 50}, ct.getTen().c_str()))
            {
                dsDaDuyet.setSelected(i);
                return SCREEN_CHITIET_DADUYET;
            }

            y += 70;
            hasPending = true;
        
    }

    if (!hasPending)
    {
        DrawText("Khong co chu tro nao", 330, 350, 30, RED);
    }

    if (GuiButton({400, 700, 200, 30}, "Quay Lai"))
        return SCREEN_CHUTRO;

    return SCREEN_AD_DADUYET;
}
ScreenState DrawScreenDsNTCuaAd(QuanLy<DangKiThue>& dsCTDaDuyet)
{

    static bool firstLoad = true;
    if (firstLoad) {
        dsCTDaDuyet.docFile("quanlynt.txt");
        firstLoad = false;
    }

    ClearBackground(RAYWHITE);
    GuiSetStyle(DEFAULT, TEXT_SIZE, 20);

    float fontSize = 30;
    const char* title = "DANH SACH NGUOI THUE";
    int textWidth = MeasureText(title, fontSize);
    int textX = (1000 - textWidth) / 2;
    DrawText(title, textX, 40, fontSize, DARKBLUE);

    int y = 120;
    bool hasPending = false;
    for (int i = 0; i < dsCTDaDuyet.size(); i++)
    {
        DangKiThue& dk = dsCTDaDuyet.lay(i);
        const NguoiThue& nt = dk.getNguoiThue();

            if (GuiButton({300, (float)y, 400, 50}, nt.getTen().c_str()))
            {
                dsCTDaDuyet.setSelected(i);
                return SCREEN_CHITIET_NTAD;
            }

            y += 70;
            hasPending = true;
        
    }

    if (!hasPending)
    {
        DrawText("Khong co nguoi thue nao", 330, 350, 30, RED);
    }

    if (GuiButton({400, 700, 200, 30}, "Quay Lai"))
        return SCREEN_THUETRO;

    return SCREEN_NTAD;
}
ScreenState DrawScreenChiTietNTAD(QuanLy<DangKiThue>& dsCTDaDuyet) {
    int index = dsCTDaDuyet.getSelected();
    if (index < 0 || index >= dsCTDaDuyet.size()) return SCREEN_NTAD;
                std::string tenChuTro = "";
               

    DangKiThue& dk = dsCTDaDuyet.lay(index);
    const NguoiThue& ntHienTai = dk.getNguoiThue();
              QuanLy<DangKi> dsCT;
                dsCT.docFile("quanlyct.txt");
                for (int i = 0; i < dsCT.size(); i++)
                {
                    const ChuTro& ct = dsCT.lay(i).getChuTro();
                    if (ct.getSTK() == ntHienTai.getSTK_ChuTro())
                    {
                        tenChuTro = ct.getTen();
                        break;
                    }
                }
    ClearBackground(RAYWHITE);
    GuiSetStyle(DEFAULT, TEXT_SIZE, 20);

    float fontSize = 30;
    const char* title = "THONG TIN NGUOI THUE";
    int textWidth = MeasureText(title, fontSize);
    int textX = (1000 - textWidth) / 2;
    DrawText(title, textX, 40, fontSize, DARKBLUE);


     GuiLabel({200, 140, 200, 30}, "Ho va ten:");
        GuiLabel({420, 140, 400, 30}, ntHienTai.getTen().c_str());

        GuiLabel({200, 190, 200, 30}, "So dien thoai:");
        GuiLabel({420, 190, 400, 30}, ntHienTai.getSdt().c_str());

        GuiLabel({200, 240, 200, 30}, "Que quan:");
        GuiLabel({420, 240, 400, 30}, ntHienTai.getQueQuan().c_str());

        GuiLabel({200, 290, 200, 30}, "Ngay bat dau:");
        GuiLabel({420, 290, 400, 30}, ntHienTai.getNgayThue().c_str());

        GuiLabel({200, 340, 200, 30}, "Phong dang thue:");
        GuiLabel({420, 340, 400, 30}, std::to_string(ntHienTai.getPhongSo()).c_str());

        GuiLabel({200, 400, 200, 30}, "Chu tro:");
        GuiLabel({420, 400, 400, 30}, tenChuTro.c_str());

        DrawRectangleLines(180, 120, 640, 340, Fade(DARKGRAY, 0.5f));

    if (GuiButton({400, 700, 200, 30}, "Quay Lai")) {
        dsCTDaDuyet.clearSelected();
        return SCREEN_NTAD;
    }

    return SCREEN_CHITIET_NTAD;
}

ScreenState DrawScreenChiTietDaDuyet(QuanLy<DangKi>& dsDaDuyet, HinhAnh& anh) {
    int index = dsDaDuyet.getSelected();
    if (index < 0 || index >= dsDaDuyet.size()) return SCREEN_AD_DADUYET;

    DangKi& dk = dsDaDuyet.lay(index);
    const ChuTro& ct = dk.getChuTro();

    ClearBackground(RAYWHITE);
    GuiSetStyle(DEFAULT, TEXT_SIZE, 20);

    float fontSize = 30;
    const char* title = "THONG TIN CHU TRO";
    int textWidth = MeasureText(title, fontSize);
    int textX = (1000 - textWidth) / 2;
    DrawText(title, textX, 40, fontSize, DARKBLUE);


    GuiLabel({200, 100, 400, 30}, ("Ten: " + ct.getTen()).c_str());
    GuiLabel({200, 150, 400, 30}, ("SDT: " + ct.getSdt()).c_str());
    GuiLabel({200, 200, 400, 30}, ("Dia Chi: " + ct.getDiaChi()).c_str());
    GuiLabel({200, 250, 400, 30}, ("So Luong Phong:"+ std::to_string(ct.getSoLuongPhong()) ).c_str());
    GuiLabel({200, 300, 400, 30}, ("Tien Phong: " + ct.getTienPhong() + " VND").c_str());
    GuiLabel({200, 350, 400, 30}, ("Don Gia Dien: " + ct.getTienDien() + " VND").c_str());
    GuiLabel({200, 400, 400, 30}, ("Don Gia Nuoc: " + ct.getTienNuoc() +  " VND").c_str());


    if (!ct.getHinhAnh().empty() && anh.has(ct.getHinhAnh())) {
        Texture2D tex = anh.get(ct.getHinhAnh());
        DrawTextureEx(tex, {600, 120}, 0, 0.35f, WHITE);
        GuiLabel({600, 100, 200, 25}, "Anh");
    }

    if (GuiButton({400, 600, 200, 30}, "XOA"))
{
    dsDaDuyet.erase(index);
    dsDaDuyet.luuFile("quanlyct.txt");
    dsDaDuyet.clearSelected();
    return SCREEN_AD_DUYET;
}
    if (GuiButton({400, 700, 200, 30}, "Quay Lai")) {
        dsDaDuyet.clearSelected();
        return SCREEN_AD_DADUYET;
    }

    return SCREEN_CHITIET_DADUYET;
}
ScreenState DrawScreenChiTietDaDuyet2(QuanLy<DangKi>& dsDaDuyet, HinhAnh& anh) {
    int index = dsDaDuyet.getSelected();
    if (index < 0 || index >= dsDaDuyet.size()) return SCREEN_CHITIET_PHONGTRO;

    DangKi& dk = dsDaDuyet.lay(index);
    const ChuTro& ct = dk.getChuTro();

    ClearBackground(RAYWHITE);
    GuiSetStyle(DEFAULT, TEXT_SIZE, 20);

    float fontSize = 30;
    const char* title = "THONG TIN CHU TRO";
    int textWidth = MeasureText(title, fontSize);
    int textX = (1000 - textWidth) / 2;
    DrawText(title, textX, 40, fontSize, DARKBLUE);


    GuiLabel({200, 100, 400, 30}, ("Ten: " + ct.getTen()).c_str());
    GuiLabel({200, 150, 400, 30}, ("SDT: " + ct.getSdt()).c_str());
    GuiLabel({200, 200, 400, 30}, ("Dia Chi: " + ct.getDiaChi()).c_str());
    GuiLabel({200, 250, 400, 30}, ("So Luong Phong:"+ std::to_string(ct.getSoLuongPhong()) ).c_str());
    GuiLabel({200, 300, 400, 30}, ("Tien Phong: " + ct.getTienPhong() + " VND").c_str());
    GuiLabel({200, 350, 400, 30}, ("Don Gia Dien: " + ct.getTienDien() + " VND").c_str());
    GuiLabel({200, 400, 400, 30}, ("Don Gia Nuoc: " + ct.getTienNuoc() +  " VND").c_str());


    if (!ct.getHinhAnh().empty() && anh.has(ct.getHinhAnh())) {
        Texture2D tex = anh.get(ct.getHinhAnh());
        DrawTextureEx(tex, {600, 120}, 0, 0.35f, WHITE);
        GuiLabel({600, 100, 200, 25}, "Anh");
    }
    if (GuiButton({400, 700, 200, 30}, "Quay Lai")) {
        return SCREEN_CHITIET_PHONGTRO;
    }

    return SCREEN_CHITIET_DADUYET2;
}

ScreenState DrawScreenThongTinUser(const std::string& soTK, HinhAnh& anh)
{
    ClearBackground(RAYWHITE);
    GuiSetStyle(DEFAULT, TEXT_SIZE, 20);

    float fontSize = 30;
    const char* title = "THONG TIN CHU TRO";
    int textWidth = MeasureText(title, fontSize);
    int textX = (1000 - textWidth) / 2;
    DrawText(title, textX, 40, fontSize, DARKBLUE);

    static QuanLy<DangKi> dsUser;
    static bool firstLoad = true;

    if (firstLoad) {
        std::string userFile = "data/" + soTK + "/chutro.txt";
        dsUser.docFile(userFile);
        firstLoad = false;
    }

    int y = 100;
    for (int i = 0; i < dsUser.size(); i++) {
        DangKi& dk = dsUser.lay(i);
        const ChuTro& ct = dk.getChuTro();

        GuiLabel({200, float(y), 400, 30}, ("Ten: " + ct.getTen()).c_str());
        y += 50;

        GuiLabel({200, float(y), 400, 30}, ("SDT: " + ct.getSdt()).c_str());
        y += 50;

        GuiLabel({200, float(y), 400, 30}, ("Dia Chi: " + ct.getDiaChi()).c_str());
        y += 50;

        GuiLabel({200, float(y), 400, 30}, ("So Luong Phong: " + std::to_string(ct.getSoLuongPhong())).c_str());
        y += 50;

        GuiLabel({200, float(y), 400, 30}, ("Tien Phong: " + ct.getTienPhong() +" VND").c_str());
        y += 50;

        GuiLabel({200, float(y), 400, 30}, ("Don Gia Dien: " + ct.getTienDien() +" VND").c_str());
        y += 50;

        GuiLabel({200, float(y), 400, 30}, ("Don Gia Nuoc: " + ct.getTienNuoc() +" VND").c_str());
        y += 50;
        if (!ct.getHinhAnh().empty() && anh.has(ct.getHinhAnh())) {
            Texture2D tex = anh.get(ct.getHinhAnh());
            DrawTextureEx(tex, {600,120}, 0, 0.35f, WHITE);
            GuiLabel({600, 100, 200, 25}, "Anh");
        }
    }

    if (GuiButton({400, 700, 200, 30}, "Quay Lai")) {
        firstLoad = true;
        return SCREEN_INNKEEPER;
    }

    return SCREEN_THONGTIN;
}

ScreenState DrawScreenInnkeeper(){
    ClearBackground(RAYWHITE);
    GuiSetStyle(DEFAULT,TEXT_SIZE,20);
     float fontSize = 30;
    const char *title = "HE THONG CHU TRO";
    int textWibth = MeasureText(title,fontSize);
    int textX = (1000 - textWibth)/2;
    DrawText(title,textX,40,fontSize,DARKBLUE);
   
    const char *dkChuTro = "DANG KI CHU TRO";
    int textXdkChuTro = (1000 - 300)/2;
    if(GuiButton({textXdkChuTro,200,300,50},dkChuTro)){
        return SCREEN_DANGKI;} 
    const char *qlNguoiThue = "QUAN LY DAY TRO";
    int textXqlNguoiThue = (1000 - 300)/2;
    if(GuiButton({textXqlNguoiThue,300,300,50},qlNguoiThue)){
        return SCREEN_QUANLY_DAYTRO;} 
    const char *ThongTin = "THONG TIN PHONG TRO";
    int textXThongTin = (1000 - 300)/2;
    if(GuiButton({textXThongTin,400,300,50},ThongTin)){
        return SCREEN_THONGTIN;} 
     

    if(GuiButton({400,700,200,30},"Quay Lai")){
        return SCREEN_USER;
    }
    

    return SCREEN_INNKEEPER;
}
ScreenState DrawScreenTenant(){
    ClearBackground(RAYWHITE);
    GuiSetStyle(DEFAULT,TEXT_SIZE,20);
     float fontSize = 30;
    const char *title = "HE THONG NGUOI THUE";
    int textWibth = MeasureText(title,fontSize);
    int textX = (1000 - textWibth)/2;
    DrawText(title,textX,40,fontSize,DARKBLUE);
    
    
    const char *timkiem = "TIM KIEM PHONG TRO";
    int textXtimkiem = (1000 - 300)/2;
    if(GuiButton({textXtimkiem,200,300,50},timkiem)){
        return SCREEN_TIMKIEM;} 
    const char *qlpt = "QUAN LY PHONG TRO";
    int textXqlpt = (1000 - 300)/2;
    if(GuiButton({textXqlpt,300,300,50},qlpt)){
        return SCREEN_QUANLY_PHONGTRO;}  
    if(GuiButton({400,700,200,30},"Quay Lai")){
        return SCREEN_USER;
    }
    
    return SCREEN_TENANT;
}
ScreenState DrawScreenUserRegister(char* name, char* userName, char* userPass){
    static QuanLyDataUser userData;
    ClearBackground(RAYWHITE);
    GuiSetStyle(DEFAULT, TEXT_SIZE, 19);

    float fontSize = 50;
    const char *title = "DANG KY USER";
    int textWidth = MeasureText(title, fontSize);
    int textX = (800 - textWidth) / 2;
    DrawText(title, textX, 40, fontSize, DARKBLUE);

    Rectangle nameBox       = {200, 100, 400, 40}; 
    Rectangle accountBox    = {200, 170, 400, 40};   
    Rectangle passwordBox   = {200, 240, 400, 40};   
    Rectangle registerButton = {320, 320, 160, 45};  
    Rectangle btnBack       = {320, 550, 160, 45}; 

    static bool nameEditMode = false;
    static bool accountEditMode = false;
    static bool passEditMode = false;
    int labelWidth1 = MeasureText("Mat Khau",15);
    int labelWidth2 = MeasureText("So Tai Khoan",15);

    DrawText("Ten :", nameBox.x - 40, nameBox.y + (nameBox.height - 15)/2, 15, BLACK);
    DrawText("So Tai Khoan :",accountBox.x - labelWidth1 - 70,accountBox.y + (passwordBox.height -15)/2,15,BLACK);
    DrawText("Mat khau :",passwordBox.x - labelWidth2 - 10,passwordBox.y + (passwordBox.height -15)/2,15,BLACK);

    Vector2 mouse = GetMousePosition();
    bool mouseClicked = IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
    if (mouseClicked) {
        if (CheckCollisionPointRec(mouse, nameBox)) { nameEditMode = true; accountEditMode = false; passEditMode = false; }
        else if (CheckCollisionPointRec(mouse, accountBox)) { nameEditMode = false; accountEditMode = true; passEditMode = false; }
        else if (CheckCollisionPointRec(mouse, passwordBox)) { nameEditMode = false; accountEditMode = false; passEditMode = true; }
        else { nameEditMode = false; accountEditMode = false; passEditMode = false; }
    }

    GuiTextBox(nameBox, name, 64, nameEditMode);
    GuiTextBox(accountBox, userName, 64, accountEditMode);
    GuiTextBox(passwordBox, userPass, 64, passEditMode);

    static string regMessage = "";
    static Color colorMessage = RED;

    if (GuiButton(btnBack, "Quay laI")) {
        regMessage.clear();
        return SCREEN_USER_LOGIN;
    }

    if (GuiButton(registerButton, "Dang Ky")) {
        string soTK(userName);
        string mk(userPass);
        string ten(name);

        if (soTK.empty() || mk.empty() || ten.empty()) {
            regMessage = "Vui long nhap day du thong tin!";
            colorMessage = RED;
        } else {
        
            userData.dangKyUser(soTK, mk, ten);
            userData.taoFolderUser(soTK);
            userData.taoFileMacDinhUser(soTK);

            regMessage = "Dang ky thanh cong!";
            colorMessage = GREEN;
        }
    }

    if (!regMessage.empty()) {
        DrawText(regMessage.c_str(), 240, 500, 20, colorMessage);
    }

    return SCREEN_DANGKI_USER;
}
ScreenState DrawScreenQuanLyNguoiThue(){

ClearBackground(RAYWHITE);
    GuiSetStyle(DEFAULT, TEXT_SIZE, 20);

    float fontSize = 30;
    const char* title = "QUAN LY NGUOI THUE";
    int textWidth = MeasureText(title, fontSize);
    int textX = (1000 - textWidth) / 2;
    DrawText(title, textX, 40, fontSize, DARKBLUE);

    if (GuiButton({350, 200, 300, 50}, "DANH SACH NGUOI THUE"))
    {
        return SCREEN_NTAD; 
    }

    if (GuiButton({350, 300, 300, 50}, "DANH SACH CHO DUYET"))
    {
        return SCREEN_NTAD_DUYET;
    }

    if (GuiButton({350, 500, 300, 50}, "Quay Lai"))
    {
        return SCREEN_ADMIN;
    }
    return SCREEN_THUETRO;}
ScreenState DrawScreenDanhSachNT(QuanLy<DangKiThue>& dsDangKiThue)
{
    static bool daDocFile = false;
    if (!daDocFile) {
        dsDangKiThue.docFile("dangkithuephong.txt");
        daDocFile = true;
    }

    ClearBackground(RAYWHITE);
    GuiSetStyle(DEFAULT, TEXT_SIZE, 20);

    float fontSize = 30;
    const char* title = "DANH SACH NGUOI THUE CHO DUYET";
    int textWidth = MeasureText(title, fontSize);
    int textX = (1000 - textWidth) / 2;
    DrawText(title, textX, 40, fontSize, DARKBLUE);

    int y = 120;
    bool hasPending = false;

    for (int i = 0; i < dsDangKiThue.size(); i++)
    {
        DangKiThue& dk = dsDangKiThue.lay(i);

        if (dk.getStatusNT() == CHO_DUYET_NT)  
        {
            const NguoiThue& nt = dk.getNguoiThue();

            std::string info = nt.getTen();

            if (GuiButton({250, (float)y, 500, 60}, info.c_str()))
            {
                dsDangKiThue.setSelected(i);  
                return SCREEN_NTAD_CHITIET;
            }

            y += 120;  
            hasPending = true;
        }
    }

    if (!hasPending)
    {
        DrawText("Khong co nguoi thue nao dang cho duyet", 250, 380, 24, RED);
    }

    if (GuiButton({400, 700, 200, 40}, "Quay Lai"))
    {
        dsDangKiThue.clearSelected();
        daDocFile = false;
        return SCREEN_THUETRO;  
    }
    return SCREEN_NTAD_DUYET;
}
ScreenState DrawScreenChiTietDangKiThue(QuanLy<DangKiThue>& dsDangKiThue, QuanLy<DangKiThue>& dsAdDaDuyet)
{
    int index = dsDangKiThue.getSelected();
    if (index < 0 || index >= dsDangKiThue.size()) {
        return SCREEN_NTAD_DUYET;
    }

    DangKiThue& dk = dsDangKiThue.lay(index);
    const NguoiThue& nt = dk.getNguoiThue();

    ClearBackground(RAYWHITE);
    GuiSetStyle(DEFAULT, TEXT_SIZE, 20);

  
    float fontSize = 30;
    const char* title = "CHI TIET";
    int textWidth = MeasureText(title, fontSize);
    int textX = (1000 - textWidth) / 2;
    DrawText(title, textX, 40, fontSize, DARKBLUE);

    GuiLabel({200, 130, 200, 30}, "Ho va ten:");
    GuiLabel({420, 130, 400, 30}, nt.getTen().c_str());

    GuiLabel({200, 180, 200, 30}, "So dien thoai:");
    GuiLabel({420, 180, 400, 30}, nt.getSdt().c_str());

    GuiLabel({200, 230, 200, 30}, "Que quan:");
    GuiLabel({420, 230, 400, 30}, nt.getQueQuan().c_str());

    GuiLabel({200, 280, 200, 30}, "Ngay bat dau thue:");
    GuiLabel({420, 280, 400, 30}, nt.getNgayThue().c_str());

    GuiLabel({200, 330, 200, 30}, "Phong muon thue:");
    GuiLabel({420, 330, 400, 30},std::to_string( nt.getPhongSo()).c_str());
    static QuanLy<DangKi> dsChuTroDaDuyet;
    static bool loaded = false;
    if (!loaded) {
        dsChuTroDaDuyet.docFile("quanlyct.txt");
        loaded = true;
    }

    std::string tenChuTro = "Khong tim thay chu tro";
    for (int i = 0; i < dsChuTroDaDuyet.size(); i++) {
        const ChuTro& ct = dsChuTroDaDuyet.lay(i).getChuTro();
        if (ct.getSTK() == nt.getSTK_ChuTro()) {
            tenChuTro = ct.getTen();
            break;
        }
    }

    GuiLabel({200, 390, 200, 30}, "Chu tro:");
    GuiLabel({420, 390, 400, 30}, tenChuTro.c_str());

    if (GuiButton({280, 500, 160, 60}, "DUYET")) {
        dk.setStatusNT(DA_DUYET_NT);

        std::string filename = "data/" + nt.getSTK_ChuTro() + "/dondkthuept.txt";

        dsAdDaDuyet.them(dk);
        dsAdDaDuyet.luuFile(filename);
        dsDangKiThue.erase(index);
        dsDangKiThue.luuFile("dangkithuephong.txt");
        dsDangKiThue.clearSelected();

         return SCREEN_NTAD_DUYET;
    }

    if (GuiButton({520, 500, 160, 60}, "TU CHOI")) {
        dk.setStatusNT(TU_CHOI_NT);
        dsDangKiThue.erase(index);
        dsDangKiThue.luuFile("dangkithuephong.txt");
        dsDangKiThue.clearSelected();
         return SCREEN_NTAD_DUYET;
    }

    
    if (GuiButton({400, 600, 200, 50}, "Quay Lai")) {
        dsDangKiThue.clearSelected();
        return SCREEN_NTAD_DUYET;
    }
    return SCREEN_NTAD_CHITIET;
}
ScreenState DrawScreenDayTro()
{
    ClearBackground(RAYWHITE);
    GuiSetStyle(DEFAULT, TEXT_SIZE, 20);

    float fontSize = 30;
    const char* title = "QUAN LY DAY TRO";
    int textWidth = MeasureText(title, fontSize);
    int textX = (1000 - textWidth) / 2;
    DrawText(title, textX, 40, fontSize, DARKBLUE);

    if (GuiButton({350, 200, 300, 50}, "QUAN LY PHONG TRO"))
    {
        return SCREEN_DS_PHONGTRO; 
    }

    if (GuiButton({350, 300, 300, 50}, "DANH SACH CHO DUYET"))
    {
        return SCREEN_DS_CD;
    }

    if (GuiButton({350, 500, 300, 50}, "Quay Lai"))
    {
        return SCREEN_INNKEEPER;
    }
    return SCREEN_QUANLY_DAYTRO;
}
ScreenState DrawDSCD(QuanLy<DangKiThue>& dsAdDaDuyet){

   
    static bool daDocFile = false;
    
    if (!daDocFile)
    {
        string folder = "data/" + currentUserSoTK + "/";
        string filename = folder + "dondkthuept.txt";
        if (!std::filesystem::exists(folder))
            std::filesystem::create_directories(folder);

        dsAdDaDuyet.docFile(filename);
        daDocFile = true;
    }

    ClearBackground(RAYWHITE);
    GuiSetStyle(DEFAULT, TEXT_SIZE, 20);
    float fontSize = 30;
    const char* title = "DANH SACH CHO DUYET";
    int textWidth = MeasureText(title, fontSize);
    int textX = (1000 - textWidth) / 2;
    DrawText(title, textX, 40, fontSize, DARKBLUE);

    int y = 120;
    bool coDon = false;

    for (int i = 0; i < dsAdDaDuyet.size(); i++) {
        DangKiThue& dk = dsAdDaDuyet.lay(i);
        const NguoiThue& nt = dk.getNguoiThue();
        if (dk.getStatusNT() == DA_DUYET_NT) {
            string info = nt.getTen() + " - Phong: " + std::to_string(nt.getPhongSo()) + " - " + nt.getNgayThue();

            if (GuiButton({200, (float)y, 600, 60}, info.c_str())) {
                dsAdDaDuyet.setSelected(i);
                daDocFile = false;
                return SCREEN_CT_CHITIET_DON;
            }
            y += 80;
            coDon = true;
        }
    }

    if (!coDon) {
        DrawText("Hien tai khong co don nao cho duyet", 300, 250, 25, GRAY);
    }


      if (GuiButton({350, 500, 300, 50}, "Quay Lai"))
    {
        daDocFile = false;             
        dsAdDaDuyet.clearSelected();
        return SCREEN_QUANLY_DAYTRO;
    }
    return SCREEN_DS_CD;
}
ScreenState DrawScreenChiTietDonChuTro(QuanLy<DangKiThue>& dsAdDaDuyet,QuanLy<DangKiThue> dsCTDaDuyet)
{
    int index = dsAdDaDuyet.getSelected();
    if (index < 0 || index >= dsAdDaDuyet.size()) {
        return SCREEN_DS_CD;
    }

    DangKiThue& dk = dsAdDaDuyet.lay(index);
    const NguoiThue& nt = dk.getNguoiThue();

    ClearBackground(RAYWHITE);
    GuiSetStyle(DEFAULT, TEXT_SIZE, 20);

    DrawText("CHI TIET DON THUE PHONG", 350, 40, 30, DARKBLUE);

    GuiLabel({200, 120, 200, 30}, "Ho ten:");
    GuiLabel({400, 120, 400, 30}, nt.getTen().c_str());

    GuiLabel({200, 170, 200, 30}, "So dien thoai:");
    GuiLabel({400, 170, 400, 30}, nt.getSdt().c_str());

    GuiLabel({200, 220, 200, 30}, "Que quan:");
    GuiLabel({400, 220, 400, 30}, nt.getQueQuan().c_str());

    GuiLabel({200, 270, 200, 30}, "Ngay Bat Dau Thue:");
    GuiLabel({400, 270, 400, 30}, nt.getNgayThue().c_str());

    GuiLabel({200, 320, 200, 30}, "Phong muon thue:");
    GuiLabel({400, 320, 400, 30}, std::to_string(nt.getPhongSo()).c_str());

    if (GuiButton({250, 450, 150, 60}, "DUYET")) {
        dk.setStatusNT(DA_DUYET_NT);
    const NguoiThue nt = dk.getNguoiThue();

    {
        std::string path = "data/" + currentUserSoTK + "/quanlynt.txt";
        std::filesystem::create_directories("data/" + currentUserSoTK);

        std::ofstream f(path, std::ios::app);
        f << nt.getSTK_NguoiThue() << ","
          << currentUserSoTK << ","
          << nt.getTen() << ","
          << nt.getSdt() << ","
          << nt.getQueQuan() << ","
          << nt.getNgayThue() << ","
          << nt.getPhongSo() << ","
          << DA_DUYET_NT << "\n";
        f.close();
    }

    {
        std::string path = "data/" + nt.getSTK_NguoiThue() + "/nguoithue.txt";
        std::filesystem::create_directories("data/" + nt.getSTK_NguoiThue());

        std::ofstream f(path, std::ios::app);
        f << nt.getSTK_NguoiThue() << ","
          << currentUserSoTK << ","
          << nt.getTen() << ","
          << nt.getSdt() << ","
          << nt.getQueQuan() << ","
          << nt.getNgayThue() << ","
          << nt.getPhongSo() << ","
          << DA_DUYET_NT << "\n";
        f.close();
    }
    dsAdDaDuyet.luuFile("quanlynt.txt");
    dsAdDaDuyet.erase(index);
    dsAdDaDuyet.luuFile("data/" + currentUserSoTK + "/dondkthuept.txt");

        DrawText("DA DUYET THANH CONG!", 380, 550, 25, GREEN);
        return SCREEN_DS_CD;
    }

    if (GuiButton({550, 450, 150, 60}, "TU CHOI")) {
        dk.setStatusNT(TU_CHOI_NT);
        dsAdDaDuyet.erase(index);
        dsAdDaDuyet.luuFile("data/" + currentUserSoTK + "/dondkthuept.txt");
        return SCREEN_DS_CD;
    }

    if (GuiButton({400, 700, 200, 40}, "Quay Lai")) {
        mydondk.clearSelected();
        return SCREEN_DS_CD;
    }

    return SCREEN_CT_CHITIET_DON;
}

ScreenState DrawScreenQuanLyPhongTroCuaChuTro(QuanLy<DangKi>& dsChuTro)
{       
    static bool daDoc = false;

    if (!daDoc)
    {
        soLuongPhong = 0;
        phongDangXem = 0;
        for (int i = 1; i <= 100; i++)
        {
            phongDaThue[i] = false;
            dsNguoiThuePhong[i] = NguoiThue();
        }
        std::string pathChuTro = "data/" + currentUserSoTK + "/chutro.txt";
        if (FileExists(pathChuTro.c_str()))
        {
            dsChuTro.docFile(pathChuTro);
        }
        else
        {

            dsChuTro.docFile("chutro.txt");
        }
        for (int i = 0; i < dsChuTro.size(); i++)
        {
            const ChuTro& ct = dsChuTro.lay(i).getChuTro();
            if (ct.getSTK() == currentUserSoTK)
            {
                soLuongPhong = ct.getSoLuongPhong();
                if (soLuongPhong > 100) soLuongPhong = 100;
                break;
            }
        }

        std::string pathNT = "data/" + currentUserSoTK + "/quanlynt.txt";
        if (FileExists(pathNT.c_str()))
        {
            QuanLy<DangKiThue> dsTemp;
            dsTemp.docFile(pathNT);

            for (int i = 0; i < dsTemp.size(); i++)
            {
                const NguoiThue& nt = dsTemp.lay(i).getNguoiThue();
                int p = nt.getPhongSo();
                if (p >= 1 && p <= soLuongPhong)
                {
                    phongDaThue[p] = true;
                    dsNguoiThuePhong[p] = nt;  
                }
            }
        }

        daDoc = true;
    }

    ClearBackground(RAYWHITE);
    GuiSetStyle(DEFAULT, TEXT_SIZE, 20);
    DrawText("QUAN LY PHONG TRO", 350, 40, 32, DARKBLUE);

    if (soLuongPhong <= 0)
    {
        DrawText("Ban chua dang ky phong tro nao", 300, 300, 28, RED);
    }
    else
    {
        DrawText(("Tong so phong: " + std::to_string(soLuongPhong)).c_str(), 380, 100, 26, DARKBLUE);

        const int COLS = 4;
        const int BTN_W = 180;
        const int BTN_H = 100;
        const int SPACE_X = 60;
        const int SPACE_Y = 100;
        const int START_X = 80;
        const int START_Y = 160;

        for (int i = 1; i <= soLuongPhong; i++)  
        {
            int col = (i - 1) % COLS;
            int row = (i - 1) / COLS;
            int x = START_X + col * (BTN_W + SPACE_X);
            int y = START_Y + row * (BTN_H + SPACE_Y);

            std::string tenPhong = "Phong " + std::to_string(i);
            std::string trangThai = phongDaThue[i] ? "Dang thue" : "Trong";
            Color mauNen = phongDaThue[i] ? GREEN : LIGHTGRAY;
            Color mauChu = phongDaThue[i] ? WHITE : DARKBLUE;

            DrawRectangle(x, y, BTN_W, BTN_H, mauNen);
            DrawRectangleLines(x, y, BTN_W, BTN_H, DARKGRAY);


            int textW = MeasureText(tenPhong.c_str(), 28);
            DrawText(tenPhong.c_str(), x + (BTN_W - textW) / 2, y + 20, 28, mauChu);

            int textW2 = MeasureText(trangThai.c_str(), 22);
            DrawText(trangThai.c_str(), x + (BTN_W - textW2) / 2, y + 60, 22, mauChu);

            Rectangle rec = {(float)x, (float)y, (float)BTN_W, (float)BTN_H};
            if (CheckCollisionPointRec(GetMousePosition(), rec) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                if (phongDaThue[i])
                {
                    phongDangXem = i;  
                    return SCREEN_CT_CHITIET_NGUOITHUE;  
                }
                else
                {
                }
            }
        }
    }

    if (GuiButton({300, 700, 150, 50}, "Lam moi"))
    {
        daDoc = false;  
    }

    if (GuiButton({550, 700, 150, 50}, "Quay Lai"))
    {
        daDoc = false;
        return SCREEN_QUANLY_DAYTRO;
    }

    return SCREEN_DS_PHONGTRO;
}
ScreenState DrawScreenChiTietNguoiThue()
{
   if (phongDangXem == 0 || phongDangXem > 100)
    {
        return SCREEN_DS_PHONGTRO;
    }

    const NguoiThue& nt = dsNguoiThuePhong[phongDangXem];


    if (nt.getTen().empty())
    {
        return SCREEN_DS_PHONGTRO;
    }

    ClearBackground(RAYWHITE);
    GuiSetStyle(DEFAULT, TEXT_SIZE, 20);

    DrawText(TextFormat("THONG TIN NGUOI THUE - PHONG %d", phongDangXem), 280, 40, 32, DARKBLUE);

    GuiLabel({220, 140, 180, 30}, "Ho va ten:");
    GuiLabel({420, 140, 400, 30}, nt.getTen().c_str());

    GuiLabel({220, 190, 180, 30}, "So dien thoai:");
    GuiLabel({420, 190, 400, 30}, nt.getSdt().c_str());

    GuiLabel({220, 240, 180, 30}, "Que quan:");
    GuiLabel({420, 240, 400, 30}, nt.getQueQuan().c_str());

    GuiLabel({220, 290, 180, 30}, "Ngay bat dau thue:");
    GuiLabel({420, 290, 400, 30}, nt.getNgayThue().c_str());

    GuiLabel({220, 340, 180, 30}, "So TK:");
    GuiLabel({420, 340, 400, 30}, nt.getSTK_NguoiThue().c_str());

    GuiLabel({220, 400, 180, 30}, "Trang thai:");
    GuiLabel({420, 400, 400, 30}, "Dang thue");

    if (GuiButton({300, 500, 200, 60}, "XOA"))
    {
        dsNguoiThuePhong[phongDangXem] = NguoiThue();
        phongDaThue[phongDangXem] = false;


        QuanLy<DangKiThue> dsTemp;
        std::string pathCT = "data/" + currentUserSoTK + "/quanlynt.txt";
        if (FileExists(pathCT.c_str()))
        {
            dsTemp.docFile(pathCT);
        }
        for (int i = 0; i < dsTemp.size(); i++)
        {
            if (dsTemp.lay(i).getNguoiThue().getPhongSo() == phongDangXem)
            {
                dsTemp.erase(i);
                break;
            }
        }
        dsTemp.luuFile(pathCT);
        std::string pathNT = "data/" + nt.getSTK_NguoiThue() + "/nguoithue.txt";
        if (FileExists(pathNT.c_str()))
        {
            std::remove(pathNT.c_str());
        }

        phongDangXem = 0;
        return SCREEN_DS_PHONGTRO;  
    }

    if (GuiButton({550, 500, 200, 60}, "QUAY LAI"))
    {
        phongDangXem = 0;
        return SCREEN_DS_PHONGTRO;
    }
    return SCREEN_CT_CHITIET_NGUOITHUE;
}

ScreenState DrawScreenPhongTroCuaToi()
{
    static bool daDoc = false;
    static NguoiThue ntHienTai;           
    static std::string tenChuTro = "";

    if (!daDoc)
    {
        tenChuTro = "Khong tim thay chu tro";
        ntHienTai = NguoiThue(); 

        std::string path = "data/" + currentUserSoTK + "/nguoithue.txt";

        if (FileExists(path.c_str()))
        {
            std::ifstream f(path);
            std::string line;
            if (std::getline(f, line) && !line.empty())
            {
                std::stringstream ss(line);
                std::string stkNT, stkCT, ten, sdt, que, ngay, phong, status;

                std::getline(ss, stkNT,   ',');
                std::getline(ss, stkCT,   ',');
                std::getline(ss, ten,     ',');
                std::getline(ss, sdt,     ',');
                std::getline(ss, que,     ',');
                std::getline(ss, ngay,    ',');
                std::getline(ss, phong,   ',');
                std::getline(ss, status,  ',');
                
                int PhongSo = 0;
               if (!phong.empty())
               {PhongSo = std::stoi(phong);}
                ntHienTai = NguoiThue(stkNT, stkCT, ten, que, sdt, ngay, PhongSo);
                QuanLy<DangKi> dsCT;
                dsCT.docFile("quanlyct.txt");
                for (int i = 0; i < dsCT.size(); i++)
                {
                    const ChuTro& ct = dsCT.lay(i).getChuTro();
                    if (ct.getSTK() == stkCT)
                    {
                        tenChuTro = ct.getTen();
                        break;
                    }
                }
            }
            f.close();
        }
        daDoc = true;
    }

    ClearBackground(RAYWHITE);
    GuiSetStyle(DEFAULT, TEXT_SIZE, 20);
    DrawText("PHONG TRO CUA TOI", 380, 40, 32, DARKBLUE);

    if (ntHienTai.getTen().empty())
    {
        DrawText("Ban chua thue phong nao", 360, 300, 28, RED);
    }
    else
    {
        GuiLabel({200, 140, 200, 30}, "Ho va ten:");
        GuiLabel({420, 140, 400, 30}, ntHienTai.getTen().c_str());

        GuiLabel({200, 190, 200, 30}, "So dien thoai:");
        GuiLabel({420, 190, 400, 30}, ntHienTai.getSdt().c_str());

        GuiLabel({200, 240, 200, 30}, "Que quan:");
        GuiLabel({420, 240, 400, 30}, ntHienTai.getQueQuan().c_str());

        GuiLabel({200, 290, 200, 30}, "Ngay bat dau:");
        GuiLabel({420, 290, 400, 30}, ntHienTai.getNgayThue().c_str());

        GuiLabel({200, 340, 200, 30}, "Phong dang thue:");
        GuiLabel({420, 340, 400, 30}, std::to_string(ntHienTai.getPhongSo()).c_str());

        GuiLabel({200, 400, 200, 30}, "Chu tro:");
        GuiLabel({420, 400, 400, 30}, tenChuTro.c_str());

        DrawRectangleLines(180, 120, 640, 340, Fade(DARKGRAY, 0.5f));
    }

    if (GuiButton({350, 600, 150, 50}, "Lam moi"))
        daDoc = false;

    if (GuiButton({520, 600, 150, 50}, "Quay Lai"))
        return SCREEN_TENANT;

    return SCREEN_QUANLY_PHONGTRO;
}
ScreenState DrawScreenChonPhong(QuanLy<DangKi>& dsDaDuyet){
    static int soLuongPhong = 0;
    static bool phongDaThue[101] = {false};
    static int chonPhong = 0;
    static bool daLoad = false;
    if(!daLoad){
        soLuongPhong = 0;
        chonPhong = 0;
        for(int i = 1;i <= 100;i++ ) phongDaThue[i] = false;

       dsDaDuyet.docFile("quanlyct.txt");

       bool timThay = false;
       for (int i = 0; i < dsDaDuyet.size(); i++)
        {
            const ChuTro& ct = dsDaDuyet.lay(i).getChuTro();
            if (ct.getSTK() == currentChuTroSTK)
            {
                soLuongPhong = ct.getSoLuongPhong();
                if (soLuongPhong > 100) soLuongPhong = 100;
                timThay = true;
                break;
            }
        }
        if(!timThay || soLuongPhong <= 0){
            soLuongPhong = 0;
        }
        else 
        {
            std::string NT = "data/" + currentChuTroSTK + "/quanlynt.txt";
            if(FileExists(NT.c_str())){
                QuanLy<DangKiThue> dsNT;
                dsNT.docFile(NT);

                for(int i = 0;i < dsNT.size();i++){
                    int p = dsNT.lay(i).getNguoiThue().getPhongSo();
                    if(p >= 1 && p <= soLuongPhong ){
                        phongDaThue[p] = true;
                    }
                }
            }
        }
        daLoad = true ;
    }
        ClearBackground(RAYWHITE);
        GuiSetStyle(DEFAULT, TEXT_SIZE, 20);
         
    float fontSize = 30;
    const char* title = "CHON PHONG";
    int textWidth = MeasureText(title, fontSize);
    int textX = (1000 - textWidth) / 2;
    DrawText(title, textX, 40, fontSize, DARKBLUE);
   if(soLuongPhong <= 0)
   {
    DrawText("Chu Tro Chua Co Phong",280,300,26,RED);
   }else{
    const int COLS = 5;
        const int BTN_W = 130;
        const int BTN_H = 70;
        const int SPACE_X = 40;
        const int SPACE_Y = 90;
        const int START_X = 120;
        const int START_Y = 180;

        for (int i = 1; i <= soLuongPhong; i++)
        {
            int col = (i - 1) % COLS;
            int row = (i - 1) / COLS;
            int x = START_X + col * (BTN_W + SPACE_X);
            int y = START_Y + row * (BTN_H + SPACE_Y);

            std::string label = "Phong " + std::to_string(i);
            Color mauNen = phongDaThue[i] ? MAROON : (chonPhong == i ? SKYBLUE : LIGHTGRAY);

            if (GuiButton({(float)x, (float)y, (float)BTN_W, (float)BTN_H}, label.c_str()))
            {
                if (!phongDaThue[i])
                {
                    chonPhong= i;  
                }
            }

            if (phongDaThue[i])
            {
                DrawText("Da thue", x + 25, y + BTN_H + 10, 20, RED);
            }
            else if (chonPhong == i)
            {
                DrawText("Da chon", x + 30, y + BTN_H + 10, 20, DARKBLUE);
            }
            else
            {
                DrawText("Trong", x + 40, y + BTN_H + 10, 20, GREEN);
            }
        }
   }

bool coPhongTrong = false;
    for (int i = 1; i <= soLuongPhong; i++)
    {
        if (!phongDaThue[i]) { coPhongTrong = true; break; }
    }

    if (GuiButton({300, 650, 200, 50}, "Xac nhan chon phong"))
    {
        if (chonPhong == 0)
        {
            
        }
        else
        {
            
            phongMuonThue = chonPhong;
        }

        daLoad = false; 
        return SCREEN_DK_THUE;  
    }

    if (GuiButton({550, 650, 150, 50}, "Huy"))
    {   
        phongMuonThue = 0;
        chonPhong = 0;
        daLoad = false;
        return SCREEN_DK_THUE;
    }

   return SCREEN_CHONPHONG;

}
int main(){
    InitWindow(ScreenWidth,ScreenHeigth,"PBL2");
    SetTargetFPS(60);
    adminTable.loadFromFile("admin.txt");
    userTable.loadFromFile("user.txt");
    
    ScreenState currentScreen = SCREEN_LOGIN;
    ScreenState nextScreen = SCREEN_LOGIN;
    ScreenState prevScreen = SCREEN_AD_DADUYET;
     
    static char adminName[64] = "";
    static char adminPass[64] = "";
    static char userName[64]  = "";
    static char userPass[64]  = "";
    static char registersoTK[64] = "";
    static char registerPass[64] = "";
    static char registerName[64] = "";
    std::string tinh = "";
    std::string quan = "";
    std::string diaChiDaChon;
    
    QuanLy<DangKi> dsDangKi;
    QuanLy<DangKi> dsDaDuyet;
    QuanLy<DangKi> dsChuTro;
    QuanLy<DangKiThue> dsDangKiThue;
    QuanLy<DangKiThue> dsAdDaDuyet;
    QuanLy<DangKiThue> dsCTDaDuyet;
    HinhAnh hinhAnhManager;
    hinhAnhManager.loadAnh("hinhanh"); 
    HinhAnh hinhAnhDaDuyet;
    hinhAnhDaDuyet.loadAnh("hinhanhdatai");

    while(!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(RAYWHITE);
        
        switch (currentScreen)
        {
        case SCREEN_LOGIN:
            currentScreen = DrawScreenLogin();
            break;

        case SCREEN_ADMIN_LOGIN:
            nextScreen = DrawScreenADLogin(adminName, adminPass);
            if (nextScreen != SCREEN_ADMIN_LOGIN) currentScreen = nextScreen;
            if (currentScreen == SCREEN_ADMIN) SetWindowSize(1000, 800);
            break;

        case SCREEN_USER_LOGIN:
            nextScreen = DrawScreenUserLogin(userName, userPass);
            if (nextScreen != SCREEN_USER_LOGIN) currentScreen = nextScreen;
            if (currentScreen == SCREEN_USER) SetWindowSize(1000, 800);
            if(currentScreen == SCREEN_DANGKI_USER) SetWindowSize(800,600);
            break;

        case SCREEN_ADMIN:
            nextScreen = DrawScreenAd(adminName,adminPass);
            if (nextScreen != SCREEN_ADMIN) currentScreen = nextScreen;
            if (currentScreen == SCREEN_ADMIN_LOGIN) SetWindowSize(600, 400);
            break;

        case SCREEN_USER:
            nextScreen = DrawScreenUser(userName,userPass);
            if (nextScreen != SCREEN_USER) currentScreen = nextScreen;
            if (currentScreen == SCREEN_USER_LOGIN) SetWindowSize(600, 400);
            break;

        case SCREEN_DANGKI:
            nextScreen = DrawSCreenDK(dsDangKi, hinhAnhManager,diaChi);
            if (nextScreen != SCREEN_DANGKI) currentScreen = nextScreen;
            break;

        case SCREEN_TIMKIEM:
            SetWindowSize(1000,800);
            nextScreen = DrawScreenTimKiem();
            if (nextScreen != SCREEN_TIMKIEM) currentScreen = nextScreen;
            break;

        case SCREEN_CHITIET:
            nextScreen = DrawScreenChiTiet(dsDangKi,dsDaDuyet,hinhAnhManager);
            if (nextScreen != SCREEN_CHITIET) currentScreen = nextScreen;
            break;

        case SCREEN_CHUTRO:
            nextScreen = DrawScreenChuTro();
            if (nextScreen != SCREEN_CHUTRO) currentScreen = nextScreen;
            break;

        case SCREEN_AD_DUYET:
            nextScreen = DrawScreenDanhSach(dsDangKi);
            if (nextScreen != SCREEN_AD_DUYET) currentScreen = nextScreen;
            break;

        case SCREEN_AD_DADUYET:
            nextScreen = DrawScreenDsDaDuyet(dsDaDuyet);
            if(nextScreen == SCREEN_CHITIET_DADUYET){
                prevScreen = SCREEN_AD_DADUYET;
                nextScreen = DrawScreenChiTietDaDuyet(dsDaDuyet,hinhAnhDaDuyet);
            }
            if(nextScreen != SCREEN_AD_DADUYET) currentScreen = nextScreen;
            break;

        case SCREEN_CHITIET_PHONGTRO:
            SetWindowSize(1000,800);
            nextScreen = DrawScreenChiTietPhongTro();
            if(nextScreen != SCREEN_CHITIET_PHONGTRO) currentScreen = nextScreen;
            break;

        case SCREEN_CHITIET_DADUYET:
            nextScreen = DrawScreenChiTietDaDuyet(dsDaDuyet,hinhAnhDaDuyet);
            if(nextScreen != SCREEN_CHITIET_DADUYET) currentScreen = nextScreen;
            break;

        case SCREEN_TENANT:
            nextScreen = DrawScreenTenant();
            if(nextScreen != SCREEN_TENANT) currentScreen = nextScreen;
            break;

        case SCREEN_INNKEEPER:
            nextScreen = DrawScreenInnkeeper();
            if(nextScreen != SCREEN_INNKEEPER) currentScreen = nextScreen;
            break;

        case SCREEN_DANGKI_USER:
            nextScreen = DrawScreenUserRegister(registerName,registersoTK,registerPass);
            if(nextScreen != SCREEN_DANGKI_USER) currentScreen = nextScreen;
            if(currentScreen == SCREEN_USER_LOGIN) SetWindowSize(600,400);
            break;

        case SCREEN_THONGTIN:
            nextScreen = DrawScreenThongTinUser(currentUserSoTK,hinhAnhDaDuyet);
            if(nextScreen != SCREEN_THONGTIN) currentScreen = nextScreen;
            break;

        case SCREEN_CHONTINH:
            SetWindowSize(600,400);
            nextScreen = DrawScreenChonTinh(diaChi);
            if(nextScreen != SCREEN_CHONTINH) currentScreen = nextScreen;
            if(currentScreen == SCREEN_DANGKI) SetWindowSize(1000,800);
            break;

        case SCREEN_CHONQUAN:
            SetWindowSize(1000,800);
            nextScreen = DrawScreenChonQuan(diaChi);
            if(nextScreen != SCREEN_CHONQUAN) currentScreen = nextScreen;
            break;

        case SCREEN_TKQUAN:
            SetWindowSize(1000,800);
            nextScreen = DrawScreenTimKiemQuan(diaChiPt);
            if(nextScreen != SCREEN_TKQUAN) currentScreen = nextScreen;
            break;

        case SCREEN_TKTINH:
            SetWindowSize(600,400);
            nextScreen = DrawScreenTKTinh(diaChiPt);
            if(nextScreen != SCREEN_TKTINH) currentScreen = nextScreen;
            break;

        case SCREEN_PHONGTRO:
            nextScreen = DrawScreenPhongTro(dsDaDuyet,diaChiPt);
            if(nextScreen != SCREEN_PHONGTRO) currentScreen = nextScreen;
            break;

        case SCREEN_DK_THUE:
            SetWindowSize(1000,800);
            nextScreen = DrawScreenDangKyThue(dsDangKiThue);
            if(nextScreen != SCREEN_DK_THUE) currentScreen = nextScreen;
            break;

        case SCREEN_THUETRO:
            SetWindowSize(1000,800);
            nextScreen = DrawScreenQuanLyNguoiThue();
            if(nextScreen != SCREEN_THUETRO) currentScreen = nextScreen;
            break;

        case SCREEN_NTAD_DUYET:
            SetWindowSize(1000,800);
            nextScreen = DrawScreenDanhSachNT(dsDangKiThue);
            if(nextScreen != SCREEN_NTAD_DUYET) currentScreen = nextScreen;
            break;
        case SCREEN_NTAD_CHITIET:
            SetWindowSize(1000,800);
            nextScreen = DrawScreenChiTietDangKiThue(dsDangKiThue,dsAdDaDuyet);
            if(nextScreen != SCREEN_NTAD_CHITIET) currentScreen = nextScreen;
            break;
        case SCREEN_QUANLY_DAYTRO:
            SetWindowSize(1000,800);
            nextScreen = DrawScreenDayTro();
            if(nextScreen != SCREEN_QUANLY_DAYTRO) currentScreen = nextScreen;
            break;
        case SCREEN_DS_CD:
        SetWindowSize(1000,800);
        nextScreen = DrawDSCD(dsAdDaDuyet);
        if(nextScreen != SCREEN_DS_CD) currentScreen = nextScreen;
            break;
        case SCREEN_CT_CHITIET_DON:
        SetWindowSize(1000,800);
        nextScreen = DrawScreenChiTietDonChuTro(dsAdDaDuyet,dsCTDaDuyet);
        if(nextScreen != SCREEN_CT_CHITIET_DON) currentScreen = nextScreen;
            break;
       // case SCREEN_DS_NGUOI_THUE:
        //SetWindowSize(1000,800);
        //nextScreen = DrawScreenDsNguoiThueCuaChuTro(dsCTDaDuyet);
        //if(nextScreen != SCREEN_DS_NGUOI_THUE) currentScreen = nextScreen;
          //  break;
        case SCREEN_CT_CHITIET_NGUOITHUE:
         SetWindowSize(1000,800);
        nextScreen = DrawScreenChiTietNguoiThue();
        if(nextScreen != SCREEN_CT_CHITIET_NGUOITHUE) currentScreen = nextScreen;
            break;
        case SCREEN_QUANLY_PHONGTRO:
         SetWindowSize(1000,800);
        nextScreen = DrawScreenPhongTroCuaToi();
        if(nextScreen != SCREEN_QUANLY_PHONGTRO) currentScreen = nextScreen;
            break;  
        case SCREEN_DS_PHONGTRO:
          SetWindowSize(1000,800);
          nextScreen = DrawScreenQuanLyPhongTroCuaChuTro(dsChuTro);
          if(nextScreen != SCREEN_DS_PHONGTRO) currentScreen = nextScreen;
          break;  
            case SCREEN_CHITIET_DADUYET2:
            nextScreen = DrawScreenChiTietDaDuyet2(dsDaDuyet,hinhAnhDaDuyet);
            if(nextScreen != SCREEN_CHITIET_DADUYET2) currentScreen = nextScreen;
            break;
            case SCREEN_CHONPHONG:
            nextScreen = DrawScreenChonPhong(dsDaDuyet);
            if(nextScreen != SCREEN_CHONPHONG) currentScreen = nextScreen;
            break;
         case SCREEN_NTAD:
            nextScreen = DrawScreenDsNTCuaAd(dsCTDaDuyet);
            if(nextScreen != SCREEN_NTAD) currentScreen = nextScreen;
            break;
          case SCREEN_CHITIET_NTAD:
            nextScreen = DrawScreenChiTietNTAD(dsCTDaDuyet);
            if(nextScreen != SCREEN_CHITIET_NTAD) currentScreen = nextScreen;
            break;
        }
        
        
        EndDrawing();
    }
    CloseWindow();
    return 0;
}