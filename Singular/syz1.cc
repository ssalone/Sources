/****************************************
*  Computer Algebra System SINGULAR     *
****************************************/
/* $Id: syz1.cc,v 1.45 1999-10-20 11:55:28 obachman Exp $ */
/*
* ABSTRACT: resolutions
*/

#include "mod2.h"
#include "tok.h"
#include "mmemory.h"
#include "polys.h"
#include "febase.h"
#include "kstd1.h"
#include "kutil.h"
#include "stairc.h"
#include "ipid.h"
#include "cntrlc.h"
#include "ipid.h"
#include "intvec.h"
#include "ipshell.h"
#include "limits.h"
#include "numbers.h"
#include "modulop.h"
#include "ideals.h"
#include "intvec.h"
#include "ring.h"
#include "lists.h"
#include "syz.h"
#include "kbuckets.h"
#include "polys-comp.h"
#include <limits.h>

extern void rSetmS(poly p, int* Components, long* ShiftedComponents);

/*--------------static variables------------------------*/
/*---points to the real components, shifted of the actual module-*/
int *  currcomponents=NULL;
long *  currShiftedComponents=NULL;


/*---head-term-polynomials for the reduction------------*/
static poly redpol=NULL;
/*---counts number of applications of GM-criteria-------*/
//static int crit;
//static int euler;

/*3
* deletes all entres of a pair
*/
void syDeletePair(SObject * so)
{
  pDelete(&(*so).p);
  pDelete(&(*so).lcm);
  pDelete(&(*so).syz);
  (*so).p1 = NULL;
  (*so).p2 = NULL;
  (*so).ind1 = 0;
  (*so).ind2 = 0;
  (*so).syzind = -1;
  (*so).order = 0;
  (*so).isNotMinimal = NULL;
  (*so).length = -1;
  (*so).reference = -1;
}

/*3
* initializes all entres of a pair
*/
void syInitializePair(SObject * so)
{
  (*so).p = NULL;
  (*so).lcm = NULL;
  (*so).syz = NULL;
  (*so).p1 = NULL;
  (*so).p2 = NULL;
  (*so).ind1 = 0;
  (*so).ind2 = 0;
  (*so).syzind = -1;
  (*so).order = 0;
  (*so).isNotMinimal = NULL;
  (*so).length = -1;
  (*so).reference = -1;
}

/*3
* puts all entres of a pair to another
*/
void syCopyPair(SObject * argso, SObject * imso)
{
  *imso=*argso;
  (*argso).p = NULL;
  (*argso).p1 = NULL;
  (*argso).p2 = NULL;
  (*argso).lcm = NULL;
  (*argso).syz = NULL;
  (*argso).ind1 = 0;
  (*argso).ind2 = 0;
  (*argso).syzind = -1;
  (*argso).order = 0;
  (*argso).isNotMinimal = NULL;
  (*argso).length = -1;
  (*argso).reference = -1;
}

/*3
* deletes empty objects from a pair set beginning with
* pair first
* assumes a pair to be empty if .lcm does so
*/
void syCompactifyPairSet(SSet sPairs, int sPlength, int first)
{
  int k=first,kk=0;

  while (k+kk<sPlength)
  {
    if (sPairs[k+kk].lcm!=NULL)
    {
      if (kk>0) syCopyPair(&sPairs[k+kk],&sPairs[k]);
      k++;
    }
    else
    {
      kk++;
    }
  }
  while (k<sPlength)
  {
    syInitializePair(&sPairs[k]);
    k++;
  }
}

/*3
* deletes empty objects from a pair set beginning with
* pair first
* assumes a pair to be empty if .lcm does so
*/
void syCompactify1(SSet sPairs, int* sPlength, int first)
{
  int k=first,kk=0;

  while (k+kk<*sPlength)
  {
    if (sPairs[k+kk].lcm!=NULL)
    {
      if (kk>0) syCopyPair(&sPairs[k+kk],&sPairs[k]);
      k++;
    }
    else
    {
      kk++;
    }
  }
  while (k<*sPlength)
  {
    syInitializePair(&sPairs[k]);
    k++;
  }
  *sPlength -= kk;
}

static pCompProc syOldComp1;
/*3
* replaces comp1dpc during homogeneous syzygy-computations
* compares with components of currcomponents instead of the
* exp[0]
*/
static int syzcomp0dpc(poly p1, poly p2)
{
  /*4 compare monomials by order then revlex*/
    int i = pVariables;
    if ((pGetExp(p1,i) == pGetExp(p2,i)))
    {
      do
      {
        i--;
        if (i <= 1)
        {
           /*4 handle module case:*/
           if (pGetComp(p1)==pGetComp(p2)) return 0;
           else if
              (currcomponents[pGetComp(p1)]>currcomponents[pGetComp(p2)])
                return 1;
           else return -1;
        }
      } while ((pGetExp(p1,i) == pGetExp(p2,i)));
    }
    if (pGetExp(p1,i) < pGetExp(p2,i)) return 1;
    return -1;
}

/*3
* replaces comp1dpc during homogeneous syzygy-computations
* compares with components of currcomponents instead of the
* exp[0]
*/
int syzcomp1dpc(poly p1, poly p2)
{
  int i = pVariables;
  while ((i>1) && (pGetExp(p1,i)==pGetExp(p2,i)))
    i--;
  if (i>1)
  {
    if (pGetExp(p1,i) < pGetExp(p2,i)) return 1;
    return -1;
  }
  int o1=pGetComp(p1);
  int o2=pGetComp(p2);
  if (o1==o2/*pGetComp(p1)==pGetComp(p2)*/) return 0;
  if (currcomponents[o1]>currcomponents[o2]) return 1;
  return -1;

}

/*3
* replaces comp1dpc during homogeneous syzygy-computations
* compares with components of currcomponents instead of the
* exp[0]
*/

#ifdef PDEBUG
static int syzcomp2dpc_test(poly p1, poly p2)
{
  long c1, c2, cc1, cc2, ccc1, ccc2, ec1, ec2;
  c1 = pGetComp(p1);
  c2 = pGetComp(p2);
  cc1 = currcomponents[c1];
  cc2 = currcomponents[c2];
  ccc1 = currShiftedComponents[cc1];
  ccc2 = currShiftedComponents[cc2];
  ec1 = p1->exp.l[currRing->typ[1].data.syzcomp.place];
  ec2 = p2->exp.l[currRing->typ[1].data.syzcomp.place];

  if (ec1 != ccc1)
  {
    Warn("Shifted comp of p1 out of sync. should %d, is %d", ccc1, ec1);
    //mmDBInfoBlock(p1);
  }
  if (ec2 != ccc2)
  {
    Warn("Shifted comp of p2 out of sync. should %d, is %d", ccc2, ec2);
    //mmDBInfoBlock(p2);
  }

  if (c1 == c2)
  {
    assume(ccc1 == ccc2);
  }
  else if (cc1 > cc2)
  {
    assume(ccc1 > ccc2);
  }
  else
  {
    assume (cc1 < cc2);
    assume (ccc1 < ccc2);
  }
  int o1=pGetOrder(p1), o2=pGetOrder(p2);
  if (o1 > o2) return 1;
  if (o1 < o2) return -1;

  //if (o1>0)
  {
    int i = pVariables;
    while ((i>1) && (pGetExp(p1,i)==pGetExp(p2,i)))
      i--;
    //(*orderingdepth)[pVariables-i]++;
    if (i>1)
    {
      if (pGetExp(p1,i) < pGetExp(p2,i)) return 1;
      return -1;
    }
  }
  o1=pGetComp(p1);
  o2=pGetComp(p2);
  if (o1==o2/*pGetComp(p1)==pGetComp(p2)*/) return 0;
  if (currcomponents[o1]>currcomponents[o2]) return 1;
  return -1;
}
int syzcomp2dpc(poly p1, poly p2)
{
  int test = syzcomp2dpc_test(p1, p2);
  int rc = rComp0(p1, p2);
  if (test != rc)
  {
    assume(0);
    syzcomp2dpc_test(p1, p2);
    rComp0(p1, p2);
  }
  return test;
}
#endif // PDEBUG

/*3
* compares only the monomial without component
*/
static int syzcompmonomdp(poly p1, poly p2)
{
  int i;

  /*4 compare monomials by order then revlex*/
  if (pGetOrder(p1) == pGetOrder(p2))
  {
    i = pVariables;
    if ((pGetExp(p1,i) == pGetExp(p2,i)))
    {
      do
      {
        i--;
        if (i <= 1)
          return 0;
      } while ((pGetExp(p1,i) == pGetExp(p2,i)));
    }
    if (pGetExp(p1,i) < pGetExp(p2,i)) return 1;
    return -1;
  }
  else if (pGetOrder(p1) > pGetOrder(p2)) return 1;
  return -1;
}

poly syOrdPolySchreyer(poly p)
{
  return pOrdPolyMerge(p);
}

static int syLength(poly p)
{
  int result=0;

  while (p!=NULL)
  {
    result++;
    pIter(p);
  }
  return result;
}

poly syRedtail (poly p, syStrategy syzstr, int index)
{
  poly h, hn;
  int j,pos;
  ideal redWith=syzstr->orderedRes[index];

  h = p;
  hn = pNext(h);
  while(hn != NULL)
  {
    j = syzstr->Firstelem[index-1][pGetComp(hn)]-1;
    if (j>=0)
    {
      pos = j+syzstr->Howmuch[index-1][pGetComp(hn)];
      while (j < pos)
      {
        if (pDivisibleBy2(redWith->m[j], hn))
        {
          //hn = sySPolyRed(hn,redWith->m[j]);
          hn = ksOldSpolyRed(redWith->m[j],hn);
          if (hn == NULL)
          {
            pNext(h) = NULL;
            return p;
          }
          j = syzstr->Firstelem[index-1][pGetComp(hn)]-1;
          pos = j+syzstr->Howmuch[index-1][pGetComp(hn)];
        }
        else
        {
          j++;
        }
      }
    }
    h = pNext(h) = hn;
    hn = pNext(h);
  }
  return p;
}


/*3
* local procedure for of syInitRes for the module case
*/
static int syChMin(intvec * iv)
{
  int i,j=-1,r=-1;

  for (i=iv->length()-1;i>=0;i--)
  {
    if ((*iv)[i]>=0)
    {
      if ((j<0) || ((*iv)[i]<j))
      {
        j = (*iv)[i];
        r = i;
      }
    }
  }
  return r;
}

