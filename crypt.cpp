#include "crypt.h"

crypt::crypt()
{
    Botan::InitializationVector init;
}

std::string crypt::myCrypt(std::string text, std::string log, std::string pas, bool mode)
{
    Botan::AutoSeeded_RNG rng;
    Botan::SymmetricKey key (log+pas);
    Botan::InitializationVector iv ("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"); //initialis_vector must be 16*aa
    if(mode==true){
        Botan::Pipe pipe(Botan::get_cipher("AES-128/CBC",key,iv,Botan::ENCRYPTION),new Botan::Hex_Encoder);
        pipe.process_msg(text);
        std::string str = pipe.read_all_as_string(0);
        return str.data();
    }
    else{

        Botan::Pipe pipe1(new Botan::Hex_Decoder,Botan::get_cipher("AES-128/CBC",key,iv,Botan::DECRYPTION));
        pipe1.process_msg(text);
        std::string str1 = pipe1.read_all_as_string(0);
        return str1.data();
    }

}

std::string crypt::genKey(QString str)
{
    int len = str.size();
    QString str_copy = str;
    for(int i = len; i < 16; ++i){
        str_copy += "0";
    }
    qDebug() << str_copy.length();
    return str_copy.toStdString();
}



