
const networks = [
    500*500,
    1000*1000,
    2000*2000,
    4000*4000,
    5000*5000,
    7000*7000,
    8000*8000,
];

const T_sec = {};
T_sec[networks[0]] = 0.515;
T_sec[networks[1]] = 2.294;
T_sec[networks[2]] = 10.122;
T_sec[networks[3]] = 44.282;
T_sec[networks[4]] = 71.816;
T_sec[networks[5]] = 74.511;
T_sec[networks[6]] = 97.842;

let C = 0;
networks.forEach((n) => {
    C += T_sec[n]/(n*Math.log2(n));
});
C = C/7;
console.log(`C = ${C}`);

const T = {};
T[networks[0]] = 0.01;
T[networks[1]] = 0.038;
T[networks[2]] = 0.148;
T[networks[3]] = 0.602;
T[networks[4]] = 0.971;
T[networks[5]] = 1.927;
T[networks[6]] = 2.466;

// const networks = [
//     500*500,
//     1000*1000,
//     2500*2500,
//     5000*5000,
//     8000*8000,
// ];
//
// const T_sec = {};
// T_sec[networks[0]] = 0.438;
// T_sec[networks[1]] = 2.042;
// T_sec[networks[2]] = 13.838;
// T_sec[networks[3]] = 61.366;
// T_sec[networks[4]] = 161.118;
//
// let C = 0;
// networks.forEach((n) => {
//     C += T_sec[n]/(n*Math.log2(n));
// });
// C = C/5;
// console.log(`C = ${C}`);
//
// const T = {};
// T[networks[0]] = 0.0140
// T[networks[1]] = 0.0550
// T[networks[2]] = 0.3540
// T[networks[3]] = 1.4380
// T[networks[4]] = 3.7480


const beats = 28;


networks.forEach((N) => {
    console.log(`******* start ${N} *******`);
    let n = Math.round(N/128);
    let T1 = C*n*Math.log2(n);
    let T2 = C*beats*(0.1*Math.pow(10, -6)+(n*12)/(425*1024*1024));
    let T3 = C*n*beats;
    let T_est = T1+T2+T3;

    let T_sec = C*N*Math.log2(N);

    let Emax = T_sec/(128*T_est);

    let E = T_sec/(128*T[N]);
    let E_Emax = E/Emax;

    let Smax = T_sec/T_est;
    let S = T_sec/T[N];

    // console.log(`n: ${n}`);
    // console.log(`T1: ${T1}`);
    // console.log(`T2: ${T2}`);
    // console.log(`T3: ${T3}`);
    console.log(`Time est: ${T_est}`);
    console.log(`T_sec: ${T_sec}`);
    console.log(`E max: ${Emax}`);
    console.log(`E: ${E}`);
    console.log(`E/Emax: ${E_Emax}`);
    console.log(`Smax: ${Smax}`);
    console.log(`S: ${S}`);
    console.log(`******* end ${n} *******\n`);
});
