
// Main header
#include "eve/math/MatrixDecompose.h"


///////////////////////////////////////////////////////////////////////////////////////////////////
//		OBJECTS
///////////////////////////////////////////////////////////////////////////////////////////////////


typedef eve::quatf HVect;
typedef float _HMatrix[4][4];
typedef struct
{
	eve::vec4f t;		// Translation Component;
	eve::quatf q;        // Essential Rotation
	eve::quatf u;        // Stretch rotation
	HVect k;        // Sign of determinant
	float f;       // Sign of determinant
} _affineParts;


enum QuatPart {X, Y, Z, W};

#define SQRTHALF_D	(0.7071067811865475244)
#define SQRTHALF_F	(0.707106f)
//static eve::quatf qxtoz(0,SQRTHALF_D,0,SQRTHALF_D);
//static eve::quatf qytoz(SQRTHALF_D,0,0,SQRTHALF_D);
//static eve::quatf qppmm( 0.5f, 0.5f,-0.5f,-0.5f );
//static eve::quatf qpppp( 0.5f, 0.5f, 0.5f, 0.5f );
//static eve::quatf qmpmm(-0.5f, 0.5f,-0.5f,-0.5f );
//static eve::quatf qpppm( 0.5f, 0.5f, 0.5f,-0.5f );
//static eve::quatf q0001( 0.0f, 0.0f, 0.0f, 1.0f );
//static eve::quatf q1000( 1.0f, 0.0f, 0.0f, 0.0f );
static eve::quatf qxtoz( SQRTHALF_F,		0.0f, SQRTHALF_F, 0.0f );
static eve::quatf qytoz( SQRTHALF_F,		SQRTHALF_F, 0.0f, 0.0f );
static eve::quatf qppmm( -0.5f,	 0.5f, 0.5f,-0.5f );
static eve::quatf qpppp(  0.5f,	 0.5f, 0.5f, 0.5f );
static eve::quatf qmpmm( -0.5f,	-0.5f, 0.5f,-0.5f );
static eve::quatf qpppm( -0.5f,	 0.5f, 0.5f, 0.5f );
static eve::quatf q0001(  1.0f,	 0.0f, 0.0f, 0.0f );
static eve::quatf q1000(  0.0f,	 1.0f, 0.0f, 0.0f );

/** Copy nxn matrix A to C using "gets" for assignment **/
#define matrixCopy(C, gets, A, n) {int32_t i, j; for (i=0;i<n;i++) for (j=0;j<n;j++)\
    C[i][j] gets (A[i][j]);}

/** Copy transpose of nxn matrix A to C using "gets" for assignment **/
#define mat_tpose(AT,gets,A,n) {int32_t i,j; for(i=0;i<n;i++) for(j=0;j<n;j++)\
    AT[i][j] gets (A[j][i]);}

/** Fill out 3x3 matrix to 4x4 **/
#define mat_pad(A) (A[W][X]=A[X][W]=A[W][Y]=A[Y][W]=A[W][Z]=A[Z][W]=0,A[W][W]=1)


/** Assign nxn matrix C the element-wise combination of A and B using "op" **/
#define matBinop(C,gets,A,op,B,n) {int32_t i,j; for(i=0;i<n;i++) for(j=0;j<n;j++)\
    C[i][j] gets (A[i][j]) op (B[i][j]);}

/** Copy nxn matrix A to C using "gets" for assignment **/
#define mat_copy(C,gets,A,n) {int32_t i,j; for(i=0;i<n;i++) for(j=0;j<n;j++)\
    C[i][j] gets (A[i][j]);}

/** Multiply the upper left 3x3 parts of A and B to get AB **/
void mat_mult(_HMatrix A, _HMatrix B, _HMatrix AB)
{
    int32_t i, j;
    for (i=0; i<3; i++) 
		for (j=0; j<3; j++)
			AB[i][j] = A[i][0]*B[0][j] + A[i][1]*B[1][j] + A[i][2]*B[2][j];
}

