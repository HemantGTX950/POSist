#include<bits/stdc++.h>
using namespace std;
struct Owner{
	string name;
	string address;
	string mobile;
	string phone;
	float value;
	string password;
	int ownerNum;
	
};
struct Node{
	time_t dt;
	Owner *owner;
	int nodeNum;
	int nodeId;
	Node *refNodeId;
	vector<int> childNodeId;
	vector<Node*> refChildNodeId;
	
};
Node *getNode(int num,Owner *own){
	Node *np=new Node;
	np->dt=time(0);
	np->owner=own;
	np->nodeNum=num;
	np->nodeId=(num);
	vector<Node*> v;
	np->refChildNodeId=v;
	np->refNodeId=NULL;
	vector<int> s;
	np->childNodeId=s;
	return np;
}

void query3(Node *child,int id,vector<Node*> &v){
	for(int i=0;i<v.size();i++){
		if(v[i]->nodeId==id){
			v[i]->refChildNodeId.push_back(child);
			v[i]->childNodeId.push_back(child->nodeId);
			child->refNodeId=v[i];
			break;
		}	
	}
}
string encrypt(string s,int n){
	string sol=s;
	for(int i=0;i<sol.length();i++){
		sol[i]+=n;
	}
	return sol;
}
string decrypt(string data,int n){
	string sol=data;
	for(int i=0;i<sol.length();i++){
		sol[i]-=n;
	}
	return sol;
}
Owner *getOwner(int num,string name, string address, string mobile, string phone, float value,string pass){
	
	Owner *own=new Owner;
	own->ownerNum=num;
	own->address=encrypt(address,num);
	own->address=encrypt(name,num);
	own->address=encrypt(mobile,num);
	own->address=encrypt(phone,num);
	own->value=value;
	own->password=encrypt(pass,num);
	return own;	
}
bool query4(vector<Owner*> &owners,Owner *currOwner,vector<Node*> &v){
	cout<<"enter NodeId: ";
			int id;
			cin>>id;
			bool f=false;
			for(int i=0;i<v.size();i++){
				if(v[i]->nodeId==id){
					if(currOwner==v[i]->owner){
						f=true;
					}
					break;
				}	
			}
		
			return f;
}
void query5(vector<Owner*> &owners, Owner *currOwner, vector<Node*> &v){
	cout<<"Enter nodeId of node to be deleted: "<<endl;
	int id;
	cin>>id;
	bool f=false;
	for(int i=0;i<v.size();i++){
		if(v[i]->nodeId==id){
			if(query4(owners,currOwner,v)){
				
				f=true;
				Node *parent=v[i]->refNodeId;
				vector<Node*> child=parent->refChildNodeId;
				for(int k=0;k<child.size();k++){
					if(child[k]->nodeId==id){
						child.erase(child.begin()+i);
						
						break;
					}
				}
				
			}else{
				cout<<"you are not the owner of this node"<<endl;
				return;
			}
			break;
		}
	}
	if(f){
		cout<<"node removed"<<endl;
	}else{
		cout<<"not found"<<endl;
	}
}
void query6(vector<Owner*> &owners,Owner *currOwner, vector<Node*> &v){
	cout<<"Enter nodeId and userId: "<<endl;
	int id,userId;
	cin>>id>>userId;
	bool f=false;
	for(int i=0;i<v.size();i++){
		if(v[i]->nodeId==id){
			if(query4(owners,currOwner,v)){
				
				
				Node *np=v[i];
				for(int k=0;k<owners.size();k++){
					if(owners[k]->ownerNum==userId){
						np->owner=owners[k];
						f=true;
						break;
					}	
				}
				
			}else{
				cout<<"you are not the owner of this node"<<endl;
				return;
			}
			break;
		}
	}
	if(f){
		cout<<"node Owner changed"<<endl;
	}else{
		cout<<"node not found"<<endl;
	}
}
void query7(vector<Node*> v){
	
}
int main(){
	St:
    int num=0,nOwners=0;
    vector<Node*> v;
    vector<Owner*> owners;
    int q;

    Owner *currOwner;
    bool f=false;
    
    while(!f){
    	cout<<"Enter 1 to login 2 to signup";
    	
    cin>>q;
    	if(q==1){
			cout<<"enter password and key";
	    	string pass;
	    	int key;
	    	cin>>pass;
	    	cin>>key;
	    	for(int i=0;i<owners.size();i++){
	    		if(owners[i]->ownerNum==key){
	    			if(pass==decrypt(owners[i]->password,owners[i]->ownerNum)){
	    				f=true;
	    				currOwner=owners[i];
	    				break;
					}
				}
			}
			cout<<"unable to login"<<endl;
		}else{
			cout<<"Enter name, address, mobile,phone, value, password:"<<endl;
			string name,address,mobile,phone,pass;
			float value;
			cin>>name>>address>>mobile>>phone;
			cin>>value;
			cin>>pass;
			currOwner=getOwner(nOwners++,name, address, mobile, phone, value,pass);
			owners.push_back(currOwner);
			cout<<"your key is "<<currOwner->ownerNum<<endl;
			f=true;
		}
	}
    
    
    while(1){
    	cout<<"Enter Query: ";
		cin>>q;
		if(q==1){
			//push a hardcoded first node 
			v.push_back(getNode(num++,currOwner));
		}else if(q==2){
			//push a set of first nodes
			int n=0;
			cout<<"Enter number of nodes: ";
			cin>>n;
			for(int i=0;i<n;i++){
				v.push_back(getNode(num++,currOwner));	
			}
			cout<<"nodes pushed"<<endl;
		}else if(q==3){
			//adding node to any node
			Node *np=getNode(num++,currOwner);
			v.push_back(np);
			cout<<"Enter NodeId: ";
			int id;
			cin>>id;
			query3(np,id,v);
		}else if(q==4){
			//verify owner
			bool f=query4(owners,currOwner,v);
			if(f){
				cout<<"you are the owner!"<<endl;
			}else{
				cout<<"you are not the owner"<<endl;
			}	
		}else if(q==5){
			//break up a node 
			query5(owners,currOwner,v);
			
		}else if(q==6){
			// transfer owner
			query6(owners,currOwner,v);
			
			
		}else if(q==7){
			//longest chain of main node
			query7(v);
			
		}else if(q==8){
			//longest chain of sub node
			
		}else if(q==9){
			//merge nodes
			
		}else if(q==10){
			//log out
			currOwner=NULL;
			goto St;
		}else {
			
		}
	}
    return 0;
}
