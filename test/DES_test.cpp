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
    char encrypt_text[255];                       // ����
    char decrypt_text[255];                       // ������
    memset(encrypt_text, 0, sizeof(encrypt_text));//memset(a,b,c)����,��a�ĵ�ַ��ʼ��c�ĳ��ȵ��ֽڶ���ʼ��Ϊb
    memset(decrypt_text, 0, sizeof(decrypt_text));
    DESFUN des;
    if (/*choice == "����"*/1) {
        //ifstream in(str);
        //if (in) // �и��ļ�
        //{
        //    while (getline(in, line)) // line�в�����ÿ�еĻ��з�
        //    {
        //        mmw += line;
        //    }
        //}
        //else // û�и��ļ�
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
        //if (out) // �и��ļ�
        //{
        //    out << answer1;
        //}
        //else // û�и��ļ�
        //{
        //    cout << "no such file" << endl;
        //}
        //ui->textEdit_7->setText("���ܽ��:" + result1);
    }
}