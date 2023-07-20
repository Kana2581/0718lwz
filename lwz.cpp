#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct DictionaryEntry{
	int prefix;//prefix存放前缀在字典中的索引下表
	char suffix;//记录新添加后缀的字符
};
DictionaryEntry* dictionary;//字典是全局变量
vector<int> result;//存放加密结果，因为字典设置为512也就是9位bit，所以用int表示，如果想更好将函数写成compressLWZ(string input,vector<int>& result);
void compressLWZ(string input) {
	
	dictionary = new DictionaryEntry[512];
	for(int i=0;i<256;i++)
	{
		dictionary[i].prefix = -1;
		dictionary[i].suffix = i;
	}
	int dictSize = 255;
	int dictIndex = 0;
	char currentChar = input[0];
	int currentPrefix = (int)currentChar;
	

	for (int i = 1; i < input.length(); i++)
	{
	
		bool found=false;
		for (int j = dictSize; j >= 256; j--)
		{
			if (dictionary[j].prefix== currentPrefix&&dictionary[j].suffix == input[i]) {
				currentPrefix = j;
				found = true;
				//result.push_back(j);
			
				break;
			}
		}
	
		if(!found)
		{
		
			dictionary[++dictSize].prefix = currentPrefix;
			dictionary[dictSize].suffix = input[i];
			result.push_back((int)currentPrefix);
			currentPrefix = input[i];
		
		

		}

	}
	result.push_back(currentPrefix);

}

void uncompressLWZ(vector<int> input) {

	dictionary = new DictionaryEntry[512];
	for (int i = 0; i < 256; i++)
	{
		dictionary[i].prefix = -1;
		dictionary[i].suffix = i;
	}
	int dictSize = 255;
	int dictIndex = 0;
	char currentChar = input[0];
	int currentPrefix = (int)currentChar;
	int i = 1,j = 1;
	
	string origin;
	origin.push_back((char)currentChar);
	while (i < input.size() || j < origin.length())
	{
		
		if (i < input.size())
		{
			int k = input[i];
			string temp;
			while (k != -1)
			{
			
				temp.insert(0, 1, dictionary[k].suffix);
				k = dictionary[k].prefix;
			} 
			
			origin.append(temp);
			i++;

		}
		//这里建议上面定义的i，j调换就可以看出和加密算法生成字典一模一样
		
		bool found=false;
		for (int k = dictSize; k >= 256; k--)
		{
			if (dictionary[k].prefix== currentPrefix&&dictionary[k].suffix == origin[j]) {
				currentPrefix = k;
				found = true;
				break;
			}
		}
	
		if(!found)
		{
			dictionary[++dictSize].prefix = currentPrefix;
			dictionary[dictSize].suffix = origin[j];
			currentPrefix = origin[j];
		}
		j++;
		
	}
	cout << endl << "解压后的的字符串表示" << origin<<endl;

	

}

int main()
{
	string a = "''~~''~~''~~''~~";//书上的样例39 39 126 126.。。。。。
	cout <<"原文的字符串表示"<< a<<endl;
	compressLWZ(a);
	cout << "加密生成的字典从256到264位置" << endl;
	for (int i = 256; i < 265; i++)
	{
		cout << (int)dictionary[i].prefix << " " << (int)dictionary[i].suffix << endl;
	}
	cout << "加密完的序列用int表示" << endl;
	for (int i = 0; i < result.size(); i++)
		cout << result[i]<<" ";
	cout << endl;
	uncompressLWZ(result);
	cout << "解密生成的字典从256到264位置" << endl;
	for (int i = 256; i < 265; i++)
	{
		cout << (int)dictionary[i].prefix << " " << (int)dictionary[i].suffix<<endl;
	}
	return 0;
}


