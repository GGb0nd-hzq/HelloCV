#include <iostream>
#include <string>
#include <fstream>
class Crypto
{
	public:
		std::string kaisa_1(const std::string& text,int shift)
		{
			std::string result = "";
			for(int k=0;k<text.length();k++)
			{
				char c =text[k];
				if(c>='A'&&c<='Z')
				
				{
					c=(c-'A'+shift)%26+'A';
				}
				else if (c>='a'&&c<='z')
				{
					c=(c-'a'+shift)%26+'a';
				}
				result=result+c;
			}		
			return result;
		}
		std::string kaisa_2(const std::string& text,int shift)
		{
			return kaisa_1(text,26-(shift%26));
		}

}; 
class FileHandler
{
	public:
		std::string getFile(const std::string& filename)
		{
			std::ifstream file(filename.c_str());
			std::string blank,line;
			if (file.is_open())
			{
				while(std::getline(file,line))
				{
					blank+=line+"\n";
					 
				}
			}
			return blank;
		}
		void writeFile(const std::string& filename, const std::string& blank)
		{
			 std::ofstream file(filename.c_str());;
			 if (file.is_open())
			 {
			 	file << blank;
			 }
		}
		void encryptFile(const std::string& inputFile, const std::string& outputFile, int key) 
		{
			Crypto crypto;
			std::string blank = getFile(inputFile);
			std::string encryptedContent = crypto.kaisa_1(blank, key);
			 writeFile(outputFile, encryptedContent);
		}
} ;
class Menu
{
	private:
		std::string title;
		Crypto crypto;
	    FileHandler fileHandler;

		const std::string ENCRYPTED_FILE = "encrypted.txt";
	public:
		Menu(const std::string& menuTitle)
		{
			title = menuTitle;
			
		}
		void start()
		
		{
			std::cout<<title<<std::endl;
			std::cout<<"1.�����ı�"<<std::endl;
			std::cout<<"2.�����ı�"<<std::endl;
			std::cout<<"3.�ļ�����"<<std::endl;
			
		}
		int Choice()
		{
			int choice;
			std::cin>>choice;
			std::cin.ignore();
			return choice;
		} 
		void jiamiwenben()
		{
			int key;
			std::string text,result;
			std::cout<<"������Ҫ���ܵ��ı�:"<<std::endl;
			std::getline(std::cin,text);
			std::cout<<"��������Կ:"<<std::endl;
			std::cin>>key;
			result = crypto.kaisa_1(text, key);
			std::cout<<"���ܽ��:"<<result<<std::endl;
			std::cout << "���س�������...";
			std::cin.get();
			
		}
		void jiemiwenben()
		{
			int key;
			std::string text,result;
			std::cout<<"������Ҫ���ܵ��ı�:"<<std::endl;
			std::getline(std::cin,text);
			std::cout<<"��������Կ:"<<std::endl;
			std::cin>>key;
			result = crypto.kaisa_2(text, key);
			
			std::cout<<"���ܽ��:"<<result<<std::endl;
			std::cout << "���س�������...";
			std::cin.get();
			
		}
		void jiamiwenjian()
		{
			std::string inputfile;
			int key;
			std::cout<<"������Ҫ���ܵ��ļ�·��:"<<std::endl;
			std::getline(std::cin,inputfile);
			std::cout<<"��������Կ:"<<std::endl;
			std::cin>>key;
				fileHandler.encryptFile(inputfile, ENCRYPTED_FILE, key);
				std::cout << "���ܽ���ѱ��浽: " << ENCRYPTED_FILE << std::endl;
			std::cout<<"���س�������...";
			std::cin.get();
			
			
		}
		void getchoice(int choice)
		{
			switch(choice)
			{
				case 1:
					jiamiwenben();
					break;
				case 2:
					jiemiwenben();
					break;
				case 3:
					jiamiwenjian();
					break;
				
			}
		} 
		void run()
		{
			
		    start();
			int choice=Choice();
			getchoice(choice);
			
		}
	 
};
int main()
{
	Menu cryptoMenu("��������");
	cryptoMenu.run();
	return 0;
}
