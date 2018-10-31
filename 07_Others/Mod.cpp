int add(int x,int y){return (x+=y)>=MOD?x-MOD:x;}
int sub(int x,int y){return (x-=y)<0?x+MOD:x;}
int mul(int x,int y){return 1ll*x*y%MOD;}
