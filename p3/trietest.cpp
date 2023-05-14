#include <iostream>
#include <string>
#include "trie.hpp"
#include <fstream>

int main(){

    std::string cmd = "";
    trie mytrie;

    while(std::cin >> cmd){

        if(cmd == "i")
        {
            
            std::string word;
            std::cin >> word;
            try
            {
                for(int i=0; i < word.length(); i++)
                {
                    int m = word[i];
                    if((m < 97) || (m > 122))
                    {   
                        throw illegal_exception();
                    }
                }

                bool a = mytrie.is_find(word);
                if(a == true)
                {   
                    std::cout << "failure" << std::endl;
                } else {
                    mytrie.addword(word);
                    std::cout << "success" << std::endl;
                }
            }
            catch(const std::exception& e)
            {
                std::cout << "illegal argument" << std::endl;
            }
        }

        else if(cmd == "load")
        {
            std::ifstream fin("corpus.txt");
            std::string add;
            while(fin >> add)
            {
                bool a = mytrie.is_find(add);
                if(a == false)
                {
                mytrie.addword(add);
                }

            }
            std::cout << "success" << std::endl;
        }

        else if(cmd == "s")
        {
            std::string word;
            std::cin >> word;
            try
            {
                for(int i=0; i < word.length(); i++)
                {
                    int m = word[i];
                    if((m < 97) || (m > 122))
                    {   
                        throw illegal_exception();
                    }
                }

                bool a = mytrie.is_find(word);
                if(a == true)
                {
                    std::cout << "found " << word << std::endl;
                } else {
                    std::cout << "not found" << std::endl;
                }
            }
            catch(const std::exception& e)
            {
                std::cout << "illegal argument" << std::endl;
            }

        }

        else if(cmd == "empty")
        {   
            mytrie.empty();

        }

        else if(cmd == "p")
        {
            
            if(mytrie.t_size() == 0)
            {
                
            }
            else {

                mytrie.print();
            }

        }

        else if(cmd == "e")
        {
            std::string word;
            std::cin >> word;


            try
            {
                for(int i=0; i < word.length(); i++)
                {
                    int m = word[i];
                    if((m < 97) || (m > 122))
                    {   
                        throw illegal_exception();
                    }
                }

                bool a = mytrie.is_find(word);
            
                if(a == true)
                {
                    mytrie.erase(word);
                    std::cout << "success" << std::endl;
                
                } else {
                    std::cout << "failure" << std::endl;
                }
            }
            catch(const std::exception& e)
            {
                std::cout << "illegal argument" << std::endl;
            }

        }

        else if(cmd == "size")
        {
            std::cout << "number of words is "<< mytrie.t_size() << std::endl;
        }

        else if(cmd == "spellcheck")
        {
            std::string word;
            std::cin >> word;
            bool a = mytrie.is_find(word);
            if(a == true)
            {
                std::cout << "correct" << std::endl;
            }
            else{
            mytrie.spellcheck(word);
            }   
        }

        else if(cmd == "clear")
        {
            mytrie.clear();
            std::cout << "success" << std::endl;
        }

        else if(cmd == "exit")
        {
            return 0;
        }
    }

return 0;
}