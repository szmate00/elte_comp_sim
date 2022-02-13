#######################################################################
# Python script to create the appropriate figures for the assignment. #
# @Máte Szűcs, 2022                                                   #
#######################################################################

import os
import numpy as np
import matplotlib. pyplot as plt

plt.style.use('science')


def x(x0: float, v0: float, omega: float, t: float) -> float:
    return x0 * np.cos(omega * t) + v0/omega * np.sin(omega * t)

def v(x0: float, v0: float, omega: float, t: float) -> float:
    return -x0 * omega * np.sin(omega * t) + v0 * np.cos(omega * t)

def createPlots(input: str, outPath: str, x0: float=10., v0: float=10., omega: float=13.):
    dataE = np.loadtxt(f'out/{input}E.txt').T
    dataEC = np.loadtxt(f'out/{input}EC.txt').T

    dataERun = np.loadtxt(f'out/{input}ERun.txt').T
    dataECRun = np.loadtxt(f'out/{input}ECRun.txt').T

    tE = dataE[0]
    xE = dataE[1]
    vE = dataE[2]
    EE = dataE[3]

    tEC = dataEC[0]
    xEC = dataEC[1]
    vEC = dataEC[2]
    EEC = dataEC[3]

    nERun = dataERun[0]
    tERun = dataERun[1]

    nECRun = dataECRun[0]
    tECRun = dataECRun[1]

    # Energia
    plt.figure(figsize=(10, 5))
    plt.plot(tE, EE, label='Euler módszer')
    plt.plot(tEC, EEC, label='Euler-Cromer módszer')
    plt.plot(tE, [EE[0] for i in tE], '--', alpha=0.9,label='Analitikus megoldás')

    plt.xlabel('$t~[s]$', size=18)
    plt.ylabel('$E$', size=18)
    plt.title('$x_0=10, v_0=10, \omega=13$', size=18)
    plt.legend(loc='upper left')
    plt.savefig(f'{outPath}/energia.png', dpi=100)

    # Kitérés-idő
    plt.figure(figsize=(10, 5))
    plt.plot(tE, xE, label='Euler módszer')
    plt.plot(tEC, xEC, label='Euler-Cromer módszer')
    plt.plot(tE, [x(x0, v0, omega, i) for i in tE], '--', alpha=0.9, label='Analitikus megoldás')

    plt.xlabel('$t~[s]$', size=18)
    plt.ylabel('$x(t)$', size=18)
    plt.title('$x_0=10, v_0=10, \omega=13$', size=18)
    plt.legend(loc='upper left')
    plt.savefig(f'{outPath}/kit_ido.png', dpi=100)

    # Kitérés-sebesség
    plt.figure(figsize=(10, 5))
    plt.plot(tE, vE, label='Euler módszer')
    plt.plot(tEC, vEC, label='Euler-Cromer módszer')
    plt.plot(tE, [v(x0, v0, omega, i) for i in tE], '--', alpha=0.9, label='Analitikus megoldás')

    plt.xlabel('$t~[s]$', size=18)
    plt.ylabel('$v(t)$', size=18)
    plt.title('$x_0=10, v_0=10, \omega=13$', size=18)
    plt.legend(loc='upper left')
    plt.savefig(f'{outPath}/kit_seb.png', dpi=100)

    # Runtime
    plt.figure(figsize=(10, 5))
    plt.plot(nERun, tERun, 'o-', label='Euler módszer')
    plt.plot(nECRun, tECRun, 'o-', label='Euler-Cromer módszer')

    plt.ylabel('futási idő [ms]', size=18)
    plt.xlabel('lépések száma', size=18)
    plt.title('$x_0=10, v_0=10, \omega=13$', size=18)
    plt.legend(loc='upper left')
    plt.savefig(f'{outPath}/futas.png', dpi=100)


if __name__ == '__main__':
    createPlots('out', 'figures')