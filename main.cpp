#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include "TaiKhoan.h"
HashTable<TaiKhoan> adminTable; 
HashTable<TaiKhoan> userTable; 

#define MAX_INPUT_CHARS 20

 float ScreenWidth = 600;
 float ScreenHeigth = 400;
typedef enum{
    SCREEN_LOGIN,
    SCREEN_ADMIN_LOGIN,
    SCREEN_USER_LOGIN
}ScreenState;
ScreenState DrawScreenLogin(){
   
    ClearBackground(RAYWHITE);
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
      Color colorMessage = RED;
       if(GuiButton(btnBack,"QUAY LAI MENU")){
        return SCREEN_LOGIN;
       }
       if (GuiButton(loginButton, "Dang nhap")) {
    TaiKhoan* tk = userTable.find(userName, userPass);

    if (tk) {
      loginMessage = "Dang nhap thanh cong!";
      colorMessage = GREEN;
      
    } else {
        loginMessage = "Sai tai khoan hoac mat khau!";
        colorMessage = RED;
    }
}
 if(!loginMessage.empty()){
    DrawText(loginMessage.c_str(),180,300,20,colorMessage);
 }
       return SCREEN_USER_LOGIN;

}


int main(){
    InitWindow(ScreenWidth,ScreenHeigth,"PBL2");
    SetTargetFPS(60);
    adminTable.loadFromFile("admin.txt");
    userTable.loadFromFile("user.txt");
    ScreenState currentScreen = SCREEN_LOGIN;
     

    static char adminName[64] = "";
    static char adminPass[64] = "";
    static char userName[64]  = "";
    static char userPass[64]  = "";

    while(!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(RAYWHITE);
        switch (currentScreen)
        {
        case SCREEN_LOGIN:
          currentScreen = DrawScreenLogin();
                   break;
        case SCREEN_ADMIN_LOGIN:
            currentScreen = DrawScreenADLogin(adminName,adminPass);
            break;
         case SCREEN_USER_LOGIN:
            currentScreen = DrawScreenUserLogin(userName,userPass);
            break;

        }
        
        EndDrawing();
    }
    CloseWindow();
    return 0;
}