/*3
* initialize the resolution and puts in the argument as
* zeroth entre, length must be > 0
* assumes that the basering is degree-compatible
*/
SRes syInitRes(ideal arg,int * length, intvec * Tl, intvec * cw)
{
  if (idIs0(arg)) return NULL;
  SRes resPairs = (SRes)Alloc0(*length*sizeof(SSet));
  resPairs[0] = (SSet)Alloc0(IDELEMS(arg)*sizeof(SObject));
  intvec * iv=NULL;
  int i,j;

  if (idRankFreeModule(arg)==0)
  {
    iv = idSort(arg);
    for (i=0;i<IDELEMS(arg);i++)
    {
      (resPairs[0])[i].syz = /*pCopy*/(arg->m[(*iv)[i]-1]);
      arg->m[(*iv)[i]-1] = NULL;
      (resPairs[0])[i].order = pTotaldegree((resPairs[0])[i].syz);
    }
  }
  else
  {
    iv = new intvec(IDELEMS(arg),1,-1);
    for (i=0;i<IDELEMS(arg);i++)
    {
      (*iv)[i] = pTotaldegree(arg->m[i])+(*cw)[pGetComp(arg->m[i])-1];
    }
    for (i=0;i<IDELEMS(arg);i++)
    {
      j = syChMin(iv);
      if (j<0) break;
      (resPairs[0])[i].syz = arg->m[j];
      arg->m[j] = NULL;
      (resPairs[0])[i].order = (*iv)[j];
      (*iv)[j] = -1;
    }
  }
  if (iv!=NULL)  delete iv;
  (*Tl)[0] = IDELEMS(arg);
  return resPairs;
}

// rearrange shifted components
long syReorderShiftedComponents(long * sc, int n)
{
  long holes = 0;
  int i;
  long new_comps = 0, new_space, max;

  // count number of holes
  for (i=1; i<n; i++)
  {
    if (sc[i-1] + 1 < sc[i]) holes++;
  }

  if (LONG_MAX - SYZ_SHIFT_BASE <= sc[n-1])
  {
    // need new components
    new_comps = (1 << SYZ_SHIFT_MAX_NEW_COMP_ESTIMATE) - 1;
    max = LONG_MAX;
  }
  else
  {
    max = sc[n-1] + SYZ_SHIFT_BASE;
  }

  // no we arrange things such that
  // (n - holes) + holes*new_space + new_comps*SYZ_SHIFT_BASE= LONG_MAX
  new_space = (max - n + holes - new_comps*SYZ_SHIFT_BASE) / holes;

  assume(new_space < SYZ_SHIFT_BASE && new_space >= 4);

  long* tc = ( long*) Alloc(n*sizeof(long));
  tc[0] = sc[0];
  // rearrange things
  for (i=1; i<n; i++)
  {
    if (sc[i-1] + 1 < sc[i])
    {
      tc[i] = tc[i-1] + new_space;
    }
    else
    {
      tc[i] = tc[i-1] + 1;
    }
    assume(tc[i] > tc[i-1]);
  }

  assume(LONG_MAX -  SYZ_SHIFT_BASE > tc[n-1]);
#ifdef HAVE_ASSUME
  for (i=1; i<n; i++)
  {
    assume(tc[i] >= 0);
    assume(tc[i-1] + 1 <= tc[i]);
  }
#endif

  memcpyW(sc, tc, n);
  Free(tc, n*sizeof(long));
  return new_space;
}

// this make a Setm on p
static void pResetSetm(poly p)
{
#ifdef PDEBUG
  poly q = p;
#endif
  while (p!= NULL)
  {
    pSetm(p);
    pIter(p);
  }
#ifdef PDEBUG
  if (! pTest(q))
  {
    pSetm(p);
  }
#endif
}

void syResetShiftedComponents(syStrategy syzstr, int index,int hilb)
{
  assume(index > 0);
  int i;
  if (syzstr->res[index] != NULL)
  {
    long * prev_s;
    int* prev_c;
    int p_length;
    rGetSComps(&prev_c, &prev_s, &p_length);
    currcomponents = syzstr->truecomponents[index-1];
    currShiftedComponents = syzstr->ShiftedComponents[index-1];
    rChangeSComps(currcomponents,
                  currShiftedComponents,
                  IDELEMS(syzstr->res[index-1]));
    if (hilb==0)
    {
      ideal id = syzstr->res[index];
      for (i=0; i<IDELEMS(id); i++)
      {
        pResetSetm(id->m[i]);
      }
    }
    else if (hilb==1)
    {
      assume (index>1);
      assume (syzstr->resPairs[index-1]!=NULL);
      SSet Pairs=syzstr->resPairs[index-1];
      SSet Pairs1=syzstr->resPairs[index]; 
      int till=(*syzstr->Tl)[index-1];
      for (i=0;i<till;i++)
      {
        if (Pairs[i].syz!=NULL)
          pResetSetm(Pairs[i].syz);
      }
      till=(*syzstr->Tl)[index];
      for (i=0;i<till;i++)
      {
        if (Pairs1[i].p!=NULL)
          pResetSetm(Pairs1[i].p);
      }
    }
    currcomponents  = prev_c;
    currShiftedComponents = prev_s;
    rChangeSComps(prev_c, prev_s, p_length);
  }
}

/*3
* determines the place of a polynomial in the right ordered resolution
* set the vectors of truecomponents
*/
static BOOLEAN syOrder(poly p,syStrategy syzstr,int index,
                    int realcomp)
{
  int i=IDELEMS(syzstr->res[index-1])+1,j=0,k,tc,orc,ie=realcomp-1;
  int *trind1=syzstr->truecomponents[index-1];
  int *trind=syzstr->truecomponents[index];
  long *shind=syzstr->ShiftedComponents[index];
  int *bc=syzstr->backcomponents[index];
  int *F1=syzstr->Firstelem[index-1];
  int *H1=syzstr->Howmuch[index-1];
  poly pp;
  polyset o_r=syzstr->orderedRes[index]->m;
  polyset or1=syzstr->orderedRes[index-1]->m;
  BOOLEAN ret = FALSE;

  // if != 0, then new element can go into same component
  // i.e., we do not need to leave space in shifted components
  long same_comp = 0;

  if (p==NULL) return FALSE;
  if (realcomp==0) realcomp=1;

  if (index>1)
    tc = trind1[pGetComp(p)]-1;
  else
    tc = pGetComp(p)-1;
  loop         //while ((j<ie) && (trind1[orc]<=tc+1))
  {
    if (j>=ie)
      break;
    else
    {
      orc = pGetComp(o_r[j]);
      if (trind1[orc]>tc+1) break;
      else if (trind1[orc] == tc+1)
      {
        same_comp = 1;
      }
      else
      {
        assume(same_comp == 0);
      }
      j += H1[orc];
    }
  }
  if (j>ie)
  {
    WerrorS("orderedRes to small");
    return FALSE;
  }
  ie++;
  if (j == (ie -1))
  {
    // new element is the last in ordered module
    if (same_comp == 0)
      same_comp = SYZ_SHIFT_BASE;

    // test wheter we have enough space for new shifted component
    if ((LONG_MAX - same_comp) <= shind[ie-1])
    {
      long new_space = syReorderShiftedComponents(shind, ie);
      assume((LONG_MAX - same_comp) > shind[ie-1]);
      ret = TRUE;
      if (TEST_OPT_PROT) Print("(T%u)", new_space);
    }

    // yes, then set new shifted component
    assume(ie == 1 || shind[ie-1] > 0);
    shind[ie] = shind[ie-1] + same_comp;
  }
  else
  {
    // new element must come in between
    // i.e. at place j+1
    long prev, next;

    // test whether new component can get shifted value
    prev = shind[j];
    next = shind[j+1];
    assume(next > prev);
    if ((same_comp && prev + 2 >= next) || (!same_comp && next - prev < 4))
    {
       long new_space = syReorderShiftedComponents(shind, ie);
      prev = shind[j];
      next = shind[j+1];
      assume((same_comp && prev + 2 < next) || (!same_comp && next - prev >= 4));
      ret = TRUE;
     if (TEST_OPT_PROT) Print("(B%u)", new_space);
    }

    // make room for insertion of j+1 shifted component
    for (k=ie; k > j+1; k--) shind[k] = shind[k-1];

    if (same_comp)
    {
      // can simply add one
      shind[j+1] = prev + 1;
      assume(shind[j+1] + 1 < shind[j+2]);
    }
    else
    {
      // need to leave more breathing room - i.e. value goes in
      // between
      shind[j+1]  = prev + ((next - prev) >> 1);
      assume (shind[j] + 1 < shind[j+1] && shind[j+1] + 1 < shind[j+2]);
    }
  }

  if (o_r[j]!=NULL)
  {
    for (k=ie-1;k>j;k--)
    {
      o_r[k] = o_r[k-1];
      bc[k] = bc[k-1];
    }
  }
  o_r[j] = p;
  bc[j] = realcomp-1;
  (H1[pGetComp(p)])++;
  for (k=0;k<i;k++)
  {
    if (F1[k]>j)
      (F1[k])++;
  }
  if (F1[pGetComp(p)]==0)
    F1[pGetComp(p)]=j+1;
  for (k=0;k<IDELEMS((syzstr->res)[index]);k++)
  {
    if (trind[k]>j)
      trind[k] += 1;
  }
  for (k=IDELEMS((syzstr->res)[index])-1;k>realcomp;k--)
    trind[k] = trind[k-1];
  trind[realcomp] = j+1;
  return ret;
}

//#define OLD_PAIR_ORDER
#ifdef OLD_PAIR_ORDER
static intvec* syLinStrat(SSet nextPairs, syStrategy syzstr,
                          int howmuch, int index)
{
  int i=howmuch-1,i1=0,l,ll;
  int ** Fin=syzstr->Firstelem;
  int ** Hin=syzstr->Howmuch;
  int ** bin=syzstr->backcomponents;
  ideal o_r=syzstr->orderedRes[index+1];
  intvec *result=new intvec(howmuch+1);
  BOOLEAN isDivisible;
  SObject tso;

  while (i>=0)
  {
    tso = nextPairs[i];
    isDivisible = FALSE;
    if (syzstr->res[index+1]!=NULL)
    {
      l = Fin[index][pGetComp(tso.lcm)]-1;
      if (l>=0)
      {
        ll = l+Hin[index][pGetComp(tso.lcm)];
        while ((l<ll) && (!isDivisible))
        {
          if (o_r->m[l]!=NULL)
          {
            isDivisible = isDivisible ||
              pDivisibleBy2(o_r->m[l],tso.lcm);
          }
          l++;
        }
      }
    }
    if (isDivisible)
    {
      syDeletePair(&nextPairs[i]);
      //crit++;
    }
    else
    {
      nextPairs[i].p =
        //sySPoly(tso.p1, tso.p2,tso.lcm);
        spSpolyCreate(tso.p2, tso.p1,NULL,spSpolyLoop_General);
      (*result)[i1] = i+1;
      i1++;
    }
    i--;
  }
  return result;
}
#else
static intvec* syLinStrat(SSet nextPairs, syStrategy syzstr,
                          int howmuch, int index)
{
  int i=howmuch-1,i1=0,i2,i3,l,ll;
  int ** Fin=syzstr->Firstelem;
  int ** Hin=syzstr->Howmuch;
  int ** bin=syzstr->backcomponents;
  ideal o_r=syzstr->orderedRes[index+1];
  intvec *result=new intvec(howmuch+1);
  intvec *spl=new intvec(howmuch,1,-1);
  BOOLEAN isDivisible;
  SObject tso;

  while (i>=0)
  {
    tso = nextPairs[i];
    isDivisible = FALSE;
    if (syzstr->res[index+1]!=NULL)
    {
      l = Fin[index][pGetComp(tso.lcm)]-1;
      if (l>=0)
      {
        ll = l+Hin[index][pGetComp(tso.lcm)];
        while ((l<ll) && (!isDivisible))
        {
          if (o_r->m[l]!=NULL)
          {
            isDivisible = isDivisible ||
              pDivisibleBy2(o_r->m[l],tso.lcm);
          }
          l++;
        }
      }
    }
    if (isDivisible)
    {
      syDeletePair(&nextPairs[i]);
      //crit++;
    }
    else
    {
      pTest(tso.p2);
      pTest(tso.p1);
      nextPairs[i].p =
        ksOldCreateSpoly(tso.p2, tso.p1,NULL);
      (*spl)[i] = pLength(nextPairs[i].p);
    }
    i--;
  }
  i3 = 0;
  loop
  {
    i2 = -1;
    for (i1=0;i1<howmuch;i1++)
    {
      if (i2==-1)
      {
        if ((*spl)[i1]!=-1)
        {
          i2 = i1;
        }
      }
      else
      {
        if (((*spl)[i1]>=0) && ((*spl)[i1]<(*spl)[i2]))
        {
          i2 = i1;
        }
      }
    }
    if (i2>=0)
    {
      (*result)[i3] = i2+1;
      (*spl)[i2] = -1;
      i3++;
    }
    else
    {
      break;
    }
  }
  return result;
}
#endif

