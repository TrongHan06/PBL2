#include <raylib.h>
#define RAYGUI_IMPLEMENTATION
#include <raygui.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>  
#include <time.h>

#define MAX_INPUT_CHARS 20
#define MAX_MENH_GIA 4
#define MAX_LICH_SU 100
#define HASH_SIZE 100

typedef struct{
    char soTaiKhoan[64];
    char matKhau[64];
    char tenChuTK[128];
    char pin[5];
    float soDu;
}TaiKhoan;
 
typedef enum{
    SCREEN_LOGIN,
    SCREEN_MENU,
    SCREEN_CHECK_BALANCE,
    SCREEN_NAP_TIEN,
    SCREEN_RUT_TIEN,
    SCREEN_LICH_SU
}ScreenState;
typedef struct HashNode {
    TaiKhoan tk;
    struct HashNode* next;
} HashNode;
typedef struct {
    HashNode* buckets[HASH_SIZE];
} HashTable;
HashTable* initHashTable() {
    HashTable* table = (HashTable*)malloc(sizeof(HashTable));
    for (int i = 0; i < HASH_SIZE; i++) {
        table->buckets[i] = NULL;
    }
    return table;
}
typedef struct{
    int menhGia;
    int soTo;
}MenhGiaRut;
typedef struct{
    char loai[10]; // Nạp hoặc rút
    int soTien;
    char thoiGian[30]; 
}LichSu;
 typedef struct BSTNode {
    LichSu ls;
    struct BSTNode* left;
    struct BSTNode* right;
} BSTNode;

unsigned int hash(const char* key) {
    unsigned int hash = 0;
    while (*key) {
        hash = (hash * 31 + *key) % HASH_SIZE;
        key++;
    }
    return hash;
}
void insertHashTable(HashTable* table, TaiKhoan tk) {
    unsigned int index = hash(tk.soTaiKhoan);
    HashNode* node = table->buckets[index];
    while (node != NULL) {
        if (strcmp(node->tk.soTaiKhoan, tk.soTaiKhoan) == 0) {
            node->tk = tk;
            return;
        }
        node = node->next;
    }
    HashNode* newNode = (HashNode*)malloc(sizeof(HashNode));
    newNode->tk = tk;
    newNode->next = table->buckets[index];
    table->buckets[index] = newNode;
}void loadAccounts(HashTable* table) {
    FILE* file = fopen("account.txt", "r");
    if (!file) {
        perror("Khong the mo file account.txt");
        return;
    }
    
    char line[512];
    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\r\n")] = '\0';
        TaiKhoan tk;
        if (sscanf(line, "%s %s %127[^0-9] %f", tk.soTaiKhoan, tk.matKhau, tk.tenChuTK, &tk.soDu) == 4) {
            insertHashTable(table, tk);
        }
    }
    fclose(file);
}
void saveAccounts(HashTable* table) {
    FILE* file = fopen("account.txt", "w");
    if (!file) {
        perror("Khong the mo file account.txt de ghi");
        return;
    }
    
    for (int i = 0; i < HASH_SIZE; i++) {
        HashNode* node = table->buckets[i];
        while (node != NULL) {
            fprintf(file, "%s %s %s %.2f\n", node->tk.soTaiKhoan, node->tk.matKhau, node->tk.tenChuTK, node->tk.soDu);
            node = node->next;
        }
    }
    fclose(file);
}
bool findHashTable(HashTable* table, const char* soTaiKhoan, const char* matKhau, TaiKhoan* tkOut) {
    unsigned int index = hash(soTaiKhoan);
    HashNode* node = table->buckets[index];
    
    while (node != NULL) {
        if (strcmp(node->tk.soTaiKhoan, soTaiKhoan) == 0 && strcmp(node->tk.matKhau, matKhau) == 0) {
            *tkOut = node->tk;
            return true;
        }
        node = node->next;
    }
    return false;
}

bool ThongTin(const char* soTaiKhoan,const char *matKhau,TaiKhoan *tkOut,HashTable *table){
    return findHashTable(table,soTaiKhoan,matKhau,tkOut);
}
 void GhiTaiKhoan(TaiKhoan* tk,HashTable *table){
    insertHashTable(table,*tk);
    saveAccounts(table);
 }
