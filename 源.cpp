#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<vector>
#include<map>
#include<set>
#include<utility>
#include<algorithm>
#include<iomanip>
using namespace std;

class Interest;
class Student;

/****兴趣类型类****/
class Inty
{
private:
	vector<string> It;
public:
	friend class Interest;
	Inty(){}
	~Inty(){}
	void readfile();
	void writefile();
	void addtype();
	void changetype();
	void print();
};

void Inty::print(){
	for(auto iter=this->It.cbegin();iter!=this->It.cend();++iter)
	{
		cout<<(*iter)<<endl;
	}
}

void Inty::readfile()
{
	ifstream rfile("E:\\课程设计\\数据结构\\1.txt");
	if (!rfile.is_open()) 
		cout<<"未成功打开文件"<<endl;

	string str;
	while(getline(rfile,str)) {
		this->It.push_back(str);
	}
	rfile.close();
}

void Inty::writefile()
{
	ofstream wfile("E:\\课程设计\\数据结构\\1.txt");
	for(auto iter=this->It.begin();iter!=this->It.end();iter++)
	{
		wfile<<(*iter)<<endl;
	}
	wfile.close();
}

void Inty::addtype()
{
	cout<<"请输入您要添加的兴趣类别"<<"(ctrl+z结束输入)"<<endl;
	string str;
	while(cin>>str)
	{
		this->It.push_back(str);
	}
	cin.clear();
	cin.sync();
}

void Inty::changetype()
{
	cout<<"请输入目标兴趣类别和修改后类别"<<"(ctrl+z结束输入)"<<endl;
	string str1,str2;
	while(cin>>str1>>str2);
	{
		if(this->It.cend()!=find(this->It.cbegin(),this->It.cend(),str1))
			replace(this->It.begin(),this->It.end(),str1,str2);
		else
			cout<<"错误：没有该兴趣类型可供删除"<<endl;
	}
	cin.clear();
	cin.sync();
}

/****兴趣项类****/
class Inelem{
private:
	vector<vector<string>> Ie;
public:
	friend class Interest;
	Inelem(){}
	~Inelem(){}
	void readfile();
	void writefile();
	void deletelem();
	void changelem();
	void print();
};

void Inelem::print(){
	for(auto iter=this->Ie.cbegin();iter!=this->Ie.cend();++iter)
	{
		for(auto ite=iter->cbegin();ite!=iter->cend();++ite)
		{
			cout<<(*ite)<<" ";
		}
		cout<<endl;
	}
}

void Inelem::readfile(){
	ifstream rfile("E:\\课程设计\\数据结构\\2.txt");
	if (!rfile.is_open()) 
		cout<<"未成功打开文件"<<endl;

	string line,word;
	while(getline(rfile,line))
	{
		vector<string> temp;
		istringstream instream(line);
		while(instream>>word)
		{
			temp.push_back(word);
		}
		this->Ie.push_back(temp);
	}

	rfile.close();
}

void Inelem::writefile(){
	ofstream wfile("E:\\课程设计\\数据结构\\2.txt");
	for(auto iter=this->Ie.cbegin();iter!=this->Ie.cend();++iter)
	{
		for(auto ite=iter->cbegin();ite!=(iter->cend()-1);++ite)
		{
			wfile<<(*ite)<<" ";
		}
		wfile<<(*(iter->cend()-1))<<endl;
	}
	wfile.close();
}

void Inelem::deletelem(){
	cout<<"请输入要删除的兴趣项："<<"(ctrl+z结束输入)"<<endl;
	string str;
	while(cin>>str){
		auto iter=this->Ie.begin();
		for(;iter!=this->Ie.end();++iter)
		{
			auto ite=find(iter->begin(),iter->end(),str);
			if(ite!=iter->cend())
			{
				if(iter->size()==1){
					iter->erase(ite);
					iter->push_back(string("无"));
				}
				else
					iter->erase(ite);
				break;
			}
		}
		if(iter==this->Ie.end())
			cout<<"错误：没有该兴趣项可供删除"<<endl;
	}
	cin.clear();
	cin.sync();
}

