#include <iostream>
#include <string>
#include "trie.hpp"

node::node()
{
    letter = "";
    isWordEnd = false;
    // is_push = false;
    for (int i = 0; i < size; i++)
    {
        child[i] = NULL;
    }
}

node::~node()
{
    for(int i = 0; i < size ; i++)
    {
        delete this-> child[i];
        this->child[i] = NULL;   
    }
}

trie::trie()
{
    count = 0;
    // initial = 0;
    root = new node;
}

trie::~trie()
{
    r_clear(root);

    delete root;

    root = nullptr;
}

bool trie::is_find(std::string word)
{
    node *p = root;
    for (int i = 0; i < word.length(); ++i)
    {
        int index = word[i] - 'a';
        if (p->child[index] == NULL)
        {
            return false;
        }
        else if (p->child[index] != NULL)
        {
            p = p->child[index];
        }
    }

    if (p->isWordEnd == true)
    {
        return true;
    }
    else
    {
        return false;
    }

}

void trie::addword(std::string word)
{

    node *p = root;
    
    for (int i = 0; i < word.length(); ++i)
    {
        int index = word[i] - 'a';
        if (p->child[index] == NULL)
        {
            p->child[index] = new node;
            node *temp = p;
            p = p->child[index];
            p->letter = word[i];
            p->parent = temp;
        }
        else
        {
            p = p->child[index];

        }
    }
    p->isWordEnd = true;
    count++;
    // std::cout << count << std::endl;
}

int trie::is_empty(node *p)
{
    int a = 0;
    for (int i = 0; i < size; ++i)
    {
        if (p->child[i] != NULL)
        {
            a++;
        }
    }

    return a;
}

void trie::empty()
{
    if(count == 0)
    {
        std::cout << "empty 1" << std::endl;
    }
    else
    {
        std::cout << "empty 0" << std::endl;
    }
}

void trie::print()
{
    node *p = root;
    std::string word = "";
    r_print(p, word);
    std::cout <<std::endl;
}

void trie::r_print(node *p, std::string word)
{

    if((p->isWordEnd == true))
    {   
        word.push_back(p->letter[0]);
        std::cout << word << " ";

    }else if((is_empty(p) > 0))
    {
        word.push_back(p->letter[0]);

    }

    for(int i = 0; i < size ; i++)
    { 
        if((p->child[i] != NULL) )
        {  
            r_print(p->child[i], word);
            
        }
    }

    word.pop_back();
}

void trie::erase(std::string word)
{
    node *p = root;
    r_erase(p, word, 0);
    count --;
} 

void trie::r_erase(node *p, std::string word, int iw)
{   
    if( (iw == word.length()) && (p->isWordEnd == true))
    {
        if(is_empty(p) == 0)
        {   
            int index = word[iw -1] - 'a';
            p = p->parent;
            delete p->child[index];
            p->child[index] = NULL;
        } 
        else{
            int index = word[iw -1] - 'a';
            p = p->parent;
            (p->child[index])->isWordEnd = false;
        }
        return;
    }
    else{
        
        int index = word[iw] - 'a';
        if(p->child[index] != NULL)
        {
            r_erase(p->child[index], word, iw + 1);

            if((p->isWordEnd == false) && (is_empty(p) == 0) && (p != root))
            {   
                int index = word[iw-1] - 'a';
                p = p->parent;
                delete p->child[index];
                p->child[index] = NULL;
            }
        }
        return;
    }
}

void trie::spellcheck(std::string word)
{
    node *p = root;
    s_check(p, word, 0);
    std::cout<< std::endl;
}

void trie::s_check(node *p, std::string word, int iw)
{    
    if(p == root)
    {
        int index = word[iw] - 'a';
        if(p->child[index] != NULL)
        {
            //  std::cout << "children1 " << (p->child[index])->letter << std::endl;
            s_check(p->child[index], word, iw+1);
        }
        else
        {
            return;
        }
    }

    else if(p != root)
    {   
        int index = word[iw] - 'a';
        if(iw < word.length())
        {   
            if(p->child[index] != NULL)
            {
            s_check(p->child[index], word, iw+1);
            }
        }

        if((iw == word.length()) || (is_empty(p) == 0) || (p->child[index] == NULL))

        {   
            r_print(p, word.substr(0, iw-1));
        }
    }

    return;
 
}

int trie::t_size()
{
    return count;
}

void trie::clear()
{
    node *p = root;
    r_clear(p);
    count = 0;
    p = nullptr;
    delete p ;
}

void trie::r_clear(node *p)
{   
    if(is_empty(root) == 0)
    {
        return;
    }
    
    for(int i= 0; i < size ; i++)
    {
        if((p->child[i]) != NULL)
        {   
            // std::cout << "current1 " << p->letter << std::endl;

            r_clear(p->child[i]);

            // std::cout << "current2 " << p->letter << std::endl;
            delete p->child[i];
            p->child[i] = NULL;

        }
    }
}