void syEnlargeFields(syStrategy syzstr,int index)
{
  pEnlargeSet(&(syzstr->res[index]->m),IDELEMS(syzstr->res[index]),16);
  syzstr->truecomponents[index]=(int*)ReAlloc0((ADDRESS)syzstr->truecomponents[index],
                               (IDELEMS(syzstr->res[index])+1)*sizeof(int),
                               (IDELEMS(syzstr->res[index])+17)*sizeof(int));
  syzstr->ShiftedComponents[index]
    =(long*)ReAlloc0((ADDRESS)syzstr->ShiftedComponents[index],
                              (IDELEMS(syzstr->res[index])+1)*sizeof(long),
                              (IDELEMS(syzstr->res[index])+17)*sizeof(long));
  syzstr->backcomponents[index]=(int*)ReAlloc0((ADDRESS)syzstr->backcomponents[index],
                               (IDELEMS(syzstr->res[index])+1)*sizeof(int),
                               (IDELEMS(syzstr->res[index])+17)*sizeof(int));
  syzstr->Howmuch[index]=(int*)ReAlloc0((ADDRESS)syzstr->Howmuch[index],
                               (IDELEMS(syzstr->res[index])+1)*sizeof(int),
                               (IDELEMS(syzstr->res[index])+17)*sizeof(int));
  syzstr->Firstelem[index]=(int*)ReAlloc0((ADDRESS)syzstr->Firstelem[index],
                               (IDELEMS(syzstr->res[index])+1)*sizeof(int),
                               (IDELEMS(syzstr->res[index])+17)*sizeof(int));
  syzstr->elemLength[index]=(int*)ReAlloc0((ADDRESS)syzstr->elemLength[index],
                               (IDELEMS(syzstr->res[index])+1)*sizeof(int),
                               (IDELEMS(syzstr->res[index])+17)*sizeof(int));
  syzstr->sev[index]=(unsigned long*)ReAlloc0((ADDRESS)syzstr->sev[index],
                                    (IDELEMS(syzstr->res[index])+1)*sizeof(unsigned long),
                               (IDELEMS(syzstr->res[index])+17)*sizeof(unsigned long));
  IDELEMS(syzstr->res[index]) += 16;
  pEnlargeSet(&(syzstr->orderedRes[index]->m),IDELEMS(syzstr->orderedRes[index]),16);
  IDELEMS(syzstr->orderedRes[index]) += 16;
}
/*3
* reduces all pairs of degree deg in the module index
* put the reduced generators to the resolvente which contains
* the truncated kStd
*/
static void syRedNextPairs(SSet nextPairs, syStrategy syzstr,
               int howmuch, int index)
{
  int i,j,k=IDELEMS(syzstr->res[index]);
  int ks=IDELEMS(syzstr->res[index+1]),kk,l,ll;
  int * Fin=syzstr->Firstelem[index-1];
  int * Hin=syzstr->Howmuch[index-1];
  int * bin=syzstr->backcomponents[index];
  int * elL=syzstr->elemLength[index];
  number coefgcd,n;
  polyset redset=syzstr->orderedRes[index]->m;
  poly p=NULL,q;
  intvec *spl1=new intvec(howmuch+1);
  SObject tso;
  long * ShiftedComponents = syzstr->ShiftedComponents[index];
  int* Components = syzstr->truecomponents[index];
  assume(Components != NULL && ShiftedComponents != NULL);
  BOOLEAN need_reset;

  if ((nextPairs==NULL) || (howmuch==0)) return;
  while ((k>0) && (syzstr->res[index]->m[k-1]==NULL)) k--;
  while ((ks>0) && (syzstr->res[index+1]->m[ks-1]==NULL)) ks--;
  spl1 = syLinStrat(nextPairs,syzstr,howmuch,index);
  i=0;
  while ((*spl1)[i]>0)
  {
    need_reset = FALSE;
    tso = nextPairs[(*spl1)[i]-1];
    if ((tso.p1!=NULL) && (tso.p2!=NULL))
    {
      coefgcd =
        nGcd(pGetCoeff(tso.p1),pGetCoeff(tso.p2));
      tso.syz = pHead(tso.lcm);
      p = tso.syz;
      pSetCoeff(p,nDiv(pGetCoeff(tso.p1),coefgcd));
      pGetCoeff(p) = nNeg(pGetCoeff(p));
      pSetComp(p,tso.ind2+1);
      rSetmS(p, Components, ShiftedComponents); // actueller index
      pNext(p) = pHead(tso.lcm);
      pIter(p);
      pSetComp(p,tso.ind1+1);
      rSetmS(p, Components, ShiftedComponents); // actueller index
      pSetCoeff(p,nDiv(pGetCoeff(tso.p2),coefgcd));
      nDelete(&coefgcd);
      if (tso.p != NULL)
      {
        kBucketInit(syzstr->bucket,tso.p,-1);
        q = kBucketGetLm(syzstr->bucket);
        j = Fin[pGetComp(q)]-1;
        int pos = j+Hin[pGetComp(q)];
        loop
        {
          if (j<0) break;
          if (pDivisibleBy2(redset[j],q))
          {
            pNext(p) = pHead(q);
            pIter(p);
            pSetComp(p,bin[j]+1);
            rSetmS(p, Components, ShiftedComponents); // actueller index
//if (pLength(redset[j])!=syzstr->elemLength[index][bin[j]])
//Print("Halt");
//if (pLength(redset[j])!=syzstr->elemLength[index][bin[j]])
//Print("Halt");
            pGetCoeff(p) = nNeg(pGetCoeff(p));
            number up = kBucketPolyRed(syzstr->bucket,redset[j],elL[bin[j]],
                                       NULL);
            // Thomas: Check whether you need number here
            nDelete(&up);
            q = kBucketGetLm(syzstr->bucket);
            if (q==NULL) break;
            j = Fin[pGetComp(q)]-1;
            pos = j+Hin[pGetComp(q)];
          }
          else
          {
            j++;
            if (j==pos) break;
          }
        }
        int lb;
        kBucketClear(syzstr->bucket,&tso.p,&lb);
      }
      if (tso.p != NULL)
      {
        if (TEST_OPT_PROT) Print("g");
        if (k==IDELEMS((syzstr->res)[index]))
        {
          syEnlargeFields(syzstr,index);
          bin=syzstr->backcomponents[index];
          elL=syzstr->elemLength[index];
          redset=syzstr->orderedRes[index]->m;
          Components = syzstr->truecomponents[index];
          ShiftedComponents = syzstr->ShiftedComponents[index];
        }
        pNext(p) = pHead(tso.p);
        pIter(p);

        assume(p!= NULL);
        k++;
        syzstr->res[index]->m[k-1] = tso.p;
        syzstr->elemLength[index][k-1] = pLength(tso.p);
        pNorm(syzstr->res[index]->m[k-1]);
        need_reset = syOrder(syzstr->res[index]->m[k-1],syzstr,index,k);
        pSetComp(p,k); // actueller index
        rSetmS(p, Components, ShiftedComponents);
        pGetCoeff(p) = nNeg(pGetCoeff(p));

        tso.isNotMinimal = p;
        tso.p = NULL;
      }
      else
      {
        if (TEST_OPT_PROT) Print(".");
        //if (index % 2==0)
          //euler++;
        //else
          //euler--;
      }
      if (ks==IDELEMS(syzstr->res[index+1]))
      {
        syEnlargeFields(syzstr,index+1);
      }
      syzstr->res[index+1]->m[ks] = tso.syz;
      syzstr->elemLength[index+1][ks] = pLength(tso.syz);
      pNorm(syzstr->res[index+1]->m[ks]);
      tso.syz =NULL;
      tso.syzind = ks;
      if (need_reset)
        syResetShiftedComponents(syzstr, index+1);
      if (syOrder(syzstr->res[index+1]->m[ks],syzstr,index+1,ks+1))
         syResetShiftedComponents(syzstr, index+2);
      ks++;
      p = NULL;
      nextPairs[(*spl1)[i]-1] = tso;
    }
    i++;
  }
  delete spl1;
}

/*3
* reduces the generators of the module index in degree deg
* (which are actual syzygies of the module index-1)
* wrt. the ideal generated by elements of lower degrees
*/
static void syRedGenerOfCurrDeg(syStrategy syzstr, int deg, int index)
{
  ideal res=syzstr->res[index];
  int i=0,j,k=IDELEMS(res),kk;
  SSet sPairs=syzstr->resPairs[index-1];

  while ((k>0) && (res->m[k-1]==NULL)) k--;
  while ((i<(*syzstr->Tl)[index-1]) && (((sPairs)[i].syz==NULL) ||
          ((sPairs)[i].order<deg)))
    i++;
  if ((i>=(*syzstr->Tl)[index-1]) || ((sPairs)[i].order>deg)) return;
  while ((i<(*syzstr->Tl)[index-1]) && (((sPairs)[i].syz==NULL) ||
         ((sPairs)[i].order==deg)))
  {
    if ((sPairs)[i].syz!=NULL)
    {
      j = k-1;
      while ((j>=0) && (res->m[j]!=NULL) &&
             ((sPairs)[i].syz!=NULL))
      {
        if (pDivisibleBy1(res->m[j],(sPairs)[i].syz))
        {
          (sPairs)[i].syz =
            ksOldSpolyRed(res->m[j],(sPairs)[i].syz);
            //sySPolyRed((sPairs)[i].syz,res->m[j]);
          j = k-1;
        }
        else
        {
          j--;
        }
      }
      if ((sPairs)[i].syz != NULL)
      {
        if (k==IDELEMS(res))
        {
          syEnlargeFields(syzstr,index);
          res=syzstr->res[index];
        }
        if (BTEST1(6))
        {
          if ((sPairs)[i].isNotMinimal==NULL)
          {
            PrintLn();
            Print("minimal generator: ");pWrite((syzstr->resPairs[index-1])[i].syz);
            Print("comes from: ");pWrite((syzstr->resPairs[index-1])[i].p1);
            Print("and: ");pWrite((syzstr->resPairs[index-1])[i].p2);
          }
        }
        //res->m[k] = (sPairs)[i].syz;
        res->m[k] = syRedtail((sPairs)[i].syz,syzstr,index);
        (sPairs)[i].syzind = k;
        syzstr->elemLength[index][k] = pLength((sPairs)[i].syz);
        pNorm(res->m[k]);
  //      (sPairs)[i].syz = NULL;
        k++;
        if (syOrder(res->m[k-1],syzstr,index,k))
          syResetShiftedComponents(syzstr, index);
        //euler++;
      }
      else
        (sPairs)[i].syzind = -1;
    }
    i++;
  }
}

