
const networks = [
    500*500,
    1000*1000,
    2000*2000,
    4000*4000,
    5000*5000,
    6000*6000,
    7000*7000,
];

const T = {};
T[networks[0]] = 0.009;
T[networks[1]] = 0.035;
T[networks[2]] = 0.142;
T[networks[3]] = 0.577;
T[networks[4]] = 0.945;
T[networks[5]] = 1.33;
T[networks[6]] = 1.88;

const beats = 22;

const C = 107.71*Math.pow(10, -9)
networks.forEach((n) => {
    console.log(`******* start ${n} *******`);
    let T1 = C*n*Math.log2(n);
    let T_est = T1+C*beats*(0.1+n*12/425)+C*n*beats;
    let Emax = T1/(128*T_est);
    let E = T1/(128*T[n]);
    let E_Emax = E/Emax;
    let Smax = T1/T_est;
    let S = T1/T[n];
    console.log(`Time est: ${T_est}`);
    console.log(`E max: ${Emax}`);
    console.log(`E: ${E}`);
    console.log(`E/Emax: ${E_Emax}`);
    console.log(`Smax: ${Smax}`);
    console.log(`S: ${S}`);
    console.log(`******* end ${n} *******\n`);
});