void GhiLichSu(const char* soTaiKhoan, const char* loai, int soTien, const char* thoiGian);
char* ThoiGian();

int DrawScreenMenu(){
    
    ClearBackground(RAYWHITE);
    int screenWidth = GetScreenWidth();
    int screenHeigth = GetScreenHeight();

    int buttonWidth = 200;
    int buttonHeigth = 40;
    int spacing = 1;
    int totalHeigth = 5*buttonHeigth + 4*spacing;

    int centerX = (screenWidth - buttonWidth)/2;
    int startY = (screenHeigth - totalHeigth)/2;

    DrawText("MENU",screenWidth / 2 - MeasureText("MENU",30) / 2 ,30,30,DARKGREEN);
    
    Rectangle btnCheckBalance = {centerX, startY + 0*(buttonHeigth + spacing),buttonWidth,buttonHeigth};
    Rectangle btnWithdraw = {centerX, startY + 1*(buttonHeigth + spacing),buttonWidth,buttonHeigth};
    Rectangle btnDeposit = {centerX, startY + 2*(buttonHeigth + spacing),buttonWidth,buttonHeigth};
    Rectangle btnHistory = {centerX, startY + 3*(buttonHeigth + spacing),buttonWidth,buttonHeigth};
    Rectangle btnExit = {centerX, startY + 4*(buttonHeigth + spacing),buttonWidth,buttonHeigth};

    if(GuiButton(btnCheckBalance,"1.Kiem tra so du")) return 1;
    if(GuiButton(btnWithdraw,"2.Nap tien")) return 2;
    if(GuiButton(btnDeposit,"3.Rut tien")) return 3;
    if(GuiButton(btnHistory,"4.Lich su giao dich")) return 4;
    if(GuiButton(btnExit,"5.Thoat")) return 5;
    return 0;
}

