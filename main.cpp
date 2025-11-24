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

HashTable<TaiKhoan> adminTable; 
HashTable<TaiKhoan> userTable; 

#define MAX_INPUT_CHARS 20

 float ScreenWidth = 600;
 float ScreenHeigth = 400;

 char ten[64] = "";
char sdt[64] = "";
char diaChi[128] = "";
char moTa[256] = "";
char hinhAnh[64] = "";

bool focusTen = false;
bool focusSdt = false;
bool focusDiaChi = false;
bool focusMoTa = false;
bool focusHinhAnh = false;

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
    SCREEN_CHITIET
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
      static string loginMessage = "";
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
        loginMessage = "Sai tai khoan hoac mat khau!";
        messagesColor = RED;
    }
}
    if(!loginMessage.empty()){
        DrawText(loginMessage.c_str(),180,300,20,messagesColor);
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
    Rectangle loginButton = {250,237,100,35};
    
    static bool nameEditMode = false;
    static bool passEditMode = false;

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
    static string loginMessage = "";     
    static Color colorMessage = RED;     

    if (GuiButton(btnBack, "QUAY LAI MENU")) {
        loginMessage.clear();            
        return SCREEN_LOGIN;
    }

    if (GuiButton(loginButton, "Dang nhap")) {
        TaiKhoan* tk = userTable.find(userName, userPass);

        if (tk) {
            loginMessage = "Dang nhap thanh cong!";
            colorMessage = GREEN;      
            return SCREEN_USER;
        } else {
            loginMessage = "Sai tai khoan hoac mat khau!";
            colorMessage = RED;
        }
    }

    if (!loginMessage.empty()) {
        DrawText(loginMessage.c_str(), 180, 300, 20, colorMessage); 
 
       return SCREEN_USER_LOGIN;

}
}
ScreenState DrawScreenAd(){
    ClearBackground(RAYWHITE);
    GuiSetStyle(DEFAULT,TEXT_SIZE,20);
    float fontSize = 30;
    const char *title = "HE THONG QUAN LY THUE PHONG TRO - ADMIN";
    int textWibth = MeasureText(title,fontSize);
    int textX = (1000 - textWibth)/2;
    DrawText(title,textX,40,fontSize,DARKBLUE);
    const char *chuTro = "Quan Ly Chu TRo";
    int textXChuTro = (1000 - 300)/2;
    if(GuiButton({textXChuTro,200,300,50},chuTro)){
        return SCREEN_CHUTRO;}
    const char *thueTro = "Quan Ly Nguoi Thue TRo";
    int textXthueTro = (1000 - 300)/2;
    if(GuiButton({textXthueTro,400,300,50},thueTro)){
        return SCREEN_THUETRO;}
    if(GuiButton({400,700,200,30},"Dang xuat")){
        return SCREEN_LOGIN;
    }
    return SCREEN_ADMIN;
}
ScreenState DrawScreenUser(){
    ClearBackground(RAYWHITE);
    GuiSetStyle(DEFAULT,TEXT_SIZE,20);
     float fontSize = 30;
    const char *title = "HE THONG DANG KI VA TIM KIEM PHONG TRO";
    int textWibth = MeasureText(title,fontSize);
    int textX = (1000 - textWibth)/2;
    DrawText(title,textX,40,fontSize,DARKBLUE);
    const char *dkchuTro = "Dang Ki Chu TRo";
    int textXdkChuTro = (1000 - 300)/2;
    if(GuiButton({textXdkChuTro,200,300,50},dkchuTro)){
        return SCREEN_DANGKI;}   
     DrawText(title,textX,40,fontSize,DARKBLUE);
    const char *timkiem = "Tim Kiem Chu TRo";
    int textXtimkiem = (1000 - 300)/2;
    if(GuiButton({textXtimkiem,300,300,50},timkiem)){
        return SCREEN_TIMKIEM;}   

    if(GuiButton({400,700,200,30},"Dang xuat")){
        return SCREEN_LOGIN;
    }
   return SCREEN_USER;
}
void resetDangKy() {
    ten[0] = sdt[0] = diaChi[0] = moTa[0] = hinhAnh[0] = '\0';
    focusTen = focusSdt = focusDiaChi = focusMoTa = focusHinhAnh = false;
    showMessage = false;
}
ScreenState DrawSCreenDK(QuanLy<DangKi>& dsDangKy, HinhAnh& hinhAnhManager){
    ClearBackground(RAYWHITE);
    GuiSetStyle(DEFAULT, TEXT_SIZE, 20);

    float fontSize = 30;
    const char* title = "DANG KI CHU TRO";
    int textWidth = MeasureText(title, fontSize);
    int textX = (1000 - textWidth) / 2;
    DrawText(title, textX, 40, fontSize, DARKBLUE);

    Vector2 mouse = GetMousePosition();
    bool mouseClicked = IsMouseButtonPressed(MOUSE_LEFT_BUTTON);

    static bool focusTen = false, focusSdt = false, focusDiaChi = false, focusMoTa = false;
    static bool chonHinhAnh = false;
    static std::string hinhAnh = "";

    if(mouseClicked){
        focusTen     = CheckCollisionPointRec(mouse, {350,100,300,30});
        focusSdt     = CheckCollisionPointRec(mouse, {350,200,300,30});
        focusDiaChi  = CheckCollisionPointRec(mouse, {350,300,300,30});
        focusMoTa    = CheckCollisionPointRec(mouse, {350,400,300,30});
        if(focusTen) focusSdt = focusDiaChi = focusMoTa = false;
        else if(focusSdt) focusTen = focusDiaChi = focusMoTa = false;
        else if(focusDiaChi) focusTen = focusSdt = focusMoTa = false;
        else if(focusMoTa) focusTen = focusSdt = focusDiaChi = false;
    }
    GuiLabel({200,100,150,30}, "Ho va Ten:");
    if(GuiTextBox({350,100,300,30}, ten, 64, focusTen)) focusTen = false;

    GuiLabel({200,200,150,30}, "So Dien Thoai:");
    if(GuiTextBox({350,200,300,30}, sdt, 64, focusSdt)) focusSdt = false;

    GuiLabel({200,300,150,30}, "Dia Chi:");
    if(GuiTextBox({350,300,300,30}, diaChi, 128, focusDiaChi)) focusDiaChi = false;

    GuiLabel({200,400,150,30}, "Mo Ta:");
    if(GuiTextBox({350,400,300,30}, moTa, 256, focusMoTa)) focusMoTa = false;

    GuiLabel({200,500,150,30}, "Hinh Anh:");
    if(GuiButton({350,500,300,30}, hinhAnh.empty() ? "Chon hinh anh": hinhAnh.c_str())){
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
        if(GuiButton({520, 550, 100, 30}, "Huy")) chonHinhAnh = false;
    }

    static bool showMessage = false;
    if(GuiButton({425,600,150,40}, "Dang Ky")){
        PhongTro pt(moTa, diaChi, hinhAnh);
        ChuTro ct(ten, sdt, pt);
        DangKi dk(ct);

        dsDangKy.them(dk);
        dsDangKy.luuFile("dangky.txt");
        showMessage = true;
    }

    if(showMessage){
        DrawText("Dang Ky Thanh Cong!", 400, 650, 20, GREEN);
    }
    if(GuiButton({400,700,200,30}, "Quay Lai")){
        ten[0] = sdt[0] = diaChi[0] = moTa[0] = '\0';
        hinhAnh = "";
        focusTen = focusSdt = focusDiaChi = focusMoTa = false;
        showMessage = false;
        chonHinhAnh = false;
        return SCREEN_USER;
    }

    return SCREEN_DANGKI;
}
ScreenState DrawScreenTimKiem(){
    ClearBackground(RAYWHITE);
    GuiSetStyle(DEFAULT, TEXT_SIZE, 20);

    float fontSize = 30;
    const char* title = "TIM KIEM PHONG TRO";
    int textWidth = MeasureText(title, fontSize);
    int textX = (1000 - textWidth) / 2;
    DrawText(title, textX, 40, fontSize, DARKBLUE);


    if(GuiButton({400,700,200,30}, "Quay Lai")){
        return SCREEN_USER;

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
        DrawText("Khong co chu tro nao cho duyet", 300, 200, 20, RED);
    }

    if (GuiButton({400, 700, 200, 30}, "Quay Lai"))
        return SCREEN_CHUTRO;

    return SCREEN_AD_DUYET;
}