void Inelem::changelem(){
	cout<<"请输入目标兴趣项和修改后项"<<"(ctrl+z结束输入)"<<endl;
	string str1,str2;
	while(cin>>str1>>str2){
		auto iter=this->Ie.begin();
		for(;iter!=this->Ie.end();++iter)
		{
			auto ite=find(iter->begin(),iter->end(),str1);
			if(ite!=iter->end()){
				replace(iter->begin(),iter->end(),str1,str2);
				break;
			}
		}
		if(iter==this->Ie.end())
			cout<<"错误：没有该兴趣项可供修改"<<endl;
	}
	cin.clear();
	cin.sync();
}

/****兴趣类 同一管理兴趣的各种操作****/
class Interest{
private:
	Inty it;
	Inelem ie;
public:
	friend class Student;
	Interest(){}
	~Interest(){}
	bool ffind(const string &s);
	void readfile();
	void writefile();
	void addtype(){this->it.addtype();}
	void addelem();
	void deletetype();
	void deletelem(){this->ie.deletelem();}
	void changetype(){this->it.changetype();}
	void changelem(){this->ie.changelem();}
	void print();
};

bool Interest::ffind(const string &s){
	for(auto iter=this->ie.Ie.cbegin();iter!=this->ie.Ie.cend();++iter)
	{
		if(iter->cend()!=find(iter->cbegin(),iter->cend(),s))
			return true;
	}
	return false;
}

void Interest::readfile(){
	this->it.readfile();
	this->ie.readfile();
}

void Interest::writefile(){
	this->it.writefile();
	this->ie.writefile();
}

void Interest::addelem(){
	cout<<"请问为哪个兴趣类别添加兴趣项"<<endl;
	string str1,str2;
	while(cin>>str1)
	{
		unsigned int i=0;
		for(;i<this->it.It.size();++i){
			if(str1==this->it.It.at(i))
				break;
		}

		if(i==this->it.It.size())
			cout<<"错误：没有该兴趣类别"<<endl;
		else{
			cout<<"请输入要添加的兴趣项"<<"(输入ctrl+z结束输入)"<<endl;
			if(i<this->ie.Ie.size()){
				unsigned int j=1;
				if(this->ie.Ie.at(i).size()==j && this->ie.Ie.at(i).at(0)==string("无")){
					this->ie.Ie.at(i).clear();
					while(cin>>str2){
						this->ie.Ie.at(i).push_back(str2);
					}
				}
			}
			else{
				unsigned int j=1;
				if(this->ie.Ie.at(i).size()==j && this->ie.Ie.at(i).at(0)==string("无")){
					this->ie.Ie.at(i).clear();
					vector<string> temp;
					while(cin>>str2){
						temp.push_back(str2);
					}
					this->ie.Ie.push_back(temp);
				}
			}
		}
	}
	cin.clear();
	cin.sync();
}

void Interest::deletetype(){
	cout<<"请输入要删除的兴趣类别"<<"(输入ctrl+z结束输入)"<<endl;
	string str;
	while(cin>>str)
	{
		unsigned int i=0;
		for(;i<this->it.It.size();++i){
			if(str==this->it.It.at(i))
				break;
		}
		
		if(i==this->it.It.size())
			cout<<"错误：没有该兴趣项"<<endl;
		else{
			this->it.It.erase(find(this->it.It.begin(),this->it.It.end(),str));
			this->ie.Ie.erase(this->ie.Ie.begin()+i);
		}
	}
	cin.clear();
	cin.sync();
}

void Interest::print(){
	unsigned int i=0;
	for(auto iter=this->it.It.cbegin();iter!=this->it.It.cend();++iter)
	{
		cout<<(*iter)<<":";
		if(i<this->ie.Ie.size())
		{
			for(auto ite=this->ie.Ie.at(i).cbegin();ite!=this->ie.Ie.at(i).cend();++ite)
			{
				cout<<(*ite)<<" ";
			}
		}
		cout<<endl;
		++i;
	}
}