void DrawScreenCheckBalance(TaiKhoan tK){
    int screenWidth = 800;
    ClearBackground(RAYWHITE);
    float fontSize = 30;
        const char *title = "THONG TIN TAI KHOAN";
        int textWidth = MeasureText(title, fontSize);
        int textX = (screenWidth - textWidth) / 2;
        DrawText(title, textX, 40, fontSize, DARKBLUE);
    char textName[128];
    sprintf(textName,"Ten: %s",tK.tenChuTK);
    DrawText(textName,250,120,24,BLACK);

    char textSoDu[128];
    sprintf(textSoDu,"So du: %.2f VND",tK.soDu);
    DrawText(textSoDu,250,160,24,BLUE);

}
void DrawScreenNapTien(TaiKhoan *tk, ScreenState *currentScreen,HashTable *table){
    static char inputAmount [20] = "0";
    static bool success = false;
    static char message[64] = "";
    static bool editMode = true;
    char inputNapTien[20] = "";
    
    ClearBackground(RAYWHITE);
        int screenWidth = 800;
        float fontSize = 30;
        const char *title = "NAP TIEN";
        int textWidth = MeasureText(title, fontSize);
        int textX = (screenWidth - textWidth) / 2;
    DrawText(title, textX, 40, fontSize, DARKBLUE);
        const char *title11 = "Nhap so tien can nap";
        int fontSize2 = 20;
        int textWidth22 = MeasureText(title11,fontSize2);
        int textX3 = (screenWidth - textWidth22)/2;
    
    DrawText(title11,textX3,120,20,BLACK);
    Rectangle inputBox = {300,150,200,30};
    Vector2 mouse = GetMousePosition();
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        if (CheckCollisionPointRec(mouse, inputBox)) {
            editMode = true;
        } else {
            editMode = false;
        }
    }
    
    if (editMode) {
        int key = GetCharPressed();
        while (key > 0) {
            if ((key >= '0' && key <= '9') && (strlen(inputAmount) < sizeof(inputAmount) - 1)) {
                inputAmount[strlen(inputAmount)] = (char)key;
                inputAmount[strlen(inputAmount)] = '\0';
            }
            key = GetCharPressed();
        }
        if (IsKeyPressed(KEY_BACKSPACE) && strlen(inputAmount) > 0) {
            inputAmount[strlen(inputAmount) - 1] = '\0';
        }
    }
    GuiTextBox(inputBox, inputAmount, sizeof(inputAmount), editMode);
    if(GuiButton((Rectangle){345,200,100,30},"XAC NHAN"))
    {
        int amount = atoi(inputAmount);
        if(amount > 0){
         snprintf(message,sizeof(message),"Da nap %d VND",amount);
          tk->soDu += amount;
         success = true;
         GhiTaiKhoan(tk,table);    
         GhiLichSu(tk->soTaiKhoan,"Nap",amount,ThoiGian());
         FILE *file = fopen("account.txt","r");
         FILE *temp = fopen("temp.txt","w");
         inputNapTien[0] ='\0';
         if(file && temp){
            char buffer[512];
            while(fgets(buffer,sizeof(buffer),file)){
                char user[64],pass[64],name[128];
                float balance;
                if(sscanf(buffer,"%s %s %[^\n] %f",user,pass,name,&balance)==4){
                    if(strcmp(user,tk->soTaiKhoan)==0){
                        fprintf(temp,"%s %s %s %.2f\n",user,pass,name,tk->soDu);
                    }else{
                        fputs(buffer,temp);
                    }
                }else{
                    fputs(buffer,temp);
                }

            }
            fclose(file);
            fclose(temp);
            remove("account.txt");
            rename("temp.txt","account.txt");
         }   
        }else{
            snprintf(message,sizeof(message),"So tien khong hop le.Xin vui long thu lai");
            success = false;

        }
        
    }
    if(strlen(message)>0){
            float screenWidth = 800;
            float fontSizeMes = 20;
            float textWidth = MeasureText(message,fontSizeMes);
            float textX = (screenWidth - textWidth)/2;

            DrawText(message,textX,250,fontSizeMes,success?GREEN:RED);

        }
    if(GuiButton((Rectangle){345,400,100,30},"QUAY LAI MENU")){
        *currentScreen = SCREEN_MENU;
        strcpy(inputAmount,"0");
        message[0] = '\0';
        success = false ;
    }
}
bool RutTien(int soTien,MenhGiaRut ketQuaRut[MAX_MENH_GIA]){
    if(soTien < 50000 || soTien % 50000 != 0) 
    return false;
    int menhGia[] ={500000,200000,100000,50000};
    for(int i=0;i<MAX_MENH_GIA;i++){
            ketQuaRut[i].menhGia = menhGia[i];
            ketQuaRut[i].soTo = soTien/menhGia[i];
            soTien %= menhGia[i];
    }
    return true;
}
void DrawScreenRutTien(TaiKhoan *tkHienTai,ScreenState *currentScreen,HashTable *table){
     int screenWidth = 800;
     char inputRutTien[20]="";
    ClearBackground(RAYWHITE);
    float fontSize = 30;
         const char *title = "RUT TIEN";
         float fontSize11 = 20;
         const char *title1 = "Nhap so tien muon rut. (Luu y: >= 50000 VND va la boi so cua 50000 VND)";
        int textWidth = MeasureText(title, fontSize);
        int textWidth1 = MeasureText(title1,fontSize11);
        int textX = (screenWidth - textWidth) / 2;
        int textX1 = (screenWidth - textWidth1) / 2;
        DrawText(title, textX, 40, fontSize, DARKBLUE);
    static char soTienInput[20] = "";
    static bool daRut = false;
    static MenhGiaRut ketQuaRut[MAX_MENH_GIA];
    static char thongBao[100] = "";
    static bool editMode = false;
        Rectangle inputBox = {300,150,200,30};
        DrawText(title1, textX1, 80, fontSize11, BLACK);

Vector2 mouse = GetMousePosition();
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        if (CheckCollisionPointRec(mouse, inputBox)) {
            editMode = true;
        } else {
            editMode = false;
        }
    }
    
    if (editMode) {
        int key = GetCharPressed();
        while (key > 0) {
            if ((key >= '0' && key <= '9') && (strlen(soTienInput) < sizeof(soTienInput) - 1)) {
                soTienInput[strlen(soTienInput)] = (char)key;
                soTienInput[strlen(soTienInput)] = '\0';
            }
            key = GetCharPressed();
        }
        if (IsKeyPressed(KEY_BACKSPACE) && strlen(soTienInput) > 0) {
            soTienInput[strlen(soTienInput) - 1] = '\0';
        }
    }
    GuiTextBox(inputBox, soTienInput, sizeof(soTienInput), editMode);

        static Color mauThongBao = RED;
    if(GuiButton((Rectangle){350,200,100,30},"RUT")){
        int  soTien = atoi(soTienInput);
        if(RutTien(soTien,ketQuaRut)){
            if(soTien <=  tkHienTai->soDu){
                tkHienTai->soDu -= soTien;
                daRut = true;
                GhiTaiKhoan(tkHienTai,table);
                GhiLichSu(tkHienTai->soTaiKhoan,"Rut",soTien,ThoiGian());
                sprintf(thongBao,"Rut thanh cong %d VND",soTien);
                 mauThongBao = GREEN;
                 inputRutTien[0] = '\0';
            } else {
                sprintf(thongBao,"Khong du so du");
                daRut = false;
                mauThongBao = RED;
          }  }else{
                sprintf(thongBao,"So tien khong hop le");
                daRut = false;
                mauThongBao = RED;
            }
     
    }  
            float fontSizeTB = 24;
            float textWidthTB = MeasureText(thongBao,fontSizeTB);
            float textXTB = (screenWidth - textWidthTB)/2;  
            DrawText(thongBao,textXTB,250,fontSizeTB,mauThongBao);    
    if(daRut){
        int y = 300;
        for(int i =0;i<MAX_MENH_GIA;i++){
            if(ketQuaRut[i].soTo > 0)
            {
                char text[100];
                sprintf(text,"%d VND x %d",ketQuaRut[i].menhGia,ketQuaRut[i].soTo);
                float fontSizeMG = 20;
                float textWidthMG = MeasureText(text,fontSizeTB);
                float textXMG = (screenWidth - textWidthMG)/2; 
                DrawText(text,textXMG,y,20,DARKGREEN);
                y+=30;
            }
        }
    }
    if(GuiButton((Rectangle){345,400,100,30},"QUAY LAI MENU")){
        *currentScreen = SCREEN_MENU;
        strcpy(soTienInput,"");
        daRut = false;
        strcpy(thongBao,"");
    }

}
BSTNode* createBSTNode(LichSu ls) {
    BSTNode* node = (BSTNode*)malloc(sizeof(BSTNode));
    node->ls = ls;
    node->left = node->right = NULL;
    return node;
}
BSTNode* insertBST(BSTNode* root, LichSu ls) {
    if (root == NULL) return createBSTNode(ls);
    
    if (strcmp(ls.thoiGian, root->ls.thoiGian) < 0) {
        root->left = insertBST(root->left, ls);
    } else {
        root->right = insertBST(root->right, ls);
    }
    return root;
}

