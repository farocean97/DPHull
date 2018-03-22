#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>

#define EPSILON 0.3
#define EPSILON_SQ 0.09

#define HULL_MAX 20
#define HULL_MAX_2 40
#define HULL_MAX_3 60

#define PUSH_OP 0
#define TOP_OP 1
#define BOT_OP 2

#define XX 0
#define YY 1
#define WW 2

typedef double POINT[2];
typedef double HOMOG[3];

typedef struct {
	int top; //top index
	int bot; //bot index
	int hp;  //operation index from 0...
	int op[HULL_MAX_3];            //operation type: push_op, top_op, bot_op
	POINT *elt[HULL_MAX_2];       // double end array storing vertex forming convex
	POINT *helt[HULL_MAX_3];      // Storing the history of vertex operated on
} PATH_HULL;

#define MIN(a,b) (a<b?a:b)
#define MAX(ab,b) (a>b?a:b)
#define SGN(a) (a>=0)




//#define DOTPROD_2CH(p,q)  (q[WW]+p[XX]*q[XX]+p[YY]*q[YY])

//#define LEFT_OF(a, b, c) ((((*a)[XX] - (*c)[XX])*((*b)[YY] - (*c)[YY])) >= (((*b)[XX] - (*c)[XX])*((*a)[YY] - (*c)[YY])))

//#define SLOPE_SIGN(h,p,q,l) SGN((l[XX]* ((*h->elt[q])[XX]-(*h->elt[p])[XX]) + l[YY]* ((*h->elt[q])[YY]-(*h->elt[p])[YY]) ))




//#define Hull_Pop_Top(h) \
//	h->helt[++h->hp] = h->elt[h->top--];\
//	h->op[h->hp] = TOP_OP;

//#define Hull_Pop_Bot(h) \
//	h->helt[++h->hp] = h->elt[h->bot++];\
//	h->op[h->hp] = BOT_OP;

//#define Hull_Init(h,e1,e2) \
//	h->elt[HULL_MAX] = e1;\
//	h->elt[h->top = HULL_MAX+1] = h->elt[h->bot = HULL_MAX-1] = h->helt[h->hp=0] = e2;\
//	h->op[0] = PUSH_OP;

POINT *V;
int n;
PATH_HULL *left, *right;
POINT *PHtag;


int LEFT_OF(POINT *a, POINT *b, POINT *c) {
	return (((*a)[XX] - (*c)[XX])*(((*b)[YY] - (*c)[YY])) >= (((*b)[XX] - (*c)[XX])*((*a)[YY] - (*c)[YY]))); //CA * CB >0
}

int SLOPE_SIGN(PATH_HULL *h, int p,int q, HOMOG l) {
	return SGN((l[XX]* ((h->elt[q])[XX]-(h->elt[p])[XX]) + l[YY]* ((h->elt[q])[YY]-(h->elt[p])[YY]) ));
}


void CROSSPROD_2CCH(POINT p,POINT q, HOMOG *r) {
	(*r)[WW] = p[XX]*q[YY]- p[YY]*q[XX];
	(*r)[XX] = -q[YY]+p[YY];
	(*r)[YY] = q[XX]-p[XX];
}

//dist from point C to line AB :  (AC*AB)/ |AB| 
double DOTPROD_2CH(POINT p, HOMOG q) { 
	return (q[WW]+p[XX]*q[XX]+p[YY]*q[YY]); //Cross product AC * AB
}


void  Hull_Push(PATH_HULL *h, POINT *e) {
	h->elt[++h->top] = h->elt[--h->bot] = h->helt[++h->hp] = e;
	h->op[h->hp] = PUSH_OP;
}


void Hull_Pop_Top(PATH_HULL *h) {
	h->helt[++h->hp] = h->elt[h->top];
	h->elt[h->top] = NULL; //remove the top 
	h->top--;
	h->op[h->hp] = TOP_OP;
}

void Hull_Pop_Bot(PATH_HULL *h) {
	h->helt[++h->hp] = h->elt[h->bot];
	h->elt[h->bot] = NULL; //remove the bot
	h->bot++;
	h->op[h->hp] = BOT_OP;
}

void Hull_Init(PATH_HULL *h, POINT *e1, POINT *e2) {
	h->elt[HULL_MAX] = e1;
	h->top = HULL_MAX+1;
	h->elt[h->top] = e2;
	h->bot = HULL_MAX-1;
	h->elt[h->bot] = e2;
	h->hp=0;
	h->helt[h->hp] = e2;
	h->op[0] = PUSH_OP;
}


void Find_Extreme (PATH_HULL *h, HOMOG line, POINT **e, double *dist) {
	int sbase, sbrk, mid,lo,m1, brk,m2,hi;
	double d1, d2;
	if((h->top - h->bot)>6) {
		lo = h->bot;
		hi = h->top-1;
		sbase = SLOPE_SIGN(h,hi,lo,line);
		do {
			brk = (lo +hi)/2;
			sbrk = SLOPE_SIGN(h,brk,brk+1,line);
			if(sbase == sbrk) {
				if(sbase == SLOPE_SIGN(h,lo,brk+1,line)) lo = brk+1;
				else hi = brk;
			}
		}
		while (sbase == sbrk);
		
		m1 = brk;
		while (lo <m1) {
			mid = (lo + m1)/2;
			if(sbase == SLOPE_SIGN(h,mid, mid+1,line)) lo = mid+1;
			else m1 = mid;
		}
		m2= brk;
		while (m2 <hi) {
			mid = (m2+hi) /2;
			if(sbase == SLOPE_SIGN(h,mid,mid+1,line)) hi = mid;
			else m2 = mid+1;
		}
		d1 = fabs(DOTPROD_2CH(*h->elt[lo],line));
		d2 = fabs(DOTPROD_2CH(*h->elt[m2],line));
		if(d1>d2) {
			*dist = d1;
			*e = h->elt[lo];
		}else {
			*dist = d2;
			*e = h->elt[m2];
		}
	} else {
		//brute force
		*dist = 0;
		for(mid = h->bot; mid<h->top;mid++){
			d1 = fabs(DOTPROD_2CH(*h->elt[mid],line));
			if(d1>*dist) {
				*dist = d1;
				*e = h->elt[mid];
			}
		}
	}
}