/****学生类****/
class Student{
private:
	map<string,set<string>> student;
	map<string,set<string>> stuinter;
	Interest *in;
public:
	Student(Interest *i=nullptr){ in=i;}
	~Student(){}
	string addstudent();
	bool print(string &s);
	void readfile();
	void writefile();
	string login();
	void addmessage(string &s);
	void deletemessage(string &s);
	void changemessage(string &s);
	void addinter(string &s);
	void deleteinter(string &s);
	void changeinter(string &s);
};

string Student::addstudent(){
	string str;
	set<string> tempset;
	cout<<"请输入要添加的学生姓名"<<endl;
	cin>>str;
	this->student.insert(pair<string,set<string>>(str,tempset));
	this->stuinter.insert(pair<string,set<string>>(str,tempset));

	return str;
}

bool Student::print(string &s){
	if(this->student.find(s)!=this->student.cend()){
		cout<<s<<"的个人信息:";
		for(auto iter=this->student.find(s)->second.begin();iter!=this->student.find(s)->second.end();++iter)
		{
			cout<<(*iter)<<" ";
		}

		cout<<"       "<<"兴趣：";

		int i=0;
		for(auto ite=this->stuinter.find(s)->second.begin();ite!=this->stuinter.find(s)->second.end();)
		{
			if(this->in->ffind(*ite)){
				cout<<(*ite)<<" ";
				++ite;
			}
			else{
				this->stuinter.find(s)->second.erase(ite++);
				++i;
			}
		}
		cout<<endl;
		if(0!=i)
			cout<<"由于教务系统取消了一些兴趣项，请您留意教务信息并尽快删除相关兴趣!"<<endl;
		return true;
	}
	else
		return false;
}

void Student::readfile(){
	ifstream rfile("E:\\课程设计\\数据结构\\3.txt");
	ifstream infile("E:\\课程设计\\数据结构\\4.txt");
	if (!rfile.is_open()) 
		cout<<"未成功打开文件"<<endl;

	string line,word;
	string tempstr;
	set<string> tempset;
	while(getline(rfile,line))
	{
		int i=0;
		tempstr.clear();
		tempset.clear();

		istringstream instream(line);
		while(instream>>word)
		{
			if(0==i)
				tempstr=word;
			else
				tempset.insert(word);
			++i;
		}
		this->student.insert(pair<string,set<string>>(tempstr,tempset));

		line.clear();
		tempset.clear();
		getline(infile,line);
		istringstream instream1(line);
		while(instream1>>word)
		{
			tempset.insert(word);
		}
		this->stuinter.insert(pair<string,set<string>>(tempstr,tempset));
	}

	rfile.close();
	infile.close();
}

void Student::writefile(){
	ofstream wfile("E:\\课程设计\\数据结构\\3.txt");
	ofstream ofile("E:\\课程设计\\数据结构\\4.txt");

	for(auto iter=this->student.cbegin();iter!=this->student.cend();++iter)
	{
		wfile<<iter->first<<" ";
		for(auto ite=iter->second.cbegin();ite!=iter->second.cend();++ite)
		{
			wfile<<(*ite)<<" ";
		}
		wfile<<endl;
	}

	for(auto i=this->stuinter.cbegin();i!=this->stuinter.cend();++i)
	{
		for(auto j=i->second.cbegin();j!=i->second.cend();++j)
		{
			ofile<<(*j)<<" ";
		}
		ofile<<endl;
	}

	wfile.close();
	ofile.close();
}

string Student::login(){
	string str;
	cout<<"请输入姓名登录"<<endl;
	cin>>str;
	cout<<endl;
	return str;
}

void Student::addmessage(string &s){
	cout<<"请输入要添加的信息"<<"(输入ctrl+z结束输入)"<<endl;
	string str;
	while(cin>>str){
		this->student.find(s)->second.insert(str);
	}
	cin.clear();
	cin.sync();
}

