//Low-poly spaceship!

background { rgb<1,1,1> }

camera {
        location <-1,3,3>*2.3
        look_at <0,0,0>
        angle 110
}


light_source { <7,7,7> color rgb<1,1,1> }

#declare A = <-6,0,-3>; // 0
#declare B = <-5,0,0>;  // 1     
#declare C = <-1,0,1>;  // 2
#declare D = <-1,0,-3>; // 3
#declare E = <6,0,-3>;  // 4
#declare F = <5,0,0>;   // 5
#declare G = <1,0,1>;   // 6
#declare H = <1,0,-3>;  // 7
#declare I = <0,0,-4>;  // 8
#declare J = <0,0,3>;   // 9
#declare K = <0,1,-3>;  // 10
#declare L = <0,1,2>;   // 11
#declare M = <0,2,-4>;  // 12
#declare N = <-2,-.5,0>;// 13
#declare O = <-3,-.5,0>;// 14
#declare P = <-2.5,0,0>;// 15
#declare Q = <-2.5,0,2>;// 16
#declare R = <3,-.5,0>; // 17
#declare S = <2,-.5,0>; // 18
#declare T = <2.5,0,0>; // 19
#declare U = <2.5,0,2>; // 20


#declare B0 = <-5, 1.2, 1>;
#declare B1 = <-5, 1.2, -1>;
#declare B2 = <5, 1.2, 1>;
#declare B3 = <5, 1.2, -1>;
#declare B4 = <4, -1, 0>;
#declare B5 = <4, -1, -2>;
#declare B6 = <-4, -1, 0>;
#declare B7 = <-4, -1, -2>;
#declare B8 = <-1, 1, 2>;
#declare B9 = <1, 1, 2>;
#declare B10 = <0, -1, -6>;
#declare B11 = <0, -1, 2>;
#declare B12 = <0, -.5, -4>;
#declare B13 = <0, 1, -6>;

// DELTA
#declare C0 = <0,0,2>;
#declare C1 = <-1,0,0>;
#declare C2 = <0,1,0>;
#declare C3 = <1,0,0>;
#declare C4 = <0,-1,0>;
#declare C5 = <0,0,-4>;
#declare C6 = <0,3,-5>;
#declare C7 = <0,1,-6>;                 
#declare C8 = <0,2,-5>;
#declare C9 = <0,-2,-5>;
#declare C10 = <0,-1,-6>;
#declare C11 = <0,-3,-5>;
#declare C12 = <-3,0,-5>;
#declare C13 = <-1,0,-6>;
#declare C14 = <-2,0,-5>;
#declare C15 = <2,0,-5>;
#declare C16 = <1,0,-6>;
#declare C17 = <3,0,-5>;

// EPSILON
#declare D0 = <-3,3,1>;
#declare D1 = <-3,3,-3>;
#declare D2 = <-1,1,-1>;
#declare D3 = <-1,1,1>;
#declare D4 = <-3,-3,1>;
#declare D5 = <-3,-3,-3>;
#declare D6 = <-1,-1,-1>;
#declare D7 = <-1,-1,1>;
#declare D8 = <3,3,1>;
#declare D9 = <3,3,-3>;
#declare D10 = <1,1,-1>;
#declare D11 = <1,1,1>;
#declare D12 = <3,-3,1>;
#declare D13 = <3,-3,-3>;
#declare D14 = <1,-1,-1>;
#declare D15 = <1,-1,1>;
#declare D16 = <0,0,-5>;

#declare AA = <-3,0,-3>; 
#declare AB = <-3,0,-2>;
#declare AC = <0,0,3>;
#declare AD = <3,0,-2>;
#declare AE = <3,0,-3>;
#declare AF = <-1, 1.5,-3>;
#declare AG = <0,2,-3>;
#declare AH = <1,1.5,-3>;
#declare AI = <0,0,-3>;


// Zeta
#declare Z0 = <-6, 1, 0>;
#declare Z1 = <-6, 1, -2>;
#declare Z2 = <-3, 0, -2>;
#declare Z3 = <-3, 0, 0>;
#declare Z4 = <3, 0, 0>;
#declare Z5 = <3, 0, -2>;
#declare Z6 = <6, 1, -2>;
#declare Z7 = <6, 1, 0>;
#declare Z8 = <-1, 0, 1>;
#declare Z9 = <0, -1.5, 1>;
#declare Z10 = <1, 0, 1>;
#declare Z11 = <0,0, -7>;
#declare Z12 = <2.5, -1, -3>;
#declare Z13 = <3, 0, -3>;
#declare Z14 = <3.5, -1, -3>;
#declare Z15 = <3, 0, 1>;
#declare Z16 = <-3, 0, 1>;
#declare Z17 = <-2.5, -1, -3>;
#declare Z18 = <-3, 0, -3>;
#declare Z19 = <-3.5, -1, -3>;
#declare Z20 = <0, 1, -7>;
#declare Z21 = <0, 0, -5>;

