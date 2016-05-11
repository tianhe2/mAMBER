/*
 * Copyright (c) 2003, 2007-11 Matteo Frigo
 * Copyright (c) 2003, 2007-11 Massachusetts Institute of Technology
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */

/* This file was automatically generated --- DO NOT EDIT */
/* Generated on Wed Jul 27 06:17:53 EDT 2011 */

#include "codelet-rdft.h"

#ifdef HAVE_FMA

/* Generated by: ../../../genfft/gen_hc2cdft.native -fma -reorder-insns -schedule-for-pipeline -compact -variables 4 -pipeline-latency 4 -n 8 -dit -name hc2cfdft_8 -include hc2cf.h */

/*
 * This function contains 82 FP additions, 52 FP multiplications,
 * (or, 60 additions, 30 multiplications, 22 fused multiply/add),
 * 55 stack variables, 2 constants, and 32 memory accesses
 */
#include "hc2cf.h"

static void hc2cfdft_8(R *Rp, R *Ip, R *Rm, R *Im, const R *W, stride rs, INT mb, INT me, INT ms)
{
     DK(KP707106781, +0.707106781186547524400844362104849039284835938);
     DK(KP500000000, +0.500000000000000000000000000000000000000000000);
     {
	  INT m;
	  for (m = mb, W = W + ((mb - 1) * 14); m < me; m = m + 1, Rp = Rp + ms, Ip = Ip + ms, Rm = Rm - ms, Im = Im - ms, W = W + 14, MAKE_VOLATILE_STRIDE(rs)) {
	       E T1A, T1w, T1z, T1x, T1H, T1v, T1L, T1F;
	       {
		    E Ty, T14, TO, T1o, Tv, TG, T16, T1m, Ta, T19, T1h, TV, T10, TX, TZ;
		    E Tk, T1i, TY, T1b, TF, TB, T1l;
		    {
			 E TH, TN, TK, TM;
			 {
			      E Tw, Tx, TI, TJ;
			      Tw = Ip[0];
			      Tx = Im[0];
			      TI = Rm[0];
			      TJ = Rp[0];
			      TH = W[0];
			      Ty = Tw - Tx;
			      TN = Tw + Tx;
			      T14 = TJ + TI;
			      TK = TI - TJ;
			      TM = W[1];
			 }
			 {
			      E Ts, Tp, Tt, Tm, Tr;
			      {
				   E Tn, To, TL, T1n;
				   Tn = Ip[WS(rs, 2)];
				   To = Im[WS(rs, 2)];
				   TL = TH * TK;
				   T1n = TM * TK;
				   Ts = Rp[WS(rs, 2)];
				   TF = Tn + To;
				   Tp = Tn - To;
				   TO = FNMS(TM, TN, TL);
				   T1o = FMA(TH, TN, T1n);
				   Tt = Rm[WS(rs, 2)];
			      }
			      Tm = W[6];
			      Tr = W[7];
			      {
				   E TE, TD, T15, TC, Tu, Tq;
				   TB = W[8];
				   TC = Tt - Ts;
				   Tu = Ts + Tt;
				   Tq = Tm * Tp;
				   TE = W[9];
				   TD = TB * TC;
				   T15 = Tm * Tu;
				   Tv = FNMS(Tr, Tu, Tq);
				   T1l = TE * TC;
				   TG = FNMS(TE, TF, TD);
				   T16 = FMA(Tr, Tp, T15);
			      }
			 }
		    }
		    {
			 E TU, TR, TT, T1g, TS;
			 {
			      E T2, T3, T7, T8;
			      T2 = Ip[WS(rs, 1)];
			      T1m = FMA(TB, TF, T1l);
			      T3 = Im[WS(rs, 1)];
			      T7 = Rp[WS(rs, 1)];
			      T8 = Rm[WS(rs, 1)];
			      {
				   E T1, T4, T9, T6, T5, TQ, T18;
				   T1 = W[2];
				   TU = T2 + T3;
				   T4 = T2 - T3;
				   TR = T7 - T8;
				   T9 = T7 + T8;
				   T6 = W[3];
				   T5 = T1 * T4;
				   TQ = W[4];
				   T18 = T1 * T9;
				   TT = W[5];
				   Ta = FNMS(T6, T9, T5);
				   T1g = TQ * TU;
				   TS = TQ * TR;
				   T19 = FMA(T6, T4, T18);
			      }
			 }
			 {
			      E Tc, Td, Th, Ti;
			      Tc = Ip[WS(rs, 3)];
			      T1h = FNMS(TT, TR, T1g);
			      TV = FMA(TT, TU, TS);
			      Td = Im[WS(rs, 3)];
			      Th = Rp[WS(rs, 3)];
			      Ti = Rm[WS(rs, 3)];
			      {
				   E Tb, Te, Tj, Tg, Tf, TW, T1a;
				   Tb = W[10];
				   T10 = Tc + Td;
				   Te = Tc - Td;
				   TX = Th - Ti;
				   Tj = Th + Ti;
				   Tg = W[11];
				   Tf = Tb * Te;
				   TW = W[12];
				   T1a = Tb * Tj;
				   TZ = W[13];
				   Tk = FNMS(Tg, Tj, Tf);
				   T1i = TW * T10;
				   TY = TW * TX;
				   T1b = FMA(Tg, Te, T1a);
			      }
			 }
		    }
		    {
			 E T1E, T1t, TA, T1s, T1D, T1u, T1e, T13, T1r, T1d;
			 {
			      E TP, T1f, T1q, T12, T17, T1c;
			      {
				   E Tl, T11, Tz, T1p, T1k, T1j;
				   T1E = Ta - Tk;
				   Tl = Ta + Tk;
				   T1j = FNMS(TZ, TX, T1i);
				   T11 = FMA(TZ, T10, TY);
				   Tz = Tv + Ty;
				   T1t = Ty - Tv;
				   T1A = T1o - T1m;
				   T1p = T1m + T1o;
				   T1k = T1h + T1j;
				   T1w = T1j - T1h;
				   T1z = TO - TG;
				   TP = TG + TO;
				   T1f = Tz - Tl;
				   TA = Tl + Tz;
				   T1s = T1k + T1p;
				   T1q = T1k - T1p;
				   T12 = TV + T11;
				   T1x = TV - T11;
				   T1D = T14 - T16;
				   T17 = T14 + T16;
				   T1c = T19 + T1b;
				   T1u = T19 - T1b;
			      }
			      Im[WS(rs, 1)] = KP500000000 * (T1q - T1f);
			      T1e = T12 + TP;
			      T13 = TP - T12;
			      T1r = T17 + T1c;
			      T1d = T17 - T1c;
			      Ip[WS(rs, 2)] = KP500000000 * (T1f + T1q);
			 }
			 Im[WS(rs, 3)] = KP500000000 * (T13 - TA);
			 Ip[0] = KP500000000 * (TA + T13);
			 Rm[WS(rs, 3)] = KP500000000 * (T1r - T1s);
			 Rp[0] = KP500000000 * (T1r + T1s);
			 Rp[WS(rs, 2)] = KP500000000 * (T1d + T1e);
			 Rm[WS(rs, 1)] = KP500000000 * (T1d - T1e);
			 T1H = T1u + T1t;
			 T1v = T1t - T1u;
			 T1L = T1D + T1E;
			 T1F = T1D - T1E;
		    }
	       }
	       {
		    E T1y, T1I, T1B, T1J;
		    T1y = T1w + T1x;
		    T1I = T1w - T1x;
		    T1B = T1z - T1A;
		    T1J = T1z + T1A;
		    {
			 E T1M, T1K, T1C, T1G;
			 T1M = T1I + T1J;
			 T1K = T1I - T1J;
			 T1C = T1y + T1B;
			 T1G = T1B - T1y;
			 Im[0] = -(KP500000000 * (FNMS(KP707106781, T1K, T1H)));
			 Ip[WS(rs, 3)] = KP500000000 * (FMA(KP707106781, T1K, T1H));
			 Rp[WS(rs, 1)] = KP500000000 * (FMA(KP707106781, T1M, T1L));
			 Rm[WS(rs, 2)] = KP500000000 * (FNMS(KP707106781, T1M, T1L));
			 Rp[WS(rs, 3)] = KP500000000 * (FMA(KP707106781, T1G, T1F));
			 Rm[0] = KP500000000 * (FNMS(KP707106781, T1G, T1F));
			 Im[WS(rs, 2)] = -(KP500000000 * (FNMS(KP707106781, T1C, T1v)));
			 Ip[WS(rs, 1)] = KP500000000 * (FMA(KP707106781, T1C, T1v));
		    }
	       }
	  }
     }
}

