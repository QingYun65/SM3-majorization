#include <iostream>
#include <string>
#include <cmath>
#include <time.h>
#include <random>
#include <stdlib.h>
using namespace std;


string t_i[64];
//������ת��Ϊʮ�����ƺ���ʵ��
string BinToHex(string str) {
	string hex = "";//�����洢������ɵ�ʮ��������
	int temp = 0;//�����洢ÿ����λ����������ʮ����ֵ
	while (str.size() % 4 != 0) {//��Ϊÿ��λ�����������ܹ���Ϊһ��ʮ�������������Խ�������������ת��Ϊ4�ı���
		str = "0" + str;//���λ��0ֱ������Ϊ4�ı�������
	}
	for (int i = 0; i < str.size(); i += 4) {
		temp = (str[i] - '0') * 8 + (str[i + 1] - '0') * 4 + (str[i + 2] - '0') * 2 + (str[i + 3] - '0') * 1;//�жϳ�4λ����������ʮ���ƴ�СΪ����
		if (temp < 10) {//���õ���ֵС��10ʱ������ֱ����0-9������
			hex += to_string(temp);
		}
		else {//���õ���ֵ����10ʱ����Ҫ����A-F��ת��
			hex += 'A' + (temp - 10);
		}
	}
	return hex;
}

//ʮ������ת��Ϊ�����ƺ���ʵ��
string HexToBin(string str) {
	string bin = "";
	string table[16] = { "0000","0001","0010","0011","0100","0101","0110","0111","1000","1001","1010","1011","1100","1101","1110","1111" };
	for (int i = 0; i < str.size(); i++) {
		if (str[i] >= 'A' && str[i] <= 'F') {
			bin += table[str[i] - 'A' + 10];
		}
		else {
			bin += table[str[i] - '0'];
		}
	}
	return bin;
}

//������ת��Ϊʮ���Ƶĺ���ʵ��
int BinToDec(string str) {
	int dec = 0;
	for (int i = 0; i < str.size(); i++) {
		dec += (str[i] - '0') * pow(2, str.size() - i - 1);
	}
	return dec;
}

//ʮ����ת��Ϊ�����Ƶĺ���ʵ��
string DecToBin(int str) {
	string bin = "";
	while (str >= 1) {
		bin = to_string(str % 2) + bin;
		str = str / 2;
	}
	return bin;
}

//ʮ������ת��Ϊʮ���Ƶĺ���ʵ��
int HexToDec(string str) {
	int dec = 0;
	for (int i = 0; i < str.size(); i++) {
		if (str[i] >= 'A' && str[i] <= 'F') {
			dec += (str[i] - 'A' + 10) * pow(16, str.size() - i - 1);
		}
		else {
			dec += (str[i] - '0') * pow(16, str.size() - i - 1);
		}
	}
	return dec;
}

//ʮ����ת��Ϊʮ�����Ƶĺ���ʵ��
string DecToHex(int str) {
	string hex = "";
	int temp = 0;
	while (str >= 1) {
		temp = str % 16;
		if (temp < 10 && temp >= 0) {
			hex = to_string(temp) + hex;
		}
		else {
			hex += ('A' + (temp - 10));
		}
		str = str / 16;
	}
	return hex;
}

string padding(string str) {//�����ݽ������ 
	string res = "";
	for (int i = 0; i < str.size(); i++) {//���Ƚ�����ֵת��Ϊ16�����ַ���
		res += DecToHex((int)str[i]);
	}
	/*
	cout << "�����ַ�����ASCII���ʾΪ��" << endl;
	for (int i = 0; i < res.size(); i++) {
		cout << res[i];
		if ((i + 1) % 8 == 0) {
			cout << "  ";
		}
		if ((i + 1) % 64 == 0 || (i + 1) == res.size()) {
			cout << endl;
		}
	}
	cout << endl;
	*/
	int res_length = res.size() * 4;//��¼�ĳ���Ϊ2�����µĳ���
	res += "8";//�ڻ�õ����ݺ�����1����16�������൱�������8
	while (res.size() % 128 != 112) {
		res += "0";//��0���������
	}
	string res_len = DecToHex(res_length);//���ڼ�¼���ݳ��ȵ��ַ���
	while (res_len.size() != 16) {
		res_len = "0" + res_len;
	}
	res += res_len;
	return res;
}

string LeftShift(string str, int len) {//ʵ��ѭ������lenλ����
	string res = HexToBin(str);
	res = res.substr(len) + res.substr(0, len);
	return BinToHex(res);
}

