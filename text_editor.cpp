/*input
1
ashish 0
1
vishal 6
1
singh 6
2 6
2 6
3
3
3
3
4
4
5
0 5
6 11
7 ash
7 vishal
0
*/
#include<bits/stdc++.h>
#include<algorithm>
#include <fstream>
#include <sstream>
#include <string>
//#include <ext/pb_ds/assoc_container.hpp>
//#include <ext/pb_ds/tree_policy.hpp>
//#include <functional>
//using namespace __gnu_pbds;
using namespace std;
#define pb push_back
#define pf push_front
#define pob pop_back
#define pof pop_front
#define is insert
#define rep1(i,a,b) for(long long i=a;i<=b;i++)
#define mp make_pair
#define mh make_heap
#define F first
#define S second
//#define fin cin
//#define fout cout
#define file ifstream fin("input.txt");ofstream fout("output.txt");
#define fast ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#define fr(n) for(long long i=0;i<n;i++)
#define rep(i,a,b) for(long long i=a;i<b;i++)
#define ALL(x) (x).begin(), (x).end()
typedef long long int ll;
typedef long double ld;
#define lb lower_bound
#define ub uper_bound
#define bs lower_bound
//#define db(i) cout<<i<<endl;
typedef pair<ll,ll> pairs;
typedef vector<ll> vi;
typedef vector<pairs> vpair;
// find_by_order()  // order_of_key
//typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update>ordered_set;
// typedef tree<pair<int,int>, null_type, less<pair<int,int>>, rb_tree_tag,
// tree_order_statistics_node_update> pbds;
struct compare{
  bool operator()(const pairs &a, const pairs &b)const{
    if(a.first == b.first) return a.second < b.second;
    return a.first > b.first;
  }
};

struct trie
{
	trie* c[256];
	vector<int>index;
	bool leaf;
};
//ukkonen algorithm
class editor
{
	string s,copy_string,st;
	stack<pair<char,pair<int,int> > > undo,redo;
	int pos,siz;
	
	trie* root;
	public:
	editor();
	void push_word(int position,string st);
	void del(int position);
	void undo_moves();
	void redo_moves();
	void copy(int position,int number);
	void paste(int position);
	void search(string ss);

	void auto_fill(string s);
	void build_trie();
	void insert(trie* root,string st,int pos);
	trie* new_node();
};
editor::editor()
{

	this->pos=0;this->siz=0;
	cout<<"constructor called"<<pos<<" "<<siz<<endl;
}
void editor :: push_word(int position,string new_string)
{
	if(s.size()>=position)
	st=s.substr(0,position)+new_string+s.substr(position);
	else
		st=s+new_string;
	s=st;
	st.clear();
	for(int i=0;i<new_string.size();i++)
		undo.push(mp(new_string[i],mp(position++,1)));
	cout<<s<<endl;
}
void editor:: del(int position)
{
	if(position>s.size())return ;
	undo.push(mp(s[position],mp(position,0)));
	s.erase(s.begin()+position);
	cout<<s<<endl;
}
void editor::undo_moves()
{
	string ns;
	if(undo.size()==0)return ;
	redo.push(undo.top());
	int ind=undo.top().S.F,flag=undo.top().S.S;char c=undo.top().F;
	if(flag==1)
	s.erase(s.begin()+ind);
	else
	{ns+=c;s.insert(ind,ns);}
	undo.pop();
	cout<<s<<endl;
}
void editor:: redo_moves()
{
	string ns;
	if(redo.size()==0)return ;
	undo.push(redo.top());
	int ind=redo.top().S.F,flag=redo.top().S.S;char c=redo.top().F;
	if(flag==0)
	s.erase(s.begin()+ind);
	else
	{ns+=c;s.insert(ind,ns);}
redo.pop();
cout<<s<<endl;
}

void editor::copy(int sp,int ep)
{
	copy_string.erase();
	for(sp;sp<=ep;sp++)
		copy_string+=s[sp];
	cout<<copy_string<<endl;
}
void editor::paste(int position)
{
	st.erase();
	st=s.substr(0,position)+copy_string+s.substr(position);
	s=st;
	cout<<s<<endl;
}


trie* editor::new_node()
{
	trie* temp=new trie();
	for(int i=0;i<256;i++)
		temp->c[i]=0;
	temp->leaf=0;
	return temp;
}
void editor::insert(trie* root_,string st,int position)
{
	for(int i=0;i<st.size();i++)
	{
		if(root_->c[st[i]]==0)
			root_->c[st[i]]=new_node();
		root_=root_->c[st[i]];
		root_->index.push_back(position++);
	}
}

void editor::build_trie()
{
	root=0;
	root=new_node();
	for(int i=0;i<s.size();i++)
		insert(root,s.substr(i),i);
}
void editor::search(string st)
{
	build_trie();
	for(int i=0;i<st.size();i++)
	{
		if(root->c[st[i]]==0)
		{
			cout<<"not found"<<endl;
			return ;
		}
		root=root->c[st[i]];
	}
	cout<<"found at :"<<endl;
	int n=st.size();
	n-=1;
	for(int i=0;i<root->index.size();i++)
	{
		cout<<(root->index[i])-n<<" "<<root->index[i]<<endl;
	}
	return ;
}

int main()
{
	editor loki;
	int n=1;
	while(n)
	{
		cout<<"press for the follwing action :\n 0 : Exit \n 1 : Push String \n 2 : Delete character \n 3 : undo last moves \n 4 : redo last moves \n 5 : copy character \n 6 : paste character \n 7 : search pattern"<<endl;
		cin>>n;
		if(n==0)
			break;
		else if(n==1)
		{
			int position;string st;
			cin>>st>>position;
			loki.push_word(position,st);
		}
		else if(n==2)
		{
			int position;cin>>position;
			loki.del(position);
		}
		else if(n==3)
		{
			loki.undo_moves();
		}
		else if(n==4)
			loki.redo_moves();
		else if(n==5)
		{
			int sp,noc;cin>>sp>>noc;
			loki.copy(sp,noc);

		}
		else if(n==6)
		{
			int pos;cin>>pos;
			loki.paste(pos);
		}
		if(n==7)
		{
			string patt;cin>>patt;
			loki.search(patt);
		}

	}
}