static const tw_instr twinstr[] = {
     {TW_FULL, 1, 8},
     {TW_NEXT, 1, 0}
};

static const hc2c_desc desc = { 8, "hc2cfdft_8", twinstr, &GENUS, {60, 30, 22, 0} };

void X(codelet_hc2cfdft_8) (planner *p) {
     X(khc2c_register) (p, hc2cfdft_8, &desc, HC2C_VIA_DFT);
}
#else				/* HAVE_FMA */

/* Generated by: ../../../genfft/gen_hc2cdft.native -compact -variables 4 -pipeline-latency 4 -n 8 -dit -name hc2cfdft_8 -include hc2cf.h */

/*
 * This function contains 82 FP additions, 44 FP multiplications,
 * (or, 68 additions, 30 multiplications, 14 fused multiply/add),
 * 39 stack variables, 2 constants, and 32 memory accesses
 */
#include "hc2cf.h"

static void hc2cfdft_8(R *Rp, R *Ip, R *Rm, R *Im, const R *W, stride rs, INT mb, INT me, INT ms)
{
     DK(KP353553390, +0.353553390593273762200422181052424519642417969);
     DK(KP500000000, +0.500000000000000000000000000000000000000000000);
     {
	  INT m;
	  for (m = mb, W = W + ((mb - 1) * 14); m < me; m = m + 1, Rp = Rp + ms, Ip = Ip + ms, Rm = Rm - ms, Im = Im - ms, W = W + 14, MAKE_VOLATILE_STRIDE(rs)) {
	       E Tv, TX, Ts, TY, TE, T1a, TJ, T19, T1l, T1m, T9, T10, Ti, T11, TP;
	       E T16, TU, T17, T1i, T1j;
	       {
		    E Tt, Tu, TD, Tz, TA, TB, Tn, TI, Tr, TG, Tk, To;
		    Tt = Ip[0];
		    Tu = Im[0];
		    TD = Tt + Tu;
		    Tz = Rm[0];
		    TA = Rp[0];
		    TB = Tz - TA;
		    {
			 E Tl, Tm, Tp, Tq;
			 Tl = Ip[WS(rs, 2)];
			 Tm = Im[WS(rs, 2)];
			 Tn = Tl - Tm;
			 TI = Tl + Tm;
			 Tp = Rp[WS(rs, 2)];
			 Tq = Rm[WS(rs, 2)];
			 Tr = Tp + Tq;
			 TG = Tp - Tq;
		    }
		    Tv = Tt - Tu;
		    TX = TA + Tz;
		    Tk = W[6];
		    To = W[7];
		    Ts = FNMS(To, Tr, Tk * Tn);
		    TY = FMA(Tk, Tr, To * Tn);
		    {
			 E Ty, TC, TF, TH;
			 Ty = W[0];
			 TC = W[1];
			 TE = FNMS(TC, TD, Ty * TB);
			 T1a = FMA(TC, TB, Ty * TD);
			 TF = W[8];
			 TH = W[9];
			 TJ = FMA(TF, TG, TH * TI);
			 T19 = FNMS(TH, TG, TF * TI);
		    }
		    T1l = TJ + TE;
		    T1m = T1a - T19;
	       }
	       {
		    E T4, TO, T8, TM, Td, TT, Th, TR;
		    {
			 E T2, T3, T6, T7;
			 T2 = Ip[WS(rs, 1)];
			 T3 = Im[WS(rs, 1)];
			 T4 = T2 - T3;
			 TO = T2 + T3;
			 T6 = Rp[WS(rs, 1)];
			 T7 = Rm[WS(rs, 1)];
			 T8 = T6 + T7;
			 TM = T6 - T7;
		    }
		    {
			 E Tb, Tc, Tf, Tg;
			 Tb = Ip[WS(rs, 3)];
			 Tc = Im[WS(rs, 3)];
			 Td = Tb - Tc;
			 TT = Tb + Tc;
			 Tf = Rp[WS(rs, 3)];
			 Tg = Rm[WS(rs, 3)];
			 Th = Tf + Tg;
			 TR = Tf - Tg;
		    }
		    {
			 E T1, T5, Ta, Te;
			 T1 = W[2];
			 T5 = W[3];
			 T9 = FNMS(T5, T8, T1 * T4);
			 T10 = FMA(T1, T8, T5 * T4);
			 Ta = W[10];
			 Te = W[11];
			 Ti = FNMS(Te, Th, Ta * Td);
			 T11 = FMA(Ta, Th, Te * Td);
			 {
			      E TL, TN, TQ, TS;
			      TL = W[4];
			      TN = W[5];
			      TP = FMA(TL, TM, TN * TO);
			      T16 = FNMS(TN, TM, TL * TO);
			      TQ = W[12];
			      TS = W[13];
			      TU = FMA(TQ, TR, TS * TT);
			      T17 = FNMS(TS, TR, TQ * TT);
			 }
			 T1i = T17 - T16;
			 T1j = TP - TU;
		    }
	       }
	       {
		    E T1h, T1t, T1w, T1y, T1o, T1s, T1r, T1x;
		    {
			 E T1f, T1g, T1u, T1v;
			 T1f = Tv - Ts;
			 T1g = T10 - T11;
			 T1h = KP500000000 * (T1f - T1g);
			 T1t = KP500000000 * (T1g + T1f);
			 T1u = T1i - T1j;
			 T1v = T1l + T1m;
			 T1w = KP353553390 * (T1u - T1v);
			 T1y = KP353553390 * (T1u + T1v);
		    }
		    {
			 E T1k, T1n, T1p, T1q;
			 T1k = T1i + T1j;
			 T1n = T1l - T1m;
			 T1o = KP353553390 * (T1k + T1n);
			 T1s = KP353553390 * (T1n - T1k);
			 T1p = TX - TY;
			 T1q = T9 - Ti;
			 T1r = KP500000000 * (T1p - T1q);
			 T1x = KP500000000 * (T1p + T1q);
		    }
		    Ip[WS(rs, 1)] = T1h + T1o;
		    Rp[WS(rs, 1)] = T1x + T1y;
		    Im[WS(rs, 2)] = T1o - T1h;
		    Rm[WS(rs, 2)] = T1x - T1y;
		    Rm[0] = T1r - T1s;
		    Im[0] = T1w - T1t;
		    Rp[WS(rs, 3)] = T1r + T1s;
		    Ip[WS(rs, 3)] = T1t + T1w;
	       }
	       {
		    E Tx, T15, T1c, T1e, TW, T14, T13, T1d;
		    {
			 E Tj, Tw, T18, T1b;
			 Tj = T9 + Ti;
			 Tw = Ts + Tv;
			 Tx = Tj + Tw;
			 T15 = Tw - Tj;
			 T18 = T16 + T17;
			 T1b = T19 + T1a;
			 T1c = T18 - T1b;
			 T1e = T18 + T1b;
		    }
		    {
			 E TK, TV, TZ, T12;
			 TK = TE - TJ;
			 TV = TP + TU;
			 TW = TK - TV;
			 T14 = TV + TK;
			 TZ = TX + TY;
			 T12 = T10 + T11;
			 T13 = TZ - T12;
			 T1d = TZ + T12;
		    }
		    Ip[0] = KP500000000 * (Tx + TW);
		    Rp[0] = KP500000000 * (T1d + T1e);
		    Im[WS(rs, 3)] = KP500000000 * (TW - Tx);
		    Rm[WS(rs, 3)] = KP500000000 * (T1d - T1e);
		    Rm[WS(rs, 1)] = KP500000000 * (T13 - T14);
		    Im[WS(rs, 1)] = KP500000000 * (T1c - T15);
		    Rp[WS(rs, 2)] = KP500000000 * (T13 + T14);
		    Ip[WS(rs, 2)] = KP500000000 * (T15 + T1c);
	       }
	  }
     }
}

static const tw_instr twinstr[] = {
     {TW_FULL, 1, 8},
     {TW_NEXT, 1, 0}
};

static const hc2c_desc desc = { 8, "hc2cfdft_8", twinstr, &GENUS, {68, 30, 14, 0} };

void X(codelet_hc2cfdft_8) (planner *p) {
     X(khc2c_register) (p, hc2cfdft_8, &desc, HC2C_VIA_DFT);
}
#endif				/* HAVE_FMA */