string XOR(string str1, string str2) {//ʵ��������
	string res1 = HexToBin(str1);
	string res2 = HexToBin(str2);
	string res = "";
	for (int i = 0; i < res1.size(); i++) {
		if (res1[i] == res2[i]) {
			res += "0";
		}
		else {
			res += "1";
		}
	}
	return BinToHex(res);
}

string AND(string str1, string str2) {//ʵ�������
	string res1 = HexToBin(str1);
	string res2 = HexToBin(str2);
	string res = "";
	for (int i = 0; i < res1.size(); i++) {
		if (res1[i] == '1' && res2[i] == '1') {
			res += "1";
		}
		else {
			res += "0";
		}
	}
	return BinToHex(res);
}

string OR(string str1, string str2) {//ʵ�ֻ����
	string res1 = HexToBin(str1);
	string res2 = HexToBin(str2);
	string res = "";
	for (int i = 0; i < res1.size(); i++) {
		if (res1[i] == '0' && res2[i] == '0') {
			res += "0";
		}
		else {
			res += "1";
		}
	}
	return BinToHex(res);
}

string NOT(string str) {//ʵ�ַǲ���
	string res1 = HexToBin(str);
	string res = "";
	for (int i = 0; i < res1.size(); i++) {
		if (res1[i] == '0') {
			res += "1";
		}
		else {
			res += "0";
		}
	}
	return BinToHex(res);
}

char binXor(char str1, char str2) {//ʵ�ֵ����ص�������
	return str1 == str2 ? '0' : '1';
}

char binAnd(char str1, char str2) {//ʵ�ֵ����ص������
	return (str1 == '1' && str2 == '1') ? '1' : '0';
}

string ModAdd(string str1, string str2) {//mod 2^32����ĺ���ʵ��
	string res1 = HexToBin(str1);
	string res2 = HexToBin(str2);
	char temp = '0';
	string res = "";
	for (int i = res1.size() - 1; i >= 0; i--) {
		res = binXor(binXor(res1[i], res2[i]), temp) + res;
		if (binAnd(res1[i], res2[i]) == '1') {
			temp = '1';
		}
		else {
			if (binXor(res1[i], res2[i]) == '1') {
				temp = binAnd('1', temp);
			}
			else {
				temp = '0';
			}
		}
	}
	return BinToHex(res);
}

string P1(string str) {//ʵ���û�����P1��X��
	return XOR(XOR(str, LeftShift(str, 15)), LeftShift(str, 23));
}

string P0(string str) {//ʵ���û�����P0��X��
	return XOR(XOR(str, LeftShift(str, 9)), LeftShift(str, 17));
}

string T(int j) {//����Tj����ֵ�ĺ���ʵ��
	if (0 <= j && j <= 15) {
		return "79CC4519";
	}
	else {
		return "7A879D8A";
	}
}

string FF(string str1, string str2, string str3, int j) {//ʵ�ֲ�������FF����
	if (0 <= j && j <= 15) {
		return XOR(XOR(str1, str2), str3);
	}
	else {
		return OR(OR(AND(str1, str2), AND(str1, str3)), AND(str2, str3));
	}
}

string GG(string str1, string str2, string str3, int j) {//ʵ�ֲ�������GG����
	if (0 <= j && j <= 15) {
		return XOR(XOR(str1, str2), str3);
	}
	else {
		return OR(AND(str1, str2), AND(NOT(str1), str3));
	}
}


void OneRound(string BB, int i, string& A, string& B, string& C, string& D, string& E, string& F, string& G, string& H, string(&W)[68]) {
	if (i < 12) {
		W[i + 4] = BB.substr((i + 4) * 8, 8);
	}
	else {
		W[i + 4] = XOR(XOR(P1(XOR(XOR(W[i - 12], W[i - 5]), LeftShift(W[i + 1], 15))), LeftShift(W[i - 9], 7)), W[i - 2]);
	}
	string TT1 = "", TT2 = "";
	TT2 = LeftShift(A, 12);
	TT1 = ModAdd(ModAdd(TT2, E), t_i[i]);
	TT1 = LeftShift(TT1, 7);
	TT2 = XOR(TT2, TT1);
	D = ModAdd(ModAdd(ModAdd(D, FF(A, B, C, i)), TT2), XOR(W[i], W[i + 4]));
	H = ModAdd(ModAdd(ModAdd(H, GG(E, F, G, i)), TT1), W[i]);
	B = LeftShift(B, 9);
	F = LeftShift(F, 19);
	H = P0(H);
}