float mat_norm(_HMatrix M, int32_t tpose)
{
    int32_t i;
    float sum, max=0.0;
    for (i=0; i<3; i++) 
	{
        if (tpose) sum = eve::math::abs(M[0][i])+eve::math::abs(M[1][i])+eve::math::abs(M[2][i]);
        else       sum = eve::math::abs(M[i][0])+eve::math::abs(M[i][1])+eve::math::abs(M[i][2]);

        if (max<sum) max = sum;
    }
    return max;
}

float norm_inf(_HMatrix M) {return mat_norm(M, 0);}
float norm_one(_HMatrix M) {return mat_norm(M, 1);}

static _HMatrix mat_id = 
	{ {1,0,0,0}
	, {0,1,0,0}
	, {0,0,1,0}
	, {0,0,0,1} };
 
/** Return index of column of M containing maximum abs entry, or -1 if M=0 **/
int32_t find_max_col(_HMatrix M)
{
    float abs, max;
    int32_t i, j, col;
    max = 0.0; col = -1;
    for (i=0; i<3; i++)
	{
		for (j=0; j<3; j++) 
		{
			abs = M[i][j]; 
			if (abs<0.0) abs = -abs;
			if (abs>max) {max = abs; col = j;}
		}
    }
    return col;
}

void vcross(float *va, float *vb, float *v)
{
    v[0] = va[1]*vb[2] - va[2]*vb[1];
    v[1] = va[2]*vb[0] - va[0]*vb[2];
    v[2] = va[0]*vb[1] - va[1]*vb[0];
}

/** Return dot product of length 3 vectors va and vb **/
float vdot(float *va, float *vb)
{
    return (va[0]*vb[0] + va[1]*vb[1] + va[2]*vb[2]);
}


/** Set MadjT to transpose of inverse of M times determinant of M **/
void adjoint_transpose(_HMatrix M, _HMatrix MadjT)
{
    vcross(M[1], M[2], MadjT[0]);
    vcross(M[2], M[0], MadjT[1]);
    vcross(M[0], M[1], MadjT[2]);
}

/** Setup u for Household reflection to zero all v components but first **/
void make_reflector(float *v, float *u)
{
    float s = eve::math::sqrt(vdot(v, v));
    u[0] = v[0]; u[1] = v[1];
    u[2] = v[2] + ((v[2]<0.0) ? -s : s);
    s = eve::math::sqrt (2.0f/vdot(u, u) );
    u[0] = u[0]*s; u[1] = u[1]*s; u[2] = u[2]*s;
}

/** Apply Householder reflection represented by u to column vectors of M **/
void reflect_cols(_HMatrix M, float *u)
{
    int32_t i, j;
    for (i=0; i<3; i++) 
	{
        float s = u[0]*M[0][i] + u[1]*M[1][i] + u[2]*M[2][i];
        for (j=0; j<3; j++) 
			M[j][i] -= u[j]*s;
    }
}

/** Apply Householder reflection represented by u to row vectors of M **/
void reflect_rows(_HMatrix M, float *u)
{
    int32_t i, j;
    for (i=0; i<3; i++) 
	{
        float s = vdot(u, M[i]);
        for (j=0; j<3; j++) M[i][j] -= u[j]*s;
    }
}

/** Find orthogonal factor Q of rank 1 (or less) M **/
void do_rank1(_HMatrix M, _HMatrix Q)
{
    float v1[3], v2[3], s;
    int32_t col;
    mat_copy(Q,=,mat_id,4);
    /* If rank(M) is 1, we should find a non-zero column in M */
    col = find_max_col(M);
    if (col<0) return; /* Rank is 0 */

    v1[0] = M[0][col]; v1[1] = M[1][col]; v1[2] = M[2][col];
    make_reflector(v1, v1); 
	reflect_cols(M, v1);

    v2[0] = M[2][0]; v2[1] = M[2][1]; v2[2] = M[2][2];
    make_reflector(v2, v2); 
	reflect_rows(M, v2);

    s = M[2][2];
    if (s<0.0) 
		Q[2][2] = -1.0;
    reflect_cols(Q, v1); 
	reflect_rows(Q, v2);
}

