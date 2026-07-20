
struct AC {
    static const int N=26;
    struct Node {
        int len,link,out,tag;
        array<int,N> nxt;
        Node() : len(0),link(0),out(0),tag(0),nxt{} {};
    };
    vector<Node> t;
    AC() {init();}
    
    void init() {
        t.assign(2,Node());
        t[0].nxt.fill(1);
        t[0].len=-1;
    }
    
    int newNode() {
        t.emplace_back();
        return t.size()-1;
    }
    
    int insert(string &a,int id=1) {
        int p=1;
        for (auto c : a) {
            int u=c-'a';
            if (next(p,u) == 0) {
                t[p].nxt[u]=newNode();
                t[next(p,u)].len=t[p].len+1;
            }
            p=next(p,u);
        }
        t[p].tag=id;
        return p;
    }
    
    void work() {
        queue<int> q;
        q.push(1);
        while (q.size()) {
            int x=q.front();
            q.pop();
            int f=link(x);
            t[x].out=t[f].tag ? f : t[f].out;
            for (int i=0;i<N;i++) {
                if (next(x,i) == 0) t[x].nxt[i]=next(link(x),i);
                else {
                    t[next(x,i)].link=next(link(x),i);
                    q.push(next(x,i));
                }
            }
        }
    }
    
    int next(int p,int x) {return t[p].nxt[x];}
    int link(int p) {return t[p].link;}
};