/*3
* puts a pair into the right place in resPairs
*/
static void syEnterPair(SSet sPairs, SObject * so, int * sPlength,int index)
{
  int ll,k,no=(*so).order,sP=*sPlength,i;
  poly p=(*so).lcm;

  if ((sP==0) || (sPairs[sP-1].order<=no))
    ll = sP;
  else if (sP==1)
    ll = 0;
  else
  {
    int an=0,en=sP-1;
    loop
    {
      if (an>=en-1)
      {
        if ((sPairs[an].order<=no) && (sPairs[an+1].order>no))
        {
          ll = an+1;
          break;
        }
        else if ((sPairs[en].order<=no) && (sPairs[en+1].order>no))
        {
          ll = en+1;
          break;
        }
        else if (sPairs[an].order>no)
        {
          ll = an;
          break;
        }
        else
        {
          Print("Hier ist was faul!\n");
          break;
        }
      }
      i=(an+en) / 2;
      if (sPairs[i].order <= no)
        an=i;
      else
        en=i;
    }
  }
  for (k=(*sPlength);k>ll;k--)
  {
    syCopyPair(&sPairs[k-1],&sPairs[k]);
  }
  syCopyPair(so,&sPairs[ll]);
  (*sPlength)++;
}
void syEnterPair(syStrategy syzstr, SObject * so, int * sPlength,int index)
{
  int ll;

  if (*sPlength>=(*syzstr->Tl)[index])
  {
    SSet temp = (SSet)Alloc0(((*syzstr->Tl)[index]+16)*sizeof(SObject));
    for (ll=0;ll<(*syzstr->Tl)[index];ll++)
    {
      temp[ll].p = (syzstr->resPairs[index])[ll].p;
      temp[ll].p1 = (syzstr->resPairs[index])[ll].p1;
      temp[ll].p2 = (syzstr->resPairs[index])[ll].p2;
      temp[ll].syz = (syzstr->resPairs[index])[ll].syz;
      temp[ll].lcm = (syzstr->resPairs[index])[ll].lcm;
      temp[ll].ind1 = (syzstr->resPairs[index])[ll].ind1;
      temp[ll].ind2 = (syzstr->resPairs[index])[ll].ind2;
      temp[ll].syzind = (syzstr->resPairs[index])[ll].syzind;
      temp[ll].order = (syzstr->resPairs[index])[ll].order;
      temp[ll].isNotMinimal = (syzstr->resPairs[index])[ll].isNotMinimal;
      temp[ll].length = (syzstr->resPairs[index])[ll].length;
      temp[ll].reference = (syzstr->resPairs[index])[ll].reference;
    }
    Free((ADDRESS)syzstr->resPairs[index],(*syzstr->Tl)[index]*sizeof(SObject));
    (*syzstr->Tl)[index] += 16;
    syzstr->resPairs[index] = temp;
  }
  syEnterPair(syzstr->resPairs[index],so,sPlength,index);
}

/*3
* computes pairs from the new elements (beginning with the element newEl)
* in the module index
*/
static void syCreateNewPairs(syStrategy syzstr, int index, int newEl)
{
  SSet temp;
  SObject tso;
  int i,ii,j,k=IDELEMS(syzstr->res[index]),l=(*syzstr->Tl)[index],ll;
  int qc,first,pos,jj,j1;
  int * bci=syzstr->backcomponents[index];
  poly p,q;
  polyset rs=syzstr->res[index]->m,nPm;


  while ((k>0) && (rs[k-1]==NULL)) k--;
  if (newEl>=k) return;

  long * ShiftedComponents = syzstr->ShiftedComponents[index];
  int* Components = syzstr->truecomponents[index];

  ideal nP=idInit(k,syzstr->res[index]->rank);
  nPm=nP->m;
  while ((l>0) && ((syzstr->resPairs[index])[l-1].p1==NULL)) l--;
  for (j=newEl;j<k;j++)
  {
    q = rs[j];
    qc = pGetComp(q);
    first = syzstr->Firstelem[index-1][pGetComp(q)]-1;
    pos = first+syzstr->Howmuch[index-1][pGetComp(q)];
    for (i=first;i<pos;i++)
    {
      jj = bci[i];
      if (jj>=j) break;
      p = pOne();
      pLcm(rs[jj],q,p);
      pSetComp(p,j+1);
      rSetmS(p, Components, ShiftedComponents);
      ii = first;
      loop
      {
        j1 = bci[ii];
        if (nPm[j1]!=NULL)
        {
          if (pDivisibleBy2(nPm[j1],p))
          {
            pDelete(&p);
            break;
          }
          else if (pDivisibleBy2(p,nPm[j1]))
          {
            pDelete(&(nPm[j1]));
            //break;
          }
        }
        ii++;
        if (ii>=pos) break;
      }
      if (p!=NULL)
      {
        nPm[jj] = p;
      }
    }
    for (i=first;i<pos;i++)
    {
      ii = bci[i];
      if (nPm[ii]!=NULL)
      {
        if (l>=(*syzstr->Tl)[index])
        {
          temp = (SSet)Alloc0(((*syzstr->Tl)[index]+16)*sizeof(SObject));
          for (ll=0;ll<(*syzstr->Tl)[index];ll++)
          {
            temp[ll].p = (syzstr->resPairs[index])[ll].p;
            temp[ll].p1 = (syzstr->resPairs[index])[ll].p1;
            temp[ll].p2 = (syzstr->resPairs[index])[ll].p2;
            temp[ll].syz = (syzstr->resPairs[index])[ll].syz;
            temp[ll].lcm = (syzstr->resPairs[index])[ll].lcm;
            temp[ll].ind1 = (syzstr->resPairs[index])[ll].ind1;
            temp[ll].ind2 = (syzstr->resPairs[index])[ll].ind2;
            temp[ll].syzind = (syzstr->resPairs[index])[ll].syzind;
            temp[ll].order = (syzstr->resPairs[index])[ll].order;
            temp[ll].isNotMinimal = (syzstr->resPairs[index])[ll].isNotMinimal;
          }
          Free((ADDRESS)syzstr->resPairs[index],(*syzstr->Tl)[index]*sizeof(SObject));
          (*syzstr->Tl)[index] += 16;
          syzstr->resPairs[index] = temp;
        }
        tso.lcm = p = nPm[ii];
        nPm[ii] = NULL;
        tso.order = pGetOrder(p) = pTotaldegree(p);
        if ((syzstr->cw!=NULL) && (index>0) && (pGetComp(q)>0))
        {
          int ii=index-1,jj=pGetComp(q);
          while (ii>0)
          {
            jj = pGetComp(syzstr->res[ii]->m[jj-1]);
            ii--;
          }
          tso.order += (*syzstr->cw)[jj-1];
        }
        tso.p1 = rs[ii];
        tso.p2 = q;
        tso.ind1 = ii;
        tso.ind2 = j;
        tso.syzind = -1;
        tso.isNotMinimal = NULL;
        tso.p = NULL;
        tso.syz = NULL;
        syEnterPair(syzstr->resPairs[index],&tso,&l,index);
      }
    }
  }
  idDelete(&nP);
}

static SSet syChosePairsPutIn(syStrategy syzstr, int *index,
               int *howmuch, int * actdeg, int an, int en)
{
  int newdeg=*actdeg,newindex=-1,i,t,sldeg;
  poly p;
  SSet result;
  SRes resPairs=syzstr->resPairs;

  if (an>syzstr->length) return NULL;
  if (en>syzstr->length) en=syzstr->length;
  while (*index<en)
  {
    if (resPairs[*index]!=NULL)
    {
      sldeg = (*actdeg)+*index;
      i = 0;
      if (*index!=0)
      {
        while ((i<(*syzstr->Tl)[*index]))
        {
          if ((resPairs[*index])[i].lcm!=NULL)
          {
            if ((resPairs[*index])[i].order == sldeg)
            {
              result = &(resPairs[*index])[i];
              *howmuch =1;
              i++;
              while ((i<(*syzstr->Tl)[*index]) && ((resPairs[*index])[i].lcm!=NULL)
                      && ((resPairs[*index])[i].order == sldeg))
              {
                i++;
                (*howmuch)++;
              }
              return result;
            }
          }
          i++;
        }
      }
      else
      {
        while ((i<(*syzstr->Tl)[*index]))
        {
          if ((resPairs[*index])[i].syz!=NULL)
          {
            if ((resPairs[*index])[i].order == sldeg)
            {
              result = &(resPairs[*index])[i];
              (*howmuch) =1;
              i++;
              while ((i<(*syzstr->Tl)[*index]) && ((resPairs[*index])[i].syz!=NULL)
                      && ((resPairs[*index])[i].order == *actdeg))
              {
                i++;
                (*howmuch)++;
              }
              return result;
            }
          }
          i++;
        }
      }
    }
    (*index)++;
  }
  *index = an;
  //if (TEST_OPT_PROT) Print("(Euler:%d)",euler);
  while (*index<en)
  {
    if (resPairs[*index]!=NULL)
    {
      i = 0;
      while ((i<(*syzstr->Tl)[*index]))
      {
        t = *actdeg+*index;
        if (((resPairs[*index])[i].lcm!=NULL) ||
              ((resPairs[*index])[i].syz!=NULL))
        {
          if ((resPairs[*index])[i].order > t)
            t = (resPairs[*index])[i].order;
        }
        if ((t>*actdeg+*index) && ((newdeg==*actdeg) || (t<newdeg+*index)))
        {
          newdeg = t-*index;
          newindex = *index;
          break;
        }
        i++;
      }
    }
    (*index)++;
  }
  if (newdeg>*actdeg)
  {
    *actdeg = newdeg;
    *index = newindex;
    return syChosePairsPutIn(syzstr,index,howmuch,actdeg,an,en);
  }
  else return NULL;
}