/** Find orthogonal factor Q of rank 2 (or less) M using adjoint transpose **/
void do_rank2(_HMatrix M, _HMatrix MadjT, _HMatrix Q)
{
    float v1[3], v2[3];
    float w, x, y, z, c, s, d;
    int32_t col;
    /* If rank(M) is 2, we should find a non-zero column in MadjT */
    col = find_max_col(MadjT);
    if (col<0) {do_rank1(M, Q); return;} /* Rank<2 */

    v1[0] = MadjT[0][col]; v1[1] = MadjT[1][col]; v1[2] = MadjT[2][col];
    make_reflector(v1, v1); 
	reflect_cols(M, v1);

    vcross(M[0], M[1], v2);
    make_reflector(v2, v2); 
	reflect_rows(M, v2);

    w = M[0][0]; x = M[0][1]; y = M[1][0]; z = M[1][1];
    if (w*z>x*y) 
	{
        c = z+w; s = y-x; d = eve::math::sqrt(c*c+s*s); c = c/d; s = s/d;
        Q[0][0] = Q[1][1] = c; Q[0][1] = -(Q[1][0] = s);
    } else 
	{
        c = z-w; s = y+x; d = eve::math::sqrt(c*c+s*s); c = c/d; s = s/d;
        Q[0][0] = -(Q[1][1] = c); Q[0][1] = Q[1][0] = s;
    }
    Q[0][2] = Q[2][0] = Q[1][2] = Q[2][1] = 0.0; Q[2][2] = 1.0;
    reflect_cols(Q, v1); 
	reflect_rows(Q, v2);
}

/* Return product of quaternion q by scalar w. */
eve::quatf Qt_Scale(eve::quatf q, float w)
{
	//eve::quatf qq;
	//qq.w	= q.w	* w;
	//qq.x()	= q.x()	* w;
	//qq.y()	= q.y()	* w;
	//qq.z()	= q.z()	* w;
	//return (qq);
	return (q*w);
}

/* Construct a unit quaternion from rotation matrix.  Assumes matrix is
* used to multiply column vector on the left: vnew = mat vold.  Works
* correctly for right-handed coordinate system and right-handed rotations.
* Translation and perspective components ignored. */

eve::quatf quatFromMatrix(_HMatrix mat)
{
   /* This algorithm avoids near-zero divides by looking for a large component
	* - first w, then x, y, or z.  When the trace is greater than zero,
	* |w| is greater than 1/2, which is as small as a largest component can be.
	* Otherwise, the largest diagonal entry corresponds to the largest of |x|,
	* |y|, or |z|, one of which must be larger than |w|, and at least 1/2. */
   eve::quatf qu = q0001;
   float tr, s;

   tr = mat[X][X] + mat[Y][Y]+ mat[Z][Z];
   if (tr >= 0.0)
   {
	   s = eve::math::sqrt(tr + mat[W][W]);
	   qu.w = s * 0.5f;
	   s = 0.5f / s;
	   qu.setX((mat[Z][Y] - mat[Y][Z]) * s);
	   qu.setY((mat[X][Z] - mat[Z][X]) * s);
	   qu.setZ((mat[Y][X] - mat[X][Y]) * s);
   }
   else
   {
	   int32_t h = X;
	   if (mat[Y][Y] > mat[X][X]) h = Y;
	   if (mat[Z][Z] > mat[h][h]) h = Z;
	   switch (h) 
	   {
#define caseMacro(i,j,k,I,J,K) \
		   case I:\
				  s = eve::math::sqrt( (mat[I][I] - (mat[J][J]+mat[K][K])) + mat[W][W] );\
		   qu.i() = s*0.5f;\
		   s = 0.5f / s;\
		   qu.j() = (mat[I][J] + mat[J][I]) * s;\
		   qu.k() = (mat[K][I] + mat[I][K]) * s;\
		   qu.w = (mat[K][J] - mat[J][K]) * s;\
		   break
		   caseMacro(x,y,z,X,Y,Z);
		   caseMacro(y,z,x,Y,Z,X);
		   caseMacro(z,x,y,Z,X,Y);
	   }
   }
   if (mat[W][W] != 1.0) 
	   qu = Qt_Scale(qu, 1.0f/eve::math::sqrt(mat[W][W]));
   
   return (qu);
}