void HienLichSu(BSTNode* root, float screenWidth, float textXL, int* y) {
    if (root == NULL) return;
    
    HienLichSu(root->left, screenWidth, textXL, y);
    if (*y < 430) { // Giới hạn hiển thị để không vượt màn hình
        DrawText(root->ls.loai, textXL - 300, *y, 18, DARKGRAY);
        char soTienText[20];
        sprintf(soTienText, "%d", root->ls.soTien);
        DrawText(soTienText, textXL, *y, 18, DARKGRAY);
        DrawText(root->ls.thoiGian, textXL + 300, *y, 18, DARKGRAY);
        *y += 30;
    }
    HienLichSu(root->right, screenWidth, textXL, y);
}
BSTNode* loadLichSuFromFile(const char* soTaiKhoan) {
    BSTNode* root = NULL;
    FILE* file = fopen("lichsu.txt", "r");
    if (!file) return NULL;
    
    char line[128];
    while (fgets(line, sizeof(line), file)) {
        char stk[20], loai[10], thoiGian[30];
        int soTien;
        if (sscanf(line, "%[^|]|%[^|]|%d|%[^\n]", stk, loai, &soTien, thoiGian) == 4) {
            if (strcmp(stk, soTaiKhoan) == 0) {
                LichSu ls;
                strcpy(ls.loai, loai);
                ls.soTien = soTien;
                strcpy(ls.thoiGian, thoiGian);
                root = insertBST(root, ls);
            }
        }
    }
    fclose(file);
    return root;
}
LichSu lichSu[MAX_LICH_SU];
int soLuongLichSu = 0;
void GhiLichSu(const char* soTaiKhoan,const char* loai,int soTien,const char* thoiGian){
    FILE* file = fopen("lichsu.txt","a");
    if(!file) return;
    fprintf(file,"%s|%s|%d|%s\n",soTaiKhoan,loai,soTien,thoiGian);
    fclose(file);
}
char* ThoiGian(){
   static char buffer[30];
    time_t t = time(NULL);
    struct tm* tm = localtime(&t);
    sprintf(buffer, "%02d-%02d-%d %02d:%02d", tm->tm_mday, tm->tm_mon + 1, tm->tm_year + 1900, tm->tm_hour, tm->tm_min);
    return buffer;
}
void DrawScreenLichSu(ScreenState *currentScreen,const char *soTaiKhoan){
    ClearBackground(RAYWHITE);
    BSTNode* root = loadLichSuFromFile(soTaiKhoan);
    int y = 130;
     const float screenWidth = 800;
     const char *title = "LICH SU GIAO DICH";
     float fontSizeHis = 30;
     float textWidthHis = MeasureText(title,fontSizeHis);
     float textXHis = (screenWidth - textWidthHis)/2;
     DrawText(title,textXHis,40,fontSizeHis,DARKBLUE);
     const char *titleL = "So tien";
     float fontSizeL = 20;
     float textWidthL = MeasureText(titleL,fontSizeL);
     float textXL = (screenWidth - textWidthL)/2;
     DrawText(titleL,textXL,100,fontSizeL,BLACK);
     DrawText("Loai",textXL-300,100,20,BLACK);
     DrawText("Thoi Gian",textXL+300,100,20,BLACK);
        HienLichSu(root, screenWidth, textXL, &y);

       Rectangle btnBack = {300,400,200,24};
       if(GuiButton(btnBack,"QUAY LAI MENU")){
        *currentScreen = SCREEN_MENU;
       }
}
typedef struct {
    char items[MAX_INPUT_CHARS];
    int top;
} Stack;