ScreenState DrawScreenChiTiet(QuanLy<DangKi>& dsDangKi, HinhAnh& anh) {
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
    GuiLabel({200, 250, 400, 30}, ("Mo Ta: " + ct.getMoTa()).c_str());
    if (!ct.getHinhAnh().empty() && anh.has(ct.getHinhAnh())) {
        Texture2D tex = anh.get(ct.getHinhAnh());
        DrawTextureEx(tex, {600, 120}, 0, 0.35f, WHITE);
        GuiLabel({600, 90, 200, 25}, "Anh");
    }
    if (GuiButton({250, 600, 150, 50}, "DUYET")) {

        dk.setStatus(TrangThai::DA_DUYET);

        QuanLy<DangKi> dsDaDuyet;
        dsDaDuyet.docFile("quanlyct.txt");
        dsDaDuyet.them(dk);
        dsDaDuyet.luuFile("quanlyct.txt");
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

    // Nút quản lý phòng trọ
    if (GuiButton({350, 200, 300, 50}, "Quan Ly Phong Tro"))
    {
        return SCREEN_CHUTRO; 
    }

    // ⭐ NÚT DANH SÁCH CHỜ DUYỆT (đúng yêu cầu của bạn)
    if (GuiButton({350, 300, 300, 50}, "Danh Sach Cho Duyet"))
    {
        return SCREEN_AD_DUYET;
    }

    if (GuiButton({350, 500, 300, 50}, "Back"))
    {
        return SCREEN_ADMIN;
    }
    return SCREEN_CHUTRO;
}


int main(){
    InitWindow(ScreenWidth,ScreenHeigth,"PBL2");
    SetTargetFPS(60);
    adminTable.loadFromFile("admin.txt");
    userTable.loadFromFile("user.txt");
    ScreenState currentScreen = SCREEN_LOGIN;
    ScreenState nextScreen = SCREEN_LOGIN;
     

    static char adminName[64] = "";
    static char adminPass[64] = "";
    static char userName[64]  = "";
    static char userPass[64]  = "";
    QuanLy<DangKi> dsDangKi;
    HinhAnh hinhAnhManager;
    hinhAnhManager.loadAnh("hinhanh"); 

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
    if (nextScreen != SCREEN_ADMIN_LOGIN)
        currentScreen = nextScreen;

    if (currentScreen == SCREEN_ADMIN)
        SetWindowSize(1000, 800);
    break;

case SCREEN_USER_LOGIN:
    nextScreen = DrawScreenUserLogin(userName, userPass);
    if (nextScreen != SCREEN_USER_LOGIN)
        currentScreen = nextScreen;

    if (currentScreen == SCREEN_USER)
        SetWindowSize(1000, 800);
    break;

case SCREEN_ADMIN:
    nextScreen = DrawScreenAd();
    if (nextScreen != SCREEN_ADMIN)
        currentScreen = nextScreen;

    if (currentScreen == SCREEN_LOGIN)
        SetWindowSize(600, 400);
    break;

case SCREEN_USER:
    nextScreen = DrawScreenUser();
    if (nextScreen != SCREEN_USER)
        currentScreen = nextScreen;

    if (currentScreen == SCREEN_LOGIN)
        SetWindowSize(600, 400);
    break;

case SCREEN_DANGKI:
    nextScreen = DrawSCreenDK(dsDangKi, hinhAnhManager);
    if (nextScreen != SCREEN_DANGKI)
        currentScreen = nextScreen;
    break;

case SCREEN_TIMKIEM:
    nextScreen = DrawScreenTimKiem();
    if (nextScreen != SCREEN_TIMKIEM)
        currentScreen = nextScreen;
    break;

case SCREEN_CHITIET:
    nextScreen = DrawScreenChiTiet(dsDangKi, hinhAnhManager);
    if (nextScreen != SCREEN_CHITIET)
        currentScreen = nextScreen;
    break;

case SCREEN_CHUTRO:
    nextScreen = DrawScreenChuTro();
    if (nextScreen != SCREEN_CHUTRO)
        currentScreen = nextScreen;
    break;

case SCREEN_AD_DUYET:
    nextScreen = DrawScreenDanhSach(dsDangKi);
    if (nextScreen != SCREEN_AD_DUYET)
        currentScreen = nextScreen;
    break;
}

        EndDrawing();
    }
    CloseWindow();
    return 0;
}