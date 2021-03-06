// Geometry Templates>>>>>>>>>>>>
#include<stdio.h>
#include<string.h>
#include<vector>
#include<math.h>
#include<algorithm>
using namespace std;

//Macro........
#define maxm 100100
#define pi acos(-1.0)
#define eps 1e-9
#define sq(a) ((a)*(a))
#define dist(a,b) (sq(a.x-b.x) + sq(a.y-b.y))
#define iseq(a,b) (fabs(a-b)<eps)
#define mini(a,b) a<b ? a:b
#define maxi(a,b) a>b ? a:b
#define area_t(x1,y1,x2,y2,x3,y3) ( x1*(y2-y3) + x2*(y3-y1) + x3*(y1-y2) )
#define spDist(lat1,long1,lat2,long2,r) ( r * acos( sin(lat1) * sin(lat2) + cos(lat1) * cos(lat2) * cos(long1-long2) ) )

// Template........
template< class T > bool inside(T a, T b, T c) { return a<=b && b<=c; }

// Structure....
struct point { // Creates normal 2D point
    double x, y;
    point() {}
    point( double xx, double yy ) { x = xx, y = yy; }
};

struct line { // Creates a line with equation ax + by + c = 0
    double a, b, c;
    line() {}
    line( point p1,point p2 ) {
        a = p1.y - p2.y;
        b = p2.x - p1.x;
        c = p1.x * p2.y - p2.x * p1.y;
    }
};
struct circle { // Creates a circle with point 'center' as center and r as radius
    point center;
    double r;
    circle() {}
    circle( point P, double rr ) { center = P; r = rr; }
};
struct segment { // Creates a segment with two end points -> A, B
    point A, B;
    segment() {}
    segment( point P1, point P2 ) { A = P1, B = P2; }
};
inline double distancepp( point a, point b ) {
    return sqrt( ( a.x - b.x ) * ( a.x - b.x ) + ( a.y - b.y ) * ( a.y - b.y ) );
}
inline double sq_distance( point a, point b ) {
    return ( a.x - b.x ) * ( a.x - b.x ) + ( a.y - b.y ) * ( a.y - b.y );
}
inline double distancepl( point P, line L ) {
    return fabs( L.a * P.x + L.b * P.y + L.c ) / sqrt( L.a * L.a + L.b * L.b );
}
inline double cross( point p0, point p1, point p2 ) {
    return( ( p1.x - p0.x ) * ( p2.y - p0.y ) - ( p2.x - p0.x ) * ( p1.y - p0.y ) );
}
double areaPoly(point P[],int n){
    double area=0;
    for( int i = 0, j = n - 1; i < n; j = i++ ) area += P[j].x * P[i].y - P[j].y * P[i].x;
    return fabs(area)*.5;
}
bool sort_x(point a,point b){
    if(iseq(a.x,b.x)) return a.y<b.y;
    return a.x<b.x;
}
bool sort_y(point a,point b){
    if(iseq(a.y,b.y)) return a.x<b.x;
    return a.y<b.y;
}
//end>>>>>

int n,nc;
point p[maxm],c[maxm]; // p=all points. c=convex_hull points

//comp = polar angle>>>(convex_hull)
bool comp(point a,point b){

    double d = cross(p[0], a, b);
    if(d<0) return false;
    if(iseq(d,0) && dist(p[0], b) < dist(p[0], a)) return false;
    return true;
}

// COnvex_hull ............
void convex_hull(point c[],int &n,int &nc);

double ang(point a,point b,point c){    //returns angle <bac
    double absq = sq_distance(a , b);
    double bcsq = sq_distance(c , b), acsq = sq_distance(a , c);
    double cosp = (absq+acsq - bcsq)/(2.0*sqrt(absq * acsq) );
    return acos(cosp);
}
double conv(double theta){

    double ret=180; ret/=pi; return ret*theta;
}

bool normal(const point &a, const point &b) {   return (iseq(a.x,b.x) ? a.y < b.y : a.x < b.x);}
bool issame(const point &a, const point &b) {   return (iseq(a.x,b.x) && iseq(a.y,b.y));}
void makeUnique(int &np) {  sort(&p[0], &p[np], normal);    np = unique(&p[0], &p[np], issame) - p;}

int main(){

    int i,j,k,l,test,t=1;

    //freopen("in.txt","r",stdin);

    while(scanf("%d",&n)==1){

        if(!n) break;

        for(i=0;i<n;i++){
            scanf("%lf %lf",&p[i].x,&p[i].y);
        }
        nc=0;
        convex_hull(c,n,nc);
        if(n==nc){
            printf("No\n");
        }
        else printf("Yes\n");
    }


    return 0;
}


void convex_hull(point ans[],int &n,int &nc){

    makeUnique(n);

    int i,pos = 0;
    for(i=1; i<n; i++)
        if(p[i].y<p[pos].y || (p[i].y==p[pos].y && p[i].x<p[pos].x))
            pos = i;
    swap(p[0], p[pos]);
    sort(p+1, p+n, comp);

    ans[0] = p[0];
    if(n>=2)    ans[1] = p[1];
    for(i=nc=2; i<n; i++)
    {
        while(nc>=2 && cross(ans[nc-2], ans[nc-1], p[i])<0||iseq(cross(ans[nc-2], ans[nc-1], p[i]),0)) nc--;
        ans[nc++] = p[i];
    }
    if(n==1)        nc=1;
    else if(nc==2)
    {
        if(p[0].x == p[1].x && p[0].y == p[1].y)   nc=1;
    }


}