/*3
* FOR THE HOMOGENEOUS CASE ONLY!
* looks through the pair set and the given module for
* remaining pairs or generators to consider
* returns a pointer to the first pair and the number of them in the given module
* works with slanted degree (i.e. deg=realdeg-index)
*/
SSet syChosePairs(syStrategy syzstr, int *index, int *howmuch, int * actdeg)
{
  return syChosePairsPutIn(syzsts,index,howmuch,actdeg,0,syzstr->length);
}

/*3
* FOR THE INHOMOGENEOUS CASE ONLY!
* looks through the pair set and the given module for
* remaining pairs or generators to consider
* returns a pointer to the first pair and the number of them in the given module
* works with slanted degree (i.e. deg=realdeg-index)
* looks first through the 0 and 1 module then through the other
*/
static SSet syChosePairsIH(syStrategy syzstr, int *index,
               int *howmuch, int * actdeg, int mindeg)
{
  SSet result=NULL;

  result = syChosePairsPutIn(syzstr,index,howmuch,actdeg,0,2);
  if (result == NULL)
  {
    *actdeg = mindeg;
    result = syChosePairsPutIn(syzstr,index,howmuch,actdeg,2,syzstr->length);
  }
  return result;
}

/*3
* looks through the pair set and the given module for
* remaining pairs or generators to consider
* returns a pointer to the first pair and the number of them in the given module
* works deg by deg
*/
/*
*static SSet syChosePairs1(SRes resPairs,intvec * Tl, int *index, int *howmuch,
*                   int length,int * actdeg)
*{
*  int newdeg=*actdeg,newindex=-1,i,t;
*  SSet result;
*
*  while (*index>=0)
*  {
*    if (resPairs[*index]!=NULL)
*    {
*      i = 0;
*      if (*index!=0)
*      {
*        while ((i<(*Tl)[*index]))
*        {
*          if ((resPairs[*index])[i].lcm!=NULL)
*          {
*            if (pGetOrder((resPairs[*index])[i].lcm) == *actdeg)
*            {
*              result = &(resPairs[*index])[i];
*              *howmuch =1;
*              i++;
*              while ((i<(*Tl)[*index]) && ((resPairs[*index])[i].lcm!=NULL)
*                      && (pGetOrder((resPairs[*index])[i].lcm) == *actdeg))
*              {
*                i++;
*                (*howmuch)++;
*              }
*              return result;
*            }
*          }
*          i++;
*        }
*      }
*      else
*      {
*        while ((i<(*Tl)[*index]))
*        {
*          if ((resPairs[*index])[i].syz!=NULL)
*          {
*            if ((resPairs[*index])[i].order == *actdeg)
*            {
*              result = &(resPairs[*index])[i];
*              (*howmuch) =1;
*              i++;
*              while ((i<(*Tl)[*index]) && ((resPairs[*index])[i].syz!=NULL)
*                      && ((resPairs[*index])[i].order == *actdeg))
*              {
*                i++;
*                (*howmuch)++;
*              }
*              return result;
*            }
*          }
*          i++;
*        }
*      }
*    }
*    (*index)--;
*  }
*  *index = length-1;
*  while (*index>=0)
*  {
*    if (resPairs[*index]!=NULL)
*    {
*      i = 0;
*      while ((i<(*Tl)[*index]))
*      {
*        t = *actdeg;
*        if ((resPairs[*index])[i].lcm!=NULL)
*        {
*          if (pGetOrder((resPairs[*index])[i].lcm) > *actdeg)
*            t = pGetOrder((resPairs[*index])[i].lcm);
*        }
*        else if ((resPairs[*index])[i].syz!=NULL)
*        {
*          if ((resPairs[*index])[i].order > *actdeg)
*            t = (resPairs[*index])[i].order;
*        }
*        if ((t>*actdeg) && ((newdeg==*actdeg) || (t<newdeg)))
*        {
*          newdeg = t;
*          newindex = *index;
*          break;
*        }
*        i++;
*      }
*    }
*    (*index)--;
*  }
*  if (newdeg>*actdeg)
*  {
*    *actdeg = newdeg;
*    *index = newindex;
*    return syChosePairs1(resPairs,Tl,index,howmuch,length,actdeg);
*  }
*  else return NULL;
*}
*/
/*3
* statistics of the resolution
*/
static void syStatistics(resolvente res,int length)
{
  int i,j=1,k;
  Order_t deg = 0;

  PrintLn();
  while ((j<length) && (res[j]!=NULL))
  {
    Print("In module %d: \n",j);
    k = 0;
    while ((k<IDELEMS(res[j])) && (res[j]->m[k]!=NULL))
    {
      i = 1;
      deg = pGetOrder(res[j]->m[k]);
      k++;
      while ((k<IDELEMS(res[j])) && (res[j]->m[k]!=NULL) &&
              (pGetOrder(res[j]->m[k])==deg))
      {
        i++;
        k++;
      }
      Print("%d elements of degree %d\n",i,deg);
    }
    j++;
  }
}

/*3
* initialize a module
*/
int syInitSyzMod(syStrategy syzstr, int index, int init)
{
  int result;

  if (syzstr->res[index]==NULL)
  {
    syzstr->res[index] = idInit(init-1,1);
    syzstr->truecomponents[index] = (int*)Alloc0(init*sizeof(int));
    syzstr->ShiftedComponents[index] = (long*)Alloc0(init*sizeof(long));
    if (index==0)
    {
      for (int i=0;i<init;i++)
      {
        syzstr->truecomponents[0][i] = i;
        syzstr->ShiftedComponents[0][i] = (i)*SYZ_SHIFT_BASE;
      }
    }
    syzstr->backcomponents[index] = (int*)Alloc0(init*sizeof(int));
    syzstr->Howmuch[index] = (int*)Alloc0(init*sizeof(int));
    syzstr->Firstelem[index] = (int*)Alloc0(init*sizeof(int));
    syzstr->elemLength[index] = (int*)Alloc0(init*sizeof(int));
    syzstr->orderedRes[index] = idInit(init-1,1);
    syzstr->sev[index] = (unsigned long*) Alloc0(init*sizeof(unsigned long));
    result = 0;
  }
  else
  {
    result = IDELEMS(syzstr->res[index]);
    while ((result>0) && (syzstr->res[index]->m[result-1]==NULL)) result--;
  }
  return result;
}

/*3
* deletes a resolution
*/
void syKillComputation(syStrategy syzstr)
{
  if (syzstr->references>0)
  {
    (syzstr->references)--;
  }
  else
  {
    int i,j;
    if (syzstr->minres!=NULL)
    {
      for (i=0;i<syzstr->length;i++)
      {
        if (syzstr->minres[i]!=NULL)
        {
          for (j=0;j<IDELEMS(syzstr->minres[i]);j++)
          {
            if (syzstr->minres[i]->m[j]!=NULL)
              pDelete(&(syzstr->minres[i]->m[j]));
          }
        }
        idDelete(&(syzstr->minres[i]));
      }
      Free((ADDRESS)syzstr->minres,(syzstr->length+1)*sizeof(ideal));
    }
    if (syzstr->fullres!=NULL)
    {
      for (i=0;i<syzstr->length;i++)
      {
        if (syzstr->fullres[i]!=NULL)
        {
          for (j=0;j<IDELEMS(syzstr->fullres[i]);j++)
          {
            if (syzstr->fullres[i]->m[j]!=NULL)
              pDelete(&(syzstr->fullres[i]->m[j]));
          }
        }
        idDelete(&(syzstr->fullres[i]));
      }
      Free((ADDRESS)syzstr->fullres,(syzstr->length+1)*sizeof(ideal));
    }
    ring origR = currRing;

    if (syzstr->syRing != NULL)
      rChangeCurrRing(syzstr->syRing, FALSE);

    if (syzstr->resPairs!=NULL)
    {
      for (i=0;i<syzstr->length;i++)
      {
        for (j=0;j<(*syzstr->Tl)[i];j++)
        {
          if ((syzstr->resPairs[i])[j].lcm!=NULL)
            pDelete(&((syzstr->resPairs[i])[j].lcm));
        }
        if (syzstr->orderedRes[i]!=NULL)
        {
          for (j=0;j<IDELEMS(syzstr->orderedRes[i]);j++)
          {
            syzstr->orderedRes[i]->m[j] = NULL;
          }
        }
        idDelete(&(syzstr->orderedRes[i]));
        if (syzstr->truecomponents[i]!=NULL)
        {
          Free((ADDRESS)syzstr->truecomponents[i],(IDELEMS(syzstr->res[i])+1)*sizeof(int));
          syzstr->truecomponents[i]=NULL;
          Free((ADDRESS)syzstr->ShiftedComponents[i],(IDELEMS(syzstr->res[i])+1)*sizeof(long));
          syzstr->ShiftedComponents[i]=NULL;
        }
        if (syzstr->backcomponents[i]!=NULL)
        {
          Free((ADDRESS)syzstr->backcomponents[i],(IDELEMS(syzstr->res[i])+1)*sizeof(int));
          syzstr->backcomponents[i]=NULL;
        }
        if (syzstr->Howmuch[i]!=NULL)
        {
          Free((ADDRESS)syzstr->Howmuch[i],(IDELEMS(syzstr->res[i])+1)*sizeof(int));
          syzstr->Howmuch[i]=NULL;
        }
        if (syzstr->Firstelem[i]!=NULL)
        {
          Free((ADDRESS)syzstr->Firstelem[i],(IDELEMS(syzstr->res[i])+1)*sizeof(int));
          syzstr->Firstelem[i]=NULL;
        }
        if (syzstr->res[i]!=NULL)
        {
          for (j=0;j<IDELEMS(syzstr->res[i]);j++)
          {
            if (syzstr->res[i]->m[j]!=NULL)
              pDelete(&(syzstr->res[i]->m[j]));
          }
        }
        if (syzstr->weights!=0)
        {
          if (syzstr->weights[i]!=NULL)
          {
            delete syzstr->weights[i];
          }
          Free((ADDRESS)syzstr->weights,syzstr->length*sizeof(intvec*));
        }
        if (syzstr->sev[i] != NULL)
          Free((ADDRESS)syzstr->sev[i], (IDELEMS(syzstr->res[i])+1)*sizeof(unsigned long))
        idDelete(&(syzstr->res[i]));
        Free((ADDRESS)syzstr->resPairs[i],(*syzstr->Tl)[i]*sizeof(SObject));
      }
      Free((ADDRESS)syzstr->resPairs,syzstr->length*sizeof(SObject*));
      Free((ADDRESS)syzstr->res,(syzstr->length+1)*sizeof(ideal));
      Free((ADDRESS)syzstr->orderedRes,(syzstr->length+1)*sizeof(ideal));
      Free((ADDRESS)syzstr->elemLength,(syzstr->length+1)*sizeof(int*));
      Free((ADDRESS)syzstr->truecomponents,(syzstr->length+1)*sizeof(int*));
      Free((ADDRESS)syzstr->ShiftedComponents,(syzstr->length+1)*sizeof(long*));
      if (syzstr->sev != NULL)
        Free(((ADDRESS)syzstr->sev), (syzstr->length+1)*sizeof(unsigned long*));
      Free((ADDRESS)syzstr->backcomponents,(syzstr->length+1)*sizeof(int*));
      Free((ADDRESS)syzstr->Howmuch,(syzstr->length+1)*sizeof(int*));
      Free((ADDRESS)syzstr->Firstelem,(syzstr->length+1)*sizeof(int*));
    }
    if (syzstr->cw!=NULL)
      delete syzstr->cw;
    if (syzstr->betti!=NULL)
      delete syzstr->betti;
    if (syzstr->resolution!=NULL)
      delete syzstr->resolution;
    if (syzstr->syRing != NULL)
    {
      rChangeCurrRing(origR, FALSE);
      rKill(syzstr->syRing);
    }
    FreeSizeOf((ADDRESS)syzstr,ssyStrategy);
  }
}