/******* Polar Decomposition *******/
/* Polar Decomposition of 3x3 matrix in 4x4,
 * M = QS.  See Nicholas Higham and Robert S. Schreiber,
 * Fast Polar Decomposition of An Arbitrary Matrix,
 * Technical Report 88-942, October 1988,
 * Department of Computer Science, Cornell University.
 */

float polarDecomp( _HMatrix M, _HMatrix Q, _HMatrix S)
{

#define TOL 1.0e-6
	_HMatrix Mk, MadjTk, Ek;
	float det, M_one, M_inf, MadjT_one, MadjT_inf, E_one, gamma, g1, g2;
	int32_t i, j;

	mat_tpose(Mk,=,M,3);
	M_one = norm_one(Mk);  M_inf = norm_inf(Mk);

	do
	{
		adjoint_transpose(Mk, MadjTk);
		det = vdot(Mk[0], MadjTk[0]);
		if (det==0.0)
		{
			do_rank2(Mk, MadjTk, Mk);
			break;
		}

		MadjT_one = norm_one(MadjTk);
		MadjT_inf = norm_inf(MadjTk);

		gamma = eve::math::sqrt(eve::math::sqrt((MadjT_one*MadjT_inf)/(M_one*M_inf))/eve::math::abs(det));
		g1 = gamma*0.5f;
		g2 = 0.5f/(gamma*det);
		matrixCopy(Ek,=,Mk,3);
		matBinop(Mk,=,g1*Mk,+,g2*MadjTk,3);
		mat_copy(Ek,-=,Mk,3);
		E_one = norm_one(Ek);
		M_one = norm_one(Mk);
		M_inf = norm_inf(Mk);

	} while(E_one>(M_one*TOL));

	mat_tpose(Q,=,Mk,3); mat_pad(Q);
	mat_mult(Mk, M, S);  mat_pad(S);

	for (i=0; i<3; i++)
		for (j=i; j<3; j++)
			S[i][j] = S[j][i] = 0.5f*(S[i][j]+S[j][i]);
	return (det);
}

