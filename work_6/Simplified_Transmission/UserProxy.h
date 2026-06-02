#pragma once
#include "EncryptStrategy.h"
#include "VerificationStrategy.h"
#include <string>
#include <iostream>

class UserProxy{
    EncryptStrategy* encrypt;
    VerificationStrategy* verification;
    RealUser* us;
public:
    UserProxy(RealUser* user, EncryptStrategy* en, VerificationStrategy* ve): encrypt(en), verification(ve), us(user) {}
    void sendMessage(std::string message)
    {
        std::string temp;
        temp = encrypt -> encode(message);
        std::string ve_string;
        ve_string = verification->verify(message);
        us -> sendMessage(temp);
        std::cout << ve_string << std::endl;
    }
};