string ProcessBlock(string str) {
	int num = str.size() / 128;
	//cout << "��Ϣ�������֮���� " + to_string(num) + " ����Ϣ���顣" << endl;
	//cout << endl;
	string V = "7380166F4914B2B9172442D7DA8A0600A96F30BC163138AAE38DEE4DB0FB0E4E";
	string BB = "";
	string W[68];
	for (int i = 0; i < num; i++) {
		//cout << "�� " << to_string(i + 1) << " ����Ϣ���飺" << endl;
		//cout << endl;
		BB = str.substr(i * 128, 128);
		W[0] = BB.substr(0, 8), W[1] = BB.substr(8, 8), W[2] = BB.substr(16, 8), W[3] = BB.substr(24, 8);
		string A = V.substr(0, 8), B = V.substr(8, 8), C = V.substr(16, 8), D = V.substr(24, 8), E = V.substr(32, 8), F = V.substr(40, 8), G = V.substr(48, 8), H = V.substr(56, 8);
		for (int i = 0; i <= 60;) {
			OneRound(BB, i + 0, A, B, C, D, E, F, G, H, W);
			OneRound(BB, i + 1, D, A, B, C, H, E, F, G, W);
			OneRound(BB, i + 2, C, D, A, B, G, H, E, F, W);
			OneRound(BB, i + 3, B, C, D, A, F, G, H, E, W);
			i = i + 4;
		}
		//for (int i = 0; i < 68; i++) {
			//cout << "W_" << i << "\t" << W[i] << endl;
		//}
		V = XOR(V, A+B+C+D+E+F+G+H);
	}
	return V;
}



string rand_str(const int len)  /*����Ϊ�ַ����ĳ���*/
{
	/*��ʼ��*/
	string str;                 /*����������������ַ�����str*/
	char c;                     /*�����ַ�c����������������ɵ��ַ�*/
	int idx;                    /*����ѭ���ı���*/
	/*ѭ�����ַ��������������ɵ��ַ�*/
	for (idx = 0; idx < len; idx++)
	{
		/*rand()%26��ȡ�࣬����Ϊ0~25����'a',������ĸa~z,���asc���*/
		c = 'a' + rand() % 26;
		str.push_back(c);       /*push_back()��string��β�庯���������������ַ�c*/
	}
	return str;                 /*�������ɵ�����ַ���*/
}



void Speedtest() {
	int total_num = 10;
	cout << endl;
	cout << "SM3��ϣ" << total_num << "������ַ���" << endl;
	//string* random_str;
	//random_str = (string*)malloc(total_num * sizeof(string*));
	string random_str[10];
	for (int i = 0; i < total_num; i++) {
		random_str[i] = rand_str(64);
	}
	clock_t start_test = clock();
	for (int i = 0; i < total_num; i++) {
		string paddingvalue = padding(random_str[i]);
		string result = ProcessBlock(paddingvalue);
	}
	clock_t finish_test = clock();
	double test_time = (double)(finish_test - start_test) / CLOCKS_PER_SEC;
	cout << (double)(test_time/total_num);
}


int main() {//������
	//��ȷ�Բ���
	cout << "SM3��ȷ�Բ��ԣ�" << endl;
	string str_example = "abcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcd";//��ȷ�Բ����ַ���
	cout << "������ϢΪ�ַ���: " + str_example << endl;
	cout << endl;
	//����T_i����Ӧ��t_i���ֱ�Ӳ��
	for (int i = 0; i < 64; i++) {
		string t = T(i);
		t_i[i] = LeftShift(t, i%32);
		//cout << i << ":" << t_i[i] << endl;
	}


	clock_t start, finish;
	double runtime;
	start = clock();
	string paddingValue = padding(str_example);
	cout << "�������ϢΪ��" << endl;
	for (int i = 0; i < paddingValue.size() / 64; i++) {
		for (int j = 0; j < 8; j++) {
			cout << paddingValue.substr(i * 64 + j * 8, 8) << "  ";
		}
		cout << endl;
	}
	cout << endl;
	string result = ProcessBlock(paddingValue);
	cout << "�Ӵ�ֵ��" << endl;
	for (int i = 0; i < 8; i++) {
		cout << result.substr(i * 8, 8) << "  ";
	}
	cout << endl;
	cout << endl;
	finish = clock();
	runtime = (double)(finish - start) / CLOCKS_PER_SEC;
	cout << runtime;
	cout << endl;
	Speedtest();
}
