Vin(min) = 2.7V
Vin(max) = 3.6V
Vout = 3.3V
Iout = 1A
f = 1.6MHz
Vd = 0.7V
efficiency target = 90%
peak to peak ripple = 40%

delta(t) = 1/f

                 Vout + Vd            3.3V + 0.7V
Duty(min) = -------------------- = ------------------ = 52.6%
            Vin(max) + Vout + Vd   3.6V + 3.3V + 0.7V

                 Vout + Vd            3.3V + 0.7V
Duty(max) = -------------------- = ------------------ = 59.7%
            Vin(min) + Vout + Vd   2.7V + 3.3V + 0.7V


                   Vout
Iripple = Iout * -------- * Ipp(ripple)
                 Vin(min)

              3.3
        = 1 * ---- * 0.4 = 0.4888..
              2.7


        delta(i)                   delta(t)    Vin(min)
V = L * -------- => L = Vin(min) * -------- = ----------- * d(max)
        delta(t)                   delta(i)   Iripple * f


L = 2.7/(.489 * 1600000)*.597 = 2.06uH

Halved because coupled => 1uH

              Vout * Iout
L1 Irms = --------------------- = 1.36A
          Vin(min) * efficiency

L2 Irms = Iout = 1A

L1 Ipeak = Irms + (0.5*Iripple) = 1.36 + 0.5*.4888 = 1.6A

L2 Ipeak = Irms + (0.5*Iripple) + 1 + 0.5*.4888 = 1.24
