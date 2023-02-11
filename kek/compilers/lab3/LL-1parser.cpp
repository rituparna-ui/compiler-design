#include <iostream>
#include <string.h>
using namespace std;
#include <unordered_map>
#include <vector> 
#include<unordered_set>
#include<algorithm>
#include <fstream>

vector<string> nonterm_userdef={"E","T","F"};
vector<string> term_userdef={"+","-","*","/","(",")","i","n"};
string sample_input_string="( id ) * id + id";


unordered_map<string,unordered_set<char>> firsts;
unordered_map<string,unordered_set<char>> follows;
unordered_map<string,vector<string>> removeLeftRecursion(unordered_map<string,vector<string>>& rules){
    
    unordered_map<string,vector<string>> store;
    for(auto lhs:rules){
        vector<string> alpha;
        vector<string> beta;
        vector<string> allrhs = lhs.second;
        for(auto subrhs:allrhs){
            //cout<<subrhs[0]<<"\n"<<"hello "<<lhs.first<<"\n";
            if(subrhs[0]==lhs.first[0]){
                alpha.push_back(subrhs.substr(1,subrhs.length()));
            }else{
                beta.push_back(subrhs);
            }
        }

        if(alpha.size()!=0){
            string lhs_=lhs.first+"^";
            
            for(int b=0;b<beta.size();b++){
                 beta[b].append(lhs_);
            }
            rules[lhs.first] = beta;
            for(int b=0;b<alpha.size();b++){
                 alpha[b].append(lhs_);
            }
            alpha.push_back("#");

            store[lhs_]=alpha;
        }

       

        

    }

    for(auto left: store){
        rules[left.first]=store[left.first];
    }

    cout<<"After Eliminating left recursion new grammar becomes:"<<"\n";
    for(auto rule:rules){
        for(auto i :rule.second){
              cout<<rule.first<<"->"<<i<<"\n";
        }
        
    }

    return rules;
}