/******* Spectral Decomposition *******/
/* Compute the spectral decomposition of symmetric positive semi-definite S.
* Returns rotation in U and scale factors in result, so that if K is a diagonal
* matrix of the scale factors, then S = U K (U transpose). Uses Jacobi method.
* See Gene H. Golub and Charles F. Van Loan. Matrix Computations. Hopkins 1983.
*/
HVect spectDecomp(_HMatrix S, _HMatrix U)
{
   HVect kv;
   float Diag[3],OffD[3]; /* OffD is off-diag (by omitted index) */
   float g,h,fabsh,fabsOffDi,t,theta,c,s,tau,ta,OffDq,a,b;
   static char nxt[] = {Y,Z,X};
   int32_t sweep, i, j;
   mat_copy(U,=,mat_id,4);
   Diag[X] = S[X][X]; Diag[Y] = S[Y][Y]; Diag[Z] = S[Z][Z];
   OffD[X] = S[Y][Z]; OffD[Y] = S[Z][X]; OffD[Z] = S[X][Y];
   for (sweep=20; sweep>0; sweep--) {
	   float sm = eve::math::abs(OffD[X])+eve::math::abs(OffD[Y])+eve::math::abs(OffD[Z]);
	   if (sm==0.0) break;
	   for (i=Z; i>=X; i--) {
		   int32_t p = nxt[i]; int32_t q = nxt[p];
		   fabsOffDi = eve::math::abs(OffD[i]);
		   g = 100.0f*fabsOffDi;
		   if (fabsOffDi>0.0) {
			   h = Diag[q] - Diag[p];
			   fabsh = eve::math::abs(h);
			   if (fabsh+g==fabsh) {
				   t = OffD[i]/h;
			   } else {
				   theta = 0.5f*h/OffD[i];
				   t = 1.0f/(eve::math::abs(theta)+eve::math::sqrt(theta*theta+1.0f));
				   if (theta<0.0) t = -t;
			   }
			   c = 1.0f / eve::math::sqrt(t*t+1.0f); s = t*c;
			   tau = s / (c+1.0f);
			   ta = t*OffD[i]; OffD[i] = 0.0;
			   Diag[p] -= ta; Diag[q] += ta;
			   OffDq = OffD[q];
			   OffD[q] -= s*(OffD[p] + tau*OffD[q]);
			   OffD[p] += s*(OffDq   - tau*OffD[p]);
			   for (j=Z; j>=X; j--) {
				   a = U[j][p]; b = U[j][q];
				   U[j][p] -= s*(b + tau*a);
				   U[j][q] += s*(a - tau*b);
			   }
		   }
	   }
   }
   kv.x() = Diag[X]; kv.y() = Diag[Y]; kv.z() = Diag[Z]; kv.w = 1.0;
   return (kv);
}

/* Return conjugate of quaternion. */
eve::quatf Qt_Conj(eve::quatf q)
{
	eve::quatf qq;
    qq.x()	= -q.x(); 
	qq.y()	= -q.y(); 
	qq.z()	= -q.z(); 
	qq.w	= q.w;
    return (qq);
}

/* Return quaternion product qL * qR.  Note: order is important!
 * To combine rotations, use the product Mul(qSecond, qFirst),
 * which gives the effect of rotating by qFirst then qSecond. */
eve::quatf Qt_Mul(eve::quatf qL, eve::quatf qR)
{
	eve::quatf qq;
    qq.w	= qL.w*qR.w   - qL.x()*qR.x() - qL.y()*qR.y() - qL.z()*qR.z();
    qq.x()	= qL.w*qR.x() + qL.x()*qR.w   + qL.y()*qR.z() - qL.z()*qR.y();
    qq.y()	= qL.w*qR.y() + qL.y()*qR.w   + qL.z()*qR.x() - qL.x()*qR.z();
    qq.z()	= qL.w*qR.z() + qL.z()*qR.w   + qL.x()*qR.y() - qL.y()*qR.x();
    return (qq);
}

/* Construct a (possibly non-unit) quaternion from real components. */
eve::quatf Qt_(float x, float y, float z, float w)
{
	eve::quatf qq;
    qq.x() = x; qq.y() = y; qq.z() = z; qq.w = w;
    return (qq);
}

/******* Spectral Axis Adjustment *******/

/* Given a unit quaternion, q, and a scale vector, k, find a unit quaternion, p,
 * which permutes the axes and turns freely in the plane of duplicate scale
 * factors, such that q p has the largest possible w component, i.e. the
 * smallest possible angle. Permutes k's components to go with q p instead of q.
 * See Ken Shoemake and Tom Duff. Matrix Animation and Polar Decomposition.
 * Proceedings of Graphics Interface 1992. Details on p. 262-263.
 */
