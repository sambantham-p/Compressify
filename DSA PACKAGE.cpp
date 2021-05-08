#include<iostream>
#include<cstdio>
#include<string>
#include<bits/stdc++.h>
#include<vector>
#include<conio.h>
#include<stdlib.h>
#include<stdio.h>
#include<sstream>

using namespace std;

class HuffTree
{
  public:
    int val;
    char letter;
    HuffTree *left;
    HuffTree *right;

    HuffTree(int val, char c)
    {
        this->val=val;
        this->letter=c;
        this->left=NULL;
        this->right=NULL;
    }
};

vector<pair<int,char>>frequencyDect(string s)
{
    map<char,int>mp;
    for(int i=0;i<s.size();i++)
    {
        mp[s[i]]++;
    }
    vector<pair<int,char>>v;
    for(int i=0;i<s.size();i++)
    {
        if(mp[s[i]]!=0)
        {
            v.push_back(make_pair(mp[s[i]],s[i]));
            mp[s[i]]=0;

        }
    }
    return v;

}

class Compare
{
  public:
    bool operator() (HuffTree* a,HuffTree* b)
    {
        if(a->val>b->val)
            return true;
        else
        {
            return false;
        }
    }

};
void print(priority_queue<HuffTree*,vector<HuffTree*>,Compare>q)
{
    while(q.size())
    {
        cout<<q.top()->letter<<" "<<q.top()->val<<endl;
        q.pop();

    }
}


HuffTree *maketree(vector<pair<int,char>>&freq)
{
    priority_queue<HuffTree*,vector<HuffTree*>,Compare> q;
    for(int i=0;i<freq.size();i++)
    {
        q.push(new HuffTree(freq[i].first,freq[i].second));
    }
    print(q);
    while(q.size()>1)
    {
        HuffTree *left=q.top();
        q.pop();
        HuffTree *right=q.top();
        q.pop();

        HuffTree *node= new HuffTree(left->val+right->val,'~');
        node->left=left;
        node->right=right;
        q.push(node);

    }
    return q.top();
}
void getval(HuffTree *root,string s,map<char,string>& vtr)
{
  if(!root)
  {
    return;
  }

if(root->letter!='~')
{
    vtr[root->letter]=s;
    return;
}
else
{
    getval(root->left,s+"0",vtr);
    getval(root->right,s+"1",vtr);

}
}
string decode(HuffTree *tree,string s,int &i)
{
    string str="";
    while(i<s.size())
    {
    if(tree->letter!='~')
    {
        str+=tree->letter;
        return str;

    }

    else if(s[i]=='0')
    {
        if(tree->left)
        {
            tree=tree->left;
            i++;
        }
        else{
            return str;
        }
    }
    else if(s[i]='1')
    {
        if(tree->right)
        {
            tree=tree->right;
            i++;
        }
        else
        {
            return str;
        }
    }

    }
    return "";
}

int main()
{
   ifstream f("test2.txt");
   string s;
   if(f)
   {
      ostringstream ss,sr;
      ss << f.rdbuf();
      s = ss.str();
      vector<pair<int,char>>freq= frequencyDect(s);
      sort(freq.begin(),freq.end());
      for(int i=0;i<freq.size();i++)
      {
         cout<<freq[i].first<<" "<<freq[i].second<<endl;

      }
      map<char,string>vtr;
      HuffTree *tree=maketree(freq);
      getval(tree,"",vtr);
      string res="";
      for(auto i:s)
      res+=vtr[i];
      cout<<"*****"<<endl;
      cout<<s<<endl;
      cout<<res<<endl;
      string back="";
      for(int i=0;i<s.size();)
      {
         back+=decode(tree,s,i);
      }
      cout<<back<<endl;
      /*ofstream fe("datoutput.bin",std::ios_base::binary);
      fe<<endl;
      if(fe.is_open())
      {
          fe<<res;
          cout<<endl;
          fe.close();
      }
      else
      {
          cout<<"Unable to open the file";
          return 0;
      }*/
    ofstream savefile("score.dat", std::ios_base::binary);
    if(savefile.good())
    {
        savefile.write((char*) &res, sizeof (string));
        cout<<endl;
        savefile.close();
    }
    else
    {
          cout<<"Unable to open the file";
          return 0;
    }

   }
}