// Theta

#declare T0 = <-6,0,-1>;
#declare T1 = <-6,0,-1>;
#declare T2 = <-6,0,-1>;
#declare T3 = <-6,0,-1>;
#declare T4 = <-6,0,-1>;
#declare T5 = <-6,0,-1>;
#declare T6 = <-6,0,-1>;
#declare T7 = <-6,0,-1>;
#declare T8 = <-6,0,-1>;
#declare T9 = <-6,0,-1>;
#declare T10 = <-6,0,-1>;
#declare T11 = <-6,0,-1>;
#declare T12 = <-6,0,-1>;
#declare T13 = <-6,0,-1>;
#declare T14 = <-6,0,-1>;
#declare T15 = <-6,0,-1>;
#declare T16 = <-6,0,-1>;
#declare T17 = <-6,0,-1>;
#declare T18 = <-6,0,-1>;
#declare T19 = <-6,0,-1>;
#declare T20 = <-6,0,-1>;
#declare T21 = <-6,0,-1>;
#declare T22 = <-6,0,-1>;
#declare T23 = <-6,0,-1>;


#declare THICK = .075;

//  a  b  c  d  e  f  g  h  i  j  k  l  m  n  o  p  q  r  s  t  u
//  0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16 17 18 19 20



#declare ship_linesE = union {
        sphere_sweep { linear_spline 2, D0 THICK, D1 THICK }
        sphere_sweep { linear_spline 2, D0 THICK, D3 THICK }
        sphere_sweep { linear_spline 2, D1 THICK, D2 THICK }
        sphere_sweep { linear_spline 2, D2 THICK, D3 THICK }
        sphere_sweep { linear_spline 2, D4 THICK, D5 THICK }
        sphere_sweep { linear_spline 2, D4 THICK, D7 THICK }
        sphere_sweep { linear_spline 2, D5 THICK, D6 THICK }
        sphere_sweep { linear_spline 2, D6 THICK, D7 THICK }
        sphere_sweep { linear_spline 2, D8 THICK, D9 THICK }
        sphere_sweep { linear_spline 2, D8 THICK, D11 THICK }
        sphere_sweep { linear_spline 2, D9 THICK, D10 THICK }
        sphere_sweep { linear_spline 2, D10 THICK, D11 THICK }
        sphere_sweep { linear_spline 2, D12 THICK, D13 THICK }
        sphere_sweep { linear_spline 2, D12 THICK, D15 THICK }
        sphere_sweep { linear_spline 2, D13 THICK, D14 THICK }
        sphere_sweep { linear_spline 2, D14 THICK, D15 THICK }
        sphere_sweep { linear_spline 2, D2 THICK, D10 THICK }
        sphere_sweep { linear_spline 2, D3 THICK, D11 THICK }
        sphere_sweep { linear_spline 2, D6 THICK, D14 THICK }
        sphere_sweep { linear_spline 2, D7 THICK, D15 THICK }
        sphere_sweep { linear_spline 2, D2 THICK, D6 THICK }
        sphere_sweep { linear_spline 2, D3 THICK, D7 THICK }
        sphere_sweep { linear_spline 2, D10 THICK, D14 THICK }
        sphere_sweep { linear_spline 2, D11 THICK, D15 THICK }
        
        sphere_sweep { linear_spline 2, D16 THICK, D2 THICK }
        sphere_sweep { linear_spline 2, D16 THICK, D6 THICK }
        sphere_sweep { linear_spline 2, D16 THICK, D10 THICK }
        sphere_sweep { linear_spline 2, D16 THICK, D14 THICK }
        

        
        texture { pigment { color rgb<1,0,0> }  finish { ambient 1 } }
}