eve::quatf snuggle(eve::quatf q, HVect *k)
{
#define sgn(n,v)    ((n)?-(v):(v))
#define swap(a,i,j) {a[3]=a[i]; a[i]=a[j]; a[j]=a[3];}
#define cycle(a,p)  if (p) {a[3]=a[0]; a[0]=a[1]; a[1]=a[2]; a[2]=a[3];}\
	else   {a[3]=a[2]; a[2]=a[1]; a[1]=a[0]; a[0]=a[3];}

	eve::quatf p = q0001;
	float ka[4];
	int32_t i, turn = -1;
	ka[X] = k->x(); 
	ka[Y] = k->y(); 
	ka[Z] = k->z();

	if (ka[X]==ka[Y]) {
		if (ka[X]==ka[Z])
			turn = W;
		else turn = Z;
	}
	else {
		if (ka[X]==ka[Z])
			turn = Y;
		else if (ka[Y]==ka[Z])
			turn = X;
	}
	if (turn>=0) {
		eve::quatf qtoz, qp;
		uint32_t  win;
		float mag[3], t;
		switch (turn) {
			default: return (Qt_Conj(q));
			case X: q = Qt_Mul(q, qtoz = qxtoz); swap(ka,X,Z) break;
			case Y: q = Qt_Mul(q, qtoz = qytoz); swap(ka,Y,Z) break;
			case Z: qtoz = q0001; break;
		}
		q = Qt_Conj(q);
		mag[0] = (float)q.z()*q.z()+(float)q.w*q.w-0.5f;
		mag[1] = (float)q.x()*q.z()-(float)q.y()*q.w;
		mag[2] = (float)q.y()*q.z()+(float)q.x()*q.w;

		bool neg[3];
		for (i=0; i<3; i++)
		{
			neg[i] = (mag[i]<0.0);
			if (neg[i]) mag[i] = -mag[i];
		}

		if (mag[0]>mag[1]) {
			if (mag[0]>mag[2])
				win = 0;
			else win = 2;
		}
		else {
			if (mag[1]>mag[2]) win = 1;
			else win = 2;
		}

		switch (win) {
			case 0: if (neg[0]) p = q1000; else p = q0001; break;
			case 1: if (neg[1]) p = qppmm; else p = qpppp; cycle(ka,0) break;
			case 2: if (neg[2]) p = qmpmm; else p = qpppm; cycle(ka,1) break;
		}

		qp = Qt_Mul(q, p);
		t = eve::math::sqrt( mag[win] + 0.5f );
		p = Qt_Mul(p, Qt_(0.0,0.0,-qp.z()/t,qp.w/t));
		p = Qt_Mul(qtoz, Qt_Conj(p));
	}
	else {
		float qa[4], pa[4];
		uint32_t lo, hi;
		bool par = false;
		bool neg[4];
		float all, big, two;
		qa[0] = q.x(); qa[1] = q.y(); qa[2] = q.z(); qa[3] = q.w;
		for (i=0; i<4; i++) {
			pa[i] = 0.0;
			neg[i] = (qa[i]<0.0);
			if (neg[i]) qa[i] = -qa[i];
			par ^= neg[i];
		}

		/* Find two largest components, indices in hi and lo */
		if (qa[0]>qa[1]) lo = 0;
		else lo = 1;

		if (qa[2]>qa[3]) hi = 2;
		else hi = 3;

		if (qa[lo]>qa[hi]) {
			if (qa[lo^1]>qa[hi]) {
				hi = lo; lo ^= 1;
			}
			else {
				hi ^= lo; lo ^= hi; hi ^= lo;
			}
		}
		else {
			if (qa[hi^1]>qa[lo]) lo = hi^1;
		}

		all = (qa[0]+qa[1]+qa[2]+qa[3])*0.5f;
		two = (qa[hi]+qa[lo])*SQRTHALF_F;
		big = qa[hi];
		if (all>two) {
			if (all>big) {/*all*/
				{int32_t i; for (i=0; i<4; i++) pa[i] = sgn(neg[i], 0.5f);}
				cycle(ka,par);
			}
			else {/*big*/ pa[hi] = sgn(neg[hi], 1.0f);}
		} else {
			if (two>big) { /*two*/
				pa[hi] = sgn(neg[hi],SQRTHALF_F);
				pa[lo] = sgn(neg[lo], SQRTHALF_F);
				if (lo>hi) {
					hi ^= lo; lo ^= hi; hi ^= lo;
				}
				if (hi==W) {
					hi = "\001\002\000"[lo];
					lo = 3-hi-lo;
				}
				swap(ka,hi,lo);
			}
			else {/*big*/
				pa[hi] = sgn(neg[hi], 1.0f);
			}
		}
		p.x() = -pa[0]; p.y() = -pa[1]; p.z() = -pa[2]; p.w = pa[3];
	}
	k->x() = ka[X]; k->y() = ka[Y]; k->z() = ka[Z];
	return (p);
}