vector<char> first(string rule,unordered_map<string,vector<string>> rules){
    string str;
    vector<char> first_temp;
    str+=rule[0];
    if(rule.length()!=0 && rule !=" "){
        if(find(term_userdef.begin(),term_userdef.end(),str)!=term_userdef.end()){
             first_temp.push_back(rule[0]);
             return first_temp;
        }else if(rule[0]=='#'){
            first_temp.push_back('#');
            return first_temp;
        }
    }

    if(rule.length()!=0){
        if(rules.count(str)!=0){
            
            vector<string> rhs_rules=rules[str];

            for(auto itr:rhs_rules){
                vector<char> indiRes=first(itr,rules);
                for(auto i:indiRes){
                    first_temp.push_back(i);
                }
            }

            if(find(first_temp.begin(),first_temp.end(),'#')==first_temp.end()){
                 return first_temp;
            }else{
                 vector<char> newTemp;
                 remove(first_temp.begin(),first_temp.end(),'#');
                 if(rule.length()>1){
                     vector<char> ansNew=first(rule.substr(1,rule.length()),rules);
                     vector<char> newList;
                     if(ansNew.size()>0){
                         
                         first_temp.insert(first_temp.end(),ansNew.begin(),ansNew.end());
                         newList=first_temp;
                     }else{
                         newList=first_temp;
                     }
                     return newList;
                 }


                 first_temp.push_back('#');
                 return first_temp;
            }

        }
    }
}
int computeAllFirsts(unordered_map<string,vector<string>> rules){
    
    

    
    for(auto rule:rules){
        unordered_set<char> temp;
        for (auto sub:rule.second){
            vector<char> res=first(sub,rules);
            if(res.size()>0){
                for(auto u:res){
                    temp.insert(u);
                }
            }
        }
        firsts[rule.first]=temp;
    }


    cout<<"First of all non terminals are:"<<"\n";

    for(auto i:firsts){
        cout<<i.first<<"=>";
        for(auto j:i.second){
            cout<<j;
        }
        cout<<"\n";
    }
    

    return 0;
}
vector<char> follow(string non_term,unordered_map<string,vector<string>> rules){
    vector<char> solset;
    if(non_term=="E"){
        solset.push_back('$');
    }
    
    if(non_term.length()==1){
        for(auto cur:rules){
        vector<string> rhs=rules[cur.first];
        //cout<<cur.first<<"=>";
        for(auto sub:rhs){
            
            if(sub.find(non_term)<sub.length() && sub[sub.find(non_term)+1]!='^' ){
                
                while(sub.find(non_term)<sub.length() && sub[sub.find(non_term)+1]!='^' ){
                    int index_nt=sub.find(non_term);
                    
                    if(sub[index_nt+1]=='^'){
                        index_nt++;
                        
                    }
                    sub=sub.substr(index_nt+1,sub.length());
                    //cout<<sub<<"\n";
                    vector<char> res;
                    if(sub.length()!=0){
                        //res=first(sub,rules);
                        if(find(term_userdef.begin(),term_userdef.end(),sub)!=term_userdef.end()){
                            res.push_back(sub[0]);
                        }else{
                            unordered_set<char> temp =firsts[sub];
                            for(auto i:temp){
                                res.push_back(i);
                            }
                        }
                        
                        
                        if(find(res.begin(),res.end(),'#')!=res.end()){
                            
                           
                            remove(res.begin(),res.end(),'#');
                            vector<char> ansNew=follow(cur.first,rules);
                            
                            
                            vector<char> newList;
                            if(ansNew.size()>0){
                                
                                
                                res.insert(res.end(),ansNew.begin(),ansNew.end());
                                newList=res;
                                
                                res=newList;
                            }else{
                                newList=res;
                            }

                            res=newList;


                            
                        }
                       
                        
                    }
                    else{
                            if(non_term!=cur.first){
                                res=follow(cur.first,rules);
                                //cout<<cur.first;
                            }
                    }
                    

                    if(res.size()>0){
                        for(auto g:res){
                            //cout<<g;
                            solset.push_back(g);
                        }
                    }
                    
                }
                
            }
            
        }
        //cout<<"\n";

        
        
    }

    }else{
       for(auto cur:rules){
        vector<string> rhs=rules[cur.first];
        //cout<<cur.first<<"=>";
        for(auto sub:rhs){
            
            if(sub.find(non_term)<sub.length() && sub[sub.find(non_term)+1]=='^' ){
               
                while(sub.find(non_term)<sub.length() && sub[sub.find(non_term)+1]=='^' ){
                    int index_nt=sub.find(non_term);
                    
                    if(sub[index_nt+1]=='^'){
                        index_nt++;
                        
                    }
                    sub=sub.substr(index_nt+1,sub.length());
                    //cout<<sub<<"\n";
                    vector<char> res;
                    if(sub.length()!=0){
                        //res=first(sub,rules);
                        if(find(term_userdef.begin(),term_userdef.end(),sub)!=term_userdef.end()){
                            res.push_back(sub[0]);
                        }else{
                            unordered_set<char> temp =firsts[sub];
                            for(auto i:temp){
                                res.push_back(i);
                            }
                        }
                        
                        
                        if(find(res.begin(),res.end(),'#')!=res.end()){
                            
                           
                            remove(res.begin(),res.end(),'#');
                            vector<char> ansNew=follow(cur.first,rules);
                            
                            
                            vector<char> newList;
                            if(ansNew.size()>0){
                                
                                
                                res.insert(res.end(),ansNew.begin(),ansNew.end());
                                newList=res;
                                
                                res=newList;
                            }else{
                                newList=res;
                            }

                            res=newList;


                            
                        }
                       
                        
                    }
                    else{
                            if(non_term!=cur.first){
                                res=follow(cur.first,rules);
                                //cout<<cur.first;
                            }
                    }
                    

                    if(res.size()>0){
                        for(auto g:res){
                            //cout<<g;
                            solset.push_back(g);
                        }
                    }
                    
                }
                
            }
            
        }
        //cout<<"\n";

        
        
    }
    }
    
    return solset;

}
int computeAllFollows(unordered_map<string,vector<string>> rules){

    
     
    for(auto non_ter:rules){
        unordered_set<char> solset;
        
        vector<char> sol=follow(non_ter.first,rules);
        if(sol.size()>0){
            for(auto g:sol){
                solset.insert(g);
            }
        }

        follows[non_ter.first]=solset;



    }

    cout<<"Follow set of all non terminals are:"<<"\n";
   

    for(auto i:follows){
        cout<<i.first<<"=>";
        for(auto j:i.second){
            cout<<j;
        }
        cout<<"\n";
    }
}
int main() {
    unordered_map<string,vector<string>> rules;
    vector<string> rule1={"E+T", "E-T" ,"T"};
    vector<string> rule2={"T*F" , "T/F" , "F"};
    vector<string> rule3={"(E)" ,"i" ,"n"};

    rules.insert(pair<string,vector<string>> ("E",rule1));
    rules.insert(pair<string,vector<string>> ("T",rule2));
    rules.insert(pair<string,vector<string>> ("F",rule3));

    string myText ;

    ifstream MyReadFile("output.txt");
    string input;
    int flag=0;

    while (getline (MyReadFile, myText)) {
        // Output the text from the file
        if(myText=="error"){
            cout<<"invalid character in input"<<"\n";
            flag=1;
            break;
        }else{
            input+=myText;
        }
        

    }
    if(!flag)
    cout<<input<<"\n";



    

   rules=removeLeftRecursion(rules);
    


    computeAllFirsts(rules);
    computeAllFollows(rules);

    return 0;
}