#declare ship_linesD = union {
    sphere_sweep { linear_spline 2, C0 THICK, C1 THICK }
    sphere_sweep { linear_spline 2, C0 THICK, C2 THICK }
    sphere_sweep { linear_spline 2, C0 THICK, C3 THICK }
    sphere_sweep { linear_spline 2, C0 THICK, C4 THICK }
    sphere_sweep { linear_spline 2, C1 THICK, C2 THICK }
    sphere_sweep { linear_spline 2, C2 THICK, C3 THICK }
    sphere_sweep { linear_spline 2, C3 THICK, C4 THICK }
    sphere_sweep { linear_spline 2, C1 THICK, C4 THICK }
    sphere_sweep { linear_spline 2, C5 THICK, C1 THICK }
    sphere_sweep { linear_spline 2, C5 THICK, C2 THICK }
    sphere_sweep { linear_spline 2, C5 THICK, C3 THICK }
    sphere_sweep { linear_spline 2, C5 THICK, C4 THICK }
    sphere_sweep { linear_spline 2, C5 THICK, C12 THICK }
    sphere_sweep { linear_spline 2, C5 THICK, C14 THICK }
    sphere_sweep { linear_spline 2, C13 THICK, C12 THICK }
    sphere_sweep { linear_spline 2, C13 THICK, C14 THICK }
    sphere_sweep { linear_spline 2, C5 THICK, C15 THICK }
    sphere_sweep { linear_spline 2, C5 THICK, C17 THICK }
    sphere_sweep { linear_spline 2, C16 THICK, C15 THICK }
    sphere_sweep { linear_spline 2, C16 THICK, C17 THICK }
    sphere_sweep { linear_spline 2, C5 THICK, C6 THICK }
    sphere_sweep { linear_spline 2, C5 THICK, C8 THICK }
    sphere_sweep { linear_spline 2, C7 THICK, C6 THICK }
    sphere_sweep { linear_spline 2, C7 THICK, C8 THICK }
    sphere_sweep { linear_spline 2, C5 THICK, C11 THICK }
    sphere_sweep { linear_spline 2, C5 THICK, C9 THICK }
    sphere_sweep { linear_spline 2, C10 THICK, C11 THICK }
    sphere_sweep { linear_spline 2, C10 THICK, C9 THICK }
        
    texture { pigment { color rgb<0,1,1> }  finish { ambient 1 } }
}

#declare ship_linesC = union {
        sphere_sweep { linear_spline 2, B0 THICK, B1 THICK }
        sphere_sweep { linear_spline 2, B1 THICK, B3 THICK }
        sphere_sweep { linear_spline 2, B2 THICK, B3 THICK }
        sphere_sweep { linear_spline 2, B0 THICK, B2 THICK }
        sphere_sweep { linear_spline 2, B4 THICK, B5 THICK }
        sphere_sweep { linear_spline 2, B4 THICK, B6 THICK }
        sphere_sweep { linear_spline 2, B7 THICK, B5 THICK }
        sphere_sweep { linear_spline 2, B6 THICK, B7 THICK }
        sphere_sweep { linear_spline 2, B8 THICK, B10 THICK }
        sphere_sweep { linear_spline 2, B9 THICK, B10 THICK }
        sphere_sweep { linear_spline 2, B11 THICK, B10 THICK }
        sphere_sweep { linear_spline 2, B8 THICK, B9 THICK }
        sphere_sweep { linear_spline 2, B9 THICK, B11 THICK }
        sphere_sweep { linear_spline 2, B8 THICK, B11 THICK }
        sphere_sweep { linear_spline 2, B10 THICK, B13 THICK }
        sphere_sweep { linear_spline 2, B12 THICK, B13 THICK }
        
        
        
        texture { pigment { color rgb<0,0,1> }  finish { ambient 1 } }
}

#declare ship_linesB = union {
        sphere_sweep { linear_spline 2, AA THICK, AB THICK }
        sphere_sweep { linear_spline 2, AB THICK, AC THICK }
        sphere_sweep { linear_spline 2, AB THICK, AC THICK }        
        sphere_sweep { linear_spline 2, AC THICK, AD THICK }
        sphere_sweep { linear_spline 2, AC THICK, AG THICK }
        sphere_sweep { linear_spline 2, AC THICK, AI THICK }
        sphere_sweep { linear_spline 2, AC THICK, AF THICK }
        sphere_sweep { linear_spline 2, AC THICK, AH THICK }
        sphere_sweep { linear_spline 2, AD THICK, AE THICK }
        sphere_sweep { linear_spline 2, AA THICK, AE THICK }        
        sphere_sweep { linear_spline 2, AH THICK, AI THICK }
        sphere_sweep { linear_spline 2, AF THICK, AI THICK }
        sphere_sweep { linear_spline 2, AG THICK, AI THICK }
        
        
        texture { pigment { color rgb<1,1,0> }  finish { ambient 1 } }
}