void Student::deletemessage(string &s){
	cout<<"请输入要删除的信息"<<"(输入ctrl+z结束输入)"<<endl;
	string str;
	while(cin>>str){
		if(this->student.find(s)->second.find(str)!=this->student.find(s)->second.cend())
			this->student.find(s)->second.erase(str);
		else
			cout<<"错误：系统没有您的该项信息"<<endl;
	}
	cin.clear();
	cin.sync();
}

void Student::changemessage (string &s){
	cout<<"请输入要修改的信息和修改后的信息"<<"(输入ctrl+z结束输入)"<<endl;
	string  str1,str2;
	while(cin>>str1>>str2)
	{
		if(this->student.find(s)->second.find(str1)!=this->student.find(s)->second.cend())
		{
			this->student.find(s)->second.erase(str1);
			this->student.find(s)->second.insert(str2);
		}
		else
			cout<<"错误：系统没有您的该项信息"<<endl;
	}
	cin.clear();
	cin.sync();
}

void Student::addinter(string &s){
	this->in->print();
	cout<<"请输入要添加的兴趣项"<<"(输入ctrl+z结束输入)"<<endl;
	string str;
	while(cin>>str){
		if(this->in->ffind(str))
			this->stuinter.find(s)->second.insert(str);
		else
			cout<<"对不起教务系统没有开设相关课程，请选择其他兴趣"<<endl;
	}
	cin.clear();
	cin.sync();
}

void Student::deleteinter(string &s){
	cout<<"请输入要删除的兴趣项"<<"(输入ctrl+z结束输入)"<<endl;
	string str;
	while(cin>>str){
		if(this->stuinter.find(s)->second.find(str)!=this->stuinter.find(s)->second.cend())
			this->stuinter.find(s)->second.erase(str);
		else
			cout<<"错误：没有该兴趣项可供删除"<<endl;
	}
	cin.clear();
	cin.sync();
}


void Student::changeinter(string &s){
	cout<<"请输入要修改的兴趣项和修改后的兴趣项"<<"(输入ctrl+z结束输入)"<<endl;
	string  str1,str2;
	while(cin>>str1>>str2)
	{
		if(this->stuinter.find(s)->second.find(str1)!=this->stuinter.find(s)->second.cend())
		{
			this->stuinter.find(s)->second.erase(str1);
			this->stuinter.find(s)->second.insert(str2);
		}
		else
			cout<<"错误：没有该兴趣项可供修改"<<endl;
	}
	cin.clear();
	cin.sync();
}



