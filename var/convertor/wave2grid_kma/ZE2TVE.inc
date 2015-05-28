      SUBROUTINE ZE2TVE( Z, TV, PS,       A, B, IMAX, JMAX, LMAX,
     1                   VLG, WRK1, WRK2, WRK3, WRK4, WRK5, WRK6 )
C
C     INPUT   Z   (I,J,L) : GEOPOTENTIAL HEIGHT(M)
C             PS  (I,J)   : SURFACE PRESSURE(HPA)
C     OUTPUT  TV  (I,J,L) : VIRTUAL TEMPERATURE(K)
C     CONTROL DLG (L)     : PRESSURE OF  INPUT VARIABLE(Z ) LEVELS
C             VLG (L)     : PRESSURE OF OUTPUT VARIABLE(TV) LEVELS
C             A(L), B(L)  : A+B*PS DEFINITION OF ETA-HALF LEVEL

      DIMENSION Z(IMAX*JMAX,LMAX), TV(IMAX*JMAX,LMAX), PS(IMAX*JMAX),
     \     A(LMAX), B(LMAX),TV2(IMAX*JMAX,LMAX),
     \     VLG(IMAX*JMAX,LMAX)
      DIMENSION WRK1(IMAX*JMAX,LMAX), WRK2(IMAX*JMAX,LMAX),
     1          WRK3(IMAX*JMAX,LMAX), WRK4(IMAX*JMAX,LMAX),
     2          WRK5(IMAX*JMAX,LMAX), WRK6(IMAX*JMAX,LMAX)
C
        DO 90 L = 1, LMAX
        DO 90 I = 1, IMAX*JMAX
          WRK1(I,L) = A(L)+B(L)*PS(I)
          WRK2(I,L) = LOG( WRK1(I,L) )
   90   CONTINUE
        DO 100 L = 1, LMAX-1
        DO 100 I = 1, IMAX*JMAX
          VLG(I,L) = (WRK1(I,L)*WRK2(I,L)-WRK1(I,L+1)*WRK2(I,L+1))
     1             / (WRK1(I,L)-WRK1(I,L+1)) - 1.0
  100   CONTINUE
        DO 110 I = 1, IMAX*JMAX
          VLG(I,LMAX) = LOG(0.5*(A(LMAX)+B(LMAX)*PS(I)))
  110   CONTINUE
CORG    CALL SPLDIF3( TV2, VLG, LMAX, Z, VLG, LMAX, IMAX*JMAX,
CORG W                WRK1, WRK2, WRK3, WRK4, WRK5, WRK6 )
        CALL SPLDIF3_H(TV, VLG, LMAX, Z, VLG, LMAX, IMAX*JMAX,
     W                WRK1, WRK2, WRK3, WRK4, WRK5, WRK6 )
C
C	  CALL MONTWO(TV,TV2,'NEW  SPLINE','ORG  SPLINE',IMAX*JMAX,LMAX)

      RETURN
      END SUBROUTINE ZE2TVE