#declare ship_linesA = union {
        sphere_sweep { linear_spline 2, A THICK, B THICK }
        sphere_sweep { linear_spline 2, A THICK, D THICK }
        sphere_sweep { linear_spline 2, B THICK, C THICK }        
        sphere_sweep { linear_spline 2, C THICK, D THICK }
        sphere_sweep { linear_spline 2, C THICK, J THICK }
        sphere_sweep { linear_spline 2, C THICK, L THICK }        
        sphere_sweep { linear_spline 2, D THICK, I THICK }
        sphere_sweep { linear_spline 2, D THICK, K THICK }        
        sphere_sweep { linear_spline 2, E THICK, H THICK }
        sphere_sweep { linear_spline 2, E THICK, F THICK }        
        sphere_sweep { linear_spline 2, F THICK, G THICK }        
        sphere_sweep { linear_spline 2, G THICK, H THICK }
        sphere_sweep { linear_spline 2, G THICK, J THICK }
        sphere_sweep { linear_spline 2, G THICK, L THICK }        
        sphere_sweep { linear_spline 2, H THICK, I THICK }
        sphere_sweep { linear_spline 2, H THICK, K THICK }        
        sphere_sweep { linear_spline 2, I THICK, K THICK }
        sphere_sweep { linear_spline 2, I THICK, M THICK }        
        sphere_sweep { linear_spline 2, J THICK, L THICK }        
        sphere_sweep { linear_spline 2, K THICK, L THICK }
        sphere_sweep { linear_spline 2, K THICK, M THICK }                
        sphere_sweep { linear_spline 2, N THICK, O THICK }
        sphere_sweep { linear_spline 2, N THICK, P THICK }
        sphere_sweep { linear_spline 2, N THICK, Q THICK }        
        sphere_sweep { linear_spline 2, O THICK, P THICK }       
        sphere_sweep { linear_spline 2, O THICK, Q THICK }        
        sphere_sweep { linear_spline 2, P THICK, Q THICK }        
        sphere_sweep { linear_spline 2, R THICK, S THICK }
        sphere_sweep { linear_spline 2, R THICK, T THICK }
        sphere_sweep { linear_spline 2, R THICK, U THICK }        
        sphere_sweep { linear_spline 2, S THICK, T THICK }
        sphere_sweep { linear_spline 2, S THICK, U THICK }        
        sphere_sweep { linear_spline 2, T THICK, U THICK }
        
        
        texture { pigment { color rgb<0,1,0> }  finish { ambient 1 } }
}

#declare ship_linesE = union {
        sphere_sweep { linear_spline 2, Z0 THICK, Z1 THICK }
        sphere_sweep { linear_spline 2, Z1 THICK, Z2 THICK }
        sphere_sweep { linear_spline 2, Z2 THICK, Z3 THICK }
        sphere_sweep { linear_spline 2, Z0 THICK, Z3 THICK }
        sphere_sweep { linear_spline 2, Z2 THICK, Z5 THICK }
        sphere_sweep { linear_spline 2, Z3 THICK, Z4 THICK }
        sphere_sweep { linear_spline 2, Z4 THICK, Z5 THICK }
        sphere_sweep { linear_spline 2, Z5 THICK, Z6 THICK }
        sphere_sweep { linear_spline 2, Z6 THICK, Z7 THICK }
        sphere_sweep { linear_spline 2, Z4 THICK, Z7 THICK }
        sphere_sweep { linear_spline 2, Z8 THICK, Z9 THICK }
        sphere_sweep { linear_spline 2, Z9 THICK, Z10 THICK }
        sphere_sweep { linear_spline 2, Z8 THICK, Z10 THICK }
        sphere_sweep { linear_spline 2, Z9 THICK, Z11 THICK }
        sphere_sweep { linear_spline 2, Z8 THICK, Z11 THICK }        
        sphere_sweep { linear_spline 2, Z10 THICK, Z11 THICK }
        sphere_sweep { linear_spline 2, Z12 THICK, Z15 THICK }
        sphere_sweep { linear_spline 2, Z13 THICK, Z15 THICK }
        sphere_sweep { linear_spline 2, Z14 THICK, Z15 THICK }
        sphere_sweep { linear_spline 2, Z12 THICK, Z13 THICK }
        sphere_sweep { linear_spline 2, Z13 THICK, Z14 THICK }
        sphere_sweep { linear_spline 2, Z12 THICK, Z14 THICK }
        sphere_sweep { linear_spline 2, Z17 THICK, Z16 THICK }
        sphere_sweep { linear_spline 2, Z18 THICK, Z16 THICK }
        sphere_sweep { linear_spline 2, Z19 THICK, Z16 THICK }
        sphere_sweep { linear_spline 2, Z17 THICK, Z18 THICK }
        sphere_sweep { linear_spline 2, Z18 THICK, Z19 THICK }
        sphere_sweep { linear_spline 2, Z17 THICK, Z19 THICK }
        sphere_sweep { linear_spline 2, Z11 THICK, Z20 THICK }
        sphere_sweep { linear_spline 2, Z20 THICK, Z21 THICK }
        
        
        
        texture { pigment { color rgb<1,0,1> }  finish { ambient 1 } }        
}

//object { ship_linesB   }
// object { ship_linesD }
// object { ship_linesA  }
// object { ship_linesA }
object { ship_linesC }
object { ship_linesE pigment{ color rgb<0,0,0> } rotate<-30,25,-25> }


/*  */
        