void Hull_Add(PATH_HULL *h, POINT *p) {
	int topflag, botflag;
	topflag = LEFT_OF(h->elt[h->top],h->elt[h->top-1],p);
	botflag = LEFT_OF(h->elt[h->bot+1],h->elt[h->bot],p);
	if(topflag || botflag) {
		while(topflag) {
			Hull_Pop_Top(h);
			topflag = LEFT_OF(h->elt[h->top],h->elt[h->top-1],p);
		}

		while(botflag) {
			Hull_Pop_Bot(h);
			botflag = LEFT_OF(h->elt[h->bot+1],h->elt[h->bot],p);
		}
		Hull_Push(h,p);
	}
}

void Build(POINT *i, POINT *j)  {
	POINT *k;
	PHtag = i + (j-i)/2;
	//Hull_Init(left,PHtag,PHtag-1);
	Hull_Init(left,PHtag,PHtag-1);
	for(k = PHtag-2; k >= i; k--)
		Hull_Add(left,k);
	Hull_Init(right,PHtag,PHtag+1);
	for(k = PHtag+2; k <= j; k++)
		Hull_Add(right,k);	
}

void Split(PATH_HULL *h,POINT *e) {
	POINT *tmpe;
	int tmpo;
	tmpo = h->op[h->hp];
	tmpe = h->helt[h->hp];
	while( h->hp >=0 && (tmpe != e || tmpo != PUSH_OP))
	{
		h->hp--;
		switch (tmpo) {
			case PUSH_OP: //0
				h->top--;
				h->bot++;
				break;
			case TOP_OP : //1
				h->elt[++h->top] = tmpe; 
				break;
			case BOT_OP : //2
				h->elt[--h->bot] = tmpe;
				break;
		}
		tmpo = h->op[h->hp];
	    tmpe = h->helt[h->hp];
	}

}

void OutputVertex (POINT *p) {
	printf("x = %f \t y = %f\n", (*p)[0], (*p)[1]);
}

POINT *DPHull(POINT *i,POINT *j) {
	POINT *lextr, *rextr;
	double ldist, rdist;
	HOMOG line;
	double len_sq;
	POINT *tmp;
	CROSSPROD_2CCH(*i,*j,&line);
	len_sq = line[XX]*line[XX] + line[YY]*line[YY];

	if((j-i)<1) {
		return j;
	}else {
		Find_Extreme(left, line, &lextr,&ldist);
		Find_Extreme(right, line, &rextr,&rdist);
		if(ldist <= rdist) {
			if(rdist*rdist<= EPSILON_SQ*len_sq)
				return (j);
			else {
				if(PHtag == rextr){
					Build(i,rextr);
				}else {
					Split(right,rextr);
				}
				OutputVertex(DPHull(i,rextr));
				Build(rextr,j);
				return(DPHull(rextr,j));
			}
		}else {
			if(ldist*ldist<= EPSILON_SQ*len_sq)
				return (j);
			else {
				Split(left,lextr);
				tmp = DPHull(lextr,j);
				Build(rextr,j);
				OutputVertex(DPHull(i,lextr));
				return tmp;
			}

		}
	}

}


void main() {
	POINT p1 = {1,2};
	POINT p2 = {2,1};
	POINT p3 = {3,3.5};
	POINT p4 = {4, 2};
	POINT p5 = {5,6};
	POINT p6 = {6,2};
	POINT p7 = {7,1};
	POINT p8 = {8,3.5};
	POINT p9 = {9, 2};
	POINT p10 ={10,6};
	POINT *V;
	POINT *VNew;
	POINT *a,*b;
	PATH_HULL ph,ph2;
	int i;
	int n = 10;
	V = (POINT*) malloc (10*sizeof(POINT));
	memcpy(V[0],p1,sizeof(POINT));
	memcpy(V[1],p2,sizeof(POINT));
	memcpy(V[2],p3,sizeof(POINT));
	memcpy(V[3],p4,sizeof(POINT));
	memcpy(V[4],p5,sizeof(POINT));
	memcpy(V[5],p6,sizeof(POINT));
	memcpy(V[6],p7,sizeof(POINT));
	memcpy(V[7],p8,sizeof(POINT));
	memcpy(V[8],p9,sizeof(POINT));
	memcpy(V[9],p10,sizeof(POINT));

	//double *V[10] = {p1,p2,p3,p4,p5,p6,p7,p8,p9,p10};
	b = V+( (V+10-1)-V)/2;
	for(a=V;a<=b;a++){
		//printf("a=%d\n",a);
		printf("a=%f\n", (*a)[1]);
	}
	
	ph.bot = 0;
	ph.top = 0;
	ph.hp = 0;
	ph2.bot = 0;
	ph2.top = 0;
	ph2.hp = 0;
	left = &ph;
	right = &ph2;

	//build left hull and right hull
	Build(V,V+10-1);

	OutputVertex(V);

	VNew = DPHull(V, V+10-1);

	OutputVertex(VNew);

    printf("V[5].X = %f\n",V[4][0]);
	getchar();
}







