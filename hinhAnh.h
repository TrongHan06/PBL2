#ifndef HINHANH_H
#define HINHANH_H

#include "raylib.h"
#include <string>
#include <unordered_map>
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

class HinhAnh{
    private:
    std::unordered_map<std::string,Texture2D> anh;
    public:
    
    void loadAnh(const std::string& folder){
        for(const auto& a : fs::directory_iterator(folder)){
            if(a.is_regular_file()){
                std::string path = a.path().string();
                std::string name = a.path().filename().string();

                Texture2D tex = LoadTexture(path.c_str());
                if(tex.id != 0){
                    anh[name] = tex;
                    
                }else {
                    std::cout << " that bai: " << name << std::endl;

                }
            }
        }
    }
    Texture2D get(const std::string& name)
{
    if(anh.find(name) != anh.end()){
        return anh[name];
    }
    return{0};
}
const std::unordered_map<std::string, Texture2D>& getAll() const {
        return anh;
    }
void unloadAnh(){
    for(auto& huya : anh){
        UnloadTexture(huya.second);
    }
    anh.clear();
}
bool has(const std::string& name ){
    return anh.find(name) != anh.end();
}
};
#endif