/*3
* read out the Betti numbers from resolution
* (if not LaScala calls the traditional Betti procedure)
*/
intvec * syBettiOfComputation(syStrategy syzstr, BOOLEAN minim)
{
  int dummy;
  if (syzstr->betti!=NULL)
  {
    return ivCopy(syzstr->betti);
  }
  intvec *result;
  if (syzstr->resPairs!=NULL)
  {
    int i,j=-1,jj=-1,l,sh=0;
    SRes rP=syzstr->resPairs;

    if (syzstr->hilb_coeffs!=NULL) sh = 1;
    l = syzstr->length;
    while ((l>0) && (rP[l-1]==NULL)) l--;
    if (l==0) return NULL;
    l--;
    while (l>=sh)
    {
      i = 0;
      while ((i<(*syzstr->Tl)[l]) &&
        ((rP[l][i].lcm!=NULL) || (rP[l][i].syz!=NULL)))
      {
        if (rP[l][i].isNotMinimal==NULL)
        {
          if (j<rP[l][i].order-l)
            j = rP[l][i].order-l;
          if (jj<l)
            jj = l;
        }
        i++;
      }
      l--;
    }
    j = j+sh;
    jj = jj+2;
    result=new intvec(j,jj-sh,0);
    IMATELEM(*result,1,1) = max(1,idRankFreeModule(syzstr->res[1]));
    for (i=sh;i<jj;i++)
    {
      j = 0;
      while (j<(*syzstr->Tl)[i])
      {
        if ((rP[i][j].isNotMinimal==NULL)&&
           ((rP[i][j].lcm!=NULL) || (rP[i][j].syz!=NULL)))
          IMATELEM(*result,rP[i][j].order-i+sh,i+2-sh)++;
        j++;
      }
    }
    syzstr->betti = result;
  }
  else if (syzstr->fullres!=NULL)
    syzstr->betti = syBetti(syzstr->fullres,syzstr->length,&dummy,NULL,minim);
  else
    syzstr->betti = syBetti(syzstr->minres,syzstr->length,&dummy,NULL,minim);
  return ivCopy(syzstr->betti);
}

/*2
* read out the Betti numbers from resolution
* (interpreter interface)
*/
BOOLEAN syBetti2(leftv res, leftv u, leftv w)
{
  syStrategy syzstr=(syStrategy)u->Data();
  BOOLEAN minim=(int)w->Data();

  res->data=(void *)syBettiOfComputation(syzstr,minim);
  return FALSE;
}
BOOLEAN syBetti1(leftv res, leftv u)
{
  syStrategy syzstr=(syStrategy)u->Data();

  res->data=(void *)syBettiOfComputation(syzstr);
  return FALSE;
}

/*3
* computes the allocated length of the resolution
*/
int syLength(syStrategy syzstr)
{
  return syzstr->length;
}

/*3
* computes the real length of the resolution
*/
int sySize(syStrategy syzstr)
{
  resolvente r=syzstr->res;
  if (r==NULL)
    r = syzstr->fullres;
  if (r==NULL)
    r = syzstr->minres;
  if (r==NULL)
  {
    WerrorS("No resolution found");
    return 0;
  }
  int i=syzstr->length;
  while ((i>0) && (r[i-1]==NULL)) i--;
  return i;
}

/*3
* computes the cohomological dimension of res[1]
*/
int syDim(syStrategy syzstr)
{
  int i,j=-1,l;
  if (syzstr->resPairs!=NULL)
  {
    SRes rP=syzstr->resPairs;

    l = syzstr->length;
    while ((l>0) && (rP[l-1]==NULL)) l--;
    if (l==0) return -1;
    l--;
    while (l>=0)
    {
      i = 0;
      while ((i<(*syzstr->Tl)[l]) &&
        ((rP[l][i].lcm!=NULL) || (rP[l][i].syz!=NULL)) &&
        (rP[l][i].isNotMinimal!=NULL))
      {
        i++;
      }
      if ((i<(*syzstr->Tl)[l]) &&
        ((rP[l][i].lcm!=NULL) || (rP[l][i].syz!=NULL)) &&
        (rP[l][i].isNotMinimal==NULL))
        return l;
      l--;
    }
    return l;
  }
  else
    return sySize(syzstr);
}

/*3
* copies the resolution (by increment the reference counter)
*/
syStrategy syCopy(syStrategy syzstr)
{
  syStrategy result=syzstr;
  (result->references)++;
  return result;
}

/*2
* local print procedure used in syPrint
*/
static void syPrintEmptySpaces(int i)
{
  if (i!=0)
  {
    Print(" ");
    syPrintEmptySpaces(i/10);
  }
}

/*2
* local print procedure used in syPrint
*/
static void syPrintEmptySpaces1(int i)
{
  if (i!=0)
  {
    Print(" ");
    syPrintEmptySpaces1(i-1);
  }
}

/*2
* local print procedure used in syPrint
*/
static int syLengthInt(int i)
{
  int j=0;

  if (i==0) return 1;
  while (i!=0)
  {
    j++;
    i = i/10;
  }
  return j;
}

/*3
* prints the resolution as sequence of free modules
*/
void syPrint(syStrategy syzstr)
{
  if ((syzstr->resPairs==NULL) && (syzstr->fullres==NULL)
     && (syzstr->minres==NULL))
  {
    Print("No resolution defined\n");
    return;
  }
  int l=0;
  if (syzstr->resolution==NULL)
  {
    int j;
    if (syzstr->resPairs!=NULL)
    {
      syzstr->resolution = new intvec(syzstr->length+1);
      SRes rP=syzstr->resPairs;
      (*syzstr->resolution)[0] = max(1,idRankFreeModule(syzstr->res[1]));
      while ((l<syzstr->length) && (rP[l]!=NULL))
      {
        j=0;
        while ((j<(*syzstr->Tl)[l]) &&
          ((rP[l][j].lcm!=NULL) || (rP[l][j].syz!=NULL)))
        {
          if (rP[l][j].isNotMinimal==NULL)
            ((*syzstr->resolution)[l+1])++;
          j++;
        }
        l++;
      }
    }
    else
    {
      resolvente rr;
      syzstr->resolution = new intvec(syzstr->length+2);
      if (syzstr->minres!=NULL)
        rr = syzstr->minres;
      else
        rr = syzstr->fullres;
      (*syzstr->resolution)[0] = max(1,idRankFreeModule(rr[0]));
      while ((l<syzstr->length) && (rr[l]!=NULL))
      {
        j = IDELEMS(rr[l]);
        while ((l>0) && (rr[l]->m[j-1]==NULL)) j--;
        ((*syzstr->resolution)[l+1]) = j;
        l++;
      }
    }
  }
  char *sn=currRingHdl->id;
  int sl=strlen(sn);
  syPrintEmptySpaces1(sl);
  l = 0;
  loop
  {
    Print("%d",(*syzstr->resolution)[l]);
    if ((l>=syzstr->resolution->length()) || ((*syzstr->resolution)[l]==0))
      break;
    syPrintEmptySpaces1(sl+5);
    l++;
  }
  PrintLn();
  l = 0;
  loop
  {
    Print(sn);
    if ((l>=syzstr->resolution->length()) || ((*syzstr->resolution)[l]==0))
      break;
    syPrintEmptySpaces((*syzstr->resolution)[l]);
    Print(" <-- ");
    l++;
  }
  PrintLn();
  PrintLn();
  l = 0;
  loop
  {
    Print("%d",l);
    if ((l>=syzstr->resolution->length()) || ((*syzstr->resolution)[l]==0))
      break;
    syPrintEmptySpaces1(sl+5+syLengthInt((*syzstr->resolution)[l])-
                         syLengthInt(l));
    l++;
  }
  PrintLn();
  if (syzstr->minres==NULL)
  {
    Print("resolution not minimized yet");
    PrintLn();
  }
}

/*2
* divides out the weight monomials (given by the Schreyer-ordering)
* from the LaScala-resolution
*/
static resolvente syReorder(resolvente res,int length,
        syStrategy syzstr,BOOLEAN toCopy=TRUE,resolvente totake=NULL)
{
  int i,j,l;
  poly p,q,tq;
  polyset ri1;
  resolvente fullres;
  ring origR=syzstr->syRing;
  fullres = (resolvente)Alloc0((length+1)*sizeof(ideal));
  if (totake==NULL)
    totake = res;
  for (i=length-1;i>0;i--)
  {
    if (res[i]!=NULL)
    {
      if (i>1)
      {
        j = IDELEMS(res[i-1]);
        while ((j>0) && (res[i-1]->m[j-1]==NULL)) j--;
        fullres[i-1] = idInit(IDELEMS(res[i]),j);
        ri1 = totake[i-1]->m;
        for (j=IDELEMS(res[i])-1;j>=0;j--)
        {
          p = res[i]->m[j];
          q = NULL;
          while (p!=NULL)
          {
            if (toCopy)
            {
              if (origR!=NULL)
                tq = pFetchHead(origR,p);
              else
                tq = pHead(p);
              pIter(p);
            }
            else
            {
              res[i]->m[j] = NULL;
              if (origR!=NULL)
              {
                poly pp=p;
                pIter(p);
                pNext(pp)=NULL;
                tq = pFetchCopyDelete(origR,pp);
              }
              else
              {
                tq = p;
                pIter(p);
                pNext(tq) = NULL;
              }
            }
            for (l=pVariables;l>0;l--)
            {
              if (origR!=NULL)
                pSubExp(tq,l, pRingGetExp(origR,ri1[pGetComp(tq)-1],l));
              else
                pSubExp(tq,l, pGetExp(ri1[pGetComp(tq)-1],l));
            }
            pSetm(tq);
            q = pAdd(q,tq);
          }
          fullres[i-1]->m[j] = q;
        }
      }
      else
      {
        if (origR!=NULL)
        {
          fullres[i-1] = idInit(IDELEMS(res[i]),res[i]->rank);
          for (j=IDELEMS(res[i])-1;j>=0;j--)
          {
            if (toCopy)
              fullres[i-1]->m[j] = pFetchCopy(origR,res[i]->m[j]);
            else
            {
              fullres[i-1]->m[j] = pFetchCopyDelete(origR,res[i]->m[j]);
              res[i]->m[j] = NULL;
            }
          }
        }
        else
        {
          if (toCopy)
            fullres[i-1] = idCopy(res[i]);
          else
          {
            fullres[i-1] = res[i];
            res[i] = NULL;
          }
        }
        for (j=IDELEMS(fullres[i-1])-1;j>=0;j--)
          fullres[i-1]->m[j] = pOrdPolyInsertSetm(fullres[i-1]->m[j]);
      }
      if (!toCopy)
      {
        if (res[i]!=NULL) idDelete(&res[i]);
      }
    }
  }
  if (!toCopy)
    Free((ADDRESS)res,(length+1)*sizeof(ideal));
  //syzstr->length = length;
  return fullres;
}

