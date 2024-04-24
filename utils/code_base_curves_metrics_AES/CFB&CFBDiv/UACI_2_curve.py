import numpy as np
import matplotlib.pyplot as plt
import math
import os
import cv2
import sys
import pickle
sys.path.append('../')

from lib.metriques import *

def main() :

    modes_op_aes = ["CFB","CFB_dec_bad_key"]
    uaci_modes = []

    with open("UACI_2_results.bin","rb") as f :
        uaci_modes = pickle.load(f)

    ############ MOYENNES ############

    t_ecart_type = []
    t_avg = []
    for i in range(0, len(uaci_modes)):
        sum = 0
        sum_pow = 0
        for y in range (0, len(uaci_modes[i])):
            sum += uaci_modes[i][y]
            sum_pow += pow(uaci_modes[i][y], 2)
        avg = sum/len(uaci_modes[i])
        pow_avg = sum_pow/len(uaci_modes[i])
        t_avg.append(avg)
        var = pow_avg - pow(avg,2)
        t_ecart_type.append(math.sqrt(var))

    ########## BARRES ##########
    x = modes_op_aes
    y = t_avg
    couleurs = ['purple', 'pink']
    plt.bar(x, y, color=couleurs)

    plt.xlabel('Mode opératoire')
    plt.ylabel('UACI')
    plt.title('Graphe du UACI moyen de 1000 images chiffrées par chiffrement AES en CFB et déchiffrées (mauvaise clé)')

    font = {'family': 'serif',
            'color':  'black',
            'weight': 'bold',
            'size': 8
            }

    box = {'facecolor': 'none',
        'edgecolor': 'black',
        'boxstyle': 'round'
        }

    for i in range(0, len(modes_op_aes)):
        plt.text(modes_op_aes[i], t_avg[i] + 0.00005 , 's = '+ str(t_ecart_type[i])+'', fontdict=font, bbox=box)
    
    mini = min(t_avg) - 0.0005
    maxi = max(t_avg) + 0.0005
    plt.ylim(mini,maxi)
    plt.yticks(np.arange(mini,maxi, 0.0001))
    plt.show()


    ########## COURBES ##########

    for i in range(0,len(uaci_modes)):            
        x = np.arange(0, len(uaci_modes[i])) 
        y = uaci_modes[i]

        plt.plot(x, y,label=modes_op_aes[i],color=couleurs[i])

    plt.xlabel('Images')
    plt.ylabel('UACI')
    plt.title('Courbes du UACI d\'images chiffrées par chiffrement AES en CFB et déchiffrées (mauvaise clé)')
    plt.grid()
    plt.legend()
    plt.show()


if __name__ == "__main__":
    main()