/******* Decompose Affine Matrix *******/

/* Decompose 4x4 affine matrix A as TFRUK(U transpose), where t contains the
 * translation components, q contains the rotation R, u contains U, k contains
 * scale factors, and f contains the sign of the determinant.
 * Assumes A transforms column vectors in right-handed coordinates.
 * See Ken Shoemake and Tom Duff. Matrix Animation and Polar Decomposition.
 * Proceedings of Graphics Interface 1992.
 */
void decompAffine(_HMatrix A, _affineParts * parts)
{
	_HMatrix Q, S, U;
	eve::quatf p;

	//Translation component.
	parts->t = eve::vec4f(A[X][W], A[Y][W], A[Z][W], 0);
	float det = polarDecomp(A, Q, S);
	if( det < 0.0f )
	{
		matrixCopy(Q, =, -Q, 3);
		parts->f = -1;
	}
	else
		parts->f = 1;

	parts->q = quatFromMatrix(Q);
	parts->k = spectDecomp(S, U);
	parts->u = quatFromMatrix(U);
	p = snuggle(parts->u, &parts->k);
	parts->u = Qt_Mul(parts->u, p);
}



//=================================================================================================
void eve::math::decompose_matrix44( const eve::mat44f & mat, eve::vec3f & t, eve::quatf & r, eve::vec3f & s, eve::quatf & so )
{
	_affineParts parts;
    _HMatrix hmatrix;

    // Transpose copy of LTW
    for ( int32_t i =0; i<4; i++)
    {
        for ( int32_t j=0; j<4; j++)
        {
            hmatrix[ i ][ j ] = mat.m[ j*4 + i ];
        }
    }

    decompAffine(hmatrix, &parts);

    float mul = 1.0f;
    if( parts.t[W] != 0.0f )
        mul = 1.0f / parts.t[W];

    t.x = parts.t[X] * mul;
    t.y = parts.t[Y] * mul;
    t.z = parts.t[Z] * mul;

	r.set(parts.q.w, parts.q.x(), parts.q.y(), parts.q.z());

    mul = 1.0f;
    if (parts.k.w != 0.0f)
        mul = 1.0f / parts.k.w;

    // mul be sign of determinant to support negative scales.
    mul *= parts.f;
    s.x  = parts.k.x() * mul;
    s.y  = parts.k.y() * mul;
    s.z  = parts.k.z() * mul;

	so.set(parts.u.w, parts.u.x(), parts.u.y(), parts.u.z());
}



//=================================================================================================
void eve::math::decompose_matrix44( const eve::mat44f & mat, eve::vec3f & t, eve::quatf & r )
{
	_affineParts parts;
	_HMatrix hmatrix;

	// Transpose copy of LTW
	for ( int32_t i =0; i<4; i++)
	{
		for ( int32_t j=0; j<4; j++)
		{
			hmatrix[ i ][ j ] = mat.m[ j*4 + i ];
		}
	}

	decompAffine(hmatrix, &parts);

	float mul = 1.0f;
	if ( parts.t[W] != 0.0f )
		mul = 1.0f / parts.t[W];

	t.x = parts.t[X] * mul;
	t.y = parts.t[Y] * mul;
	t.z = parts.t[Z] * mul;

	r.set(parts.q.w, parts.q.x(), parts.q.y(), parts.q.z());
}