/*3
* converts a resolution into a list of modules
*/
lists syConvRes(syStrategy syzstr,BOOLEAN toDel)
{
  if ((syzstr->fullres==NULL) && (syzstr->minres==NULL))
  {
    if (syzstr->hilb_coeffs==NULL)
    {
      syzstr->fullres = syReorder(syzstr->res,syzstr->length,syzstr);
    }
    else
    {
      syzstr->minres = syReorder(syzstr->orderedRes,syzstr->length,syzstr);
      syKillEmptyEntres(syzstr->minres,syzstr->length);
    }
  }
  resolvente tr;
  int typ0=IDEAL_CMD;
  if (syzstr->minres!=NULL)
    tr = syzstr->minres;
  else
    tr = syzstr->fullres;
  resolvente trueres=NULL;
  intvec ** w=NULL;
  if (syzstr->length>0)
  {
    trueres=(resolvente)Alloc0((syzstr->length)*sizeof(ideal));
    for (int i=(syzstr->length)-1;i>=0;i--)
    {
      if (tr[i]!=NULL)
      {
        trueres[i] = idCopy(tr[i]);
      }
    }
    if (idRankFreeModule(trueres[0]) > 0)
      typ0 = MODUL_CMD;
    if (syzstr->weights!=NULL)
    {
      w = (intvec**)Alloc0((syzstr->length)*sizeof(intvec*));
      for (int i=(syzstr->length)-1;i>=0;i--)
      {
        if (syzstr->weights[i]!=NULL) w[i] = ivCopy(syzstr->weights[i]);
      }
    }
  }
  lists li = liMakeResolv(trueres,syzstr->length,syzstr->list_length,typ0,w);
  if (toDel) syKillComputation(syzstr);
  return li;
}

/*3
* converts a list of modules into a resolution
*/
syStrategy syConvList(lists li,BOOLEAN toDel)
{
  int typ0;
  syStrategy result=(syStrategy)Alloc0SizeOf(ssyStrategy);

  resolvente fr = liFindRes(li,&(result->length),&typ0,&(result->weights));
  if (fr != NULL)
  {

    result->fullres = (resolvente)Alloc0((result->length+1)*sizeof(ideal));
    for (int i=result->length-1;i>=0;i--)
    {
      if (fr[i]!=NULL)
        result->fullres[i] = idCopy(fr[i]);
    }
    result->list_length=result->length;
    Free((ADDRESS)fr,(result->length)*sizeof(ideal));
  }
  else
  {
    FreeSizeOf (result, ssyStrategy);
    result = NULL;
  }
  if (toDel) li->Clean();
  return result;
}

/*3
* converts a list of modules into a minimal resolution
*/
syStrategy syForceMin(lists li)
{
  int typ0;
  syStrategy result=(syStrategy)Alloc0SizeOf(ssyStrategy);

  resolvente fr = liFindRes(li,&(result->length),&typ0);
  result->minres = (resolvente)Alloc0((result->length+1)*sizeof(ideal));
  for (int i=result->length-1;i>=0;i--)
  {
    if (fr[i]!=NULL)
      result->minres[i] = idCopy(fr[i]);
  }
  Free((ADDRESS)fr,(result->length)*sizeof(ideal));
  return result;
}

/*2
* deleting all monomials the component of which correspond
* to non-minimal generators
*/
static poly syStripOut(poly p,intvec * toStrip)
{
  if (toStrip==NULL) return p;
  poly pp=p;

  while ((pp!=NULL) && ((*toStrip)[pGetComp(pp)]!=0))
    pDelete1(&pp);
  p = pp;
  if (pp!=NULL)
  {
    while (pNext(pp)!=NULL)
    {
      if ((*toStrip)[pGetComp(pNext(pp))]!=0)
        pDelete1(&pNext(pp));
      else
        pIter(pp);
    }
  }
  return p;
}

/*2
* copies only those monomials the component of which correspond
* to minimal generators
*/
static poly syStripOutCopy(poly p,intvec * toStrip)
{
  if (toStrip==NULL) return pCopy(p);
  poly result=NULL,pp;

  while (p!=NULL)
  {
    if ((*toStrip)[pGetComp(p)]==0)
    {
      if (result==NULL)
      {
        result = pp = pHead(p);
      }
      else
      {
        pNext(pp) = pHead(p);
        pIter(pp);
      }
    }
    pIter(p);
  }
  return result;
}

/*2
* minimizes toMin
*/
static poly syMinimizeP(int toMin,syStrategy syzstr,intvec * ordn,int index,
                        intvec * toStrip)
{
  int ii=0,i,j,tc;
  poly p,pp,q=NULL,tq,pisN;
  SSet sPairs=syzstr->resPairs[index];
  poly tempStripped=NULL;

  //pp=pCopy(syzstr->res[index+1]->m[toMin]);
  pp = syStripOutCopy(syzstr->res[index+1]->m[toMin],toStrip);
  while ((ii<ordn->length()) && ((*ordn)[ii]!=-1) &&
             (sPairs[(*ordn)[ii]].syzind!=toMin))
  {
    ii++;
  }
  while (ii>=0)
  {
    i = (*ordn)[ii];
    if (sPairs[i].isNotMinimal!=NULL)
    {
      tempStripped =
        syStripOutCopy(syzstr->res[index+1]->m[sPairs[i].syzind],toStrip);
      pisN = sPairs[i].isNotMinimal;
      tc = pGetComp(pisN);
      p = pp;
      while (p!=NULL)
      {
        if (pGetComp(p)==tc)
        {
          tq = pInit();
          for(j=pVariables; j>0; j--)
            pSetExp(tq,j, pGetExp(p,j)-pGetExp(pisN,j));
          pSetComp(tq, 0);
          pSetCoeff0(tq,nDiv(pGetCoeff(p),pGetCoeff(pisN)));
          pGetCoeff(tq) = nNeg(pGetCoeff(tq));
          pSetm(tq);
          q = pAdd(q,pMultT(pCopy(tempStripped),tq));
          pDelete(&tq);
        }
        pIter(p);
      }
      if (q!=NULL)
      {
        pp = pAdd(pp,q);
        q = NULL;
      }
      pDelete(&tempStripped);
    }
    ii--;
  }
  return pp;
}

/*2
* minimizes toMin
*/
static poly syMinimizeP1(int toMin,syStrategy syzstr,intvec * ordn,int index,
                        intvec * toStrip)
{
  int ii=0,i,j,tc,lp,ltS=-1;
  poly p,mp=NULL,pp,q=NULL,tq,pisN;
  SSet sPairs=syzstr->resPairs[index];
  poly tempStripped=NULL;

  pp = syStripOutCopy(syzstr->res[index+1]->m[toMin],toStrip);
  kBucketInit(syzstr->bucket,pp,-1);
  while ((ii<ordn->length()) && ((*ordn)[ii]!=-1) &&
             (sPairs[(*ordn)[ii]].syzind!=toMin))
  {
    ii++;
  }
  while (ii>=0)
  {
    i = (*ordn)[ii];
    if (sPairs[i].isNotMinimal!=NULL)
    {
      tempStripped =
        syStripOutCopy(syzstr->res[index+1]->m[sPairs[i].syzind],toStrip);
      tc = pGetComp(sPairs[i].isNotMinimal);
      //p = pTakeOutComp1(&tempStripped,tc);
      int lu;
      pTakeOutComp(&tempStripped,tc,&p,&lu);
      kBucketTakeOutComp(syzstr->bucket,tc,&mp,&lp);
      mp = pDivideM(mp,p);
      while (mp!=NULL)
      {
        p = pNext(mp);
        pNext(mp) = NULL;
        ltS = -1;
        kBucket_Minus_m_Mult_p(syzstr->bucket,mp,tempStripped,&ltS);
        mp = p;
      }
      pDelete(&mp);
      pDelete(&tempStripped);
    }
    ii--;
  }
  kBucketClear(syzstr->bucket,&pp,&lp);
  return pp;
}

/*2
* deletes empty components after minimization
*/
void syKillEmptyEntres(resolvente res,int length)
{
  int i,j,jj,k,rj;
  intvec * changes;
  poly p;
  ideal ri;

  for (i=0;i<length;i++)
  {
    ri = res[i];
    if (ri!=NULL)
    {
      rj = IDELEMS(ri);
      changes = new intvec(rj+1,1,-1);
      while ((rj>0) && (ri->m[rj-1]==NULL)) rj--;
      j = k = 0;
      while (j+k<rj)
      {
        if (ri->m[j+k]!=NULL)
        {
          ri->m[j] = ri->m[j+k];
          (*changes)[j+k+1] = j+1;
          j++;
        }
        else
        {
          k++;
        }
      }
      for (jj=j;jj<rj;jj++)
        ri->m[jj] = NULL;
      if (res[i+1]!=NULL)
      {
        ri = res[i+1];
        for (j=IDELEMS(ri)-1;j>=0;j--)
        {
          p = ri->m[j];
          while (p!=NULL)
          {
            pSetComp(p,(*changes)[pGetComp(p)]);
            pSetm(p);
            pIter(p);
          }
        }
      }
    }
  }
}

/*2
* determines the components for minimization
*/
static intvec * syToStrip(syStrategy syzstr, int index)
{
  intvec * result=NULL;

  if ((syzstr->resPairs[index-1]!=NULL) && (!idIs0(syzstr->res[index])))
  {
    result=new intvec(IDELEMS(syzstr->res[index])+1);
    for (int i=(*syzstr->Tl)[index-1]-1;i>=0;i--)
    {
      if (syzstr->resPairs[index-1][i].isNotMinimal!=NULL)
      {
        (*result)[syzstr->resPairs[index-1][i].syzind+1] = 1;
      }
    }
  }
  return result;
}

/*2
* re-computes the order of pairs during the algorithm
* this ensures to procede with a triangular matrix
*/
static intvec * syOrdPairs(SSet sPairs, int length)
{
  intvec * result=new intvec(length,1,-1);
  int i,j=0,k=-1,l,ii;

  loop
  {
    l = -1;
    for(i=0;i<length;i++)
    {
      if (sPairs[i].syzind>k)
      {
        if (l==-1)
        {
          l = sPairs[i].syzind;
          ii = i;
        }
        else
        {
          if (sPairs[i].syzind<l)
          {
            l = sPairs[i].syzind;
            ii = i;
          }
        }
      }
    }
    if (l==-1) break;
    (*result)[j] = ii;
    j++;
    k = l;
  }
  return result;
}

