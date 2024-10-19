* Eletric Model of a Brushless Motor
* It models its mechanical side with eletronic components
* Resource: https://www.pspice.com/resources/application-notes/brushless-dc-motor-model
*                                          .                 ::::::::::.:::::..  
*                                          .                 - :.:               
*     :....  .....                          ..                   .               
*     :  . .......                          ..               - ..:               
*     .                                     ..                       .      ...  
*     ::    ..::.... .:. ...... ... ......  .:.              :::-...::.: .:.:--: 
*     .     .....:::..:.....::: ... ......  ..                                   
*     .                ...:... .......... ..:............                        
*.  ..:           ...      ....          :..::  .        ...                     
*:.:.:-::::.    ..             ..        ..::-: .           ..                   
*     .        .                ..           ..               ..                 
*     .       .                   .          :.                .                 
*    .:      :                    ..         .:                 :                
*   ..::.....:............         :        ..                  .. :             
*  ..  ..   ..            :        :        :: ..................:.:             
*   . ...   ..           ..        :     . . ....           .:  .. :             
*    .-......-...........          .   .. .      .              .  .             
*     .      ..                   :   .:         ...            .  .             
*     .       ..                 .  .:             ..          .   ::  :-::      
*     .        ..               .  :                 ..      ..    -.  ....      
*  .::-.::.:::   ..           .   :::.:. .          :::::: -.      :             
*    .:    ..      ......::::.. ...::..::............:-.::.        .             
*     .                            ..                ..           .:.            
*     :-. .  .  .                  .:.                ::          .:..           
*     :......:.:..                 ..                ..              -.          
*                                  ..                ..                          
*                                 .:                ...                          
*                                  .                                             
* Mechanical Model -----------------------------------
.subckt motor_mech shaft_speed shaft_angle 
+ params:
+ J=  3e-5 ; Moment of inertia of rotor (Kg*m^2)
+ B=  3.6e-5  ; Damping and eddy current losses (Kg*m*sec/rad)
+ F = 7.2e-5  ; Friction losses (constant torque loss) (Kg*m)
+ D = 2.9e-5  ; Magnetic detent torque (Kg*m)
+ A = 2    ; Number of north poles on the rotor
+ P = 3    ; Number of stator phases (only change this if you changed the motor windings amount)
+ twopi =  {2 * 3.141596} 
** Mechanical Parameters
Cmotor shaft_speed 0 {J*twopi} ; Inertia 
Reddy shaft_speed 0 {1/(B*twopi)} ; Damping and Eddy Current loss
*** Magnetic Detent Torque
Gdetent shaft_speed ld2 VALUE={D *sin(2*A*P*V(shaft_angle))} ; Magnetic Detent Torque
Ldummy2 ld2 0 100mH ; force timestep control
*** Friction Loss
Gdrag shaft_speed ld1 VALUE = {F * V(drag)} ; nonlinear drag
Ldummy1 ld1 0 100mH ; force timestep control, no actual model impact
Edrag2 drag 0 TABLE {V(shaft_speed)}=(-.001, -1) (.001, 1)
Rdummy1 drag 0 1
** Gets the shaft_angle back
Gintegrate 0 shaft_angle_intg VALUE = {V(shaft_speed)} 
Cintegrate 0 shaft_angle_intg {1/twopi} IC=0.0 
Rdummy2 0 shaft_angle_intg 1e12 ; (otherwise floating) 
Ecopy shaft_angle 0 VALUE = {V(shaft_angle_intg)} 
*** Copy the voltage 
Rdummy3 shaft_angle 0 1 ; Make sure there is a load 
.ends
* Eletric Model --------------------------------------
* The motor with both ends of each coil available. 
* 
* Phase 3 coil ------------------+---+ 
* Phase 2 coil ----------+---+   |   | 
* Phase 1 coil --+---+   |   |   |   | 
*                |   |   |   |   |   | 
.subckt bldcmtr p1a p1b p2a p2b p3a p3b shaft_speed shaft_angle 
+ params: 
+ J= 3e-5 ; moment of inertia of rotor (Kg*m^2) 
+ B= 3.6e-5 ; Damping and eddy current losses 
* (linear torque with speed) (Kg*m*sec/rad) 
+ F= 7.2e-5 ; Friction/drag losses (constant torque losses) 
* (Kg*m) 
+ D= 2.9e-5 ; Magnetic detent torque (Kg*m) 
+ A= 2 ; Number of north poles on the rotor 
+ P= 3 ; Number of phases (if you change this you need 
* to add more windings to the motor subckt.) 
+ CL=3mh ; winding inductance (Henrys) 
+ CR=6ohm ; winding resistance (Ohms) 
+ CC=.001uf ; winding capacitance to ground (Farads) 
+ CM=.5 ; adjacent winding mutual coupling factor 
+ Cb=.12 ; Back EMF constant (Volt*sec/rev) 
+ Ct=3e-3 ; Torque constant (N*m/amp) 
+ twopi = {2 * 3.141596} 
* Model each winding. The inductor must be here so we can include 
* mutual inductance. The other effects are modeled in 
* motor_winding 
Lwinding1 p1a p1x {CL} 
R_snub_1 p1a p1x {1K*twopi*CL} 
* ; snubbing resistor to limit coil Q 
x1 p1x p1b shaft_speed shaft_angle motor_winding 
+ params: N=1 A={A} P={P} CL={CL} CR={CR} CC={CC} 
+ CM={CM} Cb={Cb} Ct={Ct} twopi={twopi} 
Lwinding2 p2a p2x {CL} 
R_snub_2 p2a p2x {1K*twopi*CL} 
* ; snubbing resistor to limit coil Q 
x2 p2x p2b shaft_speed shaft_angle motor_winding 
+ params: N=2 A={A} P={P} CL={CL} CR={CR} CC={CC} 
+ CM={CM} Cb={Cb} Ct={Ct} twopi={twopi} 
Lwinding3 p3a p3x {CL} 
R_snub_3 p3a p3x {1K*twopi*CL} 
* ; snubbing resistor to limit coil Q 
x3 p3x p3b shaft_speed shaft_angle motor_winding 
+ params: N=3 A={A} P={P} CL={CL} CR={CR} CC={CC} 
+ CM={CM} Cb={Cb} Ct={Ct} twopi={twopi} 
* Model the mutual inductance here. 
* (For three phase, all windings are adjacent to each other.) 
k1 Lwinding1 Lwinding2 {Cm} 
k2 Lwinding2 Lwinding3 {Cm} 
k3 Lwinding3 Lwinding1 {Cm} 
* Model the motor mechanical system. 
x4 shaft_speed shaft_angle motor_mech 
+ params: J={J} B={B} F={F} D={D} A={A} P={P} twopi={twopi} 
.ends 
* 
* The motor winding 
* 
* This models the electrical properties of the windings, 
* and creates the torque "current" which is delivered to 
* the mechanical model. 
* Mutual inductance is modeled in the motor subcircuit, 
* so the inductance must be there also. The inductance 
* must be in series with this model. 
.subckt motor_winding winding1 winding2 shaft_speed shaft_angle 
+ params: N=1 A=2 P=3 CL=3mh CR=6ohm CC=.001uf CM=.5 Cb=.12 Ct=3e-3 
+ twopi={2*3.141596} 
* The electrical model: backemf, resistance, and capacitance 
Ebackemf winding1 3 VALUE = {Cb * V(shaft_speed) * V(factor)} 
Vsense 3 4 0v ; measure winding current 
Rwinding 4 winding2 {CR} 
* Place half the winding capacitance at each end of the winding 
C1 winding1 0 {CC/2} 
C2 winding2 0 {CC/2} 
* The mechanical model: torque created by this winding 
Gtorque 0 shaft_speed VALUE = {Ct * I(Vsense) * V(factor) } 
* The shaft angle function for this phase. 
Efactor factor 0 VALUE = {sin(A*V(shaft_angle) - (N-1)*(twopi/P))} 
Cdummy factor 0 10uf ; force timestep control 
.ends
.end

