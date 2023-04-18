#include "common.h"

#include "desfun.h"

#include <sstream>

using namespace std;


string StringToHex(const std::string& data)
{
    const std::string hex = "0123456789ABCDEF";
    std::stringstream ss;

    for (std::string::size_type i = 0; i < data.size(); ++i)
        ss << hex[(unsigned char)data[i] >> 4] << hex[(unsigned char)data[i] & 0xf];
    std::cout << ss.str() << std::endl;
    return ss.str();
}

void DES_test() {
    //string str = ui->lineEdit_8->text().toStdString();
    //string str1 = ui->lineEdit_20->text().toStdString();
    //string strkey = ui->lineEdit_9->text().toStdString();
    //QString choice = ui->comboBox_4->currentText();
    //QString result1, result2;
    string answer1, answer2;
    string line;
    //string mmw;
    const char* key = /*strkey.c_str()*/"iVBORw0KGgoAAAANSUhEUgAAAMYAAAB5CAZ";
    cout << key << endl;
    enum { ENCRYPT, DECRYPT };
    char encrypt_text[255];                       // 密文
    char decrypt_text[255];                       // 解密文
    memset(encrypt_text, 0, sizeof(encrypt_text));//memset(a,b,c)函数,在a的地址开始到c的长度的字节都初始化为b
    memset(decrypt_text, 0, sizeof(decrypt_text));
    DESFUN des;
    if (/*choice == "加密"*/1) {
        //ifstream in(str);
        //if (in) // 有该文件
        //{
        //    while (getline(in, line)) // line中不包括每行的换行符
        //    {
        //        mmw += line;
        //    }
        //}
        //else // 没有该文件
        //{
        //    cout << "no such file" << endl;
        //}
        //cout << mmw << endl;
        const char* plain = /*mmw.c_str()*/"123456a";
        char* plain_text = new char[100];
        int i = strlen(plain);
        strcpy_s(plain_text, strlen(plain_text), plain);
        cout << plain_text << "##" << endl;
        des.DES_Act(encrypt_text, plain_text, sizeof(plain_text), key, sizeof(key), ENCRYPT);
        answer1 = encrypt_text;
        //result1 = QString::fromLocal8Bit(answer1.data());
        cout << encrypt_text << "EN" << endl;

        string out = StringToHex(encrypt_text);

        //cout << "output: " << out << endl;

        //ofstream out(str1);
        //if (out) // 有该文件
        //{
        //    out << answer1;
        //}
        //else // 没有该文件
        //{
        //    cout << "no such file" << endl;
        //}
        //ui->textEdit_7->setText("加密结果:" + result1);
    }
}