void initStack(Stack* s) {
    s->top = -1;
}
bool isStackEmpty(Stack* s) {
    return s->top == -1;
}
bool isStackFull(Stack* s) {
    return s->top == MAX_INPUT_CHARS - 1;
}
void push(Stack* s, char c) {
    if (!isStackFull(s)) {
        s->items[++(s->top)] = c;
    }
}

// Pop ký tự từ stack
char pop(Stack* s) {
    if (!isStackEmpty(s)) {
        return s->items[(s->top)--];
    }
    return '\0';
}
int stackSize(Stack* s) {
    return s->top + 1;
}
void stackToString(Stack* s, char* output) {
    for (int i = 0; i <= s->top; i++) {
        output[i] = s->items[i];
    }
    output[s->top + 1] = '\0';
}

int main(){
    const int screenWidth = 800;
    const int screenHeigth = 450;
    HashTable *table = initHashTable();
    loadAccounts(table);

     float fontSize = 30;
      float spacing = 1;
     TaiKhoan tkHienTai;

    ScreenState currentScreen = SCREEN_LOGIN;

    InitWindow(screenWidth,screenHeigth,"ATM-Dang Nhap");
    
    char accountNumber[MAX_INPUT_CHARS + 1 ] = "\0";
    Stack passwordStack;
    initStack(&passwordStack);

    bool loginSuccess = false;
    bool loginTried = false;
    
    Rectangle accountBox = {screenWidth / 2 - 100,120,200,40};
    Rectangle passwordBox = {screenWidth / 2 - 100,180,200,40};
    Rectangle loginButton = {screenWidth / 2 - 50,250,100,40};

    bool accountEditMode = false;
    bool passwordEditMode = false;
    
    SetTargetFPS(60);

    while(!WindowShouldClose()){
        BeginDrawing();
    switch(currentScreen){
        case SCREEN_LOGIN:
        ClearBackground(RAYWHITE);
            
         Vector2 mouse = GetMousePosition();
         if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            if(CheckCollisionPointRec(mouse,accountBox)){
                accountEditMode = true;
                passwordEditMode = false;
            }else if(CheckCollisionPointRec(mouse,passwordBox)){
                accountEditMode = false;
                passwordEditMode = true;
            }else{
            accountEditMode = false;
            passwordEditMode = false;
            }
            
         }
         if (accountEditMode) {
                    int key = GetCharPressed();
                    while (key > 0) {
                        if ((key >= '0' && key <= '9') && (strlen(accountNumber) < MAX_INPUT_CHARS)) {
                            accountNumber[strlen(accountNumber)] = (char)key;
                            accountNumber[strlen(accountNumber)] = '\0';
                        }
                        key = GetCharPressed();
                    }
                    if (IsKeyPressed(KEY_BACKSPACE) && strlen(accountNumber) > 0) {
                        accountNumber[strlen(accountNumber) - 1] = '\0';
                    }
                }
                GuiTextBox(accountBox, accountNumber, MAX_INPUT_CHARS + 1, accountEditMode);
                accountNumber[strcspn(accountNumber, "\r\n")] = '\0';
        char display[MAX_INPUT_CHARS + 1] = "\0";
       
                for (int i = 0; i < stackSize(&passwordStack); i++) {
                    display[i] = '*';
                }
                if (passwordEditMode) {
                    int key = GetCharPressed();
                    while (key > 0) {
                        if ((key >= 32) && (key <= 255) && !isStackFull(&passwordStack)) {
                            push(&passwordStack, (char)key);
                        }
                        key = GetCharPressed();
                    }
                    if (IsKeyPressed(KEY_BACKSPACE) && !isStackEmpty(&passwordStack)) {
                        pop(&passwordStack);
                    }
                }
        GuiTextBox(passwordBox, display, MAX_INPUT_CHARS + 1, passwordEditMode);
        char password[MAX_INPUT_CHARS +1] = "\0";
        stackToString(&passwordStack, password);
        if(GuiButton(loginButton,"Dang nhap")){
            loginTried = true;
            loginSuccess = ThongTin(accountNumber,password,&tkHienTai,table);
        if(loginSuccess){

            currentScreen = SCREEN_MENU;
            initStack(&passwordStack);
        }
        }
        float fontSize = 30;
        const char *title = "ATM - DANG NHAP";
        int textWidth = MeasureText(title, fontSize);
        int textX = (screenWidth - textWidth) / 2;
        DrawText(title, textX, 40, fontSize, DARKBLUE);

    int labelWidth1 = MeasureText("Mat Khau",15);
    int labelWidth2 = MeasureText("So Tai Khoan",15);

    DrawText("So Tai Khoan:",accountBox.x - labelWidth1 - 70,accountBox.y + (passwordBox.height -15)/2,15,BLACK);
    DrawText("Mat khau:",passwordBox.x - labelWidth2 - 10,passwordBox.y + (passwordBox.height -15)/2,15,BLACK);

        if(loginTried){
            char *title = "Sai So Tai Khoan Hoac Mat Khau";
            float fontSize = 20;
            float textWidth = MeasureText(title,fontSize);
            float textX = (screenWidth - textWidth)/2;
    if(loginSuccess){
        DrawText("Dang Nhap Thanh Cong",screenWidth / 2 - 100,320,20,GREEN);
    }else{
        DrawText(title,textX,320,fontSize,RED);
    }
    }
     break;
    case SCREEN_MENU:{
    int selected = DrawScreenMenu();
        switch(selected){
        case 1:
        currentScreen = SCREEN_CHECK_BALANCE;
        break;
        case 2:
        currentScreen = SCREEN_NAP_TIEN;
        break;
        case 3: 
        currentScreen = SCREEN_RUT_TIEN;
        break;   
        case 4:
        currentScreen = SCREEN_LICH_SU;
        break;
        case 5:
        GhiTaiKhoan(&tkHienTai,table);
        CloseWindow();   
        break;
    }
    break;
    }
    case SCREEN_CHECK_BALANCE:
      DrawScreenCheckBalance(tkHienTai);
            Rectangle btnBack = {300,400,200,40};
            if(GuiButton(btnBack,"QUAY LAI MENU")){
                currentScreen = SCREEN_MENU;
            }
            break;
    case SCREEN_NAP_TIEN:
    DrawScreenNapTien(&tkHienTai,&currentScreen,table);
    break;
    case SCREEN_RUT_TIEN:
    DrawScreenRutTien(&tkHienTai,&currentScreen,table);
    break;
    case SCREEN_LICH_SU:
    DrawScreenLichSu(&currentScreen,tkHienTai.soTaiKhoan);
    break;
}
EndDrawing();

    }
         
CloseWindow();
return 0;
}


