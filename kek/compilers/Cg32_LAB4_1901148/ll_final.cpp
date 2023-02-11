#include <iostream>
#include <string.h>
using namespace std;
#include <unordered_map>
#include <vector> 
#include<unordered_set>
#include<algorithm>
#include <fstream>
#include<stack>



vector<string> nonterm_userdef={"E","T","F"};
vector<string> term_userdef={"+","-","*","/","i","n","(",")"};
string sample_input_string="( id ) * id + id";
string start_symbol={"S"};


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

unordered_map<string,vector<string>> removeLeftFactoring(unordered_map<string,vector<string>> &rules){
    
    unordered_map<string,vector<string>> newDict;

    for(auto lhs:rules){
        vector<string> allrhs ;
        allrhs=rules[lhs.first];
        unordered_map<char,vector<string>> temp;
        for(auto subrhs:allrhs){
            if(temp.find(subrhs[0])==temp.end()){
                    temp[subrhs[0]].push_back(subrhs);
            }else{
                    temp[subrhs[0]].push_back(subrhs);
            }
        }
        vector<string> rule_temp;
        unordered_map<string,vector<string>> temp_dict;
        for(auto key:temp){
            if(temp[key.first].size()>1){
                string lhs_=lhs.first;
                lhs_+="^";
                string temp_key;
                temp_key+=key.first;
                rule_temp.push_back(temp_key);
                rule_temp.push_back(lhs_);

                vector<string> ex_rules;
                for(auto g:temp[key.first]){
                    ex_rules.push_back(g.substr(1));
                }
                temp_dict[lhs_]=ex_rules;

            }else{
                for(auto i:temp[key.first]){
                    rule_temp.push_back(i);
                }
            }
        }
        newDict[lhs.first]=rule_temp;

        for(auto key:temp_dict){
            newDict[key.first]=temp_dict[key.first];
        }


    }

      cout<<"After Eliminating left factoring new grammar becomes:"<<"\n";
    for(auto rule:newDict){
        for(auto i :rule.second){
              cout<<rule.first<<"->"<<i<<"\n";
        }
        
    }
    
    return newDict;
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
    if(non_term==start_symbol){
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


unordered_map<string,unordered_map<string,vector<string>>> createParse(unordered_map<string,vector<string>> rules){
    vector<string> ntlist ;
    for(auto rule:rules){
        ntlist.push_back(rule.first);
    }
    vector<string> terminals = term_userdef;
    terminals.push_back("$");

    unordered_map<string,unordered_map<string,vector<string>>> mat;

     for(auto x: ntlist){
         unordered_map<string,vector<string>> temp;
        for(auto y:terminals){
            vector<string> str;
            temp[y]=str;

        }
       
        mat[x]=temp;
    }

    for(auto lhs:rules){
        vector<string> rhs=lhs.second;
        
        for(auto y:rhs){
            string t;
            t+=y[0];
            unordered_set<char> res;
            if(find(ntlist.begin(),ntlist.end(),t)!=ntlist.end()){
                res=firsts[t];
                if(find(res.begin(),res.end(),'#')!=res.end()){
                    unordered_set<char> temp=follows[lhs.first];
                    for(auto j:temp){
                        res.insert(j);
                    }
                }
                //res.erase(res.find('#'));
            }else{
                if(y[0]=='#'){
                    //cout<<y<<"\n";
                   unordered_set<char> temp=follows[lhs.first];
                    for(auto j:temp){
                        res.insert(j);
                    }

                   // res.erase(res.find('#'));
                   

                }else{
                    //cout<<"hi  "<<y<<"\n";
                    res.insert(y[0]);
                   
                }
            }
            /*cout<<"TESTING"<<"\n";
             cout<<lhs.first<<"=>"<<y<<"\n";


            for(auto i:res){
               
                cout<<i;
            }*/

            for(auto i:terminals){
                if(find(res.begin(),res.end(),i[0])!=res.end()){// terminal is present in first set
                    string test=lhs.first+"=>"+y;
                    //cout<<test<<"\n";
                   
                    if(find(mat[lhs.first][i].begin(),mat[lhs.first][i].end(),"_")==mat[lhs.first][i].end()){
                         remove(mat[lhs.first][i].begin(),mat[lhs.first][i].end(),"_");
                          mat[lhs.first][i].push_back(test);
                         
                    }else{
                         mat[lhs.first][i].push_back(test);
                    }
                }/*else{
                    //cout<<"_"<<"\n";
                    if(find(mat[lhs.first][i].begin(),mat[lhs.first][i].end(),"_")==mat[lhs.first][i].end() && mat[lhs.first][i].size()==0){
                            mat[lhs.first][i].push_back("_");
                    }
                        
                }*/
            }
           


        }

      
    }
      int flag=1;
      unordered_map<string,vector<string>> fin;
      for(auto row:mat){
           // non terminals
            for(auto col:row.second){
                //terminals
                
                        for(auto v:col.second){
                    //rule list
                        fin[col.first].push_back(v);
                        if(fin[col.first].size()>1){
                            flag=0;
                        }
                
                }
                
                // cout<<"\n";
            }
            // cout<<"\n";
        }

        /*if(!flag){
            cout<<"there are multiple entries in one column of parse table ";
            return mat;
        }*/

        for(auto row:mat){
            cout<<"   "<<row.first<<"   ";
        }
        cout<<"\n";
        for(auto row:fin){
           // non terminals
           cout<<row.first<<": ";
            for(auto v: row.second){
                cout<<v<<"  ";
            }
            cout<<"\n";
        }



    

}


unordered_map<string,unordered_map<string,vector<string>>> createParseTable(unordered_map<string,vector<string>> rules){

    int mx_len_first = 0, mx_len_fol = 0;
    for(auto u :rules){
        int k1 = (firsts[u.first]).size();
        int k2 = (follows[u.first]).size();
        if(k1 > mx_len_first)
            mx_len_first = k1;
        if(k2 > mx_len_fol)
            mx_len_fol = k2;
    }
  
    vector<string> ntlist ;
    for(auto rule:rules){
        ntlist.push_back(rule.first);
    }
    vector<string> terminals = term_userdef;
    terminals.push_back("$");

   
    //vector<vector<string>> mat;
    unordered_map<string,unordered_map<string,vector<string>>> mat;

    for(auto x: ntlist){
         unordered_map<string,vector<string>> temp;
        for(auto y:terminals){
            vector<string> str;
            temp[y]=str;

        }
       
        mat[x]=temp;
    }

    
    
    bool grammar_is_LL = true;

    for(auto lhs:rules){
        vector<string> rhs=lhs.second;
        //cout<<lhs.first;
        
        for(auto y:rhs){
                string t;
                t+=y[0];
                unordered_set<char> res;
                
                cout<<y<<"\n";
                

                if(find(ntlist.begin(),ntlist.end(),t)!=ntlist.end()){
                     res=firsts[t];
                     cout<<"y";
                     if(find(res.begin(),res.end(),'#')!=res.end()){
                        unordered_set<char> temp=follows[lhs.first];
                        
                        for(auto i:temp){
                            res.insert(i);
                            //cout<<"bye"<<lhs.first<<i<<"\n";
                        }
                        res.erase(res.find('#'));
                    } 
                        
                    
                    
                }else{
                    //cout<<"hi"<<"\n";
                    //cout<<y<<"\n";
                    //cout<<y[0]<<"\n";
                    if(y[0]=='#'){
                        unordered_set<char> temp=follows[lhs.first];
                        
                        for(auto i:temp){
                            res.insert(i);
                            //cout<<"bye"<<lhs.first<<i<<"\n";
                        }
                        res.erase(res.find('#'));

                    }
                     else{
                         res.insert(y[0]);
                     }
                }
                
               
                
            
            for(auto c:terminals){
                cout<<c << " == ";
                if(find(res.begin(),res.end(),c[0])!=res.end()){
                        string test=lhs.first+"->"+y;
                        
                        mat[lhs.first][c].push_back(test);
                        //cout<<lhs.first<<"=>"<<c<<"\n";
                }else{
                       mat[lhs.first][c].push_back("_");
                      // cout<<lhs.first<<"=>"<<"_"<<c<<"\n";
                }

               // cout << "###### \n";
           
            }
           



            /*cout<<y<<"=>";
                for(auto i:res){
                    cout<<i;
                }
            cout<<"\n";*/
            }
        

        
    }

    
    cout<<"PARSE TABLE"<<"\n";
    for(auto x: mat["E"]){
        cout<<"    "<<x.first<<"    ";
           
    }

    cout<<"\n";
    for(auto x: mat){
        cout<<x.first<<"  ";
       for(auto y:x.second){
           
           for(auto i:y.second){
               if(i=="_"){
                   cout<<"_"<<" ";
               }else{
                   cout<<" "<<i<<" ";
               }
               
           }
       }
       cout<<"\n";
    }
    cout<<"\n";
   

    return mat; // grammar_is_LL, terminals

}

bool validateString(unordered_map<string,vector<string>> rules,string input,unordered_map<string,unordered_map<string,vector<string>>> mat){
    stack<string> s;
    s.push("$");
    s.push(start_symbol);
   

    stack<string> buffer;
    buffer.push("$");
    for(int i=input.length()-1;i>=0;i--){
        string t;
        t+=input[i];
        if(t=="^"){
            t+=input[i+1];
            i++;
        }
        buffer.push(t);
    }
    cout<<"BUFFER ";
    /*for(auto i: buffer){
        cout<<i;
    }*/
    bool validString;
    int it=3;
    while(true){
        /*string t;
        t+=s.top();
        string y;
        y+=buffer.top();
        cout<<t<<"\n";
        cout<<y<<"\n";*/
        if(s.top()=="$" && buffer.top()=="$"){
            validString=true;
            return validString;
        }else if(find(term_userdef.begin(),term_userdef.end(),s.top())==term_userdef.end()){
            //cout<<"hello";
            if(mat[s.top()][buffer.top()].size()==1){
                //cout<<"bye";
                //s.pop();
                string temp=s.top();
                s.pop();
                for(auto i:mat[temp][buffer.top()]){
                    int id=i.find("=>");
                    cout<<  temp  << buffer.top()  <<   i   <<"\n";
                    for(int j=i.length()-1; j>=id+2;j--){
                        string x="";
                        if(i[j]=='#'){
                            continue;
                        }
                        if(i[j]=='^'){
                            string t;
                            t+=i[j-1];
                            string y;
                            y+=i[j];
                            x+=t+y;
                            j--;
                        }else{
                            x+=i[j];
                        }
                        //cout<<x<<"\n";
                        
                        s.push(x);

                        
                    }
                   
                }
            }else{
                
                cout<<"Multiple input entries"<<"\n";
                cout<<s.top()<<buffer.top();
                return false;
            }
                
        }else{
            if(s.top()==buffer.top()){
                buffer.pop();
                s.pop();
            }else{
                //cout<<t<<y<<"\n";
                cout<<"Not matching top element";
                validString=false;
                return validString;
            }
        }
        it--;
    }
}

int main() {
    unordered_map<string,vector<string>> rules;
    vector<string> rule1={"E+T","E-T","T"};
    vector<string> rule2={"T*F" , "T/F","F" };
    vector<string> rule3={"i","num","(E)" };
    //vector<string> rule4={"b" };
    //vector<string> rule5={"a" };

    rules.insert(pair<string,vector<string>> ("E",rule1));
    rules.insert(pair<string,vector<string>> ("T",rule2));
    rules.insert(pair<string,vector<string>> ("F",rule3));
    //rules.insert(pair<string,vector<string>> ("C",rule4));
    //rules.insert(pair<string,vector<string>> ("D",rule5));

    

   rules=removeLeftRecursion(rules);
   rules=removeLeftFactoring(rules);
    


    computeAllFirsts(rules);
    computeAllFollows(rules);
    unordered_map<string,unordered_map<string,vector<string>>> mat;
    cout<<"PARSE TABLE"<<"\n";
    mat=createParse(rules);

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

    bool ans=validateString(rules,input,mat);
    if(ans){
        cout<<"string is accepted";
    }else{
        cout<<"string is not accepted";
    }
    //cout<<ans;

    return 0;
}
