#include "Singleton.h"

Singleton *Singleton::s_pInstance = nullptr;

void Singleton::Create(){
    qDebug("okokokok");
    if(!s_pInstance){
        s_pInstance = new Singleton;
    }
}

Singleton *Singleton::getInstance(){
    if(!s_pInstance){
        s_pInstance = new Singleton;
    }
    return s_pInstance;
}

void Singleton::Destroy(){
    delete s_pInstance;
    s_pInstance = nullptr;
}
