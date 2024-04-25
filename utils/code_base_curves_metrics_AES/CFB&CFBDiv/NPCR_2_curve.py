import numpy as np
import matplotlib.pyplot as plt
import math
import os
import cv2
import sys
sys.path.append('../')
import pickle

from lib.metriques import *

def main() :
    modes_op_aes = ["CFB","CFB_dec_bad_key"]
    npcr_modes = []

    with open("NPCR_2_results.bin","rb") as f:
        npcr_modes = pickle.load(f)


    # for i in range(len(npcr_modes)):
    #     for y in range(len(npcr_modes[i])) :
    #         print(modes_op_aes[i] + ':' + str(npcr_modes[i][y]))

    ############ MOYENNES ############

    t_ecart_type = []
    t_ecart_type2 = []
    t_avg = []
    for i in range(0, len(npcr_modes)):
        sum = 0
        sum_pow = 0
        for y in range (0, len(npcr_modes[i])):
            sum += npcr_modes[i][y]
            sum_pow += pow(npcr_modes[i][y], 2)
        avg = sum/len(npcr_modes[i])
        pow_avg = sum_pow/len(npcr_modes[i])
        t_avg.append(avg)
        var = pow_avg - pow(avg,2)
        t_ecart_type.append(math.sqrt(var))
        t_ecart_type2.append(math.sqrt(var)/2)


    ########## BARRES ##########
    x = modes_op_aes
    y = t_avg
    couleurs = ['purple', 'pink']
    plt.bar(x, y, color=couleurs)
    plt.errorbar(range(len(y)),y,t_ecart_type2, fmt='none',capsize=10,ecolor='black',elinewidth=2,capthick=2)

    plt.xlabel('Mode opératoire')
    plt.ylabel('NPCR')
    plt.title('Graphe du NPCR moyen de 1000 images chiffrées par chiffrement AES en CFB et déchiffrées (mauvaise clé)')

    font = {'family': 'serif',
            'color':  'black',
            'weight': 'bold',
            'size': 8
            }

    box = {'facecolor': 'none',
        'edgecolor': 'black',
        'boxstyle': 'round'
        }


    avg_min, avg_max = min(t_avg), max(t_avg)
    ecart_min, ecart_max = min(t_ecart_type), max(t_ecart_type)

    facteur = 0.60

    mini = avg_min - facteur * ecart_max
    maxi = avg_max + facteur * ecart_max

    plt.ylim(mini, maxi)
    espacement = (maxi - mini) / 30
    plt.yticks(np.arange(mini, maxi + espacement, espacement))

    for i in range(0, len(modes_op_aes)):
        plt.text( modes_op_aes[i], t_avg[i] + espacement/2 , 's = '+ str(t_ecart_type[i])+'', fontdict=font, bbox=box)
    plt.show()
    

    ########## COURBES ##########

    for i in range(0,len(npcr_modes)):
            
        x = np.arange(0, len(npcr_modes[i])) 
        y = npcr_modes[i]

        plt.plot(x, y,label=modes_op_aes[i],color = couleurs[i])

    plt.xlabel('Images')
    plt.ylabel('NPCR')
    plt.title('Courbes du NPCR d\'images chiffrées par chiffrement AES en CFB et déchiffrées (mauvaise clé)')
    plt.grid()
    plt.legend()
    plt.show()


if __name__ == "__main__":
    main()
