#include<bits/stdc++.h>
#include <Windows.h>
using namespace std;
/*
Time:
Algorithm:
Time Complexity:
*/
const int MAXTURN = 35; 
int n = 6,t,tot,deb = 0,totStep;
string skill[5],style[10],act[15],ini[10];
string fileName = "Combat";
ofstream output;
struct Style{
	int pos,ski[MAXTURN],spe[MAXTURN],tar;
	string name;
} per[10];
struct Action{
	int turn,id,step;
	string type;
};
queue<Action> q;
void judge(){
	freopen("Line.txt","r",stdin);
	// output.open("Combat.json");
//	freopen("test.out","w",stdout);
}
void pre(){
	skill[0] = "\"action\": \"DoNothing\"\n";
	skill[1] = "\"action\": \"Click\",\n\"post_delay\": 600,\n\"target\": [670,175,41,32]\n";
	skill[2] = "\"action\": \"Click\",\n\"post_delay\": 600,\n\"target\": [626,282,65,40]\n";
	skill[3] = "\"action\": \"Click\",\n\"post_delay\": 600,\n\"target\": [616,390,56,36]\n";
	style[1] = "\"action\": \"Click\",\n\"post_delay\": 600,\n\"target\": [100,585,29,28]\n";
	style[2] = "\"action\": \"Click\",\n\"post_delay\": 600,\n\"target\": [300,589,28,23]\n";
	style[3] = "\"action\": \"Click\",\n\"post_delay\": 600,\n\"target\": [500,588,24,22]\n";
	style[4] = "\"action\": \"Click\",\n\"post_delay\": 600,\n\"target\": [670,590,21,22]\n";
	style[5] = "\"action\": \"Click\",\n\"post_delay\": 600,\n\"target\": [840,591,26,26]\n";
	style[6] = "\"action\": \"Click\",\n\"post_delay\": 600,\n\"target\": [1000,590,24,24]\n";
	act[0] = "\"recognition\": \"OCR\",\n\"roi\" : [985,515,165,165],\n\"expected\": \"start\",\"replace\": [[\"Start\",\"start\"],[\"开始行动\",\"start\"],[\"开始行\",\"start\"]],\n\"action\": \"Click\",\n\"target\": [1050,580,10,10],\n\"post_delay\": 20000\n";
	act[1] = "\"recognition\": \"TemplateMatch\",\n\"roi\" : [1050,515,213,155],\n\"template\": [\"Action.png\"],\n\"action\": \"Click\",\n\"target\": [1150,580,10,10],\n\"post_delay\": 3000\n";
	ini[0] = "\"recognition\": \"OCR\",\n\"expected\": \"start\",\n\"replace\": [[\"Start\",\"start\"],[\"开始行动\",\"start\"],[\"开始行\",\"start\"]],\n";
	ini[1] = "\"recognition\": \"TemplateMatch\",\n\"roi\" : [1050,515,213,155],\n\"template\": [\"Action.png\"],\n\"target\": [1150,580,10,10],\n\"post_delay\": 3000,\n";
	ini[2] = "\"recognition\": \"TemplateMatch\",\n\"roi\" : [1050,516,213,155],\n\"template\": [\"Action.png\"],\n\"pre_delay\": 3000,\n\"target\": [1150,580,10,10]\n";
}
void debug(int i,int t){
	if (per[i].ski[t] == -1){
		cout<<per[i].name<<" is background on turn "<<t<<endl;
		return;
	}
	cout<<per[i].name<<" use Skill"<<per[i].ski[t];
	if (per[i].spe[t]) cout<<" for person "<<per[per[i].spe[t]].name;
	cout<<" at position "<<per[i].pos;
	cout<<" on turn "<<t<<endl;
}
//初步确定 Task 格式为 Turn[i]Step[j] 
void Click(int x,int t){
	q.push({t,x,++tot,"Style"});
	//此处生成交换的 json
	// output<<"\"T"<<t<<"Step"<<++tot<<"\": {"<<endl;
	// output<<"\"interrupt\": "<<"\"Style"<<x<<"\","<<endl;
	// output<<"\"next\": "
	// output<<"},"<<endl;
}
void CSki(int x,int t){
	q.push({t,x,++tot,"Skill"});
	// output<<x<<endl;
}
void preAct(int t){
	q.push({t,2,++tot,"PreAction"});
}
void Act(int t){
	q.push({t,1,++tot,"Action"});
}
void UseSkill(int i,int t){
	Click(per[i].pos,t);
	CSki(per[i].ski[t],t);
	if (per[i].spe[t]){
		Click(per[per[i].spe[t]].pos,t);
	}
}
void Swap(int x,int y,int t){
	swap(per[x].pos,per[y].pos);
	Click(per[x].pos,t),Click(per[y].pos,t);
}
void getski(Style & p,int t){
	char c = getchar(),fl = 1;
	while (c>'9' || c<'0'){
		if (c == '-') fl = -1;
		c = getchar();
//		cout<<(int)c<<endl;
	}
	p.ski[t] = (c-'0')*fl;
	c = getchar();
	p.tar = 0;
	while (c!=',' && c!='\n'){
		if (c == '*'){
			char d = getchar();
			p.spe[t] = d-'0';
		}
		if (c == '/'){
			char d = getchar();
			p.tar = d-'0';
		}
		c = getchar();
	}
}
void Tab(int x){
	for (int i=1;i<=x;i++) output<<"\t";
}
void Output(string & s){
	int len = s.length();
	// Tab(2);
	for (int i=0;i<len;i++){
		output<<s[i];
		if (i!=len-1 && s[i] == '\n'){
			Tab(2);
		}
	}
}
void parseAll(){
	cout<<"Would you like to have an entry point with a name?\n1) Yes\n2) No"<<endl;
	int uc;
	cin>>uc;
	if (uc == 1){
		cout<<"Please enter name: "<<endl;
		cin>>fileName;
	}
	string fullName = fileName+".json";
	output.open(fullName);
	output<<"{"<<endl;
	if (uc == 1){
		Tab(1);
		output<<"\""<<fileName<<"\": {"<<endl;
		Tab(2);
		Output(ini[1]);
		Tab(2);
		output<<"\"next\": "<<"\""<<fileName<<"_"<<"T"<<1<<"Step"<<1<<"\""<<endl;
		Tab(1);
		output<<"},"<<endl;
	}
	while (!q.empty()){
		Action x = q.front(),y = {0,0,0,""};
		q.pop();
		if (!q.empty()) y = q.front();
		if (deb){
			cout<<"Turn "<<x.turn<<" Step "<<x.step<<":\n";
		}
		Tab(1);
		output<<"\""<<fileName<<"_"<<"T"<<x.turn<<"Step"<<x.step<<"\": {"<<endl;
		if (y.turn){
			Tab(2);
			output<<"\"next\": "<<"\""<<fileName<<"_"<<"T"<<y.turn<<"Step"<<y.step<<"\","<<endl;
		}
		// if (x.turn == 1 && x.step == 2) cout<<x.id<<endl;
		if (x.type == "Skill"){
			if (deb) cout<<"Use skill "<<x.id<<endl;
			Tab(2);
			Output(skill[x.id]);
			// output<<skill[x.id];
		}
		else if (x.type == "Style"){
			if (deb) cout<<"Click style "<<x.id<<endl;
			Tab(2);
			Output(style[x.id]);
			// output<<style[x.id];
		}
		else if (x.type == "Action"){
			if (deb) cout<<"Combat"<<endl;
			Tab(2);
			Output(act[x.id]);
			// output<<act[x.id];
		}
		else if (x.type == "PreAction"){
			if (deb) cout<<"PreAct"<<endl;
			Tab(2);
			Output(ini[x.id]);
		}
		else{
			cout<<"Invalid type!"<<endl;
		}
		Tab(1);
		output<<"}";
		if (y.turn) output<<","<<endl;
		else output<<endl;
		totStep++;
	}
	output<<"}";
}
int main(){
	judge();
	pre();
	SetConsoleOutputCP(CP_UTF8);
	for (int i=1;i<=n;i++){
		cin>>per[i].name;
		per[i].pos = i;
	}
	//输入回合数 
	cin>>t;
	for (int cur=1;cur<=t;cur++){
		tot = 0;
		preAct(cur);
		for (int i=1;i<=n;i++){
			getski(per[i],cur);
			if (per[i].tar){
				for (int j=1;j<=n;j++){
					if (per[j].pos == per[i].tar){
						Swap(i,j,cur);
					}
				}
			}
		}
		for (int i=1;i<=n;i++){
			if (per[i].ski[cur]>=0){
				if (per[i].pos>3){
					for (int j=1;j<=n;j++){
						if (per[j].ski[cur] == -1 && per[j].pos<=3){
							Swap(i,j,cur);
							break;
						}
					}
				}
				if (per[i].pos>3){
					cout<<"Wrong position for person "<<per[i].name<<" at turn "<<cur<<endl;
				}
			}
			// debug(i,cur);
		}
		for (int i=1;i<=n;i++){
			if (per[i].pos<=3){
				if (per[i].ski[cur]!=0) UseSkill(i,cur);
			}
		}
		Act(cur);
	}
	freopen("CON","r",stdin);
	cout<<"Parsing Line.txt finished"<<endl;
	parseAll();
	cout<<"Total stpes: "<<totStep<<endl;
	system("pause");
	return 0;
}