int main(){
	Interest inter;
	Interest *inte=&inter;
	inter.readfile();
	Student stu(inte);
	stu.readfile();

LOOP1:
	cout<<"请选择操作："<<endl;
	cout<<"1.学生信息管理"<<endl
		<<"2.兴趣管理"<<endl
		<<"3.关闭程序"<<endl;

	int operation;
	cin>>operation;
	system("cls");
	if(1==operation){
LOOP6:
		cout<<"请选择操作"<<endl
			<<"1.实名登录"<<endl
			<<"2.注册"<<endl
			<<"3.后退一步"<<endl
			<<"4.关闭程序"<<endl;
		cin>>operation;
		if(1==operation){
			system("cls");
			string tempstu=stu.login();
LOOP7:
			if(stu.print(tempstu)){
				cout<<"请选择操作"<<endl
					<<"1.信息管理"<<endl
					<<"2.兴趣管理"<<endl
					<<"3.后退一步"<<endl
					<<"4.关闭程序"<<endl;
				cin>>operation;
				if(1==operation){
					cout<<"请选择操作"<<endl
						<<"1.添加信息"<<endl
						<<"2.删除信息"<<endl
						<<"3.修改信息"<<endl
						<<"4.后退一步"<<endl
						<<"5.关闭程序"<<endl;
					cin>>operation;
					if(1==operation){
						stu.addmessage(tempstu);
						system("cls");
						goto LOOP7;
					}
					else if(2==operation){
						stu.deletemessage(tempstu);
						system("cls");
						goto LOOP7;
					}
					else if(3==operation){
						stu.changemessage(tempstu);
						system("cls");
						goto LOOP7;
					}
					else if(4==operation){
						system("cls");
						goto LOOP7;
					}
					else{
						goto LOOP5;
					}
				}
				else if(2==operation){
					cout<<"请选择操作"<<endl
						<<"1.添加兴趣"<<endl
						<<"2.删除兴趣"<<endl
						<<"3.修改兴趣"<<endl
						<<"4.后退一步"<<endl
						<<"5.关闭程序"<<endl;
					cin>>operation;
					if(1==operation){
						stu.addinter(tempstu);
						system ("cls");
						goto LOOP7;
					}
					else if(2==operation){
						stu.deleteinter(tempstu);
						system ("cls");
						goto LOOP7;
					}
					else if(3==operation){
						stu.changeinter(tempstu);
						system ("cls");
						goto LOOP7;
					}
					else if(4==operation){
						system("cls");
						goto LOOP7;
					}
					else{
						goto LOOP5;
					}
				}
				else if(3==operation){
					system("cls");
					goto LOOP6;
				}
				else{
					goto LOOP5;
				}
			}
			else{
				system("cls");
				cout<<"没有找到你的信息,请选择注册操作"<<endl;
				goto LOOP6;
			}

		}
		else if(2==operation){
			system("cls");
			string temstr=stu.addstudent();
LOOP9:
			stu.print(temstr);
			cout<<"请选择操作"<<endl
				<<"1.添加信息"<<endl
				<<"2.添加兴趣"<<endl
				<<"3.后退一步"<<endl
				<<"4.关闭程序"<<endl;
			cin>>operation;
			if(1==operation){
				stu.addmessage(temstr);
				system("cls");
				goto LOOP9;
			}
			else if(2==operation){
				inter.print();
				stu.addinter(temstr);
				system("cls");
				goto LOOP9;
			}
			else if(3==operation){
				system("cls");
				goto LOOP6;
			}
			else{
				goto LOOP5;
			}
		}
		else if(3==operation){
			system("cls");
			goto LOOP1;
		}
		else{
			goto LOOP5;
		}
	}
	else if(2==operation){
LOOP2:
		system("cls");
		inter.print();
		cout<<"请选择操作："<<endl
			<<"1.兴趣类别管理"<<endl
			<<"2.兴趣项管理"<<endl
			<<"3.后退一步"<<endl
			<<"4.关闭程序"<<endl;
		cin>>operation;
		if(1==operation){
LOOP3:
			cout<<"请选择操作："<<endl
				<<"1.添加兴趣类别"<<endl
				<<"2.删除兴趣类别"<<endl
				<<"3.修改兴趣类别"<<endl
				<<"4.后退一步"<<endl
				<<"5.关闭程序"<<endl;
			cin>>operation;
			if(1==operation){
				inter.addtype();
				system("cls");
				inter.print();
				goto LOOP3;
			}
			else if(2==operation){
				inter.deletetype();
				system("cls");
				inter.print();
				goto LOOP3;
			}
			else if(3==operation){
				inter.changetype();
				system("cls");
				inter.print();
				goto LOOP3;
			}
			else if(4==operation){
				goto LOOP2;
			}
			else{
				goto LOOP5;
			}
		}
		else if(2==operation){
LOOP4:
			cout<<"请选择操作"<<endl
				<<"1.添加兴趣项"<<endl
				<<"2.删除兴趣项"<<endl
				<<"3.修改兴趣项"<<endl
				<<"4.后退一步"<<endl
				<<"5.关闭程序"<<endl;
			cin>>operation;
			if(1==operation){
				inter.addelem();
				system("cls");
				inter.print();
				goto LOOP4;
			}
			else if(2==operation){
				inter.deletelem();
				system("cls");
				inter.print();
				goto LOOP4;
			}
			else if(3==operation){
				inter.changelem();
				system("cls");
				inter.print();
				goto LOOP4;
			}
			else if(4==operation){
				goto LOOP2;
			}
			else{
				goto LOOP5;
			}
		}
		else if(3==operation){
			system("cls");
			goto LOOP1;
		}
		else{
			goto LOOP5;
		}
	}

LOOP5:
	inter.writefile();
	stu.writefile();
	return 0;
}