/*2
* minimizes the output of LaScala
*/
static resolvente syReadOutMinimalRes(syStrategy syzstr,
           BOOLEAN computeStd=FALSE)
{
  intvec * Strip, * ordn;
  resolvente tres=(resolvente)Alloc0((syzstr->length+1)*sizeof(ideal));
  ring tmpR = NULL;
  ring origR = currRing;

//Print("Hier ");
  if (computeStd)
  {
    tres[0] = syzstr->res[1];
    syzstr->res[1] = idInit(IDELEMS(tres[0]),tres[0]->rank);
    return tres;
  }
  int i,j,l,index,ii,i1;
  poly p;
  ideal rs;
  SSet sPairs;
  int * ord,*b0,*b1;
  pSetmProc oldSetm=pSetm;
  pCompProc oldComp0=pComp0;

  assume(syzstr->syRing != NULL);
  rChangeCurrRing(syzstr->syRing, TRUE);
//Print("laeufts ");
  pComp0 = syzcomp2dpc;
  syzstr->bucket = kBucketCreate();
  for (index=syzstr->length-1;index>0;index--)
  {
    if (syzstr->resPairs[index]!=NULL)
    {
//Print("ideal %d: \n",index);
      currcomponents = syzstr->truecomponents[index];
      currShiftedComponents = syzstr->ShiftedComponents[index];
      rChangeSComps(currcomponents, currShiftedComponents,
                    IDELEMS(syzstr->res[index]));
      sPairs = syzstr->resPairs[index];
      Strip = syToStrip(syzstr,index);
      tres[index+1] = idInit(IDELEMS(syzstr->res[index+1]),syzstr->res[index+1]->rank);
      i1 = (*syzstr->Tl)[index];
//Print("i1= %d\n",i1);
      ordn = syOrdPairs(sPairs,i1);
      for (i=0;i<i1;i++)
      {
        if ((sPairs[i].isNotMinimal==NULL) && (sPairs[i].lcm!=NULL))
        {
          l = sPairs[i].syzind;
//Print("Minimiere Poly %d: ",l);pWrite(syzstr->res[index+1]->m[l]);
          tres[index+1]->m[l] =
            syMinimizeP1(l,syzstr,ordn,index,Strip);
        }
      }
      delete Strip;
      Strip = NULL;
    }
  }
  currcomponents = syzstr->truecomponents[0];
  currShiftedComponents = syzstr->ShiftedComponents[0];
  rChangeSComps( currcomponents, currShiftedComponents,
                 IDELEMS(syzstr->res[0]));
  tres[1] = idInit(IDELEMS(syzstr->res[1]),syzstr->res[1]->rank);
  sPairs = syzstr->resPairs[0];
  for (i=(*syzstr->Tl)[0]-1;i>=0;i--)
  {
    if (sPairs[i].syzind>=0)
    {
      tres[1]->m[sPairs[i].syzind] = pCopy(syzstr->res[1]->m[sPairs[i].syzind]);
    }
  }
/*--- changes to the original ring------------------*/
  kBucketDestroy(&syzstr->bucket);
  if (syzstr->syRing != NULL)
  {
    rChangeCurrRing(origR,TRUE);
    // Thomas: now make sure that all data which you need is pFetchCopied
    // maybe incoporate it into syReorder ??
  }
  else
  {
    pSetm=oldSetm;
    pComp0=oldComp0;
  }
  tres = syReorder(tres,syzstr->length,syzstr,FALSE,syzstr->res);
  syKillEmptyEntres(tres,syzstr->length);
  idSkipZeroes(tres[0]);
  return tres;
}

/*3
* minimizes any kind of resolution
*/
syStrategy syMinimize(syStrategy syzstr)
{
  if (syzstr->minres==NULL)
  {
    if (syzstr->resPairs!=NULL)
    {
      if (syzstr->hilb_coeffs==NULL)
      {
        syzstr->minres = syReadOutMinimalRes(syzstr);
      }
      else
      {
        syzstr->minres = syReorder(syzstr->orderedRes,syzstr->length,syzstr);
      }
    }
    else if (syzstr->fullres!=NULL)
    {
      syMinimizeResolvente(syzstr->fullres,syzstr->length,1);
      syzstr->minres = syzstr->fullres;
      syzstr->fullres = NULL;
    }
  }
  (syzstr->references)++;
  return syzstr;
}

/*2
* implementation of LaScala's algorithm
* assumes that the given module is homogeneous
* works with slanted degree, uses syChosePairs
*/
syStrategy syLaScala3(ideal arg,int * length)
{
  BOOLEAN noPair=FALSE;
  int i,j,* ord,*b0,*b1,actdeg=32000,index=0,reg=-1;
  int startdeg,howmuch;
  poly p;
  ideal temp;
  SSet nextPairs;
  syStrategy syzstr=(syStrategy)Alloc0SizeOf(ssyStrategy);
  ring tmpR = NULL;
  ring origR = currRing;

  if ((idIs0(arg)) ||
      ((idRankFreeModule(arg)>0) && (!idHomModule(arg,NULL,&(syzstr->cw)))))
  {
    syzstr->minres = (resolvente)Alloc0SizeOf(ideal);
    syzstr->length = 1;
    syzstr->minres[0] = idInit(1,arg->rank);
    return syzstr;
  }
  pSetmProc oldSetm=pSetm;
  pCompProc oldComp0=pComp0;

  //crit = 0;
  //euler = -1;
  redpol = pInit();
  syzstr->length = *length = pVariables+2;

  // construct new ring
  tmpR = (ring) Alloc0SizeOf(sip_sring);
  tmpR->wvhdl = (int **)Alloc0(3 * sizeof(int *));
  ord = (int*)Alloc0(3*sizeof(int));
  b0 = (int*)Alloc0(3*sizeof(int));
  b1 = (int*)Alloc0(3*sizeof(int));
  ord[0] = ringorder_dp;
  ord[1] = ringorder_S;
  b0[0] = 1;
  b1[0] = currRing->N;
  tmpR->OrdSgn = 1;
  tmpR->N = currRing->N;
  tmpR->ch = currRing->ch;
  tmpR->order = ord;
  tmpR->block0 = b0;
  tmpR->block1 = b1;
  tmpR->P = currRing->P;

  if (currRing->parameter!=NULL)
  {
    tmpR->minpoly=nCopy(currRing->minpoly);
    tmpR->parameter=(char **)Alloc(rPar(currRing)*sizeof(char *));
    for(i=0;i<tmpR->P;i++)
    {
      tmpR->parameter[i]=mstrdup(currRing->parameter[i]);
    }
  }
  tmpR->names   = (char **)Alloc(tmpR->N * sizeof(char *));
  for (i=0; i<tmpR->N; i++)
  {
    tmpR->names[i] = mstrdup(currRing->names[i]);
  }
  currcomponents = (int*)Alloc0((arg->rank+1)*sizeof(int));
  currShiftedComponents = (long*)Alloc0((arg->rank+1)*sizeof(long));
  for (i=0;i<=arg->rank;i++)
  {
    currShiftedComponents[i] = (i)*SYZ_SHIFT_BASE;
    currcomponents[i] = i;
  }
  rComplete(tmpR, 1);
  rChangeCurrRing(tmpR, TRUE);
  rChangeSComps(currcomponents, currShiftedComponents, arg->rank);
  syzstr->syRing = tmpR;
  pComp0 = syzcomp2dpc;
/*--- initializes the data structures---------------*/
  syzstr->Tl = new intvec(*length);
  temp = idInit(IDELEMS(arg),arg->rank);
  for (i=0;i<IDELEMS(arg);i++)
  {
    temp->m[i] = pFetchCopy(origR, arg->m[i]);
    if (temp->m[i]!=NULL)
    {
      j = pTotaldegree(temp->m[i]);
      if (j<actdeg) actdeg = j;
    }
  }
  idTest(temp);
  idSkipZeroes(temp);
  idTest(temp);
  syzstr->resPairs = syInitRes(temp,length,syzstr->Tl,syzstr->cw);
  Free((ADDRESS)currcomponents,(arg->rank+1)*sizeof(int));
  Free((ADDRESS)currShiftedComponents,(arg->rank+1)*sizeof(long));
  syzstr->res = (resolvente)Alloc0((*length+1)*sizeof(ideal));
  syzstr->orderedRes = (resolvente)Alloc0((*length+1)*sizeof(ideal));
  syzstr->elemLength = (int**)Alloc0((*length+1)*sizeof(int*));
  syzstr->truecomponents = (int**)Alloc0((*length+1)*sizeof(int*));
  syzstr->ShiftedComponents = (long**)Alloc0((*length+1)*sizeof(long*));
  syzstr->backcomponents = (int**)Alloc0((*length+1)*sizeof(int*));
  syzstr->Howmuch = (int**)Alloc0((*length+1)*sizeof(int*));
  syzstr->Firstelem = (int**)Alloc0((*length+1)*sizeof(int*));
  syzstr->sev = (unsigned long **) Alloc0((*length+1)*sizeof(unsigned long *));
  syzstr->bucket = kBucketCreate();
  int len0=idRankFreeModule(arg)+1;
  startdeg = actdeg;
  nextPairs = syChosePairs(syzstr,&index,&howmuch,&actdeg);
  //if (TEST_OPT_PROT) Print("(%d,%d)",howmuch,index);
/*--- computes the resolution ----------------------*/
  while (nextPairs!=NULL)
  {
    if (TEST_OPT_PROT) Print("%d",actdeg);
    if (TEST_OPT_PROT) Print("(m%d)",index);
    if (index==0)
      i = syInitSyzMod(syzstr,index,len0);
    else
      i = syInitSyzMod(syzstr,index);
    currcomponents = syzstr->truecomponents[max(index-1,0)];
    currShiftedComponents = syzstr->ShiftedComponents[max(index-1,0)];
    rChangeSComps(currcomponents, currShiftedComponents,
                  IDELEMS(syzstr->res[max(index-1,0)]));
    j = syInitSyzMod(syzstr,index+1);
    if (index>0)
    {
      syRedNextPairs(nextPairs,syzstr,howmuch,index);
      syCompactifyPairSet(syzstr->resPairs[index],(*syzstr->Tl)[index],0);
    }
    else
      syRedGenerOfCurrDeg(syzstr,actdeg,index+1);
/*--- creates new pairs -----------------------------*/
    syCreateNewPairs(syzstr,index,i);
    if (index<(*length)-1)
    {
      syCreateNewPairs(syzstr,index+1,j);
    }
    index++;
    nextPairs = syChosePairs(syzstr,&index,&howmuch,&actdeg);
    //if (TEST_OPT_PROT) Print("(%d,%d)",howmuch,index);
  }
  if (temp!=NULL) idDelete(&temp);
  kBucketDestroy(&(syzstr->bucket));
  if (ord!=NULL)
  {
    rChangeCurrRing(origR,TRUE);
  }
  else
  {
    pSetm=oldSetm;
    pComp0=oldComp0;
  }
  pDelete1(&redpol);
  if (TEST_OPT_PROT) PrintLn();
  return syzstr;
}

